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

#if defined(VERSION_US)
INCLUDE_ASM("asm/us/dra/nonmatchings/627C4", func_801028AC);
#elif defined(VERSION_HD)
INCLUDE_ASM("asm/hd/dra/nonmatchings/627C4", jpt_80102810);
#endif

void func_80102CD8(s32 start) {
    D_801379AC.start = start;
    D_801379AC.current = 0;
    D_801379AC.coords = D_800A3194[start];
}

void func_80102D08(void) {
    D_801379AC.unk8 = D_801379AC.coords[D_801379AC.current];
    if (D_801379AC.coords[++D_801379AC.current] == 0x7FFF) {
        D_801379AC.start = 0;
        D_801379AC.unk8 = 0;
    }
}
