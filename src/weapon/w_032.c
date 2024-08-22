// SPDX-License-Identifier: AGPL-3.0-only
// Weapon ID #32. Used by weapons:
// Combat knife, Unknown#175
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_032_1.h"
#include "w_032_2.h"
#define g_Animset w_032_1
#define g_Animset2 w_032_2

extern WeaponAnimation D_E4000_8017A8F8[];

void EntityWeaponAttack(Entity* self) {
    WeaponAnimation* anim;
    s16 animIndex;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;
    animIndex = (self->params >> 8) & 0x7F;
    anim = &D_E4000_8017A8F8[animIndex];

    if ((PLAYER.ext.player.anim < anim->frameStart ||
         PLAYER.ext.player.anim >= (anim->frameStart + 7) ||
         g_Player.unk46 == 0) &&
        self->step != 2) {
        self->step = 2;
        self->ext.timer.t = 4;
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
    if (self->step == 0) {
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = PAL_DRA(0x110);
        self->unk5A = 0x64;
        if (g_HandId) {
            self->palette += 0x18;
            self->animSet += 2;
            self->unk5A = 0x66;
        }
        self->palette += anim->palette;
        self->flags = FLAG_UNK_40000 | FLAG_UNK_20000;
        if (self->params & 0x7F00) {
            self->zPriority = PLAYER.zPriority - 2;
        } else {
            self->zPriority = PLAYER.zPriority + 2;
        }
        SetWeaponProperties(self, 0);
        self->step++;
    }
    if (self->step == 2) {
        self->ext.weapon.lifetime--;
        if (!self->ext.weapon.lifetime) {
            DestroyEntity(self);
        }
    } else {
        self->ext.weapon.anim = PLAYER.ext.player.anim - anim->frameStart;
        if ((PLAYER.animFrameDuration == 1) &&
            (PLAYER.animFrameIdx == anim->soundFrame)) {
            g_api.PlaySfx(anim->soundId);
            if (anim->soundId == SFX_WEAPON_SWISH_B) {
                g_api.PlaySfx(SFX_UNK_6EF);
            }
        }
        if (g_api.UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
            self->step = 2;
            self->ext.weapon.lifetime = 4;
            self->animCurFrame = 0;
            self->hitboxState = 0;
        }
        if (self->ext.weapon.anim < 4 && PLAYER.animFrameIdx == 6) {
            self->hitboxState = 4;
        }
        self->drawFlags = PLAYER.drawFlags;
        self->rotY = PLAYER.rotY;
        self->rotPivotY = PLAYER.rotPivotY;
    }
}

s32 func_ptr_80170004(Entity* self) {}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 32; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
