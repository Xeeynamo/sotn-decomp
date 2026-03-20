// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rnz0.h"

static s16 D_pspeu_09259590[] = {0, 32, 0, 4, 8, -4, -16};
static s16 unused1[] = {0, 32, 8, 0};
static s16 D_pspeu_092595A0[] = {0, 10, 255, 0};
static s16 D_pspeu_092595A8[] = {0, 8, 10, 8, 8, 10, 8, 0};

// Walk cycle
static u8 D_pspeu_092595B8[] = {8, 1, 11, 2, 11, 3, 16, 4, 11, 5, 11, 6, 8, 1, 0};
// Punch attack
static u8 D_pspeu_092595C8[] = {16, 7, 32, 8, 1, 1, 1, 9, 1, 45, 2, 46, 2, 47, 1, 45, 1, 9, 12, 11, 10, 1, 255, 0};
// Jump windup
static u8 D_pspeu_092595E0[] = {20, 12, 10, 13, 255, 0};
// Flying through the air
static u8 D_pspeu_092595E8[] = {10, 14, 10, 15, 10, 16, 10, 17, 1, 18, 10, 15, 0};
// Jump landing (note it's the windup backward)
static u8 D_pspeu_092595F8[] = {10, 13, 20, 12, 255, 0};
// Flying (slow wing flaps)
static u8 D_pspeu_09259600[] = {5, 39, 4, 41, 4, 15, 5, 42, 3, 16, 3, 43, 2, 44, 10, 40, 1, 44, 1, 16, 1, 15, 2, 41, 0};
// Flying (faster wing flaps - note same frames for less time)
static u8 D_pspeu_09259620[] = {3, 39, 2, 41, 2, 15, 3, 42, 2, 16, 2, 43, 1, 44, 6, 40, 1, 44, 1, 16, 1, 15, 2, 41, 0};
// Windup for minion spawning
static u8 D_pspeu_09259640[] = {4, 19, 2, 20, 2, 21, 2, 22, 10, 17, 255, 0};
// Windup and shoot fireball
static u8 D_pspeu_09259650[] = {40, 7, 64, 8, 1, 1, 42, 9, 10, 1, 255, 0};
// Minion spawning animation
static u8 D_pspeu_09259660[] = {10, 18, 16, 19, 48, 24, 10, 19, 10, 16, 10, 17, 255, 0};
// Some kind of death animation
static u8 D_pspeu_09259670[] = {24, 1, 12, 2, 12, 3, 48, 4, 12, 5, 12, 6, 24, 1, 0};
// Final fade-away death animation
static u8 D_pspeu_09259680[] = {6, 39, 6, 41, 6, 12, 6, 13, 6, 14, 6, 20, 6, 24, 255, 0};

extern EInit D_us_80180A38;

typedef enum{
    LD_STEP_MINION_INIT = 32,
} LesserDemonSteps;


// Seems to be related to the iframes of the minion spawn
void func_pspeu_0924DBD0(s16* unkArg) {
    switch (g_CurrentEntity->step_s) {
    case 0:
        g_CurrentEntity->animCurFrame = 0;
        g_CurrentEntity->hitboxState = 0;
        g_CurrentEntity->drawFlags |= ENTITY_OPACITY;
        g_CurrentEntity->opacity = 0;
        g_CurrentEntity->step_s++;
        if (!unkArg) {
            g_CurrentEntity->step_s = 2;
        }
        break;

    case 1:
        if (UnkCollisionFunc3(unkArg) & 1) {
            g_CurrentEntity->animCurFrame = 1;
            g_CurrentEntity->step_s++;
        }
        break;

    case 2:
        g_CurrentEntity->opacity += 2;
        if (g_CurrentEntity->opacity == 0xC0) {
            g_CurrentEntity->drawFlags = ENTITY_DEFAULT;
            g_CurrentEntity->blendMode = BLEND_NO;
            g_CurrentEntity->ext.lesserDemon.unkAC = 0x40;
            g_CurrentEntity->step_s++;
        }
        break;

    case 3:
        if (g_CurrentEntity->ext.lesserDemon.unkAC & 1) {
            g_CurrentEntity->palette = D_us_80180A38[3];
        } else {
            g_CurrentEntity->palette = PAL_FLAG(PAL_UNK_19F);
        }
        if (!(--g_CurrentEntity->ext.lesserDemon.unkAC)) {
            g_CurrentEntity->palette = D_us_80180A38[3];
            g_CurrentEntity->hitboxState = 3;
            SetStep(1);
        }
        break;
    }
}

