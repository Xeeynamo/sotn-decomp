// SPDX-License-Identifier: AGPL-3.0-or-later
#if !defined(_WIN32) && !defined(__APPLE__)
#include <unistd.h>
#endif
#include <game.h>
#include <stdio.h>
#include <string.h>
#include "overlay.h"

#if defined(_WIN32)
__declspec(dllimport) void* __stdcall LoadLibraryA(const char* lpLibFileName);
__declspec(dllimport) void* __stdcall GetProcAddress(
    void* hModule, const char* lpProcName);
__declspec(dllimport) int __stdcall FreeLibrary(void* hLibModule);
__declspec(dllimport) unsigned long __stdcall GetModuleFileNameA(
    void* hModule, char* lpFilename, unsigned long nSize);

#define OVL_EXT ".dll"
typedef void* OvlHandle;

static OvlHandle OvlOpen(const char* path) { return LoadLibraryA(path); }
static void* OvlSym(OvlHandle h, const char* name) {
    return (void*)GetProcAddress(h, name);
}
static void OvlClose(OvlHandle h) { FreeLibrary(h); }
static const char* OvlError(void) {
    return "LoadLibrary/GetProcAddress failed";
}
static bool GetExePath(char* buf, size_t size) {
    unsigned long len = GetModuleFileNameA(NULL, buf, (unsigned long)size);
    return len != 0 && len < size;
}
#elif defined(__APPLE__)
#include <dlfcn.h>
#include <mach-o/dyld.h>

#define OVL_EXT ".dylib"
typedef void* OvlHandle;

static OvlHandle OvlOpen(const char* path) {
    return dlopen(path, RTLD_NOW | RTLD_GLOBAL);
}
static void* OvlSym(OvlHandle h, const char* name) { return dlsym(h, name); }
static void OvlClose(OvlHandle h) { dlclose(h); }
static const char* OvlError(void) { return dlerror(); }
static bool GetExePath(char* buf, size_t size) {
    uint32_t len = size;
    return _NSGetExecutablePath(buf, &len) == 0;
}
#else
#include <dlfcn.h>

#define OVL_EXT ".so"
typedef void* OvlHandle;

static OvlHandle OvlOpen(const char* path) {
    return dlopen(path, RTLD_NOW | RTLD_GLOBAL);
}
static void* OvlSym(OvlHandle h, const char* name) { return dlsym(h, name); }
static void OvlClose(OvlHandle h) { dlclose(h); }
static const char* OvlError(void) { return dlerror(); }
static bool GetExePath(char* buf, size_t size) {
    ssize_t len = readlink("/proc/self/exe", buf, size - 1);
    if (len <= 0) {
        return false;
    }
    buf[len] = '\0';
    return true;
}
#endif

static const char* GetExeDir(void) {
    static char dir[512];
    static bool done = false;
    static bool isok = false;
    if (done) {
        return isok ? dir : NULL;
    }
    done = true;

    if (!GetExePath(dir, sizeof(dir))) {
        return NULL;
    }

    // strip the trailing "exe" on Windows to keep only the directory name
    char* lastSep = strrchr(dir, '/');
    char* lastBackslash = strrchr(dir, '\\');
    if (lastBackslash > lastSep) {
        lastSep = lastBackslash;
    }
    if (!lastSep) {
        return NULL;
    }
    *lastSep = '\0';

    isok = true;
    return dir;
}

static void* OpenOverlayEntrypoint(
    const char* name, const char* entrypointName, OvlHandle* outHandle) {
    char path[512];
    const char* exeDir = GetExeDir();
    if (exeDir) {
        // overlays must be loaded from the exe directory
        snprintf(path, sizeof(path), "%s/%s%s", exeDir, name, OVL_EXT);
    } else {
        // alternatively, use current working directory as fallback
        snprintf(path, sizeof(path), "%s%s", name, OVL_EXT);
    }

    OvlHandle handle = OvlOpen(path);
    if (!handle) {
        ERRORF("failed to load '%s': %s", path, OvlError());
        return NULL;
    }

    void* entrypoint = OvlSym(handle, entrypointName);
    if (!entrypoint) {
        ERRORF("failed as '%s' has no '%s' entrypoint: %s", path,
               entrypointName, OvlError());
        OvlClose(handle);
        return NULL;
    }

    INFOF("loaded '%s'", path);
    *outHandle = handle;
    return entrypoint;
}

static OvlHandle CurrentStageOverlay = NULL;
bool LoadStageOverlay(const char* name, Overlay* o) {
    OvlHandle handle;
    PfnInitStage entrypoint;

    if (CurrentStageOverlay) {
        OvlClose(CurrentStageOverlay);
        CurrentStageOverlay = NULL;
    }
    entrypoint = (PfnInitStage)OpenOverlayEntrypoint(
        name, OVL_STAGE_ENTRYPOINT_NAME, &handle);
    if (!entrypoint) {
        return false;
    }
    CurrentStageOverlay = handle;
    entrypoint(o);
    return true;
}

static OvlHandle CurrentServantOverlay = NULL;
bool LoadServantOverlay(const char* name, ServantDesc* o) {
    OvlHandle handle;
    PfnInitServant entrypoint;

    if (CurrentServantOverlay) {
        OvlClose(CurrentServantOverlay);
        CurrentServantOverlay = NULL;
    }
    entrypoint = (PfnInitServant)OpenOverlayEntrypoint(
        name, OVL_SERVANT_ENTRYPOINT_NAME, &handle);
    if (!entrypoint) {
        return false;
    }
    CurrentServantOverlay = handle;
    entrypoint(o);
    return true;
}
