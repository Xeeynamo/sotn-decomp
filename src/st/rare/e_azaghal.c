// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rare.h"

extern EInit g_EInitAzaghal;

typedef struct {
    SVECTOR* vec;
    s16* ptr;
} Unk;

static s16 D_us_801818B0[] = {
    0x0000, 0x0048, 0x0000, 0x0004, 0x0004, 0xFFFC, 0xFFF8, 0x0000,
};
static s16 D_us_801818C0[][6] = {
    {0x0040, 0x0000, 0x003F, 0x007F, 0xFFF8, 0xFFE2},
    {0x0080, 0x0000, 0x0057, 0x007F, 0xFFF8, 0xFFE8},
    {0x0000, 0x0080, 0x005F, 0x006F, 0xFFC0, 0xFFF0},
    {0x0080, 0x0000, 0x0057, 0x007F, 0xFFE8, 0xFFE3},
};
static SVECTOR D_us_801818F0 = {0xFFF0, 0x0008, 0x0000, 0x0000};
static SVECTOR D_us_801818F8 = {0x0010, 0x0008, 0x0000, 0x0000};
static SVECTOR D_us_80181900 = {0xFFF0, 0x0078, 0x0000, 0x0000};
static SVECTOR D_us_80181908 = {0x0010, 0x0078, 0x0000, 0x0000};
static SVECTOR D_us_80181910 = {0x0000, 0x0008, 0xFFF8, 0x0000};
static SVECTOR D_us_80181918 = {0x0000, 0x0008, 0x0008, 0x0000};
static SVECTOR D_us_80181920 = {0x0000, 0x0078, 0xFFF8, 0x0000};
static SVECTOR D_us_80181928 = {0x0000, 0x0078, 0x0008, 0x0000};
static SVECTOR D_us_80181930 = {0x0000, 0x0078, 0x0000, 0x0000};

static s16 D_us_80181938[] = {
    0x0000, 0x0000, 0x000C, 0x0100, 0x000C, 0x0200, 0x000C, 0x0400, 0x000C,
    0x0800, 0x000C, 0x0C00, 0x000C, 0x0E00, 0x000C, 0x0F00, 0x000C, 0x1000,
};

static s16 D_us_8018195C[] = {
    0x0000, 0x0000, 0x0020, 0x0400, 0x0008,
    0x0800, 0x0004, 0x0E00, 0x0010, 0x1000,
};

static s16 D_us_80181970[] = {
    0x0000, 0x0000, 0x0020, 0x0400, 0x0008,
    0x0800, 0x0008, 0x0F00, 0x0030, 0x1000,
};

static s16 D_us_80181984[] = {
    0x0000, 0x0000, 0x0008, 0x0100, 0x0006, 0x0800,
    0x0004, 0x0E00, 0x0004, 0x0F80, 0x0020, 0x1000,
};

static s16 D_us_8018199C[] = {
    0x0000, 0x0000, 0x000E, 0x0100, 0x000A, 0x0800,
    0x0008, 0x0E00, 0x0008, 0x0F80, 0x0020, 0x1000,
};

static s16 D_us_801819B4[] = {
    0x0000, 0x0000, 0x0006, 0x0100, 0x0006, 0x0400, 0x0006,
    0x0800, 0x0004, 0x0E00, 0x0004, 0x0F80, 0x0008, 0x1000,
};

static s16 D_us_801819D0[] = {
    0x0000, 0x0000, 0x0003, 0x0100, 0x0003, 0x0400, 0x0003,
    0x0800, 0x0002, 0x0E00, 0x0002, 0x0F80, 0x0004, 0x1000,
};

static SVECTOR D_us_801819EC = {0x0000, 0x0000, 0x00E0, 0x0000};
static SVECTOR D_us_801819F4 = {0x0000, 0x0000, 0x0030, 0x0000};
static Unk D_us_801819FC[] = {
    {.vec = &D_us_801819EC, .ptr = D_us_80181938},
    {.vec = &D_us_801819F4, .ptr = D_us_80181938},
};

static SVECTOR D_us_80181A0C = {0xFBE0, 0x0330, 0x0CE0, 0x0000};
static SVECTOR D_us_80181A14 = {0x0000, 0x0400, 0x0800, 0x0000};
static SVECTOR D_us_80181A1C = {0x0000, 0x0000, 0x0540, 0x0000};
static Unk D_us_80181A24 = {.vec = &D_us_80181A0C, .ptr = D_us_80181938};
static Unk D_us_80181A2C = {.vec = &D_us_80181A14, .ptr = D_us_801819D0};
static Unk D_us_80181A34 = {.vec = &D_us_80181A1C, .ptr = D_us_8018195C};

