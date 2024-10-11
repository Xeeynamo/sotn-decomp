// SPDX-License-Identifier: AGPL-3.0-or-later

// Holds the entities which exist in the background on NO3 and NP3.
// No enemies here, those are elsewhere.
// The fact that we have these two stages that are so similar could be
// helpful for understanding the overall layouts of stages in the game.
// If enemies are always in their own area, that would be good to know.

void EntityUnkId16(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
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

#if defined(STAGE_IS_NO3)
static u8 D_80180EA0[] = {
    0x09, 0x04, 0x27, 0x28, 0x2A, 0x2C, 0x2F, 0x32, 0x36, 0x3F, 0x4A, 0x56,
    0x62, 0x6E, 0x7A, 0x00, 0x0C, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
    0x37, 0x40, 0x4B, 0x57, 0x63, 0x6F, 0x7B, 0x01, 0x0E, 0x05, 0x05, 0x05,
    0x05, 0x05, 0x05, 0x05, 0x38, 0x41, 0x4C, 0x58, 0x64, 0x70, 0x7C, 0x02,
    0x0F, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x39, 0x42, 0x4D, 0x59,
    0x65, 0x71, 0x7D, 0x03, 0x02, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12,
    0x3A, 0x43, 0x4E, 0x5A, 0x66, 0x72, 0x7E, 0x0A, 0x03, 0x12, 0x12, 0x12,
    0x12, 0x12, 0x12, 0x12, 0x12, 0x44, 0x4F, 0x5B, 0x67, 0x73, 0x7F, 0x0B,
    0x04, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x50, 0x5C,
    0x68, 0x74, 0x80, 0x0C, 0x0A, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12,
    0x12, 0x45, 0x51, 0x5D, 0x69, 0x75, 0x81, 0x0D, 0x0B, 0x12, 0x12, 0x12,
    0x12, 0x2E, 0x31, 0x34, 0x3C, 0x46, 0x52, 0x5E, 0x6A, 0x76, 0x82, 0x0E,
    0x10, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x35, 0x3D, 0x47, 0x53, 0x5F,
    0x6B, 0x77, 0x83, 0x0F, 0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12,
    0x3E, 0x48, 0x54, 0x60, 0x6C, 0x78, 0x84, 0x10, 0x12, 0x12, 0x12, 0x12,
    0x12, 0x12, 0x12, 0x12, 0x12, 0x49, 0x55, 0x61, 0x6D, 0x79, 0x85, 0x11};
#endif

static u8 lightningClutIndices[] = {
#if defined(STAGE_IS_NO3)
    0x09, 0x04, 0x07, 0x00, 0x0C, 0x05, 0x08, 0x01, 0x0E, 0x05, 0x08, 0x02,
    0x0F, 0x06, 0x09, 0x03, 0x02, 0x12, 0x12, 0x0A, 0x03, 0x12, 0x12, 0x0B,
    0x04, 0x12, 0x12, 0x0C, 0x0A, 0x12, 0x12, 0x0D, 0x0B, 0x12, 0x12, 0x0E,
    0x10, 0x12, 0x12, 0x0F, 0x11, 0x12, 0x12, 0x10, 0x12, 0x12, 0x12, 0x11,
#endif
    0x15, 0x17, 0x18, 0x17, 0x5C, 0x13, 0x14, 0x13, 0x5E, 0x15, 0x16, 0x15,
    0x17, 0x86, 0x87, 0x86, 0x49, 0x88, 0x89, 0x88, 0x14, 0x8A, 0x8B, 0x8A,
    0xFF, 0x00, 0x00, 0x00};

static u16 lightningAnim[] = {
    0x0104, 0x0002, 0x0102, 0x0002, 0x0102, 0x0002, 0x00FF, 0x0000};
#if defined(STAGE_IS_NO3)
static u16 D_80180FBC[] = {
    0x0108, 0x0208, 0x0308, 0x0408, 0x0508, 0x0608, 0x0708, 0x0808,
    0x0908, 0x0A08, 0x0B08, 0x0C08, 0x0D08, 0x0E08, 0x0F08, 0x00FF};
#endif
static u8 lightningThunderXY[][2] = {
    {0x88, 0x6C}, {0xC8, 0x30}, {0x30, 0x44}, {0x88, 0x6C}};

void EntityBackgroundLightning(Entity* self) {
    Entity* otherEnt;
    s32 animFrame;
    s32 randOf3;
    u8* clutIndices;
    s32 i;
#if defined(STAGE_IS_NO3)
    s32 clutDest;
    u8* var_s1;
    s32 playerRealX;
#endif

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->ext.backgroundLightning.timer = 0x80;
        self->animCurFrame = 15;
#if defined(STAGE_IS_NO3)
        var_s1 = &D_80180EA0[0];
        for (i = 0; i < 12; i++) {
            clutDest = var_s1[0];
            animFrame = 15;
            animFrame = var_s1[animFrame];
            g_ClutIds[clutDest] = g_ClutIds[animFrame + 0x200];
            var_s1 += 16;
        }
        if (self->params & 256) {
            self->step = 4;
            break;
        }
        if (g_CastleFlags[CASTLE_FLAG_55]) {
            self->params = 0;
        }
#else
        g_CastleFlags[CASTLE_FLAG_55] |= 1;
        if (self->params & FLAG_DEAD) {
            self->step = 4;
            break;
        }
#endif
    case 1:
        switch (self->step_s) {
#if !defined(STAGE_IS_NO3)
        default:
            break;
#endif
        case 0:
            otherEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (otherEnt != NULL) {
                CreateEntityFromCurrentEntity(E_LIGHTNING_THUNDER, otherEnt);
                randOf3 = Random() & 3;
                otherEnt->posX.i.hi = lightningThunderXY[randOf3][0];
                otherEnt->posY.i.hi = lightningThunderXY[randOf3][1];
            }
            otherEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (otherEnt != NULL) {
                CreateEntityFromCurrentEntity(E_LIGHTNING_CLOUD, otherEnt);
                if (randOf3 > 2) {
                    randOf3 = 0;
                }
                otherEnt->params = randOf3;
            }
            self->step_s++;
            /* fallthrough */
        case 1:
            if (AnimateEntity(lightningAnim, self) == 0) {
                self->ext.backgroundLightning.timer = (Random() & 0x7F) + 0x40;
                self->step_s++;
            }
            clutIndices = &lightningClutIndices[0];
#if defined(STAGE_IS_NO3)
            if (!self->params) {
                clutIndices += 0x30;
            }
#endif
            for (animFrame = self->animCurFrame; *clutIndices != 0xFF;
                 clutIndices += 4) {
                i = *clutIndices;
                g_ClutIds[i] = g_ClutIds[(clutIndices + animFrame)[1] + 0x200];
            }

            if (animFrame == 1) {
                g_GpuBuffers[0].draw.r0 = 0x30;
                g_GpuBuffers[0].draw.g0 = 0x30;
                g_GpuBuffers[0].draw.b0 = 0x48;
                g_GpuBuffers[1].draw.r0 = 0x30;
                g_GpuBuffers[1].draw.g0 = 0x30;
                g_GpuBuffers[1].draw.b0 = 0x48;
            } else { // Same as case 2 right below
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
            if (--self->ext.backgroundLightning.timer) {
                break;
            }
            SetSubStep(0);
            break;
        }
#if defined(STAGE_IS_NO3)
        if (self->params != 1) {
            break;
        }
        otherEnt = &PLAYER;
        playerRealX = g_Tilemap.scrollX.i.hi + otherEnt->posX.i.hi;
        if (playerRealX > 0x300) {
            g_CastleFlags[CASTLE_FLAG_55] = 1;
            SetStep(2);
        }
#endif
        break;
#if defined(STAGE_IS_NO3)
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
            animFrame = self->animCurFrame;
            animFrame = var_s1[animFrame];
            g_ClutIds[clutDest] = g_ClutIds[animFrame + 0x200];
            var_s1 += 16;
        }
        break;
#endif
    // careful, this is the outer switch!
    case 4:
        g_GpuBuffers[0].draw.r0 = 16;
        g_GpuBuffers[0].draw.g0 = 8;
        g_GpuBuffers[0].draw.b0 = 56;
        g_GpuBuffers[1].draw.r0 = 16;
        g_GpuBuffers[1].draw.g0 = 8;
        g_GpuBuffers[1].draw.b0 = 56;
    }
#if defined(STAGE_IS_NO3)
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
#endif
}

