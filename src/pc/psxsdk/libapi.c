#include <common.h>
#include <log.h>
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
