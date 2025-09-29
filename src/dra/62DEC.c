// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"

void MemCardSetPort(s32 nPort) {
    g_MemCardRStep = 0;
    g_MemCardRStepSub = nPort;
}

s32 MemCardInitAndFormat(void) {
    u32 nPort = g_MemCardRStepSub;
    s32 state = g_MemCardRStep;

    switch (state) {
    case 0:
        MemcardInit();
        g_MemCardRetryCount = 4;
        g_MemCardRStep++;
        break;

    case 1:
        if (MemcardFormat(nPort, 0) != 1) {
            if (--g_MemCardRetryCount == -1) {
                return -1;
            }
        } else {
            return 1;
        }
        break;
    }

    return 0;
}
