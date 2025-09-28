// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

static u8 D_us_801825D4[] = {
    0x0D, 0x01, 0x10, 0x02, 0x0D, 0x03, 0x10, 0x02, 0x00};
static u8 D_us_801825E0[] = {
    0x08, 0x04, 0x07, 0x05, 0x03, 0x06, 0x03, 0x07, 0x06,
    0x08, 0x05, 0x09, 0x04, 0x0A, 0x32, 0x03, 0xFF, 0x00};
static u8 D_us_801825F4[] = {
    0x06, 0x0B, 0x04, 0x0C, 0x03, 0x0D, 0x06, 0x0E, 0x06,
    0x0F, 0x04, 0x10, 0x04, 0x11, 0x32, 0x03, 0xFF, 0x00};
static u8 D_us_80182608[] = {
    0x04, 0x12, 0x03, 0x13, 0x02, 0x14, 0x02, 0x15, 0xFF, 0x00};

static u8 D_us_80182614[] = {
    0x11, 0x18, 0x14, 0x17, 0x11, 0x16, 0x14, 0x17, 0x00, 0x00};

static u8 D_us_80182620[] = {0x07, 0x19, 0x07, 0x1A, 0x07, 0x1B, 0x00, 0x00};

static u8 D_us_80182628[] = {0x05, 0x1C, 0x06, 0x1D, 0x07, 0x1E, 0x02, 0x1F,
                             0x05, 0x20, 0x05, 0x21, 0x08, 0x22, 0xFF, 0x00};
static u8 D_us_80182638[] = {0x0A, 0x26, 0x06, 0x23, 0x04, 0x24, 0x03,
                             0x23, 0x03, 0x25, 0x41, 0x23, 0xFF, 0x00};
static u8 D_us_80182648[] = {
    0x02, 0x27, 0x02, 0x28, 0x02, 0x29, 0x02, 0x28, 0x00};

static s16 D_us_80182654[] = {0x0000, 0x0012, 0x000C, 0x0000};
// nb. this resides in BSS on PSP
static s16 D_us_8018265C[] = {0, 0, 0, 0};
static s16 D_us_80182664[] = {
    0x0000, 0x0012, 0x0000, 0x0004, 0x000C, 0xFFFC, 0xFFE8, 0x0000};
static s16 D_us_80182674[] = {
    0x0000, 0x0004, 0x0000, 0x0004, 0x0004, 0xFFFC, 0xFFF8, 0x0000};
static Point16 D_us_80182684[3] = {{.x = 0x0020, .y = 0x0000},
                                   {.x = 0x0014, .y = 0xFFEC},
                                   {.x = 0x0000, .y = 0xFFE4}};
static Point32 D_us_80182690[3] = {{.x = 0x00016000, .y = 0xFFFD8000},
                                   {.x = 0x00020000, .y = 0xFFFD0000},
                                   {.x = 0x00028000, .y = 0xFFFC0000}};
static s16 D_us_801826A8[] = {0x0020, 0x0040, 0x0050, 0x0060};
static Point16 D_us_801826B0[3] = {{.x = 0x0004, .y = 0xFFF0},
                                   {.x = 0xFFF6, .y = 0xFFFE},
                                   {.x = 0x0002, .y = 0x0004}};

