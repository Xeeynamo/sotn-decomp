// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

INCLUDE_ASM("maria_psp/nonmatchings/pl_main", DestroyEntity);

INCLUDE_ASM("maria_psp/nonmatchings/pl_main", GetTeleportToOtherCastle);

INCLUDE_ASM("maria_psp/nonmatchings/pl_main", func_80156DE4);

INCLUDE_ASM("maria_psp/nonmatchings/pl_main", MarInit);

INCLUDE_ASM("maria_psp/nonmatchings/pl_main", CheckStageCollision);

INCLUDE_ASM("maria_psp/nonmatchings/pl_main", CheckBladeDashInput);

INCLUDE_ASM("maria_psp/nonmatchings/pl_main", CheckHighJumpInput);

INCLUDE_ASM("maria_psp/nonmatchings/pl_main", MarMain);
