// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "sfx.h"

// This file holds functions to handle the Slogra and Gaibon fight.
// Slogra and Gaibon themselves are in individual files.
s32 g_BossFlag = 0x00000000;
static s16 D_80181014[][3] = {
    {0xFFF8, 0x0068, 0}, {0xFFF8, 0x0078, 0}, {0xFFF8, 0x0088, 0},
    {0xFFF8, 0x0098, 0}, {0x0408, 0x0068, 1}, {0x0408, 0x0078, 1},
    {0x0408, 0x0088, 1}, {0x0408, 0x0098, 1}, {0x0408, 0x0168, 1},
    {0x0408, 0x0178, 1}, {0x0408, 0x0188, 1}, {0x0408, 0x0198, 1}};

void EntityBossFightManager(Entity* self) {
    Entity* entity;
    s32 i;
    s16* temp_s1;
    s32 xPos;
    s32 newEntY;
    bool bosses_defeated;

    FntPrint("boss_flag %x\n", g_BossFlag);
    FntPrint("boss_step %x\n", self->step);
    switch (self->step) {
    case 0:
        bosses_defeated = g_api.TimeAttackController(
            TIMEATTACK_EVENT_SLOGRA_GAIBON_DEFEAT, TIMEATTACK_GET_RECORD);
        if (bosses_defeated) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(g_EInitInteractable);
        g_BossFlag = 0;
        entity = self + 1;
        temp_s1 = (s16*)D_80181014;
        for (i = 0; i < LEN(D_80181014); i++, entity++, temp_s1 += 3) {
            CreateEntityFromCurrentEntity(E_ID(BOSS_ROOM_BLOCK), entity);
            entity->params = temp_s1[2];
            entity->posX.i.hi = temp_s1[0] - g_Tilemap.scrollX.i.hi;
            entity->posY.i.hi = temp_s1[1] - g_Tilemap.scrollY.i.hi;
        }
        // This spawns Slogra and Gaibon! Note that they always spawn at slot
        // 80 and 88, which allows the SLOGRA and GAIBON macros (self[8]) to
        // work.
        entity = &g_Entities[80];
        CreateEntityFromCurrentEntity(E_ID(SLOGRA), entity);
        entity->posX.i.hi = 0x280 - g_Tilemap.scrollX.i.hi;
        entity->posY.i.hi = 0x1A0 - g_Tilemap.scrollY.i.hi;
        entity = &g_Entities[88];
        CreateEntityFromCurrentEntity(E_ID(GAIBON), entity);
        entity->posX.i.hi = 0x2A0 - g_Tilemap.scrollX.i.hi;
        entity->posY.i.hi = 0x160 - g_Tilemap.scrollY.i.hi;
        // fall through
    case 1: // Detect whether player is in the room. If so, close the door.
        entity = &PLAYER;
        xPos = entity->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (24 < xPos && xPos < 968) {
            g_BossFlag |= BOSS_FLAG_DOORS_CLOSED;
            // Unknown sound
            g_api.PlaySfx(SET_UNK_90);
            stopMusicFlag = false;
            self->step++;
        }
        break;
    case 2: // Door closed. Wait for player to get far enough to start the fight
        entity = &PLAYER;
        xPos = entity->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (0x220 < xPos && xPos < 0x340) {
            g_BossFlag |= BOSS_FLAG_FIGHT_BEGIN;
        }
        if (g_BossFlag & BOSS_FLAG_FIGHT_BEGIN) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_SLOGRA_GAIBON_DEFEAT, TIMEATTACK_SET_VISITED);
            stopMusicFlag = true;
            currentMusicId = MU_FESTIVAL_OF_SERVANTS;
            self->step++;
        }
        break;
    case 3: // Fight is now active.
        if (g_api.func_80131F68() == false) {
            stopMusicFlag = false;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        /* fallthrough */
    case 4:
        // Wait for the fight to be over.
        if ((g_BossFlag & BOSS_FLAG_GAIBON_DEAD) &&
            (g_BossFlag & BOSS_FLAG_SLOGRA_DEAD)) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_SLOGRA_GAIBON_DEFEAT, TIMEATTACK_SET_RECORD);
            if (g_api.func_80131F68() != false) {
                g_api.PlaySfx(SET_UNK_90);
            }
            currentMusicId = MU_DANCE_OF_GOLD;
            self->step++;
        }
        break;
    case 5: // Fight is now over.
        xPos = 0x80;
        newEntY = 0x180 - g_Tilemap.scrollY.i.hi;
        entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (entity == NULL) {
            return;
        }
        CreateEntityFromEntity(E_ID(LIFE_UP_SPAWN), self, entity);
        entity->posX.i.hi = xPos;
        entity->posY.i.hi = newEntY;
        entity->params = 5;
        g_BossFlag |= BOSS_FLAG_DOORS_OPEN; // Reopen the door
        g_CastleFlags[SLO_GAI_DEFEATED] = 1;
        stopMusicFlag = true;
        currentMusicId = MU_DANCE_OF_GOLD;
        self->step++;
        break;
    case 6:
        if (g_api.func_80131F68() == false) {
            stopMusicFlag = false;
            g_api.PlaySfx(currentMusicId);
            self->step++;
            return;
        }
        break;
    case 0xFF:
#include "../pad2_anim_debug.h"
    }
}

// blocks that move to close slogra/gaibon room
void EntityBossRoomBlock(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBossDoor);
        self->animCurFrame = 8;

    case 1:
        if (g_BossFlag & 1) {
            self->ext.GS_Props.timer = 16;
            self->step++;
        }
        break;

    case 2:
        if (self->params) {
            self->velocityX = FIX(-1);
        } else {
            self->velocityX = FIX(1);
        }
        MoveEntity();
        GetPlayerCollisionWith(self, 8, 8, 5);
        if (!(g_Timer & 3)) {
            g_api.PlaySfx(SFX_STONE_MOVE_B);
        }
        if (--self->ext.GS_Props.timer) {
            break;
        }
        self->step++;
        break;

    case 3:
        GetPlayerCollisionWith(self, 8, 8, 5);
        if (g_BossFlag & BOSS_FLAG_DOORS_OPEN) {
            self->step++;
        }
        break;

    case 4:
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        if (self->params) {
            self->velocityX = FIX(1);
        } else {
            self->velocityX = FIX(-1);
        }
        MoveEntity();
        break;
    }
}
