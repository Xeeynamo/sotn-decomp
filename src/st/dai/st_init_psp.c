// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dai/dai.h"

#include "../pfn_entity_update.h"

extern LayoutEntity* D_8D2E2B0;
extern LayoutEntity* D_8D2E384;

extern Overlay OVL_EXPORT(Overlay);

extern char OVL_EXPORT(cutscene_script_en)[];
extern char OVL_EXPORT(cutscene_script_fr)[];
extern char OVL_EXPORT(cutscene_script_sp)[];
extern char OVL_EXPORT(cutscene_script_ge)[];
extern char OVL_EXPORT(cutscene_script_it)[];

u8* OVL_EXPORT(cutscene_script); // bss
u8* D_pspeu_092970B8;            // bss

#include "../get_lang_at.h"

extern s32 D_pspeu_092970C8;
extern s32 D_pspeu_092970D0;
extern s32 D_pspeu_092970D8;
extern s32 D_pspeu_092970E0;
extern s32 D_pspeu_092970E8;
extern s32 D_pspeu_092970F0;
extern s32 D_pspeu_092970F8;
extern s32 D_pspeu_09297100;
extern s32 D_pspeu_09297108;
extern s32 D_pspeu_09297110;
extern s32 D_pspeu_09297118;
extern s32 D_pspeu_09297120;
extern s32 D_pspeu_09297128;
extern s32 D_pspeu_09297130;
extern s32 D_pspeu_09297138;
extern s32 D_pspeu_09297140;
extern s32 D_pspeu_09297148;
extern s32 D_pspeu_09297150;
extern s32 D_pspeu_09297158;
extern s32 D_pspeu_09297160;
extern s32 D_pspeu_09297168;
extern s32 D_pspeu_09297170;
extern s32 D_pspeu_09297178;
extern s32 D_pspeu_09297180;
extern s32 D_pspeu_09297188;
extern s32 D_pspeu_09297190;
extern s32 D_pspeu_09297198;
extern s32 D_pspeu_092971A0;
extern s32 D_pspeu_092971A8;
extern s32 D_pspeu_092971B0;
extern s32 D_pspeu_092971B8;
extern s32 D_pspeu_092971C0;
extern s32 D_pspeu_092971C8;
extern s32 D_pspeu_092971D0;
extern s32 D_pspeu_092971D8;
extern s32 D_pspeu_092971E0;
extern s32 D_pspeu_092971E8;
extern s32 D_pspeu_092971F0;
extern s32 D_pspeu_092971F8;
extern s32 D_pspeu_09297200;
extern s32 D_pspeu_09297208;
extern s32 D_pspeu_09297210;
extern s32 D_pspeu_09297218;
extern s32 D_pspeu_09297220;
extern s32 D_pspeu_09297228;
extern s32 D_pspeu_09297230;
extern s32 D_pspeu_09297238;
extern s32 D_pspeu_09297240;
extern s32 D_pspeu_09297248;
extern s32 D_pspeu_09297250;
extern s32 D_pspeu_09297258;
extern s32 D_pspeu_09297260;
extern s32 D_pspeu_09297268;
extern s32 D_pspeu_09297270;
extern s32 D_pspeu_09297278;
extern s32 D_pspeu_09297280;

void InitEntityIds(void) {
    D_pspeu_09297280 = 0x11;
    D_pspeu_09297278 = 0x12;
    D_pspeu_09297270 = 0x13;
    D_pspeu_09297268 = 0x14;
    D_pspeu_09297260 = 0x15;
    D_pspeu_09297258 = 0x16;
    D_pspeu_09297250 = 0x17;
    D_pspeu_09297248 = 0x18;
    D_pspeu_09297240 = 0x19;
    D_pspeu_09297238 = 0x1A;
    D_pspeu_09297230 = 0x1B;
    D_pspeu_09297228 = 0x1C;
    D_pspeu_09297220 = 0x1D;
    D_pspeu_09297218 = 0x1E;
    D_pspeu_09297210 = 0x1F;
    D_pspeu_09297208 = 0x20;
    D_pspeu_09297200 = 0x21;
    D_pspeu_092971F8 = 0x22;
    D_pspeu_092971F0 = 0x23;
    D_pspeu_092971E8 = 0x24;
    D_pspeu_092971E0 = 0x25;
    D_pspeu_092971D8 = 0x26;
    D_pspeu_092971D0 = 0x27;
    D_pspeu_092971C8 = 0x28;
    D_pspeu_092971C0 = 0x29;
    D_pspeu_092971B8 = 0x2A;
    D_pspeu_092971B0 = 0x2B;
    D_pspeu_092971A8 = 0x2C;
    D_pspeu_092971A0 = 0x2D;
    D_pspeu_09297198 = 0x2E;
    D_pspeu_09297190 = 0x2F;
    D_pspeu_09297188 = 0x30;
    D_pspeu_09297180 = 0x31;
    D_pspeu_09297178 = 0x32;
    D_pspeu_09297170 = 0x33;
    D_pspeu_09297168 = 0x34;
    D_pspeu_09297160 = 0x35;
    D_pspeu_09297158 = 0x36;
    D_pspeu_09297150 = 0x37;
    D_pspeu_09297148 = 0x38;
    D_pspeu_09297140 = 0x39;
    D_pspeu_09297138 = 0x3A;
    D_pspeu_09297130 = 0x3B;
    D_pspeu_09297128 = 0x3C;
    D_pspeu_09297120 = 0x3D;
    D_pspeu_09297118 = 0x3E;
    D_pspeu_09297110 = 0x3F;
    D_pspeu_09297108 = 0x40;
    D_pspeu_09297100 = 0x41;
    D_pspeu_092970F8 = 0x42;
    D_pspeu_092970F0 = 0x43;
    D_pspeu_092970E8 = 0x44;
    D_pspeu_092970E0 = 0x45;
    D_pspeu_092970D8 = 0x46;
    D_pspeu_092970D0 = 0x47;
    D_pspeu_092970C8 = 0x48;
}

void OVL_EXPORT(Load)(void) {
    OVL_EXPORT(cutscene_script) = GetLangAt(
        0, (u8*)OVL_EXPORT(cutscene_script_en),
        (u8*)OVL_EXPORT(cutscene_script_fr),
        (u8*)OVL_EXPORT(cutscene_script_sp),
        (u8*)OVL_EXPORT(cutscene_script_ge),
        (u8*)OVL_EXPORT(cutscene_script_it));
    D_pspeu_092970B8 = GetLangAt(
        0, (u8*)OVL_EXPORT(cutscene_script_en),
        (u8*)OVL_EXPORT(cutscene_script_fr),
        (u8*)OVL_EXPORT(cutscene_script_sp),
        (u8*)OVL_EXPORT(cutscene_script_ge),
        (u8*)OVL_EXPORT(cutscene_script_it));
    InitEntityIds();
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = &D_8D2E2B0;
    g_pStObjLayoutVertical = &D_8D2E384;
    func_892A018();
    memcpy(&g_api, &OVL_EXPORT(Overlay), 0x40U);
}
