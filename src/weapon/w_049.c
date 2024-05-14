// Weapon ID #49. Used by weapons:
// Firebrand, Marsil, Unknown#179, Unknown#180
#include "weapon_private.h"
#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_049", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_049", func_15B000_8017B88C);

INCLUDE_ASM("weapon/nonmatchings/w_049", func_ptr_80170004);

INCLUDE_ASM("weapon/nonmatchings/w_049", func_ptr_80170008);

INCLUDE_ASM("weapon/nonmatchings/w_049", func_ptr_8017000C);

INCLUDE_ASM("weapon/nonmatchings/w_049", func_ptr_80170010);

extern SpriteParts D_15B000_8017AA44[];
extern AnimationFrame D_15B000_8017B10C[];

s32 func_ptr_80170014(Entity* self) {
    switch (self->step) {
    case 0:
        SetSpriteBank2(D_15B000_8017AA44);
        self->animSet = ANIMSET_OVL(0x11);
        self->unk5A = 101;
        self->palette = 0x117;
        if (g_HandId != 0) {
            self->palette = 0x12F;
            self->unk5A += 2;
            self->animSet += 2;
        }
        self->unk4C = D_15B000_8017B10C;
        self->zPriority = PLAYER.zPriority + 2;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->rotX = self->rotY = 0x100;
        self->drawMode = DRAW_TPAGE | 0x20;
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.weapon.parent->enemyId;
        self->hitboxHeight = self->hitboxWidth = 12;
        self->hitboxOffY = self->hitboxOffX = 0;
        self->velocityY = FIX(-0.375);
        g_api.PlaySfx(0x65B);
        self->step++;
        return;
    case 1:
        self->posY.val += self->velocityY;
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
        }
    }
}

int GetWeaponId(void) { return 49; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
