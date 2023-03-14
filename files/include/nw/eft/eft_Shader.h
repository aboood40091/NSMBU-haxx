#ifndef EFT_SHADER_H_
#define EFT_SHADER_H_

#include <nw/eft/eft_typeDef.h>
#include <nw/eft/cafe/eft_CafeWrapper.h>
#include <nw/eft/eft_UniformBlock.h>

namespace nw { namespace eft {

// nw::eft::BillboardType
typedef u8 VertexBillboardTypeVariation;

// nw::eft::PtclRotType
typedef u8 VertexRotationVariation;

// nw::eft::StripeType
typedef u8 VertexStripeVariation;

// nw::eft::CombinerType
typedef u8 FragmentCombinerTypeVariation;

// nw::eft::AlphaCombinerType
typedef u8 FragmentAlphaVariation;

enum
{
    EFT_FRAGMENT_SHADER_TYPE_VARIATION_PARTICLE             = 0,
    EFT_FRAGMENT_SHADER_TYPE_VARIATION_REFRACT_PARTICLE     = 1,
    EFT_FRAGMENT_SHADER_TYPE_VARIATION_DISTORTION_PARTICLE  = 2,
    EFT_FRAGMENT_SHADER_TYPE_VARIATION_MAX                  = 3,
};

typedef u8 FragmentShaderVariation;

enum
{
    EFT_FRAGMENT_SHADER_TEXTURE_VARIATION_0 = 0,
    EFT_FRAGMENT_SHADER_TEXTURE_VARIATION_1,
    EFT_FRAGMENT_SHADER_TEXTURE_VARIATION_MAX
};

typedef u8 FragmentTextureVariation;

enum
{
    EFT_FRAGMENT_SHADER_COMPOSITE_MUL = 0,
    EFT_FRAGMENT_SHADER_COMPOSITE_ADD,
    EFT_FRAGMENT_SHADER_COMPOSITE_SUB,
    EFT_FRAGMENT_SHADER_COMPOSITE_MAX,
};

typedef u8 FragmentCompositeVariation;

enum
{
    EFT_FRAGMENT_SHADER_INPUT_OPT_SRC = 0,
    EFT_FRAGMENT_SHADER_INPUT_OPT_ONE,
    EFT_FRAGMENT_SHADER_INPUT_OPT_RED,
    EFT_FRAGMENT_SHADER_INPUT_OPT_MAX,
};

typedef u8 FragmentInputOptVariation;

struct VertexShaderKey
{
    VertexBillboardTypeVariation    mVertexBillboardTypeVariation;
    VertexRotationVariation         mVertexRotationVariation;
    u8                              mUserShaderSetting;
    VertexStripeVariation           mStripeTypeVariation;
    bool                            mStripeEmitterCoord;
    bool                            mUsePrimitive;
    u32                             mUserShaderFlag;
    u32                             mUserShaderSwitchFlag;
    char                            mUserShaderCompileDef[16];

    bool IsStripe() const
    {
        return mVertexBillboardTypeVariation == EFT_BILLBOARD_TYPE_STRIPE ||
               mVertexBillboardTypeVariation == EFT_BILLBOARD_TYPE_COMPLEX_STRIPE;
    }

    bool IsUsePrimitive() const
    {
        return mUsePrimitive;
    }

    void MakeKeyFromSimpleEmitterData(const SimpleEmitterData* res, const char* userDef)
    {
        mVertexBillboardTypeVariation = res->billboardType;
        mVertexRotationVariation      = (res->ptclRotType != EFT_ROT_TYPE_NO_WORK) ? 1 : 0;
        mUserShaderSetting            = res->userShaderSetting;
        mUserShaderFlag               = res->userShaderFlag;
        mUserShaderSwitchFlag         = res->userShaderSwitchFlag;
        mStripeTypeVariation          = EFT_STRIPE_TYPE_BILLBOARD;
      //mStripeEmitterCoord           = false; <-- Nintendo forgot to do this
        mUsePrimitive                 = (res->meshType == EFT_MESH_TYPE_PRIMITIVE) ? true : false;

        if (userDef)
            strcpy(mUserShaderCompileDef, userDef);
        else
            mUserShaderCompileDef[0] = '\0';
    }

