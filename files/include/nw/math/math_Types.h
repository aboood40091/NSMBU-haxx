#ifndef NW_MATH_TYPES_H_
#define NW_MATH_TYPES_H_

#include <nw/types.h>
//#include <nw/ut/ut_TypeTraits.h>
#include <nw/math/math_Config.h>
#include <nw/math/math_Triangular.h>
#include <nw/math/math_Vector2.h>
#include <nw/math/math_Vector3.h>
#include <nw/math/math_Vector4.h>
#include <nw/math/math_Quaternion.h>
//#include <nw/math/math_Matrix22.h>
//#include <nw/math/math_Matrix23.h>
//#include <nw/math/math_Matrix33.h>
#include <nw/math/math_Matrix34.h>
#include <nw/math/math_Matrix44.h>
//#include <nw/math/math_Matrix43.h>
#include <nw/math/math_Transform.h>

#include <cstring>

namespace nw { namespace math {

struct VEC2;
struct VEC3;
struct VEC4;
struct QUAT;

namespace internal { namespace standard {

    VEC3* VEC3TransformArray(VEC3* pOut, const MTX34* pM, const VEC3* pV, s32 count);
    VEC4* VEC3TransformArray(VEC4* pOut, const MTX44* pM, const VEC3* pV, u32 count);
    VEC3* VEC3TransformNormal(VEC3* pOut, const MTX34* pM, const VEC3* pV);
    VEC3* VEC3TransformNormalArray(VEC3* pOut, const MTX34* pM, const VEC3* pV, u32 count);
    VEC3* VEC3TransformCoord(VEC3* pOut, const MTX44* pM, const VEC3* pV);
    VEC3* VEC3TransformCoordArray(VEC3* pOut, const MTX44* pM, const VEC3* pV, u32 count);
    VEC4* VEC4Transform(VEC4* pOut, const MTX44* pM, const VEC4* pV);
    VEC4* VEC4TransformArray(VEC4* pOut, const MTX44* pM, const VEC4* pV, u32 count);
    VEC4* VEC4Transform(VEC4* pOut, const MTX34* pM, const VEC4* pV);
    VEC4* VEC4TransformArray(VEC4* pOut, const MTX34* pM, const VEC4* pV, u32 count);

} } // namespace internal::standard

#if defined(NW_MATH_ENABLE_INTRINSICS)

namespace internal { namespace intrinsics {

    VEC3* VEC3TransformArray(VEC3* pOut, const MTX34* pM, const VEC3* pV, s32 count);
    VEC4* VEC3TransformArray(VEC4* pOut, const MTX44* pM, const VEC3* pV, u32 count);
    VEC3* VEC3TransformNormal(VEC3* pOut, const MTX34* pM, const VEC3* pV);
    VEC3* VEC3TransformNormalArray(VEC3* pOut, const MTX34* pM, const VEC3* pV, u32 count);
    VEC3* VEC3TransformCoord(VEC3* pOut, const MTX44* pM, const VEC3* pV);
    VEC3* VEC3TransformCoordArray(VEC3* pOut, const MTX44* pM, const VEC3* pV, u32 count);
    VEC4* VEC4Transform(VEC4* pOut, const MTX44* pM, const VEC4* pV);
    VEC4* VEC4TransformArray(VEC4* pOut, const MTX44* pM, const VEC4* pV, u32 count);
    VEC4* VEC4Transform(VEC4* pOut, const MTX34* pM, const VEC4* pV);
    VEC4* VEC4TransformArray(VEC4* pOut, const MTX34* pM, const VEC4* pV, u32 count);

} } // namespace internal::intrinsics

#endif // NW_MATH_ENABLE_INTRINSICS

} }  // namespace nw::math

#if defined(NW_MATH_AS_INLINE)

