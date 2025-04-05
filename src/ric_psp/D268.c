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
                        if (!colliderFlags || colliderFlags & EFFECT_UNK_0800) {
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
                        if (!colliderFlags ||
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
                        if (!colliderFlags ||
                            (colliderFlags & 0x4800) == 0x800 ||
                            (colliderFlags & 0xC000) == 0x8000) {
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

// RIC entity #43. Blueprint 49. Subweapon 8. Vibhuti!
void RicEntitySubwpnThrownVibhuti(Entity* self) {
    Collider col;
    FakePrim* prim;
    s16 randomAngle;
    s16 x;
    s16 y;
    s16 temp; // used for multiple unrelated things
    s32 i;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.func_800EDB58(PRIM_TILE_ALT, 13);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->ext.subweapon.subweaponId = PL_W_VIBHUTI;
        RicSetSubweaponParams(self);
        self->hitboxWidth = self->hitboxHeight = 4;
        self->ext.subweapon.timer = 0x80;
        prim = (FakePrim*)&g_PrimBuf[self->primIndex];
        self->posY.i.hi -= 15;
        if (PLAYER.facingLeft) {
            self->posX.i.hi -= 13;
        } else {
            self->posX.i.hi += 13;
        }
        x = self->posX.i.hi;
        y = self->posY.i.hi;
        i = 0;
        while (true) {
            prim->drawMode = DRAW_UNK02;
            prim->priority = PLAYER.zPriority - 1;
            if (prim->next == NULL) {
                prim->drawMode &= ~DRAW_HIDE;
                prim->y0 = prim->x0 = prim->w = 0;
                break;
            }
            prim->posX.i.hi = x;
            prim->posY.i.hi = y;
            prim->posX.i.lo = prim->posY.i.lo = 0;
            randomAngle = (rand() & 0xFF) + 0x100;
            temp = (rand() & 0xFF) + 0x80;
            prim->velocityX.val = ((rcos(randomAngle) << 4) * temp >> 9);
            prim->velocityX.val += FIX(0.5);
            prim->velocityY.val = -((rsin(randomAngle) << 4) * temp >> 9);
            prim->velocityX.val = (prim->velocityX.val * 3) >> 1;
            if (self->facingLeft) {
                prim->velocityX.val = -prim->velocityX.val;
            }
            prim->posY.i.hi -= 4;
            prim->delay = 1;
            prim->x0 = prim->posX.i.hi;
            prim->y0 = prim->posY.i.hi;
            prim->r0 = 0xFF;
            prim->g0 = 0xFF;
            prim->b0 = 0xFF;
            prim->w = 2;
            prim->h = 2;
            i++;
            prim = prim->next;
        }
        g_api.PlaySfx(SFX_WEAPON_SWISH_C);
        self->step++;
        break;
    case 1:
        temp = 2;
        if (self->facingLeft) {
            temp = -temp;
        }
        if (--self->ext.subweapon.timer == 0) {
            DestroyEntity(self);
            return;
        }
        prim = (FakePrim*)&g_PrimBuf[self->primIndex];
        i = 0;
        while (true) {
            if (prim->next == NULL) {
                prim->drawMode &= ~DRAW_HIDE;
                prim->y0 = prim->x0 = prim->w = 0;
                break;
            }
            prim->posX.i.hi = prim->x0;
            prim->posY.i.hi = prim->y0;
            if (prim->delay) {
                if (prim->velocityX.val != 0) {
                    prim->posX.val += prim->velocityX.val;
                    g_api.CheckCollision(
                        prim->posX.i.hi + temp, prim->posY.i.hi, &col, 0);
                    if (col.effects & EFFECT_UNK_0002) {
                        prim->velocityX.val = 0;
                    }
                }
                prim->posY.val += prim->velocityY.val;
                prim->velocityY.val += FIX(12.0 / 128);
                if (prim->velocityY.val > FIX(4)) {
                    prim->velocityY.val = FIX(4);
                }
                if (prim->velocityY.val > 0) {
                    g_api.CheckCollision(
                        prim->posX.i.hi, prim->posY.i.hi, &col, 0);
                    if (col.effects & EFFECT_SOLID) {
                        prim->delay = 0;
                        prim->posY.i.hi += col.unk18;
                        prim->posY.i.hi -= (i % 3 + 1);
                        prim->w = prim->h = 3;
                    }
                }
            }
            if ((self->ext.subweapon.timer & 7) == i) {
                self->posX.i.hi = prim->posX.i.hi;
                self->posY.i.hi = prim->posY.i.hi;
                if (prim->drawMode & DRAW_HIDE) {
                    self->hitboxWidth = self->hitboxHeight = 0;
                } else {
                    self->hitboxWidth = self->hitboxHeight = 4;
                }
                if (prim->delay) {
                    self->hitboxOffY = 0;
                } else {
                    self->hitboxOffY = -6;
                }
            }
            if (self->hitFlags && ((self->ext.subweapon.timer + 1) & 7) == i) {
                prim->drawMode = DRAW_HIDE;
            }
            if (self->ext.subweapon.timer - 1 == i) {
                prim->drawMode = DRAW_HIDE;
            }
            i++;
            prim->x0 = prim->posX.i.hi;
            prim->y0 = prim->posY.i.hi;
            prim = prim->next;
        }
        self->hitFlags = 0;
        break;
    }
}

static u8 PrimDecreaseBrightness(Primitive* prim, u8 amount) {
    s32 i;
    s32 j;
    u8* colorPtr;   // points to an RGB color
    u8* channelPtr; // points to a single channel of that color
    u8 isEnd;

    isEnd = 0;
    colorPtr = &prim->r0;
    for (i = 0; i < 4; colorPtr += OFF(Primitive, r1) - OFF(Primitive, r0),
        i++) {
        for (j = 0; j < 3; j++) {
            channelPtr =
                &colorPtr[j]; // get the red, green, blue, or pad channel
            *channelPtr -= amount;

            if (*channelPtr < 16) {
                *channelPtr = 16;
            } else {
                isEnd |= 1;
            }
        }
    }
    return isEnd;
}

// RIC Entity #44. Blueprint 51. Subweapon 9. Agunea (non-crash). DRA
// blueprint 25. DRA entity 21.
void RicEntitySubwpnAgunea(Entity* self) {
    Primitive* prim;
    s32 heartCost;
    s16 tempX;
    s16 tempY;
    u32 heartBroachesWorn;

    if (g_Player.status & (PLAYER_STATUS_TRANSFORM | PLAYER_STATUS_UNK10000)) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        self->facingLeft = PLAYER.facingLeft;
        self->ext.agunea.subweaponId = PL_W_AGUNEA;
        RicSetSubweaponParams(self);
        self->hitboxWidth = self->hitboxHeight = 4;
        self->hitboxOffX = 4;
        self->hitboxOffY = 0;
        self->posY.i.hi = self->ext.agunea.unk82 =
            PLAYER.posY.i.hi + PLAYER.hitboxOffY - 8;
        self->posX.i.hi = self->ext.agunea.unk80 = PLAYER.posX.i.hi;
        prim = &g_PrimBuf[self->primIndex];
        prim->type = PRIM_LINE_G2;
        prim->priority = PLAYER.zPriority + 2;
        prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                         DRAW_TPAGE | DRAW_TRANSP;
        prim->r1 = 0x60;
        prim->g1 = 0;
        prim->b1 = 0x80;
        RicSetSpeedX(FIX(6));
        g_api.PlaySfx(SFX_WEAPON_SWISH_C);
        self->step++;
        break;
    case 1:
        self->posX.val += self->velocityX;
        if (self->posX.i.hi < -0x40 || self->posX.i.hi > 0x140 ||
            self->posY.i.hi < -0x20 || self->posY.i.hi > 0x120) {
            self->step = 2;
        }
        if (self->hitFlags) {
            self->ext.agunea.parent = self->unkB8;
            self->step = 3;
        }
        break;
    case 4:
        self->posX.i.hi = self->ext.agunea.parent->posX.i.hi;
        self->posY.i.hi = self->ext.agunea.parent->posY.i.hi;
        if (++self->ext.agunea.unk7C < 16) {
            break;
        }
        // Fallthrough
    case 2:
        prim = &g_PrimBuf[self->primIndex];
        if (prim->r1 < 5) {
            DestroyEntity(self);
            return;
        }
        break;
    case 3:
        if ((g_Player.padPressed & (PAD_UP + PAD_SQUARE)) !=
            (PAD_UP + PAD_SQUARE)) {
            self->step = 4;
        }
        if (!self->ext.agunea.parent->entityId) {
            self->step = 2;
            return;
        }
        if (self->ext.agunea.unk7C &&
            (self->ext.agunea.parent->hitPoints > 0x7000 ||
             !self->ext.agunea.parent->hitPoints ||
             !self->ext.agunea.parent->hitboxState)) {
            self->step = 2;
            return;
        }

        tempX = self->posX.i.hi = self->ext.agunea.parent->posX.i.hi;
        tempY = self->posY.i.hi = self->ext.agunea.parent->posY.i.hi;
        if ((self->ext.agunea.unk7C % 12) == 0) {
            self->posX.i.hi += (rand() & 0xF) - 8;
            self->posY.i.hi += (rand() & 0xF) - 8;
            if (g_Status.hearts >= 5) {
                g_Status.hearts -= 5;
                RicCreateEntFactoryFromEntity(self, BP_AGUNEA_HIT_ENEMY, 0);
                g_api.PlaySfx(SFX_THUNDER_B);
            } else if (self->ext.agunea.unk84 == 0) {
                RicCreateEntFactoryFromEntity(self, BP_AGUNEA_HIT_ENEMY, 0);
                g_api.PlaySfx(SFX_THUNDER_B);
                self->ext.agunea.unk84++;
            } else {
                self->step = 4;
            }
        }
        self->posX.i.hi = tempX;
        self->posY.i.hi = tempY;
        self->ext.agunea.unk7C++;
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    if (prim->r1 >= 4) {
        prim->r1 -= 4;
    }
    if (prim->g1 >= 4) {
        prim->g1 -= 4;
    }
    if (prim->b1 >= 4) {
        prim->b1 -= 4;
    }
    if (prim->b1 < 5) {
        prim->drawMode |= DRAW_HIDE;
    }
    prim->x0 = self->ext.agunea.unk80;
    prim->y0 = self->ext.agunea.unk82;
    prim->x1 = self->posX.i.hi;
    prim->y1 = self->posY.i.hi;
}

void RicEntityAguneaHitEnemy(Entity* self) {
    Entity* parent;
    Primitive* prim;
    Primitive* temp_s3;
    Primitive* var_a0;
    s16 arctan;
    s16 angle;
    s16 xOffset;
    s16 yOffset;
    s16 temp_s2;
    u8 var_s3;
    s32 i;
    u8 var_s8;

    parent = self->ext.et_801291C4.parent;
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = (PLAYER.posY.i.hi + PLAYER.hitboxOffY) - 8;
    if (self->ext.et_801291C4.parent->entityId != 0x2C) {
        switch (self->step) {
        case 0:
            DestroyEntity(self);
            return;
        case 1:
        case 2:
        case 4:
            self->step = 3;
        }
    }
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x28);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            break;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        self->facingLeft = PLAYER.facingLeft;
        self->ext.et_801291C4.unk84 = (rand() & 0x3FF) - 0x200;
        if (self->facingLeft) {
            // @bug: This should be assigned to something. As-is, does nothing.
            self->ext.et_801291C4.unk84 + 0x800;
        }
        self->ext.et_801291C4.unk84 &= 0xFFF;
        self->ext.et_801291C4.unk90 = (self->params >> 8) & 0xFF;
        prim = &g_PrimBuf[self->primIndex];
        self->ext.et_801291C4.prim1 = prim;
        self->ext.et_801291C4.prim2 = prim;
        for (i = 0; prim != NULL;) {
            prim->tpage = 0x1A;
            prim->clut = 0x194;
            prim->u0 = prim->u1 = i * 0x10 + 0x90;
            prim->u2 = prim->u3 = prim->u0 + 0x10;
            prim->v0 = prim->v2 = 0xD0;
            prim->v1 = prim->v3 = 0xC0;
            prim->x0 = self->posX.i.hi;
            prim->y0 = self->posY.i.hi;
            prim->x2 = self->posX.i.hi;
            prim->y2 = self->posX.i.hi;
            prim->r0 = prim->g0 = prim->b0 = 0xF0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            i++;
            if (i > 5) {
                i = 0;
            }
        }
        prim = self->ext.et_801291C4.prim1;
        prim->x0 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        prim->x1 = prim->x0;
        prim->y1 = prim->y1 - 0x10;
        prim->x2 = self->posX.i.hi;
        prim->y2 = self->posY.i.hi;
        prim->x3 = prim->x2;
        prim->y3 = prim->y2 - 0x10;
        self->ext.et_801291C4.prim2 = prim;
        while (prim != NULL) {
            prim->clut = 0x194;
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.et_801291C4.unk88 = 0;
        self->step++;
        break;
    case 1:
        for (i = 0; i < 2; i++) {
            prim = self->ext.et_801291C4.prim2;
            temp_s2 = self->ext.et_801291C4.unk84;
            xOffset = parent->posX.i.hi - prim->x2;
            yOffset = parent->posY.i.hi - prim->y2;
            if (abs(xOffset) < 8 && abs(yOffset) < 8) {
                self->step++;
                break;
            }
            if (abs(xOffset) < 0x40 && abs(yOffset) < 0x40) {
                var_s3 = 1;
            } else {
                var_s3 = 0;
            }
            if (!self->ext.et_801291C4.unk88) {
                self->ext.et_801291C4.unk88 = 4;
                if (var_s3) {
                    self->ext.et_801291C4.unk88 = 2;
                }
                arctan = ratan2(-yOffset, xOffset);
                angle = arctan - temp_s2;
                if (angle > 0x800) {
                    angle = 0x1000 - angle;
                }
                if (angle < -0x800) {
                    angle = 0x1000 + angle;
                }
                if (!var_s3) {
                    angle /= 4;
                } else {
                    angle /= 2;
                }
                self->ext.et_801291C4.unk86 = angle;
            }
            temp_s2 += self->ext.et_801291C4.unk86;
            if (!var_s3) {
                temp_s2 += 0x180 - ((rand() & 3) << 8);
            }
            temp_s2 &= 0xFFF;
            temp_s3 = prim->next;
            if (temp_s3 == NULL) {
                self->step++;
                return;
            }
            LOW(temp_s3->x0) = LOW(prim->x2);
            LOW(temp_s3->x1) = LOW(prim->x3);
            self->ext.et_801291C4.unk84 = temp_s2;
            self->ext.et_801291C4.prim2 = temp_s3;
            xOffset = (rcos(temp_s2) * 0xC) >> 0xC;
            yOffset = -((rsin(temp_s2) * 0xC) >> 0xC);
            temp_s3->x2 = temp_s3->x0 + xOffset;
            temp_s3->y2 = temp_s3->y0 + yOffset;
            angle = temp_s2 - 0x400;
            var_s8 = 0x10 - (self->params * 4);
            xOffset = (var_s8 * rcos(angle)) >> 0xC;
            yOffset = -((var_s8 * rsin(angle)) >> 0xC);
            temp_s3->x3 = temp_s3->x2 + xOffset;
            temp_s3->y3 = temp_s3->y2 + yOffset;
            temp_s3->drawMode = DRAW_COLORS | DRAW_UNK02;
            self->ext.et_801291C4.unk88--;
        }
        break;
    case 2:
        if (!self->step_s) {
            prim = self->ext.et_801291C4.prim1;
            while (prim != NULL) {
                prim->clut = 0x15F;
                prim = prim->next;
            }
            self->step_s++;
            return;
        }
        prim = self->ext.et_801291C4.prim1;
        while (prim != NULL) {
            prim->clut = 0x194;
            prim->r0 = prim->g0 = prim->b0 = 0x60;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        self->step_s = 0;
        self->step++;
        break;
    case 3:
        var_s8 = 1;
        prim = self->ext.et_801291C4.prim1;
        while (prim != NULL) {
            var_s8 &= !PrimDecreaseBrightness(prim, 4);
            prim = prim->next;
        }
        if (var_s8) {
            prim = self->ext.et_801291C4.prim1;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            DestroyEntity(self);
        }
        break;
    }
}

// White cloud that comes out of Richter's finger with the Vibhuti crash
static AnimationFrame D_80155EA8[] = {
    {3, FRAME(1, 0)},  {3, FRAME(2, 0)},  {3, FRAME(3, 0)},  {3, FRAME(4, 0)},
    {3, FRAME(5, 0)},  {3, FRAME(6, 0)},  {3, FRAME(7, 0)},  {3, FRAME(8, 0)},
    {3, FRAME(9, 0)},  {3, FRAME(10, 0)}, {3, FRAME(11, 0)}, {3, FRAME(12, 0)},
    {3, FRAME(13, 0)}, A_LOOP_AT(0)};
void RicEntityVibhutiCrashCloud(Entity* entity) {
    s32 angle;

    switch (entity->step) {
    case 0:
        entity->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (entity->primIndex == -1) {
            DestroyEntity(entity);
            return;
        }
        entity->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        entity->posX.val = entity->ext.vibCrashCloud.parent->ext.vibhutiCrash.x;
        entity->posY.val = entity->ext.vibCrashCloud.parent->ext.vibhutiCrash.y;
        entity->facingLeft =
            entity->ext.vibCrashCloud.parent->ext.vibhutiCrash.facing;
        entity->ext.vibCrashCloud.subweaponId = PL_W_CRASH_VIBHUTI;
        RicSetSubweaponParams(entity);
        entity->flags |= FLAG_UNK_100000;
        entity->unk5A = 0x79;
        entity->animSet = ANIMSET_DRA(14);
        entity->palette = PAL_OVL(0x19E);
        entity->anim = D_80155EA8;
        entity->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        entity->drawFlags = FLAG_DRAW_UNK8;
        entity->unk6C = 0x60;
        entity->hitboxWidth = 8;
        entity->hitboxHeight = 8;
        angle = (rand() % 512) + 0x300;
        entity->velocityX = rcos(angle) * 32;
        entity->velocityY = -(rsin(angle) * 32);
        entity->step++;
        break;
    case 1:
        entity->ext.vibCrashCloud.unk7C++;
        if (entity->ext.vibCrashCloud.unk7C >= 39) {
            DestroyEntity(entity);
        } else {
            entity->posX.val += entity->velocityX;
            entity->posY.val += entity->velocityY;
        }
        break;
    }
}

#if defined(VERSION_PSP)
extern s32 crash_vibhuti_timer;
#else
static s32 crash_vibhuti_timer;
#endif
void RicEntityCrashVibhuti(Entity* self) {
    FakePrim* prim;
    s32 angle;
    s32 magnitude;
    s32 i;
    s32 facing;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_TILE, 9);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            g_Player.unk4E = 1;
            return;
        }
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        prim = (FakePrim*)&g_PrimBuf[self->primIndex];
        for (i = 0; i < 9; i++) {
            prim->r0 = prim->g0 = prim->b0 = 0xFF;
            prim->w = prim->h = 1;
            prim->priority = PLAYER.zPriority + 8;
            prim->drawMode = DRAW_HIDE | DRAW_UNK02;
            prim = prim->next;
        }
        crash_vibhuti_timer = 0;
        self->step++;
        break;
    case 1:
        // Weird fake stuff to load unk7E a second time
        self->ext.vibhutiCrash.unk7E++;
        if (!(self->ext.vibhutiCrash.unk7E % 2) &&
            self->ext.vibhutiCrash.timer < 8) {
            self->ext.vibhutiCrash.timer++;
            self->ext.vibhutiCrash.unk80++;
            if (self->ext.vibhutiCrash.unk80 >= 0x30) {
                self->step++;
            }
            prim = (FakePrim*)&g_PrimBuf[self->primIndex];
            for (i = 0; i < 9; i++) {
                if (prim->drawMode & DRAW_HIDE) {
                    break;
                }
                prim = prim->next;
            }
            prim->posX.val = PLAYER.posX.val;
            prim->posY.val = PLAYER.posY.val + FIX(-24);
            angle = rand() % 0x200 + 0x300;
            magnitude = (rand() % 24) + 0x20;
            prim->velocityX.val = (rcos(angle) * magnitude);
            prim->velocityY.val = -(rsin(angle) * magnitude);
            prim->drawMode &= ~DRAW_HIDE;
            prim->delay = 0x10;
        }
        // fallthrough
    case 2:
        crash_vibhuti_timer++;
        if (!(crash_vibhuti_timer % 8)) {
            g_api.PlaySfx(SFX_NOISE_SWEEP_DOWN_A);
        }
        prim = (FakePrim*)&g_PrimBuf[self->primIndex];
        for (i = 0; i < 9; i++) {
            if (!(prim->drawMode & DRAW_HIDE)) {
                if (!--prim->delay) {
                    prim->drawMode |= DRAW_HIDE;
                    self->ext.vibhutiCrash.timer--;
                    self->ext.vibhutiCrash.x = prim->posX.val;
                    self->ext.vibhutiCrash.y = prim->posY.val;
                    if (prim->velocityX.val > 0) {
                        facing = false;
                    } else {
                        facing = true;
                    }
                    self->ext.vibhutiCrash.facing = facing;
                    RicCreateEntFactoryFromEntity(
                        self, BP_VITHUBI_CRASH_CLOUD, 0);
                } else {
                    prim->posX.val += prim->velocityX.val;
                    prim->posY.val += prim->velocityY.val;
                    prim->velocityY.val += FIX(0.25);
                    prim->x0 = prim->posX.i.hi;
                    prim->y0 = prim->posY.i.hi;
                }
            }
            prim = prim->next;
        }
        if (self->step == 2 && !self->ext.vibhutiCrash.timer) {
            self->step++;
        }
        break;
    case 3:
        g_Player.unk4E = 1;
        g_Player.unk4E = 1;
        DestroyEntity(self);
        break;
    }
}

