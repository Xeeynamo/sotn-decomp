#include "ric.h"

// Entity ID #7. Made by blueprint 6. Comes from subweapon 3. Holy water!
// Not at all the same as DRA's.
void EntityHolyWater(Entity* self) {
    s16 argY;
    s32 collision_result;
    s32 tempXVel;
    s32 trigresult;
    s32 trigtemp;

    if (self->step >= 3) {
        self->posY.i.hi += 5;
    }
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_08000000;
        self->animSet = ANIMSET_OVL(0x12);
        self->animCurFrame = 0x23;
        self->zPriority = PLAYER.zPriority + 2;
        self->unk5A = 0x46;
        self->palette = 0x812F;
        self->posX.i.hi = self->posX.i.hi;
        self->posY.i.hi = self->posY.i.hi - 0x10;
        self->ext.holywater.angle = (rand() & 0x7F) + 0xDC0;
        if (PLAYER.facingLeft == 1) {
            self->ext.holywater.angle = (rand() & 0x7F) + 0x9C0;
        }

        trigresult = rcos(self->ext.holywater.angle);
        trigtemp = trigresult * 16;
        self->velocityX = (trigresult * 32 + trigtemp) << 9 >> 8;

        trigresult = rsin(self->ext.holywater.angle);
        trigtemp = trigresult * 16;
        self->velocityY = -((trigresult * 32 + trigtemp) << 9) >> 8;

        self->ext.factory.unkB0 = 3;
        func_8015FAB8(self);
        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        self->ext.holywater.unk80 = 0x200;
        self->step += 1;
        break;
    case 1:
        self->posY.val += self->velocityY;
        collision_result = CheckHolyWaterCollision(0, 0);
        self->posX.val += self->velocityX;

        if (self->velocityX < 0) {
            argY = -4;
        } else {
            argY = 4;
        }
        collision_result |= func_8016840C(-7, argY);
        if (collision_result & 2) {
            self->velocityX = -self->velocityX;
            collision_result = 1;
        }
        if ((collision_result & 1) || (self->hitFlags != 0)) {
            g_api.CreateEntFactoryFromEntity(self, 0x28U, 0);
            g_api.PlaySfx(0x68A);
            self->ext.holywater.timer = 0x50;
            self->animSet = 0;
            self->hitboxState = 0;
            self->step = 3;
            self->velocityX >>= 2;
        }
        break;
    case 2:
        if (--self->ext.holywater.timer == 0) {
            self->ext.holywater.timer = 0x50;
            self->velocityX >>= 2;
            self->step++;
        }
        break;
    case 3:
        if (!(self->ext.holywater.timer & 3)) {
            CreateEntFactoryFromEntity(
                self, (self->ext.holywater.unk82 << 0x10) | 7, 0);
            // weirdly nonmatching with ++;
            self->ext.holywater.unk82 = self->ext.holywater.unk82 + 1;
            self->velocityX -= (self->velocityX / 32);
        }
        collision_result = CheckHolyWaterCollision(6, 0);
        tempXVel = self->velocityX;
        if (self->velocityX < 0) {
            if ((collision_result & 0xF000) == 0xC000) {
                tempXVel = tempXVel * 10 / 16;
            }
            if ((collision_result & 0xF000) == 0xD000) {
                tempXVel = tempXVel * 13 / 16;
            }
        }
        if (self->velocityX > 0) {
            if ((collision_result & 0xF000) == 0x8000) {
                tempXVel = tempXVel * 10 / 16;
            }
            if ((collision_result & 0xF000) == 0x9000) {
                tempXVel = tempXVel * 13 / 16;
            }
        }
        self->posX.val += tempXVel;
        if (self->velocityX < 0) {
            argY = -4;
        } else {
            argY = 4;
        }
        collision_result |= func_8016840C(-7, argY);
        if (!(collision_result & 1)) {
            self->velocityX >>= 1;
            self->step++;
        }
        break;
    case 4:
        if (!(self->ext.holywater.timer & 3)) {
            CreateEntFactoryFromEntity(
                self, FACTORY(self->ext.holywater.unk82 * 0x100, 7), 0);
            self->ext.holywater.unk82 = self->ext.holywater.unk82 + 1;
        }
        self->velocityY += FIX(12.0 / 128);
        if (self->velocityY > FIX(4)) {
            self->velocityY = FIX(4);
        }
        self->posY.val += self->velocityY;
        collision_result = CheckHolyWaterCollision(0, 0);
        self->posX.val += self->velocityX;
        if (self->velocityX < 0) {
            argY = -4;
        } else {
            argY = 4;
        }
        collision_result |= func_8016840C(-7, argY);
        if ((collision_result & 1)) {
            self->velocityX *= 2;
            self->step--;
        }
        break;
    case 5:
        break;
    }
    if (self->step >= 3) {
        if (--self->ext.holywater.timer < 0) {
            DestroyEntity(self);
            return;
        }
        if (self->ext.holywater.timer == 2) {
            self->step = 5;
        }
        self->animCurFrame = 0;
        self->hitboxState = 0;
        self->posY.i.hi -= 5;
    }
    g_Player.D_80072F00[3] = 2;
}

