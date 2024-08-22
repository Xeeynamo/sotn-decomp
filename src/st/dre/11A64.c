// SPDX-License-Identifier: AGPL-3.0-only
/*
 * File: 11A64.c
 * Overlay: DRE
 * Description: Nightmare
 */

#include "dre.h"
#include "sfx.h"

// puts garbled hp max up text on screen
void EntityUnkId11(Entity* entity) {
    ObjInit* obj = (ObjInit*)&D_80180528[entity->params * 10];

    if (entity->step == 0) {
        InitializeEntity(g_eInitGeneric2);
        entity->animSet = obj->animSet;
        entity->zPriority = obj->zPriority;
        entity->unk5A = obj->unk5A;
        entity->palette = obj->palette;
        entity->drawFlags = obj->drawFlags;
        entity->drawMode = obj->drawMode;

        if (obj->unkC != 0) {
            entity->flags = obj->unkC;
        }

        if (entity->params == 1) {
            entity->rotY = 0x200;
            entity->rotX = 0x200;
        }
    }

    AnimateEntity(obj->unk10, entity);
}

void func_80191B44(Entity* entity) {
    s32 ret;
    u16* temp_v0_2;
    u16 temp_s1 = entity->params;
    u16 phi_v1;
    u16 unk;
    entity->unk6D[0] = 0;

    if (entity->step != 0) {
        switch (temp_s1) {
        case 4:
        case 5:
            if (g_Tilemap.x != 0) {
                return;
            }
            break;

        case 6:
            if (g_pads->pressed & PAD_TRIANGLE) {
                g_Tilemap.x = 0;
                g_Tilemap.width = 1280;
                entity->step++;
                return;
            }
            break;
        }

        if (entity->unk44 != 0) {
            ret = GetSideToPlayer();
            phi_v1 = entity->ext.generic.unk7C.s;
            if (phi_v1 != 0) {
                phi_v1 = (ret & 2) * 2;
            } else {
                phi_v1 = (ret & 1) * 4;
            }
            unk = 8;
            temp_s1 = (temp_s1 * unk) + phi_v1;
            temp_v0_2 = &D_80180590[temp_s1];
            g_Tilemap.x = *(temp_v0_2++);
            g_Tilemap.y = *(temp_v0_2++);
            g_Tilemap.width = *(temp_v0_2++);
            g_Tilemap.height = *(temp_v0_2++);
        }
    } else {
        InitializeEntity(D_801804A0);
        entity->ext.generic.unk7C.s = D_80180588[temp_s1];
        if (entity->ext.generic.unk7C.s != 0) {
            entity->hitboxWidth = D_80180580[temp_s1];
            entity->hitboxHeight = 16;
        } else {
            entity->hitboxWidth = 16;
            entity->hitboxHeight = D_80180580[temp_s1];
        }
    }
}

extern u16 g_eBreakableInit[];
extern u8* g_eBreakableAnimations[];
extern u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakableanimSets[];
extern u8 g_eBreakableDrawModes[];
void EntityBreakable(Entity* entity) {
    Entity* temp_v0;
    u16 temp_s0 = entity->params >> 0xC;

    if (entity->step != 0) {
        AnimateEntity(g_eBreakableAnimations[temp_s0], entity);
        if (entity->unk44 != 0) {
            g_api.PlaySfx(SFX_CANDLE_HIT);
            temp_v0 = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (temp_v0 != NULL) {
                CreateEntityFromCurrentEntity(2, temp_v0);
                temp_v0->params = g_eBreakableExplosionTypes[temp_s0];
            }
            ReplaceBreakableWithItemDrop(entity);
        }
    } else {
        InitializeEntity(g_eBreakableInit);
        entity->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 20;
        entity->drawMode = g_eBreakableDrawModes[temp_s0];
        entity->hitboxHeight = g_eBreakableHitboxes[temp_s0];
        entity->animSet = g_eBreakableanimSets[temp_s0];
    }
}

// clouds in the background ID 0x18
void EntityBackgroundClouds(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 camX, camY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGeneric);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 5);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0x6E - g_Tilemap.scrollY.i.hi;
        prim->y2 = prim->y3 = 0xF0;
        setRGB0(prim, 16, 16, 16);
        prim->priority = 0x20;
        prim->drawMode = DRAW_DEFAULT;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim = prim->next;
        camX = -g_Tilemap.scrollX.i.hi;
        camY = 32 - g_Tilemap.scrollY.i.hi;
        while (prim != 0) {
            prim->x0 = prim->x2 = camX;
            camX += 95;
            prim->x1 = prim->x3 = camX;
            prim->tpage = 0xF;
            prim->clut = 5;
            prim->u0 = prim->u2 = 0x84;
            prim->u1 = prim->u3 = 0xE3;
            prim->v0 = prim->v1 = 1;
            prim->v2 = prim->v3 = 0x4F;
            prim->y0 = prim->y1 = camY;
            prim->y2 = prim->y3 = camY + 0x4E;
            prim->priority = 0x20;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }
        break;

    case 255:
        /**
         * Debug: Press SQUARE / CIRCLE on the second controller
         * to advance/rewind current animation frame
         */
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params == 0) {
                self->animCurFrame++;
                self->params |= 1;
            } else {
                break;
            }
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s == 0) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
    g_GpuBuffers[0].draw.r0 = 40;
    g_GpuBuffers[0].draw.g0 = 24;
    g_GpuBuffers[0].draw.b0 = 24;
    g_GpuBuffers[1].draw.r0 = 40;
    g_GpuBuffers[1].draw.g0 = 24;
    g_GpuBuffers[1].draw.b0 = 24;
}
