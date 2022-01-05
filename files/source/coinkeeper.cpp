#include "coinkeeper.h"

#include <agl/lyr/aglRenderer.h>
#include <heap/seadHeapMgr.h>

#include <cointilerenderer.h>
#include <objlayerrenderer.h>
#include <resarchive.h>

const ActorInfo CoinKeeperActorInfo = { Vec2i(0, 0), Vec2i(0, 0), Vec2i(0, 0), 0, 0, 0, 0, ActorInfo::FlagIgnoreSpawnRange };
const Profile CoinKeeperProfile(&CoinKeeper::build, ProfileId::CoinKeeper, "CoinKeeper", &CoinKeeperActorInfo, 0);
PROFILE_RESOURCES(ProfileId::CoinKeeper, "obj_coin");

CoinKeeper* CoinKeeper::sInstance = nullptr;

Base* CoinKeeper::build(const ActorBuildInfo* buildInfo)
{
    return new CoinKeeper(buildInfo);
}

u32 CoinKeeper::onCreate()
{
    if (CoinKeeper::sInstance != nullptr)
        return 2;

    sead::Heap* heap = sead::HeapMgr::instance()->getCurrentHeap();
    yCoin = ResArchiveMgr::instance->get("obj_coin")->getModel("obj_coin",      1, 1, 1, 1, 0, false, heap);
    bCoin = ResArchiveMgr::instance->get("obj_coin")->getModel("obj_coin_blue", 1, 1, 1, 1, 0, false, heap);

    mtxRT.makeRzxyIdx(0, CoinTileRenderer::instance()->coinYRot, 0);

    CoinKeeper::sInstance = this;
    return 1;
}

u32 CoinKeeper::onExecute()
{
    mtxRT.makeRzxyIdx(0, CoinTileRenderer::instance()->coinYRot, 0);
    return 1;
}

u32 CoinKeeper::onDelete()
{
    if (CoinKeeper::sInstance == this)
        CoinKeeper::sInstance = nullptr;

    return 1;
}

void CoinKeeper::drawAt(Model& model, const Vec3& pos)
{
    // TODO: This currently has two bugs
    // 1. This replaces BgRenderer's graphics context. Therefore, whenever a coin is rendered, all tileset tiles appear opaque.
    // 2. Only one coin can be drawn at a time. Reason unknown.

    mtxRT.setTranslation(pos);
    model.setMtx(mtxRT);
    model.updateModel();
    model.calc();

    ObjLayer* layer = sead::DynamicCast<ObjLayer>(agl::lyr::Renderer::instance()->layers[9]);
    u32 layerIdx = layer->parentRendererLayerIdx;

    ObjLayerRenderer* renderer = layer->parentRenderer;
    ObjLayerRenderInfo& layerRenderInfo = renderer->layerRenderInfos[layerIdx];

    //model.updateView(layerIdx, layerRenderInfo.viewMtx, layerRenderInfo.projMtx, renderer); //<--- does nothing
    model.calcGPU(layerIdx, layerRenderInfo.viewMtx, layerRenderInfo.projMtx, renderer);
    model.drawOpa(layerIdx, layerRenderInfo.viewMtx, layerRenderInfo.projMtx, renderer);
    //model.drawXlu(layerIdx, layerRenderInfo.viewMtx, layerRenderInfo.projMtx, renderer); //<--- probably not needed
}
