// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rnz0.h"

extern EInit g_EInitInteractable;
// Fire demon head and arms go back. Maybe prep for shooting fireball?
static u8 D_pspeu_09258898[] = {
    1, 13, 1, 14, 2, 16, 8, 2, 10, 3, 10, 4, 10, 5, 10, 6, 255, 0};
// Idle animation, just moving up and down a little
static u8 D_pspeu_092588B0[] = {10, 3, 10, 4, 10, 5, 10, 6, 0};
// Walk cycle
static u8 D_pspeu_092588C0[] = {24, 7, 23, 8, 16, 9, 20, 10, 20, 11, 16, 12, 0};
// Big shaking charge-up animation
static u8 D_pspeu_092588D0[] = {1, 13, 1, 14, 0};
// head rears back to shoot
static u8 D_pspeu_092588D8[] = {1, 15, 2, 16, 0};
// blasting fireball from mouth
static u8 D_pspeu_092588E0[] = {32, 17, 32, 18, 255, 0};

static s32 D_us_80181A68[] = {
    FIX(-1), FIX(-1.5), FIX(-1.5), FIX(-1.5), FIX(-3)};
static u8 D_us_80181A7C[] = {1, 9, 21, 43};
static u16 D_us_80181A80[] = {16, 24, 42, 46};

void EntityUnkId22(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 2;
        self->animCurFrame = D_us_80181A7C[self->params & 0xF];
        self->velocityY = D_us_80181A68[self->params & 0xF];
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_NOT_AN_ENEMY |
                      FLAG_UNK_00200000 | FLAG_UNK_2000;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        if (self->params & 0x10) {
            self->palette = PAL_FLAG(0x195);
            self->blendMode = BLEND_TRANSP;
        }
        if (self->params & 0x20) {
            self->blendMode = BLEND_SUB | BLEND_TRANSP;
        }
        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        self->params &= 0xF;
        self->step++;
        return;
    }
    self->posY.val += self->velocityY;
    self->poseTimer++;
    if (!(self->poseTimer % 2)) {
        self->animCurFrame += 1;
    }
    if (self->poseTimer > D_us_80181A80[self->params]) {
        DestroyEntity(self);
    }
}

typedef struct fireDemonPrim {
    struct fireDemonPrim* next;
    s32 : 32;
    s32 : 32;
    s16 unkC;
    s16 unkE;
    s32 unk10;
    s32 unk14;
    s16 unk18;
    s16 : 16;
    s16 : 16;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    u8 unk28;
    s16 : 16;
    s16 : 16;
    s8 unk2E;
    s16 unk30;
    s16 : 16;
    s16 : 16;
    u16 unk36;
} fireDemonPrim;

#define FD_NEXT ((fireDemonPrim*)prim->next)

void func_pspeu_0923D100(Primitive* prim) {
    switch (FD_NEXT->unk28) {
    case 0:
        UnkPolyFunc2(prim);
        prim->tpage = 0x1A;
        prim->clut = 0x19D;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;
        FD_NEXT->unk18 = g_CurrentEntity->posX.i.hi;
        FD_NEXT->unkE = g_CurrentEntity->posY.i.hi;
        FD_NEXT->unk20 = 0x40;
        FD_NEXT->unk22 = 0x40;
        FD_NEXT->unk2E = 0x40;
        prim->p3 |= 0x10;
        FD_NEXT->unk24 = 0;
        FD_NEXT->unk26 = FD_NEXT->unk24;
        prim->priority = g_CurrentEntity->zPriority + 3;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        FD_NEXT->unk28++;
        /* fallthrough */
    case 1:
        FD_NEXT->unk24 += 0x300;
        FD_NEXT->unk26 = FD_NEXT->unk24;
        if (FD_NEXT->unk24 > 0x1800) {
            prim->clut = 0x19C;
            FD_NEXT->unk2E = 0x28;
            FD_NEXT->unk28++;
        }
        break;
    case 2:
        FD_NEXT->unk24 += 0x180;
        FD_NEXT->unk26 = FD_NEXT->unk24;
        if (FD_NEXT->unk24 > 0x2000) {
            FD_NEXT->unk28++;
        }
        break;
    case 3:
        if (PrimDecreaseBrightness(prim, 6) == 0) {
            prim->drawMode = DRAW_HIDE;
            FD_NEXT->unk28++;
        }
        break;
    }
    if (FD_NEXT->unk28 < 3) {
        UnkPrimHelper(prim);
    }
}

static u8 D_pspeu_09258910[] = {4,  0,  32,  31, 31, 2,  64, 32, 225, 16, 4,
                                32, 32, 225, 31, 2,  32, 32, 31, 16,  0};
