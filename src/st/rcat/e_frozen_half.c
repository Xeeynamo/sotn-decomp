// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcat.h"
#include <scratchpad.h>

extern EInit g_EInitFrozenHalf;
extern EInit D_us_8018103C;
extern EInit D_us_80181048;
extern EInit D_us_80181054;
extern EInit D_us_80181060;
extern EInit g_EInitParticle;

static u8 D_us_80182080[] = {
    0x07, 0x02, 0x07, 0x03, 0x07, 0x04, 0x07, 0x05, 0x07, 0x06,
    0x07, 0x07, 0x07, 0x08, 0x30, 0x01, 0xFF, 0x00, 0x00, 0x00,
};
static u8 D_us_80182094[] = {
    0x0A, 0x0A, 0x04, 0x06, 0x04, 0x07, 0x04, 0x08, 0x01, 0x01, 0xFF, 0x00,
};
static u8 D_us_801820A0[] = {
    0x05, 0x0A, 0x02, 0x06, 0x02, 0x07, 0x02, 0x08, 0x01, 0x01, 0xFF, 0x00,
};
static u8 D_us_801820AC[] = {
    0x06, 0x02, 0x05, 0x04, 0x04, 0x05, 0x04, 0x06,
    0x04, 0x07, 0x04, 0x08, 0x01, 0x01, 0xFF, 0x00,
};
static u8 D_us_801820BC[] = {
    0x03, 0x02, 0x03, 0x04, 0x02, 0x05, 0x02, 0x06,
    0x02, 0x07, 0x02, 0x08, 0x01, 0x01, 0xFF, 0x00,
};
static u8 D_us_801820CC[] = {
    0x06, 0x0F, 0x08, 0x10, 0x07, 0x11, 0x04, 0x12,
    0x04, 0x13, 0x04, 0x14, 0x01, 0x15, 0xFF, 0x00,
};
static u8 D_us_801820DC[] = {
    0x01, 0x15, 0x03, 0x14, 0x03, 0x13, 0x03, 0x12,
    0x03, 0x11, 0x01, 0x01, 0xFF, 0x00, 0x00, 0x00,
};

static u8 D_us_801820EC[] = {
    0x01, 0x18, 0x01, 0x19, 0x01, 0x1A, 0x01, 0x1B, 0x00, 0x00, 0x00, 0x00,
};
static u8 D_us_801820F8[] = {
    0x03, 0x1A, 0x01, 0x19, 0x01, 0x18, 0xFF, 0x00,
};
static u8 D_us_80182100[] = {
    0x01, 0x1C, 0x01, 0x1D, 0x00, 0x00, 0x00, 0x00,
};
static u8 D_us_80182108[] = {
    0x01, 0x1E, 0x01, 0x1F, 0x00, 0x00, 0x00, 0x00,
};
static s16 D_us_80182110[] = {
    0x0020, 0x00A0, 0x0030, 0x00C0, 0x0050, 0x0068, 0x00D0, 0x0040,
};
static SVECTOR D_us_80182120 = {0xFFC0, 0x0000, 0xFFC0, 0x0000};
static SVECTOR D_us_80182128 = {0x0040, 0x0000, 0xFFC0, 0x0000};
static SVECTOR D_us_80182130 = {0xFFC0, 0x0000, 0x0040, 0x0000};
static SVECTOR D_us_80182138 = {0x0040, 0x0000, 0x0040, 0x0000};

