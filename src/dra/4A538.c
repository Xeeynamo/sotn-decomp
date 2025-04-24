// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"

void func_800EA538(s32 arg0) {
    Unkstruct_8006C3C4* var_v0;
    s32 temp;
    s32 v1;
    s32 i;

    // !FAKE: 0x8000 inside a temp is weird
    temp = 0x8000;
    v1 = (temp >> (arg0 - 1));

    if (arg0 != 0) {
        for (i = 0; i < LEN(D_8006C3C4); i++) {
            if (v1 & D_8006C3C4[i].unk8) {
                D_8006C3C4[i].unk8 = 0;
            }
        }
        return;
    }

    D_8003C0EC[3] = 0;
    var_v0 = &D_8006C3C4;

    for (i = 0; i < LEN(D_8006C3C4); i++) {
        var_v0->unk8 = 0;
        var_v0++;
    }
}

void func_800EA5AC(u16 arg0, u8 arg1, u8 arg2, u8 arg3) {
    D_8003C0EC[3] = arg0;
    D_8003C0EC[0] = arg1;
    D_8003C0EC[1] = arg2;
    D_8003C0EC[2] = arg3;
}

s32 func_800EA5E4(u32 arg0) {
    u16 temp_v0;
    s32 i;
    s32 j;
    u32 start;
    u32 count;
    u_long* clut;
    Unkstruct_8006C3C4* clutAnim;

    temp_v0 = arg0 & ~0xFF; // & 0xFF00 would be more descriptive.
    arg0 = arg0 & 0xFF;

    if (temp_v0 & 0x8000) {
        clut = g_api.o.cluts[arg0];
    } else {
        clut = D_800A3BB8[arg0];
    }

    if (clut[0] == 0) {
        return 1;
    }
    if (clut[0] == -1) {
        return 1;
    }

    for (j = 0, clutAnim = &D_8006C3C4[0]; j < LEN(D_8006C3C4); j++,
        clutAnim++) {
        if (clutAnim->unk8 != 0) {
            continue;
        }
        clutAnim->desc = clut;
        clutAnim->data = clut + 3;
        clutAnim->unk8 = (GET_PAL_OP_KIND(clut[0]) | temp_v0);
        clutAnim->index = 0;
        clutAnim->unkC = 0;

        // Set unkStruct's array to all zeros, except within this range
        start = clut[1];
        count = clut[2] + start - 1;
        start >>= 8;
        count >>= 8;
        for (i = 0; i < LEN(clutAnim->unkArray); i++) {
            clutAnim->unkArray[i] = 0;
        }
        for (i = start; count >= i; i++) {
            clutAnim->unkArray[i] = 1;
        }

        switch ((u8)clutAnim->unk8) {
        case 2:
        case 16:
            clutAnim->unkE = 0x1F;
        }
        return 0;
    }
    return -1;
}

#define RED_MASK 0x1F
#define GREEN_MASK 0x3E0
#define BLUE_MASK 0x7C00
// These could be ~RED_MASK, but that doesn't match.
#define UNRED_MASK 0xFFFF - RED_MASK
#define UNGREEN_MASK 0xFFFF - GREEN_MASK
#define UNBLUE_MASK 0xFFFF - BLUE_MASK

#define GET_RED(x) ((x) & RED_MASK)
#define GET_GREEN(x) ((x) & GREEN_MASK)
#define GET_BLUE(x) ((x) & BLUE_MASK)

// Takes a color "col" in RGB555 and increments/decrements each component
// to bring it closer to the target by 1.
u16 func_800EA720(u16 target, u16 col) {
    if (GET_RED(target) > GET_RED(col)) {
        col = (col & UNRED_MASK) | (GET_RED(col) + 1);
    }
    if (GET_RED(target) < GET_RED(col)) {
        col = (col & UNRED_MASK) | (GET_RED(col) - 1);
    }

    if (GET_GREEN(target) > GET_GREEN(col)) {
        col = (col & UNGREEN_MASK) | (GET_GREEN(col) + (1 << 5));
    }
    if (GET_GREEN(target) < GET_GREEN(col)) {
        col = (col & UNGREEN_MASK) | (GET_GREEN(col) - (1 << 5));
    }

    if (GET_BLUE(target) > GET_BLUE(col)) {
        col = (col & UNBLUE_MASK) | (GET_BLUE(col) + (1 << 10));
    }
    if (GET_BLUE(target) < GET_BLUE(col)) {
        col = (col & UNBLUE_MASK) | (GET_BLUE(col) - (1 << 10));
    }

    return col;
}

