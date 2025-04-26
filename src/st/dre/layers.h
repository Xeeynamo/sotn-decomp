// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
extern u16 tilemap_0B548[];
extern u16 tilemap_0B948[];
extern TileDefinition tiledef_10158[];
extern TileDefinition tiledef_0C148[];
static LayerDef layers[] = {
    { NULL, NULL, 0, 0, 0 },
    { tilemap_0B548, tiledef_10158, {0, 0, 1, 0, 0x10}, 0x60, 0x0003},
    { tilemap_0B948, tiledef_10158, {0, 1, 1, 1, 0x10}, 0x60, 0x0003},
};
RoomDef OVL_EXPORT(rooms_layers)[] = {
    { &layers[1], &layers[0] },
    { &layers[2], &layers[0] },
};
