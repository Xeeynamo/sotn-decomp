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

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/st_common", func_8018C1E0);

void SetStep(u8 step) {
    g_CurrentEntity->step = step;
    g_CurrentEntity->step_s = 0;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/st_common", InitializeEntity);

void EntityDummy(Entity* arg0) {
    if (!arg0->step) {
        arg0->step++;
    }
}

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/st_common", func_8018C55C);

#include "../replace_breakable_with_item_drop.h"
