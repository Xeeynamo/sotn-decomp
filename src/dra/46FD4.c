#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

void func_800E6FD4(void) {
    POLY_GT4* poly;
    u8 temp_s0;

    if ((!(D_80097494 & 0x800)) || (g_IsTimeAttackUnlocked == 0)) {
        switch (D_80073060) {
        case 0:
            if (D_8006C3B0 == 0) {
                func_800EA538(0);
                func_800EA5E4(0x1A);
                D_8006C398 = 1;
                D_8006BAFC = 0x18;
                func_800E3618(0x140);
                D_8013640C = AllocPolygons(4, 2);
                poly = &D_80086FEC[D_8013640C];
                func_80107360(poly, 0x2C, 0x60, 0xE8, 0x20, 0, 0);
                func_801072BC(poly);
                poly->tpage = 0x1C;
                poly->pad3 = 4;
                poly->p1 = 0x40;
                poly = (POLY_G4*)poly->tag;
                func_80107360(poly, 0x3C, 0xD0, 0xC0, 0x10, 0, 0x20);
                func_801072DC(poly);
                poly->tpage = 0x1C;
                poly->pad3 = 8;
                D_80073060++;
                return;
            }
            break;

        case 1:
            poly = &D_80086FEC[D_8013640C];
            poly->p1--;
            if (poly->p1 == 0) {
                D_80073060++;
            }
            break;

        case 2:
            poly = &D_80086FEC[D_8013640C];
            temp_s0 = poly->r0 + 1;
            func_80107250(poly, temp_s0);
            if (temp_s0 == 0x60) {
                ((POLY_GT4*)poly->tag)->pad3 = 8;
            }
            if (temp_s0 == 0x80) {
                poly->p1 = 0x80;
                D_80073060++;
            }
            break;

        case 3:
            poly = &D_80086FEC[D_8013640C];
            poly->p1--;
            if (poly->p1 == 0) {
                D_80073060++;
            }
            break;

        case 4:
            poly = &D_80086FEC[D_8013640C];
            temp_s0 = poly->r0 - 1;
            func_80107250(poly, temp_s0);
            if (temp_s0 == 0x40) {

                ((POLY_GT4*)poly->tag)->pad3 = 8;
            }
            if (temp_s0 == 0) {
                FreePolygons(D_8013640C);
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

const u32 rodataPadding_800DB804 = 0;