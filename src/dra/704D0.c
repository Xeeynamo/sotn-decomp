#include "dra.h"
#include "dra_bss.h"
#include "sfx.h"
#include "player.h"

bool CheckGravityBootsInput(void) {
    switch (g_ButtonCombo[COMBO_GRAVITY_BOOTS].buttonsCorrect) {
    case 0:
        if ((g_Player.padTapped & PAD_DOWN) && (g_Player.padHeld == 0)) {
            g_ButtonCombo[COMBO_GRAVITY_BOOTS].timer = 16;
            g_ButtonCombo[COMBO_GRAVITY_BOOTS].buttonsCorrect++;
        }
        break;
    case 1:
        if (g_Player.padTapped & PAD_UP) {
            g_ButtonCombo[COMBO_GRAVITY_BOOTS].timer = 16;
            g_ButtonCombo[COMBO_GRAVITY_BOOTS].buttonsCorrect++;
        } else {
            if (--g_ButtonCombo[COMBO_GRAVITY_BOOTS].timer == 0) {
                g_ButtonCombo[COMBO_GRAVITY_BOOTS].buttonsCorrect = 0;
            }
        }
        break;
    case 2:
        if ((g_ButtonCombo[COMBO_GRAVITY_BOOTS].timer != 0) &&
            --g_ButtonCombo[COMBO_GRAVITY_BOOTS].timer == 0) {
            g_ButtonCombo[COMBO_GRAVITY_BOOTS].buttonsCorrect = 0;
            break;
        }
        if (IsRelicActive(RELIC_GRAVITY_BOOTS) &&
            (g_Player.padTapped & PAD_CROSS) && !(g_Player.unk46 & 0x8000) &&
            ((PLAYER.step == Player_Crouch) ||
             ((PLAYER.step == Player_Jump) && (g_Player.unk44 & 1)))) {
            if (g_Player.unk72 == 0) {
                if (HandleGravityBootsMP(REDUCE) >= 0) {
                    DoGravityJump();
                    g_ButtonCombo[COMBO_GRAVITY_BOOTS].buttonsCorrect = 0;
                    return 1;
                }
            } else {
                g_ButtonCombo[COMBO_GRAVITY_BOOTS].buttonsCorrect = 0;
            }
        }
        break;
    }
    return 0;
}

// Used for wolf charge, and for weapons which have a move using this pattern
bool CheckQuarterCircleForwardInput(void) {
    s32 directionsPressed;
    s32 down_forward;
    s32 forward;

    directionsPressed =
        g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    if (!g_WasFacingLeft) {
        forward = PAD_RIGHT;
    } else {
        forward = PAD_LEFT;
    }
    if (!g_WasFacingLeft) {
        down_forward = PAD_DOWN + PAD_RIGHT;
    } else {
        down_forward = PAD_DOWN + PAD_LEFT;
    }
    switch (g_ButtonCombo[COMBO_QCF].buttonsCorrect) {
    case 0:
        g_WasFacingLeft = PLAYER.facingLeft;
        if (directionsPressed == PAD_DOWN) {
            g_ButtonCombo[COMBO_QCF].timer = 20;
            g_ButtonCombo[COMBO_QCF].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_QCF].timer == 0) {
            g_ButtonCombo[COMBO_QCF].buttonsCorrect = 0;
        }
        break;
    case 1:
        if (directionsPressed == down_forward) {
            g_ButtonCombo[COMBO_QCF].timer = 20;
            g_ButtonCombo[COMBO_QCF].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_QCF].timer == 0) {
            g_ButtonCombo[COMBO_QCF].buttonsCorrect = 0;
        }
        break;
    case 2:
        if (directionsPressed == forward) {
            g_ButtonCombo[COMBO_QCF].timer = 20;
            g_ButtonCombo[COMBO_QCF].buttonsCorrect = COMBO_COMPLETE;
            break;
        }
        if (--g_ButtonCombo[COMBO_QCF].timer == 0) {
            g_ButtonCombo[COMBO_QCF].buttonsCorrect = 0;
        }
        break;
    default:
        if (g_ButtonCombo[COMBO_QCF].timer != 0) {
            if (g_Player.unk72 != 0) {
                g_ButtonCombo[COMBO_QCF].buttonsCorrect = 0;
                break;
            }
            if (--g_ButtonCombo[1].timer == 0) {
                g_ButtonCombo[COMBO_QCF].buttonsCorrect = 0;
                g_WasFacingLeft = PLAYER.facingLeft;
            }
        }
    }
    return 0;
}

