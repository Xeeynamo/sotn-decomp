#include "stage.h"

PfnEntityUpdate PfnEntityUpdates[];

// if self->subId & 0x8000 then the item will not disappear
// self->unk80.modeS8.unk0: frames left before the prize disappear
u16 D_8018044C[];
u16 D_80180DF4[];
u8* D_80180E58[];
u16 D_80180EB8[];
void EntityPrizeDrop(Entity* self) {
    Collider collider;
    Primitive* prim;
    s16 firstPrimIndex;
    s16 var_a2;
    u16 itemId;
    s16 temp_a0;

    itemId = self->subId & 0x7FFF;
    if (self->step != 0) {
        AnimateEntity(D_80180E58[itemId], self);
    }
    if (self->step - 2 < 3U && self->unk48 != 0) {
        self->step = 5;
    }
    self->palette = 0;
    if ((u8)self->unk6D >= 0x18 && !(D_8003C8C4 & 2) && self->subId != 1) {
        self->palette = 0x815F;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_8018044C);
        self->zPriority = g_zEntityCenter.S16.unk0 - 0x14;
        self->blendMode = 0;
        if (itemId >= 0x18) {
            self->subId = 0;
            itemId = 0;
        }
        if (itemId > 13 && itemId < 23 && itemId == D_80180DF4[D_80097BFC]) {
            self->subId = itemId = 1;
        }
        if (itemId == 0 || itemId == 2) {
            self->hitboxWidth = 4;
        }
        break;

    case 1:
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi, &collider, 0);
        if (collider.unk0 & 7) {
            DestroyEntity(self);
        } else {
            self->step++;
            if (LOH(self->unk94) != 0) {
                temp_a0 = LOH(self->unk94) - 1;
                g_zEntityCenter.S16 = g_zEntityCenter.S16;
                D_8003BF9C[temp_a0 >> 3] |= 1 << (temp_a0 & 7);
            }
        }
        if (itemId == 0) {
            self->unk84.unk = -0x10000;
            self->unk88.S16.unk0 = 0x800;
        }
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
        if (itemId != 0) {
            if (collider.unk0 & 5 && self->accelerationY > 0) {
                self->accelerationX = 0;
                self->accelerationY = 0;
                self->posY.i.hi += LOH(collider.unk18);
                self->unk80.modeS8.unk0 = 0xF0;
                self->step++;
            } else {
                FallEntity();
            }
            func_8018C55C(D_80180EB8, 2);
        } else if (collider.unk0 & 5) {
            self->posY.i.hi += LOH(collider.unk18);
            self->unk80.modeS8.unk0 = 0x60;
            self->step++;
        } else {
            func_8018CAB0();
        }
        break;

    case 3:
        func_8018CB34(itemId);
        if (!(self->subId & 0x8000) && !(--self->unk80.modeS8.unk0)) {
            self->unk80.modeS8.unk0 = itemId == 0 ? 0x40 : 0x50;
            self->step++;
        }
        break;

    case 4:
        func_8018CB34(itemId);
        if (self->unk80.modeS8.unk0 += 255) {
            if (self->unk80.modeS8.unk0 & 2) {
                self->animCurFrame = 0;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        break;

    case 5:
        if (itemId == 0 || itemId == 1) {
            CollectHeart(itemId);
        } else if (itemId < 12) {
            CollectGold(itemId);
        } else if (itemId == 12) {
            CollectHeartVessel();
        } else if (itemId < 14) {
            DestroyCurrentEntity();
        } else if (itemId < 23) {
            func_8018CDEC(itemId);
        } else if (itemId == 23) {
            CollectLifeVessel();
        } else {
            DestroyEntity(self);
            return;
        }
        break;

    case 6:
    case 7:
        switch (self->unk2E) {
        case 0:
            self->animCurFrame = 0;
            if (itemId > 13 && itemId < 23) {
                if (itemId == D_80180DF4[D_80097BFC]) {
                    self->subId = itemId = 1;
                }
            }
            firstPrimIndex = g_api.AllocPrimitives(4, 1);
            if (firstPrimIndex != -1) {
                self->firstPolygonIndex = firstPrimIndex;
                self->flags |= 0x800000;
                prim = &g_PrimBuf[firstPrimIndex];
                prim->tpage = 0x1A;
                prim->clut = 0x170;
                prim->v2 = prim->v3 = 0x20;
                prim->u1 = prim->u3 = 0x20;
                prim->v0 = prim->v1 = 0;
                prim->u0 = prim->u2 = 0;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0x80;
                prim->blendMode = 8;
                prim->priority = self->zPriority + 1;
                self->unk2E++;
            }
            break;

        case 1:
            MoveEntity();
            g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi + 7,
                                 &collider, 0);
            if (collider.unk0 & 5 && self->accelerationY > 0) {
                self->accelerationX = 0;
                self->accelerationY = 0;
                self->posY.i.hi += LOH(collider.unk18);
                self->unk2E++;
            } else {
                FallEntity();
            }
            func_8018C55C(D_80180EB8, 2);
            self->animCurFrame = 0;
            if (self->unk88.S16.unk2 != 0) {
                self->unk88.S16.unk2--;
            } else {
                prim = &g_PrimBuf[self->firstPolygonIndex];
                prim->x0 = prim->x2 = self->posX.i.hi - 1;
                prim->x1 = prim->x3 = self->posX.i.hi + 1;
                prim->y0 = prim->y1 = self->posY.i.hi - 1;
                prim->y2 = prim->y3 = self->posY.i.hi + 1;
                prim->blendMode = 0x37;
            }
            break;

        case 2:
            func_8018CB34(itemId);
            prim = &g_PrimBuf[self->firstPolygonIndex];
            self->unk88.S16.unk2++;
            if (self->unk88.S16.unk2 < 0x11) {
                var_a2 = self->unk88.S16.unk2;
                self->animCurFrame = 0;
            } else {
                var_a2 = 0x20 - self->unk88.S16.unk2;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->r3 - 8;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = prim->g3 - 8;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->b3 - 8;
            }
            prim->x0 = prim->x2 = self->posX.i.hi - var_a2;
            prim->x1 = prim->x3 = self->posX.i.hi + var_a2;
            prim->y0 = prim->y1 = self->posY.i.hi - var_a2;
            prim->y2 = prim->y3 = self->posY.i.hi + var_a2;
            if (self->unk88.S16.unk2 == 0x20) {
                g_api.FreePrimitives(self->firstPolygonIndex);
                self->unk80.modeS8.unk0 = 0xD0;
                self->step = 3;
                self->unk2E = 0;
                self->flags &= ~0x800000;
            }
            break;
        }

        break;
    }
}

