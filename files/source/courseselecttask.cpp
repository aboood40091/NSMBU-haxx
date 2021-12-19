#include <framework/seadCalculateTask.h>
#include <framework/seadTaskMgr.h>

#include <agl/lyr/aglDrawMethod.h>
#include <agl/lyr/aglRenderer.h>
#include <agl/aglShaderLocation.h>
#include <gfx/seadCamera.h>
#include <gfx/seadGraphicsContext.h>
#include <gfx/seadPrimitiveRenderer.h>
#include <gfx/seadProjection.h>
#include <util/vec.h>
#include <layeragl.h>

#include "render/shader.h"
#include "render/texture.h"
#include "render/vbo.h"

#include <log.h>

#define COURSE_SELECT_DEBUG 0

class CourseSelectTask : public sead::CalculateTask
{
    SEAD_TASK_SINGLETON_DISPOSER(CourseSelectTask)

public:
    class Layer2D : public LayerAgl
    {
        Layer2D();
        virtual ~Layer2D();

        u32 getRenderStepNum() const override;
        void getRenderStepName(sead::SafeString* name, s32 idx) const override;
    };

public:
    CourseSelectTask(const sead::TaskConstructArg& arg);
    virtual ~CourseSelectTask();

    void prepare() override;
    void enter() override;
    void exit() override;
    void calc() override;

    void render(const agl::lyr::RenderInfo& render_info);

private:
    bool mInitialized;
    agl::lyr::DrawMethod mDrawMethod;
    ShaderUR* mShader;
    VBO* mVBO;
    Texture* mTexture1;
    Texture* mTexture2;
    agl::SamplerLocation mSamplerLoc1;
    agl::SamplerLocation mSamplerLoc2;
    Mtx34 mModelMtx;
    sead::LookAtCamera mCamera;
    sead::PerspectiveProjection mProjection;
    Vec3u mCubeRotations[10];
};

SEAD_TASK_SINGLETON_DISPOSER_IMPL(CourseSelectTask)

CourseSelectTask::CourseSelectTask(const sead::TaskConstructArg& arg)
    : sead::CalculateTask(arg, "CourseSelectTask")
    , mInitialized(false)
    , mShader(nullptr)
    , mVBO(nullptr)
    , mTexture1(nullptr)
    , mTexture2(nullptr)
{
    mCamera.getPos() = Vec3(0.0f, 0.0f, 3.0f);
    mCamera.getAt() = Vec3(0.0f, 0.0f, 2.0f);
    mCamera.doUpdateMatrix(&mCamera.getMatrix());
}

CourseSelectTask::~CourseSelectTask()
{
    if (mShader)
    {
        delete mShader;
        mShader = nullptr;
    }

    if (mVBO)
    {
        delete mVBO;
        mVBO = nullptr;
    }

    if (mTexture1)
    {
        delete mTexture1;
        mTexture1 = nullptr;
    }

    if (mTexture2)
    {
        delete mTexture2;
        mTexture2 = nullptr;
    }
}

// For GX2 texcoords, +Y is down, whereas for OpenGL texcoords, +Y is up
// GX2    -> (0, 0) is top    left and (1, 1) is bottom right
// OpenGL -> (0, 0) is bottom left and (1, 1) is top    right

// Alignment is not necessary, but recommended
#pragma alignvar(GX2_VERTEX_BUFFER_ALIGNMENT)
static const f32 vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f
};

static const Vec3 cubePositions[] = {
    Vec3( 0.0f,  0.0f,  0.0f),
    Vec3( 2.0f,  5.0f, -15.0f),
    Vec3(-1.5f, -2.2f, -2.5f),
    Vec3(-3.8f, -2.0f, -12.3f),
    Vec3( 2.4f, -0.4f, -3.5f),
    Vec3(-1.7f,  3.0f, -7.5f),
    Vec3( 1.3f, -2.0f, -2.5f),
    Vec3( 1.5f,  2.0f, -2.5f),
    Vec3( 1.5f,  0.2f, -1.5f),
    Vec3(-1.3f,  1.0f, -1.5f)
};

