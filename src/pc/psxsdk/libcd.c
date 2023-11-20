#include <common.h>
#include <psxsdk/libcd.h>
#include "../log.h"

CdlCB CdReadyCallback(CdlCB func) {
    DEBUGF("not implemented");
    return func;
}

int CdControl(u_char com, u_char* param, u_char* result) {
    DEBUGF("com %d", com);
    return 1;
}

int CdSync(int mode, u_char* result) {
    DEBUGF("mode %0d", mode);
    return CdlComplete;
}

int CdMix(CdlATV* vol) {
    DEBUGF("not implemented");
    return 0;
}
