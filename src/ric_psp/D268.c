// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../ric/ric.h"
#include <player.h>

#include "../rebound_stone.h"

void RicEntitySubwpnReboundStone(Entity* self) {
    s16 playerX;
    s16 playerY;
    Collider collider;
    s32 speed;
    s32 currX;
    s32 currY;
    s32 collX;
    s32 collY;
    s32 deltaX;
    s32 deltaY;
    s32 i;
    s32 colliderFlags;
    PrimLineG2* prim;

    speed = 0x400;
    self->ext.reboundStone.unk82 = 0;
    playerX = self->posX.i.hi;
    playerY = self->posY.i.hi;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 16);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->posY.i.hi -= 0x10;
        playerY = self->posY.i.hi;
        for (prim = (PrimLineG2*)&g_PrimBuf[self->primIndex], i = 0;
             prim != NULL; i++, prim = prim->next) {
            PGREY(prim, 0) = PGREY(prim, 1) = 0xFF;
            prim->priority = PLAYER.zPriority + 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            if (i != 0) {
                prim->drawMode |= DRAW_HIDE;
            }
            prim->x0 = prim->x1 = playerX;
            prim->y0 = prim->y1 = playerY;
            prim->timer = 20;
        }
        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        self->zPriority = PLAYER.zPriority + 2;

        if (PLAYER.facingLeft) {
            self->ext.reboundStone.stoneAngle = 0x980;
        } else {
            self->ext.reboundStone.stoneAngle = 0xE80;
        }
        self->ext.reboundStone.stoneAngle += (rand() & 0x7F) - 0x40;

        self->ext.reboundStone.lifeTimer = 0x40;
        self->ext.reboundStone.subweaponId = PL_W_REBNDSTONE;
        RicSetSubweaponParams(self);
        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->ext.reboundStone.unk84 = 4;
        }
        self->step++;
        g_api.PlaySfx(SFX_WEAPON_SWISH_C);
        break;
    case 1:
        deltaX = rcos(self->ext.reboundStone.stoneAngle) * 0x10;
        deltaY = -rsin(self->ext.reboundStone.stoneAngle) * 0x10;
        currX = self->posX.val;
        currY = self->posY.val;
        if (!self->ext.reboundStone.unk84) {
            for (i = 0; i < 6; i++) {
                collX = FIX_TO_I(currX);
                collY = FIX_TO_I(currY + deltaY);
                g_api.CheckCollision(collX, collY, &collider, 0);
                colliderFlags =
                    collider.effects &
                    (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                     EFFECT_UNK_1000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                     EFFECT_SOLID);
                if (colliderFlags & EFFECT_SOLID) {
                    colliderFlags &= 0xFF00;
                    if (deltaY > 0) {
                        if ((colliderFlags == 0) ||
                            (colliderFlags & EFFECT_UNK_0800)) {
                            ReboundStoneBounce1(0x800);
                        }
                        if (colliderFlags == EFFECT_UNK_8000) {
                            ReboundStoneBounce2(0x200);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_8000 + EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0x12E);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_8000 + EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0xA0);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_8000 + EFFECT_UNK_4000) {
                            ReboundStoneBounce2(0x600);
                        }
                        if (colliderFlags == EFFECT_UNK_8000 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0x6D2);
                        }
                        if (colliderFlags == EFFECT_UNK_8000 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0x760);
                        }
                    }
                    if (deltaY < 0) {
                        if ((colliderFlags == 0) ||
                            (colliderFlags & EFFECT_UNK_8000)) {
                            ReboundStoneBounce1(0x800);
                        }
                        if (colliderFlags == EFFECT_UNK_0800) {
                            ReboundStoneBounce2(0xE00);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_0800 + EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0xED2);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_0800 + EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0xF60);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_0800 + EFFECT_UNK_4000) {
                            ReboundStoneBounce2(0xA00);
                        }
                        if (colliderFlags == EFFECT_UNK_0800 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0x92E);
                        }
                        if (colliderFlags == EFFECT_UNK_0800 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0x8A0);
                        }
                    }
                }
                collY = FIX_TO_I(currY);
                collX = FIX_TO_I(currX + deltaX);
                g_api.CheckCollision(collX, collY, &collider, 0);
                colliderFlags =
                    collider.effects &
                    (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                     EFFECT_UNK_1000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                     EFFECT_SOLID);
                if (colliderFlags & EFFECT_SOLID) {
                    colliderFlags &= 0xFF00;
                    // Cases when traveling right
                    if (deltaX > 0) {
                        if ((colliderFlags == 0) ||
                            TEST_BITS(colliderFlags, 0x4800) ||
                            TEST_BITS(colliderFlags, 0xC000)) {
                            ReboundStoneBounce1(0x400);
                        }
                        if (colliderFlags == EFFECT_UNK_0800) {
                            ReboundStoneBounce2(0xE00);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_0800 + EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0xED2);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_0800 + EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0xF60);
                        }
                        if (colliderFlags == EFFECT_UNK_8000) {
                            ReboundStoneBounce2(0x200);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_8000 + EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0x12E);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_8000 + EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0xA0);
                        }
                    }
                    // Cases when traveling left
                    if (deltaX < 0) {
                        if ((colliderFlags == 0) ||
                            ((colliderFlags & 0x4800) == 0x800) ||
                            ((colliderFlags & 0xC000) == 0x8000)) {
                            ReboundStoneBounce1(0x400);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_0800 + EFFECT_UNK_4000) {
                            ReboundStoneBounce2(0xA00);
                        }
                        if (colliderFlags == EFFECT_UNK_0800 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0x92E);
                        }
                        if (colliderFlags == EFFECT_UNK_0800 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0x8A0);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_8000 + EFFECT_UNK_4000) {
                            ReboundStoneBounce2(0x600);
                        }
                        if (colliderFlags == EFFECT_UNK_8000 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0x6D2);
                        }
                        if (colliderFlags == EFFECT_UNK_8000 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0x760);
                        }
                    }
                }
                if (self->ext.reboundStone.unk82) {
                    goto block_93;
                }
                currX += deltaX;
                currY += deltaY;
            }
        } else {
            self->ext.reboundStone.unk84--;
        }
    block_93:
        if (self->ext.reboundStone.unk82) {
            g_api.CreateEntFactoryFromEntity(self, FACTORY(BP_42, 2), 0);
            g_api.PlaySfx(SFX_UI_TINK);
        }
        if (self->posX.i.hi < -0x40 || self->posX.i.hi > 0x140 ||
            self->posY.i.hi < -0x40 || self->posY.i.hi > 0x140 ||
            self->ext.reboundStone.unk80 == 15) {
            self->step = 2;
        } else {
            deltaX =
                ((rcos(self->ext.reboundStone.stoneAngle) << 4) * speed) >> 8;
            self->posX.val += deltaX;
            deltaY =
                -((rsin(self->ext.reboundStone.stoneAngle) << 4) * speed) >> 8;
            self->posY.val += deltaY;
        }
        break;
    case 2:
        if (--self->ext.reboundStone.lifeTimer == 0) {
            DestroyEntity(self);
            return;
        }
        if (self->ext.reboundStone.lifeTimer == 0x20) {
            self->hitboxState = 0;
        }
        prim = (PrimLineG2*)&g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->timer = 0;
            prim = prim->next;
        }
        break;
    }

    prim = (PrimLineG2*)&g_PrimBuf[self->primIndex];
    i = 0;
    if (self->step == 2) {
        colliderFlags = 4;
    } else {
        colliderFlags = 2;
    }
    // cleaner to use previous 3 lines than to put them in the for's initializer
    for (; prim != NULL; i++, prim = prim->next) {
        if (self->ext.reboundStone.unk82) {
            if (i == self->ext.reboundStone.unk80) {
                prim->x0 = playerX;
                prim->y0 = playerY;
                prim->drawMode &= ~DRAW_HIDE;
            }
        }
        if (i == self->ext.reboundStone.unk80) {
            prim->x1 = self->posX.i.hi;
            prim->y1 = self->posY.i.hi;
        }
        if (!(prim->drawMode & DRAW_HIDE)) {
            if (prim->timer) {
                prim->timer--;
            } else {
                // again not colliderFlags, seems to control stone fading
                if (colliderFlags < prim->b1) {
                    prim->b1 -= colliderFlags;
                }
                PGREY(prim, 0) = PGREY(prim, 1);
            }
        }
    }
}

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", RicEntitySubwpnThrownVibhuti);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", func_pspeu_092B4688);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", RicEntitySubwpnAgunea);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", RicEntityAguneaHitEnemy);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", RicEntityVibhutiCrashCloud);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", RicEntityCrashVibhuti);

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", RicEntityCrashReboundStoneParticles);
// clang-format on

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", func_8016D9C4);

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", RicEntityCrashReboundStoneExplosion);
// clang-format on

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", RicEntityCrashReboundStone);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", RicEntityCrashBibleBeam);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", RicEntityCrashBible);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", func_8016F198);

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", RicEntityCrashStopwatchDoneSparkle);
// clang-format on

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", RicEntityStopwatchCrashLightning);
// clang-format on

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", RicEntityCrashStopwatch);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", GetAguneaLightningAngle);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", AguneaShuffleParams);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", RicEntityAguneaLightning);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", RicEntityAguneaCircle);

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", RicEntitySubwpnStopwatchCircle);
// clang-format on

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", RicEntitySubwpnStopwatch);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", RicEntitySubwpnBibleTrail);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/D268", RicEntitySubwpnBible);
