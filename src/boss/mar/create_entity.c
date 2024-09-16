// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

// TODO: import BSS and use create_entity.h
extern u16* g_LayoutObjHorizontal;
extern u16* g_LayoutObjVertical;
extern u8 g_LayoutObjPosHorizontal;
extern u8 g_LayoutObjPosVertical;

#include "../../st/st_private.h"
#include "../../st/create_entity_from_layout.h"
#include "../../st/create_entity_in_range.h"
#include "../../st/find_entity_horizontal.h"
#include "../../st/create_entities_horizontal.h"
#include "../../st/find_entity_vertical.h"
#include "../../st/create_entities_vertical.h"
#include "../../st/init_room_entities.h"
#include "../../st/update_room_position.h"
#include "../../st/create_entity_from_entity.h"
