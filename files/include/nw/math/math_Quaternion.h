#ifndef NW_MATH_QUATERNION_H_
#define NW_MATH_QUATERNION_H_

#include <cstring>
#include <nw/math/math_Config.h>

#if defined(NW_PLATFORM_CAFE)
    #include <cafe/mtx/mtxVec.h>
#endif


namespace nw { namespace math {

struct QUAT;

namespace internal { namespace standard {

    QUAT* QUATAdd(QUAT* pOut, const QUAT* q1, const QUAT* q2);
    QUAT* QUATSub(QUAT *pOut,  const QUAT *q1, const QUAT *q2);
    QUAT* QUATMult(QUAT* pOut, const QUAT* q1, const QUAT* q2);
    f32 QUATDot(const QUAT* q1, const QUAT* q2);
    QUAT* QUATScale(QUAT* pOut, const QUAT* q, f32 scale);
    QUAT* QUATNormalize(QUAT* pOut, const QUAT* q);
    QUAT* QUATInverse(QUAT* pOut, const QUAT* q);
    QUAT* QUATExp(QUAT* pOut, const QUAT* q);
    QUAT* QUATLogN(QUAT* pOut, const QUAT* q);
    QUAT* QUATLerp(QUAT* pOut, const QUAT* q1, const QUAT* q2, f32 t);
    QUAT* QUATSlerp(QUAT* pOut, const QUAT* q1, const QUAT* q2, f32 t);
    QUAT* QUATMakeClosest(QUAT* pOut, const QUAT *q, const QUAT *qto);
    VEC3* VEC3CalcRPY(VEC3* pOut, const QUAT *q);

} } // namespace internal::standard

#if defined(NW_MATH_ENABLE_INTRINSICS)

namespace internal { namespace intrinsics {

    QUAT* QUATAdd(QUAT* pOut, const QUAT* q1, const QUAT* q2);
    QUAT* QUATSub(QUAT *pOut,  const QUAT *q1, const QUAT *q2);
    QUAT* QUATMult(QUAT* pOut, const QUAT* q1, const QUAT* q2);
    f32 QUATDot(const QUAT* q1, const QUAT* q2);
    QUAT* QUATScale(QUAT* pOut, const QUAT* q, f32 scale);
    QUAT* QUATNormalize(QUAT* pOut, const QUAT* q);
    QUAT* QUATInverse(QUAT* pOut, const QUAT* q);
    QUAT* QUATExp(QUAT* pOut, const QUAT* q);
    QUAT* QUATLogN(QUAT* pOut, const QUAT* q);
    QUAT* QUATLerp(QUAT* pOut, const QUAT* q1, const QUAT* q2, f32 t);
    QUAT* QUATSlerp(QUAT* pOut, const QUAT* q1, const QUAT* q2, f32 t);
    QUAT* QUATMakeClosest(QUAT* pOut, const QUAT *q, const QUAT *qto);
    VEC3* VEC3CalcRPY(VEC3* pOut, const QUAT *q);

} } // namespace internal::intrinsics

#endif // NW_MATH_ENABLE_INTRINSICS

NW_MATH_INLINE QUAT* QUATAdd(QUAT* pOut, const QUAT* q1, const QUAT* q2);
NW_MATH_INLINE QUAT* QUATSub(QUAT* pOut, const QUAT* q1, const QUAT* q2);
NW_MATH_INLINE QUAT* QUATDivide(QUAT* pOut, const QUAT* q1, const QUAT* q2);
NW_MATH_INLINE QUAT* QUATMult(QUAT* pOut, const QUAT* q1, const QUAT* q2);
NW_MATH_INLINE f32   QUATDot(const QUAT* q1, const QUAT* q2);
NW_MATH_INLINE QUAT* QUATInverse(QUAT* pOut, const QUAT* q);
NW_MATH_INLINE QUAT* QUATScale(QUAT* pOut, const QUAT* q, f32 scale);
NW_MATH_INLINE QUAT* QUATNormalize(QUAT* pOut, const QUAT* q);
NW_MATH_INLINE QUAT* QUATExp(QUAT* pOut, const QUAT* q);
NW_MATH_INLINE QUAT* QUATLogN(QUAT* pOut, const QUAT* q);
NW_MATH_INLINE QUAT* QUATLerp(QUAT* pOut, const QUAT* q1, const QUAT* q2, f32 t);
NW_MATH_INLINE QUAT* QUATSlerp(QUAT* pOut, const QUAT* q1, const QUAT* q2, f32 t);
NW_MATH_INLINE QUAT* MTX34ToQUAT(QUAT* pOut, const MTX34* pMtx);
NW_MATH_INLINE QUAT* QUATSquad(QUAT* pOut, const QUAT* p, const QUAT* a, const QUAT* b, const QUAT* q, f32 t);

NW_MATH_INLINE QUAT* QUATMakeClosest( QUAT* pOut, const QUAT *q, const QUAT *qto );
NW_MATH_INLINE QUAT* QUATRotAxisRad( QUAT* pOut, const VEC3 *axis, f32 rad );
NW_MATH_INLINE QUAT* QUATMakeVectorRotation( QUAT *pOut, const VEC3* pFrom, const VEC3* pTo );

struct QUAT_
{
    f32 x;
    f32 y;
    f32 z;
    f32 w;
};

struct QUAT : public QUAT_
{
public:
    typedef QUAT self_type;
    typedef f32  value_type;
public:
    QUAT() {}
    explicit QUAT(const f32* p) { x = p[0]; y = p[1]; z = p[2]; w = p[3]; }
    explicit QUAT(const QUAT_& rhs) { x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w; }
    QUAT(f32 fx, f32 fy, f32 fz, f32 fw) { x = fx; y = fy; z = fz; w = fw; }

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

