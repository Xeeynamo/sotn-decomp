/*
 * File: D600.c
 * Overlay: CEN
 * Description: Center Cube Area (Final Boss)
 */

#include "cen.h"

// background block of rock
void EntityBackgroundBlock(Entity* self) {
    ObjInit2* obj = &D_80180490[self->subId].animSet;

    if (self->step == 0) {
        InitializeEntity(D_80180458);
        self->animSet = obj->animSet;
        self->zPriority = obj->zPriority;
        self->unk5A = obj->unk4.s;
        self->palette = obj->palette;
        self->unk19 = obj->unk8;
        self->blendMode = obj->blendMode;

        if (obj->unkC != 0) {
            self->flags = obj->unkC;
        }

        if (self->subId == 1) {
            self->unk1C = 0x200;
            self->unk1A = 0x200;
        }
    }
    func_80194394(obj->unk10, self);
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityUnkId12);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityUnkId01);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8018DB18);

void func_8018DF0C(void) {
    D_8019D384 = 2;
    D_8019D382 = 2;
    D_8019D386 = 0;
    D_8019D38A = 0;
    D_8019D38E = 0;
    D_8019D38F = 8;
    D_8019D37E = D_8019D380 + 0x14;
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8018DF60);

void func_8018E124(s16 arg0) {
    RECT rect;

    rect.y = (arg0 * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8018E180);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8018E238);

void func_8018E3BC(s32 arg0) {
    D_8019D3B8 = arg0 + 0x100000;
    D_8019D3B6 = 0;
    D_8019D3B4 = 1;
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8018E3E8);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8018E6C4);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityUnkId16);

void func_8018F890(s16 arg0) {
    s16 temp_v0 = arg0 - g_CurrentRoom.height;

    if (temp_v0 > 1) {
        g_CurrentRoom.height++;
    } else if (temp_v0 < -1) {
        g_CurrentRoom.height--;
    } else {
        g_CurrentRoom.height = arg0;
    }
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8018F8EC);

// platform that lifts you into chamber, starts cutscene
INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityPlatform);

// Black layer that covers room interior and lights up when cutscene starts
INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityRoomDarkness);

void EntityMaria(Entity* self) {
    if (self->step == 0) {
        /* Has player seen Maria Holy Glasses Cutscene? */
        if (D_8003BDEC[216] != 0) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(D_80180428);
        self->flags = FLAG_UNK_08000000;
        self->animSet = -0x7FFF;
        self->animCurFrame = 10;
        self->unk5A = 0x48;
        self->palette = 0x210;
        self->zPriority = 0x80;
    }
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8019040C);

s16 func_801904B8(Primitive* prim, s16 arg1) {
    prim->u0 = prim->u2 = 0x50;
    prim->u1 = prim->u3 = 0x60;
    prim->blendMode = 2;
    prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi - 8;
    prim->x1 = prim->x3 = g_CurrentEntity->posX.i.hi + 8;
    prim->y2 = prim->y3 = arg1;
    arg1 -= 32;
    prim->v2 = prim->v3 = 38;
    prim->v0 = prim->v1 = 6;
    prim->y0 = prim->y1 = arg1;
    return arg1;
}

// Elevator when not moving (ID 1A)
INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityElevatorStationary);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityUnkId1B);

// Elevator when moving, fixes player into position (ID 1C)
INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityMovingElevator);

