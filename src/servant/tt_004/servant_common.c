// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sword.h"
#include <sfx.h>

#include "../servant_update_anim.h"
#include "../../destroy_entity.h"
#include "../accumulate_toward_zero.h"
#include "../search_for_entity_in_range.h"
#include "../calculate_angle_to_entity.h"
#include "../get_target_position_with_distance_buffer.h"
#include "../calculate_distance.h"
#include "../play_sfx.h"
#include "../process_event.h"
#include "../create_event_entity.h"
#include "../is_movement_allowed.h"
#include "../check_all_entities_valid.h"
#include "../servant_unk0.h"
