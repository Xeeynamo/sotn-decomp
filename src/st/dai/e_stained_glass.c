// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

static s16 D_us_80182564[] = {0, 2, 3, 5, 3, 5, 6, 8};
static SVECTOR D_us_80182574 = {-208, -192, 0};
static SVECTOR D_us_8018257C = {208, -192, 0};
static SVECTOR D_us_80182584 = {-208, 192, 0};
static SVECTOR D_us_8018258C = {208, 192, 0};
static SVECTOR D_us_80182594 = {-208, -96, 0};
static SVECTOR D_us_8018259C = {208, -96, 0};
static SVECTOR D_us_801825A4 = {-208, 96, 0};
static SVECTOR D_us_801825AC = {208, 96, 0};
// Atypical use of this vector.  It uses the vector values, but also uses pad to
// store the number of recursions of StainedGlassRecurseDepth
static VECTOR params[] = {
    {FLT(0.0625), 0, FLT(0.125), 3},   {FLT(0.0625), 0, FLT(0.28125), 2},
    {FLT(0.0625), 0, FLT(0.4375), 2},  {FLT(0.0625), 0, FLT(0.59375), 0},
    {FLT(0.0625), 0, FLT(0.75), 0},    {FLT(0.0625), 0, FLT(0.90625), 0},
    {FLT(-0.0625), 0, FLT(0.125), 3},  {FLT(-0.0625), 0, FLT(0.28125), 2},
    {FLT(-0.0625), 0, FLT(0.4375), 2}, {FLT(-0.0625), 0, FLT(0.59375), 0},
    {FLT(-0.0625), 0, FLT(0.75), 0},   {FLT(-0.0625), 0, FLT(0.90625), 0}};

static s16 D_us_80182674[] = {1024,  1024,  1024,  1024,  1024,  1024,
                              -1024, -1024, -1024, -1024, -1024, -1024};
static CVECTOR D_us_8018268C[] = {
    {128, 128, 128, 32}, {120, 120, 120, 36}, {112, 112, 112, 40},
    {104, 104, 104, 48}, {96, 96, 96, 56},    {88, 88, 88, 64},
    {96, 96, 96, 4},     {88, 88, 88, 4},     {80, 80, 80, 4},
    {72, 72, 72, 4},     {64, 64, 64, 4},     {56, 56, 56, 4}};

// pspeu has D_us_8018277C and D_us_801826BC swapped vs psx
#ifdef VERSION_PSP
static SVECTOR D_us_8018277C; // bss
#else
static SVECTOR D_us_801826BC = {0, 0, 0};
#endif

static SVECTOR D_us_801826C4 = {-192, -64, 0};
static SVECTOR D_us_801826CC = {192, -64, 0};
static SVECTOR D_us_801826D4 = {-192, 64, 0};
static SVECTOR D_us_801826DC = {192, 64, 0};

#ifdef VERSION_PSP
static SVECTOR D_us_801826E4; // bss D_pspeu_092978A0
#else
static SVECTOR D_us_801826E4 = {0, 0, 0};
#endif

static VECTOR D_us_801826EC[] = {
    {0, 0, FLT(1)},        {0, -224, FLT(0.125)}, {0, -224, FLT(0.25)},
    {0, -224, FLT(0.375)}, {0, -224, FLT(0.5)},   {0, -224, FLT(0.625)},
    {0, -224, FLT(0.75)},  {0, -224, FLT(0.875)}, {0, -224, FLT(1)}};
#ifdef VERSION_PSP
static SVECTOR D_us_801826BC; // bss
#else
static SVECTOR D_us_8018277C = {0, 0, 0};
#endif

