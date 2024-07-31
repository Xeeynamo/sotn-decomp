// Weapon ID #12. Used by weapons:
// Chakram, Vorpal blade, Crissaegrim
#include "weapon_private.h"
#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_012", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_012", func_ptr_80170004);

void func_ptr_80170008(Entity* self) {
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

void func_ptr_8017000C(Entity* self) {}

s32 func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 12; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
