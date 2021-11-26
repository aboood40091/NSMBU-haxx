#pragma once

#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <thread/seadCriticalSection.h>

#include "layer.h"
#include "renderbuffer.h"

namespace agl { namespace lyr {

enum DisplayType
{
    cDisplayType_Top_TV     = 0,
    cDisplayType_Bottom_DRC = 1,
    cDisplayType_Max        = 2,
    cDisplayType_Invalid    = 0xFFFFFFFF
};

class Renderer
{
    SEAD_SINGLETON_DISPOSER(Renderer)

public:
    Renderer();
    virtual ~Renderer();

    bool draw(DisplayType display_type) const;
    bool drawTVHaxx(DisplayType display_type) const;
    bool drawDRCHaxx(DisplayType display_type) const;

    // ...

    u32 isDisplayList;
    u32 multiSampleType; // agl::MultiSampleType
    u8 renderDisplays[cDisplayType_Max][0x6C4]; // agl::lyr::RenderDisplay[cDisplayType_Max]
    agl::RenderBuffer* renderBuffers[cDisplayType_Max];
    sead::Buffer<agl::lyr::Layer*> layers;
    mutable sead::BitFlag16 flags;
    f32 _DB4;
    u8 _DB8[16];
    sead::CriticalSection cs;
    u8 jobQueues[2][0x64]; // sead::FixedSizeJQ[2]
    sead::PtrArrayImpl renderDisplayJobs[cDisplayType_Max]; // sead::PtrArray<agl::lyr::RenderDisplay::Job>[cDisplayType_Max]
    u32 _EE4;
    u32 _EE8;
    s32 _EEC;
    void* debugController; // sead::Controller*
    f32 _EF4;
    sead::Vector2f _EF8;
    u32 _F00;
    u8 renderDLBuffer[0x58]; // agl::lyr::RenderDLBuffer
    u32 gpuCounter;
    u32 gpuCounterPeriod;
    u32 _F64;
    s32 colorBufferSwizzle;
    s32 depthBufferSwizzle;
    f32 _F70;
};
static_assert(sizeof(Renderer) == 0xF78, "agl::lyr::Renderer size mismatch");

} }
