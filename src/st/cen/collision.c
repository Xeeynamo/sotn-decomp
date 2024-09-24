// SPDX-License-Identifier: AGPL-3.0-or-later

#include "cen.h"

#if !defined(VERSION_HD)

#include "../collision.h"

#else

INCLUDE_ASM("st/cen/nonmatchings/collision", HitDetection);

#include "../entity_damage_display.h"

#endif
