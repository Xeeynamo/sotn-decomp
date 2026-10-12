// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo4.h"

#ifdef VERSION_PSP
INCLUDE_ASM("boss/rbo4/nonmatchings/e_room_bg", EntityBackgroundBlock);
#else
#include "../../st/e_room_bg.h"
#endif
