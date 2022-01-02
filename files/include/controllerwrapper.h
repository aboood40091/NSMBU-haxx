#pragma once

#include <controller/seadControllerWrapper.h>
#include <controller.h>

class ControllerWrapper : public sead::ControllerWrapper
{
public:
    static const u8 cPadConfig[18];

public:
    ControllerWrapper();
    virtual ~ControllerWrapper();

    virtual void calc(u32, bool);

    void registerWith(GameController::Id id);
};
