#include "stage.h"

extern RoomHeader* g_stRooms[];
extern ObjectInit* g_pStObjLayout[];
extern u8* D_80180310;
extern PfnEntityUpdate PfnEntityUpdates[];
extern u16 D_80180440[];
extern u16 D_80180458[];
extern u16 D_80180494[];
extern ObjInit2 D_801804E0[];
extern u8* D_801805B8[];
extern u8 D_801805D8[];
extern u8 D_801805E0[];
extern u16 D_801805E8[];
extern u8 D_801805F8[];
extern u16 D_80180690[];
extern s16 D_80180A94[];
extern s32 D_80180E08[];
extern s32 c_GoldPrizes[];
extern s8 c_HeartPrizes[];
extern s32 D_80180EC4[];
extern u8* D_80180F70[];
extern u16 D_80180FF8[];
extern s32 D_80181008[];
extern s32 D_80181020[];
extern u8 D_80181038[];
extern u16 D_8018103C[];
extern u8 D_8018104C[];
extern ObjInit2 D_80181134[];

extern ObjectInit* D_80193AB0;
extern ObjectInit* D_80193AB4;
extern s8 D_80193AB8;
extern s8 D_80193ABC;

void SpawnExplosionEntity(u16, Entity*);
void ReplaceCandleWithDrop(Entity*);
void EntityCandleDrop(Entity*);
void EntityCandleHeartDrop(Entity*);
void func_8018D894(Entity*);
void func_801916C4(s32);
void func_80192F40(s32, s32);

void func_80186FD0(Entity* arg0) {
    ObjInit2* objInit = &D_801804E0[arg0->subId];
    if (arg0->initState == 0) {
        InitializeEntity(D_80180494);
        arg0->animationSet = objInit->animationSet;
        arg0->zPriority = objInit->zPriority;
        arg0->unk5A = objInit->unk4.data;
        arg0->palette = objInit->palette;
        arg0->unk19 = objInit->unk8;
        arg0->unk18 = objInit->unkA;

        if (objInit->unkC != 0) {
            arg0->unk34 = objInit->unkC;
        }

        if (arg0->subId == 1) {
            arg0->unk1C = 0x0200;
            arg0->unk1A = 0x0200;
        }
    }

    AnimateEntity(objInit->unk10, arg0);
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801870B0);
#else
s32 func_8018B970();
extern u16 D_80180488[];
extern u8 D_80180528[];
extern s8 D_80180530[];
extern s16 D_80180538[];

void func_801870B0(Entity* entity) {
    s32 temp_v0;
    s32 temp_v1;
    u16* temp_v0_2;
    u16 temp_s1;
    u16 phi_v1;
    u16 unk;

    temp_s1 = entity->subId;
    entity->unk6D = 0;
    if (entity->initState != 0) {
        temp_v1 = temp_s1;
        if (temp_v1 > 3) {
            if (temp_v1 > 5) {
                if (temp_v1 != 6) {
                test_2:
                    if (g_CurrentRoomX)
                        return;
                } else {
                    if (g_pads->pressed & PAD_TRIANGLE) {
                        g_CurrentRoomX = 0;
                        g_CurrentRoomWidth = 1280;
                        entity->initState++;
                        return;
                    }
                }
            } else {
                goto test_2;
            }
        }

        if (entity->unk44 != 0) {
            temp_v0 = func_8018B970();
            if (entity->unk7C != 0) {
                phi_v1 = (temp_v0 & 2) * 2;
            } else {
                phi_v1 = (temp_v0 & 1) * 4;
            }

            unk = phi_v1 + temp_s1 * 8;
            temp_v0_2 = D_80180538 + unk;
            g_CurrentRoomX = (s32)*temp_v0_2++;
            g_CurrentRoomY = (s32)*temp_v0_2++;
            g_CurrentRoomWidth = (s32)*temp_v0_2++;
            g_CurrentRoomHeight = (s32)*temp_v0_2++;
        }
    } else {
        u8 temp_v0_5;
        InitializeEntity(D_80180488);
        temp_v0_5 = D_80180530[temp_s1];
        entity->unk7C = temp_v0_5;
        if (temp_v0_5 != 0) {
            entity->hitboxWidth = D_80180528[temp_s1];
            entity->hitboxHeight = 16;
        } else {
            entity->hitboxWidth = 16;
            entity->hitboxHeight = D_80180528[temp_s1];
        }
    }
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", EntityCandle);
#else
void EntityCandle(Entity* entity) {
    u16 temp_s0 = entity->subId >> 0xC;
    if (entity->initState) {
        AnimateEntity(D_801805B8[temp_s0], entity);
        if (entity->unk44) { // If the candle is destroyed
            Entity* entityDropItem;
            g_pfnPlaySfx(0x634);
            entityDropItem =
                AllocEntity(D_8007D858, D_8007D858 + MaxEntityCount);
            if (entityDropItem != NULL) {
                SpawnExplosionEntity(EntityExplosionID, entityDropItem);
                entityDropItem->subId = D_801805E0[temp_s0];
            }
            ReplaceCandleWithDrop(entity);
        }
    } else {
        InitializeEntity(D_80180440);
        entity->zPriority = D_80097408 - 0x14;
        entity->unk18 = D_801805F8[temp_s0];
        entity->hitboxHeight = D_801805D8[temp_s0];
        entity->animationSet = D_801805E8[temp_s0];
    }
}
#endif

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801873A0);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80187F1C);

