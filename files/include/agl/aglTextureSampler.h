#pragma once

#include <agl/aglTextureData.h>

#include <gfx/seadColor.h>
#include <prim/seadBitFlag.h>

namespace agl {

class SamplerLocation;

class TextureSampler
{
public:
    TextureSampler();
    TextureSampler(const TextureData& textureData);

    virtual ~TextureSampler();

    bool activate(const SamplerLocation& samplerLoc, s32 = -1) const;
    void applyTextureData_(const TextureData& data);

    void applyTextureData(const TextureData& data)
    {
        if (!this->isTexValid ||
                this->textureData.surface.dimension != data.surface.dimension ||
                this->textureData.surface.width     != data.surface.width ||
                this->textureData.surface.height    != data.surface.height ||
                this->textureData.surface.depth     != data.surface.depth ||
                this->textureData.surface.num_mips  != data.surface.num_mips ||
                this->textureData.surface.format    != data.surface.format ||
                this->textureData.surface.swizzle   != data.surface.swizzle ||
                this->textureData.surface.tile      != data.surface.tile ||
                this->textureData.surface.aa        != data.surface.aa)
        {
            applyTextureData_(data);
        }
        else
        {
            this->textureData.surface.image_data = data.surface.image_data;
            this->textureData.surface.mip_data   = data.surface.mip_data;

            this->gx2Texture.surface.image_data = this->textureData.surface.image_data;
            this->gx2Texture.surface.mip_data   = this->textureData.surface.mip_data;
        }
    }

    TextureData textureData;
    u32 magFilter;
    u32 minFilter;
    u32 mipFilter;
    u32 wrapX;
    u32 wrapY;
    u32 wrapZ;
    sead::Color4f borderColor;
    f32 minLOD;
    f32 maxLOD;
    f32 LODBias;
    u32 maxAnisoRatio;
    bool overrideCompSel;
    TextureCompSel rComp;
    TextureCompSel gComp;
    TextureCompSel bComp;
    TextureCompSel aComp;
    bool isTexValid;
    u8 _E9;
    u8 _EA;
    u32 depthCompare;
    GX2Sampler gx2Sampler;
    GX2Texture gx2Texture;
    bool hasBorder;
    sead::BitFlag8 flags;
};
static_assert(sizeof(TextureSampler) == 0x1A0, "agl::TextureSampler size mismatch");

}