bool CheckBackForwardInput(void) {
    s32 directionsPressed;
    s32 backward;
    s32 forward;

    directionsPressed =
        g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    if (!g_WasFacingLeft2) {
        forward = PAD_RIGHT;
    } else {
        forward = PAD_LEFT;
    }
    switch (g_ButtonCombo[COMBO_BF].buttonsCorrect) {
    case 0:
        g_WasFacingLeft2 = PLAYER.facingLeft;
        if (!g_WasFacingLeft2) {
            backward = PAD_LEFT;
        } else {
            backward = PAD_RIGHT;
        }
        if (directionsPressed == backward) {
            g_ButtonCombo[COMBO_BF].timer = 15;
            g_ButtonCombo[COMBO_BF].buttonsCorrect++;
        } else if (--g_ButtonCombo[COMBO_BF].timer == 0) {
            g_ButtonCombo[COMBO_BF].buttonsCorrect = 0;
        }
        break;
    case 1:
        if (directionsPressed == forward) {
            g_ButtonCombo[COMBO_BF].timer = 15;
            g_ButtonCombo[COMBO_BF].buttonsCorrect = COMBO_COMPLETE;
            break;
        } else if (--g_ButtonCombo[COMBO_BF].timer == 0) {
            g_ButtonCombo[COMBO_BF].buttonsCorrect = 0;
        }
        break;
    case 2:
    default:
        if (g_Player.unk72 != 0) {
            g_ButtonCombo[COMBO_BF].buttonsCorrect = 0;
            break;
        }
        if (g_ButtonCombo[COMBO_BF].timer != 0 &&
            --g_ButtonCombo[COMBO_BF].timer == 0) {
            g_ButtonCombo[COMBO_BF].buttonsCorrect = 0;
            g_WasFacingLeft2 = PLAYER.facingLeft;
        }
    }
    return 0;
}

bool CheckDarkMetamorphosisInput(void) {
    s32 directionsPressed;
    s32 up_back;
    s32 up_forward;
    s32 forward;
    s32 up;

    directionsPressed =
        g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    if (!g_WasFacingLeft3) {
        up_forward = PAD_UP + PAD_RIGHT;
        forward = PAD_RIGHT;
        up_back = PAD_UP + PAD_LEFT;
    } else {
        up_forward = PAD_UP + PAD_LEFT;
        forward = PAD_LEFT;
        up_back = PAD_UP + PAD_RIGHT;
    }
    up = PAD_UP;

    switch (g_ButtonCombo[COMBO_DARK_METAMORPH].buttonsCorrect) {
    case 0:
        if (!PLAYER.facingLeft) {
            if (g_Player.padTapped & PAD_LEFT) {
                g_ButtonCombo[COMBO_DARK_METAMORPH].timer = 20;
                g_WasFacingLeft3 = 0;
                g_ButtonCombo[COMBO_DARK_METAMORPH].buttonsCorrect++;
            }
            break;
        }
        if (g_Player.padTapped & PAD_RIGHT) {
            g_ButtonCombo[COMBO_DARK_METAMORPH].timer = 20;
            g_WasFacingLeft3 = 1;
            g_ButtonCombo[COMBO_DARK_METAMORPH].buttonsCorrect++;
        }
        break;
    case 1:
        if ((up_back & g_Player.padPressed) == up_back) {
            g_ButtonCombo[COMBO_DARK_METAMORPH].timer = 20;
            g_ButtonCombo[COMBO_DARK_METAMORPH].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_DARK_METAMORPH].timer == 0) {
            g_ButtonCombo[COMBO_DARK_METAMORPH].buttonsCorrect = 0;
        }
        break;
    case 2:
        if (g_Player.padPressed == up) {
            g_ButtonCombo[COMBO_DARK_METAMORPH].timer = 20;
            g_ButtonCombo[COMBO_DARK_METAMORPH].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_DARK_METAMORPH].timer == 0) {
            g_ButtonCombo[COMBO_DARK_METAMORPH].buttonsCorrect = 0;
        }
        break;
    case 3:
        if ((directionsPressed & up_forward) == up_forward) {
            g_ButtonCombo[COMBO_DARK_METAMORPH].timer = 20;
            g_ButtonCombo[COMBO_DARK_METAMORPH].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_DARK_METAMORPH].timer == 0) {
            g_ButtonCombo[COMBO_DARK_METAMORPH].buttonsCorrect = 0;
        }
        break;
    case 4:
        if (directionsPressed == forward) {
            g_ButtonCombo[COMBO_DARK_METAMORPH].timer = 20;
            g_ButtonCombo[COMBO_DARK_METAMORPH].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_DARK_METAMORPH].timer == 0) {
            g_ButtonCombo[COMBO_DARK_METAMORPH].buttonsCorrect = 0;
        }
        break;
    case 5:
        if (--g_ButtonCombo[COMBO_DARK_METAMORPH].timer != 0) {
            if ((g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) &&
                !(g_Player.unk46 & 0x8000) &&
                ((PLAYER.step == Player_Walk) ||
                 (PLAYER.step == Player_Stand)) &&
                (CastSpell(SPELL_DARK_METAMORPHOSIS) != 0)) {
                func_8010FB68();
                g_ButtonCombo[COMBO_DARK_METAMORPH].buttonsCorrect = 0;
                LearnSpell(SPELL_DARK_METAMORPHOSIS);
                return 1;
            }
            break;
        }
        g_ButtonCombo[COMBO_DARK_METAMORPH].buttonsCorrect = 0;
    }
    return 0;
}

