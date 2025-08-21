// SPDX-License-Identifier: MIT
#include "common.h"
#include <kernel.h>
#include "libcd_internal.h"

static inline void def_cbsync(u_char intr, Result_t* result) {
    DeliverEvent(HwCdRom, EvSpCOMP);
}

static inline void def_cbready(u_char intr, Result_t* result) {
    DeliverEvent(HwCdRom, EvSpDR);
}

static inline void def_cbread(u_char intr, Result_t* result) {
    DeliverEvent(HwCdRom, EvSpDR);
}

int CdInit(void) {
    unsigned int i;

    for (i = 4; i != -1; --i) {
        if (CdReset(1) == 1) {
            CdSyncCallback(def_cbsync);
            CdReadyCallback(def_cbready);
            CdReadCallback(def_cbread);
            i = 1;
            return (float)i; // FAKE
        }
    }

    printf("CdInit: Init failed\n");
    return 0;
}
