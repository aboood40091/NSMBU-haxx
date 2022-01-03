#pragma once

#include <util/vec.h>

class BgRenderer
{
public:
    // ...
    void scheduleTileForDrawing(u32 layer, const Vec3& position, u16 tile);
    void scheduleTileForDrawingHaxx(u32 layer, const Vec3& position, u16 tile);
    // ...
};