// Entity ID #8. Blueprint 7.
void EntityHolyWaterFlame(Entity* self) {
    s16 sp10[5];
    s16 sp20[5];
    s16 pad[2];
    Primitive* prim;
    s16 angleTemp;
    s32 angle;
    s32 i;
    s32 hex80;
    u8 randR;
    u8 randG;
    u8 randB;
    u8 primUBase;
    u8 primVBase;
    s16* primYPtr;
    s32 var_s4;
    s16 temp_v0_2;
    s32 doubleparams;

    s16 upperParams = self->params >> 8;

    primUBase = D_80155D9C[(g_GameTimer & 7)].x;
    primVBase = D_80155D9C[(g_GameTimer & 7)].y;
    switch (self->step) {
    case 0:
        randR = (rand() & 0x3F) + 0x2F;
        randG = (rand() & 0x3F) + 0x6F;
        randB = (rand() & 0x7F) + 0x6F;
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        i = 0;
        while (prim != NULL) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = randR;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = randG;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = randB;
            if (i == 0) {
                prim->b0 = prim->b1 = prim->g0 = prim->g1 = prim->r0 =
                    prim->r1 = 0;
            }
            prim->clut = 0x1B0;
            prim->tpage = 0x1A;
            prim->priority = PLAYER.zPriority + 2;
            prim->drawMode = 0x7F;
            prim = prim->next;
            i++;
        }
        self->flags = FLAG_UNK_08000000 | FLAG_HAS_PRIMS;
        self->ext.timer.t = 1;
        self->step += 1;
        break;

    case 1:
        if (--self->ext.timer.t == 0) {
            self->ext.factory.unkB0 = 0xB;
            func_8015FAB8(self);
            self->hitboxWidth = 4;
            self->ext.factory.unk84 = (s16)self->hitboxState;
            self->posY.i.hi = self->posY.i.hi - 0xA;
            CreateEntFactoryFromEntity(self, 0x30004U, 0);
            self->ext.timer.t = 0x50;
            self->posY.i.hi = self->posY.i.hi + 0xA;
            self->ext.holywaterflame.unk80 = (rand() & 0xF) + 0x12;
            self->ext.holywaterflame.angle = rand() & 0xFFF;
            self->step += 1;
        }
        break;
    case 2:
        if (self->facingLeft) {
            var_s4 = 1;
        } else {
            var_s4 = -1;
        }
        angleTemp = self->ext.holywaterflame.angle;
        self->ext.holywaterflame.angle += 0xC0;
        angle = angleTemp;
        for (i = 0; i < 4; i++) {
            sp10[i] = self->posX.i.hi + (rsin(angle) >> 0xA);
            angle += 0x400;
        }
        sp10[4] = self->posX.i.hi;
        sp10[0] = var_s4 + self->posX.i.hi;
        temp_v0_2 = rsin((s16)((self->ext.timer.t * 64) + 0x800)) >> 8;
        temp_v0_2 += self->ext.holywaterflame.unk80;
        temp_v0_2 = temp_v0_2 * 3 >> 1;
        sp20[0] = self->posY.i.hi - temp_v0_2;
        sp20[4] = self->posY.i.hi;
        sp20[2] = (sp20[0] + sp20[4]) / 2;
        sp20[1] = (sp20[0] + sp20[2]) / 2;
        sp20[3] = (sp20[2] + sp20[4]) / 2;
        prim = &g_PrimBuf[self->primIndex];
        if (--self->ext.timer.t < 0) {
            DestroyEntity(self);
            return;
        }
        if (self->ext.timer.t & 3) {
            self->hitboxState = 0;
        } else {
            self->hitboxState = self->ext.holywaterflame.unk84;
        }
        if (self->ext.timer.t < 0x15) {
            self->hitboxState = 0;
        }
        i = 0;
        while (prim != NULL) {
            if (upperParams * 2 + 0x18 >= self->ext.timer.t) {
                if (prim->g0 >= 10) {
                    prim->g0 -= 5;
                }
                if (prim->b0 >= 10) {
                    prim->b0 -= 5;
                }
                if (prim->r0 >= 16) {
                    prim->r0 -= 8;
                }
                prim->g1 = prim->g2 = prim->g3 = prim->g0;
                prim->r1 = prim->r2 = prim->r3 = prim->r0;
                prim->b1 = prim->b2 = prim->b3 = prim->b0;
            }
            prim->x0 = sp10[i] - 8;
            prim->x1 = sp10[i] + 8;
            prim->y0 = sp10[i + 8];
            prim->y1 = sp10[i + 8];
            prim->x2 = sp10[i + 1] - 8;
            prim->x3 = sp10[i + 1] + 8;
            prim->y2 = sp20[i + 1];
            prim->y3 = sp20[i + 1];
            prim->drawMode &= ~DRAW_HIDE;
            hex80 = 0x80;
            prim->u0 = prim->u1 = primUBase - ((i * 7) + hex80);
            prim->u2 = prim->u3 = primUBase - (((i + 1) * 7) + hex80);
            prim->v0 = prim->v2 = primVBase - hex80;
            prim->v1 = prim->v3 = primVBase - 0x70;
            if ((sp20[4] - sp20[0]) < 7) {
                prim->drawMode |= DRAW_HIDE;
                DestroyEntity(self);
                return;
            }
            i++;
            prim = prim->next;
        }
        self->hitboxHeight = temp_v0_2 >> 1;
        self->hitboxOffY = (-temp_v0_2 >> 1);
    }
    g_Player.D_80072F00[3] = 2;
}

