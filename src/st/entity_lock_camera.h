// SPDX-License-Identifier: AGPL-3.0-or-later
extern EInit g_EInitLockCamera;
static u8 D_8018065C[] = {32, 0};
#ifdef VERSION_PSP
extern u8 D_80180660[]; // needs BSS imported
#else
static u8 D_80180660[] = {0, 0};
#endif
static u16 D_80180664[] = {
    0x0000, 0x0000, 0x0500, 0x0200, // 0
    0x0000, 0x0000, 0x0500, 0x0100, // 1
};
void EntityLockCamera(Entity* self) {
    u16* rect16;
    u16 params;
    u16 facingLeft;

    params = self->params & 0xFF;
    if (!self->step) {
        InitializeEntity(g_EInitLockCamera);
        self->hitboxState = 1;

        facingLeft = self->ext.lockCamera.unk7C = D_80180660[params];
        if (facingLeft) {
            self->hitboxWidth = D_8018065C[params];
            self->hitboxHeight = 20;
        } else {
            self->hitboxWidth = 20;
            self->hitboxHeight = D_8018065C[params];
        }
    }

    if (self->params & 0x100) {
        params = params * 4;
        rect16 = &D_80180664[params];
        g_Tilemap.x = *rect16++;
        g_Tilemap.y = *rect16++;
        g_Tilemap.width = *rect16++;
        g_Tilemap.height = *rect16;
        DestroyEntity(self);
        return;
    }

    if (PlayerIsWithinHitbox(self)) {
        facingLeft = GetSideToPlayer();
        if (self->ext.lockCamera.unk7C) {
            facingLeft &= 2;
            facingLeft *= 2;
        } else {
            facingLeft &= 1;
            facingLeft *= 4;
        }
        params = (params << 3) + facingLeft;
        rect16 = &D_80180664[params];
        g_Tilemap.x = *rect16++;
        g_Tilemap.y = *rect16++;
        g_Tilemap.width = *rect16++;
        g_Tilemap.height = *rect16;
    }
}
