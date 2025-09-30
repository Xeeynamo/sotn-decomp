#include "bo6.h"

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", func_us_801BE79C);

INCLUDE_ASM(
    "boss/bo6/nonmatchings/us_3E79C", BO6_RicEntityShrinkingPowerUpRing);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntityHitByIce);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntityHitByLightning);

extern EInit D_us_801804B4;
extern AnimationFrame D_us_80181E78[];
extern s32 D_us_801D0850;
extern s32 D_us_801D0854[];
extern s32 D_us_801D169C;

// possibly ShaftOrb?
void func_us_801C03E8(Entity* self) {
    Primitive* prim; // s0
    s32 i;           // s1

    u16 palette;   // 0x6E(sp)
    s32 temp_s0_5; // 0x68(sp)
    s32 temp_v0_7; // 0x64(sp)
    s32 var_v1_2;  // 0x60(sp)
    s32 var_a0_2;  // 0x5C(sp)

    s32 distanceX; // 0x58(sp)
    s32 distanceY; // 0x54(sp)

    s32 scale;   // 0x50(sp)
    s32 posX;    // 0x4C(sp)
    s32 posY;    // 0x48(sp)
    s32 ricPosX; // 0x44(sp)
    s32 ricPosY; // s8

    s32 anotherX;
    s32 anotherY;

    s32 var_s4;    // 0x38(sp)
    s32 sp30;      // 0x34(sp)
    s32 j;         // 0x30(sp)
    s32 angle;     // s7
    s32 distance;  // s6
    s32 direction; // s5
    s32 primX;     // s4
    s32 primY;     // s3
    s32 temp_s0_2; // s2

    scale = 4;
    D_us_801D169C = 0;
    var_s4 = 0;
    sp30 = 0;

    if (self->flags & FLAG_DEAD) {
        if (self->step < 0x14) {
            D_us_801D169C = 1;
            self->step = 0x14;
        }
    } else {
#ifdef VERSION_PSP
        if ((self->hitFlags) && (self->step != 10)) {
#else
        if ((self->hitFlags) && (self->step == 2)) {
#endif
            self->ext.shaftOrb.unkTimer = 10;
            self->step = 0xA;
        }
        self->hitFlags = 0;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804B4);
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x20);

        if (self->primIndex == -1) {
            self->step = 0;
            return;
        }
        prim = &g_PrimBuf[self->primIndex];

        for (i = 0; i < 8; i++) {
            prim->clut = 0x252;
            prim->tpage = 0x12;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x1F;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 0x1F;
            prim->priority = RIC.zPriority + 4;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_HIDE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            D_us_801D0854[i] = 0;
            prim = prim->next;
        }

        for (i = 0; i < 24; i++) {
            prim->priority = RIC.zPriority - 2;
            prim->r0 = prim->g0 = prim->r1 = prim->g1 = 0x3F;
            prim->b0 = prim->b1 = 0x7F;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE | DRAW_UNK02 | DRAW_TRANSP;
            prim->type = PRIM_LINE_G2;
            prim = prim->next;
        }

        self->flags |= FLAG_UNK_20000000 | FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        self->posX.i.hi = 0x80;
        self->posY.i.hi = 0x30;
        self->ext.ILLEGAL.s16[4] = 0x400;
        self->ext.ILLEGAL.s16[5] = 0x10;
        self->ext.ILLEGAL.s16[6] = 0x30;
        self->ext.ILLEGAL.s16[7] = 0xC00;
        self->animSet = ANIMSET_OVL(5);
        self->animCurFrame = 0;
        self->unk5A = 0x48;
        self->palette = 0x8252;
        self->ext.ILLEGAL.s16[0] = self->hitboxState;
        self->anim = D_us_80181E78;
        self->zPriority = RIC.zPriority + 4;
        self->step = 1;
        self->opacity = 0;
        self->drawFlags = FLAG_DRAW_OPACITY;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        break;

    case 1:
        self->opacity++;
        if (self->opacity >= 0x80) {
            self->drawFlags = FLAG_DRAW_DEFAULT;
            self->drawMode = DRAW_DEFAULT;
            self->step++;
        }
        break;

    case 2:
        distanceX = RIC.posX.i.hi + RIC.hitboxOffX;
        distanceY = (RIC.posY.i.hi + RIC.hitboxOffY) - 0x40;

        angle = self->ext.ILLEGAL.s16[4];

        distanceX += (((rcos(angle) >> 4) * scale) >> 8);
        distanceY -= (((rsin(angle) >> 4) * scale) >> 8);
        self->ext.ILLEGAL.s16[4] += self->ext.ILLEGAL.s16[5];

        posX = distanceX - self->posX.i.hi;
        posY = distanceY - self->posY.i.hi;
        angle = ratan2(-posY, posX) & 0xFFF;

        temp_s0_2 = (self->ext.ILLEGAL.s16[7] & 0xFFF);
        var_v1_2 = abs(temp_s0_2 - angle);

        var_a0_2 = self->ext.ILLEGAL.s16[6];
        if (self->ext.ILLEGAL.s16[6] > var_v1_2) {
            var_a0_2 = var_v1_2;
        }

        if (temp_s0_2 < angle) {
            if (var_v1_2 < 0x800) {
                temp_s0_2 += var_a0_2;
            } else {
                temp_s0_2 -= var_a0_2;
            }
        } else {
            if (var_v1_2 < 0x800) {
                temp_s0_2 -= var_a0_2;
            } else {
                distance = var_a0_2;
                temp_s0_2 += distance;
            }
        }
        self->ext.ILLEGAL.s16[7] = temp_s0_2 & 0xFFF;
        temp_s0_5 = rcos(temp_s0_2) * 0x10;
        temp_v0_7 = rsin(temp_s0_2) * 0x10;
        self->posX.val = temp_s0_5 + self->posX.val;
        self->posY.val -= temp_v0_7;
        break;
    case 10:
        if (g_Timer & 1) {
            self->palette = 0x815F;
        } else {
            self->palette = 0x8168;
        }

        self->poseTimer++;
        if (--self->ext.shaftOrb.unkTimer == 0) {
            self->step = 2;
        }

        break;
    case 20:
        BO6_RicCreateEntFactoryFromEntity(self, 0x49, 0);
        BO6_RicCreateEntFactoryFromEntity(self, 0x4B, 0);
        self->step++;
        break;
    case 21:
        DestroyEntity(self);
        return;
    }

    if (g_api.CheckEquipmentItemCount(0x22U, 1U) != 0) {
        palette = 0x8252;
        self->hitboxState = self->ext.ILLEGAL.s16[0];
        self->ext.ILLEGAL.s16[1] = 1;
    } else {
        palette = 0x810D;
        self->hitboxState = 0;
        self->ext.ILLEGAL.s16[1] = 0;
    }
    if (RIC.step == PL_S_DEAD || RIC.step == PL_S_ENDING_1) {
        self->hitboxState = 0;
    }
    if (self->step != PL_S_9) {
        self->palette = palette;
    }
    if (!(g_Timer % 4) && (self->step == 2)) {
        D_us_801D0850++;
        D_us_801D0850 %= 8;
        var_s4 = 1;
    }

    if (g_Timer % 0x100 == 0) {
        if (self->step == 2) {
            if ((abs(self->posX.i.hi - RIC.posX.i.hi) < 0x20) &&
                (RIC.step != PL_S_DEAD)) {
                sp30 = 1;
                if (self->ext.ILLEGAL.s16[1]) {
                    BO6_RicCreateEntFactoryFromEntity(self, 0x590021, 0);
                }
            }
        }
    }

    posX = self->posX.i.hi;
    posY = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];

    for (i = 0; i < 8; i++) {
        if (D_us_801D0854[i] == 0) {
            if ((var_s4 != 0) && (D_us_801D0850 == i)) {
                prim->x0 = prim->x2 = posX - 0x10;
                prim->x1 = prim->x3 = posX + 0xF;
                prim->y0 = prim->y1 = posY - 0x10;
                prim->y2 = prim->y3 = posY + 0xF;
                prim->drawMode &= ~DRAW_HIDE;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 =
                    prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                        prim->b2 = prim->b3 = 0x80;
                D_us_801D0854[i] += 1;
            }
        } else {
            prim->b3 -= 4;
            if (prim->b3 < 0x10) {
                D_us_801D0854[i] = 0;
            }
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3;
        }
        if (!self->ext.ILLEGAL.s16[1]) {
            prim->drawMode |= DRAW_HIDE;
        }
        prim = prim->next;
    }

    ricPosX = RIC.posX.i.hi;
    ricPosY = RIC.posY.i.hi;

    if (g_Timer & 1) {
        direction = -1;
    } else {
        direction = 1;
    }
    posX -= 3;

    for (j = 0; j < 3; j++, posX += 3) {
        primX = posX;
        primY = posY;
        distance = 3;
        // > lw a1, 0x48(sp)
        anotherY = ricPosY - posY;
        anotherX = ricPosX - posX;
        angle = ratan2(-anotherY, anotherX);
        distance = (SquareRoot12(I_TO_FLT(
                        (anotherX * anotherX) + (anotherY * anotherY))) /
                    7);
        distance = FLT_TO_I(distance);

        for (i = 0; i < 8; i++) {
            direction = -direction;
            if (prim->r2 == 0) {
                if (sp30 != 0) {
                    prim->r2++;
                    prim->b2 = 0xC;
                    prim->drawMode &= ~DRAW_HIDE;
                }
            } else if (--prim->b2 == 0) {
                prim->drawMode |= DRAW_HIDE;
                prim->r2 = 0;
            }
            prim->x0 = primX;
            prim->y0 = primY;
            temp_s0_2 = angle + (rand() & 0x1FF) * direction;
            prim->x1 = (((rcos(temp_s0_2) >> 4) * distance) >> 8) + primX;
            prim->y1 = -(((rsin(temp_s0_2) >> 4) * distance) >> 8) + primY;
            primX = prim->x1;
            primY = prim->y1;

            if (i == 7) {
                prim->x1 = ricPosX;
                prim->y1 = ricPosY;
            }
            if (!self->ext.ILLEGAL.s16[1]) {
                prim->drawMode |= DRAW_HIDE;
            }
            prim = prim->next;
        }
    }
