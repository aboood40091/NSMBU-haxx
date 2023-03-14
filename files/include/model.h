#pragma once

#include <container/seadBuffer.h>

#include "renderobjlayer.h"
#include "modelresource.h"

class ModelNW : public Model
{
    SEAD_RTTI_OVERRIDE(ModelNW, Model)

public:
    // Calculates the drawing resources for skeleton matrices, shapes and materials
    void calc() override;

    // Updates buffers for the GPU
    void calcGPU(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderer) override;

    // (Does nothing)
    void updateView(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderer) override;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Notes:
    // 1. Shadow-only shapes and reflection-only shapes are always invisible
    // 2. Shadow casting for a shape is automatically enabled if "shadow_cast" is not present in its material's render info

    void drawOpa(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderer) override;
    void drawXlu(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderer) override;

    // This draws the shadow of shadow-casting shapes
    void drawShadowOpa(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderer) override;

    // These draws the reflection on shapes
    void drawReflectionOpa(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderer) override;
    void drawReflectionXlu(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderer) override;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool hasShadow() const override;

    virtual ~ModelNW();

    void updateAnimations() override;
    void updateModel() override;

    // Rotation + Translation matrix
    void setMtx(const Mtx34& mtxRT) override;
    const Mtx34& getMtx() const override;

    void setScale(const Vec3& scale) override;
    const Vec3& getScale() const override;

    // Determines if there are any shapes that can be drawn by draw*Opa()
    bool hasOpa() const override;
    // Determines if there are any shapes that can be drawn by draw*Xlu()
    bool hasXlu() const override;

    s32 getBoneIdx(const sead::SafeString& name) const override;
    const char* getBoneName(u32 idx) const override;
    u32 getBoneCount() const override;
    void setBoneSRT(u32 idx, const Mtx34& mtxRT, const Vec3& scale) override;
    void getBoneSRT(u32 idx, Mtx34* mtxRT = NULL, Vec3* scale = NULL) override;
    // World matrix for bone
    void setBoneTransform(u32 idx, const Mtx34& transform) override;
    void getBoneTransform(u32 idx, Mtx34& transform) override;
    void setBoneVisibility(u32 idx, bool visibility) override;
    bool getBoneVisibility(u32 idx) const override; // deleted
    u32 getMaterialCount() const override;
    s32 getMaterialIdx(const sead::SafeString& name) const override;
    const char* getMaterialName(u32 idx) const override;
    Material& getMaterial(u32 idx) override;
    void setMaterialVisibility(u32 idx, bool visibility) override;
    bool getMaterialVisibility(u32 idx) const override; // deleted
    void vf124() override; // deleted
    void vf12C() override; // gets a flag
    const nw::g3d::Sphere& getBounding() override;
    void initViewShapesBuffer(void*, void*) override;
    void getName(sead::SafeString& name) const override;
    void setSklAnimRelatedFloat(u32 idx, f32) override;
    f32 getSklAnimRelatedFloat() override; // deleted
    void setSklAnim(u32 idx, const SkeletalAnimation& anim) override;
    void setTexAnim(u32 idx, const TexturePatternAnimation& anim) override;
    void setShuAnim(u32 idx, const ShaderParamAnimation& anim) override;
    void setVisAnim(u32 idx, const VisibilityAnimation& anim) override;
    void setShaAnim(u32 idx, const ShapeAnimation& anim) override;
    const SkeletalAnimation** getSklAnims() const override;
    const TexturePatternAnimation** getTexAnims() const override;
    const ShaderParamAnimation** getShuAnims() const override;
    const VisibilityAnimation** getVisAnims() const override;
    const ShapeAnimation** getShaAnims() const override;

    // ...
};


struct FrameCtrl
{
    enum Flags
    {
        FlagRepeat  = 1 << 0,
        FlagUnk2    = 1 << 1,
        FlagIsDone  = 1 << 5,
    };

    void setRepeat(bool repeat);

    inline bool isAnimationDone() { return flags & FlagIsDone; }

    f32 startFrame; // 0    Inited to 0.0
    f32 endFrame;   // 4    Inited to 1.0
    f32 _8;         // 8    Inited to 0.0
    f32 _C;         // C    Inited to 1.0
    f32 frame;      // 10   Inited to 0.0
    f32 speed;      // 14   Inited to 1.0
    u32 flags;      // 18   Inited to FlagRepeat | FlagUnk2
};

class Animation : public FrameCtrl
{
public:
    Animation();
    virtual void calculate() = 0;
};

class SkeletalAnimation : public Animation  // size: 0x98
{
public:
    SkeletalAnimation();
    void calculate() override;

