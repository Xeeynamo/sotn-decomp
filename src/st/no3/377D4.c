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
            arg0->unk34 = temp_v0;
        }
    }

    AnimateEntity(temp_s0->unk10, arg0);
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId12);

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

// matches except for nops after loads
#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId16);
#else
extern u8 D_8003CB25;
extern u8 D_8003CB26;
extern u8 D_8003CB27;
extern u8 D_80054319;
extern u8 D_8005431A;
extern u8 D_8005431B;
extern u16 D_80180AD0;

void func_801B7B98(Entity* arg0) {
    switch (arg0->step) {
    case 0:
        InitializeEntity(&D_80180AD0);
        arg0->unk7C.S8.unk0 = 0x10U;
        arg0->unk7C.S8.unk1 = 8U;
        arg0->unk7E.modeU8.unk0 = 0x38U;
        /* fallthrough */
    case 1:
        D_8003CB25 = arg0->unk7C.S8.unk0;
        D_8003CB26 = arg0->unk7C.S8.unk1;
        D_8003CB27 = arg0->unk7E.modeU8.unk0;
        D_80054319 = arg0->unk7C.S8.unk0;
        D_8005431A = arg0->unk7C.S8.unk1;
        D_8005431B = arg0->unk7E.modeU8.unk0;
        break;
    }
}
#endif

// lightning and sound for background
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityBackgroundLightning);

// window that opens and shuts in the background
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityShuttingWindow);

// main door to the castle that closes during intro
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityCastleDoor);

// bushes in parallax background
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityBackgroundBushes);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId1C);

// transparent water "plane" seen in the merman room
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityTransparentWater);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B94F0);

// lever and platform to open caverns door
void EntityCavernDoorLever(Entity* entity) {
    s32 posX;
    s32 posY;

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180B18);
        entity->animCurFrame = 18;
        entity->unk1E = -0x200;
        entity->unk19 |= 4;
        CreateEntityFromEntity(0x1E, entity, &entity[1]);
        if (*D_8003BE1C != 0) {
            entity->unk1E = 0;
        }

    case 1:
        if (entity[1].unk84.S8.unk0 != 0) {
            entity->unk1E += 4;
            if (entity->unk1E > 0) {
                entity->unk1E = 0;
                if (*D_8003BE1C == 0) {
                    g_api.PlaySfx(0x675);
                }
                *D_8003BE1C = 1;
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
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityCavernDoorPlatform);

// door blocking way to caverns
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityCavernDoor);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B9C44);

// switch that clicks when you step on it
void EntityClickSwitch(Entity* entity) {
    s32 temp_a0 = func_801C5D18(entity, 8, 4, 4);
    Entity* player = &PLAYER;

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180B18);
        entity->animCurFrame = 9;
        entity->zPriority = 0x5E;
        if (*D_8003BE1D != 0) {
            entity->step = 2;
            entity->posY.i.hi += 4;
        }
        break;

    case 1:
        if (temp_a0 != 0) {
            player->posY.i.hi++;
            entity->posY.val += 0xC000;
            if ((D_80073092 + entity->posY.i.hi) > 160) {
                entity->posY.i.hi = 160 - D_80073092;
                g_api.PlaySfx(NA_SE_EV_SWITCH_CLICK);
                *D_8003BE1D = 1;
                entity->step++;
            }
        }
        break;
    }
}

// smaller weight blocking path near cube of zoe
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityZoeSmallWeight);

// taller weight blocking path near cube of zoe
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityZoeTallWeight);

// trap door that leads to underground garden in saturn version.
// also opens the one leading to the save room
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityTrapDoor);

// left side of the breakable rock, drops pot roast
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityMermanRockLeftSide);

// right side of the merman room rock, breaks when hit
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityMermanRockRightSide);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId26);

// falling rock that breaks into dust
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityFallingRock2);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId5C);

// falling rock with puff of smoke when it disappears. I think part of the
// merman room breakable rock
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityFallingRock);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BB548);

// sky animation during death cutscene
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityDeathSkySwirl);

extern u8 D_80181390;

void EntityUnkId29(Entity* arg0) {
    if (arg0->step == 0) {
        InitializeEntity(D_80180B18);
        arg0->zPriority = 0x2A;
        arg0->unk34 &= 0xF7FFFFFF;
        arg0->facing = Random() & 1;
        g_api.func_80134714(0x665, 0x40, (arg0->posX.i.hi >> 0x4) - 8);
    }
    if (AnimateEntity(&D_80181390, arg0) == 0) {
        DestroyEntity(arg0);
    }
}

void EntityUnkId2A(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(D_80180B18);
        entity->zPriority = 0x29;
        entity->unk34 &= 0xF7FFFFFF;
        entity->animCurFrame = entity->subId + 0x22;
        entity->posX.i.hi = D_8018139C[entity->subId << 1];
        entity->posY.i.hi = D_8018139E[entity->subId << 1];
        entity->unk80.modeS16.unk0 = 5;
    }
    entity->unk80.modeS16.unk0--;
    if ((entity->unk80.modeS16.unk0 << 0x10) == 0) {
        DestroyEntity(entity);
    }
}

