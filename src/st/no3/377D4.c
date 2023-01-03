/*
 * File: 377D4.c
 * Overlay: NO3
 * Description: Castle Entrance
 */

#include "stage.h"

void SpawnExplosionEntity(u16, Entity*);
void ReplaceBreakableWithItemDrop(Entity*);
void EntityItemDrop(Entity*);
void EntityHeartDrop(Entity*);

extern u8* D_80180850;
extern u16 D_80180B00[];
extern ObjInit2 D_80180BFC[];
extern s16 D_801820C4[];
extern LayoutObject* D_801D7110;
extern LayoutObject* D_801D7114;
extern s8 D_801D7118;
extern s8 D_801D711C;
extern s16 D_801D7D30;
extern s16 D_801D7D32;
extern s16 D_801D7D36;
extern s16 D_801D7D60;
extern s16 D_801D7D62;
extern s32 D_801D7D64;
extern s16 D_801D7D2A;
extern u16 D_801D7D2C;
extern s16 D_801D7D2E;
extern s8 D_801D7D3A;
extern s8 D_801D7D3B;
extern LayoutObject* g_pStObjLayout[];
extern PfnEntityUpdate PfnEntityUpdates[];

void func_801B77D4(Entity* arg0) {
    s32 temp_v0;
    ObjInit2* temp_s0 = &D_80180BFC[arg0->subId];

    if (arg0->step == 0) {
        InitializeEntity(D_80180B00);
        arg0->animationSet = temp_s0->animationSet;
        arg0->zPriority = temp_s0->zPriority;
        arg0->facing = temp_s0->unk4.data1.unk0;
        arg0->unk5A = temp_s0->unk4.data1.unk1;
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

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B78A8);

extern u16 g_eBreakableInit[];
extern u8* g_eBreakableAnimations[8];
extern u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakableAnimationSets[];
extern u8 g_eBreakableBlendModes[];
void EntityBreakable(Entity* entity) {
    u16 breakableType = entity->subId >> 0xC;
    if (entity->step) {
        AnimateEntity(g_eBreakableAnimations[breakableType], entity);
        if (entity->unk44) { // If the candle is destroyed
            Entity* entityDropItem;
            g_pfnPlaySfx(NA_SE_BREAK_CANDLE);
            entityDropItem =
                AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
            if (entityDropItem != NULL) {
                SpawnExplosionEntity(ENTITY_EXPLOSION, entityDropItem);
                entityDropItem->subId =
                    g_eBreakableExplosionTypes[breakableType];
            }
            ReplaceBreakableWithItemDrop(entity);
        }
    } else {
        InitializeEntity(g_eBreakableInit);
        entity->zPriority = g_zEntityCenter.typeShort - 0x14;
        entity->blendMode = g_eBreakableBlendModes[breakableType];
        entity->hitboxHeight = g_eBreakableHitboxes[breakableType];
        entity->animationSet = g_eBreakableAnimationSets[breakableType];
    }
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B7B98);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B7C4C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B8254);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B8564);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B8A74);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B8ED0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B9198);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B94F0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B9650);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B97D0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B989C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B9C44);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B9CE8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B9E10);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BA0A0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BA348);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BA4C0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BA868);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BABE8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BAD6C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BAEF0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BB3BC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BB548);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BBB8C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BBDC0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BBE70);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BBF38);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BC05C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BC3FC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BC4EC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BC780);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BC93C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BCC4C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BCE08);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BD564);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BD71C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BDEB0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BE080);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BE134);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BE444);

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

// https://decomp.me/scratch/ErGo1
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BE75C);

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

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BEEB0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BFF00);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C033C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C083C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C11A4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C12E8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C13F8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C14B8);

