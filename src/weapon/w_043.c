// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #43. Used by weapons:
// Alucard sword, Sword Familiar, Alucart sword, Unknown#197
#include "weapon_private.h"
#include "gen/w_043_1.h"
#include "gen/w_043_2.h"
#define g_Animset w_043_1
#define g_Animset2 w_043_2
#include "sfx.h"

static u16 pal_0[N_ARRAY_PAL][COLORS_PER_PAL] = {
    {0x0000, 0x8000, 0xA821, 0x9DC0, 0xA821, 0xA821, 0xA821, 0xA821, 0x843F,
     0xB0E4, 0x9CA4, 0x0000, 0x0000, 0x0000, 0xD294, 0xF2F3},
    {0x0000, 0x8000, 0x0000, 0x0000, 0x0000, 0xED8C, 0xED8C, 0xED8C, 0x843F,
     0xBC00, 0xBC00, 0xED8C, 0xED8C, 0xED8C, 0xD294, 0xFFFF},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xE021, 0xE021, 0x801F,
     0x9C00, 0xB800, 0xE021, 0x0000, 0x0000, 0xD294, 0xEAD3},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xA0C0, 0x0000, 0x843F,
     0x0000, 0xA800, 0x0000, 0xF608, 0x0000, 0xD294, 0xE24C},
    {0x0000, 0x8000, 0x9C00, 0x9DC0, 0x9C00, 0x9C00, 0x9C00, 0x9C00, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF2D1},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0xD400, 0xD400, 0xD400, 0xD400, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xCCA0, 0x0000, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xEA90}};
static u16 pal_2[N_ARRAY_PAL][COLORS_PER_PAL] = {
    {0x0000, 0x8007, 0xAD6B, 0xAD6B, 0xAD6B, 0xAD6B, 0xAD6B, 0xAD6B, 0x843F,
     0xB148, 0xA928, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8007, 0x0000, 0x0000, 0x0000, 0xE717, 0xE717, 0xE717, 0x843F,
     0xA0E6, 0xA0E6, 0xE717, 0xE717, 0xE717, 0xD294, 0xF39C},
    {0x0000, 0x8007, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xB56A, 0xA927, 0x801F,
     0x9062, 0x98C6, 0xB148, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8007, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xA4E6, 0x0000, 0x843F,
     0x0000, 0x9483, 0x0000, 0xA0C4, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8007, 0x98C6, 0x9DC0, 0x98C6, 0x98C6, 0x98C6, 0x98C6, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8007, 0x0000, 0x9DC0, 0xA94A, 0xA94A, 0xA94A, 0xA94A, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8007, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x94A5, 0x0000, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xEB5A}};
static u16 pal_3[N_ARRAY_PAL][COLORS_PER_PAL] = {
    {0x0000, 0x8000, 0x800F, 0x800F, 0x800F, 0x800F, 0x800F, 0x800F, 0x83E0,
     0x800F, 0x8CB4, 0x0000, 0x0000, 0x0000, 0xD294, 0xCF1C},
    {0x0000, 0x8000, 0x0000, 0x0000, 0x0000, 0xA818, 0xB0B8, 0xAC38, 0x83E0,
     0x800E, 0x8450, 0x9418, 0x9418, 0x9818, 0xD294, 0xFFFF},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x8014, 0x940C, 0x83E0,
     0x8005, 0x844E, 0x807D, 0x0000, 0x0000, 0xD294, 0xE35C},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xA008, 0x0000, 0x83E0,
     0x0000, 0x8008, 0x0000, 0x806C, 0x0000, 0xD294, 0xBEBC},
    {0x0000, 0x8000, 0x800B, 0x9DC0, 0x800B, 0x800B, 0x800B, 0x800B, 0x83E0,
     0xB9C0, 0x800B, 0x0000, 0x0000, 0x0000, 0xD294, 0xAABC},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x8011, 0x8011, 0x8011, 0x8011, 0x83E0,
     0xB9C0, 0x8011, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x8008, 0x0000, 0x83E0,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0x9E1C}};
static u16 pal_1[N_ARRAY_PAL][COLORS_PER_PAL] = {
    {0x0000, 0x8000, 0x8900, 0x8900, 0x8900, 0x8900, 0x8902, 0x8904, 0x843F,
     0x9541, 0x95E1, 0x0000, 0x0000, 0x0000, 0xD294, 0xF2D1},
    {0x0000, 0x8000, 0x0000, 0x0000, 0x0000, 0xA208, 0xA208, 0xA208, 0x843F,
     0x9541, 0x9541, 0xA208, 0xA208, 0xA208, 0xD294, 0xF39C},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x8160, 0x8920, 0x801F,
     0x8080, 0x88E1, 0x8160, 0x0000, 0x0000, 0xD294, 0xE796},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x94A0, 0x0000, 0x843F,
     0x0000, 0x8080, 0x0000, 0xA264, 0x0000, 0xD294, 0xAB8D},
    {0x0000, 0x8000, 0x80E0, 0x80E0, 0x80E0, 0x80E0, 0x80E0, 0x80E0, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF2B2},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x8200, 0x8200, 0x8200, 0x8200, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8000, 0x0000, 0xA686, 0x0000, 0x0000, 0xA520, 0x0000, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xB792}};
