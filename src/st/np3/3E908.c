#include "np3.h"

void EntityInventoryDrop(Entity* self) {
    u16 itemId = self->subId & 0x7FFF;
    s32 firstPolygonIndex;
    Collider collider;
    POLY_GT4* poly;
    s32* itemName;
    s16 index;
    s32 vramX;
    s32 vramY;
    u8 left;
    u8 right;
    u16 top;
    u8 bottom;
    u8 temp_v0_6;
    s16 temp_a0;
    s32* unk;

    if (((self->step - 2) < 3U) && (self->unk48 != 0)) {
        self->step = 5;
    }

    switch (self->step) {
    case 0:
        if (g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
            self->pfnUpdate = EntityPriceDrop;
            self->subId = 0;
            self->objectId = 3;
            func_801BD114(0);
            EntityPriceDrop(self);
            return;
        }
        InitializeEntity(D_80180A48);
        self->unk7C.s = 0;
        break;

    case 1:
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi, &collider, 0);

        if (!(collider.unk0 & 7)) {
            for (index = 0; index < 32; index++) {
                if (D_801D33F4[index] == 0) {
                    break;
                }
            }

            if (index >= 32) {
                DestroyEntity(self);
                return;
            }

            if (*(s16*)&self->unk94 != 0) {
                temp_a0 = *(s16*)&self->unk94;
                temp_a0--;
                D_8003BF9C[temp_a0 >> 3] |= 1 << (temp_a0 & 7);
            }

            firstPolygonIndex = g_api.AllocPrimitives(4, 1);
            if (firstPolygonIndex == (-1)) {
                DestroyEntity(self);
                return;
            }

            self->flags |= FLAG_FREE_POLYGONS;
            self->firstPolygonIndex = firstPolygonIndex;
            D_801D33F4[index] = 0x1E0;
            self->unk8C.modeU16.unk0 = index;

            if (itemId < 169) {
                g_api.func_800EB534(g_api.D_800A4B04[itemId].icon,
                                    g_api.D_800A4B04[itemId].palette, index);
            } else {
                itemId -= 169;
                g_api.func_800EB534(g_api.D_800A7718[itemId].icon,
                                    g_api.D_800A7718[itemId].palette, index);
            }

            poly = &g_PrimBuf[firstPolygonIndex];
            vramX = ((temp_v0_6 = index) & 7) * 0x10;
            vramY = (temp_v0_6 & 0x18) * 2;

            left = vramX | 1;
            right = vramX | 0xF;
            top = 0x81;
            top = vramY | top;
            bottom = vramY | 0x8F;

            poly->tpage = 0x1A;
            poly->v3 = bottom;
            poly->clut = index + 464;
            poly->u0 = poly->u2 = left;
            poly->u1 = poly->u3 = right;
            poly->v1 = top;
            poly->v2 = bottom;
            poly->v0 = top;
            poly->pad2 = 0x80;
            poly->pad3 = 6;

            self->unk7C.s = 128;
            self->step++;
            break;
        }
        DestroyEntity(self);
        break;

    case 2:
        if (self->accelerationY < 0) {
            g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi - 7,
                                 &collider, 0);
            if (collider.unk0 & 5) {
                self->accelerationY = 0;
            }
        }

        MoveEntity();

        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi + 7, &collider,
                             0);

        if ((collider.unk0 & 5) && (self->accelerationY > 0)) {
            self->accelerationX = 0;
            self->accelerationY = 0;
            self->posY.i.hi += *(u16*)&collider.unk18;
            self->unk80.modeS8.unk0 = 240;
            self->step++;
        } else {
            FallEntity();
        }

        func_801BD430(D_80181E74, 2);
        break;

    case 3:
        func_801BDA08(1);
        if (!(self->subId & 0x8000)) {
            if (!(--self->unk80.modeS8.unk0 & 255)) {
                self->unk80.modeS8.unk0 = 0x50;
                self->step++;
            }
        } else {
            D_801D33F4[self->unk8C.modeS16.unk0] = 0x10;
        }
        break;

    case 4:
        func_801BDA08(1);
        if (self->unk80.modeS8.unk0 += 255) {
            poly = &g_PrimBuf[self->firstPolygonIndex];
            if (self->unk80.modeS8.unk0 & 2) {
                poly->pad3 = 8;
            } else {
                poly->pad3 = 2;
            }
        } else {
            DestroyEntity(self);
        }
        break;

    case 5:
        unk = &D_80097410;
        if (*unk != 0) {
            g_api.FreePrimitives(D_80097414);
            *unk = 0;
        }

        g_api.PlaySfx(NA_SE_PL_IT_PICKUP);

        if (itemId < 169) {
            itemName = g_api.D_800A4B04[itemId].name;
            g_api.AddToInventory(itemId, 0);
        } else {
            itemId -= 169;
            itemName = g_api.D_800A7718[itemId].name;
            g_api.AddToInventory(itemId, 2);
        }

        func_801C3E14(itemName, 1);
        DestroyEntity(self);
        break;
    }

    if (self->step >= 2) {
        if (self->unk7C.u != 0) {
            self->unk7C.u--;
        }
        func_801BE864(self, self->unk7C.u);
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801BEEF0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", EntityRelicOrb);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", EntityHeartDrop);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", EntityUnkId0E);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C02F4);

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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C04F4);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C0624);

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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C07FC);