    self_type& operator += (const self_type& rhs) { (void)QUATAdd(this, this, &rhs); return *this; }
    self_type& operator -= (const self_type& rhs) { (void)QUATSub(this, this, &rhs); return *this; }
    self_type& operator *= (f32 f) { (void)QUATScale(this, this, f); return *this; }
    self_type& operator /= (f32 f) { return operator*=(1.f / f); }

    self_type operator + () const { return *this; }
    self_type operator - () const { return self_type(-x, -y, -z, -w); }

    self_type operator + (const self_type& rhs) const { QUAT tmp; (void)QUATAdd(&tmp, this, &rhs); return tmp; }
    self_type operator - (const self_type& rhs) const { QUAT tmp; (void)QUATSub(&tmp, this, &rhs); return tmp; }
    self_type operator * (f32 f) const { QUAT tmp; (void)QUATScale(&tmp, this, f); return tmp; }
    self_type operator / (f32 f) const { return operator*(1.f / f); }

    bool operator == (const self_type& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w; }
    bool operator != (const self_type& rhs) const { return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w; }
};

typedef struct QUAT Quaternion;

inline QUAT
operator * (f32 f, const QUAT& rhs) { QUAT tmp; (void)QUATScale(&tmp, &rhs, f); return tmp; }

} } // namespace nw::math


#if defined(NW_MATH_AS_INLINE)

#include <cmath>