static SVECTOR D_us_80181A3C = {0xFE20, 0x0020, 0x07D0, 0x0000};
static SVECTOR D_us_80181A44 = {0xFE20, 0x0020, 0xFF20, 0x0000};
static Unk D_us_80181A4C = {.vec = &D_us_80181A3C, .ptr = D_us_80181970};
static Unk D_us_80181A54 = {.vec = &D_us_80181A44, .ptr = D_us_8018199C};

static SVECTOR D_us_80181A5C = {0xFC80, 0xFFE0, 0x0700, 0x0000};
static SVECTOR D_us_80181A64 = {0xFC88, 0xFFE0, 0xFE70, 0x0000};
static Unk D_us_80181A6C = {.vec = &D_us_80181A5C, .ptr = D_us_80181984};
static Unk D_us_80181A74 = {.vec = &D_us_80181A64, .ptr = D_us_80181970};
static Unk D_us_80181A7C = {.vec = &D_us_80181A5C, .ptr = D_us_80181938};
static Unk D_us_80181A84 = {.vec = &D_us_80181A64, .ptr = D_us_80181984};

static SVECTOR D_us_80181A8C = {0xFE30, 0xFE60, 0xFF90, 0x0000};
static SVECTOR D_us_80181A94 = {0xFE30, 0xFF60, 0x06D0, 0x0000};
static Unk D_us_80181A9C = {.vec = &D_us_80181A8C, .ptr = D_us_80181970};
static Unk D_us_80181AA4 = {.vec = &D_us_80181A94, .ptr = D_us_80181984};

static SVECTOR D_us_80181AAC = {0x0000, 0x0000, 0x0930, 0x0000};
static SVECTOR D_us_80181AB4 = {0x0000, 0x0000, 0x0200, 0x0000};
// unused
static Unk D_us_80181ABC[] = {
    {.vec = &D_us_80181AAC, .ptr = D_us_80181938},
    {.vec = &D_us_80181AB4, .ptr = D_us_80181938},
};

static SVECTOR D_us_80181ACC = {0x0000, 0x0000, 0x0200, 0x0000};
static Unk D_us_80181AD4 = {.vec = &D_us_80181ACC, .ptr = D_us_80181984};

static SVECTOR D_us_80181ADC = {0x0000, 0x0000, 0xFBC0, 0x0000};
static SVECTOR D_us_80181AE4 = {0x0000, 0x0000, 0x0400, 0x0000};
static Unk D_us_80181AEC = {.vec = &D_us_80181ADC, .ptr = D_us_80181984};

static SVECTOR D_us_80181AF4 = {0xFBC0, 0x0000, 0xFBC0, 0x0000};
static SVECTOR D_us_80181AFC = {0xFBC0, 0x0000, 0xFBC0, 0x0000};
static SVECTOR D_us_80181B04 = {0xFBC0, 0x0000, 0x0A00, 0x0000};
static Unk D_us_80181B0C[] = {
    {.vec = &D_us_80181AF4, .ptr = D_us_801819B4},
    {.vec = &D_us_80181AFC, .ptr = D_us_801819B4},
    {.vec = &D_us_80181B04, .ptr = D_us_801819B4},
    {.vec = &D_us_80181AAC, .ptr = D_us_801819D0},
    {.vec = &D_us_80181AB4, .ptr = D_us_801819D0},
    {.vec = &D_us_80181A8C, .ptr = D_us_801819D0},
    {.vec = &D_us_80181A94, .ptr = D_us_801819D0},
    {.vec = &D_us_80181AAC, .ptr = D_us_801819D0},
    {.vec = &D_us_80181AE4, .ptr = D_us_801819D0},
};
static s16 D_us_80181B54[] = {0, 2, 3, 5, 3, 5, 6, 8};

