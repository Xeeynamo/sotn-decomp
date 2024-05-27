#include "../wrp/wrp.h"

#include "../../destroy_entity.h"

void PreventEntityFromRespawning(Entity* entity) {
    if (entity->entityRoomIndex) {
        u16 index = entity->entityRoomIndex - 1 >> 5;
        g_unkGraphicsStruct.D_80097428[index] |=
            1 << ((entity->entityRoomIndex - 1) & 0x1F);
    }
}

#include "../animate_entity.h"

u8 GetSideToPlayer() {
    u8 side = 0;
    Entity* player = &PLAYER;

    if (g_CurrentEntity->posX.i.hi > player->posX.i.hi) {
        side |= 1;
    }

    if (g_CurrentEntity->posY.i.hi > player->posY.i.hi) {
        side |= 2;
    }
    return side;
}

void MoveEntity() {
    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.val += g_CurrentEntity->velocityY;
}

void FallEntity(void) {
    if (g_CurrentEntity->velocityY < FALL_TERMINAL_VELOCITY) {
        g_CurrentEntity->velocityY += FALL_GRAVITY;
    }
}

Entity* AllocEntity(Entity* start, Entity* end) {
    Entity* current = start;

    while (current < end) {
        if (!current->entityId) {
            DestroyEntity(current);
            return current;
        }
        current++;
    }
    return NULL;
}

void UnkEntityFunc0(u16 slope, s16 speed) {
    g_CurrentEntity->velocityX = rcos(slope) * speed / 16;
    g_CurrentEntity->velocityY = rsin(slope) * speed / 16;
}

u16 func_8018C160(Entity* a, Entity* b) {
    s32 diffX = b->posX.i.hi - a->posX.i.hi;
    s32 diffY = b->posY.i.hi - a->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_8018C1E0(u16 arg0, u16 arg1, u16 arg2) {
    u16 temp_a2 = (s16)(arg2 - arg1);
    u16 var_v0;

    if (temp_a2 & 0x800) {
        var_v0 = (0x800 - temp_a2) & 0x7FF;
    } else {
        var_v0 = temp_a2;
    }

    if (var_v0 > arg0) {
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

void InitializeEntity(u16 arg0[]) {
    u16 enemyId;
    EnemyDef* enemyDef;

    g_CurrentEntity->animSet = *arg0++;
    g_CurrentEntity->animCurFrame = *arg0++;
    g_CurrentEntity->unk5A = *arg0++;
    g_CurrentEntity->palette = *arg0++;

    enemyId = g_CurrentEntity->enemyId = *arg0++;
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
    g_CurrentEntity->step++;
    g_CurrentEntity->step_s = 0;
    if (!g_CurrentEntity->zPriority) {
        g_CurrentEntity->zPriority =
            g_unkGraphicsStruct.g_zEntityCenter.unk - 0xC;
    }
}

void EntityDummy(Entity* arg0) {
    if (!arg0->step) {
        arg0->step++;
    }
}

void func_8018C55C(s16* hitSensors, s16 sensorCount) {
    Collider collider;
    s32 velocityX;
    s16 i;
    s16 x;
    s16 y;

    velocityX = g_CurrentEntity->velocityX;
    if (velocityX == 0) {
        return;
    }

    x = g_CurrentEntity->posX.i.hi;
    y = g_CurrentEntity->posY.i.hi;
    for (i = 0; i < sensorCount; i++) {
        if (velocityX < 0) {
            x += *hitSensors++;
        } else {
            x -= *hitSensors++;
        }

        y += *hitSensors++;
        g_api.CheckCollision(x, y, &collider, 0);
        if (collider.effects & EFFECT_UNK_0002 &&
            (!(collider.effects & EFFECT_UNK_8000) || i)) {
            if (velocityX < 0) {
                g_CurrentEntity->posX.i.hi += collider.unk1C;
            } else {
                g_CurrentEntity->posX.i.hi += collider.unk14;
            }
            break;
        }
    }
}

#include "../replace_breakable_with_item_drop.h"
