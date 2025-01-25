// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

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

INCLUDE_ASM("dra_psp/psp/dra_psp/33F0", func_psp_090DFFD0);

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

static void DestroyPrimitive(Primitive* prim) {
    s32 i;
    s32 n;
    u32* primData = (u32*)prim;

    for (n = sizeof(Primitive) / sizeof(*primData), i = 0; i < n; i++) {
        *primData++ = 0;
    }
}

void DestroyAllPrimitives(void) {
    s32 i;
    Primitive* prim;

    for (i = 0, prim = g_PrimBuf; i < MAX_PRIM_COUNT; i++) {
        DestroyPrimitive(prim);
        prim->type = PRIM_NONE;
        prim++;
    }
}

s32 func_800EDAE4(void) {
    s32 i;
    DR_ENV* ptr = &D_800974AC[0];

    for (i = 0; i < 16; i++, ptr++) {
        ptr->tag = 0;
    }
#ifdef VERSION_PSP
    return 0;
#endif
}

DR_ENV* func_800EDB08(Primitive* prim) {
    s32 i;
    DR_ENV* dr = &D_800974AC[0];

    for (i = 0; i < LEN(D_800974AC); i++, dr++) {
        if (dr->tag == 0) {
#ifdef VERSION_PSP
            SetDrawEnv(dr, 0);
#endif
            dr->tag = 1;
            setcode(prim, 7);
            *(DR_ENV**)&prim->r1 = dr;
            return dr;
        }
    }

    return NULL;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/33F0", func_800EDB58);

INCLUDE_ASM("dra_psp/psp/dra_psp/33F0", AllocPrimitives);

INCLUDE_ASM("dra_psp/psp/dra_psp/33F0", func_800EDD9C);

INCLUDE_ASM("dra_psp/psp/dra_psp/33F0", FreePrimitives);

INCLUDE_ASM("dra_psp/psp/dra_psp/33F0", RenderPrimitives);
