// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"
#include "sfx.h"

// pushes alucard to the right
void EntityPushAlucard(Entity* entity) {
    Entity* player = &PLAYER;
    Tilemap* tilemap = &g_Tilemap;

    switch (entity->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        g_Entities[UNK_ENTITY_1].ext.alucardController.unk7C = true;
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 255;
        player->posX.i.hi = 0;
        g_unkGraphicsStruct.unkC = 0;
        player->animCurFrame = 0;
        g_PauseAllowed = false;
        break;

    case 1:
        player->posX.val += FIX(6);
        if (tilemap->scrollX.i.hi > 0x800) {
            g_Entities[UNK_ENTITY_1].ext.alucardController.unk7C = false;
            g_Player.padSim = PAD_RIGHT;
            entity->step++;
        }
        player->animCurFrame = 0;
        g_Player.D_80072EFC = 1;
        g_api.func_8010E0A8();
        break;

    case 2:
        player->posX.val += FIX(8.5);
        g_unkGraphicsStruct.unkC += 4;
        if (g_unkGraphicsStruct.unkC == 192) {
            entity->ext.alucardController.unk80 = FIX(4.5);
            entity->step++;
        }
        g_Player.D_80072EFC = 1;
        g_api.func_8010E0A8();
        break;

    case 3:
        if (g_unkGraphicsStruct.unkC > 128) {
            g_unkGraphicsStruct.unkC -= 1;
            entity->ext.alucardController.unk80 = FIX(3.5);
        } else {
            entity->ext.alucardController.unk80 = FIX(4.5);
        }
        player->posX.val += entity->ext.alucardController.unk80;
        if (entity->ext.alucardController.unk80 == FIX(4.5)) {
            entity->step++;
        }
        g_Player.D_80072EFC = 1;
        g_api.func_8010E0A8();
        break;

    case 4:
        player->posX.val += FIX(4.5);
        if (tilemap->scrollX.i.hi > 0xF80) {
            g_api.PlaySfx(SFX_VO_ALU_ATTACK_B);
            g_Player.padSim = PAD_RIGHT | PAD_CROSS;
            entity->ext.alucardController.unk7C = false;
            entity->step++;
        }
        g_Player.D_80072EFC = 1;
        g_api.func_8010E0A8();
        break;

    case 5:
        if ((player->velocityY > 0) &&
            (entity->ext.alucardController.unk7C == false)) {
            g_Player.padSim = PAD_CROSS;
            entity->ext.alucardController.unk7C = true;
        } else {
            g_Player.padSim = PAD_RIGHT | PAD_CROSS;
        }
        g_api.func_8010E0A8();
        g_Player.D_80072EFC = 1;
        player->posX.val += FIX(4.5);
    }
}

// Pushes Alucard through the castle door at the entrance
void EntityCastleDoorTransition(Entity* entity) {
    Entity* player = &PLAYER;

    switch (entity->step) {
    case 0:
        if (g_CastleFlags[CASTLE_FLAG_52]) {
            DestroyEntity(entity);
            return;
        }
        InitializeEntity(g_EInitSpawner);
        g_Entities[UNK_ENTITY_1].ext.alucardController.unk7C = true;
        g_Player.padSim = PAD_RIGHT;
        g_Player.D_80072EFC = 0xFF;
        player->posX.i.hi = 8;
        entity->ext.castleDoorTransition.playerVelocity = 0x28000;
        break;

    case 1:
        player->posX.val += entity->ext.castleDoorTransition.playerVelocity;
        g_Player.D_80072EFC = 1;
        if ((player->posX.i.hi + g_Tilemap.scrollX.i.hi) > 120) {
            g_Player.padSim = 0;
            entity->step++;
        }
        break;

    case 2:
        if (entity->ext.castleDoorTransition.playerVelocity != 0) {
            entity->ext.castleDoorTransition.playerVelocity -= 0x2800;
            EntityExplosionVariantsSpawner(
                &PLAYER, 1, 1, 4, 0x18, (Random() & 3) + 1, -4);
        } else {
            g_PauseAllowed = true;
            entity->step++;
        }
        player->posX.val += entity->ext.castleDoorTransition.playerVelocity;
        g_Player.D_80072EFC = 1;
        break;
    }
}

