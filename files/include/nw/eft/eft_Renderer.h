#ifndef EFT_RENDERER_H_
#define EFT_RENDERER_H_

#include <nw/eft/eft_Emitter.h>
#include <nw/eft/eft_TemporaryBuffer.h>

#include <nw/eft/cafe/eft_CafeWrapper.h>

namespace nw { namespace eft {

class  Config;
class  Heap;
class  ParticleShader;
class  Primitive;
struct PtclAttributeBuffer;
struct PtclInstance;
struct PtclStripe;
struct StripeVertexBuffer;
class  System;
struct ViewUniformBlock;

class Renderer
{
private:
    struct sortPtcl
    {
        PtclInstance*   ptcl;
        f32             z;
        u32             index;
    };
    static_assert(sizeof(sortPtcl) == 0xC, "nw::eft::Renderer::sortPtcl size mismatch");

    static s32 ComparePtclViewZ(const void* a, const void* b);

public:
    Renderer(Heap* heap, System* system, const Config& config);
    ~Renderer();

    void BeginRender(const nw::math::MTX44& proj, const nw::math::MTX34& view, const nw::math::VEC3& camPos, f32 near, f32 far);
    void EntryParticle(EmitterInstance* emitter, bool cacheFlush = true, void* userParam = NULL);

    void EntryParticleFromCallback(const EmitterInstance* emitter, bool cacheFlush, void* userParam)
    {
        if (mCurrentDrawingType == EFT_PTCL_TYPE_CHILD)
            EntryChildParticleSub(emitter, cacheFlush, userParam);
        else
            EntryParticleSub(emitter, cacheFlush, userParam);
    }

    void EndRender();

    void SetDepthTexture(Texture depthTexture, f32 offsetU = 0.0f, f32 offsetV = 0.0f, f32 scaleU = 1.0f, f32 scaleV = 1.0f)
    {
        SetTextureSlot(EFT_TEXTURE_SLOT_DEPTH_BUFFER, depthTexture);
        mDepthTextureOffset.x   = offsetU;
        mDepthTextureOffset.y   = offsetV;
        mDepthTextureScale.x    = scaleU;
        mDepthTextureScale.y    = scaleV;
    }

    void SetFrameBufferTexture( Texture frameBufferTexture, f32 offsetU = 0.0f, f32 offsetV = 0.0f, f32 scaleU = 1.0f, f32 scaleV = 1.0f )
    {
        SetTextureSlot(EFT_TEXTURE_SLOT_FRAME_BUFFER, frameBufferTexture);
        mFrameBufferTextureOffset.x = offsetU;
        mFrameBufferTextureOffset.y = offsetV;
        mFrameBufferTextureScale.x  = scaleU;
        mFrameBufferTextureScale.y  = scaleV;
    }

    void SetTextureSlot(TextureSlot slot, Texture texture)
    {
        mExtensionTexture[slot - EFT_TEXTURE_SLOT_BIN_MAX] = texture;
    }

    void SwapDoubleBuffer();
    void* AllocFromDoubleBuffer(u32 size);

    u32 GetDoubleBufferSize() const
    {
        return mTemporaryBuffer.GetSize();
    }

    u32 GetUsedDoubleBufferSize() const
    {
        return mTemporaryBuffer.GetUsedSize();
    }

    void FlushCache();

    ParticleShader* GetShader(const EmitterInstance* emitter)
    {
        if (mCurrentDrawingType == EFT_PTCL_TYPE_CHILD)
        {
            return emitter->childShader[mCurrentShaderType];
        }
        else
        {
            return emitter->shader[mCurrentShaderType];
        }
    }

    u8 GetUserShaderSetting(const EmitterInstance* emitter)
    {
        if (mCurrentDrawingType == EFT_PTCL_TYPE_CHILD)
        {
            const ComplexEmitterData* res  = reinterpret_cast<const ComplexEmitterData*>(emitter->res);
            const ChildData*          cres = reinterpret_cast<const ChildData*>(res + 1);

            return cres->childUserShaderSetting;
        }
        else
        {
            return emitter->res->userShaderSetting;
        }
    }

    u32 GetUserShaderFlag(const EmitterInstance* emitter)
    {
        if (mCurrentDrawingType == EFT_PTCL_TYPE_CHILD)
        {
            const ComplexEmitterData* res  = reinterpret_cast<const ComplexEmitterData*>(emitter->res);
            const ChildData*          cres = reinterpret_cast<const ChildData*>(res + 1);

            return cres->childUserShaderFlag;
        }
        else
        {
            return emitter->res->userShaderFlag;
        }
    }

    const nw::eft::UserShaderParam* GetUserShaderParam(const EmitterInstance* emitter)
    {
        if (mCurrentDrawingType == EFT_PTCL_TYPE_CHILD)
        {
            const ComplexEmitterData* res  = reinterpret_cast<const ComplexEmitterData*>(emitter->res);
            const ChildData*          cres = reinterpret_cast<const ChildData*>(res + 1);

            return &cres->childUserShaderParam;
        }
        else
        {
            return &emitter->res->userShaderParam;
        }
    }

    f32 GetParentParticleUserShaderParam(const EmitterInstance* emitter, u32 paramIdx)
    {
        return emitter->res->userShaderParam.param[paramIdx];
    }

    f32 GetChildParticleUserShaderParam(const EmitterInstance* emitter, u32 paramIdx)
    {
        const ComplexEmitterData* res  = reinterpret_cast<const ComplexEmitterData*>(emitter->res);
        const ChildData*          cres = reinterpret_cast<const ChildData*>(res + 1);

        return cres->childUserShaderParam.param[paramIdx];
    }