Primitive* func_us_801B2C40(
    SVECTOR* p0, SVECTOR* p1, SVECTOR* p2, SVECTOR* p3, Primitive* srcPrim,
    s32 iterations, Primitive* dstPrim, u8* dataPtr) {
    long sp4C;
    long sp48;
    long sp44;
    s32 index0;
    s32 index1;
    s32 index2;
    s32 index3;
    s16* indexPtr;
    uvPair* uvValues;
    Primitive* tempPrim;
    SVECTOR* points;
    s32 count;
    Primitive* dstPrimNext;

    if (dstPrim == NULL) {
        return NULL;
    }
    tempPrim = (Primitive*)dataPtr;
    dataPtr += sizeof(Primitive);
    points = (SVECTOR*)dataPtr;
    dataPtr += sizeof(SVECTOR) * 9;
    uvValues = (uvPair*)dataPtr;
    dataPtr += sizeof(uvPair) * 10;
    points[0] = *p0;
    points[2] = *p1;
    points[6] = *p2;
    points[8] = *p3;

    points[3].vx = ((points[0].vx + points[6].vx + 1) >> 1);
    points[3].vy = ((points[0].vy + points[6].vy + 1) >> 1);
    points[3].vz = ((points[0].vz + points[6].vz + 1) >> 1);
    points[5].vx = ((points[2].vx + points[8].vx + 1) >> 1);
    points[5].vy = ((points[2].vy + points[8].vy + 1) >> 1);
    points[5].vz = ((points[2].vz + points[8].vz + 1) >> 1);

    uvValues[0] = UV(srcPrim->u0);
    uvValues[2] = UV(srcPrim->u1);
    uvValues[6] = UV(srcPrim->u2);
    uvValues[8] = UV(srcPrim->u3);
    uvValues[3].u = (((uvValues[0].u) + (uvValues[6].u) + 1) >> 1);
    uvValues[3].v = (((uvValues[0].v) + (uvValues[6].v) + 1) >> 1);
    uvValues[5].u = (((uvValues[2].u) + (uvValues[8].u) + 1) >> 1);
    uvValues[5].v = (((uvValues[2].v) + (uvValues[8].v) + 1) >> 1);

    *tempPrim = *srcPrim;
    indexPtr = D_us_80181B54;
    for (count = 0; count < 2; count++) {
        index0 = *indexPtr++;
        index1 = *indexPtr++;
        index2 = *indexPtr++;
        index3 = *indexPtr++;

        sp44 = RotTransPers4(
            &points[index0], &points[index1], &points[index2], &points[index3],
            (long*)&tempPrim->x0, (long*)&tempPrim->x1, (long*)&tempPrim->x2,
            (long*)&tempPrim->x3, &sp48, &sp4C);

        UV(tempPrim->u0) = uvValues[index0];
        UV(tempPrim->u1) = uvValues[index1];
        UV(tempPrim->u2) = uvValues[index2];
        UV(tempPrim->u3) = uvValues[index3];

        if (iterations == 1) {
            dstPrimNext = dstPrim->next;
            *dstPrim = *tempPrim;
            dstPrim->next = dstPrimNext;
            dstPrim = dstPrim->next;
            if (dstPrim == NULL) {
                return NULL;
            }
        } else {
            dstPrim = func_us_801B2C40(
                &points[index0], &points[index1], &points[index2],
                &points[index3], tempPrim, iterations - 1, dstPrim, dataPtr);
        }
    }
    return dstPrim;
}

s32 func_us_801B30A8(s32 arg0, s32 arg1) {
    Primitive* prim;
    s16* var_s1;
    u8 var_s2;

    prim = g_CurrentEntity->ext.azaghal.primTwo;
    var_s1 = D_us_801818C0[arg0];
    switch (arg1) {
    case 0:
        prim->u0 = prim->u2 = var_s1[0];
        prim->u1 = prim->u3 = var_s1[0] + var_s1[2];
        prim->v0 = prim->v1 = var_s1[1];
        prim->v2 = prim->v3 = var_s1[1] + var_s1[3];

        if (g_CurrentEntity->facingLeft) {
            prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi - var_s1[4];
            prim->x1 = prim->x3 = prim->x0 - var_s1[2];
        } else {
            prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi + var_s1[4];
            prim->x1 = prim->x3 = prim->x0 + var_s1[2];
        }
        prim->y0 = prim->y1 = g_CurrentEntity->posY.i.hi + var_s1[5];
        prim->y2 = prim->y3 = prim->y0 + var_s1[3];

        PGREY(prim, 0) = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = g_CurrentEntity->zPriority + 1;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        g_CurrentEntity->ext.azaghal.unk8C = 0;
        break;
    case 1:
        var_s2 = (g_CurrentEntity->ext.azaghal.unk8C *
                  abs(rsin(g_CurrentEntity->ext.azaghal.unk82))) >>
                 0xC;
        prim->r0 = prim->g0 = prim->b0 = var_s2;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);

        if (g_CurrentEntity->facingLeft) {
            prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi - var_s1[4];
            prim->x1 = prim->x3 = prim->x0 - var_s1[2];
        } else {
            prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi + var_s1[4];
            prim->x1 = prim->x3 = prim->x0 + var_s1[2];
        }

        prim->y0 = prim->y1 = g_CurrentEntity->posY.i.hi + var_s1[5];
        prim->y2 = prim->y3 = prim->y0 + var_s1[3];

        if (g_CurrentEntity->ext.azaghal.unk8C < 0x80) {
            g_CurrentEntity->ext.azaghal.unk8C += 8;
        }
        g_CurrentEntity->ext.azaghal.unk82 += 0x20;
        if (g_Timer & 2) {
            prim->clut = 0x211;
        } else {
            prim->clut = 0x212;
        }
        break;
    case 2:
        if (!PrimDecreaseBrightness(prim, 7)) {
            prim->drawMode = DRAW_HIDE;
            return 1;
        }
        break;
    }

    return 0;
}

