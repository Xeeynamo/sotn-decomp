// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <servant.h>

extern s32 g_IsServantDestroyed;

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80170F84);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171284);

#include "../check_entity_valid.h"

void func_us_80171560(void) {}

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171568);

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

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172C08);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172C4C);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172CC0);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172D10);

#include "../process_event.h"

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", CreateEventEntity);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80173378);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80173490);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_8017353C);

INCLUDE_RODATA("servant/tt_001/nonmatchings/F84", func_us_80170F60);
