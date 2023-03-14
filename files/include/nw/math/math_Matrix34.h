#ifndef NW_MATH_MATRIX34_H_
#define NW_MATH_MATRIX34_H_

#include <cstring>
#include <nw/math/math_Config.h>

namespace nw { namespace math {

struct MTX34;

namespace internal { namespace standard {

    VEC3* VEC3Transform(VEC3* pOut, const MTX34* pM, const VEC3* pV);
    MTX34* MTX34Add(MTX34* pOut, const MTX34* p1, const MTX34* p2);
    MTX34* MTX34Sub(MTX34* pOut, const MTX34* p1, const MTX34* p2);
    MTX34* MTX34MultScale(MTX34* pOut, const MTX34* pM, const VEC3* pS);
    MTX34* MTX34MultScale(MTX34* pOut, const VEC3* pS, const MTX34* pM);
    MTX34* MTX34Mult(MTX34* pOut, const MTX34* p, f32 f);
    MTX34* MTX34MAdd(MTX34* pOut, f32 t, const MTX34* p1, const MTX34* p2);
    MTX34* MTX34Mult(MTX34* pOut, const MTX34* p1, const MTX34* p2);
    u32 MTX34Inverse(MTX34* pOut, const MTX34* p);
    u32 MTX34InvTranspose(MTX34* pOut, const MTX34* p);

} } // namespace internal::standard

namespace internal { namespace intrinsics {

    VEC3* VEC3Transform(VEC3* pOut, const MTX34* pM, const VEC3* pV);
    MTX34* MTX34Add(MTX34* pOut, const MTX34* p1, const MTX34* p2);
    MTX34* MTX34Sub(MTX34* pOut, const MTX34* p1, const MTX34* p2);
    MTX34* MTX34MultScale(MTX34* pOut, const MTX34* pM, const VEC3* pS);
    MTX34* MTX34MultScale(MTX34* pOut, const VEC3* pS, const MTX34* pM);
    MTX34* MTX34Mult(MTX34* pOut, const MTX34* p, f32 f);
    MTX34* MTX34MAdd(MTX34* pOut, f32 t, const MTX34* p1, const MTX34* p2);
    MTX34* MTX34Mult(MTX34* pOut, const MTX34* p1, const MTX34* p2);
    u32 MTX34Inverse(MTX34* pOut, const MTX34* p);
    u32 MTX34InvTranspose(MTX34* pOut, const MTX34* p);

} } // namespace internal::intrinsics

NW_MATH_INLINE MTX34* MTX34Zero(MTX34* pOut);
NW_MATH_INLINE bool MTX34IsIdentity(const MTX34* p);
NW_MATH_INLINE MTX34* MTX34Identity(MTX34* pOut);
// NW_MATH_INLINE MTX34* MTX34Copy(MTX34* pOut, const MTX34* p); <-- Redeclaration below

NW_MATH_INLINE MTX34* MTX34Add(MTX34* pOut, const MTX34* p1, const MTX34* p2);
NW_MATH_INLINE MTX34* MTX34Sub(MTX34* pOut, const MTX34* p1, const MTX34* p2);
NW_MATH_INLINE MTX34* MTX34Mult(MTX34* pOut, const MTX34* p, f32 f);
// NW_MATH_INLINE MTX34* MTX34Mult(MTX34* pOut, const MTX34* p1, const MTX34* p2); <-- Redeclaration below
NW_MATH_INLINE MTX34* MTX34MAdd(MTX34* pOut, f32 t, const MTX34* p1, const MTX34* p2);

NW_MATH_INLINE MTX34* MTX34MultArray(MTX34* pOut, const MTX34* p1, const MTX34* pSrc, s32 count);
NW_MATH_INLINE u32    MTX34Inverse(MTX34* pOut, const MTX34* p);
NW_MATH_INLINE MTX34* MTX34Transpose(MTX34* pOut, const MTX34* p);
NW_MATH_INLINE u32    MTX34InvTranspose(MTX34* pOut, const MTX34* p);

NW_MATH_INLINE MTX34* MTX34LookAt(MTX34* pOut, const VEC3* pCamPos, const VEC3* pCamUp, const VEC3* pTarget);
NW_MATH_INLINE MTX34* MTX34LookAt(MTX34* pOut, const VEC3* pCamPos, f32 twist, const VEC3* pTarget);
NW_MATH_INLINE MTX34* MTX34CameraRotate(MTX34* pOut, const VEC3* pCamPos, const VEC3* pCamRotate);

NW_MATH_INLINE MTX34* MTX34TextureProjectionFrustum(MTX34* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT);
NW_MATH_INLINE MTX34* MTX34TextureProjectionPerspective(MTX34* pOut, f32 fovy, f32 aspect, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT);
NW_MATH_INLINE MTX34* MTX34TextureProjectionOrtho(MTX34* pOut, f32 l, f32 r, f32 b, f32 t, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT);

NW_MATH_INLINE MTX34* MTX34RotXYZIdx(MTX34* pOut, u32 idxX, u32 idxY, u32 idxZ);
NW_MATH_INLINE MTX34* MTX34RotXYZTranslateIdx(MTX34* pOut, u32 idxX, u32 idxY, u32 idxZ, const VEC3* pT);
NW_MATH_INLINE MTX34* MTX34RotAxisIdx(MTX34* pOut, const VEC3* pAxis, u32 idx);

NW_MATH_INLINE MTX34* MTX34Scale(MTX34* pOut, const VEC3* pS);
NW_MATH_INLINE MTX34* MTX34MultScale(MTX34* pOut, const MTX34* pM, const VEC3* pS);
NW_MATH_INLINE MTX34* MTX34MultScale(MTX34* pOut, const VEC3* pS, const MTX34* pM);

NW_MATH_INLINE MTX34* MTX34Translate(MTX34* pOut, const VEC3* pT);
NW_MATH_INLINE MTX34* MTX34MultTranslate(MTX34* pOut, const MTX34* pM, const VEC3* pT);
NW_MATH_INLINE MTX34* MTX34MultTranslate(MTX34* pOut, const VEC3* pT, const MTX34* pM);

NW_MATH_INLINE MTX34* MTX34MakeSRT(MTX34* pOut, const VEC3* pS, const VEC3* pR, const VEC3* pT);
NW_MATH_INLINE MTX34* MTX34MakeST(MTX34* pOut, const VEC3* pS, const VEC3* pT);
NW_MATH_INLINE MTX34* MTX34MakeS(MTX34* pOut, const VEC3* pS);

NW_MATH_INLINE MTX34* QUATToMTX34(MTX34* pOut, const QUAT* p);

NW_FORCE_INLINE MTX34* MTX34Copy(MTX34* pOut, const MTX34* p);
NW_FORCE_INLINE MTX34* MTX34Mult(MTX34* pOut, const MTX34* p1, const MTX34* p2);

inline MTX34*
MTX34RotXYZRad(MTX34* pOut, f32 fRadX, f32 fRadY, f32 fRadZ)
{
    return MTX34RotXYZIdx(pOut, NW_MATH_RAD_TO_IDX(fRadX), NW_MATH_RAD_TO_IDX(fRadY), NW_MATH_RAD_TO_IDX(fRadZ));
}

inline MTX34*
MTX34RotXYZDeg(MTX34* pOut, f32 fDegX, f32 fDegY, f32 fDegZ)
{
    return MTX34RotXYZIdx(pOut, NW_MATH_DEG_TO_IDX(fDegX), NW_MATH_DEG_TO_IDX(fDegY), NW_MATH_DEG_TO_IDX(fDegZ));
}

inline MTX34*
MTX34RotAxisRad(MTX34* pOut, const VEC3* pAxis, f32 fRad)
{
    return MTX34RotAxisIdx(pOut, pAxis, NW_MATH_RAD_TO_IDX(fRad));
}

inline MTX34*
MTX34RotAxisDeg(MTX34* pOut, const VEC3* pAxis, f32 fDeg)
{
    return MTX34RotAxisIdx(pOut, pAxis, NW_MATH_DEG_TO_IDX(fDeg));
}
struct MTX34_
{
    struct BaseData
    {
        f32 _00, _01, _02, _03;
        f32 _10, _11, _12, _13;
        f32 _20, _21, _22, _23;
    };
    union
    {
        struct
        {
            f32 _00, _01, _02, _03;
            f32 _10, _11, _12, _13;
            f32 _20, _21, _22, _23;
        };
        BaseData f;
        f32 m[3][4];
        f32 a[12];
        VEC4_ v[3];
    };
};

struct MTX34 : public MTX34_
{
public:
    static const int ROW_COUNT = 3;
    static const int COLUMN_COUNT = 4;

    static const MTX34& Identity()
    {
        static const MTX34 identity(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f);

        return identity;
    }

    typedef MTX34 self_type;
    typedef f32   value_type;
public:
    MTX34() {}

    explicit MTX34(const f32* p) { (void)MTX34Copy(this, (MTX34*)p); }

    MTX34(const MTX34& rhs) { (void)MTX34Copy(this, &rhs); }

    MTX34(f32 x00, f32 x01, f32 x02, f32 x03,
          f32 x10, f32 x11, f32 x12, f32 x13,
          f32 x20, f32 x21, f32 x22, f32 x23)
    {
        f._00 = x00; f._01 = x01; f._02 = x02; f._03 = x03;
        f._10 = x10; f._11 = x11; f._12 = x12; f._13 = x13;
        f._20 = x20; f._21 = x21; f._22 = x22; f._23 = x23;
    }


    operator f32*() { return this->a; }
    operator const f32*() const { return this->a; }

    f32* ToF32() { return this->a; }
    const f32* ToF32() const { return this->a; }

    template <typename FromPtr>
    static MTX34* CastFrom(FromPtr* fromPtr)
    {
        return reinterpret_cast<MTX34*>( fromPtr );
    }

    template <typename FromPtr>
    static const MTX34* CastFrom(const FromPtr* fromPtr)
    {
        return reinterpret_cast<const MTX34*>( fromPtr );
    }

    template <typename FromPtr>
    static MTX34& CastFrom(FromPtr& fromPtr)
    {
        return *reinterpret_cast<MTX34*>( &fromPtr );
    }

    template <typename FromPtr>
    static const MTX34& CastFrom(const FromPtr& fromPtr)
    {
        return *reinterpret_cast<const MTX34*>( &fromPtr );
    }

    VEC4& GetRow(int index)
    {
        return *reinterpret_cast<VEC4*>(&this->v[index]);
    }

