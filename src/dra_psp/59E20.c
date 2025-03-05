// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

void func_8012C600(void) {
    s32 x, y;
    s32 i;
    s32 t0 = PLAYER.posX.i.hi;
    s32 t1 = PLAYER.posY.i.hi;

    x = g_Entities[20].posX.i.hi + 8;
    for (i = 0; i < 9; i++) {
        if (x <= g_Entities[i + 21].posX.i.hi + 4) {
            x = g_Entities[i + 21].posX.i.hi + 4;
        }
    }
    D_8013AEBC[0] = x - t0;

    x = g_Entities[20].posX.i.hi - 8;
    for (i = 0; i < 9; i++) {
        if (x >= g_Entities[i + 21].posX.i.hi - 4) {
            x = g_Entities[i + 21].posX.i.hi - 4;
        }
    }
    D_8013AEBC[2] = x - t0;

    y = g_Entities[21].posY.i.hi;
    for (i = 0; i < 9; i++) {
        if (y >= g_Entities[i + 21].posY.i.hi) {
            y = g_Entities[i + 21].posY.i.hi;
        }
    }
    y = y - 4;
    if (y >= g_Entities[30].posY.i.hi - 12) {
        y = g_Entities[30].posY.i.hi - 12;
    }
    if (y >= g_Entities[20].posY.i.hi - 8) {
        y = g_Entities[20].posY.i.hi - 8;
    }
    D_8013AEBC[3] = y - t1;
    if (D_8013AEBC[3] < -24) {
        D_8013AEBC[3] = -24;
    }

    y = g_Entities[21].posY.i.hi;
    for (i = 0; i < 9; i++) {
        if (y <= g_Entities[i + 21].posY.i.hi) {
            y = g_Entities[i + 21].posY.i.hi;
        }
    }
    y = y + 4;

    if (y <= PLAYER.posY.i.hi + 28) {
        y = PLAYER.posY.i.hi + 28;
    }
    if (y <= g_Entities[17].posY.i.hi + 28) {
        y = g_Entities[17].posY.i.hi + 28;
    }
    D_8013AEBC[1] = y - t1;
    if (D_8013AEBC[1] > 0x27) {
        D_8013AEBC[1] = 0x27;
    }

    if (!PLAYER.facingLeft) {
        if (D_8013AEBC[2] < -0x2C) {
            D_8013AEBC[2] = -0x2C;
        }
        if (D_8013AEBC[0] > 0x13) {
            D_8013AEBC[0] = 0x13;
        }
    } else {
        if (D_8013AEBC[2] < -0x13) {
            D_8013AEBC[2] = -0x13;
        }
        if (D_8013AEBC[0] > 0x2C) {
            D_8013AEBC[0] = 0x2C;
        }
    }
}

bool WolfFormFinished(void) {
    if (PLAYER.step_s == 0 || PLAYER.step_s == 8) {
        return false;
    }
    if (D_80097448[1] != 0 && !IsRelicActive(RELIC_HOLY_SYMBOL) ||
        g_Player.padTapped & PAD_L1 ||
        HandleTransformationMP(FORM_WOLF, REDUCE) < 0) {
        SetPlayerStep(Player_UnmorphWolf);
        SetPlayerAnim(0xCA);
        D_800AFDA4[1] = 1;
        PLAYER.palette = 0x810D;
        g_Player.unk66 = 0;
        g_Player.unk68 = 0;
        // Create factory for EntityPlayerBlinkWhite
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(44, 0x24), 0);
        PLAYER.velocityY >>= 1;
        return true;
    }
    return false;
}

void func_8012C97C(void) {
    if (g_Entities[PLAYER_CHARACTER].step_s == 0 || 
        g_Entities[PLAYER_CHARACTER].step_s == 8 ||
        g_Entities[PLAYER_CHARACTER].step_s == 9) {
        return;
    }
    if (D_80097448[1] <= 12) {
        return;
    }
    if (!IsRelicActive(RELIC_HOLY_SYMBOL)) {
        return;
    }
    if (!IsRelicActive(RELIC_SKILL_OF_WOLF)) {
        return;
    }
    if (g_Player.pl_vram_flag & 1) {
        return;
    }
    if (!(g_Player.padPressed & PAD_TRIANGLE)) {
        return;
    }
    if (D_80138440 != 0) {
        return;
    }

    PLAYER.step_s = 9;
    D_800B0914 = 0;
    SetPlayerAnim(0xEC);
    PLAYER.velocityY = 0;
}

void func_8012CA64(void) {
    s32 anim = 0xDE;

    PLAYER.step_s = 1;
    D_800B0914 = 0;

    if (g_Player.pl_vram_flag & 0x20) {
        anim++;
    }
    SetPlayerAnim(anim);

    PLAYER.velocityX /= 2;
    PLAYER.velocityY = 0;

    D_800B0918 = 0x200;
    if (g_Player.pl_vram_flag & 0x40) {
        D_800B0914 = 1;
        SetPlayerAnim(0xE9);
    }
}

