/*
 * File: 3246C.c
 * Overlay: NP3
 * Description: Castle Entrance (After entering Alchemy Laboratory)
 */

#include "np3.h"

void func_801B246C(Entity* self) {
    ObjInit2* temp_s0 = &D_80180C10[self->params];

    if (self->step == 0) {
        InitializeEntity(D_80180A90);
        self->animSet = temp_s0->animSet;
        self->zPriority = temp_s0->zPriority;
        self->facing = temp_s0->unk4.U8.unk0;
        self->unk5A = temp_s0->unk4.U8.unk1;
        self->palette = temp_s0->palette;
        self->unk19 = temp_s0->unk8;
        self->blendMode = temp_s0->blendMode;
        if (temp_s0->unkC != 0) {
            self->flags = temp_s0->unkC;
        }
    }

    AnimateEntity(temp_s0->unk10, self);
}

void func_801B2540(Entity* entity) {
    s32 ret;
    u16* temp_v0_2;
    u16 temp_s1 = entity->params;
    u16 phi_v1;
    u16 unk;

    entity->unk6D = 0;

    if (entity->step != 0) {
        switch (temp_s1) {
        case 4:
        case 5:
            if (g_CurrentRoom.x != 0) {
                return;
            }
            break;

        case 6:
            if (g_pads->pressed & PAD_TRIANGLE) {
                g_CurrentRoom.x = 0;
                g_CurrentRoom.width = 1280;
                entity->step++;
                return;
            }
            break;
        }

        if (entity->unk44 != 0) {
            ret = GetSideToPlayer();
            phi_v1 = entity->ext.generic.unk7C.s;
            if (phi_v1 != 0) {
                phi_v1 = (ret & 2) * 2;
            } else {
                phi_v1 = (ret & 1) * 4;
            }
            unk = 8;
            temp_s1 = (temp_s1 * unk) + phi_v1;
            temp_v0_2 = &D_80180DA8[temp_s1];
            g_CurrentRoom.x = *(temp_v0_2++);
            g_CurrentRoom.y = *(temp_v0_2++);
            g_CurrentRoom.width = *(temp_v0_2++);
            g_CurrentRoom.height = *(temp_v0_2++);
        }
    } else {
        InitializeEntity(D_80180A84);
        entity->ext.generic.unk7C.s = D_80180DA0[temp_s1];
        if (entity->ext.generic.unk7C.s != 0) {
            entity->hitboxWidth = D_80180D98[temp_s1];
            entity->hitboxHeight = 16;
        } else {
            entity->hitboxWidth = 16;
            entity->hitboxHeight = D_80180D98[temp_s1];
        }
    }
}

void EntityBreakable(Entity* entity) {
    u16 breakableType = entity->params >> 0xC;

    if (entity->step) {
        AnimateEntity(g_eBreakableAnimations[breakableType], entity);
        if (entity->unk44) { // If the candle is destroyed
            Entity* entityDropItem;
            g_api.PlaySfx(NA_SE_BREAK_CANDLE);
            entityDropItem =
                AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
            if (entityDropItem != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, entityDropItem);
                entityDropItem->params =
                    g_eBreakableExplosionTypes[breakableType];
            }
            ReplaceBreakableWithItemDrop(entity);
        }
    } else {
        InitializeEntity(g_eBreakableInit);
        entity->zPriority = g_zEntityCenter.S16.unk0 - 0x14;
        entity->blendMode = g_eBreakableBlendModes[breakableType];
        entity->hitboxHeight = g_eBreakableHitboxes[breakableType];
        entity->animSet = g_eBreakableanimSets[breakableType];
    }
}

void func_801B2830(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180A60);
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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B28E4);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityShuttingWindow);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B2F30);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B32A8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B3704);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B39CC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B3D24);

void EntityCavernDoorLever(Entity* entity) {
    s32 posX;
    s32 posY;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180AA8);
        entity->animCurFrame = 18;
        entity->rotAngle = -0x200;
        entity->unk19 |= 4;
        CreateEntityFromEntity(0x1E, entity, &entity[1]);
        if (D_8003BDEC[0x30] != 0) {
            entity->rotAngle = 0;
        }

    case 1:
        if (entity[1].ext.generic.unk84.S8.unk0 != 0) {
            entity->rotAngle += 4;
            if (entity->rotAngle > 0) {
                entity->rotAngle = 0;
                if (D_8003BDEC[0x30] == 0) {
                    g_api.PlaySfx(0x675);
                }
                D_8003BDEC[48] = 1;
            } else if (!(g_blinkTimer & 0xF)) {
                g_api.PlaySfx(0x675);
            }
        }
        break;
    }

    posX = entity->posX.val;
    posY = entity->posY.val;
    posX += rcos(entity->rotAngle) * 0x280;
    posY += rsin(entity->rotAngle) * 0x280;
    entity[1].posX.val = posX;
    entity[1].posY.val = posY;
}

