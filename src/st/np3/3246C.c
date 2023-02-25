/*
 * File: 3246C.c
 * Overlay: NP3
 * Description: Castle Entrance (After entering Alchemy Laboratory)
 */

#include "np3.h"

void func_801B246C(Entity* self) {
    ObjInit2* temp_s0 = &D_80180C10[self->subId];

    if (self->step == 0) {
        InitializeEntity(D_80180A90);
        self->animSet = temp_s0->animSet;
        self->zPriority = temp_s0->zPriority;
        self->facing = temp_s0->unk4.U8.unk0;
        self->unk5A = temp_s0->unk4.U8.unk1;
        self->palette = temp_s0->palette;
        self->unk19 = temp_s0->unk8;
        self->blendMode = temp_s0->blendMode;
        if (temp_s0->unkC != 0) {
            self->unk34 = temp_s0->unkC;
        }
    }

    AnimateEntity(temp_s0->unk10, self);
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B2540);

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
            g_api.PlaySfx(NA_SE_BREAK_CANDLE);
            entityDropItem =
                AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
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

void func_801B2830(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(&D_80180A60);
        self->unk7C.S8.unk0 = 16;
        self->unk7C.S8.unk1 = 8;
        self->unk7E.modeU8.unk0 = 56;

    case 1:
        D_8003CB25 = self->unk7C.S8.unk0;
        D_8003CB26 = self->unk7C.S8.unk1;
        D_8003CB27 = self->unk7E.modeU8.unk0;
        D_80054319 = self->unk7C.S8.unk0;
        D_8005431A = self->unk7C.S8.unk1;
        D_8005431B = self->unk7E.modeU8.unk0;
        break;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B28E4);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B2C20);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B2F30);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B32A8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B3704);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B39CC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B3D24);

void EntityCavernDoorLever(Entity* entity) {
    s32 posX;
    s32 posY;

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180AA8);
        entity->animCurFrame = 18;
        entity->unk1E = -0x200;
        entity->unk19 |= 4;
        CreateEntityFromEntity(0x1E, entity, &entity[1]);
        if (*D_8003BE1C != 0) {
            entity->unk1E = 0;
        }

    case 1:
        if (entity[1].unk84.S8.unk0 != 0) {
            entity->unk1E += 4;
            if (entity->unk1E > 0) {
                entity->unk1E = 0;
                if (*D_8003BE1C == 0) {
                    g_api.PlaySfx(0x675);
                }
                *D_8003BE1C = 1;
            } else if (!(g_blinkTimer & 0xF)) {
                g_api.PlaySfx(0x675);
            }
        }
        break;
    }

    posX = entity->posX.val;
    posY = entity->posY.val;
    posX += rcos(entity->unk1E) * 0x280;
    posY += rsin(entity->unk1E) * 0x280;
    entity[1].posX.val = posX;
    entity[1].posY.val = posY;
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B4004);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B40F8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B44B4);

// switch that clicks when you step on it
void EntityClickSwitch(Entity* entity) {
    s32 temp_a0 = func_801BD588(entity, 8, 4, 4);
    Entity* player = &PLAYER;

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180AA8);
        entity->animCurFrame = 9;
        entity->zPriority = 0x5E;
        if (*D_8003BE1D != 0) {
            entity->step = 2;
            entity->posY.i.hi += 4;
        }
        break;

    case 1:
        if (temp_a0 != 0) {
            player->posY.i.hi++;
            entity->posY.val += 0xC000;
            if ((D_80073092 + entity->posY.i.hi) > 160) {
                entity->posY.i.hi = 160 - D_80073092;
                g_api.PlaySfx(NA_SE_EV_SWITCH_CLICK);
                *D_8003BE1D = 1;
                entity->step++;
            }
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B4680);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B4940);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityTrapDoor);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B4D60);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B5108);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B5488);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B560C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B5790);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B5C5C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B5DE8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B5E98);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntitySwitch);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B6084);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityUnkId49);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B653C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B65FC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B6990);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B75EC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B7798);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B78BC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B8CC0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B8D84);

