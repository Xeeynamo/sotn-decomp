// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcat.h"
#include <scratchpad.h>

extern EInit g_EInitInteractable;
extern u8 D_us_801812D4[];
extern s16 D_us_801812E4[];
extern SVECTOR D_us_801812FC;
extern SVECTOR D_us_8018130C;
extern SVECTOR D_us_80181314;
extern SVECTOR D_us_8018131C;
extern SVECTOR D_us_80181324;
extern SVECTOR D_us_8018132C;
extern SVECTOR D_us_80181334;
extern SVECTOR D_us_8018133C;
extern SVECTOR D_us_80181344;
extern SVECTOR D_us_8018134C;
extern SVECTOR D_us_80181354;
extern SVECTOR D_us_8018135C;

// BSS
extern Primitive* D_us_801C3184[14];
extern Primitive* D_us_801C31BC[14];

void EntityLava(Entity* self) {
    long p;
    long flag;
    SVECTOR sVec;
    VECTOR vec;
    MATRIX matrix;
    Primitive* prim;
    Primitive** primArr;
    s32 i;
    s32 j;
    Primitive* prevPrim;
    Primitive* nextPrim;
    s32 primIndex;
    Entity* newEntity;

    if (self->params & 2) {
        primArr = D_us_801C31BC;
    } else {
        primArr = D_us_801C3184;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->ext.lava.prim = NULL;
        self->ext.lava.unk89 = 1;
        self->ext.lava.unk84 = 0;
        self->zPriority = 0xA8;
        if (!self->params) {
            newEntity =
                AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_LAVA_EMBERS, self, newEntity);
            }
        }

        if (self->params & 2) {
            self->zPriority -= 8;
        }

        self->ext.lava.clut = 0x224;
        if (self->params) {
            self->ext.lava.clut = 0x223;
            self->posY.i.hi = 0x44 - g_Tilemap.scrollY.i.hi;
        }
        // fallthrough
    case 1:
        primIndex = g_api.func_800EDB58(PRIM_GT4, 0x1A);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.lava.prim = prim;
        } else {
            DestroyEntity(self);
            return;
        }
        self->step++;
        // fallthrough
    case 2:
        for (prim = self->ext.lava.prim, i = 0; i < 13; prim = prim->next,
            i++) {
            primArr[i] = prim;
            UnkPolyFunc2(prim);
            prim->next->x1 = (i << 5) - 0x10;
            prim->next->y0 = self->posY.i.hi;
            prim->tpage = 0x15;
            prim->clut = self->ext.lava.clut;
            prim->u0 = 8;
            prim->u1 = 0x27;
            prim->u2 = 8;
            prim->u3 = 0x27;
            prim->v0 = 0x18;
            prim->v1 = 0x18;
            prim->v2 = 0x40;
            prim->v3 = 0x40;
            if (self->params) {
                prim->clut = 0x223;
                prim->v0 = 0x28;
                prim->v1 = 0x28;
                prim->v2 = 0x48;
                prim->v3 = 0x48;
            }
            LOH(prim->r0) = 0x4040;
            LOH(prim->r1) = 0x4040;
            prim->b0 = prim->b1 = 0x40;
            LOH(prim->r2) = -0x2F30;
            LOH(prim->r3) = -0x2F30;
            prim->b2 = prim->b3 = 0xD0;
            prim->priority = self->zPriority - 1;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            if (self->params & 1) {
                prim->drawMode |= DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            }
            LOBU(prim->next->priority) = D_us_801812D4[i];
            prim->next->tpage = D_us_801812E4[i];
            prim = prim->next;
        }

        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        primArr[0]->drawMode |= DRAW_HIDE;
        self->ext.lava.unk84 = 2;
        self->step++;
        self->step_s = 0;
    case 3:
        if (!self->ext.lava.unk84) {
            prim = primArr[0];
            nextPrim = primArr[1];
            if (!(prim->next->r3 | nextPrim->next->r3)) {
                prim->next->r3 = 1;
                LOW(prim->next->r1) = -0x8000;
            }
            self->ext.lava.unk84 = 0x100;
        } else {
            self->ext.lava.unk84--;
        }

        if (primArr[0]->next->x1 < -0x50) {
            primArr[0]->next->x1 = primArr[12]->next->x1 + 0x20;
            primArr[13] = primArr[0];
            primArr[13]->drawMode &= ~DRAW_HIDE;

            for (j = 0; j < 13; j++) {
                primArr[j] = primArr[j + 1];
            }

            primArr[0]->drawMode |= DRAW_HIDE;
        }

        if (primArr[12]->next->x1 > 0x150) {
            primArr[12]->next->x1 = primArr[0]->next->x1 - 0x20;
            for (j = 13; j > 0; j--) {
                primArr[j] = primArr[j - 1];
            }

            primArr[0] = primArr[13];
            primArr[0]->drawMode |= DRAW_HIDE;
            primArr[0]->next->r3 = 0;
            LOW(primArr[0]->next->r1) = 0;
            primArr[0]->next->y0 = self->posY.i.hi;
            primArr[0]->next->x0 = 0;
            primArr[1]->drawMode &= ~DRAW_HIDE;
        }

        prim = primArr[0];
        if (!(g_Timer % 3)) {
            if (LOBU(prim->next->priority)) {
                LOH(prim->next->tpage) += 1;
            } else {
                LOH(prim->next->tpage) -= 1;
            }

            if (LOH(prim->next->tpage) > 0x10) {
                LOBU(prim->next->priority) = 0;
            }
            if (LOH(prim->next->tpage) < -0x10) {
                LOBU(prim->next->priority) = 1;
            }
        }

        SetGeomScreen(0x400);
        SetGeomOffset(0x80, self->posY.i.hi + 0x40);
        sVec.vx = 0;
        sVec.vy = LOH(prim->next->tpage);
        if (self->params & 2) {
            sVec.vy += 0x800;
        }
        sVec.vz = 0;
        RotMatrix(&D_us_8018130C, &matrix);
        RotMatrixY(sVec.vy, &matrix);
        SetRotMatrix(&matrix);
        vec.vx = prim->next->x1 - 0x80;
        vec.vy = -0x40;
        vec.vz = 0x400;
        TransMatrix(&matrix, &vec);
        SetTransMatrix(&matrix);

        if (prim->next->r3) {
            LOW(prim->next->x0) -= LOW(prim->next->r1);
            LOW(prim->next->r1) += 0x400;
            if (LOW(prim->next->r1) == 0x8400) {
                prim->next->r3 = 0;
            }
            if (!LOW(prim->next->r1)) {
                nextPrim = primArr[1];
                nextPrim->next->r3 = 1;
                LOW(nextPrim->next->r1) = -0x8000;
            }
        }

        prim->x1 = prim->next->x1;
        prim->y1 = prim->next->y0;
        RotTransPers(&D_us_801812FC, (long*)&prim->x3, &p, &flag);

        for (prevPrim = prim, i = 1; i < 13; prevPrim = prim, i++) {
            prim = primArr[i];
            if (!(g_Timer % 3)) {
                if (LOBU(prim->next->priority)) {
                    LOH(prim->next->tpage) += 1;
                } else {
                    LOH(prim->next->tpage) -= 1;
                }

                if (LOH(prim->next->tpage) > 0x10) {
                    LOBU(prim->next->priority) = 0U;
                }
                if (LOH(prim->next->tpage) < -0x10) {
                    LOBU(prim->next->priority) = 1;
                }
            }

            sVec.vx = 0;
            sVec.vy = LOH(prim->next->tpage);
            if (self->params & 2) {
                sVec.vy += 0x800;
            }
            sVec.vz = 0;
            RotMatrix(&D_us_8018130C, &matrix);
            RotMatrixY(sVec.vy, &matrix);
            SetRotMatrix(&matrix);
            vec.vx = prim->next->x1 - 0x80;
            vec.vy = -0x40;
            vec.vz = 0x400;
            TransMatrix(&matrix, &vec);
            SetTransMatrix(&matrix);

            if (prim->next->r3) {
                LOW(prim->next->x0) -= LOW(prim->next->r1);
                LOW(prim->next->r1) += 0x400;
                if (LOW(prim->next->r1) == 0x8400) {
                    prim->next->r3 = 0;
                }

                if (!LOW(prim->next->r1) && i < 9) {
                    nextPrim = primArr[i + 1];
                    nextPrim->next->r3 = 1;
                    LOW(nextPrim->next->r1) = -0x8000;
                }
            }

            prim->x0 = prevPrim->x1;
            prim->y0 = prevPrim->y1;
            prim->x2 = prevPrim->x3;
            prim->y2 = prevPrim->y3;
            prim->x1 = prim->next->x1;
            prim->y1 = prim->next->y0;
            RotTransPers(&D_us_801812FC, (long*)&prim->x3, &p, &flag);
        }

        break;
    }
}

