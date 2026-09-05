// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #40. Used by weapons:
// Monster vial 1
#include "weapon_private.h"
#include "gen/w_040_1.h"
#include "gen/w_040_2.h"
#define g_Animset w_040_1
#define g_Animset2 w_040_2
#include "sfx.h"

static u16 pal_0[N_ARRAY_PAL][COLORS_PER_PAL] = {
    {0x0000, 0x6B5D, 0x1ABD, 0x05BA, 0x0091, 0x0008, 0x0004, 0x0400, 0x1084,
     0x2120, 0x1FFF, 0x01A1, 0x0E64, 0x306B, 0x2D6B, 0x77BD},
    {0x0000, 0x7C00, 0x7C00, 0x0017, 0x0013, 0x0010, 0x000C, 0x7C00, 0x7C00,
     0x00BF, 0x015F, 0x01FF, 0x131F, 0x2FFF, 0x4FFF, 0x7FFF},
    {0x0000, 0xA4C6, 0xA8E7, 0xAD29, 0xB16B, 0xB5AD, 0xB9CE, 0xBDEF, 0xC210,
     0xC631, 0xCA52, 0xCE73, 0xD294, 0xD6B5, 0xDAD6, 0xE2F6},
    {0x0000, 0x1C65, 0x2065, 0x2886, 0x30A7, 0x34C8, 0x3CE9, 0x450A, 0x4D2B,
     0x558C, 0x5E0E, 0x6670, 0x6EF1, 0x7753, 0x7FD5, 0x7FFF},
    {0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
     0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
    {0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
     0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
    {0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
     0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
    {0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
     0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
    {0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
     0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
    {0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
     0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
    {0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
     0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
    {0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
     0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
    {0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
     0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
    {0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
     0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
    {0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
     0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
    {0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
     0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
    {0x0000, 0x8000, 0x8000, 0x8000, 0x0001, 0x8000, 0x8000, 0x8000, 0x8000,
     0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x0400}};
static AnimationFrame anim_0[] = {
    POSE(2, 0x06, 1), POSE(2, 0x07, 1), POSE(2, 0x08, 1),
    POSE(2, 0x09, 1), POSE(2, 0x0A, 1), POSE(2, 0x0B, 1),
    POSE(2, 0x0C, 1), POSE(2, 0x0D, 1), POSE_LOOP(0)};
static AnimationFrame anim_1[] = {
    POSE(17, 0x01, 1), POSE(4, 0x02, 1),  POSE(1, 0x11, 1), POSE(1, 0x0F, 2),
    POSE(10, 0x0E, 2), POSE(4, 0x0F, 2),  POSE(3, 0x10, 2), POSE(3, 0x11, 1),
    POSE(3, 0x02, 1),  POSE(2, 0x03, 1),  POSE(8, 0x04, 1), POSE(15, 0x05, 1),
    POSE(3, 0x02, 1),  POSE(2, 0x03, 1),  POSE(8, 0x04, 1), POSE(15, 0x05, 1),
    POSE(3, 0x02, 1),  POSE(2, 0x03, 1),  POSE(8, 0x04, 1), POSE(15, 0x05, 1),
    POSE(8, 0x02, 1),  POSE(16, 0x01, 1), POSE(3, 0x02, 1), POSE(2, 0x11, 1),
    POSE(2, 0x0F, 2),  POSE(2, 0x0E, 2),  POSE(8, 0x0F, 2), POSE_END};
static AnimationFrame anim_2[] = {
    POSE(1, 0x12, 3), POSE(1, 0x13, 3), POSE(1, 0x14, 3),
    POSE(1, 0x15, 3), POSE(1, 0x16, 3), POSE(1, 0x17, 3),
    POSE(1, 0x18, 3), POSE(1, 0x19, 3), POSE_LOOP(0)};
static AnimationFrame anim_3[] = {
    POSE(2, 0x1B, 5), POSE(1, 0x21, 5), POSE(2, 0x1C, 5), POSE(1, 0x1D, 5),
    POSE(1, 0x1E, 5), POSE(1, 0x1F, 5), POSE(1, 0x20, 5), POSE(1, 0x1C, 5),
    POSE(1, 0x21, 5), POSE_END};
static AnimationFrame anim_4[] = {POSE(128, 0x1A, 0), POSE_END};
static AnimationFrame anim_5[] = {
    POSE(10, 0x0E, 2), POSE(1, 0x0F, 2), POSE(1, 0x11, 1), POSE(4, 0x02, 1),
    POSE(4, 0x01, 1),  POSE(2, 0x0D, 1), POSE(2, 0x0C, 1), POSE(2, 0x0B, 1),
    POSE(2, 0x0A, 1),  POSE(2, 0x09, 1), POSE(2, 0x08, 1), POSE(2, 0x07, 1),
    POSE(2, 0x06, 1),  POSE_LOOP(5)};
static FrameProperty hitboxes[] = {
    {0, 0, 0, 0},  {0, 1, 5, 17}, {-2, 7, 10, 11},
    {4, 1, 10, 4}, {0, 0, 3, 3},  {-63, -63, 0, 0}};
static s32 speed_mod[] = {FIX(0.875), FIX(1), FIX(0.75), FIX(1.125)};
static u16* g_WeaponCluts[] = {pal_0};
static s32 g_HandId = HAND_ID;
static s32 D_11C000_8017B540;

#include "shared.h"

void func_11C000_8017AC14(void) {
    RECT rect;
    u16* dst;
    s16 color;

    color = (g_GameTimer >> 1) % 2 ? 0x039C : 0x199D;
    dst = (u16*)g_Clut + (g_HandId * N_WEAPON_PAL + 0x110) * COLORS_PER_PAL;
    dst[10] = color;

    rect.x = 0;
    rect.y = 0xF1;
    rect.w = 0x100;
    rect.h = 3;
    dst = (u16*)g_Clut + 0x1100;
    LoadImage(&rect, (u_long*)dst);
}

static void EntityWeaponAttack(Entity* self) {
    Collider col;
    s32 var_a2;
    s16 xMod;

    switch (self->step) {
    case 0:
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(16);
        self->palette = PAL_UNK_110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->palette += 0x18;
            self->unk5A += 2;
            self->animSet += 2;
        }

        self->zPriority = PLAYER.zPriority + 2;
        self->facingLeft = PLAYER.facingLeft;
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_100000;
        self->anim = anim_4;
        self->posY.i.hi -= 4;

        D_11C000_8017B540 %= 4;
        SetSpeedX(speed_mod[D_11C000_8017B540]);
        self->velocityY = -FIX(2.5);
        g_Player.timers[10] = 4;
        D_11C000_8017B540++;
        self->step++;
        break;
    case 1:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY += FIX(0.15625);
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi, &col, 0);
        if (col.effects & EFFECT_SOLID) {
            self->posY.i.hi += col.unk18;
            self->anim = anim_3;
            self->poseTimer = 0;
            self->pose = 0;
            self->blendMode = BLEND_TRANSP | BLEND_ADD;
            g_api.PlaySfxVolPan(SFX_GLASS_BREAK_A, 0x50, 0);
            // TODO: FACTORY()
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(56, 0), 0);
            self->step++;
            return;
        }

        if (self->velocityX < 0) {
            xMod = -4;
        } else {
            xMod = 4;
        }
        g_api.CheckCollision(
            (s16)(xMod + self->posX.i.hi), self->posY.i.hi, &col, 0);
        if (col.effects & EFFECT_UNK_0002) {
            if (xMod < 0) {
                self->posX.i.hi += col.unkC;
            } else {
                self->posX.i.hi += col.unk4;
            }
            self->velocityX /= -2;
        }

        g_api.CheckCollision(
            self->posX.i.hi, (s16)(self->posY.i.hi - 8), &col, 0);
        if (col.effects & EFFECT_SOLID) {
            self->posY.i.hi += col.unk20 + 1;
            self->velocityY = FIX(1);
            self->velocityX /= 2;
            return;
        }
        break;
    case 2:
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

s32 func_ptr_80170004(Entity* self) {
    switch (self->step) {
    case 0:
        self->animSet = self->ext.weapon.parent->animSet;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->palette = self->ext.weapon.parent->palette;
        self->facingLeft = (self->facingLeft + 1) & 1;
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->zPriority = self->ext.weapon.parent->zPriority - 2;
        self->anim = anim_0;
        self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleY = 0;
        self->scaleX = 0;
        self->rotPivotY = 0x16;
        self->posY.i.hi -= 0x16;
        self->step++;
        break;
    case 1:
        self->scaleX += 4;
        if (self->scaleX >= 0x100) {
            self->scaleX = 0x100;
            self->anim = anim_1;
            self->pose = 0;
            self->poseTimer = 0;
            self->ext.weapon.equipId =
                self->ext.weapon.parent->ext.weapon.equipId;
            SetWeaponProperties(self, 0);
            self->step++;
        }
        self->scaleY = self->scaleX;
        break;
    case 2:
        if (self->poseTimer == 1) {
            if ((self->pose == 0xB || self->pose == 0xF ||
                 self->pose == 0x13) &&
                // TODO: FACTORY()
                g_api.CreateEntFactoryFromEntity(self, WFACTORY(62, 0), 0) !=
                    NULL) {
                g_api.PlaySfx(SFX_EXPLODE_B);
            }
        }
        if (self->poseTimer < 0) {
            self->anim = anim_5;
            self->pose = 0;
            self->poseTimer = 0;
            g_api.PlaySfx(SFX_VO_ALU_PAIN_A);
            self->step++;
        }
        break;
    case 3:
        if (self->scaleX == 0x40) {
            // TODO: FACTORY()
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(70, 0), 0);
        }
        if (self->pose >= 5) {
            self->scaleX -= 4;
        }
        if (self->scaleX < 0) {
            DestroyEntity(self);
            return;
        }
        self->scaleY = self->scaleX;
        break;
    }
    g_api.UpdateAnim(hitboxes, NULL);
    func_11C000_8017AC14();
}

static void func_ptr_80170008(Entity* self) {
    s32 var_a1;

    if (self->step == 0) {
        if (self->ext.weapon.parent->entityId == 0) {
            DestroyEntity(self);
            return;
        }
        self->animSet = self->ext.weapon.parent->animSet;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->palette = self->ext.weapon.parent->palette;
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->zPriority = self->ext.weapon.parent->zPriority - 2;
        self->anim = anim_0;
        self->posY.i.hi -= 0xA;
        var_a1 = 0x18;
        if (self->facingLeft == 0) {
            var_a1 = -0x18;
        }
        self->posX.i.hi = var_a1 + self->posX.i.hi;
        SetSpeedX(-FIX(2.5));
        self->anim = anim_2;
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        self->attackElement |= ELEMENT_FIRE;
        SetWeaponProperties(self, 0);
        self->step++;
    } else {
        self->posX.val += self->velocityX;
        if (self->hitFlags != 0) {
            DestroyEntity(self);
            return;
        }
    }

    g_api.UpdateAnim(hitboxes, NULL);
}

static void func_ptr_8017000C(Entity* self) {
    if (self->step == 0) {
        self->animSet = self->ext.weapon.parent->animSet;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->palette = self->ext.weapon.parent->palette;
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_100000;
        self->zPriority = self->ext.weapon.parent->zPriority + 2;
        self->anim = anim_3;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->posY.i.hi += 0x10;
        self->step++;
    } else if (self->poseTimer < 0) {
        DestroyEntity(self);
    }
}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 40; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
