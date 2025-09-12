// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"
#include <cutscene.h>

extern Dialogue g_Dialogue;
extern const char* actor_names[];

#define CUTSCENE_UNK1_NEXT_X (DISP_STAGE_W + 2)
#include "../../st/cutscene_unk1.h"

#include "../../st/set_cutscene_script.h"

#define CUTSCENE_UNK3_RECT_X DISP_STAGE_W
#include "../../st/cutscene_unk3.h"

#define CUTSCENE_UNK4_TPAGE 0x14
#include "../../st/cutscene_unk4.h"

#include "../../st/cutscene_actor_name.h"

#include "../../st/set_cutscene_end.h"

#define CUTSCENE_TILEMAP_SCROLL
#include "../../st/cutscene_run.h"

#include "../../st/cutscene_skip.h"

#include "../../st/cutscene_scale_avatar.h"

INCLUDE_ASM("boss/bo6/nonmatchings/cutscene", func_us_801A7DC0);