#ifndef VERSION_PSP
    FntPrint("tama_step:%02x\n", self->step);
#endif
}

#ifdef VERSION_PSP
extern s32 D_pspeu_0927BAF8;
#define E_ID_17 D_pspeu_0927BAF8
#else
#endif

extern s32 g_CutsceneFlags;

// TODO: I AM SHAFT!
void EntityShaft(Entity* self) {
    Entity* entity;
    FntPrint("I AM SHAFT\n");
    switch (self->step) {
    case 0:
#ifdef VERSION_PSP
        self->flags = FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
#else
        self->flags = FLAG_UNK_10000000;
#endif
        self->animSet = -0x7FFB;
        self->animCurFrame = 0x8B;
        self->unk5A = 0x48;
        self->palette = PAL_OVL(0x250);
        self->zPriority = RIC.zPriority + 2;
        self->opacity = 0;
        self->drawFlags = FLAG_DRAW_OPACITY;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->step++;
        break;

    case 1:
        self->opacity += 4;
        if (self->opacity > 48) {
            self->step++;
            entity = &g_Entities[0xC8];
            CreateEntityFromCurrentEntity(E_ID_17, entity);
            entity->params = 3;
            self->ext.ILLEGAL.s16[0] = 0x100;
        }
        self->posY.val += rsin(self->ext.ILLEGAL.s16[1]) * 4;
        self->ext.ILLEGAL.s16[1] += 0x20;
        break;

    case 2:
        if (!self->ext.ILLEGAL.s16[0]) {
            if ((g_CutsceneFlags & 0x40) || (g_DemoMode != Demo_None)) {
                self->drawFlags |= FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
                self->scaleX = self->scaleY = 0x100;
                self->step++;
            }
        } else {
            self->ext.ILLEGAL.s16[0]--;
        }
        self->posY.val += rsin(self->ext.ILLEGAL.s16[1]) * 4;
        self->ext.ILLEGAL.s16[1] += 0x20;
        break;

    case 3:
        self->scaleX -= 0x20;
        if (self->scaleX < 0x10) {
            self->scaleX = 0x10;
        }

        self->scaleY += 64;
        if (self->scaleY > 0x800) {
            self->scaleY = 0x800;
        }
        self->opacity += 6;
        if (self->opacity > 0xF0) {
            self->step++;
        }
        break;

    case 4:
        self->opacity -= 3;
        if (self->opacity < 4) {
            DestroyEntity(self);
        }
        break;
    }
}

