// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rare/rare.h"

#include "../pfn_entity_update.h"

extern LayoutEntity* D_8D2E0FC;
extern LayoutEntity* D_8D2E1D0;

extern Overlay OVL_EXPORT(Overlay);

s32 E_ID(BACKGROUND_BLOCK);
s32 E_ID(LOCK_CAMERA);
s32 E_ID(UNK_ID13);
s32 E_ID(EXPLOSION_VARIANTS);
s32 E_ID(GREY_PUFF);
s32 E_ID(UNK_16);
s32 E_ID(UNK_17);
s32 E_ID(UNK_18);
s32 E_ID(UNK_19);
s32 E_ID(UNK_1A);
s32 E_ID(CORNER_GUARD_ATTACK);
s32 E_ID(UNK_1C);
s32 E_ID(UNK_1D);
s32 E_ID(UNK_1E);
s32 E_ID(UNK_1F);
s32 E_ID(UNK_20);
s32 E_ID(UNK_21);
s32 E_ID(BREAKABLE_FLOOR_SECRET);
s32 E_ID(BREAKABLE_DEBRIS);
s32 E_ID(BACKGROUND_DOOR_RUBBLE);
s32 E_ID(FOUNTAIN_WATER);
s32 E_ID(BOSS_TORCH);
s32 E_ID(BOSS_DOORS);
s32 E_ID(UNK_28);
s32 E_ID(UNK_29);
s32 E_ID(UNK_2A);

void InitEntityIds(void) {
    E_ID(BACKGROUND_BLOCK) = 0x11;
    E_ID(LOCK_CAMERA) = 0x12;
    E_ID(UNK_ID13) = 0x13;
    E_ID(EXPLOSION_VARIANTS) = 0x14;
    E_ID(GREY_PUFF) = 0x15;
    E_ID(UNK_16) = 0x16;
    E_ID(UNK_17) = 0x17;
    E_ID(UNK_18) = 0x18;
    E_ID(UNK_19) = 0x19;
    E_ID(UNK_1A) = 0x1A;
    E_ID(CORNER_GUARD_ATTACK) = 0x1B;
    E_ID(UNK_1C) = 0x1C;
    E_ID(UNK_1D) = 0x1D;
    E_ID(UNK_1E) = 0x1E;
    E_ID(UNK_1F) = 0x1F;
    E_ID(UNK_20) = 0x20;
    E_ID(UNK_21) = 0x21;
    E_ID(BREAKABLE_FLOOR_SECRET) = 0x22;
    E_ID(BREAKABLE_DEBRIS) = 0x23;
    E_ID(BACKGROUND_DOOR_RUBBLE) = 0x24;
    E_ID(FOUNTAIN_WATER) = 0x25;
    E_ID(BOSS_TORCH) = 0x26;
    E_ID(BOSS_DOORS) = 0x27;
    E_ID(UNK_28) = 0x28;
    E_ID(UNK_29) = 0x29;
    E_ID(UNK_2A) = 0x2A;
}

void OVL_EXPORT(Load)(void) {
    InitEntityIds();
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = &D_8D2E0FC;
    g_pStObjLayoutVertical = &D_8D2E1D0;
    func_892A018();
    memcpy(&g_api.o, &OVL_EXPORT(Overlay), sizeof(Overlay));
}