void func_us_801CF87C(Primitive* prim) {
    s32 primY;

    switch (prim->p3) {
    case 1:
        prim->v0 = prim->v1 = 0x58;
        prim->v2 = prim->v3 = 0x58;
        PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) = PGREY(prim, 3) =
            0x80;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        if (g_CurrentEntity->facingLeft) {
            prim->x0 -= 4;
            prim->x1 -= 4;
        } else {
            prim->x0 += 4;
            prim->x1 += 4;
        }
        prim->p3++;
        // fallthrough
    case 2:
        primY = prim->y2 - prim->y0;
        primY = (0x24 - primY) / 2;
        if (primY < 2) {
            primY = 2;
        }
        prim->y0 = prim->y1 -= primY;
        prim->v2 = prim->v3 += primY;
        prim->x3 = g_CurrentEntity->posX.i.hi;
        if (prim->v2 >= 0x7C) {
            prim->drawMode |= DRAW_COLORS;
            if (g_CurrentEntity->facingLeft) {
                prim->x3 = prim->x2 + 0x10;
            } else {
                prim->x3 = prim->x2 - 0x10;
            }
            prim->v2 = prim->v3 = 0x7C;
            prim->p3++;
        }
        break;
    case 3:
        prim->y0 = ++prim->y1;
        primY = prim->y2 - prim->y0;
        if (primY < 0x10) {
            prim->p3 = 4;
        }
        break;
    case 4:
        if (g_CurrentEntity->facingLeft) {
            prim->x1--;
            prim->x3--;
        } else {
            prim->x1++;
            prim->x3++;
        }
        if (!PrimDecreaseBrightness(prim, 7)) {
            prim->p3 = 0;
            prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        }
        break;
    }
}

