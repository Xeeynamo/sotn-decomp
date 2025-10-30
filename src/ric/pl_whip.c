// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"

static Point16 D_801559AC[] = {
    {7, -2}, {16, -2}, {5, -18}, {-14, -18}, {-23, -6}, {-24, -6}, {-25, -6}};
static Point16 D_801559C8[] = {
    {7, 11}, {16, 11}, {5, -5}, {-14, -5}, {-23, 11}, {-24, 11}, {-25, 11}};
static Point16 D_801559E4[] = {
    {-15, -4}, {-14, -14}, {-9, -6}, {-18, -6}, {-9, 2},
    {-11, -9}, {-16, -10}, {-7, 0},  {-14, 0}};
static s16 D_80155A08[] = {15, 14, 18, 9, 9, 16, 11, 14, 7, 0};
static Point16 D_80155A1C[] = {
    {-15, 9}, {-14, -1}, {-9, 7},  {-18, 9}, {-9, 15},
    {-11, 4}, {-16, 3},  {-7, 13}, {-14, 13}};
static s16 D_80155A40[] = {15, 14, 18, 9, 9, 16, 11, 14, 7};
static Point16 D_80155A54[] = {
    {-15, -6},  {-14, -16}, {-9, -8}, {-18, -6}, {-9, 0},
    {-11, -11}, {-16, -12}, {-7, -2}, {-14, -2}};
static s16 D_80155A78[] = {15, 14, 18, 9, 9, 16, 11, 14, 7};
static s16 unused[] = {1, 0, 5, 0, 2, 0, 7, 0, 4, 0, 8, 0, 3, 0, 6, 0};
static Point32 D_80155AAC[] = {
    {FIX(4), FIX(2)},  {FIX(4), FIX(-2.5)}, {FIX(16), FIX(0)},
    {FIX(16), FIX(0)}, {FIX(-20), FIX(0)},  {FIX(-32), FIX(0)},
    {FIX(-52), FIX(0)}};
static Point32 D_80155AE4[] = {
    {FIX(0), FIX(0)},       {FIX(-2.5), FIX(0)},  {FIX(-0.125), FIX(2)},
    {FIX(-0.125), FIX(-2)}, {FIX(0.5), FIX(0)},   {FIX(-2), FIX(1.5)},
    {FIX(-2), FIX(-1.5)},   {FIX(0.5), FIX(1.5)}, {FIX(0.5), FIX(-1.5)}};
