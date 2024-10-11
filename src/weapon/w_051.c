// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #51. Used by weapons:
// Estoc, Claymore, Flamberge, Zwei hander, Obsidian sword, Great Sword,
// Unknown#182, Unknown#183, Unknown#184, Unknown#185
#include "weapon_private.h"
#include "w_051_1.h"
#include "w_051_2.h"
#define g_Animset w_051_1
#define g_Animset2 w_051_2
#include "sfx.h"

static u16 D_169000_8017A950[N_ARRAY_PAL][COLORS_PER_PAL] = {
    {0x0000, 0x0421, 0x04CA, 0x152F, 0x2173, 0x1218, 0x1EDF, 0x20A4, 0x03E0,
     0x3BF6, 0x0623, 0x0000, 0x45A7, 0x5A4F, 0x5F37, 0x6F99},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
     0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}};
static u16 D_169000_8017A990[N_ARRAY_PAL][COLORS_PER_PAL] = {
    {0x0000, 0x0421, 0x04CA, 0x152F, 0x2173, 0x1218, 0x1EDF, 0x20A4, 0x03E0,
     0x3BF6, 0x0623, 0x0000, 0x01DB, 0x0131, 0x00CB, 0x4215},
    {0x0000, 0x821F, 0x81FD, 0x81DB, 0x81B9, 0x8197, 0x8175, 0x8153, 0x8131,
     0x810F, 0x80ED, 0x80CB, 0x80A9, 0x8087, 0x8065, 0x8044}};
static u16 D_169000_8017A9D0[N_ARRAY_PAL][COLORS_PER_PAL] = {
    {0x0000, 0x0421, 0x04CA, 0x152F, 0x2173, 0x1218, 0x1EDF, 0x20A4, 0x03E0,
     0x3BF6, 0x0623, 0x0000, 0x45A7, 0x5A4F, 0x5F37, 0x6F99},
    {0x0000, 0xFE00, 0xF5E0, 0xEDC0, 0xE5A0, 0xDD80, 0xD560, 0xCD40, 0xC520,
     0xBD00, 0xB4E0, 0xACC0, 0xA4A0, 0x9C80, 0x9460, 0x9040},
    {0x0000, 0x0421, 0x04CA, 0x152F, 0x2173, 0x1218, 0x1EDF, 0x20A4, 0x03E0,
     0x3BF6, 0x0623, 0x0000, 0x08A2, 0x0882, 0x0862, 0x0842},
    {0x0000, 0x83E0, 0x83A0, 0x8360, 0x8320, 0x82E0, 0x82A0, 0x8260, 0x8220,
     0x81E0, 0x81A0, 0x8160, 0x8120, 0x80E0, 0x80A0, 0x8080}};

static s16 D_169000_8017AA50[] = {
    0x201, 0x402, 0x3203, 0x3204, 0x3205, 0x3206, 0x3407,
    0xC08, 0xE09, 0x100A, 0x100B, 0x100C, 0x100D, 0xFFFF,
};

static s16 D_169000_8017AA6C[] = {
    0x0E0E, 0x120F, 0x3610, 0x3611, 0x3612, 0x3613, 0x1814,
    0x1A15, 0x1A16, 0x101D, 0x101E, 0x101F, 0x1020, 0xFFFF,
};

static s16 D_169000_8017AA88[] = {
    0x0E0E, 0x120F, 0x3817, 0x3818, 0x3A19, 0x3C1A, 0x241B,
    0x241C, 0x101D, 0x101E, 0x101F, 0x1020, 0xFFFF,
};

static s16 D_169000_8017AAA4[] = {
    0x0221, 0x0422, 0x3223, 0x3224, 0x3225, 0x3E26, 0x3427,
    0x0C28, 0x0E29, 0x102A, 0x102B, 0x102C, 0x102D, 0xFFFF,
};

static s16 D_169000_8017AAC0[] = {
    0x2A2E, 0x042F, 0x3E30, 0x3E31, 0x3E32, 0x3E33, 0x3434,
    0x0C35, 0x0E36, 0x103D, 0x103E, 0x103F, 0x1040, 0xFFFF,
};

