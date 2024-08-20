// Weapon ID #34. Used by weapons:
// Shotel, Unknown#176
#include "weapon_private.h"
#include "w_034_1.h"
#include "w_034_2.h"
#define g_Animset w_034_1
#define g_Animset2 w_034_2

extern u8 D_8007341E;
extern u8 D_8007341F;

static u16 D_F2000_8017A784[] = {
    COLOR16(0, 0, 0, 0),    COLOR16(31, 31, 31, 1), COLOR16(6, 6, 6, 0),
    COLOR16(11, 11, 11, 0), COLOR16(16, 16, 16, 0), COLOR16(21, 21, 21, 0),
    COLOR16(26, 26, 26, 0), COLOR16(31, 31, 31, 0), COLOR16(14, 14, 20, 0),
    COLOR16(4, 4, 4, 0),    COLOR16(11, 7, 4, 0),   COLOR16(19, 11, 0, 0),
    COLOR16(24, 16, 4, 0),  COLOR16(31, 22, 7, 0),  COLOR16(20, 14, 14, 0),
    COLOR16(14, 19, 14, 0), COLOR16(0, 0, 0, 0),    COLOR16(0, 2, 2, 0),
    COLOR16(0, 2, 4, 0),    COLOR16(0, 2, 6, 0),    COLOR16(0, 2, 8, 0),
    COLOR16(0, 2, 10, 0),   COLOR16(0, 2, 12, 0),   COLOR16(0, 2, 14, 0),
    COLOR16(0, 2, 16, 0),   COLOR16(0, 2, 18, 0),   COLOR16(0, 2, 20, 0),
    COLOR16(0, 2, 22, 0),   COLOR16(0, 2, 24, 0),   COLOR16(0, 2, 26, 0),
    COLOR16(0, 2, 28, 0),   COLOR16(0, 2, 30, 0),   COLOR16(0, 0, 0, 0),
    COLOR16(0, 4, 2, 0),    COLOR16(0, 4, 4, 0),    COLOR16(0, 4, 6, 0),
    COLOR16(0, 4, 8, 0),    COLOR16(0, 4, 10, 0),   COLOR16(0, 4, 12, 0),
    COLOR16(0, 4, 14, 0),   COLOR16(0, 4, 16, 0),   COLOR16(0, 4, 18, 0),
    COLOR16(0, 4, 20, 0),   COLOR16(0, 4, 22, 0),   COLOR16(0, 4, 24, 0),
    COLOR16(0, 4, 26, 0),   COLOR16(0, 4, 28, 0),   COLOR16(0, 4, 30, 0),
    COLOR16(0, 0, 0, 0),    COLOR16(0, 6, 2, 0),    COLOR16(0, 6, 4, 0),
    COLOR16(0, 6, 6, 0),    COLOR16(0, 6, 8, 0),    COLOR16(0, 6, 10, 0),
    COLOR16(0, 6, 12, 0),   COLOR16(0, 6, 14, 0),   COLOR16(0, 6, 16, 0),
    COLOR16(0, 6, 18, 0),   COLOR16(0, 6, 20, 0),   COLOR16(0, 6, 22, 0),
    COLOR16(0, 6, 24, 0),   COLOR16(0, 6, 26, 0),   COLOR16(0, 6, 28, 0),
    COLOR16(0, 6, 30, 0),   COLOR16(0, 0, 0, 0),    COLOR16(0, 8, 2, 0),
    COLOR16(0, 8, 4, 0),    COLOR16(0, 8, 6, 0),    COLOR16(0, 8, 8, 0),
    COLOR16(0, 8, 10, 0),   COLOR16(0, 8, 12, 0),   COLOR16(0, 8, 14, 0),
    COLOR16(0, 8, 16, 0),   COLOR16(0, 8, 18, 0),   COLOR16(0, 8, 20, 0),
    COLOR16(0, 8, 22, 0),   COLOR16(0, 8, 24, 0),   COLOR16(0, 8, 26, 0),
    COLOR16(0, 8, 28, 0),   COLOR16(0, 8, 30, 0)};

static u16 D_F2000_8017A824[] = {
    0x0201, 0x0402, 0x0604, 0x0605, 0x0606, 0x0607, 0x0808,
    0x0A09, 0x0A0A, 0x0A0B, 0x0A0C, 0x0A0D, 0xFFFF, 0x0000,
};

