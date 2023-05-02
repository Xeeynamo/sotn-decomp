#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

void func_800E6FD4(void) {
    POLY_GT4* poly;
    u8 temp;

    if ((!(g_pads[0].tapped & 0x800)) || (!g_IsTimeAttackUnlocked)) {
        switch (D_80073060) {
        case 0:
            if (D_8006C3B0 == 0) {
                func_800EA538(0);
                func_800EA5E4(0x1A);
                D_8006C398 = 1;
                D_8006BAFC = 0x18;
                func_800E3618(0x140);
                D_8013640C = AllocPrimitives(4, 2);
                poly = &g_PrimBuf[D_8013640C];
                func_80107360(poly, 44, 96, 232, 32, 0, 0);
                func_801072BC(poly);
                poly->tpage = 0x1C;
                poly->pad3 = 4;
                poly->p1 = 0x40;
                poly = (POLY_G4*)poly->tag;
                func_80107360(poly, 60, 208, 192, 16, 0, 32);
                func_801072DC(poly);
                poly->tpage = 0x1C;
                poly->pad3 = 8;
                D_80073060++;
                return;
            }
            break;

        case 1:
            poly = &g_PrimBuf[D_8013640C];
            poly->p1--;
            if (poly->p1 == 0) {
                D_80073060++;
            }
            break;

        case 2:
            poly = &g_PrimBuf[D_8013640C];
            temp = poly->r0 + 1;
            func_80107250(poly, temp);
            if (temp == 96) {
                ((POLY_GT4*)poly->tag)->pad3 = 8;
            }
            if (temp == 128) {
                poly->p1 = 128;
                D_80073060++;
            }
            break;

        case 3:
            poly = &g_PrimBuf[D_8013640C];
            poly->p1--;
            if (poly->p1 == 0) {
                D_80073060++;
            }
            break;

        case 4:
            poly = &g_PrimBuf[D_8013640C];
            temp = poly->r0 - 1;
            func_80107250(poly, temp);
            if (temp == 64) {

                ((POLY_GT4*)poly->tag)->pad3 = 8;
            }
            if (temp == 0) {
                FreePrimitives(D_8013640C);
                D_80073060++;
            }
            break;

        case 5:
            if (D_8006C3B0 == 0) {
                D_8003C728 = 1;
                D_8003C100 = 1;
                D_80073060++;
            }
            break;

        case 6:
            g_api.o.unk08();
            if (D_8003C728 == 0) {
                func_800E4970();
            }
            break;
        }

    } else {
        func_800E4970();
    }
}

void nullsub_9(void) {}

void func_800E738C(void) {
    if (D_80073060 == 1) {
        if ((g_UseDisk && D_8006C3B0 == 0) ||
            (!g_UseDisk && func_800E81FC(6, FILETYPE_SYSTEM) >= 0 &&
             func_800E81FC(7, FILETYPE_SYSTEM) >= 0)) {
            if (func_80131F68() != 0) {
                PlaySfx(0x80);
            }
            func_800E346C();
            D_80073060++;
            return;
        }
    }
    g_api.o.unk3C();
}

void func_800E7458(void) {
    s32 pad[0x40];

    switch (D_80073060) {
    case 0:
        g_StageId = STAGE_SEL;
        if (g_UseDisk) {
            D_8006C398 = 1;
            D_8006BAFC = 3;
            g_mapTilesetId = STAGE_SEL;
        }
        D_80073060++;
        break;
    case 1:
        if (g_UseDisk && D_8006C3B0 != 0)
            break;

        if (g_UseDisk || func_800E81FC(12, FILETYPE_SYSTEM) >= 0) {
            D_80073060++;
        }
        break;
    case 2:
        if (g_UseDisk) {
            D_8006C398 = 1;
            D_8006BAFC = 0xD;
        }
        D_80073060++;
        break;
    case 3:
        if (g_UseDisk && D_8006C3B0 != 0)
            break;

        if (g_UseDisk || func_800E81FC(0, FILETYPE_VH) >= 0 &&
                             func_800E81FC(0, FILETYPE_VB) >= 0) {
            D_80073060++;
        }
        break;
    case 4:
        if (g_UseDisk) {
            D_8006C398 = 1;
            D_8006BAFC = 0x100;
        }
        D_80073060++;
        break;
    case 5:
        if (g_UseDisk && D_8006C3B0 != 0)
            break;

        if (g_UseDisk || func_800E81FC(0, FILETYPE_STAGE_PRG) >= 0) {
            D_8003C9A4 = 0;
            D_80073060++;
        }
        break;
    case 6:
        g_api.o.Update();
        break;
    case 7:
        func_800E4970();
        break;
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/46FD4", func_800E768C);

void func_800E7AEC(void) {
    switch (D_8003C734) {
    case 0:
    case 1:
    case 99:
        func_800E451C();
        break;
    case 2:
        func_800E4A14();
        break;
    case 3:
        func_800E5584();
        break;
    case 4:
        func_800E6358();
        break;
    case 5:
        func_800E6FD4();
        break;
    case 6:
        nullsub_9();
        break;
    case 7:
        func_800E738C();
        break;
    case 8:
        func_800E7458();
        break;
    case 9:
        func_800E768C();
        break;
    }
}