// switch that goes downwards when you stand on it
extern u8 D_8003BE1E[];
void EntitySwitch(Entity* entity) {
    s32 temp_a0 = func_801C5D18(entity, 8, 4, 4);
    Entity* player = &PLAYER;

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180B18);
        entity->animCurFrame = 9;
        entity->zPriority = 0x5E;
        if (*D_8003BE1E != 0) {
            entity->step = 2;
            entity->posY.i.hi += 4;
        }
        break;

    case 1:
        if (temp_a0 != 0) {
            player->posY.i.hi++;
            entity->posY.val += 0x4000;
            if ((D_80073092 + entity->posY.i.hi) > 193) {
                entity->posY.i.hi = 193 - D_80073092;
                *D_8003BE1E = 1;
                g_api.PlaySfx(0x608);
                entity->step++;
            }
        }
        break;
    }
}

// door preventing access to warp room / heart
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityHeartRoomGoldDoor);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId49);

// pushes alucard to the right
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityPushAlucard);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId53);

// large foreground tree during intro
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityForegroundTree);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId50);

// part of parallax background with pine trees
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityBackgroundPineTrees);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId52);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId54);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId55);

// shows part of the parallax background castle wall
void EntityBackgroundCastleWall(Entity* entity) {
    Entity* newEntity;

    newEntity = AllocEntity(D_8007C0D8, &D_8007C0D8[64]);
    if (newEntity != NULL) {
        CreateEntityFromCurrentEntity(0x11U, newEntity);
        newEntity->subId = 0xC;
        newEntity->unk68 = 0x80;
        newEntity = AllocEntity(newEntity, &D_8007C0D8[64]);
        if (newEntity != NULL) {
            CreateEntityFromCurrentEntity(0x11U, newEntity);
            newEntity->subId = 0xB;
            newEntity->posY.i.hi = 0x80;
            newEntity->unk68 = 0xC0;
            newEntity->posX.i.hi += 0x40;
        }
    }
    DestroyEntity(entity);
}

// intro owl and leaves
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityFlyingOwlAndLeaves);

// a single leaf from when the owl comes out in the intro
void EntityFallingLeaf(Entity* entity) {
    volatile int pad;

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180B00);
        entity->animSet = -0x7FFF;
        entity->animCurFrame = (entity->subId & 1) + 63;
        entity->zPriority = 0xC1;
        entity->accelerationX = D_801819E8[entity->subId * 2];
        entity->accelerationY = D_801819EC[entity->subId * 2];
        entity->unk68 = 0x1C0;
        break;

    case 1:
        if (entity->accelerationX > 0) {
            entity->accelerationX = entity->accelerationX - 0x1000;
        }
        if (entity->accelerationY <= 0xFFFF) {
            entity->accelerationY = entity->accelerationY + 0x400;
        }
        if (entity->accelerationY > 0x10000) {
            entity->accelerationY -= 0x400;
        }
        MoveEntity();
        break;
    }
}

void func_801BE544(void) {
    D_801D7D30 = 0x182;
    D_801D7D2E = 0x182;
    D_801D7D32 = 0;
    D_801D7D36 = 0;
    D_801D7D3A = 0;
    D_801D7D3B = 8;
    D_801D7D2A = D_801D7D2C + 0x14;
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BE598);

void func_801BE75C(s16 yOffset) {
    RECT rect;

    rect.x = 384;
    rect.y = (yOffset * 12) + 256;
    rect.w = 64;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BE7BC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BE870);

void func_801BE9F4(s32 arg0) {
    D_801D7D64 = arg0 + 0x100000;
    D_801D7D62 = 0;
    D_801D7D60 = 1;
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BEA20);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BECCC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BEDAC);

// seems to cause a room transition
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityRoomTransition1);

// seems to cause a room transition
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityRoomTransition2);

// shows the sword taken from you by Death. Using a different subid shows
// the other items?
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityDeathStolenItem);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId5A);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId5B);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId5E);

void func_801C13F8() {
    Entity* entity;
    s16 temp_s3;
    s32 i;
    s8 temp_s4;

    temp_s4 = Random() & 3;
    temp_s3 = ((Random() & 0xF) << 8) - 0x800;
    for (i = 0; i < 6; i++) {
        entity = AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
        if (entity != NULL) {
            CreateEntityFromEntity(0x62, g_CurrentEntity, entity);
            entity->subId = 2;
            entity->unk88.S8.unk1 = 6 - i;
            entity->unk84.S16.unk0 = temp_s3;
            entity->unk88.S8.unk0 = temp_s4;
        }
    }
}

// A single "puff" of the warg explosion animation, opaque
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityWargExplosionPuffOpaque);

s32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", Update);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C1B78);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C1C80);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityNumericDamage);

