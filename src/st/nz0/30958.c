// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "sfx.h"

void func_801B0958(Entity* self) {
    ObjInit* objInit = &D_80180D64[self->params];

    if (self->step == 0) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->unk5A = objInit->unk5A;
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->drawMode = objInit->drawMode;
        if (objInit->unkC != 0) {
            self->flags = objInit->unkC;
        }
    }
    AnimateEntity(objInit->animFrames, self);
}

#include "../player_is_within_hitbox.h"

extern u16 g_EInitUnkId12[];
static u8 e_801B0AA4_hitbox[] = {32, 32, 32, 32};
static u8 e_801B0AA4_variant[] = {0, 0, 0, 0};
static u16 e_801B0AA4_mapScroll[] = {
    0x0000, 0x00FB, 0x0100, 0x01FB, 0x0000, 0x00FB, 0x0100, 0x01FB,
    0x0000, 0x00FB, 0x0600, 0x01FB, 0x0000, 0x0000, 0x0600, 0x01FB,
};
void func_801B0AA4(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    u16* dataPtr;
    // These vars are all reused for things; hard to make good names :(
    u16 var_s2;
    u16 params;
    s16 var_s4;

    params = self->params;
    if (!self->step) {
        InitializeEntity(g_EInitUnkId12);
        self->hitboxState = 1;
        var_s2 = self->ext.et_801B0AA4.unk7C = e_801B0AA4_variant[params];
        if (var_s2) {
            self->hitboxWidth = e_801B0AA4_hitbox[params];
            self->hitboxHeight = 0x14;
        } else {
            self->hitboxWidth = 0x14;
            self->hitboxHeight = e_801B0AA4_hitbox[params];
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
            params = (params << 3) + var_s2;
            dataPtr = &e_801B0AA4_mapScroll[params];
            self->ext.et_801B0AA4.unk7E = 0;
            self->ext.et_801B0AA4.unk8A = 0x10;
            params = tilemap->scrollX.i.hi;
            if (params != *dataPtr && self->ext.et_801B0AA4.unk7C) {
                self->ext.et_801B0AA4.unk7E = 1;
                tilemap->x = params;
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
            params += 0x100;
            if (params != *dataPtr && self->ext.et_801B0AA4.unk7C) {
                self->ext.et_801B0AA4.unk7E |= 4;
                tilemap->width = params;
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
