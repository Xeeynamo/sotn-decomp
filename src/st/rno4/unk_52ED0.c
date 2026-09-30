// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno4.h"

extern AnimateEntityFrame D_us_8018230C[];

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", func_pspeu_0924B480);

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", EntityAlucardWaterEffect);

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", EntitySplashWater);

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", EntitySurfacingWater);

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", EntitySideWaterSplash);

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", EntitySmallWaterDrop);

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", EntityWaterDrop);

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", func_us_801D511C);

extern s16 D_us_80182330[];
extern u16 g_EInitDarkOctopus;

void func_us_801D58FC(Entity* self) {
    Entity* prevEnt;

    if ((self->flags & FLAG_DEAD) && (self->step < 2)) {
        self->hitboxState = 0;
        self->drawFlags |= ENTITY_OPACITY;
        self->opacity = 0x80;
        self->ext.et_801D58FC.unk82 = 0x80;
        SetStep(2);
    }

    prevEnt = self - 1;
    self->posX.i.hi = prevEnt->posX.i.hi;
    self->posY.i.hi = prevEnt->posY.i.hi;
    self->posY.i.hi += D_us_80182330[prevEnt->animCurFrame];

    switch (self->step) {
    case 0:
        InitializeEntity(&g_EInitDarkOctopus);
        self->hitboxWidth = 6;
        self->hitboxHeight = 0xB;
        self->hitboxOffX = 1;
        self->hitboxOffY = -5;
        self->nextPart = self - 1;

#if defined(VERSION_PSP)
        break;
#endif

    case 1:
        AnimateEntity(D_us_8018230C, self);

        break;

    case 2:
        if (!(g_Timer % 8)) {
            prevEnt =
                AllocEntity(&g_Entities[0xE0], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (prevEnt) {
                CreateEntityFromEntity(E_EXPLOSION, self, prevEnt);
                prevEnt->params = 0x11;
            }
        }
        switch (self->step_s) {
        case 0:
            prevEnt =
                AllocEntity(&g_Entities[0xE0], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (prevEnt) {
                CreateEntityFromEntity(E_SUBWPN_IN_CONT, self, prevEnt);
                prevEnt->params = 2;
                self->ext.et_801D58FC.entity = prevEnt;
                prevEnt->ext.et_801D58FC.entity = self;
            } else {
                self->ext.et_801D58FC.entity = 0;
            }
            self->step_s += 1;

            break;

        case 1:
            self->opacity -= 4;

            if (!self->opacity) {
                self->blendMode = BLEND_NO;
                self->opacity = 0x80;
                self->poseTimer = 0;
                self->pose = 0;
                self->palette = PAL_FLAG(0x224);
                self->drawFlags |= ENTITY_SCALEY;
                self->scaleY = 0x100;

                if (self->ext.et_801D58FC.entity != 0) {
                    prevEnt = self->ext.et_801D58FC.entity;
                    DestroyEntity(prevEnt);
                }

                self->step_s += 1;
            }
            break;

        case 2:
            self->scaleY -= 4;
            self->posY.val += FIX(0.1875);

            if (self->scaleY < 0x20) {
                self->step_s += 1;
            }

            break;

        case 3:
            DestroyEntity(self);
        }
    }
}

extern u16 D_us_80180B54;
extern s16 D_us_801822DC;

void func_us_801D5BA4(Entity* self) {
    Entity* player;

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180B54);
        self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY | ENTITY_ROTATE;
        self->drawFlags |= ENTITY_OPACITY;
        self->blendMode = BLEND_SUB | BLEND_TRANSP;
        self->opacity = 0x40;
        self->scaleX = 0x10;
        self->scaleY = 0x40;
        player = &PLAYER;
        self->zPriority = player->zPriority + 1;
        self->rotate = self->ext.et_801D5BA4.unk84;
        self->ext.et_801D5BA4.unk88 = 0x30;
        self->step_s = 0;
        return;

    case 1:
        UnkCollisionFunc2(&D_us_801822DC);
        self->velocityX =
            rsin(self->ext.et_801D5BA4.unk84) * self->ext.et_801D5BA4.unk88;
        self->velocityY =
            -rcos(self->ext.et_801D5BA4.unk84) * self->ext.et_801D5BA4.unk88;
        if (self->ext.et_801D5BA4.unk88 > 12) {
            self->ext.et_801D5BA4.unk88 -= 2;
        }
        switch (self->step_s) {
        case 0:
            self->scaleX += 8;
            self->scaleY += 0x10;
            if (self->scaleX == 0x100) {
                self->scaleY = 0x100;
                self->ext.et_801D5BA4.unk88 = 4;
                self->hitboxState = 0;
                self->step_s += 1;
                return;
            }
            break;

        case 1:
            self->scaleX += 8;
            self->scaleY += 8;
            self->opacity -= 2;
            if (!self->opacity) {
                DestroyEntity(self);
            }
        }
    }
}

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", StepTowards);

