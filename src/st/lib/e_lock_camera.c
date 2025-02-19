// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

#include "../player_is_within_hitbox.h"

static u8 hitboxes[] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x50, 0x20};
#ifdef VERSION_PSP
extern u8 entityLockCameraData[]; // bss
#else
static u8 entityLockCameraData[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
#endif
extern u16 tileMapProps[] = {
    0x0000, 0x0000, 0x0100, 0x0100, 0x0000, 0x0000, 0x0100, 0x0100,
    0x0000, 0x00FC, 0x0600, 0x01FC, 0x0000, 0x0000, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x00FC, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x0200, 0x0600, 0x0300,
    0x0000, 0x01FB, 0x0500, 0x02FB, 0x0000, 0x0000, 0x0500, 0x0400,
    0x0000, 0x0000, 0x0500, 0x0400, 0x0000, 0x01FB, 0x0500, 0x02FB,
    0x00F0, 0x01FB, 0x0310, 0x02FB, 0x00F0, 0x01FB, 0x0310, 0x02FB};

extern s32 D_us_80181AD0;

void EntityLockCamera(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    u16* dataPtr;
    u16 facingLeft;
    u16 params;
    s16 var_s4;

    params = self->params;
    if (!self->step) {
        InitializeEntity(g_EInitLockCamera);
        self->hitboxState = 1;
        facingLeft = self->ext.lockCamera.unk7C = entityLockCameraData[params];
        if (facingLeft) {
            self->hitboxWidth = hitboxes[params];
            self->hitboxHeight = 0x14;
        } else {
            self->hitboxWidth = 0x14;
            self->hitboxHeight = hitboxes[params];
        }
        self->ext.lockCamera.unk88 = 2;
    }

    switch (params) {
    case 4:
    case 5:
        // While this looks odd being empty, it appears there is functionality
        // here in other overlays to check g_Tilemap.x. Looks like this was
        // removed in LIB code.
        break;
    case 6:
        if (D_us_80181AD0 != 0) {
            g_Tilemap.x = 0;
            g_Tilemap.width = 0x500;
            self->step++;
            return;
        }
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
        if (facingLeft != self->ext.lockCamera.unk88) {
            self->ext.lockCamera.unk88 = facingLeft;
            params = (params << 3) + facingLeft;
            dataPtr = &tileMapProps[params];
            self->ext.lockCamera.unk7E = 0;
            self->ext.lockCamera.unk8A = 0x10;
            params = tilemap->scrollX.i.hi;
            if (params != *dataPtr && self->ext.lockCamera.unk7C) {
                self->ext.lockCamera.unk7E = 1;
                tilemap->x = params;
            } else {
                tilemap->x = *dataPtr;
            }
            self->ext.lockCamera.unk80 = *dataPtr++;
            facingLeft = tilemap->scrollY.i.hi - 4;
            if (facingLeft != *dataPtr && !self->ext.lockCamera.unk7C) {
                self->ext.lockCamera.unk7E |= 2;
                tilemap->y = facingLeft;
            } else {
                tilemap->y = *dataPtr;
            }
            self->ext.lockCamera.unk82 = *dataPtr++;
            params += 0x100;
            if (params != *dataPtr && self->ext.lockCamera.unk7C) {
                self->ext.lockCamera.unk7E |= 4;
                tilemap->width = params;
            } else {
                tilemap->width = *dataPtr;
            }
            self->ext.lockCamera.unk84 = *dataPtr++;
            facingLeft += 0x100;
            if (facingLeft != *dataPtr && !self->ext.lockCamera.unk7C) {
                self->ext.lockCamera.unk7E |= 8;
                tilemap->height = facingLeft;
            } else {
                tilemap->height = *dataPtr;
            }
            self->ext.lockCamera.unk86 = *dataPtr;
        }
    } else {
        self->ext.lockCamera.unk88 = 2;
    }

    if (self->ext.lockCamera.unk7E) {
        if (!(--self->ext.lockCamera.unk8A)) {
            tilemap->x = self->ext.lockCamera.unk80;
            tilemap->y = self->ext.lockCamera.unk82;
            tilemap->width = self->ext.lockCamera.unk84;
            tilemap->height = self->ext.lockCamera.unk86;
            self->ext.lockCamera.unk7E = 0;
            return;
        }
        var_s4 = (self->ext.lockCamera.unk80 - tilemap->x) / 2;
        if (var_s4) {
            if (var_s4 > 0) {
                tilemap->x += 2;
            } else {
                tilemap->x -= 2;
            }
        } else {
            tilemap->x = self->ext.lockCamera.unk80;
            self->ext.lockCamera.unk7E &= ~1;
        }
        var_s4 = (self->ext.lockCamera.unk82 - tilemap->y) / 2;
        if (var_s4) {
            if (var_s4 > 0) {
                tilemap->y += 2;
            } else {
                tilemap->y -= 2;
            }
        } else {
            tilemap->y = self->ext.lockCamera.unk82;
            self->ext.lockCamera.unk7E &= ~2;
        }
        var_s4 = (self->ext.lockCamera.unk84 - tilemap->width) / 2;
        if (var_s4) {
            if (var_s4 > 0) {
                tilemap->width += 2;
            } else {
                tilemap->width -= 2;
            }
        } else {
            tilemap->width = self->ext.lockCamera.unk84;
            self->ext.lockCamera.unk7E &= ~4;
        }
        var_s4 = (self->ext.lockCamera.unk86 - tilemap->height) / 2;
        if (var_s4) {
            if (var_s4 > 0) {
                tilemap->height += 2;
            } else {
                tilemap->height -= 2;
            }
        } else {
            tilemap->height = self->ext.lockCamera.unk86;
            self->ext.lockCamera.unk7E &= ~8;
        }
    }
}
