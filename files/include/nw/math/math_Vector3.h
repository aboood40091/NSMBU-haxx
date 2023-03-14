#ifndef NW_MATH_VECTOR3_H_
#define NW_MATH_VECTOR3_H_

#include <cstring>
#include <nw/math/math_Config.h>
#include <nw/math/math_Constant.h>

namespace nw { namespace math {

struct VEC3;
struct MTX34;
struct MTX44;

namespace internal { namespace standard {

    VEC3* VEC3Maximize(VEC3* pOut, const VEC3* p1, const VEC3* p2);
    VEC3* VEC3Minimize(VEC3* pOut, const VEC3* p1, const VEC3* p2);
    f32 VEC3SquareDist(const VEC3* p1, const VEC3* p2);

} } // namespace internal::standard

#if defined(NW_MATH_ENABLE_INTRINSICS)

namespace internal { namespace intrinsics {

    VEC3* VEC3Maximize(VEC3* pOut, const VEC3* p1, const VEC3* p2);
    VEC3* VEC3Minimize(VEC3* pOut, const VEC3* p1, const VEC3* p2);
    f32 VEC3SquareDist(const VEC3* p1, const VEC3* p2);

} } // namespace internal::intrinsics

#endif // NW_MATH_ENABLE_INTRINSICS

NW_MATH_INLINE bool VEC3IsZero(const VEC3* p);
NW_MATH_INLINE VEC3* VEC3Maximize(VEC3* pOut, const VEC3* p1, const VEC3* p2);
NW_MATH_INLINE VEC3* VEC3Minimize(VEC3* pOut, const VEC3* p1, const VEC3* p2);
NW_MATH_INLINE VEC3* VEC3Cross(VEC3* pOut, const VEC3* p1, const VEC3* p2);
NW_MATH_INLINE VEC3* VEC3Normalize(VEC3* pOut, const VEC3* p);
/* NW_MATH_INLINE */ extern VEC3* VEC3FastNormalize(VEC3* pOut, const VEC3* p);
NW_MATH_INLINE VEC3* VEC3SafeNormalize(VEC3* pOut, const VEC3* p, const VEC3& alt);
/* NW_MATH_INLINE */ extern VEC3* VEC3FastSafeNormalize(VEC3* pOut, const VEC3* p, const VEC3& alt);
NW_MATH_INLINE f32   VEC3SquareDist(const VEC3* p1, const VEC3* p2);

inline VEC3* VEC3Add(VEC3* pOut, const VEC3* p1, const VEC3* p2);
inline VEC3* VEC3Sub(VEC3* pOut, const VEC3* p1, const VEC3* p2);
inline VEC3* VEC3Mult(VEC3* pOut, const VEC3* p1, const VEC3* p2);
inline VEC3* VEC3Scale(VEC3* pOut, const VEC3* p, f32 scale);
inline VEC3* VEC3Lerp(VEC3* pOut, const VEC3* p1, const VEC3* p2, f32 t);
inline f32   VEC3Dot(const VEC3* p1, const VEC3* p2);
inline f32   VEC3Len(const VEC3* p);
inline f32   VEC3SquareLen(const VEC3* p);
inline f32   VEC3Dist(const VEC3* p1, const VEC3* p2);

struct VEC3_
{
    f32 x;
    f32 y;
    f32 z;
};

struct VEC3 : public VEC3_
{
public:
    static const int DIMENSION = 3;

    static const VEC3& Zero()
    {
        static const VEC3 zero(0.0f, 0.0f, 0.0f);

        return zero;
    }

    typedef VEC3 self_type;
    typedef f32  value_type;
public:
    VEC3() {}
    explicit VEC3(const f32* p) { x = p[0]; y = p[1]; z = p[2]; }
    explicit VEC3(const VEC3_& v) { x = v.x; y = v.y; z = v.z; }
    VEC3(f32 fx, f32 fy, f32 fz) { x = fx; y = fy; z = fz; }

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

    self_type& operator += (const self_type& rhs) { (void)VEC3Add(this, this, &rhs); return *this; }
    self_type& operator -= (const self_type& rhs) { (void)VEC3Sub(this, this, &rhs); return *this; }
    self_type& operator *= (const self_type& rhs) { (void)VEC3Mult(this, this, &rhs); return *this; }
    self_type& operator *= (f32 f) { (void)VEC3Scale(this, this, f); return *this; }
    self_type& operator /= (f32 f) { return operator*=(1.f / f); }

