#ifndef __LOGGER_H_
#define __LOGGER_H_

#ifdef __cplusplus
extern "C" {
#endif

#define log_printf(FMT, ARGS...)  ((void (*)(const char *format, ...))(*(unsigned int *)(DATA_ADDR + 0x20000)))(FMT, ## ARGS);

#ifdef __cplusplus
}
#endif

#endif
