#include "wrp.h"

extern s8 c_HeartPrizes[];
extern s32 c_GoldPrizes[];
extern u8* D_80180E08[];
extern u16 D_80180DC4[];
extern u16 D_80180DF4[];
extern u16 g_ItemIconSlots[];
extern u16 UNK_Invincibility0[];
extern PfnEntityUpdate PfnEntityUpdates[];
extern LayoutEntity* g_LayoutObjHorizontal;
extern LayoutEntity* g_LayoutObjVertical;
extern u8 g_LayoutObjPosHorizontal;
extern s16 D_80180A94[];
extern LayoutEntity* D_80180310[];
extern u8 g_LayoutObjPosVertical;
extern LayoutEntity* g_pStObjLayoutHorizontal[];
extern LayoutEntity* g_pStObjLayoutVertical[];

INCLUDE_ASM("st/wrp/nonmatchings/861C", TestCollisions);

#include "../entity_damage_display.h"

#include "../create_entity_from_layout.h"

void CreateEntityWhenInVerticalRange(LayoutEntity* layoutObj) {
    s16 yClose;
    s16 yFar;
    s16 posY;
    Entity* entity;

    posY = g_Tilemap.scrollY.i.hi;
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
        if (entity->entityId == E_NONE) {
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

    posX = g_Tilemap.scrollX.i.hi;
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
        if (entity->entityId == E_NONE) {
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

void FindFirstEntityToTheRight(s16 arg0) {
    while (true) {
        if (g_LayoutObjHorizontal->posX != 0xFFFE &&
            g_LayoutObjHorizontal->posX >= arg0) {
            break;
        }
        g_LayoutObjHorizontal++;
    }
}

void FindFirstEntityToTheLeft(s16 arg0) {
    while (true) {
        if (g_LayoutObjHorizontal->posX != 0xFFFF &&
            (arg0 >= g_LayoutObjHorizontal->posX ||
             g_LayoutObjHorizontal->posX == 0xFFFE)) {
            break;
        }
        g_LayoutObjHorizontal--;
    }
}

void CreateEntitiesToTheRight(s16 x) {
    u8 flag;
    s32 expected;

    if (g_LayoutObjPosHorizontal != 0) {
        FindFirstEntityToTheRight(x - g_ScrollDeltaX);
        g_LayoutObjPosHorizontal = 0;
    }

    while (true) {
        if (g_LayoutObjHorizontal->posX == 0xFFFF ||
            g_LayoutObjHorizontal->posX > x) {
            return;
        }

        expected = 0;
        flag = (g_LayoutObjHorizontal->entityRoomIndex >> 8) + 0xFF;
        if (flag == 0xFF ||
            (g_entityDestroyed[flag >> 5] & (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInVerticalRange(g_LayoutObjHorizontal);
        }
        g_LayoutObjHorizontal++;
    }
}

void CreateEntitiesToTheLeft(s16 x) {
    u8 flag;
    s32 expected;

    if (x < 0) {
        x = 0;
    }
    if (g_LayoutObjPosHorizontal == 0) {
        FindFirstEntityToTheLeft(x - g_ScrollDeltaX);
        g_LayoutObjPosHorizontal = 1;
    }

    while (true) {
        if (g_LayoutObjHorizontal->posX == 0xFFFE ||
            x > g_LayoutObjHorizontal->posX) {
            return;
        }

        expected = 0;
        flag = (g_LayoutObjHorizontal->entityRoomIndex >> 8) + 0xFF;
        if (flag == 0xFF ||
            (g_entityDestroyed[flag >> 5] & (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInVerticalRange(g_LayoutObjHorizontal);
        }
        g_LayoutObjHorizontal--;
    }
}

void FindFirstEntityAbove(s16 arg0) {
    u16 a1 = -2;
    s32 tmp = arg0;
    arg0 = (s16)arg0;
loop_1:
    if (g_LayoutObjVertical->posY == (s32)a1 ||
        g_LayoutObjVertical->posY < tmp) {
        g_LayoutObjVertical++;
        goto loop_1;
    }
}

void FindFirstEntityBelow(s16 arg0) {
    while (true) {
        if (g_LayoutObjVertical->posY == 0xFFFF) {
            g_LayoutObjVertical--;
        } else if ((s32)arg0 >= (s32)g_LayoutObjVertical->posY ||
                   g_LayoutObjVertical->posY == 0xFFFE) {
            break;
        } else {
            g_LayoutObjVertical--;
        }
    }
}

void CreateEntitiesAbove(s16 arg0) {
    u8 flag;
    s32 expected;

    if (g_LayoutObjPosVertical) {
        FindFirstEntityAbove(arg0 - g_ScrollDeltaY);
        g_LayoutObjPosVertical = 0;
    }

    while (true) {
        if (g_LayoutObjVertical->posY == 0xFFFF ||
            g_LayoutObjVertical->posY > arg0) {
            break;
        }

        expected = 0;
        flag = (g_LayoutObjVertical->entityRoomIndex >> 8) + 0xFF;
        if (flag == 0xFF ||
            (g_entityDestroyed[flag >> 5] & (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInHorizontalRange(g_LayoutObjVertical);
        }
        g_LayoutObjVertical++;
    }
}

void CreateEntitiesBelow(s16 arg0) {
    u8 flag;
    s32 expected;

    if (arg0 < 0) {
        arg0 = 0;
    }

    if (g_LayoutObjPosVertical == 0) {
        FindFirstEntityBelow(arg0 - g_ScrollDeltaY);
        g_LayoutObjPosVertical = 1;
    }

    while (true) {
        if (g_LayoutObjVertical->posY == 0xFFFE ||
            arg0 > g_LayoutObjVertical->posY) {
            return;
        }

        expected = 0;
        flag = (g_LayoutObjVertical->entityRoomIndex >> 8) + 0xFF;
        if (flag == 0xFF ||
            (g_entityDestroyed[flag >> 5] & (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInHorizontalRange(g_LayoutObjVertical);
        }
        g_LayoutObjVertical--;
    }
}

void InitRoomEntities(s32 objLayoutId) {
    u16* pObjLayoutStart = g_pStObjLayoutHorizontal[objLayoutId];
    Tilemap* tilemap = &g_Tilemap;
    s16 temp_s0;
    s16 arg0;
    s16 i;
    u16* temp_v1;

    g_LayoutObjHorizontal = pObjLayoutStart;
    g_LayoutObjVertical = g_pStObjLayoutVertical[objLayoutId];

    if (*pObjLayoutStart != 0xFFFE) {
        g_LayoutObjHorizontal = pObjLayoutStart + 1;
        arg0 = Random() & 0xFF;
        for (i = 0; true; i++) {
            temp_v1 = g_LayoutObjHorizontal;
            g_LayoutObjHorizontal = temp_v1 + 1;
            arg0 -= temp_v1[0];
            if (arg0 < 0) {
                break;
            }
            g_LayoutObjHorizontal = temp_v1 + 3;
        }
        g_LayoutObjHorizontal = (temp_v1[2] << 0x10) + temp_v1[1];
        ((u16*)g_LayoutObjVertical) += i * 2 + 2;
        g_LayoutObjVertical =
            (g_LayoutObjVertical->posY << 0x10) + g_LayoutObjVertical->posX;
    }
    arg0 = tilemap->scrollX.i.hi;
    temp_s0 = arg0 + 0x140;
    i = arg0 - 0x40;
    if (i < 0) {
        i = 0;
    }

    g_LayoutObjPosHorizontal = 0;
    g_LayoutObjPosVertical = 0;
    FindFirstEntityToTheRight(i);
    CreateEntitiesToTheRight(temp_s0);
    FindFirstEntityAbove(tilemap->scrollY.i.hi + 0x120);
}

void UpdateRoomPosition(void) {
    Tilemap* tilemap = &g_Tilemap;

    if (g_ScrollDeltaX != 0) {
        s16 tmp = tilemap->scrollX.i.hi;
        if (g_ScrollDeltaX > 0)
            CreateEntitiesToTheRight(tmp + 0x140);
        else
            CreateEntitiesToTheLeft(tmp - 0x40);
    }

    if (g_ScrollDeltaY != 0) {
        s16 tmp = tilemap->scrollY.i.hi;
        if (g_ScrollDeltaY > 0)
            CreateEntitiesAbove(tilemap->scrollY.i.hi + 0x120);
        else
            CreateEntitiesBelow(tmp - 0x40);
    }
}

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
    entity->pfnUpdate = PfnEntityUpdates[entityId - 1];
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
}

#include "../entity_is_near_player.h"

INCLUDE_ASM("st/wrp/nonmatchings/861C", EntityRedDoor);

#include "../../destroy_entity.h"

#include "../../destroy_entities_from_index.h"

void PreventEntityFromRespawning(Entity* entity) {
    if (entity->entityRoomIndex) {
        u32 value = (entity->entityRoomIndex - 1);
        u16 index = value / 32;
        u16 bit = value % 32;
        g_entityDestroyed[index] |= 1 << bit;
    }
}

#include "../animate_entity.h"

u8 func_8018B7E8(u8 frames[], Entity* self, u8 arg2) {
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

// Absolute distance from g_CurrentEntity to the player in the X Axis
s16 GetDistanceToPlayerX(void) {
    s16 xDistance = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (xDistance < 0) {
        xDistance = -xDistance;
    }
    return xDistance;
}

// Absolute distance from g_CurrentEntity to the player in the Y Axis
s32 GetDistanceToPlayerY(void) {
    s32 yDistance = g_CurrentEntity->posY.i.hi - PLAYER.posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

#include "../get_side_to_player.h"

void MoveEntity(void) {
    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.val += g_CurrentEntity->velocityY;
}

void FallEntity(void) {
    if (g_CurrentEntity->velocityY < FALL_TERMINAL_VELOCITY) {
        g_CurrentEntity->velocityY += FALL_GRAVITY;
    }
}

s32 func_8018BA10(u16* sensors) {
    Collider col;
    Collider colBack;
    s16 x;
    s16 y;
    s16 i;

    MoveEntity();
    FallEntity();
    if (g_CurrentEntity->velocityY >= 0) {
        x = g_CurrentEntity->posX.i.hi;
        y = g_CurrentEntity->posY.i.hi;
        for (i = 0; i < 4; i++) {
            x += *sensors++;
            y += *sensors++;
            g_api.CheckCollision(x, y, &col, 0);
            if (col.effects & EFFECT_UNK_8000) {
                if (i == 1) {
                    if (col.effects & EFFECT_SOLID) {
                        g_api.CheckCollision(x, y - 8, &colBack, 0);
                        if (!(colBack.effects & EFFECT_SOLID)) {
                            g_CurrentEntity->posY.i.hi =
                                (u16)g_CurrentEntity->posY.i.hi + 4 + col.unk18;
                            g_CurrentEntity->velocityX = 0;
                            g_CurrentEntity->velocityY = 0;
                            g_CurrentEntity->flags &= ~FLAG_UNK_10000000;
                            return 1;
                        }
                    }
                    continue;
                }
            }
            if (col.effects & EFFECT_NOTHROUGH && i != 1) {
                if (col.effects & EFFECT_QUICKSAND) {
                    g_CurrentEntity->flags &= ~FLAG_UNK_10000000;
                    return 4;
                }
                g_api.CheckCollision(x, y - 8, &colBack, 0);
                if (!(colBack.effects & EFFECT_SOLID)) {
                    g_CurrentEntity->posY.i.hi =
                        g_CurrentEntity->posY.i.hi + col.unk18;
                    g_CurrentEntity->velocityX = 0;
                    g_CurrentEntity->velocityY = 0;
                    g_CurrentEntity->flags &= ~FLAG_UNK_10000000;
                    return 1;
                }
            }
        }
    }
    g_CurrentEntity->flags |= FLAG_UNK_10000000;
    return 0;
}

s32 func_8018BC88(s16* posX) {
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

s32 func_8018BED0(u8 arg0, s16 arg1) { return D_80180A94[arg0] * arg1; }

s16 func_8018BEFC(u8 arg0) { return D_80180A94[arg0]; }

void func_8018BF18(s32 arg0, s16 arg1) {
    g_CurrentEntity->velocityX = func_8018BED0(arg0, arg1);
    g_CurrentEntity->velocityY = func_8018BED0(arg0 - 0x40, arg1);
}

u8 func_8018BF84(s16 x, s16 y) { return ((ratan2(y, x) >> 4) + 0x40); }

u8 func_8018BFBC(Entity* a, Entity* b) {
    s32 diffX = (u16)b->posX.i.hi - (u16)a->posX.i.hi;
    s32 diffY = (u16)b->posY.i.hi - (u16)a->posY.i.hi;
    return func_8018BF84(diffX, diffY);
}

u8 func_8018C004(s32 x, s32 y) {
    s32 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s32 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return func_8018BF84(diffX, diffY);
}

#include "../adjust_value_within_threshold.h"

#include "../unk_entity_func0.h"

u16 func_8018C130(s16 x, s16 y) { return ratan2(y, x); }

u16 func_8018C160(Entity* a, Entity* b) {
    s32 diffX = b->posX.i.hi - a->posX.i.hi;
    s32 diffY = b->posY.i.hi - a->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_8018C198(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s16 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_8018C1E0(u16 arg0, s16 arg1, s16 arg2) {
    u16 var_v0 = arg1;
    u16 temp_a2 = arg2 - arg1;
    u16 var_v0_2;

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

void func_8018C260(u8 step_s) {
    g_CurrentEntity->step_s = step_s;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

void EntityExplosionSpawn(u16 arg0, u16 arg1) {
    Entity* entity;

    if (arg1 != 0) {
        func_801916C4(arg1);
    }
    if (arg0 == 0xFF) {
        DestroyEntity(g_CurrentEntity);
        return;
    }

    entity = g_CurrentEntity;
    entity->drawFlags = 0;
    entity->entityId = E_EXPLOSION;
    entity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
    entity->params = arg0;
    entity->animCurFrame = 0;
    g_CurrentEntity->step = 0;
    g_CurrentEntity->step_s = 0;
}

void InitializeEntity(u16 arg0[]) {
    u16 enemyId;
    EnemyDef* enemyDef;

    g_CurrentEntity->animSet = *arg0++;
    g_CurrentEntity->animCurFrame = *arg0++;
    g_CurrentEntity->unk5A = *arg0++;
    g_CurrentEntity->palette = *arg0++;

    enemyId = *arg0++;
    g_CurrentEntity->enemyId = enemyId;
    enemyDef = &g_api.enemyDefs[enemyId];
    g_CurrentEntity->hitPoints = enemyDef->hitPoints;
    g_CurrentEntity->attack = enemyDef->attack;
    g_CurrentEntity->attackElement = enemyDef->attackElement;
    g_CurrentEntity->hitboxState = enemyDef->hitboxState;
    g_CurrentEntity->hitboxWidth = enemyDef->hitboxWidth;
    g_CurrentEntity->hitboxHeight = enemyDef->hitboxHeight;
    g_CurrentEntity->flags = enemyDef->flags;
    g_CurrentEntity->hitboxOffX = 0;
    g_CurrentEntity->hitboxOffY = 0;
    g_CurrentEntity->step_s = 0;
    g_CurrentEntity->step++;
    if (g_CurrentEntity->zPriority == 0) {
        g_CurrentEntity->zPriority =
            g_unkGraphicsStruct.g_zEntityCenter.S16.unk0 - 0xC;
    }
}

void EntityDummy(Entity* arg0) {
    if (arg0->step == 0) {
        arg0->step++;
    }
}

s32 func_8018C434(u16* hitSensors, s16 sensorCount) {
    Collider collider;
    s16 i;
    s32 velocityX;
    u16 temp_a1;
    s16 x;
    s16 y;

    velocityX = g_CurrentEntity->velocityX;
    if (velocityX != 0) {
        x = g_CurrentEntity->posX.i.hi;
        y = g_CurrentEntity->posY.i.hi;
        for (i = 0; i < sensorCount; i++) {
            if (velocityX < 0) {
                s16 newX = x + *hitSensors++;
                x = newX;
            } else {
                s16 newX = x - *hitSensors++;
                x = newX;
            }

            y += *hitSensors++;
            g_api.CheckCollision(x, y, &collider, 0);
            if (collider.effects & EFFECT_UNK_0002 &&
                ((!(collider.effects & EFFECT_UNK_8000)) || (i != 0))) {
                return 2;
            }
        }
        return 0;
    }
}

void func_8018C55C(u16* hitSensors, s16 sensorCount) {
    Collider collider;
    s16 i;
    s32 velocityX;
    s16 x;
    s16 y;

    velocityX = g_CurrentEntity->velocityX;
    if (velocityX == 0)
        return;
    x = g_CurrentEntity->posX.i.hi;
    y = g_CurrentEntity->posY.i.hi;
    for (i = 0; i < sensorCount; i++) {
        if (velocityX < 0) {
            x = x + *hitSensors++;
        } else {
            x = x - *hitSensors++;
        }

        y += *hitSensors++;
        g_api.CheckCollision(x, y, &collider, 0);
        if (collider.effects & EFFECT_UNK_0002 &&
            (!(collider.effects & EFFECT_UNK_8000) || i != 0)) {
            if (velocityX < 0) {
                g_CurrentEntity->posX.i.hi += collider.unk1C;
            } else {
                g_CurrentEntity->posX.i.hi += collider.unk14;
            }
            return;
        }
    }
}

INCLUDE_ASM("st/wrp/nonmatchings/861C", func_8018C6B4);

#include "../replace_breakable_with_item_drop.h"

void func_8018CAB0(void) {
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

void func_8018CB34(u16 arg0) {
    Collider collider;

    if (g_CurrentEntity->velocityX < 0) {
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi - 7, &collider, 0);
        if (collider.effects & EFFECT_NOTHROUGH) {
            g_CurrentEntity->velocityY = 0;
        }
    }

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                         g_CurrentEntity->posY.i.hi + 7, &collider, 0);

    if (arg0) {
        if (!(collider.effects & EFFECT_NOTHROUGH)) {
            MoveEntity();
            FallEntity();
            return;
        }

        g_CurrentEntity->velocityX = 0;
        g_CurrentEntity->velocityY = 0;

        if (collider.effects & EFFECT_QUICKSAND) {
            g_CurrentEntity->posY.val += FIX(0.125);
            return;
        }

        g_CurrentEntity->posY.i.hi += collider.unk18;
        return;
    }

    if (!(collider.effects & EFFECT_NOTHROUGH)) {
        MoveEntity();
        func_8018CAB0();
    }
}

#include "../collect_heart.h"

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

#include "../collect_heart_vessel.h"

void CollectLifeVessel(void) {
    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_api.func_800FE044(LIFE_VESSEL_INCREASE, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

void DestroyCurrentEntity(void) { DestroyEntity(g_CurrentEntity); }