s32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", UpdateStageEntities);
#else
extern u16 D_80194728[];

void UpdateStageEntities(void) {
    s16 i;
    Entity* entity;
    s32* unk;

    for (i = 0; i < 0x20; i++) {
        if (D_80194728[i]) {
            D_80194728[i]--;
        }
    }

    unk = &D_80097410;
    if (*unk) {
        if (!--*unk) {
            g_pfnFreePolygons(D_80097414);
        }
    }

    for (entity = D_800762D8; entity < &D_8007EFD8; entity++) {
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
                s16 posY = entity->posY.Data.high + D_80073092;
                s16 test = (g_CurrentRoomVSize * 256) + 128;
                if (posY > test) {
                    DestroyEntity(entity);
                    continue;
                }
            }

            if (unk34 & 0xF) {
                entity->palette =
                    D_80180690[(entity->unk49 << 1) | (unk34 & 1)];
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
                    if (!D_800973FC || unk34 & 0x2100 ||
                        (unk34 & 0x200 && !(D_8003C8C4 & 3))) {
                        D_8006C3B8 = entity;
                        entity->pfnUpdate(entity);
                        entity->unk44 = 0;
                        entity->unk48 = 0;
                    }
                }
            }
        } else {
            D_8006C3B8 = entity;
            entity->pfnUpdate(entity);
            entity->unk44 = 0;
            entity->unk48 = 0;
        }
    }
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80188514);
#else
void func_80188514(void) {
    Entity* entity;
    for (entity = D_800762D8; entity < &D_8007EFD8; entity++) {
        if (!entity->pfnUpdate)
            continue;

        if (entity->initState) {
            if (entity->unk34 & 0x10000) {
                if (entity->unk34 & 0xF) {
                    entity->palette =
                        D_80180690[entity->unk49 << 1 | entity->unk34 & 1];
                    entity->unk34--;
                    if ((entity->unk34 & 0xF) == 0) {
                        entity->palette = entity->unk6A;
                        entity->unk6A = 0;
                    }
                }
            } else
                continue;
        }

        D_8006C3B8 = entity;
        entity->pfnUpdate(entity);
        entity->unk44 = 0;
        entity->unk48 = 0;
    }
}

#endif

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018861C);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80189734);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", CreateEntity);
#else
void CreateEntity(Entity* entity, ObjectInit* initDesc) {
    DestroyEntity(entity);
    entity->objectId = initDesc->flags & 0x3FF;
    entity->pfnUpdate = PfnEntityUpdates[entity->objectId];
    entity->posX.Data.high = initDesc->posX - D_8007308E;
    entity->posY.Data.high = initDesc->posY - D_80073092;
    entity->subId = initDesc->unk8;
    entity->unk32 = initDesc->unk6 >> 8;
    entity->unk68 = initDesc->flags >> 0xA & 7;
}
#endif

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80189E9C);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80189FB4);

void func_8018A0CC(s32 arg0) {
    s32 a1 = 0xFFFE;
    arg0 = (s16)arg0;
loop_1:
    if (D_80193AB0->posX == a1 || D_80193AB0->posX < arg0) {
        D_80193AB0++;
        goto loop_1;
    }
}