    void init(ModelNW* model, ModelResource* resource, void* unk, sead::Heap* heap);
    void play(ModelResource* resource, const sead::SafeString& identifier);

    // nw::g3d::SkeletalAnimObj at 0x20
};

class TexturePatternAnimation : public Animation
{
public:
    TexturePatternAnimation();
    void calculate() override;

    void play(ModelResource* resource, const sead::SafeString& identifier);
};

class ShaderParamAnimation : public Animation
{
public:
    ShaderParamAnimation();
    void calculate() override;

    void playColorAnim(ModelResource* resource, const sead::SafeString& identifier);
    void playTexSrtAnim(ModelResource* resource, const sead::SafeString& identifier);
};

class VisibilityAnimation : public Animation
{
public:
    VisibilityAnimation();
    void calculate() override;

    void play(ModelResource* resource, const sead::SafeString& identifier);
};

class ShapeAnimation : public Animation
{
public:
    ShapeAnimation();
    void calculate() override;

    void play(ModelResource* resource, const sead::SafeString& identifier);
};


class BasicModel
{
public:
    BasicModel(ModelNW* model, u32 numSklAnims, u32 numTexAnims, u32 numShuAnims, u32 numVisAnims, u32 numShaAnims);
    void setup(ModelResource* resource, void* unk, sead::Heap* heap);
    void updateModel();
    void updateAnimations();

    inline void setMtx(const Mtx34& mtxRT)
    {
        model->setMtx(mtxRT);
    }

    inline const Mtx34& getMtx() const
    {
        return model->getMtx();
    }

    inline void setScale(const Vec3& scale)
    {
        model->setScale(scale);
    }

    inline const Vec3& getScale() const
    {
        return model->getScale();
    }

    inline void playSklAnim(const sead::SafeString& identifier, u32 idx)
    {
        sklAnims[idx]->play(resource, identifier);
    }

    inline void playTexPatternAnim(const sead::SafeString& identifier, u32 idx)
    {
        texAnims[idx]->play(resource, identifier);
    }

    inline void playColorAnim(const sead::SafeString& identifier, u32 idx)
    {
        shuAnims[idx]->playColorAnim(resource, identifier);
    }

    inline void playTexSrtAnim(const sead::SafeString& identifier, u32 idx)
    {
        shuAnims[idx]->playTexSrtAnim(resource, identifier);
    }

    inline void playBoneVisAnim(const sead::SafeString& identifier, u32 idx)
    {
        visAnims[idx]->play(resource, identifier);
    }

    inline void playShapeAnim(const sead::SafeString& identifier, u32 idx)
    {
        shaAnims[idx]->play(resource, identifier);
    }

    // boundingType: 0 = no bounding, 1 = bounding sphere, 2 = bounding box

    static inline BasicModel* create(const sead::SafeString& resourceIdentifier, const sead::SafeString& modelIdentifier, u32 numSklAnims = 0, u32 numTexAnims = 0, u32 numShuAnims = 0, u32 numVisAnims = 0, u32 numShaAnims = 0, u32 boundingType = 0, sead::Heap* heap = nullptr)
    {
        ModelResource* resource = ModelResourceMgr::instance->get(resourceIdentifier);
        return create(resource, modelIdentifier, numSklAnims, numTexAnims, numShuAnims, numVisAnims, numShaAnims, boundingType, heap);
    }

    static inline BasicModel* create(ModelResource* resource, const sead::SafeString& modelIdentifier, u32 numSklAnims = 0, u32 numTexAnims = 0, u32 numShuAnims = 0, u32 numVisAnims = 0, u32 numShaAnims = 0, u32 boundingType = 0, sead::Heap* heap = nullptr)
    {
        ModelNW* model = resource->getModel(modelIdentifier, numSklAnims, numTexAnims, numShuAnims, numVisAnims, numShaAnims, boundingType, heap);
        BasicModel* wrapper = new (heap) BasicModel(model, numSklAnims, numTexAnims, numShuAnims, numVisAnims, numShaAnims);
        wrapper->setup(resource, nullptr, heap);
        return wrapper;
    }

	ModelNW* model;                                     // 0
	ModelResource* resource;                            // 4
	sead::Buffer<SkeletalAnimation*> sklAnims;          // 8
	sead::Buffer<TexturePatternAnimation*> texAnims;    // 10
	sead::Buffer<ShaderParamAnimation*> shuAnims;       // 18
	sead::Buffer<VisibilityAnimation*> visAnims;        // 20
	sead::Buffer<ShapeAnimation*> shaAnims;             // 28
};
