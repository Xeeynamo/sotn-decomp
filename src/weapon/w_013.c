// Weapon ID #13. Used by weapons:
// Heaven sword, Unknown#202
#include "weapon_private.h"
#include "shared.h"

extern u8 D_5F000_8017A5B0[6][8];

s32 func_5F000_8017A9CC(Primitive* prim, s32 x, s32 y) {
    s32 size;
    s32 left;
    s32 right;
    s32 top;
    s32 bottom;
    u8* uvPtr;

    // Should be able to do this as an array access but nope
    uvPtr = &D_5F000_8017A5B0;
    uvPtr += prim->b0 * 8;

    if (prim->b0 >= 3) {
        size = 4;
    } else {
        size = 6;
    }
    if (prim->b0 == 6) {
        return -1;
    }
    left = x - size;
    top = y - size;
    right = x + size;
    bottom = y + size;

    prim->x0 = left;
    prim->y0 = top;
    prim->x1 = right;
    prim->y1 = top;
    prim->x2 = left;
    prim->y2 = bottom;
    prim->x3 = right;
    prim->y3 = bottom;

    prim->u0 = *uvPtr++;
    prim->v0 = *uvPtr++;
    prim->u1 = *uvPtr++;
    prim->v1 = *uvPtr++;
    prim->u2 = *uvPtr++;
    prim->v2 = *uvPtr++;
    prim->u3 = *uvPtr++;
    prim->v3 = *uvPtr++;
    if (!(++prim->b1 & 1)) {
        prim->b0++;
    }
    return 0;
}

INCLUDE_ASM("weapon/nonmatchings/w_013", EntityWeaponAttack);

s32 func_ptr_80170004(Entity* self) {
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
        self->palette = self->ext.weapon.parent->ext.weapon.childPalette;
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

INCLUDE_ASM("weapon/nonmatchings/w_013", func_ptr_80170008);

// Pay attention to unk80, unk8A, and childPalette. These all seem to be
// special for Heaven Sword and we should probably have it as a special weapon.
void func_ptr_8017000C(Entity* self) {
    s16 angle;

    if (self->ext.weapon.parent->entityId == 0) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        self->animCurFrame = self->ext.weapon.parent->animCurFrame;
        self->animSet = self->ext.weapon.parent->animSet;
        self->facingLeft = self->ext.weapon.parent->facingLeft;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->zPriority = self->ext.weapon.parent->zPriority;
        self->flags = FLAG_UNK_04000000;
        self->palette = self->ext.weapon.parent->palette + (self->params >> 8);
        self->drawFlags = self->ext.weapon.parent->drawFlags | FLAG_DRAW_UNK80;
        self->rotZ = self->ext.weapon.parent->rotZ;
        self->ext.weapon.childPalette =
            self->ext.weapon.parent->ext.weapon.childPalette;
        self->ext.weapon.unk8A = self->ext.weapon.parent->ext.weapon.unk8A;
        self->ext.weapon.unk80 = (rand() & 0x1F) + 1;
        self->step++;
        break;
    case 1:
        if (self->ext.weapon.parent->step == 3) {
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.weapon.unk80 == 0) {
            self->rotZ = 0;
            angle = ratan2(-(self->ext.weapon.unk8A - self->posY.i.hi),
                           self->ext.weapon.childPalette - self->posX.i.hi);
            self->velocityX = rcos(angle) * 0x100;
            self->velocityY = -rsin(angle) * 0x100;
            self->step++;
            self->ext.weapon.equipId =
                self->ext.weapon.parent->ext.weapon.equipId;
            SetWeaponProperties(self, 0);
            self->enemyId = self->ext.weapon.parent->enemyId;
            self->hitboxWidth = 0x12;
            self->hitboxHeight = 4;
        }
        break;
    case 3:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->facingLeft == 0) {
            if (self->posX.i.hi > self->ext.weapon.childPalette) {
                DestroyEntity(self);
                return;
            }
        } else {
            if (self->posX.i.hi < self->ext.weapon.childPalette) {
                DestroyEntity(self);
                return;
            }
        }
    }
}

s32 func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 13; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