u16 D_80180458[];
s32 D_80180EC4[];
u8* D_80180F70[];
void EntityExplosion(Entity* entity) {
    u16 zPriority;

    if (entity->step == 0) {
        InitializeEntity(D_80180458);
        entity->animSet = 2;
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
        entity->blendMode = 0x30;
        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->blendMode = 0x10;
        }

        zPriority = entity->subId & 0xFF00;
        if (zPriority) {
            entity->zPriority = zPriority >> 8;
        }
        entity->subId &= 15;
        entity->accelerationY = D_80180EC4[entity->subId];
    } else {
        entity->posY.val += entity->accelerationY;
        if (!AnimateEntity(D_80180F70[entity->subId], entity)) {
            DestroyEntity(entity);
        }
    }
}

void func_8018D990(Entity* arg0, s32 renderFlags) {
    POLY_GT4* poly;
    s16 left, top, right, bottom;

    poly = &g_PrimBuf[arg0->firstPolygonIndex];

    left = arg0->posX.i.hi - 7;
    right = arg0->posX.i.hi + 7;
    poly->x2 = left;
    poly->x0 = left;
    poly->x3 = right;
    poly->x1 = right;

    top = arg0->posY.i.hi - 7;
    bottom = arg0->posY.i.hi + 7;
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

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", EntityInventoryDrop);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", func_8018E01C);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", EntityRelicOrb);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", EntityHeartDrop);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", EntityUnkId0E);

u8 func_8018F420(s16* arg0, u8 facing) {
    u8 ret = 0;
    Collider res;
    s16 posX, posY;

    while (*arg0 != 0xFF) {
        ret <<= 1;

        posX = facing ? (g_CurrentEntity->posX.i.hi + *arg0++)
                      : (g_CurrentEntity->posX.i.hi - *arg0++);
        posY = g_CurrentEntity->posY.i.hi + *arg0++;

        g_api.CheckCollision(posX, posY, &res, 0);

        if (res.unk0 & 1) {
            ret |= 1;
        }
    }

    return ret;
}

