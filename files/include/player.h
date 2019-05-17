#pragma once

#include <sead/heap.h>
#include <actor.h>

class PlayerBase : public StageActor {
public:
};
class Player : public PlayerBase {
public:
};

class PlayerMgr : public sead::IDisposer {
public:
    // One of the following 4 variables is not present in v1.0.0
    unsigned int _10;
    unsigned int _14;
    unsigned int _18;
    unsigned int _1C;

    Player *players[4];
    Player **ptrToPlayers;

    unsigned int _34;
    unsigned int _38;
    unsigned int _3C;
    unsigned short _40;
    unsigned short playerFlags;
    unsigned int _44;
    unsigned int _48;
    unsigned int _4C;
    unsigned int _50;
};
