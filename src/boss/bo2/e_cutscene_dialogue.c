// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo2.h"
#include <cutscene.h>

extern Dialogue g_Dialogue;
extern const char* actor_names[];

#include "../../st/cutscene_unk1.h"

#include "../../st/set_cutscene_script.h"

#include "../../st/cutscene_unk3.h"

#include "../../st/cutscene_unk4.h"

#include "../../st/cutscene_actor_name.h"

#include "../../st/set_cutscene_events.h"

#include "../../st/cutscene_events.h"

#include "../../st/cutscene_skip.h"

#include "../../st/cutscene_scale_avatar.h"

INCLUDE_RODATA("boss/bo2/nonmatchings/e_cutscene_dialogue", D_us_801A1F6C);

INCLUDE_RODATA("boss/bo2/nonmatchings/e_cutscene_dialogue", D_us_801A1F78);

INCLUDE_ASM("boss/bo2/nonmatchings/e_cutscene_dialogue", EntityCutsceneDialogue);