void RicEntityCrashReboundStoneParticles(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->ext.subweapon.subweaponId = PL_W_CRASH_REBOUND_STONE;
        RicSetSubweaponParams(entity);
        entity->hitboxWidth = 4;
        entity->hitboxHeight = 4;
        entity->step++;
        break;
    case 1:
        entity->ext.subweapon.timer++;
        if (entity->ext.subweapon.timer > 3) {
            DestroyEntity(entity);
        }
        break;
    }
}

// RIC Entity # 49. Comes from blueprint 57. Factory call in
// RicEntityCrashReboundStone. RicEntityCrashReboundStone is RIC Entity #48.
// Comes from blueprint 56. Blueprint 56 is subweapon 25. And subweapon 25 is
// the crash of subweapon 7. And subweapon 7 is the rebound stone. This is an
// entity spawned from the rebound stone crash.
static s32 angles_80155EE0[] = {0x00000F80, 0x00000100, 0x00000700, 0x00000880};
void func_8016D9C4(Entity* self) {
    PrimLineG2* prim;
    Primitive* prim2;
    s32 i;
    long angle;
    s32 var_s6;
    s32 var_s5;
    s32 var_s7;
    s32 brightness;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 20);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = (PrimLineG2*)&g_PrimBuf[self->primIndex];
        for (i = 0; i < 4; i++) {
            prim->preciseX.val = PLAYER.posX.val;
            prim->preciseY.val = PLAYER.posY.val - FIX(40);
            prim->priority = 194;
            prim->drawMode = DRAW_HIDE;
            prim->x0 = prim->x1 = PLAYER.posX.i.hi;
            prim->y0 = prim->y1 = PLAYER.posY.i.hi - 0x1C;
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            prim->r1 = prim->g1 = prim->b1 = 0x70;
            prim->angle = angles_80155EE0[i];
            prim->delay = 1;
            prim = (PrimLineG2*)prim->next;
        }
        for (brightness = 0x80; i < 20; i++) {
            if (!(i % 4)) {
                brightness -= 0x10;
                switch (i / 4) {
                case 1:
                    self->ext.et_8016D9C4.lines[0] = prim;
                    break;
                case 2:
                    self->ext.et_8016D9C4.lines[1] = prim;
                    break;
                case 3:
                    self->ext.et_8016D9C4.lines[2] = prim;
                    break;
                case 4:
                    self->ext.et_8016D9C4.lines[3] = prim;
                    break;
                }
            }
            prim->priority = 0xC2;
            prim->drawMode = DRAW_HIDE;
            prim->x0 = prim->x1 = PLAYER.posX.i.hi;
            prim->y0 = prim->y1 = PLAYER.posY.i.hi - 0x1C;
            prim->r0 = prim->g0 = prim->b0 = brightness;
            prim->r1 = prim->g1 = prim->b1 = brightness - 0x10;
            prim = (PrimLineG2*)prim->next;
        }
        self->ext.et_8016D9C4.unk90 = 4;
        self->ext.et_8016D9C4.unk8C = self->ext.et_8016D9C4.unk8E = 0;
        g_api.PlaySfx(SFX_RIC_RSTONE_TINK);
        self->step++;
        break;
    case 1:
        self->ext.et_8016D9C4.unk8E = 1;
        switch (self->ext.et_8016D9C4.unk8C) {
        case 0:
            prim = (PrimLineG2*)&g_PrimBuf[self->primIndex];
            break;
        case 1:
            prim = self->ext.et_8016D9C4.lines[0];
            break;
        case 2:
            prim = self->ext.et_8016D9C4.lines[1];
            break;
        case 3:
            prim = self->ext.et_8016D9C4.lines[2];
            break;
        case 4:
            prim = self->ext.et_8016D9C4.lines[3];
            break;
        }
        for (i = 0; i < 4; i++) {
            prim->drawMode &= ~DRAW_HIDE;
            prim = (PrimLineG2*)prim->next;
        }
        self->ext.et_8016D9C4.unk8C++;
        if (self->ext.et_8016D9C4.unk8C > 4) {
            self->step++;
        }
        break;
    case 2:
        if (!self->ext.et_8016D9C4.unk90) {
            self->step++;
            break;
        }
        break;
    case 3:
        self->ext.et_8016D9C4.unk90++;
        if (self->ext.et_8016D9C4.unk90 > 4) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    if (!self->ext.et_8016D9C4.unk8E) {
        return;
    }
    prim = (PrimLineG2*)&g_PrimBuf[self->primIndex];
    for (i = 0; i < 4; i++) {
        if (prim->delay) {
            prim->x1 = prim->x0;
            prim->y1 = prim->y0;
            prim->x0 = prim->preciseX.i.hi;
            prim->y0 = prim->preciseY.i.hi;
            var_s7 = ratan2(prim->preciseY.val, FIX(128) - prim->preciseX.val) &
                     0xFFF;
            angle = prim->angle - var_s7;
            if (labs(angle) > 0x800) {
                if (angle < 0) {
                    angle += 0x1000;
                } else {
                    angle -= 0x1000;
                }
            }
            if (angle >= 0) {
                if (angle > 0x80) {
                    var_s6 = 0x80;
                } else {
                    var_s6 = angle;
                }
                angle = var_s6;
            } else {
                if (angle < -0x80) {
                    var_s5 = -0x80;
                } else {
                    var_s5 = angle;
                }
                angle = var_s5;
            }
            prim->angle = prim->angle - angle;
            prim->angle &= 0xFFF;
            prim->velocityX.val = (rcos(prim->angle) << 4 << 4);
            prim->velocityY.val = -(rsin(prim->angle) << 4 << 4);
            prim->preciseX.val += prim->velocityX.val;
            prim->preciseY.val += prim->velocityY.val;
            self->posX.i.hi = prim->preciseX.i.hi;
            self->posY.i.hi = prim->preciseY.i.hi;
            RicCreateEntFactoryFromEntity(
                self, BP_CRASH_REBOUND_STONE_PARTICLES, 0);
            if (prim->preciseY.val < 0) {
                prim->delay = 0;
                prim->drawMode |= DRAW_HIDE;
                self->ext.et_8016D9C4.unk90--;
            }
        }
        prim = (PrimLineG2*)prim->next;
    }
    prim = self->ext.et_8016D9C4.lines[0];
    prim2 = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 16; i++) {
        prim->x1 = prim->x0;
        prim->y1 = prim->y0;
        prim->x0 = prim2->x1;
        prim->y0 = prim2->y1;
        prim = (PrimLineG2*)prim->next;
        prim2 = prim2->next;
    }
}

