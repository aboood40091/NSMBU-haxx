#include <actor/player.h>
#include <model.h>
#include <playermgr.h>
#include <ptclmgr.h>

#include <nw/eft/eft_Handle.h>

#include <log.h>

/*
    TODO:
    * Make it more customizable.
    * Better digits rendering (make sead::PrimitiveRenderer work).
    * Better handling of inputs (slightly).
    * Better centering of emitter set number.

    Controls (Player 1 only):
    * Down: Next effect (emitter set)
    * Up: Previous effect (emitter set)
*/

class EffectPlayer : public Actor
{
public:
    EffectPlayer(const ActorBuildInfo* buildInfo);

    static ActorBase* build(const ActorBuildInfo* buildInfo)
    {
        return new EffectPlayer(buildInfo);
    }

    u32 onCreate()  override;
    u32 onExecute() override;
    u32 onDraw()    override;

private:
    bool nextEffect_(const PlayerInput& player1_input);
    bool prevEffect_(const PlayerInput& player1_input);
    void killEffect_();

private:
    static const Vec2 s_p1;
    static const Vec2 s_p2;
    static const Vec2 s_p3;
    static const Vec2 s_p4;
    static const Vec2 s_p5;
    static const Vec2 s_p6;

    static const s32 cHoldRegisterDuration = 15; // 0.25 sec

    nw::eft::Handle mEffectHandle;
    s32             mCurrentEmitterSetID;
    nw::math::MTX34 mMtx;
    bool            mIsDownHeld;
    bool            mIsUpHeld;
    s32             mDownHeldCnt;
    s32             mUpHeldCnt;

    BasicModel*     mModel[4][7]; // 4 digits, each can use up to 7 lines
};

const Vec2 EffectPlayer::s_p1(-8.0f,  16.0f);
const Vec2 EffectPlayer::s_p2( 8.0f,  16.0f);
const Vec2 EffectPlayer::s_p3( 8.0f,   0.0f);
const Vec2 EffectPlayer::s_p4( 8.0f, -16.0f);
const Vec2 EffectPlayer::s_p5(-8.0f, -16.0f);
const Vec2 EffectPlayer::s_p6(-8.0f,   0.0f);

const Profile effectPlayerProfile(&EffectPlayer::build, cProfileId_EffectPlayer, "EffectPlayer", nullptr, 0);
PROFILE_RESOURCES(cProfileId_EffectPlayer, "block_snake");

EffectPlayer::EffectPlayer(const ActorBuildInfo* buildInfo)
    : Actor(buildInfo)
    , mEffectHandle()
    , mCurrentEmitterSetID(-1)
    , mMtx(nw::math::MTX34::Identity())
    , mIsDownHeld(false)
    , mIsUpHeld(false)
    , mDownHeldCnt(0)
    , mUpHeldCnt(0)
{
}

u32 EffectPlayer::onCreate()
{
    LOG("EffectPlayer: onCreate start")

    mCurrentEmitterSetID    = -1;
    mIsDownHeld             = false;
    mIsUpHeld               = false;
    mDownHeldCnt            = 0;
    mUpHeldCnt              = 0;

    nw::math::VEC3 ef_scale(scale.x, scale.y, scale.z);

    nw::math::VEC3 ef_rotat;
    if (settings1 & 1)
    {
        ef_rotat.x = sead::Mathf::idx2rad(rotation.x + 0x20000000);
        ef_rotat.y = sead::Mathf::idx2rad(rotation.y + 0x20000000);
    }
    else
    {
        ef_rotat.x = sead::Mathf::idx2rad(rotation.x);
        ef_rotat.y = sead::Mathf::idx2rad(rotation.y);
    }
    ef_rotat.z = sead::Mathf::idx2rad(rotation.z);

    nw::math::VEC3 ef_trans;
    ef_trans.x = (position.x += 8.0f);
    ef_trans.y = (position.y -= 8.0f);
    ef_trans.z = position.z;

    nw::math::MTX34MakeSRT(&mMtx, ef_scale,
                                  ef_rotat,
                                  ef_trans);

    for (u32 i = 0; i < 4; i++)
        for (u32 j = 0; j < 7; j++)
            mModel[i][j] = BasicModel::create("block_snake", "block_snake");

    LOG("EffectPlayer: onCreate end")

    return 1;
}

