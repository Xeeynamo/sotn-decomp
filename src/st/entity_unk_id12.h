// SPDX-License-Identifier: AGPL-3.0-or-later

extern u16 g_EntityUnkId12Init[];
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
        InitializeEntity(g_EntityUnkId12Init);
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
