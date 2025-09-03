// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

// Used by e_confessional/EntityConfessionalGhost
#ifdef VERSION_PSP
bool g_confessionalChimeActive; // bss on pspeu
#else
bool g_confessionalChimeActive = {0};
#endif

// Resets sound loop to DAI music
void func_us_801C3644(Entity* self) {
    if (!g_confessionalChimeActive) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        g_api.PlaySfx(SET_STOP_SEQ);
        D_80097928 = true;
        self->step = 2;
        if (g_api.func_80131F68()) {
            g_api.PlaySfx(SET_UNK_80);
            self->step++;
        }
        break;
    case 1:
        if (!g_api.func_80131F68()) {
            self->step++;
        }
        break;
    case 2:
        g_api.PlaySfx(D_80097910);
        D_80097928 = false;
        g_confessionalChimeActive = false;
        self->step++;
        break;
    }
}
