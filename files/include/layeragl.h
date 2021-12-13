#pragma once

#include "agl/layer.h"

class LayerAgl : public agl::lyr::Layer // size: 0x420
{
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

    // ...

    u8 _41C[0x420 - 0x41C];
};
