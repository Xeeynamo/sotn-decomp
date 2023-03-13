#include "dre.h"

// Pink ball projectile shot by succubus duplicates ID 0x1D
void EntityPinkBallProjectile(Entity* self) {
    Entity* entity;
    s16 temp_s0;
    s16 temp_v0;

    if (D_80180664 & 2) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180500);
        self->blendMode = 0x30;
        self->unk19 = 3;
        self->unk1C = 0;
        self->unk1A = 0;

    case 1:
        self->unk1A = self->unk1C += 4;
        if (self->unk1A > 256) {
            self->unk19 = 0;
        }
        AnimateEntity(D_80180794, self);

        entity = self->unk9C;
        if (entity->unk84.U8.unk1 != 0) {
            self->unk19 = 0;
            self->step++;
        }
        if (entity->flags & 0x100) {
            DestroyEntity(self);
        }
        break;

    case 2:
        temp_s0 = (self->subId << 0xA) + 0x200;
        self->accelerationX = rcos(temp_s0) * 0x38;
        self->accelerationY = rsin(temp_s0) * 0x38;
        self->unkA2 = temp_s0;
        self->unk80.modeS16.unk0 = 128;
        self->step++;

    case 3:
        AnimateEntity(D_80180794, self);
        MoveEntity();
        temp_v0 = func_8019AF08(self, g_EntityArray);
        temp_s0 = func_8019AF88(0x10, self->unkA2, temp_v0);
        self->accelerationX = rcos(temp_s0) * 0x38;
        self->accelerationY = rsin(temp_s0) * 0x38;
        self->unkA2 = temp_s0;

        if (self->unk48 & 0x80) {
            self->step = 4;
        }

        if (--self->unk80.modeS16.unk0 == 0) {
            self->step = 4;
        }
        break;

    case 4:
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        AnimateEntity(D_80180794, self);
        MoveEntity();
        break;
    }
}

// Extending wing spike from succubus ID 0x1E
void EntitySuccubusWingSpike(Entity* self) {
    s32 temp_s2;
    s16 var_s0;

    if (D_80180664 & 2) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_801804E8);
        self->unk19 = 4;
        self->animCurFrame = 0;
        var_s0 = D_801807F0[self->subId];
        self->unk1E = var_s0;
        self->unk19 |= 1;
        self->unk1A = 0x100;
        CreateEntityFromEntity(0x1F, self, &self[1]);
        self[1].facing = self->facing;
        self[1].subId = self->subId;
        self[1].unk1E = self->unk1E;

    case 1:
        if (self->unk9C->unk84.U8.unk1 != 0) {
            self->step++;
        }
        break;

    case 2:
        self->animCurFrame = 85;
        self->unk1A += 0x40;
        if (self->unk1A > 0x600) {
            self->unk1A = 0x600;
        }

        if (self->unk9C->unk84.U8.unk1 == 0) {
            self->step++;
        }
        break;

    case 3:
        self->unk1A -= 0x40;
        if (self->unk1A < 0x100) {
            DestroyEntity(self);
            return;
        }
    }

    var_s0 = self->unk1E;
    temp_s2 = (self->unk1A * 0xB) >> 6;
    if (self->facing == 0) {
        var_s0 = 0x800 - var_s0;
    }

    self[1].posX.i.hi = self->posX.i.hi;
    self[1].posY.i.hi = self->posY.i.hi;
    self[1].posX.i.hi += temp_s2 * rcos(var_s0) >> 0xC;
    self[1].posY.i.hi -= temp_s2 * rsin(var_s0) >> 0xC;
}

void EntityUnkId1F(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_8018050C);
        entity->animCurFrame = 0;
        entity->unk19 = 4;
        entity->unk3C = 0;
    case 1:
        if (entity[-1].animCurFrame != 0) {
            entity->unk3C = 1;
            entity->animCurFrame = 0x56;
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

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801947C8);

void func_8019498C(s16 yOffset) {
    RECT rect;

    rect.y = (yOffset * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801949E8);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_80194AA0);

void func_80194C24(s32 arg0) {
    D_801A3F18 = arg0 + 0x100000;
    D_801A3F16 = 0;
    D_801A3F14 = 1;
}

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_80194C50);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_80194F14);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_80194FF4);

// dialogue with mother opens as alucard walks right ID 20
INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", EntitySuccubusIntroCutscene);

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

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", EntityUnkId21);

// appears to load from the CD and freeze the game
INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", EntityUnkId23);

// Fades to white
INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", EntityFadeToWhite1);

// Fades to white ID 24
INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", EntityFadeToWhite2);

s32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

