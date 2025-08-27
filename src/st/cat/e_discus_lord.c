// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

extern EInit D_us_80181200;
static s16 D_us_801822D4[] = {0, 46, 0, 4, 8, -4, -16, 0};
static Point16 D_us_801822E4[] = {
    {.x = -35, .y = -24}, {.x = -14, .y = -23}, {.x = -2, .y = -25},
    {.x = -13, .y = -40}, {.x = -1, .y = 1},    {.x = -31, .y = 1}};
static u8 D_us_801822FC[] = {
    0x08, 0x01, 0x08, 0x02, 0x07, 0x03, 0x07, 0x04, 0x08, 0x05, 0x00, 0x00};
static u8 D_us_80182308[] = {
    0x26, 0x06, 0x05, 0x07, 0x03, 0x08, 0x03, 0x09, 0x02, 0x0A,
    0x02, 0x0B, 0x03, 0x0C, 0x04, 0x0D, 0x04, 0x0A, 0x04, 0x0D,
    0x10, 0x0B, 0x03, 0x0C, 0x04, 0x0D, 0xFF, 0x00};
static u8 D_us_80182324[] = {
    0x14, 0x09, 0x08, 0x08, 0x08, 0x0E, 0x04, 0x07, 0xFF, 0x00, 0x00, 0x00};
static u8 D_us_80182330[] = {
    0x04, 0x01, 0x08, 0x0E, 0x08, 0x0E, 0x04, 0x01, 0xFF, 0x00, 0x00, 0x00};
static u8 D_us_8018233C[] = {0x18, 0x06, 0x03, 0x07, 0x03, 0x08, 0x18, 0x09,
                             0x04, 0x08, 0x04, 0x07, 0x04, 0x06, 0xFF, 0x00};
static u8 D_us_8018234C[] = {
    0x18, 0x06, 0x02, 0x07, 0x02, 0x08, 0x02, 0x09, 0x18, 0x0A,
    0x03, 0x09, 0x03, 0x08, 0x03, 0x07, 0x03, 0x06, 0xFF, 0x00};
static Point16 D_us_80182360[] = {{.x = 0, .y = 9}, {.x = -9, .y = 15}};
static Point16 D_us_80182368[] = {{.x = 14, .y = 35}, {.x = 12, .y = 30}};

extern EInit D_us_8018120C;
static s16 D_us_80182370[] = {0, 12, 8, 0};
static Point16 D_us_80182378[] = {
    {.x = 0, .y = 0},     {.x = 24, .y = 8},    {.x = 24, .y = 8},
    {.x = 24, .y = 10},   {.x = 24, .y = 12},   {.x = 24, .y = 10},
    {.x = 24, .y = 8},    {.x = 24, .y = 16},   {.x = 2, .y = 20},
    {.x = -48, .y = 2},   {.x = -48, .y = -32}, {.x = -46, .y = -32},
    {.x = -44, .y = -32}, {.x = -46, .y = -32}, {.x = 16, .y = 4}};
static Point16 D_us_801823B4[] = {
    {.x = 0, .y = 0},    {.x = -24, .y = 10}, {.x = -24, .y = 10},
    {.x = -24, .y = 12}, {.x = -24, .y = 14}, {.x = -24, .y = 12},
    {.x = -24, .y = 10}, {.x = -23, .y = 11}, {.x = 0, .y = 12},
    {.x = 0, .y = 12},   {.x = 16, .y = 5},   {.x = 16, .y = 6},
    {.x = 15, .y = 5},   {.x = 16, .y = 5},   {.x = -32, .y = 4}};