    const VEC4& GetRow(int index) const
    {
        return *reinterpret_cast<const VEC4*>(&this->v[index]);
    }

    VEC3 GetColumn(int index) const
    {
        VEC3 column;
        column.x = this->m[0][index];
        column.y = this->m[1][index];
        column.z = this->m[2][index];
        return column;
    }

    void SetColumn(int index, const VEC3& column)
    {
        this->m[0][index] = column.x;
        this->m[1][index] = column.y;
        this->m[2][index] = column.z;
    }

    self_type& operator += (const self_type& rhs) { return *MTX34Add(this, this, &rhs); }
    self_type& operator -= (const self_type& rhs) { return *MTX34Sub(this, this, &rhs); }

    self_type& operator *= (f32 f) { return *MTX34Mult(this, this, f); }
    self_type& operator /= (f32 f) { return operator*=(1.f / f); }

    self_type operator + () const { return *this; }
    self_type operator - () const
    {
        return MTX34(-f._00, -f._01, -f._02, -f._03,
                     -f._10, -f._11, -f._12, -f._13,
                     -f._20, -f._21, -f._22, -f._23);
    }

    self_type operator + (const self_type& rhs) const { MTX34 tmp; return *MTX34Add(&tmp, this, &rhs); }
    self_type operator - (const self_type& rhs) const { MTX34 tmp; return *MTX34Sub(&tmp, this, &rhs); }

    self_type operator * (f32 f) const { MTX34 tmp; return *MTX34Mult(&tmp, this, f); }
    self_type operator / (f32 f) const { return *this * (1.f / f); }

    self_type& Transpose() { return *MTX34Transpose(this, this); }

    self_type& SetInverse( const MTX34& mtx )
    {
        MTX34Inverse(this, &mtx); return *this;
    }

    self_type& Inverse()
    {
        MTX34Inverse(this, this); return *this;
    }

    self_type& SetMult( const MTX34& lhs, const MTX34& rhs )
    {
        return *MTX34Mult( this, &lhs, &rhs );
    }

    self_type& SetIdentity() { return *MTX34Identity(this); }

    self_type& SetScale(const VEC3& scale) { return *MTX34Scale(this, &scale); }

    self_type& SetTranslate(const VEC3& translate)
    {
        return *MTX34Translate(this, &translate);
    }

    self_type& SetRotateXyz(const VEC3& rotate)
    {
        return *MTX34RotXYZRad(this, rotate.x, rotate.y, rotate.z);
    }

    self_type& SetRotate(const VEC3& axis, f32 theta)
    {
        return *MTX34RotAxisRad(this, &axis, theta);
    }

    self_type& SetRotate(const QUAT& quaternion)
    {
        return *QUATToMTX34(this, &quaternion);
    }

    self_type& SetLookAt(const VEC3& camPos, const VEC3& camUp, const VEC3& target)
    {
        return *MTX34LookAt(this, &camPos, &camUp, &target);
    }

    self_type& SetLookAt(const VEC3& camPos, f32 twist, const VEC3& target)
    {
        return *MTX34LookAt(this, &camPos, twist, &target);
    }

    self_type& SetCameraRotate(const VEC3& camPos, const VEC3& camRotate)
    {
        return *MTX34CameraRotate(this, &camPos, &camRotate);
    }

    self_type& SetTextureProjectionFrustum(f32 l, f32 r, f32 b, f32 t, f32 n, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT)
    {
        return *MTX34TextureProjectionFrustum(this, l, r, b, t, n, scaleS, scaleT, translateS, translateT);
    }

    self_type& SetTextureProjectionPerspective(f32 fovy, f32 aspect, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT)
    {
        return *MTX34TextureProjectionPerspective(this, fovy, aspect, scaleS, scaleT, translateS, translateT);
    }

    self_type& SetTextureProjectionOrtho(f32 l, f32 r, f32 b, f32 t, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT)
    {
        return *MTX34TextureProjectionOrtho(this, l, r, b, t, scaleS, scaleT, translateS, translateT);
    }

    self_type& SetSRTMtx(const VEC3& s, const VEC3& r, const VEC3& t)
    {
        return *MTX34MakeSRT(this, &s, &r, &t);
    }

    self_type& SetSTMtx(const VEC3& s, const VEC3& t)
    {
        return *MTX34MakeST(this, &s, &t);
    }

    self_type& SetSMtx(const VEC3& s)
    {
        return *MTX34MakeS(this, &s);
    }

    bool operator == (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(MTX34)) == 0; }
    bool operator != (const self_type& rhs) const { return ::std::memcmp(this, &rhs, sizeof(MTX34)) != 0; }

    bool IsIdentity() const { return MTX34IsIdentity(this); }
};

typedef struct MTX34 Matrix34;

inline MTX34 operator * (f32 f, const MTX34& rhs)
{
    MTX34 tmp;
    (void)MTX34Mult(&tmp, &rhs, f);
    return tmp;
}

NW_FORCE_INLINE MTX34*
MTX34Copy(MTX34* pOut, const MTX34* p)
{
    if ( p != pOut )
    {
        *pOut = *p;
    }

    return pOut;
}

NW_INLINE MTX34*
MTX34Mult(MTX34* pOut, const MTX34* p1, const MTX34* p2)
{
    return NW_MATH_IMPL_NS::MTX34Mult(pOut, p1, p2);
}

} } // namespace nw::math

namespace nw { namespace math {

inline bool MTX34IsIdentity(const MTX34& m) { return MTX34IsIdentity( &m ); }

inline MTX34* MTX34Add(MTX34* pOut, const MTX34& m1, const MTX34& m2) { return MTX34Add( pOut, &m1, &m2 ); }
inline MTX34* MTX34Sub(MTX34* pOut, const MTX34& m1, const MTX34& m2) { return MTX34Sub( pOut, &m1, &m2 ); }
inline MTX34* MTX34Mult(MTX34* pOut, const MTX34& m, f32 f) { return MTX34Mult( pOut, &m, f ); }
inline MTX34* MTX34Mult(MTX34* pOut, const MTX34& m1, const MTX34& m2) { return MTX34Mult( pOut, &m1, &m2 ); }
inline MTX34* MTX34MAdd(MTX34* pOut, f32 t, const MTX34& m1, const MTX34& m2) { return MTX34MAdd( pOut, t, &m1, &m2 ); }

inline MTX34* MTX34Copy(MTX34* pOut, const MTX34& m) { return MTX34Copy( pOut, &m ); }
inline MTX34* MTX34MultArray(MTX34* pOut, const MTX34& m1, const MTX34* pSrc, s32 count) { return MTX34MultArray( pOut, m1, pSrc, count ); }
inline u32    MTX34Inverse(MTX34* pOut, const MTX34& m) { return MTX34Inverse( pOut, &m ); }
inline MTX34* MTX34Transpose(MTX34* pOut, const MTX34& m) { return MTX34Transpose( pOut, &m ); }
inline u32    MTX34InvTranspose(MTX34* pOut, const MTX34& m) { return MTX34InvTranspose( pOut, &m ); }

inline MTX34* MTX34LookAt(MTX34* pOut, const VEC3& vCamPos, const VEC3& vCamUp, const VEC3& vTarget) { return MTX34LookAt( pOut, &vCamPos, &vCamUp, &vTarget ); }
inline MTX34* MTX34LookAt(MTX34* pOut, const VEC3& vCamPos, f32 twist, const VEC3& vTarget) { return MTX34LookAt( pOut, &vCamPos, twist, &vTarget ); }
inline MTX34* MTX34CameraRotate(MTX34* pOut, const VEC3& vCamPos, const VEC3& vCamRotate) { return MTX34CameraRotate( pOut, &vCamPos, &vCamRotate ); }

inline MTX34* MTX34RotXYZTranslateIdx(MTX34* pOut, u32 idxX, u32 idxY, u32 idxZ, const VEC3& vT) { return MTX34RotXYZTranslateIdx( pOut, idxX, idxY, idxZ, &vT ); }
inline MTX34* MTX34RotAxisIdx(MTX34* pOut, const VEC3& vAxis, u32 idx) { return MTX34RotAxisIdx( pOut, &vAxis, idx ); }
inline MTX34* MTX34RotAxisRad(MTX34* pOut, const VEC3& vAxis, f32 fRad) { return MTX34RotAxisRad( pOut, &vAxis, fRad ); }
inline MTX34* MTX34RotAxisDeg(MTX34* pOut, const VEC3& vAxis, f32 fDeg) { return MTX34RotAxisDeg( pOut, &vAxis, fDeg ); }

inline MTX34* MTX34Scale(MTX34* pOut, const VEC3& vS) { return MTX34Scale( pOut, &vS ); }
inline MTX34* MTX34MultScale(MTX34* pOut, const MTX34& m, const VEC3& vS) { return MTX34MultScale( pOut, &m, &vS ); }
inline MTX34* MTX34MultScale(MTX34* pOut, const VEC3& vS, const MTX34& m) { return MTX34MultScale( pOut, &vS, &m ); }

inline MTX34* MTX34Translate(MTX34* pOut, const VEC3& vT) { return MTX34Translate( pOut, &vT ); }
inline MTX34* MTX34MultTranslate(MTX34* pOut, const MTX34& m, const VEC3& vT) { return MTX34MultTranslate( pOut, &m, &vT ); }
inline MTX34* MTX34MultTranslate(MTX34* pOut, const VEC3& vT, const MTX34& m) { return MTX34MultTranslate( pOut, &vT, &m ); }

inline MTX34* MTX34MakeSRT(MTX34* pOut, const VEC3& s, const VEC3& r, const VEC3& t) { return MTX34MakeSRT( pOut, &s, &r, &t ); }
inline MTX34* MTX34MakeST(MTX34* pOut, const VEC3& s, const VEC3& t) { return MTX34MakeST( pOut, &s, &t ); }
inline MTX34* MTX34MakeS(MTX34* pOut, const VEC3& s) { return MTX34MakeS( pOut, &s ); }

inline MTX34* QUATToMTX34(MTX34* pOut, const QUAT& q) { return QUATToMTX34( pOut, &q ); }

} } // namespace nw::math

#if defined(NW_MATH_AS_INLINE)

#include <cmath>
#include <nw/math/math_Vector3.h>

