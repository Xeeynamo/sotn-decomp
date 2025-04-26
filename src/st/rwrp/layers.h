// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
extern u16 tilemap_01FC8[];
extern u16 tilemap_021C8[];
extern u16 tilemap_023C8[];
extern u16 tilemap_025C8[];
extern u16 tilemap_027C8[];
extern u16 tilemap_029C8[];
extern TileDefinition tiledef_02FC8[];
extern TileDefinition tiledef_06FD8[];
static LayerDef layers[] = {
    { NULL, NULL, 0, 0, 0 },
    { tilemap_01FC8, tiledef_06FD8, {23, 51, 23, 51, 0x01}, 0x60, 0x0003},
    { tilemap_021C8, tiledef_06FD8, {26, 42, 26, 42, 0x01}, 0x60, 0x0003},
    { tilemap_023C8, tiledef_06FD8, {4, 46, 4, 46, 0x01}, 0x60, 0x0003},
    { tilemap_025C8, tiledef_06FD8, {48, 25, 48, 25, 0x01}, 0x60, 0x0003},
    { tilemap_027C8, tiledef_06FD8, {28, 19, 28, 19, 0x01}, 0x60, 0x0003},
    { tilemap_029C8, tiledef_02FC8, {29, 19, 29, 19, 0x41}, 0x20, 0x0203},
    { tilemap_029C8, tiledef_02FC8, {47, 25, 47, 25, 0x40}, 0x1F, 0x0203},
    { tilemap_029C8, tiledef_02FC8, {27, 42, 27, 42, 0x41}, 0x1E, 0x0203},
    { tilemap_029C8, tiledef_02FC8, {3, 46, 3, 46, 0x40}, 0x1D, 0x0203},
    { tilemap_029C8, tiledef_02FC8, {24, 51, 24, 51, 0x41}, 0x1C, 0x0203},
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