static u16 pal_4[N_ARRAY_PAL][COLORS_PER_PAL] = {
    {0x0000, 0x8000, 0x817F, 0x81B6, 0x81DF, 0x827F, 0xA2FE, 0xD77F, 0x843F,
     0x819E, 0x9A1F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8000, 0x0000, 0x0000, 0x0000, 0xB77D, 0xB77D, 0xB77D, 0x843F,
     0x811E, 0x811E, 0xB77D, 0xB77D, 0xB77D, 0xD294, 0xFFFF},
    {0x0000, 0x8000, 0x0000, 0x9A1F, 0x0000, 0x0000, 0x8E3F, 0x99DF, 0x801F,
     0x80B0, 0x811A, 0x9ADF, 0x0000, 0x0000, 0xD294, 0xE35C},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x80FE, 0x0000, 0x843F,
     0x0000, 0x80B1, 0x0000, 0x8157, 0x0000, 0xD294, 0xD31C},
    {0x0000, 0x8000, 0x8158, 0x81B6, 0x819B, 0x823D, 0xA2FF, 0xD31F, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8000, 0x0000, 0xB77D, 0xB77D, 0xB77D, 0xB77D, 0xB77D, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8000, 0x0000, 0x819E, 0x0000, 0x0000, 0x811E, 0x0000, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C}};
static u16 anim_0[] = {
    WPOSE(1, 1),  WPOSE(2, 2),  WPOSE(3, 2),  WPOSE(4, 2), WPOSE(5, 2),
    WPOSE(6, 3),  WPOSE(7, 3),  WPOSE(8, 3),  WPOSE(9, 3), WPOSE(10, 4),
    WPOSE(11, 4), WPOSE(12, 4), WPOSE(13, 4), WPOSE_END};
static u16 anim_1[] = {
    WPOSE(14, 5), WPOSE(15, 6), WPOSE(16, 6), WPOSE(17, 6), WPOSE(18, 6),
    WPOSE(19, 7), WPOSE(20, 7), WPOSE(21, 7), WPOSE(22, 7), WPOSE(31, 4),
    WPOSE(32, 4), WPOSE(33, 4), WPOSE(34, 4), WPOSE_END};
static u16 anim_2[] = {
    WPOSE(14, 5),  WPOSE(23, 8),  WPOSE(24, 9),  WPOSE(25, 8),  WPOSE(26, 9),
    WPOSE(27, 10), WPOSE(28, 10), WPOSE(29, 10), WPOSE(30, 10), WPOSE(31, 4),
    WPOSE(32, 4),  WPOSE(33, 4),  WPOSE(34, 4),  WPOSE_END};
static u16 anim_3[] = {
    WPOSE(35, 11), WPOSE(36, 12), WPOSE(37, 12), WPOSE(38, 12),
    WPOSE(39, 12), WPOSE(40, 13), WPOSE(41, 13), WPOSE(42, 13),
    WPOSE(43, 13), WPOSE(44, 4),  WPOSE_END};
static u16 anim_4[] = {
    WPOSE(45, 14), WPOSE(46, 15), WPOSE(47, 15), WPOSE(48, 15),
    WPOSE(49, 15), WPOSE(50, 16), WPOSE(51, 16), WPOSE(52, 16),
    WPOSE(53, 16), WPOSE(62, 4),  WPOSE_END};
static u16 anim_5[] = {
    WPOSE(45, 14), WPOSE(54, 17), WPOSE(55, 17), WPOSE(56, 17),
    WPOSE(57, 17), WPOSE(58, 18), WPOSE(59, 18), WPOSE(60, 18),
    WPOSE(61, 18), WPOSE(62, 4),  WPOSE_END};
static AnimationFrame D_131000_8017AF40[] = {
    POSE(2, 0x23, 0), POSE(1, 0x24, 0), POSE(1, 0x25, 0), POSE(1, 0x26, 0),
    POSE(1, 0x27, 0), POSE(1, 0x28, 0), POSE(1, 0x29, 0), POSE(1, 0x2A, 0),
    POSE(2, 0x2B, 0), POSE(4, 0x2C, 0), POSE(2, 0x23, 0), POSE(1, 0x24, 0),
    POSE(1, 0x25, 0), POSE(1, 0x26, 0), POSE(1, 0x27, 0), POSE(1, 0x28, 0),
    POSE(1, 0x29, 0), POSE(1, 0x2A, 0), POSE(2, 0x2B, 0), POSE(8, 0x2C, 0),
    POSE_END};
