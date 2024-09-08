// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #55. Used by weapons:
// Holy sword, Unknown#196
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_055_1.h"
#include "w_055_2.h"
#define g_Animset w_055_1
#define g_Animset2 w_055_2

extern WeaponAnimation D_185000_8017B0AC[];
extern u8 D_185000_8017B0B8[];
extern AnimationFrame D_185000_8017B174[];

void EntityWeaponAttack(Entity* self) {
    s8 animIndex = (self->params & 0x7FFF) >> 8;
    WeaponAnimation* anim = &D_185000_8017B0AC[animIndex];

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;

    if ((PLAYER.ext.player.anim < anim->frameStart) ||
        (PLAYER.ext.player.anim >= anim->frameStart + 7) ||
        (g_Player.unk46 == 0)) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->palette += anim->palette;
        self->flags = FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        if (animIndex == 1) {
            g_api.PlaySfx(SFX_UNK_69D);
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x38, 0), 0);
        }
        SetWeaponProperties(self, 0);
        self->step++;
    }
    self->ext.weapon.anim = PLAYER.ext.player.anim - anim->frameStart;
    if (PLAYER.animFrameDuration == 1 &&
        PLAYER.animFrameIdx == anim->soundFrame) {
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

extern SpriteParts D_185000_8017B160[];

s32 func_ptr_80170004(Entity* self) {
    Primitive* prim;
    s32 angle;
    s32 scale;
    s32 x, y;
    s16 xOffset, yOffset;
    s32 i;
    s16 params;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;

    params = (self->params >> 4) & 0x7f0;

    if (PLAYER.ext.player.anim < D_185000_8017B0B8[params] ||
        PLAYER.ext.player.anim >= (D_185000_8017B0B8[params] + 7) ||
        !g_Player.unk46) {
        DestroyEntity(self);
        return;
    }

    xOffset = 12;
    if (PLAYER.facingLeft) {
        xOffset = -xOffset;
    }
    x = self->posX.i.hi + xOffset;
    y = self->posY.i.hi - 28;

    if (self->step == 0) {
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 64);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 64; i++) {
            prim->r1 = 127;
            prim->g1 = 127;
            prim->b1 = 255;
            prim->x2 = rand() & 0xFFF;
            prim->x3 = (rand() & 0xFF) + 512;
            prim->y2 = prim->x3 / 2;
            prim->priority = PLAYER.zPriority + 2;
            prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                             DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;
        }
        SetSpriteBank2(D_185000_8017B160);
        self->animSet = ANIMSET_OVL(0x11);
        self->palette = PAL_DRA(0x117);
        self->unk5A = 0x65;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 24;
            self->unk5A += 2;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_UNK_100000 |
                      FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        self->anim = D_185000_8017B174;
        self->zPriority = PLAYER.zPriority + 4;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.weapon.parent->enemyId;
        self->hitboxWidth = self->hitboxHeight = 32;
        self->hitboxOffX = 12;
        self->hitboxOffY = -28;
        self->step++;
    } else {
        if (self->animCurFrame == 1 && self->animFrameDuration == 1) {
            self->hitboxWidth = self->hitboxHeight = 12;
            self->hitboxOffX = 13;
            self->hitboxOffY = -28;
        }
    }

    if (self->animFrameDuration < 0) {
        DestroyEntity(self);
        return;
    }

    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 64; i++) {
        if (prim->r1 >= 17) {
            prim->r1 -= 12;
        }
        if (prim->g1 >= 17) {
            prim->g1 -= 12;
        }
        if (prim->b1 >= 17) {
            prim->b1 -= 24;
        }

        angle = prim->x2;
        scale = prim->x3;
        prim->x3 += prim->y2;
        prim->x0 = x;
        prim->y0 = y;
        prim->x1 = x + (((rcos(angle) >> 8) * scale) >> 8);
        prim->y1 = y - (((rsin(angle) >> 8) * scale) >> 8);
        prim = prim->next;
    }
}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 55; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
