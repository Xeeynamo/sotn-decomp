#include "dre.h"

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
                if (g_ItemIconSlots[index] == 0) {
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
            g_ItemIconSlots[index] = 0x1E0;
            self->ext.generic.unk8C.modeU16.unk0 = index;

            if (itemId < NUM_HAND_ITEMS) {
                g_api.LoadEquipIcon(
                    g_api.D_800A4B04[itemId].icon,
                    g_api.D_800A4B04[itemId].iconPalette, index);
            } else {
                itemId -= NUM_HAND_ITEMS;
                g_api.LoadEquipIcon(
                    g_api.D_800A7718[itemId].icon,
                    g_api.D_800A7718[itemId].iconPalette, index);
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
            self->posY.i.hi += *(u16*)&collider.unk18;
            self->ext.generic.unk80.modeS8.unk0 = 240;
            self->step++;
        } else {
            FallEntity();
        }

        func_8019B304(D_801811A4, 2);
        break;

    case 3:
        func_8019B8DC(1);
        if (!(self->params & 0x8000)) {
            if (!(--self->ext.generic.unk80.modeS8.unk0 & 255)) {
                self->ext.generic.unk80.modeS8.unk0 = 0x50;
                self->step++;
            }
        } else {
            g_ItemIconSlots[self->ext.generic.unk8C.modeS16.unk0] = 0x10;
        }
        break;

    case 4:
        func_8019B8DC(1);
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
        if (self->ext.generic.unk7C.u != 0) {
            self->ext.generic.unk7C.u--;
        }
        BlinkItem(self, self->ext.generic.unk7C.u);
    }
}

#include "../blit_char.h"
