// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"

#include "../player_is_within_hitbox.h"

extern u16 g_EInitLockCamera[];
static u8 lockCamera_hitbox[] = {32, 32, 32, 32};
static u8 lockCamera_data[] = {0, 0, 0, 0};
static u16 lockCamera_mapScroll[] = {
    0x0000, 0x00FB, 0x0100, 0x01FB, 0x0000, 0x00FB, 0x0100, 0x01FB,
    0x0000, 0x00FB, 0x0600, 0x01FB, 0x0000, 0x0000, 0x0600, 0x01FB,
};
void OVL_EXPORT(EntityLockCamera)(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    u16* dataPtr;
    // These vars are all reused for things; hard to make good names :(
    u16 var_s2;
    u16 params;
    s16 var_s4;

    params = self->params;
    if (!self->step) {
        InitializeEntity(g_EInitLockCamera);
        self->hitboxState = 1;
        var_s2 = self->ext.lockCamera.unk7C = lockCamera_data[params];
        if (var_s2) {
            self->hitboxWidth = lockCamera_hitbox[params];
            self->hitboxHeight = 0x14;
        } else {
            self->hitboxWidth = 0x14;
            self->hitboxHeight = lockCamera_hitbox[params];
        }
        self->ext.lockCamera.unk88 = 2;
    }

    if (PlayerIsWithinHitbox(self)) {
        var_s2 = GetSideToPlayer();
        if (self->ext.lockCamera.unk7C) {
            var_s2 &= 2;
            var_s2 *= 2;
        } else {
            var_s2 &= 1;
            var_s2 *= 4;
        }
        if (var_s2 != self->ext.lockCamera.unk88) {
            self->ext.lockCamera.unk88 = var_s2;
            params = (params << 3) + var_s2;
            dataPtr = &lockCamera_mapScroll[params];
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
            var_s2 = tilemap->scrollY.i.hi - 4;
            if (var_s2 != *dataPtr && !self->ext.lockCamera.unk7C) {
                self->ext.lockCamera.unk7E |= 2;
                tilemap->y = var_s2;
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
            var_s2 += 0x100;
            if (var_s2 != *dataPtr && !self->ext.lockCamera.unk7C) {
                self->ext.lockCamera.unk7E |= 8;
                tilemap->height = var_s2;
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