static SVECTOR window_vec1 = {0, -120, 0};
static SVECTOR window_vec2 = {25, -120, 0};
static SVECTOR window_vec3 = {0, 0, 0};
static SVECTOR window_vec4 = {25, 0, 0};

static SVECTOR window_vec5 = {0, -120, 0};
static SVECTOR window_vec6 = {-25, -120, 0};
static SVECTOR window_vec7 = {0, 0, 0};
static SVECTOR window_vec8 = {-25, 0, 0};

static SVEC4 windowVectors[2] = {
    {&window_vec1, &window_vec2, &window_vec3, &window_vec4},
    {&window_vec5, &window_vec6, &window_vec7, &window_vec8}};

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
<<<<<<< HEAD
        InitializeEntity(g_EInitParticle);
=======
        InitializeEntity(g_InitializeEntityData0);
>>>>>>> 4a2fd5bc (Dedupe closing window)
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
            PlaySfxPositional(NA_SE_EV_WINDOW_LATCH);
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

    svec4 = windowVectors;
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

static SVECTOR doorvec1 = {-8, -128, -48};
static SVECTOR doorvec2 = {8, -128, -48};
static SVECTOR doorvec3 = {-8, 0, -48};
static SVECTOR doorvec4 = {8, 0, -48};

static SVECTOR doorvec5 = {-8, -128, 4};
static SVECTOR doorvec6 = {-8, -128, -48};
static SVECTOR doorvec7 = {-8, 0, 4};
static SVECTOR doorvec8 = {-8, 0, -48};

static SVECTOR doorvec9 = {8, -128, -48};
static SVECTOR doorvec10 = {8, -128, 4};
static SVECTOR doorvec11 = {8, 0, -48};
static SVECTOR doorvec12 = {8, 0, 4};

static SVEC4 castleDoorVectors[3] = {
    {
        &doorvec1,
        &doorvec2,
        &doorvec3,
        &doorvec4,
    },
    {
        &doorvec5,
        &doorvec6,
        &doorvec7,
        &doorvec8,
    },
    {
        &doorvec9,
        &doorvec10,
        &doorvec11,
        &doorvec12,
    }};

