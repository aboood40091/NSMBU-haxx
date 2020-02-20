#pragma once
#ifndef Cemu
#define log_printf(FMT, ARGS...)  ((void (*)(const char *format, ...))(*(unsigned int *)(DATA_ADDR - 4)))(FMT, ## ARGS);
#else
#define log_printf(x, ...)
#endif