// TODO: rename ShaftOrb
Entity* BO6_RicGetFreeEntity(s16, s16);
extern u8 D_us_80181E9C[];

void func_us_801C0FE8(Entity* self) {
    Entity* entity;
    Primitive* prim;
    s32 posX;
    s32 posY;
    s32 accelX;
    s32 accelY;
    s16 primIndex;
    s16 params;
    s32 velocity;

    params = self->params & 0xFF;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        prim->clut = 0x252;
        prim->tpage = 0x12;

        // temp_a1 = &D_us_80181E9C[temp_a0];
        prim->u0 = prim->u2 = D_us_80181E9C[params * 2] - 2;
        prim->u1 = prim->u3 = D_us_80181E9C[params * 2] + 2;

        prim->v0 = prim->v1 = D_us_80181E9C[params * 2 + 1] - 2;
        prim->v2 = prim->v3 = D_us_80181E9C[params * 2 + 1] + 2;

        prim->priority = RIC.zPriority + 4;
        prim->drawMode = DRAW_UNK02;

        accelX = D_us_80181E9C[params * 2] - 16;
        accelY = D_us_80181E9C[params * 2 + 1] - 16;
        self->posX.i.hi += accelX;
        self->posY.i.hi += accelY;

        velocity = ratan2(-accelY, accelX);
        velocity += ((rand() & 0x7F) - 0x40);
        self->ext.shaftOrb.velocityAngle = velocity;
        self->flags = FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        self->ext.shaftOrb.timer = 8;
        self->step++;
        break;

    case 1:
        if (--self->ext.shaftOrb.timer == 0) {
            self->ext.shaftOrb.timer = 16;
            velocity = self->ext.shaftOrb.velocityAngle;
            self->velocityX = (rcos(velocity) * 32) + (rand() & 0xF);
            self->velocityY = -((rsin(velocity) * 32) + (rand() & 0xF));
            self->step++;
        }
        break;

    case 2:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (--self->ext.shaftOrb.timer == 0) {
            BO6_RicCreateEntFactoryFromEntity(self, 0x4A, 0);
            self->velocityY = (rand() & 0x7FFF) + 0xFFFF0000;
            self->velocityX = self->velocityX >> 2;
            self->ext.shaftOrb.timer = 1;
            self->step++;
        }
        break;
    case 3:
        if ((self->ext.shaftOrb.timer % 4) == 0) {
            entity = BO6_RicGetFreeEntity(0x50, 0x8F);
            if (entity != NULL) {
                DestroyEntity(entity);
                entity->entityId = 0x43;
                entity->params = 0x100;
                // not shaft orb
                entity->ext.shaftOrb.parent = self->ext.shaftOrb.parent;
                entity->posX.val = self->posX.val;
                entity->posY.val = self->posY.val;
            }
        }
        self->ext.shaftOrb.timer += 1;
        self->velocityY += 0xC00;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        self->flags &= ~FLAG_UNK_10000000;
        break;
    }

    posX = self->posX.i.hi;
    posY = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = prim->x2 = posX - 2;
    prim->x1 = prim->x3 = posX + 2;
    prim->y0 = prim->y1 = posY - 2;
    prim->y2 = prim->y3 = posY + 2;
}

