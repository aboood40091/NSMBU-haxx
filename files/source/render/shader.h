#pragma once

#include <cafe.h>

#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>
#include <util/mtx.h>

class Shader
{
public:
    Shader(const sead::SafeString& filePath, u32 vtxIdx = 0, u32 frgIdx = 0, sead::Heap* heap = nullptr);
    virtual ~Shader();

    bool isInitialized() const
    {
        return mInited;
    }

    virtual void use() const;

protected:
    bool mInited;
    GX2VertexShader* mVertexShader;
    GX2PixelShader* mPixelShader;
    u8* mGSH;
};

// Shader class enforcing uniform register mode
class ShaderUR : public Shader
{
public:
    ShaderUR(const sead::SafeString& filePath, u32 vtxIdx = 0, u32 frgIdx = 0, sead::Heap* heap = nullptr)
        : Shader(filePath, vtxIdx, frgIdx, heap)
    {
    }

    virtual void use() const;

    void setBool(const sead::SafeString& name, bool value) const
    {
        setInt(name, (s32)value);
    }

    void setInt(const sead::SafeString& name, s32 value) const
    {
        const char* c_name = name.cstr();

        s32 vtxOffs = GX2GetVertexUniformVarOffset(mVertexShader, c_name);
        if (vtxOffs != -1)
            GX2SetVertexUniformReg(vtxOffs, 1, &value);

        s32 frgOffs = GX2GetPixelUniformVarOffset(mPixelShader, c_name);
        if (frgOffs != -1)
            GX2SetPixelUniformReg(frgOffs, 1, &value);
    }

    void setFloat(const sead::SafeString& name, f32 value) const
    {
        const char* c_name = name.cstr();

        s32 vtxOffs = GX2GetVertexUniformVarOffset(mVertexShader, c_name);
        if (vtxOffs != -1)
            GX2SetVertexUniformReg(vtxOffs, 1, &value);

        s32 frgOffs = GX2GetPixelUniformVarOffset(mPixelShader, c_name);
        if (frgOffs != -1)
            GX2SetPixelUniformReg(frgOffs, 1, &value);
    }

    void setMat4(const sead::SafeString& name, const Mtx34& mat)
    {
        const char* c_name = name.cstr();

        // GLSL shader needs matrix in column-major layout
        f32 mtx_t[16] = {
            mat.m[0][0], mat.m[1][0], mat.m[2][0], 0.0f,
            mat.m[0][1], mat.m[1][1], mat.m[2][1], 0.0f,
            mat.m[0][2], mat.m[1][2], mat.m[2][2], 0.0f,
            mat.m[0][3], mat.m[1][3], mat.m[2][3], 1.0f
        };

        s32 vtxOffs = GX2GetVertexUniformVarOffset(mVertexShader, c_name);
        if (vtxOffs != -1)
            GX2SetVertexUniformReg(vtxOffs, 16, mtx_t);

        s32 frgOffs = GX2GetPixelUniformVarOffset(mPixelShader, c_name);
        if (frgOffs != -1)
            GX2SetPixelUniformReg(frgOffs, 16, mtx_t);
    }

    void setMat4(const sead::SafeString& name, const Mtx44& mat)
    {
        const char* c_name = name.cstr();

        // GLSL shader needs matrix in column-major layout
        f32 mtx_t[16] = {
            mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[3][0],
            mat.m[0][1], mat.m[1][1], mat.m[2][1], mat.m[3][1],
            mat.m[0][2], mat.m[1][2], mat.m[2][2], mat.m[3][2],
            mat.m[0][3], mat.m[1][3], mat.m[2][3], mat.m[3][3]
        };

        s32 vtxOffs = GX2GetVertexUniformVarOffset(mVertexShader, c_name);
        if (vtxOffs != -1)
            GX2SetVertexUniformReg(vtxOffs, 16, mtx_t);

        s32 frgOffs = GX2GetPixelUniformVarOffset(mPixelShader, c_name);
        if (frgOffs != -1)
            GX2SetPixelUniformReg(frgOffs, 16, mtx_t);
    }
};
