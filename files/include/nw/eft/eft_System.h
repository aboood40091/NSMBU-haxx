#ifndef EFT_SYSTEM_H_
#define EFT_SYSTEM_H_

#include <nw/eft/eft_typeDef.h>
#include <nw/eft/eft_Data.h>
#include <nw/eft/eft_Callback.h>

namespace nw { namespace eft {

struct AlphaAnim;
class Config;
class EmitterCalc;
class EmitterSet;
struct EmitterStaticUniformBlock;
class Handle;
class Heap;
class PtclStripe;
class Renderer;
class Resource;
struct ScaleAnim;
struct SimpleEmitterData;

class System
{
public:
    explicit System(const Config& config);
    virtual ~System(); // deleted

    void EntryResource(Heap* heap, void* resource, s32 resId);
    void ClearResource(Heap* heap, s32 resId);
    Resource* GetResource(u32 resId) { return mResource[resId]; }

    bool CreateEmitterSetID(Handle* handle, const nw::math::VEC3& pos, s32 emitterSetID, s32 resourceID = 0, u8 groupID = 0, u32 emitterMask = 0xffffffff)
    {
        nw::math::MTX34 matrix;
        matrix.SetIdentity();
        matrix._03 = pos.x;
        matrix._13 = pos.y;
        matrix._23 = pos.z;
        return CreateEmitterSetID(handle, matrix, emitterSetID, resourceID, groupID, emitterMask);
    }

    bool CreateEmitterSetID(Handle* handle, const nw::math::MTX34& mtx, s32 emitterSetID, s32 resourceID = 0, u8 groupID = 0, u32 emitterMask = 0xffffffff);

    void KillAllEmitter();
    void KillEmitterGroup(u8 groupID);
    void KillEmitterSet(EmitterSet* emitterSet);
    void KillEmitterSet(const char* emitterSetName, s32 resId);
    void KillEmitter(EmitterInstance* emitter);
    void KillParticle(EmitterInstance* emitter, PtclInstance* ptcl);
    void KillChildParticle(EmitterInstance* emitter, PtclInstance* ptcl);

    s32 SearchEmitterSetID(const char* emitterSetName, s32 resId = 0) const;
    const char* SearchEmitterSetName(s32 emitterSetId, s32 resId = 0) const;

    void BeginFrame();
    void SwapDoubleBuffer();
    void CalcEmitter(u8 groupID, f32 frameRate = 1.0f);

public:
    void CalcParticle(EmitterInstance* emitter, CpuCore core);
    void CalcChildParticle(EmitterInstance* emitter, CpuCore core);
    void CalcParticle(bool cacheFlush = true);
    void Calc(bool cacheFlush = true);

    void RemovePtcl();

    void FlushCache();
    void FlushGpuCache();

    void BeginRender(const nw::math::MTX44& proj, const nw::math::MTX34& view, const nw::math::VEC3& camPos, f32 nearClip, f32 farClip);
    void RenderEmitter(EmitterInstance* emitter, bool cacheFlush = true, void* userParam = NULL);
    void EndRender();

    Renderer* GetRenderer()
    {
        return mRenderer[GetCurrentCore()];
    }

    Renderer* GetRenderer(nw::eft::CpuCore core)
    {
        return mRenderer[core];
    }

    void SetUserDataEmitterPreCalcCallback(UserDataCallBackID id, UserDataEmitterPreCalcCallback callback);
    void SetUserDataEmitterPostCalcCallback(UserDataCallBackID id, UserDataEmitterPostCalcCallback callback);
    void SetUserDataParticleEmitCallback(UserDataCallBackID id, UserDataParticleEmitCallback callback);
    void SetUserDataParticleRemoveCallback(UserDataCallBackID id, UserDataParticleRemoveCallback callback);
    void SetUserDataParticleCalcCallback(UserDataCallBackID id, UserDataParticleCalcCallback callback);
    void SetUserDataParticleMakeAttributeCallback(UserDataCallBackID id, UserDataParticleMakeAttributeCallback callback);
    void SetUserDataEmitterDrawOverrideCallback(UserDataCallBackID id, UserDataEmitterDrawOverrideCallback callback);

    UserDataEmitterPreCalcCallback GetCurrentUserDataEmitterPreCalcCallback(const EmitterInstance* emitter);
    UserDataEmitterPostCalcCallback GetCurrentUserDataEmitterPostCalcCallback(const EmitterInstance* emitter);
    UserDataParticleEmitCallback GetCurrentUserDataParticleEmitCallback(const EmitterInstance* emitter);
    UserDataParticleRemoveCallback GetCurrentUserDataParticleRemoveCallback(const EmitterInstance* emitter);
    UserDataParticleCalcCallback GetCurrentUserDataParticleCalcCallback(const EmitterInstance* emitter);
    UserDataParticleMakeAttributeCallback GetCurrentUserDataParticleMakeAttributeCallback(const EmitterInstance* emitter);
    UserDataEmitterDrawOverrideCallback GetCurrentUserDataEmitterDrawOverrideCallback(const EmitterInstance* emitter);

