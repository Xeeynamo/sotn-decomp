// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stage_loader.h"
#include "../../st/wrp/wrp.h"

u8 D_80181D08[32];
u8 D_80181D28[64];

extern Overlay OVL_EXPORT(Overlay);
extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutHorizontal)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutVertical)[];
extern PfnEntityUpdate* PfnEntityUpdates;
extern LayoutEntity** g_pStObjLayoutHorizontal;
extern LayoutEntity** g_pStObjLayoutVertical;
void InitStageWRP(Overlay* o) {
    LoadReset();
    LOAD_ASSET_GFX("assets/st/wrp", stage_placeholder);
    LOAD_ASSET_GFX("assets/st/wrp", stage_title_jp);
    LOAD_ASSET_PAL("assets/st/wrp", D_80181D08);
    LOAD_ASSET_PAL("assets/st/wrp", D_80181D28);
    memcpy(o, &OVL_EXPORT(Overlay), sizeof(Overlay));
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = OVL_EXPORT(pStObjLayoutHorizontal);
    g_pStObjLayoutVertical = OVL_EXPORT(pStObjLayoutVertical);
}
