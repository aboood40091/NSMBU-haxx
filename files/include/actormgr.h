#pragma once

#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <heap/seadUnitHeap.h>

#include "actor/base.h"

class ActorBuffer
{
public:
    Base* findActorWithId(u32* id);

    sead::Buffer<Base*> buffer;
    u32 usedCount;
    Base** last;
    u32 _10;
    u8 _14;
};

class ActorMgr
{
public:
    /* "addToActive":
       0: add to actorsToCreate
       1: add to activeActors and drawableActors
       else: don't add to any of the lists */
    Base* create(ActorBuildInfo* buildInfo, u32 addToActive);

    void createAdditionalHeap(/* sead::FrameHeap */ sead::Heap** ppHeap);

    static ActorMgr* instance;

    sead::IDisposer disposer;
    sead::UnitHeap* playerUnitHeap;
    sead::UnitHeap* actorUnitHeap;
    u8 deferredActorCreations[0x5970]; // sead::FixedRingBuffer<ActorBuildInfo, 520>
    Base::ActorList actorsToCreate;
    Base::ActorList actorsToDelete;
    Base::ActorList activeActors;
    Base::ActorList drawableActors;
    sead::FixedPtrArray<sead::Heap, 520> deletedActorHeaps;
    sead::FixedPtrArray<Base, 520> finalExecuteList;
    ActorBuffer actors;
    // ...
};