// platform attached to lever at cavern door
void EntityCavernDoorPlatform(Entity* self) {
    Entity* player;
    s32 temp;
    s32 temp2;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180AA8);
        self->animCurFrame = 17;
        self->ext.generic.unk88.unk = self->posX.val;
        self->ext.generic.unk88.unk = self->posX.val; // ? WTF

    case 1:
        player = &PLAYER;
        self->ext.generic.unk84.S8.unk0 = temp2 = func_801BD588(self, 6, 5, 4);

        if (temp2 != 0) {
            temp = self->posX.i.hi;
            temp -= self->ext.generic.unk88.S16.unk2;
            player->posX.i.hi += temp;
            player->posY.i.hi++;
            D_8009748A[0] += temp;
            D_8009748A[2] += 1;
        }
        self->ext.generic.unk88.unk = self->posX.val;
        self->ext.generic.unk8C.modeS32 = self->posY.val;
    }
}

void func_801B40F8(Entity* self) {
    s16 primIndex;
    u16* tileLayoutPtr;
    Entity* entity;
    POLY_GT4* poly;
    s32 tilePos;
    s32 i;
    s32 temp;
    s32 temp2;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180AA8);
        self->animCurFrame = 10;
        self->zPriority = 0x9F;

        tileLayoutPtr = &D_801810F8[0];
        if (D_8003BDEC[48] != 0) {
            tileLayoutPtr = &D_801810F8[3];
            self->step = 128;
            self->animCurFrame = 0;
        } else {
            primIndex = g_api.AllocPrimitives(PRIM_TILE, 64);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }

            poly = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            *((s32*)(&self->ext.generic.unk7C)) = poly;
            self->flags |= FLAG_HAS_PRIMS;
            while (poly != NULL) {
                poly->u0 = poly->v0 = 1;
                poly->r0 = 64;
                poly->b0 = 128;
                poly->g0 = 96;
                tilePos = 0x76;
                poly->pad2 = self->zPriority + 0x18;
                poly->pad3 = 8;
                poly->p3 = 0;
                poly = (POLY_GT4*)poly->tag;
            }
        }

        for (tilePos = 0x76, i = 0; i < 3; i++) {
            g_CurrentRoomTileLayout.fg[tilePos] = *tileLayoutPtr;
            tileLayoutPtr++;
            tilePos += 0x10;
        }
        break;

    case 1:
        if (D_8003BDEC[48] != 0) {
            self->step++;
        }
        break;

    case 2:
        self->posY.val += 0x6000;
        if (++self->ext.generic.unk80.modeS32 & 1) {
            self->posX.i.hi++;
        } else {
            self->posX.i.hi--;
        }

        temp = self->posY.i.hi - 136;
        if (temp < 0) {
            temp2 = self->posY.i.hi - 121;
        } else {
            temp2 = self->posY.i.hi - 136;
        }

        temp = temp2 >> 4;
        if (temp >= 4) {
            temp = 3;
            self->step = 3;
        }

        if (!(self->ext.generic.unk80.modeS32 & 15)) {
            g_api.PlaySfx(NA_SE_EV_HEAVY_BLOCK_DRAG);
        }

        for (tilePos = 0x76, tileLayoutPtr = &D_801810F8[3], i = 0; i < temp;
             tileLayoutPtr++, tilePos += 0x10, i++) {
            g_CurrentRoomTileLayout.fg[tilePos] = *tileLayoutPtr;
        }

        if (!(g_blinkTimer & 1)) {
            poly = func_801D2470((POLY_GT4*)(*(s32*)&self->ext.generic.unk7C));
            if (poly != NULL) {
                poly->p3 = 1;
            }

            if (!(g_blinkTimer & 15)) {
                entity = AllocEntity(D_8007D858, &D_8007D858[32]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
                    entity->posY.i.hi = 156;
                    entity->posX.i.hi += -8 + (Random() & 15);
                    entity->zPriority = self->zPriority + 2;
                    entity->params = 0x10;
                    entity->unk19 |= 3;
                    entity->unk1A = entity->unk1C = 192;
                }
            }
        }
        break;
    }

    if (self->flags & FLAG_HAS_PRIMS) {
        for (poly = *(s32*)&self->ext.generic.unk7C; poly != NULL;
             poly = (POLY_GT4*)poly->tag) {
            if (poly->p3 != 0) {
                func_801B3D24(poly);
            }
        }
    }
}

