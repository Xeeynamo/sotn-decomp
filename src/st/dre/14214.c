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

        entity = self->ext.generic.unk9C;
        if (entity->ext.generic.unk84.U8.unk1 != 0) {
            self->unk19 = 0;
            self->step++;
        }
        if (entity->flags & 0x100) {
            DestroyEntity(self);
        }
        break;

    case 2:
        temp_s0 = (self->params << 0xA) + 0x200;
        self->accelerationX = rcos(temp_s0) * 0x38;
        self->accelerationY = rsin(temp_s0) * 0x38;
        self->ext.generic.unkA2 = temp_s0;
        self->ext.generic.unk80.modeS16.unk0 = 128;
        self->step++;

    case 3:
        AnimateEntity(D_80180794, self);
        MoveEntity();
        temp_v0 = func_8019AF08(self, g_Entities);
        temp_s0 = func_8019AF88(0x10, self->ext.generic.unkA2, temp_v0);
        self->accelerationX = rcos(temp_s0) * 0x38;
        self->accelerationY = rsin(temp_s0) * 0x38;
        self->ext.generic.unkA2 = temp_s0;

        if (self->hitFlags & 0x80) {
            self->step = 4;
        }

        if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
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
        var_s0 = D_801807F0[self->params];
        self->rotAngle = var_s0;
        self->unk19 |= 1;
        self->unk1A = 0x100;
        CreateEntityFromEntity(0x1F, self, &self[1]);
        self[1].facing = self->facing;
        self[1].params = self->params;
        self[1].rotAngle = self->rotAngle;

    case 1:
        if (self->ext.generic.unk9C->ext.generic.unk84.U8.unk1 != 0) {
            self->step++;
        }
        break;

    case 2:
        self->animCurFrame = 85;
        self->unk1A += 0x40;
        if (self->unk1A > 0x600) {
            self->unk1A = 0x600;
        }

        if (self->ext.generic.unk9C->ext.generic.unk84.U8.unk1 == 0) {
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

    var_s0 = self->rotAngle;
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
        entity->hitboxState = 0;
    case 1:
        if (entity[-1].animCurFrame != 0) {
            entity->hitboxState = 1;
            entity->animCurFrame = 0x56;
        }
        if (entity->hitFlags != 0) {
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
            g_api.FreePrimitives(D_80097414);
        }
    }

    for (entity = &g_Entities[STAGE_ENTITY_START];
         entity < &g_Entities[TOTAL_ENTITY_COUNT]; entity++) {
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
                    D_8018097C[(entity->nFramesInvincibility << 1) |
                               (unk34 & 1)];
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
                        entity->hitFlags = 0;
                    }
                }
            }
        } else {
            g_CurrentEntity = entity;
            entity->pfnUpdate(entity);
            entity->unk44 = 0;
            entity->hitFlags = 0;
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
    entity->params = initDesc->params;
    entity->objectRoomIndex = initDesc->objectRoomIndex >> 8;
    entity->unk68 = (initDesc->objectId >> 0xA) & 7;
}

void CreateEntityWhenInVerticalRange(LayoutObject* layoutObj) {
    s16 yClose;
    s16 yFar;
    s16 posY;
    Entity* entity;

    posY = g_Camera.posY.i.hi;
    yClose = posY - 0x40;
    yFar = posY + 0x120;
    if (yClose < 0) {
        yClose = 0;
    }

    posY = layoutObj->posY;
    if (posY < yClose) {
        return;
    }

    if (yFar < posY) {
        return;
    }

    switch (layoutObj->objectId & 0xE000) {
    case 0x0:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->objectRoomIndex];
        if (entity->objectId == 0) {
            CreateEntityFromLayout(entity, layoutObj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->objectRoomIndex];
        CreateEntityFromLayout(entity, layoutObj);
        break;
    }
}

