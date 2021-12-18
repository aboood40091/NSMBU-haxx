#pragma once

#include <cstddef>

// Workarounds to match newer standards
#define nullptr NULL
#define override
#define forceinline __attribute__((always_inline))

#ifndef cafe
#define cafe
#endif // cafe

#ifndef static_assert

// https://stackoverflow.com/a/1597129
#define TOKENPASTE(x, y) x ## y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)

#define static_assert(condition, ...) typedef int TOKENPASTE2(static_assert_, __LINE__)[(condition) ? 1 : -1]

#endif // static_assert

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;

typedef signed char         s8;
typedef signed short        s16;
typedef signed int          s32;
typedef signed long long    s64;

typedef float               f32;
typedef double              f64;

typedef unsigned int        size_t;
typedef signed int          ssize_t;

typedef unsigned int        uintptr_t;
typedef signed int          intptr_t;

typedef wchar_t             char16;

typedef int                 BOOL;

enum Direction
{
    RIGHT = 0,
    LEFT  = 1,
    UP    = 2,
    DOWN  = 3
};
