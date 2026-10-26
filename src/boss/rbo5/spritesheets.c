// SPDX-License-Identifier: AGPL-3.0-or-later
#include <common.h>

#ifdef VERSION_PSP
// the PSP spritesheets live outside of the overlay
extern u8* D_8D31FA0[];
extern u8* D_8D589B8[];
u8** doppleganger_sprites = D_8D31FA0;
u8** bat_form_sprites = D_8D589B8;
#else
#include "gen/doppleganger.h"
#include "gen/bat_form.h"
#endif

#ifdef VERSION_US
static u16 __pad = 0;
#endif