u16 D_8018047C[];
void func_8018F510(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_8018047C);
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

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", func_8018F620);

// https://decomp.me/scratch/peM5t by stuckpixel
#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", func_8018F750);
#else
extern void func_8018F928(Entity*);
void func_8018F750(Entity* source, s8 count, u16 xOffset, u16 yOffset,
                   s16 xDistance) {
    Entity* entity;
    s32 x, y;
    u8 i;

    x = (u16)source->posX.i.hi + xOffset;
    y = (u16)source->posY.i.hi + yOffset;

    for (i = 0; i < count; i++) {
        entity = AllocEntity(D_8007A958, &D_8007A958[MaxEntityCount]);
        if (entity != NULL) {
            entity->objectId = 21;
            entity->pfnUpdate = func_8018F928;
            entity->posX.i.hi = x;
            entity->posY.i.hi = y;
            entity->subId = i;
            entity->zPriority = source->zPriority + 1;
        }
        x += xDistance;
    }
}
#endif

s32 D_80181020[];
u8 D_80181038[];
u16 D_8018103C[];
void func_8018F838(Entity* entity) {
    if (entity->step == 0) {
        entity->accelerationY = D_80181020[entity->unk94];
        entity->flags = 0x2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = 2;
        entity->animCurFrame = D_80181038[entity->subId];
        entity->blendMode = 0x10;
        entity->step++;
    } else {
        entity->animFrameDuration++;
        entity->posY.val -= entity->accelerationY;

        if (!(entity->animFrameDuration & 1)) {
            entity->animCurFrame++;
        }

        if (D_8018103C[entity->subId] < (s32)entity->animFrameDuration) {
            DestroyEntity(entity);
        }
    }
}

u16 D_80180FF8[];
s32 D_80181008[];
void func_8018F928(Entity* arg0) {
    u16 temp_v0;

    if (arg0->step == 0) {
        arg0->flags = 0x2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        arg0->palette = 0x8195;
        arg0->animSet = 5;
        arg0->animCurFrame = 1U;
        arg0->blendMode = 0x10;
        arg0->unk19 = 3;
        temp_v0 = D_80180FF8[arg0->subId];
        arg0->unk1A = temp_v0;
        arg0->unk1C = temp_v0;
        arg0->accelerationY = D_80181008[arg0->subId];
        arg0->step++;
    } else {
        arg0->animFrameDuration++;
        arg0->posY.val -= arg0->accelerationY;
        if (!(arg0->animFrameDuration & 1)) {
            arg0->animCurFrame++;
        }
        if (arg0->animFrameDuration >= 37) {
            DestroyEntity(arg0);
        }
    }
}

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", func_8018FA1C);

bool func_8018FC4C(Unkstruct6* unk) {
    Collider res;

    FallEntity();
    g_CurrentEntity->posX.val += g_CurrentEntity->accelerationX;
    g_CurrentEntity->posY.val += g_CurrentEntity->accelerationY;

    if (g_CurrentEntity->accelerationY >= 0) {
        s16 posX = g_CurrentEntity->posX.i.hi;
        s16 posY = g_CurrentEntity->posY.i.hi;
        posX += unk->x;
        posY += unk->y;
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

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", func_8018FD48);

void EntityIntenseExplosion(Entity* entity) {
    u32 zPriority;
    if (entity->step == 0) {
        InitializeEntity(D_80180458);
        entity->palette = 0x8170;
        entity->animSet = 5;
        entity->animCurFrame = 1;
        entity->blendMode = 0x30;
        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->blendMode = 0x10;
        }

        zPriority = entity->subId & 0xFF00;
        if (zPriority != 0) {
            entity->zPriority = zPriority >> 8;
        }
        entity->zPriority += 8;
    } else {
        entity->animFrameDuration++;
        entity->posY.val -= 0x4000;

        if ((entity->animFrameDuration & 1) == 0) {
            entity->animCurFrame++;
        }

        if (entity->animFrameDuration >= 37) {
            DestroyEntity(entity);
        }
    }
}

u8 D_8018104C[];
void func_801903C8(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(D_80180458);
        entity->unk6C = 0xF0;
        entity->unk1A = 0x01A0;
        entity->unk1C = 0x01A0;
        entity->animSet = 8;
        entity->animCurFrame = 1;
        entity->zPriority += 16;

        if (entity->subId) {
            entity->palette = entity->subId;
        } else {
            entity->palette = 0x8160;
        }

        entity->step++;
    } else {
        MoveEntity();
        if (!AnimateEntity(D_8018104C, entity)) {
            DestroyEntity(entity);
        }
    }
}