namespace nw { namespace math {

namespace internal { namespace standard {

NW_MATH_INLINE VEC3*
VEC3Transform(VEC3* pOut, const MTX34* __restrict pM, const VEC3* __restrict pV)
{
    const f32 x = pM->f._00 * pV->x + pM->f._01 * pV->y + pM->f._02 * pV->z + pM->f._03;
    const f32 y = pM->f._10 * pV->x + pM->f._11 * pV->y + pM->f._12 * pV->z + pM->f._13;
    const f32 z = pM->f._20 * pV->x + pM->f._21 * pV->y + pM->f._22 * pV->z + pM->f._23;

    pOut->x = x;
    pOut->y = y;
    pOut->z = z;

    return pOut;
}


NW_MATH_INLINE MTX34*
MTX34Add(MTX34* pOut, const MTX34* p1, const MTX34* p2)
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

    return pOut;
}


NW_MATH_INLINE MTX34*
MTX34Sub(MTX34* pOut, const MTX34* p1, const MTX34* p2)
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

    return pOut;
}


NW_MATH_INLINE MTX34*
MTX34Mult(MTX34* pOut, const MTX34* p, f32 f)
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

    return pOut;
}


NW_MATH_INLINE MTX34*
MTX34MultScale(MTX34* pOut, const MTX34* pM, const VEC3* pS)
{
    pOut->f._00 = pM->f._00 * pS->x;
    pOut->f._10 = pM->f._10 * pS->x;
    pOut->f._20 = pM->f._20 * pS->x;

    pOut->f._01 = pM->f._01 * pS->y;
    pOut->f._11 = pM->f._11 * pS->y;
    pOut->f._21 = pM->f._21 * pS->y;

    pOut->f._02 = pM->f._02 * pS->z;
    pOut->f._12 = pM->f._12 * pS->z;
    pOut->f._22 = pM->f._22 * pS->z;

    if (pOut != pM)
    {
        pOut->f._03 = pM->f._03;
        pOut->f._13 = pM->f._13;
        pOut->f._23 = pM->f._23;
    }

    return pOut;
}


NW_MATH_INLINE MTX34*
MTX34MultScale(MTX34* pOut, const VEC3* __restrict pS, const MTX34* pM)
{
    const f32 (*const src)[4] = pM->m;
    f32 (*const dst)[4] = pOut->m;

    dst[0][0] = src[0][0] * pS->x;     dst[0][1] = src[0][1] * pS->x;
    dst[0][2] = src[0][2] * pS->x;     dst[0][3] = src[0][3] * pS->x;

    dst[1][0] = src[1][0] * pS->y;     dst[1][1] = src[1][1] * pS->y;
    dst[1][2] = src[1][2] * pS->y;     dst[1][3] = src[1][3] * pS->y;

    dst[2][0] = src[2][0] * pS->z;     dst[2][1] = src[2][1] * pS->z;
    dst[2][2] = src[2][2] * pS->z;     dst[2][3] = src[2][3] * pS->z;

    return pOut;
}


NW_MATH_INLINE MTX34*
MTX34MAdd(MTX34* pOut, f32 t, const MTX34* p1, const MTX34* p2)
{
    pOut->f._00 = t * p1->f._00 + p2->f._00;
    pOut->f._01 = t * p1->f._01 + p2->f._01;
    pOut->f._02 = t * p1->f._02 + p2->f._02;
    pOut->f._03 = t * p1->f._03 + p2->f._03;

    pOut->f._10 = t * p1->f._10 + p2->f._10;
    pOut->f._11 = t * p1->f._11 + p2->f._11;
    pOut->f._12 = t * p1->f._12 + p2->f._12;
    pOut->f._13 = t * p1->f._13 + p2->f._13;

    pOut->f._20 = t * p1->f._20 + p2->f._20;
    pOut->f._21 = t * p1->f._21 + p2->f._21;
    pOut->f._22 = t * p1->f._22 + p2->f._22;
    pOut->f._23 = t * p1->f._23 + p2->f._23;

    return pOut;
}

NW_MATH_INLINE MTX34*
MTX34Mult(MTX34* pOut, const MTX34* p1, const MTX34* p2)
{
    MTX34 mTmp;

    MTX34* __restrict pDst = (pOut == p1 || pOut == p2) ? &mTmp : pOut;

    pDst->f._00 = p1->f._00 * p2->f._00 + p1->f._01 * p2->f._10 + p1->f._02 * p2->f._20;
    pDst->f._01 = p1->f._00 * p2->f._01 + p1->f._01 * p2->f._11 + p1->f._02 * p2->f._21;
    pDst->f._02 = p1->f._00 * p2->f._02 + p1->f._01 * p2->f._12 + p1->f._02 * p2->f._22;
    pDst->f._03 = p1->f._00 * p2->f._03 + p1->f._01 * p2->f._13 + p1->f._02 * p2->f._23 + p1->f._03;

    pDst->f._10 = p1->f._10 * p2->f._00 + p1->f._11 * p2->f._10 + p1->f._12 * p2->f._20;
    pDst->f._11 = p1->f._10 * p2->f._01 + p1->f._11 * p2->f._11 + p1->f._12 * p2->f._21;
    pDst->f._12 = p1->f._10 * p2->f._02 + p1->f._11 * p2->f._12 + p1->f._12 * p2->f._22;
    pDst->f._13 = p1->f._10 * p2->f._03 + p1->f._11 * p2->f._13 + p1->f._12 * p2->f._23 + p1->f._13;

    pDst->f._20 = p1->f._20 * p2->f._00 + p1->f._21 * p2->f._10 + p1->f._22 * p2->f._20;
    pDst->f._21 = p1->f._20 * p2->f._01 + p1->f._21 * p2->f._11 + p1->f._22 * p2->f._21;
    pDst->f._22 = p1->f._20 * p2->f._02 + p1->f._21 * p2->f._12 + p1->f._22 * p2->f._22;
    pDst->f._23 = p1->f._20 * p2->f._03 + p1->f._21 * p2->f._13 + p1->f._22 * p2->f._23 + p1->f._23;

    // overwrite a or b if needed
    if ( pDst == &mTmp )
    {
        MTX34Copy( pOut, &mTmp );
    }

    return pOut;
}

NW_MATH_INLINE u32
MTX34Inverse(MTX34* pOut, const MTX34* p)
{
    MTX34 mTmp;
    f32 (*m)[4];
    f32 det;

    f32 (*const inv)[4] = pOut->m;
    const f32 (*const src)[4] = p->m;

    if ( p == pOut )
    {
        m = mTmp.m;
    }
    else
    {
        m = inv;
    }

    // compute the determinant of the upper 3x3 submatrix
    det =   src[0][0]*src[1][1]*src[2][2]
          + src[0][1]*src[1][2]*src[2][0]
          + src[0][2]*src[1][0]*src[2][1]
          - src[2][0]*src[1][1]*src[0][2]
          - src[1][0]*src[0][1]*src[2][2]
          - src[0][0]*src[2][1]*src[1][2];

    // check if matrix is singular
    if ( det == 0.0f )
    {
        return 0;
    }

    // compute the inverse of the upper submatrix:

    // find the transposed matrix of cofactors of the upper submatrix
    // and multiply by (1/det)

    det = 1.0f / det;

    m[0][0] = (src[1][1]*src[2][2] - src[2][1]*src[1][2]) * det;
    m[0][1] = (src[2][1]*src[0][2] - src[0][1]*src[2][2]) * det;
    m[0][2] = (src[0][1]*src[1][2] - src[1][1]*src[0][2]) * det;

    m[1][0] = (src[2][0]*src[1][2] - src[1][0]*src[2][2]) * det;
    m[1][1] = (src[0][0]*src[2][2] - src[2][0]*src[0][2]) * det;
    m[1][2] = (src[1][0]*src[0][2] - src[0][0]*src[1][2]) * det;

    m[2][0] = (src[1][0]*src[2][1] - src[2][0]*src[1][1]) * det;
    m[2][1] = (src[2][0]*src[0][1] - src[0][0]*src[2][1]) * det;
    m[2][2] = (src[0][0]*src[1][1] - src[1][0]*src[0][1]) * det;

    // compute (invA)*(-C)
    m[0][3] = -m[0][0]*src[0][3] - m[0][1]*src[1][3] - m[0][2]*src[2][3];
    m[1][3] = -m[1][0]*src[0][3] - m[1][1]*src[1][3] - m[1][2]*src[2][3];
    m[2][3] = -m[2][0]*src[0][3] - m[2][1]*src[1][3] - m[2][2]*src[2][3];

    // copy back if needed
    if ( m == mTmp.m )
    {
        MTX34Copy( pOut, &mTmp );
    }

    return 1;
}

NW_MATH_INLINE u32
MTX34InvTranspose(MTX34* pOut, const MTX34* __restrict p)
{
    MTX34 mTmp;
    f32 (*m)[4];
    f32 det;

    f32 (*const invX)[4] = pOut->m;
    const f32 (*const src)[4] = p->m;

    if ( p == pOut )
    {
        m = mTmp.m;
    }
    else
    {
        m = invX;
    }

    // compute the determinant of the upper 3x3 submatrix
    det =   src[0][0]*src[1][1]*src[2][2]
          + src[0][1]*src[1][2]*src[2][0]
          + src[0][2]*src[1][0]*src[2][1]
          - src[2][0]*src[1][1]*src[0][2]
          - src[1][0]*src[0][1]*src[2][2]
          - src[0][0]*src[2][1]*src[1][2];

    // check if matrix is singular
    if ( det == 0.0f )
    {
        return 0;
    }

    // compute the inverse-transpose of the upper submatrix:

    // find the transposed matrix of cofactors of the upper submatrix
    // and multiply by (1/det)

    det = 1.0f / det;

    m[0][0] = (src[1][1]*src[2][2] - src[2][1]*src[1][2]) * det;
    m[0][1] = (src[1][2]*src[2][0] - src[2][2]*src[1][0]) * det;
    m[0][2] = (src[1][0]*src[2][1] - src[2][0]*src[1][1]) * det;

    m[1][0] = (src[2][1]*src[0][2] - src[0][1]*src[2][2]) * det;
    m[1][1] = (src[2][2]*src[0][0] - src[0][2]*src[2][0]) * det;
    m[1][2] = (src[2][0]*src[0][1] - src[0][0]*src[2][1]) * det;

    m[2][0] = (src[0][1]*src[1][2] - src[1][1]*src[0][2]) * det;
    m[2][1] = (src[0][2]*src[1][0] - src[1][2]*src[0][0]) * det;
    m[2][2] = (src[0][0]*src[1][1] - src[1][0]*src[0][1]) * det;

    // the fourth columns should be all zero
    m[0][3] = 0.0F;
    m[1][3] = 0.0F;
    m[2][3] = 0.0F;

    // copy back if needed
    if ( m == mTmp.m )
    {
        MTX34Copy( pOut, &mTmp );
    }

    return 1;
}

} } // namespace internal::standard


