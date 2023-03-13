/*
 * File: D8C8.c
 * Overlay: MAD
 * Description: Debug Area. Unused ingame.
 */

// hack to make the code compile for this weird overlay
#define STAGE_MAD_FIX
#include "stage.h"

void func_801908DC(s16);
void func_801909D8(s16);
void func_80190B7C(s16);
void func_80190C78(s16);
void CreateEntityFromCurrentEntity(u16, Entity*);
u8 func_80192914(s16 arg0, s16 arg1);
void ReplaceBreakableWithItemDrop(Entity*);
void CreateEntityFromEntity(u16 objectId, Entity* ent1, Entity* ent2);
void func_80198BC8(void* const, s32);
void func_8019344C(void);

// OFFSET FIXED
extern u8 D_8003BEE8[];
extern s32 g_pfnInitRoomEntities; // It's 8003C8C4!
extern Entity* g_CurrentEntity;
extern Entity g_EntityArray[];
extern Entity D_8007D858[];
extern Entity D_8007EF1C;
extern s32 D_80097410;
extern s32 D_80097414;
extern u8 D_8009796E;
extern Entity D_800762D8[];
extern s32 D_800973FC;

// TODO FIX
extern s32 D_80097908;

// ST/MAD
extern u16 D_8018052C[];
extern u16 D_801806B4[];
extern u16 D_80180F5C[];
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
extern ObjInit2 D_801810F4[];
extern u16 D_80180508;
extern s16 D_801809EC[];
extern u8 D_80181010;
extern RoomHeader g_rooms[];
extern LayoutObject* g_pStObjLayout[];
extern LayoutObject** D_801803C8[];
extern PfnEntityUpdate PfnEntityUpdates[];

extern LayoutObject* D_801997D8;
extern LayoutObject* D_801997DC;
extern u8 D_801997E0;
extern s8 D_801997E4;
extern u16 D_80199E54[];

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8018D8C8);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8018DC28);

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8018DF0C);
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

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8018E090);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8018E13C);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8018E1D4);

void func_8018E5AC(Entity* self) {
    s32 temp_v0;
    ObjInit2* objInit = &D_8018056C[self->subId];

    if (self->step == 0) {
        InitializeEntity(D_80180544);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->unk5A = objInit->unk4.s;
        self->palette = objInit->palette;
        self->unk19 = objInit->unk8;
        self->blendMode = objInit->blendMode;
        temp_v0 = objInit->unkC;
        if (temp_v0 != 0) {
            self->flags = temp_v0;
        }
    }
    AnimateEntity(objInit->unk10, self);
}

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8018E674);

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
            g_api.PlaySfx(0x635);
            entityDropItem =
                AllocEntity(D_8007D858, D_8007D858 + MaxEntityCount);
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

s32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

void Update(void) {
    s16 i;
    Entity* entity;
    s32* unk;

    for (i = 0; i < 0x20; i++) {
        if (D_80199E54[i]) {
            D_80199E54[i]--;
        }
    }

    unk = &D_80097410;
    if (*unk) {
        if (!--*unk) {
            g_api.FreePolygons(D_80097414);
        }
    }

    for (entity = D_800762D8; entity < &D_8007EFD8; entity++) {
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
                    D_801806B4[(entity->unk49 << 1) | (unk34 & 1)];
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

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8018EC90);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8018EDB8);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", EntityNumericDamage);

void CreateEntityFromLayout(Entity* entity, LayoutObject* initDesc) {
    DestroyEntity(entity);
    entity->objectId = initDesc->objectId & 0x3FF;
    do { //! FAKE https://decomp.me/scratch/zysYC
        entity->pfnUpdate = PfnEntityUpdates[entity->objectId];
    } while (0);
    entity->posX.i.hi = initDesc->posX - g_Camera.posX.i.hi;
    entity->posY.i.hi = initDesc->posY - g_Camera.posY.i.hi;
    entity->subId = initDesc->subId;
    entity->objectRoomIndex = initDesc->objectRoomIndex >> 8;
    entity->unk68 = initDesc->objectId >> 0xA & 7;
}

/**
 * Note: This function got too old to even compile
 * rework is needed to get it in compiling state
 */
