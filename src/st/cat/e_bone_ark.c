// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

extern EInit D_us_80181188;
extern EInit D_us_80181194;
extern EInit D_us_801811A0;
extern EInit D_us_801811AC;
extern EInit D_us_801811B8;

static s16 D_us_80182234[] = {0, 22, 4, 0};
static s16 D_us_8018223C[] = {0, 22, 0, 4, 8, -4, -16, 0};
static u8 D_us_8018224C[] = {
    0x07, 0x01, 0x07, 0x02, 0x07, 0x03, 0x07, 0x02, 0x00, 0x00, 0x00, 0x00};
static u8 D_us_80182258[] = {
    0x02, 0x27, 0x02, 0x28, 0x02, 0x29, 0x02, 0x28, 0x02, 0x27,
    0x02, 0x28, 0x02, 0x29, 0x02, 0x28, 0x00, 0x00, 0x00, 0x00};
static u8 D_us_8018226C[] = {
    0x10, 0x01, 0x05, 0x05, 0x04, 0x06, 0x05, 0x07, 0x04, 0x08, 0x05, 0x09,
    0x04, 0x0A, 0x05, 0x0B, 0x05, 0x0C, 0x05, 0x0B, 0x51, 0x0C, 0xFF, 0x00};
static u8 D_us_80182284[] = {
    0x02, 0x15, 0x01, 0x19, 0x02, 0x16, 0x01, 0x19, 0x02, 0x17,
    0x01, 0x19, 0x02, 0x18, 0x01, 0x19, 0x00, 0x00, 0x00, 0x00};
static u8 D_us_80182298[] = {
    0x01, 0x1B, 0x01, 0x1C, 0x02, 0x1D, 0x03, 0x1E, 0x02, 0x1F,
    0x01, 0x20, 0x01, 0x21, 0x02, 0x22, 0x01, 0x23, 0x02, 0x24,
    0x01, 0x25, 0x01, 0x26, 0x00, 0x00, 0x00, 0x00};