bool CheckSummonSpiritInput(void) {
    s32 directionsPressed;
    s32 forward;

    directionsPressed =
        g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    if (g_WasFacingLeft4) {
        forward = g_Player.padPressed & PAD_LEFT;
    } else {
        forward = g_Player.padPressed & PAD_RIGHT;
    }
    switch (g_ButtonCombo[COMBO_SUMMON_SPIRIT].buttonsCorrect) {
    case 0:
        if (!PLAYER.facingLeft) {
            if (g_Player.padTapped == PAD_LEFT) {
                g_ButtonCombo[COMBO_SUMMON_SPIRIT].timer = 20;
                g_WasFacingLeft4 = 0;
                g_ButtonCombo[COMBO_SUMMON_SPIRIT].buttonsCorrect++;
            }
            break;
        }
        if (g_Player.padTapped == PAD_RIGHT) {
            g_ButtonCombo[COMBO_SUMMON_SPIRIT].timer = 20;
            g_WasFacingLeft4 = 1;
            g_ButtonCombo[COMBO_SUMMON_SPIRIT].buttonsCorrect++;
        }
        break;
    case 1:
        if (directionsPressed == forward) {
            g_ButtonCombo[COMBO_SUMMON_SPIRIT].timer = 20;
            g_ButtonCombo[COMBO_SUMMON_SPIRIT].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_SUMMON_SPIRIT].timer == 0) {
            g_ButtonCombo[COMBO_SUMMON_SPIRIT].buttonsCorrect = 0;
        }
        break;

    case 2:
        if (directionsPressed == PAD_UP) {
            g_ButtonCombo[COMBO_SUMMON_SPIRIT].timer = 20;
            g_ButtonCombo[COMBO_SUMMON_SPIRIT].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_SUMMON_SPIRIT].timer == 0) {
            g_ButtonCombo[COMBO_SUMMON_SPIRIT].buttonsCorrect = 0;
        }
        break;
    case 3:
        if (directionsPressed == PAD_DOWN) {
            g_ButtonCombo[COMBO_SUMMON_SPIRIT].timer = 20;
            g_ButtonCombo[COMBO_SUMMON_SPIRIT].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_SUMMON_SPIRIT].timer == 0) {
            g_ButtonCombo[COMBO_SUMMON_SPIRIT].buttonsCorrect = 0;
        }
        break;
    case 4:
        if (--g_ButtonCombo[COMBO_SUMMON_SPIRIT].timer == 0) {
            g_ButtonCombo[COMBO_SUMMON_SPIRIT].buttonsCorrect = 0;
        }
        if ((g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) &&
            !(g_Player.unk46 & 0x8000) && (PLAYER.step == Player_Crouch) &&
            (CastSpell(SPELL_SUMMON_SPIRIT) != 0)) {
            func_8010FC50();
            g_ButtonCombo[COMBO_SUMMON_SPIRIT].buttonsCorrect = 0;
            LearnSpell(SPELL_SUMMON_SPIRIT);
            return 1;
        }
        break;
    }
    return 0;
}

