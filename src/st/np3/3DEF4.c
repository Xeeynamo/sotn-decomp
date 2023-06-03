#include "np3.h"

u16 D_80180A48[];
u16 D_80181DB0[];
u8* D_80181E14[];
u16 D_80181E74[];
void EntityPrizeDrop(Entity* self) {
    Collider collider;
    Primitive* prim;
    s16 firstPrimIndex;
    s16 var_a2;
    u16 itemId;
    s16 temp_a0;

    itemId = self->subId & 0x7FFF;
    if (self->step != 0) {
        AnimateEntity(D_80181E14[itemId], self);
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
        InitializeEntity(D_80180A48);
        self->zPriority = g_zEntityCenter.S16.unk0 - 0x14;
        self->blendMode = 0;
        if (itemId >= 0x18) {
            self->subId = 0;
            itemId = 0;
        }
        if (itemId > 13 && itemId < 23 &&
            itemId == D_80181DB0[g_Status.subWeapon]) {
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
            if (LOH(self->ext.generic.unk94) != 0) {
                temp_a0 = LOH(self->ext.generic.unk94) - 1;
                g_zEntityCenter.S16 = g_zEntityCenter.S16;
                D_8003BF9C[temp_a0 >> 3] |= 1 << (temp_a0 & 7);
            }
        }
        if (itemId == 0) {
            self->ext.generic.unk84.unk = -0x10000;
            self->ext.generic.unk88.S16.unk0 = 0x800;
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
                self->posY.i.hi += collider.unk18;
                self->ext.generic.unk80.modeS8.unk0 = 0xF0;
                self->ext.generic.unk80.modeS8.unk0 = 0xF0;
                self->step++;
            } else {
                FallEntity();
            }
            func_801BD430(D_80181E74, 2);
        } else if (collider.unk0 & 5) {
            self->posY.i.hi += collider.unk18;
            self->ext.generic.unk80.modeS8.unk0 = 0x60;
            self->step++;
        } else {
            func_801BD984();
        }
        break;

    case 3:
        func_801BDA08(itemId);
        if (!(self->subId & 0x8000) &&
            --self->ext.generic.unk80.modeS8.unk0 == 0) {
            self->ext.generic.unk80.modeS8.unk0 = itemId == 0 ? 0x40 : 0x50;
            self->step++;
        }
        break;

    case 4:
        func_801BDA08(itemId);
        if (--self->ext.generic.unk80.modeS8.unk0) {
            if (self->ext.generic.unk80.modeS8.unk0 & 2) {
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
            CollectSubweapon(itemId);
        } else if (itemId == 23) {
            CollectLifeVessel();
        } else {
            DestroyEntity(self);
            return;
        }
        break;

    case 6:
    case 7:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0;
            if (itemId > 13 && itemId < 23) {
                if (itemId == D_80181DB0[g_Status.subWeapon]) {
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
                self->step_s++;
            }
            break;

        case 1:
            MoveEntity();
            g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi + 7,
                                 &collider, 0);
            if (collider.unk0 & 5 && self->accelerationY > 0) {
                self->accelerationX = 0;
                self->accelerationY = 0;
                self->posY.i.hi += collider.unk18;
                self->step_s++;
            } else {
                FallEntity();
            }
            func_801BD430(D_80181E74, 2);
            self->animCurFrame = 0;
            if (self->ext.generic.unk88.S16.unk2 != 0) {
                self->ext.generic.unk88.S16.unk2--;
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
            func_801BDA08(itemId);
            prim = &g_PrimBuf[self->firstPolygonIndex];
            self->ext.generic.unk88.S16.unk2++;
            if (self->ext.generic.unk88.S16.unk2 < 0x11) {
                var_a2 = self->ext.generic.unk88.S16.unk2;
                self->animCurFrame = 0;
            } else {
                var_a2 = 0x20 - self->ext.generic.unk88.S16.unk2;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->r3 - 8;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = prim->g3 - 8;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->b3 - 8;
            }
            prim->x0 = prim->x2 = self->posX.i.hi - var_a2;
            prim->x1 = prim->x3 = self->posX.i.hi + var_a2;
            prim->y0 = prim->y1 = self->posY.i.hi - var_a2;
            prim->y2 = prim->y3 = self->posY.i.hi + var_a2;
            if (self->ext.generic.unk88.S16.unk2 == 0x20) {
                g_api.FreePrimitives(self->firstPolygonIndex);
                self->ext.generic.unk80.modeS8.unk0 = 0xD0;
                self->step = 3;
                self->step_s = 0;
                self->flags &= ~0x800000;
            }
            break;
        }

        break;
    }
}

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

void func_801BE864(Entity* self, s32 arg1) {
    POLY_GT4* poly = &g_PrimBuf[self->firstPolygonIndex];
    s16 right, left, bottom, top;

    left = self->posX.i.hi - 7;
    right = self->posX.i.hi + 7;

    poly->x0 = poly->x2 = left;
    poly->x1 = poly->x3 = right;

    top = self->posY.i.hi - 7;
    bottom = self->posY.i.hi + 7;

    poly->y0 = poly->y1 = top;
    poly->y2 = poly->y3 = bottom;

    if (arg1 & RENDERFLAGS_NOSHADOW) {
        poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 =
            poly->g2 = poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
                255;
    } else {
        poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 =
            poly->g2 = poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
                128;
    }
}

