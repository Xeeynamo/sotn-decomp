#include "nz0.h"

void func_801B8E0C(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BEC);
        D_8003C8B8 = 0;
        g_unkGraphicsStruct.unk0 = 1;
        g_Player.padSim = PAD_LEFT;
        if (g_Player.unk0C & PLAYER_STATUS_WOLF_FORM) {
            g_Player.padSim = PAD_R2;
        }
        g_Player.D_80072EFC = 1;
        break;

    case 1:
        if (PLAYER.posX.i.hi < 176) {
            g_Player.padSim = 0;
            self->step++;
        } else {
            g_Player.padSim = 0;
            if (g_Player.unk0C & PLAYER_STATUS_WOLF_FORM) {
                if (g_Timer & 1) {
                    g_Player.padSim = PAD_R2;
                }
            } else {
                g_Player.padSim = PAD_LEFT;
            }
        }
        g_Player.D_80072EFC = 1;
        break;

    case 2:
        if (D_801CB734 & 0x2000) {
            D_8003C8B8 = 1;
            if (g_unkGraphicsStruct.unk0 != 0) {
                g_unkGraphicsStruct.unk0 = 0;
            }
            DestroyEntity(self);
        }
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        break;
    }
}

INCLUDE_ASM("st/nz0/nonmatchings/38E0C", func_801B8F94);