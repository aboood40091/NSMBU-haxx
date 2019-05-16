#pragma once

namespace sead {
    template <class T>
    class PtrArrayImpl {
    public:
        unsigned int count;
        unsigned int size;
        T **ptrs;
    };

};
