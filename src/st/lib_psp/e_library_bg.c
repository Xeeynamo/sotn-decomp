// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../lib/lib.h"

extern SVECTOR D_psp_092702F8;
extern SVECTOR D_psp_092A54A0;

// parallax book cases
void EntityBackgroundBookcase(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    long p, flag;
    s16 x;
    long sxy;
    SVECTOR svector;
    VECTOR vector;
    MATRIX matrix;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;
            while (prim != NULL) {
                prim->tpage = 0xF;
                prim->clut = 0x35;
                prim->u0 = prim->u2 = 130;
                prim->u1 = prim->u3 = 253;
                prim->v0 = prim->v1 = 50;
                prim->v2 = prim->v3 = 125;
                prim->priority = 0x40;
                prim->drawMode = DRAW_UNK02;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        g_GpuBuffers[0].draw.r0 = 16;
        g_GpuBuffers[0].draw.g0 = 16;
        g_GpuBuffers[0].draw.b0 = 16;
        g_GpuBuffers[1].draw.r0 = 16;
        g_GpuBuffers[1].draw.g0 = 16;
        g_GpuBuffers[1].draw.b0 = 16;
        // fallthrough
    case 1:
        SetGeomScreen(1024);
        SetGeomOffset(128, self->posY.i.hi);
        RotMatrix(&D_psp_092A54A0, &matrix);
        vector.vx = self->posX.i.hi - 128;
        vector.vy = 0;
        vector.vz = 1024;
        TransMatrix(&matrix, &vector);
        SetRotMatrix(&matrix);
        SetTransMatrix(&matrix);
        RotTransPers(&D_psp_092702F8, &sxy, &p, &flag);

        x = sxy & 0xFFFF;
        if (x > 0) {
            while (x > -64) {
                x -= 124;
            }
        } else {
            while (x < -128) {
                x += 124;
            }
        }

        prim = self->ext.prim;
        while (prim != NULL) {
            prim->x0 = prim->x2 = x;
            x += 124;
            prim->x1 = prim->x3 = x;
            prim->y0 = prim->y1 = self->posY.i.hi - 76;
            prim->y2 = prim->y3 = self->posY.i.hi;
            prim->drawMode = DRAW_UNK02;

            prim = prim->next;
            if (x > 256) {
                break;
            }
        }

        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        break;
    }
}

extern SVECTOR D_psp_09270300;
extern SVECTOR D_psp_092A54A8;

// parallax desk & chairs
void EntityBackgroundFurniture(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    long p, flag;
    s16 x;
    long sxy;
    SVECTOR svector;
    VECTOR vector;
    MATRIX matrix;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;
            while (prim != NULL) {
                prim->tpage = 0xF;
                prim->clut = 0x34;
                prim->u0 = prim->u2 = 128;
                prim->u1 = prim->u3 = 248;
                prim->v0 = prim->v1 = 0;
                prim->v2 = prim->v3 = 28;
                prim->priority = 0x50;
                prim->drawMode = DRAW_UNK02;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        // fallthrough
    case 1:
        SetGeomScreen(1024);
        SetGeomOffset(128, self->posY.i.hi);
        RotMatrix(&D_psp_092A54A8, &matrix);
        vector.vx = self->posX.i.hi - 128;
        vector.vy = 0;
        vector.vz = 1024;
        TransMatrix(&matrix, &vector);
        SetRotMatrix(&matrix);
        SetTransMatrix(&matrix);
        RotTransPers(&D_psp_09270300, &sxy, &p, &flag);

        x = sxy & 0xFFFF;
        if (x > 0) {
            while (x > -64) {
                x -= 120;
            }
        } else {
            while (x < -128) {
                x += 120;
            }
        }

        prim = self->ext.prim;
        while (prim != NULL) {
            prim->x0 = prim->x2 = x;
            x += 120;
            prim->x1 = prim->x3 = x;
            prim->y0 = prim->y1 = self->posY.i.hi - 28;
            prim->y2 = prim->y3 = self->posY.i.hi;
            prim->drawMode = DRAW_UNK02;

            prim = prim->next;
            if (x > 256) {
                break;
            }
        }

        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        break;
    }
}

extern SVECTOR D_psp_09270308;
extern SVECTOR D_psp_092A54B0;

