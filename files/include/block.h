#pragma once

/*
    Classes related to blocks.
    From Newer U.
*/

#include <sead/runtime.h>
#include <actor.h>
#include <collider.h>
#include <movement.h>
#include <state.h>
#include <vec.h>

class BlockCoinRelatedBase : public StateActor {
public:
    enum Content {
        FireMushroom = 0,
        MiniMushroom = 1,
        LifeMushroom = 2,
        Mushroom = 3,
        FireFlower = 4,
        IceMushroom = 5,
        PenguinMushroom = 6,
        PropellerMushroom = 7,
        Star = 8,
        ContinuousStar = 9,
        SquirrelMushroom = 10,
        LifeMoon = 11,
        Coin = 12,
        MultiCoin = 13,
        Vine = 15,
        Yoshi = 16,
        Spring = 17,
        MushroomIfSmall = 19,
        Nothing = 21
    };

    char _17C8[0x10];
    RectCollider solidColl;
    Vec2 _1A68;
    Vec2 _1A70;
    float _1A78;
    float _1A7C;
    float _1A80;
    char _1A84[0x1AB8 - 0x1A84];
    unsigned int content;
    unsigned int hitPlayerId;
    unsigned int spawnDirection;
    char _1AC4[0x1B28 - 0x1AC4];

    void spawnPortableSpring();
    void spawnYoshiEgg(bool multi);
    void spawnVine();
    void spawnPowerup(Vec3 *pos, unsigned int, unsigned int, bool spawnAsChild);
    void spawnMultiPowerup(Vec3 *pos, unsigned int, unsigned int, bool spawnAsChild);

    BlockCoinRelatedBase(ActorBuildInfo *);

    bool checkDerivedRuntimeTypeInfo(sead::RuntimeTypeInfo::Interface const *) const;
    ~BlockCoinRelatedBase();

    virtual void vf18C(); //nullsub
    virtual void vf194(); //nullsub
    virtual void vf19C(); //nullsub
    virtual void vf1A4(); //nullsub
    virtual void spawnItemUp(); //nullsub
    virtual void vf1B4(); //nullsub
    virtual void vf1BC(); //nullsub
    virtual void spawnItemDown(); //nullsub
    virtual void vf1CC(); //nullsub
    virtual void vf1D4(bool);
    virtual unsigned int vf1DC(); //returns 0
    virtual void spawnCoinShower();
    virtual void vf1EC(); //nullsub, only exists in NSLU
    virtual void beginState_BumpUp();
    virtual void executeState_BumpUp();
    virtual void endState_BumpUp();
    virtual void beginState_BlockCoinRelatedState1();
    virtual void executeState_BlockCoinRelatedState1();
    virtual void endState_BlockCoinRelatedState1();
    virtual void beginState_BumpDown();
    virtual void executeState_BumpDown();
    virtual void endState_BumpDown();
    virtual void beginState_BlockCoinRelatedState2(); //Counts down a timer
    virtual void executeState_BlockCoinRelatedState2(); //6 frames
    virtual void endState_BlockCoinRelatedState2();
    virtual void beginState_BumpUp2();
    virtual void executeState_BumpUp2();
    virtual void endState_BumpUp2();
    virtual void beginState_BumpDown2();
    virtual void executeState_BumpDown2();
    virtual void endState_BumpDown2();
    virtual void beginState_BlockCoinRelatedState3(); //Counts down a timer
    virtual void executeState_BlockCoinRelatedState3(); //6 frames
    virtual void endState_BlockCoinRelatedState3();

    static State<BlockCoinRelatedBase> StateID_BumpUp;
    static State<BlockCoinRelatedBase> StateID_BlockCoinRelatedState1;
    static State<BlockCoinRelatedBase> StateID_BumpDown;
    static State<BlockCoinRelatedBase> StateID_BlockCoinRelatedState2;
    static State<BlockCoinRelatedBase> StateID_BumpUp2;
    static State<BlockCoinRelatedBase> StateID_BumpDown2;
    static State<BlockCoinRelatedBase> StateID_BlockCoinRelatedState3;
};

class BlockCoinBase : public BlockCoinRelatedBase {
public:
    char _1B28[0xC];
    Vec3 _1B34;
    MovementHandler mover;
    char _1C38[0x1CA8 - 0x1C38];