void EntityEquipItemDrop(Entity* self) {
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
            self->pfnUpdate = EntityPrizeDrop;
            self->subId = 0;
            self->objectId = 3;
            SetStep(0);
            EntityPrizeDrop(self);
            return;
        }
        InitializeEntity(D_80180A48);
        self->ext.generic.unk7C.s = 0;
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

            if (LOH(self->ext.generic.unk94) != 0) {
                temp_a0 = LOH(self->ext.generic.unk94);
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
            self->ext.generic.unk8C.modeU16.unk0 = index;

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

            self->ext.generic.unk7C.s = 128;
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
            self->ext.generic.unk80.modeS8.unk0 = 240;
            self->step++;
        } else {
            FallEntity();
        }

        func_801BD430(D_80181E74, 2);
        break;

    case 3:
        func_801BDA08(1);
        if (!(self->subId & 0x8000)) {
            if (!(--self->ext.generic.unk80.modeS8.unk0 & 255)) {
                self->ext.generic.unk80.modeS8.unk0 = 0x50;
                self->step++;
            }
        } else {
            D_801D33F4[self->ext.generic.unk8C.modeS16.unk0] = 0x10;
        }
        break;

    case 4:
        func_801BDA08(1);
        if (self->ext.generic.unk80.modeS8.unk0 += 255) {
            poly = &g_PrimBuf[self->firstPolygonIndex];
            if (self->ext.generic.unk80.modeS8.unk0 & 2) {
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
        if (self->ext.generic.unk7C.u != 0) {
            self->ext.generic.unk7C.u--;
        }
        func_801BE864(self, self->ext.generic.unk7C.u);
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801BEEF0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", EntityRelicOrb);

void EntityHeartDrop(Entity* self) {
    u16 temp_a0;
    u16 temp_a0_2;
    u16 var_a0;

    if (self->step == 0) {
        temp_a0 = self->subId + 0x30;
        self->ext.generic.unkB4 = temp_a0;
        if ((D_8003BEEC[temp_a0 >> 3] >> (temp_a0 & 7)) & 1) {
            DestroyEntity(self);
            return;
        }
        temp_a0_2 = temp_a0 - 0x30;
        var_a0 = D_80181618[temp_a0_2];
        if (var_a0 < 128) {
            self->ext.generic.unkB8.unkFuncB8 = EntityPrizeDrop;
        } else {
            self->ext.generic.unkB8.unkFuncB8 = EntityEquipItemDrop;
            var_a0 -= 128;
        }
        self->subId = var_a0 + 0x8000;
    } else {
        temp_a0_2 = self->ext.generic.unkB4;
        if (self->step < 5) {
            if (self->unk48 != 0) {
                var_a0 = self->ext.generic.unkB4;
                D_8003BEEC[temp_a0_2 >> 3] |= 1 << (var_a0 & 7);
                self->step = 5;
            }
        }
    }
    self->ext.generic.unkB8.unkFuncB8(self);
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", EntityUnkId0E);

u8 func_801C02F4(s16* arg0, u8 facing) {
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

void func_801C03E4(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180A78);
        entity->ext.generic.unk8C.modeU16.unk0 =
            entity->ext.generic.unk80.entityPtr->objectId;
    case 1:
        if (entity->ext.generic.unk7C.U8.unk0++ >= 5) {
            Entity* newEntity =
                AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(ENTITY_EXPLOSION, entity, newEntity);
                newEntity->objectId = ENTITY_EXPLOSION;
                newEntity->pfnUpdate = EntityExplosion;
                newEntity->subId = entity->subId;
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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801C04F4);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801C0624);

void func_801C070C(Entity* entity) {
    if (entity->step == 0) {
        entity->accelerationY = D_80181FDC[entity->ext.generic.unk94];
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

void func_801C07FC(Entity* entity) {
    u16 temp_v0;
    u32 temp2;

    if (entity->step == 0) {
        entity->flags = 0x2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = 5;
        entity->animCurFrame = 1;
        entity->blendMode = 0x10;
        entity->unk19 = 3;
        temp_v0 = D_80181FB4[entity->subId];
        entity->unk1A = temp_v0;
        entity->unk1C = temp_v0;
        temp2 = D_80181FC4[entity->subId];
        entity->step += 1;
        entity->accelerationY = temp2;
    } else {
        entity->animFrameDuration++;
        entity->posY.val -= entity->accelerationY;

        if (!(entity->animFrameDuration & 1)) {
            entity->animCurFrame++;
        }

        if (entity->animFrameDuration >= 0x25) {
            DestroyEntity(entity);
        }
    }
}

void func_801C08F0(Entity* self) {
    s16 firstPolygonIndex;
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180A54);
        firstPolygonIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (firstPolygonIndex != -1) {
            prim = &g_PrimBuf[firstPolygonIndex];
            self->firstPolygonIndex = firstPolygonIndex;
            self->unk3C = 0;
            *(s32*)&self->ext.generic.unk7C = prim;
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
        prim = (Primitive*)*(s32*)&self->ext.generic.unk7C.s;
        if (func_801C02F4(&D_80182000, 0) & 255) {
            prim->y1 += 2;
            if (self->step_s == 0) {
                func_801C04F4(self, 1, 2, 0, 0, 3, 0);
                self->step_s = 1;
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

bool func_801C0B20(Unkstruct6* unk) {
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
            g_CurrentEntity->posY.i.hi += res.unk18;
            g_CurrentEntity->accelerationY =
                -g_CurrentEntity->accelerationY / 2;
            if (g_CurrentEntity->accelerationY > -0x10000) {
                return true;
            }
        }
    }
    return false;
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801C0C1C);

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

void func_801C129C(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(D_80180A54);
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
    } else {
        MoveEntity();
        if (!AnimateEntity(D_80182008, entity)) {
            DestroyEntity(entity);
        }
    }
}

void func_801C1368(u16 objectId, Entity* src, Entity* dst) {
    DestroyEntity(dst);
    dst->objectId = objectId;
    dst->pfnUpdate = PfnEntityUpdates[objectId];
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
        dst->palette = (s16)src->palette;
    }
}

void func_801C1848(void) {
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
            entity->ext.generic.unk84.U8.unk1 = 6 - i;
            entity->ext.generic.unk80.modeS16.unk0 = temp_s3;
            entity->ext.generic.unk84.U8.unk0 = temp_s4;
        }
    }
}

void func_801C14E8(Entity* self) {
    s32 accelerationX;
    s32 accelerationY;
    s32 temp;

    if (self->step == 0) {
        InitializeEntity(D_80180A54);
        self->animSet = 2;
        self->palette = 0x81B6;
        self->unk6C = 0x70;
        self->zPriority = 192;
        self->unk19 |= 0xC;
        self->blendMode |= 0x30;

        switch (self->ext.generic.unk84.U8.unk0) {
        case 1:
            if (self->ext.generic.unk84.U8.unk1 >= 4) {
                self->ext.generic.unk84.U8.unk1 += 253;
                self->ext.generic.unk80.modeS16.unk0 -= 0x800;
            }
            break;

        case 2:
            self->ext.generic.unk80.modeS16.unk0 +=
                self->ext.generic.unk84.U8.unk1 * 192;
            break;
        }

        self->unk1E = self->ext.generic.unk80.modeS16.unk0 &= 0xFFF;
        temp = (self->ext.generic.unk84.U8.unk1 * 320) / 24;
        self->accelerationX = temp * rsin(self->ext.generic.unk80.modeS16.unk0);
        self->accelerationY =
            -(temp * rcos(self->ext.generic.unk80.modeS16.unk0));
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

    if (AnimateEntity(D_80181EA8, self) == 0) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801C16C0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801C1CA0);

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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801C2598);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801C2690);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", EntityStageNamePopup);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", EntityAbsorbOrb);

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
            InitializeEntity(D_80180A48);
            prim = &g_PrimBuf[i];
            self->firstPolygonIndex = i;
            self->animSet = 0;
            subId = self->subId;
            self->unk3C = 1;
            self->ext.generic.unk7C.s = 48;
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
                    func_801BCF78(0xCC0 + i * 64,
                                  ((Random() & 0xF) * 0x10) + 0x180);
                } else {
                    func_801BCF78(0xB40 - i * 64,
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
                self->ext.generic.unk80.modeS32 = -0x200;
            } else {
                self->accelerationX = -0x14000;
                self->ext.generic.unk80.modeS32 = 0x200;
            }
            self->accelerationY = 0;
            break;
        }
        DestroyEntity(self);
        break;

    case 1:
        if (!(--self->ext.generic.unk7C.u)) {
            DestroyEntity(self);
            break;
        }

        if (self->unk3C != 0) {
            if (g_Player.unk0C & 0x02000000) {
                posX = self->posX.i.hi;
                self->accelerationX += self->ext.generic.unk80.modeS32;

                MoveEntity(self); // argument pass necessary to match

                posX -= self->posX.i.hi;
                if (posX < 0) {
                    posX = -posX;
                }

                if (self->ext.generic.unk7C.u > 16) {
                    self->ext.generic.unk7E.modeU16 += posX;
                    self->hitboxWidth = self->ext.generic.unk7E.modeU16 / 2;
                    self->hitboxHeight =
                        (self->ext.generic.unk7E.modeU16 / 4) + 8;
                } else {
                    self->unk3C = 0;
                }

                if (self->unk48 != 0) {
                    if (g_Player.unk56 == 0) {
                        g_Player.unk56 = 1;
                        g_Player.unk58 = 8;
                        if (g_api.CheckEquipmentItemCount(0x3C, 4)) {
                            g_Player.unk58 *= 2;
                        }
                    }
                    g_Player.unk10++;
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

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801C3E14);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801C4144);

// ID 0x2C
INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801C424C);

