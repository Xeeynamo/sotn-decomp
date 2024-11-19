// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "servant.h"
#include "sfx.h"

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80172DC4);

void DestroyEntityPassthrough(Entity* self)
{
    DestroyEntity(self);
}

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80172EF8);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80173348);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_801737F0);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80173D14);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_801744CC);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_8017472C);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80174FD0);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_8017540C);

void func_us_80175800(void) {}

void func_us_80175808(void) {}

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80175810);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80175C08);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80175D20);

void UpdateServantSfxPassthrough(Entity* self) { ProcessSfxState(self); }

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80176564);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_801765A0);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80176814);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80176C1C);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_801771B0);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80177690);

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

INCLUDE_RODATA("servant/tt_003/nonmatchings/demon", SetAnimationFrame);

// maybe a match for FindValidTarget, but only 90%.  It looks to be significantly simpler
INCLUDE_RODATA("servant/tt_003/nonmatchings/demon", FindValidTarget);

INCLUDE_RODATA("servant/tt_003/nonmatchings/demon", CheckEntityValid);

INCLUDE_RODATA("servant/tt_003/nonmatchings/demon", func_us_80172DBC);
