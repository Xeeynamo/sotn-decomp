// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
extern u16 tilemap_1AC38[];
extern u16 tilemap_1CC38[];
extern u16 tilemap_1E638[];
extern u16 tilemap_23038[];
extern u16 tilemap_23638[];
extern u16 tilemap_26438[];
extern u16 tilemap_19A38[];
extern u16 tilemap_19E38[];
extern u16 tilemap_1EA38[];
extern u16 tilemap_20038[];
extern u16 tilemap_20238[];
extern u16 tilemap_21438[];
extern u16 tilemap_23438[];
extern u16 tilemap_19438[];
extern u16 tilemap_1BA38[];
extern u16 tilemap_22238[];
extern u16 tilemap_19638[];
extern u16 tilemap_1B238[];
extern u16 tilemap_1CA38[];
extern u16 tilemap_1DA38[];
extern u16 tilemap_25A38[];
extern u16 tilemap_26038[];
extern u16 tilemap_1AE38[];
extern u16 tilemap_1F838[];
extern u16 tilemap_18838[];
extern u16 tilemap_1C238[];
extern u16 tilemap_1CE38[];
extern u16 tilemap_1E838[];
extern u16 tilemap_20838[];
extern u16 tilemap_20E38[];
extern u16 tilemap_21238[];
extern u16 tilemap_1F638[];
extern u16 tilemap_21038[];
extern u16 tilemap_21638[];
extern u16 tilemap_22E38[];
extern u16 tilemap_23238[];
extern u16 tilemap_1B038[];
extern u16 tilemap_1B638[];
extern u16 tilemap_1FA38[];
extern u16 tilemap_1FC38[];
extern u16 tilemap_25C38[];
extern u16 tilemap_25E38[];
extern u16 tilemap_26238[];
extern TileDefinition tiledef_2EA58[];
extern TileDefinition tiledef_26A38[];
extern TileDefinition tiledef_2AA48[];
static LayerDef layers[] = {
    { NULL, NULL, 0, 0, 0 },
    { tilemap_18838, tiledef_2EA58, {2, 38, 3, 40, 0x01}, 0x60, 0x0003},
    { tilemap_19438, tiledef_2EA58, {0, 0, 0, 0, 0x00}, 0x20, 0x0003},
    { tilemap_19638, tiledef_2EA58, {2, 41, 2, 42, 0x01}, 0xA0, 0x0003},
    { tilemap_19A38, tiledef_2EA58, {2, 41, 2, 42, 0x01}, 0x60, 0x0003},
    { tilemap_19E38, tiledef_2EA58, {4, 40, 10, 40, 0x01}, 0x60, 0x0003},
    { tilemap_1AC38, tiledef_2EA58, {0, 0, 0, 0, 0x00}, 0x20, 0x0003},
    { tilemap_1AE38, tiledef_2EA58, {5, 38, 5, 38, 0x01}, 0x60, 0x0003},
    { tilemap_1B038, tiledef_2EA58, {5, 38, 5, 38, 0x01}, 0x20, 0x0003},
    { tilemap_1B238, tiledef_2EA58, {6, 38, 6, 39, 0x01}, 0x60, 0x0003},
    { tilemap_1B638, tiledef_2EA58, {6, 38, 6, 39, 0x01}, 0x20, 0x0003},
    { tilemap_1BA38, tiledef_2EA58, {7, 39, 10, 39, 0x01}, 0x60, 0x0003},
    { tilemap_1C238, tiledef_2EA58, {7, 39, 10, 39, 0x01}, 0x20, 0x0003},
    { tilemap_1CA38, tiledef_2EA58, {11, 39, 11, 39, 0x01}, 0x60, 0x0003},
    { tilemap_1CC38, tiledef_2EA58, {11, 39, 11, 39, 0x01}, 0x20, 0x0003},
    { tilemap_1CE38, tiledef_2EA58, {11, 40, 13, 41, 0x01}, 0xA0, 0x0003},
    { tilemap_1DA38, tiledef_2EA58, {11, 40, 13, 41, 0x01}, 0x60, 0x0003},
    { tilemap_1E638, tiledef_2EA58, {10, 41, 10, 41, 0x01}, 0xA0, 0x0003},
    { tilemap_1E838, tiledef_2EA58, {10, 41, 10, 41, 0x01}, 0x60, 0x0003},
    { tilemap_1EA38, tiledef_2EA58, {14, 40, 19, 40, 0x01}, 0x60, 0x0003},
    { tilemap_1F638, tiledef_2EA58, {0, 0, 0, 0, 0x00}, 0x20, 0x0003},
    { tilemap_1F838, tiledef_2EA58, {14, 41, 14, 41, 0x01}, 0xA0, 0x0003},
    { tilemap_1FA38, tiledef_2EA58, {14, 41, 14, 41, 0x01}, 0x60, 0x0003},
    { tilemap_1FC38, tiledef_2EA58, {20, 39, 20, 40, 0x01}, 0x60, 0x0003},
    { tilemap_20038, tiledef_2EA58, {0, 0, 0, 0, 0x00}, 0x20, 0x0003},
    { tilemap_20238, tiledef_2EA58, {21, 38, 21, 40, 0x01}, 0x60, 0x0003},
    { tilemap_20838, tiledef_2EA58, {21, 38, 21, 40, 0x01}, 0x20, 0x0003},
    { tilemap_20E38, tiledef_2EA58, {20, 38, 20, 38, 0x01}, 0x60, 0x0003},
    { tilemap_21038, tiledef_2EA58, {0, 0, 0, 0, 0x00}, 0x20, 0x0003},
    { tilemap_21238, tiledef_2EA58, {19, 39, 19, 39, 0x01}, 0x60, 0x0003},
    { tilemap_21438, tiledef_2EA58, {19, 39, 19, 39, 0x01}, 0x20, 0x0003},
    { tilemap_21638, tiledef_2EA58, {18, 36, 19, 38, 0x01}, 0x60, 0x0003},
    { tilemap_22238, tiledef_2EA58, {18, 36, 19, 38, 0x01}, 0x20, 0x0003},
    { tilemap_22E38, tiledef_2EA58, {17, 38, 17, 38, 0x01}, 0x60, 0x0003},
    { tilemap_23038, tiledef_2EA58, {17, 38, 17, 38, 0x01}, 0x20, 0x0003},
    { tilemap_23238, tiledef_2EA58, {20, 37, 20, 37, 0x01}, 0x60, 0x0003},
    { tilemap_23438, tiledef_2EA58, {20, 37, 20, 37, 0x01}, 0x20, 0x0003},
    { tilemap_23638, tiledef_2EA58, {0, 44, 17, 44, 0x10}, 0x60, 0x0003},
    { tilemap_25A38, tiledef_2EA58, {0, 0, 0, 0, 0x00}, 0x20, 0x0003},
    { tilemap_25C38, tiledef_2EA58, {18, 44, 18, 44, 0x80}, 0x02, 0x0028},
    { tilemap_25E38, tiledef_2EA58, {1, 40, 1, 40, 0x92}, 0x11, 0x002C},
    { tilemap_26038, tiledef_26A38, {20, 36, 20, 36, 0x41}, 0x0B, 0x0203},
    { tilemap_26038, tiledef_26A38, {16, 38, 16, 38, 0x40}, 0x0E, 0x0203},
    { tilemap_26038, tiledef_26A38, {17, 36, 17, 36, 0x40}, 0x0D, 0x0203},
    { tilemap_26038, tiledef_26A38, {15, 41, 15, 41, 0x41}, 0x0C, 0x0203},
    { tilemap_26238, tiledef_2AA48, {3, 42, 3, 42, 0x22}, 0x60, 0x0203},
    { tilemap_26438, tiledef_2AA48, {17, 37, 17, 37, 0x20}, 0x60, 0x0203},
    { tilemap_26438, tiledef_2AA48, {5, 39, 5, 39, 0x20}, 0x60, 0x0203},
};
RoomDef OVL_EXPORT(rooms_layers)[] = {
    { &layers[1], &layers[2] },
    { &layers[3], &layers[4] },
    { &layers[5], &layers[6] },
    { &layers[7], &layers[8] },
    { &layers[9], &layers[10] },
    { &layers[11], &layers[12] },
    { &layers[13], &layers[14] },
    { &layers[15], &layers[16] },
    { &layers[17], &layers[18] },
    { &layers[19], &layers[20] },
    { &layers[21], &layers[22] },
    { &layers[23], &layers[24] },
    { &layers[25], &layers[26] },
    { &layers[27], &layers[28] },
    { &layers[29], &layers[30] },
    { &layers[31], &layers[32] },
    { &layers[33], &layers[34] },
    { &layers[35], &layers[36] },
    { &layers[37], &layers[38] },
    { &layers[39], &layers[0] },
    { &layers[40], &layers[0] },
    { &layers[41], &layers[0] },
    { &layers[42], &layers[0] },
    { &layers[43], &layers[0] },
    { &layers[44], &layers[0] },
    { &layers[45], &layers[0] },
    { &layers[46], &layers[0] },
    { &layers[47], &layers[0] },
};
