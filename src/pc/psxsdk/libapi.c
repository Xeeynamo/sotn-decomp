#include <unistd.h>
#include <common.h>
#include <log.h>

int VSync(int mode) {
    DEBUGF("dummy");
    return 0;
}

long SetRCnt(unsigned long, unsigned short, long) { NOT_IMPLEMENTED; }

void ChangeClearPAD(long) { NOT_IMPLEMENTED; }

void _bu_init(void) { NOT_IMPLEMENTED; }
