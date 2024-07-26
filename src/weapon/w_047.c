// Weapon ID #47. Used by weapons:
// Dynamite
#include "weapon_private.h"
#include "shared.h"

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
            self->animSet = 0x8011;
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
            self->drawMode = 0x30;
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

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

s32 func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 47; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