namespace nw { namespace math {

namespace internal { namespace standard {

NW_MATH_INLINE VEC3*
VEC3TransformArray(VEC3* pOut, const MTX34* __restrict pM, const VEC3* __restrict pV, s32 count)
{
    VEC3 vTmp;
    VEC3* __restrict pOutBase = pOut;
    const f32 (*const m)[4] = pM->m;

    for (s32 i = 0; i < count; ++i)
    {
        // Vec has a 4th implicit 'w' coordinate of 1
        vTmp.x = m[0][0] * pV->x + m[0][1] * pV->y + m[0][2] * pV->z + m[0][3];
        vTmp.y = m[1][0] * pV->x + m[1][1] * pV->y + m[1][2] * pV->z + m[1][3];
        vTmp.z = m[2][0] * pV->x + m[2][1] * pV->y + m[2][2] * pV->z + m[2][3];

        // copy back
        pOut->x = vTmp.x;
        pOut->y = vTmp.y;
        pOut->z = vTmp.z;

        pV++;
        pOut++;
    }

    return pOutBase;
}

NW_MATH_INLINE VEC4*
VEC3TransformArray(VEC4* pOut, const MTX44* __restrict pM, const VEC3* __restrict pV, u32 count)
{
    VEC4* pDst = pOut;
    for (u32 i = 0; i < count; ++i)
    {
        (void)standard::VEC3Transform(pDst, pM, pV);
        ++pDst;
        ++pV;
    }

    return pOut;
}

NW_MATH_INLINE VEC3*
VEC3TransformNormal(VEC3* pOut, const MTX34* pM, const VEC3* pV)
{
    VEC3 tmp;
    tmp.x = pM->f._00 * pV->x + pM->f._01 * pV->y + pM->f._02 * pV->z;
    tmp.y = pM->f._10 * pV->x + pM->f._11 * pV->y + pM->f._12 * pV->z;
    tmp.z = pM->f._20 * pV->x + pM->f._21 * pV->y + pM->f._22 * pV->z;

    pOut->x = tmp.x;
    pOut->y = tmp.y;
    pOut->z = tmp.z;

    return pOut;
}

NW_MATH_INLINE VEC3*
VEC3TransformNormalArray(VEC3* pOut, const MTX34* pM, const VEC3* pV, u32 count)
{
    u32 i;
    VEC3 tmp;
    VEC3* pDst = pOut;

    for (i = 0; i < count; i++)
    {
        // Vec has a 4th implicit 'w' coordinate of 1
        tmp.x = pM->f._00 * pV->x + pM->f._01 * pV->y + pM->f._02 * pV->z;
        tmp.y = pM->f._10 * pV->x + pM->f._11 * pV->y + pM->f._12 * pV->z;
        tmp.z = pM->f._20 * pV->x + pM->f._21 * pV->y + pM->f._22 * pV->z;

        // copy back
        pDst->x = tmp.x;
        pDst->y = tmp.y;
        pDst->z = tmp.z;

        pV++;
        pDst++;
    }

    return pOut;
}

NW_MATH_INLINE VEC3*
VEC3TransformCoord(VEC3* pOut, const MTX44* pM, const VEC3* pV)
{
    VEC3 tmp;
    f32 rw;

    tmp.x = pM->f._00 * pV->x + pM->f._01 * pV->y + pM->f._02 * pV->z + pM->f._03;
    tmp.y = pM->f._10 * pV->x + pM->f._11 * pV->y + pM->f._12 * pV->z + pM->f._13;
    tmp.z = pM->f._20 * pV->x + pM->f._21 * pV->y + pM->f._22 * pV->z + pM->f._23;
       rw = pM->f._30 * pV->x + pM->f._31 * pV->y + pM->f._32 * pV->z + pM->f._33;
    rw = 1.f / rw;

    pOut->x = rw * tmp.x;
    pOut->y = rw * tmp.y;
    pOut->z = rw * tmp.z;

    return pOut;
}

NW_MATH_INLINE VEC3*
VEC3TransformCoordArray(VEC3* pOut, const MTX44* pM, const VEC3* pV, u32 count)
{
    VEC3* pDst = pOut;
    for (u32 i = 0; i < count; ++i)
    {
        (void)standard::VEC3TransformCoord(pDst, pM, pV);
        ++pDst;
        ++pV;
    }

    return pOut;
}

NW_MATH_INLINE VEC4*
VEC4Transform(VEC4* pOut, const MTX44* __restrict pM, const VEC4* __restrict pV)
{
    VEC4 tmp;
    tmp.x = pM->f._00 * pV->x + pM->f._01 * pV->y + pM->f._02 * pV->z + pM->f._03 * pV->w;
    tmp.y = pM->f._10 * pV->x + pM->f._11 * pV->y + pM->f._12 * pV->z + pM->f._13 * pV->w;
    tmp.z = pM->f._20 * pV->x + pM->f._21 * pV->y + pM->f._22 * pV->z + pM->f._23 * pV->w;
    tmp.w = pM->f._30 * pV->x + pM->f._31 * pV->y + pM->f._32 * pV->z + pM->f._33 * pV->w;

    pOut->x = tmp.x;
    pOut->y = tmp.y;
    pOut->z = tmp.z;
    pOut->w = tmp.w;

    return pOut;
}

NW_MATH_INLINE VEC4*
VEC4TransformArray(VEC4* pOut, const MTX44* pM, const VEC4* pV, u32 count)
{
    VEC4* pDst = pOut;
    for (u32 i = 0; i < count; ++i)
    {
        (void)standard::VEC4Transform(pDst, pM, pV);
        ++pDst;
        ++pV;
    }

    return pOut;
}

NW_MATH_INLINE VEC4*
VEC4Transform(VEC4* pOut, const MTX34* __restrict pM, const VEC4* __restrict pV)
{
    VEC4 tmp;
    tmp.x = pM->f._00 * pV->x + pM->f._01 * pV->y + pM->f._02 * pV->z + pM->f._03 * pV->w;
    tmp.y = pM->f._10 * pV->x + pM->f._11 * pV->y + pM->f._12 * pV->z + pM->f._13 * pV->w;
    tmp.z = pM->f._20 * pV->x + pM->f._21 * pV->y + pM->f._22 * pV->z + pM->f._23 * pV->w;

    pOut->x = tmp.x;
    pOut->y = tmp.y;
    pOut->z = tmp.z;
    pOut->w = pV->w;

    return pOut;
}

NW_MATH_INLINE VEC4*
VEC4TransformArray(VEC4* pOut, const MTX34* pM, const VEC4* pV, u32 count)
{
    VEC4* pDst = pOut;
    for (u32 i = 0; i < count; ++i)
    {
        (void)standard::VEC4Transform(pDst, pM, pV);
        ++pDst;
        ++pV;
    }

    return pOut;
}

} } // namespace internal::standard

#if defined(NW_MATH_ENABLE_INTRINSICS)

namespace internal { namespace intrinsics {

NW_MATH_INLINE VEC3*
VEC3TransformArray(VEC3* pOut, const MTX34* __restrict pM, const VEC3* __restrict pV, s32 count)
{
    f32x2 m00m01 = __PSQ_LX(pM, offsetof(MTX44, f._00), 0, 0);
    f32x2 m10m11 = __PSQ_LX(pM, offsetof(MTX44, f._10), 0, 0);
    f32x2 m02m03 = __PSQ_LX(pM, offsetof(MTX44, f._02), 0, 0);
    f32x2 m12m13 = __PSQ_LX(pM, offsetof(MTX44, f._12), 0, 0);

    f32x2 m00m10 = __PS_MERGE00(m00m01, m10m11);
    f32x2 m01m11 = __PS_MERGE11(m00m01, m10m11);
    f32x2 m02m12 = __PS_MERGE00(m02m03, m12m13);
    f32x2 m03m13 = __PS_MERGE11(m02m03, m12m13);

    f32x2 m20m30 = __PSQ_LX(pM, offsetof(MTX34, f._20), 1, 0);
    f32x2 m21m31 = __PSQ_LX(pM, offsetof(MTX34, f._21), 1, 0);
    f32x2 m22m32 = __PSQ_LX(pM, offsetof(MTX34, f._22), 1, 0);
    f32x2 m23m33 = __PSQ_LX(pM, offsetof(MTX34, f._23), 1, 0);

    VEC3* pDst = pOut;
    for (s32 i = 0; i < count; ++i)
    {
        f32x2 fp0, fp1;

        // { xy zw } = { x y z 1 }
        f32x2 xy = __PSQ_LX(pV, offsetof(VEC3, x), 0, 0);
        f32x2 zw = __PSQ_LX(pV, offsetof(VEC3, z), 1, 0);

        // fp0 = [ m00 m01 m02 m03 ] . T[ x y z 1 ]
        //       [ m10 m11 m12 m03 ] .
        fp0 = __PS_MADDS0(m02m12, zw, m03m13);
        fp0 = __PS_MADDS1(m01m11, xy, fp0);
        fp0 = __PS_MADDS0(m00m10, xy, fp0);

        // fp1 = [ m20 m21 m22, m23 ] . T[ x y z 1 ]
        //       [ m30 m31 m32, m33 ]
        fp1 = __PS_MADDS0(m22m32, zw, m23m33);
        fp1 = __PS_MADDS1(m21m31, xy, fp1);
        fp1 = __PS_MADDS0(m20m30, xy, fp1);

        tof32x2(pDst->x) = fp0;
        pDst->z = fp1[0];

        pV++;
        pDst++;
    }

    return pOut;
}

NW_MATH_INLINE VEC4*
VEC3TransformArray(VEC4* pOut, const MTX44* __restrict pM, const VEC3* __restrict pV, u32 count)
{
    f32x2 m00m01 = __PSQ_LX(pM, offsetof(MTX44, f._00), 0, 0);
    f32x2 m10m11 = __PSQ_LX(pM, offsetof(MTX44, f._10), 0, 0);
    f32x2 m02m03 = __PSQ_LX(pM, offsetof(MTX44, f._02), 0, 0);
    f32x2 m12m13 = __PSQ_LX(pM, offsetof(MTX44, f._12), 0, 0);

    f32x2 m00m10 = __PS_MERGE00(m00m01, m10m11);
    f32x2 m01m11 = __PS_MERGE11(m00m01, m10m11);
    f32x2 m02m12 = __PS_MERGE00(m02m03, m12m13);
    f32x2 m03m13 = __PS_MERGE11(m02m03, m12m13);

    f32x2 m20m21 = __PSQ_LX(pM, offsetof(MTX44, f._20), 0, 0);
    f32x2 m30m31 = __PSQ_LX(pM, offsetof(MTX44, f._30), 0, 0);
    f32x2 m22m23 = __PSQ_LX(pM, offsetof(MTX44, f._22), 0, 0);
    f32x2 m32m33 = __PSQ_LX(pM, offsetof(MTX44, f._32), 0, 0);

    f32x2 m20m30 = __PS_MERGE00(m20m21, m30m31);
    f32x2 m21m31 = __PS_MERGE11(m20m21, m30m31);
    f32x2 m22m32 = __PS_MERGE00(m22m23, m32m33);
    f32x2 m23m33 = __PS_MERGE11(m22m23, m32m33);

    VEC4* pDst = pOut;
    for (u32 i = 0; i < count; ++i)
    {
        f32x2 fp0, fp1;

        // { xy zw } = { x y z 1 }
        f32x2 xy = __PSQ_LX(pV, offsetof(VEC3, x), 0, 0);
        f32x2 zw = __PSQ_LX(pV, offsetof(VEC3, z), 1, 0);

        // fp0 = [ m00 m01 m02, m03 ] . T[ x y z 1 ]
        //       [ m10 m11 m12, m13 ]
        fp0 = __PS_MADDS0(m02m12, zw, m03m13);
        fp0 = __PS_MADDS1(m01m11, xy, fp0);
        fp0 = __PS_MADDS0(m00m10, xy, fp0);

        // fp1 = [ m20 m21 m22, m23 ] . T[ x y z 1 ]
        //       [ m30 m31 m32, m33 ]
        fp1 = __PS_MADDS0(m22m32, zw, m23m33);
        fp1 = __PS_MADDS1(m21m31, xy, fp1);
        fp1 = __PS_MADDS0(m20m30, xy, fp1);

        tof32x2(pDst->x) = fp0;
        tof32x2(pDst->z) = fp1;

        ++pDst;
        ++pV;
    }

    return pOut;
}

NW_MATH_INLINE VEC3*
VEC3TransformNormal(VEC3* pOut, const MTX34* __restrict pM, const VEC3* __restrict pV)
{
    f32x2 m00m01 = __PSQ_LX(pM, offsetof(MTX34, m[0][0]), 0, 0);
    f32x2 m02m03 = __PSQ_LX(pM, offsetof(MTX34, m[0][2]), 1, 0);
    f32x2 m10m11 = __PSQ_LX(pM, offsetof(MTX34, m[1][0]), 0, 0);
    f32x2 m12m13 = __PSQ_LX(pM, offsetof(MTX34, m[1][2]), 1, 0);
    f32x2 m20m21 = __PSQ_LX(pM, offsetof(MTX34, m[2][0]), 0, 0);
    f32x2 m22m23 = __PSQ_LX(pM, offsetof(MTX34, m[2][2]), 1, 0);

    f32x2 fp0, fp1, fp2;

    // { xy zw } = { x y z 1 }
    f32x2 xy = __PSQ_LX(pV, offsetof(VEC3, x), 0, 0);
    f32x2 zw = __PSQ_LX(pV, offsetof(VEC3, z), 1, 0);

    // fp0 = [ m00 m01 m02 0 ] . T[ x y z 1 ]
    fp0 = __PS_MUL(m00m01, xy);
    fp0 = __PS_SUM0(fp0, fp0, fp0);
    fp0 = __PS_MADD(m02m03, zw, fp0);

    pOut->x = fp0[0];

    // fp1 = [ m10 m11 m12 0 ] . T[ x y z 1 ]
    fp1 = __PS_MUL(m10m11, xy);
    fp1 = __PS_SUM0(fp1, fp1, fp1);
    fp1 = __PS_MADD(m12m13, zw, fp1);

    pOut->y = fp1[0];

    // fp2 = [ m20 m21 m22 0 ] . T[ x y z 1 ]
    fp2 = __PS_MUL(m20m21, xy);
    fp2 = __PS_SUM0(fp2, fp2, fp2);
    fp2 = __PS_MADD(m22m23, zw, fp2);

    pOut->z = fp2[0];

    return pOut;
}

NW_MATH_INLINE VEC3*
VEC3TransformNormalArray(VEC3* pOut, const MTX34* __restrict pM, const VEC3* __restrict pV, u32 count)
{
    f32x2 m00m01 = __PSQ_LX(pM, offsetof(MTX34, f._00), 0, 0);
    f32x2 m10m11 = __PSQ_LX(pM, offsetof(MTX34, f._10), 0, 0);
    f32x2 m00m10 = __PS_MERGE00(m00m01, m10m11);
    f32x2 m01m11 = __PS_MERGE11(m00m01, m10m11);
    f32x2 m02m12 = { pM->f._02, pM->f._12 };
    f32x2 m20m21 = __PSQ_LX(pM, offsetof(MTX34, f._20), 0, 0);
    f32x2 m22    = __PSQ_LX(pM, offsetof(MTX34, f._22), 1, 0);

    VEC3* pDst = pOut;
    for (s32 i = 0; i < count; ++i)
    {
        f32x2 fp0, fp1;

        // { xy zw } = { x y z 1 }
        f32x2 zw = __PSQ_LX(pV, offsetof(VEC3, z), 1, 0);
        f32x2 xy = __PSQ_LX(pV, offsetof(VEC3, x), 0, 0);

        // fp0 = [ m00 m01 m02 m03 ] . T[ x y z 0 ]
        //       [ m10 m11 m12 m13 ] .
        fp0 = __PS_MULS0(m02m12, zw);
        fp0 = __PS_MADDS1(m01m11, xy, fp0);
        fp0 = __PS_MADDS0(m00m10, xy, fp0);

        // fp1 = [ m20 m21 m22 m23 ] . T[ x y z 0 ]
        fp1 = __PS_MUL(m20m21, xy);
        fp1 = __PS_SUM0(fp1, fp1, fp1);
        fp1 = __PS_MADDS0(m22, zw, fp1);

        tof32x2(pDst->x) = fp0;
        pDst->z = fp1[0];

        pV++;
        pDst++;
    }

    return pOut;
}

NW_MATH_INLINE VEC3*
VEC3TransformCoord(VEC3* pOut, const MTX44* __restrict pM, const VEC3* __restrict pV)
{
    // { xy zw } = { x y z 1 }
    const f32x2 xy = __PSQ_LX(pV, offsetof(VEC3, x), 0, 0);
    const f32x2 zw = __PSQ_LX(pV, offsetof(VEC3, z), 1, 0);

    f32x2 m30m31 = __PSQ_LX(pM, offsetof(MTX44, f._30), 0, 0);
    f32x2 m32m33 = __PSQ_LX(pM, offsetof(MTX44, f._32), 0, 0);

    f32x2 fp0, fp1, fp2, fp3;

    // fp3 = [ m30 m31 m32, m33 ] . T[ x y z 1 ]
    fp3 = __PS_MUL(m30m31, xy);
    fp3 = __PS_MADD(m32m33, zw, fp3);
    fp3 = __PS_SUM0(fp3, fp3, fp3);

    // rw[1] = 1 / w
    const f32x2 rw = __PS_DIV(zw, __PS_MERGE00(fp3, fp3));

    f32x2 m00m01 = __PSQ_LX(pM, offsetof(MTX44, f._00), 0, 0);
    f32x2 m02m03 = __PSQ_LX(pM, offsetof(MTX44, f._02), 0, 0);
    f32x2 m10m11 = __PSQ_LX(pM, offsetof(MTX44, f._10), 0, 0);
    f32x2 m12m13 = __PSQ_LX(pM, offsetof(MTX44, f._12), 0, 0);
    f32x2 m20m21 = __PSQ_LX(pM, offsetof(MTX44, f._20), 0, 0);
    f32x2 m22m23 = __PSQ_LX(pM, offsetof(MTX44, f._22), 0, 0);

    // fp0 = [ m00 m01 m02, m03 ] . T[ x y z 1 ]
    //       [ m10 m11 m12, m13 ]
    fp0 = __PS_MUL(m00m01, xy);
    fp1 = __PS_MUL(m10m11, xy);
    fp0 = __PS_MADD(m02m03, zw, fp0);
    fp1 = __PS_MADD(m12m13, zw, fp1);
    fp0 = __PS_SUM0(fp0, fp0, fp0);
    fp0 = __PS_SUM1(fp1, fp0, fp1);
    fp0 = __PS_MULS1(fp0, rw);

    // fp2 = [ m20 m21 m22, m23 ] . T[ x y z 1 ]
    fp2 = __PS_MUL(m20m21, xy);
    fp2 = __PS_MADD(m22m23, zw, fp2);
    fp2 = __PS_SUM0(fp2, fp2, fp2);
    fp2 = __PS_MULS1(fp2, rw);

    tof32x2(pOut->x) = fp0;
    pOut->z = fp2[0];

    return pOut;
}

NW_MATH_INLINE VEC3*
VEC3TransformCoordArray(VEC3* pOut, const MTX44* pM, const VEC3* pV, u32 count)
{
    const f32x2 m00m01 = __PSQ_LX(pM, offsetof(MTX44, f._00), 0, 0);
    const f32x2 m02m03 = __PSQ_LX(pM, offsetof(MTX44, f._02), 0, 0);
    const f32x2 m10m11 = __PSQ_LX(pM, offsetof(MTX44, f._10), 0, 0);
    const f32x2 m12m13 = __PSQ_LX(pM, offsetof(MTX44, f._12), 0, 0);
    const f32x2 m20m21 = __PSQ_LX(pM, offsetof(MTX44, f._20), 0, 0);
    const f32x2 m22m23 = __PSQ_LX(pM, offsetof(MTX44, f._22), 0, 0);
    const f32x2 m30m31 = __PSQ_LX(pM, offsetof(MTX44, f._30), 0, 0);
    const f32x2 m32m33 = __PSQ_LX(pM, offsetof(MTX44, f._32), 0, 0);

    const f32x2 m00m10 = __PS_MERGE00(m00m01, m10m11);
    const f32x2 m01m11 = __PS_MERGE11(m00m01, m10m11);
    const f32x2 m02m12 = __PS_MERGE00(m02m03, m12m13);
    const f32x2 m03m13 = __PS_MERGE11(m02m03, m12m13);
    const f32x2 m20m30 = __PS_MERGE00(m20m21, m30m31);
    const f32x2 m21m31 = __PS_MERGE11(m20m21, m30m31);
    const f32x2 m22m32 = __PS_MERGE00(m22m23, m32m33);
    const f32x2 m23m33 = __PS_MERGE11(m22m23, m32m33);

    VEC3* pDst = pOut;
    for (u32 i = 0; i < count; ++i)
    {
        f32x2 fp0, fp1;

        // { xy zw } = { x y z 1 }
        const f32x2 xy = __PSQ_LX(pV, offsetof(VEC3, x), 0, 0);
        const f32x2 zw = __PSQ_LX(pV, offsetof(VEC3, z), 1, 0);

        // fp0 = [ m00 m01 m02, m03 ] . T[ x y z 1 ]
        //       [ m10 m11 m12, m13 ]
        fp0 = __PS_MADDS0(m02m12, zw, m03m13);
        fp0 = __PS_MADDS1(m01m11, xy, fp0);
        fp0 = __PS_MADDS0(m00m10, xy, fp0);

        // fp1 = [ m20 m21 m22, m23 ] . T[ x y z 1 ]
        //       [ m30 m31 m32, m33 ]
        fp1 = __PS_MADDS0(m22m32, zw, m23m33);
        fp1 = __PS_MADDS1(m21m31, xy, fp1);
        fp1 = __PS_MADDS0(m20m30, xy, fp1);

        // rw[1] = 1 / w
        const f32x2 rw = __PS_DIV(zw, __PS_MERGE11(fp1, fp1));

        fp0 = __PS_MULS1(fp0, rw);
        fp1 = __PS_MULS1(fp1, rw);

        tof32x2(pDst->x) = fp0;
        pDst->z = fp1[0];

        ++pDst;
        ++pV;
    }

    return pOut;
}

NW_MATH_INLINE VEC4*
VEC4Transform(VEC4* pOut, const MTX44* __restrict pM, const VEC4* __restrict pV)
{
    const f32x2 m00m01 = __PSQ_LX(pM, offsetof(MTX44, m[0][0]), 0, 0);
    const f32x2 m02m03 = __PSQ_LX(pM, offsetof(MTX44, m[0][2]), 0, 0);
    const f32x2 m10m11 = __PSQ_LX(pM, offsetof(MTX44, m[1][0]), 0, 0);
    const f32x2 m12m13 = __PSQ_LX(pM, offsetof(MTX44, m[1][2]), 0, 0);
    const f32x2 m20m21 = __PSQ_LX(pM, offsetof(MTX44, m[2][0]), 0, 0);
    const f32x2 m22m23 = __PSQ_LX(pM, offsetof(MTX44, m[2][2]), 0, 0);
    const f32x2 m30m31 = __PSQ_LX(pM, offsetof(MTX44, m[3][0]), 0, 0);
    const f32x2 m32m33 = __PSQ_LX(pM, offsetof(MTX44, m[3][2]), 0, 0);

    f32x2 fp0, fp1, fp2, fp3;

    // { xy zw } = { x y z w }
    const f32x2 xy = __PSQ_LX(pV, offsetof(VEC4, x), 0, 0);
    const f32x2 zw = __PSQ_LX(pV, offsetof(VEC4, z), 0, 0);

    // fp1 = [ m00 m01 m02, m03 ] . T[ x y z w ]
    //       [ m10 m11 m12, m13 ]
    fp0 = __PS_MUL(m00m01, xy);
    fp1 = __PS_MUL(m10m11, xy);
    fp0 = __PS_MADD(m02m03, zw, fp0);
    fp1 = __PS_MADD(m12m13, zw, fp1);
    fp0 = __PS_SUM0(fp0, fp0, fp0);
    fp1 = __PS_SUM1(fp1, fp0, fp1);

    // fp3 = [ m20 m21 m22, m23 ] . T[ x y z w ]
    //       [ m30 m31 m32, m33 ]
    fp2 = __PS_MUL(m20m21, xy);
    fp3 = __PS_MUL(m30m31, xy);
    fp2 = __PS_MADD(m22m23, zw, fp2);
    fp3 = __PS_MADD(m32m33, zw, fp3);
    fp2 = __PS_SUM0(fp2, fp2, fp2);
    fp3 = __PS_SUM1(fp3, fp2, fp3);

    tof32x2(pOut->x) = fp1;
    tof32x2(pOut->z) = fp3;

    return pOut;
}

NW_MATH_INLINE VEC4*
VEC4TransformArray(VEC4* pOut, const MTX44* pM, const VEC4* pV, u32 count)
{
    f32x2 m00m01 = __PSQ_LX(pM, offsetof(MTX44, f._00), 0, 0);
    f32x2 m02m03 = __PSQ_LX(pM, offsetof(MTX44, f._02), 0, 0);
    f32x2 m10m11 = __PSQ_LX(pM, offsetof(MTX44, f._10), 0, 0);
    f32x2 m12m13 = __PSQ_LX(pM, offsetof(MTX44, f._12), 0, 0);

    f32x2 m00m10 = __PS_MERGE00(m00m01, m10m11);
    f32x2 m01m11 = __PS_MERGE11(m00m01, m10m11);
    f32x2 m02m12 = __PS_MERGE00(m02m03, m12m13);
    f32x2 m03m13 = __PS_MERGE11(m02m03, m12m13);

    f32x2 m20m21 = __PSQ_LX(pM, offsetof(MTX44, f._20), 0, 0);
    f32x2 m22m23 = __PSQ_LX(pM, offsetof(MTX44, f._22), 0, 0);
    f32x2 m30m31 = __PSQ_LX(pM, offsetof(MTX44, f._30), 0, 0);
    f32x2 m32m33 = __PSQ_LX(pM, offsetof(MTX44, f._32), 0, 0);

    f32x2 m20m30 = __PS_MERGE00(m20m21, m30m31);
    f32x2 m21m31 = __PS_MERGE11(m20m21, m30m31);
    f32x2 m22m32 = __PS_MERGE00(m22m23, m32m33);
    f32x2 m23m33 = __PS_MERGE11(m22m23, m32m33);

    VEC4* pDst = pOut;
    for (u32 i = 0; i < count; ++i)
    {
        f32x2 fp0, fp1;

        // { xy zw } = { x y z w }
        f32x2 xy = __PSQ_LX(pV, offsetof(VEC4, x), 0, 0);
        f32x2 zw = __PSQ_LX(pV, offsetof(VEC4, z), 0, 0);

        // fp0 = [ m00 m01 m02, m03 ] . T[ x y z w ]
        //       [ m10 m11 m12, m13 ]
        fp0 = __PS_MULS0(m00m10, xy);
        fp0 = __PS_MADDS1(m01m11, xy, fp0);
        fp0 = __PS_MADDS0(m02m12, zw, fp0);
        fp0 = __PS_MADDS1(m03m13, zw, fp0);

        // fp1 = [ m20 m21 m22, m23 ] . T[ x y z w ]
        //       [ m30 m31 m32, m33 ]
        fp1 = __PS_MULS0(m20m30, xy);
        fp1 = __PS_MADDS1(m21m31, xy, fp1);
        fp1 = __PS_MADDS0(m22m32, zw, fp1);
        fp1 = __PS_MADDS1(m23m33, zw, fp1);

        tof32x2(pDst->x) = fp0;
        tof32x2(pDst->z) = fp1;

        ++pDst;
        ++pV;
    }

    return pOut;
}

NW_MATH_INLINE VEC4*
VEC4Transform(VEC4* pOut, const MTX34* __restrict pM, const VEC4* __restrict pV)
{
    const f32x2 m00m01 = __PSQ_LX(pM, offsetof(MTX44, m[0][0]), 0, 0);
    const f32x2 m02m03 = __PSQ_LX(pM, offsetof(MTX44, m[0][2]), 0, 0);
    const f32x2 m10m11 = __PSQ_LX(pM, offsetof(MTX44, m[1][0]), 0, 0);
    const f32x2 m12m13 = __PSQ_LX(pM, offsetof(MTX44, m[1][2]), 0, 0);
    const f32x2 m20m21 = __PSQ_LX(pM, offsetof(MTX44, m[2][0]), 0, 0);
    const f32x2 m22m23 = __PSQ_LX(pM, offsetof(MTX44, m[2][2]), 0, 0);

    f32x2 fp0, fp1, fp2;

    // { xy zw } = { x y z w }
    const f32x2 xy = __PSQ_LX(pV, offsetof(VEC4, x), 0, 0);
    const f32x2 zw = __PSQ_LX(pV, offsetof(VEC4, z), 0, 0);

    // fp1 = [ m00 m01 m02 m03 ] . T[ x y z w ]
    //       [ m10 m11 m12 m13 ]
    fp0 = __PS_MUL(m00m01, xy);
    fp0 = __PS_MADD(m02m03, zw, fp0);
    fp0 = __PS_SUM0(fp0, fp0, fp0);

    fp1 = __PS_MUL(m10m11, xy);
    fp1 = __PS_MADD(m12m13, zw, fp1);
    fp1 = __PS_SUM1(fp1, fp0, fp1);

    // fp2 = [ m20 m21 m22 m23 ] . T[ x y z w ]
    //       [   0   0   0    1 ]
    fp2 = __PS_MUL(m20m21, xy);
    fp2 = __PS_MADD(m22m23, zw, fp2);
    fp2 = __PS_SUM0(fp2, zw, fp2);

    tof32x2(pOut->x) = fp1;
    tof32x2(pOut->z) = fp2;

    return pOut;
}

NW_MATH_INLINE VEC4*
VEC4TransformArray(VEC4* pOut, const MTX34* pM, const VEC4* pV, u32 count)
{
    f32x2 m00m01 = __PSQ_LX(pM, offsetof(MTX44, f._00), 0, 0);
    f32x2 m02m03 = __PSQ_LX(pM, offsetof(MTX44, f._02), 0, 0);
    f32x2 m10m11 = __PSQ_LX(pM, offsetof(MTX44, f._10), 0, 0);
    f32x2 m12m13 = __PSQ_LX(pM, offsetof(MTX44, f._12), 0, 0);

    f32x2 m20m21 = __PSQ_LX(pM, offsetof(MTX44, f._20), 0, 0);
    f32x2 m22m23 = __PSQ_LX(pM, offsetof(MTX44, f._22), 0, 0);

    f32x2 m00m10 = __PS_MERGE00(m00m01, m10m11);
    f32x2 m01m11 = __PS_MERGE11(m00m01, m10m11);
    f32x2 m02m12 = __PS_MERGE00(m02m03, m12m13);
    f32x2 m03m13 = __PS_MERGE11(m02m03, m12m13);

    VEC4* pDst = pOut;
    for (u32 i = 0; i < count; ++i)
    {
        f32x2 fp0, fp1;

        // { xy zw } = { x y z w }
        f32x2 xy = __PSQ_LX(pV, offsetof(VEC4, x), 0, 0);
        f32x2 zw = __PSQ_LX(pV, offsetof(VEC4, z), 0, 0);

        // fp0 = [ m00 m01 m02, m03 ] . T[ x y z w ]
        //       [ m10 m11 m12, m13 ]
        // fp1 = [ m20 m21 m22, m23 ] . T[ x y z w ]
        //       [   0   0   0    1 ]
        fp0 = __PS_MULS0(m00m10, xy);
        fp0 = __PS_MADDS1(m01m11, xy, fp0);
        fp0 = __PS_MADDS0(m02m12, zw, fp0);
        fp0 = __PS_MADDS1(m03m13, zw, fp0);

        fp1 = __PS_MUL(m20m21, xy);
        fp1 = __PS_MADD(m22m23, zw, fp1);
        fp1 = __PS_SUM0(fp1, zw, fp1);

        tof32x2(pDst->x) = fp0;
        tof32x2(pDst->z) = fp1;

        ++pDst;
        ++pV;
    }

    return pOut;
}

} } // namespace internal::intrinsics

#endif // NW_MATH_ENABLE_INTRINSICS

NW_MATH_INLINE QUAT*
MTX34ToQUAT(QUAT* pOut, const MTX34* pMtx)
{
    f32 tr, s;
    s32 i, j, k;
    s32 nxt[3] = {1, 2, 0};
    f32 q[3];

    const f32 (*const m)[4] = pMtx->m;

    tr = m[0][0] + m[1][1] + m[2][2];
    if ( tr > 0.0f )
    {
        s = (f32)::std::sqrt(tr + 1.0f);
        pOut->w = s * 0.5f;
        s = 0.5f / s;
        pOut->x = (m[2][1] - m[1][2]) * s;
        pOut->y = (m[0][2] - m[2][0]) * s;
        pOut->z = (m[1][0] - m[0][1]) * s;
    }
    else
    {
        i = 0;
        if (m[1][1] > m[0][0]) i = 1;
        if (m[2][2] > m[i][i]) i = 2;
        j = nxt[i];
        k = nxt[j];
        s = (f32)::std::sqrt( (m[i][i] - (m[j][j] + m[k][k])) + 1.0f );
        q[i] = s * 0.5f;

        if (s!=0.0f)
            s = 0.5f / s;

        pOut->w = (m[k][j] - m[j][k]) * s;
        q[j] = (m[i][j] + m[j][i]) * s;
        q[k] = (m[i][k] + m[k][i]) * s;

        pOut->x = q[0];
        pOut->y = q[1];
        pOut->z = q[2];
    }

    return pOut;
}

NW_MATH_INLINE VEC3*
VEC3TransformArray(VEC3* pOut, const MTX34* __restrict pM, const VEC3* __restrict pV, s32 count)
{
    return NW_MATH_IMPL_NS::VEC3TransformArray(pOut, pM, pV, count);
}

NW_MATH_INLINE VEC4*
VEC3TransformArray(VEC4* pOut, const MTX44* __restrict pM, const VEC3* __restrict pV, u32 count)
{
    return NW_MATH_IMPL_NS::VEC3TransformArray(pOut, pM, pV, count);
}

NW_MATH_INLINE VEC3*
VEC3TransformNormal(VEC3* pOut, const MTX34* pM, const VEC3* pV)
{
    return NW_MATH_IMPL_NS::VEC3TransformNormal(pOut, pM, pV);
}

NW_MATH_INLINE VEC3*
VEC3TransformNormalArray(VEC3* pOut, const MTX34* pM, const VEC3* pV, u32 count)
{
    return NW_MATH_IMPL_NS::VEC3TransformNormalArray(pOut, pM, pV, count);
}

NW_MATH_INLINE VEC3*
VEC3TransformCoord(VEC3* pOut, const MTX44* pM, const VEC3* pV)
{
    return NW_MATH_IMPL_NS::VEC3TransformCoord(pOut, pM, pV);
}

NW_MATH_INLINE VEC3*
VEC3TransformCoordArray(VEC3* pOut, const MTX44* pM, const VEC3* pV, u32 count)
{
    return NW_MATH_IMPL_NS::VEC3TransformCoordArray(pOut, pM, pV, count);
}

NW_MATH_INLINE VEC4*
VEC4Transform(VEC4* pOut, const MTX44* __restrict pM, const VEC4* __restrict pV)
{
    return NW_MATH_IMPL_NS::VEC4Transform(pOut, pM, pV);
}

NW_MATH_INLINE VEC4*
VEC4TransformArray(VEC4* pOut, const MTX44* pM, const VEC4* pV, u32 count)
{
    return NW_MATH_IMPL_NS::VEC4TransformArray(pOut, pM, pV, count);
}

NW_MATH_INLINE VEC4*
VEC4Transform(VEC4* pOut, const MTX34* __restrict pM, const VEC4* __restrict pV)
{
    return NW_MATH_IMPL_NS::VEC4Transform(pOut, pM, pV);
}

NW_MATH_INLINE VEC4*
VEC4TransformArray(VEC4* pOut, const MTX34* pM, const VEC4* pV, u32 count)
{
    return NW_MATH_IMPL_NS::VEC4TransformArray(pOut, pM, pV, count);
}

} } // namespace nw::math

#endif

#endif


