/*
 * File: 27D64.c
 * Overlay: ST0
 * Description: Final Stage: Bloodletting
 */

#include "stage.h"

extern PfnEntityUpdate PfnEntityUpdates[];
extern bool g_isSecretStairsButtonPressed;
extern bool g_isDraculaFirstFormDefeated;

void func_801B3BDC(u16 objectId, Entity* source, Entity* entity);
s16 func_801B4C78();
void MoveEntity();
void func_801B5794(u8);
void func_801B6B60(Entity*);

extern u16 D_801805BC[];
extern ObjInit2 D_80180638[];
void func_801A7D64(Entity* arg0) {
    s32 temp_v0;
    ObjInit2* temp_s0 = &D_80180638[arg0->subId];

    if (arg0->step == 0) {
        InitializeEntity(D_801805BC);
        arg0->animationSet = temp_s0->animationSet;
        arg0->zPriority = temp_s0->zPriority;
        arg0->unk5A = temp_s0->unk4.data;
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

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A7E2C);
#else
bool func_801A7E2C(Entity* entity) {
    Entity* player = GET_PLAYER(g_EntityArray);
    s16 distance;

    distance = PLAYER.posX.Data.high - entity->posX.Data.high;
    if (distance < 0) {
        distance = -distance;
    }
    if (entity->hitboxWidth >= distance) {
        if ((s16)(g_EntityArray[PLAYER_CHARACTER].posY.Data.high -
                  entity->posY.Data.high) < 0) {
            return true;
        }
    }

    return false;
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityLockCamera);
#else
extern u16 D_801805B0[];
extern u8 D_8018065C[];
extern u8 D_80180660[];
extern u16 D_80180664[];

bool func_801A7E2C(Entity* entity);
void EntityLockCamera(Entity* entity) {
    s32 temp_v0_2;
    s32 temp_v1;
    u16* temp_v1_2;
    u16* temp_v1_5;
    u8 temp_s1;
    u8 temp_v0;
    s32 phi_v1;

    temp_s1 = entity->subId;
    if (entity->step == 0) {
        InitializeEntity(D_801805B0);
        temp_v1 = temp_s1 & 0xFFFF;
        entity->unk3C = 1;
        temp_v0 = D_80180660[temp_v1];
        entity->unk7C.modeU16 = temp_v0;
        if (temp_v0) {
            entity->hitboxWidth = D_8018065C[temp_v1];
            entity->hitboxHeight = 20;
        } else {
            entity->hitboxWidth = 20;
            entity->hitboxHeight = D_8018065C[temp_v1];
        }
    }

    if (entity->subId & 0x100) {
        temp_v1_2 = &D_80180664[(((temp_s1 & 0xFFFF) * 4) & 0xFFFF)];
        g_CurrentRoomX = *temp_v1_2++;
        g_CurrentRoomY = *temp_v1_2++;
        g_CurrentRoomWidth = *temp_v1_2++;
        g_CurrentRoomHeight = *temp_v1_2++;
        DestroyEntity(entity);
        return;
    }

    if (func_801A7E2C(entity)) {
        temp_v0_2 = func_801B4C78();
        if (entity->unk7C.modeU16) {
            phi_v1 = (temp_v0_2 & 2) * 2;
        } else {
            phi_v1 = (temp_v0_2 & 1) * 4;
        }

        temp_v1_5 = &D_80180664[(phi_v1 + temp_s1 * 8) & 0xFFFF];
        g_CurrentRoomX = *temp_v1_5++;
        g_CurrentRoomY = *temp_v1_5++;
        g_CurrentRoomWidth = *temp_v1_5++;
        g_CurrentRoomHeight = *temp_v1_5++;
    }
}
#endif

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A805C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A8328);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A8620);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A8984);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A89D8);

void func_801A8B9C(s16 yOffset) {
    RECT rect;

    rect.y = (yOffset * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A8BF8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A8CB0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A8E34);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A8E60);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A910C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityDialogue);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AA218);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityCutscene);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntitySecretButton);

