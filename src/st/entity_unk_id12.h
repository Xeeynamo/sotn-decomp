// SPDX-License-Identifier: AGPL-3.0-or-later

static u8 g_EntityUnkId12Hitbox[] = {
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x50, 0x20};

#ifndef VERSION_PSP // moved to BSS
static u8 g_EntityUnkId12Data[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
#else
extern u8 g_EntityUnkId12Data[];
#endif

static u16 g_EntityUnkId12TilemapProps[] = {
    0x0000, 0x0000, 0x0600, 0x0100, 0x0000, 0x0000, 0x0600, 0x01FC, 0x0000,
    0x00FC, 0x0600, 0x01FC, 0x0000, 0x0000, 0x0600, 0x01FC, 0x0000, 0x00FC,
    0x0600, 0x0300, 0x0000, 0x00FC, 0x0600, 0x01FC, 0x0000, 0x00FC, 0x0600,
    0x0300, 0x0000, 0x0200, 0x0600, 0x0300, 0x0000, 0x01FC, 0x0500, 0x02FC,
    0x0000, 0x0000, 0x0500, 0x0400, 0x0000, 0x0000, 0x0500, 0x0400, 0x0000,
    0x01FC, 0x0500, 0x02FC, 0x00F0, 0x01FC, 0x0310, 0x02FC, 0x00F0, 0x01FC,
    0x0310, 0x02FC,
#if defined(STAGE_IS_NO3)
    0x0104, 0x0204, 0x0000, 0x0000, 0x0004, 0x0004, 0x0000, 0x0000
#endif
};

extern u16 g_EInitUnkId12[];
void EntityUnkId12(Entity* entity) {
    u16 var_s0;
    u16 params;
    u16* tilemapProps;

    entity->unk6D[0] = 0;
    params = entity->params;
    if (entity->step) {
        switch (params) {
        case 4:
        case 5:
            if (g_Tilemap.x) {
                return;
            }
            break;
        case 6:
            if (g_pads->pressed & PAD_TRIANGLE) {
                g_Tilemap.x = 0;
                g_Tilemap.width = 1280;
                entity->step++;
                return;
            }
            break;
        }

        if (entity->hitParams) {
            var_s0 = GetSideToPlayer();
            if (entity->ext.generic.unk7C.u) {
                var_s0 &= 2;
                var_s0 *= 2;
            } else {
                var_s0 &= 1;
                var_s0 *= 4;
            }
            params = (params << 3) + var_s0;
            tilemapProps = &g_EntityUnkId12TilemapProps[params];
            g_Tilemap.x = *tilemapProps++;
            g_Tilemap.y = *tilemapProps++;
            g_Tilemap.width = *tilemapProps++;
            g_Tilemap.height = *tilemapProps;
        }
    } else {
        InitializeEntity(g_EInitUnkId12);
        var_s0 = entity->ext.generic.unk7C.u = g_EntityUnkId12Data[params];
        if (var_s0) {
            entity->hitboxWidth = g_EntityUnkId12Hitbox[params];
            entity->hitboxHeight = 16;
        } else {
            entity->hitboxWidth = 16;
            entity->hitboxHeight = g_EntityUnkId12Hitbox[params];
        }
    }
}
