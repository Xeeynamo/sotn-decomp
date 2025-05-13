// SPDX-License-Identifier: AGPL-3.0-or-later
// Appears totally unused. Never created by any entity creation call,
// doesn't show up in the e_layout either.
void EntityTilemapShufflerUnused(Entity* self) {
    u16 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        break;
    case 1:
        temp = g_Tilemap.fg[9];
        g_Tilemap.fg[6] = temp;
        temp = g_Tilemap.fg[10];
        g_Tilemap.fg[7] = temp;
        temp = g_Tilemap.fg[0x39];
        g_Tilemap.fg[0x36] = temp;
        temp = g_Tilemap.fg[0x3A];
        g_Tilemap.fg[0x37] = temp;
        temp = g_Tilemap.fg[0x69];
        g_Tilemap.fg[0x66] = temp;
        temp = g_Tilemap.fg[0x6A];
        g_Tilemap.fg[0x67] = temp;
        self->step++;
        break;
    }
}
