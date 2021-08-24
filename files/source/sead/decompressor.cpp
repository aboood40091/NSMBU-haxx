#include <filedevice/seadFileDeviceMgr.h>
#include <heap/seadHeap.h>
#include <heap/seadHeapMgr.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadEndian.h>
#include <resource/seadSZSDecompressor.h>

#include "dynamic_libs/zlib_functions.h"
#include "log.h"

namespace sead {

u8*
SZSDecompressor::tryDecompFromDevice(
    const ResourceMgr::LoadArg& arg, Resource* res,
    u32* out_size, u32* out_buffer_size, bool* out_need_delete
)
{
    Heap* heap = arg.load_data_heap;
    if (heap == NULL)
        heap = HeapMgr::sInstancePtr->getCurrentHeap();

    FileHandle handle;
    FileDevice* device;

    if (arg.device != NULL)
        device = arg.device->tryOpen(&handle, arg.path, FileDevice::cFileOpenFlag_ReadOnly, arg.div_size);
    else
        device = FileDeviceMgr::instance()->tryOpen(&handle, arg.path, FileDevice::cFileOpenFlag_ReadOnly, arg.div_size);

    if (device == NULL)
        return NULL;

    u8* work = mWorkBuffer;
    if (work == NULL)
        work = new(heap, -FileDevice::cBufferMinAlignment) u8[mWorkSize];

    if (work == NULL)
    {
        //SEAD_ASSERT_MSG(false, "cannot alloc work buf");
        return NULL;
    }

    u32 bytesRead = handle.read(work, mWorkSize);
    if (bytesRead < getHeaderSize())
    {
        //SEAD_ASSERT_MSG(false, "Invalid header size.");

        if (mWorkBuffer == NULL)
            delete[] work;

        return NULL;
    }

    u32 decomp_size = getDecompSize(work);
    //SEAD_ASSERT(decomp_size > 0);

    s32 decomp_alignment = getDecompAlignment(work);
    //SEAD_ASSERT_MSG(decomp_alignment == 0 || (decomp_alignment - 1u & decomp_alignment) == 0 "decomp_alignment[%d] must be power of 2.", decomp_alignment);

    if (decomp_size > arg.load_data_buffer_size && arg.load_data_buffer_size != 0)
        decomp_size = arg.load_data_buffer_size;

    u32 buffer_size = Mathi::roundUpPow2(decomp_size, 0x20);

    u8* dst = arg.load_data_buffer;
    bool need_delete = false;

    if (dst == NULL)
    {
        DirectResource* directResource = DynamicCast<DirectResource, Resource>(res);
        s32 alignment = 0;

        if (directResource != NULL)
        {
            if (arg.load_data_alignment != 0)
            {
                alignment = Mathi::max(arg.load_data_alignment, 0x20);
                //SEAD_ASSERT_MSG(decomp_alignment == 0 || alignment % decomp_alignment == 0, "load_data_alignment[%d] doesn\'t meet decomp_alignment[%d].", arg.load_data_alignment, decomp_alignment);
            }
            else
            {
                if (decomp_alignment == 0)
                    alignment = directResource->getLoadDataAlignment();
                else
                    alignment = decomp_alignment;

                alignment = Mathi::sign(arg.instance_alignment) * Mathi::max(alignment, 0x20);
            }
        }
        else
        {
            alignment = -Mathi::sign(arg.instance_alignment) << 5;
        }

        dst = new(heap, alignment) u8[buffer_size];

        if (dst == NULL)
        {
            //SEAD_ASSERT_MSG(false, "cannot alloc dst buf");

            if (mWorkBuffer == NULL)
                delete[] work;

            return NULL;
        }
        else
        {
            need_delete = true;
        }
    }
    else
    {
        //SEAD_ASSERT(arg.load_data_buffer_size >= decomp_size);
        //SEAD_ASSERT_MSG(decomp_alignment == 0 || ((uintptr_t)dst & decomp_alignment - 1u) == 0, "load_data_buffer is not aligned with decomp_alignment[%d]", decomp_alignment);
    }

    if (Endian::toHost(Endian::cBig, *(u32*)work) == 0x5A6C6962) // Zlib
    {
        z_stream strm;

        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        strm.avail_in = 0;
        strm.next_in = Z_NULL;

        s32 ret = inflateInit(&strm);
        if (ret != Z_OK)
        {
            //SEAD_ASSERT_MSG(false, "inflateInit returned error(%d).", ret);

            if (need_delete)
                delete[] dst;

            if (mWorkBuffer == NULL)
                delete[] work;

            return NULL;
        }

        bytesRead -= getHeaderSize();
        u8* in = work + getHeaderSize();

        do
        {
            strm.avail_in = bytesRead;
            strm.next_in = in;

            strm.avail_out = buffer_size - strm.total_out;
            strm.next_out = dst + strm.total_out;
            ret = inflate(&strm, Z_NO_FLUSH);

            if (ret == Z_STREAM_ERROR || ret == Z_NEED_DICT || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR)
                break;

            in = work;
        }
        while (ret != Z_STREAM_END && (bytesRead = handle.read(in, mWorkSize), bytesRead != 0));

        (void)inflateEnd(&strm);

        if (ret != Z_STREAM_END)
        {
            //SEAD_ASSERT_MSG(false, "inflate returned error(%d).", ret);

            if (need_delete)
                delete[] dst;

            if (mWorkBuffer == NULL)
                delete[] work;

            return NULL;
        }
    }
    else if (bytesRead < mWorkSize)
    {
        s32 error = decomp(dst, buffer_size, work, mWorkSize);
        if (error < 0)
        {
            //SEAD_ASSERT_MSG(false, "decompSZS returned error(%d).", error);

            if (need_delete)
                delete[] dst;

            if (mWorkBuffer == NULL)
                delete[] work;

            return NULL;
        }
    }
    else
    {
        DecompContext context(dst);
        context.forceDestCount = decomp_size;

        while (bytesRead > 0)
        {
            s32 error = streamDecomp(&context, work, bytesRead);
            if (error == 0)
                break;

            if (error < 0)
            {
                //SEAD_ASSERT_MSG(false, "streamDecompSZS returned error(%d).", error);

                if (need_delete)
                    delete[] dst;

                if (mWorkBuffer == NULL)
                    delete[] work;

                return NULL;
            }

            bytesRead = handle.read(work, mWorkSize);
        }
    }

    if (mWorkBuffer == NULL)
        delete[] work;

    if (out_size != NULL)
        *out_size = decomp_size;

    if (out_buffer_size != NULL)
        *out_buffer_size = buffer_size;

    if (out_need_delete != NULL)
        *out_need_delete = need_delete;

    return dst;
}

}
