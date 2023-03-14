#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadNamable.h>

class RenderMgr : public sead::IDisposer, public sead::INamable
{
public:
    RenderMgr(const sead::SafeString& name);
    virtual ~RenderMgr();

    void init(u32 num_layers_max, u32 num_nodes_max, u32 num_opa_buffers_max, u32 num_xlu_buffers_max, sead::Heap* heap);
    // ...

    u8 _18[0x4D4 - 0x18];
};
static_assert(sizeof(RenderMgr) == 0x4D4, "RenderMgr size mismatch");
