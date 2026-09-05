// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef PALETTES_H
#define PALETTES_H

// Palette macros
#define PAL_UNK_FLAG 0x8000
#define PAL_FLAG(x) ((x) | PAL_UNK_FLAG)

#define PALETTE_LEN ((COLORS_PER_PAL) * ((COLOR_BPP) / 8))

#define MAKE_PAL_OP(kind, freq) (u_long*)((kind) | ((freq) << 0x10))
#define GET_PAL_OP_KIND(x) (LOHU(x))
#define GET_PAL_OP_FREQ(x) (HIH(x))

#define PAL_COPY 1
#define PAL_COPY_INFO() MAKE_PAL_OP(PAL_COPY, 0)
#define PAL_COPY_DATA(dst, data)                                               \
    (u_long*)(dst), (u_long*)LEN(data), (u_long*)(data)
#define PAL_COPY_DATA_(dst, data, len)                                         \
    (u_long*)(dst), (u_long*)(len), (u_long*)(data)

#define PAL_UNK_OP2 2
#define PAL_UNK_OP2_INFO(dst, n) (u_long*)(dst), (u_long*)(n)
#define PAL_UNK_OP2_DATA(data) (u_long*)(data)

#define PAL_UNK_OP3 3
#define PAL_UNK_OP3_INFO(dst, n) (u_long*)(dst), (u_long*)(n)
#define PAL_UNK_OP3_DATA(data) (u_long*)(data)

#define PAL_GLOW_ANIM 4
#define PAL_GLOW_INFO(dst, n) (u_long*)(dst), (u_long*)(n)
#define PAL_GLOW_DATA(data) (u_long*)(data)

#define PAL_BULK_COPY 5
#define PAL_BULK_COPY_INFO(dst, n) (u_long*)(dst), (u_long*)(n)
#define PAL_BULK(dst, src) (u_long*)(dst), (u_long*)LEN(src), (u_long*)(src)
#define PAL_BULK_(dst, src, len) (u_long*)(dst), (u_long*)(len), (u_long*)(src)

#define PAL_TERMINATE() ((u_long*)-1)

// Palettes
// Each palette is made up of 16 colors and range from 0x000 to 0x2FF.
// Each 0x100 is its own category.
// - 0x000-0x0FF = used by stage overlay
// - 0x100-0x1FF = from F_GAME.BIN and F_GAME2.BIN, used by player characters
//                 weapons, and common objects across all stages overlays.
// - 0x200-0x2FF = enemies and other overlay-specific palettes
typedef enum PaletteIndices {
    PAL_NULL = 0x0, // breakable

    // 0x100-0x1FF
    PAL_ALUCARD = 0x100,
    PAL_ALUCARD_RED_OUTLINE,
    PAL_ALUCARD_BLUE_OUTLINE_MASK, // EntityWingSmashTrail and ELEMENT_THUNDER
    PAL_ALUCARD_GRAY_OUTLINE_MASK,
    PAL_ALUCARD_WOLF,
    PAL_PLAYER_HIDDEN = 0x10D, // used during teleporting and transforming
    PAL_UNK_110 = 0x110,       // weapon
    PAL_UNK_111 = 0x111,
    PAL_UNK_117 = 0x117,
    PAL_RICHTER = 0x120,
    PAL_UNK_128 = 0x128,
    PAL_UNK_12F = 0x12F,
    PAL_UNK_138 = 0x138,
    PAL_UNK_13C = 0x13C,
    PAL_UNK_13D = 0x13D, // richter
    // TODO: This enum value is duplicated and can't be auto-linted
    // We should probably fix this at some point
    PAL_SERVANT = 0x140,
    PAL_RIC_WHIP = 0x140,
    PAL_UNK_143 = 0x143,
    PAL_UNK_148 = 0x148,
    PAL_UNK_149 = 0x149,
    PAL_UNK_14E = 0x14E, // richter

    // Fill colors (color 0 in palette is still used for transparent bg)
    /* 0x158 */ PAL_FILL_YELLOW = 0x158,
    /* 0x159 */ PAL_FILL_ORANGE,
    /* 0x15A */ PAL_FILL_PURPLE,
    /* 0x15B */ PAL_FILL_BLUE,
    /* 0x15C */ PAL_FILL_GREEN,
    /* 0x15D */ PAL_FILL_RED,
    /* 0x15E */ PAL_FILL_BLACK,
    /* 0x15F */ PAL_FILL_WHITE,

    // Color-cycling effects
    /* 0x160 */ PAL_CC_FIRE_EFFECT,
    /* 0x161 */ PAL_CC_STONE_EFFECT,
    /* 0x162 */ PAL_CC_MAGIC_HUD_EFFECT,
    /* 0x163 */ PAL_CC_CRITICAL_EFFECT,
    /* 0x164 */ PAL_CC_DARK_EFFECT, // ELEMENT_POISON and ELEMENT_DARK
    /* 0x165 */ PAL_CC_CURSE_EFFECT,
    /* 0x166 */ PAL_CC_RED_EFFECT_A, // ELEMENT_CUT
    /* 0x167 */ PAL_CC_YELLOW_EFFECT,
    /* 0x168 */ PAL_CC_GREEN_EFFECT_A, // ELEMENT_HOLY
    /* 0x169 */ PAL_CC_BLUE_EFFECT_A,  // ELEMENT_ICE
    /* 0x16A */ PAL_CC_PURPLE_EFFECT_A,
    /* 0x16B */ PAL_CC_TURQUOISE_EFFECT, // spectral sword
    /* 0x16C */ PAL_CC_PURPLE_EFFECT_B,
    /* 0x16D */ PAL_CC_RED_EFFECT_B,
    /* 0x16E */ PAL_CC_GREEN_EFFECT_B,
    /* 0x16F */ PAL_CC_BLUE_EFFECT_B,
    PAL_UNK_170 = 0x170,
    PAL_UNK_190 = 0x190,
    PAL_UNK_191 = 0x191,
    PAL_UNK_194 = 0x194,
    PAL_UNK_195 = 0x195,
    PAL_UNK_196 = 0x196,
    PAL_UNK_197 = 0x197,
    PAL_UNK_198 = 0x198,
    PAL_UNK_199 = 0x199,
    PAL_UNK_19C = 0x19C,
    PAL_UNK_19D = 0x19D, // Light grey to black gradient
    PAL_UNK_19E = 0x19E,
    PAL_UNK_19F = 0x19F, // Black to white gradient
    // eDamageDisplay
    PAL_UNK_1B0 = 0x1B0,
    PAL_UNK_1B1 = 0x1B1,
    PAL_UNK_1B2 = 0x1B2,
    PAL_UNK_1B3 = 0x1B3,
    PAL_UNK_1B4 = 0x1B4,
    PAL_UNK_1B5 = 0x1B5,
    PAL_UNK_1B6 = 0x1B6,
    PAL_UNK_1B7 = 0x1B7,
    PAL_UNK_1B8 = 0x1B8,
    PAL_UNK_1BA = 0x1BA,
    PAL_UNK_1A1 = 0x1A1,
    PAL_UNK_1AB = 0x1AB,
    PAL_UNK_1AE = 0x1AE,
    PAL_UNK_1AF = 0x1AF,
    PAL_UNK_1CF = 0x1CF,
    PAL_UNK_1F3 = 0x1F3,
    // 0x200-0x2FF is not included here
} PaletteIndices;

#endif