static u8 D_pspeu_09258928[] = {
    3,   64, 32, 15, 15, 3,   80, 32, 15, 15, 3,  80, 32,
    241, 15, 3,  96, 32, 241, 15, 3,  96, 32, 15, 15, 0};
static u8 D_pspeu_09258948[] = {
    2,   0,  32, 31, 15, 2,  96, 0,   31, 15,  2,   128, 0,
    225, 15, 2,  64, 0,  31, 15, 2,   96, 0,   225, 15,  2,
    32,  0,  31, 15, 2,  64, 0,  225, 15, 255};
static u8 D_pspeu_09258970[] = {
    2, 32, 0, 31, 15, 3, 64, 0, 225, 15, 3, 96, 0, 225, 15, 0};
static u8 D_pspeu_09258980[] = {
    2, 64, 0, 225, 15, 2, 64, 0, 31, 15, 2, 96, 0, 225, 15, 0};

extern EInit D_us_80180A2C;

void EntityUnkId21(Entity* self) {
    Entity* player = &PLAYER; // unused
    Entity* explosion;
    Primitive* prim;
    Primitive* prim2;
    s16 xVar;
    s16 yVar;
    s32 primIndex;
    s16 angle;
    Collider collider;

    ((u16*)&D_8006C384)[3] = self->step; // what is this madness
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A2C);
        self->animCurFrame = 0;
        angle = 0x600;
        if (self->facingLeft) {
            angle = -0x600;
        }
        self->velocityX = rsin(angle) * -0x40;
        self->velocityY = rcos(angle) * -0x40;
        self->ext.fireDemon.angle = angle;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 6);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        UnkPolyFunc2(prim);
        prim->tpage = 0x1A;
        prim->clut = 0x170;
        FD_NEXT->unk1E = -angle;
        FD_NEXT->unk20 = 0x18;
        FD_NEXT->unk22 = 0x40;
        FD_NEXT->unk18 = self->posX.i.hi;
        FD_NEXT->unkE = self->posY.i.hi;
        FD_NEXT->unk10 = (-rsin(angle) * 0x38);
        FD_NEXT->unk14 = (-rcos(angle) * 0x38);
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;
        prim = prim->next;
        UnkPolyFunc2(prim);
        FD_NEXT->unk1E = angle;
        prim->tpage = 0x1A;
        prim->clut = 0x170;
        FD_NEXT->unk1E = (0x800 - angle);
        FD_NEXT->unk20 = 0x10;
        FD_NEXT->unk22 = 0x18;
        FD_NEXT->unk18 = self->posX.i.hi;
        FD_NEXT->unkE = self->posY.i.hi;
        FD_NEXT->unk10 = (rsin(angle) * -0x40);
        FD_NEXT->unk14 = (rcos(angle) * -0x40);
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;
        prim = prim->next;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.fireDemon.primA4 = NULL;
    case 1:
        MoveEntity();
        self->ext.fireDemon.unk88++;
        prim = self->ext.prim;
        if (!(self->ext.fireDemon.unk88 % 2)) {
            FD_NEXT->unk22 ^= 8;
        }
        UpdateAnimation(&D_pspeu_09258910, prim);
        UnkPrimHelper(prim);
        prim = prim->next;
        prim = prim->next;
        if ((self->ext.fireDemon.unk88 % 3) == 0) {
            FD_NEXT->unk22++;
        }

        if (((self->ext.fireDemon.unk88 % 4) == 0) && (FD_NEXT->unk20 > 8)) {
            FD_NEXT->unk20--;
        }
        UpdateAnimation(&D_pspeu_09258928, prim);
        UnkPrimHelper(prim);
        prim = prim->next;
        prim = prim->next;
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi;
        g_api.CheckCollision(xVar, yVar, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            explosion = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (explosion != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, explosion);
                explosion->params = EXPLOSION_UNK_19;
            }
            self->posY.i.hi += collider.unk18;
            self->step += 1;
            PlaySfxPositional(SFX_EXPLODE_B);
        }
        break;
    case 2:
        prim = self->ext.prim;
        prim->p2 = 0;
        prim->p1 = 0;
        FD_NEXT->unk18 = self->posX.i.hi;
        FD_NEXT->unkE = self->posY.i.hi - 8;
        FD_NEXT->unk10 = 0x30000;
        FD_NEXT->unk14 = 0;
        FD_NEXT->unk1E = 0;
        FD_NEXT->unk20 = 0x20;
        FD_NEXT->unk22 = 0x10;
        FD_NEXT->unk30 = FD_NEXT->unk22 / 2;
        prim = prim->next;
        prim = prim->next;
        prim->p2 = 0;
        prim->p1 = 0;
        FD_NEXT->unk18 = self->posX.i.hi;
        FD_NEXT->unkE = self->posY.i.hi - 8;
        FD_NEXT->unk10 = 0xFFFD0000;
        FD_NEXT->unk14 = 0;
        FD_NEXT->unk1E = 0;
        FD_NEXT->unk20 = 0x20;
        FD_NEXT->unk22 = 0x10;
        FD_NEXT->unk30 = FD_NEXT->unk22 / 2;
        prim = prim->next;
        prim = prim->next;
        self->ext.fireDemon.primA4 = prim;
        self->step += 1;
        /* fallthrough */
    case 3:
        prim = self->ext.prim;
        UnkPrimHelper(prim);
        UpdateAnimation(&D_pspeu_09258948, prim);
        FD_NEXT->unk10 -= 0x3000;
        FD_NEXT->unk30 += 2;
        prim->x0 = prim->x2 = self->posX.i.hi - 0x10;
        prim->y1 = (u32)self->posY.i.hi - FD_NEXT->unk30;
        prim = prim->next;
        prim = prim->next;
        UnkPrimHelper(prim);
        UpdateAnimation(&D_pspeu_09258948, prim);
        FD_NEXT->unk10 += 0x3000;
        FD_NEXT->unk30 += 2;
        prim->x1 = prim->x3 = self->posX.i.hi + 0x10;
        prim->y0 = (u32)self->posY.i.hi - FD_NEXT->unk30;
        if (FD_NEXT->unk10 == 0) {
            self->step = 4;
        }
        break;
    case 4:
        prim = self->ext.prim;
        self->ext.fireDemon.unk9C.xVars[1] =
            (prim->x3 - self->posX.i.hi) - 0x10;
        prim->p1 = 0;
        prim->p2 = 0;
        prim = prim->next;
        prim = prim->next;
        self->ext.fireDemon.unk9C.xVars[0] =
            ((prim->x2 - self->posX.i.hi) + 0x10);
        self->ext.fireDemon.unkA0 = true;
        prim->p1 = 2;
        prim->p2 = 0;
        g_api.func_80102CD8(1);
        PlaySfxPositional(SFX_FIREBALL_SHOT_B);
        self->step += 1;
        break;
    case 5:
        prim = self->ext.prim;
        UpdateAnimation(&D_pspeu_09258970, prim);
        prim->y0 -= 12;
        prim->y1 += 3;
        prim->x1 = prim->x3 -= 1;
        prim2 = prim;
        prim = prim->next;
        prim = prim->next;
        UpdateAnimation(&D_pspeu_09258980, prim);
        prim->y0 = prim2->y0;
        prim->y1 = prim2->y1;
        xVar = self->posX.i.hi * 2;
        prim->x0 = xVar - prim2->x0;
        prim->x1 = xVar - prim2->x1;
        prim->x2 = xVar - prim2->x2;
        prim->x3 = xVar - prim2->x3;
        if (prim->y1 > prim->y2) {
            self->step += 1;
        }
        break;
    case 6:
        prim = self->ext.prim;
        FD_NEXT->unkE = prim->y0;
        FD_NEXT->unk14 = 0;
        prim->p1 = 2;
        prim->p2 = 0;
        prim = prim->next;
        prim = prim->next;
        FD_NEXT->unkE = prim->y0;
        FD_NEXT->unk14 = 0;
        prim->p1 = 1;
        prim->p2 = 0;
        self->step += 1;
        break;
    case 7:
        prim = self->ext.prim;
        UpdateAnimation(&D_pspeu_09258980, prim);
        prim->y0 = FD_NEXT->unkE;
        LOW(FD_NEXT->unkC) += FD_NEXT->unk14;
        FD_NEXT->unk14 += 0x3000;
        prim2 = prim;
        prim = prim->next;
        prim = prim->next;
        UpdateAnimation(&D_pspeu_09258970, prim);
        prim->y0 = prim2->y0;
        prim->y1 = prim2->y1;
        xVar = self->posX.i.hi * 2;
        prim->x0 = xVar - prim2->x0;
        prim->x1 = xVar - prim2->x1;
        prim->x2 = xVar - prim2->x2;
        prim->x3 = xVar - prim2->x3;
        if (prim->y0 > prim->y2) {
            self->step += 1;
        }
        break;
    case 8:
        prim = self->ext.prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.prim = NULL;
        self->ext.fireDemon.primA4 = NULL;
        self->ext.fireDemon.unk88 = 0x10;
        self->step += 1;
        break;
    case 9:
        if (!--self->ext.fireDemon.unk88) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    if (self->ext.prim != NULL) {
        prim = self->ext.prim;
        self->hitboxWidth = 12;
        self->hitboxHeight = (self->posY.i.hi - prim->y0) / 4;
        if (self->hitboxHeight & 0xF000) {
            self->hitboxHeight = 0;
        }
        self->hitboxOffY = -self->hitboxHeight;
    } else {
        self->hitboxState = 0;
    }
    if (self->step < 3) {
        self->hitboxOffY = 0;
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
    }
    if (self->ext.fireDemon.primA4 != NULL) {
        prim = self->ext.fireDemon.primA4;
        func_pspeu_0923D100(prim);
    }
    if (self->ext.fireDemon.unkA0) {
        for (xVar = self->ext.fireDemon.unk9C.xVars[0];
             xVar < self->ext.fireDemon.unk9C.xVars[1]; xVar += 8) {
            if (!(Random() & 3)) {
                explosion = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (explosion != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, explosion);
                    explosion->posX.i.hi += xVar;
                    explosion->posY.i.hi += (((Random() & 3) * 2) + 6);
                    explosion->params = 0x5F00;
                }
            }
        }
    }
}

