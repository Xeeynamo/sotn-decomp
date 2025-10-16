// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

typedef enum {
    BREAKABLE_CRYSTAL_FLOOR_INIT,
    BREAKABLE_CRYSTAL_FLOOR_IDLE,
    BREAKABLE_CRYSTAL_FLOOR_BREAK,
    BREAKABLE_CRYSTAL_FLOOR_CHECK
} BREAKABLE_CRYSTAL_FLOOR_STEPS;

// clang-format off
static s16 crystal_floor_tile_layout[] = {
    // Phase 0
    0x054C, 0x054D, 0x054E,
    0x0180, 0x0551, 0x0552,
    // Phase 1
    0x054C, 0x0740, 0x0748,
    0x0180, 0x0551, 0x0552,
    // Phase 2
    0x054C, 0x074D, 0x074E,
    0x0180, 0x0551, 0x0552,
    // Phase 3
    0x055E, 0x0000, 0x0000,
    0x055F, 0x0000, 0x0000
};

static s16 breakable_wall_tile_layout[] = {
    // Phase 0
    0x030E, 0x0310, 0x0766, 0x0312,
    0x076B, 0x0319, 0x0323, 0x0310,
    // Phase 1
    0x076D, 0x0310, 0x076E, 0x0312,
    0x076F, 0x0319, 0x0770, 0x0310,
    // Phase 2
    0x0771, 0x0310, 0x0772, 0x0312,
    0x0773, 0x0319, 0x0774, 0x0310,
    // Phase 3
    0x030F, 0x0310, 0x0334, 0x0314,
    0x0327, 0x031B, 0x0351, 0x0352};
// clang-format on

#ifdef VERSION_PSP
extern s32 E_ID(BREAKABLE_WALL_DEBRIS);
#endif

void EntityBreakableCrystalFloor(Entity* self) {
    Entity* newEntity;
    s16* tileLayoutPtr;
    s32 tilePos;
    s32 i;

    // NOTE: Behind the breakable floor, the background layer is originally
    // empty in the tilemap data (all black)
    switch (self->step) {
    case BREAKABLE_CRYSTAL_FLOOR_INIT:
        // Overwrite the background tiles so when the floor is broken, the cave
        // wall is visible
        // Overwrite the foreground tiles based on whether the floor has
        // already been broken or not
        InitializeEntity(g_EInitInteractable);
        self->hitboxWidth = 16;
        self->hitboxHeight = 16;
        self->hitboxState = 2;
        if (g_CastleFlags[NO4_SECRET_FLOOR_OPEN]) {
            i = 0x12;
        } else {
            i = 0;
        }
        tileLayoutPtr = &crystal_floor_tile_layout[i];
        // Looks like a copy-paste bug
        tilePos = 0x2D3;
        tilePos = 0x2D3;
        (&g_BgLayers[0].layout[tilePos])[1] = 0x3FE;
        (&g_BgLayers[0].layout[tilePos])[2] = 0x3FF;
        (&g_BgLayers[0].layout[tilePos])[17] = 0x401;
        (&g_BgLayers[0].layout[tilePos])[18] = 0x402;
        for (i = 0; i < 2; i++, tileLayoutPtr += 3) {
            (&g_Tilemap.fg[tilePos])[0] = tileLayoutPtr[0];
            (&g_Tilemap.fg[tilePos])[1] = tileLayoutPtr[1];
            (&g_Tilemap.fg[tilePos])[2] = tileLayoutPtr[2];
            tilePos += 0x10;
        }
        if (g_CastleFlags[NO4_SECRET_FLOOR_OPEN]) {
            DestroyEntity(self);
            return;
        }
        // fallthrough
    case BREAKABLE_CRYSTAL_FLOOR_IDLE:
        // Initially, go into an idle state
        // When hit, process to the break-and-check states
        if (self->hitFlags) {
            self->step++;
        }
        break;
    case BREAKABLE_CRYSTAL_FLOOR_BREAK:
        // Update the tiles with every break and spawn puffs of smoke
        self->ext.breakable.breakCount++;
        tileLayoutPtr =
            &crystal_floor_tile_layout[self->ext.breakable.breakCount * 6];
        tilePos = 0x2D3;
        for (i = 0; i < 2; i++, tileLayoutPtr += 3) {
            (&g_Tilemap.fg[tilePos])[0] = tileLayoutPtr[0];
            (&g_Tilemap.fg[tilePos])[1] = tileLayoutPtr[1];
            (&g_Tilemap.fg[tilePos])[2] = tileLayoutPtr[2];
            tilePos += 0x10;
        }
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0x11;
        }
        // There is a cooldown of 32 frames between breaks
        self->ext.breakable.resetTimer = 32;
        self->step += 1;
        if (self->ext.breakable.breakCount == 3) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 0x13;
            }
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            g_CastleFlags[NO4_SECRET_FLOOR_OPEN] = 1;
            g_api.RevealSecretPassageAtPlayerPositionOnMap(
                NO4_SECRET_FLOOR_OPEN);
            DestroyEntity(self);
            return;
        }
        break;
    case BREAKABLE_CRYSTAL_FLOOR_CHECK:
        // Wait for cooldown to finish, then switch to idle state
        if (!--self->ext.breakable.resetTimer) {
            self->step = BREAKABLE_CRYSTAL_FLOOR_IDLE;
            return;
        }
        break;
    }
}

