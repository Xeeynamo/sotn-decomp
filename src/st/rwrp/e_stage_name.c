// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rwrp.h"

#define STAGE_NAME RWRP_STAGE_NAME

#if VERSION == VER_US
#include "../e_stage_name_us.h"
#endif

#if VERSION < VER_JP10 || TARGET == TARGET_PSP
#include "../e_stage_name_jp.h"
#endif
