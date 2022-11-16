/*
 * File: 394D4.c
 * Overlay: NZ0
 * Description: Alchemy Laboratory
 */

#include "stage.h"

void DestroyEntity(Entity* item);
void func_8019B858(void);
void func_801BDD9C(void);
s32 func_801BCF74(s32*);
s32 func_801BD720(s32*, s32);
void func_801BEB80(Entity*);
void func_801C29B0(s32);
void EntityCandleDrop(Entity* entity);
void EntityCandleHeartDrop(Entity* entity);
void func_801C33D8(const u32*, s32);

extern u32 g_randomNext;
extern PfnEntityUpdate D_80180A90[];
extern s16 D_80181978[];
extern s8 c_HeartPrizes[];
extern Entity* D_8006C3B8;
extern u16 D_80180BE0[];
extern s32 D_80181DA8[];
extern s32 D_80181E54[];
extern u8 D_80181F1C[];
extern s32 D_80181F04[];
extern u16 D_80181F20[];
extern s16 D_80181EDC[];
extern u32 D_80181EEC[];
extern ObjInit2 D_80182014[];
extern u16 D_80180C1C[];
extern LayoutObject* D_801CAA74;
extern LayoutObject* D_801CAA78;
extern u8 D_801822B4[];
PfnEntityUpdate D_80180A90[];
extern s32 D_801824B8;
extern s32 D_801824C0;
extern u16 D_80180C88;
extern const u8* D_80181F30;
extern const u16* D_80180CF4;
extern s32 D_80182600[];
extern s32* D_8018216C;
extern s32* D_80182174;
extern const u16* D_80180BD4;
extern const s32 D_80181D3C[];
extern const u16* D_80180C94;
extern u16 D_80182424[];
extern const u32 D_80181CEC[];
extern const s32 c_GoldPrizes[];
extern const u16 D_80180CA0[];
extern u32 D_80182488[];
extern const u16* D_80180C58;
extern s16 D_801820E4[];

s32 Random(void) {
    // Linear congruential generator algorithm

    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801B9504);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801B9800);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801B9908);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BAA20);

void CreateEntity(Entity* entity, LayoutObject* initDesc) {
    DestroyEntity(entity);
    entity->objectId = initDesc->objectId & 0x3FF;
    do { //! FAKE https://decomp.me/scratch/zysYC
        entity->pfnUpdate = D_80180A90[entity->objectId];
    } while (0);
    entity->posX.Data.high = initDesc->posX - D_8007308E;
    entity->posY.Data.high = initDesc->posY - (u16)D_80073092;
    entity->subId = initDesc->subId;
    entity->objectRoomIndex = initDesc->objectRoomIndex >> 8;
    entity->unk68 = (initDesc->objectId >> 0xA) & 7;
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BB188);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BB2A0);

void func_801BB3B8(s16 arg0) {
    while (true) {
        if ((D_801CAA74->posX != 0xFFFE) && (D_801CAA74->posX >= arg0)) {
            break;
        }
        D_801CAA74++;
    }
}

void func_801BB404(s16 arg0) {
    while (true) {
        if (!(D_801CAA74->posX == 0xFFFF) &&
            ((arg0 >= D_801CAA74->posX) || (D_801CAA74->posX == 0xFFFE))) {
            break;
        }
        D_801CAA74--;
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BB45C);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BB558);

void func_801BB66C(s16 arg0) {
    while (true) {
        if ((D_801CAA78->posY != 0xFFFE) && (D_801CAA78->posY >= arg0)) {
            break;
        }
        D_801CAA78++;
    }
}

void func_801BB6B8(s16 arg0) {
    while (true) {
        if (!(D_801CAA78->posY == 0xFFFF) &&
            ((arg0 >= D_801CAA78->posY) || (D_801CAA78->posY == 0xFFFE))) {
            break;
        }
        D_801CAA78--;
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BB710);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BB80C);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BB920);

// TODO: try after resolving aspsx
// https://decomp.me/scratch/cJ3CF
INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BBA98);

void SpawnExplosionEntity(u16 objectId, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = D_80180A90[objectId];
    entity->posX.Data.high = D_8006C3B8->posX.Data.high;
    entity->posY.Data.high = D_8006C3B8->posY.Data.high;
}

