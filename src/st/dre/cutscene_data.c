// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dre.h"
#include <cutscene.h>

#ifdef VERSION_PSP
u8 cutscene_script_pre_fight_it[] = {
#include "gen/cutscene_script_pre_fight_it.h"
#include "gen/cutscene_data_pre_fight_it.h"
};

u8 cutscene_script_pre_fight_sp[] = {
#include "gen/cutscene_script_pre_fight_sp.h"
#include "gen/cutscene_data_pre_fight_sp.h"
};

u8 cutscene_script_pre_fight_fr[] = {
#include "gen/cutscene_script_pre_fight_fr.h"
#include "gen/cutscene_data_pre_fight_fr.h"
};

u8 cutscene_script_pre_fight_ge[] = {
#include "gen/cutscene_script_pre_fight_ge.h"
#include "gen/cutscene_data_pre_fight_ge.h"
};

u8 cutscene_script_pre_fight_en[] = {
#include "gen/cutscene_script_pre_fight_en.h"
#include "gen/cutscene_data_pre_fight_en.h"
};

u8 cutscene_script_post_fight_it[] = {
#include "gen/cutscene_script_post_fight_it.h"
#include "gen/cutscene_data_post_fight_it.h"
};

u8 cutscene_script_post_fight_sp[] = {
#include "gen/cutscene_script_post_fight_sp.h"
#include "gen/cutscene_data_post_fight_sp.h"
};

u8 cutscene_script_post_fight_fr[] = {
#include "gen/cutscene_script_post_fight_fr.h"
#include "gen/cutscene_data_post_fight_fr.h"
};

u8 cutscene_script_post_fight_ge[] = {
#include "gen/cutscene_script_post_fight_ge.h"
#include "gen/cutscene_data_post_fight_ge.h"
};

u8 cutscene_script_post_fight_en[] = {
#include "gen/cutscene_script_post_fight_en.h"
#include "gen/cutscene_data_post_fight_en.h"
};
#else
// These are defined in st_init_psp as bss for pspeu, but us seems to have them
// located here
u8 D_801816C0 = 0;
u8 D_801816C4[4] = {0};

u8 OVL_EXPORT(cutscene_script)[] = {
#include "gen/cutscene_script_psx.h"
};
#endif
