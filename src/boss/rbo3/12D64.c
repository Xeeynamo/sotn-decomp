// SPDX-License-Identifier: AGPL-3.0-or-later

#include "rbo3.h"
extern EInit D_us_801804BC;
extern s32 D_us_8018072C;
extern u32 D_psp_09254D28;

void func_us_80192D64(Entity* self) {
    s32 i;
    s32 fg;
    s32 fgIndex;
    s32 y;
    Entity* next;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804BC);
        self->zPriority = 0x5C;
        if (self->params & 2) {
            self->animCurFrame = 0xE;
            return;
        }
        if (self->params & 1) {
            self->animCurFrame = 13;
            self->posX.i.hi = 48 - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = 224 - g_Tilemap.scrollY.i.hi;
        } else {
            self->animCurFrame = 12;
            self->posX.i.hi = 496 - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = 224 - g_Tilemap.scrollY.i.hi;
        }

        next = self + 1;
#ifdef VERSION_PSP
        CreateEntityFromEntity(D_psp_09254D28, self, next);
#else
        CreateEntityFromEntity(UNK_ENTITY_29, self, self + 1);
#endif

        next->params = 2;
        next->posY.i.hi = 96;
        if (self->params) {
            next->posX.i.hi -= 16;
        }
        break;

    case 1:
        if (D_us_8018072C) {
            if (self->params & 2) {
                self->step = 8;
                break;
            }
            if (self->params) {
                fgIndex = 0xC1;
            } else {
                fgIndex = 0xDE;
            }

            for (i = 0; i < 4; i++) {
                g_Tilemap.fg[fgIndex] = 0x4B3;
                fgIndex += 0x20;
            }

            self->step = 2;
        }
        break;

    case 2:
        self->posY.val -= FIX(1.125);
        if (self->posY.i.hi < 186) {
            self->posY.i.hi = 186;
            self->step++;
        }
        break;

    case 3:
        if (D_us_8018072C == 0) {
            if (self->params) {
                fgIndex = 0xC1;
            } else {
                fgIndex = 0xDE;
            }

            for (i = 0; i < 4; i++) {
                g_Tilemap.fg[fgIndex] = 0;
                fgIndex += 0x20;
            }
            self->step++;
        }
        break;
    case 4:
        self->posY.val += FIX(0.75);
        y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (y > 0xE0) {
            self->posY.i.hi = 0xE0 - g_Tilemap.scrollY.i.hi;
            self->step++;
        }
        break;

    case 5:
    case 6:
    case 7:
        break;
    case 8:
        self->posY.val += FIX(1.125);
        if (self->posY.i.hi > 127) {
            self->posY.i.hi = 127;
            self->step++;
        }
        break;
    case 9:
        if (D_us_8018072C == 0) {
            self->step++;
        }
        break;
    case 10:
        self->posY.val += FIX(-0.75);
        y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (y < 96) {
            self->posY.i.hi = 96 - g_Tilemap.scrollY.i.hi;
            self->step++;
        }
        break;
    case 11:
        break;
    }
}

extern EInit g_EInitInteractable;

void func_us_80193050(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 x;

    if (self->step != 0) {
        return;
    }

    InitializeEntity(g_EInitInteractable);
    primIndex = g_api.AllocPrimitives(PRIM_GT4, 5);

    if (primIndex == -1) {
        DestroyEntity(self);
        return;
    }

    prim = &g_PrimBuf[primIndex];
    self->primIndex = primIndex;
    self->flags |= FLAG_HAS_PRIMS;
    x = 0;

    while (prim != NULL) {
        prim->x0 = prim->x2 = x;
        x += 62;
        prim->x1 = prim->x3 = x;
        prim->tpage = 0xF;
        prim->clut = 0xC5;
        prim->u0 = prim->u2 = 65;
        prim->u1 = prim->u3 = 127;
        prim->v0 = prim->v1 = 169;
        prim->v2 = prim->v3 = 198;
        prim->y0 = prim->y1 = 64;
        prim->y2 = prim->y3 = 18;
        prim->priority = 0x10;
        prim->drawMode = DRAW_DEFAULT;

        prim = prim->next;
    }
}
