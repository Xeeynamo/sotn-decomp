// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno1.h"

static s16 g_Rno1DebrisCollisionSensors[] = {
    0, 0, 0, 4, 0, -4, 0, 0,
};

static s32 g_Rno1DebrisVelocities[][2] = {
    {FIX(1), FIX(-3)}, {FIX(1.5), FIX(-1.5)},  {FIX(0.75), FIX(-2.25)},
    {FIX(2), FIX(-1)}, {FIX(0.5), FIX(-0.25)}, {FIX(1), FIX(-2)},
};

static s32 g_Rno1WallDebrisVelocities[][2] = {
    {0, 0x6000},      {0x2000, 0x4000}, {0x4000, 0x8000},
    {0x8000, 0x6000}, {0xC000, 0x4000},
};

static s16 g_Rno1WallDebrisSizes[] = {8, 12, 4, 14, 6, 0};
static s16 g_Rno1WallDebrisRotations[] = {
    0x180, 0x100, 0x200, 0xC0, 0x1C0, 0,
};

static AnimateEntityFrame g_Rno1DebrisAnim[] = {
    {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {-1, 0},
};

INCLUDE_ASM("st/rno1/nonmatchings/unk_26178", EntityBreakable);

extern EInit g_EInitInteractable;
extern EInit g_EInitParticle;

void EntityBreakableDebris(Entity* self) {
    Collider collider;
    Entity* explosion;
    Primitive* prim;
    s32 primIndex;
    s16 posX, posY;

    switch (self->step) {
    case 0:
        if (self->params & 0x100) {
            InitializeEntity(g_EInitInteractable);
            self->animSet = ANIMSET_OVL(10);
            self->unk5A = 0x5B;
            self->palette = 0x22C;
            self->animCurFrame = 0x15;
            self->zPriority = 0x6A;
            self->step = 0x100;
            return;
        }

        InitializeEntity(g_EInitParticle);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        UnkPolyFunc2(prim);
        prim->tpage = 0x16;
        prim->clut = 0x230;
        prim->u0 = prim->u2 = 0x98;
        prim->u1 = prim->u3 = 0xA7;

#ifdef VERSION_PSP
        posY = 0x84;
#else
        posY = -0x7C;
#endif
        posY += self->params * 16;
        prim->v0 = prim->v1 = posY;
        prim->v2 = prim->v3 = posY + 15;
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        LOH(prim->next->r2) = 0x10;
        LOH(prim->next->b2) = 0x10;
        prim->next->b3 = 0x80;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_UNK02;
        self->velocityX = ((Random() & 7) << 12) + FIX(0.5);
        if (!self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        self->velocityY = ((Random() & 7) << 12) - FIX(0.5);

    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        prim = self->ext.prim;
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        if (self->facingLeft) {
            LOH(prim->next->tpage) += 0x10;
        } else {
            LOH(prim->next->tpage) -= 0x10;
        }
        UnkPrimHelper(prim);

        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 8;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            g_api.PlaySfx(SFX_QUICK_STUTTER_EXPLODE_B);
            explosion = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (explosion != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, explosion);
                explosion->params = 0;
            }
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("st/rno1/nonmatchings/unk_26178", RNO1_DebugShowWaitInfo);

INCLUDE_ASM("st/rno1/nonmatchings/unk_26178", RNO1_DebugInputWait);

INCLUDE_ASM("st/rno1/nonmatchings/unk_26178", func_us_801A68AC);

INCLUDE_ASM("st/rno1/nonmatchings/unk_26178", func_us_801A700C);

void func_us_801B7CC4_from_no1(Entity* self) {
    if (!self->step) {
        g_api.PlaySfx(SET_RELEASE_RATE_HIGH_20_21);
        self->step++;
    }
    DestroyEntity(self);
}

void func_us_801B8F50_from_no1(Entity* self) {
    extern u16 D_us_8018073C;
    extern u8 D_us_80180BF8[];
    extern void* D_us_80180C04[];
    void* anim;

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_8018073C);
        self->animCurFrame = D_us_80180BF8[self->params];
        self->zPriority = 0x6A;
        break;

    case 1:
        if (g_CastleFlags[NO1_ELEVATOR_ACTIVATED]) {
            self->step += 1;
        }
        break;

    case 2:
        anim = D_us_80180C04[self->params];
        AnimateEntity(anim, self);
        break;
    }
}

INCLUDE_ASM("st/rno1/nonmatchings/unk_26178", func_us_801BE880_from_no1);

extern u16 D_us_80180754;

void func_us_801BEB54_from_no1(Entity* self) {
    Entity* tempEntity;
    s32 i;

    if (self->hitParams) {
        PlaySfxPositional(SFX_EXPLODE_FAST_B);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180754);
        self->hitPoints = 0x18;
        self->hitboxWidth = 0x10;
        self->hitboxHeight = 0xC;
        self->hitboxState = 2;
        self->ext.segmentedBreakableWall.hitPoints = self->hitPoints;
        self->hitboxOffY = 0xC;
        break;

    case 1:
        if (self->hitPoints ^ self->ext.segmentedBreakableWall.hitPoints) {
            (self - self->params)->ext.segmentedBreakableWall.damageTaken +=
                self->ext.segmentedBreakableWall.hitPoints - self->hitPoints;
            self->ext.segmentedBreakableWall.hitPoints = self->hitPoints;
        }
        if (self->flags & FLAG_DEAD) {
            (self - self->params)->ext.segmentedBreakableWall.pieceBroken |=
                self->params;
            self->step++;
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                tempEntity->posY.i.hi += 8;
                tempEntity->params = 0x13;
            }

            for (i = 0; i < 3; i++) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, tempEntity);
                    tempEntity->posX.i.hi -= (i * 0x10) - 0x10;
                    tempEntity->params = 0x10;
                }
            }

            for (i = 0; i < 5; i++) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_ID(UNK_29), self, tempEntity);
                    tempEntity->posX.i.hi -= (i * 8) - 0x10 + (Random() & 3);
                    tempEntity->posY.i.hi += (Random() & 7) + 0x14;
                    tempEntity->params = i;
                }
            }
            self->step_s++;
            break;
        }
        break;
    }
}

