#pragma once

#include <agl/lyr/aglLayer.h>

class LayerAgl : public agl::lyr::Layer // size: 0x420
{
    SEAD_RTTI_OVERRIDE(LayerAgl, agl::lyr::Layer)

public:
    class Node
    {
        SEAD_RTTI_BASE(Node)

    public:
        virtual void calc() = 0;
    };

public:
    LayerAgl();
    virtual ~LayerAgl();

    void preDrawImpl(const agl::lyr::RenderInfo& render_info) const override;
    void postDrawImpl(const agl::lyr::RenderInfo& render_info) const override;

    // ...

    u8 _41C[0x420 - 0x41C];
};
