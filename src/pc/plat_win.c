// SPDX-License-Identifier: AGPL-3.0-only
#include <common.h>
#include <log.h>
#include <string.h>
#include <psxsdk/kernel.h>

void _adjust_path(char* dst, const char* src, int maxlen) {
    INFOF("TODO: adjust path '%s'", src);
    strncpy(dst, src, maxlen);
    dst[maxlen - 1] = '\0';
}

struct DIRENTRY* my_firstfile(char* dirPath, struct DIRENTRY* firstEntry) {
    NOT_IMPLEMENTED;
    return NULL;
}

struct DIRENTRY* my_nextfile(struct DIRENTRY* outEntry) {
    NOT_IMPLEMENTED;
    return NULL;
}

long my_erase(char* path) {
    char adjPath[0x100];
    _adjust_path(adjPath, path, sizeof(adjPath));

    DEBUGF("remove('%s')", adjPath);
    return remove(adjPath) == 0;
}
