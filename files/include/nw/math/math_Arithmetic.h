#ifndef NW_MATH_ARITHMETIC_H_
#define NW_MATH_ARITHMETIC_H_

#include <nw/math/math_Config.h>
#include <nw/math/math_Constant.h>

#include <cmath>

namespace nw { namespace math {

inline f32
FSelect(f32 cond, f32 ifPos, f32 ifNeg)
{
    f32 ret;
    ret = (cond >= 0) ? ifPos: ifNeg;
    return ret;
}

inline f32
FAbs(f32 x)
{
    f32 ret;
    ret = ::std::fabs(x);
    return ret;
}

inline f32
FNAbs(f32 x)
{
    f32 ret;
    ret = - FAbs(x);
    return ret;
}

inline f32
FCopySign(f32 abs, f32 sign)
{
    f32 pos = FAbs(abs);
    f32 neg = FNAbs(abs);

    return FSelect(sign, pos, neg);
}

inline f32
FExp(f32 x)
{
    return ::std::exp(x);
}

inline f32
FLog(f32 x)
{
    return ::std::log(x);
}

inline f32
FLog10(f32 x)
{
    return ::std::log10(x);
}

inline f32
FMod(f32 x, f32 y)
{
    return ::std::fmod(x, y);
}

inline f32
FModf(f32 x, f32* y)
{
    return ::std::modf(x, y);
}

inline f32
FCeil(f32 x)
{
    return ::std::ceil(x);
}

inline f32
FFloor(f32 x)
{
    return ::std::floor(x);
}

inline s16
F32ToS16(f32 x)
{
    return s16(x);

}

inline u16
F32ToU16(f32 x)
{
    return u16(x);
}

inline f32
U16ToF32(u16 x)
{
    return f32(x);
}

inline f32
S16ToF32(s16 x)
{
    return f32(x);
}

inline f32
FInv(f32 x)
{
    f32 ix;
    ix = 1.0f / x;
    return ix;
}

inline f32
FSqrt(f32 x)
{
    return ::std::sqrt(x);
}

inline f32
FCbrt(f32 x)
{
    return ::std::pow(x, 1/3.f);
}

inline f32
Reciprocal(f32 x)
{
    return 1.0f / x;
}

inline f32
Hermite(f32 v0, f32 t0, f32 v1, f32 t1, f32 s)
{
    f32 SS   = s * s;
    f32 SS_S = s * s - s;
    f32 b1 = SS_S * s - SS_S;
    f32 b2 = SS_S * s;
    f32 a2 = SS - 2.f * b2;

    return v0 - a2 * v0 + a2 * v1 + b1 * t0 + b2 * t1;
}

NW_FORCE_INLINE f32
Hermite(f32 v0, f32 t0, f32 v1, f32 t1, f32 p, f32 d)
{
    f32 inv_d = 1 / d;
    f32 s = p * inv_d;
    f32 s_1 = s - 1;
    return v0 + (v0 - v1) * (2 * s - 3) * s * s + s * s_1 * (s_1 * t0 + s * t1);
}

inline bool IsPwr2(int x) { return 0 == (x & (x - 1)); }

inline int Rightmost1(int x) { return x & (-x); }

inline int Rightmost0(int x) { return ~x & (x + 1); }

} } // namespace nw::math

#endif // NW_MATH_ARITHMETIC_H_