// EntitySplashWater ID 0x2D
INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801C4DCC);

// EntitySurfacingWater ID 0x2E
INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801C56D8);

// EntitySideWaterSplash ID 0x2F
INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801C5BC4);

// EntitySmallWaterDrop ID 0x30
INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801C5F58);

// EntityWaterDrop ID 0x31
INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801C61B4);

s32 func_801C6458(s16 yVector) {
    s16 newY = yVector + g_CurrentEntity->posY.i.hi;
    s32 expectedResult = 0;
    Collider collider;
    Entity* newEntity;
    s32 res;

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi, newY, &collider, 0);
    res = expectedResult == (collider.unk0 & 1);

    if (collider.unk0 & 8) {
        if (*(u8*)&g_CurrentEntity->ext.generic.unkA0 == 0) {
            newEntity = AllocEntity(&D_8007DE38, &D_8007DE38[24]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x33, g_CurrentEntity, newEntity);
                newEntity->posY.i.hi += yVector;
                newEntity->zPriority = g_CurrentEntity->zPriority;
            }
            g_api.PlaySfx(0x7C2);
            *(u8*)&g_CurrentEntity->ext.generic.unkA0 = 1;
        }
    }
    return res;
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", EntityMerman2);
#else
#define NA_SE_EV_WATER_SPLASH 0x7C2

extern u16 D_80181230[]; // pos TBL
extern s32 D_80182224[]; // accel_x TBL
extern s32 D_80182228[]; // accel_y TBL
extern u8 D_80182244[];  // timers
extern s32 D_80182248;   // Collision data
extern s32 D_80182258;   // Collision data
extern u16 D_80182268;   // Collision data
extern u8 D_80182270[];  // Animation
extern u8 D_8018227C[];  // Animation
extern u8 D_80182294[];  // Animation
extern u8 D_8018229C[];  // Animation

