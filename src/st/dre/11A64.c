/*
 * File: 11A64.c
 * Overlay: DRE
 * Description: Nightmare
 */

#include "stage.h"

void ReplaceBreakableWithItemDrop(Entity* arg0);
void DestroyEntity(Entity* entity);
void func_80198F18(s16);
void func_80199014(s16);
void func_801991CC(s16);
void func_801992C8(s16);
void func_801A046C(u16);
s32 func_8019AC78(u8, s16);
void PreventEntityFromRespawning(Entity* entity);
void FallEntity(void);
void func_8019B858(void);
void SpawnExplosionEntity(u16 objectId, Entity* entity);
Entity* AllocEntity(Entity*, Entity*);
void func_8019A78C(void);
Entity* func_8019AC18(Entity*, Entity*);
void func_8019E5E0(Entity* entity);

extern u16 D_80180494[];
extern s16 D_80180D80[];
extern LayoutObject* D_801A32C4;
extern LayoutObject* D_801A32C8;
extern u16 D_8007308E;
extern u16 D_801804AC[];
extern u16 D_80180470[];
extern s32 D_801811B0[];
extern u32 D_8018125C[];
extern s16 D_801812E4[];
extern u32 D_801812F4[];
extern u8 D_80181338;
extern PfnEntityUpdate D_801803C4[];
extern u16 D_801804E8;
extern u16 D_8018050C;
extern PfnEntityUpdate D_801803C4[];
extern s16 D_801A3EDE;
extern u16 D_801A3EE0;
extern s16 D_801A3EE2;
extern s16 D_801A3EE4;
extern s16 D_801A3EE6;
extern s16 D_801A3EEA;
extern s8 D_801A3EEE;
extern s8 D_801A3EEF;
extern s16 D_801A3F14;
extern s16 D_801A3F16;
extern s32 D_801A3F18;
extern s8 c_HeartPrizes[];
extern s32 D_80180668;
extern u16 D_80180528[];
extern u32 D_8018130C[];
extern u8 D_80181324[];
extern u16 D_80181328[];

void func_80191A64(Entity* entity) {
    ObjInit2* obj = (ObjInit2*)&D_80180528[entity->subId * 10];

    if (entity->step == 0) {
        InitializeEntity(&D_801804AC);
        entity->animationSet = obj->animationSet;
        entity->zPriority = obj->zPriority;
        entity->unk5A = obj->unk4.s;
        entity->palette = obj->palette;
        entity->unk19 = obj->unk8;
        entity->blendMode = obj->blendMode;

        if (obj->unkC != 0) {
            entity->unk34 = obj->unkC;
        }

        if (entity->subId == 1) {
            entity->unk1C = 0x200;
            entity->unk1A = 0x200;
        }
    }

    AnimateEntity(obj->unk10, entity);
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80191B44);

extern u16 g_eBreakableInit[];
extern u8* g_eBreakableAnimations[];
extern u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakableAnimationSets[];
extern u8 g_eBreakableBlendModes[];
void EntityBreakable(Entity* entity) {
    Entity* temp_v0;
    u16 temp_s0 = entity->subId >> 0xC;

    if (entity->step != 0) {
        AnimateEntity(g_eBreakableAnimations[temp_s0], entity);
        if (entity->unk44 != 0) {
            g_api.PlaySfx(NA_SE_BREAK_CANDLE);
            temp_v0 = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (temp_v0 != NULL) {
                SpawnExplosionEntity(2, temp_v0);
                temp_v0->subId = g_eBreakableExplosionTypes[temp_s0];
            }
            ReplaceBreakableWithItemDrop(entity);
        }
    } else {
        InitializeEntity(g_eBreakableInit);
        entity->zPriority = g_zEntityCenter.S16.unk0 - 20;
        entity->blendMode = g_eBreakableBlendModes[temp_s0];
        entity->hitboxHeight = g_eBreakableHitboxes[temp_s0];
        entity->animationSet = g_eBreakableAnimationSets[temp_s0];
    }
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80191E34);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80192104);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80193B3C);

void func_80193D7C(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(&D_801804E8);
    }

    entity->posX.i.hi = entity[-1].posX.i.hi;
    entity->animationFrame = 0;
    entity->posY.i.hi = entity[-1].posY.i.hi;
    entity->facing = entity[-1].facing;

    if (entity[-1].animationFrame == 0x32) {
        entity->animationFrame = 0x3E;
    }

    if (entity[-1].animationFrame == 0x33) {
        entity->animationFrame = 0x3F;
    }

    entity->zPriority = PLAYER.zPriority + 4;
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80193E18);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194214);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194488);