extern u16 D_80180628[];
void EntitySecretStairsEmitter(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180628);
        entity->animationFrame = 3;
        entity->zPriority += 2;
        if (g_isSecretStairsButtonPressed) {
            entity->animationFrame = 0;
            entity->step = 3;
        }
        break;
    case 1:
        if (g_isSecretStairsButtonPressed) {
            g_pfnPlaySfx(NA_SE_SECRET_STAIRS);
            entity->step++;
        }
        break;
    case 2:
        entity->posY.value -= 0x4000;
        if (entity->posY.Data.high < -16) {
            entity->step++;
        }
        break;
    case 3:
        entity->animationFrame = 0;
        break;
    }
}

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntitySecretStairsChunk);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityStageTitleFadeout);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityStageTitleCard);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801ABBBC);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AC458);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityDracula);

extern u16 D_801805E0[];
void EntityDraculaBody(Entity* entity) {
    if (g_isDraculaFirstFormDefeated) {
        DestroyEntity(entity);
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(D_801805E0);
        entity->unk3C = 1;
        entity->hitPoints = 0x7FFF;
        entity->unk10 = 3;
        entity->unk12 = 0x27;
        entity->hitboxWidth = 12;
        entity->animationFrame = 0;
        entity->hitboxHeight = 34;
        break;
    case 1:
        entity->facing = entity[-1].facing;
        entity->posX.Data.high = entity[-1].posX.Data.high;
        entity->posY.Data.high = entity[-1].posY.Data.high;
        entity->unk3C = entity[-1].unk3C & 0xFFFD;
        break;
    case 2:
        entity->unk3C = 0;
        break;
    }

    if (g_isDraculaFirstFormDefeated) {
        entity->unk3C = 0;
    }
}

extern u16 D_801805EC[];
extern u8 D_8018097C[];
void EntityDraculaFireball(Entity* entity) {
    u16 temp_v0;

    if (g_isDraculaFirstFormDefeated) {
        entity->unk34 |= 0x100;
    }

    if (entity->unk34 & 0x100) {
        entity->pfnUpdate = (PfnEntityUpdate)func_801B6B60;
        entity->step = 0;
        entity->subId = 2;
        return;
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(D_801805EC);

        if (entity->facing == 0) {
            entity->accelerationX = -0x20000;
        } else {
            entity->accelerationX = 0x20000;
        }

        if (entity->subId == 1) {
            entity->accelerationY = -0x8000;
        }

        if (entity->subId == 2) {
            entity->accelerationY = 0x8000;
        }
        entity->unk8C.modeU16.unk0 = 0x28;

    case 1:
        AnimateEntity(D_8018097C, entity);
        MoveEntity();
        temp_v0 = entity->unk8C.modeU16.unk0 - 1;
        entity->unk8C.modeU16.unk0 = temp_v0;

        if ((temp_v0 << 0x10) == 0) {
            entity->accelerationY = 0;
        }
        return;
    }
}

extern u16 D_801805F8[];
extern u8 D_80180990[];
extern u8 D_801809B0[];
extern s16 D_80180A60[];
extern s16 D_80180A62[];
void EntityDraculaMeteorball(Entity* entity) {
    s32 speedX;

    if (g_isDraculaFirstFormDefeated) {
        entity->objectId = ENTITY_EXPLOSION;
        entity->pfnUpdate = func_801B6B60;
        entity->step = 0;
        entity->unk2E = 0;
        entity->subId = 1;
        return;
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(D_801805F8);
        entity->unk3C = 0;
        entity->unk19 |= 4;
        break;
    case 1:
        if (AnimateEntity(D_801809B0, entity) == 0) {
            entity->unk3C = 1;
            func_801B5794(2);
        }
        break;
    case 2:
        AnimateEntity(&D_80180990, entity);
        MoveEntity();
        entity->unk1E += 4;
        speedX = 0x1000;
        if (entity->subId != 0) {
            speedX = 0xE00;
        }

        if (entity->facing != 0) {
            entity->accelerationX += speedX;
        } else {
            entity->accelerationX -= speedX;
        }

        if (!(g_blinkTimer & 3)) { // lolwut?
            Entity* newEntity = AllocEntity(D_8007D858, D_8007D858 + 0x20);
            if (newEntity != 0) {
                s32 randomPosXYIndex;
                func_801B3BDC(0x1E, entity, newEntity);
                newEntity->zPriority = entity->zPriority + 1;
                randomPosXYIndex = (Random() & 3) * 2;
                newEntity->posX.Data.high =
                    newEntity->posX.Data.high + D_80180A60[randomPosXYIndex];
                newEntity->posY.Data.high =
                    newEntity->posY.Data.high + D_80180A62[randomPosXYIndex];
            }
        }
        break;
    }
}

