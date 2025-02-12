// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

static s32 D_us_80181570 = 0;
static s16 D_us_80181574[] = {0x80, 0x80, 0x100, 0x300, 0x500, 0x700};
static s16 D_us_80181580[] = {0xC, 0xC, 0x12, 0x16, 0x20, 0x26};
static s16 D_us_8018158C[] = {0x100, 0x100, 0xF8, 0xF2, 0xEE, 0xEC};
static u8 D_us_80181598[] = {0x01, 0x62, 0x01, 0x63, 0x00, 0x00, 0x00, 0x00};
static u8 D_us_801815A0[] = {0x01, 0x64, 0x01, 0x65, 0x00, 0x00, 0x00, 0x00};
static u8 D_us_801815A8[] = {0x02, 0x62, 0x02, 0x63, 0x00, 0x00, 0x00, 0x00};
static u8 D_us_801815B0[] = {0x02, 0x64, 0x02, 0x65, 0x00, 0x00, 0x00, 0x00};
static s16 D_us_801815B8[] = {
    0x000, 0x600, 0xE00, 0x100, 0x800, 0xA00, 0x200, 0x400, 0xC00, 0x000};
static s16 D_us_801815CC[] = {4, 8, 13, -24, -20, -12, 21, -12, 2, 0};
static s16 D_us_801815E0[] = {20, 8, 12, 13, 16, 6, 12, 16, 8, 4};

extern s32 D_psp_0929A6C0;
extern s32 D_psp_0929A6B0;
extern s32 D_psp_0929A6A8;

void func_us_801BD8AC(Entity* self) {
    Entity* tempEntity;
    s32 i;

    switch (self->step) {
    case 0:

        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        self->animCurFrame = 0;
        tempEntity = self + 1;
        for (i = 1; i < 6; i++) {
#ifdef VERSION_PSP
            CreateEntityFromEntity(D_psp_0929A6C0, self, tempEntity);
#else
            CreateEntityFromEntity(E_ID_36, self, tempEntity);
#endif
            tempEntity->params = i + 0x100;
            tempEntity++;
#ifdef VERSION_PSP
            CreateEntityFromEntity(D_psp_0929A6C0, self, tempEntity);
#else
            CreateEntityFromEntity(E_ID_36, self, tempEntity);
#endif
            tempEntity->params = i;
            tempEntity++;
        }
#ifdef VERSION_PSP
        CreateEntityFromEntity(D_psp_0929A6B0, self, tempEntity);
        tempEntity++;
        CreateEntityFromEntity(D_psp_0929A6A8, self, tempEntity);
#else
        CreateEntityFromEntity(E_ID_38, self, tempEntity);
        tempEntity++;
        CreateEntityFromEntity(E_ID_39, self, tempEntity);
#endif
        break;

    case 1:
        if (D_us_80181570 & 1) {
            self->step += 2;
        }
        break;

    case 2:
        if (!--self->ext.et_801BDA0C.unk9C) {
            self->step++;
        }
        break;

    case 3:
        tempEntity = self + 1;
        tempEntity->ext.et_801BDA0C.unk84 = 1;
        tempEntity++;
        tempEntity->ext.et_801BDA0C.unk84 = 1;
        self->step++;
        break;
    }
}

