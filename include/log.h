#ifndef LOG_H
#define LOG_H

#include "common.h"

typedef enum {
    LOG_LEVEL_D,
    LOG_LEVEL_I,
    LOG_LEVEL_W,
    LOG_LEVEL_E,
} LOG_LEVEL;

#define NAMEOF(var) #var
#define NOT_IMPLEMENTED WARNF("not implemented")

#ifndef NO_LOGS

#define DEBUGF(...) _log(LOG_LEVEL_D, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define INFOF(...) _log(LOG_LEVEL_I, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define WARNF(...) _log(LOG_LEVEL_W, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define ERRORF(...) _log(LOG_LEVEL_E, __FILE__, __LINE__, __func__, __VA_ARGS__)

void SetMinLogLevel(LOG_LEVEL level);
void _log(unsigned int level, const char* file, unsigned int line,
          const char* func, const char* fmt, ...);

#else

#define DEBUGF(fmt, ...)
#define INFOF(fmt, ...)
#define WARNF(fmt, ...)
#define ERRORF(fmt, ...)

#endif

#endif