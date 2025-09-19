// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

#ifdef VERSION_PSP
extern s32 E_ID(BELL);
#endif

static SVECTOR vector_one_0 = {-16, 0, 0};
static SVECTOR vector_one_1 = {16, 0, 0};
static SVECTOR vector_one_2 = {-16, 26, 0};
static SVECTOR vector_one_4 = {16, 26, 0};
static SVECTOR vector_two_0 = {-50, 26, 0};
static SVECTOR vector_two_1 = {0, 26, 0};
static SVECTOR vector_two_2 = {-50, 128, 0};
static SVECTOR vector_two_3 = {0, 128, 0};
static SVECTOR vector_two_alt_0 = {50, 26, 0};
static SVECTOR vector_two_alt_2 = {50, 128, 0};
static SVEC4 points[] = {
    {&vector_one_0, &vector_one_1, &vector_one_2, &vector_one_4},
    {&vector_two_0, &vector_two_1, &vector_two_2, &vector_two_3},
    {&vector_two_alt_0, &vector_two_1, &vector_two_alt_2, &vector_two_3}};
static bellRopeParams rope_params[] = {{2, 12, 171}, {4, 29, 169}};
// Two sets of x, y, params
static s16 xy_params[] = {512, 456, 0, 512, 589, 1};
static VECTOR trans_vector = {0, 0, 1024, 0};

