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
} Rbo1BlockPlacement;

static Rbo1BlockPlacement D_us_80180988[] = {
    {0x408, 0x168, 1}, {0x408, 0x178, 1}, {0x408, 0x188, 1}, {0x408, 0x198, 1},
    {-8, 0x068, 0},    {-8, 0x078, 0},    {-8, 0x088, 0},    {-8, 0x098, 0},
    {-8, 0x168, 0},    {-8, 0x178, 0},    {-8, 0x188, 0},    {-8, 0x198, 0},
};

extern EInit g_EInitInteractable;
#ifdef VERSION_PSP
extern s32 D_pspeu_09256D48;
extern s32 D_pspeu_09256D50;
extern s32 D_pspeu_09256D98;
extern s32 D_pspeu_09256DC8;
#define RBO1_BOSS_FLAGS D_pspeu_09256DC8
#define RBO1_E_BOSS_ROOM_BLOCK D_pspeu_09256D50
#define RBO1_E_LIFE_UPSPAWN D_pspeu_09256D48
#define RBO1_E_UNK_16 D_pspeu_09256D98
#else
extern s32 D_us_801A1F1C;
#define RBO1_BOSS_FLAGS D_us_801A1F1C
#define RBO1_E_BOSS_ROOM_BLOCK E_BOSS_ROOM_BLOCK
#define RBO1_E_LIFE_UPSPAWN E_LIFE_UPSPAWN
#define RBO1_E_UNK_16 E_UNK_16
#endif

void func_us_80194C50(Entity* self) {
    Entity* entity;
#ifndef VERSION_PSP
    u16* placementY;
    register Entity* entityToCreate __asm__("$17");
    u16* placementX;
    u16* scroll;
#else
    Rbo1BlockPlacement* placement;
#endif
    s32 offsetX;
    s32 offsetY;
    s32 i;

    switch (self->step) {
    case 0:
#ifdef VERSION_PSP
        InitializeEntity(g_EInitInteractable);
        entity = &self[1];
        placement = D_us_80180988;
        i = 0;
        while (i < LEN(D_us_80180988)) {
            CreateEntityFromCurrentEntity(RBO1_E_BOSS_ROOM_BLOCK, entity);
            entity->params = placement->params;
            entity->posX.i.hi = placement->x - g_Tilemap.scrollX.i.hi;
            entity->posY.i.hi = placement->y - g_Tilemap.scrollY.i.hi;
            i++;
            entity++;
            placement++;
        }
#else
        entityToCreate = &self[1];
        InitializeEntity(g_EInitInteractable);
        placementX = &D_us_80180988[0].x;
        i = 0;
        scroll = (u16*)&g_Tilemap.scrollX.i.hi;
        placementY = placementX + 1;
        entity = &self[1];
        do {
            CreateEntityFromCurrentEntity(
                RBO1_E_BOSS_ROOM_BLOCK, entityToCreate);
            i++;
            entityToCreate++;
            entity->params = placementY[1];
            entity->posX.i.hi = *placementX - scroll[0];
            placementX += 3;
            entity->posY.i.hi = *placementY - scroll[2];
            placementY += 3;
            entity++;
        } while (i < LEN(D_us_80180988));
#endif
        entity = &g_Entities[80];
        CreateEntityFromCurrentEntity(RBO1_E_UNK_16, entity);
        entity->posX.i.hi = 0x240 - g_Tilemap.scrollX.i.hi;
        entity->posY.i.hi = 0xD8 - g_Tilemap.scrollY.i.hi;
        // fallthrough

    case 1:
#ifdef VERSION_PSP
        entity = &PLAYER;
        offsetX = entity->posX.i.hi + g_Tilemap.scrollX.i.hi;
#else
        offsetX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
#endif
#ifdef VERSION_PSP
        if (offsetX > 0x18 && offsetX < 0x3D8) {
#else
        if ((u32)(offsetX - 0x19) < 0x3BF) {
#endif
            RBO1_BOSS_FLAGS |= RBO1_BOSS_FLAG_DOORS_CLOSE;
            g_api.PlaySfx(SET_UNK_90);
            self->step++;
        }
        break;

    case 2:
#ifdef VERSION_PSP
        entity = &PLAYER;
        offsetX = entity->posX.i.hi + g_Tilemap.scrollX.i.hi;
#else
        offsetX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
#endif
#ifdef VERSION_PSP
        if (offsetX > 0x140 && offsetX < 0x300) {
#else
        if ((u32)(offsetX - 0x141) < 0x1DF) {
#endif
            RBO1_BOSS_FLAGS |= RBO1_BOSS_FLAG_FIGHT_STARTED;
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_BEELZEBUB_DEFEAT, TIMEATTACK_SET_VISITED);
            self->step++;
        }
        break;

    case 3:
        if (g_api.func_80131F68() == false) {
            stopMusicFlag = false;
            currentMusicId = MU_DEATH_BALLAD;
#ifdef VERSION_PSP
            g_api.PlaySfx(MU_DEATH_BALLAD);
#else
            g_api.PlaySfx(currentMusicId);
#endif
            self->step++;
        }
        // fallthrough

    case 4:
        if (RBO1_BOSS_FLAGS & RBO1_BOSS_FLAG_DEFEATED) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_BEELZEBUB_DEFEAT, TIMEATTACK_SET_RECORD);
            g_api.PlaySfx(SET_UNK_90);
            currentMusicId = MU_FINAL_TOCATTA;
            self->step++;
        }
        break;

    case 5:
        if (RBO1_BOSS_FLAGS & RBO1_BOSS_FLAG_REWARD_READY) {
            self->step++;
        }
        break;

    case 6:
        offsetX = 0x80;
        offsetY = 0x180 - g_Tilemap.scrollY.i.hi;
#ifdef VERSION_PSP
        entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (entity != NULL) {
            CreateEntityFromEntity(RBO1_E_LIFE_UPSPAWN, self, entity);
            entity->posX.i.hi = offsetX;
            entity->posY.i.hi = offsetY;
            entity->params = 5;
            RBO1_BOSS_FLAGS |= RBO1_BOSS_FLAG_DOORS_OPEN;
            stopMusicFlag = true;
            currentMusicId = MU_FINAL_TOCATTA;
            self->step++;
        }
#else
        entityToCreate = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (entityToCreate != NULL) {
            CreateEntityFromEntity(RBO1_E_LIFE_UPSPAWN, self, entityToCreate);
            entityToCreate->posX.i.hi = offsetX;
            entityToCreate->posY.i.hi = offsetY;
            entityToCreate->params = 5;
            stopMusicFlag = true;
            currentMusicId = MU_FINAL_TOCATTA;
            RBO1_BOSS_FLAGS |= RBO1_BOSS_FLAG_DOORS_OPEN;
            self->step++;
        }
#endif
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
