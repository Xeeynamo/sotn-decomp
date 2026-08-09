// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo1.h"

#define RBO1_BOSS_FLAG_FIGHT_STARTED (1 << 0)
#define RBO1_BOSS_FLAG_DEFEATED (1 << 1)
#define RBO1_BOSS_FLAG_REWARD_READY (1 << 2)
#define RBO1_BOSS_FLAG_DOORS_CLOSE (1 << 3)
#define RBO1_BOSS_FLAG_DOORS_OPEN (1 << 4)

typedef struct {
    u16 x;
    u16 y;
    u16 params;
} Rbo1BlockPlacement;

static Rbo1BlockPlacement D_us_80180988[] = {
    {0x408, 0x168, 1}, {0x408, 0x178, 1}, {0x408, 0x188, 1}, {0x408, 0x198, 1},
    {-8, 0x068, 0},    {-8, 0x078, 0},    {-8, 0x088, 0},    {-8, 0x098, 0},
    {-8, 0x168, 0},    {-8, 0x178, 0},    {-8, 0x188, 0},    {-8, 0x198, 0},
};

extern EInit g_EInitInteractable;
extern s32 D_us_801A1F1C;

void func_us_80194C50(Entity* self) {
    Entity* entity;
    u16* placementY;
    register Entity* entityToCreate __asm__("$17");
    u16* placementX;
    u16* scroll;
    s32 offsetX;
    s32 offsetY;
    s32 i;

    switch (self->step) {
    case 0:
        entityToCreate = &self[1];
        InitializeEntity(g_EInitInteractable);
        placementX = &D_us_80180988[0].x;
        i = 0;
        scroll = (u16*)&g_Tilemap.scrollX.i.hi;
        placementY = placementX + 1;
        entity = &self[1];
        do {
            CreateEntityFromCurrentEntity(E_BOSS_ROOM_BLOCK, entityToCreate);
            i++;
            entityToCreate++;
            entity->params = placementY[1];
            entity->posX.i.hi = *placementX - scroll[0];
            placementX += 3;
            entity->posY.i.hi = *placementY - scroll[2];
            placementY += 3;
            entity++;
        } while (i < LEN(D_us_80180988));
        entity = &g_Entities[80];
        CreateEntityFromCurrentEntity(E_UNK_16, entity);
        entity->posX.i.hi = 0x240 - g_Tilemap.scrollX.i.hi;
        entity->posY.i.hi = 0xD8 - g_Tilemap.scrollY.i.hi;
        // fallthrough

    case 1:
        offsetX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
        if ((u32)(offsetX - 0x19) < 0x3BF) {
            D_us_801A1F1C |= RBO1_BOSS_FLAG_DOORS_CLOSE;
            g_api.PlaySfx(SET_UNK_90);
            self->step++;
        }
        break;

    case 2:
        offsetX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
        if ((u32)(offsetX - 0x141) < 0x1DF) {
            D_us_801A1F1C |= RBO1_BOSS_FLAG_FIGHT_STARTED;
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_BEELZEBUB_DEFEAT, TIMEATTACK_SET_VISITED);
            self->step++;
        }
        break;

    case 3:
        if (g_api.func_80131F68() == false) {
            stopMusicFlag = false;
            currentMusicId = MU_DEATH_BALLAD;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        // fallthrough

    case 4:
        if (D_us_801A1F1C & RBO1_BOSS_FLAG_DEFEATED) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_BEELZEBUB_DEFEAT, TIMEATTACK_SET_RECORD);
            g_api.PlaySfx(SET_UNK_90);
            currentMusicId = MU_FINAL_TOCATTA;
            self->step++;
        }
        break;

    case 5:
        if (D_us_801A1F1C & RBO1_BOSS_FLAG_REWARD_READY) {
            self->step++;
        }
        break;

    case 6:
        offsetX = 0x80;
        offsetY = 0x180 - g_Tilemap.scrollY.i.hi;
        entityToCreate = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (entityToCreate != NULL) {
            CreateEntityFromEntity(E_LIFE_UPSPAWN, self, entityToCreate);
            entityToCreate->posX.i.hi = offsetX;
            entityToCreate->posY.i.hi = offsetY;
            entityToCreate->params = 5;
            stopMusicFlag = true;
            currentMusicId = MU_FINAL_TOCATTA;
            D_us_801A1F1C |= RBO1_BOSS_FLAG_DOORS_OPEN;
            self->step++;
        }
        break;

    case 7:
        if (g_api.func_80131F68() == false) {
            stopMusicFlag = false;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        break;
    }
}
