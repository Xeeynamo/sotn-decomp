#include "stage.h"

extern PfnEntityUpdate PfnEntityUpdates[];
extern bool g_isSecretStairsButtonPressed;

void func_801B3BDC(u16 objectId, Entity *source, Entity *entity);
s32 func_801B4C78();
void MoveEntity();
void func_801B5794(u8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A7D64);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A7E2C);
#else
bool func_801A7E2C(Entity *entity) {
    s16 distance;

    distance = D_800733DA - entity->posX.Data.high;
    if (distance < 0) {
        distance = -distance;
    }
    if (entity->hitboxWidth >= distance) {
        if ((s16)(D_800733DE - entity->posY.Data.high) < 0) {
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

void EntityLockCamera(Entity *entity) {
    s32 temp_v0_2;
    s32 temp_v1;
    u16 *temp_v1_2;
    u16 *temp_v1_5;
    u8 temp_s1;
    u8 temp_v0;
    s32 phi_v1;

    temp_s1 = entity->subId;
    if (entity->initState == 0) {
        InitializeEntity(D_801805B0);
        temp_v1 = temp_s1 & 0xFFFF;
        entity->unk3C = 1;
        temp_v0 = D_80180660[temp_v1];
        entity->unk7C = temp_v0;
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
        if (entity->unk7C) {
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

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A8B9C);

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
    switch (entity->initState) {
    case 0:
        InitializeEntity(D_80180628);
        entity->animationFrame = 3;
        entity->zPriority += 2;
        if (g_isSecretStairsButtonPressed) {
            entity->animationFrame = 0;
            entity->initState = 3;
        }
        break;
    case 1:
        if (g_isSecretStairsButtonPressed) {
            D_8003C7DC(0x644);
            entity->initState++;
        }
        break;
    case 2:
        entity->posY.value -= 0x4000;
        if (entity->posY.Data.high < -16) {
            entity->initState++;
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

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AD430);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AD530);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityDraculaMeteorball);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AD838);

extern u16 D_801805EC[];
extern u8 D_80180A40[];
void EntityDraculaGlass(Entity* entity) {
    switch (entity->initState) {
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
            entity->accelerationX = speed * func_80016D68(radians);
            entity->accelerationY = speed * rsin(radians);
            func_801B5794(3);
        }
    case 1:
        MoveEntity();
        entity->unk1E += 0x20;
        entity->accelerationY += 0x2000;
        if (entity->posY.Data.high >= 205) {
            D_8003C7DC(0x68B);
            entity->posY.Data.high = 204;
            func_801B5794(2);
        }
        break;
    case 2:
        entity->unk19 = 0;
        if (AnimateEntity(D_80180A40, entity) == 0) {
            s32 i;
            for (i = 0; i < 8; i++) {
                Entity *glassShardEntity = AllocEntity(D_8007D858, D_8007D858 + MaxEntityCount);
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

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801ADAC8);

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

u32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B189C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B1B98);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B1CA0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B2A3C);

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

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3BDC);
#else
void func_801B3BDC(u16 objectId, Entity *source, Entity *entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.Data.high = source->posX.Data.high;
    entity->posY.Data.high = source->posY.Data.high;
}
#endif

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3C58);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3CD0);

void DestroyEntity(Entity* item) {
    int i, length;
    u32* ptr;

    if (item->unk34 & 0x800000) {
        D_8003C7B4(item->unk64);
    }

    ptr = item;
    length = sizeof(Entity) / sizeof(s32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4974);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B49F0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", AnimateEntity);
s32 AnimateEntity(u8 *arg0, Entity *entity);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4AF0);

s16 func_801B4C08(void) {
    s16 value = D_8006C3B8->posX.Data.high - D_800733DA;
    if (value < 0) {
        value = -value;
    }
    return value;
}

s32 func_801B4C44(void) {
    s32 value = D_8006C3B8->posY.Data.high - D_800733DE;
    if (value < 0) {
        value = -value;
    }
    return value;
}

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4C78);

void MoveEntity(void) {
    D_8006C3B8->posX.value += D_8006C3B8->accelerationX;
    D_8006C3B8->posY.value += D_8006C3B8->accelerationY;
}

void FallEntity(void) {
    if (D_8006C3B8->accelerationY < FALL_TERMINAL_VELOCITY) {
        D_8006C3B8->accelerationY += FALL_GRAVITY;
    }
}

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4D18);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4D5C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4FD4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B51E4);

Entity *AllocEntity(Entity* start, Entity* end) {
    Entity* current = start;
    while (current < end)
    {
        if (current->objectId == 0)
        {
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

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B568C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B56BC);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B56F4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B573C);

void func_801B5794(u8 state) {
    D_8006C3B8->initState = state;
    D_8006C3B8->unk2E = 0;
    D_8006C3B8->animationFrameIndex = 0;
    D_8006C3B8->animationFrameDuration = 0;
}

void func_801B57B4(u8 arg0) {
    D_8006C3B8->unk2E = arg0;
    D_8006C3B8->animationFrameIndex = 0;
    D_8006C3B8->animationFrameDuration = 0;
}

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B57D0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", InitializeEntity);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5948);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5970);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5A98);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5BF0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5E38);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5EC8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5F4C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B60A8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B615C);

void func_801B61D4(void) {
}

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B61DC);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B6204);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B6314);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B633C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B6358);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityDraculaFireball);
#else
extern u16 D_8018058C[];
extern u32 D_80181D7C[];
extern u16 D_80181E28[][2];

void EntityDraculaFireball(Entity* entity) {
    if (entity->initState == 0) {
        u32 zPriority;

        InitializeEntity(D_8018058C);
        entity->animationSet = 2;
        entity->animationFrameIndex = 0;
        entity->animationFrameDuration = 0;
        entity->unk18 = 0x30;
        
        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->unk18 = 0x10;
        }

        zPriority = entity->subId & 0xFF00;
        if (zPriority != 0) {
            entity->zPriority = zPriority >> 8;
        }

        entity->subId = entity->subId & 0xF;
        entity->accelerationY = D_80181D7C[entity->subId];
    }
    else
    {
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

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8338);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8434);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B89B4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8AB4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8B80);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8C48);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8D00);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8ED8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B94B8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B9BB8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B9DB0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B9EA8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BA23C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BA6EC);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BA7D8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityClouds);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityClockTower3D);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityCutscenePhotograph);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityCutscenePhotographFire);
#else
extern u16 D_801805D4[];
extern u8 D_801824CC[];

void EntityCutscenePhotographFire(Entity* entity) {
    switch (entity->initState) {
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
            entity->unk18 = 0x50;
        } else {
            entity->zPriority = 0x1FE;
            entity->unk18 = 0x30;
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

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD6A4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD72C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD80C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD860);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD88C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD8F0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityBackgroundVortex);