// large foreground tree during intro
void EntityForegroundTree(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Entity *EntRange, *ent, *ent2;
    u16* ptrParams;
    u16 temp_s4;
    s16 var_s3;
    u16 y;

    if (self->params != 0) {
        var_s3 = 320;
        ptrParams = &D_80181468[self->ext.foregroundTree.unk7C].x;
    } else {
        var_s3 = 448;
        ptrParams = &D_801813DC[self->ext.foregroundTree.unk7C].x;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        EntRange = &g_Entities[192];
        self->unk68 = var_s3;
        self->flags |= FLAG_POS_CAMERA_LOCKED;
    label:
        if (*ptrParams <= 352) {
            ent = AllocEntity(EntRange, &EntRange[64]);
            if (ent != NULL) {
                CreateEntityFromCurrentEntity(E_ID_11, ent);
                ent->posX.i.hi = *ptrParams++;
                y = *ptrParams++;
                ent->params = (y >> 8) + self->params;
                ent->posY.i.hi = y & 255;
                ent->unk68 = var_s3;
                if (self->params != 0) {
                    ent->unk6C = 0x60;
                }
            } else {
                ptrParams += 2;
            }
            self->ext.foregroundTree.unk7C++;
            goto label;
        }
        break;

    case 1:
        self->posX.i.hi = 128;
        temp_s4 = var_s3 * tilemap->scrollX.i.hi / 256 + 352;
        if (temp_s4 >= *ptrParams) {
            ent = AllocEntity(&g_Entities[192], &g_Entities[256]);
            if (ent != NULL) {
                CreateEntityFromCurrentEntity(E_ID_11, ent);
                ent->posX.i.hi = temp_s4 - ptrParams[0] + 368;
                y = ptrParams[1];
                ent->params = (y >> 8) + self->params;
                ent->posY.i.hi = y & 255;
                ent->unk68 = var_s3;
                if (self->params != 0) {
                    ent->unk6C = 0x60;
                } else if (self->ext.foregroundTree.unk7C == 7) {
                    ent2 = AllocEntity(&g_Entities[192], &g_Entities[256]);
                    CreateEntityFromEntity(E_ID_11, ent, ent2);
                    ent2->params = 0x12;
                    ent2->unk68 = var_s3;
                    ent2->unk6C = 0x40;
                    ent2->posY.i.hi -= 16;
                } else if (self->ext.foregroundTree.unk7C == 10) {
                    ent2 = AllocEntity(&g_Entities[192], &g_Entities[256]);
                    CreateEntityFromEntity(E_ID_11, ent, ent2);
                    ent2->params = 0x13;
                    ent2->unk68 = var_s3;
                    ent2->unk6C = 0x40;
                    ent2->posY.i.hi += 48;
                } else if (self->ext.foregroundTree.unk7C == 15) {
                    ent2 = AllocEntity(&g_Entities[192], &g_Entities[256]);
                    CreateEntityFromEntity(E_ID_11, ent, ent2);
                    ent2->params = 0x14;
                    ent2->unk68 = var_s3;
                    ent2->unk6C = 0x40;
                    ent2->posY.i.hi += 4;
                }
            }
            self->ext.foregroundTree.unk7C++;
        }
    }
}