namespace nw { namespace math {

#define NW_QUAT_EPSILON        0.00001F

namespace internal { namespace standard {

NW_MATH_INLINE QUAT*
QUATAdd(QUAT* pOut, const QUAT* q1, const QUAT* q2)
{
    pOut->x = q1->x + q2->x;
    pOut->y = q1->y + q2->y;
    pOut->z = q1->z + q2->z;
    pOut->w = q1->w + q2->w;

    return pOut;
}

NW_MATH_INLINE QUAT*
QUATSub(QUAT *pOut,  const QUAT *q1, const QUAT *q2)
{
    pOut->x = q1->x - q2->x;
    pOut->y = q1->y - q2->y;
    pOut->z = q1->z - q2->z;
    pOut->w = q1->w - q2->w;

    return pOut;
}

NW_MATH_INLINE QUAT*
QUATMult(QUAT* pOut, const QUAT* __restrict q1, const QUAT* __restrict q2)
{
    QUAT * __restrict pDst;
    QUAT  tmp;

    if ( q1 == pOut || q2 == pOut )
    {
        pDst = &tmp;
    }
    else
    {
        pDst = pOut;
    }

    pDst->w = q1->w * q2->w - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z;
    pDst->x = q1->w * q2->x + q1->x * q2->w + q1->y * q2->z - q1->z * q2->y;
    pDst->y = q1->w * q2->y + q1->y * q2->w + q1->z * q2->x - q1->x * q2->z;
    pDst->z = q1->w * q2->z + q1->z * q2->w + q1->x * q2->y - q1->y * q2->x;

    if ( pDst == &tmp )
    {
        *pOut = tmp;
    }

    return pOut;
}

NW_MATH_INLINE f32
QUATDot(const QUAT* q1, const QUAT* q2)
{
    return (q1->x * q2->x + q1->y * q2->y + q1->z * q2->z + q1->w * q2->w);
}

NW_MATH_INLINE QUAT*
QUATScale(QUAT* pOut, const QUAT* q, f32 scale)
{
    pOut->x = q->x * scale;
    pOut->y = q->y * scale;
    pOut->z = q->z * scale;
    pOut->w = q->w * scale;

    return pOut;
}

NW_MATH_INLINE QUAT*
QUATNormalize(QUAT* pOut, const QUAT* __restrict q)
{
    f32 mag = (q->x * q->x) + (q->y * q->y) + (q->z * q->z) + (q->w * q->w);

    if ( mag >= NW_QUAT_EPSILON )
    {
        mag = 1.0F / ::std::sqrt(mag);

        pOut->x = q->x * mag;
        pOut->y = q->y * mag;
        pOut->z = q->z * mag;
        pOut->w = q->w * mag;
    }
    else
    {
        pOut->x = pOut->y = pOut->z = pOut->w = 0.0F;
    }

    return pOut;
}

NW_MATH_INLINE QUAT*
QUATInverse(QUAT* pOut, const QUAT* __restrict q)
{
    f32 mag, norminv;

    mag = ( q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w );

    if ( mag == 0.0f )
    {
        mag = 1.0f;
    }

    // [Inverse] = [Conjugate] / [Magnitude]
    norminv = 1.0f / mag;
    pOut->x = -q->x * norminv;
    pOut->y = -q->y * norminv;
    pOut->z = -q->z * norminv;
    pOut->w =  q->w * norminv;

    return pOut;
}

NW_MATH_INLINE QUAT*
QUATExp(QUAT* pOut, const QUAT* __restrict q)
{
    f32 theta, scale;

    theta = ::std::sqrt( q->x * q->x + q->y * q->y + q->z * q->z );
    scale = 1.0F;

    if ( theta > NW_QUAT_EPSILON )
    {
        scale = (f32)::std::sin(theta) / theta;
    }

    pOut->x = scale * q->x;
    pOut->y = scale * q->y;
    pOut->z = scale * q->z;
    pOut->w = (f32)::std::cos(theta);

    return pOut;
}

NW_MATH_INLINE QUAT*
QUATLogN(QUAT* pOut, const QUAT* __restrict q)
{
    f32 theta, scale;

    scale = q->x * q->x + q->y * q->y + q->z * q->z;

    scale = ::std::sqrt(scale);
    theta = ::std::atan2( scale, q->w );

    if ( scale > 0.0F )
    {
        scale = theta / scale;
    }

    pOut->x = scale * q->x;
    pOut->y = scale * q->y;
    pOut->z = scale * q->z;
    pOut->w = 0.0F;

    return pOut;
}

NW_MATH_INLINE QUAT*
QUATLerp(QUAT* pOut, const QUAT* __restrict q1, const QUAT* __restrict q2, f32 t)
{
    pOut->x = t * ( q2->x - q1->x ) + q1->x;
    pOut->y = t * ( q2->y - q1->y ) + q1->y;
    pOut->z = t * ( q2->z - q1->z ) + q1->z;
    pOut->w = t * ( q2->w - q1->w ) + q1->w;

    return pOut;
}

NW_MATH_INLINE QUAT*
QUATSlerp(QUAT* pOut, const QUAT* __restrict q1, const QUAT* __restrict q2, f32 t)
{
    f32 theta, sin_th, cos_th, tp, tq;

    cos_th = q1->x * q2->x + q1->y * q2->y + q1->z * q2->z + q1->w * q2->w;
    tq     = 1.0F;

    if ( cos_th < 0.0F )
    {
        cos_th = -cos_th;
        tq     = -tq;
    }

    if ( cos_th <= 1.0F - NW_QUAT_EPSILON )
    {
        theta  = ::std::acos(cos_th);
        sin_th = ::std::sin(theta);
        tp     = ::std::sin((1.0F - t) * theta) / sin_th;
        tq    *= ::std::sin( t * theta ) / sin_th;
    }
    else
    {
        // cos(theta) is close to 1.0F -> linear
        tp = 1.0F - t;
        tq = tq * t;
    }

    pOut->x = tp * q1->x + tq * q2->x;
    pOut->y = tp * q1->y + tq * q2->y;
    pOut->z = tp * q1->z + tq * q2->z;
    pOut->w = tp * q1->w + tq * q2->w;

    return pOut;
}

NW_MATH_INLINE QUAT*
QUATMakeClosest(QUAT* pOut, const QUAT *q, const QUAT *qto)
{
    f32 dot;

    dot =  q->x * qto->x + q->y * qto->y + q->z * qto->z + q->w * qto->w;

    if ( dot < 0.0f )
    {
        pOut->x = -q->x;
        pOut->y = -q->y;
        pOut->z = -q->z;
        pOut->w = -q->w;
    }
    else
    {
        *pOut = *q;
    }

    return pOut;
}

// NW_MATH_INLINE VEC3*
// VEC3CalcRPY(VEC3* pOut, const QUAT *q)
// {
//     f32 q00 = q->w * q->w;
//     f32 q11 = q->x * q->x;
//     f32 q22 = q->y * q->y;
//     f32 q33 = q->z * q->z;
//
//     f32 r11 = q00 + q11 - q22 - q33;
//     f32 r21 = 2.0f * (q->x * q->y + q->w * q->z);
//     f32 r31 = 2.0f * (q->x * q->z - q->w * q->y);
//     f32 r32 = 2.0f * (q->y * q->z + q->w * q->x);
//     f32 r33 = q00 - q11 - q22 + q33;
//
//     f32 tmp = math::FAbs(r31);
//     if (1.0f - tmp < math::F_ULP)
//     {
//         f32 r12 = 2.0f * (q->x * q->y - q->w * q->z);
//         f32 r13 = 2.0f * (q->x * q->z + q->w * q->y);
//
//         pOut->x = 0.f;
//         pOut->y = -math::F_PI / 2.0f * (r31 / tmp);
//         pOut->z = math::Atan2Rad(-r12, -r31 * r13);
//     }
//     else
//     {
//         pOut->x = math::Atan2Rad(r32, r33);
//         pOut->y = math::AsinRad(-r31);
//         pOut->z = math::Atan2Rad(r21, r11);
//     }
//
//     return pOut;
// }

} } // namespace internal::standard

#if defined(NW_MATH_ENABLE_INTRINSICS)

namespace internal { namespace intrinsics {

NW_MATH_INLINE QUAT*
QUATAdd(QUAT* pOut, const QUAT* q1, const QUAT* q2)
{
    tof32x2(pOut->x) = __PS_ADD(tof32x2(q1->x), tof32x2(q2->x));
    tof32x2(pOut->z) = __PS_ADD(tof32x2(q1->z), tof32x2(q2->z));

    return pOut;
}

NW_MATH_INLINE QUAT*
QUATSub(QUAT *pOut,  const QUAT *q1, const QUAT *q2)
{
    tof32x2(pOut->x) = __PS_SUB(tof32x2(q1->x), tof32x2(q2->x));
    tof32x2(pOut->z) = __PS_SUB(tof32x2(q1->z), tof32x2(q2->z));

    return pOut;
}

NW_MATH_INLINE QUAT*
QUATMult(QUAT* pOut, const QUAT* q1, const QUAT* q2)
{
    // o = a * b
    //
    // ox = + aw * bx + ax * bw + ay * bz - az * by;
    // oy = + aw * by + ay * bw + az * bx - ax * bz;
    // oz = + aw * bz + az * bw + ax * by - ay * bx;
    // ow = + aw * bw - ax * bx - ay * by - az * bz;
    //
    // x y, z w のペアになるように項の順序を並び替える。
    //
    // ox = ( + aw * bx + ay * bz ) - az * by + ax * bw;
    // oy = ( + az * bx - ax * bz ) + aw * by + ay * bw;
    // oz = ( - ay * bx + aw * bz ) + az * bw - ( - ax * by );
    // ow = ( - ax * bx - az * bz ) + aw * bw - ( + ay * by );
    //
    // 前2項は要素の順が逆なので演算後に入れ替える。

    const f32x2 axay = tof32x2(q1->x); // { ax ay }
    const f32x2 azaw = tof32x2(q1->z); // { az aw }
    const f32x2 bxby = tof32x2(q2->x); // { bx by }
    const f32x2 bzbw = tof32x2(q2->z); // { bz bw }

    const f32x2 AxAy = __PS_NEG(axay);
    const f32x2 Axay = __PS_MERGE01(AxAy, axay);
    const f32x2 AzAw = __PS_NEG(azaw);
    const f32x2 Azaw = __PS_MERGE01(AzAw, azaw);

    f32x2 oxy, ozw;

    oxy = __PS_MULS0(azaw, bxby);
    oxy = __PS_MADDS0(Axay, bzbw, oxy);
    oxy = __PS_MERGE10(oxy, oxy);          // 要素順を入れ替え。
    oxy = __PS_MADDS1(Azaw, bxby, oxy);
    oxy = __PS_MADDS1(axay, bzbw, oxy);

    ozw = __PS_MULS0(AxAy, bxby);
    ozw = __PS_MADDS0(Azaw, bzbw, ozw);
    ozw = __PS_MERGE10(ozw, ozw);          // 要素順を入れ替え。
    ozw = __PS_MADDS1(azaw, bzbw, ozw);
    ozw = __PS_SUB(ozw, __PS_MULS1(Axay, bxby));

    tof32x2(pOut->x) = oxy;
    tof32x2(pOut->z) = ozw;

    return pOut;
}

NW_MATH_INLINE f32
QUATDot(const QUAT* q1, const QUAT* q2)
{
    // o = a . b

    const f32x2 axay = tof32x2(q1->x);
    const f32x2 azaw = tof32x2(q1->z);
    const f32x2 bxby = tof32x2(q2->x);
    const f32x2 bzbw = tof32x2(q2->z);

    f32x2 f0;

    f0 = __PS_MUL(axay, bxby);
    f0 = __PS_MADD(azaw, bzbw, f0);
    f0 = __PS_SUM0(f0, f0, f0);

    return f0[0];
}

NW_MATH_INLINE QUAT*
QUATScale(QUAT* pOut, const QUAT* q, f32 scale)
{
    tof32x2(pOut->x) = __PS_MULS0F(tof32x2(q->x), scale);
    tof32x2(pOut->z) = __PS_MULS0F(tof32x2(q->z), scale);

    return pOut;
}

NW_MATH_INLINE QUAT*
QUATNormalize(QUAT* pOut, const QUAT* q)
{
    f32x2 xy = tof32x2(q->x);
    f32x2 zw = tof32x2(q->z);

    f32x2 f0 = __PS_MADD(xy, xy, __PS_MUL(zw, zw));
    f0 = __PS_SUM0(f0, f0, f0);

    f32 mag = f0[0];

    if ( mag >= NW_QUAT_EPSILON )
    {
        mag = 1.0F / ::std::sqrt(mag);

        tof32x2(pOut->x) = __PS_MULS0F(xy, mag);
        tof32x2(pOut->z) = __PS_MULS0F(zw, mag);
    }
    else
    {
        f32x2 zero = __PS_SUB(f0, f0);
        tof32x2(pOut->x) = zero;
        tof32x2(pOut->z) = zero;
    }

    return pOut;
}

NW_MATH_INLINE QUAT*
QUATInverse(QUAT* pOut, const QUAT* __restrict q)
{
    f32x2 xy = tof32x2(q->x);
    f32x2 zw = tof32x2(q->z);

    f32x2 f0 = __PS_MADD(xy, xy, __PS_MUL(zw, zw));
    f0 = __PS_SUM0(f0, f0, f0);

    f32 mag = f0[0];
    f32 zero = xy[0] - xy[0];
    if ( mag == zero )
    {
        mag = 1.0f;
    }

    // [Inverse] = [Conjugate] / [Magnitude]
    f32x2 szw = __PS_FDUP(1.0f / mag);
    f32x2 sxy = __PS_NEG(szw);
    szw[0] = sxy[0];

    tof32x2(pOut->x) = __PS_MUL(xy, sxy);
    tof32x2(pOut->z) = __PS_MUL(zw, szw);

    return pOut;
}

NW_MATH_INLINE QUAT*
QUATLerp(QUAT* pOut, const QUAT* __restrict q1, const QUAT* __restrict q2, f32 t)
{
    f32x2 tt = __PS_FDUP(t);
    f32x2 xy = tof32x2(q1->x);
    f32x2 zw = tof32x2(q1->z);

    tof32x2(pOut->x) = __PS_MADD(tof32x2(q2->x), tt, __PS_NMSUB(xy, tt, xy));
    tof32x2(pOut->z) = __PS_MADD(tof32x2(q2->z), tt, __PS_NMSUB(zw, tt, zw));

    return pOut;
}

NW_MATH_INLINE QUAT*
QUATSlerp(QUAT* pOut, const QUAT* __restrict q1, const QUAT* __restrict q2, f32 t)
{
    f32 theta, sin_th, cos_th;
    f32x2 tp, tq;

    f32x2 xy1 = tof32x2(q1->x);
    f32x2 zw1 = tof32x2(q1->z);
    f32x2 xy2 = tof32x2(q2->x);
    f32x2 zw2 = tof32x2(q2->z);

    f32x2 f0 = __PS_MADD(xy1, xy2, __PS_MUL(zw1, zw2));
    f0 = __PS_SUM0(f0, f0, f0);

    cos_th = f0[0];
    tq     = __PS_FDUP(1.0F);

    f32 zero = xy1[0] - xy1[0];
    if ( cos_th < zero )
    {
        cos_th = -cos_th;
        tq     = __PS_NEG(tq);
    }

    if ( cos_th <= 1.0F - NW_QUAT_EPSILON )
    {
        theta  = ::std::acos(cos_th);
        sin_th = ::std::sin(theta);
        tp     = __PS_FDUP(::std::sin((1.0F - t) * theta) / sin_th);
        tq     = __PS_MULS0F(tq, ::std::sin( t * theta ) / sin_th);
    }
    else
    {
        // cos(theta) is close to 1.0F -> linear
        tp = __PS_FDUP(1.0F - t);
        tq = __PS_MULS0F(tq, t);
    }

    tof32x2(pOut->x) = __PS_MADD(tp, xy1, __PS_MUL(tq, xy2));
    tof32x2(pOut->z) = __PS_MADD(tp, zw1, __PS_MUL(tq, zw2));

    return pOut;
}

NW_MATH_INLINE QUAT*
QUATMakeClosest(QUAT* pOut, const QUAT *q, const QUAT *qto)
{
    f32x2 xy1 = tof32x2(q->x);
    f32x2 zw1 = tof32x2(q->z);
    f32x2 xy2 = tof32x2(qto->x);
    f32x2 zw2 = tof32x2(qto->z);

    f32x2 f0 = __PS_MADD(xy1, xy2, __PS_MUL(zw1, zw2));
    f0 = __PS_SUM0(f0, f0, f0);

    f32 dot = f0[0];

    f32 zero = xy1[0] - xy1[0];
    if ( dot < zero )
    {
        xy1 = __PS_NEG(xy1);
        zw1 = __PS_NEG(zw1);
    }

    tof32x2(pOut->x) = xy1;
    tof32x2(pOut->z) = zw1;

    return pOut;
}

} } // namespace internal::intrinsics

#endif // NW_MATH_ENABLE_INTRINSICS

NW_MATH_INLINE QUAT*
QUATAdd(QUAT* pOut, const QUAT* q1, const QUAT* q2)
{
    return NW_MATH_IMPL_NS::QUATAdd(pOut, q1, q2);
}

NW_MATH_INLINE QUAT*
QUATSub(QUAT *pOut,  const QUAT *q1, const QUAT *q2)
{
    return NW_MATH_IMPL_NS::QUATSub(pOut, q1, q2);
}

NW_MATH_INLINE QUAT*
QUATDivide(QUAT* pOut, const QUAT* q1, const QUAT* q2)
{
    QUAT qtmp;

    QUATInverse(&qtmp, q2);
    QUATMult(pOut, &qtmp, q1);

    return pOut;
}

NW_MATH_INLINE QUAT*
QUATMult(QUAT* pOut, const QUAT* __restrict q1, const QUAT* __restrict q2)
{
    return NW_MATH_IMPL_NS::QUATMult(pOut, q1, q2);
}

NW_MATH_INLINE f32
QUATDot(const QUAT* q1, const QUAT* q2)
{
    return NW_MATH_IMPL_NS::QUATDot(q1, q2);
}

NW_MATH_INLINE QUAT*
QUATScale(QUAT* pOut, const QUAT* q, f32 scale)
{
    return NW_MATH_IMPL_NS::QUATScale(pOut, q, scale);
}

NW_MATH_INLINE QUAT*
QUATNormalize(QUAT* pOut, const QUAT* __restrict q)
{
    return NW_MATH_IMPL_NS::QUATNormalize(pOut, q);
}

NW_MATH_INLINE QUAT*
QUATInverse(QUAT* pOut, const QUAT* __restrict q)
{
    return NW_MATH_IMPL_NS::QUATInverse(pOut, q);
}

NW_MATH_INLINE QUAT*
QUATExp(QUAT* pOut, const QUAT* __restrict q)
{
    return internal::standard::QUATExp(pOut, q);
}

NW_MATH_INLINE QUAT*
QUATLogN(QUAT* pOut, const QUAT* __restrict q)
{
    return internal::standard::QUATLogN(pOut, q);
}

NW_MATH_INLINE QUAT*
QUATLerp(QUAT* pOut, const QUAT* __restrict q1, const QUAT* __restrict q2, f32 t)
{
    return NW_MATH_IMPL_NS::QUATLerp(pOut, q1, q2, t);
}

NW_MATH_INLINE QUAT*
QUATSlerp(QUAT* pOut, const QUAT* __restrict q1, const QUAT* __restrict q2, f32 t)
{
    return NW_MATH_IMPL_NS::QUATSlerp(pOut, q1, q2, t);
}

NW_MATH_INLINE QUAT*
QUATSquad(QUAT* pOut, const QUAT* p, const QUAT* a, const QUAT* b, const QUAT* q, f32 t)
{
    QUAT pq, ab;
    f32 t2;

    t2 = 2 * t * ( 1.0F - t );
    QUATSlerp(&pq, p, q, t);
    QUATSlerp(&ab, a, b, t);
    QUATSlerp(pOut, &pq, &ab, t2);

    return pOut;
}

NW_MATH_INLINE QUAT*
QUATMakeClosest(QUAT* pOut, const QUAT *q, const QUAT *qto)
{
    return NW_MATH_IMPL_NS::QUATMakeClosest(pOut, q, qto);
}

NW_MATH_INLINE QUAT*
QUATRotAxisRad( QUAT *pOut, const VEC3 *axis, f32 rad )
{
    f32 half, sh, ch;
    VEC3 nAxis;

    VEC3Normalize(&nAxis, axis);

    half = rad * 0.50F;
    sh   = ::std::sin(half);
    ch   = ::std::cos(half);

    pOut->x = sh * nAxis.x;
    pOut->y = sh * nAxis.y;
    pOut->z = sh * nAxis.z;
    pOut->w = ch;

    return pOut;
}

NW_MATH_INLINE QUAT*
QUATMakeVectorRotation( QUAT *pOut, const VEC3* pFrom, const VEC3* pTo )
{
    VEC3 c;
    c.SetCross( *pFrom, *pTo );
    f32 dPlus1 = VEC3Dot( pFrom, pTo ) + 1.f;

    if ( dPlus1 <= nw::math::F_ULP )
    {
        pOut->x = 1.f;
        pOut->y = 0.f;
        pOut->z = 0.f;
        pOut->w = 0.f;

        return pOut;
    }

    f32 s = FSqrt( dPlus1 * 2.f );
    f32 oos = 1.f / s;

    pOut->x = c.x * oos;
    pOut->y = c.y * oos;
    pOut->z = c.z * oos;
    pOut->w = s * 0.5f;

    return pOut;
}

NW_MATH_INLINE VEC3*
VEC3CalcRPY(VEC3* pOut, const QUAT *q)
{
    return internal::standard::VEC3CalcRPY(pOut, q);
}

} } // namespace nw::math

