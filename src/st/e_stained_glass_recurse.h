// SPDX-License-Identifier: AGPL-3.0-or-later

Primitive* StainedGlassRecurseDepth(
    SVECTOR* p0, SVECTOR* p1, SVECTOR* p2, SVECTOR* p3, Primitive* srcPrim,
    s32 iterations, Primitive* dstPrim, u8* dataPtr) {
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

        gte_ldv0(&points[index3]);
        gte_rtps();

#ifdef VERSION_PSP
        gte_stsxy((long*)tempPrim + sizeof(uvPair) * 6);
#else
        gte_stsxy((long*)&tempPrim->x3);
#endif

        gte_ldv3(&points[index0], &points[index1], &points[index2]);
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
