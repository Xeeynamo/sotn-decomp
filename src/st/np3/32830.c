REDACTED
#include "sfx.h"

REDACTED
REDACTED
REDACTED
        InitializeEntity(D_80180A60);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_GpuBuffers[0].draw.r0 = self->ext.generic.unk7C.S8.unk0;
        g_GpuBuffers[0].draw.g0 = self->ext.generic.unk7C.S8.unk1;
        g_GpuBuffers[0].draw.b0 = self->ext.generic.unk7E.modeU8.unk0;
        g_GpuBuffers[1].draw.r0 = self->ext.generic.unk7C.S8.unk0;
        g_GpuBuffers[1].draw.g0 = self->ext.generic.unk7C.S8.unk1;
        g_GpuBuffers[1].draw.b0 = self->ext.generic.unk7E.modeU8.unk0;
REDACTED
REDACTED
REDACTED

void func_801B28E4(Entity* self) {
    Entity* newEntity;
    s32 animFrame;
    s32 random0to3;
    u8* clutIndices;
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
        self->ext.et_801B28E4.timer = 0x80;
        self->animCurFrame = 15;
        g_CastleFlags[55] |= 1;
        if (self->params & FLAG_DEAD) {
            self->step = 4;
            return;
        }
    case 1:
        switch (self->step_s) {
        case 0:
REDACTED
REDACTED
                CreateEntityFromCurrentEntity(E_801B5DE8, newEntity);
                random0to3 = Random() & 3;
                newEntity->posX.i.hi = D_80180EA4[random0to3][0];
                newEntity->posY.i.hi = D_80180EA4[random0to3][1];
            }
REDACTED
REDACTED
                CreateEntityFromCurrentEntity(E_801B5E98, newEntity);
                if (random0to3 >= 3) {
                    random0to3 = 0;
                }
                newEntity->params = random0to3;
            }
            self->step_s++;
            /* fallthrough */
        case 1:
            if (AnimateEntity(D_80180E94, self) == 0) {
                self->ext.et_801B28E4.timer = (Random() & 0x7F) + 0x40;
                self->step_s++;
            }
            animFrame = self->animCurFrame;
            for (clutIndices = &D_80180E78; *clutIndices != 0xFF;
                 clutIndices += 4) {
                g_ClutIds[*clutIndices] =
                    g_ClutIds[0x200 + (clutIndices + animFrame)[1]];
            }
            if (animFrame == 1) {
                g_GpuBuffers[0].draw.r0 = 0x30;
                g_GpuBuffers[0].draw.g0 = 0x30;
                g_GpuBuffers[0].draw.b0 = 0x48;
                g_GpuBuffers[1].draw.r0 = 0x30;
                g_GpuBuffers[1].draw.g0 = 0x30;
                g_GpuBuffers[1].draw.b0 = 0x48;
                return;
            }
            break; // Breaks to case 4 of outer switch
        case 2:
            g_GpuBuffers[0].draw.r0 = 0x10;
            g_GpuBuffers[0].draw.g0 = 8;
            g_GpuBuffers[0].draw.b0 = 0x38;
            g_GpuBuffers[1].draw.r0 = 0x10;
            g_GpuBuffers[1].draw.g0 = 8;
            g_GpuBuffers[1].draw.b0 = 0x38;
            if (--self->ext.et_801B28E4.timer == 0) {
                SetSubStep(0);
            }
            return;
        default:
            return;
        }

    // careful, this is the outer switch!
    case 4:
        g_GpuBuffers[0].draw.r0 = 0x10;
        g_GpuBuffers[0].draw.g0 = 8;
        g_GpuBuffers[0].draw.b0 = 0x38;
        g_GpuBuffers[1].draw.r0 = 0x10;
        g_GpuBuffers[1].draw.g0 = 8;
        g_GpuBuffers[1].draw.b0 = 0x38;
    }
}

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_InitializeEntityData0);
REDACTED
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
REDACTED
        self->primIndex = primIndex;
REDACTED
        self->flags |= FLAG_HAS_PRIMS;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = 2;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            PlaySfxPositional(NA_SE_EV_WINDOW_LATCH);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
REDACTED
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->primIndex = primIndex;
REDACTED
        self->flags |= FLAG_HAS_PRIMS;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = 2;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->ext.castleDoor.rotZ = 0;
