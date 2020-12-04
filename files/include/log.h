#pragma once

#ifdef Cemu
#define LOG(FMT, ARGS...)
#else
#define LOG(FMT, ARGS...)  ((void (*)(const char *format, ...))(*(unsigned int *)(DATA_ADDR - 4)))(FMT, ## ARGS);
#endif