static MATRIX castleDoorColorMatrix = {
    {{0x800, 0, 0x800}, {0x800, 0, 0x800}, {0x800, 0, 0x800}}};

static SVECTOR doorColNormVec1 = {0, 0, 0x1000};
static SVECTOR doorColNormVec2 = {0x1000, 0, 0};
static SVECTOR doorColNormVec3 = {-0x1000, 0, 0};

static SVECTOR* doorColorNormalVectors[] = {
    &doorColNormVec1, &doorColNormVec2, &doorColNormVec3};

static u8 castleDoorUCoords[] = {
    0x3A, 0x46, 0x01, 0x35, 0x35, 0x01, 0x00, 0x00};
static s16 castleDoorTilesOpen[] = {
    0x06D1, 0x06D2, 0x06D3, 0x06D4, 0x06D5, 0x06D6, 0x06D3, 0x06D4,
};
static s16 castleDoorTilesShut[] = {
    0x010F, 0x112, 0x114, 0x116, 0x118, 0x11A, 0x114, 0x116,
};

// main door to the castle that closes during intro
void EntityCastleDoor(Entity* self) {
    s32 selfX, selfY;
    long sxy2, p, sxy3;
    SVECTOR sVec1;
    VECTOR vec1;
    MATRIX mtx1, mtx2;
    CVECTOR cVec1, cVec2;
    SVECTOR sVec2;
    Primitive* prim;
    SVECTOR** var_s5;
    SVEC4* var_s6;
    s32 primIndex;
    s32 temp_s3;
    s32 tilePos;
    u8* uPtr;
    s32 i;

    sVec2 = g_CastleDoorVector;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.castleDoor.prim = prim;
        uPtr = castleDoorUCoords;
        for (i = 0; i < 3; i++) {
            prim->tpage = 0xF;
            prim->clut = 0x41;
            prim->priority = 0x6A;
            prim->drawMode = DRAW_UNK02;
            prim->u0 = prim->u2 = *uPtr++;
            prim->u1 = prim->u3 = *uPtr++;
            prim->v0 = prim->v1 = 1;
            prim->v2 = prim->v3 = 0x81;
            prim = prim->next;
        }
#if defined(STAGE_IS_NO3)
        if (g_CastleFlags[CASTLE_FLAG_52]) {
            self->ext.castleDoor.rotZ = 0;
            self->step = 5;
        }
#else
        self->ext.castleDoor.rotZ = 0;
        tilePos = 0x445;
        for (i = 0; i < 8; i++) {
            g_Tilemap.fg[tilePos] = castleDoorTilesShut[i];
            tilePos += 0x20;
        }
#endif
        break;
#if defined(STAGE_IS_NO3)
    case 1:
        tilePos = 0x445;
        for (i = 0; i < 8; tilePos += 0x20, i++) {
            g_Tilemap.fg[tilePos] = castleDoorTilesOpen[i];
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
        if (!--self->ext.castleDoor.timer) {
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
            for (i = 0; i < 8; tilePos += 0x20, i++) {
                g_Tilemap.fg[tilePos] = castleDoorTilesShut[i];
            }
        }
        break;

    case 5:
        self->step++;
        tilePos = 0x445;
        for (i = 0; i < 8; tilePos += 0x20, i++) {
            g_Tilemap.fg[tilePos] = castleDoorTilesShut[i];
        }
        break;
#endif
    }
    SetGeomScreen(0x300);
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    SetGeomOffset(selfX, selfY);
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
    cVec1.r = 128;
    cVec1.g = 128;
    cVec1.b = 128;
    cVec1.cd = 4;
    cVec2.r = 64;
    cVec2.g = 64;
    cVec2.b = 64;
    cVec2.cd = 4;
    RotMatrix(&sVec1, &mtx2);
    SetColorMatrix(&castleDoorColorMatrix);
    SetLightMatrix(&mtx2);

    prim = self->ext.castleDoor.prim;
    var_s6 = castleDoorVectors;
    var_s5 = doorColorNormalVectors;
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

#define UVWH(u, v, w, h) u, v, w, h

static u8 bush_uvwh[] = {
    UVWH(0x10, 0xC8, 0x20, 0x1F), UVWH(0x30, 0xC8, 0x20, 0x1F),
    UVWH(0x50, 0xD0, 0x20, 0x2F), UVWH(0xB8, 0xB8, 0x47, 0x47),
    UVWH(0xAE, 0xC9, 0x0A, 0x32), UVWH(0xAD, 0xC9, 0x0C, 0x28)};
// Seems to be used when continuing a bush from one of the above starts?
static u8 bush_uvwh_cont[] = {
    UVWH(0x80, 0x80, 0x38, 0x42), UVWH(0x80, 0x80, 0x2C, 0x34)};
// clang-format off
static s16 bush_unk_data[] = {0, 20, 0, 32, 1, 32, 0, 8, 2, 20, 1, 16, 0xFFFF, 0,
                           3, 63, 0xFFFF, 0,
                           4, 64, 4, 96, 0xFFFF, 0,
                           5, 80, 5, 96, 5, 32, 0xFFFF, 0};
// clang-format on
// VZ, Priority, Clut, and an X value. 4 such sets.
static s16 bush_render_data[] = {
    0x00C0, 0x005E, 0x0017, 0x0080, 0x0200, 0x005B, 0x0014, 0x003F,
    0x0140, 0x005D, 0x003C, 0x00A0, 0x01C0, 0x005C, 0x003C, 0x00D0};
static s16* bush_unk_starts[] = {&bush_unk_data[0], &bush_unk_data[14],
                                 &bush_unk_data[18], &bush_unk_data[24]};
static s16 backgroundTreePositions[][2] = {
    {0x200, 0}, {0x280, 12}, {0x300, 4}, {0x380, 16}};
static u16 backgroundTreeCluts[] = {0x15, 0x46, 0x47, 0x48};
static SVECTOR backgroundBushZeroVec = {0, 0, 0};
static SVECTOR backgroundTreeZeroVec = {0, 0, 0};

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
        InitializeEntity(g_EInitInteractable3);
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
    RotMatrix(&backgroundBushZeroVec, &m);
    SetRotMatrix(&m);
    if (self->params) {
        trans.vx = self->posX.i.hi - 0x200;
    } else {
        trans.vx = self->posX.i.hi + 0x200;
    }
    trans.vy = 0;
    var_s5 = bush_render_data;
    var_s8 = bush_unk_starts;
    prim = self->ext.prim;
    for (i = 0; i < 4; i++, var_s8++, var_s5 += 4) {
        trans.vz = var_s5[0] + 0x400;
        TransMatrix(&m, &trans);
        SetTransMatrix(&m);
        RotTransPers(
            &backgroundBushZeroVec, &rotTransXYResult, &unused1, &unused2);
        // Split out the upper and lower halfword of rotTransXYResult
        xPos = rotTransXYResult & 0xFFFF;
        yPos = rotTransXYResult >> 16;
        xPos = xPos % var_s5[3];
        xPos -= var_s5[3];
        yPos = self->posY.i.hi;
        var_s4 = *var_s8;
        while (xPos < 0x140) {
            var_s1 = &bush_uvwh[0];
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
            // Need to figure out what this means.
            if (i > 1) {
                yOffset = var_s1[3];
                var_s1 = &bush_uvwh_cont[0];
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

void EntityBackgroundTrees(Entity* self) {
    volatile char pad[8]; //! FAKE
    long sxy, p, flag;
    Primitive* prim;
    s32 primIndex;
    VECTOR vec;
    MATRIX mtx;
    s32 zVal;
    s32 posX;
    s32 posY;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable3);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 32);
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
            prim->clut = backgroundTreeCluts[self->params & 0xF];
            prim->u0 = prim->u2 = 0xBF;
            prim->u1 = prim->u3 = 0xFF;
            prim->v0 = prim->v1 = 0x80;
            prim->v2 = prim->v3 = 0xB8;
            prim->priority = 0x5A;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }
    zVal = backgroundTreePositions[self->params & 0xF][0];

    SetGeomScreen(0x400);
    if (self->params & 0x100) {
        SetGeomOffset(0x80, 0x98);
    } else {
        SetGeomOffset(0x80, 0x80);
    }

    RotMatrix(&backgroundTreeZeroVec, &mtx);
    vec.vx = self->posX.i.hi - 128;
    vec.vy = self->posY.i.hi - 128;
    vec.vz = zVal + 0x400;
    TransMatrix(&mtx, &vec);
    SetRotMatrix(&mtx);
    SetTransMatrix(&mtx);
    RotTransPers(&backgroundTreeZeroVec, &sxy, &p, &flag);
    posX = sxy & 0xFFFF;
    posY = sxy >> 0x10;

    posX %= 64;
    posX -= 64;
    posX -= backgroundTreePositions[self->params & 0xF][1];
    prim = self->ext.prim;
    while (posX < 320) {
        prim->x0 = prim->x2 = posX;
        prim->x1 = prim->x3 = posX + 64;
        prim->y0 = prim->y1 = posY - 56;
        prim->y2 = prim->y3 = posY;
        prim->drawMode = DRAW_UNK02;
        prim = prim->next;
        posX += 64;
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

static u8 transWaterCluts[] = {
    0x24, 0x1A, 0x21, 0x1A, 0x2B, 0x1B, 0x22, 0x1B, 0x2C, 0x1C, 0x23,
    0x1C, 0x2D, 0x1D, 0x24, 0x1D, 0x2E, 0x1E, 0x25, 0x1E, 0x2F, 0x1F,
    0x26, 0x1F, 0x56, 0x20, 0x21, 0x20, 0xFF, 0x00, 0x00, 0x00};
static u8 transWaterUV[] = {
    UVWH(0xA1, 0x01, 0x26, 0x3E), UVWH(0xC9, 0x01, 0x26, 0x3E),
    UVWH(0xA1, 0x41, 0x26, 0x3E)};
static u8 transWaterAnim[] = {10, 0, 10, 1, 10, 2, 10, 1, 0, 0, 0, 0};
// Transparent water plane that can be seen in the merman room
void EntityTransparentWater(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    u32 selfY;
    s32 uCoord;
    s32 vCoord;
    u8* uvPtr;
    u8* clutIdx;
    s32 prim_xPos;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->ext.transparentWater.unk80 = 4;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.transparentWater.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 0x18;
            prim->priority = 0xB0;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        break;

    case 1:
        clutIdx = &transWaterCluts[0];
        while (*clutIdx != 0xFF) {
            g_ClutIds[clutIdx[0]] = g_ClutIds[clutIdx[2] + 0x200];
            clutIdx += 4;
        }

        if (!--self->ext.transparentWater.unk80) {
            self->ext.transparentWater.unk80 = 4;
            self->step++;
        }
        break;

    case 2:
        clutIdx = &transWaterCluts[0];
        while (*clutIdx != 0xFF) {
            g_ClutIds[clutIdx[0]] = g_ClutIds[clutIdx[3] + 0x200];
            clutIdx += 4;
        }

        if (!--self->ext.transparentWater.unk80) {
            self->ext.transparentWater.unk80 = 4;
            self->step--;
        }
        break;
    }

    AnimateEntity(transWaterAnim, self);

    prim_xPos = -1 * g_Tilemap.scrollX.i.hi % 38;
    prim_xPos += 304;
    if (self->params) {
        prim_xPos = 96;
    }

    uvPtr = transWaterUV;
    uvPtr += 4 * self->animCurFrame;
    uCoord = uvPtr[0];
    vCoord = uvPtr[1];
    selfY = self->posY.i.hi;
    prim = self->ext.transparentWater.prim;
    while (prim_xPos > 0) {
        prim->u0 = prim->u2 = uCoord;
        prim->u1 = prim->u3 = uCoord + 0x26;
        prim->v0 = prim->v1 = vCoord;
        prim->v2 = prim->v3 = vCoord + 0x3E;
        prim->x1 = prim->x3 = prim_xPos;
        prim_xPos -= 0x26;
        prim->x0 = prim->x2 = prim_xPos;
        prim->y0 = prim->y1 = selfY;
        prim->y2 = prim->y3 = selfY + 0x3E;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

// When cavern door or heart door are opened, a cascade
// of single blue pixels flies out of the door as it slides down.
// This function manages the physics for those pixel-prims.
void DoorCascadePhysics(EntranceCascadePrim* prim) {
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
            prim->velocityX.val = Random() * 0x40;
        } else {
            prim->velocityX.val = -Random() * 0x40;
        }
        prim->velocityY.val = (Random() << 8) + FIX(-4);
        prim->drawMode = DRAW_UNK02;
        prim->p3++;
        /* fallthrough */
    case 2:
        xVar = (prim->x0 << 0x10) + (u16)prim->x1;
        yVar = (prim->y0 << 0x10) + (u16)prim->y1;
        xVar += prim->velocityX.val;
        yVar += prim->velocityY.val;
        prim->x0 = (xVar >> 0x10);
        prim->x1 = xVar & 0xFFFF;
        prim->y0 = (yVar >> 0x10);
        prim->y1 = yVar & 0xFFFF;

        prim->velocityY.val += FIX(1.0 / 4.0);
        if (prim->velocityY.val <= FIX(6)) {
            return;
        }
        prim->p3++;
        break;
    case 3:
        prim->drawMode = DRAW_HIDE;
        prim->p3 = 0;
        break;
    }
}

// lever and platform to open caverns door
void EntityCavernDoorLever(Entity* self) {
    s32 posX;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable3);
        self->animCurFrame = 18;
        self->rotZ = -0x200;
        self->drawFlags |= FLAG_DRAW_ROTZ;
        CreateEntityFromEntity(E_CAVERN_DOOR_PLATFORM, self, self + 1);
        if (g_CastleFlags[CASTLE_FLAG_48] != 0) {
            self->rotZ = 0;
        }

    case 1:
        if ((self + 1)->ext.cavernDoor.collision != 0) {
            self->rotZ += 4;
            if (self->rotZ > 0) {
                self->rotZ = 0;
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

    posX = self->posX.val;
    posY = self->posY.val;
    posX += rcos(self->rotZ) * 0x280;
    posY += rsin(self->rotZ) * 0x280;
    (self + 1)->posX.val = posX;
    (self + 1)->posY.val = posY;
}

// platform attached to lever at cavern door
void EntityCavernDoorPlatform(Entity* self) {
    Entity* player;
    s32 xDiff;
    s32 collision;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable3);
        self->animCurFrame = 17;
        self->ext.cavernDoor.xCoord.val = self->posX.val;
        self->ext.cavernDoor.xCoord.val = self->posX.val; // ? WTF

    case 1:
        collision = GetPlayerCollisionWith(self, 6, 5, 4);
        self->ext.cavernDoor.collision = collision;

        if (collision != 0) {
            xDiff = self->posX.i.hi - self->ext.cavernDoor.xCoord.i.hi;
            player = &PLAYER;
            player->posX.i.hi += xDiff;
            player->posY.i.hi += 1;
// Need to identify this var, and see why it's in NP3 but not NO3
#if !defined(STAGE_IS_NO3)
            D_80097488.x.i.hi += xDiff;
            D_80097488.y.i.hi += 1;
#endif
        }
        self->ext.cavernDoor.xCoord.val = self->posX.val;
        self->ext.cavernDoor.yCoord.val = self->posY.val;
    }
}

static u16 cavernDoorTiles[] = {0x6D0, 0x04FA, 0x04FA, 0x0551, 0, 0};

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
        InitializeEntity(g_EInitInteractable3);
        self->animCurFrame = 10;
        self->zPriority = 0x9F;

        tileLayoutPtr = &cavernDoorTiles[0];
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
#if defined(STAGE_IS_NO3)
            g_api.PlaySfx(SFX_SWITCH_CLICK);
#endif
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
#if !defined(STAGE_IS_NO3)
        if (!(self->ext.cavernDoor.jiggler & 15)) {
            g_api.PlaySfx(SFX_STONE_MOVE_C);
        }
#endif
        tilePos = 0x76;
        tileLayoutPtr = &cavernDoorTiles[0];
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
                DoorCascadePhysics(prim);
            }
        }
    }
}

