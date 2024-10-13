// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"
#include "sfx.h"

// vase in the room with the door to the caverns
void EntityCavernDoorVase(Entity* self) {
    ObjInit2* objInit = &D_80180BFC[self->params];

    if (self->step == 0) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->facingLeft = objInit->facingLeft;
        self->unk5A = objInit->unk5A;
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->drawMode = objInit->drawMode;
        if (objInit->unkC != 0) {
            self->flags = objInit->unkC;
        }
    }

    AnimateEntity(objInit->animFrames, self);
}

void EntityUnkId12(Entity* entity) {
    s32 ret;
    u16* temp_v0_2;
    u16 temp_s1 = entity->params;
    u16 phi_v1;
    u16 unk;

    entity->unk6D[0] = 0;

    if (entity->step != 0) {
        switch (temp_s1) {
        case 4:
        case 5:
            if (g_Tilemap.x != 0) {
                return;
            }
            break;

        case 6:
            if (g_pads->pressed & PAD_TRIANGLE) {
                g_Tilemap.x = 0;
                g_Tilemap.width = 1280;
                entity->step++;
                return;
            }
            break;
        }

        if (entity->hitParams) {
            ret = GetSideToPlayer();
            phi_v1 = entity->ext.generic.unk7C.s;
            if (phi_v1 != 0) {
                phi_v1 = (ret & 2) * 2;
            } else {
                phi_v1 = (ret & 1) * 4;
            }
            unk = 8;
            temp_s1 = (temp_s1 * unk) + phi_v1;
            temp_v0_2 = &D_80180DD0[temp_s1];
            g_Tilemap.x = *(temp_v0_2++);
            g_Tilemap.y = *(temp_v0_2++);
            g_Tilemap.width = *(temp_v0_2++);
            g_Tilemap.height = *(temp_v0_2++);
        }
    } else {
        InitializeEntity(D_80180AF4);
        entity->ext.generic.unk7C.s = D_80180DC8[temp_s1];
        if (entity->ext.generic.unk7C.s != 0) {
            entity->hitboxWidth = D_80180DC0[temp_s1];
            entity->hitboxHeight = 16;
        } else {
            entity->hitboxWidth = 16;
            entity->hitboxHeight = D_80180DC0[temp_s1];
        }
    }
}

extern u16 g_EInitBreakable[];
extern u8* g_eBreakableAnimations[8];
extern u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakableanimSets[];
extern u8 g_eBreakableDrawModes[];
void EntityBreakable(Entity* entity) {
    u16 breakableType = entity->params >> 0xC;
    if (entity->step) {
        AnimateEntity(g_eBreakableAnimations[breakableType], entity);
        if (entity->hitParams) { // If the candle is destroyed
            Entity* entityDropItem;
            g_api.PlaySfx(SFX_CANDLE_HIT);
            entityDropItem = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entityDropItem != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, entityDropItem);
                entityDropItem->params =
                    g_eBreakableExplosionTypes[breakableType];
            }
            ReplaceBreakableWithItemDrop(entity);
        }
    } else {
        InitializeEntity(g_EInitBreakable);
        entity->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x14;
        entity->drawMode = g_eBreakableDrawModes[breakableType];
        entity->hitboxHeight = g_eBreakableHitboxes[breakableType];
        entity->animSet = g_eBreakableanimSets[breakableType];
    }
}

void EntityUnkId16(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180AD0);
        self->ext.generic.unk7C.S8.unk0 = 16;
        self->ext.generic.unk7C.S8.unk1 = 8;
        self->ext.generic.unk7E.modeU8.unk0 = 56;

    case 1:
        g_GpuBuffers[0].draw.r0 = self->ext.generic.unk7C.S8.unk0;
        g_GpuBuffers[0].draw.g0 = self->ext.generic.unk7C.S8.unk1;
        g_GpuBuffers[0].draw.b0 = self->ext.generic.unk7E.modeU8.unk0;
        g_GpuBuffers[1].draw.r0 = self->ext.generic.unk7C.S8.unk0;
        g_GpuBuffers[1].draw.g0 = self->ext.generic.unk7C.S8.unk1;
        g_GpuBuffers[1].draw.b0 = self->ext.generic.unk7E.modeU8.unk0;
        break;
    }
}

extern u8 D_80180EA0[];
extern u8 D_80180F60;

extern u16 D_80180FAC[];
extern u16 D_80180FBC[];

extern u8 D_80180FDC[][2];

