// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

u16 D_800A37D8[] = {0x8430, 0x843F};
u16 D_psp_09189DE8[] = {0x8000, 0x8000, 0x8000, 0x8000};

u16 D_psp_09189DF0[] = {0x8430, 0x843F, 0xD5CE, 0xE739};
u16 D_psp_09189DF8[] = {0xBEBB, 0xFFFF, 0x8594, 0x873F};
u16 D_psp_09189E00[] = {0x994A, 0xA5CE, 0x8421, 0x9CE7};
u16 D_psp_09189E08[] = {0x8420, 0x8427, 0x8421, 0x9CE7};
u16 D_psp_09189E10[] = {0xA4A8, 0xAD0A, 0xCC21, 0xFC42};
u16 D_psp_09189E18[] = {0x910C, 0x996E, 0x8048, 0x80B2};
u16 D_psp_09189E20[] = {0x90A1, 0x9102, 0xA821, 0xCC42};
u16 D_psp_09189E28[] = {0x90C9, 0x94EB, 0x85E4, 0xA2CD};
u16 D_psp_09189E30[] = {0x842C, 0x8C6F, 0x8018, 0x98DD};
u16 D_psp_09189E38[] = {0x994A, 0xA5CE, 0x0000, 0xBC0F};
u16 D_psp_09189E40[] = {0x8433, 0x843A, 0x0000, 0x0000, 0x0000, 0x0000, 0xCC21, 0xFC42, 0xA4A8, 0xAD0A};

u_long* D_psp_09189E58[] = {GFX_TERMINATE()};

u8 D_psp_09189E60[] = {
#include "../dra/gen_D_psp_09189E60.h"
};

u8 D_psp_0918A690[] = {
#include "../dra/gen_D_psp_0918A690.h"
};

u8 D_psp_0918ABA8[] = {
#include "../dra/gen_D_psp_0918ABA8.h"
};

u8 D_psp_0918B1A0[] = {
#include "../dra/gen_D_psp_0918B1A0.h"
};

extern u8 D_psp_09162D88[];

u_long* D_psp_0918B830[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x320, 128, 128, D_psp_09162D88),
    GFX_TERMINATE(),
};

u_long* D_psp_0918B848[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x320, 128, 128, D_psp_0918B1A0),
    GFX_TERMINATE(),
};

u_long* D_psp_0918B860[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x320, 128, 128, D_psp_0918A690),
    GFX_TERMINATE(),
};

u_long* D_psp_0918B878[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x320, 128, 128, D_psp_0918ABA8),
    GFX_TERMINATE(),
};

u_long* D_psp_0918B890[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x320, 128, 128, D_psp_09189E60),
    GFX_TERMINATE(),
};

extern u8 D_psp_09166F20[];
extern u8 D_psp_09166A90[];

u_long* D_psp_0918B8A8[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x320, 128, 128, D_psp_09166F20),
    GFX_ENTRY(0x170, 0x3E0, 16, 80, D_psp_09166A90),
    GFX_TERMINATE(),
};

extern u8 D_psp_09165CC0[];
extern u8 D_psp_09166CF0[];

u_long* D_psp_0918B8C8[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x320, 128, 128, D_psp_09165CC0),
    GFX_ENTRY(0x170, 0x3E0, 16, 80, D_psp_09166CF0),
    GFX_TERMINATE(),
};

u16 D_psp_0918B8E8[] = {
    0x0000, 0xA108, 0xC210, 0xCA92, 0xD294, 0xDF97, 0xE739, 0xF39C,
    0xFBDE, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

u_long* D_psp_0918B908[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x1A10, D_psp_0918B8E8),
    PAL_TERMINATE(),
};

u_long* D_psp_0918B920[] = {
    MAKE_PAL_OP(PAL_GLOW_ANIM, 6),
    PAL_GLOW_INFO(0x1721, 1),
    PAL_GLOW_DATA(&D_psp_09189DF0[0]),
    PAL_GLOW_DATA(&D_psp_09189DF0[1]),
    PAL_TERMINATE(),
};

