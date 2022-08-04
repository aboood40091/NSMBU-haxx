#ifndef SEAD_CONTROLLER_DEFINE_H_
#define SEAD_CONTROLLER_DEFINE_H_

namespace sead {

class ControllerDefine
{
public:
    enum ControllerId
    {
        cController_Null       = 0,
        cController_Win        = 1,
        cController_Ctr        = 2,
        cController_CtrDebug   = 3,
        cController_WiiRemote  = 4,
        cController_CafeDebug  = 5,
        cController_WinDRC     = 6,
        cController_CafeRemote = 7,
        cController_CafeDRC    = 8,
        cController_Merge      = 9,
        cController_UserDefine = 10
    };

    enum DeviceId
    {
        cDevice_Null          = 0,
        cDevice_KeyboardMouse = 1,
        cDevice_CtrHid        = 2,
        cDevice_WinJoyPad     = 3,
        cDevice_RvlWPad       = 4,
        cDevice_WinWPad       = 5,
        cDevice_CafeDebugPad  = 6,
        cDevice_CafeWPad      = 7,
        cDevice_CafeVPad      = 8,
        cDevice_UserDefine    = 9
    };

    enum AddonId
    {
        cAddon_Null          = 0,
        cAddon_Accelerometer = 1,
        cAddon_PatternRumble = 2,
        cAddon_UserDefine    = 3
    };
};

} // namespace sead

#endif // SEAD_CONTROLLER_DEFINE_H_
