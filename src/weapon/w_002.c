// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #2. Used by weapons:
// Mace

#include "weapon_private.h"
#include "w_002_1.h"
#include "w_002_2.h"
#define g_Animset w_002_1
#define g_Animset2 w_002_2
#include "sfx.h"

static u16 clut0[N_ARRAY_PAL][COLORS_PER_PAL] = {
    {0x0000, 0x1484, 0x8000, 0x0449, 0x2570, 0x3A33, 0x148F, 0x30D3, 0x217A,
     0x1EBA, 0x0842, 0x18C6, 0x294A, 0x41EF, 0x5694, 0x6F59},
    {0x0000, 0x7440, 0x7D60, 0x7EA0, 0x7F83, 0x3969, 0x59B0, 0x1C10, 0x1D7A,
     0x1F5F, 0x0842, 0x18C6, 0x294A, 0x41EF, 0x5694, 0x6F99},
    {0x0000, 0xB544, 0xC5A8, 0x14A9, 0x214D, 0x2217, 0x36DC, 0x1CA4, 0x30E5,
     0x4988, 0x2E75, 0x1DEE, 0x2507, 0x358A, 0x4A0E, 0x5AD4},
    {0x0000, 0x2E40, 0x3340, 0x4BF0, 0x3BFB, 0x3969, 0x59B0, 0x2D22, 0x3DE5,
     0x53D7, 0x0842, 0x18C6, 0x294A, 0x41EF, 0x5694, 0x6F99},
    {0x0000, 0x2E40, 0x3340, 0x4BF0, 0x3BFB, 0x3969, 0x59B0, 0x2D22, 0x3DE5,
     0x53D7, 0x0842, 0x18C6, 0x294A, 0x41EF, 0x5694, 0x6F99},
    {0x0000, 0x1484, 0x8000, 0x0446, 0x38E9, 0x454B, 0x148F, 0x07E0, 0x03E0,
     0x03E0, 0x0842, 0x20A3, 0x2D27, 0x41CD, 0x5694, 0x7B99},
    {0x0000, 0x059F, 0x2A3F, 0x3B9F, 0x5FFF, 0x1171, 0x21F7, 0x1C10, 0x1D7A,
     0x1F5F, 0x0842, 0x18C6, 0x294A, 0x41EF, 0x5694, 0x6F99},
    {0x0000, 0x1041, 0x7CA6, 0x6C26, 0x5986, 0x5846, 0x58A8, 0x590A, 0x598C,
     0x59EE, 0x5A50, 0x5AD2, 0x6E6B, 0x5F49, 0x40A7, 0x598A},
    {0x0000, 0x2061, 0x7085, 0x5C24, 0x5AD2, 0x5986, 0x5846, 0x58A8, 0x590A,
     0x598C, 0x59EE, 0x5A50, 0x5F49, 0x777A, 0x40A7, 0x598A},
    {0x0000, 0x1041, 0x6464, 0x4C23, 0x5A50, 0x5AD2, 0x5986, 0x5846, 0x58A8,
     0x590A, 0x598C, 0x59EE, 0x6E6B, 0x5F49, 0x40A7, 0x598A},
    {0x0000, 0x2061, 0x5843, 0x3C22, 0x59EE, 0x5A50, 0x5AD2, 0x5986, 0x5846,
     0x58A8, 0x590A, 0x598C, 0x5F49, 0x777A, 0x40A7, 0x598A},
    {0x0000, 0x1041, 0x4C23, 0x3041, 0x598C, 0x59EE, 0x5A50, 0x5AD2, 0x5986,
     0x5846, 0x58A8, 0x590A, 0x6E6B, 0x5F49, 0x40A7, 0x598A},
    {0x0000, 0x2061, 0x5843, 0x3C22, 0x590A, 0x598C, 0x59EE, 0x5A50, 0x5AD2,
     0x5986, 0x5846, 0x58A8, 0x5F49, 0x777A, 0x40A7, 0x598A},
    {0x0000, 0x1041, 0x6464, 0x4C23, 0x58A8, 0x590A, 0x598C, 0x59EE, 0x5A50,
     0x5AD2, 0x5986, 0x5846, 0x6E6B, 0x5F49, 0x40A7, 0x598A},
    {0x0000, 0x2061, 0x7085, 0x5C24, 0x5846, 0x58A8, 0x590A, 0x598C, 0x59EE,
     0x5A50, 0x5AD2, 0x5986, 0x5F49, 0x777A, 0x40A7, 0x598A},
    {0x0000, 0x0C41, 0x1BE3, 0x3D8A, 0x2CA1, 0x4503, 0x59A7, 0x5E2B, 0x62AF,
     0x1084, 0x1D08, 0x296C, 0x39F0, 0x4654, 0x52D8, 0x635C},
    {0x0000, 0x3C00, 0x4800, 0x5923, 0x6DC8, 0x7ED1, 0x7F73, 0x7FFF, 0x0400,
     0x3DAD, 0x4E10, 0x66D6, 0x735A, 0x8000, 0x7FB5, 0x0400}};