static void FadeOutEmber(Primitive* prim) {
    if (g_Timer % prim->u3) {
        return;
    }
    prim->y0++;

    if (prim->y0 > prim->u2 + 0x70) {
        prim->r0 -= 2;
        prim->g0 -= 2;
        prim->b0 -= 7;
    }

    if (prim->b0 < 8) {
        prim->p3 = 0;
        prim->drawMode = DRAW_HIDE;
    }
}

extern Primitive* FindFirstUnkPrim(Primitive* prim);
void EntityLavaEmbers(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.func_800EDB58(PRIM_TILE_ALT, 0x14);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;
            while (prim != NULL) {
                self->ext.lava.emberPrim = prim;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        // fallthrough
    case 1:
        if (!(g_Timer % 7)) {
            prim = self->ext.prim;
            prim = FindFirstUnkPrim(prim);
            if (1) {
                prim->p3 = 2;
                prim->x0 = Random() & 0xFF;
                prim->y0 = 0;
                prim->u0 = prim->v0 = 1;
                prim->priority = 0xA9;
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
                prim->r0 = 0xA0;
                prim->g0 = 0x60;
                prim->b0 = 0xF0;
                prim->u2 = (Random() & 0x1F) + 0x10;
                prim->u3 = (Random() & 3) + 2;
            }
        }

        prim = self->ext.prim;
        while (prim != NULL) {
            if (prim->p3) {
                FadeOutEmber(prim);
            }
            prim = prim->next;
        }

        prim = self->ext.lava.emberPrim;
        prim->x0 = 0x10;
        prim->y0 = 0x10;
        prim->u0 = 0;
        prim->v0 = 0;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        break;
    }
}

