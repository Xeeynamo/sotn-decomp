// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

extern Point16 D_us_8018248C[];
extern s16 D_us_801824B0[];
extern u8 D_us_801824C0[];

void func_us_801CBE14(void) {
    long p, flag;
    SVECTOR svecTwo;    // sp90
    VECTOR vec;         // sp80
    MATRIX matrix;      // sp60
    SVECTOR svec = {0}; // sp58
    SVECTOR p0, p1, p2, p3;

    Primitive* prim;   // s0
    Entity* newEntity; // s1
    s32 i;             // s2
    s16 posX;          // s3
    s16 posY;          // s4
    s32 var_s5;        // s5
    s32 primIndex;     // s6

    switch (g_CurrentEntity->step_s) {
    case 0:
        // BUG? Immediately overwritten
        g_CurrentEntity->animCurFrame = 0x32;
        g_CurrentEntity->animCurFrame = 0;

        for (i = 5; i >= 0; i--) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x32, g_CurrentEntity, newEntity);
                posX = D_us_8018248C[i].x;
                posY = D_us_8018248C[i].y;
                posX += 0x10;
                posY += 0x14;
                if (g_CurrentEntity->facingLeft) {
                    posX = -posX;
                }
                posX = newEntity->posX.i.hi += posX;
                posY = newEntity->posY.i.hi += posY;
                newEntity->params = i;
                newEntity->facingLeft = g_CurrentEntity->facingLeft;
                newEntity->step = 0x11;
                newEntity->flags |= 0x2000;
            }
        }

        primIndex = g_api.AllocPrimitives(PRIM_G4, 8);
        if (primIndex != -1) {
            g_CurrentEntity->flags |= 0x800000;
            g_CurrentEntity->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.prim = prim; // TODO

            i = 0;
            while (prim != NULL) {
                prim->r0 = 0x20;
                prim->g0 = 0x20;
                prim->b0 = 0x40;
                LOW(prim->r1) = LOW(prim->r0);

                prim->r2 = 0xC0;
                prim->g2 = 0xC0;
                prim->b2 = 0xD0;
                LOW(prim->r3) = LOW(prim->r2);

                prim->u0 = D_us_801824C0[i];
                LOH(prim->u2) = D_us_801824B0[i];
                prim->v0 = 0;
                prim->u1 = 1;
                prim->v1 = 0;

                prim->priority = g_CurrentEntity->zPriority + 1;
                prim->drawMode = 0x433;
                prim = prim->next;
                i++;
            }
        } else {
            DestroyEntity(g_CurrentEntity);
            break;
        }
        g_CurrentEntity->step_s++;
        break;
    case 1:
        prim = g_CurrentEntity->ext.prim; // TODO
        SetGeomScreen(0x400);
        posX = g_CurrentEntity->posX.i.hi;
        posY = g_CurrentEntity->posY.i.hi + 0x2F;
        SetGeomOffset(posX, posY);
        while (prim != NULL) {
            if (prim->u0) {
                prim->u0--;
                prim = prim->next;
            } else {
                svecTwo.vx = 0;
                svecTwo.vy = LOH(prim->u2);
                svecTwo.vz = 0;
                RotMatrix(&svec, &matrix);
                RotMatrixY(svecTwo.vy, &matrix);
                vec.vx = 0;
                vec.vy = 0;
                vec.vz = 0x400;
                TransMatrix(&matrix, &vec);
                SetRotMatrix(&matrix);
                SetTransMatrix(&matrix);

                p0.vx = p2.vx = -(prim->u1 - prim->v1);
                p1.vx = p3.vx = prim->u1 - prim->v1;
                p0.vy = p1.vy = -prim->v0;
                p2.vy = p3.vy = 0;
                p0.vz = p1.vz = p2.vz = p3.vz = -0x18;
                var_s5 = RotAverage4(
                    &p0, &p1, &p2, &p3, (long*)&prim->x0, (long*)&prim->x1,
                    (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
                if (var_s5 < 0x100) {
                    prim->priority = g_CurrentEntity->zPriority + 2;
                } else {
                    prim->priority = g_CurrentEntity->zPriority - 2;
                }

                if (prim->v0 > 0xF0) {
                    if (prim->u1 > 0xA) {
                        if (prim->v1 > prim->u1) {
                            prim->drawMode = 8;
                        } else {
                            prim->v1++;
                        }
                    } else {
                        prim->u1++;
                    }
                } else {
                    prim->v0 += 0xF;
                    if (prim->v0 > 0xF0 && LOH(prim->u2) < 0) {
                        PlaySfxPositional(0x66D);
                    }
                }
                prim = prim->next;
            }
        }
        break;
    }
}

