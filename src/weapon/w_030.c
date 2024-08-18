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

extern AnimationFrame D_D6000_8017A514[];
extern AnimationFrame D_D6000_8017A548[];
extern WeaponAnimation D_D6000_8017A5E4[];

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

INCLUDE_ASM("weapon/nonmatchings/w_030", func_ptr_8017000C);

s32 func_ptr_80170010(Entity* self) {
    s32 hitboxSize;

    if (self->ext.weapon.parent->entityId == 0) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        self->animSet = 9;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_ROTZ;
        self->rotX = self->rotY = 0x20;
        self->anim = D_D6000_8017A514;
        if ((u8)self->params != 0) {
            self->anim = D_D6000_8017A548;
        }
        self->zPriority = PLAYER.zPriority + 8;
        self->facingLeft = (self->ext.weapon.parent->facingLeft + 1) & 1;
        SetSpeedX(FIX(3.5));
        self->attack = 0x14;
        self->hitboxState = 2;
        self->nFramesInvincibility = 4;
        self->stunFrames = 4;
        self->attackElement = ELEMENT_HIT;
        self->hitEffect = 1;
        self->entityRoomIndex = 0;
        self->posY.i.hi -= 0x27;
        g_api.func_80118894(self);
        self->ext.weapon.vol = 0x30;
        self->step++;
        break;
    case 1:
        if (!(g_GameTimer & 7)) {
            FntPrint("vol:%02x\n", self->ext.weapon.vol);
            g_api.PlaySfxVolPan(SFX_EXPLODE_FAST_A, self->ext.weapon.vol, 0);
            self->ext.weapon.vol += 8;
            if (self->ext.weapon.vol > 0x7F) {
                self->ext.weapon.vol = 0x7F;
            }
        }
        self->rotZ += 0x100;
        self->rotX += 2;
        if (self->rotX > 0x100) {
            self->rotX = 0x100;
        }
        self->rotY = self->rotX;
        if (self->ext.weapon.parent->animFrameIdx == 0x20 &&
            self->animFrameDuration == 1) {
            g_api.PlaySfx(SFX_EXPLODE_SMALL);
            if ((u8)self->params != 0) {
                self->drawMode = DRAW_UNK_40 | DRAW_TPAGE;
                self->step++;
                break;
            }
            DestroyEntity(self);
            return;
        }
        break;
    case 2:
        self->posX.val += self->velocityX;
        if (!(g_GameTimer & 3)) {
            self->rotZ += 0x400;
        }
        if (!(g_GameTimer & 1) && (rand() & 1)) {
            g_api.CreateEntFactoryFromEntity(self, FACTORY(0x100, 0x24), 0);
        }
        if (self->hitFlags != 0) {
            self->step++;
        }
        break;
    case 3:
        self->rotX -= 16;
        self->rotY = self->rotX;
        if (self->rotX < 0x40) {
            self->hitboxState = 0;
            self->animSet = 0;
            self->ext.weapon.lifetime = 0x80;
            self->step++;
        }
        /* fallthrough */
    case 4:
        if (--self->ext.weapon.lifetime == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    hitboxSize = (self->rotX >> 0x6) * 3;
    self->hitboxWidth = hitboxSize;
    self->hitboxHeight = hitboxSize;
}

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
