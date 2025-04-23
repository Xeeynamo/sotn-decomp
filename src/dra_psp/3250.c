// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

extern SaveData D_psp_091CB700;
extern u8 D_psp_091CD6FE;
extern u8 D_psp_091CD6FF;
extern s32 D_8B42044;

void func_psp_090DFBD0(void) {
    if (*(g_SaveAreaNames[g_StageId]) != 0) {
        StoreSaveData(&D_psp_091CB700, 0, rand() & 0xF);
        if (D_8B42044 != 0) {
            D_8B42044 = 0;
            D_psp_091CD6FF = 0;
        } else {
            D_psp_091CD6FF = 0xFF;
        }
        D_psp_091CD6FE = D_8006C374;
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/3250", func_psp_090DFC68);

INCLUDE_ASM("dra_psp/psp/dra_psp/3250", func_psp_090DFC80);

void func_800EA538(s32 arg0) {
    u16 v1;
    s32 i, j;
    u16 unk8;

    v1 = (0x8000 >> (arg0 - 1));
    if (arg0) {
        for (i = 0; i < LEN(D_8006C3C4); i++) {
            unk8 = D_8006C3C4[i].unk8;
            if (unk8 & v1) {
                D_8006C3C4[i].unk8 = 0;
            }
        }
    } else {
        D_8003C0EC[3] = 0;
        for (j = 0; j < LEN(D_8006C3C4); j++) {
            D_8006C3C4[j].unk8 = 0;
        }
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

INCLUDE_ASM("dra_psp/psp/dra_psp/3250", func_psp_090DFFD0);

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
            g_ClutIds[index++] = getClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0; j < 0x100; j += 0x10) {
            g_ClutIds[index++] = getClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x100; j < 0x200; j += 0x10) {
            g_ClutIds[index++] = getClut(j, i);
        }
    }
}