extern EInit D_us_80181218;
extern u8 D_us_801823F0[2][3];
extern u16 D_us_801823F8[];
extern u16 D_us_801823FC[];
extern s16 D_us_80182400[];
extern s16 D_us_80182410[];
extern s16 D_us_80182420[];
extern u8 D_us_80182428[];
extern u8 D_us_80182434[];
extern u8 D_us_80182444[];
extern u8 D_us_80182458[];
extern u8 D_us_80182464[];
extern u8 D_us_80182470[];
extern u8 D_us_80182484[];
extern s16 D_us_801824A4[];

void func_us_801CC2E4(Entity* self) {
    Primitive* prim; // s0
    Entity* entity;  // s1
    s32 primIndex;   // s2
    u8* ptr;         // s3
    s16 var_s4;      // s4
    s16 var_s5;      // s5
    u8 animResult;   // s6
    u16 var_s7;      // s7

    if (self->flags & 0x100 && self->step < 0x10) {
        if (self->flags & 0x800000) {
            primIndex = self->primIndex;
            g_api.FreePrimitives(primIndex);
            self->flags &= 0xFF7FFFFF;
        }
        if (self->ext.hellfireBeast.entity != NULL) {
            entity = self->ext.hellfireBeast.entity;
            DestroyEntity(entity);
        }
        self->hitboxState = 0;
        self->ext.hellfireBeast.unk84 = 0x100;
        PlaySfxPositional(0x775);
        SetStep(0x10);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80181218);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        entity = self + 1;
        CreateEntityFromCurrentEntity(0x36, entity);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex != -1) {
            self->flags |= 0x800000;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.hellfireBeast.prim = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 0x1A;
            prim->clut = 0x208;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x3F;
            prim->v0 = prim->v1 = 0xC0;
            prim->v2 = prim->v3 = 0xFF;
            prim->priority = self->zPriority - 2;
            prim->drawMode = 8;
            prim->p3 |= 0x10;
            LOH(prim->next->r2) = 0x40;
            LOH(prim->next->b2) = 0x40;
            prim = prim->next;
            prim = prim->next;

            self->ext.hellfireBeast.primTwo = prim;
            prim->tpage = 0x12;
            prim->clut = 0x230;
            prim->u0 = prim->u2 = 0xA0;
            prim->u1 = prim->u3 = 0xBF;
            prim->v0 = prim->v1 = 0xC0;
            prim->v2 = prim->v3 = 0xD7;
            prim->priority = self->zPriority + 1;
        } else {
            DestroyEntity(self);
            return;
        }
        break;
    case 1:
        if (UnkCollisionFunc3(D_us_80182400) & 1) {
            self->step++;
        }
        break;
    case 2:
        if (!self->step_s) {
            self->ext.hellfireBeast.unk84 = 0x40;
            self->step_s++;
        } else {
            if (!AnimateEntity(D_us_80182428, self)) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            }
            if (self->ext.hellfireBeast.unk84) {
                self->ext.hellfireBeast.unk84--;
            } else if (GetDistanceToPlayerX() < 0x40) {
                SetStep(4);
            } else {
                SetStep(5);
            }
        }
        break;
    case 3:
        animResult = AnimateEntity(D_us_80182464, self);
        if (animResult & 0x80 && self->pose == 4) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }

        if (!animResult) {
            SetStep(2);
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            self->velocityX = 0;
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
            break;
        case 1:
            UnkCollisionFunc2(D_us_80182420);
            if (!AnimateEntity(D_us_80182434, self)) {
                PlaySfxPositional(0x66D);
                self->ext.hellfireBeast.unk84 = 0xC;
                SetSubStep(2);
            }
            if (self->pose == 4) {
                self->velocityX = -0x40000;
                if (self->facingLeft) {
                    self->velocityX = -self->velocityX;
                }
            }
            break;
        case 2:
            UnkCollisionFunc2(D_us_80182420);
            if (self->facingLeft) {
                self->velocityX -= 0x2AAA;
            } else {
                self->velocityX += 0x2AAA;
            }

            if (!--self->ext.hellfireBeast.unk84) {
                SetSubStep(3);
                if (!self->velocityX) {
                    SetSubStep(4);
                } else if (self->facingLeft) {
                    EntityGreyPuffSpawner(self, 5, 3, 0x18, 0x30, 2, -7);
                } else {
                    EntityGreyPuffSpawner(self, 5, 3, -0x18, 0x30, 2, 7);
                }
            }
            break;
        case 3:
            UnkCollisionFunc2(D_us_80182420);
            if (self->pose > 2) {
                self->velocityX -= self->velocityX / 8;
            }

            if (!AnimateEntity(D_us_80182444, self)) {
                SetStep(2);
            }
            break;
        case 4:
            if (!AnimateEntity(D_us_80182458, self)) {
                SetStep(2);
            }
            break;
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80182470, self)) {
                self->ext.hellfireBeast.unk88 = Random() & 1;
                SetSubStep(1);
            }
            break;
        case 1:
            switch (self->ext.hellfireBeast.unk88) {
            case 0:
                if (self->facingLeft) {
                    var_s4 = 0x24;
                } else {
                    var_s4 = -0x24;
                }
                var_s5 = -8;
                break;
            case 1:
                var_s4 = PLAYER.posX.i.hi - self->posX.i.hi;
                var_s5 = 0x2F;
                break;
            default:
                var_s4 = 0x24;
                var_s5 = -8;
                break;
            }

            prim = self->ext.hellfireBeast.prim;
            prim->clut = D_us_801823F8[self->ext.hellfireBeast.unk88];
            LOH(prim->next->u1) = 0;
            prim->next->x2 = 0;
            prim->next->y2 = 0;
            prim->next->b3 = 0;
            prim->next->x1 = self->posX.i.hi;
            prim->next->x1 += var_s4;
            prim->next->y0 = self->posY.i.hi + var_s5;
            prim->drawMode = 0x77;
            prim = self->ext.hellfireBeast.primTwo;
            if (self->facingLeft) {
                prim->x0 = prim->x2 = self->posX.i.hi - 0xFFDF;
                prim->x1 = prim->x3 = prim->x0 - 0x20;
            } else {
                prim->x0 = prim->x2 = self->posX.i.hi + 0xFFDF;
                prim->x1 = prim->x3 = prim->x0 + 0x20;
            }
            prim->y0 = prim->y1 = self->posY.i.hi + 0xFFEF;
            prim->y2 = prim->y3 = prim->y1 + 0x18;

            PGREY(prim, 0) = 0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->drawMode = 0x437U;
            self->ext.hellfireBeast.unk84 = 0x20;
            self->step_s++;
            break;
        case 2:
            prim = self->ext.hellfireBeast.prim;
            prim->next->b3 += 4;
            prim->next->x2 = prim->next->y2 += 0x30;

            prim = self->ext.hellfireBeast.primTwo;
            ptr = D_us_801823F0[self->ext.hellfireBeast.unk88];
            prim->r0 += *ptr++;
            prim->g0 += *ptr++;
            prim->b0 += *ptr++;
            LOW(prim->r2) = LOW(prim->r0);

            if (self->ext.hellfireBeast.unk84 % 2) {
                prim->drawMode |= 8;
            } else {
                prim->drawMode &= 0xFFF7;
            }

            if (!--self->ext.hellfireBeast.unk84) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    var_s7 = D_us_801823FC[self->ext.hellfireBeast.unk88];
                    CreateEntityFromEntity(var_s7, self, entity);
                    entity->facingLeft = self->facingLeft;
                    prim = self->ext.hellfireBeast.prim;
                    entity->posX.i.hi = prim->next->x1;
                    entity->posY.i.hi = prim->next->y0;
                    self->ext.hellfireBeast.entity = entity;
                    self->step_s++;
                } else {
                    self->ext.hellfireBeast.entity = NULL;
                    SetStep(2);
                    return;
                }
            }
            break;
        case 3:
            AnimateEntity(D_us_80182484, self);
            prim = self->ext.hellfireBeast.primTwo;
            if (self->animCurFrame == 0x34) {
                prim->drawMode |= 8;
            } else {
                prim->drawMode &= 0xFFF7;
            }

            entity = self->ext.hellfireBeast.entity;
            if (!entity->entityId) {
                self->ext.hellfireBeast.entity = NULL;
                prim = self->ext.hellfireBeast.primTwo;
                prim->drawMode = 8;
                self->animCurFrame = 0x25;
                self->step_s++;
            }
            break;
        case 4:
            prim = self->ext.hellfireBeast.prim;
            prim->next->b3 -= 8;
            if (prim->next->b3 < 0x10) {
                prim->drawMode = 8;
                SetStep(2);
            }
            break;
        }

        prim = self->ext.hellfireBeast.prim;
        UnkPrimHelper(prim);
        switch (g_Timer % 3) {
        case 0:
            prim->clut = 0x300;
            break;
        case 1:
            prim->clut = 0x15F;
            break;
        case 2:
            prim->clut = D_us_801823F8[self->ext.hellfireBeast.unk88];
            break;
        }

        break;
    case 16:
        func_us_801CBE14();
        if (!--self->ext.hellfireBeast.unk84) {
            DestroyEntity(self);
            return;
        }
        break;
    case 17:
        InitializeEntity(D_us_80181218);
        self->hitboxState = 0;
        self->animCurFrame = self->params + 0x2B;
        self->ext.hellfireBeast.unk84 = D_us_801824A4[self->params];
        if (self->params < 3) {
            self->zPriority += 4;
        }
        if (self->params < 4) {
            self->zPriority++;
        } else {
            self->drawFlags |= 4;
        }
        SetStep(0x13);
        break;
    case 19:
        if (self->ext.hellfireBeast.unk84) {
            self->ext.hellfireBeast.unk84--;
            if (!self->ext.hellfireBeast.unk84) {
                // BUG! This plays the same sound effect either way
                if (self->params == 2) {
                    PlaySfxPositional(0x62E);
                } else {
                    PlaySfxPositional(0x62E);
                }
            }
            break;
        }

        if (UnkCollisionFunc3(D_us_80182410) & 1) {
            PlaySfxPositional(0x655);
            MakeExplosions();
            DestroyEntity(self);
            return;
        }

        self->rotate += self->ext.hellfireBeast.unk86;
        self->ext.hellfireBeast.unk86 += 2;
        self->velocityY -= 0x2000;
        break;
    }

    if (self->animCurFrame > 0x1F && self->animCurFrame < 0x24) {
        self->hitboxOffX = -9;
        self->hitboxOffY = 0xF;
        self->hitboxWidth = 0xC;
        self->hitboxHeight = 0x1E;
    } else {
        self->hitboxOffX = 0;
        self->hitboxOffY = 9;
        self->hitboxWidth = 0xE;
        self->hitboxHeight = 0x23;
    }
}

