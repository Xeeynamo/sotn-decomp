// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

extern EInit g_EInitInteractable;
extern u16 D_us_80180C66;

void func_us_801A6370(Entity* self) {
    s32 hasRecord;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        hasRecord = g_api.TimeAttackController(
            TIMEATTACK_EVENT_SCYLLA_DEFEAT, TIMEATTACK_GET_RECORD);
        if (hasRecord) {
            DestroyEntity(self);
            break;
        }
        g_api.PlaySfx(SET_UNK_90);
        /* fall through */
    case 1:
        if (g_BossMgrState & BOSS_MGR_FIGHT_ON) {
            stopMusicFlag = false;
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
        /* fall through */
    case 3:
        if (g_BossMgrState & BOSS_MGR_DEFEAT) {
            g_api.PlaySfx(0x91);
            currentMusicId = MU_CRYSTAL_TEARDROPS;
            stopMusicFlag = false;
            self->step++;
        }
        break;

    case 4:
        if (g_BossMgrState & BOSS_MGR_TERMINATED) {
            stopMusicFlag = true;
            currentMusicId = MU_CRYSTAL_TEARDROPS;
            self->step++;
        }
        break;

    case 5:
        if (g_api.func_80131F68() == false) {
            stopMusicFlag = false;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        break;
    }
}

void func_us_801A6568(Entity* self) {
    u8 defeated;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        defeated = g_CastleFlags[SCYLLA_WYRM_DEFEATED];
        if (defeated) {
            DestroyEntity(self);
            break;
        }
        /* fall through */
    case 1:
        if (D_us_80180C66 & 2) {
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
        /* fall through */
    case 3:
        if (g_CastleFlags[SCYLLA_WYRM_DEFEATED]) {
            g_api.PlaySfx(SET_UNK_90);
            stopMusicFlag = true;
            currentMusicId = MU_CRYSTAL_TEARDROPS;
            self->step = 4;
        }
        break;

    case 4:
        if (g_api.func_80131F68() == false) {
            stopMusicFlag = false;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        break;
    }
}
