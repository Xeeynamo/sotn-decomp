// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"

#if !defined(VERSION_HD)

#include "../create_entity.h"

#else

#include "../create_entity_from_layout.h"
#include "../create_entity_in_range.h"

INCLUDE_ASM("st/cen/nonmatchings/create_entity", FindFirstEntityToTheRight);

INCLUDE_ASM("st/cen/nonmatchings/create_entity", FindFirstEntityToTheLeft);

INCLUDE_ASM("st/cen/nonmatchings/create_entity", CreateEntitiesToTheLeft);

INCLUDE_ASM("st/cen/nonmatchings/create_entity", CreateEntitiesToTheRight);

INCLUDE_ASM("st/cen/nonmatchings/create_entity", FindFirstEntityAbove);

INCLUDE_ASM("st/cen/nonmatchings/create_entity", FindFirstEntityBelow);

INCLUDE_ASM("st/cen/nonmatchings/create_entity", CreateEntitiesAbove);

INCLUDE_ASM("st/cen/nonmatchings/create_entity", CreateEntitiesBelow);

INCLUDE_ASM("st/cen/nonmatchings/create_entity", InitRoomEntities);

INCLUDE_ASM("st/cen/nonmatchings/create_entity", UpdateRoomPosition);

#include "../create_entity_from_entity.h"

#endif
