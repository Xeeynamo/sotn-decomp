// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../wrp/wrp.h"
#include "../pfn_entity_update.h"

// entity table to allocate new entities
extern PfnEntityUpdate* D_08C6BC30;

extern LayoutEntity* D_8D2DE7C;
extern LayoutEntity* D_8D2DF50;

// entity table to allocate new entities
extern PfnEntityUpdate D_psp_09246E30[];
extern Overlay g_StageOverlay;
extern s32 D_psp_0924BC90;
extern s32 D_psp_0924BC98;
extern s32 D_psp_0924BCA0;
extern s32 D_psp_0924BCA8;
extern s32 D_psp_0924BCB0;
extern s32 D_psp_0924BCB8;
extern s32 D_psp_0924BCC0;

void func_psp_09244760(void) {
    D_psp_0924BCC0 = 0x11;
    D_psp_0924BCB8 = 0x12;
    D_psp_0924BCB0 = 0x13;
    D_psp_0924BCA8 = 0x14;
    D_psp_0924BCA0 = 0x15;
    D_psp_0924BC98 = 0x16;
    D_psp_0924BC90 = 0x17;
}

void func_psp_092447C0(void) {
    func_psp_09244760();
    D_08C6BC30 = (PfnEntityUpdate*)&D_psp_09246E30;
    g_pStObjLayoutHorizontal = &D_8D2DE7C;
    g_pStObjLayoutVertical = &D_8D2DF50;
    func_892A018();
    memcpy((u8*)&g_api, (u8*)&g_StageOverlay, sizeof(Overlay));
}
