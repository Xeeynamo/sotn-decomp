// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo0.h"
#include "../../st/pfn_entity_update.h"

static void InitEntityIds(void) {
    E_ID(BACKGROUND_BLOCK) = E_BACKGROUND_BLOCK;
    E_ID(LOCK_CAMERA) = E_LOCK_CAMERA;
    E_ID(UNK_ID13) = E_UNK_ID13;
    E_ID(EXPLOSION_VARIANTS) = E_EXPLOSION_VARIANTS;
    E_ID(GREY_PUFF) = E_GREY_PUFF;
    E_ID(BOSS_TORCH) = E_BOSS_TORCH;
    E_ID(BOSS_DOORS) = E_BOSS_DOORS;
    E_ID(LIFE_UP_SPAWN) = E_LIFE_UP_SPAWN;
    E_ID(COFFIN) = E_COFFIN;
    E_ID(UNK_1A) = E_UNK_1A;
    E_ID(FAKE_RALPH) = E_FAKE_RALPH;
    E_ID(FAKE_GRANT) = E_FAKE_GRANT;
    E_ID(FAKE_SYPHA) = E_FAKE_SYPHA;
    E_ID(BONE_CROSS) = E_BONE_CROSS;
    E_ID(BONE_CROSS_AFTER_IMAGE) = E_BONE_CROSS_AFTER_IMAGE;
    E_ID(GIANT_BONE_CROSS) = E_GIANT_BONE_CROSS;
    E_ID(DAGGER) = E_DAGGER;
    E_ID(HOLY_WATER_FLASK) = E_HOLY_WATER_FLASK;
    E_ID(HOLY_WATER_FLAME) = E_HOLY_WATER_FLAME;
    E_ID(VERTICAL_DAGGER) = E_VERTICAL_DAGGER;
    E_ID(HORIZONTAL_DAGGER) = E_HORIZONTAL_DAGGER;
    E_ID(UNK_26) = E_UNK_26;
    E_ID(UNK_27) = E_UNK_27;
    E_ID(DEATH_FLAMES) = E_DEATH_FLAMES;
    E_ID(HOLY_FLAME) = E_HOLY_FLAME;
    E_ID(PETRIFY_CLOUD) = E_PETRIFY_CLOUD;
    E_ID(HOLY_LIGHTNING) = E_HOLY_LIGHTNING;
    E_ID(RESURRECT) = E_RESURRECT;
}

extern LayoutEntity* D_8D2DE10;
extern LayoutEntity* D_8D2DEE4;
extern Overlay OVL_EXPORT(Overlay);

void OVL_EXPORT(Load)(void) {
    InitEntityIds();
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = &D_8D2DE10;
    g_pStObjLayoutVertical = &D_8D2DEE4;
    func_892A018();
    memcpy(&g_api.o, &OVL_EXPORT(Overlay), sizeof(Overlay));
}