void func_us_801BDA0C(Entity* self) {
    s32 flag;
    s32 primIndex;
    s16 xOffset, yOffset;
    s16 magnitude;
    Entity* tempEntity;
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801809C8);
        self->drawFlags |=
            FLAG_DRAW_UNK8 | FLAG_DRAW_ROTZ | FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
        if ((self->params & 0xF) > 1) {
            self->unk6C = 0x20;
        } else {
            self->unk6C = 0x80;
        }
        self->rotX = D_us_8018158C[self->params & 0xF];
        self->rotY = self->rotX;
        if ((self->params & 0xF) % 2) {
            self->rotZ = -0x400;
        } else {
            self->rotZ = 0;
        }
        self->zPriority = (0x40 - self->params) & 0xF;
        if (self->params & 0x100) {
            self->animCurFrame = 0x64;
        } else {
            self->animCurFrame = 0x62;
        }
        primIndex = g_api.AllocPrimBuffers(PRIM_TILE, 1);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801BDA0C.unk7C = prim;
            prim->x0 = self->posX.i.hi;
            prim->y0 = self->posY.i.hi;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        } else {
            DestroyEntity(self);
            return;
        }
        self->ext.et_801BDA0C.unk84 = 0;
        self->ext.et_801BDA0C.unk80 = 0;
        break;
    case 1:
        self->palette = 0x804F;
        if (self->ext.et_801BDA0C.unk84) {
            self->step++;
        }
        break;

    case 2:
        flag = self->params & 0xFF;
        if (flag != 1) {
            self->step++;
        } else {
            if (self->params & 0x100) {
                AnimateEntity(D_us_801815A0, self);
            } else {
                AnimateEntity(D_us_80181598, self);
            }
            if ((g_Timer & 0xF) == 0) {
                g_api.PlaySfx(SFX_STONE_MOVE_B);
            }
            if (D_us_80181570 & 8) {
                self->step++;
            }
        }
        break;

    case 3:
        if (g_Timer % 2 == 0) {
            self->palette++;
            if (self->palette > 0x8058) {
                g_api.PlaySfx(SFX_ELECTRICITY);
                self->palette = 0x804F;
                self->step++;
                if (self->params == 5) {
                    (self + 1)->ext.et_801BDA0C.unk84 = 1;
                }
            }
        }
        break;

    case 4:
        magnitude = self->ext.et_801BDA0C.unk80 / 0x10000;
        xOffset = (rcos(self->rotZ - 0x400) * magnitude) >> 0xC;
        yOffset = (rsin(self->rotZ - 0x400) * magnitude) >> 0xC;
        prim = self->ext.et_801BDA0C.unk7C;
        self->posX.i.hi = prim->x0 + xOffset;
        self->posY.i.hi = prim->y0 + yOffset;
        if (self->params & 0x100) {
            AnimateEntity(D_us_801815A0, self);
        } else {
            AnimateEntity(D_us_80181598, self);
        }
        if ((g_Timer & 0xF) == 0) {
            g_api.PlaySfx(SFX_STONE_MOVE_B);
        }
        if (self->params & 0x100) {
            self->ext.et_801BDA0C.unk88 -= D_us_80181574[self->params & 0xF];
        } else {
            self->ext.et_801BDA0C.unk88 += D_us_80181574[self->params & 0xF];
        }
        self->ext.et_801BDA0C.unk80 += self->ext.et_801BDA0C.unk88;
        if (abs(self->ext.et_801BDA0C.unk80) > FIX(12)) {
            (self + 2)->ext.et_801BDA0C.unk84 = 1;
            self->step++;
            if (self->params == 5) {
                (self + 1)->ext.et_801BDA0C.unk84 = 1;
            }
        }
        tempEntity = self + 2;
        if (tempEntity->unk6C < 0x80) {
            tempEntity->unk6C++;
        }
        break;

    case 5:
        tempEntity = self + 2;
        if (tempEntity->unk6C < 0x80) {
            tempEntity->unk6C += 2;
        }
        magnitude = self->ext.et_801BDA0C.unk80 / 0x10000;
        xOffset = (rcos(self->rotZ - 0x400) * magnitude) >> 0xC;
        yOffset = (rsin(self->rotZ - 0x400) * magnitude) >> 0xC;
        prim = self->ext.et_801BDA0C.unk7C;
        self->posX.i.hi = prim->x0 + xOffset;
        self->posY.i.hi = prim->y0 + yOffset;
        if (self->params & 0x100) {
            AnimateEntity(D_us_801815B0, self);
        } else {
            AnimateEntity(D_us_801815A8, self);
        }
        self->rotZ += D_us_80181580[self->params & 0xF];
        if (self->params & 0x100) {
            self->ext.et_801BDA0C.unk88 -= D_us_80181574[self->params & 0xF];
        } else {
            self->ext.et_801BDA0C.unk88 += D_us_80181574[self->params & 0xF];
        }
        self->ext.et_801BDA0C.unk80 += self->ext.et_801BDA0C.unk88;
        if (self->ext.et_801BDA0C.unk80 > FIX(64)) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801BDF9C(Entity* self) {
    Primitive* prim;
    s32 i;
    s32 primIndex;
    s16 posX, posY;
    s16 xOffset;
    Primitive* lastPrim;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        break;

    case 1:
        if (self->ext.et_801BE2C8.unk84) {
            self->step++;
            self->ext.et_801BE2C8.unk84 = 0;
        }
        break;

    case 2:
        primIndex = g_api.AllocatePrimitives(PRIM_TILE_ALT, 0x30);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801BE2C8.unk7C = prim;
            while (prim != NULL) {
                prim->r0 = prim->g0 = prim->b0 = 8;
                prim->priority = 0xD0;
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                lastPrim = prim;
                prim = prim->next;
            }
            self->ext.et_801BE2C8.unk80 = lastPrim;
        } else {
            DestroyEntity(self);
            return;
        }
        self->step++;
        break;

    case 3:
        xOffset = (self - 1)->ext.et_801BDA0C.unk80 /
                  0x10000; // note previous entity uses a different ext.
        if (xOffset < 0) {
            xOffset = -xOffset;
        }
        posX = self->posX.i.hi;
        posY = self->posY.i.hi - 0x28;
        prim = self->ext.et_801BE2C8.unk7C;
        for (i = 0; i < 0x20; i++) {
            prim->x0 = posX - xOffset - 0x20 + i;
            prim->y0 = posY - 0x20 + i;
            prim->u0 = xOffset * 2 + 0x40 - i * 2;
            prim->v0 = 0x94 - i * 2;
            prim = prim->next;
        }
        while (prim != NULL) {
            prim->x0 = posX - xOffset;
            prim->y0 = posY;
            prim->u0 = xOffset * 2;
            prim->v0 = 0x54;
            prim = prim->next;
        }
        lastPrim = self->ext.et_801BE2C8.unk80;
        if (self->ext.et_801BE2C8.unk84) {
            lastPrim->x0 = 0;
            lastPrim->y0 = 0;
            lastPrim->u0 = 0xFF;
            lastPrim->v0 = 0xFF;
            if (lastPrim->r0 < 0xF8) {
                lastPrim->r0 += 8;
                lastPrim->g0 = lastPrim->b0 = lastPrim->r0;
            } else {
                (self + 1)->ext.et_801BE2C8.unk84 = 1;
                self->step++;
            }
        }
        break;

    case 4:
        prim = self->ext.et_801BE2C8.unk7C;
        prim->type = PRIM_TILE;
        prim->r0 = prim->b0 = prim->g0 = 0xFF;
        prim->priority = 0x40;
        prim = prim->next;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        prim = self->ext.et_801BE2C8.unk80;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        (self + 1)->ext.et_801BE2C8.unk84 = 1;
        self->step++;
        break;

    case 5:
        lastPrim = self->ext.et_801BE2C8.unk80;
        if (lastPrim->r0 > 8) {
            lastPrim->r0 -= 8;
            lastPrim->g0 = lastPrim->b0 = lastPrim->r0;
        } else {
            (self + 1)->ext.et_801BE2C8.unk84 = 1;
            prim = self->ext.et_801BE2C8.unk7C;
            prim = prim->next;
            g_api.FreePrimitives(prim - g_PrimBuf);
            prim = self->ext.et_801BE2C8.unk7C;
            prim->next = NULL;
            self->step++;
        }
        break;
    }
}

