// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stage_loader.h"
#include "../st/nz0/nz0.h"

u8 e_axe_knight_g0[3824];
u8 e_axe_knight_g1[3056];
u8 e_blood_skeleton_g[2960];
u8 e_bloody_zombie_g[3256];
u8 e_cloche_g[2900];
u8 e_explosion_g[3964];
u8 e_gaibon_g0[3440];
u8 e_gaibon_g1[1984];
u8 e_maria_nz0_g0[4884];
u8 e_maria_nz0_g1[3448];
u8 e_sealed_door_g[4288];
u8 e_skelerang_g0[3160];
u8 e_skelerang_g1[3320];
u8 e_skeleton_g[2912];
u8 e_slinger_g[3036];
u8 e_slogra_g0[2804];
u8 e_slogra_g1[2536];
u8 e_slogra_g2[2244];
u8 e_table_blue_flame_g[3076];
u8 e_table_with_alembic_g[1508];
u8 e_table_with_globe_g[1480];
u8 stage_title_nz0_jp[1160];
u8 stage_title_nz0_us[1432];
u8 D_80195CBC[32];
u8 D_80195CFC[64];
u8 D_8019621C[192];
u8 D_8019661C[32];
u8 D_8019665C[256];
u8 D_8019675C[256];
u8 D_8019685C[256];
u8 D_8019695C[256];
u8 e_axe_knight_p[128];
u8 e_blood_skeleton_p[128];
u8 e_bloody_zombie_p[96];
u8 e_cloche_p[320];
u8 e_explosion_p[512];
u8 e_gaibon_p[256];
u8 e_maria_nz0_p[32];
u8 e_sealed_door_p[160];
u8 e_skelerang_p[96];
u8 e_skeleton_p[32];
u8 e_slinger_p[32];
u8 e_slogra_p[96];
u8 e_table_blue_flame_p[128];
u8 e_table_with_alembic_p[128];
u8 e_table_with_globe_p[128];

extern AbbreviatedOverlay OVL_EXPORT(Overlay);
extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutHorizontal)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutVertical)[];
extern PfnEntityUpdate* PfnEntityUpdates;
extern LayoutEntity** g_pStObjLayoutHorizontal;
extern LayoutEntity** g_pStObjLayoutVertical;
void InitStageNZ0(Overlay* o) {
    LoadReset();
    LOAD_ASSET_GFX("assets/st/nz0", e_axe_knight_g0);
    LOAD_ASSET_GFX("assets/st/nz0", e_axe_knight_g1);
    LOAD_ASSET_GFX("assets/st/nz0", e_blood_skeleton_g);
    LOAD_ASSET_GFX("assets/st/nz0", e_bloody_zombie_g);
    LOAD_ASSET_GFX("assets/st/nz0", e_cloche_g);
    LOAD_ASSET_GFX("assets/st/nz0", e_explosion_g);
    LOAD_ASSET_GFX("assets/st/nz0", e_gaibon_g0);
    LOAD_ASSET_GFX("assets/st/nz0", e_gaibon_g1);
    LOAD_ASSET_GFX("assets/st/nz0", e_maria_nz0_g0);
    LOAD_ASSET_GFX("assets/st/nz0", e_maria_nz0_g1);
    LOAD_ASSET_GFX("assets/st/nz0", e_sealed_door_g);
    LOAD_ASSET_GFX("assets/st/nz0", e_skelerang_g0);
    LOAD_ASSET_GFX("assets/st/nz0", e_skelerang_g1);
    LOAD_ASSET_GFX("assets/st/nz0", e_skeleton_g);
    LOAD_ASSET_GFX("assets/st/nz0", e_slinger_g);
    LOAD_ASSET_GFX("assets/st/nz0", e_slogra_g0);
    LOAD_ASSET_GFX("assets/st/nz0", e_slogra_g1);
    LOAD_ASSET_GFX("assets/st/nz0", e_slogra_g2);
    LOAD_ASSET_GFX("assets/st/nz0", e_table_blue_flame_g);
    LOAD_ASSET_GFX("assets/st/nz0", e_table_with_alembic_g);
    LOAD_ASSET_GFX("assets/st/nz0", e_table_with_globe_g);
    LOAD_ASSET_GFX("assets/st/nz0", stage_title_nz0_jp);
    LOAD_ASSET_GFX("assets/st/nz0", stage_title_nz0_us);
    LOAD_ASSET_PAL("assets/st/nz0", D_80195CBC);
    LOAD_ASSET_PAL("assets/st/nz0", D_80195CFC);
    LOAD_ASSET_PAL("assets/st/nz0", D_8019621C);
    LOAD_ASSET_PAL("assets/st/nz0", D_8019661C);
    LOAD_ASSET_PAL("assets/st/nz0", D_8019665C);
    LOAD_ASSET_PAL("assets/st/nz0", D_8019675C);
    LOAD_ASSET_PAL("assets/st/nz0", D_8019685C);
    LOAD_ASSET_PAL("assets/st/nz0", D_8019695C);
    LOAD_ASSET_PAL("assets/st/nz0", e_axe_knight_p);
    LOAD_ASSET_PAL("assets/st/nz0", e_blood_skeleton_p);
    LOAD_ASSET_PAL("assets/st/nz0", e_bloody_zombie_p);
    LOAD_ASSET_PAL("assets/st/nz0", e_cloche_p);
    LOAD_ASSET_PAL("assets/st/nz0", e_explosion_p);
    LOAD_ASSET_PAL("assets/st/nz0", e_gaibon_p);
    LOAD_ASSET_PAL("assets/st/nz0", e_maria_nz0_p);
    LOAD_ASSET_PAL("assets/st/nz0", e_sealed_door_p);
    LOAD_ASSET_PAL("assets/st/nz0", e_skelerang_p);
    LOAD_ASSET_PAL("assets/st/nz0", e_skeleton_p);
    LOAD_ASSET_PAL("assets/st/nz0", e_slinger_p);
    LOAD_ASSET_PAL("assets/st/nz0", e_slogra_p);
    LOAD_ASSET_PAL("assets/st/nz0", e_table_blue_flame_p);
    LOAD_ASSET_PAL("assets/st/nz0", e_table_with_alembic_p);
    LOAD_ASSET_PAL("assets/st/nz0", e_table_with_globe_p);
    memcpy(o, &OVL_EXPORT(Overlay), sizeof(AbbreviatedOverlay));
    // PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = OVL_EXPORT(pStObjLayoutHorizontal);
    g_pStObjLayoutVertical = OVL_EXPORT(pStObjLayoutVertical);
}