    self_type operator + () const { return *this; }
    self_type operator - () const { return self_type(-x, -y, -z); }

    self_type operator + (const self_type& rhs) const { VEC3 tmp; (void)VEC3Add(&tmp, this, &rhs); return tmp; }
    self_type operator - (const self_type& rhs) const { VEC3 tmp; (void)VEC3Sub(&tmp, this, &rhs); return tmp; }
    self_type operator * (f32 f) const { VEC3 tmp; (void)VEC3Scale(&tmp, this, f); return tmp; }
    self_type operator / (f32 f) const { f32 r = 1.f / f; return operator*(r); }

    self_type& Lerp(const VEC3& lhs, const VEC3& rhs, f32 t)
    {
        return *VEC3Lerp(this, &lhs, &rhs, t);
    }

    f32 Dot(const VEC3& vec) const
    {
        return VEC3Dot(this, &vec);
    }

    f32 LengthSquare() const { return VEC3SquareLen(this); }
    f32 Length() const { return VEC3Len(this); }

    self_type& Normalize()
    {
        return *VEC3Normalize(this, this);
    }

    self_type& SetNormalize(const VEC3& src)
    {
        return *VEC3Normalize(this, &src);
    }

    self_type& SafeNormalize(const VEC3& alt)
    {
        return *VEC3SafeNormalize(this, this, alt);
    }

    self_type& SetSafeNormalize(const VEC3& src, const VEC3& alt)
    {
        return *VEC3SafeNormalize(this, &src, alt);
    }

    f32 DistanceSquare(const VEC3& vec)
    {
        return VEC3SquareDist(this, &vec);
    }

    f32 Distance(const VEC3& vec)
    {
        return VEC3Dist(this, &vec);
    }

    self_type& SetMaximize(const VEC3& lhs, const VEC3& rhs)
    {
        return *VEC3Maximize(this, &lhs, &rhs);
    }

    self_type& SetMinimize(const VEC3& lhs, const VEC3& rhs)
    {
        return *VEC3Minimize(this, &lhs, &rhs);
    }

    self_type& Cross(const VEC3& rhs)
    {
        return *VEC3Cross(this, this, &rhs);
    }

    self_type& SetCross(const VEC3& lhs, const VEC3& rhs)
    {
        return *VEC3Cross(this, &lhs, &rhs);
    }

    NW_MATH_INLINE self_type& SetTransform(const MTX34& pM, const VEC3& src);
    self_type& Transform(const MTX34& pM) { return this->SetTransform(pM, *this); }

    NW_MATH_INLINE self_type& SetTransform(const MTX44& pM, const VEC3& src);
    self_type& Transform(const MTX44& pM) { return this->SetTransform(pM, *this); }

    NW_MATH_INLINE self_type& SetTransformNormal(const MTX34& pM, const VEC3& src);
    self_type& TransformNormal(const MTX34& pM) { return this->SetTransform(pM, *this); } // <--- Mistake?

    void Set(f32 fx, f32 fy, f32 fz) { x = fx; y = fy; z = fz; }
    void Set(const self_type& value) { x = value.x; y = value.y; z = value.z; }