void CreateEntityWhenInHorizontalRange(LayoutObject* layoutObj) {
    s16 xClose;
    s16 xFar;
    s16 posX;
    Entity* entity;

    posX = g_Camera.posX.i.hi;
    xClose = posX - 0x40;
    xFar = posX + 0x140;
    if (xClose < 0) {
        xClose = 0;
    }

    posX = layoutObj->posX;
    if (posX < xClose) {
        return;
    }

    if (xFar < posX) {
        return;
    }

    switch (layoutObj->objectId & 0xE000) {
    case 0x0:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->objectRoomIndex];
        if (entity->objectId == 0) {
            CreateEntityFromLayout(entity, layoutObj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->objectRoomIndex];
        CreateEntityFromLayout(entity, layoutObj);
        break;
    }
}

void func_80198E74(s16 arg0) {
    while (1) {
        if ((D_801A32C4->posX != 0xFFFE) && ((s32)D_801A32C4->posX >= arg0)) {
            break;
        }

        D_801A32C4++;
    }
}

void func_80198EC0(s16 arg0) {
    while (true) {
        if ((D_801A32C4->posX != 0xFFFF) &&
            ((arg0 >= (s32)D_801A32C4->posX) || (D_801A32C4->posX == 0xFFFE))) {
            break;
        }
        D_801A32C4--;
    }
}

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_80198F18);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_80199014);

void func_80199128(s16 arg0) {
    while (1) {
        if ((D_801A32C8[1] != 0xFFFE) && ((s32)D_801A32C8[1] >= arg0)) {
            break;
        }

        D_801A32C8 += 5;
    }
}

void func_80199174(s16 arg0) {
    while (true) {
        if ((D_801A32C8[1] != 0xFFFF) &&
            (((s32)arg0 >= D_801A32C8[1]) || (D_801A32C8[1] == 0xFFFE))) {
            break;
        }
        D_801A32C8 -= 5;
    }
}

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801991CC);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_801992C8);