void StainedGlassBlendPalette(
    RECT* arg0, u16 srcPalIdx, u16 destPalIdx, s32 steps, CVECTOR* color) {
    u16 buffer[COLORS_PER_PAL];
    RECT rect;
    s32 factor;
    s32 step, index;
    u16* palette;
    u32 r, g, b, mask;

    rect.x = arg0->x;
    rect.w = COLORS_PER_PAL;
    rect.h = 1;

    color->r /= 8;
    color->g /= 8;
    color->b /= 8;
    palette = &g_Clut[0][srcPalIdx * COLORS_PER_PAL];

    for (step = 0; step < steps; destPalIdx++, step++) {
        factor = (step * FLT(1)) / steps;
        for (index = 0; index < COLORS_PER_PAL; index++) {
            if (!(palette[index] & 0x7FFF)) {
                buffer[index] = palette[index];
            } else {
                r = GET_RED(palette[index]);
                g = GET_GREEN(palette[index]);
                b = GET_BLUE(palette[index]);
                mask = palette[index] & ALPHA_MASK;
                r = ((r * (FLT(1) - factor)) + (color->r * factor)) >> 12;
                g = ((g * (FLT(1) - factor)) + (color->g * factor)) >> 12;
                b = ((b * (FLT(1) - factor)) + (color->b * factor)) >> 12;
                buffer[index] = ((mask | (r)) | (g << 5)) | (b << 10);
                (&g_Clut[0][destPalIdx * COLORS_PER_PAL])[index] =
                    buffer[index];
            }
        }
        // These don't seem like they're x and y values
        rect.y = ((destPalIdx - 512) / COLORS_PER_PAL) + 240;
        rect.x = (((destPalIdx - 512) % COLORS_PER_PAL) * COLORS_PER_PAL) + 256;
        LoadImage(&rect, (u_long*)buffer);
    }
}

Primitive* StainedGlassRecurseDepth(
    SVECTOR* p0, SVECTOR* p1, SVECTOR* p2, SVECTOR* p3, Primitive* srcPrim,
    s32 iterations, Primitive* dstPrim, u8* dataPtr) {
    s32 index0;
    s32 index1;
    s32 index2;
    s32 index3;
    s16* indices;
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
    indices = D_us_80182564;
    for (count = 0; count < 2; count++) {
        index0 = *indices++;
        index1 = *indices++;
        index2 = *indices++;
        index3 = *indices++;

        gte_ldv0(&points[index3]);
        gte_rtps();
#ifdef VERSION_PSP
        gte_stsxy((long*)tempPrim + sizeof(uvPair) * 6);
#else
        gte_stsxy((long*)&tempPrim->x3);
#endif
#ifdef VERSION_PSP
        gte_ldv0(&points[index0]);
        gte_ldv1(&points[index1]);
        gte_ldv2(&points[index2]);
#else
        gte_ldv3(&points[index0], &points[index1], &points[index2]);
#endif
        gte_rtpt();
        gte_stsxy3_gt3(tempPrim);

        UV(tempPrim->u0) = uvValues[index0];
        UV(tempPrim->u1) = uvValues[index1];
        UV(tempPrim->u2) = uvValues[index2];
        UV(tempPrim->u3) = uvValues[index3];

        if ((tempPrim->x1 >= 0) && (tempPrim->x0 <= 256)) {
            if (iterations == 1) {
                dstPrimNext = dstPrim->next;
                *dstPrim = *tempPrim;
                dstPrim->next = dstPrimNext;
                dstPrim = dstPrim->next;
                if (dstPrim == NULL) {
                    return NULL;
                }
            } else {
                dstPrim = StainedGlassRecurseDepth(
                    &points[index0], &points[index1], &points[index2],
                    &points[index3], tempPrim, iterations - 1, dstPrim,
                    dataPtr);
            }
        }
    }
    return dstPrim;
}

