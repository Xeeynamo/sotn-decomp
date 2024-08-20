// Weapon ID #30. Used by weapons:
// Sword of Dawn, Unknown#177
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_030_1.h"
#include "w_030_2.h"
#define g_Animset w_030_1
#define g_Animset2 w_030_2

extern WeaponAnimation D_D6000_8017A5E4[];
extern s16 D_D6000_8017A66C[16];
extern s32 D_D6000_8017CC44;

static void EntityWeaponAttack(Entity* self) {
    WeaponAnimation* anim;
    WeaponAnimation* anim2;
    s8 animIndex;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;
    animIndex = (self->params >> 8) & 0x7f;
    anim = &D_D6000_8017A5E4[animIndex];

    if (PLAYER.ext.weapon.anim < anim->frameStart ||
        PLAYER.ext.weapon.anim >= (anim->frameStart + 7) ||
        g_Player.unk46 == 0) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        self->animSet = 10;
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->palette += anim->palette;
        self->flags = FLAG_UNK_20000 | FLAG_UNK_40000;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE | DRAW_TPAGE2 | DRAW_UNK_40;
        SetWeaponProperties(self, 0);
        self->step++;
    }

    self->ext.weapon.anim = PLAYER.ext.weapon.anim - anim->frameStart;

    if ((PLAYER.animFrameDuration == 1) &&
        (PLAYER.animFrameIdx == anim->soundFrame)) {
        g_api.PlaySfx(anim->soundId);
    }

    if (g_api.UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }

    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

INCLUDE_ASM("weapon/nonmatchings/w_030", func_ptr_80170004);

INCLUDE_ASM("weapon/nonmatchings/w_030", func_ptr_80170008);

void func_ptr_8017000C(Entity* self) {
    s16 result;
    s16 angleDiff;
    s16 maskedParams;
    s32 temp_a2;
    s16 angle;
    s32 temp_lo;

    maskedParams = (self->params >> 8) & 0x7F;
    switch (self->step) {
    case 0:
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->flags = FLAG_UNK_08000000;
        self->animSet = 0xA;
        self->animCurFrame = 0x64;
        self->zPriority = PLAYER.zPriority + 2;
        self->facingLeft = self->ext.weapon.parent->facingLeft;
        if (maskedParams == 1) {
            self->posY.i.hi -= 4;
        }
        if (maskedParams == 0) {
            self->posY.i.hi -= 0x10;
        }
        if (maskedParams == 2) {
            self->posY.i.hi -= 28 + (rand() & 15);
            self->posX.i.hi += D_D6000_8017A66C[D_D6000_8017CC44 % 3];
            self->posX.i.hi += -4 + (rand() & 7);
            self->ext.weapon.unk82 = (self->facingLeft + 1) & 1;
            self->facingLeft = 0;
            self->drawFlags = DRAW_COLORS;
            self->step = 2;
            g_api.PlaySfx(SFX_UNK_6BA);
            self->ext.weapon.unk80 = rand();
            self->ext.weapon.lifetime = ((u8)self->params * 4) + 0x30;
            D_D6000_8017CC44++;
        } else {
            SetSpeedX(FIX(-5.5));
            self->posX.val += self->velocityX * 5;
        }
        self->attack = 4;
        self->attackElement = ELEMENT_HIT;
        self->hitboxState = 2;
        self->nFramesInvincibility = 4;
        self->stunFrames = 4;
        self->hitEffect = 1;
        self->entityRoomIndex = 0;
        g_api.func_80118894(self);
        self->hitboxWidth = 8;
        self->hitboxHeight = 4;
        self->step++;
        break;
    case 1:
        if (maskedParams == 2) {
            result = g_api.func_80118B18(
                self, self->ext.weapon_030.other, self->ext.weapon.unk82);
            if (result >= 0) {
                temp_a2 = self->ext.weapon.unk80 & 0xFFF;
                angle = temp_a2;
                angleDiff = abs(angle - result);
                if (self->ext.weapon.unk98 > angleDiff) {
                    self->ext.weapon.unk98 = angleDiff;
                }
                if (angle < result) {
                    if (angleDiff < 0x800) {
                        angle += self->ext.weapon.unk98;
                    } else {
                        angle -= self->ext.weapon.unk98;
                    }
                } else {
                    if (angleDiff < 0x800) {
                        angle -= self->ext.weapon.unk98;
                    } else {
                        angle += self->ext.weapon.unk98;
                    }
                }
                self->ext.weapon.unk80 = angle & 0xFFF;
            }
            self->velocityX =
                (rcos(self->ext.weapon.unk80) * self->ext.weapon.unk9A) >> 5;
            temp_lo = rsin(self->ext.weapon.unk80) * self->ext.weapon.unk9A;
            self->ext.weapon.unk98 += 0x18;
            self->rotZ = -self->ext.weapon.unk80 + 0x800;
            self->velocityY = -(temp_lo >> 5);
        }
        if (self->hitFlags != 0) {
            self->ext.weapon.lifetime = 10;
            self->step++;
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        return;
    case 2:
        self->drawFlags |= FLAG_DRAW_UNK80;
        if (--self->ext.weapon.lifetime == 0) {
            DestroyEntity(self);
            return;
        }
        return;
    case 3:
        self->ext.weapon.unk80 += 0x100;
        self->rotZ = -self->ext.weapon.unk80 + 0x800;
        if (--self->ext.weapon.lifetime == 0) {
            self->ext.weapon_030.other = g_api.func_80118970();
            self->ext.weapon.unk98 = 0x20;
            self->ext.weapon.unk9A = 0x600;
            g_api.PlaySfx(SFX_ARROW_SHOT_C);
            self->step = 1;
        }
        break;
    }
}

INCLUDE_ASM("weapon/nonmatchings/w_030", func_ptr_80170010);

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 30; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
