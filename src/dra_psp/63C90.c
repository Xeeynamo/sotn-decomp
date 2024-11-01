// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

bool func_80131F68(void) {
    bool ret;
    if (D_8013B61C) {
        ret = 1;
    } else {
        ret = (D_8013901C != 0);
    }
    return ret;
}

// Never called in PSX; probably removed by deadstripping.
// s16 GetCdVolume(void) { return g_CdVolume; }

void SetReverbDepth(short depth) { SsUtSetReverbDepth(depth, depth); }

void func_80131FCC(void) {
    switch(D_8013B680){
        case 0:
        D_80138F7C = 0;
        break;
        case 1:
        case 2:
        D_80138F7C++;
        break;
    }
    D_8013B680 = 0;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/63C90", func_psp_09140698);
