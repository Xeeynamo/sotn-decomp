#include "st0.h"
#include "sfx.h"

void func_801B5EC8(void) {
    s32 temp_v1;
    Entity* entity;

    entity = g_CurrentEntity;
    if (entity->velocityY >= 0) {
        temp_v1 =
            entity->ext.generic.unk88.S16.unk0 + entity->ext.generic.unk84.unk;
        entity->ext.generic.unk84.unk = temp_v1;
        entity->velocityX = temp_v1;
        if (temp_v1 == 0x10000 || temp_v1 == -0x10000) {
            entity->ext.generic.unk88.S16.unk0 =
                -entity->ext.generic.unk88.S16.unk0;
        }
        entity = g_CurrentEntity;
    }

    if (entity->velocityY < FIX(0.25)) {
        entity->velocityY += FIX(0.125);
    }
}

void func_801B5F4C(u16 arg0) {
    Collider res;

    if (g_CurrentEntity->velocityX < 0) {
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi - 7, &res, 0);
        if (res.effects & 5) {
            g_CurrentEntity->velocityY = 0;
        }
    }

    g_api.CheckCollision(
        g_CurrentEntity->posX.i.hi, g_CurrentEntity->posY.i.hi + 7, &res, 0);

    if (arg0) {
        if (!(res.effects & 5)) {
            MoveEntity();
            FallEntity();
            return;
        }

        g_CurrentEntity->velocityX = 0;
        g_CurrentEntity->velocityY = 0;

        if (res.effects & 4) {
            g_CurrentEntity->posY.val += FIX(0.125);
            return;
        }

        g_CurrentEntity->posY.i.hi += res.unk18;
        return;
    }

    if (!(res.effects & 5)) {
        MoveEntity();
        func_801B5EC8();
    }
}

// Can't be deduped with the other instances due to the extra memcpy
void CollectHeart(u16 index) {
    s8 hearts[10];

    __builtin_memcpy(&hearts[0], &c_HeartPrizes[0], 2);
    __builtin_memcpy(&hearts[8], &c_HeartPrizes[4], 2);
    g_api.PlaySfx(SFX_HEART_PICKUP);
    g_Status.hearts = hearts[index] + g_Status.hearts;
    if (g_Status.heartsMax < g_Status.hearts) {
        g_Status.hearts = g_Status.heartsMax;
    }
    DestroyEntity(g_CurrentEntity);
}

#include "../collect_gold.h"

void func_801B61D4(void) {}

void UnusedDestroyCurrentEntity(void) { DestroyEntity(g_CurrentEntity); }

void CollectSubweapon(u16 subWeaponIdx) {
    Entity* player = &PLAYER;
    u16 subWeapon;

    g_api.PlaySfx(SFX_ITEM_PICKUP);
    subWeapon = g_Status.subWeapon;
    g_Status.subWeapon = D_80181CAC[subWeaponIdx];

    if (subWeapon == g_Status.subWeapon) {
        subWeapon = 1;
        g_CurrentEntity->unk6D[0] = 0x10;
    } else {
        subWeapon = D_80181CDC[subWeapon];
        g_CurrentEntity->unk6D[0] = 0x60;
    }

    if (subWeapon != 0) {
        g_CurrentEntity->params = subWeapon;
        g_CurrentEntity->posY.i.hi = player->posY.i.hi + 12;
        g_CurrentEntity->step = 7;
        g_CurrentEntity->step_s = 0;
        g_CurrentEntity->velocityY = FIX(-2.5);
        g_CurrentEntity->animCurFrame = 0;
        g_CurrentEntity->ext.generic.unk88.S16.unk2 = 5;
        if (player->facingLeft != 1) {
            g_CurrentEntity->velocityX = FIX(-2);
            return;
        }
        g_CurrentEntity->velocityX = FIX(2);
        return;
    }
    DestroyEntity(g_CurrentEntity);
}

void DestroyCurrentEntity(void) { DestroyEntity(g_CurrentEntity); }

Entity* func_801B633C(void) {
    g_CurrentEntity->step = 3;
    g_CurrentEntity->params = 4;
    return g_CurrentEntity;
}

extern u16 g_InitializeData0[];
extern u8* D_80181D18[];
extern u16 D_80181D74[];

static u16 g_ItemIconSlots[ICON_SLOT_NUM];