void EntityLargeGaibonProjectile(Entity* self) {
    Entity* newEntity;

    if (self->unk34 & 0x100) {
        self->pfnUpdate = EntityExplosion;
        self->objectId = 2;
        self->unk19 = 0;
        self->step = 0;
        self->subId = 1;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(&D_80180B80);
        if (self->subId == 0) {
            self->animSet = 2;
            self->unk19 = 4;
            self->accelerationX = (rcos(self->unk1E) * 0x38000) >> 0xC;
            self->accelerationY = (rsin(self->unk1E) * 0x38000) >> 0xC;
            self->palette = 0x81B6;
            self->unk1E -= 0x400;
        } else {
            self->animSet = 14;
            self->unk5A = 0x79;
            self->unk19 = 0xD;
            self->unk1A = 0x100;
            self->unk6C = 0x80;
            self->palette = 0x81F3;
            self->blendMode = 0x30;
            self->step = 2;
            self->unk3C = 0;
            self->unk34 |= 0x2000;
        }
        break;

    case 1:
        MoveEntity();
        AnimateEntity(&D_801815EC, self);
        if (!(g_blinkTimer & 3)) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x54, self, newEntity);
                newEntity->subId = 1;
                newEntity->unk1E = self->unk1E;
                newEntity->zPriority = self->zPriority + 1;
            }
        }
        break;

    case 2:
        self->unk6C += 0xFE;
        self->unk1A -= 4;
        if (AnimateEntity(&D_801815FC, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B90BC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", Update);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B93E8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B94F0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityNumericDamage);

void CreateEntityFromLayout(Entity* entity, LayoutObject* initDesc) {
    DestroyEntity(entity);
    entity->objectId = initDesc->objectId & 0x3FF;
    do {
        entity->pfnUpdate = PfnEntityUpdates[entity->objectId];
    } while (0);
    entity->posX.i.hi = initDesc->posX - D_8007308E;
    entity->posY.i.hi = initDesc->posY - D_80073092;
    entity->subId = initDesc->subId;
    entity->objectRoomIndex = initDesc->objectRoomIndex >> 8;
    entity->unk68 = (initDesc->objectId >> 0xA) & 7;
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BAD70);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BAE88);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BAFA0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BAFEC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BB044);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BB140);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BB254);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BB2A0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BB2F8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BB3F4);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", InitRoomEntities);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BB680);

void CreateEntityFromCurrentEntity(u16 objectId, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.i.hi = g_CurrentEntity->posX.i.hi;
    entity->posY.i.hi = g_CurrentEntity->posY.i.hi;
}

void CreateEntityFromEntity(u16 objectId, Entity* source, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
}

s32 func_801BB824(Unkstruct5* arg0) {
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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityRedDoor);

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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BC6BC);

s32 func_801BC7D4(void) {
    s16 yDistance = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

s32 func_801BC810(void) {
    s32 yDistance = g_CurrentEntity->posY.i.hi - PLAYER.posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

s16 func_801BC844(void) {
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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", FallEntity);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BC8E4);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BCB5C);

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

s32 func_801BCDA4(u8 arg0, s16 arg1) { return D_80181A50[arg0] * arg1; }

s16 func_801BCDD0(u8 arg0) { return D_80181A50[arg0]; }

void func_801BCDEC(s32 arg0, s16 arg1) {
    g_CurrentEntity->accelerationX = func_801BCDA4(arg0, arg1);
    g_CurrentEntity->accelerationY = func_801BCDA4(arg0 - 0x40, arg1);
}

u8 func_801BCE58(s16 x, s16 y) { return ((ratan2(y, x) >> 4) + 0x40); }

u8 func_801BCE90(Entity* a, Entity* b) {
    s32 diffX = (u16)b->posX.i.hi - (u16)a->posX.i.hi;
    s32 diffY = (u16)b->posY.i.hi - (u16)a->posY.i.hi;
    return func_801BCE58(diffX, diffY);
}

u8 func_801BCED8(s32 x, s32 y) {
    s32 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s32 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return func_801BCE58(diffX, diffY);
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BCF20);

void func_801BCF78(u16 slope, s16 speed) {
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

u16 func_801BD004(s16 x, s16 y) { return ratan2(y, x); }

u16 func_801BD034(Entity* a, Entity* b) {
    s32 diffX = b->posX.i.hi - a->posX.i.hi;
    s32 diffY = b->posY.i.hi - a->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_801BD06C(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s16 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return ratan2(diffY, diffX);
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BD0B4);

void func_801BD114(u8 step) {
    g_CurrentEntity->step = step;
    g_CurrentEntity->unk2E = 0;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

void func_801BD134(u8 arg0) {
    g_CurrentEntity->unk2E = arg0;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BD150);

void InitializeEntity(u16 arg0[]) {
    u16 temp_v1;
    Unkstruct5* temp_v0;

    g_CurrentEntity->animSet = *arg0++;
    g_CurrentEntity->animCurFrame = *arg0++;
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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BD308);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BD430);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BD588);

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
    temp_a0 = 0;
    entity->unk6D = 0x10;
    entity->step = temp_a0;
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BD984);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BDA08);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BDB64);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BDBE4);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BDCC0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BDDD8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BDE7C);

