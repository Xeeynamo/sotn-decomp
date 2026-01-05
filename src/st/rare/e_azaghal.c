// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rare.h"

extern EInit g_EInitAzaghal;

typedef struct {
    SVECTOR* targetPosition;
    s16* lerpVals;
} AzaghalPosition;

static s16 sensors_ground[] = {0, 72, 0, 4, 4, -4, -8, 0};

// { u, v, x1, y1, x2, y2 }
static s16 body_config[][6] = {
    // idle
    {64, 0, 63, 127, -8, -30},
    // combo attack
    {128, 0, 87, 127, -8, -24},
    // hit by player or dead
    {0, 128, 95, 111, -64, -16},
    // sword overhead
    {128, 0, 87, 127, -24, -29},
};
static SVECTOR D_us_801818F0 = {.vx = -16, .vy = 8, .vz = 0};
static SVECTOR D_us_801818F8 = {.vx = 16, .vy = 8, .vz = 0};
static SVECTOR D_us_80181900 = {.vx = -16, .vy = 120, .vz = 0};
static SVECTOR D_us_80181908 = {.vx = 16, .vy = 120, .vz = 0};
static SVECTOR D_us_80181910 = {.vx = 0, .vy = 8, .vz = -8};
static SVECTOR D_us_80181918 = {.vx = 0, .vy = 8, .vz = 8};
static SVECTOR D_us_80181920 = {.vx = 0, .vy = 120, .vz = -8};
static SVECTOR D_us_80181928 = {.vx = 0, .vy = 120, .vz = 8};
static SVECTOR D_us_80181930 = {.vx = 0, .vy = 120, .vz = 0};

static s16 lerp_a[][2] = {
    {0, 0},     {12, 256},  {12, 512},  {12, 1024}, {12, 2048},
    {12, 3072}, {12, 3584}, {12, 3840}, {12, 4096},
};

static s16 lerp_b[][2] = {
    {0, 0}, {32, 1024}, {8, 2048}, {4, 3584}, {16, 4096},
};

static s16 lerp_c[][2] = {
    {0, 0}, {32, 1024}, {8, 2048}, {8, 3840}, {48, 4096},
};

static s16 lerp_d[][2] = {
    {0, 0}, {8, 256}, {6, 2048}, {4, 3584}, {4, 3968}, {32, 4096},
};

static s16 lerp_e[][2] = {
    {0, 0}, {14, 256}, {10, 2048}, {8, 3584}, {8, 3968}, {32, 4096},
};

static s16 lerp_f[][2] = {
    {0, 0}, {6, 256}, {6, 1024}, {6, 2048}, {4, 3584}, {4, 3968}, {8, 4096},
};

static s16 lerp_g[][2] = {
    {0, 0}, {3, 256}, {3, 1024}, {3, 2048}, {2, 3584}, {2, 3968}, {4, 4096},
};

static SVECTOR D_us_801819EC = {.vx = 0, .vy = 0, .vz = 224};
static SVECTOR D_us_801819F4 = {.vx = 0, .vy = 0, .vz = 48};
static AzaghalPosition anim_seek_player[] = {
    {.targetPosition = &D_us_801819EC, .lerpVals = *lerp_a},
    {.targetPosition = &D_us_801819F4, .lerpVals = *lerp_a},
};

static SVECTOR D_us_80181A0C = {.vx = -1056, .vy = 816, .vz = 3296};
static SVECTOR D_us_80181A14 = {.vx = 0, .vy = 1024, .vz = 2048};
static SVECTOR D_us_80181A1C = {.vx = 0, .vy = 0, .vz = 1344};
static AzaghalPosition anim_sword_overhead_a = {
    .targetPosition = &D_us_80181A0C,
    .lerpVals = *lerp_a,
};
static AzaghalPosition anim_sword_overhead_b = {
    .targetPosition = &D_us_80181A14,
    .lerpVals = *lerp_g,
};
static AzaghalPosition anim_sword_overhead_c = {
    .targetPosition = &D_us_80181A1C,
    .lerpVals = *lerp_b,
};

static SVECTOR D_us_80181A3C = {.vx = -480, .vy = 32, .vz = 2000};
static SVECTOR D_us_80181A44 = {.vx = -480, .vy = 32, .vz = -224};
static AzaghalPosition anim_slash_down_a = {
    .targetPosition = &D_us_80181A3C,
    .lerpVals = *lerp_c,
};
static AzaghalPosition anim_slash_down_b = {
    .targetPosition = &D_us_80181A44,
    .lerpVals = *lerp_e,
};