void InitRoomEntities(s32 objLayoutId) {
    u16* pObjLayoutStart = D_80180220[objLayoutId];
    Unkstruct8* currentRoomTileLayout = &g_CurrentRoomTileLayout;
    s16 temp_s0;
    s16 arg0;
    s16 i;
    u16* temp_v1;

    D_801A32C4 = pObjLayoutStart;
    D_801A32C8 = D_801802F4[objLayoutId];

    if (*pObjLayoutStart != 0xFFFE) {
        D_801A32C4 = pObjLayoutStart + 1;
        arg0 = Random() & 0xFF;
        for (i = 0; true; i++) {
            temp_v1 = D_801A32C4;
            D_801A32C4 = temp_v1 + 1;
            arg0 -= temp_v1[0];
            if (arg0 < 0) {
                break;
            }
            D_801A32C4 = temp_v1 + 3;
        }
        D_801A32C4 = (temp_v1[2] << 0x10) + temp_v1[1];
        D_801A32C8 += i * 2 + 2;
        D_801A32C8 = (D_801A32C8[1] << 0x10) + D_801A32C8[0];
    }
    arg0 = currentRoomTileLayout->unkA;
    temp_s0 = arg0 + 0x140;
    i = arg0 - 0x40;
    if (i < 0) {
        i = 0;
    }

    D_801A32CC = 0;
    D_801A32D0 = 0;
    func_80198E74(i);
    func_80198F18(temp_s0);
    func_80199128(currentRoomTileLayout->unkE + 0x120);
}

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

    if (item->flags & FLAG_HAS_PRIMS) {
        g_api.FreePrimitives(item->primIndex);
    }

    ptr = (u32*)item;
    length = sizeof(Entity) / sizeof(s32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

void DestroyEntityFromIndex(s16 index) {
    Entity* entity = &g_Entities[index];

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

u8 func_8019A590(u8 frames[], Entity* self, u8 arg2) {
    u16 animFrameStart = self->animFrameIdx * 2;
    u8* var_s1 = &frames[animFrameStart];
    s16 var_a1 = 0;

    if (self->animFrameDuration == 0) {
        if (*var_s1 != 0) {
            if (*var_s1 == 0xFF) {
                return 0;
            }
            self->animFrameDuration = *var_s1++ + (u8)self->ext.stub[0x3F];
            self->animCurFrame = *var_s1++;
            self->animFrameIdx++;
            var_a1 = 128;
        } else {
            var_s1 = frames;
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->ext.stub[0x3F] = (arg2 * Random()) >> 8;
            self->animFrameDuration = *var_s1++ + (u8)self->ext.stub[0x3F];
            self->animCurFrame = *var_s1;
            self->animFrameIdx++;
            return 0;
        }
    }
    self->animFrameDuration--;
    self->animCurFrame = var_s1[-1];
    var_a1 |= 1;
    return var_a1;
}

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
    entity->step_s = 0;
    entity->animFrameIdx = 0;
    entity->animFrameDuration = 0;
}

void func_8019B008(u8 arg0) {
    Entity* entity;

    entity = g_CurrentEntity;
    entity->step_s = arg0;
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
    entity->objectId = E_EXPLOSION;
    entity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
    entity->params = arg0;
    entity->animCurFrame = 0;
    g_CurrentEntity->step = 0;
    g_CurrentEntity->step_s = 0;
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
    g_CurrentEntity->hitboxState = enemyDef->unkC;
    g_CurrentEntity->hitboxWidth = enemyDef->hitboxWidth;
    g_CurrentEntity->hitboxHeight = enemyDef->hitboxHeight;
    g_CurrentEntity->flags = enemyDef->unk24;
    g_CurrentEntity->hitboxOffX = 0;
    g_CurrentEntity->hitboxOffY = 0;
    g_CurrentEntity->step_s = 0;
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

s32 func_8019B1DC(u16* hitSensors, s16 sensorCount) {
    Collider collider;
    s16 i;
    s32 accelerationX;
    u16 temp_a1;
    s16 x;
    s16 y;

    accelerationX = g_CurrentEntity->accelerationX;
    if (accelerationX != 0) {
        x = g_CurrentEntity->posX.i.hi;
        y = g_CurrentEntity->posY.i.hi;
        for (i = 0; i < sensorCount; i++) {
            if (accelerationX < 0) {
                s16 newX = x + *hitSensors++;
                x = newX;
            } else {
                s16 newX = x - *hitSensors++;
                x = newX;
            }

            y += *hitSensors++;
            g_api.CheckCollision(x, y, &collider, 0);
            if (collider.effects & EFFECT_UNK_0002 &&
                ((!(collider.effects & EFFECT_UNK_8000)) || (i != 0))) {
                return 2;
            }
        }
        return 0;
    }
}

void func_8019B304(u16* hitSensors, s16 sensorCount) {
    Collider collider;
    s16 i;
    s32 accelerationX;
    s16 x;
    s16 y;

    accelerationX = g_CurrentEntity->accelerationX;
    if (accelerationX == 0)
        return;
    x = g_CurrentEntity->posX.i.hi;
    y = g_CurrentEntity->posY.i.hi;
    for (i = 0; i < sensorCount; i++) {
        if (accelerationX < 0) {
            x = x + *hitSensors++;
        } else {
            x = x - *hitSensors++;
        }

        y += *hitSensors++;
        g_api.CheckCollision(x, y, &collider, 0);
        if (collider.effects & EFFECT_UNK_0002 &&
            (!(collider.effects & EFFECT_UNK_8000) || i != 0)) {
            if (accelerationX < 0) {
                g_CurrentEntity->posX.i.hi += collider.unk1C;
            } else {
                g_CurrentEntity->posX.i.hi += collider.unk14;
            }
            return;
        }
    }
}

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019B45C);

void ReplaceBreakableWithItemDrop(Entity* self) {
    u16 params;

    PreventEntityFromRespawning(self);

#if STAGE != STAGE_ST0
    if (!(g_Status.relics[10] & 2)) {
        DestroyEntity(self);
        return;
    }
#endif

    params = self->params &= 0xFFF;

    if (params < 0x80) {
        self->objectId = E_PRIZE_DROP;
        self->pfnUpdate = (PfnEntityUpdate)EntityPrizeDrop;
        self->animFrameDuration = 0;
        self->animFrameIdx = 0;
    } else {
        params -= 0x80;
        self->objectId = E_EQUIP_ITEM_DROP;
        self->pfnUpdate = (PfnEntityUpdate)EntityEquipItemDrop;
    }

    self->params = params;
    self->unk6D = 0x10;
    self->step = 0;
}

void func_8019B858(void) {
    s32 temp_v1;
    Entity* entity = g_CurrentEntity;

    if (entity->accelerationY >= 0) {
        temp_v1 =
            entity->ext.generic.unk84.unk + entity->ext.generic.unk88.S16.unk0;
        entity->ext.generic.unk84.unk = temp_v1;
        entity->accelerationX = temp_v1;

        if ((temp_v1 == 0x10000) || (temp_v1 == -0x10000)) {
            entity->ext.generic.unk88.U16.unk0 =
                -entity->ext.generic.unk88.U16.unk0;
        }
        entity = g_CurrentEntity;
    }

    if (entity->accelerationY < 0x00004000) {
        entity->accelerationY += 0x2000;
    }
}

void func_8019B8DC(u16 arg0) {
    Collider collider;

    if (g_CurrentEntity->accelerationX < 0) {
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi - 7, &collider, 0);
        if (collider.effects & EFFECT_NOTHROUGH) {
            g_CurrentEntity->accelerationY = 0;
        }
    }

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                         g_CurrentEntity->posY.i.hi + 7, &collider, 0);

    if (arg0) {
        if (!(collider.effects & EFFECT_NOTHROUGH)) {
            MoveEntity();
            FallEntity();
            return;
        }

        g_CurrentEntity->accelerationX = 0;
        g_CurrentEntity->accelerationY = 0;

        if (collider.effects & EFFECT_QUICKSAND) {
            g_CurrentEntity->posY.val += 0x2000;
            return;
        }

        g_CurrentEntity->posY.i.hi += collider.unk18;
        return;
    }

    if (!(collider.effects & EFFECT_NOTHROUGH)) {
        MoveEntity();
        func_8019B858();
    }
}

