#include <log.h>
#include <stdarg.h>
#include <stdio.h>

#ifdef NDEBUG
LOG_LEVEL g_MinLogLevel = LOG_LEVEL_I;
#else
LOG_LEVEL g_MinLogLevel = LOG_LEVEL_D;
#endif

void SetMinLogLevel(LOG_LEVEL level) { g_MinLogLevel = level; }

void _log(unsigned int level, const char* file, unsigned int line,
          const char* func, const char* fmt, ...) {
    static const char levels[] = "DIWE";
    va_list args;

    va_start(args, fmt);
    if (level >= g_MinLogLevel && level < LEN(levels)) {
        char buf[1024];

        int n = vsnprintf(buf, sizeof(buf), fmt, args);
        if (n >= sizeof(buf)) {
            WARNF("cannot write '%d' characters in '%s'", n, NAMEOF(buf));
        }

        fprintf(stderr, "[%c][%s:%d][%s] %s\n", levels[level], file, line, func,
                buf);
    }
    va_end(args);
}
