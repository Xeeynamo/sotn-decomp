// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rdai.h"

#include <scratchpad.h>

extern EInit g_EInitInteractable;

static s16 indices[] = {0, 2, 3, 5, 3, 5, 6, 8};
static SVECTOR glass_points_0 = {-208, -192, 0};
static SVECTOR glass_points_1 = {208, -192, 0};
static SVECTOR glass_points_2 = {-208, 192, 0};
static SVECTOR glass_points_3 = {208, 192, 0};
static SVECTOR light_points_0 = {-208, -96, 0};
static SVECTOR light_points_1 = {208, -96, 0};
static SVECTOR light_points_2 = {-208, 96, 0};
static SVECTOR light_points_3 = {208, 96, 0};
// Atypical use of this vector.  It uses the normal vector values normally, but
// also uses pad to store the number of recursions of StainedGlassRecurseDepth
static VECTOR params[] = {
    {FLT(0.0625), 0, FLT(0.125), 3},   {FLT(0.0625), 0, FLT(0.28125), 2},
    {FLT(0.0625), 0, FLT(0.4375), 2},  {FLT(0.0625), 0, FLT(0.59375), 0},
    {FLT(0.0625), 0, FLT(0.75), 0},    {FLT(0.0625), 0, FLT(0.90625), 0},
    {FLT(-0.0625), 0, FLT(0.125), 3},  {FLT(-0.0625), 0, FLT(0.28125), 2},
    {FLT(-0.0625), 0, FLT(0.4375), 2}, {FLT(-0.0625), 0, FLT(0.59375), 0},
    {FLT(-0.0625), 0, FLT(0.75), 0},   {FLT(-0.0625), 0, FLT(0.90625), 0}};

static s16 y_vals[] = {1024,  1024,  1024,  1024,  1024,  1024,
                       -1024, -1024, -1024, -1024, -1024, -1024};
static CVECTOR colors[] = {
    {128, 128, 128, 32}, {120, 120, 120, 36}, {112, 112, 112, 40},
    {104, 104, 104, 48}, {96, 96, 96, 56},    {88, 88, 88, 64},
    {96, 96, 96, 4},     {88, 88, 88, 4},     {80, 80, 80, 4},
    {72, 72, 72, 4},     {64, 64, 64, 4},     {56, 56, 56, 4}};

static SVECTOR light_rot_vector = {0, 0, 0}; // bss on pspeu
/*
static SVECTOR bg_points_0 = {-192, -64, 0};
static SVECTOR bg_points_1 = {192, -64, 0};
static SVECTOR bg_points_2 = {-192, 64, 0};
static SVECTOR bg_points_3 = {192, 64, 0};
static SVECTOR bg_pos_vector = {0, 0, 0}; // bss on pspeu
static VECTOR trans_vectors[] = {
    {0, 0, FLT(1)},        {0, -224, FLT(0.125)}, {0, -224, FLT(0.25)},
    {0, -224, FLT(0.375)}, {0, -224, FLT(0.5)},   {0, -224, FLT(0.625)},
    {0, -224, FLT(0.75)},  {0, -224, FLT(0.875)}, {0, -224, FLT(1)}};
static SVECTOR bg_rot_vector = {0, 0, 0}; // bss on pspeu
*/

#include "../e_stained_glass_blend.h"

Primitive* StainedGlassRecurse(
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
    indexPtr = indices;
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
                dstPrim = StainedGlassRecurse(
                    &points[index0], &points[index1], &points[index2],
                    &points[index3], tempPrim, iterations - 1, dstPrim,
                    dataPtr);
            }
        }
    }
    return dstPrim;
}