extern AnimationFrame D_us_80181EDC[];

void func_us_801C13A8(Entity* self) {
    s16 params = self->params & 0x7F00;
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_20000000 | FLAG_POS_CAMERA_LOCKED;
        self->unk5A = 0x79;
        self->animSet = 0xE;
        self->zPriority = RIC.zPriority + 6;
        self->palette = PAL_OVL(0x25E);
        self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        self->scaleX = self->scaleY = 0xC0;
        self->anim = D_us_80181EDC;
        if (params) {
            self->scaleX = self->scaleY = 0x80;
            self->anim = D_us_80181EDC;
        }
        self->velocityY = -FIX(0.25);
        self->step++;
        break;

    case 1:
        self->posY.val += self->velocityY;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntityWhip);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntityArmBrandishWhip);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", func_us_801C2688);

void func_us_801C277C(void) {}

void func_us_801C2784(void) {}

INCLUDE_ASM(
    "boss/bo6/nonmatchings/us_3E79C", BO6_RicEntitySubwpnHolyWaterBreakGlass);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntityCrashHydroStorm);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_DebugShowWaitInfo);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_DebugInputWait);

s32 func_us_801C310C(s16 height, s16 width) {
    Collider collider;
    Collider collider2;
    s16 maskedEffects;
    s16 maskedEffects2;
    s16 posX;
    s16 posY;
    s16 newPosY;

    if (((g_CurrentEntity->posX.val + width) < 0) ||
        (((s16) g_CurrentEntity->posX.i.hi + width) > 0x100)) {
        if ((g_CurrentEntity->posY.i.hi + height) >= 0xD4) {
            g_CurrentEntity->posY.i.hi = 0xD4 - height;
            return 1;
        }
        return 0;
    }
    posX = g_CurrentEntity->posX.i.hi + width;
    posY = g_CurrentEntity->posY.i.hi + height;

    g_api.CheckCollision(posX, posY, &collider, 0);
    maskedEffects =  collider.effects & 0xF801;
    posY = posY - 1 + collider.unk18;
    g_api.CheckCollision(posX, posY, &collider2, 0);

    newPosY = height + ((s16) g_CurrentEntity->posY.i.hi + collider.unk18);
    if ((maskedEffects & 0x8801) == 1 ||
        (maskedEffects & 0x8801) == 0x801) {
        maskedEffects = collider2.effects & 0xF001;
        if (!(maskedEffects & 1)) {
            g_CurrentEntity->posY.i.hi = newPosY;
            return 1;
        }
        if (((s32) collider2.effects & 0x8001) == 0x8001) {
            g_CurrentEntity->posY.i.hi = newPosY - 1 + collider2.unk18;
            return maskedEffects;
        }
        return 0;
    }
    if ((maskedEffects & 0x8001) == 0x8001) {
        g_CurrentEntity->posY.i.hi = newPosY;
        return maskedEffects & 0xF001;
    }
    return 0;
}


