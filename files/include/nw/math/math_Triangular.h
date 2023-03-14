#ifndef NW_MATH_TRIANGULAR_H_
#define NW_MATH_TRIANGULAR_H_

#include <nw/math/math_Constant.h>

namespace nw { namespace math { namespace internal {

struct SinCosSample
{
    f32 sin_val;
    f32 sin_delta;
    f32 cos_val;
    f32 cos_delta;
};

extern const SinCosSample gSinCosTbl[256 + 1];

} } } // namespace nw::math::internal

namespace nw { namespace math {

#define NW_MATH_RAD_TO_IDX(rad)  (static_cast<u32>(static_cast<s64>((rad) * (::nw::math::I_HALF_ROUND_IDX / ::nw::math::F_PI))))
#define NW_MATH_DEG_TO_IDX(deg)  (static_cast<u32>(static_cast<s64>((deg) * (::nw::math::I_HALF_ROUND_IDX / 180.0f))))
#define NW_MATH_DEG_TO_RAD(deg)  ((deg) * (::nw::math::F_PI / 180.0f))
#define NW_MATH_RAD_TO_DEG(rad)  ((rad) * (180.0f / ::nw::math::F_PI))
#define NW_MATH_IDX_TO_RAD(idx)  ((idx) * (::nw::math::F_PI / ::nw::math::I_HALF_ROUND_IDX))
#define NW_MATH_IDX_TO_DEG(idx)  ((idx) * (180.0f / ::nw::math::I_HALF_ROUND_IDX))

inline f32 RadToDeg(f32 rad)
{
    return rad * (180.0f / F_PI);
}

inline f32 DegToRad(f32 deg)
{
    return deg * (F_PI / 180.0f);
}

inline f32 SinIdx(u32 idx)
{
    u32 index = (idx >> 24) & 0xff;
    u32 rest = idx & 0xffffff;

    return internal::gSinCosTbl[index].sin_val + internal::gSinCosTbl[index].sin_delta * rest / 0x1000000;
}

inline f32 CosIdx(u32 idx)
{
    u32 index = (idx >> 24) & 0xff;
    u32 rest = idx & 0xffffff;

    return internal::gSinCosTbl[index].cos_val + internal::gSinCosTbl[index].cos_delta * rest / 0x1000000;
}

inline void SinCosIdx(f32* pSin, f32* pCos, u32 idx)
{
    u32 index = (idx >> 24) & 0xff;
    f32 rest = static_cast<f32>(idx & 0xffffff) / 0x1000000;
    const internal::SinCosSample* table = &internal::gSinCosTbl[index];

    *pSin = table->sin_val + table->sin_delta * rest;
    *pCos = table->cos_val + table->cos_delta * rest;
}

inline f32 TanIdx(u32 idx)
{
    u32 index = (idx >> 24) & 0xff;
    f32 rest = static_cast<f32>(idx & 0xffffff) / 0x1000000;
    const internal::SinCosSample* table = &internal::gSinCosTbl[index];

    return (table->sin_val + table->sin_delta * rest) / (table->cos_val + table->cos_delta * rest);
}

inline f32 SinRad(f32 rad)
{
    return SinIdx(NW_MATH_RAD_TO_IDX(rad));
}

inline f32 CosRad(f32 rad)
{
    return CosIdx(NW_MATH_RAD_TO_IDX(rad));
}

inline void SinCosRad(f32* pSin, f32* pCos, f32 rad)
{
    SinCosIdx(pSin, pCos, NW_MATH_RAD_TO_IDX(rad));
}

inline f32 TanRad(f32 rad)
{
    return TanIdx(NW_MATH_RAD_TO_IDX(rad));
}

inline f32 SinDeg(f32 deg)
{
    return SinIdx(NW_MATH_DEG_TO_IDX(deg));
}

inline f32 CosDeg(f32 deg)
{
    return CosIdx(NW_MATH_DEG_TO_IDX(deg));
}

inline void SinCosDeg(f32* pSin, f32* pCos, f32 deg)
{
    SinCosIdx(pSin, pCos, NW_MATH_DEG_TO_IDX(deg));
}

inline f32 TanDeg(f32 deg)
{
    return TanIdx(NW_MATH_DEG_TO_IDX(deg));
}

} } // namespace nw::math

#endif // NW_MATH_TRIANGULAR_H_