void func_pspeu_0923E290(Primitive* prim) {
    switch (FD_NEXT->unk28) {
    case 0:
        prim->drawMode = DRAW_HIDE;
        FD_NEXT->unk30 -= 1;
        if (!FD_NEXT->unk30) {
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            FD_NEXT->unk28 = 1;
        }
        FD_NEXT->unk36 &= ~2;
        return;
    case 1:
        prim->drawMode = DRAW_DEFAULT;
        FD_NEXT->unk10 = 0x7000 - ((Random() & 7) << 0xD);
        FD_NEXT->unk14 = -0x40000;
        FD_NEXT->unk28 += 1;
        return;
    case 2:
        UnkPrimHelper(prim);
        if (FD_NEXT->unk14 < 0) {
            FD_NEXT->unk14 += 0x2000;
        } else {
            FD_NEXT->unk14 += 0x1000;
        }
        if (FD_NEXT->unk10 > 0) {
            FD_NEXT->unk1E += 0x80;
        } else {
            FD_NEXT->unk1E -= 0x80;
        }
    }
}

void func_pspeu_0923E448(Primitive* prim) {
    u16 sp1C[2];
    s16 sp18[2];

    switch (prim->g3) {
    case 0:
        prim->drawMode = DRAW_HIDE;
        prim->r3--;
        if (!prim->r3) {
            prim->g3 = 1;
        }
        break;
    case 1:
        prim->drawMode = DRAW_DEFAULT;
        LOW(prim->x2) = (0x8000 - (Random() << 8));
        LOW(prim->x3) = -0x40000;
        prim->g3 += 1;
        break;
    case 2:
        if (LOW(prim->x3) < 0) {
            LOW(sp1C) = (prim->x0 << 0x10) + prim->x1;
            LOW(prim->x3) += 0x2000;
        } else {
            LOW(sp1C) = (prim->x0 << 0x10) + prim->x1;
            LOW(prim->x3) += 0x400;
        }
        LOW(sp1C) += LOW(prim->x2);
        prim->x0 = sp1C[1];
        prim->x1 = sp1C[0];
        LOW(sp18) = (prim->y0 << 0x10) + prim->y1;
        LOW(sp18) += LOW(prim->x3);
        prim->y0 = sp18[1];
        prim->y1 = sp18[0];
        break;
    }
}