typedef enum { WEIGHT_SMALL, WEIGHT_TALL } WeightSelect;

// To the right of Cube of Zoe is the weight system.
// The two weights hang from chains. The chains are prims
// that are 32 px in height. This function places them
// all at the right locations to stack up above the weight.
void UpdateWeightChains(WeightSelect weight) {
    s32 posY = g_CurrentEntity->posY.i.hi;
    s32 posX = g_CurrentEntity->posX.i.hi;
    Primitive* prim;

    if (weight != WEIGHT_SMALL) {
        posY -= 64;
    } else {
        posY -= 16;
    }

    prim = g_CurrentEntity->ext.prim;

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

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

// switch to lower the weights to the right of Cube of Zoe
void EntityWeightsSwitch(Entity* self) {
    s32 collision = GetPlayerCollisionWith(self, 8, 4, 4);
    Entity* player = &PLAYER;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable3);
        self->animCurFrame = 9;
        self->zPriority = 0x5E;
        if (g_CastleFlags[CASTLE_FLAG_49] != 0) {
            self->step = 2;
            self->posY.i.hi += 4;
        }
        break;

    case 1:
        if (collision) {
            player->posY.i.hi++;
            self->posY.val += FIX(0.75);
            if ((g_Tilemap.scrollY.i.hi + self->posY.i.hi) > 160) {
                self->posY.i.hi = 160 - g_Tilemap.scrollY.i.hi;
                g_api.PlaySfx(SFX_SWITCH_CLICK);
                g_CastleFlags[CASTLE_FLAG_49] = 1;
                self->step++;
            }
        }
        break;
    }
}

