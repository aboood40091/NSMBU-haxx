#include <sead/string.h>
#include <actor.h>
#include <globals.h>
#include <level.h>

LevelData *Level;
LevelInfoStruct *LevelInfo;

PlayerMgr *PlayerMgrInst;

void *PhysicsCollisionMgr;
void *Drawer;
void *ResLoader;

SetActorFiles::SetActorFiles(ActorIDs id, char count, const sead::String list[]) {
    fileCounts[id] = count;
    fileLists[id] = list;
}

// Sometimes, instances of the globals above can be uninitialized
// To avoid this, we set them at the right time

void setLevelInstances() {
    #ifdef Cemu
    Level = *(LevelData **)0x101DB048;
    LevelInfo = *(LevelInfoStruct **)0x101D18EC;
    #else
    Level = *(LevelData **)0x106DD248;
    LevelInfo = *(LevelInfoStruct **)0x106D3AEC;
    #endif
}

void setPlayerMgrInstance() {
    #ifdef Cemu
    PlayerMgrInst = *(PlayerMgr **)0x101e6994;
    #else
    PlayerMgrInst = *(PlayerMgr **)0x106E8B94;
    #endif
}

void setPhysCollMgrInstance() {
    #ifdef Cemu
    PhysicsCollisionMgr = *(void **)0x101c9360;
    #else
    PhysicsCollisionMgr = *(void **)0x106CB560;
    #endif
}

void setDrawerInstance() {
    #ifdef Cemu
    Drawer = *(void **)0x101d2d88;
    #else
    Drawer = *(void **)0x106D4F88;
    #endif
}

void setResLoaderInstance() {
    #ifdef Cemu
    ResLoader = *(void **)0x101d2d50;
    #else
    ResLoader = *(void **)0x106D4F50;
    #endif
}
