#ifndef EFT_CALLBACK_H_
#define EFT_CALLBACK_H_

#include <nw/eft/eft_Shader.h>

namespace nw  { namespace eft {

struct EmitterInstance;
struct PtclInstance;
class  Renderer;

struct EmitterPreCalcArg
{
    EmitterInstance*    emitter;
};
static_assert(sizeof(EmitterPreCalcArg) == 4, "nw::eft::EmitterPreCalcArg size mismatch");

struct EmitterPostCalcArg
{
    EmitterInstance* emitter;
};
static_assert(sizeof(EmitterPostCalcArg) == 4, "nw::eft::EmitterPostCalcArg size mismatch");

struct EmitterDrawOverrideArg
{
    const EmitterInstance*  emitter;
    Renderer*               renderer;
    bool                    cacheFlush;
    void*                   userParam;
};
static_assert(sizeof(EmitterDrawOverrideArg) == 0x10, "nw::eft::EmitterDrawOverrideArg size mismatch");

struct ParticleEmitArg
{
    PtclInstance*   particle;
};
static_assert(sizeof(ParticleEmitArg) == 4, "nw::eft::ParticleEmitArg size mismatch");

struct ParticleRemoveArg
{
    PtclInstance*   particle;
};
static_assert(sizeof(ParticleRemoveArg) == 4, "nw::eft::ParticleRemoveArg size mismatch");

struct ParticleCalcArg
{
    EmitterInstance*    emitter;
    PtclInstance*       ptcl;
    CpuCore             core;
    bool                skipBehavior;
};
static_assert(sizeof(ParticleCalcArg) == 0x10, "nw::eft::ParticleCalcArg size mismatch");

struct ShaderEmitterPostCalcArg
{
    EmitterInstance* emitter;
    bool             skipBehavior;
    bool             isChild;
};
static_assert(sizeof(ShaderEmitterPostCalcArg) == 8, "nw::eft::ShaderEmitterPostCalcArg size mismatch");

struct ShaderDrawOverrideArg
{
    const EmitterInstance*  emitter;
    Renderer*               renderer;
    bool                    cacheFlush;
    void*                   userParam;
};
static_assert(sizeof(ShaderDrawOverrideArg) == 0x10, "nw::eft::ShaderDrawOverrideArg size mismatch");

struct RenderStateSetArg
{
    const EmitterInstance*  emitter;
    Renderer*               renderer;
    bool                    cacheFlush;
    void*                   userParam;
};
static_assert(sizeof(RenderStateSetArg) == 0x10, "nw::eft::RenderStateSetArg size mismatch");

typedef void (*UserDataEmitterPreCalcCallback)(EmitterPreCalcArg& arg);
typedef void (*UserDataEmitterPostCalcCallback)(EmitterPostCalcArg& arg);
typedef void (*UserDataEmitterDrawOverrideCallback)(EmitterDrawOverrideArg& arg);
typedef bool (*UserDataParticleEmitCallback)(ParticleEmitArg& arg);
typedef bool (*UserDataParticleRemoveCallback)(ParticleRemoveArg& arg);
typedef void (*UserDataParticleCalcCallback)(ParticleCalcArg& arg);
typedef void (*UserDataParticleMakeAttributeCallback)(const ParticleCalcArg& arg);
typedef void (*UserShaderEmitterPostCalcCallback)(ShaderEmitterPostCalcArg& arg);
typedef void (*UserShaderDrawOverrideCallback)(ShaderDrawOverrideArg& arg);
typedef void (*UserShaderRenderStateSetCallback)(RenderStateSetArg& arg);

} } // namespace nw::eft

#endif // EFT_CALLBACK_H_
