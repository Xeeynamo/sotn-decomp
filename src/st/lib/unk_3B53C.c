// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

#ifdef VERSION_PSP
extern s32 E_ID(ID_1F);
extern s32 E_ID(ID_12);
extern s32 E_ID(ID_42);
extern Entity D_91E5084;
#endif
extern s32 currentMusicId;
extern s32 stopMusicFlag;
extern s32 D_us_80181AC8;
extern s32 D_us_80181ACC;
extern s32 D_us_80181AD0;

// PSX symbols unused in code, but referenced in ASM so may be needed for
// importing the data.
// D_80076E9A = tempEntity->posX.i.hi
// D_80076E9E = tempEntity->posY.i.hi
// D_80076E0C = tempEntity->params
// D_80076DDE = (tempEntity-1)->posX.i.hi
// D_80076DE2 = (tempEntity-1)->posY.i.hi

// This also seems to be related to the Lesser Demon boss fight somehow, but not
// the Lesser Demon itself.  Possibly the books that block escape from the
// fight.
void func_us_801BB53C(Entity* self) {
    Entity* tempEntity;
    s32 x, y;
    s32 timeAttackRecord;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        timeAttackRecord = g_api.TimeAttackController(
            TIMEATTACK_EVENT_LESSER_DEMON_DEFEAT, TIMEATTACK_GET_RECORD);
        if (timeAttackRecord) {
            DestroyEntity(self);
            return;
        }
        tempEntity = &g_Entities[E_BOSS_WEAPON];
        CreateEntityFromCurrentEntity(E_ID(ID_1F), tempEntity);
        tempEntity->posX.i.hi = 0x200 - g_Tilemap.scrollX.i.hi;
        tempEntity->posY.i.hi = 0x2A0 - g_Tilemap.scrollY.i.hi;
#ifdef VERSION_PSP
        tempEntity = &D_91E5084;
#else
        tempEntity--;
#endif
        CreateEntityFromCurrentEntity(E_ID(ID_12), tempEntity);
        tempEntity->params = 6;
        tempEntity->posX.i.hi = 0x200 - g_Tilemap.scrollX.i.hi;
        tempEntity->posY.i.hi = 0x270 - g_Tilemap.scrollY.i.hi;
    case 1:
        tempEntity = &g_Entities[0];
        x = tempEntity->posX.i.hi + g_Tilemap.scrollX.i.hi;
        y = tempEntity->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (x > 0x170 && x < 0x290 && y > 0x220 && y < 0x2c0) {
            D_us_80181AC8 = 1;
            D_us_80181ACC |= 1;
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_LESSER_DEMON_DEFEAT, TIMEATTACK_SET_VISITED);
            self->step++;
        }
        break;
    case 2:
        if (g_api.func_80131F68()) {
            g_api.PlaySfx(SET_UNK_90);
        }
        stopMusicFlag = true;
        currentMusicId = MU_FESTIVAL_OF_SERVANTS;
        self->step++;
        break;
    case 3:
        if (!g_api.func_80131F68()) {
            stopMusicFlag = false;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        /* fallthrough */
    case 4:
        if (D_us_80181ACC & 0x2) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_LESSER_DEMON_DEFEAT, TIMEATTACK_SET_RECORD);
            if (g_api.func_80131F68() != 0) {
                g_api.PlaySfx(SET_UNK_90);
            }
            currentMusicId = MU_WOOD_CARVING_PARTITA;
            self->step = 5;
        }
        break;
    case 5:
        if (D_us_80181ACC & 0x4) {
            tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_ID(ID_42), self, tempEntity);
                tempEntity->posX.i.hi = 0x80;
                tempEntity->posY.i.hi = 0x80;
                tempEntity->params = 7;
                D_us_80181AC8 = 0;
                stopMusicFlag = true;
                currentMusicId = MU_WOOD_CARVING_PARTITA;
                D_us_80181AD0 = 1;
                D_us_80181ACC &= ~1;
                self->step++;
            }
        }
        break;
    case 6:
        if (!g_api.func_80131F68()) {
            stopMusicFlag = false;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        break;
    }
}