    void MakeKeyFromComplexEmitterData(const ComplexEmitterData* res, const char* userDef)
    {
        MakeKeyFromSimpleEmitterData(res, userDef);

        if (res->billboardType == EFT_BILLBOARD_TYPE_STRIPE ||
            res->billboardType == EFT_BILLBOARD_TYPE_COMPLEX_STRIPE)
        {
            const StripeData* stripeRes = reinterpret_cast<const StripeData*>((u32)res + res->stripeDataOffset);

            mStripeTypeVariation = stripeRes->stripeType;
            if (res->stripeFlg & EFT_STRIPE_FLAG_EMITTER_COORD)
                mStripeEmitterCoord = true;
            else
                mStripeEmitterCoord = false;
        }
        else
        {
            mStripeEmitterCoord = false;
        }

        if (userDef)
            strcpy(mUserShaderCompileDef, userDef);
        else
            mUserShaderCompileDef[0] = '\0';
    }

    void MakeKeyFromChildData(const ChildData* res, const char* userDef)
    {
        mVertexBillboardTypeVariation = res->childBillboardType;
        mVertexRotationVariation      = (res->childRotType != EFT_ROT_TYPE_NO_WORK) ? 1 : 0;
        mUserShaderSetting            = res->childUserShaderSetting;
        mUserShaderFlag               = res->childUserShaderFlag;
        mUserShaderSwitchFlag         = res->childUserShaderSwitchFlag;
        mStripeTypeVariation          = EFT_STRIPE_TYPE_MAX;
      //mStripeEmitterCoord           = false; <-- Nintendo forgot to do this
        mUsePrimitive                 = (res->childMeshType == EFT_MESH_TYPE_PRIMITIVE) ? true : false;

        if (userDef)
            strcpy(mUserShaderCompileDef, userDef);
        else
            mUserShaderCompileDef[0] = '\0';
    }

    bool IsEqual(const VertexShaderKey* key) const
    {
        if (mVertexBillboardTypeVariation == key->mVertexBillboardTypeVariation &&
            mVertexRotationVariation      == key->mVertexRotationVariation      &&
            mUserShaderSetting            == key->mUserShaderSetting            &&
            mUserShaderFlag               == key->mUserShaderFlag               &&
            mUserShaderSwitchFlag         == key->mUserShaderSwitchFlag         &&
            mStripeTypeVariation          == key->mStripeTypeVariation          &&
            mStripeEmitterCoord           == key->mStripeEmitterCoord           &&
            mUsePrimitive                 == key->mUsePrimitive                 &&
            strcmp(mUserShaderCompileDef, key->mUserShaderCompileDef) == 0)
        {
            return true;
        }
        return false;
    }

    // TODO
    bool GetCompileSetting(char* compileSetting, u32 compileSettingBufferSize, bool targetCafe);
};
static_assert(sizeof(VertexShaderKey) == 0x20, "nw::eft::VertexShaderKey size mismatch");

struct FragmentShaderKey
{
    FragmentShaderVariation             mShaderVariation;
    u8                                  mUseSoftEdge;
    FragmentTextureVariation            mTextureVariation;
    FragmentCombinerTypeVariation       mColorVariation;
    FragmentAlphaVariation              mAlphaVariation;
    u8                                  mUserShaderSetting;
    bool                                mUsePrimitive;
    FragmentCompositeVariation          mTexture1ColorComposite;
    FragmentCompositeVariation          mTexture1AlphaComposite;
    FragmentCompositeVariation          mPrimitiveColorComposite;
    FragmentCompositeVariation          mPrimitiveAlphaComposite;
    FragmentInputOptVariation           mTexture0ColorOpt;
    FragmentInputOptVariation           mTexture1ColorOpt;
    FragmentInputOptVariation           mPrimitiveColorOpt;
    FragmentInputOptVariation           mTexture0AlphaOpt;
    FragmentInputOptVariation           mTexture1AlphaOpt;
    FragmentInputOptVariation           mPrimitiveAlphaOpt;
    u8                                  mApplyAlpha;
    u16                                 _12;
    u32                                 mUserShaderFlag;
    u32                                 mUserShaderSwitchFlag;
    char                                mUserShaderCompileDef[16];
    u16                                 _2c;
    u8                                  dummy[2];

