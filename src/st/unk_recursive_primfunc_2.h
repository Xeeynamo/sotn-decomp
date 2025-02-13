// SPDX-License-Identifier: AGPL-3.0-or-later
static s16 g_UnkRecursPrimInds[] = {
    0, 1, 3, 4, 1, 2, 4, 5, 3, 4, 6, 7, 4, 5, 7, 8,
#if !defined(STAGE_IS_NZ0) && !defined(STAGE_IS_NO1) &&                        \
    !defined(STAGE_IS_CHI) && STAGE != STAGE_ST0 && !defined(STAGE_IS_LIB)
    0, 0,
#endif
#if defined(VERSION_BETA)
    0, 0
#endif
};

// dataPtr holds, in order:
// A Primitive, an array of 9 CVECTORs, an array of 9 Point16s, an array of 10
// uvPairs, and a pointer to another of dataPtr. Pointer type on dataPtr is
// fake, but needed for Windows.

Primitive* UnkRecursivePrimFunc2(
    Primitive* prim, s32 iterations, Primitive* prim2, u8* dataPtr) {
    s32 i;
    Primitive* tempPrim;
    Point16* points;
    CVECTOR* colors;
    uvPair* uv_values;
    s16* indices;

    if (prim2 == NULL) {
        return NULL;
    }
    tempPrim = (Primitive*)dataPtr;
    dataPtr += sizeof(Primitive);
    colors = (CVECTOR*)dataPtr;
    dataPtr += sizeof(CVECTOR) * 9;

    points = (Point16*)dataPtr;
    dataPtr += sizeof(Point16) * 9;
    uv_values = (uvPair*)dataPtr;
    dataPtr += sizeof(uvPair) * 10;

    colors[0] = *(CVECTOR*)&prim->r0;
    colors[2] = *(CVECTOR*)&prim->r1;
    colors[6] = *(CVECTOR*)&prim->r2;
    colors[8] = *(CVECTOR*)&prim->r3;

    colors[1].r = ((colors[0].r + colors[2].r + 1) >> 1);
    colors[1].g = ((colors[0].g + colors[2].g + 1) >> 1);
    colors[1].b = ((colors[0].b + colors[2].b + 1) >> 1);

    colors[7].r = ((colors[6].r + colors[8].r + 1) >> 1);
    colors[7].g = ((colors[6].g + colors[8].g + 1) >> 1);
    colors[7].b = ((colors[6].b + colors[8].b + 1) >> 1);

    colors[3].r = ((colors[0].r + colors[6].r + 1) >> 1);
    colors[3].g = ((colors[0].g + colors[6].g + 1) >> 1);
    colors[3].b = ((colors[0].b + colors[6].b + 1) >> 1);

    colors[5].r = ((colors[2].r + colors[8].r + 1) >> 1);
    colors[5].g = ((colors[2].g + colors[8].g + 1) >> 1);
    colors[5].b = ((colors[2].b + colors[8].b + 1) >> 1);

    colors[4].r = ((colors[3].r + colors[5].r + 1) >> 1);
    colors[4].g = ((colors[3].g + colors[5].g + 1) >> 1);
    colors[4].b = ((colors[3].b + colors[5].b + 1) >> 1);

    uv_values[0] = *(uvPair*)&prim->u0;
    uv_values[2] = *(uvPair*)&prim->u1;
    uv_values[6] = *(uvPair*)&prim->u2;
    uv_values[8] = *(uvPair*)&prim->u3;
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

    points[0] = *(Point16*)&prim->x0;
    points[2] = *(Point16*)&prim->x1;
    points[6] = *(Point16*)&prim->x2;
    points[8] = *(Point16*)&prim->x3;
    points[1].x = ((points[0].x + points[2].x + 1) >> 1);
    points[1].y = ((points[0].y + points[2].y + 1) >> 1);
    points[7].x = ((points[6].x + points[8].x + 1) >> 1);
    points[7].y = ((points[6].y + points[8].y + 1) >> 1);
    points[3].x = ((points[0].x + points[6].x + 1) >> 1);
    points[3].y = ((points[0].y + points[6].y + 1) >> 1);
    points[5].x = ((points[2].x + points[8].x + 1) >> 1);
    points[5].y = ((points[2].y + points[8].y + 1) >> 1);
    points[4].x = ((points[3].x + points[5].x + 1) >> 1);
    points[4].y = ((points[3].y + points[5].y + 1) >> 1);

    *tempPrim = *prim;
    indices = g_UnkRecursPrimInds;
    for (i = 0; i < 4; i++) {
        s32 idx1 = *indices++;
        s32 idx2 = *indices++;
        s32 idx3 = *indices++;
        s32 idx4 = *indices++;
        *(uvPair*)&tempPrim->u0 = uv_values[idx1];
        *(uvPair*)&tempPrim->u1 = uv_values[idx2];
        *(uvPair*)&tempPrim->u2 = uv_values[idx3];
        *(uvPair*)&tempPrim->u3 = uv_values[idx4];
        *(Point16*)&tempPrim->x0 = points[idx1];
        *(Point16*)&tempPrim->x1 = points[idx2];
        *(Point16*)&tempPrim->x2 = points[idx3];
        *(Point16*)&tempPrim->x3 = points[idx4];
        *(CVECTOR*)&tempPrim->r0 = colors[idx1];
        *(CVECTOR*)&tempPrim->r1 = colors[idx2];
        *(CVECTOR*)&tempPrim->r2 = colors[idx3];
        *(CVECTOR*)&tempPrim->r3 = colors[idx4];

        tempPrim->type = prim->type;
        if (iterations == 1) {
            Primitive* swap = prim2->next;
            *prim2 = *tempPrim;
            prim2->next = swap;
            prim2 = prim2->next;
            if (prim2 == NULL) {
                return NULL;
            }
        } else {
            prim2 =
                UnkRecursivePrimFunc2(tempPrim, iterations - 1, prim2, dataPtr);
        }
    }
    return prim2;
}