s32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80190E7C);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80191178);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80191280);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityNumericDamage);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80192A3C);

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
        entity = &D_800762D8[(u8)layoutObj->objectRoomIndex];
        if (entity->objectId == 0) {
            func_80192A3C(entity, layoutObj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity = &D_800762D8[(u8)layoutObj->objectRoomIndex];
        func_80192A3C(entity, layoutObj);
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
        entity = &D_800762D8[(u8)layoutObj->objectRoomIndex];
        if (entity->objectId == 0) {
            func_80192A3C(entity, layoutObj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity = &D_800762D8[(u8)layoutObj->objectRoomIndex];
        func_80192A3C(entity, layoutObj);
        break;
    }
}

void func_80192D30(s16 arg0) {
    while (1) {
        if ((D_8019C764->posX != 0xFFFE) && ((s32)D_8019C764->posX >= arg0)) {
            break;
        }

        D_8019C764++;
    }
}

void func_80192D7C(s16 arg0) {
    while (true) {
        if (((D_8019C764->posX != 0xFFFF) &&
             ((arg0 >= D_8019C764->posX) || (D_8019C764->posX == 0xFFFE)))) {
            break;
        }
        D_8019C764--;
    }
}

void func_80192DD4(s16 arg0) {
    s32 expected;
    u8 flag;

    if (D_8019C76C != 0) {
        func_80192D30(arg0 - D_80097908);
        D_8019C76C = 0;
    }

    while (true) {
        if ((D_8019C764->posX == 0xFFFF) || (arg0 < D_8019C764->posX)) {
            return;
        }

        expected = 0;
        flag = (D_8019C764->objectRoomIndex >> 8) + 0xFF;
        if ((flag == 0xFF) ||
            (g_entityDestroyed[flag >> 5] & (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInVerticalRange(D_8019C764);
        }
        D_8019C764++;
    }
}

void func_80192ED0(s16 arg0) {
    u8 flag;
    s32 expected;

    if (arg0 < 0) {
        arg0 = 0;
    }

    if (D_8019C76C == 0) {
        func_80192D7C(arg0 - D_80097908);
        D_8019C76C = 1;
    }

    while (true) {
        if (D_8019C764->posX == 0xFFFE || arg0 > D_8019C764->posX) {
            return;
        }

        expected = 0;
        flag = (D_8019C764->objectRoomIndex >> 8) + 255;
        if (flag == 0xFF ||
            (g_entityDestroyed[flag >> 5] & (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInVerticalRange(D_8019C764);
        }
        D_8019C764--;
    }
}

void func_80192FE4(s16 arg0) {
    while (true) {
        if ((D_8019C768->posY != 0xFFFE) && ((s32)D_8019C768->posY >= arg0)) {
            break;
        }

        D_8019C768++;
    }
}

void func_80193030(s16 arg0) {
    while (true) {
        if ((D_8019C768->posY != 0xFFFF) &&
            ((arg0 >= D_8019C768->posY) || !(D_8019C768->posY != 0xFFFE))) {
            break;
        }
        D_8019C768--;
    }
}

void func_80193088(s16 arg0) {
    u8 flag;
    s32 expected;

    if (D_8019C770 != 0) {
        func_80192FE4(arg0 - D_8009790C);
        D_8019C770 = 0;
    }

    while (true) {
        if ((D_8019C768->posY == 0xFFFF) || (arg0 < D_8019C768->posY)) {
            return;
        }

        expected = 0;
        flag = (D_8019C768->objectRoomIndex >> 8) + 0xFF;
        if ((flag == 0xFF) ||
            (g_entityDestroyed[flag >> 5] & (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInHorizontalRange(D_8019C768);
        }
        D_8019C768++;
    }
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80193184);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80193298);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80193410);

void CreateEntityFromCurrentEntity(u16 objectId, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = D_80180390[objectId];
    entity->posX.i.hi = (s16)(u16)g_CurrentEntity->posX.i.hi;
    entity->posY.i.hi = (s16)(u16)g_CurrentEntity->posY.i.hi;
}

void CreateEntityFromEntity(u16 objectId, Entity* source, Entity* entity);
void func_80193538(u16 objectId, Entity* source, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = D_80180390[objectId];
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
}

bool func_801935B4(Entity* self) {
    s16 posX = PLAYER.posX.i.hi - self->posX.i.hi;
    s16 posY;

    posX = ABS(posX);

    if (posX < 17) {
        posY = PLAYER.posY.i.hi - self->posY.i.hi;
        posY = ABS(posY);
        return posY < 33;
    }
    return 0;
}

// Red door (ID 05)
INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityRedDoor);

void DestroyEntity(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->flags & FLAG_FREE_POLYGONS) {
        g_api.FreePrimitives(entity->firstPolygonIndex);
    }

    ptr = (u32*)entity;
    length = sizeof(Entity) / sizeof(u32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

void func_801942D0(s16 index) {
    Entity* entity = &g_EntityArray[index];

    while (entity < &D_8007EF1C) {
        DestroyEntity(entity);
        entity++;
    }
}

void func_8019434C(Entity* entity) {
    if (entity->objectRoomIndex) {
        u32 value = (entity->objectRoomIndex - 1);
        u16 index = value / 32;
        u16 bit = value % 32;
        g_entityDestroyed[index] |= 1 << bit;
    }
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80194394);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8019444C);

/*
 * Returns the absolute distance from g_CurrentEntity to player in the X Axis
 */
s32 func_80194564(void) {
    s16 xDistance = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (xDistance < 0) {
        xDistance = -xDistance;
    }
    return xDistance;
}

/*
 * Returns the absolute distance from g_CurrentEntity to player in the Y Axis
 */
s32 func_801945A0(void) {
    s32 yDistance = g_CurrentEntity->posY.i.hi - PLAYER.posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

s16 func_801945D4(void) {
    s16 var_a0 = g_CurrentEntity->posX.i.hi > PLAYER.posX.i.hi;

    if (g_CurrentEntity->posY.i.hi > PLAYER.posY.i.hi) {
        var_a0 |= 2;
    }
    return var_a0;
}

void MoveEntity() {
    g_CurrentEntity->posX.val += g_CurrentEntity->accelerationX;
    g_CurrentEntity->posY.val += g_CurrentEntity->accelerationY;
}

void func_80194648(void) {
    if (g_CurrentEntity->accelerationY < FALL_TERMINAL_VELOCITY) {
        g_CurrentEntity->accelerationY += FALL_GRAVITY;
    }
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80194674);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_801948EC);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", AllocEntity);

s32 func_80194B34(u8 arg0, s16 arg1) { return D_80180BBC[arg0] * arg1; }

s16 func_80194B60(u8 arg0) { return D_80180BBC[arg0]; }

void func_80194B7C(s32 arg0, s16 arg1) {
    g_CurrentEntity->accelerationX = func_80194B34(arg0 & 0xFF, arg1);
    g_CurrentEntity->accelerationY = func_80194B34((arg0 - 0x40) & 0xFF, arg1);
}

u8 func_80194BE8(s16 x, s16 y) { return ((ratan2(y, x) >> 4) + 0x40); }

u8 func_80194C20(Entity* arg0, Entity* arg1) {
    u16 x;
    u16 y;

    x = arg1->posX.i.hi - arg0->posX.i.hi;
    y = arg1->posY.i.hi - arg0->posY.i.hi;

    return func_80194BE8(x, y);
}

u16 func_80194C68(s16 x, s16 y) {
    x -= g_CurrentEntity->posX.i.hi;
    y -= g_CurrentEntity->posY.i.hi;

    return func_80194BE8(x, y);
}

u8 func_80194CB0(u8 arg0, u8 arg1, u8 arg2) {
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

void func_80194D08(s32 slope, s16 speed) {
    Entity* entity;
    s32 moveX;
    s32 moveY;

    moveX = rcos((u16)slope) * speed;
    entity = g_CurrentEntity;

    if (moveX < 0) {
        moveX += 15;
    }

    entity->accelerationX = moveX >> 4;

    moveY = rsin((u16)slope) * speed;
    entity = g_CurrentEntity;

    if (moveY < 0) {
        moveY += 15;
    }

    entity->accelerationY = moveY >> 4;
}

u16 func_80194D94(s16 arg0, s16 arg1) { return ratan2(arg1, arg0); }

u16 func_80194DC4(Entity* a, Entity* b) {
    s32 diffX = b->posX.i.hi - a->posX.i.hi;
    s32 diffY = b->posY.i.hi - a->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_80194DFC(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s16 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_80194E44(u16 arg0, s16 arg1, s16 arg2) {
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

void func_80194EA4(u8 step) {
    Entity* entity = g_CurrentEntity;

    entity->step = step;
    entity->unk2E = 0;
    entity->animFrameIdx = 0;
    entity->animFrameDuration = 0;
}

void func_80194EC4(u8 arg0) {
    Entity* entity = g_CurrentEntity;

    entity->unk2E = arg0;
    entity->animFrameIdx = 0;
    entity->animFrameDuration = 0;
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80194EE0);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", InitializeEntity);

void func_80195070(Entity* entity) {
    if (entity->step == 0) {
        entity->step++;
    }
}

s32 func_80195098(u16* hitSensors, s16 sensorCount) {
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
            if (collider.unk0 & 2 &&
                ((!(collider.unk0 & 0x8000)) || (i != 0))) {
                return 2;
            }
        }
        return 0;
    }
}

void func_801951C0(u16* hitSensors, s16 sensorCount) {
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
        if (collider.unk0 & 2 && (!(collider.unk0 & 0x8000) || i != 0)) {
            if (accelerationX < 0) {
                g_CurrentEntity->posX.i.hi += collider.unk1C;
            } else {
                g_CurrentEntity->posX.i.hi += collider.unk14;
            }
            return;
        }
    }
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80195318);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8019565C);

void func_80195714(void) {
    s32 temp_v1;
    Entity* entity;

    entity = g_CurrentEntity;
    if (entity->accelerationY >= 0) {
        temp_v1 = entity->unk88.S16.unk0 + entity->unk84.unk;
        entity->unk84.unk = temp_v1;
        entity->accelerationX = temp_v1;
        if (temp_v1 == 0x10000 || temp_v1 == -0x10000) {
            entity->unk88.S16.unk0 = -entity->unk88.S16.unk0;
        }
        entity = g_CurrentEntity;
    }
    NOP;

    if (entity->accelerationY < 0x00004000) {
        entity->accelerationY += 0x2000;
    }
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80195798);

void CollectHeart(u16 index) {
    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_Status.hearts = D_80180FE8[index] + g_Status.hearts;
    if (g_Status.heartsMax < g_Status.hearts) {
        g_Status.hearts = g_Status.heartsMax;
    }
    DestroyEntity(g_CurrentEntity);
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80195974);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80195A50);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80195B68);

void func_80195C0C(void) {
    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_api.func_800FE044(5, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

void func_80195C5C(void) { DestroyEntity(g_CurrentEntity); }

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityPrizeDrop);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityExplosion);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_801965F4);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityEquipItemDrop);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80196C80);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityRelicOrb);

