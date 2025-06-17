// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dai/dai.h"

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", DestroyEntity);
// clang-format off
INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", PreventEntityFromRespawning);
// clang-format on
INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", AnimateEntity);

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", GetDistanceToPlayerX);

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", GetDistanceToPlayerY);

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", GetSideToPlayer);

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", MoveEntity);

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", FallEntity);

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", UnkCollisionFunc3);

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", UnkCollisionFunc2);

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", AllocEntity);

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", GetSineScaled);
// clang-format off
INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", SetEntityVelocityFromAngle);
// clang-format on
INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", Ratan2Shifted);
// clang-format off
INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", GetAngleBetweenEntitiesShifted);

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", AdjustValueWithinThreshold);
// clang-format on
INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", UnkEntityFunc0);
// clang-format off
INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", GetAngleBetweenEntities);
// clang-format on
INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", GetNormalizedAngle);

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", SetStep);

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", SetSubStep);

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", InitializeEntity);

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", EntityDummy);

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", UnkCollisionFunc);

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", CheckFieldCollision);
// clang-format off
INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", GetPlayerCollisionWith);

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/st_common", ReplaceBreakableWithItemDrop);