#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80190608);
#else
void func_80190608(LayoutObject* initDesc) {
    s16 temp_a2;
    s16 temp_v1_2;
    s16 phi_a0;
    Entity* entity;

    temp_a2 = g_Camera.posY.i.hi + 0x120;
    phi_a0 = g_Camera.posY.i.hi - 0x40;
    if (phi_a0 < 0) {
        phi_a0 = 0;
    }

    temp_v1_2 = initDesc->posY;
    if (temp_v1_2 >= phi_a0 && temp_a2 >= temp_v1_2 &&
        (initDesc->objectId & 0xE000) != 0x8000) {
        switch (initDesc->objectId & 0xE000) {
        case 0x0:
            entity = &D_800762D8[*(u8*)&->objectRoomIndex];
            if (entity->objectId != 0) {
                break;
            }
            CreateEntityFromLayout(entity, initDesc);
            break;
        case 0xA000:
            CreateEntityFromLayout(&D_800762D8[->objectRoomIndex], initDesc);
            break;
        }
    }
}
#endif

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80190720);

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
INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_801908DC);
#else
void func_801908DC(s16 arg0) {
    u32 temp_a0, temp_v1_2;
    if (D_801997E0 != 0) {
        func_80190838((s16)(arg0 - D_80097908));
        D_801997E0 = 0;
    }

    while (true) {
        if (D_801997D8->posX == 0xFFFF || arg0 < D_801997D8->posX)
            break;

        temp_a0 = ((u32)D_801997D8->unk6 >> 8) + 0xFF;
        temp_v1_2 = temp_a0 & 0xFF;
        if (temp_v1_2 == 0xFF || (((1 << (temp_a0 & 0x1F)) &
                                   g_entityDestroyed[temp_v1_2 >> 5]) == 0)) {
            func_80190608(D_801997D8);
        }
        D_801997D8++;
    }
}
#endif

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_801909D8);

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

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80190B7C);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80190C78);

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", InitRoomEntities);
#else
void InitRoomEntities(s32 objLayoutId) {
    s16 temp_s0;
    u16* pObjLayoutStart;
    LayoutObject* temp_v1;
    LayoutObject* temp_v0_2;
    s32 phi_a0;
    s16 phi_a1;
    s16 phi_a1_2;
    Unkstruct4* s1;

    pObjLayoutStart = g_pStObjLayout[objLayoutId];
    D_801997D8 = pObjLayoutStart;
    D_801997DC = D_801803C8[objLayoutId];
    s1 = &g_CurrentRoomTileLayout;
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

        D_801997D8 = (temp_v1->objectId << 0x10) + temp_v1->posY;
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
    Unkstruct8* currentRoomTileLayout = &g_CurrentRoomTileLayout;

    if (D_80097908 != 0) {
        s16 tmp = g_Camera.posX.i.hi;
        if (D_80097908 > 0)
            func_801908DC(tmp + 0x140);
        else
            func_801909D8(tmp - 0x40);
    }

    if (D_8009790C != 0) {
        s16 tmp = currentRoomTileLayout->unkE;
        if (D_8009790C > 0)
            func_80190B7C(tmp + 0x120);
        else
            func_80190C78(tmp - 0x40);
    }
}

void CreateEntityFromCurrentEntity(u16 objectId, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.i.hi = g_CurrentEntity->posX.i.hi;
    entity->posY.i.hi = g_CurrentEntity->posY.i.hi;
}

void CreateEntityFromEntity(u16 objectId, Entity* ent1, Entity* ent2) {
    DestroyEntity(ent2);
    ent2->objectId = objectId;
    ent2->pfnUpdate = PfnEntityUpdates[objectId];
    ent2->posX.i.hi = (s16)ent1->posX.i.hi;
    ent2->posY.i.hi = (s16)ent1->posY.i.hi;
}