typedef enum { WEIGHT_SMALL, WEIGHT_TALL } WeightSelect;

void func_801B44B4(WeightSelect weight) {
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
        prim->blendMode = 2;
        prim = prim->next;
    }
    posY -= 32;

    while (prim != 0) {
        prim->blendMode = 8;
        prim = prim->next;
    }
}

// switch that clicks when you step on it
void EntityClickSwitch(Entity* entity) {
    s32 temp_a0 = func_801BD588(entity, 8, 4, 4);
    Entity* player = &PLAYER;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180AA8);
        entity->animCurFrame = 9;
        entity->zPriority = 0x5E;
        if (D_8003BDEC[49] != 0) {
            entity->step = 2;
            entity->posY.i.hi += 4;
        }
        break;

    case 1:
        if (temp_a0 != 0) {
            player->posY.i.hi++;
            entity->posY.val += 0xC000;
            if ((g_Camera.posY.i.hi + entity->posY.i.hi) > 160) {
                entity->posY.i.hi = 160 - g_Camera.posY.i.hi;
                g_api.PlaySfx(NA_SE_EV_SWITCH_CLICK);
                D_8003BDEC[49] = 1;
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
        InitializeEntity(D_80180AA8);
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

        self->posX.i.hi = 416 - g_Camera.posX.i.hi;
        self->posY.i.hi = 64 - g_Camera.posY.i.hi;
        if (D_8003BDEC[49] != 0) {
            self->posY.i.hi += 111;
            self->step = 3;
        }
        break;

    case 1:
        if (D_8003BDEC[49] != 0) {
            self->step++;
        }
        break;

    case 2:
        self->posY.val += 0x8000;
        if ((self->posY.i.hi + g_Camera.posY.i.hi) >= 175) {
            func_801C2598(0x63D);
            self->posY.i.hi = 175 - g_Camera.posY.i.hi;
            self->step++;
        }
        break;

    case 3:
        for (var_a1 = 0x179, i = 0; i < 2; var_a1 -= 0x20, i++) {
            g_CurrentRoomTileLayout.fg[var_a1] = 0x4FA;
            g_CurrentRoomTileLayout.fg[var_a1 + 1] = 0x4FA;
        }
        self->step++;
        break;
    }

    if ((self->step < 3) && (func_801BD588(self, 16, 16, 5) & 4)) {
        Entity* player = &PLAYER;

        player->posY.i.hi++;
    }
    func_801B44B4(WEIGHT_SMALL);
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
        InitializeEntity(D_80180AA8);
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

        if (D_8003BDEC[49] != 0) {
            self->step = 3;
            self->posY.i.hi -= 128;
        }
        break;

    case 1:
        if (D_8003BDEC[49] != 0) {
            self->step++;
        }
        break;

    case 2:
        self->posY.val -= 0x8000;
        temp = self->posY.i.hi + g_Camera.posY.i.hi;
        if (temp <= -16) {
            self->posY.i.hi = -16 - g_Camera.posY.i.hi;
            self->step++;
        }
        break;
    }

    func_801B44B4(WEIGHT_TALL);
    do {
        temp = self->posY.i.hi + g_Camera.posY.i.hi;
    } while (0);
    var_v0 = 112 - temp;
    var_a1 = 0x157;

    if (var_v0 < 0) {
        var_v0 += 15;
    }

    for (temp_a2 = var_v0 >> 4, i = 0; i < temp_a2; var_a1 -= 0x20, i++) {
        g_CurrentRoomTileLayout.fg[var_a1] = 0;
        g_CurrentRoomTileLayout.fg[var_a1 + 1] = 0;
    }

    for (temp_a2 = 8 - temp_a2, i = 0; i < temp_a2; var_a1 -= 0x20, i++) {
        g_CurrentRoomTileLayout.fg[var_a1] = 0x4FA;
        g_CurrentRoomTileLayout.fg[var_a1 + 1] = 0x4FA;
    }
}

