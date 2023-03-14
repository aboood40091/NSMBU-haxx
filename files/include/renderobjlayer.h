#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>

#include "nw/g3d.h"
#include "renderobjlayerbase.h"

class SkeletalAnimation;
class TexturePatternAnimation;
class ShaderParamAnimation;
class VisibilityAnimation;
class ShapeAnimation;

class Model : public RenderObj, public sead::IDisposer
{
    SEAD_RTTI_OVERRIDE(Model, RenderObj)

public:
    class Material;

public:
    Model();
    virtual ~Model();

    virtual void updateAnimations() = 0;
    virtual void updateModel() = 0;
    virtual void setMtx(const Mtx34& mtxRT) = 0;
    virtual const Mtx34& getMtx() const = 0;
    virtual void setScale(const Vec3& scale) = 0;
    virtual const Vec3& getScale() const = 0;
    virtual bool hasOpa() const = 0;
    virtual bool hasXlu() const = 0;
    virtual s32 getBoneIdx(const sead::SafeString& name) const = 0;
    virtual const char* getBoneName(u32 idx) const = 0;
    virtual u32 getBoneCount() const = 0;
    virtual void setBoneSRT(u32 idx, const Mtx34& mtxRT, const Vec3& scale) = 0;
    virtual void getBoneSRT(u32 idx, Mtx34* mtxRT, Vec3* scale) = 0;
    virtual void setBoneTransform(u32 idx, const Mtx34& transform) = 0;
    virtual void getBoneTransform(u32 idx, Mtx34& transform) = 0;
    virtual void setBoneVisibility(u32 idx, bool visibility) = 0;
    virtual bool getBoneVisibility(u32 idx) const = 0;
    virtual u32 getMaterialCount() const = 0;
    virtual s32 getMaterialIdx(const sead::SafeString& name) const = 0;
    virtual const char* getMaterialName(u32 idx) const = 0;
    virtual Material& getMaterial(u32 idx) = 0;
    virtual void setMaterialVisibility(u32 idx, bool visibility) = 0;
    virtual bool getMaterialVisibility(u32 idx) const = 0;
    virtual void vf124() = 0;
    virtual void vf12C() = 0;
    virtual const nw::g3d::Sphere& getBounding() = 0;
    virtual void initViewShapesBuffer(void*, void*) = 0;
    virtual void getName(sead::SafeString& name) const = 0;
    virtual void setSklAnimRelatedFloat(u32 idx, f32) = 0;
    virtual f32 getSklAnimRelatedFloat() = 0;
    virtual void setSklAnim(u32 idx, const SkeletalAnimation& anim) = 0;
    virtual void setTexAnim(u32 idx, const TexturePatternAnimation& anim) = 0;
    virtual void setShuAnim(u32 idx, const ShaderParamAnimation& anim) = 0;
    virtual void setVisAnim(u32 idx, const VisibilityAnimation& anim) = 0;
    virtual void setShaAnim(u32 idx, const ShapeAnimation& anim) = 0;
    virtual const SkeletalAnimation** getSklAnims() const = 0;
    virtual const TexturePatternAnimation** getTexAnims() const = 0;
    virtual const ShaderParamAnimation** getShuAnims() const = 0;
    virtual const VisibilityAnimation** getVisAnims() const = 0;
    virtual const ShapeAnimation** getShaAnims() const = 0;

    s32 _20;
    s32 _24;
};

class RenderObjLayer : public RenderObjLayerBase // size: 0x478
{
public:
    RenderObjLayer();
    virtual ~RenderObjLayer();

    u32 getRenderStepNum() const override;
    void getRenderStepName(sead::SafeString* name, s32 idx) const override;
    void doInitialize(sead::Heap* heap) override;
    u32 vf54() override;
    void vf64(s32) override;

    // ...

    u8 _42C[0x478 - 0x42C];
};