void func_801BDECC(void) { DestroyEntity(g_CurrentEntity); }

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityPriceDrop);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityExplosion);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BE864);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityInventoryDrop);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801BEEF0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityRelicOrb);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityHeartDrop);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityUnkId0E);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C02F4);

void func_801C03E4(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180A78);
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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C04F4);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C0624);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C070C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C07FC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C08F0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C0B20);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C0C1C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityIntenseExplosion);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C129C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C1368);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C1430);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C14E8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C16C0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C1CA0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C23A0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C2598);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C2690);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityStageNamePopup);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityAbsorbOrb);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityEnemyBlood);

extern ObjInit2 D_801820F0[];
void EntityRoomForeground(Entity* entity) {
    ObjInit2* objInit = &D_801820F0[entity->subId];

    if (entity->step == 0) {
        InitializeEntity(D_80180A90);
        entity->animSet = objInit->animSet;
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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C3E14);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C4144);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C424C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C4DCC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C56D8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C5BC4);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C5F58);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C61B4);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C6458);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C6564);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C7650);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C7880);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C7954);

void func_801C7D80(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(&D_80180AB4);
        self->animCurFrame = 0;
        self->unk3C = 0;
        self->unk34 |= 0x2000;
        self->zPriority += 4;
    }
    MoveEntity();
    self->accelerationY += 0x2800;
    if (AnimateEntity(&D_801822B8, self) == 0) {
        DestroyEntity(self);
    }
}