// lightning and sound for background
// More complicated than NP3 version.
void EntityBackgroundLightning(Entity* self) {
    Entity* otherEnt;
    s32 playerRealX;
    s32 randOf3;
    s32 clutDest;
    s32 i;
    s32 clutSrc;
    u8* clutIndices;
    u8* var_s1;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);

        self->ext.backgroundLightning.timer = 0x80;
        self->animCurFrame = 0xF;
        var_s1 = &D_80180EA0[0];
        for (i = 0; i < 12; i++) {
            clutDest = var_s1[0];
            clutSrc = 15;
            clutSrc = var_s1[clutSrc];
            g_ClutIds[clutDest] = g_ClutIds[clutSrc + 0x200];
            var_s1 += 16;
        }
        if (self->params & 256) {
            self->step = 4;
            break;
        }
        if (g_CastleFlags[CASTLE_FLAG_55]) {
            self->params = 0;
        }
    case 1:
        switch (self->step_s) {
        case 0:
            otherEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (otherEnt != NULL) {
                CreateEntityFromCurrentEntity(E_LIGHTNING_THUNDER, otherEnt);
                randOf3 = (Random() & 3);
                otherEnt->posX.i.hi = D_80180FDC[randOf3][0];
                otherEnt->posY.i.hi = D_80180FDC[randOf3][1];
            }
            otherEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (otherEnt != NULL) {
                CreateEntityFromCurrentEntity(E_LIGHTNING_CLOUD, otherEnt);
                if (randOf3 > 2) {
                    randOf3 = 0;
                }
                otherEnt->params = randOf3;
            }
            self->step_s += 1;

        case 1:
            if (AnimateEntity(D_80180FAC, self) == 0) {
                self->ext.backgroundLightning.timer = (Random() & 0x7F) + 0x40;
                self->step_s += 1;
            }
            clutIndices = &D_80180F60;
            if (!self->params) {
                clutIndices += 0x30;
            }
            for (clutSrc = self->animCurFrame; *clutIndices != 0xFF;
                 clutIndices += 4) {
                i = clutIndices[0];
                g_ClutIds[i] = g_ClutIds[(clutIndices + clutSrc)[1] + 0x200];
            }

            if (clutSrc == 1) {
                g_GpuBuffers[0].draw.r0 = 0x30;
                g_GpuBuffers[0].draw.g0 = 0x30;
                g_GpuBuffers[0].draw.b0 = 0x48;
                g_GpuBuffers[1].draw.r0 = 0x30;
                g_GpuBuffers[1].draw.g0 = 0x30;
                g_GpuBuffers[1].draw.b0 = 0x48;
            } else {
                g_GpuBuffers[0].draw.r0 = 0x10;
                g_GpuBuffers[0].draw.g0 = 8;
                g_GpuBuffers[0].draw.b0 = 0x38;
                g_GpuBuffers[1].draw.r0 = 0x10;
                g_GpuBuffers[1].draw.g0 = 8;
                g_GpuBuffers[1].draw.b0 = 0x38;
            }
            break;
        case 2:
            g_GpuBuffers[0].draw.r0 = 0x10;
            g_GpuBuffers[0].draw.g0 = 8;
            g_GpuBuffers[0].draw.b0 = 0x38;
            g_GpuBuffers[1].draw.r0 = 0x10;
            g_GpuBuffers[1].draw.g0 = 8;
            g_GpuBuffers[1].draw.b0 = 0x38;
            if (!--self->ext.backgroundLightning.timer) {
                SetSubStep(0);
            }
            break;
        }
        if (self->params != 1) {
            break;
        }
        otherEnt = &PLAYER;
        playerRealX = g_Tilemap.scrollX.i.hi + otherEnt->posX.i.hi;
        if (playerRealX > 0x300) {
            g_CastleFlags[CASTLE_FLAG_55] = 1;
            SetStep(2);
        }
        break;

    case 2:
        if (AnimateEntity(D_80180FBC, self) == 0) {
            self->params = 0;
            SetStep(1);
        }
        g_GpuBuffers[0].draw.r0 = 16;
        g_GpuBuffers[0].draw.g0 = 8;
        g_GpuBuffers[0].draw.b0 = 56;
        g_GpuBuffers[1].draw.r0 = 16;
        g_GpuBuffers[1].draw.g0 = 8;
        g_GpuBuffers[1].draw.b0 = 56;
        var_s1 = &D_80180EA0[0];
        for (i = 0; i < 12; i++) {
            clutDest = var_s1[0];
            clutSrc = self->animCurFrame;
            clutSrc = var_s1[clutSrc];
            g_ClutIds[clutDest] = g_ClutIds[clutSrc + 0x200];
            var_s1 += 16;
        }
        break;

    case 4:
        g_GpuBuffers[0].draw.r0 = 16;
        g_GpuBuffers[0].draw.g0 = 8;
        g_GpuBuffers[0].draw.b0 = 56;
        g_GpuBuffers[1].draw.r0 = 16;
        g_GpuBuffers[1].draw.g0 = 8;
        g_GpuBuffers[1].draw.b0 = 56;
    }
    if (self->params == 1) {
        switch (self->ext.backgroundLightning.unk84) {
        case 0:
            g_api.PlaySfx(SET_UNK_90);
            self->ext.backgroundLightning.unk84++;
            D_80097928 = 1;
            D_80097910 = SE_INTRO_WIND_QUIET;
            break;
        case 1:
            if (g_api.func_80131F68() == false) {
                D_80097928 = 0;
                g_api.PlaySfx(D_80097910);
                self->ext.backgroundLightning.unk84++;
            }
            break;
        case 2:
            otherEnt = &PLAYER;
            playerRealX = g_Tilemap.scrollX.i.hi + otherEnt->posX.i.hi;
            if (playerRealX > 0x300) {
                g_api.PlaySfx(SET_UNK_90);
                D_80097928 = 1;
                D_80097910 = MU_DRACULAS_CASTLE;
                self->ext.backgroundLightning.unk84++;
            }
            break;
        case 3:
            if (g_api.func_80131F68() == false) {
                D_80097928 = 0;
                g_api.PlaySfx(D_80097910);
                self->ext.backgroundLightning.unk84++;
            }
            break;
        }
    }
}

// window that opens and shuts in the background
void EntityShuttingWindow(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    SVECTOR svec;
    SVEC4* svec4;
    VECTOR vec;
    MATRIX mtx;
    s32 flag;
    s32 p;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.shuttingWindow.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 0xD;
            prim->u0 = prim->u2 = 0x9C;
            prim->u1 = prim->u3 = 0x84;
            prim->v1 = 4;
            prim->v0 = 4;
            prim->v2 = prim->v3 = 0x7C;
            prim->priority = 0x5F;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }

    case 1:
        self->ext.shuttingWindow.unk80 += 8;
        if (self->ext.shuttingWindow.unk80 > 0x300) {
            self->ext.shuttingWindow.unk80 = 0x300;
            self->ext.shuttingWindow.unk82 = 0;
            self->step++;
        }
        break;

    case 2:
        self->ext.shuttingWindow.unk80 += self->ext.shuttingWindow.unk82;
        self->ext.shuttingWindow.unk82 -= 4;
        if (self->ext.shuttingWindow.unk80 < 0) {
            PlaySfxPositional(SE_NO3_WINDOW_CLOSE);
            self->ext.shuttingWindow.unk80 = 0;
            self->ext.shuttingWindow.timer = 32;
            self->step++;
        }
        break;

    case 3:
        if (--self->ext.shuttingWindow.timer == 0) {
            self->step = 1;
        }
        break;
    }
    SetGeomScreen(0x400);
    SetGeomOffset(self->posX.i.hi, self->posY.i.hi);

    svec4 = D_80181024;
    prim = self->ext.shuttingWindow.prim;

    for (i = 0; i < 2; svec4++, i++) {
        svec.vx = 0;
        if (i != 0) {
            svec.vy = self->ext.shuttingWindow.unk80;
        } else {
            svec.vy = -self->ext.shuttingWindow.unk80;
        }
        svec.vz = 0;
        RotMatrix(&svec, &mtx);
        if (i == 0) {
            vec.vx = -0x18;
        } else {
            vec.vx = 0x19;
        }
        vec.vy = 0;
        vec.vz = 0x400;
        TransMatrix(&mtx, &vec);
        SetRotMatrix(&mtx);
        SetTransMatrix(&mtx);
        RotTransPers4(svec4->v0, svec4->v1, svec4->v2, svec4->v3,
                      (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2,
                      (long*)&prim->x3, (long*)&p, (long*)&flag);
        prim = prim->next;
    }
}