void EntityStainedGlass(Entity* self) {
    s16 midpointX, midpointY;
    s32 primIndex;
    SVECTOR rotVector;
    VECTOR transVector;
    MATRIX mtx;
    u8 transparent; // u8, but used as bool
    s32 iterations;
    s16* yVals;
    VECTOR* paramsPtr;
    CVECTOR* colors;
    s32 count;
    Primitive* prim1;
    Primitive* prim2;
    Primitive* tempPrim;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 60);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim1 = &g_PrimBuf[primIndex];
            self->ext.stainedGlass.prim1 = prim1;
            for (count = 0; count < 12; count++) {
                prim1->tpage = 15;
                prim1->clut = PAL_STAINED_GLASS_E;
                prim1->u0 = prim1->u2 = 4;
                prim1->u1 = prim1->u3 = 28;
                prim1->v0 = prim1->v1 = 1;
                prim1->v2 = prim1->v3 = 174;
                PGREY(prim1, 0) = 96;
                LOW(prim1->r1) = LOW(prim1->r0);
                LOW(prim1->r2) = LOW(prim1->r0);
                LOW(prim1->r3) = LOW(prim1->r0);
                prim1->priority = 86;
                prim1->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
                prim1 = prim1->next;
            }
            for (self->ext.stainedGlass.prim2 = prim1; prim1 != NULL;
                 prim1 = prim1->next) {
                prim1->drawMode = DRAW_HIDE;
            }
            return;
        }
        DestroyEntity(self);
        return;
    case 1:
        SetGeomScreen(1024);
        SetGeomOffset(128, 160);
        prim1 = self->ext.stainedGlass.prim1;
        prim2 = self->ext.stainedGlass.prim2;
        paramsPtr = params;
        yVals = D_us_80182674;
        colors = D_us_8018268C;
        for (count = 0; count < 12; count++) {
            rotVector.vx = 0;
            rotVector.vy = *yVals;
            rotVector.vz = 0;
            RotMatrix(&rotVector, &mtx);
            transVector = *paramsPtr;
            if (transVector.vx > 0) {
                transparent = true;
                prim1->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            } else {
                transparent = false;
                prim1->drawMode = DRAW_COLORS;
            }
            iterations = paramsPtr->pad;
            transVector.vx += self->posX.i.hi - 128;
            transVector.vy += self->posY.i.hi - 160;
            transVector.vz += 1024;
#ifdef VERSION_PSP
            SetRotMatrix(&mtx);
#else
            gte_SetRotMatrix(&mtx);
#endif
            gte_SetTransVector(&transVector);
            CVEC(prim1->r0) = *colors;
            LOW(prim1->r1) = LOW(prim1->r0);
            LOW(prim1->r2) = LOW(prim1->r0);
            LOW(prim1->r3) = LOW(prim1->r0);
            prim1->type = 4;
            if (iterations) {
                prim2 = StainedGlassRecurseDepth(
                    &D_us_80182574, &D_us_8018257C, &D_us_80182584,
                    &D_us_8018258C, prim1, iterations, prim2, (u8*)SP(0));
                prim1->drawMode = DRAW_HIDE;
            }
#ifdef VERSION_PSP
            gte_ldv0(&D_us_80182574);
            gte_ldv1(&D_us_8018257C);
            gte_ldv2(&D_us_80182584);
#else
            gte_ldv3(&D_us_80182574, &D_us_8018257C, &D_us_80182584);
#endif
            gte_rtpt();
            gte_stsxy3_gt3(prim1);
            gte_ldv0(&D_us_8018258C);
            gte_rtps();
            gte_stsxy((long*)&prim1->x3);
            if (transparent) {
                tempPrim = prim2->next;
                *prim2 = *prim1;
                prim2->next = tempPrim;

                prim2->clut = PAL_STAGE_NAME_15F;
                prim2->priority = prim1->priority - 1;
                prim2->drawMode = DRAW_COLORS;
                prim2->r0 = prim2->g0 = prim2->b0 = colors->cd;
                LOW(prim2->r1) = LOW(prim2->r0);
                prim2->r2 = prim2->g2 = prim2->b2 = colors->cd / 2;
                LOW(prim2->r3) = LOW(prim2->r2);

                prim2 = prim2->next;
                tempPrim = prim2->next;
                *prim2 = *prim1;
                prim2->next = tempPrim;

                rotVector.vx = 0;
                rotVector.vy = *yVals;
                rotVector.vz = -1024;
                RotMatrix(&D_us_801826BC, &mtx);
                RotMatrixY(rotVector.vy, &mtx);
                RotMatrixZ(rotVector.vz, &mtx);
                transVector = *paramsPtr;
                transVector.vx = 96;
                transVector.vy = 256;
                transVector.vx += self->posX.i.hi - 128;
                transVector.vy += self->posY.i.hi - 160;
                transVector.vz += 1024;
#ifdef VERSION_PSP
                SetRotMatrix(&mtx);
#else
                gte_SetRotMatrix(&mtx);
#endif
                gte_SetTransVector(&transVector);
                CVEC(prim2->r0) = *colors;
                LOW(prim2->r1) = LOW(prim2->r0);
                LOW(prim2->r2) = LOW(prim2->r0);
                LOW(prim2->r3) = LOW(prim2->r0);
                prim2->type = 4;
#ifdef VERSION_PSP
                gte_ldv0(&D_us_80182594);
                gte_ldv1(&D_us_8018259C);
                gte_ldv2(&D_us_801825A4);
#else
                gte_ldv3(&D_us_80182594, &D_us_8018259C, &D_us_801825A4);
#endif
                gte_rtpt();
                gte_stsxy3_gt3(prim2);
                gte_ldv0(&D_us_801825AC);
                gte_rtps();
                gte_stsxy((long*)&prim2->x3);
                prim2->clut = PAL_STAINED_GLASS_204;
                prim2->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                                  DRAW_COLORS | DRAW_TRANSP;
                midpointX = (prim2->x0 + prim2->x2) / 2;
                midpointY = (prim2->y0 + prim2->y1) / 2;
                prim2 = prim2->next;
                tempPrim = prim2->next;
                *prim2 = *prim1;
                prim2->next = tempPrim;
                prim2->clut = PAL_STAGE_NAME_15F;
                prim2->priority = prim1->priority + 1;
                prim2->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                prim2->r0 = 24;
                prim2->g0 = 8;
                prim2->b0 = 32;
                LOW(prim2->r1) = LOW(prim2->r0);
                prim2->r2 = 8;
                prim2->g2 = 24;
                prim2->b2 = 8;
                prim2->r3 = prim2->g3 = prim2->b3 = 0;
                LOW(prim2->x0) = LOW(prim1->x1);
                LOW(prim2->x1) = LOW(prim1->x0);
                LOW(prim2->x2) = LOW(prim1->x3);
                prim2->x3 = midpointX;
                prim2->y3 = midpointY;
                prim2 = prim2->next;
            }
            colors++;
            yVals++;
            paramsPtr++;
            prim1 = prim1->next;
        }
        for (count = 0; prim2; prim2 = prim2->next) {
            count++;
            prim2->drawMode = DRAW_HIDE;
        }
    }
}

