/*
 * File: 394D4.c
 * Overlay: NZ0
 * Description: Alchemy Laboratory
 */

#include "stage.h"

void DestroyEntity(Entity* item);
void func_8018F928(Entity*);
void func_8019B858(void);
void func_801BDD9C(void);
s32 func_801BCF74(s32*);
s32 func_801BD720(s32*, s32);
void EntityExplosion(Entity*);
void func_801C29B0(s32);
void func_801C33D8(const u32*, s32);
void func_801C0B24(Entity* entity);
void func_801C4CC0(void);

extern u32 g_randomNext;
extern PfnEntityUpdate D_80180A90[];
extern s16 D_80181978[];
extern s8 c_HeartPrizes[];
extern Entity* g_CurrentEntity;
extern const u16 D_80180BE0[];
extern s32 D_80181DA8[];
extern const u8* D_80181E54[];
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
extern const u8 D_80181F30;
extern const u16* D_80180CF4;
extern s32 D_80182600[];
extern s32 D_8018216C;
extern s32 D_80182174;
extern const u16* D_80180BD4;
extern const s32 D_80181D3C[];
extern const u16* D_80180C94;
extern u16 D_80182424[];
extern const u32* D_80181CEC[];
extern const s32 c_GoldPrizes[];
extern const u16 D_80180CA0[];
extern u32 D_80182488[];
extern const u16* D_80180C58;
extern s16 D_801820E4[];
extern const u16 D_80180C04[];
extern u8 D_801825F0;
extern s32 D_80180C70;
extern u32 D_801822BC[];
extern u32 D_801822C8[];

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B0958);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B0A20);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B0AA4);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", EntityBreakable);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B11C0);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B12E8);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B14C4);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B1770);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B19A0);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B1C18);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B1E54);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B20CC);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B23B4);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B25C4);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B2874);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B2978);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B2AD8);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B2D08);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B2FD8);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B3294);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B3534);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B3648);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B37C0);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B3A50);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B3B78);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B3C38);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B3FCC);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B4518);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B4690);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B4778);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B54A8);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B5654);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B5778);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B69E8);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B6AAC);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B6BBC);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B6DE4);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B7034);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B74CC);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B7520);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B76E4);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B7740);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B77F8);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B797C);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B79A8);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B7C54);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B7D58);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B8E0C);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B8F94);

s32 Random(void) {
    // Linear congruential generator algorithm

    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", Update);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801B9800);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", TestCollisions);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", EntityNumericDamage);

void CreateEntityFromLayout(Entity* entity, LayoutObject* initDesc) {
    DestroyEntity(entity);
    entity->objectId = initDesc->objectId & 0x3FF;
    do { //! FAKE https://decomp.me/scratch/zysYC
        entity->pfnUpdate = D_80180A90[entity->objectId];
    } while (0);
    entity->posX.i.hi = initDesc->posX - D_8007308E;
    entity->posY.i.hi = initDesc->posY - (u16)D_80073092;
    entity->subId = initDesc->subId;
    entity->objectRoomIndex = initDesc->objectRoomIndex >> 8;
    entity->unk68 = (initDesc->objectId >> 0xA) & 7;
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801BB188);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801BB2A0);

void func_801BB3B8(s16 arg0) {
    while (true) {
        if ((D_801CAA74->posX != 0xFFFE) && (D_801CAA74->posX >= (s32)arg0)) {
            break;
        }
        D_801CAA74++;
    }
}

void func_801BB404(s16 arg0) {
    while (true) {
        if (!(D_801CAA74->posX == 0xFFFF) &&
            (((s32)arg0 >= D_801CAA74->posX) || (D_801CAA74->posX == 0xFFFE))) {
            break;
        }
        D_801CAA74--;
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801BB45C);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801BB558);

void func_801BB66C(s16 arg0) {
    while (true) {
        if ((D_801CAA78->posY != 0xFFFE) && (D_801CAA78->posY >= (s32)arg0)) {
            break;
        }
        D_801CAA78++;
    }
}

void func_801BB6B8(s16 arg0) {
    while (true) {
        if (!(D_801CAA78->posY == 0xFFFF) &&
            (((s32)arg0 >= D_801CAA78->posY) || (D_801CAA78->posY == 0xFFFE))) {
            break;
        }
        D_801CAA78--;
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801BB710);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801BB80C);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801BB920);