void func_us_801BEFD8(Entity* self) {
    Primitive* prim;
    s32 i;
    s32 j;
    s32 posX;
    s32 posY;
    Entity* entity;
    s32 animResult;
    s16 var_s7;
    s32 primIndex;

    if (g_Timer & 1) {
        self->palette = 0x200;
    } else {
        self->palette = 0x201;
    }

    FntPrint("step %x\n", self->step);
    FntPrint("step_s %x\n", self->step_s);
    if (self->step & 1 && self->hitFlags & 3) {
        SetStep(10);
    }

    if (self->flags & FLAG_DEAD && self->step < 0x10) {
        PlaySfxPositional(SFX_FROZEN_HALF_DEATH);
        if (self->ext.frozenHalf.entity != NULL) {
            entity = self->ext.frozenHalf.entity;
            DestroyEntity(entity);
        }
        SetStep(16);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFrozenHalf);
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        entity = self + 1;
        CreateEntityFromEntity(E_UNK_23, self, entity);
        SetStep(3);
        break;
    case 3:
        self->facingLeft = GetSideToPlayer() & 1;
        if (GetDistanceToPlayerX() < 0x60) {
            SetStep(5);
        }
        break;
    case 5:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
        }

        MoveEntity();
        self->facingLeft = GetSideToPlayer() & 1;
        var_s7 = self->ext.frozenHalf.unk82 += 0x20;
        var_s7 &= 0xFFF;
        self->velocityY = rsin(var_s7) * 0x10;
        if (self->ext.frozenHalf.unk87) {
            self->velocityY += FIX(0.125);
        } else {
            self->velocityY -= FIX(0.125);
        }

        AnimateEntity(D_us_80182080, self);
        if (var_s7 > 0x600) {
            self->pose = 0;
            self->poseTimer = 0;
            self->animCurFrame = 1;
        }

        if (!(self->ext.frozenHalf.unk82 & 0x3FF)) {
            entity = &PLAYER;
            if (GetDistanceToPlayerX() < 0x68 &&
                entity->facingLeft != self->facingLeft) {
                self->ext.frozenHalf.unk84 = 1;
                SetStep(7);
            }

            if (GetDistanceToPlayerX() > 0x50 &&
                entity->facingLeft == self->facingLeft) {
                self->ext.frozenHalf.unk84 = 0;
                SetStep(7);
            }
        }
        if (!(self->ext.frozenHalf.unk82 & 0xFFF)) {
            if (self->posY.i.hi < 0x60) {
                self->ext.frozenHalf.unk87 = 1;
            } else {
                self->ext.frozenHalf.unk87 = 0;
            }
        }
        break;
    case 7:
        switch (self->step_s) {
        case 0:
            self->velocityY = 0;
            self->ext.frozenHalf.unk80 = 0x40;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->facingLeft = GetSideToPlayer() & 1;
            if (self->ext.frozenHalf.unk84) {
                self->animCurFrame = 0xB;
            } else {
                self->animCurFrame = 9;
            }

            if (self->facingLeft ^ self->ext.frozenHalf.unk84) {
                self->velocityX -= FIX(0.0625);
                if (self->velocityX <= FIX(-1.0)) {
                    self->velocityX = FIX(-1.0);
                }
            } else {
                self->velocityX += FIX(0.0625);
                if (self->velocityX >= FIX(1.0)) {
                    self->velocityX = FIX(1.0);
                }
            }

            if (!self->ext.frozenHalf.unk84) {
                if (GetDistanceToPlayerX() < 0x48) {
                    SetSubStep(2);
                }
            }

            if (self->ext.frozenHalf.unk84 && GetDistanceToPlayerX() > 0x70) {
                SetSubStep(2);
            }

            if (!--self->ext.frozenHalf.unk80) {
                SetSubStep(3);
            }
            break;
        case 2:
            MoveEntity();
            self->velocityX -= self->velocityX / 8;

            if (self->ext.frozenHalf.unk84) {
                animResult = AnimateEntity(D_us_801820BC, self);
            } else {
                animResult = AnimateEntity(D_us_801820A0, self);
            }

            if (!animResult) {
                self->ext.frozenHalf.unk84 ^= 1;
                SetSubStep(1);
            }

            break;
        case 3:
            MoveEntity();
            self->velocityX -= self->velocityX / 16;

            if (self->ext.frozenHalf.unk84) {
                animResult = AnimateEntity(D_us_801820AC, self);
            } else {
                animResult = AnimateEntity(D_us_80182094, self);
            }

            if (!animResult) {
                if (self->ext.frozenHalf.unk85) {
                    if (self->posX.i.hi & 0xFF00) {
                        SetStep(7);
                    } else {
                        SetStep(8);
                    }
                } else {
                    SetStep(6);
                }
                self->ext.frozenHalf.unk85 ^= 1;
            }
            break;
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                PlaySfxPositional(SFX_GLASS_SHARDS);
                CreateEntityFromEntity(E_UNK_24, self, entity);
                if (self->facingLeft) {
                    entity->posX.i.hi += 0x10;
                } else {
                    entity->posX.i.hi -= 0x10;
                }
                entity->posY.i.hi -= 0x10;
                entity->facingLeft = self->facingLeft;
                self->ext.frozenHalf.entity = entity;
            } else {
                self->ext.frozenHalf.entity = NULL;
                SetStep(5);
                break;
            }

            self->animCurFrame = 0xD;
            self->step_s++;
            break;
        case 1:
            entity = self->ext.frozenHalf.entity;
            if (entity->flags & FLAG_DEAD) {
                self->ext.frozenHalf.entity = NULL;
                SetStep(5);
            } else if (!(entity->drawFlags & ENTITY_SCALEX)) {
                PlaySfxPositional(SFX_FROZEN_HALF_ATTACK);
                PlaySfxPositional(SFX_GLASS_SHARDS);
                self->ext.frozenHalf.entity = NULL;
                self->ext.frozenHalf.unk80 = 0x20;
                self->step_s++;
            }

            break;
        case 2:
            self->animCurFrame = 0xE;
            if (!--self->ext.frozenHalf.unk80) {
                SetStep(5);
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 1;
            if (self->posY.i.hi < 0x60) {
                self->step_s++;
            } else {
                self->posY.i.hi--;
            }
            break;
        case 1:
            if (AnimateEntity(&D_us_801820CC, self) == 0) {
                PlaySfxPositional(SFX_FROZEN_HALF_MAXIMUM_POWER);
                PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
                self->ext.frozenHalf.unk80 = 0x40;
                self->step_s++;
            }
            break;
        case 2:
            if (g_Timer & 2) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_27, self, entity);
                    entity->posY.i.hi -= 0x20;
                    entity->params = g_Timer & 1;
                    if (!entity->params) {
                        entity->velocityX =
                            ((rand() & PSP_RANDMASK) * 2) - 0x8000;
                    } else {
                        entity->velocityX = (rand() & PSP_RANDMASK) - 0x4000;
                    }
                }
            }

            if (!--self->ext.frozenHalf.unk80) {
                self->step_s++;
            }

            break;
        case 3:
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_25, self, entity);
                entity->posY.i.hi -= 0x28;
                entity->facingLeft = self->facingLeft;
                entity->zPriority = self->zPriority - 1;
                self->ext.frozenHalf.entity = entity;
                self->step_s++;
                PlaySfxPositional(SFX_TRANSFORM_3X);
            } else {
                self->ext.frozenHalf.entity = NULL;
                SetSubStep(5);
                break;
            }
            // fallthrough
        case 4:
            entity = self->ext.frozenHalf.entity;
            if (entity->entityId != E_UNK_25) {
                self->ext.frozenHalf.entity = NULL;
                SetSubStep(5);
            }
            break;
        case 5:
            if (!AnimateEntity(&D_us_801820DC, self)) {
                SetStep(5);
            }
            break;
        }
        break;
    case 10:
        switch (self->step_s) {
        case 0:
            self->facingLeft = GetSideToPlayer() & 1;
            if (self->facingLeft) {
                self->velocityX = FIX(1.0);
            } else {
                self->velocityX = FIX(-1.0);
            }
            self->velocityY = 0;
            self->ext.frozenHalf.unk80 = 0x10;
            self->animCurFrame = 0xC;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityX -= self->velocityX / 0x20;
            if (!--self->ext.frozenHalf.unk80) {
                SetStep(5);
            }
            break;
        }
        break;
    case 16:
        switch (self->step_s) {
        case 0:
            entity = self + 1;
            entity->step = 0x10;
            entity->flags |= FLAG_UNK_2000;
            self->hitboxState = 0;
            if (self->facingLeft) {
                self->velocityX = FIX(1.0);
            } else {
                self->velocityX = FIX(-1.0);
            }
            self->velocityY = 0;
            self->ext.frozenHalf.unk80 = 0x10;
            self->animCurFrame = 0xC;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityX -= self->velocityX / 0x20;
            if (!--self->ext.frozenHalf.unk80) {
                self->step_s++;
            }
            break;
        case 2:
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x200);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }

            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            self->ext.frozenHalf.prim = prim = &g_PrimBuf[primIndex];
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            // BUG! This is a reassignment of above line and only required for
            // PSP match
            prim = self->ext.frozenHalf.prim;
            prim->tpage = 0x12;
            prim->clut = 0x200;

            if (self->facingLeft) {
                prim->u0 = prim->u2 = 0xA0;
                prim->u1 = prim->u3 = 0x80;
            } else {
                prim->u0 = prim->u2 = 0x80;
                prim->u1 = prim->u3 = 0xA0;
            }

            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 0x30;
            prim->x0 = prim->x2 = posX - 0xF;
            prim->x1 = prim->x3 = posX + 0x11;
            prim->y0 = prim->y1 = posY - 0x15;
            prim->y2 = prim->y3 = posY + 0x1B;
            prim->priority = self->zPriority;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
            for (i = 0; i < 0x18; i++) {
                for (j = 0; j < 0x10; j++) {
                    prim->tpage = 0x12;
                    prim->clut = 0x200;
                    if (self->facingLeft) {
                        prim->u0 = prim->u2 = 0xA0 - (j * 2);
                        prim->u1 = prim->u3 = 0x9E - (j * 2);
                    } else {
                        prim->u0 = prim->u2 = 0x80 + (j * 2);
                        prim->u1 = prim->u3 = 0x82 + (j * 2);
                    }

                    prim->v0 = prim->v1 = 0x2E - (i * 2);
                    prim->v2 = prim->v3 = 0x30 - (i * 2);
                    prim->x0 = prim->x2 = posX - 0xF + (j * 2);
                    prim->x1 = prim->x3 = posX - 0xF + (j * 2) + 2;
                    prim->y0 = prim->y1 = posY + 0x1B - (i * 2) - 2;
                    prim->y2 = prim->y3 = posY + 0x1B - (i * 2);

                    PGREY(prim, 0) = 0x60;
                    LOW(prim->r1) = LOW(prim->r0);
                    LOW(prim->r2) = LOW(prim->r0);
                    LOW(prim->r3) = LOW(prim->r0);
                    prim->p3 = 0x50;
                    prim->priority = self->zPriority;
                    prim->priority++;
                    prim->drawMode = DRAW_HIDE | DRAW_UNK02;
                    prim = prim->next;
                }
            }

            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }

            self->animCurFrame = 0;
            self->ext.frozenHalf.unk80 = 1;
            self->ext.frozenHalf.unk8C = 0;
            PlaySfxPositional(SFX_GLASS_SHARDS);
            self->step_s++;
            break;
        case 3:
            if (!--self->ext.frozenHalf.unk80) {
                self->ext.frozenHalf.unk80 = 6;
                prim = self->ext.frozenHalf.prim;
                prim->v2 = prim->v3 -= 2;
                prim->y2 = prim->y3 -= 2;

                self->ext.frozenHalf.unk8C++;
                if (self->ext.frozenHalf.unk8C >= 0x17) {
                    self->step_s++;
                }
            }
            // fallthrough
        case 4:
            prim = self->ext.frozenHalf.prim;
            prim = prim->next;
            animResult = 1;
            for (i = 0; i < self->ext.frozenHalf.unk8C * 0x10; i++) {
                if (!prim->r0) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                } else {
                    animResult = 0;
                    posX = prim->x0 << 8;
                    posY = prim->y0 << 8;
                    posX += prim->p2;
                    posY += (prim->p3 * 0x10) - 0x400;
                    if (self->facingLeft) {
                        posX -= ((prim->u0 - 0x90) * 0x18);
                    } else {
                        posX += ((prim->u0 - 0x90) * 0x18);
                    }
                    prim->x0 = posX >> 8;
                    prim->p2 = posX & 0xFF;
                    prim->y0 = posY >> 8;
                    if (prim->p3) {
                        prim->p3 -= 2;
                    }
                    prim->x2 = prim->x0;
                    prim->x1 = prim->x3 = prim->x0 + 2;
                    prim->y1 = prim->y0;
                    prim->y2 = prim->y3 = prim->y0 + 2;

                    prim->r0 -= 2;
                    PGREY(prim, 1) = PGREY(prim, 2) = PGREY(prim, 3) =
                        prim->g0 = prim->b0 = prim->r0;

                    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                     DRAW_UNK02 | DRAW_TRANSP;
                    prim = prim->next;
                }
            }

            if (animResult) {
                DestroyEntity(self);
            }
            break;
        }
        break;
    // TODO: pad2_anim_debug
    case 0xFF:
