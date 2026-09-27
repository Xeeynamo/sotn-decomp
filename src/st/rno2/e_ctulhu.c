// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno2.h"

#ifndef VERSION_PSP // temporary, since psp doesn't have sprite banks yet
#define ctulhu_shockwave_uvs sprites_rno2_5
#endif

#define DISABLE_TRIPLE_FIREBALL
#define CTULHU_TPAGE 0x12
#include "../e_ctulhu.h"