#if defined(NW_MATH_ENABLE_INTRINSICS)

namespace internal { namespace intrinsics {

NW_MATH_INLINE VEC3*
VEC3Transform(VEC3* pOut, const MTX34* __restrict pM, const VEC3* __restrict pV)
{
    const f32x2 m00m01 = __PSQ_LX(pM, offsetof(MTX34, m[0][0]), 0, 0);
    const f32x2 m02m03 = __PSQ_LX(pM, offsetof(MTX34, m[0][2]), 0, 0);
    const f32x2 m10m11 = __PSQ_LX(pM, offsetof(MTX34, m[1][0]), 0, 0);
    const f32x2 m12m13 = __PSQ_LX(pM, offsetof(MTX34, m[1][2]), 0, 0);
    const f32x2 m20m21 = __PSQ_LX(pM, offsetof(MTX34, m[2][0]), 0, 0);
    const f32x2 m22m23 = __PSQ_LX(pM, offsetof(MTX34, m[2][2]), 0, 0);

    // { xy zw } = { x y z 1 }
    const f32x2 xy = __PSQ_LX(pV, offsetof(VEC3, x), 0, 0);
    const f32x2 zw = __PSQ_LX(pV, offsetof(VEC3, z), 1, 0);

    f32x2 fp4, fp5, fp6;

    // fp4 = [ m00 m01 m02, m03 ] . T[ x y z 1 ]
    fp4 = __PS_MUL(m00m01, xy);
    fp4 = __PS_MADD(m02m03, zw, fp4);
    fp4 = __PS_SUM0(fp4, fp4, fp4);

    // fp5 = [ m10 m11 m12, m13 ] . T[ x y z 1 ]
    fp5 = __PS_MUL(m10m11, xy);
    fp5 = __PS_MADD(m12m13, zw, fp5);
    fp5 = __PS_SUM1(fp5, fp4, fp5);

    // fp6 = [ m20 m21 m22, m23 ] . T[ x y z 1 ]
    fp6 = __PS_MUL(m20m21, xy);
    fp6 = __PS_MADD(m22m23, zw, fp6);
    fp6 = __PS_SUM0(fp6, fp6, fp6);

    tof32x2(pOut->x) = fp5;
    pOut->z = fp6[0];

    return pOut;
}


NW_MATH_INLINE MTX34*
MTX34Add(MTX34* pOut, const MTX34* p1, const MTX34* p2)
{
    f32x2 fp0 = __PS_ADD(tof32x2(p1->a[0] ), tof32x2(p2->a[0] ));
    f32x2 fp1 = __PS_ADD(tof32x2(p1->a[2] ), tof32x2(p2->a[2] ));
    f32x2 fp2 = __PS_ADD(tof32x2(p1->a[4] ), tof32x2(p2->a[4] ));
    f32x2 fp3 = __PS_ADD(tof32x2(p1->a[6] ), tof32x2(p2->a[6] ));
    f32x2 fp4 = __PS_ADD(tof32x2(p1->a[8] ), tof32x2(p2->a[8] ));
    f32x2 fp5 = __PS_ADD(tof32x2(p1->a[10]), tof32x2(p2->a[10]));

    tof32x2(pOut->a[0] ) = fp0;
    tof32x2(pOut->a[2] ) = fp1;
    tof32x2(pOut->a[4] ) = fp2;
    tof32x2(pOut->a[6] ) = fp3;
    tof32x2(pOut->a[8] ) = fp4;
    tof32x2(pOut->a[10]) = fp5;

    return pOut;
}


NW_MATH_INLINE MTX34*
MTX34Sub(MTX34* pOut, const MTX34* p1, const MTX34* p2)
{
    f32x2 fp0 = __PS_SUB(tof32x2(p1->a[0] ), tof32x2(p2->a[0] ));
    f32x2 fp1 = __PS_SUB(tof32x2(p1->a[2] ), tof32x2(p2->a[2] ));
    f32x2 fp2 = __PS_SUB(tof32x2(p1->a[4] ), tof32x2(p2->a[4] ));
    f32x2 fp3 = __PS_SUB(tof32x2(p1->a[6] ), tof32x2(p2->a[6] ));
    f32x2 fp4 = __PS_SUB(tof32x2(p1->a[8] ), tof32x2(p2->a[8] ));
    f32x2 fp5 = __PS_SUB(tof32x2(p1->a[10]), tof32x2(p2->a[10]));

    tof32x2(pOut->a[0] ) = fp0;
    tof32x2(pOut->a[2] ) = fp1;
    tof32x2(pOut->a[4] ) = fp2;
    tof32x2(pOut->a[6] ) = fp3;
    tof32x2(pOut->a[8] ) = fp4;
    tof32x2(pOut->a[10]) = fp5;

    return pOut;
}


NW_MATH_INLINE MTX34*
MTX34Mult(MTX34* pOut, const MTX34* p, f32 f)
{
    f32x2 fp0 = __PS_MULS0F(tof32x2(p->a[0] ), f);
    f32x2 fp1 = __PS_MULS0F(tof32x2(p->a[2] ), f);
    f32x2 fp2 = __PS_MULS0F(tof32x2(p->a[4] ), f);
    f32x2 fp3 = __PS_MULS0F(tof32x2(p->a[6] ), f);
    f32x2 fp4 = __PS_MULS0F(tof32x2(p->a[8] ), f);
    f32x2 fp5 = __PS_MULS0F(tof32x2(p->a[10]), f);

    tof32x2(pOut->a[0] ) = fp0;
    tof32x2(pOut->a[2] ) = fp1;
    tof32x2(pOut->a[4] ) = fp2;
    tof32x2(pOut->a[6] ) = fp3;
    tof32x2(pOut->a[8] ) = fp4;
    tof32x2(pOut->a[10]) = fp5;

    return pOut;
}


NW_MATH_INLINE MTX34*
MTX34MultScale(MTX34* pOut, const MTX34* pM, const VEC3* pS)
{
    // d = { m00 m01 m02 m03 } . { sx 0  0  0 }
    //     { m10 m11 m12 m13 }   { 0  sy 0  0 }
    //     { m20 m21 m22 m23 }   { 0  0  sz 0 }
    //     { 0   0   0   1   }   { 0  0  0  1 }
    //
    //   = { sx*m00 sy*m01 sz*m02 m03 }
    //     { sx*m10 sy*m11 sz*m12 m13 }
    //     { sx*m20 sy*m21 sz*m22 m23 }
    //     { 0      0      0      1   }

    // { xy zw } = { sx sy sz 1 }
    const f32x2 xy = __PSQ_LX(pS, offsetof(VEC3, x), 0, 0);
    const f32x2 zw = __PSQ_LX(pS, offsetof(VEC3, z), 1, 0);

    f32x2 fp00 = __PS_MUL(tof32x2(pM->f._00), xy);
    f32x2 fp10 = __PS_MUL(tof32x2(pM->f._10), xy);
    f32x2 fp20 = __PS_MUL(tof32x2(pM->f._20), xy);

    f32x2 fp02 = __PS_MUL(tof32x2(pM->f._02), zw);
    f32x2 fp12 = __PS_MUL(tof32x2(pM->f._12), zw);
    f32x2 fp22 = __PS_MUL(tof32x2(pM->f._22), zw);

    tof32x2(pOut->f._00) = fp00;
    tof32x2(pOut->f._10) = fp10;
    tof32x2(pOut->f._20) = fp20;

    tof32x2(pOut->f._02) = fp02;
    tof32x2(pOut->f._12) = fp12;
    tof32x2(pOut->f._22) = fp22;

    return pOut;
}


NW_MATH_INLINE MTX34*
MTX34MultScale(MTX34* pOut, const VEC3* __restrict pS, const MTX34* pM)
{
    // d = { sx 0  0  0 } . { m00 m01 m02 m03 }
    //     { 0  sy 0  0 }   { m10 m11 m12 m13 }
    //     { 0  0  sz 0 }   { m20 m21 m22 m23 }
    //     { 0  0  0  1 }   { 0   0   0   1   }
    //
    //   = { sx*m00 sx*m01 sx*m02 sx*m03 }
    //     { sy*m10 sy*m11 sy*m12 sy*m13 }
    //     { sz*m20 sz*m21 sz*m22 sz*m23 }
    //     { 0      0      0      1      }

    // { xy zw } = { sx sy sz 1 }
    const f32x2 xy = __PSQ_LX(pS, offsetof(VEC3, x), 0, 0);
    const f32x2 zw = __PSQ_LX(pS, offsetof(VEC3, z), 1, 0);

    f32x2 fp00 = __PS_MULS0(tof32x2(pM->f._00), xy);
    f32x2 fp02 = __PS_MULS0(tof32x2(pM->f._02), xy);

    f32x2 fp10 = __PS_MULS1(tof32x2(pM->f._10), xy);
    f32x2 fp12 = __PS_MULS1(tof32x2(pM->f._12), xy);

    f32x2 fp20 = __PS_MULS0(tof32x2(pM->f._20), zw);
    f32x2 fp22 = __PS_MULS0(tof32x2(pM->f._22), zw);

    tof32x2(pOut->f._00) = fp00;
    tof32x2(pOut->f._02) = fp02;

    tof32x2(pOut->f._10) = fp10;
    tof32x2(pOut->f._12) = fp12;

    tof32x2(pOut->f._20) = fp20;
    tof32x2(pOut->f._22) = fp22;

    return pOut;
}


NW_MATH_INLINE MTX34*
MTX34MAdd(MTX34* pOut, f32 t, const MTX34* p1, const MTX34* p2)
{
    f32x2 fp0 = __PS_MADDS0F(tof32x2(p1->a[0] ), t, tof32x2(p2->a[0] ));
    f32x2 fp1 = __PS_MADDS0F(tof32x2(p1->a[2] ), t, tof32x2(p2->a[2] ));
    f32x2 fp2 = __PS_MADDS0F(tof32x2(p1->a[4] ), t, tof32x2(p2->a[4] ));
    f32x2 fp3 = __PS_MADDS0F(tof32x2(p1->a[6] ), t, tof32x2(p2->a[6] ));
    f32x2 fp4 = __PS_MADDS0F(tof32x2(p1->a[8] ), t, tof32x2(p2->a[8] ));
    f32x2 fp5 = __PS_MADDS0F(tof32x2(p1->a[10]), t, tof32x2(p2->a[10]));

    tof32x2(pOut->a[0] ) = fp0;
    tof32x2(pOut->a[2] ) = fp1;
    tof32x2(pOut->a[4] ) = fp2;
    tof32x2(pOut->a[6] ) = fp3;
    tof32x2(pOut->a[8] ) = fp4;
    tof32x2(pOut->a[10]) = fp5;

    return pOut;
}

NW_MATH_INLINE MTX34*
MTX34Mult(MTX34* d, const MTX34* a, const MTX34* b)
{
    const int ROW = 16;

    // { f0 f4 } = { b00 b01 b02 b03 }
    // { f1 f5 }   { b10 b11 b12 b13 }
    // { f2 f6 }   { b20 b21 b22 b23 }
    // {    f7 }   {   0   0   0   1 }

    f32x2 f0 = __PSQ_LX(b,  0, 0, 0);
    f32x2 f1 = __PSQ_LX(b, 16, 0, 0);
    f32x2 f2 = __PSQ_LX(b, 32, 0, 0);
    f32x2 f4 = __PSQ_LX(b,  8, 0, 0);
    f32x2 f5 = __PSQ_LX(b, 24, 0, 0);
    f32x2 f6 = __PSQ_LX(b, 40, 0, 0);
    f32x2 f7 = { 0, 1 };

    f32x2 f8, f9, f10;

    // { d00 d01 d02 d03 } = { f9 f10 } := { a00 a01 a02 a03 } . { f0 f4 }
    //                                                           { f1 f5 }
    //                                                           { f2 f6 }
    //                                                           {    f7 }

    f8  = __PSQ_LX(a, 0 * ROW + 0, 0, 0);  // { a00 a01 }
    f9  = __PS_MULS0(f0, f8);
    f10 = __PS_MULS0(f4, f8);
    f9  = __PS_MADDS1(f1, f8, f9);
    f10 = __PS_MADDS1(f5, f8, f10);
    f8  = __PSQ_LX(a, 0 * ROW + 8, 0, 0);  // { a02 a03 }
    f9  = __PS_MADDS0(f2, f8, f9);
    f10 = __PS_MADDS0(f6, f8, f10);
    f10 = __PS_MADDS1(f7, f8, f10);
    __PSQ_STX(d, 0 * ROW + 0, f9,  0, 0);
    __PSQ_STX(d, 0 * ROW + 8, f10, 0, 0);

    //                                                           { f0 f4 }
    // { d10 d11 d12 d13 } = { f9 f10 } := { a10 a11 a12 a13 } . { f1 f5 }
    //                                                           { f2 f6 }
    //                                                           {    f7 }

    f8  = __PSQ_LX(a, 1 * ROW + 0, 0, 0);  // { a10 a11 }
    f9  = __PS_MULS0(f0, f8);
    f10 = __PS_MULS0(f4, f8);
    f9  = __PS_MADDS1(f1, f8, f9);
    f10 = __PS_MADDS1(f5, f8, f10);
    f8  = __PSQ_LX(a, 1 * ROW + 8, 0, 0);  // { a12 a13 }
    f9  = __PS_MADDS0(f2, f8, f9);
    f10 = __PS_MADDS0(f6, f8, f10);
    f10 = __PS_MADDS1(f7, f8, f10);
    __PSQ_STX(d, 1 * ROW + 0, f9,  0, 0);
    __PSQ_STX(d, 1 * ROW + 8, f10, 0, 0);

    //                                                           { f0 f4 }
    //                                                           { f1 f5 }
    // { d20 d21 d22 d23 } = { f9 f10 } := { a20 a21 a22 a23 } . { f2 f6 }
    //                                                           {    f7 }

    f8  = __PSQ_LX(a, 2 * ROW + 0, 0, 0);  // { a20 a21 }
    f9  = __PS_MULS0(f0, f8);
    f10 = __PS_MULS0(f4, f8);
    f9  = __PS_MADDS1(f1, f8, f9);
    f10 = __PS_MADDS1(f5, f8, f10);
    f8  = __PSQ_LX(a, 2 * ROW + 8, 0, 0);  // { a22 a23 }
    f9  = __PS_MADDS0(f2, f8, f9);
    f10 = __PS_MADDS0(f6, f8, f10);
    f10 = __PS_MADDS1(f7, f8, f10);
    __PSQ_STX(d, 2 * ROW + 0, f9,  0, 0);
    __PSQ_STX(d, 2 * ROW + 8, f10, 0, 0);

    return d;
}

NW_MATH_INLINE u32
MTX34Inverse(MTX34* pOut, const MTX34* p)
{
    f32 (*const inv)[4] = pOut->m;
    const f32 (*const src)[4] = p->m;

    f32x2 fp0;
    f32x2 fp1;
    f32x2 fp2;
    f32x2 fp3;
    f32x2 fp4;
    f32x2 fp5;

    f32x2 fp6;
    f32x2 fp7;
    f32x2 fp8;
    f32x2 fp9;
    f32x2 fp10;
    f32x2 fp11;
    f32x2 fp12;
    f32x2 fp13;

    // det = 00 * 11 * 22 + 01 * 12 * 20 + 02 * 10 * 21
    //     - 20 * 11 * 02 - 10 * 01 * 22 - 00 * 21 * 12;

    // fp0 [ 00 ][ 1.0F ] : Load
    fp0 = __PSQ_LX(src, 0, 1, 0);

    // fp1 [ 01 ][ 02 ]   : Load
    fp1 = __PSQ_LX(src, 4, 0, 0);

    // fp2 [ 10 ][ 1.0F ] : Load
    fp2 = __PSQ_LX(src, 16, 1, 0);

    // fp6 [ 02 ][ 00 ]
    fp6 = __PS_MERGE10(fp1, fp0);

    // fp3 [ 11 ][ 12 ]   : Load
    fp3 = __PSQ_LX(src, 20, 0, 0);

    // fp4 [ 20 ][ 1.0F ] : Load
    fp4 = __PSQ_LX(src, 32, 1, 0);

    // fp7 [ 12 ][ 10 ]
    fp7 = __PS_MERGE10(fp3, fp2);

    // fp5 [ 21 ][ 22 ]   : Load
    fp5 = __PSQ_LX(src, 36, 0, 0);

    // fp11[ 11*02 ][ 00*12 ]
    fp11 = __PS_MUL(fp3, fp6);

    // fp8 [ 22 ][ 20 ]
    fp8 = __PS_MERGE10(fp5, fp4);

    // fp13[ 21*12 ][ 10*22 ]
    fp13 = __PS_MUL(fp5, fp7);

    // fp11[ 01*12 - 11*02 ][ 10*02 - 00*12 ]
    fp11 = __PS_MSUB(fp1, fp7, fp11);

    // fp12[ 01*22 ][ 20*02 ]
    fp12 = __PS_MUL(fp1, fp8);

    // fp13[ 11*22 - 21*12 ][ 20*12 - 10*22 ]
    fp13 = __PS_MSUB(fp3, fp8, fp13);

    // fp10[ 20*11 ][ N/A ]
    fp10 = __PS_MUL(fp3, fp4);

    // fp12[ 21*02 - 01*22 ][ 00*22 - 20*02 ]
    fp12 = __PS_MSUB(fp5, fp6, fp12);

    // fp7 [ 00*(11*22-21*12) ][ N/A ]
    fp7  = __PS_MUL(fp0, fp13);

    // fp9 [ 00*21 ][ N/A ]
    fp9  = __PS_MUL(fp0, fp5);

    // fp8 [ 10*01 ][ N/A ]
    fp8  = __PS_MUL(fp1, fp2);

    // fp7 [ 00*(11*22-21*12) + 10*(21*02-01*22) ][ N/A ]
    fp7 = __PS_MADD(fp2, fp12, fp7);

    // fp6 [ 0.0F ][ 0.0F ]
    fp6 = __PS_SUB(fp6, fp6);

    // fp10[ 10*21 - 20*11 ][ N/A ]
    fp10 = __PS_MSUB(fp2, fp5, fp10);

    // fp7 [ 00*(11*22-21*12) + 10*(21*02-01*22) + 20*(01*12-11*02) ][ N/A ] : det
    fp7 = __PS_MADD(fp4, fp11, fp7);

    // fp9 [ 20*01 - 00*21 ][ N/A ]
    fp9 = __PS_MSUB(fp1, fp4, fp9);

    // fp8 [ 00*11 - 10*01 ][ N/A ]
    fp8 = __PS_MSUB(fp0, fp3, fp8);

    // check if matrix is singular
    if( fp7[0] == 0.0f && fp7[1] == 0.0f)
    {
        return 0;
    }

    // compute the inverse of the upper submatrix:

    // find the transposed matrix of cofactors of the upper submatrix
    // and multiply by (1/det)

    // fp0 [ 1/det ][ N/A ]
    fp0 = __PS_DIVS(1.f, fp7[0]);

    // fp1 [ 03 ][ 03 ] : Load
    fp1[0] = src[0][3];
    fp1[1] = src[0][3];

    // fp13[ ( 11*22 - 21*12 ) * rdet ][ ( 20*12 - 10*22 ) * rdet ] : i[0][0], i[1][0]
    fp13 = __PS_MULS0(fp13, fp0);

    // fp2 [ 13 ][ 13 ] : Load
    fp2[0] = src[1][3];
    fp2[1] = src[1][3];

    // fp12[ ( 21*02 - 01*22 ) * rdet ][ ( 00*22 - 20*02 ) * rdet ] : i[0][1], i[1][1]
    fp12 = __PS_MULS0(fp12, fp0);

    // fp3 [ 23 ][ 23 ] : Load
    fp3[0] = src[2][3];
    fp3[1] = src[2][3];

    // fp11[ ( 01*12 - 11*02 ) * rdet ][ ( 10*02 - 00*12 ) * rdet ] : i[0][2], i[1][2]
    fp11 = __PS_MULS0(fp11, fp0);

    // fp5 [ i00 ][ i01 ]
    fp5 = __PS_MERGE00(fp13, fp12);

    // fp4 [ i10 ][ i11 ]
    fp4 = __PS_MERGE11(fp13, fp12);

    // fp6 [ i00*03 ][ i10*03 ]
    fp6 = __PS_MUL(fp13, fp1);

    // [ i00 ][ i01 ] : Store fp5   -> free(fp5[ i00 ][ i01 ])
    //inv[0][0] = fp5[0];
    //inv[0][1] = fp5[1];
    __PSQ_STX(inv, 0, fp5, 0, 0);

    // [ i10 ][ i11 ] : Store fp4   -> free(fp4[ i10 ][ i11 ])
    //inv[1][0] = fp4[0];
    //inv[1][1] = fp4[1];
    __PSQ_STX(inv, 16, fp4, 0, 0);

    // fp10[ ( 10*21 - 20*11 ) * rdet ] : i[2][0]
    fp10  = __PS_MULS0(fp10, fp0);

    // fp9 [ ( 20*01 - 00*21 ) * rdet ] : i[2][1]
    fp9  = __PS_MULS0(fp9,  fp0);

    // fp6 [ i00*03+i01*13 ][ i10*03+i11*13 ]
    fp6 = __PS_MADD(fp12, fp2, fp6);

    // [ i20 ] : Store fp10
    //inv[2][0] = fp10[0];
    __PSQ_STX(inv, 32, fp10, 1, 0);

    // fp8 [ ( 00*11 - 10*01 ) * rdet ] : i[2][2]
    fp8 = __PS_MULS0(fp8,  fp0);

    // fp6 [ -i00*03-i01*13-i02*23 ][ -i10*03-i11*13-i12*23 ] : i[0][3], i[1][3]
    fp6 = __PS_NMADD(fp11, fp3, fp6);

    // [ i21 ] : Store fp9
    //inv[2][1] = fp9[0];
    __PSQ_STX(inv, 36, fp9, 1, 0);

    // fp7 [ i20*03 ][ N/A ]
    fp7 = __PS_MUL(fp10, fp1);

    // fp5 [ i02 ][ i03 ]
    fp5 = __PS_MERGE00(fp11, fp6);

    // [ i22 ] : Store fp8
    //inv[2][2] = fp8[0];
    __PSQ_STX(inv, 40, fp8, 1, 0);

    // fp7 [ i20*03+i21*13 ][ N/A ]
    fp7  = __PS_MADD(fp9,  fp2, fp7);

    // fp4 [ i12 ][ i13 ]
    fp4  = __PS_MERGE11(fp11, fp6);

    // [ i02 ][ i03 ] : Store fp5
    //inv[0][2] = fp5[0];
    //inv[0][3] = fp5[1];
    __PSQ_STX(inv, 8, fp5, 0, 0);

    // fp7 [ -i20*03-i21*13-i22*23 ][ N/A ] : i[2][3]
    fp7 = __PS_NMADD(fp8,  fp3, fp7);

    // [ i12 ][ i13 ] : Store fp4
    //inv[1][2] = fp4[0];
    //inv[1][3] = fp4[1];
    __PSQ_STX(inv, 24, fp4, 0, 0);

    // [ i23 ] : Store fp7
    //inv[2][3] = fp7[0];
    __PSQ_STX(inv, 44, fp7, 1, 0);

    return 1;
}

NW_MATH_INLINE u32
MTX34InvTranspose(MTX34* pOut, const MTX34* __restrict p)
{
    f32 (*const invX)[4] = pOut->m;
    const f32 (*const src)[4] = p->m;

    f32x2 fp0;
    f32x2 fp1;
    f32x2 fp2;
    f32x2 fp3;
    f32x2 fp4;
    f32x2 fp5;

    f32x2 fp6;
    f32x2 fp7;
    f32x2 fp8;
    f32x2 fp9;
    f32x2 fp10;
    f32x2 fp11;
    f32x2 fp12;
    f32x2 fp13;

    // fp0 [ 00 ][ 1.0F ] : Load
    //fp0[0] = src[0][0];
    //fp0[1] = 1.0F;
    fp0 = __PSQ_LX(src, 0, 1, 0);

    // fp1 [ 01 ][ 02 ]   : Load
    //fp1[0] = src[0][1];
    //fp1[1] = src[0][2];
    fp1 = __PSQ_LX(src, 4, 0, 0);

    // fp2 [ 10 ][ 1.0F ] : Load
    //fp2[0] = src[1][0];
    //fp2[1] = 1.0F;
    fp2 = __PSQ_LX(src, 16, 1, 0);

    // fp6 [ 02 ][ 00 ]
    fp6 = __PS_MERGE10(fp1, fp0);

    // fp3 [ 11 ][ 12 ]   : Load
    //fp3[0] = src[1][1];
    //fp3[1] = src[1][2];
    fp3 = __PSQ_LX(src, 20, 0, 0);

    // fp4 [ 20 ][ 1.0F ] : Load
    //fp4[0] = src[2][0];
    //fp4[1] = 1.0F;
    fp4 = __PSQ_LX(src, 32, 1, 0);

    // fp7 [ 12 ][ 10 ]
    fp7 = __PS_MERGE10(fp3, fp2);

    // fp5 [ 21 ][ 22 ]   : Load
    //fp5[0] = src[2][1];
    //fp5[1] = src[2][2];
    fp5 = __PSQ_LX(src, 36, 0, 0);

    // fp11[ 11*02 ][ 00*12 ]
    fp11 = __PS_MUL(fp3, fp6);

    // fp8 [ 22 ][ 20 ]
    fp8 = __PS_MERGE10(fp5, fp4);

    // fp13[ 21*12 ][ 10*22 ]
    fp13 = __PS_MUL(fp5, fp7);

    // fp11[ 01*12 - 11*02 ][ 10*02 - 00*12 ]
    fp11 = __PS_MSUB(fp1, fp7, fp11);

    // fp12[ 01*22 ][ 20*02 ]
    fp12 = __PS_MUL(fp1, fp8);

    // fp13[ 11*22 - 21*12 ][ 20*12 - 10*22 ]
    fp13 = __PS_MSUB(fp3, fp8, fp13);

    // fp10[ 20*11 ][ N/A ]
    fp10 = __PS_MUL(fp3, fp4);

    // fp12[ 21*02 - 01*22 ][ 00*22 - 20*02 ]
    fp12 = __PS_MSUB(fp5, fp6, fp12);

    // fp7 [ 00*(11*22-21*12) ][ N/A ]
    fp7  = __PS_MUL(fp0, fp13);

    // fp9 [ 00*21 ][ N/A ]
    fp9  = __PS_MUL(fp0, fp5);

    // fp8 [ 10*01 ][ N/A ]
    fp8  = __PS_MUL(fp1, fp2);

    // fp7 [ 00*(11*22-21*12) + 10*(21*02-01*22) ][ N/A ]
    fp7 = __PS_MADD(fp2, fp12, fp7);

    // fp6 [ 0.0F ][ 0.0F ]
    fp6 = __PS_SUB(fp6, fp6);

    // fp10[ 10*21 - 20*11 ][ N/A ]
    fp10 = __PS_MSUB(fp2, fp5, fp10);

    // fp7 [ 00*(11*22-21*12) + 10*(21*02-01*22) + 20*(01*12-11*02) ][ N/A ] : det
    fp7 = __PS_MADD(fp4, fp11, fp7);

    // fp9 [ 20*01 - 00*21 ][ N/A ]
    fp9 = __PS_MSUB(fp1, fp4, fp9);

    // fp8 [ 00*11 - 10*01 ][ N/A ]
    fp8 = __PS_MSUB(fp0, fp3, fp8);

    // check if matrix is singular
    if( fp7[0] == 0.0f && fp7[1] == 0.0f)
    {
        return 0;
    }

    // compute the inverse-transpose of the upper submatrix:

    // find the transposed matrix of cofactors of the upper submatrix
    // and multiply by (1/det)

    // fp0 [ 1/det ][ N/A ]
    fp0 = __PS_DIVS(1.f, fp7[0]);

    // [ ix03 ] : Store fp6
    invX[0][3] = fp6[0];

    // [ ix13 ] : Store fp6
    //invX[1][3] = fp6[0];
    __PSQ_STX(invX, 28, fp6, 1, 0);

    // [ ix23 ] : Store fp6
    //invX[2][3] = fp6[0];
    __PSQ_STX(invX, 44, fp6, 1, 0);

    // fp13[ ( 11*22 - 21*12 ) * rdet ][ ( 20*12 - 10*22 ) * rdet ] : ix[0][0], ix[0][1]
    fp13 = __PS_MULS0(fp13, fp0);

    // fp12[ ( 21*02 - 01*22 ) * rdet ][ ( 00*22 - 20*02 ) * rdet ] : ix[1][0], ix[1][1]
    fp12 = __PS_MULS0(fp12, fp0);

    // [ ix00 ][ ix01 ] : Store fp13
    //invX[0][0] = fp13[0];
    //invX[0][1] = fp13[1];
    __PSQ_STX(invX, 0, fp13, 0, 0);

    // fp11[ ( 01*12 - 11*02 ) * rdet ][ ( 10*02 - 00*12 ) * rdet ] : ix[2][0], ix[2][1]
    fp11 = __PS_MULS0(fp11, fp0);

    // [ ix10 ][ ix11 ] : Store fp12
    //invX[1][0] = fp12[0];
    //invX[1][1] = fp12[1];
    __PSQ_STX(invX, 16, fp12, 0, 0);

    // fp10[ ( 10*21 - 20*11 ) * rdet ] : i[0][2]
    fp10 = __PS_MULS0(fp10, fp0);

    // [ ix20 ][ ix21 ] : Store fp11
    //invX[2][0] = fp11[0];
    //invX[2][1] = fp11[1];
    __PSQ_STX(invX, 32, fp11, 0, 0);

    // fp9 [ ( 20*01 - 00*21 ) * rdet ] : i[1][2]
    fp9 = __PS_MULS0(fp9, fp0);

    // [ ix02 ]         : Store fp10
    //invX[0][2] = fp10[0];
    __PSQ_STX(invX, 8, fp10, 1, 0);

    // fp8 [ ( 00*11 - 10*01 ) * rdet ] : i[2][2]
    fp8 = __PS_MULS0(fp8, fp0);

    // [ ix12 ]         : Store fp9
    //invX[1][2] = fp9[0];
    __PSQ_STX(invX, 24, fp9, 1, 0);

    // [ ix22 ]         : Store fp8
    //invX[2][2] = fp8[0];
    __PSQ_STX(invX, 40, fp8, 1, 0);

    return 1;
}

} } // namespace internal::intrinsics

