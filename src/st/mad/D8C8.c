#include "stage.h"

void func_801908DC(s16);
void func_801909D8(s16);
void func_80190B7C(s16);
void func_80190C78(s16);
void SpawnExplosionEntity(u16, Entity*);
u8 func_80192914(s16 arg0, s16 arg1);
void ReplaceCandleWithDrop(Entity*);
void EntityCandleDrop(Entity*);
void EntityCandleHeartDrop(Entity*);
void func_80194218(Entity*);
void func_8019102C(u16 objectId, Entity* ent1, Entity* ent2);

// OFFSET FIXED
extern void (*D_8003C6B0)(s32);
extern void (*D_8003C6B8)(s32, s32, Unkstruct7*, s32);
extern void (*D_8003C6D8)(s32);
extern s32 g_pfnLoadObjLayout; // It's 8003C8C4!
extern Entity* D_8006C26C;
extern u16 D_80072B3E;
extern s16 D_80072B42;
extern u16 D_80072B58;
extern s16 D_80072E8A;
extern s16 D_80072E8E;
extern Entity D_80072E88[];
extern Entity D_8007D308[];
extern Entity D_8007E9CC;
extern void* D_8007EA88;
extern u16 D_80096EB8;
extern s32 D_80096EC0;
extern s32 D_80096EC4;
extern u32 D_80097364;
extern u8 D_8009741A;
extern Entity D_80075D88[];
extern s32 D_80096EAC;

// TODO FIX
extern s32 D_80096ED8[];
extern s32 D_800973B4;
extern POLY_GT4 D_800973B8[];

// ST/MAD
extern u16 D_80180544[];
extern ObjInit2 D_8018056C[];
extern s16 D_80180ED8[];
extern s32 D_80180E18[];
extern s32 D_80180EC4[];
extern s16 D_80180EDA[];
extern u16 D_80180FBC[];
extern s32 D_80180FCC[];
extern s32 D_80180FE4[];
extern u8 D_80180FFC[];
extern u16 D_80181000[];
extern u8 D_801810F4[];
extern u16 D_801804F0[];
extern u16 D_80180508;
extern u8* D_80180644[];
extern u8 D_80180664[];
extern u8 D_8018066C[];
extern u16 D_80180674[];
extern u8 D_80180684[];
extern s16 D_801809EC[];
extern u8 D_80181010;
extern RoomHeader g_rooms[];
extern ObjectInit* g_pStObjLayout[];
extern ObjectInit** D_801803C8[];
extern PfnEntityUpdate PfnEntityUpdates[];

extern ObjectInit* D_801997D8;
extern ObjectInit* D_801997DC;
extern u8 D_801997E0;
extern s8 D_801997E4;

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018D8C8);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018DC28);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018DF0C);
#else
void func_8018DF0C(s32 arg0, s32 arg1) {
    s32 temp_a3;
    s32 phi_v1;
    s16 phi_a2;
    s32 phi_a3;
    s16* phi_t0;
    s32 phi_a3_2;
    s16* phi_a2_2;
    s32 phi_v1_2;
    s32 phi_a3_3;
    s16* phi_a2_3;
    s32 phi_v1_3;
    s32 phi_a3_4;
    s16* phi_a2_4;
    s32 phi_v1_4;
    s32 phi_a3_5;
    s16* phi_a1;
    s32 phi_v1_5;

    for (phi_a3 = 0; phi_a3 < 0x10; phi_a3++) {
        phi_t0 = arg0;
        phi_v1_2 = 0;

        for (phi_v1 = 0; phi_v1 < 0x20; phi_v1++) {
            phi_a2 = -(((phi_a3 - 2) < 0xCU) ^ 1) & 3;
            if (phi_v1 - 2 >= 0x1C) {
                phi_a2 = 3;
            }

            *((phi_a3 << 5) + phi_t0) = phi_a2;
            phi_t0++;
        }
    }

    if (arg1 & 4) {
        for (phi_a3_2 = 6; phi_a3_2 < 0xA; phi_a3_2++) {
            phi_a2_2 = arg0;
        loop_9:
            *((phi_a3_2 << 5) + phi_a2_2) = 0;
            phi_a2_2++;
            phi_v1_2++;
            if (phi_v1_2 < 2) {
                goto loop_9;
            }
        }
    }

    if (arg1 & 8) {
        for (phi_a3_3 = 6; phi_a3_3 < 0xA; phi_a3_3++) {
            phi_a2_3 = arg0 + 0x3C;
            phi_v1_3 = 0x1E;
        loop_14:
            *((phi_a3_3 << 5) + phi_a2_3) = 0;
            phi_a2_3++;
            phi_v1_3++;
            if (phi_v1_3 < 0x20) {
                goto loop_14;
            }
        }
    }

    if (arg1 & 1) {
        for (phi_a3_4 = 0; phi_a3_4 < 2; phi_a3_4++) {
            phi_a2_4 = arg0 + 0xC;
            phi_v1_4 = 6;
        loop_19:
            *((phi_a3_4 << 6) + ((((arg1 & 8) == 0) << 5) + phi_a2_4)) = 0;
            phi_a2_4++;
            phi_v1_4++;
            if (phi_v1_4 < 0xA) {
                goto loop_19;
            }
        }
    }

    if (arg1 & 2) {
        for (phi_a3_5 = 0xE; phi_a3_5 < 0x10; phi_a3_5++) {
            phi_a1 = arg0 + 0xC;
            phi_v1_5 = 6;
        loop_24:
            *((phi_a3_5 << 6) + ((((arg1 & 8) == 0) << 5) + phi_a1)) = 0;
            phi_a1++;
            phi_v1_5++;
            if (phi_v1_5 < 0xA) {
                goto loop_24;
            }
        }
    }
}
#endif

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018E090);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018E13C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018E1D4);