// Seems to be the windup just before the spit attack
u8 func_pspeu_0924DDF0(void) {
    Primitive* prim;
    Pos tempPos;
    s32 primIndex;
    s32 unkVar;
    u8 randomVal;
    u8 ret;
    s32 pad[2];

    ret = false;
    switch (g_CurrentEntity->ext.lesserDemon.unk84) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 0x18);
        if (primIndex != -1) {
            g_CurrentEntity->primIndex = primIndex;
            g_CurrentEntity->flags |= FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.lesserDemon.unk7C = prim;
            while (prim != NULL) {
                PGREY_ALT(prim, 0, 0)
                prim->u0 = 2;
                prim->v0 = 2;
                prim->priority = g_CurrentEntity->zPriority + 2;
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                randomVal = Random() & 0x7F;
                if (g_CurrentEntity->facingLeft) {
                    // These look like they could be -= and += respectively,
                    // but that oddly does not match
                    randomVal = randomVal - 0x40;
                } else {
                    randomVal = randomVal + 0x40;
                }
                prim->x0 = (g_CurrentEntity->posX.i.hi +
                            ((rcos(randomVal * 0x10) * 0x60) >> 0xC) +
                            (Random() & 0x3F)) -
                           0x1F;
                prim->y0 = (g_CurrentEntity->posY.i.hi +
                            ((rsin(randomVal * 0x10) * 0x60) >> 0xC) +
                            (Random() & 0x3F)) -
                           0x1F;
                prim->x1 = 0;
                prim->y1 = 0;
                if (g_CurrentEntity->facingLeft) {
                    unkVar =
                        prim->x0 - (g_CurrentEntity->posX.i.hi + 10) << 0x10;
                } else {
                    unkVar =
                        prim->x0 - (g_CurrentEntity->posX.i.hi - 10) << 0x10;
                }
                LOW(prim->x2) = -unkVar / 64;
                unkVar = prim->y0 - (g_CurrentEntity->posY.i.hi - 11) << 0x10;
                LOW(prim->x3) = -unkVar / 64;
                prim = prim->next;
            }
        } else {
            ret = true;
            g_CurrentEntity->ext.lesserDemon.unk84 = 2;
        }
        g_CurrentEntity->ext.lesserDemon.unk80 = 0;
        g_CurrentEntity->ext.lesserDemon.unk84++;
        break;

    case 1:
        prim = g_CurrentEntity->ext.lesserDemon.unk7C;
        while (prim != NULL) {
            tempPos.x.i.hi = prim->x0;
            tempPos.x.i.lo = prim->x1;
            tempPos.y.i.hi = prim->y0;
            tempPos.y.i.lo = prim->y1;
            tempPos.x.val += LOWU(prim->x2);
            tempPos.y.val += LOWU(prim->x3);
            LOH(prim->x0) = tempPos.x.i.hi;
            LOH(prim->x1) = tempPos.x.i.lo;
            LOH(prim->y0) = tempPos.y.i.hi;
            LOH(prim->y1) = tempPos.y.i.lo;
            prim->r0 += 3;
            prim = prim->next;
        }
        prim = g_CurrentEntity->ext.lesserDemon.unk7C;
        PrimToggleVisibility(prim, 0x18);
        if (g_CurrentEntity->ext.lesserDemon.unk80++ > 0x40) {
            primIndex = g_CurrentEntity->primIndex;
            g_api.FreePrimitives(primIndex);
            g_CurrentEntity->flags &= ~FLAG_HAS_PRIMS;
            g_CurrentEntity->ext.lesserDemon.unk84++;
            g_CurrentEntity->ext.lesserDemon.unk80 = 0;
        }
        break;

    case 2:
        ret = true;
    }
    return ret;
}


extern EInit g_EInitLesserDemonSpit;


// Traveling diagonally downward
static u8 D_pspeu_09259690[] = {1, 25, 1, 26, 1, 27, 1, 28, 0};
// Splash when hitting the ground
static u8 D_pspeu_092596A0[] = {
    4, 29, 4, 30, 4, 31, 4, 32, 4, 33, 2, 34, 2, 36, 255, 0};
// Fizzling out on ground
static u8 D_pspeu_092596B0[] = {4, 37, 4, 38, 255, 0};

// EntityLesserDemonSpit

void func_us_801BCAB0(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    u16 posX, posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitLesserDemonSpit);
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = 0x180;
        self->scaleY = 0x180;
        break;

    case 1:
        if (self->facingLeft) {
            self->velocityX = FIX(4.0);
        } else {
            self->velocityX = FIX(-4.0);
        }
        self->velocityY = FIX(4.0);
        self->step++;
        break;

    case 2:
        MoveEntity();
        AnimateEntity(D_pspeu_09259690, self);
        if (CheckColliderOffsets(D_pspeu_092595A0, 0)) {
            self->pose = 0;
            self->poseTimer = 0;
            self->scaleX = 0x140;
            self->scaleY = 0x200;
            self->hitboxWidth = 8;
            self->hitboxHeight = 8;
            self->step++;
        }
        break;

    case 3:
        if (!AnimateEntity(D_pspeu_092596A0, self)) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                self->ext.lesserDemon.unk7C = prim;
                prim->tpage = 0x13;
                prim->clut = 0x231;
                prim->u0 = 0x68;
                prim->v0 = 0xC8;
                prim->u1 = 0x7F;
                prim->v1 = 0xC8;
                prim->u2 = 0x68;
                prim->v2 = 0xFF;
                prim->u3 = 0x7F;
                prim->v3 = 0xFF;
                prim->x0 = self->posX.i.hi - 0x10;
                prim->x1 = prim->x0 + 0x2C;
                prim->x2 = prim->x0;
                prim->x3 = prim->x1;
                prim->y0 = self->posY.i.hi - 0x30;
                prim->y1 = prim->y0;
                prim->y2 = self->posY.i.hi + 0xC;
                prim->y3 = prim->y2;
                prim->priority = self->zPriority + 2;
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            } else {
                DestroyEntity(self);
                return;
            }
            self->animCurFrame = 0x25;
            self->poseTimer = 0;
            self->pose = 0;
            self->ext.lesserDemon.unk80 = 0;
            PlaySfxPositional(SFX_FM_EXPLODE_B);
            self->step++;
        }
        break;

    case 4:
        prim = self->ext.lesserDemon.unk7C;
        if (self->ext.lesserDemon.unk80++ > 0x10) {
            self->step++;
            self->ext.lesserDemon.unk80 = 0x1D;
            self->hitboxHeight = 0x40;
            self->hitboxOffY -= 0x20;
        } else {
            prim->y0 -= 0x10 - self->ext.lesserDemon.unk80;
            prim->y1 = prim->y0;
        }
        break;

    case 5:
        prim = self->ext.lesserDemon.unk7C;
        if (!--self->ext.lesserDemon.unk80) {
            self->pose = 0;
            self->poseTimer = 0;
            self->hitboxState = 0;
            self->step++;
            prim->drawMode = DRAW_HIDE;
        } else {
            prim->y0 += 4;
            prim->y1 = prim->y0;
            prim->v2 -= 2;
            prim->v3 = prim->v2;
            self->hitboxHeight = 8;
            self->hitboxOffY = -4;
        }
        break;

    case 6:
        self->scaleY -= 0x20;
        if (!AnimateEntity(D_pspeu_092596B0, self)) {
            self->drawFlags |= ENTITY_OPACITY;
            self->opacity = 0x80;
            self->step++;
        }
        break;

    case 7:
        self->scaleY -= 0x10;
        self->opacity -= 0x10;
        if (!self->opacity) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