void EntityUnkId50(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* newEntity;
    Entity* temp;
    u16 temp_s3;
    s32 var_v0;
    u16* ptr;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        ptr = D_801814EC;
        temp = &g_Entities[192];
        self->unk68 = 0xC0;
        self->ext.et_801BCC4C.unk7C = 0;
        self->flags |= FLAG_POS_CAMERA_LOCKED;
    label:
        while (*ptr <= 288) {
            newEntity = AllocEntity(temp, &temp[64]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_ID_11, newEntity);
                newEntity->posX.i.hi = *ptr++;
                newEntity->params = *ptr++;
                newEntity->unk68 = 0xC0;
            } else {
                ptr += 2;
            }
            self->ext.et_801BCC4C.unk7C++;
            goto label;
        }
        break;

    case 1:
        self->posX.i.hi = 128;
        ptr = &D_801814EC[self->ext.et_801BCC4C.unk7C * 2];
        var_v0 = tilemap->scrollX.i.hi * 0xC0;

        if (var_v0 < 0) {
            var_v0 += 0xFF;
        }
        temp_s3 = (var_v0 >> 8) + 288;
        if (temp_s3 >= ptr[0]) {
            newEntity = AllocEntity(&g_Entities[192], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_ID_11, newEntity);
                newEntity->posX.i.hi = temp_s3 - ptr[0] + 288;
                newEntity->posX.i.lo = self->posX.i.lo;
                newEntity->params = ptr[1];
                newEntity->unk68 = 0xC0;
            }
            self->ext.et_801BCC4C.unk7C++;
        }
        break;
    }
}