void func_8018E5AC(Entity* arg0) {
    s32 temp_v0;
    ObjInit2* temp_s0 = &D_8018056C[arg0->subId];

    if (arg0->initState == 0) {
        InitializeEntity(D_80180544);
        arg0->animationSet = temp_s0->animationSet;
        arg0->zPriority = temp_s0->zPriority;
        arg0->unk5A = temp_s0->unk4.data;
        arg0->palette = temp_s0->palette;
        arg0->unk19 = temp_s0->unk8;
        arg0->unk18 = temp_s0->unkA;
        temp_v0 = temp_s0->unkC;
        if (temp_v0 != 0) {
            arg0->unk34 = temp_v0;
        }
    }
    AnimateEntity(temp_s0->unk10, arg0);
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018E674);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", EntityCandle);
#else
void EntityCandle(Entity* entity) {
    u16 temp_s0 = entity->subId >> 0xC;
    if (entity->initState) {
        AnimateEntity(D_80180644[temp_s0], entity);
        if (entity->unk44) { // If the candle is destroyed
            Entity* entityDropItem;
            D_8003C6D8(0x635);
            entityDropItem =
                AllocEntity(D_8007D308, D_8007D308 + MaxEntityCount);
            if (entityDropItem != NULL) {
                SpawnExplosionEntity(EntityExplosionID, entityDropItem);
                entityDropItem->subId = D_8018066C[temp_s0];
            }
            ReplaceCandleWithDrop(entity);
        }
    } else {
        InitializeEntity(D_801804F0);
        entity->zPriority = D_80096EB8 - 0x14;
        entity->unk18 = D_80180684[temp_s0];
        entity->hitboxHeight = D_80180664[temp_s0];
        entity->animationSet = D_80180674[temp_s0];
    }
}
#endif

s32 Random(void) {
    D_80097364 = (D_80097364 * 0x01010101) + 1;
    return D_80097364 >> 0x18;
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", UpdateStageEntities);
#else
extern s16 D_801806B4[];
extern u16 D_80199E54[];

void UpdateStageEntities(void) {
    s16 i;
    Entity* entity;
    s32* unk;

    for (i = 0; i < 0x20; i++) {
        if (D_80199E54[i]) {
            D_80199E54[i]--;
        }
    }

    unk = &D_80096EC0;
    if (*unk) {
        if (!--*unk) {
            D_8003C6B0(D_80096EC4);
        }
    }

    for (entity = D_80075D88; entity < &D_8007EA88; entity++) {
        if (!entity->pfnUpdate)
            continue;

        if (entity->initState) {
            s32 unk34 = entity->unk34;
            if (unk34 < 0) {
                u16 posX = entity->posX.Data.high;
                u16 posY = entity->posY.Data.high;
                if (unk34 & 0x40000000) {
                    if ((u16)(posY + 64) > 352 || (u16)(posX + 64) > 384) {
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
                s16 posY = entity->posY.Data.high + D_80072B42;
                s16 test = (D_80072B58 * 256) + 128;
                if (posY > test) {
                    DestroyEntity(entity);
                    continue;
                }
            }

            if (unk34 & 0xF) {
                entity->palette =
                    D_801806B4[(entity->unk49 << 1) | (unk34 & 1)];
                entity->unk34--;
                if ((entity->unk34 & 0xF) == 0) {
                    entity->palette = entity->unk6A;
                    entity->unk6A = 0;
                }
            }

            if (!(unk34 & 0x20000000) || (unk34 & 0x10000000) ||
                ((u16)(entity->posX.Data.high + 64) <= 384) &&
                    ((u16)(entity->posY.Data.high + 64) <= 352)) {
                if (!entity->unk58 || (entity->unk58--, unk34 & 0x100000)) {
                    if (!D_80096EAC || unk34 & 0x2100 ||
                        (unk34 & 0x200 && !(g_pfnLoadObjLayout & 3))) {
                        D_8006C26C = entity;
                        entity->pfnUpdate(entity);
                        entity->unk44 = 0;
                        entity->unk48 = 0;
                    }
                }
            }
        } else {
            D_8006C26C = entity;
            entity->pfnUpdate(entity);
            entity->unk44 = 0;
            entity->unk48 = 0;
        }
    }
}
#endif

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018EC90);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018EDB8);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018FEA0);

