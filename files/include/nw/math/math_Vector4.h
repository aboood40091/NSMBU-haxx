#ifndef NW_MATH_VECTOR4_H_
#define NW_MATH_VECTOR4_H_

#include <cstring>
#include <nw/math/math_Config.h>

namespace nw { namespace math {

struct VEC4;

namespace internal { namespace standard {

    VEC4* VEC4Add(VEC4* pOut, const VEC4* p1, const VEC4* p2);
    VEC4* VEC4Sub(VEC4* pOut, const VEC4* p1, const VEC4* p2);
    VEC4* VEC4Scale(VEC4* pOut, const VEC4* p, f32 scale);
    VEC4* VEC4Lerp(VEC4* pOut, const VEC4* p1, const VEC4* p2, f32 t);
    f32 VEC4Dot(const VEC4* p1, const VEC4* p2);
    f32 VEC4LenSq(const VEC4* p);
    f32 VEC4DistSq(const VEC4* p1, const VEC4* p2);
    VEC4* VEC4Maximize(VEC4* pOut, const VEC4* p1, const VEC4* p2);
    VEC4* VEC4Minimize(VEC4* pOut, const VEC4* p1, const VEC4* p2);

} } // namespace internal::standard

#if defined(NW_MATH_ENABLE_INTRINSICS)

namespace internal { namespace intrinsics {

    VEC4* VEC4Add(VEC4* pOut, const VEC4* p1, const VEC4* p2);
    VEC4* VEC4Sub(VEC4* pOut, const VEC4* p1, const VEC4* p2);
    VEC4* VEC4Scale(VEC4* pOut, const VEC4* p, f32 scale);
    VEC4* VEC4Lerp(VEC4* pOut, const VEC4* p1, const VEC4* p2, f32 t);
    f32 VEC4Dot(const VEC4* p1, const VEC4* p2);
    f32 VEC4LenSq(const VEC4* p);
    f32 VEC4DistSq(const VEC4* p1, const VEC4* p2);
    VEC4* VEC4Maximize(VEC4* pOut, const VEC4* p1, const VEC4* p2);
    VEC4* VEC4Minimize(VEC4* pOut, const VEC4* p1, const VEC4* p2);

} } // namespace internal::intrinsics

#endif // NW_MATH_ENABLE_INTRINSICS

NW_MATH_INLINE bool VEC4IsZero(const VEC4* p);
NW_MATH_INLINE bool VEC4IsZeroWOne(const VEC4* p);
NW_MATH_INLINE VEC4* VEC4Add(VEC4* pOut, const VEC4* p1, const VEC4* p2);
NW_MATH_INLINE VEC4* VEC4Sub(VEC4* pOut, const VEC4* p1, const VEC4* p2);
NW_MATH_INLINE VEC4* VEC4Scale(VEC4* pOut, const VEC4* p, f32 scale);
NW_MATH_INLINE VEC4* VEC4Lerp(VEC4* pOut, const VEC4* p1, const VEC4* p2, f32 t);
NW_MATH_INLINE f32   VEC4Dot(const VEC4* p1, const VEC4* p2);
NW_MATH_INLINE f32   VEC4LenSq(const VEC4* p);
NW_MATH_INLINE f32   VEC4Len(const VEC4* p);
/* NW_MATH_INLINE */ extern VEC4* VEC4Normalize(VEC4* pOut, const VEC4* p);
/* NW_MATH_INLINE */ extern VEC4* VEC4FastNormalize(VEC4* pOut, const VEC4* p);
/* NW_MATH_INLINE */ extern VEC4* VEC4SafeNormalize(VEC4* pOut, const VEC4* p, const VEC4& alt);
/* NW_MATH_INLINE */ extern VEC4* VEC4FastSafeNormalize(VEC4* pOut, const VEC4* p, const VEC4& alt);
NW_MATH_INLINE f32   VEC4DistSq(const VEC4* p1, const VEC4* p2);
NW_MATH_INLINE VEC4* VEC4Maximize(VEC4* pOut, const VEC4* p1, const VEC4* p2);
NW_MATH_INLINE VEC4* VEC4Minimize(VEC4* pOut, const VEC4* p1, const VEC4* p2);

struct VEC4_
{
    f32 x;
    f32 y;
    f32 z;
    f32 w;
};

struct VEC4 : public VEC4_
{
public:
    static const int DIMENSION = 4;

    static const VEC4& Zero()
    {
        static const VEC4 zero(0.0f, 0.0f, 0.0f, 0.0f);

        return zero;
    }

