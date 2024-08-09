// Weapon ID #15. Used by weapons:
// Shuriken, Cross shuriken, Buffalo star, Flame star, TNT
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_015_1.h"
#include "w_015_2.h"
#define g_Animset w_015_1
#define g_Animset2 w_015_2

INCLUDE_ASM("weapon/nonmatchings/w_015", EntityWeaponAttack);

s32 func_ptr_80170004(Entity* self) {
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

extern AnimationFrame D_6D000_8017A6C0[];
extern s32 D_6D000_8017BFC8;

static void func_ptr_80170008(Entity* self) {
    Entity* factory;

    if (self->step == 0) {
        self->animSet = 2;
        self->unk4C = D_6D000_8017A6C0;
        self->zPriority = PLAYER.zPriority - 4;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
        self->velocityY = FIX(-1);

        if (!(D_6D000_8017BFC8 & 1)) {
            factory =
                g_api.CreateEntFactoryFromEntity(self, FACTORY(0xB00, 4), 0);
            if (factory != NULL) {
                if (g_HandId == 0) {
                    factory->entityId = 0xEF;
                } else {
                    factory->entityId = 0xFF;
                }
            }
        }

        self->posY.i.hi += (rand() % 12) - 6;
        self->posX.i.hi += (rand() & 7) - 3;
        D_6D000_8017BFC8++;

        if (!(rand() & 1)) {
            self->drawMode =
                FLAG_DRAW_UNK40 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK10;
        }
        self->step++;
    }
    self->posY.val += self->velocityY;
    if (self->animFrameDuration < 0) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("weapon/nonmatchings/w_015", func_ptr_8017000C);

INCLUDE_ASM("weapon/nonmatchings/w_015", func_ptr_80170010);

extern SpriteParts D_6D000_8017A2B0[];
extern AnimationFrame D_6D000_8017A770[];

static s32 func_ptr_80170014(Entity* self) {
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

static int GetWeaponId(void) { return 15; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
