// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
extern u16 tilemap_05300[];
extern u16 tilemap_05500[];
extern TileDefinition tiledef_09700[];
static LayerDef layers[] = {
    { NULL, NULL, 0, 0, 0 },
    { tilemap_05300, tiledef_09700, {32, 26, 32, 26, 0x01}, 0x60, 0x0003},
    { tilemap_05500, tiledef_09700, {32, 26, 32, 26, 0x01}, 0x20, 0x0003},
};
RoomDef OVL_EXPORT(rooms_layers)[] = {
    { &layers[1], &layers[2] },
};
