// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

extern PlayerState g_Dop;

void func_us_801C4954(s32 resetAnims, s32 arg1);
s32 CheckMoveDirection(void);
void func_8010E470(s32 arg0, s32 velocityX);
void func_8010E570(s32 arg0);
void func_8010E6AC(bool forceAnim13);
void func_8010FAF4(void);
bool func_us_801C5650(s32 arg0);
void DecelerateX(s32 amount);
void SetSpeedX(s32 speed);

void func_80111CC0(void) {
    if (g_Dop.timers[1] != 0) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x2C, 0x17), 0);
    }
    if (g_Dop.timers[0] != 0) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x2C, 0x16), 0);
    }
}

void DopplegangerStepStand(void) {
    s32 anim;
    u16 var_s0;

    var_s0 = 3;
    anim = 0;
    if (g_Dop.vram_flag & IN_AIR_OR_EDGE) {
        anim = 1;
    }

    if (func_us_801C5650(0x4301C) == false) {
        DecelerateX(FIX(0.125));
        switch (DOPPLEGANGER.step_s) {
        case 0:
        case 2:
            break;
        case 1:
            var_s0 = 1;
            if (!(g_Dop.padPressed & PAD_UP)) {
                var_s0 = 5;
            }
            break;
        case 3:
            var_s0 = 0;
            if (DOPPLEGANGER.pose > 3) {
                var_s0 = 1;
            }
            if (DOPPLEGANGER.pose > 6 || DOPPLEGANGER.poseTimer < 0) {
                var_s0 = 7;
            }
            break;
        case 0x40:
        case 0x41:
        case 0x42:
            func_us_801C4954(1, 1);
            if (DOPPLEGANGER.pose < g_Dop.unk54) {
                var_s0 = 0;
            } else {
                g_Dop.unk46 &= 0x7FFF;
                var_s0 = 0x1B;
                if (DOPPLEGANGER.poseTimer < 0) {
                    var_s0 = 0xF;
                }
            }
            break;
        case 0x51:

            func_us_801C4954(1, 1);
            var_s0 = 0;
            if (DOPPLEGANGER.poseTimer < 0) {
                var_s0 = 0xF;
            }

            break;
        }

        if (var_s0 & 4) {
            func_8010E570(0);
            var_s0 |= 0x8000;
        }
        if (var_s0 & 2 && g_Dop.padPressed & PAD_UP && !g_Dop.unk48) {
            SetDopplegangerAnim(anim);
            DOPPLEGANGER.step_s = 1;
            var_s0 |= 0x8000;
        }

        if (var_s0 & 1 && CheckMoveDirection() != 0) {
            func_8010E6AC(0);
            var_s0 |= 0x8000;
        }
        if (var_s0 & 0x8000 && var_s0 & 8) {
            func_8010FAF4();
        }
    }
}

void DopplegangerStepWalk(void) {
    if (func_us_801C5650(0x4301C) == false) {
        SetSpeedX(FIX(1.5));
        if (CheckMoveDirection() == 0) {
            func_8010E570(0);
        }
    }
}

static s16 D_us_801813C0[] = {
    1,
    0x1f,
    0,
    27,
};

void DopplegangerStepJump(void) {
    s32 moveDirection;
    s16 index;

    DecelerateX(FIX(1.0 / 16.0));
    if (DOPPLEGANGER.velocityY < FIX(-1)) {
        if (!(g_Dop.unk44 & 0x40) && !(g_Dop.padPressed & 0x40)) {
            DOPPLEGANGER.velocityY = FIX(-1);
        }
        if (g_Dop.vram_flag & TOUCHING_CEILING) {
            DOPPLEGANGER.velocityY = FIX(-0.25);
            g_Dop.unk44 |= 0x20;
        }
    }

    if (func_us_801C5650(0x11029)) {
        return;
    }

    switch (DOPPLEGANGER.step_s) {
    case 0:
        moveDirection = CheckMoveDirection();
        if (moveDirection) {
            if (DOPPLEGANGER.ext.player.anim == 22 ||
                DOPPLEGANGER.ext.player.anim == 25) {
                SetDopplegangerAnim(24);
            }
            SetSpeedX(FIX(1.5));
        } else if (DOPPLEGANGER.ext.player.anim == 26 ||
                   DOPPLEGANGER.ext.player.anim == 24) {
            SetDopplegangerAnim(25);
        }
        if (moveDirection <= 0) {
            g_Dop.unk44 &= 0xFFEF;
        }
        if (DOPPLEGANGER.velocityY > 0) {
            if (DOPPLEGANGER.ext.player.anim != 27) {
                SetDopplegangerAnim(27);
            }
            DOPPLEGANGER.step_s = 1;
        }
        break;
    case 1:
        moveDirection = CheckMoveDirection();
        if (moveDirection != 0) {
            SetSpeedX(FIX(1.5));
        }
        if (moveDirection <= 0) {
            g_Dop.unk44 &= 0xFFEF;
        }

        break;

    case 0x40:
    case 0x41:
    case 0x42:
    case 0x51:
        func_us_801C4954(1, 1);
        if (g_Dop.padPressed & PAD_LEFT) {
            DOPPLEGANGER.velocityX = FIX(-1.5);
        }
        if (g_Dop.padPressed & PAD_RIGHT) {
            DOPPLEGANGER.velocityX = FIX(1.5);
        }
        if (DOPPLEGANGER.poseTimer < 0) {
            if (DOPPLEGANGER.velocityY > FIX(1)) {
                index = 0;
            } else {
                index = 2;
            }
            DOPPLEGANGER.step_s = D_us_801813C0[index];
            SetDopplegangerAnim((u8)D_us_801813C0[index + 1]);
            func_8010FAF4();
        }
        break;
    }
}

