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
    if (self->step - 2 < 3U && self->hitFlags != 0) {
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
        if (collider.effects & EFFECT_NOTHROUGH_PLUS) {
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
            if (collider.effects & EFFECT_NOTHROUGH) {
                self->accelerationY = 0;
            }
        }
        MoveEntity();
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi + 7, &collider,
                             0);
        if (itemId != 0) {
            if (collider.effects & EFFECT_NOTHROUGH &&
                self->accelerationY > 0) {
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
        } else if (collider.effects & EFFECT_NOTHROUGH) {
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
            if (collider.effects & EFFECT_NOTHROUGH &&
                self->accelerationY > 0) {
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

    if (((self->step - 2) < 3U) && (self->hitFlags != 0)) {
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

        if (!(collider.effects & EFFECT_NOTHROUGH_PLUS)) {
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
            if (collider.effects & EFFECT_NOTHROUGH) {
                self->accelerationY = 0;
            }
        }

        MoveEntity();

        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi + 7, &collider,
                             0);

        if ((collider.effects & EFFECT_NOTHROUGH) &&
            (self->accelerationY > 0)) {
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
            if (self->hitFlags != 0) {
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
    Collider collider;
    s16 posX, posY;

    while (*arg0 != 0xFF) {
        ret <<= 1;

        posX = facing ? (g_CurrentEntity->posX.i.hi + *arg0++)
                      : (g_CurrentEntity->posX.i.hi - *arg0++);
        posY = g_CurrentEntity->posY.i.hi + *arg0++;

        g_api.CheckCollision(posX, posY, &collider, 0);

        if (collider.effects & EFFECT_SOLID) {
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
                CreateEntityFromEntity(E_EXPLOSION, entity, newEntity);
                newEntity->objectId = E_EXPLOSION;
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

bool func_801C0B20(point16* unk) {
    Collider collider;

    FallEntity();
    g_CurrentEntity->posX.val += g_CurrentEntity->accelerationX;
    g_CurrentEntity->posY.val += g_CurrentEntity->accelerationY;

    if (g_CurrentEntity->accelerationY >= 0) {
        s16 posX = g_CurrentEntity->posX.i.hi;
        s16 posY = g_CurrentEntity->posY.i.hi;
        posX += unk->x;
        posY += unk->y;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            g_CurrentEntity->posY.i.hi += collider.unk18;
            g_CurrentEntity->accelerationY =
                -g_CurrentEntity->accelerationY / 2;
            if (g_CurrentEntity->accelerationY > -0x10000) {
                return true;
            }
        }
    }
    return false;
}

u8 func_801C0C1C(s32 arg0) {
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
            g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                                 (s16)(g_CurrentEntity->posY.i.hi - 4),
                                 &collider, 0);
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
            g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                                 (s16)(g_CurrentEntity->posY.i.hi + 4),
                                 &collider, 0);
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
            CreateEntityFromEntity(E_EXPLOSION, g_CurrentEntity, entity);
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

        self->rotAngle = self->ext.generic.unk80.modeS16.unk0 &= 0xFFF;
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

// The white flying orbs of energy that Alucard summons as part of the Soul
// Steal spell
void EntitySoulStealOrb(Entity* self) {
    Primitive* prim;
    s32 firstPrimIndex;
    u16* temp_d;
    u16 temp_e;
    s32 temp_a;
    s32 temp_b;
    u16 angle;
    switch (self->step) {
    case 0:
        firstPrimIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (firstPrimIndex == (-1)) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(D_80180A48);
        D_8008701E[firstPrimIndex * 0x1a] = 8;
        self->firstPolygonIndex = firstPrimIndex;
        self->animSet = 0;
        self->flags |= 0x800000;
        angle = func_801BD034(self, &g_Entities[PLAYER_CHARACTER]);
        temp_a = self->posY.i.hi < 113;
        temp_b = temp_a ^ 1;
        if (self->posX.i.hi < g_Entities[PLAYER_CHARACTER].posX.i.hi) {
            temp_b = temp_a;
        }
        if (temp_b & 0xFFFF) {
            self->ext.soulStealOrb.angle = angle - D_8018205C[Random() & 7];
        } else {
            angle += D_8018205C[Random() & 7];
            self->ext.soulStealOrb.angle = angle;
        }
        self->ext.soulStealOrb.unk80 = 0x400;
        self->ext.soulStealOrb.unk7E = 0;
        self->unk3C = 0;
        break;

    case 1:
        self->ext.soulStealOrb.unk82++;
        if (self->ext.soulStealOrb.unk82 == 16) {
            self->unk3C = 1;
        }
        if (self->hitFlags != 0) {
            if (g_Player.unk56 == 0) {
                g_Player.unk56 = 1;
                g_Player.unk58 = 8;
            }
            DestroyEntity(self);
            return;
        }
        if (self->unk1A < 0x100) {
            self->unk1A = (self->unk1C += 0x10);
        }
        if (self->ext.soulStealOrb.unk7E < 0x200) {
            self->ext.soulStealOrb.unk7E += 2;
        }
        if (self->ext.soulStealOrb.unk80 < 0x800) {
            self->ext.soulStealOrb.unk80 += 4;
        }
        self->ext.soulStealOrb.angle = func_801BD0B4(
            self->ext.soulStealOrb.unk7E, (u16)self->ext.soulStealOrb.angle,
            0xffff & func_801BD034(self, &g_Entities[PLAYER_CHARACTER]));
        func_801BCF78(self->ext.soulStealOrb.angle & 0xFFFF,
                      self->ext.soulStealOrb.unk80);
        MoveEntity(self);
        prim = &g_PrimBuf[self->firstPolygonIndex];
        AnimateEntity(&D_801820CC, self);
        angle = (float)((u32)self);
        prim->tpage = 0x18;
        prim->clut = 0x194;
        temp_d = &D_8018206C[(u16)((8 * ((u16)self->animCurFrame)) - 8)];
        prim->x0 = (prim->x2 = self->posX.i.hi + (*(temp_d++)));
        prim->y0 = (prim->y1 = self->posY.i.hi + (*(temp_d++)));
        prim->x1 = (prim->x3 = prim->x0 + (*(temp_d++)));
        prim->y2 = (prim->y3 = prim->y0 + (*(temp_d++)));
        prim->u0 = (prim->u2 = *(temp_d++));
        prim->v0 = (prim->v1 = *(temp_d++));
        prim->u1 = (prim->u3 = *(temp_d++));
        prim->v2 = (prim->v3 = *(temp_d++));
        prim->priority = self->zPriority;
        prim->blendMode = 0;
        break;
    }
}

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

                if (self->hitFlags != 0) {
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
            entity->rotAngle = 0x800;
            entity->unk19 |= 4;
        }
    }
    AnimateEntity(objInit->unk10, entity);
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801C3E14);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801C4144);

// ID 0x2C
INCLUDE_ASM("asm/us/st/np3/nonmatchings/3DEF4", func_801C424C);
