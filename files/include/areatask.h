#pragma once

#include <agl/lyr/aglRenderInfo.h>

class AreaTask
{
public:
    void readHaxxOptions();
    void drawLayer3D(const agl::lyr::RenderInfo& renderInfo);
    void debugDraw(const agl::lyr::RenderInfo& renderInfo);

    static AreaTask* instance;

    u8 _0[0x72C];
    u32 wrapFlag;
    u8 _730[0x4B4];
};
