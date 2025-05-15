// SPDX-License-Identifier: AGPL-3.0-or-later

// Stairway piece you can break before Death encounter
void EntityStairwayPiece(Entity* self, u8 arg1, u8 arg2, u8 arg3) {
    Primitive *prim, *prim2, *prim3;
    Entity* newEntity;
    Collider collider;
    s16 primIndex;
    s32 temp;
    s16 x, y;
    u8 v1;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxWidth = 8;
        self->hitboxHeight = 8;
        self->posX.i.hi = 1432 - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = 200 - g_Tilemap.scrollY.i.hi;
        self->hitPoints = 16;
        if (g_CastleFlags[DEATH_STAIRWAY_BROKEN]) {
            self->hitboxState = 0;
            g_Tilemap.fg[0x4D9] = 0x3EE;
            g_Tilemap.fg[0x539] = 0x3D2;
            self->step = 32;
            break;
        }
        self->hitboxState = 2;
        g_Tilemap.fg[0x4D9] = 0x408;
        g_Tilemap.fg[0x539] = 0x40D;
        break;

    case 1:
        if (self->hitFlags != 0) {
            g_api.PlaySfx(SFX_STOMP_SOFT_A);
        }

        if (self->flags & FLAG_DEAD) {
            self->step++;
        }
        break;

    case 2:
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
        g_Tilemap.fg[0x4D9] = 0x3EE;
        g_Tilemap.fg[0x539] = 0x3D2;
        g_CastleFlags[DEATH_STAIRWAY_BROKEN] = true;

        newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EQUIP_ITEM_DROP, self, newEntity);
            newEntity->params = ITEM_TURKEY;
        }

        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, newEntity);
            newEntity->params = 0x10;
            newEntity->zPriority = self->zPriority + 1;
            newEntity->posX.i.hi += 8;
            newEntity->posY.i.hi += 8;
        }

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        UnkPolyFunc2(prim);
        v1 = g_Tilemap.tileDef->gfxIndex[0x409];
        arg1 = v1;
        temp = g_Tilemap.tileDef->gfxPage[0x409];
        prim->clut = g_Tilemap.tileDef->clut[0x409];
        prim->tpage = temp + 8;
        arg1 *= 16;
        arg3 = 0xF;
        arg3 = arg1 | arg3;
        prim->u0 = prim->u2 = arg1;
        arg2 = v1 & 0xF0 | 0xF;
        prim->v0 = prim->v1 = v1 & 0xF0;
        prim->u1 = prim->u3 = arg3;
        prim->v2 = prim->v3 = arg2;
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        LOW(prim->next->u0) = 0xFFFF0000;
        LOW(prim->next->r1) = 0xFFFF0000;
        LOH(prim->next->r2) = 16;
        LOH(prim->next->b2) = 16;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_UNK02;
        self->step++;

    case 3:
        prim = self->ext.prim;
        prim2 = prim->next;
        prim2->tpage -= 0x20;
        prim2 = prim->next;
        LOW(prim2->r1) += 0x2000;
        UnkPrimHelper(prim);
        prim3 = prim->next;
        x = prim3->x1;
        y = prim3->y0;
        g_api.CheckCollision(x, (s16)(y + 8), &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posX.i.hi = x;
            self->posY.i.hi = y - 4;
            self->step++;
        }
        break;

    case 4:
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0x11;
            newEntity->zPriority = self->zPriority + 1;
        }

        for (i = 0; i < 6; i++) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_FALLING_ROCK, self, newEntity);
                newEntity->params = Random() & 3;
                if (newEntity->params == 3) {
                    newEntity->params = 0;
                }
            }
        }
        DestroyEntity(self);
    }
}

