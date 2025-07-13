// SPDX-License-Identifier: AGPL-3.0-or-later
#include "top.h"
#include "../pfn_entity_update.h"
#include <cutscene.h>

extern Dialogue g_Dialogue;

#include "../cutscene_unk1.h"
#include "../set_cutscene_script.h"
#include "../cutscene_unk3.h"
#include "../cutscene_unk4.h"
#include "../cutscene_actor_name.h"
#include "../set_cutscene_end.h"
#include "../cutscene_run.h"
#include "../cutscene_skip.h"
#include "../cutscene_scale_avatar.h"

INCLUDE_RODATA("st/top/nonmatchings/cutscene", D_us_801A898C);

INCLUDE_RODATA("st/top/nonmatchings/cutscene", D_us_801A8998);

INCLUDE_RODATA("st/top/nonmatchings/cutscene", D_us_801A89A0);

INCLUDE_ASM("st/top/nonmatchings/cutscene", TOP_EntityCutscene);