    bool IsUseSoftEdge() const
    {
        return mUseSoftEdge;
    }

    bool IsUsePrimitive() const
    {
        return mUsePrimitive;
    }

    bool IsApplyAlpha() const
    {
        return mApplyAlpha;
    }

    bool IsEqual(const FragmentShaderKey* key) const
    {
        if (mShaderVariation         == key->mShaderVariation           &&
            mUseSoftEdge             == key->mUseSoftEdge               &&
            mTextureVariation        == key->mTextureVariation          &&
            mColorVariation          == key->mColorVariation            &&
            mAlphaVariation          == key->mAlphaVariation            &&
            mUserShaderSetting       == key->mUserShaderSetting         &&
            mUsePrimitive            == key->mUsePrimitive              &&
            mTexture1ColorComposite  == key->mTexture1ColorComposite    &&
            mTexture1AlphaComposite  == key->mTexture1AlphaComposite    &&
            mPrimitiveColorComposite == key->mPrimitiveColorComposite   &&
            mPrimitiveAlphaComposite == key->mPrimitiveAlphaComposite   &&
            mTexture0ColorOpt        == key->mTexture0ColorOpt          &&
            mTexture1ColorOpt        == key->mTexture1ColorOpt          &&
            mPrimitiveColorOpt       == key->mPrimitiveColorOpt         &&
            mTexture0AlphaOpt        == key->mTexture0AlphaOpt          &&
            mTexture1AlphaOpt        == key->mTexture1AlphaOpt          &&
            mPrimitiveAlphaOpt       == key->mPrimitiveAlphaOpt         &&
            mApplyAlpha              == key->mApplyAlpha                &&
            mUserShaderFlag          == key->mUserShaderFlag            &&
            mUserShaderSwitchFlag    == key->mUserShaderSwitchFlag      &&
            strcmp(mUserShaderCompileDef, key->mUserShaderCompileDef) == 0)
        {
            return true;
        }
        return false;
    }