void func_us_801C6360(Entity* self) {
    Primitive* prim; // s0
    Entity* entity;  // s2
    s32 i;           // s1
    s32 primIndex;   // s3
    s16 var_s4;      // s4

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801811B8);
        self->drawFlags |= FLAG_DRAW_ROTATE;
        if (self->params) {
            self->drawFlags |= FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
            self->scaleX = self->scaleY = 0;
            self->animCurFrame = 0x1A;
            self->palette = 0x8162;
            entity = self->ext.boneArk.entity;
            self->zPriority = entity->zPriority - 2;
            self->ext.boneArk.unk8C.i.lo = 8;
            self->step = 0x10;
        } else {
            self->palette = 0x8160;
            self->ext.boneArk.unk98 = 0x80000;
        }
        if (self->params) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        } else {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        }

        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.boneArk.prim = prim;
            while (prim != NULL) {
                UnkPolyFunc2(prim);
                prim->tpage = 0x1A;
                prim->u0 = 0;
                prim->u1 = 0x3F;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->v0 = 0xC0;
                prim->v1 = prim->v0;
                prim->v2 = 0xFF;
                prim->v3 = prim->v2;
                prim->next->x1 = self->posX.i.hi;
                prim->next->y0 = self->posY.i.hi;
                if (self->params) {
                    prim->clut = 0x19F;
                    prim->priority = self->zPriority - 1;
                    prim->drawMode =
                        DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
                    prim->next->b3 = 0xC0;
                    LOH(prim->next->r2) = 0x40;
                    LOH(prim->next->b2) = 0x40;
                    prim->next->x2 = 0;
                    prim->next->y2 = 0;
                    prim->p3 |= 0x10;
                } else {
                    prim->clut = 0x15F;
                    prim->priority = self->zPriority - 3;
                    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                     DRAW_UNK02 | DRAW_TRANSP;
                    prim->next->b3 = 0x80;
                    LOH(prim->next->r2) = 0;
                    LOH(prim->next->b2) = 0;
                }
                prim = prim->next;
                prim = prim->next;
            }
        } else {
            if (self->params) {
                entity = self->ext.boneArk.entity;
                entity->ext.boneArk.entity = NULL;
            }
            DestroyEntity(self);
            return;
        }

        break;
    case 1:
        AnimateEntity(D_us_80182284, self);
        MoveEntity();
        self->ext.boneArk.unk98 -= 0x4000;
        var_s4 = self->ext.boneArk.unk98 >> 0xC;
        self->velocityX = rcos(self->ext.boneArk.unk94) * var_s4;
        self->velocityY = -rsin(self->ext.boneArk.unk94) * var_s4;
        if (!self->ext.boneArk.unk98) {
            g_api.PlaySfx(0x65B);
            self->palette = 0x200;
            self->drawFlags |= FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
            self->scaleX = self->scaleY = 0;
            self->pose = 0;
            self->poseTimer = 0;
            self->step_s = 0;
            self->ext.boneArk.unk90 = 0;
            self->ext.boneArk.unk92 = 0x10;
            self->ext.boneArk.unk8C.i.lo = 0;
            self->step++;
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(0x3C, self, entity);
                entity->params = 1;
                entity->ext.boneArk.entity = self;
                self->ext.boneArk.entity = entity;
            } else {
                self->ext.boneArk.entity = NULL;
            }
        }
        break;
    case 2:
        self->rotate += 0x600;
        AnimateEntity(D_us_80182298, self);
        switch (self->step_s) {
        case 0:
            self->scaleX += 0x10;
            self->scaleY = self->scaleX;
            if (self->scaleX == 0xC0) {
                self->step_s++;
            }
            break;
        case 1:
            self->scaleX += 4;
            self->scaleY = self->scaleX;
            if (self->scaleX == 0x100) {
                self->step_s++;
            }
            break;
        case 2:
            prim = self->ext.boneArk.prim;
            if (self->ext.boneArk.unk8C.i.lo % 2) {
                self->scaleX -= 0x20;
            } else {
                self->scaleX += 0x20;
            }
            self->scaleY = self->scaleX;
            self->ext.boneArk.unk8C.i.lo++;
            if (!(self->ext.boneArk.unk8C.i.lo & 0xF)) {
                g_api.PlaySfx(0x665);
            }
            if (self->ext.boneArk.unk8C.i.lo > 0x40) {
                self->drawMode |= DRAW_TPAGE2 | DRAW_TPAGE;
                self->drawFlags |= FLAG_DRAW_OPACITY;
                self->opacity = 0xC0;
                self->step_s = 0;
                LOH(prim->next->r2) = 0x40;
                LOH(prim->next->b2) = 0x40;
                self->ext.boneArk.unk90++;
                self->hitboxState = 0;
                g_api.PlaySfx(0x684);
                self->step++;
            }
            break;
        }

        if (!self->ext.boneArk.unk92) {
            switch (self->ext.boneArk.unk90) {
            case 0:
                prim = self->ext.boneArk.prim;
                prim->next->x1 = self->posX.i.hi;
                prim->next->y0 = self->posY.i.hi;
                LOH(prim->next->r2) = 0x30;
                LOH(prim->next->b2) = 0x30;
                self->ext.boneArk.unk90++;
                break;
            case 1:
                prim = self->ext.boneArk.prim;
                LOH(prim->next->r2)++;
                LOH(prim->next->b2)++;
                if (LOH(prim->next->r2) > 0x40) {
                    self->hitboxState = 1;
                    self->ext.boneArk.unk90++;
                }
                break;
            case 2:
                if (!(g_Timer % 2)) {
                    LOH(prim->next->r2) = 0x40;
                    LOH(prim->next->b2) = 0x40;
                } else {
                    LOH(prim->next->r2) = 0x20;
                    LOH(prim->next->b2) = 0x20;
                }
                break;
            }
        } else {
            self->ext.boneArk.unk92--;
        }
        break;
    case 3:
        if (self->animCurFrame) {
            AnimateEntity(D_us_80182298, self);
        }
        self->opacity -= 4;
        self->scaleX += 0x20;
        self->scaleY -= 8;
        if (!self->opacity) {
            self->animCurFrame = 0;
        }

        prim = self->ext.boneArk.prim;
        switch (self->step_s) {
        case 0:
            if (!(g_Timer % 3)) {
                LOH(prim->next->r2)++;
                LOH(prim->next->b2)++;
                if (LOH(prim->next->r2) > 0x42) {
                    prim->next->b3 = 0x40;
                    prim->priority = self->zPriority;
                }

                if (LOH(prim->next->r2) == 0x48) {
                    self->step_s++;
                    self->ext.boneArk.unk8C.i.lo = 0x200;
                    if (self->ext.boneArk.entity != NULL) {
                        self->ext.boneArk.entity->step_s++;
                    }

                    prim = prim->next;
                    prim = prim->next;
                    i = 0;
                    while (prim != NULL) {
                        prim->u0 = 0x40;
                        prim->u1 = 0x7F;
                        prim->u2 = prim->u0;
                        prim->u3 = prim->u1;
                        prim->v0 = 0xC0;
                        prim->v1 = prim->v0;
                        prim->v2 = 0xFF;
                        prim->v3 = prim->v2;
                        LOH(prim->next->r2) = 0x40;
                        LOH(prim->next->b2) = 0x40;
                        prim->next->x2 = 0x1400 - (i << 9);
                        prim->next->y2 = 0x1400 - (i << 9);
                        prim->next->b3 = 0x80;
                        prim->next->x1 = self->posX.i.hi;
                        prim->next->y0 = self->posY.i.hi;
                        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE |
                                         DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
                        prim->p3 |= 0x30;
                        prim->next->y3 = i * 0x180;
                        prim->next->r3 = i;
                        LOHU(prim->next->u3) = i * 8;
                        prim = prim->next;
                        prim = prim->next;
                        i++;
                    }
                }
            }
            break;
        case 1:
            if (LOH(prim->next->r2)) {
                LOH(prim->next->r2) -= 2;
                LOH(prim->next->b2) -= 2;
            }

            prim = prim->next;
            prim = prim->next;
            while (prim != NULL) {
                if (!LOHU(prim->next->u3)) {
                    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                     DRAW_UNK02 | DRAW_TRANSP;
                    prim->next->x2 += 0x100;
                    prim->next->y2 += 0x100;
                    prim->next->b3 -= 4;
                    if (prim->next->r3 % 2) {
                        prim->next->x3 += 0x40;
                        prim->next->y3 += 0x80;
                        LOH(prim->next->tpage) += 0x20;
                    } else {
                        prim->next->x3 -= 0x40;
                        prim->next->y3 -= 0x80;
                        LOH(prim->next->tpage) -= 0x20;
                    }

                    if (!prim->next->b3) {
                        prim->drawMode = DRAW_HIDE;
                        LOHU(prim->next->u3)--;
                    }
                } else {
                    LOHU(prim->next->u3)--;
                }
                prim = prim->next;
                prim = prim->next;
            }

            if (!--self->ext.boneArk.unk8C.i.lo) {
                DestroyEntity(self);
                return;
            }
        }
        break;
    case 16:
        self->rotate += 2;
        switch (self->step_s) {
        case 0:
            if (!self->ext.boneArk.unk8C.i.lo) {
                self->scaleX += 0x10;
                self->scaleY = self->scaleX;
                if (self->scaleX == 0x100) {
                    self->step_s++;
                }
            } else {
                self->ext.boneArk.unk8C.i.lo--;
            }
        case 1:
            break;
        case 2:
            self->scaleX -= 0x10;
            self->scaleY -= 0x10;
            if (!self->scaleX) {
                self->animCurFrame = 0;
                self->drawFlags = FLAG_DRAW_DEFAULT;
                self->drawMode = DRAW_DEFAULT;
                self->step_s++;
            }
            break;
        case 3:
            prim = self->ext.boneArk.prim;
            prim->next->b3 -= 2;
            LOH(prim->next->tpage) += 0x128;
            if (!prim->next->b3) {
                DestroyEntity(self);
                return;
            }
            break;
        }

        if (self->step_s < 3) {
            prim = self->ext.boneArk.prim;
            prim->next->x2 = ((self->scaleX + 0x60) << 4);
            prim->next->y2 = ((self->scaleY + 0x60) << 4);
        }

        break;
    }

    prim = self->ext.boneArk.prim;
    while (prim != NULL) {
        if (prim->p3 & 8) {
            UnkPrimHelper(prim);
        }
        prim = prim->next;
    }
}

