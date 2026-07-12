// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../stages/stage_loader.h"
#include "../stages/overlay.h"
#include "../boss/bo4/bo4.h"

extern AbbreviatedOverlay2 OVL_EXPORT(Overlay);
extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutHorizontal)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutVertical)[];
extern GAME_IMPORT PfnEntityUpdate* PfnEntityUpdates;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutHorizontal;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutVertical;

// stubs
AluFrame* D_us_801B0A78[1] = {0};
DopWeaponAnimation D_us_80184278[1] = {0};
SpriteParts* D_us_801B159C[1] = {0};
SpriteParts* D_us_801B1664[1] = {0};
SpriteParts* D_us_801B2068[1] = {0};
SpriteParts* D_us_801B252C[1] = {0};

OVL_API void InitStage(Overlay* o) {
    LoadReset();
    memcpy(o, &OVL_EXPORT(Overlay), sizeof(AbbreviatedOverlay2));
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = OVL_EXPORT(pStObjLayoutHorizontal);
    g_pStObjLayoutVertical = OVL_EXPORT(pStObjLayoutVertical);
}
