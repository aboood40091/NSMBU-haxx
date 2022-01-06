#ifndef G3D_FND_GFXBUFFER_H_
#define G3D_FND_GFXBUFFER_H_

#include <types.h>

namespace nw { namespace g3d { namespace fnd {

struct GfxBuffer_t
{
    void* data;
    u32 size;

    u8 _8[0xE - 0x8];

    u16 numBuffers;

    u8 _10[0x14 - 0x10];
};
static_assert(sizeof(GfxBuffer_t) == 0x14, "nw::g3d::fnd::GfxBuffer_t size mismatch");

class GfxBuffer : public GfxBuffer_t
{
public:
    void* GetData(s32 idx = 0);
    const void* GetData(s32 idx = 0) const;

    void DCFlush(s32 idx = 0) const;

    void SetData(void* data, u32 size, s32 numBuffers);
};

} } }

#endif // G3D_FND_GFXBUFFER_H_
