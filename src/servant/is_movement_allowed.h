// SPDX-License-Identifier: AGPL-3.0-or-later
s32 IsMovementAllowed(s32 arg0) {
    if (PLAYER.velocityY < 0 && !(g_Player.pl_vram_flag & 1)) {
        return 1;
    }

    if (PLAYER.velocityY > 0 && !(g_Player.pl_vram_flag & 2)) {
        return 1;
    }

    if (PLAYER.velocityX < 0 && !(g_Player.pl_vram_flag & 8))
        return 1;

    if (PLAYER.velocityX > 0 && !(g_Player.pl_vram_flag & 4))
        return 1;

    if (arg0 == 0)
        return 0;

    if (g_Player.prev_step != PLAYER.step || PLAYER.step != Player_Stand)
        return 1;

    if (g_Player.prev_step_s != PLAYER.step_s)
        return 1;

    if (PLAYER.step_s != 0 && PLAYER.step_s != 4)
        return 1;

    return 0;
}