void EntityBreakableWall(Entity* self) {
    Entity* newEntity;
    s32 i;
    s32 tilePos;
    s16* tileLayoutPtr;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxWidth = 8;
        self->hitboxHeight = 0x20;
        self->hitboxState = 2;
        if (g_CastleFlags[NO4_SECRET_WALL_OPEN]) {
            i = 0x18;
        } else {
            i = 0;
        }
        tileLayoutPtr = &breakable_wall_tile_layout[i];
        tilePos = 0x60;

        for (i = 0; i < 4; tilePos += 0x10, i++, tileLayoutPtr += 2) {
            (&g_Tilemap.fg[tilePos])[0] = tileLayoutPtr[0];
            (&g_Tilemap.fg[tilePos])[1] = tileLayoutPtr[1];
        }

        if (g_CastleFlags[NO4_SECRET_WALL_OPEN]) {
            DestroyEntity(self);
            break;
        }
        // fallthrough
    case 1:
        if (self->hitFlags) {
            self->step++;
        }
        break;
    case 2:
        self->ext.breakable.breakCount++;
        tileLayoutPtr =
            &breakable_wall_tile_layout[self->ext.breakable.breakCount * 8];
        tilePos = 0x60;

        for (i = 0; i < 4; tilePos += 0x10, i++, tileLayoutPtr += 2) {
            (&g_Tilemap.fg[tilePos])[0] = tileLayoutPtr[0];
            (&g_Tilemap.fg[tilePos])[1] = tileLayoutPtr[1];
        }
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0x11;
        }
        self->ext.breakable.resetTimer = 0x14;
        self->step++;
        if (self->ext.breakable.breakCount == 3) {
            for (i = 0; i < 0x10; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(BREAKABLE_WALL_DEBRIS), self, newEntity);
                    newEntity->posX.i.hi += (Random() & 0xF) - 4;
                    newEntity->posY.i.hi += (i * 4) - 0x1F;
                    newEntity->velocityX = (Random() << 8) + FIX(0.5);
                    newEntity->params = 0;
                }
            }

            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            g_CastleFlags[NO4_SECRET_WALL_OPEN] = 1;
            g_api.RevealSecretPassageAtPlayerPositionOnMap(
                NO4_SECRET_WALL_OPEN);
            DestroyEntity(self);
        }
        break;
    case 3:
        if (!--self->ext.breakable.resetTimer) {
            self->step = 1;
        }
        break;
    }
}

void EntityBreakableWallDebris(Entity* self) {
    Collider collider;
    Entity* newEntity;
    s32 posX;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->drawFlags = FLAG_DRAW_ROTATE;
        self->animSet = ANIMSET_OVL(1);
        if (Random() & 1) {
            self->animCurFrame = 0x26;
        } else {
            self->animCurFrame = 0x27;
        }
        if (self->velocityX < 0) {
            self->facingLeft = 1;
        }
        // fallthrough
    case 1:
        MoveEntity();
        self->rotate += 0x20;
        if (self->params) {
            self->rotate += 0x20;
        }
        self->velocityY += FIX(0.125);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 6;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk18;
            if (self->velocityY < FIX(0.5)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, newEntity);
                    newEntity->params = 0x10;
                }
                DestroyEntity(self);
                break;
            }

            self->velocityY = (-self->velocityY * 2) / 3;
        }
        break;
    }
}