void Update(void) {
    s16 i;
    Entity* entity;
    s32* unk;

    for (i = 0; i < 0x20; i++) {
        if (D_801A3F8C[i]) {
            D_801A3F8C[i]--;
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
                    D_8018097C[(entity->unk49 << 1) | (unk34 & 1)];
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

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801972BC);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801973C4);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", EntityNumericDamage);

void CreateEntityFromLayout(Entity* entity, LayoutObject* initDesc) {
    DestroyEntity(entity);
    entity->objectId = initDesc->objectId & 0x3FF;
    entity->pfnUpdate = D_801803C4[entity->objectId];
    entity->posX.i.hi = initDesc->posX - g_Camera.posX.i.hi;
    entity->posY.i.hi = initDesc->posY - g_Camera.posY.i.hi;
    entity->subId = initDesc->subId;
    entity->objectRoomIndex = initDesc->objectRoomIndex >> 8;
    entity->unk68 = (initDesc->objectId >> 0xA) & 7;
}

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_80198C44);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_80198D5C);

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

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_80198F18);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_80199014);

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

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801991CC);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801992C8);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801993DC);

void func_80199554(void) {
    Unkstruct8* currentRoomTileLayout = &g_CurrentRoomTileLayout;

    if (D_80097908 != 0) {
        s16 tmp = g_Camera.posX.i.hi;
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

void CreateEntityFromCurrentEntity(u16 objectId, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = D_801803C4[objectId];
    entity->posX.i.hi = g_CurrentEntity->posX.i.hi;
    entity->posY.i.hi = g_CurrentEntity->posY.i.hi;
}

void CreateEntityFromEntity(u16 objectId, Entity* source, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = D_801803C4[objectId];
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
}

s32 func_801996F8(Entity* e) {
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

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", EntityRedDoor);

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

s32 AnimateEntity(const u8 frames[], Entity* entity) {
    s32 flag = 0;
    u16 currentFrameIndex = entity->animFrameIdx * 2;
    u8* currentFrame = frames + currentFrameIndex;

    if (entity->animFrameDuration == 0) {
        if (currentFrame[0] > 0) {
            flag = 0x80;
            if (currentFrame[0] == 0xFF) {
                return false;
            }

            entity->animFrameDuration = *currentFrame++;
            entity->animCurFrame = *currentFrame++;
            entity->animFrameIdx++;
        } else {
            currentFrame = frames;
            entity->animFrameIdx = 0;
            entity->animFrameDuration = 0;
            entity->animFrameDuration = *currentFrame++;
            entity->animCurFrame = *currentFrame++;
            entity->animFrameIdx++;
            return false;
        }
    }

    entity->animFrameDuration = entity->animFrameDuration - 1;
    entity->animCurFrame = currentFrame[-1];
    flag |= true;

    return (u8)flag;
}

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019A590);

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

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019A7B8);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019AA30);

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
    entity->animFrameIdx = 0;
    entity->animFrameDuration = 0;
}

void func_8019B008(u8 arg0) {
    Entity* entity;

    entity = g_CurrentEntity;
    entity->unk2E = arg0;
    entity->animFrameIdx = 0;
    entity->animFrameDuration = 0;
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

void func_8019B1B4(Entity* arg0) {
    if (arg0->step == 0) {
        arg0->step++;
    }
}

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019B1DC);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019B304);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019B45C);

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

void func_8019B858(void) {
    s32 temp_v1;
    Entity* entity = g_CurrentEntity;

    if (entity->accelerationY >= 0) {
        temp_v1 = entity->unk84.unk + entity->unk88.S16.unk0;
        entity->unk84.unk = temp_v1;
        entity->accelerationX = temp_v1;

        if ((temp_v1 == 0x10000) || (temp_v1 == -0x10000)) {
            entity->unk88.U16.unk0 = -entity->unk88.U16.unk0;
        }
        entity = g_CurrentEntity;
    }

    NOP;
    if (entity->accelerationY < 0x00004000) {
        entity->accelerationY += 0x2000;
    }
}

void func_8019B8DC(u16 arg0) {
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

        g_CurrentEntity->posY.i.hi += LOH(res.unk18);
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
    hearts = &D_80097BA0.hearts;
    *hearts += c_HeartPrizes[arg0];

    if (D_80097BA0.heartsMax < *hearts) {
        *hearts = D_80097BA0.heartsMax;
    }

    DestroyEntity(g_CurrentEntity);
}

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019BAB8);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019BB94);

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
    g_api.func_800FE044(LIFE_VESSEL_INCREASE, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

void DestroyCurrentEntity(void) { DestroyEntity(g_CurrentEntity); }

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", EntityPriceDrop);

void EntityExplosion(Entity* entity) {
    u32 temp_v0;
    u32 temp;

    if (!entity->step) {
        InitializeEntity(&D_80180470);
        entity->animSet = 2;
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
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

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", EntityInventoryDrop);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019CDC4);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", EntityRelicOrb);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", EntityHeartDrop);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", EntityUnkId0E);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019E1C8);

