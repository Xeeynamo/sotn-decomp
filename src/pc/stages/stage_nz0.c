// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <string.h>
#include "overlay.h"
#include "../st/nz0/nz0.h"
#include "stage_loader.h"
#include "stage_init.h"

extern AbbreviatedOverlay OVL_EXPORT(Overlay);
extern PfnEntityUpdate EntityUpdates[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutHorizontal)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutVertical)[];
extern GAME_IMPORT PfnEntityUpdate* PfnEntityUpdates;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutHorizontal;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutVertical;
OVL_API void InitStage(Overlay* o) {
    LoadReset();
    InitOnce();
    memcpy(o, &OVL_EXPORT(Overlay), sizeof(AbbreviatedOverlay));
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = OVL_EXPORT(pStObjLayoutHorizontal);
    g_pStObjLayoutVertical = OVL_EXPORT(pStObjLayoutVertical);
}
