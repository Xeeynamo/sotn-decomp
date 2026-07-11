// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitCommon;

// block to determine richter fight
void func_us_801A9250(Entity* self) {
    FntPrint("step:%02x\n", self->step);
    FntPrint("p_x:%02x\n", PLAYER.posX.i.hi);

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        break;

    case 1:
        if (PLAYER.posX.i.hi < 8 &&
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_SAVE_RICHTER, TIMEATTACK_GET_RECORD) == 0) {
            g_Player.padSim = PAD_LEFT;
            g_Player.demo_timer = 10;
            g_Tilemap.left += 4;
            g_PlayerX -= 0x400;
            self->step++;
        }
        break;

    case 2:
        g_Player.padSim = PAD_LEFT;
        g_Player.demo_timer = 10;
        break;
    }
}