static s16 D_169000_8017AADC[] = {
    0x2A2E, 0x042F, 0x4037, 0x4038, 0x4039, 0x423A, 0x423B,
    0x0E3C, 0x103D, 0x103E, 0x103F, 0x1040, 0xFFFF,
};

static s16 D_169000_8017AAF8[] = {
    0x0201, 0x0402, 0x0603, 0x0804, 0x0805, 0x0806, 0x0A07,
    0x0C08, 0x0E09, 0x100A, 0x100B, 0x100C, 0x100D, 0xFFFF,
};

static s16 D_169000_8017AB14[] = {
    0x0E0E, 0x120F, 0x1410, 0x1611, 0x1612, 0x1613, 0x1814,
    0x1A15, 0x1A16, 0x101D, 0x101E, 0x101F, 0x1020, 0xFFFF,
};

static s16 D_169000_8017AB30[] = {
    0x0E0E, 0x120F, 0x1C17, 0x1E18, 0x2019, 0x221A, 0x241B,
    0x241C, 0x101D, 0x101E, 0x101F, 0x1020, 0xFFFF,
};

static s16 D_169000_8017AB4C[] = {
    0x0221, 0x0422, 0x2623, 0x0824, 0x0825, 0x2826, 0x0A27,
    0x0C28, 0x0E29, 0x102A, 0x102B, 0x102C, 0x102D, 0xFFFF,
};

static s16 D_169000_8017AB68[] = {
    0x2A2E, 0x42F, 0x2630, 0x2831, 0x2832, 0x2833, 0x0A34,
    0x0C35, 0xE36, 0x103D, 0x103E, 0x103F, 0x1040, 0xFFFF,
};

static s16 D_169000_8017AB84[] = {
    0x2A2E, 0x042F, 0x2C37, 0x2E38, 0x2E39, 0x303A, 0x303B,
    0x0E3C, 0x103D, 0x103E, 0x103F, 0x1040, 0xFFFF,
};

static s16 D_169000_8017ABA0[] = {
    0x0221, 0x0422, 0x2623, 0x0824, 0x0825, 0x0805, 0x0806, 0x0A07,
    0x0C08, 0x0E09, 0x100A, 0x100B, 0x100C, 0x100D, 0xFFFF,
};

static s16 D_169000_8017ABC0[] = {
    0x0221, 0x0422, 0x2623, 0x3224, 0x3225, 0x3205, 0x3206, 0x3407,
    0x0C08, 0x0E09, 0x100A, 0x100B, 0x100C, 0x100D, 0xFFFF,
};

