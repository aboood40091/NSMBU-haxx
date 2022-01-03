#pragma once

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <prim/seadNamable.h>

class ObjLayer;

struct ObjLayerRenderInfo
{
    ObjLayer* layer;
    Mtx34 viewMtx;
    Mtx44 projMtx;
    Mtx44* _74;
    void* _78; // Something containing nw::g3d::ViewVolume
    u32 _7C;
};
static_assert(sizeof(ObjLayerRenderInfo) == 0x80, "ObjLayerRenderInfo size mismatch");

class ObjLayerRenderer : public sead::IDisposer, public sead::INamable
{
public:
    ObjLayerRenderer(const sead::SafeString& name);
    virtual ~ObjLayerRenderer();

    void init(u32 num_layers_max, u32 num_nodes_max, u32 num_opa_buffers_max, u32 num_xlu_buffers_max, sead::Heap* heap);
    // ...

    u8 _18[0x4C4 - 0x18];
    sead::Buffer<ObjLayerRenderInfo> layerRenderInfos;
    u8 _4cc[0x4D4 - 0x4CC];
};
static_assert(sizeof(ObjLayerRenderer) == 0x4D4, "ObjLayerRenderer size mismatch");