void func_us_801CA2A4(Entity* self) {
    Entity* entity;  // s0
    Primitive* prim; // s1
    s16 posX;        // s2
    s16 posY;        // s3
    s32 i;           // s4
    u8 var_s5;       // s5
    Entity* child;   // s6
    s32 sqrt;        // s7
    s32 primIndex;   // s8

    child = self + 1;
    if (self->flags & 0x100 && self->step < 0x10) {
        self->hitboxState = 0;
        child->flags |= FLAG_DEAD;
        self->flags &= ~(FLAG_UNK_20000000 | FLAG_UNK_200);
        self->flags |= FLAG_UNK_2000;
        SetStep(0x10);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80181200);
        CreateEntityFromEntity(0x2F, self, child);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        // fallthrough
    case 1:
        UnkCollisionFunc3(D_us_801822D4);
        AnimateEntity(D_us_801822FC, self);
        if (GetDistanceToPlayerX() < 0x80) {
            self->step++;
        }
        break;
    case 2:
        if (!self->step_s) {
            self->ext.discusLord.unk82 = 0x40;
            self->step_s++;
        }

        var_s5 = (GetSideToPlayer() & 1) ^ 1;
        if (var_s5 ^ self->facingLeft) {
            SetStep(3);
        }

        AnimateEntity(D_us_801822FC, self);
        if (self->ext.discusLord.unk82) {
            self->ext.discusLord.unk82--;
        } else {
            if (GetDistanceToPlayerX() < 0xB0) {
                SetStep(4);
            }
            if (GetDistanceToPlayerX() < 0x40) {
                SetStep(5);
                if (GetSideToPlayer() & 2) {
                    SetStep(6);
                }
            }
        }
        break;
    case 3:
        var_s5 = AnimateEntity(D_us_80182330, self);
        if ((var_s5 & 0x80) && self->pose == 3) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        if (!var_s5) {
            SetStep(2);
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80182308, self)) {
                self->step_s++;
            }
            if (self->animCurFrame == 9 && !self->poseTimer) {
                PlaySfxPositional(0x765);
                PlaySfxPositional(0x763);
                child->ext.discusLord.unk80 = 1;
                if (self->facingLeft) {
                    EntityGreyPuffSpawner(self, 5, 3, -4, 0x30, 2, 7);
                } else {
                    EntityGreyPuffSpawner(self, 5, 3, 4, 0x30, 2, -7);
                }
            }
            break;
        case 1:
            if (!child->ext.discusLord.unk80) {
                PlaySfxPositional(0x765);
                SetSubStep(2);
            }
            break;
        case 2:
            if (!AnimateEntity(D_us_80182324, self)) {
                SetStep(2);
            }
            break;
        }
        break;
    case 5:
        if (self->pose < 5) {
            child->ext.discusLord.unk98 = 0;
        }
        if (!AnimateEntity(D_us_8018233C, self)) {
            SetStep(2);
        }
        if (!self->poseTimer && self->pose == 3) {
            PlaySfxPositional(0x66E);
        }
        break;
    case 6:
        if (self->pose < 6) {
            child->ext.discusLord.unk98 = 0;
        }
        if (!AnimateEntity(D_us_8018234C, self)) {
            SetStep(2);
        }
        if (!self->poseTimer && self->pose == 4) {
            PlaySfxPositional(0x66E);
        }
        break;
    case 16:
        switch (self->step_s) {
        case 0:
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex != -1) {
                self->primIndex = primIndex;
                self->flags |= FLAG_HAS_PRIMS;
                prim = &g_PrimBuf[primIndex];
                self->ext.discusLord.prim = prim;
                UnkPolyFunc2(prim);
                prim->tpage = 0x1A;
                prim->clut = 0x235;
                prim->u0 = prim->u2 = 0;
                prim->u1 = prim->u3 = 0x3F;
                prim->v0 = prim->v1 = 0xC0;
                prim->v2 = prim->v3 = 0xFF;
                prim->priority = self->zPriority - 1;
                prim->drawMode = DRAW_UNK_400 | DRAW_COLORS | DRAW_UNK02;
                prim->next->x1 = self->posX.i.hi;
                prim->next->y0 = self->posY.i.hi;
                LOH(prim->next->r2) = 0;
                LOH(prim->next->b2) = 0;
                prim->next->b3 = 0x40;
            } else {
                DestroyEntity(self);
                return;
            }

            for (i = 5; i >= 0; i--) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(0x2E, self, entity);

                    posX = D_us_801822E4[i].x;
                    posY = D_us_801822E4[i].y;
                    posX += 0x10;
                    posY += 0x14;
                    if (self->facingLeft) {
                        posX = -posX;
                    }
                    posX = entity->posX.i.hi += posX;
                    posY = entity->posY.i.hi += posY;
                    entity->params = i;
                    entity->facingLeft = self->facingLeft;
                    entity->ext.discusLord.entity = self;
                    entity->step = 0x11;
                    entity->flags |= FLAG_UNK_2000;
                }
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(6, entity);
                    entity->posX.i.hi = posX;
                    entity->posY.i.hi = posY;
                }
            }

            self->animCurFrame = 0;
            PlaySfxPositional(0x764);
            PlaySfxPositional(0x6C2);
            self->step_s++;
            // fallthrough
        case 1:
            prim = self->ext.discusLord.prim;
            LOH(prim->next->r2) += 3;
            LOH(prim->next->b2) = LOH(prim->next->r2);
            UnkPrimHelper(prim);
            if (LOH(prim->next->r2) > 0x60) {
                self->ext.discusLord.unk82 = 0x60;
                self->step_s++;
            }
            break;
        case 2:
            if (!--self->ext.discusLord.unk82) {
                self->ext.discusLord.unk82 = 0x20;
                self->step_s++;
            }
            break;
        case 3:
            prim = self->ext.discusLord.prim;
            LOH(prim->next->r2)--;
            LOH(prim->next->b2) = LOH(prim->next->r2);
            UnkPrimHelper(prim);
            if (!--self->ext.discusLord.unk82) {
                self->step_s++;
            }
            break;
        case 4:
            prim = self->ext.discusLord.prim;
            UnkPrimHelper(prim);
            LOH(prim->next->r2) -= 4;
            LOH(prim->next->b2) += 4;

            if (LOH(prim->next->r2) < 0) {
                DestroyEntity(self);
                return;
            }
            break;
        }

        if (g_Timer % 2) {
            prim = self->ext.discusLord.prim;
            prim->clut--;
            if (prim->clut < 0x231) {
                prim->clut = 0x235;
            }
        }

        break;
    case 17:
        InitializeEntity(D_us_80181200);
        self->hitboxState = 0;
        self->flags &= ~(FLAG_UNK_20000000 | FLAG_UNK_200);
        self->flags |= FLAG_UNK_00200000 | FLAG_UNK_2000;
        self->drawFlags |= FLAG_DRAW_OPACITY | FLAG_DRAW_ROTATE;
        self->drawFlags |= FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        self->scaleX = 0x100;
        self->scaleY = 0x100;
        self->opacity = 0x80;
        self->animCurFrame = self->params + 0x11;
        entity = self->ext.discusLord.entity;
        self->ext.discusLord.angle =
            GetAngleBetweenEntitiesShifted(entity, self);
        sqrt = ((Random() & 3) + 1) << 0x4;
        self->ext.discusLord.unkA8 = (sqrt << 0x10) / 0x20;
        self->ext.discusLord.unkAC = self->ext.discusLord.unkA8 / 0x20;
        // fallthrough
    case 18:
        SetEntityVelocityFromAngle(
            self->ext.discusLord.angle, self->ext.discusLord.unkA8 >> 0xC);
        MoveEntity();
        self->ext.discusLord.unkA8 -= self->ext.discusLord.unkAC;
        if (self->ext.discusLord.unkA8 < 0) {
            self->step++;
        }
        break;
    case 19:
        entity = self->ext.discusLord.entity;
        posX = entity->posX.i.hi - self->posX.i.hi;
        posY = entity->posY.i.hi - self->posY.i.hi;
        sqrt = (posX * posX) + (posY * posY);
        sqrt = SquareRoot0(sqrt);
        var_s5 = GetAngleBetweenEntitiesShifted(self, entity);
        SetEntityVelocityFromAngle(var_s5, sqrt / 8);
        self->ext.discusLord.unk82 = ((Random() & 0xF) * 4) + 0x40;
        self->step++;
        // fallthrough
    case 20:
        MoveEntity();
        if (self->params % 2) {
            self->rotate -= 4;
        } else {
            self->rotate += 4;
        }
        self->opacity--;
        self->scaleX--;
        self->scaleY = self->scaleX;
        if (!--self->ext.discusLord.unk82) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(6, entity);
                entity->drawFlags |= FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
                entity->scaleX = entity->scaleY = self->scaleX;
                entity->drawFlags |= FLAG_DRAW_OPACITY;
                entity->opacity = 0x30;
                self->ext.discusLord.entity = entity;
                self->animCurFrame = 0;
                self->step++;
            } else {
                DestroyEntity(self);
                return;
            }
        }
        break;
    case 21:
        MoveEntity();
        entity = self->ext.discusLord.entity;
        entity->posX.i.hi = self->posX.i.hi;
        entity->posY.i.hi = self->posY.i.hi;
        entity->opacity--;
        entity->scaleX = entity->scaleY -= 4;
        if (!entity->opacity) {
            DestroyEntity(entity);
            DestroyEntity(self);
            return;
        }
        break;
    }

    var_s5 = self->animCurFrame;
    if (var_s5 < 8 || var_s5 == 0xE) {
        var_s5 = 0;
    } else {
        var_s5 = 1;
    }
    self->hitboxOffX = D_us_80182360[var_s5].x;
    self->hitboxOffY = D_us_80182360[var_s5].y;
    self->hitboxWidth = D_us_80182368[var_s5].x;
    self->hitboxHeight = D_us_80182368[var_s5].y;
}

