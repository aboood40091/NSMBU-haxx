#ifndef EFT_EMITTER_H_
#define EFT_EMITTER_H_

#include <nw/eft/eft_typeDef.h>
#include <nw/eft/eft_Data.h>
#include <nw/eft/eft_Random.h>
#include <nw/eft/eft_AnimKeyFrame.h>
#include <nw/eft/eft_Primitive.h>
#include <nw/eft/eft_Shader.h>
#include <nw/eft/eft_Particle.h>

namespace nw { namespace eft {

class  EmitterCalc;
class  EmitterController;
struct EmitterDynamicUniformBlock;
class  EmitterSet;
struct EmitterStaticUniformBlock;
struct PtclAttributeBuffer;
class  StripeVertexBuffer;

struct EmitterInstance
{
    f32                                         cnt;
    f32                                         preCnt;
    f32                                         emitCnt;
    f32                                         preEmitCnt;
    f32                                         emitSaving;
    s32                                         ptclNum;
    s32                                         childPtclNum;
    s32                                         groupID;
    EmitterSet*                                 emitterSet;
    EmitterController*                          controller;
    u32                                         emitterSetCreateID;
    nw::math::MTX34                             emitterRT;
    nw::math::MTX34                             emitterSRT;
    PtclRandom                                  rnd;
    s32                                         emissionInterval;
    f32                                         fadeAlpha;
    f32                                         frameRate;
    nw::math::VEC3                              emitDistPrevPos;
    bool                                        emitDistPrevPosSet;
    f32                                         emitDistVessel;
    nw::math::VEC3                              scaleRnd;
    nw::math::VEC3                              rotatRnd;
    nw::math::VEC3                              transRnd;
    PtclFollowType                              followType;
    EmitterInstance*                            prev;
    EmitterInstance*                            next;
    EmitterCalc*                                calc;
    const SimpleEmitterData*                    res;
    PtclInstance*                               ptclHead;
    PtclInstance*                               childHead;
    PtclInstance*                               ptclTail;
    PtclInstance*                               childTail;
    ParticleShader*                             shader[EFT_SHADER_TYPE_MAX];
    ParticleShader*                             childShader[EFT_SHADER_TYPE_MAX];
    Primitive*                                  primitive;
    Primitive*                                  childPrimitive;
    KeyFrameAnimArray*                          emitterAnimArray;
    f32                                         emitAnimValue[EFT_ANIM_MAX];
    nw::math::MTX34                             animEmitterRT;
    nw::math::MTX34                             animEmitterSRT;
    f32                                         emitVessel;
    bool                                        isEmitted;
    bool                                        isCalculated;
    bool                                        stopDraw;
    u32                                         behaviorFlag;
    u32                                         shaderArrtFlag;
    u32                                         childShaderArrtFlag;

    mutable u32                                 entryNum;
    mutable u32                                 childEntryNum;
    mutable u32                                 stripeVertexNum;

    PtclAttributeBuffer*                        ptclAttributeBuffer;
    PtclAttributeBuffer*                        childPtclAttributeBuffer;
    StripeVertexBuffer*                         stripeBuffer;
    EmitterStaticUniformBlock*                  emitterStaticUniformBlock;
    EmitterStaticUniformBlock*                  childEmitterStaticUniformBlock;
    EmitterDynamicUniformBlock*                 emitterDynamicUniformBlock;
    EmitterDynamicUniformBlock*                 childEmitterDynamicUniformBlock;

    void Init(const SimpleEmitterData* resource);
    void UpdateResInfo();

    void TransformWorldVec(nw::math::VEC3* pDst, nw::math::VEC3* pSrc, PtclInstance* pPtcl);
    void TransformWorldVecNormal(nw::math::VEC3* pDst, nw::math::VEC3* pSrc, PtclInstance* pPtcl);
    void TransformLocalVec(nw::math::VEC3* pDst, nw::math::VEC3* pSrc, PtclInstance* pPtcl);
    void TransformLocalVecNormal(nw::math::VEC3* pDst, nw::math::VEC3* pSrc, PtclInstance* pPtcl);

    EmitterType GetEmitterType() const
    {
        return res->type;
    }

    BillboardType GetBillboardType() const
    {
        return res->billboardType;
    }

    const SimpleEmitterData* GetSimpleEmitterData() const
    {
        return res;
    }

    u32 GetDrawPathFlag() const
    {
        return res->drawPath;
    }

    const char* GetEmitterName() const
    {
        return res->name;
    }

    BlendType GetBlendType() const
    {
        return res->blendType;
    }

    const EmitterSet* GetEmitterSet() const
    {
        return emitterSet;
    }

