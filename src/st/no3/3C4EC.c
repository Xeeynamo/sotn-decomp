// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"

// pushes alucard to the right
void EntityPushAlucard(Entity* entity) {
    Entity* player = &PLAYER;
    Tilemap* tilemap = &g_Tilemap;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180AD0);
        g_Entities[UNK_ENTITY_1].ext.alucardController.unk7C = true;
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 255;
        player->posX.i.hi = 0;
        g_unkGraphicsStruct.unkC = 0;
        player->animCurFrame = 0;
        D_8003C8B8 = 0;
        break;

    case 1:
        player->posX.val += 0x60000;
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
        player->posX.val += 0x88000;
        g_unkGraphicsStruct.unkC += 4;
        if (g_unkGraphicsStruct.unkC == 192) {
            entity->ext.generic.unk80.modeS32 = 0x48000;
            entity->step++;
        }
        g_Player.D_80072EFC = 1;
        g_api.func_8010E0A8();
        break;

    case 3:
        if (g_unkGraphicsStruct.unkC > 128) {
            g_unkGraphicsStruct.unkC -= 1;
            entity->ext.generic.unk80.modeS32 = 0x38000;
        } else {
            entity->ext.generic.unk80.modeS32 = 0x48000;
        }
        player->posX.val += entity->ext.generic.unk80.modeS32;
        if (entity->ext.generic.unk80.modeS32 == 0x48000) {
            entity->step++;
        }
        g_Player.D_80072EFC = 1;
        g_api.func_8010E0A8();
        break;

    case 4:
        player->posX.val += 0x48000;
        if (tilemap->scrollX.i.hi > 0xF80) {
            g_api.PlaySfx(SE_NO3_ALUCARD_JUMP);
            g_Player.padSim = PAD_RIGHT | PAD_CROSS;
            entity->ext.generic.unk7C.S8.unk0 = 0;
            entity->step++;
        }
        g_Player.D_80072EFC = 1;
        g_api.func_8010E0A8();
        break;

    case 5:
        if ((player->velocityY > 0) &&
            (entity->ext.generic.unk7C.U8.unk0 == 0)) {
            g_Player.padSim = PAD_CROSS;
            entity->ext.generic.unk7C.S8.unk0 = 1;
        } else {
            g_Player.padSim = PAD_RIGHT | PAD_CROSS;
        }
        g_api.func_8010E0A8();
        g_Player.D_80072EFC = 1;
        player->posX.val += 0x48000;
    }
}

// Pushes Alucard through the castle door at the entrance
void EntityCastleDoorTransition(Entity* entity) {
    Entity* player = &PLAYER;

    switch (entity->step) {
    case 0:
        if (g_CastleFlags[52]) {
            DestroyEntity(entity);
            return;
        }
        InitializeEntity(D_80180AD0);
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
            EntityUnkId14Spawner(
                &PLAYER, 1, 1, 4, 0x18, (Random() & 3) + 1, -4);
        } else {
            D_8003C8B8 = 1;
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
        InitializeEntity(D_80180AD0);
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
        InitializeEntity(D_80180AD0);
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

// part of parallax background with pine trees
INCLUDE_ASM("st/no3/nonmatchings/3C4EC", EntityBackgroundPineTrees);

void EntityUnkId52(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* newEntity;
    Entity* temp;
    u16 temp_s3;
    s32 var_v0;
    u16* ptr;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180AD0);
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

INCLUDE_ASM("st/no3/nonmatchings/3C4EC", EntityCastleBridge);

// ID 0x55
void EntityBackgroundTrees(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s16 temp_v0_2;
    s16 var_a2;

    do { //! FAKE:
        switch (self->step) {
        case 0:
            InitializeEntity(D_80180AD0);
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