void EntityBell(Entity* self) {
    s16 angle;
    s32 sfxFlag;
    s32 primIndex;
    s32 gteFlag;
    s32 gteParams;
    s32 ropeLength;
    s32 priority;
    // These temp variables really seem like they should be some kind of
    // struct(s) or array(s)
    s32 tempPosX;
    s32 tempPosY;
    s32 tempX1;
    s32 tempY1;
    s32 tempX2;
    s32 tempY2;
    s32 tempX3;
    s32 tempY3;
    bellRopeParams* ropeParams;
    Entity* playerPtr;
    DRAWENV drawEnv;
    DR_ENV* drEnv;
    RECT clipRect;
    SVECTOR rotVector;
    s32 maxRopeSegments;
    s32 posY;
    SVEC4* pointsPtr;
    s32 posX;
    s32 ropeSegment;
    Primitive* prim;
    // It would be nice to get rid of this, but psx currently needs it
    s32 dummy[4];
    MATRIX mtx;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter + 8;
        self->ext.et_bell.unk9C = 0;
        ropeParams = &rope_params[self->params];
        maxRopeSegments = ropeParams->segments;
        priority = ropeParams->priority;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, maxRopeSegments + 6);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        ropeLength = ropeParams->length;
        prim->tpage = 15;
        prim->clut = PAL_BELL_2;
        prim->u0 = prim->u2 = 96;
        prim->u1 = prim->u3 = 128;
        prim->v0 = prim->v1 = 0;
        prim->v2 = prim->v3 = 24;
        prim->x0 = prim->x2 = self->posX.i.hi - 16;
        prim->x1 = prim->x3 = prim->x0 + 32;
        prim->y0 = prim->y1 = self->posY.i.hi - 10;
        prim->y2 = prim->y3 = prim->y1 + 24;
        prim->priority = (priority - 1);
        prim->drawMode = DRAW_UNK02;
        prim = prim->next;
        for (ropeSegment = 0; ropeSegment < maxRopeSegments; ropeSegment++) {
            prim->tpage = 15;
            prim->clut = PAL_BELL_2;
            prim->u0 = prim->u2 = 120;
            prim->u1 = prim->u3 = 128;
            prim->v0 = prim->v1 = 65;
            prim->v2 = prim->v3 = (ropeLength + 65);
            prim->priority = priority;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
        prim->tpage = 15;
        prim->clut = PAL_BELL_2;
        prim->u0 = prim->u2 = 96;
        prim->u1 = prim->u3 = 128;
        prim->v0 = prim->v1 = 36;
        prim->v2 = prim->v3 = 62;
        prim->priority = priority;
        prim->drawMode = DRAW_UNK02;
        prim = prim->next;
        for (ropeSegment = 0; ropeSegment < 2; ropeSegment++) {
            prim->tpage = 15;
            prim->clut = PAL_BELL_1;
            prim->u0 = prim->u2 = 177;
            prim->u1 = prim->u3 = 224;
            prim->v0 = prim->v1 = 1;
            prim->v2 = prim->v3 = 97;
            prim->priority = priority;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
        drawEnv = g_CurrentBuffer->draw;

        drEnv = g_api.func_800EDB08((POLY_GT4*)prim);
        if (drEnv == NULL) {
            DestroyEntity(self);
            return;
        }
        prim->type = PRIM_ENV;
        drawEnv.isbg = 0;
        drawEnv.r0 = 0;
        drawEnv.g0 = 0;
        drawEnv.b0 = 0;
        drawEnv.dtd = 0;
        drawEnv.ofs[0] = 0;
        clipRect.x = 0;
        clipRect.w = 256;
        clipRect.y = 20;
        clipRect.h = 207;
        drawEnv.clip = clipRect;
        SetDrawEnv(drEnv, &drawEnv);
        prim->priority = (g_unkGraphicsStruct.g_zEntityCenter - 1);
        prim->drawMode = DRAW_UNK_1000 | DRAW_HIDE;
        prim = prim->next;
        drEnv = g_api.func_800EDB08((POLY_GT4*)prim);
        if (drEnv == NULL) {
            DestroyEntity(self);
            return;
        }
        prim->type = PRIM_ENV;
        prim->priority = (g_unkGraphicsStruct.g_zEntityCenter + 1);
        prim->drawMode = DRAW_UNK_800 | DRAW_HIDE;
        prim = prim->next;
    }
    self->ext.et_bell.unk84 += self->ext.et_bell.unk88;
    if (self->ext.et_bell.unk84 > self->ext.et_bell.unk8C) {
        self->ext.et_bell.unk88 -= FIX(0.25);
    }
    if (self->ext.et_bell.unk84 < self->ext.et_bell.unk8C) {
        self->ext.et_bell.unk88 += FIX(0.25);
    }
    self->ext.et_bell.unk88 -= self->ext.et_bell.unk88 / 8;
    if ((abs(self->ext.et_bell.unk88) < FIX(0.375)) &&
        (abs(self->ext.et_bell.unk84 - self->ext.et_bell.unk8C) < FIX(0.375))) {
        self->ext.et_bell.unk88 = 0;
        self->ext.et_bell.unk84 = self->ext.et_bell.unk8C;
    }
    if (self->ext.et_bell.unk84 > FIX(64.0)) {
        self->ext.et_bell.unk84 = FIX(64.0);
    }
    if (self->ext.et_bell.unk84 < -FIX(64.0)) {
        self->ext.et_bell.unk84 = -FIX(64.0);
    }
    ropeParams = &rope_params[self->params];
    priority = ropeParams->priority;
    if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
        priority = g_unkGraphicsStruct.g_zEntityCenter - 4 + (priority - 169);
    }

    posX = self->posX.i.hi;
    posY = self->posY.i.hi;
    maxRopeSegments = ropeParams->segments;
    ropeLength = ropeParams->length;
    angle = 0;
    prim = self->ext.prim;
    prim->priority = (priority - 1);
    prim = prim->next;
    tempPosX = posX - 4;
    tempPosY = posY;
    tempX1 = posX + 4;
    tempY1 = posY;

    for (ropeSegment = 0; ropeSegment < maxRopeSegments; ropeSegment++) {
        posX -= (ropeLength * rsin(angle)) >> 12;
        posY += (ropeLength * rcos(angle)) >> 12;
        angle = ((self->ext.et_bell.unk84 / maxRopeSegments) * ropeSegment) /
                FIX(1);
        tempX2 = posX - ((rsin(angle + 1024) * 4) >> 12);
        tempY2 = posY + ((rcos(angle + 1024) * 4) >> 12);
        tempX3 = posX - ((rsin(angle - 1024) * 4) >> 12);
        tempY3 = posY + ((rcos(angle - 1024) * 4) >> 12);
        prim->x0 = tempPosX;
        prim->y0 = tempPosY;
        prim->x1 = tempX1;
        prim->y1 = tempY1;
        prim->x2 = tempX2;
        prim->y2 = tempY2;
        prim->x3 = tempX3;
        prim->y3 = tempY3;
        prim->priority = priority;
        prim->drawMode = DRAW_UNK02;
        tempPosX = tempX2;
        tempPosY = tempY2;
        tempX1 = tempX3;
        tempY1 = tempY3;
        prim = prim->next;
    }
    SetGeomScreen(1024);
    SetGeomOffset(posX, posY);
    rotVector.vx = 0;
    rotVector.vy = 0;
    rotVector.vz = angle;
    RotMatrix(&rotVector, &mtx);
    TransMatrix(&mtx, &trans_vector);
    SetRotMatrix(&mtx);
    SetTransMatrix(&mtx);
    pointsPtr = points;
    for (ropeSegment = 0; ropeSegment < 3; ropeSegment++) {
        RotTransPers4(
            pointsPtr->v0, pointsPtr->v1, pointsPtr->v2, pointsPtr->v3,
            (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2,
            (long*)&prim->x3, (long*)&gteFlag, (long*)&gteParams);
        pointsPtr++;
        prim->priority = priority;
        prim->drawMode = DRAW_UNK02;
        prim = prim->next;
    }
    tempPosX = posX;
    tempPosY = posY;
    playerPtr = &PLAYER;
    posX = playerPtr->posX.i.hi - tempPosX;
    posY = tempPosY + 124 - playerPtr->posY.i.hi;
    if ((u16)(posY) < 80 && (abs(posX) < 24)) {
        drEnv = (DR_ENV*)LOW(prim->r1);
        drawEnv = g_CurrentBuffer->draw;
        drawEnv.isbg = 0;
        drawEnv.ofs[0] = 0;
        clipRect.x = 0;
        clipRect.w = 256;
        clipRect.y = tempPosY + 120;
        clipRect.h = 227 - (tempPosY + 140);
        drawEnv.clip = clipRect;
        SetDrawEnv(drEnv, &drawEnv);
        prim->priority = (g_unkGraphicsStruct.g_zEntityCenter - 1);
        prim->drawMode = DRAW_UNK_1000;
        prim = prim->next;
        prim->drawMode = DRAW_UNK_800;
        prim = prim->next;
        g_api.func_8010DFF0(1, 1);
        g_api.func_8010E168(1, 32);
        g_Player.status |= PLAYER_STATUS_UNK100000 | PLAYER_STATUS_UNK8;
        if (!(g_Player.status &
              (PLAYER_STATUS_MIST_FORM | PLAYER_STATUS_BAT_FORM))) {
            g_Player.demo_timer = 2;
            g_Player.padSim = 0;
        }
    } else {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
    self->hitboxWidth = 56;
    self->hitboxHeight = 128;
    self->hitboxHeight /= 2;
    self->hitboxOffY = (tempPosY - 8) - self->posY.i.hi;
    self->hitboxOffY += self->hitboxHeight;
    self->hitboxState = 1;
    sfxFlag = 0;
    switch (self->ext.et_bell.swingStep) {
    case 0:
        self->ext.et_bell.unk8C = 0;
        playerPtr = &PLAYER;
        posX = playerPtr->posX.i.hi - self->posX.i.hi;
        posY = playerPtr->posY.i.hi - (tempPosY - 8);
        if ((u16)(posY) < 128 && (abs(posX) < 56)) {
            if (g_Player.vram_flag & 1) {
                sfxFlag = 1;
                self->ext.et_bell.swingStep = 1;
                if (posX > 0) {
                    self->ext.et_bell.unk88 = FIX(10.0);
                } else {
                    self->ext.et_bell.unk88 = -FIX(10.0);
                }
            }
            if (g_Player.vram_flag & 2) {
                sfxFlag = 1;
                self->ext.et_bell.swingStep = 2;
                if (posX > 0) {
                    self->ext.et_bell.unk88 = -FIX(8.0);
                } else {
                    self->ext.et_bell.unk88 = FIX(8.0);
                }
            }
        }
        break;
    case 1:
        playerPtr = &PLAYER;
        posX = playerPtr->posX.i.hi - self->posX.i.hi;
        if (!(g_Player.vram_flag & 1)) {
            sfxFlag = 1;
            self->ext.et_bell.swingStep = 0;
            if (posX > 0) {
                self->ext.et_bell.unk88 = FIX(10.0);
            } else {
                self->ext.et_bell.unk88 = -FIX(10.0);
            }
        } else if (posX > 0) {
            self->ext.et_bell.unk8C = FIX(20.0);
        } else {
            self->ext.et_bell.unk8C = -FIX(20.0);
        }
        break;
    case 2:
        self->ext.et_bell.unk8C = 0;
        if (!(g_Player.vram_flag & 2)) {
            sfxFlag = 1;
            self->ext.et_bell.swingStep = 0;
        }
        break;
    }
    if (self->ext.et_bell.unk9C) {
        self->ext.et_bell.unk9C--;
        return;
    }
    if (sfxFlag) {
        g_api.PlaySfx(SFX_CHAPEL_BELL);
        self->ext.et_bell.unk9C = 64;
        return;
    }
}

void EntityBellHelper(Entity* self) {
    Entity* entity;
    s32 count;
    s16* ptr = xy_params;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        for (entity = self + 1, count = 0; count < 2; count++, entity++) {
            CreateEntityFromCurrentEntity(E_ID(BELL), entity);
            entity->posX.i.hi = *ptr++ - g_Tilemap.scrollX.i.hi;
            entity->posY.i.hi = *ptr++ - g_Tilemap.scrollY.i.hi;
            entity->params = *ptr++;
        }
    }
}
