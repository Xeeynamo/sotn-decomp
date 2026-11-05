// SPDX-License-Identifier: AGPL-3.0-or-later
#include <psyz/module.h>
#include <game.h>
#include <string.h>
#include "overlay.h"
#include "../../st/rdai/rdai.h"

extern AbbreviatedOverlay g_Overlay;
extern PfnEntityUpdate EntityUpdates[];
extern LayoutEntity* entityLayoutHorizontal[];
extern LayoutEntity* entityLayoutVertical[];
extern PfnEntityUpdate* PfnEntityUpdates;
extern LayoutEntity** g_pStObjLayoutHorizontal;
extern LayoutEntity** g_pStObjLayoutVertical;
extern u_long* cluts[];
extern u16 pal_A420[];

static void PatchA420PalettePc(void) {
    // PAL_BULK_(0x2240, pal_A420, 0x90) copies 0x90 colors, while pal_A420
    // only has 0x60
    u_long** palDefs = (u_long**)cluts[0];
    for (int i = 1; palDefs[i] != PAL_TERMINATE(); i++) {
        if (palDefs[i] == (u_long*)pal_A420) {
            palDefs[i - 1] = (u_long*)0x60;
            break;
        }
    }
}

void Psyz_ModuleStart(void* param) {
    Overlay* o = param;

    memcpy(o, &g_Overlay, sizeof(AbbreviatedOverlay));
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = entityLayoutHorizontal;
    g_pStObjLayoutVertical = entityLayoutVertical;
    PatchA420PalettePc();
}

void Psyz_ModuleStop(void) {}