void func_us_801BE2C8(Entity* self) {
    s32 primIndex;
    s16 rotZ;
    s16 rotY;
    long p, flag;
    SVECTOR p0, p1, p2, p3;
    u8 pad[4];
    VECTOR trans;
    MATRIX m;
    Primitive* lastPrim;
    Primitive* prim;
    s16 t;
    s16 iter;
    s32 i, j;
    s16* zPointer;
    s16 posX, posY; // unused

    SVECTOR rot = {0};

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        break;

    case 1:
        if (self->ext.et_801BE2C8.unk84) {
            self->step++;
        }
        break;

    case 2:
        self->ext.et_801BE2C8.unk84 = 0;
        primIndex = g_api.AllocatePrimitives(PRIM_GT4, 0x180);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801BE2C8.unk7C = prim;
            while (prim != NULL) {
                prim->tpage = 0x1A;
                prim->clut = 0x15F;
                prim->u0 = prim->u2 = 0x20;
                prim->u1 = prim->u3 = 0x28;
                prim->v0 = prim->v1 = 0xA0;
                prim->v2 = prim->v3 = 0xA8;
                prim->r0 = prim->g0 = prim->b0 = 0x10;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->priority = 0xD0;
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
                lastPrim = prim;
                prim = prim->next;
            }
            self->ext.et_801BE2C8.unk80 = lastPrim;
            lastPrim->x0 = lastPrim->x2 = 0;
            lastPrim->x1 = lastPrim->x3 = 0;
            lastPrim->y0 = lastPrim->y1 = 0;
            lastPrim->y2 = lastPrim->y3 = 0;
            lastPrim->r0 = lastPrim->g0 = lastPrim->b0 = 0xFF;
            LOW(lastPrim->r1) = LOW(lastPrim->r0);
            LOW(lastPrim->r2) = LOW(lastPrim->r0);
            LOW(lastPrim->r3) = LOW(lastPrim->r0);
            lastPrim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
        } else {
            DestroyEntity(self);
            return;
        }
        zPointer = self->ext.et_801BE2C8.unk88;
        for (i = 0; i < 8; i++) {
            *zPointer = D_us_801815B8[i];
            zPointer++;
        }
        self->ext.et_801BE2C8.unkA0 = 0;
        g_api.PlaySfx(0x7AE);
        self->step++;
        break;

    case 3:
        iter = 0;
        zPointer = self->ext.et_801BE2C8.unk88;
        prim = self->ext.et_801BE2C8.unk7C;
        SetGeomScreen(0x100);
        SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
        for (i = 0; i < 8; i++) {
            rotY = 0x280;
            rotZ = *zPointer;
            RotMatrix(&rot, &m);
            RotMatrixY(rotY, &m);
            RotMatrixZ(rotZ, &m);
            trans.vx = 0;
            trans.vy = 0;
            trans.vz = 0x140;
            TransMatrix(&m, &trans);
            SetRotMatrix(&m);
            SetTransMatrix(&m);
            t = D_us_801815E0[i] - self->ext.et_801BE2C8.unkA0 / 16;
            if (t < 0) {
                t = 0;
            }
            p0.vx = 0;
            p0.vy = 0 - t;
            p0.vz = 0;

            p1.vx = t - 0;
            p1.vy = 0;
            p1.vz = 0;

            p2.vx = 0 - t;
            p2.vy = 0;
            p2.vz = 0;

            p3.vx = 0;
            p3.vy = t - 0;
            p3.vz = 0;
            for (j = 0; p0.vx < 0xC0; j++, prim = prim->next) {
                if (iter > 0x170) {
                    break;
                }
                RotAverage4(
                    &p0, &p1, &p2, &p3, (long*)(&prim->x0), (long*)(&prim->x1),
                    (long*)(&prim->x2), (long*)(&prim->x3), &p, &flag);
                prim->r0 = 0x20 - (i % 3) * 8 - j / 4;
                if (prim->r0 > 0x80) {
                    prim->r0 = 0;
                }
                prim->g0 = 0x20 - (i % 2) * 8 - j / 4;
                if (prim->g0 > 0x80) {
                    prim->g0 = 0;
                }
                prim->b0 = 0x20 - (i % 4) * 8 - j / 4;
                if (prim->b0 > 0x80) {
                    prim->b0 = 0;
                }
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                iter++;
                posX = prim->x0;
                posY = prim->y0;
                p0.vx += 3;
                p1.vx += 3;
                p2.vx += 3;
                p3.vx += 3;
            }
            *zPointer += D_us_801815CC[i];
            zPointer++;
        }
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        prim = self->ext.et_801BE2C8.unk80;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        if (self->ext.et_801BE2C8.unk84) {
            self->ext.et_801BE2C8.unkA0 += 4;
        }
        if (self->ext.et_801BE2C8.unkA0 > 0x200) {
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            DestroyEntity(self);
        }
        break;
    }
}
