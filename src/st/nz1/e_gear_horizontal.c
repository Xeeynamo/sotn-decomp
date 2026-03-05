// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

extern EInit g_EInitEnvironment;

static u8 D_us_80180FB8[] = {8, 4, 8, 5, 8, 6, 0, 0};

void EntityGearHorizontal(Entity* self) {
    Entity* player;
    s32 collision;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnvironment);
        self->zPriority = 0x6C;
        // fallthrough

    case 1:
        AnimateEntity(D_us_80180FB8, self);
        collision = GetPlayerCollisionWith(self, 0x20, 8, 4);
        if (collision != 0) {
            player = &PLAYER;
            if (!self->params) {
                if (!(g_Player.vram_flag & TOUCHING_R_WALL)) {
                    player->posX.val += FIX(0.25);
                    D_80097488.x.val += FIX(0.25);
                }
            } else {
                if (!(g_Player.vram_flag & TOUCHING_L_WALL)) {
                    player->posX.val -= FIX(0.25);
                    D_80097488.x.val -= FIX(0.25);
                }
            }
        }
        break;
    }
}
