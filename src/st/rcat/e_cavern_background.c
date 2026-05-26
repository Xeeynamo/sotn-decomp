// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcat.h"
#include <scratchpad.h>

extern EInit g_EInitInteractable;

static SVECTOR D_us_801821E4 = {0};
static SVECTOR D_us_801821EC = {.vx = 0, .vy = -96, .vz = 0, .pad = 0};
static SVECTOR D_us_801821F4 = {.vx = 0, .vy = 96, .vz = 0, .pad = 0};
static SVECTOR D_us_801821FC = {0};
static SVECTOR D_us_80182204 = {0};

static SVECTOR D_us_8018220C = {0};
static SVECTOR D_us_80182214 = {.vx = 0, .vy = -64, .vz = 0, .pad = 0};
static SVECTOR D_us_8018221C = {.vx = 0, .vy = 64, .vz = 64, .pad = 0};
static SVECTOR D_us_80182224 = {.vx = 0, .vy = 0, .vz = 64, .pad = 0};
static SVECTOR D_us_8018222C = {0};

// Handles icy cavern background in the rooms with Skeleton/Frozen Halfs
// In non-inverted this hosts the Lossoth enemies and lava instead
void EntityCavernBackgroundIce(Entity* self) {
#ifdef VERSION_PC
    u8 sp[SP_LEN];
#endif
    s32 pad[2];
    long p;
    long flag;
    VECTOR sp48;
    MATRIX matrix;

    Primitive* prim;
    s32 i;
    s16 posX;
    s16 r;
    Primitive* prevPrim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        // fallthrough
    case 1:
        // nb. this is unnecessary, needed for PSP match though
        i = 0;
        primIndex = g_api.func_800EDB58(PRIM_GT4, 0x15);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;
            while (prim != NULL) {
                prim->tpage = 0xF;
                prim->clut = PAL_CAVERN_A;
                prim->u0 = 0x85;
                prim->u1 = 0xC3;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->priority = 0x1F;
                prim->drawMode = DRAW_UNK_400 | DRAW_COLORS | DRAW_UNK02;
                // nb. this goes unused
                prevPrim = prim;
                prim = prim->next;
            }

            for (prim = self->ext.prim, i = 0; i < 7; prim = prim->next, i++) {
                prim->v0 = 0xC0;
                prim->v1 = prim->v0;
                prim->v2 = 0xFE;
                prim->v3 = prim->v2;
                PGREY(prim, 0) = 0x60;
                LOW(prim->r1) = LOW(prim->r0);
                PGREY(prim, 2) = 0x40;
                LOW(prim->r3) = LOW(prim->r2);
                prim = prim->next;

                prim->v0 = 0x81;
                prim->v1 = prim->v0;
                prim->v2 = 0xBF;
                prim->v3 = prim->v2;
                PGREY(prim, 0) = 0x40;
                LOW(prim->r1) = LOW(prim->r0);
                PGREY(prim, 2) = 0x60;
                LOW(prim->r3) = LOW(prim->r2);
                prim = prim->next;

                prim->v0 = 0xC0;
                prim->v1 = prim->v0;
                prim->v2 = 0xFF;
                prim->v3 = prim->v2;
                PGREY(prim, 0) = 0x60;
                LOW(prim->r1) = LOW(prim->r0);
                PGREY(prim, 2) = 0x80;
                LOW(prim->r3) = LOW(prim->r2);
            }
        }
        self->step++;
        self->step_s = 1;
        // fallthrough
    case 2:
        SetGeomScreen(0xC0);
        SetGeomOffset(0x80, 0x80);

        posX = (self->posX.i.hi & 0xFF) - 0x100;
        while (posX < 0) {
            posX += 0x40;
        }
        posX -= 0x80;

        for (i = 0; i < 8; i++) {
            r = -0x2AA;
            RotMatrix(&D_us_80182204, &matrix);
            RotMatrixX(r, &matrix);
            sp48.vx = (i * 64) + posX - 0x80;
            sp48.vy = 0x68;
            sp48.vz = 0xC8;
            TransMatrix(&matrix, &sp48);
            SetRotMatrix(&matrix);
            SetTransMatrix(&matrix);
            RotTransPers(&D_us_801821E4, &((long*)SPAD(0))[i * 4], &p, &flag);
            RotTransPers(&D_us_801821EC, &((long*)SPAD(1))[i * 4], &p, &flag);

            r = 0x2AA;
            RotMatrix(&D_us_80182204, &matrix);
            RotMatrixX(r, &matrix);
            sp48.vx = (i * 64) + posX - 0x80;
            sp48.vy = -0x40;
            sp48.vz = 0xC8;
            TransMatrix(&matrix, &sp48);
            SetRotMatrix(&matrix);
            SetTransMatrix(&matrix);
            RotTransPers(&D_us_801821F4, &((long*)SPAD(2))[i * 4], &p, &flag);
            RotTransPers(&D_us_801821FC, &((long*)SPAD(3))[i * 4], &p, &flag);
        }

        for (prim = self->ext.prim, i = 0; i < 7; prim = prim->next, i++) {
            LOW(prim->x0) = ((long*)SPAD(0))[i * 4];
            LOW(prim->x1) = ((long*)SPAD(4))[i * 4];
            LOW(prim->x2) = ((long*)SPAD(1))[i * 4];
            LOW(prim->x3) = ((long*)SPAD(5))[i * 4];
            prim = prim->next;

            LOW(prim->x0) = ((long*)SPAD(1))[i * 4];
            LOW(prim->x1) = ((long*)SPAD(5))[i * 4];
            LOW(prim->x2) = ((long*)SPAD(2))[i * 4];
            LOW(prim->x3) = ((long*)SPAD(6))[i * 4];
            prim = prim->next;

            LOW(prim->x0) = ((long*)SPAD(2))[i * 4];
            LOW(prim->x1) = ((long*)SPAD(6))[i * 4];
            LOW(prim->x2) = ((long*)SPAD(3))[i * 4];
            LOW(prim->x3) = ((long*)SPAD(7))[i * 4];
        }
        break;
    }
}