bool CheckHellfireInput(void) {
    s32 directionsPressed;
    s32 down_forward;
    s32 forward;

    directionsPressed =
        g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    if (!g_WasFacingLeft5) {
        forward = PAD_RIGHT;
    } else {
        forward = PAD_LEFT;
    }

    if (!g_WasFacingLeft5) {
        down_forward = PAD_DOWN + PAD_RIGHT;
    } else {
        down_forward = PAD_DOWN + PAD_LEFT;
    }
    switch (g_ButtonCombo[COMBO_HELLFIRE].buttonsCorrect) {
    case 0:
        if (g_Player.padTapped == PAD_UP) {
            g_ButtonCombo[COMBO_HELLFIRE].timer = 20;
            g_ButtonCombo[COMBO_HELLFIRE].buttonsCorrect++;
        }
        break;
    case 1:
        if (directionsPressed == PAD_DOWN) {
            g_ButtonCombo[COMBO_HELLFIRE].timer = 21;
            g_ButtonCombo[COMBO_HELLFIRE].buttonsCorrect++;
            g_WasFacingLeft5 = PLAYER.facingLeft;
            break;
        }
        if (--g_ButtonCombo[COMBO_HELLFIRE].timer == 0) {
            g_ButtonCombo[COMBO_HELLFIRE].buttonsCorrect = 0;
        }
        break;
    case 2:
        if ((directionsPressed & down_forward) == down_forward) {
            g_ButtonCombo[COMBO_HELLFIRE].timer = 20;
            g_ButtonCombo[COMBO_HELLFIRE].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_HELLFIRE].timer == 0) {
            g_ButtonCombo[COMBO_HELLFIRE].buttonsCorrect = 0;
        }
        break;
    case 3:
        if (directionsPressed == forward) {
            g_ButtonCombo[COMBO_HELLFIRE].timer = 20;
            g_ButtonCombo[COMBO_HELLFIRE].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_HELLFIRE].timer == 0) {
            g_ButtonCombo[COMBO_HELLFIRE].buttonsCorrect = 0;
        }
        break;
    case 4:
        if ((g_ButtonCombo[COMBO_HELLFIRE].timer == 0) ||
            --g_ButtonCombo[COMBO_HELLFIRE].timer != 0) {
            FntPrint("pl_pose:%02x\n", PLAYER.animFrameIdx);
            if ((g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) &&
                !(g_Player.unk46 & 0x8000) &&
                ((PLAYER.step == Player_Crouch) ||
                 ((PLAYER.step == Player_Walk) ||
                  (PLAYER.step == Player_Stand)))) {
                if (g_Player.unk72 == 0) {
                    if (CastSpell(SPELL_HELLFIRE) == 0) {
                        return 0;
                    }
                    PerformHellfire();
                    g_ButtonCombo[COMBO_HELLFIRE].buttonsCorrect = 0;
                    LearnSpell(SPELL_HELLFIRE);
                    return 1;
                }
                g_ButtonCombo[COMBO_HELLFIRE].buttonsCorrect = 0;
            }
            return 0;
        }
        g_ButtonCombo[COMBO_HELLFIRE].buttonsCorrect = 0;
    }
    return 0;
}

