#include "coinkeeper.h"

#include <agl/lyr/aglRenderer.h>
#include <heap/seadHeapMgr.h>
#include <prim/seadEndian.h>

#include <actormgr.h>
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
    // Abort if already created
    if (CoinKeeper::sInstance != nullptr)
        return 2;

    // Create Model instances
    sead::Heap* heap = sead::HeapMgr::instance()->getCurrentHeap();
    yCoin = ResArchiveMgr::instance->get("obj_coin")->getModel("obj_coin",      1, 1, 1, 1, 0, 0, heap);
    bCoin = ResArchiveMgr::instance->get("obj_coin")->getModel("obj_coin_blue", 1, 1, 1, 1, 0, 0, heap);

    // Create additional heaps for Shp Uniform Block arrays (Limit of 1568 coin tiles at once)
    coinHeap1 = sead::HeapMgr::instance()->getCurrentHeap();
    ActorMgr::instance->createAdditionalHeap(&coinHeap2);
    ActorMgr::instance->createAdditionalHeap(&coinHeap3);
    ActorMgr::instance->createAdditionalHeap(&coinHeap4);

    // Allocate the Shp Uniform Block arrays
    shpBlockBuffer1 = (nw::g3d::ShpBlock*)(new (coinHeap1, 0x100) u8[0x100 * 392u]);
    shpBlockBuffer2 = (nw::g3d::ShpBlock*)(new (coinHeap2, 0x100) u8[0x100 * 392u]);
    shpBlockBuffer3 = (nw::g3d::ShpBlock*)(new (coinHeap3, 0x100) u8[0x100 * 392u]);
    shpBlockBuffer4 = (nw::g3d::ShpBlock*)(new (coinHeap4, 0x100) u8[0x100 * 392u]);

    // Create Rotation Matrix
    mtxRT.makeRzxyIdx(0, CoinTileRenderer::instance()->coinYRot, 0);

    CoinKeeper::sInstance = this;
    return 1;
}

u32 CoinKeeper::onExecute()
{
    // Update Rotation Matrix
    mtxRT.makeRzxyIdx(0, CoinTileRenderer::instance()->coinYRot, 0);
    return 1;
}

u32 CoinKeeper::onDelete()
{
    if (CoinKeeper::sInstance == this)
    {
        delete[] (u8*)shpBlockBuffer1; shpBlockBuffer1 = nullptr;
        delete[] (u8*)shpBlockBuffer2; shpBlockBuffer2 = nullptr;
        delete[] (u8*)shpBlockBuffer3; shpBlockBuffer3 = nullptr;
        delete[] (u8*)shpBlockBuffer4; shpBlockBuffer4 = nullptr;

        CoinKeeper::sInstance = nullptr;
    }

    return 1;
}

void CoinKeeper::drawAt(Model& model, const Vec3& pos)
{
    // TODO: This currently has one known bug:
    // This replaces BgRenderer's graphics context. Therefore, whenever a coin is rendered, all tileset tiles appear opaque.

    // Set position for World Matrix
    mtxRT.setTranslation(pos);
    // Update the Model
    model.setMtx(mtxRT);
    model.updateModel();
    model.calc();

    ObjLayer* layer = sead::DynamicCast<ObjLayer>(agl::lyr::Renderer::instance()->layers[9]);
    u32 layerIdx = layer->parentRendererLayerIdx;
    ObjLayerRenderer* renderer = layer->parentRenderer;
    ObjLayerRenderInfo& layerRenderInfo = renderer->layerRenderInfos[layerIdx];

    // Update GPU Buffers for the model

    //model.updateView(layerIdx, layerRenderInfo.viewMtx, layerRenderInfo.projMtx, renderer); //<--- does nothing
    model.calcGPU(layerIdx, layerRenderInfo.viewMtx, layerRenderInfo.projMtx, renderer);

    // Replace the Shp Uniform Block pointer to allow for rendering
    // the same Model instance with different transformations in the same frame

    nw::g3d::ModelObj& modelObj = model.modelObj;
    //SEAD_ASSERT(modelObj.numShapes == 1);

    nw::g3d::ShapeObj& shapeObj = modelObj.shapes[0];
    //SEAD_ASSERT(shapeObj.flags & 2); // Little-endian
    //SEAD_ASSERT(!shapeObj.multiView);
    //SEAD_ASSERT(shapeObj.numShpBlocks == 1);
    //SEAD_ASSERT(shapeObj.numBuffersPerShpBlock == 1);

    nw::g3d::fnd::GfxBuffer& g3d_block = shapeObj.shpBlocks[0];
    // Save the original uniform block ptr
    void* g3d_block_data = g3d_block.GetData();

    // Determine free array and index within the coin limit
    static u32 counter = 0u;
    u32 buffer = counter / 392u;
    u32 idx = counter % 392u;

    // Set the uniform block data

    nw::g3d::ShpBlock& block = shpBlockBuffers[buffer][idx];
    block.weightNum = 0;

    // TODO: Optimize this

    for (u32 i = 0; i < 3; i++)
        for (u32 j = 0; j < 4; j++)
            block.shpMtx.m[i][j] = sead::Endian::swap(mtxRT.m[i][j]);

    g3d_block.SetData(&block, sizeof(nw::g3d::ShpBlock), 1);
    // Flush the Data
    g3d_block.DCFlush();

    // Draw

    model.drawOpa(layerIdx, layerRenderInfo.viewMtx, layerRenderInfo.projMtx, renderer);
    //model.drawXlu(layerIdx, layerRenderInfo.viewMtx, layerRenderInfo.projMtx, renderer); //<--- probably not needed

    // Restore the original uniform block ptr after drawing (probably not needed)
    g3d_block.SetData(g3d_block_data, sizeof(nw::g3d::ShpBlock), 1);

    counter = (counter + 1u) % 1568u;
}
