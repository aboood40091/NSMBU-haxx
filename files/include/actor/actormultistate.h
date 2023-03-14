#pragma once

#include "actorcollision.h"
#include "states.h"

class ActorMultiState : public ActorCollision
{
    SEAD_RTTI_OVERRIDE(ActorMultiState, ActorCollision)

public:
    ActorMultiState(const ActorBuildInfo* buildInfo);
    virtual ~ActorMultiState() { }

    virtual void doStateChange(StateBase* state)
    {
        states.changeState(state);
    }

    StateWrapper<ActorMultiState> states;       // 17A0
    u32 _17C4;                                  // 17C4
};