    void MakeKeyFromSimpleEmitterData(const SimpleEmitterData* res, const char* userDef)
    {
        mShaderVariation          = static_cast<FragmentShaderVariation>(res->shaderType);
        mUseSoftEdge              = res->shaderUseSoftEdge;
        mTextureVariation         = EFT_FRAGMENT_SHADER_TEXTURE_VARIATION_0;
        if (res->texRes[EFT_TEXTURE_SLOT_1].width != 0 && res->texRes[EFT_TEXTURE_SLOT_1].height != 0)
            mTextureVariation     = EFT_FRAGMENT_SHADER_TEXTURE_VARIATION_1;
        mColorVariation           = static_cast<FragmentCombinerTypeVariation>(res->colorCombinerType);
        mAlphaVariation           = static_cast<FragmentAlphaVariation>(res->alphaCombinerType);
        mUserShaderSetting        = res->userShaderSetting;
        mUserShaderFlag           = res->userShaderFlag;
        mUserShaderSwitchFlag     = res->userShaderSwitchFlag;
        mApplyAlpha               = res->shaderApplyAlphaToRefract;
        mUsePrimitive             = (res->meshType == EFT_MESH_TYPE_PRIMITIVE) ? true : false;

        switch (res->texture1ColorBlend)
        {
        case EFT_COLOR_BLEND_TYPE_MOD: mTexture1ColorComposite = EFT_FRAGMENT_SHADER_COMPOSITE_MUL; break;
        case EFT_COLOR_BLEND_TYPE_ADD: mTexture1ColorComposite = EFT_FRAGMENT_SHADER_COMPOSITE_ADD; break;
        case EFT_COLOR_BLEND_TYPE_SUB: mTexture1ColorComposite = EFT_FRAGMENT_SHADER_COMPOSITE_SUB; break;
        }

        switch (res->texture1AlphaBlend)
        {
        case EFT_COLOR_BLEND_TYPE_MOD: mTexture1AlphaComposite = EFT_FRAGMENT_SHADER_COMPOSITE_MUL; break;
        case EFT_COLOR_BLEND_TYPE_ADD: mTexture1AlphaComposite = EFT_FRAGMENT_SHADER_COMPOSITE_ADD; break;
        case EFT_COLOR_BLEND_TYPE_SUB: mTexture1AlphaComposite = EFT_FRAGMENT_SHADER_COMPOSITE_SUB; break;
        }

        switch (res->primitiveColorBlend)
        {
        case EFT_COLOR_BLEND_TYPE_MOD: mPrimitiveColorComposite = EFT_FRAGMENT_SHADER_COMPOSITE_MUL; break;
        case EFT_COLOR_BLEND_TYPE_ADD: mPrimitiveColorComposite = EFT_FRAGMENT_SHADER_COMPOSITE_ADD; break;
        case EFT_COLOR_BLEND_TYPE_SUB: mPrimitiveColorComposite = EFT_FRAGMENT_SHADER_COMPOSITE_SUB; break;
        }

        switch (res->primitiveAlphaBlend)
        {
        case EFT_COLOR_BLEND_TYPE_MOD: mPrimitiveAlphaComposite = EFT_FRAGMENT_SHADER_COMPOSITE_MUL; break;
        case EFT_COLOR_BLEND_TYPE_ADD: mPrimitiveAlphaComposite = EFT_FRAGMENT_SHADER_COMPOSITE_ADD; break;
        case EFT_COLOR_BLEND_TYPE_SUB: mPrimitiveAlphaComposite = EFT_FRAGMENT_SHADER_COMPOSITE_SUB; break;
        }

        if (res->flg & EFT_EMITTER_FLAG_TEXTURE0_COLOR_ONE)    { mTexture0ColorOpt  = EFT_FRAGMENT_SHADER_INPUT_OPT_ONE; }
        else                                                   { mTexture0ColorOpt  = EFT_FRAGMENT_SHADER_INPUT_OPT_SRC; }
        if (res->flg & EFT_EMITTER_FLAG_TEXTURE1_COLOR_ONE)    { mTexture1ColorOpt  = EFT_FRAGMENT_SHADER_INPUT_OPT_ONE; }
        else                                                   { mTexture1ColorOpt  = EFT_FRAGMENT_SHADER_INPUT_OPT_SRC; }
        if (res->flg & EFT_EMITTER_FLAG_PRIMITIVE_COLOR_ONE)   { mPrimitiveColorOpt = EFT_FRAGMENT_SHADER_INPUT_OPT_ONE; }
        else                                                   { mPrimitiveColorOpt = EFT_FRAGMENT_SHADER_INPUT_OPT_SRC; }
        if (res->flg & EFT_EMITTER_FLAG_TEXTURE0_ALPHA_ONE)    { mTexture0AlphaOpt  = EFT_FRAGMENT_SHADER_INPUT_OPT_ONE; }
        else                                                   { mTexture0AlphaOpt  = EFT_FRAGMENT_SHADER_INPUT_OPT_SRC; }
        if (res->flg & EFT_EMITTER_FLAG_TEXTURE1_ALPHA_ONE)    { mTexture1AlphaOpt  = EFT_FRAGMENT_SHADER_INPUT_OPT_ONE; }
        else                                                   { mTexture1AlphaOpt  = EFT_FRAGMENT_SHADER_INPUT_OPT_SRC; }
        if (res->flg & EFT_EMITTER_FLAG_PRIMITIVE_ALPHA_ONE)   { mPrimitiveAlphaOpt = EFT_FRAGMENT_SHADER_INPUT_OPT_ONE; }
        else                                                   { mPrimitiveAlphaOpt = EFT_FRAGMENT_SHADER_INPUT_OPT_SRC; }

        if (userDef)
            strcpy(mUserShaderCompileDef, userDef);
        else
            mUserShaderCompileDef[0] = '\0';

        _12 = 0;
        _2c = 0;
    }

