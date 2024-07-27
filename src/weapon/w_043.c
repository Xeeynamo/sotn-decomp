// Weapon ID #43. Used by weapons:
// Alucard sword, Sword Familiar, Alucart sword, Unknown#197
#include "weapon_private.h"
#include "shared.h"

extern SpriteParts D_131000_8017A040[];
extern AnimationFrame D_131000_8017AF40[];

INCLUDE_ASM("weapon/nonmatchings/w_043", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_043", func_ptr_80170004);

void func_ptr_80170008(Entity* self) {
    if (self->step == 0) {
        self->unk4C = D_131000_8017AF40;
        SetSpriteBank1(D_131000_8017A040);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_UNK_100000 | FLAG_UNK_40000 |
                      FLAG_UNK_20000;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.weapon.parent->enemyId;
        self->hitboxOffX = 0x1B;
        self->hitboxOffY = -0x13;
        self->hitboxWidth = 0x23;
        self->step++;
    } else {
        if ((self->animFrameIdx == 1) || (self->animFrameIdx == 0xB)) {
            g_api.PlaySfx(SE_WPN_ALUCARD_SWORD_SWING);
        }
        if ((u16)self->animCurFrame - 0x24U < 6) {
            self->hitboxHeight = 8;
        } else {
            self->hitboxHeight = 0;
        }
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
            return;
        }
    }
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

void func_ptr_8017000C(Entity* self) {}

s32 func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 43; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
