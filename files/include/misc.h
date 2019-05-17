#pragma once

#include <actor.h>
#include <rect.h>
#include <stdbool.h>

void GetStageActorRect(StageActor *actor, Rect *rect);
bool RectsOverlap(Rect *, Rect *);