static RECT D_pspeu_09258990 = {0, 0x100, 0x80, 0x100};

void EntityUnkId20(Entity* self) {
    DRAWENV sp2C;
    s32 primIndex;
    DR_ENV* dr_env;
    Entity* otherEnt;
    Primitive* prim;
    Primitive* prim2;
    s16 xVar;
    s32 i;
    RECT sp24;

    sp24 = D_pspeu_09258990;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.func_800EDB58(0x11, 0x42);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env != NULL) {
                sp2C = g_CurrentBuffer->draw;
                sp2C.isbg = 1;
                sp2C.clip = sp24;
                sp2C.ofs[0] = 0;
                sp2C.ofs[1] = 0x100;
                SetDrawEnv(dr_env, &sp2C);
                prim->type = PRIM_ENV;
                prim->priority = 0x71;
                prim->drawMode = DRAW_DEFAULT;
            } else {
                DestroyEntity(self);
                return;
            }

            prim = prim->next;
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env != NULL) {
                prim->type = PRIM_ENV;
                prim->priority = 0x73;
                prim->drawMode = DRAW_UNK_800;
            } else {
                DestroyEntity(self);
                return;
            }

            prim = prim->next;
            for (i = 0; i < 3; i++) {
                prim->type = PRIM_GT4;
                prim->tpage = 0x110;
                if (i == 0) {
                    prim->u0 = prim->u2 = 0x7F;
                    prim->u1 = prim->u3 = 0;
                } else {
                    prim->u0 = prim->u2 = 0;
                    prim->u1 = prim->u3 = 0x7F;
                }
                prim->v0 = prim->v1 = 0x80;
                prim->v2 = prim->v3 = 0xFF;
                prim->y2 = prim->y3 = self->posY.i.hi;
                prim->priority = 0x76;
                prim->drawMode = DRAW_UNK02;
                prim = prim->next;
            }
            prim = &g_PrimBuf[primIndex] + 2;
            xVar = self->posX.i.hi;
            prim->x2 = xVar - 0x40;
            prim->x3 = xVar + 0x40;
            prim->x0 = prim->x2;
            prim->x1 = prim->x3;
            prim->y0 = prim->y1 = prim->y2 - 0xC0;
            prim = prim->next;
            xVar -= 8;
            prim->x2 = (xVar - 0x40);
            prim->x3 = (xVar + 0x40);
            prim->x0 = (xVar - 0x60);
            prim->x1 = (xVar + 0x40);
            prim->y0 = prim->y1 = prim->y2 - 0xA0;
            prim = prim->next;
            xVar += 8;
            prim->x2 = (xVar - 0x40);
            prim->x3 = (xVar + 0x40);
            prim->x0 = (xVar - 0x40);
            prim->x1 = (xVar + 0x60);
            prim->y0 = prim->y1 = prim->y2 - 0xA0;
            prim = prim->next;
            self->ext.prim = prim;
            for (i = 0; i < 6; i++) {
                UnkPolyFunc2(prim);
                prim->type = PRIM_GT4;
                prim->tpage = 0xA;
                prim->clut = 0x9B;
                prim->u0 = ((Random() & 3) * 0x10);
                prim->u1 = prim->u0 + (Random() & 7) + 8;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->v0 = (((Random() & 2) * 0x10) + 0x20);
                prim->v1 = prim->v0;
                prim->v2 = prim->v0 + (Random() & 7) + 8;
                prim->v3 = prim->v2;
                FD_NEXT->unk20 = prim->u1 - prim->u0 + 1;
                FD_NEXT->unk22 = prim->v2 - prim->v0 + 1;
                FD_NEXT->unk18 = 0x40;
                FD_NEXT->unkE = 0x100;
                prim->priority = 0x72;
                prim->drawMode = DRAW_HIDE;
                FD_NEXT->unk28 = 0;
                FD_NEXT->unk30 = i * 4;
                prim = prim->next;
                prim = prim->next;
            }

            for (i = 0, self->ext.fireDemon.prim80 = prim; prim != NULL;
                 prim = prim->next) {
                prim->u0 = 1;
                prim->v0 = 1;
                prim->x0 = 0x40;
                prim->y0 = 0x100;
                prim->r0 = 0x40;
                prim->g0 = 0x90;
                prim->b0 = 0x70;
                prim->priority = 0x72;
                prim->drawMode = DRAW_HIDE;
                prim->g3 = 0;
                prim->r3 = i / 2;
                i++;
                prim2 = prim;
            }
            self->ext.fireDemon.prim84 = prim2;
        } else {
            DestroyEntity(self);
            return;
        }
        self->ext.fireDemon.unk88 = 0;
        // fallthrough
    case 1:
        prim = self->ext.prim;
        for (i = 0; i < 6; i++) {
            func_pspeu_0923E290(prim);
            prim = prim->next;
            prim = prim->next;
        }
        while (prim != NULL) {
            func_pspeu_0923E448(prim);
            prim = prim->next;
        }
        prim = self->ext.fireDemon.prim84;
        prim->x0 = 0;
        prim->y0 = 0;
        prim->drawMode = DRAW_DEFAULT;
        if ((self->ext.fireDemon.unk88 % 8 == 0) &&
            (self->ext.fireDemon.unk88 < 32)) {
            otherEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (otherEnt != NULL) {
                CreateEntityFromCurrentEntity(E_UNK_22, otherEnt);
                otherEnt->params = 0x13;
                otherEnt->zPriority = 0x72;
                otherEnt->params += 0x7200;
                otherEnt->posX.i.hi = 0x40;
                otherEnt->posY.i.hi = 0x100;
            }
        }
        if (++self->ext.fireDemon.unk88 > 0xC0) {
            DestroyEntity(self);
        }
    }
}