void func_801BBBC0(u16 objectId, Entity* ent1, Entity* ent2) {
    DestroyEntity(ent2);
    ent2->objectId = objectId;
    ent2->pfnUpdate = D_80180A90[objectId];
    ent2->posX.Data.high = (s16)ent1->posX.Data.high;
    ent2->posY.Data.high = (s16)ent1->posY.Data.high;
}

s32 func_801BBC3C(Unkstruct5* arg0) {
    s16 var_v0_2;

    var_v0_2 = D_800733DA - arg0->unk2;
    var_v0_2 = ABS_ALT(var_v0_2);

    if (var_v0_2 >= 0x11) {
        var_v0_2 = 0;
    } else {
        var_v0_2 = D_800733DE - arg0->unk6;
        var_v0_2 = ABS_ALT(var_v0_2);
        var_v0_2 = var_v0_2 < 0x21;
    }

    return var_v0_2;
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BBCB4);

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
    Entity* entity = &D_800733D8[index];

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

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BCAD4);

s32 func_801BCBEC(void) {
    s16 value = D_8006C3B8->posX.Data.high - D_800733DA;

    if (value < 0) {
        value = -value;
    }
    return value;
}

s32 func_801BCC28(void) {
    s32 value = D_8006C3B8->posY.Data.high - D_800733DE;

    if (value < 0) {
        value = -value;
    }
    return value;
}

s16 func_801BCC5C(void) {
    s16 var_a0 = D_8006C3B8->posX.Data.high > D_800733DA;

    if (D_8006C3B8->posY.Data.high > D_800733DE) {
        var_a0 |= 2;
    }
    return var_a0;
}

void MoveEntity(void) {
    D_8006C3B8->posX.value += D_8006C3B8->accelerationX;
    D_8006C3B8->posY.value += D_8006C3B8->accelerationY;
}

void FallEntity(void) {
    if (D_8006C3B8->accelerationY < FALL_TERMINAL_VELOCITY) {
        D_8006C3B8->accelerationY += FALL_GRAVITY;
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BCCFC);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BCF74);

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

s32 func_801BD1BC(u8 arg0, s16 arg1) { return D_80181978[arg0] * arg1; }

s16 func_801BD1E8(u8 arg0) { return D_80181978[arg0]; } // Unique

void func_801BD204(s32 arg0, s16 arg1) {
    D_8006C3B8->accelerationX = func_801BD1BC(arg0, arg1);
    D_8006C3B8->accelerationY = func_801BD1BC(arg0 - 0x40, arg1);
}

u8 func_801BD270(s16 x, s16 y) { return ((ratan2(y, x) >> 4) + 0x40); }

u8 func_8019AD64(ObjInit2* arg0, ObjInit2* arg1) {
    u16 x, y;

    x = arg1->zPriority - arg0->zPriority;
    y = arg1->palette - arg0->palette;

    return func_801BD270(x, y);
}

u8 func_801BD2F0(s16 arg0, s16 arg1) {
    s16 x, y;

    x = arg0 - D_8006C3B8->posX.Data.high;
    y = arg1 - D_8006C3B8->posY.Data.high;

    return func_801BD270(x, y);
}