    f32 GetUserShaderParam(const EmitterInstance* emitter, u32 paramIdx)
    {
        if (mCurrentDrawingType == EFT_PTCL_TYPE_CHILD)
        {
            const ComplexEmitterData* res  = reinterpret_cast<const ComplexEmitterData*>(emitter->res);
            const ChildData*          cres = reinterpret_cast<const ChildData*>(res + 1);

            return cres->childUserShaderParam.param[paramIdx];
        }
        else
        {
            return emitter->res->userShaderParam.param[paramIdx];
        }
    }

    void SetDrawViewFlag(DrawViewFlag flag)
    {
        mDrawViewFlag = flag;
    }

    DrawViewFlag GetDrawViewFlag() const
    {
        return mDrawViewFlag;
    }

    u32 GetStripeVertexCalcNum() const
    {
        return mStripeVertexCalcNum;
    }

    const System* GetEffectSystem() const
    {
        return mSystem;
    }

    void SetShaderType(ShaderType type)
    {
        mCurrentShaderType = type;
    }

    bool MakeStripeAttributeBlock(EmitterInstance* emitter);
    StripeVertexBuffer* MakeConnectionStripeAttributeBlock(EmitterInstance* emitter, bool cacheFlush);

    Primitive* GetCurrentPrimitive() const
    {
        return mCurrentPrimitive;
    }

    Rendercontext& GetRenderContext()
    {
        return mRenderContext;
    }

    PtclType GetPtclType() const
    {
        return mCurrentDrawingType;
    }

    nw::math::MTX44 GetViewMatrix() const
    {
        return mMatView;
    }

    nw::math::MTX44 GetViewProjMatrix() const
    {
        return mMatViewProj;
    }

private:
    void EntryParticleSub(const EmitterInstance* emitter, bool cacheFlush, void* userParam);
    void EntryChildParticleSub(const EmitterInstance* emitter, bool cacheFlush, void* userParam);

    void RequestParticle(const EmitterInstance*  e,
                         ParticleShader*         shader,
                         bool                    bChild,
                         bool                    cacheFlush,
                         void*                   userParam);

    bool SetupParticleShaderAndVertex(ParticleShader* shader, MeshType meshType, Primitive* primitive);

    void EntryStripe(EmitterInstance* emitter, bool cacheFlush, void* userParam);
    void EntryConnectionStripe(EmitterInstance* emitter, bool cacheFlush, void* userParam);
    bool SetupStripeDrawSetting(const EmitterInstance* emitter, bool cacheFlush, void* userParam);

    s32 MakeStripeAttributeBlockCore(PtclStripe* __restrict stripe, StripeVertexBuffer* stripeVertex, s32 wroteVertexNum);
    s32 MakeStripeAttributeBlockCoreDivide(PtclStripe* stripe, StripeVertexBuffer* stripeVertex, s32 wroteVertexNum, s32 numDivide);

    s32 MakeConnectionStripeAttributeBlockCore(EmitterInstance* emitter, s32 numPtcl, PtclInstance* pTailPtcl, PtclInstance* pTail2ndPtcl, s32 tailType, StripeVertexBuffer* stripeVertex, s32 wroteVertexNum = 0);
    s32 MakeConnectionStripeAttributeBlockCoreDivide(EmitterInstance* emitter, s32 numPtcl, PtclInstance* pTailPtcl, PtclInstance* pTail2ndPtcl, s32 tailType, StripeVertexBuffer* stripeVertex, s32 wroteVertexNum = 0);

    bool ConnectionStripeUvScaleCalc(f32& frateScaleUv, f32& uvStartOfs, const EmitterInstance* emitter, s32 numLoop, f32 frateScale, s32 tailType);

    static void GetPositionOnCubic(nw::math::VEC3*         retPos,
                                   const nw::math::VEC3&   startPos,
                                   const nw::math::VEC3&   startVel,
                                   const nw::math::VEC3&   endPos,
                                   const nw::math::VEC3&   endVel,
                                   float                   time);

private:
    void BindParticleAttributeBlock(PtclAttributeBuffer* ptclAttributeBuffer, ParticleShader* shader, u32 entryNum);

private:
    System*                         mSystem;
    Heap*                           mHeap;
    Rendercontext                   mRenderContext;
    Draw::PrimitiveType             mDrawPrimitiveType;
    nw::math::MTX44                 mMatView;
    nw::math::MTX44                 mMatViewProj;
    nw::math::MTX44                 mMatBillboard;
    nw::math::VEC3                  mEyeVec;
    nw::math::VEC3                  mEyePos;
    VertexBuffer                    mPositionVB;
    VertexBuffer                    mIndexVB;
    Primitive*                      mCurrentPrimitive;
    ViewUniformBlock*               mViewUniformBlock;
    Texture                         mExtensionTexture[EFT_TEXTURE_SLOT_MAX - EFT_TEXTURE_SLOT_BIN_MAX];
    nw::math::VEC2                  mDepthTextureOffset;
    nw::math::VEC2                  mDepthTextureScale;
    nw::math::VEC2                  mFrameBufferTextureOffset;
    nw::math::VEC2                  mFrameBufferTextureScale;
    TemporaryBuffer                 mTemporaryBuffer;
    u32                             mStripeVertexCalcNum;
    PtclType                        mCurrentDrawingType;
    ShaderType                      mCurrentShaderType;
    DrawViewFlag                    mDrawViewFlag;
};
static_assert(sizeof(Renderer) == 0x17C, "nw::eft::Renderer size mismatch");

} } // namespace nw::eft

#endif // EFT_RENDERER_H_
