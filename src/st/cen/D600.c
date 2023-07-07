/*
 * File: D600.c
 * Overlay: CEN
 * Description: Center Cube Area (Final Boss)
 */

#include "cen.h"
#include "game.h"

// background block of rock
void EntityBackgroundBlock(Entity* self) {
    ObjInit2* obj = &D_80180490[self->params].animSet;

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

        if (self->params == 1) {
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

void func_8018F8EC(u16 index) {
    Unkstruct8* t = &g_CurrentRoomTileLayout;
    u16 tilePos = 0x5B6;
    u16* tileLayoutPtr = &D_8018068C[index * 4];
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            t->fg[tilePos] = *tileLayoutPtr;
            tileLayoutPtr++;
            tilePos++;
        }
        tilePos += 0x2C;
    }
}

// platform that lifts you into chamber, starts cutscene, gives you holy glasses
void EntityPlatform(Entity* self) {
    Unkstruct8* roomLayout = &g_CurrentRoomTileLayout;
    Entity* player = &PLAYER;
    Primitive* prim;
    s16 primIndex;
    s16 temp_a0;
    s16 temp_s1;
    s16 temp_v0;
    s16 temp_v1_4;
    u16 temp_a1;

    self->posY.i.hi -= 8;
    temp_a1 = func_80195318(self, 0x20, 0x11, 4);
    temp_s1 = player->posX.i.hi + g_Camera.posX.i.hi;
    temp_v0 = self->posY.i.hi + g_Camera.posY.i.hi;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex != -1) {
            InitializeEntity(D_80180434);
            self->animSet = ANIMSET_OVL(2);
            self->animCurFrame = 9;
            self->zPriority = 0x80;

            if (D_8003BDEC[216] != 0) {
                self->step = 9;
            }

            func_8018F8EC(0);
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->flags |= FLAG_HAS_PRIMS;
            prim->tpage = 0xF;
            prim->clut = 2;
            prim->u0 = prim->u2 = 0xA0;
            prim->u1 = prim->u3 = 0xB0;
            prim->v0 = prim->v1 = 0xA1;
            prim->v2 = prim->v3 = 0xA7;
            prim->priority = 0x7F;
            prim->blendMode = 2;
        }
        break;

    case 1:
        if ((func_80194564() < 32) &&
            ((self->posY.i.hi - player->posY.i.hi) < 80)) {
            D_8003C8B8 = 0;
            *D_80097400 = 1;
            if (g_Player_unk0C & 1) {
                g_Player.D_80072EF4 = 8;
            } else if (g_Player_unk0C & 2) {
                g_Player.D_80072EF4 = 4;
            } else if (g_Player_unk0C & 4) {
                g_Player.D_80072EF4 = 2;
            } else if (temp_s1 > 384) {
                g_Player.D_80072EF4 = 0x8000;
            } else if (temp_s1 < 384) {
                g_Player.D_80072EF4 = 0x2000;
            } else {
                g_Player.D_80072EF4 = 0;
            }
            g_Entities[1].ext.generic.unk7C.S8.unk0 = 0;
            g_Player.D_80072EFC = 1;
            self->step++;
        }
        break;

    case 2:
        g_Player.D_80072EF4 = 0;
        if (g_Player_unk0C & 7) {
            if (g_blinkTimer & 1) {
                if (g_Player_unk0C & 1) {
                    g_Player.D_80072EF4 = 8;
                } else if (g_Player_unk0C & 2) {
                    g_Player.D_80072EF4 = 4;
                } else if (g_Player_unk0C & 4) {
                    g_Player.D_80072EF4 = 2;
                }
            }
        } else {
            if ((temp_a1 != 0) || (g_Player.pl_vram_flag & 1)) {
                if (temp_s1 > 384) {
                    g_Player.D_80072EF4 = 0x8000;
                } else if (temp_s1 < 384) {
                    g_Player.D_80072EF4 = 0x2000;
                }
                self->step++;
            }
        }
        g_Player.D_80072EFC = 1;
        break;

    case 3:
        if (g_Player.D_80072EF4 == 0x8000) {
            if (temp_s1 <= 384) {
                g_Player.D_80072EF4 = 0;
            }
        } else if ((g_Player.D_80072EF4 == 0x2000) && (temp_s1 >= 384)) {
            g_Player.D_80072EF4 = 0;
        }
        if (g_Player.D_80072EF4 == 0) {
            g_Player.D_80072EF4 = 0x8000;
            player->posX.i.hi = 384 - roomLayout->unkA;
            self->step++;
            g_api.PlaySfx(0x60D);
            D_8019D424 |= 1;
            roomLayout->unk48 = ((s16)roomLayout->unkE + 0x100);
            func_8018F8EC(0);
        }
        g_Player.D_80072EFC = 1;
        break;

    case 4:
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 1;
        player->posX.i.hi = 384 - roomLayout->unkA;
        if (temp_v0 > 496) {
            self->posY.i.hi--;
            player->posY.i.hi--;
            D_8009748E[0]--;
        } else {
            g_api.PlaySfx(0x64F);
            if (player->facing == 0) {
                g_Player.D_80072EF4 = 0x8000;
            }
            D_8019D424 |= 4;
            self->step++;
        }
        func_8018F890(0x200);
        break;

    case 5:
        func_8018F890(0x200);
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 1;

        if (D_8019D424 & 8) {
            CreateEntityFromCurrentEntity(E_EQUIP_ITEM_DROP, &g_Entities[204]);
            g_Entities[204].params = ITEM_HOLY_GLASSES;
            g_Entities[204].step = 5;
            g_Entities[204].flags = 0;
            self->step++;
        }
        break;

    case 6:
        if (D_8019D424 & 2) {
            self->step++;
            g_api.PlaySfx(0x60D);
        }
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 1;
        break;

    case 7:
        if (temp_v0 < 592) {
            self->posY.i.hi++;
            player->posY.i.hi++;
            *D_8009748A += 1;
        } else {
            D_8003C8B8 = 1;
            if (*D_80097400 != 0) {
                *D_80097400 = 0;
            }
            g_Entities[1].ext.generic.unk7C.S8.unk0 = 1;
            self->step++;
            g_api.PlaySfx(0x64F);
        }
        func_8018F890(0x300);
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 1;
        break;

    case 8:
        func_8018F890(0x300);
        if (roomLayout->unk48 == 0x300) {
            self->step++;
        }
        break;

    case 9:
        break;
    }

    prim = &g_PrimBuf[self->primIndex];
    temp_a0 = self->posX.i.hi - 8;
    temp_v1_4 = self->posX.i.hi + 8;
    self->posY.i.hi += 8;
    prim->x0 = prim->x2 = temp_a0;
    prim->x1 = prim->x3 = temp_v1_4;
    prim->y0 = prim->y1 = self->posY.i.hi + 15;
    prim->y2 = prim->y3 = 0x268 - roomLayout->unkE;
}

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
        self->animSet = ANIMSET_OVL(1);
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
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->objectRoomIndex];
        if (entity->objectId == 0) {
            func_80192A3C(entity, layoutObj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->objectRoomIndex];
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
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->objectRoomIndex];
        if (entity->objectId == 0) {
            func_80192A3C(entity, layoutObj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->objectRoomIndex];
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
        if ((D_8019C768[1] != 0xFFFE) && ((s32)D_8019C768[1] >= arg0)) {
            break;
        }

        D_8019C768 += 5;
    }
}

