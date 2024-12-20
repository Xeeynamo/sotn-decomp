// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../st0/st0.h"
#include "../pfn_entity_update.h"

extern u16* g_LayoutObjHorizontal;
extern u16* g_LayoutObjVertical;
extern u8 g_LayoutObjPosHorizontal;
extern u8 g_LayoutObjPosVertical;

#include "../st_private.h"
#include "../create_entity_from_layout.h"
#include "../create_entity_in_range.h"
#include "../find_entity_horizontal.h"
NOP;

void CreateEntitiesToTheRight(s16);
INCLUDE_ASM("st/st0_psp/psp/st0_psp/create_entity", CreateEntitiesToTheRight);

void CreateEntitiesToTheLeft(s16);
INCLUDE_ASM("st/st0_psp/psp/st0_psp/create_entity", CreateEntitiesToTheLeft);

#include "../find_entity_vertical.h"

void CreateEntitiesAbove(s16);
INCLUDE_ASM("st/st0_psp/psp/st0_psp/create_entity", CreateEntitiesAbove);

void CreateEntitiesBelow(s16);
INCLUDE_ASM("st/st0_psp/psp/st0_psp/create_entity", CreateEntitiesBelow);

INCLUDE_ASM("st/st0_psp/psp/st0_psp/create_entity", InitRoomEntities);

#include "../update_room_position.h"
#include "../create_entity_from_entity.h"