// For the intermediate room with the bridge on the roof
// In non-inverted this houses the Discus Lord but here it's largely empty
void EntityCavernBackgroundIceBridge(Entity* self) {
#ifdef VERSION_PC
    u8 sp[SP_LEN];
#endif
    s32 pad[2];
    long p;
    long flag;
    VECTOR sp48;
    MATRIX matrix;

    Primitive* prim;
    s32 i;
    s16 posX;
    s16 r;
    Primitive* prevPrim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        // Position is offset so it doesn't clip into the transparent ice
        self->posY.i.hi = 0x80 - g_Tilemap.scrollY.i.hi;
        // fallthrough
    case 1:
        // nb. this is unnecessary, needed for PSP match though
        i = 0;
        primIndex = g_api.func_800EDB58(PRIM_GT4, 0x15);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;
            while (prim != NULL) {
                prim->tpage = 0xF;
                prim->clut = PAL_CAVERN_A;
                prim->u0 = 0x85;
                prim->u1 = 0xC3;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->priority = 0x1F;
                prim->drawMode = DRAW_UNK_400 | DRAW_COLORS | DRAW_UNK02;
                // nb. this goes unused
                prevPrim = prim;
                prim = prim->next;
            }

            for (prim = self->ext.prim, i = 0; i < 7; prim = prim->next, i++) {
                prim->v0 = 0xC0;
                prim->v1 = prim->v0;
                prim->v2 = 0xFE;
                prim->v3 = prim->v2;
                PGREY(prim, 0) = 0x90;
                LOW(prim->r1) = LOW(prim->r0);
                PGREY(prim, 2) = 0x60;
                LOW(prim->r3) = LOW(prim->r2);
                prim = prim->next;

                prim->v0 = 0x81;
                prim->v1 = prim->v0;
                prim->v2 = 0xBF;
                prim->v3 = prim->v2;
                PGREY(prim, 0) = 0x60;
                LOW(prim->r1) = LOW(prim->r0);
                PGREY(prim, 2) = 0x40;
                LOW(prim->r3) = LOW(prim->r2);
                prim = prim->next;

                prim->v0 = 0xC0;
                prim->v1 = prim->v0;
                prim->v2 = 0xFF;
                prim->v3 = prim->v2;
                PGREY(prim, 0) = 0x40;
                LOW(prim->r1) = LOW(prim->r0);
                PGREY(prim, 2) = 0xB0;
                LOW(prim->r3) = LOW(prim->r2);
            }
        }
        self->step++;
        self->step_s = 1;
        // fallthrough
    case 2:
        SetGeomScreen(0xC0);
        SetGeomOffset(0x80, self->posY.i.hi);

        posX = (self->posX.i.hi & 0xFF) - 0x100;
        while (posX < 0) {
            posX += 0x40;
        }
        posX -= 0x80;

        for (i = 0; i < 8; i++) {
            r = -0x2AA;
            RotMatrix(&D_us_8018222C, &matrix);
            RotMatrixX(r, &matrix);
            sp48.vx = (i * 64) + posX - 0x80;
            sp48.vy = 0x80;
            sp48.vz = 0xC8;
            TransMatrix(&matrix, &sp48);
            SetRotMatrix(&matrix);
            SetTransMatrix(&matrix);
            RotTransPers(&D_us_8018220C, &((long*)SPAD(0))[i * 4], &p, &flag);
            RotTransPers(&D_us_80182214, &((long*)SPAD(1))[i * 4], &p, &flag);

            r = 0x40;
            RotMatrix(&D_us_8018222C, &matrix);
            RotMatrixX(r, &matrix);
            sp48.vx = (i * 64) + posX - 0x80;
            sp48.vy = -0x38;
            sp48.vz = 0xC8;
            TransMatrix(&matrix, &sp48);
            SetRotMatrix(&matrix);
            SetTransMatrix(&matrix);
            RotTransPers(&D_us_8018221C, &((long*)SPAD(2))[i * 4], &p, &flag);
            RotTransPers(&D_us_80182224, &((long*)SPAD(3))[i * 4], &p, &flag);
        }

        for (prim = self->ext.prim, i = 0; i < 7; prim = prim->next, i++) {
            LOW(prim->x0) = ((long*)SPAD(0))[i * 4];
            LOW(prim->x1) = ((long*)SPAD(4))[i * 4];
            LOW(prim->x2) = ((long*)SPAD(1))[i * 4];
            LOW(prim->x3) = ((long*)SPAD(5))[i * 4];
            prim = prim->next;

            LOW(prim->x0) = ((long*)SPAD(1))[i * 4];
            LOW(prim->x1) = ((long*)SPAD(5))[i * 4];
            LOW(prim->x2) = ((long*)SPAD(2))[i * 4];
            LOW(prim->x3) = ((long*)SPAD(6))[i * 4];
            prim = prim->next;

            LOW(prim->x0) = ((long*)SPAD(2))[i * 4];
            LOW(prim->x1) = ((long*)SPAD(6))[i * 4];
            LOW(prim->x2) = ((long*)SPAD(3))[i * 4];
            LOW(prim->x3) = ((long*)SPAD(7))[i * 4];
        }
        break;
    }
}