void func_us_801CADC4(Primitive* prim) {
    u32 x;
    u32 y;

    switch (prim->g3) {
    case 0:
        prim->r0 = 0x80;
        prim->g0 = 0x80;
        prim->b0 = 0xC0;
        prim->drawMode = DRAW_UNK02;
        prim->x1 = 0;
        prim->y1 = 0;
        x = -g_CurrentEntity->velocityX / 2;
        LOW(prim->x2) = x;
        LOW(prim->x3) = -(0x40000 - abs(x));
        LOW(prim->x2) += 0x7000 - ((Random() & 7) << 0xD);
        LOW(prim->x3) += 0x7000 - ((Random() & 7) << 0xD);
        prim->g3 = 1;
        prim->r3 = 0x10;
        // fallthrough
    case 1:
#ifdef VERSION_US
        x = (prim->x0 << 0x10) + (u16)prim->x1;
#else
        x = (prim->x0 << 0x10) + prim->x1;
#endif
        x += LOW(prim->x2);
        prim->x0 = HIHU(x);
        prim->x1 = LOHU(x);

#ifdef VERSION_US
        y = (prim->y0 << 0x10) + (u16)prim->y1;
#else
        y = (prim->y0 << 0x10) + prim->y1;
#endif
        y += LOW(prim->x3);
        prim->y0 = HIH(y);
        prim->y1 = LOH(y);

        LOW(prim->x3) += 0x2000;
        prim->r0 -= 5;
        prim->g0 -= 5;
        prim->b0 -= 9;
        prim->r3 -= 1;
        if (!prim->r3) {
            prim->g3 = 0;
            prim->drawMode = DRAW_HIDE;
            prim->p3 = 0;
        }
        break;
    }
}