// main door to the castle that closes during intro
void EntityCastleDoor(Entity* self) {
    SVECTOR sVec1;
    VECTOR vec1;
    MATRIX mtx1;
    MATRIX mtx2;
    CVECTOR cVec1;
    CVECTOR cVec2;
    SVECTOR sVec2;
    long sxy2, sxy3, p;
    Primitive* prim;
    SVECTOR** var_s5;
    SVEC4* var_s6;
    s16 primIndex;
    s32 temp_s3;
    s32 tilePos;
    s32 i;
    u16* tilePtr;
    u8* var_a0;

    sVec2 = D_801B73E0;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        var_a0 = D_80181118;
        self->primIndex = primIndex;
        self->ext.castleDoor.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;

        for (i = 0; i < 3; i++) {
            prim->tpage = 0xF;
            prim->clut = 0x41;
            prim->priority = 0x6A;
            prim->drawMode = DRAW_UNK02;
            //! FAKE:
            tilePos = prim->u2 = *var_a0++;
            prim->u0 = tilePos;

            prim->u1 = prim->u3 = *var_a0;
            prim->v0 = prim->v1 = 1;
            prim->v2 = prim->v3 = 0x81;
            prim = prim->next;
            var_a0++;
        }
        if (g_CastleFlags[CASTLE_FLAG_52] != 0) {
            self->ext.castleDoor.rotZ = 0;
            self->step = 5;
        }
        break;

    case 1:
        tilePos = 0x445;
        for (i = 0, tilePtr = D_80181120; i < 8; tilePtr++, i++) {
            g_Tilemap.fg[tilePos] = *tilePtr;
            tilePos += 0x20;
        }
        self->ext.castleDoor.rotZ = -0x380;
        self->ext.castleDoor.timer = 32;
        self->step = 4;
        g_CastleFlags[CASTLE_FLAG_52] = 1;
        break;

    case 2:
        self->ext.castleDoor.rotZ -= 8;
        if (self->ext.castleDoor.rotZ < -0x380) {
            self->ext.castleDoor.rotZ = -0x380;
            self->ext.castleDoor.timer = 128;
            self->step++;
        }
        break;

    case 3:
        if (--self->ext.castleDoor.timer == 0) {
            self->step++;
        }
        break;

    case 4:
        self->ext.castleDoor.rotZ += 0x10;
        if (self->ext.castleDoor.rotZ > 0) {
            self->ext.castleDoor.rotZ = 0;
            self->step += 2;
            g_api.PlaySfx(SFX_START_SLAM_B);
            tilePos = 0x445;
            for (i = 0, tilePtr = D_80181130; i < 8; tilePtr++, i++) {
                g_Tilemap.fg[tilePos] = *tilePtr;
                tilePos += 0x20;
            }
        }
        break;

    case 5:
        self->step++;
        tilePos = 0x445;
        for (i = 0, tilePtr = D_80181130; i < 8; tilePtr++, i++) {
            g_Tilemap.fg[tilePos] = *tilePtr;
            tilePos += 0x20;
        }
        break;
    }
    SetGeomScreen(768);
    SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
    sVec1.vx = 0;
    sVec1.vy = self->ext.castleDoor.rotZ;
    sVec1.vz = 0;
    RotMatrix(&sVec2, &mtx1);
    RotMatrixY(sVec1.vy, &mtx1);
    vec1.vx = 0;
    vec1.vy = 0;
    vec1.vz = 0x334;
    TransMatrix(&mtx1, &vec1);
    SetRotMatrix(&mtx1);
    SetTransMatrix(&mtx1);
    SetBackColor(128, 128, 128);
    cVec1.b = cVec1.g = cVec1.r = 128;
    cVec1.cd = 4;
    cVec2.b = cVec2.g = cVec2.r = 64;
    cVec2.cd = 4;
    RotMatrix(&sVec1, &mtx2);
    SetColorMatrix(&D_801810D4);
    SetLightMatrix(&mtx2);

    prim = self->ext.prim;
    var_s6 = &D_801810A4;
    var_s5 = &D_8018110C;
    for (i = 0; i < 3; var_s6++, var_s5++, i++) {
        temp_s3 = RotAverageNclip4(
            var_s6->v0, var_s6->v1, var_s6->v2, var_s6->v3, (long*)&prim->x0,
            (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &sxy2, &sxy3,
            &p);
        NormalColorCol(*var_s5, &cVec1, (CVECTOR*)&prim->r0);
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);

        if (i != 0) {
            NormalColorCol(*var_s5, &cVec2, (CVECTOR*)&prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
        }

        if (temp_s3 <= 0) {
            prim->drawMode = DRAW_HIDE;
        } else {
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
        }
        prim = prim->next;
    }
}

extern u16 D_80180B18[];
extern SVECTOR D_801811E8;
extern s16 D_801811A0;
extern s16* D_801811C0;
extern u8 D_80181140[];
extern u8 D_80181158[];

// bushes in parallax background
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
        InitializeEntity(D_80180B18);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x48);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }
    SetGeomScreen(0x400);
    SetGeomOffset(0x80, self->posY.i.hi);
    RotMatrix(&D_801811E8, &m);
    SetRotMatrix(&m);
    if (self->params) {
        trans.vx = self->posX.i.hi - 0x200;
    } else {
        trans.vx = self->posX.i.hi + 0x200;
    }
    trans.vy = 0;
    var_s5 = &D_801811A0;
    var_s8 = &D_801811C0;
    prim = self->ext.prim;
    for (i = 0; i < 4; i++, var_s8++, var_s5 += 4) {
        trans.vz = *var_s5 + 0x400;
        TransMatrix(&m, &trans);
        SetTransMatrix(&m);
        RotTransPers(&D_801811E8, &rotTransXYResult, &unused1, &unused2);
        // Split out the upper and lower halfword of rotTransXYResult
        xPos = rotTransXYResult & 0xFFFF;
        yPos = rotTransXYResult >> 16;
        xPos = xPos % var_s5[3];
        xPos -= var_s5[3];
        yPos = self->posY.i.hi;
        var_s4 = *var_s8;
        while (xPos < 0x140) {
            var_s1 = &D_80181140[0];
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
                var_s1 = &D_80181158[0];
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
        prim = prim->next;
    }
}

