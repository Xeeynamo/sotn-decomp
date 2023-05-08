/*
 * File: 3246C.c
 * Overlay: NP3
 * Description: Castle Entrance (After entering Alchemy Laboratory)
 */

#include "np3.h"

void func_801B246C(Entity* self) {
    ObjInit2* temp_s0 = &D_80180C10[self->subId];

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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B2540);

extern u16 g_eBreakableInit[];
extern u8* g_eBreakableAnimations[8];
extern u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakableanimSets[];
extern u8 g_eBreakableBlendModes[];
void EntityBreakable(Entity* entity) {
    u16 breakableType = entity->subId >> 0xC;
    if (entity->step) {
        AnimateEntity(g_eBreakableAnimations[breakableType], entity);
        if (entity->unk44) { // If the candle is destroyed
            Entity* entityDropItem;
            g_api.PlaySfx(NA_SE_BREAK_CANDLE);
            entityDropItem =
                AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
            if (entityDropItem != NULL) {
                CreateEntityFromCurrentEntity(ENTITY_EXPLOSION, entityDropItem);
                entityDropItem->subId =
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
        InitializeEntity(&D_80180A60);
        self->ext.generic.unk7C.S8.unk0 = 16;
        self->ext.generic.unk7C.S8.unk1 = 8;
        self->ext.generic.unk7E.modeU8.unk0 = 56;

    case 1:
        D_8003CB08.buf.draw.r0 = self->ext.generic.unk7C.S8.unk0;
        D_8003CB08.buf.draw.g0 = self->ext.generic.unk7C.S8.unk1;
        D_8003CB08.buf.draw.b0 = self->ext.generic.unk7E.modeU8.unk0;
        D_800542FC.buf.draw.r0 = self->ext.generic.unk7C.S8.unk0;
        D_800542FC.buf.draw.g0 = self->ext.generic.unk7C.S8.unk1;
        D_800542FC.buf.draw.b0 = self->ext.generic.unk7E.modeU8.unk0;
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
        InitializeEntity(&D_80180AA8);
        entity->animCurFrame = 18;
        entity->unk1E = -0x200;
        entity->unk19 |= 4;
        CreateEntityFromEntity(0x1E, entity, &entity[1]);
        if (D_8003BDEC[0x30] != 0) {
            entity->unk1E = 0;
        }

    case 1:
        if (entity[1].ext.generic.unk84.S8.unk0 != 0) {
            entity->unk1E += 4;
            if (entity->unk1E > 0) {
                entity->unk1E = 0;
                if (D_8003BDEC[0x30] == 0) {
                    g_api.PlaySfx(0x675);
                }
                D_8003BDEC[0x30] = 1;
            } else if (!(g_blinkTimer & 0xF)) {
                g_api.PlaySfx(0x675);
            }
        }
        break;
    }

    posX = entity->posX.val;
    posY = entity->posY.val;
    posX += rcos(entity->unk1E) * 0x280;
    posY += rsin(entity->unk1E) * 0x280;
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
    s16 firstPolygonIndex;
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
            firstPolygonIndex = g_api.AllocPrimitives(1, 64);
            if (firstPolygonIndex == -1) {
                DestroyEntity(self);
                return;
            }

            poly = &g_PrimBuf[firstPolygonIndex];
            self->firstPolygonIndex = firstPolygonIndex;
            *((s32*)(&self->ext.generic.unk7C)) = poly;
            self->flags |= FLAG_FREE_POLYGONS;
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
                    CreateEntityFromEntity(6, self, entity);
                    entity->posY.i.hi = 156;
                    entity->posX.i.hi += -8 + (Random() & 15);
                    entity->zPriority = self->zPriority + 2;
                    entity->subId = 0x10;
                    entity->unk19 |= 3;
                    entity->unk1A = entity->unk1C = 192;
                }
            }
        }
        break;
    }

    if (self->flags & FLAG_FREE_POLYGONS) {
        for (poly = *(s32*)&self->ext.generic.unk7C; poly != NULL;
             poly = (POLY_GT4*)poly->tag) {
            if (poly->p3 != 0) {
                func_801B3D24(poly);
            }
        }
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B44B4);

