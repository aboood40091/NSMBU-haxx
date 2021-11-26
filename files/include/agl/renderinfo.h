#pragma once

#include "types.h"

namespace sead {

class Camera;
class FrameBuffer;
class Projection;
class Viewport;

}

namespace agl {

class DisplayList;

namespace lyr {

class Layer;

class RenderInfo
{
public:
    u32 renderStepIdx;
    u32 displayType;
    sead::FrameBuffer* frameBuffer;
    u32 _C;
    Layer* parentLayer;
    sead::Camera* camera;
    sead::Projection* projection;
    sead::Viewport* viewport;
    DisplayList* displayList;
    bool _24;
};

} }