void CreateEntity(Entity* entity, ObjectInit* initDesc) {
    DestroyEntity(entity);
    entity->objectId = initDesc->flags & 0x3FF;
    do { //! FAKE https://decomp.me/scratch/zysYC
        entity->pfnUpdate = PfnEntityUpdates[entity->objectId];
    } while (0);
    entity->posX.Data.high = initDesc->posX - D_80072B3E;
    entity->posY.Data.high = initDesc->posY - D_80072B42;
    entity->subId = initDesc->unk8;
    entity->unk32 = initDesc->unk6 >> 8;
    entity->unk68 = initDesc->flags >> 0xA & 7;
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190608);
#else
void func_80190608(ObjectInit* initDesc) {
    s16 temp_a2;
    s16 temp_v1_2;
    s16 phi_a0;
    Entity* entity;

    temp_a2 = D_80072B42 + 0x120;
    phi_a0 = D_80072B42 - 0x40;
    if (phi_a0 < 0) {
        phi_a0 = 0;
    }

    temp_v1_2 = initDesc->posY;
    if (temp_v1_2 >= phi_a0 && temp_a2 >= temp_v1_2 &&
        (initDesc->flags & 0xE000) != 0x8000) {
        switch (initDesc->flags & 0xE000) {
        case 0x0:
            entity = &D_80075D88[*(u8*)&initDesc->unk6];
            if (entity->objectId != 0) {
                break;
            }
            CreateEntity(entity, initDesc);
            break;
        case 0xA000:
            CreateEntity(&D_80075D88[initDesc->unk6], initDesc);
            break;
        }
    }
}
#endif

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190720);

void func_80190838(s32 arg0) {
    s32 a1 = 0xFFFE;
    arg0 = (s16)arg0;
loop_1:
    if (D_801997D8->posX == a1 || D_801997D8->posX < arg0) {
        D_801997D8++;
        goto loop_1;
    }
}

void func_80190884(s32 arg0) {
    s32 a2, a3;
    a3 = 0xFFFF;
    arg0 = (s16)arg0;
    a2 = 0xFFFE;
loop_1:
    if ((D_801997D8->posX == a3) ||
        ((arg0 < D_801997D8->posX) && (D_801997D8->posX != a2))) {
        D_801997D8--;
        goto loop_1;
    }
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801908DC);
#else
void func_801908DC(s16 arg0) {
    u32 temp_a0, temp_v1_2;
    if (D_801997E0 != 0) {
        func_80190838((s16)(arg0 - D_800973B4));
        D_801997E0 = 0;
    }

    while (true) {
        if (D_801997D8->posX == 0xFFFF || arg0 < D_801997D8->posX)
            break;

        temp_a0 = ((u32)D_801997D8->unk6 >> 8) + 0xFF;
        temp_v1_2 = temp_a0 & 0xFF;
        if (temp_v1_2 == 0xFF ||
            (((1 << (temp_a0 & 0x1F)) & D_80096ED8[temp_v1_2 >> 5]) == 0)) {
            func_80190608(D_801997D8);
        }
        D_801997D8++;
    }
}
#endif

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801909D8);

