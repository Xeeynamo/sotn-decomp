// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../sel/sel.h"

extern Overlay OVL_EXPORT(Overlay);

extern u8 D_psp_0924A470[];
extern u8 D_psp_0924AD10[];
extern u8 D_psp_0924B590[];
extern u8 D_psp_0924BE90[];
extern u8 D_psp_0924C7B0[];
extern u8 D_psp_0924CF90[];
extern u8 D_psp_0924D4F0[];
extern u8 D_psp_0924DA50[];
extern u8 D_psp_0924DFB0[];
extern u8 D_psp_0924E510[];

// BSS
u8* D_psp_09285BA8;
u8* D_psp_09285BA0;
u8* D_psp_09285B98;
u8* D_psp_09285B90;
u8* D_psp_09285B88;
u8* D_psp_09285B80;

s32 D_psp_0924EA70 = 0x08D39D3C;

static u16 D_psp_0924EA78[] = {
#include "gen/D_psp_0924EA78.h"
};

static u8 D_psp_0924EA98[] = {
#include "gen/D_psp_0924EA98.h"
};

s32 D_psp_0924F800 = 0xE;

s32 D_psp_0924F808 = 0x1D;

static u16 D_psp_0924F810[] = {
#include "gen/D_psp_0924F810.h"
};

static u8 D_psp_0924F850[] = {
#include "gen/D_psp_0924F850.h"
};

static u8 D_psp_09253850[] = {
#include "gen/D_psp_09253850.h"
};

static u8 D_psp_09257850[] = {
#include "gen/D_psp_09257850.h"
};

static u8 D_psp_0925B850[] = {
#include "gen/D_psp_0925B850.h"
};

static u16 D_psp_0925F850[] = {
#include "gen/D_psp_0925F850.h"
};

static u8 D_psp_0925FA50[] = {
#include "gen/D_psp_0925FA50.h"
};

static u8 D_psp_09260550[] = {
#include "gen/D_psp_09260550.h"
};

static u8 D_psp_09261030[] = {
#include "gen/D_psp_09261030.h"
};

static u8 D_psp_09261AF8[] = {
#include "gen/D_psp_09261AF8.h"
};

static u8 D_psp_09262618[] = {
#include "gen/D_psp_09262618.h"
};

static u8 D_psp_092630D8[] = {
#include "gen/D_psp_092630D8.h"
};

static u8 D_psp_09263700[] = {
#include "gen/D_psp_09263700.h"
};

static u8 D_psp_09263CE0[] = {
#include "gen/D_psp_09263CE0.h"
};

static u8 D_psp_09264290[] = {
#include "gen/D_psp_09264290.h"
};

static u8 D_psp_09264868[] = {
#include "gen/D_psp_09264868.h"
};

static u8 D_psp_09264E90[] = {
#include "gen/D_psp_09264E90.h"
};

static u8 D_psp_09266578[] = {
#include "gen/D_psp_09266578.h"
};

static u8 D_psp_09267B08[] = {
#include "gen/D_psp_09267B08.h"
};

static u8 D_psp_09269440[] = {
#include "gen/D_psp_09269440.h"
};

static u8 D_psp_0926A9E8[] = {
#include "gen/D_psp_0926A9E8.h"
};

static u8 D_psp_0926BFB0[] = {
#include "gen/D_psp_0926BFB0.h"
};

static u8 D_psp_0926D980[] = {
#include "gen/D_psp_0926D980.h"
};

static u8 D_psp_0926F188[] = {
#include "gen/D_psp_0926F188.h"
};

static u8 D_psp_09270758[] = {
#include "gen/D_psp_09270758.h"
};

static u8 D_psp_09272158[] = {
#include "gen/D_psp_09272158.h"
};

static u8 D_psp_092738F8[] = {
#include "gen/D_psp_092738F8.h"
};

static u8 D_psp_09274EC8[] = {
#include "gen/D_psp_09274EC8.h"
};

static u8 D_psp_092767E0[] = {
#include "gen/D_psp_092767E0.h"
};

static u8 D_psp_09277F88[] = {
#include "gen/D_psp_09277F88.h"
};

static u8 D_psp_09279558[] = {
#include "gen/D_psp_09279558.h"
};

static u8 D_psp_0927AF10[] = {
#include "gen/D_psp_0927AF10.h"
};

static u_long* D_psp_0927C6F0[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x3C0, 128, 128, D_psp_092630D8),
    GFX_TERMINATE(),
};

static u_long* D_psp_0927C708[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x1C0, 128, 128, D_psp_09266578),
    GFX_TERMINATE(),
};

static u_long* D_psp_0927C720[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x1E0, 128, 128, D_psp_09264E90),
    GFX_TERMINATE(),
};

static u_long* D_psp_0927C738[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x180, 0x1C0, 128, 128, D_psp_09267B08),
    GFX_TERMINATE(),
};

static u_long* D_psp_0927C750[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x180, 0x1E0, 128, 128, D_psp_09269440),
    GFX_TERMINATE(),
};

static u_long* D_psp_0927C768[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x80, 0x320, 128, 128, D_psp_09269440),
    GFX_TERMINATE(),
};

static u_long* D_psp_0927C780[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0, 0x300, 128, 128, D_psp_09266578),
    GFX_TERMINATE(),
};

static u_long* D_psp_0927C798[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x80, 0x300, 128, 128, D_psp_09267B08),
    GFX_TERMINATE(),
};