void EntityMerman2(Entity* self) {
    s32 firstPrimIndex;
    Collider collider;
    Entity* newEntity;
    Entity* temp_s4;
    Primitive* prim;
    s32 colRes;
    s32 offset;
    s16* pos;
    s16 posX;
    s16 posY;
    s16 camY;
    s32 rnd;
    s32 i;
    u16 temp_v0_10;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_9;
    u32 temp_v0_12;
    u32 v0;
    u16 var_v0_11;
    s32 res;
    s32 index;
    unsigned int temp;
    if (self->ext.merman2.ignoreCol && (self->step < 7)) {
        SetStep(7);
    }
    if ((self->flags & 0x100) && (self->step < 8)) {
        func_801C2598(0x71D);
        self->unk19 = 0;
        if (self->flags & 0x00800000) {
            g_api.FreePrimitives(self->firstPolygonIndex);
            self->flags &= ~0x00800000;
        }
        self->unk3C = 0;
        self->flags &= ~0x20000000;
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180AB4);
        self->unk12 = 8;
        self->zPriority = 0xA9;
        if (self->subId != 0) {
            self->palette++;
        }
        self->accelerationY = -0x10000;
        break;

    case 1:
        AnimateEntity(D_8018229C, self);
        MoveEntity();
        posY = self->posY.i.hi - 24;
        g_api.CheckCollision(self->posX.i.hi, posY, &collider, 0);
        if (!(collider.unk0 & 8)) {
            SetStep(3);
            break;
        }

    case 3:
        if (self->step_s == 0) {
            rnd = (Random() & 3) * 2;
            self->accelerationX = D_80182224[rnd];
            self->accelerationY = D_80182228[rnd];
            self->step_s++;
        }
        if (AnimateEntity(D_8018229C, self) == 0) {
            self->facing = (GetPlayerSide() & 1) ^ 1;
        }
        MoveEntity();
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY -= 24;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (!(collider.unk0 & 8)) {
            self->accelerationY = 0x8000;
        }
        index = (self->subId >> 8) & 1;
        pos = &D_80181230;
        pos += index;
        posY += g_Camera.posY.i.hi;
        if (pos[4] < posY) {
            self->posY.i.hi = (pos[4] - g_Camera.posY.i.hi) - 24;
        }
        if (((u8)(self->ext.merman2.timer++)) > 32) {
            self->ext.merman2.timer = 0;
            self->step_s = 0;
            if ((GetPlayerDistanceX() >= 48) && (!(Random() & 1))) {
                SetStep(4);
            }
        }
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            self->accelerationX = 0;
            self->accelerationY = -0x88000;
            self->step_s++;
            firstPrimIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (firstPrimIndex != (-1)) {
                prim = &g_PrimBuf[firstPrimIndex];
                self->animCurFrame = 0;
                self->firstPolygonIndex = firstPrimIndex;
                self->ext.merman2.prim = prim;
                self->flags |= 0x00800000;
                prim->tpage = 0x12;
                prim->clut = 0x28C;
                if (self->subId & 1) {
                    prim->clut = 0x28D;
                }
                prim->u0 = 0;
                prim->u1 = 0x20;
                prim->v1 = (prim->v0 = 0x38);
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                v0 = prim->v0 + 0x38;
                prim->v2 = v0;
                prim->v3 = v0;
                if (self->facing != 0) {
                    temp_v0_5 = self->posX.i.hi;
                    prim->x0 = temp_v0_5 + 0xF;
                    prim->x1 = temp_v0_5 - 0x11;
                    prim->x2 = prim->x0;
                    prim->x3 = prim->x1;
                } else {
                    temp_v0_6 = self->posX.i.hi;
                    prim->x0 = temp_v0_6 - 0xF;
                    prim->x1 = temp_v0_6 + 0x11;
                    prim->x2 = prim->x0;
                    prim->x3 = prim->x1;
                }
                prim->y0 = (prim->y1 = self->posY.i.hi - 0x11);
                prim->r0 = 64, prim->g0 = 64, prim->b0 = 160;
                *((s32*)(&prim->r1)) = *((s32*)(&prim->r0));
                *((s32*)(&prim->r2)) = *((s32*)(&prim->r0));
                *((s32*)(&prim->r3)) = *((s32*)(&prim->r0));
                prim->y3 = (prim->y2 = prim->y0 + 0x38);
                prim->priority = self->zPriority;
                prim->blendMode = 6;
                return;
            }
            self->animCurFrame = 17;
            DestroyEntity(self);
            break;

        case 1:
            MoveEntity();
            index = (self->subId >> 8) & 1;
            pos = &D_80181230;
            pos += index;
            posY = self->posY.i.hi;
            posY -= 24;
            camY = g_Camera.posY.i.hi + posY;
            if (camY < pos[3]) {
                g_api.PlaySfx(0x7C2);
                newEntity = AllocEntity(D_8007DE38, &D_8007DE38[24]);
                if (newEntity != 0) {
                    CreateEntityFromEntity(0x33, self, newEntity);
                    newEntity->posY.i.hi -= 24;
                    newEntity->zPriority = self->zPriority;
                }
                self->unk1E = 0;
                self->unk19 |= 4;
                self->step_s++;
            }
            break;

        case 2:
            prim = self->ext.merman2.prim;
            if (self->accelerationY > ((s32)0xFFFF4000)) {
                prim->blendMode = 8;
                self->animCurFrame = 18;
                self->hitboxHeight = 8;
                self->unk1E -= 0x80;
            } else {
                if (self->facing != 0) {
                    temp_v0_9 = self->posX.i.hi;
                    prim->x0 = temp_v0_9 + 0xF;
                    prim->x1 = temp_v0_9 - 0x11;
                    prim->x2 = prim->x0;
                    prim->x3 = prim->x1;
                    prim->y1 = (prim->y0 = self->posY.i.hi - 0x11);
                    prim->y3 = (prim->y2 = prim->y0 + 0x38);
                } else {
                    temp_v0_10 = self->posX.i.hi;
                    prim->x0 = temp_v0_10 - 0xF;
                    prim->x1 = temp_v0_10 + 0x11;
                    prim->x2 = prim->x0;
                    prim->x3 = prim->x1;
                    prim->y1 = (prim->y0 = self->posY.i.hi - 0x11);
                    prim->y3 = (prim->y2 = prim->y0 + 0x38);
                }
                temp_v0_12 = ((u32)(((((self->accelerationY < 0)
                                           ? (-self->accelerationY)
                                           : (self->accelerationY)) >>
                                      0xC) -
                                     0xA) &
                                    0xFF)) >>
                             1;
                prim->r0 = 128 - temp_v0_12, prim->g0 = 128 - temp_v0_12,
                prim->b0 = temp_v0_12 + 192;
                *((s32*)(&prim->r1)) = *((s32*)(&prim->r0));
                *((s32*)(&prim->r2)) = *((s32*)(&prim->r0));
                *((s32*)(&prim->r3)) = *((s32*)(&prim->r0));
            }
            if (self->accelerationY < 0) {
                newEntity = AllocEntity(D_8007DE38, &D_8007DE38[24]);
                if (newEntity != 0) {
                    CreateEntityFromEntity(0x38, self, newEntity);
                    newEntity->posX.i.hi -= 6 - ((Random() & 3) * 4);
                    newEntity->zPriority = self->zPriority + 1;
                }
            }
            if (self->accelerationY > 0) {
                func_801C6458(0x1B);
            }
            if (self->ext.merman2.isUnderwater == 0) {
                if (func_801BC8E4(&D_80182248) & 1) {
                    g_api.FreePrimitives(self->firstPolygonIndex);
                    self->hitboxHeight = 21;
                    self->flags &= ~0x00800000;
                    self->unk19 &= 0xFB;
                    SetStep(5);
                    return;
                }
            } else {
                self->flags |= 0xC0000000;
                MoveEntity();
                self->accelerationY += 0x4000;
            }
        }

        break;

    case 5:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(D_80182294, self) == 0) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
            }
            break;

        case 1:
            self->facing = (GetPlayerSide() & 1) ^ 1;
            self->ext.merman2.timer = D_80182244[Random() & 3];
            self->step_s++;
            break;

        case 2:
            AnimateEntity(D_80182270, self);
            colRes = func_801BCB5C(&D_80182268);
            if (colRes == 0xFF) {
                self->facing ^= 1;
            }
            if (self->facing == 0) {
                self->accelerationX = -0x6000;
            } else {
                self->accelerationX = 0x6000;
            }
            if (colRes & 0x80) {
                self->posX.val += self->accelerationX;
            }
            if ((!(self->subId & 1)) ||
                ((self->accelerationX *= 2, !(self->subId & 1)))) {
                if (!(self->posX.i.hi & 0xFF00)) {
                    self->ext.merman2.timer--;
                    if ((self->ext.merman2.timer & 0xFF) == 0) {
                        if (Random() % 2) {
                            SetStep(6);
                        } else {
                            self->step_s--;
                        }
                    }
                    res = func_801C6458(0x1B);
                    if (res != 0) {
                        self->ext.merman2.ignoreCol = 1;
                    }
                }
            } else {
                res = func_801C6458(0x1B);
                if (res != 0) {
                    self->ext.merman2.ignoreCol = 1;
                }
            }
        }

        break;

    case 6:
        switch (self->step_s) {
        case 0:
            self->facing = (GetPlayerSide() & 1) ^ 1;
            self->step_s++;
            return;

        case 1:
            if (AnimateEntity(D_8018227C, self) == 0) {
                func_801C2598(0x662);
                newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
                i = 0;
                if (newEntity != 0) {
                    CreateEntityFromEntity(0x34, self, newEntity);
                    newEntity->posY.i.hi -= 12;
                    newEntity->facing = self->facing;
                }
                temp_s4 = &D_8007A958[64];
                for (offset = 0; i < 3; i++, offset += 8) {
                    newEntity = AllocEntity(temp_s4, &temp_s4[32]);
                    if (newEntity != 0) {
                        CreateEntityFromEntity(0x36, self, newEntity);
                        if (self->facing != 0) {
                            newEntity->posX.i.hi += 8 + offset;
                        } else {
                            newEntity->posX.i.hi += (-8) - offset;
                        }
                        newEntity->posY.i.hi -= 12;
                        newEntity->facing = self->facing;
                        if (i == 0) {
                            newEntity->subId = 1;
                        }
                    }
                }

                self->ext.merman2.rotation = 1;
                self->unk1E = 0;
                self->unk19 = self->unk19 | 4;
                if (self->facing != 0) {
                    self->accelerationX = -0x60000;
                } else {
                    self->accelerationX = 0x60000;
                }
                self->accelerationY = -0x1000;
                self->posY.i.hi -= 1;
                self->step_s++;
            }
            break;

        case 2:
            if ((self->ext.merman2.rotation < 0x100) && (g_blinkTimer & 1)) {
                self->ext.merman2.rotation *= 2;
            }
            if (self->accelerationX != 0) {
                if (self->facing != 0) {
                    self->accelerationX += 0x3000;
                } else {
                    self->accelerationX -= 0x3000;
                }
            }
            posX = self->posX.i.hi;
            posY = self->posY.i.hi + 8;
            if (self->facing != 0) {
                posX -= 20;
            } else {
                posX += 20;
            }
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.unk0 & 1) {
                self->accelerationX = 0;
            }
            self->unk1E += self->ext.merman2.rotation;
            self->accelerationY -= 0x2000;
            if (func_801BC8E4(&D_80182248) & 1) {
                if (self->facing == 0) {
                    self->accelerationX = 0x28000;
                } else {
                    self->accelerationX = ~0x27FFF;
                }
                self->ext.merman2.rotation = 4;
                self->posY.i.hi += 10;
                self->step_s++;
            }
            func_801C6458(0x1B);
            res = self->ext.merman2.isUnderwater;
            if (res != 0) {
                self->ext.merman2.ignoreCol = 1;
            }
            break;

        case 3:
            posY = self->posY.i.hi + 8;
            posX = self->posX.i.hi;
            if (self->facing != 0) {
                posX -= 20;
            } else {
                posX += 20;
            }
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.unk0 & 1) {
                self->accelerationX = 0;
            }
            MoveEntity();
            self->unk1E += 0xC0;
            if (self->unk1E > 0x1000) {
                self->posY.i.hi -= 10;
                self->unk19 &= 0xFB;
                SetStep(5);
            }
            res = func_801C6458(0x1B);
            if (res != 0) {
                self->ext.merman2.ignoreCol = 1;
            }
        }

        break;

    case 7:
        if (self->step_s == 0) {
            self->flags |= 0xC0000000;
            self->step_s++;
        }
        MoveEntity();
        self->accelerationY += 0x4000;
        if ((!func_801C6458(0x1B)) && (!self->ext.merman2.isUnderwater)) {
            self->ext.merman2.ignoreCol = 0;
            SetStep(5);
        }
        break;

    case 8:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 14;
            self->flags |= 0xC0000000;
            if (!(GetPlayerSide() & 1)) {
                self->accelerationX = -0x20000;
            } else {
                self->accelerationX = 0x20000;
            }
            self->accelerationY = -0x10000;
            self->step_s++;
            firstPrimIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (firstPrimIndex != (-1)) {
                prim = &g_PrimBuf[firstPrimIndex];
                self->firstPolygonIndex = firstPrimIndex;
                self->ext.merman2.prim = prim;
                self->flags |= 0x800000;
                func_801D2684(prim, firstPrimIndex);
                prim->tpage = 0x12;
                prim->clut = 0x292;
                if (self->subId & 1) {
                    prim->clut = 0x293;
                }
                if (self->facing != 0) {
                    var_v0_11 = 0x1C8;
                    prim->u0 = 0xF0;
                    prim->u1 = var_v0_11;
                } else {
                    prim->u0 = 0xC8;
                    prim->u1 = 0xF0;
                }
                prim->v0 = (prim->v1 = 0);
                temp = prim->v0;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                temp = prim->v0 + 0x30;
                prim->v2 = temp;
                prim->v3 = temp;
                prim->priority = self->zPriority + 1;
                prim->blendMode = 2;
                *((s16*)(&prim->next->r2)) = 0x28;
                *((s16*)(&prim->next->b2)) = 0x30;
                prim->next->b3 = 0x80;
                if (self->facing != 0) {
                    prim->next->x1 = self->posX.i.hi - 3;
                } else {
                    prim->next->x1 = self->posX.i.hi + 3;
                }
                prim->next->y0 = self->posY.i.hi + 2;
            }
            func_801D1F38(prim);
            break;

        case 1:
            func_801BC8E4(&D_80182258);
            prim = *((s32*)(&self->ext.merman2.prim));
            self->accelerationY -= 0x3000;
            if (self->facing != 0) {
                prim->next->x1 = self->posX.i.hi - 3;
            } else {
                prim->next->x1 = self->posX.i.hi + 3;
            }
            prim->next->y0 = self->posY.i.hi + 2;
            func_801D1F38(prim);
            if (!(g_blinkTimer % 10)) {
                prim->clut += 2;
                if (prim->clut >= 0x2A0) {
                    prim->blendMode = 8;
                    self->step_s++;
                } else {
                    newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                    if (newEntity != 0) {
                        CreateEntityFromEntity(0x37, self, newEntity);
                        newEntity->facing = self->facing;
                        newEntity->subId = prim->clut;
                        newEntity->zPriority = self->zPriority;
                    }
                }
            }
            func_801C6458(0x1B);
            return;

        case 2:
            func_801C2598(0x65B);
            func_801B653C();
            DestroyEntity(self);
        }

        break;
    }
}
#endif

