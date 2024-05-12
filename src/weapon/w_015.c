// Weapon ID #15. Used by weapons:
// Shuriken, Cross shuriken, Buffalo star, Flame star, TNT
#include "weapon_private.h"
#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_015", EntityWeaponAttack);

void func_ptr_80170004(Entity* self) {
    if (self->step == 0) {
        self->animSet = self->ext.weapon.parent->animSet;
        self->animCurFrame = self->ext.weapon.parent->animCurFrame;
        self->facingLeft = self->ext.weapon.parent->facingLeft;
        self->zPriority = self->ext.weapon.parent->zPriority - 2;
        self->flags = FLAG_UNK_08000000;
        self->palette = self->ext.weapon.parent->palette;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->ext.generic.unk7C.s = 10;
        self->drawMode = DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_UNK8;
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

extern SpriteParts D_6D000_8017A2B0[];
extern AnimationFrame D_6D000_8017A770[];

void func_ptr_80170014(Entity* self) {
    s16 angle;

    if (self->step == 0) {
        if (self->ext.weapon.parent->entityId == 0) {
            DestroyEntity(self);
            return;
        }
        SetSpriteBank2(D_6D000_8017A2B0);
        self->animSet = ANIMSET_OVL(17);
        self->palette = 0x111;
        self->unk5A = 101;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 24;
            self->unk5A = 103;
        }
        self->unk4C = D_6D000_8017A770;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE | 0x20;
        angle = ratan2(-self->ext.weapon.parent->velocityY,
                       self->ext.weapon.parent->velocityX);
        angle += (0x500 + (rand() % 0x600));
        self->velocityX = rcos(angle) * 64;
        self->velocityY = rsin(angle) * -64;
        self->ext.weapon.accelerationX = -self->velocityX / 13;
        self->ext.weapon.accelerationY = -self->velocityY / 13;
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.weapon.parent->enemyId;
        self->hitboxHeight = self->hitboxWidth = 12;
        self->step++;
        return;
    }
    if (self->animFrameDuration < 0) {
        DestroyEntity(self);
        return;
    }
    self->posY.val += self->velocityY;
    self->posX.val += self->velocityX;
    self->velocityX += self->ext.weapon.accelerationX;
    self->velocityY += self->ext.weapon.accelerationY;
}

int GetWeaponId(void) { return 15; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
