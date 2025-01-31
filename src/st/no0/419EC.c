// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

#include "../player_is_within_hitbox.h"

extern u8 D_us_80180E94[];
extern u8 D_us_80180E9C[];
extern u16 D_us_80180EA4[];

void func_801B0AA4(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    u16* dataPtr;
    // These vars are all reused for things; hard to make good names :(
    u16 var_s2;
    u16 var_s3;
    s16 var_s4;

    var_s3 = self->params;
    if (!self->step) {
        InitializeEntity(D_us_80180ADC);
        self->hitboxState = 1;
        var_s2 = self->ext.et_801B0AA4.unk7C = D_us_80180E9C[var_s3];
        if (var_s2) {
            self->hitboxWidth = D_us_80180E94[var_s3];
            self->hitboxHeight = 0x14;
        } else {
            self->hitboxWidth = 0x14;
            self->hitboxHeight = D_us_80180E94[var_s3];
        }
        self->ext.et_801B0AA4.unk88 = 2;
    }

    if (PlayerIsWithinHitbox(self)) {
        var_s2 = GetSideToPlayer();
        if (self->ext.et_801B0AA4.unk7C) {
            var_s2 &= 2;
            var_s2 *= 2;
        } else {
            var_s2 &= 1;
            var_s2 *= 4;
        }
        if (var_s2 != self->ext.et_801B0AA4.unk88) {
            self->ext.et_801B0AA4.unk88 = var_s2;
            var_s3 = (var_s3 << 3) + var_s2;
            dataPtr = &D_us_80180EA4[var_s3];
            self->ext.et_801B0AA4.unk7E = 0;
            self->ext.et_801B0AA4.unk8A = 0x10;
            var_s3 = tilemap->scrollX.i.hi;
            if (var_s3 != *dataPtr && self->ext.et_801B0AA4.unk7C) {
                self->ext.et_801B0AA4.unk7E = 1;
                tilemap->x = var_s3;
            } else {
                tilemap->x = *dataPtr;
            }
            self->ext.et_801B0AA4.unk80 = *dataPtr++;
            var_s2 = tilemap->scrollY.i.hi - 4;
            if (var_s2 != *dataPtr && !self->ext.et_801B0AA4.unk7C) {
                self->ext.et_801B0AA4.unk7E |= 2;
                tilemap->y = var_s2;
            } else {
                tilemap->y = *dataPtr;
            }
            self->ext.et_801B0AA4.unk82 = *dataPtr++;
            var_s3 += 0x100;
            if (var_s3 != *dataPtr && self->ext.et_801B0AA4.unk7C) {
                self->ext.et_801B0AA4.unk7E |= 4;
                tilemap->width = var_s3;
            } else {
                tilemap->width = *dataPtr;
            }
            self->ext.et_801B0AA4.unk84 = *dataPtr++;
            var_s2 += 0x100;
            if (var_s2 != *dataPtr && !self->ext.et_801B0AA4.unk7C) {
                self->ext.et_801B0AA4.unk7E |= 8;
                tilemap->height = var_s2;
            } else {
                tilemap->height = *dataPtr;
            }
            self->ext.et_801B0AA4.unk86 = *dataPtr;
        }
    } else {
        self->ext.et_801B0AA4.unk88 = 2;
    }
    // Unique for NO0
    if (self->params == 4) {
        self->ext.et_801B0AA4.unk8A = 1U;
    }

    if (self->ext.et_801B0AA4.unk7E) {
        if (!(--self->ext.et_801B0AA4.unk8A)) {
            tilemap->x = self->ext.et_801B0AA4.unk80;
            tilemap->y = self->ext.et_801B0AA4.unk82;
            tilemap->width = self->ext.et_801B0AA4.unk84;
            tilemap->height = self->ext.et_801B0AA4.unk86;
            self->ext.et_801B0AA4.unk7E = 0;
            return;
        }
        var_s4 = (self->ext.et_801B0AA4.unk80 - tilemap->x) / 2;
        if (var_s4) {
            if (var_s4 > 0) {
                tilemap->x += 2;
            } else {
                tilemap->x -= 2;
            }
        } else {
            tilemap->x = self->ext.et_801B0AA4.unk80;
            self->ext.et_801B0AA4.unk7E &= ~1;
        }
        var_s4 = (self->ext.et_801B0AA4.unk82 - tilemap->y) / 2;
        if (var_s4) {
            if (var_s4 > 0) {
                tilemap->y += 2;
            } else {
                tilemap->y -= 2;
            }
        } else {
            tilemap->y = self->ext.et_801B0AA4.unk82;
            self->ext.et_801B0AA4.unk7E &= ~2;
        }
        var_s4 = (self->ext.et_801B0AA4.unk84 - tilemap->width) / 2;
        if (var_s4) {
            if (var_s4 > 0) {
                tilemap->width += 2;
            } else {
                tilemap->width -= 2;
            }
        } else {
            tilemap->width = self->ext.et_801B0AA4.unk84;
            self->ext.et_801B0AA4.unk7E &= ~4;
        }
        var_s4 = (self->ext.et_801B0AA4.unk86 - tilemap->height) / 2;
        if (var_s4) {
            if (var_s4 > 0) {
                tilemap->height += 2;
            } else {
                tilemap->height -= 2;
            }
        } else {
            tilemap->height = self->ext.et_801B0AA4.unk86;
            self->ext.et_801B0AA4.unk7E &= ~8;
        }
    }
}