u8 func_801BD338(u8 arg0, u8 arg1, u8 arg2) {
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

void func_801BD390(u16 slope, s16 speed) {
    Entity* entity;
    s32 moveX;
    s32 moveY;

    moveX = rcos(slope) * speed;
    entity = D_8006C3B8;

    if (moveX < 0) {
        moveX += 15;
    }

    entity->accelerationX = moveX >> 4;

    moveY = rsin(slope) * speed;
    entity = D_8006C3B8;

    if (moveY < 0) {
        moveY += 15;
    }

    entity->accelerationY = moveY >> 4;
}

u16 func_801BD41C(s16 x, s16 y) { return ratan2(y, x); }

u16 func_801BD44C(Entity* a, Entity* b) {
    s32 diffX = b->posX.Data.high - a->posX.Data.high;
    s32 diffY = b->posY.Data.high - a->posY.Data.high;
    return ratan2(diffY, diffX);
}

u16 func_801BD484(s32 x, s32 y) {
    s16 diffX = x - (u16)D_8006C3B8->posX.Data.high;
    s16 diffY = y - (u16)D_8006C3B8->posY.Data.high;
    return ratan2(diffY, diffX);
}

u16 func_801BD4CC(u16 arg0, s16 arg1, s16 arg2) {
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

void func_801BD52C(u8 initState) {
    Entity* entity;

    entity = D_8006C3B8;
    entity->initState = initState;
    entity->unk2E = 0;
    entity->animationFrameIndex = 0;
    entity->animationFrameDuration = 0;
}

void func_801BD54C(u8 arg0) {
    Entity* entity;

    entity = D_8006C3B8;
    entity->unk2E = arg0;
    entity->animationFrameIndex = 0;
    entity->animationFrameDuration = 0;
}

void func_801BD568(u16 arg0, u16 arg1) {
    if (arg1 != 0) {
        func_801C29B0(arg1);
    }

    if (arg0 == 0xFF) {
        DestroyEntity(D_8006C3B8);
        return;
    }

    D_8006C3B8->objectId = 2;
    D_8006C3B8->pfnUpdate = (PfnEntityUpdate)func_801BEB80;
    D_8006C3B8->subId = arg0;
    D_8006C3B8->animationFrame = 0;
    D_8006C3B8->unk19 = 0;
    D_8006C3B8->initState = 0;
    D_8006C3B8->unk2E = 0;
}

void InitializeEntity(const u16 arg0[]) {
    u16 temp_v1;
    Unkstruct5* temp_v0;

    D_8006C3B8->animationSet = *arg0++;
    D_8006C3B8->animationFrame = *arg0++;
    D_8006C3B8->unk5A = *arg0++;
    D_8006C3B8->palette = *arg0++;
    temp_v1 = *arg0++;
    D_8006C3B8->unk3A = temp_v1;
    temp_v0 = (Unkstruct5*)(temp_v1 * sizeof(Unkstruct5) + (u32)D_8003C808);
    D_8006C3B8->unk3E = temp_v0->unk4;
    D_8006C3B8->unk40 = temp_v0->unk6;
    D_8006C3B8->unk42 = temp_v0->unk8;
    D_8006C3B8->unk3C = temp_v0->unkC;
    D_8006C3B8->hitboxWidth = temp_v0->hitboxWidth;
    D_8006C3B8->hitboxHeight = temp_v0->hitboxHeight;
    D_8006C3B8->unk34 = temp_v0->unk24;
    D_8006C3B8->unk10 = 0;
    D_8006C3B8->unk12 = 0;
    D_8006C3B8->unk2E = 0;
    D_8006C3B8->initState++;
    if (D_8006C3B8->zPriority == 0) {
        D_8006C3B8->zPriority = g_zEntityCenter - 0xC;
    }
}

void func_801BD6F8(Entity* arg0) {
    if (arg0->initState == 0) {
        arg0->initState++;
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BD720);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BD848);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BD9A0);

void func_801BDCE4(Entity* entity) {
    u16 subId;

    PreventEntityFromRespawning(entity);

    if (!(D_8009796E & 2)) {
        DestroyEntity(entity);
        return;
    }

    subId = entity->subId &= 0xFFF;

    if (subId < 0x80) {
        entity->objectId = OBJECT_03;
        entity->pfnUpdate = EntityCandleDrop;
        entity->animationFrameDuration = 0;
        entity->animationFrameIndex = 0;
    } else {
        subId -= 0x80;
        entity->objectId = OBJECT_0A;
        entity->pfnUpdate = (PfnEntityUpdate)EntityCandleHeartDrop;
    }

    entity->subId = subId;
    entity->unk6D = 0x10;
    entity->initState = 0;
}

// https://decomp.me/scratch/W8pIb branch problem, probably aspsx
#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BDD9C);
#else
void func_801BDD9C(void) {
    if (D_8006C3B8->accelerationY >= 0) {
        D_8006C3B8->unk84.value += D_8006C3B8->unk88;
        D_8006C3B8->accelerationX = D_8006C3B8->unk84.value;

        if ((D_8006C3B8->accelerationX == 0x10000) ||
            (D_8006C3B8->accelerationX == -0x10000)) {
            D_8006C3B8->unk88 = -D_8006C3B8->unk88;
        }
    }

    if (D_8006C3B8->accelerationY < 0x4000) {
        D_8006C3B8->accelerationY += 0x2000;
    }
}
#endif

void func_801BDE20(u16 arg0) {
    Unkstruct7 sp10;

    if (D_8006C3B8->accelerationX < 0) {
        D_8003C7BC(D_8006C3B8->posX.Data.high, D_8006C3B8->posY.Data.high - 7,
                   &sp10, 0);
        if (sp10.sp10 & 5) {
            D_8006C3B8->accelerationY = 0;
        }
    }

    D_8003C7BC(D_8006C3B8->posX.Data.high, D_8006C3B8->posY.Data.high + 7,
               &sp10, 0);

    if (arg0) {
        if (!(sp10.sp10 & 5)) {
            MoveEntity();
            FallEntity();
            return;
        }

        D_8006C3B8->accelerationX = 0;
        D_8006C3B8->accelerationY = 0;

        if (sp10.sp10 & 4) {
            D_8006C3B8->posY.value += 0x2000;
            return;
        }

        D_8006C3B8->posY.Data.high =
            (u16)D_8006C3B8->posY.Data.high + (u16)sp10.sp28;
        return;
    }

    if (!(sp10.sp10 & 5)) {
        MoveEntity();
        func_801BDD9C();
    }
}

void CollectHeart(u16 heartSize) {
    s32* hearts;

    g_pfnPlaySfx(NA_SE_PL_COLLECT_HEART);
    hearts = (s32*)&g_playerHeart;
    *hearts += c_HeartPrizes[heartSize];

    if (g_playerHeart->max < *hearts) {
        *hearts = g_playerHeart->max;
    }

    DestroyEntity(D_8006C3B8);
}

void CollectGold(u16 goldSize) {
    s32 *gold, *unk;
    u16 goldSizeIndex;

    g_pfnPlaySfx(NA_SE_PL_COLLECT_GOLD);
    gold = &g_playerGold;
    goldSizeIndex = goldSize - 2;
    *gold += c_GoldPrizes[goldSizeIndex];
    if (*gold > MAX_GOLD) {
        *gold = MAX_GOLD;
    }

    unk = &D_80097410;
    if (*unk) {
        g_pfnFreePolygons(D_80097414);
        *unk = 0;
    }

    func_801C33D8(D_80181CEC[goldSizeIndex], 1);
    DestroyEntity(D_8006C3B8);
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BE0D8); // Unique

void CollectHeartVessel(void) {
    if (g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
        g_pfnPlaySfx(NA_SE_PL_COLLECT_HEART);
        g_playerHeart->current += HEART_VESSEL_RICHTER;

        if (g_playerHeart->max < g_playerHeart->current) {
            g_playerHeart->current = g_playerHeart->max;
        }
    } else {
        g_pfnPlaySfx(NA_SE_PL_COLLECT_HEART);
        D_8003C848(HEART_VESSEL_INCREASE, 0x4000);
    }
    DestroyEntity(D_8006C3B8);
}

void CollectLifeVessel(void) {
    g_pfnPlaySfx(NA_SE_PL_COLLECT_HEART);
    D_8003C848(5, 0x8000);
    DestroyEntity(D_8006C3B8);
}

void func_801BE2E4(void) { DestroyEntity(D_8006C3B8); }

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", EntityCandleDrop);

void func_801BEB80(Entity* entity) {
    u32 temp_v0;

    if (entity->initState == 0) {
        InitializeEntity(&D_80180BE0);
        entity->animationSet = 2;
        entity->animationFrameIndex = 0;
        entity->animationFrameDuration = 0;
        entity->blendMode = 0x30;

        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->blendMode = 0x10;
        }

        temp_v0 = entity->subId & 0xFF00;
        if (temp_v0) {
            entity->zPriority = temp_v0 >> 8;
        }

        entity->subId = entity->subId & 0xF;
        entity->accelerationY = D_80181DA8[entity->subId];
        return;
    }

    entity->posY.value += entity->accelerationY;
    if (!AnimateEntity(D_80181E54[entity->subId], entity)) {
        DestroyEntity(entity);
    }
}

