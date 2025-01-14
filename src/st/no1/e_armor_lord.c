// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

// Armor Lord fire wave helper
INCLUDE_ASM("st/no1/nonmatchings/e_armor_lord", func_us_801D1184);

// Armor Lord fire wave helper
INCLUDE_ASM("st/no1/nonmatchings/e_armor_lord", func_us_801D1388);

extern u16 g_EInitInteractable[];

void EntityArmorLordFireWave(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->ext.armorLord.unk80 = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x1A);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.armorLord.unk7C = prim;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim->p3 = 0;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        prim = self->ext.armorLord.unk7C;
        prim = FindFirstUnkPrim2(prim, 2);
        if (prim != NULL) {
            UnkPolyFunc2(prim);
            prim->x2 = self->posX.i.hi;
            if (self->facingLeft) {
                prim->x3 = prim->x2 + 0x20;
            } else {
                prim->x3 = prim->x2 - 0x20;
            }
            prim->y2 = self->posY.i.hi + 0x28;
            prim->y3 = prim->y2;
            prim->next->r3 = 5;
            prim->next->g3 = 0;
        }

    case 1:
        prim = self->ext.armorLord.unk7C;
        while (prim != NULL) {
            if (prim->p3 & 8) {
                if (prim->next->g3) {
                    func_us_801D1184(prim);
                } else {
                    func_us_801D1388(prim);
                }
            }
            prim = prim->next;
        }
        if (self->ext.armorLord.unk80++ > 0x100) {
            DestroyEntity(self);
            return;
        }
    }
}

void func_us_801D1A94(void) {}

INCLUDE_ASM("st/no1/nonmatchings/e_armor_lord", func_us_801D1A9C);

extern MATRIX D_us_80182DF4;
extern SVECTOR D_us_80182E14;
extern SVECTOR D_us_80182E1C;
extern SVECTOR D_us_80182E24;