void func_80190AD8(s32 arg0) {
    s32 a1 = 0xFFFE;
    arg0 = (s16)arg0;
loop_1:
    if (D_801997DC->posY == a1 || D_801997DC->posY < arg0) {
        D_801997DC++;
        goto loop_1;
    }
}

void func_80190B24(s16 arg0) {
    while (true) {
        if (D_801997DC->posY == 0xFFFF)
            D_801997DC--;
        else if (arg0 >= (s32)D_801997DC->posY || D_801997DC->posY == 0xFFFE)
            break;
        else
            D_801997DC--;
    }
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190B7C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190C78);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", LoadObjLayout);
#else
void LoadObjLayout(s32 objLayoutId) {
    s16 temp_s0;
    u16* pObjLayoutStart;
    ObjectInit* temp_v1;
    ObjectInit* temp_v0_2;
    s32 phi_a0;
    s16 phi_a1;
    s16 phi_a1_2;
    Unkstruct4* s1;

    pObjLayoutStart = g_pStObjLayout[objLayoutId];
    D_801997D8 = pObjLayoutStart;
    D_801997DC = D_801803C8[objLayoutId];
    s1 = &D_80072B34;
    if (*pObjLayoutStart != 0xFFFE) {
        D_801997D8 = pObjLayoutStart + 1;
        phi_a0 = Random() & 0xFF;

        for (phi_a1 = 0;; phi_a1++) {
            s32 temp_v0 = phi_a0 - D_801997D8->posX;
            D_801997D8 = (u16*)D_801997D8 + 1;
            phi_a0 = temp_v0;
            if (temp_v0 << 0x10 < 0)
                break;

            D_801997D8 = (u32*)D_801997D8 + 1;
        }

        D_801997D8 = (temp_v1->flags << 0x10) + temp_v1->posY;
        temp_v0_2 = (u32*)D_801997DC + (phi_a1 + 1);
        D_801997DC = temp_v0_2;
        D_801997DC = (temp_v0_2->posY << 0x10) + temp_v0_2->posX;
    }

    temp_s0 = s1->unkA + 0x140;
    phi_a1_2 = s1->unkA - 0x40;
    if (phi_a1_2 < 0) {
        phi_a1_2 = 0;
    }

    D_801997E0 = 0;
    D_801997E4 = 0;
    func_80190838(phi_a1_2);
    func_801908DC(temp_s0);
    func_80190AD8((s16)(s1->unkE + 0x120));
}
#endif

void func_80190F04(void) {
    Unkstruct4* s0 = &D_80072B34;
    s32 temp_v0_2;

    if (D_800973B4 != 0) {
        s16 temp_a0 = D_80072B3E;
        if (D_800973B4 > 0)
            func_801908DC(temp_a0 + 0x140);
        else
            func_801909D8(temp_a0 - 0x40);
    }

    temp_v0_2 = D_800973B8[0].tag;
    if (temp_v0_2 != 0) {
        s16 temp_a0_2 = s0->unkE;
        if (temp_v0_2 > 0)
            func_80190B7C(temp_a0_2 + 0x120);
        else
            func_80190C78(temp_a0_2 - 0x40);
    }
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", SpawnExplosionEntity);
#else
void SpawnExplosionEntity(u16 objectId, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.Data.high = D_8006C26C->posX.Data.high;
    entity->posY.Data.high = D_8006C26C->posY.Data.high;
}
#endif

// at -> v0 reg swap
#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019102C);
#else
void func_8019102C(u16 objectId, Entity* ent1, Entity* ent2) {
    DestroyEntity(ent2);
    ent2->objectId = objectId;
    ent2->pfnUpdate = PfnEntityUpdates[objectId];
    ent2->posX.Data.high = (s16)ent1->posX.Data.high;
    ent2->posY.Data.high = (s16)ent1->posY.Data.high;
}
#endif

s32 func_801910A8(Unkstruct5* arg0) {
    s16 var_v0_2;

    var_v0_2 = D_80072E8A - arg0->unk2;
    var_v0_2 = ABS_ALT(var_v0_2);

    if (var_v0_2 >= 0x11) {
        var_v0_2 = 0;
    } else {
        var_v0_2 = D_80072E8E - arg0->unk6;
        var_v0_2 = ABS_ALT(var_v0_2);
        var_v0_2 = var_v0_2 < 0x21;
    }

    return var_v0_2;
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80191120);

void DestroyEntity(Entity* item) {
    s32 i;
    s32 length;
    u32* ptr;

    if (item->unk34 & 0x800000) {
        D_8003C6B0(item->firstPolygonIndex);
    }

    ptr = (u32*)item;
    length = sizeof(Entity) / sizeof(s32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

void DestroyEntityFromIndex(s16 index) {
    Entity* entity = &D_80072E88[index];

    while (entity < &D_8007E9CC) {
        DestroyEntity(entity);
        entity++;
    }
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80191E24);
void func_80191E24(Entity* entity);
#else
void func_80191E24(Entity* entity) {
    if (entity->unk32 != 0) {
        u32 temp_a0_2 = entity->unk32 - 1;
        s32* temp_v1 = &D_80096ED8[(temp_a0_2 >> 5) & 0xFFFF];
        *temp_v1 |= 1 << (temp_a0_2 & 0x1F);
    }
}
#endif

#include "st/AnimateEntity.h"

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80191F24);

s32 func_8019203C(void) {
    s16 value = D_8006C26C->posX.Data.high - D_80072E8A;

    if (value < 0) {
        value = -value;
    }
    return value;
}

s32 func_80192078(void) {
    s32 value = D_8006C26C->posY.Data.high - D_80072E8E;

    if (value < 0) {
        value = -value;
    }
    return value;
}

s16 func_801920AC(void) {
    s16 var_a0 = D_8006C26C->posX.Data.high > D_80072E8A;

    if (D_8006C26C->posY.Data.high > D_80072E8E) {
        var_a0 |= 2;
    }
    return var_a0;
}

void MoveEntity(void) {
    D_8006C26C->posX.value += D_8006C26C->accelerationX;
    D_8006C26C->posY.value += D_8006C26C->accelerationY;
}

void FallEntity(void) {
    if (D_8006C26C->accelerationY < FALL_TERMINAL_VELOCITY) {
        D_8006C26C->accelerationY += FALL_GRAVITY;
    }
}

u8 func_8019214C(void) {
    u8 unkState;
    Entity* entity;

    MoveEntity();
    FallEntity();

    entity = D_8006C26C;

    if (unkState & 1) {
        entity->accelerationY = 0;
    }

    return unkState;
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192190);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192408);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192618);

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

