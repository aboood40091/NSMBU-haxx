#ifndef EFT_UNIFORM_BLOCK_H_
#define EFT_UNIFORM_BLOCK_H_

#include <nw/eft/eft_typeDef.h>

namespace nw { namespace eft {

struct ViewUniformBlock
{
    nw::math::MTX44 viewMat;
    nw::math::MTX44 vpMat;
    nw::math::MTX44 bldMat;
    nw::math::VEC4  eyeVec;
    nw::math::VEC4  eyePos;
    nw::math::VEC4  depthBufferTexMat;
    nw::math::VEC4  frameBufferTexMat;
    nw::math::VEC4  viewParam;
};
static_assert(sizeof(ViewUniformBlock) == 0x110, "nw::eft::ViewUniformBlock size mismatch");

struct EmitterDynamicUniformBlock
{
    nw::math::VEC4  emitterColor0;
    nw::math::VEC4  emitterColor1;
};
static_assert(sizeof(EmitterDynamicUniformBlock) == 0x20, "nw::eft::EmitterDynamicUniformBlock size mismatch");

struct EmitterStaticUniformBlock
{
    nw::math::VEC4  uvScaleInit;
    nw::math::VEC4  rotBasis;
    nw::math::VEC4  shaderParam;
    nw::math::VEC4  _align256[(256 - 3 * sizeof(nw::math::VEC4)) / sizeof(nw::math::VEC4)];
};
static_assert(sizeof(EmitterStaticUniformBlock) == 0x100, "nw::eft::EmitterStaticUniformBlock size mismatch");

struct StripeVertexBuffer
{
    nw::math::VEC4  pos;
    nw::math::VEC4  outer;
    nw::math::VEC4  tex;
    nw::math::VEC4  dir;
};
static_assert(sizeof(StripeVertexBuffer) == 0x40, "nw::eft::StripeVertexBuffer size mismatch");

struct StripeUniformBlock
{
    nw::math::VEC4  stParam;
    nw::math::VEC4  uvScrollAnim;
    nw::math::VEC4  uvScaleRotAnim0;
    nw::math::VEC4  uvScaleRotAnim1;
    nw::math::VEC4  vtxColor0;
    nw::math::VEC4  vtxColor1;
    nw::math::MTX44 emitterMat;
};
static_assert(sizeof(StripeUniformBlock) == 0xA0, "nw::eft::StripeUniformBlock size mismatch");

} } // namespace nw::eft

#endif // EFT_UNIFORM_BLOCK_H_
