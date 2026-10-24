// SPDX-License-Identifier: AGPL-3.0-or-later
#include <psyz/module.h>
#include <game.h>
#include <string.h>
#include <stage.h>
#include "../pc.h"

extern AbbreviatedOverlay g_BossOverlay;
extern PfnEntityUpdate EntityUpdates[];
extern LayoutEntity* entityLayoutHorizontal[];
extern LayoutEntity* entityLayoutVertical[];
extern PfnEntityUpdate* PfnEntityUpdates;
extern LayoutEntity** g_pStObjLayoutHorizontal;
extern LayoutEntity** g_pStObjLayoutVertical;

extern u8 cutscene_script[];
extern u8 D_us_8018A928[];
extern u8 D_us_8018B6A8[];

static void InitCutscenePc(void) {
    static const CutsceneSymbolRange symbols[] = {
        {cutscene_script, 0x80181d5c, 0x243},
        {D_us_8018A928, 0x8018a928, 0xd80},
        {D_us_8018B6A8, 0x8018b6a8, 0xd80},
    };
    CutscenePcAlloc(symbols, LEN(symbols));
}

void Psyz_ModuleStart(void* param) {
    AbbreviatedOverlay* o = param;

    memcpy(o, &g_BossOverlay, sizeof(AbbreviatedOverlay));
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = entityLayoutHorizontal;
    g_pStObjLayoutVertical = entityLayoutVertical;
    InitCutscenePc();
}

void Psyz_ModuleStop(void) {}
