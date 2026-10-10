// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"
#include "../../dra/subwpn_dagger.h"

Entity* CreateEntFactoryFromEntity(Entity* source, u32 factoryParams, s16 arg2);

extern PlayerState g_Dop;

#include "../../rebound_stone.h"

extern EInit EInitReboundStone;
void EntitySubwpnReboundStone(Entity* self) {
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

    switch (self->step) {
    case 0:
        InitializeEntity(EInitReboundStone);
        if (g_Dop.status & PLAYER_STATUS_POISON) {
            self->attack = self->attack / 2;
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 8);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->posY.i.hi -= 12;
        playerX = self->posX.i.hi;
        playerY = self->posY.i.hi;

        for (prim = (PrimLineG2*)&g_PrimBuf[self->primIndex], i = 0;
             prim != NULL; i++, prim = prim->next) {
            prim->r0 = prim->r1 = 0xFF;
            prim->g0 = prim->g1 = 0x7F;
            prim->priority = DOPPLEGANGER.zPriority + 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            if (i != 0) {
                prim->drawMode |= DRAW_HIDE;
            }
            prim->x0 = prim->x1 = playerX;
            prim->y0 = prim->y1 = playerY;
            prim->timer = 20;
        }
        self->flags |=
            FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->zPriority = DOPPLEGANGER.zPriority + 2;

        if (DOPPLEGANGER.facingLeft) {
            self->ext.reboundStone.stoneAngle = 0x980;
        } else {
            self->ext.reboundStone.stoneAngle = 0xE80;
        }
        self->ext.reboundStone.stoneAngle += (rand() & 0x7F) - 0x40;

        self->ext.reboundStone.lifeTimer = 0x40;
        self->step = 1;
        g_api.PlaySfx(SFX_WEAPON_SWISH_C);

        break;
    case 1:
        if (self->flags & FLAG_DEAD) {
            CreateEntFactoryFromEntity(self, BP_REBOUND_STONE_HIT, 0);
            g_api.PlaySfx(SFX_UI_SUBWEAPON_TINK);
            self->step = 2;
            break;
        }

        playerX = self->posX.i.hi;
        playerY = self->posY.i.hi;
        deltaX = rcos(self->ext.reboundStone.stoneAngle) * 0x10;
        deltaY = -rsin(self->ext.reboundStone.stoneAngle) * 0x10;
        currX = self->posX.val;
        currY = self->posY.val;

        for (i = 0; i < 6; i++) {
            collX = FIX_TO_I(currX);
            collY = FIX_TO_I(currY + deltaY);
            g_api.CheckCollision(collX, collY, &collider, 0);
            colliderFlags =
                collider.effects &
                (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                 EFFECT_UNK_1000 | EFFECT_UNK_0800 | EFFECT_BLOCK);
            if (colliderFlags & EFFECT_SOLID) {
                colliderFlags &=
                    EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                    EFFECT_UNK_1000 | EFFECT_UNK_0800 | EFFECT_UNK_0400 |
                    EFFECT_UNK_0200 | EFFECT_UNK_0100;
                if (deltaY > 0) {
                    if ((colliderFlags == EFFECT_NONE) ||
                        (colliderFlags & EFFECT_UNK_0800)) {
                        ReboundStoneBounce1(0x800);
                    }
                    if (colliderFlags == EFFECT_UNK_8000) {
                        ReboundStoneBounce2(0x200);
                    }
                    if (colliderFlags == EFFECT_UNK_8000 + EFFECT_UNK_1000) {
                        ReboundStoneBounce2(0x12E);
                    }
                    if (colliderFlags == EFFECT_UNK_8000 + EFFECT_UNK_2000) {
                        ReboundStoneBounce2(0xA0);
                    }
                    if (colliderFlags == EFFECT_UNK_8000 + EFFECT_UNK_4000) {
                        ReboundStoneBounce2(0x600);
                    }
                    if (colliderFlags ==
                        EFFECT_UNK_8000 + EFFECT_UNK_4000 + EFFECT_UNK_1000) {
                        ReboundStoneBounce2(0x6D2);
                    }
                    if (colliderFlags ==
                        EFFECT_UNK_8000 + EFFECT_UNK_4000 + EFFECT_UNK_2000) {
                        ReboundStoneBounce2(0x760);
                    }
                }
                if (deltaY < 0) {
                    if ((colliderFlags == EFFECT_NONE) ||
                        (colliderFlags & EFFECT_UNK_8000)) {
                        ReboundStoneBounce1(0x800);
                    }
                    if (colliderFlags == EFFECT_UNK_0800) {
                        ReboundStoneBounce2(0xE00);
                    }
                    if (colliderFlags == EFFECT_UNK_0800 + EFFECT_UNK_1000) {
                        ReboundStoneBounce2(0xED2);
                    }
                    if (colliderFlags == EFFECT_UNK_0800 + EFFECT_UNK_2000) {
                        ReboundStoneBounce2(0xF60);
                    }
                    if (colliderFlags == EFFECT_UNK_0800 + EFFECT_UNK_4000) {
                        ReboundStoneBounce2(0xA00);
                    }
                    if (colliderFlags ==
                        EFFECT_UNK_0800 + EFFECT_UNK_4000 + EFFECT_UNK_1000) {
                        ReboundStoneBounce2(0x92E);
                    }
                    if (colliderFlags ==
                        EFFECT_UNK_0800 + EFFECT_UNK_4000 + EFFECT_UNK_2000) {
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
                 EFFECT_UNK_1000 | EFFECT_UNK_0800 | EFFECT_BLOCK);
            if (colliderFlags & EFFECT_SOLID) {
                colliderFlags &=
                    EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                    EFFECT_UNK_1000 | EFFECT_UNK_0800 | EFFECT_UNK_0400 |
                    EFFECT_UNK_0200 | EFFECT_UNK_0100;
                // Cases when traveling right
                if (deltaX > 0) {
                    if (colliderFlags == EFFECT_NONE ||
                        TEST_BITS(
                            colliderFlags, EFFECT_UNK_4000 | EFFECT_UNK_0800) ||
                        TEST_BITS(
                            colliderFlags, EFFECT_UNK_8000 | EFFECT_UNK_4000)) {
                        ReboundStoneBounce1(0x400);
                    }
                    if (colliderFlags == EFFECT_UNK_0800) {
                        ReboundStoneBounce2(0xE00);
                    }
                    if (colliderFlags == EFFECT_UNK_0800 + EFFECT_UNK_1000) {
                        ReboundStoneBounce2(0xED2);
                    }
                    if (colliderFlags == EFFECT_UNK_0800 + EFFECT_UNK_2000) {
                        ReboundStoneBounce2(0xF60);
                    }
                    if (colliderFlags == EFFECT_UNK_8000) {
                        ReboundStoneBounce2(0x200);
                    }
                    if (colliderFlags == EFFECT_UNK_8000 + EFFECT_UNK_1000) {
                        ReboundStoneBounce2(0x12E);
                    }
                    if (colliderFlags == EFFECT_UNK_8000 + EFFECT_UNK_2000) {
                        ReboundStoneBounce2(0xA0);
                    }
                }
                // Cases when traveling left
                if (deltaX < 0) {
                    if ((colliderFlags == EFFECT_NONE) ||
                        ((colliderFlags &
                          (EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                         EFFECT_UNK_0800) ||
                        ((colliderFlags &
                          (EFFECT_UNK_8000 | EFFECT_UNK_4000)) ==
                         EFFECT_UNK_8000)) {
                        ReboundStoneBounce1(0x400);
                    }
                    if (colliderFlags == EFFECT_UNK_0800 + EFFECT_UNK_4000) {
                        ReboundStoneBounce2(0xA00);
                    }
                    if (colliderFlags ==
                        EFFECT_UNK_0800 + EFFECT_UNK_4000 + EFFECT_UNK_1000) {
                        ReboundStoneBounce2(0x92E);
                    }
                    if (colliderFlags ==
                        EFFECT_UNK_0800 + EFFECT_UNK_4000 + EFFECT_UNK_2000) {
                        ReboundStoneBounce2(0x8A0);
                    }
                    if (colliderFlags == EFFECT_UNK_8000 + EFFECT_UNK_4000) {
                        ReboundStoneBounce2(0x600);
                    }
                    if (colliderFlags ==
                        EFFECT_UNK_8000 + EFFECT_UNK_4000 + EFFECT_UNK_1000) {
                        ReboundStoneBounce2(0x6D2);
                    }
                    if (colliderFlags ==
                        EFFECT_UNK_8000 + EFFECT_UNK_4000 + EFFECT_UNK_2000) {
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

    block_93:
        if (self->ext.reboundStone.unk82) {
            CreateEntFactoryFromEntity(self, 10, 0);
            g_api.PlaySfx(SFX_UI_SUBWEAPON_TINK);
        }
        if (self->posX.i.hi < -0x40 || self->posX.i.hi > 0x140 ||
            self->posY.i.hi < -0x40 || self->posY.i.hi > 0x140 ||
            self->ext.reboundStone.unk80 == 7) {
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
        playerX = self->posX.i.hi;
        playerY = self->posY.i.hi;
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
        if (self->ext.reboundStone.unk82 && i == self->ext.reboundStone.unk80) {
            prim->x0 = playerX;
            prim->y0 = playerY;
            prim->drawMode &= ~DRAW_HIDE;
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
                if (colliderFlags < prim->r1) {
                    prim->r1 -= colliderFlags;
                }
                prim->r0 = prim->r1;
                if (prim->g1 > (colliderFlags / 2)) {
                    prim->g1 -= colliderFlags / 2;
                }
                prim->g0 = prim->g1;
            }
        }
    }
}

s32 UpdateUnarmedAnim(s8*, AnimationFrame*);
extern EInit D_us_80180440;
extern EInit D_us_8018044C;
extern DopWeaponAnimation D_us_80184278[];

// Similar to DRA's EntityUnarmedAttack
void DopplegangerUnarmedAttack(Entity* self) {
    EInit* var_a0;
    s16 animIndex;
    DopWeaponAnimation* anim;

    animIndex = (self->params & 0x7FFF) >> 8;
    self->posX.val = DOPPLEGANGER.posX.val;
    self->posY.val = DOPPLEGANGER.posY.val;
    self->facingLeft = DOPPLEGANGER.facingLeft;
    anim = &D_us_80184278[animIndex];

    if (DOPPLEGANGER.ext.player.anim < anim->frameStart ||
        DOPPLEGANGER.ext.player.anim >= (anim->frameStart + 7) ||
        !g_Dop.unk46) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        var_a0 = D_us_80180440;
        if (animIndex != 0) {
            var_a0 = D_us_8018044C;
        }
        InitializeEntity(var_a0);
        if (g_Dop.status & PLAYER_STATUS_POISON) {
            self->attack /= 2;
        }
        self->zPriority = DOPPLEGANGER.zPriority - 2;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->flags = FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED;
        self->step = Dop_Stand;
    }
    self->ext.weapon.anim = DOPPLEGANGER.ext.player.anim - anim->frameStart;
    if (DOPPLEGANGER.poseTimer == 1 && DOPPLEGANGER.pose == anim->soundFrame) {
        g_api.PlaySfx(anim->soundId);
    }
    if (UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
    }
}

extern EInit EInitSubwpnKnife;

void EntitySubwpnKnife(Entity* self) {
    Collider collider;
    Primitive* prim;
    s32 i;
    s16 offsetX;
    s16 offsetY;
    s16 angle1;
    s16 angle2;
    s16 angle3;
    s16 angle4;
    s16 x;
    s16 y;
    s16 xCol;
    s32 modX;
    s32 modY;

    switch (self->step) {
    case DAGGER_INIT:
        InitializeEntity(EInitSubwpnKnife);
        if (g_Dop.status & PLAYER_STATUS_POISON) {
            self->attack = self->attack / 2;
        }

        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->facingLeft = DOPPLEGANGER.facingLeft;
        self->hitboxWidth = 8;
        self->hitboxHeight = 5;
        self->hitboxOffX = 4;
        self->hitboxOffY = 0;
        if (!(g_Dop.status & PLAYER_STATUS_CROUCH)) {
            self->posY.i.hi -= 9;
        }
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1C;
        prim->clut = PAL_UNK_1AB;
        prim->u0 = prim->u1 = 0x18;
        prim->v0 = prim->v2 = 0x18;
        prim->u2 = prim->u3 = 0x20;
        prim->v1 = prim->v3 = 0;
        prim->priority = DOPPLEGANGER.zPriority + 2;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;

        prim = prim->next;
        prim->type = PRIM_LINE_G2;
        prim->priority = DOPPLEGANGER.zPriority + 2;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE | DRAW_UNK02 | DRAW_TRANSP;
        prim->r0 = 0x7F;
        prim->g0 = 0x3F;
        prim->b0 = 0;
        SetSpeedX(FIX(8));
        g_api.PlaySfx(SFX_WEAPON_SWISH_C);
        g_Dop.timers[ALU_T_USE_SUBWPN] = 4;
        break;
    case DAGGER_FLYING:
        self->ext.timer.t++;
        if (self->velocityX > 0) {
            xCol = 8;
        }
        if (self->velocityX < 0) {
            xCol = -8;
        }

        for (i = 0; i < 8; i++) {
            if (self->velocityX > 0) {
                self->posX.i.hi++;
            }
            if (self->velocityX < 0) {
                self->posX.i.hi--;
            }
            g_api.CheckCollision(
                self->posX.i.hi + xCol, self->posY.i.hi, &collider, 0);
            if (collider.effects & EFFECT_BLOCK || (self->flags & FLAG_DEAD)) {
                self->ext.timer.t = 64;
                self->velocityX = -(self->velocityX >> 3);
                self->velocityY = FIX(-2.5);
                self->hitboxState = 0;
                self->posX.i.hi += xCol;
                CreateEntFactoryFromEntity(
                    self, FACTORY(BP_REBOUND_STONE_HIT, 0), 0);
                self->posX.i.hi -= xCol;
                if (collider.effects & EFFECT_BLOCK) {
                    // n.b.! this is the same sound effect as the other side
                    //       of the branch. this only effects PSP
                    g_api.PlaySfx(SFX_UI_SUBWEAPON_TINK);
                } else {
                    // n.b.! this is the same sound effect as the other side
                    //       of the branch. this only effects PSP
                    g_api.PlaySfx(SFX_UI_SUBWEAPON_TINK);
                }
                self->step++;
                return;
            }
        }
        if (self->hitFlags & 0x80) {
            self->ext.timer.t = 4;
            self->step = DAGGER_HIT_ENEMY;
            self->hitboxState = 0;
            return;
        }
        x = self->posX.i.hi;
        y = self->posY.i.hi;
        offsetX = 12;
        offsetY = 8;
        if (self->facingLeft) {
            offsetX = -offsetX;
            offsetY = -offsetY;
        }
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = x - offsetX;
        prim->y0 = y - 4;
        prim->x1 = x + offsetX;
        prim->y1 = y - 4;
        prim->x2 = x - offsetX;
        prim->y2 = y + 4;
        prim->x3 = x + offsetX;
        prim->y3 = y + 4;
        prim->clut = PAL_UNK_1AB;
        (g_GameTimer >> 1) & 1; // no-op
        prim->drawMode &= ~DRAW_HIDE;
        prim = prim->next;
        prim->x0 = x - offsetY;
        prim->y0 = y - 1;
        prim->x1 = x - (offsetX * (self->ext.timer.t / 2));
        prim->y1 = y - 1;
        prim->drawMode &= ~DRAW_HIDE;
        if (self->step != DAGGER_FLYING) {
            prim->drawMode |= DRAW_HIDE;
            return;
        }
        break;
    case DAGGER_BOUNCE:
        prim = &g_PrimBuf[self->primIndex];
        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
            return;
        }
        if (self->ext.timer.t == 0x20) {
            prim->drawMode |=
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) = PGREY(prim, 3) =
                0x60;
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY += FIX(0.125);
        x = self->posX.i.hi;
        y = self->posY.i.hi;
        offsetX = 12;
        if (self->facingLeft == 0) {
            angle1 = 0x800 - 0xD2;
            angle2 = 0xD2;
            angle3 = 0x800 + 0xD2;
            angle4 = -0xD2;
            self->rotate -= ROT(11.25);
        } else {
            angle2 = 0x800 - 0xD2;
            angle1 = 0xD2;
            angle4 = 0x800 + 0xD2;
            angle3 = -0xD2;
            self->rotate += ROT(11.25);
        }
        angle1 += self->rotate;
        angle2 += self->rotate;
        angle3 += self->rotate;
        angle4 += self->rotate;
        if (self->facingLeft) {
            offsetX = -offsetX;
        }
        prim = &g_PrimBuf[self->primIndex];
        modX = (rcos(angle1) * 0xCA0) >> 0x14;
        modY = -(rsin(angle1) * 0xCA0) >> 0x14;
        prim->x0 = x + (s16)modX;
        prim->y0 = y - (s16)modY;
        modX = (rcos(angle2) * 0xCA0) >> 0x14;
        modY = -(rsin(angle2) * 0xCA0) >> 0x14;
        prim->x1 = x + (s16)modX;
        prim->y1 = y - (s16)modY;
        modX = (rcos(angle3) * 0xCA0) >> 0x14;
        modY = -(rsin(angle3) * 0xCA0) >> 0x14;
        prim->x2 = x + (s16)modX;
        prim->y2 = y - (s16)modY;
        modX = (rcos(angle4) * 0xCA0) >> 0x14;
        modY = -(rsin(angle4) * 0xCA0) >> 0x14;
        prim->x3 = x + (s16)modX;
        prim->y3 = y - (s16)modY;
        prim->clut = PAL_UNK_1AB;

        (g_GameTimer >> 1) & 1; // no-op
        if (self->ext.timer.t < 0x21) {
            prim->r0 -= 2;
            prim->g0 = prim->b0 = PGREY(prim, 1) = PGREY(prim, 2) =
                PGREY(prim, 3) = prim->r0;
        }
        prim->drawMode &= ~DRAW_HIDE;
        prim = prim->next;
        prim->drawMode |= DRAW_HIDE;
        break;
    case DAGGER_HIT_ENEMY:
        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
