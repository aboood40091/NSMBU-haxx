#ifndef NW_MATH_VECTOR2_H_
#define NW_MATH_VECTOR2_H_

#include <cstring>
#include <nw/math/math_Config.h>
#include <nw/math/math_Arithmetic.h>

namespace nw { namespace math {

struct VEC2;

namespace internal { namespace standard {

    VEC2* VEC2Maximize(VEC2* pOut, const VEC2* p1, const VEC2* p2);
    VEC2* VEC2Minimize(VEC2* pOut, const VEC2* p1, const VEC2* p2);

} } // namespace internal::standard

#if defined(NW_MATH_ENABLE_INTRINSICS)

namespace internal { namespace intrinsics {

    VEC2* VEC2Maximize(VEC2* pOut, const VEC2* p1, const VEC2* p2);
    VEC2* VEC2Minimize(VEC2* pOut, const VEC2* p1, const VEC2* p2);

} } // namespace internal::intrinsics

#endif // NW_MATH_ENABLE_INTRINSICS

NW_MATH_INLINE bool VEC2IsZero(const VEC2* p);

NW_MATH_INLINE VEC2* VEC2Lerp(VEC2* pOut, const VEC2* p1, const VEC2* p2, f32 t);
NW_MATH_INLINE f32 VEC2Dot(const VEC2* p1, const VEC2* p2);
NW_MATH_INLINE VEC2* VEC2Maximize(VEC2* pOut, const VEC2* p1, const VEC2* p2);
NW_MATH_INLINE VEC2* VEC2Minimize(VEC2* pOut, const VEC2* p1, const VEC2* p2);
/* NW_MATH_INLINE */ extern VEC2* VEC2Normalize(VEC2* pOut, const VEC2* p);
/* NW_MATH_INLINE */ extern VEC2* VEC2FastNormalize(VEC2* pOut, const VEC2* p);
/* NW_MATH_INLINE */ extern VEC2* VEC2SafeNormalize(VEC2* pOut, const VEC2* p, const VEC2& alt);
/* NW_MATH_INLINE */ extern VEC2* VEC2FastSafeNormalize(VEC2* pOut, const VEC2* p, const VEC2& alt);
NW_MATH_INLINE f32 VEC2DistSq(const VEC2* p1, const VEC2* p2);

struct VEC2_
{
    f32 x;
    f32 y;
};

struct VEC2 : public VEC2_
{
public:
    static const int DIMENSION = 2;

    static const VEC2& Zero()
    {
        static const VEC2 zero(0.0f, 0.0f);

        return zero;
    }

    typedef VEC2 self_type;
    typedef f32  value_type;
public:
    VEC2() {}
    explicit VEC2(const f32* p) { x = p[0]; y = p[1]; }
    explicit VEC2(const VEC2_& v) { x = v.x; y = v.y; }
    VEC2(f32 fx, f32 fy) { x = fx; y = fy; }

    operator f32*() { return &x; }
    operator const f32*() const { return &x; }

    f32* ToF32() { return &x; }
    const f32* ToF32() const { return &x; }

    template <typename ToPtr>
    ToPtr Cast()
    {
        return reinterpret_cast<ToPtr>( this );
    }

    template <typename ToPtr>
    ToPtr Cast() const
    {
        return reinterpret_cast<ToPtr>( this );
    }

