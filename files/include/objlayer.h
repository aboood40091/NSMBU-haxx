#pragma once

#include "util/mtx.h"
#include "layeragl.h"

class ObjLayerRenderer;

class ObjLayer : public LayerAgl // size: 0x42C
{
    SEAD_RTTI_OVERRIDE(ObjLayer, LayerAgl)

public:
    class Node : public LayerAgl::Node
    {
        SEAD_RTTI_OVERRIDE(Node, LayerAgl::Node)

    public:
        virtual void calcGPU(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, ObjLayerRenderer* renderer) = 0;
        virtual void updateView(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, ObjLayerRenderer* renderer) = 0;
        virtual void drawOpa(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, ObjLayerRenderer* renderer) = 0;
        virtual void drawXlu(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, ObjLayerRenderer* renderer) = 0;
        virtual void drawShadowOpa(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, ObjLayerRenderer* renderer) { }
        virtual void drawReflectionOpa(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, ObjLayerRenderer* renderer) { }
        virtual void drawReflectionXlu(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, ObjLayerRenderer* renderer) { }
        virtual bool hasShadow() const { return false; }
    };

public:
    ObjLayer();
    virtual ~ObjLayer();

    virtual void vf64(s32) { }

    void setParentRenderer(ObjLayerRenderer* renderer);

    // ...

    u8 _420[0x42C - 0x420];
};