extern u16 D_801817D4[];
extern u16 D_801817DC[];
extern u8 D_801817E4[];
extern u16 D_801817E8[];
extern u16* D_801817EC[];
// part of parallax background with pine trees
void EntityBackgroundPineTrees(Entity* self) {
    Tilemap* gTilemap = &g_Tilemap;
    u16 selfUnk68;
    s32 primIndex;
    u16* var_s5;
    u16 var_s4;
    u16 width;
    u16 xpos;
    Primitive* prim_s1;
    Primitive* prim_s0;

    xpos = self->params; // Temporary reuse of xpos var for params
    selfUnk68 = D_801817D4[xpos];
    var_s5 = D_801817EC[xpos];
    var_s5 += (u16)self->ext.timer.t * 2;
    var_s4 = D_801817DC[xpos];
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        self->flags |= FLAG_POS_CAMERA_LOCKED;
        self->unk68 = selfUnk68;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 32);
        if (primIndex == 0) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;

        for (prim_s0 = &g_PrimBuf[primIndex]; prim_s0 != NULL;
             prim_s0 = prim_s0->next) {
            prim_s0->drawMode = DRAW_HIDE;
        }

        for (prim_s0 = &g_PrimBuf[primIndex]; true; prim_s0 = prim_s1->next) {
            if (*var_s5 >= 0x121) {
                return;
            }
            self->ext.timer.t++;
            for (; prim_s0 != NULL; prim_s0 = prim_s0->next) {
                if (prim_s0->drawMode == DRAW_HIDE) {
                    break;
                }
            }
            if (prim_s0 == NULL) {
                return;
            }

            for (prim_s1 = prim_s0->next; prim_s1 != NULL;
                 prim_s1 = prim_s1->next) {
                if (prim_s1->drawMode == DRAW_HIDE) {
                    break;
                }
            }
            if (prim_s1 == NULL) {
                return;
            }
            prim_s0->tpage = 0xE;
            prim_s0->u0 = prim_s0->u2 = 0x80;
            prim_s0->u1 = prim_s0->u3 = 0x80 + 0x28;
            prim_s0->v0 = prim_s0->v1 = 0x80;
            prim_s0->v2 = prim_s0->v3 = 0x80 + 0x50;

            prim_s1->tpage = 0xF;
            prim_s1->u0 = prim_s1->u2 = 0xB0;
            prim_s1->u1 = prim_s1->u3 = 0xB0 + 0x08;
            prim_s1->v0 = prim_s1->v1 = 0xC8;
            prim_s1->v2 = prim_s1->v3 = 0xC8 + 0x30;

            xpos = *var_s5++;
            width = var_s4 * 20 / 256;

            prim_s0->x0 = prim_s0->x2 = xpos - width;
            prim_s0->x1 = prim_s0->x3 = xpos + width;

            width = var_s4 * 4 / 256;

            prim_s1->x0 = prim_s1->x2 = xpos - width + 1;
            prim_s1->x1 = prim_s1->x3 = xpos + width + 1;

            xpos = *var_s5++;

            prim_s0->clut = prim_s1->clut = D_801817E8[(xpos >> 8) & 0xFF];

            prim_s0->y2 = prim_s0->y3 =
                0x9C - ((0x2C - (xpos & 0xFF)) * var_s4 / 256);

            prim_s0->y0 = prim_s0->y1 = prim_s0->y2 - (var_s4 * 80 / 256);

            prim_s1->y2 = prim_s1->y3 = 0x9C;
            prim_s1->y0 = prim_s1->y1 = 0x9C - 0x30;
            // Set all colors for both prims.
            PCOL(prim_s0) = PCOL(prim_s1) = D_801817E4[self->params];
            prim_s0->priority = 0x3F - (self->params * 2);
            prim_s1->priority = prim_s0->priority - 1;
            prim_s0->drawMode = prim_s1->drawMode = DRAW_COLORS;
        }
    case 1:
        xpos = 0x80 - self->posX.i.hi;
        self->posX.i.hi = 0x80;

        for (prim_s0 = &g_PrimBuf[self->primIndex]; prim_s0 != NULL;
             prim_s0 = prim_s0->next) {
            if (prim_s0->drawMode != DRAW_HIDE) {
                prim_s0->x0 = prim_s0->x2 -= xpos;
                prim_s0->x1 = prim_s0->x3 -= xpos;
                if (prim_s0->x1 <= 0) {
                    prim_s0->drawMode = DRAW_HIDE;
                }
            }
        }
        xpos = gTilemap->scrollX.i.hi * selfUnk68 / 256 + 0x120;

        if (xpos < *var_s5) {
            return;
        }
        self->ext.timer.t++;
        for (prim_s0 = &g_PrimBuf[self->primIndex]; prim_s0 != NULL;
             prim_s0 = prim_s0->next) {
            if (prim_s0->drawMode == DRAW_HIDE) {
                for (prim_s1 = prim_s0->next; prim_s1 != NULL;
                     prim_s1 = prim_s1->next) {
                    if (prim_s1->drawMode == DRAW_HIDE) {
                        prim_s0->tpage = 0xE;
                        prim_s0->u0 = prim_s0->u2 = 0x80;
                        prim_s0->u1 = prim_s0->u3 = 0x80 + 0x28;
                        prim_s0->v0 = prim_s0->v1 = 0x80;
                        prim_s0->v2 = prim_s0->v3 = 0x80 + 0x50;

                        prim_s1->tpage = 0xF;
                        prim_s1->u0 = prim_s1->u2 = 0xB0;
                        prim_s1->u1 = prim_s1->u3 = 0xB0 + 0x08;
                        prim_s1->v0 = prim_s1->v1 = 0xC8;
                        prim_s1->v2 = prim_s1->v3 = 0xC8 + 0x30;

                        xpos = 0x120 - (xpos - *var_s5++);
                        width = var_s4 * 20 / 256;

                        prim_s0->x0 = prim_s0->x2 = xpos - width;
                        prim_s0->x1 = prim_s0->x3 = xpos + width;

                        width = var_s4 * 4 / 256;

                        prim_s1->x0 = prim_s1->x2 = xpos - width + 1;
                        prim_s1->x1 = prim_s1->x3 = xpos + width + 1;

                        xpos = *var_s5;
                        prim_s0->clut = prim_s1->clut =
                            D_801817E8[(xpos >> 8) & 0xFF];
                        prim_s0->y2 = prim_s0->y3 =
                            0x9C - ((0x2C - (xpos & 0xFF)) * var_s4 / 256);
                        prim_s0->y0 = prim_s0->y1 =
                            prim_s0->y2 - (var_s4 * 80 / 256);
                        prim_s1->y2 = prim_s1->y3 = 0x9C;
                        prim_s1->y0 = prim_s1->y1 = 0x9C - 0x30;
                        // Set all colors for both prims.
                        PCOL(prim_s0) = PCOL(prim_s1) =
                            D_801817E4[self->params];
                        prim_s0->priority = 0x3F - (self->params * 2);
                        prim_s1->priority = prim_s0->priority - 1;
                        prim_s0->drawMode = prim_s1->drawMode = DRAW_COLORS;
                        break;
                    }
                }
                break;
            }
        }
        break;
    }
}

