// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <string.h>
#include "overlay.h"
#include "../../st/np3/np3.h"

extern AbbreviatedOverlay OVL_EXPORT(Overlay);
extern PfnEntityUpdate EntityUpdates[];
extern LayoutEntity* entityLayoutHorizontal[];
extern LayoutEntity* entityLayoutVertical[];
extern GAME_IMPORT PfnEntityUpdate* PfnEntityUpdates;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutHorizontal;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutVertical;

extern u_long* cluts[];
extern u16 e_slogra_p[];

static void PatchSlograPalettePc(void) {
    // On NP3: PAL_BULK_(0x2D90, e_slogra_p, 0x90),
    // On NZ0: PAL_BULK_(0x2270, e_slogra_p, 0x30),
    // NP3 wrongly assigns a color count of 0x90, while the real color data
    // only has 0x30 colors. This results on the PC port crashing when the
    // stage loader attempts reading beyond the end of the array. Patch the
    // PAL_BULK to 0x30, same as NZ0.
    u_long** palDefs = (u_long**)cluts[0];
    for (int i = 1; palDefs[i] != PAL_TERMINATE(); i++) {
        if (palDefs[i] == (u_long*)e_slogra_p) {
            palDefs[i - 1] = (u_long*)0x30;
            break;
        }
    }
}

OVL_API void InitStage(Overlay* o) {
    memcpy(o, &OVL_EXPORT(Overlay), sizeof(AbbreviatedOverlay));
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = entityLayoutHorizontal;
    g_pStObjLayoutVertical = entityLayoutVertical;
    PatchSlograPalettePc();
}