#include "../pad2_anim_debug.h"
    }
}

void func_us_801BFF94(Entity* self) {
    Entity* parent;
    s32 posX;
    s32 posY;
    s16 var_s3;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018103C);
        // fallthrough
    case 1:
        MoveEntity();
        AnimateEntity(D_us_801820EC, self);
        self->ext.frozenHalf.unk82 += 0x40;
        parent = self - 1;
        if (parent->entityId != E_UNK_22) {
            DestroyEntity(self);
            return;
        }

        posX = parent->posX.val;
        posY = parent->posY.val;
        var_s3 = self->ext.frozenHalf.unk82;

        posX += rcos(var_s3) << 9;
        posY += (rsin(var_s3 / 2)) << 7;
        self->posX.val = posX;
        self->posY.val = posY;
        break;
    case 16:
        switch (self->step_s) {
        case 0:
            self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleX = self->scaleY = 0x100;
            self->pose = 0;
            self->poseTimer = 0;
            self->step_s++;
            // fallthrough
        case 1:
            AnimateEntity(D_us_801820F8, self);
            self->scaleX = self->scaleY -= 0x10;
            if (!self->scaleX) {
                DestroyEntity(self);
                return;
            }
            break;
        }
        break;
    }
}

void func_us_801C0118(Entity* self) {
    Entity* player;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80181048);
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = 0;
        self->drawFlags |= ENTITY_ROTATE;
        // fallthrough
    case 1:
        AnimateEntity(D_us_80182108, self);
        self->rotate += 0x10;
        self->scaleY = self->scaleX += 8;
        if (self->scaleX >= 0x100) {
            self->drawFlags = ENTITY_ROTATE;
            self->palette = 0x815F;
            self->step++;
        }
        break;
    case 2:
        self->palette = 0x200;
        player = &PLAYER;
        angle = GetAngleBetweenEntities(self, player);
        self->velocityX = rcos(angle) * 0x28;
        self->velocityY = rsin(angle) * 0x28;
        if (self->facingLeft) {
            if (self->velocityX > 0) {
                self->velocityX = FIX(-0.625);
            }
        } else {
            if (self->velocityX < 0) {
                self->velocityX = FIX(0.625);
            }
        }
        self->step++;
        break;
    case 3:
        AnimateEntity(D_us_80182108, self);
        MoveEntity();
        self->rotate += 0x40;
        break;
    }
}

