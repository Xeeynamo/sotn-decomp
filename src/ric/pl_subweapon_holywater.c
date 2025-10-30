// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"

void RicEntityNotImplemented3(Entity* self) {}

// Entity ID #35. Created by blueprint 40. No known FACTORY calls with
// blueprint 40. Duplicate of DRA EntitySubwpnHolyWaterBreakGlass.
static s16 D_80155D64[4][6] = {
    {2, -2, 0, -4, 0, 0},
    {-3, -3, -1, 1, 2, 0},
    {-4, -3, 2, -2, -2, 2},
    {-1, 0, 0, -4, 3, 3}};
#define FAKEPRIM ((FakePrim*)prim)
void RicEntitySubwpnHolyWaterBreakGlass(Entity* self) {
    Point16 sp10[8];
    Primitive* prim;
    s16 posX;
    s16 posY;
    s16 arrIndex;
    s32 i;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; prim != NULL; i++, prim = prim->next) {
            if (i < 8) {
                sp10[i].x = FAKEPRIM->posX.i.hi = FAKEPRIM->x0 = posX;
                sp10[i].y = FAKEPRIM->posY.i.hi = FAKEPRIM->y0 = posY;
                // Random velocity from 0.25 to 0.5
                FAKEPRIM->velocityX.val = (rand() & 0x3FFF) + FIX(0.25);
                if (i & 1) {
                    FAKEPRIM->velocityX.val = -FAKEPRIM->velocityX.val;
                }
                FAKEPRIM->velocityY.val =
                    -(((rand() & PSP_RANDMASK) * 2) + FIX(2.5));
                FAKEPRIM->drawMode = DRAW_HIDE | DRAW_UNK02;
                FAKEPRIM->type = PRIM_TILE;
            } else {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 =
                    (rand() & 0xF) + 0x30;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 =
                    (rand() & 0x7F) + 0x80;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 =
                    (rand() & 0x1F) + 0x30;
                if (rand() & 1) {
                    prim->drawMode = (DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                      DRAW_UNK02 | DRAW_TRANSP);
                } else {
                    prim->drawMode = (DRAW_COLORS | DRAW_UNK02);
                }
                posX = sp10[i - 8].x;
                posY = sp10[i - 8].y;
                prim->u0 = arrIndex = i & 3;
                prim->x0 = posX + D_80155D64[arrIndex][0];
                prim->y0 = posY + D_80155D64[arrIndex][1];
                prim->x1 = posX + D_80155D64[arrIndex][2];
                prim->y1 = posY + D_80155D64[arrIndex][3];
                prim->x3 = prim->x2 = posX + D_80155D64[arrIndex][4];
                prim->y3 = prim->y2 = posY + D_80155D64[arrIndex][5];
                prim->type = PRIM_G4;
                prim->priority = PLAYER.zPriority + 2;
            }
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->ext.timer.t = 20;
        self->step++;
        break;
    case 1:
        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; prim != NULL; i++, prim = prim->next) {
            if (i < 8) {
                FAKEPRIM->posX.i.hi = FAKEPRIM->x0;
                FAKEPRIM->posY.i.hi = FAKEPRIM->y0;
                FAKEPRIM->posX.val += FAKEPRIM->velocityX.val;
                FAKEPRIM->posY.val += FAKEPRIM->velocityY.val;
                FAKEPRIM->velocityY.val += FIX(36.0 / 128);
                sp10[i].x = FAKEPRIM->posX.i.hi;
                sp10[i].y = FAKEPRIM->posY.i.hi;
                FAKEPRIM->x0 = FAKEPRIM->posX.i.hi;
                FAKEPRIM->y0 = FAKEPRIM->posY.i.hi;
            } else {
                posX = sp10[i - 8].x;
                posY = sp10[i - 8].y;
                arrIndex = prim->u0;
                prim->x0 = posX + D_80155D64[arrIndex][0];
                prim->y0 = posY + D_80155D64[arrIndex][1];
                prim->x1 = posX + D_80155D64[arrIndex][2];
                prim->y1 = posY + D_80155D64[arrIndex][3];
                prim->x3 = prim->x2 = posX + D_80155D64[arrIndex][4];
                prim->y3 = prim->y2 = posY + D_80155D64[arrIndex][5];
            }
        }
        break;
    }
}