s32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", UpdateStageEntities);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C1B78);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C1C80);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityNumericDamage);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", CreateEntity);
#else
void CreateEntity(Entity* entity, LayoutObject* initDesc) {
    DestroyEntity(entity);
    entity->objectId = initDesc->objectId & 0x3FF;
    entity->pfnUpdate = PfnEntityUpdates[entity->objectId];
    entity->posX.Data.high = initDesc->posX - D_8007308E;
    entity->posY.Data.high = initDesc->posY - D_80073092;
    entity->subId = initDesc->subId;
    entity->objectRoomIndex = initDesc->objectRoomIndex >> 8;
    entity->unk68 = initDesc->objectId >> 0xA & 7;
}
#endif

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
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", LoadObjLayout);
#else
void LoadObjLayout(s32 objLayoutId) {
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

// TODO: try after resolving aspsx
// https://decomp.me/scratch/cJ3CF
#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C3E10);
#else
void func_801C3E10(void) {
    s32 temp_v0;
    s32 temp_v0_2;
    s16 temp_a0;
    Unkstruct8* temp_a0_2 = &g_CurrentRoomTileLayout;

    temp_v0 = D_80097908;
    if (temp_v0 != 0) {
        temp_a0 = D_8007308E;
        if (temp_v0 > 0) {
            func_801C37D4((s16)(D_8007308E + 0x140));
        } else {
            func_801C38D0((s16)(temp_a0 - 0x40));
        }
    }
    temp_v0_2 = D_8009790C;
    if (D_8009790C != 0) {
        s16 temp = temp_a0_2->unkE;
        if (D_8009790C > 0) {
            func_801C3A88((temp + 0x120));
        } else {
            func_801C3B84((s16)(temp - 0x40));
        }
    }
}
#endif

void SpawnExplosionEntity(u16 objectId, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.Data.high = g_CurrentEntity->posX.Data.high;
    entity->posY.Data.high = g_CurrentEntity->posY.Data.high;
}

void func_801C3F38(u16 objectId, Entity* source, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.Data.high = source->posX.Data.high;
    entity->posY.Data.high = source->posY.Data.high;
}

s32 func_801C3FB4(Unkstruct5* arg0) {
    Entity* player = GET_PLAYER(g_EntityArray);
    s16 diff;

    diff = player->posX.Data.high - arg0->unk2;
    diff = ABS_ALT(diff);

    if (diff >= 17) {
        diff = 0;
    } else {
        diff = player->posY.Data.high - arg0->unk6;
        diff = ABS_ALT(diff);
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
        g_pfnFreePolygons(item->firstPolygonIndex);
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
s16 func_801C4F64(void) {
    Entity* player = GET_PLAYER(g_EntityArray);
    s16 xDistance = g_CurrentEntity->posX.Data.high - player->posX.Data.high;

    if (xDistance < 0) {
        xDistance = -xDistance;
    }
    return xDistance;
}

/*
 * Returns the absolute distance from g_CurrentEntity to player in the Y Axis
 */
s32 func_801C4FA0(void) {
    Entity* player = GET_PLAYER(g_EntityArray);
    s32 yDistance = g_CurrentEntity->posY.Data.high - player->posY.Data.high;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

s16 func_801C4FD4(void) {
    Entity* player = GET_PLAYER(g_EntityArray);
    s16 var_a0 = g_CurrentEntity->posX.Data.high > player->posX.Data.high;

    if (g_CurrentEntity->posY.Data.high > player->posY.Data.high) {
        var_a0 |= 2;
    }
    return var_a0;
}

void MoveEntity(void) {
    g_CurrentEntity->posX.value += g_CurrentEntity->accelerationX;
    g_CurrentEntity->posY.value += g_CurrentEntity->accelerationY;
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

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C557C);

u8 func_801C55E8(s16 arg0, s16 arg1) {
    return ((ratan2(arg1, arg0) >> 4) + 0x40);
}

u8 func_801C5620(Entity* arg0, Entity* arg1) {
    s16 a = arg1->posX.Data.high - arg0->posX.Data.high;
    s16 b = arg1->posY.Data.high - arg0->posY.Data.high;
    return func_801C55E8(a, b);
}

u8 func_801C5668(s32 arg0, s32 arg1) {
    s16 a = (arg0 - (u16)g_CurrentEntity->posX.Data.high);
    s16 b = (arg1 - (u16)g_CurrentEntity->posY.Data.high);
    return func_801C55E8(a, b);
}

// https://decomp.me/scratch/0GgS4
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C56B0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C5708);

u16 func_801C5794(s16 arg0, s16 arg1) { return ratan2(arg1, arg0); }

u16 func_801C57C4(Entity* a, Entity* b) {
    s32 diffX = b->posX.Data.high - a->posX.Data.high;
    s32 diffY = b->posY.Data.high - a->posY.Data.high;
    return ratan2(diffY, diffX);
}

// https://decomp.me/scratch/ghlVg
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C57FC);

// https://decomp.me/scratch/FkEAs
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C5844);

void func_801C58A4(u8 state) {
    g_CurrentEntity->step = state;
    g_CurrentEntity->unk2E = 0;
    g_CurrentEntity->animationFrameIndex = 0;
    g_CurrentEntity->animationFrameDuration = 0;
}

void func_801C58C4(u8 state) {
    g_CurrentEntity->unk2E = state;
    g_CurrentEntity->animationFrameIndex = 0;
    g_CurrentEntity->animationFrameDuration = 0;
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C58E0);

void InitializeEntity(const u16 arg0[]) {
    u16 temp_v1;
    Unkstruct5* temp_v0;

    g_CurrentEntity->animationSet = *arg0++;
    g_CurrentEntity->animationFrame = *arg0++;
    g_CurrentEntity->unk5A = *arg0++;
    g_CurrentEntity->palette = *arg0++;
    temp_v1 = *arg0++;
    g_CurrentEntity->unk3A = temp_v1;
    temp_v0 = (Unkstruct5*)(temp_v1 * sizeof(Unkstruct5) + (u32)D_8003C808);
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
        g_CurrentEntity->zPriority = g_zEntityCenter.typeShort - 0xC;
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
        entity->objectId = ENTITY_ITEM_DROP;
        entity->pfnUpdate = EntityItemDrop;
        entity->animationFrameDuration = 0;
        entity->animationFrameIndex = 0;
    } else {
        var_v1 = temp_a0 - 0x80;
        entity->objectId = ENTITY_HEART_DROP;
        entity->pfnUpdate = EntityHeartDrop;
    }

    entity->subId = var_v1;
    temp_a0 = 0;
    entity->unk6D = 0x10;
    entity->step = temp_a0;
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C6114);
#else
void func_801C6114(void) {
    if (g_CurrentEntity->accelerationY >= 0) {
        g_CurrentEntity->unk84.value =
            g_CurrentEntity->unk88 + g_CurrentEntity->unk84.value;
        g_CurrentEntity->accelerationX = g_CurrentEntity->unk84.value;
        if ((g_CurrentEntity->accelerationX == 0x10000) ||
            (g_CurrentEntity->accelerationX == -0x10000)) {
            g_CurrentEntity->unk88 = -g_CurrentEntity->unk88;
        }
    }
    if (g_CurrentEntity->accelerationY < 0x4000) {
        g_CurrentEntity->accelerationY += 0x2000;
    }
}
#endif

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C6198);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C62F4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C6374);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C6450);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C6568);