// smaller weight blocking path near cube of zoe
void EntityPathBlockSmallWeight(Entity* self) {
    s16 primIndex;
    Primitive* prim;
    s32 var_a1;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable3);
        self->animCurFrame = 8;
        self->zPriority = 0x5E;
        // All the prims below here are for the chain.
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
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
            prim->clut = 0x22;
            prim->u0 = prim->u2 = 0xE0;
            prim->u1 = prim->u3 = 0xE0 + 0x10;
            prim->v0 = prim->v1 = 0x54;
            prim->v2 = prim->v3 = 0x54 + 0x20;
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
#if !defined(STAGE_IS_NO3)
        self->posX.i.hi = 416 - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = 64 - g_Tilemap.scrollY.i.hi;
#endif
        if (g_CastleFlags[CASTLE_FLAG_49] != 0) {
            self->posY.i.hi += 111;
            self->step = 3;
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
#if !defined(STAGE_IS_NO3)
            PlaySfxPositional(SFX_START_SLAM_B);
#endif
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
    UpdateWeightChains(WEIGHT_SMALL);
}

// taller weight blocking path near cube of zoe
void EntityPathBlockTallWeight(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 steps_covered;
    s32 tilemap_idx;
    s32 yPos;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable3);
        self->animCurFrame = 7;
        self->zPriority = 0x5E;

        // All the prims below here are for the chain.
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
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
            prim->clut = 0x22;
            prim->u0 = prim->u2 = 0xE0;
            prim->u1 = prim->u3 = 0xE0 + 0x10;
            prim->v0 = prim->v1 = 0x54;
            prim->v2 = prim->v3 = 0x54 + 0x20;
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        if (g_CastleFlags[CASTLE_FLAG_49]) {
            self->posY.i.hi -= 128;
            self->step = 3;
        }
        break;

    case 1:
        if (g_CastleFlags[CASTLE_FLAG_49]) {
            self->step++;
        }
        break;

    case 2:
        self->posY.val -= FIX(0.5);
        yPos = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (yPos <= -16) {
            self->posY.i.hi = -16 - g_Tilemap.scrollY.i.hi;
            self->step++;
        }
        break;
    }

    UpdateWeightChains(WEIGHT_TALL);
    yPos = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    yPos = 112 - yPos;
    steps_covered = yPos / 16;

    for (tilemap_idx = 0x20 * 10 + 0x17, i = 0; i < steps_covered;
         tilemap_idx -= 0x20, i++) {
        g_Tilemap.fg[tilemap_idx] = 0;
        // This should be g_Tilemap.fg[tilemap_idx + 1] but psp fails
        *(&g_Tilemap.fg[tilemap_idx] + 1) = 0;
    }

    for (steps_covered = 8 - steps_covered, i = 0; i < steps_covered;
         tilemap_idx -= 0x20, i++) {
        g_Tilemap.fg[tilemap_idx] = 0x4FA;
        *(&g_Tilemap.fg[tilemap_idx] + 1) = 0x4FA;
    }
}

