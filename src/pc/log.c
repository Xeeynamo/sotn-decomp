// SPDX-License-Identifier: AGPL-3.0-or-later
#include <log.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// uncomment to disable the logs grouping feature
// #define FORCE_LINEAR_LOGS

#ifdef NDEBUG
LOG_LEVEL g_MinLogLevel = LOG_LEVEL_I;
#else
LOG_LEVEL g_MinLogLevel = LOG_LEVEL_D;
#endif

void SetMinLogLevel(LOG_LEVEL level) { g_MinLogLevel = level; }

typedef unsigned int hash;

typedef struct {
    unsigned short level;
    unsigned short count;
    size_t ttyLine;
    hash hash;
} LogEntry;

#define MAX_LOGS 65536
#define MASTER_SEED 5381

static LogEntry logHistory[MAX_LOGS] = {0};
static size_t ttyLineCount = 1;

hash djb2_hash(hash hash, const char* str) {
    int c;
    while ((c = *str++))
        hash += (hash << 5) + c;
    return hash;
}

static const char levels[] = "DIWE";
static const char* coloured_levels[] = {
    "\033[1;90;m",
    "\033[1;37;m",
    "\033[1;33;m",
    "\033[1;31;m",
};

// WARNING: the whole function is thread-unsafe
void _log(unsigned int level, const char* file, unsigned int line,
          const char* func, const char* fmt, ...) {
    va_list args;

    va_start(args, fmt);
    if (level >= g_MinLogLevel && level < sizeof(levels) - 1) {
        char buf[1024];

        int n = vsnprintf(buf, sizeof(buf), fmt, args);
        if (n >= sizeof(buf)) {
            WARNF("cannot write '%d' characters in '%s'", n, NAMEOF(buf));
            buf[sizeof(buf) - 1] = '\0';
        }

#ifdef FORCE_LINEAR_LOGS
        if (false) {
#else
        if (isatty(fileno(stderr))) {
#endif
            hash altHash = djb2_hash(MASTER_SEED, buf);
            hash logHash = altHash;
            logHash = djb2_hash(logHash, file);
            logHash += (logHash << 5) + line;
            logHash = djb2_hash(logHash, func);

            LogEntry* entry = &logHistory[logHash % MAX_LOGS];
            // check if the collision is real, caused by a small dict or because
            // the entry is just unused
            if (entry->hash == altHash) {
                // duplicate log
                if (++entry->count > 9999) {
                    // adjust the count to show the log keeps being
                    // triggered
                    entry->count = 9000;
                }

                // go back N amount of lines to modify the existing log
                size_t nLinesBack = ttyLineCount - entry->ttyLine;
                while (nLinesBack-- > 0) {
                    fputs("\033[F", stderr);
                }

                // now update the log line, in a very cheap way
                fprintf(stderr, "(%d) ", entry->count);

                // go immediately back to the last line
                nLinesBack = ttyLineCount - entry->ttyLine;
                while (nLinesBack-- > 0) {
                    fputs("\033[E", stderr);
                }
            } else {
                entry->level = level;
                entry->count = 1;
                entry->ttyLine = ttyLineCount;
                entry->hash = altHash;
                ttyLineCount++;
                fprintf(stderr, "%s%s:%d ┃ %s ┃ %s\033[m\n",
                        coloured_levels[level], file, line, func, buf);
            }

        } else {
            fprintf(stderr, "[%c][%s:%d][%s] %s\n", levels[level], file, line,
                    func, buf);
        }
    }
    va_end(args);
}
