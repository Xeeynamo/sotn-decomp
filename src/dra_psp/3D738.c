// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

typedef enum{
    DAGGER_INIT,
    DAGGER_FLYING,
    DAGGER_BOUNCE,
    DAGGER_HIT_ENEMY
} DaggerSteps;

// dagger thrown when using subweapon
void EntitySubwpnThrownDagger(Entity* self) {
    Collider collider;
    Primitive* prim;
    s16 offsetX;
    s16 offsetY;
    s16 angle_a;
    s16 angle_b;
    s16 angle_c;
    s16 angle_d;
    s16 selfX;
    s16 selfY;
    s16 var_s5;
    s32 cosine;
    s32 sine;
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
        prim->clut = 0x1AB;
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
        return;
    case DAGGER_FLYING:
        self->ext.timer.t++;
        if (self->velocityX > 0) {
            var_s5 = 8;
        }
        if (self->velocityX < 0) {
            var_s5 = -8;
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
                self->posX.i.hi + var_s5, self->posY.i.hi, &collider, 0);
            if (self->hitFlags == 2 ||
                collider.effects & (EFFECT_SOLID | EFFECT_UNK_0002)) {
                self->ext.timer.t = 64;
                self->velocityX = -(self->velocityX >> 3);
                self->velocityY = FIX(-2.5);
                self->hitboxState = 0;
                self->posX.i.hi += var_s5;
                CreateEntFactoryFromEntity(self, FACTORY(10, 0), 0);
                self->posX.i.hi -= var_s5;
                PlaySfx(SFX_UI_TINK);
                self->step++;
                return;
            }
        }
        selfX = self->posX.i.hi;
        selfY = self->posY.i.hi;
        offsetX = 12;
        offsetY = 8;
        if (self->facingLeft) {
            offsetX = -offsetX;
            offsetY = -offsetY;
        }
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = selfX - offsetX;
        prim->y0 = selfY - 4;
        prim->x1 = selfX + offsetX;
        prim->y1 = selfY - 4;
        prim->x2 = selfX - offsetX;
        prim->y2 = selfY + 4;
        prim->x3 = selfX + offsetX;
        prim->y3 = selfY + 4;
        prim->clut = 0x1AB;
        (g_GameTimer >> 1) & 1; // no-op
        prim->drawMode &= ~DRAW_HIDE;
        prim = prim->next;
        prim->x0 = selfX - offsetY;
        prim->y0 = selfY - 1;
        prim->x1 = selfX - (offsetX * (self->ext.timer.t / 2));
        prim->y1 = selfY - 1;
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
            PGREY(prim,0) = PGREY(prim,1) = PGREY(prim,2) = PGREY(prim,3) = 0x60;
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY += FIX(0.125);
        selfX = self->posX.i.hi;
        selfY = self->posY.i.hi;
        offsetX = 12;
        if (self->facingLeft == 0) {
            angle_a = 0x72E;
            angle_b = 0xD2;
            angle_c = 0x8D2;
            angle_d = -0xD2;

            self->rotZ -= 0x80;
        } else {
            angle_b = 0x72E;
            angle_a = 0xD2;
            // nb: order swapped
            angle_d = 0x8D2;
            angle_c = -0xD2;
            self->rotZ += 0x80;
        }
        angle_a += self->rotZ;
        angle_b += self->rotZ;
        angle_c += self->rotZ;
        angle_d += self->rotZ;
        if (self->facingLeft) {
            offsetX = -offsetX;
        }
        prim = &g_PrimBuf[self->primIndex];
        cosine = (rcos(angle_a) * 0xCA0) >> 0x14;
        sine = -(rsin(angle_a) * 0xCA0) >> 0x14;
        prim->x0 = selfX + (s16)cosine;
        prim->y0 = selfY - (s16)sine;
        cosine = (rcos(angle_b) * 0xCA0) >> 0x14;
        sine = -(rsin(angle_b) * 0xCA0) >> 0x14;
        prim->x1 = selfX + (s16)cosine;
        prim->y1 = selfY - (s16)sine;
        cosine = (rcos(angle_c) * 0xCA0) >> 0x14;
        sine = -(rsin(angle_c) * 0xCA0) >> 0x14;
        prim->x2 = selfX + (s16)cosine;
        prim->y2 = selfY - (s16)sine;
        cosine = (rcos(angle_d) * 0xCA0) >> 0x14;
        sine = -(rsin(angle_d) * 0xCA0) >> 0x14;
        prim->x3 = selfX + (s16)cosine;
        prim->y3 = selfY - (s16)sine;
        prim->clut = 0x1AB;

        (g_GameTimer >> 1) & 1; // no-op
        if (self->ext.timer.t < 0x21) {
            prim->r0 -= 2;
            prim->g0 = prim->b0 = PGREY(prim,1) = PGREY(prim,2) = PGREY(prim,3) = prim->r0;
        }
        prim->drawMode &= ~DRAW_HIDE;
        prim = prim->next;
        prim->drawMode |= DRAW_HIDE;
        return;
    case DAGGER_HIT_ENEMY:
        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntitySubwpnThrownAxe(Entity* self) {
    u8 rVal;
    u8 gVal;
    u8 bVal;
    s16 xVar;
    s16 yVar;
    s32 rgbIdx;
    s32 graphicsTemp;
    s16 angle0;
    s16 angle1;
    s16 angle2;
    s16 angle3;
    s16 angleOffset;
    s32 twentyone;
    Primitive* prevPrim;
    s32 i;
    Primitive* prim;
    
    twentyone = 21;

    switch (self->step) {
    case 0:
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
        if (self->facingLeft){
            self->ext.subwpnAxe.unk7C = 0x400;
        }else{
            self->ext.subwpnAxe.unk7C = 0xC00;
        }
        
        if (!(g_Player.status & PLAYER_STATUS_CROUCH)) {
            self->posY.i.hi -= 12;
        }
        for(prim = &g_PrimBuf[self->primIndex], i = 0; prim != NULL; i++, prim = prim->next) {
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
    case 1:
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
            self->step = 2;
        }
        break;
    case 2:
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

    if (self->animFrameDuration == 0) {
        graphicsTemp = self->animFrameIdx;
        self->ext.subwpnAxe.unk8C[graphicsTemp] = 0;
        self->ext.subwpnAxe.unk90[graphicsTemp] = 1;
        self->ext.subwpnAxe.unk94[graphicsTemp] = 1;
        graphicsTemp++;
        graphicsTemp &= 3;
        self->animFrameIdx = graphicsTemp;
        self->animFrameDuration = 2;
    } else {
        self->animFrameDuration--;
    }
    for(prim = &g_PrimBuf[self->primIndex], 
        prevPrim = prim, 
        graphicsTemp = ((g_GameTimer >> 1) & 1) + 0x1AB, 
        i = 0; prim != NULL; i++, prim = prim->next) {
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
            rgbIdx = self->ext.subwpnAxe.unk8C[i-1]++;
            if (rgbIdx < 10) {
                rVal = D_800B0628[rgbIdx*4 + 0];
                gVal = D_800B0628[rgbIdx*4 + 1];
                bVal = D_800B0628[rgbIdx*4 + 2];
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
                self->ext.subwpnAxe.unk90[i -1] = 0;
                prim->drawMode |= DRAW_HIDE;
            }
        }
    }
}

// Same RIC function is func_801682B4
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

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", func_psp_0911B820);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", EntityHolyWater);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", EntityHolyWaterBreakGlass);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", EntityHolyWaterFlame);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", EntitySubwpnCrashCross);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", EntitySubwpnCrashCrossParticles);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", EntityHellfireHandler);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", EntityHellfireNormalFireball);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", EntityBatFireball);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", EntityHellfireBigFireball);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", EntityExpandingCircle);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", func_80127CC8);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", func_psp_0911EA78);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", func_psp_0911EB00);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", EntitySubwpnReboundStone);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", EntitySubwpnThrownVibhuti);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", func_psp_0911FBD0);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", EntitySubwpnAgunea);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", EntityAguneaHitEnemy);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", func_80129864);

INCLUDE_ASM("dra_psp/psp/dra_psp/3D738", EntitySummonSpirit);