#endif // NW_MATH_ENABLE_INTRINSICS

NW_MATH_INLINE VEC3*
VEC3Transform(VEC3* pOut, const MTX34* __restrict pM, const VEC3* __restrict pV)
{
    return NW_MATH_IMPL_NS::VEC3Transform(pOut, pM, pV);
}

// NW_MATH_INLINE VEC3*
// VEC3CalcRPY(VEC3* pOut, const MTX34* pM)
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

NW_MATH_INLINE MTX34*
MTX34Zero(MTX34* pOut)
{
    pOut->f._00 = pOut->f._01 = pOut->f._02 = pOut->f._03 =
    pOut->f._10 = pOut->f._11 = pOut->f._12 = pOut->f._13 =
    pOut->f._20 = pOut->f._21 = pOut->f._22 = pOut->f._23 = 0.f;

    return pOut;
}

NW_MATH_INLINE MTX34*
MTX34Identity(MTX34* pOut)
{
    MTX34Copy(pOut, MTX34::Identity());

    return pOut;
}

NW_MATH_INLINE bool
MTX34IsIdentity(const MTX34* p)
{
    return p->f._00 == 1.f && p->f._01 == 0.f && p->f._02 == 0.f && p->f._03 == 0.f &&
           p->f._10 == 0.f && p->f._11 == 1.f && p->f._12 == 0.f && p->f._13 == 0.f &&
           p->f._20 == 0.f && p->f._21 == 0.f && p->f._22 == 1.f && p->f._23 == 0.f;
}

