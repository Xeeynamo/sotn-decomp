#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <common.h>
#include <log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _MSC_VER
#include <dirent.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <psxsdk/kernel.h>

int VSync(int mode) {
    DEBUGF("dummy");
    return 0;
}

long SetRCnt(unsigned long a, unsigned short b, long c) { NOT_IMPLEMENTED; }

void ChangeClearPAD(long a) { NOT_IMPLEMENTED; }

void _bu_init(void) { NOT_IMPLEMENTED; }

long OpenEvent(unsigned long a, long b, long c, long (*func)()) {
    NOT_IMPLEMENTED;
}

long EnableEvent(long a) { NOT_IMPLEMENTED; }

long TestEvent(unsigned long event) { NOT_IMPLEMENTED; }

void EnterCriticalSection(void) { NOT_IMPLEMENTED; }

void ExitCriticalSection(void) { NOT_IMPLEMENTED; }

void _adjust_path(char* dst, const char* src, int maxlen) {
#ifndef _MSC_VER
    INFOF("TODO: adjust path '%s'", src);
    strncpy(dst, src, maxlen);
    dst[maxlen - 1] = '\0';
#endif
}

void _populate_entry(struct DIRENTRY* dst, struct dirent* src) {
#ifndef _MSC_VER
    struct stat fileStat;
    if (stat(src->d_name, &fileStat) == -1) {
        ERRORF("failed to stat '%s'", src->d_name);
    }

    // TODO: names longer than 20 characters are not supported
    if (strlen(src->d_name) >= sizeof(dst->name) - 1) {
        WARNF("dir name '%s' will be truncated", src->d_name);
    }
    strncpy(dst->name, src->d_name, sizeof(dst->name) - 1);
    dst->name[sizeof(dst->name) - 1] = '\0';
    dst->attr = 0; // not sure what this is
    dst->size = fileStat.st_size;
    dst->head = 0; // not sure what this is
    dst->system[0] = 'O';
    dst->system[1] = 'S';
    dst->system[2] = '\0';
    dst->system[3] = '\0';
#endif
}

struct DIRENTRY* firstfile(char* dirPath, struct DIRENTRY* firstEntry) {
#ifndef _MSC_VER
    char adjPath[0x100];
    _adjust_path(adjPath, dirPath, sizeof(adjPath));

    DEBUGF("opendir('%s')", adjPath);
    DIR* dir = opendir(adjPath);

    if (!dir) {
        ERRORF("Failed to open directory '%s'", adjPath);
        return NULL;
    }

    struct dirent* entry = readdir(dir);
    if (!entry) {
        ERRORF("Failed to read directory '%s'", adjPath);
        closedir(dir);
        return NULL;
    }

    _populate_entry(firstEntry, entry);
    firstEntry->next = (struct DIRENTRY*)dir;

// since libapi does not offer a 'closefile', the expectation is that the
// caller will consume 'nextfile' until a NULL is received, effectively
// calling 'closedir' and freeing the resource created here.
// If that does not happen, a memory leak will occur.
#endif
    return firstEntry;
}

// dirent not available on MSVC
struct DIRENTRY* nextfile(struct DIRENTRY* outEntry) {
#ifndef _MSC_VER
    if (!outEntry) {
        return NULL;
    }

    if (!outEntry->next) {
        return NULL;
    }

    DIR* dir = (DIR*)outEntry->next;
    struct dirent* entry = readdir(dir);

    while (entry) {
        // filter by regular files
        if (entry->d_type == DT_REG) {
            _populate_entry(outEntry, entry);
            return outEntry;
        }

        entry = readdir(dir);
    }

    // Close the directory if there are no more entries
    closedir(dir);
    outEntry->next = NULL;
#endif
    return NULL;
}

long erase(char* path) {
#ifndef _MSC_VER
    char adjPath[0x100];
    _adjust_path(adjPath, path, sizeof(adjPath));

    DEBUGF("remove('%s')", adjPath);
    return remove(adjPath) == 0;
#else
    return 0;
#endif
}

long format(char* fs) { NOT_IMPLEMENTED; }
