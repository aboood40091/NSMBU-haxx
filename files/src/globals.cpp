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
    Level = *(LevelData **)0x106DD248;
    LevelInfo = *(LevelInfoStruct **)0x106D3AEC;
}

void setPlayerMgrInstance() {
    PlayerMgrInst = *(PlayerMgr **)0x106E8B94;
}

void setPhysCollMgrInstance() {
    PhysicsCollisionMgr = *(void **)0x106CB560;
}

void setDrawerInstance() {
    Drawer = *(void **)0x106D4F88;
}

void setResLoaderInstance() {
    ResLoader = *(void **)0x106D4F50;
}