// switch that clicks when you step on it
void EntityClickSwitch(Entity* entity) {
    s32 temp_a0 = func_801BD588(entity, 8, 4, 4);
    Entity* player = &PLAYER;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180AA8);
        entity->animCurFrame = 9;
        entity->zPriority = 0x5E;
        if (D_8003BDEC[0x31] != 0) {
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
                D_8003BDEC[0x31] = 1;
                entity->step++;
            }
        }
        break;
    }
}

// smaller weight blocking path near cube of zoe
void EntityPathBlockSmallWeight(Entity* self) {
    s16 firstPolygonIndex;
    POLY_GT4* poly;
    s32 var_a1;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(&D_80180AA8);
        self->animCurFrame = 8;
        self->zPriority = 0x5E;

        firstPolygonIndex = g_api.AllocPrimitives(4, 8);
        if (firstPolygonIndex == -1) {
            DestroyEntity(self);
            return;
        }

        poly = &g_PrimBuf[firstPolygonIndex];
        self->firstPolygonIndex = firstPolygonIndex;
        *(s32*)&self->ext.generic.unk7C = poly;
        self->flags |= FLAG_FREE_POLYGONS;

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
    func_801B44B4(0);
}

// taller weight blocking path near cube of zoe
void EntityPathBlockTallWeight(Entity* self) {
    POLY_GT4* poly;
    s16 firstPolygonIndex;
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

        firstPolygonIndex = g_api.AllocPrimitives(4, 8);
        if (firstPolygonIndex == -1) {
            DestroyEntity(self);
            return;
        }

        poly = &g_PrimBuf[firstPolygonIndex];
        self->firstPolygonIndex = firstPolygonIndex;
        *(s32*)&self->ext.generic.unk7C = poly;
        self->flags |= FLAG_FREE_POLYGONS;

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

    func_801B44B4(1);
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
        entity->unk3C = 1;

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
        if (entity->unk48 != 0) {
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
    u8* subId;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180A6C);
        self->unk3C = 2;
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

        if (D_8003BDEC[51] & 1) { /* 0 0 0 0 0 0 0 1 = Half broken */
            tileLayoutPtr = &D_8018112C;
            tilePos = 0x1F1;
            for (i = 0; i < 3; i++) {
                g_CurrentRoomTileLayout.fg[tilePos] = *tileLayoutPtr;
                g_CurrentRoomTileLayout.fg[tilePos + 1] = *(tileLayoutPtr + 3);
                tileLayoutPtr++;
                tilePos += 0x30;
            }
            self->unk3C = 1;
            self->step = 2;
        }
        break;

    case 1:
        if (self->unk48 != 0) {
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
                CreateEntityFromEntity(2, self, newEntity);
                newEntity->subId = 0x13;
                newEntity->zPriority = 0xA9;
                newEntity->posX.i.hi += self->ext.generic.unk84.S16.unk0 * 16;
                newEntity->posY.i.hi += 16;
            }

            subId = &D_8018120C[self->ext.generic.unk84.S16.unk0 * 3];

            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x27, self, newEntity);
                    newEntity->subId = *subId++;
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
                newEntity->subId = 0x43;
            }
            D_8003BDEC[51] |= 1; /* 0 0 0 0 0 0 0 1 = Half broken */
            self->unk3C = 1;
            self->step++;
        }
        break;

    case 2:
        if ((self->unk48 != 0) && (D_80072F20.unk0C & 4)) {
            D_8003BDEC[51] |= 4; /* 0 0 0 0 0 1 0 0 = Broken */
        }
        break;
    }
}

