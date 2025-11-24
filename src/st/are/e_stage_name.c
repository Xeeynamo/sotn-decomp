// SPDX-License-Identifier: AGPL-3.0-or-later
#include "are.h"

#define STAGE_FLAG OVL_EXPORT(STAGE_FLAG)

#ifdef VERSION_US
#include "../e_stage_name_us.h"
#endif

#ifdef VERSION_PSP
static u8 stage_name_en[] = {
#include "gen/stage_name_en.h"
};
static u8 stage_name_it[] = {
#include "gen/stage_name_it.h"
};
static u8 stage_name_sp[] = {
#include "gen/stage_name_sp.h"
};
// nb. For some reason this is ordered differently to other overlays
static u8 stage_name_fr[] = {
#include "gen/stage_name_fr.h"
};
static u8 stage_name_ge[] = {
#include "gen/stage_name_ge.h"
};

#define STAGE_NAME_LOAD_GFX
#include "../e_stage_name_jp.h"
#endif
