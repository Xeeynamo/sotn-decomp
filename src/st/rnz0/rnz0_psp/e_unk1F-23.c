// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rnz0.h"

extern u16 g_EInitInteractable;

static s32 D_us_80181A68[] = {
    FIX(-1), FIX(-1.5), FIX(-1.5), FIX(-1.5), FIX(-3)};
static u8 D_us_80181A7C[] = {1, 9, 21, 43};
static u16 D_us_80181A80[] = {16, 24, 42, 46};

void EntityUnkId22(Entity* self) {
    if (!self->step) {
        InitializeEntity(&g_EInitInteractable);
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

typedef struct weirdPrim {
    struct weirdPrim* next;
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
} weirdPrim;

#define NEXT_DUDE ((weirdPrim*)prim->next)

void func_pspeu_0923D100(Primitive* prim) {
    switch (NEXT_DUDE->unk28) {
    case 0:
        UnkPolyFunc2(prim);
        prim->tpage = 0x1A;
        prim->clut = 0x19D;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;
        NEXT_DUDE->unk18 = g_CurrentEntity->posX.i.hi;
        NEXT_DUDE->unkE = g_CurrentEntity->posY.i.hi;
        NEXT_DUDE->unk20 = 0x40;
        NEXT_DUDE->unk22 = 0x40;
        NEXT_DUDE->unk2E = 0x40;
        prim->p3 |= 0x10;
        NEXT_DUDE->unk24 = 0;
        NEXT_DUDE->unk26 = NEXT_DUDE->unk24;
        prim->priority = g_CurrentEntity->zPriority + 3;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        NEXT_DUDE->unk28++;
        /* fallthrough */
    case 1:
        NEXT_DUDE->unk24 += 0x300;
        NEXT_DUDE->unk26 = NEXT_DUDE->unk24;
        if (NEXT_DUDE->unk24 > 0x1800) {
            prim->clut = 0x19C;
            NEXT_DUDE->unk2E = 0x28;
            NEXT_DUDE->unk28++;
        }
        break;
    case 2:
        NEXT_DUDE->unk24 += 0x180;
        NEXT_DUDE->unk26 = NEXT_DUDE->unk24;
        if (NEXT_DUDE->unk24 > 0x2000) {
            NEXT_DUDE->unk28++;
        }
        break;
    case 3:
        if (PrimDecreaseBrightness(prim, 6) == 0) {
            prim->drawMode = DRAW_HIDE;
            NEXT_DUDE->unk28++;
        }
        break;
    }
    if (NEXT_DUDE->unk28 < 3) {
        UnkPrimHelper(prim);
    }
}

extern s32 D_pspeu_09258910;
extern s32 D_pspeu_09258928;
extern s32 D_pspeu_09258948;
extern s32 D_pspeu_09258970;
extern s32 D_pspeu_09258980;

extern EInit D_pspeu_09260720;

void func_us_801BA21C(Entity* self) {
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
        InitializeEntity(D_pspeu_09260720);
        self->animCurFrame = 0;
        angle = 0x600;
        if (self->facingLeft) {
            angle = -0x600;
        }
        self->velocityX = rsin(angle) * -0x40;
        self->velocityY = rcos(angle) * -0x40;
        self->ext.fireDemon.unk94 = angle;
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
        NEXT_DUDE->unk1E = -angle;
        NEXT_DUDE->unk20 = 0x18;
        NEXT_DUDE->unk22 = 0x40;
        NEXT_DUDE->unk18 = self->posX.i.hi;
        NEXT_DUDE->unkE = self->posY.i.hi;
        NEXT_DUDE->unk10 = (-rsin(angle) * 0x38);
        NEXT_DUDE->unk14 = (-rcos(angle) * 0x38);
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;
        prim = prim->next;
        UnkPolyFunc2(prim);
        NEXT_DUDE->unk1E = angle;
        prim->tpage = 0x1A;
        prim->clut = 0x170;
        NEXT_DUDE->unk1E = (0x800 - angle);
        NEXT_DUDE->unk20 = 0x10;
        NEXT_DUDE->unk22 = 0x18;
        NEXT_DUDE->unk18 = self->posX.i.hi;
        NEXT_DUDE->unkE = self->posY.i.hi;
        NEXT_DUDE->unk10 = (rsin(angle) * -0x40);
        NEXT_DUDE->unk14 = (rcos(angle) * -0x40);
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
            NEXT_DUDE->unk22 ^= 8;
        }
        UpdateAnimation(&D_pspeu_09258910, prim);
        UnkPrimHelper(prim);
        prim = prim->next;
        prim = prim->next;
        if ((self->ext.fireDemon.unk88 % 3) == 0) {
            NEXT_DUDE->unk22++;
        }

        if (((self->ext.fireDemon.unk88 % 4) == 0) && (NEXT_DUDE->unk20 > 8)) {
            NEXT_DUDE->unk20--;
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
        NEXT_DUDE->unk18 = self->posX.i.hi;
        NEXT_DUDE->unkE = self->posY.i.hi - 8;
        NEXT_DUDE->unk10 = 0x30000;
        NEXT_DUDE->unk14 = 0;
        NEXT_DUDE->unk1E = 0;
        NEXT_DUDE->unk20 = 0x20;
        NEXT_DUDE->unk22 = 0x10;
        NEXT_DUDE->unk30 = NEXT_DUDE->unk22 / 2;
        prim = prim->next;
        prim = prim->next;
        prim->p2 = 0;
        prim->p1 = 0;
        NEXT_DUDE->unk18 = self->posX.i.hi;
        NEXT_DUDE->unkE = self->posY.i.hi - 8;
        NEXT_DUDE->unk10 = 0xFFFD0000;
        NEXT_DUDE->unk14 = 0;
        NEXT_DUDE->unk1E = 0;
        NEXT_DUDE->unk20 = 0x20;
        NEXT_DUDE->unk22 = 0x10;
        NEXT_DUDE->unk30 = NEXT_DUDE->unk22 / 2;
        prim = prim->next;
        prim = prim->next;
        self->ext.fireDemon.primA4 = prim;
        self->step += 1;
        /* fallthrough */
    case 3:
        prim = self->ext.prim;
        UnkPrimHelper(prim);
        UpdateAnimation(&D_pspeu_09258948, prim);
        NEXT_DUDE->unk10 -= 0x3000;
        NEXT_DUDE->unk30 += 2;
        prim->x0 = prim->x2 = self->posX.i.hi - 0x10;
        prim->y1 = (u32)self->posY.i.hi - NEXT_DUDE->unk30;
        prim = prim->next;
        prim = prim->next;
        UnkPrimHelper(prim);
        UpdateAnimation(&D_pspeu_09258948, prim);
        NEXT_DUDE->unk10 += 0x3000;
        NEXT_DUDE->unk30 += 2;
        prim->x1 = prim->x3 = self->posX.i.hi + 0x10;
        prim->y0 = (u32)self->posY.i.hi - NEXT_DUDE->unk30;
        if (NEXT_DUDE->unk10 == 0) {
            self->step = 4;
        }
        break;
    case 4:
        prim = self->ext.prim;
        self->ext.fireDemon.unk9E = (prim->x3 - self->posX.i.hi) - 0x10;
        prim->p1 = 0;
        prim->p2 = 0;
        prim = prim->next;
        prim = prim->next;
        self->ext.fireDemon.unk9C = ((prim->x2 - self->posX.i.hi) + 0x10);
        self->ext.fireDemon.unkA0 = 1;
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
        NEXT_DUDE->unkE = prim->y0;
        NEXT_DUDE->unk14 = 0;
        prim->p1 = 2;
        prim->p2 = 0;
        prim = prim->next;
        prim = prim->next;
        NEXT_DUDE->unkE = prim->y0;
        NEXT_DUDE->unk14 = 0;
        prim->p1 = 1;
        prim->p2 = 0;
        self->step += 1;
        break;
    case 7:
        prim = self->ext.prim;
        UpdateAnimation(&D_pspeu_09258980, prim);
        prim->y0 = NEXT_DUDE->unkE;
        LOW(NEXT_DUDE->unkC) += NEXT_DUDE->unk14;
        NEXT_DUDE->unk14 += 0x3000;
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
        for (xVar = self->ext.fireDemon.unk9C; xVar < self->ext.fireDemon.unk9E;
             xVar += 8) {
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
    switch (NEXT_DUDE->unk28) {
    case 0:
        prim->drawMode = DRAW_HIDE;
        NEXT_DUDE->unk30 -= 1;
        if (!NEXT_DUDE->unk30) {
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            NEXT_DUDE->unk28 = 1;
        }
        NEXT_DUDE->unk36 &= ~2;
        return;
    case 1:
        prim->drawMode = DRAW_DEFAULT;
        NEXT_DUDE->unk10 = 0x7000 - ((Random() & 7) << 0xD);
        NEXT_DUDE->unk14 = -0x40000;
        NEXT_DUDE->unk28 += 1;
        return;
    case 2:
        UnkPrimHelper(prim);
        if (NEXT_DUDE->unk14 < 0) {
            NEXT_DUDE->unk14 += 0x2000;
        } else {
            NEXT_DUDE->unk14 += 0x1000;
        }
        if (NEXT_DUDE->unk10 > 0) {
            NEXT_DUDE->unk1E += 0x80;
        } else {
            NEXT_DUDE->unk1E -= 0x80;
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

extern RECT D_pspeu_09258990;

void func_us_801BB000(Entity* self) {
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
        InitializeEntity(&g_EInitInteractable);
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
                NEXT_DUDE->unk20 = prim->u1 - prim->u0 + 1;
                NEXT_DUDE->unk22 = prim->v2 - prim->v0 + 1;
                NEXT_DUDE->unk18 = 0x40;
                NEXT_DUDE->unkE = 0x100;
                prim->priority = 0x72;
                prim->drawMode = DRAW_HIDE;
                NEXT_DUDE->unk28 = 0;
                NEXT_DUDE->unk30 = i * 4;
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

INCLUDE_ASM("st/rnz0_psp/nonmatchings/rnz0_psp/e_unk1F-23", func_us_801BB5D8);
