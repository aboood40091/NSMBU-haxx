#include "texture.h"

#include <agl/aglTextureDataInitializer.h>
#include <filedevice/seadFileDeviceMgr.h>

Texture::Texture(const sead::SafeString& filePath, u32 texIdx, sead::Heap* heap)
    : mInited(false)
    , mGTX(nullptr)
{
    {
        sead::FileHandle handle;
        if (!sead::FileDeviceMgr::instance()->tryOpen(&handle, filePath,
                                                      sead::FileDevice::cFileOpenFlag_ReadOnly, 0))
            return;

        u32 fileSize = handle.getFileSize();
        if (fileSize == 0)
            return;

        mGTX = new(heap, 0x2000) u8[fileSize];
        if (!mGTX)
            return;

        if (handle.read(mGTX, fileSize) != fileSize)
        {
            delete[] mGTX;
            mGTX = nullptr;

            return;
        }
    }

    agl::TextureDataInitializerGTX::initialize(&mData, mGTX, texIdx);
    mData.invalidateGPUCache();
    mSampler.applyTextureData(mData);

    mInited = true;
}

Texture::~Texture()
{
    if (!mInited)
        return;

    delete[] mGTX;
    mGTX = nullptr;

    mInited = false;
}
