// Weapon ID #22. Used by weapons:
// Magic Missile
#include "weapon_private.h"
#include "shared.h"

extern AnimationFrame D_9E000_8017A760[];
extern AnimationFrame D_9E000_8017A800[];

extern SpriteParts D_9E000_8017A040[];
extern AnimationFrame D_9E000_8017A77C[];

void EntityWeaponAttack(Entity* self) {
    s16 deltaX;

    switch (self->step) {
    case 0:
        SetSpriteBank1(D_9E000_8017A040);
        self->animSet = ANIMSET_OVL(16);
        self->palette = PAL_DRA(0x110);
        self->unk5A = 0x64;

        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }

        self->zPriority = PLAYER.zPriority + 2;
        self->facingLeft = PLAYER.facingLeft;
        self->flags = FLAG_UNK_100000 | FLAG_UNK_40000;
        self->unk4C = D_9E000_8017A77C;

        deltaX = (self->facingLeft) ? 32 : -32;
        self->posY.i.hi -= 6;
        self->posX.i.hi += deltaX;

        g_api.PlaySfx(0x669);
        DestroyEntityWeapon(1);
        g_Player.D_80072F00[10] = 4;
        self->step++;
        break;

    case 1:
        if (self->animFrameDuration < 0) {
            self->ext.timer.t = 16;
            self->drawFlags |= DRAW_MENU;
            self->step++;
        }
        if (self->animFrameIdx == 20 && self->animFrameDuration == 2 &&
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) | 0x38, 0)) {
            g_api.PlaySfx(SFX_ARROW_SHOT_A);
        }
        break;

    case 2:
        self->ext.timer.t--;
        if (self->ext.timer.t == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

s32 func_ptr_80170004(Entity* self) {
    switch (self->step) {
    case 0:
        if (self->ext.weapon.parent->entityId == 0) {
            DestroyEntity(self);
            break;
        }
        self->facingLeft = self->ext.weapon.parent->facingLeft;
        self->animSet = self->ext.weapon.parent->animSet;
        self->unk4C = D_9E000_8017A800;
        self->zPriority = PLAYER.zPriority + 2;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->palette = self->ext.weapon.parent->palette;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
        SetSpeedX(FIX(5));
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->hitboxOffX = 8;
        self->hitboxWidth = 8;
        self->hitboxHeight = 4;
        self->step++;
        break;
    case 1:
        if (self->hitFlags == 1) {
            self->animFrameDuration = 0;
            self->animFrameIdx = 0;
            self->unk4C = D_9E000_8017A760;
            self->step++;
        } else {
            self->posX.val += self->velocityX;
        }
        break;
    case 2:
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

s32 func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 22; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