static s32 g_TrapDoorFlag = 0; // 0 = Closed, 1 = Open

static u8 trapdoor_anim[] = {
    1,   27, 6,   28, 6,   29, 129, 30, 255, 0, 0,   0,
    108, 2,  115, 2,  122, 2,  109, 2,  116, 2, 123, 2};

// trap door that leads to underground garden in saturn version.
// also opens the one leading to the save room
void EntityTrapDoor(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(g_EInitInteractable3);
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
        AnimateEntity(trapdoor_anim, entity);
        break;
    }
}

static u16 leftRockTiles[][6] = {
    {0x06B2, 0x0000, 0x06C5, 0x06B3, 0x06D9, 0x06DA},
    {0x06B2, 0x0000, 0x06C5, 0x06B3, 0x06B4, 0x06B5},
    {0x0332, 0x033A, 0x0351, 0x0000, 0x0000, 0x0000}};

static u16 leftRockInitTiles[][6] = {
    {0x0332, 0x033A, 0x0351, 0x0350, 0x032F, 0x034E},
    {0x02A7, 0x0287, 0x02B4, 0x02A8, 0x02AE, 0x02B5}};
static u16 rightRockTiles[][6] = {
    {0x06DB, 0x06DC, 0x06DD, 0x06B7, 0x0000, 0x06C6},
    {0x06B6, 0x06B8, 0x06B9, 0x06B7, 0x0000, 0x06C6},
    {0x0000, 0x0000, 0x0000, 0x0350, 0x032F, 0x034E}};
