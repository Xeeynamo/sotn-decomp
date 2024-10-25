// SPDX-License-Identifier: AGPL-3.0-or-later
#include "faerie.h"

INCLUDE_ASM("servant/tt_002/nonmatchings/7AC4", func_us_80177AC4);

INCLUDE_ASM("servant/tt_002/nonmatchings/7AC4", func_us_80177F64);

INCLUDE_ASM("servant/tt_002/nonmatchings/7AC4", func_us_80177F84);

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