NW_MATH_INLINE MTX34*
MTX34Add(MTX34* pOut, const MTX34* p1, const MTX34* p2)
{
    return NW_MATH_IMPL_NS::MTX34Add(pOut, p1, p2);
}

NW_MATH_INLINE MTX34*
MTX34Sub(MTX34* pOut, const MTX34* p1, const MTX34* p2)
{
    return NW_MATH_IMPL_NS::MTX34Sub(pOut, p1, p2);
}

NW_MATH_INLINE MTX34*
MTX34Mult(MTX34* pOut, const MTX34* p, f32 f)
{
    return NW_MATH_IMPL_NS::MTX34Mult(pOut, p, f);
}

NW_MATH_INLINE MTX34*
MTX34Scale(MTX34* pOut, const VEC3* pS)
{
    f32 (*const m)[4] = pOut->m;

    m[0][0] = pS->x;    m[0][1] = 0.0f;  m[0][2] = 0.0f;  m[0][3] = 0.0f;
    m[1][0] = 0.0f;     m[1][1] = pS->y; m[1][2] = 0.0f;  m[1][3] = 0.0f;
    m[2][0] = 0.0f;     m[2][1] = 0.0f;  m[2][2] = pS->z; m[2][3] = 0.0f;

    return pOut;
}

NW_MATH_INLINE MTX34*
MTX34MultScale(MTX34* pOut, const MTX34* pM, const VEC3* pS)
{
    return NW_MATH_IMPL_NS::MTX34MultScale(pOut, pM, pS);
}

