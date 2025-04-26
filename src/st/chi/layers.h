// SPDX-License-Identifier: AGPL-3.0-or-later
// clang-format off
extern u16 tilemap_0F560[];
extern u16 tilemap_0C760[];
extern u16 tilemap_0E960[];
extern u16 tilemap_0DB60[];
extern u16 tilemap_0F360[];
extern u16 tilemap_0B560[];
extern u16 tilemap_0CF60[];
extern u16 tilemap_0D360[];
extern u16 tilemap_0EB60[];
extern u16 tilemap_0EF60[];
extern u16 tilemap_0B160[];
extern u16 tilemap_0C160[];
extern u16 tilemap_0D560[];
extern u16 tilemap_0E360[];
extern u16 tilemap_0A960[];
extern u16 tilemap_0B960[];
extern TileDefinition tiledef_17B80[];
extern TileDefinition tiledef_0FB60[];
extern TileDefinition tiledef_13B70[];
static LayerDef layers[] = {
    { NULL, NULL, 0, 0, 0 },
    { tilemap_0A960, tiledef_17B80, {27, 38, 27, 41, 0x01}, 0x60, 0x0003},
    { tilemap_0B160, tiledef_17B80, {28, 40, 29, 40, 0x01}, 0x60, 0x0003},
    { tilemap_0B560, tiledef_17B80, {30, 40, 31, 40, 0x01}, 0x60, 0x0003},
    { tilemap_0B960, tiledef_17B80, {32, 40, 32, 43, 0x01}, 0x60, 0x0003},
    { tilemap_0C160, tiledef_17B80, {0, 0, 0, 2, 0x04}, 0x20, 0x0003},
    { tilemap_0C760, tiledef_17B80, {33, 40, 36, 40, 0x01}, 0x60, 0x0003},
    { tilemap_0CF60, tiledef_17B80, {37, 40, 37, 41, 0x01}, 0x60, 0x0003},
    { tilemap_0D360, tiledef_17B80, {36, 41, 36, 41, 0x01}, 0x60, 0x0003},
    { tilemap_0D560, tiledef_17B80, {31, 44, 33, 44, 0x01}, 0x60, 0x0003},
    { tilemap_0DB60, tiledef_17B80, {32, 45, 32, 48, 0x01}, 0x60, 0x0003},
    { tilemap_0E360, tiledef_17B80, {0, 0, 0, 2, 0x04}, 0x20, 0x0003},
    { tilemap_0E960, tiledef_17B80, {31, 48, 31, 48, 0x01}, 0x60, 0x0003},
    { tilemap_0EB60, tiledef_17B80, {33, 48, 33, 49, 0x01}, 0x60, 0x0003},
    { tilemap_0EF60, tiledef_17B80, {29, 44, 30, 44, 0x01}, 0x60, 0x0003},
    { tilemap_0F360, tiledef_0FB60, {32, 49, 32, 49, 0x40}, 0x12, 0x0203},
    { tilemap_0F360, tiledef_0FB60, {34, 44, 34, 44, 0x41}, 0x14, 0x0203},
    { tilemap_0F360, tiledef_0FB60, {28, 38, 28, 38, 0x41}, 0x13, 0x0203},
    { tilemap_0F560, tiledef_13B70, {28, 41, 28, 41, 0x22}, 0x60, 0x0203},
};
RoomDef OVL_EXPORT(rooms_layers)[] = {
    { &layers[1], &layers[0] },
    { &layers[2], &layers[0] },
    { &layers[3], &layers[0] },
    { &layers[4], &layers[5] },
    { &layers[6], &layers[0] },
    { &layers[7], &layers[0] },
    { &layers[8], &layers[0] },
    { &layers[9], &layers[0] },
    { &layers[10], &layers[11] },
    { &layers[12], &layers[0] },
    { &layers[13], &layers[0] },
    { &layers[14], &layers[0] },
    { &layers[15], &layers[0] },
    { &layers[16], &layers[0] },
    { &layers[17], &layers[0] },
    { &layers[18], &layers[0] },
};
