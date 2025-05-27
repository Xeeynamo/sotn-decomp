#include "common.h"

u8 stage_title_jp[] = {
#include "gen/stage_title_jp.h"
};
u8 stage_placeholder[] = {
#include "gen/stage_placeholder.h"
};

#if defined(VERSION_HD)
// most likely the cutscene data is mis-extracted
u8 cutscene_alucard[] = {
#include "gen/D_80181F60.h"
};

#else
u8 cutscene_alucard[] = {
#include "gen/cutscene_alucard.h"
};
u8 cutscene_maria[] = {
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

#ifdef VERSION_HD
#include "gen/tilemap_06A0C.h"
#include "gen/tilemap_06E0C.h"
#include "gen/tilemap_0800C.h"
#include "gen/tiledef_0860C.h"
#include "gen/tiledef_0C61C.h"
#else
#include "gen/tilemap_069EC.h"
#include "gen/tilemap_06DEC.h"
#include "gen/tilemap_07FEC.h"
#include "gen/tiledef_085EC.h"
#include "gen/tiledef_0C5FC.h"
#endif
