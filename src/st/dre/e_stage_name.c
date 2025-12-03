// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dre.h"

#define STAGE_FLAG OVL_EXPORT(STAGE_FLAG)

#ifdef VERSION_US
#include "../e_stage_name_us.h"
#endif

#ifdef VERSION_PSP
static u8 stage_name_en[] = {
#include GEN_VERSION(gfx_stage_name_en.h)
};
static u8 stage_name_it[] = {
#include GEN_VERSION(gfx_stage_name_it.h)
};
static u8 stage_name_sp[] = {
#include GEN_VERSION(gfx_stage_name_sp.h)
};
static u8 stage_name_ge[] = {
#include GEN_VERSION(gfx_stage_name_ge.h)
};
static u8 stage_name_fr[] = {
#include GEN_VERSION(gfx_stage_name_fr.h)
};

#define STAGE_NAME_LOAD_GFX
#include "../e_stage_name_jp.h"
#endif
