// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../wrp/wrp.h"
#include "../pfn_entity_update.h"

static u16* g_LayoutObjHorizontal;
static u16* g_LayoutObjVertical;
static u8 g_LayoutObjPosHorizontal;
static u8 g_LayoutObjPosVertical;

#include "../st_private.h"

#include "../create_entity_from_layout.h"

#include "../create_entity_in_range.h"

#include "../find_entity_horizontal.h"

void CreateEntitiesToTheRight(s16);
INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/create_entity", CreateEntitiesToTheRight);

void CreateEntitiesToTheLeft(s16);
INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/create_entity", CreateEntitiesToTheLeft);

#include "../find_entity_vertical.h"

void CreateEntitiesAbove(s16);
INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/create_entity", CreateEntitiesAbove);

void CreateEntitiesBelow(s16);
INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/create_entity", CreateEntitiesBelow);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/create_entity", InitRoomEntities);

#include "../update_room_position.h"

extern PfnEntityUpdate* PfnEntityUpdates;

#include "../create_entity_from_entity.h"