void CreateEntityFromLayout(Entity* entity, LayoutObject* initDesc) {
    DestroyEntity(entity);
    entity->objectId = initDesc->objectId & 0x3FF;
    do {
        entity->pfnUpdate = PfnEntityUpdates[entity->objectId];
    } while (0);
    entity->posX.i.hi = initDesc->posX - D_8007308E;
    entity->posY.i.hi = initDesc->posY - D_80073092;
    entity->subId = initDesc->subId;
    entity->objectRoomIndex = initDesc->objectRoomIndex >> 8;
    entity->unk68 = (initDesc->objectId >> 0xA) & 7;
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C3500);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C3618);

void func_801C3730(s16 arg0) {
    while (true) {
        if ((D_801D7110->posX != (u16)~1) && !(D_801D7110->posX < arg0)) {
            break;
        }
        D_801D7110++;
    }
}

void func_801C377C(s16 arg0) {
    while (true) {
        if ((D_801D7110->posX == (u16)~0) ||
            ((arg0 < D_801D7110->posX) && (D_801D7110->posX != (u16)~1))) {
            D_801D7110--;
        } else {
            break;
        }
    }
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C37D4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C38D0);

void func_801C39E4(s16 arg0) {
    while (true) {
        if ((D_801D7114->posY != (u16)~1) && !(D_801D7114->posY < arg0)) {
            break;
        }
        D_801D7114++;
    }
}

void func_801C3A30(s16 arg0) {
    while (true) {
        if (D_801D7114->posY == (u16)~0)
            D_801D7114--;
        else if ((arg0 >= (s32)D_801D7114->posY) ||
                 (D_801D7114->posY == (u16)~1))
            break;
        else
            D_801D7114--;
    }
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C3A88);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C3B84);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", InitRoomEntities);
#else
void InitRoomEntities(s32 objLayoutId) {
    s16 temp_s0;
    s16 var_a1_2;
    u16 temp_v1_2;
    u16* pObjLayoutStart;
    Unkstruct8* layout;

    pObjLayoutStart = g_pStObjLayout[objLayoutId];
    layout = &g_CurrentRoomTileLayout;
    D_801D7110 = pObjLayoutStart;
    D_801D7114 = *(&D_80180850 + objLayoutId);
    if (*pObjLayoutStart != 0xFFFE) {
        s32 var_a0;
        s16 var_a1;
        u16* temp_v1;

        D_801D7110 = pObjLayoutStart + 1;
        var_a0 = Random() & 0xFF;

        for (var_a1 = 0;; var_a1++) {
            s32 temp_v0;
            temp_v1 = D_801D7110;
            D_801D7110 = (u16*)D_801D7110 + 1;
            temp_v0 = var_a0 - temp_v1[0];
            var_a0 = temp_v0;
            if ((s16)temp_v0 < 0)
                break;
            D_801D7110 = temp_v1 + 3;
        }

        D_801D7110 = (temp_v1[2] << 0x10) + temp_v1[1];
        D_801D7114 = (var_a1 * 2) + 2 + (u16*)D_801D7114;
        D_801D7114 = (((u16*)D_801D7114)[1] << 0x10) + ((u16*)D_801D7114)[0];
    }

    var_a1_2 = (s16)layout->unkA - 0x40;
    temp_s0 = layout->unkA + 0x140;
    if (var_a1_2 < 0) {
        var_a1_2 = 0;
    }
    D_801D7118 = 0;
    D_801D711C = 0;
    func_801C3730(var_a1_2);
    func_801C37D4(temp_s0);
    func_801C39E4((s16)(layout->unkE + 0x120));
}
#endif

void func_801C37D4(s16);
void func_801C38D0(s16);
void func_801C3A88(s16);
void func_801C3B84(s16);

void func_801C3E10(void) {
    Unkstruct8* currentRoomTileLayout = &g_CurrentRoomTileLayout;

    if (D_80097908 != 0) {
        s16 tmp = D_8007308E;
        if (D_80097908 > 0)
            func_801C37D4(tmp + 0x140);
        else
            func_801C38D0(tmp - 0x40);
    }

    if (D_8009790C != 0) {
        s16 tmp = currentRoomTileLayout->unkE;
        if (D_8009790C > 0)
            func_801C3A88(currentRoomTileLayout->unkE + 0x120);
        else
            func_801C3B84(tmp - 0x40);
    }
}

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

s32 func_801C3FB4(Unkstruct5* arg0) {
    s16 diff;

    diff = PLAYER.posX.i.hi - arg0->unk2;
    diff = ABS(diff);

    if (diff >= 17) {
        diff = 0;
    } else {
        diff = PLAYER.posY.i.hi - arg0->unk6;
        diff = ABS(diff);
        diff = diff < 33;
    }

    return diff;
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityRedDoor);

