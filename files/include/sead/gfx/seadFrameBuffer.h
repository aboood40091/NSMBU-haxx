#ifndef SEAD_FRAME_BUFFER_H_
#define SEAD_FRAME_BUFFER_H_

#include <gfx/seadColor.h>
#include <math/seadBoundBox.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace sead {

class LogicalFrameBuffer
{
    SEAD_RTTI_BASE(LogicalFrameBuffer)

public:
    LogicalFrameBuffer(const Vector2f& virtual_size, const BoundBox2f& physical_area)
        : mVirtualSize(virtual_size)
        , mPhysicalArea(physical_area)
    {
    }

    LogicalFrameBuffer(const Vector2f& virtual_size, f32 physical_x, f32 physical_y, f32 physical_w, f32 physical_h)
        : mVirtualSize(virtual_size)
        , mPhysicalArea(physical_x, physical_y, physical_x + physical_w, physical_y + physical_h)
    {
    }

    LogicalFrameBuffer(const Vector2f& virtual_size, f32 physical_x, f32 physical_y, u32 physical_w, u32 physical_h)
        : mVirtualSize(virtual_size)
        , mPhysicalArea(physical_x, physical_y, physical_x + physical_w, physical_y + physical_h)
    {
    }

    virtual ~LogicalFrameBuffer()
    {
    }

    const Vector2f& getVirtualSize() const
    {
        return mVirtualSize;
    }

    const BoundBox2f& getPhysicalArea() const
    {
        return mPhysicalArea;
    }

    void setVirtualSize(const Vector2f& virtual_size)
    {
        mVirtualSize = virtual_size;
    }

    void setPhysicalArea(const BoundBox2f& ph_size)
    {
        mPhysicalArea.set(ph_size.getMin(), ph_size.getMax());
    }

    void setPhysicalArea(f32 x, f32 y, f32 w, f32 h)
    {
        mPhysicalArea.set(x, y, x + w, y + h);
    }

    void setPhysicalArea(f32 x, f32 y, u32 w, u32 h)
    {
        mPhysicalArea.set(x, y, x + w, y + h);
    }

protected:
    Vector2f mVirtualSize;
    BoundBox2f mPhysicalArea;
};
#ifdef cafe
static_assert(sizeof(LogicalFrameBuffer) == 0x1C, "sead::LogicalFrameBuffer size mismatch");
#endif // cafe

class DisplayBuffer;

class FrameBuffer : public LogicalFrameBuffer
{
    SEAD_RTTI_OVERRIDE(FrameBuffer, LogicalFrameBuffer)

public:
    FrameBuffer(const Vector2f& virtual_size, const BoundBox2f& physical_area)
        : LogicalFrameBuffer(virtual_size, physical_area)
    {
    }

    FrameBuffer(const Vector2f& virtual_size, f32 physical_x, f32 physical_y, f32 physical_w, f32 physical_h)
        : LogicalFrameBuffer(virtual_size, physical_x, physical_y, physical_w, physical_h)
    {
    }

    FrameBuffer(const Vector2f& virtual_size, f32 physical_x, f32 physical_y, u32 physical_w, u32 physical_h)
        : LogicalFrameBuffer(virtual_size, physical_x, physical_y, physical_w, physical_h)
    {
    }

    virtual void copyToDisplayBuffer(const DisplayBuffer* display_buffer) const
    {
    }

    virtual void clear(u32 clr_flag, const Color4f& color, f32 depth, u32 stencil) const = 0;
    virtual void clearMRT(u32 target, const Color4f& color) const;
    virtual void bindImpl_() const = 0;

    void bind() const;
};
#ifdef cafe
static_assert(sizeof(FrameBuffer) == 0x1C, "sead::FrameBuffer size mismatch");
#endif // cafe

}  // namespace sead

#endif // SEAD_FRAME_BUFFER_H_