    void MakeKeyFromChildData(const ChildData* res, const char* userDef, u32 childFlag)
    {
        mShaderVariation          = (FragmentShaderVariation)res->childShaderType;
        mUseSoftEdge              = res->childShaderUseSoftEdge;
        mTextureVariation         = EFT_FRAGMENT_SHADER_TEXTURE_VARIATION_0;
        mColorVariation           = (FragmentCombinerTypeVariation)res->childCombinerType;
        mAlphaVariation           = (FragmentAlphaVariation)res->childAlphaCombinerType;
        mUserShaderSetting        = res->childUserShaderSetting;
        mUserShaderFlag           = res->childUserShaderFlag;
        mUserShaderSwitchFlag     = res->childUserShaderSwitchFlag;
        mApplyAlpha               = res->childShaderApplyAlphaToRefract;
        mUsePrimitive             = (res->childMeshType == EFT_MESH_TYPE_PRIMITIVE) ? true : false;

        mTexture1ColorComposite   = EFT_FRAGMENT_SHADER_COMPOSITE_MUL;
        mTexture1AlphaComposite   = EFT_FRAGMENT_SHADER_COMPOSITE_MUL;

        switch (res->primitiveColorBlend)
        {
        case EFT_COLOR_BLEND_TYPE_MOD: mPrimitiveColorComposite = EFT_FRAGMENT_SHADER_COMPOSITE_MUL; break;
        case EFT_COLOR_BLEND_TYPE_ADD: mPrimitiveColorComposite = EFT_FRAGMENT_SHADER_COMPOSITE_ADD; break;
        case EFT_COLOR_BLEND_TYPE_SUB: mPrimitiveColorComposite = EFT_FRAGMENT_SHADER_COMPOSITE_SUB; break;
        }

        switch (res->primitiveAlphaBlend)
        {
        case EFT_COLOR_BLEND_TYPE_MOD: mPrimitiveAlphaComposite = EFT_FRAGMENT_SHADER_COMPOSITE_MUL; break;
        case EFT_COLOR_BLEND_TYPE_ADD: mPrimitiveAlphaComposite = EFT_FRAGMENT_SHADER_COMPOSITE_ADD; break;
        case EFT_COLOR_BLEND_TYPE_SUB: mPrimitiveAlphaComposite = EFT_FRAGMENT_SHADER_COMPOSITE_SUB; break;
        }

        if (childFlag & EFT_CHILD_FLAG_TEXTURE_COLOR_ONE)      { mTexture0ColorOpt  = EFT_FRAGMENT_SHADER_INPUT_OPT_ONE; }
        else                                                   { mTexture0ColorOpt  = EFT_FRAGMENT_SHADER_INPUT_OPT_SRC; }
        mTexture1ColorOpt  = EFT_FRAGMENT_SHADER_INPUT_OPT_SRC;
        if (childFlag & EFT_CHILD_FLAG_PRIMITIVE_COLOR_ONE)    { mPrimitiveColorOpt = EFT_FRAGMENT_SHADER_INPUT_OPT_ONE; }
        else                                                   { mPrimitiveColorOpt = EFT_FRAGMENT_SHADER_INPUT_OPT_SRC; }
        if (childFlag & EFT_CHILD_FLAG_TEXTURE_ALPHA_ONE)      { mTexture0AlphaOpt  = EFT_FRAGMENT_SHADER_INPUT_OPT_ONE; }
        else                                                   { mTexture0AlphaOpt  = EFT_FRAGMENT_SHADER_INPUT_OPT_SRC; }
        mTexture1AlphaOpt  = EFT_FRAGMENT_SHADER_INPUT_OPT_SRC;
        if (childFlag & EFT_CHILD_FLAG_PRIMITIVE_ALPHA_ONE)    { mPrimitiveAlphaOpt = EFT_FRAGMENT_SHADER_INPUT_OPT_ONE; }
        else                                                   { mPrimitiveAlphaOpt = EFT_FRAGMENT_SHADER_INPUT_OPT_SRC; }

        if (userDef)
            strcpy(mUserShaderCompileDef, userDef);
        else
            mUserShaderCompileDef[0] = '\0';

        _12 = 0;
        _2c = 0;
    }