s32 func_801910A8(Entity* e) {
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

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", EntityRedDoor);

void DestroyEntity(Entity* item) {
    s32 i;
    s32 length;
    u32* ptr;

    if (item->flags & FLAG_FREE_POLYGONS) {
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
    if (entity->objectRoomIndex != 0) {
        u32 value = (entity->objectRoomIndex - 1);
        u16 index = value / 32;
        u16 bit = value % 32;
        g_entityDestroyed[index] |= 1 << bit;
    }
}

#include "st/AnimateEntity.h"

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80191F24);

s32 func_8019203C(void) {
    s16 value = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (value < 0) {
        value = -value;
    }
    return value;
}

s32 func_80192078(void) {
    s32 value = g_CurrentEntity->posY.i.hi - PLAYER.posY.i.hi;

    if (value < 0) {
        value = -value;
    }
    return value;
}

s16 func_801920AC(void) {
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

u8 func_8019214C(void) {
    u8 unkState;
    Entity* entity;

    MoveEntity();
    FallEntity();

    entity = g_CurrentEntity;

    if (unkState & 1) {
        entity->accelerationY = 0;
    }

    return unkState;
}

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80192190);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80192408);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80192618);

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
    g_CurrentEntity->accelerationX = func_80192860(arg0, arg1);
    g_CurrentEntity->accelerationY = func_80192860(arg0 - 0x40, arg1);
}

u8 func_80192914(s16 x, s16 y) { return ((ratan2(y, x) >> 4) + 0x40); }

u8 func_8019294C(Entity* a, Entity* b) {
    s32 diffX = (u16)b->posX.i.hi - (u16)a->posX.i.hi;
    s32 diffY = (u16)b->posY.i.hi - (u16)a->posY.i.hi;
    return func_80192914(diffX, diffY);
}

u8 func_80192994(s32 x, s32 y) {
    s32 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s32 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
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

u16 func_80192AC0(s16 x, s16 y) { return ratan2(y, x); }

u16 func_80192AF0(Entity* a, Entity* b) {
    s32 diffX = b->posX.i.hi - a->posX.i.hi;
    s32 diffY = b->posY.i.hi - a->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_80192B28(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s16 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
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
    g_CurrentEntity->step = (s16)(arg0 & 0xFF);
    g_CurrentEntity->unk2E = 0;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

void func_80192BF0(s32 arg0) {
    g_CurrentEntity->unk2E = (s16)(arg0 & 0xFF);
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

void func_80192C0C(u16 arg0, u16 arg1) {
    Entity* entity;

    if (arg1 != 0) {
        g_api.PlaySfx(arg1);
    }
    if (arg0 == 0xFF) {
        DestroyEntity(g_CurrentEntity);
        return;
    }

    entity = g_CurrentEntity;
    entity->unk19 = 0;
    entity->objectId = ENTITY_EXPLOSION;
    entity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
    entity->subId = arg0;
    entity->animCurFrame = 0;
    g_CurrentEntity->step = 0;
    g_CurrentEntity->unk2E = 0;
}

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

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80192DD0);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80192EF8);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80193050);

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
    entity->unk6D = 0x10;
    temp_a0 = 0;
    entity->step = temp_a0;
}

// This function matches with PSYQ4.0 GCC 2.7.2 with -02 Optimization flag
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8019344C);
#else
void func_8019344C(void) {
    s32 temp_v1;
    Entity* entity = g_CurrentEntity;

    if (entity->accelerationY >= 0) {
        temp_v1 = entity->unk88 + entity->unk84.value;
        entity->unk84.value = temp_v1;
        entity->accelerationX = temp_v1;

        if ((temp_v1 == 0x10000) || (temp_v1 == -0x10000)) {
            entity->unk88 = -entity->unk88;
        }
        entity = g_CurrentEntity;
    }

    if (entity->accelerationY < 0x00004000) {
        entity->accelerationY += 0x2000;
    }
}
#endif

void func_801934D0(u16 arg0) {
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
            return;
        }

        g_CurrentEntity->posY.i.hi =
            (u16)g_CurrentEntity->posY.i.hi + LOH(res.unk18);
        return;
    }

    if (!(res.unk0 & 5)) {
        MoveEntity();
        func_8019344C();
    }
}

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8019362C);

extern s32 g_playerGold; // g_playerGold?
void* const D_80180D60[];
const s32 D_80180D88[]; // c_GoldPrizes

void func_801936E0(u16 goldSize) { // CollectGold
    s32 *gold, *unk;
    u16 goldSizeIndex;

    g_api.PlaySfx(0x69D);
    gold = &g_playerGold;
    goldSizeIndex = goldSize - 2;
    *gold += D_80180D88[goldSizeIndex];
    if (*gold > MAX_GOLD) {
        *gold = MAX_GOLD;
    }

    unk = &D_80097410;
    if (*unk) {
        g_api.FreePolygons(D_80097414); // g_api.FreePolygons
        *unk = 0;
    }

    func_80198BC8(D_80180D60[goldSizeIndex], 1);
    DestroyEntity(g_CurrentEntity);
}