void EntityUnkId1C(Entity* self, s16 primIndex) {
    volatile char pad[8]; //! FAKE
    Primitive* prim;
    VECTOR vec;
    MATRIX mtx;
    long sxy;
    long p;
    long flag;
    s32 temp_s3;
    s32 temp_a1;
    s32 temp_a2;
    s32 var_v1;

    if (self->step == 0) {
        InitializeEntity(D_80180B18);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 32);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = D_801811E0[self->params % 16];
            prim->u0 = prim->u2 = 0xBF;
            prim->u1 = prim->u3 = 0xFF;
            prim->v0 = prim->v1 = 0x80;
            prim->v2 = prim->v3 = 0xB8;
            prim->priority = 0x5A;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }
    var_v1 = D_801811D0[self->params % 16][0];
    temp_s3 = var_v1;

    SetGeomScreen(0x400);
    if (self->params & 0x100) {
        SetGeomOffset(0x80, 0x98);
    } else {
        SetGeomOffset(0x80, 0x80);
    }

    RotMatrix(D_801811F0, &mtx);
    vec.vx = self->posX.i.hi - 128;
    vec.vy = self->posY.i.hi - 128;
    vec.vz = temp_s3 + 0x400;
    TransMatrix(&mtx, &vec);
    SetRotMatrix(&mtx);
    SetTransMatrix(&mtx);
    RotTransPers(D_801811F0, &sxy, &p, &flag);
    temp_a1 = sxy & 0xFFFF;
    temp_a2 = sxy >> 0x10;

    if (temp_a1 < 0) {
        var_v1 = temp_a1 + 0x3F;
    } else {
        var_v1 = temp_a1;
    }

    prim = self->ext.prim;
    temp_a1 -= (var_v1 >> 6) << 6;
    temp_a1 -= 64;
    temp_a1 -= D_801811D0[self->params % 16][1];
    while (temp_a1 < 320) {
        prim->x1 = prim->x3 = temp_a1 + 64;
        prim->x0 = prim->x2 = temp_a1;
        prim->y0 = prim->y1 = temp_a2 - 56;
        prim->y2 = prim->y3 = temp_a2;
        prim->drawMode = DRAW_UNK02;
        prim = prim->next;
        temp_a1 += 64;
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

// transparent water "plane" seen in the merman room
void EntityTransparentWater(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    u32 temp_a0;
    s16 temp_t1;
    s32 temp_v0;
    u8* temp_v1;
    u8* var_a0;
    u8 temp_t2;
    s32 var_a3;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->ext.transparentWater.unk80 = 4;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.transparentWater.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 0x18;
            prim->priority = 0xB0;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        break;

    case 1:
        var_a0 = &D_801811F8;
        while (*var_a0 != 0xFF) {
            g_ClutIds[var_a0[0]] = g_ClutIds[var_a0[2] + 0x200];
            var_a0 += 4;
        }

        if (--self->ext.transparentWater.unk80 == 0) {
            self->ext.transparentWater.unk80 = 4;
            self->step++;
        }
        break;

    case 2:
        var_a0 = &D_801811F8;
        while (*var_a0 != 0xFF) {
            g_ClutIds[var_a0[0]] = g_ClutIds[var_a0[3] + 0x200];
            var_a0 += 4;
        }

        if (--self->ext.transparentWater.unk80 == 0) {
            self->ext.transparentWater.unk80 = 4;
            self->step--;
        }
        break;
    }

    AnimateEntity(D_80181224, self);

    var_a3 = -1 * g_Tilemap.scrollX.i.hi % 38;
    var_a3 += 304;
    if (self->params != 0) {
        var_a3 = 96;
    }

    prim = self->ext.transparentWater.prim;
    temp_a0 = self->posY.i.hi;
    temp_v1 = D_80181218;
    temp_v1 += 4 * self->animCurFrame;
    temp_v0 = temp_v1[0];
    temp_v1 = temp_v1[1];
    while (var_a3 > 0) {
        temp_t2 = temp_v0 + 0x26;
        temp_t1 = temp_v1 + 0x3E;
        prim->x1 = prim->x3 = var_a3;
        var_a3 -= 0x26;
        prim->x0 = prim->x2 = var_a3;
        prim->u0 = prim->u2 = temp_v0;
        prim->u1 = prim->u3 = temp_t2;
        prim->v0 = prim->v1 = temp_v1;
        prim->v2 = prim->v3 = temp_t1;
        prim->y0 = prim->y1 = temp_a0;
        prim->y2 = prim->y3 = temp_a0 + 0x3E;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_801B94F0(Primitive* prim) {
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

// lever and platform to open caverns door
void EntityCavernDoorLever(Entity* entity) {
    s32 posX;
    s32 posY;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180B18);
        entity->animCurFrame = 18;
        entity->rotZ = -0x200;
        entity->drawFlags |= FLAG_DRAW_ROTZ;
        CreateEntityFromEntity(E_CAVERN_DOOR_LEVER_UNK0, entity, &entity[1]);
        if (g_CastleFlags[CASTLE_FLAG_48] != 0) {
            entity->rotZ = 0;
        }

    case 1:
        if (entity[1].ext.generic.unk84.S8.unk0 != 0) {
            entity->rotZ += 4;
            if (entity->rotZ > 0) {
                entity->rotZ = 0;
                if (g_CastleFlags[CASTLE_FLAG_48] == 0) {
                    g_api.PlaySfx(SFX_LEVER_METAL_BANG);
                }
                g_CastleFlags[CASTLE_FLAG_48] = 1;
            } else if (!(g_Timer & 0xF)) {
                g_api.PlaySfx(SFX_LEVER_METAL_BANG);
            }
        }
        break;
    }

    posX = entity->posX.val;
    posY = entity->posY.val;
    posX += rcos(entity->rotZ) * 0x280;
    posY += rsin(entity->rotZ) * 0x280;
    entity[1].posX.val = posX;
    entity[1].posY.val = posY;
}

// platform attached to lever at cavern door
void EntityCavernDoorPlatform(Entity* self) {
    Entity* player;
    s32 xDiff;
    s32 collision;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B18);
        self->animCurFrame = 17;
        self->ext.cavernDoor.xCoord.val = self->posX.val;
        self->ext.cavernDoor.xCoord.val = self->posX.val; // ? WTF

    case 1:
        collision = GetPlayerCollisionWith(self, 6, 5, 4);
        self->ext.cavernDoor.collision = collision;

        if (collision != 0) {
            xDiff = self->posX.i.hi - FIX_TO_I(self->ext.cavernDoor.xCoord.val);
            player = &PLAYER;
            player->posX.i.hi += xDiff;
            player->posY.i.hi += 1;
        }
        self->ext.cavernDoor.xCoord.val = self->posX.val;
        self->ext.cavernDoor.yCoord.val = self->posY.val;
    }
}