void func_80193030(s16 arg0) {
    while (true) {
        if ((D_8019C768[1] != 0xFFFF) &&
            ((arg0 >= D_8019C768[1]) || !(D_8019C768[1] != 0xFFFE))) {
            break;
        }
        D_8019C768 -= 5;
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
        if ((D_8019C768[1] == 0xFFFF) || (arg0 < D_8019C768[1])) {
            return;
        }

        expected = 0;
        flag = (D_8019C768[3] >> 8) + 0xFF;
        if ((flag == 0xFF) ||
            (g_entityDestroyed[flag >> 5] & (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInHorizontalRange(D_8019C768);
        }
        D_8019C768 += 5;
    }
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80193184);

void InitRoomEntities(s32 objLayoutId) {
    u16* pObjLayoutStart = D_801801EC[objLayoutId];
    Unkstruct8* currentRoomTileLayout = &g_CurrentRoomTileLayout;
    s16 temp_s0;
    s16 arg0;
    s16 i;
    u16* temp_v1;

    D_8019C764 = pObjLayoutStart;
    D_8019C768 = D_801802C0[objLayoutId];

    if (*pObjLayoutStart != 0xFFFE) {
        D_8019C764 = pObjLayoutStart + 1;
        arg0 = Random() & 0xFF;
        for (i = 0; true; i++) {
            temp_v1 = D_8019C764;
            D_8019C764 = temp_v1 + 1;
            arg0 -= temp_v1[0];
            if (arg0 < 0) {
                break;
            }
            D_8019C764 = temp_v1 + 3;
        }
        D_8019C764 = (temp_v1[2] << 0x10) + temp_v1[1];
        D_8019C768 += i * 2 + 2;
        D_8019C768 = (D_8019C768[1] << 0x10) + D_8019C768[0];
    }
    arg0 = currentRoomTileLayout->unkA;
    temp_s0 = arg0 + 0x140;
    i = arg0 - 0x40;
    if (i < 0) {
        i = 0;
    }

    D_8019C76C = 0;
    D_8019C770 = 0;
    func_80192D30(i);
    func_80192DD4(temp_s0);
    func_80192FE4(currentRoomTileLayout->unkE + 0x120);
}

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

    if (entity->flags & FLAG_HAS_PRIMS) {
        g_api.FreePrimitives(entity->primIndex);
    }

    ptr = (u32*)entity;
    length = sizeof(Entity) / sizeof(u32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

void func_801942D0(s16 index) {
    Entity* entity = &g_Entities[index];

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

u16 func_80194E44(u16 arg0, u16 arg1, u16 arg2) {
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

void SetStep(u8 step) {
    Entity* entity = g_CurrentEntity;

    entity->step = step;
    entity->step_s = 0;
    entity->animFrameIdx = 0;
    entity->animFrameDuration = 0;
}

void func_80194EC4(u8 arg0) {
    Entity* entity = g_CurrentEntity;

    entity->step_s = arg0;
    entity->animFrameIdx = 0;
    entity->animFrameDuration = 0;
}

void func_80194EE0(u16 arg0, u16 arg1) {
    Entity* entity;

    if (arg1 != 0) {
        func_8019A328(arg1);
    }
    if (arg0 == 0xFF) {
        DestroyEntity(g_CurrentEntity);
        return;
    }
    entity = g_CurrentEntity;
    entity->unk19 = 0;
    entity->objectId = 2;
    entity->pfnUpdate = EntityExplosion;
    entity->params = arg0;
    entity->animCurFrame = 0;
    g_CurrentEntity->step = 0;
    g_CurrentEntity->step_s = 0;
}

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
            if (collider.effects & EFFECT_UNK_0002 &&
                ((!(collider.effects & EFFECT_UNK_8000)) || (i != 0))) {
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

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80195318);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8019565C);

void func_80195714(void) {
    s32 temp_v1;
    Entity* entity;

    entity = g_CurrentEntity;
    if (entity->accelerationY >= 0) {
        temp_v1 =
            entity->ext.generic.unk88.S16.unk0 + entity->ext.generic.unk84.unk;
        entity->ext.generic.unk84.unk = temp_v1;
        entity->accelerationX = temp_v1;
        if (temp_v1 == 0x10000 || temp_v1 == -0x10000) {
            entity->ext.generic.unk88.S16.unk0 =
                -entity->ext.generic.unk88.S16.unk0;
        }
        entity = g_CurrentEntity;
    }

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

void CollectSubweapon(u16 subWeaponIdx) {
    Entity* player = &PLAYER;
    u16 subWeapon;

    g_api.PlaySfx(NA_SE_PL_IT_PICKUP);
    subWeapon = g_Status.subWeapon;
    g_Status.subWeapon = D_80180EEC[subWeaponIdx];

    if (subWeapon == g_Status.subWeapon) {
        subWeapon = 1;
        g_CurrentEntity->unk6D = 0x10;
    } else {
        subWeapon = D_80180F1C[subWeapon];
        g_CurrentEntity->unk6D = 0x60;
    }

    if (subWeapon != 0) {
        g_CurrentEntity->params = subWeapon;
        g_CurrentEntity->posY.i.hi = player->posY.i.hi + 12;
        SetStep(7);
        g_CurrentEntity->accelerationY = -0x28000;
        g_CurrentEntity->animCurFrame = 0;
        g_CurrentEntity->ext.generic.unk88.S16.unk2 = 5;
        if (player->facing != 1) {
            g_CurrentEntity->accelerationX = -0x20000;
            return;
        }
        g_CurrentEntity->accelerationX = 0x20000;
        return;
    }
    DestroyEntity(g_CurrentEntity);
}

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
        temp_a0 = self->params + 0xC0;
        self->ext.generic.unkB4 = temp_a0;
        if ((D_8003BEEC[temp_a0 >> 3] >> (temp_a0 & 7)) & 1) {
            DestroyEntity(self);
            return;
        }
        temp_a0_2 = temp_a0 - 0xC0;
        var_a0 = D_801805D8[temp_a0_2];
        if (var_a0 < 128) {
            self->ext.generic.unkB8.unkFuncB8 = EntityPrizeDrop;
        } else {
            self->ext.generic.unkB8.unkFuncB8 = EntityEquipItemDrop;
            var_a0 -= 128;
        }
        self->params = var_a0 + 0x8000;
    } else {
        temp_a0_2 = self->ext.generic.unkB4;
        if (self->step < 5) {
            if (self->hitFlags != 0) {
                var_a0 = self->ext.generic.unkB4;
                D_8003BEEC[temp_a0_2 >> 3] |= 1 << (var_a0 & 7);
                self->step = 5;
            }
        }
    }
    self->ext.generic.unkB8.unkFuncB8(self);
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityUnkId0E);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80198084);

extern u16 D_80180440[];
void EntityUnkId13(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180440);
        entity->ext.generic.unk8C.modeU16.unk0 =
            entity->ext.generic.unk80.entityPtr->objectId;
    case 1:
        if (entity->ext.generic.unk7C.U8.unk0++ >= 5) {
            Entity* newEntity =
                AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
            if (newEntity != NULL) {
                func_80193538(E_EXPLOSION, entity, newEntity);
                newEntity->objectId = E_EXPLOSION;
                newEntity->pfnUpdate = EntityExplosion;
                newEntity->params = entity->params;
            }
            entity->ext.generic.unk7C.U8.unk0 = 0;
        }
        entity->posX.i.hi = entity->ext.generic.unk80.entityPtr->posX.i.hi;
        entity->posY.i.hi = entity->ext.generic.unk80.entityPtr->posY.i.hi;
        if (entity->ext.generic.unk80.entityPtr->objectId !=
            entity->ext.generic.unk8C.modeU16.unk0) {
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

u8 func_801989AC(s32 arg0) {
    Collider collider;
    u32 bits_67;
    u32 bits_45;
    u32 bits_23;
    u8 bits_01;
    u16 collEff;

    MoveEntity();
    bits_67 = 0;
    bits_23 = 0;
    bits_45 = 0;
    bits_01 = arg0 & 3;
    collEff = 0;
    switch (bits_01) {
    case 0:
        g_CurrentEntity->posY.i.hi += 3;
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != 0) {
            collEff = collider.effects;
            g_CurrentEntity->posY.i.hi += collider.unk18;
            g_api.CheckCollision(
                g_CurrentEntity->posX.i.hi,
                (s16)(g_CurrentEntity->posY.i.hi - 4), &collider, 0);
            if (collider.effects & EFFECT_UNK_0002) {
                bits_67 = 0x40;
                if (g_CurrentEntity->accelerationX > 0) {
                    bits_01 = 2;
                } else {
                    bits_01 = 3;
                    g_CurrentEntity->accelerationX =
                        -g_CurrentEntity->accelerationX;
                }
                g_CurrentEntity->accelerationY =
                    -g_CurrentEntity->accelerationX;
                g_CurrentEntity->accelerationX = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posX.val -= g_CurrentEntity->accelerationX;
            if (g_CurrentEntity->accelerationX > 0) {
                bits_01 = 3;
            } else {
                bits_01 = 2;
                g_CurrentEntity->accelerationX =
                    -g_CurrentEntity->accelerationX;
            }
            g_CurrentEntity->accelerationY = g_CurrentEntity->accelerationX;
            g_CurrentEntity->accelerationX = 0;
        }
        break;

    case 1:
        g_CurrentEntity->posY.i.hi -= 3;
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != 0) {
            collEff = collider.effects;
            g_CurrentEntity->posY.i.hi += collider.unk20;
            g_api.CheckCollision(
                g_CurrentEntity->posX.i.hi,
                (s16)(g_CurrentEntity->posY.i.hi + 4), &collider, 0);
            if (collider.effects & EFFECT_UNK_0002) {
                bits_67 = 0x40;
                if (g_CurrentEntity->accelerationX > 0) {
                    bits_01 = 2;
                } else {
                    bits_01 = 3;
                    g_CurrentEntity->accelerationX =
                        -g_CurrentEntity->accelerationX;
                }
                g_CurrentEntity->accelerationY = g_CurrentEntity->accelerationX;
                g_CurrentEntity->accelerationX = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posX.val -= g_CurrentEntity->accelerationX;
            if (g_CurrentEntity->accelerationX > 0) {
                bits_01 = 3;
            } else {
                bits_01 = 2;
                g_CurrentEntity->accelerationX =
                    -g_CurrentEntity->accelerationX;
            }
            g_CurrentEntity->accelerationY = -g_CurrentEntity->accelerationX;
            g_CurrentEntity->accelerationX = 0;
        }
        break;

    case 2:
        g_CurrentEntity->posX.i.hi += 3;
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != 0) {
            collEff = collider.effects;
            g_CurrentEntity->posX.i.hi += collider.unk14;
            g_api.CheckCollision((s16)(g_CurrentEntity->posX.i.hi - 4),
                                 g_CurrentEntity->posY.i.hi, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                bits_67 = 0x40;
                if (g_CurrentEntity->accelerationY > 0) {
                    bits_01 = 0;
                } else {
                    bits_01 = 1;
                    g_CurrentEntity->accelerationY =
                        -g_CurrentEntity->accelerationY;
                }
                g_CurrentEntity->accelerationX =
                    -g_CurrentEntity->accelerationY;
                g_CurrentEntity->accelerationY = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posY.val -= g_CurrentEntity->accelerationY;
            if (g_CurrentEntity->accelerationY > 0) {
                bits_01 = 1;
            } else {
                bits_01 = 0;
                g_CurrentEntity->accelerationY =
                    -g_CurrentEntity->accelerationY;
            }
            g_CurrentEntity->accelerationX = g_CurrentEntity->accelerationY;
            g_CurrentEntity->accelerationY = 0;
        }
        break;

    case 3:
        g_CurrentEntity->posX.i.hi -= 3;
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != 0) {
            collEff = collider.effects;
            g_CurrentEntity->posX.i.hi += collider.unk1C;
            g_api.CheckCollision((s16)(g_CurrentEntity->posX.i.hi + 4),
                                 g_CurrentEntity->posY.i.hi, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                bits_67 = 0x40;
                if (g_CurrentEntity->accelerationY > 0) {
                    bits_01 = 0;
                } else {
                    bits_01 = 1;
                    g_CurrentEntity->accelerationY =
                        -g_CurrentEntity->accelerationY;
                }
                g_CurrentEntity->accelerationX = g_CurrentEntity->accelerationY;
                g_CurrentEntity->accelerationY = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posY.val -= g_CurrentEntity->accelerationY;
            if (g_CurrentEntity->accelerationY > 0) {
                bits_01 = 1;
            } else {
                bits_01 = 0;
                g_CurrentEntity->accelerationY =
                    -g_CurrentEntity->accelerationY;
            }
            g_CurrentEntity->accelerationX = -g_CurrentEntity->accelerationY;
            g_CurrentEntity->accelerationY = 0;
        }
    }

    if (collEff & EFFECT_UNK_8000) {
        bits_23 = 4;
    }
    if (collEff & EFFECT_UNK_1000) {
        bits_23 = 8;
    }
    if (collEff & EFFECT_UNK_2000) {
        bits_23 = 0xC;
    }
    if (collEff & EFFECT_UNK_0800) {
        bits_45 = 0x20;
    }
    if (collEff & EFFECT_UNK_4000) {
        bits_45 = 0x10;
    }
    bits_01 = (bits_45 + (bits_23 + (bits_67 + bits_01)));
    return bits_01;
}

// ID 06
INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityIntenseExplosion);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8019902C);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_801990F8);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_801991C0);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80199278);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80199450);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_80199A30);

