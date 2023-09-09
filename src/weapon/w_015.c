#include "weapon_private.h"
#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_015", EntityWeaponAttack);

void func_ptr_80170004(Entity* self) {
    if (self->step == 0) {
        self->animSet = self->ext.weapon.parent->animSet;
        self->animCurFrame = self->ext.weapon.parent->animCurFrame;
        self->facingLeft = self->ext.weapon.parent->facingLeft;
        self->zPriority = self->ext.weapon.parent->zPriority - 2;
        self->flags = FLAG_UNK_08000000;
        self->palette = self->ext.weapon.parent->palette;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->ext.generic.unk7C.s = 10;
        self->blendMode = 0x10;
        self->unk19 = 8;
        self->unk6C = 0x80;
        self->step++;
    }
    if (self->unk6C >= 0x30) {
        self->unk6C += 0xF8;
    }

    if (--self->ext.generic.unk7C.s == 0) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("weapon/nonmatchings/w_015", func_ptr_80170008);

INCLUDE_ASM("weapon/nonmatchings/w_015", func_ptr_8017000C);

INCLUDE_ASM("weapon/nonmatchings/w_015", func_ptr_80170010);

INCLUDE_ASM("weapon/nonmatchings/w_015", func_ptr_80170014);

int GetWeaponId(void) { return 15; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