static s32 D_80155B2C_0[] = {1, 1, 5, 6, 0, 1, 1, 0, 0};
static s32 D_80155B2C_1[] = {2, 5, 2, 0, 7, 2, 0, 2, 0};
static s32 D_80155B2C_2[] = {3, 6, 0, 3, 8, 0, 3, 0, 3};
static s32 D_80155B2C_3[] = {4, 0, 7, 8, 4, 0, 0, 4, 4};
static s32 D_80155B2C_4[] = {5, 5, 5, 0, 0, 5, 1, 2, 0};
static s32 D_80155B2C_5[] = {6, 6, 0, 6, 0, 1, 6, 0, 3};
static s32 D_80155B2C_6[] = {7, 0, 7, 0, 7, 1, 0, 7, 4};
static s32 D_80155B2C_7[] = {8, 0, 0, 8, 8, 4, 3, 7, 8};
#if defined(VERSION_PSP)
extern s32 D_80155B2C_8[];
#else
static s32 D_80155B2C_8[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
#endif
static u16 D_80155C70[] = {0x8139, 0x813A, 0x813B};
static s16 D_80155C78[] = {
    16, 14, 12, 10, 8, 6, 4, 2, 15, 13, 11, 9, 7, 5, 3, 255};
#if defined(VERSION_PSP)
static s16 D_80155C98[] = {
#else
static u16 D_80155C98[] = {
#endif
    0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11, 13, 15};
#if defined(VERSION_PSP)
extern u32 D_80175080;
extern s32 D_80175084;
#else
static u32 D_80175080;
static s32 D_80175084;
#endif
void RicEntityWhip(Entity* self) {
    byte stackpad[40];
    s16 sp4E;
    s16 radius;
    s32 sp44;
    s32 sp40;
    s32 prevX;
    s32 prevY;
    s16 sp4A;
    s32 aimPath;
    s32 newY;
    s16 angle;
    s32 diffY;
    s16 psp_s4;
    s32 diffX;
    s32 newX;
    Primitive* prim;
    s32 psp_s0;

    psp_s4 = self->params & 0xFF;
    sp4A = self->params & 0xFF00;
    if (psp_s4 == 0) {
        if (self->ext.whip.unkA6) {
            self->ext.whip.unkA6--;
        }
    }
    if (g_Player.unk46 == 0) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 2 && g_Player.unk46 == 2) {
        self->step = 1;
        self->velocityX = 0;
        self->velocityY = 0;
        self->palette = PAL_FLAG(0x148);
        if (PLAYER.facingLeft == 0) {
            self->ext.whip.unk88 = 2;
        } else {
            self->ext.whip.unk88 = 3;
        }
        self->ext.whip.unk8C = 0x600;
    }
    if (self->step) {
        diffX = self->posX.val - self->ext.whip.curX;
        diffY = self->posY.val - self->ext.whip.curY;
        self->ext.whip.prevX += diffX;
        self->ext.whip.prevY += diffY;
    }
    aimPath = g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    // @bug: up+down or left+right are not handled, psp_s0 will be undefined.
    // this never happens due to physical limitatitions of the PS controller.
    ASSERT(aimPath != (PAD_UP | PAD_DOWN));
    ASSERT(aimPath != (PAD_LEFT | PAD_RIGHT));
    if (aimPath == PAD_UP) {
        psp_s0 = D_80155B2C_0[self->ext.whip.unk88];
    }
    if (aimPath == PAD_DOWN) {
        psp_s0 = D_80155B2C_3[self->ext.whip.unk88];
    }
    if (aimPath == PAD_RIGHT) {
        psp_s0 = D_80155B2C_1[self->ext.whip.unk88];
    }
    if (aimPath == PAD_LEFT) {
        psp_s0 = D_80155B2C_2[self->ext.whip.unk88];
    }
    if (aimPath == (PAD_UP + PAD_RIGHT)) {
        psp_s0 = D_80155B2C_4[self->ext.whip.unk88];
    }
    if (aimPath == (PAD_UP + PAD_LEFT)) {
        psp_s0 = D_80155B2C_5[self->ext.whip.unk88];
    }
    if (aimPath == (PAD_DOWN + PAD_RIGHT)) {
        psp_s0 = D_80155B2C_6[self->ext.whip.unk88];
    }
    if (aimPath == (PAD_DOWN + PAD_LEFT)) {
        psp_s0 = D_80155B2C_7[self->ext.whip.unk88];
    }
    if (aimPath == 0) {
        psp_s0 = D_80155B2C_8[self->ext.whip.unk88];
    }

    self->ext.whip.unk86 = 0;
    if (psp_s4 == 0) {
        if (self->step == 1) {
            if (PLAYER.step == PL_S_CROUCH) {
                if (PLAYER.facingLeft == 0) {
                    newX = D_80155A40[psp_s0];
                } else {
                    newX = D_80155A1C[psp_s0].x;
                }
                newY = D_80155A1C[psp_s0].y;
            } else if (PLAYER.step == PL_S_STAND) {
                if (PLAYER.facingLeft == 0) {
                    newX = D_80155A08[psp_s0];
                } else {
                    newX = D_801559E4[psp_s0].x;
                }
                newY = D_801559E4[psp_s0].y;
            } else {
                if (PLAYER.facingLeft == 0) {
                    newX = D_80155A78[psp_s0];
                } else {
                    newX = D_80155A54[psp_s0].x;
                }
                newY = D_801559E4[psp_s0].y;
            }
        } else {
            if (PLAYER.step == PL_S_CROUCH) {
                newX = D_801559C8[PLAYER.pose].x;
                newY = D_801559C8[PLAYER.pose].y;
            } else {
                newX = D_801559AC[PLAYER.pose].x;
                newY = D_801559AC[PLAYER.pose].y;
            }
            if (PLAYER.facingLeft == 0) {
                newX = -newX;
            }
        }
        newX <<= 16;
        newY <<= 16;
        newX += PLAYER.posX.val;
        newY += PLAYER.posY.val;
    } else {
        self--;
        newX = self->posX.val;
        newY = self->posY.val;
        self++;
    }
    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_OVL(18);
        self->animCurFrame = 0x1D;
        self->animCurFrame = 0x1E;
        self->palette = PAL_FLAG(0x138);
        self->unk5A = 0x46;
        if (psp_s4 < 8) {
            self->hitboxWidth = 3;
            self->hitboxHeight = 3;
            self->hitboxOffX = 0;
            self->hitboxOffY = 0;
            self->ext.whip.unkB0 = PL_W_WHIP;
            RicSetSubweaponParams(self);
        }
        if (psp_s4 == 0) {
            self->zPriority = PLAYER.zPriority - 2;
        }
        if (psp_s4 == 7) {
            self->animCurFrame = 0x1F;
            self->hitboxWidth++;
            self->hitboxHeight++;
        }
        self->zPriority = PLAYER.zPriority + 4;
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_PLAYER_LOCKED |
                      FLAG_UNK_20000 | FLAG_UNK_10000;
        self->posX.val = newX;
        self->posY.val = newY;
        self->ext.whip.prevX = self->posX.val;
        self->ext.whip.prevY = self->posY.val;
        self->ext.whip.curX = self->ext.whip.prevX;
        self->ext.whip.curY = self->ext.whip.prevY;
        self->ext.whip.unk8C = 0x500;
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (self->primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[self->primIndex];
            prim->r0 = 0x7F;
            prim->g0 = 0x7F;
            prim->b0 = 0x7F;
            prim->r1 = 0x1F;
            prim->g1 = 0x1F;
            prim->b1 = 0x1F;
            prim->priority = PLAYER.zPriority + 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        }
        self->step = 2;
        RicEntityWhip(self);
        break;
    case 1:
        if (sp4A == 0) {
            if (self->palette < 0x8148 && self->palette >= 0x8140) {
                if (self->ext.whip.unkA4) {
                    self->ext.whip.unkA4--;
                } else {
                    self->palette++;
                }
            }
        } else if (self->ext.whip.unkA4) {
            if (!(psp_s4 & 1)) {
                RicCreateEntFactoryFromEntity(self, BP_20, 0);
                self->ext.whip.unkA4 = 0;
            }
        }
        if (psp_s4 < 8) {
            if (self->ext.whip.unk84) {
                if (--self->ext.whip.unk84 == 0) {
                    if (self->velocityY < 0) {
                        self->velocityY = 0;
                    }
                    self->velocityX = 0;
                }
            } else {
                self->velocityX = self->velocityX * 3 / 4;
            }
            if (self->ext.whip.unk88 == psp_s0) {
                break;
            }
            if (psp_s4 == 0) {
                if (sp4A) {
                    if (self->ext.whip.unkA6 == 0) {
                        g_api.PlaySfx(SFX_RIC_WHIP_RATTLE_A);
                        self->ext.whip.unkA6 = 0x20;
                    }
                } else {
                    if (self->ext.whip.unkA6 == 0) {
                        g_api.PlaySfx(SFX_RIC_WHIP_RATTLE_A);
                        self->ext.whip.unkA6 = 0x20;
                    }
                }
                if (sp4A == 0) {
                    RicCreateEntFactoryFromEntity(self, FACTORY(BP_18, 0), 0);
                } else {
                    RicCreateEntFactoryFromEntity(self, FACTORY(BP_18, 1), 0);
                }
            }

            self->ext.whip.unk84 = 6;
            if (psp_s0 == 0) {
                if (PLAYER.facingLeft == 0) {
                    diffX = D_80155A08[0];
                } else {
                    diffX = D_801559E4[0].x;
                }
                diffY = D_801559E4[0].y;
                diffX += PLAYER.posX.i.hi;
                diffY += PLAYER.posY.i.hi;
                diffX <<= 16;
                diffY <<= 16;

                diffX -= self->posX.val;
                diffY -= self->posY.val;
                angle = ratan2(-diffY, diffX);
                radius = 0x80;
                self->velocityX = (radius * rcos(angle)) >> 4;
                self->velocityY = -(radius * rsin(angle)) >> 4;
            } else {
                self->velocityY = D_80155AE4[psp_s0].x;
                self->velocityX = D_80155AE4[psp_s0].y;
            }
            self->ext.whip.unk88 = psp_s0;
        }
        break;
    case 2:
        if (psp_s4 > 7) {
            if (self->flags & FLAG_HAS_PRIMS) {
                if (PLAYER.pose == 5) {
                    g_api.FreePrimitives(self->primIndex);
                    self->flags &= ~FLAG_HAS_PRIMS;
                }
            }
            if (PLAYER.pose == 6) {
                if (PLAYER.poseTimer > 14) {
                    self->palette = PAL_FLAG(0x138);
                } else if (PLAYER.poseTimer == 0) {
                    self->palette = PAL_FLAG(0x138);
                } else if ((PLAYER.poseTimer == 11 || PLAYER.poseTimer == 12) ||
                           (PLAYER.poseTimer == 13 || PLAYER.poseTimer == 14)) {
                    self->palette = PAL_FLAG(0x13C);
                } else {
// poseTimer can be -1 apparently.
// todo this should read the previous element out of bounds?
#ifdef VERSION_PC
                    if (PLAYER.poseTimer >= 0) {
                        self->palette =
                            D_80155C70[PLAYER.poseTimer % LEN(D_80155C70)];
                    }
#else
                    self->palette =
                        D_80155C70[PLAYER.poseTimer % LEN(D_80155C70)];
#endif
                }
            }
        } else {
            self->velocityX = D_80155AAC[PLAYER.pose].x;
            self->velocityY = D_80155AAC[PLAYER.pose].y;
            switch (PLAYER.pose) {
            case 0:
                radius = 0x800;
                angle = (rand() & 0x3FF) - 0x200;
                self->velocityX = (radius * rcos(angle)) >> 4;
                self->velocityY = -(radius * rsin(angle)) >> 4;
                break;
            case 1:
                radius = 0x800;
                angle = (rand() & 0x3FF) - 0x400;
                self->velocityX = (radius * rcos(angle)) >> 4;
                self->velocityY = -(radius * rsin(angle)) >> 3;
                self->ext.whip.unk8C = 0x600;
                break;
            case 4:
                self->ext.whip.unk8C = 0x3C0;
                if (PLAYER.poseTimer == 1) {
                    self->velocityX = FIX(-8);
                }
                break;
            case 5:
                self->ext.whip.unk8C += 0xC0;
                if (self->flags & FLAG_HAS_PRIMS) {
                    g_api.FreePrimitives(self->primIndex);
                    self->flags &= ~FLAG_HAS_PRIMS;
                }
                break;
            case 6:
                if (sp4A) {
                    if (PLAYER.poseTimer == D_80155C78[psp_s4]) {
                        RicCreateEntFactoryFromEntity(self, BP_20, 0);
                    }
                }
                if (psp_s4 == (0x10 - PLAYER.poseTimer)) {
                    self->ext.whip.unk8C = 0x600;
                }
                // This very well might be a switch
                if (PLAYER.poseTimer > 14) {
                    self->palette = PAL_FLAG(0x138);
                } else if (PLAYER.poseTimer == 0) {
                    self->palette = PAL_FLAG(0x138);
                } else if (PLAYER.poseTimer == 11 || PLAYER.poseTimer == 12 ||
                           PLAYER.poseTimer == 13 || PLAYER.poseTimer == 14) {
                    self->palette = PAL_FLAG(0x13C);
                } else {
// poseTimer can be -1 apparently.
// todo this should read the previous element out of bounds?
#ifdef VERSION_PC
                    if (PLAYER.poseTimer >= 0) {
                        self->palette = D_80155C70[PLAYER.poseTimer % 3];
                    }
#else
                    self->palette = D_80155C70[PLAYER.poseTimer % 3];
#endif
                }
                break;
            }
            if (PLAYER.facingLeft == 0) {
                self->velocityX = -self->velocityX;
            }
            self->velocityX = self->velocityX / 2;
            self->velocityY = self->velocityY / 2;
        }
        break;
    }
    sp4E = self->ext.whip.unk8C;
    prevX = self->posX.val;
    prevY = self->posY.val;
    if (psp_s4 == 0) {
        self->posX.val = newX;
        self->posY.val = newY;
    } else if (psp_s4 > 7) {
        diffX = (self - 8)->posX.val;
        diffY = (self - 8)->posY.val;
        sp44 = (self - 7)->posX.val;
        sp40 = (self - 7)->posY.val;
        self->posX.val = (diffX + sp44) / 2;
        self->posY.val = (diffY + sp40) / 2;
    } else {
        sp44 = self->posX.val - self->ext.whip.prevX;
        sp40 = self->posY.val - self->ext.whip.prevY;
        if (self->step == 1) {
            if (self->velocityY < FIX(0.5)) {
                self->posX.val += sp44 * 16 / 16;
                self->posY.val += sp40 * 16 / 16;
            }
            if (self->velocityY >= FIX(0.5) && self->velocityY < FIX(1.25)) {
                self->posX.val += sp44 * 15 / 16;
                self->posY.val += sp40 * 15 / 16;
            }
            if (self->velocityY >= FIX(1.25) || self->velocityY < 0) {
                self->posX.val += sp44 * 13 / 16;
                self->posY.val += sp40 * 13 / 16;
            }
        } else {
            self->posX.val += sp44 * 3 / 4;
            self->posY.val += sp40 * 3 / 4;
        }
        if (self->velocityY < FIX(8) || self->velocityY < 0) {
            self->velocityY += 0xA00;
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        diffY = self->posY.val - newY;
        diffX = self->posX.val - newX;
        if (((sp4E * sp4E) >> 0x10) < ((diffY * (diffY >> 0x10)) >> 0x10) +
                                          ((diffX * (diffX >> 0x10)) >> 0x10)) {
            angle = ratan2(-diffY, diffX);
            diffX = (rcos(angle) * sp4E) >> 4;
            diffY = -(rsin(angle) * sp4E) >> 4;
            self->posX.val = newX + diffX;
            self->posY.val = newY + diffY;
        }
    }
    self->ext.whip.prevX = prevX;
    self->ext.whip.prevY = prevY;
    self->ext.whip.curX = self->posX.val;
    self->ext.whip.curY = self->posY.val;
    self->ext.whip.unkA0 = sp40;
    if (psp_s4 == 0) {
        D_80175080 = psp_s0;
        D_80175084 = self->ext.whip.unk88;
    }
    if (self->primIndex != -1 && (self->flags & FLAG_HAS_PRIMS)) {
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        prim->x1 = self->ext.whip.prevX >> 0x10;
        prim->y1 = self->ext.whip.prevY >> 0x10;
        if (PLAYER.pose == 4) {
            prim->priority = PLAYER.zPriority + 4;
        } else {
            prim->priority = PLAYER.zPriority + 2;
        }
    }
    if (sp4A) {
        if (psp_s4 != 7) {
            angle = (((g_GameTimer >> 2) & 7) + D_80155C98[psp_s4]) * 512;
            self->opacity = (rsin(angle) >> 6) + 0x80;
            self->drawFlags |= DRAW_HIDE;
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        }
        self->palette = PAL_FLAG(0x160);
    }
}

static u16 D_80155CB8[] = {10, 11, 13, 17, 15, 12, 18, 14, 16};
static u16 D_80155CCC[] = {10, 11, 17, 13, 15, 18, 12, 16, 14};
static u16 D_80155CE0[] = {1, 2, 4, 8, 6, 3, 9, 5, 7};
static u16 D_80155CF4[] = {1, 2, 8, 4, 6, 9, 3, 7, 5};
static u16 D_80155D08[] = {19, 20, 22, 26, 24, 21, 27, 23, 25};
static u16 D_80155D1C[] = {19, 20, 26, 22, 24, 27, 21, 25, 23};
void RicEntityArmBrandishWhip(Entity* entity) {
    if (g_Player.unk46 == 0) {
        DestroyEntity(entity);
        return;
    }
    entity->facingLeft = PLAYER.facingLeft;
    if (entity->step == 0) {
        entity->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
                        FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_10000;
        entity->animSet = ANIMSET_OVL(18);
        entity->unk5A = 0x46;
        entity->palette = PAL_FLAG(0x120);
        entity->zPriority = PLAYER.zPriority + 2;
    }
    if (PLAYER.step == PL_S_CROUCH) {
        if (PLAYER.facingLeft) {
            entity->animCurFrame = D_80155CCC[D_80175080];
        } else {
            entity->animCurFrame = D_80155CB8[D_80175080];
        }
    } else if (PLAYER.step == 0) {
        if (PLAYER.facingLeft) {
            entity->animCurFrame = D_80155CF4[D_80175080];
        } else {
            entity->animCurFrame = D_80155CE0[D_80175080];
        }
    } else if (PLAYER.facingLeft) {
        entity->animCurFrame = D_80155D1C[D_80175080];
    } else {
        entity->animCurFrame = D_80155D08[D_80175080];
    }
    entity->posX.val = PLAYER.posX.val;
    entity->posY.val = PLAYER.posY.val;
}

static s16 D_80155D30[] = {0x10, 0x18, 0x11, 0x19, 0x12, 0x1A, 0x13, 0x1B,
                           0x14, 0x1C, 0x15, 0x1D, 0x16, 0x1E, 0x17};
static u16 unused_2[] = {0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x02, 0x04, 0x00};
void func_80167964(Entity* entity) {
    if (g_Player.unk46 == 0) {
        DestroyEntity(entity);
        return;
    }
    if (entity->step == 0) {
        entity->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
                        FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_10000;
    }
    if (!(entity->params & 0xFF00)) {
        g_Entities[D_80155D30[entity->poseTimer]].palette = PAL_FLAG(0x140);
    }
    g_Entities[D_80155D30[entity->poseTimer]].ext.player.unkA4 = 4;
    entity->poseTimer++;
    if (entity->poseTimer == 15) {
        DestroyEntity(entity);
    }
}
