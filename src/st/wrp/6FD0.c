/*
 * File: 6FD0.c
 * Overlay: WRP
 * Description: All warp rooms.
 */

#include "stage.h"

void func_80188514(void);
void func_8018861C();
void func_8018A7AC();
void LoadObjLayout(s32 objLayoutId);
void SpawnExplosionEntity(u16, Entity*);
void ReplaceCandleWithDrop(Entity*);
void ReplaceBreakableWithItemDrop();
void EntityCandleDrop(Entity*);
void EntityCandleHeartDrop(Entity*);
void func_8018D894(Entity*);
void func_801916C4(s32);
void func_80192F40(s32, s32);

extern RoomHeader g_stRooms[];
extern PfnEntityUpdate PfnEntityUpdates[];
extern u16 D_80180458[];
extern u16 D_80180494[];
extern ObjInit2 D_801804E0[];
extern u16 D_80180690[];
extern s16 D_80180A94[];
extern void* D_80180E08[];
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

void func_80186FD0(Entity* arg0) {
    ObjInit2* objInit = &D_801804E0[arg0->subId];
    if (arg0->initState == 0) {
        InitializeEntity(D_80180494);
        arg0->animationSet = objInit->animationSet;
        arg0->zPriority = objInit->zPriority;
        arg0->unk5A = objInit->unk4.data;
        arg0->palette = objInit->palette;
        arg0->unk19 = objInit->unk8;
        arg0->blendMode = objInit->blendMode;

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
void func_801870B0(Entity* entity);
#else
extern u16 D_80180488[];
u8 D_80180528[];
s8 D_80180530[];
s16 D_80180538[];

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
            if (entity->unk7C.modeU16 != 0) {
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
        entity->unk7C.modeU16 = temp_v0_5;
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

u16 g_eBreakableInit[];
u8* g_eBreakableAnimations[];
u8 g_eBreakableHitboxes[];
u8 g_eBreakableExplosionTypes[];
u16 g_eBreakableAnimationSets[];
u8 g_eBreakableBlendModes[];
void EntityBreakable(Entity* entity) {
    u16 breakableType = entity->subId >> 0xC;
    if (entity->initState) {
        AnimateEntity(g_eBreakableAnimations[breakableType], entity);
        if (entity->unk44) { // If the candle is destroyed
            Entity* entityDropItem;
            g_pfnPlaySfx(0x634);
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
        entity->zPriority = g_zEntityCenter - 0x14;
        entity->blendMode = g_eBreakableBlendModes[breakableType];
        entity->hitboxHeight = g_eBreakableHitboxes[breakableType];
        entity->animationSet = g_eBreakableAnimationSets[breakableType];
    }
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801873A0);
void func_801873A0(Entity*);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80187F1C);
void func_80187F1C(Entity*);

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
void func_80189734(Entity*);

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
    entity->objectRoomIndex = initDesc->unk6 >> 8;
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
extern s32 g_entityDestroyed[];
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
                (1 << (flag & 0x1F) & g_entityDestroyed[flag >> 5]) == 0) {
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
    Unkstruct8* currentRoomTileLayout = &g_CurrentRoomTileLayout;

    if (D_80097908 != 0) {
        s16 tmp = D_8007308E;
        if (D_80097908 > 0)
            func_8018A170(tmp + 0x140);
        else
            func_8018A26C(tmp - 0x40);
    }

    if (D_8009790C != 0) {
        s16 tmp = currentRoomTileLayout->unkE;
        if (D_8009790C > 0)
            func_8018A424(currentRoomTileLayout->unkE + 0x120);
        else
            func_8018A520(tmp - 0x40);
    }
}

void SpawnExplosionEntity(u16 objectId, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.Data.high = D_8006C3B8->posX.Data.high;
    entity->posY.Data.high = D_8006C3B8->posY.Data.high;
}

void func_8018A8D4(u16 objectId, Entity* source, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.Data.high = source->posX.Data.high;
    entity->posY.Data.high = source->posY.Data.high;
}

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
void func_8018A9C8(Entity*);

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

s32 func_8018BED0(u8 arg0, s16 arg1) { return D_80180A94[arg0 & 0xFF] * arg1; }

s16 func_8018BEFC(s32 arg0) { return D_80180A94[arg0 & 0xFF]; }

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
    entity->objectId = ENTITY_EXPLOSION;
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
        D_8006C3B8->zPriority = g_zEntityCenter - 0xC;
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
        entity->pfnUpdate = EntityCandleDrop;
        entity->animationFrameDuration = 0;
        entity->animationFrameIndex = 0;
    } else {
        var_v1 = temp_a0 - 0x80;
        entity->objectId = ENTITY_HEART_DROP;
        entity->pfnUpdate = EntityCandleHeartDrop;
    }

    entity->subId = var_v1;
    temp_a0 = 0;
    entity->unk6D = 0x10;
    entity->initState = temp_a0;
}

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

void CollectHeart(u16 heartSize) {
    s32* hearts;

    g_pfnPlaySfx(0x67A);
    hearts = &g_playerHeart;
    *hearts += c_HeartPrizes[heartSize];

    if (g_playerHeart->max < *hearts) {
        *hearts = g_playerHeart->max;
    }

    DestroyEntity(D_8006C3B8);
}

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

void CollectHeartVessel(void) {
    if (g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
        g_pfnPlaySfx(0x67A);
        g_playerHeart->current += HEART_VESSEL_RICHTER;

        if (g_playerHeart->max < g_playerHeart->current) {
            g_playerHeart->current = g_playerHeart->max;
        }
    } else {
        g_pfnPlaySfx(0x67A);
        D_8003C848(HEART_VESSEL_INCREASE, 0x4000);
    }
    DestroyEntity(D_8006C3B8);
}

void CollectLifeVessel(void) {
    g_pfnPlaySfx(0x67A);
    D_8003C848(LIFE_VESSEL_INCREASE, 0x8000);
    DestroyEntity(D_8006C3B8);
}

void func_8018CFF8(void) { DestroyEntity(D_8006C3B8); }

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", EntityCandleDrop);

void func_8018D894(Entity* entity) {
    u16 zPriority;

    if (entity->initState == 0) {
        InitializeEntity(D_80180458);
        entity->animationSet = 2;
        entity->animationFrameIndex = 0;
        entity->animationFrameDuration = 0;
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
        entity->accelerationY = D_80180EC4[entity->subId];
    } else {
        entity->posY.value += entity->accelerationY;
        if (!AnimateEntity(D_80180F70[entity->subId], entity)) {
            DestroyEntity(entity);
        }
    }
}

void func_8018D990(Entity* arg0, s32 renderFlags) {
    POLY_GT4* poly;
    s16 left, top, right, bottom;

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

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", EntityCandleHeartDrop);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018E01C);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018E2CC);
void func_8018E2CC(Entity*);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018ED9C);
void func_8018ED9C(Entity*);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018EEC4);
void func_8018EEC4(Entity*);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018F420);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018F510);
void func_8018F510(Entity*);

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
void func_8018F838(Entity* entity);
#else
void func_8018F838(Entity* entity) {
    if (entity->initState == 0) {
        entity->palette = 0x8195;
        entity->animationSet = 2;
        entity->unk34 = 0x0C002000;
        entity->accelerationY = D_80181020[entity->unk94];
        entity->blendMode = 16;
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
        arg0->blendMode = 0x10;
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
            func_8018A8D4(ENTITY_EXPLOSION, D_8006C3B8, entity);
            entity->unk84.Data1.unk1 = 6 - i;
            entity->unk80.data = temp_s3;
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
void func_8019198C(Entity*);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80192610);
void func_80192610(Entity*);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801929A4);
void func_801929A4(Entity*);