// Lesser Demon punch attack
void func_pspeu_0924E7D0(void) {
    Primitive* prim;
    s32 primIndex;

    switch (g_CurrentEntity->ext.lesserDemon.unk84) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex != -1) {
            g_CurrentEntity->flags |= FLAG_HAS_PRIMS;
            g_CurrentEntity->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.lesserDemon.unk7C = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 0x13;
            prim->clut = 0x22E;
            prim->v0 = 0x70;
            prim->v1 = prim->v0;
            prim->v2 = 0x7F;
            prim->v3 = prim->v2;
            if (g_CurrentEntity->facingLeft) {
                prim->next->x1 = g_CurrentEntity->posX.i.hi + 4;
                prim->next->clut = 2;
                prim->u0 = 0x2F;
                prim->u1 = 0;
            } else {
                prim->u0 = 0;
                prim->u1 = 0x2F;
                prim->next->x1 = g_CurrentEntity->posX.i.hi - 4;
                LOH(prim->next->clut) = -2;
            }
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->next->y0 = g_CurrentEntity->posY.i.hi + 1;
            prim->priority = g_CurrentEntity->zPriority + 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim->next->b3 = 0x80;
            LOH(prim->next->r2) = 0x28;
            LOH(prim->next->b2) = 0x10;
        } else {
            g_CurrentEntity->ext.lesserDemon.unk84 = 3;
        }
        g_CurrentEntity->ext.lesserDemon.unk84++;
        break;

    case 1:
        prim = g_CurrentEntity->ext.lesserDemon.unk7C;
        if (prim->next->r3) {
            prim->clut = 0x236;
        } else {
            prim->clut = 0x22E;
        }
        prim->next->r3 ^= 1;
        UnkPrimHelper(prim);
        LOH(prim->next->r2) += 2;
        LOH(prim->next->b2) -= 1;
        prim->next->b3 -= 4;
        if (LOH(prim->next->r2) > 0x38) {
            g_CurrentEntity->ext.lesserDemon.unk84++;
        }
        break;

    case 2:
        primIndex = g_CurrentEntity->primIndex;
        g_api.FreePrimitives(primIndex);
        g_CurrentEntity->flags &= ~FLAG_HAS_PRIMS;
        g_CurrentEntity->ext.lesserDemon.unk84++;
        break;
    }
}

void func_pspeu_0924EB18(void) {
    Primitive* prim;
    s32 primIndex;

    switch (g_CurrentEntity->ext.lesserDemon.unk84) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex != -1) {
            g_CurrentEntity->flags |= FLAG_HAS_PRIMS;
            g_CurrentEntity->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.lesserDemon.unk7C = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 0x1A;
            prim->clut = PAL_CC_BLUE_EFFECT_A;
            prim->u0 = prim->u2 = 0xE0;
            prim->u1 = prim->u3 = 0xFF;
            prim->v0 = prim->v1 = 0x40;
            prim->v2 = prim->v3 = 0x5F;
            if (g_CurrentEntity->facingLeft) {
                prim->next->x1 = g_CurrentEntity->posX.i.hi - 0x14;
            } else {
                prim->next->x1 = g_CurrentEntity->posX.i.hi + 0x14;
            }
            prim->next->y0 = g_CurrentEntity->posY.i.hi + 1;
            prim->priority = g_CurrentEntity->zPriority + 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim->p3 |= 0x10;
            LOH(prim->next->r2) = 0x10;
            LOH(prim->next->b2) = 0x10;
            prim->next->x2 = 0x100;
            prim->next->y2 = 0x100;
            prim->next->b3 = 0x80;
        } else {
            g_CurrentEntity->ext.lesserDemon.unk84 = 3;
        }
        PlaySfxPositional(SFX_ELECTRICITY);
        g_CurrentEntity->ext.lesserDemon.unk84++;
        break;

    case 1:
        prim = g_CurrentEntity->ext.lesserDemon.unk7C;
        LOH(prim->next->tpage) += 0x40;
        prim->next->x2 += 0x40;
        prim->next->y2 = prim->next->x2;
        UnkPrimHelper(prim);
        break;

    case 2:
        primIndex = g_CurrentEntity->primIndex;
        g_api.FreePrimitives(primIndex);
        g_CurrentEntity->flags &= ~FLAG_HAS_PRIMS;
        g_CurrentEntity->ext.lesserDemon.unk84++;
        break;
    }
}

