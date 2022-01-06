#ifndef G3D_MODELOBJ_H_
#define G3D_MODELOBJ_H_

#include "g3d_ShapeObj.h"

namespace nw { namespace g3d {

class ModelObj
{
public:
    u8 _0[0x14 - 0x0];

    u16 numShapes;

    u8 _16[0x1C - 0x16];

    ShapeObj* shapes;

    u8 _20[0x34 - 0x20];
};
static_assert(sizeof(ModelObj) == 0x34, "nw::g3d::ModelObj size mismatch");

} }

#endif // G3D_MODELOBJ_H_
