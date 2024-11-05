// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stage_loader.h"
#include "../st/cen/cen.h"

u8 e_elevator_cen_g[3420];
u8 e_maria_cen_g0[4400];
u8 e_maria_cen_g1[3264];
u8 D_8018658C[256];
u8 D_8018668C[256];
u8 D_8018678C[256];
u8 D_8018688C[256];
u8 e_elevator_cen_p[64];
u8 e_maria_cen_p[32];

extern Overlay OVL_EXPORT(Overlay);
extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutHorizontal)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutVertical)[];
extern PfnEntityUpdate* PfnEntityUpdates;
extern LayoutEntity** g_pStObjLayoutHorizontal;
extern LayoutEntity** g_pStObjLayoutVertical;
void InitStageCEN(Overlay* o) {
    LoadReset();
    LOAD_ASSET_GFX("assets/st/wrp", stage_placeholder);
    LOAD_ASSET_GFX("assets/st/wrp", stage_title_jp);
    LOAD_ASSET_GFX("assets/st/cen", e_elevator_cen_g);
    LOAD_ASSET_GFX("assets/st/cen", e_maria_cen_g0);
    LOAD_ASSET_GFX("assets/st/cen", e_maria_cen_g1);
    LOAD_ASSET_PAL("assets/st/cen", D_8018658C);
    LOAD_ASSET_PAL("assets/st/cen", D_8018668C);
    LOAD_ASSET_PAL("assets/st/cen", D_8018678C);
    LOAD_ASSET_PAL("assets/st/cen", D_8018688C);
    LOAD_ASSET_PAL("assets/st/cen", e_elevator_cen_p);
    LOAD_ASSET_PAL("assets/st/cen", e_maria_cen_p);
    memcpy(o, &OVL_EXPORT(Overlay), sizeof(Overlay));
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = OVL_EXPORT(pStObjLayoutHorizontal);
    g_pStObjLayoutVertical = OVL_EXPORT(pStObjLayoutVertical);
}
