#ifndef SEAD_NEW_H_
#define SEAD_NEW_H_

#include <cstddef>
#include <new>

#include <basis/seadTypes.h>

namespace sead {

class Heap;

} // namespace sead

void* operator new(size_t size);
void* operator new[](size_t size);

void operator delete(void* ptr);
void operator delete[](void* ptr);

void* operator new(size_t size, sead::Heap* heap, s32 alignment);
void* operator new[](size_t size, sead::Heap* heap, s32 alignment);

#endif // SEAD_NEW_H_