void func_801C660C(void) {
    g_pfnPlaySfx(NA_SE_PL_COLLECT_HEART);
    D_8003C848(5, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

void func_801C665C(void) { DestroyEntity(g_CurrentEntity); }

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityItemDrop);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityExplosion);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C6FF4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityHeartDrop);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C7680);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityRelicItem);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityInventoryItem);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityUnkId0D);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C8A84);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C8B74);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C8C84);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C8DB4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C8E9C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C8F8C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C9080);

bool func_801C92B0(Unkstruct6* unk) {
    Unkstruct7 a;

    FallEntity();
    g_CurrentEntity->posX.value += g_CurrentEntity->accelerationX;
    g_CurrentEntity->posY.value += g_CurrentEntity->accelerationY;

    if (g_CurrentEntity->accelerationY >= 0) {
        s16 posX = g_CurrentEntity->posX.Data.high;
        s16 posY = g_CurrentEntity->posY.Data.high;
        posX += unk->x;
        posY += unk->y;
        D_8003C7BC(posX, posY, &a, 0);
        if (a.sp10 & 1) {
            g_CurrentEntity->posY.Data.high += a.sp28;
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

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityIntenseExplosion);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C9A2C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C9AF8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C9BC0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C9C78);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C9E50);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CA430);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CAB30);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CAD28);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CAE20);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityStageNamePopup);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityAbsorbOrb);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityEnemyBlood);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityRoomForeground);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CC5A4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CC6F8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CC820);

