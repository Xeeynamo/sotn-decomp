#include <unistd.h>
#include <common.h>
#include <log.h>

int VSync(int mode) {
    DEBUGF("dummy");
    return 0;
}

long SetRCnt(unsigned long, unsigned short, long) { DEBUGF("not implemented"); }

void ChangeClearPAD(long) { DEBUGF("not implemented"); }

void _bu_init(void) { DEBUGF("not implemented"); }
