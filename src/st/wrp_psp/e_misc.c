// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../wrp/wrp.h"

extern u16 g_HeartDropArray[];

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_misc", EntityRelicOrb);

#define HEART_DROP_CASTLE_FLAG 280
#include "../entity_heart_drop.h"

u16 g_InitializeData0[];
void BlitChar(char*, s32, s32, s32);
#include "../entity_message_box.h"

#include "../entity_unkId13.h"

#include "../entity_unkId14.h"

#include "../entity_unkId15.h"

extern u16 g_InitializeEntityData0[];

#include "../entity_intense_explosion.h"

#include "../play_sfx_positional.h"
