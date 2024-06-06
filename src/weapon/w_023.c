// Weapon ID #23. Used by weapons:
// Herald shield, Unknown#207
#include "weapon_private.h"
#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_023", EntityWeaponAttack);

s32 func_ptr_80170004(Entity* self) {}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 23; }

INCLUDE_ASM("weapon/nonmatchings/w_023", EntityWeaponShieldSpell);

INCLUDE_ASM("weapon/nonmatchings/w_023", func_ptr_80170024);

extern AnimationFrame D_A5000_8017AB58[];

void func_ptr_80170028(Entity* self) {

    switch (self->step) {
    case 0:
        self->palette = self->ext.weapon.parent->palette;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->unk4C = D_A5000_8017AB58;
        self->flags |= (FLAG_UNK_04000000 | FLAG_UNK_100000);
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;

        self->rotX = self->rotY = 0;
        self->posY.i.hi += 40;
        self->velocityY = FIX(-1.5);
        self->ext.weapon.unk7E = 0;
        // Note: This is a weird use of the lifetime, it's not a lifetime! It's
        // just caching the initial X position.
        self->ext.weapon.lifetime = self->posX.i.hi;
        self->animFrameIdx = rand() % 5;
        self->animFrameDuration = 2;
        self->ext.weapon.unk7E = 0x400;
        self->ext.weapon.unk80 = (self->params & 0xFF) * 4;
        self->step++;
        return;
    case 1:
        // Actually, looks like it's using unk80 as the life timer.
        if (--self->ext.weapon.unk80 == 0) {
            self->animSet = self->ext.weapon.parent->animSet;
            self->ext.weapon.unk80 = 0x40;
            self->step++;
        }
        return;
    case 2:
        if (--self->ext.weapon.unk80 == 0) {
            DestroyEntity(self);
            return;
        }
        self->posY.val += self->velocityY;
        self->ext.weapon.unk7E = (self->ext.weapon.unk7E + 0x80) & 0xFFF;
        self->posX.i.hi = self->ext.weapon.lifetime +
                          ((rcos(self->ext.weapon.unk7E) * 2) >> 8);
        if (self->ext.weapon.unk7E < 0x800) {
            self->zPriority = 0x1B4;
        } else {
            self->zPriority = 0x1BC;
        }
        self->rotX = self->rotY = -(rsin(self->ext.weapon.unk7E) >> 5) + 0xC0;
        break;
    }
}
void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
