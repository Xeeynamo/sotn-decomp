#include "rwrp.h"
INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", TestCollisions);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018B6B4);

#include "../create_entity_from_layout.h"

void CreateEntityWhenInVerticalRange(LayoutEntity* layoutObj) {
    s16 yClose;
    s16 yFar;
    s16 posY;
    Entity* entity;

    posY = g_Tilemap.cameraY.i.hi;
    yClose = posY - 0x40;
    yFar = posY + 0x120;
    if (yClose < 0) {
        yClose = 0;
    }

    posY = layoutObj->posY;
    if (posY < yClose) {
        return;
    }

    if (yFar < posY) {
        return;
    }

    switch (layoutObj->entityId & 0xE000) {
    case 0x0:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->entityRoomIndex];
        if (entity->entityId == 0) {
            CreateEntityFromLayout(entity, layoutObj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->entityRoomIndex];
        CreateEntityFromLayout(entity, layoutObj);
        break;
    }
}

void CreateEntityWhenInHorizontalRange(LayoutEntity* layoutObj) {
    s16 xClose;
    s16 xFar;
    s16 posX;
    Entity* entity;

    posX = g_Tilemap.cameraX.i.hi;
    xClose = posX - 0x40;
    xFar = posX + 0x140;
    if (xClose < 0) {
        xClose = 0;
    }

    posX = layoutObj->posX;
    if (posX < xClose) {
        return;
    }

    if (xFar < posX) {
        return;
    }

    switch (layoutObj->entityId & 0xE000) {
    case 0x0:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->entityRoomIndex];
        if (entity->entityId == 0) {
            CreateEntityFromLayout(entity, layoutObj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->entityRoomIndex];
        CreateEntityFromLayout(entity, layoutObj);
        break;
    }
}

void func_8018C04C(s16 arg0) {
    while (true) {
        if (D_80195A30->posX != 0xFFFE && (s32)D_80195A30->posX >= arg0) {
            break;
        }
        D_80195A30++;
    }
}

void func_8018C098(s16 arg0) {
    while (true) {
        if ((D_80195A30->posX != 0xFFFF) &&
            ((arg0 >= D_80195A30->posX) || (D_80195A30->posX == 0xFFFE))) {
            break;
        }
        D_80195A30--;
    }
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018C0F0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018C1EC);

void func_8018C300(s16 arg0) {
    while (true) {
        if (D_80195A34->posY != 0xFFFE && (s32)D_80195A34->posY >= arg0) {
            break;
        }
        D_80195A34++;
    }
}

void func_8018C34C(s16 arg0) {
    while (true) {
        if ((D_80195A34->posY != 0xFFFF) &&
            ((arg0 >= D_80195A34->posY) || (D_80195A34->posY == 0xFFFE))) {
            break;
        }
        D_80195A34--;
    }
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018C3A4);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018C4A0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018C5B4);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018C72C);

void CreateEntityFromCurrentEntity(u16 entityId, Entity* entity) {
    DestroyEntity(entity);
    entity->entityId = entityId;
    entity->pfnUpdate = PfnEntityUpdates[entityId - 1];
    entity->posX.i.hi = g_CurrentEntity->posX.i.hi;
    entity->posY.i.hi = g_CurrentEntity->posY.i.hi;
}

void CreateEntityFromEntity(u16 entityId, Entity* source, Entity* entity) {
    DestroyEntity(entity);
    entity->entityId = entityId;
    entity->pfnUpdate = D_801803E0[entityId];
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018C8D0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018C948);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", DestroyEntity);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018D5EC);

void PreventEntityFromRespawning(Entity* entity) {
    if (entity->entityRoomIndex) {
        u32 value = (entity->entityRoomIndex - 1);
        u16 index = value / 32;
        u16 bit = value % 32;
        g_entityDestroyed[index] |= 1 << bit;
    }
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018D6B0);