static s8 hitboxes[][4] = {
    {0, 0, 0, 0},     {4, -23, 8, 5},   {30, -17, 35, 8}, {30, -14, 18, 4},
    {-32, -31, 0, 0}, {-4, -6, 8, 5},   {22, 0, 35, 8},   {22, 3, 18, 4},
    {29, 22, 13, 11}, {12, 7, 19, 12},  {14, 14, 18, 4},  {1, -25, 8, 5},
    {27, -19, 35, 8}, {27, -16, 18, 4}, {-8, -26, 8, 5},  {24, -17, 35, 8},
    {24, -14, 18, 4}, {23, 0, 27, 14},  {18, 2, 21, 11},  {29, -14, 34, 4},
    {21, 3, 34, 4},   {28, 21, 12, 10}, {26, -16, 34, 4}, {23, -14, 34, 4},
    {22, 3, 26, 10}};
static u16* animGroup0[] = {
    anim_0, anim_0, anim_1, anim_2, anim_3, anim_4, anim_5};
static WeaponAnimation weaponAnims[] = {
    {animGroup0, hitboxes, 0, SFX_ALUCARD_SWORD_SWISH, 0x41, 0x04},
    {animGroup0, hitboxes, 0, SFX_ALUCARD_SWORD_SWISH, 0x41, 0x04},
    {animGroup0, hitboxes, 0, SFX_ALUCARD_SWORD_SWISH, 0x41, 0x04}};
static u16* g_WeaponCluts[] = {pal_0, pal_1, pal_2, pal_3, pal_4};
static s32 g_HandId = HAND_ID;

#include "shared.h"

static void EntityWeaponAttack(Entity* self) {
    s8 animIndex = (self->params & 0x7FFF) >> 8;
    WeaponAnimation* anim = &weaponAnims[animIndex];
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
        self->primIndex = g_api.AllocPrimitives(PRIM_TILE, 16);
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
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = PAL_UNK_110;
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
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        SetWeaponProperties(self, 0);
        self->step++;
    }
    self->ext.weapon.anim = PLAYER.ext.player.anim - anim->frameStart;
    if (PLAYER.poseTimer == 1 && PLAYER.pose == anim->soundFrame) {
        g_api.PlaySfx(anim->soundId);
    }
    if (g_api.UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }
    if (PLAYER.poseTimer == 1 && PLAYER.pose == 3) {
        flag = 1;
    }
    self->drawFlags = PLAYER.drawFlags;
    self->scaleY = PLAYER.scaleY;
    self->rotPivotY = PLAYER.rotPivotY;

    modifierY = 0;
    if (PLAYER.drawFlags & ENTITY_SCALEY) {
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
        self->palette = PAL_FLAG(PAL_ALUCARD);
        self->zPriority = PLAYER.zPriority;
        self->facingLeft = PLAYER.facingLeft;
        // this toggles the high bit, but xor does not
        // produce the same set of instructions
        self->animCurFrame = PLAYER.animCurFrame + ANIM_FRAME_LOAD;
        self->animSet = ANIMSET_DRA(1);
        self->blendMode = BLEND_TRANSP;
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
        if (PLAYER.pose == 5 && PLAYER.poseTimer == 1) {
            self->facingLeft++;
            self->facingLeft &= 1;
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(62, 0), 0);
            self->step++;
        }
        break;

    case 2:
        self->blendMode = BLEND_NO;
        self->animCurFrame = PLAYER.animCurFrame + ANIM_FRAME_LOAD;
        if (PLAYER.pose == 0xE) {
            self->facingLeft++;
            self->facingLeft &= 1;
            SetSpeedX(FIX(-13.0));
            self->velocityY = FIX(1.0 / 8.0);
            self->step++;
        }
        break;

    case 3:
        self->blendMode = BLEND_TRANSP;
        self->animCurFrame = PLAYER.animCurFrame + ANIM_FRAME_LOAD;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        DecelerateX(FIX(15.0 / 32.0));
        if (PLAYER.pose == 19) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    self->drawFlags = PLAYER.drawFlags;
    self->scaleY = PLAYER.scaleY;
    self->rotPivotY = PLAYER.rotPivotY;
}

static void func_ptr_80170008(Entity* self) {
    if (self->step == 0) {
        self->anim = D_131000_8017AF40;
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = PAL_UNK_110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_100000 |
                      FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        self->zPriority = PLAYER.zPriority - 2;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.weapon.parent->enemyId;
        self->hitboxOffX = 0x1B;
        self->hitboxOffY = -0x13;
        self->hitboxWidth = 0x23;
        self->step++;
    } else {
        if ((self->pose == 1) || (self->pose == 0xB)) {
            g_api.PlaySfx(SFX_ALUCARD_SWORD_SWISH);
        }
        if ((u16)self->animCurFrame - 0x24U < 6) {
            self->hitboxHeight = 8;
        } else {
            self->hitboxHeight = 0;
        }
        if (self->poseTimer < 0) {
            DestroyEntity(self);
            return;
        }
    }
    self->drawFlags = PLAYER.drawFlags;
    self->scaleY = PLAYER.scaleY;
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