POLY_GT4* func_801BEC7C(Entity* entity, s32 arg1) {
    POLY_GT4* poly;
    s16 left, top, right, bottom;

    poly = &D_80086FEC[entity->firstPolygonIndex];

    left = entity->posX.Data.high - 7;
    right = entity->posX.Data.high + 7;
    poly->x2 = left;
    poly->x0 = left;
    poly->x3 = right;
    poly->x1 = right;

    top = entity->posY.Data.high - 7;
    bottom = entity->posY.Data.high + 7;
    poly->y1 = top;
    poly->y0 = top;
    poly->y3 = bottom;
    poly->y2 = bottom;

    if (arg1 & RENDERFLAGS_NOSHADOW) {
        poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 =
            poly->g2 = poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
                255;
    } else {
        poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 =
            poly->g2 = poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
                128;
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", EntityCandleHeartDrop);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BF308);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801BF5B8);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C0088); // Unique

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C01B0);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C070C);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C07FC); // Unique

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C090C);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C0A3C);

void func_801C0B24(Entity* entity) {
    if (entity->initState == 0) {
        entity->accelerationY = D_80181F04[entity->unk94];
        entity->unk34 = 0x0C002000;
        entity->palette = 0x8195;
        entity->animationSet = 2;
        entity->animationFrame = D_80181F1C[entity->subId];
        entity->blendMode = 0x10;
        entity->initState++;
        return;
    }

    entity->animationFrameDuration++;
    entity->posY.value -= entity->accelerationY;

    if (!(entity->animationFrameDuration & 1)) {
        entity->animationFrame++;
    }

    if (D_80181F20[entity->subId] < entity->animationFrameDuration) {
        DestroyEntity(entity);
    }
}