void func_801937BC(void) {}

void func_801937C4(void) { DestroyEntity(g_CurrentEntity); }

// https://decomp.me/scratch/GsS0m
INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_801937EC);

void CollectHeartVessel(void) {
    g_api.PlaySfx(0x670);
    g_api.func_800FE044(HEART_VESSEL_INCREASE, 0x4000);
    DestroyEntity(g_CurrentEntity);
}

void CollectLifeVessel(void) {
    g_api.PlaySfx(0x670);
    g_api.func_800FE044(LIFE_VESSEL_INCREASE, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

void DestroyCurrentEntity(void) { DestroyEntity(g_CurrentEntity); }

Entity* func_801939C4(void) {
    g_CurrentEntity->step = 3;
    g_CurrentEntity->subId = 4;
    return g_CurrentEntity;
}

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", EntityPriceDrop);

void EntityExplosion(Entity* entity) {
    u32 temp_v0;

    if (entity->step == 0) {
        InitializeEntity(&D_80180508);
        entity->animSet = 2;
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
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
        entity->accelerationY = D_80180E18[entity->subId];
        return;
    }

    entity->posY.val += entity->accelerationY;
    if (!AnimateEntity((const u8*)D_80180EC4[entity->subId], entity)) {
        DestroyEntity(entity);
    }
}

void func_80194314(Entity* entity) {
    if (entity->step != 0) {
        if (entity->posY.i.hi >= 0xF1) {
            DestroyEntity(entity);
            return;
        }
        FallEntity();
        MoveEntity();
        return;
    }

    InitializeEntity(g_eBreakableInit);
    entity->animCurFrame = entity->unk7C.U8.unk0;
    entity->accelerationX = D_80180ED8[entity->unk80.modeS8.unk0 * 2];
    entity->accelerationY = D_80180EDA[entity->unk80.modeS8.unk0 * 2];

    if (entity->subId != 0) {
        entity->zPriority -= 1;
    }
}

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", EntityInventoryDrop);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", EntityRelicOrb);

// v1 -> a0 reg swap
// branching
// signature conflict
// https://decomp.me/scratch/h3CVU
#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", EntityHeartDrop);
#else
void EntityHeartDrop(Entity* entity, u32 arg1) {
    u16 temp_v0_2;
    u16 temp_v1;
    u16 var_v1;
    u32 temp_a0;

    if (entity->step == 0) {
        temp_v0_2 = entity->subId;
        temp_a0 = temp_v0_2 & 0xFFFF;
        var_v1 = temp_v0_2;
        entity->unkB4 = var_v1;

        if ((D_8003BEE8[temp_a0 >> 3] >> (var_v1 & 7)) & 1) {
            DestroyEntity(entity);
            return;
        }

        var_v1 = D_80180F5C[temp_a0];

        if (var_v1 < 0x80) {
            entity->unkB8.unkFuncB8 = EntityPriceDrop;
        } else {
            entity->unkB8.unkFuncB8 = EntityInventoryDrop;
            var_v1 -= 0x80;
        }

        entity->subId = var_v1 + 0x8000;
        return;
    }

    temp_v1 = entity->unkB4;

    if (entity->step < 5) {
        arg1 = temp_v1 / 8;
        if (entity->unk48 != 0) {
            D_8003BEE8[arg1] |= (1 << (temp_v1 & 7));
            entity->step = 5;
        }
    }
    entity->unkB8.unkFuncB8(entity, arg1, entity);
}
#endif

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8019563C);

void func_8019572C(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_8018052C);
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

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8019583C);

// https://decomp.me/scratch/3IMus
INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8019596C);

void func_80195A54(Entity* entity) {
    if (entity->step == 0) {
        entity->accelerationY = D_80180FE4[entity->unk94];
        entity->flags = 0x2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = 2;
        entity->animCurFrame = D_80180FFC[entity->subId];
        entity->blendMode = 0x10;
        entity->step++;
        return;
    }

    entity->animFrameDuration++;
    entity->posY.val -= entity->accelerationY;

    if (!(entity->animFrameDuration & 1)) {
        entity->animCurFrame++;
    }

    if (D_80181000[entity->subId] < (s32)entity->animFrameDuration) {
        DestroyEntity(entity);
    }
}

