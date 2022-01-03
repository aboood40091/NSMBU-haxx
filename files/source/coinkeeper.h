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

    Mtx34 mtxRT;
};
