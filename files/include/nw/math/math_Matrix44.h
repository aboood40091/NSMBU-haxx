#ifndef NW_MATH_MATRIX44_H_
#define NW_MATH_MATRIX44_H_

//#define NW_MATH_USE_OLDMTX

#if defined(NW_PLATFORM_CAFE)
    #include <cafe/mtx/mtx44.h>
#endif

#include <cstring>
#include <nw/math/math_Config.h>

namespace nw { namespace math {

struct MTX44;

namespace internal { namespace standard {

    VEC4* VEC3Transform(VEC4* pOut, const MTX44* pM, const VEC3* pV);
    MTX44* MTX44Add(MTX44* pOut, const MTX44* p1, const MTX44* p2);
    MTX44* MTX44Sub(MTX44* pOut, const MTX44* p1, const MTX44* p2);
    MTX44* MTX44Mult(MTX44* pOut, const MTX44* p, f32 f);
    MTX44* MTX44Mult(MTX44* pOut, const MTX44* __restrict p1, const MTX44* __restrict p2);
    MTX44* MTX44MultScale(MTX44* pOut, const MTX44* pM, const VEC3* pS);
    MTX44* MTX44MultScale(MTX44* pOut, const VEC3* pS, const MTX44* pM);

} } // namespace internal::standard

namespace internal { namespace intrinsics {

    VEC4* VEC3Transform(VEC4* pOut, const MTX44* pM, const VEC3* pV);
    MTX44* MTX44Add(MTX44* pOut, const MTX44* p1, const MTX44* p2);
    MTX44* MTX44Sub(MTX44* pOut, const MTX44* p1, const MTX44* p2);
    MTX44* MTX44Mult(MTX44* pOut, const MTX44* p, f32 f);
    MTX44* MTX44Mult(MTX44* pOut, const MTX44* __restrict p1, const MTX44* __restrict p2);
    MTX44* MTX44MultScale(MTX44* pOut, const MTX44* pM, const VEC3* pS);
    MTX44* MTX44MultScale(MTX44* pOut, const VEC3* pS, const MTX44* pM);

} } // namespace internal::intrinsics

NW_MATH_INLINE MTX44* MTX44Zero(MTX44* pOut);
NW_MATH_INLINE bool   MTX44IsIdentity(const MTX44* p);
NW_MATH_INLINE MTX44* MTX44Identity(MTX44* pOut);
NW_MATH_INLINE MTX44* MTX44Copy(MTX44* pOut, const MTX44* p);

NW_MATH_INLINE MTX44* MTX44Add(MTX44* pOut, const MTX44* p1, const MTX44* p2);
NW_MATH_INLINE MTX44* MTX44Sub(MTX44* pOut, const MTX44* p1, const MTX44* p2);
NW_MATH_INLINE MTX44* MTX44Mult(MTX44* pOut, const MTX44* p, f32 f);
NW_MATH_INLINE MTX44* MTX44Mult(MTX44* pOut, const MTX44* p1, const MTX44* p2);

NW_MATH_INLINE MTX44* MTX44FrustumNew(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f);
NW_MATH_INLINE MTX44* MTX44OrthoNew(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f);
NW_MATH_INLINE MTX44* MTX44PerspectiveRadNew(MTX44* pOut, f32 fovyRad, f32 aspect, f32 n, f32 f);

NW_MATH_INLINE MTX44* MTX44FrustumOld(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f);
NW_MATH_INLINE MTX44* MTX44OrthoOld(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f);
NW_MATH_INLINE MTX44* MTX44PerspectiveRadOld(MTX44* pOut, f32 fovyRad, f32 aspect, f32 n, f32 f);

NW_MATH_INLINE MTX44* MTX44Frustum(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f)
{
#ifdef NW_MATH_USE_OLDMTX
    return MTX44FrustumOld(pOut, l, r, b, t, n, f);
#else
    return MTX44FrustumNew(pOut, l, r, b, t, n, f);
#endif
}
NW_MATH_INLINE MTX44* MTX44Ortho(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f)
{
#ifdef NW_MATH_USE_OLDMTX
    return MTX44OrthoOld(pOut, l, r, b, t, n, f);
#else
    return MTX44OrthoNew(pOut, l, r, b, t, n, f);
#endif
}
NW_MATH_INLINE MTX44* MTX44PerspectiveRad(MTX44* pOut, f32 fovyRad, f32 aspect, f32 n, f32 f)
{
#ifdef NW_MATH_USE_OLDMTX
    return MTX44PerspectiveRadOld(pOut, fovyRad, aspect, n, f);
#else
    return MTX44PerspectiveRadNew(pOut, fovyRad, aspect, n, f);
#endif
}

NW_MATH_INLINE MTX44* MTX44Transpose(MTX44* pOut, const MTX44 *pSrc);
NW_MATH_INLINE MTX44* MTX44MultArray(MTX44* pOut, const MTX44* p1, const MTX44* pSrc, s32 count);
NW_MATH_INLINE u32    MTX44Inverse(MTX44* pOut, const MTX44* p);

NW_MATH_INLINE MTX44* MTX44RotXYZIdx(MTX44* pOut, u32 idxX, u32 idxY, u32 idxZ);
NW_MATH_INLINE MTX44* MTX44RotAxisIdx(MTX44* pOut, const VEC3* pAxis, u32 idx);

NW_MATH_INLINE MTX44* MTX44Scale(MTX44* pOut, const VEC3* pS);
NW_MATH_INLINE MTX44* MTX44MultScale(MTX44* pOut, const MTX44* pM, const VEC3* pS);
NW_MATH_INLINE MTX44* MTX44MultScale(MTX44* pOut, const VEC3* pS, const MTX44* pM);

NW_MATH_INLINE MTX44* MTX44Translate(MTX44* pOut, const VEC3* pT);
NW_MATH_INLINE MTX44* MTX44MultTranslate(MTX44* pOut, const MTX44* pM, const VEC3* pT);
NW_MATH_INLINE MTX44* MTX44MultTranslate(MTX44* pOut, const VEC3* pT, const MTX44* pM);

enum PivotDirection
{
    PIVOT_NONE,
    PIVOT_UPSIDE_TO_TOP,
    PIVOT_UPSIDE_TO_RIGHT,
    PIVOT_UPSIDE_TO_BOTTOM,
    PIVOT_UPSIDE_TO_LEFT,
    PIVOT_NUM
};

NW_MATH_INLINE MTX44* MTX44FrustumPivot(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, PivotDirection pivot = PIVOT_NONE);
NW_MATH_INLINE MTX44* MTX44OrthoPivot(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, PivotDirection pivot = PIVOT_NONE);
NW_MATH_INLINE MTX44* MTX44PerspectivePivotRad(MTX44* pOut, f32 fovyRad, f32 aspect, f32 n, f32 f, PivotDirection pivot = PIVOT_NONE);

inline MTX44*
MTX44PerspectiveDeg(MTX44* pOut, f32 fovyDeg, f32 aspect, f32 n, f32 f)
{
    return MTX44PerspectiveRad(pOut, NW_MATH_DEG_TO_RAD(fovyDeg), aspect, n, f);
}

inline MTX44*
MTX44Perspective(MTX44* pOut, f32 fovyRad, f32 aspect, f32 n, f32 f)
{
    return MTX44PerspectiveRad(pOut, fovyRad, aspect, n, f);
}

inline MTX44*
MTX44PerspectivePivotDeg(MTX44* pOut, f32 fovyDeg, f32 aspect, f32 n, f32 f, PivotDirection pivot = PIVOT_NONE )
{
    return MTX44PerspectivePivotRad(pOut, NW_MATH_DEG_TO_RAD(fovyDeg), aspect, n, f, pivot);
}

inline MTX44*
MTX44RotXYZRad(MTX44* pOut, f32 fRadX, f32 fRadY, f32 fRadZ)
{
    return MTX44RotXYZIdx(pOut, NW_MATH_RAD_TO_IDX(fRadX), NW_MATH_RAD_TO_IDX(fRadY), NW_MATH_RAD_TO_IDX(fRadZ));
}

inline MTX44*
MTX44RotXYZDeg(MTX44* pOut, f32 fDegX, f32 fDegY, f32 fDegZ)
{
    return MTX44RotXYZIdx(pOut, NW_MATH_DEG_TO_IDX(fDegX), NW_MATH_DEG_TO_IDX(fDegY), NW_MATH_DEG_TO_IDX(fDegZ));
}

inline MTX44*
MTX44RotAxisRad(MTX44* pOut, const VEC3* pAxis, f32 fRad)
{
    return MTX44RotAxisIdx(pOut, pAxis, NW_MATH_RAD_TO_IDX(fRad));
}

inline MTX44*
MTX44RotAxisDeg(MTX44* pOut, const VEC3* pAxis, f32 fDeg)
{
    return MTX44RotAxisIdx(pOut, pAxis, NW_MATH_DEG_TO_IDX(fDeg));
}

struct MTX34;

struct MTX44_
{
    struct BaseData
    {
        f32 _00, _01, _02, _03;
        f32 _10, _11, _12, _13;
        f32 _20, _21, _22, _23;
        f32 _30, _31, _32, _33;
    };

