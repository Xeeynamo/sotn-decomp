// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rdai.h"

#if defined(VERSION_PSP)
#include "../check_collider_offsets.h"

extern EInit g_EInitParticle;
extern EInit g_EInitUnkId13;

void EntityExplosion(Entity*);
#include "../e_unk_id13.h"

#include "../e_explosion_variants.h"

#include "../e_grey_puff.h"

#include "../e_intense_explosion.h"

#include "../play_sfx_positional.h"
#else
#include "../e_misc.h"
#endif