extern EInit D_us_80181248;
void func_us_801CFAE8(Entity* self) {
    Entity* newEntity; // s0
    s32 i;             // s1
    u32 var_s2;        // s2

    if ((self->flags & FLAG_DEAD) && self->step < 8) {
        PlaySfxPositional(0x735);
        SetStep(8);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80181248);
        self->animCurFrame = 1;
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;

        newEntity = self + 1;
        CreateEntityFromEntity(0x3F, self, newEntity);
        newEntity->zPriority = self->zPriority + 1;

        newEntity = self + 2;
        CreateEntityFromEntity(0x43, self, newEntity);
        newEntity->params = 1;
        newEntity->ext.lossoth.unk9C = self;
        // fallthrough
    case 1:
        if (UnkCollisionFunc3(D_us_80182664) & 1) {
            SetStep(2);
        }
        break;
    case 2:
        if (!self->step_s) {
            self->ext.lossoth.unk80 = 0x40;
            self->step_s++;
        }
        AnimateEntity(D_us_801825D4, self);
        UnkCollisionFunc2(D_us_80182654);

        if (self->facingLeft) {
            self->velocityX = FIX(0.25);
        } else {
            self->velocityX = FIX(-0.25);
        }

        if (!--self->ext.lossoth.unk80) {
            self->facingLeft ^= 1;
            self->ext.lossoth.unk80 = 0x40;
        }

        if (GetDistanceToPlayerX() < 0x60 &&
            ((GetSideToPlayer() & 1) ^ self->facingLeft)) {
            SetStep(3);
        }

        break;
    case 3:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.lossoth.unk80 = D_us_801826A8[Random() & 3];
            self->step_s++;
        }

        if (!AnimateEntity(D_us_801825D4, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }

        var_s2 = UnkCollisionFunc2(&D_us_80182654);
        if (var_s2 & 0x80) {
            self->ext.lossoth.unk80 = 1;
        }

        if (self->facingLeft) {
            self->velocityX = FIX(0.4375);
        } else {
            self->velocityX = FIX(-0.4375);
        }

        if (!--self->ext.lossoth.unk80) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;

            if (Random() & 1) {
                SetStep(5);
            } else {
                SetStep(4);
            }

            if (var_s2 & 0x80) {
                SetStep(4);
            }
        }

        if (GetDistanceToPlayerX() > 0xC0) {
            SetStep(2);
        }

        break;
    case 4:
        if (!AnimateEntity(D_us_801825E0, self)) {
            SetStep(3);
        }

        if (!self->poseTimer && self->pose == 3) {
            PlaySfxPositional(0x62C);

            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x40, self, newEntity);
                    newEntity->facingLeft = self->facingLeft;
                    newEntity->params = i;
                    if (self->facingLeft) {
                        newEntity->posX.i.hi += D_us_80182684[i].x;
                    } else {
                        newEntity->posX.i.hi -= D_us_80182684[i].x;
                    }
                    newEntity->posY.i.hi += D_us_80182684[i].y;
                }
            }
        }
        break;
    case 5:
        if (!AnimateEntity(D_us_801825F4, self)) {
            SetStep(3);
        }

        if (!self->poseTimer && self->pose == 3) {
            PlaySfxPositional(0x734);
            PlaySfxPositional(0x660);
            newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x41, self, newEntity);
                newEntity->facingLeft = self->facingLeft;
                if (self->facingLeft) {
                    newEntity->posX.i.hi += 8;
                } else {
                    newEntity->posX.i.hi -= 8;
                }
                newEntity->posY.i.hi += 0x12;
            }
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0x2E;
            self->hitboxState = 0;
            self->drawFlags |= FLAG_DRAW_OPACITY;
            self->opacity = 0x80;

            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x42, self, newEntity);
                    newEntity->facingLeft = self->facingLeft;
                    newEntity->ext.lossoth.unkA8 = self;
                    if (i == 0) {
                        newEntity->zPriority = self->zPriority - 4;
                    } else {
                        newEntity->zPriority = self->zPriority + 4;
                    }
                    newEntity->params = i + 2;
                }
            }
            SetSubStep(1);
            break;
        case 1:
            if (!self->opacity) {
                self->drawFlags = FLAG_DRAW_DEFAULT;
                self->animCurFrame = 0x18;
                self->ext.lossoth.unk80 = 0;
                SetSubStep(2);
            }
            break;
        case 2:
            if (!(g_Timer & 0xF)) {
                PlaySfxPositional(0x672);
            }
            var_s2 = AnimateEntity(D_us_80182614, self);
            if (!self->poseTimer && self->pose == 2) {
                self->ext.lossoth.unk80++;
            }
            UnkCollisionFunc2(D_us_80182654);

            if (self->facingLeft ^ self->ext.lossoth.unk80) {
                self->velocityX = FIX(0.25);
            } else {
                self->velocityX = FIX(-0.25);
            }

            if (!var_s2) {
                self->ext.lossoth.unk80++;
                if (self->ext.lossoth.unk80 > 1) {
                    SetSubStep(3);
                }
            }

            if (!(g_Timer & 3)) {
                self->palette++;
                if (self->palette > 0x21A) {
                    self->palette = 0x216;
                }
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_80182638, self)) {
                PlaySfxPositional(0x654);
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(2, self, newEntity);
                    newEntity->params = 2;
                    if (self->facingLeft) {
                        newEntity->posX.i.hi += 6;
                    } else {
                        newEntity->posX.i.hi -= 6;
                    }
                }
                self->ext.lossoth.unk80 = 0x10;
                self->step_s++;
            }

            if (!(g_Timer & 3)) {
                self->palette++;
                if (self->palette > 0x21A) {
                    self->palette = 0x216;
                }
            }
            break;
        case 4:
            if (!--self->ext.lossoth.unk80) {
                DestroyEntity(self);
                return;
            }

            if (!(g_Timer & 3)) {
                self->palette++;
                if (self->palette > 0x21A) {
                    self->palette = 0x216;
                }
            }
            break;
        }
        break;
    case 255:
#include "../pad2_anim_debug.h"
    }
}

