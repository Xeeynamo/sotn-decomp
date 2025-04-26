// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
extern u16 tilemap_07FEC[];
extern u16 tilemap_069EC[];
extern u16 tilemap_06DEC[];
extern TileDefinition tiledef_0C5FC[];
extern TileDefinition tiledef_085EC[];
static LayerDef layers[] = {
    { NULL, NULL, 0, 0, 0 },
    { tilemap_069EC, tiledef_0C5FC, {32, 28, 32, 29, 0x01}, 0x60, 0x0003},
    { tilemap_06DEC, tiledef_0C5FC, {31, 30, 33, 32, 0x01}, 0x60, 0x0003},
    { tilemap_07FEC, tiledef_0C5FC, {32, 33, 32, 33, 0x10}, 0x60, 0x0003},
};
RoomDef OVL_EXPORT(rooms_layers)[] = {
    { &layers[1], &layers[0] },
    { &layers[2], &layers[0] },
    { &layers[3], &layers[0] },
};