static void func_us_801C6F9C(Primitive* prim) {
    Pos pos; // sp18

    s32 dx;    // s0
    s32 dy;    // s1
    u8 var_s2; // s2

    switch (prim->p1) {
    case 0:
        var_s2 = (Random() & 0x1F);
        var_s2 = var_s2 + 0x70 + (g_CurrentEntity->rotate / 16);
        prim->x0 = g_CurrentEntity->posX.i.hi +
                   ((rcos((var_s2) * 0x10) * 0x78) >> 0xC);
        prim->y0 = g_CurrentEntity->posY.i.hi +
                   ((rsin((var_s2) * 0x10) * 0x78) >> 0xC);
        prim->x1 = prim->x0;
        prim->y1 = prim->y0;
        prim->x2 = 0;
        prim->y2 = 0;
        LOH(prim->u2) = 0;
        LOH(prim->u3) = 0;

        prim->r0 = 0x80;
        prim->g0 = 0x40;
        prim->b0 = 0x40;

        prim->r1 = 0x40;
        prim->g1 = 0x40;
        prim->b1 = 0x80;

        LOW(prim->u0) = 0;
        LOW(prim->u1) = 0;
        LOW(prim->r2) = 0;
        LOW(prim->x3) = 0;

        dx = (prim->x0 << 0x10) - g_CurrentEntity->posX.val;
        dy = (prim->y0 << 0x10) - g_CurrentEntity->posY.val;
        LOH(prim->r3) = ratan2(dy, -dx);
        prim->priority = g_CurrentEntity->zPriority - 2;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->b3 = 0x2C;
        prim->p1 = 1;
        break;
    case 1:
        dx = (LOW(prim->u0) >> 0xC) * rcos(LOH(prim->r3));
        dy = -(LOW(prim->u0) >> 0xC) * rsin(LOH(prim->r3));
        pos.x.i.hi = prim->x0;
        pos.x.i.lo = prim->x2;
        pos.y.i.hi = prim->y0;
        pos.y.i.lo = prim->y2;
        pos.x.val += dx;
        pos.y.val += dy;
        prim->x0 = pos.x.i.hi;
        prim->x2 = pos.x.i.lo;
        prim->y0 = pos.y.i.hi;
        prim->y2 = pos.y.i.lo;
        LOW(prim->r2) += 0x100;
        LOW(prim->u0) += LOW(prim->r2) * 8;
        if (LOW(prim->u0) > 0x72000) {
            LOW(prim->r2) = -LOW(prim->r2);
        }
        if (LOW(prim->u0) < 0) {
            LOW(prim->u0) = 0x8000;
            LOW(prim->u1) = 0x8000;
        }
        LOW(prim->r2) += 0x100;
        dx = prim->x0 - g_CurrentEntity->posX.i.hi;
        dy = prim->y0 - g_CurrentEntity->posY.i.hi;
        if (abs(dx) < 4 && abs(dy) < 4) {
            prim->p1 = 2;
        }
        // fallthrough
    case 2:
        dx = (LOW(prim->u1) >> 0xC) * rcos(LOH(prim->r3));
        dy = -(LOW(prim->u1) >> 0xC) * rsin(LOH(prim->r3));
        pos.x.i.hi = prim->x1;
        pos.x.i.lo = LOH(prim->u2);
        pos.y.i.hi = prim->y1;
        pos.y.i.lo = LOH(prim->u3);
        pos.x.val += dx;
        pos.y.val += dy;
        prim->x1 = pos.x.i.hi;
        LOH(prim->u2) = pos.x.i.lo;
        prim->y1 = pos.y.i.hi;
        LOH(prim->u3) = pos.y.i.lo;
        if (prim->b3 < 0x28) {
            LOW(prim->x3) += 0x100;
            LOW(prim->u1) += LOW(prim->x3) * 8;
            if (LOW(prim->u1) > 0x72000) {
                LOW(prim->x3) = -LOW(prim->x3);
            }
            if (LOW(prim->u1) < 0) {
                LOW(prim->u1) = 0x8000;
            }
        }

        prim->b3--;
        dx = prim->x1 - g_CurrentEntity->posX.i.hi;
        dy = prim->y1 - g_CurrentEntity->posY.i.hi;
        if (abs(dx) < 8 && abs(dy) < 8) {
            prim->drawMode = DRAW_HIDE;
            prim->p3 = 0;
        }

        if (!prim->b3) {
            prim->drawMode = DRAW_HIDE;
            prim->p3 = 0;
        }

        break;
    }
}

