// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rcat/rcat.h"

extern EInit g_EInitSpawner;

void func_us_801B1F1C(Entity* self) {
    FntPrint("col step %x\n", self->step);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        if (self->params) {
            g_Tilemap.flags &= (u16)~LAYER_SEMI_TRANS;
            DestroyEntity(self);
            break;
        }

        g_Tilemap.flags |= LAYER_SEMI_TRANS;
        g_api.func_800EA5E4(ANIMSET_OVL(4));
        g_api.func_800EA5E4(ANIMSET_OVL(6));
        g_api.func_800EA5E4(ANIMSET_OVL(7));
        g_api.func_800EA5E4(ANIMSET_OVL(8));
        self->step = 4;
        break;
    case 1:
        g_api.func_800EA5E4(0xA003);
        g_api.func_800EA5E4(0xA005);
        self->step++;
        break;
    case 2:
        if (g_CastleFlags[RCAT_SPIKE_ROOM_LIT]) {
            g_api.func_800EA538(3);
            self->step++;
        }
        break;
    case 3:
        g_Tilemap.flags |= LAYER_SEMI_TRANS;
        g_api.func_800EA5E4(ANIMSET_OVL(4));
        g_api.func_800EA5E4(ANIMSET_OVL(6));
        g_api.func_800EA5E4(ANIMSET_OVL(7));
        g_api.func_800EA5E4(ANIMSET_OVL(8));
        g_api.func_800EA5E4(ANIMSET_OVL(11));
        self->step++;
        break;
    case 4:
        g_Tilemap.flags |= LAYER_SEMI_TRANS;
        break;
    }
}