u_long* D_psp_0918B938[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA_(0x171E, &D_psp_09189DF0[2], 2),
};

u_long* D_psp_0918B948[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA_(0x171E, &D_psp_09189DF8[0], 2),
};

u_long* D_psp_0918B958[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA_(0x171E, &D_psp_09189DF8[2], 2),
};

extern u8 D_psp_09160D88[0x10];
extern u8 D_psp_09160DA8[0x10];

u_long* D_psp_0918B968[] = {
    MAKE_PAL_OP(PAL_UNK_OP3, 4),
    PAL_UNK_OP3_INFO(0x1700, LEN(D_psp_09160D88)),
    PAL_UNK_OP3_DATA(D_psp_09160D88),
    PAL_UNK_OP3_DATA(D_psp_09160DA8),
    PAL_TERMINATE(),
};

extern u8 D_psp_09160F88[0x100];
extern u8 D_psp_09161188[0x100];
extern u8 D_psp_09161388[0x100];
extern u8 D_psp_09161588[0x100];
extern u8 D_psp_09161788[0x100];

u_long* D_psp_0918B980[] = {
    MAKE_PAL_OP(PAL_UNK_OP3, 4),  PAL_UNK_OP3_INFO(0x1600, LEN(D_psp_09160F88)),
    PAL_UNK_OP3_DATA(D_psp_09160F88), PAL_UNK_OP3_DATA(D_psp_09161188),
    PAL_UNK_OP3_DATA(D_psp_09161388), PAL_UNK_OP3_DATA(D_psp_09161588),
    PAL_UNK_OP3_DATA(D_psp_09161788), PAL_TERMINATE(),
};

extern u8 D_psp_09160DC8[0x10];
extern u8 D_psp_09160DE8[0x10];
extern u8 D_psp_09160E08[0x10];
extern u8 D_psp_09160E28[0x10];
extern u8 D_psp_09160E48[0x10];

u_long* D_psp_0918B9A8[] = {
    MAKE_PAL_OP(PAL_UNK_OP3, 4),  PAL_UNK_OP3_INFO(0x17E0, LEN(D_psp_09160DC8)),
    PAL_UNK_OP3_DATA(D_psp_09160DC8), PAL_UNK_OP3_DATA(D_psp_09160DE8),
    PAL_UNK_OP3_DATA(D_psp_09160E08), PAL_UNK_OP3_DATA(D_psp_09160E28),
    PAL_UNK_OP3_DATA(D_psp_09160E48), PAL_TERMINATE(),
};

extern u8 D_psp_09160E68[0x10];
extern u8 D_psp_09160E88[0x10];
extern u8 D_psp_09160EA8[0x10];
extern u8 D_psp_09160EC8[0x10];
extern u8 D_psp_09160EE8[0x10];

u_long* D_psp_0918B9D0[] = {
    MAKE_PAL_OP(PAL_UNK_OP3, 4),  PAL_UNK_OP3_INFO(0x17F0, LEN(D_psp_09160E68)),
    PAL_UNK_OP3_DATA(D_psp_09160E68), PAL_UNK_OP3_DATA(D_psp_09160E88),
    PAL_UNK_OP3_DATA(D_psp_09160EA8), PAL_UNK_OP3_DATA(D_psp_09160EC8),
    PAL_UNK_OP3_DATA(D_psp_09160EE8), PAL_TERMINATE(),
};

u_long* D_psp_0918B9F8[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA_(0x1006, D_psp_09189E00, 4),
};

u_long* D_psp_0918BA08[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA_(0x1008, &D_psp_09189E08[2], 2),
};

u_long* D_psp_0918BA18[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA_(0x1006, D_psp_09189E10, 4),
};

u_long* D_psp_0918BA28[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA_(0x1006, &D_psp_09189E40[6], 4),
};

u_long* D_psp_0918BA38[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA_(0x1006, D_psp_09189E18, 4),
};

