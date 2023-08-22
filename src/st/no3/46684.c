#include "no3.h"

void EntityPrizeDrop(Entity* self) {
    Collider collider;
    Primitive* prim;
    s16 primIndex;
    s16 var_a2;
    u16 itemId;
    s16 temp_a0;

    itemId = self->params & 0x7FFF;
    if (self->step != 0) {
        AnimateEntity(D_80182488[itemId], self);
    }
    if (self->step - 2 < 3U && self->hitFlags != 0) {
        self->step = 5;
    }
    self->palette = 0;
    if ((u8)self->unk6D >= 0x18 && !(D_8003C8C4 & 2) && self->params != 1) {
        self->palette = 0x815F;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeData0);
        self->zPriority = g_zEntityCenter.S16.unk0 - 0x14;
        self->blendMode = 0;
        if (itemId >= 0x18) {
            self->params = 0;
            itemId = 0;
        }
        if (itemId > 13 && itemId < 23 &&
            itemId == D_80182424[g_Status.subWeapon]) {
            self->params = itemId = 1;
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
        if (self->velocityY < 0) {
            g_api.CheckCollision(
                self->posX.i.hi, self->posY.i.hi - 7, &collider, 0);
            if (collider.effects & EFFECT_NOTHROUGH) {
                self->velocityY = 0;
            }
        }
        MoveEntity();
        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 7, &collider, 0);
        if (itemId != 0) {
            if (collider.effects & EFFECT_NOTHROUGH && self->velocityY > 0) {
                self->velocityX = 0;
                self->velocityY = 0;
                self->posY.i.hi += collider.unk18;
                self->ext.generic.unk80.modeS8.unk0 = 0xF0;
                self->step++;
            } else {
                FallEntity();
            }
            func_801C5BC0(D_801824E8, 2);
        } else if (collider.effects & EFFECT_NOTHROUGH) {
            self->posY.i.hi += collider.unk18;
            self->ext.generic.unk80.modeS8.unk0 = 0x60;
            self->step++;
        } else {
            func_801C6114();
        }
        break;

    case 3:
        func_801C6198(itemId);
        if (!(self->params & 0x8000) &&
            --self->ext.generic.unk80.modeS8.unk0 == 0) {
            self->ext.generic.unk80.modeS8.unk0 = itemId == 0 ? 0x40 : 0x50;
            self->step++;
        }
        break;

    case 4:
        func_801C6198(itemId);
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
                if (itemId == D_80182424[g_Status.subWeapon]) {
                    self->params = itemId = 1;
                }
            }
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (primIndex != -1) {
                self->primIndex = primIndex;
                self->flags |= FLAG_HAS_PRIMS;
                prim = &g_PrimBuf[primIndex];
                prim->tpage = 0x1A;
                prim->clut = 0x170;
                prim->v2 = prim->v3 = 0x20;
                prim->u1 = prim->u3 = 0x20;
                prim->v0 = prim->v1 = 0;
                prim->u0 = prim->u2 = 0;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0x80;
                prim->blendMode = BLEND_VISIBLE;
                prim->priority = self->zPriority + 1;
                self->step_s++;
            }
            break;

        case 1:
            MoveEntity();
            g_api.CheckCollision(
                self->posX.i.hi, self->posY.i.hi + 7, &collider, 0);
            if (collider.effects & EFFECT_NOTHROUGH && self->velocityY > 0) {
                self->velocityX = 0;
                self->velocityY = 0;
                self->posY.i.hi += collider.unk18;
                self->step_s++;
            } else {
                FallEntity();
            }
            func_801C5BC0(D_801824E8, 2);
            self->animCurFrame = 0;
            if (self->ext.generic.unk88.S16.unk2 != 0) {
                self->ext.generic.unk88.S16.unk2--;
            } else {
                prim = &g_PrimBuf[self->primIndex];
                prim->x0 = prim->x2 = self->posX.i.hi - 1;
                prim->x1 = prim->x3 = self->posX.i.hi + 1;
                prim->y0 = prim->y1 = self->posY.i.hi - 1;
                prim->y2 = prim->y3 = self->posY.i.hi + 1;
                prim->blendMode = 0x37;
            }
            break;

        case 2:
            func_801C6198(itemId);
            prim = &g_PrimBuf[self->primIndex];
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
                g_api.FreePrimitives(self->primIndex);
                self->ext.generic.unk80.modeS8.unk0 = 0xD0;
                self->step = 3;
                self->step_s = 0;
                self->flags &= ~FLAG_HAS_PRIMS;
            }
            break;
        }

        break;
    }
}

void EntityExplosion(Entity* entity) {
    u16 zPriority;

    if (entity->step == 0) {
        InitializeEntity(g_InitializeEntityData0);
        entity->animSet = ANIMSET_DRA(2);
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
        entity->blendMode = 0x30;
        if (entity->params & 0xF0) {
            entity->palette = 0x8195;
            entity->blendMode = 0x10;
        }

        zPriority = entity->params & 0xFF00;
        if (zPriority) {
            entity->zPriority = zPriority >> 8;
        }
        entity->params &= 15;
        entity->velocityY = D_801824F4[entity->params];
    } else {
        entity->posY.val += entity->velocityY;
        if (!AnimateEntity(D_801825A0[entity->params], entity)) {
            DestroyEntity(entity);
        }
    }
}

