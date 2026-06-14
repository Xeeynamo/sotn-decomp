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

#ifdef VERSION_PSP
extern s32 D_us_801806AC;
#else
s32 D_us_801806AC = 0; // may be in a different file
#endif
s32 D_us_801806B0 = 0;
s32 D_us_801806B4 = 0;

// main boss controller
void OVL_EXPORT(EntityBoss)(Entity* self) {
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
