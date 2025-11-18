// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

static u8 lava_priorities[] = {0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0};
static s16 lava_tpages[] = {2, 8, -4, 0, -3, -10, 4, 12, 0, 7, 1, -8};
static SVECTOR lava_vec = {.vx = 0, .vy = 0, .vz = -512, .pad = 0};
static SVECTOR unused = {.vx = 0, .vy = 0, .vz = -512, .pad = 0};

// BSS
static SVECTOR empty = {0};
#ifdef VERSION_US
static Primitive* main_lava_prims[14];
static Primitive* top_layer_prims[14];
#else
static Primitive* main_lava_prims[14] = {0};
static Primitive* top_layer_prims[14] = {0};
#endif

// Params 0 = Lossoth rooms, non-transparent, spawns embers
// Params non-0 = Discus Lord room, transparent, no embers
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
        primArr = top_layer_prims;
    } else {
        primArr = main_lava_prims;
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

        // Top layer of the lava sits behind the Discus Lord platform
        // The rest sits in front of it as a transparent layer
        if (self->params & 2) {
            self->zPriority -= 8;
        }

        self->ext.lava.clut = PAL_LAVA_OPAQUE;
        if (self->params) {
            self->ext.lava.clut = PAL_LAVA_TRANSPARENT;
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
                prim->clut = PAL_LAVA_TRANSPARENT;
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
            LOBU(prim->next->priority) = lava_priorities[i];
            prim->next->tpage = lava_tpages[i];
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
        SetGeomOffset(0x80, self->posY.i.hi - 0x40);
        sVec.vx = 0;
        sVec.vy = LOH(prim->next->tpage);
        if (self->params & 2) {
            sVec.vy += 0x800;
        }
        sVec.vz = 0;
        RotMatrix(&empty, &matrix);
        RotMatrixY(sVec.vy, &matrix);
        SetRotMatrix(&matrix);
        vec.vx = prim->next->x1 - 0x80;
        vec.vy = 0x40;
        vec.vz = 0x400;
        TransMatrix(&matrix, &vec);
        SetTransMatrix(&matrix);

        if (prim->next->r3) {
            LOW(prim->next->x0) += LOW(prim->next->r1);
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
        RotTransPers(&lava_vec, (long*)&prim->x3, &p, &flag);

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
            RotMatrix(&empty, &matrix);
            RotMatrixY(sVec.vy, &matrix);
            SetRotMatrix(&matrix);
            vec.vx = prim->next->x1 - 0x80;
            vec.vy = 0x40;
            vec.vz = 0x400;
            TransMatrix(&matrix, &vec);
            SetTransMatrix(&matrix);

            if (prim->next->r3) {
                LOW(prim->next->x0) += LOW(prim->next->r1);
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
            RotTransPers(&lava_vec, (long*)&prim->x3, &p, &flag);
        }

        break;
    }
}

static void FadeOutEmber(Primitive* prim) {
    if (g_Timer % prim->u3) {
        return;
    }
    prim->y0--;

    if (prim->y0 < prim->u2 + 144) {
        prim->r0 -= 8;
        prim->g0 -= 4;
        prim->b0 -= 4;
    }

    // Once we hit a color threshold, the ember has "burnt out"
    // and is hidden
    if (prim->r0 < 8) {
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
        // Spawn the embers at various random positions
        if (!(g_Timer % 7)) {
            prim = self->ext.prim;
            prim = FindFirstUnkPrim(prim);
#ifdef VERSION_PSP
            if (prim != NULL) {
#else
            if (1) {
#endif
                prim->p3 = 2;
                prim->x0 = Random() & 0xFF;
                prim->y0 = 0x100;
                prim->u0 = prim->v0 = 1;
                prim->priority = 0xA9;
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
                prim->r0 = 0xF0;
                prim->g0 = 0xC0;
                prim->b0 = 0x80;
                prim->u2 = (Random() & 0x1F) + 0x10;
                prim->u3 = (Random() & 3) + 2;
            }
        }

        // Embers rise up and change colour and eventually burn out to nothing
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
