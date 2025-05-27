// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

u8 stage_title_jp[] = {
#include "gen/stage_title_jp.h"
};
u8 stage_placeholder[] = {
#include "gen/stage_placeholder.h"
};
u8 e_skyswirl_g0[] = {
#include "gen/e_skyswirl_g0.h"
};
u8 e_skyswirl_g1[] = {
#include "gen/e_skyswirl_g1.h"
};
u8 e_merman_g0[] = {
#include "gen/e_merman_g0.h"
};
u8 e_merman_g1[] = {
#include "gen/e_merman_g1.h"
};
u8 e_merman_g2[] = {
#include "gen/e_merman_g2.h"
};
u8 e_merman_g3[] = {
#include "gen/e_merman_g3.h"
};
u8 e_slinger_g[] = {
#include "gen/e_slinger_g.h"
};
u8 e_ghost_bat_g[] = {
#include "gen/e_ghost_bat_g.h"
};
u8 e_zombie_g[] = {
#include "gen/e_zombie_g.h"
};
u8 e_bloody_zombie_g[] = {
#include "gen/e_bloody_zombie_g.h"
};
u8 e_owlknight_g0[] = {
#include "gen/e_owlknight_g0.h"
};
u8 e_owlknight_g1[] = {
#include "gen/e_owlknight_g1.h"
};
u8 e_owlknight_g2[] = {
#include "gen/e_owlknight_g2.h"
};
u8 e_explosion_g[] = {
#include "gen/e_explosion_g.h"
};
u8 e_slogra_g0[] = {
#include "gen/e_slogra_g0.h"
};
u8 e_slogra_g1[] = {
#include "gen/e_slogra_g1.h"
};
u8 e_slogra_g2[] = {
#include "gen/e_slogra_g2.h"
};
u8 e_gaibon_g0[] = {
#include "gen/e_gaibon_g0.h"
};
u8 e_gaibon_g1[] = {
#include "gen/e_gaibon_g1.h"
};
u8 e_gurkha_g[] = {
#include "gen/e_gurkha_g.h"
};
u16 e_skyswirl_p[] = {
#include "gen/e_skyswirl_p.h"
};
u16 e_merman_p[] = {
#include "gen/e_merman_p.h"
};
u16 D_80195B54[] = {
#include "gen/D_80195B54.h"
};
u16 D_80195B74[] = {
#include "gen/D_80195B74.h"
};
u16 D_80195BB4[] = {
#include "gen/D_80195BB4.h"
};
u16 D_80195BF4[] = {
#include "gen/D_80195BF4.h"
};
u16 D_80195C34[] = {
#include "gen/D_80195C34.h"
};
u16 D_80195C74[] = {
#include "gen/D_80195C74.h"
};
u16 D_80195CB4[] = {
#include "gen/D_80195CB4.h"
};
u16 D_80195CF4[] = {
#include "gen/D_80195CF4.h"
};
u16 D_80195D34[] = {
#include "gen/D_80195D34.h"
};
u16 D_80195D74[] = {
#include "gen/D_80195D74.h"
};
u16 D_80195DB4[] = {
#include "gen/D_80195DB4.h"
};
u16 D_80195DF4[] = {
#include "gen/D_80195DF4.h"
};
u16 D_80195E34[] = {
#include "gen/D_80195E34.h"
};
u16 D_80195E74[] = {
#include "gen/D_80195E74.h"
};
u16 D_80195EB4[] = {
#include "gen/D_80195EB4.h"
};
u16 D_80195EF4[] = {
#include "gen/D_80195EF4.h"
};
u16 e_slinger_p[] = {
#include "gen/e_slinger_p.h"
};
u16 e_ghost_bat_p[] = {
#include "gen/e_ghost_bat_p.h"
};
u16 e_zombie_p[] = {
#include "gen/e_zombie_p.h"
};
u16 e_bloody_zombie_p[] = {
#include "gen/e_bloody_zombie_p.h"
};
u16 e_owlknight_p[] = {
#include "gen/e_owlknight_p.h"
};
u16 e_explosion_p[] = {
#include "gen/e_explosion_p.h"
};
u16 D_801965B4[] = {
#include "gen/D_801965B4.h"
};
u16 e_slogra_p[] = {
#include "gen/e_slogra_p.h"
};
u16 e_gaibon_p[] = {
#include "gen/e_gaibon_p.h"
};
u16 e_gurkha_p[] = {
#include "gen/e_gurkha_p.h"
};

#include "gen/tilemap_168F4.h"
#include "gen/tilemap_174F4.h"
#include "gen/tilemap_176F4.h"
#include "gen/tilemap_17AF4.h"
#include "gen/tilemap_17EF4.h"
#include "gen/tilemap_18CF4.h"
#include "gen/tilemap_18EF4.h"
#include "gen/tilemap_190F4.h"
#include "gen/tilemap_192F4.h"
#include "gen/tilemap_196F4.h"
#include "gen/tilemap_19AF4.h"
#include "gen/tilemap_1A2F4.h"
#include "gen/tilemap_1AAF4.h"
#include "gen/tilemap_1ACF4.h"
#include "gen/tilemap_1AEF4.h"
#include "gen/tilemap_1BAF4.h"
#include "gen/tilemap_1C6F4.h"
#include "gen/tilemap_1C8F4.h"
#include "gen/tilemap_1CAF4.h"
#include "gen/tilemap_1D6F4.h"
#include "gen/tilemap_1D8F4.h"
#include "gen/tilemap_1DAF4.h"
#include "gen/tilemap_1DCF4.h"
#include "gen/tilemap_1E0F4.h"
#include "gen/tilemap_1E2F4.h"
#include "gen/tilemap_1E8F4.h"
#include "gen/tilemap_1EEF4.h"
#include "gen/tilemap_1F0F4.h"
#include "gen/tilemap_1F2F4.h"
#include "gen/tilemap_1F4F4.h"
#include "gen/tilemap_1F6F4.h"
#include "gen/tilemap_202F4.h"
#include "gen/tilemap_20EF4.h"
#include "gen/tilemap_210F4.h"
#include "gen/tilemap_212F4.h"
#include "gen/tilemap_214F4.h"
#include "gen/tilemap_216F4.h"
#include "gen/tilemap_218F4.h"
#include "gen/tilemap_21AF4.h"
#include "gen/tiledef_220F4.h"
#include "gen/tiledef_26104.h"
#include "gen/tiledef_2A114.h"
