// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "pc.h"

static const CutsceneSymbol* _symbols = NULL;
static int _symbolCount = 0;

// normalize 0x8018xxxx ptr to 0x0018xxxx
#define PC_ADDR(x) ((x) & 0x0FFFFFFF)

void CutscenePcAlloc(const CutsceneSymbol* symbols, int count) {
    int i;

    if (!symbols || count <= 0) {
        _symbols = NULL;
        _symbolCount = 0;
        return;
    }

    _symbols = symbols;
    _symbolCount = count;
    for (i = 1; i < count; i++) {
        // catch overlapping symbols
        u32 prevEnd = PC_ADDR(symbols[i - 1].psxAddr) + symbols[i - 1].size;
        if (PC_ADDR(symbols[i].psxAddr) < prevEnd) {
            ERRORF("cutscene symbol at 0x%08x overlaps the previous entry "
                   "ending at 0x%08x; a registered size is wrong",
                   symbols[i].psxAddr, prevEnd);
        }
    }
}

u8* CutsceneAddrToPc(u32 psxAddr) {
    u32 addr = PC_ADDR(psxAddr);
    for (int i = 0; i < _symbolCount; i++) {
        u32 base = PC_ADDR(_symbols[i].psxAddr);
        if (addr >= base && addr < base + _symbols[i].size) {
            return (u8*)_symbols[i].pcAddr + (addr - base);
        }
    }
    ERRORF("address 0x%08x not found", psxAddr);
    return NULL;
}