void DestroyEntity(Entity* item) {
    s32 i;
    s32 length;
    u32* ptr;

    if (item->unk34 & 0x800000) {
        g_api.FreePolygons(item->firstPolygonIndex);
    }

    ptr = (u32*)item;
    length = sizeof(Entity) / sizeof(s32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

void DestroyEntityFromIndex(s16 index) {
    Entity* entity = &g_EntityArray[index];

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

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C4E4C);

/*
 * Returns the absolute distance from g_CurrentEntity to player in the X Axis
 */
s32 func_801C4F64(void) {
    s16 xDistance = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (xDistance < 0) {
        xDistance = -xDistance;
    }
    return xDistance;
}

/*
 * Returns the absolute distance from g_CurrentEntity to player in the Y Axis
 */
s32 func_801C4FA0(void) {
    s32 yDistance = g_CurrentEntity->posY.i.hi - PLAYER.posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

s32 func_801C4FD4(void) {
    s16 var_a0 = g_CurrentEntity->posX.i.hi > PLAYER.posX.i.hi;

    if (g_CurrentEntity->posY.i.hi > PLAYER.posY.i.hi) {
        var_a0 |= 2;
    }
    return var_a0;
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

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C5074);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C52EC);

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

s32 func_801C5534(u8 arg0, s16 arg1) { return D_801820C4[arg0] * arg1; }

s16 func_801C5560(u8 arg0) { return D_801820C4[arg0]; }

void func_801C557C(s32 arg0, s16 arg1) {
    g_CurrentEntity->accelerationX = func_801C5534(arg0, arg1);
    g_CurrentEntity->accelerationY = func_801C5534(arg0 - 0x40, arg1);
}

u8 func_801C55E8(s16 arg0, s16 arg1) {
    return ((ratan2(arg1, arg0) >> 4) + 0x40);
}

u8 func_801C5620(Entity* arg0, Entity* arg1) {
    s16 a = arg1->posX.i.hi - arg0->posX.i.hi;
    s16 b = arg1->posY.i.hi - arg0->posY.i.hi;
    return func_801C55E8(a, b);
}

u8 func_801C5668(s32 arg0, s32 arg1) {
    s16 a = (arg0 - (u16)g_CurrentEntity->posX.i.hi);
    s16 b = (arg1 - (u16)g_CurrentEntity->posY.i.hi);
    return func_801C55E8(a, b);
}

u8 func_801C56B0(u8 arg0, u8 arg1, u8 arg2) {
    u8 var_v0;
    s8 temp_a2 = arg2 - arg1;

    if (temp_a2 < 0) {
        var_v0 = -temp_a2;
    } else {
        var_v0 = temp_a2;
    }

    if (var_v0 > arg0) {
        if (temp_a2 < 0) {
            var_v0 = arg1 - arg0;
        } else {
            var_v0 = arg1 + arg0;
        }

        return var_v0;
    }

    return arg2;
}

// Duplicate
void func_801C5708(u16 slope, s16 speed) {
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

u16 func_801C5794(s16 arg0, s16 arg1) { return ratan2(arg1, arg0); }

u16 func_801C57C4(Entity* a, Entity* b) {
    s32 diffX = b->posX.i.hi - a->posX.i.hi;
    s32 diffY = b->posY.i.hi - a->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_801C57FC(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s16 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_801C5844(u16 arg0, u16 arg1, u16 arg2) {
    u16 var_v0 = arg1;
    u16 temp_a2 = arg2 - arg1;
    u16 var_v0_2;

    if (temp_a2 & 0x800) {
        var_v0_2 = (0x800 - temp_a2) & 0x7FF;
    } else {
        var_v0_2 = temp_a2;
    }

    if (var_v0_2 > arg0) {
        if (temp_a2 & 0x800) {
            var_v0 = arg1 - arg0;
        } else {
            var_v0 = arg1 + arg0;
        }

        return var_v0;
    }

    return arg2;
}

void func_801C58A4(u8 state) {
    g_CurrentEntity->step = state;
    g_CurrentEntity->unk2E = 0;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

void func_801C58C4(u8 state) {
    g_CurrentEntity->unk2E = state;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

s32 func_801CAD28(s32);

void func_801C58E0(u16 arg0, u16 arg1) {
    Entity* entity;

    if (arg1 != 0) {
        func_801CAD28(arg1);
    }
    if (arg0 == 0xFF) {
        DestroyEntity(g_CurrentEntity);
        return;
    }

    entity = g_CurrentEntity;
    entity->unk19 = 0;
    entity->objectId = 2;
    entity->pfnUpdate = EntityExplosion;
    entity->subId = arg0;
    entity->animCurFrame = 0;
    g_CurrentEntity->step = 0;
    g_CurrentEntity->unk2E = 0;
}

void InitializeEntity(u16 arg0[]) {
    u16 temp_v1;
    Unkstruct5* temp_v0;

    g_CurrentEntity->animSet = *arg0++;
    g_CurrentEntity->animCurFrame = *arg0++;
    g_CurrentEntity->unk5A = *arg0++;
    g_CurrentEntity->palette = *arg0++;
    temp_v1 = *arg0++;
    g_CurrentEntity->unk3A = temp_v1;
    temp_v0 =
        (Unkstruct5*)(temp_v1 * sizeof(Unkstruct5) + (u32)g_api.D_800A8900);
    g_CurrentEntity->hitPoints = temp_v0->unk4;
    g_CurrentEntity->unk40 = temp_v0->unk6;
    g_CurrentEntity->unk42 = temp_v0->unk8;
    g_CurrentEntity->unk3C = temp_v0->unkC;
    g_CurrentEntity->hitboxWidth = temp_v0->hitboxWidth;
    g_CurrentEntity->hitboxHeight = temp_v0->hitboxHeight;
    g_CurrentEntity->unk34 = temp_v0->unk24;
    g_CurrentEntity->unk10 = 0;
    g_CurrentEntity->unk12 = 0;
    g_CurrentEntity->unk2E = 0;
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

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C5A98);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C5BC0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C5D18);

void ReplaceBreakableWithItemDrop(Entity* entity) {
    u16 temp_a0;
    u16 var_v1;

    PreventEntityFromRespawning(entity);
    if (!(D_8009796E & 2)) {
        DestroyEntity(entity);
        return;
    }

    temp_a0 = entity->subId & 0xFFF;
    var_v1 = temp_a0;
    entity->subId = var_v1;

    if (var_v1 < 0x80) {
        entity->objectId = ENTITY_PRICE_DROP;
        entity->pfnUpdate = EntityPriceDrop;
        entity->animFrameDuration = 0;
        entity->animFrameIdx = 0;
    } else {
        var_v1 = temp_a0 - 0x80;
        entity->objectId = ENTITY_INVENTORY_DROP;
        entity->pfnUpdate = EntityInventoryDrop;
    }

    entity->subId = var_v1;
    temp_a0 = 0;
    entity->unk6D = 0x10;
    entity->step = temp_a0;
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C6114);
#else
// matches with gcc 2.6.0 + aspsx 2.34
void func_801C6114(void) {
    s32 temp_v1;

    if (g_CurrentEntity->accelerationY >= 0) {
        temp_v1 = g_CurrentEntity->unk88.S16.unk0 + g_CurrentEntity->unk84.unk;
        g_CurrentEntity->unk84.unk = temp_v1;
        g_CurrentEntity->accelerationX = temp_v1;
        if ((temp_v1 == 0x10000) || (temp_v1 == -0x10000)) {
            g_CurrentEntity->unk88.S16.unk0 = -g_CurrentEntity->unk88.S16.unk0;
        }
    }
    if (g_CurrentEntity->accelerationY < 0x4000) {
        g_CurrentEntity->accelerationY += 0x2000;
    }
}
#endif

void func_801C6198(u16 arg0) {
    CollisionResult res;

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
            return;
        }

        g_CurrentEntity->posY.i.hi += (u16)res.unk18;
        return;
    }

    if (!(res.unk0 & 5)) {
        MoveEntity();
        func_801C6114();
    }
}

extern s8 D_801824F0[]; // c_HeartPrizes
void func_801C62F4(u16 arg0) {
    s32* hearts;

    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    hearts = &D_80097B9C.hearts;
    *hearts += D_801824F0[arg0];

    if (D_80097B9C.heartsMax < *hearts) {
        *hearts = D_80097B9C.heartsMax;
    }

    DestroyEntity(g_CurrentEntity);
}

void CollectGold(u16 goldSize) {
    s32 *gold, *unk;
    u16 goldSizeIndex;

    g_api.PlaySfx(NA_SE_PL_COLLECT_GOLD);
    gold = &g_playerGold;
    goldSizeIndex = goldSize - 2;
    *gold += c_GoldPrizes[goldSizeIndex];
    if (*gold > MAX_GOLD) {
        *gold = MAX_GOLD;
    }

    unk = &D_80097410;
    if (*unk) {
        g_api.FreePolygons(D_80097414);
        *unk = 0;
    }

    func_801D06FC(D_80182438[goldSizeIndex], 1);
    DestroyEntity(g_CurrentEntity);
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C6450);

void CollectHeartVessel(void) {
    if (g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
        g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
        D_80097B9C.hearts += HEART_VESSEL_RICHTER;

        if (D_80097B9C.heartsMax < D_80097B9C.hearts) {
            D_80097B9C.hearts = D_80097B9C.heartsMax;
        }
    } else {
        g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
        g_api.func_800FE044(HEART_VESSEL_INCREASE, 0x4000);
    }
    DestroyEntity(g_CurrentEntity);
}

void func_801C660C(void) {
    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_api.func_800FE044(5, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

void func_801C665C(void) { DestroyEntity(g_CurrentEntity); }

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityPriceDrop);

void EntityExplosion(Entity* entity) {
    u16 zPriority;

    if (entity->step == 0) {
        InitializeEntity(D_80180AC4);
        entity->animSet = 2;
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
        entity->blendMode = 0x30;
        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->blendMode = 0x10;
        }

        zPriority = entity->subId & 0xFF00;
        if (zPriority) {
            entity->zPriority = zPriority >> 8;
        }
        entity->subId &= 15;
        entity->accelerationY = D_801824F4[entity->subId];
    } else {
        entity->posY.val += entity->accelerationY;
        if (!AnimateEntity(D_801825A0[entity->subId], entity)) {
            DestroyEntity(entity);
        }
    }
}

void func_801C6FF4(Entity* entity, s32 renderFlags) {
    POLY_GT4* poly;
    s16 left, top, right, bottom;

    poly = &D_80086FEC[entity->firstPolygonIndex];

    left = entity->posX.i.hi - 7;
    right = entity->posX.i.hi + 7;
    poly->x2 = left;
    poly->x0 = left;
    poly->x3 = right;
    poly->x1 = right;

    top = entity->posY.i.hi - 7;
    bottom = entity->posY.i.hi + 7;
    poly->y1 = top;
    poly->y0 = top;
    poly->y3 = bottom;
    poly->y2 = bottom;

    if (renderFlags & RENDERFLAGS_NOSHADOW) {
        poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 =
            poly->g2 = poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
                255;
    } else {
        poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 =
            poly->g2 = poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
                128;
    }
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityInventoryDrop);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C7680);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityRelicOrb);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityHeartDrop);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId0E);