extern EInit D_us_8018123C;

void func_us_801CCEF0(Entity* self) {
    u8 sp3F;       // sp3F
    s16 angle;     // sp3C
    s16 posX;      // sp3A
    s16 posY;      // sp38
    s32 primIndex; // sp34

    Primitive* prim;    // s0
    Primitive* primTwo; // s1
    s16 var_s2;         // s2
    s32 dx;             // s3
    s16 var_s4;         // s4
    s32 dy;             // s5
    u8 var_s6;          // s6
    u8 var_s7;          // s7
    s16 var_s8;         // s8
    int x;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018123C);
        self->hitboxWidth = self->hitboxHeight = 0;
        self->animSet = 2;
        self->animCurFrame = 0;
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (primIndex != -1) {
            self->flags |= 0x800000;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.hellfireBeastUnk.prim = prim;
            prim->x0 = prim->x1 = self->posX.i.hi;
            prim->y0 = prim->y1 = self->posY.i.hi;
            prim->r0 = 0x60;
            prim->g0 = 0x20;
            prim->b0 = 0x80;
            PGREY(prim, 1) = 0x20;
            prim->priority = self->zPriority + 8;
            prim->drawMode = 0x33;
        } else {
            DestroyEntity(self);
            break;
        }
        PlaySfxPositional(0x620);
        // fallthrough
    case 1:
        prim = self->ext.hellfireBeastUnk.prim;
        if (!self->step_s) {
            if (self->facingLeft) {
                prim->x0 += 0x20;
            } else {
                prim->x0 -= 0x20;
            }

            if (prim->x0 & 0xFF00) {
                self->step_s++;
            }
        } else if (!PrimDecreaseBrightness(prim, 7)) {
            self->step++;
        }
        break;
    case 2:
        primIndex = self->primIndex;
        g_api.FreePrimitives(primIndex);
        self->flags &= 0xFF7FFFFF;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x40);
        if (primIndex != -1) {
            self->flags |= 0x800000;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.hellfireBeastUnk.prim = prim;
            while (prim != NULL) {
                prim->tpage = 0x13;
                prim->clut = 0x24A;
                prim->v0 = prim->v2 = 0x20;
                prim->v1 = prim->v3 = 0x10;
#ifdef VERSION_PSP
                PGREY(prim, 0) = 0xF0;
#else
                PGREY(prim, 0) = 0xC0;
#endif
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->priority = self->zPriority;
                prim->drawMode = 8;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            break;
        }
        self->ext.hellfireBeastUnk.unk8C = 0;
        self->ext.hellfireBeastUnk.unk90 = 0;
        self->ext.hellfireBeastUnk.unk8A = 4;
        self->hitboxState = 1;
        self->ext.hellfireBeastUnk.unk84 = 0x80;
        self->step++;
        // fallthrough
    case 3:
        posX = self->posX.i.hi + (self->ext.hellfireBeastUnk.unk8C >> 0x10);
        posY = self->posY.i.hi;
        if (self->facingLeft) {
            posY -= 8;
        } else {
            posY += 8;
        }

        self->ext.hellfireBeastUnk.unk8C += self->ext.hellfireBeastUnk.unk90;
        if (self->facingLeft) {
            self->ext.hellfireBeastUnk.unk90 += 0x4000;
        } else {
            self->ext.hellfireBeastUnk.unk90 -= 0x4000;
        }

        if (self->facingLeft) {
            var_s4 = 0;
        } else {
            var_s4 = 0x800;
        }

        var_s4 += (0xD0 - ((Random() & 7) << 6));
        var_s6 = self->ext.hellfireBeastUnk.unk94 * 0x10;
        self->ext.hellfireBeastUnk.unk94++;
        if (self->ext.hellfireBeastUnk.unk94 > 6) {
            self->ext.hellfireBeastUnk.unk94 = 1;
        }

        var_s8 = 1;
        prim = self->ext.hellfireBeastUnk.prim;
        prim->x0 = self->posX.i.hi;
        prim->x1 = prim->x0;
        prim->y0 = self->posY.i.hi;
        if (self->facingLeft) {
            prim->y0 -= 8;
            prim->y1 = prim->y0 + 0x10;
        } else {
            prim->y0 += 8;
            prim->y1 = prim->y0 - 0x10;
        }

        prim->x2 = self->posX.i.hi;
        prim->y2 = prim->y0;
        prim->x3 = prim->x2;
        prim->y3 = prim->y1;

        while (true) {
            dx = posX - prim->x2;
            dy = posY - prim->y2;
            if (!self->ext.hellfireBeastUnk.unk88) {
                self->ext.hellfireBeastUnk.unk88 = 4;
                angle = ratan2(-dy, dx);
                var_s2 = angle - var_s4;
                if (var_s2 > 0x800) {
                    var_s2 = 0x1000 - var_s2;
                }
                if (var_s2 < -0x800) {
                    var_s2 = 0x1000 + var_s2;
                }
                var_s2 /= 4;
                self->ext.hellfireBeastUnk.unk86 = var_s2;
            }

            var_s4 += self->ext.hellfireBeastUnk.unk86;
            var_s4 &= 0xFFF;

            primTwo = prim->next;
            if (primTwo == NULL) {
                self->step++;
                break; // exits while loop
            }

            LOW(primTwo->x0) = LOW(prim->x2);
            LOW(primTwo->x1) = LOW(prim->x3);
            dx = (rcos(var_s4) * 0xC) >> 0xC;
            dy = -((rsin(var_s4) * 0xC) >> 0xC);
            primTwo->x2 = primTwo->x0 + dx;
            primTwo->y2 = primTwo->y0 + dy;

            var_s2 = var_s4 - 0x400;
            var_s7 = 0x10;
            dx = (var_s7 * rcos(var_s2)) >> 0xC;
            dy = -(var_s7 * rsin(var_s2) >> 0xC);
            primTwo->x3 = primTwo->x2 + dx;
            primTwo->y3 = primTwo->y2 + dy;

            primTwo->u1 = var_s6;
            primTwo->u0 = var_s6;
            primTwo->u2 = primTwo->u3 = primTwo->u0 + 0xF;
            var_s6 += 0x10;
            if (var_s6 > 0x60) {
                var_s6 = 0x10;
            }

            if (!(g_Timer % 2)) {
                sp3F = primTwo->v0;
                primTwo->v0 = primTwo->v2 = primTwo->v1;
                primTwo->v1 = primTwo->v3 = sp3F;
            }
            primTwo->drawMode = 6;
            prim = primTwo;
            self->ext.hellfireBeastUnk.unk88--;
            var_s8++;

            if (var_s8 <= self->ext.hellfireBeastUnk.unk8A) {
                continue;
            }

            dx = primTwo->x0 - self->posX.i.hi;
            dx = abs(dx);
            if (dx > 0x1FF) {
                dx = 0x1FF;
            }
            self->hitboxOffX = -dx / 2;
            self->hitboxWidth = dx / 2;
            self->hitboxHeight = 8;
            self->hitboxOffY = 8;

#ifdef VERSION_US
            x = 8;
            while (prim != NULL) {
                prim->drawMode = x;
                prim = prim->next;
            }

            // Fake!
            if (0) {
                while (posY)
                    ;
            }
#else
            while (prim != NULL) {
                prim->drawMode = 8;
                prim = prim->next;
            }
#endif

            if (!(g_Timer % 3) && self->ext.hellfireBeastUnk.unk8A < 0x40) {
                self->ext.hellfireBeastUnk.unk8A++;
            }
            if (!(self->ext.hellfireBeastUnk.unk84 & 0x1F)) {
                g_api.PlaySfx(0x614);
            }

            if (!--self->ext.hellfireBeastUnk.unk84) {
                self->step++;
            }
            break; // exits while loop
        }
        break;
    case 4:
        DestroyEntity(self);
        break;
    }
}

