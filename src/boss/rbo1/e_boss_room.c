// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo1.h"

#define RBO1_BOSS_FLAG_FIGHT_STARTED (1 << 0)
#define RBO1_BOSS_FLAG_DEFEATED (1 << 1)
#define RBO1_BOSS_FLAG_REWARD_READY (1 << 2)
#define RBO1_BOSS_FLAG_DOORS_CLOSE (1 << 3)
#define RBO1_BOSS_FLAG_DOORS_OPEN (1 << 4)

typedef struct {
    s16 x;
    s16 y;
    s16 params;
} Rbo1TilePlacement;

static Rbo1TilePlacement tile_placements[] = {
    {0x408, 0x168, 1}, {0x408, 0x178, 1}, {0x408, 0x188, 1}, {0x408, 0x198, 1},
    {-8, 0x068, 0},    {-8, 0x078, 0},    {-8, 0x088, 0},    {-8, 0x098, 0},
    {-8, 0x168, 0},    {-8, 0x178, 0},    {-8, 0x188, 0},    {-8, 0x198, 0},
};

extern EInit g_EInitInteractable;
extern s32 bossFlags;

void func_us_80194C50(Entity* self) {
    Entity* entity;
    Rbo1TilePlacement* placement;
    s32 offsetX;
    s32 offsetY;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        entity = &self[1];
        placement = tile_placements;
        i = 0;
        while (i < LEN(tile_placements)) {
            CreateEntityFromCurrentEntity(E_ID(BOSS_ROOM_BLOCK), entity);
            entity->params = placement->params;
            entity->posX.i.hi = placement->x - g_Tilemap.scrollX.i.hi;
            entity->posY.i.hi = placement->y - g_Tilemap.scrollY.i.hi;
            i++;
            entity++;
            placement++;
        }
        entity = &g_Entities[80];
        CreateEntityFromCurrentEntity(E_ID(UNK_16), entity);
        entity->posX.i.hi = 0x240 - g_Tilemap.scrollX.i.hi;
        entity->posY.i.hi = 0xD8 - g_Tilemap.scrollY.i.hi;
        // fallthrough

    case 1:
        offsetX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (offsetX > 0x18 && offsetX < 0x3D8) {
            bossFlags |= RBO1_BOSS_FLAG_DOORS_CLOSE;
            g_api.PlaySfx(SET_UNK_90);
            self->step++;
        }
        break;

    case 2:
        offsetX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (offsetX > 0x140 && offsetX < 0x320) {
            bossFlags |= RBO1_BOSS_FLAG_FIGHT_STARTED;
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
        if (bossFlags & RBO1_BOSS_FLAG_DEFEATED) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_BEELZEBUB_DEFEAT, TIMEATTACK_SET_RECORD);
            g_api.PlaySfx(SET_UNK_90);
            currentMusicId = MU_FINAL_TOCATTA;
            self->step++;
        }
        break;

    case 5:
        if (bossFlags & RBO1_BOSS_FLAG_REWARD_READY) {
            self->step++;
        }
        break;

    case 6:
        offsetX = 0x80;
        offsetY = 0x180 - g_Tilemap.scrollY.i.hi;
        entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_ID(LIFE_UP_SPAWN), self, entity);
            entity->posX.i.hi = offsetX;
            entity->posY.i.hi = offsetY;
            entity->params = 5;
            stopMusicFlag = true;
            currentMusicId = MU_FINAL_TOCATTA;
            bossFlags |= RBO1_BOSS_FLAG_DOORS_OPEN;
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

INCLUDE_ASM("boss/rbo1/nonmatchings/e_boss_room", EntityBossRoomBlock);
