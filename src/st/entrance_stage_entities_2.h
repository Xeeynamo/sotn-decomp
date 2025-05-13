// SPDX-License-Identifier: AGPL-3.0-or-later
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
        InitializeEntity(g_EInitStInteractable);
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
        InitializeEntity(g_EInitStInteractable);
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
        InitializeEntity(g_EInitStInteractable);
        self->animCurFrame = 18;
        self->rotZ = -0x200;
        self->drawFlags |= FLAG_DRAW_ROTZ;
        CreateEntityFromEntity(E_CAVERN_DOOR_PLATFORM, self, self + 1);
        if (g_CastleFlags[NO4_TO_NP3_SHORTCUT] != 0) {
            self->rotZ = 0;
        }

    case 1:
        if ((self + 1)->ext.cavernDoor.collision != 0) {
            self->rotZ += 4;
            if (self->rotZ > 0) {
                self->rotZ = 0;
                if (g_CastleFlags[NO4_TO_NP3_SHORTCUT] == 0) {
                    g_api.PlaySfx(SFX_LEVER_METAL_BANG);
                }
                g_CastleFlags[NO4_TO_NP3_SHORTCUT] = 1;
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
        InitializeEntity(g_EInitStInteractable);
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
        InitializeEntity(g_EInitStInteractable);
        self->animCurFrame = 10;
        self->zPriority = 0x9F;

        tileLayoutPtr = &cavernDoorTiles[0];
        if (g_CastleFlags[NO4_TO_NP3_SHORTCUT]) {
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
        if (g_CastleFlags[NO4_TO_NP3_SHORTCUT]) {
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
        InitializeEntity(g_EInitStInteractable);
        self->animCurFrame = 9;
        self->zPriority = 0x5E;
        if (g_CastleFlags[NO0_TO_NP3_SHORTCUT] != 0) {
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
                g_CastleFlags[NO0_TO_NP3_SHORTCUT] = 1;
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
        InitializeEntity(g_EInitStInteractable);
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
        if (g_CastleFlags[NO0_TO_NP3_SHORTCUT] != 0) {
            self->posY.i.hi += 111;
            self->step = 3;
        }
        break;

    case 1:
        if (g_CastleFlags[NO0_TO_NP3_SHORTCUT] != 0) {
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
        InitializeEntity(g_EInitStInteractable);
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

        if (g_CastleFlags[NO0_TO_NP3_SHORTCUT]) {
            self->posY.i.hi -= 128;
            self->step = 3;
        }
        break;

    case 1:
        if (g_CastleFlags[NO0_TO_NP3_SHORTCUT]) {
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
        InitializeEntity(g_EInitStInteractable);
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

        if (g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] & rockBroken) {
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
            g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] |= rockBroken;
            self->hitboxState = 1;
            self->step++;
        }
        break;

    case 2:
        if ((self->hitFlags != 0) &&
            (g_Player.status & PLAYER_STATUS_WOLF_FORM)) {
            g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] |= wolfFlag;
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

        if (g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] & rockBroken) {
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
            g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] |= rockBroken;
            self->hitboxState = 1;
            self->step++;
        }
        break;

    case 2:
        if ((self->hitFlags != 0) &&
            (g_Player.status & PLAYER_STATUS_BAT_FORM)) {
            g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] |= batFlag;
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
        if (g_CastleFlags[JEWEL_SWORD_ROOM_OPEN] != 0) {
            self->step = 2;
        }
        break;

    case 1:
        if ((g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] & 12) == 12) {
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

        g_CastleFlags[JEWEL_SWORD_ROOM_OPEN] |= 1;
        g_api.RevealSecretPassageAtPlayerPositionOnMap(JEWEL_SWORD_ROOM_OPEN);
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
        InitializeEntity(g_EInitStInteractable);
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
