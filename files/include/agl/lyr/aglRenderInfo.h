#pragma once

#include <agl/lyr/aglRenderer.h>

#include <gfx/seadCamera.h>
#include <gfx/seadFrameBuffer.h>
#include <gfx/seadProjection.h>
#include <gfx/seadViewport.h>

namespace agl {

class DisplayList;

namespace lyr {

class RenderInfo
{
public:
    s32 renderStepIdx;
    DisplayType displayType;
    sead::FrameBuffer* frameBuffer;
    s32 layerIdx; // in agl::Renderer's layer buffer
    Layer* parentLayer;
    sead::Camera* camera;
    sead::Projection* projection;
    sead::Viewport* viewport;
    DisplayList* displayList;
    bool _24;
};

} }
