// Weapon ID #29. Used by weapons:
// Fire shield, Unknown#213
#include "weapon_private.h"
#include "shared.h"

extern u16 D_CF000_8017AD04[];

INCLUDE_ASM("weapon/nonmatchings/w_029", EntityWeaponAttack);

void func_ptr_80170004(Entity* self) {
    if (self->ext.weapon.parent->ext.weapon.equipId != 15) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        self->animSet = self->ext.weapon.parent->animSet;
        self->zPriority = self->ext.weapon.parent->zPriority + 4;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->ext.weapon.unk80 = self->ext.weapon.parent->ext.weapon.unk80;
        self->animCurFrame = self->ext.weapon.parent->animCurFrame;
        self->flags = 0x08000000;
        self->unk19 = 0x18;
        self->unk6C = 0x80;
        self->ext.weapon.unk7E = 0x14;
        self->step++;
    } else {
        if (self->unk6C >= 7) {
            self->unk6C -= 7;
        }

        if (--self->ext.weapon.unk7E == 0) {
            DestroyEntity(self);
            return;
        }
    }
    self->palette =
        self->ext.weapon.unk80 + D_CF000_8017AD04[g_GameTimer / 2 % 5];
}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

void func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 29; }

INCLUDE_ASM("weapon/nonmatchings/w_029", EntityWeaponShieldSpell);

INCLUDE_ASM("weapon/nonmatchings/w_029", func_ptr_80170024);

void func_ptr_80170028(Entity* self) {
    if (self->ext.weapon.parent->entityId == 0) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->hitboxHeight = 14;
        self->hitboxWidth = 14;
        self->ext.weapon.unk80 = 10;
        self->step++;
        return;
    }
    if (--self->ext.weapon.unk80 == 0) {
        DestroyEntity(self);
    }
}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