void EntityTrapDoor(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180AA8);
        entity->animCurFrame = 0x1B;
        entity->zPriority = 0x6A;
        entity->hitboxWidth = 0x10;
        entity->hitboxHeight = 4;
        entity->hitboxState = 1;

        if (g_TrapDoorFlag == 0) {
            if (PLAYER.posY.val < entity->posY.val) {
                g_CurrentRoomTileLayout.fg[0xA8E / 2] = 0x129;
                g_CurrentRoomTileLayout.fg[0xA90 / 2] = 0x132;
                DestroyEntity(entity);
                return;
            }
            g_CurrentRoomTileLayout.fg[0xA8E / 2] = 0x6C8;
            g_CurrentRoomTileLayout.fg[0xA90 / 2] = 0x6C9;
        } else {
            entity->animCurFrame = 30;
            g_CurrentRoomTileLayout.fg[0xA8E / 2] = 0x6C8;
            g_CurrentRoomTileLayout.fg[0xA90 / 2] = 0x6C9;
            entity->step = 128;
        }

    case 1:
        if (entity->hitFlags != 0) {
            g_TrapDoorFlag = 1;
            entity->step++;
        }
        break;

    case 2:
        AnimateEntity(D_80181108, entity);
        break;
    }
}

// left side of the breakable rock, drops pot roast
void EntityMermanRockLeftSide(Entity* self) {
    u16* tileLayoutPtr;
    Entity* newEntity;
    s32 tilePos;
    u8* params;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180A6C);
        self->hitboxState = 2;
        self->hitboxWidth = 16;
        self->hitboxHeight = 24;

        tileLayoutPtr = &D_80181144;
        tilePos = 0x1F1;
        for (i = 0; i < 3; i++) {
            g_CurrentRoom.bg[0].layout[tilePos] = *tileLayoutPtr;
            g_CurrentRoom.bg[0].layout[tilePos + 1] = *(tileLayoutPtr + 3);
            tileLayoutPtr++;
            tilePos += 0x30;
        }

        if (D_8003BDEC[51] & 1) { /* 0 0 0 0 0 0 0 1 = Broken */
            tileLayoutPtr = &D_8018112C;
            tilePos = 0x1F1;
            for (i = 0; i < 3; i++) {
                g_CurrentRoomTileLayout.fg[tilePos] = *tileLayoutPtr;
                g_CurrentRoomTileLayout.fg[tilePos + 1] = *(tileLayoutPtr + 3);
                tileLayoutPtr++;
                tilePos += 0x30;
            }
            self->hitboxState = 1;
            self->step = 2;
        }
        break;

    case 1:
        if (self->hitFlags != 0) {
            tileLayoutPtr = &D_80181120[self->ext.generic.unk84.S16.unk0 * 6];
            tilePos = 0x1F1;
            for (i = 0; i < 3; i++) {
                g_CurrentRoomTileLayout.fg[tilePos] = *tileLayoutPtr;
                g_CurrentRoomTileLayout.fg[tilePos + 1] = *(tileLayoutPtr + 3);
                tileLayoutPtr++;
                tilePos += 0x30;
            }

            g_api.PlaySfx(NA_SE_EN_ROCK_BREAK);

            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 0x13;
                newEntity->zPriority = 0xA9;
                newEntity->posX.i.hi += self->ext.generic.unk84.S16.unk0 * 16;
                newEntity->posY.i.hi += 16;
            }

            params = &D_8018120C[self->ext.generic.unk84.S16.unk0 * 3];

            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x27, self, newEntity);
                    newEntity->params = *params++;
                    newEntity->accelerationX = -0x8000 - (Random() << 8);
                    newEntity->accelerationY = -Random() * 0x100;
                    newEntity->posY.i.hi += -16 + (i * 16);
                }
            }
            self->ext.generic.unk84.S16.unk0++;
        }

        if (self->ext.generic.unk84.S16.unk0 >= 2) {
            newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0xA, self, newEntity);
                newEntity->params = 0x43;
            }
            D_8003BDEC[51] |= 1; /* 0 0 0 0 0 0 0 1 = Broken */
            self->hitboxState = 1;
            self->step++;
        }
        break;

    case 2:
        if ((self->hitFlags != 0) && (g_Player.unk0C & 4)) {
            D_8003BDEC[51] |= 4; /* 0 0 0 0 0 1 0 0 = Wolf form collision */
        }
        break;
    }
}