static void func_us_801BC814(Primitive* prim) {
    s16 angleOffset;
    s32 posX2, posY2;
    Pos params;
    Pos offsets;
    Primitive* prim2;
    s16 angle2;
    u8 rnd;
    s32 posX;
    s32 i;
    u8* rgbPtr;
    s16 angle;
    s32 posY;
    u8* component;

    switch (prim->u0) {
    case 0:
        prim->r0 = prim->r1 = 0x80;
        prim->g0 = prim->g1 = 0x80;
        prim->b0 = prim->b1 = 0x80;
        prim->priority = g_CurrentEntity->zPriority + 2;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->x3 += prim->y3;
        prim->x3 &= 0xFFF;
        angle = prim->x3;
        offsets.x.val = rcos(angle) << 3 << 4;
        offsets.y.val = -(rsin(angle) << 3 << 4);
        params.x.i.hi = prim->x0;
        params.x.i.lo = prim->clut;
        params.y.i.hi = prim->y0;
        params.y.i.lo = prim->tpage;
        params.x.val += offsets.x.val;
        params.y.val += offsets.y.val;
        prim->x1 = params.x.i.hi;
        prim->clut = params.x.i.lo;
        prim->y1 = params.y.i.hi;
        prim->tpage = params.y.i.lo;
        if (!prim->u2) {
            prim->u2 = 5;
            rnd = Random() & 1;
            if (g_CurrentEntity->facingLeft) {
                posX = g_CurrentEntity->posX.i.hi + rnd * 16;
            } else {
                posX = g_CurrentEntity->posX.i.hi - rnd * 16;
            }
            posY = g_CurrentEntity->posY.i.hi + ((Random() & 3) * 8) - 12;
            posX2 = posX - prim->x1;
            posY2 = posY - prim->y1;
            angle = ratan2(-posY2, posX2);
            angleOffset = prim->x3;
            angle2 = angle - angleOffset;
            if (angle2 > 0x800) {
                angle2 = 0x1000 - angle2;
            }
            if (angle2 < -0x800) {
                angle2 = 0x1000 + angle2;
            }
            angle2 /= 5;
            prim->y3 = angle2;
        }
        prim->v0 = 1;
        prim->u0++;
        break;

    case 1:
        if (!--prim->v0) {
            prim2 = g_CurrentEntity->ext.lesserDemon.unk7C;
            prim2 = FindFirstUnkPrim(prim2);
            if (prim2 != NULL) {
                if (g_CurrentEntity->facingLeft) {
                    prim2->x0 = prim->x1 + 1;
                } else {
                    prim2->x0 = prim->x1 - 1;
                }
                prim2->y0 = prim->y1;
                prim2->clut = prim->clut;
                prim2->tpage = prim->tpage;
                prim2->p3 = 2;
                prim2->x3 = prim->x3;
                prim2->y3 = prim->y3;
                prim2->u2 = prim->u2 - 1;
                prim->v0 = 8;
                prim->u0++;
            }
        }
        break;

    case 2:
        rgbPtr = &prim->r1;
        for (i = 0; i < 3; i++) {
            component = &rgbPtr[i];
            if (Random() & 1) {
                *component -= 24;
            } else {
                *component -= 12;
            }
            if (*component > 0xC0) {
                *component = 0;
            }
        }
        rgbPtr = &prim->r0;
        for (i = 0; i < 3; i++) {
            component = &rgbPtr[i];
            if (Random() & 1) {
                *component -= 16;
            } else {
                *component -= 8;
            }
            if (*component > 0xC0) {
                *component = 0;
            }
        }
        if (!--prim->v0) {
            prim->u0 = 0;
            prim->p3 = 0;
            prim->drawMode = DRAW_HIDE;
        }
        break;
    }
}

extern EInit D_us_80180A50;
static u8 blueFireballAnim[] = {
    1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7, 1, 8, 0};

void func_us_801BD7D0(Entity* self) {
    Primitive* prim;
    Primitive* uninitializedPrim;
    s32 primIndex;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A50);
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        self->drawFlags = ENTITY_SCALEX;
        self->scaleX = 0x180;
        if (self->facingLeft) {
            self->velocityX = FIX(5.0);
        } else {
            self->velocityX = FIX(-5.0);
        }
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 0x3C);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.lesserDemon.unk7C = prim;
            while (prim != NULL) {
                prim->p3 = 0;
                prim->drawMode = DRAW_HIDE;
                prim->u0 = 0;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        prim = self->ext.lesserDemon.unk7C;
        prim->p3 = 4;
        prim->type = PRIM_GT4;
        prim->tpage = 0x1A;
        prim->clut = PAL_CC_BLUE_EFFECT_A;
        prim->u0 = prim->u2 = 0xE0;
        prim->u1 = prim->u3 = 0xFF;
        prim->v0 = prim->v1 = 0x40;
        prim->v2 = prim->v3 = 0x5F;
        prim->x0 = self->posX.i.hi;
#ifdef VERSION_PSP
        prim->x3 = prim->x0;
#else
        prim->x3 = uninitializedPrim->x0;
#endif
        prim->x1 = prim->x0 + 16;
        prim->x2 = prim->x0 - 16;
        prim->y1 = self->posY.i.hi;
        prim->y2 = prim->y1;
        prim->y0 = prim->y1 + 14;
        prim->y3 = prim->y1 - 14;
        PGREY(prim, 0) = 0x60;
        PGREY(prim, 3) = 0x60;
        if (self->facingLeft) {
            PGREY(prim, 1) = 0xC0;
            PGREY(prim, 2) = 0x10;
        } else {
            PGREY(prim, 1) = 0x10;
            PGREY(prim, 2) = 0xC0;
        }
        prim->priority = self->zPriority + 4;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim = self->ext.lesserDemon.unk7C;
        prim = prim->next;
        for (i = 0; i < 3; i++) {
            if (self->facingLeft) {
                prim->x3 = 0;
            } else {
                prim->x3 = 0x800;
            }
            prim->y3 = 0;
            if (self->facingLeft) {
                prim->x0 = prim->x1 = self->posX.i.hi - 15;
            } else {
                prim->x0 = prim->x1 = self->posX.i.hi + 15;
            }
            prim->y0 = prim->y1 = self->posY.i.hi + i * 2 - 2;
            prim->p3 = 2;
            prim->u2 = 3;
            prim->u0 = 0;
            prim = prim->next;
        }
        break;

    case 1:
        AnimateEntity(blueFireballAnim, self);
        MoveEntity();
        prim = self->ext.lesserDemon.unk7C;
        if (self->facingLeft) {
            prim->x0 = self->posX.i.hi;
            prim->x3 = prim->x0;
            prim->x1 = prim->x0 + 16;
            if (prim->x1 - prim->x2 > 0x80) {
                prim->x2 = prim->x1 - 0x80;
            }
        } else {
            prim->x0 = self->posX.i.hi;
            prim->x3 = prim->x0;
            prim->x2 = prim->x0 - 16;
            if (prim->x1 - prim->x2 > 0x80) {
                prim->x1 = prim->x2 + 0x80;
            }
        }
        prim = prim->next;
        while (prim != NULL) {
            if (prim->p3 & 2) {
                func_us_801BC814(prim);
            }
            prim = prim->next;
        }
        break;
    }
}

static u8 D_pspeu_092596D0[][3] = {
    {0xC0, 0x80, 0xC0}, {0xC0, 0x80, 0x80}, {0xC0, 0xC0, 0x80},
    {0x80, 0xC0, 0x80}, {0x80, 0xA0, 0xA0}, {0x80, 0x80, 0xC0},
    {0xC0, 0x80, 0xC0}};

static u8 unused_triples[][3] = {
    {0x60, 0x40, 0x60}, {0x60, 0x40, 0x40}, {0x60, 0x60, 0x40}, 
    {0x40, 0x60, 0x40}, {0x40, 0x60, 0x60}, {0x40, 0x40, 0x60},
    {0x60, 0x40, 0x60}};

