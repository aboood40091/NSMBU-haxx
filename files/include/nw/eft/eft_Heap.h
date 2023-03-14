#ifndef EFT_HEAP_H_
#define EFT_HEAP_H_

#include <nw/eft/eft_typeDef.h>

namespace nw { namespace eft {

class Heap
{
public:
    Heap() { }
    virtual ~Heap() { }

    enum Alignment
    {
        EFT_HEAP_DEAFULT_ALIGNMENT = 128
    };

    virtual void* Alloc(u32 size, s32 alignment = EFT_HEAP_DEAFULT_ALIGNMENT) = 0;
    virtual void Free(void* ptr) = 0;
};
static_assert(sizeof(Heap) == 4, "nw::eft::Heap size mismatch");

} } // namespace nw::eft

#endif // EFT_HEAP_H_
