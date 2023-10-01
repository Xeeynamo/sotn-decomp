#include "dra.h"
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
            ((PLAYER.step == 2) ||
             ((PLAYER.step == 4) && (g_Player.unk44 & 1)))) {
            if (g_Player.unk72 == 0) {
                if (func_800FF064(1) >= 0) {
                    func_8010E9A4();
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
                !(g_Player.unk46 & 0x8000) && (PLAYER.step < 2) &&
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

INCLUDE_ASM("dra/nonmatchings/704D8", func_80110BC8);

INCLUDE_ASM("dra/nonmatchings/704D8", func_80110DF8);

INCLUDE_ASM("dra/nonmatchings/704D8", func_80111018);

INCLUDE_ASM("dra/nonmatchings/704D8", func_801112AC);

INCLUDE_ASM("dra/nonmatchings/704D8", func_8011151C);
