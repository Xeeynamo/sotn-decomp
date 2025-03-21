// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

void func_801073C0(void) {
    CdReadyCallback(NULL);
    CdDataCallback(NULL);
}

CdFile D_800ACC64 = {0x0000, 3, 0x00000, 0, 0, 0xFF, 0};
void func_801083BC(void) {
    g_CdStep = CdStep_LoadInit;
    g_LoadFile = CdFile_25;
    D_8013AE9C = 10;
    D_800ACC64.loc = 0;
}