void func_801C7E18(Entity* self) {
    s8 temp; // probably !FAKE

    switch (self->step) {
    case 0:
        InitializeEntity(&D_80180A54);
        self->animSet = 2;
        self->accelerationY = -0x50000;
        self->palette = 0x8162;
        self->blendMode = 0x10;
        self->palette = 0x8018;
        self->blendMode = 0x30;
        self->unk6C = 0xA0;
        self->unk1A = 0x100;
        self->unk1C = 0x1A0;
        self->unk19 |= 3;
        self->unk84.S8.unk1 = 0x11;
        self->unk84.S8.unk0 = *(s8*)&self->subId; // wtf
        self->unk19 |= 8;
        break;

    case 1:
        temp = self->unk84.S8.unk0 - 1;
        self->unk84.S8.unk0--;
        self->unk84.S8.unk1--;
        if (!(temp & 0xFF)) {
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(&D_801822C0, self);
        MoveEntity();
        self->accelerationY += 0x4000;
        self->unk1A += 6;
        self->unk1C -= 4;
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
        }
        if (!--self->unk84.U8.unk1) {
            self->accelerationY = 0;
            self->step++;
        }
        break;

    case 3:
        if (AnimateEntity(&D_801822C0, self) == 0) {
            MoveEntity();
            self->accelerationY += 0x4000;
            self->unk1A += 6;
            self->unk1C -= 4;
        }
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntityLargeFallingObject(Entity* self) {
    u8 temp_v0;

    if (self->step == 0) {
        InitializeEntity(&D_80180AB4);
        self->animCurFrame = 13;
        self->unk84.S8.unk0 = 0x20;
        self->unk3C = 0;
        self->accelerationY = 0x1000;
        self->palette = self->subId + 0xE;
        self->unk6C = 0x80;
        self->unk19 |= 8;
        self->unk34 |= 0x2000;
        return;
    }
    MoveEntity();
    temp_v0 = self->unk84.U8.unk0 - 1;
    self->unk84.U8.unk0--;
    self->accelerationY += 0x1000;
    self->unk6C += 0xFE;
    if (temp_v0 == 0) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityMerman2);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityMerman);

void func_801C8DF0(Entity* self) {
    Entity* entity;

    if (self->step == 0) {
        InitializeEntity(&D_80180AD8);
        self->hitboxWidth = 6;
        self->animCurFrame = 0;
        self->hitboxHeight = 3;

        if (self->facing != 0) {
            self->accelerationX = 0x10000 | 0x8000;
        } else {
            self->accelerationX = 0xFFFE0000 | 0x8000;
        }

        self->unk19 = 3;
        self->unk1C = self->unk1A = 0x80;

        entity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (entity != NULL) {
            CreateEntityFromEntity(ENTITY_15, self, entity);
            entity->unk94 = 4;
            entity->unk19 = 3;
            entity->zPriority = self->zPriority + 8;
            entity->unk1C = entity->unk1A = 192;
        }
    } else {
        AnimateEntity(&D_80182400, self);
        MoveEntity();

        if (self->unk1A < 0x100) {
            self->unk1C = self->unk1A += 8;
        }

        if (self->unk34 & 0x100) {
            entity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (entity != NULL) {
                CreateEntityFromEntity(2, self, entity);
                entity->subId = 0;
            }
            DestroyEntity(self);
        }
    }
}

// some kind of falling object
void func_801C8F54(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(&D_80180ACC);
        self->animCurFrame = 0;
        self->unk3C = 0;
        self->zPriority += 4;
        self->unk34 |= 0x2000;
    }
    MoveEntity();
    self->accelerationY += 0x2800;
    if (AnimateEntity(&D_80182414, self) == 0) {
        DestroyEntity(self);
    }
}

void EntityMermanExplosion(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(&D_80180A54);
        self->palette = 0x82BB;
        self->animSet = 2;
        self->animCurFrame = D_80182454[self->subId];
        self->accelerationY = D_80182440[self->subId];
        self->step++;
        return;
    } else {
        self->animFrameDuration++;
        self->posY.val += self->accelerationY;
    }

    if (!(self->animFrameDuration & 1)) {
        self->animCurFrame++;
    }

    if (D_80182458[self->subId] < self->animFrameDuration) {
        DestroyEntity(self);
    }
}

void func_801C90E8(void) {
    s32 temp = func_801BCB5C(&D_80182540);
    s16 temp2 = func_801BD308(&D_80182548, 3);

    if ((temp == 128) || (temp2 & 2)) {
        func_801BD114(5);
        return;
    }
    if ((g_CurrentEntity->unk7C.U8.unk0) == 0) {
        if (func_801BC7D4() < 64) {
            if (g_CurrentEntity->facing != (func_801BC844() & 1)) {
                func_801BD114(4);
            }
        }
    } else {
        g_CurrentEntity->unk7C.S8.unk0--;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityBoneScimitar);

// debris that rotates and falls down
void EntityFallingDebris(Entity* entity) {
    if (entity->step) {
        entity->unk88.S8.unk0--;
        if (entity->unk88.S8.unk0 & 0xFF) {
            entity->unk1E += D_801824B8[entity->subId];
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
    InitializeEntity(&D_80180AF0);
    entity->unk19 = 4;
    entity->animCurFrame = *(u8*)&entity->subId + 16;

    if (entity->facing != 0) {
        entity->accelerationX = -entity->accelerationX;
    }

    if (entity->subId & 0xF00) {
        entity->palette += entity->subId / 256;
    }
}
