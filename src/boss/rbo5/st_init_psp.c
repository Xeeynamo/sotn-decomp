// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

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
s32 E_ID(ID_1E);

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
    SET_E_ID(ID_1E);
}

extern LayoutEntity* D_8D2DDD8[];
extern LayoutEntity* D_8D2DEAC[];
extern AbbreviatedOverlay2 g_BossOverlay;
extern u8** doppleganger_sprites;
extern u8** bat_form_sprites;

void func_892A018(void);
void func_8929FA8(void* arg0, s32 arg1);

void RBO5_Load(void) {
    InitEntityIds();
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = D_8D2DDD8;
    g_pStObjLayoutVertical = D_8D2DEAC;
    func_892A018();
    func_8929FA8(doppleganger_sprites, 0xD3);
    func_8929FA8(bat_form_sprites, 0x6);
    memcpy(&g_api.o, &g_BossOverlay, sizeof(Overlay));
}
