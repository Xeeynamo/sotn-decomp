// SPDX-License-Identifier: AGPL-3.0-or-later

void EntityEquipItemDrop(Entity* self) {
    Collider collider;
    Primitive* prim;
    s16 i;
    u16 itemId;
    s16 index;
    s32 primIndex;
    const char* name;

    itemId = self->params & 0x7FFF;
    if (
#if defined(VERSION_US) && STAGE != STAGE_ST0
        self->step >= 2 &&
#else
        self->step &&
#endif
        self->step < 5 && self->hitFlags) {
        self->step = 5;
    }

    switch (self->step) {
    case 0:
#if !(defined VERSION_BETA || STAGE == STAGE_ST0)
        if (g_PlayableCharacter != PLAYER_ALUCARD) {
            self->params = 0;
            self->pfnUpdate = EntityPrizeDrop;
            self->entityId = 3;
            SetStep(0);
            EntityPrizeDrop(self);
            return;
        }
#endif
        InitializeEntity(g_EInitObtainable);
        self->ext.equipItemDrop.timer = 0;
        break;
    case 1:
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi, &collider, 0);
        if (collider.effects & EFFECT_NOTHROUGH_PLUS) {
            DestroyEntity(self);
            break;
        }

        for (i = 0; i < LEN(g_ItemIconSlots); i++) {
            if (!g_ItemIconSlots[i]) {
                break;
            }
        }
        if (i >= LEN(g_ItemIconSlots)) {
            DestroyEntity(self);
            return;
        }
#if !(defined VERSION_BETA || STAGE == STAGE_ST0)
        index = self->ext.equipItemDrop.castleFlag;
        if (index) {
            index--;
            g_CastleFlags[(index >> 3) + ENEMY_LIST_RAREDROP_1B0] |=
                1 << (index & 7);
        }
#endif
        primIndex = g_api.AllocPrimBuffers(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        g_ItemIconSlots[i] = 0x1E0;
#if !(defined VERSION_BETA || STAGE == STAGE_ST0)
        self->ext.equipItemDrop.iconSlot = i;
#endif
        if (itemId < NUM_HAND_ITEMS) {
            g_api.LoadEquipIcon(g_api.equipDefs[itemId].icon,
                                g_api.equipDefs[itemId].iconPalette, i);
        } else {
            itemId -= NUM_HAND_ITEMS;
            g_api.LoadEquipIcon(g_api.accessoryDefs[itemId].icon,
                                g_api.accessoryDefs[itemId].iconPalette, i);
        }

        prim = &g_PrimBuf[primIndex];
        prim->tpage = 0x1A;
        prim->clut = i + 464;

#ifdef VERSION_PSP
        prim->u0 = prim->u2 = (i & 7) * 0x10 + 1;
#else
        prim->u0 = prim->u2 = (u8)(i & 7) * 0x10 + 1;
#endif
        prim->u1 = prim->u3 = prim->u0 + 0xE;

#ifdef VERSION_PSP
        prim->v0 = prim->v1 = (i & 0x18) * 2 + 0x81;
#else
        prim->v0 = prim->v1 = (u8)(i & 0x18) * 2 + 0x81;
#endif
        prim->v2 = prim->v3 = prim->v0 + 0xE;

        prim->priority = 0x80;
        prim->drawMode = DRAW_UNK02 | DRAW_COLORS;

        self->ext.equipItemDrop.timer = 128;
        self->step++;
        break;
    case 2:
#if defined VERSION_BETA || STAGE == STAGE_ST0
        if (self->velocityX < 0) {
#else
        if (self->velocityY < 0) {
#endif
            g_api.CheckCollision(
                self->posX.i.hi, self->posY.i.hi - 7, &collider, 0);
            if (collider.effects & EFFECT_NOTHROUGH) {
                self->velocityY = 0;
            }
        }
        MoveEntity();
        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 7, &collider, 0);
        if ((collider.effects & EFFECT_NOTHROUGH) && self->velocityY > 0) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->posY.i.hi += collider.unk18;
            self->ext.equipItemDrop.aliveTimer = 240;
            self->step++;
        } else {
            FallEntity();
        }
        CheckFieldCollision(D_80180EB8, 2);
        break;
    case 3:
        PrizeDropFall2(1);
        if (!(self->params & 0x8000)) {
            if (!(--self->ext.equipItemDrop.aliveTimer)) {
                self->ext.equipItemDrop.aliveTimer = 80;
                self->step++;
            }
#if !(defined VERSION_BETA || STAGE == STAGE_ST0)
        } else {
            i = self->ext.equipItemDrop.iconSlot;
            g_ItemIconSlots[i] = 0x10;
#endif
        }
        break;
    case 4:
        PrizeDropFall2(1);
        if (--self->ext.equipItemDrop.aliveTimer) {
            prim = &g_PrimBuf[self->primIndex];
            if (self->ext.equipItemDrop.aliveTimer & 2) {
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->drawMode = DRAW_UNK02;
            }
        } else {
            DestroyEntity(self);
        }
        break;
    case 5:
        if (g_unkGraphicsStruct.BottomCornerTextTimer) {
            g_api.FreePrimitives(g_unkGraphicsStruct.BottomCornerTextPrims);
            g_unkGraphicsStruct.BottomCornerTextTimer = 0;
        }
        g_api.PlaySfx(SFX_ITEM_PICKUP);
        if (itemId < NUM_HAND_ITEMS) {
            name = g_api.equipDefs[itemId].name;
            g_api.AddToInventory(itemId, EQUIP_HAND);
        } else {
            itemId -= NUM_HAND_ITEMS;
            name = g_api.accessoryDefs[itemId].name;
            g_api.AddToInventory(itemId, EQUIP_ARMOR);
        }
        BottomCornerText(name, 1);
        DestroyEntity(self);
        break;
    }

    if (self->step > 1) {
#if !(defined VERSION_BETA || STAGE == STAGE_ST0)
        if (self->ext.equipItemDrop.timer) {
            self->ext.equipItemDrop.timer--;
        }
        BlinkItem(self, self->ext.equipItemDrop.timer);
#else
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = prim->x2 = self->posX.i.hi - 7;
        prim->x1 = prim->x3 = prim->x0 + 0xE;
        prim->y0 = prim->y1 = self->posY.i.hi - 7;
        prim->y2 = prim->y3 = prim->y0 + 0xE;
        if (self->ext.equipItemDrop.timer) {
            self->ext.equipItemDrop.timer--;
            if (self->ext.equipItemDrop.timer & 2) {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 =
                    prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                        prim->b2 = prim->b3 = 0xFF;
            } else {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 =
                    prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                        prim->b2 = prim->b3 = 0x80;
            }
        }
#endif
    }
}