void func_us_801D5DC8(Primitive* prim) {
    s32 yPos;
    switch (prim->p2) {
    case 0:
        LOW(prim->x2) = Random() * 8;
        prim->x3 = (Random() & 0x1F) + 0x10;
        prim->drawMode = DRAW_UNK02;
        prim->p2 += 1;

    case 1:
        yPos = (prim->y0 << 0x10) + prim->y1;
        yPos = yPos + LOW(prim->x2);
        LOW(prim->x2) -= 0x1000;
        prim->y0 = yPos >> 0x10;
        prim->y1 = yPos & 0xffff;
        if (!(prim->x3 -= 1)) {
            prim->p2 = 0;
            prim->drawMode = DRAW_HIDE;
            prim->p3 = 0;
        }
        return;
    }
}

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", func_us_801D5E90);

extern u16 D_us_80180B6C;

void func_us_801D68E0(Entity* self) {
    Primitive* prim;
    Entity* ent;
    s32 xPosition;
    s32 primIndex;
    s32 yPosition;
    s16 angle;

    if (self->hitFlags && !(self->hitFlags & 0x80)) {
        self->hitboxState = 0;
        SetStep(2);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180B6C);
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);

        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801D68E0.unk7C = prim;

        prim->x0 = (prim->x1 = self->posX.i.hi);
        prim->y0 = (prim->y1 = self->posY.i.hi);
        prim->r0 = 0xFF;
        prim->g0 = 0x60;
        prim->b0 = 0x60;
        prim->r1 = 0x80;
        prim->g1 = 0x40;
        prim->b1 = 0x40;
        prim->priority = self->zPriority;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;

        angle = self->ext.et_801D68E0.unk8C;

        if (self->facingLeft) {
            angle = -angle;
        }

        self->velocityX = rsin((s32)angle) * (-0x80);
        self->velocityY = rcos((s32)angle) << 7;
        self->ext.et_801D68E0.unk80 = 0x20;

    case 1:
        MoveEntity();

        prim = self->ext.et_801D68E0.unk7C;
        xPosition = (prim->x0 = self->posX.i.hi);
        yPosition = (prim->y0 = self->posY.i.hi);

        if (!(self->ext.et_801D68E0.unk80 -= 1)) {
            self->step = 2;
        }

        break;

    case 2:
        self->velocityX = -self->velocityX;
        self->velocityY = -self->velocityY;
        self->step++;

    case 3:
        MoveEntity();

        prim = self->ext.et_801D68E0.unk7C;
        xPosition = (prim->x0 = self->posX.i.hi);
        yPosition = (prim->y0 = self->posY.i.hi);

        prim = self->ext.et_801D68E0.unk7C;
        xPosition -= prim->x1;
        yPosition -= prim->y1;

        if ((abs(xPosition) < 8) && (abs(yPosition) < 8)) {
            DestroyEntity(self);
        }
    }

    ent = self->ext.et_801D68E0.unk9C;
#if defined(VERSION_PSP) || defined(FIX_UB)
    // Non-PSX versions fix a null pointer here
    if (ent != NULL) {
#else
    if (1) {
#endif
        if (ent->entityId != 0x40) {
            DestroyEntity(self);
        }
    }
}

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", func_us_801D6B8C);
