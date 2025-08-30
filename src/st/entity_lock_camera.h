// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitLockCamera;

static u8 entityLockCameraHitbox[] = {
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x50, 0x20,
};

u8 entityLockCameraData[8] = {0};

u16 entityLockCameraTilemapProps[] = {
#if defined(STAGE_IS_NO1)
    0x01A0, 0x0000, 0x02A0, 0x0200, 0x01A0, 0x0000, 0x02A0, 0x0200,
#else
    0x0000, 0x0000, 0x0600, 0x0100, 0x0000, 0x0000, 0x0600, 0x01FC,
#endif
    0x0000, 0x00FC, 0x0600, 0x01FC, 0x0000, 0x0000, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x00FC, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x0200, 0x0600, 0x0300,
    0x0000, 0x01FC, 0x0500, 0x02FC, 0x0000, 0x0000, 0x0500, 0x0400,
    0x0000, 0x0000, 0x0500, 0x0400, 0x0000, 0x01FC, 0x0500, 0x02FC,
    0x00F0, 0x01FC, 0x0310, 0x02FC, 0x00F0, 0x01FC, 0x0310, 0x02FC,
};

// params: Which camera lock config to use
void OVL_EXPORT(EntityLockCamera)(Entity* self) {
    u16 var_s0;
    u16 params;
    u16* tilemapProps;

    self->unk6D[0] = 0;
    params = self->params;
    if (self->step) {
        switch (params) {
        case 4:
        case 5:
            if (g_Tilemap.x) {
                return;
            }
            break;
        case 6:
            if (g_pads[0].pressed & PAD_TRIANGLE) {
                g_Tilemap.x = 0;
                g_Tilemap.width = 1280;
                self->step++;
                return;
            }
            break;
        }

        if (self->hitParams) {
            var_s0 = GetSideToPlayer();
            if (self->ext.lockCamera.unk7C) {
                var_s0 &= 2;
                var_s0 *= 2;
            } else {
                var_s0 &= 1;
                var_s0 *= 4;
            }
            params = (params << 3) + var_s0;
            tilemapProps = &entityLockCameraTilemapProps[params];
            g_Tilemap.x = *tilemapProps++;
            g_Tilemap.y = *tilemapProps++;
            g_Tilemap.width = *tilemapProps++;
            g_Tilemap.height = *tilemapProps;
        }
    } else {
        InitializeEntity(g_EInitLockCamera);
        var_s0 = self->ext.lockCamera.unk7C = entityLockCameraData[params];
        if (var_s0) {
            self->hitboxWidth = entityLockCameraHitbox[params];
            self->hitboxHeight = 16;
        } else {
            self->hitboxWidth = 16;
            self->hitboxHeight = entityLockCameraHitbox[params];
        }
    }
}
