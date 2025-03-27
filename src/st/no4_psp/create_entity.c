// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

INCLUDE_ASM("st/no4_psp/psp/no4_psp/create_entity", CreateEntityFromLayout);

// clang-format off
INCLUDE_ASM("st/no4_psp/psp/no4_psp/create_entity", CreateEntityWhenInVerticalRange);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/create_entity", CreateEntityWhenInHorizontalRange);
// clang-format on

INCLUDE_ASM("st/no4_psp/psp/no4_psp/create_entity", FindFirstEntityToTheRight);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/create_entity", FindFirstEntityToTheLeft);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/create_entity", CreateEntitiesToTheRight);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/create_entity", CreateEntitiesToTheLeft);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/create_entity", FindFirstEntityAbove);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/create_entity", FindFirstEntityBelow);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/create_entity", CreateEntitiesAbove);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/create_entity", CreateEntitiesBelow);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/create_entity", InitRoomEntities);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/create_entity", UpdateRoomPosition);

// clang-format off
INCLUDE_ASM("st/no4_psp/psp/no4_psp/create_entity", CreateEntityFromCurrentEntity);
// clang-format on

INCLUDE_ASM("st/no4_psp/psp/no4_psp/create_entity", CreateEntityFromEntity);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/create_entity", func_pspeu_092449B0);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/create_entity", func_pspeu_092457E8);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/create_entity", func_psp_0923C0C0);

INCLUDE_ASM("st/no4_psp/psp/no4_psp/create_entity", EntityStageNamePopup);
