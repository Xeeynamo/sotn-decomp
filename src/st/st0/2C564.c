#include "st0.h"

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2C564", EntityDracula);

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
        entity->animCurFrame = 0;
        entity->hitboxHeight = 34;
        break;
    case 1:
        entity->facing = entity[-1].facing;
        entity->posX.i.hi = entity[-1].posX.i.hi;
        entity->posY.i.hi = entity[-1].posY.i.hi;
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
        entity->flags |= 0x100;
    }

    if (entity->flags & 0x100) {
        entity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
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
        entity->ext.generic.unk8C.modeU16.unk0 = 0x28;

    case 1:
        AnimateEntity(D_8018097C, entity);
        MoveEntity();
        temp_v0 = entity->ext.generic.unk8C.modeU16.unk0 - 1;
        entity->ext.generic.unk8C.modeU16.unk0 = temp_v0;

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
        entity->objectId = E_EXPLOSION;
        entity->pfnUpdate = EntityExplosion;
        entity->step = 0;
        entity->step_s = 0;
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
        AnimateEntity(D_80180990, entity);
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
                CreateEntityFromEntity(0x1E, entity, newEntity);
                newEntity->zPriority = entity->zPriority + 1;
                randomPosXYIndex = (Random() & 3) * 2;
                newEntity->posX.i.hi =
                    newEntity->posX.i.hi + D_80180A60[randomPosXYIndex];
                newEntity->posY.i.hi =
                    newEntity->posY.i.hi + D_80180A62[randomPosXYIndex];
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
        entity->animCurFrame = 0;
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
        entity->animCurFrame = 0x59;
        entity->unk19 = 4;
        entity->unk3C = 0;
        entity->accelerationX = -0x10000;
        entity->accelerationY = 0;
        if (entity->subId) {
            s16 radians;
            s32 speed;
            entity->animCurFrame = 0x5C;
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
        if (entity->posY.i.hi >= 205) {
            g_api.PlaySfx(NA_SE_BREAK_GLASS);
            entity->posY.i.hi = 204;
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
                    CreateEntityFromEntity(31, entity, glassShardEntity);
                    glassShardEntity->subId = 1;
                }
            }
            DestroyEntity(entity);
        }
        break;
    case 3:
        MoveEntity();
        entity->accelerationY += 0x2000;
        if (entity->posY.i.hi >= 205) {
            DestroyEntity(entity);
        }
        break;
    }
}

bool func_801ADAC8(s32 arg0) {
    s32 unk = 0xD0;
    Entity* entity = g_CurrentEntity;
    s16 temp_v1 = entity->posY.i.hi + arg0;

    if (temp_v1 >= unk) {
        entity->posY.i.hi = unk - temp_v1 + entity->posY.i.hi;
        return true;
    } else {
        return false;
    }
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2C564", func_801ADB10);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2C564", EntityDraculaFinalForm);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2C564", EntityDraculaMegaFireball);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2C564", EntityDraculaRainAttack);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2C564", func_801AF380);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2C564", func_801AF6D0);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2C564", func_801AF774);