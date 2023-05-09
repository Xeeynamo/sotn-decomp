/*
 * File: 377D4.c
 * Overlay: NO3
 * Description: Castle Entrance
 */

#include "no3.h"

// vase in the room with the door to the caverns
void EntityCavernDoorVase(Entity* arg0) {
    s32 temp_v0;
    ObjInit2* temp_s0 = &D_80180BFC[arg0->subId];

    if (arg0->step == 0) {
        InitializeEntity(D_80180B00);
        arg0->animSet = temp_s0->animSet;
        arg0->zPriority = temp_s0->zPriority;
        arg0->facing = temp_s0->unk4.U8.unk0;
        arg0->unk5A = temp_s0->unk4.U8.unk1;
        arg0->palette = temp_s0->palette;
        arg0->unk19 = temp_s0->unk8;
        arg0->blendMode = temp_s0->blendMode;
        temp_v0 = temp_s0->unkC;
        if (temp_v0 != 0) {
            arg0->flags = temp_v0;
        }
    }

    AnimateEntity(temp_s0->unk10, arg0);
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityUnkId12);

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

void EntityUnkId16(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180AD0);
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

// lightning and sound for background
INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityBackgroundLightning);

// window that opens and shuts in the background
INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityShuttingWindow);

// main door to the castle that closes during intro
INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityCastleDoor);

// bushes in parallax background
INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityBackgroundBushes);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityUnkId1C);

// transparent water "plane" seen in the merman room
INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityTransparentWater);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", func_801B94F0);

// lever and platform to open caverns door
void EntityCavernDoorLever(Entity* entity) {
    s32 posX;
    s32 posY;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180B18);
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
        InitializeEntity(D_80180B18);
        self->animCurFrame = 17;
        self->ext.generic.unk88.unk = self->posX.val;
        self->ext.generic.unk88.unk = self->posX.val; // ? WTF

    case 1:
        player = &PLAYER;
        self->ext.generic.unk84.S8.unk0 = temp2 = func_801C5D18(self, 6, 5, 4);

        if (temp2 != 0) {
            temp = self->posX.i.hi;
            temp -= self->ext.generic.unk88.S16.unk2;
            player->posX.i.hi += temp;
            player->posY.i.hi++;
        }
        self->ext.generic.unk88.unk = self->posX.val;
        self->ext.generic.unk8C.modeS32 = self->posY.val;
    }
}

// door blocking way to the Underground Caverns
void EntityCavernDoor(Entity* self) {
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
        InitializeEntity(D_80180B18);
        self->animCurFrame = 10;
        self->zPriority = 0x9F;

        tileLayoutPtr = &D_80181230[0];
        if (D_8003BDEC[48] != 0) {
            tileLayoutPtr = &D_80181230[3];
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
            *(s32*)&self->ext.generic.unk7C = poly;
            self->flags |= FLAG_FREE_POLYGONS;
            while (poly != NULL) {
                poly->u0 = poly->v0 = 1;
                poly->r0 = 64;
                poly->b0 = 128;
                poly->g0 = 96;
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
            g_api.PlaySfx(NA_SE_EV_SWITCH_CLICK);
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

        for (tilePos = 0x76, tileLayoutPtr = &D_80181230[3], i = 0; i < temp;
             tileLayoutPtr++, tilePos += 0x10, i++) {
            g_CurrentRoomTileLayout.fg[tilePos] = *tileLayoutPtr;
        }

        if (!(g_blinkTimer & 1)) {
            poly = func_801D6DB8((POLY_GT4*)(*(s32*)&self->ext.generic.unk7C));
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
                func_801B94F0(poly);
            }
        }
    }
}

typedef enum { WEIGHT_SMALL, WEIGHT_TALL } WeightSelect;

