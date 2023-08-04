#include "common.h"
#include "libsnd_internal.h"

void SsEnd(void) {
    if (D_80032EF4 == 0) {
        D_80032F01 = 0;
        EnterCriticalSection();
        if (D_80032F00 != 0) {
            VSyncCallback(NULL);
            D_80032F00 = 0;
        } else if (D_80032F02 == 0) {
            InterruptCallback(0, D_80032EFC);
            D_80032EFC = 0;
        } else {
            InterruptCallback(6, NULL);
        }
        ExitCriticalSection();
        D_80032F02 = 0xFF;
    }
}