extern u16 D_801805EC[];
extern u8 D_801809E0[];
void func_801AD838(Entity* entity) {
    if (g_isDraculaFirstFormDefeated) {
        DestroyEntity(entity);
        return;
    }

    if (entity->step == 0) {
        InitializeEntity(D_801805EC);
        entity->animationFrame = 0;
        entity->unk3C = 0;
        entity->accelerationY = -0x10000;
    }
    MoveEntity();

    if (AnimateEntity(D_801809E0, entity) == 0) {
        DestroyEntity(entity);
    }
}

extern u16 D_801805EC[];
extern u8 D_80180A40[];
void EntityDraculaGlass(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_801805EC);
        entity->animationFrame = 0x59;
        entity->unk19 = 4;
        entity->unk3C = 0;
        entity->accelerationX = -0x10000;
        entity->accelerationY = 0;
        if (entity->subId) {
            s16 radians;
            s32 speed;
            entity->animationFrame = 0x5C;
            speed = (Random() & 0x1F) + 0x10;
            radians = (Random() * 6) + 0x900;
            entity->accelerationX = speed * rcos(radians);
            entity->accelerationY = speed * rsin(radians);
            func_801B5794(3);
        }
    case 1:
        MoveEntity();
        entity->unk1E += 0x20;
        entity->accelerationY += 0x2000;
        if (entity->posY.Data.high >= 205) {
            g_pfnPlaySfx(NA_SE_BREAK_GLASS);
            entity->posY.Data.high = 204;
            func_801B5794(2);
        }
        break;
    case 2:
        entity->unk19 = 0;
        if (AnimateEntity(D_80180A40, entity) == 0) {
            s32 i;
            for (i = 0; i < 8; i++) {
                Entity* glassShardEntity =
                    AllocEntity(D_8007D858, D_8007D858 + MaxEntityCount);
                if (glassShardEntity != 0) {
                    func_801B3BDC(31, entity, glassShardEntity);
                    glassShardEntity->subId = 1;
                }
            }
            DestroyEntity(entity);
        }
        break;
    case 3:
        MoveEntity();
        entity->accelerationY += 0x2000;
        if (entity->posY.Data.high >= 205) {
            DestroyEntity(entity);
        }
        break;
    }
}

bool func_801ADAC8(s32 arg0) {
    s32 unk = 0xD0;
    Entity* entity = g_CurrentEntity;
    s16 temp_v1 = entity->posY.Data.high + arg0;

    if (temp_v1 >= unk) {
        entity->posY.Data.high = unk - temp_v1 + entity->posY.Data.high;
        return true;
    } else {
        return false;
    }
}

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801ADB10);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityDraculaFinalForm);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityDraculaMegaFireball);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityDraculaRainAttack);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AF380);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AF6D0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AF774);

void func_801B0030(s32 arg0) {
    D_8003C734 = arg0;
    D_80073060 = 0;
    g_backbufferX = 0;
    g_backbufferY = 0;
}

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B0058);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B0180);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B01C0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B01F8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B0280);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B0324);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B0414);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B0464);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B101C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B1198);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B11E8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B1298);

s32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", UpdateStageEntities);
#else
extern s16 D_801815EC[];
extern u16 D_801C2584[];