    // TODO
    bool GetCompileSetting(char* compileSetting, u32 compileSettingBufferSize, bool targetCafe);
};
static_assert(sizeof(FragmentShaderKey) == 0x30, "nw::eft::FragmentShaderKey size mismatch");

struct GeometryShaderKey
{
    u8       mStripeType;
    u8       mDummy[3];
};
static_assert(sizeof(GeometryShaderKey) == 4, "nw::eft::GeometryShaderKey size mismatch");

struct ShaderImageInformation
{
    u32                 shaderNum;
    u32                 totalSize;
    u32                 offsetShaderSrcInfo;
    u32                 offsetShaderBinInfo;
};
static_assert(sizeof(ShaderImageInformation) == 0x10, "nw::eft::ShaderImageInformation size mismatch");

struct ShaderSrcInformation
{
    u32                 shaderSourceNum;
    u32                 shaderSourceTotalSize;

    struct sourceCodeTable
    {
        u32                 size;
        u32                 offset;
    };
    static_assert(sizeof(sourceCodeTable) == 8, "nw::eft::ShaderSrcInformation::sourceCodeTable size mismatch");

    sourceCodeTable vshParticle;
    sourceCodeTable fshParticle;
    sourceCodeTable vshStripe;
    sourceCodeTable gshStripe;
    sourceCodeTable vshUser;
    sourceCodeTable fshUser;
    sourceCodeTable vshParticleDeclaration;
    sourceCodeTable fshParticleDeclaration;
};
static_assert(sizeof(ShaderSrcInformation) == 0x48, "nw::eft::ShaderSrcInformation size mismatch");

struct ShaderInformation
{
    VertexShaderKey     vertexShaderKey;
    FragmentShaderKey   fragmentShaderKey;
    GeometryShaderKey   geometryShaderKey;
    u32                 shaderSize;
    u32                 offset;
};
static_assert(sizeof(ShaderInformation) == 0x5C, "nw::eft::ShaderInformation size mismatch");

class ParticleShader
{
    friend class Renderer;

private:
    enum
    {
        UNIFORM_BLOCK_VERTEX_VIEW_BLOCK             = 0,
        UNIFORM_BLOCK_VERTEX_EMITTER_STATIC_BLOCK   = 1,
        UNIFORM_BLOCK_VERTEX_EMITTER_DYNAMIC_BLOCK  = 2,
        UNIFORM_BLOCK_VERTEX_STRIPE_BLOCK           = 3,
        UNIFORM_BLOCK_FRAGMENT_EMITTER_STATIC_BLOCK = 4,
        UNIFORM_BLOCK_FRAGMENTVIEW_BLOCK            = 5,
      //UNIFORM_BLOCK_                              = 6,
      //UNIFORM_BLOCK_                              = 7,
        UNIFORM_BLOCK_ID_MAX                        = 8,
    };

public:
    enum UserUniformBlockID
    {
        UNIFORM_BLOCK_USER_VERTEX_ID_0      = UNIFORM_BLOCK_ID_MAX,
        UNIFORM_BLOCK_USER_VERTEX_ID_1      = UNIFORM_BLOCK_ID_MAX + 1,
        UNIFORM_BLOCK_USER_FRAGMENT_ID_0    = UNIFORM_BLOCK_ID_MAX + 2,
        UNIFORM_BLOCK_USER_FRAGMENT_ID_1    = UNIFORM_BLOCK_ID_MAX + 3,
    };

