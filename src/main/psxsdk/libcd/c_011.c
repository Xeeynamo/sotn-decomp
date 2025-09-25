// SPDX-License-Identifier: MIT
#include "common.h"
#include "registers.h"
#include <psxsdk/libcd.h>

extern volatile s32* D_80032E78;
extern volatile s32* D_80032E7C;
extern volatile s32* D_80032E88;
extern volatile s32* D_80032E98;
extern s32 D_80032EB0;
extern volatile u16* D_8003B68C;
extern s32 D_8003C0FC;
extern s16 D_8003C75C;
extern s32 D_8003C764;
extern s32 D_8003C768;
extern void (*D_8003C8C0)(void);
extern bool D_8003C908;
extern s32 D_8006BAF0;
extern s32 D_8006BAF4;
extern s32 D_80072BCC;
extern s32 D_800730D4;
extern s32 D_800978FC;
extern s32 D_80097954;
extern s32 D_80097958;
extern s32 D_800987A8;
extern u32 D_800987B8;
extern s32 D_800987C0;
extern u16* D_800987C4;
extern StHEADER* D_800987C8;
extern s32 D_80098894;

void StCdInterrupt(void) {
    volatile s16 subroutine_arg8[4];
    CdlLOC loc;
    Result_t result;
    u32* var_a1;
    s32 var_t0;
    u32* var_a0;
    u32 var_v1_2;
    u32 var_v1_3;
    u8* var_v1;

    if (D_800730D4 == 1) {
        return;
    }
    if ((D_8003C764 != 0) && (*D_80032E88 & 0x01000000)) {
        D_8003C908 = true;
        if (D_800987A8 != 0) {
            D_800978FC++;
        }
        D_80032EB0 = 1;
        return;
    }
    if (CdReady(1, &result) == CdlDiskError) {
        return;
    }
    subroutine_arg8[1] = result[0];
    subroutine_arg8[2] = result[1];
    if (subroutine_arg8[1] & 4) {
        D_80032EB0 = 3;
        return;
    }
    D_8003B68C = (u16*)&D_800987C8[D_80097954];
    if (D_8003B68C[0] != 0) {
        if (D_800987A8 != 0) {
            D_800978FC++;
        }
        D_80032EB0 = 4;
        return;
    }
    *libcd_CDRegister0 = 0;
    *libcd_CDRegister3 = 0;
    *libcd_CDRegister0 = 0;
    *libcd_CDRegister3 = 0x80;
    *D_80032E78 = 0x20943;
    *D_80032E7C = 0x1323;
    if (D_8003C768 == 0) {
        var_v1 = (u8*)&subroutine_arg8[4];
        do {
            *var_v1++ = *libcd_CDRegister2;
        } while (var_v1 < &subroutine_arg8[6]);
        for (var_v1_2 = 0; var_v1_2 < 8; var_v1_2++) {
            *libcd_CDRegister2;
        }
    }
    var_t0 = 0x11000000;
    if (D_800987A8 != 0) {
        mem2mem(D_8003B68C, (D_800978FC << 0xB) + D_800987A8, 8, 0);
    } else {
        dma_execute(3, D_8003B68C, 0, 8, var_t0, 0, 0);
    }
    while (*D_80032E98 & 0x01000000) {
    }
    ((StHEADER*)D_8003B68C)->loc = loc;
    *D_80032E78 = 0x20843;
    *D_80032E7C = 0x1325;
    if ((D_800987C0 == 1) && (D_8006BAF4 != 0)) {
        if (D_8006BAF4 != D_8003B68C[4]) {
            D_8003B68C[0] = 0;
            if (D_800987A8 != 0) {
                D_800978FC++;
            }
            return;
        }
        D_800987C0 = 0;
    }
    if ((D_8003B68C[0] != 0x160) ||
        (((D_8003B68C[1] >> 0xA) & 0x1F) != D_80072BCC)) {
        if (D_800987A8 != 0) {
            D_800978FC = 0;
        } else {
            D_8003B68C[0];
        }
        D_80032EB0 = 5;
        D_8003B68C[0] = 0;
        return;
    }
    if ((D_8003C75C != D_8003B68C[2]) ||
        ((D_8003C0FC != 0) && (D_8003C0FC != D_8003B68C[4]))) {
        D_8003C0FC = 0;
        D_8003C75C = 0;
        init_ring_status(D_80097958, D_80097954 - D_80097958);
        D_80097954 = D_80097958;
        D_8003B68C[0] = 0;
        if (D_800987A8 != 0) {
            D_800978FC++;
        }
        D_80032EB0 = 6;
        return;
    }
    if (D_8003B68C[2] == 0) {
        D_8003C75C = 0;
        D_8003C0FC = D_8003B68C[4];
        if ((D_800987B8 != 0) && (D_8003C0FC >= D_800987B8)) {
            D_8003C0FC = 0;
            D_8003C75C = 0;
            init_ring_status(D_80097958, D_80097954 - D_80097958);
            D_80097954 = D_80097958;
            D_8003B68C[0] = 0;
            D_800987C0 = 1;
            if (D_8003C8C0 != NULL) {
                D_8003C8C0();
            }
            if (D_800987A8 != 0) {
                D_800978FC++;
            }
            D_80032EB0 = 7;
            return;
        }
        if ((u32)(D_80098894 - D_80097954 - 1) < D_8003B68C[3]) {
            if (D_800987B8 == 0) {
                D_8003B68C[0] = 1;
                D_800987C0 = 1;
                if (D_8003C8C0 != NULL) {
                    D_8003C8C0();
                }
                if (D_800987A8 != 0) {
                    D_800978FC++;
                }
                D_80032EB0 = 8;
                return;
            }
            if ((s16)D_800987C8->id != 0) {
                D_8003B68C[0] = 0;
                if (D_800987A8 != 0) {
                    D_800978FC++;
                }
                D_80032EB0 = 9;
                return;
            }
            D_8003B68C[0] = 1;
            var_a1 = D_800987C8;
            var_a0 = D_8003B68C;
            D_80097954 = 0;
            for (var_v1_3 = 0; var_v1_3 < 8; var_v1_3++) {
                *var_a1++ = *var_a0++;
            }
            D_8003B68C = D_800987C8;
        }
        D_80097958 = D_80097954;
    }
    D_80032EB0 = 10;
    D_8003C75C++;
    D_800987C4 = &D_800987C8[D_80098894] + (D_80097954 * 0x3F);

    if (D_8003C764 != 0) {
        var_t0 = 0x11000000;
        *D_80032E78 = 0x20943;
        *D_80032E7C = 0x1323;
    } else {
        *D_80032E78 = 0x21020843;
        var_t0 = 0x11400100;
    }
    if ((D_8003B68C[3] - 1) == D_8003B68C[2]) {
        D_800730D4 = 1;
        if (D_800987A8 != 0) {
            mem2mem(
                D_800987C4, (D_800978FC << 0xB) + D_800987A8 + 0x20, 0x1F8, 1);
            D_800978FC++;
        } else {
            dma_execute(3, D_800987C4, 0, 0x1F8, var_t0, 1, 0);
        }
        D_8003C75C = 0;
        D_8003C0FC = 0;
        D_80072BCC = D_8006BAF0;
    } else {
        if (D_800987A8 != 0) {
            mem2mem(
                D_800987C4, (D_800978FC << 0xB) + D_800987A8 + 0x20, 0x1F8, 0);
            D_800978FC++;
        } else {
            dma_execute(3, D_800987C4, 0, 0x1F8, var_t0, 0, 0);
        }
    }
    *D_80032E7C = 0x1325;
    D_8003B68C[0] = 3;
    D_80097954 += 1;
    if ((D_800987A8 != 0) && (D_800730D4 != 0)) {
        data_ready_callback();
    }
}

void mem2mem(s32* dst, s32* src, u32 num, u32 arg3) {
    u32 i;
    for (i = 0; i < num; i++) {
        *dst++ = *src++;
    }
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/c_011", dma_execute);
