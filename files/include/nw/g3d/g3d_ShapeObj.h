#ifndef G3D_SHAPEOBJ_H_
#define G3D_SHAPEOBJ_H_

#include "fnd/g3d_GfxBuffer.h"
#include "math/g3d_Mtx34.h"
#include "math/g3d_Vec3.h"

namespace nw { namespace g3d {

struct Sphere
{
    math::Vec3 center;
    f32 radius;
};

struct ShpBlock
{
    math::Mtx34 shpMtx;
    s32 weightNum;
    u8 pad[0x100 - 0x34];
};
static_assert(sizeof(ShpBlock) == 0x100, "nw::g3d::ShpBlock size mismatch");

class ShapeObj
{
public:
    u8 _0[0x4 - 0x0];

    u32 flags;
    u8 _8;
    bool multiView;
    u8 numShpBlocks;
    u8 numBuffersPerShpBlock;
    fnd::GfxBuffer* shpBlocks;

    u8 _10[0x28 - 0x10];
};
static_assert(sizeof(ShapeObj) == 0x28, "nw::g3d::ShapeObj size mismatch");

} }

#endif // G3D_SHAPEOBJ_H_
