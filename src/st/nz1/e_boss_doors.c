// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

extern EInit g_EInitInteractable;
s32 D_us_80181134 = 0;
s32 D_us_80181138 = 0;

void EntityBossDoorTrigger(Entity* self) {
    Entity* entity;
    s32 timeAttackResult;
    s32 scrollX;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        timeAttackResult = g_api.TimeAttackController(
            TIMEATTACK_EVENT_KARASUMAN_DEFEAT, TIMEATTACK_GET_RECORD);
        if (timeAttackResult) {
            DestroyEntity(self);
            return;
        }
        entity = &g_Entities[80];
        CreateEntityFromCurrentEntity(E_ID(KARASUMAN), entity);
        entity->posX.i.hi = 128 - g_Tilemap.scrollX.i.hi;
        entity->posY.i.hi = 176 - g_Tilemap.scrollY.i.hi;
        // fallthrough

    case 1:
        entity = &PLAYER;
        scrollX = entity->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (!g_Player.demo_timer) {
            D_us_80181138 |= 1;
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_KARASUMAN_DEFEAT, TIMEATTACK_SET_VISITED);
            self->step++;
        }
        break;

    case 2:
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_ID(BOSS_DOORS), entity);
        entity->posX.i.hi = -8 - g_Tilemap.scrollX.i.hi;
        entity->posY.i.hi = 128 - g_Tilemap.scrollY.i.hi;
        entity->params = 0;
        entity = self + 2;
        CreateEntityFromCurrentEntity(E_ID(BOSS_DOORS), entity);
        entity->posX.i.hi = 264 - g_Tilemap.scrollX.i.hi;
        entity->posY.i.hi = 128 - g_Tilemap.scrollY.i.hi;
        entity->params = 1;
        D_us_80181134 = 1;
        self->step++;
        // fallthrough

    case 3:
        if (g_api.func_80131F68() != false) {
            g_api.PlaySfx(SET_UNK_90);
        }
        stopMusicFlag = true;
        currentMusicId = MU_FESTIVAL_OF_SERVANTS;
        self->step++;
        break;

    case 4:
        if (g_api.func_80131F68() == false) {
            stopMusicFlag = false;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        // fallthrough
    case 5:
        if (D_us_80181138 & 2) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_KARASUMAN_DEFEAT, TIMEATTACK_SET_RECORD);
            if (g_api.func_80131F68() != false) {
                g_api.PlaySfx(SET_UNK_90);
            }
            currentMusicId = MU_THE_TRAGIC_PRINCE;
            self->step++;
        }
        break;
    case 6:
        if (D_us_80181138 & 4) {
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(LIFE_UP_SPAWN), self, entity);
                entity->posX.i.hi = 128;
                entity->posY.i.hi = 128;
                entity->params = 7;
                D_us_80181134 = 0;
                stopMusicFlag = true;
                currentMusicId = MU_THE_TRAGIC_PRINCE;
                self->step++;
            }
        }
        break;
    case 7:
        if (g_api.func_80131F68() == false) {
            stopMusicFlag = 0;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        break;
    }
}

static s16 D_us_8018113C[] = {
    0x56A, 0x56B, 0x570, 0x571, 0x572, 0x573, 0x574, 0x577,
};

// n.b.! this is included in `us` but unused. PSP fixes this.
static s16 D_pspeu_092637C8[] = {
    0x135, 0x138, 0x142, 0x138, 0x13A, 0x13D, 0x10A, 0xE1,
};

void EntityBossDoors(Entity* self) {
    s16* doorTilemap;
    Entity* entity;
    s32 offsetX;
    s32 tileIndex;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnvironment);
        self->animCurFrame = 7;
        self->zPriority = 0x78;
        break;

    case 1:
        if (D_us_80181134) {
            self->step++;
        }
        break;

    case 2:
        GetPlayerCollisionWith(self, 8, 32, 5);
        if (self->params) {
            self->velocityX = FIX(-0.5);
        } else {
            self->velocityX = FIX(0.5);
        }

        MoveEntity();
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
            entity->params = 0x10;
            entity->posY.i.hi += 32;
            entity->posX.i.hi -= (Random() & 7);
        }
        if (!(g_Timer & 0xF)) {
            g_api.PlaySfx(SFX_STONE_MOVE_B);
        }
        offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (self->params) {
            if (offsetX < 238) {
                self->step++;
            }
        } else if (offsetX > 18) {
            self->step++;
        }
        break;

    case 3:
        doorTilemap = D_us_8018113C;
        if (self->params) {
            tileIndex = 0x6E;
            doorTilemap += 4;
        } else {
            tileIndex = 0x61;
        }
        for (i = 0; i < 4; i++, doorTilemap++, tileIndex += 16) {
            g_Tilemap.fg[tileIndex] = *doorTilemap;
        }
        self->step++;
        // fallthrough

    case 4:
        if (!D_us_80181134) {
#ifdef VERSION_PSP
            doorTilemap = D_pspeu_092637C8;
#else
            doorTilemap = D_us_8018113C;
#endif
            if (self->params) {
                tileIndex = 0x6E;
                doorTilemap += 4;
            } else {
                tileIndex = 0x61;
            }
            for (i = 0; i < 4; i++, tileIndex += 16) {
                g_Tilemap.fg[tileIndex] = 0;
            }
            self->step++;
        }
        break;

    case 5:
        if (self->params) {
            self->velocityX = FIX(0.75);
        } else {
            self->velocityX = FIX(-0.75);
        }
        MoveEntity();
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
            entity->params = 0x10;
            entity->posY.i.hi += 32;
            entity->posX.i.hi -= (Random() & 7);
        }
        offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (self->params) {
            if (offsetX > 264) {
                DestroyEntity(self);
            }
        } else if (offsetX > 7) {
            DestroyEntity(self);
        }
        break;
    }
}

static s32 BossDoorHelper(Entity* self) UNUSED {
    s32 offsetY;

    MoveEntity();
    g_CurrentEntity->velocityY += FIX(0.25);
    offsetY =
        g_CurrentEntity->posY.i.hi + self->posX.i.hi + g_Tilemap.scrollY.i.hi;

    offsetY = 208 - offsetY; // critical, all in one line breaks regalloc

    if (offsetY <= 0) {
        g_CurrentEntity->posY.i.hi += offsetY;
        g_CurrentEntity->velocityX = 0;
        g_CurrentEntity->velocityY = 0;
        return 1;
    }

    return 0;
}
