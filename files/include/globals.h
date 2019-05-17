#pragma once

#include <sead/string.h>
#include <level.h>

extern LevelData *Level;
extern LevelInfoStruct *LevelInfo;

class PlayerMgr;
extern PlayerMgr *PlayerMgrInst;

extern void *PhysicsCollisionMgr;
extern void *Drawer;
extern void *ResLoader;

extern char fileCounts[];
extern const sead::String *fileLists[];

void setLevelInstances();
void setPlayerMgrInstance();
void setPhysCollMgrInstance();
void setDrawerInstance();
void setResLoaderInstance();
