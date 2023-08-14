#include "weapon_private.h"

INCLUDE_ASM("weapon/nonmatchings/w_015", DestroyEntity);

INCLUDE_ASM("weapon/nonmatchings/w_015", LoadWeaponPalette);

INCLUDE_ASM("weapon/nonmatchings/w_015", SetSpriteBank1);

INCLUDE_ASM("weapon/nonmatchings/w_015", SetSpriteBank2);

INCLUDE_ASM("weapon/nonmatchings/w_015", ResetAnimation);

INCLUDE_ASM("weapon/nonmatchings/w_015", DecelerateX);

INCLUDE_ASM("weapon/nonmatchings/w_015", DecelerateY);

INCLUDE_ASM("weapon/nonmatchings/w_015", SetSpeedX);

INCLUDE_ASM("weapon/nonmatchings/w_015", DestroyEntityWeapon);

INCLUDE_ASM("weapon/nonmatchings/w_015", SetWeaponProperties);

INCLUDE_ASM("weapon/nonmatchings/w_015", EntityWeaponAttack);

void func_ptr_80170004(Entity* self) {
    if (self->step == 0) {
        self->animSet = self->ext.generic.unk8C.entityPtr->animSet;
        self->animCurFrame = self->ext.generic.unk8C.entityPtr->animCurFrame;
        self->facing = self->ext.generic.unk8C.entityPtr->facing;
        self->zPriority = self->ext.generic.unk8C.entityPtr->zPriority - 2;
        self->flags = FLAG_UNK_08000000;
        self->palette = self->ext.generic.unk8C.entityPtr->palette;
        self->unk5A = self->ext.generic.unk8C.entityPtr->unk5A;
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

INCLUDE_ASM("weapon/nonmatchings/w_015", func_ptr_80170018);

void func_ptr_80170020(void) {}

void func_ptr_80170024(void) {}

void func_ptr_80170028(void) {}

void func_ptr_8017002C(void) {}

void func_ptr_80170030(void) {}

void func_ptr_80170034(void) {}

void func_ptr_80170038(void) {}

void func_ptr_8017003C(void) {}