// Entity 13. Made by blueprint 13. That's from subweapon 12.
// That's the crash for subweapon 4. That's the cross.
void EntitySubwpnCrashCross(Entity* self) {
    Primitive* prim;
    s16 right;
    s16 left;
    s32 var_v0;
    s32 temp_three;
    u16 three = 3;
    u16 one = 1;

    self->posY.i.hi = 0x78;
    self->posX.i.hi = PLAYER.posX.i.hi;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        self->ext.crashcross.unk80 = 1;
        self->zPriority = 0xC2;
        self->ext.factory.unkB0 = 0xC;
        func_8015FAB8(self);
        LoadImage(&D_80155E3C, D_80155DDC);
        g_api.PlaySfx(0x6DF);
        g_api.PlaySfx(0x636);
        self->step += 1;
        break;
    case 1:
        // FAKE, register reuse thing
        one = three * 2;
        self->ext.crashcross.unk7E = three + self->ext.crashcross.unk7E;
        self->ext.crashcross.unk82 += one;
        if ((u8)self->ext.crashcross.unk7E >= 0x70U) {
            CreateEntFactoryFromEntity(self, FACTORY(0, 14), 0);
            CreateEntFactoryFromEntity(self, FACTORY(0, 34), 0);
            self->step += 1;
        }
        break;
    case 2:
        if (g_Timer & 1) {
            self->ext.crashcross.unk80 += one * 2;
            self->ext.crashcross.unk7C = one + self->ext.crashcross.unk7C;
            if (self->ext.crashcross.unk80 >= 0x2CU) {
                self->ext.crashcross.unk84 = 0x80;
                self->step += 1;
            }
        }
        break;
    case 3:
        if (--self->ext.crashcross.unk84 == 0) {
            g_api.func_801027C4(0);
            left = self->posX.i.hi - self->ext.crashcross.unk7C;
            ;
            if (left < 0) {
                left = 0;
            }
            right = self->posX.i.hi + self->ext.crashcross.unk7C;
            if (right >= 0x100) {
                right = 0xFF;
            }
            g_api.PlaySfx(0x62F);
            self->step += 1;
        }
        break;
    case 4:
        temp_three = one * 2;
        temp_three |= one;
        var_v0 = self->posX.i.hi - 0x80;
        self->ext.crashcross.unk7C =
            (((temp_three) * ((s16)(var_v0 > 0 ? var_v0 : -var_v0) + 0x80)) /
             112) +
            self->ext.crashcross.unk7C;

        left = self->posX.i.hi - self->ext.crashcross.unk7C;
        if (left < 0) {
            left = 0;
        }
        right = self->posX.i.hi + self->ext.crashcross.unk7C;
        if (right >= 0x100) {
            right = 0xFF;
        }
        if ((right - left) >= 0xF9) {
            g_Player.unk4E = 1;
            DestroyEntity(self);
            return;
        }
        break;
    }
    self->hitboxOffY = 0;
    self->hitboxHeight = self->ext.crashcross.unk7E;
    if (self->step == 4) {
        self->hitboxWidth = ((right - left) >> 1);
        self->hitboxOffX = ((left + right) >> 1) - self->posX.i.hi;
    } else {
        self->hitboxOffX = 0;
        self->hitboxWidth = self->ext.crashcross.unk7C;
    }
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = prim->x2 = self->posX.i.hi - self->ext.crashcross.unk7C;
    prim->y1 = prim->y0 = self->posY.i.hi - self->ext.crashcross.unk7E;
    prim->x1 = prim->x3 = prim->x0 + self->ext.crashcross.unk80;
    prim->y2 = prim->y3 = prim->y0 + self->ext.crashcross.unk82;
    prim->u0 = prim->u2 = 1;
    prim->u1 = prim->u3 = 0x30;
    prim->v0 = prim->v1 = prim->v2 = prim->v3 = 0xF8;
    prim->tpage = 0x11C;
    if (self->step == 4) {
        prim->x0 = prim->x2 = left;
        prim->x1 = prim->x3 = right;
    }
    prim->drawMode = 0x31;
    prim->priority = self->zPriority;
    g_Player.D_80072F00[3] = 2;
    return;
}

// Entity ID #21. Blueprint 22. Called in func_8015B348.
// Creates the white column around Richter when he is revived in the Prologue.
void EntityRichterRevivalColumn(Entity* self) {
    Primitive* prim;
    u32 three = 3;
    u32 one = 1;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_UNK_10000;
        self->posY.i.hi = 0x78;
        self->ext.ricColumn.unk80 = 1;
        self->zPriority = 0xC2;
        LoadImage(&D_80155E3C, &D_80155DDC);
        self->step += 1;
        break;
    case 1:
        self->ext.ricColumn.unk7E = three + self->ext.ricColumn.unk7E;
        self->ext.ricColumn.unk82 += three * 2;
        if ((u8)self->ext.ricColumn.unk7E >= 0x70U) {
            self->step += 1;
        }
        break;
    case 2:
        if (g_Timer & 1) {
            self->ext.ricColumn.unk80 += one * 2;
            self->ext.ricColumn.unk7C = one + self->ext.ricColumn.unk7C;
            if (self->ext.ricColumn.unk80 >= 0x2CU) {
                self->ext.ricColumn.unk84 = 0xA0;
                self->step += 1;
            }
        }
        break;
    case 3:
        if (--self->ext.ricColumn.unk84 == 0) {
            self->step += 1;
        }
        break;
    case 4:
        if (g_Timer & 1) {
            self->ext.ricColumn.unk80 -= one * 4;
            self->ext.ricColumn.unk7C -= (one * 2);
            if (self->ext.ricColumn.unk80 < 4U) {
                DestroyEntity(self);
                return;
            }
        }
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = prim->x2 = self->posX.i.hi - self->ext.ricColumn.unk7C;
    prim->y1 = prim->y0 = self->posY.i.hi - self->ext.factory.unk7E;
    prim->x1 = prim->x3 = prim->x0 + self->ext.ricColumn.unk80;
    prim->y2 = prim->y3 = prim->y0 + self->ext.ricColumn.unk82;
    prim->u0 = prim->u2 = 1;
    prim->u1 = prim->u3 = 0x30;
    prim->v0 = prim->v1 = prim->v2 = prim->v3 = 0xF8;
    prim->tpage = 0x11C;
    if (g_Timer & 1) {
        prim->drawMode = 0x31;
    } else {
        prim->drawMode = DRAW_HIDE;
    }
    prim->priority = self->zPriority;
}

