// SPDX-License-Identifier: AGPL-3.0-or-later
#include "faerie.h"

// There is some .rodata jumptable stuff going on with ProcessSfxState
// where the table is in the middle of the .rodata function
INCLUDE_ASM("servant/tt_002/nonmatchings/8A30", func_us_80178A30);
// #include "../play_sfx.h"

#include "../process_event.h"

#include "../create_event_entity.h"

#include "../is_movement_allowed.h"

#ifndef VERSION_PSP
#include "../check_all_entities_valid.h"
#endif

#include "../servant_unk0.h"