    enum UserSamplerSlot
    {
        USER_SAMPLER_SLOT_0      = 0,
        USER_SAMPLER_SLOT_1      = 1,
        USER_SAMPLER_SLOT_2      = 2,
        USER_SAMPLER_SLOT_3      = 3,
        USER_SAMPLER_SLOT_4      = 4,
        USER_SAMPLER_SLOT_5      = 5,
        USER_SAMPLER_SLOT_6      = 6,
        USER_SAMPLER_SLOT_7      = 7,
        USER_SAMPLER_SLOT_MAX    = 8,
    };

public:
    ParticleShader();

    void Finalize(Heap* heap);

    bool SetupShaderResource(Heap* heap, void* shaderResource, u32 shaderResourceSize);

    void SetVertexShaderKey(VertexShaderKey* key)
    {
        mVertexShaderKey = *key;
    }

    void SetFragmentShaderKey(FragmentShaderKey* key)
    {
        mFragmentShaderKey = *key;
    }

    void SetGeometryShaderKey(GeometryShaderKey* key)
    {
        mGeometryShaderKey = *key;
    }

    const VertexShaderKey& GetVertexShaderKey() const
    {
        return mVertexShaderKey;
    }

    const FragmentShaderKey& GetFragmentShaderKey() const
    {
        return mFragmentShaderKey;
    }

    const GeometryShaderKey& GetGeometryShaderKey() const
    {
        return mGeometryShaderKey;
    }

    bool IsStripe() const
    {
        return mVertexShaderKey.IsStripe();
    }

    FragmentShaderVariation GetShaderVariation() const
    {
        return mFragmentShaderKey.mShaderVariation;
    }

    bool IsFragmentSoftEdgeVariation() const
    {
        return mFragmentShaderKey.IsUseSoftEdge();
    }

    FragmentTextureVariation GetTextureVariation() const
    {
        return mFragmentShaderKey.mTextureVariation;
    }

    FragmentCombinerTypeVariation GetCombinerTyperVariation() const
    {
        return mFragmentShaderKey.mColorVariation;
    }

    FragmentAlphaVariation GetAlphaVariation() const
    {
        return mFragmentShaderKey.mAlphaVariation;
    }

    void InitializeAttribute();
    void InitializeStripeAttribute();
    void InitializeVertexShaderLocation();
    void InitializeStripeVertexShaderLocation();
    void InitializeFragmentShaderLocation();

    void Setup(Heap* heap)
    {
        mShader.SetupShader(heap);
    }

    bool IsInitialized() const
    {
        return mShader.IsInitialized();
    }

    void Bind();

    void EnableInstanced();
    void DisableInstanced();

    Shader* GetShaderInst()
    {
        return &mShader;
    }

    void BindViewUniformBlock(ViewUniformBlock* block)
    {
        mVertexViewUniformBlock.BindUniformBlock(block);
        mFragmentViewUniformBlock.BindUniformBlock(block);
    }

    void BindEmitterStaticUniformBlock(EmitterStaticUniformBlock* block)
    {
        mVertexEmitterStaticUniformBlock.BindUniformBlock(block);
        mFragmentEmitterStaticUniformBlock.BindUniformBlock(block);
    }

    void BindEmitterDynamicUniformBlock(EmitterDynamicUniformBlock* block)
    {
        mVertexEmitterDynamicUniformBlock.BindUniformBlock(block);
    }