u8 func_8018D768(u8 frames[], Entity* self, u8 arg2) {
    u16 animFrameStart = self->animFrameIdx * 2;
    u8* var_s1 = &frames[animFrameStart];
    s16 var_a1 = 0;

    if (self->animFrameDuration == 0) {
        if (*var_s1 != 0) {
            if (*var_s1 == 0xFF) {
                return 0;
            }
            self->animFrameDuration = *var_s1++ + (u8)self->ext.stub[0x3F];
            self->animCurFrame = *var_s1++;
            self->animFrameIdx++;
            var_a1 = 128;
        } else {
            var_s1 = frames;
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->ext.stub[0x3F] = (arg2 * Random()) >> 8;
            self->animFrameDuration = *var_s1++ + (u8)self->ext.stub[0x3F];
            self->animCurFrame = *var_s1;
            self->animFrameIdx++;
            return 0;
        }
    }
    self->animFrameDuration--;
    self->animCurFrame = var_s1[-1];
    var_a1 |= 1;
    return var_a1;
}

s32 GetDistanceToPlayerX(void) {
    s16 temp_v1 = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (temp_v1 >> 16) {
        temp_v1 = -temp_v1;
    }
    return temp_v1;
}

s32 GetDistanceToPlayerY(void) {
    s32 var_v0 = g_CurrentEntity->posY.i.hi - PLAYER.posY.i.hi;

    if (var_v0 < 0) {
        var_v0 = -var_v0;
    }
    return var_v0;
}

#include "../get_side_to_player.h"

void MoveEntity() {
    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.val += g_CurrentEntity->velocityY;
}

void FallEntity(void) {
    if (g_CurrentEntity->velocityY < FALL_TERMINAL_VELOCITY) {
        g_CurrentEntity->velocityY += FALL_GRAVITY;
    }
}
INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018D990);

s32 func_8018DC08(s16* posX) {
    Collider collider;
    s16 temp2;
    s16 temp4;
    s16 x, y;

    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    temp2 = g_CurrentEntity->posY.i.hi + 3;
    g_CurrentEntity->posY.i.hi = temp2;
    x = g_CurrentEntity->posX.i.hi + *posX;
    posX++;
    y = temp2 + *posX;
    g_api.CheckCollision(x, y, &collider, 0);
    if (!(collider.effects & EFFECT_SOLID)) {
        return 0;
    }
    posX++;

    g_CurrentEntity->posY.i.hi = g_CurrentEntity->posY.i.hi + collider.unk18;
    if (g_CurrentEntity->velocityX != 0) {
        if (g_CurrentEntity->velocityX < 0) {
            temp4 = x - *posX;
            posX++;
        } else {
            temp4 = x + *posX;
            posX++;
        }
        y = y + *posX - 7;
        g_api.CheckCollision(temp4, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if ((collider.effects & (EFFECT_UNK_8000 | EFFECT_UNK_0002)) ==
                EFFECT_UNK_0002) {
                g_CurrentEntity->posX.val =
                    g_CurrentEntity->posX.val - g_CurrentEntity->velocityX;
                g_CurrentEntity->velocityX = 0;
                return 0xFF;
            }
            return 0x61;
        }
        y += 15;
        g_api.CheckCollision(temp4, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if (collider.effects & EFFECT_UNK_8000) {
                return 0x61;
            }
            return 1;
        }
        g_CurrentEntity->posX.val -= g_CurrentEntity->velocityX;
        g_CurrentEntity->velocityX = 0;

        return 0x80;
    }
    return 1;
}

Entity* AllocEntity(Entity* start, Entity* end) {
    Entity* current = start;
    while (current < end) {
        if (current->entityId == E_NONE) {
            DestroyEntity(current);
            return current;
        }

        current++;
    }
    return NULL;
}

s32 func_8018DE50(u8 arg0, s16 arg1) { return D_80180A94[arg0] * arg1; }

s16 func_8018DE7C(u8 arg0) { return D_80180A94[arg0]; }

void func_8018DE98(u8 arg0, s16 arg1) {
    g_CurrentEntity->velocityX = func_8018DE50(arg0, arg1);
    g_CurrentEntity->velocityY = func_8018DE50((arg0 - 0x40), arg1);
}

u8 func_8018DF04(s16 arg0, s16 arg1) {
    return (ratan2(arg1, arg0) >> 4) + 0x40;
}

