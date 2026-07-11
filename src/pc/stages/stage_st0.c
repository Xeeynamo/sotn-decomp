// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <string.h>
#include "../st/st0/st0.h"
#include "stage_loader.h"

extern Overlay OVL_EXPORT(Overlay);
extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutHorizontal)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutVertical)[];
extern PfnEntityUpdate* PfnEntityUpdates;
extern LayoutEntity** g_pStObjLayoutHorizontal;
extern LayoutEntity** g_pStObjLayoutVertical;
void InitStageST0(Overlay* o) {
    LoadReset();
    InitOnce();
    memcpy(o, &OVL_EXPORT(Overlay), sizeof(Overlay));
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = OVL_EXPORT(pStObjLayoutHorizontal);
    g_pStObjLayoutVertical = OVL_EXPORT(pStObjLayoutVertical);
}
