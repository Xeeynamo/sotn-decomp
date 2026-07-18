// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"
#include <scratchpad.h>

static SVECTOR vec_negneg = {-0x100, 0, -0x100};
static SVECTOR vec_posneg = {0x100, 0, -0x100};
static SVECTOR vec_negpos = {-0x100, 0, 0x100};
static SVECTOR vec_pospos = {0x100, 0, 0x100};
static CVECTOR D_8018136C = {0x80, 0xC0, 0xF0, 0x00};
static s16 D_80181370[] = {0, 1, 3, 4, 1, 2, 4, 5, 3, 4, 6, 7, 4, 5, 7, 8};

// See also: UnkRecursivePrimFunc1. Strong overlap, but also some different
// logic.
static Primitive* SkySwirlHelper(
    SVECTOR* p0, SVECTOR* p1, SVECTOR* p2, SVECTOR* p3, Primitive* srcPrim,
    s32 iterations, Primitive* dstPrim, u8* dataPtr) {
    s32 i;
    Primitive* tempPrim;
    s16* indices;
    SVECTOR* points;
    uvPair* uv_values;
    long flag;
    long p;
    s32 rotTransResult;

    if (dstPrim == NULL) {
        return NULL;
    }
    tempPrim = (Primitive*)dataPtr;
    dataPtr += sizeof(Primitive);
    points = (SVECTOR*)dataPtr;
    dataPtr += sizeof(SVECTOR) * 9;
    uv_values = (uvPair*)dataPtr;
    dataPtr += sizeof(uvPair) * 10;

    points[0] = *p0;
    points[2] = *p1;
    points[6] = *p2;
    points[8] = *p3;

    points[1].vx = (points[0].vx + points[2].vx + 1) >> 1;
    points[1].vy = (points[0].vy + points[2].vy + 1) >> 1;
    points[1].vz = (points[0].vz + points[2].vz + 1) >> 1;
    points[7].vx = (points[6].vx + points[8].vx + 1) >> 1;
    points[7].vy = (points[6].vy + points[8].vy + 1) >> 1;
    points[7].vz = (points[6].vz + points[8].vz + 1) >> 1;
    points[3].vx = (points[0].vx + points[6].vx + 1) >> 1;
    points[3].vy = (points[0].vy + points[6].vy + 1) >> 1;
    points[3].vz = (points[0].vz + points[6].vz + 1) >> 1;
    points[5].vx = (points[2].vx + points[8].vx + 1) >> 1;
    points[5].vy = (points[2].vy + points[8].vy + 1) >> 1;
    points[5].vz = (points[2].vz + points[8].vz + 1) >> 1;
    points[4].vx = (points[3].vx + points[5].vx + 1) >> 1;
    points[4].vy = (points[3].vy + points[5].vy + 1) >> 1;
    points[4].vz = (points[3].vz + points[5].vz + 1) >> 1;

    uv_values[0] = *(uvPair*)&srcPrim->u0;
    uv_values[2] = *(uvPair*)&srcPrim->u1;
    uv_values[6] = *(uvPair*)&srcPrim->u2;
    uv_values[8] = *(uvPair*)&srcPrim->u3;
    uv_values[1].u = (uv_values[0].u + uv_values[2].u + 1) >> 1;
    uv_values[1].v = (uv_values[0].v + uv_values[2].v + 1) >> 1;
    uv_values[7].u = (uv_values[6].u + uv_values[8].u + 1) >> 1;
    uv_values[7].v = (uv_values[6].v + uv_values[8].v + 1) >> 1;
    uv_values[3].u = (uv_values[0].u + uv_values[6].u + 1) >> 1;
    uv_values[3].v = (uv_values[0].v + uv_values[6].v + 1) >> 1;
    uv_values[5].u = (uv_values[2].u + uv_values[8].u + 1) >> 1;
    uv_values[5].v = (uv_values[2].v + uv_values[8].v + 1) >> 1;
    uv_values[4].u = (uv_values[3].u + uv_values[5].u + 1) >> 1;
    uv_values[4].v = (uv_values[3].v + uv_values[5].v + 1) >> 1;

    *tempPrim = *srcPrim;
    D_8018136C.cd = srcPrim->type;
    indices = D_80181370;
    for (i = 0; i < 4; i++) {
        s32 idx1 = *indices++;
        s32 idx2 = *indices++;
        s32 idx3 = *indices++;
        s32 idx4 = *indices++;

        RotTransPers(&points[idx1], (long*)&tempPrim->x0, &p, &flag);
        DpqColor(&D_8018136C, p, &tempPrim->r0);

        RotTransPers(&points[idx2], (long*)&tempPrim->x1, &p, &flag);
        DpqColor(&D_8018136C, p, &tempPrim->r1);

        RotTransPers(&points[idx3], (long*)&tempPrim->x2, &p, &flag);
        DpqColor(&D_8018136C, p, &tempPrim->r2);

        rotTransResult =
            RotTransPers(&points[idx4], (long*)&tempPrim->x3, &p, &flag);
        DpqColor(&D_8018136C, p, &tempPrim->r3);

        *(uvPair*)&tempPrim->u0 = uv_values[idx1];
        *(uvPair*)&tempPrim->u1 = uv_values[idx2];
        *(uvPair*)&tempPrim->u2 = uv_values[idx3];
        *(uvPair*)&tempPrim->u3 = uv_values[idx4];
        if (iterations == 1) {
            if (rotTransResult > 0) {
                Primitive* origNext = dstPrim->next;
                *dstPrim = *tempPrim;
                dstPrim->next = origNext;
                dstPrim = dstPrim->next;
                if (dstPrim == NULL) {
                    return NULL;
                }
            }
        } else {
            dstPrim = SkySwirlHelper(
                &points[idx1], &points[idx2], &points[idx3], &points[idx4],
                tempPrim, iterations - 1, dstPrim, dataPtr);
        }
    }
    return dstPrim;
}