void EntityCrossBoomerang(Entity* self) {
    s32 xAccel;
    s32 xDist;
    s32 yDist;
    Point16* temp_a0;
    s16 playerHitboxX;
    s16 playerHitboxY;

    f32 tempX;

    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 | FLAG_UNK_100000;
        self->ext.crossBoomerang.unk84 = &D_80175088[D_80175888];
        D_80175888++;
        D_80175888 &= 3;
        CreateEntFactoryFromEntity(self, FACTORY(0, 5), 0);
        self->animSet = ANIMSET_OVL(0x11);
        self->unk5A = 0x66;
        self->unk4C = D_80155E44;
        self->facingLeft = PLAYER.facingLeft;
        self->zPriority = PLAYER.zPriority;
        SetSpeedX(FIX(3.5625));
        self->drawFlags = 4;
        self->rotZ = 0xC00;
        self->ext.factory.unkB0 = 4;
        func_8015FAB8(self);
        self->hitboxHeight = self->hitboxWidth = 8;
        self->posY.i.hi -= 8;
        g_api.PlaySfx(0x69F);
        self->step++;
        break;
    case 1:
        if (PLAYER.animFrameIdx == 1) {
            self->step++;
        }
        /* fallthrough */
    case 2:
        // First phase. We spin at 0x80 angle units per frame.
        // Velocity gets decremented by 1/16 per frame until we slow
        // down to less than 0.75.
        self->rotZ -= 0x80;
        self->posX.val += self->velocityX;
        xAccel = self->facingLeft ? FIX(-1.0 / 16) : FIX(1.0 / 16);
        self->velocityX -= xAccel;
        if (ABS(self->velocityX) < FIX(0.75)) {
            self->step++;
        }
        break;
    case 3:
        // Second phase. Once we are slow, we spin twice as fast, and then
        // wait until our speed gets higher once again (turned around).
        self->rotZ -= 0x100;
        self->posX.val += self->velocityX;
        xAccel = self->facingLeft ? FIX(-1.0 / 16) : FIX(1.0 / 16);
        self->velocityX -= xAccel;
        if (ABS(self->velocityX) > FIX(0.75)) {
            self->step++;
        }
        break;
    case 4:
        // Third phase. We've now sped up and we're coming back.
        // Increase speed until a terminal velocity of 2.5.
        xAccel = self->facingLeft ? FIX(-1.0 / 16) : FIX(1.0 / 16);
        self->velocityX -= xAccel;
        if (ABS(self->velocityX) > FIX(2.5)) {
            self->step++;
        }
        /* fallthrough */
    case 5:
        // FAKE, unfortunate need to preload this.
        tempX = self->posX;
        // Now we check 2 conditions. If we're within the player's hitbox...
        playerHitboxX = (PLAYER.posX.i.hi + PLAYER.hitboxOffX);
        playerHitboxY = (PLAYER.posY.i.hi + PLAYER.hitboxOffY);
        xDist = tempX.i.hi - playerHitboxX;
        if (ABS(xDist) < (PLAYER.hitboxWidth + self->hitboxWidth)) {
            yDist = self->posY.i.hi - playerHitboxY;
            if (ABS(yDist) < (PLAYER.hitboxHeight + self->hitboxHeight)) {
                // ... Then we go to step 7 to be destroyed.
                self->step = 7;
                self->ext.crossBoomerang.timer = 0x20;
                return;
            }
        }
        // Alternatively, if we're offscreen, we will also be destroyed.
        if ((self->facingLeft == 0 && self->posX.i.hi < -0x20) ||
            (self->facingLeft != 0 && self->posX.i.hi >= 0x121)) {
            self->step = 7;
            self->ext.crossBoomerang.timer = 0x20;
            return;
        }
        // Otherwise, we keep trucking. spin at the slower rate again.
        self->rotZ -= 0x80;
        self->posX.val += self->velocityX;
        break;

    case 7:
        if (--self->ext.crossBoomerang.timer == 0) {
            DestroyEntity(self);
            return;
        }
        self->hitboxState = 0;
        self->animSet = 0;
        self->posX.val += self->velocityX;
        break;
    }
    // We will increment through these states, creating trails.
    // Factory 3 is entity #4, func_80169C10. Appears to make tiny sparkles.
    // Factory 4 is entity #5, func_8016147C. Appears to make a "shadow" of the
    // cross boomerang.
    self->ext.crossBoomerang.unk7E++;
    if (1 < self->step && self->step < 6) {
        if ((self->ext.crossBoomerang.unk7E & 0xF) == 1) {
            CreateEntFactoryFromEntity(self, FACTORY(0, 3), 0);
        }
        if ((self->ext.crossBoomerang.unk7E & 0xF) == 4) {
            CreateEntFactoryFromEntity(self, FACTORY(0x600, 4), 0);
        }
        if ((self->ext.crossBoomerang.unk7E & 0xF) == 6) {
            CreateEntFactoryFromEntity(self, FACTORY(0, 3), 0);
        }
        if ((self->ext.crossBoomerang.unk7E & 0xF) == 8) {
            CreateEntFactoryFromEntity(self, FACTORY(0x600, 4), 0);
        }
        if ((self->ext.crossBoomerang.unk7E & 0xF) == 12) {
            CreateEntFactoryFromEntity(self, FACTORY(0x600, 4), 0);
        }
        if ((self->ext.crossBoomerang.unk7E & 0xF) == 11) {
            CreateEntFactoryFromEntity(self, FACTORY(0, 3), 0);
        }
    }
    // Applies a flickering effect
    if (!((g_GameTimer >> 1) & 1)) {
        self->palette = 0x81B1;
    } else {
        self->palette = 0x81B0;
    }
    temp_a0 = self->ext.crossBoomerang.unk84;
    // This indexes into the unk84 array.
    // Better way would have been temp_a0 = &unk84[unk80].
    temp_a0 += self->ext.crossBoomerang.unk80;
    temp_a0->x = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    temp_a0->y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    self->ext.crossBoomerang.unk80++;
    self->ext.crossBoomerang.unk80 &= 0x3F;
    g_Player.D_80072F00[3] = 2;
}