void func_801C6FF4(Entity* entity, s32 renderFlags) {
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

void EntityEquipItemDrop(Entity* self) {
    u16 itemId = self->params & 0x7FFF;
    s32 primIndex;
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
            self->params = 0;
            self->entityId = 3;
            SetStep(0);
            EntityPrizeDrop(self);
            return;
        }
        InitializeEntity(g_InitializeData0);
        self->ext.generic.unk7C.s = 0;
        break;

    case 1:
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi, &collider, 0);

        if (!(collider.effects & EFFECT_NOTHROUGH_PLUS)) {
            for (index = 0; index < 32; index++) {
                if (UNK_Update0[index] == 0) {
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

            primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }

            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            UNK_Update0[index] = 0x1E0;
            self->ext.generic.unk8C.modeU16.unk0 = index;

            if (itemId < NUM_HAND_ITEMS) {
                g_api.LoadEquipIcon(g_api.D_800A4B04[itemId].icon,
                                    g_api.D_800A4B04[itemId].palette, index);
            } else {
                itemId -= NUM_HAND_ITEMS;
                g_api.LoadEquipIcon(g_api.D_800A7718[itemId].icon,
                                    g_api.D_800A7718[itemId].palette, index);
            }

            poly = &g_PrimBuf[primIndex];
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
        if (self->velocityY < 0) {
            g_api.CheckCollision(
                self->posX.i.hi, self->posY.i.hi - 7, &collider, 0);
            if (collider.effects & EFFECT_NOTHROUGH) {
                self->velocityY = 0;
            }
        }

        MoveEntity();

        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 7, &collider, 0);

        if ((collider.effects & EFFECT_NOTHROUGH) && (self->velocityY > 0)) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->posY.i.hi += collider.unk18;
            self->ext.generic.unk80.modeS8.unk0 = 240;
            self->step++;
        } else {
            FallEntity();
        }

        func_801C5BC0(D_801824E8, 2);
        break;

    case 3:
        func_801C6198(1);
        if (!(self->params & 0x8000)) {
            if (!(--self->ext.generic.unk80.modeS8.unk0 & 255)) {
                self->ext.generic.unk80.modeS8.unk0 = 0x50;
                self->step++;
            }
        } else {
            UNK_Update0[self->ext.generic.unk8C.modeS16.unk0] = 0x10;
        }
        break;

    case 4:
        func_801C6198(1);
        if (self->ext.generic.unk80.modeS8.unk0 += 255) {
            poly = &g_PrimBuf[self->primIndex];
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

        if (itemId < NUM_HAND_ITEMS) {
            itemName = g_api.D_800A4B04[itemId].name;
            g_api.AddToInventory(itemId, HAND_TYPE);
        } else {
            itemId -= NUM_HAND_ITEMS;
            itemName = g_api.D_800A7718[itemId].name;
            g_api.AddToInventory(itemId, ARMOR_TYPE);
        }

        func_801D06FC(itemName, 1);
        DestroyEntity(self);
        break;
    }

    if (self->step >= 2) {
        if (self->ext.generic.unk7C.u != 0) {
            self->ext.generic.unk7C.u--;
        }
        func_801C6FF4(self, self->ext.generic.unk7C.u);
    }
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", func_801C7680);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntityRelicOrb);

void EntityHeartDrop(Entity* self) {
    u16 temp_a0;
    u16 temp_a0_2;
    u16 var_a0;

    if (self->step == 0) {
        temp_a0 = self->params + 0x30;
        self->ext.generic.unkB4 = temp_a0;
        if ((D_8003BEEC[temp_a0 >> 3] >> (temp_a0 & 7)) & 1) {
            DestroyEntity(self);
            return;
        }
        temp_a0_2 = temp_a0 - 0x30;
        var_a0 = D_80181C8C[temp_a0_2];
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

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntityUnkId0E);

u8 func_801C8A84(s16* arg0, u8 facing) {
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

void EntityUnkId13(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180AE8);
        entity->ext.generic.unk8C.modeU16.unk0 =
            entity->ext.generic.unk80.entityPtr->entityId;
    case 1:
        if (entity->ext.generic.unk7C.U8.unk0++ >= 5) {
            Entity* newEntity =
                AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, entity, newEntity);
                newEntity->entityId = E_EXPLOSION;
                newEntity->pfnUpdate = EntityExplosion;
                newEntity->params = entity->params;
            }
            entity->ext.generic.unk7C.U8.unk0 = 0;
        }
        entity->posX.i.hi = entity->ext.generic.unk80.entityPtr->posX.i.hi;
        entity->posY.i.hi = entity->ext.generic.unk80.entityPtr->posY.i.hi;
        if (entity->ext.generic.unk80.entityPtr->entityId !=
            entity->ext.generic.unk8C.modeU16.unk0) {
            DestroyEntity(entity);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", func_801C8C84);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", func_801C8DB4);

void EntityUnkId14(Entity* entity) {
    if (entity->step == 0) {
        entity->velocityY = D_80182650[entity->ext.generic.unk94];
        entity->flags = FLAG_UNK_2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = ANIMSET_DRA(2);
        entity->animCurFrame = D_80182668[entity->params];
        entity->blendMode = 0x10;
        entity->step++;
    } else {
        entity->animFrameDuration++;
        entity->posY.val -= entity->velocityY;

        if (!(entity->animFrameDuration & 1)) {
            entity->animCurFrame++;
        }

        if (D_8018266C[entity->params] < (s32)entity->animFrameDuration) {
            DestroyEntity(entity);
        }
    }
}

void EntityUnkId15(Entity* arg0) {
    u16 temp_v0;

    if (arg0->step == 0) {
        arg0->flags = FLAG_UNK_2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        arg0->palette = 0x8195;
        arg0->animSet = ANIMSET_DRA(5);
        arg0->animCurFrame = 1U;
        arg0->blendMode = 0x10;
        arg0->unk19 = 3;
        temp_v0 = D_80182628[arg0->params];
        arg0->unk1A = temp_v0;
        arg0->unk1C = temp_v0;
        arg0->velocityY = D_80182638[arg0->params];
        arg0->step++;
    } else {
        arg0->animFrameDuration++;
        arg0->posY.val -= arg0->velocityY;
        if (!(arg0->animFrameDuration & 1)) {
            arg0->animCurFrame++;
        }
        if (arg0->animFrameDuration >= 37) {
            DestroyEntity(arg0);
        }
    }
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", func_801C9080);

bool func_801C92B0(Point16* unk) {
    Collider collider;

    FallEntity();
    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.val += g_CurrentEntity->velocityY;

    if (g_CurrentEntity->velocityY >= 0) {
        s16 posX = g_CurrentEntity->posX.i.hi;
        s16 posY = g_CurrentEntity->posY.i.hi;
        posX += unk->x;
        posY += unk->y;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            g_CurrentEntity->posY.i.hi += collider.unk18;
            g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY / 2;
            if (g_CurrentEntity->velocityY > FIX(-1.0)) {
                return true;
            }
        }
    }
    return false;
}