void func_801C08F0(Entity* self) {
    s16 firstPolygonIndex;
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180A54);
        firstPolygonIndex = g_api.AllocPrimitives(2, 1);
        if (firstPolygonIndex != -1) {
            prim = &g_PrimBuf[firstPolygonIndex];
            self->firstPolygonIndex = firstPolygonIndex;
            self->unk3C = 0;
            *(s32*)&self->unk7C = prim;
            self->flags |= FLAG_FREE_POLYGONS;
            while (prim != NULL) {
                prim->x0 = prim->x1 = self->posX.i.hi;
                prim->y0 = prim->y1 = self->posY.i.hi;
                prim->r0 = 64;
                prim->r1 = 0;
                prim->g0 = 64;
                prim->g1 = 0;
                prim->b0 = 255;
                prim->b1 = 16;
                prim->priority = self->zPriority + 1;
                prim->blendMode |= 0x37;
                prim = prim->next;
            }
        }
        break;

    case 1:
        prim = (Primitive*)*(s32*)&self->unk7C.s;
        if (func_801C02F4(&D_80182000, 0) & 255) {
            prim->y1 += 2;
            if (self->unk2E == 0) {
                func_801C04F4(self, 1, 2, 0, 0, 3, 0);
                self->unk2E = 1;
            }
        } else {
            self->accelerationY += 0x400;
            self->posY.val += self->accelerationY;
            if ((prim->y0 - prim->y1) >= 9) {
                prim->y1 = prim->y0 - 8;
            }
        }

        prim->x0 = self->posX.i.hi;
        prim->x1 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;

        if (prim->y0 < prim->y1) {
            g_api.FreePrimitives(self->firstPolygonIndex);
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C0B20);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C0C1C);

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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C129C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C1368);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C1430);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C14E8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C16C0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C1CA0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C23A0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C2598);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C2690);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", EntityStageNamePopup);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", EntityAbsorbOrb);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", EntityEnemyBlood);

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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C3E14);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C4144);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C424C);

// EntitySplashWater
INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C4DCC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C56D8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C5BC4);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C5F58);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C61B4);

s32 func_801C6458(s16 yVector) {
    s16 newY = yVector + g_CurrentEntity->posY.i.hi;
    s32 expectedResult = 0;
    Collider collider;
    Entity* newEntity;
    s32 res;

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi, newY, &collider, 0);
    res = expectedResult == (collider.unk0 & 1);

    if (collider.unk0 & 8) {
        if (*(u8*)&g_CurrentEntity->unkA0 == 0) {
            newEntity = AllocEntity(&D_8007DE38, &D_8007DE38[24]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x33, g_CurrentEntity, newEntity);
                newEntity->posY.i.hi += yVector;
                newEntity->zPriority = g_CurrentEntity->zPriority;
            }
            g_api.PlaySfx(0x7C2);
            *(u8*)&g_CurrentEntity->unkA0 = 1;
        }
    }
    return res;
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C6564);

// some sort of explosion
void EntityExplosion2(Entity* entity, s32 arg1) {
    POLY_GT4* poly;
    s16 firstPolygonIndex;

    if (entity->step == 0) {
        InitializeEntity(D_80180AB4);
        entity->animCurFrame = 0;
        entity->unk3C = 0;
        entity->zPriority += 4;
        if (entity->subId != 0) {
            firstPolygonIndex = g_api.AllocPrimitives(4, 2);
            if (firstPolygonIndex == -1) {
                DestroyEntity(entity);
                return;
            }
            poly = &g_PrimBuf[firstPolygonIndex];
            entity->firstPolygonIndex = firstPolygonIndex;
            *(s32*)&entity->unk7C.s = poly;
            entity->flags |= FLAG_FREE_POLYGONS;
            func_801D2684(poly, firstPolygonIndex);
            poly->u0 = 0;
            poly->u1 = 0x20;
            poly->tpage = 0x1A;
            poly->clut = 0x1FF;
            poly->v3 = poly->v2 = 0x20;
            poly->v1 = poly->v0 = 0;
            poly->u2 = poly->u0;
            poly->u3 = poly->u1;
            *(s16*)&((POLY_GT4*)poly->tag)->r2 = 0x40;
            *(s16*)&((POLY_GT4*)poly->tag)->b2 = 0x40;
            *(s16*)&((POLY_GT4*)poly->tag)->u1 = 0;
            ((POLY_GT4*)poly->tag)->b3 = 0x60;
            ((POLY_GT4*)poly->tag)->x1 = (u16)entity->posX.i.hi;
            ((POLY_GT4*)poly->tag)->y0 = (u16)entity->posY.i.hi;
            poly->pad2 = entity->zPriority - 4;
            poly->pad3 = 6;
        }
    }

    if (entity->subId != 0) {
        poly = *(s32*)&entity->unk7C.s;
        func_801D1F38(poly);
        ((POLY_GT4*)poly->tag)->b3 += 252;
        *(s16*)&((POLY_GT4*)poly->tag)->u1 -= 128;
        if (((POLY_GT4*)poly->tag)->b3 < 16) {
            poly->pad3 = 8;
        }
    }

    entity->unk84.U8.unk0++;
    if (!(entity->unk84.U8.unk0 % 4)) {
        entity->posY.i.hi++;
    }

    if (AnimateEntity(D_801822B0, entity) == 0) {
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C7880);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", func_801C7954);

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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", EntityMerman);

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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3E908", EntityBoneScimitar);

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