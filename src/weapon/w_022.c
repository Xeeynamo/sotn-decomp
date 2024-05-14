// Weapon ID #22. Used by weapons:
// Magic Missile
#include "weapon_private.h"
#include "shared.h"

extern AnimationFrame D_9E000_8017A760[];
extern AnimationFrame D_9E000_8017A800[];

INCLUDE_ASM("weapon/nonmatchings/w_022", EntityWeaponAttack);

void func_ptr_80170004(Entity* self) {
    switch (self->step) {
    case 0:
        if (self->ext.weapon.parent->entityId == 0) {
            DestroyEntity(self);
            break;
        }
        self->facingLeft = self->ext.weapon.parent->facingLeft;
        self->animSet = self->ext.weapon.parent->animSet;
        self->unk4C = D_9E000_8017A800;
        self->zPriority = PLAYER.zPriority + 2;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->palette = self->ext.weapon.parent->palette;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
        SetSpeedX(FIX(5));
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->hitboxOffX = 8;
        self->hitboxWidth = 8;
        self->hitboxHeight = 4;
        self->step++;
        break;
    case 1:
        if (self->hitFlags == 1) {
            self->animFrameDuration = 0;
            self->animFrameIdx = 0;
            self->unk4C = D_9E000_8017A760;
            self->step++;
        } else {
            self->posX.val += self->velocityX;
        }
        break;
    case 2:
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 22; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