s32 func_80192860(u8 arg0, s16 arg1) { return D_801809EC[arg0 & 0xFF] * arg1; }

s16 func_8019288C(u8 arg0) { return D_801809EC[arg0]; }

void func_801928A8(s32 arg0, s16 arg1) {
    D_8006C26C->accelerationX = func_80192860(arg0, arg1);
    D_8006C26C->accelerationY = func_80192860(arg0 - 0x40, arg1);
}

u8 func_80192914(s16 x, s16 y) { return ((ratan2(y, x) >> 4) + 0x40); }

u8 func_8019294C(Entity* a, Entity* b) {
    s32 diffX = (u16)b->posX.Data.high - (u16)a->posX.Data.high;
    s32 diffY = (u16)b->posY.Data.high - (u16)a->posY.Data.high;
    return func_80192914(diffX, diffY);
}

u8 func_80192994(s32 x, s32 y) {
    s32 diffX = x - (u16)D_8006C26C->posX.Data.high;
    s32 diffY = y - (u16)D_8006C26C->posY.Data.high;
    return func_80192914(diffX, diffY);
}

u8 func_801929DC(u8 arg0, u8 arg1, u8 arg2) {
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

void func_80192A34(u16 slope, s16 speed) {
    Entity* entity;
    s32 moveX;
    s32 moveY;

    moveX = rcos(slope) * speed;
    entity = D_8006C26C;

    if (moveX < 0) {
        moveX += 15;
    }

    entity->accelerationX = moveX >> 4;

    moveY = rsin(slope) * speed;
    entity = D_8006C26C;

    if (moveY < 0) {
        moveY += 15;
    }

    entity->accelerationY = moveY >> 4;
}

u16 func_80192AC0(s16 x, s16 y) { return ratan2(y, x); }

u16 func_80192AF0(Entity* a, Entity* b) {
    s32 diffX = b->posX.Data.high - a->posX.Data.high;
    s32 diffY = b->posY.Data.high - a->posY.Data.high;
    return ratan2(diffY, diffX);
}

u16 func_80192B28(s32 x, s32 y) {
    s16 diffX = x - (u16)D_8006C26C->posX.Data.high;
    s16 diffY = y - (u16)D_8006C26C->posY.Data.high;
    return ratan2(diffY, diffX);
}

u16 func_80192B70(u16 arg0, u16 arg1, u16 arg2) {
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

void func_80192BD0(s32 arg0) {
    D_8006C26C->initState = (s16)(arg0 & 0xFF);
    D_8006C26C->unk2E = 0;
    D_8006C26C->animationFrameIndex = 0;
    D_8006C26C->animationFrameDuration = 0;
}

void func_80192BF0(s32 arg0) {
    D_8006C26C->unk2E = (s16)(arg0 & 0xFF);
    D_8006C26C->animationFrameIndex = 0;
    D_8006C26C->animationFrameDuration = 0;
}

void func_80192C0C(u16 arg0, u16 arg1) {
    Entity* entity;

    if (arg1 != 0) {
        D_8003C6D8(arg1);
    }
    if (arg0 == 0xFF) {
        DestroyEntity(D_8006C26C);
        return;
    }

    entity = D_8006C26C;
    entity->unk19 = 0;
    entity->objectId = EntityExplosionID;
    entity->pfnUpdate = (PfnEntityUpdate)func_80194218;
    entity->subId = arg0;
    entity->animationFrame = 0;
    D_8006C26C->initState = 0;
    D_8006C26C->unk2E = 0;
}

void InitializeEntity(u16* arg0) {
    u16 temp_v1;
    Unkstruct5* temp_v0;

    D_8006C26C->animationSet = *arg0++;
    D_8006C26C->animationFrame = *arg0++;
    D_8006C26C->unk5A = *arg0++;
    D_8006C26C->palette = *arg0++;
    temp_v1 = *arg0++;
    D_8006C26C->unk3A = temp_v1;
    temp_v0 = (Unkstruct5*)(temp_v1 * sizeof(Unkstruct5) + (u32)D_8003C704);
    D_8006C26C->unk3E = temp_v0->unk4;
    D_8006C26C->unk40 = temp_v0->unk6;
    D_8006C26C->unk42 = temp_v0->unk8;
    D_8006C26C->unk3C = temp_v0->unkC;
    D_8006C26C->hitboxWidth = temp_v0->hitboxWidth;
    D_8006C26C->hitboxHeight = temp_v0->hitboxHeight;
    D_8006C26C->unk34 = temp_v0->unk24;
    D_8006C26C->unk10 = 0;
    D_8006C26C->unk12 = 0;
    D_8006C26C->unk2E = 0;
    D_8006C26C->initState++;
    if (D_8006C26C->zPriority == 0) {
        D_8006C26C->zPriority = D_80096EB8 - 0xC;
    }
}

void func_80192DA8(Entity* arg0) {
    if (arg0->initState == 0) {
        arg0->initState++;
    }
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192DD0);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192EF8);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80193050);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", ReplaceCandleWithDrop);
#else
void ReplaceCandleWithDrop(Entity* entity) {
    u16 prevSubId;
    u16 subId;
    u16 newSubId;

    func_80191E24(entity);
    if (!(D_8009741A & 2)) {
        DestroyEntity(entity);
        return;
    }

    prevSubId = entity->subId;
    subId = prevSubId & 0xFFF;
    entity->subId = subId;
    if (prevSubId < 0x80) {
        entity->objectId = EntityCandleDropID;
        entity->pfnUpdate = EntityCandleDrop;
        entity->animationFrameDuration = 0;
        entity->animationFrameIndex = 0;
        newSubId = subId;
    } else {
        entity->objectId = EntityCandleHeartDropID;
        entity->pfnUpdate = EntityCandleHeartDrop;
        newSubId = subId - 0x80;
    }
    entity->subId = newSubId;
    entity->unk6D = 0x10;
    entity->initState = 0;
}