// some sort of explosion: ID 0x36
void EntityExplosion2(Entity* entity, s32 arg1) {
    Primitive* poly;
    s16 firstPolygonIndex;

    if (entity->step == 0) {
        InitializeEntity(D_80180AB4);
        entity->animCurFrame = 0;
        entity->unk3C = 0;
        entity->zPriority += 4;
        if (entity->subId != 0) {
            firstPolygonIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (firstPolygonIndex == -1) {
                DestroyEntity(entity);
                return;
            }
            poly = &g_PrimBuf[firstPolygonIndex];
            entity->firstPolygonIndex = firstPolygonIndex;
            *(s32*)&entity->ext.generic.unk7C.s = poly;
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
            LOH(poly->next->r2) = 0x40;
            LOH(poly->next->b2) = 0x40;
            LOH(poly->next->u1) = 0;
            poly->next->b3 = 0x60;
            poly->next->x1 = entity->posX.i.hi;
            poly->next->y0 = entity->posY.i.hi;
            poly->priority = entity->zPriority - 4;
            poly->blendMode = 6;
        }
    }

    if (entity->subId != 0) {
        poly = *(s32*)&entity->ext.generic.unk7C.s;
        func_801D1F38(poly);
        ((POLY_GT4*)poly->next)->b3 += 252;
        LOH(poly->next->u1) -= 128;
        if (poly->next->b3 < 16) {
            poly->blendMode = 8;
        }
    }

    entity->ext.generic.unk84.U8.unk0++;
    if (!(entity->ext.generic.unk84.U8.unk0 % 4)) {
        entity->posY.i.hi++;
    }

    if (AnimateEntity(D_801822B0, entity) == 0) {
        DestroyEntity(entity);
    }
}