// Renders the stained glass and "sunlight" effect
void func_us_801B2C28(Entity* self) {
    s32 primIndex;
    s32 p;
    s32 flag;
    s16 midpointX, midpointY;
    SVECTOR rotVector;
    VECTOR transVector;
    MATRIX mtx;
    u8 transparent; // u8, but used as bool
    s32 iterations;
    s16* yValsPtr;
    VECTOR* paramsPtr;
    CVECTOR* colorPtr;
    s32 count;
    Primitive* glassPrim;
    Primitive* lightPrim;
    Primitive* tempPrim;

    switch (self->step) {
    case 0: // init
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 60);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            glassPrim = &g_PrimBuf[primIndex];
            self->ext.stainedGlass.glassPrim = glassPrim;
            for (count = 0; count < 12; count++) {
                glassPrim->tpage = 15;
                glassPrim->clut = PAL_STAINED_GLASS;
                glassPrim->u0 = glassPrim->u2 = 4;
                glassPrim->u1 = glassPrim->u3 = 28;
                glassPrim->v0 = glassPrim->v1 = 1;
                glassPrim->v2 = glassPrim->v3 = 174;
                PGREY(glassPrim, 0) = 96;
                LOW(glassPrim->r1) = LOW(glassPrim->r0);
                LOW(glassPrim->r2) = LOW(glassPrim->r0);
                LOW(glassPrim->r3) = LOW(glassPrim->r0);
                glassPrim->priority = 86;
                glassPrim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
                glassPrim = glassPrim->next;
            }
            for (self->ext.stainedGlass.lightPrim = glassPrim;
                 glassPrim != NULL; glassPrim = glassPrim->next) {
                glassPrim->drawMode = DRAW_HIDE;
            }
            return;
        }
        DestroyEntity(self);
        return;
    case 1: // render
        SetGeomScreen(1024);
        SetGeomOffset(128, 160);
        glassPrim = self->ext.stainedGlass.glassPrim;
        lightPrim = self->ext.stainedGlass.lightPrim;
        paramsPtr = params;
        yValsPtr = y_vals;
        colorPtr = colors;
        for (count = 0; count < 12; count++) {
            rotVector.vx = 0;
            rotVector.vy = *yValsPtr;
            rotVector.vz = 0;
            RotMatrix(&rotVector, &mtx);
            RotMatrixZ(0x800, &mtx);
            transVector = *paramsPtr;
            if (transVector.vx > 0) {
                transparent = true;
                glassPrim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            } else {
                transparent = false;
                glassPrim->drawMode = DRAW_COLORS;
            }
            iterations = paramsPtr->pad;
            transVector.vx += self->posX.i.hi - 128;
            transVector.vy += self->posY.i.hi - 160;
            transVector.vz += FLT(0.25);
            TransMatrix(&mtx, &transVector);
            SetRotMatrix(&mtx);
            SetTransMatrix(&mtx);
            CVEC(glassPrim->r0) = *colorPtr;
            LOW(glassPrim->r1) = LOW(glassPrim->r0);
            LOW(glassPrim->r2) = LOW(glassPrim->r0);
            LOW(glassPrim->r3) = LOW(glassPrim->r0);
            glassPrim->type = PRIM_GT4;
            if (iterations) {
                lightPrim = StainedGlassRecurse(
                    &glass_points_0, &glass_points_1, &glass_points_2,
                    &glass_points_3, glassPrim, iterations, lightPrim,
                    (u8*)SP(0));
                glassPrim->drawMode = DRAW_HIDE;
            }
            RotTransPers4(&glass_points_0, &glass_points_1, &glass_points_2, &glass_points_3, 
                         (long*)&glassPrim->x0, (long*)&glassPrim->x1, (long*)&glassPrim->x2,
                  (long*)&glassPrim->x3, (long*)&p, (long*)&flag);

            // Renders the light "coming through" the right side glass
            if (transparent) {
                tempPrim = lightPrim->next;
                *lightPrim = *glassPrim;
                lightPrim->next = tempPrim;

                lightPrim->clut = PAL_FILL_WHITE;
                lightPrim->priority = glassPrim->priority - 1;
                lightPrim->drawMode = DRAW_COLORS;
                lightPrim->r0 = lightPrim->g0 = lightPrim->b0 = colorPtr->cd;
                LOW(lightPrim->r1) = LOW(lightPrim->r0);
                lightPrim->r2 = lightPrim->g2 = lightPrim->b2 =
                    colorPtr->cd / 2;
                LOW(lightPrim->r3) = LOW(lightPrim->r2);

                lightPrim = lightPrim->next;
                tempPrim = lightPrim->next;
                *lightPrim = *glassPrim;
                lightPrim->next = tempPrim;

                rotVector.vx = 0;
                rotVector.vy = *yValsPtr;
                rotVector.vz = 1024;
                RotMatrix(&light_rot_vector, &mtx);
                RotMatrixY(rotVector.vy, &mtx);
                RotMatrixZ(rotVector.vz, &mtx);
                RotMatrixZ(0x800, &mtx);
                transVector = *paramsPtr;
                transVector.vx = 96;
                transVector.vy = -256;
                transVector.vx += self->posX.i.hi - 128;
                transVector.vy += self->posY.i.hi - 160;
                transVector.vz += 1024;
                TransMatrix(&mtx, &transVector);
                SetRotMatrix(&mtx);
                SetTransMatrix(&mtx);
                CVEC(lightPrim->r0) = *colorPtr;
                LOW(lightPrim->r1) = LOW(lightPrim->r0);
                LOW(lightPrim->r2) = LOW(lightPrim->r0);
                LOW(lightPrim->r3) = LOW(lightPrim->r0);
                lightPrim->type = PRIM_GT4;
                RotTransPers4(&light_points_0, &light_points_1, &light_points_2, &light_points_3, 
                         (long*)&lightPrim->x0, (long*)&lightPrim->x1, (long*)&lightPrim->x2,
                  (long*)&lightPrim->x3, (long*)&p, (long*)&flag);
                lightPrim->clut = PAL_STAINED_GLASS_LIGHT;
                lightPrim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                                      DRAW_COLORS | DRAW_TRANSP;
                midpointX = (lightPrim->x0 + lightPrim->x2) / 2;
                midpointY = (lightPrim->y0 + lightPrim->y1) / 2;
                lightPrim = lightPrim->next;
                tempPrim = lightPrim->next;
                *lightPrim = *glassPrim;
                lightPrim->next = tempPrim;
                lightPrim->clut = PAL_FILL_WHITE;
                lightPrim->priority = glassPrim->priority + 1;
                lightPrim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                lightPrim->r0 = 24;
                lightPrim->g0 = 8;
                lightPrim->b0 = 32;
                LOW(lightPrim->r1) = LOW(lightPrim->r0);
                lightPrim->r2 = 8;
                lightPrim->g2 = 24;
                lightPrim->b2 = 8;
                lightPrim->r3 = lightPrim->g3 = lightPrim->b3 = 0;
                LOW(lightPrim->x0) = LOW(glassPrim->x1);
                LOW(lightPrim->x1) = LOW(glassPrim->x0);
                LOW(lightPrim->x2) = LOW(glassPrim->x3);
                lightPrim->x3 = midpointX;
                lightPrim->y3 = midpointY;
                lightPrim = lightPrim->next;
            }
            colorPtr++;
            yValsPtr++;
            paramsPtr++;
            glassPrim = glassPrim->next;
        }
        for (count = 0; lightPrim; lightPrim = lightPrim->next) {
            count++;
            lightPrim->drawMode = DRAW_HIDE;
        }
        FntPrint("rest %x\n", count);
    }
}

INCLUDE_ASM("st/rdai/nonmatchings/e_stained_glass", func_us_801B3368);
