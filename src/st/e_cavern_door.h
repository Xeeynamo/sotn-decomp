// SPDX-License-Identifier: AGPL-3.0-or-later
#ifdef VERSION_PSP
extern s32 E_ID(CAVERN_DOOR_PLATFORM);
#endif

#include "door_cascade_physics.h"

// lever and platform to open caverns door
void EntityCavernDoorLever(Entity* self) {
    s32 posX;
    s32 posY;
    Entity* platform;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitStInteractable);
        self->animCurFrame = 18;
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->rotate = -0x200;
        platform = self + 1;
        CreateEntityFromEntity(E_ID(CAVERN_DOOR_PLATFORM), self, platform);
        if (g_CastleFlags[NO4_TO_NP3_SHORTCUT]) {
            self->rotate = 0;
        }

    case 1:
        platform = self + 1;
        if (platform->ext.cavernDoor.collision) {
            self->rotate += 4;
            if (self->rotate > 0) {
                self->rotate = 0;
                if (!g_CastleFlags[NO4_TO_NP3_SHORTCUT]) {
                    g_api.PlaySfx(SFX_LEVER_METAL_BANG);
                }
                g_CastleFlags[NO4_TO_NP3_SHORTCUT] = 1;
            } else if (!(g_Timer & 0xF)) {
                g_api.PlaySfx(SFX_LEVER_METAL_BANG);
            }
        }
        break;
    }
    platform = self + 1;
    posX = self->posX.val;
    posY = self->posY.val;
    posX += rcos(self->rotate) * 0x28 << 4;
    posY += rsin(self->rotate) * 0x28 << 4;
    platform->posX.val = posX;
    platform->posY.val = posY;
}

// platform attached to lever at cavern door
void EntityCavernDoorPlatform(Entity* self) {
    Entity* player;
    s32 collision;
    s32 xDiff;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitStInteractable);
        self->animCurFrame = 17;
        self->ext.cavernDoor.xCoord.val = self->posX.val;
        self->ext.cavernDoor.xCoord.val = self->posX.val; // ? WTF

    case 1:
        collision = GetPlayerCollisionWith(self, 6, 5, 4);
        self->ext.cavernDoor.collision = collision;

        if (collision != 0) {
            xDiff = self->posX.i.hi - FIX_TO_I(self->ext.cavernDoor.xCoord.val);
            player = &PLAYER;
            player->posX.i.hi += xDiff;
            player->posY.i.hi += 1;
// Need to identify this var, and see why it's in NP3 but not NO3
#if !defined(STAGE_IS_NO3)
            D_80097488.x.i.hi += xDiff;
            D_80097488.y.i.hi += 1;
#endif
        }
        self->ext.cavernDoor.xCoord.val = self->posX.val;
        self->ext.cavernDoor.yCoord.val = self->posY.val;
    }
}

static s16 cavernDoorTiles[] = {0x6D0, 0x04FA, 0x04FA, 0x0551, 0, 0};

// door blocking way to the Underground Caverns
void EntityCavernDoor(Entity* self) {
    s32 primIndex;
    s16* tileLayoutPtr;
    Entity* entity;
    Primitive* prim;
    s32 i;
    s32 tilePos;
    s32 tileSteps;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitStInteractable);
        self->animCurFrame = 10;
        self->zPriority = 0x9F;

        tileLayoutPtr = &cavernDoorTiles[0];
        if (g_CastleFlags[NO4_TO_NP3_SHORTCUT]) {
            self->step = 128;
            self->animCurFrame = 0;
            tileLayoutPtr += 3;
        } else {
            primIndex = g_api.AllocPrimitives(PRIM_TILE, 64);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.cavernDoor.prim = prim;
            while (prim != NULL) {
                prim->u0 = prim->v0 = 1;
                prim->r0 = 64;
                prim->b0 = 128;
                prim->g0 = 96;
                prim->priority = self->zPriority + 0x18;
                prim->drawMode = DRAW_HIDE;
                prim->p3 = 0;
                prim = prim->next;
            }
        }

        for (tilePos = 0x76, i = 0; i < 3; i++) {
            g_Tilemap.fg[tilePos] = *tileLayoutPtr++;
            tilePos += 0x10;
        }
        break;

    case 1:
        if (g_CastleFlags[NO4_TO_NP3_SHORTCUT]) {
#if defined(STAGE_IS_NO3)
            g_api.PlaySfx(SFX_SWITCH_CLICK);
#endif
            self->step++;
        }
        break;

    case 2:
        self->posY.val += FIX(0.375);
        self->ext.cavernDoor.jiggler++;
        // While the door opens, it jiggles left and right by repeatedly
        // incrementing and decrementing its x position.
        if (self->ext.cavernDoor.jiggler & 1) {
            self->posX.i.hi++;
        } else {
            self->posX.i.hi--;
        }

        tileSteps = (self->posY.i.hi - 136);
        tileSteps /= 16;
        if (tileSteps > 3) {
            tileSteps = 3;
            self->step = 3;
        }
#if !defined(STAGE_IS_NO3)
        if (!(self->ext.cavernDoor.jiggler & 15)) {
            g_api.PlaySfx(SFX_STONE_MOVE_C);
        }
#endif
        tilePos = 0x76;
        tileLayoutPtr = &cavernDoorTiles[0];
        tileLayoutPtr += 3;
        for (i = 0; i < tileSteps; tilePos += 0x10, i++) {
            g_Tilemap.fg[tilePos] = *tileLayoutPtr++;
        }

        if (g_Timer & 1) {
            break;
        }
        prim = self->ext.cavernDoor.prim;
        prim = FindFirstUnkPrim(prim);
        if (prim != NULL) {
            prim->p3 = 1;
        }

        if (g_Timer & 15) {
            break;
        }
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity == NULL) {
            break;
        }
        CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
        entity->posY.i.hi = 156;
        entity->posX.i.hi += -8 + (Random() & 15);
        entity->zPriority = self->zPriority + 2;
        entity->params = 0x10;
        entity->drawFlags |= (FLAG_DRAW_SCALEX + FLAG_DRAW_SCALEY);
        entity->scaleX = entity->scaleY = 192;
        break;
    }

    if (self->flags & FLAG_HAS_PRIMS) {
        for (prim = self->ext.cavernDoor.prim; prim != NULL;
             prim = prim->next) {
            if (prim->p3) {
                DoorCascadePhysics((EntranceCascadePrim*)prim);
            }
        }
    }
}
