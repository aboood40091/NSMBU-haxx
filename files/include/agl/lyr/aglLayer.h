#pragma once

#include <gfx/seadCamera.h>
#include <gfx/seadProjection.h>
#include <heap/seadDisposer.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>

namespace agl { namespace lyr {

class DrawMethod;
class RenderInfo;

class Layer : public sead::IDisposer // size: 0x41C
{
public:
    Layer();
    virtual ~Layer();

    SEAD_RTTI_BASE(Layer)

    virtual u32 getRenderStepNum() const = 0;
    virtual void getRenderStepName(sead::SafeString* name, s32 idx) const = 0;
    virtual void doInitialize(sead::Heap* heap) { }
    virtual void vf3C() { }
    virtual void preDrawImpl(const RenderInfo& render_info) const { }
    virtual void postDrawImpl(const RenderInfo& render_info) const { }
    virtual u32 vf54() { return 0; }
    virtual u32 vf5C() { return 0; }

    DrawMethod* pushBackDrawMethod(u32 render_step_idx, DrawMethod* draw_method);
    DrawMethod* pushBackDrawMethod(DrawMethod* draw_method);
    // ...

    u8 _10[0x44 - 0x10];

    sead::Camera* renderCamera;
    sead::Projection* renderProjection;

    u8 _4c[0x90 - 0x4C];

    const char* name;     // This is not what the field actually is
                          // I just determined that it's unused and therefore am using it for myself

    u8 _94[0x41C - 0x94];
};
static_assert(sizeof(Layer) == 0x41C, "agl::lyr::Layer size mismatch");

} }