u_long* D_psp_0918BA48[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA_(0x1006, D_psp_09189E20, 4),
};

u_long* D_psp_0918BA58[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA_(0x1006, D_psp_09189E28, 4),
};

u_long* D_psp_0918BA68[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA_(0x1006, D_psp_09189E30, 4),
};

u_long* D_psp_0918BA78[] = {
    MAKE_PAL_OP(PAL_UNK_OP3, 1),
    PAL_UNK_OP3_INFO(0x1006, 4),
    PAL_UNK_OP3_DATA(D_psp_09189E38),
    PAL_UNK_OP3_DATA(&D_psp_09189E40[2]),
    PAL_TERMINATE(),
};

u_long* D_psp_0918BA90[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x1006, D_psp_09189DE8),
};

u_long* D_psp_0918BAA0[] = {
    MAKE_PAL_OP(PAL_GLOW_ANIM, 2),
    PAL_GLOW_INFO(0x1006, 2),
    PAL_GLOW_DATA(D_psp_09189E08),
    PAL_GLOW_DATA(&D_psp_09189E40[0]),
    PAL_TERMINATE(),
};

extern u16 D_psp_091633C0[0x10];

u_long* D_psp_0918BAB8[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x0000, D_psp_091633C0),
    PAL_TERMINATE(),
};

extern u16 D_psp_09166A70[0x10];

u_long* D_psp_0918BAD0[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x1F00, D_psp_09166A70),
    PAL_TERMINATE(),
};

extern u16 D_psp_09161008[0x10];

u_long* D_psp_0918BAE8[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x1F20, D_psp_09161008),
    PAL_TERMINATE(),
};

extern u16 D_psp_091610C8[0x10];

u_long* D_psp_0918BB00[] = {
    MAKE_PAL_OP(PAL_GLOW_ANIM, 1),
    PAL_GLOW_INFO(0x1F20, LEN(D_psp_091610C8)),
    PAL_GLOW_DATA(D_psp_091610C8),
    PAL_GLOW_DATA(D_psp_09161008),
    PAL_TERMINATE(),
};

u16 D_psp_0918BB18[] = {0x8076, 0x80FB, 0x8048, 0x80B1};

u_long* D_psp_0918BB20[] = {
    MAKE_PAL_OP(PAL_UNK_OP2, 1),
    PAL_UNK_OP2_INFO(0x1F0E, 2),
    PAL_UNK_OP2_DATA(&D_psp_0918BB18[0]),
    PAL_UNK_OP2_DATA(&D_psp_0918BB18[2]),
    PAL_TERMINATE(),
};

extern u16 D_psp_091633E0[0x70];

u_long* D_psp_0918BB38[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x1D00, D_psp_091633E0),
    PAL_TERMINATE(),
};

u_long* D_psp_0918BB50[] = {
    MAKE_PAL_OP(PAL_GLOW_ANIM, 2),
    PAL_GLOW_INFO(0x100A, 1),
    PAL_GLOW_DATA(&D_800A37D8[0]),
    PAL_GLOW_DATA(&D_800A37D8[1]),
    PAL_TERMINATE(),
};

u_long* D_psp_0918BB68[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA_(0x10F0, &g_Clut[0x10A0], 16),
};

u_long* D_psp_0918BB78[] = {
    MAKE_PAL_OP(PAL_UNK_OP2, 2),
    PAL_UNK_OP2_INFO(0x10F0, 16),
    PAL_UNK_OP2_DATA(&g_Clut[0x10C0]),
    PAL_TERMINATE(),
};

u_long* D_psp_0918BB90[] = {
    MAKE_PAL_OP(PAL_UNK_OP2, 2),
    PAL_UNK_OP2_INFO(0x10F0, 16),
    PAL_UNK_OP2_DATA(&g_Clut[0x1000]),
    PAL_TERMINATE(),
};