void func_80195B44(Entity* entity) {
    u16 temp_v0;

    if (entity->step == 0) {
        entity->flags = 0x2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = 5;
        entity->animCurFrame = 1;
        entity->blendMode = 0x10;
        entity->unk19 = 3;
        temp_v0 = D_80180FBC[entity->subId];
        entity->unk1A = temp_v0;
        entity->unk1C = temp_v0;
        entity->accelerationY = D_80180FCC[entity->subId];
        entity->step++;
        return;
    }

    entity->animFrameDuration++;
    entity->posY.val -= entity->accelerationY;

    if (!(entity->animFrameDuration & 1)) {
        entity->animCurFrame++;
    }

    if (entity->animFrameDuration >= 37) {
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80195C38);

bool func_80195E68(Unkstruct6* unk) {
    Collider res;

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
            g_CurrentEntity->posY.i.hi += LOH(res.unk18);
            g_CurrentEntity->accelerationY =
                -g_CurrentEntity->accelerationY / 2;
            if (g_CurrentEntity->accelerationY > -0x10000) {
                return true;
            }
        }
    }
    return false;
}

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80195F64);

void EntityIntenseExplosion(Entity* entity) {
    u32 zPriority;

    if (entity->step == 0) {
        InitializeEntity(&D_80180508);
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
        return;
    } else {
        entity->animFrameDuration++;
        entity->posY.val -= 0x4000;

        if (!(entity->animFrameDuration & 1)) {
            entity->animCurFrame++;
        }

        if (entity->animFrameDuration >= 0x25) {
            DestroyEntity(entity);
        }
    }
}

void func_801965E4(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(&D_80180508);
        entity->unk6C = 0xF0;
        entity->unk1A = 0x1A0;
        entity->unk1C = 0x1A0;
        entity->animSet = 8;
        entity->animCurFrame = 1;
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

    if (!AnimateEntity(&D_80181010, entity)) {
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_801966B0);

void func_8019686C(u16 objectId, Entity* src, Entity* dst) {
    DestroyEntity(dst);
    dst->objectId = objectId;
    dst->pfnUpdate = PfnEntityUpdates[objectId];
    dst->posX.i.hi = src->posX.i.hi;
    dst->posY.i.hi = src->posY.i.hi;
    dst->unk5A = src->unk5A;
    dst->zPriority = src->zPriority;
    dst->animSet = src->animSet;
    dst->flags = 0x45002000 | FLAG_UNK_08000000 | FLAG_DESTROY_IF_OUT_OF_CAMERA;

    if (src->palette & 0x8000) {
        dst->palette = src->unk6A;
    } else {
        dst->palette = (s16)src->palette;
    }
}

// https://decomp.me/scratch/fA367 TODO: 0x80 entity member unconfirmed
void func_80196934(void) {
    Entity* entity;
    s16 temp_s3;
    s32 i;
    u8 temp_s4;

    temp_s4 = Random() & 3;
    temp_s3 = ((Random() & 0xF) << 8) - 0x800;

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

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_801969EC);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80196BC4);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_801971A4);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_801978A4);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80197A9C);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80197B94);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", EntityAbsorbOrb);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", EntityEnemyBlood);

void EntityRoomForeground(Entity* entity) {
    ObjInit2* obj = &D_801810F4[entity->subId];

    if (entity->step == 0) {
        InitializeEntity(D_80180544);
        entity->animSet = obj->animSet;
        entity->zPriority = obj->zPriority;
        entity->unk5A = obj->unk4.s;
        entity->palette = obj->palette;
        entity->unk19 = obj->unk8;
        entity->blendMode = obj->blendMode;
        if (obj->unkC != 0) {
            entity->flags = obj->unkC;
        }
    }
    AnimateEntity(obj->unk10, entity);
}

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80198BC8);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80198FA0);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80199388);

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

INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_80199508);

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

s32 func_8019976C(Unkstruct_80128BBC* arg0, u8 value) {
    u8 ret = 0;
    s32 i;
    s32 j;
    Unkstruct_80128BBC_Sub* temp = arg0->unk04;

    for (i = 0; i < 4; i++, temp++) {
        for (j = 0; j < 3; j++) {
            temp->unk00[j] -= value;

            if (temp->unk00[j] > 248) {
                temp->unk00[j] = 0;
            } else {
                ret |= 1;
            }
        }
    }
    return ret;
}