static s16 D_pspeu_092596E8[] = {0x40, 0x80, 0xC0, 0x80};


void func_pspeu_0924F908(Primitive* prim) {
    Primitive* prim2;

    switch (prim->u0) {
    case 0:
        if (prim->u1) {
            prim->r0 = D_pspeu_092596D0[prim->v0 - 1][0] + 0x20;
            prim->g0 = D_pspeu_092596D0[prim->v0 - 1][1] + 0x20;
            prim->b0 = D_pspeu_092596D0[prim->v0 - 1][2] + 0x20;
            prim->r2 = D_pspeu_092596D0[prim->v0][0] + 0x20;
            prim->g2 = D_pspeu_092596D0[prim->v0][1] + 0x20;
            prim->b2 = D_pspeu_092596D0[prim->v0][2] + 0x20;
        } else {
            prim->r0 = D_pspeu_092596D0[prim->v0 - 1][0] + 0x20;
            prim->g0 = D_pspeu_092596D0[prim->v0 - 1][1] + 0x20;
            prim->b0 = D_pspeu_092596D0[prim->v0 - 1][2] + 0x20;
            prim->r2 = D_pspeu_092596D0[prim->v0][0] + 0x20;
            prim->g2 = D_pspeu_092596D0[prim->v0][1] + 0x20;
            prim->b2 = D_pspeu_092596D0[prim->v0][2] + 0x20;
        }
        prim->r1 = prim->r0;
        prim->g1 = prim->g0;
        prim->b1 = prim->b0;
        prim->r3 = prim->r2;
        prim->g3 = prim->g2;
        prim->b3 = prim->b2;
        prim->u0++;
        break;

    case 1:
        if (prim->y1 < 0xF0) {
            prim2 = g_CurrentEntity->ext.lesserDemon.unk7C;
            prim2 = FindFirstUnkPrim(prim2);
            if (prim2 != NULL) {
                prim2->p3 = 2;
                prim2->x0 = prim->x0;
                prim2->x1 = prim->x1;
                prim2->x2 = prim->x2;
                prim2->x3 = prim->x3;
                prim2->y0 = prim->y2;
                prim2->y1 = prim->y3;
                prim2->y2 = prim2->y0 + 0x20;
                prim2->y3 = prim2->y1 + 0x20;
                prim2->priority = prim->priority;
                prim2->drawMode = prim->drawMode;
                prim2->u1 = prim->u1;
                prim2->v0 = prim->v0 + 1;
                if (prim2->v0 > 6) {
                    prim2->v0 = 1;
                }
            }
            prim->u0++;
        }
        break;

    case 2:
        PrimDecreaseBrightness(prim, 5);
        if (prim->y2 < 0) {
            prim->u0 = 0;
            prim->drawMode = DRAW_HIDE;
            prim->p3 = 0;
        }
        break;
    }
}