// TODO: try after resolving aspsx
// https://decomp.me/scratch/cJ3CF
INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801BBA98);

void CreateEntityFromCurrentEntity(u16 objectId, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = D_80180A90[objectId];
    entity->posX.i.hi = g_CurrentEntity->posX.i.hi;
    entity->posY.i.hi = g_CurrentEntity->posY.i.hi;
}

void CreateEntityFromEntity(u16 objectId, Entity* ent1, Entity* ent2) {
    DestroyEntity(ent2);
    ent2->objectId = objectId;
    ent2->pfnUpdate = D_80180A90[objectId];
    ent2->posX.i.hi = ent1->posX.i.hi;
    ent2->posY.i.hi = ent1->posY.i.hi;
}

s32 func_801BBC3C(Unkstruct5* arg0) {
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

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", EntityRedDoor);

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

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801BCAD4);

/*
 * Returns the absolute distance from g_CurrentEntity to player in the X Axis
 */
s32 func_801BCBEC(void) {
    s16 xDistance = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (xDistance < 0) {
        xDistance = -xDistance;
    }
    return xDistance;
}

/*
 * Returns the absolute distance from g_CurrentEntity to player in the Y Axis
 */
s32 func_801BCC28(void) {
    s32 yDistance = g_CurrentEntity->posY.i.hi - PLAYER.posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

s16 func_801BCC5C(void) {
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

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801BCCFC);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801BCF74);

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
    g_CurrentEntity->accelerationX = func_801BD1BC(arg0, arg1);
    g_CurrentEntity->accelerationY = func_801BD1BC(arg0 - 0x40, arg1);
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

    x = arg0 - g_CurrentEntity->posX.i.hi;
    y = arg1 - g_CurrentEntity->posY.i.hi;

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

u16 func_801BD41C(s16 x, s16 y) { return ratan2(y, x); }

u16 func_801BD44C(Entity* a, Entity* b) {
    s32 diffX = b->posX.i.hi - a->posX.i.hi;
    s32 diffY = b->posY.i.hi - a->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_801BD484(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s16 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
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

void func_801BD52C(u8 step) {
    Entity* entity;

    entity = g_CurrentEntity;
    entity->step = step;
    entity->unk2E = 0;
    entity->animationFrameIndex = 0;
    entity->animationFrameDuration = 0;
}

void func_801BD54C(u8 arg0) {
    Entity* entity;

    entity = g_CurrentEntity;
    entity->unk2E = arg0;
    entity->animationFrameIndex = 0;
    entity->animationFrameDuration = 0;
}

void func_801BD568(u16 arg0, u16 arg1) {
    if (arg1 != 0) {
        func_801C29B0(arg1);
    }

    if (arg0 == 0xFF) {
        DestroyEntity(g_CurrentEntity);
        return;
    }

    g_CurrentEntity->objectId = ENTITY_EXPLOSION;
    g_CurrentEntity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
    g_CurrentEntity->subId = arg0;
    g_CurrentEntity->animationFrame = 0;
    g_CurrentEntity->unk19 = 0;
    g_CurrentEntity->step = 0;
    g_CurrentEntity->unk2E = 0;
}

void InitializeEntity(u16 arg0[]) {
    u16 temp_v1;
    Unkstruct5* temp_v0;

    g_CurrentEntity->animationSet = *arg0++;
    g_CurrentEntity->animationFrame = *arg0++;
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

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801BD720);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801BD848);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801BD9A0);

void ReplaceBreakableWithItemDrop(Entity* entity) {
    u16 subId;

    PreventEntityFromRespawning(entity);

    if (!(D_8009796E & 2)) {
        DestroyEntity(entity);
        return;
    }

    subId = entity->subId &= 0xFFF;

    if (subId < 0x80) {
        entity->objectId = ENTITY_PRICE_DROP;
        entity->pfnUpdate = EntityPriceDrop;
        entity->animationFrameDuration = 0;
        entity->animationFrameIndex = 0;
    } else {
        subId -= 0x80;
        entity->objectId = ENTITY_INVENTORY_DROP;
        entity->pfnUpdate = (PfnEntityUpdate)EntityInventoryDrop;
    }

    entity->subId = subId;
    entity->unk6D = 0x10;
    entity->step = 0;
}

