// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"

void func_8012C600(void) {
#ifdef VERSION_PSP
    const s32 limiting_value = 0x13;
#else
    const s32 limiting_value = 0x14;
#endif

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
        if (D_8013AEBC[0] > limiting_value) {
            D_8013AEBC[0] = limiting_value;
        }
    } else {
        if (D_8013AEBC[2] < -limiting_value) {
            D_8013AEBC[2] = -limiting_value;
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
        g_Player.padTapped & BTN_WOLF ||
        HandleTransformationMP(FORM_WOLF, REDUCE) < 0) {
        SetPlayerStep(Player_UnmorphWolf);
        SetPlayerAnim(0xCA);
        D_800AFDA4[0].pose = 1;
        PLAYER.palette = 0x810D;
        g_Player.unk66 = 0;
        g_Player.unk68 = 0;
        // Create factory for EntityPlayerBlinkWhite
        CreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x24), 0);
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
    if (g_Player.vram_flag & TOUCHING_GROUND) {
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

    if (g_Player.vram_flag & IN_AIR_OR_EDGE) {
        anim++;
    }
    SetPlayerAnim(anim);

    PLAYER.velocityX /= 2;
    PLAYER.velocityY = 0;

    D_800B0918 = 0x200;
    if (g_Player.vram_flag & VRAM_FLAG_UNK40) {
        D_800B0914 = 1;
        SetPlayerAnim(0xE9);
    }
}

void func_8012CB0C(void) {
    PLAYER.velocityY = 0;
    PLAYER.poseTimer = PLAYER.pose = D_800B0914 = 0;
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
            if ((g_Player.vram_flag &
                 (TOUCHING_ANY_SLOPE | TOUCHING_RAISING_SLOPE |
                  VRAM_FLAG_UNK2000 | TOUCHING_SLIGHT_SLOPE)) ==
                (TOUCHING_ANY_SLOPE | TOUCHING_RAISING_SLOPE)) {
                PLAYER.velocityY = -(abs(PLAYER.velocityX) + FIX(3.5));
            }
            if ((g_Player.vram_flag &
                 (TOUCHING_ANY_SLOPE | TOUCHING_RAISING_SLOPE |
                  VRAM_FLAG_UNK2000 | TOUCHING_SLIGHT_SLOPE)) ==
                TOUCHING_ANY_SLOPE) {
                PLAYER.velocityY = FIX(-0.5);
            }
        } else {
            if ((g_Player.vram_flag &
                 (TOUCHING_ANY_SLOPE | TOUCHING_RAISING_SLOPE |
                  VRAM_FLAG_UNK2000 | TOUCHING_SLIGHT_SLOPE)) ==
                TOUCHING_ANY_SLOPE) {
                PLAYER.velocityY = -(abs(PLAYER.velocityX) + FIX(3.5));
            }
            if ((g_Player.vram_flag &
                 (TOUCHING_ANY_SLOPE | TOUCHING_RAISING_SLOPE |
                  VRAM_FLAG_UNK2000 | TOUCHING_SLIGHT_SLOPE)) ==
                (TOUCHING_ANY_SLOPE | TOUCHING_RAISING_SLOPE)) {
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
            PLAYER.pose = 4;
            PLAYER.poseTimer = 1;
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

void func_8012D024(void) {
    DecelerateX(FIX(1.0 / 8));
    if (g_Player.padTapped & PAD_CROSS) {
        func_8012CCE4();
        return;
    }
    if (!(g_Player.vram_flag & TOUCHING_GROUND)) {
        func_8012CED4();
        return;
    }
    if (g_Player.padTapped & WOLF_CHARGE_ATK_BTN) {
        func_8012CC30(0);
        return;
    }
    if (g_Player.padPressed & (PAD_RIGHT | PAD_LEFT)) {
        func_8012CB4C();
        return;
    }
    if (g_Player.padPressed & PAD_DOWN) {
        func_8012CFF0();
        return;
    }
    switch (D_800B0914) {
    case 0:
        if (abs(PLAYER.posY.i.hi - g_Entities[17].posY.i.hi) < 4 &&
            --D_800B0918 == 0) {
            D_800B0914 = 1;
            SetPlayerAnim(0xE9);
        } else if (g_Player.vram_flag & VRAM_FLAG_UNK40) {
            D_800B0914 = 1;
            SetPlayerAnim(0xE9);
        }
    case 1:
        return;
    }
}

void func_8012D178(void) {
    if (g_Player.padTapped & PAD_CROSS) {
        func_8012CCE4();
    } else if (!(g_Player.vram_flag & TOUCHING_GROUND)) {
        func_8012CFA8();
    } else {
#ifdef VERSION_US
        if (PLAYER.facingLeft) {
            if (g_Player.padPressed & PAD_LEFT) {
                func_8012CB4C();
                return;
            }
        } else {
            if (g_Player.padPressed & PAD_RIGHT) {
                func_8012CB4C();
                return;
            }
        }
#else
        if (g_Player.padPressed & (PAD_LEFT | PAD_RIGHT)) {
            func_8012CB4C();
            return;
        }
#endif
        if (g_Player.unk04 & 0x40) {
            func_8012CA64();
        } else if (g_GameTimer % 6 == 0) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_69, 1), 0);
        }
    }
}

void func_8012D28C(bool exitEarly) {
    bool bitNotFound;
    s32 i;

    func_80102CD8(2);
    PlaySfx(SFX_WALL_DEBRIS_B);
    PLAYER.velocityX = 0;
    g_Player.demo_timer = 32;
    g_Player.padSim = 0;
    // Odd logic, if we exit early, we force an R2-tap. Strange!
    if (exitEarly) {
        g_Player.padTapped = BTN_WOLF;
        WolfFormFinished();
        return;
    }
    // Start a routine where we look through this array for a value.
    bitNotFound = 0;
    for (i = 3; i < NUM_VERTICAL_SENSORS; i++) {
        if (g_Player.colWall[i].effects & EFFECT_UNK_0002) {
            break;
        }
    }
    // If we made it through that loop without finding one, skip i=7,8,9
    // and keep searching.
    if (i == 7) {
        for (i = NUM_VERTICAL_SENSORS + 3; i < NUM_VERTICAL_SENSORS * 2; i++) {
            if (g_Player.colWall[i].effects & EFFECT_UNK_0002) {
                break;
            }
        }
    }
    // If we even made it through that one, then conclude the bit was not found.
    if (i == 14) {
        bitNotFound++;
    }

    SetSpeedX(FIX(1));
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_4, 9), 0);
    D_800B0914 = 0;
    // Finally make use of that bit to control if X is positive or negative.
    if (bitNotFound) {
        func_8012CED4();
        SetSpeedX(FIX(1));
        PLAYER.velocityY = FIX(-3.5);
    } else {
        func_8012CFA8();
        SetSpeedX(FIX(-1));
        PLAYER.velocityY = FIX(-3.5);
    }
}
