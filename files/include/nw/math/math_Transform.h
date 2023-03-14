#ifndef NW_MATH_TRANSFORM_H_
#define NW_MATH_TRANSFORM_H_

#include <nw/math/math_Config.h>
#include <nw/math/math_Vector2.h>
#include <nw/math/math_Vector3.h>
#include <nw/math/math_Vector4.h>

namespace nw { namespace math {

struct Transform2_
{
    VEC2    scale;
    VEC2    rotate;
    VEC2    translate;
};

struct Transform3_
{
    VEC3    scale;
    VEC3    rotate;
    VEC3    translate;
};

struct Transform2 : public Transform2_
{
public:
    typedef Transform2 self_type;
    typedef f32        value_type;
public:
    Transform2() {}
    explicit Transform2(const Transform2_& t)
    {
        scale = t.scale;
        rotate = t.rotate;
        translate = t.translate;
    }
    Transform2(const VEC2& s, const VEC2& r, const VEC2& t)
    {
        scale     = s;
        rotate    = r;
        translate = t;
    }

    bool operator == (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(Transform2)) == 0; }
    bool operator != (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(Transform2)) != 0; }
};

struct Transform3 : public Transform3_
{
public:
    typedef Transform3 self_type;
    typedef f32        value_type;
public:
    Transform3() {}
    explicit Transform3(const Transform3_& t)
    {
        scale = t.scale;
        rotate = t.rotate;
        translate = t.translate;
    }
    Transform3(const VEC3& s, const VEC3& r, const VEC3& t)
    {
        scale     = s;
        rotate    = r;
        translate = t;
    }

    bool operator == (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(Transform3)) == 0; }
    bool operator != (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(Transform3)) != 0; }
};

inline Transform2*
Transform2Identity(Transform2* pOut)
{
    pOut->scale     = VEC2(1.f, 1.f);
    pOut->rotate    = VEC2(0.f, 0.f);
    pOut->translate = VEC2(0.f, 0.f);
    return pOut;
}

inline Transform3*
Transform3Identity(Transform3* pOut)
{
    pOut->scale     = VEC3(1.f, 1.f, 1.f);
    pOut->rotate    = VEC3(0.f, 0.f, 0.f);
    pOut->translate = VEC3(0.f, 0.f, 0.f);
    return pOut;
}

// NW_MATH_INLINE VEC3* VEC3Transform(VEC3* pOut, const MTX34* pM, const VEC3* pV); <-- Redundant redeclaration
// NW_MATH_INLINE VEC3* VEC3Transform(VEC3* pOut, const MTX44* pM, const VEC3* pV); <-- Redundant redeclaration

// NW_MATH_INLINE VEC4* VEC3Transform(VEC4* pOut, const MTX44* pM, const VEC3* pV); <-- Redundant redeclaration
NW_MATH_INLINE VEC3* VEC3TransformArray(VEC3* pOut, const MTX34* pM, const VEC3* pV, s32 count);
NW_MATH_INLINE VEC4* VEC3TransformArray(VEC4* pOut, const MTX44* pM, const VEC3* pV, u32 count);

NW_MATH_INLINE VEC3* VEC3TransformNormal(VEC3* pOut, const MTX34* pM, const VEC3* pV);
NW_MATH_INLINE VEC3* VEC3TransformNormalArray(VEC3* pOutArray, const MTX34* pM, const VEC3* pArray, u32 n);

NW_MATH_INLINE VEC3* VEC3TransformCoord(VEC3* pOut, const MTX44* pM, const VEC3* pV);
NW_MATH_INLINE VEC3* VEC3TransformCoordArray(VEC3* pOut, const MTX44* pM, const VEC3* pV, u32 count);

NW_MATH_INLINE VEC4* VEC4Transform(VEC4* pOut, const MTX44* pM, const VEC4* pV);
NW_MATH_INLINE VEC4* VEC4TransformArray(VEC4* pOut, const MTX44* pM, const VEC4* pV, u32 n);

NW_MATH_INLINE VEC4* VEC4Transform(VEC4* pOut, const MTX34* pM, const VEC4* pV);
NW_MATH_INLINE VEC4* VEC4TransformArray(VEC4* pOut, const MTX34* pM, const VEC4* pV, u32 n);

inline VEC3* VEC3Transform(VEC3* pOut, const MTX34& m, const VEC3& v) { return VEC3Transform( pOut, &m, &v ); }
inline VEC4* VEC3Transform(VEC4* pOut, const MTX44& m, const VEC3& v) { return VEC3Transform( pOut, &m, &v ); }
inline VEC3* VEC3TransformArray(VEC3* pOutArray, const MTX34& m, const VEC3* pArray, s32 count) { return VEC3TransformArray( pOutArray, &m, pArray, count ); }
inline VEC4* VEC3TransformArray(VEC4* pOutArray, const MTX44& m, const VEC3* pArray, u32 count) { return VEC3TransformArray( pOutArray, &m, pArray, count ); }

inline VEC3* VEC3TransformNormal(VEC3* pOut, const MTX34& m, const VEC3& v) { return VEC3TransformNormal( pOut, &m, &v ); }
inline VEC3* VEC3TransformNormalArray(VEC3* pOutArray, const MTX34& m, const VEC3* pArray, u32 n) { return VEC3TransformNormalArray( pOutArray, &m, pArray, n ); }

inline VEC3* VEC3TransformCoord(VEC3* pOut, const MTX44& m, const VEC3& v) { return VEC3TransformCoord( pOut, &m, &v ); }
inline VEC3* VEC3TransformCoordArray(VEC3* pOutArray, const MTX44& m, const VEC3* pArray, u32 count) { return VEC3TransformCoordArray( pOutArray, &m, pArray, count ); }

inline VEC4* VEC4Transform(VEC4* pOut, const MTX44& m, const VEC4& v) { return VEC4Transform( pOut, &m, &v ); }
inline VEC4* VEC4TransformArray(VEC4* pOutArray, const MTX44& m, const VEC4* pArray, u32 n) { return VEC4TransformArray( pOutArray, &m, pArray, n ); }

NW_MATH_INLINE VEC3&
VEC3::SetTransform(const MTX34& mtx, const VEC3& src)
{
    return *VEC3Transform(this, &mtx, &src);
}

NW_MATH_INLINE VEC3&
VEC3::SetTransform(const MTX44& mtx, const VEC3& src)
{
    return *VEC3Transform(this, &mtx, &src);
}

NW_MATH_INLINE VEC3&
VEC3::SetTransformNormal(const MTX34& mtx, const VEC3& src)
{
    return *VEC3TransformNormal(this, &mtx, &src);
}


NW_MATH_INLINE VEC4&
VEC4::SetTransform(const MTX34& mtx, const VEC4& src)
{
    return *VEC4Transform(this, &mtx, &src);
}

NW_MATH_INLINE VEC4&
VEC4::SetTransform(const MTX44& mtx, const VEC4& src)
{
    return *VEC4Transform(this, &mtx, &src);
}

} }  // namespace nw::math

#endif // NW_MATH_TRANSFORM_H_