int WarpBackgroundBrightness() { return 0; }

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", func_us_801C32C4);

INCLUDE_ASM(
    "boss/bo6/nonmatchings/us_3E79C", BO6_RicEntitySubwpnHolyWaterFlame);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntitySubwpnCrashCross);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", func_us_801C4200);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", func_us_801C488C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntitySubwpnCrossTrail);

INCLUDE_ASM(
    "boss/bo6/nonmatchings/us_3E79C", BO6_RicEntitySubwpnCrashCrossParticles);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntitySubwpnThrownAxe);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", func_us_801C560C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntitySubwpnKnife);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_ReboundStoneBounce1);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_ReboundStoneBounce2);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntitySubwpnReboundStone);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntitySubwpnThrownVibhuti);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_PrimDecreaseBrightness);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntitySubwpnAgunea);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntityAguneaHitEnemy);

extern AnimationFrame D_us_801829D4[];

void BO6_RicEntityVibhutiCrashCloud(Entity* self) {
    s32 angle;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->posX.val = self->ext.vibCrashCloud.parent->ext.vibhutiCrash.x;
        self->posY.val = self->ext.vibCrashCloud.parent->ext.vibhutiCrash.y;
        self->facingLeft =
            self->ext.vibCrashCloud.parent->ext.vibhutiCrash.facing;
        self->flags |= FLAG_UNK_20000000;
        self->unk5A = 0x64;
        self->animSet = 0xE;
        self->palette = PAL_OVL(0x19E);
        self->anim = D_us_801829D4;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_OPACITY;
        self->opacity = 0x60;
        self->hitboxWidth = 8;
        self->hitboxHeight = 8;

        angle = (rand() % 512) + 0x300;
        self->velocityX = rcos(angle) << 5;
        self->velocityY = -(rsin(angle) << 5);
        self->step++;
        break;

    case 1:
        self->ext.vibCrashCloud.unk7C++;
        if (self->ext.vibCrashCloud.unk7C > 38) {
            DestroyEntity(self);
        } else {
            self->posX.val += self->velocityX;
            self->posY.val += self->velocityY;
        }
        break;
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntityCrashVibhuti);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", func_us_801C8590);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", func_us_801C8618);