void func_us_801CD614(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 2;
        self->animCurFrame = 1;
        self->zPriority = 0x100;
        self->drawFlags |= 4;
        self->flags &= 0xF7FFFFFF;
        if (self->params) {
            self->rotate = 0x800;
            self->velocityY = 0x10000;
        } else {
            self->rotate = 0;
            self->velocityY = -0x10000;
        }
    }
    self->posY.val += self->velocityY;
    self->poseTimer++;
    if (!(self->poseTimer % 2)) {
        self->animCurFrame += 1;
    }
    if (self->poseTimer > 0xF) {
        DestroyEntity(self);
    }

#ifdef VERSION_PSP
    if (self->ext.hellfireBeastUnk.entity != NULL &&
        !self->ext.hellfireBeastUnk.entity->entityId) {
#else
    if (!self->ext.hellfireBeastUnk.entity->entityId) {
#endif
        DestroyEntity(self);
    }
}

void func_us_801CD728(Primitive* prim) {
    Primitive* p;
    s16 posX;   // s3
    s16 posY;   // s4
    s16 var_s1; // s1
    s16 var_s2; // s2

    posX = g_CurrentEntity->posX.i.hi;
    posY = g_CurrentEntity->posY.i.hi - prim->p1;
    var_s1 = -prim->p1 * 6;
    prim->y0 = posY - ((g_CurrentEntity->ext.hellfireBeastUnk2.unk80 *
                        rsin(var_s1 + 0x800)) >>
                       0xC);
    prim->y1 =
        posY -
        ((g_CurrentEntity->ext.hellfireBeastUnk2.unk80 * rsin(var_s1)) >> 0xC);
    if (g_CurrentEntity->facingLeft) {
        prim->x0 = posX - ((g_CurrentEntity->ext.hellfireBeastUnk2.unk80 *
                            rcos(var_s1 + 0x800)) >>
                           0xC);
        prim->x1 =
            posX -
            ((g_CurrentEntity->ext.hellfireBeastUnk2.unk80 * rcos(var_s1)) >>
             0xC);
    } else {
        prim->x0 = posX + ((g_CurrentEntity->ext.hellfireBeastUnk2.unk80 *
                            rcos(var_s1 + 0x800)) >>
                           0xC);
        prim->x1 =
            posX +
            ((g_CurrentEntity->ext.hellfireBeastUnk2.unk80 * rcos(var_s1)) >>
             0xC);
    }

    posY += 0x20;
    var_s1 = -(g_CurrentEntity->posY.i.hi - posY) * 6;
    prim->y3 =
        posY -
        ((g_CurrentEntity->ext.hellfireBeastUnk2.unk80 * rsin(var_s1)) >> 0xC);

    if (g_CurrentEntity->facingLeft) {
        prim->x2 = posX - ((g_CurrentEntity->ext.hellfireBeastUnk2.unk80 *
                            rcos(var_s1 + 0x800)) >>
                           0xC);
        prim->x3 =
            posX -
            ((g_CurrentEntity->ext.hellfireBeastUnk2.unk80 * rcos(var_s1)) >>
             0xC);
    } else {
        prim->x2 = posX + ((g_CurrentEntity->ext.hellfireBeastUnk2.unk80 *
                            rcos(var_s1 + 0x800)) >>
                           0xC);
        prim->x3 =
            posX +
            ((g_CurrentEntity->ext.hellfireBeastUnk2.unk80 * rcos(var_s1)) >>
             0xC);
    }

    var_s2 = g_CurrentEntity->posY.i.hi - 0x88;
    if (prim->y0 < var_s2) {
        prim->y0 = var_s2;
    }
    if (prim->y1 < var_s2) {
        prim->y1 = var_s2;
    }
    if (prim->y2 < var_s2) {
        prim->y2 = var_s2;
    }
    if (prim->y3 < var_s2) {
        prim->y3 = var_s2;
    }

    if (prim->y2 > g_CurrentEntity->posY.i.hi) {
        prim->y2 = g_CurrentEntity->posY.i.hi;
    }

    if (prim->y3 > g_CurrentEntity->posY.i.hi) {
        prim->y3 = g_CurrentEntity->posY.i.hi;
    }

    if (prim->p1 > 0xA8) {
        prim->drawMode = 8;
        prim->p3 = 0;
    }

    if (prim->p1 == 0x20) {
        p = g_CurrentEntity->ext.prim;
        p = FindFirstUnkPrim(p);
        if (p != NULL) {
            p->p3 = 1;
            p->p1 = 0;
            p->y0 = p->y1 = g_CurrentEntity->posY.i.hi;
            p->y2 = p->y3 = g_CurrentEntity->posY.i.hi;
            p->drawMode = 0x37;
        }
    }
}