void EntityCavernBackgroundLossoth(Entity* self) {
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
        i = 0;
        primIndex = g_api.func_800EDB58(PRIM_GT4, 0x15);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;
            while (prim != NULL) {
                prim->tpage = 0xF;
                prim->clut = 0x224;
                prim->u0 = 0x85;
                prim->u1 = 0xC3;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->priority = 0x1F;
                prim->drawMode = DRAW_UNK_400 | DRAW_COLORS | DRAW_UNK02;
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
            RotMatrix(&D_us_80181334, &matrix);
            RotMatrixX(r, &matrix);
            sp48.vx = (i * 64) + posX - 0x80;
            sp48.vy = 0x68;
            sp48.vz = 0xC8;
            TransMatrix(&matrix, &sp48);
            SetRotMatrix(&matrix);
            SetTransMatrix(&matrix);
            RotTransPers(&D_us_80181314, &((long*)SPAD(0))[i * 4], &p, &flag);
            RotTransPers(&D_us_8018131C, &((long*)SPAD(1))[i * 4], &p, &flag);

            RotMatrix(&D_us_80181334, &matrix);
            RotMatrixX(0x2AA, &matrix);
            sp48.vx = (i * 64) + posX - 0x80;
            sp48.vy = -0x40;
            sp48.vz = 0xC8;
            TransMatrix(&matrix, &sp48);
            SetRotMatrix(&matrix);
            SetTransMatrix(&matrix);
            RotTransPers(&D_us_80181324, &((long*)SPAD(2))[i * 4], &p, &flag);
            RotTransPers(&D_us_8018132C, &((long*)SPAD(3))[i * 4], &p, &flag);
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

void EntityCavernBackgroundDiscusLord(Entity* self) {
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
        self->posY.i.hi = 0x80 - g_Tilemap.scrollY.i.hi;
        // fallthrough
    case 1:
        i = 0;
        primIndex = g_api.func_800EDB58(PRIM_GT4, 0x15);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;
            while (prim != NULL) {
                prim->tpage = 0xF;
                prim->clut = 0x224;
                prim->u0 = 0x85;
                prim->u1 = 0xC3;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->priority = 0x1F;
                prim->drawMode = DRAW_UNK_400 | DRAW_COLORS | DRAW_UNK02;
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
            RotMatrix(&D_us_8018135C, &matrix);
            RotMatrixX(r, &matrix);
            sp48.vx = (i * 64) + posX - 0x80;
            sp48.vy = 0x80;
            sp48.vz = 0xC8;
            TransMatrix(&matrix, &sp48);
            SetRotMatrix(&matrix);
            SetTransMatrix(&matrix);
            RotTransPers(&D_us_8018133C, &((long*)SPAD(0))[i * 4], &p, &flag);
            RotTransPers(&D_us_80181344, &((long*)SPAD(1))[i * 4], &p, &flag);

            RotMatrix(&D_us_8018135C, &matrix);
            RotMatrixX(0x40, &matrix);
            sp48.vx = (i * 64) + posX - 0x80;
            sp48.vy = -0x38;
            sp48.vz = 0xC8;
            TransMatrix(&matrix, &sp48);
            SetRotMatrix(&matrix);
            SetTransMatrix(&matrix);
            RotTransPers(&D_us_8018134C, &((long*)SPAD(2))[i * 4], &p, &flag);
            RotTransPers(&D_us_80181354, &((long*)SPAD(3))[i * 4], &p, &flag);
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

void EntitySpikeRoomDarkness(Entity* self) {
    Entity* newEntity;
    Primitive* prim;
    Entity* entity;
    s32 i;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        if (!g_CastleFlags[RCAT_SPIKE_ROOM_LIT]) {
            entity = &PLAYER;
            entity->zPriority = 0xD8;
            g_unkGraphicsStruct.g_zEntityCenter = 0xD8;

            for (i = 0; i < 0x300; i++) {
                if (!g_Tilemap.fg[i]) {
                    g_Tilemap.fg[i] = 0xFF0;
                }
            }

            for (i = 0; i < 0x300; i++) {
                if (!g_BgLayers[0].layout[i]) {
                    g_BgLayers[0].layout[i] = 0xFF0;
                }
            }
        } else {
            DestroyEntity(self);
            return;
        }

        primIndex = g_api.func_800EDB58(PRIM_G4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.spikes.prim = prim;

        prim->x2 = prim->x0 = 0;
        prim->x3 = prim->x1 = 0x100;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0x100;
        prim->r0 = 0x68;
        prim->g0 = 0x68;
        prim->b0 = 0x68;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0xD0;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        prim = prim->next;

        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0x300 - g_Tilemap.scrollX.i.hi;
        prim->x1 = prim->x3 = 0x240 - g_Tilemap.scrollX.i.hi;
        prim->y0 = prim->y1 = 0 - g_Tilemap.scrollY.i.hi;
        prim->y2 = prim->y3 = 0xF0 - g_Tilemap.scrollY.i.hi;
        PGREY(prim, 0) = 0x80;
        LOW(prim->r2) = LOW(prim->r0);
        PGREY(prim, 1) = 0;
        LOW(prim->r3) = LOW(prim->r1);
        prim->priority = 0xCE;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        i = 0;
        // fallthrough
    case 1:
        for (entity = &g_Entities[0], i = 0; i < STAGE_ENTITY_START; i++,
            entity++) {
            if (entity->entityId == 0x34 && !entity->ext.spikes.echoCooldown) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(E_ID(UNK_21), newEntity);
                    newEntity->posX.i.hi = entity->posX.i.hi;
                    newEntity->posY.i.hi = entity->posY.i.hi;
                    newEntity->facingLeft = entity->facingLeft;
                    newEntity->zPriority = 0x5F;
                    newEntity->params = 0;
                }

                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(E_ID(UNK_21), newEntity);
                    newEntity->posX.i.hi = entity->posX.i.hi;
                    newEntity->posY.i.hi = entity->posY.i.hi;
                    newEntity->facingLeft = entity->facingLeft;
                    newEntity->zPriority = 0x5F;
                    newEntity->params = 1;
                }
                entity->ext.spikes.echoCooldown = 0x40;
            }
        }

        break;
    }

    if (g_CastleFlags[RCAT_SPIKE_ROOM_LIT]) {
        DestroyEntity(self);
    }
}
