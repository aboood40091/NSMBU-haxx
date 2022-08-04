#include <actor/actor.h>
#include <controller/seadController.h>
#include <controller/seadControllerMgr.h>

#include <log.h>

class KeyLogger : public Actor
{
public:
    KeyLogger(const ActorBuildInfo* buildInfo)
        : Actor(buildInfo)
    {
        mControllers[0] = nullptr;
        mControllers[1] = nullptr;
        mControllers[2] = nullptr;
        mControllers[3] = nullptr;
        mControllers[4] = nullptr;
        mControllers[5] = nullptr;
    }

    virtual ~KeyLogger()
    {
    }

    static Base* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDelete() override;

private:
    static KeyLogger* sInstance;

    sead::Controller* mControllers[6];
};

const ActorInfo keyLoggerActorInfo = { Vec2i(0, 0), Vec2i(0, 0), Vec2i(0, 0), 0, 0, 0, 0, ActorInfo::FlagIgnoreSpawnRange | ActorInfo::FlagUnknown };
const Profile keyLoggerProfile(&KeyLogger::build, ProfileId::KeyLogger, "KeyLogger", &keyLoggerActorInfo, 0);

KeyLogger* KeyLogger::sInstance = nullptr;

Base* KeyLogger::build(const ActorBuildInfo* buildInfo)
{
    return new KeyLogger(buildInfo);
}

u32 KeyLogger::onCreate()
{
    if (sInstance)
        return 2;

    mControllers[0] = sead::ControllerMgr::instance()->getControllerByOrder(sead::ControllerDefine::cController_CafeDebug,  0);
    mControllers[1] = sead::ControllerMgr::instance()->getControllerByOrder(sead::ControllerDefine::cController_CafeDRC,    0);
    mControllers[2] = sead::ControllerMgr::instance()->getControllerByOrder(sead::ControllerDefine::cController_CafeRemote, 0);
    mControllers[3] = sead::ControllerMgr::instance()->getControllerByOrder(sead::ControllerDefine::cController_CafeRemote, 1);
    mControllers[4] = sead::ControllerMgr::instance()->getControllerByOrder(sead::ControllerDefine::cController_CafeRemote, 2);
    mControllers[5] = sead::ControllerMgr::instance()->getControllerByOrder(sead::ControllerDefine::cController_CafeRemote, 3);

    sInstance = this;
    return 1;
}

static const char* const sControllers[6] = {
    "CafeDebug",
    "CafeDRC",
    "CafeRemote_0",
    "CafeRemote_1",
    "CafeRemote_2",
    "CafeRemote_3"
};

u32 KeyLogger::onExecute()
{
    for (u32 i = 0; i < 6; i++)
    {
        sead::Controller* controller = mControllers[i];
        if (!controller || !controller->getTrigMask())
            continue;

        const char* const name = sControllers[i];
        LOG("%s", name);

        for (s32 j = 0; j < sead::Controller::cPadIdx_Max; j++)
        {
            if (controller->isTrig(sead::BitFlag32::makeMask(j)))
            {
                LOG("%d", j);
            }
        }
    }

    return 1;
}

u32 KeyLogger::onDelete()
{
    if (sInstance == this)
        sInstance = nullptr;

    return Actor::onDelete();
}
