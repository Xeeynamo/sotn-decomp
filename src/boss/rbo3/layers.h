// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
extern u16 tilemap_07630[];
extern u16 tilemap_07A30[];
extern TileDefinition tiledef_0C240[];
extern TileDefinition tiledef_08230[];
static LayerDef layers[] = {
    { NULL, NULL, 0, 0, 0 },
    { tilemap_07630, tiledef_0C240, {39, 50, 40, 50, 0x01}, 0x60, 0x0003},
    { tilemap_07A30, tiledef_0C240, {39, 50, 40, 50, 0x01}, 0x20, 0x0003},
};
RoomDef OVL_EXPORT(rooms_layers)[] = {
    { &layers[1], &layers[2] },
};
