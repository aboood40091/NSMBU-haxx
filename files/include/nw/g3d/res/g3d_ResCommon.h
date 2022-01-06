#ifndef G3D_RES_COMMON_H_
#define G3D_RES_COMMON_H_

#include <types.h>

namespace nw { namespace g3d { namespace res {

template <typename T>
T* OffsetToPtr(s32* pOffset)
{
    if (*pOffset == 0)
        return NULL;

    return (T*)((uintptr_t)pOffset + *pOffset);
}

template <typename T>
const T* OffsetToPtr(const s32* pOffset)
{
    if (*pOffset == 0)
        return NULL;

    return (const T*)((uintptr_t)pOffset + *pOffset);
}

struct BinaryFileHeader
{
    u8 signature[4];
    u8 version[4];
    u16 byteOrder;
    u16 headerSize;
    u32 fileSize;
};

} } }

#endif // G3D_RES_COMMON_H_