static s8 hitboxes[][4] = {
    {/* X */ 0, /* Y */ 0, /* W */ 0, /* H */ 0},
    {/* X */ 7, /* Y */ -26, /* W */ 11, /* H */ 6},
    {/* X */ -13, /* Y */ -23, /* W */ 11, /* H */ 6},
    {/* X */ 19, /* Y */ -3, /* W */ 24, /* H */ 11},
    {/* X */ 47, /* Y */ -14, /* W */ 29, /* H */ 6},
    {/* X */ 28, /* Y */ -18, /* W */ 20, /* H */ 7},
    {/* X */ 18, /* Y */ -16, /* W */ 11, /* H */ 8},
    {/* X */ 5, /* Y */ -10, /* W */ 11, /* H */ 8},
    {/* X */ -32, /* Y */ -31, /* W */ 0, /* H */ 0},
    {/* X */ -18, /* Y */ -4, /* W */ 10, /* H */ 4},
    {/* X */ 14, /* Y */ 16, /* W */ 31, /* H */ 12},
    {/* X */ 39, /* Y */ 5, /* W */ 29, /* H */ 7},
    {/* X */ 18, /* Y */ -1, /* W */ 14, /* H */ 4},
    {/* X */ 4, /* Y */ 2, /* W */ 12, /* H */ 7},
    {/* X */ 15, /* Y */ 22, /* W */ 30, /* H */ 12},
    {/* X */ 37, /* Y */ 29, /* W */ 18, /* H */ 13},
    {/* X */ 35, /* Y */ 23, /* W */ 18, /* H */ 13},
    {/* X */ 24, /* Y */ 8, /* W */ 22, /* H */ 6},
    {/* X */ 7, /* Y */ 5, /* W */ 18, /* H */ 6},
    {/* X */ 22, /* Y */ -4, /* W */ 38, /* H */ 14},
    {/* X */ 33, /* Y */ -17, /* W */ 36, /* H */ 6},
    {/* X */ -8, /* Y */ -26, /* W */ 8, /* H */ 5},
    {/* X */ 26, /* Y */ 11, /* W */ 34, /* H */ 19},
    {/* X */ 33, /* Y */ 10, /* W */ 28, /* H */ 16},
    {/* X */ 21, /* Y */ -10, /* W */ 20, /* H */ 5},
    {/* X */ 43, /* Y */ -14, /* W */ 25, /* H */ 6},
    {/* X */ 26, /* Y */ -18, /* W */ 18, /* H */ 7},
    {/* X */ 35, /* Y */ 5, /* W */ 25, /* H */ 7},
    {/* X */ 35, /* Y */ 29, /* W */ 16, /* H */ 13},
    {/* X */ 33, /* Y */ 23, /* W */ 16, /* H */ 13},
    {/* X */ 20, /* Y */ 8, /* W */ 18, /* H */ 6},
    {/* X */ 29, /* Y */ -17, /* W */ 32, /* H */ 6},
    {/* X */ 29, /* Y */ 10, /* W */ 24, /* H */ 16},
    {/* X */ 17, /* Y */ -10, /* W */ 16, /* H */ 5},
};

static u16* D_169000_8017AC68[] = {
    D_169000_8017AA50, D_169000_8017AA50, D_169000_8017AA6C, D_169000_8017AA88,
    D_169000_8017AAA4, D_169000_8017AAC0, D_169000_8017AADC,
};

static u16* D_169000_8017AC84[] = {
    D_169000_8017AAF8, D_169000_8017AAF8, D_169000_8017AB14, D_169000_8017AB30,
    D_169000_8017AB4C, D_169000_8017AB68, D_169000_8017AB84,
};

static u16* D_169000_8017ACA0[] = {
    D_169000_8017ABA0, D_169000_8017ABA0, D_169000_8017ABA0, D_169000_8017ABA0,
    D_169000_8017ABA0, D_169000_8017ABA0, D_169000_8017ABA0,
};

static u16* D_169000_8017ACBC[] = {
    D_169000_8017ABC0, D_169000_8017ABC0, D_169000_8017ABC0, D_169000_8017ABC0,
    D_169000_8017ABC0, D_169000_8017ABC0, D_169000_8017ABC0,
};

static WeaponAnimation D_169000_8017ACD8[] = {
    {D_169000_8017AC68, hitboxes, 0, SFX_FIRE_SHOT, 0x68, 4},
    {D_169000_8017AC84, hitboxes, 2, SFX_FIRE_SHOT, 0x68, 4},
    {D_169000_8017AC84, hitboxes, 4, SFX_FIRE_SHOT, 0x68, 4},
    {D_169000_8017AC84, hitboxes, 6, SFX_FIRE_SHOT, 0x68, 4},
};

static WeaponAnimation D_169000_8017AD18[] = {
    {D_169000_8017ACBC, hitboxes, 0, SFX_WEAPON_SWISH_C, 0xD6, 4},
    {D_169000_8017ACA0, hitboxes, 0, SFX_WEAPON_SWISH_C, 0xD6, 4},
    {D_169000_8017ACA0, hitboxes, 0, SFX_WEAPON_SWISH_C, 0xD6, 4},
    {D_169000_8017ACA0, hitboxes, 0, SFX_WEAPON_SWISH_C, 0xD6, 4},
};

static s16 D_169000_8017AD58[] = {
    0xAC68, 0x8017, 0xABE0, 0x8017, 0x0000, 0x06A2, 0x00D6, 0x0000,
};

