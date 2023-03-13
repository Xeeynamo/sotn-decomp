/*
 * File: 377D4.c
 * Overlay: NO3
 * Description: Castle Entrance
 */

#include "no3.h"

// vase in the room with the door to the caverns
void EntityCavernDoorVase(Entity* arg0) {
    s32 temp_v0;
    ObjInit2* temp_s0 = &D_80180BFC[arg0->subId];

    if (arg0->step == 0) {
        InitializeEntity(D_80180B00);
        arg0->animSet = temp_s0->animSet;
        arg0->zPriority = temp_s0->zPriority;
        arg0->facing = temp_s0->unk4.U8.unk0;
        arg0->unk5A = temp_s0->unk4.U8.unk1;
        arg0->palette = temp_s0->palette;
        arg0->unk19 = temp_s0->unk8;
        arg0->blendMode = temp_s0->blendMode;
        temp_v0 = temp_s0->unkC;
        if (temp_v0 != 0) {
            arg0->flags = temp_v0;
        }
    }

    AnimateEntity(temp_s0->unk10, arg0);
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityUnkId12);

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

void EntityUnkId16(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(&D_80180AD0);
        self->unk7C.S8.unk0 = 16;
        self->unk7C.S8.unk1 = 8;
        self->unk7E.modeU8.unk0 = 56;

    case 1:
        D_8003CB08.buf.draw.r0 = self->unk7C.S8.unk0;
        D_8003CB08.buf.draw.g0 = self->unk7C.S8.unk1;
        D_8003CB08.buf.draw.b0 = self->unk7E.modeU8.unk0;
        D_800542FC.buf.draw.r0 = self->unk7C.S8.unk0;
        D_800542FC.buf.draw.g0 = self->unk7C.S8.unk1;
        D_800542FC.buf.draw.b0 = self->unk7E.modeU8.unk0;
        break;
    }
}

// lightning and sound for background
INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityBackgroundLightning);

// window that opens and shuts in the background
INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityShuttingWindow);

// main door to the castle that closes during intro
INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityCastleDoor);

// bushes in parallax background
INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityBackgroundBushes);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityUnkId1C);

// transparent water "plane" seen in the merman room
INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityTransparentWater);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", func_801B94F0);

// lever and platform to open caverns door
void EntityCavernDoorLever(Entity* entity) {
    s32 posX;
    s32 posY;

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180B18);
        entity->animCurFrame = 18;
        entity->unk1E = -0x200;
        entity->unk19 |= 4;
        CreateEntityFromEntity(0x1E, entity, &entity[1]);
        if (D_8003BDEC[0x30] != 0) {
            entity->unk1E = 0;
        }

    case 1:
        if (entity[1].unk84.S8.unk0 != 0) {
            entity->unk1E += 4;
            if (entity->unk1E > 0) {
                entity->unk1E = 0;
                if (D_8003BDEC[0x30] == 0) {
                    g_api.PlaySfx(0x675);
                }
                D_8003BDEC[0x30] = 1;
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

// platform attached to lever at cavern door
INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityCavernDoorPlatform);

// door blocking way to caverns
INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityCavernDoor);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", func_801B9C44);

// switch that clicks when you step on it
void EntityClickSwitch(Entity* entity) {
    s32 temp_a0 = func_801C5D18(entity, 8, 4, 4);
    Entity* player = &PLAYER;

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180B18);
        entity->animCurFrame = 9;
        entity->zPriority = 0x5E;
        if (D_8003BDEC[0x31] != 0) {
            entity->step = 2;
            entity->posY.i.hi += 4;
        }
        break;

    case 1:
        if (temp_a0 != 0) {
            player->posY.i.hi++;
            entity->posY.val += 0xC000;
            if ((g_Camera.posY.i.hi + entity->posY.i.hi) > 160) {
                entity->posY.i.hi = 160 - g_Camera.posY.i.hi;
                g_api.PlaySfx(NA_SE_EV_SWITCH_CLICK);
                D_8003BDEC[0x31] = 1;
                entity->step++;
            }
        }
        break;
    }
}

// smaller weight blocking path near cube of zoe
INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityZoeSmallWeight);

// taller weight blocking path near cube of zoe
INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityZoeTallWeight);

// trap door that leads to underground garden in saturn version.
// also opens the one leading to the save room
void EntityTrapDoor(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180B18);
        entity->animCurFrame = 27;
        entity->zPriority = 0x6A;
        entity->hitboxWidth = 16;
        entity->hitboxHeight = 4;
        entity->unk3C = 1;
        if (D_8018123C == 0) {
            if (PLAYER.posY.val < entity->posY.val) {
                g_CurrentRoomTileLayout.fg[0xA8E / 2] = 0x129;
                g_CurrentRoomTileLayout.fg[0xA90 / 2] = 0x132;
                DestroyEntity(entity);
                break;
            }
            g_CurrentRoomTileLayout.fg[0xA8E / 2] = 0x6C8;
            g_CurrentRoomTileLayout.fg[0xA90 / 2] = 0x6C9;
        } else {
            entity->animCurFrame = 0x1E;
            g_CurrentRoomTileLayout.fg[0xA8E / 2] = 0x6C8;
            g_CurrentRoomTileLayout.fg[0xA90 / 2] = 0x6C9;
            entity->step = 128;
        }

    case 1:
        if (entity->unk48 != 0) {
            D_8018123C = 1;
            entity->step++;
        }
        break;

    case 2:
        AnimateEntity(&D_80181240, entity);
    }
}

// left side of the breakable rock, drops pot roast
INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityMermanRockLeftSide);

// right side of the merman room rock, breaks when hit
INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityMermanRockRightSide);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityUnkId26);