// RIC Entity #50. Blueprint 58. Also created by rebound stone crash. Weird!
void RicEntityCrashReboundStoneExplosion(Entity* self) {
    Primitive* prim;
    s32 i;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_G4, 0x10);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 0x10; i++) {
            prim->priority = 0xC2;
            prim->drawMode = DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            prim->x0 = prim->x1 = 0x80;
            prim->y0 = prim->y1 = 0;
            prim = prim->next;
        }
        self->ext.reboundStoneCrashExplosion.unk7C = 0x40;
        self->ext.reboundStoneCrashExplosion.unk7E = 0;
        self->ext.reboundStoneCrashExplosion.unk84 = 0;
        self->ext.reboundStoneCrashExplosion.unk80 = 0x10;
        self->ext.reboundStoneCrashExplosion.unk82 = 8;
        g_api.PlaySfx(SFX_TELEPORT_BANG_B);
        self->step++;
        break;
    case 1:
        self->ext.reboundStoneCrashExplosion.unk84 += 0x20;
        if (self->ext.reboundStoneCrashExplosion.unk84 > 0x120) {
            self->ext.reboundStoneCrashExplosion.subweaponId =
                PL_W_CRASH_REBOUND_EXPLOSION;
            RicSetSubweaponParams(self);
            self->posX.val = FIX(128.0);
            self->posY.val = FIX(128.0);
            self->hitboxWidth = 0x80;
            self->hitboxHeight = 0x80;
            self->step++;
        }
        break;
    case 2:
        self->ext.reboundStoneCrashExplosion.unk86++;
        if (self->ext.reboundStoneCrashExplosion.unk86 == 5) {
            self->ext.reboundStoneCrashExplosion.unk80 = -0x18;
        } else if (self->ext.reboundStoneCrashExplosion.unk86 >= 0xF) {
            self->ext.reboundStoneCrashExplosion.unk82 = -0x18;
            self->step++;
        }
        break;
    case 3:
        break;
    case 4:
        DestroyEntity(self);
        return;
    }
    self->ext.reboundStoneCrashExplosion.unk7C +=
        self->ext.reboundStoneCrashExplosion.unk80;
    if (self->ext.reboundStoneCrashExplosion.unk7C > 0xFF) {
        self->ext.reboundStoneCrashExplosion.unk7C = 0xFF;
        self->ext.reboundStoneCrashExplosion.unk80 = 0;
    } else if (self->ext.reboundStoneCrashExplosion.unk7C < 0) {
        self->ext.reboundStoneCrashExplosion.unk7C =
            self->ext.reboundStoneCrashExplosion.unk80 = 0;
    }
    self->ext.reboundStoneCrashExplosion.unk7E +=
        self->ext.reboundStoneCrashExplosion.unk82;
    if (self->ext.reboundStoneCrashExplosion.unk7E > 0xFF) {
        self->ext.reboundStoneCrashExplosion.unk7E = 0xFF;
        self->ext.reboundStoneCrashExplosion.unk82 = 0;
    } else if (self->ext.reboundStoneCrashExplosion.unk7E < 0) {
        self->ext.reboundStoneCrashExplosion.unk7E =
            self->ext.reboundStoneCrashExplosion.unk82 = 0;
        self->step += 1;
    }
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 16; i++) {
        prim->b0 = prim->b1 = self->ext.reboundStoneCrashExplosion.unk7C;
        prim->b2 = prim->b3 = self->ext.reboundStoneCrashExplosion.unk7E;
        prim->r0 = prim->r1 = prim->g0 = prim->g1 =
            self->ext.reboundStoneCrashExplosion.unk7C;
        prim->r2 = prim->r3 = prim->g2 = prim->g3 =
            self->ext.reboundStoneCrashExplosion.unk7E;
        if (self->step < 2) {
            prim->x2 =
                ((rcos(i << 7) * self->ext.reboundStoneCrashExplosion.unk84) >>
                 0xC) +
                0x80;
            prim->x3 = ((rcos((i + 1) << 7) *
                         self->ext.reboundStoneCrashExplosion.unk84) >>
                        0xC) +
                       0x80;
            prim->y2 =
                ((rsin(i << 7) * self->ext.reboundStoneCrashExplosion.unk84) >>
                 0xC);
            prim->y3 = ((rsin((i + 1) << 7) *
                         self->ext.reboundStoneCrashExplosion.unk84) >>
                        0xC);
        }
        prim = prim->next;
    }
}

