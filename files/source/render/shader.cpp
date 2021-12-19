#include "shader.h"

#include <cafe/gfd.h>
#include <filedevice/seadFileDeviceMgr.h>

Shader::Shader(const sead::SafeString& filePath, u32 vtxIdx, u32 frgIdx, sead::Heap* heap)
    : mInited(false)
    , mVertexShader(nullptr)
    , mPixelShader(nullptr)
    , mGSH(nullptr)
{
    {
        sead::FileHandle handle;
        if (!sead::FileDeviceMgr::instance()->tryOpen(&handle, filePath,
                                                      sead::FileDevice::cFileOpenFlag_ReadOnly, 0))
            return;

        u32 fileSize = handle.getFileSize();
        if (fileSize == 0)
            return;

        mGSH = new(heap, GX2_SHADER_ALIGNMENT) u8[fileSize];
        if (!mGSH)
            return;

        if (handle.read(mGSH, fileSize) != fileSize)
        {
            delete[] mGSH;
            mGSH = nullptr;

            return;
        }
    }

    if (GFDGetVertexShaderCount(mGSH) <= vtxIdx || GFDGetPixelShaderCount(mGSH) <= frgIdx)
    {
        delete[] mGSH;
        mGSH = nullptr;

        return;
    }

    mVertexShader = GFDGetVertexShaderPointer(vtxIdx, mGSH);
    mPixelShader = GFDGetPixelShaderPointer(frgIdx, mGSH);

    if (!mVertexShader || !mPixelShader)
    {
        delete[] mGSH;
        mGSH = nullptr;
        mVertexShader = nullptr;
        mPixelShader = nullptr;

        return;
    }

    GX2Invalidate(GX2_INVALIDATE_CPU_SHADER, mVertexShader->shader_data, mVertexShader->shader_size);
    GX2Invalidate(GX2_INVALIDATE_CPU_SHADER, mPixelShader->shader_data, mPixelShader->shader_size);

    mInited = true;
}

Shader::~Shader()
{
    if (!mInited)
        return;

    delete[] mGSH;
    mGSH = nullptr;
    mVertexShader = nullptr;
    mPixelShader = nullptr;

    mInited = false;
}

void Shader::use() const
{
    if (!mInited)
        return;

    GX2SetVertexShader(mVertexShader);
    GX2SetPixelShader(mPixelShader);
}

void ShaderUR::use() const
{
    if (!mInited)
        return;

    GX2SetShaderModeEx(GX2_SHADER_MODE_UNIFORM_REGISTER, 48, 64, 0, 0, 200, 192);

    GX2SetVertexShader(mVertexShader);
    GX2SetPixelShader(mPixelShader);
}