static u16 D_F2000_8017A840[] = {
    0x0C0E, 0x0E0F, 0x1010, 0x1011, 0x1012, 0x1013, 0x1214,
    0x0A15, 0x0A1D, 0x0A1E, 0x0A1F, 0x0A20, 0xFFFF, 0x0000,
};

static u16 D_F2000_8017A85C[] = {
    0x0C0E, 0x1416, 0x1617, 0x1618, 0x1619, 0x161A, 0x181B,
    0x0A1C, 0x0A1D, 0x0A1E, 0x0A1F, 0x0A20, 0xFFFF, 0x0000,
};

static u16 D_F2000_8017A878[] = {
    0x1A21, 0x1C22, 0x1E23, 0x1E24, 0x1E25,
    0x1E26, 0x2027, 0x0A28, 0x0A29, 0xFFFF,
};

static u16 D_F2000_8017A88C[] = {
    0x222A, 0x242B, 0x262C, 0x262D, 0x262E,
    0x262F, 0x2830, 0x0A31, 0x0A39, 0xFFFF,
};

static u16 D_F2000_8017A8A0[] = {
    0x222A, 0x2A32, 0x2C33, 0x2C34, 0x2C35,
    0x2C36, 0x2E37, 0x0A38, 0x0A39, 0xFFFF,
};

static s8 D_F2000_8017A8B4[] = {
    0x00, 0x00, 0x00, 0x00, 0x07, 0xE8, 0x07, 0x04, 0x1B, 0xEB, 0x1A, 0x08,
    0x1E, 0xF2, 0x15, 0x06, 0x18, 0xF7, 0x0F, 0x04, 0xE0, 0xE1, 0x00, 0x00,
    0xFE, 0xF8, 0x07, 0x04, 0x11, 0xFB, 0x1A, 0x08, 0x16, 0x03, 0x15, 0x06,
    0x12, 0x05, 0x0F, 0x04, 0x07, 0x03, 0x10, 0x10, 0x15, 0x14, 0x0F, 0x0B,
    0x0C, 0x11, 0x0F, 0x05, 0x03, 0xE5, 0x09, 0x05, 0x16, 0xE8, 0x1A, 0x08,
    0x19, 0xF0, 0x17, 0x06, 0x17, 0xF3, 0x13, 0x04, 0xFC, 0xE4, 0x08, 0x04,
    0x11, 0xEA, 0x1A, 0x08, 0x18, 0xF2, 0x15, 0x06, 0x11, 0xF5, 0x11, 0x04,
    0x12, 0xFD, 0x17, 0x15, 0x14, 0x08, 0x17, 0x0A, 0x0D, 0x05, 0x11, 0x07,
    0x01, 0x01, 0x10, 0x10,
};

static u16* D_F2000_8017A918[] = {
    D_F2000_8017A824, D_F2000_8017A824, D_F2000_8017A840, D_F2000_8017A85C,
    D_F2000_8017A878, D_F2000_8017A88C, D_F2000_8017A8A0,
};

static WeaponAnimation D_F2000_8017A934[] = {
    {D_F2000_8017A918, D_F2000_8017A8B4, 0, SFX_WEAPON_SWISH_B, 0x92, 0x04, 0}};

static u16* g_WeaponCluts[] = {D_F2000_8017A784, D_F2000_8017A784};
static s32 g_HandId = HAND_ID;

#include "shared.h"

static void EntityWeaponAttack(Entity* self) {
    WeaponAnimation* anim;
    s8 animIndex;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;
    animIndex = (self->params >> 8) & 0x7f;
    anim = &D_F2000_8017A934[animIndex];
    if (PLAYER.ext.weapon.anim < anim->frameStart ||
        PLAYER.ext.weapon.anim >= (anim->frameStart + 7) ||
        g_Player.unk46 == 0) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(16);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->palette += anim->palette;
        self->flags = FLAG_UNK_20000 | FLAG_UNK_40000;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE;
        SetWeaponProperties(self, 0);
        self->step++;
    }

    self->ext.weapon.anim = PLAYER.ext.weapon.anim - anim->frameStart;

    if ((PLAYER.animFrameDuration == 1) &&
        (PLAYER.animFrameIdx == anim->soundFrame)) {
        g_api.PlaySfx(anim->soundId);
    }

    if (g_api.UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }

    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