void func_80169C10(Entity* entity) {
    Primitive* prim;
    s16 primIndex;
    s32 PosX = 8;
    s32 PosY = 4;

    switch (entity->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        entity->primIndex = primIndex;
        if (primIndex != -1) {
            entity->flags = FLAG_UNK_08000000 | FLAG_HAS_PRIMS;
            entity->velocityY = FIX(0.5);
            entity->posX.i.hi =
                ((u16)entity->posX.i.hi - PosX) + (rand() & 0xF);
            entity->posY.i.hi =
                ((u16)entity->posY.i.hi - PosY) + (rand() & 0xF);
            prim = &g_PrimBuf[entity->primIndex];
            prim->clut = 0x1B0;
            prim->tpage = 0x1A;
            prim->b0 = 0;
            prim->b1 = 0;
            prim->priority = entity->zPriority;
            prim->priority = prim->priority + 4;
            prim->drawMode = 0x31;
            func_8015FDB0(prim, entity->posX.i.hi, entity->posY.i.hi);
            entity->step++;
        } else {
            DestroyEntity(entity);
        }
        break;

    default:
        entity->posY.val += entity->velocityY;
        prim = &g_PrimBuf[entity->primIndex];
        if (func_8015FDB0(prim, entity->posX.i.hi, entity->posY.i.hi) != 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

void func_80169D74(Entity* entity) {
    Multi temp;
    s16* ptr;

    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->ext.generic.unk84.unk =
            entity->ext.generic.unk8C.entityPtr->ext.generic.unk84.unk;
        entity->animSet = ANIMSET_OVL(17);
        entity->animCurFrame = D_80155E68[entity->params];
        entity->unk5A = 0x66;
        entity->palette = 0x81B0;
        entity->drawMode = DRAW_TPAGE;
        entity->facingLeft = PLAYER.facingLeft;
        entity->zPriority = PLAYER.zPriority;
        entity->drawFlags = FLAG_DRAW_ROTZ;
        entity->rotZ = 0xC00;
        entity->step++;
        break;

    case 1:
        entity->rotZ -= 0x80;
        if (entity->ext.generic.unk8C.entityPtr->step == 7) {
            entity->step++;
            entity->ext.generic.unk7C.s = (entity->params + 1) * 4;
        }
        break;

    case 2:
        entity->rotZ -= 0x80;
        entity->ext.generic.unk7C.s--;
        if (entity->ext.generic.unk7C.s == 0) {
            DestroyEntity(entity);
            return;
        }
        break;
    }
    temp = entity->ext.generic.unk84;
    ptr = temp.unk + ((u16)entity->ext.generic.unk80.modeS16.unk0 * 4);
    entity->posX.i.hi = ptr[0] - g_Tilemap.scrollX.i.hi;
    entity->posY.i.hi = ptr[1] - g_Tilemap.scrollY.i.hi;
    entity->ext.generic.unk80.modeS16.unk0 =
        (entity->ext.generic.unk80.modeS16.unk0 + 1) & 0x3F;
}

// Entity ID #32. Comes from blueprint 34.
// Surprisingly pretty different from DRA version.
void EntitySubwpnCrashCrossParticles(Entity* self) {
    Primitive* prim;
    s32 var_a2;
    s32 temp_s0;
    s32 temp_a3;
    s32 temp_t0;
    u8* temp_a1;
    s32 priority;

    s16 temp_a0;
    u8 temps0copy;

    if (self->step == 0) {
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x20);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        self->ext.timer.t = 0xC0;
        self->step += 1;
        return;
    }
    if (--self->ext.timer.t == 0) {
        DestroyEntity(self);
        return;
    }
    if ((self->ext.timer.t >= 9) && !(self->ext.timer.t & 3)) {
        for (prim = &g_PrimBuf[self->primIndex]; prim != NULL;
             prim = prim->next) {
            if (prim->r0 == 0) {
                prim->r0 = 1;
                prim->r1 = 0;
                break;
            }
        }
    }
    for (prim = &g_PrimBuf[self->primIndex]; prim != NULL; prim = prim->next) {
        if (prim->r0 == 0) {
            continue;
        }
        if (prim->r1 == 0) {
            temp_s0 = rand() & 0x3F;
            prim->g0 = (rand() % 237) + 9;
            temps0copy = temp_s0;
            prim->g1 = -0x10 - (rand() & 0x20);
            prim->clut = 0x1B0;
            prim->tpage = 0x1A;
            prim->b0 = 0;
            priority = (temp_s0 + PLAYER.zPriority) - 0x20;
            prim->drawMode = 0x31;
            prim->g3 = (temps0copy >> 2) + 4;
            prim->priority = priority;
            prim->r1++;
        } else {
            prim->g1 -= prim->g3;
            if (((u8)prim->b0 >= 6U) || ((u8)prim->g1 < 0x18U)) {
                prim->drawMode = 8;
                prim->r0 = 0;
            }
        }
        if (prim->r0 == 0) {
            continue;
        }
        temp_a1 = &D_801548F4;
        temp_a3 = prim->g0;
        temp_t0 = prim->g1;
        temp_a1 += prim->b0 * 8; // weird array indexing
        if (prim->b0 >= 3) {
            var_a2 = 4;
        } else {
            var_a2 = 8;
        }
        temp_a0 = temp_a3 - var_a2;
        prim->y1 = prim->y0 = temp_t0 - var_a2;
        prim->x0 = temp_a0;
        prim->x1 = temp_a3 + var_a2;
        prim->x2 = temp_a0;
        prim->y2 = temp_t0 + var_a2;
        prim->x3 = var_a2 + temp_a3;
        prim->y3 = var_a2 + temp_t0;
        prim->u0 = *temp_a1++;
        prim->v0 = *temp_a1++;
        prim->u1 = *temp_a1++;
        prim->v1 = *temp_a1++;
        prim->u2 = *temp_a1++;
        prim->v2 = *temp_a1++;
        prim->u3 = *temp_a1++;
        prim->v3 = *temp_a1++;
        if (!(g_GameTimer & 1)) {
            prim->b0 += 1;
        }
    }
}

// RIC entity #36. Uses RIC blueprint 67. Comes from subweapon 28.
// Subweapon 28 is the crash of subweapon 9, which is the Agunea (thunder).
void EntitySubwpnCrashAgunea(Entity* self) {
    s32 sp10;
    s32 sp18;
    Primitive* prevPrim;
    Primitive* prim;
    s32 temp_v1_3;
    s16 var_a1;
    s16 var_s0;
    s16 var_s1;
    s16 var_s2;
    s16 var_s3;
    u16 temp_s4;
    u16 temp_s5;
    u8 temp_v0_4;

    u8* arr0;
    u8* arr1;
    u8* arr2;
    s32 twentyone;

    u8 rVal;
    u8 gVal;
    u8 bVal;

    u16 tempLeft;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 5);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 | FLAG_HAS_PRIMS |
                      FLAG_UNK_20000;
        self->facingLeft = (PLAYER.facingLeft + 1) & 1;
        SetSpeedX(FIX(-2));
        self->velocityY = FIX(-6);
        tempLeft = self->facingLeft;
        self->ext.aguneaCrash.unk7C = tempLeft ? 0x400 : 0xC00;
        sp10 = 0;
        prim = &g_PrimBuf[self->primIndex];
        self->posY.i.hi -= 0xC;
        while (prim != NULL) {
            prim->tpage = 0x1C;
            prim->u0 = 0;
            prim->v0 = 0;
            prim->u1 = 0x18;
            prim->v1 = 0;
            prim->u2 = 0;
            prim->v2 = 0x28;
            prim->u3 = 0x18;
            prim->v3 = 0x28;
            prim->priority = PLAYER.zPriority - 2;
            if (sp10 != 0) {
                prim->drawMode = 0x13D;
                self->ext.aguneaCrash.unk8B[sp10] = 0;
                self->ext.aguneaCrash.unk8B[sp10 + 4] = 0;
                self->ext.aguneaCrash.unk8B[sp10 + 8] = 0;
            } else {
                prim->drawMode = 0x100 | DRAW_HIDE;
            }
            prim = prim->next;
            sp10++;
        }
        self->ext.factory.unkB0 = 2;
        func_8015FAB8(self);
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
        g_api.PlaySfx(0x60C);
        self->ext.aguneaCrash.unk98 = 0x7F;
        self->step++;
        break;
    case 1:
        if (self->facingLeft) {
            var_a1 = -0x80;
        } else {
            var_a1 = 0x80;
        }
        self->ext.aguneaCrash.unk7C = var_a1 + self->ext.aguneaCrash.unk7C;
        if (!(self->ext.aguneaCrash.unk7C & 0x3FF)) {
            g_api.func_80134714(0x60C, self->ext.aguneaCrash.unk98, 0);
            self->ext.aguneaCrash.unk98 -= 8;
            if (self->ext.aguneaCrash.unk98 < 0) {
                self->ext.aguneaCrash.unk98 = 0;
            }
        }
        self->velocityY += FIX(34.0 / 128);
        if (self->velocityY > FIX(8)) {
            self->velocityY = FIX(8);
        }
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if (self->posY.i.hi < 0x101) {
            if (self->hitFlags == 2) {
                self->velocityY = FIX(-3);
                self->hitboxState = 0;
                self->step = 2;
                self->velocityX = -(self->velocityX / 2);
            }
            break;
        }
        DestroyEntity(self);
        return;
    case 2:
        if (self->facingLeft) {
            var_a1 = 0xC0;
        } else {
            var_a1 = -0xC0;
        }
        self->ext.aguneaCrash.unk7C = var_a1 + self->ext.aguneaCrash.unk7C;
        self->velocityY += FIX(18.0 / 128);
        if (self->velocityY > FIX(8)) {
            self->velocityY = FIX(8);
        }
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if (self->posY.i.hi > 0x100) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    if (self->animFrameDuration == 0) {
        sp18 = self->animFrameIdx;
        self->ext.aguneaCrash.unk8B[sp18 + 1] = 0;
        self->ext.aguneaCrash.unk8B[sp18 + 5] = 1;
        self->ext.aguneaCrash.unk8B[sp18 + 9] = 1;
        sp18++;
        sp18 &= 3;
        self->animFrameIdx = sp18;
        self->animFrameDuration = 2;
    } else {
        self->animFrameDuration--;
    }
    sp10 = 0;
    prim = &g_PrimBuf[self->primIndex];
    prevPrim = prim;
    sp18 = ((g_GameTimer >> 1) & 1) + 0x1AB;
    while (prim != NULL) {
        prim->clut = sp18;
        if (sp10 == 0) {
            if (self->facingLeft != 0) {
                var_s0 = 0x560;
                var_s1 = 0x2A0;
                var_s2 = 0xAA0;
                var_s3 = 0xD60;
            } else {
                var_s1 = 0x560;
                var_s0 = 0x2A0;
                var_s3 = 0xAA0;
                var_s2 = 0xD60;
            }
            var_a1 = self->ext.aguneaCrash.unk7C;
            temp_s4 = self->posX.i.hi;
            temp_s5 = self->posY.i.hi;
            var_s0 += var_a1;
            var_s1 += var_a1;
            var_s2 += var_a1;
            var_s3 += var_a1;
            twentyone = 21;
            prim->x0 = temp_s4 + (((rcos(var_s0) << 4) * twentyone) >> 0x10);
            prim->y0 = temp_s5 - (((rsin(var_s0) << 4) * twentyone) >> 0x10);
            prim->x1 = temp_s4 + (((rcos(var_s1) << 4) * twentyone) >> 0x10);
            prim->y1 = temp_s5 - (((rsin(var_s1) << 4) * twentyone) >> 0x10);
            prim->x2 = temp_s4 + (((rcos(var_s2) << 4) * twentyone) >> 0x10);
            prim->y2 = temp_s5 - (((rsin(var_s2) << 4) * twentyone) >> 0x10);
            prim->x3 = temp_s4 + (((rcos(var_s3) << 4) * twentyone) >> 0x10);
            prim->y3 = temp_s5 - (((rsin(var_s3) << 4) * twentyone) >> 0x10);
            prim->drawMode &= ~DRAW_HIDE;
        } else if (self->ext.aguneaCrash.unk8B[sp10 + 4] != 0) {
            if (self->ext.aguneaCrash.unk8B[sp10 + 8] != 0) {
                self->ext.aguneaCrash.unk8B[sp10 + 8] = 0;
                prim->x0 = prevPrim->x0;
                prim->y0 = prevPrim->y0;
                prim->x1 = prevPrim->x1;
                prim->y1 = prevPrim->y1;
                prim->x2 = prevPrim->x2;
                prim->y2 = prevPrim->y2;
                prim->x3 = prevPrim->x3;
                prim->y3 = prevPrim->y3;
            }
            temp_v0_4 = self->ext.aguneaCrash.unk8B[sp10];
            self->ext.aguneaCrash.unk8B[sp10] = temp_v0_4 + 1;
            temp_v1_3 = temp_v0_4 & 0xFF;
            if ((temp_v1_3) < 0xA) {
                // whyyyyyy
                arr0 = &D_80155E70[temp_v0_4][0];
                rVal = *arr0;
                arr1 = &D_80155E70[temp_v0_4][1];
                gVal = *arr1;
                arr2 = &D_80155E70[temp_v0_4][2];
                bVal = *arr2;
                prim->r0 = rVal;
                prim->g0 = gVal;
                prim->b0 = bVal;
                prim->r1 = rVal;
                prim->g1 = gVal;
                prim->b1 = bVal;
                prim->r2 = rVal;
                prim->g2 = gVal;
                prim->b2 = bVal;
                prim->r3 = rVal;
                prim->g3 = gVal;
                prim->b3 = bVal;
                prim->drawMode &= ~DRAW_HIDE;
            } else {
                self->ext.aguneaCrash.unk8B[sp10 + 4] = 0;
                prim->drawMode |= DRAW_HIDE;
            }
        }
        prim = prim->next;
        sp10++;
    }
}

