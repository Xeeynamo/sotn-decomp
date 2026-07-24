// SPDX-License-Identifier: AGPL-3.0-or-later
#include "zero.h"
#include "inc_asm.h"
#include "sattypes.h"

// _SET_STAGE_OVERLAYADDR
void SetStageOverlayAddress() {
    PfnEntityUpdates[0] = g_StageOverlayData.entityEntries; // 0x60dc000
    *DAT_0601ac34 = *DAT_0601ac30; // 0x60dc004
    *DAT_060645e4 = *DAT_0601ac38; // 0x60dc008
    *DAT_060645f8 = *DAT_0601ac40; // 0x60dc00c
}

// _SET_SCL_OVERLAYADDR
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AC48, func_0601AC48);

// _SET_PLAYER_OVERLAYADDR
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AD14, func_0601AD14);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AE2C, func_0601AE2C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AE5C, func_0601AE5C);

s32 func_0601AE9C(void) { return 0xFF; }

s32 func_0601AEA8(void) { return 0xFF; }

void func_0601AEB4(void) {
    DAT_060645D0 = (s32)g_BatResourceDescriptorList;
}

typedef struct {
    void (*Init)(void);
} BatServantHeader;

extern BatServantHeader g_BatServantDesc;

// call familiar update function
void func_0601AECC() {
    if (g_Servant != 0) {
        g_BatServantDesc.Init();
    }
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AEF4, func_0601AEF4);

void func_0601AF2C(void) {
    func_06064674 = (void (*)())DAT_060a5000;
}

void func_0601AF44(void) {
    func_06064580 = (void (*)())DAT_060a5000;
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AF5C, func_0601AF5C);

void func_0601B184(void) {
    func_060645E0 = (void (*)())DAT_060a5000;
}

void func_0601B19C(void) {
    func_06064644 = (void (*)())g_StageOverlayData.entityEntries;
}

void func_0601B1B4(void) {
    func_06064690 = (s32 (*)())DAT_06066000;
}

// _SET_GAME_OVERLAYADDR
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B1CC, func_0601B1CC);