u8 func_8018DF3C(Entity* arg0, Entity* arg1) {
    s16 x = arg1->posX.i.hi - arg0->posX.i.hi;
    s16 y = arg1->posY.i.hi - arg0->posY.i.hi;

    return func_8018DF04(x, y);
}

s32 func_8018DF84(s32 arg0, s32 arg1) {
    s16 x = arg0 - g_CurrentEntity->posX.i.hi;
    s16 y = arg1 - g_CurrentEntity->posY.i.hi;

    return func_8018DF04(x, y);
}

#include "../adjust_value_within_threshold.h"

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", UnkEntityFunc0);

u16 func_8018E0B0(s16 arg0, s16 arg1) { return ratan2(arg1, arg0); }

u16 func_8018E0E0(Entity* arg0, Entity* arg1) {
    s32 x = arg1->posX.i.hi - arg0->posX.i.hi;
    s32 y = arg1->posY.i.hi - arg0->posY.i.hi;

    return ratan2(y, x);
}

u16 func_8018E118(s32 arg0, s32 arg1) {
    s16 x = arg0 - g_CurrentEntity->posX.i.hi;
    s16 y = arg1 - g_CurrentEntity->posY.i.hi;

    return ratan2(y, x);
}

u16 func_8018E160(u16 arg0, s16 arg1, s16 arg2) {
    u16 var_v0;
    u16 var_v0_2;
    u16 temp_a2 = arg2 - arg1;

    if (temp_a2 & 0x800) {
        var_v0_2 = (0x800 - temp_a2) & 0x7FF;
    } else {
        var_v0_2 = temp_a2;
    }
    if (var_v0_2 > arg0) {
        if (temp_a2 & 0x800) {
            var_v0 = arg1 - arg0;
        } else {
            var_v0 = arg1 + arg0;
        }
        return var_v0;
    }
    return arg2;
}

void SetStep(u8 step) {
    g_CurrentEntity->step = step;
    g_CurrentEntity->step_s = 0;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

void SetSubStep(u8 step_s) {
    g_CurrentEntity->step_s = step_s;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018E1FC);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", InitializeEntity);

void EntityDummy(Entity* entity) {
    if (entity->step == 0) {
        entity->step = (u16)(entity->step + 1);
    }
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018E3B4);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018E4DC);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018E634);

#include "../replace_breakable_with_item_drop.h"

void func_8018EA30(void) {
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

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018EAB4);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018EC10);

void CollectGold(u16 goldSize) {
    s32 *gold, *unk;
    u16 goldSizeIndex;

    g_api.PlaySfx(NA_SE_PL_COLLECT_GOLD);
    gold = &g_Status.gold;
    goldSizeIndex = goldSize - 2;
    *gold += c_GoldPrizes[goldSizeIndex];
    if (*gold > MAX_GOLD) {
        *gold = MAX_GOLD;
    }

    unk = &g_BottomCornerTextTimer;
    if (*unk) {
        g_api.FreePrimitives(g_BottomCornerTextPrims);
        *unk = 0;
    }

    BottomCornerText(D_80180E08[goldSizeIndex], 1);
    DestroyEntity(g_CurrentEntity);
}

void CollectSubweapon(u16 subWeaponIdx) {
    Entity* player = &PLAYER;
    u16 subWeapon;

    g_api.PlaySfx(NA_SE_PL_IT_PICKUP);
    subWeapon = g_Status.subWeapon;
    g_Status.subWeapon = D_80180DC4[subWeaponIdx];

    if (subWeapon == g_Status.subWeapon) {
        subWeapon = 1;
        g_CurrentEntity->unk6D[0] = 0x10;
    } else {
        subWeapon = D_80180DF4[subWeapon];
        g_CurrentEntity->unk6D[0] = 0x60;
    }

    if (subWeapon != 0) {
        g_CurrentEntity->params = subWeapon;
        g_CurrentEntity->posY.i.hi = player->posY.i.hi + 12;
        SetStep(7);
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

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018EE84);

void CollectLifeVessel(void) {
    g_api_PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_api_func_800FE044(5, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

void DestroyCurrentEntity(void) { DestroyEntity(g_CurrentEntity); }

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", EntityPrizeDrop);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018F814);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", BlinkItem);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", EntityEquipItemDrop);

#include "../blit_char.h"