static u_long* D_psp_0927C7B0[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x340, 128, 128, D_psp_0924EA98),
    GFX_TERMINATE(),
};

static u_long* D_psp_0927C7C8[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x380, 128, 128, D_psp_0924EA98),
    GFX_TERMINATE(),
};

static u_long* D_psp_0927C7E0[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x180, 0x220, 128, 128, D_psp_0925FA50),
    GFX_TERMINATE(),
};

#include "../get_lang_at.h"

#include "../../get_lang.h"

void OVL_EXPORT(Load)(void) {
    D_psp_09285BA8 = GetLangAt(8, D_psp_0924C7B0, D_psp_0924B590,
                               D_psp_0924AD10, D_psp_0924BE90, D_psp_0924A470);
    D_psp_09285BA0 = GetLangAt(0, D_psp_0924C7B0, D_psp_0924B590,
                               D_psp_0924AD10, D_psp_0924BE90, D_psp_0924A470);
    D_psp_09285B98 = GetLangAt(0, D_psp_0924E510, D_psp_0924DA50,
                               D_psp_0924D4F0, D_psp_0924DFB0, D_psp_0924CF90);
    D_psp_09285B90 = GetLangAt(0, D_psp_0924E510, D_psp_0924DA50,
                               D_psp_0924D4F0, D_psp_0924DFB0, D_psp_0924CF90);
    D_psp_09285B88 = GetLangAt(0, D_psp_0924C7B0, D_psp_0924B590,
                               D_psp_0924AD10, D_psp_0924BE90, D_psp_0924A470);
    D_psp_09285B80 = GetLangAt(4, D_psp_0924C7B0, D_psp_0924B590,
                               D_psp_0924AD10, D_psp_0924BE90, D_psp_0924A470);
    func_8929FA8(D_psp_0924EA70, 0xC5);
    memcpy(&g_api.o, &OVL_EXPORT(Overlay), sizeof(Overlay));
    D_psp_0927C6F0[3] =
        (u_long*)GetLang(D_psp_092630D8, D_psp_09264868, D_psp_09263700,
                         D_psp_09264290, D_psp_09263CE0);
    func_892667C(0x8020, D_psp_0924EA78);
    func_91040A0(D_psp_0927C6F0);
    D_psp_0927C708[3] =
        (u_long*)GetLang(D_psp_09266578, D_psp_092738F8, D_psp_0926A9E8,
                         D_psp_09277F88, D_psp_0926F188);
    D_psp_0927C738[3] =
        (u_long*)GetLang(D_psp_09267B08, D_psp_09274EC8, D_psp_0926BFB0,
                         D_psp_09279558, D_psp_09270758);
    D_psp_0927C750[3] =
        (u_long*)GetLang(D_psp_09269440, D_psp_092767E0, D_psp_0926D980,
                         D_psp_0927AF10, D_psp_09272158);
    D_psp_0927C768[3] =
        (u_long*)GetLang(D_psp_09269440, D_psp_092767E0, D_psp_0926D980,
                         D_psp_0927AF10, D_psp_09272158);
    D_psp_0927C780[3] =
        (u_long*)GetLang(D_psp_09266578, D_psp_092738F8, D_psp_0926A9E8,
                         D_psp_09277F88, D_psp_0926F188);
    D_psp_0927C798[3] =
        (u_long*)GetLang(D_psp_09267B08, D_psp_09274EC8, D_psp_0926BFB0,
                         D_psp_09279558, D_psp_09270758);
    func_91040A0(D_psp_0927C708);
    func_91040A0(D_psp_0927C720);
    func_91040A0(D_psp_0927C738);
    func_91040A0(D_psp_0927C750);
    func_91040A0(D_psp_0927C768);
    func_91040A0(D_psp_0927C780);
    func_91040A0(D_psp_0927C798);
}

void func_psp_09237C38(void) {
    func_91040A0(D_psp_0927C7B0);
    func_892667C(0x8196, D_psp_0924F810);
}

void func_psp_09237C78(void) {
    func_91040A0(D_psp_0927C7C8);
    func_892667C(0x8196, D_psp_0924F810);
}

void func_psp_09237CB8(void) {
    RECT rect;
    s32 height = 0x80;

    func_89264CC(0x8000, &D_psp_0925F850, 1);
    rect.x = D_psp_0924F800 << 6;
    rect.y = 0;
    rect.w = 0x40;
    rect.h = height;
    LoadImage(&rect, (u_long*)D_psp_0924F850);
    rect.x = (D_psp_0924F800 + 1) << 6;
    rect.y = 0;
    rect.w = 0x40;
    rect.h = height;
    LoadImage(&rect, (u_long*)D_psp_09253850);
    rect.x = D_psp_0924F808 << 6;
    rect.y = 0;
    rect.w = 0x40;
    rect.h = height;
    LoadImage(&rect, (u_long*)D_psp_09257850);
    rect.x = (D_psp_0924F808 + 1) << 6;
    rect.y = 0;
    rect.w = 0x40;
    rect.h = height;
    LoadImage(&rect, (u_long*)D_psp_0925B850);
    D_psp_0927C7E0[3] =
        (u_long*)GetLang(D_psp_0925FA50, D_psp_09262618, D_psp_09260550,
                         D_psp_09261AF8, D_psp_09261030);
    func_91040A0(D_psp_0927C7E0);
}
