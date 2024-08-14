// Weapon ID #53. Used by weapons:
// Katana, Osafune katana, Masamune, Yasutsuna, Unknown#189, Unknown#192,
// Unknown#193, Unknown#194
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_053_1.h"
#include "w_053_2.h"
#define g_Animset w_053_1
#define g_Animset2 w_053_2

INCLUDE_ASM("weapon/nonmatchings/w_053", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_053", func_ptr_80170004);

static void func_ptr_80170008(Entity* self) {
    switch (self->step) {
    case 0:
        self->palette = PAL_OVL(0x100);
        self->zPriority = PLAYER.zPriority;
        self->facingLeft = PLAYER.facingLeft;
        self->animCurFrame = PLAYER.animCurFrame - ANIMSET_OVL_FLAG;
        self->animSet = 1;
        self->drawMode = DRAW_TPAGE;
        self->unk5A = 0;
        self->flags = FLAG_UNK_04000000 | FLAG_UNK_20000;

        SetSpeedX(FIX(8));
        self->velocityY = FIX(-0.5);
        if (self->params & 0x7F00) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + FACTORY(0x2800, 0x38), 0);
        }
        self->step++;
        break;
    case 1:
        self->animCurFrame = PLAYER.animCurFrame - ANIMSET_OVL_FLAG;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        DecelerateX(FIX(15) / 32);
        if (PLAYER.animFrameIdx == 6) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + FACTORY(0x1E00, 0x38), 0);
            self->step++;
        }
        break;
    case 2:
        self->drawMode = 0;
        self->animCurFrame = PLAYER.animCurFrame - ANIMSET_OVL_FLAG;
        if (PLAYER.animFrameIdx == 8 && PLAYER.animFrameDuration == 1) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + FACTORY(0x1E00, 0x38), 0);
        }
        if (PLAYER.animFrameIdx == 10) {
            SetSpeedX(FIX(-8));
            self->velocityY = FIX(0.5);
            self->step++;
        }
        break;
    case 3:
        self->drawMode = DRAW_TPAGE;
        self->animCurFrame = PLAYER.animCurFrame - ANIMSET_OVL_FLAG;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        DecelerateX(FIX(15) / 32);
        if (PLAYER.animFrameIdx == 15) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

INCLUDE_ASM("weapon/nonmatchings/w_053", func_ptr_8017000C);

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 53; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