u8 func_801C8A84(s16* arg0, u8 facing) {
    u8 ret = 0;
    CollisionResult res;
    s16 posX, posY;

    while (*arg0 != 0xFF) {
        ret <<= 1;

        posX = facing ? (g_CurrentEntity->posX.i.hi + *arg0++)
                      : (g_CurrentEntity->posX.i.hi - *arg0++);
        posY = g_CurrentEntity->posY.i.hi + *arg0++;

        g_api.CheckCollision(posX, posY, &res, 0);

        if (res.unk0 & 1) {
            ret |= 1;
        }
    }

    return ret;
}

void EntityUnkId13(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180AE8);
        entity->unk8C.modeU16.unk0 = entity->unk80.entityPtr->objectId;
    case 1:
        if (entity->unk7C.U8.unk0++ >= 5) {
            Entity* newEntity =
                AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(ENTITY_EXPLOSION, entity, newEntity);
                newEntity->objectId = ENTITY_EXPLOSION;
                newEntity->pfnUpdate = EntityExplosion;
                newEntity->subId = entity->subId;
            }
            entity->unk7C.U8.unk0 = 0;
        }
        entity->posX.i.hi = entity->unk80.entityPtr->posX.i.hi;
        entity->posY.i.hi = entity->unk80.entityPtr->posY.i.hi;
        if (entity->unk80.entityPtr->objectId != entity->unk8C.modeU16.unk0) {
            DestroyEntity(entity);
        }
        break;
    }
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C8C84);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C8DB4);

