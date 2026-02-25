// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../nz0/nz0.h"
#include "../pfn_entity_update.h"

extern LayoutEntity* D_8D2E52C;
extern LayoutEntity* D_8D2E600;

extern Overlay OVL_EXPORT(Overlay);

extern u8 D_pspeu_092658B8[];
extern u8 D_pspeu_09265A98[];
extern u8 D_pspeu_09265CA0[];
extern u8 D_pspeu_09265E90[];
extern u8 D_pspeu_092660B0[];

extern u8* OVL_EXPORT(cutscene_text_offset);
extern u8* OVL_EXPORT(cutscene_data);

s32 E_ID(ID_11);
s32 E_ID(ID_12);
s32 E_ID(ID_13);
s32 E_ID(ID_14);
s32 E_ID(ID_15);
s32 E_ID(ID_16);
s32 E_ID(ID_17);
s32 E_ID(ID_18);
s32 E_ID(ID_19);
s32 E_ID(ID_1A);
s32 E_ID(ID_1B);
s32 E_ID(ID_1C);
s32 E_ID(ID_1D);
s32 E_ID(CANNON_SHOT);
s32 E_ID(ID_1F);
s32 E_ID(ID_20);
s32 E_ID(ID_21);
s32 E_ID(WALL_DEBRIS);
s32 E_ID(ID_23);
s32 E_ID(ID_24);
s32 E_ID(ID_25);
s32 E_ID(BLOOD_SKELETON);
s32 E_ID(ID_27);
s32 E_ID(ID_28);
s32 E_ID(ID_29);
s32 E_ID(ID_2A);
s32 E_ID(ID_2B);
s32 E_ID(ID_2C);
s32 E_ID(ID_2D);
s32 E_ID(ID_2E);
s32 E_ID(ID_2F);
s32 E_ID(ID_30);
s32 E_ID(ID_31);
s32 E_ID(ID_32);
s32 E_ID(ID_33);
s32 E_ID(ID_34);
s32 E_ID(ID_35);
s32 E_ID(ID_36);
s32 E_ID(RELIC_CONTAINER);
s32 E_ID(EXPLODE_PUFF_OPAQUE);
s32 E_ID(ID_39);
s32 E_ID(ID_3A);
s32 E_ID(ID_3B);
s32 E_ID(ID_3C);
s32 E_ID(ID_3D);
s32 E_ID(ID_3E);
s32 E_ID(BOSS_ROOM_BLOCK);
s32 E_ID(SLOGRA);
s32 E_ID(SLOGRA_SPEAR);
s32 E_ID(SLOGRA_SPEAR_PROJECTILE);
s32 E_ID(GAIBON);
s32 E_ID(GAIBON_LEG);
s32 E_ID(GAIBON_SMALL_FIREBALL);
s32 E_ID(GAIBON_BIG_FIREBALL);
s32 E_ID(ID_47);
s32 E_ID(ID_48);
s32 E_ID(LIFE_UP_SPAWN);
s32 E_ID(ID_4A);
s32 E_ID(ID_4B);
s32 E_ID(ID_4C);
s32 E_ID(ID_4D);

#include "../get_lang_at.h"

void InitEntityIds(void) {
    E_ID(ID_11) = 0x11;
    E_ID(ID_12) = 0x12;
    E_ID(ID_13) = 0x13;
    E_ID(ID_14) = 0x14;
    E_ID(ID_15) = 0x15;
    E_ID(ID_16) = 0x16;
    E_ID(ID_17) = 0x17;
    E_ID(ID_18) = 0x18;
    E_ID(ID_19) = 0x19;
    E_ID(ID_1A) = 0x1A;
    E_ID(ID_1B) = 0x1B;
    E_ID(ID_1C) = 0x1C;
    E_ID(ID_1D) = 0x1D;
    E_ID(CANNON_SHOT) = 0x1E;
    E_ID(ID_1F) = 0x1F;
    E_ID(ID_20) = 0x20;
    E_ID(ID_21) = 0x21;
    E_ID(WALL_DEBRIS) = 0x22;
    E_ID(ID_23) = 0x23;
    E_ID(ID_24) = 0x24;
    E_ID(ID_25) = 0x25;
    E_ID(BLOOD_SKELETON) = 0x26;
    E_ID(ID_27) = 0x27;
    E_ID(ID_28) = 0x28;
    E_ID(ID_29) = 0x29;
    E_ID(ID_2A) = 0x2A;
    E_ID(ID_2B) = 0x2B;
    E_ID(ID_2C) = 0x2C;
    E_ID(ID_2D) = 0x2D;
    E_ID(ID_2E) = 0x2E;
    E_ID(ID_2F) = 0x2F;
    E_ID(ID_30) = 0x30;
    E_ID(ID_31) = 0x31;
    E_ID(ID_32) = 0x32;
    E_ID(ID_33) = 0x33;
    E_ID(ID_34) = 0x34;
    E_ID(ID_35) = 0x35;
    E_ID(ID_36) = 0x36;
    E_ID(RELIC_CONTAINER) = 0x37;
    E_ID(EXPLODE_PUFF_OPAQUE) = 0x38;
    E_ID(ID_39) = 0x39;
    E_ID(ID_3A) = 0x3A;
    E_ID(ID_3B) = 0x3B;
    E_ID(ID_3C) = 0x3C;
    E_ID(ID_3D) = 0x3D;
    E_ID(ID_3E) = 0x3E;
    E_ID(BOSS_ROOM_BLOCK) = 0x3F;
    E_ID(SLOGRA) = 0x40;
    E_ID(SLOGRA_SPEAR) = 0x41;
    E_ID(SLOGRA_SPEAR_PROJECTILE) = 0x42;
    E_ID(GAIBON) = 0x43;
    E_ID(GAIBON_LEG) = 0x44;
    E_ID(GAIBON_SMALL_FIREBALL) = 0x45;
    E_ID(GAIBON_BIG_FIREBALL) = 0x46;
    E_ID(ID_47) = 0x47;
    E_ID(ID_48) = 0x48;
    E_ID(LIFE_UP_SPAWN) = 0x49;
    E_ID(ID_4A) = 0x4A;
    E_ID(ID_4B) = 0x4B;
    E_ID(ID_4C) = 0x4C;
    E_ID(ID_4D) = 0x4D;
}

void OVL_EXPORT(Load)(void) {
    OVL_EXPORT(cutscene_data) = GetLangAt(
        0, (u8*)D_pspeu_092660B0, (u8*)D_pspeu_09265CA0, (u8*)D_pspeu_09265A98,
        (u8*)D_pspeu_09265E90, (u8*)D_pspeu_092658B8);
    OVL_EXPORT(cutscene_text_offset) = GetLangAt(
        0, (u8*)D_pspeu_092660B0, (u8*)D_pspeu_09265CA0, (u8*)D_pspeu_09265A98,
        (u8*)D_pspeu_09265E90, (u8*)D_pspeu_092658B8);

    InitEntityIds();
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = &D_8D2E52C;
    g_pStObjLayoutVertical = &D_8D2E600;
    func_892A018();
    memcpy(&g_api.o, &OVL_EXPORT(Overlay), sizeof(Overlay));
}