// door blocking way to the Underground Caverns
void EntityCavernDoor(Entity* self) {
    s32 primIndex;
    s16* tileLayoutPtr;
    Entity* entity;
    Primitive* prim;
    s32 i;
    s32 tilePos;
    s32 tileSteps;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B18);
        self->animCurFrame = 10;
        self->zPriority = 0x9F;

        tileLayoutPtr = &D_80181230[0];
        if (g_CastleFlags[CASTLE_FLAG_48]) {
            self->step = 128;
            self->animCurFrame = 0;
            tileLayoutPtr += 3;
        } else {
            primIndex = g_api.AllocPrimitives(PRIM_TILE, 64);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }
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
            }
        }

        for (tilePos = 0x76, i = 0; i < 3; i++) {
            g_Tilemap.fg[tilePos] = *tileLayoutPtr++;
            tilePos += 0x10;
        }
        break;

    case 1:
        if (g_CastleFlags[CASTLE_FLAG_48]) {
            g_api.PlaySfx(SFX_SWITCH_CLICK);
            self->step++;
        }
        break;

    case 2:
        self->posY.val += FIX(0.375);
        self->ext.cavernDoor.jiggler++;
        // While the door opens, it jiggles left and right by repeatedly
        // incrementing and decrementing its x position.
        if (self->ext.cavernDoor.jiggler & 1) {
            self->posX.i.hi++;
        } else {
            self->posX.i.hi--;
        }

        tileSteps = (self->posY.i.hi - 136);
        tileSteps /= 16;
        if (tileSteps > 3) {
            tileSteps = 3;
            self->step = 3;
        }
        tilePos = 0x76;
        tileLayoutPtr = &D_80181230[0];
        tileLayoutPtr += 3;
        for (i = 0; i < tileSteps; tilePos += 0x10, i++) {
            g_Tilemap.fg[tilePos] = *tileLayoutPtr++;
        }

        if (g_Timer & 1) {
            break;
        }
        prim = self->ext.cavernDoor.prim;
        prim = FindFirstUnkPrim(prim);
        if (prim != NULL) {
            prim->p3 = 1;
        }

        if (g_Timer & 15) {
            break;
        }
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity == NULL) {
            break;
        }
        CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
        entity->posY.i.hi = 156;
        entity->posX.i.hi += -8 + (Random() & 15);
        entity->zPriority = self->zPriority + 2;
        entity->params = 0x10;
        entity->drawFlags |= (FLAG_DRAW_ROTX + FLAG_DRAW_ROTY);
        entity->rotX = entity->rotY = 192;
        break;
    }

    if (self->flags & FLAG_HAS_PRIMS) {
        for (prim = self->ext.cavernDoor.prim; prim != NULL;
             prim = prim->next) {
            if (prim->p3) {
                func_801B94F0(prim);
            }
        }
    }
}

typedef enum { WEIGHT_SMALL, WEIGHT_TALL } WeightSelect;

void func_801B9C44(WeightSelect weight) {
    s32 posY = g_CurrentEntity->posY.i.hi;
    s32 posX = g_CurrentEntity->posX.i.hi;
    Primitive* prim;

    if (weight != WEIGHT_SMALL) {
        posY -= 64;
    } else {
        posY -= 16;
    }

    prim = *(s32*)&g_CurrentEntity->ext.generic.unk7C;

    while (posY > 0) {
        prim->y2 = prim->y3 = posY;
        prim->x0 = prim->x2 = posX - 8;
        prim->x1 = prim->x3 = posX + 8;
        posY -= 32;
        prim->y0 = prim->y1 = posY;
        prim->drawMode = DRAW_UNK02;
        prim = prim->next;
    }
    posY -= 32;

    while (prim != 0) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

// switch that clicks when you step on it
void EntityClickSwitch(Entity* entity) {
    s32 temp_a0 = GetPlayerCollisionWith(entity, 8, 4, 4);
    Entity* player = &PLAYER;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180B18);
        entity->animCurFrame = 9;
        entity->zPriority = 0x5E;
        if (g_CastleFlags[CASTLE_FLAG_49] != 0) {
            entity->step = 2;
            entity->posY.i.hi += 4;
        }
        break;

    case 1:
        if (temp_a0 != 0) {
            player->posY.i.hi++;
            entity->posY.val += FIX(0.75);
            if ((g_Tilemap.scrollY.i.hi + entity->posY.i.hi) > 160) {
                entity->posY.i.hi = 160 - g_Tilemap.scrollY.i.hi;
                g_api.PlaySfx(SFX_SWITCH_CLICK);
                g_CastleFlags[CASTLE_FLAG_49] = 1;
                entity->step++;
            }
        }
        break;
    }
}

// smaller weight blocking path near cube of zoe
void EntityPathBlockSmallWeight(Entity* self) {
    s16 primIndex;
    POLY_GT4* poly;
    s32 var_a1;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B18);
        self->animCurFrame = 8;
        self->zPriority = 0x5E;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        poly = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        *(s32*)&self->ext.generic.unk7C = poly;
        self->flags |= FLAG_HAS_PRIMS;

        while (poly != NULL) {
            poly->tpage = 0xF;
            poly->clut = 0x22;
            poly->u0 = poly->u2 = 224;
            poly->u1 = poly->u3 = 240;
            poly->v0 = poly->v1 = 84;
            poly->v2 = poly->v3 = 116;
            poly->pad2 = self->zPriority + 1;
            poly->pad3 = 8;
            poly = (POLY_GT4*)poly->tag;
        }

        if (g_CastleFlags[CASTLE_FLAG_49] != 0) {
            self->step = 3;
            self->posY.i.hi += 111;
        }
        break;

    case 1:
        if (g_CastleFlags[CASTLE_FLAG_49] != 0) {
            self->step++;
        }
        break;

    case 2:
        self->posY.val += FIX(0.5);
        if ((self->posY.i.hi + g_Tilemap.scrollY.i.hi) >= 175) {
            self->posY.i.hi = 175 - g_Tilemap.scrollY.i.hi;
            self->step++;
        }
        break;

    case 3:
        for (var_a1 = 0x179, i = 0; i < 2; var_a1 -= 0x20, i++) {
            g_Tilemap.fg[var_a1] = 0x4FA;
            g_Tilemap.fg[var_a1 + 1] = 0x4FA;
        }
        self->step++;
        break;
    }

    if (self->step < 3 && GetPlayerCollisionWith(self, 16, 16, 5) & 4) {
        Entity* player = &PLAYER;

        player->posY.i.hi++;
    }
    func_801B9C44(WEIGHT_SMALL);
}