void RicEntityCrashReboundStone(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_20000 | FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->step++;
        entity->ext.timer.t = 0x14;
        // fallthrough
    case 1:
        if (--entity->ext.timer.t) {
            break;
        }
    case 3:
    case 5:
        RicCreateEntFactoryFromEntity(entity, BP_57, 0);
        entity->step++;
    case 2:
    case 4:
    case 6:
        entity->ext.timer.t++;
        if (entity->ext.timer.t > 10) {
            entity->ext.timer.t = 0;
            entity->posX.val = FIX(128.0);
            entity->posY.val = 0;
            RicCreateEntFactoryFromEntity(entity, FACTORY(BP_EMBERS, 1), 0);
            entity->step++;
        }
        break;
    case 7:
        entity->ext.timer.t++;
        if (entity->ext.timer.t > 15) {
            DestroyEntity(entity);
            g_Player.unk4E = 1;
            RicCreateEntFactoryFromEntity(
                entity, BP_CRASH_REBOUND_STONE_EXPLOSION, 0);
        }
        break;
    }
}

#define BIBLE_PAGE_COUNT 6
#if defined(VERSION_PSP)
extern Point16 bible_pages_pos[BIBLE_PAGE_COUNT];
#else
static Point16 bible_pages_pos[BIBLE_PAGE_COUNT];
#endif
void RicEntityCrashBibleBeam(Entity* self) {
    Primitive* prim;
    s32 i;
    s32 var_s3;
    s32 psp_s3;
    s32 halfwidth;
    s32 hitboxOffX;
    s16 var_s7;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_G4, BIBLE_PAGE_COUNT);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        if (self->facingLeft) {
            self->ext.bibleBeam.unk7C = -16;
            self->ext.bibleBeam.unk7E = -2;
        } else {
            self->ext.bibleBeam.unk7C = 16;
            self->ext.bibleBeam.unk7E = 2;
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < BIBLE_PAGE_COUNT; i++) {
            var_s3 = i + 2;
            if (var_s3 >= BIBLE_PAGE_COUNT) {
                var_s3 -= 6;
            }
            prim->x0 = prim->x1 = bible_pages_pos[i].x;
            prim->y0 = prim->y1 = bible_pages_pos[i].y;
            prim->x2 = prim->x3 = bible_pages_pos[var_s3].x;
            prim->y2 = prim->y3 = bible_pages_pos[var_s3].y;
            prim->priority = 0xC2;
            prim->drawMode = DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
        }
        self->step++;
        break;
    case 1:
        self->ext.bibleBeam.unk80++;
        if (self->ext.bibleBeam.unk80 >= 0x3C) {
            self->ext.bibleBeam.subweaponId = PL_W_BIBLE_BEAM;
            RicSetSubweaponParams(self);
            g_api.PlaySfx(SFX_WEAPON_APPEAR);
            g_api.PlaySfx(SFX_TELEPORT_BANG_A);
            self->step++;
        }
        break;
    case 2:
        self->ext.bibleBeam.unk80++;
        self->ext.bibleBeam.unk7E += self->ext.bibleBeam.unk7C;
        var_s3 = bible_pages_pos[1].x + self->ext.bibleBeam.unk7E;
        if (var_s3 < -0x50 || var_s3 > 0x150) {
            self->step++;
        }
        break;
    case 3:
        self->ext.bibleBeam.unk80++;
        if (self->ext.bibleBeam.unk80 >= 0x78) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    var_s7 = 0; // @bug: this is never unused
    for (i = 0; i < BIBLE_PAGE_COUNT; i++) {
        var_s3 = i + 2;
        if (var_s3 >= BIBLE_PAGE_COUNT) {
            var_s3 -= 6;
        }
        psp_s3 = i * 256;
        prim->r0 = prim->r1 =
            abs((rsin((self->ext.bibleBeam.unk80 * 20) + psp_s3) * 96) >> 0xc);
        prim->g0 = prim->g1 =
            abs((rsin((self->ext.bibleBeam.unk80 * 15) + psp_s3) * 96) >> 0xc);
        prim->b0 = prim->b1 =
            abs((rsin((self->ext.bibleBeam.unk80 * 10) + psp_s3) * 96) >> 0xc);
        psp_s3 = var_s3 * 256;
        prim->r2 = prim->r3 =
            abs((rsin((self->ext.bibleBeam.unk80 * 15) + psp_s3) * 96) >> 0xc);
        prim->g2 = prim->g3 =
            abs((rsin((self->ext.bibleBeam.unk80 * 10) + psp_s3) * 96) >> 0xc);
        prim->b2 = prim->b3 =
            abs((rsin((self->ext.bibleBeam.unk80 * 20) + psp_s3) * 96) >> 0xc);
        prim->x1 = bible_pages_pos[i].x;
        prim->y0 = prim->y1 = bible_pages_pos[i].y;
        prim->x3 = bible_pages_pos[var_s3].x;
        prim->y2 = prim->y3 = bible_pages_pos[var_s3].y;
        prim->x0 = bible_pages_pos[i].x + self->ext.bibleBeam.unk7E;
        prim->x2 = bible_pages_pos[var_s3].x + self->ext.bibleBeam.unk7E;
        if (var_s7 < abs(bible_pages_pos[i].y)) {
            var_s7 = abs(bible_pages_pos[i].y);
        }
        prim = prim->next;
    }
    self->hitboxOffX = self->facingLeft ? -(self->ext.bibleBeam.unk7E / 2)
                                        : (self->ext.bibleBeam.unk7E / 2);
    self->hitboxWidth = abs(self->hitboxOffX);
    self->hitboxHeight = var_s7 - self->posY.i.hi;
}

