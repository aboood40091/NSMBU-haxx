#include <misc.h>
#include <stdbool.h>

void GetStageActorRect(StageActor *actor, Rect *rect) {
    // Reverse-engineered from the PhysicsActor class
    // but it should work with any of the StageActor inheritors
    float XPos1;
    float XPos2;
    float YPos1;
    float YPos2;

    XPos1 = actor->position.X - 16.0;
    XPos2 = actor->position.X + 16.0;
    YPos1 = actor->position.Y -  0.0;
    YPos2 = actor->position.Y + 32.0;

    if (XPos2 <= XPos1) {
        rect->right = XPos1;
        rect->left = XPos2;
    }

    else {
        rect->right = XPos2;
        rect->left = XPos1;
    }

    if (YPos2 <= YPos1) {
        rect->bottom = YPos2;
        rect->top = YPos1;
    }

    else {
        rect->bottom = YPos1;
        rect->top = YPos2;
    }
}

bool RectsOverlap(Rect *thisRect, Rect *otherRect) {
    // https://stackoverflow.com/a/31035335
    if (thisRect->left < otherRect->right && thisRect->right > otherRect->left &&
        thisRect->top > otherRect->bottom && thisRect->bottom < otherRect->top)
            return true;

    return false;
}