u8 func_801C93AC(s32 arg0) {
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
                if (g_CurrentEntity->velocityX > 0) {
                    bits_01 = 2;
                } else {
                    bits_01 = 3;
                    g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
                }
                g_CurrentEntity->velocityY = -g_CurrentEntity->velocityX;
                g_CurrentEntity->velocityX = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posX.val -= g_CurrentEntity->velocityX;
            if (g_CurrentEntity->velocityX > 0) {
                bits_01 = 3;
            } else {
                bits_01 = 2;
                g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
            }
            g_CurrentEntity->velocityY = g_CurrentEntity->velocityX;
            g_CurrentEntity->velocityX = 0;
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
                if (g_CurrentEntity->velocityX > 0) {
                    bits_01 = 2;
                } else {
                    bits_01 = 3;
                    g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
                }
                g_CurrentEntity->velocityY = g_CurrentEntity->velocityX;
                g_CurrentEntity->velocityX = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posX.val -= g_CurrentEntity->velocityX;
            if (g_CurrentEntity->velocityX > 0) {
                bits_01 = 3;
            } else {
                bits_01 = 2;
                g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
            }
            g_CurrentEntity->velocityY = -g_CurrentEntity->velocityX;
            g_CurrentEntity->velocityX = 0;
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
                if (g_CurrentEntity->velocityY > 0) {
                    bits_01 = 0;
                } else {
                    bits_01 = 1;
                    g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
                }
                g_CurrentEntity->velocityX = -g_CurrentEntity->velocityY;
                g_CurrentEntity->velocityY = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posY.val -= g_CurrentEntity->velocityY;
            if (g_CurrentEntity->velocityY > 0) {
                bits_01 = 1;
            } else {
                bits_01 = 0;
                g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
            }
            g_CurrentEntity->velocityX = g_CurrentEntity->velocityY;
            g_CurrentEntity->velocityY = 0;
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
                if (g_CurrentEntity->velocityY > 0) {
                    bits_01 = 0;
                } else {
                    bits_01 = 1;
                    g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
                }
                g_CurrentEntity->velocityX = g_CurrentEntity->velocityY;
                g_CurrentEntity->velocityY = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posY.val -= g_CurrentEntity->velocityY;
            if (g_CurrentEntity->velocityY > 0) {
                bits_01 = 1;
            } else {
                bits_01 = 0;
                g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
            }
            g_CurrentEntity->velocityX = -g_CurrentEntity->velocityY;
            g_CurrentEntity->velocityY = 0;
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

#include "../entity_intense_explosion.h"

void func_801903C8(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(g_InitializeEntityData0);
        entity->unk6C = 0xF0;
        entity->unk1A = 0x01A0;
        entity->unk1C = 0x01A0;
        entity->animSet = ANIMSET_DRA(8);
        entity->animCurFrame = 1;
        entity->zPriority += 16;
        if (entity->params) {
            entity->palette = entity->params;
        } else {
            entity->palette = 0x8160;
        }

        entity->step++;
    } else {
        MoveEntity();
        if (!AnimateEntity(D_8018267C, entity)) {
            DestroyEntity(entity);
        }
    }
}

void func_801C9AF8(u16 entityId, Entity* src, Entity* dst) {
    DestroyEntity(dst);
    dst->entityId = entityId;
    dst->pfnUpdate = PfnEntityUpdates[entityId - 1];
    dst->posX.i.hi = src->posX.i.hi;
    dst->posY.i.hi = src->posY.i.hi;
    dst->unk5A = src->unk5A;
    dst->zPriority = src->zPriority;
    dst->animSet = src->animSet;
    dst->flags = FLAG_UNK_2000 | FLAG_UNK_01000000 | FLAG_UNK_04000000 |
                 FLAG_UNK_08000000 | FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                 FLAG_DESTROY_IF_OUT_OF_CAMERA;

    if (src->palette & 0x8000) {
        dst->palette = src->hitEffect;
    } else {
        dst->palette = src->palette;
    }
}

void func_801C9BC0(void) {
    Entity* entity;
    s8 temp_s4 = Random() & 3;
    s16 temp_s3 = ((Random() & 0xF) << 8) - 0x800;
    s32 i;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
        if (entity != NULL) {
            CreateEntityFromEntity(2, g_CurrentEntity, entity);
            entity->ext.generic.unk84.U8.unk1 = 6 - i;
            entity->ext.generic.unk80.modeS16.unk0 = temp_s3;
            entity->ext.generic.unk84.U8.unk0 = temp_s4;
        }
    }
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", func_801C9C78);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", func_801C9E50);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", func_801CA430);

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

void func_801CAD28(s16 sfxId) {
    s32 var_a3;
    s32 temp_v0_2;
    s16 var_a2;
    s32 y;
    s16 var_v0_4;
    s16 var_v1;

    var_a3 = g_CurrentEntity->posX.i.hi - 128;
    var_a2 = (ABS(var_a3) - 32) >> 5;
    if (var_a2 > 8) {
        var_a2 = 8;
    } else if (var_a2 < 0) {
        var_a2 = 0;
    }
    if (var_a3 < 0) {
        var_a2 = -var_a2;
    }
    var_a3 = ABS(var_a3) - 96;
    y = g_CurrentEntity->posY.i.hi - 128;
    temp_v0_2 = ABS(y) - 112;
    var_v1 = var_a3;
    if (temp_v0_2 > 0) {
        var_v1 += temp_v0_2;
    }
    if (var_v1 < 0) {
        var_v0_4 = 0;
    } else {
        var_v0_4 = var_v1;
    }
    var_a3 = 127 - (var_v0_4 >> 1);
    if (var_a3 > 0) {
        g_api.func_80134714(sfxId, var_a3, var_a2);
    }
}