static SVECTOR D_us_80181A5C = {.vx = -896, .vy = -32, .vz = 1792};
static SVECTOR D_us_80181A64 = {.vx = -888, .vy = -32, .vz = -400};
static AzaghalPosition anim_long_slash_hor_b = {
    .targetPosition = &D_us_80181A5C,
    .lerpVals = *lerp_d,
};
static AzaghalPosition anim_long_slash_hor_a = {
    .targetPosition = &D_us_80181A64,
    .lerpVals = *lerp_c,
};
static AzaghalPosition anim_short_slash_hor_a = {
    .targetPosition = &D_us_80181A5C,
    .lerpVals = *lerp_a,
};
static AzaghalPosition anim_short_slash_hor_b = {
    .targetPosition = &D_us_80181A64,
    .lerpVals = *lerp_d,
};

static SVECTOR D_us_80181A8C = {.vx = -464, .vy = -416, .vz = -112};
static SVECTOR D_us_80181A94 = {.vx = -464, .vy = -160, .vz = 1744};
static AzaghalPosition anim_slash_up_a = {
    .targetPosition = &D_us_80181A8C,
    .lerpVals = *lerp_c,
};
static AzaghalPosition anim_slash_up_b = {
    .targetPosition = &D_us_80181A94,
    .lerpVals = *lerp_d,
};

static SVECTOR D_us_80181AAC = {.vx = 0, .vy = 0, .vz = 2352};
static SVECTOR D_us_80181AB4 = {.vx = 0, .vy = 0, .vz = 512};
// This is unused, but the positions and lerps are integrated into
// the combo attack. Possible this portion was originally intended
// to be its own small attack.
static AzaghalPosition D_us_80181ABC[] = {
    {
        .targetPosition = &D_us_80181AAC,
        .lerpVals = *lerp_a,
    },
    {
        .targetPosition = &D_us_80181AB4,
        .lerpVals = *lerp_a,
    },
};

static SVECTOR D_us_80181ACC = {.vx = 0, .vy = 0, .vz = 512};
static AzaghalPosition anim_fall_backward = {
    .targetPosition = &D_us_80181ACC,
    .lerpVals = *lerp_d,
};

static SVECTOR D_us_80181ADC = {.vx = 0, .vy = 0, .vz = -1088};
static SVECTOR D_us_80181AE4 = {.vx = 0, .vy = 0, .vz = 1024};
static AzaghalPosition anim_combo_init = {
    .targetPosition = &D_us_80181ADC,
    .lerpVals = *lerp_d,
};

static SVECTOR D_us_80181AF4 = {.vx = -1088, .vy = 0, .vz = -1088};
static SVECTOR D_us_80181AFC = {.vx = -1088, .vy = 0, .vz = -1088};
static SVECTOR D_us_80181B04 = {.vx = -1088, .vy = 0, .vz = 2560};
static AzaghalPosition anim_combo[] = {
    {.targetPosition = &D_us_80181AF4, .lerpVals = *lerp_f},
    {.targetPosition = &D_us_80181AFC, .lerpVals = *lerp_f},
    {.targetPosition = &D_us_80181B04, .lerpVals = *lerp_f},
    {.targetPosition = &D_us_80181AAC, .lerpVals = *lerp_g},
    {.targetPosition = &D_us_80181AB4, .lerpVals = *lerp_g},
    {.targetPosition = &D_us_80181A8C, .lerpVals = *lerp_g},
    {.targetPosition = &D_us_80181A94, .lerpVals = *lerp_g},
    {.targetPosition = &D_us_80181AAC, .lerpVals = *lerp_g},
    {.targetPosition = &D_us_80181AE4, .lerpVals = *lerp_g},
};
static s16 indices[] = {0, 2, 3, 5, 3, 5, 6, 8};

// nb. this is very similar to the stained glass recursive function in DAI
static Primitive* func_us_801B2C40(
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

        if (iterations == 1) {
            dstPrimNext = dstPrim->next;
            *dstPrim = *tempPrim;
            dstPrim->next = dstPrimNext;
            dstPrim = dstPrim->next;
            if (dstPrim == NULL) {
                return NULL;
            }
        } else {
            dstPrim = func_us_801B2C40(
                &points[index0], &points[index1], &points[index2],
                &points[index3], tempPrim, iterations - 1, dstPrim, dataPtr);
        }
    }
    return dstPrim;
}

enum AzaghalBodyStep {
    INIT_BODY = 0,
    SHOW_BODY = 1,
    HIDE_BODY = 2,
};