void func_8018A118(s32 arg0) {
    s32 a2, a3;
    a3 = 0xFFFF;
    arg0 = (s16)arg0;
    a2 = 0xFFFE;
loop_1:
    if ((D_80193AB0->posX == a3) ||
        ((arg0 < D_80193AB0->posX) && (D_80193AB0->posX != a2))) {
        D_80193AB0--;
        goto loop_1;
    }
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018A170);
void func_8018A170(s16);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018A26C);
void func_8018A26C(s16);

void func_8018A380(s32 arg0) {
    s32 a1 = 0xFFFE;
    arg0 = (s16)arg0;
loop_1:
    if (D_80193AB4->posY == a1 || D_80193AB4->posY < arg0) {
        D_80193AB4++;
        goto loop_1;
    }
}

void func_8018A3CC(s16 arg0) {
    while (true) {
        if (D_80193AB4->posY == 0xFFFF)
            D_80193AB4--;
        else if (arg0 >= (s32)D_80193AB4->posY || D_80193AB4->posY == 0xFFFE)
            break;
        else
            D_80193AB4--;
    }
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018A424);
void func_8018A424(s16 arg0);
#else
void func_80189FB4(ObjectInit*);
extern s32 D_80097428[];
extern u8 D_80193ABC;

void func_8018A424(s16 arg0) {
    if (D_80193ABC) {
        func_8018A380((s16)(arg0 - D_8009790C));
        D_80193ABC = 0;
    }

    while (true) {
        if (D_80193AB4->posY != -1 && arg0 >= D_80193AB4->posY) {
            u8 flag = (D_80193AB4->unk6 >> 8) + 0xFF;
            if (flag == 0xFF ||
                (1 << (flag & 0x1F) & D_80097428[flag >> 5]) == 0) {
                func_80189FB4(D_80193AB4);
            }
            D_80193AB4++;
        } else
            break;
    }
}
#endif

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018A520);
void func_8018A520(s16);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", LoadObjLayout);
#else
void LoadObjLayout(s32 objLayoutId) {
    s16 temp_s0;
    s16 var_a1_2;
    u16 temp_v1_2;
    u16* pObjLayoutStart;
    Unkstruct8* layout;

    pObjLayoutStart = g_pStObjLayout[objLayoutId];
    layout = &g_CurrentRoomTileLayout;
    D_80193AB0 = pObjLayoutStart;
    D_80193AB4 = *(&D_80180310 + objLayoutId);
    if (*pObjLayoutStart != 0xFFFE) {
        s32 var_a0;
        s16 var_a1;
        u16* temp_v1;

        D_80193AB0 = pObjLayoutStart + 1;
        var_a0 = Random() & 0xFF;

        for (var_a1 = 0;; var_a1++) {
            s32 temp_v0;
            temp_v1 = D_80193AB0;
            D_80193AB0 = (u16*)D_80193AB0 + 1;
            temp_v0 = var_a0 - temp_v1[0];
            var_a0 = temp_v0;
            if ((s16)temp_v0 < 0)
                break;
            D_80193AB0 = temp_v1 + 3;
        }

        D_80193AB0 = (temp_v1[2] << 0x10) + temp_v1[1];
        D_80193AB4 = (var_a1 * 2) + 2 + (u16*)D_80193AB4;
        D_80193AB4 = (((u16*)D_80193AB4)[1] << 0x10) + ((u16*)D_80193AB4)[0];
    }

    var_a1_2 = (s16)layout->unkA - 0x40;
    temp_s0 = layout->unkA + 0x140;
    if (var_a1_2 < 0) {
        var_a1_2 = 0;
    }
    D_80193AB8 = 0;
    D_80193ABC = 0;
    func_8018A0CC(var_a1_2);
    func_8018A170(temp_s0);
    func_8018A380((s16)(layout->unkE + 0x120));
}
#endif

void func_8018A7AC(void) {
    Unkstruct8* s0 = &g_CurrentRoomTileLayout;

    if (D_80097908) {
        s16 tmp = D_8007308E;
        if (D_80097908 > 0)
            func_8018A170(tmp + 0x140);
        else
            func_8018A26C(tmp - 0x40);
    }

    if (D_8009790C) {
        s16 tmp = s0->unkE;
        if (D_8009790C > 0)
            func_8018A424(s0->unkE + 0x120);
        else
            func_8018A520(tmp - 0x40);
    }
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", SpawnExplosionEntity);
#else
void SpawnExplosionEntity(u16 objectId, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.Data.high = D_8006C3B8->posX.Data.high;
    entity->posY.Data.high = D_8006C3B8->posY.Data.high;
}
#endif

#ifndef NON_MATCHING
void func_8018A8D4(u16 objectId, Entity* source, Entity* entity);
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018A8D4);
#else
void func_8018A8D4(u16 objectId, Entity* source, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.Data.high = source->posX.Data.high;
    entity->posY.Data.high = source->posY.Data.high;
}
#endif

