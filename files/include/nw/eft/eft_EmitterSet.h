#ifndef EFT_EMITTER_SET_H_
#define EFT_EMITTER_SET_H_

#include <nw/eft/eft_typeDef.h>
#include <nw/eft/eft_Data.h>
#include <nw/eft/eft_System.h>
#include <nw/eft/eft_Resource.h>
#include <nw/eft/eft_Emitter.h>

namespace nw { namespace eft {

struct EmitterInstance;

class EmitterController
{
public:
    enum
    {
        EFT_EMT_CTRLR_SCALE_BIT = 8 ,
        EFT_EMT_CTRLR_SCALE_ONE = ( 1 << EFT_EMT_CTRLR_SCALE_BIT )
    };

public:
    void Reset()
    {
        mEmissionRatio              = 1.0f;
        mEmissionInterval           = 1.0f;
        mLife                       = 1.0f;
        mDrawViewFlag               = EFT_DRAW_VIEW_FLAG_ALL;
    }

    void SetEmissionRatio(s32 ratio)
    {
        mEmissionRatio = static_cast<f32>(ratio) / EFT_EMT_CTRLR_SCALE_ONE;
    }

    void SetEmissionRatio(f32 ratio)
    {
        mEmissionRatio = ratio;
    }

    void SetEmissionInterval(s32 ratio)
    {
        mEmissionInterval = static_cast<f32>(ratio) / EFT_EMT_CTRLR_SCALE_ONE;
    }

    void SetEmissionInterval(f32 ratio)
    {
        mEmissionInterval = ratio;
    }

    void SetLife(s32 ratio)
    {
        mLife = static_cast<f32>(ratio) / EFT_EMT_CTRLR_SCALE_ONE;
    }

    void SetLife(f32 ratio)
    {
        mLife = ratio;
    }

    void SetVisible(bool isVisible)
    {
        if (isVisible)
            mDrawViewFlag = EFT_DRAW_VIEW_FLAG_ALL;
        else
            mDrawViewFlag = EFT_DRAW_VIEW_FLAG_NONE;
    }

    void SetViewFlag(DrawViewFlag flag)
    {
        mDrawViewFlag = flag;
    }

    void SetStopDraw(bool isStopDraw)
    {
        if (isStopDraw)
            mDrawViewFlag = EFT_DRAW_VIEW_FLAG_NONE;
        else
            mDrawViewFlag = EFT_DRAW_VIEW_FLAG_ALL;
    }

    bool IsStopDraw() const
    {
        if (mDrawViewFlag == EFT_DRAW_VIEW_FLAG_NONE)
            return true;
        else
            return false;
    }

    DrawViewFlag GetDrawViewFlag() const
    {
        return mDrawViewFlag;
    }

    static s32 F32ToScale(f32 val)
    {
        return (s32)(val * (f32)EFT_EMT_CTRLR_SCALE_ONE);
    }

    void SetFollowType(PtclFollowType followType);
    void SetEmitterColor0(const nw::ut::FloatColor& color);
    void SetEmitterColor1(const nw::ut::FloatColor& color);

private:
    f32                         mEmissionRatio;
    f32                         mEmissionInterval;
    f32                         mLife;
    DrawViewFlag                mDrawViewFlag;
    EmitterInstance*            mEmitter;

    friend class System;
    friend class EmitterSimpleCalc;
    friend class EmitterComplexCalc;
    friend class EmitterCalc;
};
static_assert(sizeof(EmitterController) == 0x14, "nw::eft::EmitterController size mismatch");

class System;

class EmitterSet
{
public:
    EmitterSet()
        : mNumEmitter(0)
        , mNumEmitterFirst(0)
        , mEmitterCreateID(0)
        , mRuntimeUserData(0)
        , mParticleEmissionPoints(NULL)
    {
        mInitialRoate.x = 0;
        mInitialRoate.y = 0;
        mInitialRoate.z = 0;

        for (u32 i = 0; i < EFT_EMITTER_INSET_NUM; i++)
            mInstance[i] = NULL;
    }

    void SetSystem(System* sys)
    {
        mSystem = sys;
    }

    System* GetSystem()
    {
        return mSystem;
    }

    s32 GetResourceID() const
    {
        return mResourceID;
    }

    s32 GetEmitterSetID() const
    {
        return mEmitterSetID;
    }

    u32 GetCreateID() const
    {
        return mEmitterCreateID;
    }

    const char* GetEmitterSetName() const
    {
        return mSystem->SearchEmitterSetName( mEmitterSetID, mResourceID );
    }

    s32 GetNumEmitter() const
    {
        return mNumEmitter;
    }

    s32 GetNumAliveEmitter() const
    {
        return mNumEmitter;
    }

    const EmitterInstance* GetAliveEmitter( u32 idx );