u_long* D_psp_0918BBA8[] = {
    MAKE_PAL_OP(PAL_UNK_OP2, 2),
    PAL_UNK_OP2_INFO(0x10F0, 16),
    PAL_UNK_OP2_DATA(&g_Clut[0x10B0]),
    PAL_TERMINATE(),
};

extern u16 D_psp_09160BC8[0xE0];

u_long* D_psp_0918BBC0[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x1000, D_psp_09160BC8),
};

u_long** D_psp_0918BBD0[] = {D_psp_09189E58, D_psp_0918B830, D_psp_09189E58, D_psp_0918B8A8, D_psp_0918B8C8};
u_long** D_psp_0918BBE8[] = {D_psp_09189E58, D_psp_0918B890, D_psp_09189E58, D_psp_0918B8A8, D_psp_0918B8C8};
u_long** D_psp_0918BC00[] = {D_psp_09189E58, D_psp_0918B860, D_psp_09189E58, D_psp_0918B8A8, D_psp_0918B8C8};
u_long** D_psp_0918BC18[] = {D_psp_09189E58, D_psp_0918B848, D_psp_09189E58, D_psp_0918B8A8, D_psp_0918B8C8};
u_long** D_psp_0918BC30[] = {D_psp_09189E58, D_psp_0918B878, D_psp_09189E58, D_psp_0918B8A8, D_psp_0918B8C8};

extern s16* D_psp_0916A060[];
extern s16* D_psp_0916C850[];
extern s16* D_psp_0916C690[];
extern s16* D_psp_0916F148[];
extern s16* D_psp_0916EC78[];
extern s16* D_psp_0916F6A0[];
extern s16* D_psp_09168228[];
extern s16* D_psp_0916B178[];
extern s16* D_psp_091684B8[];
extern s16* D_psp_0916EEF8[];
extern s16* D_psp_0916EF90[];
extern s16* D_psp_0916F4B0[];
extern s16* D_psp_0916B630[];
extern s16* D_psp_0916C7B8[];

s16** D_800A3B70[] = {
    NULL,       D_800CF324, D_psp_0916A060, D_psp_0916C850, D_psp_0916C690, D_psp_0916F148,
    D_psp_0916EC78, D_psp_0916F6A0, D_psp_09168228, D_psp_0916B178, D_psp_091684B8, D_psp_0916EEF8,
    D_psp_0916EF90, (s16**)D_800CFE48, D_psp_0916F4B0, D_psp_0916B630, D_psp_0916B630, D_psp_0916C7B8};

u_long* D_800A3BB8[] = {
    (u_long*)D_psp_0918B908, (u_long*)D_psp_0918B938, (u_long*)D_psp_0918B948, (u_long*)D_psp_0918B958, (u_long*)D_psp_0918B968, (u_long*)D_psp_0918B980,
    (u_long*)D_psp_0918B9A8, (u_long*)D_psp_0918B9D0, (u_long*)D_psp_0918B920, (u_long*)D_psp_0918B9F8, (u_long*)D_psp_0918BA08, (u_long*)D_psp_0918BA18,
    (u_long*)D_psp_0918BA28, (u_long*)D_psp_0918BA48, (u_long*)D_psp_0918BA58, (u_long*)D_psp_0918BA68, (u_long*)D_psp_0918BA78, (u_long*)D_psp_0918BA90,
    (u_long*)D_psp_0918BA38, (u_long*)D_psp_0918B9F8, (u_long*)D_psp_0918B9F8, (u_long*)D_psp_0918BAA0, (u_long*)D_psp_0918BBC0, (u_long*)D_psp_0918BB50,
    (u_long*)D_psp_0918BAD0, (u_long*)D_psp_0918BAE8, (u_long*)D_psp_0918BAB8, (u_long*)D_psp_0918BB68, (u_long*)D_psp_0918BB78, (u_long*)D_psp_0918BB90,
    (u_long*)D_psp_0918BB00, (u_long*)D_psp_0918BBA8, (u_long*)D_psp_0918BB20, (u_long*)D_psp_0918BB38};