void EntityUnkId14(Entity* entity) {
    if (entity->step == 0) {
        entity->accelerationY = D_80182650[entity->unk94];
        entity->unk34 = 0x0C002000;
        entity->palette = 0x8195;
        entity->animSet = 2;
        entity->animCurFrame = D_80182668[entity->subId];
        entity->blendMode = 0x10;
        entity->step++;
    } else {
        entity->animFrameDuration++;
        entity->posY.val -= entity->accelerationY;

        if (!(entity->animFrameDuration & 1)) {
            entity->animCurFrame++;
        }

        if (D_8018266C[entity->subId] < (s32)entity->animFrameDuration) {
            DestroyEntity(entity);
        }
    }
}

void EntityUnkId15(Entity* arg0) {
    u16 temp_v0;

    if (arg0->step == 0) {
        arg0->unk34 = 0x0C002000;
        arg0->palette = 0x8195;
        arg0->animSet = 5;
        arg0->animCurFrame = 1U;
        arg0->blendMode = 0x10;
        arg0->unk19 = 3;
        temp_v0 = D_80182628[arg0->subId];
        arg0->unk1A = temp_v0;
        arg0->unk1C = temp_v0;
        arg0->accelerationY = D_80182638[arg0->subId];
        arg0->step++;
    } else {
        arg0->animFrameDuration++;
        arg0->posY.val -= arg0->accelerationY;
        if (!(arg0->animFrameDuration & 1)) {
            arg0->animCurFrame++;
        }
        if (arg0->animFrameDuration >= 37) {
            DestroyEntity(arg0);
        }
    }
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C9080);

bool func_801C92B0(Unkstruct6* unk) {
    CollisionResult res;

    FallEntity();
    g_CurrentEntity->posX.val += g_CurrentEntity->accelerationX;
    g_CurrentEntity->posY.val += g_CurrentEntity->accelerationY;

    if (g_CurrentEntity->accelerationY >= 0) {
        s16 posX = g_CurrentEntity->posX.i.hi;
        s16 posY = g_CurrentEntity->posY.i.hi;
        posX += unk->x;
        posY += unk->y;
        g_api.CheckCollision(posX, posY, &res, 0);
        if (res.unk0 & 1) {
            g_CurrentEntity->posY.i.hi += res.unk18;
            g_CurrentEntity->accelerationY =
                -g_CurrentEntity->accelerationY / 2;
            if (g_CurrentEntity->accelerationY > -0x10000) {
                return true;
            }
        }
    }
    return false;
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C93AC);

