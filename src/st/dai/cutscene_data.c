// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"
#include <cutscene.h>

#ifdef VERSION_PSP
u8 OVL_EXPORT(cutscene_script_it)[] = {
#include "gen/cutscene_script_it.h"
#include "gen/cutscene_data_it.h"
};

u8 OVL_EXPORT(cutscene_script_sp)[] = {
#include "gen/cutscene_script_sp.h"
#include "gen/cutscene_data_sp.h"
};

u8 OVL_EXPORT(cutscene_script_fr)[] = {
#include "gen/cutscene_script_fr.h"
#include "gen/cutscene_data_fr.h"
};

u8 OVL_EXPORT(cutscene_script_ge)[] = {
#include "gen/cutscene_script_ge.h"
#include "gen/cutscene_data_ge.h"
};

u8 OVL_EXPORT(cutscene_script_en)[] = {
#include "gen/cutscene_script_en.h"
#include "gen/cutscene_data_en.h"
};
#else
u8 OVL_EXPORT(cutscene_script)[] = {
#include "gen/cutscene_script_psx.h"
};
#endif