s32 func_8018A950(Unkstruct5* arg0) {
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

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018A9C8);

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

void func_8018B6E8(Entity* entity) {
    if (entity->unk32) {
        u32 bit = entity->unk32 - 1;
        u16 index = bit >> 5;
        D_80097428[index] |= 1 << (bit & 0x1F);
    }
}

#include "st/AnimateEntity.h"

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018B7E8);

s16 func_8018B900(void) {
    s16 value = D_8006C3B8->posX.Data.high - D_800733DA;
    if (value < 0) {
        value = -value;
    }
    return value;
}

s32 func_8018B93C(void) {
    s32 value = D_8006C3B8->posY.Data.high - D_800733DE;
    if (value < 0) {
        value = -value;
    }
    return value;
}

s16 func_8018B970(void) {
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

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018BA10);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018BC88);

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

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018BED0);
s32 func_8018BED0(u8 arg0, s16 arg1);
#else
s32 func_8018BED0(u8 arg0, s16 arg1) { return D_80180A94[arg0 & 0xFF] * arg1; }
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018BEFC);
#else
s16 func_8018BEFC(s32 arg0) { return D_80180A94[arg0 & 0xFF]; }
#endif

void func_8018BF18(s32 arg0, s16 arg1) {
    D_8006C3B8->accelerationX = func_8018BED0(arg0, arg1);
    D_8006C3B8->accelerationY = func_8018BED0(arg0 - 0x40, arg1);
}

u8 func_8018BF84(s16 x, s16 y) { return ((ratan2(y, x) >> 4) + 0x40); }

u8 func_8018BFBC(Entity* a, Entity* b) {
    s32 diffX = (u16)b->posX.Data.high - (u16)a->posX.Data.high;
    s32 diffY = (u16)b->posY.Data.high - (u16)a->posY.Data.high;
    return func_8018BF84(diffX, diffY);
}

u8 func_8018C004(s32 x, s32 y) {
    s32 diffX = x - (u16)D_8006C3B8->posX.Data.high;
    s32 diffY = y - (u16)D_8006C3B8->posY.Data.high;
    return func_8018BF84(diffX, diffY);
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018C04C);

void func_8018C0A4(u16 slope, s16 speed) {
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

u16 func_8018C130(s16 x, s16 y) { return ratan2(y, x); }

u16 func_8018C160(Entity* a, Entity* b) {
    s32 diffX = b->posX.Data.high - a->posX.Data.high;
    s32 diffY = b->posY.Data.high - a->posY.Data.high;
    return ratan2(diffY, diffX);
}

u16 func_8018C198(s32 x, s32 y) {
    s16 diffX = x - (u16)D_8006C3B8->posX.Data.high;
    s16 diffY = y - (u16)D_8006C3B8->posY.Data.high;
    return ratan2(diffY, diffX);
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018C1E0);

void func_8018C240(s32 arg0) {
    D_8006C3B8->initState = (s16)(arg0 & 0xFF);
    D_8006C3B8->unk2E = 0;
    D_8006C3B8->animationFrameIndex = 0;
    D_8006C3B8->animationFrameDuration = 0;
}

void func_8018C260(s32 arg0) {
    D_8006C3B8->unk2E = (s16)(arg0 & 0xFF);
    D_8006C3B8->animationFrameIndex = 0;
    D_8006C3B8->animationFrameDuration = 0;
}

void func_8018C27C(u16 arg0, u16 arg1) {
    Entity* entity;

    if (arg1 != 0) {
        func_801916C4(arg1);
    }
    if (arg0 == 0xFF) {
        DestroyEntity(D_8006C3B8);
        return;
    }

    entity = D_8006C3B8;
    entity->unk19 = 0;
    entity->objectId = EntityExplosionID;
    entity->pfnUpdate = (PfnEntityUpdate)func_8018D894;
    entity->subId = arg0;
    entity->animationFrame = 0;
    D_8006C3B8->initState = 0;
    D_8006C3B8->unk2E = 0;
}

void InitializeEntity(u16* arg0) {
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
        D_8006C3B8->zPriority = D_80097408 - 0xC;
    }
}

