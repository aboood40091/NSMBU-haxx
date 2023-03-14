#ifndef EFT_RESOURCE_H_
#define EFT_RESOURCE_H_

#include <nw/eft/eft_typeDef.h>
#include <nw/eft/eft_Data.h>
#include <nw/eft/eft_System.h>
#include <nw/eft/eft_Primitive.h>

namespace nw { namespace eft {

class Heap;
class ParticleShader;
class Primitive;
class System;

struct ResourceBind
{
    ResourceBind() { source = NULL; }

    EmitterSetData*         source;
    s32                     resourceID;
    s32                     emitterSetID;
    const char*             saveName;
    s32                     saveNumEmitter;
    EmitterTblData*         saveTbl;
    u32                     saveUserData;

    ParticleShader**        shaderArray;
    u32                     shaderNum;

    Primitive**             primitiveArray;
    u32                     primitiveNum;
};

struct ResourceEmitterSet
{
    EmitterSetData*     setData;
    EmitterTblData*     tblData;
    s32                 numEmitter;
    u32                 userData;

    EmitterSetData*     setDataROM;
    EmitterTblData*     tblDataROM;
    s32                 numEmitterROM;
    u32                 userDataROM;

    const char*         setName;
    bool                isShowDetail;

    ParticleShader**    shaderArray;
    u32                 shaderNum;

    Primitive**         primitiveArray;
    u32                 primitiveNum;
};
static_assert(sizeof(ResourceEmitterSet) == 0x38, "nw::eft::ResourceEmitterSet size mismatch");

class Resource
{
public:
    enum
    {
        cInvalidID = -1
    };

public:
    Resource() { }
    Resource(Heap* heap, void* bin, s32 resourceID, System* eftSys);
    virtual ~Resource(); // deleted

    const char* GetProjectName() const
    {
        return &mNameTbl[mHeader->namePos];
    }

    Heap* GetHeap() const
    {
        return mHeap;
    }

    s32 GetNumEmitterSet() const
    {
        return mHeader->numEmitterSet;
    }

    s32 GetNumEmitter(s32 emitterSetID) const
    {
        return mResEmitterSet[emitterSetID].numEmitter;
    }

    const CommonEmitterData* GetEmitterData(s32 emitterSetID, s32 emitterID) const
    {
        return mResEmitterSet[emitterSetID].tblData[emitterID].emitter;
    }

    const EmitterSetData* GetEmitterSetData(s32 emitterSetID) const
    {
        return mResEmitterSet[emitterSetID].setData;
    }

    u32 GetUserData(s32 emitterSetID) const
    {
        return mResEmitterSet[emitterSetID].userData;
    }

    u8 GetUserDataNum1(s32 emitterSetID) const
    {
        return mResEmitterSet[emitterSetID].userData & 0xff;
    }

    u8 GetUserDataNum2(s32 emitterSetID) const
    {
        return mResEmitterSet[emitterSetID].userData >> 8 & 0xff;
    }

    u16 GetUserDataBit(s32 emitterSetID) const
    {
        return mResEmitterSet[emitterSetID].userData >> 16;
    }

    const char* GetEmitterName(s32 emitterSetID, s32 emitterID) const
    {
        return  mResEmitterSet[emitterSetID].tblData[emitterID].emitter->name;
    }

    ResourceEmitterSet* GetEmitterSetResource(s32 emitterSetID) const
    {
        return &mResEmitterSet[emitterSetID];
    }

    char* GetEmitterSetNameTable() const
    {
        return mNameTbl;
    }

    s32 GetNumEmitterROM(s32 emitterSetID) const
    {
        return mResEmitterSet[emitterSetID].numEmitterROM;
    }

    const CommonEmitterData* GetEmitterDataROM(s32 emitterSetID, s32 emitterID) const
    {
        return mResEmitterSet[emitterSetID].tblDataROM[emitterID].emitter;
    }

    const EmitterSetData* GetEmitterSetDataROM(s32 emitterSetID) const
    {
        return mResEmitterSet[emitterSetID].setDataROM;
    }

    u32 GetUserDataROM(s32 emitterSetID) const
    {
        return mResEmitterSet[emitterSetID].userDataROM;
    }

    const char* GetEmitterNameROM(s32 emitterSetID, s32 emitterID) const
    {
        return mResEmitterSet[emitterSetID].tblDataROM[emitterID].emitter->name;
    }

    const char* GetEmitterSetName(s32 emitterSetID) const
    {
        return mResEmitterSet[emitterSetID].setName;
    }

    s32 SearchEmitterSetID(const char* name) const;
    s32 SearchEmitterID(const char *setName, const char *emitterName) const;
    s32 SearchEmitterID(s32 emitterSetID, const char *emitterName) const;
    s32 SearchEmitterID(s32 emitterSetID, const char *emitterName, u32 emitterIdx) const;

    void Initialize(Heap* heap, void* bin, s32 resourceID, System* eftSys);
    void Finalize(Heap* heap);

private:
    static void CreateFtexbTextureHandle(Heap* heap, void* texture_data, TextureRes& texRes);
    static void CreateOriginalTextureHandle(Heap* heap, void* texture_data, TextureRes& texRes);
    static void DeleteTextureHandle(Heap* heap, TextureRes& texRes, bool isOriginalTexture);

public:
    bool BindResource(s32 targetSetID, ResourceBind* bind, EmitterTblData* newTbl, s32 newNumEmitter, const char* newSetName, u32 newUserData, u32 newShaderNum, ParticleShader** newShaderArray, u32 newPrimitiveNum, Primitive** newPrimitiveArray);
    bool UnbindResource(ResourceBind* bind, bool isReBind, bool isKill);

    ParticleShader* GetShader(u32 index);
    ParticleShader* GetShader(s32 emitterSetID, u32 index);
    ParticleShader* GetShader(const VertexShaderKey* vertexKey, const FragmentShaderKey* fragmentKey);
    ParticleShader* GetShader(s32 emitterSetID, const VertexShaderKey* vertexKey, const FragmentShaderKey* fragmentKey);

    u32 GetShaderNum() const
    {
        return mShaderNum;
    }

    ParticleShader** GetShaderArray() const
    {
        return mShader;
    }

    u32 GetPrimitiveNum() const
    {
        return mPrimitiveNum;
    }

    Primitive** GetPrimitiveArray() const
    {
        return mPrimitive;
    }

    Primitive* GetPrimitive(s32 emitterSetID, u32 index)
    {
        u32 primitiveNum = mResEmitterSet[emitterSetID].primitiveNum;
        Primitive** primitiveArray = mResEmitterSet[emitterSetID].primitiveArray;

        for (u32 i = 0; i < primitiveNum; i++)
            if (primitiveArray[i] && index == i)
                return primitiveArray[i];

        return NULL;
    }

private:
    System*                     mSystem;
    s32                         mResourceID;
    HeaderData*                 mHeader;
    char*                       mNameTbl;
    const void*                 mTextureTbl;
    ResourceEmitterSet*         mResEmitterSet;
    Heap*                       mHeap;
    ParticleShader**            mShader;
    u32                         mShaderNum;
    Primitive**                 mPrimitive;
    u32                         mPrimitiveNum;
};
static_assert(sizeof(Resource) == 0x30, "nw::eft::Resource size mismatch");

} } // namespace nw::eft

#endif // EFT_RESOURCE_H_
