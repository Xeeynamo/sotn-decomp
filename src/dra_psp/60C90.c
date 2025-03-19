// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

extern MemcardInfo g_MemcardInfo[2];

void func_psp_0913D610(void) {}

void MemcardInit(void) { g_MemcardStep = 0; }

void MemcardInfoInit(void) {
    g_MemcardInfo[0].nBlockUsed = 0;
    g_MemcardInfo[1].nBlockUsed = 0;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/60C90", MemcardParse);

INCLUDE_ASM("dra_psp/psp/dra_psp/60C90", GetMemcardFreeBlockCount);

INCLUDE_ASM("dra_psp/psp/dra_psp/60C90", MemcardDetectSave);

s32 IsMemcardBlockUsed(s32 cardNum, s32 blockNum) {
    return g_MemcardInfo[cardNum].blocks[blockNum];
}

INCLUDE_ASM("dra_psp/psp/dra_psp/60C90", func_psp_0913D7D8);