void DopplegangerStepFall(void) {
    if (func_us_801C5650(0x9029) == false) {
        DecelerateX(FIX(1.0 / 16.0));
        if (CheckMoveDirection() != 0) {
            SetSpeedX(FIX(3.0 / 4.0));
        }
    }
}

void DopplegangerStepCrouch(void) {
    s32 anim;
    s16 var_s0;
    u8 _pad[40]; // any size between 33-40 (inclusive);

    var_s0 = 0;
    // n.b.! much of this code is copied from `func_us_801C6654`,
    // but this variable is not used in this version of the function
    anim = 0;
    if (g_Dop.vram_flag & IN_AIR_OR_EDGE) {
        anim = 1;
    }

    if (func_us_801C5650(0x100C) == false) {
        DecelerateX(FIX(0.125));
        switch (DOPPLEGANGER.step_s) {
        case 0:
            var_s0 = 6;
            break;

        case 1:
            if (!(g_Dop.padPressed & PAD_DOWN)) {
                // n.b.! var_s0 is set, but never used
                var_s0 = 1;
                SetDopplegangerAnim(0x13);
                DOPPLEGANGER.step_s = 2;
                DOPPLEGANGER.pose = 1;
                return;
            }

            if (DOPPLEGANGER.ext.player.anim == 0x65) {
                DOPPLEGANGER.step_s = 0;
            } else if (DOPPLEGANGER.poseTimer < 0) {
                var_s0 = 0x20;
            }
            break;
        case 3:
        case 4:
            if (DOPPLEGANGER.poseTimer < 0) {
                var_s0 = 0x20;
            }
            break;
        case 2:
            var_s0 = 1;
            if (DOPPLEGANGER.poseTimer < 0) {
                func_8010E570(0);
            }
            break;
        case 0x40:
        case 0x41:
        case 0x42:
            func_us_801C4954(1, 1);
            if (DOPPLEGANGER.pose < g_Dop.unk54) {
                var_s0 = 0;
            } else {
                g_Dop.unk46 &= 0x7FFF;
                var_s0 = 0xE;
                if (DOPPLEGANGER.poseTimer < 0) {
                    var_s0 = 0x2E;
                }
            }
            break;
        case 0x51:
            func_us_801C4954(1, 1);
            if (DOPPLEGANGER.poseTimer < 0) {
                var_s0 = 0x2E;
            }
            break;
        }

        if (var_s0 & 0x20) {
            func_8010E470(0, 0);
            var_s0 |= 0x8000;
        }

        if (var_s0 & 2 && g_Dop.unk4C) {
            SetDopplegangerAnim(0x14);
            DOPPLEGANGER.step_s = 0;
            var_s0 |= 0x8000;
        }

        if (var_s0 & 4 && !(g_Dop.padPressed & PAD_DOWN)) {
            SetDopplegangerAnim(0x13);
            DOPPLEGANGER.step_s = 2;
            var_s0 |= 0x8000;
        }

        if (var_s0 & 1 && CheckMoveDirection()) {
            func_8010E6AC(0);
            var_s0 |= 0x8000;
        }

        if (var_s0 & 0x8000 && var_s0 & 8) {
            func_8010FAF4();
        }
    }
}