static s16 bible_page_angles[BIBLE_PAGE_COUNT] = {
    0x0400, 0x06AB, 0x0955, 0x0C00, 0x0EAB, 0x1155,
};
#if defined(VERSION_PSP)
extern s32 bible_pages_volume;
#else
static s32 bible_pages_volume;
#endif
void RicEntityCrashBible(Entity* self) {
    Primitive* prim;
    s32 i;
    s32 psp_s2;
    s16 psp_s4;
    s16 psp_s3;
    s32 psp_s6;
    s32 psp_s5;
    s32 sp3C;
    s32 sp48;
    s32 sp40;
    long sp44;
    long sp4C;
    s32 psp_s8;
    s32 psp_s7;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1 + BIBLE_PAGE_COUNT);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            g_Player.unk4E = 1;
            return;
        }
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        self->posX.val = PLAYER.posX.val;
        self->posY.val = PLAYER.posY.val;
        self->velocityY = FIX(-4);
        if (self->facingLeft) {
            self->velocityX = FIX(12);
            self->ext.et_8016E9E4.unk88 = FIX(1.5);
            self->ext.et_8016E9E4.unk7E = -0x200;
        } else {
            self->velocityX = FIX(-12);
            self->ext.et_8016E9E4.unk88 = FIX(-1.5);
            self->ext.et_8016E9E4.unk7E = 0x200;
        }
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1E;
        prim->clut = 0x17F;
        prim->u0 = prim->u2 = 0x98;
        prim->v0 = prim->v1 = 0xD8;
        prim->u1 = prim->u3 = 0xA8;
        prim->v2 = prim->v3 = 0xF0;
        prim->priority = 0xC2;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        for (i = 0; i < BIBLE_PAGE_COUNT; i++) {
            prim->tpage = 0x1C;
            prim->clut = 0x1AE;
            prim->u0 = prim->u2 = 0x20;
            prim->u1 = prim->u3 = 0x30;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 0x10;
            prim->priority = 0xC1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.et_8016E9E4.unk84 = 0x40;
        bible_pages_volume = 0x60;
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode &= ~DRAW_HIDE;
        self->step++;
    case 2:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityX -= self->ext.et_8016E9E4.unk88;
        self->velocityY -= FIX(0.5);
        self->ext.et_8016E9E4.unk82++;
        if (self->ext.et_8016E9E4.unk82 >= 8) {
            self->ext.et_8016E9E4.unk82 = 0;
            self->step++;
        }
        break;
    case 3:
        self->ext.et_8016E9E4.unk82++;
        if (self->ext.et_8016E9E4.unk82 > 5) {
            prim = &g_PrimBuf[self->primIndex];
            prim->clut = 0x19F;
            prim->drawMode |=
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
            for (i = 0; i < BIBLE_PAGE_COUNT; i++) {
                prim->drawMode &= ~DRAW_HIDE;
                prim = prim->next;
            }
            self->ext.et_8016E9E4.unk82 = 0;
            self->step++;
        }
        break;
    case 4:
        self->ext.et_8016E9E4.unk84 -= 4;
        if (self->ext.et_8016E9E4.unk84 <= 0) {
            self->step++;
        }
        break;
    case 5:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode |= DRAW_HIDE;
        self->step++;
    case 6:
        self->ext.et_8016E9E4.unk7C += 0x80;
        self->ext.et_8016E9E4.unk7C &= 0xFFF;
        self->ext.et_8016E9E4.unk80 += 4;
        if (self->ext.et_8016E9E4.unk80 >= 0x30) {
            self->step++;
        }
        break;
    case 7:
        self->ext.et_8016E9E4.unk7C += 0x80;
        self->ext.et_8016E9E4.unk7C &= 0xFFF;
        self->ext.et_8016E9E4.unk82++;
        if (self->ext.et_8016E9E4.unk82 >= 0x1E) {
            // create bible page beam
            RicCreateEntFactoryFromEntity(self, BP_CRASH_BIBLE_BEAM, 0);
            self->ext.et_8016E9E4.unk82 = 0;
            self->step++;
        }
        break;
    case 8:
        self->ext.et_8016E9E4.unk7C += 0x80;
        self->ext.et_8016E9E4.unk7C &= 0xFFF;
        self->ext.et_8016E9E4.unk82++;
        if (self->ext.et_8016E9E4.unk82 >= 0x60) {
            g_Player.unk4E = 1;
            self->step++;
        }
        break;
    case 9:
        self->ext.et_8016E9E4.unk7C += 0x80;
        self->ext.et_8016E9E4.unk7C &= 0xFFF;
        self->ext.et_8016E9E4.unk80 -= 2;
        if (self->ext.et_8016E9E4.unk80 <= 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    // FAKE, needed for reg match
    if (self->ext.et_8016E9E4.unk7C == 0x100 ||
        self->ext.et_8016E9E4.unk7C == 0x500 ||
        self->ext.et_8016E9E4.unk7C == 0x900 ||
        self->ext.et_8016E9E4.unk7C == 0xD00) {
        if (self->step < 9) {
            g_api.PlaySfxVolPan(SFX_ARROW_SHOT_A, bible_pages_volume, 0);
            if (self->step >= 5) {
                bible_pages_volume -= 4;
            }
            if (bible_pages_volume < 0) {
                bible_pages_volume = 0;
            }
        }
    }

    prim = &g_PrimBuf[self->primIndex];
    psp_s4 = self->posX.i.hi;
    psp_s3 = self->posY.i.hi;
    prim->x0 = prim->x2 = psp_s4 - 8;
    prim->x1 = prim->x3 = psp_s4 + 8;
    prim->y0 = prim->y1 = psp_s3 - 12;
    prim->y2 = prim->y3 = psp_s3 + 12;
    prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 = prim->r2 =
        prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
            self->ext.et_8016E9E4.unk84;
    prim = prim->next;

    sp44 = rsin(self->ext.et_8016E9E4.unk7E);
    sp4C = rcos(self->ext.et_8016E9E4.unk7E);
    for (i = 0; i < BIBLE_PAGE_COUNT; i++) {
        sp3C = 0;
        sp48 = (rsin(self->ext.et_8016E9E4.unk7C + bible_page_angles[i]) *
                self->ext.et_8016E9E4.unk80) >>
               0xC;
        sp40 = (rcos(self->ext.et_8016E9E4.unk7C + bible_page_angles[i]) *
                self->ext.et_8016E9E4.unk80) >>
               0xC;
        psp_s6 = (sp4C * sp3C + sp44 * sp40) >> 0xC;
        psp_s2 = (sp4C * sp40 - sp44 * sp3C) >> 0xC;
        psp_s5 = sp48;
        psp_s2 += 0x200;
        psp_s6 = (psp_s6 << 9) / psp_s2;
        psp_s5 = (psp_s5 << 9) / psp_s2;
        psp_s4 = self->posX.i.hi + psp_s6;
        psp_s3 = self->posY.i.hi + psp_s5;
        bible_pages_pos[i].x = psp_s4;
        bible_pages_pos[i].y = psp_s3;
        psp_s8 = 0x1000 / psp_s2;
        psp_s7 = 0x1000 / psp_s2;
        prim->x0 = prim->x2 = psp_s4 - psp_s8;
        prim->x1 = prim->x3 = psp_s4 + psp_s8;
        prim->y0 = prim->y1 = psp_s3 - psp_s7;
        prim->y2 = prim->y3 = psp_s3 + psp_s7;
        prim = prim->next;
    }
}

void func_8016F198(Entity* self) {
    const int PrimCount = 16;
#if defined(VERSION_PSP)
    const MaxHeight = 248;
    const HalfHeight = 128;
#else
    const MaxHeight = 240;
    const HalfHeight = 120;
#endif
    Primitive* prim;
    s32 i;
    s32 tpage;
    s32 angleX;
    s32 angleY;
    s16 startMod;
    s16 endMod;
    s16 sx;
    s16 ex;
    s16 sy;
    s16 ey;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, PrimCount);
        if (self->primIndex == -1) {
            DestroyEntity(self);
#if !defined(VERSION_PSP)
            g_Player.unk4E = 1;
#endif
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 16; i++) {
            prim->priority = 0xC2;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 16; i++) {
            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
        }
        self->step++;
    case 2:
        self->ext.factory.unk7C++;
        if (self->ext.factory.unk7C >= 0x18) {
            self->step++;
        }
        break;
    case 3:
#if !defined(VERSION_PSP)
        g_Player.unk4E = 1;
#endif
        DestroyEntity(self);
        return;
    }
    if (!self->ext.factory.unk7C) {
        return;
    }
    if (
#if !defined(VERSION_PSP)
        g_CurrentBuffer == g_GpuBuffers
#else
        0
#endif
    ) {
        tpage = 0x104;
    } else {
        tpage = 0x100;
    }
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < PrimCount; i++) {
        angleX = rsin(i << 8);
        angleY = rcos(i << 8);
        startMod = self->ext.factory.unk7C * 8;
        endMod = 0;
        if (self->ext.factory.unk7C >= 4) {
            endMod = (self->ext.factory.unk7C - 4) * 8;
        }
        sx = ((angleY * startMod) >> 0xC) + 0x80;
        ex = ((angleY * endMod) >> 0xC) + 0x80;
        sy = ((angleX * startMod) >> 0xC) + HalfHeight;
        ey = ((angleX * endMod) >> 0xC) + HalfHeight;
        prim->x0 = sx = CLAMP(sx, 0, 0xFF);
        prim->x2 = ex = CLAMP(ex, 0, 0xFF);
        prim->y0 = sy = CLAMP(sy, 0, MaxHeight);
        prim->y2 = ey = CLAMP(ey, 0, MaxHeight);
        prim->u0 = 0xFF - prim->x0;
        prim->u2 = 0xFF - prim->x2;
        prim->v0 = MaxHeight - prim->y0;
        prim->v2 = MaxHeight - prim->y2;

        angleX = rsin((i + 1) << 8);
        angleY = rcos((i + 1) << 8);
        sx = ((angleY * startMod) >> 0xC) + 0x80;
        ex = ((angleY * endMod) >> 0xC) + 0x80;
        sy = ((angleX * startMod) >> 0xC) + HalfHeight;
        ey = ((angleX * endMod) >> 0xC) + HalfHeight;
        prim->x1 = sx = CLAMP(sx, 0, 0xFF);
        prim->x3 = ex = CLAMP(ex, 0, 0xFF);
        prim->y1 = sy = CLAMP(sy, 0, MaxHeight);
        prim->y3 = ey = CLAMP(ey, 0, MaxHeight);
        prim->u1 = 0xFF - prim->x1;
        prim->u3 = 0xFF - prim->x3;
        prim->v1 = MaxHeight - prim->y1;
        prim->v3 = MaxHeight - prim->y3;
#if defined(VERSION_PSP)
        prim->u0 = prim->u0 = CLAMP(prim->u0, 1, 0xFE);
        prim->u2 = prim->u2 = CLAMP(prim->u2, 1, 0xFE);
        prim->u1 = prim->u1 = CLAMP(prim->u1, 1, 0xFE);
        prim->u3 = prim->u3 = CLAMP(prim->u3, 1, 0xFE);
#endif

        prim->tpage = tpage;
        prim = prim->next;
    }
}