void func_us_801BEE00_from_no1(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = 8;
        self->animCurFrame = 1;
        self->palette = PAL_FLAG(0x4);
        return;

    case 1:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;
#ifdef VERSION_PSP
            UnkPolyFunc2(prim);
#else
            UnkPolyFunc2(prim, primIndex);
#endif

            prim->tpage = 0xE;
            prim->clut = 2;
            prim->u0 = 0x70;
            prim->u1 = 0x78;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0xF6;
            prim->v1 = prim->v0;
            prim->v2 = 0xFD;
            prim->v3 = prim->v2;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK02;

            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            *(u16*)&prim->next->r2 = 4;
            *(u16*)&prim->next->b2 = 4;
            prim->next->b3 = 0x80;
        } else {
            DestroyEntity(self);
            return;
        }

        self->velocityX = g_Rno1DebrisVelocities[self->params][0];
        self->velocityY = g_Rno1DebrisVelocities[self->params][1];
        self->step++;
        return;

    case 2:
        prim = self->ext.prim;
        LOH(prim->next->tpage) += 0x180;
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        UnkPrimHelper(prim);
        if (AnimateEntity(g_Rno1DebrisAnim, self) == 0) {
            self->animCurFrame = 0;
        }
        if (UnkCollisionFunc5(g_Rno1DebrisCollisionSensors) != 0) {
            DestroyEntity(self);
            return;
        }
        self->velocityY -= FIX(0.0625);
        return;
    }
}

void func_us_801BF074_from_no1(Entity* self) {
    Collider collider;
    Entity* tempEntity;
    Primitive* prim;
    s32 primIndex;
    s16 posX, posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = 8;
        self->animCurFrame = 1;
        self->palette = PAL_FLAG(4);
        break;

    case 1:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.segmentedBreakableWall.prim = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 0xE;
            prim->clut = 2;
            prim->u0 = 0x70;
            prim->u1 = 0x78;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0xF6;
            prim->v1 = prim->v0;
            prim->v2 = 0xFD;
            prim->v3 = prim->v2;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK02;

            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            LOH(prim->next->r2) = g_Rno1WallDebrisSizes[self->params];
            LOH(prim->next->b2) = LOH(prim->next->r2);
            prim->next->b3 = 0x80;
        } else {
            DestroyEntity(self);
            return;
        }

        self->velocityX = g_Rno1WallDebrisVelocities[self->params][0];
        self->velocityY = g_Rno1WallDebrisVelocities[self->params][1];
        self->step++;
        break;

    case 2:
        prim = self->ext.segmentedBreakableWall.prim;
        LOH(prim->next->tpage) += g_Rno1WallDebrisRotations[self->params];
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        UnkPrimHelper(prim);
        if (!AnimateEntity(g_Rno1DebrisAnim, self)) {
            self->animCurFrame = 0;
        }
        MoveEntity();
        self->velocityY += FIX(0.125);
        if (self->velocityY < 0) {
            break;
        }

        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY += (LOH(prim->next->r2) / 2) - 2;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk18;
            self->velocityX += FIX(0.25);
            self->velocityY = -self->velocityY / 2;
            if (self->velocityY > FIX(-0.25)) {
                if (LOH(prim->next->r2) > 6) {
                    tempEntity =
                        AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (tempEntity != NULL) {
                        CreateEntityFromEntity(
                            E_INTENSE_EXPLOSION, self, tempEntity);
                        tempEntity->params = 0x10;
                    }
                }
                DestroyEntity(self);
                return;
            }
        }
        break;
    }
}

INCLUDE_ASM("st/rno1/nonmatchings/unk_26178", func_us_801A86A8);