bool CheckTetraSpiritInput(void) {
    s32 directionsPressed;
    s32 down_forward;
    s32 up_forward;
    s32 forward;

    directionsPressed =
        g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    if (!g_WasFacingLeft6) {
        forward = PAD_RIGHT;
    } else {
        forward = PAD_LEFT;
    }
    if (!g_WasFacingLeft6) {
        down_forward = PAD_DOWN + PAD_RIGHT;
    } else {
        down_forward = PAD_DOWN + PAD_LEFT;
    }
    if (!g_WasFacingLeft6) {
        up_forward = PAD_UP + PAD_RIGHT;
    } else {
        up_forward = PAD_UP + PAD_LEFT;
    }
    switch (g_ButtonCombo[COMBO_TETRA_SPIRIT].buttonsCorrect) {
    case 0:
        // Must hold UP for 32 frames
        if (g_Player.padTapped == PAD_UP) {
            g_ButtonCombo[COMBO_TETRA_SPIRIT].timer = 32;
            g_ButtonCombo[COMBO_TETRA_SPIRIT].buttonsCorrect++;
            break;
        }
        break;
    case 1:
        if (directionsPressed == PAD_UP) {
            // Counts down the required 32 frames before you go to step 2
            if (--g_ButtonCombo[COMBO_TETRA_SPIRIT].timer == 0) {
                g_ButtonCombo[COMBO_TETRA_SPIRIT].buttonsCorrect++;
                g_WasFacingLeft6 = PLAYER.facingLeft;
            }
            break;
        }
        g_ButtonCombo[COMBO_TETRA_SPIRIT].buttonsCorrect = 0;
        break;
    case 2:
        // After holding UP, you must let go for one frame to move to step 3
        if (directionsPressed != PAD_UP) {
            g_ButtonCombo[COMBO_TETRA_SPIRIT].buttonsCorrect++;
            g_ButtonCombo[COMBO_TETRA_SPIRIT].timer = 32;
        }
        // Precheck on case 3, so you can skip it to 4.
        if ((directionsPressed & up_forward) == up_forward) {
            g_ButtonCombo[COMBO_TETRA_SPIRIT].timer = 20;
            g_ButtonCombo[COMBO_TETRA_SPIRIT].buttonsCorrect = 4;
            break;
        }
        break;
    case 3:
        if ((directionsPressed & up_forward) == up_forward) {
            g_ButtonCombo[COMBO_TETRA_SPIRIT].timer = 20;
            g_ButtonCombo[COMBO_TETRA_SPIRIT].buttonsCorrect = 4;
            break;
        }
        if (--g_ButtonCombo[COMBO_TETRA_SPIRIT].timer == 0) {
            g_ButtonCombo[COMBO_TETRA_SPIRIT].buttonsCorrect = 0;
        }
        break;
    case 4:
        if (directionsPressed == forward) {
            g_ButtonCombo[COMBO_TETRA_SPIRIT].timer = 20;
            g_ButtonCombo[COMBO_TETRA_SPIRIT].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_TETRA_SPIRIT].timer == 0) {
            g_ButtonCombo[COMBO_TETRA_SPIRIT].buttonsCorrect = 0;
        }
        break;
    case 5:
        if ((directionsPressed & down_forward) == down_forward) {
            g_ButtonCombo[COMBO_TETRA_SPIRIT].timer = 20;
            g_ButtonCombo[COMBO_TETRA_SPIRIT].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_TETRA_SPIRIT].timer == 0) {
            g_ButtonCombo[COMBO_TETRA_SPIRIT].buttonsCorrect = 0;
        }
        break;
    case 6:
        if (directionsPressed == PAD_DOWN) {
            g_ButtonCombo[COMBO_TETRA_SPIRIT].timer = 20;
            g_ButtonCombo[COMBO_TETRA_SPIRIT].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_TETRA_SPIRIT].timer == 0) {
            g_ButtonCombo[COMBO_TETRA_SPIRIT].buttonsCorrect = 0;
        }
        break;
    case 7:
        if (--g_ButtonCombo[COMBO_TETRA_SPIRIT].timer == 0) {
            g_ButtonCombo[COMBO_TETRA_SPIRIT].buttonsCorrect = 0;
        }
        if ((g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) &&
            !(g_Player.unk46 & 0x8000) && (PLAYER.step == Player_Crouch) &&
            (CastSpell(SPELL_TETRA_SPIRIT) != 0)) {
            func_8010FCB8();
            g_ButtonCombo[COMBO_TETRA_SPIRIT].buttonsCorrect = 0;
            LearnSpell(SPELL_TETRA_SPIRIT);
            return 1;
        }
        break;
    }
    return 0;
}

