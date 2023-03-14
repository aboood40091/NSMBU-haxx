#pragma once

#include "util/mtx.h"
#include "layer.h"

class RenderMgr;

class RenderObj : public RenderObjBase
{
    SEAD_RTTI_OVERRIDE(RenderObj, RenderObjBase)

public:
    virtual void calcGPU(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderer) = 0;
    virtual void updateView(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderer) = 0;
    virtual void drawOpa(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderer) = 0;
    virtual void drawXlu(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderer) = 0;
    virtual void drawShadowOpa(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderer) { }
    virtual void drawReflectionOpa(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderer) { }
    virtual void drawReflectionXlu(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderer) { }
    virtual bool hasShadow() const { return false; }
};

class RenderObjLayerBase : public Layer // size: 0x42C
{
    SEAD_RTTI_OVERRIDE(RenderObjLayerBase, Layer)

public:
    RenderObjLayerBase();
    virtual ~RenderObjLayerBase();

    virtual void vf64(s32) { }

    void setParentRenderer(RenderMgr* renderer);

    // ...

    u8 _420[0x42C - 0x420];
};
