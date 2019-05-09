#pragma once

/*
    Most (if not all) function/class names here
    are custom-defined. (from the Newer U idb)
*/

#include <sead/list.h>
#include <sead/runtime.h>
#include <sead/string.h>
#include <enums.h>
#include <globals.h>
#include <rect.h>
#include <vec.h>

class Profile;
class Actor;

struct ActorBuildInfo {
	unsigned int settings; // Nybbles 5 to 12
	unsigned int settings2; // Nybbles 13 to 20
	unsigned int parentId;
	Profile *profile;
	Vec3 position;
	unsigned int rotation;
	char layer;
	char Nybble3_4;
	char Nybble1_2;
	char _23;
	char movementId; // Nybbles 21 and 22
	char linkId; // Nybbles 23 and 24
	bool initStateFlag; // Sprite block[20]
	char _27; // pad ?
	unsigned int spriteRelated;
};

struct ActorInfo {
	int xoffs;
	int yoffs;
	unsigned int _8;
	unsigned int _C;
	unsigned int _10;
	unsigned int _14;
	unsigned short _18;
	unsigned short _1A;
	unsigned int _1C;
	unsigned short flags;
	unsigned short _22;
};

class Profile {
public:
    Profile(Actor *(ActorBuildInfo *), ActorIDs actorId, const char * name, const ActorInfo * info, unsigned int);

    Actor *(*buildMethod)(ActorBuildInfo *);
    unsigned int profileId;
    ActorInfo *actorInfo;
    char hasLoadedResources;
    char _D[3]; // pad
    unsigned int flags;

    static Profile *get(ActorIDs);
};

class Actor {
public:
    void *heap;
    unsigned int id;
    Profile *profile;
    bool isNotDereferenced;
    bool isSprite;
    bool isCreated;
    bool isDeleted;
    unsigned int settings; // Nybbles 5 to 12
    unsigned int settings2; // Nybbles 13 to 20
    char movementId; // Nybbles 21 and 22
    char linkId; // Nybbles 23 and 24
    char initStateFlag; // Sprite block[20]
    char _1B; // pad
    sead::ListImpl childList;
    sead::ListNode childNode;
    Actor *parent;
    sead::ListNode actorListNode;
    sead::ListNode drawListNode;
    unsigned int flags;

    Actor(ActorBuildInfo *); // Constructor

    virtual bool checkDerivedRuntimeTypeInfo(sead::RuntimeTypeInfo::Interface const *) const;
    virtual void vf14();
    virtual ~Actor(); // Destructor
    virtual int beforeCreate();
    virtual int onCreate();
    virtual void afterCreate(int);
    virtual int beforeExecute();
    virtual int onExecute();
    virtual void afterExecute(int);
    virtual void finalExecute();
    virtual int beforeDraw();
    virtual int onDraw();
    virtual void afterDraw(int);
    virtual int beforeDelete();
    virtual int onDelete();
    virtual void afterDelete(int);

    void removeChild(Actor *);
    ActorIDs getProfileId();
};

class StageActor : public Actor {
public:
    unsigned int direction;
    char playerId;
    char _55;
    char layer;
    char layer2;
    float xSpeed;
    float TargetXSpeed_maybe;
    float fallSpeed;
    float gravity;
    float xAccel;
    Vec3 position;
    Vec3 speed;
    Vec3 maxSpeed;
    Vec3 scale;
    Vec3Ui rotation; // 0x80000000 represents PI rad
    unsigned int _A8;
    unsigned int _AC;
    unsigned int _B0;
    Vec2 posDelta;
    char collider[0x128]; // TODO: Collider class
    Rect rect;
    Vec2 size;
    Rect _1FC;
    char zone;
    char playerType;
    char isActive;
    char isVisible;
    bool noSpriteRespawn;
    char _211;
    char _212;
    char eventID_3_4;
    char eventID_1_2;
    char _215;
    char actorInfoFlags;
    char _217;
    unsigned int bumpDamageTimer;
    unsigned int _21C;
    unsigned int _220;
    unsigned int _224;
    unsigned int _228;
    unsigned int killStreak;
    unsigned int profile0x10;
    Vec3 offset;
    Vec3 position2;
    Vec3 position3;
    Vec3 position4;
    void *yoshiEatData; // TODO: YoshiEatData class
    void *babyYoshiEatData; // TODO: BabyYoshiEatData class
    unsigned int _26C;
    char *spriteSpawnFlags;
    unsigned int _274;
    void *yoshiBubbleData; // TODO: YoshiBubbleData class

    StageActor(ActorBuildInfo *); // Constructor

    virtual void setPlayerId(char);
    virtual void removeColliders();
    virtual void addColliders();
    virtual void *getPhysics(); // TODO: Physics class
    virtual void vfAC();
    virtual unsigned int vfB4();
    virtual void vfBC();
    virtual void vfC4();
    virtual void vfCC();
    virtual void killAtGoal();
    virtual void splashWater(Vec3 *);
    virtual void splashLava(Vec3 *);
    virtual void splashLavaWave(Vec3 *);
    virtual void splashPoison(Vec3 *);
    virtual bool isOffScreen();
    virtual void bumpDamage();

    Direction getDirectionToPlayer(Vec3 *); // TODO: add the rest of functions

    bool checkDerivedRuntimeTypeInfo(sead::RuntimeTypeInfo::Interface const *) const;
    ~StageActor(); // Destructor
    void afterCreate(int);
    int beforeExecute();
    void afterExecute(int);
    int beforeDraw();
};

class SetActorFiles{
public:
    SetActorFiles(ActorIDs id, char count,const sead::String list[]);
};

SetActorFiles::SetActorFiles(ActorIDs id, char count,const sead::String list[]) {
    fileCounts[id] = count;
    fileLists[id] = list;
}
