#include "no3.h"

// pushes alucard to the right
void EntityPushAlucard(Entity* entity) {
    Entity* player = &PLAYER;
    Unkstruct8* roomLayout = &g_CurrentRoomTileLayout;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180AD0);
        g_Entities[UNK_ENTITY_1].ext.generic.unk7C.S8.unk0 = 1;
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 255;
        player->posX.i.hi = 0;
        *D_8009740C = 0;
        player->animCurFrame = 0;
        D_8003C8B8 = 0;
        break;

    case 1:
        player->posX.val += 0x60000;
        if (roomLayout->unkA > 0x800) {
            g_Entities[UNK_ENTITY_1].ext.generic.unk7C.S8.unk0 = 0;
            g_Player.D_80072EF4 = 0x2000;
            entity->step++;
        }
        player->animCurFrame = 0;
        g_Player.D_80072EFC = 1;
        g_api.func_8010E0A8();
        break;

    case 2:
        player->posX.val += 0x88000;
        *D_8009740C += 4;
        if (*D_8009740C == 192) {
            entity->ext.generic.unk80.modeS32 = 0x48000;
            entity->step++;
        }
        g_Player.D_80072EFC = 1;
        g_api.func_8010E0A8();
        break;

    case 3:
        if (*D_8009740C > 128) {
            *D_8009740C -= 1;
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
        if (roomLayout->unkA > 0xF80) {
            g_api.PlaySfx(0x6EF);
            g_Player.D_80072EF4 = 0x2040;
            entity->ext.generic.unk7C.S8.unk0 = 0;
            entity->step++;
        }
        g_Player.D_80072EFC = 1;
        g_api.func_8010E0A8();
        break;

    case 5:
        if ((player->velocityY > 0) &&
            (entity->ext.generic.unk7C.U8.unk0 == 0)) {
            g_Player.D_80072EF4 = 0x40;
            entity->ext.generic.unk7C.S8.unk0 = 1;
        } else {
            g_Player.D_80072EF4 = 0x2040;
        }
        g_api.func_8010E0A8();
        g_Player.D_80072EFC = 1;
        player->posX.val += 0x48000;
    }
}

// Instruction reorder, only matches in PSY-Q 4.0
// Probably ASPSX
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/no3/nonmatchings/3C4EC", EntityUnkId53);
#else
void EntityUnkId53(Entity* entity) {
    s32 temp_v0;
    Entity* player = &PLAYER;

    switch (entity->step) {
    case 0:
        if (D_8003BDEC[0x34] != 0) {
            DestroyEntity(entity);
            return;
        }
        InitializeEntity(D_80180AD0);
        g_Entities[1].ext.generic.unk7C.S8.unk0 = 1;
        g_Player.D_80072EF4 = 0x2000;
        g_Player.D_80072EFC = 0xFF;
        player->posX.i.hi = 8;
        *(s32*)&entity->ext.generic.unk7C.s = 0x28000;
        break;

    case 1:
        player->posX.val += *(s32*)&entity->ext.generic.unk7C.s;
        g_Player.D_80072EFC = 1;
        if ((player->posX.i.hi + g_Camera.posX.i.hi) > 120) {
            g_Player.D_80072EF4 = 0;
            entity->step++;
        }
        break;

    case 2:
        if (*(s32*)&entity->ext.generic.unk7C.s != 0) {
            *(s32*)&entity->ext.generic.unk7C.s -= 0x2800;
            func_801C8C84(&PLAYER, 1, 1, 4, 0x18, (Random() & 3) + 1, -4);
        } else {
            D_8003C8B8 = 1;
            entity->step++;
        }
        player->posX.val += *(s32*)&entity->ext.generic.unk7C.s;
        g_Player.D_80072EFC = 1;
        break;
    }
}
#endif

// large foreground tree during intro
INCLUDE_ASM("asm/us/st/no3/nonmatchings/3C4EC", EntityForegroundTree);

void EntityUnkId50(Entity* self) {
    Unkstruct8* roomLayout = &g_CurrentRoomTileLayout;
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
        self->flags |= FLAG_UNK_08000000;
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
        var_v0 = roomLayout->unkA * 0xC0;

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
INCLUDE_ASM("asm/us/st/no3/nonmatchings/3C4EC", EntityBackgroundPineTrees);

void EntityUnkId52(Entity* self) {
    Unkstruct8* layout = &g_CurrentRoomTileLayout;
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
        self->flags |= FLAG_UNK_08000000;
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

        var_v0 = layout->unkA * 0x18;
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

INCLUDE_ASM("asm/us/st/no3/nonmatchings/3C4EC", EntityUnkId54);

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
            self->flags |= FLAG_UNK_08000000 | FLAG_HAS_PRIMS;

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
                prim->blendMode = 0;
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
