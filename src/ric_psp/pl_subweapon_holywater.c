// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../ric/ric.h"

void RicEntityNotImplemented3(Entity* self) {}

// Entity ID #35. Created by blueprint 40. No known FACTORY calls with
// blueprint 40. Duplicate of DRA EntityHolyWaterBreakGlass.
static s16 D_80155D64[4][6] = {
    {2, -2, 0, -4, 0, 0},
    {-3, -3, -1, 1, 2, 0},
    {-4, -3, 2, -2, -2, 2},
    {-1, 0, 0, -4, 3, 3}};
#define FAKEPRIM ((FakePrim*)prim)
void RicEntityHolyWaterBreakGlass(Entity* self) {
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

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/pl_subweapon_holywater", RicEntityCrashHydroStorm);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/pl_subweapon_holywater", RicCheckHolyWaterCollision);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/pl_subweapon_holywater", func_8016840C);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/pl_subweapon_holywater", RicEntitySubwpnHolyWater);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/pl_subweapon_holywater", RicEntitySubwpnHolyWaterFlame);