void func_801CAE20(Primitive* prim) {
    u8 xPos;
    s32 i;
    s32 j;

    switch (prim->p3) {
    case 0:
        if (prim->p1 < 0x80) {
            if (--prim->p1 == 0) {
                prim->p3 = 1;
            }
        } else {
            if (++prim->p1 == 0) {
                prim->p3 = 2;
            }
        }

        if (prim->p3 != 0) {
            u8* dst = prim->p3 == 1 ? &prim->r1 : &prim->r0;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 3; j++) {
                    dst[j] = 0x50;
                }
                dst += 0x18;
            }
            prim->p2 = 0;
        }
        break;
    case 1:
        if (prim->p2 < 0x14) {
            prim->p2++;
        }
        xPos = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 + xPos;
        prim->x1 = prim->x1 + xPos;
        prim->x3 = prim->x0;
        UnkLoopFunc(prim, 4);
        break;
    case 2:
        if (prim->p2 < 0x14) {
            prim->p2++;
        }
        xPos = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 - xPos;
        prim->x1 = prim->x1 - xPos;
        prim->x3 = prim->x0;
        UnkLoopFunc(prim, 4);
        break;
    }
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntityStageNamePopup);

// The white flying orbs of energy that Alucard summons as part of the Soul
// Steal spell
void EntitySoulStealOrb(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    u16* temp_d;
    u16 temp_e;
    s32 temp_a;
    s32 temp_b;
    u16 angle;
    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(g_InitializeData0);
        D_8008701E[primIndex * 0x1a] = 8;
        self->primIndex = primIndex;
        self->animSet = ANIMSET_DRA(0);
        self->flags |= FLAG_HAS_PRIMS;
        angle = func_801C57C4(self, &g_Entities[PLAYER_CHARACTER]);
        temp_a = self->posY.i.hi < 113;
        temp_b = temp_a ^ 1;
        if (self->posX.i.hi < g_Entities[PLAYER_CHARACTER].posX.i.hi) {
            temp_b = temp_a;
        }
        if (temp_b & 0xFFFF) {
            self->ext.soulStealOrb.angle = angle - D_801826D0[Random() & 7];
        } else {
            angle += D_801826D0[Random() & 7];
            self->ext.soulStealOrb.angle = angle;
        }
        self->ext.soulStealOrb.unk80 = 0x400;
        self->ext.soulStealOrb.unk7E = 0;
        self->hitboxState = 0;
        break;

    case 1:
        self->ext.soulStealOrb.unk82++;
        if (self->ext.soulStealOrb.unk82 == 16) {
            self->hitboxState = 1;
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
        self->ext.soulStealOrb.angle = func_801C5844(
            self->ext.soulStealOrb.unk7E, (u16)self->ext.soulStealOrb.angle,
            0xffff & func_801C57C4(self, &g_Entities[PLAYER_CHARACTER]));
        UnkEntityFunc0(self->ext.soulStealOrb.angle & 0xFFFF,
                       self->ext.soulStealOrb.unk80);
        MoveEntity(self);
        prim = &g_PrimBuf[self->primIndex];
        AnimateEntity(&D_80182740, self);
        angle = (float)((u32)self);
        prim->tpage = 0x18;
        prim->clut = 0x194;
        temp_d = &D_801826E0[(u16)((8 * ((u16)self->animCurFrame)) - 8)];
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

#include "../entity_enemy_blood.h"

void EntityRoomForeground(Entity* entity) {
    ObjInit2* objInit = &D_80182764[entity->params];

    if (entity->step == 0) {
        InitializeEntity(D_80180B00);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk4.s;
        entity->palette = objInit->palette;
        entity->unk19 = objInit->unk8;
        entity->blendMode = objInit->blendMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->params >= 5) {
            entity->rotAngle = 0x800;
            entity->unk19 |= 4;
        }
    }
    AnimateEntity(objInit->unk10, entity);
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", func_801CC5A4);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", func_801CC6F8);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", func_801CC820);

void func_801CC90C(Entity* arg0) {
    s16 temp_v0_2;
    s16 temp_v1;
    s16 temp_v0;

    temp_v0 = GetDistanceToPlayerX();
    temp_v1 = arg0->ext.generic.unk84.S16.unk2;
    if (temp_v1 != 0) {

        if ((u32)(temp_v0) < 0x60) {
            temp_v0_2 = temp_v1 - 2;
            arg0->ext.generic.unk84.S16.unk2 = temp_v0_2;
            if (temp_v0_2 < 0) {
                arg0->ext.generic.unk84.S16.unk2 = 0;
            }
        } else {
            arg0->ext.generic.unk84.S16.unk2 = (temp_v1 - 1);
        }
    }
}

// stronger version of warg with jump and flame attack
INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntityStrongWarg);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntityUnkId30);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntityUnkId31);

// some sort of explosion
INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntityExplosion3);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", func_801CE740);

// flame-like attack on ground from strong warg
INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntityStrongWargWaveAttack);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntityUnkId2F);

// beams that go up when strong warg dies
INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntityStrongWargDeathBeams);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", func_801CF438);

void func_801CF58C(Entity* self) {
    self->velocityX = 0;
    self->ext.generic.unk84.S16.unk2 = 0x100;
    SetStep(6);
    g_api.PlaySfx(0x783);
    self->ext.generic.unk80.modeS16.unk0 = 0x20;
}

void func_801CF5E0(Entity* self) {
    s16 temp_v0;

    if (self->facing == GetSideToPlayer()) {
        SetStep(5);
        return;
    }

    if (self->ext.generic.unk84.S16.unk2 == 0) {
        func_801CF58C(self);
        return;
    }

    temp_v0 =
        self->ext.generic.unk84.S16.unk0 - self->posX.i.hi - g_Camera.posX.i.hi;

    if (temp_v0 > 16) {
        SetStep(3);
        if (self->facing != 0) {
            self->ext.generic.unk7C.S8.unk0 = 0;
        } else {
            self->ext.generic.unk7C.S8.unk0 = 1;
        }
    } else if (temp_v0 < -16) {
        SetStep(3);
        if (self->facing != 0) {
            self->ext.generic.unk7C.S8.unk0 = 1;
        } else {
            self->ext.generic.unk7C.S8.unk0 = 0;
        }
    } else {
        SetStep(7);
    }

    self->ext.generic.unk80.modeS16.unk0 = 0;
    self->ext.generic.unk80.modeS16.unk2 = 32;
}