// https://decomp.me/scratch/AzIEr
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CC90C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CC974);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CDD80);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CDF10);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CE2F4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CE740);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CE98C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CED60);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CEF88);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CF438);

void func_801CF58C(Entity* arg0) {
    arg0->accelerationX = 0;
    arg0->unk84.Data.high = 0x100;
    func_801C58A4(6);
    g_pfnPlaySfx(0x783);
    arg0->unk80.modeS16.unk0 = 0x20;
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CF5E0);

// https://decomp.me/scratch/ljfBh
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CF6D8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityWarg);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D04A4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D0624);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D06FC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D0A2C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D0B34);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D16B4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D1FC0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D24AC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D2840);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D2A9C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D2D40);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D2E4C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D3F38);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D4168);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D423C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D4668);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D4700);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D48F8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityMerman2);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityMerman);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D56D8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D583C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D58D4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D59D0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityBoneScimitar);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D615C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityBat);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityZombie);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D6710);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D6880);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D6C68);

// https://decomp.me/scratch/DHpdc
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D6DB8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D6DE8);

POLY_GT4* func_801D6E64(POLY_GT4* startPoly, s32 count) {
    POLY_GT4* poly;
    s8 unk;
    s32 i;

    if (startPoly->p3) {
        startPoly->p3 = 0;
    } else {
        startPoly->p3 = 1;
    }

    poly = startPoly;
    for (i = 0; i < count; i++) {
        if (poly->p3) {
            poly->pad3 &= ~8;
            unk = 0;
        } else {
            poly->pad3 |= 8;
            unk = 1;
        }

        poly = (POLY_GT4*)poly->tag;
        if (poly == 0)
            return 0;
        poly->p3 = unk;
    }

    return poly;
}

void func_801D6EEC(POLY_GT4* arg0) {
    arg0->p1 = 0;
    arg0->p2 = 0;
    arg0->p3 = 0;
    ((POLY_GT4*)arg0->tag)->x1 = 0;
    ((POLY_GT4*)arg0->tag)->y1 = 0;
    ((POLY_GT4*)arg0->tag)->y0 = 0;
    ((POLY_GT4*)arg0->tag)->x0 = 0;
    ((POLY_GT4*)arg0->tag)->clut = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->u0 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->b1 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->r1 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->u1 = 0;
    ((POLY_GT4*)arg0->tag)->tpage = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->r2 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->b2 = 0;
    ((POLY_GT4*)arg0->tag)->u2 = 0;
    ((POLY_GT4*)arg0->tag)->v2 = 0;
    ((POLY_GT4*)arg0->tag)->r3 = 0;
    ((POLY_GT4*)arg0->tag)->b3 = 0;
    ((POLY_GT4*)arg0->tag)->x2 = 0;
    ((POLY_GT4*)arg0->tag)->y2 = 0;
}

void func_801D6FCC(POLY_GT4* arg0) {
    func_801D6EEC(arg0);
    arg0->p3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 1;
    ((POLY_GT4*)arg0->tag)->code = 2;
    ((POLY_GT4*)arg0->tag)->pad3 = 0xA;
}

void func_801D7020(POLY_GT4* arg0) {
    arg0->p3 = 0;
    arg0->pad3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 0;
    ((POLY_GT4*)arg0->tag)->code = 4;
    ((POLY_GT4*)arg0->tag)->pad3 = 8;
}

s32 func_801D704C(s32 arg0, u8 arg1) {
    s32 var_v0;
    s32 ret = 0;
    u8* var_a0 = arg0 + 4;
    u8* var_v1;
    s32 i;

    for (i = 0; i < 4; i++) {
        var_v1 = var_a0;
        do {
            var_v0 = *var_v1 - arg1;

            if (var_v0 < 0) {
                var_v0 = 0;
            } else {
                ret |= 1;
            }

            *var_v1 = var_v0;
            var_v1++;
        } while ((s32)var_v1 < ((s32)var_a0 + 3));

        var_a0 += 0xC;
    }

    return ret;
}