static u8 D_12000_8017AAA4[] = {
    0x01, 0x02, 0x02, 0x02, 0x03, 0x04, 0x04, 0x06, 0x05, 0x06,
    0x06, 0x08, 0x07, 0x08, 0x08, 0x08, 0x09, 0x08, 0x0A, 0x0A,
    0x0B, 0x0A, 0x0C, 0x0A, 0x0D, 0x0A, 0xFF, 0xFF};
static u8 D_12000_8017AAC0[] = {
    0x0E, 0x0A, 0x0F, 0x0C, 0x10, 0x0E, 0x11, 0x10, 0x12, 0x10,
    0x13, 0x12, 0x14, 0x12, 0x15, 0x14, 0x16, 0x12, 0x1E, 0x1C,
    0x1F, 0x1C, 0x20, 0x1C, 0x21, 0x1C, 0xFF, 0xFF};
static u8 D_12000_8017AADC[] = {
    0x0E, 0x0A, 0x0F, 0x0C, 0x17, 0x16, 0x18, 0x18, 0x19, 0x18,
    0x1A, 0x1A, 0x1B, 0x1A, 0x1C, 0x1A, 0x1D, 0x1A, 0x1E, 0x1C,
    0x1F, 0x1C, 0x20, 0x1C, 0x21, 0x1C, 0xFF, 0xFF};
static u8 D_12000_8017AAF8[] = {
    0x22, 0x02, 0x23, 0x02, 0x24, 0x04, 0x25, 0x06, 0x26, 0x06, 0x27,
    0x08, 0x28, 0x08, 0x29, 0x08, 0x2A, 0x08, 0x2B, 0x0A, 0xFF, 0xFF};
static u8 D_12000_8017AB10[] = {
    0x2C, 0x1E, 0x2D, 0x1E, 0x2E, 0x04, 0x2F, 0x06, 0x30, 0x06, 0x31,
    0x08, 0x32, 0x08, 0x33, 0x08, 0x34, 0x08, 0x3C, 0x0A, 0xFF, 0xFF};
static u8 D_12000_8017AB28[] = {
    0x2C, 0x1E, 0x2D, 0x1E, 0x35, 0x20, 0x36, 0x20, 0x37, 0x20, 0x38,
    0x22, 0x39, 0x22, 0x3A, 0x22, 0x3B, 0x22, 0x3C, 0x0A, 0xFF, 0xFF};
static u32 unk[] = {
    // not sure if this is part of D_12000_8017AB28 or is unused data
    0x243D0004, 0x243E0004, 0x243F0004, 0x24400004, 0x00000000};
static s8 hitboxes[][4] = {
    {0x00, 0x00, 0x00, 0x00}, {0xFD, 0xE6, 0x0C, 0x04},
    {0x1A, 0xE5, 0x10, 0x06}, {0x28, 0xEE, 0x08, 0x08},
    {0x11, 0xF7, 0x0C, 0x08}, {0xF1, 0xFC, 0x04, 0x04},
    {0xF6, 0xF8, 0x0C, 0x04}, {0x13, 0xF5, 0x10, 0x08},
    {0x20, 0xFF, 0x08, 0x08}, {0x0F, 0x08, 0x0C, 0x08},
    {0x16, 0x03, 0x12, 0x04}, {0x11, 0x02, 0x0C, 0x0C},
    {0x1D, 0x13, 0x08, 0x08}, {0x0B, 0x12, 0x0C, 0x08},
    {0xE9, 0x0E, 0x04, 0x04}, {0xF2, 0xE4, 0x0C, 0x04},
    {0x18, 0x04, 0x14, 0x0C}, {0x06, 0xFD, 0x10, 0x08},
    {0x01, 0x00, 0x08, 0x08}, {0x00, 0x00, 0x0F, 0x0F},
    {0x01, 0x02, 0x1C, 0x1C}};
static u8* anim0[] = {
    D_12000_8017AAA4, D_12000_8017AAA4, D_12000_8017AAC0, D_12000_8017AADC,
    D_12000_8017AAF8, D_12000_8017AB10, D_12000_8017AB28};
static WeaponAnimation D_12000_8017ABC4[] = {
    anim0, hitboxes, 0, SFX_WEAPON_SCRAPE_ECHO, 0x48, 0x03, 0};
static u16* g_WeaponCluts[] = {clut0};
static s32 g_HandId = HAND_ID;

#include "shared.h"

static void EntityWeaponAttack(Entity* self) {
    WeaponAnimation* anim;
    s8 animIndex;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;
    animIndex = (self->params >> 8) & 0x7f;
    anim = &D_12000_8017ABC4[animIndex];
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
        self->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED;
        self->zPriority = PLAYER.zPriority - 2;
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
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

s32 func_ptr_80170004(Entity* self) {}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 2; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
