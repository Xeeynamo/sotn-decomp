// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <cutscene.h>
#include <string.h>
#include "stage_loader.h"
#include "overlay.h"
#include "../st/st0/st0.h"

extern Overlay OVL_EXPORT(Overlay);
extern PfnEntityUpdate EntityUpdates[];
extern LayoutEntity* entityLayoutHorizontal[];
extern LayoutEntity* entityLayoutVertical[];
extern GAME_IMPORT PfnEntityUpdate* PfnEntityUpdates;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutHorizontal;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutVertical;

extern u8 gfx_portrait_richter[];
extern u8 gfx_portrait_dracula[];

u8 OVL_EXPORT(cutscene_script)[] = {
#include "../../st/st0/gen/cutscene_script_psx.h"
#include "../../st/st0/gen/cutscene_events.h"
};

static void InitCutscenePc(void) {
    static const CutsceneSymbolRange symbols[] = {
        {OVL_EXPORT(cutscene_script), 0x801829d8,
         sizeof(OVL_EXPORT(cutscene_script))},
        {gfx_portrait_richter, 0x8018f130, 0xd80},
        {gfx_portrait_dracula, 0x8018feb0, 0xd80},
    };
    CutscenePcAlloc(symbols, LEN(symbols));
}

OVL_API void InitStage(Overlay* o) {
    LoadReset();
    memcpy(o, &OVL_EXPORT(Overlay), sizeof(Overlay));
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = entityLayoutHorizontal;
    g_pStObjLayoutVertical = entityLayoutVertical;
    InitCutscenePc();
}
