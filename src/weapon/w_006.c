// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #6. Used by weapons:
// Moon rod, Unknown#172
#define FUNC_04_VOID
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_006_1.h"
#include "w_006_2.h"
#define g_Animset w_006_1
#define g_Animset2 w_006_2
#include "sfx.h"

extern u16 D_2E000_8017ABD4[];
extern s32 D_2E000_8017ABF0[];

extern WeaponAnimation D_2E000_8017ABC4[];
static void EntityWeaponAttack(Entity* self) {
    WeaponAnimation* anim;
    s8 animIndex;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;
    animIndex = (self->params >> 8) & 0x7f;
    anim = &D_2E000_8017ABC4[animIndex];

    if (PLAYER.ext.weapon.anim < anim->frameStart ||
        PLAYER.ext.weapon.anim >= (anim->frameStart + 7) ||
        g_Player.unk46 == 0) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(16);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->palette += anim->palette;
        self->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE | DRAW_TPAGE2;
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

static void func_ptr_80170004(Entity* self) {
    s32 hitboxSize;
    u16 data;

    switch (self->step) {
    case 0:
        self->posY.i.hi += PLAYER.hitboxOffY;
        if (PLAYER.facingLeft != 0) {
            self->posX.i.hi = self->posX.i.hi - PLAYER.hitboxOffX;
        } else {
            self->posX.i.hi = self->posX.i.hi + PLAYER.hitboxOffX;
        }
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x116;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->animCurFrame = 0x42;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawFlags = DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        self->rotX = self->rotY = 0x40;
        self->ext.weapon_006.velocityZ = 0x40;

        SetSpeedX(rand() - FIX(4));

        if (self->facingLeft == 0) {
            self->ext.weapon_006.accelerationX = FIX(15.0 / 64);
        } else {
            self->ext.weapon_006.accelerationX = -FIX(15.0 / 64);
        }
        self->velocityY =
            (rand() & 0x1FFF) + D_2E000_8017ABF0[(u8)self->params];
        self->ext.weapon_006.accelerationY = -(self->velocityY >> 4);
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_20000;
        self->rotZ = rand();

        if (!(self->params & ~0x8000)) {
            g_api.PlaySfx(SFX_VO_ALU_ATTACK_A);
        }
        SetWeaponProperties(self, 0);
        DestroyEntityWeapon(true);
        g_Player.timers[10] = 4;
        self->step++;
        break;
    case 1:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        DecelerateX(FIX(5.0 / 32));
        self->rotX++;
        self->rotY = self->rotX;
        if (self->velocityX == 0) {
            self->zPriority = PLAYER.zPriority + 2;
            self->ext.weapon_006.lifetime = 0x18;
            self->step++;
        }
        break;
    case 2:
        self->ext.weapon_006.velocityZ += 8;
        if (--self->ext.weapon_006.lifetime == 0) {
            g_api.PlaySfx(SFX_TRANSFORM);
            self->step++;
        }
        break;
    case 3:
        self->rotX += 2;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityX += self->ext.weapon_006.accelerationX;
        self->velocityY += self->ext.weapon_006.accelerationY;
        if (!(self->ext.weapon_006.unk7C & 1)) {
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x40, 0), 0);
        }
        break;
    case 4:
        if (--self->ext.weapon_006.lifetime == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    if (self->step != 4) {
        self->rotY = self->rotX;
        self->rotZ = self->rotZ + self->ext.weapon_006.velocityZ;
        data = D_2E000_8017ABD4[(self->ext.weapon_006.unk7C >> 1) % 14];
        if (self->params & 0x8000) {
            self->palette = data + 0x12E;
        } else {
            self->palette = data + 0x116;
        }
        self->ext.weapon_006.unk7C++;
        hitboxSize = (self->rotX * 3) >> 5;
        self->hitboxWidth = hitboxSize;
        self->hitboxHeight = hitboxSize;
        if (self->hitFlags != 0) {
            self->palette = PAL_OVL(0x15F);
            self->drawMode = DRAW_TPAGE;
            self->ext.weapon_006.lifetime = 8;
            self->step = 4;
        }
        if (self->ext.weapon_006.unk7C % 10 == 0 && !(self->params & ~0x8000)) {
            g_api.PlaySfx(SFX_WEAPON_SWISH_B);
        }
    }
}

extern u8 D_2E000_8017AC04[6][8];

static s32 func_2E000_8017B6A0(Primitive* prim, s32 x, s32 y) {
    s32 size;
    s32 left;
    s32 right;
    s32 top;
    s32 bottom;
    u8* uvPtr;

    // Should be able to do this as an array access but nope
    uvPtr = &D_2E000_8017AC04;
    uvPtr += prim->b0 * 8;

    if (prim->b0 >= 3) {
        size = 4;
    } else {
        size = 6;
    }
    if (prim->b0 == 6) {
        return -1;
    }
    left = x - size;
    top = y - size;
    right = x + size;
    bottom = y + size;

    prim->x0 = left;
    prim->y0 = top;
    prim->x1 = right;
    prim->y1 = top;
    prim->x2 = left;
    prim->y2 = bottom;
    prim->x3 = right;
    prim->y3 = bottom;

    prim->u0 = *uvPtr++;
    prim->v0 = *uvPtr++;
    prim->u1 = *uvPtr++;
    prim->v1 = *uvPtr++;
    prim->u2 = *uvPtr++;
    prim->v2 = *uvPtr++;
    prim->u3 = *uvPtr++;
    prim->v3 = *uvPtr++;
    if (!(++prim->b1 & 1)) {
        prim->b0++;
    }
    return 0;
}

static void func_ptr_80170008(Entity* self) {
    Primitive* prim;
    s32 posX, posY;
    s32 range;

    if (self->step == 0) {
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);

        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->velocityY = FIX(1.0 / 2.0);
        range = 24;
        posX = (rand() % range) - 0xC;
        self->posX.i.hi += posX;
        posY = (rand() % range) - 0xC;
        self->posY.i.hi += posY;

        prim = &g_PrimBuf[self->primIndex];
        prim->clut = 0x1B0;
        prim->tpage = 0x1A;
        prim->b0 = 0;
        prim->b1 = 0;
        prim->priority = self->zPriority + 4;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;

        func_2E000_8017B6A0(prim, self->posX.i.hi, self->posY.i.hi);
        self->step++;
    } else {
        self->posY.val += self->velocityY;
        prim = &g_PrimBuf[self->primIndex];
        if (func_2E000_8017B6A0(prim, self->posX.i.hi, self->posY.i.hi) != 0) {
            DestroyEntity(self);
        }
    }
}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 6; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
