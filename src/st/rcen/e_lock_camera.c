// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcen.h"

#include "../player_is_within_hitbox.h"

extern EInit g_EInitLockCamera;

extern EInit g_EInitLockCamera;

static u8 hitboxes[] = {0x20, 0x20, 0x20, 0x20};
static u8 entityLockCameraData[] = {0x01, 0x00, 0x00, 0x00};
static u16 tileMapProps[] = {
    0x0100, 0x00FB, 0x0200, 0x01FB, 0x0000, 0x0000, 0x0300, 0x0300,
};

void OVL_EXPORT(EntityLockCamera)(Entity* self) {
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
        // nb. needed for PSP but unused
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

    // nb. needed for PSP but unused
    switch (self->params) {
    case 4:
        break;
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