void func_800EA7CC(void) {
    // stores which palettes have been invalidated and need to be re-uploaded
    // to the VRAM
    u8 palettes[0x30];
    Unkstruct_8006C3C4* ptr;
    u_long* temp_s0;
    u_long* temp_v0_5;
    u_long* temp_s0_4;
    s32 count;
    s32 var_a3;
    s32 isAnimNotDone;
    s32 i;
    s32 j;
    s32 offset;
    u16 temp_a0_2;
    u16 temp_s0_2;
    u16 temp_v0_3;
    u16 var_v0_2;
    u16* clut;
    u16* data;
    u32 clutX;
    s32 new_var;

    if (g_DebugEnabled && g_DebugMode == 10) {
        return;
    }

    for (i = 0; i < LEN(palettes); i++) {
        palettes[i] = 0;
    }

    // cycles through a list of palette operations stored in D_8006C3C4
    for (i = 0, ptr = D_8006C3C4, var_a3 = 0xFFFF; i < 0x20; i++, ptr++) {
        if (ptr->unk8 == 0) {
            continue;
        }
        if (ptr->index != 0) {
            ptr->index = ptr->index + var_a3;
            continue;
        }
        temp_s0 = ptr->desc;
        data = *ptr->data;
        new_var = temp_s0[1];
        count = temp_s0[2];

        clut = g_Clut;
        clut += new_var;

        switch (ptr->unk8 & 0xFF) {
        case 1: // simple palette copy
            for (j = 0; j < count; j++) {
                *clut++ = *data++;
            }
            for (j = 0; j < LEN(palettes); j++) {
                palettes[j] |= ptr->unkArray[j];
            }
            ptr->unk8 = 0;
            break;
        case 3: // palette rotation
            for (j = 0; j < count; j++) {
                *clut++ = *data++;
            }
            for (j = 0; j < LEN(palettes); j++) {
                palettes[j] |= ptr->unkArray[j];
            }

            ptr->index = HIH(temp_s0[0]) + var_a3;
            ptr->data++;

            if (*ptr->data == -1) {
                ptr->data = temp_s0 + 3;
            }
            break;
        case 2: // blend to destination color?
            for (j = 0; j < count; j++) {
                *clut = func_800EA720(*data++, *clut);
                clut++;
            }
            for (j = 0; j < LEN(palettes); j++) {
                palettes[j] |= ptr->unkArray[j];
            }

            if (ptr->unkE != 0) {
                ptr->unkE += var_a3;
                temp_s0 = ptr->desc;
                ptr->index = HIH(temp_s0[0]) + var_a3;
            } else {
                ptr->unkE = 0x1F;
                if (*++ptr->data == -1) {
                    ptr->unk8 = 0;
                }
            }
            break;
        case 4: // blend to destination, causes item to glow
            isAnimNotDone = 0;
            for (j = 0; j < count; j++) {
                temp_a0_2 = *data++;
                temp_s0_2 = *clut;
                temp_v0_3 = func_800EA720(temp_a0_2, temp_s0_2);
                if (temp_s0_2 != temp_v0_3) {
                    isAnimNotDone = 1;
                }
                *clut++ = temp_v0_3;
            }
            for (j = 0; j < LEN(palettes); j++) {
                palettes[j] |= ptr->unkArray[j];
            }

            temp_s0 = ptr->desc;
            ptr->index = HIH(temp_s0[0]) + var_a3;
            if (isAnimNotDone == 0) {
                ptr->data++;
                if (*ptr->data == -1) {
                    ptr->data = temp_s0 + 3;
                }
            }
            break;
        case 5: // some kind of bulk palette copy?
            while (true) {
                clut = g_Clut;
                temp_v0_5 = ptr->data;
                temp_s0 = temp_v0_5 - 2;
                data = temp_v0_5[0];
                new_var = temp_v0_5[-2];
                clut += new_var;
                count = temp_v0_5[-1];
                for (j = 0; j < count; j++) {
                    *clut++ = clutX = *data++;
                }

                if (temp_s0[3] != -1) {
                    ptr->data += 3;
                } else {
                    break;
                }
            }
            for (j = 0; j < LEN(palettes); j++) {
                palettes[j] = 1;
            }
            ptr->unk8 = 0;
            break;
        case 16:
            break;
        }
    }

    if (g_DebugEnabled && g_DebugMode == DEBUG_PALETTE_VIEWER) {
        palettes[g_DebugCurPal >> 4] = 1;
    }

    // re-upload updated stage tileset palette
    offset = 0;
    temp_s0 = g_Clut;
    clutX = 0x200;
    for (i = 0xF0; i < 0x100; i++, temp_s0 = (s16*)temp_s0 + 0x100, offset++) {
        if (palettes[offset] != 0) {
            LoadClut(temp_s0, clutX, i);
        }
    }

    // re-upload updated shared entity palette
    clutX = 0;
    for (i = 0xF0; i < 0x100; i++, temp_s0 = (s16*)temp_s0 + 0x100, offset++) {
        if (palettes[offset] != 0) {
            LoadClut(temp_s0, clutX, i);
        }
    }

    // re-upload updated stage-specific entities palette
    clutX = 0x100;
    for (i = 0xF0; i < 0x100; i++, temp_s0 = (s16*)temp_s0 + 0x100, offset++) {
        if (palettes[offset]) {
            LoadClut(temp_s0, clutX, i);
        }
    }
}

s32 func_800EAD0C(void) { // the return type is needed for matching
    func_800EA5E4(4);
    func_800EA5E4(5);
    func_800EA5E4(6);
    func_800EA5E4(7);
    func_800EA5E4(8);

    if (g_PlayableCharacter == PLAYER_ALUCARD && g_StageId != STAGE_ST0) {
        func_800EA5E4(0x17);
    }
}

void func_800EAD7C(void) {
    s32 index = 0;
    s32 i;
    s32 j;

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x200; j < 0x300; j += 0x10) {
            g_ClutIds[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0; j < 0x100; j += 0x10) {
            g_ClutIds[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x100; j < 0x200; j += 0x10) {
            g_ClutIds[index++] = GetClut(j, i);
        }
    }
}
