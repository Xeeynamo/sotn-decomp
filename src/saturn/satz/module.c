// SPDX-License-Identifier: AGPL-3.0-or-later
#include <dlfcn.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#if defined(__APPLE__)
int _NSGetExecutablePath(char* buf, uint32_t* bufsize);
#define MODULE_EXT ".dylib"
#else
#define MODULE_EXT ".so"
#endif
#include <unistd.h>
#include "module.h"

void satz_die(const char* fmt, ...) __attribute__((noreturn));

typedef struct {
    void* handle;
    void (*stop)(void);
    char name[32];
} Module;

static struct {
    Module current, previous;
} s_Areas[SATZ_AREA_COUNT];

static const char* module_dir(void) {
    static char dir[PATH_MAX];
    char* sep;

    if (dir[0]) {
        return dir;
    }
    if (getenv("SATZ_MODULE_DIR")) {
        snprintf(dir, sizeof(dir), "%s", getenv("SATZ_MODULE_DIR"));
        return dir;
    }
#if defined(__APPLE__)
    {
        uint32_t size = sizeof(dir);
        if (_NSGetExecutablePath(dir, &size)) {
            satz_die("module_dir: executable path too long");
        }
    }
#else
    {
        ssize_t n = readlink("/proc/self/exe", dir, sizeof(dir) - 1);
        if (n < 0) {
            satz_die("module_dir: /proc/self/exe unreadable");
        }
        dir[n] = '\0';
    }
#endif
    sep = strrchr(dir, '/');
    snprintf(sep ? sep + 1 : dir, sizeof(dir) - (sep ? sep + 1 - dir : 0),
             "modules");
    return dir;
}

static void unmap(Module* m) {
    if (m->handle) {
        dlclose(m->handle);
    }
    memset(m, 0, sizeof(*m));
}

void satz_module_close(SatzArea area) {
    Module* current = &s_Areas[area].current;

    if (!current->handle) {
        return;
    }
    if (current->stop) {
        current->stop();
    }
    unmap(&s_Areas[area].previous);
    s_Areas[area].previous = *current;
    memset(current, 0, sizeof(*current));
}

void satz_module_open(SatzArea area, const char* name, void* dst) {
    Module* current = &s_Areas[area].current;
    char path[PATH_MAX];
    void (*start)(void* area);

    satz_module_close(area);
    if (!strcmp(s_Areas[area].previous.name, name)) {
        unmap(&s_Areas[area].previous);
    }
    snprintf(path, sizeof(path), "%s/%s" MODULE_EXT, module_dir(), name);
    if (access(path, R_OK)) {
        satz_die(
            "overlay %s is not in the native build (no module %s)", name, path);
    }
    current->handle = dlopen(
        path, RTLD_NOW | (area == SATZ_AREA_PLAYER ? RTLD_GLOBAL : RTLD_LOCAL));
    if (!current->handle) {
        satz_die("module %s: %s", name, dlerror());
    }
    start = (void (*)(void*))dlsym(current->handle, "satz_module_start");
    if (!start) {
        satz_die("module %s has no satz_module_start", name);
    }
    current->stop = (void (*)(void))dlsym(current->handle, "satz_module_stop");
    snprintf(current->name, sizeof(current->name), "%s", name);
    start(dst);
}

const char* satz_module_name(SatzArea area) {
    return s_Areas[area].current.handle ? s_Areas[area].current.name : NULL;
}

void* satz_module_symbol(const char* symbol) {
    int i;
    void* p;

    for (i = 0; i < SATZ_AREA_COUNT; i++) {
        if (s_Areas[i].current.handle &&
            (p = dlsym(s_Areas[i].current.handle, symbol)) != NULL) {
            return p;
        }
    }
    return NULL;
}
