#include "common.h"
#include "psxsdk/libcd.h"
#include "registers.h"

void StUnSetRing() {
    EnterCriticalSection();
    CdDataCallback(0);
    CdReadyCallback(0);
    *libcd_CDRegister0 = 0;
    *libcd_CDRegister3 = 0;
    ExitCriticalSection();
}
