#ifndef EFT_CAFE_WRAPPER_H_
#define EFT_CAFE_WRAPPER_H_

#include <nw/eft/eft_Data.h>
#include <nw/eft/eft_Heap.h>

BOOL _DEMOGFDReadVertexShader(nw::eft::Heap* heap, GX2VertexShader** ppShader, u32 index, const void* pData);
BOOL _DEMOGFDReadPixelShader(nw::eft::Heap* heap, GX2PixelShader** ppShader, u32 index, const void* pData);
BOOL _DEMOGFDReadGeometryShader(nw::eft::Heap* heap, GX2GeometryShader** ppShader, u32 index, const void* pData);

namespace nw { namespace eft {

class Draw
{
public:
    typedef u32 PrimitiveType;

    enum
    {
        PRIM_TYPE_TRIANGLES                 = GX2_PRIMITIVE_TRIANGLES,
        PRIM_TYPE_TRIANGLE_STRIP            = GX2_PRIMITIVE_TRIANGLE_STRIP,
        PRIM_TYPE_QUADS                     = GX2_PRIMITIVE_QUADS,
    };

    static void DrawPrimitive(PrimitiveType primType, u32 vertexNum)
    {
        GX2Draw(static_cast<GX2PrimitiveType>(primType), vertexNum);
    }

    static void DrawInstanceIndexedPrimitive(PrimitiveType primType, u32 vertexNum, void* indexPtr, u32 primCount)
    {
        GX2DrawIndexedEx(static_cast<GX2PrimitiveType>(primType), vertexNum, GX2_INDEX_FORMAT_U32, indexPtr, 0, primCount);
    }

    static void DrawPrimitive(PrimitiveType primType, u32 startNum, u32 vertexNum)
    {
        GX2DrawEx(static_cast<GX2PrimitiveType>(primType), vertexNum, startNum, 1);
    }

    static void DrawInstancePrimitive(PrimitiveType primType, u32 vertexNum, u32 primCount)
    {
        GX2DrawEx(static_cast<GX2PrimitiveType>(primType), vertexNum, 0, primCount);
    }
};

class TextureSampler
{
public:
    TextureSampler();
    ~TextureSampler();

    bool Setup(TextureFilterMode textureFilter, TextureWrapMode wrapModeU, TextureWrapMode wrapModeV);
    bool SetupLOD(f32 maxMip, f32 bais);

    const GX2Sampler* GetSampler() const
    {
        return &mTextureSampler;
    }

private:
    GX2Sampler  mTextureSampler;
};
static_assert(sizeof(TextureSampler) == 0xC, "nw::eft::TextureSampler size mismatch");

typedef const GX2Texture* Texture;
typedef const GX2Sampler* Sampler;

class Rendercontext
{
public:
    Rendercontext();

    void SetupCommonState();
    void SetupBlendType(BlendType blendType);
    void SetupZBufATest(ZBufATestType zBufATestType);
    void SetupDisplaySideType(DisplaySideType displaySideType) const;
    void SetupTexture(const TextureRes* texture, TextureSlot slot, FragmentTextureLocation location);
    void SetupTexture(const Texture texture, TextureSlot slot, FragmentTextureLocation location);

    const TextureSampler* GetDefautSampler() const { return &mDefaultTextureSampler; }

private:
    TextureSampler  mTextureSampler;
    TextureSampler  mDefaultTextureSampler;

    BlendType mBlendType;
    ZBufATestType mZBufATestType;
};
static_assert(sizeof(Rendercontext) == 0x20, "nw::eft::Rendercontext size mismatch");

class VertexBuffer
{
public:
    VertexBuffer();

    void* AllocateVertexBuffer(Heap* heap, u32 size, u32 element);
    void Finalize(Heap* heap);
    void Invalidate();
    void BindBuffer(u32 index, u32 size, u32 stride);

    static void BindExtBuffer(u32 index, u32 size, u32 element, u32 stride, void* buffer);

    void* GetVertexBuffer()
    {
        return mVertexBuffer;
    }

    u32 GetVertexBufferSize()
    {
        return mVertexBufferSize;
    }

private:
    Heap*   mHeap;
    u32     mVertexElement;
    u32     mVertexBufferSize;
    void*   mVertexBuffer;
};
static_assert(sizeof(VertexBuffer) == 0x10, "nw::eft::VertexBuffer size mismatch");

class Shader
{
public:
    enum
    {
        cAttributeMax = 16
    };

    enum VertexFormat
    {
        FORMAT_32_UINT              = GX2_ATTRIB_FORMAT_32_UINT,
        FORMAT_32_32_32_FLOAT       = GX2_ATTRIB_FORMAT_32_32_32_FLOAT,
        FORMAT_32_32_32_32_FLOAT    = GX2_ATTRIB_FORMAT_32_32_32_32_FLOAT,
    };

public:
    Shader();

    bool IsInitialized() const
    {
        return mInitialized;
    }

    void Finalize(Heap* heap);
    void BindShader();
    bool CreateShader(Heap* heap, const void* gshBuffer, u32 gshBufferSize);
    u32 GetFragmentSamplerLocation(const char* name);
    u32 GetAttributeLocation(const char* name);
    u32 GetAttribute(const char* name, u32 index, VertexFormat fmt, u32 offset = 0, bool instancingAttr = false);
    void SetupShader(Heap* heap);

    const GX2VertexShader* GetVertexShader()
    {
        return mpVertexShader;
    }

    const GX2PixelShader* GetPixelShader()
    {
        return mpPixelShader;
    }

    const GX2GeometryShader* GetGeometryShader()
    {
        return mpGeometryShader;
    }

private:
    GX2VertexShader*    mpVertexShader;
    GX2PixelShader*     mpPixelShader;
    GX2GeometryShader*  mpGeometryShader;
    GX2FetchShader      mFetchShader;
    void*               mpFetchShaderBuf;
    u32                 mAttribsNum;
    GX2AttribStream     mAttribs[cAttributeMax];
    u32                 mAttribsIndex[cAttributeMax];
    bool                mInitialized;
};
static_assert(sizeof(Shader) == 0x278, "nw::eft::Shader size mismatch");

class UniformBlock
{
public:
    enum
    {
        EFT_UNIFORM_BLOCK_MODE_VERTEX   = 0,
        EFT_UNIFORM_BLOCK_MODE_FRAGMENT = 1,
        EFT_UNIFORM_BLOCK_MODE_GEOMETRY = 2,
        EFT_UNIFORM_BLOCK_MODE_MAX
    };

public:
    UniformBlock()
    {
        mInitialized        = false;
        mIsFailed           = false;
        mBufferSize	        = 0;
        mUniformLoc	        = 0;
        mUniformBlockMode   = EFT_UNIFORM_BLOCK_MODE_MAX;
    }

    bool InitializeVertexUniformBlock(Shader* shader, const char* name, u32 bindPoint);
    bool InitializePixelUniformBlock(Shader* shader, const char* name, u32 bindPoint);
    void BindUniformBlock(const void* param);

    bool IsInitialized() const
    {
        return mInitialized;
    }

    bool IsFailed() const
    {
        return mIsFailed;
    }

private:
    bool    mInitialized;
    bool    mIsFailed;
	u32		mBufferSize;
	u32		mUniformLoc;
	u32	    mUniformBlockMode;
};
static_assert(sizeof(UniformBlock) == 0x10, "nw::eft::UniformBlock size mismatch");

} } // namespace nw::eft

#endif // EFT_CAFE_WRAPPER_H_