// taller weight blocking path near cube of zoe
void EntityPathBlockTallWeight(Entity* self) {
    POLY_GT4* poly;
    s16 primIndex;
    s32 temp_a2;
    s32 var_a1;
    s32 var_v0;
    s32 temp;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B18);
        self->animCurFrame = 7;
        self->zPriority = 0x5E;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        poly = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        *(s32*)&self->ext.generic.unk7C = poly;
        self->flags |= FLAG_HAS_PRIMS;

        while (poly != NULL) {
            poly->tpage = 0xF;
            poly->clut = 0x22;
            poly->u0 = poly->u2 = 224;
            poly->u1 = poly->u3 = 240;
            poly->v0 = poly->v1 = 84;
            poly->v2 = poly->v3 = 116;
            poly->pad2 = self->zPriority + 1;
            poly->pad3 = 8;
            poly = (POLY_GT4*)poly->tag;
        }

        if (g_CastleFlags[CASTLE_FLAG_49] != 0) {
            self->step = 3;
            self->posY.i.hi -= 128;
        }
        break;

    case 1:
        if (g_CastleFlags[CASTLE_FLAG_49] != 0) {
            self->step++;
        }
        break;

    case 2:
        self->posY.val -= FIX(0.5);
        temp = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (temp <= -16) {
            self->posY.i.hi = -16 - g_Tilemap.scrollY.i.hi;
            self->step++;
        }
        break;
    }

    func_801B9C44(WEIGHT_TALL);
    do {
        temp = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    } while (0);
    var_v0 = 112 - temp;
    var_a1 = 0x157;

    if (var_v0 < 0) {
        var_v0 += 15;
    }

    for (temp_a2 = var_v0 >> 4, i = 0; i < temp_a2; var_a1 -= 0x20, i++) {
        g_Tilemap.fg[var_a1] = 0;
        g_Tilemap.fg[var_a1 + 1] = 0;
    }

    for (temp_a2 = 8 - temp_a2, i = 0; i < temp_a2; var_a1 -= 0x20, i++) {
        g_Tilemap.fg[var_a1] = 0x4FA;
        g_Tilemap.fg[var_a1 + 1] = 0x4FA;
    }
}

// trap door that leads to underground garden in saturn version.
// also opens the one leading to the save room
void EntityTrapDoor(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180B18);
        entity->animCurFrame = 27;
        entity->zPriority = 0x6A;
        entity->hitboxWidth = 16;
        entity->hitboxHeight = 4;
        entity->hitboxState = 1;

        if (g_TrapDoorFlag == 0) {
            if (PLAYER.posY.val < entity->posY.val) {
                g_Tilemap.fg[0xA8E / 2] = 0x129;
                g_Tilemap.fg[0xA90 / 2] = 0x132;
                DestroyEntity(entity);
                break;
            }
            g_Tilemap.fg[0xA8E / 2] = 0x6C8;
            g_Tilemap.fg[0xA90 / 2] = 0x6C9;
        } else {
            entity->animCurFrame = 30;
            g_Tilemap.fg[0xA8E / 2] = 0x6C8;
            g_Tilemap.fg[0xA90 / 2] = 0x6C9;
            entity->step = 128;
        }

    case 1:
        if (entity->hitFlags != 0) {
            g_TrapDoorFlag = 1;
            entity->step++;
        }
        break;

    case 2:
        AnimateEntity(D_80181240, entity);
    }
}

// left side of the breakable rock, drops pot roast
void EntityMermanRockLeftSide(Entity* self) {
    const int rockBroken = (1 << 0);
    const int wolfFlag = (1 << 2);
    u16* tileLayoutPtr;
    Entity* newEntity;
    s32 tilePos;
    u8* params;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxState = 2;
        self->hitboxWidth = 16;
        self->hitboxHeight = 24;

        tileLayoutPtr = &D_8018127C;
        tilePos = 0x1F1;
        for (i = 0; i < 3; i++) {
            g_BgLayers[0].layout[tilePos] = *tileLayoutPtr;
            g_BgLayers[0].layout[tilePos + 1] = *(tileLayoutPtr + 3);
            tileLayoutPtr++;
            tilePos += 0x30;
        }

        if (g_CastleFlags[JEWEL_SWORD_ROOM] & rockBroken) {
            tileLayoutPtr = &D_80181264;
            tilePos = 0x1F1;
            for (i = 0; i < 3; i++) {
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
                tileLayoutPtr++;
                tilePos += 0x30;
            }
            self->hitboxState = 1;
            self->step = 2;
        }
        break;

    case 1:
        if (self->hitFlags != 0) {
            tileLayoutPtr = &D_80181258[self->ext.generic.unk84.S16.unk0 * 6];
            tilePos = 0x1F1;
            for (i = 0; i < 3; i++) {
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
                tileLayoutPtr++;
                tilePos += 0x30;
            }

            g_api.PlaySfx(SFX_WALL_DEBRIS_B);

            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 0x13;
                newEntity->zPriority = 0xA9;
                newEntity->posX.i.hi += self->ext.generic.unk84.S16.unk0 * 16;
                newEntity->posY.i.hi += 16;
            }

            params = &D_80181344[self->ext.generic.unk84.S16.unk0 * 3];

            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_FALLING_ROCK_2, self, newEntity);
                    newEntity->params = *params++;
                    newEntity->velocityX = -0x8000 - (Random() << 8);
                    newEntity->velocityY = -Random() * 0x100;
                    newEntity->posY.i.hi += -16 + (i * 16);
                }
            }
            self->ext.generic.unk84.S16.unk0++;
        }

        if (self->ext.generic.unk84.S16.unk0 >= 2) {
            newEntity = AllocEntity(g_Entities + 160, g_Entities + 192);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EQUIP_ITEM_DROP, self, newEntity);
                newEntity->params = ITEM_POT_ROAST;
            }
            g_CastleFlags[JEWEL_SWORD_ROOM] |= rockBroken;
            self->hitboxState = 1;
            self->step++;
        }
        break;

    case 2:
        if ((self->hitFlags != 0) &&
            (g_Player.status & PLAYER_STATUS_WOLF_FORM)) {
            g_CastleFlags[JEWEL_SWORD_ROOM] |= wolfFlag;
        }
        break;
    }
}

// right side of the merman room rock, breaks when hit
void EntityMermanRockRightSide(Entity* self) {
    const int rockBroken = (1 << 1);
    const int batFlag = (1 << 3);
    u16* tileLayoutPtr;
    Entity* newEntity;
    s32 tilePos;
    u8* params;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxState = 2;
        self->hitboxWidth = 16;
        self->hitboxHeight = 24;

        tileLayoutPtr = &D_801812B8;
        tilePos = 0x1FD;
        for (i = 0; i < 3; i++) {
            g_BgLayers[0].layout[tilePos] = *tileLayoutPtr;
            g_BgLayers[0].layout[tilePos + 1] = *(tileLayoutPtr + 3);
            tileLayoutPtr++;
            tilePos += 0x30;
        }

        if (g_CastleFlags[JEWEL_SWORD_ROOM] & rockBroken) {
            tileLayoutPtr = &D_801812A0;
            tilePos = 0x1FD;
            for (i = 0; i < 3; i++) {
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
                tileLayoutPtr++;
                tilePos += 0x30;
            }
            self->hitboxState = 1;
            self->step = 2;
        }
        break;

    case 1:
        if (self->hitFlags != 0) {
            tileLayoutPtr = &D_80181294[(self->ext.generic.unk84.S16.unk0 * 6)];
            tilePos = 0x1FD;
            for (i = 0; i < 3; i++) {
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
                tileLayoutPtr++;
                tilePos += 0x30;
            }

            g_api.PlaySfx(SFX_WALL_DEBRIS_B);

            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 0x13;
                newEntity->zPriority = 0xA9;
                newEntity->posX.i.hi -= self->ext.generic.unk84.S16.unk0 * 16;
                newEntity->posY.i.hi += 16;
            }

            params = &D_80181344[self->ext.generic.unk84.S16.unk0 * 3];

            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_FALLING_ROCK_2, self, newEntity);
                    newEntity->params = *params++;
                    newEntity->velocityX = (Random() << 8) + 0x8000;
                    newEntity->velocityY = -Random() * 0x100;
                    newEntity->facingLeft = 1;
                    newEntity->posY.i.hi += -16 + (i * 16);
                }
            }
            self->ext.generic.unk84.S16.unk0++;
        }

        if (self->ext.generic.unk84.S16.unk0 >= 2) {
            g_CastleFlags[JEWEL_SWORD_ROOM] |= rockBroken;
            self->hitboxState = 1;
            self->step++;
        }
        break;

    case 2:
        if ((self->hitFlags != 0) &&
            (g_Player.status & PLAYER_STATUS_BAT_FORM)) {
            g_CastleFlags[JEWEL_SWORD_ROOM] |= batFlag;
        }
        break;
    }
}