bool CheckSoulStealInput(void) {
    s32 directionsPressed;
    s32 forward;
    s32 down_forward;
    s32 backward;
    s32 down_backward;
    s32 down;

    directionsPressed =
        g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    if (!g_WasFacingLeft7) {
        down_forward = PAD_DOWN + PAD_RIGHT;
        forward = PAD_RIGHT;
        backward = PAD_LEFT;
        down_backward = PAD_DOWN + PAD_LEFT;
    } else {
        down_forward = PAD_DOWN + PAD_LEFT;
        forward = PAD_LEFT;
        backward = PAD_RIGHT;
        down_backward = PAD_DOWN + PAD_RIGHT;
    }
    down = PAD_DOWN;
    switch (g_ButtonCombo[COMBO_SOUL_STEAL].buttonsCorrect) {
    case 0:
        if (!PLAYER.facingLeft) {
            if (g_Player.padTapped == PAD_LEFT) {
                g_ButtonCombo[COMBO_SOUL_STEAL].timer = 24;
                g_WasFacingLeft7 = 0;
                g_ButtonCombo[COMBO_SOUL_STEAL].buttonsCorrect++;
            }
            break;
        }
        if (g_Player.padTapped == PAD_RIGHT) {
            // @bug - Most spells use a 20-frame button timing. Soul Steal uses
            // 24. It appears that this spot was forgotten, meaning Soul Steal
            // is easier if you start facing right than left!
            g_ButtonCombo[COMBO_SOUL_STEAL].timer = 20;
            g_WasFacingLeft7 = 1;
            g_ButtonCombo[COMBO_SOUL_STEAL].buttonsCorrect++;
        }
        break;
    case 1:
        if (directionsPressed != forward) {
            if (--g_ButtonCombo[COMBO_SOUL_STEAL].timer == 0) {
                g_ButtonCombo[COMBO_SOUL_STEAL].buttonsCorrect = 0;
            }
            break;
        }
        g_ButtonCombo[COMBO_SOUL_STEAL].timer = 24;
        g_ButtonCombo[COMBO_SOUL_STEAL].buttonsCorrect++;
        break;
    case 2:
        if ((directionsPressed & down_forward) == down_forward) {
            g_ButtonCombo[COMBO_SOUL_STEAL].timer = 24;
            g_ButtonCombo[COMBO_SOUL_STEAL].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_SOUL_STEAL].timer == 0) {
            g_ButtonCombo[COMBO_SOUL_STEAL].buttonsCorrect = 0;
        }
        break;
    case 3:
        if (directionsPressed == down) {
            g_ButtonCombo[COMBO_SOUL_STEAL].timer = 24;
            g_ButtonCombo[COMBO_SOUL_STEAL].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_SOUL_STEAL].timer == 0) {
            g_ButtonCombo[COMBO_SOUL_STEAL].buttonsCorrect = 0;
        }
        break;
    case 4:
        if ((directionsPressed & down_backward) == down_backward) {
            g_ButtonCombo[COMBO_SOUL_STEAL].timer = 24;
            g_ButtonCombo[COMBO_SOUL_STEAL].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_SOUL_STEAL].timer == 0) {
            g_ButtonCombo[COMBO_SOUL_STEAL].buttonsCorrect = 0;
        }
        break;
    case 5:
        if (directionsPressed == backward) {
            g_ButtonCombo[COMBO_SOUL_STEAL].timer = 24;
            g_ButtonCombo[COMBO_SOUL_STEAL].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_SOUL_STEAL].timer == 0) {
            g_ButtonCombo[COMBO_SOUL_STEAL].buttonsCorrect = 0;
        }
        break;
    case 6:
        if (directionsPressed == forward) {
            g_ButtonCombo[COMBO_SOUL_STEAL].timer = 24;
            g_ButtonCombo[COMBO_SOUL_STEAL].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_SOUL_STEAL].timer == 0) {
            g_ButtonCombo[COMBO_SOUL_STEAL].buttonsCorrect = 0;
        }
        break;
    case 7:
        if (--g_ButtonCombo[COMBO_SOUL_STEAL].timer != 0) {
            if ((g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) &&
                !(g_Player.unk46 & 0x8000) &&
                ((PLAYER.step == Player_Walk) ||
                 (PLAYER.step == Player_Stand)) &&
                (CastSpell(SPELL_SOUL_STEAL) != 0)) {
                func_8010FBF4();
                g_ButtonCombo[COMBO_SOUL_STEAL].buttonsCorrect = 0;
                LearnSpell(SPELL_SOUL_STEAL);
                return 1;
            }
            break;
        }
        g_ButtonCombo[COMBO_SOUL_STEAL].buttonsCorrect = 0;
    }
    return 0;
}