static s16 D_pspeu_09258998[] = {0, 42, 0, 4, 8, -4, -16, 0};
static s16 D_pspeu_092589A8[] = {0, 42, 16, 0};

static RECT D_pspeu_092589B0 = {0, 0x100, 0x80, 0x100};

extern EInit D_us_80180A20;

typedef enum {
    FIRE_DEMON_INIT,
    FIRE_DEMON_1,
    FIRE_DEMON_2,
    FIRE_DEMON_3,
    FIRE_DEMON_4,
    FIRE_DEMON_5,
    FIRE_DEMON_DEAD = 0x10,
    FIRE_DEMON_TYPE14 = 0x14,
    FIRE_DEMON_TYPE15 = 0x15,
    FIRE_DEMON_ANIM_DEBUG = 0x20
} FireDemonSteps;

void EntityFireDemon(Entity* self) {
    Entity* other;
    s32 primIndex;
    Collider sp7C;
    DRAWENV sp38;
    RECT sp30;
    s16 xVar;
    s16 yVar;

    DR_ENV* dr_env;
    Primitive* prim;
    u8 var_s3;
    u8 var_s2;

    sp30 = D_pspeu_092589B0;
    FntPrint("step %x\n", self->step);
    FntPrint("step_s %x\n", self->step_s);
    var_s2 = 8;
    if ((self->flags & FLAG_DEAD) && ((self->step) < 0x10)) {
        PlaySfxPositional(SFX_UNK_RNZ0_711);
        self->hitboxState = 0;
        SetStep(FIRE_DEMON_DEAD);
    }
    switch (self->step) {
    case FIRE_DEMON_INIT:
        InitializeEntity(D_us_80180A20);
        self->hitboxState = 0;
        self->ext.fireDemon.zPriority = self->zPriority;
        self->zPriority = 0x6E;
        self->ext.fireDemon.palOffMax = 3;
        self->ext.fireDemon.palOffMin = 1;
        self->ext.fireDemon.pal_offset = 1;
        self->ext.fireDemon.palDirection = 1;
        self->ext.fireDemon.palTimer = 2;
        self->hitboxState = 3;
        self->zPriority = self->ext.fireDemon.zPriority;
        self->animCurFrame = 3;
        SetStep(FIRE_DEMON_3);
        if (self->params & 0x80) {
            self->palette = 0x815E;
            self->blendMode = BLEND_ADD | BLEND_TRANSP;
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0x60;
            self->ext.fireDemon.unk88 = 0x60;
            self->flags |= FLAG_UNK_00200000 | FLAG_UNK_2000;
            SetStep(FIRE_DEMON_TYPE15);
        }
        if (self->params & 0x100) {
            self->palette = 0x815E;
            self->animCurFrame = self->params & 0xFF;
            self->opacity = 0xC0;
            self->ext.fireDemon.unk88 = 0x20;
            self->zPriority -= 1;
            self->flags |= FLAG_UNK_00200000 | FLAG_UNK_2000;
            SetStep(FIRE_DEMON_TYPE14);
        }
        break;
    case FIRE_DEMON_1:
        self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
        if (GetDistanceToPlayerX() < 0x40) {
            self->step += 1;
        }
        break;
    case FIRE_DEMON_2:
        var_s2 = 2;
        switch (self->step_s) {
        case 0:
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0x30;
            self->velocityX = 0;
            if (self->facingLeft) {
                self->velocityX = -self->velocityX;
            }
            self->velocityY = FIX(-8.5);
            self->ext.fireDemon.accelerationY = 0;
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_FIRE_DEMON, self, other);
                other->params |= 0x80;
                other->ext.fireDemon.unk9C.otherEnt = self;
                self->ext.fireDemon.unk9C.otherEnt = other;
            } else {
                self->ext.fireDemon.unk9C.otherEnt = NULL;
            }
            self->step_s += 1;
            break;
        case 1:
            xVar = self->posX.i.hi;
            yVar = self->posY.i.hi - 0x20;
            g_api.CheckCollision(xVar, yVar, &sp7C, 0);
            if (!(sp7C.effects & EFFECT_SOLID)) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_UNK_20, self, other);
                    other->posY.i.hi -= 0x18;
                }
                self->step_s += 1;
            }
            /* fallthrough */
        case 2:
            MoveEntity();
            self->velocityY += self->ext.fireDemon.accelerationY;
            self->ext.fireDemon.accelerationY += FIX(1.0 / 16);
            if (self->velocityY > 0) {
                self->hitboxState = 3;
                self->animCurFrame = 0x13;
                self->step_s += 1;
            }
            break;
        case 3:
            if (UnkCollisionFunc3(D_pspeu_09258998) & 1) {
                self->ext.fireDemon.unk88 = 0x20;
                SetSubStep(4);
            } else {
                self->velocityY -= FIX(0.1875);
            }
            break;
        case 4:
            AnimateEntity(&D_pspeu_092588D0, self);
            if (!--self->ext.fireDemon.unk88) {
                SetSubStep(5);
            }
            break;
        case 5:
            AnimateEntity(&D_pspeu_09258898, self);
            self->opacity += 1;
            if (self->opacity > 128) {
                SetStep(FIRE_DEMON_3);
                self->drawFlags = ENTITY_DEFAULT;
            }
            break;
        }
        break;
    case FIRE_DEMON_3:
        var_s2 = 8;
        self->ext.fireDemon.palOffMax = 3;
        self->ext.fireDemon.palOffMin = 1;
        if (!self->step_s) {
            self->ext.fireDemon.unk88 = 0x80;
            self->step_s += 1;
        }
        AnimateEntity(&D_pspeu_092588B0, self);
        if (!--self->ext.fireDemon.unk88) {
            self->zPriority = self->ext.fireDemon.zPriority;
            self->ext.fireDemon.unk88 = 0x80;
            SetStep(FIRE_DEMON_4);
        }
        break;
    case FIRE_DEMON_4:
        var_s2 = 0x10;
        if (!self->step_s) {
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
            self->velocityX = FIX(-0.25);
            if (self->facingLeft) {
                self->velocityX = -self->velocityX;
            }
            self->step_s += 1;
        }
        if (!AnimateEntity(&D_pspeu_092588C0, self)) {
            PlaySfxPositional(SFX_STOMP_HARD_A);
            self->step_s = 0;
        }
        var_s3 = UnkCollisionFunc2(&D_pspeu_092589A8);
        if (var_s3 & 0x60) {
            self->velocityX = -self->velocityX;
        }
        if (self->ext.fireDemon.unk88) {
            self->ext.fireDemon.unk88--;
        } else if (GetDistanceToPlayerX() < 0x80) {
            SetStep(5);
        }
        break;
    case FIRE_DEMON_5:
        var_s2 = 8;
        self->ext.fireDemon.palOffMax = 6;
        self->ext.fireDemon.palOffMin = 3;
        switch (self->step_s) {
        case 0:
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
            self->ext.fireDemon.unk88 = 0x80;
            self->step_s += 1;
            break;
        case 1:
            AnimateEntity(&D_pspeu_092588D0, self);
            var_s2 = (self->ext.fireDemon.unk88 >> 4);
            if ((var_s2) < 2) {
                var_s2 = 2;
            }
            if ((self->ext.fireDemon.unk88 % ((var_s2) * 2)) == 0) {
                PlaySfxPositional(SFX_FIRE_DEMON_ATTACK_CHARGE);
            }
            if (!--self->ext.fireDemon.unk88) {
                self->ext.fireDemon.unk88 = 0x20;
                SetSubStep(2);
            }
            break;
        case 2:
            var_s2 = 1;
            AnimateEntity(&D_pspeu_092588D8, self);
            if (!--self->ext.fireDemon.unk88) {
                other = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_UNK_21, self, other);
                    if (self->facingLeft) {
                        other->posX.i.hi += 0x10;
                    } else {
                        other->posX.i.hi -= 0x10;
                    }
                    other->posY.i.hi -= 0x18;
                    other->facingLeft = self->facingLeft;
                }
                PlaySfxPositional(SFX_EXPLODE_SMALL);
                SetSubStep(3);
            }
            break;
        case 3:
            var_s2 = 1;
            self->ext.fireDemon.palOffMin = 6;
            self->palette = 0x220;
            if (!AnimateEntity(&D_pspeu_092588E0, self)) {
                SetStep(3);
            }
            break;
        }
        break;
    case FIRE_DEMON_DEAD:
        self->ext.fireDemon.palTimer = 2;
        switch (self->step_s) {
        case 0:
            self->drawFlags |= ENTITY_OPACITY;
            self->opacity = 0x80;
            self->step_s += 1;
            break;
        case 1:
            self->opacity -= 2;
            if (!self->opacity) {
                self->step_s += 1;
            }
            break;
        case 2:
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env == NULL) {
                DestroyEntity(self);
                return;
            }
            prim->type = PRIM_ENV;
            prim->priority = 0xD3;
            prim->drawMode = DRAW_DEFAULT;
            sp38 = g_CurrentBuffer->draw;
            sp38.isbg = 1;
            sp38.clip = sp30;
            sp38.r0 = sp38.g0 = sp38.b0 = 0;
            sp38.ofs[0] = 0;
            sp38.ofs[1] = 0x100;
            SetDrawEnv(dr_env, &sp38);
            prim = prim->next;
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env == NULL) {
                DestroyEntity(self);
                return;
            }
            prim->type = PRIM_ENV;
            prim->priority = 0xD6;
            prim->drawMode = DRAW_UNK_800;
            prim = prim->next;
            self->ext.prim = prim;
            prim->type = PRIM_GT4;
            prim->tpage = 0x110;

            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x4F;
            prim->v0 = prim->v1 = 0x80;
            prim->v2 = prim->v3 = 0xFF;
            prim->x0 = prim->x2 = self->posX.i.hi - 0x28;
            prim->x1 = prim->x3 = prim->x0 + 0x4F;
            prim->y2 = prim->y3 = self->posY.i.hi + 0x2A;
            prim->y0 = prim->y1 = prim->y2 - 0x7F;
            prim->priority = self->zPriority;
            prim->drawMode =
                DRAW_UNK_40 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_FIRE_DEMON, self, other);
                other->params |= 0x100;
                other->params |= self->animCurFrame;
                other->facingLeft = self->facingLeft;
            }
            self->drawFlags = ENTITY_DEFAULT;
            self->palette = 0x815E;
            self->zPriority = 0xD4;
            self->posX.i.hi = 0x28;
            self->posY.i.hi = 0xD5;
            self->flags &= ~FLAG_POS_CAMERA_LOCKED;
            self->ext.fireDemon.unk88 = 0x20;
            self->ext.fireDemon.unk98 = 0xC0;
            self->step_s += 1;
            break;
        case 3:
            var_s3 = 0;
            self->palette = 0x815E;
            if (self->ext.fireDemon.unk88) {
                if (--self->ext.fireDemon.unk88 % 8 == 0) {
                    var_s3 = 1;
                }
            } else {
                if (--self->ext.fireDemon.unk98) {
                    // Hello, yes, I would like one dose of whatever the SOTN
                    // devs were smoking when they wrote this math
                    if ((self->ext.fireDemon.unk98 %
                         (self->ext.fireDemon.unk98 / 32 + 1)) == 0) {
                        var_s3 = 1;
                    }
                } else {
                    PlaySfxPositional(SFX_EXPLODE_A);
                    self->step_s += 1;
                }
            }
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_EXPLODE_FAST_A);
            }
            if (var_s3) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromCurrentEntity(E_UNK_22, other);
                    other->params = 0x22;
                    other->params += 0xD500;
                    other->posX.i.hi =
                        self->posX.i.hi + ((Random() & 3) * 8) - 12;
                    other->posY.i.hi = 0x100 - ((Random() & 7) * 0x10);
                }
            }
            break;
        case 4:
            prim = self->ext.prim;
            prim->v2 = prim->v3--;
            prim->y2 = prim->y3--;
            if ((prim->v2) < (prim->v0)) {
                prim->drawMode = DRAW_HIDE;
                self->ext.fireDemon.unk88 = 0x40;
                self->step_s += 1;
            }
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromCurrentEntity(E_UNK_22, other);
                other->params = 0x20;
                other->params += 0xD500;
                other->posX.i.hi =
                    (self->posX.i.hi + ((Random() & 3) * 8)) - 0xC;
                other->posY.i.hi = (prim->v2) - 4;
            }
            break;
        case 5:
            self->animCurFrame = 0;
            if (!--self->ext.fireDemon.unk88) {
                DestroyEntity(self);
                return;
            }
            break;
        }
        break;
    case FIRE_DEMON_TYPE14:
        self->palette = 0x815E;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->drawFlags = ENTITY_OPACITY;
        self->hitboxState = 0;
        self->ext.fireDemon.palTimer = 7;
        if (self->ext.fireDemon.unk88) {
            self->ext.fireDemon.unk88--;
            break;
        }
        self->opacity--;
        if (!self->opacity) {
            DestroyEntity(self);
            return;
        }
        break;
    case FIRE_DEMON_TYPE15:
        self->palette = 0x815E;
        self->hitboxState = 0;
        self->ext.fireDemon.palTimer = 7;
        other = self->ext.fireDemon.unk9C.otherEnt;
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi;
        self->facingLeft = other->facingLeft;
        self->zPriority = ((other->zPriority) + 1);
        self->animCurFrame = other->animCurFrame;
        self->opacity = (0x80 - other->opacity) / 3;
        if (!self->opacity) {
            DestroyEntity(self);
            return;
        }
        break;
    case FIRE_DEMON_ANIM_DEBUG:
#include "../../pad2_anim_debug.h"
    }
    if (!--self->ext.fireDemon.palTimer) {
        self->ext.fireDemon.palTimer = var_s2;

        // Set the palette to an offsetted value.
        self->palette = (self->ext.fireDemon.pal_offset + 0x21D);
        // Increase or decrease by 1.
        self->ext.fireDemon.pal_offset += self->ext.fireDemon.palDirection;
        // When we reach the max or min, flip direction.
        if (self->ext.fireDemon.pal_offset > self->ext.fireDemon.palOffMax) {
            self->ext.fireDemon.palDirection = -1;
        }
        if (self->ext.fireDemon.pal_offset < self->ext.fireDemon.palOffMin) {
            self->ext.fireDemon.palDirection = 1;
        }
    }
    if (self->animCurFrame < 0xD) {
        self->hitboxOffX = -6;
        self->hitboxOffY = -1;
        self->hitboxWidth = 8;
        self->hitboxHeight = 0x28;
    } else {
        self->hitboxOffX = -1;
        self->hitboxOffY = -1;
        self->hitboxWidth = 0xB;
        self->hitboxHeight = 0x28;
    }
}
