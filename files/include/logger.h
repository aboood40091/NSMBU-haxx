#pragma once
#define log_printf(FMT, ARGS...)  ((void (*)(const char *format, ...))(*(unsigned int *)(DATA_ADDR + 0x20000)))(FMT, ## ARGS);
