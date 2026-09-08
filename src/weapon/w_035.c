// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #35. Used by weapons:
// Red Rust
#include "weapon_private.h"
#include "gen/w_035_1.h"
#include "gen/w_035_2.h"
#define g_Animset w_035_1
#define g_Animset2 w_035_2

static u16 pal0[N_ARRAY_PAL][COLORS_PER_PAL] = {
    {0x0000, 0x1084, 0x048B, 0x10B2, 0x20F9, 0x0D5B, 0x0340, 0x2D6B, 0x4E73,
     0x6B5A, 0x10EB, 0x0173, 0x1218, 0x1EDF, 0x03E0, 0x8014},
    {0x0000, 0x0840, 0x1040, 0x1840, 0x2040, 0x2840, 0x3040, 0x3840, 0x4040,
     0x4840, 0x5040, 0x5840, 0x6040, 0x6840, 0x7040, 0x7840},
    {0x0000, 0x0880, 0x1080, 0x1880, 0x2080, 0x2880, 0x3080, 0x3880, 0x4080,
     0x4880, 0x5080, 0x5880, 0x6080, 0x6880, 0x7080, 0x7880},
    {0x0000, 0x08C0, 0x10C0, 0x18C0, 0x20C0, 0x28C0, 0x30C0, 0x38C0, 0x40C0,
     0x48C0, 0x50C0, 0x58C0, 0x60C0, 0x68C0, 0x70C0, 0x78C0},
    {0x0000, 0x0900, 0x1100, 0x1900, 0x2100, 0x2900, 0x3100, 0x3900, 0x4100,
     0x4900, 0x5100, 0x5900, 0x6100, 0x6900, 0x7100, 0x7900}};

static u16 anim0[] = {
    WPOSE(1, 1), WPOSE(2, 2), WPOSE(3, 2), WPOSE(4, 3), WPOSE(5, 3),
    WPOSE(6, 3), WPOSE(7, 3), WPOSE(8, 3), WPOSE(9, 3), WPOSE_END,
};

static u16 anim1[] = {
    WPOSE(10, 4), WPOSE(11, 5), WPOSE(12, 5), WPOSE(13, 3), WPOSE(14, 3),
    WPOSE(15, 3), WPOSE(16, 3), WPOSE(17, 3), WPOSE(18, 3), WPOSE_END,
};

static u16 anim2[] = {
    WPOSE(19, 6), WPOSE(20, 7), WPOSE(21, 7), WPOSE(22, 3),
    WPOSE(23, 3), WPOSE(24, 3), WPOSE_END,    0x0000,
};

static u16 anim3[] = {
    WPOSE(25, 8), WPOSE(26, 9), WPOSE(27, 9), WPOSE(28, 3),
    WPOSE(29, 3), WPOSE(30, 3), WPOSE_END,    0x0000,
};

static s8 hitboxes[][4] = {
    {0, 0, 0, 0},    {4, -23, 8, 5},   {28, -14, 24, 4}, {-32, -31, 0, 0},
    {-4, -6, 8, 5},  {20, 3, 24, 4},   {1, -25, 8, 5},   {25, -16, 24, 4},
    {-8, -26, 8, 5}, {21, -14, 24, 4},
};

static u16* anims[] = {
    anim0, anim0, anim1, anim1, anim2, anim3, anim3,
};

static WeaponAnimation g_WeaponAnims[] = {
    {anims, hitboxes, 0, SFX_WEAPON_SWISH_B, 0x99, 0x04, 0}};

static u16* g_WeaponCluts[] = {(u16*)pal0, (u16*)pal0};

static s32 g_HandId = HAND_ID;

#include "shared.h"

static void EntityWeaponAttack(Entity* self) {
    WeaponAnimation* anim;
    s8 animIndex;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;
    animIndex = (self->params >> 8) & 0x7f;
    anim = &g_WeaponAnims[animIndex];

    if (PLAYER.ext.weapon.anim < anim->frameStart ||
        PLAYER.ext.weapon.anim >= (anim->frameStart + 7) ||
        g_Player.unk46 == 0) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(16);
        self->palette = PAL_UNK_110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->palette += anim->palette;
        self->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED;
        self->zPriority = PLAYER.zPriority - 2;
        self->blendMode = BLEND_TRANSP;
        SetWeaponProperties(self, 0);
        self->step++;
    }

    self->ext.weapon.anim = PLAYER.ext.weapon.anim - anim->frameStart;

    if ((PLAYER.poseTimer == 1) && (PLAYER.pose == anim->soundFrame)) {
        g_api.PlaySfx(anim->soundId);
    }

    if (g_api.UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }

    self->drawFlags = PLAYER.drawFlags;
    self->scaleY = PLAYER.scaleY;
    self->rotPivotY = PLAYER.rotPivotY;
}

s32 func_ptr_80170004(Entity* self) {}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 35; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
