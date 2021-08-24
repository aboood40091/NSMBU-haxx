#include <gfx/cafe/seadPrimitiveRendererCafe.h>
#include <gfx/seadPrimitiveRenderer.h>

#include "dynamic_libs/gx2_functions.h"

namespace sead {

void PrimitiveRenderer::drawLine(const Vector3f& from, const Vector3f& to, const Color4f& c0, const Color4f& c1)
{
    Vector3f dir = to - from;

    Matrix34f mtxS;
    mtxS.makeS(dir.length(), 1.0f, 1.0f);

    dir.normalize();

    Quatf q;
    q.makeVectorRotation(Vector3f(1.0f, 0.0f, 0.0f), dir);

    Matrix34f mtxR;
    mtxR.fromQuat(q);

    Matrix34f mtx;
    mtx.setMul(mtxR, mtxS);

    dir = to - from;
    dir.multScalar(0.5f);
    dir += from;
    mtx.setTranslation(dir);

    Matrix34f outMtx;
    outMtx.setMul(mModelMtx, mtx);

    mRendererImpl->drawLineImpl(outMtx, c0, c1);
}

void PrimitiveRenderer::drawCircle16(const Vector3f& pos, f32 radius, const Color4f& color)
{
    f32 diameter = 2.0f * radius;
    Vector3f scale(diameter, diameter, diameter);

    Matrix34f mtx;
    mtx.makeST(scale, pos);

    Matrix34f outMtx;
    outMtx.setMul(mModelMtx, mtx);

    mRendererImpl->drawCircle16Impl(outMtx, color);
}

void PrimitiveRenderer::drawCircle32(const Vector3f& pos, f32 radius, const Color4f& color)
{
    f32 diameter = 2.0f * radius;
    Vector3f scale(diameter, diameter, diameter);

    Matrix34f mtx;
    mtx.makeST(scale, pos);

    Matrix34f outMtx;
    outMtx.setMul(mModelMtx, mtx);

    mRendererImpl->drawCircle32Impl(outMtx, color);
}

void PrimitiveRendererCafe::drawLines_(
    const Matrix34f& model_mtx, const Color4f& c0, const Color4f& c1,
    PrimitiveRendererUtil::Vertex* vtx, u32 vtx_num, u16* idx, u32 idx_num
)
{
    GX2SetVertexUniformReg(mParamUserOffset, 12, &model_mtx);
    GX2SetVertexUniformReg(mParamColor0Offset, 4, &c0);
    GX2SetVertexUniformReg(mParamColor1Offset, 4, &c1);
    GX2SetPixelUniformReg(mParamRateOffset, 4, &Vector4f::zero);
    GX2SetAttribBuffer(0, vtx_num * sizeof(PrimitiveRendererUtil::Vertex), sizeof(PrimitiveRendererUtil::Vertex), vtx);
    GX2DrawIndexedEx(GX2_PRIMITIVE_LINE_LOOP, idx_num, GX2_INDEX_FORMAT_U16, idx, 0, 1);
}

void PrimitiveRendererCafe::drawLineImpl(
    const Matrix34f& model_mtx, const Color4f& c0, const Color4f& c1
)
{
    drawLines_(model_mtx, c0, c1, mLineVertexBuf, 2, mLineIndexBuf, 2);
}

void PrimitiveRendererCafe::drawCircle16Impl(
    const Matrix34f& model_mtx, const Color4f& edge
)
{
    drawLines_(model_mtx, edge, edge, mDiskSVertexBuf, 17, mCircleSIndexBuf, 16);
}

void PrimitiveRendererCafe::drawCircle32Impl(
    const Matrix34f& model_mtx, const Color4f& edge
)
{
    drawLines_(model_mtx, edge, edge, mDiskLVertexBuf, 33, mCircleLIndexBuf, 32);
}

}