void func_801C0C14(Entity* entity) {
    u16 temp_v0;
    u32 temp2;

    if (!entity->initState) {
        entity->unk34 = 0x0C002000;
        entity->palette = 0x8195;
        entity->animationSet = 5;
        entity->animationFrame = 1;
        entity->blendMode = 0x10;
        entity->unk19 = 3;
        temp_v0 = D_80181EDC[entity->subId];
        entity->unk1A = temp_v0;
        entity->unk1C = temp_v0;
        temp2 = D_80181EEC[entity->subId];
        entity->initState += 1;
        entity->accelerationY = temp2;
        return;
    }

    entity->animationFrameDuration++;
    entity->posY.value -= entity->accelerationY;

    if (!(entity->animationFrameDuration & 1)) {
        entity->animationFrame++;
    }

    if (entity->animationFrameDuration >= 0x25) {
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C0D08);

bool func_801C0F38(Unkstruct6* unk) {
    Unkstruct7 a;

    FallEntity();
    D_8006C3B8->posX.value += D_8006C3B8->accelerationX;
    D_8006C3B8->posY.value += D_8006C3B8->accelerationY;

    if (D_8006C3B8->accelerationY >= 0) {
        s16 posX = D_8006C3B8->posX.Data.high;
        s16 posY = D_8006C3B8->posY.Data.high;
        posX += unk->x;
        posY += unk->y;
        D_8003C7BC(posX, posY, &a, 0);
        if (a.sp10 & 1) {
            D_8006C3B8->posY.Data.high += a.sp28;
            D_8006C3B8->accelerationY = -D_8006C3B8->accelerationY / 2;
            if (D_8006C3B8->accelerationY > -0x10000) {
                return true;
            }
        }
    }
    return false;
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C1034);

void func_801C15B4(Entity* entity) {
    u32 temp_v0;

    if (entity->initState == 0) {
        InitializeEntity(D_80180BE0);
        entity->palette = 0x8170;
        entity->animationSet = 5;
        entity->animationFrame = 1;
        entity->blendMode = 0x30;

        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->blendMode = 0x10;
        }

        temp_v0 = entity->subId & 0xFF00;
        if (temp_v0 != 0) {
            entity->zPriority = temp_v0 >> 8;
        }

        entity->zPriority += 8;
        return;
    }

    entity->animationFrameDuration++;
    entity->posY.value -= 0x4000;

    if (!(entity->animationFrameDuration & 1)) {
        entity->animationFrame++;
    }

    if (entity->animationFrameDuration >= 0x25) {
        DestroyEntity(entity);
    }
}

