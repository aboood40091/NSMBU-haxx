#ifndef EFT_PRIMITIVE_H_
#define EFT_PRIMITIVE_H_

#include <nw/eft/eft_typeDef.h>
#include <nw/eft/cafe/eft_CafeWrapper.h>

namespace nw { namespace eft {

class Primitive
{
public:
    Primitive()
    {
        mInitialized       = false;
        mPrimitiveIndexNum = 0;
    }

    void Initialize(Heap* heap, u32 indexNum,
                    void* posSrc, u32 posSrcSize,
                    void* norSrc, u32 norSrcSize,
                    void* colSrc, u32 colSrcSize,
                    void* texSrc, u32 texSrcSize,
                    void* idxSrc, u32 idxSrcSize)
    {
        if (posSrc && /*colSrc &&*/ texSrc && idxSrc)
            mInitialized = true;
        else
            return;

        mPrimitiveIndexNum = indexNum;

        if (posSrc)
        {
            nw::math::VEC3* pos = static_cast<nw::math::VEC3*>(mPrimitivePosVB.AllocateVertexBuffer(heap, posSrcSize, 3));
            /* MemUtil::Copy */ memcpy(pos, posSrc, posSrcSize);
            fPos = &pos->x;
            mPrimitivePosVB.Invalidate();
        }

        if (norSrc)
        {
            nw::math::VEC3* nor = static_cast<nw::math::VEC3*>(mPrimitiveNormalVB.AllocateVertexBuffer(heap, norSrcSize, 3));
            /* MemUtil::Copy */ memcpy(nor, norSrc, norSrcSize);
            fNor = &nor->x;
            mPrimitiveNormalVB.Invalidate();
        }

        if (colSrc)
        {
            nw::math::VEC4* col = static_cast<nw::math::VEC4*>(mPrimitiveColorVB.AllocateVertexBuffer(heap, colSrcSize, 4));
            /* MemUtil::Copy */ memcpy(col, colSrc, colSrcSize);
            fCol = &col->x;
            mPrimitiveColorVB.Invalidate();
        }
        else
        {
            nw::math::VEC4* col = static_cast<nw::math::VEC4*>(
                mPrimitiveColorVB.AllocateVertexBuffer(heap, mPrimitiveIndexNum * sizeof(nw::math::VEC4), 4));
            //fCol = &col->x; <-- NSMBU doesn't do this, but MK8 does. Bug in older Eft?
            for (u32 i = 0; i < mPrimitiveIndexNum; ++i)
            {
                col->x = 1.0f;
                col->y = 1.0f;
                col->z = 1.0f;
                col->w = 1.0f;
                col++;
            }
            mPrimitiveColorVB.Invalidate();
        }

        if (texSrc && texSrcSize != 0)
        {
            nw::math::VEC4* tex = static_cast<nw::math::VEC4*>(mPrimitiveTexCrdVB.AllocateVertexBuffer(heap, texSrcSize, 2));
            /* MemUtil::Copy */ memcpy(tex, texSrc, texSrcSize);
            fUv = &tex->x;
            mPrimitiveTexCrdVB.Invalidate();
        }
/*
        else
        {
            // EFT_ASSERT( "[EFT] Primitive Texture Coord is Error." );
        }
*/

        if (idxSrc && idxSrcSize != 0)
        {
            u32* idx = static_cast<u32*>(mPrimitiveIndexVB.AllocateVertexBuffer(heap, idxSrcSize, 1));
            /* MemUtil::Copy */ memcpy(idx, idxSrc, idxSrcSize);
            uIdx = reinterpret_cast<u32*>(idx);
            mPrimitiveIndexVB.Invalidate();
        }
        else
        {
            // EFT_ASSERT( "[EFT] Primitive Index is Error." );
        }
    }

    void Finalize(Heap* heap)
    {
        mPrimitivePosVB.Finalize(heap);
        mPrimitiveNormalVB.Finalize(heap);
        mPrimitiveColorVB.Finalize(heap);
        mPrimitiveTexCrdVB.Finalize(heap);
        mPrimitiveIndexVB.Finalize(heap);
    }

    void BindPosionBuffer(u32 attr)
    {
        if (attr != EFT_INVALID_ATTRIBUTE && mPrimitivePosVB.GetVertexBuffer())
            mPrimitivePosVB.BindBuffer(attr, mPrimitivePosVB.GetVertexBufferSize(), sizeof(nw::math::VEC3));
    }

    void BindNormalBuffer(u32 attr)
    {
        if (attr != EFT_INVALID_ATTRIBUTE && mPrimitiveNormalVB.GetVertexBuffer())
            mPrimitiveNormalVB.BindBuffer(attr, mPrimitiveNormalVB.GetVertexBufferSize(), sizeof(nw::math::VEC3));
    }

    void BindColorBuffer(u32 attr)
    {
        if (attr != EFT_INVALID_ATTRIBUTE && mPrimitiveColorVB.GetVertexBuffer())
            mPrimitiveColorVB.BindBuffer(attr, mPrimitiveColorVB.GetVertexBufferSize(), sizeof(nw::math::VEC4));
    }

    void BindTextureCrdBuffer(u32 attr)
    {
        if (attr != EFT_INVALID_ATTRIBUTE && mPrimitiveTexCrdVB.GetVertexBuffer())
            mPrimitiveTexCrdVB.BindBuffer(attr, mPrimitiveTexCrdVB.GetVertexBufferSize(), sizeof(nw::math::VEC4));
    }

    void* GetIndexBuffer()
    {
        return mPrimitiveIndexVB.GetVertexBuffer();
    }

    u32 GetIndexNum()
    {
        return mPrimitiveIndexNum;
    }

    bool IsInitialized()
    {
        return mInitialized;
    }

    VertexBuffer& GetPositionVertexBuffer() { return mPrimitivePosVB; }
    VertexBuffer& GetNoramlVertexBuffer()   { return mPrimitiveNormalVB; }
    VertexBuffer& GetColorVertexBuffer()    { return mPrimitiveColorVB; }

private:
    bool                            mInitialized;
    u32                             mPrimitiveIndexNum;

    VertexBuffer                    mPrimitivePosVB;
    VertexBuffer                    mPrimitiveNormalVB;
    VertexBuffer                    mPrimitiveColorVB;
    VertexBuffer                    mPrimitiveTexCrdVB;
    VertexBuffer                    mPrimitiveIndexVB;

    f32* fPos;
    f32* fNor;
    f32* fCol;
    f32* fUv;
    u32* uIdx;
};
static_assert(sizeof(Primitive) == 0x6C, "nw::eft::Primitive size mismatch");

} } // namespace nw::eft

#endif // EFT_PRIMITIVE_H_