void EntityUnkId52(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* newEntity;
    Entity* temp;
    u16 temp_s3;
    s32 var_v0;
    u16* ptr;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        ptr = D_801817F8;
        temp = &g_Entities[192];
        self->ext.et_801BCC4C.unk7C = 0;
        self->flags |= FLAG_POS_CAMERA_LOCKED;
    label:
        while (*ptr <= 288) {
            newEntity = AllocEntity(temp, &temp[64]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_ID_11, newEntity);
                newEntity->posX.i.hi = *ptr;
                newEntity->params = 0x10;
                newEntity->unk68 = 0x18;
            }
            ptr++;
            self->ext.et_801BCC4C.unk7C++;
            goto label;
        }
        break;

    case 1:
        self->posX.i.hi = 0x80;
        ptr = &D_801817F8[self->ext.et_801BCC4C.unk7C];

        var_v0 = tilemap->scrollX.i.hi * 0x18;
        if (var_v0 < 0) {
            var_v0 += 0xFF;
        }
        temp_s3 = (var_v0 >> 8) + 288;
        if (temp_s3 >= *ptr) {
            newEntity = AllocEntity(&g_Entities[192], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_ID_11, newEntity);
                newEntity->posX.i.hi = temp_s3 - *ptr + 288;
                newEntity->posX.i.lo = self->posX.i.lo;
                newEntity->params = 0x10;
                if (self->ext.et_801BCC4C.unk7C == 5) {
                    newEntity->params = 0x11;
                }
                newEntity->unk68 = 0x18;
            }
            self->ext.et_801BCC4C.unk7C++;
        }
        break;
    }
}