    const ComplexEmitterData* GetComplexEmitterData() const
    {
        if (res->type != EFT_EMITTER_TYPE_COMPLEX)
            return NULL;

        return reinterpret_cast<const ComplexEmitterData*>(res);
    }

    const ChildData* GetChildData() const
    {
        if (res->type == EFT_EMITTER_TYPE_SIMPLE)
            return NULL;

        const ComplexEmitterData* cres = reinterpret_cast<const ComplexEmitterData*>(res);

        if (cres->childFlg & EFT_CHILD_FLAG_ENABLE)
            return reinterpret_cast<const ChildData*>(cres + 1);
        else
            return NULL;
    }

    const StripeData* GetStripeData() const
    {
        if (res->type == EFT_EMITTER_TYPE_SIMPLE)
            return NULL;

        const ComplexEmitterData* cres = reinterpret_cast<const ComplexEmitterData*>(res);

        if (cres->billboardType == EFT_BILLBOARD_TYPE_STRIPE ||
            cres->billboardType == EFT_BILLBOARD_TYPE_COMPLEX_STRIPE)
        {
            return reinterpret_cast<const StripeData*>((u32)cres + cres->stripeDataOffset);
        }

        return NULL;
    }

    bool IsHasChildParticle() const
    {
        if (res->type == EFT_EMITTER_TYPE_SIMPLE)
            return false;

        const ComplexEmitterData* cres = reinterpret_cast<const ComplexEmitterData*>(res);

        if (cres->childFlg & EFT_CHILD_FLAG_ENABLE)
            return true;
        else
            return false;
    }

    bool IsEnableUserDataFlag(nw::eft::UserDataFlag bit) const
    {
        return (res->userData & bit) ? true : false;
    }

    u8 GetUserDataU8Param0() const
    {
        return static_cast<u8>(res->userData);
    }

    u8 GetUserDataU8Param1() const
    {
        return static_cast<u8>(res->userData >> 8);
    }

    u8 GetUserDataU8Param2() const
    {
        return static_cast<u8>(res->userData2);
    }

    u8 GetUserDataU8Param3() const
    {
        return static_cast<u8>(res->userData2 >> 8);
    }

    u8 GetUserDataU8Param4() const
    {
        return static_cast<u8>(res->userData2 >> 16);
    }

    u8 GetUserDataU8Param5() const
    {
        return static_cast<u8>(res->userData2 >> 24);
    }

    f32 GetUserDataF32Param(nw::eft::UserDataParamIdx idx) const
    {
        return res->userDataF[idx];
    }
};
static_assert(sizeof(EmitterInstance) == 0x220, "nw::eft::EmitterInstance size mismatch");

class System;

class EmitterCalc
{
public:
    explicit EmitterCalc(System* sys)
    {
        mSys = sys;
    }

    virtual ~EmitterCalc() // deleted
    {
        mSys = NULL;
    }

    virtual void CalcEmitter(EmitterInstance* e) = 0;

    static void Initialize(Heap *heap)
    {
        InitializeFluctuation_(heap);
    }

    static void Finalize(Heap *heap)
    {
        FinalzieFluctuation_(heap);
        mSys = NULL;
    }

    static void EmitParticle(EmitterInstance* __restrict e)
    {
        mEmitFunctions[e->res->volumeType](e);
    }

    static void RemoveParticle(EmitterInstance* e, PtclInstance* ptcl, CpuCore core);

    virtual PtclType GetPtclType() const = 0;

    virtual u32 CalcParticle(EmitterInstance* e, CpuCore core, bool skipBehavior, bool skipMakeAttribute)
    {
        return 0;
    }

    virtual u32 CalcChildParticle(EmitterInstance* e, CpuCore core, bool skipBehavior, bool skipMakeAttribute)
    {
        return 0;
    }

    static u32 CalcSimpleParticleBehavior (EmitterInstance* __restrict e, PtclInstance* __restrict ptcl, CpuCore core);
    static u32 CalcComplexParticleBehavior(EmitterInstance* __restrict e, PtclInstance* __restrict ptcl, CpuCore core);
    static u32 CalcChildParticleBehavior  (EmitterInstance* __restrict e, PtclInstance* __restrict ptcl, CpuCore core);
    static void MakeParticleAttributeBuffer(PtclAttributeBuffer* __restrict attrBuffer, PtclInstance* __restrict ptcl, u32 shaderAttrFlag, f32 cameraOffset);

protected:
    static System* mSys;

