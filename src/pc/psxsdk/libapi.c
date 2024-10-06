#include <common.h>
#include <log.h>
#include <psxsdk/kernel.h>

int MyVSync(int mode);
int VSync(int mode) { return MyVSync(mode); }

long SetRCnt(unsigned long a, unsigned short b, long c) { NOT_IMPLEMENTED; }

void ChangeClearPAD(long a) { NOT_IMPLEMENTED; }

void _bu_init(void) { NOT_IMPLEMENTED; }

long OpenEvent(unsigned long a, long b, long c, long (*func)()) {
    NOT_IMPLEMENTED;
    return -1;
}

long EnableEvent(long a) {
    NOT_IMPLEMENTED;
    return -1;
}

long TestEvent(unsigned long event) {
    // until OpenEvent is implemented, this will remain hardcoded to
    // always return 1.
    return 1;
}

#if !defined(_MSC_VER) && !defined(__MINGW32__)
// needs to be disabled on Windows as it overlaps with the kernel32 API:
// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-entercriticalsection
void EnterCriticalSection(void) { NOT_IMPLEMENTED; }
#endif

void ExitCriticalSection(void) { NOT_IMPLEMENTED; }

struct DIRENTRY* my_firstfile(char* dirPath, struct DIRENTRY* firstEntry);
struct DIRENTRY* firstfile(char* dirPath, struct DIRENTRY* firstEntry) {
    return my_firstfile(dirPath, firstEntry);
}

struct DIRENTRY* my_nextfile(struct DIRENTRY* outEntry);
struct DIRENTRY* nextfile(struct DIRENTRY* outEntry) {
    return my_nextfile(outEntry);
}

long my_erase(char* path);
long erase(char* path) { return my_erase(path); }

long format(char* fs) { NOT_IMPLEMENTED; }
