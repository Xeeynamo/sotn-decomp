#include "rnz1.h"

extern EInit g_EInitInteractable;
extern EInit g_EInitEnvironment;

#if defined(VERSION_PSP)
extern s32 E_ID(FROZEN_SHADE_CRYSTAL);
extern s32 E_ID(UNK_2E);
extern s32 E_ID(BOSS_DOORS);
extern s32 E_ID(LIFE_UP_SPAWN);
#endif

s32 g_BossDoorsLocked = 0;
s32 g_BossFlag = 0;

void EntityBossDoorTrigger(Entity* self) {
    Entity* entity;
    s32 timeAttackResult;
    s32 scrollX;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        timeAttackResult = g_api.TimeAttackController(
            TIMEATTACK_EVENT_DARKWING_BAT_DEFEAT, TIMEATTACK_GET_RECORD);
        if (timeAttackResult) {
            self->entityId = E_RELIC_ORB;
            self->pfnUpdate = EntityRelicOrb;
            self->poseTimer = 0;
            self->pose = 0;
            self->unk6D[0] = 0x10;
            self->params = RELIC_RING_OF_VLAD;
            self->step = 0;
            return;
        }
        entity = &g_Entities[79];
        CreateEntityFromCurrentEntity(E_ID(FROZEN_SHADE_CRYSTAL), entity);
        entity->posX.i.hi = 128 - g_Tilemap.scrollX.i.hi;
        entity->posY.i.hi = 120 - g_Tilemap.scrollY.i.hi;
        entity = &g_Entities[80];
        CreateEntityFromCurrentEntity(E_ID(UNK_2E), entity);
        entity->posX.i.hi = 128 - g_Tilemap.scrollX.i.hi;
        entity->posY.i.hi = 120 - g_Tilemap.scrollY.i.hi;
        // fallthrough

    case 1:
        entity = &PLAYER;
        scrollX = entity->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if(scrollX > 0x30 && scrollX < 0xd0){
            g_BossFlag |= 1;
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_DARKWING_BAT_DEFEAT, TIMEATTACK_SET_VISITED);
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
        g_BossDoorsLocked = 1;
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
        if (g_BossFlag & 2) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_DARKWING_BAT_DEFEAT, TIMEATTACK_SET_RECORD);
            g_api.PlaySfx(SET_UNK_90);
            currentMusicId = MU_FINAL_TOCATTA;
            self->step++;
        }
        break;
    case 6:
        if (g_BossFlag & 4) {
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(LIFE_UP_SPAWN), self, entity);
                entity->posX.i.hi = 128;
                entity->posY.i.hi = 128;
                entity->params = 0x14;
                g_BossDoorsLocked = 0;
                stopMusicFlag = true;
                currentMusicId = MU_FINAL_TOCATTA;
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
INCLUDE_ASM("st/rnz1/nonmatchings/unk_2C7CC", EntityBossDoors);
