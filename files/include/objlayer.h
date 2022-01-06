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

        Vec3 position; // I think. Precisely used for z ordering.
    };

public:
    ObjLayer();
    virtual ~ObjLayer();

    virtual void vf64(s32) { }

    void setParentRenderer(ObjLayerRenderer* renderer);

    // ...

    ObjLayerRenderer* parentRenderer;
    s32 parentRendererLayerIdx;
    void* _428; // Something containing nw::g3d::ViewVolume
};
static_assert(sizeof(ObjLayer) == 0x42C, "ObjLayer size mismatch");
