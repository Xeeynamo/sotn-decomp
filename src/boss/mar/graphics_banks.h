// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
static u_long* mar_gfxbank_0[] = {
    GFX_TERMINATE(),
};
extern u8 D_801830F0[];
extern u8 D_80184220[];
static u_long* mar_gfxbank_1[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x080, 128, 128, D_801830F0),
    GFX_ENTRY(0x100, 0x0A0, 128, 128, D_80184220),
    GFX_TERMINATE(),
};
u_long* OVL_EXPORT(gfxBanks)[] = {
    mar_gfxbank_0,
    mar_gfxbank_1,
    mar_gfxbank_0,
    mar_gfxbank_0,
    mar_gfxbank_0,
    mar_gfxbank_0,
    mar_gfxbank_0,
    mar_gfxbank_0,
    mar_gfxbank_0,
    mar_gfxbank_0,
    mar_gfxbank_0,
    mar_gfxbank_0,
    mar_gfxbank_0,
    mar_gfxbank_0,
    mar_gfxbank_0,
    mar_gfxbank_0,
    mar_gfxbank_0,
    mar_gfxbank_0,
    mar_gfxbank_0,
    mar_gfxbank_0,
};
