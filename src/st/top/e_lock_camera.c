// SPDX-License-Identifier: AGPL-3.0-or-later
#include "top.h"

static u8 entityLockCameraHitbox[] = {
    0x20, 0x40, 0x20, 0x20, 0x40,
};

static u8 entityLockCameraData[8] = {
    0, 1, 0, 0, 1,
};

static u16 entityLockCameraTilemapProps[] = {
    0x0000, 0x0000, 0x0800, 0x0800, 0x0400, 0x02FB, 0x0800, 0x03FB,
    0x0400, 0x02FB, 0x0800, 0x03FB, 0x0400, 0x02FB, 0x0800, 0x03FB,
    0x0000, 0x02FB, 0x0800, 0x03FB, 0x0000, 0x0000, 0x0800, 0x03FB,
    0x0000, 0x0000, 0x0800, 0x0800, 0x0000, 0x02FB, 0x0800, 0x03FB,
    0x0000, 0x02FB, 0x0800, 0x03FB, 0x0000, 0x02FB, 0x0800, 0x03FB,
};

#include "../player_is_within_hitbox.h"

extern EInit g_EInitLockCamera;

void OVL_EXPORT(EntityLockCamera)(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    u16* dataPtr;
    // These vars are all reused for things; hard to make good names :(
    u16 var_s2;
    u16 var_s3;
    s16 var_s4;

    if ((self->params == 0) &&
        (g_api.TimeAttackController(
             TIMEATTACK_EVENT_SAVE_RICHTER, TIMEATTACK_GET_RECORD) != 0)) {
        self->params = 3;
    }
    if ((self->params == 1) &&
        (g_api.TimeAttackController(
             TIMEATTACK_EVENT_SAVE_RICHTER, TIMEATTACK_GET_RECORD) != 0)) {
        self->params = 4;
    }

    FntPrint("set_no:%02x\n", self->params);
    var_s3 = self->params;
    if (!self->step) {
        InitializeEntity(g_EInitLockCamera);
        self->hitboxState = 1;
        var_s2 = self->ext.lockCamera.unk7C = entityLockCameraData[var_s3];
        if (var_s2) {
            self->hitboxWidth = entityLockCameraHitbox[var_s3];
            self->hitboxHeight = 0x14;
        } else {
            self->hitboxWidth = 0x14;
            self->hitboxHeight = entityLockCameraHitbox[var_s3];
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
            var_s3 = (var_s3 << 3) + var_s2;
            dataPtr = &entityLockCameraTilemapProps[var_s3];
            self->ext.lockCamera.unk7E = 0;
            self->ext.lockCamera.unk8A = 0x10;
            var_s3 = tilemap->scrollX.i.hi;
            if (var_s3 != *dataPtr && self->ext.lockCamera.unk7C) {
                self->ext.lockCamera.unk7E = 1;
                tilemap->x = var_s3;
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
            var_s3 += 0x100;
            if (var_s3 != *dataPtr && self->ext.lockCamera.unk7C) {
                self->ext.lockCamera.unk7E |= 4;
                tilemap->width = var_s3;
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
        } else {
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

    FntPrint("x_min:%02x\n", tilemap->x);
}