    bool operator == (const self_type& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
    bool operator != (const self_type& rhs) const { return x != rhs.x || y != rhs.y || z != rhs.z; }

    bool IsZero() const { return VEC3IsZero(this); }
};

typedef struct VEC3 Vector3;

namespace internal { namespace standard {

NW_INLINE VEC3*
VEC3Add(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    pOut->x = p1->x + p2->x;
    pOut->y = p1->y + p2->y;
    pOut->z = p1->z + p2->z;
    return pOut;
}

NW_INLINE VEC3*
VEC3Sub(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    pOut->x = p1->x - p2->x;
    pOut->y = p1->y - p2->y;
    pOut->z = p1->z - p2->z;
    return pOut;
}

NW_INLINE VEC3*
VEC3Mult(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    pOut->x = p1->x * p2->x;
    pOut->y = p1->y * p2->y;
    pOut->z = p1->z * p2->z;
    return pOut;
}

NW_INLINE VEC3*
VEC3Scale(VEC3* pOut, const VEC3* p, f32 scale)
{
    pOut->x = scale * p->x;
    pOut->y = scale * p->y;
    pOut->z = scale * p->z;
    return pOut;
}

NW_INLINE VEC3*
VEC3Lerp(VEC3* pOut, const VEC3* p1, const VEC3* p2, f32 t)
{
    pOut->x = p1->x + t * (p2->x - p1->x);
    pOut->y = p1->y + t * (p2->y - p1->y);
    pOut->z = p1->z + t * (p2->z - p1->z);
    return pOut;
}

NW_INLINE f32
VEC3Dot(const VEC3* p1, const VEC3* p2)
{
    return p1->x * p2->x + p1->y * p2->y + p1->z * p2->z;
}

} } // namespace internal::standard

#if defined(NW_MATH_ENABLE_INTRINSICS)

namespace internal { namespace intrinsics {

NW_INLINE VEC3*
VEC3Add(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    tof32x2(pOut->x) = __PS_ADD(tof32x2(p1->x), tof32x2(p2->x));

    pOut->z = p1->z + p2->z;

    return pOut;
}

NW_INLINE VEC3*
VEC3Sub(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    tof32x2(pOut->x) = __PS_SUB(tof32x2(p1->x), tof32x2(p2->x));

    pOut->z = p1->z - p2->z;

    return pOut;
}

NW_INLINE VEC3*
VEC3Mult(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    tof32x2(pOut->x) = __PS_MUL(tof32x2(p1->x), tof32x2(p2->x));

    pOut->z = p1->z * p2->z;

    return pOut;
}

NW_INLINE VEC3*
VEC3Scale(VEC3* pOut, const VEC3* p, f32 scale)
{
    tof32x2(pOut->x) = __PS_MULS0F(tof32x2(p->x), scale);

    pOut->z = scale * p->z;

    return pOut;
}

NW_INLINE VEC3*
VEC3Lerp(VEC3* pOut, const VEC3* p1, const VEC3* p2, f32 t)
{
    f32x2 tt = __PS_FDUP(t);
    f32x2 f0 = tof32x2(p1->x);
    f0 = __PS_NMSUB(f0, tt, f0);
    tof32x2(pOut->x) = __PS_MADD(tof32x2(p2->x), tt, f0);

    pOut->z = p1->z + t * (p2->z - p1->z);

    return pOut;
}

NW_INLINE f32
VEC3Dot(const VEC3* p1, const VEC3* p2)
{
    f32x2 f0;
    f0 = __PS_MUL(tof32x2(p1->x), tof32x2(p2->x));
    f0 = __PS_SUM0(f0, f0, f0);

    return f0[0] + p1->z * p2->z;
}

} } // namespace internal::intrinsics

#endif // NW_MATH_ENABLE_INTRINSICS

inline VEC3*
VEC3Add(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    return NW_MATH_IMPL_NS::VEC3Add(pOut, p1, p2);
}

inline VEC3*
VEC3Sub(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    return NW_MATH_IMPL_NS::VEC3Sub(pOut, p1, p2);
}

inline VEC3*
VEC3Mult(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    return NW_MATH_IMPL_NS::VEC3Mult(pOut, p1, p2);
}

inline VEC3*
VEC3Scale(VEC3* pOut, const VEC3* p, f32 scale)
{
    return NW_MATH_IMPL_NS::VEC3Scale(pOut, p, scale);
}

inline VEC3*
VEC3Lerp(VEC3* pOut, const VEC3* p1, const VEC3* p2, f32 t)
{
    return NW_MATH_IMPL_NS::VEC3Lerp(pOut, p1, p2, t);
}

inline f32
VEC3Dot(const VEC3* p1, const VEC3* p2)
{
    return internal::standard::VEC3Dot(p1, p2);
}

inline f32
VEC3SquareLen(const VEC3* p)
{
    return p->x * p->x + p->y * p->y + p->z * p->z;
}

inline f32
VEC3Len(const VEC3* p)
{
    return ::std::sqrt( VEC3SquareLen( p ) );
}

inline f32
VEC3Dist( const VEC3* p1, const VEC3* p2 )
{
    return ::std::sqrt( VEC3SquareDist( p1, p2 ) );
}

inline VEC3
operator * (f32 f, const VEC3& rhs) { VEC3 tmp; (void)VEC3Scale(&tmp, &rhs, f); return tmp; }

} } // namespace nw::math

#if defined(NW_MATH_AS_INLINE)

#include <cmath>

namespace nw { namespace math {

namespace internal { namespace standard {

NW_MATH_INLINE VEC3*
VEC3Maximize(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    pOut->x = (p1->x > p2->x) ? p1->x : p2->x;
    pOut->y = (p1->y > p2->y) ? p1->y : p2->y;
    pOut->z = (p1->z > p2->z) ? p1->z : p2->z;

    return pOut;
}

NW_MATH_INLINE VEC3*
VEC3Minimize(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    pOut->x = (p1->x < p2->x) ? p1->x : p2->x;
    pOut->y = (p1->y < p2->y) ? p1->y : p2->y;
    pOut->z = (p1->z < p2->z) ? p1->z : p2->z;

    return pOut;
}

NW_MATH_INLINE f32
VEC3SquareDist(const VEC3* p1, const VEC3* p2)
{
    VEC3 diff;

    diff.x = p1->x - p2->x;
    diff.y = p1->y - p2->y;
    diff.z = p1->z - p2->z;

    return (diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z);
}

} } // namespace internal::standard

#if defined(NW_MATH_ENABLE_INTRINSICS)

namespace internal { namespace intrinsics {

NW_MATH_INLINE VEC3*
VEC3Maximize(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    f32x2 f0, f1, f2;

    f0 = tof32x2(p1->x);
    f1 = tof32x2(p2->x);
    f2 = __PS_SUB(f0, f1);
    f2 = __PS_SEL(f2, f0, f1);

    tof32x2(pOut->x) = f2;

    pOut->z = (p1->z > p2->z) ? p1->z : p2->z;

    return pOut;
}

NW_MATH_INLINE VEC3*
VEC3Minimize(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    f32x2 f0, f1, f2;

    f0 = tof32x2(p1->x);
    f1 = tof32x2(p2->x);
    f2 = __PS_SUB(f1, f0);
    f2 = __PS_SEL(f2, f0, f1);

    tof32x2(pOut->x) = f2;

    f32 z1 = p1->z;
    f32 z2 = p2->z;

    pOut->z = (z1 < z2) ? z1 : z2;

    return pOut;
}

NW_MATH_INLINE f32
VEC3SquareDist(const VEC3* p1, const VEC3* p2)
{
    f32x2 f0;
    f0 = __PS_SUB(tof32x2(p1->x), tof32x2(p2->x));
    f0 = __PS_MUL(f0, f0);
    f0 = __PS_SUM0(f0, f0, f0);

    f32 f1 = p1->z - p2->z;

    return f0[0] + f1 * f1;
}

} } // namespace internal::intrinsics

#endif // NW_MATH_ENABLE_INTRINSICS

NW_MATH_INLINE bool
VEC3IsZero(const VEC3* p)
{
    return p->x == 0.f && p->y == 0.f && p->z == 0.f;
}

NW_MATH_INLINE VEC3*
VEC3Maximize(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    return NW_MATH_IMPL_NS::VEC3Maximize(pOut, p1, p2);
}

NW_MATH_INLINE VEC3*
VEC3Minimize(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    return NW_MATH_IMPL_NS::VEC3Minimize(pOut, p1, p2);
}

NW_MATH_INLINE VEC3*
VEC3Cross(VEC3* pOut, const VEC3* p1, const VEC3* p2)
{
    VEC3 tmpVec;

    tmpVec.x = ( p1->y * p2->z ) - ( p1->z * p2->y );
    tmpVec.y = ( p1->z * p2->x ) - ( p1->x * p2->z );
    tmpVec.z = ( p1->x * p2->y ) - ( p1->y * p2->x );

    pOut->x = tmpVec.x;
    pOut->y = tmpVec.y;
    pOut->z = tmpVec.z;

    return pOut;
}

NW_MATH_INLINE VEC3*
VEC3Normalize(VEC3* pOut, const VEC3* p)
{
    f32 mag = (p->x * p->x) + (p->y * p->y) + (p->z * p->z);

    mag = 1.0f / ::std::sqrt(mag);

    pOut->x = p->x * mag;
    pOut->y = p->y * mag;
    pOut->z = p->z * mag;

    return pOut;
}

// NW_MATH_INLINE VEC3*
// VEC3FastNormalize(VEC3* pOut, const VEC3* p)
// {
//     f32 mag = (p->x * p->x) + (p->y * p->y) + (p->z * p->z);
//
//     mag = FrFastSqrt(mag);
//
//     pOut->x = p->x * mag;
//     pOut->y = p->y * mag;
//     pOut->z = p->z * mag;
//
//     return pOut;
// }

NW_MATH_INLINE VEC3*
VEC3SafeNormalize(VEC3* pOut, const VEC3* p, const VEC3& alt)
{
    f32 mag = (p->x * p->x) + (p->y * p->y) + (p->z * p->z);

    if (mag == 0 /* || mag == F_INF || isnan(mag) */)
    {
        *pOut = alt;

        return pOut;
    }

    mag = 1.0f / ::std::sqrt(mag);

    pOut->x = p->x * mag;
    pOut->y = p->y * mag;
    pOut->z = p->z * mag;

    return pOut;
}

// NW_MATH_INLINE VEC3*
// VEC3FastSafeNormalize(VEC3* pOut, const VEC3* p, const VEC3& alt)
// {
//     f32 mag = (p->x * p->x) + (p->y * p->y) + (p->z * p->z);
//
//     if (mag == 0 /* || mag == F_INF || isnan(mag) */)
//     {
//         *pOut = alt;
//
//         return pOut;
//     }
//
//     mag = FrFastSqrt(mag);
//
//     pOut->x = p->x * mag;
//     pOut->y = p->y * mag;
//     pOut->z = p->z * mag;
//
//     return pOut;
// }

NW_MATH_INLINE f32
VEC3SquareDist(const VEC3* p1, const VEC3* p2)
{
    return NW_MATH_IMPL_NS::VEC3SquareDist(p1, p2);
}

} } // namespace nw::math

#endif

namespace nw { namespace math {

inline bool VEC3IsZero(const VEC3& v){ return VEC3IsZero( &v ); }
inline VEC3* VEC3Maximize(VEC3* pOut, const VEC3& v1, const VEC3& v2) { return VEC3Maximize( pOut, &v1, &v2 ); }
inline VEC3* VEC3Minimize(VEC3* pOut, const VEC3& v1, const VEC3& v2) { return VEC3Minimize( pOut, &v1, &v2 ); }
inline VEC3* VEC3Cross(VEC3* pOut, const VEC3& v1, const VEC3& v2) { return VEC3Cross( pOut, &v1, &v2 ); }
inline VEC3* VEC3Normalize(VEC3* pOut, const VEC3& v) { return VEC3Normalize( pOut, &v ); }
inline VEC3* VEC3FastNormalize(VEC3* pOut, const VEC3& v) { return VEC3FastNormalize( pOut, &v ); }
inline VEC3* VEC3SafeNormalize(VEC3* pOut, const VEC3& v, const VEC3& alt) { return VEC3SafeNormalize( pOut, &v, alt ); }
inline VEC3* VEC3FastSafeNormalize(VEC3* pOut, const VEC3& v, const VEC3& alt) { return VEC3FastSafeNormalize( pOut, &v, alt ); }
inline f32   VEC3SquareDist(const VEC3& v1, const VEC3& v2) { return VEC3SquareDist( &v1, &v2 ); }

inline VEC3* VEC3Add(VEC3* pOut, const VEC3& v1, const VEC3& v2) { return VEC3Add( pOut, &v1, &v2 ); }
inline VEC3* VEC3Sub(VEC3* pOut, const VEC3& v1, const VEC3& v2) { return VEC3Sub( pOut, &v1, &v2 ); }
inline VEC3* VEC3Scale(VEC3* pOut, const VEC3& v, f32 scale) { return VEC3Scale( pOut, &v, scale ); }
inline VEC3* VEC3Lerp(VEC3* pOut, const VEC3& v1, const VEC3& v2, f32 t) { return VEC3Lerp( pOut, &v1, &v2, t ); }
inline f32   VEC3Dot(const VEC3& v1, const VEC3& v2) { return VEC3Dot( &v1, &v2 ); }
inline f32   VEC3Len(const VEC3& v) { return VEC3Len( &v ); }
inline f32   VEC3SquareLen(const VEC3& v) { return VEC3SquareLen( &v ); }
inline f32   VEC3Dist(const VEC3& v1, const VEC3& v2) { return VEC3Dist( &v1, &v2 ); }

} } // namespace nw::math

#endif