extern EInit D_us_80181230;

void func_us_801CDB50(Entity* self) {
    DRAWENV drawEnv;                                  // sp2C
    RECT rect = {.x = 0, .y = 256, .w = 64, .h = 64}; // sp24

    Primitive* prim;   // s0
    Entity* newEntity; // s1
    s32 i;             // s2
    s32 primIndex;     // s3
    DR_ENV* drEnv;     // s4

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80181230);
        self->animSet = 2;
        self->animCurFrame = 0;
        self->hitboxWidth = self->hitboxHeight = 0;
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (primIndex != -1) {
            self->flags |= 0x800000;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.hellfireBeastUnk2.prim = prim;

            prim->x0 = prim->x1 = self->posX.i.hi;
            prim->y0 = prim->y1 = self->posY.i.hi;
            prim->r0 = 0xC0;
            prim->g0 = 0x80;
            prim->b0 = 0x20;
            PGREY(prim, 1) = 0x20;
            prim->priority = self->zPriority + 8;
            prim->drawMode = 0x33;
        } else {
            DestroyEntity(self);
            break;
        }

        PlaySfxPositional(0x620);
        // fallthrough
    case 1:
        prim = self->ext.hellfireBeastUnk2.prim;
        if (!self->step_s) {
            prim->y0 -= 0x20;
            if (prim->y0 & 0xFF00) {
                self->step_s++;
            }
        } else if (!PrimDecreaseBrightness(prim, 7)) {
            self->step++;
        }
        break;
    case 2:
        primIndex = self->primIndex;
        g_api.FreePrimitives(primIndex);
        self->flags &= 0xFF7FFFFF;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x12);
        if (primIndex != -1) {
            self->flags |= 0x800000;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.hellfireBeast.primThree = prim;

            drEnv = g_api.func_800EDB08((POLY_GT4*)prim);
            if (drEnv == NULL) {
                DestroyEntity(self);
                break;
            }

            prim->type = 7;
            drawEnv = g_CurrentBuffer->draw;
            drawEnv.isbg = 1;
            drawEnv.clip = rect;
            drawEnv.ofs[0] = 0;
            drawEnv.ofs[1] = 0x100;
            SetDrawEnv(drEnv, &drawEnv);
            prim->priority = 0xFF;
            prim->drawMode = 8;
            prim = prim->next;

            drEnv = g_api.func_800EDB08((POLY_GT4*)prim);
            if (drEnv == NULL) {
                DestroyEntity(self);
                break;
            }

            prim->type = 7;
            prim->priority = 0x101;
            prim->drawMode = 0x808;
            prim = prim->next;

            self->ext.hellfireBeastUnk2.prim = prim;
            while (prim != NULL) {
                prim->tpage = 0x110;
                prim->u0 = prim->u1 = 0;
                prim->u2 = prim->u3 = 0x12;
                prim->v0 = prim->v2 = 0;
                prim->v1 = prim->v3 = 0x3F;
#ifdef VERSION_PSP
                PGREY(prim, 0) = 0xC0;
#else
                PGREY(prim, 0) = 0x60;
#endif
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->p3 = 0;
                prim->priority = self->zPriority;
                prim->drawMode = 8;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            break;
        }

        prim = self->ext.hellfireBeastUnk2.prim;
        prim = FindFirstUnkPrim(prim);
        if (prim != NULL) {
            prim->p3 = 1;
            prim->p1 = 0;
            prim->y0 = prim->y1 = self->posY.i.hi;
            prim->y2 = prim->y3 = self->posY.i.hi;
            prim->drawMode = 0x37;
        }
        self->ext.hellfireBeastUnk2.unk80 = 0x18;
        self->ext.hellfireBeastUnk2.unk84 = -0x10;
        PlaySfxPositional(0x660);
        self->step++;

        break;
    case 3:
        prim = self->ext.hellfireBeast.primThree;
        prim->drawMode = 0;

        prim = prim->next;
        prim->drawMode = 0x800;

        // NB. Strange way to write a single loop iteration...
        // Changed during development? Macro?
        for (i = 0; i <= 0; i++) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(0x35, newEntity);
                newEntity->posX.i.hi = Random() & 0xF;
                newEntity->posY.i.hi = 0x20;
                newEntity->params = Random() & 1;
                newEntity->ext.hellfireBeastUnk.entity = self;
            }
        }

        prim = self->ext.hellfireBeastUnk2.prim;
        while (prim != NULL) {
            if (prim->p3) {
                func_us_801CD728(prim);
            }
            prim = prim->next;
        }

        prim = self->ext.hellfireBeastUnk2.prim;
        while (prim != NULL) {
            prim->p1 += 2;
            prim = prim->next;
        }

        self->ext.hellfireBeastUnk2.unk84++;
        if (self->ext.hellfireBeastUnk2.unk84 < 0) {
            prim = self->ext.hellfireBeastUnk2.prim;
            while (prim != NULL) {
                prim->p1 += 6;
                prim = prim->next;
            }

            if (self->ext.hellfireBeastUnk2.unk80 < 0x20) {
                self->ext.hellfireBeastUnk2.unk80++;
            }
        } else {
            self->hitboxWidth = 0xC;
            self->hitboxHeight = 0x30;
            self->hitboxOffX = -4;
            self->hitboxOffY = -0x30;
            if (!(self->ext.hellfireBeastUnk2.unk84 % 8)) {
                PlaySfxPositional(0x655);
            }
        }
        if (self->ext.hellfireBeastUnk2.unk84 > 0x60) {
            self->ext.hellfireBeastUnk2.unk80--;
            self->hitboxState = 0;
            if (self->ext.hellfireBeastUnk2.unk80 < 0) {
                DestroyEntity(self);
            }
        }
        break;
    }
}

extern EInit D_us_80181224;

void func_us_801CE170(Entity* self) {
    Entity* parent = self - 1;

    if (!self->step) {
        InitializeEntity(D_us_80181224);
        self->hitboxWidth = 0xA;
        self->hitboxHeight = 4;
        self->hitboxOffX = -0x24;
        self->hitboxOffY = 4;
    }
    self->posX.i.hi = parent->posX.i.hi;
    self->posY.i.hi = parent->posY.i.hi;
    self->facingLeft = parent->facingLeft;
    if (parent->animCurFrame == 0x23) {
        self->hitboxState = 1;
    } else {
        self->hitboxState = 0;
    }
    if (!parent->entityId) {
        DestroyEntity(self);
    }
}
