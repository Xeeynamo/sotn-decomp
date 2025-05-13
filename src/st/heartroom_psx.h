void EntityHeartRoomSwitch(Entity* self) {
    s32 collision = GetPlayerCollisionWith(self, 8, 4, 4);
    s32 worldPos;
    Entity* player;
    
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitStInteractable);
        self->animCurFrame = 9;
        self->zPriority = 0x5E;
        if (g_CastleFlags[WRP_TO_NP3_SHORTCUT]) {
            self->posY.i.hi += 4;
            self->step = 2;
        }
        break;

    case 1:
        if (collision != 0) {
            player = &PLAYER;
            player->posY.i.hi++;
            self->posY.val += FIX(0.25);
            worldPos = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (worldPos > 193) {
                self->posY.i.hi = 193 - g_Tilemap.scrollY.i.hi;
                g_CastleFlags[WRP_TO_NP3_SHORTCUT] = 1;
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
        InitializeEntity(g_EInitStInteractable);
        self->animCurFrame = 37;
        self->zPriority = 0x5E;

        if (g_CastleFlags[WRP_TO_NP3_SHORTCUT]) {
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
        if (g_CastleFlags[WRP_TO_NP3_SHORTCUT]) {
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
