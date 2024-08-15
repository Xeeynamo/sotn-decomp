// Weapon ID #49. Used by weapons:
// Firebrand, Marsil, Unknown#179, Unknown#180
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "w_049_1.h"
#include "w_049_2.h"
#define g_Animset w_049_1
#define g_Animset2 w_049_2
#include "shared.h"
#include "sfx.h"

extern WeaponAnimation D_15B000_8017AFFC[];
extern SpriteParts D_15B000_8017A040[];
extern s32 D_15B000_8017C8CC;

/* near-duplicate of EntityWeaponAttack_w_048 */
void EntityWeaponAttack(Entity* self) {
    s8 animIndex = (self->params & 0x7FFF) >> 8;
    WeaponAnimation* anim = &D_15B000_8017AFFC[animIndex];

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;

    if ((PLAYER.ext.player.anim < anim->frameStart) ||
        (PLAYER.ext.player.anim >= anim->frameStart + 7) ||
        g_Player.unk46 == 0) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        SetSpriteBank1(D_15B000_8017A040);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->palette += anim->palette;
        self->flags = FLAG_UNK_40000 | FLAG_UNK_20000;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;

        if (animIndex == 1) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) | 0x5B, 0);
        }
        if (animIndex == 3) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) | 0x5F, 0);
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + 0x10040, 0);
        }
        SetWeaponProperties(self, 0);
        D_15B000_8017C8CC = 0;
        self->step += 1;
    }
    self->ext.weapon.anim = PLAYER.ext.player.anim - anim->frameStart;
    if ((PLAYER.animFrameDuration == 1) &&
        (PLAYER.animFrameIdx == anim->soundFrame)) {
        g_api.PlaySfx(anim->soundId);
    }
    if (g_api.UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }
    if ((D_15B000_8017C8CC == 0) && (PLAYER.animFrameIdx == 1)) {
        if ((animIndex == PLAYER.animFrameIdx) || (animIndex == 3)) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) | 0x5D, 0);
            g_api.PlaySfx(SFX_FM_EXPLODE_B);
        }
        if (animIndex == 2) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + 0x1005D, 0);
            g_api.PlaySfx(SFX_FM_EXPLODE_B);
        }
    }
    D_15B000_8017C8CC = PLAYER.animFrameIdx;
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

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

static s32 func_ptr_80170014(Entity* self) {
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

static int GetWeaponId(void) { return 49; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
