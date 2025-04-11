// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"
#include "sfx.h"

// Unused?
static s16 D_80155D94[] = {16, 0, -1, 0};

// Entity ID #7. Made by blueprint 6. Comes from subweapon 3. Holy water!
// Not at all the same as DRA's.
void RicEntitySubwpnHolyWater(Entity* self) {
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
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->animSet = ANIMSET_OVL(0x12);
        self->animCurFrame = 0x23;
        self->zPriority = PLAYER.zPriority + 2;
        self->unk5A = 0x46;
        self->palette = PAL_OVL(0x12F);
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

        self->ext.holywater.subweaponId = PL_W_HOLYWATER;
        RicSetSubweaponParams(self);
        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        self->ext.holywater.unk80 = 0x200;
        self->step += 1;
        break;
    case 1:
        self->posY.val += self->velocityY;
        collision_result = RicCheckHolyWaterCollision(0, 0);
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
            g_api.PlaySfx(SFX_GLASS_BREAK_WHOOSH);
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
            RicCreateEntFactoryFromEntity(
                self, FACTORY(BP_HOLYWATER_FIRE, self->ext.holywater.unk82), 0);
            // weirdly nonmatching with ++;
            self->ext.holywater.unk82 = self->ext.holywater.unk82 + 1;
            self->velocityX -= (self->velocityX / 32);
        }
        collision_result = RicCheckHolyWaterCollision(6, 0);
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
            RicCreateEntFactoryFromEntity(
                self, FACTORY(BP_HOLYWATER_FIRE, self->ext.holywater.unk82), 0);
            self->ext.holywater.unk82 = self->ext.holywater.unk82 + 1;
        }
        self->velocityY += FIX(12.0 / 128);
        if (self->velocityY > FIX(4)) {
            self->velocityY = FIX(4);
        }
        self->posY.val += self->velocityY;
        collision_result = RicCheckHolyWaterCollision(0, 0);
        self->posX.val += self->velocityX;
        if (self->velocityX < 0) {
            argY = -4;
        } else {
            argY = 4;
        }
        collision_result |= func_8016840C(-7, argY);
        if (collision_result & 1) {
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
    g_Player.timers[PL_T_3] = 2;
}

// Entity ID #8. Blueprint 7.
static Point32 D_80155D9C[] = {{28, 0}, {28, 16}, {28, 32}, {28, 48},
                               {60, 0}, {60, 16}, {60, 32}, {60, 48}};