void EntityUnkId26(Entity* self) {
    u16* tileLayoutPtr;
    s32 tileLayoutPos;
    s32 i;
    s32 j;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        if (g_CastleFlags[CASTLE_FLAG_58] != 0) {
            self->step = 2;
        }
        break;

    case 1:
        if ((g_CastleFlags[JEWEL_SWORD_ROOM] & 12) == 12) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step++;
        }
        break;

    case 2:
        for (tileLayoutPtr = &D_801812E2, i = 0; i < 3; i++) {
            tileLayoutPos = 0x420 + i;
            for (j = 0; j < 5; tileLayoutPos += 0x30, j++, tileLayoutPtr++) {
                g_Tilemap.fg[tileLayoutPos] = *tileLayoutPtr;
            }
        }

        for (tileLayoutPtr = &D_8018131E, i = 0; i < 3; i++) {
            tileLayoutPos = 0x420 + i;
            for (j = 0; j < 5; j++, tileLayoutPtr++) {
                g_BgLayers[0].layout[tileLayoutPos] = *tileLayoutPtr;
                tileLayoutPos += 0x30;
            }
        }

        g_CastleFlags[CASTLE_FLAG_58] |= 1;
        g_api.func_800F1FC4(0x3A);
        self->step++;
        break;
    }
}

// falling rock that breaks into dust
void EntityFallingRock2(Entity* self) {
    s32 animFrame = self->params & 0xF;
    Collider collider;
    Entity* newEntity;
    s32 temp_a0;
    s32 var_a1;
    s32 new_var2;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B18);
        self->animCurFrame = animFrame;
        self->animCurFrame += 31;
        self->zPriority = 0x9F;
        self->drawFlags |= FLAG_DRAW_ROTZ;
        break;

    case 1:
        MoveEntity();
        self->velocityY += FIX(0.25);
        self->rotZ -= 0x20;
        new_var2 = self->posY.i.hi;
        new_var2 += D_8018133C[animFrame];
        g_api.CheckCollision(self->posX.i.hi, new_var2, &collider, 0);

        if (collider.effects & EFFECT_SOLID) {
            if (self->velocityY > FIX(4.0)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != 0) {
                    CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                    newEntity->params = 0x11;
                    if (animFrame == 0) {
                        newEntity->params = 0x13;
                    }
                }
                DestroyEntity(self);
                return;
            }
            self->posY.i.hi = self->posY.i.hi + collider.unk18;
            temp_a0 = -self->velocityY;
            self->velocityY = -self->velocityY;
            if (temp_a0 < 0) {
                var_a1 = temp_a0 + 7;
            } else {
                var_a1 = temp_a0;
            }
            self->velocityY = temp_a0 - (var_a1 >> 3);
        }
        break;
    }
}

// ID 0x5C
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
        InitializeEntity(D_80180B18);
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

extern CVECTOR D_8018136C;
extern s16 D_80181370[];

// See also: UnkRecursivePrimFunc1. Strong overlap, but also some different
// logic.
Primitive* func_801BB548(
    SVECTOR* arg0, SVECTOR* arg1, SVECTOR* arg2, SVECTOR* arg3, Primitive* arg4,
    s32 arg5, Primitive* arg6, u8* arg7) {
    s32 i;
    Primitive* prim1;
    s32 vecIdx1;
    s32 vecIdx2;
    s32 vecIdx3;
    s32 vecIdx4;
    s16* vecIndices;
    SVECTOR* vectors;
    uvPair* uv_values;

    long unused;
    long interp;
    s32 rotTransResult;
    Primitive* nextArg6;

    if (arg6 == NULL) {
        return NULL;
    }
    prim1 = (Primitive*)arg7;
    arg7 += sizeof(Primitive);
    vectors = (SVECTOR*)arg7;
    arg7 += sizeof(SVECTOR) * 9;
    uv_values = (uvPair*)arg7;
    arg7 += sizeof(uvPair) * 10; // This is effectively arg7 = arg7->next, since
                                 // this covers the full size of arg7.

    vectors[0] = *arg0;
    vectors[2] = *arg1;
    vectors[6] = *arg2;
    vectors[8] = *arg3;

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
    D_8018136C.cd = arg4->type;
    vecIndices = &D_80181370[0];
    for (i = 0; i < 4; i++) {
        vecIdx1 = *vecIndices++;
        vecIdx2 = *vecIndices++;
        vecIdx3 = *vecIndices++;
        vecIdx4 = *vecIndices++;

        RotTransPers(&vectors[vecIdx1], (long*)&prim1->x0, &interp, &unused);
        DpqColor(&D_8018136C, interp, &prim1->r0);

        RotTransPers(&vectors[vecIdx2], (long*)&prim1->x1, &interp, &unused);
        DpqColor(&D_8018136C, interp, &prim1->r1);

        RotTransPers(&vectors[vecIdx3], (long*)&prim1->x2, &interp, &unused);
        DpqColor(&D_8018136C, interp, &prim1->r2);

        rotTransResult = RotTransPers(
            &vectors[vecIdx4], (long*)&prim1->x3, &interp, &unused);
        DpqColor(&D_8018136C, interp, &prim1->r3);

        *(uvPair*)&prim1->u0 = uv_values[vecIdx1];
        *(uvPair*)&prim1->u1 = uv_values[vecIdx2];
        *(uvPair*)&prim1->u2 = uv_values[vecIdx3];
        *(uvPair*)&prim1->u3 = uv_values[vecIdx4];
        if (arg5 == 1) {
            if (rotTransResult > 0) {
                nextArg6 = arg6->next;
                *arg6 = *prim1;
                arg6->next = nextArg6;
                arg6 = arg6->next;
                if (arg6 == NULL) {
                    return NULL;
                }
            }
        } else {
            arg6 = func_801BB548(
                &vectors[vecIdx1], &vectors[vecIdx2], &vectors[vecIdx3],
                &vectors[vecIdx4], prim1, arg5 - 1, arg6, arg7);
        }
    }
    return arg6;
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
        if (g_CastleFlags[CASTLE_FLAG_53]) {
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
    prim2 = func_801BB548(&D_8018134C, &D_80181354, &D_8018135C, &D_80181364,
                          prim, 3, prim2, 0x1F800000);
    prim->drawMode = DRAW_HIDE;
    while (prim2 != NULL) {
        prim2->drawMode = DRAW_HIDE;
        prim2 = prim2->next;
    }
}

void EntityLightningThunder(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180B18);
        self->zPriority = 0x2A;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        self->facingLeft = Random() & 1;
        g_api.PlaySfxVolPan(SFX_THUNDER_B, 0x40, (self->posX.i.hi >> 0x4) - 8);
    }
    if (AnimateEntity(D_80181390, self) == 0) {
        DestroyEntity(self);
    }
}