    union
    {
        struct
        {
            f32 _00, _01, _02, _03;
            f32 _10, _11, _12, _13;
            f32 _20, _21, _22, _23;
            f32 _30, _31, _32, _33;
        };
        BaseData f;
        f32 m[4][4];
        f32 a[16];
        VEC4_ v[4];
    };
};

struct MTX44 : public MTX44_
{
public:
    static const int ROW_COUNT = 4;
    static const int COLUMN_COUNT = 4;

    static const MTX44& Identity()
    {
        static const MTX44 identity(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);

        return identity;
    }
    typedef MTX44 self_type;
    typedef f32   value_type;

public:
    MTX44() {}

    explicit MTX44(const f32* p) { (void)MTX44Copy(this, (MTX44*)p); }

    explicit MTX44(const MTX34& rhs)
    {
        (void)MTX34Copy((MTX34*)this, (MTX34*)&rhs);
        f._30 = f._31 = f._32 = 0.f; f._33 = 1.f;
    }

    MTX44(const MTX44& rhs) { (void)MTX44Copy(this, &rhs); }

    MTX44(f32 x00, f32 x01, f32 x02, f32 x03,
          f32 x10, f32 x11, f32 x12, f32 x13,
          f32 x20, f32 x21, f32 x22, f32 x23,
          f32 x30, f32 x31, f32 x32, f32 x33)
    {
        f._00 = x00; f._01 = x01; f._02 = x02; f._03 = x03;
        f._10 = x10; f._11 = x11; f._12 = x12; f._13 = x13;
        f._20 = x20; f._21 = x21; f._22 = x22; f._23 = x23;
        f._30 = x30; f._31 = x31; f._32 = x32; f._33 = x33;
    }

    operator f32*() { return this->a; }
    operator const f32*() const { return this->a; }

    f32* ToF32() { return this->a; }
    const f32* ToF32() const { return this->a; }

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

    template <typename FromPtr>
    static MTX44* CastFrom(FromPtr* fromPtr)
    {
        return reinterpret_cast<MTX44*>( fromPtr );
    }

    template <typename FromPtr>
    static const MTX44* CastFrom(const FromPtr* fromPtr)
    {
        return reinterpret_cast<const MTX44*>( fromPtr );
    }

    template <typename FromPtr>
    static MTX44& CastFrom(FromPtr& fromPtr)
    {
        return *reinterpret_cast<MTX44*>( &fromPtr );
    }

    template <typename FromPtr>
    static const MTX44& CastFrom(const FromPtr& fromPtr)
    {
        return *reinterpret_cast<const MTX44*>( &fromPtr );
    }

    VEC4& GetRow(int index)
    {
        return *reinterpret_cast<VEC4*>(&this->v[index]);
    }

    const VEC4& GetRow(int index) const
    {
        return *reinterpret_cast<const VEC4*>(&this->v[index]);
    }

    VEC4 GetColumn(int index) const
    {
        VEC4 column;
        column.x = this->m[0][index];
        column.y = this->m[1][index];
        column.z = this->m[2][index];
        column.w = this->m[3][index];
        return column;
    }

    void SetColumn(int index, const VEC4& column)
    {
        this->m[0][index] = column.x;
        this->m[1][index] = column.y;
        this->m[2][index] = column.z;
        this->m[3][index] = column.w;
    }

    self_type& operator *= (const self_type& rhs) { return *MTX44Mult(this, this, &rhs); }

    self_type& operator += (const self_type& rhs) { return *MTX44Add(this, this, &rhs); }
    self_type& operator -= (const self_type& rhs) { return *MTX44Sub(this, this, &rhs); }

    self_type& operator *= (f32 f) { return *MTX44Mult(this, this, f); }
    self_type& operator /= (f32 f) { return operator*=(1.f / f); }

    self_type operator + () const { return *this; }
    self_type operator - () const
    {
        return MTX44(-f._00, -f._01, -f._02, -f._03,
                     -f._10, -f._11, -f._12, -f._13,
                     -f._20, -f._21, -f._22, -f._23,
                     -f._30, -f._31, -f._32, -f._33);
    }

    self_type operator + (const self_type& rhs) const { MTX44 tmp; return *MTX44Add(&tmp, this, &rhs); }
    self_type operator - (const self_type& rhs) const { MTX44 tmp; return *MTX44Sub(&tmp, this, &rhs); }

    self_type operator * (f32 f) const { MTX44 tmp; return *MTX44Mult(&tmp, this, f); }
    self_type operator / (f32 f) const { return *this * (1.f / f); }

    self_type& Transpose() { return *MTX44Transpose(this, this); }

    self_type& SetIdentity() { return *MTX44Identity(this); }

    self_type& SetInverse( const MTX44& mtx )
    {
        MTX44Inverse(this, &mtx); return *this;
    }

    self_type& Inverse()
    {
        MTX44Inverse(this, this); return *this;
    }

    self_type& SetMult( const MTX44& lhs, const MTX44& rhs )
    {
        return *MTX44Mult( this, &lhs, &rhs );
    }

    self_type& SetScale(const VEC3& scale) { return *MTX44Scale(this, &scale); }

    self_type& SetTranslate(const VEC3& translate)
    {
        return *MTX44Translate(this, &translate);
    }

    self_type& SetRotateXyz(const VEC3& rotate)
    {
        return *MTX44RotXYZRad(this, rotate.x, rotate.y, rotate.z);
    }

    self_type& SetRotate(const VEC3& axis, f32 theta)
    {
        return *MTX44RotAxisRad(this, &axis, theta);
    }

    self_type& SetFrustum(f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, PivotDirection pivot = PIVOT_NONE)
    {
        return *MTX44FrustumPivot(this, l, r, b, t, n, f, pivot);
    }

    self_type& SetOrtho(f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, PivotDirection pivot = PIVOT_NONE)
    {
        return *MTX44OrthoPivot(this, l, r, b, t, n, f, pivot);
    }

    self_type& SetPerspective(f32 fovyRad, f32 aspect, f32 n, f32 f, PivotDirection pivot = PIVOT_NONE)
    {
        return *MTX44PerspectivePivotRad(this, fovyRad, aspect, n, f, pivot);
    }

    bool operator == (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(MTX44)) == 0; }
    bool operator != (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(MTX44)) != 0; }

    bool IsIdentity() const { return MTX44IsIdentity(this); }
};

typedef struct MTX44 Matrix44;

} } // namespace nw::math