    s32 GetNumCreatedEmitter() const
    {
        return mNumEmitterFirst;
    }

    s32 GetEmitterCounter(const char* emitterName);

    s32 GetEmitterCounter(s32 emitterID);

    u8 GetGroupID() const
    {
        return static_cast<u8>(mGroupID);
    }

    EmitterSet* GetNext() const
    {
        return mNext;
    }

    bool IsLoopEffect() const;

    bool IsAlive() const
    {
        return mNumEmitter > 0;
    }

    bool IsHaveInfinityEmitter() const
    {
        return mIsHaveInfinityEmitter;
    }

    nw::math::MTX34& GetSRTMatrix()
    {
        return mSRT;
    }

    nw::math::MTX34& GetRTMatrix()
    {
        return mRT;
    }

    void SetDrawPriority(u8 priority)
    {
        mDrawPriority = priority;
    }

    u8 GetDrawPriority() const
    {
        return mDrawPriority;
    }

    u32 GetUserData() const
    {
        return mSystem->GetResource(mResourceID)->GetUserData(mEmitterSetID);
    }

    u8 GetUserDataNum1() const
    {
        return mSystem->GetResource(mResourceID)->GetUserDataNum1(mEmitterSetID);
    }

    u8 GetUserDataNum2() const
    {
        return mSystem->GetResource(mResourceID)->GetUserDataNum2(mEmitterSetID);
    }

    u16 GetUserDataBit() const
    {
        return mSystem->GetResource(mResourceID)->GetUserDataBit(mEmitterSetID);
    }

    void SetMtx(const nw::math::MTX34& mtx);

    void SetMtxFast(const nw::math::MTX34& mtx)
    {
        mSRT = mRT = mtx;
        mAutoCalcScale = nw::math::VEC3(1.0f, 1.0f, 1.0f);
        updateParticleScale_();
    }

    void SetMtxFast(const nw::math::MTX34& mtx, f32 scale)
    {
        mSRT.m[0][0] = mtx.m[0][0] * scale;
        mSRT.m[1][0] = mtx.m[1][0] * scale;
        mSRT.m[2][0] = mtx.m[2][0] * scale;

        mSRT.m[0][1] = mtx.m[0][1] * scale;
        mSRT.m[1][1] = mtx.m[1][1] * scale;
        mSRT.m[2][1] = mtx.m[2][1] * scale;

        mSRT.m[0][2] = mtx.m[0][2] * scale;
        mSRT.m[1][2] = mtx.m[1][2] * scale;
        mSRT.m[2][2] = mtx.m[2][2] * scale;

        mSRT.m[0][3] = mtx.m[0][3];
        mSRT.m[1][3] = mtx.m[1][3];
        mSRT.m[2][3] = mtx.m[2][3];

        mRT = mtx;
        mAutoCalcScale.x = scale;
        mAutoCalcScale.y = scale;
        mAutoCalcScale.z = scale;
        updateParticleScale_();
    }

    void SetMtxFast(const nw::math::MTX34& mtx, const nw::math::VEC3& scale)
    {
        mSRT.m[0][0] = mtx.m[0][0] * scale.x;
        mSRT.m[1][0] = mtx.m[1][0] * scale.x;
        mSRT.m[2][0] = mtx.m[2][0] * scale.x;

        mSRT.m[0][1] = mtx.m[0][1] * scale.y;
        mSRT.m[1][1] = mtx.m[1][1] * scale.y;
        mSRT.m[2][1] = mtx.m[2][1] * scale.y;

        mSRT.m[0][2] = mtx.m[0][2] * scale.z;
        mSRT.m[1][2] = mtx.m[1][2] * scale.z;
        mSRT.m[2][2] = mtx.m[2][2] * scale.z;

        mSRT.m[0][3] = mtx.m[0][3];
        mSRT.m[1][3] = mtx.m[1][3];
        mSRT.m[2][3] = mtx.m[2][3];

        mRT = mtx;
        mAutoCalcScale = scale;
        updateParticleScale_();
    }

    void SetPos(const nw::math::VEC3& pos)
    {
        mSRT.SetIdentity();
        mSRT.SetTranslate(pos);
        mRT = mSRT;
        updateParticleScale_();
    }

    void SetPos(const nw::math::VEC3& pos, f32 scale)
    {
        mRT.SetIdentity();
        mRT.SetTranslate(pos);
        mSRT = mRT;
        mSRT.m[0][0] *= scale;
        mSRT.m[1][1] *= scale;
        mSRT.m[2][2] *= scale;
        mAutoCalcScale.x = scale;
        mAutoCalcScale.y = scale;
        mAutoCalcScale.z = scale;
        updateParticleScale_();
    }

