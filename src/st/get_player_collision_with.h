// SPDX-License-Identifier: AGPL-3.0-only
// This function checks if the player collides with the specified entity
// and from which direction.
// w and h holds the collider size of the entity
// while flags stores which sides are solid
s32 GetPlayerCollisionWith(Entity* entity, u16 w, u16 h, u16 flags) {
    Collider col;
    Entity* pl;
    s16 x;
    s16 y;
    u16 checks;
    s32 plStatus;

    pl = &PLAYER;
    plStatus = g_Player.unk0C;
    x = entity->posX.i.hi;
    y = entity->posY.i.hi;
    if (x > 0x120 || x < -0x20 || y < -0x180 || y > 0x180) {
        return 0;
    }

    x = pl->posX.i.hi - x;
    y = pl->posY.i.hi - y;
    if (entity->facingLeft) {
        x += entity->hitboxOffX;
    } else {
        x -= entity->hitboxOffX;
    }
    y -= entity->hitboxOffY;

    g_api.func_8010BF64(&col); // get player collision size
    w += col.unk14;
    h += col.unk18;
    if (x > 0) {
        checks = 1;
    } else {
        checks = 0;
    }
    if (y > 0) {
        checks |= 2;
    }

    x += w;
    y += h;
    w += w;
    h += h;
    if ((u16)x > w || (u16)y > h) {
        // pass
    } else {
        if (x && x != w) {
            // check collision from top
            if (flags & 4 && checks ^ 2 && pl->velocityY >= 0 && y < 8) {
                pl->posY.i.hi -= y;
                D_80097488.y.i.hi -= y;
                g_Player.pl_vram_flag |= 0x41;
                if (plStatus &
                    (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM)) {
                    return 0;
                } else {
                    return 4;
                }
            }

            // check collision from bottom
            if (flags & 2 && checks & 2 &&
                (pl->velocityY <= 0 || flags & 0x10)) {
                y = (s16)h - y;
                if (y < 0x10) {
                    pl->posY.i.hi += y;
                    D_80097488.y.i.hi += y;
                    g_Player.pl_vram_flag |= 0x42;
                    if (plStatus &
                        (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM)) {
                        return 0;
                    } else {
                        return 2;
                    }
                }
            }
        }

        // check collision from the sides
        if (y && y != h && flags & 1) {
            if (checks & 1) {
                x = (s16)w - x;
                if (flags & 8 && x > 2) {
                    x = 2;
                }
                pl->posX.i.hi += x;
                D_80097488.x.i.hi += x;
                g_Player.pl_vram_flag |= 0x48;
                return 1;
            } else {
                if (flags & 8 && (s16)x > 2) {
                    x = 2;
                }
                pl->posX.i.hi -= x;
                D_80097488.x.i.hi -= x;
                g_Player.pl_vram_flag |= 0x44;
                return 1;
            }
        }
    }
    return 0;
}