    bool SetCurrentUserDataCallback(UserDataCallBackID id);

    UserShaderEmitterPostCalcCallback GetUserShaderEmitterPostCalcCallback(UserShaderCallBackID id);
    UserShaderDrawOverrideCallback GetUserShaderDrawOverrideCallback(UserShaderCallBackID id);
    UserShaderRenderStateSetCallback GetUserShaderRenderStateSetCallback(UserShaderCallBackID id);

    void SetUserShaderEmitterPostCalcCallback(UserShaderCallBackID id, UserShaderEmitterPostCalcCallback callback);
    void SetUserShaderDrawOverrideCallback(UserShaderCallBackID id, UserShaderDrawOverrideCallback callback);
    void SetUserShaderRenderStateSetCallback(UserShaderCallBackID id, UserShaderRenderStateSetCallback callback);

    bool IsValidStripe(u8 groupID) const
    {
        return mStripeHead[groupID] != NULL;
    }

    bool HasEnableEmitter(u8 groupID);

    s32 GetNumResource() const
    {
        return mNumResource;
    }

    s32 GetNumFreeEmitter() const
    {
        return mNumFreeEmitter;
    }

    s32 GetNumEmitterCalc() const
    {
        return mNumEmitterCalc;
    }

    s32 GetNumPtclCalc() const
    {
        return mNumPtclCalc;
    }

    s32 GetNumEmitterSetCalc() const
    {
        return mNumEmitterSetCalc;
    }

    s32 GetNumStripeCalc() const
    {
        return mNumStripeCalc;
    }

    s32 GetNumEmittedPtcl() const
    {
        return mNumEmittedPtcl;
    }

    u32 GetUsedDoubleBufferSize(CpuCore core = EFT_CPU_CORE_1) const;
    u32 GetDoubleBufferSize(CpuCore core = EFT_CPU_CORE_1) const;

    const EmitterInstance* GetEmitterHead(u8 groupID) const
    {
        return mEmitterHead[groupID];
    }

    EmitterInstance* GetEmitterHead(u8 groupID)
    {
        return mEmitterHead[groupID];
    }

    u32 GetNumEmitter(u8 groupID);

    const EmitterInstance* GetEmitter(u8 groupID, u32 idx) const;

    EmitterInstance* GetEmitter(u8 groupID, u32 idx);

    const EmitterSet* GetEmitterSetHead(u8 groupID) const
    {
        return mEmitterSetHead[groupID];
    }

    EmitterSet* GetEmitterSetHead(u8 groupID)
    {
        return mEmitterSetHead[groupID];
    }

    const PtclStripe* GetStripeHead(u8 groupID) const
    {
        return mStripeHead[groupID];
    }

    bool IsHasRenderingEmitter(u8 groupID, u32 drawPath) const
    {
        for (u32 core = 0; core < EFT_CPU_CORE_MAX; core++)
            if (mEnableRenderPath[core][groupID] & drawPath)
                return true;

        return false;
    }

    u64 GetEnableGroupID() const
    {
        return mEnableGroupID;
    }

    const PtclInstance* GetPtclBuf() const
    {
        return mPtcls;
    }

    u32 GetPtclBufSize() const;

    const EmitterInstance* GetEmitterBuf() const
    {
        return mEmitters;
    }

    const PtclStripe* GetStripeBuf() const
    {
        return mStripes;
    }

    static CpuCore GetCurrentCore()
    {
        return (CpuCore)OSGetCoreId();
    }

public:
    void AddPtclRemoveList(PtclInstance* ptcl, CpuCore core);
    void EmitChildParticle();
    void AddPtclAdditionList(PtclInstance* ptcl, CpuCore core);

    PtclStripe* AllocAndConnectStripe(EmitterInstance* e, PtclInstance* ptcl);
    PtclInstance* AllocPtcl(PtclType type);

    void UpdateEmitterResInfo();
    void UpdateEmitterSetResInfo();

    void RemoveStripe(PtclStripe* stripe);
    EmitterSet* RemoveEmitterSetFromDrawList(EmitterSet* set);

    void ReCreateEmitter(void** resList, s32 numResList, s32 resId, s32 setId, bool killOnly);
    void ReCreateEmitter(EmitterSet* set, s32 resId, s32 setId, u8 groupID);

private:
    EmitterSet* AllocEmitterSet(Handle* handle);
    EmitterInstance* AllocEmitter(u8 groupID);
    void AddEmitterSetToDrawList(EmitterSet* set, u8 groupID);

    void InitializeEmitter(EmitterInstance* emitter, const SimpleEmitterData* res, s32 resourceID, s32 emitterSetID, u32 setRndSeed, bool nonUpdateCreateID = false);

    void RemovePtcl_();

    struct sortEmitterSets
    {
        EmitterSet*     emitterSet;
        u32             z;
    };
    static_assert(sizeof(sortEmitterSets) == 8, "nw::eft::System::sortEmitterSets size mismatch");