void func_801C16B4(Entity* entity) {
    if (entity->initState == ENTITY_INITSTATE_0) {
        InitializeEntity(&D_80180BE0);
        entity->unk6C = 0xF0;
        entity->unk1A = 0x1A0;
        entity->unk1C = 0x1A0;
        entity->animationSet = 8;
        entity->animationFrame = 1;
        entity->zPriority += 0x10;

        if (entity->subId != 0) {
            entity->palette = entity->subId;
        } else {
            entity->palette = 0x8160;
        }

        entity->initState++;
        return;
    }

    MoveEntity();

    if (AnimateEntity(&D_80181F30, entity) == 0) {
        DestroyEntity(entity);
    }
}

void func_801C1780(u16 objectId, Entity* ent1, Entity* ent2) {
    DestroyEntity(ent2);
    ent2->objectId = objectId;
    ent2->pfnUpdate = D_80180A90[objectId];
    ent2->posX.Data.high = ent1->posX.Data.high;
    ent2->posY.Data.high = ent1->posY.Data.high;
    ent2->unk5A = ent1->unk5A;
    ent2->zPriority = ent1->zPriority;
    ent2->animationSet = ent1->animationSet;
    ent2->unk34 = 0xCD002000;

    if ((u16)ent1->palette & 0x8000) {
        ent2->palette = ent1->unk6A;
        return;
    }

    ent2->palette = (s16)ent1->palette;
}

void func_801C1848(void) {
    Entity* entity;
    s8 temp_s4 = Random() & 3;
    s16 temp_s3 = ((Random() & 0xF) << 8) - 0x800;
    s32 i;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (entity != NULL) {
            func_801BBBC0(2, D_8006C3B8, entity);
            entity->unk84.Data1.unk1 = 6 - i;
            entity->unk80.data = temp_s3;
            entity->unk84.Data1.unk0 = temp_s4;
        }
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C1900);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C1AD8);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C20B8);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C27B8);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C29B0);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", EntityAbsorbOrb);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C2E3C);

void EntityRoomForeground(Entity* entity) {
    ObjInit2* objInit = &D_80182014[entity->subId];

    if (entity->initState == 0) {
        InitializeEntity(D_80180C1C);
        entity->animationSet = objInit->animationSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk4.data;
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

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C33D8);

void func_801C3708(void) {
    s32 temp_s0;
    s32 temp_v0;

    temp_s0 = func_801BCF74(&D_8018216C);
    temp_v0 = func_801BD720(&D_80182174, 3);

    if ((temp_s0 == 0x80) || (temp_v0 & 2)) {
        func_801BD52C(5);
        return;
    }

    if (D_8006C3B8->unk7C.modeU8.unk0 == 0) {
        if (func_801BCBEC() < 0x40) {
            if (D_8006C3B8->unk14 != (func_801BCC5C() & 1)) {
                func_801BD52C(4);
            }
        }
    } else {
        D_8006C3B8->unk7C.modeU8.unk0 = (s8)D_8006C3B8->unk7C.modeU8.unk0 - 1;
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", EntityBoneScimitar);

// Not matching by a single instruction, must likely compiler version
// https://decomp.me/scratch/irC21
#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C3E94);
#else
void func_801C3E94(Entity* entity) {
    if (entity->initState) {
        entity->unk88--;
        if (entity->unk88 & 0xFF) {
            entity->unk1E += D_801820E4[entity->subId];
            FallEntity();
            MoveEntity();
            return;
        }
        entity->objectId = OBJECT_02;
        entity->pfnUpdate = func_801BEB80;
        entity->subId = 0;
        entity->initState = 0;
        return;
    }
    InitializeEntity(&D_80180C58);
    entity->unk19 = 4;
    entity->animationFrame = entity->subId + 16;

    if (entity->unk14 != 0) {
        entity->accelerationX = -entity->accelerationX;
    }

    if (entity->subId & 0xF00) {
        entity->palette += entity->subId / 256;
    }
}
#endif

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C3F9C); // Unique

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C4198); // Unique

void func_801C4550(void) {
    if (D_8006C3B8->unk82 > 0) {
        D_8006C3B8->unk82 -= 3;
    } else {
        func_801BD52C(D_801822B4[(Random() & 7)]);
        D_8006C3B8->unk82 = 0x100;
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C45BC); // Unique

void func_801C4CC0(void) {
    if (D_8006C3B8->subId != 0) {
        D_8006C3B8->unk1E += 0x80;
    } else {
        D_8006C3B8->unk1E -= 0x80;
    }

    D_8006C3B8->unk1E &= 0xFFF;
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C4D18); // Unique

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C4EAC);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C53AC);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C5568); // Unique

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C5D20);