// Lesser Demon minion spawn
// Creates second, sub-lesser demon.
// Similar to library boss version, but just spawns more lesser demons.
#define PARAM_IS_MINION 0x10
void func_pspeu_0924FE10(void) {
    Entity* tempEntity;
    Primitive* prim;
    s32 primIndex;
    s32 entityId;
    s16 xOffset;

    switch (g_CurrentEntity->ext.lesserDemon.unk84) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 0x1E);
        if (primIndex != -1) {
            g_CurrentEntity->flags |= FLAG_HAS_PRIMS;
            g_CurrentEntity->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.lesserDemon.unk7C = prim;
            while (prim != NULL) {
                prim->priority = g_CurrentEntity->zPriority + 2;
                prim->drawMode = DRAW_HIDE;
                prim->p3 = 0;
                prim = prim->next;
            }
        } else {
            g_CurrentEntity->ext.lesserDemon.unk84 = 6;
        }
        g_CurrentEntity->ext.lesserDemon.unk84++;
        break;

    case 1:
        prim = g_CurrentEntity->ext.lesserDemon.unk7C;
        prim->p3 = 2;
        PGREY(prim, 0) = 0;
        PGREY(prim, 1) = 0;
        PGREY(prim, 2) = 0x60;
        PGREY(prim, 3) = 0x60;
        prim->r2 += 0x40;
        prim->r3 += 0x40;
        prim->y0 = 0x120;
        prim->y1 = 0x100;
        prim->y2 = 0x140;
        prim->y3 = 0x120;
        if (g_CurrentEntity->facingLeft) {
            xOffset = -8;
        } else {
            xOffset = 8;
        }
        prim->x0 = g_CurrentEntity->posX.i.hi - 1 + xOffset;
        prim->x1 = prim->x0 + 2;
        prim->x2 = prim->x0;
        prim->x3 = prim->x1;
        prim->v0 = 1;
        prim->priority = g_CurrentEntity->zPriority + 4;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->u1 = 1;
        prim = prim->next;

        prim->p3 = 2;
        PGREY(prim, 0) = 0;
        PGREY(prim, 1) = 0;
        PGREY(prim, 2) = 0x60;
        PGREY(prim, 3) = 0x60;
        prim->r2 += 0x40;
        prim->r3 += 0x40;
        prim->x0 = g_CurrentEntity->posX.i.hi + 1 + xOffset;
        prim->x1 = prim->x0 - 2;
        prim->x2 = prim->x0;
        prim->x3 = prim->x1;
        prim->y0 = 0x140;
        prim->y1 = 0x120;
        prim->y2 = 0x160;
        prim->y3 = 0x140;
        prim->v0 = 1;
        prim->priority = g_CurrentEntity->zPriority - 2;
        prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->u1 = 0;
        g_CurrentEntity->ext.lesserDemon.unk85 = 0x18;
        g_CurrentEntity->ext.lesserDemon.unk84 = 3;
        break;

    case 2:
        prim = g_CurrentEntity->ext.lesserDemon.unk7C;
        while (prim != NULL) {
            if (prim->p3) {
                func_pspeu_0924F908(prim);
            }
            prim = prim->next;
        }
        prim = g_CurrentEntity->ext.lesserDemon.unk7C;
        while (prim != NULL) {
            if (g_CurrentEntity->ext.lesserDemon.unk80 % 2) {
                if (prim->u1) {
                    prim->x0--;
                    prim->x2 = prim->x0;
                    prim->x1++;
                    prim->x3 = prim->x1;
                } else {
                    prim->x0++;
                    prim->x2 = prim->x0;
                    prim->x1--;
                    prim->x3 = prim->x1;
                }
            }
            prim->y0 -= 8;
            prim->y1 -= 8;
            prim->y2 -= 8;
            prim->y3 -= 8;
            prim = prim->next;
        }
        if (g_CurrentEntity->ext.lesserDemon.unk80 % 2) {
            if (!--g_CurrentEntity->ext.lesserDemon.unk85) {
                g_CurrentEntity->ext.lesserDemon.unk84++;
                tempEntity = AllocEntity(&g_Entities[176], &g_Entities[192]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_LESSER_DEMON, g_CurrentEntity, tempEntity);
                    tempEntity->facingLeft = g_CurrentEntity->facingLeft;
                    if (g_CurrentEntity->facingLeft) {
                        tempEntity->posX.i.hi -= 8;
                    } else {
                        tempEntity->posX.i.hi += 8;
                    }

                    tempEntity->params = PARAM_IS_MINION;
                }
            }
        }
        break;

    case 3:
        prim = g_CurrentEntity->ext.lesserDemon.unk7C;
        while (prim != NULL) {
            if (prim->p3) {
                func_pspeu_0924F908(prim);
            }
            prim = prim->next;
        }
        prim = g_CurrentEntity->ext.lesserDemon.unk7C;
        while (prim != NULL) {
            prim->y0 -= 8;
            prim->y1 -= 8;
            prim->y2 -= 8;
            prim->y3 -= 8;
            prim = prim->next;
        }
        if (g_CurrentEntity->ext.lesserDemon.unk85) {
            if (!--g_CurrentEntity->ext.lesserDemon.unk85) {
                g_CurrentEntity->ext.lesserDemon.unk85 = 0x18;
                g_CurrentEntity->ext.lesserDemon.unk84--;
            }
        }
        break;

    case 4:
        prim = g_CurrentEntity->ext.lesserDemon.unk7C;
        while (prim != NULL) {
            if (prim->p3) {
                func_pspeu_0924F908(prim);
            }
            prim = prim->next;
        }
        prim = g_CurrentEntity->ext.lesserDemon.unk7C;
        while (prim != NULL) {
            if (prim->u1) {
                prim->x0++;
                prim->x2 = prim->x0;
                prim->x1--;
                prim->x3 = prim->x1;
            } else {
                prim->x0--;
                prim->x2 = prim->x0;
                prim->x1++;
                prim->x3 = prim->x1;
            }
            prim->y0 -= 8;
            prim->y1 -= 8;
            prim->y2 -= 8;
            prim->y3 -= 8;
            prim = prim->next;
        }
        if (++g_CurrentEntity->ext.lesserDemon.unk85 > 0x18) {
            g_CurrentEntity->ext.lesserDemon.unk84++;
        }
        break;

    case 5:
        primIndex = g_CurrentEntity->primIndex;
        g_api.FreePrimitives(primIndex);
        g_CurrentEntity->flags &= ~FLAG_HAS_PRIMS;
        g_CurrentEntity->ext.lesserDemon.unk84++;
        break;
    }
}

static s16 D_pspeu_092596F0[] = {0x18, 0x28, 0x18, 0x18, 0xFF, 0x00};

u8 func_pspeu_09250678(void) {
    u8 ret = 0;

    ret = CheckColliderOffsets(D_pspeu_092596F0, g_CurrentEntity->facingLeft);
    if (ret ^ 2) {
        ret = 1;
    } else {
        ret = 0;
    }
    if (g_CurrentEntity->poseTimer == 0) {
        if (g_CurrentEntity->facingLeft) {
            g_CurrentEntity->posX.i.hi += D_pspeu_092595A8[g_CurrentEntity->pose];
        } else {
            g_CurrentEntity->posX.i.hi -= D_pspeu_092595A8[g_CurrentEntity->pose];
        }
    }
    return ret;
}

