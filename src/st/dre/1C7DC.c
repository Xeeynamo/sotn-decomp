#include "dre.h"
#include "sfx.h"

static u16 g_ItemIconSlots[ICON_SLOT_NUM];

void EntityEquipItemDrop(Entity* self) {
    u16 itemId = self->params & 0x7FFF;
    s32 primIndex;
    Collider collider;
    Primitive* prim;
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
        if (g_PlayableCharacter != PLAYER_ALUCARD) {
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
                g_CastleFlags[(temp_a0 >> 3) + 0x1b0] |= 1 << (temp_a0 & 7);
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
                g_api.LoadEquipIcon(g_api.equipDefs[itemId].icon,
                                    g_api.equipDefs[itemId].iconPalette, index);
            } else {
                itemId -= NUM_HAND_ITEMS;
                g_api.LoadEquipIcon(
                    g_api.accessoryDefs[itemId].icon,
                    g_api.accessoryDefs[itemId].iconPalette, index);
            }

            prim = &g_PrimBuf[primIndex];
            vramX = ((temp_v0_6 = index) & 7) * 0x10;
            vramY = (temp_v0_6 & 0x18) * 2;

            left = vramX | 1;
            right = vramX | 0xF;
            top = 0x81;
            top = vramY | top;
            bottom = vramY | 0x8F;

            prim->tpage = 0x1A;
            prim->v3 = bottom;
            prim->clut = index + 464;
            prim->u0 = prim->u2 = left;
            prim->u1 = prim->u3 = right;
            prim->v1 = top;
            prim->v2 = bottom;
            prim->v0 = top;
            prim->priority = 0x80;
            prim->drawMode = 6;

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

        CheckFieldCollision(D_801811A4, 2);
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
            prim = &g_PrimBuf[self->primIndex];
            if (self->ext.generic.unk80.modeS8.unk0 & 2) {
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->drawMode = 2;
            }
        } else {
            DestroyEntity(self);
        }
        break;

    case 5:
        unk = &g_unkGraphicsStruct.BottomCornerTextTimer;
        if (*unk != 0) {
            g_api.FreePrimitives(g_unkGraphicsStruct.BottomCornerTextPrims);
            *unk = 0;
        }

        g_api.PlaySfx(SFX_ITEM_PICKUP);

        if (itemId < NUM_HAND_ITEMS) {
            itemName = g_api.equipDefs[itemId].name;
            g_api.AddToInventory(itemId, EQUIP_HAND);
        } else {
            itemId -= NUM_HAND_ITEMS;
            itemName = g_api.accessoryDefs[itemId].name;
            g_api.AddToInventory(itemId, EQUIP_ARMOR);
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
