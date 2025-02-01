// SPDX-License-Identifier: AGPL-3.0-or-later
static s16 g_UnkRecursPrim2Inds[] = {
    0, 1, 3, 4, 1, 2, 4, 5, 3, 4, 6, 7, 4, 5, 7, 8,
#if !defined(STAGE_IS_NZ0) && !defined(STAGE_IS_NO1) &&                        \
    !defined(STAGE_IS_CHI) && STAGE != STAGE_ST0 && !defined(STAGE_IS_LIB)
    0, 0,
#endif
#if defined(VERSION_BETA)
    0, 0
#endif
};

// arg3 holds, in order:
// A Primitive, an array of 9 rgb_sets, an array of 10 Point16s, an array of 10
// uvPairs, and a pointer to another of arg3. Pointer type on arg3 is fake, but
// needed for Windows.

Primitive* UnkRecursivePrimFunc2(
    Primitive* arg0, s32 arg1, Primitive* arg2, u8* arg3) {
    s32 i;
    Primitive* prim1;
    Primitive* prim2;
    Primitive* nextArg2;
    Point16* points;
    rgb_set* colors;
    uvPair* uv_values;
    s16* indices;
    s32 idx1;
    s32 idx2;
    s32 idx3;
    s32 idx4;

    if (arg2 == NULL) {
        return NULL;
    }
    prim2 = (Primitive*)arg3;
#ifdef VERSION_PSP
    arg3 += 0x38;
#else
    arg3 += 0x34;
#endif
    colors = (rgb_set*)arg3;
    arg3 = arg3 + 0x24;

    points = (Point16*)arg3;
    arg3 += 0x24;
    uv_values = (uvPair*)arg3;
    arg3 += 0x14;

    colors[0] = *(rgb_set*)&arg0->r0;
    colors[2] = *(rgb_set*)&arg0->r1;
    colors[6] = *(rgb_set*)&arg0->r2;
    colors[8] = *(rgb_set*)&arg0->r3;

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

    uv_values[0] = *(uvPair*)&arg0->u0;
    uv_values[2] = *(uvPair*)&arg0->u1;
    uv_values[6] = *(uvPair*)&arg0->u2;
    uv_values[8] = *(uvPair*)&arg0->u3;
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

    points[0] = *(Point16*)&arg0->x0;
    points[2] = *(Point16*)&arg0->x1;
    points[6] = *(Point16*)&arg0->x2;
    points[8] = *(Point16*)&arg0->x3;
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

    *prim2 = *arg0;
    indices = g_UnkRecursPrim2Inds;
    for (i = 0; i < 4; i++) {
        idx1 = *indices++;
        idx2 = *indices++;
        idx3 = *indices++;
        idx4 = *indices++;
        *(uvPair*)&prim2->u0 = uv_values[idx1];
        *(uvPair*)&prim2->u1 = uv_values[idx2];
        *(uvPair*)&prim2->u2 = uv_values[idx3];
        *(uvPair*)&prim2->u3 = uv_values[idx4];
        *(Point16*)&prim2->x0 = points[idx1];
        *(Point16*)&prim2->x1 = points[idx2];
        *(Point16*)&prim2->x2 = points[idx3];
        *(Point16*)&prim2->x3 = points[idx4];
        *(rgb_set*)&prim2->r0 = colors[idx1];
        *(rgb_set*)&prim2->r1 = colors[idx2];
        *(rgb_set*)&prim2->r2 = colors[idx3];
        *(rgb_set*)&prim2->r3 = colors[idx4];

        prim2->type = arg0->type;
        if (arg1 == 1) {
            nextArg2 = arg2->next;
            *arg2 = *prim2;
            arg2->next = nextArg2;
            arg2 = arg2->next;
            if (arg2 == NULL) {
                return NULL;
            }
        } else {
            arg2 = UnkRecursivePrimFunc2(prim2, arg1 - 1, arg2, arg3);
        }
    }
    return arg2;
}