// https://decomp.me/scratch/W8pIb branch problem, probably aspsx
#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801BDD9C);
#else
void func_801BDD9C(void) {
    if (g_CurrentEntity->accelerationY >= 0) {
        g_CurrentEntity->unk84.value += g_CurrentEntity->unk88;
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

void func_801BDE20(u16 arg0) {
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
        } else {
            g_CurrentEntity->posY.i.hi += res.unk18;
        }
    } else {
        if (!(res.unk0 & 5)) {
            MoveEntity();
            func_801BDD9C();
        }
    }
}

void CollectHeart(u16 heartSize) {
    s32* hearts;

    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    hearts = &D_80097B9C.hearts;
    *hearts += c_HeartPrizes[heartSize];

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

    func_801C33D8(D_80181CEC[goldSizeIndex], 1);
    DestroyEntity(g_CurrentEntity);
}

// https://decomp.me/scratch/2vxD2
// https://decomp.me/scratch/peM5t by stuckpixel
INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801BE0D8);

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

void CollectLifeVessel(void) {
    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_api.func_800FE044(5, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

void func_801BE2E4(void) { DestroyEntity(g_CurrentEntity); }

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", EntityPriceDrop);

void EntityExplosion(Entity* entity) {
    u32 temp_v0;

    if (entity->step == 0) {
        InitializeEntity(D_80180BE0);
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

    entity->posY.val += entity->accelerationY;
    if (!AnimateEntity(D_80181E54[entity->subId], entity)) {
        DestroyEntity(entity);
    }
}

void func_801BEC7C(Entity* entity, s32 arg1) {
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

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", EntityInventoryDrop);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801BF308);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", EntityRelicOrb);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", EntityHeartDrop);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", EntityUnkId0E);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C070C);

void func_801C07FC(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180C04);
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

// https://decomp.me/scratch/0VI4v
INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C090C);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C0A3C);

void func_801C0B24(Entity* entity) {
    if (entity->step == 0) {
        entity->accelerationY = D_80181F04[entity->unk94];
        entity->unk34 = 0x0C002000;
        entity->palette = 0x8195;
        entity->animationSet = 2;
        entity->animationFrame = D_80181F1C[entity->subId];
        entity->blendMode = 0x10;
        entity->step++;
    } else {
        entity->animationFrameDuration++;
        entity->posY.val -= entity->accelerationY;

        if (!(entity->animationFrameDuration & 1)) {
            entity->animationFrame++;
        }

        if (D_80181F20[entity->subId] < (s32)entity->animationFrameDuration) {
            DestroyEntity(entity);
        }
    }
}

void func_801C0C14(Entity* entity) {
    u16 temp_v0;
    u32 temp2;

    if (!entity->step) {
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
        entity->step += 1;
        entity->accelerationY = temp2;
        return;
    }

    entity->animationFrameDuration++;
    entity->posY.val -= entity->accelerationY;

    if (!(entity->animationFrameDuration & 1)) {
        entity->animationFrame++;
    }

    if (entity->animationFrameDuration >= 0x25) {
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C0D08);

bool func_801C0F38(Unkstruct6* unk) {
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

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C1034);

void EntityIntenseExplosion(Entity* entity) {
    u32 temp_v0;

    if (entity->step == 0) {
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
    entity->posY.val -= 0x4000;

    if (!(entity->animationFrameDuration & 1)) {
        entity->animationFrame++;
    }

    if (entity->animationFrameDuration >= 0x25) {
        DestroyEntity(entity);
    }
}

void func_801C16B4(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(D_80180BE0);
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

        entity->step++;
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
    ent2->posX.i.hi = ent1->posX.i.hi;
    ent2->posY.i.hi = ent1->posY.i.hi;
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
    s8* temp_s3 = (s8*)((Random() & 0xF) << 8) - 0x800; // TODO: fix type
    s32 i;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (entity != NULL) {
            CreateEntityFromEntity(2, g_CurrentEntity, entity);
            entity->unk84.U8.unk1 = 6 - i;
            entity->unk80.modeS16.unk0 = temp_s3;
            entity->unk84.U8.unk0 = temp_s4;
        }
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C1900);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C1AD8);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C20B8);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C27B8);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C29B0);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", EntityAbsorbOrb);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", EntityEnemyBlood);