void EntityMediumWaterSplash(Entity* entity) {
    Entity* newEntity;

    if (entity->step == 0) {
        InitializeEntity(D_80180AC0);
        entity->animCurFrame = 0;
        if (entity->facing != 0) {
            entity->accelerationX = 0x20000;
            return;
        }
        entity->accelerationX = -0x20000;
        return;
    }
    AnimateEntity(D_801822A4, entity);
    MoveEntity();
    if (entity->flags & 0x100) {
        newEntity = AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(ENTITY_EXPLOSION, entity, newEntity);
            newEntity->subId = 0;
        }
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801C7954);

void func_801C7D80(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180AB4);
        self->animCurFrame = 0;
        self->unk3C = 0;
        self->flags |= 0x2000;
        self->zPriority += 4;
    }
    MoveEntity();
    self->accelerationY += 0x2800;
    if (AnimateEntity(D_801822B8, self) == 0) {
        DestroyEntity(self);
    }
}

void func_801C7E18(Entity* self) {
    s8 temp; // probably !FAKE

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180A54);
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
        self->ext.generic.unk84.S8.unk1 = 0x11;
        self->ext.generic.unk84.S8.unk0 = self->subId;
        self->unk19 |= 8;
        break;

    case 1:
        temp = self->ext.generic.unk84.S8.unk0 - 1;
        self->ext.generic.unk84.S8.unk0--;
        self->ext.generic.unk84.S8.unk1--;
        if (!(temp & 0xFF)) {
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(D_801822C0, self);
        MoveEntity();
        self->accelerationY += 0x4000;
        self->unk1A += 6;
        self->unk1C -= 4;
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
        }
        if (!--self->ext.generic.unk84.U8.unk1) {
            self->accelerationY = 0;
            self->step++;
        }
        break;

    case 3:
        if (AnimateEntity(D_801822C0, self) == 0) {
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
        InitializeEntity(D_80180AB4);
        self->animCurFrame = 13;
        self->ext.generic.unk84.S8.unk0 = 0x20;
        self->unk3C = 0;
        self->accelerationY = 0x1000;
        self->palette = self->subId + 0xE;
        self->unk6C = 0x80;
        self->unk19 |= 8;
        self->flags |= 0x2000;
        return;
    }
    MoveEntity();
    temp_v0 = self->ext.generic.unk84.U8.unk0 - 1;
    self->ext.generic.unk84.U8.unk0--;
    self->accelerationY += 0x1000;
    self->unk6C += 0xFE;
    if (temp_v0 == 0) {
        DestroyEntity(self);
    }
}

void EntityMermanSpawner(Entity* self) {
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
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[170]);
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

#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", EntityMerman);
#else
extern u16 D_80181230[];
extern s32 D_80182338[];
extern s32 D_8018233C[];
extern u8 D_80182358[];
extern u16 D_8018235C;
extern u16 D_8018236C;
extern u16 D_8018237C;
extern u16 D_8018238C;
extern u8 D_80182394[]; // animation
extern u8 D_801823AC[]; // animation
extern u8 D_801823BC[]; // animation
extern u8 D_801823D0[]; // animation
extern u8 D_801823DC[]; // animation
extern u8 D_801823EC[]; // animation
extern s32 D_80182418[];

typedef enum {
    MERMAN_INIT,
    MERMAN_SWIMMING_UP,
    MERMAN_SWIMMING = 3,
    MERMAN_JUMPING,
    MERMAN_WALKING_TOWARDS_PLAYER,
    MERMAN_SPIT_FIRE,
    MERMAN_LUNGE,
    MERMAN_FALLING,
    MERMAN_DYING,
} MermanSteps;

typedef enum {
    MERMAN_JUMPING_SETUP,
    MERMAN_JUMPING_UNDERWATER,
    MERMAN_JUMPING_IN_AIR,
    MERMAN_JUMPING_LANDING,
} MermanJumpingSubSteps;

typedef enum {
    MERMAN_WALKING_TOWARDS_START,
    MERMAN_WALKING_TOWARDS_PLAYER_WALKING,
} MermanWalkingTowardsPlayerSubSteps;

typedef enum {
    MERMAN_SPIT_FIRE_FACE_PLAYER,
    MERMAN_SPIT_FIRE_ATTACK,
} MermanSpitFireSubSteps;