extern Primitive* FindFirstUnkPrim(Primitive* poly);
void func_us_801CAF68(Entity* self) {
    s32 primIndex;       // sp6C
    s32 sp68;            // sp68
    s32 sp64;            // sp64
    Primitive* prevPrim; // sp60
    Collider collider;   // sp3C
    Entity* player;      // sp38

    Primitive* prim; // s0
    s16 var_s1;      // s1
    Entity* parent;  // s2
    s16 posX;        // s3
    Entity* entity;  // s4
    s16 posY;        // s5
    s32 i;           // s6
    s16 var_s7;      // s7
    u8 var_s8;       // s8

    parent = self - 1;
    player = &PLAYER;
    self->facingLeft = parent->facingLeft;
    if (parent->entityId != 0x2E) {
        DestroyEntity(self);
        return;
    }

    if (self->flags & FLAG_DEAD) {
        MakeExplosions();
        DestroyEntity(self);
        return;
    }

    if (self->hitFlags & 0x80) {
        self->ext.discusLord.unk94 = 0x20;
    }

    if (self->ext.discusLord.unk94) {
        if (self->ext.discusLord.unk94 > 0x15) {
            self->palette = 0x21D;
        } else {
            self->palette = 0x224 - (self->ext.discusLord.unk94 / 3);
        }
        self->ext.discusLord.unk94--;
    } else {
        self->palette = 0x224;
    }

    if (!(--self->ext.discusLord.angle)) {
        self->ext.discusLord.angle = 4;
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(0x30, self, entity);
            entity->facingLeft = self->facingLeft;
            entity->rotate = self->rotate;
            entity->ext.discusLord.unk8C = self->ext.discusLord.unk8C;
            entity->ext.discusLord.unk94 = self->ext.discusLord.unk94;
            if (!self->ext.discusLord.unk98) {
                entity->params = 1;
            }
        }
    }

    self->ext.discusLord.unk9C = -0x100;
    if (self->facingLeft) {
        self->ext.discusLord.unk9C = 0x100;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018120C);
        self->hitboxOffX = 1;
        self->hitboxOffY = 1;
        self->zPriority = parent->zPriority + 1;
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->ext.discusLord.angle = 4;
        primIndex = g_api.func_800EDB58(PRIM_TILE_ALT, 0x3C);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.discusLord.unkA0 = prim;
            prim->type = PRIM_GT4;
            prim->tpage = 0x12;
            prim->clut = 0x22D;
            prim->u0 = prim->u2 = 0x6A;
            prim->u1 = prim->u3 = 0x7F;
            prim->v0 = prim->v1 = 0xD0;
            prim->v2 = prim->v3 = 0xDF;
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            self->ext.discusLord.prim = prim;

            while (prim != NULL) {
                prim->u0 = 1;
                prim->v0 = 1;
                prim->priority = 0xA8;
                prim->drawMode = DRAW_HIDE | DRAW_UNK02;
                prevPrim = prim;
                prim = prim->next;
            }

            self->ext.discusLord.unk90 = prevPrim;
        } else {
            DestroyEntity(self);
            entity = self - 1;
            DestroyEntity(entity);
            return;
        }
        entity = self + 1;
        CreateEntityFromEntity(0x31, self, entity);
        // fallthrough
    case 1:
        self->rotate += self->ext.discusLord.unk8C;
        self->ext.discusLord.unk8C = 0x180;
        var_s8 = parent->animCurFrame;
        self->posX.i.hi = parent->posX.i.hi;
        if (self->facingLeft) {
            self->posX.i.hi -= D_us_80182378[var_s8].x;
        } else {
            self->posX.i.hi += D_us_80182378[var_s8].x;
        }
        self->posY.i.hi = parent->posY.i.hi + D_us_80182378[var_s8].y;
        self->posX.val +=
            self->ext.discusLord.unk98 * rcos(self->ext.discusLord.unk96);
        self->posY.val -=
            self->ext.discusLord.unk98 * rsin(self->ext.discusLord.unk96);
        if (self->ext.discusLord.unk98 > 0x20) {
            self->ext.discusLord.unk98 -= 8;
        }
        if (self->ext.discusLord.unk98 < 0x20) {
            self->ext.discusLord.unk98 += 8;
        }

        self->ext.discusLord.unk96 += self->ext.discusLord.unk9C;
        if (self->ext.discusLord.unk80) {
            self->step_s = 0;
            self->step++;
        }
        break;
    case 2:
        self->rotate += self->ext.discusLord.unk8C;
        if (self->ext.discusLord.unk8C > 0x180) {
            self->ext.discusLord.unk8C -= 8;
        }

        switch (self->step_s) {
        case 0:
            LOW(self->ext.discusLord.entity) =
                player->posX.val - self->posX.val;
            self->ext.discusLord.unkA8 = self->posY.val - player->posY.val;
            if (LOW(self->ext.discusLord.entity) < 0) {
                LOW(self->ext.discusLord.entity) =
                    -LOW(self->ext.discusLord.entity);
            }
            if (LOW(self->ext.discusLord.entity) < 0x200000) {
                LOW(self->ext.discusLord.entity) = 0x200000;
            }
            if (self->ext.discusLord.unkA8 < 0x200000) {
                self->ext.discusLord.unkA8 = 0x200000;
            }
            if (self->ext.discusLord.unkA8 > 0x600000) {
                self->ext.discusLord.unkA8 = 0x600000;
            }

            LOH(self->ext.discusLord.unkAC) =
                abs(LOW(self->ext.discusLord.entity) / 2) >> 0x10;
            LOH(self->ext.discusLord.unkAC) = 0x40;
            self->velocityX = FIX(-6.0);
            self->velocityY = 0;
            // posX = ( - (LOH(self->ext.discusLord.unkAC) * 0x60000)) * 2;
            // posX = ;
            // posY = ;
            self->ext.discusLord.unk84 =
                -((LOW(self->ext.discusLord.entity) -
                   (LOH(self->ext.discusLord.unkAC) * 0x60000)) *
                  2 /
                  (LOH(self->ext.discusLord.unkAC) *
                   LOH(self->ext.discusLord.unkAC)));
            self->ext.discusLord.unk88 =
                -(self->ext.discusLord.unkA8 * 2) /
                (LOH(self->ext.discusLord.unkAC) *
                 LOH(self->ext.discusLord.unkAC));
            if (self->facingLeft) {
                self->velocityX = -self->velocityX;
                self->ext.discusLord.unk84 = -self->ext.discusLord.unk84;
            }
            self->ext.discusLord.unk82 = LOH(self->ext.discusLord.unkAC);
            PlaySfxPositional(0x66D);
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityX += self->ext.discusLord.unk84;
            self->velocityY += self->ext.discusLord.unk88;
            sp68 = self->velocityX;
            if (self->facingLeft) {
                sp68 = -sp68;
            }

            if (!--self->ext.discusLord.unk82) {
                self->step_s++;
                self->velocityX = 0;
                self->velocityY = 0;
                self->ext.discusLord.unk84 = 0;
                self->ext.discusLord.unk88 = 0x4000;
                if (self->facingLeft) {
                    self->ext.discusLord.unk84 = -self->ext.discusLord.unk84;
                }
            }
            break;
        case 2:
            MoveEntity();
            self->velocityX += self->ext.discusLord.unk84;
            self->velocityY += self->ext.discusLord.unk88;
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            if (posY >= parent->posY.i.hi) {
                posY += 0xC;
                g_api.CheckCollision(posX, posY, &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    PlaySfxPositional(0x640);
                    self->ext.discusLord.unk8E = 8;
                    self->ext.discusLord.unk8C = 0x300;
                    self->posY.i.hi += collider.unk18;
                    self->velocityY = -self->velocityY / 2;
                    self->ext.discusLord.unk9E = 4;
                    prim = self->ext.discusLord.unkA0;
                    prim->x3 = self->posX.i.hi;
                    if (self->facingLeft) {
                        prim->x2 = prim->x3 + 0x18;
                    } else {
                        prim->x2 = prim->x3 - 0x18;
                    }
                    prim->y2 = prim->y3 = self->posY.i.hi + 0xC;
                    prim->y2 += 0xC;
                    posX = prim->x2;
                    posY = prim->y2;
                    g_api.CheckCollision(posX, posY, &collider, 0);
                    if (collider.effects) {
                        prim->y2 += collider.unk18;
                    }
                    if (self->velocityY > FIX(-0.5)) {
                        self->ext.discusLord.unk84 = 0x2000;
                        self->ext.discusLord.unk88 = 0;
                        if (self->facingLeft) {
                            self->ext.discusLord.unk84 =
                                -self->ext.discusLord.unk84;
                        }
                        self->step_s++;
                    }
                }
            }
            break;
        case 3:
            UnkCollisionFunc2(D_us_80182370);
            if (!(g_Timer % 6)) {
                PlaySfxPositional(0x640);
            }
            self->velocityX += self->ext.discusLord.unk84;
            self->velocityY += self->ext.discusLord.unk88;
            self->ext.discusLord.unk8E = 0x10;
            self->ext.discusLord.unk9E = 1;
            prim = self->ext.discusLord.unkA0;
            prim->x3 = self->posX.i.hi;
            if (self->facingLeft) {
                prim->x2 = prim->x3 + 0x18;
            } else {
                prim->x2 = prim->x3 - 0x18;
            }
            prim->y2 = prim->y3 = self->posY.i.hi + 0xC;
            prim->y2 += 0xC;

            posX = prim->x2;
            posY = prim->y2;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                prim->y2 += collider.unk18;
            }

            posX = parent->posX.i.hi - self->posX.i.hi;
            if (abs(posX) < 0x48) {
                self->velocityX = FIX(1.5);
                if (self->facingLeft) {
                    self->velocityX = -self->velocityX;
                }
                self->velocityY = FIX(-6.0);
                self->ext.discusLord.unk80 = 0;
                PlaySfxPositional(0x62E);
                self->step_s++;
            }
            break;
        case 4:
            MoveEntity();
            self->velocityY += FIX(0.375);
            if (self->velocityY > 0) {
                posX = self->posX.i.hi - parent->posX.i.hi;
                posY = self->posY.i.hi - parent->posY.i.hi;
                var_s8 = parent->animCurFrame;
                if (self->facingLeft) {
                    posX += D_us_80182378[var_s8].x;
                } else {
                    posX -= D_us_80182378[var_s8].x;
                }
                posY -= D_us_80182378[var_s8].y;
                sp64 = (posX * posX) + (posY * posY);
                self->ext.discusLord.unk98 = SquareRoot0(sp64) * 0x10;
                self->ext.discusLord.unk96 = ratan2(-posY, posX);
                self->step_s = 0;
                self->step = 1;
            }
            break;
        }
        if (self->ext.discusLord.unk8E) {
            self->ext.discusLord.unk8E--;

            for (i = 0; i < 4; i++) {
                prim = self->ext.discusLord.prim;
                prim = FindFirstUnkPrim(prim);
                if (prim != NULL) {
                    prim->p3 = 2;
                    var_s1 = self->posX.i.hi;
                    if (self->velocityX > 0) {
                        var_s1 -= 8;
                    }
                    if (self->velocityX < 0) {
                        var_s1 += 8;
                    }
                    var_s7 = self->posY.i.hi + 0xC;
                    prim->x0 = var_s1;
                    prim->y0 = var_s7;
                }
            }
        }
        break;
    }

    prim = self->ext.discusLord.unkA0;
    if (self->ext.discusLord.unk9E) {
        self->ext.discusLord.unk9E--;
        prim->x0 = prim->x2;
        prim->x1 = prim->x3;
        if (!(g_Timer % 2)) {
            prim->y0 = prim->y1 = prim->y2 - 0x18;
        } else {
            prim->y0 = prim->y1 = prim->y2 - 0x10;
        }
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
    } else {
        prim->drawMode = DRAW_HIDE;
    }

    prim = self->ext.discusLord.prim;
    while (prim != NULL) {
        if (prim->p3) {
            func_us_801CADC4(prim);
        }
        prim = prim->next;
    }
    prim = self->ext.discusLord.unk90;
    prim->x0 = 0;
    prim->y0 = 0;
    prim->drawMode = DRAW_UNK02;
}