extern Primitive* FindFirstUnkPrim(Primitive* poly);
void func_us_801C7420(Entity* self) {
    Primitive* prim;
    Entity* entity;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801811AC);
        self->animCurFrame = 0x2A;
        self->palette = 0x8160;
        self->drawFlags =
            FLAG_DRAW_OPACITY | FLAG_DRAW_ROTATE | FLAG_DRAW_SCALEX;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->scaleX = 0x100;
        self->opacity = 0;
        self->hitboxState = 0;
        self->zPriority = self->ext.boneArk.entity->zPriority + 1;
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 0x10);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.boneArk.prim = prim;
            break;
        }

        entity = self->ext.boneArk.entity;
        entity->ext.boneArk.entity = NULL;
        DestroyEntity(self);
        break;
    case 1:
        entity = self->ext.boneArk.entity;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        self->rotate = entity->rotate;
        self->opacity++;
        if (!(g_Timer % 8)) {
            prim = self->ext.boneArk.prim;
            prim = FindFirstUnkPrim(prim);
            if (prim != NULL) {
                prim->p3 = 2;
                prim->p1 = 0;
            }
        }

        if (!(g_Timer & 0x1F)) {
            PlaySfxPositional(0x762);
        }

        prim = self->ext.boneArk.prim;
        while (prim != NULL) {
            if (prim->p3 & 2) {
                func_us_801C6F9C(prim);
            }
            prim = prim->next;
        }

        if (self->opacity > 0x78) {
            self->ext.boneArk.unk8C.i.lo = 0;
            self->step++;
        }
        break;
    case 2:
        entity = self->ext.boneArk.entity;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        self->rotate = entity->rotate;
        if (!self->step_s) {
            prim = self->ext.boneArk.prim;
            while (prim != NULL) {
                if (prim->p3 & 2) {
                    func_us_801C6F9C(prim);
                }
                prim = prim->next;
            }

            if (self->ext.boneArk.unk8C.i.lo++ > 0x20) {
                primIndex = self->primIndex;
                g_api.FreePrimitives(primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
                self->step_s++;
            }
        } else {
            self->opacity = 0x88;
        }
        break;
    case 3:
        self->scaleX += 4;
        self->opacity -= 4;
        if (self->opacity > 0xF0) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801C774C(Entity* self) {
    Entity* entity; // s0
    Entity* var_s1; // s1
    s16 angle;      // s2
    s16 dx;         // s4
    s16 dy;         // s3
    s32 primIndex;  // s5

    var_s1 = self - self->params;
    if (self->flags & 0x100 && self->step < 7) {
        PlaySfxPositional(0x683);
        self->animCurFrame = 0;
        self->hitboxState = 0;
        SetStep(7);
        var_s1->ext.boneArk.unk93 |= 1;
        if (self->flags & FLAG_HAS_PRIMS) {
            primIndex = self->primIndex;
            g_api.FreePrimitives(primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
        }

        if (self->ext.boneArk.entity != NULL) {
            entity = self->ext.boneArk.entity;
            DestroyEntity(entity);
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801811AC);
        self->ext.boneArk.unk80 = 0x800;
        self->zPriority = (self - self->params)->zPriority + 2;
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->ext.boneArk.unk82 = 8;
        break;
    case 1:
        self->ext.boneArk.unk80 += self->ext.boneArk.unk82;
        if (self->ext.boneArk.unk80 > (0x900 - var_s1->rotate)) {
            self->ext.boneArk.unk82 = -8;
        }

        if (self->ext.boneArk.unk80 < (0x6D0 - var_s1->rotate)) {
            self->ext.boneArk.unk82 = 8;
        }

        if (self->ext.boneArk.unk91) {
            self->ext.boneArk.unk8C.i.lo = 0x20;
            self->step_s = 0;
            self->step++;
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            entity = &PLAYER;
            dx = entity->posX.i.hi - self->posX.i.hi;
            dy = entity->posY.i.hi - self->posY.i.hi;
            dy -= 0x10;
            angle = ratan2(-dy, dx);
            angle += ROT(360);
            angle &= 0xF80;

            if (angle > (0xA00 - var_s1->rotate)) {
                angle = 0xA00 - var_s1->rotate;
            }
            if (angle < (0x500 - var_s1->rotate)) {
                angle = 0x500 - var_s1->rotate;
            }

            angle &= 0xF00;
            self->ext.boneArk.unk94 = angle;
            self->step_s++;
            break;
        case 1:
            if (self->ext.boneArk.unk80 == self->ext.boneArk.unk94) {
                if (!--self->ext.boneArk.unk8C.i.lo) {
                    self->step++;
                    self->animCurFrame = 0xF;
                    var_s1->ext.boneArk.unk90 |= 1;
                }
            } else if (self->ext.boneArk.unk80 > self->ext.boneArk.unk94) {
                self->ext.boneArk.unk80 -= 4;
            } else {
                self->ext.boneArk.unk80 += 4;
            }
            break;
        }
        break;
    case 3:
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(0x3D, self, entity);
            entity->ext.boneArk.entity = self;
            self->ext.boneArk.entity = entity;
        } else {
            self->ext.boneArk.entity = NULL;
        }
        self->step++;
        break;
    case 4:
        entity = self->ext.boneArk.entity;
        if (entity != NULL) {
            if (entity->opacity > 0x80) {
                var_s1->ext.boneArk.unk90 |= 8;
                self->step++;
            }
        } else {
            var_s1->ext.boneArk.unk90 |= 8;
            self->step++;
        }
        break;
    case 5:
        if (self->ext.boneArk.unk90) {
            g_api.PlaySfx(0x63D);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(0x3C, self, entity);
                entity->facingLeft = self->facingLeft;
                entity->ext.boneArk.unk94 = self->ext.boneArk.unk94;
                if (self->facingLeft) {
                    entity->posX.i.hi += 0x10;
                } else {
                    entity->posX.i.hi -= 0x10;
                }
            }
            var_s1->ext.boneArk.unk90 = 0;
            self->ext.boneArk.unk90 = 0;
            self->step_s = 0;
            self->step++;
            entity = self->ext.boneArk.entity;
            if (entity != NULL) {
                entity->step++;
            }
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            self->ext.boneArk.unk80 -= 0x30;
            if (self->ext.boneArk.unk80 < self->ext.boneArk.unk94 - 0x300) {
                self->step_s++;
            }
            break;
        case 1:
            self->ext.boneArk.unk80 += 0x18;
            if (self->ext.boneArk.unk80 > self->ext.boneArk.unk94 + 0x100) {
                self->animCurFrame = 0xE;
                self->step_s++;
            }
            break;
        case 2:
            self->ext.boneArk.unk80 -= 8;
            if (self->ext.boneArk.unk80 < 0x800 - var_s1->rotate) {
                self->step = 1;
                self->step_s = 0;
            }
            break;
        }
        break;
    case 7:
        switch (self->step_s) {
        case 0:
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(2, self, entity);
                entity->params = 1;
            }
            self->step_s++;
            break;
        case 1:
            self->ext.boneArk.unk80 += self->ext.boneArk.unk82;
            if (self->ext.boneArk.unk80 > (0xA00 - var_s1->rotate)) {
                self->ext.boneArk.unk82 = -0x30;
            }
            if (self->ext.boneArk.unk80 < (0x400 - var_s1->rotate)) {
                self->ext.boneArk.unk82 = 0x30;
            }
            break;
        }
        break;
    }
    self->rotate = 0x800 - self->ext.boneArk.unk80;
    entity = self - 1;
    dx = (rcos(self->ext.boneArk.unk80) * 2) >> 0xC;
    dy = (rsin(self->ext.boneArk.unk80) * 2) >> 0xC;
    self->posX.i.hi = entity->posX.i.hi + dx;
    self->posY.i.hi = entity->posY.i.hi - dy;
}

