// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
extern u16 tilemap_1E2D0[];
extern u16 tilemap_1B2D0[];
extern u16 tilemap_1C6D0[];
extern u16 tilemap_1DAD0[];
extern u16 tilemap_1E0D0[];
extern TileDefinition tiledef_226D0[];
static LayerDef layers[] = {
    { NULL, NULL, 0, 0, 0 },
    { tilemap_1B2D0, tiledef_226D0, {0, 2, 4, 3, 0x01}, 0xA0, 0x0003},
    { tilemap_1C6D0, tiledef_226D0, {0, 2, 4, 3, 0x01}, 0x60, 0x0003},
    { tilemap_1DAD0, tiledef_226D0, {0, 0, 2, 0, 0x01}, 0x60, 0x0003},
    { tilemap_1E0D0, tiledef_226D0, {0, 4, 0, 4, 0x01}, 0x60, 0x0003},
    { tilemap_1E2D0, tiledef_226D0, {1, 1, 2, 1, 0x01}, 0x60, 0x0003},
};
RoomDef OVL_EXPORT(rooms_layers)[] = {
    { &layers[1], &layers[2] },
    { &layers[3], &layers[0] },
    { &layers[4], &layers[0] },
    { &layers[5], &layers[0] },
};