void func_us_801CBB24(Entity* self) {
    u16 var_v0;

    if (!self->step) {
        InitializeEntity(D_us_8018120C);
        self->hitboxState = 0;
        self->drawMode |= DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags |= FLAG_DRAW_OPACITY | FLAG_DRAW_ROTATE;
        self->opacity = 0x30;
        if (self->params) {
            self->opacity = 0x80;
        }
        if (self->ext.discusLord.unk94 > 0x15) {
            self->palette = 0x21D;
        } else {
            self->palette = 0x224 - (self->ext.discusLord.unk94 / 3);
        }
    }
    self->rotate += self->ext.discusLord.unk8C;
    self->opacity -= 4;
    if (self->opacity < 8) {
        DestroyEntity(self);
    }
}

void func_us_801CBC10(Entity* self) {
    Primitive* prim;
    Entity* parent;
    Entity* grandparent;
    u8 animFrame;
    s32 primIndex;

    parent = self - 1;
    grandparent = self - 2;
    if (!self->step) {
        InitializeEntity(D_us_8018120C);
        self->animCurFrame = 0xF;
        self->hitboxState = 0;
        self->zPriority = parent->zPriority + 1;
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.discusLord.prim = prim;
            PGREY(prim, 0) = 0;
            PGREY(prim, 1) = 0x40;
            prim->priority = self->zPriority - 2;
            prim->drawMode = DRAW_UNK02;
        } else {
            DestroyEntity(self);
            return;
        }
    }

    self->posX.i.hi = parent->posX.i.hi;
    self->posY.i.hi = parent->posY.i.hi;
    prim = self->ext.discusLord.prim;
    prim->x0 = self->posX.i.hi;
    prim->y0 = self->posY.i.hi;
    prim->x1 = grandparent->posX.i.hi;
    prim->y1 = grandparent->posY.i.hi;

    animFrame = grandparent->animCurFrame;
    if (grandparent->facingLeft) {
        prim->x1 -= D_us_801823B4[animFrame].x;
    } else {
        prim->x1 += D_us_801823B4[animFrame].x;
    }
    prim->y1 += D_us_801823B4[animFrame].y;
    if (!(g_Timer % 4)) {
        PGREY(prim, 0) = 0;
        PGREY(prim, 1) = 0x10;
    } else {
        PGREY(prim, 0) = 0x40;
        PGREY(prim, 1) = 0;
    }

    if (parent->entityId != 0x2F) {
        DestroyEntity(self);
    }
}