Primitive* UnkRecursivePrimFunc1(
    SVECTOR* p0, SVECTOR* p1, SVECTOR* p2, SVECTOR* p3, Primitive* srcPrim,
    s32 iterations, Primitive* dstPrim, u8* dataPtr);

void func_us_801C02C4(Entity* self) {
#ifdef VERSION_PC
    u8 sp[SP_LEN];
#endif
    SVECTOR rot;
    VECTOR trans;
    MATRIX matrix;
    Primitive* prim;
    Primitive* nextPrim;
    Entity* entity;
    s32 var_s3;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80181054);
        self->scaleX = self->scaleY = 0;
        self->animCurFrame = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x41);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.frozenHalf.prim = prim;
        prim->tpage = 0x12;
        prim->clut = 0x202;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x40;
        prim->v0 = prim->v1 = 0x80;
        prim->v2 = prim->v3 = 0xC0;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        // fallthrough
    case 1:
        switch (self->step_s) {
        case 0:
            self->rotate += 0x40;
            self->scaleX += 0x80;
            self->scaleY = self->scaleX;
            if (self->scaleX >= 0x2000) {
                self->step_s++;
            }
            break;
        case 1:
            MoveEntity();
            self->velocityY -= FIX(0.25);
            self->rotate += 0x80;
            self->scaleX += 0x200;
            if (self->posY.i.hi < -0x60) {
                SetStep(2);
            }
            break;
        }

        SetGeomScreen(0x100);
        SetGeomOffset(self->posX.i.hi, 0x80);

        rot.vx = 0;
        rot.vy = self->rotate;
        rot.vz = 0;
        RotMatrixYXZ(&rot, &matrix);

        trans.vx = 0;
        trans.vy = -(0x80 - self->posY.i.hi);
        trans.vz = 0x100;
        TransMatrix(&matrix, &trans);

        trans.vx = self->scaleX;
        trans.vy = self->scaleX;
        trans.vz = self->scaleX;
        ScaleMatrix(&matrix, &trans);
        SetRotMatrix(&matrix);
        SetTransMatrix(&matrix);

        prim = self->ext.frozenHalf.prim;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        nextPrim = prim->next;
        nextPrim = UnkRecursivePrimFunc1(
            &D_us_80182120, &D_us_80182128, &D_us_80182130, &D_us_80182138,
            prim, 2, nextPrim, (u8*)SPAD(0));
        prim->drawMode = DRAW_HIDE;
        while (nextPrim != NULL) {
            nextPrim->drawMode = DRAW_HIDE;
            nextPrim = nextPrim->next;
        }
        break;
    case 2:
        prim = self->ext.frozenHalf.prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.frozenHalf.unk80 = 0x200;
        self->step++;
        break;
    case 3:
        entity = &PLAYER;
        var_s3 = -0x80;
        if (entity->velocityX > 0) {
            var_s3 += 0x40;
        }

        if (entity->velocityX < 0) {
            var_s3 -= 0x40;
        }

        if (!(self->ext.frozenHalf.unk80 & 0xF)) {
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_UNK_26, entity);
                entity->posY.i.hi = -0x20;
                entity->posX.i.hi = D_us_80182110[self->ext.ILLEGAL.u8[0xA]];
                entity->params = 0;
            }
            self->ext.ILLEGAL.u8[0xA] += 1;
            self->ext.ILLEGAL.u8[0xA] &= 7;
        }

        entity = AllocEntity(&g_Entities[64], &g_Entities[TOTAL_ENTITY_COUNT]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_UNK_26, entity);
            entity->posY.i.hi = -0x10;
            entity->posX.i.hi = (Random() * 2) + var_s3;
            entity->params = 1;
        }

        if (!(self->ext.frozenHalf.unk80 & 0x1F)) {
            g_api.PlaySfx(SFX_FROZEN_HALF_BLIZZARD);
        }

        if (!--self->ext.frozenHalf.unk80) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801C0718(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80181060);
        if (self->params) {
            self->hitboxState = 0;
            self->animCurFrame = 0x16;
            self->blendMode = BLEND_QUARTER | BLEND_TRANSP;
            self->step = 2;
            self->velocityX = FIX(0.75);
            self->velocityY = FIX(5.0);
            return;
        }

        self->drawFlags = ENTITY_ROTATE;
        self->velocityX = FIX(0.5);
        self->velocityY = FIX(4.0);
        // fallthrough
    case 1:
        MoveEntity();
        AnimateEntity(D_us_80182100, self);
        self->velocityY += FIX(0.0625);
        self->rotate += 0x20;

        if (self->posY.i.hi > 0x100) {
            DestroyEntity(self);
            return;
        }

        break;
    case 2:
        MoveEntity();
        self->velocityY += FIX(0.0625);

        if (self->posY.i.hi > 0x100) {
            DestroyEntity(self);
            return;
        }

        break;
    }
}