#endif

// This function matches with PSYQ4.0 GCC 2.7.2 with -02 Optimization flag
#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019344C);
#else
void func_8019344C(void) {
    s32 temp_v1;
    Entity* entity = D_8006C26C;

    if (entity->accelerationY >= 0) {
        temp_v1 = entity->unk88 + entity->unk84.value;
        entity->unk84.value = temp_v1;
        entity->accelerationX = temp_v1;

        if ((temp_v1 == 0x10000) || (temp_v1 == -0x10000)) {
            entity->unk88 = -entity->unk88;
        }
        entity = D_8006C26C;
    }

    if (entity->accelerationY < 0x00004000) {
        entity->accelerationY += 0x2000;
    }
}
#endif

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801934D0);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019362C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801936E0);

void func_801937BC(void) {}

void func_801937C4(void) { DestroyEntity(D_8006C26C); }

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801937EC);

void CollectHeartVessel(void) {
    D_8003C6D8(0x670);
    D_8003C744(HEART_VESSEL_INCREASE, 0x4000);
    DestroyEntity(D_8006C26C);
}

void CollectLifeVessel(void) {
    D_8003C6D8(0x670);
    D_8003C744(LIFE_VESSEL_INCREASE, 0x8000);
    DestroyEntity(D_8006C26C);
}

