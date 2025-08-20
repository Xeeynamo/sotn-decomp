// SPDX-License-Identifier: MIT
#include "common.h"
#include "psxsdk/libcd.h"
#include "registers.h"

void StUnSetRing() {
    EnterCriticalSection();
    CdDataCallback(NULL);
    CdReadyCallback(NULL);
    *libcd_CDRegister0 = 0;
    *libcd_CDRegister3 = 0;
    ExitCriticalSection();
}
