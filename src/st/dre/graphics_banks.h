// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
static u_long* dre_gfxbank_0[] = {
    GFX_BANK_NONE,
    GFX_ENTRY(0x000, 0x000, 0, 0, NULL),
    GFX_TERMINATE(),
};
extern u8 stage_title_us[];
extern u8 stage_placeholder[];
static u_long* dre_gfxbank_1[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x040, 128, 128, stage_title_us),
    GFX_ENTRY(0x100, 0x060, 128, 128, stage_placeholder),
    GFX_TERMINATE(),
};
extern u8 stage_title_us[];
extern u8 e_succubus_g0[];
extern u8 e_succubus_g1[];
extern u8 e_succubus_g2[];
extern u8 e_succubus_g3[];
extern u8 e_succubus_g4[];
extern u8 e_succubus_g5[];
extern u8 e_succubus_g6[];
extern u8 e_succubus_g7[];
static u_long* dre_gfxbank_2[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x040, 128, 128, stage_title_us),
    GFX_ENTRY(0x100, 0x080, 128, 128, e_succubus_g0),
    GFX_ENTRY(0x100, 0x0A0, 128, 128, e_succubus_g1),
    GFX_ENTRY(0x180, 0x080, 128, 128, e_succubus_g2),
    GFX_ENTRY(0x180, 0x0A0, 128, 128, e_succubus_g3),
    GFX_ENTRY(0x100, 0x0C0, 128, 128, e_succubus_g4),
    GFX_ENTRY(0x100, 0x0E0, 128, 128, e_succubus_g5),
    GFX_ENTRY(0x180, 0x0C0, 128, 128, e_succubus_g6),
    GFX_ENTRY(0x180, 0x0E0, 128, 128, e_succubus_g7),
    GFX_TERMINATE(),
};
u_long* OVL_EXPORT(gfxBanks)[] = {
    dre_gfxbank_0,
    dre_gfxbank_2,
    dre_gfxbank_0,
    dre_gfxbank_0,
    dre_gfxbank_0,
    dre_gfxbank_1,
    dre_gfxbank_0,
    dre_gfxbank_0,
    dre_gfxbank_0,
    dre_gfxbank_0,
    dre_gfxbank_0,
    dre_gfxbank_0,
    dre_gfxbank_0,
    dre_gfxbank_0,
    dre_gfxbank_0,
    dre_gfxbank_0,
    dre_gfxbank_0,
    dre_gfxbank_0,
    dre_gfxbank_0,
    dre_gfxbank_0,
};
