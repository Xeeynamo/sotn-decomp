// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <sfx.h>
#include <servant.h>

extern s32 g_IsServantDestroyed;

#include "../set_entity_animation.h"

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80170F84);

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
#include "../play_sfx.h"
#endif

#include "../process_event.h"

#include "../create_event_entity.h"

#include "../is_movement_allowed.h"

#ifndef VERSION_PSP
#include "../check_all_entities_valid.h"
#endif

#include "../servant_unk0.h"
