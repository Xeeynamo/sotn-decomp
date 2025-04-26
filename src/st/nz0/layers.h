// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
extern u16 tilemap_1E25C[];
extern u16 tilemap_2005C[];
extern u16 tilemap_2025C[];
extern u16 tilemap_1805C[];
extern u16 tilemap_1845C[];
extern u16 tilemap_1AE5C[];
extern u16 tilemap_19C5C[];
extern u16 tilemap_1D65C[];
extern u16 tilemap_2045C[];
extern u16 tilemap_17A5C[];
extern u16 tilemap_1A05C[];
extern u16 tilemap_1AA5C[];
extern u16 tilemap_1F25C[];
extern u16 tilemap_2085C[];
extern u16 tilemap_16E5C[];
extern u16 tilemap_1885C[];
extern u16 tilemap_1925C[];
extern u16 tilemap_17C5C[];
extern u16 tilemap_1905C[];
extern u16 tilemap_16C5C[];
extern u16 tilemap_17E5C[];
extern u16 tilemap_18A5C[];
extern u16 tilemap_1EE5C[];
extern u16 tilemap_16A5C[];
extern u16 tilemap_1BE5C[];
extern u16 tilemap_1D45C[];
extern u16 tilemap_1C65C[];
extern u16 tilemap_1C85C[];
extern u16 tilemap_2065C[];
extern u16 tilemap_1725C[];
extern u16 tilemap_1865C[];
extern u16 tilemap_1A45C[];
extern TileDefinition tiledef_24E6C[];
extern TileDefinition tiledef_20E5C[];
extern TileDefinition tiledef_26E7C[];
static LayerDef layers[] = {
    { NULL, NULL, 0, 0, 0 },
    { tilemap_16A5C, tiledef_26E7C, {13, 27, 13, 27, 0x01}, 0x60, 0x0003},
    { tilemap_16C5C, tiledef_26E7C, {5, 28, 5, 28, 0x01}, 0x60, 0x0003},
    { tilemap_16E5C, tiledef_26E7C, {6, 28, 7, 28, 0x01}, 0x60, 0x0003},
    { tilemap_1725C, tiledef_26E7C, {15, 26, 18, 26, 0x01}, 0x60, 0x0003},
    { tilemap_17A5C, tiledef_26E7C, {16, 34, 16, 34, 0x01}, 0x60, 0x0003},
    { tilemap_17C5C, tiledef_26E7C, {10, 29, 10, 29, 0x01}, 0x60, 0x0003},
    { tilemap_17E5C, tiledef_26E7C, {16, 31, 16, 31, 0x01}, 0x60, 0x0003},
    { tilemap_1805C, tiledef_26E7C, {13, 33, 14, 33, 0x01}, 0x60, 0x0003},
    { tilemap_1845C, tiledef_26E7C, {0, 0, 0, 0, 0x05}, 0x20, 0x1003},
    { tilemap_1865C, tiledef_26E7C, {15, 33, 15, 33, 0x01}, 0x60, 0x0003},
    { tilemap_1885C, tiledef_26E7C, {11, 34, 11, 34, 0x01}, 0x60, 0x0003},
    { tilemap_18A5C, tiledef_26E7C, {14, 36, 16, 36, 0x01}, 0x60, 0x0003},
    { tilemap_1905C, tiledef_26E7C, {0, 0, 0, 0, 0x05}, 0x20, 0x1003},
    { tilemap_1925C, tiledef_26E7C, {8, 27, 8, 31, 0x01}, 0x60, 0x0003},
    { tilemap_19C5C, tiledef_26E7C, {11, 29, 11, 30, 0x01}, 0x60, 0x0003},
    { tilemap_1A05C, tiledef_26E7C, {11, 31, 11, 32, 0x01}, 0x60, 0x0003},
    { tilemap_1A45C, tiledef_26E7C, {12, 32, 12, 34, 0x01}, 0x60, 0x0003},
    { tilemap_1AA5C, tiledef_26E7C, {12, 35, 12, 36, 0x01}, 0x60, 0x0003},
    { tilemap_1AE5C, tiledef_26E7C, {9, 27, 12, 28, 0x01}, 0x60, 0x0003},
    { tilemap_1BE5C, tiledef_26E7C, {9, 30, 10, 31, 0x01}, 0x60, 0x0003},
    { tilemap_1C65C, tiledef_26E7C, {0, 0, 0, 0, 0x05}, 0x20, 0x1003},
    { tilemap_1C85C, tiledef_26E7C, {13, 34, 15, 35, 0x01}, 0x60, 0x0003},
    { tilemap_1D45C, tiledef_26E7C, {0, 0, 0, 0, 0x05}, 0x20, 0x1003},
    { tilemap_1D65C, tiledef_26E7C, {13, 26, 14, 28, 0x01}, 0x60, 0x0003},
    { tilemap_1E25C, tiledef_26E7C, {19, 25, 20, 27, 0x01}, 0x60, 0x0003},
    { tilemap_1EE5C, tiledef_26E7C, {15, 28, 16, 28, 0x01}, 0x60, 0x0003},
    { tilemap_1F25C, tiledef_26E7C, {17, 28, 17, 34, 0x01}, 0x60, 0x0003},
    { tilemap_2005C, tiledef_26E7C, {0, 0, 0, 0, 0x05}, 0x20, 0x1003},
    { tilemap_2025C, tiledef_24E6C, {7, 30, 7, 30, 0x20}, 0x60, 0x0203},
    { tilemap_2045C, tiledef_24E6C, {15, 27, 15, 27, 0x22}, 0x60, 0x0203},
    { tilemap_2065C, tiledef_24E6C, {16, 35, 16, 35, 0x22}, 0x60, 0x0203},
    { tilemap_2085C, tiledef_20E5C, {21, 26, 21, 26, 0x41}, 0x16, 0x0203},
    { tilemap_2085C, tiledef_20E5C, {4, 28, 4, 28, 0x40}, 0x17, 0x0203},
    { tilemap_2085C, tiledef_20E5C, {17, 36, 17, 36, 0x41}, 0x15, 0x0203},
};
RoomDef OVL_EXPORT(rooms_layers)[] = {
    { &layers[1], &layers[0] },
    { &layers[2], &layers[0] },
    { &layers[3], &layers[0] },
    { &layers[4], &layers[0] },
    { &layers[5], &layers[0] },
    { &layers[6], &layers[0] },
    { &layers[7], &layers[0] },
    { &layers[8], &layers[9] },
    { &layers[10], &layers[0] },
    { &layers[11], &layers[0] },
    { &layers[12], &layers[13] },
    { &layers[14], &layers[0] },
    { &layers[15], &layers[0] },
    { &layers[16], &layers[0] },
    { &layers[17], &layers[0] },
    { &layers[18], &layers[0] },
    { &layers[19], &layers[0] },
    { &layers[20], &layers[21] },
    { &layers[22], &layers[23] },
    { &layers[24], &layers[0] },
    { &layers[25], &layers[0] },
    { &layers[26], &layers[0] },
    { &layers[27], &layers[28] },
    { &layers[29], &layers[0] },
    { &layers[30], &layers[0] },
    { &layers[31], &layers[0] },
    { &layers[32], &layers[0] },
    { &layers[33], &layers[0] },
    { &layers[34], &layers[0] },
};
