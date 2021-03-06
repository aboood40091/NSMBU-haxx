#pragma once

#include "types.h"

namespace sead {

struct Color4f
{
    f32 r;
    f32 g;
    f32 b;
    f32 a;

    inline Color4f(f32 v = 0.0f) :
        r(v), g(v), b(v), a(v) { }
    inline Color4f(f32 r, f32 g, f32 b, f32 a) :
        r(r), g(g), b(b), a(a) { }

    void set(f32 r, f32 g, f32 b, f32 a) { this->r = r; this->g = g; this->b = b; this->a = a; };
};

}