s32 func_us_801D1DAC(void) {
    long unusedA, unusedB;
    SVECTOR rotA, rotB, rotC;
    VECTOR trans;
    MATRIX m;
    MATRIX lightMatrix;
    CVECTOR color;

    s16 posX, posY;
    Primitive* prim;
    Primitive* prim2;
    s16 z;
    s32 primIndex;
    s32 i;
    u8 temp;
    s32 unused;

    switch (g_CurrentEntity->step_s) {
    case 0:
        g_CurrentEntity->ext.armorLord.unk8D = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0xE);
        if (primIndex != -1) {
            g_CurrentEntity->flags |= FLAG_HAS_PRIMS;
            g_CurrentEntity->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.armorLord.unk7C = prim;
            prim = g_CurrentEntity->ext.armorLord.unk7C;
            if (g_CurrentEntity->facingLeft) {
                prim->u0 = 0xFF;
                prim->u1 = 0xD8;
                prim->x0 = g_CurrentEntity->posX.i.hi - 0x1A;
            } else {
                prim->u0 = 0xD8;
                prim->u1 = 0xFF;
                prim->x0 = g_CurrentEntity->posX.i.hi - 0xD;
            }
            prim->x1 = prim->x0 + 0x28;
            prim->r0 = prim->g0 = prim->b0 = 0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;

            prim2 = prim;
            prim = prim->next;
            prim->u0 = prim2->u0;
            prim->u1 = prim->u0;
            prim->x0 = prim2->x0;
            prim->x1 = prim->x0;
            prim->r0 = prim->g0 = prim->b0 = 0x20;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = 0x80;
            LOW(prim->r3) = LOW(prim->r1);
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;

            prim = prim->next;
            prim->u0 = prim2->u1;
            prim->u1 = prim->u0;
            prim->x0 = prim2->x1;
            prim->x1 = prim->x0;
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = 0x20;
            LOW(prim->r3) = LOW(prim->r1);
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim = g_CurrentEntity->ext.armorLord.unk7C;
            for (i = 0; i < 3; i++) {
                prim->tpage = 0x15;
                prim->clut = 0x160;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->v0 = 0;
                prim->v1 = prim->v0;
                prim->v2 = 0x37;
                prim->v3 = prim->v2;
                prim->x2 = prim->x0;
                prim->x3 = prim->x1;
                prim->y0 = g_CurrentEntity->posY.i.hi - 0x10;
                prim->y1 = prim->y0;
                prim->y2 = prim->y1 + 0x38;
                prim->y3 = prim->y2;
                prim->priority = g_CurrentEntity->zPriority + 1;
                prim = prim->next;
            }
            g_CurrentEntity->ext.armorLord.unk90 = prim;
            while (prim != NULL) {
                prim->tpage = 0x14;
                prim->clut = 0x220;
                prim->u0 = 0xE2;
                prim->u1 = 0xEC;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->v0 = 0xD0;
                prim->v1 = prim->v0;
                prim->v2 = 0xD0;
                prim->v3 = prim->v2;
                prim->r0 = prim->g0 = prim->b0 = 0x40;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->priority = g_CurrentEntity->zPriority + 2;
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
                prim = prim->next;
            }
        } else {
            return 1;
        }

        g_CurrentEntity->ext.armorLord.unk86 = 0x20;
        g_CurrentEntity->ext.armorLord.unk8A = 0;
        g_CurrentEntity->ext.armorLord.unk88 = 0;
        g_CurrentEntity->ext.armorLord.unk8C = 0;
        g_CurrentEntity->drawFlags |= FLAG_DRAW_UNK8;
        g_CurrentEntity->unk6C = 0x80;
        g_CurrentEntity->step_s++;
        break;

    case 1:
        prim = g_CurrentEntity->ext.armorLord.unk7C;
        prim->r0 += 2;
        prim->g0 = prim->b0 = prim->r0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        g_CurrentEntity->unk6C += 0xFE;
        if (!g_CurrentEntity->unk6C) {
            g_CurrentEntity->animCurFrame = 0;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            g_CurrentEntity->ext.armorLord.unk8D += 1;
            PlaySfxPositional(SFX_FIREBALL_SHOT_A);
            g_CurrentEntity->step_s++;
        }
        break;

    case 2:
        g_CurrentEntity->step_s++;
        break;

    case 3:
        if (g_Timer % 8 == 0) {
            prim = g_CurrentEntity->ext.armorLord.unk7C;
            if (g_CurrentEntity->facingLeft) {
                prim->u0--;
                prim->u1++;
            } else {
                prim->u0++;
                prim->u1--;
            }
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->x0++;
            prim->x2 = prim->x0;
            prim->x1--;
            prim->x3 = prim->x1;

            prim = prim->next;
            if (g_CurrentEntity->facingLeft) {
                prim->u1--;
            } else {
                prim->u1++;
            }
            prim->u3 = prim->u1;
            prim->x1++;
            prim->x3 = prim->x1;
            prim->y0 -= 3;
            prim->y2 -= 1;

            prim = prim->next;
            if (g_CurrentEntity->facingLeft) {
                prim->u0++;
            } else {
                prim->u0--;
            }
            prim->u2 = prim->u0;
            prim->x0--;
            prim->x2 = prim->x0;
            prim->y1 -= 3;
            prim->y3 -= 1;
            g_CurrentEntity->ext.armorLord.unk8C += 1;
            if (g_CurrentEntity->ext.armorLord.unk8C > 5) {
                g_CurrentEntity->step_s++;
            }
        }
        break;

    case 5:
        if (g_Timer % 4 == 0) {
            prim = g_CurrentEntity->ext.armorLord.unk7C;
            if (g_CurrentEntity->facingLeft) {
                prim->u0--;
                prim->u1++;
            } else {
                prim->u0++;
                prim->u1--;
            }
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->x0++;
            prim->x2 = prim->x0;
            prim->x1--;
            prim->x3 = prim->x1;

            prim = prim->next;
            if (g_CurrentEntity->facingLeft) {
                prim->u0--;
                prim->u1--;
            } else {
                prim->u0++;
                prim->u1++;
            }
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->x0++;
            prim->x2 = prim->x0;
            prim->x1++;
            prim->x3 = prim->x1;

            prim = prim->next;
            if (g_CurrentEntity->facingLeft) {
                prim->u1++;
                prim->u0++;
            } else {
                prim->u1--;
                prim->u0--;
            }
            prim->u3 = prim->u1;
            prim->u2 = prim->u0;
            prim->x0--;
            prim->x2 = prim->x0;
            prim->x1--;
            prim->x3 = prim->x1;
            g_CurrentEntity->ext.armorLord.unk8C++;
            if (g_CurrentEntity->ext.armorLord.unk8C > 0x14) {
                g_CurrentEntity->ext.armorLord.unk8D = 2;
                g_CurrentEntity->step_s++;
            }
        }
        break;

    case 6:
        if (g_Timer % 2 == 0) {
            prim = g_CurrentEntity->ext.armorLord.unk7C;
            prim = prim->next;
            if (g_CurrentEntity->facingLeft) {
                prim->u0--;
            } else {
                prim->u0++;
            }
            prim->u2 = prim->u0;
            prim->x0++;
            prim->x2 = prim->x0;

            prim = prim->next;
            if (g_CurrentEntity->facingLeft) {
                prim->u1++;
            } else {
                prim->u1--;
            }
            prim->u3 = prim->u1;
            prim->x1--;
            prim->x3 = prim->x1;
            g_CurrentEntity->ext.armorLord.unk8C++;
            if (g_CurrentEntity->ext.armorLord.unk8C > 0x18) {
                g_CurrentEntity->step_s++;
            }
        }
        break;

    case 8:
        prim = g_CurrentEntity->ext.armorLord.unk7C;
        while (prim != NULL) {
            if (g_Timer % prim->p2 == 0) {
                prim->y0--;
            }
            prim->r0 -= 2;
            prim->g0 -= 2;
            prim->b0 -= 2;
            prim = prim->next;
        }
        if (g_CurrentEntity->ext.armorLord.unk8C++ > 0x40) {
            return 1;
        }
        break;
    }

    if (g_CurrentEntity->ext.armorLord.unk8D) {
        prim = g_CurrentEntity->ext.armorLord.unk90;
        prim2 = prim;
        unused = g_CurrentEntity->ext.armorLord.unk8A;
        for (i = 0; i < 8; i++) {
            if (g_CurrentEntity->ext.armorLord.unk88 < 0x5C) {
                prim->v2++;
                prim->v3 = prim->v2;
            }
            if (g_Timer % 3 == 0) {
                temp = prim->u0;
                prim->u0 = prim->u1;
                prim->u1 = temp;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
            }
            SetGeomScreen(0x400);
            rotC.vx = 0;
            rotC.vy = (i * 512) + g_CurrentEntity->ext.armorLord.unk8A;
            rotC.vz = 0;
            RotMatrix(&D_us_80182E24, &m);
            RotMatrixY(rotC.vy, &m);
            SetRotMatrix(&m);
            trans.vx = 0;
            trans.vy = 0;
            trans.vz = 0x400;
            TransMatrix(&m, &trans);
            SetTransMatrix(&m);
            SetBackColor(0x20, 0x20, 0x20);
            color.r = 0x80;
            color.g = 0x60;
            color.b = 0x60;
            color.cd = prim->type;
            RotMatrix(&rotC, &lightMatrix);
            SetColorMatrix(&D_us_80182DF4);
            SetLightMatrix(&lightMatrix);
            if (g_CurrentEntity->facingLeft) {
                posX = g_CurrentEntity->posX.i.hi - 5;
            } else {
                posX = g_CurrentEntity->posX.i.hi + 8;
            }
            posY = g_CurrentEntity->posY.i.hi + 0x29;
            SetGeomOffset(posX, posY);
            rotA.vx = 0;
            rotA.vy = 0;
            rotA.vz = -g_CurrentEntity->ext.armorLord.unk86;
            rotB.vx = 0;
            rotB.vy = -g_CurrentEntity->ext.armorLord.unk88;
            rotB.vz = -g_CurrentEntity->ext.armorLord.unk86;
            prim->x0 = prim2->x1;
            prim->y0 = prim2->y1;
            prim->x2 = prim2->x3;
            prim->y2 = prim2->y3;
            prim->r0 = prim2->r1;
            prim->g0 = prim2->g1;
            prim->b0 = prim2->b1;
            prim->r2 = prim2->r3;
            prim->g2 = prim2->g3;
            prim->b2 = prim2->b3;
            z = RotTransPers(&rotA, (long*)(&prim->x3), &unusedA, &unusedB);
            z += RotTransPers(&rotB, (long*)(&prim->x1), &unusedA, &unusedB);
            z /= 2;
            NormalColorCol(&D_us_80182E14, &color, (CVECTOR*)(&prim->r3));
            NormalColorCol(&D_us_80182E1C, &color, (CVECTOR*)(&prim->r1));
            prim->priority = g_CurrentEntity->zPriority + (0x101 - z);
            prim2 = prim;
            prim = prim->next;
        }
        prim = g_CurrentEntity->ext.armorLord.unk90;
        prim->x0 = prim2->x1;
        prim->y0 = prim2->y1;
        prim->x2 = prim2->x3;
        prim->y2 = prim2->y3;
        prim->r0 = prim2->r1;
        prim->g0 = prim2->g1;
        prim->b0 = prim2->b1;
        prim->r2 = prim2->r3;
        prim->g2 = prim2->g3;
        prim->b2 = prim2->b3;
        g_CurrentEntity->ext.armorLord.unk8A += 4;
        if (g_CurrentEntity->ext.armorLord.unk88 < 0x68) {
            g_CurrentEntity->ext.armorLord.unk88 += 2;
        } else if (g_Timer % 4 == 0) {
            g_CurrentEntity->ext.armorLord.unk86 -= 1;
            if (g_CurrentEntity->ext.armorLord.unk86 == 0x19) {
                g_CurrentEntity->step_s++;
            }
        }
        if (g_CurrentEntity->ext.armorLord.unk8D == 2) {
            g_CurrentEntity->ext.armorLord.unk88 += 8;
        }
        if (!g_CurrentEntity->ext.armorLord.unk86) {
            primIndex = g_CurrentEntity->primIndex;
            g_api.FreePrimitives(primIndex);
            primIndex = g_api.AllocPrimitives(PRIM_TILE, 0x14);
            if (primIndex != -1) {
                g_CurrentEntity->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                g_CurrentEntity->ext.armorLord.unk7C = prim;
                while (prim != NULL) {
                    prim->x0 = (posX + (Random() & 3)) - 2;
                    prim->y0 = posY - 0x48 + (Random() & 0x3F);
                    prim->u0 = 1;
                    prim->v0 = 1;
                    prim->r0 = 0xE0;
                    prim->b0 = 0x88;
                    prim->g0 = 0xA0;
                    prim->p2 = (Random() & 7) + 1;
                    prim->priority = g_CurrentEntity->zPriority + 1;
                    prim->drawMode =
                        DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                    prim = prim->next;
                }
            }
            g_CurrentEntity->ext.armorLord.unk8D = 0;
            g_CurrentEntity->ext.armorLord.unk8C = 0;
            g_CurrentEntity->step_s++;
        }
    }
    return 0;
}