namespace nw { namespace math {

inline MTX44* MTX44Copy(MTX44* pOut, const MTX44& m) { return MTX44Copy( pOut, &m ); }
inline bool   MTX44IsIdentity(const MTX44& m) { return MTX44IsIdentity( &m ); }

inline MTX44* MTX44Add(MTX44* pOut, const MTX44& m1, const MTX44& m2) { return MTX44Add( pOut, &m1, &m2 ); }
inline MTX44* MTX44Sub(MTX44* pOut, const MTX44& m1, const MTX44& m2) { return MTX44Sub( pOut, &m1, &m2 ); }
inline MTX44* MTX44Mult(MTX44* pOut, const MTX44& m, f32 f) { return MTX44Mult( pOut, &m, f ); }
inline MTX44* MTX44Mult(MTX44* pOut, const MTX44& m1, const MTX44& m2) { return MTX44Mult( pOut, &m1, &m2 ); }

inline MTX44* MTX44Transpose(MTX44* pOut, const MTX44& m) { return MTX44Transpose( pOut, &m ); }
inline MTX44* MTX44MultArray(MTX44* pOut, const MTX44& m1, const MTX44* pSrc, s32 count) { return MTX44MultArray( pOut, &m1, pSrc, count ); }
inline u32    MTX44Inverse(MTX44* pOut, const MTX44& m) { return MTX44Inverse( pOut, &m ); }

inline MTX44* MTX44RotAxisIdx(MTX44* pOut, const VEC3& vAxis, u32 idx) { return MTX44RotAxisIdx( pOut, &vAxis, idx ); }
inline MTX44* MTX44RotAxisRad(MTX44* pOut, const VEC3& vAxis, f32 fRad) { return MTX44RotAxisRad( pOut, &vAxis, fRad ); }
inline MTX44* MTX44RotAxisDeg(MTX44* pOut, const VEC3& vAxis, f32 fDeg) { return MTX44RotAxisDeg( pOut, &vAxis, fDeg ); }

inline MTX44* MTX44Scale(MTX44* pOut, const VEC3& S) { return MTX44Scale(pOut, &S); }
inline MTX44* MTX44MultScale(MTX44* pOut, const MTX44& M, const VEC3& S) { return MTX44MultScale(pOut, &M, &S); }
inline MTX44* MTX44MultScale(MTX44* pOut, const VEC3& S, const MTX44& M) { return MTX44MultScale(pOut, &S, &M); }

inline MTX44* MTX44Translate(MTX44* pOut, const VEC3& T) { return MTX44Translate(pOut, &T); }
inline MTX44* MTX44MultTranslate(MTX44* pOut, const MTX44& M, const VEC3& T) { return MTX44MultTranslate(pOut, &M, &T); }
inline MTX44* MTX44MultTranslate(MTX44* pOut, const VEC3& T, const MTX44& M) { return MTX44MultTranslate(pOut, &T, &M); }

} } // namespace nw::math

#if defined(NW_MATH_AS_INLINE)

#include <cmath>
#include <nw/math/math_Vector3.h>

