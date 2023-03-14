#ifndef NW_MATH_CONFIG_H_
#define NW_MATH_CONFIG_H_

#include <nw/types.h>

#define NW_MATH_AS_INLINE
#define NW_MATH_INLINE inline

#if defined(NW_PLATFORM_CAFE) && (__GHS_VERSION_NUMBER >= 536)
  #define NW_MATH_ENABLE_INTRINSICS
  #define NW_MATH_USE_INTRINSICS
  #define NW_MATH_IMPL_NS ::nw::math::internal::intrinsics
#else
  #define NW_MATH_IMPL_NS ::nw::math::internal::standard
#endif

#if defined(NW_MATH_ENABLE_INTRINSICS)

namespace nw { namespace math { namespace internal {

inline f32x2& tof32x2(f32& x)
{
    return *reinterpret_cast<f32x2*>(&x);
}

inline const f32x2& tof32x2(const f32& x)
{
    return *reinterpret_cast<const f32x2*>(&x);
}

inline f32x2* tof32x2(f32* x)
{
    return reinterpret_cast<f32x2*>(x);
}

inline const f32x2* tof32x2(const f32* x)
{
    return reinterpret_cast<const f32x2*>(x);
}

} } } // namespace nw::math::internal

#endif // NW_MATH_ENABLE_INTRINSICS

#endif // NW_MATH_CONFIG_H_