// right side of the merman room rock, breaks when hit
void EntityMermanRockRightSide(Entity* self) {
    u16* tileLayoutPtr;
    Entity* newEntity;
    s32 tilePos;
    u8* params;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180A6C);
        self->hitboxState = 2;
        self->hitboxWidth = 16;
        self->hitboxHeight = 24;

        tileLayoutPtr = &D_80181180;
        tilePos = 0x1FD;
        for (i = 0; i < 3; i++) {
            g_CurrentRoom.bg[0].layout[tilePos] = *tileLayoutPtr;
            g_CurrentRoom.bg[0].layout[tilePos + 1] = *(tileLayoutPtr + 3);
            tileLayoutPtr++;
            tilePos += 0x30;
        }

        if (D_8003BDEC[51] & 2) { /* 0 0 0 0 0 0 1 0 = Broken */
            tileLayoutPtr = &D_80181168;
            tilePos = 0x1FD;
            for (i = 0; i < 3; i++) {
                g_CurrentRoomTileLayout.fg[tilePos] = *tileLayoutPtr;
                g_CurrentRoomTileLayout.fg[tilePos + 1] = *(tileLayoutPtr + 3);
                tileLayoutPtr++;
                tilePos += 0x30;
            }
            self->hitboxState = 1;
            self->step = 2;
        }
        break;

    case 1:
        if (self->hitFlags != 0) {
            tileLayoutPtr = &D_8018115C[(self->ext.generic.unk84.S16.unk0 * 6)];
            tilePos = 0x1FD;
            for (i = 0; i < 3; i++) {
                g_CurrentRoomTileLayout.fg[tilePos] = *tileLayoutPtr;
                g_CurrentRoomTileLayout.fg[tilePos + 1] = *(tileLayoutPtr + 3);
                tileLayoutPtr++;
                tilePos += 0x30;
            }

            g_api.PlaySfx(NA_SE_EN_ROCK_BREAK);

            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 0x13;
                newEntity->zPriority = 0xA9;
                newEntity->posX.i.hi -= self->ext.generic.unk84.S16.unk0 * 16;
                newEntity->posY.i.hi += 16;
            }

            params = &D_8018120C[self->ext.generic.unk84.S16.unk0 * 3];

            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x27, self, newEntity);
                    newEntity->params = *params++;
                    newEntity->accelerationX = (Random() << 8) + 0x8000;
                    newEntity->accelerationY = -Random() * 0x100;
                    newEntity->facing = 1;
                    newEntity->posY.i.hi += -16 + (i * 16);
                }
            }
            self->ext.generic.unk84.S16.unk0++;
        }

        if (self->ext.generic.unk84.S16.unk0 >= 2) {
            D_8003BDEC[51] |= 2; /* 0 0 0 0 0 0 1 0 = Broken */
            self->hitboxState = 1;
            self->step++;
        }
        break;

    case 2:
        if ((self->hitFlags != 0) && (g_Player.unk0C & 1)) {
            D_8003BDEC[51] |= 8; /* 0 0 0 0 1 0 0 0 = Bat form collision */
        }
        break;
    }
}

void func_801B5488(Entity* self) {
    u16* tileLayoutPtr;
    s32 tileLayoutPos;
    s32 i;
    s32 j;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180A6C);
        if (D_8003BDEC[58] != 0) {
            self->step = 2;
        }
        break;

    case 1:
        if ((D_8003BDEC[51] & 12) == 12) {
            func_801C2598(0x644);
            self->step++;
        }
        break;

    case 2:
        for (tileLayoutPtr = &D_801811AA, i = 0; i < 3; i++) {
            tileLayoutPos = 0x420 + i;
            for (j = 0; j < 5; tileLayoutPos += 0x30, j++, tileLayoutPtr++) {
                g_CurrentRoomTileLayout.fg[tileLayoutPos] = *tileLayoutPtr;
            }
        }

        for (tileLayoutPtr = &D_801811E6, i = 0; i < 3; i++) {
            tileLayoutPos = 0x420 + i;
            for (j = 0; j < 5; j++, tileLayoutPtr++) {
                g_CurrentRoom.bg[0].layout[tileLayoutPos] = *tileLayoutPtr;
                tileLayoutPos += 0x30;
            }
        }

        D_8003BDEC[58] |= 1;
        g_api.func_800F1FC4(0x3A);
        self->step++;
        break;
    }
}