void EntityHeartDrop(Entity* self) {
    u16 temp_a0;
    u16 temp_a0_2;
    u16 var_a0;

    if (self->step == 0) {
        temp_a0 = self->subId + 0xC0;
        self->unkB4 = temp_a0;
        if ((D_8003BEEC[temp_a0 >> 3] >> (temp_a0 & 7)) & 1) {
            DestroyEntity(self);
            return;
        }
        temp_a0_2 = temp_a0 - 0xC0;
        var_a0 = D_801805D8[temp_a0_2];
        if (var_a0 < 128) {
            self->unkB8.unkFuncB8 = EntityPrizeDrop;
        } else {
            self->unkB8.unkFuncB8 = EntityEquipItemDrop;
            var_a0 -= 128;
        }
        self->subId = var_a0 + 0x8000;
    } else {
        temp_a0_2 = self->unkB4;
        if (self->step < 5) {
            if (self->unk48 != 0) {
                var_a0 = self->unkB4;
                D_8003BEEC[temp_a0_2 >> 3] |= 1 << (var_a0 & 7);
                self->step = 5;
            }
        }
    }
    self->unkB8.unkFuncB8(self);
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityUnkId0E);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80198084);

extern u16 D_80180440[];
void EntityUnkId13(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180440);
        entity->unk8C.modeU16.unk0 = entity->unk80.entityPtr->objectId;
    case 1:
        if (entity->unk7C.U8.unk0++ >= 5) {
            Entity* newEntity =
                AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
            if (newEntity != NULL) {
                func_80193538(ENTITY_EXPLOSION, entity, newEntity);
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

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80198284);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_801983B4);

