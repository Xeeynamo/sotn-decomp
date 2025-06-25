// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

u8 stage_title_cen_jp[] = {
#include "gen/stage_title_cen_jp.h"
};
u8 stage_placeholder_cen[] = {
#include "gen/stage_placeholder_cen.h"
};

#if defined(VERSION_HD)
// most likely the cutscene data is mis-extracted
u8 cutscene_cen_alucard[] = {
#include "gen/D_80181F60.h"
};

#else
u8 cutscene_cen_alucard[] = {
#include "gen/cutscene_alucard.h"
};
u8 cutscene_cen_maria[] = {
#include "gen/cutscene_maria.h"
};

#endif

u8 e_maria_cen_g0[] = {
#include "gen/e_maria_cen_g0.h"
};
u8 e_maria_cen_g1[] = {
#include "gen/e_maria_cen_g1.h"
};
u8 e_elevator_cen_g[] = {
#include "gen/e_elevator_cen_g.h"
};
u16 D_8018658C[] = {
#include "gen/D_8018658C.h"
};

u16 D_8018668C[] = {
#include "gen/D_8018668C.h"
};
u16 D_8018678C[] = {
#include "gen/D_8018678C.h"
};
u16 D_8018688C[] = {
#include "gen/D_8018688C.h"
};
u16 e_maria_cen_p[] = {
#include "gen/e_maria_cen_p.h"
};
u16 e_elevator_cen_p[] = {
#include "gen/e_elevator_cen_p.h"
};

#include "gen/cen_tilemap_0.h"
#include "gen/cen_tilemap_1.h"
#include "gen/cen_tilemap_2.h"
#include "gen/cen_tiledef_unused.h"
#include "gen/cen_tiledef_0.h"
