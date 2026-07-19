// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../top/top.h"
#include <cutscene.h>

extern Dialogue g_Dialogue;

#include "../../get_lang.h"

#include "../cutscene_actor_name.h"

#include "../cutscene_unk3.h"

#include "../cutscene_unk4.h"

#define CUTSCENE_UNK1_NEXT_X 0
#define CUTSCENE_UNK1_UNK17 2
#include "../cutscene_unk1.h"

#include "../set_cutscene_script.h"

#include "../set_cutscene_end.h"

#define CUTSCENE_TILEMAP_SCROLL
#include "../cutscene_run.h"

#include "../cutscene_skip.h"

INCLUDE_ASM("st/top_psp/nonmatchings/top_psp/cutscene", EntityCutscene);