void RicEntityCrashStopwatchDoneSparkle(Entity* self) {
    s32 sp4C;
    s32 selfX;
    s32 selfY;
    s32 psp_s8;
    s32 psp_s7;
    s32 psp_s6;
    s32 psp_s5;
    s32 psp_s4;
    s32 i;
    s32 psp_s1;
    s32 psp_s2;
    Primitive* prim;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 20);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        prim->priority = 0xC2;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->tpage = 0x1A;
        prim->clut = 0x19F;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;
        // @bug: prim->g0 is not set, instead g2 is set twice
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
            prim->g2 = prim->g3 = 0x40;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;

        prim = prim->next;
        prim->priority = 0xC2;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE | DRAW_COLORS |
                         DRAW_UNK02 | DRAW_TRANSP;
        prim->tpage = 0x1A;
        prim->clut = 0x19F;
        prim->u0 = prim->u2 = 0x40;
        prim->u1 = prim->u3 = 0x7F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
            prim->g2 = prim->g3 = 0x40;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;

        prim = prim->next;
        prim->priority = 0xC2;
        prim->drawMode = DRAW_UNK_400 | DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                         DRAW_HIDE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->tpage = 0x1A;
        prim->clut = 0x19F;
        prim->u0 = prim->u2 = 0xB;
        prim->u1 = prim->u3 = 0x35;
        prim->v0 = prim->v1 = 0xCB;
        prim->v2 = prim->v3 = 0xF5;
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
            prim->g2 = prim->g3 = 0xCF;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0xFF;

        prim = prim->next;
        prim->priority = 0xC2;
        prim->drawMode = DRAW_UNK_400 | DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                         DRAW_HIDE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->tpage = 0x1A;
        prim->clut = 0x19F;
        prim->u0 = prim->u2 = 0xB;
        prim->u1 = prim->u3 = 0x35;
        prim->v0 = prim->v1 = 0xCB;
        prim->v2 = prim->v3 = 0xF5;
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
            prim->g2 = prim->g3 = 0xCF;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0xFF;

        self->ext.et_stopWatchSparkle.unk88 = prim->next;
        for (i = 0; i < 16; i++) {
            prim = prim->next;
            prim->priority = PLAYER.zPriority + 3;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            prim->tpage = 0x1A;
            prim->clut = 0x194;
            prim->u0 = prim->u2 = (rand() % 5 * 0x10) + 0x90;
            prim->u1 = prim->u3 = prim->u0 + 0x10;
            prim->v0 = prim->v1 = 0xC0;
            prim->v2 = prim->v3 = 0xD0;
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 = 0x80;
        }
        self->ext.et_stopWatchSparkle.unk7C = 4;
        self->ext.et_stopWatchSparkle.unk7E =
            self->ext.et_stopWatchSparkle.unk80 =
                self->ext.et_stopWatchSparkle.unk82 = 0;
        self->ext.et_stopWatchSparkle.unk8C =
            self->ext.et_stopWatchSparkle.unk8E = 0;
        self->step++;
        break;
    case 1:
        self->ext.et_stopWatchSparkle.unk7C++;
        if (self->ext.et_stopWatchSparkle.unk7C >= 0x10) {
            self->ext.et_stopWatchSparkle.unk7E = 4;
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
            prim->drawMode &= ~DRAW_HIDE;
            self->ext.et_stopWatchSparkle.unk80 = 0x10;
            self->ext.et_stopWatchSparkle.unk82 = 0;
            g_api.PlaySfx(SFX_ELECTRICITY);
            self->step++;
        }
        break;
    case 2:
        self->ext.et_stopWatchSparkle.unk7C--;
        if (self->ext.et_stopWatchSparkle.unk7C <= 0) {
            prim = &g_PrimBuf[self->primIndex];
            prim->drawMode |= DRAW_HIDE;
            prim = prim->next;
            prim->drawMode |= DRAW_HIDE;
            self->ext.et_stopWatchSparkle.unk84 = 0xFF;
            self->ext.et_stopWatchSparkle.unk8E = 1;
            self->ext.et_stopWatchSparkle.unk86 =
                self->facingLeft ? 0xA00 : 0xE00;
            self->ext.et_stopWatchSparkle.unk94 =
                self->facingLeft ? 0x700 : 0x100;
            self->ext.et_stopWatchSparkle.unk90 = self->posX.i.hi;
            self->ext.et_stopWatchSparkle.unk92 = self->posY.i.hi;
            self->step++;
        }
        self->ext.et_stopWatchSparkle.unk7E += 2;
        self->ext.et_stopWatchSparkle.unk80 += 2;
        self->ext.et_stopWatchSparkle.unk82 += 0x80;
        self->ext.et_stopWatchSparkle.unk82 &= 0xFFF;
        break;
    case 3:
        self->ext.et_stopWatchSparkle.unk84 -= 0x10;
        if (self->ext.et_stopWatchSparkle.unk84 < 0x80) {
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            prim = prim->next;
            prim->drawMode |= DRAW_HIDE;
            prim = prim->next;
            prim->drawMode |= DRAW_HIDE;
            self->step++;
        }
        self->ext.et_stopWatchSparkle.unk82 += 0x80;
        self->ext.et_stopWatchSparkle.unk82 &= 0xFFF;
        break;
    case 4:
        if (!self->ext.et_stopWatchSparkle.unk8E) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    switch (self->step) {
    case 1:
        prim->x0 = prim->x2 =
            self->posX.i.hi - self->ext.et_stopWatchSparkle.unk7C;
        prim->x1 = prim->x3 =
            self->posX.i.hi + self->ext.et_stopWatchSparkle.unk7C;
        prim->y0 = prim->y1 =
            self->posY.i.hi - self->ext.et_stopWatchSparkle.unk7C;
        prim->y2 = prim->y3 =
            self->posY.i.hi + self->ext.et_stopWatchSparkle.unk7C;
        break;
    case 2:
        prim->x0 = prim->x2 =
            self->posX.i.hi - self->ext.et_stopWatchSparkle.unk7C;
        prim->x1 = prim->x3 =
            self->posX.i.hi + self->ext.et_stopWatchSparkle.unk7C;
        prim->y0 = prim->y1 =
            self->posY.i.hi - self->ext.et_stopWatchSparkle.unk7C;
        prim->y2 = prim->y3 =
            self->posY.i.hi + self->ext.et_stopWatchSparkle.unk7C;

        prim = prim->next;
        prim->x0 = prim->x2 =
            self->posX.i.hi - self->ext.et_stopWatchSparkle.unk7E;
        prim->x1 = prim->x3 =
            self->posX.i.hi + self->ext.et_stopWatchSparkle.unk7E;
        prim->y0 = prim->y1 =
            self->posY.i.hi - self->ext.et_stopWatchSparkle.unk7E;
        prim->y2 = prim->y3 =
            self->posY.i.hi + self->ext.et_stopWatchSparkle.unk7E;
        psp_s1 = rsin(self->ext.et_stopWatchSparkle.unk82);
        psp_s2 = rcos(self->ext.et_stopWatchSparkle.unk82);
        sp4C = psp_s2 * self->ext.et_stopWatchSparkle.unk80;
        psp_s8 = psp_s1 * self->ext.et_stopWatchSparkle.unk80;
        psp_s7 = psp_s2 * (self->ext.et_stopWatchSparkle.unk80 / 8);
        psp_s6 = psp_s1 * (self->ext.et_stopWatchSparkle.unk80 / 8);

        prim = prim->next;
        prim->x0 = self->posX.i.hi + ((-sp4C - -psp_s8) >> 0xC);
        prim->y0 = self->posY.i.hi + ((-psp_s8 + -sp4C) >> 0xC);
        prim->x1 = self->posX.i.hi + ((psp_s7 - -psp_s6) >> 0xC);
        prim->y1 = self->posY.i.hi + ((psp_s6 + -psp_s7) >> 0xC);
        prim->x2 = self->posX.i.hi + ((-psp_s7 - psp_s6) >> 0xC);
        prim->y2 = self->posY.i.hi + ((-psp_s6 + psp_s7) >> 0xC);
        prim->x3 = self->posX.i.hi + ((sp4C - psp_s8) >> 0xC);
        prim->y3 = self->posY.i.hi + ((psp_s8 + sp4C) >> 0xC);

        prim = prim->next;
        prim->x0 = self->posX.i.hi + ((-psp_s7 - -psp_s6) >> 0xC);
        prim->y0 = self->posY.i.hi + ((-psp_s6 + -psp_s7) >> 0xC);
        prim->x1 = self->posX.i.hi + ((sp4C - -psp_s8) >> 0xC);
        prim->y1 = self->posY.i.hi + ((psp_s8 + -sp4C) >> 0xC);
        prim->x2 = self->posX.i.hi + ((-sp4C - psp_s8) >> 0xC);
        prim->y2 = self->posY.i.hi + ((-psp_s8 + sp4C) >> 0xC);
        prim->x3 = self->posX.i.hi + ((psp_s7 - psp_s6) >> 0xC);
        prim->y3 = self->posY.i.hi + ((psp_s6 + psp_s7) >> 0xC);
        break;
    case 3:
        psp_s1 = rsin(self->ext.et_stopWatchSparkle.unk82);
        psp_s2 = rcos(self->ext.et_stopWatchSparkle.unk82);
        sp4C = psp_s2 * self->ext.et_stopWatchSparkle.unk80;
        psp_s8 = psp_s1 * self->ext.et_stopWatchSparkle.unk80;
        psp_s7 = psp_s2 * (self->ext.et_stopWatchSparkle.unk80 / 8);
        psp_s6 = psp_s1 * (self->ext.et_stopWatchSparkle.unk80 / 8);
        prim = prim->next;
        prim = prim->next;

        prim->x0 = self->posX.i.hi + ((-sp4C - -psp_s8) >> 0xC);
        prim->y0 = self->posY.i.hi + ((-psp_s8 + -sp4C) >> 0xC);
        prim->x1 = self->posX.i.hi + ((psp_s7 - -psp_s6) >> 0xC);
        prim->y1 = self->posY.i.hi + ((psp_s6 + -psp_s7) >> 0xC);
        prim->x2 = self->posX.i.hi + ((-psp_s7 - psp_s6) >> 0xC);
        prim->y2 = self->posY.i.hi + ((-psp_s6 + psp_s7) >> 0xC);
        prim->x3 = self->posX.i.hi + ((sp4C - psp_s8) >> 0xC);
        prim->y3 = self->posY.i.hi + ((psp_s8 + sp4C) >> 0xC);
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
            prim->g2 = prim->g3 = self->ext.et_stopWatchSparkle.unk84 - 0x20;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 =
            self->ext.et_stopWatchSparkle.unk84;

        prim = prim->next;
        prim->x0 = self->posX.i.hi + ((-psp_s7 - -psp_s6) >> 0xC);
        prim->y0 = self->posY.i.hi + ((-psp_s6 + -psp_s7) >> 0xC);
        prim->x1 = self->posX.i.hi + ((sp4C - -psp_s8) >> 0xC);
        prim->y1 = self->posY.i.hi + ((psp_s8 + -sp4C) >> 0xC);
        prim->x2 = self->posX.i.hi + ((-sp4C - psp_s8) >> 0xC);
        prim->y2 = self->posY.i.hi + ((-psp_s8 + sp4C) >> 0xC);
        prim->x3 = self->posX.i.hi + ((psp_s7 - psp_s6) >> 0xC);
        prim->y3 = self->posY.i.hi + ((psp_s6 + psp_s7) >> 0xC);
        prim->g1 = prim->g2 = prim->g2 = prim->g3 =
            self->ext.et_stopWatchSparkle.unk84 - 0x20;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 =
            self->ext.et_stopWatchSparkle.unk84;
        break;
    }
    if (self->ext.et_stopWatchSparkle.unk8E) {
        self->ext.et_stopWatchSparkle.unk8E = 0;
        prim = self->ext.et_stopWatchSparkle.unk88;
        for (i = 0; i < 16; i++) {
            if (i == self->ext.et_stopWatchSparkle.unk8C) {
                if (self->ext.et_stopWatchSparkle.unk90 < 0x120 &&
                    self->ext.et_stopWatchSparkle.unk90 > -0x20 &&
                    self->ext.et_stopWatchSparkle.unk92 < 0x120 &&
                    self->ext.et_stopWatchSparkle.unk92 > -0x20) {
                    prim->drawMode &= ~DRAW_HIDE;
                    prim->r0 = 0x80;
                    if (!(i % 4)) {
                        psp_s5 = rand() % 0x200 + 0x200;
                    } else {
                        psp_s5 = rand() % 0x80 + 0x80;
                    }
                    psp_s4 = self->ext.et_stopWatchSparkle.unk86 -
                             self->ext.et_stopWatchSparkle.unk94;
                    if (abs(psp_s4) > 0x800) {
                        if (psp_s4 < 0) {
                            psp_s4 += 0x1000;
                        } else {
                            psp_s4 -= 0x1000;
                        }
                    }
                    if (psp_s4 > 0) {
                        psp_s5 = -psp_s5;
                    }
                    self->ext.et_stopWatchSparkle.unk86 += psp_s5;
                    self->ext.et_stopWatchSparkle.unk86 &= 0xFFF;
                    psp_s1 = rsin(self->ext.et_stopWatchSparkle.unk86);
                    psp_s2 = rcos(self->ext.et_stopWatchSparkle.unk86);
                    prim->x0 = self->ext.et_stopWatchSparkle.unk90 +
                               (-(psp_s1 * -8) >> 0xC);
                    prim->y0 = self->ext.et_stopWatchSparkle.unk92 +
                               ((psp_s2 * -8) >> 0xC);
                    prim->x1 = self->ext.et_stopWatchSparkle.unk90 +
                               ((psp_s2 * 16 - psp_s1 * -8) >> 0xC);
                    prim->y1 = self->ext.et_stopWatchSparkle.unk92 +
                               ((psp_s1 * 16 + psp_s2 * -8) >> 0xC);
                    prim->x2 = self->ext.et_stopWatchSparkle.unk90 +
                               (-(psp_s1 * 8) >> 0xC);
                    prim->y2 = self->ext.et_stopWatchSparkle.unk92 +
                               (psp_s2 * 8 >> 0xC);
                    prim->x3 = self->ext.et_stopWatchSparkle.unk90 +
                               ((psp_s2 * 16 - psp_s1 * 8) >> 0xC);
                    prim->y3 = self->ext.et_stopWatchSparkle.unk92 +
                               ((psp_s1 * 16 + psp_s2 * 8) >> 0xC);
                    prim->r0 = 0x80;
                    self->ext.et_stopWatchSparkle.unk90 += (psp_s2 * 16) >> 0xC;
                    self->ext.et_stopWatchSparkle.unk92 += (psp_s1 * 16) >> 0xC;
                    selfX = self->posX.i.hi;
                    selfY = self->posY.i.hi;
                    self->posX.i.hi = self->ext.et_stopWatchSparkle.unk90;
                    self->posY.i.hi = self->ext.et_stopWatchSparkle.unk92;
                    RicCreateEntFactoryFromEntity(
                        self, BP_CRASH_STOPWATCH_LIGHTNING, 0);
                    self->posX.i.hi = selfX;
                    self->posY.i.hi = selfY;
                } else {
                    prim->drawMode |= DRAW_HIDE;
                }
            } else {
                prim->r0 -= 8;
                if (prim->r0 < 0x20) {
                    prim->drawMode |= DRAW_HIDE;
                }
            }
            prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 = prim->g2 =
                prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->r0;
            self->ext.et_stopWatchSparkle.unk8E |=
                prim->drawMode & DRAW_HIDE ? 0 : 1;
            prim = prim->next;
        }
        self->ext.et_stopWatchSparkle.unk8C++;
        if (self->ext.et_stopWatchSparkle.unk8C >= 0x10) {
            self->ext.et_stopWatchSparkle.unk8C = 0;
        }
    }
}

// Created by blueprint #73.
// When Stopwatch crash ends, each of the 4 ricStopWatches shoots out a
// lightning Each lightning can harm enemies. This entity represents the
// attacking part of that lightning. It does not do any graphics and just has
// the hitbox. Not clear why this is a dedicated entity rather than having one
// entity that is graphics + hitbox for the lightning.
void RicEntityStopwatchCrashLightning(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        self->ext.subweapon.subweaponId = PL_W_30;
        RicSetSubweaponParams(self);
        self->hitboxWidth = 8;
        self->hitboxHeight = 8;
        self->step++;
        break;
    case 1:
        self->ext.timer.t++;
        if (self->ext.timer.t > 4) {
            DestroyEntity(self);
        }
        break;
    }
}

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