NW_MATH_INLINE MTX34*
MTX34MultScale(MTX34* pOut, const VEC3* __restrict pS, const MTX34* pM)
{
    return NW_MATH_IMPL_NS::MTX34MultScale(pOut, pS, pM);
}

NW_MATH_INLINE MTX34*
MTX34Translate(MTX34* pOut, const VEC3* pT)
{
    f32 (*const m)[4] = pOut->m;

    m[0][0] = 1.0f;  m[0][1] = 0.0f;  m[0][2] = 0.0f;  m[0][3] = pT->x;
    m[1][0] = 0.0f;  m[1][1] = 1.0f;  m[1][2] = 0.0f;  m[1][3] = pT->y;
    m[2][0] = 0.0f;  m[2][1] = 0.0f;  m[2][2] = 1.0f;  m[2][3] = pT->z;

    return pOut;
}

NW_MATH_INLINE MTX34*
MTX34MultTranslate(MTX34* pOut, const VEC3* pT, const MTX34* pM)
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

NW_MATH_INLINE MTX34*
MTX34MultTranslate(MTX34* pOut, const MTX34* pM, const VEC3* pT)
{
    // pOut = pM * pT
    if (pOut != pM)
    {
        (void)MTX34Copy(pOut, pM);
    }

    VEC3 tmp;
    VEC3Transform(&tmp, pM, pT);

    pOut->f._03 = tmp.x;
    pOut->f._13 = tmp.y;
    pOut->f._23 = tmp.z;

    return pOut;
}

NW_MATH_INLINE MTX34*
MTX34MAdd(MTX34* pOut, f32 t, const MTX34* p1, const MTX34* p2)
{
    return NW_MATH_IMPL_NS::MTX34MAdd(pOut, t, p1, p2);
}

static NW_MATH_INLINE MTX34*
MTX34RotAxisRad_( MTX34* pOut, const VEC3 *pAxis, f32 fRad )
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
    m[0][3] =    0.0f;

    m[1][0] = ( t * x * y ) + ( s * z );
    m[1][1] = ( t * ySq )   + ( c );
    m[1][2] = ( t * y * z ) - ( s * x );
    m[1][3] =    0.0f;

    m[2][0] = ( t * x * z ) - ( s * y );
    m[2][1] = ( t * y * z ) + ( s * x );
    m[2][2] = ( t * zSq )   + ( c );
    m[2][3] =    0.0f;

    return pOut;
}

NW_MATH_INLINE MTX34*
MTX34RotAxisIdx(MTX34* pOut, const VEC3* pAxis, u32 idx)
{
    MTX34RotAxisRad_(pOut, pAxis, NW_MATH_IDX_TO_RAD(idx));

    return pOut;
}

NW_MATH_INLINE MTX34*
MTX34RotXYZIdx(MTX34* pOut, u32 idxX, u32 idxY, u32 idxZ)
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

    return pOut;
}

NW_MATH_INLINE MTX34*
MTX34RotXYZTranslateIdx(MTX34* pOut, u32 idxX, u32 idxY, u32 idxZ, const VEC3* pT)
{
    (void)MTX34RotXYZIdx(pOut, idxX, idxY, idxZ);
    pOut->f._03 = pT->x;
    pOut->f._13 = pT->y;
    pOut->f._23 = pT->z;
    return pOut;
}

NW_MATH_INLINE u32
MTX34Inverse(MTX34* pOut, const MTX34* p)
{
    return NW_MATH_IMPL_NS::MTX34Inverse(pOut, p);
}

NW_MATH_INLINE MTX34*
MTX34Transpose(MTX34* pOut, const MTX34* p)
{
    MTX34 mTmp;

    const f32 (*const src)[4] = p->m;
    f32 (*m)[4];

    if (p == pOut)
    {
        m = mTmp.m;
    }
    else
    {
        m = pOut->m;
    }

    m[0][0] = src[0][0];   m[0][1] = src[1][0];      m[0][2] = src[2][0];     m[0][3] = 0.0f;
    m[1][0] = src[0][1];   m[1][1] = src[1][1];      m[1][2] = src[2][1];     m[1][3] = 0.0f;
    m[2][0] = src[0][2];   m[2][1] = src[1][2];      m[2][2] = src[2][2];     m[2][3] = 0.0f;

    // copy back if needed
    if ( m == mTmp.m )
    {
        MTX34Copy( pOut, &mTmp );
    }

    return pOut;
}

NW_MATH_INLINE u32
MTX34InvTranspose(MTX34* pOut, const MTX34* __restrict p)
{
    return NW_MATH_IMPL_NS::MTX34InvTranspose(pOut, p);
}

NW_MATH_INLINE MTX34*
MTX34MultArray(MTX34* pOut, const MTX34* __restrict p1, const MTX34* __restrict pSrc, s32 count)
{
    MTX34* pOutBase = pOut;

    for ( s32 i = 0 ; i < count ; i++ )
    {
        MTX34Mult(pOut, p1, pSrc);

        pSrc++;
        pOut++;
    }

    return pOutBase;
}

NW_MATH_INLINE MTX34*
MTX34LookAt(MTX34* pOut, const VEC3* pCamPos, const VEC3* pCamUp, const VEC3* pTarget)
{
    f32 (*const m)[4] = pOut->m;

    // compute unit target vector
    // use negative value to look down (-Z) axis
    VEC3 vLook;
    VEC3Sub(&vLook, pCamPos, pTarget);
    VEC3Normalize(&vLook, &vLook);

    // vRight = pCamUp x vLook
    VEC3 vRight;
    VEC3Cross(&vRight, pCamUp, &vLook);
    VEC3Normalize(&vRight, &vRight);

    // vUp = vLook x vRight
    VEC3 vUp;
    VEC3Cross(&vUp, &vLook, &vRight);
    // Don't need to normalize vUp since it should already be unit length
    // VECNormalize( &vUp, &vUp );

    m[0][0] = vRight.x;
    m[0][1] = vRight.y;
    m[0][2] = vRight.z;
    m[0][3] = -( pCamPos->x * vRight.x + pCamPos->y * vRight.y + pCamPos->z * vRight.z );

    m[1][0] = vUp.x;
    m[1][1] = vUp.y;
    m[1][2] = vUp.z;
    m[1][3] = -( pCamPos->x * vUp.x + pCamPos->y * vUp.y + pCamPos->z * vUp.z );

    m[2][0] = vLook.x;
    m[2][1] = vLook.y;
    m[2][2] = vLook.z;
    m[2][3] = -( pCamPos->x * vLook.x + pCamPos->y * vLook.y + pCamPos->z * vLook.z );

    return pOut;
}