static s16 _r = 0;
static s16 _b = 0;
static s16 _g = 0;
static s16 color_step = 0;
static s16 _a = 0;
static s32 color_table[] = {
    /* 0 */ 0, 0, 0, 0, 16, 15, 0,  1,
    /* 1 */ 0, 0, 0, 0, 0,  16, 16, 1,
    /* 2 */ 8, 8, 8, 0, 8,  16, 8,  1,
    /* 3 */ 0, 0, 0, 0, 0,  0,  0,  0,
    /* 4 */ 0, 0, 0, 0, 16, 15, 0,  1,
    /* 5 */ 0, 0, 0, 0, 0,  16, 16, 1,
    /* 6 */ 8, 8, 8, 0, 8,  16, 8,  1,
    /* 7 */ 0, 0, 0, 0, 0,  0,  0,  0,
};

typedef struct {
    s16 isFlipped;
    s16 timer;
    s16 rotation;
} AnimProperties;

static AnimProperties D_169000_8017AE74[] = {
    {0, 37, 0x100}, {1, 32, 0xF00}, {0, 48, 0x000}, {1, 24, 0x080},
    {0, 37, 0xF40}, {1, 32, 0x0C0}, {0, 48, 0x000}, {1, 24, 0x140},
};

static u16 D_169000_8017AEA4[] = {
    0x80, 0x80, 0x90, 0x00, 0xC0, 0x60, 0x00, 0x00,
    0x00, 0x60, 0xA0, 0x00, 0x40, 0x48, 0x40, 0x00,
};

static u16* g_WeaponCluts[] = {
    D_169000_8017A950, D_169000_8017A990, D_169000_8017A9D0};

static s32 g_HandId = 0;

static s32 D_169000_8017C0E0;

#include "shared.h"

void func_169000_8017B1DC(s32 arg0) {
    RECT rect;
    s32 colorsChanged;
    s32 palIndex;
    u16 color;

    colorsChanged = 0;
    switch (color_step) {
    case 0:
        _r += 2;
        _g += 2;
        _b += 2;
        if (_r >= color_table[arg0 * 8 + 4]) {
            colorsChanged++;
            _r = color_table[arg0 * 8 + 4];
        }
        if (_g >= color_table[arg0 * 8 + 5]) {
            colorsChanged++;
            _g = color_table[arg0 * 8 + 5];
        }
        if (_b >= color_table[arg0 * 8 + 6]) {
            colorsChanged++;
            _b = color_table[arg0 * 8 + 6];
        }
        if (!_r && !_g && !_b) {
            _a = 0;
        } else {
            _a = 1;
        }
        if (colorsChanged == 3) {
            color_step++;
        }
        break;
    case 1:
        _r -= 2;
        _g -= 2;
        _b -= 2;
        if (_r <= color_table[arg0 * 8]) {
            colorsChanged++;
            _r = color_table[arg0 * 8];
        }
        if (_g <= color_table[arg0 * 8 + 1]) {
            colorsChanged++;
            _g = color_table[arg0 * 8 + 1];
        }
        if (_b <= color_table[arg0 * 8 + 2]) {
            colorsChanged++;
            _b = color_table[arg0 * 8 + 2];
        }
        if (!_r && !_g && !_b) {
            _a = 0;
        } else {
            _a = 1;
        }
        if (colorsChanged == 3) {
            color_step++;
        }
        break;
    case 2:
        return;
    }

    color = COLOR16(_r, _g, _b, _a);
    palIndex = (g_HandId * 0x180);
    palIndex += arg0 << 5;
    D_8006EDCC[0][0x2B + palIndex] = color;

    rect.x = 0;
    rect.y = 0xF1;
    rect.w = 256;
    rect.h = 3;
    LoadImage(&rect, (u_long*)D_8006EDCC);
}

