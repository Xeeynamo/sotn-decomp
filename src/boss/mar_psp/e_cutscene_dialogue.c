// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../mar/mar.h"
#include <cutscene.h>

extern Dialogue g_Dialogue;

#include "../../get_lang.h"

#include "../../st/cutscene_actor_name.h"

#include "../../st/cutscene_unk3.h"

#include "../../st/cutscene_unk4.h"

#define CUTSCENE_UNK1_NEXT_X 0
#define CUTSCENE_UNK1_UNK17 2
#include "../../st/cutscene_unk1.h"

#include "../../st/set_cutscene_script.h"

INCLUDE_ASM("boss/mar_psp/nonmatchings/mar_psp/e_cutscene_dialogue", SetCutsceneEvents);

INCLUDE_ASM("boss/mar_psp/nonmatchings/mar_psp/e_cutscene_dialogue", RunCutsceneEvents);

INCLUDE_ASM("boss/mar_psp/nonmatchings/mar_psp/e_cutscene_dialogue", EntityCutsceneDialogue);