void EntityIntenseExplosion(Entity* entity) {
    u32 zPriority;

    if (entity->step == 0) {
        InitializeEntity(D_80180AC4);
        entity->palette = 0x8170;
        entity->animSet = 5;
        entity->animCurFrame = 1;
        entity->blendMode = 0x30;
        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->blendMode = 0x10;
        }

        zPriority = entity->subId & 0xFF00;
        if (zPriority != 0) {
            entity->zPriority = zPriority >> 8;
        }
        entity->zPriority += 8;
    } else {
        entity->animFrameDuration++;
        entity->posY.val -= 0x4000;

        if (!(entity->animFrameDuration & 1)) {
            entity->animCurFrame++;
        }

        if (entity->animFrameDuration >= 37) {
            DestroyEntity(entity);
        }
    }
}

void func_801903C8(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(D_80180AC4);
        entity->unk6C = 0xF0;
        entity->unk1A = 0x01A0;
        entity->unk1C = 0x01A0;
        entity->animSet = 8;
        entity->animCurFrame = 1;
        entity->zPriority += 16;
        if (entity->subId) {
            entity->palette = entity->subId;
        } else {
            entity->palette = 0x8160;
        }

        entity->step++;
    } else {
        MoveEntity();
        if (!AnimateEntity(D_8018267C, entity)) {
            DestroyEntity(entity);
        }
    }
}

void func_801C9AF8(u16 objectId, Entity* source, Entity* entity) {
    u16 palette;

    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
    entity->unk5A = source->unk5A;
    entity->zPriority = source->zPriority;
    entity->animSet = source->animSet;
    entity->unk34 = 0xCD002000;

    palette = source->palette;
    entity->palette = palette & 0x8000 ? source->unk6A : palette;
}

void func_801C9BC0(void) {
    Entity* entity;
    s8 temp_s4 = Random() & 3;
    s16 temp_s3 = ((Random() & 0xF) << 8) - 0x800;
    s32 i;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
        if (entity != NULL) {
            CreateEntityFromEntity(2, g_CurrentEntity, entity);
            entity->unk84.U8.unk1 = 6 - i;
            entity->unk80.modeS16.unk0 = temp_s3;
            entity->unk84.U8.unk0 = temp_s4;
        }
    }
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C9C78);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C9E50);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CA430);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CAB30);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CAD28);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CAE20);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityStageNamePopup);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityAbsorbOrb);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityEnemyBlood);

void EntityRoomForeground(Entity* entity) {
    ObjInit2* objInit = &D_80182764[entity->subId];

    if (entity->step == 0) {
        InitializeEntity(D_80180B00);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk4.s;
        entity->palette = objInit->palette;
        entity->unk19 = objInit->unk8;
        entity->blendMode = objInit->blendMode;
        if (objInit->unkC != 0) {
            entity->unk34 = objInit->unkC;
        }
        if (entity->subId >= 5) {
            entity->unk1E = 0x800;
            entity->unk19 |= 4;
        }
    }
    AnimateEntity(objInit->unk10, entity);
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CC5A4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CC6F8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CC820);

void func_801CC90C(Entity* arg0) {
    s16 temp_v0_2;
    s16 temp_v1;
    s16 temp_v0;

    temp_v0 = func_801C4F64();
    temp_v1 = arg0->unk84.S16.unk2;
    if (temp_v1 != 0) {

        if ((u32)(temp_v0) < 0x60) {
            temp_v0_2 = temp_v1 - 2;
            arg0->unk84.S16.unk2 = temp_v0_2;
            if (temp_v0_2 < 0) {
                arg0->unk84.S16.unk2 = 0;
            }
        } else {
            arg0->unk84.S16.unk2 = (temp_v1 - 1);
        }
    }
}

// stronger version of warg with jump and flame attack
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityStrongWarg);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId30);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId31);

// some sort of explosion
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityExplosion3);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CE740);

// flame-like attack on ground from strong warg
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityStrongWargGroundWaveAttack);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId2F);

// beams that go up when strong warg dies
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityStrongWargDeathBeams);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CF438);

void func_801CF58C(Entity* arg0) {
    arg0->accelerationX = 0;
    arg0->unk84.S16.unk2 = 0x100;
    func_801C58A4(6);
    g_api.PlaySfx(0x783);
    arg0->unk80.modeS16.unk0 = 0x20;
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CF5E0);