// duplicate of func_801CC90C in this file
void func_801CF6D8(Entity* arg0) {
    s16 temp_v0_2;
    s16 temp_v1;
    s16 temp_v0;

    temp_v0 = GetDistanceToPlayerX();
    temp_v1 = arg0->ext.generic.unk84.S16.unk2;
    if (temp_v1 != 0) {

        if ((u32)(temp_v0) < 0x60) {
            temp_v0_2 = temp_v1 - 2;
            arg0->ext.generic.unk84.S16.unk2 = temp_v0_2;
            if (temp_v0_2 < 0) {
                arg0->ext.generic.unk84.S16.unk2 = 0;
            }
        } else {
            arg0->ext.generic.unk84.S16.unk2 = (temp_v1 - 1);
        }
    }
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntityWarg);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntityUnkId4B);

// A single "puff" of the warg explosion animation, transparent
void EntityWargExplosionPuffTransparent(Entity* entity) {
    u32 temp_v0;

    if (entity->step == 0) {
        InitializeEntity(g_InitializeEntityData0);
        entity->animSet = ANIMSET_DRA(14);
        entity->unk5A = 0x79;
        entity->palette = 0xD0;
        entity->blendMode = 0x30;
        entity->unk19 = 8;
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
        entity->unk6C = 0x60;
        temp_v0 = entity->params & 0xFF00;
        if (temp_v0 != 0) {
            entity->zPriority = temp_v0 >> 8;
        }
        entity->velocityY += 0xFFFF0000;
        return;
    }
    entity->posY.val += entity->velocityY;
    if (AnimateEntity(D_8018383C, entity) == 0) {
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", func_801D06FC);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", func_801D0A2C);

// Alucard says "ahh" and turns blue from water contact
INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntityAlucardWaterEffect);

// ID 0x35
void EntitySplashWater(Entity* self) {
    Unkstruct8* tileLayout = &g_CurrentRoomTileLayout;
    u16 params = self->params;
    u16 temp_s2 = params >> 0xB;
    u16 temp_s5 = (params >> 8) & 7;
    u16 temp_s4 = (params >> 5) & 7;

    Primitive *prim, *prim2;
    Entity* newEntity;
    s16 primIndex;
    s16 temp_a0;
    s16 temp_a1;
    s16 temp_a2;
    u16 temp_t3;
    s16 temp_t8;
    char pad[0x4];
    s32 i;

    params &= 0xF;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B00);
        if (temp_s2 != 0 && temp_s4 != 7) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        } else {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        }
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            temp_t3 = self->posY.i.hi;
            temp_t8 = self->posX.i.hi;
            self->ext.waterEffects.unk82 = temp_t3 + tileLayout->unkE;
            for (i = 0; prim != NULL; i++) {
                if (i % 2) {
                    prim->u0 = prim->u2 = prim2->u0;
                    prim->u1 = prim->u3 = prim2->u1;
                    prim->v0 = prim->v1 = prim2->v0;
                    prim->v2 = prim->v3 = prim2->v2;
                    prim->y2 = prim2->y2;
                    prim->y3 = prim2->y3;
                    prim->x2 = prim->x0 = prim2->x0;
                    prim->x3 = prim->x1 = prim2->x1;
                } else {
                    prim->u1 = prim->u3 = 0x20;
                    prim->v2 = prim->v3 = 0x7C;
                    prim->u0 = prim->u2 = 0;
                    prim->v0 = prim->v1 = 96;
                    prim->y2 = prim->y3 = temp_t3;
                    prim->x2 = prim->x0 = temp_t8 - 0xE;
                    prim->x3 = prim->x1 = temp_t8 + 0xE;
                    if (i >= 2) {
                        temp_a2 = D_80183858[temp_s4];
                        if (temp_s2 >= 0xF) {
                            prim->u0 = prim->u2 = prim2->u1;
                            prim->x0 = prim->x2 = prim2->x1;
                            temp_a1 = prim2->y3;
                            prim->y2 = temp_a1;
                            if (temp_a2 != 0) {
                                prim->y3 =
                                    temp_a1 - (prim->x1 - prim->x0) / temp_a2;
                            } else {
                                prim->y3 = temp_a1;
                            }
                        } else {
                            prim->u1 = prim->u3 = prim2->u0;
                            prim->x1 = prim->x3 = prim2->x0;
                            temp_a1 = prim2->y2;
                            prim->y3 = temp_a1;
                            if (temp_a2 != 0) {
                                prim->y2 =
                                    temp_a1 + (prim->x1 - prim->x0) / temp_a2;
                            } else {
                                prim->y2 = temp_a1;
                            }
                        }
                    } else {
                        if (temp_s2 != 0) {
                            if (temp_s2 >= 0xF) {
                                prim->u1 = prim->u3 =
                                    prim->u0 + (temp_s2 << 5) / 28;
                                prim->x1 = prim->x3 = temp_s2 + prim->x0;
                            } else {
                                prim->u0 = prim->u2 =
                                    prim->u2 + (temp_s2 << 5) / 28;
                                prim->x0 = prim->x2 = temp_s2 + prim->x2;
                            }
                        }
                        if (temp_s5 != 0) {
                            temp_a0 = D_80183858[temp_s5];
                            if (temp_a0 < 0) {
                                if (temp_t8 >= prim->x1) {
                                    prim->y2 += (prim->x1 - prim->x0) / temp_a0;
                                } else {
                                    prim->y2 += (temp_t8 - prim->x0) / temp_a0;
                                    prim->y3 = prim->y3 -
                                               (prim->x1 - temp_t8) / temp_a0;
                                }
                            } else if (prim->x0 >= temp_t8) {
                                prim->y3 -= (prim->x1 - prim->x0) / temp_a0;
                            } else {
                                prim->y2 += (temp_t8 - prim->x0) / temp_a0;
                                prim->y3 -= (prim->x1 - temp_t8) / temp_a0;
                            }
                        }
                    }
                }
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                    prim->b1 = 255;
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = 128;
                prim->clut = 0x162;
                prim->tpage = 0x1A;
                prim->priority = self->zPriority + 2;
                prim->blendMode = 0x77;
                if (i % 2) {
                    prim->clut = 0x15F;
                    prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                        prim->b1 = 0;
                    prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                        prim->b3 = 96;
                    prim->blendMode = 0x37;
                    prim->priority += 2;
                }
                prim2 = prim;
                prim = prim->next;
            }

            temp_a2 = (self->posX.i.hi - 120) >> 4;
            if (temp_a2 < -8) {
                temp_a2 = -8;
                temp_a2 = -8;
            }
            if (temp_a2 > 8) {
                temp_a2 = 8;
            }

            g_api.func_80134714(D_801813A8, 0x7F, temp_a2);
            self->velocityY = D_80183878[params].x;
            self->ext.waterEffects.unk7C = D_80183878[params].y;
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_WATER_DROP, newEntity);
                newEntity->velocityY = self->velocityY;
            }
            break;
        }
        DestroyEntity(self);
        return;

    case 1:
        MoveEntity(self);
        self->velocityY += self->ext.waterEffects.unk7C;
        if (self->velocityY > FIX(2.5)) {
            self->step++;
        }
        break;

    case 2:
        MoveEntity(self);
        if (D_80086FF0[self->primIndex * 0x34] < 9) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    temp_t3 = self->ext.waterEffects.unk82 - self->posY.i.hi;
    temp_t3 -= tileLayout->unkE;
    prim = &g_PrimBuf[self->primIndex];

    for (i = 0; prim != NULL; i++) {
        prim->y0 = prim->y2 - temp_t3;
        prim->y1 = prim->y3 - temp_t3;
        if (i % 2) {
            if (prim->b3 >= 4) {
                prim->b3 += 252;
            }
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
        } else {
            if (prim->b3 >= 8) {
                prim->b3 += 252;
            }
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
            if (prim->b3 <= 8) {
                if (prim->b1 >= 8) {
                    prim->b1 += 248;
                }
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1;
            }
        }
        prim = prim->next;
    }
}

