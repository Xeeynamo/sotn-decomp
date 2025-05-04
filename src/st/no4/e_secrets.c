// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

typedef enum {
    BREAKABLE_CRYSTAL_FLOOR_INIT,
    BREAKABLE_CRYSTAL_FLOOR_IDLE,
    BREAKABLE_CRYSTAL_FLOOR_BREAK,
    BREAKABLE_CRYSTAL_FLOOR_CHECK
} BREAKABLE_CRYSTAL_FLOOR_STEPS;

extern s16 D_us_80181880[];

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
        tileLayoutPtr = &D_us_80181880[i];
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
        self->ext.breakableCrystalFloor.breakCount++;
        tileLayoutPtr =
            &D_us_80181880[self->ext.breakableCrystalFloor.breakCount * 6];
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
        self->ext.breakableCrystalFloor.resetTimer = 32;
        self->step += 1;
        if (self->ext.breakableCrystalFloor.breakCount == 3) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 0x13;
            }
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            g_CastleFlags[NO4_SECRET_FLOOR_OPEN] = 1;
            g_api_func_800F1FC4(NO4_SECRET_FLOOR_OPEN);
            DestroyEntity(self);
            return;
        }
        break;
    case BREAKABLE_CRYSTAL_FLOOR_CHECK:
        // Wait for cooldown to finish, then switch to idle state
        if (!--self->ext.breakableCrystalFloor.resetTimer) {
            self->step = BREAKABLE_CRYSTAL_FLOOR_IDLE;
            return;
        }
        break;
    }
}

// NO4_SECRET_WALL_OPEN
INCLUDE_ASM("st/no4/nonmatchings/e_secrets", func_us_801C89F4);

INCLUDE_ASM("st/no4/nonmatchings/e_secrets", func_us_801C8CC4);
