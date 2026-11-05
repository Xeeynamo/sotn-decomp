// SPDX-License-Identifier: AGPL-3.0-or-later
#include <psyz/module.h>
#include <game.h>
#include <string.h>
#include "overlay.h"
#include "../../st/no1/no1.h"

s32 D_us_801D6FFC;
s32 D_us_801D7000;
s32 D_us_801D7004;
s32 D_us_801D7008;
s32 D_us_801D700C;
s32 D_us_801D7010;
s32 D_us_801D7014;
s32 D_us_801D7018;
s32 D_us_801D701C;
s32 D_us_801D7020;

extern AbbreviatedOverlay g_Overlay;
extern PfnEntityUpdate EntityUpdates[];
extern LayoutEntity* entityLayoutHorizontal[];
extern LayoutEntity* entityLayoutVertical[];
extern PfnEntityUpdate* PfnEntityUpdates;
extern LayoutEntity** g_pStObjLayoutHorizontal;
extern LayoutEntity** g_pStObjLayoutVertical;
void Psyz_ModuleStart(void* param) {
    Overlay* o = param;

    memcpy(o, &g_Overlay, sizeof(AbbreviatedOverlay));
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = entityLayoutHorizontal;
    g_pStObjLayoutVertical = entityLayoutVertical;
}

void Psyz_ModuleStop(void) {}
