// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <servant.h>



INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80170F84);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171284);

s32 func_us_801714F4(Entity* entity) {
    if (entity->hitboxState == 0)
        return 0;
    if (entity->posX.i.hi < -16)
        return 0;
    if (entity->posX.i.hi > 272)
        return 0;
    if (entity->posY.i.hi > 240)
        return 0;
    if (entity->posY.i.hi < 0)
        return 0;
    if (entity->hitPoints >= 0x7000)
        return 0;
    if (entity->hitPoints <= 0)
        return 0;

    return 1;
}

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

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172904);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_8017293C);

#include "../../destroy_entity.h"

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172B50);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172B88);

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
