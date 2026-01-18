// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"
#include "subwpn_dagger.h"

// dagger thrown when using subweapon
void EntitySubwpnKnife(Entity* self) {
    Collider collider;
    Primitive* prim;
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
    s32 i;

    switch (self->step) {
    case DAGGER_INIT:
        self->primIndex = AllocPrimitives(PRIM_GT4, 2);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->facingLeft = PLAYER.facingLeft;
        func_8011A290(self);
        self->hitboxWidth = 4;
        self->hitboxHeight = 2;
        self->hitboxOffX = 4;
        self->hitboxOffY = 0;
        if (!(g_Player.status & PLAYER_STATUS_CROUCH)) {
            self->posY.i.hi -= 9;
        }
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1C;
        prim->clut = PAL_UNK_1AB;
        prim->u0 = prim->u1 = 0x18;
        prim->v0 = prim->v2 = 0x18;
        prim->u2 = prim->u3 = 0x20;
        prim->v1 = prim->v3 = 0;
        prim->priority = PLAYER.zPriority + 2;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;

        prim = prim->next;
        prim->type = PRIM_LINE_G2;
        prim->priority = PLAYER.zPriority + 2;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE | DRAW_UNK02 | DRAW_TRANSP;
        prim->r0 = 0x7F;
        prim->g0 = 0x3F;
        prim->b0 = 0;
        SetSpeedX(FIX(8));
        PlaySfx(SFX_WEAPON_SWISH_C);
        g_Player.timers[ALU_T_10] = 4;
        self->step++;
        break;
    case DAGGER_FLYING:
        self->ext.timer.t++;
        if (self->velocityX > 0) {
            xCol = 8;
        }
        if (self->velocityX < 0) {
            xCol = -8;
        }
        if (self->hitFlags == 1) {
            self->ext.timer.t = 4;
            self->step = DAGGER_HIT_ENEMY;
            self->hitboxState = 0;
            return;
        }
        for (i = 0; i < 8; i++) {
            if (self->velocityX > 0) {
                self->posX.i.hi++;
            }
            if (self->velocityX < 0) {
                self->posX.i.hi--;
            }
            CheckCollision(
                self->posX.i.hi + xCol, self->posY.i.hi, &collider, 0);
            if (self->hitFlags == 2 ||
                collider.effects & (EFFECT_SOLID | EFFECT_UNK_0002)) {
                self->ext.timer.t = 64;
                self->velocityX = -(self->velocityX >> 3);
                self->velocityY = FIX(-2.5);
                self->hitboxState = 0;
                self->posX.i.hi += xCol;
                CreateEntFactoryFromEntity(self, FACTORY(BP_10, 0), 0);
                self->posX.i.hi -= xCol;
                PlaySfx(SFX_UI_SUBWEAPON_TINK);
                self->step++;
                return;
            }
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
            self->rotate -= 0x80;
        } else {
            angle2 = 0x800 - 0xD2;
            angle1 = 0xD2;
            angle4 = 0x800 + 0xD2;
            angle3 = -0xD2;
            self->rotate += 0x80;
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

// clang-format off
static u8 D_800B0628[] = {
    0x4F, 0x4F, 0x4F, 0x00, 
    0x4F, 0x4F, 0x4F, 0x00, 
    0x4F, 0x4F, 0x4F, 0x00,
    0x3F, 0x3F, 0x5F, 0x00, 
    0x3F, 0x3F, 0x5F, 0x00, 
    0x3F, 0x3F, 0x5F, 0x00,
    0x2F, 0x2F, 0x6F, 0x00, 
    0x2F, 0x2F, 0x6F, 0x00, 
    0x1F, 0x1F, 0x7F, 0x00,
    0x1F, 0x1F, 0x7F, 0x00};

static u16 dirty_data_10650[] = {16, 0, -1, 0};

// clang-format on

// axe thrown when using subweapon
// near-duplicate of RicEntitySubwpnThrownAxe
typedef enum { AXE_INIT, AXE_FLYING, AXE_BOUNCE } AxeSteps;
void EntitySubwpnThrownAxe(Entity* self) {
    u8 rVal;
    u8 gVal;
    u8 bVal;
    s16 xVar;
    s16 yVar;
    s32 rgbIdx;
    s16 angle0;
    s16 angle1;
    s16 angle2;
    s16 angle3;
    s16 angleOffset;
    s32 twentyone;
    Primitive* prevPrim;
    s32 i;
    Primitive* prim;
    s32 graphicsTemp;

    twentyone = 21;

    switch (self->step) {
    case AXE_INIT:
        self->primIndex = AllocPrimitives(PRIM_GT4, 5);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_HAS_PRIMS | FLAG_UNK_20000;
        self->facingLeft = (PLAYER.facingLeft + 1) & 1;
        SetSpeedX(FIX(-2));
        self->velocityY = FIX(-6);
        if (self->facingLeft) {
            self->ext.subwpnAxe.unk7C = 0x400;
        } else {
            self->ext.subwpnAxe.unk7C = 0xC00;
        }

        if (!(g_Player.status & PLAYER_STATUS_CROUCH)) {
            self->posY.i.hi -= 12;
        }
        for (prim = &g_PrimBuf[self->primIndex], i = 0; prim != NULL; i++,
            prim = prim->next) {
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
            if (i != 0) {
                prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE |
                                 DRAW_HIDE | DRAW_COLORS | DRAW_TRANSP;
                self->ext.subwpnAxe.unk8C[i - 1] = 0;
                self->ext.subwpnAxe.unk90[i - 1] = 0;
                self->ext.subwpnAxe.unk94[i - 1] = 0;
            } else {
                prim->drawMode = DRAW_UNK_100 | DRAW_HIDE;
            }
        }
        func_8011A290(self);
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
        PlaySfx(SFX_WEAPON_SWISH_C);
        g_Player.timers[ALU_T_10] = 4;
        self->ext.subwpnAxe.unk98 = 0x7F;
        self->step++;
        break;
    case AXE_FLYING:
        if (self->facingLeft) {
            angleOffset = -0x80;
        } else {
            angleOffset = 0x80;
        }
        self->ext.subwpnAxe.unk7C += angleOffset;
        if (!(self->ext.subwpnAxe.unk7C & 0x3FF)) {
            PlaySfxVolPan(SFX_WEAPON_SWISH_C, self->ext.subwpnAxe.unk98, 0);
            self->ext.subwpnAxe.unk98 -= 8;
            if (self->ext.subwpnAxe.unk98 < 0) {
                self->ext.subwpnAxe.unk98 = 0;
            }
        }
        self->velocityY += FIX(34.0 / 128);
        if (self->velocityY > FIX(8)) {
            self->velocityY = FIX(8);
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->posY.i.hi > 0x100) {
            DestroyEntity(self);
            return;
        }
        if (self->hitFlags == 2) {
            self->hitboxState = 0;
            self->velocityX = -(self->velocityX / 2);
            self->velocityY = FIX(-3);
            self->step = AXE_BOUNCE;
        }
        break;
    case AXE_BOUNCE:
        if (self->facingLeft) {
            angleOffset = 0xC0;
        } else {
            angleOffset = -0xC0;
        }
        self->ext.subwpnAxe.unk7C += angleOffset;
        self->velocityY += FIX(18.0 / 128);
        if (self->velocityY > FIX(8)) {
            self->velocityY = FIX(8);
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->posY.i.hi > 0x100) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    if (self->poseTimer == 0) {
        graphicsTemp = self->pose;
        self->ext.subwpnAxe.unk8C[graphicsTemp] = 0;
        self->ext.subwpnAxe.unk90[graphicsTemp] = 1;
        self->ext.subwpnAxe.unk94[graphicsTemp] = 1;
        graphicsTemp++;
        graphicsTemp &= 3;
        self->pose = graphicsTemp;
        self->poseTimer = 2;
    } else {
        self->poseTimer--;
    }
    for (prim = &g_PrimBuf[self->primIndex], prevPrim = prim,
        graphicsTemp = ((g_GameTimer >> 1) & 1) + 0x1AB, i = 0;
         prim != NULL; i++, prim = prim->next) {
        prim->clut = graphicsTemp;
        if (i == 0) {
            if (self->facingLeft) {
                angle0 = 0x560;
                angle1 = 0x2A0;
                angle2 = 0xAA0;
                angle3 = 0xD60;
            } else {
                angle1 = 0x560;
                angle0 = 0x2A0;
                angle3 = 0xAA0;
                angle2 = 0xD60;
            }

            xVar = self->posX.i.hi;
            yVar = self->posY.i.hi;
            angleOffset = self->ext.subwpnAxe.unk7C;
            angle0 += angleOffset;
            angle1 += angleOffset;
            angle2 += angleOffset;
            angle3 += angleOffset;
            prim->x0 = xVar + (((rcos(angle0) << 4) * twentyone) >> 0x10);
            prim->y0 = yVar + -(((rsin(angle0) << 4) * twentyone) >> 0x10);
            prim->x1 = xVar + (((rcos(angle1) << 4) * twentyone) >> 0x10);
            prim->y1 = yVar + -(((rsin(angle1) << 4) * twentyone) >> 0x10);
            prim->x2 = xVar + (((rcos(angle2) << 4) * twentyone) >> 0x10);
            prim->y2 = yVar + -(((rsin(angle2) << 4) * twentyone) >> 0x10);
            prim->x3 = xVar + (((rcos(angle3) << 4) * twentyone) >> 0x10);
            prim->y3 = yVar + -(((rsin(angle3) << 4) * twentyone) >> 0x10);
            prim->drawMode &= ~DRAW_HIDE;
        } else if (self->ext.subwpnAxe.unk90[i - 1]) {
            if (self->ext.subwpnAxe.unk94[i - 1]) {
                self->ext.subwpnAxe.unk94[i - 1] = 0;
                prim->x0 = prevPrim->x0;
                prim->y0 = prevPrim->y0;
                prim->x1 = prevPrim->x1;
                prim->y1 = prevPrim->y1;
                prim->x2 = prevPrim->x2;
                prim->y2 = prevPrim->y2;
                prim->x3 = prevPrim->x3;
                prim->y3 = prevPrim->y3;
            }
            rgbIdx = self->ext.subwpnAxe.unk8C[i - 1]++;
            if (rgbIdx < 10) {
                rVal = D_800B0628[rgbIdx * 4 + 0];
                gVal = D_800B0628[rgbIdx * 4 + 1];
                bVal = D_800B0628[rgbIdx * 4 + 2];
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
                self->ext.subwpnAxe.unk90[i - 1] = 0;
                prim->drawMode |= DRAW_HIDE;
            }
        }
    }
}

// Equivalent to RicCheckHolyWaterCollision
s32 CheckHolyWaterCollision(s16 baseY, s16 baseX) {
    Collider res1;
    Collider res2;
    s16 x;
    s16 newY;
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

    CheckCollision(x, y, &res1, 0);
    collEffs = res1.effects & colFullSet;
    y = y - 1 + res1.unk18;
    CheckCollision(x, y, &res2, 0);
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

// Equivalent to RIC func_8016840C
s32 func_80125B6C(s16 y, s16 x) {
    Collider collider;
    s16 xShift;

    if (g_CurrentEntity->velocityX == 0) {
        return 0;
    }
    CheckCollision(g_CurrentEntity->posX.i.hi + x,
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

extern s32 D_8013841C;

typedef enum {
    HOLYWATER_INIT,
    HOLYWATER_FLYING,
    HOLYWATER_BREAK,
    HOLYWATER_DESTROY
} HolyWaterSteps;
void EntitySubwpnHolyWater(Entity* self) {
    s16 xOffset;
    s32 collisionFlags = 0;

    switch (self->step) {
    case HOLYWATER_INIT:
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->animSet = ANIMSET_DRA(9);
        self->animCurFrame = 0x1D;
        self->zPriority = PLAYER.zPriority - 2;
        self->posY.i.hi += 8;
        SetSpeedX(FIX(1.25));
        self->velocityY = FIX(-3.125);
        func_8011A290(self);
        self->hitboxWidth = self->hitboxHeight = 4;
        g_Player.timers[ALU_T_10] = 4;
        self->step++;
        break;
    case HOLYWATER_FLYING:
        self->posY.val += self->velocityY;
        if (self->velocityY < FIX(4)) {
            self->velocityY += FIX(28.0 / 128);
        }

        collisionFlags = CheckHolyWaterCollision(0, 0);
        self->posX.val += self->velocityX;
        xOffset = 4;
        if (self->velocityX < 0) {
            xOffset = -xOffset;
        }
        collisionFlags |= func_80125B6C(-7, xOffset);

        if (collisionFlags & 2) {
            collisionFlags = 1;
        }

        if (collisionFlags & 1) {
            PlaySfx(SFX_ALU_HOLY_WATER_ATTACK);
            // Factory 59 has child 40, EntitySubwpnHolyWaterBreakGlass
            CreateEntFactoryFromEntity(self, FACTORY(BP_59, 0), 0);
            self->animSet = ANIMSET_DRA(0);
            self->ext.holywater.timer = 16;
            self->step = HOLYWATER_BREAK;
        }
        break;

    case HOLYWATER_BREAK:
        if (!(self->ext.holywater.timer & 3)) {
            // Factory 28 has child 23, EntitySubwpnHolyWaterFlame
            CreateEntFactoryFromEntity(
                self, FACTORY(BP_HOLY_WATER_FLAME, D_8013841C),
                self->ext.holywater.unkB2 << 9);
            D_8013841C++;
        }
        if (--self->ext.holywater.timer == 0) {
            self->ext.holywater.timer = 4;
            self->step++;
        }
        break;

    case HOLYWATER_DESTROY:
        if (--self->ext.holywater.timer == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

// Glass breaking effect for holy water. Duplicate of RIC
// RicEntitySubwpnHolyWaterBreakGlass.
static s16 D_800B0658[4][6] = {
    {2, -2, 0, -4, 0, 0},
    {-3, -3, -1, 1, 2, 0},
    {-4, -3, 2, -2, -2, 2},
    {-1, 0, 0, -4, 3, 3}};
#define FAKEPRIM ((FakePrim*)prim)
void EntitySubwpnHolyWaterBreakGlass(Entity* self) {
    Point16 sp10[8];
    Primitive* prim;
    s16 posX;
    s16 posY;
    s16 arrIndex;
    s32 i;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, 16);
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
                prim->x0 = posX + D_800B0658[arrIndex][0];
                prim->y0 = posY + D_800B0658[arrIndex][1];
                prim->x1 = posX + D_800B0658[arrIndex][2];
                prim->y1 = posY + D_800B0658[arrIndex][3];
                prim->x3 = prim->x2 = posX + D_800B0658[arrIndex][4];
                prim->y3 = prim->y2 = posY + D_800B0658[arrIndex][5];
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
                prim->x0 = posX + D_800B0658[arrIndex][0];
                prim->y0 = posY + D_800B0658[arrIndex][1];
                prim->x1 = posX + D_800B0658[arrIndex][2];
                prim->y1 = posY + D_800B0658[arrIndex][3];
                prim->x3 = prim->x2 = posX + D_800B0658[arrIndex][4];
                prim->y3 = prim->y2 = posY + D_800B0658[arrIndex][5];
            }
        }
        break;
    }
}

// Used as Point32, but data is raw, not struct.
s32 D_800B0688[16] = {28, 0, 28, 16, 28, 32, 28, 48,
                      60, 0, 60, 16, 60, 32, 60, 48};

// green flame when holy water explodes
void EntitySubwpnHolyWaterFlame(Entity* self) {
    s16 sp10[5];
    s16 sp20[5];
    s16 xMod; // unused
    Primitive* prim;
    s16 flameHeight;
    s16 angle;
    s32 i;
    u8 randR;
    u8 randG;
    u8 randB;
    u8 texX;
    u8 texY;

    texX = D_800B0688[(g_GameTimer & 7) * 2 + 0];
    texY = D_800B0688[(g_GameTimer & 7) * 2 + 1];
    switch (self->step) {
    case 0:
        randR = (rand() & 0x1F) + 0x40;
        randG = (rand() & 0x1F) + 0x80;
        randB = (rand() & 0x1F) + 0x60;
        self->primIndex = AllocPrimitives(PRIM_GT4, 4);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        // i is unused in this loop
        for (prim = &g_PrimBuf[self->primIndex], i = 0; prim != NULL; i++,
            prim = prim->next) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = randR;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = randG;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = randB;
            prim->clut = PAL_UNK_1B2;
            prim->tpage = 0x1A;
            prim->priority = PLAYER.zPriority + 2;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP |
                             DRAW_UNK02 | DRAW_COLORS | DRAW_HIDE;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        func_8011A290(self);
        self->hitboxWidth = 4;
        self->posY.i.hi -= 10;
        CreateEntFactoryFromEntity(self, FACTORY(BP_4, 7), 0);
        self->posY.i.hi += 10;
        self->ext.holywater.timer = 0x50;
        self->ext.holywater.unk80 = (rand() & 0xF) + 0x12;
        self->step++;
        break;
    case 1:
        xMod = -1;
        if (self->facingLeft) {
            xMod = -xMod;
        }
        angle = self->ext.holywater.angle;
        self->ext.holywater.angle += 0x180;
        for (i = 0; i < 4; i++) {
            sp10[i] = self->posX.i.hi + (rsin(angle + (i << 10)) >> 10);
        }
        sp10[0] = self->posX.i.hi;
        sp10[4] = self->posX.i.hi;
        angle = ((self->ext.holywater.timer - 0x10) * 64) + 0xC00;
        flameHeight = (rsin(angle) >> 8) + self->ext.holywater.unk80;
        sp20[0] = self->posY.i.hi - flameHeight;
        sp20[4] = self->posY.i.hi;
        sp20[2] = (sp20[0] + sp20[4]) / 2;
        sp20[1] = (sp20[0] + sp20[2]) / 2;
        sp20[3] = (sp20[2] + sp20[4]) / 2;
        prim = &g_PrimBuf[self->primIndex];
        if (self->ext.holywater.timer & 3) {
            self->hitboxState = 0;
        } else {
            self->hitboxState = 2;
        }
        if (--self->ext.holywater.timer < 0x11) {
            DestroyEntity(self);
            return;
        }
        for (i = 0; prim != NULL; i++, prim = prim->next) {
            if (self->ext.holywater.timer < 0x29) {
                if (prim->g0 > 16) {
                    prim->g0 -= 5;
                }
                if (prim->b0 > 16) {
                    prim->b0 -= 5;
                }
                if (prim->r0 > 16) {
                    prim->r0 -= 5;
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
            prim->u0 = prim->u1 = texX + 0x80 - (i * 7);
            prim->u2 = prim->u3 = texX + 0x80 - ((i + 1) * 7);
            prim->v0 = prim->v2 = texY + 0x80;
            prim->v1 = prim->v3 = texY + 0x90;
            if ((sp20[4] - sp20[0]) < 7) {
                prim->drawMode |= DRAW_HIDE;
            }
        }
        self->hitboxHeight = flameHeight >> 1;
        self->hitboxOffY = (-flameHeight >> 1);
        break;
    }
}

u32 D_800B06C8[] = {
    0x98C694A5, 0xA1089CE7, 0xA94AA529, 0xB18CAD6B, 0xB9CEB5AD, 0xC210BDEF,
    0xCA52C631, 0xD294CE73, 0xDAD6D6B5, 0xE318DEF7, 0xE318E318, 0xE318E318,
    0xE318E318, 0xE318E318, 0xDEF7E318, 0xD6B5DAD6, 0xCE73D294, 0xC631CA52,
    0xBDEFC210, 0xB5ADB9CE, 0xAD6BB18C, 0xA529A94A, 0x9CE7A108, 0x94A598C6};

u32 D_800B0728[] = {
    0x910C90EB, 0x914E912D, 0x9190916F, 0x91D291B1, 0x921491F3, 0x92569235,
    0x92989277, 0x92DA92B9, 0x92DA92DA, 0x92DA92DA, 0x92DA92DA, 0x92DA92DA,
    0x92DA92DA, 0x92DA92DA, 0x92DA92DA, 0x92DA92DA, 0x92B992DA, 0x92779298,
    0x92359256, 0x91F39214, 0x91B191D2, 0x916F9190, 0x912D914E, 0x90EB910C};

RECT D_800B0788 = {0x0301, 0x01F8, 0x0030, 0x0001};
RECT D_800B0790 = {0x0301, 0x01FC, 0x0030, 0x0001};

// cross subweapon crash (full effect with all parts)
void EntitySubwpnCrashCross(Entity* self) {
    Primitive* prim;
    s16 right;
    s16 left;
    s16 three = 3;
    s16 one = 1;

    func_8010DFF0(1, 1);
    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS;
        self->posY.i.hi = 0x78;
        self->ext.crashcross.unk80 = 1;
        self->zPriority = 0xC2;
        func_8011A290(self);
        LoadImage(&D_800B0788, (u_long*)D_800B06C8);
        prim = &g_PrimBuf[self->primIndex];
        prim->v0 = prim->v1 = prim->v2 = prim->v3 = 0xF8;
        prim->u0 = prim->u2 = 1;
        prim->u1 = prim->u3 = 0x30;
        prim->b3 = 0x80;
        prim->tpage = 0x11C;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        PlaySfx(SFX_CRASH_CROSS);
        PlaySfx(SFX_TELEPORT_BANG_B);
        self->step += 1;
        g_Player.timers[12] = 4;
        break;
    case 1:
        self->ext.crashcross.unk7E.val += three;
        self->ext.crashcross.unk82 += three * 2;
        if (self->ext.crashcross.unk7E.i.lo >= 0x70) {
            CreateEntFactoryFromEntity(self, 7, self->ext.factory.unkB2 << 9);
            CreateEntFactoryFromEntity(self, 8, 0);
            self->step += 1;
        }
        break;
    case 2:
        if (!(g_Timer & 1)) {
            break;
        }
        self->ext.crashcross.unk7C += one;
        self->ext.crashcross.unk80 += one * 2;
        if (self->ext.crashcross.unk80 >= 0x2C) {
            self->step += 1;
            self->ext.crashcross.unk84 = 0x80;
        }
        break;
    case 3:
        if (--self->ext.crashcross.unk84 == 0) {
            left = self->posX.i.hi - self->ext.crashcross.unk7C;
            if (left < 0) {
                left = 0;
            }
            right = self->posX.i.hi + self->ext.crashcross.unk7C;
            if (right > 0xFF) {
                right = 0xFF;
            }
            self->step += 1;
            PlaySfx(SFX_WEAPON_APPEAR);
        }
        break;
    case 4:
        one *= 3;
        left = abs(self->posX.i.hi - 0x80);
        one = one * (left + 0x80) / 112;
        self->ext.crashcross.unk7C += one;

        left = self->posX.i.hi - self->ext.crashcross.unk7C;
        right = self->posX.i.hi + self->ext.crashcross.unk7C;
        if (right > 0x180 && left < -0x80) {
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
        self->hitboxWidth = self->ext.crashcross.unk7C;
        self->hitboxOffX = 0;
    }
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = prim->x2 = self->posX.i.hi - self->ext.crashcross.unk7C;
    prim->y1 = prim->y0 = self->posY.i.hi - self->ext.crashcross.unk7E.val;
    prim->x1 = prim->x3 = prim->x0 + self->ext.crashcross.unk80;
    prim->y2 = prim->y3 = prim->y0 + self->ext.crashcross.unk82;

    if (self->step == 4) {
        if (prim->b3 < 0xF8) {
            prim->b3 += 4;
        }
        prim->x0 = prim->x2 = left;
        prim->x1 = prim->x3 = right;
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
            prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
    }
    prim->priority = self->zPriority;
}

// rising blue particles from cross crash
void EntitySubwpnCrashCrossParticles(Entity* self) {
    s16 rand63;
    s16 var_g0;
    s16 var_g1;
    Primitive* prim;

    if (self->step == 0) {
        self->primIndex = AllocPrimitives(PRIM_GT4, 64);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        // entity lives for 192 frames
        self->ext.timer.t = 192;
        self->step++;
        return;
    }
    // This is some kind of time to live, since it decrements and if 0 gets
    // destroyed.
    if (--self->ext.timer.t == 0) {
        DestroyEntity(self);
        return;
    }
    // On every third frame, as long as we have over 8 frames left alive
    if ((self->ext.timer.t > 8) && !(self->ext.timer.t & 3)) {
        // iterate through primtives until we find one where r0 == 0, and set to
        // 1
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
        // for any of those prims with nonzero r0 values,
        if (prim->r0) {
            // r1 acts as a flag to show whether this has happened.
            if (prim->r1 == 0) {
                rand63 = rand() & 0x3F; // random integer 0-63
                prim->g0 = (rand() % 237) + 9;
                prim->g1 = 0xF0 - (rand() & 0x20);
                prim->clut = PAL_UNK_1B0;
                prim->tpage = 0x1A;
                prim->b0 = 0;
                prim->b1 = 0;
                prim->priority = (PLAYER.zPriority + rand63) - 0x20;
                prim->drawMode = DRAW_DEFAULT;
                prim->g3 = ((u8)rand63 >> 2) + 4; // rand15 + 4 means 4 to 19
                prim->r1++;
            } else {
                prim->g1 -= prim->g3;
                if ((prim->b0 >= 6) || (prim->g1 < 24)) {
                    prim->drawMode = DRAW_HIDE;
                    prim->r0 = 0;
                }
            }
            if (prim->r0) {
                // This is stupid.
                var_g0 = 0;
                var_g1 = 0;
                var_g0 |= prim->g0;
                var_g1 |= prim->g1;
                func_80119E78(prim, var_g0, var_g1);
            }
        }
    }
}

typedef enum {
    HFH_INIT,
    HFH_STARTDELAY,
    HFH_BEAMWIDEN,
    HFH_BEAMFLICKER,
    HFH_BEAMSHRINK,
    HFH_PLAYER_DISAPPEAR,
    HFH_PLAYER_REAPPEAR,
    HFH_FINAL_PHASE
} HellfireHandlerSteps;

void EntityHellfire(Entity* self) {
    Primitive* prim;
    s16 selfPosX;
    s16 selfPosY;
    // These are probably adjustable variables but for now we don't
    // know what they are for so we just name them for their values
    s16 sixteen = 16;
    s16 four = 4;

    if (PLAYER.step != Player_SpellHellfire) {
        DestroyEntity(self);
        return;
    }

    FntPrint("light_timer:%02x\n", self->ext.hellfireHandler.timer);

    selfPosX = self->posX.i.hi = PLAYER.posX.i.hi;
    switch (self->step) {
    case HFH_INIT:
        g_Player.unk5C = 0;
        self->primIndex = AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            g_Player.unk5C = -1;
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS |
                      FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        self->posY.i.hi = 120;
        // I think this is to make the yellow laser beam?
        // it ends up looking like the library card effect.
        LoadImage(&D_800B0788, (u_long*)D_800B06C8);
        LoadImage(&D_800B0790, (u_long*)D_800B0728);
        prim = &g_PrimBuf[self->primIndex];
        prim->v0 = prim->v1 = prim->v2 = prim->v3 = 0xF8;
        prim->u0 = prim->u2 = 1;
        prim->u1 = prim->u3 = 0x30;
        prim->b3 = 0x80;
        prim->tpage = 0x11C;
        prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                         DRAW_TPAGE | DRAW_TRANSP;
        prim->priority = self->zPriority = 0x1C0;
        PlaySfx(SFX_TELEPORT_BANG_B);
        self->step++;
        break;
    case HFH_STARTDELAY:
        // Nothing happens since beamwidth is zero.
        self->ext.hellfireHandler.beamheight += sixteen;
        if (self->ext.hellfireHandler.beamheight >= 0x80) {
            self->step++;
        }
        break;
    case HFH_BEAMWIDEN:
        self->ext.hellfireHandler.beamwidth += four;
        if (self->ext.hellfireHandler.beamwidth >= 0x16) {
            self->ext.hellfireHandler.timer = 0x20;
            self->step++;
        }
        break;
    case HFH_BEAMFLICKER:
        if (--self->ext.hellfireHandler.timer == 0) {
            PLAYER.palette = PAL_FLAG(PAL_PLAYER_HIDDEN);
            self->step++;
        }
        break;
    case HFH_BEAMSHRINK:
        PLAYER.palette = PAL_FLAG(PAL_PLAYER_HIDDEN);
        self->ext.hellfireHandler.beamwidth -= four * 2;
        if (self->ext.hellfireHandler.beamwidth < 0) {
            self->step++;
            self->ext.hellfireHandler.timer = 0x2A;
            prim = &g_PrimBuf[self->primIndex];
            prim->drawMode |= DRAW_HIDE;
            g_Player.unk5C = 1;
        }
        break;
    case HFH_PLAYER_DISAPPEAR:
        PLAYER.palette = PAL_FLAG(PAL_PLAYER_HIDDEN);
        if (self->ext.hellfireHandler.timer == 0x10) {
            // Red flickering beam. Blueprint 38 has child 29 or func_80127CC8
            CreateEntFactoryFromEntity(self, FACTORY(BP_38, 0), 0);
        }
        if (--self->ext.hellfireHandler.timer == 0) {
            self->step++;
            self->ext.hellfireHandler.beamwidth = 0;
            prim = &g_PrimBuf[self->primIndex];
            prim->drawMode &= ~DRAW_HIDE;
        }
        if (self->ext.hellfireHandler.timer == 2) {
            g_Player.unk5C = 2;
        }
        break;
    case HFH_PLAYER_REAPPEAR:
        PLAYER.palette = PAL_FLAG(PAL_ALUCARD);
        self->ext.hellfireHandler.beamwidth += four;
        if (self->ext.hellfireHandler.beamwidth >= 0x16) {
            self->step++;
            self->ext.hellfireHandler.timer = 0x60;
            prim = &g_PrimBuf[self->primIndex];
        }
        break;
    case HFH_FINAL_PHASE:
        if (self->ext.hellfireHandler.timer == 0x50) {
            g_Player.unk5C = 3;
        }
        if (self->ext.hellfireHandler.timer == 0x30) {
            // When you press up during hellfire, you get different fireballs.
            if (g_Player.padPressed & PAD_UP) {
                // Blueprint 35 makes child 27, the big black fireballs
                CreateEntFactoryFromEntity(self, 35, 0);
            } else {
                // Blueprint 34 makes child 26, the small, normal fireballs
                CreateEntFactoryFromEntity(self, 34, 0);
            }
        }
        if (self->ext.hellfireHandler.timer == 0x50) {
            CreateEntFactoryFromEntity(self, FACTORY(BP_4, 10), 0);
        }
        if (self->ext.hellfireHandler.timer < 0x48) {
            self->ext.hellfireHandler.beamwidth -= four;
            if (self->ext.hellfireHandler.beamwidth < 0) {
                self->ext.hellfireHandler.beamwidth = 0;
            }
        }
        if (--self->ext.hellfireHandler.timer == 0x28) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    selfPosY = self->posY.i.hi = 0x78;
    prim = &g_PrimBuf[self->primIndex];
    if (g_GameTimer & 1) {
        prim->v0 = prim->v1 = prim->v2 = prim->v3 = 0xF8;
    } else {
        prim->v0 = prim->v1 = prim->v2 = prim->v3 = 0xFC;
    }
    prim->x0 = prim->x2 = selfPosX - self->ext.hellfireHandler.beamwidth;
    prim->y1 = prim->y0 = selfPosY - self->ext.hellfireHandler.beamheight;
    prim->x1 = prim->x3 = selfPosX + self->ext.hellfireHandler.beamwidth;
    prim->y2 = prim->y3 = selfPosY + self->ext.hellfireHandler.beamheight;
    if (self->step == HFH_BEAMFLICKER) {
        if (prim->b3 < 0xF8) {
            prim->b3 += 4;
        }
        PCOL(prim);
    }
    if (self->step == HFH_FINAL_PHASE) {
        if (prim->b3 > 0x20) {
            prim->b3 -= 0x20;
        }
        PCOL(prim);
    }
}

AnimationFrame D_800B0798[] = {
    {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {1, 8}, {0, 0}};

// no known usages; stripped on psp
AnimationFrame D_800B07BC[] = {{2, 9}, {1, 16}, {0, 0}};

AnimationFrame D_800B07C8[] = {
    {5, 13}, {2, 14}, {2, 14}, {2, 16}, {1, 17}, {1, 18}, {1, 19},
    {1, 20}, {1, 21}, {1, 22}, {1, 23}, {1, 24}, {1, 25}, {1, 26},
    {1, 27}, {1, 28}, {2, 9},  {1, 16}, {2, 10}, {1, 16}, {2, 11},
    {1, 16}, {2, 12}, {2, 9},  {1, 16}, {0, 23}};

s32 D_800B0830[] = {FIX(-2.5), FIX(-2.5), FIX(-2.5)};
s32 D_800B083C[] = {FIX(0), FIX(-0.75), FIX(0.75)};

// The fireball produced by Hellfire, when you do NOT press up
void EntityHellfireNormalFireball(Entity* self) {
    switch (self->step) {
    case 0:
        if (self->params == 0) {
            PlaySfx(SFX_FIREBALL_SHOT_A);
        }
        self->flags = FLAG_UNK_100000 | FLAG_POS_CAMERA_LOCKED;
        self->animSet = ANIMSET_DRA(9);
        self->anim = D_800B0798;
        self->zPriority = PLAYER.zPriority + 2;
        self->facingLeft = (PLAYER.facingLeft + 1) & 1;
        SetSpeedX(D_800B0830[self->params]);
        self->velocityY = D_800B083C[self->params];
        self->ext.timer.t = 20;
        func_8011A328(self, 2);
        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        self->step++;
        break;

    case 1:
        // Fireballs hitting anything destroys them.
        if (self->hitFlags) {
            DestroyEntity(self);
            break;
        }

        if (--self->ext.timer.t == 0) {
            self->step++;
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        break;
    case 2:
        if (self->hitFlags) {
            DestroyEntity(self);
            break;
        }
        self->posX.val += self->velocityX;
        break;
    }
}

// Entity ID 45. Created by factory blueprint 81.
// That blueprint is used in ControlBatForm, when step_s is 4.
// Also, when bat familiar shoots a fireball, the blueprint
// is used in UpdateBatAttackMode.

void EntityBatFireball(Entity* self) {
    // This is a 1 when a bat familiar is shooting, and a 0
    // when the player (in bat form) is shooting the fireball.
    // Appears to have no impact on the behavior of this function.
    s16 params = (self->params >> 8) & 0x7F;

    switch (self->step) {
    case 0:
        PlaySfx(SFX_QUICK_STUTTER_EXPLODE_A);
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_100000;
        self->animSet = 9;
        self->anim = D_800B0798;
        self->zPriority = PLAYER.zPriority - 2;

        // Wow, this is weird logic! But it's in the assembly.
        if (!params) {
            self->facingLeft = (PLAYER.facingLeft + 1) & 1;
        }
        self->facingLeft = (PLAYER.facingLeft + 1) & 1;

        SetSpeedX(FIX(-3.5));
        // Initial fireball size is 0x40 by 0x40
        self->posX.val += self->velocityX * 2;
        self->posY.i.hi -= 4;
        self->drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        self->scaleX = self->scaleY = 0x40;
        func_8011A328(self, 9);
        self->hitboxWidth = 4;
        self->hitboxHeight = 8;
        g_Player.timers[10] = 4;
        self->step++;
        break;
    case 1:
        // Once the fireball hits something, destroy it.
        if (self->hitFlags) {
            DestroyEntity(self);
            return;
        }
        self->posX.val += self->velocityX;
        // Much like the wing smash, these rot values are actually the size.
        // After shooting, the fireballs grow until they are 0x100 in size
        self->scaleX += 0x10;
        self->scaleY += 0x10;
        if (self->scaleY > 0x100) {
            self->scaleY = 0x100;
        }
        if (self->scaleX > 0x180) {
            self->scaleX = 0x180;
        }
    }
}

// Produced in Hellfire when you press UP during the casting
void EntityHellfireBigFireball(Entity* entity) {
    switch (entity->step) {
    case 0:
        if (entity->params) {
            PlaySfx(SFX_QUICK_STUTTER_EXPLODE_B);
        }

        entity->flags = FLAG_UNK_100000 | FLAG_POS_CAMERA_LOCKED;

        if (entity->params) {
            entity->posY.i.hi += 16;
        } else {
            entity->posY.i.hi -= 4;
        }
        entity->drawFlags |= FLAG_DRAW_ROTATE;
        entity->rotate = 0;
        entity->animSet = ANIMSET_DRA(9);
        entity->anim = D_800B07C8;
        entity->zPriority = PLAYER.zPriority + 2;
        entity->facingLeft = (PLAYER.facingLeft + 1) & 1;
        SetSpeedX(-0x10);
        func_8011A328(entity, 2);
        entity->hitboxWidth = 8;
        entity->hitboxHeight = 8;
        entity->step++;
        break;

    case 1:
        if (entity->pose >= 23) {
            if (!(g_GameTimer & 3)) {
                entity->rotate += 0x400;
            }
            if (entity->velocityX < 0) {
                entity->velocityX -= FIX(0.09375);
            } else {
                entity->velocityX += FIX(0.09375);
            }
            if (!(g_GameTimer & 1) && (rand() & 1)) {
                CreateEntFactoryFromEntity(entity, FACTORY(BP_36, 1), 0);
            }
            entity->posX.val += entity->velocityX;
            entity->posY.val += entity->velocityY;
        }
        break;
    }
}

// circle expands out of player
void EntityExpandingCircle(Entity* self) {
    Primitive* prim;

    if (PLAYER.facingLeft == 0) {
        self->posX.i.hi = PLAYER.posX.i.hi - 10;
    } else {
        self->posX.i.hi = PLAYER.posX.i.hi + 10;
    }
    self->posY.i.hi = PLAYER.posY.i.hi + 2;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.circleExpand.width = 22;
        self->ext.circleExpand.height = 26;
        prim = &g_PrimBuf[self->primIndex];
        prim->u0 = prim->u2 = 64;
        prim->u1 = prim->u3 = 127;
        prim->v0 = prim->v1 = 192;
        prim->v2 = prim->v3 = 255;
        PRED(prim) = 128;
        PGRN(prim) = 128;
        PBLU(prim) = 64;

        prim->tpage = 0x1A;
        prim->clut = PAL_FILL_WHITE;
        prim->priority = PLAYER.zPriority + 1;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        self->flags =
            FLAG_POS_PLAYER_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        self->step++;
        break;

    case 1:
        self->ext.circleExpand.width += 2;
        self->ext.circleExpand.height += 2;
        if (self->ext.circleExpand.width > 56) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y0 = self->posY.i.hi - self->ext.circleExpand.height;

    prim->x1 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y1 = self->posY.i.hi - self->ext.circleExpand.height;

    prim->x2 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y2 = self->posY.i.hi + self->ext.circleExpand.height;

    prim->x3 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y3 = self->posY.i.hi + self->ext.circleExpand.height;

    if (self->ext.circleExpand.width > 40) {
        prim->r3 -= 12;
        prim->g3 -= 12;
        prim->b3 -= 6;
        PRED(prim);
        PGRN(prim);
        PBLU(prim);
    }
}

void func_80127CC8(Entity* self) {
    Primitive* prim;

    if (PLAYER.step != Player_SpellHellfire) {
        // @bug Should be DestroyEntity(self)
        DestroyEntity();
        return;
    }

    self->posX.i.hi = PLAYER.posX.i.hi;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_G4, 1);

        if (self->primIndex == -1) {
            DestroyEntity(self);
            g_Player.unk5C = -1;
            return;
        }

        self->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
                      FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = 192;
        prim->g0 = prim->g1 = prim->g2 = prim->g3 = 64;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 = 64;
        prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE |
                         DRAW_COLORS | DRAW_TRANSP;
        prim->priority = self->zPriority = 0x1C0;
        self->step++;
        break;

    case 1:
        if (self->ext.timer.t++ >= 14) {
            DestroyEntity(self);
            return;
        }
    }
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = prim->x2 = self->posX.i.hi - 3;
    prim->y1 = prim->y0 = 0;
    prim->x1 = prim->x3 = self->posX.i.hi + 3;
    prim->y2 = prim->y3 = 240;

    if (g_GameTimer & 1) {
        prim->drawMode |= DRAW_HIDE;
    } else {
        prim->drawMode &= ~DRAW_HIDE;
    }
}

#include "../rebound_stone.h"

// Entity ID 20. Created by blueprint 24. This comes from BlueprintNum for
// the rebound stone SubweaponDef.
void EntitySubwpnReboundStone(Entity* self) {
    s16 playerX;       // sp5e
    s16 playerY;       // sp5c
    Collider collider; // sp38
    s32 speed;         // sp34
    s32 currX;         // s8
    s32 currY;         // s7
    s32 collX;
    s32 collY;
    s32 deltaX;        // s4
    s32 deltaY;        // s3
    s32 i;             // s2
    s32 colliderFlags; // s1
    PrimLineG2* prim;

    speed = 0x400;
    self->ext.reboundStone.unk82 = 0;
    playerX = self->posX.i.hi;
    playerY = self->posY.i.hi;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_LINE_G2, 16);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
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
        func_8011A290(self);
        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        g_Player.timers[10] = 4;
        CheckCollision(self->posX.i.hi, self->posY.i.hi, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->ext.reboundStone.unk84 = 4;
        }
        self->step++;
        PlaySfx(SFX_WEAPON_SWISH_C);
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
                CheckCollision(collX, collY, &collider, 0);
                colliderFlags =
                    collider.effects &
                    (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                     EFFECT_UNK_1000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                     EFFECT_SOLID);
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
                        if ((colliderFlags == EFFECT_NONE) ||
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
                CheckCollision(collX, collY, &collider, 0);
                colliderFlags =
                    collider.effects &
                    (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                     EFFECT_UNK_1000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                     EFFECT_SOLID);
                if (colliderFlags & EFFECT_SOLID) {
                    colliderFlags &=
                        EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                        EFFECT_UNK_1000 | EFFECT_UNK_0800 | EFFECT_UNK_0400 |
                        EFFECT_UNK_0200 | EFFECT_UNK_0100;
                    // Cases when traveling right
                    if (deltaX > 0) {
                        if (colliderFlags == EFFECT_NONE ||
                            TEST_BITS(colliderFlags,
                                      EFFECT_UNK_4000 | EFFECT_UNK_0800) ||
                            TEST_BITS(colliderFlags,
                                      EFFECT_UNK_8000 | EFFECT_UNK_4000)) {
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
                        if ((colliderFlags == EFFECT_NONE) ||
                            ((colliderFlags &
                              (EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                             EFFECT_UNK_0800) ||
                            ((colliderFlags &
                              (EFFECT_UNK_8000 | EFFECT_UNK_4000)) ==
                             EFFECT_UNK_8000)) {
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
            CreateEntFactoryFromEntity(self, 10, 0);
            PlaySfx(SFX_UI_SUBWEAPON_TINK);
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

// ash thrown when using vibhuti subweapon
void EntitySubwpnThrownVibhuti(Entity* self) {
    Collider col;
    FakePrim* prim;
    s16 randomAngle;
    s16 x;
    s16 y;
    s16 temp; // used for multiple unrelated things
    s32 i;

    switch (self->step) {
    case 0:
        self->primIndex = func_800EDB58(PRIM_TILE_ALT, 13);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        func_8011A290(self);
        self->hitboxWidth = self->hitboxHeight = 4;
        self->ext.subweapon.timer = 0x80;
        prim = (FakePrim*)&g_PrimBuf[self->primIndex];
        x = self->posX.i.hi;
        y = self->posY.i.hi - 8;
        i = 0;
        while (true) {
            prim->drawMode = DRAW_UNK02;
            prim->priority = PLAYER.zPriority + 2;
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
        PlaySfx(SFX_WEAPON_SWISH_C);
        g_Player.timers[10] = 4;
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
                    CheckCollision(
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
                    CheckCollision(prim->posX.i.hi, prim->posY.i.hi, &col, 0);
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

// ID #17. Created by factory blueprint #22. This is the blueprint for the
// Agunea (lightning) subweapon.
void EntitySubwpnAgunea(Entity* self) {
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
        self->primIndex = AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        self->facingLeft = PLAYER.facingLeft;
        func_8011A290(self);
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
        SetSpeedX(FIX(6));
        PlaySfx(SFX_WEAPON_SWISH_C);
        CreateEntFactoryFromEntity(self, FACTORY(BP_BLINK_WHITE, 0x52), 0);
        g_Player.timers[10] = 4;
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
             self->ext.agunea.parent->flags & FLAG_DEAD)) {
            self->step = 2;
            return;
        }

        tempX = self->posX.i.hi = self->ext.agunea.parent->posX.i.hi;
        tempY = self->posY.i.hi = self->ext.agunea.parent->posY.i.hi;
        if ((self->ext.agunea.unk7C % 12) == 0) {
            self->posX.i.hi += (rand() & 0xF) - 8;
            self->posY.i.hi += (rand() & 0xF) - 8;
            if (self->ext.agunea.unk84 == 0) {
                CreateEntFactoryFromEntity(self, 23, 0);
                PlaySfx(SFX_THUNDER_B);
                CreateEntFactoryFromEntity(self, FACTORY(BP_61, 2), 0);
                self->ext.agunea.unk84++;
            } else {
                heartCost = 5;
                // 0x4d is the item ID for the heart broach.
                heartBroachesWorn =
                    CheckEquipmentItemCount(ITEM_HEART_BROACH, EQUIP_ACCESSORY);
                if (heartBroachesWorn == 1) {
                    heartCost /= 2;
                }
                if (heartBroachesWorn == 2) {
                    heartCost /= 3;
                }
                if (heartCost <= 0) {
                    heartCost = 1;
                }
                if (g_Status.hearts >= heartCost) {
                    g_Status.hearts -= heartCost;
                    CreateEntFactoryFromEntity(self, 23, 0);
                    PlaySfx(SFX_THUNDER_B);
                    CreateEntFactoryFromEntity(self, FACTORY(BP_61, 2), 0);
                } else {
                    self->step = 4;
                }
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

void EntityAguneaHitEnemy(Entity* self) {
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

    if (self->ext.et_801291C4.parent->entityId != 0x11) {
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
        self->primIndex = AllocPrimitives(PRIM_GT4, 0x28);
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
            prim->clut = PAL_UNK_194;
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
            prim->clut = PAL_UNK_194;
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
                return;
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
                prim->clut = PAL_FILL_WHITE;
                prim = prim->next;
            }
            self->step_s++;
            return;
        }
        prim = self->ext.et_801291C4.prim1;
        while (prim != NULL) {
            prim->clut = PAL_UNK_194;
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

// tetra spirit out of bounds problem, add a value at beginning and end
#ifdef VERSION_PC
u8 D_800B0848[] = {0x00, 0x80, 0x80, 0x80, 0x90, 0x80, 0xA0, 0x80, 0xB0,
                   0xA0, 0x80, 0xA0, 0x90, 0xA0, 0xA0, 0xA0, 0xB0, 0xC0};
#else
u8 D_800B0848[] = {0x80, 0x80, 0x80, 0x90, 0x80, 0xA0, 0x80, 0xB0,
                   0xA0, 0x80, 0xA0, 0x90, 0xA0, 0xA0, 0xA0, 0xB0};
#endif

s16 D_800B0858[] = {0x03C0, 0x0440, 0x0340, 0x04C0};

void func_80129864(Entity* self) {
    Primitive* prim;
    s32 angle_diff;
    s32 angle_offset;
    s32 otherX, otherY;
    s32 action;
    s32 eleven;
    s32 twentyfive;

    s32 s1;
    s32 s3;
    s32 s2;
    s32 i;
    s32 xDist;
    s32 yDist;

    u8 temp_u;
    u8 temp_v;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, 0x10);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 8; i++) {
            prim->type = PRIM_TILE;
            prim->u0 = 1;
            prim->v0 = 1;
            prim->drawMode = DRAW_UNK02;
            prim->priority = 0;
            prim = prim->next;
            prim->priority = 0x1C2;
            prim->drawMode =
                DRAW_UNK_100 | DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                DRAW_HIDE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            prim->tpage = 0x1A;
            prim->clut = PAL_UNK_19F;
            prim = prim->next;
        }
        self->facingLeft = (PLAYER.facingLeft + 1) & 1; // !PLAYER.facingLeft
        self->ext.et_80129864.unk80 = D_800B0858[self->params & 0xFF];
        self->animSet = 9;
        self->anim = D_800B0798;
        self->palette = PAL_FLAG(PAL_UNK_19F);
        self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
        self->zPriority = 0x1C3;
        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
            FLAG_HAS_PRIMS | FLAG_UNK_100000 | FLAG_UNK_20000 | FLAG_UNK_10000;
        self->drawFlags = FLAG_DRAW_ROTATE;
        if (self->params & 0x7F00) {
            func_8011A328(self, 3);
        } else {
            func_8011A328(self, 1);
        }
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->step++;
        break;
    case 1:
        s1 = rcos(self->ext.et_80129864.unk82) >> 8;
        self->ext.et_80129864.unk82 += 0x80;
        self->ext.et_80129864.unk80 += s1;

        if (self->posY.i.hi < -0x20) {
            self->ext.et_80129864.ent = func_80118970();
            self->ext.et_80129864.unk84 = 0;
            self->ext.et_80129864.unk80 = 0xC00;
            if ((self->params & 0xFF) >= 2) {
                self->facingLeft = (self->facingLeft + 1) & 1;
            }
            self->step++;
        }
        break;
    case 2:
        if (self->ext.et_80129864.unk84 < 0x18) {
            angle_offset = 0x10;
        } else if (self->ext.et_80129864.unk84 < 0x28) {
            angle_offset = 0x20;
        } else if (self->ext.et_80129864.unk84 < 0x38) {
            angle_offset = 0x40;
        } else {
            angle_offset = 0x80;
        }

        if (self->ext.et_80129864.ent != NULL) {
            if (!self->ext.et_80129864.ent->entityId) {
                self->step++;
                break;
            } else {
                otherX = self->ext.et_80129864.ent->posX.i.hi;
                otherY = self->ext.et_80129864.ent->posY.i.hi;
            }
        } else {
            if (self->facingLeft) {
                otherX = 0x140;
                otherY = 0xA0;
            } else {
                otherX = -0x40;
                otherY = 0xA0;
            }
            if (self->params & 1) {
                otherY += 0x40;
            }
        }
        xDist = otherX - self->posX.i.hi;
        yDist = otherY - self->posY.i.hi;
        s1 = ratan2(-yDist, xDist) & 0xFFF;
        s3 = self->ext.et_80129864.unk80 & 0xFFF;
        angle_diff = abs(s3 - s1);
        if (angle_offset > angle_diff) {
            angle_offset = angle_diff;
        }
        if (s3 < s1) {
            if (angle_diff < 0x800) {
                s3 += angle_offset;
            } else {
                s3 -= angle_offset;
            }
        } else {
            if (angle_diff < 0x800) {
                s3 -= angle_offset;
            } else {
                s3 += angle_offset;
            }
        }
        self->ext.et_80129864.unk80 = s3 & 0xFFF;
        if (++self->ext.et_80129864.unk84 > 0x60) {
            self->step++;
        }
        break;
    case 3:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS |
                      FLAG_UNK_100000 | FLAG_UNK_10000;
        s1 = rcos(self->ext.et_80129864.unk82) >> 8;
        self->ext.et_80129864.unk82 += 0x80;
        self->ext.et_80129864.unk80 += s1;
        break;
    }

    self->velocityX = rcos(self->ext.et_80129864.unk80) << 6;
    self->velocityY = -(rsin(self->ext.et_80129864.unk80) << 6);
    self->posX.val += self->velocityX;
    self->posY.val += self->velocityY;

    if (self->facingLeft) {
        self->rotate = self->ext.et_80129864.unk80;
    } else {
        self->rotate = 0x800 - self->ext.et_80129864.unk80;
    }

    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 8; i++) {
        if (self->ext.et_80129864.unk86 == i) {
            prim->x1 = 1;
        }

        switch (prim->x1) {
        case 0:
            action = 0;
            break;
        case 1:
            action = 1;
            prim->x1 += 1;
            prim->y1 = 0x100;
            prim->x0 = self->posX.i.hi;
            prim->y0 = self->posY.i.hi;
            prim->x2 = self->ext.et_80129864.unk80;
            break;
        case 2:
            prim->y1 -= 16;
            action = 2;
            break;
        }

        xDist = prim->x0;
        yDist = prim->y0;
        s2 = prim->y1;
        eleven = 11;
        twentyfive = 25;
        s3 = prim->x2;
        prim = prim->next;

        switch (action) {
        case 0:
            prim->drawMode |= DRAW_HIDE;
            break;
        case 1:
#ifdef VERSION_PC
            // self->animCurFrame starts at 0. Seems like an out of bounds
            // bug in original?
            temp_u = D_800B0848[(self->animCurFrame) * 2];
            temp_v = D_800B0848[(self->animCurFrame) * 2 + 1];
#else
            temp_u = D_800B0848[(self->animCurFrame - 1) * 2];
            temp_v = D_800B0848[(self->animCurFrame - 1) * 2 + 1];
#endif
            prim->u0 = prim->u2 = temp_u;
            prim->u1 = prim->u3 = temp_u + 31;
            prim->v0 = prim->v1 = temp_v;
            prim->v2 = prim->v3 = temp_v + 15;
            prim->r0 = prim->b0 = prim->g0 = prim->r1 = prim->b1 = prim->g1 =
                prim->r2 = prim->b2 = prim->g2 = prim->r3 = prim->b3 =
                    prim->g3 = 0x80;
            prim->drawMode &= ~DRAW_HIDE;
            break;
        case 2:
            if (prim->g3 > 4) {
                prim->g3 -= 12;
            }
            prim->r0 = prim->b0 = prim->g0 = prim->r1 = prim->b1 = prim->g1 =
                prim->r2 = prim->b2 = prim->g2 = prim->r3 = prim->b3 = prim->g3;

            break;
        }

        if (action) {
            s1 = s3 - 0x200;
            prim->x0 = xDist + ((((rcos(s1) >> 4) * eleven >> 8) * s2) >> 8);
            prim->y0 = yDist - ((((rsin(s1) >> 4) * eleven >> 8) * s2) >> 8);
            s1 = s3 + 0x200;
            prim->x2 = xDist + ((((rcos(s1) >> 4) * eleven >> 8) * s2) >> 8);
            prim->y2 = yDist - ((((rsin(s1) >> 4) * eleven >> 8) * s2) >> 8);
            s1 = s3 - 0x734;
            prim->x1 =
                xDist + ((((rcos(s1) >> 4) * twentyfive >> 8) * s2) >> 8);
            prim->y1 =
                yDist - ((((rsin(s1) >> 4) * twentyfive >> 8) * s2) >> 8);
            s1 = s3 + 0x734;
            prim->x3 =
                xDist + ((((rcos(s1) >> 4) * twentyfive >> 8) * s2) >> 8);
            prim->y3 =
                yDist - ((((rsin(s1) >> 4) * twentyfive >> 8) * s2) >> 8);
        }
        prim = prim->next;
    }

    self->ext.et_80129864.unk86 += 1;
    self->ext.et_80129864.unk86 %= 8;
}

extern RECT D_80138424;

s16 D_800B0860[] = {31, 0,   31, -32, 0,  -32, -32, -32, -32,
                    0,  -32, 31, 0,   31, 31,  31,  31,  0};

// opens hole in backround and spirit comes out (ID 0x40)
void EntitySummonSpirit(Entity* self) {
    Primitive* prim;
    s32 timer;
    s32 selfX;
    s32 selfY;
    s32 i;

    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_20000 | FLAG_UNK_10000;
        g_unkGraphicsStruct.unk20 = 3;
        self->ext.summonspirit.spawnTimer = 10;
        func_80118C28(13);
        self->step++;
#ifdef VERSION_PSP
        func_psp_0891B0DC(0, 0);
#endif
        return;

    case 1:
        if (--self->ext.summonspirit.spawnTimer) {
            return;
        }
        self->primIndex = AllocPrimitives(PRIM_GT4, 9);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->posX.i.hi = 0x80;
        self->posY.i.hi = 0x60;
        if (PLAYER.posY.i.hi - 0x30 > 0x40) {
            self->posY.i.hi = PLAYER.posY.i.hi - 0x30;
        } else {
            self->posY.i.hi = PLAYER.posY.i.hi + 0x40;
        }
        selfX = self->posX.i.hi;
        selfY = self->posY.i.hi;
        prim = &g_PrimBuf[self->primIndex];

        prim->type = PRIM_G4;
        prim->drawMode = DRAW_UNK_100 | DRAW_UNK02;
        prim->x2 = prim->x0 = selfX - 0x20;
        prim->x3 = prim->x1 = selfX + 0x1F;
        prim->y1 = prim->y0 = selfY - 0x20;
        prim->y2 = prim->y3 = selfY + 0x1F;
        D_80138424.x = prim->x0;
#ifndef VERSION_PSP
        if (g_CurrentBuffer->disp.disp.x == 0) {
            D_80138424.x += 0x100;
        }
#endif
        D_80138424.y = prim->y0;
        D_80138424.w = 0x3F;
        D_80138424.h = 0x3F;
        MoveImage(&D_80138424, 0x200, 0x1C0);
        prim->priority = 0x1C0;
        prim = prim->next;
        for (i = 0; i < 8; i++) {
            // These should have been Point16 :(
            prim->x1 = selfX + D_800B0860[(i + 1) * 2];
            prim->y1 = selfY + D_800B0860[(i + 1) * 2 + 1];
            prim->x3 = selfX + D_800B0860[i * 2];
            prim->y3 = selfY + D_800B0860[i * 2 + 1];
            prim->u1 = D_800B0860[(i + 1) * 2] + 0x20;
            prim->v1 = D_800B0860[(i + 1) * 2 + 1] + 0xE0;
            prim->u3 = D_800B0860[i * 2] + 0x20;
            prim->v3 = D_800B0860[i * 2 + 1] + 0xE0;
            prim->u0 = prim->u2 = 0x20;
            prim->v0 = prim->v2 = 0xE0;
            prim->priority = 0x1C1;
            if (i >= 4) {
                prim->priority += 3;
            }
            prim->drawMode = DRAW_UNK_100 | DRAW_UNK02;
            prim->tpage = 0x118;
            prim = prim->next;
        }
        self->ext.summonspirit.timer = 0;
        // This just adds FLAG_HAS_PRIMS. Not sure why it wasn't an |=.
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_HAS_PRIMS | FLAG_UNK_20000 | FLAG_UNK_10000;
        self->step++;
        break;

    case 2:
        self->ext.summonspirit.timer++;
        if (self->ext.summonspirit.timer > 10) {
            // Both blueprints have child 61, but 118 has a couple 4s in the
            // other args. 61 is func_80129864. Not yet decompiled.
            if (self->params) {
                CreateEntFactoryFromEntity(self, 118, 0);
            } else {
                CreateEntFactoryFromEntity(self, 116, 0);
            }
            // Blueprint 44 is child 11. EntityPlayerBlinkWhite
            CreateEntFactoryFromEntity(self, FACTORY(BP_BLINK_WHITE, 0x67), 0);
            PlaySfx(SFX_UI_MP_FULL);
            self->step++;
        }
        break;
    case 3:
        self->ext.summonspirit.timer--;
        if (self->ext.summonspirit.timer < 0) {
            g_unkGraphicsStruct.unk20 = 0;
            DestroyEntity(self);
            return;
        }
        break;
    }
    timer = self->ext.summonspirit.timer;
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    prim = prim->next;
    for (i = 0; i < 8; i++) {
        prim->x2 = selfX + (((rcos(i << 9) >> 4) * timer) >> 8);
        prim->y2 = selfY - (((rsin(i << 9) >> 4) * timer) >> 8);
        prim->x0 = selfX + (((rcos((i + 1) << 9) >> 4) * timer) >> 8);
        prim->y0 = selfY - (((rsin((i + 1) << 9) >> 4) * timer) >> 8);
        prim = prim->next;
    }
}