// Entity ID #11. Created by blueprint 12.
// This is blueprintNum for subweapon ID 16.
// That is the crash for subweapon 3. That's holy water!
void RicEntityCrashHydroStorm(Entity* self) {
    PrimLineG2* line;
    s16 primcount;
    s32 i;

    if (self->params < 40) {
        primcount = 32;
    } else {
        primcount = 33 - (self->params - 32) * 2;
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, primcount);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.subweapon.subweaponId = PL_W_HYDROSTORM;
        RicSetSubweaponParams(self);
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_HAS_PRIMS | FLAG_UNK_20000;
        self->facingLeft = 0;
        line = (PrimLineG2*)&g_PrimBuf[self->primIndex];
        while (line != NULL) {
            line->r0 = 0x1F;
            line->g0 = 0x1F;
            line->b0 = 0x30;
            line->r1 = 0x3F;
            line->g1 = 0x50;
            line->b1 = 0x7F;
            line->x0 = rand() & 0x1FF;
            line->x1 = line->x0;
            line->y0 = -(rand() & 0xF);
            line->y1 = line->y0;
            line->preciseX.i.hi = line->x1;
            line->preciseY.i.hi = line->y1;

            // both rcos and rsin could be pre-calcualted values
            // PSP and PSX are logically equivalent
#if defined(VERSION_PSP)
            line->velocityX.val = (rcos(0xB80) * 16) * 12;
#else
            line->velocityX.val = -(rcos(0xB80) * -16) * 12;
#endif
            line->velocityY.val = -(rsin(0xB80) * 16) * 12;
            line->timer = 0;
            line->delay = (rand() & 0xF) + 12;
            if (rand() & 1) {
                line->priority = PLAYER.zPriority + 2;
            } else {
                line->priority = PLAYER.zPriority - 2;
            }
            line->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            line = line->next;
        }
        if (self->params == 1) {
            g_api.SetFadeMode(FADE_BLUE_TINT);
        }
        self->ext.subweapon.timer = 0x160;
        if ((self->params < 32) && !(self->params & 3)) {
            g_api.PlaySfx(SFX_RIC_HYDRO_STORM_ATTACK);
        }
        self->step++;
        break;
    case 1:
        line = (PrimLineG2*)&g_PrimBuf[self->primIndex];
        for (i = 0; line != NULL; i++, line = line->next) {
            if (line->timer == 0) {
                line->preciseX.i.hi = line->x1;
                line->preciseY.i.hi = line->y1;
                line->preciseX.val += line->velocityX.val;
                line->preciseY.val += line->velocityY.val;
                line->x1 = line->preciseX.i.hi;
                line->y1 = line->preciseY.i.hi;
                if (line->y1 > line->delay) {
                    line->timer++;
                    line->xLength = line->x0 - line->x1;
                    line->yLength = line->y0 - line->y1;
                }
            } else {
                line->preciseX.i.hi = line->x1;
                line->preciseY.i.hi = line->y1;
                line->preciseX.val += line->velocityX.val;
                line->preciseY.val += line->velocityY.val;
                line->x1 = line->preciseX.i.hi;
                line->y1 = line->preciseY.i.hi;
                line->y0 = line->y1 + line->yLength;
                line->x0 = line->x1 + line->xLength;
                if (line->y0 >= 0xD8) {
                    self->step = 2;
                }
            }
        }
        self->ext.subweapon.timer++;
        break;
    case 2:
#if defined(VERSION_HD) || defined(VERSION_PSP)
        if (self->params == 0x28) {
            g_Player.unk4E = 1;
        }
#endif
        DestroyEntity(self);
        break;
    }
    g_Player.timers[PL_T_3] = 16;
}

// Equivalent to DRA CheckHolyWaterCollision
s32 RicCheckHolyWaterCollision(s16 baseY, s16 baseX) {
    Collider res1;
    Collider res2;
    s16 newY;
    s16 x;
    s16 y;
    s16 collEffs;

    const u32 colFullSet =
        (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 | EFFECT_UNK_1000 |
         EFFECT_UNK_0800 | EFFECT_SOLID);
    const u32 colSetNo800 = (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                             EFFECT_UNK_2000 | EFFECT_UNK_1000 | EFFECT_SOLID);
    const u32 colSet1 = (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SOLID);
    const u32 colSet2 = (EFFECT_UNK_8000 | EFFECT_SOLID);
    x = g_CurrentEntity->posX.i.hi + baseX;
    y = g_CurrentEntity->posY.i.hi + baseY;

    g_api.CheckCollision(x, y, &res1, 0);
    collEffs = res1.effects & colFullSet;
    y = y - 1 + res1.unk18;
    g_api.CheckCollision(x, y, &res2, 0);
    newY = baseY + (g_CurrentEntity->posY.i.hi + res1.unk18);

    if ((collEffs & colSet1) == EFFECT_SOLID ||
        (collEffs & colSet1) == (EFFECT_UNK_0800 | EFFECT_SOLID)) {
        collEffs = res2.effects & colSetNo800;
        if (!(collEffs & EFFECT_SOLID)) {
            g_CurrentEntity->posY.i.hi = newY;
            return 1;
        }
        if ((res2.effects & colSet2) == colSet2) {
            g_CurrentEntity->posY.i.hi = newY - 1 + res2.unk18;
            return collEffs;
        }
        return 0;
    } else if ((collEffs & colSet2) == colSet2) {
        g_CurrentEntity->posY.i.hi = newY;
        return collEffs & colSetNo800;
    }
    return 0;
}

