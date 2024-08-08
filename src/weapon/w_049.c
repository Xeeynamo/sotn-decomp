// Weapon ID #49. Used by weapons:
// Firebrand, Marsil, Unknown#179, Unknown#180
#include "weapon_private.h"
#include "shared.h"
#include "sfx.h"

INCLUDE_ASM("weapon/nonmatchings/w_049", EntityWeaponAttack);

extern s16 D_15B000_8017B03C[];

void func_15B000_8017B88C(Entity* ent, Point16* outPoint, bool arg2) {
    s32 idx;

    idx = PLAYER.ext.player.anim - 0x41;
    if (PLAYER.facingLeft) {
        ent->posX.i.hi = PLAYER.posX.i.hi - D_15B000_8017B03C[idx * 4 + 0];
        if (arg2) {
            outPoint->x = -(D_15B000_8017B03C[idx * 4 + 2] * 3 / 4);
        } else {
            outPoint->x = -(D_15B000_8017B03C[idx * 4 + 2] * 2 / 3);
        }
    } else {
        ent->posX.i.hi = PLAYER.posX.i.hi + D_15B000_8017B03C[idx * 4 + 0];
        if (arg2) {
            outPoint->x = D_15B000_8017B03C[idx * 4 + 2] * 3 / 4;
        } else {
            outPoint->x = D_15B000_8017B03C[idx * 4 + 2] * 2 / 3;
        }
    }
    ent->posY.i.hi = PLAYER.posY.i.hi + D_15B000_8017B03C[idx * 4 + 1];
    if (arg2) {
        outPoint->y = D_15B000_8017B03C[idx * 4 + 3] * 3 / 4;
    } else {
        outPoint->y = D_15B000_8017B03C[idx * 4 + 3] * 2 / 3;
    }
}

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
        g_api.PlaySfx(SFX_FM_EXPLODE_B);
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
