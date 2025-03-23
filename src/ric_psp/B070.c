// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../ric/ric.h"
#include <player.h>

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/B070", RicCheckInput);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/B070", RicGetPlayerSensor);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/B070", RicCheckFloor);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/B070", RicCheckCeiling);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/B070", RicCheckWallRight);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/B070", RicCheckWallLeft);