// duplicate of func_801CC90C in this file
void func_801CF6D8(Entity* arg0) {
    s16 temp_v0_2;
    s16 temp_v1;
    s16 temp_v0;

    temp_v0 = func_801C4F64();
    temp_v1 = arg0->unk84.S16.unk2;
    if (temp_v1 != 0) {

        if ((u32)(temp_v0) < 0x60) {
            temp_v0_2 = temp_v1 - 2;
            arg0->unk84.S16.unk2 = temp_v0_2;
            if (temp_v0_2 < 0) {
                arg0->unk84.S16.unk2 = 0;
            }
        } else {
            arg0->unk84.S16.unk2 = (temp_v1 - 1);
        }
    }
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityWarg);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId4B);

extern u8 D_8018383C;

// A single "puff" of the warg explosion animation, transparent
void EntityWargExplosionPuffTransparent(Entity* entity) {
    u32 temp_v0;

    if (entity->step == 0) {
        InitializeEntity(D_80180AC4);
        entity->animSet = 0xE;
        entity->unk5A = 0x79;
        entity->palette = 0xD0;
        entity->blendMode = 0x30;
        entity->unk19 = 8;
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
        entity->unk6C = 0x60;
        temp_v0 = entity->subId & 0xFF00;
        if (temp_v0 != 0) {
            entity->zPriority = (u16)(temp_v0 >> 8);
        }
        entity->accelerationY += 0xFFFF0000;
        return;
    }
    entity->posY.val += entity->accelerationY;
    if (AnimateEntity(&D_8018383C, entity) == 0) {
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D06FC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D0A2C);

// Alucard says "ahh" and turns blue from water contact
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityAlucardWaterEffect);

// large splash going upwards
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityLargeUpwardsSplash);

// splash animation and sound when Alucard touches water
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityAlucardSplash);

// small water droplets go to the side
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntitySidewaysWaterDroplets);

// small water droplets go upwards
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntitySmallUpwardsSplash);

// particle effect, part of merman splash
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntitySmallWaterSplash);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D2D40);

// another merman variant
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityMerman3);

// some sort of explosion
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityExplosion2);

extern u16 D_80180B54[];
extern u8 D_80183994[];

// medium sized water splash used with merman
void EntityMediumWaterSplash(Entity* entity) {
    Entity* temp_v0;

    if (entity->step == 0) {
        InitializeEntity(D_80180B54);
        entity->animCurFrame = 0;
        if (entity->facing != 0) {
            entity->accelerationX = 0x20000;
            return;
        }
        entity->accelerationX = -0x20000;
        return;
    }
    AnimateEntity(D_80183994, entity);
    MoveEntity();
    if (entity->unk34 & 0x100) {
        temp_v0 = AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
        if (temp_v0 != NULL) {
            CreateEntityFromEntity(2, entity, temp_v0);
            temp_v0->subId = 0;
        }
        DestroyEntity(entity);
    }
}

// spawns EntityMediumWaterSplash, part of merman splash
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityLargeWaterSplash);

extern u8 D_801839A8;
extern u16 D_80180B48[];

// some kind of falling object
void EntityFallingObject2(Entity* arg0) {
    if (arg0->step == 0) {
        InitializeEntity(D_80180B48);
        arg0->animCurFrame = 0;
        arg0->unk3C = 0;
        arg0->unk34 |= 0x2000;
        arg0->zPriority += 4;
    }
    MoveEntity();
    arg0->accelerationY += 0x2800;
    if (AnimateEntity(&D_801839A8, arg0) == 0) {
        DestroyEntity(arg0);
    }
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId3D);

// falling object, larger
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityLargeFallingObject);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityMerman2);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityMerman);

// fireball shot by merman
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityMermanFireball);

extern u16 D_80180B60;
extern u8 D_80183B04;

// some sort of falling object
void EntityFallingObject(Entity* arg0) {
    if (arg0->step == 0) {
        InitializeEntity(&D_80180B60);
        arg0->animCurFrame = 0;
        arg0->unk3C = 0;
        arg0->zPriority += 4;
        arg0->unk34 |= 0x2000;
    }
    MoveEntity();
    arg0->accelerationY += 0x2800;
    if (AnimateEntity(&D_80183B04, arg0) == 0) {
        DestroyEntity(arg0);
    }
}

// part of explosion when merman dies
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityMermanExplosion);

s32 func_801C52EC(s32*);
s32 func_801C5A98(s32*, s32);

void func_801D59D0(void) {
    s32 temp_s0;
    s32 temp_v0;

    temp_s0 = func_801C52EC(&D_80183C30);
    temp_v0 = func_801C5A98(&D_80183C38, 3);

    if ((temp_s0 == 0x80) || (temp_v0 & 2)) {
        func_801C58A4(5);
        return;
    }

    if (g_CurrentEntity->unk7C.U8.unk0 == 0) {
        if (func_801C4F64() < 0x40) {
            if (g_CurrentEntity->facing != (func_801C4FD4() & 1)) {
                func_801C58A4(4);
            }
        }
    } else {
        g_CurrentEntity->unk7C.U8.unk0--;
    }
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityBoneScimitar);

// debris that rotates and falls down
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityFallingDebris);