static u8 D_us_80182140[] = {
    0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x02, 0x04, 0x02, 0x05, 0x02,
    0x06, 0x02, 0x07, 0x02, 0x08, 0x02, 0x09, 0x02, 0x0A, 0x02, 0x0B,
    0x02, 0x0C, 0x02, 0x0D, 0x02, 0x0E, 0x02, 0x0F, 0x02, 0x10, 0x02,
    0x11, 0x02, 0x12, 0x02, 0x13, 0x02, 0x14, 0x02, 0x15, 0x02, 0x16,
    0x02, 0x17, 0x02, 0x18, 0xFF, 0x00, 0x00, 0x00,
};
static u8 D_us_80182174[] = {
    0x03, 0x01, 0x03, 0x02, 0x03, 0x03, 0x03, 0x04, 0x03, 0x05,
    0x03, 0x06, 0x03, 0x07, 0x03, 0x08, 0x03, 0x09, 0x03, 0x0A,
    0x03, 0x0B, 0x03, 0x0C, 0x03, 0x0D, 0xFF, 0x00,
};

void func_us_801C0844(Entity* self) {
    s32 animResult;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        if (!self->params) {
            self->animSet = 0xE;
            self->unk5A = 0x5C;
            self->velocityY = FIX(1.0);
        } else {
            self->animSet = 5;
            self->velocityY = FIX(1.25);
        }

        self->blendMode = BLEND_QUARTER | BLEND_TRANSP;
        self->palette = 0x8202;
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = 0x80;
        // fallthrough
    case 1:
        MoveEntity();
        self->velocityY -= self->velocityY / 0x40;
        self->velocityX += self->velocityX / 0x20;

        if (!self->params) {
            animResult = AnimateEntity(D_us_80182174, self);
        } else {
            animResult = AnimateEntity(D_us_80182140, self);
        }

        self->opacity -= 1;
        if (!self->opacity) {
            animResult = 0;
        }

        if (!animResult) {
            DestroyEntity(self);
        }

        break;
    }
}
