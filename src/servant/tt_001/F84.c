// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <servant.h>

extern s32 IsServantDestroyed;

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

s32 func_us_80172B50(s32 arg0, s32 arg1) {
    if (arg0 < 0) {
        arg0 += arg1;
        if (arg0 > 0) {
            arg0 = 0;
        }
    } else {
        arg0 -= arg1;
        if (arg0 < 0) {
            arg0 = 0;
        }
    }

    return arg0;
}

Entity* func_us_80172B88(s32 rangeIndex, s32 entityId) {
    volatile u32 pad; // fake?
    s16 start = D_80170EE4[rangeIndex].start;
    s16 end = D_80170EE4[rangeIndex].end;
    Entity* entity = &g_Entities[start];
    s32 i;

    for (i = start; end >= i; i++, entity++) {
        if (entity->entityId == entityId) {
            return entity;
        }
    }

    return NULL;
}

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172C08);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172C4C);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172CC0);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172D10);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172EE8);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_801732BC);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80173378);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80173490);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_8017353C);

INCLUDE_RODATA("servant/tt_001/nonmatchings/F84", func_us_80170F60);
