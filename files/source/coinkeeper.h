#pragma once

#include <actor/base.h>
#include <model.h>

class CoinKeeper : public Base
{
    SEAD_RTTI_OVERRIDE(CoinKeeper, Base)

public:
    CoinKeeper(const ActorBuildInfo* buildInfo)
        : Base(buildInfo)
        , yCoin(nullptr)
        , bCoin(nullptr)
        , coinHeap1(nullptr)
        , coinHeap2(nullptr)
        , coinHeap3(nullptr)
        , coinHeap4(nullptr)
        , shpBlockBuffer1(nullptr)
        , shpBlockBuffer2(nullptr)
        , shpBlockBuffer3(nullptr)
        , shpBlockBuffer4(nullptr)
    {
    }

    virtual ~CoinKeeper()
    {
    }

    static Base* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDelete() override;

private:
    void drawAt(Model& model, const Vec3& pos);

public:
    void drawYAt(const Vec3& pos)
    {
        drawAt(*yCoin, pos);
    }

    void drawBAt(const Vec3& pos)
    {
        drawAt(*bCoin, pos);
    }

    static CoinKeeper* sInstance;

private:
    Model* yCoin;
    Model* bCoin;

    union
    {
        struct
        {
            sead::Heap* coinHeap1;
            sead::Heap* coinHeap2;
            sead::Heap* coinHeap3;
            sead::Heap* coinHeap4;
        };
        sead::Heap* coinHeaps[4];
    };

    union
    {
        struct
        {
            nw::g3d::ShpBlock* shpBlockBuffer1;
            nw::g3d::ShpBlock* shpBlockBuffer2;
            nw::g3d::ShpBlock* shpBlockBuffer3;
            nw::g3d::ShpBlock* shpBlockBuffer4;
        };
        nw::g3d::ShpBlock* shpBlockBuffers[4];
    };

    Mtx34 mtxRT;
};