void func_8018C40C(Entity* arg0) {
    if (arg0->initState == 0) {
        arg0->initState++;
    }
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018C434);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018C55C);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018C6B4);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", ReplaceCandleWithDrop);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018CAB0);
#else
void func_8018CAB0(void) {
    s32 temp_v1;
    Entity* entity;

    entity = D_8006C3B8;
    if (entity->accelerationY >= 0) {
        temp_v1 = entity->unk88 + entity->unk84.value;
        entity->unk84.value = temp_v1;
        entity->accelerationX = temp_v1;
        if (temp_v1 == 0x10000 || temp_v1 == -0x10000) {
            entity->unk88 = -entity->unk88;
        }
        entity = D_8006C3B8;
    }

    if (entity->accelerationY < 0x00004000) {
        entity->accelerationY += 0x2000;
    }
}
#endif

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018CB34);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", CollectHeart);
#else
void CollectHeart(u16 heartSize) {
    s32* hearts;

    g_pfnPlaySfx(0x67A);
    hearts = &g_playerHeart;
    *hearts += c_HeartPrizes[heartSize];

    if (g_playerHeartMax < *hearts) {
        *hearts = g_playerHeartMax;
    }
    
    DestroyEntity(D_8006C3B8);
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", CollectGold);
#else
void CollectGold(u16 goldSize) {
    s32 *gold, *unk;
    u16 goldSizeIndex;

    gold = &g_playerGold;
    g_pfnPlaySfx(0x6A9);
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

    func_80192F40(D_80180E08[goldSizeIndex], 1);
    DestroyEntity(D_8006C3B8);
}
#endif

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018CDEC);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", CollectHeartVessel);
#else
void CollectHeartVessel(void) {
    if (g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
        g_pfnPlaySfx(0x67A);
        g_playerHeart += HEART_VESSEL_RICHTER;
        if (g_playerHeartMax < g_playerHeart) {
            g_playerHeart = g_playerHeartMax;
        }
    } else {
        g_pfnPlaySfx(0x67A);
        D_8003C848(HEART_VESSEL_INCREASE, 0x4000);
    }
    DestroyEntity(D_8006C3B8);
}
#endif

void CollectLifeVessel(void) {
    g_pfnPlaySfx(0x67A);
    D_8003C848(LIFE_VESSEL_INCREASE, 0x8000);
    DestroyEntity(D_8006C3B8);
}

