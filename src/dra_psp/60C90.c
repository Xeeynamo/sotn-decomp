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

s32 MemcardParse(s32 nPort, s32 nCard) {
    s32 blocksFree = 0;

    if (nPort == 0) {
        // Presumably func_8919278 is something like
        // getNumFreeBlocks, but I don't know the SDK function set.
        blocksFree = func_8919278();
    }
    g_MemcardInfo[nPort].nBlockUsed = BLOCK_PER_CARD - blocksFree;
    g_MemcardInfo[nPort].nFreeBlock = blocksFree;
    return g_MemcardInfo[nPort].nFreeBlock;
}

s32 GetMemcardFreeBlockCount(s32 nPort) {
    return g_MemcardInfo[nPort].nFreeBlock;
}

s32 MemcardDetectSave(s32 nPort, s32 expectedSaveName, s32 block) {
    bool result;
    bool found;

    result = false;
    if (nPort == 0) {
        if (func_8919188(expectedSaveName) >= 0) {
            found = true;
        } else {
            found = false;
        }
        result = found;
    }
    g_MemcardInfo[nPort].blocks[block] = result;
    return result;
}

s32 IsMemcardBlockUsed(s32 cardNum, s32 blockNum) {
    return g_MemcardInfo[cardNum].blocks[blockNum];
}

s32 MemcardReadFile(s32 nPort, s32 nCard, char* name, void* data, s32 nblock) {
    s32 len;
    s32 ret;

    if (nPort != 0) {
        return -1;
    }
    if (nCard != 0) {
        return -1;
    }
    len = nblock * CARD_BLOCK_SIZE;
    if (nblock == 0) {
        len = 0x238;
    }
    if (func_89194E4(data, name, len) > 0) {
        ret = 0;
    } else {
        ret = -1;
    }
    return ret;
}

s32 MemcardWriteFile(s32 nPort, s32 nCard, const char* name, void* data, s32 flags, s32 unused, s32 create) {
    s32 ret;

    if (nPort != 0) {
        return -2;
    }
    if (nCard != 0) {
        return -2;
    }
    if (func_89193D4(data, name, flags << 0xD, create) > 0) {
        ret = 0;
    } else {
        ret = -1;
    }
    return ret;
}

s32 MemcardEraseFile(s32 nPort, s32 nCard, s32 arg2, s32 arg3) {
    if (nPort != 0) {
        return -1;
    }
    if (nCard != 0) {
        return -1;
    }
    return func_89192EC(arg2, arg3);
}

s32 MemcardClose(s32 nPort) {
    return 1;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/60C90", func_800E9880);

INCLUDE_ASM("dra_psp/psp/dra_psp/60C90", func_psp_0913DA28);

INCLUDE_ASM("dra_psp/psp/dra_psp/60C90", func_psp_0913DAA8);

INCLUDE_ASM("dra_psp/psp/dra_psp/60C90", StoreSaveData);

INCLUDE_ASM("dra_psp/psp/dra_psp/60C90", LoadSaveData);

INCLUDE_ASM("dra_psp/psp/dra_psp/60C90", MakeMemcardPath);