// falling rock with puff of smoke when it disappears. I think part of the
// merman room breakable rock
void EntityFallingRock(Entity* self) {
    s32 animFrame = self->params & 0xF;
    Collider collider;
    Entity* newEntity;
    s16 rndAngle;
    s32 rnd;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitStInteractable);
        self->animCurFrame = animFrame + 31;
        self->rotY = 0x60;
        self->rotX = 0x60;
        self->drawFlags |= FLAG_DRAW_ROTZ | FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
        rnd = (Random() & 0x1F) + 16;
        rndAngle = (Random() * 6) + 0x900;
        self->velocityX = rnd * rcos(rndAngle);
        self->velocityY = rnd * rsin(rndAngle);
        if (self->velocityX > 0) {
            self->facingLeft = 1;
        }
        break;

    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        self->rotZ -= 0x20;

        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 8, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, newEntity);
                newEntity->params = 0x10;
                if (animFrame == 0) {
                    newEntity->params = 0x13;
                }
            }
            DestroyEntity(self);
        }
        break;
    }
}

#if defined(STAGE_IS_NO3)
static SVECTOR vec_negneg = {-0x100, 0, -0x100};
static SVECTOR vec_posneg = {0x100, 0, -0x100};
static SVECTOR vec_negpos = {-0x100, 0, 0x100};
static SVECTOR vec_pospos = {0x100, 0, 0x100};
static CVECTOR D_8018136C = {0x80, 0xC0, 0xF0, 0x00};
static s16 D_80181370[] = {0, 1, 3, 4, 1, 2, 4, 5, 3, 4, 6, 7, 4, 5, 7, 8};

// See also: UnkRecursivePrimFunc1. Strong overlap, but also some different
// logic.
Primitive* func_801BB548(
    SVECTOR* p0, SVECTOR* p1, SVECTOR* p2, SVECTOR* p3, Primitive* srcPrim,
    s32 iterations, Primitive* dstPrim, u8* dataPtr) {
    s32 i;
    Primitive* tempPrim;
    s16* indices;
    SVECTOR* points;
    uvPair* uv_values;
    long p, flag;
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
            dstPrim = func_801BB548(
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
    s16 primIndex;
    SVECTOR sVec;
    VECTOR vec;
    MATRIX mtx;

    if (self->step == 0) {
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
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.deathSkySwirl.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
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
    vec.vy = -0xC0;
    vec.vx = 0;
    vec.vz = 0x200;
    TransMatrix(&mtx, &vec);
    SetRotMatrix(&mtx);
    SetTransMatrix(&mtx);
    prim = self->ext.deathSkySwirl.prim;
    prim->drawMode = DRAW_COLORS;

    prim2 = prim->next;
    prim2 = func_801BB548(&vec_negneg, &vec_posneg, &vec_negpos, &vec_pospos,
                          prim, 3, prim2, 0x1F800000);
    prim->drawMode = DRAW_HIDE;
    while (prim2 != NULL) {
        prim2->drawMode = DRAW_HIDE;
        prim2 = prim2->next;
    }
}

#endif

static u8 thunder_anim[] = {4, 23, 3, 24, 2, 25, 2, 26, 255, 0, 0, 0};

void EntityLightningThunder(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_EInitStInteractable);
        self->zPriority = 0x2A;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        self->facingLeft = Random() & 1;
        g_api.PlaySfxVolPan(SFX_THUNDER_B, 0x40, (self->posX.i.hi >> 0x4) - 8);
    }
    if (AnimateEntity(thunder_anim, self) == 0) {
        DestroyEntity(self);
    }
}

extern s16 cloudPos[][2] = {{0x88, 0x6C}, {0xC8, 0x30}, {0x30, 0x44}};

// When lightning strikes, we get a bright bolt, but it is against a cloud
// as a background. It's subtle and hard to see, but it's there.
void EntityLightningCloud(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_EInitStInteractable);
        self->zPriority = 0x29;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        // There are 3 shapes of cloud, this picks which one.
        self->animCurFrame = self->params + 0x22;
        self->posX.i.hi = cloudPos[self->params][0];
        self->posY.i.hi = cloudPos[self->params][1];
        self->ext.backgroundLightning.timer = 5;
    }

    if (--self->ext.backgroundLightning.timer == 0) {
        DestroyEntity(self);
    }
}