static s32 UpdateBodyDisplay(s32 index, s32 action) {
    Primitive* prim;
    s16* bodyConfig;
    u8 color;

    prim = g_CurrentEntity->ext.azaghal.primTwo;
    bodyConfig = body_config[index];
    switch (action) {
    case INIT_BODY:
        prim->u0 = prim->u2 = bodyConfig[0];
        prim->u1 = prim->u3 = bodyConfig[0] + bodyConfig[2];
        prim->v0 = prim->v1 = bodyConfig[1];
        prim->v2 = prim->v3 = bodyConfig[1] + bodyConfig[3];

        if (g_CurrentEntity->facingLeft) {
            prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi - bodyConfig[4];
            prim->x1 = prim->x3 = prim->x0 - bodyConfig[2];
        } else {
            prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi + bodyConfig[4];
            prim->x1 = prim->x3 = prim->x0 + bodyConfig[2];
        }
        prim->y0 = prim->y1 = g_CurrentEntity->posY.i.hi + bodyConfig[5];
        prim->y2 = prim->y3 = prim->y0 + bodyConfig[3];

        PGREY(prim, 0) = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = g_CurrentEntity->zPriority + 1;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        g_CurrentEntity->ext.azaghal.bodyGlowIntensity = 0;
        break;
    case SHOW_BODY:
        // Body color pulses and flickers
        color = (g_CurrentEntity->ext.azaghal.bodyGlowIntensity *
                 abs(rsin(g_CurrentEntity->ext.azaghal.bodyGlowPhase))) >>
                0xC;
        PGREY(prim, 0) = color;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);

        if (g_CurrentEntity->facingLeft) {
            prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi - bodyConfig[4];
            prim->x1 = prim->x3 = prim->x0 - bodyConfig[2];
        } else {
            prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi + bodyConfig[4];
            prim->x1 = prim->x3 = prim->x0 + bodyConfig[2];
        }

        prim->y0 = prim->y1 = g_CurrentEntity->posY.i.hi + bodyConfig[5];
        prim->y2 = prim->y3 = prim->y0 + bodyConfig[3];

        if (g_CurrentEntity->ext.azaghal.bodyGlowIntensity < 0x80) {
            g_CurrentEntity->ext.azaghal.bodyGlowIntensity += 8;
        }
        g_CurrentEntity->ext.azaghal.bodyGlowPhase += 0x20;
        if (g_Timer & 2) {
            prim->clut = PAL_AZAGHAL_BODY_A;
        } else {
            prim->clut = PAL_AZAGHAL_BODY_B;
        }
        break;
    case HIDE_BODY:
        if (!PrimDecreaseBrightness(prim, 7)) {
            prim->drawMode = DRAW_HIDE;
            return true;
        }
        break;
    }

    return false;
}

