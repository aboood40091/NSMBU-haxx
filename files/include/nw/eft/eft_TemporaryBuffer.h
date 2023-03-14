#ifndef EFT_TEMPORARY_BUFFER_H_
#define EFT_TEMPORARY_BUFFER_H_

#include <nw/eft/eft_typeDef.h>
#include <nw/eft/eft_Heap.h>

namespace nw { namespace eft {

struct TemporaryBuffer
{
public:
    enum BufferSide
    {
        EFT_TEMPORARY_BUFFER_FIRST      = 0,
        EFT_TEMPORARY_BUFFER_SECOND     = 1,
        EFT_TEMPORARY_BUFFER_MAX        = 2
    };

    enum
    {
       EFT_DOUBLE_BUFFER_ALIGN      = 0x100
    };

    void Initialize(Heap* heap, u32 size)
    {
        mBufferSide                          = EFT_TEMPORARY_BUFFER_FIRST;
        mBufferSize                          = size;
        mAllocedSize                         = 0;
        mFlushedSize                         = 0;
        mBuffer[EFT_TEMPORARY_BUFFER_FIRST]  = heap->Alloc(mBufferSize, EFT_DOUBLE_BUFFER_ALIGN);
        mBuffer[EFT_TEMPORARY_BUFFER_SECOND] = heap->Alloc(mBufferSize, EFT_DOUBLE_BUFFER_ALIGN);
    }

    void Finalize(Heap* heap)
    {
        heap->Free(mBuffer[EFT_TEMPORARY_BUFFER_FIRST]);
        heap->Free(mBuffer[EFT_TEMPORARY_BUFFER_SECOND]);
    }

    void Swap()
    {
        mBufferSide  = !mBufferSide;
        mAllocedSize = 0;
        mFlushedSize = 0;
    }

    void* Alloc(u32 size)
    {
        if (size == 0)
            return NULL;

        //u32 allocSize = nw::ut::RoundUp(size, EFT_DOUBLE_BUFFER_ALIGN);
        u32 allocSize = (size & ~(EFT_DOUBLE_BUFFER_ALIGN - 1)) + EFT_DOUBLE_BUFFER_ALIGN;
        if (mAllocedSize + allocSize > mBufferSize)
            return NULL;

        u8* ret = static_cast<u8*>(mBuffer[mBufferSide]) + mAllocedSize;
        mAllocedSize += allocSize;

        for (u32 i = 0; i < allocSize >> 8; i++)
        {
            u32 block0 = i * 0x100 + 0x00;
            u32 block1 = i * 0x100 + 0x20;
            u32 block2 = i * 0x100 + 0x40;
            u32 block3 = i * 0x100 + 0x60;
            u32 block4 = i * 0x100 + 0x80;
            u32 block5 = i * 0x100 + 0xA0;
            u32 block6 = i * 0x100 + 0xC0;
            u32 block7 = i * 0x100 + 0xE0;

            EFT_MEMUTIL_CAFE_DCBZ_OFFSET(ret, block0);
            EFT_MEMUTIL_CAFE_DCBZ_OFFSET(ret, block1);
            EFT_MEMUTIL_CAFE_DCBZ_OFFSET(ret, block2);
            EFT_MEMUTIL_CAFE_DCBZ_OFFSET(ret, block3);
            EFT_MEMUTIL_CAFE_DCBZ_OFFSET(ret, block4);
            EFT_MEMUTIL_CAFE_DCBZ_OFFSET(ret, block5);
            EFT_MEMUTIL_CAFE_DCBZ_OFFSET(ret, block6);
            EFT_MEMUTIL_CAFE_DCBZ_OFFSET(ret, block7);
        }

        return ret;
    }

    u32 GetSize() const { return mBufferSize; }
    u32 GetUsedSize() const { return mAllocedSize; }

    void FlushCache()
    {
        if (mFlushedSize != mAllocedSize)
        {
            DCFlushRange(static_cast<u8*>(mBuffer[mBufferSide]) + mFlushedSize, mAllocedSize - mFlushedSize);
            mFlushedSize = mAllocedSize;
        }
    }

private:
    u32     mBufferSide;
    u32     mBufferSize;
    u32     mAllocedSize;
    u32     mFlushedSize;
    void*   mBuffer[EFT_TEMPORARY_BUFFER_MAX];
};
static_assert(sizeof(TemporaryBuffer) == 0x18, "nw::eft::TemporaryBuffer size mismatch");

} } // namespace nw::eft

#endif // EFT_TEMPORARY_BUFFER_H_
