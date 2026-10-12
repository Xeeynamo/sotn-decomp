// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo4.h"

#ifdef VERSION_PSP
extern s32 E_ID(UNK_19);
extern s32 E_ID(LIFE_UP_SPAWN);
#endif

extern EInit g_EInitInteractable;
s32 g_BossMgrState = BOSS_MGR_IDLE;
extern s32 D_us_80180810;

void EntityBossFightManager(Entity* self) {
    Entity* child;
    Entity* entity;
    s32 i;
    s32 x;
    s32 y;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        self->animCurFrame = 0;
        child = self + 1;
        for (i = 1; i < 2; i++) {
            CreateEntityFromEntity(E_ID(UNK_19), self, child);
            child->params = i + 0x100;
            child++;
            CreateEntityFromEntity(E_ID(UNK_19), self, child);
            child->params = i;
            child++;
        }
    case 1:
        entity = &PLAYER;
        x = entity->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (x > 96 && x < 416) {
            D_us_80180810 = 1;
            g_BossMgrState = BOSS_MGR_FIGHT_ON;
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_THE_CREATURE_DEFEAT, TIMEATTACK_SET_VISITED);
            stopMusicFlag = true;
            currentMusicId = MU_FESTIVAL_OF_SERVANTS;
            self->step++;
        }
        break;
    case 2:
        if (g_api.func_80131F68() == false) {
            stopMusicFlag = false;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        break;
    case 3:
        if (g_BossMgrState & BOSS_MGR_DEFEAT) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_THE_CREATURE_DEFEAT, TIMEATTACK_SET_RECORD);
            g_api.PlaySfx(SET_UNK_90);
            currentMusicId = MU_FINAL_TOCATTA;
            self->step++;
        }
        break;
    case 4:
        if (g_BossMgrState & BOSS_MGR_TERMINATED) {
            self->step++;
        }
        break;
    case 5:
        x = 256 - g_Tilemap.scrollX.i.hi;
        y = 128 - g_Tilemap.scrollY.i.hi;
        entity = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
        if (entity == NULL) {
            break;
        }
        CreateEntityFromEntity(E_ID(LIFE_UP_SPAWN), self, entity);
        entity->posX.i.hi = x;
        entity->posY.i.hi = y;
        entity->params = 0x12;
        D_us_80180810 = 0;
        stopMusicFlag = true;
        currentMusicId = MU_FINAL_TOCATTA;
        self->step++;
        break;
    case 6:
        if (g_api.func_80131F68() == false) {
            stopMusicFlag = false;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        break;
    }
}