void func_8018CFF8(void) { DestroyEntity(D_8006C3B8); }

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", EntityCandleDrop);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018D894);
#else
void func_8018D894(Entity* entity) {
    u16 zPriority;

    if (entity->initState == 0) {
        InitializeEntity(D_80180458);
        entity->animationSet = 2;
        entity->animationFrameIndex = 0;
        entity->animationFrameDuration = 0;
        entity->unk18 = 0x30;
        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->unk18 = 0x10;
        }

        zPriority = entity->subId & 0xFF00;
        if (zPriority) {
            entity->zPriority = zPriority >> 8;
        }
        entity->subId &= 15;
        entity->accelerationY = D_80180EC4[entity->subId];
    } else {
        entity->posY.value += entity->accelerationY;
        if (!AnimateEntity(D_80180F70[entity->subId], entity)) {
            DestroyEntity(entity);
        }
    }
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018D990);
#else
void func_8018D990(Entity* arg0, s32 renderFlags) {
    POLY_GT4* poly;
    s16 left, top, right, bottom;
    u8 colorIntensity;

    poly = &D_80086FEC[arg0->firstPolygonIndex];

    left = arg0->posX.Data.high - 7;
    right = arg0->posX.Data.high + 7;
    poly->x2 = left;
    poly->x0 = left;
    poly->x3 = right;
    poly->x1 = right;

    top = arg0->posY.Data.high - 7;
    bottom = arg0->posY.Data.high + 7;
    poly->y1 = top;
    poly->y0 = top;
    poly->y3 = bottom;
    poly->y2 = bottom;

    colorIntensity = renderFlags & RENDERFLAGS_NOSHADOW ? 255 : 128;
    poly->b3 = colorIntensity;
    poly->b2 = colorIntensity;
    poly->b1 = colorIntensity;
    poly->b0 = colorIntensity;
    poly->g3 = colorIntensity;
    poly->g2 = colorIntensity;
    poly->g1 = colorIntensity;
    poly->g0 = colorIntensity;
    poly->r3 = colorIntensity;
    poly->r2 = colorIntensity;
    poly->r1 = colorIntensity;
    poly->r0 = colorIntensity;
}
#endif

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018DA34);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018E01C);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018E2CC);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018ED9C);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018EEC4);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018F420);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018F510);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018F620);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018F750);
#else
extern void func_8018F928(Entity*);
void func_8018F750(Entity* source, s8 count, s16 xOffset, s16 yOffset,
                   s16 xDistance) {
    Entity* entity;
    s16 x, y;
    u8 i;

    y = source->posY.Data.high + yOffset;
    x = source->posX.Data.high + xOffset;
    for (i = 0; i < count; i++) {
        entity = AllocEntity(D_8007A958, D_8007A958 + MaxEntityCount);
        if (entity != NULL) {
            entity->objectId = 21;
            entity->pfnUpdate = func_8018F928;
            entity->posX.Data.high = x;
            entity->posY.Data.high = y;
            entity->subId = i;
            entity->zPriority = source->zPriority + 1;
        }
        i++;
        x += xDistance;
    }
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018F838);
#else
void func_8018F838(Entity* entity) {
    if (entity->initState == 0) {
        entity->palette = 0x8195;
        entity->animationSet = 2;
        entity->unk34 = 0x0C002000;
        entity->accelerationY = D_80181020[entity->unk94];
        entity->unk18 = 16;
        entity->initState = entity->initState + 1;
        entity->animationFrame = D_80181038[entity->subId];
    } else {
        entity->animationFrameDuration++;
        entity->posY.value = entity->posY.value - entity->accelerationY;
        if ((entity->animationFrameDuration & 1) == 0) {
            entity->animationFrame++;
        }
        if (D_8018103C[entity->subId] < entity->animationFrameDuration) {
            DestroyEntity(entity);
        }
    }
}
#endif

void func_8018F928(Entity* arg0) {
    u16 temp_v0;

    if (arg0->initState == 0) {
        arg0->unk34 = 0x0C002000;
        arg0->palette = 0x8195;
        arg0->animationSet = 5;
        arg0->animationFrame = 1U;
        arg0->unk18 = 0x10;
        arg0->unk19 = 3;
        temp_v0 = D_80180FF8[arg0->subId];
        arg0->unk1A = temp_v0;
        arg0->unk1C = temp_v0;
        arg0->accelerationY = D_80181008[arg0->subId];
        arg0->initState++;
    } else {
        arg0->animationFrameDuration++;
        arg0->posY.value -= arg0->accelerationY;
        if ((arg0->animationFrameDuration & 1) == 0) {
            arg0->animationFrame++;
        }
        if (arg0->animationFrameDuration >= 37) {
            DestroyEntity(arg0);
        }
    }
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018FA1C);

bool func_8018FC4C(Unkstruct6* unk) {
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

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018FD48);

void func_801902C8(Entity* entity) {
    u32 zPriority;

    if (entity->initState == 0) {
        InitializeEntity(D_80180458);
        entity->palette = 0x8170;
        entity->animationSet = 5;
        entity->animationFrame = 1;
        entity->unk18 = 0x30;
        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->unk18 = 0x10;
        }

        zPriority = entity->subId & 0xFF00;
        if (zPriority != 0) {
            entity->zPriority = zPriority >> 8;
        }
        entity->zPriority += 8;
    } else {
        entity->animationFrameDuration++;
        entity->posY.value -= 0x4000;

        if ((entity->animationFrameDuration & 1) == 0) {
            entity->animationFrame++;
        }

        if (entity->animationFrameDuration >= 37) {
            DestroyEntity(entity);
        }
    }
}

