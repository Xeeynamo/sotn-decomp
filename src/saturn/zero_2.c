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

const char D_0601A0E8[] = "RSTAGE16.MAP";
const char D_0601A0F8[] = "RSTAGE16.CHR";
const char D_0601A108[] = "RSTAGE16.PRG";
const char D_0601A118[] = "RSTAGE15.MAP";
const char D_0601A128[] = "RSTAGE15.CHR";
const char D_0601A138[] = "RSTAGE15.PRG";
const char D_0601A148[] = "STAGE_16.MAP";
const char D_0601A158[] = "STAGE_16.CHR";
const char D_0601A168[] = "STAGE_16.PRG";
const char D_0601A178[] = "STAGE_15.MAP";
const char D_0601A188[] = "STAGE_15.CHR";
const char D_0601A198[] = "STAGE_15.PRG";
const char D_0601A1A8[] = "STAGE_0X.CHR";
const char D_0601A1B8[] = "STAGE_0X.PRG";
const char D_0601A1C8[] = "LIBRARY.MAP";
const char D_0601A1D4[] = "LIBRARY.CHR";
const char D_0601A1E0[] = "LIBRARY.PRG";
const char D_0601A1EC[] = "BOSS_R11.MAP";
const char D_0601A1FC[] = "BOSS_R11.CHR";
const char D_0601A20C[] = "BOSS_R11.PRG";
const char D_0601A21C[] = "BOSS_R02.MAP";
const char D_0601A22C[] = "BOSS_R02.CHR";
const char D_0601A23C[] = "BOSS_R02.PRG";
const char D_0601A24C[] = "BOSS_R12.MAP";
const char D_0601A25C[] = "BOSS_R12.CHR";
const char D_0601A26C[] = "BOSS_R12.PRG";
const char D_0601A27C[] = "BOSS_R06.MAP";
const char D_0601A28C[] = "BOSS_R06.CHR";
const char D_0601A29C[] = "BOSS_R06.PRG";
const char D_0601A2AC[] = "BOSS_R04.MAP";
const char D_0601A2BC[] = "BOSS_R04.CHR";
const char D_0601A2CC[] = "BOSS_R04.PRG";
const char D_0601A2DC[] = "BOSS_R09.MAP";
const char D_0601A2EC[] = "BOSS_R09.CHR";
const char D_0601A2FC[] = "BOSS_R09.PRG";
const char D_0601A30C[] = "BOSS_R14.CHR";
const char D_0601A31C[] = "BOSS_R14.PRG";
const char D_0601A32C[] = "BOSS_R10.MAP";
const char D_0601A33C[] = "BOSS_R10.CHR";
const char D_0601A34C[] = "BOSS_R10.PRG";
const char D_0601A35C[] = "BOSS_R13.MAP";
const char D_0601A36C[] = "BOSS_R13.CHR";
const char D_0601A37C[] = "BOSS_R13.PRG";
const char D_0601A38C[] = "BOSS_R08.MAP";
const char D_0601A39C[] = "BOSS_R08.CHR";
const char D_0601A3AC[] = "BOSS_R08.PRG";
const char D_0601A3BC[] = "RWARP.MAP";
const char D_0601A3C8[] = "RWARP.CHR";
const char D_0601A3D4[] = "RWARP.PRG";
const char D_0601A3E0[] = "RSTAGE08.MAP";
const char D_0601A3F0[] = "RSTAGE08.CHR";
const char D_0601A400[] = "RSTAGE08.PRG";
const char D_0601A410[] = "RSTAGE02.MAP";
const char D_0601A420[] = "RSTAGE02.CHR";
const char D_0601A430[] = "RSTAGE02.PRG";
const char D_0601A440[] = "RSTAGE7A.MAP";
const char D_0601A450[] = "RSTAGE07.CHR";
const char D_0601A460[] = "RSTAGE07.PRG";
const char D_0601A470[] = "RSTAGE11.MAP";
const char D_0601A480[] = "RSTAGE11.CHR";
const char D_0601A490[] = "RSTAGE11.PRG";
const char D_0601A4A0[] = "RSTAGE9A.MAP";
const char D_0601A4B0[] = "RSTAGE09.CHR";
const char D_0601A4C0[] = "RSTAGE09.PRG";
const char D_0601A4D0[] = "RSTAGE14.MAP";
const char D_0601A4E0[] = "RSTAGE14.CHR";
const char D_0601A4F0[] = "RSTAGE14.PRG";
const char D_0601A500[] = "RSTAGE01.MAP";
const char D_0601A510[] = "RSTAGE01.CHR";
const char D_0601A520[] = "RSTAGE01.PRG";
const char D_0601A530[] = "RSTAGE6A.MAP";
const char D_0601A540[] = "RSTAGE06.CHR";
const char D_0601A550[] = "RSTAGE06.PRG";
const char D_0601A560[] = "RSTAGE12.MAP";
const char D_0601A570[] = "RSTAGE12.CHR";
const char D_0601A580[] = "RSTAGE12.PRG";
const char D_0601A590[] = "RSTAGE10.MAP";
const char D_0601A5A0[] = "RSTAGE10.CHR";
const char D_0601A5B0[] = "RSTAGE10.PRG";
const char D_0601A5C0[] = "RSTAG13A.MAP";
const char D_0601A5D0[] = "RSTAGE13.CHR";
const char D_0601A5E0[] = "RSTAGE13.PRG";
const char D_0601A5F0[] = "RSTAGE05.MAP";
const char D_0601A600[] = "RSTAGE05.CHR";
const char D_0601A610[] = "RSTAGE05.PRG";
const char D_0601A620[] = "RSTAGE04.MAP";
const char D_0601A630[] = "RSTAGE04.CHR";
const char D_0601A640[] = "RSTAGE04.PRG";
const char D_0601A650[] = "RSTAGE03.MAP";
const char D_0601A660[] = "RSTAGE03.CHR";
const char D_0601A670[] = "RSTAGE03.PRG";
const char D_0601A680[] = "STAGE_00.MAP";
const char D_0601A690[] = "STAGE_00.CHR";
const char D_0601A6A0[] = "STAGE_00.PRG";
const char D_0601A6B0[] = "BOSS_10.MAP";
const char D_0601A6BC[] = "BOSS_10.CHR";
const char D_0601A6C8[] = "BOSS_10.PRG";
const char D_0601A6D4[] = "BOSS_13.MAP";
const char D_0601A6E0[] = "BOSS_13.CHR";
const char D_0601A6EC[] = "BOSS_13.PRG";
const char D_0601A6F8[] = "BOSS_11.MAP";
const char D_0601A704[] = "BOSS_11.CHR";
const char D_0601A710[] = "BOSS_11.PRG";
const char D_0601A71C[] = "BOSS_09.MAP";
const char D_0601A728[] = "BOSS_09.CHR";
const char D_0601A734[] = "BOSS_09.PRG";
const char D_0601A740[] = "BOSS_04.MAP";
const char D_0601A74C[] = "BOSS_04.CHR";
const char D_0601A758[] = "BOSS_04.PRG";
const char D_0601A764[] = "BOSS_06.MAP";
const char D_0601A770[] = "BOSS_06.CHR";
const char D_0601A77C[] = "BOSS_06.PRG";
const char D_0601A788[] = "BOSS_07.MAP";
const char D_0601A794[] = "BOSS_07.CHR";
const char D_0601A7A0[] = "BOSS_07.PRG";
const char D_0601A7AC[] = "STAGE_MA.MAP";
const char D_0601A7BC[] = "STAGE_MA.CHR";
const char D_0601A7CC[] = "STAGE_MA.PRG";
const char D_0601A7DC[] = "BOSS_12.MAP";
const char D_0601A7E8[] = "BOSS_12.CHR";
const char D_0601A7F4[] = "BOSS_12.PRG";
const char D_0601A800[] = "BOSS_08.MAP";
const char D_0601A80C[] = "BOSS_08.CHR";
const char D_0601A818[] = "BOSS_08.PRG";
const char D_0601A824[] = "BOSS_02.MAP";
const char D_0601A830[] = "BOSS_02.CHR";
const char D_0601A83C[] = "BOSS_02.PRG";
const char D_0601A848[] = "STAGE_EX.MAP";
const char D_0601A858[] = "STAGE_EX.CHR";
const char D_0601A868[] = "STAGE_EX.PRG";
const char D_0601A878[] = "BOSS_15.MAP";
const char D_0601A884[] = "BOSS_15.CHR";
const char D_0601A890[] = "BOSS_15.PRG";
const char D_0601A89C[] = "WARP.MAP";
const char D_0601A8A8[] = "WARP.CHR";
const char D_0601A8B4[] = "WARP.PRG";
const char D_0601A8C0[] = "STAGE_08.MAP";
const char D_0601A8D0[] = "STAGE_08.CHR";
const char D_0601A8E0[] = "STAGE_08.PRG";
const char D_0601A8F0[] = "STAGE_02.MAP";
const char D_0601A900[] = "STAGE_02.CHR";
const char D_0601A910[] = "STAGE_02.PRG";
const char D_0601A920[] = "STAGE_7A.MAP";
const char D_0601A930[] = "STAGE_07.CHR";
const char D_0601A940[] = "STAGE_07.PRG";
const char D_0601A950[] = "STAGE_11.MAP";
const char D_0601A960[] = "STAGE_11.CHR";
const char D_0601A970[] = "STAGE_11.PRG";
const char D_0601A980[] = "STAGE_9A.MAP";
const char D_0601A990[] = "STAGE_09.CHR";
const char D_0601A9A0[] = "STAGE_09.PRG";
const char D_0601A9B0[] = "STAGE_14.MAP";
const char D_0601A9C0[] = "STAGE_14.CHR";
const char D_0601A9D0[] = "STAGE_14.PRG";
const char D_0601A9E0[] = "STAGE_01.MAP";
const char D_0601A9F0[] = "STAGE_01.CHR";
const char D_0601AA00[] = "STAGE_01.PRG";
const char D_0601AA10[] = "STAGE06A.MAP";
const char D_0601AA20[] = "STAGE_06.CHR";
const char D_0601AA30[] = "STAGE_06.PRG";
const char D_0601AA40[] = "STAGE_12.MAP";
const char D_0601AA50[] = "STAGE_12.CHR";
const char D_0601AA60[] = "STAGE_12.PRG";
const char D_0601AA70[] = "STAGE_10.MAP";
const char D_0601AA80[] = "STAGE_10.CHR";
const char D_0601AA90[] = "STAGE_10.PRG";
const char D_0601AAA0[] = "STAGE13A.MAP";
const char D_0601AAB0[] = "STAGE_13.CHR";
const char D_0601AAC0[] = "STAGE_13.PRG";
const char D_0601AAD0[] = "STAGE_05.MAP";
const char D_0601AAE0[] = "STAGE_05.CHR";
const char D_0601AAF0[] = "STAGE_05.PRG";
const char D_0601AB00[] = "STAGE_04.MAP";
const char D_0601AB10[] = "STAGE_04.CHR";
const char D_0601AB20[] = "STAGE_04.PRG";
const char D_0601AB30[] = "STAGE_03.MAP";
const char D_0601AB40[] = "STAGE_03.CHR";
const char D_0601AB50[] = "STAGE_03.PRG";
const char D_0601AB60[] = "STAGE06B.MAP";
const char D_0601AB70[] = "STAGE_7B.MAP";
const char D_0601AB80[] = "STAGE_9C.MAP";
const char D_0601AB90[] = "STAGE_9B.MAP";
const char D_0601ABA0[] = "STAGE13B.MAP";
const char D_0601ABB0[] = "RSTAGE6B.MAP";
const char D_0601ABC0[] = "RSTAGE7B.MAP";
const char D_0601ABD0[] = "RSTAGE9C.MAP";
const char D_0601ABE0[] = "RSTAGE9B.MAP";
const char D_0601ABF0[16] = "RSTAG13B.MAP";
/* 188 filenames, 0xB18 bytes including alignment */

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

s32 func_0601AE9C(void) { return 0xFF; }

s32 func_0601AEA8(void) { return 0xFF; }

void func_0601AEB4(void) { DAT_060645D0 = DAT_060cf040; }

void (*func_060cf000)(void);

// call familiar update function
void func_0601AECC() {
    if (g_Servant != 0) {
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
