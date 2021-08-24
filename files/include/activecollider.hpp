#pragma once

#include "actor/actor.h"

inline void
ActiveCollider::getRect(Rect& outRect) const
{
    outRect.setFromCornerAndXY(*(const Vec2*)&owner->position + info.distToCenter - info.distToEdge, 2 * info.distToEdge.x, 2 * info.distToEdge.y);
}

namespace {

static inline bool RectsOverlap(const Rect& a, const Rect& b)
{
    const Vec2& minA = a.getMin(); // a bottom left
    const Vec2& minB = b.getMin(); // b bottom left

    const Vec2& maxA = a.getMax(); // a top righ
    const Vec2& maxB = b.getMax(); // b top right

    // https://stackoverflow.com/a/31035335
    return minA.x < maxB.x && maxA.x > minB.x
        && minA.y < maxB.y && maxA.y > minB.y;
}

}

inline bool
ActiveCollider::collidersOverlap(const ActiveCollider* acSelf, const ActiveCollider* acOther)
{
    Rect thisRect;
    acSelf->getRect(thisRect);

    Rect otherRect;
    acOther->getRect(otherRect);

    return RectsOverlap(thisRect, otherRect);
}
