// Weapon ID #12. Used by weapons:
// Chakram, Vorpal blade, Crissaegrim
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_012_1.h"
#include "w_012_2.h"
#define g_Animset w_012_1
#define g_Animset2 w_012_2

INCLUDE_ASM("weapon/nonmatchings/w_012", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_012", func_ptr_80170004);

static void func_ptr_80170008(Entity* self) {
    if (self->step == 0) {
        if (self->ext.weapon.parent->entityId == 0) {
            DestroyEntity(self);
            return;
        }
        self->animCurFrame = self->ext.weapon.parent->animCurFrame;
        self->animSet = self->ext.weapon.parent->animSet;
        self->facingLeft = self->ext.weapon.parent->facingLeft;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->zPriority = PLAYER.zPriority - 4;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 | FLAG_UNK_20000;
        self->palette = self->ext.weapon.parent->palette;
        self->drawFlags = self->ext.weapon.parent->drawFlags + FLAG_DRAW_UNK8;
        self->rotZ = self->ext.weapon.parent->rotZ;
        self->unk6C = 0x80;
        self->step++;
    }
    if (self->unk6C >= 48) {
        self->unk6C -= 8;
        return;
    }
    DestroyEntity(self);
}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 12; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