#ifdef VERSION_PSP
#define SETROTMATRIX(x) SetRotMatrix(x)
#else
#define SETROTMATRIX(x) gte_SetRotMatrix(x)
#endif

// There are a few things about this function that probably aren't quite right,
// but it is close enough for now
void func_us_801D9F5C(Entity* self) {
// psp wants this higher in the stack than psx
#ifdef VERSION_PSP
    RECT rect2, rect1;
#endif

    VECTOR transVector;
    MATRIX mtx;
    RECT rect;
    CVECTOR color;

// psx wants this lower in the stack than psp and uses 4 temp vars
#ifndef VERSION_PSP
    // I'm not sure if RECTs are quite right
    RECT rect1, rect2;
    s32 tempRect2w, tempRect2x;
    s32 tempRect1w, tempRect1x;
#endif

    s32 primIndex;
    VECTOR* transVectorPtr;
    s32 midpoint1, midpoint2;
    s32 count;
    Primitive* prim;
    s16 tempY, tempX;

    g_GpuBuffers[0].draw.r0 = 24;
    g_GpuBuffers[0].draw.g0 = 24;
    g_GpuBuffers[0].draw.b0 = 24;
    g_GpuBuffers[1].draw.r0 = 24;
    g_GpuBuffers[1].draw.g0 = 24;
    g_GpuBuffers[1].draw.b0 = 24;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 19);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            for (self->ext.stainedGlass.prim1 = prim; prim != NULL;
                 prim = prim->next) {
                prim->tpage = 15;
                prim->clut = PAL_STAINED_GLASS_F;
                prim->u0 = prim->u2 = 35;
                prim->u1 = prim->u3 = 92;
                prim->v0 = prim->v1 = 1;
                prim->v2 = prim->v3 = 62;
                PGREY(prim, 0) = 128;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->priority = 84;
                prim->drawMode = DRAW_DEFAULT;
            }
            for (prim = self->ext.stainedGlass.prim1, count = 0; count < 4;
                 prim = prim->next, count++) {
                prim->clut = 5;
                prim->u0 = prim->u2 = 129;
                prim->u1 = prim->u3 = 174;
                prim->v0 = prim->v1 = 1;
                prim->v2 = prim->v3 = 126;
                prim->priority = 80;
            }
            prim = self->ext.stainedGlass.prim1;
            PGREY(prim, 0) = 32;
            PGREY(prim, 1) = 48;
            PGREY(prim, 2) = 64;
            PGREY(prim, 3) = 48;
            prim = prim->next;
            prim->clut = PAL_STAGE_NAME_15F;
            PGREY(prim, 0) = 24;
            PGREY(prim, 1) = 24;
            PGREY(prim, 2) = 24;
            PGREY(prim, 3) = 24;
            prim->priority = 81;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            PGREY(prim, 0) = 80;
            PGREY(prim, 1) = 48;
            PGREY(prim, 2) = 160;
            PGREY(prim, 3) = 48;
            prim = prim->next;
            prim->clut = PAL_STAGE_NAME_15F;
            prim->r0 = 24;
            prim->g0 = 24;
            prim->b0 = 24;
            prim->r2 = 24;
            prim->g2 = 24;
            prim->b2 = 24;
            PGREY(prim, 1) = 24;
            PGREY(prim, 3) = 24;
            prim->priority = 81;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->type = PRIM_G4;
            prim->r0 = 64;
            prim->g0 = 24;
            prim->b0 = 72;
            LOW(prim->r1) = LOW(prim->r0);
            prim->r2 = 200;
            prim->g2 = 24;
            prim->b2 = 104;
            LOW(prim->r2) = LOW(prim->r3);
            prim->priority = 82;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
        } else {
            DestroyEntity(self);
            return;
        }
        rect.x = 0;
        rect.y = 256;
        rect.w = 16;
        rect.h = 1;
        color.r = 24;
        color.g = 24;
        color.b = 24;
        StainedGlassBlendPalette(&rect, PAL_STAINED_GLASS_F,
                                 PAL_STAINED_GLASS_205, COLORS_PER_PAL, &color);
        break;
    case 1:
        SetGeomScreen(1024);
        SetGeomOffset(128, 160);
        prim = self->ext.stainedGlass.prim1;
        for (transVectorPtr = D_us_801826EC, count = 0; count < 8; count++,
            transVectorPtr++) {
            RotMatrix(&D_us_8018277C, &mtx);
            transVector = *transVectorPtr;
            transVector.vx += self->posX.i.hi - 128;
            transVector.vy += self->posY.i.hi - 160;
            transVector.vz += 1024;
            SETROTMATRIX(&mtx);
            gte_SetTransVector(&transVector);
            if (!count) {
                gte_ldv0(&D_us_801826E4);
                gte_rtps();
#ifdef VERSION_PSP
                gte_stsxy((long*)&rect2.w);
                tempX = (u16)LOW(rect2.w);
                tempY = LOW(rect2.w) >> 16;
#else
                gte_stsxy((long*)&rect1.x);
                prim->drawMode = DRAW_COLORS;
                tempX = rect1.x;
                tempY = LOW(rect1.x) >> 16;
#endif

                prim->x0 = prim->x2 = tempX - 45;
                prim->x1 = prim->x3 = tempX;
                prim->y0 = prim->y1 = tempY - 62;
                prim->y2 = prim->y3 = tempY + 62;
#ifdef VERSION_PSP
                prim->drawMode = DRAW_COLORS;
#endif
                prim = prim->next;
                prim->x0 = prim->x2 = tempX - 45;
                prim->x1 = prim->x3 = tempX;
                prim->y0 = prim->y1 = tempY - 62;
                prim->y2 = prim->y3 = tempY + 62;
                prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                prim = prim->next;
                prim->x0 = prim->x2 = tempX + 45;
                prim->x1 = prim->x3 = tempX;
                prim->y0 = prim->y1 = tempY - 62;
                prim->y2 = prim->y3 = tempY + 62;
                prim->drawMode = DRAW_COLORS;
                prim = prim->next;
                prim->x0 = prim->x2 = tempX + 45;
                prim->x1 = prim->x3 = tempX;
                prim->y0 = prim->y1 = tempY - 62;
                prim->y2 = prim->y3 = tempY + 62;
                prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                prim = prim->next;
                prim->x0 = tempX - 8;
                prim->x1 = tempX + 8;
                prim->x2 = self->posX.i.hi - 24;
                prim->x3 = self->posX.i.hi + 24;
                prim->y0 = prim->y1 = tempY + 56;
                prim->y2 = prim->y3 = self->posY.i.hi + 194;
                prim->drawMode = DRAW_COLORS;
                prim = prim->next;
            } else {
#ifdef VERSION_PSP
                gte_ldv0(&D_us_801826C4);
                gte_ldv1(&D_us_801826CC);
                gte_ldv2(&D_us_801826D4);
                gte_rtpt();
                gte_stsxy3(&rect2.w, &rect2.x, &rect1.w);
                if (rect1.h >= 0) {
#else
                gte_ldv3(&D_us_801826C4, &D_us_801826CC, &D_us_801826D4);
                gte_rtpt();
                gte_stsxy3(&rect1.x, &rect1.w, &rect2.x);
                if (rect2.y >= 0) {
#endif
                    gte_ldv0(&D_us_801826DC);
                    gte_rtps();

// psx uses temp variables here where psp does not and the ordering is a bit
// different between the two
#ifdef VERSION_PSP
                    gte_stsxy((long*)&rect1.x);
                    midpoint1 =
                        ((LOW(rect2.w) + LOW(rect2.x)) / 2) & 0xFFFF0000;
                    midpoint1 |= (rect2.w + rect2.x) >> 1;
                    midpoint2 =
                        (((LOW(rect1.w) + LOW(rect1.x)) / 2) & 0xFFFF0000);
                    midpoint2 |= ((rect1.w + rect1.x) >> 1);
                    prim->clut = ((count * 2) + PAL_STAINED_GLASS_205);
                    LOW(prim->x0) = LOW(rect2.w);
                    LOW(prim->x1) = midpoint1;
                    LOW(prim->x2) = LOW(rect1.w);
                    LOW(prim->x3) = midpoint2;
                    prim->drawMode = DRAW_DEFAULT;
                    prim = prim->next;
                    prim->clut = ((count * 2) + PAL_STAINED_GLASS_205);
                    LOW(prim->x0) = LOW(rect2.x);
                    LOW(prim->x1) = midpoint1;
                    LOW(prim->x2) = LOW(rect1.x);
                    LOW(prim->x3) = midpoint2;
                    prim->drawMode = DRAW_DEFAULT;
                    prim = prim->next;
#else
                    gte_stsxy((long*)&rect2.w);
                    tempRect1x = LOW(rect1.x);
                    tempRect1w = LOW(rect1.w);
                    prim->clut = ((count * 2) + PAL_STAINED_GLASS_205);
                    prim->drawMode = DRAW_DEFAULT;
                    tempRect2x = LOW(rect2.x);
                    tempRect2w = LOW(rect2.w);
                    midpoint1 = ((tempRect1x + tempRect1w) / 2) & 0xFFFF0000;
                    midpoint1 |= (rect1.x + rect1.w) >> 1;
                    midpoint2 = (((tempRect2x + tempRect2w) / 2) & 0xFFFF0000);
                    midpoint2 |= ((rect2.x + rect2.w) >> 1);
                    LOW(prim->x0) = tempRect1x;
                    LOW(prim->x1) = midpoint1;
                    LOW(prim->x2) = tempRect2x;
                    LOW(prim->x3) = midpoint2;
                    prim = prim->next;
                    prim->clut = ((count * 2) + PAL_STAINED_GLASS_205);
                    LOW(prim->x0) = tempRect1w;
                    LOW(prim->x1) = midpoint1;
                    LOW(prim->x2) = tempRect2w;
                    LOW(prim->x3) = midpoint2;
                    prim->drawMode = DRAW_DEFAULT;
                    prim = prim->next;
#endif
                }
            }
        }
        for (; prim != NULL; prim = prim->next) {
            prim->drawMode = DRAW_HIDE;
        }
        break;
    }
}
