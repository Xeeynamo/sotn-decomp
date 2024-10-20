// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #39. Used by weapons:
// Were Bane, Unknown#190
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_039_1.h"
#include "w_039_2.h"
#define g_Animset w_039_1
#define g_Animset2 w_039_2
#include "sfx.h"

extern WeaponAnimation D_115000_8017ADC0[2];

static void EntityWeaponAttack(Entity* self) {
    WeaponAnimation* anim;
    s8 animIndex;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;
    animIndex = (self->params & 0x7fff) >> 0x8;
    anim = &D_115000_8017ADC0[animIndex];

    if (PLAYER.ext.weapon.anim < anim->frameStart ||
        PLAYER.ext.weapon.anim >= (anim->frameStart + 7) || !g_Player.unk46) {
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
        self->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED;
        self->zPriority = PLAYER.zPriority - 2;
        SetWeaponProperties(self, 0);

        self->step++;
    }

    self->ext.weapon.anim = PLAYER.ext.weapon.anim - anim->frameStart;

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

    if (animIndex != 0 && PLAYER.animFrameIdx == 4 &&
        PLAYER.animFrameDuration == 1) {
        g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x38, 0), 0);
    }
}

extern s32 D_115000_8017BA28;
extern s16 D_115000_8017BA2C[];
extern s16 D_115000_8017BA6C[];

s32 func_ptr_80170004(Entity* self) {
    const int PrimCount = 32;
    Primitive* prim;
    s32 i;
    s16 x, y;
    s16 xPos, yPos;
    s16 xOffset, yOffset;
    s16 params;

    params = (self->params & 0x7fff) >> 8; // unused (for PSP)

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;

    if (!g_Player.unk46 || PLAYER.step_s != 0x5A) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, PrimCount);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        prim = &g_PrimBuf[self->primIndex];

        for (i = 0; i < PrimCount; i++) {
#ifdef VERSION_PSP
            prim->r0 = 0xBF;
            prim->r1 = i;
            prim->g0 = 0x3F;
            prim->g1 = i;
            prim->b0 = 0xFF;
            prim->b1 = i;
#else
            prim->r0 = 0xBF;
            prim->r1 = 0xBF;
            prim->g0 = 0x3F;
            prim->g1 = 0x3F;
            prim->b0 = 0xFF;
            prim->b1 = 0xFF;
#endif
            prim->r2 = (i * 2) + 1;
            prim->priority = PLAYER.zPriority + 4;
            prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                             DRAW_TPAGE | DRAW_HIDE | DRAW_TRANSP;
            prim = prim->next;
        }

        self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.weapon.parent->enemyId;
        D_115000_8017BA28 = 40;
        self->hitboxWidth = 24;
        self->hitboxHeight = 10;
        self->hitboxOffX = 38;
        self->hitboxOffY = -12;
        self->step++;
    } else {
        if ((D_115000_8017BA28 & 7) == 7) {
            g_api.PlaySfx(SFX_ANIME_SWORD_B);
        }

        if (--D_115000_8017BA28 == 0) {
            g_api.PlaySfx(SFX_VO_ALU_ATTACK_C);
            DestroyEntity(self);
            return;
        }
    }

    prim = &g_PrimBuf[self->primIndex];

    xPos = 34;
    yPos = -14;

    if (PLAYER.facingLeft) {
        xPos = -xPos;
    }

    x = PLAYER.posX.i.hi + xPos;
    y = PLAYER.posY.i.hi + yPos;

    if (PLAYER.drawFlags & FLAG_DRAW_ROTY) {
        y -= 3;
    }

    for (i = 0; i < PrimCount; i++) {
        switch (prim->r3) {
        case 0:
            if (--prim->r2 == 0) {
                if (i == 0) {
                    xPos = x + (rand() % 24) - 12;
                    yPos = (y + (rand() % 18)) - 9;

                    if (!PLAYER.facingLeft) {
                        prim->x0 = xPos - 16;
                        prim->x1 = xPos + 16;
                    } else {
                        prim->x0 = xPos + 16;
                        prim->x1 = xPos - 16;
                    }
                    prim->y1 = yPos;
                    prim->y0 = yPos;
                    D_115000_8017BA2C[i] = prim->x1;
                    D_115000_8017BA6C[i] = prim->y1;
                    prim->drawMode &= ~DRAW_HIDE;
                    prim->r2 = 9;
                    prim->r3++;
                } else {
                    if (i & 1) {
                        xPos = x + (rand() % 24) - 12;
                        yPos = y + (rand() % 18) - 9;
                        if (!PLAYER.facingLeft) {
                            prim->x0 = D_115000_8017BA2C[i - 1];
                            prim->x1 = xPos - 16;
                        } else {
                            prim->x0 = D_115000_8017BA2C[i - 1];
                            prim->x1 = xPos + 16;
                        }
                        prim->y0 = D_115000_8017BA6C[i - 1];
                        prim->y1 = yPos;
                        D_115000_8017BA2C[i] = prim->x1;
                        D_115000_8017BA6C[i] = prim->y1;
                        prim->drawMode &= ~DRAW_HIDE;
                        prim->r2 = 9;
                        prim->r3++;
                    } else {
                        xPos = x + (rand() % 24) - 12;
                        yPos = y + (rand() % 18) - 9;
                        if (!PLAYER.facingLeft) {
                            prim->x0 = D_115000_8017BA2C[i - 1];
                            prim->x1 = xPos + 16;
                        } else {
                            prim->x0 = D_115000_8017BA2C[i - 1];
                            prim->x1 = xPos - 16;
                        }
                        prim->y1 = yPos;
                        prim->y0 = D_115000_8017BA6C[i - 1];

                        D_115000_8017BA2C[i] = prim->x1;
                        D_115000_8017BA6C[i] = prim->y1;
                        prim->drawMode &= ~DRAW_HIDE;
                        prim->r2 = 9;
                        prim->r3++;
                    }
                }
            }
            break;
        case 1:
            if (--prim->r2 == 0) {
                prim->r3++;
                prim->drawMode |= DRAW_HIDE;
            }
            break;
        }
        prim = prim->next;
    }
}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 39; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
