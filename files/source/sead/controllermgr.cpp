#include <controller/seadController.h>
#include <controller/seadControllerMgr.h>

namespace sead {

Controller* ControllerMgr::getControllerByOrder(ControllerDefine::ControllerId id, s32 index) const
{
    for (PtrArray<Controller>::iterator it = mControllers.begin(); it != mControllers.end(); ++it)
    {
        Controller& controller = *it;
        if (controller.mId == id)
        {
            if (index == 0)
                return &controller;

            index--;
        }
    }

    return nullptr;
}

} // namespace sead
