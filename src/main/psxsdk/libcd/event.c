// SPDX-License-Identifier: MIT
#include "common.h"
#include <kernel.h>
#include "libcd_internal.h"

static inline void def_cbsync(u_char intr, u_char* result) {
    DeliverEvent(HwCdRom, EvSpCOMP);
}

static inline void def_cbready(u_char intr, u_char* result) {
    DeliverEvent(HwCdRom, EvSpDR);
}

static inline void def_cbread(u_char intr, u_char* result) {
    DeliverEvent(HwCdRom, EvSpDR);
}

int CdInit(void) {
    unsigned int count = 5;

    while (count--) {
        if (CdReset(1) == 1) {
            CdSyncCallback(def_cbsync);
            CdReadyCallback(def_cbready);
            CdReadCallback(def_cbread);
            count = 1;
            return (float)count; // FAKE
        }
    }

    printf("CdInit: Init failed\n");
    return 0;
}