// RIC entity #37. Comes from blueprint 41. That's subweapon 20.
// Subweapon 20 is crash of subweapon 2, which is the axe.
void EntitySubwpnCrashAxe(Entity* self) {
    s32 sp10;
    s32 sp18;
    Primitive* prevPrim;
    Primitive* prim;
    s32 temp_v1_3;
    s16 var_s0;
    s16 var_s1;
    s16 var_s2;
    s16 var_s3;
    s16 var_v0;
    s16 temp_s4;
    s16 temp_s5;
    u8 temp_v0_4;

    s32 temp_s1;
    s16 temp_s0;

    u8* arr0;
    u8* arr1;
    u8* arr2;
    s32 twentyone;

    u8 rVal;
    u8 gVal;
    u8 bVal;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 5);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        sp10 = 0;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 | FLAG_HAS_PRIMS |
                      FLAG_UNK_20000;
        self->facingLeft = 0;
        prim = &g_PrimBuf[self->primIndex];
        self->ext.axeCrash.unk7C = ((u8)self->params << 9) + 0xC00;
        self->posY.i.hi -= 12;
        if (prim != NULL) {
            do {
                prim->tpage = 0x1C;
                prim->u0 = prim->v0 = prim->v1 = prim->u2 = 0;
                prim->u1 = prim->u3 = 0x18;
                prim->v2 = prim->v3 = 0x28;
                prim->priority = PLAYER.zPriority + 4;
                if (sp10 != 0) {
                    prim->drawMode = 0x13D;
                    self->ext.axeCrash.unk8B[sp10] = 0;
                    self->ext.axeCrash.unk8B[sp10 + 4] = 0;
                    self->ext.axeCrash.unk8B[sp10 + 8] = 0;
                } else {
                    prim->drawMode = 0x100 | DRAW_HIDE;
                }
                prim = prim->next;
                sp10++;
            } while (prim != NULL);
        }
        self->ext.factory.unkB0 = 2;
        func_8015FAB8(self);
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
        self->ext.axeCrash.unk9C = 16;
        self->ext.axeCrash.unkA0 = (u8)self->params << 9;
        self->step++;
        break;
    case 1:
        temp_s1 = self->ext.axeCrash.unk9C;
        if (++self->ext.axeCrash.unk9C >= 0x29) {
            self->ext.factory.unkA2 = 16;
            self->step++;
        }
        temp_s0 = self->ext.axeCrash.unkA0;
        self->ext.axeCrash.unkA0 += 0xC0;
        self->ext.axeCrash.unk7C += 0x80;
        self->velocityX = rcos(temp_s0) * temp_s1;
        self->velocityY = -rsin(temp_s0) * temp_s1;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        break;
    case 2:
        if (--self->ext.factory.unkA2 == 0) {
            self->ext.factory.unkA2 = 8;
            self->step++;
        }
        temp_s1 = self->ext.axeCrash.unk9C;
        temp_s0 = self->ext.axeCrash.unkA0;
        self->ext.axeCrash.unkA0 += 0xC0;
        self->ext.axeCrash.unk7C += 0x80;
        self->velocityX = rcos(temp_s0) * temp_s1;
        self->velocityY = -rsin(temp_s0) * temp_s1;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        break;
    case 3:
        if (--self->ext.factory.unkA2 == 0) {
            if ((u8)self->params == 0) {
                g_api.PlaySfx(0x635);
                g_api.PlaySfx(0x62F);
            }
            g_Player.unk4E = 1;
            self->flags &= ~(FLAG_UNK_04000000 | FLAG_UNK_20000);
        }
        temp_s1 = self->ext.axeCrash.unk9C;
        self->ext.axeCrash.unk9C += 2;
        temp_s0 = self->ext.axeCrash.unkA0;
        self->ext.axeCrash.unkA0 += 0x28;
        self->ext.axeCrash.unk7C += 0x80;
        self->velocityX = rcos(temp_s0) * temp_s1;
        self->velocityY = -rsin(temp_s0) * temp_s1;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->animFrameDuration == 0) {
            sp18 = self->animFrameIdx;
            self->ext.axeCrash.unk8B[sp18 + 1] = 0;
            self->ext.axeCrash.unk8B[sp18 + 5] = 1;
            self->ext.axeCrash.unk8B[sp18 + 9] = 1;
            sp18++;
            sp18 &= 3;
            self->animFrameIdx = sp18;
            self->animFrameDuration = 2;
        } else {
            self->animFrameDuration--;
        }
        break;
    }
    sp10 = 0;
    prim = &g_PrimBuf[self->primIndex];
    prevPrim = prim;
    sp18 = ((g_GameTimer >> 1) & 1) + 0x1AB;
    while (prim != NULL) {
        prim->clut = sp18;
        if (sp10 == 0) {
            if (self->facingLeft != 0) {
                var_s0 = 0x560;
                var_s1 = 0x2A0;
                var_s3 = 0xAA0;
                var_v0 = 0xD60;
            } else {
                var_s1 = 0x560;
                var_s0 = 0x2A0;
                var_v0 = 0xAA0;
                var_s3 = 0xD60;
            }
            var_s2 = self->ext.axeCrash.unk7C;
            temp_s4 = self->posX.i.hi;
            temp_s5 = self->posY.i.hi;
            var_s0 += var_s2;
            var_s1 += var_s2;
            var_s3 += var_s2;
            var_v0 += var_s2;
            twentyone = 21;
            prim->x0 = temp_s4 + (((rcos(var_s0) << 4) * twentyone) >> 0x10);
            prim->y0 = temp_s5 - (((rsin(var_s0) << 4) * twentyone) >> 0x10);
            prim->x1 = temp_s4 + (((rcos(var_s1) << 4) * twentyone) >> 0x10);
            prim->y1 = temp_s5 - (((rsin(var_s1) << 4) * twentyone) >> 0x10);
            prim->x2 = temp_s4 + (((rcos(var_s3) << 4) * twentyone) >> 0x10);
            prim->y2 = temp_s5 - (((rsin(var_s3) << 4) * twentyone) >> 0x10);
            prim->x3 = temp_s4 + (((rcos(var_v0) << 4) * twentyone) >> 0x10);
            prim->y3 = temp_s5 - (((rsin(var_v0) << 4) * twentyone) >> 0x10);
            prim->drawMode &= 0xFFF7;
        } else if (self->ext.axeCrash.unk8B[sp10 + 4] != 0) {
            if (self->ext.axeCrash.unk8B[sp10 + 8] != 0) {
                self->ext.axeCrash.unk8B[sp10 + 8] = 0;
                prim->x0 = prevPrim->x0;
                prim->y0 = prevPrim->y0;
                prim->x1 = prevPrim->x1;
                prim->y1 = prevPrim->y1;
                prim->x2 = prevPrim->x2;
                prim->y2 = prevPrim->y2;
                prim->x3 = prevPrim->x3;
                prim->y3 = prevPrim->y3;
            }
            temp_v0_4 = self->ext.axeCrash.unk8B[sp10];
            self->ext.axeCrash.unk8B[sp10] = temp_v0_4 + 1;
            temp_v1_3 = temp_v0_4 & 0xFF;
            if ((temp_v1_3) < 0xA) {
                // whyyyyyy
                arr0 = &D_80155E70[temp_v0_4][0];
                rVal = *arr0;
                arr1 = &D_80155E70[temp_v0_4][1];
                gVal = *arr1;
                arr2 = &D_80155E70[temp_v0_4][2];
                bVal = *arr2;
                prim->r0 = rVal;
                prim->g0 = gVal;
                prim->b0 = bVal;
                prim->r1 = rVal;
                prim->g1 = gVal;
                prim->b1 = bVal;
                prim->r2 = rVal;
                prim->g2 = gVal;
                prim->b2 = bVal;
                prim->r3 = rVal;
                prim->g3 = gVal;
                prim->b3 = bVal;
                prim->drawMode &= ~DRAW_HIDE;
            } else {
                self->ext.axeCrash.unk8B[sp10 + 4] = 0;
                prim->drawMode |= DRAW_HIDE;
            }
        }
        prim = prim->next;
        sp10++;
    }
}

