// Weapon ID #1. Used by weapons:
// Knuckle duster, Jewel knuckles, Iron Fist, Fist of Tulkas, Unknown#186,
// Unknown#187, Unknown#188
#include "weapon_private.h"
#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_001", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_001", func_ptr_80170004);

extern AnimationFrame D_B000_8017AFC8;

void func_ptr_80170008(Entity* self) {
    u16 new_var;
    switch (self->step) {
    case 0:
        self->flags = 0x08100000;
        self->animSet = 9;
        self->unk4C = &D_B000_8017AFC8;
        self->zPriority = PLAYER.zPriority - 2;
        self->facingLeft = (PLAYER.facingLeft + 1) & 1;
        SetSpeedX(-0x48000);
        self->palette = 0x81B0;
        self->drawMode = 0x30;
        self->posX.val += self->velocityX * 6;
        self->posY.i.hi -= 0xD;
        do {
            if (PLAYER.drawFlags & 2) {
                self->posY.i.hi -= 0x3;
            }
            self->drawFlags = 3;
            self->rotY = 0x60;
            self->rotX = 0x60;
            self->ext.factory.unkAE =
                self->ext.factory.parent->ext.factory.unkAE;
            SetWeaponProperties(self, 0);
            new_var = self->ext.factory.parent->enemyId;
            self->hitboxWidth = 0xA;
            self->hitboxHeight = 8;
            self->enemyId = new_var;
        } while (0);
        g_api_PlaySfx(0x62C);
        self->step += 1;
        return;

    case 1:
        if (self->hitFlags != 0) {
            DestroyEntity(self);
            return;
        }
        self->posX.val += self->velocityX;
        self->rotX += 0x10;
        if ((self->rotY += 0x10) >= 0x101) {
            self->rotY = 0x100;
        }
        if (self->rotX >= 0x181) {
            self->rotX = 0x180;
        }
        return;
    }
}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

void func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 1; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
