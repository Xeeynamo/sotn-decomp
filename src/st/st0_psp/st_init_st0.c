// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../st0/st0.h"
#include "../pfn_entity_update.h"

extern LayoutEntity* D_8D2DF54;
extern LayoutEntity* D_8D2E028;

extern Overlay OVL_EXPORT(Overlay);

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
s32 E_ID(DRACULA_UNK1B);
s32 E_ID(DRACULA_UNK1C);
s32 E_ID(DRACULA_UNK1D);
s32 E_ID(DRACULA_METEOR);
s32 E_ID(DRACULA_UNK1F);
s32 E_ID(DRACULA_UNK20);
s32 E_ID(DRACULA_UNK21);
s32 E_ID(DRACULA_FIREBALL);
s32 E_ID(DRACULA_UNK23);
s32 E_ID(ID_24);
s32 E_ID(ID_25);
s32 E_ID(ID_26);
s32 E_ID(ID_27);
s32 E_ID(SECRET_BUTTON);
s32 E_ID(SECRET_STAIRS);
s32 E_ID(ID_2A);
s32 E_ID(DRACULA_UNK2B);
s32 E_ID(DRACULA_UNK2C);
s32 E_ID(ID_2D);
s32 E_ID(DRACULA_UNK2E);

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
    E_ID(DRACULA_UNK1B) = 0x1B;    // EntityDracula
    E_ID(DRACULA_UNK1C) = 0x1C;    // EntityDracula
    E_ID(DRACULA_UNK1D) = 0x1D;    // EntityDracula
    E_ID(DRACULA_METEOR) = 0x1E;   // EntityDraculaMeteorball
    E_ID(DRACULA_UNK1F) = 0x1F;    // EntityDraculaGlass
    E_ID(DRACULA_UNK20) = 0x20;    // EntityDraculaFinalForm
    E_ID(DRACULA_UNK21) = 0x21;    // EntityDraculaFinalForm
    E_ID(DRACULA_FIREBALL) = 0x22; // EntityDraculaRainAttack
    E_ID(DRACULA_UNK23) = 0x23;
    E_ID(ID_24) = 0x24;
    E_ID(ID_25) = 0x25;
    E_ID(ID_26) = 0x26;
    E_ID(ID_27) = 0x27;
    E_ID(SECRET_BUTTON) = 0x28;
    E_ID(SECRET_STAIRS) = 0x29;
    E_ID(ID_2A) = 0x2A;
    E_ID(DRACULA_UNK2B) = 0x2B; // EntityDracula
    E_ID(DRACULA_UNK2C) = 0x2C; // EntityDraculaFinalForm
    E_ID(ID_2D) = 0x2D;         // EntityCutscenePhotograph
    E_ID(DRACULA_UNK2E) = 0x2E; // EntityDraculaFinalForm
}

void OVL_EXPORT(Load)(void) {
    InitEntityIds();
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
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
    func_91040A0(D_pspeu_0925D660);
    func_91040A0(D_pspeu_0925D678);
    func_91040A0(D_pspeu_0925D690);
    func_91040A0(D_pspeu_0925D6A8);
}
