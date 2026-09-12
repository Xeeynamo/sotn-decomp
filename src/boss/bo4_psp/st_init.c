// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../bo4/bo4.h"

#include "../../st/pfn_entity_update.h"

s32 E_ID(BACKGROUND_BLOCK);
s32 E_ID(LOCK_CAMERA);
s32 E_ID(ID_13);
s32 E_ID(EXPLOSION_VARIANTS);
s32 E_ID(GREY_PUFF);
s32 E_ID(ID_16);
s32 E_ID(ID_17);
s32 E_ID(ID_18);
s32 E_ID(ID_19);
s32 E_ID(ID_1A);
s32 E_ID(ID_1B);
s32 E_ID(ID_1C);
s32 E_ID(ID_1D);

void InitEntityIds(void) {
    SET_E_ID(BACKGROUND_BLOCK);
    SET_E_ID(LOCK_CAMERA);
    SET_E_ID(ID_13);
    SET_E_ID(EXPLOSION_VARIANTS);
    SET_E_ID(GREY_PUFF);
    SET_E_ID(ID_16);
    SET_E_ID(ID_17);
    SET_E_ID(ID_18);
    SET_E_ID(ID_19);
    SET_E_ID(ID_1A);
    SET_E_ID(ID_1B);
    SET_E_ID(ID_1C);
    SET_E_ID(ID_1D);
}

extern LayoutEntity* D_8D2DDC8[];
extern LayoutEntity* D_8D2DE9C[];
extern AbbreviatedOverlay2 g_BossOverlay;
extern void* D_pspeu_09263438;
extern void* D_pspeu_09263440;

void func_892A018(void);
void func_8929FA8(void* arg0, s32 arg1);

void BO4_Load(void) {
    InitEntityIds();
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = D_8D2DDC8;
    g_pStObjLayoutVertical = D_8D2DE9C;
    func_892A018();
    func_8929FA8(D_pspeu_09263438, 0xD3);
    func_8929FA8(D_pspeu_09263440, 0x6);
    memcpy(&g_api.o, &g_BossOverlay, sizeof(Overlay));
}