void func_8012CB0C(void) {
    PLAYER.velocityY = 0;
    PLAYER.animFrameDuration = PLAYER.animFrameIdx = D_800B0914 = 0;
    PLAYER.ext.player.anim = 0xDE;
    PLAYER.step_s = 7;
}

void func_8012CB4C(void) {
    PLAYER.step_s = 2;
    if ((PLAYER.facingLeft && g_Player.padPressed & PAD_RIGHT) ||
        (!PLAYER.facingLeft && g_Player.padPressed & PAD_LEFT)) {
        SetPlayerAnim(0xE1);
        D_800B0914 = 0;
        D_8013842C = 0;
    } else if (D_8013842C != 0) {
        SetPlayerAnim(0xE2);
        D_800B0914 = 2;

        // This is a weird phantom call that only happens on PSP.
        abs(PLAYER.velocityX < FIX(2));
        
        SetSpeedX(FIX(2));
    } else {
        SetPlayerAnim(0xE0);
        D_800B0914 = 1;
        D_8013842C = 0xC;
    }
}

void func_8012CC30(s32 arg0) {
    if (arg0 == 0) {
        D_80138444 = 1;
        if (g_ButtonCombo[COMBO_QCF].buttonsCorrect == COMBO_COMPLETE &&
            IsRelicActive(RELIC_SKILL_OF_WOLF) &&
            CastSpell(SPELL_WOLF_CHARGE)) {
            CheckMoveDirection();
            PLAYER.step_s = 2;
            D_800B0914 = 4;
            SetSpeedX(FIX(5));
            g_CurrentEntity->velocityY = 0;
            SetPlayerAnim(0xED);
            LearnSpell(SPELL_WOLF_CHARGE);
        }
    } else {
        D_80138444 = 1;
    }
}

void func_8012CCE4(void) {
    PLAYER.velocityY = FIX(-3.5);
    if ((PLAYER.step_s == 2) & (D_800B0914 == 2)) {
        SetPlayerAnim(0xE7);
        if (PLAYER.facingLeft) {
            if ((g_Player.pl_vram_flag & 0xF000) == 0xC000) {
                PLAYER.velocityY = -(abs(PLAYER.velocityX) + FIX(3.5));
            }
            if ((g_Player.pl_vram_flag & 0xF000) == 0x8000) {
                PLAYER.velocityY = FIX(-0.5);
            }
        } else {
            if ((g_Player.pl_vram_flag & 0xF000) == 0x8000) {
                PLAYER.velocityY = -(abs(PLAYER.velocityX) + FIX(3.5));
            }
            if ((g_Player.pl_vram_flag & 0xF000) == 0xC000) {
                PLAYER.velocityY = FIX(-0.5);
            }
        }
        D_800B0914 = 2;
    } else if (
        (g_Player.padPressed & (PAD_RIGHT | PAD_LEFT)) &&
        ((PLAYER.step_s != 2) || (D_800B0914 != 0)) && (PLAYER.step_s != 9)) {
        SetPlayerAnim(0xE7);
        D_800B0914 = 1;
        if (g_Player.padPressed & PAD_UP) {
            PLAYER.velocityY = FIX(-4.875);
        }
    } else {
        SetPlayerAnim(0xE6);
        D_800B0914 = 0;
        if (g_Player.padPressed & PAD_UP) {
            PLAYER.velocityY = FIX(-4.875);
        }
    }
    PLAYER.step_s = 4;
    D_80138430 += 0x80;
}

void func_8012CED4(void) {
    if (PLAYER.step_s == 2 && D_800B0914 == 2) {
        SetPlayerAnim(0xE7);
        D_800B0914 = 1;
    } else {
        SetPlayerAnim(0xE8);
        SetSpeedX(FIX(1));
        D_800B0914 = 0;
        if (D_80138438 & 0x40) {
            PLAYER.velocityX = 0;
            PLAYER.animFrameIdx = 4;
            PLAYER.animFrameDuration = 1;
        }
    }
    PLAYER.step_s = 5;
    D_80138430 -= 0x100;
    g_Player.timers[ALU_T_5] = 8;
    PLAYER.velocityY = 0;
}

void func_8012CFA8(void) {
    SetPlayerAnim(0xEA);
    D_800B0914 = 0;
    PLAYER.velocityX = 0;
    PLAYER.step_s = 6;
    g_Player.timers[ALU_T_5] = 8;
}

void func_8012CFF0(void) {
    PLAYER.step_s = 3;
    SetPlayerAnim(0xE3);
    D_800B0914 = 0;
}

// func_8012D024
INCLUDE_ASM("dra_psp/psp/dra_psp/59E20", func_psp_091374D0);
// func_8012D178
INCLUDE_ASM("dra_psp/psp/dra_psp/59E20", func_psp_09137668);
// func_8012D28C (confirmed)
INCLUDE_ASM("dra_psp/psp/dra_psp/59E20", func_psp_09137748);
