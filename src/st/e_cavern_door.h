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
