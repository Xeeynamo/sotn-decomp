// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../st0/st0.h"
#include "../pfn_entity_update.h"

extern LayoutEntity* D_8D2DF54;
extern LayoutEntity* D_8D2E028;

extern Overlay OVL_EXPORT(Overlay);

s32 E_ID(BACKGROUND_BLOCK);
s32 E_ID(LOCK_CAMERA);
s32 E_ID(ID_13);
s32 E_ID(EXPLOSION_VARIANTS);
s32 E_ID(GREY_PUFF);
s32 E_ID(CUTSCENE);
s32 E_ID(CUTSCENE_SUPPORT);
s32 E_ID(STAGE_TITLE_CARD);
s32 E_ID(STAGE_TITLE_FADEOUT);
s32 E_ID(DRACULA);
s32 E_ID(DRACULA_FIREBALL);
s32 E_ID(DRACULA_METEORBALL);
s32 E_ID(DRACULA_BODY);
s32 E_ID(ID_1E);
s32 E_ID(DRACULA_GLASS);
s32 E_ID(DRACULA_FINAL_FORM);
s32 E_ID(DRACULA_MEGA_FIREBALL);
s32 E_ID(DRACULA_RAIN_ATTACK);
s32 E_ID(DEMATERIALIZE_STAGE_BG);
s32 E_ID(BACKGROUND_VORTEX);
s32 E_ID(BACKGROUND_CLOUDS);
s32 E_ID(ID_26);
s32 E_ID(SCRET_STAIRS_CEILING);
s32 E_ID(SECRET_BUTTON);
s32 E_ID(SECRET_STAIRS);
s32 E_ID(CLOCK_TOWER_3D);
s32 E_ID(ID_2B);
s32 E_ID(PHOTOGRAPH);
s32 E_ID(PHOTOGRAPH_FIRE);
s32 E_ID(ID_2E);

void InitEntityIds(void) {
    E_ID(BACKGROUND_BLOCK) = 0x11;
    E_ID(LOCK_CAMERA) = 0x12;
    E_ID(ID_13) = 0x13;
    E_ID(EXPLOSION_VARIANTS) = 0x14;
    E_ID(GREY_PUFF) = 0x15;
    E_ID(CUTSCENE) = 0x16;
    E_ID(CUTSCENE_SUPPORT) = 0x17;
    E_ID(STAGE_TITLE_CARD) = 0x18;
    E_ID(STAGE_TITLE_FADEOUT) = 0x19;
    E_ID(DRACULA) = 0x1A;
    E_ID(DRACULA_FIREBALL) = 0x1B;
    E_ID(DRACULA_METEORBALL) = 0x1C;
    E_ID(DRACULA_BODY) = 0x1D;
    E_ID(ID_1E) = 0x1E;
    E_ID(DRACULA_GLASS) = 0x1F;
    E_ID(DRACULA_FINAL_FORM) = 0x20;
    E_ID(DRACULA_MEGA_FIREBALL) = 0x21;
    E_ID(DRACULA_RAIN_ATTACK) = 0x22;
    E_ID(DEMATERIALIZE_STAGE_BG) = 0x23;
    E_ID(BACKGROUND_VORTEX) = 0x24;
    E_ID(BACKGROUND_CLOUDS) = 0x25;
    E_ID(ID_26) = 0x26;
    E_ID(SCRET_STAIRS_CEILING) = 0x27;
    E_ID(SECRET_BUTTON) = 0x28;
    E_ID(SECRET_STAIRS) = 0x29;
    E_ID(CLOCK_TOWER_3D) = 0x2A;
    E_ID(ID_2B) = 0x2B;
    E_ID(PHOTOGRAPH) = 0x2C;
    E_ID(PHOTOGRAPH_FIRE) = 0x2D;
    E_ID(ID_2E) = 0x2E;
}

void OVL_EXPORT(Load)(void) {
    InitEntityIds();
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = &D_8D2DF54;
    g_pStObjLayoutVertical = &D_8D2E028;
    func_psp_0892A018();
    memcpy(&g_api.o, &OVL_EXPORT(Overlay), sizeof(Overlay));
}

extern u_long* D_pspeu_0925D660[];
extern u_long* D_pspeu_0925D678[];
extern u_long* D_pspeu_0925D690[];
extern u_long* D_pspeu_0925D6A8[];

void func_pspeu_09246B88(void) {
    func_psp_091040A0(D_pspeu_0925D660);
    func_psp_091040A0(D_pspeu_0925D678);
    func_psp_091040A0(D_pspeu_0925D690);
    func_psp_091040A0(D_pspeu_0925D6A8);
}
