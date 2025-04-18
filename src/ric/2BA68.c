// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"
#include "sfx.h"

void RicEntityNotImplemented3(Entity* self) {}

// Entity ID #35. Created by blueprint 40. No known FACTORY calls with
// blueprint 40. Duplicate of DRA EntityHolyWaterBreakGlass.
s16 D_80155D64[4][6] = {
    {2, -2, 0, -4, 0, 0},
    {-3, -3, -1, 1, 2, 0},
    {-4, -3, 2, -2, -2, 2},
    {-1, 0, 0, -4, 3, 3},
};
extern s16 D_80155D64[][6];
void func_80167A70(Entity* self) {
    Point16 sp10[8];
    Primitive* prim;
    FakePrim* fakeprim;
    s32 velX;
    s32 i;
    u16 posY;
    u16 posX;
    u8 arrIndex;
    u8 randbit;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        prim = &g_PrimBuf[self->primIndex];
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;

        for (i = 0; prim != NULL; i++, prim = prim->next) {
            if (i < 8) {
                fakeprim = (FakePrim*)prim;
                fakeprim->x0 = posX;
                fakeprim->posX.i.hi = posX;
                sp10[i].x = posX;
                fakeprim->y0 = posY;
                fakeprim->posY.i.hi = posY;
                sp10[i].y = posY;
                // Random velocity from 0.25 to 0.5
                velX = (rand() & 0x3FFF) + FIX(0.25);
                fakeprim->velocityX.val = velX;
                if (i & 1) {
                    fakeprim->velocityX.val = -velX;
                }
                fakeprim->velocityY.val = -((rand() * 2) + FIX(2.5));
                fakeprim->drawMode = DRAW_HIDE | DRAW_UNK02;
                fakeprim->type = PRIM_TILE;
            } else {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 =
                    (rand() & 0xF) | 0x30;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = rand() | 0x80;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 =
                    (rand() & 0x1F) + 0x30;
                randbit = rand() & 1;
                prim->drawMode = !(randbit) ? 6 : 0x37;
                posX = sp10[i - 8].x;
                posY = sp10[i - 8].y;
                arrIndex = i & 3;
                prim->u0 = arrIndex;
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
                fakeprim = (FakePrim*)prim;
                fakeprim->posX.i.hi = fakeprim->x0;
                fakeprim->posY.i.hi = fakeprim->y0;
                fakeprim->posX.val += fakeprim->velocityX.val;
                fakeprim->posY.val += fakeprim->velocityY.val;
                fakeprim->velocityY.val += FIX(36.0 / 128);
                sp10[i].x = fakeprim->posX.i.hi;
                sp10[i].y = fakeprim->posY.i.hi;
                fakeprim->x0 = fakeprim->posX.i.hi;
                fakeprim->y0 = fakeprim->posY.i.hi;
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
    s32 trigresult;
    s32 trigtemp;

    if (self->params < 40) {
        primcount = 32;
    } else {
        primcount = 33 - ((self->params - 32) * 2);
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
        line = (PrimLineG2*)&g_PrimBuf[self->primIndex];
        self->facingLeft = 0;
        while (line != NULL) {
            line->r0 = 0x1F;
            line->g0 = 0x1F;
            line->b0 = 0x30;
            line->r1 = 0x3F;
            line->g1 = 0x50;
            line->b1 = 0x7F;
            line->x1 = line->x0 = rand() & 0x1FF;
            line->y0 = line->y1 = -(rand() & 0xF);
            line->preciseX.i.hi = line->x1;
            line->preciseY.i.hi = line->y1;

            // This whole block is weird. Why are we calculating rcos
            // and rsin on a fixed value at runtime? And why aren't
            // these simple multiplications?
            trigresult = rcos(0xB80);
            trigtemp = trigresult * 16;
            line->velocityX.val = (trigresult * 32 + trigtemp) * 4;
            trigresult = rsin(0xB80);
            trigtemp = trigresult * -16;
            line->velocityY.val = trigtemp * 12;

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
            g_api.func_801027C4(3);
        }
        self->ext.subweapon.timer = 0x160;
        if ((self->params < 32) && !(self->params & 3)) {
            g_api.PlaySfx(SFX_RIC_HYDRO_STORM_ATTACK);
        }
        self->step++;
        break;
    case 1:
        line = (PrimLineG2*)&g_PrimBuf[self->primIndex];
        while (line != NULL) {
            if (line->timer == 0) {
                line->preciseX.i.hi = line->x1;
                line->preciseY.i.hi = line->y1;
                line->preciseX.val += line->velocityX.val;
                line->preciseY.val += line->velocityY.val;
                line->x1 = line->preciseX.i.hi;
                line->y1 = line->preciseY.i.hi;
                if (line->delay < line->y1) {
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
            line = line->next;
        }
        self->ext.subweapon.timer++;
        break;
    case 2:
#if defined(VERSION_HD)
        if (self->params == 0x28) {
            g_Player.unk4E = 1;
        }
#endif
        DestroyEntity(self);
        break;
    }
    g_Player.timers[PL_T_3] = 16;
}

// Copy of DRA function
s32 RicCheckHolyWaterCollision(s32 baseY, s32 baseX) {
    s16 x;
    s16 y;
    Collider res1;
    Collider res2;
    s16 colRes1;
    s16 colRes2;

    const u32 colFullSet =
        (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 | EFFECT_UNK_1000 |
         EFFECT_UNK_0800 | EFFECT_SOLID);
    const u32 colSetNo800 = (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                             EFFECT_UNK_2000 | EFFECT_UNK_1000 | EFFECT_SOLID);
    const u32 colSet1 = (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SOLID);
    const u32 colSet2 = (EFFECT_UNK_8000 | EFFECT_SOLID);
    x = baseX + g_CurrentEntity->posX.i.hi;
    y = baseY + g_CurrentEntity->posY.i.hi;

    g_api.CheckCollision(x, y, &res1, 0);
    colRes1 = res1.effects & colFullSet;
    g_api.CheckCollision(x, (s16)(y - 1 + res1.unk18), &res2, 0);
    y = baseY + (g_CurrentEntity->posY.i.hi + res1.unk18);

    if ((colRes1 & colSet1) == EFFECT_SOLID ||
        (colRes1 & colSet1) == (EFFECT_UNK_0800 | EFFECT_SOLID)) {
        colRes2 = res2.effects & colSetNo800;
        if (!((s16)res2.effects & EFFECT_SOLID)) {
            g_CurrentEntity->posY.i.hi = y;
            return 1;
        }
        if ((res2.effects & colSet2) == colSet2) {
            g_CurrentEntity->posY.i.hi = y + (s16)(res2.unk18 - 1);
            return colRes2;
        }
    } else if ((colRes1 & colSet2) == colSet2) {
        g_CurrentEntity->posY.i.hi = y;
        return colRes1 & colSetNo800;
    }
    return 0;
}

s32 func_8016840C(s16 x, s16 y) {
    Collider collider;
    u16 temp;

    if (g_CurrentEntity->velocityX != 0) {
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi + y,
                             g_CurrentEntity->posY.i.hi + x, &collider, 0);
        if (g_CurrentEntity->velocityX > 0) {
            temp = collider.unk14;
        } else {
            temp = collider.unk1C;
        }
        if (!(collider.effects & EFFECT_UNK_0002)) {
            return 0;
        }
    } else {
        return 0;
    }
    g_CurrentEntity->posX.i.lo = 0;
    g_CurrentEntity->posX.i.hi += temp;
    return 2;
}
