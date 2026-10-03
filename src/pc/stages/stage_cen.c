// SPDX-License-Identifier: AGPL-3.0-or-later
#include <psyz/module.h>
#include <game.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "overlay.h"
#include "../pc.h"
#include "../st/cen/cen.h"

extern Overlay g_Overlay;
extern PfnEntityUpdate EntityUpdates[];
extern LayoutEntity* entityLayoutHorizontal[];
extern LayoutEntity* entityLayoutVertical[];
extern PfnEntityUpdate* PfnEntityUpdates;
extern LayoutEntity** g_pStObjLayoutHorizontal;
extern LayoutEntity** g_pStObjLayoutVertical;

extern u8 cutscene_cen_alucard[];
extern u8 cutscene_cen_maria[];

static void InitCutscenePc(void) {
    static const CutsceneSymbolRange symbols[] = {
        {cutscene_cen_alucard, 0x80181f40, 0xd80},
        {cutscene_cen_maria, 0x80182cc0, 0xd80},
    };
    CutscenePcAlloc(symbols, LEN(symbols));
}

void Psyz_ModuleStart(void* param) {
    Overlay* o = param;

    memcpy(o, &g_Overlay, sizeof(Overlay));
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = entityLayoutHorizontal;
    g_pStObjLayoutVertical = entityLayoutVertical;
    InitCutscenePc();
}

void Psyz_ModuleStop(void) {}