static void func_us_801B33F4(void) {
#ifdef VERSION_PC
    u8 sp[SP_LEN];
#endif
    long flag;
    long p;
    SVECTOR sVec;
    VECTOR vector;
    MATRIX matrix;

    Primitive* prim;
    Primitive* primTwo;
    Entity* entity;
    s32 i;
    s32 swordHitboxOffsetX;
    s32 swordHitboxOffsetY;
    s32 posX;
    s32 posY;

    posX = g_CurrentEntity->posX.i.hi;
    posY = g_CurrentEntity->posY.i.hi;
    SetGeomScreen(0x100);
    SetGeomOffset(posX, posY);
    sVec.vx = g_CurrentEntity->ext.azaghal.pos.vx;
    sVec.vy = g_CurrentEntity->ext.azaghal.pos.vy;
    sVec.vz = g_CurrentEntity->ext.azaghal.pos.vz;
    RotMatrix(&sVec, &matrix);

    if (g_CurrentEntity->facingLeft) {
        RotMatrixY(0x800, &matrix);
    }

    vector.vx = 0;
    vector.vy = 0;
    vector.vz = 0x100;
    TransMatrix(&matrix, &vector);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);

    prim = g_CurrentEntity->ext.azaghal.prim;
    prim->drawMode = DRAW_UNK02;
    RotTransPers4(&D_us_801818F0, &D_us_801818F8, &D_us_80181900,
                  &D_us_80181908, (long*)&prim->x0, (long*)&prim->x1,
                  (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
    primTwo = g_CurrentEntity->ext.azaghal.primThree;
    primTwo = func_us_801B2C40(&D_us_801818F0, &D_us_801818F8, &D_us_80181900,
                               &D_us_80181908, prim, 3, primTwo, (u8*)SPAD(0));
    prim->drawMode = DRAW_HIDE;
    prim = prim->next;

    prim->drawMode = DRAW_UNK02;
    RotTransPers4(&D_us_80181910, &D_us_80181918, &D_us_80181920,
                  &D_us_80181928, (long*)&prim->x0, (long*)&prim->x1,
                  (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
    primTwo = func_us_801B2C40(&D_us_80181910, &D_us_80181918, &D_us_80181920,
                               &D_us_80181928, prim, 3, primTwo, (u8*)SPAD(0));
    prim->drawMode = DRAW_HIDE;

    if (g_CurrentEntity->flags & FLAG_DEAD) {
        while (primTwo != NULL) {
            primTwo->drawMode = DRAW_HIDE;
            primTwo = primTwo->next;
        }
    } else {
        RotTransPers(&D_us_80181930, (long*)SPAD(0), &p, &flag);
        swordHitboxOffsetX = *(s16*)SP(0);
        swordHitboxOffsetY = *(s16*)SP(2);
        swordHitboxOffsetX -= posX;
        swordHitboxOffsetY -= posY;

        g_CurrentEntity->hitboxOffX = swordHitboxOffsetX / 8;
        if (g_CurrentEntity->facingLeft) {
            g_CurrentEntity->hitboxOffX = (s16)-g_CurrentEntity->hitboxOffX;
        }

        g_CurrentEntity->hitboxOffY = swordHitboxOffsetY / 8;

        for (i = 2; i < 8; i++) {
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_AZAGHAL_SWORD_HITBOX, entity);
                entity->posX.i.hi = posX + ((swordHitboxOffsetX * i) / 8);
                entity->posY.i.hi = posY + ((swordHitboxOffsetY * i) / 8);
            }
        }

        prim = primTwo;
        for (i = 0; i < 6; i++) {
            prim->type = PRIM_G4;
            primTwo = prim->next;

            prim->r0 = i * 0x10;
            prim->g0 = i * 0x10;
            prim->b0 = i * 0x10;
            LOW(prim->r1) = LOW(prim->r0);
            prim->r2 = (i + 1) * 0x10;
            prim->g2 = (i + 1) * 0x10;
            prim->b2 = (i + 1) * 0x10;
            LOW(prim->r3) = LOW(prim->r2);
            LOW(prim->x0) = LOW(primTwo->x0);
            LOW(prim->x1) = LOW(primTwo->x1);
            LOW(prim->x2) = LOW(primTwo->x2);
            LOW(prim->x3) = LOW(primTwo->x3);
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim = primTwo;
        }

        prim->type = PRIM_G4;
        prim->r0 = i * 0x10;
        prim->g0 = i * 0x10;
        prim->b0 = i * 0x10;
        LOW(prim->r1) = LOW(prim->r0);
        prim->r2 = (i + 1) * 0x10;
        prim->g2 = (i + 1) * 0x10;
        prim->b2 = (i + 1) * 0x10;
        LOW(prim->r3) = LOW(prim->r2);
        LOW(prim->x0) = LOW(prim->x2);
        LOW(prim->x1) = LOW(prim->x3);

        prim->x2 = posX + (swordHitboxOffsetX / 4);
        prim->y2 = posY + (swordHitboxOffsetY / 4);
        prim->x3 = (posX + swordHitboxOffsetX) - (swordHitboxOffsetX / 8);
        prim->y3 = (posY + swordHitboxOffsetY) - (swordHitboxOffsetY / 8);
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;

        swordHitboxOffsetX = 0;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            swordHitboxOffsetX++;
            prim = prim->next;
        }
        FntPrint("no_use %x\n", swordHitboxOffsetX);
    }
}

static void InitPositionLerp(SVECTOR* vector) {
    SVECTOR* base = &g_CurrentEntity->ext.azaghal.base;
    SVECTOR* pos = &g_CurrentEntity->ext.azaghal.pos;
    SVECTOR* offset = &g_CurrentEntity->ext.azaghal.offset;

    offset->vx = vector->vx - pos->vx;
    offset->vy = vector->vy - pos->vy;
    offset->vz = vector->vz - pos->vz;

    base->vx = pos->vx;
    base->vy = pos->vy;
    base->vz = pos->vz;
}

static void ApplyPositionLerp(void) {
    SVECTOR* base = &g_CurrentEntity->ext.azaghal.base;
    SVECTOR* pos = &g_CurrentEntity->ext.azaghal.pos;
    SVECTOR* offset = &g_CurrentEntity->ext.azaghal.offset;
    s32 t = g_CurrentEntity->ext.azaghal.lerpT;

    pos->vx = base->vx + ((offset->vx * t) / 4096);
    pos->vy = base->vy + ((offset->vy * t) / 4096);
    pos->vz = base->vz + ((offset->vz * t) / 4096);
}

