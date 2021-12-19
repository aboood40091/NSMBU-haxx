#pragma once

#include <cafe.h>

namespace agl {

typedef u32 TextureFormat;  // enum TextureFormat
typedef u32 TextureCompSel; // enum TextureCompSel

class TextureData
{
public:
    TextureData();
    virtual ~TextureData();

    void invalidateGPUCache();

    TextureFormat format;
    GX2Surface surface;
    u32 width;
    u32 height;
    u32 depth;
    u32 size;
    TextureCompSel compSel[4];
};
static_assert(sizeof(TextureData) == 0x9C, "agl::TextureData size mismatch");

}