void EntityLesserDemon(Entity* self) {
    Collider collider;
    Entity* tempEntity;
    s32 xOffset, yOffset;
    s32 i;
    u8 hit;
    s16 posX, posY;
    s16 tempVar;

    if ((self->flags & FLAG_DEAD) && (self->step < 15)) {
        if(self->ext.lesserDemon.unk88 != NULL){
            tempEntity = self->ext.lesserDemon.unk88;
            DestroyEntity(tempEntity);
            self->ext.lesserDemon.unk88 = NULL;
        }
        if (self->flags & FLAG_HAS_PRIMS) {
            g_api.FreePrimitives(self->primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
        }
        self->hitboxState = 0;
        SetStep(15);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A38);
        #ifdef VERSION_US
        self->flags |= FLAG_UNK_02000000;
        #endif
        self->zPriority -= 2;
        self->hitboxOffX = 0;
        self->hitboxOffY = 4;
        if(self->params & PARAM_IS_MINION){
            self->animCurFrame = 0;
            self->step = LD_STEP_MINION_INIT;
            self->hitboxState = 0;
        }
        break;
    case LD_STEP_MINION_INIT:
        // Note: this function calls SetStep(1) so we progress from there.
        func_pspeu_0924DBD0(D_pspeu_09259590);
        break;
    case 1:
        if (UnkCollisionFunc3(D_pspeu_09259590) & 1) {
            SetStep(3);
        }
        break;

    case 2:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (GetDistanceToPlayerX() < 0x80) {
            SetStep(3);
        }
        break;

    case 3:
        if (!self->step_s) {
            self->ext.lesserDemon.unk80 = 0x80;
            self->step_s++;
        }
        hit = func_pspeu_09250678();
        if (hit) {
            self->facingLeft ^= 1;
        }
        if (!AnimateEntity(D_pspeu_092595B8, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        if (hit) {
            SetStep(6);
        }
        if (--self->ext.lesserDemon.unk80) {
            break;
        }
            if (!(self->posX.i.hi & 0xFF00)) {
                if (Random() & 1) {
                    self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                    self->ext.lesserDemon.unk84 = 0;
                    SetStep(13);
                } else {
                    SetStep(8);
                }
            }
            else if (g_Timer % 4 == 0){
                SetStep(3);
            } else {
                SetStep(8);
            }
        
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_pspeu_092595E0, self)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
                self->velocityY = FIX(-4.0);
                if (self->facingLeft) {
                    self->velocityX = FIX(1);
                } else {
                    self->velocityX = FIX(-1);
                }
            }
            break;

        case 1:
            AnimateEntity(D_pspeu_092595E8, self);
            if (UnkCollisionFunc3(D_pspeu_09259590) & 1) {
                PlaySfxPositional(SFX_STOMP_HARD_B);
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            } else {
                self->velocityY -= FIX(0.125);
            }
            break;

        case 2:
            if (!AnimateEntity(D_pspeu_092595F8, self)) {
                SetStep(3);
            }
            break;
        }
        break;

    case 8:
        if (!AnimateEntity(D_pspeu_09259600, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        if (!self->poseTimer && self->pose == 7) {
            PlaySfxPositional(SFX_WING_FLAP_B);
        }
        MoveEntity();
        self->velocityX = 0;
        self->velocityY = FIX(-1.5);
        if (self->posY.i.hi < 0x50) {
            self->velocityY = 0;
            SetStep(9);
        }
        break;

    case 9:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.lesserDemon.unk80 = D_pspeu_092596E8[Random() & 3];
            self->step_s++;
            break;
        }
        AnimateEntity(D_pspeu_09259600, self);
        MoveEntity();
        if (!self->poseTimer && self->pose == 7) {
            PlaySfxPositional(SFX_WING_FLAP_B);
        }
        if (self->facingLeft) {
            self->velocityX = FIX(1.0);
        } else {
            self->velocityX = FIX(-1.0);
        }
        if (!--self->ext.lesserDemon.unk80) {
            self->step_s--;
            if (self->posX.i.hi & 0xFF00) {
                if (g_Timer % 2) {
                    SetStep(10);
                } else {
                    SetStep(14);
                }
            } else {
                tempVar = GetDistanceToPlayerX();
                if (tempVar > 0x40) {
                    if (Random() & 1) {
                        SetStep(4);
                    } else {
                        SetStep(12);
                    }
                } else {
                    if (Random() & 1) {
                        SetStep(14);
                    } else {
                        SetStep(11);
                    }
                }
            }
            if (self->posY.i.hi < 0) {
                SetStep(11);
            }
        }
        break;

    case 10:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }
            self->ext.lesserDemon.unk80 = 0x60;
            self->step_s++;
            break;
        }
        MoveEntity();
        AnimateEntity(D_pspeu_09259620, self);
        if (g_Timer % 8 == 0) {
            PlaySfxPositional(SFX_WING_FLAP_B);
        }
        if (!--self->ext.lesserDemon.unk80) {
            SetStep(9);
        }
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            tempEntity = &PLAYER;
            posX = tempEntity->posX.i.hi - self->posX.i.hi;
            posY = tempEntity->posY.i.hi - self->posY.i.hi;
            if (posX < 0) {
                posX += 0x20;
            } else {
                posX -= 0x20;
            }
            posY += 0x1A;
            tempVar = ratan2(-posY, posX);
            self->velocityX = rcos(tempVar) * 0x30;
            self->velocityY = -rsin(tempVar) * 0x30;

            if (self->velocityX > 0) {
                self->facingLeft = 1;
            } else {
                self->facingLeft = 0;
            }
            self->animCurFrame = 0x18;
            
            tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_UNK_26, self, tempEntity);
                self->ext.lesserDemon.unk88 = tempEntity;
            } else {
                self->ext.lesserDemon.unk88 = NULL;
            }
            self->ext.lesserDemon.unk84 = 0;
            self->ext.lesserDemon.unk87 = 0;
            self->step_s++;
            break;
        case 1:
            MoveEntity();
            posX = self->posX.i.hi;
            posY = self->posY.i.hi + 0x20;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                PlaySfxPositional(SFX_STOMP_HARD_B);
                self->posY.i.hi += collider.unk18;
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                self->step_s++;
                if (self->ext.lesserDemon.unk88 == NULL) {
                    SetStep(3);
                }
            }
            break;

        case 2:
            tempEntity = self->ext.lesserDemon.unk88;
            if (!AnimateEntity(D_pspeu_092595C8, self) &&
                !(self->flags & FLAG_HAS_PRIMS)) {
                self->ext.lesserDemon.unk87 = 0;
                DestroyEntity(tempEntity);
                self->ext.lesserDemon.unk88 = NULL;
                SetStep(3);
                break;
            }
            if (!self->poseTimer && self->pose == 5) {
                PlaySfxPositional(SFX_LESSER_DEMON_SWIPE_ATTACK);
            }
            if (self->pose > 4 && self->pose < 11) {
                tempEntity->posX.i.hi = self->posX.i.hi;
                tempEntity->posY.i.hi = self->posY.i.hi;
                tempEntity->facingLeft = self->facingLeft;
                tempEntity->hitboxState = 1;
                self->ext.lesserDemon.unk87 = 1;
                if (self->facingLeft) {
                    EntityGreyPuffSpawner(self, 5, 3, -4, 32, 2, 7);
                } else {
                    EntityGreyPuffSpawner(self, 5, 3, 4, 32, 2, -7);
                }
            } else {
                tempEntity->hitboxState = 0;
            }
            break;
        }
        if (self->ext.lesserDemon.unk87) {
            func_pspeu_0924E7D0();
        }
        break;

    case 11:
        AnimateEntity(D_pspeu_09259600, self);
        if (!self->poseTimer && self->pose == 7) {
            PlaySfxPositional(SFX_WING_FLAP_B);
        }
        if (UnkCollisionFunc3(D_pspeu_09259590) & 1) {
            PlaySfxPositional(SFX_STOMP_HARD_B);
            SetStep(3);
        }
        if (self->posY.i.hi > 0xD0) {
            SetStep(8);
        }
        break;

    case 12:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            AnimateEntity(D_pspeu_09259640, self);
            if (self->pose == 2) {
                PlaySfxPositional(SFX_LESSER_DEMON_POISON);
                self->ext.lesserDemon.unk84 = 0;
                self->step_s++;
                self->ext.lesserDemon.unk80 = 0;
            }
            break;

        case 1:
            if (func_pspeu_0924DDF0()) {
                tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_UNK_24, self, tempEntity);
                    tempEntity->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        tempEntity->posX.i.hi += 12;
                    } else {
                        tempEntity->posX.i.hi -= 12;
                    }
                    tempEntity->posY.i.hi -= 8;
                }
                self->ext.lesserDemon.unk84 = 0;
                PlaySfxPositional(SFX_FM_EXPLODE_D);
                self->step_s++;
            }
            break;

        case 2:
            if (!AnimateEntity(D_pspeu_09259640, self)) {
                SetStep(9);
            }
            break;
        }
        break;

    case 13:
        if (!self->step_s) {
            self->ext.lesserDemon.unk84 = 0;
            self->step_s++;
        }
        if (!AnimateEntity(D_pspeu_09259650, self)) {
            self->ext.lesserDemon.unk84 = 0;
            SetStep(3);
            break;
        }
        if (self->pose == 3 && self->poseTimer == 0) {
            PlaySfxPositional(SFX_SCIFI_BLAST);
            self->ext.lesserDemon.unk84 = 2;
            tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_UNK_25, self, tempEntity);
                tempEntity->facingLeft = self->facingLeft;
            }
        }
        if (self->pose > 1) {
            func_pspeu_0924EB18();
        }
        break;

    case 14:
        switch (self->step_s) {
        case 0:
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            tempVar = 0;
            hit = false;
            for (i = 0; i < 3; i++) {
                tempVar = posY + i * 16;
                g_api.CheckCollision(posX, tempVar, &collider, 0);
                if (collider.effects != EFFECT_NONE) {
                    self->ext.lesserDemon.unk87 = 0;
                    SetStep(9);
                    return;
                }
            }
            hit = false;
            for (i = 3; i < 10; i++) {
                tempVar = posY + i * 16;
                g_api.CheckCollision(posX, tempVar, &collider, 0);
                if (collider.effects != EFFECT_NONE) {
                    hit |= true;
                    break;
                }
            }
            if (!hit) {
                self->ext.lesserDemon.unk87 = 0;
                SetStep(9);
                return;
            }
            AnimateEntity(D_pspeu_09259660, self);
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->pose == 3) {
                self->ext.lesserDemon.unk84 = 0;
                PlaySfxPositional(SFX_RAPID_SYNTH_BUBBLE);
                self->step_s++;
                self->ext.lesserDemon.unk80 = 0xE0;
            }
            break;

        case 1:
            if (g_Timer % 2) {
                self->palette = 0x22D;
            } else {
                self->palette = 0x232;
            }
            if (!--self->ext.lesserDemon.unk80) {
                self->palette = 0x22D;
                self->hitEffect = 0x22D;
                self->flags &= ~0xF;
                PlaySfxPositional(SFX_TELEPORT_BANG_A);
                self->step_s++;
                self->ext.lesserDemon.unk84++;
            }
            func_pspeu_0924FE10();
            break;

        case 2:
            self->ext.lesserDemon.unk80--;
            if (!AnimateEntity(D_pspeu_09259660, self) &&
                !(self->flags & FLAG_HAS_PRIMS)) {
                self->ext.lesserDemon.unk87 = 0;
                SetStep(9);
            } else {
                func_pspeu_0924FE10();
            }
            break;
        }
        break;

    case 15:
        self->palette = PAL_FLAG(PAL_CC_FIRE_EFFECT);
        if (!(g_Timer % 8)) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, tempEntity);
                tempEntity->posX.i.hi += (Random() & 0x1F) - 0x10;
                tempEntity->posY.i.hi += (Random() & 0x3F) - 0x20;
            }
        }
        if ((g_Timer & 0xF) == 0) {
            PlaySfxPositional(SFX_EXPLODE_B);
        }
        switch (self->step_s) {
        case 0:
            AnimateEntity(D_pspeu_09259600, self);
            if (!self->poseTimer && self->pose == 7) {
                PlaySfxPositional(SFX_WING_FLAP_B);
            }
            if (UnkCollisionFunc3(D_pspeu_09259590) & 1) {
                self->step_s++;
                self->pose = 0;
                self->poseTimer = 0;
            } else {
                self->velocityY -= FIX(3.5 / 16);
            }
            break;

        case 1:
            hit = func_pspeu_09250678();
            if (!AnimateEntity(D_pspeu_09259670, self) || hit) {
                self->pose = 0;
                self->poseTimer = 0;
                self->drawFlags = ENTITY_OPACITY;
                self->blendMode = BLEND_TRANSP | BLEND_ADD;
                self->opacity = 0x80;
                self->ext.lesserDemon.unk80 = 0x40;
                self->step_s++;
            }
            break;

        case 2:
            if(!--self->ext.lesserDemon.unk80){
                PlaySfxPositional(0x65E);
                DestroyEntity(self);
                break;
            }
            AnimateEntity(D_pspeu_09259680, self);
            self->opacity -= 2;
            if (g_Timer % 5 == 0) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                    tempEntity->params = 1;
                    tempEntity->posX.i.hi += (Random() & 0x1F) - 0x10;
                    tempEntity->posY.i.hi += (Random() & 0x1F) - 0x10;
                }
            }
            
            break;
        }
        break;

    case 255:
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params) {
                break;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }

        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (!self->step_s) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
}
extern EInit D_us_80180A5C;

void func_us_801BF7B0(Entity* self) {
    FntPrint("duumy_set\n");
    if (!self->step) {
        InitializeEntity(D_us_80180A5C);
        self->hitboxWidth = 0x1C;
        self->hitboxHeight = 4;
        self->hitboxOffX = -0x14;
        self->hitboxState = 0;
    }
}