    static const VEC4& ZeroWOne()
    {
        static const VEC4 zero(0.0f, 0.0f, 0.0f, 1.0f);

        return zero;
    }

    typedef VEC4 self_type;
    typedef f32  value_type;
public:
    VEC4() {}
    explicit VEC4(const f32* p) { x = p[0]; y = p[1]; z = p[2]; w = p[3]; }
    explicit VEC4(const VEC4_& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    VEC4(f32 fx, f32 fy, f32 fz, f32 fw) { x = fx; y = fy; z = fz; w = fw; }
    explicit VEC4(const VEC3& v) { x = v.x; y = v.y; z = v.z; w = 0.0f; }

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

    self_type& operator += (const self_type& rhs) { (void)VEC4Add(this, this, &rhs); return *this; }
    self_type& operator -= (const self_type& rhs) { (void)VEC4Sub(this, this, &rhs); return *this; }
    self_type& operator *= (f32 f) { (void)VEC4Scale(this, this, f); return *this; }
    self_type& operator /= (f32 f) { (void)VEC4Scale(this, this, 1/f); return *this; }

    self_type operator + () const { return *this; }
    self_type operator - () const { return self_type(-x, -y, -z, -w); }

    self_type operator + (const self_type& rhs) const { VEC4 tmp; (void)VEC4Add(&tmp, this, &rhs); return tmp; }
    self_type operator - (const self_type& rhs) const { VEC4 tmp; (void)VEC4Sub(&tmp, this, &rhs); return tmp; }
    self_type operator * (f32 f) const { VEC4 tmp; (void)VEC4Scale(&tmp, this, f); return tmp; }
    self_type operator / (f32 f) const { f32 r = 1.f / f; return operator*(r); }

    self_type& Lerp(const VEC4& lhs, const VEC4& rhs, f32 t)
    {
        return *VEC4Lerp(this, &lhs, &rhs, t);
    }

    f32 Dot(const VEC4& vec) const
    {
        return VEC4Dot(this, &vec);
    }

    f32 LengthSquare() const { return VEC4LenSq(this); }
    f32 Length() const { return VEC4Len(this); }

    self_type& Normalize()
    {
        return *VEC4Normalize(this, this);
    }

    self_type& SetNormalize(const VEC4& src)
    {
        return *VEC4Normalize(this, &src);
    }

    self_type& SafeNormalize(const VEC4& alt)
    {
        return *VEC4SafeNormalize(this, this, alt);
    }

    self_type& SetSafeNormalize(const VEC4& src, const VEC4& alt)
    {
        return *VEC4SafeNormalize(this, &src, alt);
    }

    f32 DistanceSquare(const VEC4& vec)
    {
        return VEC4DistSq(this, &vec);
    }

    self_type& SetMaximize(const VEC4& lhs, const VEC4& rhs)
    {
        return *VEC4Maximize(this, &lhs, &rhs);
    }

    self_type& SetMinimize(const VEC4& lhs, const VEC4& rhs)
    {
        return *VEC4Minimize(this, &lhs, &rhs);
    }

    NW_MATH_INLINE self_type& SetTransform(const MTX34& pM, const VEC4& src);
    self_type& Transform(const MTX34& pM) { return this->SetTransform(pM, *this); }

    NW_MATH_INLINE self_type& SetTransform(const MTX44& pM, const VEC4& src);
    self_type& Transform(const MTX44& pM) { return this->SetTransform(pM, *this); }

    void Set(f32 fx, f32 fy, f32 fz, f32 fw) { x = fx; y = fy; z = fz; w = fw; }

    bool operator == (const self_type& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w; }
    bool operator != (const self_type& rhs) const { return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w; }

    bool IsZero() const { return VEC4IsZero(this); }
    bool IsZeroWOne() const { return VEC4IsZeroWOne(this); }
};

typedef struct VEC4 Vector4;

inline VEC4
operator * (f32 f, const VEC4& rhs) { VEC4 tmp; (void)VEC4Scale(&tmp, &rhs, f); return tmp; }

} } // namespace nw::math

#if defined(NW_MATH_AS_INLINE)

namespace nw { namespace math {

namespace internal { namespace standard {

NW_MATH_INLINE VEC4*
VEC4Add(VEC4* pOut, const VEC4* p1, const VEC4* p2)
{
    pOut->x = p1->x + p2->x;
    pOut->y = p1->y + p2->y;
    pOut->z = p1->z + p2->z;
    pOut->w = p1->w + p2->w;

    return pOut;
}

NW_MATH_INLINE VEC4*
VEC4Sub(VEC4* pOut, const VEC4* p1, const VEC4* p2)
{
    pOut->x = p1->x - p2->x;
    pOut->y = p1->y - p2->y;
    pOut->z = p1->z - p2->z;
    pOut->w = p1->w - p2->w;

    return pOut;
}

NW_MATH_INLINE VEC4*
VEC4Scale(VEC4* pOut, const VEC4* p, f32 scale)
{
    pOut->x = scale * p->x;
    pOut->y = scale * p->y;
    pOut->z = scale * p->z;
    pOut->w = scale * p->w;

    return pOut;
}

NW_MATH_INLINE VEC4*
VEC4Lerp(VEC4* pOut, const VEC4* __restrict p1, const VEC4* __restrict p2, f32 t)
{
    // (1-t)*p1 + t*p2
    pOut->x = p1->x + t * (p2->x - p1->x);
    pOut->y = p1->y + t * (p2->y - p1->y);
    pOut->z = p1->z + t * (p2->z - p1->z);
    pOut->w = p1->w + t * (p2->w - p1->w);

    return pOut;
}

NW_MATH_INLINE f32
VEC4Dot(const VEC4* p1, const VEC4* p2)
{
    return p1->x * p2->x + p1->y * p2->y + p1->z * p2->z + p1->w * p2->w;
}

NW_MATH_INLINE f32
VEC4LenSq(const VEC4* __restrict p)
{
    return p->x * p->x + p->y * p->y + p->z * p->z + p->w * p->w;
}

NW_MATH_INLINE f32
VEC4DistSq(const VEC4* p1, const VEC4* p2)
{
    VEC4 tmp;
    return standard::VEC4LenSq(standard::VEC4Sub(&tmp, p1, p2));
}

NW_MATH_INLINE VEC4*
VEC4Maximize(VEC4* pOut, const VEC4* p1, const VEC4* p2)
{
    pOut->x = (p1->x > p2->x) ? p1->x : p2->x;
    pOut->y = (p1->y > p2->y) ? p1->y : p2->y;
    pOut->z = (p1->z > p2->z) ? p1->z : p2->z;
    pOut->w = (p1->w > p2->w) ? p1->w : p2->w;

    return pOut;
}

NW_MATH_INLINE VEC4*
VEC4Minimize(VEC4* pOut, const VEC4* p1, const VEC4* p2)
{
    pOut->x = (p1->x < p2->x) ? p1->x : p2->x;
    pOut->y = (p1->y < p2->y) ? p1->y : p2->y;
    pOut->z = (p1->z < p2->z) ? p1->z : p2->z;
    pOut->w = (p1->w < p2->w) ? p1->w : p2->w;

    return pOut;
}

} } // namespace internal::standard

#if defined(NW_MATH_ENABLE_INTRINSICS)

namespace internal { namespace intrinsics {

NW_MATH_INLINE VEC4*
VEC4Add(VEC4* pOut, const VEC4* p1, const VEC4* p2)
{
    tof32x2(pOut->x) = __PS_ADD(tof32x2(p1->x), tof32x2(p2->x));
    tof32x2(pOut->z) = __PS_ADD(tof32x2(p1->z), tof32x2(p2->z));

    return pOut;
}

NW_MATH_INLINE VEC4*
VEC4Sub(VEC4* pOut, const VEC4* p1, const VEC4* p2)
{
    tof32x2(pOut->x) = __PS_SUB(tof32x2(p1->x), tof32x2(p2->x));
    tof32x2(pOut->z) = __PS_SUB(tof32x2(p1->z), tof32x2(p2->z));

    return pOut;
}

NW_MATH_INLINE VEC4*
VEC4Scale(VEC4* pOut, const VEC4* p, f32 scale)
{
    f32x2 xy = __PS_MULS0F(tof32x2(p->x), scale);
    f32x2 zw = __PS_MULS0F(tof32x2(p->z), scale);

    tof32x2(pOut->x) = xy;
    tof32x2(pOut->z) = zw;

    return pOut;
}

NW_MATH_INLINE VEC4*
VEC4Lerp(VEC4* pOut, const VEC4* __restrict p1, const VEC4* __restrict p2, f32 t)
{
    // (1-t)*p1 + t*p2

    f32x2 tt = __PS_FDUP(t);

    f32x2 f0 = tof32x2(p1->x);
    f0 = __PS_NMSUB(f0, tt, f0);
    f0 = __PS_MADD(tof32x2(p2->x), tt, f0);

    f32x2 f1 = tof32x2(p1->z);
    f1 = __PS_NMSUB(f1, tt, f1);
    f1 = __PS_MADD(tof32x2(p2->z), tt, f1);

    tof32x2(pOut->x) = f0;
    tof32x2(pOut->z) = f1;

    return pOut;
}

NW_MATH_INLINE f32
VEC4Dot(const VEC4* p1, const VEC4* p2)
{
    f32x2 f0;
    f0 = __PS_MUL(tof32x2(p1->x), tof32x2(p2->x));
    f0 = __PS_MADD(tof32x2(p1->z), tof32x2(p2->z), f0);
    f0 = __PS_SUM0(f0, f0, f0);

    return f0[0];
}

NW_MATH_INLINE f32
VEC4LenSq(const VEC4* __restrict p)
{
    f32x2 f0, f1;
    f1 = tof32x2(p->x);
    f0 = __PS_MUL(f1, f1);
    f1 = tof32x2(p->z);
    f0 = __PS_MADD(f1, f1, f0);
    f0 = __PS_SUM0(f0, f0, f0);

    return f0[0];
}

NW_MATH_INLINE f32
VEC4DistSq(const VEC4* p1, const VEC4* p2)
{
    f32x2 f0, f1;
    f1 = __PS_SUB(tof32x2(p1->x), tof32x2(p2->x));
    f0 = __PS_MUL(f1, f1);
    f1 = __PS_SUB(tof32x2(p1->z), tof32x2(p2->z));
    f0 = __PS_MADD(f1, f1, f0);
    f0 = __PS_SUM0(f0, f0, f0);

    return f0[0];
}

NW_MATH_INLINE VEC4*
VEC4Maximize(VEC4* pOut, const VEC4* p1, const VEC4* p2)
{
    f32x2 f0, f1;

    f0 = tof32x2(p1->x);
    f1 = tof32x2(p2->x);
    tof32x2(pOut->x) = __PS_SEL(__PS_SUB(f0, f1), f0, f1);

    f0 = tof32x2(p1->z);
    f1 = tof32x2(p2->z);
    tof32x2(pOut->z) = __PS_SEL(__PS_SUB(f0, f1), f0, f1);

    return pOut;
}

NW_MATH_INLINE VEC4*
VEC4Minimize(VEC4* pOut, const VEC4* p1, const VEC4* p2)
{
    f32x2 f0, f1;

    f0 = tof32x2(p1->x);
    f1 = tof32x2(p2->x);
    tof32x2(pOut->x) = __PS_SEL(__PS_SUB(f1, f0), f0, f1);

    f0 = tof32x2(p1->z);
    f1 = tof32x2(p2->z);
    tof32x2(pOut->z) = __PS_SEL(__PS_SUB(f1, f0), f0, f1);

    return pOut;
}

} } // namespace internal::intrinsics

#endif // NW_MATH_ENABLE_INTRINSICS

NW_MATH_INLINE bool
VEC4IsZero(const VEC4* p)
{
    return p->x == 0.f && p->y == 0.f && p->z == 0.f && p->w == 0.f;
}

NW_MATH_INLINE bool
VEC4IsZeroWOne(const VEC4* p)
{
    return p->x == 0.f && p->y == 0.f && p->z == 0.f && p->w == 1.f;
}

NW_MATH_INLINE VEC4*
VEC4Add(VEC4* pOut, const VEC4* p1, const VEC4* p2)
{
    return NW_MATH_IMPL_NS::VEC4Add(pOut, p1, p2);
}

NW_MATH_INLINE VEC4*
VEC4Sub(VEC4* pOut, const VEC4* p1, const VEC4* p2)
{
    return NW_MATH_IMPL_NS::VEC4Sub(pOut, p1, p2);
}

NW_MATH_INLINE VEC4*
VEC4Scale(VEC4* pOut, const VEC4* p, f32 scale)
{
    return NW_MATH_IMPL_NS::VEC4Scale(pOut, p, scale);
}

NW_MATH_INLINE VEC4*
VEC4Lerp(VEC4* pOut, const VEC4* __restrict p1, const VEC4* __restrict p2, f32 t)
{
    return NW_MATH_IMPL_NS::VEC4Lerp(pOut, p1, p2, t);
}

NW_MATH_INLINE f32
VEC4Dot(const VEC4* p1, const VEC4* p2)
{
    return NW_MATH_IMPL_NS::VEC4Dot(p1, p2);
}

NW_MATH_INLINE f32
VEC4LenSq(const VEC4* __restrict p)
{
    return NW_MATH_IMPL_NS::VEC4LenSq(p);
}

f32 VEC4Len(const VEC4* p)
{
    return FSqrt(VEC4LenSq(p));

}

// NW_MATH_INLINE VEC4*
// VEC4Normalize(VEC4* pOut, const VEC4* p)
// {
//     (void)VEC4Scale(pOut, p, FrSqrt(VEC4LenSq(p)));
//
//     return pOut;
// }

// NW_MATH_INLINE VEC4*
// VEC4FastNormalize(VEC4* pOut, const VEC4* p)
// {
//     (void)VEC4Scale(pOut, p, FrFastSqrt(VEC4LenSq(p)));
//
//     return pOut;
// }

// NW_MATH_INLINE VEC4*
// VEC4SafeNormalize(VEC4* pOut, const VEC4* p, const VEC4& alt)
// {
//     f32 mag = VEC4LenSq(p);
//
//     if (mag == 0 /* || mag == F_INF || isnan(mag) */)
//     {
//         *pOut = alt;
//
//         return pOut;
//     }
//
//     (void)VEC4Scale(pOut, p, FrSqrt(mag));
//
//     return pOut;
// }

// NW_MATH_INLINE VEC4*
// VEC4FastSafeNormalize(VEC4* pOut, const VEC4* p, const VEC4& alt)
// {
//     f32 mag = VEC4LenSq(p);
//
//     if (mag == 0 /* || mag == F_INF || isnan(mag) */)
//     {
//         *pOut = alt;
//
//         return pOut;
//     }
//
//     (void)VEC4Scale(pOut, p, FrFastSqrt(mag));
//
//     return pOut;
// }

NW_MATH_INLINE f32
VEC4DistSq(const VEC4* p1, const VEC4* p2)
{
    return NW_MATH_IMPL_NS::VEC4DistSq(p1, p2);
}

NW_MATH_INLINE VEC4*
VEC4Maximize(VEC4* pOut, const VEC4* p1, const VEC4* p2)
{
    return NW_MATH_IMPL_NS::VEC4Maximize(pOut, p1, p2);
}

NW_MATH_INLINE VEC4*
VEC4Minimize(VEC4* pOut, const VEC4* p1, const VEC4* p2)
{
    return NW_MATH_IMPL_NS::VEC4Minimize(pOut, p1, p2);
}

} } // namespace nw::math

#endif

namespace nw { namespace math {

inline bool  VEC4IsZero(const VEC4& v){ return VEC4IsZero( &v ); }
inline bool  VEC4IsZeroWOne(const VEC4& v){ return VEC4IsZeroWOne( &v ); }
inline VEC4* VEC4Add(VEC4* pOut, const VEC4& v1, const VEC4& v2) { return VEC4Add( pOut, &v1, &v2 ); }
inline VEC4* VEC4Sub(VEC4* pOut, const VEC4& v1, const VEC4& v2) { return VEC4Sub( pOut, &v1, &v2 ); }
inline VEC4* VEC4Scale(VEC4* pOut, const VEC4& v, f32 scale) { return VEC4Scale( pOut, &v, scale); }
inline VEC4* VEC4Lerp(VEC4* pOut, const VEC4& v1, const VEC4& v2, f32 t) { return VEC4Lerp( pOut, &v1, &v2, t ); }
inline f32   VEC4Dot(const VEC4& v1, const VEC4& v2) { return VEC4Dot( &v1, &v2 ); }
inline f32   VEC4LenSq(const VEC4& v) { return VEC4LenSq( &v ); }
inline f32   VEC4Len(const VEC4& v) { return VEC4Len( &v ); }
inline VEC4* VEC4Normalize(VEC4* pOut, const VEC4& v) { return VEC4Normalize( pOut, &v ); }
inline VEC4* VEC4FastNormalize(VEC4* pOut, const VEC4& v) { return VEC4FastNormalize( pOut, &v ); }
inline VEC4* VEC4SafeNormalize(VEC4* pOut, const VEC4& v, const VEC4& alt) { return VEC4SafeNormalize( pOut, &v, alt ); }
inline VEC4* VEC4FastSafeNormalize(VEC4* pOut, const VEC4& v, const VEC4& alt) { return VEC4FastSafeNormalize( pOut, &v, alt ); }
inline f32   VEC4DistSq(const VEC4& v1, const VEC4& v2) { return VEC4DistSq( &v1, &v2 ); }
inline VEC4* VEC4Maximize(VEC4* pOut, const VEC4& v1, const VEC4& v2) { return VEC4Maximize( pOut, &v1, &v2 ); }
inline VEC4* VEC4Minimize(VEC4* pOut, const VEC4& v1, const VEC4& v2) { return VEC4Minimize( pOut, &v1, &v2 ); }

} } // namespace nw::math

#endif