    void SetPos(const nw::math::VEC3& pos, const nw::math::VEC3& scale)
    {
        mRT.SetIdentity();
        mRT.SetTranslate(pos);
        mSRT = mRT;
        mSRT.m[0][0] *= scale.x;
        mSRT.m[1][1] *= scale.y;
        mSRT.m[2][2] *= scale.z;
        mAutoCalcScale = scale;
        updateParticleScale_();
    }

    void GetPos(nw::math::VEC3& pos) const
    {
        pos.x = mSRT.m[0][3];
        pos.y = mSRT.m[1][3];
        pos.z = mSRT.m[2][3];
    }

    void Kill();
    void KillInfinityEmitter();

    void Reset(const nw::math::MTX34& matLW)
    {
        mSRT           = matLW;
        mRT            = matLW;
        mAutoCalcScale = nw::math::VEC3(1.0f, 1.0f, 1.0f);
        mEmitterScale  = nw::math::VEC3(1.0f, 1.0f, 1.0f);
        mEmissionParticleScale = nw::math::VEC2(1.0f, 1.0f);
        mParticlScaleForCalc.x = 1.0f;
        mParticlScaleForCalc.y = 1.0f;
        mStartFrame    = 0;

        mParticlScale.x = mParticlScale.y = 1.0f;
        mColor.r = mColor.g = mColor.b = mColor.a = 1.0f;
        mFigureVel = mDirectionalVel = mRandomVel = 1.0f;
        mVelAdd.x = mVelAdd.y = mVelAdd.z = 0.0f;
        mIsSetDirectional      = false;
        mFadeRequest           = false;
        mIsStopCalc            = false;
        mIsStopDraw            = false;
        mIsHaveInfinityEmitter = false;
        mNumParticleEmissionPoint = 0;

        mDrawPriority           = EFT_DEFAULT_DRAW_PRIORITY;
        mDrawPathFlag           = 0;

        mInitialRoate.Set(0.0f, 0.0f, 0.0f);

        for (u32 i = 0; i < EFT_EMITTER_INSET_NUM; ++i)
            mInstance[i] = NULL;
    }

    void Fade()
    {
        mFadeRequest = true;
    }

    bool IsFadeRequest() const
    {
        return mFadeRequest;
    }

    void CancelFade()
    {
        mFadeRequest = false;
    }

    void SetParticleScale(f32 scale)
    {
        mParticlScale.x = mParticlScale.y = scale;
        updateParticleScale_();
    }

    void SetParticleScale(f32 scaleX, f32 scaleY)
    {
        mParticlScale.x = scaleX;
        mParticlScale.y = scaleY;
        updateParticleScale_();
    }

    void SetParticleScale(const nw::math::VEC2& scale)
    {
        mParticlScale = scale;
        updateParticleScale_();
    }

    const nw::math::VEC2& GetParticleScale() const
    {
        return mParticlScale;
    }

    void SetEmissionParticleScale(f32 scale)
    {
        mEmissionParticleScale.x = mEmissionParticleScale.y = scale;
    }

    void SetEmissionParticleScale(f32 scaleX, f32 scaleY)
    {
        mEmissionParticleScale.x = scaleX;
        mEmissionParticleScale.y = scaleY;
    }

    void SetEmissionParticleScale(const nw::math::VEC2& scale)
    {
        mEmissionParticleScale = scale;
    }

    const nw::math::VEC2& GetEmissionParticleScale() const
    {
        return mEmissionParticleScale;
    }

    void SetEmitterScale(const nw::math::VEC3& scale)
    {
        mEmitterScale = scale;
    }

    const nw::math::VEC3& GetEmitterScale() const
    {
        return mEmitterScale;
    }

    const nw::math::VEC2& GetParticleScaleForCalc() const
    {
        return mParticlScaleForCalc;
    }

    void SetAlpha(f32 alpha)
    {
        mColor.a = alpha;
    }

    void SetColor(f32 r, f32 g, f32 b)
    {
        mColor.r = r;
        mColor.g = g;
        mColor.b = b;
    }

    void SetColor(const nw::ut::FloatColor& color)
    {
        mColor = color;
    }

    const nw::ut::FloatColor& GetColor() const
    {
        return mColor;
    }

    void SetAllDirectionalVel(f32 velScale)
    {
        mFigureVel = velScale;
    }

    f32 GetAllDirectionalVel() const
    {
        return mFigureVel;
    }

    void SetDirectionalVel(f32 velScale)
    {
        mDirectionalVel = velScale;
    }

    f32 GetDirectionalVel() const
    {
        return mDirectionalVel;
    }

    void SetRandomVel(f32 velScale)
    {
        mRandomVel = velScale;
    }

    f32 GetRandomVel() const
    {
        return mRandomVel;
    }

    void SetAddVel(const nw::math::VEC3& velAdd)
    {
        mVelAdd = velAdd;
    }

    const nw::math::VEC3& GetVelAdd() const
    {
        return mVelAdd;
    }