u32 EffectPlayer::onExecute()
{
    s32 numEmitterSet = PtclMgr::instance()->system->GetResource(0)->GetNumEmitterSet();
    if (numEmitterSet < 1 || mCurrentEmitterSetID >= numEmitterSet)
    {
failure:
        LOG("EffectPlayer: Failure")
        killEffect_();
        isDeleted = true;
        return 1;
    }

    const Player* player1 = nullptr;
    if (PlayerMgr::instance()->playerFlags & 1)
        player1 = PlayerMgr::instance()->players[0];

    if (player1 && nextEffect_(player1->input))
    {
        mCurrentEmitterSetID = (mCurrentEmitterSetID + 1) % numEmitterSet;
        LOG("EffectPlayer: Proceeding to next: %d", mCurrentEmitterSetID)
    }
    else if (player1 && prevEffect_(player1->input))
    {
        mCurrentEmitterSetID = (mCurrentEmitterSetID - 1) % numEmitterSet;
        if (mCurrentEmitterSetID < 0)
            mCurrentEmitterSetID += numEmitterSet;
        LOG("EffectPlayer: Going to previous: %d", mCurrentEmitterSetID)
    }
    else
    {
        if (mCurrentEmitterSetID == -1)
            return 1;
        else
            goto update;
    }

    killEffect_();

    if (!PtclMgr::instance()->system->CreateEmitterSetID(&mEffectHandle, nw::math::MTX34::Identity(), mCurrentEmitterSetID, 0, PtclMgr::instance()->getEmitterSetGroupID(mCurrentEmitterSetID)))
        goto failure;

    LOG("EffectPlayer: Create succeeded")

update:
    if (!mEffectHandle.IsValid())
        goto failure;

    mEffectHandle.GetEmitterSet()->SetMtx(mMtx);

    return 1;
}

u32 EffectPlayer::onDraw()
{
    return 1;
}

bool EffectPlayer::nextEffect_(const PlayerInput& player1_input)
{
    if (!mIsDownHeld)
    {
        if (player1_input.isDownPressed())
        {
            mIsDownHeld = true;
            mDownHeldCnt = 0;
        }
    }
    else
    {
        if (player1_input.isDownHeld())
        {
            if (player1_input.isOnlyDownHeld() && ++mDownHeldCnt >= cHoldRegisterDuration)
            {
                mDownHeldCnt = 0;
                return true;
            }
        }
        else
        {
            mIsDownHeld = false;
            if (mDownHeldCnt > 0)
                return true;
        }
    }

    return false;
}

bool EffectPlayer::prevEffect_(const PlayerInput& player1_input)
{
    if (!mIsUpHeld)
    {
        if (player1_input.isUpPressed())
        {
            mIsUpHeld = true;
            mUpHeldCnt = 0;
        }
    }
    else
    {
        if (player1_input.isUpHeld())
        {
            if (player1_input.isOnlyUpHeld() && ++mUpHeldCnt >= cHoldRegisterDuration)
            {
                mUpHeldCnt = 0;
                return true;
            }
        }
        else
        {
            mIsUpHeld = false;
            if (mUpHeldCnt > 0)
                return true;
        }
    }

    return false;
}

void EffectPlayer::killEffect_()
{
    if (mEffectHandle.IsValid())
    {
        nw::eft::EmitterSet* set = mEffectHandle.GetEmitterSet();
        if (set->IsAlive())
            set->Fade();
    }

    mEffectHandle.Invalidate();
}