void func_us_801C7D98(Entity* self) {
    Entity* entity; // s0
    Entity* var_s1; // s1
    s16 posX;       // s3
    s16 posY;       // s2

    var_s1 = self - self->params;
    entity = self + 1;
    if (var_s1->ext.boneArk.unk93 && self->step < 2) {
        self->ext.boneArk.unk8C.i.lo = 8;
        self->step = 2;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801811A0);
        self->animCurFrame = 0x10;
        self->zPriority = (self - self->params)->zPriority + 1;
        // fallthrough
    case 1:
        if (self->params == 5) {
            entity = self - self->params;
        } else {
            entity = self - 1;
        }
        posX = (rcos(self->ext.boneArk.unk80) * 4) >> 0xC;
        posY = (rsin(self->ext.boneArk.unk80) * 4) >> 0xC;
        self->posX.i.hi = entity->posX.i.hi + posX;
        self->posY.i.hi = entity->posY.i.hi - posY;
        break;
    case 2:
        if (!self->ext.boneArk.unk8C.i.lo) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(2, self, entity);
                entity->params = 0;
                entity->drawFlags |= FLAG_DRAW_ROTATE;
                entity->rotate = self->ext.boneArk.unk80 - 0x400;
            }
            self->animCurFrame = 0;
            self->flags |= FLAG_DEAD;
            self->step_s++;
            if (self->step_s > 3) {
                // BUG: double assign to same field
                self->step = 1;
                self->step = 3;
            }
        } else {
            self->ext.boneArk.unk8C.i.lo--;
        }
        break;
    case 3:
        break;
    }
}

void func_us_801C7F84(Entity* self) {
    Entity* parent; // s1
    s32 dx;         // s2
    s32 dy;         // s0
    s16 angle;      // s3
    s32 xOffset;    // s5
    s32 yOffset;    // s4

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801811A0);
        self->animCurFrame += self->params - 1;
        // fallthrough
    case 1:
        parent = self - 1;
        dx = self->posX.val - parent->posX.val;
        dy = parent->posY.val - self->posY.val;
        xOffset = dx;
        yOffset = dy;
        dy -= 0x18000;
        dy -= (parent->ext.boneArk.unk8C.val << 8) >> 8;
        dx += (parent->ext.boneArk.unk88.val << 8) >> 8;

        angle = ((dx >> 0x10) * dx + (dy >> 0x10) * dy) >> 0x10;
        if (angle > 0x24) {
            angle = ratan2(dy, dx);
            dx = rcos(angle) * 4 * 16;
            dy = rsin(angle) * 4 * 16;
        }
        self->posX.val = parent->posX.val + dx;
        self->posY.val = parent->posY.val - dy;
        self->ext.boneArk.unk88.val = -(dx - xOffset);
        self->ext.boneArk.unk8C.val = -(yOffset - dy);
        break;
    }
}

