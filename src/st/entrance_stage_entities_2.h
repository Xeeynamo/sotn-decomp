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