// right side of the merman room rock, breaks when hit
void EntityMermanRockRightSide(Entity* self) {
    u16* tileLayoutPtr;
    Entity* newEntity;
    s32 tilePos;
    u8* subId;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180A6C);
        self->unk3C = 2;
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

        if (D_8003BDEC[51] & 2) { /* 0 0 0 0 0 0 1 0 = Half broken */
            tileLayoutPtr = &D_80181168;
            tilePos = 0x1FD;
            for (i = 0; i < 3; i++) {
                g_CurrentRoomTileLayout.fg[tilePos] = *tileLayoutPtr;
                g_CurrentRoomTileLayout.fg[tilePos + 1] = *(tileLayoutPtr + 3);
                tileLayoutPtr++;
                tilePos += 0x30;
            }
            self->unk3C = 1;
            self->step = 2;
        }
        break;

    case 1:
        if (self->unk48 != 0) {
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
                CreateEntityFromEntity(2, self, newEntity);
                newEntity->subId = 0x13;
                newEntity->zPriority = 0xA9;
                newEntity->posX.i.hi -= self->ext.generic.unk84.S16.unk0 * 16;
                newEntity->posY.i.hi += 16;
            }

            subId = &D_8018120C[self->ext.generic.unk84.S16.unk0 * 3];

            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x27, self, newEntity);
                    newEntity->subId = *subId++;
                    newEntity->accelerationX = (Random() << 8) + 0x8000;
                    newEntity->accelerationY = -Random() * 0x100;
                    newEntity->facing = 1;
                    newEntity->posY.i.hi += -16 + (i * 16);
                }
            }
            self->ext.generic.unk84.S16.unk0++;
        }

        if (self->ext.generic.unk84.S16.unk0 >= 2) {
            D_8003BDEC[51] |= 2; /* 0 0 0 0 0 0 1 0 = Half broken */
            self->unk3C = 1;
            self->step++;
        }
        break;

    case 2:
        if ((self->unk48 != 0) && (D_80072F20.unk0C & 1)) {
            D_8003BDEC[51] |= 8; /* 0 0 0 0 1 0 0 0 = Broken */
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
    s32 animFrame = self->subId & 0xF;
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
        self->unk1E -= 0x20;
        new_var2 = self->posY.i.hi;
        new_var2 += D_80181204[animFrame];
        g_api.CheckCollision(self->posX.i.hi, new_var2, &collider, 0);

        if (collider.unk0 & 1) {
            if (self->accelerationY > 0x40000) {
                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                if (newEntity != 0) {
                    CreateEntityFromEntity(2, self, newEntity);
                    newEntity->subId = 0x11;
                    if (animFrame == 0) {
                        newEntity->subId = 0x13;
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
    s32 animFrame = self->subId & 0xF;
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
        self->unk1E -= 0x20;

        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi + 8, &collider,
                             0);
        if (collider.unk0 & 1) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(6, self, newEntity);
                newEntity->subId = 0x10;
                if (animFrame == 0) {
                    newEntity->subId = 0x13;
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
        self->animCurFrame = self->subId + 0x22;
        self->posX.i.hi = D_80181220[self->subId][0];
        self->posY.i.hi = D_80181220[self->subId][1];
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
            entity->subId = 2;
            entity->ext.generic.unk88.U8.unk1 = 6 - i;
            entity->ext.generic.unk84.S16.unk0 = temp_s3;
            entity->ext.generic.unk88.U8.unk0 = temp_s4;
        }
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B65FC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B6990);

void func_801B75EC(Entity* self) {
    s8* hitbox;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B50);

    case 1:
        self->facing = self[-1].facing;
        self->posX.i.hi = self[-1].posX.i.hi;
        self->posY.i.hi = self[-1].posY.i.hi;
        hitbox = D_80181454;
        hitbox += 4 * D_8018148C[self[-1].animCurFrame];
        self->unk10 = *hitbox++;
        self->unk12 = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;
        if (self[-1].ext.generic.unk84.U8.unk2 != 0) {
            self->step++;
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            self->unk19 = 4;
            self->unk3C = 0;
            if (self->facing != 0) {
                self->accelerationX = -0x24000;
            } else {
                self->accelerationX = 0x24000;
            }
            self->accelerationY = -0x40000;
            self->animCurFrame = 0x23;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;

        case 1:
            MoveEntity();
            self->accelerationY += 0x2800;
            self->unk1E += 0x80;
            if (!(self->unk1E & 0xFFF)) {
                func_801C2598(0x625);
            }
        }
    }
}

// projectile fired from slogra's spear
void EntitySlograSpearProjectile(Entity* self) {
    Entity* entity;

    if (self->flags & 0x100) {
        entity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (entity != NULL) {
            CreateEntityFromEntity(2, self, entity);
            entity->subId = 1;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(&D_80180B5C);
        if (self->facing == 0) {
            self->accelerationX = -0x40000;
        } else {
            self->accelerationX = 0x40000;
        }

    case 1:
        if (AnimateEntity(&D_801813D4, self) == 0) {
            func_801BD114(2);
        }
        break;

    case 2:
        MoveEntity();
        AnimateEntity(&D_801813E4, self);
        break;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B78BC);

void func_801B8CC0(Entity* self) {
    Entity* prevEntity;
    s16 animCurFrame;

    if (self->step == 0) {
        InitializeEntity(D_80180B68);
        self->unk3C = 0;
    }

    prevEntity = &self[-1];
    self->facing = prevEntity->facing;
    self->palette = prevEntity->palette;
    self->posX.i.hi = prevEntity->posX.i.hi;
    self->posY.i.hi = prevEntity->posY.i.hi;
    self->animCurFrame = 0;

    if ((prevEntity->animCurFrame - 32) < 3U) {
        self->animCurFrame = 0x26;
    } else if (prevEntity->animCurFrame == 35) {
        self->animCurFrame = 0x27;
    } else if ((prevEntity->animCurFrame - 36) < 2U) {
        self->animCurFrame = 0x28;
    }

    if (prevEntity->objectId != 0x51) {
        DestroyEntity(self);
    }
}

// small red projectile from gaibon
void EntitySmallGaibonProjectile(Entity* self) {
    if (self->flags & 0x100) {
        self->pfnUpdate = EntityExplosion;
        self->unk19 = 0;
        self->step = 0;
        self->objectId = 2;
        self->subId = 0;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B74);
        self->animSet = 2;
        self->animCurFrame = 1;
        self->unk19 = 5;
        self->unk1A = 0xC0;
        self->accelerationX = (rcos(self->unk1E) * 0x28000) >> 0xC;
        self->accelerationY = (rsin(self->unk1E) * 0x28000) >> 0xC;
        self->palette = 0x81B6;
        self->unk1E -= 0x400;

    case 1:
        MoveEntity();
        AnimateEntity(D_801815E0, self);
        break;
    }
}

void EntityLargeGaibonProjectile(Entity* self) {
    Entity* newEntity;

    if (self->flags & 0x100) {
        self->pfnUpdate = EntityExplosion;
        self->objectId = 2;
        self->unk19 = 0;
        self->step = 0;
        self->subId = 1;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(&D_80180B80);
        if (self->subId == 0) {
            self->animSet = 2;
            self->unk19 = 4;
            self->accelerationX = (rcos(self->unk1E) * 0x38000) >> 0xC;
            self->accelerationY = (rsin(self->unk1E) * 0x38000) >> 0xC;
            self->palette = 0x81B6;
            self->unk1E -= 0x400;
        } else {
            self->animSet = 14;
            self->unk5A = 0x79;
            self->unk19 = 0xD;
            self->unk1A = 0x100;
            self->unk6C = 0x80;
            self->palette = 0x81F3;
            self->blendMode = 0x30;
            self->step = 2;
            self->unk3C = 0;
            self->flags |= 0x2000;
        }
        break;

    case 1:
        MoveEntity();
        AnimateEntity(&D_801815EC, self);
        if (!(g_blinkTimer & 3)) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x54, self, newEntity);
                newEntity->subId = 1;
                newEntity->unk1E = self->unk1E;
                newEntity->zPriority = self->zPriority + 1;
            }
        }
        break;

    case 2:
        self->unk6C += 0xFE;
        self->unk1A -= 4;
        if (AnimateEntity(&D_801815FC, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

s32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

void Update(void) {
    s16 i;
    Entity* entity;
    s32* unk;

    for (i = 0; i < 0x20; i++) {
        if (D_801D33F4[i]) {
            D_801D33F4[i]--;
        }
    }

    unk = &D_80097410;
    if (*unk) {
        if (!--*unk) {
            g_api.FreePrimitives(D_80097414);
        }
    }

    for (entity = &g_Entities[STAGE_ENTITY_START];
         entity < &g_Entities[TOTAL_ENTITY_COUNT]; entity++) {
        if (!entity->pfnUpdate)
            continue;

        if (entity->step) {
            s32 unk34 = entity->flags;
            if (unk34 & FLAG_DESTROY_IF_OUT_OF_CAMERA) {
                s16 posX = i = entity->posX.i.hi;
                s16 posY = entity->posY.i.hi;
                if (unk34 & FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA) {
                    if ((u16)(posX + 64) > 384 || (u16)(posY + 64) > 352) {
                        DestroyEntity(entity);
                        continue;
                    }
                } else {
                    if ((u16)(posX + 128) > 512 || (u16)(posY + 128) > 480) {
                        DestroyEntity(entity);
                        continue;
                    }
                }
            }

            if ((unk34 & 0x02000000)) {
                s16 posY = entity->posY.i.hi + g_Camera.posY.i.hi;
                s16 test = (g_CurrentRoom.vSize * 256) + 128;
                if (posY > test) {
                    DestroyEntity(entity);
                    continue;
                }
            }

            if (unk34 & 0xF) {
                entity->palette =
                    D_8018164C[(entity->unk49 << 1) | (unk34 & 1)];
                entity->flags--;
                if ((entity->flags & 0xF) == 0) {
                    entity->palette = entity->unk6A;
                    entity->unk6A = 0;
                }
            }

            if (!(unk34 & 0x20000000) || (unk34 & 0x10000000) ||
                ((u16)(entity->posX.i.hi + 64) <= 384) &&
                    ((u16)(entity->posY.i.hi + 64) <= 352)) {
                if (!entity->unk58 || (entity->unk58--, unk34 & 0x100000)) {
                    if (!D_800973FC || unk34 & 0x2100 ||
                        (unk34 & 0x200 && !(D_8003C8C4 & 3))) {
                        g_CurrentEntity = entity;
                        entity->pfnUpdate(entity);
                        entity->unk44 = 0;
                        entity->unk48 = 0;
                    }
                }
            }
        } else {
            g_CurrentEntity = entity;
            entity->pfnUpdate(entity);
            entity->unk44 = 0;
            entity->unk48 = 0;
        }
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B93E8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B94F0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityNumericDamage);

void CreateEntityFromLayout(Entity* entity, LayoutObject* initDesc) {
    DestroyEntity(entity);
    entity->objectId = initDesc->objectId & 0x3FF;
    entity->pfnUpdate = PfnEntityUpdates[entity->objectId];
    entity->posX.i.hi = initDesc->posX - g_Camera.posX.i.hi;
    entity->posY.i.hi = initDesc->posY - g_Camera.posY.i.hi;
    entity->subId = initDesc->subId;
    entity->objectRoomIndex = initDesc->objectRoomIndex >> 8;
    entity->unk68 = (initDesc->objectId >> 0xA) & 7;
}

void CreateEntityWhenInVerticalRange(LayoutObject* layoutObj) {
    s16 yClose;
    s16 yFar;
    s16 posY;
    Entity* entity;

    posY = g_Camera.posY.i.hi;
    yClose = posY - 0x40;
    yFar = posY + 0x120;
    if (yClose < 0) {
        yClose = 0;
    }

    posY = layoutObj->posY;
    if (posY < yClose) {
        return;
    }

    if (yFar < posY) {
        return;
    }

    switch (layoutObj->objectId & 0xE000) {
    case 0x0:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->objectRoomIndex];
        if (entity->objectId == 0) {
            CreateEntityFromLayout(entity, layoutObj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->objectRoomIndex];
        CreateEntityFromLayout(entity, layoutObj);
        break;
    }
}

void CreateEntityWhenInHorizontalRange(LayoutObject* layoutObj) {
    s16 xClose;
    s16 xFar;
    s16 posX;
    Entity* entity;

    posX = g_Camera.posX.i.hi;
    xClose = posX - 0x40;
    xFar = posX + 0x140;
    if (xClose < 0) {
        xClose = 0;
    }

    posX = layoutObj->posX;
    if (posX < xClose) {
        return;
    }

    if (xFar < posX) {
        return;
    }

    switch (layoutObj->objectId & 0xE000) {
    case 0x0:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->objectRoomIndex];
        if (entity->objectId == 0) {
            CreateEntityFromLayout(entity, layoutObj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->objectRoomIndex];
        CreateEntityFromLayout(entity, layoutObj);
        break;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BAFA0);

extern LayoutObject* D_801D2768;
void func_801BAFEC(s16 arg0) {
    while (true) {
        if ((D_801D2768->posX != 0xFFFF) &&
            ((arg0 >= D_801D2768->posX) || (D_801D2768->posX == 0xFFFE))) {
            break;
        }
        D_801D2768--;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BB044);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BB140);

void func_801BB254(s16 arg0) {
    while (true) {
        if ((D_801D276C->posY != (u16)~1) && !(D_801D276C->posY < arg0)) {
            break;
        }
        D_801D276C++;
    }
}

extern LayoutObject* D_801D276C;
void func_801BB2A0(s16 arg0) {
    while (true) {
        if ((D_801D276C->posY != 0xFFFF) &&
            ((arg0 >= D_801D276C->posY) || (D_801D276C->posY == 0xFFFE))) {
            break;
        }
        D_801D276C--;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BB2F8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BB3F4);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", InitRoomEntities);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BB680);

void CreateEntityFromCurrentEntity(u16 objectId, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.i.hi = g_CurrentEntity->posX.i.hi;
    entity->posY.i.hi = g_CurrentEntity->posY.i.hi;
}

void CreateEntityFromEntity(u16 objectId, Entity* source, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
}

s32 func_801BB824(Entity* e) {
    s16 diff;

    diff = PLAYER.posX.i.hi - e->posX.i.hi;
    diff = ABS(diff);

    if (diff >= 17) {
        diff = 0;
    } else {
        diff = PLAYER.posY.i.hi - e->posY.i.hi;
        diff = ABS(diff);
        diff = diff < 33;
    }

    return diff;
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityRedDoor);

void DestroyEntity(Entity* item) {
    s32 i;
    s32 length;
    u32* ptr;

    if (item->flags & FLAG_FREE_POLYGONS) {
        g_api.FreePrimitives(item->firstPolygonIndex);
    }

    ptr = (u32*)item;
    length = sizeof(Entity) / sizeof(s32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

void DestroyEntityFromIndex(s16 index) {
    Entity* entity = &g_Entities[index];

    while (entity < &D_8007EF1C) {
        DestroyEntity(entity);
        entity++;
    }
}

void PreventEntityFromRespawning(Entity* entity) {
    if (entity->objectRoomIndex) {
        u32 value = (entity->objectRoomIndex - 1);
        u16 index = value / 32;
        u16 bit = value % 32;
        g_entityDestroyed[index] |= 1 << bit;
    }
}

#include "st/AnimateEntity.h"

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BC6BC);

/*
 * Returns the absolute distance from g_CurrentEntity to player in the X Axis
 */
s32 GetPlayerDistanceX(void) {
    s16 yDistance = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

/*
 * Returns the absolute distance from g_CurrentEntity to player in the Y Axis
 */
s32 GetPlayerDistanceY(void) {
    s32 yDistance = g_CurrentEntity->posY.i.hi - PLAYER.posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

/**
 * Returns the player's side position relative to g_CurrentEntity
 * 0 = Player is on the right side
 * 1 = Player is on the left side
 * 2 = Player is above
 */
s16 GetPlayerSide(void) {
    s16 side = g_CurrentEntity->posX.i.hi > PLAYER.posX.i.hi;

    if (g_CurrentEntity->posY.i.hi > PLAYER.posY.i.hi) {
        side |= 2;
    }
    return side;
}

void MoveEntity(void) {
    g_CurrentEntity->posX.val += g_CurrentEntity->accelerationX;
    g_CurrentEntity->posY.val += g_CurrentEntity->accelerationY;
}

void FallEntity(void) {
    if (g_CurrentEntity->accelerationY < FALL_TERMINAL_VELOCITY) {
        g_CurrentEntity->accelerationY += FALL_GRAVITY;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BC8E4);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BCB5C);

Entity* AllocEntity(Entity* start, Entity* end) {
    Entity* current = start;

    while (current < end) {
        if (current->objectId == 0) {
            DestroyEntity(current);
            return current;
        }
        current++;
    }
    return NULL;
}

s32 func_801BCDA4(u8 arg0, s16 arg1) { return D_80181A50[arg0] * arg1; }

s16 func_801BCDD0(u8 arg0) { return D_80181A50[arg0]; }

void func_801BCDEC(s32 arg0, s16 arg1) {
    g_CurrentEntity->accelerationX = func_801BCDA4(arg0, arg1);
    g_CurrentEntity->accelerationY = func_801BCDA4(arg0 - 0x40, arg1);
}

u8 func_801BCE58(s16 x, s16 y) { return ((ratan2(y, x) >> 4) + 0x40); }

u8 func_801BCE90(Entity* a, Entity* b) {
    s32 diffX = (u16)b->posX.i.hi - (u16)a->posX.i.hi;
    s32 diffY = (u16)b->posY.i.hi - (u16)a->posY.i.hi;
    return func_801BCE58(diffX, diffY);
}

u8 func_801BCED8(s32 x, s32 y) {
    s32 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s32 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return func_801BCE58(diffX, diffY);
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BCF20);

void func_801BCF78(u16 slope, s16 speed) {
    Entity* entity;
    s32 moveX;
    s32 moveY;

    moveX = rcos(slope) * speed;
    entity = g_CurrentEntity;
    if (moveX < 0) {
        moveX += 15;
    }
    entity->accelerationX = moveX >> 4;

    moveY = rsin(slope) * speed;
    entity = g_CurrentEntity;
    if (moveY < 0) {
        moveY += 15;
    }
    entity->accelerationY = moveY >> 4;
}

u16 func_801BD004(s16 x, s16 y) { return ratan2(y, x); }

u16 func_801BD034(Entity* a, Entity* b) {
    s32 diffX = b->posX.i.hi - a->posX.i.hi;
    s32 diffY = b->posY.i.hi - a->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_801BD06C(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s16 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return ratan2(diffY, diffX);
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BD0B4);

void func_801BD114(u8 step) {
    g_CurrentEntity->step = step;
    g_CurrentEntity->step_s = 0;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

void func_801BD134(u8 arg0) {
    g_CurrentEntity->step_s = arg0;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BD150);

void InitializeEntity(u16 arg0[]) {
    u16 enemyId;
    EnemyDef* enemyDef;

    g_CurrentEntity->animSet = *arg0++;
    g_CurrentEntity->animCurFrame = *arg0++;
    g_CurrentEntity->unk5A = *arg0++;
    g_CurrentEntity->palette = *arg0++;

    enemyId = *arg0++;
    g_CurrentEntity->enemyId = enemyId;
    enemyDef = &g_api.enemyDefs[enemyId];
    g_CurrentEntity->hitPoints = enemyDef->hitPoints;
    g_CurrentEntity->attack = enemyDef->attack;
    g_CurrentEntity->attackElement = enemyDef->attackElement;
    g_CurrentEntity->unk3C = enemyDef->unkC;
    g_CurrentEntity->hitboxWidth = enemyDef->hitboxWidth;
    g_CurrentEntity->hitboxHeight = enemyDef->hitboxHeight;
    g_CurrentEntity->flags = enemyDef->unk24;
    g_CurrentEntity->unk10 = 0;
    g_CurrentEntity->unk12 = 0;
    g_CurrentEntity->step_s = 0;
    g_CurrentEntity->step++;
    if (g_CurrentEntity->zPriority == 0) {
        g_CurrentEntity->zPriority = g_zEntityCenter.S16.unk0 - 0xC;
    }
}

void EntityDummy(Entity* arg0) {
    if (arg0->step == 0) {
        arg0->step++;
    }
}

s32 func_801BD308(u16* hitSensors, s16 sensorCount) {
    s32 accelerationX = g_CurrentEntity->accelerationX;
    Collider collider;
    u16 temp_a1;
    s16 x;
    s16 y;
    s16 i;

    if (accelerationX != 0) {
        x = g_CurrentEntity->posX.i.hi;
        y = g_CurrentEntity->posY.i.hi;
        for (i = 0; i < sensorCount; i++) {
            if (accelerationX < 0) {
                s16 newX = x + *hitSensors++;
                x = newX;
            } else {
                s16 newX = x - *hitSensors++;
                x = newX;
            }

            y += *hitSensors++;
            g_api.CheckCollision(x, y, &collider, 0);
            if (collider.unk0 & 2 &&
                ((!(collider.unk0 & 0x8000)) || (i != 0))) {
                return 2;
            }
        }
        return 0;
    }
}

void func_801BD430(u16* hitSensors, s16 sensorCount) {
    Collider collider;
    s16 i;
    s32 accelerationX;
    s16 x;
    s16 y;

    accelerationX = g_CurrentEntity->accelerationX;
    if (accelerationX == 0)
        return;
    x = g_CurrentEntity->posX.i.hi;
    y = g_CurrentEntity->posY.i.hi;
    for (i = 0; i < sensorCount; i++) {
        if (accelerationX < 0) {
            x = x + *hitSensors++;
        } else {
            x = x - *hitSensors++;
        }

        y += *hitSensors++;
        g_api.CheckCollision(x, y, &collider, 0);
        if (collider.unk0 & 2 && (!(collider.unk0 & 0x8000) || i != 0)) {
            if (accelerationX < 0) {
                g_CurrentEntity->posX.i.hi += collider.unk1C;
            } else {
                g_CurrentEntity->posX.i.hi += collider.unk14;
            }
            return;
        }
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BD588);

void ReplaceBreakableWithItemDrop(Entity* self) {
    u16 subId;

    PreventEntityFromRespawning(self);

#if STAGE != STAGE_ST0
    if (!(g_Status.relics[10] & 2)) {
        DestroyEntity(self);
        return;
    }
#endif

    subId = self->subId &= 0xFFF;

    if (subId < 0x80) {
        self->objectId = ENTITY_PRICE_DROP;
        self->pfnUpdate = (PfnEntityUpdate)EntityPrizeDrop;
        self->animFrameDuration = 0;
        self->animFrameIdx = 0;
    } else {
        subId -= 0x80;
        self->objectId = ENTITY_INVENTORY_DROP;
        self->pfnUpdate = (PfnEntityUpdate)EntityEquipItemDrop;
    }

    self->subId = subId;
    self->unk6D = 0x10;
    self->step = 0;
}

void func_801BD984(void) {
    s32 temp_v1;
    Entity* entity;

    entity = g_CurrentEntity;
    if (entity->accelerationY >= 0) {
        temp_v1 =
            entity->ext.generic.unk88.S16.unk0 + entity->ext.generic.unk84.unk;
        entity->ext.generic.unk84.unk = temp_v1;
        entity->accelerationX = temp_v1;
        if (temp_v1 == 0x10000 || temp_v1 == -0x10000) {
            entity->ext.generic.unk88.S16.unk0 =
                -entity->ext.generic.unk88.S16.unk0;
        }
        entity = g_CurrentEntity;
    }
    NOP;

    if (entity->accelerationY < 0x00004000) {
        entity->accelerationY += 0x2000;
    }
}

void func_801BDA08(u16 arg0) {
    Collider res;

    if (g_CurrentEntity->accelerationX < 0) {
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi - 7, &res, 0);
        if (res.unk0 & 5) {
            g_CurrentEntity->accelerationY = 0;
        }
    }

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                         g_CurrentEntity->posY.i.hi + 7, &res, 0);

    if (arg0) {
        if (!(res.unk0 & 5)) {
            MoveEntity();
            FallEntity();
            return;
        }

        g_CurrentEntity->accelerationX = 0;
        g_CurrentEntity->accelerationY = 0;

        if (res.unk0 & 4) {
            g_CurrentEntity->posY.val += 0x2000;
        } else {
            g_CurrentEntity->posY.i.hi += res.unk18;
        }
    } else {
        if (!(res.unk0 & 5)) {
            MoveEntity();
            func_801BD984();
        }
    }
}

void CollectHeart(u16 heartSize) {
    s32* hearts;

    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    hearts = &g_Status.hearts;
    *hearts += c_HeartPrizes[heartSize];

    if (g_Status.heartsMax < *hearts) {
        *hearts = g_Status.heartsMax;
    }

    DestroyEntity(g_CurrentEntity);
}

void CollectGold(u16 goldSize) {
    s32 *gold, *unk;
    u16 goldSizeIndex;

    g_api.PlaySfx(NA_SE_PL_COLLECT_GOLD);
    gold = &g_Status.gold;
    goldSizeIndex = goldSize - 2;
    *gold += c_GoldPrizes[goldSizeIndex];
    if (*gold > MAX_GOLD) {
        *gold = MAX_GOLD;
    }

    unk = &D_80097410;
    if (*unk) {
        g_api.FreePrimitives(D_80097414);
        *unk = 0;
    }

    func_801C3E14(D_80181DC4[goldSizeIndex], 1);
    DestroyEntity(g_CurrentEntity);
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", CollectSubweapon);

void CollectHeartVessel(void) {
    if (g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
        g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
        g_Status.hearts += HEART_VESSEL_RICHTER;

        if (g_Status.heartsMax < g_Status.hearts) {
            g_Status.hearts = g_Status.heartsMax;
        }
    } else {
        g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
        g_api.func_800FE044(HEART_VESSEL_INCREASE, 0x4000);
    }
    DestroyEntity(g_CurrentEntity);
}

void CollectLifeVessel(void) {
    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_api.func_800FE044(5, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

void DestroyCurrentEntity(void) { DestroyEntity(g_CurrentEntity); }
