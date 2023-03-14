#ifndef EFT_PARTICLE_H_
#define EFT_PARTICLE_H_

#include <nw/eft/eft_typeDef.h>
#include <nw/eft/eft_Data.h>
#include <nw/eft/eft_Shader.h>

namespace nw { namespace eft {

struct PtclInstance;

enum
{
    cNumStripeHistory     = 256
};

struct PtclStripeHistory
{
    nw::math::VEC3          pos;
    f32                     scale;
    nw::math::MTX34         emitterSRT;
    nw::math::VEC3          outer;
    nw::math::VEC3          dir;
};
static_assert(sizeof(PtclStripeHistory) == 0x58, "nw::eft::PtclStripeHistory size mismatch");

struct PtclStripe
{
    PtclInstance*               ptcl;
    s32                         histQStart;
    s32                         histQEnd;
    PtclStripeHistory           hist[cNumStripeHistory];
    s32                         numHistory;
    u32                         groupID;
    const ComplexEmitterData*   res;
    s32                         cnt;
    nw::math::MTX34             emitterSRT;
    nw::math::VEC3              interpolateNextDir;
    nw::math::VEC3              p0;
    nw::math::VEC3              p1;
    PtclStripe*                 prev;
    PtclStripe*                 next;
    u32                         startDrawVertex;
    u32                         numDrawVertex;
};
static_assert(sizeof(PtclStripe) == 0x5880, "nw::eft::PtclStripe size mismatch");

struct AlphaAnim
{
    f32                 alphaAddSec1;
    f32                 alphaAddSec2;
    s32                 alphaSec1;
    s32                 alphaSec2;
};
static_assert(sizeof(AlphaAnim) == 0x10, "nw::eft::AlphaAnim size mismatch");

struct ScaleAnim
{
    nw::math::VEC2      scaleAddSec1;
    nw::math::VEC2      scaleAddSec2;
    s32                 scaleSec1;
    s32                 scaleSec2;
};
static_assert(sizeof(ScaleAnim) == 0x18, "nw::eft::ScaleAnim size mismatch");

struct EmitterInstance;

struct PtclInstance
{
    f32                  cnt;
    s32                  life;
    nw::math::VEC3       pos;
    nw::math::VEC3       posDiff;
    nw::math::VEC3       vel;
    nw::math::VEC3       worldPos;
    nw::math::VEC3       worldPosDiff;
    nw::math::VEC3       rot;
    nw::math::VEC3       rotVel;
    f32                  dynamicsRnd;
    f32                  alpha;
    AlphaAnim*           alphaAnim;
    nw::math::VEC2       scale;
    ScaleAnim*           scaleAnim;
    f32                  uvRotateZ;
    nw::math::VEC2       uvOffset;
    nw::math::VEC2       uvScroll;
    nw::math::VEC2       uvScale;
    f32                  uvSubRotateZ;
    nw::math::VEC2       uvSubOffset;
    nw::math::VEC2       uvSubScroll;
    nw::math::VEC2       uvSubScale;
    f32                  fluctuationAlpha;
    f32                  fluctuationScale;
    nw::ut::FloatColor   color[EFT_COLOR_KIND_MAX];
    PtclAttributeBuffer* attributeBuffer;
    nw::math::MTX34      emitterRT;
    nw::math::MTX34      emitterSRT;
    nw::math::MTX34*     coordinateEmitterRT;
    nw::math::MTX34*     coordinateEmitterSRT;
    u32                  runtimeUserData;

    const SimpleEmitterData*   res;
    PtclInstance*        prev;
    PtclInstance*        next;
    EmitterInstance*     emitter;
    PtclStripe*          stripe;
    PtclType             type;
    u32                  rnd;

    f32                  childEmitCnt;
    f32                  childPreEmitCnt;
    f32                  childEmitSaving;
    u32                  _16c[0x14 / sizeof(u32)];

    f32 GetParticleCounter() const
    {
        return cnt;
    }

    s32 GetParticleLife() const
    {
        return life;
    }

    nw::math::VEC3& GetPos()
    {
        return pos;
    }

    nw::math::VEC3& GetWorldPos()
    {
        return worldPos;
    }

    nw::math::VEC3& GetVelocity()
    {
        return vel;
    }

    nw::math::VEC3& GetRotation()
    {
        return rot;
    }

    nw::math::VEC3& GetRotateVelocity()
    {
        return rotVel;
    }

    f32 GetAlpha() const
    {
        return alpha;
    }

    void SetAlpha(f32 alphaParam)
    {
        alpha = alphaParam;
    }

    nw::math::VEC2& GetScale()
    {
        return scale;
    }

    u32 GetRuntimeUserData() const
    {
        return runtimeUserData;
    }

    void SetRuntimeUserData(u32 data)
    {
        runtimeUserData = data;
    }

    PtclType GetParticleType()
    {
        return type;
    }

    void GetDrawColor0(nw::ut::FloatColor* dstColor);
    void GetDrawColor1(nw::ut::FloatColor* dstColor);
};
static_assert(sizeof(PtclInstance) == 0x180, "nw::eft::PtclInstance size mismatch");

} } // namespace nw::eft

#endif // EFT_PARTICLE_H_
