#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

extern s32 D_801379A4;
extern s32 D_801379A8;

void func_801027C4(u32 arg0) {
    POLY_GT4* poly1;
    POLY_GT4* poly2;

    poly1 = &g_PrimBuf[D_8013799C];
    poly2 = poly1->tag;
    switch (arg0) {
    case 0:
    case 3:
        poly1 = (POLY_GT4*)poly1->tag;
        do {
            poly1 = (POLY_GT4*)poly1->tag;
            poly1->x1 = 0;
            poly1->clut = 0;
            D_801379A8 = arg0 + 1;
            return;
        } while (0);
    case 1:
    case 2:
    case 5:
    case 6:
    case 7:
        poly1->x1 = 0;
        poly1->clut = 0;
        D_801379A4 = 1;
        D_801379A4 = arg0 + D_801379A4;
        break;
    case 4:
        poly1->x1 = 0xFF;
        poly1->clut = 1;
        D_801379A4 = 2;
        do {
            poly1->r0 = poly1->g0 = poly1->b0 = poly2->r0 = poly2->g0 =
                poly2->b0 = poly1->x1;
            poly1->pad3 = poly2->pad3 = 0xD1;
        } while (0);
    default:
        break;
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/627C4", func_801028AC);

void func_80102CD8(s32 arg0) {
    D_801379AC[0] = arg0;
    D_801379AC[1] = 0;
    D_801379B0 = D_800A3194[arg0];
}

// DECOMP_ME_WIP func_80102D08 https://decomp.me/scratch/NNXbc
INCLUDE_ASM("asm/us/dra/nonmatchings/627C4", func_80102D08);

// INCLUDE_ASM("asm/us/dra/nonmatchings/627C4", func_80102D70);
