// Weapon ID #1. Used by weapons:
// Knuckle duster, Jewel knuckles, Iron Fist, Fist of Tulkas, Unknown#186,
// Unknown#187, Unknown#188
#include "weapon_private.h"
#include "shared.h"
#include "w_001_1.h"
#include "w_001_2.h"
#define g_Animset w_001_1
#define g_Animset2 w_001_2

INCLUDE_ASM("weapon/nonmatchings/w_001", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_001", func_ptr_80170004);

extern AnimationFrame D_B000_8017AFC8[];

void func_ptr_80170008(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
        self->animSet = 9;
        self->unk4C = D_B000_8017AFC8;
        self->zPriority = PLAYER.zPriority - 2;
        self->facingLeft = (PLAYER.facingLeft + 1) & 1;
        SetSpeedX(FIX(-4.5));
        self->palette = PAL_OVL(0x1B0);
        self->drawMode = 0x30;
        self->posX.val += self->velocityX * 6;
        self->posY.i.hi -= 0xD;
        if (PLAYER.drawFlags & FLAG_DRAW_ROTY) {
            self->posY.i.hi -= 0x3;
        }
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->rotY = 0x60;
        self->rotX = 0x60;
        self->ext.factory.unkAE = self->ext.factory.parent->ext.factory.unkAE;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.factory.parent->enemyId;
        self->hitboxWidth = 10;
        self->hitboxHeight = 8;
        g_api.PlaySfx(0x62C);
        self->step++;
        break;

    case 1:
        if (self->hitFlags) {
            DestroyEntity(self);
            return;
        }
        self->posX.val += self->velocityX;
        self->rotX += 0x10;
        self->rotY += 0x10;
        if (self->rotY >= 0x101) {
            self->rotY = 0x100;
        }
        if (self->rotX >= 0x181) {
            self->rotX = 0x180;
        }
        break;
    }
}

void func_ptr_8017000C(Entity* self) {}

s32 func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 1; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
