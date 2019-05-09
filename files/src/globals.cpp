#include <globals.h>

LevelData *Level;
LevelInfoStruct *LevelInfo;

void *PhysicsCollisionMgr;
void *Drawer;

// Sometimes, instances of the globals above can be uninitialized
// To avoid this, we set them at the right time

void setLevelInstances() {
    Level = *(LevelData **)0x106DD248;
    LevelInfo = *(LevelInfoStruct **)0x106D3AEC;
}

void setPhysCollMgrInstance() {
    PhysicsCollisionMgr = *(void **)0x106CB560;
}

void setDrawerInstance() {
    Drawer = *(void **)0x106D4F88;
}
