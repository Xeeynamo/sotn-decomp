// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rlib/rlib.h"
#include "../pfn_entity_update.h"

extern s32 E_ID(BACKGROUND_BLOCK);
extern s32 E_ID(LOCK_CAMERA);
extern s32 E_ID(UNK_ID13);
extern s32 E_ID(EXPLOSION_VARIANTS);
extern s32 E_ID(GREY_PUFF);
extern s32 E_ID(BG_BOOKCASE);
extern s32 E_ID(BG_FURNITURE);
extern s32 E_ID(BG_SHADOW);
extern s32 E_ID(DISTANT_SHELVES);
extern s32 E_ID(THICK_BOOKCASE);
extern s32 E_ID(UNK_1B);
extern s32 E_ID(LION);
extern s32 E_ID(LION_ATTACK);
extern s32 E_ID(LION_DEATH_PARTS);
extern s32 E_ID(TINMAN);
extern s32 E_ID(TINMAN_ARM);
extern s32 E_ID(TINMAN_PROJECTILE);
extern s32 E_ID(TINMAN_SMOKE);
extern s32 E_ID(TINMAN_DEATH_PARTS);
extern s32 E_ID(SCARECROW);
extern s32 E_ID(SCARECROW_LIMB);
extern s32 E_ID(EXPLODE_PUFF_OPAQUE);
extern s32 E_ID(SCHMOO);
extern s32 E_ID(BREAKABLE_DEBRIS);
extern s32 E_ID(CANDLE_TABLE);

void InitEntityIds(void) {
    SET_E_ID(BACKGROUND_BLOCK);
    SET_E_ID(LOCK_CAMERA);
    SET_E_ID(UNK_ID13);
    SET_E_ID(EXPLOSION_VARIANTS);
    SET_E_ID(GREY_PUFF);
    SET_E_ID(BG_BOOKCASE);
    SET_E_ID(BG_FURNITURE);
    SET_E_ID(BG_SHADOW);
    SET_E_ID(DISTANT_SHELVES);
    SET_E_ID(THICK_BOOKCASE);
    SET_E_ID(UNK_1B);
    SET_E_ID(LION);
    SET_E_ID(LION_ATTACK);
    SET_E_ID(LION_DEATH_PARTS);
    SET_E_ID(TINMAN);
    SET_E_ID(TINMAN_ARM);
    SET_E_ID(TINMAN_PROJECTILE);
    SET_E_ID(TINMAN_SMOKE);
    SET_E_ID(TINMAN_DEATH_PARTS);
    SET_E_ID(SCARECROW);
    SET_E_ID(SCARECROW_LIMB);
    SET_E_ID(EXPLODE_PUFF_OPAQUE);
    SET_E_ID(SCHMOO);
    SET_E_ID(BREAKABLE_DEBRIS);
    SET_E_ID(CANDLE_TABLE);
}

extern LayoutEntity* D_8D2DFC8;
extern LayoutEntity* D_8D2E09C;
extern AbbreviatedOverlay g_StageOverlay;

void RLIB_Load(void) {
    InitEntityIds();
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = &D_8D2DFC8;
    g_pStObjLayoutVertical = &D_8D2E09C;
    func_892A018();
    memcpy(&g_api.o, &g_StageOverlay, 0x40);
}
