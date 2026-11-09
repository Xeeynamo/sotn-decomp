// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

#define STAGE_FLAG NO0_STAGE_FLAG

#if IS_VER_INTL
#include "../e_stage_name_us.h"
#endif

#if TARGET == TARGET_PSP
static u8 stage_name_en[] = {
#include <gen/stage_name_en.h>
};
static u8 stage_name_it[] = {
#include <gen/stage_name_it.h>
};
static u8 stage_name_sp[] = {
#include <gen/stage_name_sp.h>
};
static u8 stage_name_ge[] = {
#include <gen/stage_name_ge.h>
};
static u8 stage_name_fr[] = {
#include <gen/stage_name_fr.h>
};

#define STAGE_NAME_LOAD_GFX
#include "../e_stage_name_jp.h"
#endif

#if !IS_VER_INTL && TARGET != TARGET_PSP
#include "../e_stage_name_jp.h"
#endif