    static int ComparePtclViewZ(const void* a, const void* b);

protected:
    virtual void Initialize(Heap* heap, const Config& config);

private:
    bool                        mInitialized;

    Heap*                       mHeap;
    Resource**                  mResource;
    s32                         mNumResource;
    EmitterSet*                 mEmitterSet;
    s32                         mNumEmitterSet;
    s32                         mNumEmitterSetMask;

    nw::math::MTX44             mViewMatrix[EFT_CPU_CORE_MAX];

    EmitterInstance*            mEmitterHead[EFT_GROUP_MAX];
    EmitterSet*                 mEmitterSetHead[EFT_GROUP_MAX];
    EmitterSet*                 mEmitterSetTail[EFT_GROUP_MAX];

    EmitterInstance*            mEmitters;
    EmitterStaticUniformBlock*  mEmitterStaticUniformBlock;
    s32                         mCurEmitterIx;
    s32                         mNumFreeEmitter;

    PtclInstance*               mPtcls;
    s32                         mCurPtclIx;
    AlphaAnim*                  mAlphaAnim;
    ScaleAnim*                  mScaleAnim;

    PtclInstance**              mPtclAdditionArray[EFT_CPU_CORE_MAX];
    s32                         mPtclAdditionIdx[EFT_CPU_CORE_MAX];
    PtclInstance**              mPtclRemoveArray[EFT_CPU_CORE_MAX];
    u32                         mPtclRemoveIdx[EFT_CPU_CORE_MAX];

    PtclStripe*                 mStripes;
    PtclStripe*                 mStripeHead[EFT_GROUP_MAX];

    u32                         _530;
    s32                         mCurEmitterSetIx;
    s32                         mCurStripeIx;
    s32                         mNumEmitterData;
    s32                         mNumPtclData;
    s32                         mNumStripe;
    s32                         mNumEmitterDataMask;
    s32                         mNumPtclDataMask;
    s32                         mNumStripeMask;
    s32                         mNumEmitterCalc;
    s32                         mNumPtclCalc;
    s32                         mNumEmitterSetCalc;
    s32                         mNumEmittedPtcl;
    s32                         mNumStripeCalc;
    u64                         mEnableGroupID;

    u32                         mEnableRenderPath[EFT_CPU_CORE_MAX][EFT_GROUP_MAX];
    Renderer*                   mRenderer[EFT_CPU_CORE_MAX];

    u32                         mEmitterSetCreateID;
    EmitterCalc*                mEmitterCalc[EFT_EMITTER_TYPE_MAX];

    void*                       ResourcePtr;
    void*                       mEmitterSetPtr;
    void*                       mRendererPtr[EFT_CPU_CORE_MAX];
    void*                       mEmitterCalcSimplePtr;
    void*                       mEmitterCalcComplexPtr;
    u32                         _8a4;

    UserDataCallBackID          mEnableCallbackID;
    UserDataEmitterPreCalcCallback
                                mUserDataEmitterPreCalcCallback[EFT_USER_DATA_CALLBACK_ID_MAX];
    UserDataParticleEmitCallback
                                mUserDataParticleEmitCallback[EFT_USER_DATA_CALLBACK_ID_MAX];
    UserDataParticleRemoveCallback
                                mUserDataParticleRemoveCallback[EFT_USER_DATA_CALLBACK_ID_MAX];
    UserDataParticleCalcCallback
                                mUserDataParticleCalcCallback[EFT_USER_DATA_CALLBACK_ID_MAX];
    UserDataParticleMakeAttributeCallback
                                mUserDataParticleMakeAttrCallback[EFT_USER_DATA_CALLBACK_ID_MAX];
    UserDataEmitterPostCalcCallback
                                mUserDataEmitterPostCalcCallback[EFT_USER_DATA_CALLBACK_ID_MAX];
    UserDataEmitterDrawOverrideCallback
                                mUserDataEmitterDrawOverrideCallback[EFT_USER_DATA_CALLBACK_ID_MAX];
    UserShaderEmitterPostCalcCallback
                                mUserShaderEmitterCalcPostCallback[EFT_USER_SHADER_CALLBACK_MAX];
    UserShaderDrawOverrideCallback
                                mUserShaderDrawOverrideCallback[EFT_USER_SHADER_CALLBACK_MAX];
    UserShaderRenderStateSetCallback
                                mUserShaderRenderStateSetCallback[EFT_USER_SHADER_CALLBACK_MAX];
    sortEmitterSets*            mSortEmittetSet[EFT_CPU_CORE_MAX];
    u32                         mSortEmitterSetIx[EFT_CPU_CORE_MAX];
    u32                         mCurrentDrawPathFlag[EFT_CPU_CORE_MAX];
    u32                         mCalcSwapFlag;
};
static_assert(sizeof(System) == 0xA28, "nw::eft::System size mismatch");

} } // namespace nw::eft

#endif // EFT_SYSTEM_H_