void func_80190494(u16 objectId, Entity* source, Entity* entity) {
    u16 palette;

    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
    entity->unk5A = source->unk5A;
    entity->zPriority = source->zPriority;
    entity->animSet = source->animSet;
    entity->flags = 0x1002000 | FLAG_UNK_04000000 | FLAG_UNK_08000000 |
                    FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                    FLAG_DESTROY_IF_OUT_OF_CAMERA;

    palette = source->palette;
    entity->palette = palette & 0x8000 ? source->unk6A : palette;
}

void func_8019055C(void) {
    s32 temp_s3;
    s8 temp_s4;
    Entity* entity;
    s32 i;

    temp_s4 = Random() & 3;
    temp_s3 = ((Random() & 0xF) << 8) - 0x800;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
        if (entity != NULL) {
            CreateEntityFromEntity(ENTITY_EXPLOSION, g_CurrentEntity, entity);
            entity->unk84.U8.unk1 = 6 - i;
            entity->unk80.modeS16.unk0 = temp_s3;
            entity->unk84.U8.unk0 = temp_s4;
        }
    }
}

u8 D_80180EEC[];
void func_80190614(Entity* self) {
    s32 accelerationX;
    s32 accelerationY;
    s32 temp;

    if (self->step == 0) {
        InitializeEntity(D_80180458);
        self->animSet = 2;
        self->palette = 0x81B6;
        self->unk6C = 0x70;
        self->zPriority = 192;
        self->unk19 |= 0xC;
        self->blendMode |= 0x30;

        switch (self->unk84.U8.unk0) {
        case 1:
            if (self->unk84.U8.unk1 >= 4) {
                self->unk84.U8.unk1 += 253;
                self->unk80.modeS16.unk0 -= 0x800;
            }
            break;

        case 2:
            self->unk80.modeS16.unk0 += self->unk84.U8.unk1 * 192;
            break;
        }

        self->unk1E = self->unk80.modeS16.unk0 &= 0xFFF;
        temp = (self->unk84.U8.unk1 * 320) / 24;
        self->accelerationX = temp * rsin(self->unk80.modeS16.unk0);
        self->accelerationY = -(temp * rcos(self->unk80.modeS16.unk0));
    }

    if (self->animFrameIdx >= 13) {
        accelerationX = self->accelerationX;
        if (accelerationX < 0) {
            accelerationX += 3;
        }

        accelerationY = self->accelerationY;
        self->accelerationX = (accelerationX >> 2) * 3;
        if (accelerationY < 0) {
            accelerationY += 3;
        }
        self->accelerationY = (accelerationY >> 2) * 3;
    }

    MoveEntity();

    if (AnimateEntity(D_80180EEC, self) == 0) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", func_801907EC);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", func_80190DCC);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", func_801914CC);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", func_801916C4);

s32 func_80193A3C(u8* arg0, u8 value);
INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", func_801917BC);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", EntityStageNamePopup);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", EntityAbsorbOrb);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", EntityEnemyBlood);

