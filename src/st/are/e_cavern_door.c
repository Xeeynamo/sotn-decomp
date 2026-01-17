// SPDX-License-Identifier: AGPL-3.0-or-later
#include "are.h"

extern EInit g_EInitCavernDoor;

#include "../door_cascade_physics.h"

void EntityCavernDoorSwitch(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    DRAWENV sp10;
    RECT clipRect;
    DR_ENV* dr_env;
    s32 temp_t1;
    Entity* player;
    s32 collision;

    collision = GetPlayerCollisionWith(self, 8, 4, 4);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCavernDoor);
        self->animCurFrame = 2;
        self->zPriority = 0x71;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.cavernDoor.prim = prim;

        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (dr_env == NULL) {
            DestroyEntity(self);
            return;
        }

        prim->type = PRIM_ENV;
        sp10 = g_CurrentBuffer->draw;
        sp10.isbg = 0;
        sp10.r0 = 0;
        sp10.g0 = 0;
        sp10.b0 = 0;
        sp10.dtd = 0;
        sp10.ofs[0] = 0;
        clipRect.x = 0;
        clipRect.w = 256;
        clipRect.y = 20;
        clipRect.h = 0xCF;
        sp10.clip = clipRect;
        SetDrawEnv(dr_env, &sp10);
        prim->priority = 0x70;
        prim->drawMode = DRAW_UNK_1000 | DRAW_HIDE;
        prim = prim->next;
        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (dr_env == NULL) {
            DestroyEntity(self);
            return;
        }
        prim->type = PRIM_ENV;
        prim->drawMode = DRAW_UNK_800 | DRAW_HIDE;
        prim->priority = 0x72;
        prim = prim->next;

        if (g_CastleFlags[ARE_TO_DAI_SHORTCUT]) {
            self->posY.i.hi += 4;
            self->step = 2;
        }
        break;
    case 1:
        if (collision) {
            player = &PLAYER;
            player->posY.i.hi++;
            self->posY.val += FIX(0.25);
            temp_t1 = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (temp_t1 > 0xC1) {
                self->posY.i.hi = 0xC1 - g_Tilemap.scrollY.i.hi;
                g_CastleFlags[ARE_TO_DAI_SHORTCUT] = true;
                g_api.PlaySfx(SFX_SWITCH_CLICK);
                self->step++;
            }
        }
        break;
    }

    prim = self->ext.cavernDoor.prim;
    temp_t1 = 0xC0 - g_Tilemap.scrollY.i.hi;
    if (temp_t1 > 0xE3) {
        prim->drawMode |= DRAW_HIDE;
        prim = prim->next;
        prim->drawMode |= DRAW_HIDE;
    } else {
        dr_env = *((DR_ENV**)&prim->r1);
        sp10 = g_CurrentBuffer->draw;
        sp10.isbg = 0;
        sp10.ofs[0] = 0;
        clipRect.x = 0;
        clipRect.w = 256;
        clipRect.y = 0x14;
        clipRect.h = temp_t1 - 0x15;
        FntPrint("cut y:%x\n", clipRect.h + 0x15);
        sp10.clip = clipRect;
        SetDrawEnv(dr_env, &sp10);
        prim->drawMode = DRAW_UNK_1000;
        prim = prim->next;
        prim->drawMode = DRAW_UNK_800;
        prim = prim->next;
    }
}

extern Primitive* FindFirstUnkPrim(Primitive* prim);
// door blocking way to the Royal Chapel
void EntityCavernDoor(Entity* self) {
    Primitive* prim;
    Entity* entity;
    s32 posY;
    s32 primIndex;
    s32 collision;

    collision =
        GetPlayerCollisionWith(self, self->hitboxWidth, self->hitboxHeight, 5);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCavernDoor);
        self->animCurFrame = 1;
        self->zPriority = 0x71;
        self->hitboxWidth = 8;
        self->hitboxHeight = 0x38;
        if (g_CastleFlags[ARE_TO_DAI_SHORTCUT]) {
            self->step = 0x80;
            self->animCurFrame = 0;
            self->posY.i.hi += 0x80;
            break;
        }

        primIndex = g_api.AllocPrimitives(PRIM_TILE, 0x40);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = (s32)primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.cavernDoor.prim = prim;
        while (prim != NULL) {
            prim->u0 = prim->v0 = 1;
            prim->r0 = 0x40;
            prim->b0 = 0x80;
            prim->g0 = 0x60;
            prim->priority = self->zPriority + 0x18;
            prim->drawMode = DRAW_HIDE;
            prim->p3 = 0;
            prim = prim->next;
        }
        break;
    case 1:
        if (g_CastleFlags[ARE_TO_DAI_SHORTCUT]) {
            self->step++;
        }
        break;
    case 2:
        self->posY.val += FIX(0.375);
        self->ext.cavernDoor.jiggler++;
        // While the door opens, it jiggles left and right by repeatedly
        // incrementing and decrementing its x position.
        if (self->ext.cavernDoor.jiggler & 1) {
            self->posX.i.hi += 1;
        } else {
            self->posX.i.hi -= 1;
        }

        if (collision & 4) {
            entity = &PLAYER;
            entity->posY.i.hi++;
            D_80097488.y.i.hi++;
        }

        if (!(self->ext.cavernDoor.jiggler & 0xF)) {
            g_api.PlaySfx(SFX_STONE_MOVE_A);
        }

        posY = self->posY.i.hi - 0x70;
        posY /= 0x10;

        if (posY > 8) {
            self->hitboxWidth = self->hitboxHeight = 0;
            posY = 8;
            self->step = 3;
        }

        if (!(g_Timer & 1)) {
            prim = self->ext.cavernDoor.prim;
            prim = FindFirstUnkPrim(prim);
            if (prim != NULL) {
                prim->p3 = 1;
            }

            if (!(g_Timer & 0xF)) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
                    entity->posY.i.hi = 0xBC;
                    entity->posX.i.hi += (Random() & 0xF) - 8;
                    entity->params = 0x10;
                    entity->drawFlags |= FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
                    entity->scaleX = entity->scaleY = 0xC0;
                }
            }
        }
        break;
    }

    if (self->flags & FLAG_HAS_PRIMS) {
        prim = self->ext.cavernDoor.prim;
        while (prim != NULL) {
            if (prim->p3) {
                DoorCascadePhysics((EntranceCascadePrim*)prim);
            }
            prim = prim->next;
        }
    }
}
