// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"

#define HEART_DROP_CASTLE_FLAG 0xC0

#if !defined(VERSION_HD)

#include "../e_misc.h"

#else

INCLUDE_RODATA("st/cen/nonmatchings/e_misc", g_RelicOrbText);

INCLUDE_ASM("st/cen/nonmatchings/e_misc", EntityRelicOrb);

#include "../entity_heart_drop.h"

extern u16 msgBoxTpage[0x600];
#include "../entity_message_box.h"

#include "../check_coll_offsets.h"

#include "../entity_unkId13.h"

INCLUDE_ASM("st/cen/nonmatchings/e_misc", EntityUnkId14Spawner);

#include "../entity_unkId15_spawner.h"

INCLUDE_ASM("st/cen/nonmatchings/e_misc", EntityUnkId14);

INCLUDE_ASM("st/cen/nonmatchings/e_misc", EntityUnkId15);

INCLUDE_ASM("st/cen/nonmatchings/e_misc", EntityOlroxDrool);

#include "../unk_collision_func5.h"

#include "../unk_collision_func4.h"

#include "../entity_intense_explosion.h"

INCLUDE_ASM("st/cen/nonmatchings/e_misc", InitializeUnkEntity);

#include "../make_entity_from_id.h"

#include "../make_explosions.h"

#include "../entity_big_red_fireball.h"

INCLUDE_ASM("st/cen/nonmatchings/e_misc", UnkRecursivePrimFunc1);

INCLUDE_ASM("st/cen/nonmatchings/e_misc", UnkRecursivePrimFunc2);

#include "../clut_lerp.h"

#include "../play_sfx_positional.h"

#endif
