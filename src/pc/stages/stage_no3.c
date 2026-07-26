// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <cutscene.h>
#include <string.h>
#include "stage_loader.h"
#include "overlay.h"
#include "../../st/no3/no3.h"

extern AbbreviatedOverlay OVL_EXPORT(Overlay);
extern PfnEntityUpdate EntityUpdates[];
extern LayoutEntity* entityLayoutHorizontal[];
extern LayoutEntity* entityLayoutVertical[];
extern GAME_IMPORT PfnEntityUpdate* PfnEntityUpdates;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutHorizontal;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutVertical;

extern u8 cutscene_alucard[];
extern u8 cutscene_death[];

u8 cutscene_data[] = {
#include "../../st/no3/gen/cutscene_data.h"
#include "../../st/no3/gen/cutscene_events.h"
};

static void InitCutscenePc(void) {
    static const CutsceneSymbolRange symbols[] = {
        {cutscene_data, 0x80184CE0, sizeof(cutscene_data)},
        {cutscene_alucard, 0x80191b88, 0xd80},
        {cutscene_death, 0x80192908, 0xd80},
    };
    CutscenePcAlloc(symbols, LEN(symbols));
}

OVL_API void InitStage(Overlay* o) {
    LoadReset();
    memcpy(o, &OVL_EXPORT(Overlay), sizeof(AbbreviatedOverlay));
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = entityLayoutHorizontal;
    g_pStObjLayoutVertical = entityLayoutVertical;
    InitCutscenePc();
}
