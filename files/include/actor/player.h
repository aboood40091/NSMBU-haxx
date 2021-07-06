#pragma once

#include "actor.h"

class PlayerInput
{
public:
    bool isDownPressed() const;
    bool isUpPressed() const;

    bool isRightHeld() const;
    bool isLeftHeld() const;
    bool isDownHeld() const;
    bool isUpHeld() const;

    bool isOnlyDownHeld() const;

    bool isOnlyUpHeld() const
    {
        return isUpHeld() && !isRightHeld() && !isLeftHeld() && !isDownHeld();
    }

    u8 _0[0x94];
};

class PlayerBase : public Actor
{
public:
    u8 _27C[0x2A8 - 0x27C];
    PlayerInput input;
    // ...
};

class Player : public PlayerBase
{
public:
    bool vf8CC(Actor*, u32);
    bool setDamageState(Actor*, u32); // 8D4

    // ...
};