// When lightning strikes, we get a bright bolt, but it is against a cloud
// as a background. It's subtle and hard to see, but it's there.
void EntityLightningCloud(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180B18);
        self->zPriority = 0x29;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        // There are 3 shapes of cloud, this picks which one.
        self->animCurFrame = self->params + 0x22;
        self->posX.i.hi = D_8018139C[self->params << 1];
        self->posY.i.hi = D_8018139E[self->params << 1];
        self->ext.backgroundLightning.timer = 5;
    }

    if (--self->ext.backgroundLightning.timer == 0) {
        DestroyEntity(self);
    }
}

// switch that goes downwards when you stand on it
void EntitySwitch(Entity* entity) {
    s32 temp_a0 = GetPlayerCollisionWith(entity, 8, 4, 4);
    Entity* player = &PLAYER;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180B18);
        entity->animCurFrame = 9;
        entity->zPriority = 0x5E;
        if (g_CastleFlags[CASTLE_FLAG_50] != 0) {
            entity->step = 2;
            entity->posY.i.hi += 4;
        }
        break;

    case 1:
        if (temp_a0 != 0) {
            player->posY.i.hi++;
            entity->posY.val += FIX(0.25);
            if ((g_Tilemap.scrollY.i.hi + entity->posY.i.hi) > 193) {
                entity->posY.i.hi = 193 - g_Tilemap.scrollY.i.hi;
                g_CastleFlags[CASTLE_FLAG_50] = 1;
                g_api.PlaySfx(SFX_STONE_MOVE_B);
                entity->step++;
            }
        }
        break;
    }
}

// door preventing access to warp room / heart
void EntityHeartRoomGoldDoor(Entity* self) {
    s16 primIndex;
    Entity* newEntity;
    POLY_GT4* poly;
    s32 tilePos;
    s32 temp;
    s32 temp2;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B18);
        self->animCurFrame = 37;
        self->zPriority = 0x5E;

        if (g_CastleFlags[CASTLE_FLAG_50] != 0) {
            for (
                tilePos = 0x48, i = 7, self->step = 128, self->animCurFrame = 0;
                i >= 0; tilePos += 0x10, i--) {
                g_Tilemap.fg[tilePos] = 0;
            }
            break;
        }

        primIndex = g_api.AllocPrimitives(PRIM_TILE, 64);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        poly = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        *(s32*)&self->ext.generic.unk7C = poly;
        self->flags |= FLAG_HAS_PRIMS;
        while (poly != NULL) {
            poly->v0 = 1;
            poly->u0 = 1;
            poly->r0 = 64;
            poly->b0 = 128;
            poly->g0 = 96;
            poly->pad2 = self->zPriority + 0x18;
            poly->pad3 = 8;
            poly->p3 = 0;
            poly = (POLY_GT4*)poly->tag;
        }

        for (tilePos = 0x48, temp = 0x4FA, i = 7; i >= 0; tilePos += 0x10,
            i--) {
            g_Tilemap.fg[tilePos] = temp;
        }
        break;

    case 1:
        if (g_CastleFlags[CASTLE_FLAG_50] != 0) {
            g_api.PlaySfx(SFX_STONE_MOVE_A);
            self->step++;
        }
        break;

    case 2:
        self->posY.val += FIX(0.375);
        if (++self->ext.generic.unk80.modeS32 & 1) {
            self->posX.i.hi++;
        } else {
            self->posX.i.hi--;
        }

        temp = temp2 = self->posY.i.hi - 112;
        if (temp2 < 0) {
            temp2 = self->posY.i.hi - 97;
        }

        temp = temp2 >> 4;
        if (temp >= 9) {
            temp = 8;
            self->step = 3;
        }

        for (tilePos = 0x48, i = 0; i < temp; tilePos += 0x10, i++) {
            g_Tilemap.fg[tilePos] = 0;
        }

        if (!(g_Timer & 1)) {
            poly =
                FindFirstUnkPrim((POLY_GT4*)(*(s32*)&self->ext.generic.unk7C));
            if (poly != NULL) {
                poly->p3 = 1;
            }

            if (!(g_Timer & 0xF)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, newEntity);
                    newEntity->posY.i.hi = 188;
                    newEntity->posX.i.hi += -8 + (Random() & 0xF);
                    newEntity->params = 0x10;
                    newEntity->rotX = newEntity->rotY = 192;
                    newEntity->drawFlags |= FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
                }
            }
        }
        break;
    }

    if (self->flags & FLAG_HAS_PRIMS) {
        for (poly = *(s32*)&self->ext.generic.unk7C; poly != NULL;
             poly = (POLY_GT4*)poly->tag) {
            if (poly->p3 != 0) {
                func_801B94F0(poly);
            }
        }
    }
}

void EntityUnkId49(Entity* entity) {
    u16 temp;

    switch (entity->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        break;
    case 1:
        temp = g_Tilemap.fg[9];
        g_Tilemap.fg[6] = temp;
        temp = g_Tilemap.fg[10];
        g_Tilemap.fg[7] = temp;
        temp = g_Tilemap.fg[0x39];
        g_Tilemap.fg[0x36] = temp;
        temp = g_Tilemap.fg[0x3A];
        g_Tilemap.fg[0x37] = temp;
        temp = g_Tilemap.fg[0x69];
        g_Tilemap.fg[0x66] = temp;
        temp = g_Tilemap.fg[0x6A];
        g_Tilemap.fg[0x67] = temp;
        entity->step++;
        break;
    }
}