extern u16 D_us_80180ADC[];
extern s32 D_us_80182D4C;
extern u8 D_us_80182D50[];
extern s16 D_us_80182D58[];
extern s16 D_us_80182D68[];
extern s16 D_us_80182D70[];
extern u8 D_us_80182D78[];
extern u8 D_us_80182D84[];
extern u8 D_us_80182D9C[];
extern u8 D_us_80182DA4[];
extern u8 D_us_80182DAC[];
extern u8 D_us_80182DC4[];
extern u8 D_us_80182DE0[];
extern u8 D_us_80182DEC[];

void EntityArmorLord(Entity* self) {
    Entity* tempEntity;
    s16 xDistance;
    s32 posX;
    s32 primIndex;

    if ((self->flags & FLAG_DEAD) && (self->step < 8)) {
        tempEntity = self + 1;
        DestroyEntity(tempEntity);
        PlaySfxPositional(0x753);
        if (self->flags & FLAG_HAS_PRIMS) {
            primIndex = self->primIndex;
            g_api.FreePrimitives(primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
        }
        self->flags &= ~FLAG_UNK_20000000;
        self->zPriority -= 4;
        self->hitboxState = 0;
        D_us_80182D4C = 1;
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        if (D_us_80182D4C != 0) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(D_us_80180ADC);
        tempEntity = self + 1;
        CreateEntityFromEntity(E_ID_4B, self, tempEntity);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        break;

    case 1:
        if (UnkCollisionFunc3(D_us_80182D58) & 1) {
            SetStep(2);
        }
        break;

    case 2:
        if (GetDistanceToPlayerX() < 0xA0) {
            SetStep(3);
        }
        break;

    case 3:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.armorLord.unk84 = self->facingLeft;
            self->ext.armorLord.unk80 = D_us_80182D70[Random() & 3];
            self->step_s++;
        }
        if (!AnimateEntity(D_us_80182D78, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        UnkCollisionFunc2(D_us_80182D68);
        if (self->ext.armorLord.unk84) {
            self->velocityX = FIX(0.25);
        } else {
            self->velocityX = FIX(-0.25);
        }
        xDistance = GetDistanceToPlayerX();
        if (xDistance < 0x50) {
            self->ext.armorLord.unk84 = self->facingLeft ^ 1;
        }
        if (xDistance > 0x70) {
            self->ext.armorLord.unk84 = self->facingLeft;
        }
        if (!--self->ext.armorLord.unk80) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            SetStep(D_us_80182D50[Random() & 7]);
        }
        if (g_Player.status & PLAYER_STATUS_UNK400) {
            if (!self->ext.armorLord.unk85 && (Random() & 1)) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                SetStep(7);
            }
            self->ext.armorLord.unk85 = 1;
        } else {
            self->ext.armorLord.unk85 = 0;
        }
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80182D84, self)) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
                self->ext.armorLord.unk80 = 0x80;
            }
            break;

        case 1:
            AnimateEntity(D_us_80182D9C, self);
            if (!--self->ext.armorLord.unk80) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
            }
            if (self->ext.armorLord.unk80 % 7 == 0) {
                PlaySfxPositional(SFX_WEAPON_SWISH_A);
            }
            break;

        case 2:
            if (!AnimateEntity(D_us_80182DA4, self)) {
                SetStep(3);
            }
            break;
        }
        break;

    case 5:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
        }
        if (!self->animFrameDuration && self->animCurFrame == 0x14) {
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
            PlaySfxPositional(0x751);
            g_api.func_80102CD8(4);
        }
        if (!self->animFrameDuration && self->animFrameIdx == 5) {
            if (self->facingLeft) {
                self->velocityX = FIX(4.0);
            } else {
                self->velocityX = FIX(-4.0);
            }
        }
        UnkCollisionFunc2(D_us_80182D68);
        self->velocityX -= self->velocityX / 8;
        if (!AnimateEntity(D_us_80182DAC, self)) {
            SetStep(3);
        }
        break;

    case 6:
        if (self->animFrameIdx > 5 && !self->step_s) {
            PlaySfxPositional(SFX_FIREBALL_SHOT_A);
            PlaySfxPositional(0x752);
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(
                    E_ARMOR_LORD_FIRE_WAVE, self, tempEntity);
                tempEntity->facingLeft = self->facingLeft;
                tempEntity->pfnUpdate = EntityArmorLordFireWave;
                tempEntity->step = 0;
            }
            self->step_s++;
        }
        if (!AnimateEntity(D_us_80182DC4, self)) {
            SetStep(3);
        }
        break;

    case 7:
        if (!AnimateEntity(D_us_80182DE0, self)) {
            self->hitboxState = 3;
            self->step_s = 3;
        }
        if (self->animFrameIdx > 1) {
            func_us_801D1A9C();
            if ((self->flags & FLAG_HAS_PRIMS) == 0) {
                SetStep(3);
            }
        }
        break;

    case 8:
        if (!AnimateEntity(D_us_80182DEC, self)) {
            SetStep(9);
        }
        if (g_Timer % 8 == 0) {
            PlaySfxPositional(SFX_EXPLODE_FAST_B);
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, tempEntity);
                tempEntity->posX.i.hi += (Random() & 0x1F) - 0x10;
                tempEntity->posY.i.hi += (Random() & 0x3F) - 0x10;
            }
        }
        break;

    case 9:
        if (func_us_801D1DAC()) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    self->hitboxHeight = 0x1C;
    self->hitboxOffX = 0;
    self->hitboxOffY = 0xC;
    switch (self->animCurFrame) {
    case 5:
    case 16:
    case 17:
    case 29:
        self->hitboxOffX = 0x10;
        break;
    case 12:
    case 13:
    case 21:
    case 25:
        self->hitboxOffX = -2;
        self->hitboxHeight = 0x1A;
        break;
    case 4:
    case 6:
    case 7:
    case 30:
        self->hitboxOffX = 7;
        break;
    }
    posX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
    if (posX > 0x90) {
        self->posX.i.hi = 0x90 - g_Tilemap.scrollX.i.hi;
    }
}