extern EInit D_us_80181254;
void func_us_801D033C(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    Entity* entity; // s1
    s32 posX;       // s2
    s32 i;          // s3
    s32 var_s4;     // s4
    s32 posY;       // s5

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80181254);
        self->hitboxState = 0;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        // fallthrough
    case 1:
        AnimateEntity(D_us_80182648, self);
        entity = self - 1;
        self->facingLeft = entity->facingLeft;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        if (entity->facingLeft) {
            self->posX.i.hi += 7;
        } else {
            self->posX.i.hi -= 7;
        }
        self->posY.i.hi += 6;
        if (entity->flags & FLAG_DEAD) {
            SetStep(2);
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0x1C;
            self->drawMode = DRAW_DEFAULT;
            if (self->facingLeft) {
                self->velocityX = FIX(-0.75);
            } else {
                self->velocityX = FIX(0.75);
            }
            self->step_s++;
            // fallthrough
        case 1:
            if (UnkCollisionFunc3(D_us_80182674) & 1) {
                self->step_s++;
            }
            break;
        case 2:
            if (!AnimateEntity(D_us_80182628, self)) {
                self->drawFlags |= FLAG_DRAW_SCALEX;
                self->scaleX = 0x100;
                self->step_s++;
            }
            break;
        case 3:
            self->scaleX += 0x28;
            if (self->scaleX > 0x280) {
                self->step_s++;
            }
            break;
        case 4:
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.lossoth.prim = prim;

            posX = self->posX.i.hi - 0x10;
            posY = self->posY.i.hi + 4;

            while (prim != NULL) {
                prim->tpage = 0x14;
                prim->clut = 0x21F;
                prim->u0 = prim->u2 = 0xD4;
                prim->u1 = prim->u3 = 0xD6;
                prim->v0 = prim->v1 = prim->v2 = prim->v3 = 0x50;
                prim->x0 = prim->x2 = posX;
                posX += 2;
                prim->x1 = prim->x3 = posX;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 = posY;
                PGREY(prim, 0) = 0x80;
                LOW(prim->r1) = LOW(prim->r2) = LOW(prim->r3) = LOW(prim->r0);
                prim->priority = self->zPriority + 1;
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
                prim = prim->next;
            }

            self->animCurFrame = 0;
            self->step_s++;
            // fallthrough
        case 5:
            self->animCurFrame = 0x2E;
            self->palette = 0x821A;
            self->opacity = 0;
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
            self->drawFlags = FLAG_DRAW_OPACITY;
            entity = self - 1;
            self->posX.i.hi = entity->posX.i.hi;
            self->posY.i.hi = entity->posY.i.hi;
            self->facingLeft = entity->facingLeft;
            PlaySfxPositional(0x65E);
            self->step_s++;
            // fallthrough
        case 6:
            prim = self->ext.lossoth.prim;
            var_s4 = 0;
            while (prim != NULL) {
                prim->y0 = prim->y1 -= 4;
                prim->v2 = prim->v3 += 2;
                if (prim->v2 >= 0x7C) {
                    prim->v2 = prim->v3 = 0x7C;
                    var_s4 = 1;
                    self->step_s = 7;
                }
                prim = prim->next;
            }
            // fallthrough
        case 7:
            if (self->step_s == 7) {
                var_s4 = 1;
            }
            prim = self->ext.lossoth.prim;
            while (prim != NULL) {
                if (Random() & 1) {
                    prim->y0 = prim->y1 += 4;
                } else {
                    prim->y0 = prim->y1 -= 4;
                }
                prim = prim->next;
            }
            self->opacity += 4;
            if (self->opacity > 0x80) {
                self->opacity = 0x80;
                self->animCurFrame = 0;
                if (var_s4) {
                    self->step_s = 8;
                }
            }

            entity = self - 1;
            entity->opacity = (0x80 - self->opacity);
            for (i = 0; i < 2; i++) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(0x42, self, entity);
                    entity->posY.i.hi += 0x10;
                    entity->posX.i.hi += (Random() & 0x1F) - 0x10;
                    entity->zPriority = self->zPriority + 2;
                    entity->params = 6;
                }
            }
            break;
        case 8:
            prim = self->ext.lossoth.prim;
            while (prim != NULL) {
                PrimDecreaseBrightness(prim, 7);
                prim = prim->next;
            }
            break;
        }
    }

    entity = self - 1;
    if (entity->entityId != 0x3E) {
        DestroyEntity(self);
    }
}

