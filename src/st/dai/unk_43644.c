// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

// bss on pspeu
// currently used by e_priest/func_us_801C2534
#ifdef VERSION_PSP
s32 D_us_80180EA0; // D_pspeu_092970A0
#else
s32 D_us_80180EA0 = {0};
#endif

void func_us_801C3644(Entity* self) {
    if (!D_us_80180EA0) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        g_api.PlaySfx(SET_STOP_SEQ);
        D_80097928 = 1;
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
        D_80097928 = 0;
        D_us_80180EA0 = 0;
        self->step++;
        break;
    }
}
