#pragma once

#include "model.h"

class Renderer
{
public:
    static Renderer* instance;

    void drawModel(Model* model);
    void drawModel(BasicModel* model);
    void drawTile(u16 tile, const Vec3& position, const u32& rotation, const Vec3& scale);

    void setTargetLayer(RenderObjLayerBase* layer, u32 default_);
    void resetTargetLayer();
};