void EntityUnkId13(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180494);
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

// https://decomp.me/scratch/lcx4I
INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019E3C8);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019E4F8);

// an explosion animation ID 0x14
void EntityExplosion14(Entity* entity) {
    u8 new_var2;
    u32 new_var;

    if (!entity->step) {
        new_var = D_8018130C[entity->unk94];
        entity->flags = 0x2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = 2;
        entity->accelerationY = new_var;
        new_var2 = D_80181324[entity->subId];
        entity->blendMode = 0x10;
        entity->step++;
        entity->animCurFrame = new_var2;
        return;
    }

    entity->animFrameDuration++;
    entity->posY.val -= entity->accelerationY;

    if (!(entity->animFrameDuration & 1)) {
        entity->animCurFrame++;
    }

    if (D_80181328[entity->subId] < entity->animFrameDuration) {
        DestroyEntity(entity);
    }
}

// looks like a particle of dust fading away
void EntityUnkId15(Entity* entity) {
    u16 temp_v0;
    u32 temp2;

    if (!entity->step) {
        entity->flags = 0x2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = 5;
        entity->animCurFrame = 1;
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

    entity->animFrameDuration++;
    entity->posY.val -= entity->accelerationY;

    if (!(entity->animFrameDuration & 1)) {
        entity->animCurFrame++;
    }

    if (entity->animFrameDuration >= 0x25) {
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019E7C4);

bool func_8019E9F4(Unkstruct6* arg0) {
    Collider res;

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

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019EAF0);

void EntityIntenseExplosion(Entity* entity) {
    u32 temp_v0;

    if (entity->step == 0) {
        InitializeEntity(D_80180470);
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

void func_8019F170(Entity* entity) {
    if (!entity->step) {
        InitializeEntity(D_80180470);
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

    if (!AnimateEntity(&D_80181338, entity)) {
        DestroyEntity(entity);
    }
}

void func_8019F23C(u16 objectId, Entity* src, Entity* dst) {
    DestroyEntity(dst);
    dst->objectId = objectId;
    dst->pfnUpdate = D_801803C4[objectId];
    dst->posX.i.hi = src->posX.i.hi;
    dst->posY.i.hi = src->posY.i.hi;
    dst->unk5A = src->unk5A;
    dst->zPriority = src->zPriority;
    dst->animSet = src->animSet;
    dst->flags = 0x1002000 | FLAG_UNK_04000000 | FLAG_UNK_08000000 |
                 FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                 FLAG_DESTROY_IF_OUT_OF_CAMERA;

    if (src->palette & 0x8000) {
        dst->palette = src->unk6A;
    } else {
        dst->palette = src->palette;
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
            CreateEntityFromEntity(2, g_CurrentEntity, entity);
            entity->unk84.U8.unk1 = 6 - i;
            entity->unk80.modeS16.unk0 = temp_s3;
            entity->unk84.U8.unk0 = temp_s4;
        }
    }
}

// https://decomp.me/scratch/Hfk9n
INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019F3BC);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019F594);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019FB74);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801A0274);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801A046C);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801A0564);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", EntityStageNamePopup);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", EntityAbsorbOrb);

// ID 0x0D
INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", EntityEnemyBlood);

extern ObjInit2 D_80181420[];
void EntityRoomForeground(Entity* entity) {
    ObjInit2* objInit = &D_80181420[entity->subId];

    if (entity->step == 0) {
        InitializeEntity(D_801804AC);
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

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801A1CE8);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801A2018);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801A2400);

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

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801A2580);

// https://decomp.me/scratch/IIvQX a0 -> v0 register swap
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801A25FC);
#else
POLY_GT4* func_801A25FC(POLY_GT4* poly, s32 arg1) {
    s32 i;
    s8 var_a2;

    if (poly->p3 != 0) {
        poly->p3 = 0;
    } else {
        poly->p3 = 1;
    }

    for (i = 0; i < arg1; i++) {
        if (poly->p3 != 0) {
            var_a2 = 0;
            poly->pad3 &= ~8;
        } else {
            var_a2 = 1;
            poly->pad3 |= 8;
        }

        if (poly->tag != NULL) {
            poly->p3 = var_a2;
        } else {
            return NULL;
        }
    }
    return poly;
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

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801A2848);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801A2A58);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801A2C9C);

// https://decomp.me/scratch/nNfXk 95.28%
INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", EntityUnkId17);

// 3D house object in background ID 0x16
INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", Entity3DBackgroundHouse);
