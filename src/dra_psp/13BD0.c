// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/13BD0", func_psp_090F0550);

extern u8* D_8013794C;
extern s32 D_80137950;
extern s32 D_80137954;

void func_800F99B8(char* str, s32 arg1, s32 arg2) {
    // See src/st/blit_char.h
    const u16 DOUBLE_SPACE = 0x8140;
    const u16 RIGHT_DOUBLE_QUOTATION_MARK = 0x8168;

    const int FontWidth = 12;
    const int FontHeight = 16;
    char sp5f;
    s32 sp54;
    s32 sp50;
    s32 sp4c;
    s32 sp48;
    s32 var_a0;
    u8* var_a2;
    s32 var_a3;
    u8 var_s2;
    s32 var_s1;
    s32 var_s0;
    s32 i;
    s32 j;
    u8* dest_addr;

    if (arg2) {
        var_s0 = 0x3C;
    } else {
        var_s0 = 0x90;
    }
    for (i = 0, sp4c = var_s0 * FontHeight; i < sp4c; i++) {
        D_8013794C[i] = 0;
    }
    var_s1 = 0;
    sp50 = 0;
    if (arg1 & 0x100) {
        sp50 = 0x40;
    }
    if (arg1 & 0x200) {
        sp50 += 0x20;
        arg1 &= ~0x200;
    }
    sp48 = func_800F548C(arg1 & 0xFF) & 0xFF;
    while (*str != 0) {
        sp54 = 0;
        var_a0 = func_psp_0913F960(str, &sp5f);
        var_s2 = *str++;
        if ('a' <= var_s2 && var_s2 <= 'z') {
            var_a0 = var_s2 + 0x8220;
        } else if ('A' <= var_s2 && var_s2 <= 'Z') {
            var_a0 = var_s2 + 0x821F;
        } else if (var_s2 == ' ') {
            var_a0 = DOUBLE_SPACE;
            sp54 = 2;
        } else {
            sp54 = sp5f;
            if (sp5f > 1) {
                str += (sp5f - 1);
            }
            if (var_a0 == DOUBLE_SPACE) {
                var_s2 = ' ';
            }
        }
        // var_a2 = (u8*)func_80106A28(var_a0, 0);
        var_a2 = (u8*)func_psp_0913FA28(var_a0, 0);
        while (1) {
            if (var_s2 == ' ') {
                break;
            }
            for (i = 0; i < FontHeight; i++) {
                // probably fake, i think var_a2 is a 2d array like [6][??]
                if (var_a2[i * FontWidth / 2] != 0) {
                    break;
                }
            }
            if (i != FontHeight) {
                break;
            }
            for (i = 0; i < FontHeight; i++) {
                dest_addr = &var_a2[i * FontWidth / 2];
                // Effectively shift everything down an index
                for (j = 0; j < 5; j++) {
                    dest_addr[0] = dest_addr[1];
                    dest_addr += 1;
                }
                // Set last index to 0
                *dest_addr = 0;
            }
        }
        for (i = 0, var_a3 = 0; i < FontHeight; i++) {
            for (j = 0; j < FontWidth / 2; j++) {
                // similar to above comment, this could be var_a2[i][j]
                if ((var_a2[i * FontWidth / 2 + j] != 0) && (var_a3 < j)) {
                    var_a3 = j;
                }
            }
        }
        for (i = 0; i < FontHeight; i++) {
            if (var_a2[i * FontWidth / 2 + var_a3] & 0xF0) {
                break;
            }
        }
        if (i != FontHeight) {
            var_a3 += 1;
        }
        if (var_a3 < FontWidth / 2) {
            var_a3 += 1;
        }
        for (i = 0; i < FontHeight; i++) {
            dest_addr = &D_8013794C[(i * var_s0) + var_s1];
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
        }
        var_s1 += var_a3 + sp54;
        if (var_s1 >= var_s0) {
            break;
        }
    }

    LoadTPage((u_long*)D_8013794C, 0, 0, D_80137950 + sp50, D_80137954 + sp48,
              var_s0 * 2, 0x10);
    D_8013794C += sp4c;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/13BD0", func_psp_090F0DD8);
