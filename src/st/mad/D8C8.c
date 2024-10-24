// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mad.h"
#include "sfx.h"

void func_8018D8C8(u16* tilemap);
INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8018D8C8);

void func_8018DC28(u16* tilemap);
INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8018DC28);

void func_8018DF0C(u16* tilemap, s32 arg1) {
    const int RoomWidth = 32;
    s32 y, x;
    s16 tile;

    for (y = 0; y < 16; y++) {
        for (x = 0; x < 32; x++) {
            if (y < 2 || y > 13) {
                tile = 3;
            } else {
                tile = 0;
            }
            if (x < 2 || x > 29) {
                tile = 3;
            }
            *(tilemap + x + y * RoomWidth) = tile;
        }
    }
    if (arg1 & 4) {
        for (y = 6; y < 10; y++) {
            for (x = 0; x < 2; x++) {
                *(tilemap + x + y * RoomWidth) = 0;
            }
        }
    }
    if (arg1 & 8) {
        for (y = 6; y < 10; y++) {
            for (x = 30; x < 32; x++) {
                *(tilemap + x + y * RoomWidth) = 0;
            }
        }
    }
    if (arg1 & 1) {
        for (y = 0; y < 2; y++) {
            for (x = 6; x < 10; x++) {
                u8 variant = !(arg1 & 8) * RoomWidth;
                *((u16*)((u8*)&tilemap[x] + variant) + y * RoomWidth) = 0;
            }
        }
    }
    if (arg1 & 2) {
        for (y = 14; y < 16; y++) {
            for (x = 6; x < 10; x++) {
                u8 variant = !(arg1 & 8) * RoomWidth;
                *((u16*)((u8*)&tilemap[x] + variant) + y * RoomWidth) = 0;
            }
        }
    }
}

void func_8018E090(u16* tilemap) {
    const int RoomWidth = 32;
    s32 x, y;
    s32 varY;
    s32 varX;

randomize_pos:
    varX = (rand() & 0xF) + 8;
    varY = (rand() & 7) + 4;
    for (y = -2; y < 3; y++) {
        for (x = -1; x < 2; x++) {
            if (*(&tilemap[varX + x] + (varY + y) * RoomWidth)) {
                goto randomize_pos;
            }
        }
    }
    *(tilemap + varX + varY * RoomWidth) = 3;
}

void func_8018E13C(u16* tilemap) {
    const int RoomWidth = 16;
    s32 x, y;

    for (y = 10; y < 16; y++) {
        for (x = 0; x < RoomWidth; x++) {
            if (rand() & 1) {
                *(tilemap + x + y * RoomWidth) = 3;
            }
        }
    }
}

void func_8018E1D4(void);
INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8018E1D4);