typedef enum {
    MERMAN_LUNGE_START,
    MERMAN_LUNGE_SETUP,
    MERMAN_LUNGE_TOWARDS_PLAYER,
    MERMAN_LUNGE_STANDING,
} MermanLungeSubSteps;

typedef enum {
    MERMAN_DYING_SETUP,
    MERMAN_DYING_KNOCKEDBACK,
    MERMAN_DYING_END,
} MermanDyingSubSteps;

#define NA_SE_EV_WATER_SPLASH 0x7C2

void EntityMerman(Entity* self) {
    Entity* newEntity;
    Collider collider;
    s32 colRet;
    s16* pos;
    s16 posX;
    s16 posY;
    s16 camY;
    s32 rnd;
    s32 res;
    s32 index;

    if (self->ext.merman.isUnderwater) {
        self->palette = self->ext.merman.palette;
    }
    if (self->ext.merman.ignoreCol && (self->step < MERMAN_FALLING)) {
        SetStep(MERMAN_FALLING);
    }

    if ((self->flags & 0x100) && (self->step < MERMAN_DYING)) {
        func_801C2598(0x71D);
        self->unk3C = 0;
        if (self->step == MERMAN_LUNGE) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(ENTITY_EXPLOSION, self, newEntity);
                newEntity->subId = 2;
            }
            DestroyEntity(self);
            return;
        }
        SetStep(MERMAN_DYING);
    }

    switch (self->step) {
    case MERMAN_INIT:
        InitializeEntity(D_80180ACC);
        self->ext.merman.palette = 0x2B9;
        self->zPriority = 0xA9;
        self->accelerationY = -0x10000;
        self->hitboxWidth = 5;
        self->hitboxHeight = 17;
        self->palette = self->ext.merman.palette;
        break;

    case MERMAN_SWIMMING_UP:
        if (self->step_s == 0) {
            self->hitboxWidth = 18;
            self->hitboxHeight = 4;
            self->step_s++;
        }
        AnimateEntity(D_801823D0, self);
        MoveEntity();

        posX = self->posX.i.hi;
        posY = self->posY.i.hi - 24;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (!(collider.unk0 & 8)) {
            SetStep(MERMAN_SWIMMING);
            break;
        }

    case MERMAN_SWIMMING:
        if (self->step_s == 0) {
            self->hitboxWidth = 5;
            self->hitboxHeight = 17;
            rnd = (Random() & 3) * 2;
            self->accelerationX = D_80182338[rnd];
            self->accelerationY = D_8018233C[rnd];
            self->step_s++;
        }
        if (AnimateEntity(D_801823D0, self) == 0) {
            self->facing = (GetPlayerSide() & 1) ^ 1;
        }
        MoveEntity();
        camY = g_Camera.posY.i.hi;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY -= 24;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (!(collider.unk0 & 8)) {
            self->accelerationY = 0x8000;
        }
        index = (self->subId >> 8) & 1;
        pos = &D_80181230;
        pos += index;
        posY += g_Camera.posY.i.hi;
        if (pos[4] < posY) {
            self->posY.i.hi = pos[4] - g_Camera.posY.i.hi - 24;
        }
        if ((u8)self->ext.merman.timer2++ > 32) {
            self->ext.merman.timer2 = 0;
            self->step_s = 0;
            if ((GetPlayerDistanceX() >= 48) && !(Random() & 1)) {
                SetStep(MERMAN_JUMPING);
            }
        }
        break;

    case MERMAN_JUMPING:
        switch (self->step_s) {
        case MERMAN_JUMPING_SETUP:
            self->accelerationX = 0;
            self->accelerationY = -0x88000;
            self->step_s++;
            break;

        case MERMAN_JUMPING_UNDERWATER:
            MoveEntity();
            index = (self->subId >> 8) & 1;
            pos = &D_80181230;
            pos += index;
            camY = g_Camera.posY.i.hi;
            posY = self->posY.i.hi;
            posY -= 20;
            posY += camY;
            if (posY < pos[3]) {
                g_api.PlaySfx(NA_SE_EV_WATER_SPLASH);
                newEntity = AllocEntity(D_8007DE38, &D_8007DE38[24]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x33, self, newEntity);
                    newEntity->posY.i.hi -= 20;
                    newEntity->zPriority = self->zPriority;
                }
                self->step_s++;
            }
            break;

        case MERMAN_JUMPING_IN_AIR:
            AnimateEntity(D_801823BC, self);
            if (self->ext.merman.isUnderwater == 0) {
                if (func_801BC8E4(&D_8018235C) & 1) {
                    self->animFrameDuration = 0;
                    self->animFrameIdx = 0;
                    self->step_s++;
                }
            } else {
                self->flags |= 0xC0000000;
                MoveEntity();
                self->accelerationY += 0x4000;
            }

            self->ext.merman.timer++;
            if (self->accelerationY < 0) {
                if ((self->ext.merman.palette >= 0x2B3) &&
                    !(self->ext.merman.timer % 4)) {
                    self->ext.merman.palette--;
                }
                self->palette = self->ext.merman.palette;
                newEntity = AllocEntity(D_8007DE38, &D_8007DE38[24]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x3B, self, newEntity);
                    newEntity->posX.i.hi -= 6 - ((Random() & 3) * 4);
                    newEntity->accelerationX = D_80182418[self->animFrameIdx];
                }
            } else {
                self->palette = 0x2B2;
                if (self->accelerationY > 0) {
                    func_801C6458(0x15);
                }
            }
            break;

        case MERMAN_JUMPING_LANDING:
            if (AnimateEntity(D_801823DC, self) != 0) {
                break;
            }
            SetStep(MERMAN_WALKING_TOWARDS_PLAYER);
        }
        break;

    case MERMAN_WALKING_TOWARDS_PLAYER:
        switch (self->step_s) {
        case MERMAN_WALKING_TOWARDS_START:
            self->facing = (GetPlayerSide() & 1) ^ 1;
            if (self->facing == 0) {
                self->accelerationX = -0x6000;
            } else {
                self->accelerationX = 0x6000;
            }
            self->ext.merman.timer2 = D_80182358[Random() & 3];
            self->step_s++;
            break;

        case MERMAN_WALKING_TOWARDS_PLAYER_WALKING:
            AnimateEntity(D_80182394, self);
            colRet = func_801BCB5C(&D_8018238C);
            if (colRet == 0xFF) {
                self->facing ^= 1;
            }
            if (self->facing == 0) {
                self->accelerationX = -0x6000;
            } else {
                self->accelerationX = 0x6000;
            }
            if (colRet & 0x80) {
                self->posX.val += self->accelerationX;
            }
            self->ext.merman.timer2--;
            if (!(self->ext.merman.timer2 & 0xFF)) {
                if (Random() % 2) {
                    SetStep(MERMAN_SPIT_FIRE);
                } else {
                    SetStep(MERMAN_LUNGE);
                }
            }
            res = func_801C6458(0x15);
            if (res != 0) {
                self->ext.merman.ignoreCol = 1;
            }
        }
        break;

    case MERMAN_SPIT_FIRE:
        switch (self->step_s) {
        case MERMAN_SPIT_FIRE_FACE_PLAYER:
            self->facing = (GetPlayerSide() & 1) ^ 1;
            self->step_s++;
            break;

        case MERMAN_SPIT_FIRE_ATTACK:
            if (AnimateEntity(D_801823AC, self) == 0) {
                SetStep(MERMAN_WALKING_TOWARDS_PLAYER);
            }
            if (*(s32*)&self->animFrameIdx == 4) {
                func_801C2598(0x662);
                newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x3A, self, newEntity);
                    if (self->facing != 0) {
                        newEntity->posX.i.hi += 12;
                    } else {
                        newEntity->posX.i.hi -= 12;
                    }
                    newEntity->posY.i.hi -= 10;
                    newEntity->facing = self->facing;
                }
            }
        }
        break;

    case MERMAN_LUNGE:
        switch (self->step_s) {
        case MERMAN_LUNGE_START:
            if (AnimateEntity(D_801823DC, self) == 0) {
                self->step_s++;
            }
            break;

        case MERMAN_LUNGE_SETUP:
            if (self->facing == 0) {
                self->accelerationX = 0xFFFD8000;
            } else {
                self->accelerationX = 0x28000;
            }

            self->accelerationY = -0x20000;
            self->ext.merman.timer2 = 64;
            self->animCurFrame = 12;
            self->hitboxWidth = 18;
            self->hitboxHeight = 4;
            self->step_s++;
            break;

        case MERMAN_LUNGE_TOWARDS_PLAYER:
            posY = self->posY.i.hi + 8;
            posX = self->posX.i.hi;
            if (self->facing != 0) {
                posX += 24;
            } else {
                posX -= 24;
            }
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.unk0 & 1) {
                self->accelerationX = 0;
            }
            func_801C0B20(&D_8018236C);
            if (self->facing != 0) {
                self->accelerationX -= 0x800;
            } else {
                self->accelerationX += 0x800;
            }
            self->ext.merman.timer2--;
            if ((self->ext.merman.timer2 & 0xFF) == 0) {
                self->accelerationX = 0;
                self->accelerationY = 0x20000;
                self->posY.i.hi -= 9;
                func_801BC8E4(&D_8018235C);
                self->animFrameIdx = 2;
                self->hitboxWidth = 5;
                self->animFrameDuration = 0;
                self->hitboxHeight = 17;
                self->step_s++;
            }
            func_801C6458(11);
            res = self->ext.merman.isUnderwater;
            if (res != 0) {
                self->ext.merman.ignoreCol = 1;
            }
            break;

        case MERMAN_LUNGE_STANDING:
            func_801BC8E4(&D_8018235C);
            if (AnimateEntity(D_801823DC, self) == 0) {
                self->accelerationY = 0;
                SetStep(MERMAN_WALKING_TOWARDS_PLAYER);
            }
            func_801C6458(11);
            res = self->ext.merman.isUnderwater;
            if (res != 0) {
                self->ext.merman.ignoreCol = 1;
            }
        }
        break;

    case MERMAN_FALLING:
        if (self->step_s == 0) {
            self->flags |= 0xC0000000;
            self->step_s++;
        }
        MoveEntity();
        self->accelerationY += 0x4000;
        if ((func_801C6458(0x15) == 0) &&
            (self->ext.merman.isUnderwater == 0)) {
            self->ext.merman.ignoreCol = 0;
            SetStep(MERMAN_WALKING_TOWARDS_PLAYER);
        }
        break;

    case MERMAN_DYING:
        switch (self->step_s) {
        case MERMAN_DYING_SETUP:
            self->ext.merman.palette = 0x2BC;
            self->accelerationY = 0;
            self->step_s++;

        case MERMAN_DYING_KNOCKEDBACK:
            if (func_801BC8E4(&D_8018237C) &
                1) { // only knocked up when he's on the ground)
                if (!(GetPlayerSide() & 1)) {
                    self->accelerationX = -0x8000;
                } else {
                    self->accelerationX = 0x8000;
                }
                self->step_s++;
            }

        case MERMAN_DYING_END:
            AnimateEntity(D_801823EC, self); // spinning
            MoveEntity();
            self->palette = self->ext.merman.palette;
            if (!(g_blinkTimer % 8)) {
                self->ext.merman.palette++;
                if (self->ext.merman.palette == 0x2C0) {
                    func_801C2598(0x65B);
                    newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(0x3C, self, newEntity);
                        newEntity->subId = 2;
                    }
                }
            }
            if (self->ext.merman.palette >= 0x2C5) {
                DestroyEntity(self);
            }
            break;
        }
        break;
    }
}
#endif

void func_801C8DF0(Entity* self) {
    Entity* entity;

    if (self->step == 0) {
        InitializeEntity(D_80180AD8);
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
            entity->ext.generic.unk94 = 4;
            entity->unk19 = 3;
            entity->zPriority = self->zPriority + 8;
            entity->unk1C = entity->unk1A = 192;
        }
    } else {
        AnimateEntity(D_80182400, self);
        MoveEntity();

        if (self->unk1A < 0x100) {
            self->unk1C = self->unk1A += 8;
        }

        if (self->flags & 0x100) {
            entity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (entity != NULL) {
                CreateEntityFromEntity(ENTITY_EXPLOSION, self, entity);
                entity->subId = 0;
            }
            DestroyEntity(self);
        }
    }
}

// some kind of falling object
void func_801C8F54(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180ACC);
        self->animCurFrame = 0;
        self->unk3C = 0;
        self->zPriority += 4;
        self->flags |= 0x2000;
    }
    MoveEntity();
    self->accelerationY += 0x2800;
    if (AnimateEntity(D_80182414, self) == 0) {
        DestroyEntity(self);
    }
}

void EntityMermanExplosion(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180A54);
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