static void EntityWeaponAttack(Entity* self) {
    WeaponAnimation* anim;
    s16 subType;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;
    subType = self->params & 0x7FFF;
    subType >>= 8;
    anim = &D_169000_8017ACD8[subType];
    if (PLAYER.ext.player.anim < anim->frameStart ||
        PLAYER.ext.player.anim >= anim->frameStart + 7 || !g_Player.unk46) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        self->animSet = 10;
        self->palette = 0x110;
        self->unk5A = 100;
        if (g_HandId) {
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->palette += anim->palette;
        self->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED;
        self->zPriority = PLAYER.zPriority - 2;
        if (subType == 1) {
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        }
        if (subType == 2) {
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        }
        if (subType == 3) {
            self->drawMode = DRAW_TPAGE;
        }
        if (subType != 0) {
            _r = D_169000_8017AD58[subType * 0x10 - 2];
            _g = D_169000_8017AD58[subType * 0x10];
            _b = D_169000_8017AD58[subType * 0x10 + 2];
            color_step = 0;
            _a = 0;
        }
        SetWeaponProperties(self, 0);
        self->step++;
        break;
    }
    self->ext.weapon.anim = PLAYER.ext.player.anim - anim->frameStart;
    if (PLAYER.animFrameDuration == 1 &&
        PLAYER.animFrameIdx == anim->soundFrame) {
        g_api.PlaySfx(anim->soundId);
    }
    if (g_api.UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
    if (subType != 0) {
        func_169000_8017B1DC(subType - 1);
    }
}

s32 func_ptr_80170004(Entity* self) {
    WeaponAnimation* anim;
    s16 subType;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;
    subType = self->params & 0x7FFF;
    subType >>= 8;
    anim = &D_169000_8017AD18[subType];
    if (PLAYER.ext.player.anim < 0xD6 || PLAYER.ext.player.anim >= 0xD8) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        self->animSet = 10;
        self->palette = 0x110;
        self->unk5A = 100;
        if (g_HandId) {
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->palette += subType * 2;
        self->zPriority = PLAYER.zPriority - 2;
        if (subType == 1) {
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        }
        if (subType == 2) {
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        }
        if (subType == 3) {
            self->drawMode = DRAW_TPAGE;
        }
        if (subType != 0) {
            _r = D_169000_8017AD58[subType * 0x10 - 2];
            _g = D_169000_8017AD58[subType * 0x10];
            _b = D_169000_8017AD58[subType * 0x10 + 2];
            color_step = 0;
            _a = 0;
        }
        D_169000_8017C0E0 = 0;
        self->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED;
        SetWeaponProperties(self, 0);
        self->step++;
        break;
    }
    self->ext.weapon.anim = PLAYER.ext.player.anim - anim->frameStart;
    if (g_api.UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }
    if (PLAYER.animFrameIdx == 1 && PLAYER.animFrameDuration == 1) {
        g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x3E, 0), 0);
    }
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
    if (subType != 0 && (PLAYER.animFrameIdx != 4 || color_step == 0)) {
        func_169000_8017B1DC(subType - 1);
    }
}

