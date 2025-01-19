// SPDX-License-Identifier: AGPL-3.0-or-later
extern u16 g_UnkRecursPrimVecOrder[];

// arg7 holds, in order:
// a Primitive, an array of 9 SVECTORs, an array of 10 uvPairs, and a pointer to
// another of arg7.
// arg7 is not actually u8* but windows doesn't like void* I guess?

Primitive* UnkRecursivePrimFunc1(
    SVECTOR* arg0, SVECTOR* arg1, SVECTOR* arg2, SVECTOR* arg3, Primitive* arg4,
    s32 arg5, Primitive* arg6, u8* arg7) {
    s32 unused1;
    s32 unused2;
    s32 i;
    Primitive* prim1;
    Primitive* prim2;
    s32 vecIdx1;
    s32 vecIdx2;
    s32 vecIdx3;
    s32 vecIdx4;
    s16* vecIndices;
    s32 rotTransResult;
    SVECTOR* vectors;
    uvPair* uv_values;
    Primitive* nextArg6;

    if (arg6 == NULL) {
        return NULL;
    }
    prim2 = (Primitive*)arg7;
    arg7 += 0x34;
    vectors = (SVECTOR*)arg7;
    arg7 += 0x48;

    vectors[0] = *arg0;
    vectors[2] = *arg1;
    vectors[6] = *arg2;
    vectors[8] = *arg3;

    uv_values = (uvPair*)arg7;
    arg7 += 0x14; // This is effectively arg7 = arg7->next, since this covers
                  // the full size of arg7.

    prim1 = prim2;
    vectors[1].vx = (vectors[0].vx + vectors[2].vx + 1) >> 1;
    vectors[1].vy = (vectors[0].vy + vectors[2].vy + 1) >> 1;
    vectors[1].vz = (vectors[0].vz + vectors[2].vz + 1) >> 1;
    vectors[7].vx = (vectors[6].vx + vectors[8].vx + 1) >> 1;
    vectors[7].vy = (vectors[6].vy + vectors[8].vy + 1) >> 1;
    vectors[7].vz = (vectors[6].vz + vectors[8].vz + 1) >> 1;
    vectors[3].vx = (vectors[0].vx + vectors[6].vx + 1) >> 1;
    vectors[3].vy = (vectors[0].vy + vectors[6].vy + 1) >> 1;
    vectors[3].vz = (vectors[0].vz + vectors[6].vz + 1) >> 1;
    vectors[5].vx = (vectors[2].vx + vectors[8].vx + 1) >> 1;
    vectors[5].vy = (vectors[2].vy + vectors[8].vy + 1) >> 1;
    vectors[5].vz = (vectors[2].vz + vectors[8].vz + 1) >> 1;
    vectors[4].vx = (vectors[3].vx + vectors[5].vx + 1) >> 1;
    vectors[4].vy = (vectors[3].vy + vectors[5].vy + 1) >> 1;
    vectors[4].vz = (vectors[3].vz + vectors[5].vz + 1) >> 1;

    uv_values[0] = *(uvPair*)&arg4->u0;
    uv_values[2] = *(uvPair*)&arg4->u1;
    uv_values[6] = *(uvPair*)&arg4->u2;
    uv_values[8] = *(uvPair*)&arg4->u3;
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

    *prim1 = *arg4;
    vecIndices = (s16*)&g_UnkRecursPrimVecOrder;
    for (i = 0; i < 4; i++) {
        vecIdx1 = *vecIndices++;
        vecIdx2 = *vecIndices++;
        vecIdx3 = *vecIndices++;
        vecIdx4 = *vecIndices++;
        rotTransResult = RotTransPers4(
            &vectors[vecIdx1], &vectors[vecIdx2], &vectors[vecIdx3],
            &vectors[vecIdx4], (long*)&prim2->x0, (long*)&prim2->x1,
            (long*)&prim2->x2, (long*)&prim2->x3, (long*)&unused1,
            (long*)&unused2);
        *(uvPair*)&prim2->u0 = uv_values[vecIdx1];
        *(uvPair*)&prim2->u1 = uv_values[vecIdx2];
        *(uvPair*)&prim2->u2 = uv_values[vecIdx3];
        *(uvPair*)&prim2->u3 = uv_values[vecIdx4];
        if (arg5 == 1) {
            prim1 = arg6;
            if (rotTransResult > 0) {
                nextArg6 = arg6->next;
                *prim1 = *prim2;
                arg6->next = nextArg6;
                arg6 = nextArg6;
                if (arg6 == NULL) {
                    return NULL;
                }
            }
        } else {
            arg6 = UnkRecursivePrimFunc1(
                &vectors[vecIdx1], &vectors[vecIdx2], &vectors[vecIdx3],
                &vectors[vecIdx4], prim2, arg5 - 1, arg6, arg7);
        }
    }
    return arg6;
}