void func_801946C4(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(&D_8018050C);
        entity->animationFrame = 0;
        entity->unk19 = 4;
        entity->unk3C = 0;
    case 1:
        if (entity[-1].animationFrame != 0) {
            entity->unk3C = 1;
            entity->animationFrame = 0x56;
        }
        if (entity->unk48 != 0) {
            D_80180668 = 1;
        }
        if (entity[-1].objectId != 0x1E) {
            DestroyEntity(entity);
        }
    }
}

void func_80194774(void) {
    D_801A3EE4 = 2;
    D_801A3EE2 = 2;
    D_801A3EE6 = 0;
    D_801A3EEA = 0;
    D_801A3EEE = 0;
    D_801A3EEF = 8;
    D_801A3EDE = D_801A3EE0 + 20;
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801947C8);

void func_8019498C(s16 yOffset) {
    RECT rect;

    rect.y = (yOffset * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801949E8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194AA0);

void func_80194C24(s32 arg0) {
    D_801A3F18 = arg0 + 0x100000;
    D_801A3F16 = 0;
    D_801A3F14 = 1;
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194C50);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194F14);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194FF4);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801950F8);

void func_801961DC(s16 arg0) {
    s16 temp_v0 = arg0 - *(s16*)D_8009740C;

    if (temp_v0 > 1) {
        D_8009740C[0]++;
    } else if (temp_v0 < -1) {
        D_8009740C[0]--;
    } else {
        D_8009740C[0] = arg0;
    }
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80196238);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80196678);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019697C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80196CC8);

s32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", UpdateStageEntities);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801972BC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801973C4);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", EntityNumericDamage);

void CreateEntity(Entity* entity, LayoutObject* initDesc) {
    DestroyEntity(entity);
    entity->objectId = initDesc->objectId & 0x3FF;
    do { //! FAKE https://decomp.me/scratch/zysYC
        entity->pfnUpdate = D_801803C4[entity->objectId];
    } while (0);
    entity->posX.i.hi = initDesc->posX - D_8007308E;
    entity->posY.i.hi = initDesc->posY - (u16)D_80073092;
    entity->subId = initDesc->subId;
    entity->objectRoomIndex = initDesc->objectRoomIndex >> 8;
    entity->unk68 = (initDesc->objectId >> 0xA) & 7;
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80198C44);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80198D5C);

void func_80198E74(s16 arg0) {
    while (1) {
        if ((D_801A32C4->posX != 0xFFFE) && ((s32)D_801A32C4->posX >= arg0)) {
            break;
        }

        D_801A32C4++;
    }
}

void func_80198EC0(s16 arg0) {
    while (1) {
        if (D_801A32C4->posX != 0xFFFF) {
            if ((arg0 >= (s32)D_801A32C4->posX) ||
                (D_801A32C4->posX == 0xFFFE)) {
                break;
            }
        }
        D_801A32C4--;
    }
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80198F18);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80199014);

void func_80199128(s16 arg0) {
    while (1) {
        if ((D_801A32C8->posY != 0xFFFE) && ((s32)D_801A32C8->posY >= arg0)) {
            break;
        }

        D_801A32C8++;
    }
}

void func_80199174(s16 arg0) {
    while (1) {
        if (D_801A32C8->posY != 0xFFFF) {
            if (((s32)arg0 >= D_801A32C8->posY) ||
                (D_801A32C8->posY == 0xFFFE)) {
                break;
            }
        }
        D_801A32C8--;
    }
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801991CC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801992C8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801993DC);

void func_80199554(void) {
    Unkstruct8* currentRoomTileLayout = &g_CurrentRoomTileLayout;

    if (D_80097908 != 0) {
        s16 tmp = D_8007308E;
        if (D_80097908 > 0) {
            func_80198F18(tmp + 0x140);
        } else {
            func_80199014(tmp - 0x40);
        }
    }

    if (D_8009790C != 0) {
        s16 tmp = currentRoomTileLayout->unkE;
        if (D_8009790C > 0) {
            func_801991CC(tmp + 0x120);
        } else {
            func_801992C8(tmp - 0x40);
        }
    }
}

void SpawnExplosionEntity(u16 objectId, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = D_801803C4[objectId];
    entity->posX.i.hi = g_CurrentEntity->posX.i.hi;
    entity->posY.i.hi = g_CurrentEntity->posY.i.hi;
}

void func_8019967C(u16 objectId, Entity* source, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = D_801803C4[objectId];
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
}

