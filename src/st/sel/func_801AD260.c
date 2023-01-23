#include "sel.h"

void func_801AD260(u32 arg0) {
    u8** imgs;
    POLY_GT4* poly;

    func_801ACBE4(6, 8);
    imgs = &D_801803C4;
    poly = &D_80086FEC[D_801BAF48];
    switch (arg0) {
    case 0:
        func_801B2670(poly, 0x20, 0xB0, 0x10, 0x10);
        poly->pad3 = 0;
        poly = poly->tag;
        func_801B2670(poly, 0x20, 0xC0, 0x10, 0x10);
        poly->pad3 = 0;
        poly = poly->tag;
        func_801B2670(poly, 0x20, 0xD0, 0x10, 0x10);
        poly->pad3 = 0;
        break;

    case 1:
        func_801B2670(poly, 0x120, 0x20, 0x10, 0x10);
        poly->pad3 = 0;
        poly = poly->tag;
        func_801B2670(poly, 0x120, 0x30, 0x10, 0x10);
        poly->pad3 = 0;
        poly = poly->tag;
        func_801B2670(poly, 0x120, 0x40, 0x10, 0x10);
        poly->pad3 = 0;
        poly = poly->tag;
        func_801B2670(poly, 0x120, 0x50, 0x10, 0x10);
        poly->pad3 = 0;
        break;

    case 2:

    case 5:
        poly = poly->tag;
        func_801B2670(poly, 0x20, 0xC0, 0x10, 0x10);
        poly->pad3 = 0;
        poly = poly->tag;
        func_801B2670(poly, 0x20, 0xD0, 0x10, 0x10);
        poly->pad3 = 0;
        if (arg0 == 2) {
            func_801AD1D0();
        } else {
            func_801AD218();
        }
        break;

    case 3:
        poly = poly->tag;
        func_801B2670(poly, 0x20, 0xC0, 0x10, 0x10);
        poly->pad3 = 0;
        func_801B2AFC(*imgs, 0x34, 0xC4, 1);
        break;

    case 4:
        func_801B2670(poly, 0x20, 0xB8, 0x10, 0x10);
        poly->pad3 = 0;
        poly = poly->tag;
        func_801B2670(poly, 0x20, 0xC8, 0x10, 0x10);
        poly->pad3 = 0;
        break;
    }
}