namespace nw { namespace math {

namespace internal { namespace standard {

NW_MATH_INLINE VEC4*
VEC3Transform(VEC4* pOut, const MTX44* pM, const VEC3* pV)
{
    VEC4 tmp;
    tmp.x = pM->f._00 * pV->x + pM->f._01 * pV->y + pM->f._02 * pV->z + pM->f._03;
    tmp.y = pM->f._10 * pV->x + pM->f._11 * pV->y + pM->f._12 * pV->z + pM->f._13;
    tmp.z = pM->f._20 * pV->x + pM->f._21 * pV->y + pM->f._22 * pV->z + pM->f._23;
    tmp.w = pM->f._30 * pV->x + pM->f._31 * pV->y + pM->f._32 * pV->z + pM->f._33;

    pOut->x = tmp.x;
    pOut->y = tmp.y;
    pOut->z = tmp.z;
    pOut->w = tmp.w;

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44Add(MTX44* pOut, const MTX44* p1, const MTX44* p2)
{
    pOut->f._00 = p1->f._00 + p2->f._00;
    pOut->f._01 = p1->f._01 + p2->f._01;
    pOut->f._02 = p1->f._02 + p2->f._02;
    pOut->f._03 = p1->f._03 + p2->f._03;

    pOut->f._10 = p1->f._10 + p2->f._10;
    pOut->f._11 = p1->f._11 + p2->f._11;
    pOut->f._12 = p1->f._12 + p2->f._12;
    pOut->f._13 = p1->f._13 + p2->f._13;

    pOut->f._20 = p1->f._20 + p2->f._20;
    pOut->f._21 = p1->f._21 + p2->f._21;
    pOut->f._22 = p1->f._22 + p2->f._22;
    pOut->f._23 = p1->f._23 + p2->f._23;

    pOut->f._30 = p1->f._30 + p2->f._30;
    pOut->f._31 = p1->f._31 + p2->f._31;
    pOut->f._32 = p1->f._32 + p2->f._32;
    pOut->f._33 = p1->f._33 + p2->f._33;

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44Sub(MTX44* pOut, const MTX44* p1, const MTX44* p2)
{
    pOut->f._00 = p1->f._00 - p2->f._00;
    pOut->f._01 = p1->f._01 - p2->f._01;
    pOut->f._02 = p1->f._02 - p2->f._02;
    pOut->f._03 = p1->f._03 - p2->f._03;

    pOut->f._10 = p1->f._10 - p2->f._10;
    pOut->f._11 = p1->f._11 - p2->f._11;
    pOut->f._12 = p1->f._12 - p2->f._12;
    pOut->f._13 = p1->f._13 - p2->f._13;

    pOut->f._20 = p1->f._20 - p2->f._20;
    pOut->f._21 = p1->f._21 - p2->f._21;
    pOut->f._22 = p1->f._22 - p2->f._22;
    pOut->f._23 = p1->f._23 - p2->f._23;

    pOut->f._30 = p1->f._30 - p2->f._30;
    pOut->f._31 = p1->f._31 - p2->f._31;
    pOut->f._32 = p1->f._32 - p2->f._32;
    pOut->f._33 = p1->f._33 - p2->f._33;

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44Mult(MTX44* pOut, const MTX44* p, f32 f)
{
    pOut->f._00 = p->f._00 * f;
    pOut->f._01 = p->f._01 * f;
    pOut->f._02 = p->f._02 * f;
    pOut->f._03 = p->f._03 * f;

    pOut->f._10 = p->f._10 * f;
    pOut->f._11 = p->f._11 * f;
    pOut->f._12 = p->f._12 * f;
    pOut->f._13 = p->f._13 * f;

    pOut->f._20 = p->f._20 * f;
    pOut->f._21 = p->f._21 * f;
    pOut->f._22 = p->f._22 * f;
    pOut->f._23 = p->f._23 * f;

    pOut->f._30 = p->f._30 * f;
    pOut->f._31 = p->f._31 * f;
    pOut->f._32 = p->f._32 * f;
    pOut->f._33 = p->f._33 * f;

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44Mult(MTX44* pOut, const MTX44* __restrict p1, const MTX44* __restrict p2)
{
    MTX44 mTmp;

    MTX44* __restrict pDst = ( pOut == p1 || pOut == p2 ) ? &mTmp : pOut;

    pDst->f._00 = p1->f._00 * p2->f._00 + p1->f._01 * p2->f._10 + p1->f._02 * p2->f._20 + p1->f._03 * p2->f._30;
    pDst->f._01 = p1->f._00 * p2->f._01 + p1->f._01 * p2->f._11 + p1->f._02 * p2->f._21 + p1->f._03 * p2->f._31;
    pDst->f._02 = p1->f._00 * p2->f._02 + p1->f._01 * p2->f._12 + p1->f._02 * p2->f._22 + p1->f._03 * p2->f._32;
    pDst->f._03 = p1->f._00 * p2->f._03 + p1->f._01 * p2->f._13 + p1->f._02 * p2->f._23 + p1->f._03 * p2->f._33;

    pDst->f._10 = p1->f._10 * p2->f._00 + p1->f._11 * p2->f._10 + p1->f._12 * p2->f._20 + p1->f._13 * p2->f._30;
    pDst->f._11 = p1->f._10 * p2->f._01 + p1->f._11 * p2->f._11 + p1->f._12 * p2->f._21 + p1->f._13 * p2->f._31;
    pDst->f._12 = p1->f._10 * p2->f._02 + p1->f._11 * p2->f._12 + p1->f._12 * p2->f._22 + p1->f._13 * p2->f._32;
    pDst->f._13 = p1->f._10 * p2->f._03 + p1->f._11 * p2->f._13 + p1->f._12 * p2->f._23 + p1->f._13 * p2->f._33;

    pDst->f._20 = p1->f._20 * p2->f._00 + p1->f._21 * p2->f._10 + p1->f._22 * p2->f._20 + p1->f._23 * p2->f._30;
    pDst->f._21 = p1->f._20 * p2->f._01 + p1->f._21 * p2->f._11 + p1->f._22 * p2->f._21 + p1->f._23 * p2->f._31;
    pDst->f._22 = p1->f._20 * p2->f._02 + p1->f._21 * p2->f._12 + p1->f._22 * p2->f._22 + p1->f._23 * p2->f._32;
    pDst->f._23 = p1->f._20 * p2->f._03 + p1->f._21 * p2->f._13 + p1->f._22 * p2->f._23 + p1->f._23 * p2->f._33;

    pDst->f._30 = p1->f._30 * p2->f._00 + p1->f._31 * p2->f._10 + p1->f._32 * p2->f._20 + p1->f._33 * p2->f._30;
    pDst->f._31 = p1->f._30 * p2->f._01 + p1->f._31 * p2->f._11 + p1->f._32 * p2->f._21 + p1->f._33 * p2->f._31;
    pDst->f._32 = p1->f._30 * p2->f._02 + p1->f._31 * p2->f._12 + p1->f._32 * p2->f._22 + p1->f._33 * p2->f._32;
    pDst->f._33 = p1->f._30 * p2->f._03 + p1->f._31 * p2->f._13 + p1->f._32 * p2->f._23 + p1->f._33 * p2->f._33;

    if ( pDst != pOut )
    {
        nw::math::MTX44Copy( pOut, pDst );
    }

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44MultScale(MTX44* pOut, const MTX44* pM, const VEC3* pS)
{
    pOut->f._00 = pM->f._00 * pS->x;
    pOut->f._10 = pM->f._10 * pS->x;
    pOut->f._20 = pM->f._20 * pS->x;
    pOut->f._30 = pM->f._30 * pS->x;

    pOut->f._01 = pM->f._01 * pS->y;
    pOut->f._11 = pM->f._11 * pS->y;
    pOut->f._21 = pM->f._21 * pS->y;
    pOut->f._31 = pM->f._31 * pS->y;

    pOut->f._02 = pM->f._02 * pS->z;
    pOut->f._12 = pM->f._12 * pS->z;
    pOut->f._22 = pM->f._22 * pS->z;
    pOut->f._32 = pM->f._32 * pS->z;

    if (pOut != pM)
    {
        pOut->f._03 = pM->f._03;
        pOut->f._13 = pM->f._13;
        pOut->f._23 = pM->f._23;
        pOut->f._33 = pM->f._33;
    }

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44MultScale(MTX44* pOut, const VEC3* pS, const MTX44* pM)
{
    const f32 (*const src)[4] = pM->m;
    f32 (*const dst)[4] = pOut->m;

    dst[0][0] = src[0][0] * pS->x;
    dst[0][1] = src[0][1] * pS->x;
    dst[0][2] = src[0][2] * pS->x;
    dst[0][3] = src[0][3] * pS->x;

    dst[1][0] = src[1][0] * pS->y;
    dst[1][1] = src[1][1] * pS->y;
    dst[1][2] = src[1][2] * pS->y;
    dst[1][3] = src[1][3] * pS->y;

    dst[2][0] = src[2][0] * pS->z;
    dst[2][1] = src[2][1] * pS->z;
    dst[2][2] = src[2][2] * pS->z;
    dst[2][3] = src[2][3] * pS->z;

    if (pOut != pM)
    {
        dst[3][0] = src[3][0];
        dst[3][1] = src[3][1];
        dst[3][2] = src[3][2];
        dst[3][3] = src[3][3];
    }

    return pOut;
}

} } // namespace internal::standard

#if defined(NW_MATH_ENABLE_INTRINSICS)

namespace internal { namespace intrinsics {

NW_MATH_INLINE VEC4*
VEC3Transform(VEC4* pOut, const MTX44* pM, const VEC3* pV)
{
    const f32x2 m00m01 = __PSQ_LX(pM, offsetof(MTX44, m[0][0]), 0, 0);
    const f32x2 m02m03 = __PSQ_LX(pM, offsetof(MTX44, m[0][2]), 0, 0);
    const f32x2 m10m11 = __PSQ_LX(pM, offsetof(MTX44, m[1][0]), 0, 0);
    const f32x2 m12m13 = __PSQ_LX(pM, offsetof(MTX44, m[1][2]), 0, 0);
    const f32x2 m20m21 = __PSQ_LX(pM, offsetof(MTX44, m[2][0]), 0, 0);
    const f32x2 m22m23 = __PSQ_LX(pM, offsetof(MTX44, m[2][2]), 0, 0);
    const f32x2 m30m31 = __PSQ_LX(pM, offsetof(MTX44, m[3][0]), 0, 0);
    const f32x2 m32m33 = __PSQ_LX(pM, offsetof(MTX44, m[3][2]), 0, 0);

    // { xy zw } = { x y z 1 }
    const f32x2 xy = __PSQ_LX(pV, offsetof(VEC3, x), 0, 0);
    const f32x2 zw = __PSQ_LX(pV, offsetof(VEC3, z), 1, 0);

    f32x2 fp4, fp5, fp6, fp7;

    // fp4 = [ m00 m01 m02, m03 ] . T[ x y z 1 ]
    fp4 = __PS_MUL(m00m01, xy);
    fp4 = __PS_MADD(m02m03, zw, fp4);
    fp4 = __PS_SUM0(fp4, fp4, fp4);

    // fp5 = [ m10 m11 m12, m13 ] . T[ x y z 1 ]
    fp5 = __PS_MUL(m10m11, xy);
    fp5 = __PS_MADD(m12m13, zw, fp5);
    fp5 = __PS_SUM1(fp5, fp4, fp5);

    tof32x2(pOut->x) = fp5;

    // fp6 = [ m20 m21 m22, m23 ] . T[ x y z 1 ]
    fp6 = __PS_MUL(m20m21, xy);
    fp6 = __PS_MADD(m22m23, zw, fp6);
    fp6 = __PS_SUM0(fp6, fp6, fp6);

    // fp7 = [ m30 m31 m32, m33 ] . T[ x y z 1 ]
    fp7 = __PS_MUL(m30m31, xy);
    fp7 = __PS_MADD(m32m33, zw, fp7);
    fp7 = __PS_SUM1(fp7, fp6, fp7);

    tof32x2(pOut->z) = fp7;

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44Add(MTX44* pOut, const MTX44* p1, const MTX44* p2)
{
    const f32x2 fp0 = __PS_ADD(tof32x2(p1->a[0] ), tof32x2(p2->a[0] ));
    const f32x2 fp1 = __PS_ADD(tof32x2(p1->a[2] ), tof32x2(p2->a[2] ));
    const f32x2 fp2 = __PS_ADD(tof32x2(p1->a[4] ), tof32x2(p2->a[4] ));
    const f32x2 fp3 = __PS_ADD(tof32x2(p1->a[6] ), tof32x2(p2->a[6] ));
    const f32x2 fp4 = __PS_ADD(tof32x2(p1->a[8] ), tof32x2(p2->a[8] ));
    const f32x2 fp5 = __PS_ADD(tof32x2(p1->a[10]), tof32x2(p2->a[10]));
    const f32x2 fp6 = __PS_ADD(tof32x2(p1->a[12]), tof32x2(p2->a[12]));
    const f32x2 fp7 = __PS_ADD(tof32x2(p1->a[14]), tof32x2(p2->a[14]));

    tof32x2(pOut->a[0] ) = fp0;
    tof32x2(pOut->a[2] ) = fp1;
    tof32x2(pOut->a[4] ) = fp2;
    tof32x2(pOut->a[6] ) = fp3;
    tof32x2(pOut->a[8] ) = fp4;
    tof32x2(pOut->a[10]) = fp5;
    tof32x2(pOut->a[12]) = fp6;
    tof32x2(pOut->a[14]) = fp7;

    return pOut;
}


NW_MATH_INLINE MTX44*
MTX44Sub(MTX44* pOut, const MTX44* p1, const MTX44* p2)
{
    const f32x2 fp0 = __PS_SUB(tof32x2(p1->a[0] ), tof32x2(p2->a[0] ));
    const f32x2 fp1 = __PS_SUB(tof32x2(p1->a[2] ), tof32x2(p2->a[2] ));
    const f32x2 fp2 = __PS_SUB(tof32x2(p1->a[4] ), tof32x2(p2->a[4] ));
    const f32x2 fp3 = __PS_SUB(tof32x2(p1->a[6] ), tof32x2(p2->a[6] ));
    const f32x2 fp4 = __PS_SUB(tof32x2(p1->a[8] ), tof32x2(p2->a[8] ));
    const f32x2 fp5 = __PS_SUB(tof32x2(p1->a[10]), tof32x2(p2->a[10]));
    const f32x2 fp6 = __PS_SUB(tof32x2(p1->a[12]), tof32x2(p2->a[12]));
    const f32x2 fp7 = __PS_SUB(tof32x2(p1->a[14]), tof32x2(p2->a[14]));

    tof32x2(pOut->a[0] ) = fp0;
    tof32x2(pOut->a[2] ) = fp1;
    tof32x2(pOut->a[4] ) = fp2;
    tof32x2(pOut->a[6] ) = fp3;
    tof32x2(pOut->a[8] ) = fp4;
    tof32x2(pOut->a[10]) = fp5;
    tof32x2(pOut->a[12]) = fp6;
    tof32x2(pOut->a[14]) = fp7;

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44Mult(MTX44* pOut, const MTX44* p, f32 f)
{
    const f32x2 fp0 = __PS_MULS0F(tof32x2(p->a[0] ), f);
    const f32x2 fp1 = __PS_MULS0F(tof32x2(p->a[2] ), f);
    const f32x2 fp2 = __PS_MULS0F(tof32x2(p->a[4] ), f);
    const f32x2 fp3 = __PS_MULS0F(tof32x2(p->a[6] ), f);
    const f32x2 fp4 = __PS_MULS0F(tof32x2(p->a[8] ), f);
    const f32x2 fp5 = __PS_MULS0F(tof32x2(p->a[10]), f);
    const f32x2 fp6 = __PS_MULS0F(tof32x2(p->a[12]), f);
    const f32x2 fp7 = __PS_MULS0F(tof32x2(p->a[14]), f);

    tof32x2(pOut->a[0] ) = fp0;
    tof32x2(pOut->a[2] ) = fp1;
    tof32x2(pOut->a[4] ) = fp2;
    tof32x2(pOut->a[6] ) = fp3;
    tof32x2(pOut->a[8] ) = fp4;
    tof32x2(pOut->a[10]) = fp5;
    tof32x2(pOut->a[12]) = fp6;
    tof32x2(pOut->a[14]) = fp7;

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44Mult(MTX44* pOut, const MTX44* __restrict p1, const MTX44* __restrict p2)
{
    // d = a . b;
    //
    // { f0 f4 } = { b00 b01 b02 b03 }
    // { f1 f5 }   { b10 b11 b12 b13 }
    // { f2 f6 }   { b20 b21 b22 b23 }
    // { f3 f7 }   { b30 b31 b32 b33 }

    const f32x2 f0 = __PSQ_LX(p2, offsetof(MTX44, m[0][0]), 0, 0);
    const f32x2 f1 = __PSQ_LX(p2, offsetof(MTX44, m[1][0]), 0, 0);
    const f32x2 f2 = __PSQ_LX(p2, offsetof(MTX44, m[2][0]), 0, 0);
    const f32x2 f3 = __PSQ_LX(p2, offsetof(MTX44, m[3][0]), 0, 0);
    const f32x2 f4 = __PSQ_LX(p2, offsetof(MTX44, m[0][2]), 0, 0);
    const f32x2 f5 = __PSQ_LX(p2, offsetof(MTX44, m[1][2]), 0, 0);
    const f32x2 f6 = __PSQ_LX(p2, offsetof(MTX44, m[2][2]), 0, 0);
    const f32x2 f7 = __PSQ_LX(p2, offsetof(MTX44, m[3][2]), 0, 0);

    f32x2 f8, f9, f10;

    // { d00 d01 d02 d03 } = { f9 f10 } := { a00 a01 a02 a03 } . { f0 f4 }
    //                                                           { f1 f5 }
    //                                                           { f2 f6 }
    //                                                           { f3 f7 }

    f8 = __PSQ_LX(p1, offsetof(MTX44, m[0][0]), 0, 0); // { a00 a01 }
    f9 = __PS_MULS0(f0, f8);
    f10 = __PS_MULS0(f4, f8);
    f9 = __PS_MADDS1(f1, f8, f9);
    f10 = __PS_MADDS1(f5, f8, f10);
    f8 = __PSQ_LX(p1, offsetof(MTX44, m[0][2]), 0, 0); // { a02 a03 }
    f9 = __PS_MADDS0(f2, f8, f9);
    f10 = __PS_MADDS0(f6, f8, f10);
    f9 = __PS_MADDS1(f3, f8, f9);
    f10 = __PS_MADDS1(f7, f8, f10);
    __PSQ_STX(pOut, offsetof(MTX44, m[0][0]), f9, 0, 0);
    __PSQ_STX(pOut, offsetof(MTX44, m[0][2]), f10, 0, 0);

    //                                                           { f0 f4 }
    // { d10 d11 d12 d13 } = { f9 f10 } := { a10 a11 a12 a13 } . { f1 f5 }
    //                                                           { f2 f6 }
    //                                                           { f3 f7 }

    f8 = __PSQ_LX(p1, offsetof(MTX44, m[1][0]), 0, 0); // { a10 a11 }
    f9 = __PS_MULS0(f0, f8);
    f10 = __PS_MULS0(f4, f8);
    f9 = __PS_MADDS1(f1, f8, f9);
    f10 = __PS_MADDS1(f5, f8, f10);
    f8 = __PSQ_LX(p1, offsetof(MTX44, m[1][2]), 0, 0); // { a12 a13 }
    f9 = __PS_MADDS0(f2, f8, f9);
    f10 = __PS_MADDS0(f6, f8, f10);
    f9 = __PS_MADDS1(f3, f8, f9);
    f10 = __PS_MADDS1(f7, f8, f10);
    __PSQ_STX(pOut, offsetof(MTX44, m[1][0]), f9, 0, 0);
    __PSQ_STX(pOut, offsetof(MTX44, m[1][2]), f10, 0, 0);

    //                                                           { f0 f4 }
    //                                                           { f1 f5 }
    // { d20 d21 d22 d23 } = { f9 f10 } := { a20 a21 a22 a23 } . { f2 f6 }
    //                                                           { f3 f7 }

    f8 = __PSQ_LX(p1, offsetof(MTX44, m[2][0]), 0, 0); // { a20 a21 }
    f9 = __PS_MULS0(f0, f8);
    f10 = __PS_MULS0(f4, f8);
    f9 = __PS_MADDS1(f1, f8, f9);
    f10 = __PS_MADDS1(f5, f8, f10);
    f8 = __PSQ_LX(p1, offsetof(MTX44, m[2][2]), 0, 0); // { a22 a23 }
    f9 = __PS_MADDS0(f2, f8, f9);
    f10 = __PS_MADDS0(f6, f8, f10);
    f9 = __PS_MADDS1(f3, f8, f9);
    f10 = __PS_MADDS1(f7, f8, f10);
    __PSQ_STX(pOut, offsetof(MTX44, m[2][0]), f9, 0, 0);
    __PSQ_STX(pOut, offsetof(MTX44, m[2][2]), f10, 0, 0);

    //                                                           { f0 f4 }
    //                                                           { f1 f5 }
    //                                                           { f2 f6 }
    // { d30 d31 d32 d33 } = { f9 f10 } := { a30 a31 a32 a33 } . { f3 f7 }

    f8 = __PSQ_LX(p1, offsetof(MTX44, m[3][0]), 0, 0); // { a30 a31 }
    f9 = __PS_MULS0(f0, f8);
    f10 = __PS_MULS0(f4, f8);
    f9 = __PS_MADDS1(f1, f8, f9);
    f10 = __PS_MADDS1(f5, f8, f10);
    f8 = __PSQ_LX(p1, offsetof(MTX44, m[3][2]), 0, 0); // { a32 a33 }
    f9 = __PS_MADDS0(f2, f8, f9);
    f10 = __PS_MADDS0(f6, f8, f10);
    f9 = __PS_MADDS1(f3, f8, f9);
    f10 = __PS_MADDS1(f7, f8, f10);
    __PSQ_STX(pOut, offsetof(MTX44, m[3][0]), f9, 0, 0);
    __PSQ_STX(pOut, offsetof(MTX44, m[3][2]), f10, 0, 0);

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44MultScale(MTX44* pOut, const MTX44* pM, const VEC3* pS)
{
    // d = m . Mscale(s)
    //
    // d = { m00 m01 m02 m03 } . { sx 0  0  0 }
    //     { m10 m11 m12 m13 }   { 0  sy 0  0 }
    //     { m20 m21 m22 m23 }   { 0  0  sz 0 }
    //     { m30 m31 m32 m33 }   { 0  0  0  1 }
    //
    //   = { sx*m00 sy*m01 sz*m02 m03 }
    //     { sx*m10 sy*m11 sz*m12 m13 }
    //     { sx*m20 sy*m21 sz*m22 m23 }
    //     { sx*m30 sy*m31 sz*m32 m33 }

    // xy = { sx, sy }
    f32x2 xy = __PSQ_LX(pS, offsetof(VEC3, x), 0, 0);

    tof32x2(pOut->f._00) = __PS_MUL(tof32x2(pM->f._00), xy);
    tof32x2(pOut->f._10) = __PS_MUL(tof32x2(pM->f._10), xy);
    tof32x2(pOut->f._20) = __PS_MUL(tof32x2(pM->f._20), xy);
    tof32x2(pOut->f._30) = __PS_MUL(tof32x2(pM->f._30), xy);

    // z1 = { sz, 1 }
    f32x2 z1 = __PSQ_LX(pS, offsetof(VEC3, z), 1, 0);

    tof32x2(pOut->f._02) = __PS_MUL(tof32x2(pM->f._02), z1);
    tof32x2(pOut->f._12) = __PS_MUL(tof32x2(pM->f._12), z1);
    tof32x2(pOut->f._22) = __PS_MUL(tof32x2(pM->f._22), z1);
    tof32x2(pOut->f._32) = __PS_MUL(tof32x2(pM->f._32), z1);

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44MultScale(MTX44* pOut, const VEC3* pS, const MTX44* pM)
{
    // d = Mscale(s) . m
    //
    // d = { sx 0  0  0 } . { m00 m01 m02 m03 }
    //     { 0  sy 0  0 }   { m10 m11 m12 m13 }
    //     { 0  0  sz 0 }   { m20 m21 m22 m23 }
    //     { 0  0  0  1 }   { m30 m31 m32 m33 }
    //
    //   = { sx*m00 sx*m01 sx*m02 sx*m03 }
    //     { sy*m10 sy*m11 sy*m12 sy*m13 }
    //     { sz*m20 sz*m21 sz*m22 sz*m23 }
    //     {    m30    m31    m32    m33 }


    f32x2 xy = tof32x2(pS->x);

    tof32x2(pOut->f._00) = __PS_MULS0(tof32x2(pM->f._00), xy);
    tof32x2(pOut->f._02) = __PS_MULS0(tof32x2(pM->f._02), xy);

    tof32x2(pOut->f._10) = __PS_MULS1(tof32x2(pM->f._10), xy);
    tof32x2(pOut->f._12) = __PS_MULS1(tof32x2(pM->f._12), xy);

    f32x2 zz = __PS_FDUP(pS->z);

    tof32x2(pOut->f._20) = __PS_MUL(tof32x2(pM->f._20), zz);
    tof32x2(pOut->f._22) = __PS_MUL(tof32x2(pM->f._22), zz);

    if (pOut != pM)
    {
        tof32x2(pOut->f._30) = tof32x2(pM->f._30);
        tof32x2(pOut->f._32) = tof32x2(pM->f._32);
    }

    return pOut;
}

} } // namespace internal::intrinsics

#endif // NW_MATH_ENABLE_INTRINSICS

NW_MATH_INLINE VEC4*
VEC3Transform(VEC4* pOut, const MTX44* pM, const VEC3* pV)
{
    return NW_MATH_IMPL_NS::VEC3Transform(pOut, pM, pV);
}

NW_MATH_INLINE VEC3*
VEC3Transform(VEC3* pOut, const MTX44* pM, const VEC3* pV)
{
    return VEC3Transform(pOut, reinterpret_cast<const MTX34*>(pM), pV);
}

// NW_MATH_INLINE VEC3*
// VEC3CalcRPY(VEC3* pOut, const MTX44* pM)
// {
//     f32 tmp = math::FAbs(pM->_20);
//
//     if (1.0f - tmp < math::F_ULP)
//     {
//         pOut->x = 0.f;
//         pOut->y = -math::F_PI / 2.0f * (pM->_20 / tmp);
//         pOut->z = math::Atan2Rad(-pM->_01, -pM->_20 * pM->_02);
//     }
//     else
//     {
//         pOut->x = math::Atan2Rad(pM->_21, pM->_22);
//         pOut->y = math::AsinRad(-pM->_20);
//         pOut->z = math::Atan2Rad(pM->_10, pM->_00);
//     }
//
//     return pOut;
// }

NW_MATH_INLINE MTX44*
MTX44Zero(MTX44* pOut)
{
    pOut->f._00 = pOut->f._01 = pOut->f._02 = pOut->f._03 =
    pOut->f._10 = pOut->f._11 = pOut->f._12 = pOut->f._13 =
    pOut->f._20 = pOut->f._21 = pOut->f._22 = pOut->f._23 =
    pOut->f._30 = pOut->f._31 = pOut->f._32 = pOut->f._33 = 0.f;

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44Identity(MTX44* pOut)
{
    MTX44Copy(pOut, MTX44::Identity());

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44Copy(MTX44* pOut, const MTX44* p)
{
    if (pOut != p)
    {
        *pOut = *p;
    }

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44Add(MTX44* pOut, const MTX44* p1, const MTX44* p2)
{
    return NW_MATH_IMPL_NS::MTX44Add(pOut, p1, p2);
}

NW_MATH_INLINE MTX44*
MTX44Sub(MTX44* pOut, const MTX44* p1, const MTX44* p2)
{
    return NW_MATH_IMPL_NS::MTX44Sub(pOut, p1, p2);
}

NW_MATH_INLINE MTX44*
MTX44Mult(MTX44* pOut, const MTX44* p, f32 f)
{
    return MTX44Mult(pOut, p, f);
}

NW_MATH_INLINE bool
MTX44IsIdentity(const MTX44* p)
{
    return p->f._00 == 1.f && p->f._01 == 0.f && p->f._02 == 0.f && p->f._03 == 0.f &&
           p->f._10 == 0.f && p->f._11 == 1.f && p->f._12 == 0.f && p->f._13 == 0.f &&
           p->f._20 == 0.f && p->f._21 == 0.f && p->f._22 == 1.f && p->f._23 == 0.f &&
           p->f._30 == 0.f && p->f._31 == 0.f && p->f._32 == 0.f && p->f._33 == 1.f;
}

NW_MATH_INLINE MTX44*
MTX44Transpose(MTX44* pOut, const MTX44 *pSrc)
{
    MTX44 tmp;
    const MTX44 *pMtx;

    if (pOut != pSrc)
    {
        pMtx = pSrc;
        pOut->f._00 = pSrc->f._00;
        pOut->f._11 = pSrc->f._11;
        pOut->f._22 = pSrc->f._22;
        pOut->f._33 = pSrc->f._33;
    }
    else
    {
        pMtx = &tmp;
        tmp.f._01 = pSrc->f._01;
        tmp.f._02 = pSrc->f._02;
        tmp.f._03 = pSrc->f._03;
        tmp.f._12 = pSrc->f._12;
        tmp.f._13 = pSrc->f._13;
        tmp.f._23 = pSrc->f._23;
    }

    pOut->f._01 = pSrc->f._10;
    pOut->f._02 = pSrc->f._20;
    pOut->f._03 = pSrc->f._30;
    pOut->f._12 = pSrc->f._21;
    pOut->f._13 = pSrc->f._31;
    pOut->f._23 = pSrc->f._32;

    pOut->f._10 = pMtx->f._01;
    pOut->f._20 = pMtx->f._02;
    pOut->f._30 = pMtx->f._03;
    pOut->f._21 = pMtx->f._12;
    pOut->f._31 = pMtx->f._13;
    pOut->f._32 = pMtx->f._23;

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44PerspectiveRadNew(MTX44* pOut, f32 fovyRad, f32 aspect, f32 n, f32 f)
{
    f32 (*const m)[4] = pOut->m;

    // find the cotangent of half the (YZ) field of view

    const f32 angle = fovyRad * 0.5f;

    const f32 cot = 1.0f / ::std::tan(angle);

    m[0][0] =  cot / aspect;
    m[0][1] =  0.0f;
    m[0][2] =  0.0f;
    m[0][3] =  0.0f;

    m[1][0] =  0.0f;
    m[1][1] =   cot;
    m[1][2] =  0.0f;
    m[1][3] =  0.0f;

    m[2][0] =  0.0f;
    m[2][1] =  0.0f;

    const f32 tmp = -1.0f / (f - n);
    m[2][2] = (f + n) * tmp;
    m[2][3] = (2 * f * n) * tmp;

    m[3][0] =  0.0f;
    m[3][1] =  0.0f;
    m[3][2] = -1.0f;
    m[3][3] =  0.0f;

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44PerspectiveRadOld(MTX44* pOut, f32 fovyRad, f32 aspect, f32 n, f32 f)
{
    f32 (*const m)[4] = pOut->m;

    // find the cotangent of half the (YZ) field of view

    const f32 angle = fovyRad * 0.5f;

    const f32 cot = 1.0f / ::std::tan(angle);

    m[0][0] =  cot / aspect;
    m[0][1] =  0.0f;
    m[0][2] =  0.0f;
    m[0][3] =  0.0f;

    m[1][0] =  0.0f;
    m[1][1] =   cot;
    m[1][2] =  0.0f;
    m[1][3] =  0.0f;

    m[2][0] =  0.0f;
    m[2][1] =  0.0f;

    const f32 tmp = -1.0f / (f - n);
    m[2][2] = f * tmp;
    m[2][3] = f * n * tmp;

    m[3][0] =  0.0f;
    m[3][1] =  0.0f;
    m[3][2] = -1.0f;
    m[3][3] =  0.0f;

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44FrustumNew(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f)
{
    // NOTE: Be careful about "l" vs. "1" below!!!

    f32 (*const m)[4] = pOut->m;
    f32 tmp     =  1.0f / (r - l);
    m[0][0] =  (2*n) * tmp;
    m[0][1] =  0.0f;
    m[0][2] =  (r + l) * tmp;
    m[0][3] =  0.0f;

    tmp     =  1.0f / (t - b);
    m[1][0] =  0.0f;
    m[1][1] =  (2*n) * tmp;
    m[1][2] =  (t + b) * tmp;
    m[1][3] =  0.0f;

    m[2][0] =  0.0f;
    m[2][1] =  0.0f;

    tmp = -1.0f / (f - n);
    m[2][2] = (f + n) * tmp;
    m[2][3] = (2 * f * n) * tmp;

    m[3][0] =  0.0f;
    m[3][1] =  0.0f;
    m[3][2] = -1.0f;
    m[3][3] =  0.0f;

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44FrustumOld(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f)
{
    // NOTE: Be careful about "l" vs. "1" below!!!

    f32 (*const m)[4] = pOut->m;
    f32 tmp     =  1.0f / (r - l);
    m[0][0] =  (2*n) * tmp;
    m[0][1] =  0.0f;
    m[0][2] =  (r + l) * tmp;
    m[0][3] =  0.0f;

    tmp     =  1.0f / (t - b);
    m[1][0] =  0.0f;
    m[1][1] =  (2*n) * tmp;
    m[1][2] =  (t + b) * tmp;
    m[1][3] =  0.0f;

    m[2][0] =  0.0f;
    m[2][1] =  0.0f;

    tmp = -1.0f / (f - n);

    m[2][2] = f * tmp;
    m[2][3] = f * n * tmp;

    m[3][0] =  0.0f;
    m[3][1] =  0.0f;
    m[3][2] = -1.0f;
    m[3][3] =  0.0f;

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44OrthoNew(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f)
{
    // NOTE: Be careful about "l" vs. "1" below!!!

    f32 (*const m)[4] = pOut->m;
    f32 tmp     =  1.0f / (r - l);
    m[0][0] =  2.0f * tmp;
    m[0][1] =  0.0f;
    m[0][2] =  0.0f;
    m[0][3] = -(r + l) * tmp;

    tmp     =  1.0f / (t - b);
    m[1][0] =  0.0f;
    m[1][1] =  2.0f * tmp;
    m[1][2] =  0.0f;
    m[1][3] = -(t + b) * tmp;

    m[2][0] =  0.0f;
    m[2][1] =  0.0f;

    tmp     =  -1.0f / (f - n);
    m[2][2] = 2.0f * tmp;
    m[2][3] = (f + n) * tmp;

    m[3][0] =  0.0f;
    m[3][1] =  0.0f;
    m[3][2] =  0.0f;
    m[3][3] =  1.0f;

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44OrthoOld(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f)
{
    // NOTE: Be careful about "l" vs. "1" below!!!

    f32 (*const m)[4] = pOut->m;
    f32 tmp     =  1.0f / (r - l);
    m[0][0] =  2.0f * tmp;
    m[0][1] =  0.0f;
    m[0][2] =  0.0f;
    m[0][3] = -(r + l) * tmp;

    tmp     =  1.0f / (t - b);
    m[1][0] =  0.0f;
    m[1][1] =  2.0f * tmp;
    m[1][2] =  0.0f;
    m[1][3] = -(t + b) * tmp;

    m[2][0] =  0.0f;
    m[2][1] =  0.0f;

    tmp     =  -1.0f / (f - n);

    m[2][2] = tmp;
    m[2][3] = n * tmp;

    m[3][0] =  0.0f;
    m[3][1] =  0.0f;
    m[3][2] =  0.0f;
    m[3][3] =  1.0f;

    return pOut;
}

namespace {
    inline MTX44*
    MTX44Pivot( MTX44* pOut, PivotDirection pivot )
    {
        const f32 PIVOT_ROTATION_SIN_COS[ PIVOT_NUM ][ 2 ] =
        {
            { 0.0f,  1.0f }, // NONE
            { 0.0f,  1.0f }, // TO_UP
            { -1.0f, 0.0f }, // TO_RIGHT
            { 0.0f, -1.0f }, // TO_BOTTOM
            { 1.0f,  0.0f }, // TO_LEFT
        };

        if ( pivot == PIVOT_NONE )
        {
            return pOut;
        }

        f32 sin = PIVOT_ROTATION_SIN_COS[ pivot ][ 0 ];
        f32 cos = PIVOT_ROTATION_SIN_COS[ pivot ][ 1 ];

        f32 (*const m)[4] = pOut->m;

        if ( sin == 0.0f )
        {
            m[0][0] = cos * m[0][0];
            m[0][1] = cos * m[0][1];
            m[0][2] = cos * m[0][2];
            m[0][3] = cos * m[0][3];

            m[1][0] = cos * m[1][0];
            m[1][1] = cos * m[1][1];
            m[1][2] = cos * m[1][2];
            m[1][3] = cos * m[1][3];
        }
        else // if ( cos == 0.0f )
        {
            f32 tmp = m[0][0];
            m[0][0] = -sin * m[1][0];
            m[1][0] = sin * tmp;

            tmp = m[0][1];
            m[0][1] = -sin * m[1][1];
            m[1][1] = sin * tmp;

            tmp = m[0][2];
            m[0][2] = -sin * m[1][2];
            m[1][2] = sin * tmp;

            tmp = m[0][3];
            m[0][3] = -sin * m[1][3];
            m[1][3] = sin * tmp;
        }

        return pOut;
    }
} // namespace (unnamed)

NW_MATH_INLINE MTX44*
MTX44FrustumPivot(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, PivotDirection pivot)
{
    nw::math::MTX44Frustum( pOut, l, r, b, t, n, f );
    MTX44Pivot( pOut, pivot );

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44OrthoPivot(MTX44* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, PivotDirection pivot)
{
    nw::math::MTX44Ortho( pOut, l, r, b, t, n, f );
    MTX44Pivot( pOut, pivot );

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44PerspectivePivotRad(MTX44* pOut, f32 fovy, f32 aspect, f32 n, f32 f, PivotDirection pivot)
{
    nw::math::MTX44PerspectiveRad( pOut, fovy, aspect, n, f );
    MTX44Pivot( pOut, pivot );

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44Mult(MTX44* pOut, const MTX44* __restrict p1, const MTX44* __restrict p2)
{
    return NW_MATH_IMPL_NS::MTX44Mult(pOut, p1, p2);
}

NW_MATH_INLINE MTX44*
MTX44MultArray(MTX44* pOut, const MTX44* __restrict p1, const MTX44* __restrict pSrc, s32 count)
{
    MTX44* pOutBase = pOut;

    for ( s32 i = 0 ; i < count ; i++ )
    {
        nw::math::MTX44Mult(pOut, p1, pSrc);

        pSrc++;
        pOut++;
    }

    return pOutBase;
}

namespace {
    inline void SwapF(f32 &a, f32 &b)
    {
        f32 tmp;
        tmp = a;
        a = b;
        b = tmp;
    }
} // namespace (unnamed)

NW_MATH_INLINE u32
MTX44Inverse(MTX44* pOut, const MTX44* p)
{
    MTX44 mTmp;
    f32 (*src)[4];
    f32 (*inv)[4];
    f32   w;

    nw::math::MTX44Copy(&mTmp, p);
    nw::math::MTX44Identity(pOut);

    src = mTmp.m;
    inv = pOut->m;

    for (int i = 0; i < 4; ++i)
    {
        f32 max = 0.0f;
        s32 swp = i;

        // ---- partial pivoting -----
        for(int k = i ; k < 4 ; k++ )
        {
            f32 ftmp;
            ftmp = ::std::fabs(src[k][i]);
            if ( ftmp > max )
            {
                max = ftmp;
                swp = k;
            }
        }

        // check singular matrix
        //(or can't solve inverse matrix with this algorithm)
        if ( max == 0.0f )
        {
            return 0;
        }

        // swap row
        if ( swp != i )
        {
            for (int k = 0; k < 4; k++)
            {
                SwapF(src[i][k], src[swp][k]);
                SwapF(inv[i][k], inv[swp][k]);
            }
        }

        // ---- pivoting end ----

        w = 1.0f / src[i][i];
        for (int j = 0; j < 4; ++j)
        {
            src[i][j] *= w;
            inv[i][j] *= w;
        }

        for (int k = 0; k < 4; ++k )
        {
            if ( k == i )
                continue;

            w = src[k][i];
            for (int j = 0; j < 4; ++j)
            {
                src[k][j] -= src[i][j] * w;
                inv[k][j] -= inv[i][j] * w;
            }
        }
    }

    return 1;
}

static NW_MATH_INLINE MTX44*
MTX44RotAxisRad_( MTX44* pOut, const VEC3 *pAxis, f32 fRad )
{
    VEC3 vN;
    f32 s, c;             // sinTheta, cosTheta
    f32 t;                // ( 1 - cosTheta )
    f32 x, y, z;          // x, y, z components of normalized axis
    f32 xSq, ySq, zSq;    // x, y, z squared


    f32 (*const m)[4] = pOut->m;

    s = ::std::sin(fRad);
    c = ::std::cos(fRad);
    t = 1.0f - c;

    VEC3Normalize( &vN, pAxis );

    x = vN.x;
    y = vN.y;
    z = vN.z;

    xSq = x * x;
    ySq = y * y;
    zSq = z * z;

    m[0][0] = ( t * xSq )   + ( c );
    m[0][1] = ( t * x * y ) - ( s * z );
    m[0][2] = ( t * x * z ) + ( s * y );
    m[0][3] = 0.0f;

    m[1][0] = ( t * x * y ) + ( s * z );
    m[1][1] = ( t * ySq )   + ( c );
    m[1][2] = ( t * y * z ) - ( s * x );
    m[1][3] = 0.0f;

    m[2][0] = ( t * x * z ) - ( s * y );
    m[2][1] = ( t * y * z ) + ( s * x );
    m[2][2] = ( t * zSq )   + ( c );
    m[2][3] = 0.0f;

    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44RotAxisIdx(MTX44* pOut, const VEC3* pAxis, u32 idx)
{
    MTX44RotAxisRad_(pOut, pAxis, NW_MATH_IDX_TO_RAD(idx));
    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44RotXYZIdx(MTX44* pOut, u32 idxX, u32 idxY, u32 idxZ)
{
    f32 sinx, cosx;
    f32 siny, cosy;
    f32 sinz, cosz;
    f32 f1, f2;

    SinCosIdx(&sinx, &cosx, idxX);
    SinCosIdx(&siny, &cosy, idxY);
    SinCosIdx(&sinz, &cosz, idxZ);

    pOut->f._20 = -siny;
    pOut->f._00 = cosz * cosy;
    pOut->f._10 = sinz * cosy;
    pOut->f._21 = cosy * sinx;
    pOut->f._22 = cosy * cosx;

    f1 = cosx * sinz;
    f2 = sinx * cosz;

    pOut->f._01 = f2 * siny - f1;
    pOut->f._12 = f1 * siny - f2;

    f1 = sinx * sinz;
    f2 = cosx * cosz;
    pOut->f._02 = f2 * siny + f1;
    pOut->f._11 = f1 * siny + f2;

    pOut->f._03 = 0.f;
    pOut->f._13 = 0.f;
    pOut->f._23 = 0.f;

    pOut->f._30 = 0.0f;
    pOut->f._31 = 0.0f;
    pOut->f._32 = 0.0f;
    pOut->f._33 = 1.0f;

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44Scale(MTX44* pOut, const VEC3* pS)
{
    f32 (*const m)[4] = pOut->m;

    m[0][0] = pS->x;    m[0][1] = 0.0f;  m[0][2] = 0.0f;  m[0][3] = 0.0f;
    m[1][0] = 0.0f;     m[1][1] = pS->y; m[1][2] = 0.0f;  m[1][3] = 0.0f;
    m[2][0] = 0.0f;     m[2][1] = 0.0f;  m[2][2] = pS->z; m[2][3] = 0.0f;
    m[3][0] = 0.0f;     m[3][1] = 0.0f;  m[3][2] = 0.0f; m[3][3] = 1.0f;

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44MultScale(MTX44* pOut, const MTX44* pM, const VEC3* pS)
{
    return NW_MATH_IMPL_NS::MTX44MultScale(pOut, pM, pS);
}

NW_MATH_INLINE MTX44*
MTX44MultScale(MTX44* pOut, const VEC3* pS, const MTX44* pM)
{
    return NW_MATH_IMPL_NS::MTX44MultScale(pOut, pS, pM);
}

NW_MATH_INLINE MTX44*
MTX44Translate(MTX44* pOut, const VEC3* pT)
{
    f32 (*const m)[4] = pOut->m;

    m[0][0] = 1.0f;  m[0][1] = 0.0f;  m[0][2] = 0.0f;  m[0][3] = pT->x;
    m[1][0] = 0.0f;  m[1][1] = 1.0f;  m[1][2] = 0.0f;  m[1][3] = pT->y;
    m[2][0] = 0.0f;  m[2][1] = 0.0f;  m[2][2] = 1.0f;  m[2][3] = pT->z;
    m[3][0] = 0.0f;  m[3][1] = 0.0f;  m[3][2] = 0.0f;  m[3][3] = 1.0f;

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44MultTranslate(MTX44* pOut, const VEC3* pT, const MTX44* pM)
{
    const f32 (*const src)[4] = pM->m;
    f32 (*const dst)[4] = pOut->m;

    if ( src != dst )
    {
        dst[0][0] = src[0][0];    dst[0][1] = src[0][1];    dst[0][2] = src[0][2];
        dst[1][0] = src[1][0];    dst[1][1] = src[1][1];    dst[1][2] = src[1][2];
        dst[2][0] = src[2][0];    dst[2][1] = src[2][1];    dst[2][2] = src[2][2];
    }

    dst[0][3] = src[0][3] + pT->x;
    dst[1][3] = src[1][3] + pT->y;
    dst[2][3] = src[2][3] + pT->z;

    return pOut;
}

NW_MATH_INLINE MTX44*
MTX44MultTranslate(MTX44* pOut, const MTX44* pM, const VEC3* pT)
{
    // pOut = pM * pT
    if (pOut != pM)
    {
        (void)MTX44Copy(pOut, pM);
    }

    VEC4 tmp;
    VEC3Transform(&tmp, pM, pT);

    pOut->f._03 = tmp.x;
    pOut->f._13 = tmp.y;
    pOut->f._23 = tmp.z;

    return pOut;
}

} } // namespace nw::math

#endif

#endif