// func_psp_0923F328
void EntityCastleBridge(Entity* self) {
    const u32 primCount = 24;

    MATRIX* matrix;
    Primitive* prim;
    SVECTOR* vector;
    VECTOR* rotatedVector;
    s16* positionsPtr;
    s16* size;

    s16 xOffset;
    // self stored at    sp 0x40
    s16 yOffset;      // sp 0x3E
    s16 sinZ;         // sp 0x3C
    s16 cosZ;         // sp 0x3A
    Tilemap* tilemap; // sp 0x34
    Entity* player;   // sp 0x30

    u8* uv;
    s32 primIndex;

    tilemap = &g_Tilemap;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);

        primIndex = g_api.AllocPrimitives(PRIM_GT4, primCount);

        if (primIndex == 0) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];

        for (primIndex = 0; prim != NULL; primIndex++) {
            uv = &g_EntityCastleBridgeUVs
                     [g_EntityCastleBridgeUVOffsets[primIndex]];

            prim->u0 = prim->u2 = *uv++;
            prim->u1 = prim->u3 = *uv++;
            prim->v0 = prim->v1 = *uv++;
            prim->v2 = prim->v3 = *uv;

            prim->tpage = g_EntityCastleBridgePages[primIndex];
            prim->clut = 0x66;
            prim->priority = g_EntityCastleBridgePriorities[primIndex];
            prim->drawMode = DRAW_UNK02;

            prim = prim->next;
        }

        self->rotZ = 0;
        break;
    case 1:
        if (tilemap->scrollX.i.hi > 3904) {
            self->step++;
            g_api.PlaySfx(SE_CASTLE_GATE_RISE);
        }
        break;
    case 2:

        if (self->rotZ < 1024) {
            self->rotZ += 4;
        }

        player = &PLAYER;
        sinZ = rsin(self->rotZ); // the result is a signed(?) fixed point 12 bit
                                 // fractional number where 4096 == 1.0
        cosZ = rcos(self->rotZ);

        // the operation (sinZ * 12) >> 12 gives an integer between -12 and 12
        // based on the y coordinate of the rotated vector i am guessing that
        // 4563 is some tilemap offset?
        xOffset = (((sinZ * 12) >> 12) + 4563) -
                  (player->posX.i.hi + tilemap->scrollX.i.hi);

        // divide by zero check
        if (xOffset >= 0 && cosZ != 0) {

            // sinZ / cosZ is suspiciously like a tangent
            xOffset = 172 - ((cosZ * 12) >> 12) - ((xOffset * sinZ) / cosZ);

            if (xOffset > 0 && xOffset < 160) {
                switch (self->step_s) {
                case 0:
                    if (player->velocityY < 0) {
                        self->step_s++;
                    }
                    break;
                case 1:
                    if (player->velocityY >= 0 &&
                        (xOffset < player->posY.i.hi + 30)) {
                        player->posY.i.hi = xOffset - 30;
                        g_api.PlaySfx(SFX_STOMP_SOFT_A);
                        g_Player.pl_vram_flag |= 0x41;
                        self->step_s++;
                    }
                    break;
                case 2:
                    player->posY.i.hi = xOffset - 30;
                    g_Player.pl_vram_flag |= 0x41;
                    break;
                }
            }
        }
        break;
    }

    vector = (SVECTOR*)SP(0);
    rotatedVector = (VECTOR*)SP(8);
    size = (s16*)SP(0x18);
    // identity matrix
    matrix = (MATRIX*)SP(0x20);
    matrix->m[0][0] = matrix->m[1][1] = matrix->m[2][2] = 0x1000; // pain.
    matrix->m[0][1] = matrix->m[0][2] = matrix->m[1][0] = matrix->m[1][2] =
        matrix->m[2][0] = matrix->m[2][1] = 0;

    matrix = RotMatrixZ(self->rotZ, matrix);
    SetRotMatrix(matrix);
    positionsPtr = D_80181808;
    xOffset = 4563 - tilemap->scrollX.i.hi;
    vector->vz = 0;
    prim = &g_PrimBuf[self->primIndex];

    for (primIndex = 0; primIndex < 11; primIndex++) {
        if (primIndex < 2) {
            vector->vx = *positionsPtr++;
            vector->vy = *positionsPtr++;
            ApplyRotMatrix(vector, rotatedVector);

            prim->x0 = (s16)rotatedVector->vx + xOffset;
            prim->y0 = (s16)rotatedVector->vy + 168;

            vector->vx = *positionsPtr++;
            vector->vy = *positionsPtr++;
            ApplyRotMatrix(vector, rotatedVector);

            prim->x2 = (s16)rotatedVector->vx + xOffset;
            prim->y2 = (s16)rotatedVector->vy + 168;
        } else {
            size = (s16*)SP(0x18);
            prim->x0 = *size++;
            prim->y0 = *size++;
            prim->x2 = *size++;
            prim->y2 = *size++;
        }

        size = (s16*)SP(0x18);
        vector->vx = *positionsPtr++;
        vector->vy = *positionsPtr++;

        ApplyRotMatrix(vector, rotatedVector);
        prim->x1 = *size++ = (s16)rotatedVector->vx + xOffset;
        prim->y1 = *size++ = (s16)rotatedVector->vy + 168;

        vector->vx = *positionsPtr++;
        vector->vy = *positionsPtr++;
        ApplyRotMatrix(vector, rotatedVector);

        prim->x3 = *size++ = (s16)rotatedVector->vx + xOffset;
        prim->y3 = *size++ = (s16)rotatedVector->vy + 168;
        prim = prim->next;
    }

    matrix->m[0][0] = matrix->m[1][1] = matrix->m[2][2] = 0x1000;
    matrix->m[0][1] = matrix->m[0][2] = matrix->m[1][0] = matrix->m[1][2] =
        matrix->m[2][0] = matrix->m[2][1] = 0;

    vector->vx = -328;
    vector->vy = -18;

    ApplyRotMatrix(vector, rotatedVector);

    xOffset = (s16)rotatedVector->vx + xOffset;
    yOffset = (s16)rotatedVector->vy + 168;
    matrix = RotMatrixZ(
        ratan2(-352 - rotatedVector->vy, -(rotatedVector->vx - 128)), matrix);
    SetRotMatrix(matrix);

    positionsPtr = D_80181870;
    while (prim != NULL) {
        vector->vx = *positionsPtr++;
        vector->vy = *positionsPtr++;
        ApplyRotMatrix(vector, rotatedVector);
        prim->x0 = (s16)rotatedVector->vx + xOffset;
        prim->y0 = (s16)rotatedVector->vy + yOffset;

        vector->vx = *positionsPtr++;
        vector->vy = *positionsPtr++;
        ApplyRotMatrix(vector, rotatedVector);
        prim->x1 = (s16)rotatedVector->vx + xOffset;
        prim->y1 = (s16)rotatedVector->vy + yOffset;

        vector->vx = *positionsPtr++;
        vector->vy = *positionsPtr++;
        ApplyRotMatrix(vector, rotatedVector);
        prim->x2 = (s16)rotatedVector->vx + xOffset;
        prim->y2 = (s16)rotatedVector->vy + yOffset;

        vector->vx = *positionsPtr++;
        vector->vy = *positionsPtr++;
        ApplyRotMatrix(vector, rotatedVector);
        prim->x3 = (s16)rotatedVector->vx + xOffset;
        prim->y3 = (s16)rotatedVector->vy + yOffset;

        prim = prim->next;
    }
}