// ID 14
INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityExplosion14);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityUnkId15);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80198680);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_801988B0);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_801989AC);

// ID 06
INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityIntenseExplosion);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8019902C);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_801990F8);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_801991C0);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80199278);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80199450);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80199A30);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8019A130);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8019A328);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8019A420);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityStageNamePopup);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityAbsorbOrb);

void EntityEnemyBlood(Entity* self) {
    int fakeTemp; // !TODO: !FAKE
    Primitive* prim;
    s32 var_a0_2;
    u16 subId;
    s16 posX;
    s32 rnd;
    s32 i;

    switch (self->step) {
    case 0:
        i = g_api.func_800EDB58(17, 12);
        if (i != -1) {
            InitializeEntity(D_80180410);
            prim = &g_PrimBuf[i];
            self->firstPolygonIndex = i;
            self->animSet = 0;
            subId = self->subId;
            self->unk3C = 1;
            self->unk7C.s = 48;
            self->hitboxHeight = 8;
            self->zPriority = 0xC0;
            self->hitboxWidth = 0;
            self->flags |= FLAG_FREE_POLYGONS;

            for (i = 12; i != 0;) {
                prim->x0 = self->posX.i.hi + ((Random() & (fakeTemp = 7)) - 5);
                rnd = (Random() & 7) - 5;
                prim->y0 = self->posY.i.hi + rnd;
                *(s32*)&prim->r1 = 0;
                *(s32*)&prim->x1 = 0;
                prim->u0 = 4;
                prim->v0 = 4;

                if (subId != 0) {
                    func_80194D08(0xCC0 + i * 64,
                                  ((Random() & 0xF) * 0x10) + 0x180);
                } else {
                    func_80194D08(0xB40 - i * 64,
                                  ((Random() & 0xF) * 0x10) + 0x180);
                }

                *(s32*)&prim->u1 = self->accelerationX;
                *(s32*)&prim->r2 = self->accelerationY;

                var_a0_2 = *(s32*)&prim->u1;
                if (var_a0_2 <= -1) {
                    var_a0_2 += 0x3F;
                }

                *(s32*)&prim->r3 = -(var_a0_2 >> 6);
                *(s32*)&prim->x3 = -(*(s32*)&prim->r2 / 48) + 0xC00;

                prim->x2 = prim->y2 = (Random() & 7) + 7;
                prim->r0 = 128;
                prim->b0 = 16;
                prim->g0 = 0;
                prim->priority = self->zPriority;
                prim->blendMode = 2;
                i--;
                if (i != 0) {
                    prim++;
                }
            }

            if (subId != 0) {
                self->accelerationX = 0x14000;
                self->unk80.modeS32 = -0x200;
            } else {
                self->accelerationX = -0x14000;
                self->unk80.modeS32 = 0x200;
            }
            self->accelerationY = 0;
            break;
        }
        DestroyEntity(self);
        break;

    case 1:
        if (!(--self->unk7C.u)) {
            DestroyEntity(self);
            break;
        }

        if (self->unk3C != 0) {
            if (D_80072F20.unk0C & 0x02000000) {
                posX = self->posX.i.hi;
                self->accelerationX += self->unk80.modeS32;

                MoveEntity(self); // argument pass necessary to match

                posX -= self->posX.i.hi;
                if (posX < 0) {
                    posX = -posX;
                }

                if (self->unk7C.u > 16) {
                    self->unk7E.modeU16 += posX;
                    self->hitboxWidth = self->unk7E.modeU16 / 2;
                    self->hitboxHeight = (self->unk7E.modeU16 / 4) + 8;
                } else {
                    self->unk3C = 0;
                }

                if (self->unk48 != 0) {
                    if (D_80072F20.unk56 == 0) {
                        D_80072F20.unk56 = 1;
                        D_80072F20.unk58 = 8;
                        if (g_api.CheckEquipmentItemCount(0x3C, 4)) {
                            D_80072F20.unk58 *= 2;
                        }
                    }
                    D_80072F20.unk10++;
                    self->unk3C = 0;
                }
            } else {
                self->unk3C = 0;
            }
        }

        prim = &g_PrimBuf[self->firstPolygonIndex];
        for (i = 12; i != 0; i--, prim++) {
            *(u16*)&prim->b1 = prim->x0;
            prim->y1 = prim->y0;
            *(s32*)&prim->u1 += *(s32*)&prim->r3;
            *(s32*)&prim->r2 += *(s32*)&prim->x3;
            *(s32*)&prim->r1 += *(s32*)&prim->u1;
            *(s32*)&prim->x1 += *(s32*)&prim->r2;
            *(s16*)&prim->x0 = *(s16*)&prim->b1;
            prim->y0 = prim->y1;
            prim->x2--;

            if ((prim->x2 == 0) && (prim->u0 != 0)) {
                prim->v0--;
                prim->u0--;
                if (!(prim->u0 & 1)) {
                    prim->x0++;
                    prim->y0++;
                }
                prim->x2 = *(s32*)&prim->y2;
            }
        }
    }
}

