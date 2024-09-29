// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <servant.h>

extern s32 g_IsServantDestroyed;

#include "../set_entity_animation.h"

s32 UpdateEntityVelocityTowardsTarget(s32 unused, s32 targetX, s32 targetY) {
    // AngleToTarget
    D_us_801735B8 = CalculateAngleToEntity(g_CurrentEntity, targetX, targetY);
    // BufferedTargetPosition
    D_us_801735BC = GetTargetPositionWithDistanceBuffer(
        D_us_801735B8, g_CurrentEntity->ext.factory.unk82,
        g_CurrentEntity->ext.factory.unk84);
    g_CurrentEntity->ext.factory.unk82 = D_us_801735BC;
    // DeltaX
    D_us_801735B0 = targetX - g_CurrentEntity->posX.i.hi;
    // DeltaY
    D_us_801735B4 = targetY - g_CurrentEntity->posY.i.hi;
    // DistanceToTarget
    D_us_801735C0 =
        SquareRoot12(
            ((D_us_801735B0 * D_us_801735B0) + (D_us_801735B4 * D_us_801735B4))
            << 0xC) >>
        0xC;

    switch (g_CurrentEntity->step) {
    case 2:
        g_CurrentEntity->velocityX = rcos(D_us_801735BC) * D_us_801735C0 * 2;
        g_CurrentEntity->velocityY = -(rsin(D_us_801735BC) * D_us_801735C0 * 2);
        break;
    case 3:
        g_CurrentEntity->velocityX = rcos(D_us_801735BC) * D_us_801735C0 * 8;
        g_CurrentEntity->velocityY = -(rsin(D_us_801735BC) * D_us_801735C0 * 8);
        break;
    default:
        g_CurrentEntity->velocityX = (rcos(D_us_801735BC) * D_us_801735C0) >> 2;
        g_CurrentEntity->velocityY =
            -((rsin(D_us_801735BC) * D_us_801735C0) >> 2);
        break;
    }

    // Clamp velocity so it cannot go too low/high
    if (g_CurrentEntity->velocityX > 0 &&
        g_CurrentEntity->velocityX < FIX(0.25)) {
        g_CurrentEntity->velocityX = FIX(0.25);
    } else if (g_CurrentEntity->velocityX < 0 &&
               g_CurrentEntity->velocityX > FIX(-0.25)) {
        g_CurrentEntity->velocityX = FIX(-0.25);
    }

    if (g_CurrentEntity->velocityY > 0 &&
        g_CurrentEntity->velocityY < FIX(0.25)) {
        g_CurrentEntity->velocityY = FIX(0.25);
    } else if (g_CurrentEntity->velocityY < 0 &&
               g_CurrentEntity->velocityY > FIX(-0.25)) {
        g_CurrentEntity->velocityY = FIX(-0.25);
    }

    if (D_us_801735C0 > 0x100) {
        g_CurrentEntity->velocityX =
            (targetX - g_CurrentEntity->posX.i.hi) << 0xE;
        g_CurrentEntity->velocityY =
            (targetY - g_CurrentEntity->posY.i.hi) << 0xE;
    }

    // Return the distance between entity and target
    return D_us_801735C0;
}

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171284);

#include "../check_entity_valid.h"

void func_us_80171560(void) {}

#if defined(VERSION_PSP)
void func_psp_092EA460(Entity* self, s32 entityId, s32 params) {
#else
Entity* func_us_80171568(Entity* self, s32 entityId) {
#endif
    Entity* entity;
    s32 i;

    for (i = 0; i < 3; i++) {
        entity = &g_Entities[i + 5];
        if (!entity->entityId) {
            break;
        }
    }

    if (!entity->entityId) {
        DestroyEntity(entity);
#if defined(VERSION_PSP)
        entity->entityId = entityId;
#else
        if (entityId == 0) {
            entity->entityId = 0xDA;
        } else {
            entity->entityId = 0xDB;
        }
#endif
        entity->zPriority = self->zPriority;
        entity->facingLeft = self->facingLeft;
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->posX.val = self->posX.val;
        entity->posY.val = self->posY.val;
        entity->ext.factory.parent = self;
#if defined(VERSION_PSP)
        entity->params = params;
#else
        return entity;
#endif
    }
    // BUG? There is a fall-through case here with no return value on PSX
}

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171624);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171864);

void func_us_801720A4(void) {}

void func_us_801720AC(void) {}

void func_us_801720B4(void) {}

void func_us_801720BC(void) {}

void func_us_801720C4(void) {}

void func_us_801720CC(void) {}

void func_us_801720D4(void) {}

void func_us_801720DC(void) {}

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_801720E4);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_8017246C);

void func_us_801728EC(void) {}

void func_us_801728F4(void) {}

void func_us_801728FC(void) {}

#include "../destroy_servant_entity.h"

#ifndef VERSION_PSP
#include "../servant_update_anim.h"
#endif

#include "../../destroy_entity.h"

#ifndef VERSION_PSP
#include "../accumulate_toward_zero.h"
#include "../search_for_entity_in_range.h"
#endif

#include "../calculate_angle_to_entity.h"

#include "../get_target_position_with_distance_buffer.h"

#ifndef VERSION_PSP
#include "../calculate_distance.h"
#endif

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172D10);

#include "../process_event.h"

#include "../create_event_entity.h"

#include "../is_movement_allowed.h"

#ifndef VERSION_PSP
#include "../check_all_entities_valid.h"
#endif

#include "../servant_unk0.h"