// Equivalent to DRA func_80125B6C
s32 func_8016840C(s16 y, s16 x) {
    Collider collider;
    s16 xShift;

    if (g_CurrentEntity->velocityX == 0) {
        return 0;
    }
    g_api.CheckCollision(g_CurrentEntity->posX.i.hi + x,
                         g_CurrentEntity->posY.i.hi + y, &collider, 0);
    if (g_CurrentEntity->velocityX > 0) {
        xShift = collider.unk14;
    } else {
        xShift = collider.unk1C;
    }
    if (collider.effects & EFFECT_UNK_0002) {
        g_CurrentEntity->posX.i.hi += xShift;
        g_CurrentEntity->posX.i.lo = 0;
        return 2;
    }
    return 0;
}

// Unused?
static s16 D_80155D94[] = {16, 0, -1, 0};

// Entity ID #7. Made by blueprint 6. Comes from subweapon 3. Holy water!
// Not at all the same as DRA's.
void RicEntitySubwpnHolyWater(Entity* self) {
    s32 velocity;
    s16 xMod;
    s32 colRes;

    colRes = 0;
    if (self->step > 2) {
        self->posY.i.hi += 5;
    }
    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->animSet = ANIMSET_OVL(0x12);
        self->animCurFrame = 0x23;
        self->zPriority = PLAYER.zPriority + 2;
        self->unk5A = 0x46;
        self->palette = PAL_FLAG(0x12F);
        xMod = 0;
        if (self->facingLeft) {
            xMod = -xMod;
        }
        self->posX.i.hi += xMod;
        self->posY.i.hi += -16;
        self->ext.holywater.angle = (rand() & 0x7F) + 0xDC0;
        if (PLAYER.facingLeft == 1) {
            self->ext.holywater.angle = (rand() & 0x7F) + 0x9C0;
        }
        self->velocityX = ((rcos(self->ext.holywater.angle) << 4) * 0x600) >> 8;
        self->velocityY =
            -((rsin(self->ext.holywater.angle) << 4) * 0x600) >> 8;
        self->ext.holywater.subweaponId = PL_W_HOLYWATER;
        RicSetSubweaponParams(self);
        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        self->ext.holywater.unk80 = 0x200;
        self->step += 1;
        break;
    case 1:
        self->posY.val += self->velocityY;
        colRes = RicCheckHolyWaterCollision(0, 0);
        self->posX.val += self->velocityX;

        xMod = 4;
        if (self->velocityX < 0) {
            xMod = -xMod;
        }
        colRes |= func_8016840C(-7, xMod);
        if (colRes & 2) {
            self->velocityX = -self->velocityX;
            colRes = 1;
        }
        if ((colRes & 1) || self->hitFlags) {
            // @bug: should call RicCreateEntFactoryFromEntity instead in case
            // E_FACTORY goes out of order between RIC and DRA
            g_api.CreateEntFactoryFromEntity(self, BP_HOLYWATER_GLASS, 0);
            g_api.PlaySfx(SFX_GLASS_BREAK_WHOOSH);
            self->animSet = 0;
            self->hitboxState = 0;
            self->velocityX = self->velocityX >> 2;
            self->ext.holywater.timer = 0x50;
            self->step = 3;
        }
        break;
    case 2:
        if (--self->ext.holywater.timer == 0) {
            self->velocityX = self->velocityX >> 2;
            self->ext.holywater.timer = 0x50;
            self->step++;
        }
        break;
    case 3:
        if (!(self->ext.holywater.timer & 3)) {
            RicCreateEntFactoryFromEntity(
                self, FACTORY(BP_HOLYWATER_FIRE, self->ext.holywater.unk82), 0);
            self->ext.holywater.unk82 += 1;
            self->velocityX -= (self->velocityX / 32);
        }
        colRes = RicCheckHolyWaterCollision(6, 0);
        velocity = self->velocityX;
        if (self->velocityX < 0) {
            if ((colRes & 0xF000) == 0xC000) {
                velocity = velocity * 10 / 16;
            }
            if ((colRes & 0xF000) == 0xD000) {
                velocity = velocity * 13 / 16;
            }
        }
        if (self->velocityX > 0) {
            if ((colRes & 0xF000) == 0x8000) {
                velocity = velocity * 10 / 16;
            }
            if ((colRes & 0xF000) == 0x9000) {
                velocity = velocity * 13 / 16;
            }
        }
        self->posX.val += velocity;
        xMod = 4;
        if (self->velocityX < 0) {
            xMod = -xMod;
        }
        colRes |= func_8016840C(-7, xMod);
        if (!(colRes & 1)) {
            self->velocityX = self->velocityX >> 1;
            self->step++;
        }
        break;
    case 4:
        if (!(self->ext.holywater.timer & 3)) {
            RicCreateEntFactoryFromEntity(
                self, FACTORY(BP_HOLYWATER_FIRE, self->ext.holywater.unk82), 0);
            self->ext.holywater.unk82 += 1;
        }
        self->velocityY += FIX(12.0 / 128);
        if (self->velocityY > FIX(4)) {
            self->velocityY = FIX(4);
        }
        self->posY.val += self->velocityY;
        colRes = RicCheckHolyWaterCollision(0, 0);
        self->posX.val += self->velocityX;
        xMod = 4;
        if (self->velocityX < 0) {
            xMod = -xMod;
        }
        colRes |= func_8016840C(-7, xMod);
        if (colRes & 1) {
            self->velocityX = self->velocityX << 1;
            self->step--;
        }
        break;
    case 5:
        break;
    }
    if (self->step > 2) {
        if (--self->ext.holywater.timer < 0) {
            DestroyEntity(self);
            return;
        }
        if (self->ext.holywater.timer == 2) {
            self->step = 5;
        }
        self->posY.i.hi -= 5;
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
    g_Player.timers[PL_T_3] = 2;
}

