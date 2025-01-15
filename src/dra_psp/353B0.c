// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

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
        if ((g_ButtonCombo[COMBO_GRAVITY_BOOTS].timer) &&
            --g_ButtonCombo[COMBO_GRAVITY_BOOTS].timer == 0) {
            g_ButtonCombo[COMBO_GRAVITY_BOOTS].buttonsCorrect = 0;
            break;
        }
        if (IsRelicActive(RELIC_GRAVITY_BOOTS) &&
            (g_Player.padTapped & PAD_CROSS) && !(g_Player.unk46 & 0x8000) &&
            ((PLAYER.step == Player_Crouch) ||
             ((PLAYER.step == Player_Jump) && (g_Player.unk44 & 1)))) {
            if (g_Player.unk72) {
                g_ButtonCombo[COMBO_GRAVITY_BOOTS].buttonsCorrect = 0;
                break;
            }
            if (HandleGravityBootsMP(REDUCE) >= 0) {
                DoGravityJump();
                g_ButtonCombo[COMBO_GRAVITY_BOOTS].buttonsCorrect = 0;
                return 1;
            }
        }
        break;
    }
    return 0;
}

// Used for wolf charge, and for weapons which have a move using this pattern
bool CheckQuarterCircleForwardInput(void) {
    s32 directionsPressed;
    s32 forward;
    s32 down_forward;
    s32 unused = 1; // Meaningless, PSP-only

    directionsPressed =
        g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    if (g_WasFacingLeft == 0) {
        forward = PAD_RIGHT;
    } else {
        forward = PAD_LEFT;
    }
    if (g_WasFacingLeft == 0) {
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
        if (g_ButtonCombo[COMBO_QCF].timer) {
            if (g_Player.unk72) {
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
    s32 forward;
    s32 backward;
    s32 unused = 2; // Meaningless, PSP-only

    directionsPressed =
        g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    if (!g_WasFacingLeft2) {
        forward = PAD_RIGHT;
    } else {
        forward = PAD_LEFT;
    }
    if (!g_WasFacingLeft2) {
        backward = PAD_LEFT;
    } else {
        backward = PAD_RIGHT;
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
    case 0xFE: // Indicates FE might have special flag meaning. Never gets set though.
    default:
        if (g_Player.unk72) {
            g_ButtonCombo[COMBO_BF].buttonsCorrect = 0;
            break;
        }
        if (g_ButtonCombo[COMBO_BF].timer &&
            --g_ButtonCombo[COMBO_BF].timer == 0) {
            g_ButtonCombo[COMBO_BF].buttonsCorrect = 0;
            g_WasFacingLeft2 = PLAYER.facingLeft;
        }
    }
    return 0;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/353B0", func_psp_091123D8);

INCLUDE_ASM("dra_psp/psp/dra_psp/353B0", func_psp_091127A0);

INCLUDE_ASM("dra_psp/psp/dra_psp/353B0", func_psp_09112AC8);

INCLUDE_ASM("dra_psp/psp/dra_psp/353B0", func_psp_09112E48);

INCLUDE_ASM("dra_psp/psp/dra_psp/353B0", func_psp_09113268);

INCLUDE_ASM("dra_psp/psp/dra_psp/353B0", func_psp_091136F8);