void func_8019BA38(u16 arg0) {
    s32* hearts;

    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    hearts = &g_Status.hearts;
    *hearts += c_HeartPrizes[arg0];

    if (g_Status.heartsMax < *hearts) {
        *hearts = g_Status.heartsMax;
    }

    DestroyEntity(g_CurrentEntity);
}

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019BAB8);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", func_8019BB94);

void CollectHeartVessel(void) {
    if (g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
        g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
        g_Status.hearts += HEART_VESSEL_RICHTER;

        if (g_Status.heartsMax < g_Status.hearts) {
            g_Status.hearts = g_Status.heartsMax;
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

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14214", EntityPrizeDrop);

void EntityExplosion(Entity* entity) {
    u32 temp_v0;
    u32 temp;

    if (!entity->step) {
        InitializeEntity(D_80180470);
        entity->animSet = ANIMSET_DRA(2);
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
        entity->blendMode = 0x30;

        if (entity->params & 0xF0) {
            entity->palette = 0x8195;
            entity->blendMode = 0x10;
        }

        temp_v0 = entity->params & 0xFF00;

        if (temp_v0 != 0) {
            entity->zPriority = (u16)(temp_v0 >> 8);
        }

        entity->params &= 0xF;
        entity->accelerationY = D_801811B0[entity->params];
        return;
    }

    entity->posY.val += entity->accelerationY;
    if (!AnimateEntity(D_8018125C[entity->params], entity)) {
        DestroyEntity(entity);
    }
}

void func_8019C738(Entity* entity, s32 renderFlags) {
    POLY_GT4* poly;
    s16 left, top, right, bottom;

    poly = &g_PrimBuf[entity->primIndex];

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
