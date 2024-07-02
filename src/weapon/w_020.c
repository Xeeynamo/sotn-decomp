// Weapon ID #20. Used by weapons:
// Karma Coin
#include "weapon_private.h"
#include "shared.h"

extern AnimationFrame D_90000_8017A954[];
extern AnimationFrame D_90000_8017A9D8[];
extern u16 D_90000_8017AA10[];
extern s32 D_90000_8017C238;

INCLUDE_ASM("weapon/nonmatchings/w_020", EntityWeaponAttack);

s32 func_ptr_80170004(Entity* self) {}

void func_ptr_80170008(Entity* self) {
    if (self->ext.weapon.parent->entityId == 0) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        self->animSet = self->ext.weapon.parent->animSet;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
        self->zPriority = PLAYER.zPriority;

        if (D_90000_8017C238 % 4 == 1) {
            self->velocityX = FIX(8.0 / 128);
            self->velocityY = FIX(34.0 / 128);
            self->unk4C = D_90000_8017A9D8;
            self->posX.i.hi = 140;
            self->posY.i.hi = 100;
            self->zPriority = PLAYER.zPriority - 4;
        } else {
            self->zPriority = PLAYER.zPriority;
            self->unk4C = D_90000_8017A954;
            self->animFrameIdx = rand() & 0x1F;
            self->posX.i.hi = (D_90000_8017C238 % 3) * 10 + 148;
            self->posY.i.hi = (D_90000_8017C238 % 3) * 10 + 76;
            self->velocityX = FIX(19.0 / 256); // strange, FIX is usually /128
            self->velocityY = (rand() & 0x1FFF) + FIX(0.25);
        }
        D_90000_8017C238++;
        self->step++;
    }
    self->palette = D_90000_8017AA10[g_GameTimer % 3];
    if (g_HandId != 0) {
        self->palette += 0x18;
    }
    self->posX.val += self->velocityX;
    self->posY.val += self->velocityY;
}

void func_ptr_8017000C(Entity* self) {}

s32 func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 20; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
