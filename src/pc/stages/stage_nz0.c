// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <cutscene.h>
#include <string.h>
#include "stage_loader.h"
#include "overlay.h"
#include "../st/nz0/nz0.h"

extern AbbreviatedOverlay OVL_EXPORT(Overlay);
extern PfnEntityUpdate EntityUpdates[];
extern LayoutEntity* entityLayoutHorizontal[];
extern LayoutEntity* entityLayoutVertical[];
extern GAME_IMPORT PfnEntityUpdate* PfnEntityUpdates;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutHorizontal;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutVertical;

extern u8 cutscene_nz0_maria[];
extern u8 cutscene_nz0_alucard[];

u8 OVL_EXPORT(cutscene_data)[] = {
#include "../../st/nz0/gen/cutscene_data.h"
    0x81, 0x4D, 0x08, 0x80, 0x08, 0x80, 0x00, 0x00, 0x00, 0x82,
    0x4C, 0x00, 0x00, 0x08, 0x83, 0xFF, 0xFF, 0x00, 0x00, 0x00};

static void InitCutscenePc(void) {
    static const CutsceneSymbolRange symbols[] = {
        {OVL_EXPORT(cutscene_data), 0x80183B0C,
         sizeof(OVL_EXPORT(cutscene_data))},
        {cutscene_nz0_maria, 0x80193ba4, 0xd80},
        {cutscene_nz0_alucard, 0x80194924, 0xd80},
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