void EntityRoomForeground(Entity* entity) {
    ObjInit2* objInit = &D_80182014[entity->subId];

    if (entity->step == 0) {
        InitializeEntity(D_80180C1C);
        entity->animationSet = objInit->animationSet;
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

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C33D8);

void func_801C3708(void) {
    s32 temp_s0;
    s32 temp_v0;

    temp_s0 = func_801BCF74(&D_8018216C);
    temp_v0 = func_801BD720(&D_80182174, 3);

    if ((temp_s0 == 0x80) || (temp_v0 & 2)) {
        func_801BD52C(5);
        return;
    }

    if (g_CurrentEntity->unk7C.U8.unk0 == 0) {
        if (func_801BCBEC() < 0x40) {
            if (g_CurrentEntity->facing != (func_801BCC5C() & 1)) {
                func_801BD52C(4);
            }
        }
    } else {
        g_CurrentEntity->unk7C.U8.unk0 = (s8)g_CurrentEntity->unk7C.U8.unk0 - 1;
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", EntityBoneScimitar);

// Not matching by a single instruction, must likely compiler version
// https://decomp.me/scratch/irC21
#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", EntityFallingDebris);
#else
void EntityFallingDebris(Entity* entity) {
    if (entity->step) {
        entity->unk88--;
        if (entity->unk88 & 0xFF) {
            entity->unk1E += D_801820E4[entity->subId];
            FallEntity();
            MoveEntity();
            return;
        }
        entity->objectId = ENTITY_EXPLOSION;
        entity->pfnUpdate = EntityExplosion;
        entity->subId = 0;
        entity->step = 0;
        return;
    }
    InitializeEntity(&D_80180C58);
    entity->unk19 = 4;
    entity->animationFrame = entity->subId + 16;

    if (entity->facing != 0) {
        entity->accelerationX = -entity->accelerationX;
    }

    if (entity->subId & 0xF00) {
        entity->palette += entity->subId / 256;
    }
}
#endif

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C3F9C); // Unique

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C4198); // Unique

void func_801C4550(void) {
    if (g_CurrentEntity->unk80.modeS16.unk2 > 0) {
        g_CurrentEntity->unk80.modeS16.unk2 -= 3;
    } else {
        func_801BD52C(D_801822B4[(Random() & 7)]);
        g_CurrentEntity->unk80.modeS16.unk2 = 0x100;
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C45BC); // Unique

void func_801C4CC0(void) {
    if (g_CurrentEntity->subId != 0) {
        g_CurrentEntity->unk1E += 0x80;
    } else {
        g_CurrentEntity->unk1E -= 0x80;
    }

    g_CurrentEntity->unk1E &= 0xFFF;
}

void func_801C4D18(Entity* entity) {
    s32 var_v0;

    if (entity->unk34 & 0x100) {
        func_801C29B0(0x66B);
        func_801BD568(0, 0);
        return;
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180C70);
        entity->unk19 = 4;
        entity->accelerationY = D_801822C8[entity->subId];
        var_v0 = D_801822BC[entity->subId];

        if (entity->facing == 0) {
            entity->accelerationX = -var_v0;
        } else {
            entity->accelerationX = var_v0;
        }

        entity->unk7C.s = -0x40;

        if (entity->subId == 2) {
            entity->step++;
            return;
        }
        break;

    case 1:
        func_801C4CC0();
        if ((u16)entity->unk7C.s < 0x20) {
            if (entity->facing != 0) {
                var_v0 = entity->accelerationX - 0x2000;
            } else {
                var_v0 = entity->accelerationX + 0x2000;
            }
            entity->accelerationX = var_v0;
        }

        entity->unk7C.s += 1;
        MoveEntity();
        break;

    case 2:
        func_801C4CC0();
        entity->accelerationY += 0x2000;
        MoveEntity();
        break;
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C4EAC);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C53AC);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C5568); // Unique

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C5D20);