// sky animation during death cutscene
void EntityDeathSkySwirl(Entity* self) {
    Primitive* prim;
    Primitive* prim2;
    s32 primIndex;
    SVECTOR sVec;
    VECTOR vec;
    MATRIX mtx;

    if (!self->step) {
        if (g_CastleFlags[IVE_BEEN_ROBBED]) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 65);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.deathSkySwirl.prim = prim;
        prim->tpage = 0x12;
        prim->clut = 0x1F;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0xFF;
        prim->v0 = prim->v1 = 0x80;
        prim->v2 = prim->v3 = 0xFF;
        prim->priority = 0x1F;
        prim->drawMode = DRAW_DEFAULT;
    }
    g_BgLayers[0].flags &= 0xFFFE;
    self->ext.deathSkySwirl.unk84 -= 32;
    SetGeomScreen(256);
    SetGeomOffset(128, 192);
    SetFogNear(256, 256);
    SetFarColor(96, 96, 96);
    sVec.vx = 0;
    sVec.vy = self->ext.deathSkySwirl.unk84;
    sVec.vz = 0;
    RotMatrix(&sVec, &mtx);
    vec.vx = 0;
    vec.vy = -0xC0;
    vec.vz = 0x200;
    TransMatrix(&mtx, &vec);
    SetRotMatrix(&mtx);
    SetTransMatrix(&mtx);
    prim = self->ext.deathSkySwirl.prim;
    prim->drawMode = DRAW_COLORS;

    prim2 = prim->next;
    prim2 = SkySwirlHelper(&vec_negneg, &vec_posneg, &vec_negpos, &vec_pospos,
                           prim, 3, prim2, (u8*)SPAD(0));
    prim->drawMode = DRAW_HIDE;
    while (prim2 != NULL) {
        prim2->drawMode = DRAW_HIDE;
        prim2 = prim2->next;
    }
}
