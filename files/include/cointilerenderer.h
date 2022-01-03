#pragma once

#include <heap/seadDisposer.h>

class CoinTileRenderer : public sead::IDisposer
{
    SEAD_SINGLETON_DISPOSER(CoinTileRenderer)

public:
    CoinTileRenderer();
    virtual ~CoinTileRenderer();
    // ...

    u32 coinYRot;
    // ...
};
