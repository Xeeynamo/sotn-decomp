// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <cutscene.h>
#include <string.h>
#include "overlay.h"
#include "../pc.h"
#include "../../st/dre/dre.h"

extern Overlay g_Overlay;
extern PfnEntityUpdate EntityUpdates[];
extern LayoutEntity* entityLayoutHorizontal[];
extern LayoutEntity* entityLayoutVertical[];
extern GAME_IMPORT PfnEntityUpdate* PfnEntityUpdates;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutHorizontal;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutVertical;

extern u8 gfx_portrait_alucard[];
extern u8 gfx_portrait_lisa[];
extern u8 gfx_portrait_succubus[];

u8 D_801816C0 = 0;
u8 D_801816C4[4] = {0};

u8 cutscene_script[] = {
#include "../../st/dre/gen/cutscene_script_psx.h"
#include "../../st/dre/gen/cutscene_events.h"
};

static void InitCutscenePc(void) {
    static const CutsceneSymbolRange symbols[] = {
        {D_801816C4, 0x801816c4, sizeof(D_801816C4)},
        {cutscene_script, 0x801816c8,
         sizeof(cutscene_script)},
        {gfx_portrait_alucard, 0x8018800c, 0xd80},
        {gfx_portrait_lisa, 0x80188d8c, 0xd80},
        {gfx_portrait_succubus, 0x80189b0c, 0xd80},
    };
    CutscenePcAlloc(symbols, LEN(symbols));
}

OVL_API void InitStage(Overlay* o) {
    memcpy(o, &g_Overlay, sizeof(Overlay));
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = entityLayoutHorizontal;
    g_pStObjLayoutVertical = entityLayoutVertical;
    InitCutscenePc();
}
