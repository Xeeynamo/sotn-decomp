#include "weapon_private.h"
#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_013", func_5F000_8017A9CC);

INCLUDE_ASM("weapon/nonmatchings/w_013", EntityWeaponAttack);

void func_ptr_80170004(Entity* self) {
    s16 temp_rotangle;
    s16 temp_zpriority;

    if (self->step == 0) {
        if (self->ext.weapon.parent->entityId == 0) {
            DestroyEntity(self);
            return;
        }
        self->animCurFrame = self->ext.weapon.parent->animCurFrame;
        self->animSet = self->ext.weapon.parent->animSet;
        self->facingLeft = self->ext.weapon.parent->facingLeft;
        self->unk5A = self->ext.weapon.parent->unk5A;
        temp_zpriority = PLAYER.zPriority;
        self->flags = 0x0C020000;
        self->zPriority = temp_zpriority - 4;
        self->palette = self->ext.weapon.parent->ext.generic.unk88.S16.unk0;
        self->unk19 = self->ext.weapon.parent->unk19 + 8;
        temp_rotangle = self->ext.weapon.parent->rotAngle;
        self->unk6C = 0x80;
        self->step++;
        self->rotAngle = temp_rotangle;
    }
    if (self->unk6C >= 48) {
        self->unk6C -= 8;
        return;
    }
    DestroyEntity(self);
}

INCLUDE_ASM("weapon/nonmatchings/w_013", func_ptr_80170008);

INCLUDE_ASM("weapon/nonmatchings/w_013", func_ptr_8017000C);

void func_ptr_80170010(Entity* self) {}

void func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 13; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