static s32 AnimateAzaghal(AzaghalPosition* posData) {
    s16* lerpVal;
    s32 poseTimer;

    if (!g_CurrentEntity->pose && !g_CurrentEntity->poseTimer) {
        InitPositionLerp(posData->targetPosition);
    }

    lerpVal = posData->lerpVals;
    lerpVal += g_CurrentEntity->pose * 2;
    // When we have reached the end of the lerp values, the animation is over
    if (lerpVal[1] == 4096) {
        return false;
    }

    g_CurrentEntity->poseTimer++;
    poseTimer = g_CurrentEntity->poseTimer;
    g_CurrentEntity->ext.azaghal.lerpT =
        lerpVal[1] + (((lerpVal[3] - lerpVal[1]) * poseTimer) / lerpVal[2]);
    ApplyPositionLerp();

    if (poseTimer == lerpVal[2]) {
        g_CurrentEntity->poseTimer = 0;
        g_CurrentEntity->pose++;
    }

    return true;
}

void EntityAzaghal(Entity* self) {
    enum AzaghalStep {
        INIT = 0,
        FALL_TO_GROUND = 1,
        IDLE_WAIT = 3,
        SWORD_OVERHEAD = 4,
        SLASH_DOWN = 5,
        LONG_SLASH_HORIZONTAL = 6,
        SLASH_UP = 8,
        SEEK_PLAYER = 10,
        HIT_BY_PLAYER = 11,
        SHORT_SLASH_HORIZONTAL = 12,
        COMBO_ATTACK = 13,
        DEATH = 15,
        DEBUG = 255
    };

    Primitive* prim;
    Entity* entity;
    Primitive* primTwo;
    Primitive* primThree;
    s32 i;
    s32 primsHidden;
    s32 primIndex;
    s32 posX;
    s32 posY;

    FntPrint("step %x\n", self->step);
    FntPrint("step_s %x\n", self->step_s);

    if (self->hitFlags & 3 && self->step != HIT_BY_PLAYER) {
        SetStep(HIT_BY_PLAYER);
    }

    if (self->flags & FLAG_DEAD && self->step < DEATH) {
        SetStep(DEATH);
    }

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitAzaghal);
        self->hitboxState = 0;
        self->hitboxWidth = self->hitboxHeight = 0xC;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x20);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.azaghal.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0x14;
            prim->clut = PAL_AZAGHAL_BODY_A;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        prim = self->ext.azaghal.prim;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x28;
        prim->v0 = prim->v1 = 0x10;
        prim->v2 = prim->v3 = 0x70;
        prim = prim->next;

        prim->u0 = prim->u2 = 0x28;
        prim->u1 = prim->u3 = 0x37;
        prim->v0 = prim->v1 = 0x10;
        prim->v2 = prim->v3 = 0x70;
        prim = prim->next;

        self->ext.azaghal.primTwo = prim;
        PGREY(prim, 0) = 0x80;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim = prim->next;
        prim = prim->next;
        prim = prim->next;
        self->ext.azaghal.primThree = prim;
        // fallthrough
    case FALL_TO_GROUND:
        if (UnkCollisionFunc3(sensors_ground) & 1) {
            SetStep(IDLE_WAIT);
        }
        break;
    case IDLE_WAIT:
        switch (self->step_s) {
        case 0:
            prim = self->ext.azaghal.prim;
            prim->u0 = prim->u2 = 4;
            prim->u1 = prim->u3 = 0x24;
            prim->v0 = prim->v1 = 0x10;
            prim->v2 = prim->v3 = 0x68;
            prim->x0 = prim->x2 = self->posX.i.hi - 0x10;
            prim->x1 = prim->x3 = self->posX.i.hi + 0x10;
            prim->y0 = prim->y1 = self->posY.i.hi - 0x10;
            prim->y2 = prim->y3 = self->posY.i.hi + 0x48;
            prim->drawMode = DRAW_UNK02;
            self->posY.i.hi -= 0x18;
            UpdateBodyDisplay(0, INIT_BODY);
            self->step_s++;
            // fallthrough
        case 1:
            UpdateBodyDisplay(0, SHOW_BODY);
            if (GetDistanceToPlayerX() < 0x60) {
                self->step_s++;
            }
            break;
        case 2:
            if (UpdateBodyDisplay(0, HIDE_BODY)) {
                self->step_s++;
            }
            break;
        case 3:
            self->posY.i.hi--;
            prim = self->ext.azaghal.prim;
            prim->y0 = prim->y1 -= 1;
            prim->v2 = prim->v3 += 1;
            if (prim->v2 > 0x7F) {
                prim->v2 = prim->v3 = 0x7F;
                self->step_s++;
            }
            break;
        case 4:
            prim = self->ext.azaghal.prim;
            prim->u0 = prim->u2 = 4;
            prim->u1 = prim->u3 = 0x24;
            prim->v0 = prim->v1 = 0x10;
            prim->v2 = prim->v3 = 0x80;
            prim = prim->next;

            prim->u0 = prim->u2 = 0x28;
            prim->u1 = prim->u3 = 0x37;
            prim->v0 = prim->v1 = 0x10;
            prim->v2 = prim->v3 = 0x80;
            // nb. This goes unused
            prim = prim->next;

            self->step_s++;
            // fallthrough
        case 5:
            prim = self->ext.azaghal.prim;
            prim = prim->next;
            prim = prim->next;
            while (prim != NULL) {
                prim->x0 = self->posX.i.hi;
                prim->y0 = self->posY.i.hi;
                LOW(prim->x1) = LOW(prim->x0);
                LOW(prim->x2) = LOW(prim->x0);
                LOW(prim->x3) = LOW(prim->x0);
                prim = prim->next;
            }
            self->hitboxState = 2;
            SetStep(SEEK_PLAYER);
        }
        break;
    case SWORD_OVERHEAD:
        switch (self->step_s) {
        case 0:
            if (!AnimateAzaghal(&anim_sword_overhead_a)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                self->step_s = 1;
            }
            break;
        case 1:
            if (!AnimateAzaghal(&anim_sword_overhead_b)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                self->step_s++;
            }
            break;
        case 2:
            if (!AnimateAzaghal(&anim_sword_overhead_c)) {
                UpdateBodyDisplay(3, INIT_BODY);
                self->ext.azaghal.timer = 0x10;
                self->step_s++;
            }
            break;
        case 3:
            UpdateBodyDisplay(3, SHOW_BODY);
            if (!--self->ext.azaghal.timer) {
                self->step_s++;
            }
            break;
        case 4:
            if (UpdateBodyDisplay(3, HIDE_BODY)) {
                PlaySfxPositional(SFX_VANDAL_SWORD_ATTACK);
                if (self->ext.azaghal.attackCounter & 1) {
                    SetStep(SLASH_DOWN);
                } else {
                    SetStep(SHORT_SLASH_HORIZONTAL);
                }

                self->ext.azaghal.attackCounter++;
                if (self->ext.azaghal.attackCounter > 3) {
                    self->ext.azaghal.attackCounter = 0;
                    SetStep(COMBO_ATTACK);
                }
            }
            break;
        }

        func_us_801B33F4();
        break;
    case SEEK_PLAYER:
        if (!self->step_s) {
            self->ext.azaghal.timer = 0x80;
            self->velocityX = 0;
            self->velocityY = 0;
            self->ext.azaghal.animIndex = 0;
            self->step_s++;
        }

        if (!AnimateAzaghal(&anim_seek_player[self->ext.azaghal.animIndex])) {
            self->ext.azaghal.animIndex ^= 1;
            self->pose = 0;
            self->poseTimer = 0;
        }

        MoveEntity();
        self->rotate += ROT(5.625);
        self->velocityY = rsin(self->rotate) * 0xE;
        if (self->posY.val < FIX(128.5)) {
            self->velocityY += FIX(0.25);
        } else {
            self->velocityY -= FIX(0.25);
        }

        if (GetDistanceToPlayerX() < 0x30) {
            self->velocityX = FIX(0.5);
        }

        if (GetDistanceToPlayerX() > 0x38) {
            self->velocityX = FIX(-0.5);
        }

        if (self->facingLeft) {
            self->velocityX = -self->velocityX;
        }

        if (self->facingLeft != ((GetSideToPlayer() & 1) ^ 1)) {
            SetStep(SWORD_OVERHEAD);
        }

        if (!--self->ext.azaghal.timer) {
            SetStep(SWORD_OVERHEAD);
        }
        func_us_801B33F4();
        break;
    case SLASH_DOWN:
        switch (self->step_s) {
        case 0:
            if (!AnimateAzaghal(&anim_slash_down_a)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            break;
        case 1:
            if (!AnimateAzaghal(&anim_slash_down_b)) {
                SetStep(LONG_SLASH_HORIZONTAL);
            }
            break;
        }
        func_us_801B33F4();
        break;
    case LONG_SLASH_HORIZONTAL:
        switch (self->step_s) {
        case 0:
            if (!AnimateAzaghal(&anim_long_slash_hor_a)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->velocityX = FIX(-4.0);
                if (self->facingLeft) {
                    self->velocityX = -self->velocityX;
                }
                self->velocityY = 0;
                self->step_s++;
            }
            break;
        case 1:
            MoveEntity();
            self->velocityX -= self->velocityX / 16;
            if (!AnimateAzaghal(&anim_long_slash_hor_b)) {
                SetStep(SEEK_PLAYER);
            }
            break;
        }
        func_us_801B33F4();
        break;
    case SHORT_SLASH_HORIZONTAL:
        switch (self->step_s) {
        case 0:
            if (!AnimateAzaghal(&anim_short_slash_hor_a)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->velocityX = FIX(-4.0);
                if (self->facingLeft) {
                    self->velocityX = -self->velocityX;
                }
                self->velocityY = 0;
                self->step_s++;
            }
            break;
        case 1:
            MoveEntity();
            self->velocityX -= self->velocityX / 16;
            if (!AnimateAzaghal(&anim_short_slash_hor_b)) {
                SetStep(SLASH_UP);
            }
            break;
        }
        func_us_801B33F4();
        break;
    case SLASH_UP:
        switch (self->step_s) {
        case 0:
            if (!AnimateAzaghal(&anim_slash_up_a)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            break;
        case 1:
            if (!AnimateAzaghal(&anim_slash_up_b)) {
                SetStep(SEEK_PLAYER);
            }
            break;
        }
        func_us_801B33F4();
        break;
    case COMBO_ATTACK:
        switch (self->step_s) {
        case 0:
            UpdateBodyDisplay(1, INIT_BODY);
            self->step_s++;
            // fallthrough
        case 1:
            UpdateBodyDisplay(1, SHOW_BODY);
            if (!AnimateAzaghal(&anim_combo_init)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->ext.azaghal.timer = 0;
                self->step_s++;
            }
            break;
        case 2:
            prim = self->ext.azaghal.primTwo;
            primTwo = prim->next;
            primThree = primTwo->next;

            *primTwo = *prim;
            PGREY(primTwo, 0) = 0x80;
            LOW(primTwo->r1) = LOW(primTwo->r0);
            LOW(primTwo->r2) = LOW(primTwo->r0);
            LOW(primTwo->r3) = LOW(primTwo->r0);
            primTwo->next = primThree;
            primTwo->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                DRAW_UNK02 | DRAW_TRANSP;
            primTwo = primTwo->next;
            primThree = primTwo->next;

            *primTwo = *prim;
            PGREY(primTwo, 0) = 0x80;
            LOW(primTwo->r1) = LOW(primTwo->r0);
            LOW(primTwo->r2) = LOW(primTwo->r0);
            LOW(primTwo->r3) = LOW(primTwo->r0);
            primTwo->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                DRAW_UNK02 | DRAW_TRANSP;
            primTwo->next = primThree;
            // nb. This goes unused
            primTwo = primTwo->next;

            self->step_s++;
            // fallthrough
        case 3:
            primsHidden = 0;
            prim = self->ext.azaghal.primTwo;
            prim = prim->next;
            if (self->facingLeft) {
                prim->x0 = prim->x2 += 1;
                prim->x1 = prim->x3 -= 1;
            } else {
                prim->x0 = prim->x2 -= 1;
                prim->x1 = prim->x3 += 1;
            }

            prim->y0 = prim->y1 -= 1;
            prim->y2 = prim->y3 += 1;

            if (g_Timer & 1) {
                prim->clut = PAL_AZAGHAL_COMBO_A;
            } else {
                prim->clut = PAL_AZAGHAL_COMBO_B;
            }

            if (!PrimDecreaseBrightness(prim, 7)) {
                prim->drawMode = DRAW_HIDE;
                primsHidden++;
            }

            prim = prim->next;
            if (self->facingLeft) {
                prim->x0 = prim->x2 += 3;
                prim->x1 = prim->x3 -= 3;
            } else {
                prim->x0 = prim->x2 -= 3;
                prim->x1 = prim->x3 += 3;
            }

            prim->y0 = prim->y1 -= 3;
            prim->y2 = prim->y3 += 3;
            if (g_Timer & 1) {
                prim->clut = PAL_AZAGHAL_COMBO_A;
            } else {
                prim->clut = PAL_AZAGHAL_COMBO_B;
            }

            if (!PrimDecreaseBrightness(prim, 7)) {
                prim->drawMode = DRAW_HIDE;
                primsHidden++;
            }

            UpdateBodyDisplay(1, SHOW_BODY);
            if (primsHidden == 2) {
                self->step_s++;
            }
            break;
        case 4:
            if (UpdateBodyDisplay(1, HIDE_BODY)) {
                self->ext.azaghal.animIndex = 0;
                self->step_s++;
            }
            break;
        case 5:
            i = self->ext.azaghal.animIndex;
            if (!AnimateAzaghal(&anim_combo[i])) {
                self->ext.azaghal.animIndex++;
                self->pose = 0;
                self->poseTimer = 0;
                if (self->ext.azaghal.animIndex == 9) {
                    self->velocityX = FIX(-6.0);
                    if (self->facingLeft) {
                        self->velocityX = -self->velocityX;
                    }
                    self->velocityY = 0;
                    self->step_s++;
                }
            }
            break;
        case 6:
            MoveEntity();
            self->velocityX -= self->velocityX / 16;
            if (self->ext.azaghal.timer++ > 0x40) {
                SetStep(SEEK_PLAYER);
            }
            break;
        }
        func_us_801B33F4();
        break;
    case HIT_BY_PLAYER:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(-4.0);
            } else {
                self->velocityX = FIX(4.0);
            }
            self->velocityY = FIX(-4.0);

            prim = self->ext.azaghal.primTwo;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;

            UpdateBodyDisplay(2, INIT_BODY);
            PlaySfxPositional(SFX_VANDAL_SWORD_PAIN);
            self->step_s++;
            // fallthrough
        case 1:
            AnimateAzaghal(&anim_fall_backward);
            UpdateBodyDisplay(2, SHOW_BODY);
            MoveEntity();
            self->velocityX -= self->velocityX / 32;
            self->velocityY += FIX(0.125);
            if (self->velocityY > FIX(4.0)) {
                self->step_s++;
            }
            break;
        case 2:
            if (UpdateBodyDisplay(2, HIDE_BODY)) {
                SetStep(SEEK_PLAYER);
            }
            break;
        }
        func_us_801B33F4();
        break;
    case DEATH:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(-4.0);
            } else {
                self->velocityX = FIX(4.0);
            }
            self->velocityY = FIX(-4.0);

            prim = self->ext.azaghal.primTwo;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;

            UpdateBodyDisplay(2, INIT_BODY);
            PlaySfxPositional(SFX_VANDAL_SWORD_DEATH);
            self->step_s++;
            // fallthrough
        case 1:
            AnimateAzaghal(&anim_fall_backward);
            UpdateBodyDisplay(2, SHOW_BODY);
            MoveEntity();
            self->velocityX -= self->velocityX / 32;
            self->velocityY += FIX(0.125);
            if (self->velocityY > FIX(4.0)) {
                self->ext.azaghal.animIndex = 0;
                self->ext.azaghal.timer = 4;
                self->step_s++;
            }
            func_us_801B33F4();
            break;
        case 2:
            prim = self->ext.azaghal.primTwo;
            PrimDecreaseBrightness(prim, 1);
            if (!--self->ext.azaghal.timer) {
                PlaySfxPositional(SFX_EXPLODE_B);
                self->ext.azaghal.timer = 4;
                prim = self->ext.azaghal.primThree;

                for (i = 0; i < self->ext.azaghal.animIndex; i++) {
                    prim = prim->next;
                }

                prim->drawMode = DRAW_HIDE;
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
                    posX = prim->x0 + prim->x1 + prim->x2 + prim->x3;
                    posX /= 4;
                    posY = prim->y0 + prim->y1 + prim->y2 + prim->y3;
                    posY /= 4;
                    entity->posX.i.hi = posX;
                    entity->posY.i.hi = posY;
                    entity->params = EXPLOSION_FIREBALL;
                }
                self->ext.azaghal.animIndex++;
                if (self->ext.azaghal.animIndex > 7) {
                    self->step_s++;
                }
            }
            break;
        case 3:
            DestroyEntity(self);
            return;
        }
        break;
    case DEBUG:
        if (g_pads[1].pressed & PAD_TRIANGLE) {
            self->ext.azaghal.pos.vx += 0x10;
        }

        if (g_pads[1].pressed & PAD_CROSS) {
            self->ext.azaghal.pos.vx -= 0x10;
        }

        if (g_pads[1].pressed & PAD_CIRCLE) {
            self->ext.azaghal.pos.vy += 0x10;
        }

        if (g_pads[1].pressed & PAD_SQUARE) {
            self->ext.azaghal.pos.vy -= 0x10;
        }

        if (g_pads[1].pressed & PAD_RIGHT) {
            self->ext.azaghal.pos.vz += 0x10;
        }

        if (g_pads[1].pressed & PAD_LEFT) {
            self->ext.azaghal.pos.vz -= 0x10;
        }

        if (g_pads[1].pressed & PAD_SELECT) {
            self->ext.azaghal.pos.vx = 0;
            self->ext.azaghal.pos.vy = 0;
            self->ext.azaghal.pos.vz = 0;
        }

        FntPrint("x:%4x\n", self->ext.azaghal.pos.vx);
        FntPrint("y:%4x\n", self->ext.azaghal.pos.vy);
        FntPrint("z:%4x\n", self->ext.azaghal.pos.vz);
        func_us_801B33F4();
        break;
    }

    D_8006C384.y = self->ext.azaghal.lerpT;
    D_8006C38C.x = self->pose;
    D_8006C38C.y = self->poseTimer;
}

// 6 hitboxes are placed down the length of the sword
// which can damage the player
void EntityAzaghalSwordHitbox(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitAzaghal);
        self->hitboxState = 1;
        self->hitboxWidth = self->hitboxHeight = 4;
        return;
    }

    DestroyEntity(self);
}
