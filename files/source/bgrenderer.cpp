#include <bgrenderer.h>
#include "coinkeeper.h"
#include <tiles.h>

void BgRenderer::scheduleTileForDrawingHaxx(u32 layer, const Vec3& position, u16 tile)
{
    if (CoinKeeper::sInstance != nullptr)
    {
        switch (tile)
        {
        case TileId::Coin:
            CoinKeeper::sInstance->drawYAt(Vec3(position.x + 8.0f, -position.y - 8.0f, position.z + 10000.0f));
            return;
        case TileId::BlueCoin_CoreCoin:
            CoinKeeper::sInstance->drawBAt(Vec3(position.x + 8.0f, -position.y - 8.0f, position.z + 10000.0f));
            return;
        }
    }

    scheduleTileForDrawing(layer, position, tile);
}