void EntityRoomForeground(Entity* entity) {
    ObjInit2* objInit = &D_80181134[entity->subId];
    if (entity->initState == 0) {
        InitializeEntity(D_80180494);
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

PfnOverlayEntry g_pStOverlay[] = {
    /* 0x00 */ (PfnOverlayEntry)UpdateStageEntities,
    /* 0x04 */ (PfnOverlayEntry)func_8018861C,
    /* 0x08 */ (PfnOverlayEntry)func_8018A7AC,
};
PfnLoadObjectLayout g_pfnStLoadObjectLayout =
    (PfnLoadObjectLayout)LoadObjLayout;

void* g_pStUnkRoomDef[] = {
    /* 0x10 */ (void*)g_stRooms,
    /* 0x14 */ (void*)0x80180040,
    /* 0x18 */ (void*)0x801800B4,
};
void* g_pStUnkObjLayouts = NULL;
void* g_pStUnkTilesLayout = (void*)0x80180168;

void* g_pStTilesets[] = {
    /* 0x024 */ (void*)0x801801EC,
    /* 0x028 */ (void*)func_80188514,
    /* 0x02C */ (void*)0x00000000,
    /* 0x030 */ (void*)0x00000000,
    /* 0x034 */ (void*)0x00000000,
    /* 0x038 */ (void*)0x00000000,
    /* 0x03C */ (void*)0x00000000,
    /* 0x040 */ (void*)0x00000000,
    /* 0x044 */ (void*)0x80186D88,
    /* 0x048 */ (void*)0x00000000,
    /* 0x04C */ (void*)0x00000000,
    /* 0x050 */ (void*)0x00000000,
    /* 0x054 */ (void*)0x00000000,
    /* 0x058 */ (void*)0x00000000,
    /* 0x05C */ (void*)0x00000000,
    /* 0x060 */ (void*)0x00000000,
    /* 0x064 */ (void*)0x00000000,
    /* 0x068 */ (void*)0x00000000,
    /* 0x06C */ (void*)0x00000000,
    /* 0x070 */ (void*)0x00000000,
    /* 0x074 */ (void*)0x00000000,
    /* 0x078 */ (void*)0x00000000,
    /* 0x07C */ (void*)0x00000000,
    /* 0x080 */ (void*)0x00000000,
    /* 0x084 */ (void*)0x00000000,
    /* 0x088 */ (void*)0x00000000,
    /* 0x08C */ (void*)0x00000000,
    /* 0x090 */ (void*)0x00000000,
    /* 0x094 */ (void*)0x00000000,
    /* 0x098 */ (void*)0x00000000,
    /* 0x09C */ (void*)0x00000000,
    /* 0x0A0 */ (void*)0x00000005,
    /* 0x0A4 */ (void*)0x00002000,
    /* 0x0A8 */ (void*)0x00000010,
    /* 0x0AC */ (void*)0x80181D08,
    /* 0x0B0 */ (void*)0xFFFFFFFF,
    /* 0x0B4 */ (void*)0x801800A0,
    /* 0x0B8 */ (void*)0x00000000,
    /* 0x0BC */ (void*)0x00000000,
    /* 0x0C0 */ (void*)0x00000000,
    /* 0x0C4 */ (void*)0x00000000,
    /* 0x0C8 */ (void*)0x80181D68,
    /* 0x0CC */ (void*)0x80186D78,
    /* 0x0D0 */ (void*)0x01328328,
    /* 0x0D4 */ (void*)0x00030060,
    /* 0x0D8 */ (void*)0x80181F68,
    /* 0x0DC */ (void*)0x80186D78,
    /* 0x0E0 */ (void*)0x01565565,
    /* 0x0E4 */ (void*)0x00030060,
    /* 0x0E8 */ (void*)0x80182168,
    /* 0x0EC */ (void*)0x80186D78,
    /* 0x0F0 */ (void*)0x0147B47B,
    /* 0x0F4 */ (void*)0x00030060,
    /* 0x0F8 */ (void*)0x80182368,
    /* 0x0FC */ (void*)0x80186D78,
    /* 0x100 */ (void*)0x0198F98F,
    /* 0x104 */ (void*)0x00030060,
    /* 0x108 */ (void*)0x80182568,
    /* 0x10C */ (void*)0x80186D78,
    /* 0x110 */ (void*)0x01B23B23,
    /* 0x114 */ (void*)0x00030060,
    /* 0x118 */ (void*)0x80182768,
    /* 0x11C */ (void*)0x80182D68,
    /* 0x120 */ (void*)0x40B22B22,
    /* 0x124 */ (void*)0x02030020,
    /* 0x128 */ (void*)0x80182768,
    /* 0x12C */ (void*)0x80182D68,
    /* 0x130 */ (void*)0x41990990,
    /* 0x134 */ (void*)0x0203001F,
    /* 0x138 */ (void*)0x80182768,
    /* 0x13C */ (void*)0x80182D68,
    /* 0x140 */ (void*)0x40564564,
    /* 0x144 */ (void*)0x0203001E,
    /* 0x148 */ (void*)0x80182768,
    /* 0x14C */ (void*)0x80182D68,
    /* 0x150 */ (void*)0x4147C47C,
    /* 0x154 */ (void*)0x0203001D,
    /* 0x158 */ (void*)0x80182768,
    /* 0x15C */ (void*)0x80182D68,
    /* 0x160 */ (void*)0x40327327,
    /* 0x164 */ (void*)0x0203001C,
    /* 0x168 */ (void*)0x801800C8,
    /* 0x16C */ (void*)0x801800B8,
    /* 0x170 */ (void*)0x801800D8,
    /* 0x174 */ (void*)0x801800B8,
    /* 0x178 */ (void*)0x801800E8,
    /* 0x17C */ (void*)0x801800B8,
    /* 0x180 */ (void*)0x801800F8,
    /* 0x184 */ (void*)0x801800B8,
    /* 0x188 */ (void*)0x80180108,
    /* 0x18C */ (void*)0x801800B8,
    /* 0x190 */ (void*)0x80180118,
    /* 0x194 */ (void*)0x801800B8,
    /* 0x198 */ (void*)0x80180128,
    /* 0x19C */ (void*)0x801800B8,
    /* 0x1A0 */ (void*)0x80180138,
    /* 0x1A4 */ (void*)0x801800B8,
    /* 0x1A8 */ (void*)0x80180148,
    /* 0x1AC */ (void*)0x801800B8,
    /* 0x1B0 */ (void*)0x80180158,
    /* 0x1B4 */ (void*)0x801800B8,
    /* 0x1B8 */ (void*)0x00000000,
    /* 0x1BC */ (void*)0x00000000,
    /* 0x1C0 */ (void*)0x00000000,
    /* 0x1C4 */ (void*)0x00000000,
    /* 0x1C8 */ (void*)0xFFFFFFFF,
    /* 0x1CC */ (void*)0x00000004,
    /* 0x1D0 */ (void*)0x00400100,
    /* 0x1D4 */ (void*)0x00800080,
    /* 0x1D8 */ (void*)0x80181420,
    /* 0x1DC */ (void*)0x00600100,
    /* 0x1E0 */ (void*)0x00800080,
    /* 0x1E4 */ (void*)0x80181764,
    /* 0x1E8 */ (void*)0xFFFFFFFF,
    /* 0x1EC */ (void*)0x801801B8,
    /* 0x1F0 */ (void*)0x801801B8,
    /* 0x1F4 */ (void*)0x801801B8,
    /* 0x1F8 */ (void*)0x801801B8,
    /* 0x1FC */ (void*)0x801801B8,
    /* 0x200 */ (void*)0x801801CC,
    /* 0x204 */ (void*)0x801801B8,
    /* 0x208 */ (void*)0x801801B8,
    /* 0x20C */ (void*)0x801801B8,
    /* 0x210 */ (void*)0x801801B8,
    /* 0x214 */ (void*)0x801801B8,
    /* 0x218 */ (void*)0x801801B8,
    /* 0x21C */ (void*)0x801801B8,
    /* 0x220 */ (void*)0x801801B8,
    /* 0x224 */ (void*)0x801801B8,
    /* 0x228 */ (void*)0x801801B8,
    /* 0x22C */ (void*)0x801801B8,
    /* 0x230 */ (void*)0x801801B8,
    /* 0x234 */ (void*)0x801801B8,
    /* 0x238 */ (void*)0x801801B8,
};

ObjectInit* g_pStObjLayout[] = {
    /* 0x23C */ (ObjectInit*)0x801812F0,
    /* 0x240 */ (ObjectInit*)0x80181228,
    /* 0x244 */ (ObjectInit*)0x80181250,
    /* 0x248 */ (ObjectInit*)0x801812A0,
    /* 0x24C */ (ObjectInit*)0x801812C8,
    /* 0x250 */ (ObjectInit*)0x80181278,
    /* 0x254 */ (ObjectInit*)0x801812F0,
    /* 0x258 */ (ObjectInit*)0x801812F0,
    /* 0x25C */ (ObjectInit*)0x801812F0,
    /* 0x260 */ (ObjectInit*)0x801812F0,
    /* 0x264 */ (ObjectInit*)0x801812F0,
    /* 0x268 */ (ObjectInit*)0x801812F0,
    /* 0x26C */ (ObjectInit*)0x801812F0,
    /* 0x270 */ (ObjectInit*)0x801812F0,
    /* 0x274 */ (ObjectInit*)0x801812F0,
    /* 0x278 */ (ObjectInit*)0x801812F0,
    /* 0x27C */ (ObjectInit*)0x801812F0,
    /* 0x280 */ (ObjectInit*)0x801812F0,
    /* 0x284 */ (ObjectInit*)0x801812F0,
    /* 0x288 */ (ObjectInit*)0x801812F0,
    /* 0x28C */ (ObjectInit*)0x801812F0,
    /* 0x290 */ (ObjectInit*)0x801812F0,
    /* 0x294 */ (ObjectInit*)0x801812F0,
    /* 0x298 */ (ObjectInit*)0x801812F0,
    /* 0x29C */ (ObjectInit*)0x801812F0,
    /* 0x2A0 */ (ObjectInit*)0x801812F0,
    /* 0x2A4 */ (ObjectInit*)0x801812F0,
    /* 0x2A8 */ (ObjectInit*)0x801812F0,
    /* 0x2AC */ (ObjectInit*)0x801812F0,
    /* 0x2B0 */ (ObjectInit*)0x801812F0,
    /* 0x2B4 */ (ObjectInit*)0x801812F0,
    /* 0x2B8 */ (ObjectInit*)0x801812F0,
    /* 0x2BC */ (ObjectInit*)0x801812F0,
    /* 0x2C0 */ (ObjectInit*)0x801812F0,
    /* 0x2C4 */ (ObjectInit*)0x801812F0,
    /* 0x2C8 */ (ObjectInit*)0x801812F0,
    /* 0x2CC */ (ObjectInit*)0x801812F0,
    /* 0x2D0 */ (ObjectInit*)0x801812F0,
    /* 0x2D4 */ (ObjectInit*)0x801812F0,
    /* 0x2D8 */ (ObjectInit*)0x801812F0,
    /* 0x2DC */ (ObjectInit*)0x801812F0,
    /* 0x2E0 */ (ObjectInit*)0x801812F0,
    /* 0x2E4 */ (ObjectInit*)0x801812F0,
    /* 0x2E8 */ (ObjectInit*)0x801812F0,
    /* 0x2EC */ (ObjectInit*)0x801812F0,
    /* 0x2F0 */ (ObjectInit*)0x801812F0,
    /* 0x2F4 */ (ObjectInit*)0x801812F0,
    /* 0x2F8 */ (ObjectInit*)0x801812F0,
    /* 0x2FC */ (ObjectInit*)0x80181304,
    /* 0x300 */ (ObjectInit*)0x80181304,
    /* 0x304 */ (ObjectInit*)0x80181304,
    /* 0x308 */ (ObjectInit*)0x80181304,
    /* 0x30C */ (ObjectInit*)0x80181304,
};

void* D_80180310[] = {
    /* 310 */ (void*)0x801813EC,
    /* 314 */ (void*)0x80181324,
    /* 318 */ (void*)0x8018134C,
    /* 31C */ (void*)0x8018139C,
    /* 320 */ (void*)0x801813C4,
    /* 324 */ (void*)0x80181374,
    /* 328 */ (void*)0x801813EC,
    /* 32C */ (void*)0x801813EC,
    /* 330 */ (void*)0x801813EC,
    /* 334 */ (void*)0x801813EC,
    /* 338 */ (void*)0x801813EC,
    /* 33C */ (void*)0x801813EC,
    /* 340 */ (void*)0x801813EC,
    /* 344 */ (void*)0x801813EC,
    /* 348 */ (void*)0x801813EC,
    /* 34C */ (void*)0x801813EC,
    /* 350 */ (void*)0x801813EC,
    /* 354 */ (void*)0x801813EC,
    /* 358 */ (void*)0x801813EC,
    /* 35C */ (void*)0x801813EC,
    /* 360 */ (void*)0x801813EC,
    /* 364 */ (void*)0x801813EC,
    /* 368 */ (void*)0x801813EC,
    /* 36C */ (void*)0x801813EC,
    /* 370 */ (void*)0x801813EC,
    /* 374 */ (void*)0x801813EC,
    /* 378 */ (void*)0x801813EC,
    /* 37C */ (void*)0x801813EC,
    /* 380 */ (void*)0x801813EC,
    /* 384 */ (void*)0x801813EC,
    /* 388 */ (void*)0x801813EC,
    /* 38C */ (void*)0x801813EC,
    /* 390 */ (void*)0x801813EC,
    /* 394 */ (void*)0x801813EC,
    /* 398 */ (void*)0x801813EC,
    /* 39C */ (void*)0x801813EC,
    /* 3A0 */ (void*)0x801813EC,
    /* 3A4 */ (void*)0x801813EC,
    /* 3A8 */ (void*)0x801813EC,
    /* 3AC */ (void*)0x801813EC,
    /* 3B0 */ (void*)0x801813EC,
    /* 3B4 */ (void*)0x801813EC,
    /* 3B8 */ (void*)0x801813EC,
    /* 3BC */ (void*)0x801813EC,
    /* 3C0 */ (void*)0x801813EC,
    /* 3C4 */ (void*)0x801813EC,
    /* 3C8 */ (void*)0x801813EC,
    /* 3CC */ (void*)0x801813EC,
    /* 3D0 */ (void*)0x80181400,
    /* 3D4 */ (void*)0x80181400,
    /* 3D8 */ (void*)0x80181400,
    /* 3DC */ (void*)0x80181400,
};

PfnEntityUpdate PfnEntityUpdates[] = {
    /* 3E0 */ (PfnEntityUpdate)0x80181400,
    /* 3E4 */ (PfnEntityUpdate)EntityBreakable,
    /* 3E8 */ (PfnEntityUpdate)func_8018D894,
    /* 3EC */ (PfnEntityUpdate)EntityCandleDrop,
    /* 3F0 */ (PfnEntityUpdate)func_80189734,
    /* 3F4 */ (PfnEntityUpdate)func_8018A9C8,
    /* 3F8 */ (PfnEntityUpdate)func_801902C8,
    /* 3FC */ (PfnEntityUpdate)func_80192610,
    /* 400 */ (PfnEntityUpdate)EntityRoomForeground,
    /* 404 */ (PfnEntityUpdate)func_8019198C,
    /* 408 */ (PfnEntityUpdate)EntityCandleHeartDrop,
    /* 40C */ (PfnEntityUpdate)func_8018E2CC,
    /* 410 */ (PfnEntityUpdate)func_8018ED9C,
    /* 414 */ (PfnEntityUpdate)func_801929A4,
    /* 418 */ (PfnEntityUpdate)func_8018EEC4,
    /* 41C */ (PfnEntityUpdate)func_8018C40C,
    /* 420 */ (PfnEntityUpdate)func_8018C40C,
    /* 424 */ (PfnEntityUpdate)func_80186FD0,
    /* 428 */ (PfnEntityUpdate)func_801870B0,
    /* 42C */ (PfnEntityUpdate)func_8018F510,
    /* 430 */ (PfnEntityUpdate)func_8018F838,
    /* 434 */ (PfnEntityUpdate)func_8018F928,
    /* 438 */ (PfnEntityUpdate)func_801873A0,
    /* 43C */ (PfnEntityUpdate)func_80187F1C,
};

u16 g_eBreakableInit[] = {
    /* 440 */ 0x8001, 0x0000,
    /* 444 */ 0x0000, 0x0000,
    /* 448 */ 0x0000, 0x0000,
};

u16 D_8018044C[] = {
    /* 44C */ 0x0003, 0x0000,
    /* 450 */ 0x0000, 0x0000,
    /* 454 */ 0x0001, 0x0000,
};

u16 D_80180458[] = {
    /* 458 */ 0x0003, 0x0000,
    /* 45C */ 0x0000, 0x0000,
    /* 460 */ 0x0002, 0x0000,
    /* 464 */ 0x0000, 0x0000,
    /* 468 */ 0x0000, 0x0000,
    /* 46C */ 0x0004, 0x0000,
};

u16 D_80180470[] = {
    /* 470 */ 0x0000, 0x0000,
    /* 474 */ 0x0000, 0x0000,
    /* 478 */ 0x0005, 0x0000,
};

u16 D_8018047C[] = {
    /* 47C */ 0x0000, 0x0000,
    /* 480 */ 0x0000, 0x0000,
    /* 484 */ 0x0002, 0x0000,
};

u16 D_80180488[] = {
    /* 488 */ 0x0000, 0x0000,
    /* 48C */ 0x0000, 0x0000,
    /* 490 */ 0x0001, 0x0000,
};

u16 D_80180494[] = {
    /* 494 */ 0x0000, 0x0000,
    /* 498 */ 0x0000, 0x0000,
    /* 49C */ 0x0003, 0x0000,
};

u32 D_801804A0[] = {
    /* 4A0 */ 0x00000000,
    /* 4A4 */ 0x00000000,
    /* 4A8 */ 0x00000003,
    /* 4AC */ 0x00008001,
    /* 4B0 */ 0x00000000,
    /* 4B4 */ 0x00000003,
    /* 4B8 */ 0x0001800B,
    /* 4BC */ 0x021A0048,
    /* 4C0 */ 0x00000061,
};

u32 D_801804C4[] = {
    /* 4C4 */ 0x00008001,
    /* 4C8 */ 0x00000000,
    /* 4CC */ 0x00000005,
    /* 4D0 */ 0x00FF0140,
    /* 4D4 */ 0x26022502,
    /* 4D8 */ 0x26022702,
    /* 4DC */ 0x00000000,
};

ObjInit2 D_801804E0[] = {
    {0x0006, 0x01FA, 0x0000, 0x0000, 0x00, 0x00, 0x10, 0x00, 0x00000000,
     0x801804D0},
    {0x8001, 0x00C0, 0x0000, 0x0000, 0x03, 0x00, 0x30, 0x00, 0x00000000,
     0x801804D4},
};

u16 D_80180508[] = {
    /* 508 */ 0x001D,
    /* 50A */ 0x0025,
    /* 50C */ 0x0075,
    /* 50E */ 0x007D,
    /* 510 */ 0x00C6,
    /* 512 */ 0x00C7,
    /* 514 */ 0x00C8,
    /* 516 */ 0x00C9,
    /* 518 */ 0x001F,
    /* 51A */ 0x0027,
    /* 51C */ 0x0077,
    /* 51E */ 0x007F,
    /* 520 */ 0x00CA,
    /* 522 */ 0x00CB,
    /* 524 */ 0x00CC,
    /* 526 */ 0x00CD,
};

u8 D_80180528[] = {
    /* 528 */ 0x20,
    /* 529 */ 0x20,
    /* 52A */ 0x20,
    /* 52B */ 0x20,
    /* 52C */ 0x20,
    /* 52D */ 0x20,
    /* 52E */ 0x50,
    /* 52F */ 0x20,
};

s8 D_80180530[] = {
    /* 530 */ 0x00,
    /* 531 */ 0x00,
    /* 532 */ 0x00,
    /* 533 */ 0x00,
    /* 534 */ 0x00,
    /* 535 */ 0x00,
    /* 536 */ 0x00,
    /* 537 */ 0x00,
};

s16 D_80180538[] = {
    /* 538 */ 0x0000,
    /* 53A */ 0x0000,
    /* 53C */ 0x0600,
    /* 53E */ 0x0100,
    /* 540 */ 0x0000,
    /* 542 */ 0x0000,
    /* 544 */ 0x0600,
    /* 546 */ 0x01FC,
    /* 548 */ 0x0000,
    /* 54A */ 0x00FC,
    /* 54C */ 0x0600,
    /* 54E */ 0x01FC,
    /* 550 */ 0x0000,
    /* 552 */ 0x0000,
    /* 554 */ 0x0600,
    /* 556 */ 0x01FC,
    /* 558 */ 0x0000,
    /* 55A */ 0x00FC,
    /* 55C */ 0x0600,
    /* 55E */ 0x0300,
    /* 560 */ 0x0000,
    /* 562 */ 0x00FC,
    /* 564 */ 0x0600,
    /* 566 */ 0x01FC,
    /* 568 */ 0x0000,
    /* 56A */ 0x00FC,
    /* 56C */ 0x0600,
    /* 56E */ 0x0300,
    /* 570 */ 0x0000,
    /* 572 */ 0x0200,
    /* 574 */ 0x0600,
    /* 576 */ 0x0300,
    /* 578 */ 0x0000,
    /* 57A */ 0x01FC,
    /* 57C */ 0x0500,
    /* 57E */ 0x02FC,
    /* 580 */ 0x0000,
    /* 582 */ 0x0000,
    /* 584 */ 0x0500,
    /* 586 */ 0x0400,
    /* 588 */ 0x0000,
    /* 58A */ 0x0000,
    /* 58C */ 0x0500,
    /* 58E */ 0x0400,
    /* 590 */ 0x0000,
    /* 592 */ 0x01FC,
    /* 594 */ 0x0500,
    /* 596 */ 0x02FC,
    /* 598 */ 0x00F0,
    /* 59A */ 0x01FC,
    /* 59C */ 0x0310,
    /* 59E */ 0x02FC,
    /* 5A0 */ 0x00F0,
    /* 5A2 */ 0x01FC,
    /* 5A4 */ 0x0310,
    /* 5A6 */ 0x02FC,
    /* 5A8 */ 0x0104,
    /* 5AA */ 0x0204,
    /* 5AC */ 0x0000,
    /* 5AE */ 0x0000,
    /* 5B0 */ 0x0004,
    /* 5B2 */ 0x0004,
    /* 5B4 */ 0x0000,
    /* 5B6 */ 0x0000,
};

u8* g_eBreakableAnimations[] = {
    /* 5B8 */ (u8*)0x801805A8,
    /* 5BC */ (u8*)0x801805B0,
    /* 5C0 */ (u8*)0x00000000,
    /* 5C4 */ (u8*)0x00000000,
    /* 5C8 */ (u8*)0x00000000,
    /* 5CC */ (u8*)0x00000000,
    /* 5D0 */ (u8*)0x00000000,
    /* 5D4 */ (u8*)0x00000000,
};

u8 g_eBreakableHitboxes[] = {
    /* 5D8 */ 0x08,
    /* 5D9 */ 0x08,
    /* 5DA */ 0x00,
    /* 5DB */ 0x00,
    /* 5DC */ 0x00,
    /* 5DD */ 0x00,
    /* 5DE */ 0x00,
    /* 5DF */ 0x00,
};

u8 g_eBreakableExplosionTypes[] = {
    /* 5E0 */ 0x00,
    /* 5E1 */ 0x00,
    /* 5E2 */ 0x00,
    /* 5E3 */ 0x00,
    /* 5E4 */ 0x00,
    /* 5E5 */ 0x00,
    /* 5E6 */ 0x00,
    /* 5E7 */ 0x00,
};

u16 g_eBreakableAnimationSets[] = {
    /* 5E8 */ 0x0003,
    /* 5EA */ 0x0003,
    /* 5EC */ 0x0000,
    /* 5EE */ 0x0000,
    /* 5F0 */ 0x0000,
    /* 5F2 */ 0x0000,
    /* 5F4 */ 0x0000,
    /* 5F6 */ 0x0000,
};

u8 g_eBreakableBlendModes[] = {
    /* 5F8 */ 0x70,
    /* 5F9 */ 0x30,
    /* 5FA */ 0x00,
    /* 5FB */ 0x00,
    /* 5FC */ 0x00,
    /* 5FD */ 0x00,
    /* 5FE */ 0x00,
    /* 5FF */ 0x00,
    /* 600 */ 0x00,
    /* 601 */ 0x00,
    /* 602 */ 0x00,
    /* 603 */ 0x00,
    /* 604 */ 0x00,
    /* 605 */ 0x00,
    /* 606 */ 0x00,
    /* 607 */ 0x00,
};

u32 D_80180608[] = {
    /* 608 */ 0x00000000,
    /* 60C */ 0x00000200,
    /* 610 */ 0x00000400,
    /* 614 */ 0x00000600,
    /* 618 */ 0x00000800,
    /* 61C */ 0x00000A00,
    /* 620 */ 0x00000C00,
    /* 624 */ 0x00000E00,
    /* 628 */ 0x00001000,
    /* 62C */ 0x00001200,
    /* 630 */ 0x00001400,
    /* 634 */ 0x00001600,
    /* 638 */ 0x00001800,
    /* 63C */ 0x00001A00,
    /* 640 */ 0x00001C00,
    /* 644 */ 0x00001E00,
};

u32 D_80180648[] = {
    /* 648 */ 0x00000000,
    /* 64C */ 0x00040000,
    /* 650 */ 0x00040000,
    /* 654 */ 0xFFFC0004,
    /* 658 */ 0x0000FFF8,
};

u16 D_8018065C[] = {
    /* 65C */ 0x000F,
    /* 65E */ 0x0026,
    /* 660 */ 0x0023,
    /* 662 */ 0x002C,
    /* 664 */ 0x003B,
    /* 666 */ 0x0011,
    /* 668 */ 0x0028,
    /* 66A */ 0x000C,
    /* 66C */ 0x0025,
    /* 66E */ 0x0015,
    /* 670 */ 0x0000,
    /* 672 */ 0x0000,
    /* 674 */ 0x0000,
    /* 676 */ 0x0000,
    /* 678 */ 0x0001,
    /* 67A */ 0x0000,
    /* 67C */ 0x0001,
    /* 67E */ 0x0000,
    /* 680 */ 0x0001,
    /* 682 */ 0x0001,
    /* 684 */ 0x0001,
    /* 686 */ 0x0001,
    /* 688 */ 0x0001,
    /* 68A */ 0x0001,
    /* 68C */ 0x0001,
    /* 68E */ 0x0101,
};

u16 D_80180690[] = {
    /* 690 */ 0x8163,
    /* 692 */ 0x8164,
    /* 694 */ 0x8166,
    /* 696 */ 0x8164,
    /* 698 */ 0x8160,
    /* 69A */ 0x8166,
    /* 69C */ 0x8162,
    /* 69E */ 0x8164,
    /* 6A0 */ 0x8167,
    /* 6A2 */ 0x8164,
    /* 6A4 */ 0x8167,
    /* 6A6 */ 0x8168,
    /* 6A8 */ 0x8168,
    /* 6AA */ 0x8164,
    /* 6AC */ 0x8161,
    /* 6AE */ 0x8164,
    /* 6B0 */ 0x8165,
    /* 6B2 */ 0x8165,
    /* 6B4 */ 0x8163,
    /* 6B6 */ 0x8163,
    /* 6B8 */ 0x8165,
    /* 6BA */ 0x8165,
};

u16 D_801806BC[] = {
    /* 6BC */ 0x0000,
    /* 6BE */ 0x0000,
    /* 6C0 */ 0x0000,
    /* 6C2 */ 0x0000,
    /* 6C4 */ 0x0000,
    /* 6C6 */ 0x0000,
    /* 6C8 */ 0x001E,
    /* 6CA */ 0x0000,
    /* 6CC */ 0x0000,
    /* 6CE */ 0x002B,
    /* 6D0 */ 0x0000,
    /* 6D2 */ 0x0010,
    /* 6D4 */ 0x0000,
    /* 6D6 */ 0x000D,
    /* 6D8 */ 0x0068,
    /* 6DA */ 0x0068,
    /* 6DC */ 0x0016,
    /* 6DE */ 0x0000,
    /* 6E0 */ 0x0000,
    /* 6E2 */ 0x0000,
    /* 6E4 */ 0x003E,
    /* 6E6 */ 0x0000,
    /* 6E8 */ 0x0023,
    /* 6EA */ 0x0050,
    /* 6EC */ 0x0000,
    /* 6EE */ 0x0000,
    /* 6F0 */ 0x0000,
    /* 6F2 */ 0x0006,
    /* 6F4 */ 0x0000,
    /* 6F6 */ 0x000A,
    /* 6F8 */ 0x0000,
    /* 6FA */ 0x007D,
    /* 6FC */ 0x0000,
    /* 6FE */ 0x0000,
    /* 700 */ 0x002D,
    /* 702 */ 0x0000,
    /* 704 */ 0x0000,
    /* 706 */ 0x006D,
    /* 708 */ 0x007B,
    /* 70A */ 0x0000,
    /* 70C */ 0x0017,
    /* 70E */ 0x0041,
    /* 710 */ 0x0000,
    /* 712 */ 0x0073,
    /* 714 */ 0x0000,
    /* 716 */ 0x004C,
    /* 718 */ 0x0000,
    /* 71A */ 0x0000,
    /* 71C */ 0x0038,
    /* 71E */ 0x0014,
    /* 720 */ 0x005C,
    /* 722 */ 0x0000,
    /* 724 */ 0x0000,
    /* 726 */ 0x0000,
    /* 728 */ 0x0000,
    /* 72A */ 0x0000,
    /* 72C */ 0x0000,
    /* 72E */ 0x0000,
    /* 730 */ 0x0000,
    /* 732 */ 0x0000,
    /* 734 */ 0x0000,
    /* 736 */ 0x0046,
    /* 738 */ 0x0000,
    /* 73A */ 0x0000,
    /* 73C */ 0x0003,
    /* 73E */ 0x0058,
    /* 740 */ 0x0044,
    /* 742 */ 0x0024,
    /* 744 */ 0x0037,
    /* 746 */ 0x0000,
    /* 748 */ 0x0002,
    /* 74A */ 0x0059,
    /* 74C */ 0x0000,
    /* 74E */ 0x0000,
    /* 750 */ 0x0000,
    /* 752 */ 0x0007,
    /* 754 */ 0x0000,
    /* 756 */ 0x0056,
    /* 758 */ 0x0000,
    /* 75A */ 0x007C,
    /* 75C */ 0x0000,
    /* 75E */ 0x000B,
    /* 760 */ 0x0000,
    /* 762 */ 0x0026,
    /* 764 */ 0x0000,
    /* 766 */ 0x001D,
    /* 768 */ 0x0000,
    /* 76A */ 0x0000,
    /* 76C */ 0x002A,
    /* 76E */ 0x0000,
    /* 770 */ 0x0000,
    /* 772 */ 0x0000,
    /* 774 */ 0x0000,
    /* 776 */ 0x0027,
    /* 778 */ 0x0000,
    /* 77A */ 0x0000,
    /* 77C */ 0x0000,
    /* 77E */ 0x001C,
    /* 780 */ 0x0000,
    /* 782 */ 0x0031,
    /* 784 */ 0x0000,
    /* 786 */ 0x0000,
    /* 788 */ 0x001A,
    /* 78A */ 0x0000,
    /* 78C */ 0x008D,
    /* 78E */ 0x0009,
    /* 790 */ 0x002C,
    /* 792 */ 0x0030,
    /* 794 */ 0x0020,
    /* 796 */ 0x0000,
    /* 798 */ 0x0005,
    /* 79A */ 0x0047,
    /* 79C */ 0x0000,
    /* 79E */ 0x005E,
    /* 7A0 */ 0x0035,
    /* 7A2 */ 0x0034,
    /* 7A4 */ 0x006A,
    /* 7A6 */ 0x0000,
    /* 7A8 */ 0x003A,
    /* 7AA */ 0x0000,
    /* 7AC */ 0x0066,
    /* 7AE */ 0x0000,
    /* 7B0 */ 0x0045,
    /* 7B2 */ 0x0000,
    /* 7B4 */ 0x0019,
    /* 7B6 */ 0x0000,
    /* 7B8 */ 0x0071,
    /* 7BA */ 0x0000,
    /* 7BC */ 0x0029,
    /* 7BE */ 0x0039,
    /* 7C0 */ 0x0000,
    /* 7C2 */ 0x0051,
    /* 7C4 */ 0x0000,
    /* 7C6 */ 0x004D,
    /* 7C8 */ 0x0000,
    /* 7CA */ 0x0000,
    /* 7CC */ 0x003F,
    /* 7CE */ 0x0000,
    /* 7D0 */ 0x0077,
    /* 7D2 */ 0x0000,
    /* 7D4 */ 0x0000,
    /* 7D6 */ 0x0072,
    /* 7D8 */ 0x0000,
    /* 7DA */ 0x0000,
    /* 7DC */ 0x006F,
    /* 7DE */ 0x0000,
    /* 7E0 */ 0x002F,
    /* 7E2 */ 0x0000,
    /* 7E4 */ 0x0074,
    /* 7E6 */ 0x0000,
    /* 7E8 */ 0x0000,
    /* 7EA */ 0x0079,
    /* 7EC */ 0x0000,
    /* 7EE */ 0x007A,
    /* 7F0 */ 0x0000,
    /* 7F2 */ 0x0000,
    /* 7F4 */ 0x0013,
    /* 7F6 */ 0x0011,
    /* 7F8 */ 0x0036,
    /* 7FA */ 0x0036,
    /* 7FC */ 0x0000,
    /* 7FE */ 0x005F,
    /* 800 */ 0x005F,
    /* 802 */ 0x0000,
    /* 804 */ 0x0000,
    /* 806 */ 0x0067,
    /* 808 */ 0x0000,
    /* 80A */ 0x0075,
    /* 80C */ 0x0000,
    /* 80E */ 0x0001,
    /* 810 */ 0x0000,
    /* 812 */ 0x0000,
    /* 814 */ 0x0000,
    /* 816 */ 0x0000,
    /* 818 */ 0x0000,
    /* 81A */ 0x0008,
    /* 81C */ 0x0000,
    /* 81E */ 0x0000,
    /* 820 */ 0x000E,
    /* 822 */ 0x0000,
    /* 824 */ 0x002E,
    /* 826 */ 0x0000,
    /* 828 */ 0x0069,
    /* 82A */ 0x0021,
    /* 82C */ 0x0000,
    /* 82E */ 0x0000,
    /* 830 */ 0x0055,
    /* 832 */ 0x0000,
    /* 834 */ 0x0054,
    /* 836 */ 0x0000,
    /* 838 */ 0x0053,
    /* 83A */ 0x0000,
    /* 83C */ 0x0000,
    /* 83E */ 0x000F,
    /* 840 */ 0x0000,
    /* 842 */ 0x0076,
    /* 844 */ 0x0000,
    /* 846 */ 0x0000,
    /* 848 */ 0x008E,
    /* 84A */ 0x0000,
    /* 84C */ 0x0000,
    /* 84E */ 0x0000,
    /* 850 */ 0x0000,
    /* 852 */ 0x004A,
    /* 854 */ 0x0000,
    /* 856 */ 0x0000,
    /* 858 */ 0x004B,
    /* 85A */ 0x0000,
    /* 85C */ 0x0000,
    /* 85E */ 0x0000,
    /* 860 */ 0x0000,
    /* 862 */ 0x0043,
    /* 864 */ 0x0000,
    /* 866 */ 0x0000,
    /* 868 */ 0x003D,
    /* 86A */ 0x0000,
    /* 86C */ 0x0078,
    /* 86E */ 0x008A,
    /* 870 */ 0x0000,
    /* 872 */ 0x0000,
    /* 874 */ 0x0000,
    /* 876 */ 0x0052,
    /* 878 */ 0x0000,
    /* 87A */ 0x0000,
    /* 87C */ 0x0089,
    /* 87E */ 0x0048,
    /* 880 */ 0x0000,
    /* 882 */ 0x003C,
    /* 884 */ 0x0040,
    /* 886 */ 0x008B,
    /* 888 */ 0x0000,
    /* 88A */ 0x0000,
    /* 88C */ 0x0000,
    /* 88E */ 0x001F,
    /* 890 */ 0x0000,
    /* 892 */ 0x0000,
    /* 894 */ 0x007E,
    /* 896 */ 0x0000,
    /* 898 */ 0x0000,
    /* 89A */ 0x0049,
    /* 89C */ 0x0000,
    /* 89E */ 0x0000,
    /* 8A0 */ 0x0000,
    /* 8A2 */ 0x0015,
    /* 8A4 */ 0x0000,
    /* 8A6 */ 0x0000,
    /* 8A8 */ 0x000C,
    /* 8AA */ 0x0028,
    /* 8AC */ 0x0000,
    /* 8AE */ 0x0000,
    /* 8B0 */ 0x0000,
    /* 8B2 */ 0x0032,
    /* 8B4 */ 0x0000,
    /* 8B6 */ 0x0022,
    /* 8B8 */ 0x0012,
    /* 8BA */ 0x0000,
    /* 8BC */ 0x0000,
    /* 8BE */ 0x0000,
    /* 8C0 */ 0x0000,
    /* 8C2 */ 0x0000,
    /* 8C4 */ 0x0000,
    /* 8C6 */ 0x0033,
    /* 8C8 */ 0x0060,
    /* 8CA */ 0x0000,
    /* 8CC */ 0x0064,
    /* 8CE */ 0x0000,
    /* 8D0 */ 0x0000,
    /* 8D2 */ 0x007F,
    /* 8D4 */ 0x0000,
    /* 8D6 */ 0x0000,
    /* 8D8 */ 0x0000,
    /* 8DA */ 0x004E,
    /* 8DC */ 0x0000,
    /* 8DE */ 0x006E,
    /* 8E0 */ 0x0000,
    /* 8E2 */ 0x0000,
    /* 8E4 */ 0x0000,
    /* 8E6 */ 0x004F,
    /* 8E8 */ 0x0000,
    /* 8EA */ 0x0000,
    /* 8EC */ 0x0057,
    /* 8EE */ 0x0000,
    /* 8F0 */ 0x0000,
    /* 8F2 */ 0x0000,
    /* 8F4 */ 0x0086,
    /* 8F6 */ 0x0065,
    /* 8F8 */ 0x0000,
    /* 8FA */ 0x003B,
    /* 8FC */ 0x0000,
    /* 8FE */ 0x0000,
    /* 900 */ 0x0000,
    /* 902 */ 0x0000,
    /* 904 */ 0x0000,
    /* 906 */ 0x0000,
    /* 908 */ 0x0025,
    /* 90A */ 0x0062,
    /* 90C */ 0x0062,
    /* 90E */ 0x0000,
    /* 910 */ 0x0000,
    /* 912 */ 0x0000,
    /* 914 */ 0x0042,
    /* 916 */ 0x0000,
    /* 918 */ 0x0000,
    /* 91A */ 0x0018,
    /* 91C */ 0x001B,
    /* 91E */ 0x006B,
    /* 920 */ 0x0000,
    /* 922 */ 0x008C,
    /* 924 */ 0x0000,
    /* 926 */ 0x0000,
    /* 928 */ 0x0000,
    /* 92A */ 0x0000,
    /* 92C */ 0x0000,
    /* 92E */ 0x0000,
    /* 930 */ 0x0000,
    /* 932 */ 0x0000,
    /* 934 */ 0x0000,
    /* 936 */ 0x0000,
    /* 938 */ 0x0000,
    /* 93A */ 0x0000,
    /* 93C */ 0x0000,
    /* 93E */ 0x0000,
    /* 940 */ 0x0061,
    /* 942 */ 0x0063,
    /* 944 */ 0x0088,
    /* 946 */ 0x0000,
    /* 948 */ 0x0000,
    /* 94A */ 0x0000,
    /* 94C */ 0x0085,
    /* 94E */ 0x0000,
    /* 950 */ 0x0000,
    /* 952 */ 0x0000,
    /* 954 */ 0x0000,
    /* 956 */ 0x0000,
    /* 958 */ 0x0084,
    /* 95A */ 0x0000,
    /* 95C */ 0x0000,
    /* 95E */ 0x0087,
    /* 960 */ 0x0000,
    /* 962 */ 0x0000,
    /* 964 */ 0x0000,
    /* 966 */ 0x0000,
    /* 968 */ 0x005D,
    /* 96A */ 0x0000,
    /* 96C */ 0x0000,
    /* 96E */ 0x0000,
    /* 970 */ 0x0000,
    /* 972 */ 0x0000,
    /* 974 */ 0x0000,
    /* 976 */ 0x0000,
    /* 978 */ 0x005B,
    /* 97A */ 0x0091,
    /* 97C */ 0x0000,
    /* 97E */ 0x0000,
    /* 980 */ 0x0000,
    /* 982 */ 0x0000,
    /* 984 */ 0x0090,
    /* 986 */ 0x0000,
    /* 988 */ 0x0000,
    /* 98A */ 0x0000,
    /* 98C */ 0x0000,
    /* 98E */ 0x0000,
    /* 990 */ 0x0000,
    /* 992 */ 0x005A,
    /* 994 */ 0x0000,
    /* 996 */ 0x0000,
    /* 998 */ 0x0082,
    /* 99A */ 0x0000,
    /* 99C */ 0x0000,
    /* 99E */ 0x0000,
    /* 9A0 */ 0x0083,
    /* 9A2 */ 0x0000,
    /* 9A4 */ 0x0081,
    /* 9A6 */ 0x0000,
    /* 9A8 */ 0x0000,
    /* 9AA */ 0x0000,
    /* 9AC */ 0x0000,
    /* 9AE */ 0x0000,
    /* 9B0 */ 0x0000,
    /* 9B2 */ 0x0092,
    /* 9B4 */ 0x0000,
    /* 9B6 */ 0x0000,
    /* 9B8 */ 0x0000,
    /* 9BA */ 0x0000,
    /* 9BC */ 0x0004,
    /* 9BE */ 0x0000,
    /* 9C0 */ 0x0070,
    /* 9C2 */ 0x0000,
    /* 9C4 */ 0x0000,
    /* 9C6 */ 0x006C,
    /* 9C8 */ 0x0000,
    /* 9CA */ 0x0000,
    /* 9CC */ 0x0080,
    /* 9CE */ 0x0080,
    /* 9D0 */ 0x0000,
    /* 9D2 */ 0x0000,
    /* 9D4 */ 0x008F,
    /* 9D6 */ 0x0000,
    /* 9D8 */ 0x0000,
    /* 9DA */ 0x0000,
};

u8 D_801809DC[] = {
    /* 9DC */ 0x00,
    /* 9DD */ 0x40,
    /* 9DE */ 0x20,
    /* 9DF */ 0x10,
};

u8 D_801809E0[] = {
    /* 9E0 */ 0x80,
    /* 9E1 */ 0x80,
    /* 9E2 */ 0xA0,
    /* 9E3 */ 0xA0,
    /* 9E4 */ 0xC0,
    /* 9E5 */ 0xC0,
    /* 9E6 */ 0x00,
    /* 9E7 */ 0x00,
};

u8 D_801809E8[] = {
    /* 9E8 */ 0x60,
    /* 9E9 */ 0x60,
    /* 9EA */ 0x60,
    /* 9EB */ 0x60,
    /* 9EC */ 0x60,
    /* 9ED */ 0x60,
    /* 9EE */ 0x00,
    /* 9EF */ 0x00,
};

u16 D_801809F0[] = {
    /* 9F0 */ 0x8000,
    /* 9F2 */ 0x4000,
    /* 9F4 */ 0x2000,
    /* 9F6 */ 0x1000,
    /* 9F8 */ 0x0800,
    /* 9FA */ 0x0200,
    /* 9FC */ 0x0100,
    /* 9FE */ 0x0080,
    /* A00 */ 0x0400,
    /* A02 */ 0x0040,
};

u8 D_80180A04[] = {
    /* A04 */ 0x02,
    /* A05 */ 0x04,
    /* A06 */ 0x03,
    /* A07 */ 0x05,
    /* A08 */ 0x06,
    /* A09 */ 0x07,
    /* A0A */ 0x08,
    /* A0B */ 0x0A,
    /* A0C */ 0x02,
    /* A0D */ 0x01,
    /* A0E */ 0x00,
    /* A0F */ 0x00,
};

u16 D_80180A10[] = {
    /* A10 */ 0x0003,
    /* A12 */ 0x0000,
    /* A14 */ 0x0002,
    /* A16 */ 0x0003,
    /* A18 */ 0x0003,
    /* A1A */ 0x0003,
    /* A1C */ 0x0003,
    /* A1E */ 0x0003,
    /* A20 */ 0x0003,
    /* A22 */ 0x0004,
    /* A24 */ 0x0004,
    /* A26 */ 0x0004,
    /* A28 */ 0x0004,
    /* A2A */ 0x0005,
    /* A2C */ 0x0005,
    /* A2E */ 0x0000,
    /* A30 */ 0x0000,
    /* A32 */ 0x0000,
    /* A34 */ 0x0000,
    /* A36 */ 0x0000,
    /* A38 */ 0x0000,
    /* A3A */ 0x0000,
    /* A3C */ 0x0000,
    /* A3E */ 0x0000,
    /* A40 */ 0x0000,
    /* A42 */ 0x0000,
    /* A44 */ 0x0001,
    /* A46 */ 0x0001,
    /* A48 */ 0x0002,
    /* A4A */ 0x0006,
    /* A4C */ 0x0007,
    /* A4E */ 0x00C6,
};

u16 D_80180A50[] = {
    /* A50 */ 0x0C00,
    /* A52 */ 0x0168,
    /* A54 */ 0x0F00,
    /* A56 */ 0x0169,
    /* A58 */ 0x0FD0,
    /* A5A */ 0x016A,
    /* A5C */ 0x0FF0,
    /* A5E */ 0x016B,
    /* A60 */ 0x0FF8,
    /* A62 */ 0x016C,
    /* A64 */ 0x0FFD,
    /* A66 */ 0x016D,
    /* A68 */ 0x0FFF,
    /* A6A */ 0x016E,
};

u16 D_80180A6C[] = {
    /* A6C */ 0x01B2,
    /* A6E */ 0x01B3,
    /* A70 */ 0x01B6,
    /* A72 */ 0x01B7,
    /* A74 */ 0x01B4,
    /* A76 */ 0x01B5,
    /* A78 */ 0x01B0,
    /* A7A */ 0x01B1,
};

u8 D_80180A7C[] = {
    /* A7C */ 0xB1,
    /* A7D */ 0xB7,
    /* A7E */ 0xB1,
    /* A7F */ 0xB7,
    /* A80 */ 0x21,
    /* A81 */ 0x21,
    /* A82 */ 0x5F,
    /* A83 */ 0x5F,
    /* A84 */ 0x88,
    /* A85 */ 0xA8,
    /* A86 */ 0x88,
    /* A87 */ 0xA8,
    /* A88 */ 0x21,
    /* A89 */ 0x21,
    /* A8A */ 0x5F,
    /* A8B */ 0x5F,
    /* A8C */ 0xA8,
    /* A8D */ 0x88,
    /* A8E */ 0xA8,
    /* A8F */ 0x88,
    /* A90 */ 0x21,
    /* A91 */ 0x21,
    /* A92 */ 0x5F,
    /* A93 */ 0x5F,
};

s16 D_80180A94[] = {
    /* A94 */ 0x0000,
    /* A96 */ 0x0065,
    /* A98 */ 0x00C9,
    /* A9A */ 0x012D,
    /* A9C */ 0x0191,
    /* A9E */ 0x01F5,
    /* AA0 */ 0x0259,
    /* AA2 */ 0x02BC,
    /* AA4 */ 0x031F,
    /* AA6 */ 0x0381,
    /* AA8 */ 0x03E3,
    /* AAA */ 0x0444,
    /* AAC */ 0x04A5,
    /* AAE */ 0x0505,
    /* AB0 */ 0x0564,
    /* AB2 */ 0x05C2,
    /* AB4 */ 0x061F,
    /* AB6 */ 0x067C,
    /* AB8 */ 0x06D7,
    /* ABA */ 0x0732,
    /* ABC */ 0x078B,
    /* ABE */ 0x07E3,
    /* AC0 */ 0x083A,
    /* AC2 */ 0x088F,
    /* AC4 */ 0x08E4,
    /* AC6 */ 0x0937,
    /* AC8 */ 0x0988,
    /* ACA */ 0x09D8,
    /* ACC */ 0x0A26,
    /* ACE */ 0x0A73,
    /* AD0 */ 0x0ABF,
    /* AD2 */ 0x0B08,
    /* AD4 */ 0x0B50,
    /* AD6 */ 0x0B97,
    /* AD8 */ 0x0BDB,
    /* ADA */ 0x0C1E,
    /* ADC */ 0x0C5E,
    /* ADE */ 0x0C9D,
    /* AE0 */ 0x0CDA,
    /* AE2 */ 0x0D15,
    /* AE4 */ 0x0D4E,
    /* AE6 */ 0x0D85,
    /* AE8 */ 0x0DB9,
    /* AEA */ 0x0DEC,
    /* AEC */ 0x0E1C,
    /* AEE */ 0x0E4B,
    /* AF0 */ 0x0E77,
    /* AF2 */ 0x0EA1,
    /* AF4 */ 0x0EC8,
    /* AF6 */ 0x0EEE,
    /* AF8 */ 0x0F11,
    /* AFA */ 0x0F31,
    /* AFC */ 0x0F50,
    /* AFE */ 0x0F6C,
    /* B00 */ 0x0F85,
    /* B02 */ 0x0F9C,
    /* B04 */ 0x0FB1,
    /* B06 */ 0x0FC4,
    /* B08 */ 0x0FD4,
    /* B0A */ 0x0FE1,
    /* B0C */ 0x0FEC,
    /* B0E */ 0x0FF5,
    /* B10 */ 0x0FFB,
    /* B12 */ 0x0FFF,
    /* B14 */ 0x1000,
    /* B16 */ 0x0FFF,
    /* B18 */ 0x0FFB,
    /* B1A */ 0x0FF5,
    /* B1C */ 0x0FEC,
    /* B1E */ 0x0FE1,
    /* B20 */ 0x0FD4,
    /* B22 */ 0x0FC4,
    /* B24 */ 0x0FB1,
    /* B26 */ 0x0F9C,
    /* B28 */ 0x0F85,
    /* B2A */ 0x0F6C,
    /* B2C */ 0x0F50,
    /* B2E */ 0x0F31,
    /* B30 */ 0x0F11,
    /* B32 */ 0x0EEE,
    /* B34 */ 0x0EC8,
    /* B36 */ 0x0EA1,
    /* B38 */ 0x0E77,
    /* B3A */ 0x0E4B,
    /* B3C */ 0x0E1C,
    /* B3E */ 0x0DEC,
    /* B40 */ 0x0DB9,
    /* B42 */ 0x0D85,
    /* B44 */ 0x0D4E,
    /* B46 */ 0x0D15,
    /* B48 */ 0x0CDA,
    /* B4A */ 0x0C9D,
    /* B4C */ 0x0C5E,
    /* B4E */ 0x0C1E,
    /* B50 */ 0x0BDB,
    /* B52 */ 0x0B97,
    /* B54 */ 0x0B50,
    /* B56 */ 0x0B08,
    /* B58 */ 0x0ABF,
    /* B5A */ 0x0A73,
    /* B5C */ 0x0A26,
    /* B5E */ 0x09D8,
    /* B60 */ 0x0988,
    /* B62 */ 0x0937,
    /* B64 */ 0x08E4,
    /* B66 */ 0x088F,
    /* B68 */ 0x083A,
    /* B6A */ 0x07E3,
    /* B6C */ 0x078B,
    /* B6E */ 0x0732,
    /* B70 */ 0x06D7,
    /* B72 */ 0x067C,
    /* B74 */ 0x061F,
    /* B76 */ 0x05C2,
    /* B78 */ 0x0564,
    /* B7A */ 0x0505,
    /* B7C */ 0x04A5,
    /* B7E */ 0x0444,
    /* B80 */ 0x03E3,
    /* B82 */ 0x0381,
    /* B84 */ 0x031F,
    /* B86 */ 0x02BC,
    /* B88 */ 0x0259,
    /* B8A */ 0x01F5,
    /* B8C */ 0x0191,
    /* B8E */ 0x012D,
    /* B90 */ 0x00C9,
    /* B92 */ 0x0065,
    /* B94 */ 0x0000,
    /* B96 */ 0xFF9B,
    /* B98 */ 0xFF37,
    /* B9A */ 0xFED3,
    /* B9C */ 0xFE6F,
    /* B9E */ 0xFE0B,
    /* BA0 */ 0xFDA7,
    /* BA2 */ 0xFD44,
    /* BA4 */ 0xFCE1,
    /* BA6 */ 0xFC7F,
    /* BA8 */ 0xFC1D,
    /* BAA */ 0xFBBC,
    /* BAC */ 0xFB5B,
    /* BAE */ 0xFAFB,
    /* BB0 */ 0xFA9C,
    /* BB2 */ 0xFA3E,
    /* BB4 */ 0xF9E1,
    /* BB6 */ 0xF984,
    /* BB8 */ 0xF929,
    /* BBA */ 0xF8CE,
    /* BBC */ 0xF875,
    /* BBE */ 0xF81D,
    /* BC0 */ 0xF7C6,
    /* BC2 */ 0xF771,
    /* BC4 */ 0xF71C,
    /* BC6 */ 0xF6C9,
    /* BC8 */ 0xF678,
    /* BCA */ 0xF628,
    /* BCC */ 0xF5DA,
    /* BCE */ 0xF58D,
    /* BD0 */ 0xF541,
    /* BD2 */ 0xF4F8,
    /* BD4 */ 0xF4B0,
    /* BD6 */ 0xF469,
    /* BD8 */ 0xF425,
    /* BDA */ 0xF3E2,
    /* BDC */ 0xF3A2,
    /* BDE */ 0xF363,
    /* BE0 */ 0xF326,
    /* BE2 */ 0xF2EB,
    /* BE4 */ 0xF2B2,
    /* BE6 */ 0xF27B,
    /* BE8 */ 0xF247,
    /* BEA */ 0xF214,
    /* BEC */ 0xF1E4,
    /* BEE */ 0xF1B5,
    /* BF0 */ 0xF189,
    /* BF2 */ 0xF15F,
    /* BF4 */ 0xF138,
    /* BF6 */ 0xF112,
    /* BF8 */ 0xF0EF,
    /* BFA */ 0xF0CF,
    /* BFC */ 0xF0B0,
    /* BFE */ 0xF094,
    /* C00 */ 0xF07B,
    /* C02 */ 0xF064,
    /* C04 */ 0xF04F,
    /* C06 */ 0xF03C,
    /* C08 */ 0xF02C,
    /* C0A */ 0xF01F,
    /* C0C */ 0xF014,
    /* C0E */ 0xF00B,
    /* C10 */ 0xF005,
    /* C12 */ 0xF001,
    /* C14 */ 0xF000,
    /* C16 */ 0xF001,
    /* C18 */ 0xF005,
    /* C1A */ 0xF00B,
    /* C1C */ 0xF014,
    /* C1E */ 0xF01F,
    /* C20 */ 0xF02C,
    /* C22 */ 0xF03C,
    /* C24 */ 0xF04F,
    /* C26 */ 0xF064,
    /* C28 */ 0xF07B,
    /* C2A */ 0xF094,
    /* C2C */ 0xF0B0,
    /* C2E */ 0xF0CF,
    /* C30 */ 0xF0EF,
    /* C32 */ 0xF112,
    /* C34 */ 0xF138,
    /* C36 */ 0xF15F,
    /* C38 */ 0xF189,
    /* C3A */ 0xF1B5,
    /* C3C */ 0xF1E4,
    /* C3E */ 0xF214,
    /* C40 */ 0xF247,
    /* C42 */ 0xF27B,
    /* C44 */ 0xF2B2,
    /* C46 */ 0xF2EB,
    /* C48 */ 0xF326,
    /* C4A */ 0xF363,
    /* C4C */ 0xF3A2,
    /* C4E */ 0xF3E2,
    /* C50 */ 0xF425,
    /* C52 */ 0xF469,
    /* C54 */ 0xF4B0,
    /* C56 */ 0xF4F8,
    /* C58 */ 0xF541,
    /* C5A */ 0xF58D,
    /* C5C */ 0xF5DA,
    /* C5E */ 0xF628,
    /* C60 */ 0xF678,
    /* C62 */ 0xF6C9,
    /* C64 */ 0xF71C,
    /* C66 */ 0xF771,
    /* C68 */ 0xF7C6,
    /* C6A */ 0xF81D,
    /* C6C */ 0xF875,
    /* C6E */ 0xF8CE,
    /* C70 */ 0xF929,
    /* C72 */ 0xF984,
    /* C74 */ 0xF9E1,
    /* C76 */ 0xFA3E,
    /* C78 */ 0xFA9C,
    /* C7A */ 0xFAFB,
    /* C7C */ 0xFB5B,
    /* C7E */ 0xFBBC,
    /* C80 */ 0xFC1D,
    /* C82 */ 0xFC7F,
    /* C84 */ 0xFCE1,
    /* C86 */ 0xFD44,
    /* C88 */ 0xFDA7,
    /* C8A */ 0xFE0B,
    /* C8C */ 0xFE6F,
    /* C8E */ 0xFED3,
    /* C90 */ 0xFF37,
    /* C92 */ 0xFF9B,
    /* C94 */ 0x0E01,
    /* C96 */ 0x0000,
    /* C98 */ 0x0302,
    /* C9A */ 0x0406,
    /* C9C */ 0x0505,
    /* C9E */ 0x0605,
    /* CA0 */ 0x0704,
    /* CA2 */ 0x0803,
    /* CA4 */ 0x0904,
    /* CA6 */ 0x0A05,
    /* CA8 */ 0x0B05,
    /* CAA */ 0x0C06,
    /* CAC */ 0x0307,
    /* CAE */ 0x0406,
    /* CB0 */ 0x0505,
    /* CB2 */ 0x0605,
    /* CB4 */ 0x0704,
    /* CB6 */ 0x0803,
    /* CB8 */ 0x0904,
    /* CBA */ 0x0A05,
    /* CBC */ 0x0B05,
    /* CBE */ 0x0C06,
    /* CC0 */ 0x0D02,
    /* CC2 */ 0x0000,
    /* CC4 */ 0x1404,
    /* CC6 */ 0x1507,
    /* CC8 */ 0x1606,
    /* CCA */ 0x1703,
    /* CCC */ 0x1803,
    /* CCE */ 0x1906,
    /* CD0 */ 0x1502,
    /* CD2 */ 0x0000,
    /* CD4 */ 0x1A01,
    /* CD6 */ 0x0000,
    /* CD8 */ 0x1B01,
    /* CDA */ 0x0000,
    /* CDC */ 0x1C01,
    /* CDE */ 0x0000,
    /* CE0 */ 0x1D01,
    /* CE2 */ 0x0000,
    /* CE4 */ 0x1E01,
    /* CE6 */ 0x0000,
    /* CE8 */ 0x1F01,
    /* CEA */ 0x0000,
    /* CEC */ 0x2001,
    /* CEE */ 0x0000,
    /* CF0 */ 0x2101,
    /* CF2 */ 0x0000,
    /* CF4 */ 0x2202,
    /* CF6 */ 0x2302,
    /* CF8 */ 0x2402,
    /* CFA */ 0x2502,
    /* CFC */ 0x2602,
    /* CFE */ 0x2702,
    /* D00 */ 0x2802,
    /* D02 */ 0x2902,
    /* D04 */ 0x0000,
    /* D06 */ 0x0000,
    /* D08 */ 0x0F1A,
    /* D0A */ 0x1006,
    /* D0C */ 0x1104,
    /* D0E */ 0x1202,
    /* D10 */ 0x1104,
    /* D12 */ 0x1006,
    /* D14 */ 0x0000,
    /* D16 */ 0x0000,
    /* D18 */ 0x1301,
    /* D1A */ 0x0000,
    /* D1C */ 0x2A05,
    /* D1E */ 0x2B05,
    /* D20 */ 0x2C05,
    /* D22 */ 0x2D05,
    /* D24 */ 0x2E05,
    /* D26 */ 0x2F05,
    /* D28 */ 0x3005,
    /* D2A */ 0x3105,
    /* D2C */ 0x0000,
    /* D2E */ 0x0000,
    /* D30 */ 0x3205,
    /* D32 */ 0x3305,
    /* D34 */ 0x3405,
    /* D36 */ 0x3505,
    /* D38 */ 0x3605,
    /* D3A */ 0x3705,
    /* D3C */ 0x3805,
    /* D3E */ 0x3905,
    /* D40 */ 0x0000,
    /* D42 */ 0x0000,
    /* D44 */ 0x3A05,
    /* D46 */ 0x3B05,
    /* D48 */ 0x3C05,
    /* D4A */ 0x3D05,
    /* D4C */ 0x3E05,
    /* D4E */ 0x3F05,
    /* D50 */ 0x4005,
    /* D52 */ 0x4105,
    /* D54 */ 0x0000,
    /* D56 */ 0x0000,
    /* D58 */ 0x4205,
    /* D5A */ 0x4305,
    /* D5C */ 0x4405,
    /* D5E */ 0x4505,
    /* D60 */ 0x4605,
    /* D62 */ 0x4705,
    /* D64 */ 0x4805,
    /* D66 */ 0x4905,
    /* D68 */ 0x0000,
    /* D6A */ 0x0000,
    /* D6C */ 0x4A05,
    /* D6E */ 0x4B05,
    /* D70 */ 0x4C05,
    /* D72 */ 0x4D05,
    /* D74 */ 0x4E05,
    /* D76 */ 0x4F05,
    /* D78 */ 0x5005,
    /* D7A */ 0x5105,
    /* D7C */ 0x0000,
    /* D7E */ 0x0000,
    /* D80 */ 0x5205,
    /* D82 */ 0x5305,
    /* D84 */ 0x5405,
    /* D86 */ 0x5505,
    /* D88 */ 0x5605,
    /* D8A */ 0x5705,
    /* D8C */ 0x5805,
    /* D8E */ 0x5905,
    /* D90 */ 0x0000,
    /* D92 */ 0x0000,
    /* D94 */ 0x5A05,
    /* D96 */ 0x5B05,
    /* D98 */ 0x5C05,
    /* D9A */ 0x5D05,
    /* D9C */ 0x5E05,
    /* D9E */ 0x5F05,
    /* DA0 */ 0x6005,
    /* DA2 */ 0x6105,
    /* DA4 */ 0x0000,
    /* DA6 */ 0x0000,
    /* DA8 */ 0x6205,
    /* DAA */ 0x6305,
    /* DAC */ 0x6405,
    /* DAE */ 0x6505,
    /* DB0 */ 0x6605,
    /* DB2 */ 0x6705,
    /* DB4 */ 0x6805,
    /* DB6 */ 0x6905,
    /* DB8 */ 0x0000,
    /* DBA */ 0x0000,
    /* DBC */ 0x6A05,
    /* DBE */ 0x6B05,
    /* DC0 */ 0x6C05,
    /* DC2 */ 0x6D05,
};

u16 D_80180DC4[] = {
    /* DC4 */ 0x6E05,
    /* DC6 */ 0x6F05,
    /* DC8 */ 0x7005,
    /* DCA */ 0x7105,
    /* DCC */ 0x0000,
    /* DCE */ 0x0000,
    /* DD0 */ 0x8F01,
    /* DD2 */ 0x0000,
    /* DD4 */ 0xFCFC,
    /* DD6 */ 0xFC04,
    /* DD8 */ 0x04FC,
    /* DDA */ 0x0404,
    /* DDC */ 0x0080,
    /* DDE */ 0x0000,
    /* DE0 */ 0x0001,
    /* DE2 */ 0x0002,
    /* DE4 */ 0x0004,
    /* DE6 */ 0x0003,
    /* DE8 */ 0x0006,
    /* DEA */ 0x0005,
    /* DEC */ 0x0007,
    /* DEE */ 0x0008,
    /* DF0 */ 0x0009,
    /* DF2 */ 0x0000,
};

u16 D_80180DF4[] = {
    /* DF4 */ 0x0000,
    /* DF6 */ 0x000E,
    /* DF8 */ 0x000F,
    /* DFA */ 0x0011,
    /* DFC */ 0x0010,
    /* DFE */ 0x0013,
    /* E00 */ 0x0012,
    /* E02 */ 0x0014,
    /* E04 */ 0x0015,
    /* E06 */ 0x0016,
};

void* D_80180E08[] = {
    /* E08 */ (void*)0x80186F08,
    /* E0C */ (void*)0x80186F00,
    /* E10 */ (void*)0x80186EF8,
    /* E14 */ (void*)0x80186EF0,
    /* E18 */ (void*)0x80186EE8,
    /* E1C */ (void*)0x80186EE0,
    /* E20 */ (void*)0x80186ED8,
    /* E24 */ (void*)0x80186ED0,
    /* E28 */ (void*)0x80186EC8,
    /* E2C */ (void*)0x80186EC0,
};

s32 c_GoldPrizes[] = {
    1, 25, 50, 100, 250, 400, 700, 1000, 2000, 5000,
};

void* D_80180E58[] = {
    /* E58 */ (void*)0x80180C94,
    /* E5C */ (void*)0x80180C98,
    /* E60 */ (void*)0x80180CC4,
    /* E64 */ (void*)0x80180CD4,
    /* E68 */ (void*)0x80180CD8,
    /* E6C */ (void*)0x80180CDC,
    /* E70 */ (void*)0x80180CE0,
    /* E74 */ (void*)0x80180CE4,
    /* E78 */ (void*)0x80180CE8,
    /* E7C */ (void*)0x80180CEC,
    /* E80 */ (void*)0x80180CF0,
    /* E84 */ (void*)0x80180CF4,
    /* E88 */ (void*)0x80180D08,
    /* E8C */ (void*)0x80180D18,
    /* E90 */ (void*)0x80180D58,
    /* E94 */ (void*)0x80180D44,
    /* E98 */ (void*)0x80180D1C,
    /* E9C */ (void*)0x80180D30,
    /* EA0 */ (void*)0x80180D6C,
    /* EA4 */ (void*)0x80180D80,
    /* EA8 */ (void*)0x80180D94,
    /* EAC */ (void*)0x80180DA8,
    /* EB0 */ (void*)0x80180DBC,
    /* EB4 */ (void*)0x80180DD0,
};

u32 D_80180EB8[] = {
    /* EB8 */ 0x0004FFFA,
    /* EBC */ 0xFFF80000,
};

s8 c_HeartPrizes[] = {1, 5};

s32 D_80180EC4[] = {
    /* EC4 */ 0xFFFF0000,
    /* EC8 */ 0xFFFE8000,
    /* ECC */ 0xFFFE8000,
    /* ED0 */ 0xFFFE8000,
    /* ED4 */ 0xFFFD0000,
    /* ED8 */ 0x02020102,
    /* EDC */ 0x04020302,
    /* EE0 */ 0x06020502,
    /* EE4 */ 0x08020702,
    /* EE8 */ 0x00000000,
};

u8 D_80180EEC[] = {
    /* EEC */ 0x01, 0x09, 0x02, 0x0A,
    /* EF0 */ 0x02, 0x0B, 0x02, 0x0C,
    /* EF4 */ 0x02, 0x0D, 0x02, 0x0E,
    /* EF8 */ 0x02, 0x0F, 0x02, 0x10,
    /* EFC */ 0x02, 0x11, 0x02, 0x12,
    /* F00 */ 0x03, 0x13, 0x04, 0x14,
    /* F04 */ 0x00, 0x00, 0x00, 0x00,
    /* F08 */ 0x02, 0x15, 0x02, 0x16,
    /* F0C */ 0x02, 0x17, 0x02, 0x18,
    /* F10 */ 0x02, 0x19, 0x02, 0x1A,
    /* F14 */ 0x02, 0x1B, 0x02, 0x1C,
    /* F18 */ 0x02, 0x1D, 0x02, 0x1E,
    /* F1C */ 0x02, 0x1F, 0x02, 0x20,
    /* F20 */ 0x02, 0x21, 0x02, 0x22,
    /* F24 */ 0x02, 0x23, 0x02, 0x24,
    /* F28 */ 0x02, 0x25, 0x02, 0x26,
    /* F2C */ 0x02, 0x27, 0x02, 0x28,
    /* F30 */ 0x02, 0x29, 0x02, 0x2A,
    /* F34 */ 0x00, 0x00, 0x00, 0x00,
    /* F38 */ 0x02, 0x2B, 0x02, 0x2C,
    /* F3C */ 0x02, 0x2D, 0x02, 0x2E,
    /* F40 */ 0x02, 0x2F, 0x02, 0x30,
    /* F44 */ 0x02, 0x31, 0x02, 0x32,
    /* F48 */ 0x02, 0x33, 0x02, 0x34,
    /* F4C */ 0x02, 0x35, 0x02, 0x36,
    /* F50 */ 0x02, 0x37, 0x02, 0x38,
    /* F54 */ 0x02, 0x39, 0x02, 0x3A,
    /* F58 */ 0x02, 0x3B, 0x02, 0x3C,
    /* F5C */ 0x02, 0x3D, 0x02, 0x3E,
    /* F60 */ 0x02, 0x3F, 0x02, 0x40,
    /* F64 */ 0x02, 0x41, 0x02, 0x42,
    /* F68 */ 0x00, 0x00, 0x00, 0x00,
    /* F6C */ 0x01, 0x43, 0x00, 0x00,
};

u8* D_80180F70[] = {
    /* F70 */ (u8*)0x80180ED8,
    /* F74 */ (u8*)&D_80180EEC,
    /* F78 */ (u8*)0x80180F08,
    /* F7C */ (u8*)0x80180F38,
    /* F80 */ (u8*)0x80180F6C,
};

void* D_80180F84[] = {
    /* F84 */ (void*)0x80186F48,
};

s16 D_80180F88[] = {16, 12, 8, 4, 0, -4, -8, -12};
s16 D_80180F98[] = {-32, -26, -20, -13, -7, -1, 5, 12};
s16 D_80180FA8[] = {-16, -12, -8, -4, 0, 4, 8, 12};
s16 D_80180FB8[] = {32, 26, 20, 13, 7, 1, -5, -12};
s16 D_80180FC8[] = {-8, 4, -2, 8, 0, 4, -4, 2};
s16 D_80180FD8[] = {-2, 2, 4, -3, 0, 2, -4, 3};

u16 D_80180FE8[] = {
    /* FE8 */ 0x0010,
    /* FEA */ 0x0020,
    /* FEC */ 0x0030,
    /* FEE */ 0x0040,
    /* FF0 */ 0x0050,
    /* FF2 */ 0x0060,
    /* FF4 */ 0x0070,
    /* FF6 */ 0x0000,
};

u16 D_80180FF8[] = {
    /* FF8 */ 0x0030,
    /* FFA */ 0x0050,
    /* FFC */ 0x0080,
    /* FFE */ 0x00B0,
    /* 1000 */ 0x00D0,
    /* 1002 */ 0x0100,
    /* 1004 */ 0x0100,
    /* 1006 */ 0x0000,
};

s32 D_80181008[] = {
    /* 1008 */ 0x00000400,
    /* 100C */ 0x00002400,
    /* 1010 */ 0x00003C00,
    /* 1014 */ 0x00006000,
    /* 1018 */ 0x00007800,
    /* 101C */ 0x0000C000,
};

s32 D_80181020[] = {
    /* 1020 */ 0x00000800,
    /* 1024 */ 0x00002800,
    /* 1028 */ 0x00004800,
    /* 102C */ 0x00007000,
    /* 1030 */ 0x0000E000,
    /* 1034 */ 0x00012000,
};

u8 D_80181038[] = {
    /* 1038 */ 0x01,
    /* 1039 */ 0x09,
    /* 103A */ 0x15,
    /* 103B */ 0x2B,
};

u16 D_8018103C[] = {
    /* 103C */ 0x0010,
    /* 103E */ 0x0018,
    /* 1040 */ 0x002A,
    /* 1042 */ 0x002F,
};

u32 D_80181044[] = {
    /* 1044 */ 0x00000000,
    /* 1048 */ 0x000000FF,
};

u8 D_8018104C[] = {
    2, 1, 2, 2, 2, 3, 2, 4, 2, 5, 4, 6, -1,
};
u16 D_8018105C[] = {0, 1, 3, 4, 1, 2, 4, 5, 3, 4, 6, 7, 4, 5, 7, 8};
u16 D_8018107C[] = {0, 1, 3, 4, 1, 2, 4, 5, 3, 4, 6, 7, 4, 5, 7, 8, 0, 0};

u16 D_801810A0[] = {
    /* 10A0 */ 0x0820,
    /* 10A2 */ 0x0840,
    /* 10A4 */ 0x0860,
    /* 10A6 */ 0x0880,
    /* 10A8 */ 0x08C0,
    /* 10AA */ 0x0900,
    /* 10AC */ 0x0940,
    /* 10AE */ 0x0A00,
};

u16 D_801810B0[] = {
    /* 10B0 */ 0xFFFD,
    /* 10B2 */ 0xFFFD,
    /* 10B4 */ 0x0008,
    /* 10B6 */ 0x0008,
    /* 10B8 */ 0x00D0,
    /* 10BA */ 0x0068,
    /* 10BC */ 0x00D8,
    /* 10BE */ 0x0070,
    /* 10C0 */ 0xFFFD,
    /* 10C2 */ 0xFFFD,
    /* 10C4 */ 0x0008,
    /* 10C6 */ 0x0008,
    /* 10C8 */ 0x00C8,
    /* 10CA */ 0x0068,
    /* 10CC */ 0x00D0,
    /* 10CE */ 0x0070,
    /* 10D0 */ 0xFFF9,
    /* 10D2 */ 0xFFF9,
    /* 10D4 */ 0x0010,
    /* 10D6 */ 0x000F,
    /* 10D8 */ 0x00C8,
    /* 10DA */ 0x0070,
    /* 10DC */ 0x00D8,
    /* 10DE */ 0x007F,
    /* 10E0 */ 0xFFF5,
    /* 10E2 */ 0xFFF5,
    /* 10E4 */ 0x0018,
    /* 10E6 */ 0x0017,
    /* 10E8 */ 0x0080,
    /* 10EA */ 0x0068,
    /* 10EC */ 0x0098,
    /* 10EE */ 0x007F,
    /* 10F0 */ 0xFFF5,
    /* 10F2 */ 0xFFF5,
    /* 10F4 */ 0x0018,
    /* 10F6 */ 0x0017,
    /* 10F8 */ 0x0098,
    /* 10FA */ 0x0068,
    /* 10FC */ 0x00B0,
    /* 10FE */ 0x007F,
    /* 1100 */ 0xFFF5,
    /* 1102 */ 0xFFF5,
    /* 1104 */ 0x0018,
    /* 1106 */ 0x0017,
    /* 1108 */ 0x00B0,
    /* 110A */ 0x0068,
    /* 110C */ 0x00C8,
    /* 110E */ 0x007F,
};

u32 D_80181110[] = {
    /* 1110 */ 0x03030204,
    /* 1114 */ 0x05030403,
    /* 1118 */ 0x03030603,
    /* 111C */ 0x00000000,
    /* 1120 */ 0x00FF0140,
    /* 1124 */ 0x00FF0240,
    /* 1128 */ 0x00FF0240,
    /* 112C */ 0x00FF0140,
    /* 1130 */ 0x00FF0340,
};

ObjInit2 D_80181134[] = {
    {0x0006, 0x01EC, 0x0000, 0x0000, 0x00, 0x00, 0x10, 0x00, 0, 0x80181120},
    {0x000C, 0x01EC, 0x0000, 0x0000, 0x00, 0x00, 0x10, 0x00, 0, 0x80181128},
    {0x000C, 0x0080, 0x0000, 0x0000, 0x00, 0x00, 0x10, 0x00, 0, 0x8018112C},
    {0x0006, 0x01EC, 0x0000, 0x0000, 0x00, 0x00, 0x10, 0x00, 0, 0x80181124},
    {0x000C, 0x01EC, 0x0000, 0x0000, 0x00, 0x00, 0x10, 0x00, 0, 0x80181130},
    {0x000C, 0x0080, 0x0000, 0x0000, 0x00, 0x00, 0x10, 0x00, 0, 0x8018112C},
};

RoomHeader g_stRooms[] = {
    { 40, 12, 40, 12, {0, 0, 0, 1}},
    { 37, 21, 37, 21, {1, 0, 0, 2}},
    { 59, 17, 59, 17, {2, 0, 0, 3}},
    { 15, 38, 15, 38, {3, 0, 0, 4}},
    { 35, 44, 35, 44, {4, 0, 0, 5}},
    { 34, 44, 34, 44, {5, 0, 0, 48}},
    { 16, 38, 16, 38, {6, 0, 0, 49}},
    { 36, 21, 36, 21, {7, 0, 0, 50}},
    { 60, 17, 60, 17, {8, 0, 0, 51}},
    { 39, 12, 39, 12, {9, 0, 0, 52}},
    { 38, 12, 38, 12, {28, -1, 0, 0}},
    { 61, 17, 61, 17, {29, -1, 0, 0}},
    { 35, 21, 35, 21, {30, -1, 0, 0}},
    { 17, 38, 17, 38, {31, -1, 0, 0}},
    { 33, 44, 33, 44, {32, -1, 0, 0}},
    { 64, 0, 0, 0, {-2, -1, -2, -1}},
};

const char D_80186E30[] = "step %x\n";
const char D_80186E3C[] = "move_room%x\n";
const char D_80186E4C[] = "for_x:%x y%x\n";
// gives some padding to align it to the next section
const char D_80186E5C[] = "move_x:%x y%x\n\0\0\0\0\0";
