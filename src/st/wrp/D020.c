#include "wrp.h"

u16 D_80180DF4[];
u8* D_80180E58[];
u16 D_80180EB8[];

void EntityPrizeDrop(Entity* self) {
    Collider collider;
    Primitive* prim;
    s16 primIndex;
    s16 var_a2;
    u16 itemId;
    s16 temp_a0;

    // if self->params & 0x8000 then the item will not disappear
    // self->ext.generic.unk80.modeS8.unk0: frames left before the prize
    // disappear
    itemId = self->params & 0x7FFF;
    if (self->step != 0) {
        AnimateEntity(D_80180E58[itemId], self);
    }
    if (self->step - 2 < 3U && self->hitFlags != 0) {
        self->step = 5;
    }
    self->palette = 0;
    if ((u8)self->unk6D[0] >= 0x18 && !(D_8003C8C4 & 2) && self->params != 1) {
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
            itemId == D_80180DF4[g_Status.subWeapon]) {
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
            func_8018C55C(D_80180EB8, 2);
        } else if (collider.effects & EFFECT_NOTHROUGH) {
            self->posY.i.hi += collider.unk18;
            self->ext.generic.unk80.modeS8.unk0 = 0x60;
            self->step++;
        } else {
            func_8018CAB0();
        }
        break;

    case 3:
        func_8018CB34(itemId);
        if (!(self->params & 0x8000) &&
            --self->ext.generic.unk80.modeS8.unk0 == 0) {
            self->ext.generic.unk80.modeS8.unk0 = itemId == 0 ? 0x40 : 0x50;
            self->step++;
        }
        break;

    case 4:
        func_8018CB34(itemId);
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
                if (itemId == D_80180DF4[g_Status.subWeapon]) {
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
            func_8018C55C(D_80180EB8, 2);
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
            func_8018CB34(itemId);
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

u16 D_80180458[];
s32 D_80180EC4[];
u8* D_80180F70[];
void EntityExplosion(Entity* entity) {
    u16 zPriority;

    if (entity->step == 0) {
        InitializeEntity(D_80180458);
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
        entity->velocityY = D_80180EC4[entity->params];
    } else {
        entity->posY.val += entity->velocityY;
        if (!AnimateEntity(D_80180F70[entity->params], entity)) {
            DestroyEntity(entity);
        }
    }
}

void BlinkItem(Entity* arg0, u16 renderFlags) {
    POLY_GT4* poly;
    s16 left, top, right, bottom;

    poly = &g_PrimBuf[arg0->primIndex];

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
        self->ext.equipItemDrop.timer = 0;
        break;

    case 1:
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi, &collider, 0);

        if (!(collider.effects & EFFECT_NOTHROUGH_PLUS)) {
            for (index = 0; index < 32; index++) {
                if (g_ItemIconSlots[index] == 0) {
                    break;
                }
            }

            if (index >= 32) {
                DestroyEntity(self);
                return;
            }

            if (LOH(self->ext.equipItemDrop.unk94) != 0) {
                temp_a0 = LOH(self->ext.equipItemDrop.unk94);
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
            g_ItemIconSlots[index] = 0x1E0;
            self->ext.equipItemDrop.unk8C = index;

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

            self->ext.equipItemDrop.timer = 128;
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
            self->ext.equipItemDrop.unk80 = 240;
            self->step++;
        } else {
            FallEntity();
        }

        func_8018C55C(D_80180EB8, 2);
        break;

    case 3:
        func_8018CB34(1);
        if (!(self->params & 0x8000)) {
            if (!(--self->ext.equipItemDrop.unk80 & 255)) {
                self->ext.equipItemDrop.unk80 = 0x50;
                self->step++;
            }
        } else {
            g_ItemIconSlots[self->ext.equipItemDrop.unk8C] = 0x10;
        }
        break;

    case 4:
        func_8018CB34(1);
        if (self->ext.equipItemDrop.unk80 += 255) {
            poly = &g_PrimBuf[self->primIndex];
            if (self->ext.equipItemDrop.unk80 & 2) {
                poly->pad3 = 8;
            } else {
                poly->pad3 = 2;
            }
        } else {
            DestroyEntity(self);
        }
        break;

    case 5:
        unk = &g_BottomCornerTextTimer;
        if (*unk != 0) {
            g_api.FreePrimitives(g_BottomCornerTextPrims);
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

        BottomCornerText(itemName, 1);
        DestroyEntity(self);
        break;
    }

    if (self->step >= 2) {
        if (self->ext.equipItemDrop.timer != 0) {
            self->ext.equipItemDrop.timer--;
        }
        BlinkItem(self, self->ext.equipItemDrop.timer);
    }
}

#include "../blit_char.h"
