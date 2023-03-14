#pragma once

#include <agl/lyr/aglLayer.h>

class RenderObjBase
{
    SEAD_RTTI_BASE(RenderObjBase)

public:
    virtual void calc() = 0;
};

class Layer : public agl::lyr::Layer // size: 0x420
{
    SEAD_RTTI_OVERRIDE(Layer, agl::lyr::Layer)

public:
    Layer();
    virtual ~Layer();

    void preDrawImpl(const agl::lyr::RenderInfo& render_info) const override;
    void postDrawImpl(const agl::lyr::RenderInfo& render_info) const override;

    // ...

    u8 _41C[0x420 - 0x41C];
};