// Accesses and offsets are weird, so I'm just making this a big chunk of data.
// This feels like 3 arrays, but if I split them up, they get zero-padded to
// align 4.
static u16 remainingRockTiles[] = {
    0x0332, 0x033A, 0x0351, 0x0350, 0x032F, 0x034E, 0x02D2, 0x02D2, 0x02D2,
    0x02D2, 0x02D2, 0x02D2, 0x02D2, 0x02D2, 0x02D2, 0x02D2, 0x02D6, 0x02D4,
    0x02D6, 0x02D8, 0x02D7,
    // Offset 21 gets used later
    0x06BA, 0x0000, 0x0000, 0x06BD, 0x06BF, 0x06BB, 0x0000, 0x0000, 0x06BE,
    0x06C0, 0x06BC, 0x0000, 0x0000, 0x06BD, 0x06C1, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0350, 0x0000,
    0x034E, 0x0339, 0x0000,
    // Offset 51 is here.
    0x034E, 0x0339, 0x0350, 0x032F, 0x0000, 0x034F, 0x033A, 0x0351, 0x0330,
    0x0000, 0x0350, 0x032F, 0x034E, 0x0339, 0x0000};
static u16 rockYOffsets[] = {12, 6, 7, 0};

static u8 newRockParams[] = {1, 2, 1, 2, 1};

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

        tileLayoutPtr = &leftRockInitTiles;
        tilePos = 0x1F1;
        for (i = 0; i < 3; i++) {
            g_BgLayers[0].layout[tilePos] = *tileLayoutPtr;
            g_BgLayers[0].layout[tilePos + 1] = *(tileLayoutPtr + 3);
            tileLayoutPtr++;
            tilePos += 0x30;
        }

        if (g_CastleFlags[JEWEL_SWORD_ROOM] & rockBroken) {
            tileLayoutPtr = &leftRockTiles[1];
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
            tileLayoutPtr = &leftRockTiles[self->ext.mermanRock.unk84];
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
                newEntity->posX.i.hi += self->ext.mermanRock.unk84 * 16;
                newEntity->posY.i.hi += 16;
            }

            params = &newRockParams[self->ext.mermanRock.unk84 * 3];

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
            self->ext.mermanRock.unk84++;
        }

        if (self->ext.mermanRock.unk84 >= 2) {
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

        tileLayoutPtr = &remainingRockTiles[0];
        tilePos = 0x1FD;
        for (i = 0; i < 3; i++) {
            g_BgLayers[0].layout[tilePos] = *tileLayoutPtr;
            g_BgLayers[0].layout[tilePos + 1] = *(tileLayoutPtr + 3);
            tileLayoutPtr++;
            tilePos += 0x30;
        }

        if (g_CastleFlags[JEWEL_SWORD_ROOM] & rockBroken) {
            tileLayoutPtr = &rightRockTiles[1];
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
            tileLayoutPtr = &rightRockTiles[self->ext.mermanRock.unk84];
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
                newEntity->posX.i.hi -= self->ext.mermanRock.unk84 * 16;
                newEntity->posY.i.hi += 16;
            }

            params = &newRockParams[self->ext.mermanRock.unk84 * 3];

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
            self->ext.mermanRock.unk84++;
        }

        if (self->ext.mermanRock.unk84 >= 2) {
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

void EntityJewelSwordDoor(Entity* self) {
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
        for (tileLayoutPtr = &remainingRockTiles[21], i = 0; i < 3; i++) {
            tileLayoutPos = 0x420 + i;
            for (j = 0; j < 5; tileLayoutPos += 0x30, j++, tileLayoutPtr++) {
                g_Tilemap.fg[tileLayoutPos] = *tileLayoutPtr;
            }
        }

        for (tileLayoutPtr = &remainingRockTiles[51], i = 0; i < 3; i++) {
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
    s32 collX;
    s32 collY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable3);
        self->animCurFrame = animFrame + 31;
        self->drawFlags |= FLAG_DRAW_ROTZ;
        self->zPriority = 0x9F;
        break;

    case 1:
        MoveEntity();
        self->velocityY += FIX(0.25);
        self->rotZ -= 0x20;
        collX = self->posX.i.hi;
        collY = self->posY.i.hi;
        collY += rockYOffsets[animFrame];
        g_api.CheckCollision(collX, collY, &collider, 0);

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
            self->posY.i.hi += collider.unk18;
            // Seems to be a bounce effect. Reverse velocity, and lose 1/8 of
            // it.
            self->velocityY = -self->velocityY;
            self->velocityY -= self->velocityY / 8;
        }
        break;
    }
}

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
        InitializeEntity(g_EInitInteractable3);
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
        InitializeEntity(g_EInitInteractable3);
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
        InitializeEntity(g_EInitInteractable3);
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

