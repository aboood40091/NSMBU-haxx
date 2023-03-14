#pragma once

#include <heap/seadDisposer.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>

#include "nw/g3d.h"

class ModelNW;

class ModelResource : public sead::IDisposer
{
public:
    // boundingType: 0 = no bounding, 1 = bounding sphere, 2 = bounding box
    ModelNW* getModel(const sead::SafeString& identifier, u32 numView, u32 numSklAnims, u32 numTexAnims, u32 numShuAnims, u32 numVisAnims, u32 numShaAnims, u32 boundingType, sead::Heap* heap);
    ModelNW* getModel(const sead::SafeString& identifier, u32 numSklAnims, u32 numTexAnims, u32 numShuAnims, u32 numVisAnims, u32 numShaAnims, u32 boundingType, sead::Heap* heap);

    nw::g3d::res::ResFile* res;
};

class ModelResourceMgr
{
public:
    static ModelResourceMgr* instance;

    ModelResource* get(const sead::SafeString& identifier);
};

bool loadActorModelResource(const sead::SafeString& name, sead::Heap* heap = nullptr);
