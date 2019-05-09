#pragma once

#include <enums.h>
#include <state.h>
#include <vec.h>

class MovementHandler {
public:
    Vec3 position;
    char _C[0x44];
    unsigned int zRotation;
    char _54[0x80];
    StateMgrBase<MovementHandler> state;

    MovementHandler();

    unsigned int GetMaskForMovementType(MovementType type);
    void FindMovementControllerAndDoState(Vec3 *actorPos, unsigned int typeMask, unsigned char movementId);
    void executeState();
};