INCLUDE_ASM("ric/nonmatchings/2C4C4", func_8016B0C0);

void func_8016B8E8(s32 arg0) {
    g_CurrentEntity->ext.generic.unk7C.s =
        (arg0 << 0x10 >> 0xF) - g_CurrentEntity->ext.generic.unk7C.s;
    if (g_CurrentEntity->ext.generic.unk80.modeS16.unk2 == 0) {
        g_CurrentEntity->ext.generic.unk80.modeS16.unk0++;
        g_CurrentEntity->ext.generic.unk80.modeS16.unk2++;
    }
}

void func_8016B92C(s16 arg0) {
    if (g_CurrentEntity->ext.generic.unk80.modeS16.unk2 == 0) {
        g_CurrentEntity->ext.generic.unk7C.s =
            (arg0 * 2) - g_CurrentEntity->ext.generic.unk7C.s;
        g_CurrentEntity->ext.generic.unk80.modeS16.unk0++;
        g_CurrentEntity->ext.generic.unk80.modeS16.unk2++;
    }
}

INCLUDE_ASM("ric/nonmatchings/2C4C4", func_8016B97C);

INCLUDE_ASM("ric/nonmatchings/2C4C4", func_8016C1BC);

s32 RicPrimDecreaseBrightness(Primitive* prim, u8 amount) {
    u8 isEnd;
    s32 i;
    s32 j;
    u8* pColor;

    isEnd = 0;
    pColor = &prim->r0;
    for (i = 0; i < 4; i++, pColor += OFF(Primitive, r1) - OFF(Primitive, r0)) {
        for (j = 0; j < 3; j++) {
            pColor[j] -= amount;

            if (pColor[j] < 16) {
                pColor[j] = 16;
            } else {
                isEnd |= 1;
            }
        }
    }
    return isEnd;
}

