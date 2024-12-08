// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <string.h>
#include "stage_loader.h"
#include "../st/st0/st0.h"

u8 bg_moon[1688];
u8 bg_sky[3164];
u8 bg_tower_g0[6372];
u8 bg_tower_g1[1980];
u8 D_80191B8C[8740];
u8 e_breakables_g[2484];
u8 e_dracula1_g0[2912];
u8 e_dracula1_g1[4080];
u8 e_dracula1_g2[4200];
u8 e_dracula1_g3[2944];
u8 e_dracula1_g9[1432];
u8 e_dracula2_g1[4456];
u8 e_dracula2_g2[3788];
u8 e_dracula2_g3[3472];
u8 e_dracula2_g4[2848];
u8 e_dracula2_g5[3568];
u8 e_dracula2_g6[3968];
u8 e_dracula2_g9[3424];
u8 e_dracula_particles_g[5008];
u8 e_secret_stairs_g[3692];
u8 e_smoke_g[3556];
u8 richter_cutscene[2108];
u8 richter_hud[3644];
u8 richter_subweapons[3064];
u8 stage_title_st0_jp[1448];
u8 stage_title_st0_us[836];
u8 bg_moon_p[512];
u8 D_8019A830[256];
u8 D_8019A930[256];
u8 D_8019AA30[256];
u8 D_8019AB30[256];
u8 D_8019AD70[96];
u8 D_8019AE70[192];
u8 D_8019B210[192];
u8 e_breakables_p[256];
u8 e_dracula_p[224];
u8 e_secret_stairs_p[224];
u8 e_smoke_p[160];
u8 stage_title_p[64];

// bss
u16 msgBoxTpage[768];
u32 D_801C06B0[4];
u32 D_801C06C0[1346];
SVECTOR D_801C1BC8[0x100];
u32 D_801C23C8[64];
u32 D_801C2510[26];
s32 D_801C2578;

extern Overlay OVL_EXPORT(Overlay);
extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutHorizontal)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutVertical)[];
extern PfnEntityUpdate* PfnEntityUpdates;
extern LayoutEntity** g_pStObjLayoutHorizontal;
extern LayoutEntity** g_pStObjLayoutVertical;
void InitStageST0(Overlay* o) {
    LoadReset();
    LOAD_ASSET_GFX("assets/st/st0", bg_moon);
    LOAD_ASSET_GFX("assets/st/st0", bg_sky);
    LOAD_ASSET_GFX("assets/st/st0", bg_tower_g0);
    LOAD_ASSET_GFX("assets/st/st0", bg_tower_g1);
    LOAD_ASSET_GFX("assets/st/st0", D_80191B8C);
    LOAD_ASSET_GFX("assets/st/st0", e_breakables_g);
    LOAD_ASSET_GFX("assets/st/st0", e_dracula1_g0);
    LOAD_ASSET_GFX("assets/st/st0", e_dracula1_g1);
    LOAD_ASSET_GFX("assets/st/st0", e_dracula1_g2);
    LOAD_ASSET_GFX("assets/st/st0", e_dracula1_g3);
    LOAD_ASSET_GFX("assets/st/st0", e_dracula1_g9);
    LOAD_ASSET_GFX("assets/st/st0", e_dracula2_g1);
    LOAD_ASSET_GFX("assets/st/st0", e_dracula2_g2);
    LOAD_ASSET_GFX("assets/st/st0", e_dracula2_g3);
    LOAD_ASSET_GFX("assets/st/st0", e_dracula2_g4);
    LOAD_ASSET_GFX("assets/st/st0", e_dracula2_g5);
    LOAD_ASSET_GFX("assets/st/st0", e_dracula2_g6);
    LOAD_ASSET_GFX("assets/st/st0", e_dracula2_g9);
    LOAD_ASSET_GFX("assets/st/st0", e_dracula_particles_g);
    LOAD_ASSET_GFX("assets/st/st0", e_secret_stairs_g);
    LOAD_ASSET_GFX("assets/st/st0", e_smoke_g);
    LOAD_ASSET_GFX("assets/st/st0", richter_cutscene);
    LOAD_ASSET_GFX("assets/st/st0", richter_hud);
    LOAD_ASSET_GFX("assets/st/st0", richter_subweapons);
    LOAD_ASSET_GFX("assets/st/st0", stage_title_st0_jp);
    LOAD_ASSET_GFX("assets/st/st0", stage_title_st0_us);
    LOAD_ASSET_PAL("assets/st/st0", bg_moon_p);
    LOAD_ASSET_PAL("assets/st/st0", D_8019A830);
    LOAD_ASSET_PAL("assets/st/st0", D_8019A930);
    LOAD_ASSET_PAL("assets/st/st0", D_8019AA30);
    LOAD_ASSET_PAL("assets/st/st0", D_8019AB30);
    LOAD_ASSET_PAL("assets/st/st0", D_8019AD70);
    LOAD_ASSET_PAL("assets/st/st0", D_8019AE70);
    LOAD_ASSET_PAL("assets/st/st0", D_8019B210);
    LOAD_ASSET_PAL("assets/st/st0", e_breakables_p);
    LOAD_ASSET_PAL("assets/st/st0", e_dracula_p);
    LOAD_ASSET_PAL("assets/st/st0", e_secret_stairs_p);
    LOAD_ASSET_PAL("assets/st/st0", e_smoke_p);
    LOAD_ASSET_PAL("assets/st/st0", stage_title_p);
    memcpy(o, &OVL_EXPORT(Overlay), sizeof(Overlay));
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = OVL_EXPORT(pStObjLayoutHorizontal);
    g_pStObjLayoutVertical = OVL_EXPORT(pStObjLayoutVertical);
}

void EntityClouds(Entity* self) { NOT_IMPLEMENTED; }