void func_801903C8(Entity* entity) {
    if (entity->initState == 0) {
        InitializeEntity(D_80180458);
        entity->unk6C = 0xF0;
        entity->unk1A = 0x01A0;
        entity->unk1C = 0x01A0;
        entity->animationSet = 8;
        entity->animationFrame = 1;
        entity->zPriority += 16;
        if (entity->subId) {
            entity->palette = entity->subId;
        } else {
            entity->palette = 0x8160;
        }

        entity->initState++;
    } else {
        MoveEntity();
        if (AnimateEntity(D_8018104C, entity) == 0) {
            DestroyEntity(entity);
        }
    }
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80190494);
#else
void func_80190494(u16 objectId, Entity* source, Entity* entity) {
    u16 palette;

    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.Data.high = source->posX.Data.high;
    entity->posY.Data.high = source->posY.Data.high;
    entity->unk5A = source->unk5A;
    entity->zPriority = source->zPriority;
    entity->animationSet = source->animationSet;
    entity->unk34 = 0xCD002000;

    palette = source->palette;
    entity->palette = palette & 0x8000 ? source->unk6A : palette;
}
#endif

void func_8019055C(void) {
    s32 temp_s3;
    s8 temp_s4;
    Entity* entity;
    s32 i;

    temp_s4 = Random() & 3;
    temp_s3 = ((Random() & 0xF) << 8) - 0x800;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(D_8007D858, D_8007D858 + MaxEntityCount);
        if (entity != NULL) {
            func_8018A8D4(EntityExplosionID, D_8006C3B8, entity);
            entity->unk84.Data1.unk1 = 6 - i;
            entity->unk80 = temp_s3;
            entity->unk84.Data1.unk0 = temp_s4;
        }
    }
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80190614);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801907EC);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80190DCC);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801914CC);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801916C4);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801917BC);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8019198C);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80192610);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801929A4);

void func_80192E54(Entity* arg0) {
    ObjInit2* objInit = &D_80181134[arg0->subId];
    if (arg0->initState == 0) {
        InitializeEntity(D_80180494);
        arg0->animationSet = objInit->animationSet;
        arg0->zPriority = objInit->zPriority;
        arg0->unk5A = objInit->unk4.data;
        arg0->palette = objInit->palette;
        arg0->unk19 = objInit->unk8;
        arg0->unk18 = objInit->unkA;

        if (objInit->unkC != 0) {
            arg0->unk34 = objInit->unkC;
        }

        if (arg0->subId >= 5) {
            arg0->unk1E = 0x0800;
            arg0->unk19 = arg0->unk19 | 4;
        }
    }

    AnimateEntity(objInit->unk10, arg0);
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80192F40);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80193270);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80193658);

POLY_GT4* func_801937A8(POLY_GT4* poly) {
    while (poly) {
        if (poly->p3 == 0)
            return poly;
        poly = (POLY_GT4*)poly->tag;
    }
    return NULL;
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801937D8);
#else
POLY_GT4* func_801937D8(POLY_GT4* poly, u8 index) {
    while (poly) {
        s32 i = 1;
        if (poly->p3 == 0) {
            if (index >= 1) {
                do {
                    poly = poly->tag;
                    if (poly == 0) {
                        return 0;
                    }
                } while (poly->p3 == 0 && ++i < index);
            }
            if (i == index) {
                return poly;
            }
        }
        poly = poly->tag;
    }
    return 0;
}
#endif

POLY_GT4* func_80193854(POLY_GT4* startPoly, s32 count) {
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

void func_801938DC(POLY_GT4* arg0) {
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

void func_801939BC(POLY_GT4* arg0) {
    func_801938DC(arg0);
    arg0->p3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 1;
    ((POLY_GT4*)arg0->tag)->code = 2;
    ((POLY_GT4*)arg0->tag)->pad3 = 0xA;
}

void func_80193A10(POLY_GT4* arg0) {
    arg0->p3 = 0;
    arg0->pad3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 0;
    ((POLY_GT4*)arg0->tag)->code = 4;
    ((POLY_GT4*)arg0->tag)->pad3 = 8;
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80193A3C);
#else
s32 func_80193A3C(u8* arg0, u8 arg1) {
    s32 temp_v0;
    u8 phi_v0;
    u8* phi_a0;
    s32 i;
    s32 phi_a2;

    phi_a2 = 0;
    phi_a0 = arg0 + 4;
    for (i = 0; i < 4; i++) {
        u8* phi_v1 = phi_a0;
        s32 end = phi_a0 + 3;
    loop_2:
        temp_v0 = *phi_v1 - arg1;
        phi_v0 = temp_v0;
        if (temp_v0 < 0) {
            phi_v0 = 0;
        } else {
            phi_a2 |= 1;
        }

        *phi_v1++ = phi_v0;
        if ((s32)phi_v1 < end) {
            goto loop_2;
        }

        phi_a0 += 0xC;
    }

    return phi_a2;
}
#endif