    void SetDirectional(const nw::math::VEC3& dir)
    {
        mDirectional = dir;
        mIsSetDirectional = true;
    }

    const nw::math::VEC3& GetDirectional() const
    {
        return mDirectional;
    }

    void SetInitRotate(const nw::math::VEC3& rot)
    {
        mInitialRoate = rot;
    }

    /* void SetInitRotate(const Vector3i& rot)
    {
        mInitialRoate.x = NW_MATH_IDX_TO_RAD(rot.x);
        mInitialRoate.y = NW_MATH_IDX_TO_RAD(rot.y);
        mInitialRoate.z = NW_MATH_IDX_TO_RAD(rot.z);
    } */

    void DisableDirectional()
    {
        mIsSetDirectional = false;
    }

    bool IsSetDirectional() const
    {
        return mIsSetDirectional;
    }

    void SetStartFrame(s32 frame)
    {
        mStartFrame = frame;
    }

    s32 GetStartFrame() const
    {
        return mStartFrame;
    }

    EmitterController* GetEmitterController(s32 ix)
    {
        return &mController[ix];
    }

    const EmitterController* GetAliveEmitterController(s32 ix);

    void SetParticleEmissionPoints(s32 numPoint, nw::math::VEC3* points)
    {
        mNumParticleEmissionPoint = numPoint;
        mParticleEmissionPoints = points;
    }

    void SetManualParticleEmission(bool isManual)
    {
        mStartFrame = isManual ? 0x7fffffff : 0;
    }

    void EmitParticle(const nw::math::VEC3& pos);

    void ForceCalc(s32 numLoop);

    void SetStopCalcAndDraw(bool isStopCalcAndDraw)
    {
        mIsStopCalc = isStopCalcAndDraw;
        mIsStopDraw = isStopCalcAndDraw;
    }

    bool IsStopCalcAndDraw() const
    {
        return mIsStopCalc && mIsStopDraw;
    }

    void SetStopCalc(bool isStopCalc);

    bool IsStopCalc() const
    {
        return mIsStopCalc;
    }

    void SetStopDraw(bool isStopDraw);

    bool IsStopDraw() const
    {
        return mIsStopDraw;
    }

    void SetStopDraw(u32 emitterID, bool isStopDraw)
    {
        mController[emitterID].SetStopDraw(isStopDraw);
    }

    void SetRandomSeed(u32 seed);

    u32 GetRuntimeUserData() const
    {
        return mRuntimeUserData;
    }

    void SetRuntimeUserData(u32 data)
    {
        mRuntimeUserData = data;
    }

    void UpdateEmitterFromResInfo();

private:
    System*             mSystem;
    s32                 mNumEmitter;
    s32                 mNumEmitterFirst;
    u32                 mEmitterCreateID;
    EmitterInstance*    mInstance[EFT_EMITTER_INSET_NUM];
    EmitterController   mController[EFT_EMITTER_INSET_NUM];
    s32                 mResourceID;
    s32                 mEmitterSetID;
    u32                 mRuntimeUserData;
    s32                 mGroupID;
    u32                 mDrawPathFlag;

    nw::math::MTX34     mSRT;
    nw::math::MTX34     mRT;
    nw::math::VEC3      mAutoCalcScale;

    nw::math::VEC2      mParticlScale;
    nw::math::VEC2      mEmissionParticleScale;
    nw::math::VEC2      mParticlScaleForCalc;
    nw::math::VEC3      mEmitterScale;

    nw::ut::FloatColor  mColor;
    f32                 mFigureVel;
    f32                 mDirectionalVel;
    f32                 mRandomVel;
    nw::math::VEC3      mVelAdd;
    nw::math::VEC3      mDirectional;
    s32                 mStartFrame;
    nw::math::VEC3      mInitialRoate;
    s32                 mNumParticleEmissionPoint;
    nw::math::VEC3*     mParticleEmissionPoints;

    EmitterSet*         mNext;
    EmitterSet*         mPrev;

    bool                mFadeRequest;
    bool                mIsSetDirectional;
    bool                mIsStopCalc;
    bool                mIsStopDraw;
    bool                mIsHaveInfinityEmitter;

    u8                  mDrawPriority;
    u8                  _28e[EFT_CPU_CORE_MAX];

    inline void updateParticleScale_()
    {
        mParticlScaleForCalc.x = mParticlScale.x * mAutoCalcScale.x;
        mParticlScaleForCalc.y = mParticlScale.y * mAutoCalcScale.y;
    }

    friend class System;
    friend class EmitterSimpleCalc;
    friend class EmitterComplexCalc;
    friend class EmitterCalc;
    friend class Renderer;
};
static_assert(sizeof(EmitterSet) == 0x294, "nw::eft::EmitterSet size mismatch");

} } // namespace nw::eft

#endif // EFT_EMITTER_SET_H_