static void func_ptr_80170008(Entity* self) {
    AnimProperties* anim;
    Primitive* prim;
    s16 rot;
    u16 color;
    s16 x;
    s16 y;
    s16 t;
    u32 subType;
    u16 temp_s6;
    u32 tmp_var;
    u8 temp_s3;
    u32 flags;

    color = (g_Entities[0x10].params & 0x7F00) >> 8;
    tmp_var = self->params & 0x7F00;
    subType = tmp_var >> 8;
    temp_s6 = subType & 0xFFFF;
    temp_s3 = 128;
    temp_s3 = g_HandId ? -temp_s3 : 0;
    anim = &D_169000_8017AE74[subType % LEN(D_169000_8017AE74)];
    switch (self->step) {
    case 0:
        self->posX.val = PLAYER.posX.val;
        self->posY.val = PLAYER.posY.val;
        self->facingLeft = PLAYER.facingLeft;
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        prim->u0 = prim->u2 = 128;
        prim->u1 = prim->u3 = 192;
        if (anim->isFlipped) {
            prim->v0 = prim->v1 = temp_s3 | 0x40;
            prim->v2 = prim->v3 = temp_s3;
        } else {
            prim->v0 = prim->v1 = temp_s3;
            prim->v2 = prim->v3 = temp_s3 | 0x40;
        }
        prim->r1 = prim->r3 = D_169000_8017AEA4[color * 4 + 0] + (rand() & 0xF);
        prim->g1 = prim->g3 = D_169000_8017AEA4[color * 4 + 1] + (rand() & 0xF);
        prim->b1 = prim->b3 = D_169000_8017AEA4[color * 4 + 2] + (rand() & 0xF);
        prim->clut = 0x15F;
        prim->r0 = prim->r2 = 0;
        prim->g0 = prim->g2 = 0;
        prim->b0 = prim->b2 = 0;
        prim->tpage = 0x19;
        prim->priority = PLAYER.zPriority + 4;
        prim->drawMode = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_ROTZ;
        prim->drawMode |= FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK40;
        prim->drawMode |= FLAG_DRAW_UNK100;
        if (color == 3) {
            prim->drawMode &= ~(FLAG_DRAW_UNK20 | FLAG_DRAW_UNK40);
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        if (temp_s6 == 0) {
            self->ext.weapon.equipId =
                self->ext.weapon.parent->ext.weapon.equipId;
            SetWeaponProperties(self, 0);
            self->enemyId = self->ext.weapon.parent->enemyId;
            self->hitboxWidth = 30;
            self->hitboxHeight = 16;
            self->hitboxOffX = 8;
        }
        if (!(temp_s6 & 3)) {
            g_api.PlaySfx(SFX_WEAPON_SWISH_C);
        }
        self->ext.weapon.unk82 = color == 0 ? 20 : 30;
        if (self->facingLeft) {
            self->ext.weapon.unk82 = -self->ext.weapon.unk82;
        }
        self->ext.weapon.unk80 = -18;
        self->posX.i.hi += self->ext.weapon.unk82;
        self->posY.i.hi += self->ext.weapon.unk80;
        self->rotZ = anim->rotation;
        self->ext.timer.t = anim->timer;
        self->ext.weapon.unk7E = 0;
        SetSpeedX((rand() * 2) + FIX(6));
        self->step++;
        break;
    }
    self->posX.val += self->velocityX;
    DecelerateX(0x2800);
    if (temp_s6 == 0) {
        u32 tmp = (g_HandId + 1) << 0xC;
        flags = FACTORY(0x3E, self->ext.weapon.unk7E + 1);
        g_api.CreateEntFactoryFromEntity(self, tmp + flags, 0);
    }
    prim = &g_PrimBuf[self->primIndex];
    self->ext.weapon.unk7E++;
    if (self->ext.weapon.unk7E > 8) {
        DestroyEntity(self);
        return;
    }

    x = self->posX.i.hi;
    y = self->posY.i.hi;
    t = self->ext.timer.t;
    rot = self->rotZ;

    rot += 0x600;
    if (self->facingLeft) {
        prim->x0 = x - (((rcos(rot) >> 4) * t) >> 8);
    } else {
        prim->x0 = x + (((rcos(rot) >> 4) * t) >> 8);
    }
    prim->y0 = y - (((rsin(rot) >> 4) * t) >> 9);

    rot -= 0x400;
    if (self->facingLeft) {
        prim->x1 = x - (((rcos(rot) >> 4) * t) >> 8);
    } else {
        prim->x1 = x + (((rcos(rot) >> 4) * t) >> 8);
    }
    prim->y1 = y - (((rsin(rot) >> 4) * t) >> 9);

    rot -= 0x800;
    if (self->facingLeft) {
        prim->x2 = x - (((rcos(rot) >> 4) * t) >> 8);
    } else {
        prim->x2 = x + (((rcos(rot) >> 4) * t) >> 8);
    }
    prim->y2 = y - (((rsin(rot) >> 4) * t) >> 9);

    rot += 0x400;
    if (self->facingLeft) {
        prim->x3 = x - (((rcos(rot) >> 4) * t) >> 8);
    } else {
        prim->x3 = x + (((rcos(rot) >> 4) * t) >> 8);
    }
    prim->y3 = y - (((rsin(rot) >> 4) * t) >> 9);
}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 51; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
