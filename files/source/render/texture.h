#pragma once

#include <agl/aglTextureData.h>
#include <agl/aglTextureSampler.h>

#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>

class Texture
{
public:
    Texture(const sead::SafeString& filePath, u32 texIdx = 0, sead::Heap* heap = nullptr);
    ~Texture();

    bool isInitialized() const
    {
        return mInited;
    }

    agl::TextureData& getTextureInner()
    {
        return mData;
    }

    agl::TextureSampler& getSampler()
    {
        return mSampler;
    }

    void bind();

private:
    bool mInited;
    agl::TextureData mData;
    agl::TextureSampler mSampler;
    u8* mGTX;
};