bool CheckSwordBrothersInput(void) {
    s32 directionsPressed;
    s32 down_forward;
    s32 forward;
    s32 up_forward;

    directionsPressed =
        g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    if (!PLAYER.facingLeft) {
        down_forward = PAD_DOWN + PAD_RIGHT;
        forward = PAD_RIGHT;
        up_forward = PAD_UP + PAD_RIGHT;
    } else {
        down_forward = PAD_DOWN + PAD_LEFT;
        forward = PAD_LEFT;
        up_forward = PAD_UP + PAD_LEFT;
    }

    // Check if sword familiar is currently active. If not, prevent having
    // buttons correct
    if (g_Servant != FAM_ACTIVE_SWORD) {
        g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect = 0;
    }

    switch (g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect) {
    case 0:
        if (directionsPressed == PAD_DOWN) {
            g_ButtonCombo[COMBO_SWORD_BROTHERS].timer = 20;
            g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect++;
        }
        break;
    case 1:
        if (directionsPressed == down_forward) {
            g_ButtonCombo[COMBO_SWORD_BROTHERS].timer = 20;
            g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_SWORD_BROTHERS].timer == 0) {
            g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect = 0;
        }
        break;
    case 2:
        if (directionsPressed == forward) {
            g_ButtonCombo[COMBO_SWORD_BROTHERS].timer = 20;
            g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_SWORD_BROTHERS].timer == 0) {
            g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect = 0;
        }
        break;
    case 3:
        if (directionsPressed == up_forward) {
            g_ButtonCombo[COMBO_SWORD_BROTHERS].timer = 20;
            g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_SWORD_BROTHERS].timer == 0) {
            g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect = 0;
        }
        break;
    case 4:
        if (directionsPressed == PAD_UP) {
            g_ButtonCombo[COMBO_SWORD_BROTHERS].timer = 64;
            g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_SWORD_BROTHERS].timer == 0) {
            g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect = 0;
        }
        break;
    case 5:
        if (--g_ButtonCombo[COMBO_SWORD_BROTHERS].timer == 0) {
            g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect++;
            break;
        }
        if (!(directionsPressed & PAD_UP)) {
            g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect = 0;
        }
        break;
    case 6:
        if (!(directionsPressed & PAD_UP)) {
            g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect++;
            g_ButtonCombo[COMBO_SWORD_BROTHERS].timer = 20;
        }
        break;
    case 7:
        if (directionsPressed == PAD_DOWN) {
            g_ButtonCombo[COMBO_SWORD_BROTHERS].timer = 20;
            g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect++;
            break;
        }
        if (--g_ButtonCombo[COMBO_SWORD_BROTHERS].timer == 0) {
            g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect = 0;
        }
        break;
    case 8:
        if (--g_ButtonCombo[COMBO_SWORD_BROTHERS].timer == 0) {
            g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect = 0;
        }
        if ((g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) &&
            !(g_Player.unk46 & 0x8000)) {
            if (PLAYER.step == Player_Crouch) {
                if (CastSpell(SPELL_SWORD_BROTHERS) != 0) {
                    func_8010FD24();
                    g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect =
                        COMBO_COMPLETE;
                    g_ButtonCombo[COMBO_SWORD_BROTHERS].timer = 20;
                    LearnSpell(SPELL_SWORD_BROTHERS);
                    g_Player.unk70 = 1;
                    return 1;
                }
                break;
            }
            FntPrint("command ok\n");
            break;
        }
        break;
    case COMBO_COMPLETE:
        FntPrint("100sword set ok\n");
        if (--g_ButtonCombo[COMBO_SWORD_BROTHERS].timer == 0) {
            g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect = 0;
            g_Player.unk70 = 1;
        }
        break;
    }
    return 0;
}

void CheckSpecialMoveInputs(void) {
    s32 var_v0;
    s32 i;

    for (i = 0; i < 16; i++) {
        switch (i) {
        case 0:
            var_v0 = CheckGravityBootsInput();
            break;
        case 1:
            var_v0 = CheckQuarterCircleForwardInput();
            break;
        case 2:
            var_v0 = CheckBackForwardInput();
            break;
        case 3:
            var_v0 = CheckHellfireInput();
            break;
        case 4:
            var_v0 = CheckTetraSpiritInput();
            break;
        case 6:
            var_v0 = CheckSoulStealInput();
            break;
        case 9:
            var_v0 = CheckSwordBrothersInput();
            break;
        case 14:
            var_v0 = CheckSummonSpiritInput();
            break;
        case 15:
            var_v0 = CheckDarkMetamorphosisInput();
            break;
        case 5:
        case 7:
        case 8:
        case 10:
        case 11:
        case 12:
        case 13:
        default:
            var_v0 = 0;
            break;
        }
        if (var_v0 != 0) {
            return;
        }
    }
}