INCLUDE_ASM(
    "boss/bo6/nonmatchings/us_3E79C", BO6_RicEntityCrashReboundStoneExplosion);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntityCrashReboundStone);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntityCrashBibleBeam);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntityCrashBible);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", func_us_801C9DE8);

void func_us_801CA340(Entity* self) {
    OVL_EXPORT(RicCreateEntFactoryFromEntity)(self, FACTORY(0x3F, 1), 0);
    DestroyEntity(self);
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_GetAguneaLightningAngle);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_AguneaShuffleParams);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntityAguneaLightning);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntityAguneaCircle);

INCLUDE_ASM(
    "boss/bo6/nonmatchings/us_3E79C", BO6_RicEntitySubwpnStopwatchCircle);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_EntityStopWatch);

void OVL_EXPORT(RicEntitySubwpnBibleTrail)(Entity* entity) {
    Primitive* prim;

    switch (entity->step) {
    case 0:
        entity->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (entity->primIndex == -1) {
            DestroyEntity(entity);
            return;
        }
        entity->flags = FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[entity->primIndex];
        prim->tpage = 0x1C;
        prim->clut = 0x19D;
        prim->u0 = prim->u2 = 0x20;
        prim->v0 = prim->v1 = 0;
        prim->u1 = prim->u3 = 0x30;
        prim->v2 = prim->v3 = 0x10;
        prim->x0 = prim->x2 = entity->posX.i.hi - 8;
        prim->x1 = prim->x3 = entity->posX.i.hi + 8;
        prim->y0 = prim->y1 = entity->posY.i.hi - 8;
        prim->y2 = prim->y3 = entity->posY.i.hi + 8;
        prim->priority = entity->zPriority;
        prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        entity->ext.et_BibleSubwpn.unk7E = 0x60;
        entity->step++;
        break;
    case 1:
        entity->ext.et_BibleSubwpn.unk7C++;
        if (entity->ext.et_BibleSubwpn.unk7C > 5) {
            entity->step++;
        }
        entity->ext.et_BibleSubwpn.unk7E -= 8;
        break;
    case 2:
        DestroyEntity(entity);
        return;
    }
    prim = &g_PrimBuf[entity->primIndex];
    PCOL(prim) = entity->ext.et_BibleSubwpn.unk7E;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntitySubwpnBible);

INCLUDE_RODATA("boss/bo6/nonmatchings/us_3E79C", D_us_801A7028);

INCLUDE_RODATA("boss/bo6/nonmatchings/us_3E79C", D_us_801A7030);

INCLUDE_ASM("boss/bo6/nonmatchings/us_3E79C", BO6_RicEntityCrashCrossBeam);
