// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <cutscene.h>
#include <string.h>
#include "overlay.h"
#include "../pc.h"
#include "../../st/lib/lib.h"

extern Overlay g_Overlay;
extern PfnEntityUpdate EntityUpdates[];
extern LayoutEntity* entityLayoutHorizontal[];
extern LayoutEntity* entityLayoutVertical[];
extern GAME_IMPORT PfnEntityUpdate* PfnEntityUpdates;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutHorizontal;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutVertical;

s32 metLibrarian = 0;
s32 D_us_80183F64 = 0;

extern u8 gfx_portrait_alucard[];
extern u8 gfx_portrait_master_librarian[];

u8 cutscene_data[] = {
#include "../../st/lib/gen/cutscene_data.h"
#include "../../st/lib/gen/cutscene_events.h"
};

static void InitCutscenePc(void) {
    static const CutsceneSymbolRange symbols[] = {
        {&metLibrarian, 0x80183f60, sizeof(s32)},
        {&D_us_80183F64, 0x80183f64, sizeof(s32)},
        {cutscene_data, 0x80183f68, sizeof(cutscene_data)},
        {gfx_portrait_alucard, 0x8018a488, 0xD80},
        {gfx_portrait_master_librarian, 0x8018b208, 0xD80},
    };
    CutscenePcAlloc(symbols, LEN(symbols));
}

OVL_API void InitStage(Overlay* o) {
    memcpy(o, &g_Overlay, sizeof(AbbreviatedOverlay));
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = entityLayoutHorizontal;
    g_pStObjLayoutVertical = entityLayoutVertical;
    InitCutscenePc();
}
