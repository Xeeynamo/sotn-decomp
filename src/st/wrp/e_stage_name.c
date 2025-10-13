// SPDX-License-Identifier: AGPL-3.0-or-later
#include "wrp.h"

#define STAGE_NAME OVL_EXPORT(STAGE_NAME)

#ifdef VERSION_US
#include "../e_stage_name.h"
#endif

#if defined(VERSION_PSP) || defined(VERSION_HD)
#include "../e_stage_name_psp.h"
#endif
