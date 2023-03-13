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
            self->flags = temp_s0->unkC;
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
        D_8003CB08.buf.draw.r0 = self->unk7C.S8.unk0;
        D_8003CB08.buf.draw.g0 = self->unk7C.S8.unk1;
        D_8003CB08.buf.draw.b0 = self->unk7E.modeU8.unk0;
        D_800542FC.buf.draw.r0 = self->unk7C.S8.unk0;
        D_800542FC.buf.draw.g0 = self->unk7C.S8.unk1;
        D_800542FC.buf.draw.b0 = self->unk7E.modeU8.unk0;
        break;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B28E4);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityShuttingWindow);

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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B4680);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B4940);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityTrapDoor);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B4D60);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B5108);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B5488);

void EntityFallingRock2(Entity* self) {
    s32 animFrame = self->subId & 0xF;
    Collider collider;
    Entity* newEntity;
    s32 temp_a0;
    s32 var_a1;
    s32 new_var2;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180AA8);
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
        new_var2 += D_80181204[animFrame];
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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B5790);

void EntityFallingRock(Entity* self) {
    s32 animFrame = self->subId & 0xF;
    Collider collider;
    Entity* newEntity;
    s16 rndAngle;
    s32 rnd;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180AA8);
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

void func_801B5DE8(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180AA8);
        self->zPriority = 0x2A;
        self->flags &= ~FLAG_UNK_08000000;
        self->facing = Random() & 1;
        g_api.func_80134714(0x665, 0x40, (self->posX.i.hi >> 0x4) - 8);
    }
    if (AnimateEntity(D_80181214, self) == 0) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B5E98);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntitySwitch);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B6084);

void EntityUnkId49(Entity* self) {
    u16 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180A6C);
        break;
    case 1:
        temp = g_CurrentRoomTileLayout.fg[0x12 / 2];
        g_CurrentRoomTileLayout.fg[0xC / 2] = temp;
        temp = g_CurrentRoomTileLayout.fg[0x14 / 2];
        g_CurrentRoomTileLayout.fg[0xE / 2] = temp;
        temp = g_CurrentRoomTileLayout.fg[0x72 / 2];
        g_CurrentRoomTileLayout.fg[0x6C / 2] = temp;
        temp = g_CurrentRoomTileLayout.fg[0x74 / 2];
        g_CurrentRoomTileLayout.fg[0x6E / 2] = temp;
        temp = g_CurrentRoomTileLayout.fg[0xD2 / 2];
        g_CurrentRoomTileLayout.fg[0xCC / 2] = temp;
        temp = g_CurrentRoomTileLayout.fg[0xD4 / 2];
        g_CurrentRoomTileLayout.fg[0xCE / 2] = temp;
        self->step++;
        break;
    }
}

void func_801B653C(void) {
    Entity* entity;
    s8 temp_s4 = Random() & 3;
    s16 temp_s3 = ((Random() & 0xF) << 8) - 0x800;
    s32 i;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (entity != NULL) {
            CreateEntityFromEntity(0x4D, g_CurrentEntity, entity);
            entity->subId = 2;
            entity->unk88.U8.unk1 = 6 - i;
            entity->unk84.S16.unk0 = temp_s3;
            entity->unk88.U8.unk0 = temp_s4;
        }
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B65FC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B6990);

void func_801B75EC(Entity* self) {
    s8* hitbox;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B50);

    case 1:
        self->facing = self[-1].facing;
        self->posX.i.hi = self[-1].posX.i.hi;
        self->posY.i.hi = self[-1].posY.i.hi;
        hitbox = D_80181454;
        hitbox += 4 * D_8018148C[self[-1].animCurFrame];
        self->unk10 = *hitbox++;
        self->unk12 = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;
        if (self[-1].unk84.U8.unk2 != 0) {
            self->step++;
        }
        break;

    case 2:
        switch (self->unk2E) {
        case 0:
            self->unk19 = 4;
            self->unk3C = 0;
            if (self->facing != 0) {
                self->accelerationX = -0x24000;
            } else {
                self->accelerationX = 0x24000;
            }
            self->accelerationY = -0x40000;
            self->animCurFrame = 0x23;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->unk2E++;

        case 1:
            MoveEntity();
            self->accelerationY += 0x2800;
            self->unk1E += 0x80;
            if (!(self->unk1E & 0xFFF)) {
                func_801C2598(0x625);
            }
        }
    }
}