void func_us_801B33F4(void) {
#ifdef VERSION_PC
    u8 sp[SP_LEN];
#endif
    long flag;
    long p;
    SVECTOR sVec;
    VECTOR vector;
    MATRIX matrix;

    Primitive* prim;
    Primitive* primTwo;
    Entity* entity;
    s32 i;
    s32 var_s4;
    s32 var_s5;
    s32 posX;
    s32 posY;

    posX = g_CurrentEntity->posX.i.hi;
    posY = g_CurrentEntity->posY.i.hi;
    SetGeomScreen(0x100);
    SetGeomOffset(posX, posY);
    sVec.vx = g_CurrentEntity->ext.azaghal.vx;
    sVec.vy = g_CurrentEntity->ext.azaghal.vy;
    sVec.vz = g_CurrentEntity->ext.azaghal.vz;
    RotMatrix(&sVec, &matrix);

    if (g_CurrentEntity->facingLeft) {
        RotMatrixY(0x800, &matrix);
    }

    vector.vx = 0;
    vector.vy = 0;
    vector.vz = 0x100;
    TransMatrix(&matrix, &vector);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
    prim = g_CurrentEntity->ext.azaghal.prim;
    prim->drawMode = DRAW_UNK02;
    RotTransPers4(&D_us_801818F0, &D_us_801818F8, &D_us_80181900,
                  &D_us_80181908, (long*)&prim->x0, (long*)&prim->x1,
                  (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
    primTwo = g_CurrentEntity->ext.azaghal.primThree;
    primTwo = func_us_801B2C40(&D_us_801818F0, &D_us_801818F8, &D_us_80181900,
                               &D_us_80181908, prim, 3, primTwo, (u8*)SPAD(0));
    prim->drawMode = DRAW_HIDE;
    prim = prim->next;
    prim->drawMode = DRAW_UNK02;
    RotTransPers4(&D_us_80181910, &D_us_80181918, &D_us_80181920,
                  &D_us_80181928, (long*)&prim->x0, (long*)&prim->x1,
                  (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
    primTwo = func_us_801B2C40(&D_us_80181910, &D_us_80181918, &D_us_80181920,
                               &D_us_80181928, prim, 3, primTwo, (u8*)SPAD(0));
    prim->drawMode = DRAW_HIDE;
    if (g_CurrentEntity->flags & FLAG_DEAD) {
        while (primTwo != NULL) {
            primTwo->drawMode = DRAW_HIDE;
            primTwo = primTwo->next;
        }
    } else {
        RotTransPers(&D_us_80181930, (long*)SPAD(0), &p, &flag);
        var_s4 = *(s16*)SP(0);
        var_s5 = *(s16*)SP(2);
        var_s4 -= posX;
        var_s5 -= posY;

        g_CurrentEntity->hitboxOffX = var_s4 / 8;
        if (g_CurrentEntity->facingLeft) {
            g_CurrentEntity->hitboxOffX = (s16)-g_CurrentEntity->hitboxOffX;
        }

        g_CurrentEntity->hitboxOffY = var_s5 / 8;

        for (i = 2; i < 8; i++) {
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_UNK_21, entity);
                entity->posX.i.hi = posX + ((var_s4 * i) / 8);
                entity->posY.i.hi = posY + ((var_s5 * i) / 8);
            }
        }

        prim = primTwo;
        for (i = 0; i < 6; i++) {
            prim->type = PRIM_G4;
            primTwo = prim->next;

            prim->r0 = i * 0x10;
            prim->g0 = i * 0x10;
            prim->b0 = i * 0x10;
            LOW(prim->r1) = LOW(prim->r0);
            prim->r2 = (i + 1) * 0x10;
            prim->g2 = (i + 1) * 0x10;
            prim->b2 = (i + 1) * 0x10;
            LOW(prim->r3) = LOW(prim->r2);
            LOW(prim->x0) = LOW(primTwo->x0);
            LOW(prim->x1) = LOW(primTwo->x1);
            LOW(prim->x2) = LOW(primTwo->x2);
            LOW(prim->x3) = LOW(primTwo->x3);
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim = primTwo;
        }

        prim->type = PRIM_G4;
        prim->r0 = i * 0x10;
        prim->g0 = i * 0x10;
        prim->b0 = i * 0x10;
        LOW(prim->r1) = LOW(prim->r0);
        prim->r2 = (i + 1) * 0x10;
        prim->g2 = (i + 1) * 0x10;
        prim->b2 = (i + 1) * 0x10;
        LOW(prim->r3) = LOW(prim->r2);
        LOW(prim->x0) = LOW(prim->x2);
        LOW(prim->x1) = LOW(prim->x3);

        prim->x2 = posX + (var_s4 / 4);
        prim->y2 = posY + (var_s5 / 4);
        prim->x3 = (posX + var_s4) - (var_s4 / 8);
        prim->y3 = (posY + var_s5) - (var_s5 / 8);
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;

        var_s4 = 0;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            var_s4++;
            prim = prim->next;
        }
        FntPrint("no_use %x\n", var_s4);
    }
}

void func_us_801B3938(SVECTOR* vector) {
    s16* var_s2;
    s16* var_s1;
    s16* var_s0;

    var_s2 = &g_CurrentEntity->ext.azaghal.unkAC;
    var_s0 = &g_CurrentEntity->ext.azaghal.vx;
    var_s1 = &g_CurrentEntity->ext.azaghal.unkA4;

    var_s1[0] = vector->vx - var_s0[0];
    var_s1[1] = vector->vy - var_s0[1];
    var_s1[2] = vector->vz - var_s0[2];

    var_s2[0] = var_s0[0];
    var_s2[1] = var_s0[1];
    var_s2[2] = var_s0[2];
}

void func_us_801B398C(void) {
    s16* var_s2;
    s16* var_s1;
    s16* var_s0;
    s32 var_s3;

    var_s2 = &g_CurrentEntity->ext.azaghal.unkAC;
    var_s1 = &g_CurrentEntity->ext.azaghal.vx;
    var_s0 = &g_CurrentEntity->ext.azaghal.unkA4;
    var_s3 = g_CurrentEntity->ext.azaghal.unk98;
    var_s1[0] = var_s2[0] + ((var_s0[0] * var_s3) / 0x1000);
    var_s1[1] = var_s2[1] + ((var_s0[1] * var_s3) / 0x1000);
    var_s1[2] = var_s2[2] + ((var_s0[2] * var_s3) / 0x1000);
}

s32 func_us_801B3A1C(Unk* str) {
    s16* ptr;
    s32 poseTimer;

    if (!g_CurrentEntity->pose && !g_CurrentEntity->poseTimer) {
        func_us_801B3938(str->vec);
    }

    ptr = str->ptr;
    ptr += g_CurrentEntity->pose * 2;
    if (ptr[1] == 0x1000) {
        return 0;
    }

    g_CurrentEntity->poseTimer++;
    poseTimer = g_CurrentEntity->poseTimer;
    g_CurrentEntity->ext.ILLEGAL.u32[7] =
        ptr[1] + (((ptr[3] - ptr[1]) * poseTimer) / ptr[2]);
    func_us_801B398C();

    if (poseTimer == ptr[2]) {
        g_CurrentEntity->poseTimer = 0;
        g_CurrentEntity->pose++;
    }

    return 1;
}

void func_us_801B3B34(Entity* self) {
    Primitive* prim;
    Entity* entity;
    Primitive* primTwo;
    Primitive* primThree;
    s32 i;
    s32 var_s4;
    s32 primIndex;
    s32 var_s8;
    s32 var_s7;

    FntPrint("step %x\n", self->step);
    FntPrint("step_s %x\n", self->step_s);
    if (self->hitFlags & 3 && self->step != 0xB) {
        SetStep(0xB);
    }
    if (self->flags & FLAG_DEAD && self->step < 0xF) {
        SetStep(0xF);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitAzaghal);
        self->hitboxState = 0;
        self->hitboxWidth = self->hitboxHeight = 0xC;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x20);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.azaghal.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0x14;
            prim->clut = 0x211;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        prim = self->ext.azaghal.prim;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x28;
        prim->v0 = prim->v1 = 0x10;
        prim->v2 = prim->v3 = 0x70;
        prim = prim->next;

        prim->u0 = prim->u2 = 0x28;
        prim->u1 = prim->u3 = 0x37;
        prim->v0 = prim->v1 = 0x10;
        prim->v2 = prim->v3 = 0x70;
        prim = prim->next;

        self->ext.azaghal.primTwo = prim;
        PGREY(prim, 0) = 0x80;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim = prim->next;
        prim = prim->next;
        prim = prim->next;
        self->ext.azaghal.primThree = prim;
        // fallthrough
    case 1:
        if (UnkCollisionFunc3(&D_us_801818B0) & 1) {
            SetStep(3);
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            prim = self->ext.azaghal.prim;
            prim->u0 = prim->u2 = 4;
            prim->u1 = prim->u3 = 0x24;
            prim->v0 = prim->v1 = 0x10;
            prim->v2 = prim->v3 = 0x68;
            prim->x0 = prim->x2 = self->posX.i.hi - 0x10;
            prim->x1 = prim->x3 = self->posX.i.hi + 0x10;
            prim->y0 = prim->y1 = self->posY.i.hi - 0x10;
            prim->y2 = prim->y3 = self->posY.i.hi + 0x48;
            prim->drawMode = DRAW_UNK02;
            self->posY.i.hi -= 0x18;
            func_us_801B30A8(0, 0);
            self->step_s++;
            // fallthrough
        case 1:
            func_us_801B30A8(0, 1);
            if (GetDistanceToPlayerX() < 0x60) {
                self->step_s++;
            }
            break;
        case 2:
            if (func_us_801B30A8(0, 2)) {
                self->step_s++;
            }
            break;
        case 3:
            self->posY.i.hi--;
            prim = self->ext.azaghal.prim;
            prim->y0 = prim->y1 -= 1;
            prim->v2 = prim->v3 += 1;
            if (prim->v2 > 0x7F) {
                prim->v2 = prim->v3 = 0x7F;
                self->step_s++;
            }
            break;
        case 4:
            prim = self->ext.azaghal.prim;
            prim->u0 = prim->u2 = 4;
            prim->u1 = prim->u3 = 0x24;
            prim->v0 = prim->v1 = 0x10;
            prim->v2 = prim->v3 = 0x80;
            prim = prim->next;

            prim->u0 = prim->u2 = 0x28;
            prim->u1 = prim->u3 = 0x37;
            prim->v0 = prim->v1 = 0x10;
            prim->v2 = prim->v3 = 0x80;
            // nb. This goes unused
            prim = prim->next;

            self->step_s++;
            // fallthrough
        case 5:
            prim = self->ext.azaghal.prim;
            prim = prim->next;
            prim = prim->next;
            while (prim != NULL) {
                prim->x0 = self->posX.i.hi;
                prim->y0 = self->posY.i.hi;
                LOW(prim->x1) = LOW(prim->x0);
                LOW(prim->x2) = LOW(prim->x0);
                LOW(prim->x3) = LOW(prim->x0);
                prim = prim->next;
            }
            self->hitboxState = 2;
            SetStep(0xA);
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            if (!func_us_801B3A1C(&D_us_80181A24)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                self->step_s = 1;
            }
            break;
        case 1:
            if (!func_us_801B3A1C(&D_us_80181A2C)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                self->step_s++;
            }
            break;
        case 2:
            if (!func_us_801B3A1C(&D_us_80181A34)) {
                func_us_801B30A8(3, 0);
                self->ext.azaghal.unk80 = 0x10;
                self->step_s++;
            }
            break;
        case 3:
            func_us_801B30A8(3, 1);
            if (!--self->ext.azaghal.unk80) {
                self->step_s++;
            }
            break;
        case 4:
            if (func_us_801B30A8(3, 2)) {
                PlaySfxPositional(SFX_VANDAL_SWORD_ATTACK);
                if (self->ext.azaghal.unk8D & 1) {
                    SetStep(5);
                } else {
                    SetStep(0xC);
                }

                self->ext.azaghal.unk8D++;
                if (self->ext.azaghal.unk8D > 3) {
                    self->ext.azaghal.unk8D = 0;
                    SetStep(0xD);
                }
            }
            break;
        }

        func_us_801B33F4();
        break;
    case 0xA:
        if (!self->step_s) {
            self->ext.azaghal.unk80 = 0x80;
            self->velocityX = 0;
            self->velocityY = 0;
            self->ext.azaghal.unk8E = 0;
            self->step_s++;
        }

        if (!func_us_801B3A1C(&D_us_801819FC[self->ext.azaghal.unk8E])) {
            self->ext.azaghal.unk8E ^= 1;
            self->pose = 0;
            self->poseTimer = 0;
        }

        MoveEntity();
        self->rotate += 0x40;
        self->velocityY = rsin(self->rotate) * 0xE;
        if (self->posY.val < FIX(128.5)) {
            self->velocityY += FIX(0.25);
        } else {
            self->velocityY -= FIX(0.25);
        }

        if (GetDistanceToPlayerX() < 0x30) {
            self->velocityX = FIX(0.5);
        }

        if (GetDistanceToPlayerX() > 0x38) {
            self->velocityX = FIX(-0.5);
        }

        if (self->facingLeft) {
            self->velocityX = -self->velocityX;
        }

        if (self->facingLeft != ((GetSideToPlayer() & 1) ^ 1)) {
            SetStep(4);
        }

        if (!--self->ext.azaghal.unk80) {
            SetStep(4);
        }
        func_us_801B33F4();
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            if (!func_us_801B3A1C(&D_us_80181A4C)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            break;
        case 1:
            if (!func_us_801B3A1C(&D_us_80181A54)) {
                SetStep(6);
            }
            break;
        }
        func_us_801B33F4();
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            if (!func_us_801B3A1C(&D_us_80181A74)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->velocityX = FIX(-4.0);
                if (self->facingLeft) {
                    self->velocityX = -self->velocityX;
                }
                self->velocityY = 0;
                self->step_s++;
            }
            break;
        case 1:
            MoveEntity();
            self->velocityX -= self->velocityX / 16;
            if (!func_us_801B3A1C(&D_us_80181A6C)) {
                SetStep(0xA);
            }
            break;
        }
        func_us_801B33F4();
        break;
    case 0xC:
        switch (self->step_s) {
        case 0:
            if (!func_us_801B3A1C(&D_us_80181A7C)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->velocityX = FIX(-4.0);
                if (self->facingLeft) {
                    self->velocityX = -self->velocityX;
                }
                self->velocityY = 0;
                self->step_s++;
            }
            break;
        case 1:
            MoveEntity();
            self->velocityX -= self->velocityX / 16;
            if (!func_us_801B3A1C(&D_us_80181A84)) {
                SetStep(8);
            }
            break;
        }
        func_us_801B33F4();
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            if (!func_us_801B3A1C(&D_us_80181A9C)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            break;
        case 1:
            if (!func_us_801B3A1C(&D_us_80181AA4)) {
                SetStep(0xA);
            }
            break;
        }
        func_us_801B33F4();
        break;
    case 0xD:
        switch (self->step_s) {
        case 0:
            func_us_801B30A8(1, 0);
            self->step_s++;
            // fallthrough
        case 1:
            func_us_801B30A8(1, 1);
            if (!func_us_801B3A1C(&D_us_80181AEC)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->ext.azaghal.unk80 = 0;
                self->step_s++;
            }
            break;
        case 2:
            prim = self->ext.azaghal.primTwo;
            primTwo = prim->next;
            primThree = primTwo->next;

            *primTwo = *prim;
            PGREY(primTwo, 0) = 0x80;
            LOW(primTwo->r1) = LOW(primTwo->r0);
            LOW(primTwo->r2) = LOW(primTwo->r0);
            LOW(primTwo->r3) = LOW(primTwo->r0);
            primTwo->next = primThree;
            primTwo->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                DRAW_UNK02 | DRAW_TRANSP;
            primTwo = primTwo->next;
            primThree = primTwo->next;

            *primTwo = *prim;
            PGREY(primTwo, 0) = 0x80;
            LOW(primTwo->r1) = LOW(primTwo->r0);
            LOW(primTwo->r2) = LOW(primTwo->r0);
            LOW(primTwo->r3) = LOW(primTwo->r0);
            primTwo->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                DRAW_UNK02 | DRAW_TRANSP;
            primTwo->next = primThree;
            // nb. This goes unused
            primTwo = primTwo->next;

            self->step_s++;
            // fallthrough
        case 3:
            var_s4 = 0;
            prim = self->ext.azaghal.primTwo;
            prim = prim->next;
            if (self->facingLeft) {
                prim->x0 = prim->x2 += 1;
                prim->x1 = prim->x3 -= 1;
            } else {
                prim->x0 = prim->x2 -= 1;
                prim->x1 = prim->x3 += 1;
            }

            prim->y0 = prim->y1 -= 1;
            prim->y2 = prim->y3 += 1;

            if (g_Timer & 1) {
                prim->clut = 0x213;
            } else {
                prim->clut = 0x214;
            }

            if (!PrimDecreaseBrightness(prim, 7)) {
                prim->drawMode = DRAW_HIDE;
                var_s4 += 1;
            }

            prim = prim->next;
            if (self->facingLeft) {
                prim->x0 = prim->x2 += 3;
                prim->x1 = prim->x3 -= 3;
            } else {
                prim->x0 = prim->x2 -= 3;
                prim->x1 = prim->x3 += 3;
            }

            prim->y0 = prim->y1 -= 3;
            prim->y2 = prim->y3 += 3;
            if (g_Timer & 1) {
                prim->clut = 0x213;
            } else {
                prim->clut = 0x214;
            }

            if (!PrimDecreaseBrightness(prim, 7)) {
                prim->drawMode = DRAW_HIDE;
                var_s4++;
            }

            func_us_801B30A8(1, 1);
            if (var_s4 == 2) {
                self->step_s++;
            }
            break;
        case 4:
            if (func_us_801B30A8(1, 2)) {
                self->ext.azaghal.unk8E = 0;
                self->step_s++;
            }
            break;
        case 5:
            i = self->ext.azaghal.unk8E;
            if (!func_us_801B3A1C(&D_us_80181B0C[i])) {
                self->ext.azaghal.unk8E++;
                self->pose = 0;
                self->poseTimer = 0;
                if (self->ext.azaghal.unk8E == 9) {
                    self->velocityX = FIX(-6.0);
                    if (self->facingLeft) {
                        self->velocityX = -self->velocityX;
                    }
                    self->velocityY = 0;
                    self->step_s++;
                }
            }
            break;
        case 6:
            MoveEntity();
            self->velocityX -= self->velocityX / 16;
            if (self->ext.azaghal.unk80++ > 0x40) {
                SetStep(0xA);
            }
            break;
        }
        func_us_801B33F4();
        break;
    case 0xB:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(-4.0);
            } else {
                self->velocityX = FIX(4.0);
            }
            self->velocityY = FIX(-4.0);

            prim = self->ext.azaghal.primTwo;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;

            func_us_801B30A8(2, 0);
            PlaySfxPositional(SFX_VANDAL_SWORD_PAIN);
            self->step_s++;
            // fallthrough
        case 1:
            func_us_801B3A1C(&D_us_80181AD4);
            func_us_801B30A8(2, 1);
            MoveEntity();
            self->velocityX -= self->velocityX / 32;
            self->velocityY += FIX(0.125);
            if (self->velocityY > FIX(4.0)) {
                self->step_s++;
            }
            break;
        case 2:
            if (func_us_801B30A8(2, 2)) {
                SetStep(0xA);
            }
            break;
        }
        func_us_801B33F4();
        break;
    case 0xF:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(-4.0);
            } else {
                self->velocityX = FIX(4.0);
            }
            self->velocityY = FIX(-4.0);

            prim = self->ext.azaghal.primTwo;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;

            func_us_801B30A8(2, 0);
            PlaySfxPositional(SFX_VANDAL_SWORD_DEATH);
            self->step_s++;
            // fallthrough
        case 1:
            func_us_801B3A1C(&D_us_80181AD4);
            func_us_801B30A8(2, 1);
            MoveEntity();
            self->velocityX -= self->velocityX / 32;
            self->velocityY += FIX(0.125);
            if (self->velocityY > FIX(4.0)) {
                self->ext.azaghal.unk8E = 0;
                self->ext.azaghal.unk80 = 4;
                self->step_s++;
            }
            func_us_801B33F4();
            break;
        case 2:
            prim = self->ext.azaghal.primTwo;
            PrimDecreaseBrightness(prim, 1);
            if (!--self->ext.azaghal.unk80) {
                PlaySfxPositional(SFX_EXPLODE_B);
                self->ext.azaghal.unk80 = 4;
                prim = self->ext.azaghal.primThree;

                for (i = 0; i < self->ext.azaghal.unk8E; i++) {
                    prim = prim->next;
                }

                prim->drawMode = DRAW_HIDE;
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
                    var_s8 = prim->x0 + prim->x1 + prim->x2 + prim->x3;
                    var_s8 /= 4;
                    var_s7 = prim->y0 + prim->y1 + prim->y2 + prim->y3;
                    var_s7 /= 4;
                    entity->posX.i.hi = var_s8;
                    entity->posY.i.hi = var_s7;
                    entity->params = EXPLOSION_FIREBALL;
                }
                self->ext.azaghal.unk8E++;
                if (self->ext.azaghal.unk8E > 7) {
                    self->step_s++;
                }
            }
            break;
        case 3:
            DestroyEntity(self);
            return;
        }
        break;
    case 0xFF:
        if (g_pads[1].pressed & PAD_TRIANGLE) {
            self->ext.azaghal.vx += 0x10;
        }

        if (g_pads[1].pressed & PAD_CROSS) {
            self->ext.azaghal.vx -= 0x10;
        }

        if (g_pads[1].pressed & PAD_CIRCLE) {
            self->ext.azaghal.vy += 0x10;
        }

        if (g_pads[1].pressed & PAD_SQUARE) {
            self->ext.azaghal.vy -= 0x10;
        }

        if (g_pads[1].pressed & PAD_RIGHT) {
            self->ext.azaghal.vz += 0x10;
        }

        if (g_pads[1].pressed & PAD_LEFT) {
            self->ext.azaghal.vz -= 0x10;
        }

        if (g_pads[1].pressed & PAD_SELECT) {
            self->ext.azaghal.vx = 0;
            self->ext.azaghal.vy = 0;
            self->ext.azaghal.vz = 0;
        }

        FntPrint("x:%4x\n", self->ext.azaghal.vx);
        FntPrint("y:%4x\n", self->ext.azaghal.vy);
        FntPrint("z:%4x\n", self->ext.azaghal.vz);
        func_us_801B33F4();
        break;
    }

    D_8006C384.y = self->ext.azaghal.unk98;
    D_8006C38C.x = self->pose;
    D_8006C38C.y = self->poseTimer;
}

void func_us_801B4E9C(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitAzaghal);
        self->hitboxState = 1;
        self->hitboxWidth = self->hitboxHeight = 4;
        return;
    }

    DestroyEntity(self);
}