INCLUDE_ASM("ric/nonmatchings/2C4C4", func_8016C734);

INCLUDE_ASM("ric/nonmatchings/2C4C4", func_8016CC74);

void func_8016D328(Entity* entity) {
    s16 primIndex;
    s32 newVelocity;

    switch (entity->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        entity->primIndex = primIndex;
        if (primIndex != -1) {
            entity->flags = FLAG_UNK_08000000 | FLAG_HAS_PRIMS;
            entity->posX.val =
                entity->ext.generic.unk8C.entityPtr->ext.generic.unk84.unk;
            entity->posY.val =
                entity->ext.generic.unk8C.entityPtr->ext.generic.unk88.unk;
            entity->facingLeft = entity->ext.generic.unk8C.entityPtr->ext
                                     .generic.unk8C.modeU16.unk0;
            entity->ext.generic.unkB0 = 0x18;
            func_8015FAB8(entity);
            entity->unk5A = 0x79;
            entity->animSet = ANIMSET_DRA(14);
            entity->palette = 0x819E;
            entity->unk4C = &D_80155EA8;
            entity->drawMode = 0x30;
            entity->drawFlags = FLAG_DRAW_UNK8;
            entity->unk6C = 0x60;
            entity->hitboxWidth = 8;
            entity->hitboxHeight = 8;
            entity->flags |= FLAG_UNK_100000;
            newVelocity = (rand() % 512) + 0x300;
            entity->velocityX = rcos(newVelocity) * 32;
            entity->velocityY = -(rsin(newVelocity) * 32);
            entity->step++;
        } else {
            DestroyEntity(entity);
        }
        break;

    case 1:
        if (++entity->ext.generic.unk7C.s >= 39) {
            DestroyEntity(entity);
        } else {
            entity->posX.val += entity->velocityX;
            entity->posY.val += entity->velocityY;
        }
        break;
    }
}

INCLUDE_ASM("ric/nonmatchings/2C4C4", func_8016D4D8);

void func_8016D920(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_04000000;
        entity->ext.generic.unkB0 = 0x19;
        func_8015FAB8(entity);
        entity->hitboxWidth = 4;
        entity->hitboxHeight = 4;
        entity->step++;
        break;

    case 1:
        if (++entity->ext.generic.unk7C.s >= 4) {
            DestroyEntity(entity);
        }
        break;
    }
}

INCLUDE_ASM("ric/nonmatchings/2C4C4", func_8016D9C4);

INCLUDE_ASM("ric/nonmatchings/2C4C4", func_8016DF74);