// projectile fired from slogra's spear
void EntitySlograSpearProjectile(Entity* self) {
    Entity* entity;

    if (self->flags & 0x100) {
        entity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (entity != NULL) {
            CreateEntityFromEntity(2, self, entity);
            entity->subId = 1;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(&D_80180B5C);
        if (self->facing == 0) {
            self->accelerationX = -0x40000;
        } else {
            self->accelerationX = 0x40000;
        }

    case 1:
        if (AnimateEntity(&D_801813D4, self) == 0) {
            func_801BD114(2);
        }
        break;

    case 2:
        MoveEntity();
        AnimateEntity(&D_801813E4, self);
        break;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B78BC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B8CC0);

// small red projectile from gaibon
void EntitySmallGaibonProjectile(Entity* self) {
    if (self->flags & 0x100) {
        self->pfnUpdate = EntityExplosion;
        self->unk19 = 0;
        self->step = 0;
        self->objectId = 2;
        self->subId = 0;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B74);
        self->animSet = 2;
        self->animCurFrame = 1;
        self->unk19 = 5;
        self->unk1A = 0xC0;
        self->accelerationX = (rcos(self->unk1E) * 0x28000) >> 0xC;
        self->accelerationY = (rsin(self->unk1E) * 0x28000) >> 0xC;
        self->palette = 0x81B6;
        self->unk1E -= 0x400;

    case 1:
        MoveEntity();
        AnimateEntity(D_801815E0, self);
        break;
    }
}

void EntityLargeGaibonProjectile(Entity* self) {
    Entity* newEntity;

    if (self->flags & 0x100) {
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
            self->flags |= 0x2000;
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

s32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

void Update(void) {
    s16 i;
    Entity* entity;
    s32* unk;

    for (i = 0; i < 0x20; i++) {
        if (D_801D33F4[i]) {
            D_801D33F4[i]--;
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
                    D_8018164C[(entity->unk49 << 1) | (unk34 & 1)];
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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B93E8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801B94F0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityNumericDamage);

void CreateEntityFromLayout(Entity* entity, LayoutObject* initDesc) {
    DestroyEntity(entity);
    entity->objectId = initDesc->objectId & 0x3FF;
    entity->pfnUpdate = PfnEntityUpdates[entity->objectId];
    entity->posX.i.hi = initDesc->posX - g_Camera.posX.i.hi;
    entity->posY.i.hi = initDesc->posY - g_Camera.posY.i.hi;
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

s32 func_801BB824(Entity* e) {
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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityRedDoor);

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

void FallEntity(void) {
    if (g_CurrentEntity->accelerationY < FALL_TERMINAL_VELOCITY) {
        g_CurrentEntity->accelerationY += FALL_GRAVITY;
    }
}

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

void CollectHeartVessel(void) {
    if (g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
        g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
        D_80097BA0.hearts += HEART_VESSEL_RICHTER;

        if (D_80097BA0.heartsMax < D_80097BA0.hearts) {
            D_80097BA0.hearts = D_80097BA0.heartsMax;
        }
    } else {
        g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
        g_api.func_800FE044(HEART_VESSEL_INCREASE, 0x4000);
    }
    DestroyEntity(g_CurrentEntity);
}

void CollectLifeVessel(void) {
    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_api.func_800FE044(5, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

void DestroyCurrentEntity(void) { DestroyEntity(g_CurrentEntity); }

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", EntityPriceDrop);

void EntityExplosion(Entity* entity) {
    u32 temp_v0;

    if (entity->step == 0) {
        InitializeEntity(D_80180A54);
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
        entity->accelerationY = D_80181E80[entity->subId];
        return;
    }

    entity->posY.val += entity->accelerationY;
    if (!AnimateEntity(D_80181F2C[entity->subId], entity)) {
        DestroyEntity(entity);
    }
}

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

void func_801C070C(Entity* entity) {
    if (entity->step == 0) {
        entity->accelerationY = D_80181FDC[entity->unk94];
        entity->flags = 0x2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = 2;
        entity->animCurFrame = D_80181FF4[entity->subId];
        entity->blendMode = 0x10;
        entity->step++;
    } else {
        entity->animFrameDuration++;
        entity->posY.val -= entity->accelerationY;

        if (!(entity->animFrameDuration & 1)) {
            entity->animCurFrame++;
        }

        if (D_80181FF8[entity->subId] < (s32)entity->animFrameDuration) {
            DestroyEntity(entity);
        }
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C07FC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C08F0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C0B20);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3246C", func_801C0C1C);

void EntityIntenseExplosion(Entity* entity) {
    u32 temp_v0;

    if (entity->step == 0) {
        InitializeEntity(D_80180A54);
        entity->palette = 0x8170;
        entity->animSet = 5;
        entity->animCurFrame = 1;
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

    entity->animFrameDuration++;
    entity->posY.val -= 0x4000;

    if (!(entity->animFrameDuration & 1)) {
        entity->animCurFrame++;
    }

    if (entity->animFrameDuration >= 0x25) {
        DestroyEntity(entity);
    }
}

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
            entity->flags = objInit->unkC;
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
        self->flags |= 0x2000;
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
        self->flags |= 0x2000;
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

void EntityMerman2(Entity* self) {
    Entity* newEntity;
    u16 temp_s0_2;
    u16 temp_s0;
    s32 temp2;
    s16 temp;

    if (self->step == 0) {
        InitializeEntity(D_80180A60);
        self->flags |= 0x2000;
    }

    if (!(g_blinkTimer & 0x3F)) {
        Entity* player = &PLAYER;
        temp = g_Camera.posY.i.hi + player->posY.i.hi;
        if (temp >= 256) {
            temp_s0 = g_Camera.posX.i.hi + player->posX.i.hi;
            temp_s0_2 = 128;
            temp_s0_2 = temp_s0 - temp_s0_2 + Random();
            temp_s0 = temp_s0_2 - 64;
            if (temp_s0 <= 0x280) {
                temp2 = 496;
                newEntity =
                    AllocEntity(&g_EntityArray[160], &g_EntityArray[170]);
                if (newEntity != 0) {
                    if (Random() & 1) {
                        CreateEntityFromCurrentEntity(0x32, newEntity);
                        newEntity->subId = Random() & 1;
                    } else {
                        CreateEntityFromCurrentEntity(0x39, newEntity);
                    }
                    newEntity->posX.i.hi = temp_s0_2 - g_Camera.posX.i.hi;
                    newEntity->posY.i.hi = temp2 - g_Camera.posY.i.hi;
                }
            }
        }
    }
}

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

        if (self->flags & 0x100) {
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
        self->flags |= 0x2000;
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