void RicEntitySubwpnHolyWaterFlame(Entity* self) {
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
            PRED(prim) = randR;
            PGRN(prim) = randG;
            PBLU(prim) = randB;
            if (i == 0) {
                prim->b0 = prim->b1 = prim->g0 = prim->g1 = prim->r0 =
                    prim->r1 = 0;
            }
            prim->clut = 0x1B0;
            prim->tpage = 0x1A;
            prim->priority = PLAYER.zPriority + 2;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_HIDE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
            i++;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->ext.holywater.timer = 1;
        self->step += 1;
        break;
    case 1:
        if (--self->ext.holywater.timer == 0) {
            self->ext.holywater.subweaponId = PL_W_HOLYWATER_FLAMES;
            RicSetSubweaponParams(self);
            self->hitboxWidth = 4;
            self->ext.holywater.hitboxState = self->hitboxState;
            self->posY.i.hi = self->posY.i.hi - 10;
            RicCreateEntFactoryFromEntity(self, FACTORY(BP_EMBERS, 3), 0);
            self->ext.holywater.timer = 0x50;
            self->posY.i.hi = self->posY.i.hi + 10;
            self->ext.holywater.unk80 = (rand() & 0xF) + 0x12;
            self->ext.holywater.angle = rand() & 0xFFF;
            self->step += 1;
        }
        break;
    case 2:
        if (self->facingLeft) {
            var_s4 = 1;
        } else {
            var_s4 = -1;
        }
        angleTemp = self->ext.holywater.angle;
        self->ext.holywater.angle += 0xC0;
        angle = angleTemp;
        for (i = 0; i < 4; i++) {
            sp10[i] = self->posX.i.hi + (rsin(angle) >> 0xA);
            angle += 0x400;
        }
        sp10[4] = self->posX.i.hi;
        sp10[0] = var_s4 + self->posX.i.hi;
        temp_v0_2 = rsin((s16)((self->ext.holywater.timer * 64) + 0x800)) >> 8;
        temp_v0_2 += self->ext.holywater.unk80;
        temp_v0_2 = temp_v0_2 * 3 >> 1;
        sp20[0] = self->posY.i.hi - temp_v0_2;
        sp20[4] = self->posY.i.hi;
        sp20[2] = (sp20[0] + sp20[4]) / 2;
        sp20[1] = (sp20[0] + sp20[2]) / 2;
        sp20[3] = (sp20[2] + sp20[4]) / 2;
        prim = &g_PrimBuf[self->primIndex];
        if (--self->ext.holywater.timer < 0) {
            DestroyEntity(self);
            return;
        }
        if (self->ext.holywater.timer & 3) {
            self->hitboxState = 0;
        } else {
            self->hitboxState = self->ext.holywater.hitboxState;
        }
        if (self->ext.holywater.timer < 0x15) {
            self->hitboxState = 0;
        }
        i = 0;
        while (prim != NULL) {
            if (upperParams * 2 + 0x18 >= self->ext.holywater.timer) {
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
            prim->y0 = sp20[i];
            prim->y1 = sp20[i];
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
    g_Player.timers[PL_T_3] = 2;
}

// Entity 13. Made by blueprint 13. That's from subweapon 12.
// That's the crash for subweapon 4. That's the cross.
static u16 crash_cross_img_data[] = {
    0x94A5, 0x98C6, 0x9CE7, 0xA108, 0xA529, 0xA94A, 0xAD6B, 0xB18C,
    0xB5AD, 0xB9CE, 0xBDEF, 0xC210, 0xC631, 0xCA52, 0xCE73, 0xD294,
    0xD6B5, 0xDAD6, 0xDEF7, 0xE318, 0xE318, 0xE318, 0xE318, 0xE318,
    0xE318, 0xE318, 0xE318, 0xE318, 0xE318, 0xDEF7, 0xDAD6, 0xD6B5,
    0xD294, 0xCE73, 0xCA52, 0xC631, 0xC210, 0xBDEF, 0xB9CE, 0xB5AD,
    0xB18C, 0xAD6B, 0xA94A, 0xA529, 0xA108, 0x9CE7, 0x98C6, 0x94A5};
static RECT crash_cross_img_vram = {0x0301, 0x01F8, 0x0030, 0x0001};
void RicEntitySubwpnCrashCross(Entity* self) {
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
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        self->ext.crashcross.unk80 = 1;
        self->zPriority = 0xC2;
        self->ext.crashcross.subweaponId = PL_W_CRASH_CROSS;
        RicSetSubweaponParams(self);
        LoadImage(&crash_cross_img_vram, crash_cross_img_data);
        g_api.PlaySfx(SFX_CRASH_CROSS);
        g_api.PlaySfx(SFX_TELEPORT_BANG_B);
        self->step += 1;
        break;
    case 1:
        // FAKE, register reuse thing
        one = three * 2;
        self->ext.crashcross.unk7E.val += three;
        self->ext.crashcross.unk82 += one;
        if (self->ext.crashcross.unk7E.i.lo >= 0x70U) {
            RicCreateEntFactoryFromEntity(self, BP_CRASH_CROSSES_ONLY, 0);
            RicCreateEntFactoryFromEntity(self, BP_CRASH_CROSS_PARTICLES, 0);
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
            g_api.PlaySfx(SFX_WEAPON_APPEAR);
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
    self->hitboxHeight = self->ext.crashcross.unk7E.val;
    if (self->step == 4) {
        self->hitboxWidth = ((right - left) >> 1);
        self->hitboxOffX = ((left + right) >> 1) - self->posX.i.hi;
    } else {
        self->hitboxOffX = 0;
        self->hitboxWidth = self->ext.crashcross.unk7C;
    }
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = prim->x2 = self->posX.i.hi - self->ext.crashcross.unk7C;
    prim->y1 = prim->y0 = self->posY.i.hi - self->ext.crashcross.unk7E.val;
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
    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
    prim->priority = self->zPriority;
    g_Player.timers[PL_T_3] = 2;
}

// Entity ID #21. Blueprint 22. Called in RicHandleDeadPrologue.
// Creates the white column around Richter when he is revived in the Prologue.
void RicEntityRevivalColumn(Entity* self) {
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
        LoadImage(&crash_cross_img_vram, crash_cross_img_data);
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
    prim->y1 = prim->y0 = self->posY.i.hi - self->ext.ricColumn.unk7E;
    prim->x1 = prim->x3 = prim->x0 + self->ext.ricColumn.unk80;
    prim->y2 = prim->y3 = prim->y0 + self->ext.ricColumn.unk82;
    prim->u0 = prim->u2 = 1;
    prim->u1 = prim->u3 = 0x30;
    prim->v0 = prim->v1 = prim->v2 = prim->v3 = 0xF8;
    prim->tpage = 0x11C;
    if (g_Timer & 1) {
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
    } else {
        prim->drawMode = DRAW_HIDE;
    }
    prim->priority = self->zPriority;
}

static AnimationFrame anim_cross_boomerang[] = {
    {36, FRAME(1, 0)}, {1, FRAME(2, 0)}, {1, FRAME(3, 0)},
    {1, FRAME(4, 0)},  {1, FRAME(5, 0)}, {1, FRAME(6, 0)},
    {1, FRAME(7, 0)},  {1, FRAME(8, 0)}, A_LOOP_AT(0)};
static Point16 D_80175088[4][128];
static s32 D_80175888;
void RicEntitySubwpnCross(Entity* self) {
    s32 xAccel;
    Point16* temp_a0;
    s16 playerHitboxX;
    s16 playerHitboxY;

    f32 tempX;

    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
        // gets used by shadow, must align with that entity
        self->ext.crossBoomerang.unk84 = &D_80175088[D_80175888];
        D_80175888++;
        D_80175888 &= 3;
        RicCreateEntFactoryFromEntity(self, BP_5, 0);
        self->animSet = ANIMSET_OVL(0x11);
        self->unk5A = 0x66;
        self->anim = anim_cross_boomerang;
        self->facingLeft = PLAYER.facingLeft;
        self->zPriority = PLAYER.zPriority;
        RicSetSpeedX(FIX(3.5625));
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->rotZ = 0xC00;
        self->ext.crossBoomerang.subweaponId = PL_W_CROSS;
        RicSetSubweaponParams(self);
        self->hitboxHeight = self->hitboxWidth = 8;
        self->posY.i.hi -= 8;
        g_api.PlaySfx(SFX_THROW_WEAPON_MAGIC);
        self->step++;
        break;
    case 1:
        if (PLAYER.pose == 1) {
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
        if (abs(self->velocityX) < FIX(0.75)) {
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
        if (abs(self->velocityX) > FIX(0.75)) {
            self->step++;
        }
        break;
    case 4:
        // Third phase. We've now sped up and we're coming back.
        // Increase speed until a terminal velocity of 2.5.
        xAccel = self->facingLeft ? FIX(-1.0 / 16) : FIX(1.0 / 16);
        self->velocityX -= xAccel;
        if (abs(self->velocityX) > FIX(2.5)) {
            self->step++;
        }
        /* fallthrough */
    case 5:
        // FAKE, unfortunate need to preload this.
        tempX = self->posX;
        // Now we check 2 conditions. If we're within the player's hitbox...
        playerHitboxX = (PLAYER.posX.i.hi + PLAYER.hitboxOffX);
        playerHitboxY = (PLAYER.posY.i.hi + PLAYER.hitboxOffY);
        if (abs(tempX.i.hi - playerHitboxX) <
                PLAYER.hitboxWidth + self->hitboxWidth &&
            abs(self->posY.i.hi - playerHitboxY) <
                PLAYER.hitboxHeight + self->hitboxHeight) {
            // ... Then we go to step 7 to be destroyed.
            self->step = 7;
            self->ext.crossBoomerang.timer = 0x20;
            return;
        }
        // Alternatively, if we're offscreen, we will also be destroyed.
        if ((!self->facingLeft && self->posX.i.hi < -0x20) ||
            (self->facingLeft && self->posX.i.hi >= 0x121)) {
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
    // Factory 4 is entity #5, RicEntityHitByCutBlood. Appears to make a
    // "shadow" of the cross boomerang.
    self->ext.crossBoomerang.unk7E++;
    if (1 < self->step && self->step < 6) {
        if ((self->ext.crossBoomerang.unk7E & 0xF) == 1) {
            RicCreateEntFactoryFromEntity(self, BP_SUBWPN_CROSS_PARTICLES, 0);
        }
        if ((self->ext.crossBoomerang.unk7E & 0xF) == 4) {
            RicCreateEntFactoryFromEntity(self, FACTORY(BP_EMBERS, 6), 0);
        }
        if ((self->ext.crossBoomerang.unk7E & 0xF) == 6) {
            RicCreateEntFactoryFromEntity(self, BP_SUBWPN_CROSS_PARTICLES, 0);
        }
        if ((self->ext.crossBoomerang.unk7E & 0xF) == 8) {
            RicCreateEntFactoryFromEntity(self, FACTORY(BP_EMBERS, 6), 0);
        }
        if ((self->ext.crossBoomerang.unk7E & 0xF) == 12) {
            RicCreateEntFactoryFromEntity(self, FACTORY(BP_EMBERS, 6), 0);
        }
        if ((self->ext.crossBoomerang.unk7E & 0xF) == 11) {
            RicCreateEntFactoryFromEntity(self, BP_SUBWPN_CROSS_PARTICLES, 0);
        }
    }
    // Applies a flickering effect
    if (!((g_GameTimer >> 1) & 1)) {
        self->palette = PAL_OVL(0x1B1);
    } else {
        self->palette = PAL_OVL(0x1B0);
    }
    temp_a0 = self->ext.crossBoomerang.unk84;
    // This indexes into the unk84 array.
    // Better way would have been temp_a0 = &unk84[unk80].
    temp_a0 += self->ext.crossBoomerang.unk80;
    temp_a0->x = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    temp_a0->y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    self->ext.crossBoomerang.unk80++;
    self->ext.crossBoomerang.unk80 &= 0x3F;
    g_Player.timers[PL_T_3] = 2;
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
            entity->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
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
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
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

// made by blueprint #5, see step 0 of RicEntitySubwpnCross
static s16 D_80155E68[] = {9, 10, 11, 12};
void RicEntitySubwpnCrossTrail(Entity* self) {
    s16* temp;

    switch (self->step) {
    case 0:
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_CAMERA_LOCKED;
        // the parent pointer is set in RicEntityFactory.
        // the value of unk84 is set in RicEntitySubwpnCross
        self->ext.crossBoomerang.unk84 =
            self->ext.crossBoomerang.parent->ext.crossBoomerang.unk84;
        self->animSet = ANIMSET_OVL(17);
        self->animCurFrame = D_80155E68[self->params];
        self->unk5A = 0x66;
        self->palette = PAL_OVL(0x1B0);
        self->drawMode = DRAW_TPAGE;
        self->facingLeft = PLAYER.facingLeft;
        self->zPriority = PLAYER.zPriority;
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->rotZ = 0xC00;
        self->step++;
        break;

    case 1:
        self->rotZ -= 0x80;
        if (self->ext.crossBoomerang.parent->step == 7) {
            self->step++;
            self->ext.crossBoomerang.timer = (self->params + 1) * 4;
        }
        break;

    case 2:
        self->rotZ -= 0x80;
        if (--self->ext.crossBoomerang.timer == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    // get the x and y position from the parent (must align)
    temp = &self->ext.crossBoomerang.unk84[0];
    temp += self->ext.crossBoomerang.unk80 * 2;
    self->posX.i.hi = *temp - g_Tilemap.scrollX.i.hi;
    temp++;
    self->posY.i.hi = *temp - g_Tilemap.scrollY.i.hi;
    self->ext.crossBoomerang.unk80++;
    self->ext.crossBoomerang.unk80 &= 0x3F;
}

// Entity ID #32. Comes from blueprint 34.
// Surprisingly pretty different from DRA version.
void RicEntitySubwpnCrashCrossParticles(Entity* self) {
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
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_20000;
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
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim->g3 = (temps0copy >> 2) + 4;
            prim->priority = priority;
            prim->r1++;
        } else {
            prim->g1 -= prim->g3;
            if (((u8)prim->b0 >= 6U) || ((u8)prim->g1 < 0x18U)) {
                prim->drawMode = DRAW_HIDE;
                prim->r0 = 0;
            }
        }
        if (prim->r0 == 0) {
            continue;
        }
        temp_a1 = &uv_anim_801548F4;
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
