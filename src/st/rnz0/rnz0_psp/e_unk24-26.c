// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rnz0.h"

INCLUDE_ASM("st/rnz0_psp/nonmatchings/rnz0_psp/e_unk24-26", func_pspeu_0924DBD0);

INCLUDE_ASM("st/rnz0_psp/nonmatchings/rnz0_psp/e_unk24-26", func_pspeu_0924DDF0);

extern EInit g_EInitLesserDemonSpit;

extern s16 D_pspeu_092595A0[];

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

// lesser demon helper
INCLUDE_ASM("st/rnz0_psp/nonmatchings/rnz0_psp/e_unk24-26", func_pspeu_0924E7D0);
// lesser demon helper
INCLUDE_ASM("st/rnz0_psp/nonmatchings/rnz0_psp/e_unk24-26", func_pspeu_0924EB18);

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

// Lesser Demon minion spawn?
// Seems like the vertical tractor beam effect that spawns
// Mudmen, Skeleton, Ectoplasm
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
                    CreateEntityFromEntity(
                        0x23, g_CurrentEntity, tempEntity);
                    tempEntity->facingLeft = g_CurrentEntity->facingLeft;
                    if (g_CurrentEntity->facingLeft) {
                        tempEntity->posX.i.hi -= 8;
                    } else {
                        tempEntity->posX.i.hi += 8;
                    }
                    tempEntity->params = 0x10;
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

INCLUDE_ASM("st/rnz0_psp/nonmatchings/rnz0_psp/e_unk24-26", func_pspeu_09250678);

INCLUDE_ASM("st/rnz0_psp/nonmatchings/rnz0_psp/e_unk24-26", EntityLesserDemon);

INCLUDE_ASM("st/rnz0_psp/nonmatchings/rnz0_psp/e_unk24-26", func_us_801BF7B0);
