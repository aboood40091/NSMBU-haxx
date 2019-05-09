#pragma once

#include "list.h"
#include "string.h"

namespace sead {
    class Heap;

    class IDisposer {
    public:
        IDisposer();

        virtual ~IDisposer();

        sead::Heap* heap;
        sead::ListNode listNode;
    };
};

#include "critical.h"

namespace sead {
    class Heap : public IDisposer {
    public:
        sead::String name;
        unsigned int addr;
        unsigned int size;
        Heap *parent;
        sead::ListImpl children;
        unsigned int _34;
        unsigned int _38;
        sead::ListImpl disposers;
        unsigned int direction;
        sead::CriticalSection mutex;
        unsigned int flags;
        void *vtable;
    };
};