extern EInit D_us_80181260;
void func_us_801D08A8(Entity* self) {
    Collider collider;
    Entity* newEntity;
    s32 params;
    s32 posX;
    s32 posY;

    if (self->hitParams || self->flags & FLAG_DEAD) {
        self->drawFlags = FLAG_DRAW_DEFAULT;
        self->pfnUpdate = EntityExplosion;
        self->step = 0;
        self->params = 0;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80181260);
        self->animCurFrame = 0x2B;
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->rotate = Random() * 0x10;
        params = self->params;
        self->velocityX = D_us_80182690[params].x;
        self->velocityY = D_us_80182690[params].y;
        if (!self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        // fallthrough
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        self->rotate -= 0xC0;
        if (!(g_Timer & 3)) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x42, self, newEntity);
                newEntity->rotate = self->rotate;
            }
        }
        if (self->velocityX > 0) {
            posX = self->posX.i.hi + 8;
        } else {
            posX = self->posX.i.hi - 8;
        }
        posY = self->posY.i.hi;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->flags |= FLAG_DEAD;
        }

        if (self->velocityY != 0) {
            posX = self->posX.i.hi;
            posY = self->posY.i.hi + 8;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->posY.i.hi += collider.unk18;
                self->rotate = 0;
                SetStep(2);
            }

            if (collider.effects & EFFECT_UNK_8000) {
                self->flags |= FLAG_DEAD;
            }
        }
        break;
    case 2:
        if (!AnimateEntity(&D_us_80182608, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

extern Primitive* FindFirstUnkPrim(Primitive* poly);
void func_us_801D0B38(Entity* self) {
    Primitive* prim;
    Entity* newEntity;
    s32 primIndex;
    s32 var_s2; // s2
    s32 var_s1;

    FntPrint("f_step %x\n", self->step);
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80181260);
        self->animCurFrame = 0;
        self->hitboxWidth = 0xC;
        self->hitboxOffX = 0x10;
        self->hitboxHeight = 8;
        self->hitboxOffY = -8;
#ifdef VERSION_US
        self->hitboxState = 1;
#endif
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.lossoth.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0x14;
            prim->clut = 0x21A;
            prim->u0 = prim->u2 = 0x80;
            prim->u1 = prim->u3 = 0x90;
            prim->v0 = prim->v1 = 0x58;
            prim->v2 = prim->v3 = 0x58;
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_HIDE | DRAW_UNK02;
            prim->p3 = 0;
            prim = prim->next;
        }

        if (self->facingLeft) {
            self->velocityX = FIX(2.0);
        } else {
            self->velocityX = FIX(-2.0);
        }

        self->ext.lossothUnk.unk9C = self->ext.lossothUnk.prim;
        self->ext.lossothUnk.unkA0.val = 0;
        prim = self->ext.lossothUnk.unk9C;
        prim->x0 = prim->x2 = self->posX.i.hi;
        prim->y0 = prim->y2 = self->posY.i.hi;
        break;
    case 1:
        var_s2 = UnkCollisionFunc2(D_us_8018265C);
        self->ext.lossothUnk.unkA0.val -= abs(self->velocityX);
        if (var_s2 & 0x80) {
            self->ext.lossothUnk.unkA0.val = 0;
            self->step++;
        }
        if (self->ext.lossothUnk.unkA0.i.hi <= 0) {
            prim = self->ext.lossothUnk.unk9C;
            prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y1 = prim->y3 = self->posY.i.hi;
            prim->p3 = 1;

            prim = self->ext.lossothUnk.prim;
            prim = FindFirstUnkPrim(prim);
            self->ext.lossothUnk.unk9C = prim;
            if (prim == NULL) {
                DestroyEntity(self);
                return;
            }

            if (self->velocityX > 0) {
                prim->x0 = prim->x2 = self->posX.i.hi - 8;
            } else {
                prim->x0 = prim->x2 = self->posX.i.hi + 8;
            }
            prim->y0 = prim->y2 = self->posY.i.hi;
            self->ext.lossothUnk.unkA0.val += (Random() << 8) + 0x80000;
        }

        if (!(g_Timer & 3)) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x42, self, newEntity);
                newEntity->zPriority = self->zPriority + 2;
                newEntity->params = 1;
            }
        }
        break;
    case 2:
        self->hitboxState = 0;
        if (!self->ext.lossothUnk.unkA5) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    prim = self->ext.lossothUnk.prim;
    var_s2 = 0;
    var_s1 = self->ext.lossothUnk.unkA4;
    while (prim != NULL) {
        prim->clut = var_s1 + 0x21A;
        if (prim->p3) {
            func_us_801CF87C(prim);
            var_s2++;
        }
        var_s1++;
        if (var_s1 > 4) {
            var_s1 = 0;
        }
        prim = prim->next;
    }
    self->ext.lossothUnk.unkA5 = var_s2;
    if (!(g_Timer & 3)) {
        self->ext.lossothUnk.unkA4 += 1;
        if (self->ext.lossothUnk.unkA4 > 4) {
            self->ext.lossothUnk.unkA4 = 0;
        }
    }
}