void func_801B9C44(WeightSelect weight) {
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
    s32 temp_a0 = func_801C5D18(entity, 8, 4, 4);
    Entity* player = &PLAYER;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180B18);
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
        InitializeEntity(D_80180B18);
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

        if (D_8003BDEC[49] != 0) {
            self->step = 3;
            self->posY.i.hi += 111;
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

    if ((self->step < 3) && (func_801C5D18(self, 16, 16, 5) & 4)) {
        Entity* player = &PLAYER;

        player->posY.i.hi++;
    }
    func_801B9C44(WEIGHT_SMALL);
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
        InitializeEntity(D_80180B18);
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

    func_801B9C44(WEIGHT_TALL);
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

// trap door that leads to underground garden in saturn version.
// also opens the one leading to the save room
void EntityTrapDoor(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180B18);
        entity->animCurFrame = 27;
        entity->zPriority = 0x6A;
        entity->hitboxWidth = 16;
        entity->hitboxHeight = 4;
        entity->unk3C = 1;

        if (g_TrapDoorFlag == 0) {
            if (PLAYER.posY.val < entity->posY.val) {
                g_CurrentRoomTileLayout.fg[0xA8E / 2] = 0x129;
                g_CurrentRoomTileLayout.fg[0xA90 / 2] = 0x132;
                DestroyEntity(entity);
                break;
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
        AnimateEntity(D_80181240, entity);
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
        InitializeEntity(D_80180ADC);
        self->unk3C = 2;
        self->hitboxWidth = 16;
        self->hitboxHeight = 24;

        tileLayoutPtr = &D_8018127C;
        tilePos = 0x1F1;
        for (i = 0; i < 3; i++) {
            g_CurrentRoom.bg[0].layout[tilePos] = *tileLayoutPtr;
            g_CurrentRoom.bg[0].layout[tilePos + 1] = *(tileLayoutPtr + 3);
            tileLayoutPtr++;
            tilePos += 0x30;
        }

        if (D_8003BDEC[51] & 1) { /* 0 0 0 0 0 0 0 1 = Half broken */
            tileLayoutPtr = &D_80181264;
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
            tileLayoutPtr = &D_80181258[self->ext.generic.unk84.S16.unk0 * 6];
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

            subId = &D_80181344[self->ext.generic.unk84.S16.unk0 * 3];

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
        InitializeEntity(D_80180ADC);
        self->unk3C = 2;
        self->hitboxWidth = 16;
        self->hitboxHeight = 24;

        tileLayoutPtr = &D_801812B8;
        tilePos = 0x1FD;
        for (i = 0; i < 3; i++) {
            g_CurrentRoom.bg[0].layout[tilePos] = *tileLayoutPtr;
            g_CurrentRoom.bg[0].layout[tilePos + 1] = *(tileLayoutPtr + 3);
            tileLayoutPtr++;
            tilePos += 0x30;
        }

        if (D_8003BDEC[51] & 2) { /* 0 0 0 0 0 0 1 0 = Half broken */
            tileLayoutPtr = &D_801812A0;
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
            tileLayoutPtr = &D_80181294[(self->ext.generic.unk84.S16.unk0 * 6)];
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

            subId = &D_80181344[self->ext.generic.unk84.S16.unk0 * 3];

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

void EntityUnkId26(Entity* self) {
    u16* tileLayoutPtr;
    s32 tileLayoutPos;
    s32 i;
    s32 j;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180ADC);
        if (D_8003BDEC[58] != 0) {
            self->step = 2;
        }
        break;

    case 1:
        if ((D_8003BDEC[51] & 12) == 12) {
            func_801CAD28(0x644);
            self->step++;
        }
        break;

    case 2:
        for (tileLayoutPtr = &D_801812E2, i = 0; i < 3; i++) {
            tileLayoutPos = 0x420 + i;
            for (j = 0; j < 5; tileLayoutPos += 0x30, j++, tileLayoutPtr++) {
                g_CurrentRoomTileLayout.fg[tileLayoutPos] = *tileLayoutPtr;
            }
        }

        for (tileLayoutPtr = &D_8018131E, i = 0; i < 3; i++) {
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

// falling rock that breaks into dust
void EntityFallingRock2(Entity* self) {
    s32 animFrame = self->subId & 0xF;
    Collider collider;
    Entity* newEntity;
    s32 temp_a0;
    s32 var_a1;
    s32 new_var2;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B18);
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
        new_var2 += D_8018133C[animFrame];
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
            self->posY.i.hi = self->posY.i.hi + collider.unk18;
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

INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityUnkId5C);

// falling rock with puff of smoke when it disappears. I think part of the
// merman room breakable rock
void EntityFallingRock(Entity* self) {
    s32 animFrame = self->subId & 0xF;
    Collider collider;
    Entity* newEntity;
    s16 rndAngle;
    s32 rnd;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B18);
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

INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", func_801BB548);

// sky animation during death cutscene
INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityDeathSkySwirl);

void EntityUnkId29(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180B18);
        self->zPriority = 0x2A;
        self->flags &= ~FLAG_UNK_08000000;
        self->facing = Random() & 1;
        g_api.func_80134714(0x665, 0x40, (self->posX.i.hi >> 0x4) - 8);
    }
    if (AnimateEntity(D_80181390, self) == 0) {
        DestroyEntity(self);
    }
}

void EntityUnkId2A(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(D_80180B18);
        entity->zPriority = 0x29;
        entity->flags &= ~FLAG_UNK_08000000;
        entity->animCurFrame = entity->subId + 0x22;
        entity->posX.i.hi = D_8018139C[entity->subId << 1];
        entity->posY.i.hi = D_8018139E[entity->subId << 1];
        entity->ext.generic.unk80.modeS16.unk0 = 5;
    }
    entity->ext.generic.unk80.modeS16.unk0--;
    if ((entity->ext.generic.unk80.modeS16.unk0 << 0x10) == 0) {
        DestroyEntity(entity);
    }
}

// switch that goes downwards when you stand on it
void EntitySwitch(Entity* entity) {
    s32 temp_a0 = func_801C5D18(entity, 8, 4, 4);
    Entity* player = &PLAYER;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180B18);
        entity->animCurFrame = 9;
        entity->zPriority = 0x5E;
        if (D_8003BDEC[0x32] != 0) {
            entity->step = 2;
            entity->posY.i.hi += 4;
        }
        break;

    case 1:
        if (temp_a0 != 0) {
            player->posY.i.hi++;
            entity->posY.val += 0x4000;
            if ((g_Camera.posY.i.hi + entity->posY.i.hi) > 193) {
                entity->posY.i.hi = 193 - g_Camera.posY.i.hi;
                D_8003BDEC[0x32] = 1;
                g_api.PlaySfx(0x608);
                entity->step++;
            }
        }
        break;
    }
}