void func_801C5F2C(Entity* arg0) {
    if ((func_801BCF74(&D_801824B8) & 0x60) == 0x60) {
        arg0->posX.value -= arg0->accelerationX;
    }

    if (!(func_801BD720(&D_801824C0, 3) & 2)) {
        if ((--arg0->unk7C.modeU8.unk0) == 0) {
            func_801BD52C(4);
        }
    } else {
        func_801BD52C(5);
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C5FC4); // Unique

void func_801C6494(Entity* entity) {
    if (entity->initState) {
        entity->unk88--;
        if (entity->unk88 & 0xFF) {
            entity->unk1E += D_80182424[entity->subId];
            FallEntity();
            MoveEntity();
            return;
        }

        entity->objectId = OBJECT_02;
        entity->pfnUpdate = (PfnEntityUpdate)func_801BEB80;
        entity->subId = 0;
        entity->initState = ENTITY_INITSTATE_0;
        return;
    }

    InitializeEntity(&D_80180C94);
    entity->unk19 = 4;
    entity->animationFrame = entity->subId + 15;

    if (entity->unk14 != 0) {
        entity->accelerationX = -entity->accelerationX;
    }
}

void func_801C6574(Entity* entity) {
    s32 var_a0;
    u32 value;

    if (entity->initState) {
        if (entity->unk34 & 0x100) {
            func_801BD568(0, 0);
            return;
        }

        entity->unk1E += 0x80;
        entity->accelerationY += 0x2400;
        MoveEntity();

        if (entity->posY.Data.high > 240) {
            DestroyEntity(entity);
        }
    } else {
        InitializeEntity(&D_80180CA0);
        entity->posY.value -= 0x1000;
        value = func_801BCBEC();
        value /= 32;
        value = CLAMP_MAX(value, 7);
        var_a0 = D_80182488[value];
        value = entity->unk14;

        if (value > 0) {
            var_a0 = -var_a0;
        }

        entity->accelerationY = -0x48000;
        entity->accelerationX = var_a0;
        entity->unk19 = 4;
    }
}

void func_801C6678(Entity* entity) {
    if (entity->initState == 0) {
        InitializeEntity(&D_80180C88);
        entity->unk1A = 0x120;
        entity->unk1C = 0x200;
        entity->unk6C = 0;
        entity->unk3C = 0;
        entity->unk19 = entity->unk19 | 0xB;
        return;
    }

    entity->unk14 = entity[-1].unk14;
    entity->zPriority = entity[-1].zPriority - 1;
    entity->animationFrame = entity[-1].animationFrame;
    entity->posX.Data.high = entity[-1].posX.Data.high;
    entity->posY.Data1.unk2 = entity[-1].posY.value - 0x14;

    if (entity[-1].objectId != 0x2E) {
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C672C); // Unique

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C6B24); // Unique

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C6C6C); // Unique

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C7048); // Unique

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C7538); // Unique

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C7654); // Unique

