#pragma once

#include <coreinit/mutex.h>
#include "heap.h"

namespace sead {
    class CriticalSection : public sead::IDisposer {
    public:
        OSMutex mutex;
    };
};