static void func_us_801C80E0(Primitive* prim) {
    Entity* newEntity;

    switch (prim->next->u2) {
    case 0:
        LOW(prim->next->u0) = (prim->next->r3 % 2) * 0x18000 - 0x8000 - 0x4000;
        LOW(prim->next->u0) += ((Random() & 3) << 0xD) - 0x4000;
        LOW(prim->next->r1) = -0x40000;
        LOW(prim->next->r1) -= (prim->next->r3 >> 1) << 0xD;
        LOW(prim->next->r1) += ((Random() & 3) << 0xE) - 0x8000;
        prim->next->u2 = 1;
        break;
    case 1:
        UnkPrimHelper(prim);
        if (prim->next->r3 % 2) {
            LOH(prim->next->tpage) += 0xD0 - ((prim->next->r3 >> 1) * 0x60);
            prim->next->x3 += ((Random() & 3) * 0x10) + 0x100;
            prim->next->y3 += ((Random() & 3) * 0x10) + 0x20;
        } else {
            LOH(prim->next->tpage) -= 0xD0 - ((prim->next->r3 >> 1) * 0x60);
            prim->next->x3 -= ((Random() & 3) * 0x10) + 0x100;
            prim->next->y3 -= ((Random() & 3) * 0x10) + 0x20;
        }

        LOW(prim->next->r1) += 0x3000 - ((prim->next->r3 >> 1) << 0xC);
        if (LOW(prim->next->r1) > ((prim->next->r3 >> 1) << 0xF) + 0x34000) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(2, newEntity);

                if (prim->next->r3 >> 1) {
                    newEntity->params = 2;
                } else {
                    newEntity->params = 3;
                }

                newEntity->facingLeft = prim->next->r3 % 2;
                newEntity->posX.i.hi = prim->next->x1;
                newEntity->posY.i.hi = prim->next->y0;
            }
            UnkPolyFunc0(prim);
        }
        break;
    }
}

