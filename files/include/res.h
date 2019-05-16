#pragma once

#include <sead/string.h>
#include <model.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

ResArchive *getResArchive(void *resLoader, sead::String filename);

#ifdef __cplusplus
}
#endif // __cplusplus