NW_MATH_INLINE MTX34*
MTX34LookAt(MTX34* pOut, const VEC3* pCamPos, f32 twist, const VEC3* pTarget)
{
    f32 (*const m)[4] = pOut->m;

    VEC3 lookReverse(pCamPos->x - pTarget->x, pCamPos->y - pTarget->y, pCamPos->z - pTarget->z);

    if ((lookReverse.x == 0.0f) && (lookReverse.z == 0.0f))
    {
        m[0][0] = 1.0f;
        m[0][1] = 0.0f;
        m[0][2] = 0.0f;
        m[0][3] = -pCamPos->x;

        m[1][0] = 0.0f;
        m[1][1] = 0.0f;

        m[2][0] = 0.0f;
        m[2][2] = 0.0f;

        if (lookReverse.y <= 0.0f)
        {
            m[1][2] = 1.0f;
            m[1][3] = -pCamPos->z;

            m[2][1] = -1.0f;
            m[2][3] = pCamPos->y;
        }
        else
        {
            m[1][2] = -1.0f;
            m[1][3] = pCamPos->z;

            m[2][1] = 1.0f;
            m[2][3] = -pCamPos->y;
        }
    }
    else
    {
        VEC3 r(lookReverse.z, 0.0f, -lookReverse.x);

        VEC3Normalize(&lookReverse, &lookReverse);
        VEC3Normalize(&r, &r);

        VEC3 u;
        VEC3Cross(&u, &lookReverse, &r);

        f32 st, ct;
        SinCosDeg(&st, &ct, twist);
        VEC3 right, up;

        right.x = st * u.x + ct * r.x;
        right.y = st * u.y;
        right.z = st * u.z + ct * r.z;

        up.x    = ct * u.x - st * r.x;
        up.y    = ct * u.y;
        up.z    = ct * u.z - st * r.z;

        // right
        m[0][0] = right.x;
        m[0][1] = right.y;
        m[0][2] = right.z;
        m[0][3] = -VEC3Dot(pCamPos, &right);

        // up
        m[1][0] = up.x;
        m[1][1] = up.y;
        m[1][2] = up.z;
        m[1][3] = -VEC3Dot(pCamPos, &up);

        // look
        m[2][0] = lookReverse.x;
        m[2][1] = lookReverse.y;
        m[2][2] = lookReverse.z;
        m[2][3] = -VEC3Dot(pCamPos, &lookReverse);
    }

    return pOut;
}

NW_MATH_INLINE MTX34*
MTX34CameraRotate(MTX34* pOut, const VEC3* pCamPos, const VEC3* pCamRotate)
{
    f32 (*const m)[4] = pOut->m;

    f32 sx, sy, sz, cx, cy, cz;
    SinCosDeg(&sx, &cx, pCamRotate->x);
    SinCosDeg(&sy, &cy, pCamRotate->y);
    SinCosDeg(&sz, &cz, pCamRotate->z);

    VEC3 right, up, back;

    right.x = sx * sy * sz + cy * cz;
    right.y = cx * sz;
    right.z = sx * cy * sz - sy * cz;

    up.x    = sx * sy * cz - cy * sz;
    up.y    = cx * cz;
    up.z    = sx * cy * cz + sy * sz;

    back.x  = cx * sy;
    back.y  = - sx;
    back.z  = cx * cy;

    m[0][0] = right.x;
    m[0][1] = right.y;
    m[0][2] = right.z;
    m[0][3] = -VEC3Dot(pCamPos, &right);

    m[1][0] = up.x;
    m[1][1] = up.y;
    m[1][2] = up.z;
    m[1][3] = -VEC3Dot(pCamPos, &up);

    m[2][0] = back.x;
    m[2][1] = back.y;
    m[2][2] = back.z;
    m[2][3] = -VEC3Dot(pCamPos, &back);

    return pOut;
}

NW_MATH_INLINE MTX34*
MTX34TextureProjectionFrustum(MTX34* pOut, f32 l, f32 r, f32 b, f32 t, f32 n, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT)
{
    f32 reverseWidth = 1.0f / (r - l);

    f32 (*const mtx)[4] = pOut->m;

    mtx[0][0] = ((2.0f * n) * reverseWidth) * scaleS;
    mtx[0][1] = 0.0f;
    mtx[0][2] = (((r + l) * reverseWidth) * scaleS) - translateS;
    mtx[0][3] = 0.0f;

    f32 reverseHeight = 1.0f / (t - b);
    mtx[1][0] = 0.0f;
    mtx[1][1] = ((2.0f * n) * reverseHeight) * scaleT;
    mtx[1][2] = (((t+ b) * reverseHeight) * scaleT) - translateT;
    mtx[1][3] = 0.0f;

    mtx[2][0] = 0.0f;
    mtx[2][1] = 0.0f;
    mtx[2][2] = -1.0f;
    mtx[2][3] = 0.0f;
    return pOut;
}

NW_MATH_INLINE MTX34*
MTX34TextureProjectionPerspective(MTX34* pOut, f32 fovy, f32 aspect, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT)
{
    float angle = fovy * 0.5f;
    float cot = 1.0f / math::TanRad(angle);

    f32 (*const mtx)[4] = pOut->m;

    mtx[0][0] = (cot / aspect) * scaleS;
    mtx[0][1] = 0.0f;
    mtx[0][2] = -translateS;
    mtx[0][3] = 0.0f;

    mtx[1][0] = 0.0f;
    mtx[1][1] = cot * scaleT;
    mtx[1][2] = -translateT;
    mtx[1][3] = 0.0f;

    mtx[2][0] = 0.0f;
    mtx[2][1] = 0.0f;
    mtx[2][2] = -1.0f;
    mtx[2][3] = 0.0f;

    return pOut;
}

NW_MATH_INLINE MTX34*
MTX34TextureProjectionOrtho(MTX34* pOut, f32 l, f32 r, f32 b, f32 t, f32 scaleS, f32 scaleT, f32 translateS, f32 translateT)
{
    float reverseWidth = 1.0f / (r - l);

    f32 (*const mtx)[4] = pOut->m;

    mtx[0][0] = 2.0f * reverseWidth * scaleS;
    mtx[0][1] = 0.0f;
    mtx[0][2] = 0.0f;
    mtx[0][3] = ((-(r + l) * reverseWidth) * scaleS) + translateS;

    float reverseHeight = 1.0f / (t - b);
    mtx[1][0] = 0.0f;
    mtx[1][1] = (2.0f * reverseHeight) * scaleT;
    mtx[1][2] = 0.0f;
    mtx[1][3] = ((-(t + b) * reverseHeight) * scaleT) + translateT;

    mtx[2][0] = 0.0f;
    mtx[2][1] = 0.0f;
    mtx[2][2] = 0.0f;
    mtx[2][3] = 1.0f;
    return pOut;
}

NW_MATH_INLINE MTX34*
MTX34MakeSRT(MTX34* pOut, const VEC3* pS, const VEC3* pR, const VEC3* pT)
{
    f32 sinV[3];
    f32 cosV[3];

    sinV[0] = SinRad( pR->x );
    sinV[1] = SinRad( pR->y );
    sinV[2] = SinRad( pR->z );

    cosV[0] = CosRad( pR->x );
    cosV[1] = CosRad( pR->y );
    cosV[2] = CosRad( pR->z );

    f32 opt1 = cosV[0] * cosV[2];
    f32 opt2 = sinV[0] * sinV[1];
    f32 opt3 = cosV[0] * sinV[2];

    pOut->m[0][0] = pS->x * ( cosV[1] * cosV[2] );
    pOut->m[1][0] = pS->x * ( cosV[1] * sinV[2] );
    pOut->m[2][0] = pS->x * ( -sinV[1] );

    pOut->m[0][1] = pS->y * ( ( opt2 * cosV[2] ) - ( opt3 ) );
    pOut->m[1][1] = pS->y * ( ( opt2 * sinV[2] ) + ( opt1 ));
    pOut->m[2][1] = pS->y * ( ( sinV[0] * cosV[1] ) );

    pOut->m[0][2] = pS->z * ( ( opt1 * sinV[1] ) + ( sinV[0] * sinV[2] ) );
    pOut->m[1][2] = pS->z * ( ( opt3 * sinV[1] ) - ( sinV[0] * cosV[2] ) );
    pOut->m[2][2] = pS->z * ( ( cosV[0] * cosV[1] ) );

    pOut->m[0][3] = pT->x;
    pOut->m[1][3] = pT->y;
    pOut->m[2][3] = pT->z;

    return pOut;
}

NW_MATH_INLINE MTX34*
MTX34MakeST(MTX34* pOut, const VEC3* pS, const VEC3* pT)
{
    pOut->m[0][0] = pS->x;
    pOut->m[1][0] = 0.f;
    pOut->m[2][0] = 0.f;

    pOut->m[0][1] = 0.f;
    pOut->m[1][1] = pS->y;
    pOut->m[2][1] = 0.f;

    pOut->m[0][2] = 0.f;
    pOut->m[1][2] = 0.f;
    pOut->m[2][2] = pS->z;

    pOut->m[0][3] = pT->x;
    pOut->m[1][3] = pT->y;
    pOut->m[2][3] = pT->z;

    return pOut;
}

NW_MATH_INLINE MTX34*
MTX34MakeS(MTX34* pOut, const VEC3* pS)
{
    pOut->m[0][0] = pS->x;
    pOut->m[0][1] = 0.f;
    pOut->m[0][2] = 0.f;

    pOut->m[1][0] = 0.f;
    pOut->m[1][1] = pS->y;
    pOut->m[1][2] = 0.f;

    pOut->m[2][0] = 0.f;
    pOut->m[2][1] = 0.f;
    pOut->m[2][2] = pS->z;

    pOut->m[0][3] = 0.f;
    pOut->m[1][3] = 0.f;
    pOut->m[2][3] = 0.f;

    return pOut;
}

NW_MATH_INLINE MTX34*
QUATToMTX34(MTX34* pOut, const QUAT* pQ)
{
    f32 s, xs, ys, zs;
    f32 wx, wy, wz, xx, xy, xz, yy, yz, zz;

    f32 (*const m)[4] = pOut->m;

    s = 2.0f / ( (pQ->x * pQ->x) + (pQ->y * pQ->y) + (pQ->z * pQ->z) + (pQ->w * pQ->w) );

    xs = pQ->x *  s;     ys = pQ->y *  s;  zs = pQ->z *  s;
    wx = pQ->w * xs;     wy = pQ->w * ys;  wz = pQ->w * zs;
    xx = pQ->x * xs;     xy = pQ->x * ys;  xz = pQ->x * zs;
    yy = pQ->y * ys;     yz = pQ->y * zs;  zz = pQ->z * zs;

    m[0][0] = 1.0f - (yy + zz);
    m[0][1] = xy   - wz;
    m[0][2] = xz   + wy;
    m[0][3] = 0.0f;

    m[1][0] = xy   + wz;
    m[1][1] = 1.0f - (xx + zz);
    m[1][2] = yz   - wx;
    m[1][3] = 0.0f;

    m[2][0] = xz   - wy;
    m[2][1] = yz   + wx;
    m[2][2] = 1.0f - (xx + yy);
    m[2][3] = 0.0f;

    return pOut;
}

} } // namespace nw::math

#endif

#endif