void CourseSelectTask::prepare()
{
    LOG("CourseSelectTask::prepare start")

    agl::lyr::Renderer::instance()->createLayer<Layer2D>(6,  "CourseSelect",     agl::lyr::cDisplayType_Top_TV,     nullptr);
  //agl::lyr::Renderer::instance()->createLayer<Layer2D>(24, "CourseSelect_DRC", agl::lyr::cDisplayType_Bottom_DRC, nullptr);

    mShader = new ShaderUR("res/7.2.camera.gsh");
    if (!mShader->isInitialized())
    {
        LOG("Shader loading failed.");
        delete mShader;
        mShader = nullptr;
        return;
    }

    mVBO = new VBO(0);
    if (!mVBO->setVertexAttrib(0, 0,               VBO::VAR_TYPE_VEC3) || // position
        !mVBO->setVertexAttrib(1, 3 * sizeof(f32), VBO::VAR_TYPE_VEC2))   // texcoord
    {
        LOG("Vertex Attributes setup failed.");
        delete mVBO;
        mVBO = nullptr;
        return;
    }

    mVBO->build();
    mVBO->bindBufferData(vertices, 36 * (5 * sizeof(f32)), 5 * sizeof(f32));

    {
        mTexture1 = new Texture("res/container.gtx");
        if (!mTexture1->isInitialized())
        {
            LOG("Texture 1 loading failed.");
            delete mTexture1;
            mTexture1 = nullptr;
            return;
        }

        agl::TextureSampler& sampler = mTexture1->getSampler();

        sampler.wrapX = GX2_TEX_CLAMP_WRAP;
        sampler.wrapY = GX2_TEX_CLAMP_WRAP;
        sampler.minFilter = GX2_TEX_XY_FILTER_BILINEAR;
        sampler.magFilter = GX2_TEX_XY_FILTER_BILINEAR;
        //sampler.mipFilter = GX2_TEX_MIP_FILTER_LINEAR;

        sampler.flags.setBit(1); // Update Wrap
        sampler.flags.setBit(2); // Update Filters

        mSamplerLoc1.name = "texture1";
        mSamplerLoc1.loc.ps = 0;
    }

    {
        mTexture2 = new Texture("res/awesomeface.gtx");
        if (!mTexture2->isInitialized())
        {
            LOG("Texture 2 loading failed.");
            delete mTexture2;
            mTexture2 = nullptr;
            return;
        }

        agl::TextureSampler& sampler = mTexture2->getSampler();

        sampler.wrapX = GX2_TEX_CLAMP_WRAP;
        sampler.wrapY = GX2_TEX_CLAMP_WRAP;
        sampler.minFilter = GX2_TEX_XY_FILTER_BILINEAR;
        sampler.magFilter = GX2_TEX_XY_FILTER_BILINEAR;
        //sampler.mipFilter = GX2_TEX_MIP_FILTER_LINEAR;

        sampler.flags.setBit(1); // Update Wrap
        sampler.flags.setBit(2); // Update Filters

        mSamplerLoc2.name = "texture2";
        mSamplerLoc2.loc.ps = 1;
    }

    mProjection.set(0.1f, 100.0f, sead::Mathf::deg2rad(45), 1280.0f / 720.0f);

    for (u32 i = 0; i < 10; i++)
    {
        mCubeRotations[i].x = i * 0x19999999u; // sead::GlobalRandom::instance()->randU32()
        mCubeRotations[i].y = i * 0x19999999u; // sead::GlobalRandom::instance()->randU32()
        mCubeRotations[i].z = i * 0x19999999u; // sead::GlobalRandom::instance()->randU32()
    }

    mInitialized = true;

    LOG("CourseSelectTask::prepare end")
}

void CourseSelectTask::enter()
{
    LOG("CourseSelectTask::enter")

    if (!mInitialized)
        return;

    mDrawMethod.bind(this, &CourseSelectTask::render, "CourseSelect");
    agl::lyr::Renderer::instance()->layers[6]->pushBackDrawMethod(0, &mDrawMethod);
}

void CourseSelectTask::exit()
{
    LOG("CourseSelectTask::exit")
}

#if COURSE_SELECT_DEBUG

static inline u32 getLyrVtbl(const agl::lyr::Layer* layer)
{
    return *((u32*)layer + 3);
}

#endif // COURSE_SELECT_DEBUG

void CourseSelectTask::calc()
{
#if COURSE_SELECT_DEBUG
    static bool first_frame = true;
    if (first_frame)
    {
        first_frame = false;

        sead::SafeString render_step_name;

        const sead::Buffer<agl::lyr::Layer*>& layers = agl::lyr::Renderer::instance()->layers;
        for (s32 i = 0; i < layers.getSize(); i++)
        {
            const agl::lyr::Layer* layer = layers[i];
            if (layer == NULL)
                continue;

            const char* name = (layer->name != NULL) ? layer->name
                                                     : "{no-name}";

            LOG("Layer %d, Name: %s, vtbl addr: 0x%08X", i, name, getLyrVtbl(layer));
            for (s32 j = 0; j < layer->getRenderStepNum(); j++)
            {
                layer->getRenderStepName(&render_step_name, j);
                LOG(" - Render Step %d: %s", j, render_step_name.cstr());
            }
        }
    }
#endif // COURSE_SELECT_DEBUG
}

void CourseSelectTask::render(const agl::lyr::RenderInfo& render_info)
{
    sead::GraphicsContext context;
    context.setDepthEnable(true, true);
    context.setDepthFunc(sead::Graphics::cDepthFunc_LessEqual);
    context.setCullingMode(sead::Graphics::cCullingMode_None);
    context.setBlendEnable(false);
    context.apply();

    mShader->use();
    mVBO->bind();
    mTexture1->getSampler().activate(mSamplerLoc1);
    mTexture2->getSampler().activate(mSamplerLoc2);

    mShader->setMat4("projection", mProjection.getDeviceProjectionMatrix());
    mShader->setMat4("view", mCamera.getMatrix());

    for (u32 i = 0; i < 10; i++)
    {
        mModelMtx.makeRTIdx(mCubeRotations[i], cubePositions[i]);
        mShader->setMat4("model", mModelMtx);

        GX2DrawEx(GX2_PRIMITIVE_TRIANGLES, 36, 0, 1);
    }

    sead::PrimitiveRenderer::instance()->setProjection(mProjection);
    sead::PrimitiveRenderer::instance()->setCamera(mCamera);
    sead::PrimitiveRenderer::instance()->setModelMatrix(Mtx34::ident);
    sead::PrimitiveRenderer::instance()->begin();

    sead::PrimitiveRenderer::QuadArg arg;
    arg.setCenter(Vec3(0.0f, 0.0f, 0.0f));
    arg.setSize(Vec2(2.0f, 2.0f));
    arg.setColor(sead::Color4f(0.0f, 0.0f, 1.0f, 1.0f),
                 sead::Color4f(0.0f, 1.0f, 0.0f, 1.0f));

    sead::PrimitiveRenderer::instance()->drawQuad(arg);

    sead::PrimitiveRenderer::instance()->end();
}
