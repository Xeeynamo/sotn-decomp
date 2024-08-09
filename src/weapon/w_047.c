// Weapon ID #47. Used by weapons:
// Dynamite
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_047_1.h"
#include "w_047_2.h"
#define g_Animset w_047_1
#define g_Animset2 w_047_2

INCLUDE_ASM("weapon/nonmatchings/w_047", EntityWeaponAttack);

extern SpriteParts D_14D000_8017A0D4[];
extern AnimationFrame D_14D000_8017A528[];

s32 func_ptr_80170004(Entity* self) {
    s16 speed;

    if (self->step == 0) {
        if (self->ext.factory.parent->entityId == 0) {
            DestroyEntity(self);
        } else {
            SetSpriteBank2(D_14D000_8017A0D4);
            self->animSet = ANIMSET_OVL(0x11);
            self->unk5A = 0x64;
            self->palette = 0x111;
            if (g_HandId != 0) {
                self->palette = 0x129;
                self->unk5A += 2;
                self->animSet += 2;
            }
            self->unk4C = D_14D000_8017A528;
            self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
            self->zPriority = PLAYER.zPriority + 2;
            speed = (rand() % 1535) + 0x100;
            self->velocityX = rcos((s32)speed) << 7;
            self->velocityY = -(rsin((s32)speed) << 7);
            self->posX.val += self->velocityX * 2;
            self->posY.val += self->velocityY * 2;
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
            if (rand() & 1) {
                self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
            }
            self->step += 1;
        }
        return;
    }
    self->posY.val += self->velocityY;
    self->posX.val += self->velocityX;
    if (self->animFrameDuration < 0) {
        DestroyEntity(self);
    }
}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 47; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