extern Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index);
void func_us_801C839C(Entity* self) {
    s16 xOffset; // sp3E
    s16 yOffset; // sp3C

    Primitive* prim; // s0
    s32 i;           // s1
    Entity* entity;  // s2
    s16 var_s3;      // s3
    s16 angle;       // s4
    u8 var_s5;       // s5
    s32 primIndex;   // s6
    s32 dx;          // s8
    s32 dy;          // s7
    s32 pad[9];

    FntPrint("main_step %x\n", self->step);
    FntPrint("main_step_s %x\n", self->step_s);
    FntPrint("hd_flag %x\n", self->ext.boneArk.unk93);
    if (self->ext.boneArk.unk93 && self->step < 8) {
        SetStep(8);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80181188);
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->hitboxState = 0;
        self->rotate = 0;
        self->animCurFrame = 0xD;

        entity = self - 1;
        CreateEntityFromEntity(0x38, self, entity);
        entity->posX.i.hi -= 0x18;
        entity->params = 1;
        entity->ext.boneArk.posX = entity->posX.i.hi;
        entity->ext.boneArk.posY = entity->posY.i.hi - 0x14;

        entity = self - 2;
        CreateEntityFromEntity(0x38, self, entity);
        entity->posX.i.hi += 0x16;
        entity->params = 2;
        entity->ext.boneArk.posX = entity->posX.i.hi;
        entity->ext.boneArk.posY = entity->posY.i.hi - 0x14;

        for (i = 1; i < 5; i++) {
            entity = &self[i];
            CreateEntityFromEntity(0x39, self, entity);
            entity->params = i;
        }

        for (i = 5; i < 9; i++) {
            entity = &self[i];
            CreateEntityFromEntity(0x3A, self, entity);
            entity->params = i;
        }

        entity = self + 9;
        CreateEntityFromEntity(0x3B, self, entity);
        entity->params = 9;
        self->ext.boneArk.unk88.i.lo = 0x400;
        self->ext.boneArk.unk82 = -0x18;
        self->ext.boneArk.unk8C.i.lo = 0x100;
        self->step_s = 1;
        // fallthrough
    case 1:
        entity = &PLAYER;
        if (!self->step_s) {
            self->ext.boneArk.unk8C.i.lo = 0x80;
            (self - 1)->step_s &= 0x10;
            (self - 2)->step_s &= 0x10;
            if (entity->posX.i.hi > self->posX.i.hi) {
                self->ext.boneArk.unkA0 = 1;
            } else {
                self->ext.boneArk.unkA0 = 0;
            }
            self->step_s++;
        }

        angle = self->posX.i.hi - entity->posX.i.hi;
        if ((u16)angle < 0x40) {
            (self - 1)->step_s &= 0x10;
            (self - 2)->step_s &= 0x10;
            self->ext.boneArk.unkA0 = 1;
        }

        self->ext.boneArk.unk88.i.lo += self->ext.boneArk.unk82;
        if (self->ext.boneArk.unk88.i.lo > 0x800 - self->rotate) {
            self->ext.boneArk.unk82 = -0x18;
        }

        if (self->ext.boneArk.unk88.i.lo < -self->rotate) {
            self->ext.boneArk.unk82 = 0x18;
        }

        if (!--self->ext.boneArk.unk8C.i.lo) {
            self->step_s = 0;
            if ((u16)angle < 0xC0) {
                self->step++;
                (self - 1)->ext.boneArk.unk91 = 1;
                (self - 2)->ext.boneArk.unk91 = 1;
                (self + 9)->ext.boneArk.unk91 = 1;
            }
        }

        break;
    case 2:
        angle = self->ext.boneArk.unk88.i.lo - (0x800 - self->rotate);
        if (abs(angle) < 8) {
            self->ext.boneArk.unk90 |= 1;
            self->step++;
        } else if (self->ext.boneArk.unk88.i.lo > (0x800 - self->rotate)) {
            self->ext.boneArk.unk88.i.lo -= 8;
        } else {
            self->ext.boneArk.unk88.i.lo += 8;
        }

        break;
    case 3:
        if (self->ext.boneArk.unk90 == 0xF) {
            (self - 1)->ext.boneArk.unk91 = 0;
            (self - 2)->ext.boneArk.unk91 = 0;
            (self + 9)->ext.boneArk.unk91 = 0;
            (self + 9)->ext.boneArk.unk90 = 1;
            self->step_s = 0;
            self->step++;
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            if (!self->ext.boneArk.unk90) {
                self->ext.boneArk.unk88.i.lo -= 0x80;
                if (self->ext.boneArk.unk88.i.lo < -self->rotate) {
                    self->step_s++;
                }
            }
            break;
        case 1:
            self->ext.boneArk.unk88.i.lo += 8;
            if (self->ext.boneArk.unk88.i.lo > (0x400 - self->rotate)) {
                self->step_s++;
            }
            break;
        case 2:
            self->step_s = 0;
            self->step = 1;
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            self->ext.boneArk.unk88.i.lo += self->ext.boneArk.unk82;
            if (self->ext.boneArk.unk88.i.lo > 0xA00) {
                self->ext.boneArk.unk82 = -0x40;
            }

            if (self->ext.boneArk.unk88.i.lo < 0x100) {
                self->ext.boneArk.unk82 = 0x40;
            }

            entity = self + 5;
            if (entity->step == 3) {
                self->step_s++;
            }
            break;
        case 1:
            PlaySfxPositional(0x684);
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(2, self, entity);
                entity->params = 1;
            }

            (self - 1)->ext.boneArk.unk90 = 0xFF;
            (self - 2)->ext.boneArk.unk90 = 0xFF;
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
            if (primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                self->ext.boneArk.prim = prim;

                for (i = 0; i < 4; i++) {
                    prim = self->ext.boneArk.prim;
                    prim = FindFirstUnkPrim2(prim, 2);
                    if (prim != NULL) {
                        UnkPolyFunc2(prim);
                        prim->tpage = 0x12;
                        prim->clut = 0x200;
                        prim->u0 = (i % 2) * 0x28 + 0x30;
                        prim->u1 = prim->u0 + 0x28;
                        prim->u2 = prim->u0;
                        prim->u3 = prim->u1;
                        prim->v0 = (i >> 1) * 0xC;
                        prim->v1 = prim->v0;
                        prim->v2 = prim->v0 + 0xC;
                        prim->v3 = prim->v2;
                        prim->next->x1 = self->posX.i.hi;
                        prim->next->y0 = self->posY.i.hi;
                        prim->next->b3 = 0x80;
                        prim->next->tpage = self->rotate;
                        prim->next->r3 = i;
                        LOH(prim->next->r2) = 0x28;
                        LOH(prim->next->b2) = 0xC;
                        prim->priority = self->zPriority;
                        prim->drawMode = DRAW_UNK02;
                        // nb. this looks like a copy paste mistake
                        // this is overwritten by the loop iteration
                        prim = prim->next;
                    }
                }
            } else {
                self->ext.boneArk.prim = NULL;
            }

            for (i = 1; i < 10; i++) {
                entity = &self[i];
                DestroyEntity(entity);
            }

            self->animCurFrame = 0;
            self->step_s++;
            break;
        case 2:
            var_s5 = 0;
            prim = self->ext.boneArk.prim;
            while (prim != NULL) {
                if (prim->p3 & 8) {
                    var_s5 |= 1;
                    func_us_801C80E0(prim);
                }
                prim = prim->next;
            }

            if (!var_s5) {
                PreventEntityFromRespawning(self);
                DestroyEntity(self);
                return;
            }

            break;
        }
        break;
    case 16:
#include "../pad2_anim_debug.h"
    }

    xOffset =
        (((self - 1)->ext.boneArk.posX + (self - 2)->ext.boneArk.posX) / 2) + 3;
    yOffset = ((self - 1)->ext.boneArk.posY + (self - 2)->ext.boneArk.posY) / 2;
    self->posX.i.hi = xOffset;
    self->posY.i.hi = yOffset;
    dx = (self - 2)->ext.boneArk.posX - (self - 1)->ext.boneArk.posX;
    dy = (self - 2)->ext.boneArk.posY - (self - 1)->ext.boneArk.posY;
    angle = ratan2(dy, dx);
    self->rotate = angle;

    var_s3 = self->ext.boneArk.unk88.i.lo;
    angle = -self->rotate;
    angle = (var_s3 - angle) / 4;
    for (i = 5; i < 7; i++) {
        entity = &self[i];
        var_s3 = var_s3 - angle;
        entity->ext.boneArk.unk80 = var_s3 + self->rotate;
    }

    var_s3 = -self->rotate;
    angle = ((self + 9)->ext.boneArk.unk80 - var_s3) / 3;
    for (i = 7; i < 9; i++) {
        entity = &self[i];
        var_s3 = var_s3 + angle;
        entity->ext.boneArk.unk80 = var_s3 + self->rotate;
    }
}

