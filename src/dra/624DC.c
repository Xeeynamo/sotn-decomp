// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"

typedef struct {
    u16 start;
    s16 current;
    s16* coords;
    s16 unk8;
} Unkstruct_80102CD8;

// BSS
static s32 D_8013799C[4];
static Unkstruct_80102CD8 D_801379AC;

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

void func_801024DC(void) {
    Primitive* prim;
    s32 x;

    D_8013799C[0] = AllocPrimitives(PRIM_TILE, 4);
    prim = &g_PrimBuf[D_8013799C[0]];
    for (x = 0; prim != NULL; x++) {
        prim->x0 = (x & 1) * 128;
        prim->u0 = 0x80;
        prim->v0 = 0xF0;
        prim->priority = 0x1FD;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }

    D_8013799C[3] = 0;
    D_8013799C[2] = 0;

    D_8013799C[1] = AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_8013799C[1]];
    prim->u0 = 0;
    prim->v0 = 0;
    prim->u1 = 0xFF;
    prim->v1 = 0;
    prim->u2 = 0;
    prim->v2 = 0xFF;
    prim->u3 = 0xFF;
    prim->v3 = 0xFF;
    prim->tpage = 0x1D;
    prim->clut = 0x1C0;
    prim->priority = 0x1FE;

    prim->drawMode = DRAW_HIDE;
}

s32 func_801025F4(void) {
    Primitive* prim = &g_PrimBuf[D_8013799C[0]];
    return prim->clut;
}

void func_80102628(s32 arg0) {
    Primitive* prim;
    s32 i;

    prim = &g_PrimBuf[D_8013799C[0]];
    for (i = 0; prim != NULL; i++) {
        prim->x0 = arg0 / 2 * (i & 1);
        prim->y0 = 0;
        prim->u0 = arg0 / 2;
        prim->v0 = 0xF0;
        prim->b0 = 0;
        prim->g0 = 0;
        prim->r0 = 0;
        prim->priority = 0x1FD;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_801026BC(s32 arg0) {
    Primitive* prim = &g_PrimBuf[D_8013799C[1]];

    if (arg0 == 0) {
        prim->drawMode = DRAW_HIDE;
        return;
    } else if (!(g_StageId & STAGE_INVERTEDCASTLE_FLAG)) {
        SetPrimRect(prim, 0, 1, 255, 255);
    } else {
        prim->x0 = prim->x2 = 255;
        prim->x1 = prim->x3 = 0;
        prim->y0 = prim->y1 = 240;
        prim->y2 = prim->y3 = -15;
    }

    func_80107250(prim, arg0 * 2);

    if (arg0 == 0x40) {
        prim->drawMode = DRAW_DEFAULT;
    } else {
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
    }
}

void func_801027A4(void) { func_801026BC(0); }

void func_801027C4(u32 arg0) {
    Primitive* prim1;
    Primitive* prim2;

    prim1 = &g_PrimBuf[D_8013799C[0]];
    prim2 = prim1->next;
    switch (arg0) {
    case 0:
    case 3:
        prim1 = prim1->next;
        do {
            prim1 = prim1->next;
            prim1->x1 = 0;
            prim1->clut = 0;
            D_8013799C[3] = arg0 + 1;
        } while (0);
        break;
    case 1:
    case 2:
    case 5:
    case 6:
    case 7:
        prim1->x1 = 0;
        prim1->clut = 0;
        D_8013799C[2] = arg0 + 1;
        break;
    case 4:
        prim1->x1 = 0xFF;
        prim1->clut = 1;
        D_8013799C[2] = 2;
        do {
            prim1->r0 = prim1->g0 = prim1->b0 = prim2->r0 = prim2->g0 =
                prim2->b0 = prim1->x1;
            prim1->drawMode = prim2->drawMode =
                DRAW_MENU | DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        } while (0);
        break;
    }
}

#ifdef VERSION_PSP
#define IFSTATEMENT prim1->y1-- == 0
#else
#define IFSTATEMENT --prim1->y1 == -1
#endif

void func_801028AC(bool exitEarly) {
    Primitive* prim1;
    Primitive* prim2;
    s32 prim1clut;

    prim1 = &g_PrimBuf[D_8013799C[0]];
    prim2 = prim1->next;
    prim1clut = prim1->clut;
    switch (D_8013799C[2] - 1) {
    case -1:
        prim2->drawMode = prim1->drawMode = DRAW_HIDE;
        break;
    case 1:
    case 5:
    case 6:
        PGREY(prim1, 0) = PGREY(prim2, 0) = prim1->x1;
        if (prim1clut == 0) {
            if (D_8013799C[2] - 1 == 1) {
                prim1->x1 += 0x20;
            } else if (D_8013799C[2] - 1 == 6) {
                prim1->x1 += 8;
            } else {
                prim1->x1 += 2;
            }
            if ((D_8013799C[2] - 1) == 6) {
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
            D_8013799C[2] = 0;
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
            D_8013799C[2] = 0;
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
    switch (D_8013799C[3] - 1) {
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
                D_8013799C[3] = 0;
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
            D_8013799C[3] = 0;
        }
    }
}

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

void func_80102D70(void) {
    switch (D_801379AC.start) {
    case 0:
        break;
    case 1:
        func_80102D08();
        g_backbufferY = D_801379AC.unk8;
        break;
    case 2:
        func_80102D08();
        g_backbufferX = D_801379AC.unk8;
        break;
    case 3:
        func_80102D08();
        g_backbufferY = D_801379AC.unk8;
        break;
    case 4:
        func_80102D08();
        g_backbufferY = D_801379AC.unk8;
        break;
    case 5:
        break;
    case 6:
        func_80102D08();
        g_backbufferY = D_801379AC.unk8;
        break;
    }
}
