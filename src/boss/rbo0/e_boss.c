// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo0.h"

bool func_us_80194338(s16* offsets) {
    s32 posY;

    offsets++;
    posY = g_CurrentEntity->posY.i.hi + *offsets + g_Tilemap.scrollY.i.hi;
    posY = 0xE0 - posY;
    if (posY <= 0) {
        g_CurrentEntity->posY.i.hi += posY;
        g_CurrentEntity->velocityX = 0;
        g_CurrentEntity->velocityY = 0;
        return true;
    }
    return false;
}

extern s32 D_us_801806AC;
s32 D_us_801806B0 = 0;
s32 D_us_801806B4 = 0;

// clang-format off
s8 D_us_801806B8[] = {
    0, 0, 0, 0,
    -64, -96, 0, 0,
    1, 3, 6, 20,
    2, 5, 7, 12,
    3, 12, 8, 12,
    0, -1, 6, 16,
    -3, 2, 4, 23,
    -64, -88, 0, 0,
    0, 0, 16, 16,
    2, 2, 15, 11,
    1, 4, 9, 13,
    -3, 2, 15, 11,
    -4, 5, 9, 14,
    -1, 4, 15, 11,
    3, 3, 13, 19,
    -4, 13, 9, 13,
    -1, 2, 4, 24,
    6, 5, 9, 14,
    0, 4, 10, 12,
    -2, 11, 13, 9,
    4, 13, 9, 13,
    -9, 13, 9, 13,
    0, 5, 2, 7,
    0, 1, 5, 21,
};
u8 D_us_80180718[] = {
    0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 4, 5, 5,
    3, 3, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 5, 5, 5, 2, 2, 6, 6, 6, 6, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7, 7, 8,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9,
    9, 9, 10, 10, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 14, 14, 14, 15, 15,
    15, 15, 15, 16, 17, 17, 9, 18, 18, 18, 18, 18, 19, 19, 20, 20,
    15, 15, 21, 21, 21, 21, 21, 21, 22, 23, 23, 23, 23, 23, 23, 23,
    23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23,
    23, 23, 23, 23, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};
s8 D_us_8018081C[] = {
    0, 0, 0, 0,
    -64, -96, 0, 0,
    -64, -88, 0, 0,
    31, -9, 22, 3,
    36, -7, 24, 2,
    54, -7, 33, 2,
    35, 5, 21, 2,
    39, 7, 21, 2,
    54, 8, 33, 2,
    -60, -92, 0, 0,
    -9, -12, 11, 39,
    -60, -95, 0, 0,
};
u8 D_us_8018084C[] = {
    0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 7, 8, 8, 8, 8, 8,
    8, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 10, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 11, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};
// clang-format on
static s16 unused_0 UNUSED = 24;
static s32 unused_1 UNUSED = 8;

// main boss controller
void EntityBoss(Entity* self) {
    Entity* entity;
    s32 offsetX;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        entity = &g_Entities[80];
        CreateEntityFromCurrentEntity(E_ID(FAKE_RALPH), entity);
        entity->posX.i.hi = 0x100 - g_Tilemap.scrollX.i.hi;
        entity->posY.i.hi = 0xC4 - g_Tilemap.scrollY.i.hi;

        entity = &g_Entities[88];
        CreateEntityFromCurrentEntity(E_ID(FAKE_GRANT), entity);
        entity->posX.i.hi = 0xB8 - g_Tilemap.scrollX.i.hi;
        entity->posY.i.hi = 0xC4 - g_Tilemap.scrollY.i.hi;

        entity = &g_Entities[96];
        CreateEntityFromCurrentEntity(E_ID(FAKE_SYPHA), entity);
        entity->posX.i.hi = 0x148 - g_Tilemap.scrollX.i.hi;
        entity->posY.i.hi = 0xC4 - g_Tilemap.scrollY.i.hi;
        // fallthrough

    case 1:
        entity = &PLAYER;
        offsetX = entity->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (offsetX > 0xE0 && offsetX < 0x140) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_RALPH_GRANT_SYPHA_DEFEAT,
                TIMEATTACK_SET_VISITED);
            D_us_801806B0 |= 1;
            D_us_801806AC = 1;
            self->ext.et_801806B0.timer = 0x140;
            stopMusicFlag = 0;
            currentMusicId = MU_FESTIVAL_OF_SERVANTS;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        break;
    case 2:
        if (!--self->ext.et_801806B0.timer) {
            D_us_801806B0 |= 2;
            self->step++;
        }
        break;
    case 3:
        if (D_us_801806B4 > 2) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_RALPH_GRANT_SYPHA_DEFEAT,
                TIMEATTACK_SET_RECORD);
            D_us_801806B0 |= 4;
            self->ext.et_801806B0.timer = 0x80;
            g_api.PlaySfx(SET_UNK_90);
            currentMusicId = MU_DOOR_OF_HOLY_SPIRITS;
            self->step++;
        }
        break;
    case 4:
        if (!--self->ext.et_801806B0.timer) {
            self->step++;
        }
        break;
    case 5:
        entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_ID(LIFE_UP_SPAWN), self, entity);
            entity->posX.i.hi = 0x100 - g_Tilemap.scrollX.i.hi;
            entity->posY.i.hi = 0x80 - g_Tilemap.scrollY.i.hi;
            entity->params = 2;
            D_us_801806AC = 0;
            stopMusicFlag = 1;
            currentMusicId = MU_DOOR_OF_HOLY_SPIRITS;
            self->step++;
        }
        break;
    case 6:
        if (g_api.func_80131F68() == false) {
            stopMusicFlag = 0;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        break;
    case 7:
        break;
    }
}