#endif

namespace nw { namespace math {

inline QUAT* QUATAdd(QUAT* pOut, const QUAT& q1, const QUAT& q2) { return QUATAdd( pOut, &q1, &q2 ); }
inline QUAT* QUATSub(QUAT* pOut, const QUAT& q1, const QUAT& q2) { return QUATSub( pOut, &q1, &q2 ); }
inline QUAT* QUATDivide(QUAT* pOut, const QUAT& q1, const QUAT& q2) { return QUATDivide( pOut, &q1, &q2 ); }
inline QUAT* QUATMult(QUAT* pOut, const QUAT& q1, const QUAT& q2) { return QUATMult( pOut, &q1, &q2 ); }
inline f32   QUATDot(const QUAT& q1, const QUAT& q2) { return QUATDot( &q1, &q2 ); }
inline QUAT* QUATInverse(QUAT* pOut, const QUAT& q) { return QUATInverse( pOut, &q ); }
inline QUAT* QUATScale(QUAT* pOut, const QUAT& q, f32 scale) { return QUATScale( pOut, &q, scale ); }
inline QUAT* QUATNormalize(QUAT* pOut, const QUAT& q) { return QUATNormalize( pOut, &q ); }
inline QUAT* QUATExp(QUAT* pOut, const QUAT& q) { return QUATExp( pOut, &q ); }
inline QUAT* QUATLogN(QUAT* pOut, const QUAT& q) { return QUATLogN( pOut, &q ); }
inline QUAT* QUATLerp(QUAT* pOut, const QUAT& q1, const QUAT& q2, f32 t) { return QUATLerp( pOut, &q1, &q2, t ); }
inline QUAT* QUATSlerp(QUAT* pOut, const QUAT& q1, const QUAT& q2, f32 t) { return QUATSlerp( pOut, &q1, &q2, t ); }
inline QUAT* MTX34ToQUAT(QUAT* pOut, const MTX34& mtx) { return MTX34ToQUAT( pOut, &mtx ); }
inline QUAT* QUATSquad(QUAT* pOut, const QUAT& p, const QUAT& a, const QUAT& b, const QUAT& q, f32 t) { return QUATSquad( pOut, &p, &a, &b, &q, t ); }

inline QUAT* QUATMakeClosest( QUAT*  pOut, const QUAT& q, const QUAT& qto ) { return QUATMakeClosest( pOut, &q, &qto ); }
inline QUAT* QUATRotAxisRad( QUAT* pOut, const VEC3& axis, f32 rad ) { return QUATRotAxisRad( pOut, &axis, rad ); }
inline QUAT* QUATMakeVectorRotation( QUAT *pOut, const VEC3& from, const VEC3& to ) { return QUATMakeVectorRotation( pOut, &from, &to ); }

} } // namespace nw::math

#endif