    self_type& operator += (const self_type& rhs) { x += rhs.x; y += rhs.y; return *this; }
    self_type& operator -= (const self_type& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
    self_type& operator *= (f32 f) { x *= f; y *= f; return *this; }
    self_type& operator /= (f32 f) { f32 r = 1.f / f; x *= r; y *= r; return *this; }

    self_type operator + () const { return *this; }
    self_type operator - () const { return self_type(-x, -y); }

    self_type operator + (const self_type& rhs) const { return self_type(x + rhs.x, y + rhs.y); }
    self_type operator - (const self_type& rhs) const { return self_type(x - rhs.x, y - rhs.y); }
    self_type operator * (f32 f) const { return self_type(f * x, f * y); }
    self_type operator / (f32 f) const { f32 r = 1.f / f; return self_type(r * x, r * y); }

    self_type& Lerp(const VEC2& lhs, const VEC2& rhs, f32 t)
    {
        return *VEC2Lerp(this, &lhs, &rhs, t);
    }

    f32 Dot(const VEC2& vec) const
    {
        return VEC2Dot(this, &vec);
    }

    f32 LengthSquare() const { return x * x + y * y; }
    f32 Length() const { return FSqrt(this->x * this->x + this->y * this->y); }

    self_type& Normalize()
    {
        return *VEC2Normalize(this, this);
    }

    self_type& SetNormalize(const VEC2& src)
    {
        return *VEC2Normalize(this, &src);
    }

    self_type& SafeNormalize(const VEC2& alt)
    {
        return *VEC2SafeNormalize(this, this, alt);
    }

    self_type& SetSafeNormalize(const VEC2& src, const VEC2& alt)
    {
        return *VEC2SafeNormalize(this, &src, alt);
    }

    f32 DistanceSquare(const VEC2& vec)
    {
        return VEC2DistSq(this, &vec);
    }

    self_type& SetMaximize(const VEC2& lhs, const VEC2& rhs)
    {
        return *VEC2Maximize(this, &lhs, &rhs);
    }

    self_type& SetMinimize(const VEC2& lhs, const VEC2& rhs)
    {
        return *VEC2Minimize(this, &lhs, &rhs);
    }

    void Set(f32 fx, f32 fy) { x = fx; y = fy; }

    bool operator == (const self_type& rhs) const { return x == rhs.x && y == rhs.y; }
    bool operator != (const self_type& rhs) const { return x != rhs.x || y != rhs.y; }

    bool IsZero() const { return VEC2IsZero(this); }
};

typedef struct VEC2 Vector2;

namespace internal { namespace standard {

NW_INLINE VEC2*
VEC2Add(VEC2* pOut, const VEC2* p1, const VEC2* p2)
{
    pOut->x = p1->x + p2->x; pOut->y = p1->y + p2->y;
    return pOut;
}

NW_INLINE VEC2*
VEC2Sub(VEC2* pOut, const VEC2* p1, const VEC2* p2)
{
    pOut->x = p1->x - p2->x; pOut->y = p1->y - p2->y;
    return pOut;
}

NW_INLINE VEC2*
VEC2Scale(VEC2* pOut, const VEC2* p, f32 scale)
{
    pOut->x = p->x * scale; pOut->y = p->y * scale;
    return pOut;
}

NW_INLINE VEC2*
VEC2Lerp(VEC2* pOut, const VEC2* p1, const VEC2* p2, f32 t)
{
    // (1-t)*p1 + t*p2
    pOut->x = p1->x + t * (p2->x - p1->x);
    pOut->y = p1->y + t * (p2->y - p1->y);
    return pOut;
}

NW_INLINE f32
VEC2Dot(const VEC2* p1, const VEC2* p2)
{
    return p1->x * p2->x + p1->y * p2->y;
}

NW_INLINE f32
VEC2LenSq(const VEC2* p)
{
    return p->x * p->x + p->y * p->y;
}

NW_INLINE f32
VEC2DistSq(const VEC2* p1, const VEC2* p2)
{
    VEC2 tmp;
    return standard::VEC2LenSq(VEC2Sub(&tmp, p1, p2));
}

} } // namespace internal::standard

#if defined(NW_MATH_ENABLE_INTRINSICS)

namespace internal { namespace intrinsics {

NW_INLINE VEC2*
VEC2Add(VEC2* pOut, const VEC2* p1, const VEC2* p2)
{
    tof32x2(pOut->x) = __PS_ADD(tof32x2(p1->x), tof32x2(p2->x));

    return pOut;
}

NW_INLINE VEC2*
VEC2Sub(VEC2* pOut, const VEC2* p1, const VEC2* p2)
{
    tof32x2(pOut->x) = __PS_SUB(tof32x2(p1->x), tof32x2(p2->x));

    return pOut;
}

NW_INLINE VEC2*
VEC2Scale(VEC2* pOut, const VEC2* p, f32 scale)
{
    tof32x2(pOut->x) = __PS_MULS0F(tof32x2(p->x), scale);

    return pOut;
}

NW_INLINE VEC2*
VEC2Lerp(VEC2* pOut, const VEC2* p1, const VEC2* p2, f32 t)
{
    // (1-t)*p1 + t*p2

    f32x2 tt = __PS_FDUP(t);
    f32x2 f0 = tof32x2(p1->x);
    f0 = __PS_NMSUB(f0, tt, f0);
    tof32x2(pOut->x) = __PS_MADD(tof32x2(p2->x), tt, f0);

    return pOut;
}

NW_INLINE f32
VEC2Dot(const VEC2* p1, const VEC2* p2)
{
    f32x2 f0 = __PS_MUL(tof32x2(p1->x), tof32x2(p2->x));
    f0 = __PS_SUM0(f0, f0, f0);

    return f0[0];
}

NW_INLINE f32
VEC2LenSq(const VEC2* p)
{
    f32x2 f0 = tof32x2(p->x);
    f0 =__PS_MUL(f0, f0);
    f0 = __PS_SUM0(f0, f0, f0);

    return f0[0];
}

NW_INLINE f32
VEC2DistSq(const VEC2* p1, const VEC2* p2)
{
    f32x2 f0 = __PS_SUB(tof32x2(p1->x), tof32x2(p2->x));
    f0 =__PS_MUL(f0, f0);
    f0 = __PS_SUM0(f0, f0, f0);

    return f0[0];
}

} } // namespace internal::intrinsics

#endif // NW_MATH_ENABLE_INTRINSICS

inline VEC2*
VEC2Add(VEC2* pOut, const VEC2* p1, const VEC2* p2)
{
    return NW_MATH_IMPL_NS::VEC2Add(pOut, p1, p2);
}

inline VEC2*
VEC2Sub(VEC2* pOut, const VEC2* p1, const VEC2* p2)
{
    return NW_MATH_IMPL_NS::VEC2Sub(pOut, p1, p2);
}

inline VEC2*
VEC2Scale(VEC2* pOut, const VEC2* p, f32 scale)
{
    return NW_MATH_IMPL_NS::VEC2Scale(pOut, p, scale);
}

inline VEC2*
VEC2Lerp(VEC2* pOut, const VEC2* p1, const VEC2* p2, f32 t)
{
    return NW_MATH_IMPL_NS::VEC2Lerp(pOut, p1, p2, t);
}

inline f32
VEC2Dot(const VEC2* p1, const VEC2* p2)
{
    return NW_MATH_IMPL_NS::VEC2Dot(p1, p2);
}

inline f32
VEC2LenSq(const VEC2* p)
{
    return internal::standard::VEC2LenSq(p);
}

inline f32
VEC2Len(const VEC2* p) { return FSqrt(p->x * p->x + p->y * p->y); }

inline f32
VEC2DistSq(const VEC2* p1, const VEC2* p2)
{
    return NW_MATH_IMPL_NS::VEC2DistSq(p1, p2);
}

inline VEC2
operator * (f32 f, const VEC2& rhs) { return VEC2(f * rhs.x, f * rhs.y); }

} } // namespace nw::math

#if defined(NW_MATH_AS_INLINE)

namespace nw { namespace math {

namespace internal { namespace standard {

NW_MATH_INLINE VEC2*
VEC2Maximize(VEC2* pOut, const VEC2* p1, const VEC2* p2)
{
    pOut->x = (p1->x > p2->x) ? p1->x : p2->x;
    pOut->y = (p1->y > p2->y) ? p1->y : p2->y;

    return pOut;
}

NW_MATH_INLINE VEC2*
VEC2Minimize(VEC2* pOut, const VEC2* p1, const VEC2* p2)
{
    pOut->x = (p1->x < p2->x) ? p1->x : p2->x;
    pOut->y = (p1->y < p2->y) ? p1->y : p2->y;

    return pOut;
}

} } // namespace internal::standard

#if defined(NW_MATH_ENABLE_INTRINSICS)

namespace internal { namespace intrinsics {

NW_MATH_INLINE VEC2*
VEC2Maximize(VEC2* pOut, const VEC2* p1, const VEC2* p2)
{
    f32x2 f0 = tof32x2(p1->x);
    f32x2 f1 = tof32x2(p2->x);
    tof32x2(pOut->x) = __PS_SEL(__PS_SUB(f0, f1), f0, f1);

    return pOut;
}

NW_MATH_INLINE VEC2*
VEC2Minimize(VEC2* pOut, const VEC2* p1, const VEC2* p2)
{
    f32x2 f0 = tof32x2(p1->x);
    f32x2 f1 = tof32x2(p2->x);
    tof32x2(pOut->x) = __PS_SEL(__PS_SUB(f1, f0), f0, f1);

    return pOut;
}

} } // namespace internal::intrinsics

#endif // NW_MATH_ENABLE_INTRINSICS

NW_MATH_INLINE bool
VEC2IsZero(const VEC2* p)
{
    return p->x == 0.f && p->y == 0.f;
}

NW_MATH_INLINE VEC2*
VEC2Maximize(VEC2* pOut, const VEC2* p1, const VEC2* p2)
{
    return NW_MATH_IMPL_NS::VEC2Maximize(pOut, p1, p2);
}

NW_MATH_INLINE VEC2*
VEC2Minimize(VEC2* pOut, const VEC2* p1, const VEC2* p2)
{
    return NW_MATH_IMPL_NS::VEC2Minimize(pOut, p1, p2);
}

// NW_MATH_INLINE VEC2*
// VEC2Normalize(VEC2* pOut, const VEC2* p)
// {
//     (void)VEC2Scale(pOut, p, FrSqrt(p->x * p->x + p->y * p->y));
//
//     return pOut;
// }

// NW_MATH_INLINE VEC2*
// VEC2FastNormalize(VEC2* pOut, const VEC2* p)
// {
//     (void)VEC2Scale(pOut, p, FrFastSqrt(p->x * p->x + p->y * p->y));
//
//     return pOut;
// }

// NW_MATH_INLINE VEC2*
// VEC2SafeNormalize(VEC2* pOut, const VEC2* p, const VEC2& alt)
// {
//     f32 mag = (p->x * p->x) + (p->y * p->y);
//
//     if (mag == 0 /* || mag == F_INF || isnan(mag) */)
//     {
//         *pOut = alt;
//
//         return pOut;
//     }
//
//     (void)VEC2Scale(pOut, p, FrSqrt(mag));
//
//     return pOut;
// }

// NW_MATH_INLINE VEC2*
// VEC2FastSafeNormalize(VEC2* pOut, const VEC2* p, const VEC2& alt)
// {
//     f32 mag = (p->x * p->x) + (p->y * p->y);
//
//     if (mag == 0 /* || mag == F_INF || isnan(mag) */)
//     {
//         *pOut = alt;
//
//         return pOut;
//     }
//
//     (void)VEC2Scale(pOut, p, FrFastSqrt(mag));
//
//     return pOut;
// }

} } // namespace nw::math

#endif

namespace nw { namespace math {

inline bool VEC2IsZero(const VEC2& v){ return VEC2IsZero( &v ); }
inline VEC2* VEC2Add(VEC2* pOut, const VEC2& p1, const VEC2& p2) { return VEC2Add(pOut, &p1, &p2); }
inline VEC2* VEC2Sub(VEC2* pOut, const VEC2& v1, const VEC2& v2) { return VEC2Sub(pOut, &v1, &v2); }
inline VEC2* VEC2Scale(VEC2* pOut, const VEC2& v, f32 scale) { return VEC2Scale(pOut, &v, scale); }
inline VEC2* VEC2Lerp(VEC2* pOut, const VEC2& v1, const VEC2& v2, f32 t) { return VEC2Lerp(pOut, &v1, &v2, t); }
inline f32 VEC2Dot(const VEC2& v1, const VEC2& v2) { return VEC2Dot(&v1, &v2); }
inline f32 VEC2LenSq(const VEC2& v) { return VEC2LenSq( &v ); }
inline f32 VEC2Len(const VEC2& v) { return VEC2Len( &v ); }
inline f32 VEC2DistSq(const VEC2& v1, const VEC2& v2) { return VEC2DistSq( &v1, &v2 ); }

inline VEC2* VEC2Maximize(VEC2* pOut, const VEC2& v1, const VEC2& v2) { return VEC2Maximize( pOut, &v1, &v2 ); }
inline VEC2* VEC2Minimize(VEC2* pOut, const VEC2& v1, const VEC2& v2) { return VEC2Minimize( pOut, &v1, &v2 ); }
inline VEC2* VEC2Normalize(VEC2* pOut, const VEC2& v) { return VEC2Normalize( pOut, &v ); }
inline VEC2* VEC2FastNormalize(VEC2* pOut, const VEC2& v) { return VEC2FastNormalize( pOut, &v ); }
inline VEC2* VEC2SafeNormalize(VEC2* pOut, const VEC2& v, const VEC2& alt) { return VEC2SafeNormalize( pOut, &v, alt ); }
inline VEC2* VEC2FastSafeNormalize(VEC2* pOut, const VEC2& v, const VEC2& alt) { return VEC2FastSafeNormalize( pOut, &v, alt ); }

} } // namespace nw::math

#endif
