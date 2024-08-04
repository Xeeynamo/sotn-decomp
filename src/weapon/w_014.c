// Weapon ID #14. Used by weapons:
// Runesword
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_014_1.h"
#include "w_014_2.h"
#define g_Animset w_014_1
#define g_Animset2 w_014_2

INCLUDE_ASM("weapon/nonmatchings/w_014", EntityWeaponAttack);

s32 func_ptr_80170004(Entity* self) {
    s16 angle;
    u16 baseX, baseY;
    s16 paramsLo;

    if (self->ext.weapon.parent->entityId == 0) {
        DestroyEntity(self);
        return;
    }
    paramsLo = self->params & 0xFF;
    angle = 0;
    if (self->step == 0) {
        self->facingLeft = self->ext.weapon.parent->facingLeft;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 | FLAG_UNK_20000;
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.weapon.parent->enemyId;
        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        self->step++;
    }

    if (self->ext.weapon.parent->drawFlags & FLAG_DRAW_ROTZ) {
        angle = self->ext.weapon.parent->rotZ;
    }
    if (self->facingLeft) {
        angle = 0x800 - angle;
    }
    switch (paramsLo) {
    case 0:
        baseX = ((rcos(angle) >> 4) * 5) >> 7;
        baseY = ((rsin(angle) >> 4) * 5) >> 7;
        break;
    case 1:
        baseX = ((rcos(angle) >> 4) * 5) >> 6;
        baseY = ((rsin(angle) >> 4) * 5) >> 6;
        break;
    case 2:
        baseX = ((rcos(angle) >> 4) * 0xF) >> 7;
        baseY = ((rsin(angle) >> 4) * 0xF) >> 7;
        break;
    case 3:
        baseX = ((rcos(angle) >> 4) * 5) >> 5;
        baseY = ((rsin(angle) >> 4) * 5) >> 5;
        break;
    }
    self->posX.i.hi = baseX + self->ext.weapon.parent->posX.i.hi;
    self->posY.i.hi = baseY + self->ext.weapon.parent->posY.i.hi;
}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 14; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