// parallax column shadow
void EntityBackgroundShadow(Entity* self) {
    Primitive *prim, *last;
    s32 primIndex;
    long p, flag;
    s16 x;
    long sxy;
    SVECTOR svector;
    VECTOR vector;
    MATRIX matrix;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.func_800EDB58(PRIM_TILE_ALT, 10);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.libraryShadow.prim = prim;
            while (prim != NULL) {
                prim->u0 = 24;
                prim->v0 = 64;
                prim->r0 = prim->g0 = prim->b0 = 0;
                prim->priority = 0x60;
                prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                last = prim;
                prim = prim->next;
            }
            prim = last;
            self->ext.libraryShadow.lastPrim = prim;
            prim->u0 = 255;
            prim->v0 = 48;
            prim->x0 = 0;
            prim->y0 = self->posY.i.hi - 112;
            prim->r0 = prim->g0 = prim->b0 = 0;
            prim->priority = 0x60;
            prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        } else {
            DestroyEntity(self);
            return;
        }
        // fallthrough
    case 1:
        SetGeomScreen(1024);
        SetGeomOffset(128, self->posY.i.hi);
        RotMatrix(&D_psp_092A54B0, &matrix);
        vector.vx = self->posX.i.hi - 128;
        vector.vy = 0;
        vector.vz = 1024;
        TransMatrix(&matrix, &vector);
        SetRotMatrix(&matrix);
        SetTransMatrix(&matrix);
        RotTransPers(&D_psp_09270308, &sxy, &p, &flag);

        x = sxy & 0xFFFF;
        if (x > 0) {
            while (x > -64) {
                x -= 56;
            }
        } else {
            while (x < -128) {
                x += 56;
            }
        }

        prim = self->ext.libraryShadow.prim;
        while (prim != NULL) {
            prim->x0 = x;
            x += 56;
            prim->y0 = self->posY.i.hi - 64;
            prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;

            prim = prim->next;
            if (x > 256) {
                break;
            }
        }

        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        prim = self->ext.libraryShadow.lastPrim;
        prim->u0 = 255;
        prim->v0 = 48;
        prim->x0 = 0;
        prim->y0 = self->posY.i.hi - 112;
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->priority = 0x60;
        prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        break;
    }
}

extern SVECTOR D_psp_09270310;
// clang-format off
extern u8 D_us_80180DF8[];
extern u8 D_us_80180E14[];
extern u8 D_us_80180E30[];
extern u8 D_us_80180E4C[];
// clang-format on
extern u8* D_psp_09270398[];
extern Point16 D_psp_092703A8[];
extern SVECTOR D_psp_092A54B8;

void func_us_801AFA80(Entity* self) {
    long p, flag;
    u8 pad[4];
    long sxy;
    VECTOR trans;
    MATRIX m;
    Primitive* prim;
    s32 primIndex;
    s32 i, j;
    u8* ptr;
    s16 posX, posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->posX.i.hi =
            D_psp_092703A8[self->params].x - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi =
            D_psp_092703A8[self->params].y - g_Tilemap.scrollY.i.hi;
        primIndex = g_api.func_800EDB58(PRIM_GT4, 0x10);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;
            for (i = 0; prim != NULL; i++) {
                prim->tpage = 0xF;
                prim->clut = 0x2F;
                if (i % 2) {
                    prim->u0 = prim->u2 = 0x88;
                    prim->u1 = prim->u3 = 0xFE;
                } else {
                    prim->u0 = prim->u2 = 0xFE;
                    prim->u1 = prim->u3 = 0x88;
                }
                prim->v0 = prim->v1 = 0x81;
                prim->v2 = prim->v3 = 0xFF;
                prim->priority = 0x20;
                prim->drawMode = DRAW_UNK02;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        g_GpuBuffers[0].draw.r0 = 0x40;
        g_GpuBuffers[0].draw.g0 = 0x38;
        g_GpuBuffers[0].draw.b0 = 0x28;
        g_GpuBuffers[1].draw.r0 = 0x40;
        g_GpuBuffers[1].draw.g0 = 0x38;
        g_GpuBuffers[1].draw.b0 = 0x28;
    case 1:
        SetGeomScreen(0x400);
        SetGeomOffset(0x80, 0x80);
        RotMatrix(&D_psp_092A54B8, &m);
        trans.vx = self->posX.i.hi - 0x80;
        trans.vy = self->posY.i.hi - 0x80;
        trans.vz = 0x400;
        TransMatrix(&m, &trans);
        SetRotMatrix(&m);
        SetTransMatrix(&m);
        RotTransPers(&D_psp_09270310, &sxy, &p, &flag);
        posX = sxy & 0xFFFF;
        posY = sxy >> 0x10;
        prim = self->ext.prim;
        ptr = D_psp_09270398[self->params];
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                prim->drawMode = DRAW_UNK_400 | DRAW_COLORS;
                prim->x0 = prim->x2 = posX + (j * 0x78) - 0xF0;
                if (prim->x0 > 0x100) {
                    prim->drawMode = DRAW_HIDE;
                }
                prim->x1 = prim->x3 = posX + (j * 0x78) - 0x78;
                if (prim->x1 < 0) {
                    prim->drawMode = DRAW_HIDE;
                }
                prim->y0 = prim->y1 = posY + (i * 0x80) - 0x100;
                if (prim->y0 > 0x100) {
                    prim->drawMode = DRAW_HIDE;
                }
                prim->y2 = prim->y3 = posY + (i * 0x80) - 0x80;
                if (prim->y2 < 0) {
                    prim->drawMode = DRAW_HIDE;
                }
                PGREY(prim, 0) = *(ptr + i * 5 + j + 0);
                PGREY(prim, 1) = *(ptr + i * 5 + j + 1);
                PGREY(prim, 2) = *(ptr + (i + 1) * 5 + j + 0);
                PGREY(prim, 3) = *(ptr + (i + 1) * 5 + j + 1);
                prim = prim->next;
            }
        }
    }
}