void func_801C77B8(Entity* entity) {
    s16 temp_v1_2;

    switch (entity->initState) {
    case ENTITY_INITSTATE_0:
        InitializeEntity(&D_80180CF4);
        entity->unk19 = 3;
        entity->unk1C = 0x100;
        entity->unk1A = 0x100;
        entity->accelerationX = 0;
        entity->animationFrame = entity->subId + 8;
        entity->accelerationY = D_80182600[entity->subId];
        break;

    case ENTITY_INITSTATE_1:
        MoveEntity();
        temp_v1_2 = entity->unk1C - 8;
        entity->accelerationY -= 0x400;
        entity->unk1C = temp_v1_2;
        entity->unk1A = temp_v1_2;

        if ((temp_v1_2 << 0x10) == 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

void func_801C7884(Entity* entity) {
    u16 subId = entity->subId;

    switch (entity->initState) {
    case ENTITY_INITSTATE_0:
        InitializeEntity(&D_80180BD4);
        entity->unk3C = 0;

    case ENTITY_INITSTATE_1:
        MoveEntity();
        AnimateEntity(D_80181D3C[subId], entity);

        entity->accelerationY = rsin(entity->unk1E) * 2;
        entity->unk1E += 0x20;

        if (entity[-1].initState != 1) {
            entity->objectId = OBJECT_03;
            entity->pfnUpdate = EntityCandleDrop;
            entity->animationFrameDuration = 0;
            entity->animationFrameIndex = 0;
            entity->initState = ENTITY_INITSTATE_0;
            entity->unk3C = 1;
        }
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C7958); // Unique

s32 func_801C7CF0(Unkstruct5* arg0) {
    s16 var_v0_2;

    var_v0_2 = D_800733DA - arg0->unk2;
    var_v0_2 = ABS_ALT(var_v0_2);

    if (var_v0_2 >= 0x19) {
        var_v0_2 = 0;
    } else {
        var_v0_2 = D_800733DE - arg0->unk6;
        var_v0_2 = ABS_ALT(var_v0_2);
        var_v0_2 = var_v0_2 < 0x21;
    }

    return var_v0_2;
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C7D68);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C8ADC);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", EntityAreaTitlePopup);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C9930);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C9D18);

POLY_GT4* func_801C9E68(POLY_GT4* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = (POLY_GT4*)poly->tag;
        } else {
            return poly;
        }
    }
    return NULL;
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801C9E98);

POLY_GT4* func_801C9F14(POLY_GT4* startPoly, s32 count) {
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
        if (poly == NULL)
            return NULL;
        poly->p3 = unk;
    }

    return poly;
}

void func_801C9F9C(unkStruct3* arg0) {
    arg0->unk12.data1.unk1 = 0;
    arg0->unk1E.data1.unk1 = 0;
    arg0->unk2B = 0;
    arg0->unk0->unk14 = 0;
    arg0->unk0->unk16 = 0;
    arg0->unk0->unkA = 0;
    arg0->unk0->unk8 = 0;
    arg0->unk0->unkE = 0;
    arg0->unk0->unkC = 0;
    arg0->unk0->unk12.data = 0;
    arg0->unk0->unk10 = 0;
    arg0->unk0->unk18 = 0;
    arg0->unk0->unk1A = 0;
    arg0->unk0->unk1C = 0;
    arg0->unk0->unk1E.data = 0;
    arg0->unk0->unk24 = 0;
    arg0->unk0->unk25 = 0;
    arg0->unk0->unk28 = 0;
    arg0->unk0->unk2A = 0;
    arg0->unk0->unk20 = 0;
    arg0->unk0->unk22 = 0;
}

void func_801CA07C(unkStruct3* arg0) {
    func_801C9F9C(arg0);
    arg0->unk2B = 8;
    arg0->unk0->unk2B = 1;
    arg0->unk0->unk7 = 2;
    arg0->unk0->unk32 = 0xA;
}

void func_801CA0D0(unkStruct3* arg0) {
    arg0->unk2B = 0;
    arg0->unk32 = 8;
    arg0->unk0->unk2B = 0;
    arg0->unk0->unk7 = 4;
    arg0->unk0->unk32 = 8;
}

//! FAKE
s32 func_801CA0FC(s32 arg0, u8 arg1) {
    s32 var_v0;
    s32 ret = 0;
    s32* j = arg0 + 4;
    u8* var_v1;
    s32 i;

    for (i = 0; i < 4; i++, j += 3) {
        var_v1 = j;
        do {
            var_v0 = *var_v1 - arg1;

            if (var_v0 < 0) {
                var_v0 = 0;
            } else {
                ret |= 1;
            }

            *var_v1 = var_v0;
            var_v1++;
        } while ((s32)var_v1 < (s32)j + 3);
    }

    return ret;
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/394D4", func_801CA160); // Unique