// Entity ID #8. Blueprint 7.
static s32 D_80155D9C[] = {
    28, 0, 28, 16, 28, 32, 28, 48, 60, 0, 60, 16, 60, 32, 60, 48};
void RicEntitySubwpnHolyWaterFlame(Entity* self) {
    s16 sp10[5];
    s16 sp20[5];
    s16 xMod;
    s16 variant;
    s16* primYPtr;
    s32 doubleparams;
    u8 randR;
    u8 randG;
    u8 randB;
    s16 flameHeight;
    s16 angle;
    u8 texX;
    u8 texY;
    s32 i;
    Primitive* prim;

    variant = self->params >> 8;
    texX = D_80155D9C[(g_GameTimer & 7) * 2 + 0];
    texY = D_80155D9C[(g_GameTimer & 7) * 2 + 1];
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
        while (prim) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = randR;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = randG;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = randB;
            if (i == 0) {
                prim->r0 = prim->r1 = 0;
                prim->g0 = prim->g1 = 0;
                prim->b0 = prim->b1 = 0;
            }
            prim->clut = 0x1B0;
            prim->tpage = 0x1A;
            prim->priority = PLAYER.zPriority + 2;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_HIDE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            i++;
            prim = prim->next;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->ext.holywater.timer = 1;
        self->step++;
        break;
    case 1:
        if (--self->ext.holywater.timer == 0) {
            self->ext.holywater.subweaponId = PL_W_HOLYWATER_FLAMES;
            RicSetSubweaponParams(self);
            self->ext.holywater.hitboxState = self->hitboxState;
            self->hitboxWidth = 4;
            self->posY.i.hi -= 10;
            RicCreateEntFactoryFromEntity(self, FACTORY(BP_EMBERS, 3), 0);
            self->posY.i.hi += 10;
            self->ext.holywater.timer = 0x50;
            self->ext.holywater.unk80 = (rand() & 0xF) + 0x12;
            self->ext.holywater.angle = rand() & 0xFFF;
            self->step++;
        }
        break;
    case 2:
        xMod = -1;
        if (self->facingLeft) {
            xMod = -xMod;
        }
        angle = self->ext.holywater.angle;
        self->ext.holywater.angle += 0xC0;
        for (i = 0; i < 4; i++) {
            sp10[i] = self->posX.i.hi + (rsin(angle + (i * 1024)) >> 10);
        }
        sp10[4] = self->posX.i.hi;
        sp10[0] = self->posX.i.hi + xMod;
        angle = (self->ext.holywater.timer - 16) * 64 + 0xC00;
        flameHeight = (rsin(angle) >> 8) + self->ext.holywater.unk80;
        flameHeight = flameHeight * 3 >> 1;
        sp20[0] = self->posY.i.hi - flameHeight;
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
        while (prim) {
            if (self->ext.holywater.timer <= variant * 2 + 0x18) {
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
            prim->u0 = prim->u1 = texX + 0x80 - i * 7;
            prim->u2 = prim->u3 = texX + 0x80 - ((i + 1) * 7);
            prim->v0 = prim->v2 = texY + 0x80;
            prim->v1 = prim->v3 = texY + 0x90;
            if ((sp20[4] - sp20[0]) < 7) {
                prim->drawMode |= DRAW_HIDE;
                DestroyEntity(self);
                return;
            }
            i++;
            prim = prim->next;
        }
        self->hitboxHeight = flameHeight >> 1;
        self->hitboxOffY = (-flameHeight >> 1);
        break;
    }
    g_Player.timers[PL_T_3] = 2;
}
