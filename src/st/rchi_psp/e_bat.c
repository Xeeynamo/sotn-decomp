// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rchi/rchi.h"

/* PSP RCHI uses the exact RCAT bat variant, including collision avoidance and
 * randomized proximity fields. PSX RCHI remains stage-specific assembly. */
#define STAGE_IS_RCAT
#include "../e_bat.h"
