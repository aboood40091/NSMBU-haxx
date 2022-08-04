#ifndef SEAD_CONTROLLER_WRAPPER_H_
#define SEAD_CONTROLLER_WRAPPER_H_

#include <controller/seadControllerWrapperBase.h>

namespace sead {

class ControllerWrapper : public ControllerWrapperBase
{
    SEAD_RTTI_OVERRIDE(ControllerWrapper, ControllerWrapperBase)

public:
    static const u8 cPadConfigDefault[Controller::cPadIdx_Max];

public:
    ControllerWrapper();
    virtual ~ControllerWrapper() { }

    virtual void calc(u32 prev_hold, bool prev_pointer_on);

    u32 createPadMaskFromControllerPadMask_(u32 controller_mask) const;
    void setPadConfig(s32 padbit_max, const u8* pad_config, bool enable_stickcross_emulation);

protected:
    u8 mPadConfig[cPadIdx_MaxBase];
};
#ifdef cafe
static_assert(sizeof(ControllerWrapper) == 0x194, "sead::ControllerWrapper size mismatch");
#endif // cafe

} // namespace sead

#endif // SEAD_CONTROLLER_WRAPPER_H_
