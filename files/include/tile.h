#pragma once

#include <vec.h>

#ifdef __cplusplus
extern "C" {
#endif

void drawTile(void* drawer, unsigned int tileNumber, Vec3 *pos, unsigned int *rotation, Vec3 *scale);
unsigned short *getTilePtr(unsigned short x, unsigned short y, unsigned char layer, unsigned int *dstBlockIdx);

#ifdef __cplusplus
}
#endif
