#pragma once

#include <gfx/seadFrameBuffer.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>

namespace agl {

class RenderBuffer : public sead::IDisposer, public sead::FrameBuffer
{
    SEAD_RTTI_OVERRIDE(RenderBuffer, sead::FrameBuffer)

public:
    RenderBuffer();
    RenderBuffer(const sead::Vector2f& virtual_size, f32 physical_x, f32 physical_y, f32 physical_w, f32 physical_h);
    virtual ~RenderBuffer();

    virtual void copyToDisplayBuffer(const sead::DisplayBuffer* display_buffer) const;
    virtual void clear(u32 clr_flag, const sead::Color4f& color, f32 depth, u32 stencil) const;
    virtual void bindImpl_() const;

    void* renderTargetColors[8]; // agl::RenderTarget<agl::RenderTargetColor>*[8]
    void* renderTargetDepth; // agl::RenderTarget<agl::RenderTargetDepth>*
};
static_assert(sizeof(RenderBuffer) == 0x50, "agl::RenderBuffer size mistmatch");

}