    BlockCoinBase(ActorBuildInfo *);

    bool checkDerivedRuntimeTypeInfo(sead::RuntimeTypeInfo::Interface const *) const;
    ~BlockCoinBase();

    void spawnItemUp();
    void spawnItemDown();
    unsigned int vf1DC();

    virtual void vf29C(); //nullsub
    virtual void setTileFlag();
    virtual unsigned int vf2AC(); //returns 0
    virtual void vf2B4(); //nullsub
    virtual void vf2BC(); //nullsub
    virtual bool vf2C4(); //checks state stuff
    virtual void vf2CC();
};

class CoinBase : public BlockCoinBase {
public:
    class CoinYoshiEatData { //: public YoshiEatData { // TODO
        char _0[0x24];
        CoinBase *owner;
    };

    unsigned int _1CA8;
    Vec2 _1CAC;
    Vec2 _1CB4;
    float _1CBC;
    unsigned int _1CC0;
    unsigned short _1CC4;
    unsigned int _1CC8;
    unsigned int _1CCC;
    unsigned int _1CD0;
    unsigned int _1CD4;
    unsigned int _1CD8;
    char _1CDC;
    char _1CDD;
    char _1CDE;
    char _1CDF;
    char _1CE0;
    char _1CE1;
    char _1CE2;
    char _1CE3;
    char _1CE4;
    float _1CE8;
    float _1CEC;
    unsigned int _1CF0;
    CoinYoshiEatData yoshiEatData;
    char _1D1C;
    char _1D1D;
    char _1D1E;
    unsigned int _1D20;
    float _1D24;
    unsigned int _1D28;
    char _1D2C;

    CoinBase(ActorBuildInfo *);

    void init();
    void initCollider(unsigned int);
    void addCollider();

    bool checkDerivedRuntimeTypeInfo(sead::RuntimeTypeInfo::Interface const *) const;
    ~CoinBase();

    int onExecute();
    int onDraw();

    void splashWater(Vec3 *);
    void splashLava(Vec3 *);
    void splashLavaWave(Vec3 *);
    void splashPoison(Vec3 *);

    void vf11C();
    void vf124(float);
    unsigned int vf12C();
    void vf144(bool);
    unsigned int vf2AC();

    virtual unsigned int vf2D4();
    virtual void initYoshiEatData();
    virtual void vf2E4();
    virtual void vf2EC();
    virtual void vf2F4();
    virtual void vf2FC();
    virtual void vf304();
    virtual void vf30C();

    static State<CoinBase> StateID_Main;
};

class BlockBase : public BlockCoinBase {
public:
    float _1CA8;
    float _1CAC;
    float _1CB0;
    float _1CB4;
    float _1CB8;
    unsigned int _1CBC;
    unsigned int _1CC0;
    char _1CC4;
    char _1CC5;
    char _1CC6;
    unsigned int _1CC8;
    char _1CCC;

    static void otherCollisionCallback1(PhysicsCollider *coll, void *phys, unsigned int);
    static void otherCollisionCallback2(PhysicsCollider *coll, void *phys, unsigned int);
    static void otherCollisionCallback3(PhysicsCollider *coll, void *phys, unsigned int);

    BlockBase(ActorBuildInfo *);

    bool init(bool, bool);

    bool checkDerivedRuntimeTypeInfo(sead::RuntimeTypeInfo::Interface const *) const;
    ~BlockBase();
    int onExecute();
    int onDraw();

    void vf19C();
    void spawnItemUp();
    void spawnItemDown();
    void vf1CC();

    bool vf2C4(); //checks state stuff

    virtual bool vf2D4();
    virtual void vf2DC(); //nullsub
    virtual char getContent();
    virtual void vf2EC();
    virtual void vf2F4(Vec3 *);
    virtual void execute();
    virtual void vf304(); //deletes and something
    virtual void vf30C(); //deletes and something
    virtual void vf314(); //nullsub
    virtual void vf31C(); //nullsub
    virtual void vf324(); //nullsub
    virtual unsigned int vf32C(); //returns 0
    virtual void beginState_Wait();
    virtual void executeState_Wait();
    virtual void endState_Wait();
    virtual void beginState_Used();
    virtual void executeState_Used();
    virtual void endState_Used();

    static State<BlockBase> StateID_Wait;
    static State<BlockBase> StateID_Used;
};