    s32 GetPositionAttribute() const { return mPositionAttr; }
    s32 GetNormalAttribute() const { return mNormalAttr; }
    s32 GetColorAttribute() const { return mColorAttr; }
    s32 GetTextureCoordAttribute() const { return mTexCoordAttr0; }
    s32 GetTextureCoordAttribute1() const { return mTexCoordAttr1; }
    s32 GetIndexAttribute() const { return mIndexAttr; }
    s32 GetRotateAttribute() const { return vRotAttr; }
    s32 GetColorAttribute0() const { return mColor0Attr; }
    s32 GetColorAttribute1() const { return mColor1Attr; }
    s32 GetScaleAttribute() const { return mSclAttr; }
    s32 GetTexAnimAttribute() const { return mTexAnimAttr; }
    s32 GetSubTexAnimAttribute() const { return mSubTexAnimAttr; }
    s32 GetWolrdPosAttribute() const { return mWldPosAttr; }
    s32 GetWolrdPosDiffAttribute() const { return mWldPosDfAttr; }
    s32 GetEmitterMatrix0Attribute() const { return mEmtMatAttr0; }
    s32 GetOuterAttribute() const { return mOuterAttr; }
    s32 GetDirAttribute() const { return mDirAttr; }

    FragmentTextureLocation GetTextureSamplerLocation(TextureSlot slot) const
    {
        return mFragmentTextureSampler[slot];
    }

    FragmentTextureLocation GetFrameBufferTextureSamplerLocation() const
    {
        return mFragmentTextureSampler[EFT_TEXTURE_SLOT_FRAME_BUFFER];
    }

    FragmentTextureLocation GetDepthTextureSamplerLocation() const
    {
        return mFragmentTextureSampler[EFT_TEXTURE_SLOT_DEPTH_BUFFER];
    }

    bool SetUserVertexUniformBlock(UserUniformBlockID uniformBlockID, const char* name, void* param);
    bool SetUserFragmentUniformBlock(UserUniformBlockID uniformBlockID, const char* name, void* param);

    FragmentTextureLocation GetUserFragmentSamplerLocation(UserSamplerSlot userSamplerSlot, const char* name);
    VertexTextureLocation GetUserVertexSamplerLocation(UserSamplerSlot userSamplerSlot, const char* name);

private:
    enum {  DISPLAY_LSIT_SIZE = 512 };
    u8  mDisplayListBuffer[DISPLAY_LSIT_SIZE];
    u32 mDisplayListBufferUsed;

    Shader                  mShader;
    VertexShaderKey         mVertexShaderKey;
    FragmentShaderKey       mFragmentShaderKey;
    GeometryShaderKey       mGeometryShaderKey;
    s32                     mPositionAttr;
    s32                     mNormalAttr;
    s32                     mColorAttr;
    s32                     mTexCoordAttr0;
    s32                     mTexCoordAttr1;
    s32                     mIndexAttr;
    s32                     mOuterAttr;
    s32                     mDirAttr;

    FragmentTextureLocation mFragmentTextureSampler[EFT_TEXTURE_SLOT_MAX];

    s32                     mSclAttr;
    s32                     mTexAnimAttr;
    s32                     mSubTexAnimAttr;
    s32                     mWldPosAttr;
    s32                     mWldPosDfAttr;
    s32                     mColor0Attr;
    s32                     mColor1Attr;
    s32                     vRotAttr;
    s32                     mEmtMatAttr0;
    s32                     mEmtMatAttr1;
    s32                     mEmtMatAttr2;

    UniformBlock            mVertexViewUniformBlock;
    UniformBlock            mFragmentViewUniformBlock;
    UniformBlock            mVertexEmitterStaticUniformBlock;
    UniformBlock            mVertexEmitterDynamicUniformBlock;
    UniformBlock            _56c;
    UniformBlock            mFragmentEmitterStaticUniformBlock;
    UniformBlock            mStripeUniformBlock;

    UniformBlock            mUserVertexUniformBlock[2];
    UniformBlock            mUserFragmentUniformBlock[2];
    VertexTextureLocation   mUserVertexSamplerLocation[USER_SAMPLER_SLOT_MAX];
    FragmentTextureLocation mUserFragmentSamplerLocation[USER_SAMPLER_SLOT_MAX];
};
static_assert(sizeof(ParticleShader) == 0x61C, "nw::eft::ParticleShader size mismatch");

} } // namespace nw::eft

#endif // EFT_SHADER_H_
