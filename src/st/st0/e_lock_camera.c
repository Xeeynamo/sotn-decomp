// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"

#include "../player_is_within_hitbox.h"

extern u16 g_EInitLockCamera[];
static u8 D_8018065C[] = {32, 0};
static u8 D_80180660[] = {0, 0};
static u16 D_80180664[] = {
    0x0000, 0x0000, 0x0500, 0x0200, // 0
    0x0000, 0x0000, 0x0500, 0x0100, // 1
};
void EntityLockCamera(Entity* self) {
    s32 facingLeft;
    u16 offset;
    u16* rect16;
    u16 params;
    u8 flag;

    params = (u8)self->params;
    if (self->step == 0) {
        InitializeEntity(g_EInitLockCamera);

        self->hitboxState = 1;

        flag = D_80180660[params];
        self->ext.lockCamera.unk7C = flag;

        if (flag) {
            self->hitboxWidth = D_8018065C[params];
            self->hitboxHeight = 20;
        } else {
            self->hitboxWidth = 20;
            self->hitboxHeight = D_8018065C[params];
        }
    }

    if (self->params & 0x100) {
        params *= 4;
        rect16 = &D_80180664[params];
        g_Tilemap.x = *rect16++;
        g_Tilemap.y = *rect16++;
        g_Tilemap.width = *rect16++;
        g_Tilemap.height = *rect16++;
        DestroyEntity(self);
        return;
    }

    if (PlayerIsWithinHitbox(self) != 0) {
        facingLeft = GetSideToPlayer();
        if (self->ext.lockCamera.unk7C) {
            facingLeft &= 2;
            offset = facingLeft * 2;
        } else {
            facingLeft &= 1;
            offset = facingLeft * 4;
        }
        params <<= 3;
        params += offset;
        rect16 = &D_80180664[params];
        g_Tilemap.x = *rect16++;
        g_Tilemap.y = *rect16++;
        g_Tilemap.width = *rect16++;
        g_Tilemap.height = *rect16++;
    }
}