// ID 0x36
void EntitySurfacingWater(Entity* self) {
    Unkstruct8* tileLayout = &g_CurrentRoomTileLayout;
    s16 left, right, bottom;
    Primitive* prim;
    s16 primIndex;
    s16 temp_t0;
    s32 rnd;
    s16 var_s2;
    u16 params;
    s16* ptr;
    s16 temp3;
    s16 tempv0;
    s16 x, y;
    s32 i, j;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B00);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        var_s2 = (self->posX.i.hi - 120) >> 4;
        if (var_s2 < -8) {
            var_s2 = -8;
        }
        if (var_s2 > 8) {
            var_s2 = 8;
        }
        params = self->params;
        if (!(params & 0x8000)) {
            g_api.func_80134714(D_801813AA, 0x7F, var_s2);
        }
        params = (params >> 8) & 0x7F;
        prim = &g_PrimBuf[primIndex];
        right = self->posX.i.hi;
        bottom = self->posY.i.hi;
        left = right - 9;
        right += 9;
        self->ext.waterEffects.unk82 = self->posY.i.hi + g_Camera.posY.i.hi;

        for (i = 0; i < 2; i++) {
            prim->u2 = 0;
            prim->u0 = 0;
            prim->u1 = prim->u3 = 0x1E;
            prim->v0 = prim->v1 = 0x60;
            prim->v2 = prim->v3 = 0x7C;
            prim->y2 = prim->y3 = bottom;
            prim->x2 = prim->x0 = left;
            prim->x3 = prim->x1 = right;
            if (params != 0) {
                var_s2 = D_80183858[params];
                prim->y2 = prim->y2 + 9 / var_s2;
                prim->y3 = prim->y3 - 9 / var_s2;
            }
            prim->clut = 0x162;
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                255;
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                128;
            prim->tpage = 0x1A;
            prim->priority = self->zPriority + 2;
            prim->blendMode = 0x77;
            if (i != 0) {
                prim->clut = 0x161;
                prim->priority = self->zPriority + 4;
                prim->blendMode = 0x77;
            }
            prim = prim->next;
        }
        rnd = (rand() & 1) + 12;
        self->ext.generic.unk84.S16.unk2 = D_80183898[(u8)self->params] + rnd;
        self->velocityX = self->ext.generic.unk88.S16.unk2 * 16;
        if (params != 0) {
            self->velocityY = self->velocityX / var_s2;
            if (self->velocityY < 0) {
                self->velocityY = -self->velocityY;
            }
        }
        break;

    case 1:
        self->ext.waterEffects.unk84.val -= 0x4000;
        break;
    }

    MoveEntity(self);

    //! FAKE:
    j = self->velocityX;

    if (self->velocityX != 0) {
        right = D_801813AC[self->ext.waterEffects.unk88];
        ptr = D_801813AC;
        if (self->velocityX < 0) {
            right += 6;
            x = right - tileLayout->unkA;
            if (self->posX.i.hi < x) {
                DestroyEntity(self);
                return;
            }
        } else {
            ptr++;
            temp3 = tileLayout->unkA + 6;
            x = right;
            x += (ptr[self->ext.waterEffects.unk88] - temp3);
            if (self->posX.i.hi >= x) {
                DestroyEntity(self);
                return;
            }
        }
    }

    j = 0;
    tempv0 = self->ext.waterEffects.unk82;
    x = self->posX.i.hi;
    y = self->posY.i.hi;

    bottom = tempv0 - y - tileLayout->unkE;

    prim = &g_PrimBuf[self->primIndex];
    temp_t0 = x - 9;
    x += 9;

    while (j < 2) {
        prim->y2 = prim->y2 - bottom;
        prim->y3 = prim->y3 - bottom;
        prim->y0 = prim->y2 - self->ext.waterEffects.unk84.modeS16.unk2;
        prim->y1 = prim->y3 - self->ext.waterEffects.unk84.modeS16.unk2;
        prim->x2 = prim->x0 = temp_t0;
        prim->x3 = prim->x1 = x;
        prim->b1 += 248;
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1;
        prim->b3 += 252;
        prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
        if (prim->r0 < 9) {
            DestroyEntity(self);
            return;
        }
        prim = prim->next;
        j++;
    }
    self->ext.waterEffects.unk82 = self->posY.i.hi + tileLayout->unkE;
}

