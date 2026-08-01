// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rlib.h"

extern EInit g_EInitLockCamera;
extern u8 D_us_801807A4[];
extern u8 D_us_801807AC[];
extern u16 D_us_801807B4[];

void OVL_EXPORT(EntityLockCamera)(Entity* self) {
    u16* dataPtr;
    u16 params;
    u16 facingLeft;

    params = self->params;

    // always cleared, regardless of step (branch delay slot in the original asm)
    self->unk6D[0] = 0;

    if (self->step) {
        switch (params) {
        case 4:
        case 5:
            if (g_Tilemap.x != 0) {
                return;
            }
            break;
        case 6:
            if (g_pads[0].pressed & 0x10) {
                g_Tilemap.x = 0;
                g_Tilemap.width = 0x500;
                self->step++;
                return;
            }
            break;
        }

        if (self->hitParams) {
            facingLeft = GetSideToPlayer();
            if (self->ext.lockCamera.unk7C) {
                facingLeft &= 2;
                facingLeft *= 2;
            } else {
                facingLeft &= 1;
                facingLeft *= 4;
            }
            params = (params << 3) + facingLeft;
            dataPtr = &D_us_801807B4[params];
            g_Tilemap.x = *dataPtr++;
            g_Tilemap.y = *dataPtr++;
            g_Tilemap.width = *dataPtr++;
            g_Tilemap.height = *dataPtr;
        }
    } else {
        InitializeEntity(g_EInitLockCamera);
        facingLeft = self->ext.lockCamera.unk7C = D_us_801807AC[params];
        if (facingLeft) {
            self->hitboxWidth = D_us_801807A4[params];
            self->hitboxHeight = 0x10;
        } else {
            self->hitboxWidth = 0x10;
            self->hitboxHeight = D_us_801807A4[params];
        }
    }
}
