/*
 * File: en_debug_cerberus_gate.c
 * Overlay: CHI
 * Description: ENTITY - DEBUG Cerberus Gate
 */

#include "chi.h"

// E_CERBERUS_GATE_DEBUG
// params: True to use version for right side
// func_8019CBA8
// https://decomp.me/scratch/BFa12
// PSP:func_psp_0924B458:Match
// PSP:https://decomp.me/scratch/IWYbc
void EntityCerberusGateDebug(Entity* self) {
    typedef enum Step {
        INIT = 0,
        WAIT_FOR_INPUT = 1,
        DROP = 2,
        ADD_COLLISION = 3,
        RAISE = 4,
        WAIT_TO_DESTROY = 5,
    };

    s32 tileIdx;
    s32 primIdx;
    Primitive* prim;
    Collider collider;
    Entity* entity;

    s32 i;
    s16 x;
    s16 y;

    switch (self->step) {
    case INIT:
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
            x = 0x1F0;
        } else {
            x = 0;
        }
        x = x - g_Tilemap.scrollX.i.hi;
        prim->x0 = prim->x2 = x;
        prim->x1 = prim->x3 = x + 0x10;

        prim->y0 = prim->y1 = 0x1C;
        prim->y2 = prim->y3 = 0x5C;
        prim->priority = 0x6B;
        prim->drawMode = DRAW_UNK02;
        prim = prim->next;

        while (prim != NULL) {
            prim->type = 1;
            prim->u0 = prim->v0 = 1;
            prim->r0 = 0x20;
            prim->g0 = 0x40;
            prim->b0 = 0x20;
            prim->priority = 0x6C;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        return;

    case WAIT_FOR_INPUT:
        if (!(g_pads->pressed & PAD_UP)) {
            return;
        }
        self->step++;
        return;

    case DROP:
        self->posY.val += self->velocityY;
        self->velocityY += 0x8000;
        x = self->posX.i.hi;
        y = self->posY.i.hi + 0x22;
        if (self->posY.i.hi <= 0x60) {
            return;
        }
        g_api.CheckCollision(x, y, &collider, 0);
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

    case ADD_COLLISION:
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

    case RAISE:
        self->posY.val -= 0x4000;

        if (!(g_Timer & 7)) {
            if ((g_Timer % 2)) {
                prim = self->ext.prim;
                prim = prim->next;
                prim = FindFirstUnkPrim(prim);
                if (prim != NULL) {
                    prim->p3 = 1;

                    x = (self->posX.i.hi + (Random() & 0xF)) - 8;
                    y = 0x5C;
                    prim->x0 = x;
                    prim->y0 = y;
                    prim->drawMode = DRAW_UNK02;
                }
            }
        }

        y = (0x7A - self->posY.i.hi) >> 4;
        if (self->params) {
            tileIdx = 0x13F;
        } else {
            tileIdx = 0x120;
        }

        for (i = 0; i < y; tileIdx -= 0x20, i++) {
            g_Tilemap.fg[tileIdx] = 0x32E;
        }
        self->ext.debugCerberusGate.timer = 0x20;
        if (self->posY.i.hi < 0x3A) {
            self->step++;
        }
        /* fallthrough */
    case WAIT_TO_DESTROY:
        prim = self->ext.prim;
        while (prim != NULL) {
            if (prim->p3) {
                prim->y0 += 2;
                if (prim->y0 > 0xA0) {
                    prim->drawMode = DRAW_HIDE;
                    prim->p3 = 0;
                }
            }
            prim = prim->next;
        }
        if (--self->ext.debugCerberusGate.timer) {
            return;
        }
        DestroyEntity(self);
        return;
    }
}