static s32 func_ptr_80170004(Entity* self) {
    s16 xDist;
    s16 yDist;
    s16 offsetY;
    s16 var_s1;
    s16 xVar;
    s16 yVar;
    s16 angleTarget;
    s16 angleDiff;
    s16 angle;

    switch (self->step) {
    case 0:
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->unk5A = 0x64;
        self->palette = 0x110;
        if (g_HandId != 0) {
            self->unk5A = 0x66;
            self->animSet += 2;
            self->palette += 0x18;
        }
        self->animCurFrame = 0x3A;
        self->facingLeft = PLAYER.facingLeft;
        self->zPriority = PLAYER.zPriority - 2;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 | FLAG_UNK_20000;
        self->drawMode = DRAW_TPAGE;
        SetSpeedX(FIX(4.5));
        self->ext.sword.unk7E = 0x1C;
        offsetY = PLAYER.posY.i.hi + PLAYER.hitboxOffY;
        self->posY.i.hi = offsetY - 8;
        if (PLAYER.step != 2) {
            self->posY.i.hi = offsetY - 0x10;
        }

        if (self->facingLeft) {
            self->posX.i.hi = PLAYER.posX.i.hi - PLAYER.hitboxOffX;
            self->ext.sword.unk7C = 0x2000;
        } else {
            self->posX.i.hi = PLAYER.posX.i.hi + PLAYER.hitboxOffX;
            self->ext.sword.unk7C = -0x2000;
        }

        self->velocityX += PLAYER.velocityX;
        self->ext.sword.unk84 = 0x200;
        self->velocityY = FIX(-0.25);
        self->ext.sword.unk86 = 0x400;
        self->rotZ = 0;
        self->drawFlags |= FLAG_DRAW_ROTZ;
        SetWeaponProperties(self, 0);
        DestroyEntityWeapon(true);
        self->hitboxHeight = 9;
        self->hitboxWidth = 9;
        g_Player.D_80072F00[10] = 4;
        self->step++;
        break;
    case 1:
        self->rotZ += 0x200;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityX += self->ext.sword.unk7C;
        self->velocityY += self->ext.sword.unk86;
        self->ext.sword.unk86 = self->ext.sword.unk86; // ???
        if (--self->ext.sword.unk7E == 0) {
            self->ext.sword.unk82 =
                ratan2(-self->velocityY, self->velocityX) & 0xFFF;
            self->step++;
        }
        break;
    case 2:
        self->rotZ += 0x200;
        var_s1 = self->ext.sword.unk84;
        self->ext.sword.unk84 += 0x10;
        xDist = abs((PLAYER.posX.i.hi + PLAYER.hitboxOffX) - self->posX.i.hi);
        if (xDist < (D_8007341E + self->hitboxWidth) >> 1) {
            yDist =
                abs((PLAYER.posY.i.hi + PLAYER.hitboxOffY) - self->posY.i.hi);
            if (yDist < (D_8007341F + self->hitboxHeight) >> 1) {
                DestroyEntity(self);
                return;
            }
        }
        xVar = (PLAYER.posX.i.hi + PLAYER.hitboxOffX) - self->posX.i.hi;
        yVar = (PLAYER.posY.i.hi + PLAYER.hitboxOffY) - self->posY.i.hi;
        angleTarget = ratan2(-yVar, xVar) & 0xFFF;
        angle = self->ext.heavenSword.unk82 & 0xFFF;
        angleDiff = abs(angle - angleTarget);
        if (var_s1 > angleDiff) {
            var_s1 = angleDiff;
        }
        if (angle < angleTarget) {
            if (angleDiff < 0x800) {
                angle += var_s1;
            } else {
                angle -= var_s1;
            }
        } else {
            if (angleDiff < 0x800) {
                angle -= var_s1;
            } else {
                angle += var_s1;
            }
        }
        self->ext.sword.unk82 = angle & 0xFFF;
        self->posX.val += rcos(self->ext.sword.unk82) << 6;
        self->posY.val -= rsin(self->ext.sword.unk82) << 6;
        break;
    }

    if (!(g_GameTimer & 7)) {
        g_api.PlaySfx(SFX_WEAPON_SWISH_B);
    }
    return;
}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 34; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
