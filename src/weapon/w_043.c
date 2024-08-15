// Weapon ID #43. Used by weapons:
// Alucard sword, Sword Familiar, Alucart sword, Unknown#197
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_043_1.h"
#include "w_043_2.h"
#define g_Animset w_043_1
#define g_Animset2 w_043_2

extern AnimationFrame D_131000_8017AF40[];

INCLUDE_ASM("weapon/nonmatchings/w_043", EntityWeaponAttack);

s32 func_ptr_80170004(Entity* self) {
    switch (self->step) {
    case 0:
        self->palette = PAL_OVL(0x100);
        self->zPriority = PLAYER.zPriority;
        self->facingLeft = PLAYER.facingLeft;
        // this toggles the high bit, but xor does not
        // produce the same set of instructions
        self->animCurFrame = PLAYER.animCurFrame + ANIMSET_OVL_FLAG;
        self->animSet = ANIMSET_DRA(1);
        self->drawMode = DRAW_TPAGE;
        self->flags = FLAG_UNK_04000000 | FLAG_UNK_20000;
        self->unk5A = 0;
        SetSpeedX(FIX(13.0));
        self->velocityY = FIX(-1.0 / 8.0);
        self->step++;
        break;

    case 1:
        self->animCurFrame = PLAYER.animCurFrame + ANIMSET_OVL_FLAG;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        DecelerateX(FIX(15.0 / 32.0));
        if (PLAYER.animFrameIdx == 5 && PLAYER.animFrameDuration == 1) {
            self->facingLeft++;
            self->facingLeft &= 1;
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + FACTORY(0, 62), 0);
            self->step++;
        }
        break;

    case 2:
        self->drawMode = DRAW_DEFAULT;
        self->animCurFrame = PLAYER.animCurFrame + ANIMSET_OVL_FLAG;
        if (PLAYER.animFrameIdx == 0xE) {
            self->facingLeft++;
            self->facingLeft &= 1;
            SetSpeedX(FIX(-13.0));
            self->velocityY = FIX(1.0 / 8.0);
            self->step++;
        }
        break;

    case 3:
        self->drawMode = DRAW_TPAGE;
        self->animCurFrame = PLAYER.animCurFrame + ANIMSET_OVL_FLAG;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        DecelerateX(FIX(15.0 / 32.0));
        if (PLAYER.animFrameIdx == 19) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

static void func_ptr_80170008(Entity* self) {
    if (self->step == 0) {
        self->unk4C = D_131000_8017AF40;
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_UNK_100000 | FLAG_UNK_40000 |
                      FLAG_UNK_20000;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.weapon.parent->enemyId;
        self->hitboxOffX = 0x1B;
        self->hitboxOffY = -0x13;
        self->hitboxWidth = 0x23;
        self->step++;
    } else {
        if ((self->animFrameIdx == 1) || (self->animFrameIdx == 0xB)) {
            g_api.PlaySfx(SE_WPN_ALUCARD_SWORD_SWING);
        }
        if ((u16)self->animCurFrame - 0x24U < 6) {
            self->hitboxHeight = 8;
        } else {
            self->hitboxHeight = 0;
        }
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
            return;
        }
    }
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 43; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