void EntityFallingRock2(Entity* self) {
    s32 animFrame = self->params & 0xF;
    Collider collider;
    Entity* newEntity;
    s32 temp_a0;
    s32 var_a1;
    s32 new_var2;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180AA8);
        self->animCurFrame = animFrame;
        self->animCurFrame += 31;
        self->zPriority = 0x9F;
        self->unk19 |= 4;
        break;

    case 1:
        MoveEntity();
        self->accelerationY += 0x4000;
        self->rotAngle -= 0x20;
        new_var2 = self->posY.i.hi;
        new_var2 += D_80181204[animFrame];
        g_api.CheckCollision(self->posX.i.hi, new_var2, &collider, 0);

        if (collider.effects & EFFECT_SOLID) {
            if (self->accelerationY > 0x40000) {
                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
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
            self->posY.i.hi = self->posY.i.hi + *(u16*)&collider.unk18;
            temp_a0 = -self->accelerationY;
            self->accelerationY = -self->accelerationY;
            if (temp_a0 < 0) {
                var_a1 = temp_a0 + 7;
            } else {
                var_a1 = temp_a0;
            }
            self->accelerationY = temp_a0 - (var_a1 >> 3);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B5790);

void EntityFallingRock(Entity* self) {
    s32 animFrame = self->params & 0xF;
    Collider collider;
    Entity* newEntity;
    s16 rndAngle;
    s32 rnd;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180AA8);
        self->animCurFrame = animFrame + 31;
        self->unk1C = 0x60;
        self->unk1A = 0x60;
        self->unk19 |= 7;
        rnd = (Random() & 0x1F) + 16;
        rndAngle = (Random() * 6) + 0x900;
        self->accelerationX = rnd * rcos(rndAngle);
        self->accelerationY = rnd * rsin(rndAngle);
        if (self->accelerationX > 0) {
            self->facing = 1;
        }
        break;

    case 1:
        MoveEntity();
        self->accelerationY += 0x2000;
        self->rotAngle -= 0x20;

        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 8, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(6, self, newEntity);
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

void func_801B5DE8(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180AA8);
        self->zPriority = 0x2A;
        self->flags &= ~FLAG_UNK_08000000;
        self->facing = Random() & 1;
        g_api.func_80134714(0x665, 0x40, (self->posX.i.hi >> 0x4) - 8);
    }
    if (AnimateEntity(D_80181214, self) == 0) {
        DestroyEntity(self);
    }
}

void func_801B5E98(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180AA8);
        self->zPriority = 0x29;
        self->flags &= ~FLAG_UNK_08000000;
        self->animCurFrame = self->params + 0x22;
        self->posX.i.hi = D_80181220[self->params][0];
        self->posY.i.hi = D_80181220[self->params][1];
        self->ext.generic.unk80.modeS16.unk0 = 5;
    }

    if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntitySwitch);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B6084);

void EntityUnkId49(Entity* self) {
    u16 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180A6C);
        break;
    case 1:
        temp = g_CurrentRoomTileLayout.fg[0x12 / 2];
        g_CurrentRoomTileLayout.fg[0xC / 2] = temp;
        temp = g_CurrentRoomTileLayout.fg[0x14 / 2];
        g_CurrentRoomTileLayout.fg[0xE / 2] = temp;
        temp = g_CurrentRoomTileLayout.fg[0x72 / 2];
        g_CurrentRoomTileLayout.fg[0x6C / 2] = temp;
        temp = g_CurrentRoomTileLayout.fg[0x74 / 2];
        g_CurrentRoomTileLayout.fg[0x6E / 2] = temp;
        temp = g_CurrentRoomTileLayout.fg[0xD2 / 2];
        g_CurrentRoomTileLayout.fg[0xCC / 2] = temp;
        temp = g_CurrentRoomTileLayout.fg[0xD4 / 2];
        g_CurrentRoomTileLayout.fg[0xCE / 2] = temp;
        self->step++;
        break;
    }
}

void func_801B653C(void) {
    Entity* entity;
    s8 temp_s4 = Random() & 3;
    s16 temp_s3 = ((Random() & 0xF) << 8) - 0x800;
    s32 i;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (entity != NULL) {
            CreateEntityFromEntity(0x4D, g_CurrentEntity, entity);
            entity->params = 2;
            entity->ext.generic.unk88.U8.unk1 = 6 - i;
            entity->ext.generic.unk84.S16.unk0 = temp_s3;
            entity->ext.generic.unk88.U8.unk0 = temp_s4;
        }
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B65FC);