ObjInit2 D_80181134[];
u16 D_80180494[];
void EntityRoomForeground(Entity* entity) {
    ObjInit2* objInit = &D_80181134[entity->subId];
    if (entity->step == 0) {
        InitializeEntity(D_80180494);
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

#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", func_80192F40);
#else
void func_80192F40(u8* arg0, u8 arg1) {
    u8 sp10[0x40];
    POLY_GT4* poly;
    s16 temp_t2;
    s16 temp_t3;
    s32 firstPolyIndex;
    s16 temp_v0_2;
    s16 var_t5_2;
    s16 var_t5_3;
    short temp_v1;
    s32 var_s0;
    u16 polyCount;
    s32 i;
    u8 temp_v1_2;
    u8 var_v1;
    u8* var_a1;
    u8* var_a1_2;
    u8* var_a1_3;
    var_a1 = &sp10;
    var_s0 = 0;
    polyCount = 0;
    for (i = sizeof(sp10) - 1; i >= 0; i--) {
        *(var_a1++) = 0;
    }

    var_a1_2 = &sp10;
    while (1) {
        var_v1 = *arg0++;
        if (var_v1 == 0xFF) {
            var_v1 = *arg0++;
            if (var_v1 == 0) {
                break;
            }
        }
        *(var_a1_2++) = var_v1;
        if (var_v1 != 0) {
            polyCount++;
            var_s0 = var_s0 + 8;
        } else {
            var_s0 += 4;
        }
    }

    firstPolyIndex = g_api.AllocPrimitives(6, polyCount + 4);
    D_80097414 = firstPolyIndex;
    if (firstPolyIndex == (-1)) {
        return;
    }
    poly = &g_PrimBuf[firstPolyIndex];
    setcode(poly, 3);
    poly->r3 = 0;
    poly->r2 = 0;
    poly->r1 = 0;
    poly->r0 = 0;
    poly->g3 = 0;
    poly->g2 = 0;
    poly->g1 = 0;
    poly->g0 = 0;
    poly->b3 = 0;
    poly->b2 = 0;
    poly->b1 = 0;
    poly->b0 = 0;
    if (arg1) {
        poly->b1 = 0xAF;
        poly->b0 = 0xAF;
    } else {
        poly->g1 = 0x5F;
        poly->g0 = 0x5F;
    }
    var_t5_2 = 7;
    if (arg1) {
        var_s0 += 4;
    } else {
        var_t5_2 = 0xD4 - var_s0;
    }
    temp_v1 = var_t5_2 + var_s0;
    temp_v0_2 = temp_v1 + 0x20;
    temp_t2 = var_t5_2 + 0xA;
    temp_t3 = temp_v1 + 0x18;
    poly->x3 = temp_v0_2;
    poly->x1 = temp_v0_2;
    poly->y1 = 0xD0;
    poly->y0 = 0xD0;
    poly->y3 = 0xDF ^ 0;
    poly->y2 = 0xDF;
    poly->pad2 = 0x1EE;
    poly->pad3 = 0x11;
    poly->x2 = var_t5_2;
    poly->x0 = var_t5_2;
    var_t5_3 = var_t5_2 + 0x10;
    poly = poly->tag;
    poly->tpage = 0x1F;
    poly->clut = 0x197;
    poly->x0 = var_t5_2 - 6;
    poly->y0 = 0xCB;
    poly->u0 = 0x80;
    poly->v0 = 0;
    poly->u1 = 0x10;
    poly->v1 = 0x18;
    poly->pad2 = 0x1EF;
    poly->pad3 = 0;
    poly = poly->tag;
    poly->tpage = 0x1F;
    poly->clut = 0x197;
    poly->x0 = temp_v1 + 0x16;
    poly->y0 = 0xCB;
    poly->u0 = 0xA8;
    poly->v0 = 0;
    poly = poly;
    poly->u1 = 0x10;
    poly->v1 = 0x18;
    poly->pad2 = 0x1EF;
    poly->pad3 = 0;
    poly = poly->tag;
    setcode(poly, 4);
    poly->y1 = 0xCD;
    poly->y0 = 0xCD;
    poly->y3 = 0xE1;
    poly->y2 = 0xE1;
    do {
        poly->u2 = 0x98;
        poly->u0 = 0x98;
        poly->u3 = 0x9C;
        poly->u1 = 0x9C;
        poly->v1 = 2;
        poly->v0 = 2;
        poly->tpage = 0x1F;
        poly->clut = 0x197;
        poly->x2 = temp_t2;
        poly->x0 = temp_t2;
        poly->x3 = temp_t3;
        poly->x1 = temp_t3;
        poly->v3 = 0x16;
    } while (0);
    poly->v2 = 0x16;
    poly->pad2 = 0x1EF;
    poly->pad3 = 0;
    poly = poly->tag;
    var_a1_3 = &sp10;
    while (poly != 0) {
        var_v1 = *var_a1_3++;
        temp_v1_2 = var_v1;
        if (temp_v1_2 != 0) {
            poly->x0 = var_t5_3;
            poly->u0 = (temp_v1_2 & 0xF) * 8;
            poly->tpage = 0x1E;
            poly->clut = 0x196;
            poly->v0 = (temp_v1_2 & 0xF0) / 2;
            poly->v1 = 8;
            poly->u1 = 8;
            poly->pad2 = 0x1F0;
            poly->pad3 = 0;
            poly->y0 = 0xD4;
            poly = poly->tag;
            var_t5_3 += 8;
        } else {
            var_t5_3 += 4;
        }
    }

    D_80097410 = 0x130;
}
#endif

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", func_80193270);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/D020", func_80193658);

POLY_GT4* func_801937A8(POLY_GT4* poly) {
    while (poly) {
        if (poly->p3 == 0)
            return poly;
        poly = (POLY_GT4*)poly->tag;
    }
    return NULL;
}

POLY_GT4* func_801937D8(POLY_GT4* poly, u8 index) {
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

POLY_GT4* func_80193854(POLY_GT4* startPoly, s32 count) {
    POLY_GT4* poly;
    s8 unk;
    s32 i;

    if (startPoly->p3) {
        startPoly->p3 = 0;
    } else {
        startPoly->p3 = 1;
    }

    poly = startPoly;
    for (i = 0; i < count; i++) {
        if (poly->p3) {
            poly->pad3 &= ~8;
            unk = 0;
        } else {
            poly->pad3 |= 8;
            unk = 1;
        }

        poly = (POLY_GT4*)poly->tag;
        if (poly == 0)
            return 0;
        poly->p3 = unk;
    }

    return poly;
}

void func_801938DC(POLY_GT4* arg0) {
    arg0->p1 = 0;
    arg0->p2 = 0;
    arg0->p3 = 0;
    ((POLY_GT4*)arg0->tag)->x1 = 0;
    ((POLY_GT4*)arg0->tag)->y1 = 0;
    ((POLY_GT4*)arg0->tag)->y0 = 0;
    ((POLY_GT4*)arg0->tag)->x0 = 0;
    ((POLY_GT4*)arg0->tag)->clut = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->u0 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->b1 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->r1 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->u1 = 0;
    ((POLY_GT4*)arg0->tag)->tpage = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->r2 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->b2 = 0;
    ((POLY_GT4*)arg0->tag)->u2 = 0;
    ((POLY_GT4*)arg0->tag)->v2 = 0;
    ((POLY_GT4*)arg0->tag)->r3 = 0;
    ((POLY_GT4*)arg0->tag)->b3 = 0;
    ((POLY_GT4*)arg0->tag)->x2 = 0;
    ((POLY_GT4*)arg0->tag)->y2 = 0;
}

void func_801939BC(POLY_GT4* poly) {
    func_801938DC(poly);
    poly->p3 = 8;
    ((POLY_GT4*)poly->tag)->p3 = 1;
    ((POLY_GT4*)poly->tag)->code = 2;
    ((POLY_GT4*)poly->tag)->pad3 = 0xA;
}

void func_80193A10(POLY_GT4* poly) {
    poly->p3 = 0;
    poly->pad3 = 8;
    ((POLY_GT4*)poly->tag)->p3 = 0;
    ((POLY_GT4*)poly->tag)->code = 4;
    ((POLY_GT4*)poly->tag)->pad3 = 8;
}

s32 func_80193A3C(u8* arg0, u8 value) {
    s32 ret = 0;
    u8* phi_a0 = arg0 + 4;
    s32 i;

    for (i = 0; i < 4; i++) {
        u8* ptrCur = phi_a0;
        s32 ptrEnd = (s32)phi_a0 + 3;
        do {
            s32 phi_v0 = *ptrCur - value;
            if (phi_v0 < 0) {
                phi_v0 = 0;
            } else {
                ret |= 1;
            }

            *ptrCur++ = phi_v0;
        } while ((s32)ptrCur < ptrEnd);

        phi_a0 += 0xC;
    }

    return ret;
}
