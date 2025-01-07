// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra_psp.h"
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

#ifdef VERSION_PSP
#define IFSTATEMENT prim1->y1-- == 0
#else
#define IFSTATEMENT --prim1->y1 == -1
#endif

void func_801028AC(bool exitEarly) {
    Primitive* prim1;
    Primitive* prim2;
    s32 prim1clut;

    prim1 = &g_PrimBuf[D_8013799C];
    prim2 = prim1->next;
    prim1clut = prim1->clut;
    switch (D_801379A4[0] - 1) {
    case -1:
        prim2->drawMode = prim1->drawMode = DRAW_HIDE;
        break;
    case 1:
    case 5:
    case 6:
        PGREY(prim1, 0) = PGREY(prim2, 0) = prim1->x1;
        if (prim1clut == 0) {
            if (D_801379A4[0] - 1 == 1) {
                prim1->x1 += 0x20;
            } else if (D_801379A4[0] - 1 == 6) {
                prim1->x1 += 8;
            } else {
                prim1->x1 += 2;
            }
            if ((D_801379A4[0] - 1) == 6) {
                if (prim1->x1 >= 0x40) {
                    prim1->clut++;
                    prim1->x1 = 0x40;
                }
                func_801026BC(prim1->x1);
            } else {
                if (prim1->x1 >= 0x100) {
                    prim1->clut++;
                    prim1->x1 = 0xFF;
                }
            }
        }
        prim1->drawMode = prim2->drawMode =
            DRAW_MENU | DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        break;
    case 7:
        PGREY(prim1, 0) = PGREY(prim2, 0) = 0x40 - prim1->x1;
        if (prim1clut == 0) {
            prim1->x1 += 8;
            if (prim1->x1 >= 0x40) {
                prim1->clut++;
                prim1->x1 = 0x40;
            }
            func_801026BC(0x40 - prim1->x1);
        } else {
            func_801026BC(0);
            D_801379A4[0] = 0;
        }
        prim1->drawMode = prim2->drawMode =
            DRAW_MENU | DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        break;
    case 2:
        PGREY(prim1, 0) = PGREY(prim2, 0) = 0xFF - prim1->x1;
        if (prim1clut == 0) {
            prim1->x1 += 0x20;
            if (prim1->x1 >= 0x100) {
                prim1->clut++;
                prim1->x1 = 0xFF;
            }
        } else {
            D_801379A4[0] = 0;
        }
        prim1->drawMode = prim2->drawMode =
            DRAW_MENU | DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        break;
    }
    if (exitEarly) {
        return;
    }

    prim1 = prim2->next;
    prim2 = prim1->next;
    prim1clut = prim1->clut;
    switch (D_801379A4[1] - 1) {
    case -1:
        prim2->drawMode = prim1->drawMode = DRAW_HIDE;
        break;
    case 0:
        PGREY(prim1, 0) = PGREY(prim2, 0) = prim1->x1;
        if (prim1clut == 0) {
            prim1->x1 += 8;
            if (prim1->x1 >= 0x100) {
                prim1->clut++;
                prim1->x1 -= 8;
                prim1->y1 = 4;
            }
            prim1->drawMode = prim2->drawMode =
                DRAW_ABSPOS | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        } else if (prim1clut == 1) {
            if (IFSTATEMENT) {
                prim1->clut++;
            }

        } else {
            prim1->x1 -= 4;
            if (prim1->x1 < 0) {
                prim1->drawMode = prim2->drawMode = DRAW_HIDE;
                D_801379A4[1] = 0;
            }
        }
        break;
    case 3:
        prim1->b0 = prim2->b0 = 0;
        prim1->r0 = prim1->g0 = prim2->r0 = prim2->g0 = prim1->x1;
        if (prim1clut == 0) {
            if (++prim1->x1 >= 0x20) {
                prim1->clut++;
                prim1->x1--;
                prim1->y1 = 0xA0;
            }
            prim1->drawMode = prim2->drawMode =
                DRAW_ABSPOS | DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        } else if (prim1clut == 1) {
            if (IFSTATEMENT) {
                prim1->clut++;
            }
        } else if (--prim1->x1 < 0) {
            prim1->drawMode = prim2->drawMode = DRAW_HIDE;
            D_801379A4[1] = 0;
        }
    }
}

#define COORD_TERMINATOR 0x7FFF

s16 D_800A3134[] = {
    3, -3, 2, -2, 1, -1, COORD_TERMINATOR,
};

s16 D_800A3144[] = {
    3, -3, 3, -3, 2, -2, 2, -2, 1, -1, 1, -1, COORD_TERMINATOR,
};

s16 D_800A3160[] = {
    +6, -6, +6, -6, +5,
    -5, +5, -5, +4, -4,
    +4, -4, +3, -3, +3,
    -3, +2, -2, +2, -2,
    +1, -1, +1, -1, COORD_TERMINATOR,
};

s16* D_800A3194[] = {
    D_800A3134, D_800A3134, D_800A3144, D_800A3134,
    D_800A3144, D_800A3144, D_800A3160,
};

void func_80102CD8(s32 start) {
    D_801379AC.start = start;
    D_801379AC.current = 0;
    D_801379AC.coords = D_800A3194[start];
}

void func_80102D08(void) {
    D_801379AC.unk8 = D_801379AC.coords[D_801379AC.current];
    D_801379AC.current++;
    if (D_801379AC.coords[D_801379AC.current] == COORD_TERMINATOR) {
        D_801379AC.start = 0;
        D_801379AC.unk8 = 0;
    }
}