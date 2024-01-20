// Weapon ID #16. Used by weapons:
// Bwaka knife, Boomerang, Javelin, Fire boomerang, Iron ball
#include "weapon_private.h"
#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_016", EntityWeaponAttack);

void func_ptr_80170004(Entity* self) {

    if (self->step == 0) {
        self->animSet = self->ext.weapon.parent->animSet;
        self->animCurFrame = self->ext.weapon.parent->animCurFrame;
        self->facingLeft = self->ext.weapon.parent->facingLeft;
        self->zPriority = PLAYER.zPriority - 4;
        self->flags = FLAG_UNK_08000000;
        self->palette = self->ext.weapon.parent->palette;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->ext.weapon.lifetime = 0x16;
        self->drawFlags = FLAG_DRAW_ROTZ | FLAG_DRAW_UNK8;
        self->drawMode = DRAW_TPAGE;
        self->rotZ = self->ext.weapon.parent->rotZ;
        self->unk6C = 0x80;
        self->step++;
    }
    if (--self->ext.weapon.lifetime == 0) {
        DestroyEntity(self);
        return;
    }
    if (self->unk6C >= 48) {
        self->unk6C -= 8;
    }
}

INCLUDE_ASM("weapon/nonmatchings/w_016", func_ptr_80170008);

INCLUDE_ASM("weapon/nonmatchings/w_016", func_ptr_8017000C);

INCLUDE_ASM("weapon/nonmatchings/w_016", func_ptr_80170010);

INCLUDE_ASM("weapon/nonmatchings/w_016", func_ptr_80170014);

int GetWeaponId(void) { return 16; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
