// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <servant.h>

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_801739D0);

// This is a duplicate CreateEventEntity which is lower in the file, but we need both
// to match the binary for PSX
void CreateEventEntity_Dupe(Entity* entityParent, s32 entityId, s32 params) {
    Entity* entity;
    s32 i;

    for (i = 0; i < 3; i++) {
        entity = &g_Entities[5 + i];
        if (!entity->entityId) {
            break;
        }
    }

    if (!entity->entityId) {
        DestroyEntity(entity);
        entity->entityId = entityId;
        entity->zPriority = entityParent->zPriority;
        entity->facingLeft = entityParent->facingLeft;
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->posX.val = entityParent->posX.val;
        entity->posY.val = entityParent->posY.val;
        // Not necessarily making batFamBlueTrail here, but
        // that's an Ext that works. Just needs parent at 0x8C.
        entity->ext.batFamBlueTrail.parent = entityParent;
        entity->params = params;
    }
}

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80173BD0);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80173D60);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_801746E8);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80174998);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80174F0C);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_801753E4);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80175730);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80175A78);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80175DBC);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80176178);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80176504);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80176B6C);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80176C98);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80177380);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80177958);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80177AC4);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80177F64);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80177F84);

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

// There is some .rodata jumptable stuff going on with ProcessSfxState
// where the table is in the middle of the .rodata function
INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80178A30);
//#include "../play_sfx.h"
#endif

#include "../process_event.h"

#include "../create_event_entity.h"

#include "../is_movement_allowed.h"

#ifndef VERSION_PSP
#include "../check_all_entities_valid.h"
#endif

#include "../servant_unk0.h"

INCLUDE_RODATA("servant/tt_002/nonmatchings/3678", func_us_80173994);

INCLUDE_RODATA("servant/tt_002/nonmatchings/3678", func_us_801739C8);
