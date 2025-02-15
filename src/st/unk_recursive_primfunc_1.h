// SPDX-License-Identifier: AGPL-3.0-or-later

// 0------1------2
// |             |
// |             |
// 3      4      5
// |             |
// |             |
// 6------7------8

// clang-format off
static s16 g_QuadIndices1[] = {
    0, 1, 3, 4, //top left quad
    1, 2, 4, 5, //top right quad
    3, 4, 6, 7, //bottom left quad
    4, 5, 7, 8, //bottom right quad
};
// clang-format on

// dataPtr holds, in order:
// a Primitive, an array of 9 SVECTORs, an array of 10 uvPairs, and a pointer to
// another of dataPtr. Pointer type on dataPtr is
// fake, but needed for Windows.

// dataPtr gets filled up with scratch data used to split srcPrim into 4 smaller
// quads

Primitive* UnkRecursivePrimFunc1(
    SVECTOR* p0, SVECTOR* p1, SVECTOR* p2, SVECTOR* p3, Primitive* srcPrim,
    s32 iterations, Primitive* dstPrim, u8* dataPtr) {
    long p, flag;
    s32 i;
    Primitive* tempPrim;
    s16* indices;
    s32 rotTransResult;
    SVECTOR* points;
    uvPair* uv_values;

    if (dstPrim == NULL) {
        return NULL;
    }
    tempPrim = (Primitive*)dataPtr;
    dataPtr += sizeof(Primitive);
    points = (SVECTOR*)dataPtr;
    dataPtr += sizeof(SVECTOR) * 9;

    points[0] = *p0;
    points[2] = *p1;
    points[6] = *p2;
    points[8] = *p3;

    uv_values = (uvPair*)dataPtr;
    dataPtr += sizeof(uvPair) * 10;

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
    indices = g_QuadIndices1;
    for (i = 0; i < 4; i++) {
        s32 idx1 = *indices++;
        s32 idx2 = *indices++;
        s32 idx3 = *indices++;
        s32 idx4 = *indices++;
        rotTransResult = RotTransPers4(
            &points[idx1], &points[idx2], &points[idx3], &points[idx4],
            (long*)&tempPrim->x0, (long*)&tempPrim->x1, (long*)&tempPrim->x2,
            (long*)&tempPrim->x3, &p, &flag);
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
            dstPrim = UnkRecursivePrimFunc1(
                &points[idx1], &points[idx2], &points[idx3], &points[idx4],
                tempPrim, iterations - 1, dstPrim, dataPtr);
        }
    }
    return dstPrim;
}
