// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
extern u16 tilemap_01D68[];
extern u16 tilemap_01F68[];
extern u16 tilemap_02168[];
extern u16 tilemap_02368[];
extern u16 tilemap_02568[];
extern u16 tilemap_02768[];
extern TileDefinition tiledef_06D78[];
extern TileDefinition tiledef_02D68[];
static LayerDef layers[] = {
    { NULL, NULL, 0, 0, 0 },
    { tilemap_01D68, tiledef_06D78, {40, 12, 40, 12, 0x01}, 0x60, 0x0003},
    { tilemap_01F68, tiledef_06D78, {37, 21, 37, 21, 0x01}, 0x60, 0x0003},
    { tilemap_02168, tiledef_06D78, {59, 17, 59, 17, 0x01}, 0x60, 0x0003},
    { tilemap_02368, tiledef_06D78, {15, 38, 15, 38, 0x01}, 0x60, 0x0003},
    { tilemap_02568, tiledef_06D78, {35, 44, 35, 44, 0x01}, 0x60, 0x0003},
    { tilemap_02768, tiledef_02D68, {34, 44, 34, 44, 0x40}, 0x20, 0x0203},
    { tilemap_02768, tiledef_02D68, {16, 38, 16, 38, 0x41}, 0x1F, 0x0203},
    { tilemap_02768, tiledef_02D68, {36, 21, 36, 21, 0x40}, 0x1E, 0x0203},
    { tilemap_02768, tiledef_02D68, {60, 17, 60, 17, 0x41}, 0x1D, 0x0203},
    { tilemap_02768, tiledef_02D68, {39, 12, 39, 12, 0x40}, 0x1C, 0x0203},
};
RoomDef OVL_EXPORT(rooms_layers)[] = {
    { &layers[1], &layers[0] },
    { &layers[2], &layers[0] },
    { &layers[3], &layers[0] },
    { &layers[4], &layers[0] },
    { &layers[5], &layers[0] },
    { &layers[6], &layers[0] },
    { &layers[7], &layers[0] },
    { &layers[8], &layers[0] },
    { &layers[9], &layers[0] },
    { &layers[10], &layers[0] },
};