// small water droplets go to the side
INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntitySideWaterSplash);

// small water droplets go upwards
INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntitySmallWaterDrop);

// ID 0x38
void EntityWaterDrop(Entity* self) {
    u16 x = self->posX.i.hi;
    u16 y = self->posY.i.hi;
    Primitive* prim;
    s16 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B00);
        primIndex = g_api.func_800EDB58(0x11, 0x21);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.generic.unk7C.s = 0x2F;
        self->flags |= FLAG_HAS_PRIMS;

        while (1) {
            prim->blendMode = 0x73;
            prim->priority = self->zPriority + 2;

            if (prim->next == NULL) {
                prim->u0 = 0;
                prim->x0 = 0;
                prim->y0 = 0;
                prim->blendMode &= ~BLEND_VISIBLE;
                break;
            }

            prim->x1 = 0;
            LOH(prim->r1) = 0;
            LOW(prim->r2) = (rand() * 8) + self->velocityY;
            prim->y1 = y + (rand() & 15);
            LOH(prim->b1) = x + (rand() & 31) - 16;
            LOH(prim->u2) = (rand() & 15) + 32;
            prim->b0 = prim->g0 = prim->r0 = 255;
            prim->v0 = prim->u0 = 2;
            prim->x0 = LOH(prim->b1);
            prim->y0 = prim->y1;
            prim = prim->next;
        }
        break;

    case 1:
        if (--self->ext.generic.unk7C.s == 0) {
            DestroyEntity(self);
            return;
        }

        prim = &g_PrimBuf[self->primIndex];

        while (1) {
            if (prim->next == NULL) {
                prim->u0 = 0;
                prim->x0 = 0;
                prim->y0 = 0;
                prim->blendMode &= ~BLEND_VISIBLE;
                return;
            }
            LOH(prim->b1) = prim->x0;
            prim->y1 = prim->y0;
            LOH(prim->u2)--;
            if (LOH(prim->u2) == 0) {
                prim->blendMode |= BLEND_VISIBLE;
            }
            LOW(prim->x1) += LOW(prim->r2);
            if (LOW(prim->r2) > 0x8000) {
                prim->r0 += 252;
                prim->g0 += 252;
                prim->b0 += 252;
            } else {
                LOW(prim->r2) += 0x3800;
            }
            prim->x0 = LOW(prim->b1);
            prim->y0 = prim->y1;
            prim = prim->next;
        }
        break;
    }
}

s32 func_801D2D40(s16 yVector) {
    s16 newY = yVector + g_CurrentEntity->posY.i.hi;
    s32 expectedResult = 0;
    Collider collider;
    Entity* newEntity;
    s32 res;

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi, newY, &collider, 0);
    res = expectedResult == (collider.effects & EFFECT_SOLID);

    if (collider.effects & EFFECT_WATER) {
        if (*(u8*)&g_CurrentEntity->ext.generic.unkA0 == 0) {
            newEntity = AllocEntity(&D_8007DE38, &D_8007DE38[24]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x3B, g_CurrentEntity, newEntity);
                newEntity->posY.i.hi += yVector;
                newEntity->zPriority = g_CurrentEntity->zPriority;
            }
            g_api.PlaySfx(0x7C2);
            *(u8*)&g_CurrentEntity->ext.generic.unkA0 = 1;
        }
    }
    return res;
}

// another merman variant
INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntityMerman3);

// some sort of explosion
void EntityExplosion2(Entity* entity, s32 arg1) {
    POLY_GT4* poly;
    s16 primIndex;

    if (entity->step == 0) {
        InitializeEntity(D_80180B48);
        entity->animCurFrame = 0;
        entity->hitboxState = 0;
        entity->zPriority += 4;
        if (entity->params != 0) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex == -1) {
                DestroyEntity(entity);
                return;
            }
            poly = &g_PrimBuf[primIndex];
            entity->primIndex = primIndex;
            *(s32*)&entity->ext.generic.unk7C.s = poly;
            entity->flags |= FLAG_HAS_PRIMS;
            func_801D6FCC(poly, primIndex);
            poly->u0 = 0;
            poly->u1 = 0x20;
            poly->tpage = 0x1A;
            poly->clut = 0x1FF;
            poly->v3 = poly->v2 = 0x20;
            poly->v1 = poly->v0 = 0;
            poly->u2 = poly->u0;
            poly->u3 = poly->u1;
            LOH(((POLY_GT4*)poly->tag)->r2) = 0x40;
            LOH(((POLY_GT4*)poly->tag)->b2) = 0x40;
            LOH(((POLY_GT4*)poly->tag)->u1) = 0;
            ((POLY_GT4*)poly->tag)->b3 = 0x60;
            ((POLY_GT4*)poly->tag)->x1 = (u16)entity->posX.i.hi;
            ((POLY_GT4*)poly->tag)->y0 = (u16)entity->posY.i.hi;
            poly->pad2 = entity->zPriority - 4;
            poly->pad3 = 6;
        }
    }

    if (entity->params != 0) {
        poly = *(s32*)&entity->ext.generic.unk7C.s;
        func_801D6880(poly);
        ((POLY_GT4*)poly->tag)->b3 += 252;
        LOH(((POLY_GT4*)poly->tag)->u1) -= 128;
        if (((POLY_GT4*)poly->tag)->b3 < 16) {
            poly->pad3 = 8;
        }
    }

    entity->ext.generic.unk84.U8.unk0++;
    if (!(entity->ext.generic.unk84.U8.unk0 % 4)) {
        entity->posY.i.hi++;
    }

    if (AnimateEntity(D_801839A0, entity) == 0) {
        DestroyEntity(entity);
    }
}

// medium sized water splash used with merman
void EntityMediumWaterSplash(Entity* entity) {
    Entity* newEntity;

    if (entity->step == 0) {
        InitializeEntity(D_80180B54);
        entity->animCurFrame = 0;
        if (entity->facing != 0) {
            entity->velocityX = FIX(2);
            return;
        }
        entity->velocityX = FIX(-2);
        return;
    }
    AnimateEntity(D_80183994, entity);
    MoveEntity();
    if (entity->flags & 0x100) {
        newEntity = AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(2, entity, newEntity);
            newEntity->params = 0;
        }
        DestroyEntity(entity);
    }
}

