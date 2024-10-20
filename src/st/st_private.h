// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef ST_PRIVATE_H
#define ST_PRIVATE_H

#include <stage.h>

#define LAYOUT_OBJ_START 0xfffe
#define LAYOUT_OBJ_END 0xffff

#define LAYOUT_OBJ_POSITION_FORWARD 0
#define LAYOUT_OBJ_POSITION_BACKWARD 1

// Follows the struct from LayoutEntity
#define LAYOUT_OBJ_POS_X 0
#define LAYOUT_OBJ_POS_Y 1
#define LAYOUT_OBJ_ID 2
#define LAYOUT_OBJ_SLOT 3
#define LAYOUT_OBJ_PARAMS 4

#endif // ST_PRIVATE_H
