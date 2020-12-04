#include "types.h"

typedef void (*InitFunc)();
extern "C" InitFunc _ctors[];

void callCtors()
{
    static bool initialized = false;
    if (initialized)
        return;

    initialized = true;
    for (s32 i = 0; _ctors[i]; i++)
        (*_ctors[i])();
}
