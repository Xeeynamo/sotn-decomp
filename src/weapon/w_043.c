// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #43. Used by weapons:
// Alucard sword, Sword Familiar, Alucart sword, Unknown#197
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_043_1.h"
#include "w_043_2.h"
#define g_Animset w_043_1
#define g_Animset2 w_043_2
#include "sfx.h"

extern AnimationFrame D_131000_8017AF40[];
extern SpriteParts D_131000_8017A040[];
extern WeaponAnimation D_131000_8017B014[];

void EntityWeaponAttack(Entity* self) {
    s8 animIndex = (self->params & 0x7FFF) >> 8;
    WeaponAnimation* anim = &D_131000_8017B014[animIndex];
    Primitive* prim;
    s16 offsetX, offsetY;
    bool flag;
    s16 baseX, baseY, modifierY;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;

    if ((PLAYER.ext.player.anim < anim->frameStart) ||
        (PLAYER.ext.player.anim >= anim->frameStart + 7) ||
        g_Player.unk46 == 0) {
        DestroyEntity(self);
        return;
    }

    flag = 0;
    if (self->step == 0) {
        self->primIndex = g_api.AllocPrimBuffers(PRIM_TILE, 16);
        if (self->primIndex != -1) {
            prim = &g_PrimBuf[self->primIndex];
            while (prim != NULL) {
                prim->v0 = 2;
                prim->u0 = 2;
                if (animIndex == 2) {
                    prim->b0 = 0x20;
                    prim->g0 = 0x7F;
                    prim->r0 = 0;
                } else {
                    prim->g0 = 0x20;
                    prim->b0 = 0xFF;
                    prim->r0 = 0x20;
                }
                prim->priority = PLAYER.zPriority + 2;
                prim->drawMode = DRAW_UNK_200 | DRAW_TPAGE2 | DRAW_TPAGE |
                                 DRAW_HIDE | DRAW_TRANSP;
                prim = prim->next;
            }
        }
        SetSpriteBank1(D_131000_8017A040);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->palette += anim->palette;
        self->flags = FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        if (self->primIndex != -1) {
            self->flags =
                FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        }
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
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
    if (PLAYER.animFrameDuration == 1 && PLAYER.animFrameIdx == 3) {
        flag = 1;
    }
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;

    modifierY = 0;
    if (PLAYER.drawFlags & FLAG_DRAW_ROTY) {
        modifierY = -3;
        if (PLAYER.ext.player.anim >= 0x43 && PLAYER.ext.player.anim < 0x45) {
            modifierY = -1;
        }
    }

    if (self->primIndex != -1) {
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            if (prim->r1 == 0) {
                if (flag) {
                    baseX = self->hitboxOffX;
                    baseY = self->hitboxOffY;
                    if (self->facingLeft) {
                        baseX = -baseX;
                    }
                    offsetX = self->posX.i.hi + baseX;
                    offsetY = self->posY.i.hi + baseY + modifierY;

                    prim->x0 = offsetX + (rand() % 48) - 24;
                    prim->y0 = offsetY + (rand() & 7);

                    prim->r1++;
                    prim->g1 = 9;
                    prim->b1 = rand() & 3;
                }
            } else if (prim->b1) {
                prim->b1--;
            } else if (prim->g1) {
                prim->g1--;
                if (prim->g1 < 3) {
                    prim->v0 = 1;
                    prim->u0 = 1;
                }
                prim->drawMode &= ~DRAW_HIDE;
                if (prim->g1 & 1) {
                    prim->y0 = prim->y0 - 1;
                }
                if (self->facingLeft) {
                    prim->x0 = prim->x0 + 2;
                } else {
                    prim->x0 = prim->x0 - 2;
                }
            } else {
                prim->drawMode |= DRAW_HIDE;
            }
            prim = prim->next;
        }
    }
}

s32 func_ptr_80170004(Entity* self) {
    switch (self->step) {
    case 0:
        self->palette = PAL_OVL(0x100);
        self->zPriority = PLAYER.zPriority;
        self->facingLeft = PLAYER.facingLeft;
        // this toggles the high bit, but xor does not
        // produce the same set of instructions
        self->animCurFrame = PLAYER.animCurFrame + ANIM_FRAME_LOAD;
        self->animSet = ANIMSET_DRA(1);
        self->drawMode = DRAW_TPAGE;
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_20000;
        self->unk5A = 0;
        SetSpeedX(FIX(13.0));
        self->velocityY = FIX(-1.0 / 8.0);
        self->step++;
        break;

    case 1:
        self->animCurFrame = PLAYER.animCurFrame + ANIM_FRAME_LOAD;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        DecelerateX(FIX(15.0 / 32.0));
        if (PLAYER.animFrameIdx == 5 && PLAYER.animFrameDuration == 1) {
            self->facingLeft++;
            self->facingLeft &= 1;
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(62, 0), 0);
            self->step++;
        }
        break;

    case 2:
        self->drawMode = DRAW_DEFAULT;
        self->animCurFrame = PLAYER.animCurFrame + ANIM_FRAME_LOAD;
        if (PLAYER.animFrameIdx == 0xE) {
            self->facingLeft++;
            self->facingLeft &= 1;
            SetSpeedX(FIX(-13.0));
            self->velocityY = FIX(1.0 / 8.0);
            self->step++;
        }
        break;

    case 3:
        self->drawMode = DRAW_TPAGE;
        self->animCurFrame = PLAYER.animCurFrame + ANIM_FRAME_LOAD;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        DecelerateX(FIX(15.0 / 32.0));
        if (PLAYER.animFrameIdx == 19) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

static void func_ptr_80170008(Entity* self) {
    if (self->step == 0) {
        self->anim = D_131000_8017AF40;
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_100000 |
                      FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.weapon.parent->enemyId;
        self->hitboxOffX = 0x1B;
        self->hitboxOffY = -0x13;
        self->hitboxWidth = 0x23;
        self->step++;
    } else {
        if ((self->animFrameIdx == 1) || (self->animFrameIdx == 0xB)) {
            g_api.PlaySfx(SFX_ALUCARD_SWORD_SWISH);
        }
        if ((u16)self->animCurFrame - 0x24U < 6) {
            self->hitboxHeight = 8;
        } else {
            self->hitboxHeight = 0;
        }
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
            return;
        }
    }
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 43; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
