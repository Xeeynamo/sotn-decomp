// SPDX-License-Identifier: AGPL-3.0-only
//
// Section Sizes:
//
//         | Data  | RO Data | Text  | BSS  |
// --------+-------+---------+-------+------+
//  PSX US | TBD   | TBD     | 0xB78 | 0x10 |
//  PSX HD | TBD   | TBD     | 0xB78 | 0x10 |
//

#include <common.h>

static u16* g_LayoutObjHorizontal;
static u16* g_LayoutObjVertical;
static u8 g_LayoutObjPosHorizontal;
STATIC_PAD_BSS(3);
static u8 g_LayoutObjPosVertical;
STATIC_PAD_BSS(3);

#include "st_private.h"
#include "create_entity_from_layout.h"
#include "create_entity_in_range.h"
#include "find_entity_horizontal.h"
#include "create_entities_horizontal.h"
#include "find_entity_vertical.h"
#include "create_entities_vertical.h"
#include "init_room_entities.h"
#include "update_room_position.h"
#include "create_entity_from_entity.h"
