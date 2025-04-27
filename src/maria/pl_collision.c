// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

INCLUDE_ASM("maria_psp/nonmatchings/pl_collision", func_pspeu_092B3848);

INCLUDE_ASM("maria_psp/nonmatchings/pl_collision", MarGetPlayerSensor);

INCLUDE_ASM("maria_psp/nonmatchings/pl_collision", MarCheckFloor);

INCLUDE_ASM("maria_psp/nonmatchings/pl_collision", MarCheckCeiling);

INCLUDE_ASM("maria_psp/nonmatchings/pl_collision", func_pspeu_092B5340);

INCLUDE_ASM("maria_psp/nonmatchings/pl_collision", MarCheckWallRight);
