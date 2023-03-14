#ifndef NW_TYPES_H_
#define NW_TYPES_H_

#include <cstddef>

#define NW_PLATFORM_CAFE
#define NW_RELEASE

#define NW_INLINE inline
#define NW_FORCE_INLINE     __attribute__((always_inline)) inline

#define NW_CONFIG_USE_STATIC
#define NW_TABLE_FIELD static const

#endif // NW_TYPES_H_
