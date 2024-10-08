// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_us_801C1854);

#include "../player_is_within_hitbox.h"

extern u16 D_us_80180ADC[];
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

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_us_801C1E48);

s16 func_us_801C1F98(Primitive* prim, s16 arg1) {
    s16 ret = arg1;
    s16 temp_v0;

    prim->x2 = arg1;
    prim->x0 = arg1;
    ret += 0x20;
    prim->drawMode = DRAW_UNK02;
    prim->v0 = prim->v1 = 0x50;
    prim->v2 = prim->v3 = 0x60;
    prim->y0 = prim->y1 = 0x2C;
    prim->y2 = prim->y3 = 0x3C;
    prim->u0 = prim->u2 = 2;

    if (ret > 0xB0) {
        temp_v0 = 0xB2 - arg1;
        prim->u1 = prim->u3 = temp_v0;
        ret = 0;
        prim->x1 = prim->x3 = 0xB0;
    } else {
        prim->u1 = prim->u3 = 0x22;
        prim->x1 = prim->x3 = ret;
    }
    return ret;
}

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_us_801C2044);

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_us_801C2184);

extern u16 D_us_80180B60[];
void func_us_801C26B8(Entity* self) {
    Entity* entity = &self[self->params];
    s32 step = self->step;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B60);
        if (self->params & 16) {
            self->animCurFrame = self->params & 15;
            self->zPriority = 0x6A;
            self->step = 2;
            return;
        }
        self->animCurFrame = 0;
        break;

    case 1:
        self->posX.i.hi = entity->posX.i.hi;
        if (self->params == step) {
            self->posY.i.hi = entity->posY.i.hi + 35;
            self->ext.generic.unk80.modeS8.unk0 =
                GetPlayerCollisionWith(self, 12, 8, 4);
        } else {
            self->posY.i.hi = entity->posY.i.hi - 24;
            self->ext.generic.unk80.modeS8.unk0 =
                GetPlayerCollisionWith(self, 12, 8, 6);
        }
        break;
    }
}

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_us_801C27A4);

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_us_801C2A34);

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_us_801C2B24);

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_us_801C2CD8);

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_us_801C2E7C);

void func_us_801C3308(Entity* self) {
    g_CastleFlags[CASTLE_FLAG_1] = 1;
    DestroyEntity(self);
}

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_us_801C3334);

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", EntityWargExplosionPuffOpaque);