    static PtclInstance* _emitPoint               (EmitterInstance* __restrict e);
    static PtclInstance* _emitCircle              (EmitterInstance* __restrict e);
    static PtclInstance* _emitCircleSameDivide    (EmitterInstance* __restrict e);
    static PtclInstance* _emitFillCircle          (EmitterInstance* __restrict e);
    static PtclInstance* _emitSphere              (EmitterInstance* __restrict e);
    static PtclInstance* _emitSphereSameDivide    (EmitterInstance* __restrict e);
    static PtclInstance* _emitSphereSameDivide64  (EmitterInstance* __restrict e);
    static PtclInstance* _emitFillSphere          (EmitterInstance* __restrict e);
    static PtclInstance* _emitCylinder            (EmitterInstance* __restrict e);
    static PtclInstance* _emitFillCylinder        (EmitterInstance* __restrict e);
    static PtclInstance* _emitBox                 (EmitterInstance* __restrict e);
    static PtclInstance* _emitFillBox             (EmitterInstance* __restrict e);
    static PtclInstance* _emitLine                (EmitterInstance* __restrict e);
    static PtclInstance* _emitLineSameDivide      (EmitterInstance* __restrict e);
    static PtclInstance* _emitRectangle           (EmitterInstance* __restrict e);

    typedef PtclInstance* (*EmitFunction)(EmitterInstance* __restrict e);
    static EmitFunction mEmitFunctions[];

    static const void* _ptclField_Random     (EmitterInstance* __restrict e, PtclInstance* __restrict ptcl, const void* fieldData);
    static const void* _ptclField_Magnet     (EmitterInstance* __restrict e, PtclInstance* __restrict ptcl, const void* fieldData);
    static const void* _ptclField_Spin       (EmitterInstance* __restrict e, PtclInstance* __restrict ptcl, const void* fieldData);
    static const void* _ptclField_Collision  (EmitterInstance* __restrict e, PtclInstance* __restrict ptcl, const void* fieldData);
    static const void* _ptclField_Convergence(EmitterInstance* __restrict e, PtclInstance* __restrict ptcl, const void* fieldData);
    static const void* _ptclField_PosAdd     (EmitterInstance* __restrict e, PtclInstance* __restrict ptcl, const void* fieldData);
    static void _calcField(const ComplexEmitterData* __restrict res, EmitterInstance* __restrict e, PtclInstance* __restrict ptcl);

    static f32* sFluctuationTbl;
    static void InitializeFluctuation_(Heap* heap);
    static void FinalzieFluctuation_(Heap* heap);
    static void CalcFluctuation(EmitterInstance* __restrict e, PtclInstance* __restrict ptcl);

    static void EmitCommon(EmitterInstance* __restrict e, PtclInstance* __restrict ptcl);

    static inline void AddParticle(EmitterInstance* emitter, PtclInstance* ptcl);
};
static_assert(sizeof(EmitterCalc) == 4, "nw::eft::EmitterCalc size mismatch");

inline void EmitterCalc::_calcField(const ComplexEmitterData* __restrict res, EmitterInstance* __restrict e, PtclInstance* __restrict ptcl)
{
    const void* __restrict fres = reinterpret_cast<const void*>((u32)res + res->fieldDataOffset);

    if ( res->fieldFlg & EFT_FIELD_MASK_RANDOM      ) fres = _ptclField_Random     (e, ptcl, fres);
    if ( res->fieldFlg & EFT_FIELD_MASK_MAGNET      ) fres = _ptclField_Magnet     (e, ptcl, fres);
    if ( res->fieldFlg & EFT_FIELD_MASK_SPIN        ) fres = _ptclField_Spin       (e, ptcl, fres);
    if ( res->fieldFlg & EFT_FIELD_MASK_COLLISION   ) fres = _ptclField_Collision  (e, ptcl, fres);
    if ( res->fieldFlg & EFT_FIELD_MASK_CONVERGENCE ) fres = _ptclField_Convergence(e, ptcl, fres);
    if ( res->fieldFlg & EFT_FIELD_MASK_POSADD      ) fres = _ptclField_PosAdd     (e, ptcl, fres);
}

void EmitterCalc::AddParticle(EmitterInstance* emitter, PtclInstance* ptcl)
{
    if (emitter->ptclHead == NULL)
    {
        emitter->ptclHead       = ptcl;
        ptcl->prev              = NULL;
        ptcl->next              = NULL;
    }
    else
    {
        emitter->ptclHead->prev = ptcl;
        ptcl->next              = emitter->ptclHead;
        emitter->ptclHead       = ptcl;
        ptcl->prev              = NULL;
    }

    if (emitter->ptclTail == NULL)
        emitter->ptclTail = ptcl;

    emitter->ptclNum++;
}

} } // namespace nw::eft

#endif // EFT_EMITTER_H_