void func_801C5F2C(Entity* arg0) {
    if ((func_801BCF74(&D_801824B8) & 0x60) == 0x60) {
        arg0->posX.val -= arg0->accelerationX;
    }

    if (!(func_801BD720(&D_801824C0, 3) & 2)) {
        if ((--arg0->unk7C.U8.unk0) == 0) {
            func_801BD52C(4);
        }
    } else {
        func_801BD52C(5);
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C5FC4); // Unique

void func_801C6494(Entity* entity) {
    if (entity->step) {
        entity->unk88.S8.unk0--;
        if (entity->unk88.S8.unk0 & 0xFF) {
            entity->unk1E += D_80182424[entity->subId];
            FallEntity();
            MoveEntity();
            return;
        }

        entity->objectId = ENTITY_EXPLOSION;
        entity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
        entity->subId = 0;
        entity->step = 0;
        return;
    }

    InitializeEntity(&D_80180C94);
    entity->unk19 = 4;
    entity->animationFrame = entity->subId + 15;

    if (entity->facing != 0) {
        entity->accelerationX = -entity->accelerationX;
    }
}

void func_801C6574(Entity* entity) {
    s32 var_a0;
    u32 value;

    if (entity->step) {
        if (entity->unk34 & 0x100) {
            func_801BD568(0, 0);
            return;
        }

        entity->unk1E += 0x80;
        entity->accelerationY += 0x2400;
        MoveEntity();

        if (entity->posY.i.hi > 240) {
            DestroyEntity(entity);
        }
    } else {
        InitializeEntity(&D_80180CA0);
        entity->posY.val -= 0x1000;
        value = func_801BCBEC();
        value /= 32;
        value = CLAMP_MAX(value, 7);
        var_a0 = D_80182488[value];
        value = entity->facing;

        if (value > 0) {
            var_a0 = -var_a0;
        }

        entity->accelerationY = -0x48000;
        entity->accelerationX = var_a0;
        entity->unk19 = 4;
    }
}

void func_801C6678(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(&D_80180C88);
        entity->unk1A = 0x120;
        entity->unk1C = 0x200;
        entity->unk6C = 0;
        entity->unk3C = 0;
        entity->unk19 = entity->unk19 | 0xB;
        return;
    }

    entity->facing = entity[-1].facing;
    entity->zPriority = entity[-1].zPriority - 1;
    entity->animationFrame = entity[-1].animationFrame;
    entity->posX.i.hi = entity[-1].posX.i.hi;
    entity->posY.i.hi = entity[-1].posY.val - 0x14;

    if (entity[-1].objectId != 0x2E) {
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C672C); // Unique

// https://decomp.me/scratch/T0T7K mostly regalloc
INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C6B24);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C6C6C); // Unique

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C7048); // Unique

void func_801C7538(Entity* entity) {
    s32 new_var;
    s16 var_v0;

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180CF4);
        entity->unk19 = 4;
        entity->animationFrame = entity->subId;
        entity->palette += entity->unk84.S16.unk2;
        entity->accelerationX = entity->unk84.S16.unk0 << 12;
        entity->accelerationX += 0x8000 - (Random() << 8);
        entity->accelerationY -= (Random() & 0x1F) << 12;
        break;

    case 1:
        MoveEntity();
        entity->accelerationY += 0x2000;

        if (entity->accelerationX != 0) {
            if (entity->facing == 0) {
                new_var = (u16)entity->unk1E - 16;
                var_v0 = new_var;
            } else {
                var_v0 = entity->unk1E + 16;
            }
        } else if (entity->facing != 0) {
            var_v0 = entity->unk1E - 16;
        } else {
            var_v0 = entity->unk1E + 16;
        }

        entity->unk1E = var_v0;
        break;
    }
}

void func_801C7654(Entity* entity) {
    CollisionResult res;

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180BE0);
        entity->animationSet = 2;
        entity->palette = 0x816D;
        entity->blendMode = 0x70;
        entity->accelerationX = rcos(entity->unk1E) * 0x10;
        entity->accelerationY = rsin(entity->unk1E) * 0x10;
        break;

    case 1:
        AnimateEntity(&D_801825F0, entity);
        MoveEntity();
        entity->accelerationY += 0x2000;

        g_api.CheckCollision(entity->posX.i.hi, entity->posY.i.hi + 8,
                             &res.unk0, 0);

        if (res.unk0 & 1) {
            entity->unk19 = 2;
            entity->unk1C = 0x100;
            entity->accelerationY = 0x4000;
            entity->accelerationX *= 8;
            entity->step++;
        }
        break;

    case 2:
        MoveEntity();
        entity->unk1C -= 8;
        if (!(entity->unk1C << 0x10)) {
            DestroyEntity(entity);
        }
        break;
    }
}