// nb. This must be defined after pad2_anim_debug.h to align PSP data
static s16 D_us_801822B4[] = {
    10, -20, -21, -22, -8, -20, -19, -8, -6, 0, 4, 8, 10, 0, 0, 0};

void func_us_801C8CE0(Entity* self) {
    Entity* entity;       // s0
    Entity* paramsEntity; // s1
    Entity* newEntity;    // s2
    u8 collisionDetected; // s3

    paramsEntity = &self[self->params];
    if (self->params == 1) {
        entity = self - 1;
    } else {
        entity = self + 1;
    }

    if (self->ext.boneArk.unk90 == 0xFF) {
        if (!(self->flags & FLAG_DEAD)) {
            self->facingLeft = GetSideToPlayer() & 1;
            SetStep(5);
            self->hitboxHeight = 0x12;
            self->hitboxOffY = 0;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        }
    }

    if (self->flags & 0x100 && self->step < 6) {
        PlaySfxPositional(0x6CB);
        self->hitboxState = 0;
        self->ext.boneArk.unk8C.i.hi = 0;
        self->velocityX = 0;
        entity->velocityX = 0;
        entity->step_s |= 0x10;
        if (!self->ext.boneArk.unk92) {
            entity->ext.boneArk.unk92 = 1;
        }
        SetStep(6);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80181194);
        self->zPriority = paramsEntity->zPriority + 1 - self->params;
        // fallthrough
    case 1:
        if (UnkCollisionFunc3(D_us_8018223C) & 1) {
            self->pose = self->params;
            self->step++;
        }
        break;
    case 2:
        if (!self->step_s) {
            if (paramsEntity->ext.boneArk.unkA0) {
                self->velocityX = FIX(0.375);
            } else {
                self->velocityX = FIX(-0.375);
            }

            if (self->ext.boneArk.unk92) {
                self->velocityX /= 2;
            }

            if (self->params == 2) {
                entity->step_s = 0;
            }
            self->step_s++;
        }

        AnimateEntity(D_us_8018224C, self);
        collisionDetected = UnkCollisionFunc2(D_us_80182234);
        if (collisionDetected & 0x80) {
            if (self->params == 1) {
                entity->posX.val -= entity->velocityX;
            } else {
                entity->step_s |= 0x10;
            }
            entity->velocityX = 0;
            self->step_s &= 0x10;
            entity->step_s &= 0x10;
            paramsEntity->ext.boneArk.unkA0 ^= 1;
        }

        if (self->ext.boneArk.unk91) {
            self->velocityX = 0;
            SetStep(3);
        }

        break;
    case 3:
        switch (self->step_s) {
        case 0:
            self->ext.boneArk.unk8C.i.lo = self->params * 0x10;
            self->step_s++;
            // fallthrough
        case 1:
            if (!--self->ext.boneArk.unk8C.i.lo) {
                self->hitboxHeight = 0xE;
                self->hitboxOffY = 7;
                self->animCurFrame = 4;
                self->ext.boneArk.unk8C.i.hi = 0xD;
                self->step_s++;
            }
            break;
        case 2:
            if (!self->ext.boneArk.unk8C.i.hi) {
                paramsEntity->ext.boneArk.unk90 |= 1 << self->params;
                SetStep(4);
            } else {
                self->ext.boneArk.unk8C.i.hi--;
            }
            break;
        }
        break;
    case 4:
        if (paramsEntity->step == 1) {
            self->hitboxHeight = 0x12;
            self->hitboxOffY = 0;
            SetStep(1);
        }
        break;
    case 5:
        self->ext.boneArk.unk90 = 0;
        switch (self->step_s) {
        case 16:
        case 0:
            collisionDetected = UnkCollisionFunc2(D_us_80182234);
            if (!AnimateEntity(D_us_80182258, self)) {
                self->facingLeft = GetSideToPlayer() & 1;
            }

            if (collisionDetected == 0xFF) {
                self->facingLeft ^= 1;
                self->pose = 0;
                self->poseTimer = 0;
            }

            if (collisionDetected == 0x80) {
                PlaySfxPositional(0x6BE);
                self->velocityY = FIX(-4.0);
                self->step_s++;
            }

            if (self->facingLeft) {
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = FIX(-1.5);
            }
            break;
        case 17:
        case 1:
            if (UnkCollisionFunc3(D_us_8018223C) & 1) {
                self->step_s--;
            }
            break;
        }
        break;
    case 6:
        if (!AnimateEntity(D_us_8018226C, self)) {
            PlaySfxPositional(0x694);
            self->animCurFrame = 0;
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(2, self, newEntity);
                newEntity->posY.i.hi += 0xA;
                newEntity->params = 2;
            }
            entity->step_s = 0;
            self->step++;
        }
        break;
    case 7:
        UnkCollisionFunc2(D_us_80182234);
        self->velocityX = entity->velocityX;
        if (self->ext.boneArk.unk91) {
            paramsEntity->ext.boneArk.unk90 |= 1 << self->params;
            self->ext.boneArk.unk91 = 0;
        }

        if (paramsEntity->entityId != 0x37) {
            DestroyEntity(self);
            return;
        }

        break;
    }

    self->ext.boneArk.posX = self->posX.i.hi;
    self->ext.boneArk.posY =
        (self->posY.i.hi + D_us_801822B4[self->animCurFrame]) -
        self->ext.boneArk.unk8C.i.hi;
}
