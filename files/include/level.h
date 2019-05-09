#pragma once

#include <rect.h>

struct LevelArea {
    char _0[4];
    void *blockPtrs[15];
    // ...
};

struct LevelData {
    char _0[0x10];
    LevelArea areas[4];
};

struct AreaOptions {
    unsigned int eventBits32;
    unsigned int eventBits64;
    unsigned short wrapByte;
    unsigned short timelimit;
    char _C; // unused
    char _D;
    char _E;
    char _F;
    char startEntrance;
    char _11; // unused
    char _12; // unused
    char startEntranceCoinBoost;
    unsigned short timelimit2;
    unsigned short timelimit3;
};

struct LevelInfoStruct {
    char _0[0x12];
    char currentAreaId;
    // ...
};

struct Location {
    unsigned short x;
    unsigned short y;
    unsigned short width;
    unsigned short height;
    char id;
};

#ifdef __cplusplus
extern "C" {
#endif

LevelArea *getAreaById(LevelData *_this, unsigned int id);
Location *getLocationById(LevelArea *_this, Rect *rect, unsigned int id);

#ifdef __cplusplus
}
#endif
