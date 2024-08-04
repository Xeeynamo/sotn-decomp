// Weapon ID #38. Used by weapons:
// Rapier, Unknown#191
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_038_1.h"
#include "w_038_2.h"
#define g_Animset w_038_1
#define g_Animset2 w_038_2

extern WeaponAnimation D_10E000_8017ADC0[2];

static void EntityWeaponAttack(Entity* self) {
    WeaponAnimation* anim;
    s8 animIndex;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;
    animIndex = (self->params & 0x7fff) >> 0x8;
    anim = &D_10E000_8017ADC0[animIndex];

    if (PLAYER.ext.weapon.anim < anim->frameStart ||
        PLAYER.ext.weapon.anim >= (anim->frameStart + 7) || !g_Player.unk46) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
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
        SetWeaponProperties(self, 0);

        self->step++;
    }

    self->ext.weapon.anim = PLAYER.ext.weapon.anim - anim->frameStart;

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

    if (animIndex != 0 && PLAYER.animFrameIdx == 4 &&
        PLAYER.animFrameDuration == 1) {
        g_api.CreateEntFactoryFromEntity(
            self, ((g_HandId + 1) << 0xC) | 0x38, 0);
    }
}

INCLUDE_ASM("weapon/nonmatchings/w_038", func_ptr_80170004);

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 38; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
