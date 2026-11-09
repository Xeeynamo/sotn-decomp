// SPDX-License-Identifier: AGPL-3.0-or-later
#include "np3.h"

#define STAGE_FLAG NP3_STAGE_FLAG

#if VERSION == VER_US
#include "../e_stage_name_us.h"
#endif

#if VERSION < VER_JP10 || TARGET == TARGET_PSP
#include "../e_stage_name_jp.h"
#endif