void func_8019399C(void) { DestroyEntity(D_8006C26C); }

Entity* func_801939C4(void) {
    D_8006C26C->initState = 3;
    D_8006C26C->subId = 4;
    return D_8006C26C;
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", EntityCandleDrop);

// at -> a0 reg swap
#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80194218);
#else
void func_80194218(Entity* entity) {
    u32 temp_v0;

    if (entity->initState == 0) {
        InitializeEntity(&D_80180508);
        entity->animationSet = 2;
        entity->animationFrameIndex = 0;
        entity->animationFrameDuration = 0;
        entity->unk18 = 0x30;

        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->unk18 = 0x10;
        }

        temp_v0 = entity->subId & 0xFF00;
        if (temp_v0) {
            entity->zPriority = temp_v0 >> 8;
        }

        entity->subId = entity->subId & 0xF;
        entity->accelerationY = D_80180E18[entity->subId];
        return;
    }

    entity->posY.value += entity->accelerationY;
    if (!AnimateEntity(D_80180EC4[entity->subId], entity)) {
        DestroyEntity(entity);
    }
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80194314);
#else
void func_80194314(Entity* entity) {
    if (entity->initState != 0) {
        if (entity->posY.Data.high >= 0xF1) {
            DestroyEntity(entity);
            return;
        }
        FallEntity();
        MoveEntity();
        return;
    }

    InitializeEntity(&D_801804F0);
    entity->animationFrame = entity->unk7C.modeU8.unk0;
    entity->accelerationX = D_80180ED8[entity->unk80.data1.unk0 * 2];
    entity->accelerationY = D_80180EDA[entity->unk80.data1.unk0 * 2];

    if (entity->subId != 0) {
        entity->zPriority -= 1;
    }
}
#endif

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", EntityCandleHeartDrop);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801949C0);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80195520);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019563C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019572C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019583C);

// https://decomp.me/scratch/X3ho9
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019596C);

// at -> a1 reg swap
#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80195A54);
#else
void func_80195A54(Entity* entity) {
    if (entity->initState == 0) {
        entity->accelerationY = D_80180FE4[entity->unk94];
        entity->unk34 = 0x0C002000;
        entity->palette = 0x8195;
        entity->animationSet = 2;
        entity->animationFrame = D_80180FFC[entity->subId];
        entity->unk18 = 0x10;
        entity->initState++;
        return;
    }

    entity->animationFrameDuration++;
    entity->posY.value -= entity->accelerationY;

    if (!(entity->animationFrameDuration & 1)) {
        entity->animationFrame++;
    }

    if (D_80181000[entity->subId] < entity->animationFrameDuration) {
        DestroyEntity(entity);
    }
}
#endif

