#include "chi.h"

/*
 * File: 1CBA8.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

extern EntityInit EntityInit_8018067C;
extern u16 g_Tilemap_scrollX_i_hi;

// [Entity]
// PSP:func_psp_0924B458:Match
void func_8019CBA8(Entity* self) {
    s32 tileIdx;        // s2
    s32 primIdx;        // s6
    Primitive* prim;    // s0
    Collider collider;
    Entity* entity;

    s32 i;              // s1
    s16 s3;             // s3
    s16 s4;

    switch (self->step) {
    case 0:
        InitializeEntity(&EntityInit_8018067C);
        self->zPriority = 0x6A;
        if (self->params) {
            self->animCurFrame = 6;
            tileIdx = 0xDF;
        } else {
            self->animCurFrame = 5;
            tileIdx = 0xC0;
        }
        for (i = 0; i < 4; tileIdx += 0x20, i++) {
            g_Tilemap.fg[tileIdx] = 0x32E;
        }
        primIdx = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (primIdx == -1) {
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIdx;
        prim = &g_PrimBuf[primIdx];
        self->ext.prim = prim;

        prim->tpage = 0xF;
        prim->clut = 0x1B;
        if (self->params) {
            prim->u0 = prim->u2 = 0xE3;
            prim->u1 = prim->u3 = 0xD3;
        } else {
            prim->u0 = prim->u2 = 0xD4;
            prim->u1 = prim->u3 = 0xE4;
        }
        prim->v0 = prim->v1 = 0x9C;
        prim->v2 = prim->v3 = 0xDC;

        if (self->params) {
            s3 = 0x1F0;
        } else {
            s3 = 0;
        }
        s3 = s3 - g_Tilemap.scrollX.i.hi;
        prim->x0 = prim->x2 = s3;
        prim->x1 = prim->x3 = s3 + 0x10;

        prim->y0 = prim->y1 = 0x1C;
        prim->y2 = prim->y3 = 0x5C;
        prim->priority = 0x6B;
        prim->drawMode = 2;
        prim = prim->next;

        while (prim != NULL) {
            prim->type = 1;
            prim->u0 = prim->v0 = 1;
            prim->r0 = 0x20;
            prim->g0 = 0x40;
            prim->b0 = 0x20;
            prim->priority = 0x6C;
            prim->drawMode = 8;
            prim = prim->next;
        }
        return;
    case 1:
        if (!(g_pads->pressed & 0x1000)) {
            return;
        }
        self->step++;
        return;
    case 2:
        self->posY.val += self->velocityY;
        self->velocityY += 0x8000;
        s3 = self->posX.i.hi;
        s4 = self->posY.i.hi + 0x22;
        if (self->posY.i.hi <= 0x60) {
            return;
        }
        g_api.CheckCollision(s3, s4, &collider, 0);
        if (collider.effects == 0) {
            return;
        }

        self->posY.i.hi += collider.unk18;
        self->velocityY = -self->velocityY;
        self->velocityY /= 4;

        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
            entity->posX.i.hi += -8 + (Random() & 7) * 2;
            entity->posY.i.hi += 0x20;
            entity->params = 0x10;
        }
        if (self->velocityY <= -0x2000) {
            return;
        }
        self->step++;
        return;
    case 3:
        if (self->params) {
            tileIdx = 0xDF;
        } else {
            tileIdx = 0xC0;
        }
        for (i = 0; i < 4; tileIdx += 0x20, i++) {
            g_Tilemap.fg[tileIdx] = 0x3A1;
        }
        self->step++;
        return;
    case 4:
        self->posY.val -= 0x4000;

        if (!(g_Timer & 7)) {
            if ((g_Timer & 1)) {
                prim = self->ext.prim;
                prim = prim->next;
                prim = FindFirstUnkPrim(prim);
                if (prim != NULL) {
                    prim->p3 = 1;

                    s3 = (self->posX.i.hi + (Random() & 0xF)) - 8;
                    s4 = 0x5C;
                    prim->x0 = s3;
                    prim->y0 = s4;
                    prim->drawMode = 2;
                }
            }
        }

        s4 = (0x7A - self->posY.i.hi) >> 4;
        if (self->params) {
            tileIdx = 0x13F;
        } else {
            tileIdx = 0x120;
        }

        for (i = 0; i < s4; tileIdx -= 0x20, i++) {
            g_Tilemap.fg[tileIdx] = 0x32E;
        }
        self->ext.factory.unk80 = 0x20;
        if (self->posY.i.hi < 0x3A) {
            self->step++;
        }
        /* fallthrough */
    case 5:
        prim = self->ext.prim;
        while (prim != NULL) {
            if (prim->p3) {
                prim->y0 += 2;
                if (prim->y0 > 0xA0) {
                    prim->drawMode = 8;
                    prim->p3 = 0;
                }
            }
            prim = prim->next;
        }
        if (--self->ext.factory.unk80) {
            return;
        }
        DestroyEntity(self);
        return;
    default:
        return;
    }
}

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_8019D0D8);
{

    }


        prim->p2 = 0;
    }
}
