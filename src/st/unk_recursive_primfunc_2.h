// SPDX-License-Identifier: AGPL-3.0-or-later
extern u16 g_UnkRecursPrim2Inds[];

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
    s32 Idx1;
    s32 Idx2;
    s32 Idx3;
    s32 Idx4;
    s16* Indices;
    Point16* points;
    rgb_set* colors;
    uvPair* uv_values;

    if (arg2 == NULL) {
        return NULL;
    }
    prim2 = arg3;
    arg3 += 0x34;
    colors = arg3;
    arg3 = arg3 + 0x24;

    colors[0] = *(rgb_set*)&arg0->r0;
    colors[2] = *(rgb_set*)&arg0->r1;
    colors[6] = *(rgb_set*)&arg0->r2;
    colors[8] = *(rgb_set*)&arg0->r3;

    points = arg3;
    arg3 += 0x24;
    uv_values = arg3;
    arg3 += 0x14;
    prim1 = arg2;

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
    Indices = &g_UnkRecursPrim2Inds;
    for (i = 0; i < 4; i++) {
        Idx1 = *Indices++;
        Idx2 = *Indices++;
        Idx3 = *Indices++;
        Idx4 = *Indices++;
        *(uvPair*)&prim2->u0 = uv_values[Idx1];
        *(uvPair*)&prim2->u1 = uv_values[Idx2];
        *(uvPair*)&prim2->u2 = uv_values[Idx3];
        *(uvPair*)&prim2->u3 = uv_values[Idx4];
        *(Point16*)&prim2->x0 = points[Idx1];
        *(Point16*)&prim2->x1 = points[Idx2];
        *(Point16*)&prim2->x2 = points[Idx3];
        *(Point16*)&prim2->x3 = points[Idx4];
        *(rgb_set*)&prim2->r0 = colors[Idx1];
        *(rgb_set*)&prim2->r1 = colors[Idx2];
        *(rgb_set*)&prim2->r2 = colors[Idx3];
        *(rgb_set*)&prim2->r3 = colors[Idx4];

        prim2->type = arg0->type;
        if (arg1 == 1) {
            nextArg2 = arg2->next;
            *arg2 = *prim2;
            arg2->next = nextArg2;
            arg2 = nextArg2;
            if (arg2 == NULL) {
                return NULL;
            }
        } else {
            arg2 = UnkRecursivePrimFunc2(prim2, arg1 - 1, arg2, arg3);
        }
    }
    return arg2;
}
