#ifndef SEAD_CONTROL_DEVICE_H_
#define SEAD_CONTROL_DEVICE_H_

#include <container/seadListImpl.h>
#include <controller/seadControllerDefine.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace sead {

class ControllerMgr;

class ControlDevice
{
    SEAD_RTTI_BASE(ControlDevice)

public:
    ControlDevice()
        : mListNode()
        , mId(ControllerDefine::cDevice_Null)
        , mMgr(NULL)
    {
    }

    virtual ~ControlDevice()
    {
    }

    virtual void calc() = 0;

protected:
    ListNode mListNode;
    ControllerDefine::DeviceId mId;
    ControllerMgr* mMgr;

    friend class ControllerMgr;
};
#ifdef cafe
static_assert(sizeof(ControlDevice) == 0x14, "sead::ControlDevice size mismatch");
#endif // cafe

} // namespace sead

#endif // SEAD_CONTROL_DEVICE_H_
