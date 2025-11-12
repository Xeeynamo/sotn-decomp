// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../cat/cat.h"

extern EInit g_EInitSpawner;

INCLUDE_ASM("st/cat_psp/nonmatchings/cat_psp/unk_28C10", func_us_801BB4CC);

INCLUDE_ASM("st/cat_psp/nonmatchings/cat_psp/unk_28C10", func_us_801BA164);

INCLUDE_ASM("st/cat_psp/nonmatchings/cat_psp/unk_28C10", func_us_801BA388);

INCLUDE_ASM("st/cat_psp/nonmatchings/cat_psp/unk_28C10", func_us_801B732C);

void func_us_801B8AD0(Entity* self) {
    FntPrint("col step %x\n", self->step);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        if (self->params) {
            g_api.func_800EA5E4(0x800B);
            g_Tilemap.flags &= (u16)~LAYER_SEMI_TRANS;
            DestroyEntity(self);
            break;
        }

        if (g_CastleFlags[CAT_SPIKE_ROOM_LIT]) {
            g_Tilemap.flags |= LAYER_SEMI_TRANS;
            g_api.func_800EA5E4(0x8004);
            g_api.func_800EA5E4(0x8006);
            g_api.func_800EA5E4(0x8007);
            g_api.func_800EA5E4(0x8008);
            g_api.func_800EA5E4(0x800B);
            self->step = 4;
            break;
        }

        g_Tilemap.flags &= (u16)~LAYER_SEMI_TRANS;
        g_api.func_800EA5E4(0x800A);
        break;
    case 1:
        g_api.func_800EA5E4(0xA003);
        g_api.func_800EA5E4(0xA005);
        self->step++;
        break;
    case 2:
        if (g_CastleFlags[CAT_SPIKE_ROOM_LIT]) {
            g_api.func_800EA538(3);
            self->step++;
        }
        break;
    case 3:
        g_Tilemap.flags |= LAYER_SEMI_TRANS;
        g_api.func_800EA5E4(0x8004);
        g_api.func_800EA5E4(0x8006);
        g_api.func_800EA5E4(0x8007);
        g_api.func_800EA5E4(0x8008);
        g_api.func_800EA5E4(0x800B);
        self->step++;
        break;
    case 4:
        g_Tilemap.flags |= LAYER_SEMI_TRANS;
        break;
    }
}