void func_us_801D0F10(Entity* self) {
    Entity* entity;
    s32 params;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80181248);
#ifdef VERSION_US
        self->flags |= FLAG_UNK_00200000 | FLAG_UNK_2000;
        self->hitboxState = 0;
#else
        self->flags |= FLAG_UNK_2000;
#endif
        switch (self->params) {
        case 0:
            self->drawFlags |= FLAG_DRAW_ROTATE;
            self->animCurFrame = 0x2D;
            self->ext.lossothUnk.unk80 = 0x10;
            self->velocityX = rcos(self->rotate) * 0x10;
            self->velocityY = rsin(self->rotate) * 0x10;
            self->step = 1;
            break;
        case 1:
            self->animCurFrame = 0x2D;
            self->ext.lossothUnk.unk80 = 0x20;
            self->velocityX = 0;
            self->velocityY = FIX(-0.75);
            self->step = 1;
            break;
        case 6:
            self->animCurFrame = 0x2D;
            self->ext.lossothUnk.unk80 = (Random() & 0x1F) + 0x10;
            self->velocityX = 0;
            self->velocityY = -0x4000 - (Random() << 8);
            self->step = 1;
            break;
        default:
            self->drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
            self->scaleY = self->scaleX = 0;
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
            self->ext.lossothUnk.unk80 = 0x40;
            self->step = 2;
            break;
        }
        break;
    case 1:
        MoveEntity();
        if (!--self->ext.lossothUnk.unk80) {
            DestroyEntity(self);
        }
        break;
    case 2:
        if (self->ext.lossothUnk.unk80) {
            self->ext.lossothUnk.unk80--;
            break;
        }

        self->scaleY = self->scaleX += 4;
        if (self->scaleX > 0x100) {
            self->drawFlags = FLAG_DRAW_DEFAULT;
        }

        AnimateEntity(D_us_80182620, self);
        params = self->params - 2;
        entity = self->ext.lossoth.unkA8;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        if (self->facingLeft) {
            self->posX.i.hi -= D_us_801826B0[params].x;
        } else {
            self->posX.i.hi += D_us_801826B0[params].x;
        }
        self->posY.i.hi += D_us_801826B0[params].y;

        if (entity->animCurFrame > 0x22 && entity->animCurFrame < 0x26) {
            if (self->facingLeft) {
                self->posX.i.hi += 8;
            } else {
                self->posX.i.hi -= 8;
            }
            self->posY.i.hi += 4;
        }

        if (entity->entityId != 0x3E) {
            DestroyEntity(self);
        }
        break;
    }
}