void func_801C77B8(Entity* entity) {
    s16 temp_v1_2;

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180CF4);
        entity->unk19 = 3;
        entity->unk1C = 0x100;
        entity->unk1A = 0x100;
        entity->accelerationX = 0;
        entity->animationFrame = entity->subId + 8;
        entity->accelerationY = D_80182600[entity->subId];
        break;

    case 1:
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

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180BD4);
        entity->unk3C = 0;

    case 1:
        MoveEntity();
        AnimateEntity(D_80181D3C[subId], entity);

        entity->accelerationY = rsin(entity->unk1E) * 2;
        entity->unk1E += 0x20;

        if (entity[-1].step != 1) {
            entity->objectId = ENTITY_PRICE_DROP;
            entity->pfnUpdate = EntityPriceDrop;
            entity->animationFrameDuration = 0;
            entity->animationFrameIndex = 0;
            entity->step = 0;
            entity->unk3C = 1;
        }
    }
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", EntityBloodSkeleton);

s32 func_801C7CF0(Unkstruct5* arg0) {
    s16 diff;

    diff = PLAYER.posX.i.hi - arg0->unk2;
    diff = ABS(diff);

    if (diff >= 25) {
        diff = 0;
    } else {
        diff = PLAYER.posY.i.hi - arg0->unk6;
        diff = ABS(diff);
        diff = diff < 33;
    }

    return diff;
}

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C7D68);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C8ADC);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", EntityStageNamePopup);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C9930);

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C9D18);

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

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801C9E98);

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

void func_801C9F9C(POLY_GT4* poly) {
    poly->p1 = 0;
    poly->p2 = 0;
    poly->p3 = 0;
    ((POLY_GT4*)poly->tag)->x1 = 0;
    ((POLY_GT4*)poly->tag)->y1 = 0;
    ((POLY_GT4*)poly->tag)->y0 = 0;
    ((POLY_GT4*)poly->tag)->x0 = 0;
    ((POLY_GT4*)poly->tag)->clut = 0;
    *(u16*)&((POLY_GT4*)poly->tag)->u0 = 0;
    *(u16*)&((POLY_GT4*)poly->tag)->b1 = 0;
    *(u16*)&((POLY_GT4*)poly->tag)->r1 = 0;
    *(u16*)&((POLY_GT4*)poly->tag)->u1 = 0;
    ((POLY_GT4*)poly->tag)->tpage = 0;
    *(u16*)&((POLY_GT4*)poly->tag)->r2 = 0;
    *(u16*)&((POLY_GT4*)poly->tag)->b2 = 0;
    ((POLY_GT4*)poly->tag)->u2 = 0;
    ((POLY_GT4*)poly->tag)->v2 = 0;
    ((POLY_GT4*)poly->tag)->r3 = 0;
    ((POLY_GT4*)poly->tag)->b3 = 0;
    ((POLY_GT4*)poly->tag)->x2 = 0;
    ((POLY_GT4*)poly->tag)->y2 = 0;
}

void func_801CA07C(POLY_GT4* poly) {
    func_801C9F9C(poly);
    poly->p3 = 8;
    ((POLY_GT4*)poly->tag)->p3 = 1;
    ((POLY_GT4*)poly->tag)->code = 2;
    ((POLY_GT4*)poly->tag)->pad3 = 0xA;
}

void func_801CA0D0(POLY_GT4* poly) {
    poly->p3 = 0;
    poly->pad3 = 8;
    ((POLY_GT4*)poly->tag)->p3 = 0;
    ((POLY_GT4*)poly->tag)->code = 4;
    ((POLY_GT4*)poly->tag)->pad3 = 8;
}

//! FAKE
s32 func_801CA0FC(s32 arg0, u8 arg1) {
    s32 var_v0;
    s32 ret = 0;
    s32 j = arg0 + 4;
    u8* var_v1;
    s32 i;

    for (i = 0; i < 4; i++, j += 12) {
        var_v1 = (u8*)j;
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

INCLUDE_ASM("config/../asm/st/nz0/nonmatchings/30958", func_801CA160); // Unique