// spawns EntityMediumWaterSplash, part of merman splash
INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntityLargeWaterSplash);

// some kind of falling object
void EntityFallingObject2(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180B48);
        self->animCurFrame = 0;
        self->hitboxState = 0;
        self->flags |= 0x2000;
        self->zPriority += 4;
    }
    MoveEntity();
    self->velocityY += FIX(0.15625);
    if (AnimateEntity(D_801839A8, self) == 0) {
        DestroyEntity(self);
    }
}

void EntityUnkId3D(Entity* self) {
    s8 temp; // probably !FAKE

    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeEntityData0);
        self->animSet = ANIMSET_DRA(2);
        self->velocityY = FIX(-5);
        self->palette = 0x8162;
        self->blendMode = 0x10;
        self->palette = 0x8018;
        self->blendMode = 0x30;
        self->unk6C = 0xA0;
        self->unk1A = 0x100;
        self->unk1C = 0x1A0;
        self->unk19 |= 3;
        self->ext.generic.unk84.S8.unk1 = 0x11;
        self->ext.generic.unk84.S8.unk0 = self->params;
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
        AnimateEntity(D_801839B0, self);
        MoveEntity();
        self->velocityY += FIX(0.25);
        self->unk1A += 6;
        self->unk1C -= 4;
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
        }
        if (!--self->ext.generic.unk84.U8.unk1) {
            self->velocityY = 0;
            self->step++;
        }
        break;

    case 3:
        if (AnimateEntity(D_801839B0, self) == 0) {
            MoveEntity();
            self->velocityY += FIX(0.25);
            self->unk1A += 6;
            self->unk1C -= 4;
        }
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
        }
        break;
    }
}

// falling object, larger
void EntityLargeFallingObject(Entity* self) {
    u8 temp_v0;

    if (self->step == 0) {
        InitializeEntity(D_80180B48);
        self->animCurFrame = 13;
        self->ext.generic.unk84.S8.unk0 = 0x20;
        self->hitboxState = 0;
        self->velocityY = FIX(0.0625);
        self->palette = self->params + 0xE;
        self->unk6C = 0x80;
        self->unk19 |= 8;
        self->flags |= 0x2000;
        return;
    }
    MoveEntity();
    temp_v0 = self->ext.generic.unk84.U8.unk0 - 1;
    self->ext.generic.unk84.U8.unk0--;
    self->velocityY += FIX(0.0625);
    self->unk6C += 0xFE;
    if (temp_v0 == 0) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntityMermanSpawner);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntityMerman);

// fireball shot by merman
void EntityMermanFireball(Entity* self) {
    Entity* entity;

    if (self->step == 0) {
        InitializeEntity(D_80180B6C);
        self->hitboxWidth = 6;
        self->animCurFrame = 0;
        self->hitboxHeight = 3;

        if (self->facing != 0) {
            self->velocityX = 0x10000 | 0x8000; // LINT_IGNORE
        } else {
            self->velocityX = 0xFFFE0000 | 0x8000; // LINT_IGNORE
        }

        self->unk19 = 3;
        self->unk1C = self->unk1A = 0x80;

        entity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_ID_15, self, entity);
            entity->ext.generic.unk94 = 4;
            entity->unk19 = 3;
            entity->zPriority = self->zPriority + 8;
            entity->unk1C = entity->unk1A = 192;
        }
    } else {
        AnimateEntity(D_80183AF0, self);
        MoveEntity();

        if (self->unk1A < 0x100) {
            self->unk1C = self->unk1A += 8;
        }

        if (self->flags & 0x100) {
            entity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (entity != NULL) {
                CreateEntityFromEntity(2, self, entity);
                entity->params = 0;
            }
            DestroyEntity(self);
        }
    }
}

// some sort of falling object
void EntityFallingObject(Entity* arg0) {
    if (arg0->step == 0) {
        InitializeEntity(D_80180B60);
        arg0->animCurFrame = 0;
        arg0->hitboxState = 0;
        arg0->zPriority += 4;
        arg0->flags |= 0x2000;
    }
    MoveEntity();
    arg0->velocityY += 0x2800;
    if (AnimateEntity(D_80183B04, arg0) == 0) {
        DestroyEntity(arg0);
    }
}

// part of explosion when merman dies
INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntityMermanExplosion);

s32 func_801C52EC(s32*);
s32 func_801C5A98(u16* hitSensors, s16 sensorCount);

void func_801D59D0(void) {
    s32 temp = func_801C52EC(&D_80183C30);
    s32 temp2 = func_801C5A98(&D_80183C38, 3);

    if ((temp == 128) || (temp2 & 2)) {
        SetStep(5);
        return;
    }

    if (g_CurrentEntity->ext.generic.unk7C.U8.unk0 == 0) {
        if (GetDistanceToPlayerX() < 64) {
            if (g_CurrentEntity->facing != (GetSideToPlayer() & 1)) {
                SetStep(4);
            }
        }
    } else {
        g_CurrentEntity->ext.generic.unk7C.U8.unk0--;
    }
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/46684", EntityBoneScimitar);

// debris that rotates and falls down
void EntityBoneScimitarParts(Entity* entity) {
    if (entity->step) {
        entity->ext.generic.unk88.S8.unk0--;
        if (entity->ext.generic.unk88.S8.unk0 & 0xFF) {
            entity->rotAngle += D_80183BA8[entity->params];
            FallEntity();
            MoveEntity();
            return;
        }
        entity->entityId = E_EXPLOSION;
        entity->pfnUpdate = EntityExplosion;
        entity->params = 0;
        entity->step = 0;
        return;
    }
    InitializeEntity(D_80180B84);
    entity->unk19 = 4;
    entity->animCurFrame = *(u8*)&entity->params + 16;

    if (entity->facing != 0) {
        entity->velocityX = -entity->velocityX;
    }

    if (entity->params & 0xF00) {
        entity->palette += entity->params / 256;
    }
}
