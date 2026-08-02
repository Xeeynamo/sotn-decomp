// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno0/rno0.h"
#include "../pfn_entity_update.h"

extern LayoutEntity* D_8D2E394;
extern LayoutEntity* D_8D2E468;

extern Overlay OVL_EXPORT(Overlay);


INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/st_init", InitEntityIds);

void OVL_EXPORT(Load)(void) {
    InitEntityIds();
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = &D_8D2E394;
    g_pStObjLayoutVertical = &D_8D2E468;
    func_892A018();
    memcpy(&g_api.o, &OVL_EXPORT(Overlay), sizeof(Overlay));
}