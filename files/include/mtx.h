#pragma once

#include<vec.h>

typedef float Mtx[3][4];

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void calcMatrix(Mtx *, Vec3Ui *, Vec3 *);

#ifdef __cplusplus
}
#endif // __cplusplus
