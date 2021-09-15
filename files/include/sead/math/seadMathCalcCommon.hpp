#pragma once

#include <math/cafe/seadMathCalcCommonCafe.h>

namespace sead {

template <>
inline s32
MathCalcCommon<s32>::abs(s32 t)
{
    return (t ^ t >> 31) - (t >> 31);
}

template <>
inline u32
MathCalcCommon<u32>::abs(u32 t)
{
    return t;
}

template <>
inline s32
MathCalcCommon<s32>::roundUpPow2(s32 val, s32 base)
{
    //SEAD_ASSERT_MSG(val >= 0 && (base - 1u & base) == 0, "illegal param[val:%d, base:%d]", val, base);
    return val + base - 1 & (u32)-base;
}

template <>
inline s32
MathCalcCommon<u32>::roundUpPow2(u32 val, s32 base)
{
    //SEAD_ASSERT_MSG((base - 1u & base) == 0, "illegal param[base:%d]", base);
    return val + base - 1 & (u32)-base;
}

template <typename T>
inline T
MathCalcCommon<T>::cos(T t)
{
    return std::cos(t);
}

template <typename T>
inline T
MathCalcCommon<T>::sin(T t)
{
    return std::sin(t);
}

template <typename T>
inline T
MathCalcCommon<T>::atan2(T y, T x)
{
    return std::atan2(y, x);
}

template <typename T>
inline T
MathCalcCommon<T>::sqrt(T x)
{
    return rsqrt(x) * x;
}

template <typename T>
inline T
MathCalcCommon<T>::rsqrt(T x)
{
    return MathCafe<T>::rsqrt(x);
}

} // namespace sead
