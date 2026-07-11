// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno0.h"

INCLUDE_ASM("st/rno0/nonmatchings/create_entity", RNO0_CreateEntityFromLayout);

INCLUDE_ASM("st/rno0/nonmatchings/create_entity", RNO0_CreateEntityWhenInVerticalRange);

INCLUDE_ASM("st/rno0/nonmatchings/create_entity", RNO0_CreateEntityWhenInHorizontalRange);

INCLUDE_ASM("st/rno0/nonmatchings/create_entity", FindFirstEntityToTheRight);

INCLUDE_ASM("st/rno0/nonmatchings/create_entity", FindFirstEntityToTheLeft);

INCLUDE_ASM("st/rno0/nonmatchings/create_entity", CreateEntitiesToTheRight);

INCLUDE_ASM("st/rno0/nonmatchings/create_entity", CreateEntitiesToTheLeft);

INCLUDE_ASM("st/rno0/nonmatchings/create_entity", FindFirstEntityAbove);

INCLUDE_ASM("st/rno0/nonmatchings/create_entity", FindFirstEntityBelow);

INCLUDE_ASM("st/rno0/nonmatchings/create_entity", CreateEntitiesAbove);

INCLUDE_ASM("st/rno0/nonmatchings/create_entity", CreateEntitiesBelow);

INCLUDE_ASM("st/rno0/nonmatchings/create_entity", InitRoomEntities);

INCLUDE_ASM("st/rno0/nonmatchings/create_entity", RNO0_UpdateRoomPosition);

INCLUDE_ASM("st/rno0/nonmatchings/create_entity", RNO0_CreateEntityFromCurrentEntity);

INCLUDE_ASM("st/rno0/nonmatchings/create_entity", RNO0_CreateEntityFromEntity);