void EntityHeartRoomSwitch(Entity* self) {
    s32 collision = GetPlayerCollisionWith(self, 8, 4, 4);
    Entity* player = &PLAYER;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable3);
        self->animCurFrame = 9;
        self->zPriority = 0x5E;
        if (g_CastleFlags[CASTLE_FLAG_50]) {
            self->step = 2;
            self->posY.i.hi += 4;
        }
        break;

    case 1:
        if (collision != 0) {
            player->posY.i.hi++;
            self->posY.val += FIX(0.25);
            if ((g_Tilemap.scrollY.i.hi + self->posY.i.hi) > 193) {
                self->posY.i.hi = 193 - g_Tilemap.scrollY.i.hi;
                g_CastleFlags[CASTLE_FLAG_50] = 1;
#if defined(STAGE_IS_NO3)
                g_api.PlaySfx(SFX_STONE_MOVE_B);
#else
                g_api.PlaySfx(SFX_SWITCH_CLICK);
#endif
                self->step++;
            }
        }
        break;
    }
}

// door preventing access to warp room / heart
void EntityHeartRoomGoldDoor(Entity* self) {
    Entity* newEntity;
    Primitive* prim;
    s32 primIndex;
    s32 yPos;
    s32 i;
    s32 tilePos;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable3);
        self->animCurFrame = 37;
        self->zPriority = 0x5E;

        if (g_CastleFlags[CASTLE_FLAG_50]) {
            self->step = 128;
            self->animCurFrame = 0;
            for (tilePos = 0x48, i = 0; i < 8; tilePos += 0x10, i++) {
                g_Tilemap.fg[tilePos] = 0;
            }
            break;
        }

        primIndex = g_api.AllocPrimitives(PRIM_TILE, 64);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.heartRoomGoldDoor.prim = prim;
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

        for (tilePos = 0x48, i = 0; i < 8; tilePos += 0x10, i++) {
            g_Tilemap.fg[tilePos] = 0x4FA;
        }
        break;

    case 1:
        if (g_CastleFlags[CASTLE_FLAG_50]) {
            g_api.PlaySfx(SFX_STONE_MOVE_A);
            self->step++;
        }
        break;

    case 2:
        self->posY.val += FIX(0.375);
        self->ext.heartRoomGoldDoor.timer++;
        if (self->ext.heartRoomGoldDoor.timer & 1) {
            self->posX.i.hi++;
        } else {
            self->posX.i.hi--;
        }
#if !defined(STAGE_IS_NO3)
        if ((self->ext.heartRoomGoldDoor.timer & 0xF) == 0) {
            g_api.PlaySfx(SFX_STONE_MOVE_A);
        }
#endif

        yPos = self->posY.i.hi - 112;
        yPos = yPos / 16;
        // Door is fully opened now.
        if (yPos > 8) {
            yPos = 8;
            self->step = 3;
        }

        for (tilePos = 0x48, i = 0; i < yPos; tilePos += 0x10, i++) {
            g_Tilemap.fg[tilePos] = 0;
        }

        if (!(g_Timer & 1)) {
            prim = self->ext.heartRoomGoldDoor.prim;
            prim = FindFirstUnkPrim(prim);
            if (prim != NULL) {
                prim->p3 = 1;
            }
            if (!(g_Timer & 0xF)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, newEntity);
                    newEntity->posY.i.hi = 188;
                    newEntity->posX.i.hi += -8 + (Random() & 15);
                    newEntity->params = 0x10;
                    newEntity->drawFlags |= FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
                    newEntity->rotX = newEntity->rotY = 192;
                }
            }
        }
        break;
    }

    if (self->flags & FLAG_HAS_PRIMS) {
        prim = self->ext.heartRoomGoldDoor.prim;
        while (prim != NULL) {
            if (prim->p3) {
                DoorCascadePhysics(prim);
            }
            prim = prim->next;
        }
    }
}

// Appears totally unused. Never created by any entity creation call,
// doesn't show up in the e_layout either.
void EntityTilemapShufflerUnused(Entity* self) {
    u16 temp;

    switch (self->step) {
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
        self->step++;
        break;
    }
}
