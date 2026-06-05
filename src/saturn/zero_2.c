// SPDX-License-Identifier: AGPL-3.0-or-later
#include "zero.h"
#include "inc_asm.h"
#include "sattypes.h"

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6019074, func_06019074);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60190D8, func_060190D8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6019560, func_06019560);

void func_060195F0(void) {
    DAT_060476a4 = 0;
    DAT_060476a0 = 0;
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601960C, func_0601960C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601972C, func_0601972C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60198F4, func_060198F4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601992C, func_0601992C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60199F8, func_060199F8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6019A7C, func_06019A7C);

// _INIT_NOW_LOADING
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6019FA0, func_06019FA0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6019FE4, func_06019FE4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601A020, func_0601A020);

// _SET_STAGE_OVERLAYADDR
void SetStageOverlayAddress() {
    *DAT_0601ac28 = *DAT_0601ac2c; // 0x60dc000
    *DAT_0601ac34 = *DAT_0601ac30; // 0x60dc004
    *DAT_0601ac3c = *DAT_0601ac38; // 0x60dc008
    *DAT_0601ac44 = *DAT_0601ac40; // 0x60dc00c
}

// _SET_SCL_OVERLAYADDR
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AC48, func_0601AC48);

// _SET_PLAYER_OVERLAYADDR
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AD14, func_0601AD14);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AE2C, func_0601AE2C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AE5C, func_0601AE5C);

s32 func_0601AE9C(void) { return 0xff; }

s32 func_0601AEA8(void) { return 0xff; }

void func_0601AEB4(void) { DAT_060645D0 = DAT_060cf040; }

s32 d_0605D7E4;
void (*func_060cf000)(void);

// call familiar update function
void func_0601AECC() {
    if (d_0605D7E4) {
        (*func_060cf000)();
    }
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AEF4, func_0601AEF4);

void func_0601AF2C(void) { DAT_06064674 = DAT_060a5000; }

void func_0601AF44(void) { DAT_06064580 = DAT_060a5000; }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AF5C, func_0601AF5C);

void func_0601B184(void) { DAT_060645e0 = DAT_060a5000; }

void func_0601B19C(void) { DAT_06064644 = DAT_060dc000; }

void func_0601B1B4(void) { DAT_06064690 = DAT_06066000; }

// _SET_GAME_OVERLAYADDR
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B1CC, func_0601B1CC);