// ID 0x55
// Mostly just shadows in the far distance.
// Use texture viewer to confirm.
void EntityDistantBackgroundTrees(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s16 temp_v0_2;
    s16 var_a2;

    do { //! FAKE:
        switch (self->step) {
        case 0:
            InitializeEntity(g_EInitSpawner);
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 9);
            if (primIndex == 0) {
                DestroyEntity(self);
                return;
            }
            prim = &g_PrimBuf[primIndex];
            var_a2 = 0;
            self->posX.i.hi = 128;
            self->primIndex = primIndex;
            self->unk68 = 0x10;
            self->flags |= FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;

            while (prim != NULL) {
                prim->x0 = prim->x2 = var_a2;
                var_a2 += 0x1E;
                prim->tpage = 0xE;
                prim->clut = 0x67;
                prim->u0 = prim->u2 = 0x61;
                prim->u1 = prim->u3 = 0x7F;
                prim->v0 = prim->v1 = 0xE1;
                prim->v2 = prim->v3 = 0xFF;
                prim->x1 = prim->x3 = var_a2;
                prim->y0 = prim->y1 = 0xC0;
                prim->y2 = prim->y3 = 0xE3;
                prim->priority = 0x40;
                prim->drawMode = DRAW_DEFAULT;
                prim = prim->next;
            }
            break;

        case 1:
            var_a2 = 128 - self->posX.i.hi;
            self->posX.i.hi = 0x80;
            primIndex = self->primIndex;
            prim = &g_PrimBuf[self->primIndex];
            while (prim != NULL) {
                temp_v0_2 = prim->x2 - var_a2;
                prim->x0 = prim->x2 = temp_v0_2;
                prim->x1 = prim->x3 = temp_v0_2 + 0x1E;
                prim = prim->next;
            }
            break;
        }
    } while (0);
}

// shows part of the parallax background castle wall
void EntityBackgroundCastleWall(Entity* entity) {
    Entity* newEntity;

    newEntity = AllocEntity(&g_Entities[192], &g_Entities[256]);
    if (newEntity != NULL) {
        CreateEntityFromCurrentEntity(E_ID_11, newEntity);
        newEntity->params = 0xC;
        newEntity->unk68 = 0x80;
        newEntity = AllocEntity(newEntity, &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromCurrentEntity(E_ID_11, newEntity);
            newEntity->params = 0xB;
            newEntity->posY.i.hi = 0x80;
            newEntity->unk68 = 0xC0;
            newEntity->posX.i.hi += 0x40;
        }
    }
    DestroyEntity(entity);
}