REDACTED
REDACTED
REDACTED
            g_Tilemap.fg[tilePos] = *tilePtr;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    svec1.vy = self->ext.castleDoor.rotZ;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = 6;
REDACTED
            prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
REDACTED

extern SVECTOR D_801810B0;
extern s16 D_80181068;
extern s16* D_80181088;
extern u8 D_80181008[];
extern u8 D_80181020[];

void EntityBackgroundBushes(Entity* self) {
    byte stackpad[8];

    // Lots of ugly pointers
    u8* var_s1;
    s16* var_s4;
    s16* var_s5;
    s16** var_s8;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s32 yOffset;
    s16 xPos;
    s16 yPos;
    s32 rotTransXYResult;
    s32 unused1; // return args for rottranspers
    s32 unused2; // we don't use them.
    VECTOR trans;
    MATRIX m;

    if (!self->step) {
REDACTED
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x48);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
REDACTED
        self->ext.prim = prim;
REDACTED
REDACTED
            prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
    SetGeomScreen(0x400);
    SetGeomOffset(0x80, self->posY.i.hi);
    RotMatrix(&D_801810B0, &m);
    SetRotMatrix(&m);
    if (self->params) {
        trans.vx = self->posX.i.hi - 0x200;
    } else {
        trans.vx = self->posX.i.hi + 0x200;
    }
    trans.vy = 0;
    var_s5 = &D_80181068;
    var_s8 = &D_80181088;
    prim = self->ext.prim;
    for (i = 0; i < 4; i++, var_s8++, var_s5 += 4) {
        trans.vz = *var_s5 + 0x400;
        TransMatrix(&m, &trans);
        SetTransMatrix(&m);
        RotTransPers(&D_801810B0, &rotTransXYResult, &unused1, &unused2);
        // Split out the upper and lower halfword of rotTransXYResult
        xPos = rotTransXYResult & 0xFFFF;
        yPos = rotTransXYResult >> 16;
        xPos = xPos % var_s5[3];
        xPos -= var_s5[3];
        yPos = self->posY.i.hi;
        var_s4 = *var_s8;
        while (xPos < 0x140) {
            var_s1 = &D_80181008[0];
            var_s1 += ((*var_s4++) * 4);
            prim->u0 = prim->u2 = var_s1[0];
            prim->u1 = prim->u3 = prim->u0 + var_s1[2];
            prim->v0 = prim->v1 = var_s1[1];
            prim->v2 = prim->v3 = prim->v0 + var_s1[3];
            prim->x0 = prim->x2 = xPos - var_s1[2] / 2;
            prim->x1 = prim->x3 = xPos + var_s1[2] / 2;
            prim->y0 = prim->y1 = yPos - var_s1[3];
            prim->y2 = prim->y3 = yPos;
            prim->clut = var_s5[2];
            prim->priority = var_s5[1];
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;

            if (prim == NULL) {
                return;
            }
            if (i > 1) {
                yOffset = var_s1[3];
                var_s1 = &D_80181020[0];
                prim->u0 = prim->u2 = var_s1[0];
                prim->u1 = prim->u3 = prim->u0 + var_s1[2];
                prim->v0 = prim->v1 = var_s1[1];
                prim->v2 = prim->v3 = prim->v0 + var_s1[3];
                var_s1 += (i - 2) * 4;
                prim->x0 = prim->x2 = xPos - var_s1[2] / 2;
                prim->x1 = prim->x3 = xPos + var_s1[2] / 2;
                prim->y0 = prim->y1 = (yPos - yOffset) - var_s1[3];
                prim->y2 = prim->y3 = (yPos - yOffset);
                prim->clut = 0x17;
                if (i > 2) {
                    prim->clut = 0x49;
                }
                prim->priority = var_s5[1];
                prim->drawMode = DRAW_UNK02;
                prim = prim->next;
                if (prim == NULL) {
                    return;
                }
            }
            xPos += *var_s4++;
            if (*var_s4 == -1) {
                var_s4 = *var_s8;
            }
        }
    }
    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
REDACTED
        self->primIndex = primIndex;
REDACTED
        self->flags |= FLAG_HAS_PRIMS;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode = 2;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
REDACTED
REDACTED
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
REDACTED
        self->primIndex = primIndex;
REDACTED
        self->flags |= FLAG_HAS_PRIMS;
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = 8;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_ClutIds[var_a0[0]] = g_ClutIds[var_a0[2] + 0x200];
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_ClutIds[var_a0[0]] = g_ClutIds[var_a0[3] + 0x200];
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    var_a3 = -1 * g_Tilemap.scrollX.i.hi % 38;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode = 0x33;
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode = 8;
REDACTED
REDACTED
REDACTED

void func_801B3D24(Primitive* prim) {
    s32 xVar;
    s32 yVar;

    switch (prim->p3) {
    case 1:
        xVar = (Random() & 0xF) - 8;
        prim->x0 = g_CurrentEntity->posX.i.hi + xVar;
        prim->y0 = 0x9C;
        prim->x1 = 0;
        prim->y1 = 0;
        if (xVar > 0) {
            LOW(prim->x3) = Random() << 6;
        } else {
            LOW(prim->x3) = -Random() * 0x40;
        }
        LOW(prim->x2) = (Random() << 8) + FIX(-4);
        prim->blendMode = 2;
        prim->p3++;
        /* fallthrough */
    case 2:
        xVar = (prim->x0 << 0x10) + (u16)prim->x1;
        yVar = (prim->y0 << 0x10) + (u16)prim->y1;
        xVar += LOW(prim->x3);
        yVar += LOW(prim->x2);
        prim->x0 = (xVar >> 0x10);
        prim->x1 = xVar & 0xFFFF;
        prim->y0 = (yVar >> 0x10);
        prim->y1 = yVar & 0xFFFF;

        LOW(prim->x2) += FIX(1.0 / 4.0);
        if (LOW(prim->x2) <= 0x60000) {
            return;
        }
        prim->p3++;
        break;
    case 3:
        prim->blendMode = 8;
        prim->p3 = 0;
        break;
    }
}

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        entity->rotZ = -0x200;
        entity->drawFlags |= 4;
REDACTED
        if (g_CastleFlags[0x30] != 0) {
            entity->rotZ = 0;
REDACTED
REDACTED
REDACTED
REDACTED
            entity->rotZ += 4;
            if (entity->rotZ > 0) {
                entity->rotZ = 0;
                if (g_CastleFlags[48] == 0) {
                    g_api.PlaySfx(SFX_LEVER_METAL_BANG);
REDACTED
                g_CastleFlags[48] = 1;
            } else if (!(g_Timer & 0xF)) {
                g_api.PlaySfx(SFX_LEVER_METAL_BANG);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    posX += rcos(entity->rotZ) * 0x280;
    posY += rsin(entity->rotZ) * 0x280;
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
    s32 xDiff;
    s32 collision;

REDACTED
REDACTED
REDACTED
REDACTED
        self->ext.cavernDoor.xCoord.val = self->posX.val;
        self->ext.cavernDoor.xCoord.val = self->posX.val; // ? WTF
REDACTED
REDACTED
        collision = GetPlayerCollisionWith(self, 6, 5, 4);
        self->ext.cavernDoor.collision = collision;

        if (collision != 0) {
            xDiff = self->posX.i.hi - FIX_TO_I(self->ext.cavernDoor.xCoord.val);
            player = &PLAYER;
            player->posX.i.hi += xDiff;
            player->posY.i.hi += 1;
            // These two lines are extra compared to NO3
            D_80097488.x.i.hi += xDiff;
            D_80097488.y.i.hi += 1;
REDACTED
        self->ext.cavernDoor.xCoord.val = self->posX.val;
        self->ext.cavernDoor.yCoord.val = self->posY.val;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    s32 primIndex;
    s16* tileLayoutPtr;
REDACTED
    Primitive* prim;
REDACTED
    s32 tilePos;
    s32 tileSteps;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[48]) {
REDACTED
REDACTED
            tileLayoutPtr += 3;
REDACTED
            primIndex = g_api.AllocPrimitives(PRIM_TILE, 64);
            if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.cavernDoor.prim = prim;
            while (prim != NULL) {
                prim->u0 = prim->v0 = 1;
                prim->r0 = 64;
                prim->b0 = 128;
                prim->g0 = 96;
                prim->priority = self->zPriority + 0x18;
                prim->drawMode = DRAW_HIDE;
                prim->p3 = 0;
                prim = prim->next;
REDACTED
REDACTED
REDACTED
REDACTED
            g_Tilemap.fg[tilePos] = *tileLayoutPtr++;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[48]) {
            // Missing line compared to NO3
            // g_api.PlaySfx(SFX_SWITCH_CLICK);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->posY.val += FIX(0.375);
        self->ext.cavernDoor.jiggler++;
        // While the door opens, it jiggles left and right by repeatedly
        // incrementing and decrementing its x position.
        if (self->ext.cavernDoor.jiggler & 1) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        tileSteps = (self->posY.i.hi - 136);
        tileSteps /= 16;
        if (tileSteps > 3) {
            tileSteps = 3;
REDACTED
REDACTED
        // Extra block compared to NO3
        if (!(self->ext.cavernDoor.jiggler & 15)) {
            g_api.PlaySfx(SFX_STONE_MOVE_C);
REDACTED
REDACTED
        tilePos = 0x76;
REDACTED
        tileLayoutPtr += 3;
        for (i = 0; i < tileSteps; tilePos += 0x10, i++) {
            g_Tilemap.fg[tilePos] = *tileLayoutPtr++;
REDACTED
REDACTED
        if (g_Timer & 1) {
            break;
        }
        prim = self->ext.cavernDoor.prim;
        prim = FindFirstUnkPrim(prim);
        if (prim != NULL) {
            prim->p3 = 1;
        }
REDACTED
        if (g_Timer & 15) {
            break;
        }
REDACTED
        if (entity == NULL) {
            break;
REDACTED
        CreateEntityFromEntity(6, self, entity);
        entity->posY.i.hi = 156;
        entity->posX.i.hi += -8 + (Random() & 15);
        entity->zPriority = self->zPriority + 2;
        entity->params = 0x10;
        entity->drawFlags |= (FLAG_DRAW_ROTX + FLAG_DRAW_ROTY);
        entity->rotX = entity->rotY = 192;
REDACTED
REDACTED
REDACTED
    if (self->flags & FLAG_HAS_PRIMS) {
        for (prim = self->ext.cavernDoor.prim; prim != NULL;
             prim = prim->next) {
            if (prim->p3) {
                func_801B3D24(prim);
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode = 2;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
    s32 temp_a0 = GetPlayerCollisionWith(entity, 8, 4, 4);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[49] != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            entity->posY.val += FIX(0.75);
            if ((g_Tilemap.scrollY.i.hi + entity->posY.i.hi) > 160) {
                entity->posY.i.hi = 160 - g_Tilemap.scrollY.i.hi;
                g_api.PlaySfx(SFX_SWITCH_CLICK);
                g_CastleFlags[49] = 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
    s16 primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
REDACTED
        poly = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
REDACTED
        self->flags |= FLAG_HAS_PRIMS;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->posX.i.hi = 416 - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = 64 - g_Tilemap.scrollY.i.hi;
        if (g_CastleFlags[49] != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[49] != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->posY.val += FIX(0.5);
        if ((self->posY.i.hi + g_Tilemap.scrollY.i.hi) >= 175) {
            PlaySfxPositional(SFX_START_SLAM_B);
            self->posY.i.hi = 175 - g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_Tilemap.fg[var_a1] = 0x4FA;
            g_Tilemap.fg[var_a1 + 1] = 0x4FA;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if ((self->step < 3) && (GetPlayerCollisionWith(self, 16, 16, 5) & 4)) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    s16 primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
REDACTED
        poly = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
REDACTED
        self->flags |= FLAG_HAS_PRIMS;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[49] != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[49] != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->posY.val -= FIX(0.5);
        temp = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
REDACTED
            self->posY.i.hi = -16 - g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        temp = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
        g_Tilemap.fg[var_a1] = 0;
        g_Tilemap.fg[var_a1 + 1] = 0;
REDACTED
REDACTED
REDACTED
        g_Tilemap.fg[var_a1] = 0x4FA;
        g_Tilemap.fg[var_a1 + 1] = 0x4FA;
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        entity->hitboxState = 1;
REDACTED
REDACTED
REDACTED
                g_Tilemap.fg[0xA8E / 2] = 0x129;
                g_Tilemap.fg[0xA90 / 2] = 0x132;
REDACTED
REDACTED
REDACTED
            g_Tilemap.fg[0xA8E / 2] = 0x6C8;
            g_Tilemap.fg[0xA90 / 2] = 0x6C9;
REDACTED
REDACTED
            g_Tilemap.fg[0xA8E / 2] = 0x6C8;
            g_Tilemap.fg[0xA90 / 2] = 0x6C9;
REDACTED
REDACTED
REDACTED
REDACTED
        if (entity->hitFlags != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
        self->hitboxState = 2;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_BgLayers[0].layout[tilePos] = *tileLayoutPtr;
            g_BgLayers[0].layout[tilePos + 1] = *(tileLayoutPtr + 3);
REDACTED
REDACTED
REDACTED

        if (g_CastleFlags[jewelSwordRoomUnlock] & rockBroken) {
REDACTED
REDACTED
REDACTED
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
REDACTED
REDACTED
REDACTED
            self->hitboxState = 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (self->hitFlags != 0) {
REDACTED
REDACTED
REDACTED
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
REDACTED
REDACTED
REDACTED
REDACTED
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
REDACTED
REDACTED
REDACTED
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
REDACTED
REDACTED
                    newEntity->velocityX = -0x8000 - (Random() << 8);
                    newEntity->velocityY = -Random() * 0x100;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            newEntity = AllocEntity(g_Entities + 160, g_Entities + 192);
REDACTED
REDACTED
REDACTED
REDACTED
            g_CastleFlags[jewelSwordRoomUnlock] |= rockBroken;
            self->hitboxState = 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_CastleFlags[jewelSwordRoomUnlock] |= wolfFlag;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
// right side of the merman room rock, breaks when hit
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
        self->hitboxState = 2;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_BgLayers[0].layout[tilePos] = *tileLayoutPtr;
            g_BgLayers[0].layout[tilePos + 1] = *(tileLayoutPtr + 3);
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[jewelSwordRoomUnlock] & rockBroken) {
REDACTED
REDACTED
REDACTED
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
REDACTED
REDACTED
REDACTED
            self->hitboxState = 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (self->hitFlags != 0) {
REDACTED
REDACTED
REDACTED
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
REDACTED
REDACTED
REDACTED
REDACTED
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
REDACTED
REDACTED
REDACTED
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
REDACTED
REDACTED
                    newEntity->velocityX = (Random() << 8) + 0x8000;
                    newEntity->velocityY = -Random() * 0x100;
                    newEntity->facingLeft = 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_CastleFlags[jewelSwordRoomUnlock] |= rockBroken;
            self->hitboxState = 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_CastleFlags[jewelSwordRoomUnlock] |= batFlag;
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
        if (g_CastleFlags[58] != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if ((g_CastleFlags[51] & 12) == 12) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                g_Tilemap.fg[tileLayoutPos] = *tileLayoutPtr;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                g_BgLayers[0].layout[tileLayoutPos] = *tileLayoutPtr;
REDACTED
REDACTED
REDACTED
REDACTED
        g_CastleFlags[58] |= 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
    Collider collider;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->drawFlags |= 4;
REDACTED
REDACTED
REDACTED
REDACTED
        self->velocityY += FIX(0.25);
        self->rotZ -= 0x20;
REDACTED
REDACTED
REDACTED
REDACTED
        if (collider.effects & EFFECT_SOLID) {
            if (self->velocityY > FIX(4.0)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
                    CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            temp_a0 = -self->velocityY;
            self->velocityY = -self->velocityY;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->velocityY = temp_a0 - (var_a1 >> 3);
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
REDACTED
REDACTED
        self->posX.i.hi = 1432 - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = 200 - g_Tilemap.scrollY.i.hi;
REDACTED
        if (g_CastleFlags[stairwayPieceBroken]) {
REDACTED
            g_Tilemap.fg[0x4D9] = 0x3EE;
            g_Tilemap.fg[0x539] = 0x3D2;
REDACTED
REDACTED
REDACTED
REDACTED
        g_Tilemap.fg[0x4D9] = 0x408;
        g_Tilemap.fg[0x539] = 0x40D;
REDACTED
REDACTED
REDACTED
        if (self->hitFlags != 0) {
            g_api.PlaySfx(SFX_STOMP_SOFT_A);
REDACTED
REDACTED
        if (self->flags & FLAG_DEAD) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
        g_Tilemap.fg[0x4D9] = 0x3EE;
        g_Tilemap.fg[0x539] = 0x3D2;
        g_CastleFlags[stairwayPieceBroken] = true;
REDACTED
REDACTED
REDACTED
            CreateEntityFromEntity(E_EQUIP_ITEM_DROP, self, newEntity);
REDACTED
REDACTED
REDACTED
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
REDACTED
        self->primIndex = primIndex;
REDACTED
        self->flags |= FLAG_HAS_PRIMS;
        UnkPolyFunc2(prim);
        v1 = g_Tilemap.tileDef->gfxIndex[0x409];
REDACTED
        temp = g_Tilemap.tileDef->gfxPage[0x409];
        prim->clut = g_Tilemap.tileDef->clut[0x409];
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode = 2;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        UnkPrimHelper(prim);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
    Collider collider;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->rotY = 0x60;
        self->rotX = 0x60;
        self->drawFlags |= 7;
REDACTED
REDACTED
        self->velocityX = rnd * rcos(rndAngle);
        self->velocityY = rnd * rsin(rndAngle);
        if (self->velocityX > 0) {
            self->facingLeft = 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->velocityY += FIX(0.125);
        self->rotZ -= 0x20;
REDACTED
        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 8, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
REDACTED
        self->flags &= ~FLAG_UNK_08000000;
        self->facingLeft = Random() & 1;
        g_api.PlaySfxVolPan(SFX_THUNDER_B, 0x40, (self->posX.i.hi >> 0x4) - 8);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
REDACTED
        self->flags &= ~FLAG_UNK_08000000;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
    s32 temp_a0 = GetPlayerCollisionWith(self, 8, 4, 4);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[50]) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if ((g_Tilemap.scrollY.i.hi + self->posY.i.hi) > 193) {
                self->posY.i.hi = 193 - g_Tilemap.scrollY.i.hi;
                g_CastleFlags[50] = true;
                g_api.PlaySfx(SFX_SWITCH_CLICK);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
    s16 primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[50] != 0) {
            for (
                tilePos = 0x48, i = 7, self->step = 128, self->animCurFrame = 0;
                i >= 0; tilePos += 0x10, i--) {
                g_Tilemap.fg[tilePos] = 0;
REDACTED
REDACTED
REDACTED
REDACTED
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 64);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->primIndex = primIndex;
REDACTED
        self->flags |= FLAG_HAS_PRIMS;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = 8;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_Tilemap.fg[tilePos] = temp;
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[50]) {
            g_api.PlaySfx(SFX_STONE_MOVE_A);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->posY.val += FIX(0.375);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_api.PlaySfx(SFX_STONE_MOVE_A);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_Tilemap.fg[tilePos] = 0;
REDACTED
REDACTED
        if (!(g_Timer & 1)) {
            prim = FindFirstUnkPrim(self->ext.heartRoomGoldDoor.prim);
REDACTED
REDACTED
REDACTED
            if (!(g_Timer & 0xF)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, newEntity);
REDACTED
REDACTED
REDACTED
                    newEntity->rotX = newEntity->rotY = 192;
                    newEntity->drawFlags |= 3;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if (self->flags & FLAG_HAS_PRIMS) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED

REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
REDACTED
REDACTED
        temp = g_Tilemap.fg[0x12 / 2];
        g_Tilemap.fg[0xC / 2] = temp;
        temp = g_Tilemap.fg[0x14 / 2];
        g_Tilemap.fg[0xE / 2] = temp;
        temp = g_Tilemap.fg[0x72 / 2];
        g_Tilemap.fg[0x6C / 2] = temp;
        temp = g_Tilemap.fg[0x74 / 2];
        g_Tilemap.fg[0x6E / 2] = temp;
        temp = g_Tilemap.fg[0xD2 / 2];
        g_Tilemap.fg[0xCC / 2] = temp;
        temp = g_Tilemap.fg[0xD4 / 2];
        g_Tilemap.fg[0xCE / 2] = temp;
REDACTED
REDACTED
REDACTED
REDACTED