void UpdateStageEntities(void) {
    s16 i;
    Entity* entity;
    s32* unk;

    for (i = 0; i < 0x20; i++) {
        if (D_801C2584[i]) {
            D_801C2584[i]--;
        }
    }

    unk = &D_80097410;
    if (*unk) {
        if (!--*unk) {
            D_8003C7B4(D_80097414);
        }
    }

    for (entity = D_800762D8; entity < &D_8007EFD8; entity++) {
        if (!entity->pfnUpdate)
            continue;

        if (entity->step) {
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
                    D_801815EC[(entity->unk49 << 1) | (unk34 & 1)];
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
#endif

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B1B98);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B1CA0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityNumericDamage);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", CreateEntity);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B31A4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B32BC);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B33D4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3420);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3478);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3574);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3688);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B36D4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B372C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3828);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B393C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3AB4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3B68);

void func_801B3BDC(u16 objectId, Entity* source, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.Data.high = source->posX.Data.high;
    entity->posY.Data.high = source->posY.Data.high;
}

s32 func_801B3C58(Unkstruct5* arg0) {
    Entity* player = GET_PLAYER(g_EntityArray);
    s16 diff;

    diff = PLAYER.posX.Data.high - arg0->unk2;
    diff = ABS_ALT(diff);

    if (diff >= 17) {
        diff = 0;
    } else {
        diff = PLAYER.posY.Data.high - arg0->unk6;
        diff = ABS_ALT(diff);
        diff = diff < 33;
    }

    return diff;
}

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityRedDoor);

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

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4AF0);

/*
 * Returns the absolute distance from g_CurrentEntity to player in the X Axis
 */
s16 func_801B4C08(void) {
    Entity* player = GET_PLAYER(g_EntityArray);
    s16 xDistance = g_CurrentEntity->posX.Data.high - PLAYER.posX.Data.high;

    if (xDistance < 0) {
        xDistance = -xDistance;
    }
    return xDistance;
}

/*
 * Returns the absolute distance from g_CurrentEntity to player in the Y Axis
 */
s32 func_801B4C44(void) {
    Entity* player = GET_PLAYER(g_EntityArray);
    s32 yDistance = g_CurrentEntity->posY.Data.high - PLAYER.posY.Data.high;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

s16 func_801B4C78(void) {
    Entity* player = GET_PLAYER(g_EntityArray);
    s16 var_a0 = g_CurrentEntity->posX.Data.high > PLAYER.posX.Data.high;

    if (g_CurrentEntity->posY.Data.high > PLAYER.posY.Data.high) {
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

u8 func_801B4D18(void) {
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

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4D5C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4FD4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B51E4);

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

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B542C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5458);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5474);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B54E0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5518);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5560);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B55A8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5600);

u16 func_801B568C(s16 x, s16 y) { return ratan2(y, x); }

u16 func_801B56BC(Entity* a, Entity* b) {
    s32 diffX = b->posX.Data.high - a->posX.Data.high;
    s32 diffY = b->posY.Data.high - a->posY.Data.high;
    return ratan2(diffY, diffX);
}

u16 func_801B56F4(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.Data.high;
    s16 diffY = y - (u16)g_CurrentEntity->posY.Data.high;
    return ratan2(diffY, diffX);
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B573C);
#else
// very minor reg swap
u16 func_801B573C(u16 arg0, s16 arg1, s16 arg2) {
    u16 temp_a2 = arg2 - arg1;
    u16 var_v0 = arg1;
    u16 var_v0_2;

    if (temp_a2 & 0x800) {
        var_v0_2 = temp_a2 & 0x7FF;
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
#endif

void func_801B5794(u8 state) {
    g_CurrentEntity->step = state;
    g_CurrentEntity->unk2E = 0;
    g_CurrentEntity->animationFrameIndex = 0;
    g_CurrentEntity->animationFrameDuration = 0;
}

void func_801B57B4(u8 arg0) {
    g_CurrentEntity->unk2E = arg0;
    g_CurrentEntity->animationFrameIndex = 0;
    g_CurrentEntity->animationFrameDuration = 0;
}

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B57D0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", InitializeEntity);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityDummy);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5970);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5A98);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5BF0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5E38);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5EC8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5F4C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B60A8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B615C);

void func_801B61D4(void) {}

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B61DC);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B6204);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B6314);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B633C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B6358);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B6B60);
void func_801B6B60(Entity* entity);
#else
extern u16 D_8018058C[];
extern u32 D_80181D7C[];
extern u16 D_80181E28[][2];