// if self->params & 0x8000 then the item will not disappear
// self->ext.generic.unk80.modeS8.unk0: frames left before the prize disappear
void EntityPrizeDrop(Entity* self) {
    Collider collider;
    Primitive* prim;
    s16 primIndex;
    s16 var_a2;
    u16 itemId;
    s16 temp_a0;

    itemId = self->params & 0x7FFF;
    if (self->step != 0) {
        AnimateEntity(D_80181D18[itemId], self);
        if (self->step && self->step < 5 && self->hitFlags != 0) {
            self->step = 5;
        }
    }
    self->palette = 0x100;
    if ((u8)self->unk6D[0] >= 0x18 && !(g_GameTimer & 2) && self->params != 1) {
        self->palette = 0x815F;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeData0);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter.unk - 0x14;
        self->drawMode = DRAW_DEFAULT;
        if (itemId >= 0x17) {
            self->params = 0;
            itemId = 0;
        }
        if (itemId > 13 && itemId < 23 &&
            itemId == D_80181CDC[g_Status.subWeapon]) {
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
        }
        if (itemId == 0) {
            self->ext.generic.unk84.unk = -0x10000;
            self->ext.generic.unk88.S16.unk0 = 0x800;
        }
        break;

    case 2:
        if (self->velocityX < 0) {
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
            CheckFieldCollision(D_80181D74, 2);
            return;
        }
        if (collider.effects & EFFECT_NOTHROUGH) {
            self->posY.i.hi += collider.unk18;
            self->ext.generic.unk80.modeS8.unk0 = 0x60;
            self->step++;
        } else {
            func_801B5EC8();
        }
        break;

    case 3:
        func_801B5F4C(itemId);
        if (!(self->params & 0x8000) &&
            --self->ext.generic.unk80.modeS8.unk0 == 0) {
            self->ext.generic.unk80.modeS8.unk0 = itemId == 0 ? 0x40 : 0x50;
            self->step++;
        }
        break;

    case 4:
        func_801B5F4C(itemId);
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
        } else if (itemId < 14) {
            DestroyCurrentEntity();
        } else if (itemId < 23) {
            CollectSubweapon(itemId);
        } else {
            DestroyEntity(self);
            return;
        }
        break;

    case 7:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0;
            if (itemId > 13 && itemId < 23) {
                if (itemId == D_80181CDC[g_Status.subWeapon]) {
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
                prim->u0 = prim->u2 = 0;
                prim->v0 = prim->v1 = 0;
                prim->u1 = prim->u3 = 0x20;
                prim->v2 = prim->v3 = 0x20;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0x80;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;
                prim->drawMode = DRAW_HIDE;
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
            CheckFieldCollision(D_80181D74, 2);
            self->animCurFrame = 0;
            if (self->ext.generic.unk88.S16.unk2 != 0) {
                self->ext.generic.unk88.S16.unk2--;
            } else {
                prim = &g_PrimBuf[self->primIndex];
                prim->x0 = prim->x2 = self->posX.i.hi - 1;
                prim->x1 = prim->x3 = self->posX.i.hi + 1;
                prim->y0 = prim->y1 = self->posY.i.hi - 1;
                prim->y2 = prim->y3 = self->posY.i.hi + 1;
                prim->drawMode = 0x37;
            }
            break;

        case 2:
            func_801B5F4C(itemId);
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
// #endif

#include "../entity_explosion.h"

void func_801B6C5C(Entity* entity) {
    if (entity->step != 0) {
        if (entity->posY.i.hi >= 0xF1) {
            DestroyEntity(entity);
            return;
        }
        FallEntity();
        MoveEntity();
        return;
    }

    InitializeEntity(D_80180574);
    entity->animCurFrame = entity->ext.generic.unk7C.U8.unk0;
    entity->velocityX = D_80181E3C[entity->ext.generic.unk80.modeS8.unk0 * 2];
    entity->velocityY = D_80181E3E[entity->ext.generic.unk80.modeS8.unk0 * 2];

    if (entity->params != 0) {
        entity->zPriority -= 1;
    }
}

// Different from other overlays, but extremely similar to MAD.
void EntityEquipItemDrop(Entity* self) {
    Collider collider;
    Primitive* prim;
    s16 i;
    u16 itemId;
    s16 index;
    s32 primIndex;
    const char* name;
    s32 xPos;
    s32 yPos;

    itemId = self->params & 0x7FFF;
    if (self->step && self->step < 5 && self->hitFlags) {
        self->step = 5;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeData0);
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

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        g_ItemIconSlots[i] = 0x1E0;
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
        prim->u0 = prim->u2 = (u8)(i & 7) * 0x10 + 1;
        prim->u1 = prim->u3 = prim->u0 + 0xE;
        prim->v0 = prim->v1 = (u8)(i & 0x18) * 2 + 0x81;
        prim->v2 = prim->v3 = prim->v0 + 0xE;
        prim->priority = 0x80;
        prim->drawMode = DRAW_UNK02 | DRAW_COLORS;

        self->ext.equipItemDrop.timer = 128;
        self->step++;
        break;
    case 2:
        if (self->velocityX < 0) {
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
        CheckFieldCollision(D_80181D74, 2);
        break;
    case 3:
        func_801B5F4C(1);
        if (!(self->params & 0x8000)) {
            if (!(--self->ext.equipItemDrop.aliveTimer)) {
                self->ext.equipItemDrop.aliveTimer = 80;
                self->step++;
            }
        }
        break;
    case 4:
        func_801B5F4C(1);
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
        prim = &g_PrimBuf[self->primIndex];
        xPos = (u16)self->posX.i.hi;
        prim->x0 = prim->x2 = xPos - 7;
        prim->x1 = prim->x3 = xPos + 7;
        yPos = (u16)self->posY.i.hi;
        prim->y0 = prim->y1 = yPos - 7;
        prim->y2 = prim->y3 = yPos + 7;
        if (self->ext.equipItemDrop.timer) {
            self->ext.equipItemDrop.timer--;
            if (!(self->ext.equipItemDrop.timer & 2)) {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 =
                    prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                        prim->b2 = prim->b3 = 0x80;
            } else {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 =
                    prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                        prim->b2 = prim->b3 = 0xFF;
            }
        }
    }
}