s32 func_801996F8(Unkstruct5* arg0) {
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

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", EntityRedDoor);

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

s32 AnimateEntity(const u8 frames[], Entity* entity) {
    s32 flag = 0;
    u16 currentFrameIndex = entity->animationFrameIndex * 2;
    u8* currentFrame = frames + currentFrameIndex;

    if (entity->animationFrameDuration == 0) {
        if (currentFrame[0] > 0) {
            flag = 0x80;
            if (currentFrame[0] == 0xFF) {
                return false;
            }

            entity->animationFrameDuration = *currentFrame++;
            entity->animationFrame = *currentFrame++;
            entity->animationFrameIndex++;
        } else {
            currentFrame = frames;
            entity->animationFrameIndex = 0;
            entity->animationFrameDuration = 0;
            entity->animationFrameDuration = *currentFrame++;
            entity->animationFrame = *currentFrame++;
            entity->animationFrameIndex++;
            return false;
        }
    }

    entity->animationFrameDuration = entity->animationFrameDuration - 1;
    entity->animationFrame = currentFrame[-1];
    flag |= true;

    return (u8)flag;
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019A590);

/*
 * Returns the absolute distance from g_CurrentEntity to player in the X Axis
 */
s32 func_8019A6A8(void) {
    s16 xDistance = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (xDistance < 0) {
        xDistance = -xDistance;
    }
    return xDistance;
}

/*
 * Returns the absolute distance from g_CurrentEntity to player in the Y Axis
 */
s32 func_8019A6E4(void) {
    s32 yDistance = g_CurrentEntity->posY.i.hi - PLAYER.posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

s16 func_8019A718(void) {
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

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019A7B8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019AA30);

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

s32 func_8019AC78(u8 arg0, s16 arg1) { return D_80180D80[arg0] * arg1; }

extern s16 D_80180D80[];
s16 func_8019ACA4(u8 arg0) { return D_80180D80[arg0]; }

void func_8019ACC0(s32 arg0, s16 arg1) {
    g_CurrentEntity->accelerationX = func_8019AC78(arg0, arg1);
    g_CurrentEntity->accelerationY = func_8019AC78(arg0 - 0x40, arg1);
}

u8 func_8019AD2C(s16 x, s16 y) { return ((ratan2(y, x) >> 4) + 0x40); }

u8 func_8019AD64(ObjInit2* arg0, ObjInit2* arg1) {
    u16 x, y;

    x = arg1->zPriority - arg0->zPriority;
    y = arg1->palette - arg0->palette;

    return func_8019AD2C(x, y);
}

u8 func_8019ADAC(s16 arg0, s16 arg1) {
    s16 x, y;

    x = arg0 - g_CurrentEntity->posX.i.hi;
    y = arg1 - g_CurrentEntity->posY.i.hi;

    return func_8019AD2C(x, y);
}

u8 func_8019ADF4(u8 arg0, u8 arg1, u8 arg2) {
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

void func_8019AE4C(u16 slope, s16 speed) {
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

u16 func_8019AED8(s16 arg0, s16 arg1) { return ratan2(arg1, arg0); }

u16 func_8019AF08(Entity* a, Entity* b) {
    s32 diffX = b->posX.i.hi - a->posX.i.hi;
    s32 diffY = b->posY.i.hi - a->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_8019AF40(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s16 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_8019AF88(u16 arg0, s16 arg1, s16 arg2) {
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

void func_8019AFE8(u8 step) {
    Entity* entity;

    entity = g_CurrentEntity;
    entity->step = step;
    entity->unk2E = 0;
    entity->animationFrameIndex = 0;
    entity->animationFrameDuration = 0;
}

void func_8019B008(u8 arg0) {
    Entity* entity;

    entity = g_CurrentEntity;
    entity->unk2E = arg0;
    entity->animationFrameIndex = 0;
    entity->animationFrameDuration = 0;
}

void func_8019B024(u16 arg0, u16 arg1) {
    Entity* entity;

    if (arg1 != 0) {
        func_801A046C(arg1);
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
    entity->animationFrame = 0;
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

void func_8019B1B4(Entity* arg0) {
    if (arg0->step == 0) {
        arg0->step++;
    }
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B1DC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B304);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B45C);

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
        entity->animationFrameDuration = 0;
        entity->animationFrameIndex = 0;
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

// This function matches with PSYQ4.0 GCC 2.7.2 with -02 Optimization flag
#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B858);
#else
void func_8019B858(void) {
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

void func_8019B8DC(u16 arg0) {
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

        g_CurrentEntity->posY.i.hi += res.unk18;
        return;
    }

    if (!(res.unk0 & 5)) {
        MoveEntity();
        func_8019B858();
    }
}

void func_8019BA38(u16 arg0) {
    s32* hearts;

    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    hearts = &g_playerHeart;
    *hearts += c_HeartPrizes[arg0];

    if (g_playerHeart->max < *hearts) {
        *hearts = g_playerHeart->max;
    }

    DestroyEntity(g_CurrentEntity);
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019BAB8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019BB94);

void CollectHeartVessel(void) {
    if (g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
        g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
        g_playerHeart->current += HEART_VESSEL_RICHTER;

        if (g_playerHeart->max < g_playerHeart->current) {
            g_playerHeart->current = g_playerHeart->max;
        }
    } else {
        g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
        g_api.func_800FE044(HEART_VESSEL_INCREASE, 0x4000);
    }
    DestroyEntity(g_CurrentEntity);
}

void CollectLifeVessel(void) {
    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_api.func_800FE044(LIFE_VESSEL_INCREASE, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

void func_8019BDA0(void) { DestroyEntity(g_CurrentEntity); }

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", EntityPriceDrop);

void EntityExplosion(Entity* entity) {
    u32 temp_v0;
    u32 temp;

    if (!entity->step) {
        InitializeEntity(&D_80180470);
        entity->animationSet = 2;
        entity->animationFrameIndex = 0;
        entity->animationFrameDuration = 0;
        entity->blendMode = 0x30;

        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->blendMode = 0x10;
        }

        temp_v0 = entity->subId & 0xFF00;

        if (temp_v0 != 0) {
            entity->zPriority = (u16)(temp_v0 >> 8);
        }

        entity->subId &= 0xF;
        entity->accelerationY = D_801811B0[entity->subId];
        return;
    }

    entity->posY.val += entity->accelerationY;
    if (!AnimateEntity(D_8018125C[entity->subId], entity)) {
        DestroyEntity(entity);
    }
}

void func_8019C738(Entity* entity, s32 renderFlags) {
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

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", EntityInventoryDrop);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019CDC4);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", EntityRelicOrb);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", EntityHeartDrop);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019DC6C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E1C8);

void func_8019E2B8(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180494);
        entity->unk8C.modeU16.unk0 = entity->unk80.entityPtr->objectId;
    case 1:
        if (entity->unk7C.U8.unk0++ >= 5) {
            Entity* newEntity =
                AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
            if (newEntity != NULL) {
                func_8019967C(ENTITY_EXPLOSION, entity, newEntity);
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

// https://decomp.me/scratch/lcx4I
INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E3C8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E4F8);

void func_8019E5E0(Entity* entity) {
    u8 new_var2;
    u32 new_var;

    if (!entity->step) {
        new_var = D_8018130C[entity->unk94];
        entity->unk34 = 0x0C002000;
        entity->palette = 0x8195;
        entity->animationSet = 2;
        entity->accelerationY = new_var;
        new_var2 = D_80181324[entity->subId];
        entity->blendMode = 0x10;
        entity->step++;
        entity->animationFrame = new_var2;
        return;
    }

    entity->animationFrameDuration++;
    entity->posY.val -= entity->accelerationY;

    if (!(entity->animationFrameDuration & 1)) {
        entity->animationFrame++;
    }

    if (D_80181328[entity->subId] < entity->animationFrameDuration) {
        DestroyEntity(entity);
    }
}

void func_8019E6D0(Entity* entity) {
    u16 temp_v0;
    u32 temp2;

    if (!entity->step) {
        entity->unk34 = 0x0C002000;
        entity->palette = 0x8195;
        entity->animationSet = 5;
        entity->animationFrame = 1;
        entity->blendMode = 0x10;
        entity->unk19 = 3;
        temp_v0 = D_801812E4[entity->subId];
        entity->unk1A = temp_v0;
        entity->unk1C = temp_v0;
        temp2 = D_801812F4[entity->subId];
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

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E7C4);

bool func_8019E9F4(Unkstruct6* arg0) {
    CollisionResult res;

    FallEntity();
    g_CurrentEntity->posX.val += g_CurrentEntity->accelerationX;
    g_CurrentEntity->posY.val += g_CurrentEntity->accelerationY;

    if (g_CurrentEntity->accelerationY >= 0) {
        s16 posX = g_CurrentEntity->posX.i.hi;
        s16 posY = g_CurrentEntity->posY.i.hi;
        posX += arg0->x;
        posY += arg0->y;

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

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019EAF0);

void EntityIntenseExplosion(Entity* entity) {
    u32 temp_v0;

    if (entity->step == 0) {
        InitializeEntity(D_80180470);
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

void func_8019F170(Entity* entity) {
    if (!entity->step) {
        InitializeEntity(D_80180470);
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

    if (!AnimateEntity(&D_80181338, entity)) {
        DestroyEntity(entity);
    }
}

void func_8019F23C(u16 arg0, Entity* ent1, Entity* ent2) {
    u16 palette;

    DestroyEntity(ent2);

    ent2->objectId = arg0;
    ent2->pfnUpdate = D_801803C4[arg0];
    ent2->posX.i.hi = ent1->posX.i.hi;
    ent2->posY.i.hi = ent1->posY.i.hi;
    ent2->unk5A = ent1->unk5A;
    ent2->zPriority = ent1->zPriority;
    ent2->animationSet = ent1->animationSet;
    ent2->unk34 = -0x32FFE000;
    palette = ent1->palette;

    if (palette & 0x8000) {
        ent2->palette = ent1->unk6A;
    } else {
        ent2->palette = palette;
    }
}

void func_8019F304(void) {
    Entity* entity;
    s8 temp_s4 = Random() & 3;
    s16 temp_s3 = ((Random() & 0xF) << 8) - 0x800;
    s32 i;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (entity != NULL) {
            func_8019967C(2, g_CurrentEntity, entity);
            entity->unk84.U8.unk1 = 6 - i;
            entity->unk80.modeS16.unk0 = temp_s3;
            entity->unk84.U8.unk0 = temp_s4;
        }
    }
}

// https://decomp.me/scratch/Hfk9n
INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019F3BC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019F594);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019FB74);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A0274);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A046C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A0564);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", EntityStageNamePopup);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", EntityAbsorbOrb);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A174C);

extern ObjInit2 D_80181420[];
void EntityRoomForeground(Entity* entity) {
    ObjInit2* objInit = &D_80181420[entity->subId];
    if (entity->step == 0) {
        InitializeEntity(D_801804AC);
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

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A1CE8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2018);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2400);

POLY_GT4* func_801A2550(POLY_GT4* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = (POLY_GT4*)poly->tag;
        } else {
            return poly;
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2580);

// https://decomp.me/scratch/IIvQX a0 -> v0 register swap
#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A25FC);
#else

typedef struct Unkstruct_801A25FC {
    /* 0x00 */ struct Unkstruct_801A25FC* unk0;
    /* 0x04 */ s8 unk4;
    /* 0x05 */ char pad5[0x1];
    /* 0x06 */ s8 unk6;
    /* 0x07 */ s8 unk7;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ UnkUnion2 unk10;
    /* 0x12 */ UnkUnion2 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ UnkUnion2 unk1C;
    /* 0x1E */ UnkUnion2 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s8 unk24;
    /* 0x25 */ s8 unk25;
    /* 0x26 */ char pad26[0x2];
    /* 0x28 */ s8 unk28;
    /* 0x29 */ char pad[0x1];
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ char pad2E[4];
    /* 0x32 */ u16 unk32;
} Unkstruct_801A25FC; // This might be POLY_GT4

Unkstruct_801A25FC* func_801A25FC(Unkstruct_801A25FC* arg0, s32 arg1) {
    s32 i;
    s8 var_a2;

    if (arg0->unk2B != 0) {
        arg0->unk2B = 0;
    } else {
        arg0->unk2B = 1;
    }

    for (i = 0; i < arg1; i++) {
        if (arg0->unk2B != 0) {
            var_a2 = 0;
            arg0->unk32 &= 0xFFF7;
        } else {
            var_a2 = 1;
            arg0->unk32 |= 8;
        }

        if (arg0->unk0 != NULL) {
            arg0->unk2B = var_a2;
        } else {
            return NULL;
        }
    }
    return arg0;
}
#endif

void func_801A2684(POLY_GT4* poly) {
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

void func_801A2764(POLY_GT4* poly) {
    func_801A2684(poly);
    poly->p3 = 8;
    ((POLY_GT4*)poly->tag)->p3 = 1;
    ((POLY_GT4*)poly->tag)->code = 2;
    ((POLY_GT4*)poly->tag)->pad3 = 0xA;
}

void func_801A27B8(POLY_GT4* poly) {
    poly->p3 = 0;
    poly->pad3 = 8;
    ((POLY_GT4*)poly->tag)->p3 = 0;
    ((POLY_GT4*)poly->tag)->code = 4;
    ((POLY_GT4*)poly->tag)->pad3 = 8;
}

s32 func_801A27E4(s32 arg0, u8 arg1) {
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
        } while (((s32)var_v1 < ((s32)var_a0 + 3)));

        var_a0 += 0xC;
    }

    return ret;
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2848);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2A58);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2C9C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2E20);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2F10);