// door preventing access to warp room / heart
void EntityHeartRoomGoldDoor(Entity* self) {
    s16 firstPolygonIndex;
    Entity* newEntity;
    POLY_GT4* poly;
    s32 tilePos;
    s32 temp;
    s32 temp2;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B18);
        self->animCurFrame = 37;
        self->zPriority = 0x5E;

        if (D_8003BDEC[50] != 0) {
            for (tilePos = 0x48, i = 7, self->step = 128,
                self->animCurFrame = 0;
                 i >= 0; tilePos += 0x10, i--) {
                g_CurrentRoomTileLayout.fg[tilePos] = 0;
            }
            break;
        }

        firstPolygonIndex = g_api.AllocPrimitives(1, 64);
        if (firstPolygonIndex == -1) {
            DestroyEntity(self);
            return;
        }

        poly = &g_PrimBuf[firstPolygonIndex];
        self->firstPolygonIndex = firstPolygonIndex;
        *(s32*)&self->ext.generic.unk7C = poly;
        self->flags |= FLAG_FREE_POLYGONS;
        while (poly != NULL) {
            poly->v0 = 1;
            poly->u0 = 1;
            poly->r0 = 64;
            poly->b0 = 128;
            poly->g0 = 96;
            poly->pad2 = self->zPriority + 0x18;
            poly->pad3 = 8;
            poly->p3 = 0;
            poly = (POLY_GT4*)poly->tag;
        }

        for (tilePos = 0x48, temp = 0x4FA, i = 7; i >= 0;
             tilePos += 0x10, i--) {
            g_CurrentRoomTileLayout.fg[tilePos] = temp;
        }
        break;

    case 1:
        if (D_8003BDEC[50] != 0) {
            g_api.PlaySfx(0x607);
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

        temp = temp2 = self->posY.i.hi - 112;
        if (temp2 < 0) {
            temp2 = self->posY.i.hi - 97;
        }

        temp = temp2 >> 4;
        if (temp >= 9) {
            temp = 8;
            self->step = 3;
        }

        for (tilePos = 0x48, i = 0; i < temp; tilePos += 0x10, i++) {
            g_CurrentRoomTileLayout.fg[tilePos] = 0;
        }

        if (!(g_blinkTimer & 1)) {
            poly = func_801D6DB8((POLY_GT4*)(*(s32*)&self->ext.generic.unk7C));
            if (poly != NULL) {
                poly->p3 = 1;
            }

            if (!(g_blinkTimer & 0xF)) {
                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(6, self, newEntity);
                    newEntity->posY.i.hi = 188;
                    newEntity->posX.i.hi += -8 + (Random() & 0xF);
                    newEntity->subId = 0x10;
                    newEntity->unk1A = newEntity->unk1C = 192;
                    newEntity->unk19 |= 3;
                }
            }
        }
        break;
    }

    if (self->flags & FLAG_FREE_POLYGONS) {
        for (poly = *(s32*)&self->ext.generic.unk7C; poly != NULL;
             poly = (POLY_GT4*)poly->tag) {
            if (poly->p3 != 0) {
                func_801B94F0(poly);
            }
        }
    }
}

void EntityUnkId49(Entity* entity) {
    u16 temp;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180ADC);
        break;
    case 1:
        temp = g_CurrentRoomTileLayout.fg[9];
        g_CurrentRoomTileLayout.fg[6] = temp;
        temp = g_CurrentRoomTileLayout.fg[10];
        g_CurrentRoomTileLayout.fg[7] = temp;
        temp = g_CurrentRoomTileLayout.fg[0x39];
        g_CurrentRoomTileLayout.fg[0x36] = temp;
        temp = g_CurrentRoomTileLayout.fg[0x3A];
        g_CurrentRoomTileLayout.fg[0x37] = temp;
        temp = g_CurrentRoomTileLayout.fg[0x69];
        g_CurrentRoomTileLayout.fg[0x66] = temp;
        temp = g_CurrentRoomTileLayout.fg[0x6A];
        g_CurrentRoomTileLayout.fg[0x67] = temp;
        entity->step++;
        break;
    }
}