// falling rock that breaks into dust
void EntityFallingRock2(Entity* self) {
    s32 animFrame = self->subId & 0xF;
    Collider collider;
    Entity* newEntity;
    s32 temp_a0;
    s32 var_a1;
    s32 new_var2;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B18);
        self->animCurFrame = animFrame;
        self->animCurFrame += 31;
        self->zPriority = 0x9F;
        self->unk19 |= 4;
        break;

    case 1:
        MoveEntity();
        self->accelerationY += 0x4000;
        self->unk1E -= 0x20;
        new_var2 = self->posY.i.hi;
        new_var2 += D_8018133C[animFrame];
        g_api.CheckCollision(self->posX.i.hi, new_var2, &collider, 0);

        if (collider.unk0 & 1) {
            if (self->accelerationY > 0x40000) {
                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                if (newEntity != 0) {
                    CreateEntityFromEntity(2, self, newEntity);
                    newEntity->subId = 0x11;
                    if (animFrame == 0) {
                        newEntity->subId = 0x13;
                    }
                }
                DestroyEntity(self);
                return;
            }
            self->posY.i.hi = self->posY.i.hi + *(u16*)&collider.unk18;
            temp_a0 = -self->accelerationY;
            self->accelerationY = -self->accelerationY;
            if (temp_a0 < 0) {
                var_a1 = temp_a0 + 7;
            } else {
                var_a1 = temp_a0;
            }
            self->accelerationY = temp_a0 - (var_a1 >> 3);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityUnkId5C);

// falling rock with puff of smoke when it disappears. I think part of the
// merman room breakable rock
void EntityFallingRock(Entity* self) {
    s32 animFrame = self->subId & 0xF;
    Collider collider;
    Entity* newEntity;
    s16 rndAngle;
    s32 rnd;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B18);
        self->animCurFrame = animFrame + 31;
        self->unk1C = 0x60;
        self->unk1A = 0x60;
        self->unk19 |= 7;
        rnd = (Random() & 0x1F) + 16;
        rndAngle = (Random() * 6) + 0x900;
        self->accelerationX = rnd * rcos(rndAngle);
        self->accelerationY = rnd * rsin(rndAngle);
        if (self->accelerationX > 0) {
            self->facing = 1;
        }
        break;

    case 1:
        MoveEntity();
        self->accelerationY += 0x2000;
        self->unk1E -= 0x20;

        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi + 8, &collider,
                             0);
        if (collider.unk0 & 1) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(6, self, newEntity);
                newEntity->subId = 0x10;
                if (animFrame == 0) {
                    newEntity->subId = 0x13;
                }
            }
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", func_801BB548);

// sky animation during death cutscene
INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityDeathSkySwirl);

void EntityUnkId29(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180B18);
        self->zPriority = 0x2A;
        self->flags &= ~FLAG_UNK_08000000;
        self->facing = Random() & 1;
        g_api.func_80134714(0x665, 0x40, (self->posX.i.hi >> 0x4) - 8);
    }
    if (AnimateEntity(D_80181390, self) == 0) {
        DestroyEntity(self);
    }
}

void EntityUnkId2A(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(D_80180B18);
        entity->zPriority = 0x29;
        entity->flags &= ~FLAG_UNK_08000000;
        entity->animCurFrame = entity->subId + 0x22;
        entity->posX.i.hi = D_8018139C[entity->subId << 1];
        entity->posY.i.hi = D_8018139E[entity->subId << 1];
        entity->unk80.modeS16.unk0 = 5;
    }
    entity->unk80.modeS16.unk0--;
    if ((entity->unk80.modeS16.unk0 << 0x10) == 0) {
        DestroyEntity(entity);
    }
}

// switch that goes downwards when you stand on it
void EntitySwitch(Entity* entity) {
    s32 temp_a0 = func_801C5D18(entity, 8, 4, 4);
    Entity* player = &PLAYER;

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180B18);
        entity->animCurFrame = 9;
        entity->zPriority = 0x5E;
        if (D_8003BDEC[0x32] != 0) {
            entity->step = 2;
            entity->posY.i.hi += 4;
        }
        break;

    case 1:
        if (temp_a0 != 0) {
            player->posY.i.hi++;
            entity->posY.val += 0x4000;
            if ((g_Camera.posY.i.hi + entity->posY.i.hi) > 193) {
                entity->posY.i.hi = 193 - g_Camera.posY.i.hi;
                D_8003BDEC[0x32] = 1;
                g_api.PlaySfx(0x608);
                entity->step++;
            }
        }
        break;
    }
}

// door preventing access to warp room / heart
INCLUDE_ASM("asm/us/st/no3/nonmatchings/377D4", EntityHeartRoomGoldDoor);

void EntityUnkId49(Entity* entity) {
    u16 temp;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180ADC);
        break;
    case 1:
        temp = g_CurrentRoomTileLayout.fg[9];
        g_CurrentRoomTileLayout.fg[6] = temp;
        temp = g_CurrentRoomTileLayout.fg[10];
        g_CurrentRoomTileLayout.fg[7] = temp;
        temp = g_CurrentRoomTileLayout.fg[0x39];
        g_CurrentRoomTileLayout.fg[0x36] = temp;
        temp = g_CurrentRoomTileLayout.fg[0x3A];
        g_CurrentRoomTileLayout.fg[0x37] = temp;
        temp = g_CurrentRoomTileLayout.fg[0x69];
        g_CurrentRoomTileLayout.fg[0x66] = temp;
        temp = g_CurrentRoomTileLayout.fg[0x6A];
        g_CurrentRoomTileLayout.fg[0x67] = temp;
        entity->step++;
        break;
    }
}