void EntityUnkId08(Entity* entity) {
    ObjInit2* objInit = &D_8018125C[entity->subId];

    if (entity->step == 0) {
        InitializeEntity(D_80180458);
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
            entity->unk19 = (u8)(entity->unk19 | 4);
        }
    }
    func_80194394(objInit->unk10, entity);
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8019BBA4);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8019BED4);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8019C2BC);

POLY_GT4* func_8019C40C(POLY_GT4* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = (POLY_GT4*)poly->tag;
        } else {
            return poly;
        }
    }
    return NULL;
}

POLY_GT4* func_8019C43C(POLY_GT4* poly, u8 index) {
    if (poly) {
        s32 index_ = index;
    loop_2:
        if (poly->p3 == 0) {
            POLY_GT4* var_v0 = NULL;
            POLY_GT4* firstPoly = poly;
            s32 i = 1;
            if (i < index_) {
                do {
                    poly = (POLY_GT4*)poly->tag;
                    if (!poly)
                        return NULL;
                } while (poly->p3 == 0 && ++i < index);
            }
            var_v0 = firstPoly;
            if (i == index_)
                return var_v0;
        }
        poly = (POLY_GT4*)poly->tag;
        if (poly) {
            goto loop_2;
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8019C4B8);

void func_8019C540(POLY_GT4* poly) {
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

void func_8019C620(POLY_GT4* poly) {
    func_8019C540(poly);
    poly->p3 = 8;
    ((POLY_GT4*)poly->tag)->p3 = 1;
    ((POLY_GT4*)poly->tag)->code = 2;
    ((POLY_GT4*)poly->tag)->pad3 = 0xA;
}

void func_8019C674(POLY_GT4* poly) {
    poly->p3 = 0;
    poly->pad3 = 8;
    ((POLY_GT4*)poly->tag)->p3 = 0;
    ((POLY_GT4*)poly->tag)->code = 4;
    ((POLY_GT4*)poly->tag)->pad3 = 8;
}

s32 func_8019C6A0(s32 arg0, u8 arg1) {
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