void func_801B6B60(Entity* entity) {
    if (entity->step == 0) {
        u32 zPriority;

        InitializeEntity(D_8018058C);
        entity->animationSet = 2;
        entity->animationFrameIndex = 0;
        entity->animationFrameDuration = 0;
        entity->blendMode = 0x30;

        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->blendMode = 0x10;
        }

        zPriority = entity->subId & 0xFF00;
        if (zPriority != 0) {
            entity->zPriority = zPriority >> 8;
        }

        entity->subId = entity->subId & 0xF;
        entity->accelerationY = D_80181D7C[entity->subId];
    } else {
        s32 posY = entity->posY.value;
        posY += entity->accelerationY;
        entity->posY.value = posY;
        if (!AnimateEntity(D_80181E28 + entity->subId, entity)) {
            DestroyEntity(entity);
        }
    }
}
#endif

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B6C5C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B6D34);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B7308);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B7B0C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B7BFC);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B7D0C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B7E3C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B7F24);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8014);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8108);

bool func_801B8338(Unkstruct6* unk) {
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

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8434);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityIntenseExplosion);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8AB4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8B80);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8C48);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8D00);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8ED8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B94B8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B9BB8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B9DB0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityAbsorbOrb);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BA23C);

extern ObjInit2 D_80181FE8[];
void EntityRoomForeground(Entity* entity) {
    ObjInit2* objInit = &D_80181FE8[entity->subId];
    if (entity->step == 0) {
        InitializeEntity(D_801805BC);
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

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BA7D8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityClouds);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityClockTower3D);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityCutscenePhotograph);

#ifndef NON_MATCHING // TODO fix 'li' opcode with ASPATCH
INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityCutscenePhotographFire);
#else
extern u16 D_801805D4[];
extern u8 D_801824CC[];

void EntityCutscenePhotographFire(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_801805D4);
        entity->animationSet = 0x8007;
        entity->unk5A = 0x57;
        entity->palette = 0x8285;
        entity->unk19 = 8;
        entity->unk6C = 0x40;
        entity->unk34 &= 0xF7FFFFFF;
        if (entity->subId) {
            entity->unk6C = 0x10;
            entity->zPriority = 0x1FB;
            entity->blendMode = 0x50;
        } else {
            entity->zPriority = 0x1FE;
            entity->blendMode = 0x30;
        }
    case 1:
        entity->posY.value -= 0x10000;
        if (AnimateEntity(D_801824CC, entity) == 0) {
            DestroyEntity(entity);
        }
        break;
    }
}
#endif

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BC5C0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD0C0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD4A8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD5F8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD628);

POLY_GT4* func_801BD6A4(POLY_GT4* startPoly, s32 count) {
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

void func_801BD72C(POLY_GT4* arg0) {
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

void func_801BD80C(POLY_GT4* arg0) {
    func_801BD72C(arg0);
    arg0->p3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 1;
    ((POLY_GT4*)arg0->tag)->code = 2;
    ((POLY_GT4*)arg0->tag)->pad3 = 0xA;
}

void func_801BD860(POLY_GT4* arg0) {
    arg0->p3 = 0;
    arg0->pad3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 0;
    ((POLY_GT4*)arg0->tag)->code = 4;
    ((POLY_GT4*)arg0->tag)->pad3 = 8;
}

s32 func_801BD88C(s32 arg0, u8 arg1) {
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

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD8F0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityBackgroundVortex);