void func_80195B44(Entity* entity) {
    u16 temp_v0;

    if (entity->initState == 0) {
        entity->unk34 = 0x0C002000;
        entity->palette = 0x8195;
        entity->animationSet = 5;
        entity->animationFrame = 1;
        entity->unk18 = 0x10;
        entity->unk19 = 3;
        temp_v0 = D_80180FBC[entity->subId];
        entity->unk1A = temp_v0;
        entity->unk1C = temp_v0;
        entity->accelerationY = D_80180FCC[entity->subId];
        entity->initState++;
        return;
    }

    entity->animationFrameDuration++;
    entity->posY.value -= entity->accelerationY;

    if (!(entity->animationFrameDuration & 1)) {
        entity->animationFrame++;
    }

    if (entity->animationFrameDuration >= 37) {
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80195C38);

bool func_80195E68(Unkstruct6* unk) {
    Unkstruct7 a;

    FallEntity();
    D_8006C26C->posX.value += D_8006C26C->accelerationX;
    D_8006C26C->posY.value += D_8006C26C->accelerationY;

    if (D_8006C26C->accelerationY >= 0) {
        s16 posX = D_8006C26C->posX.Data.high;
        s16 posY = D_8006C26C->posY.Data.high;
        posX += unk->x;
        posY += unk->y;
        D_8003C6B8(posX, posY, &a, 0);
        if (a.sp10 & 1) {
            D_8006C26C->posY.Data.high += a.sp28;
            D_8006C26C->accelerationY = -D_8006C26C->accelerationY / 2;
            if (D_8006C26C->accelerationY > -0x10000) {
                return true;
            }
        }
    }
    return false;
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80195F64);

void func_801964E4(Entity* entity) {
    u32 temp_v0;

    if (entity->initState == 0) {
        InitializeEntity(&D_80180508);
        entity->palette = 0x8170;
        entity->animationSet = 5;
        entity->animationFrame = 1;
        entity->unk18 = 0x30;

        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->unk18 = 0x10;
        }

        temp_v0 = entity->subId & 0xFF00;

        if (temp_v0 != 0) {
            entity->zPriority = (u16)(temp_v0 >> 8);
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

void func_801965E4(Entity* entity) {
    if (entity->initState == 0) {
        InitializeEntity(&D_80180508);
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

    if (!AnimateEntity(&D_80181010, entity)) {
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801966B0);

// at -> v0 reg swap
#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019686C);
#else
void func_8019686C(u16 objectId, Entity* ent1, Entity* ent2) {
    DestroyEntity(ent2);
    ent2->objectId = objectId;
    ent2->pfnUpdate = PfnEntityUpdates[objectId];
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
#endif

void func_80196934(void) {
    Entity* entity;
    s16 temp_s3;
    s32 i;
    u8 temp_s4;

    temp_s4 = Random() & 3;
    temp_s3 = ((Random() & 0xF) << 8) - 0x800;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(D_8007D308, &D_8007D308[MaxEntityCount]);
        if (entity != NULL) {
            func_8019102C(2, D_8006C26C, entity);
            entity->unk84.Data1.unk1 = 6 - i;
            entity->unk80.data = temp_s3;
            entity->unk84.Data1.unk0 = temp_s4;
        }
    }
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801969EC);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80196BC4);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801971A4);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801978A4);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80197A9C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80197B94);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801982BC);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80198650);

void func_80198B00(Entity* entity) {
    s32 temp_v0;
    ObjInit2* temp_s0 = (ObjInit2*)&D_801810F4[entity->subId * 0x14];

    if (entity->initState == 0) {
        InitializeEntity(D_80180544);
        entity->animationSet = temp_s0->animationSet;
        entity->zPriority = temp_s0->zPriority;
        entity->unk5A = temp_s0->unk4.data;
        entity->palette = temp_s0->palette;
        entity->unk19 = temp_s0->unk8;
        entity->unk18 = temp_s0->unkA;
        temp_v0 = temp_s0->unkC;
        if (temp_v0 != 0) {
            entity->unk34 = temp_v0;
        }
    }
    AnimateEntity(temp_s0->unk10, entity);
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80198BC8);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80198FA0);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80199388);

POLY_GT4* func_801994D8(POLY_GT4* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = (POLY_GT4*)poly->tag;
        } else {
            return poly;
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80199508);

POLY_GT4* func_80199584(POLY_GT4* startPoly, s32 count) {
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

void func_8019960C(POLY_GT4* arg0) {
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

void func_801996EC(POLY_GT4* arg0) {
    func_8019960C(arg0);
    arg0->p3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 1;
    ((POLY_GT4*)arg0->tag)->code = 2;
    ((POLY_GT4*)arg0->tag)->pad3 = 0xA;
}

void func_80199740(POLY_GT4* arg0) {
    arg0->p3 = 0;
    arg0->pad3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 0;
    ((POLY_GT4*)arg0->tag)->code = 4;
    ((POLY_GT4*)arg0->tag)->pad3 = 8;
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019976C);
#else
s32 func_8019976C(s32 arg0, s32 value) {
    s32 temp_t0;
    u8* phi_v1;
    u8* phi_a0;
    int i;

    s32 phi_a2;
    s32 phi_a2_2;

    phi_v1 = arg0 + 4;
    phi_a2 = 0;
    for (i = 0, phi_a2_2 = 0; i < 4; i++) {
        phi_v1 = phi_a0;
    loop_2:
        *phi_v1 -= value;
        if ((u32)*phi_v1 >= 0xF9) {
            *phi_v1 = 0;
        } else {
            phi_a2 |= 1;
        }

        phi_v1++;
        if (phi_v1 < (phi_a0 + 3)) {
            goto loop_2;
        }

        phi_a0 += 0xC;
    }

    return phi_a2 & 0xFF;
}
#endif
