// SPDX-License-Identifier: AGPL-3.0-or-later
#include <psyz/module.h>
#include <game.h>
#include <cutscene.h>
#include <string.h>
#include "overlay.h"
#include "../pc.h"
#include "../../st/rcen/rcen.h"

extern Overlay g_Overlay;
extern PfnEntityUpdate EntityUpdates[];
extern LayoutEntity* entityLayoutHorizontal[];
extern LayoutEntity* entityLayoutVertical[];
extern PfnEntityUpdate* PfnEntityUpdates;
extern LayoutEntity** g_pStObjLayoutHorizontal;
extern LayoutEntity** g_pStObjLayoutVertical;

// Read by the SCRIPT_SWITCH in the cutscene script; never written on PSX
static s32 D_us_801817A8 = 0;

extern u8 gfx_portrait_alucard[];
extern u8 gfx_portrait_shaft[];

u8 cutscene_script[] = {
#include "../../st/rcen/gen/cutscene_script_psx.h"
#include "../../st/rcen/gen/cutscene_events.h"
};

static void InitCutscenePc(void) {
    static const CutsceneSymbolRange symbols[] = {
        {&D_us_801817A8, 0x801817a8, sizeof(s32)},
        {cutscene_script, 0x801817ac, sizeof(cutscene_script)},
        {gfx_portrait_alucard, 0x8018ec70, 0xd80},
        {gfx_portrait_shaft, 0x8018f9f0, 0xd80},
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
