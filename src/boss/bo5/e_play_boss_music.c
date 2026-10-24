// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo5.h"

extern EInit g_EInitInteractable;
s32 D_us_80180B74 = 1;

void EntityPlayBossMusic(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
    case 1:
        if (D_us_801806DC) {
            stopMusicFlag = true;
            currentMusicId = MU_DEATH_BALLAD;
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
        if (!D_us_80180B74) {
            g_api.PlaySfx(0x91);
            self->step++;
        }
        break;
    case 4:
        break;
    }
}