void ClutLerp(RECT* rect, u16 palIdxA, u16 palIdxB, s32 steps, u16 offset) {
    u16 buf[COLORS_PER_PAL];
    RECT bufRect;
    s32 factor;
    u32 t;
    u32 r, g, b;
    s32 i, j;
    u16 *palA, *palB;

    bufRect.x = rect->x;
    bufRect.w = COLORS_PER_PAL;
    bufRect.h = 1;

    palA = g_Clut + palIdxA * COLORS_PER_PAL;
    palB = g_Clut + palIdxB * COLORS_PER_PAL;

    for (i = 0; i < steps; i++) {
        factor = i * 4096 / steps;
        for (j = 0; j < COLORS_PER_PAL; j++) {
            r = (palA[j] & 0x1F) * (4096 - factor) + (palB[j] & 0x1F) * factor;
            g = ((palA[j] >> 5) & 0x1F) * (4096 - factor) +
                ((palB[j] >> 5) & 0x1F) * factor;
            b = ((palA[j] >> 10) & 0x1F) * (4096 - factor) +
                ((palB[j] >> 10) & 0x1F) * factor;

            t = palA[j] & 0x8000;
            t |= palB[j] & 0x8000;

            buf[j] = t | (r >> 12) | ((g >> 12) << 5) | ((b >> 12) << 10);
        }

        bufRect.y = rect->y + i;
        LoadImage(&bufRect, buf);
        D_8003C104[offset + i] = GetClut(bufRect.x, bufRect.y);
    }
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8019A328);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8019A420);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityStageNamePopup);
