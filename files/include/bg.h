#pragma once

#include "types.h"
#include "tiles.h"


class Bg
{
public:
    static u16* getTilePtr(u16 x, u16 y, u32 file, u8 layer, u32* blockIndexOut = nullptr);
    static u16* getTilePtrCurrentCdFile(u16 x, u16 y, u8 layer, u32* blockIndexOut = nullptr);

    static Bg* instance;
};
