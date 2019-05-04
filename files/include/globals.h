#pragma once

#include <level.h>

LevelData *Level;
LevelInfoStruct *LevelInfo;

void setLevelInstances() {
    // Sometimes, the Level and LevelInfo instances can be uninitialized
    // To avoid this, we set them at the right time
    Level = *(LevelData **)0x106DD248;
    LevelInfo = *(LevelInfoStruct **)0x106D3AEC;
}
