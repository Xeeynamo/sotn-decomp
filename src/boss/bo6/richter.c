// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

extern AnimationFrame D_us_80182008[];
extern s32 D_us_801D11C8[];
extern s32 D_us_801D1248[];

void func_us_801B4BD0(void) {
    s32 i;
    Entity* var_s1;
    Entity* e;
    PlayerState* var_a0;
    Primitive* prim;
    s32* memset_ptr;
    s32 memset_len;
    s16 temp_v0;
    s16 primIndex;
    s32 radius;
    s32 intensity;
    s32 temp_v1;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s2_3;
    s32* var_s0;
    s32* var_s3;

    RIC.animSet = ANIMSET_OVL(1);
    RIC.zPriority = g_unkGraphicsStruct.g_zEntityCenter + 8;
    RIC.flags = FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED | FLAG_UNK_400000 |
                FLAG_UNK_2000;
    RIC.facingLeft = 0;
    RIC.unk5A = 8;
    RIC.palette = 0x8220;
    RIC.scaleX = RIC.scaleY = 0x100;
    RIC.rotPivotY = 0x18;
    RIC.drawMode = DRAW_DEFAULT;

    g_PlayerDraw[8].r0 = g_PlayerDraw[8].r1 = g_PlayerDraw[8].r2 =
        g_PlayerDraw[8].r3 = g_PlayerDraw[8].g0 = g_PlayerDraw[8].g1 =
            g_PlayerDraw[8].g2 = g_PlayerDraw[8].g3 = g_PlayerDraw[8].b0 =
                g_PlayerDraw[8].b1 = g_PlayerDraw[8].b2 = g_PlayerDraw[8].b3 =
                    0x80;

    g_PlayerDraw[8].enableColorBlend = 0;

    memset_len = sizeof(PlayerState) / sizeof(s32);
    memset_ptr = (s32*)&g_Ric;
    for (i = 0; i < memset_len; i++) {
        *memset_ptr++ = 0;
    }

    g_Ric.vram_flag = g_Ric.unk04 = 1;

    BO6_RicSetStand(0);
    RIC.anim = D_us_80182008;

    for (i = 0; i < 32; i++) {
        radius = (rand() & 0x3FF) + FLT(1.0 / 16.0);
        intensity = (rand() & 0xFF) + FLT(1.0 / 16.0);
        D_us_801D11C8[i] = ((rcos(radius) << 4) * intensity) >> 8;
        D_us_801D1248[i] = -(((rsin(radius) << 4) * intensity) >> 7);
    }

    for (e = &g_Entities[STAGE_ENTITY_START + 1], i = 0; i < 3; i++, e++) {
        DestroyEntity(e);
        e->animSet = ANIMSET_OVL(1);
        e->unk5A = i + 9;
        e->palette = PAL_OVL(0x220);
        e->flags = FLAG_POS_CAMERA_LOCKED;
    }

    primIndex = g_api.AllocPrimitives(PRIM_TILE, 6);
    prim = &g_PrimBuf[primIndex];
    g_Entities[65].primIndex = primIndex;
    g_Entities[65].flags |= FLAG_HAS_PRIMS;
    while (prim != NULL) {
        prim->drawMode = DRAW_UNK_100 | DRAW_HIDE | DRAW_UNK02;
        prim = prim->next;
    }
    g_api.TimeAttackController(
        TIMEATTACK_EVENT_SAVE_RICHTER, TIMEATTACK_SET_VISITED);
}

void func_us_801B4EAC(void) {
    g_Ric.unk04 = g_Ric.vram_flag;
    g_Ric.vram_flag = 0;
    RIC.posY.val += RIC.velocityY;
    RIC.posX.val += RIC.velocityX;

    if (RIC.posY.val >= 0xB30000) {
        RIC.posY.val = 0xB30000;
        g_Ric.vram_flag |= 1;
    }
    if (RIC.posY.val <= 0x280000) {
        RIC.posY.val = 0x280000;
        g_Ric.vram_flag |= 2;
    }
    if (RIC.posX.val >= 0xF80000) {
        RIC.posX.val = 0xF80000;
        g_Ric.vram_flag |= 4;
    }
    if (RIC.posX.val <= 0x80000) {
        RIC.posX.val = 0x80000;
        g_Ric.vram_flag |= 8;
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_CheckBladeDashInput);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_CheckHighJumpInput);

extern s32 D_us_80181210[];
extern u16 D_us_80181250[];
extern u16 D_us_80181270[];
extern AnimationFrame* D_us_80181F14[];
extern AnimationFrame D_us_801820BC[];
extern AnimationFrame D_us_801821E0[];
extern AnimationFrame D_us_8018224C[];
extern FrameProperty D_us_801824A4[];
extern s32 D_us_801D169C;
extern u32 D_us_801D16A4;

void OVL_EXPORT(RicMain)(void) {
    s16 angle;
    s32 timer;
    s32 i;
    s32 status;
    s16 step;
    s16 step_s;
    PlayerDraw* playerDraw;
    DamageParam damage;
    s32 posX, posY;

    // status = saved_reg_s3;
    // step = saved_reg_s5;
    // step_s = saved_reg_s6;
#ifdef VERSION_PSP
    status = 0;
#endif
    g_CurrentEntity = &RIC;
    playerDraw = &g_PlayerDraw[8];
    g_Ric.unk4C = 0;
    for (i = 0; i < LEN(g_Ric.timers); i++) {
        if (g_Ric.timers[i]) {
            switch (i) {      /* switch 1 */
            case PL_T_POISON: /* switch 1 */
                g_Ric.timers[PL_T_POISON] = 0x800;
                break;
            case PL_T_CURSE:
                break;
            case PL_T_2: /* switch 1 */
                RIC.palette = g_Ric.unk40;
                break;
            case PL_T_3:
                break;
            case PL_T_4: /* switch 1 */
                angle = (g_GameTimer & 0xF) * 256;
                playerDraw->r0 = playerDraw->g0 = playerDraw->b0 =
                    (rsin(angle) + FLT(1)) / 64 + 0x60;

                angle += FLT(1.0 / 8.0);
                playerDraw->r1 = playerDraw->g1 = playerDraw->b1 =
                    (rsin(angle) + FLT(1)) / 64 + 0x60;

                angle += FLT(1.0 / 8.0);
                playerDraw->r3 = playerDraw->g3 = playerDraw->b3 =
                    (rsin(angle) + FLT(1)) / 64 + 0x60;

                angle += FLT(1.0 / 8.0);
                playerDraw->r2 = playerDraw->g2 = playerDraw->b2 =
                    (rsin(angle) + FLT(1)) / 64 + 0x60;

                playerDraw->enableColorBlend = true;
                break;
            case PL_T_5:
            case PL_T_6:
            case PL_T_7:
            case PL_T_8:
            case PL_T_ATTACK:
            case PL_T_10:
            case PL_T_RUN:
            case PL_T_12:
                break;
            case PL_T_INVINCIBLE_SCENE: /* switch 1 */
                g_Ric.timers[PL_T_INVINCIBLE_SCENE] = 4;
                break;
            case PL_T_INVINCIBLE:
                break;
            case PL_T_AFTERIMAGE_DISABLE: /* switch 1 */
                OVL_EXPORT(DisableAfterImage)(0, 0);
                break;
            }

            if (--g_Ric.timers[i] == 0) {
                switch (i) { /* switch 2 */
                case PL_T_POISON:
                case PL_T_CURSE:
                    break;
                case PL_T_2: /* switch 2 */
                    RIC.palette = PAL_OVL(0x220);
                    break;
                case PL_T_3:
                    break;
                case PL_T_4: /* switch 2 */
                    playerDraw->enableColorBlend = false;
                    break;
                case PL_T_INVINCIBLE_SCENE: /* switch 2 */
                    OVL_EXPORT(RicSetInvincibilityFrames)(1, 0x10);
                    break;
                case PL_T_6: /* switch 2 */
                    if ((RIC.step == 4) && (RIC.anim != D_us_801820BC)) {
                        BO6_RicSetAnimation(D_us_801820BC);
                        g_Ric.unk44 &= ~0x10;
                    }
                    break;
                case PL_T_INVINCIBLE:
                    break;
                case PL_T_AFTERIMAGE_DISABLE: /* switch 2 */
                    func_us_801B9C14();
                    break;
                case PL_T_5:
                case PL_T_7:
                case PL_T_8:
                case PL_T_ATTACK:
                case PL_T_10:
                case PL_T_RUN:
                case PL_T_12:
                default:
                    break;
                }
            }
        }
    }

    g_Ric.padHeld = g_Ric.padPressed;
    if (g_Ric.demo_timer) {
        g_Ric.demo_timer--;
        g_Ric.padPressed = g_Ric.padSim;
    } else {
        g_Ric.padPressed = g_pads[1].pressed;
    }
    g_Ric.padTapped = (g_Ric.padHeld ^ g_Ric.padPressed) & g_Ric.padPressed;

    if ((RIC.step != PL_S_ENDING_4) && (RIC.step != PL_S_DEAD)) {
        if (RIC.step != PL_S_DEAD && RIC.flags & FLAG_DEAD) {
            D_us_801D16A4 |= 2;
            step = RIC.step;
            step_s = RIC.step_s;
            damage.effects =
                D_us_80181210[g_CurrentEntity->nFramesInvincibility];
            OVL_EXPORT(RicSetStep)(0x11);
#ifdef VERSION_PSP
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_SAVE_RICHTER, TIMEATTACK_SET_RECORD);
#endif
        } else if (D_us_801D169C != 0) {
            OVL_EXPORT(RicSetStep)(0x70);
        } else {
            if ((g_Ric.timers[PL_T_INVINCIBLE_SCENE] |
                 g_Ric.timers[PL_T_INVINCIBLE]) == 0) {
                if ((g_CurrentEntity->hitFlags > 0) &&
                    (g_CurrentEntity->hitFlags < 4)) {
                    step = RIC.step;
                    step_s = RIC.step_s;
                    damage.effects =
                        D_us_80181210[g_CurrentEntity->nFramesInvincibility];
                    if ((g_Ric.unk6C - g_Ric.unk6A) >= 10) {
                        damage.damageKind = 3;
                    } else {
                        damage.damageKind = 2;
                    }
                    OVL_EXPORT(RicSetStep)(0xB);
                }
            }
            goto check_input_combo;
        }
    } else {
    check_input_combo:
        BO6_CheckBladeDashInput();
        BO6_CheckHighJumpInput();
    }
    g_Ric.prev_step = RIC.step;
    g_Ric.prev_step_s = RIC.step_s;

    switch (RIC.step) { /* switch 3 */
    case PL_S_STAND:    /* switch 3 */
        BO6_RicStepStand();
        break;
    case PL_S_WALK: /* switch 3 */
        BO6_RicStepWalk();
        break;
    case PL_S_CROUCH: /* switch 3 */
        BO6_RicStepCrouch();
        break;
    case PL_S_FALL: /* switch 3 */
        BO6_RicStepFall();
        break;
    case PL_S_JUMP: /* switch 3 */
        BO6_RicStepJump();
        break;
    case PL_S_HIGHJUMP: /* switch 3 */
        BO6_RicStepHighJump();
        break;
    case PL_S_HIT: /* switch 3 */
        BO6_RicStepHit(damage.effects, damage.damageKind, step, step_s);
        break;
    case PL_S_DEAD: /* switch 3 */
        BO6_RicStepDead(damage.effects, damage.damageKind, step, step_s);
        break;
    case PL_S_STAND_IN_AIR: /* switch 3 */
        BO6_RicStepStandInAir();
        break;
    case PL_S_FLAME_WHIP: /* switch 3 */
        BO6_RicStepEnableFlameWhip();
        break;
    case PL_S_HYDROSTORM: /* switch 3 */
        BO6_RicStepHydrostorm();
        break;
    case PL_S_THROW_DAGGERS: /* switch 3 */
        BO6_RicStepThrowDaggers();
        break;
    case PL_S_SUBWPN_CRASH: /* switch 3 */
        BO6_RicStepGenericSubwpnCrash();
        break;
    case PL_S_SLIDE: /* switch 3 */
        BO6_RicStepSlide();
        break;
    case PL_S_RUN: /* switch 3 */
        BO6_RicStepRun();
        break;
    case PL_S_SLIDE_KICK: /* switch 3 */
        BO6_RicStepSlideKick();
        break;
    case PL_S_BLADEDASH: /* switch 3 */
        BO6_RicStepBladeDash();
        break;
    case PL_S_ENDING_1: /* switch 3 */
        func_us_801B913C();
        break;
    case PL_S_ENDING2: /* switch 3 */
        func_us_801B9144();
        break;
    case PL_S_ENDING_3: /* switch 3 */
        func_us_801B9338();
        break;
    case PL_S_ENDING_4: /* switch 3 */
        func_us_801B9340();
        break;
    }

    g_Ric.unk08 = g_Ric.status;

    switch (RIC.step) {      /* switch 4 */
    case PL_S_STAND:         /* switch 4 */
        status = 0x08000000; /* switch 4 */
        break;
    case PL_S_WALK:
        status = 0x08000000;
        break;
    case PL_S_CROUCH: /* switch 4 */
        status = 0x08000000;
        if (RIC.step_s != 2) {
            status = 0x08000020;
        }
        break;
    case PL_S_FALL: /* switch 4 */
        status = 0x08002000;
        break;
    case PL_S_JUMP: /* switch 4 */
        status = 0x08002000;
        break;
    case PL_S_HIGHJUMP: /* switch 4 */
        BO6_RicSetInvincibilityFrames(1, 4);
        break;
    case PL_S_HIT: /* switch 4 */
        status = 0x08010000;
        BO6_RicSetInvincibilityFrames(1, 8);
        break;
    case PL_S_DEAD: /* switch 4 */
#ifdef VERSION_PSP
        g_api.TimeAttackController(
            TIMEATTACK_EVENT_SAVE_RICHTER, TIMEATTACK_SET_RECORD);
#endif
        status = 0x08050000;
        if (RIC.step_s == 0x80) {
            status |= 0x80000;
        }
        BO6_RicSetInvincibilityFrames(1, 8);
        break;

    case PL_S_FLAME_WHIP:    /* switch 4 */
    case PL_S_HYDROSTORM:    /* switch 4 */
    case PL_S_THROW_DAGGERS: /* switch 4 */
    case PL_S_SUBWPN_CRASH:  /* switch 4 */
        status = 0x08000000;
        // fallthrough
    // possibly PSP specific
    case PL_S_STAND_IN_AIR:
        BO6_RicSetInvincibilityFrames(1, 8);
        break;
    case PL_S_SLIDE:      /* switch 4 */
    case PL_S_SLIDE_KICK: /* switch 4 */
        status = 0x20;
        break;
    case PL_S_RUN:
    case PL_S_BLADEDASH:
        break;
    case PL_S_ENDING_1: /* switch 4 */
    case PL_S_ENDING2:  /* switch 4 */
        BO6_RicSetInvincibilityFrames(1, 8);
        status |= 0x08000000;
        break;
    case PL_S_ENDING_3: /* switch 4 */
#ifdef VERSION_PSP
        g_api.TimeAttackController(
            TIMEATTACK_EVENT_SAVE_RICHTER, TIMEATTACK_SET_RECORD);
#endif
        BO6_RicSetInvincibilityFrames(1, 8);
        status |= 0x08000000;
        break;
    case PL_S_ENDING_4: /* switch 4 */
        g_api.TimeAttackController(
            TIMEATTACK_EVENT_SAVE_RICHTER, TIMEATTACK_SET_RECORD);
        BO6_RicSetInvincibilityFrames(1, 8);
        status |= 0x08000000;
        break;
    }

    if (g_Ric.timers[PL_T_ATTACK]) {
        status |= 0x400;
    }
    if (g_Ric.timers[PL_T_10]) {
        status |= 0x800;
    }
    if (g_Ric.timers[PL_T_12]) {
        status |= 0x1000;
    }
    status |= 0x10000000;
    g_Ric.status = status;
    if (g_Ric.unk08 & 0x10000) {
        if (!(g_Ric.status & PLAYER_STATUS_UNK10000)) {
            if (g_Ric.unk5C) {
                if (g_Status.hp < 2) {
                    OVL_EXPORT(RicSetDeadPrologue)();
                    BO6_RicSetInvincibilityFrames(1, 8);
                }
            } else {
                BO6_RicSetInvincibilityFrames(1, 8);
                g_Ric.timers[PL_T_4] = 8;
                RIC.palette = PAL_OVL(0x220);
            }
        }
    }
    if (status & 0x08000000) {
        BO6_DisableAfterImage(1, 4);
    }
    g_api.UpdateAnim(D_us_801824A4, D_us_80181F14);
    if (RIC.anim == &D_us_8018224C[0]) {
        RIC.palette = D_us_80181250[RIC.pose];
    }
    if ((RIC.anim == &D_us_801821E0[0]) && (RIC.pose == 4)) {
        RIC.palette = D_us_80181270[RIC.poseTimer & 3];
    }
    if (g_Ric.status & PLAYER_STATUS_DEAD) {
        if (RIC.poseTimer < 0) {
            RIC.animCurFrame |= 0x8000;
        }
        RIC.hitboxState = 0;
    } else {
        RIC.hitboxState = g_Ric.unk70;
        if ((g_Ric.timers[PL_T_INVINCIBLE_SCENE] |
             g_Ric.timers[PL_T_INVINCIBLE]) != 0) {
            RIC.hitboxState = 0;
        }
    }
    func_us_801B94CC();
    // g_Entities_64 = 0x091E4580;
    //                 0x091E4584;
    //                 0x091E4596;
    posX = RIC.posX.val;
    posY = RIC.posY.val;
    func_us_801B4EAC();
    func_us_801B96F4();
#ifdef VERSION_PSP
    FntPrint("pl_color:%04x\n", RIC.palette);
#endif
}

extern s32 D_us_801CF3C8; // Richter Think Step
extern s32 D_us_801CF3CC; // Richter Think Step_s
void func_us_801B5A14(s32 step) {
    D_us_801CF3C8 = step;
    D_us_801CF3CC = 0;
}

typedef enum { THINK_STEP_INIT } ThinkStep;

// RIC base = 0x800762D8
extern s32 D_us_80181278;
extern s32 D_us_801CF3C8; // Richter Think Step
extern s32 D_us_801CF3CC; // Richter Think Step_s
extern s32 D_us_801CF3D0;
extern s32 D_us_801CF3D8;
extern s32 D_us_801CF3E0;
extern s32 D_us_801CF3E4;
extern s32 g_CutsceneFlags;

extern s32 D_us_801D169C; // padSim + 0xB0
static void func_us_801B5A14(s32 step);

// not matching on PSP
void RichterThinking(void) {
    s32 globalPosX;
    s32 playerDistanceX;
    bool facingLeft;

    if (D_us_801CF3D8) {
        D_us_801CF3D8--;
    }

    globalPosX = g_Tilemap.scrollX.i.hi + RIC.posX.i.hi;
    g_Ric.demo_timer = 2;
    g_Ric.padSim = 0;

    facingLeft = false;
    if ((RIC.posX.i.hi - PLAYER.posX.i.hi) >= 0) {
        facingLeft = true;
    }

    playerDistanceX = abs(RIC.posX.i.hi - PLAYER.posX.i.hi);

    if (D_us_801CF3E4 < g_Ric.unk6C && D_us_801CF3E4 >= g_Ric.unk6A) {
        D_us_801CF3C8 = 0x1E;
    }

    if (D_us_801D169C != 0) {
        func_us_801B5A14(0x28);
    }

    if (g_Player.status & PLAYER_STATUS_DEAD) {
        D_us_801CF3C8 = 0x32;
    }

    if (D_us_801CF3C8 < 0x12) {
        if (g_Ric.status & PLAYER_STATUS_UNK10000) {
            func_us_801B5A14(0);
        } else if (g_Player.timers[ALU_T_12] && D_us_801CF3C8 != 0xE) {
            func_us_801B5A14(0xE);
        }
    }

    FntPrint("think_step:%02x\n", D_us_801CF3C8);

    switch (D_us_801CF3C8) { /* switch 1 */
    // following item crash at start of fight
    case THINK_STEP_INIT: /* switch 1 */
        if (!(g_Ric.status & PLAYER_STATUS_UNK10000)) {
            if (g_Player.timers[ALU_T_10]) {
                if (rand() & 1) {
                    func_us_801B5A14(7);
                } else {
                    func_us_801B5A14(5);
                }
            } else if (abs(RIC.posY.i.hi - PLAYER.posY.i.hi) > 0x20) {
                func_us_801B5A14(7);
            } else {
                if (playerDistanceX > 0x58) {
                    if (facingLeft) {
                        g_Ric.padSim = 0x8000;
                    } else {
                        g_Ric.padSim = 0x2000;
                    }
                } else {
                    func_us_801B5A14(1);
                }
            }
        }
        break;
    // decicing on attack?
    case 1: /* switch 1 */
        if (RIC.facingLeft != facingLeft) {
            if (facingLeft) {
                g_Ric.padSim = 0x8000;
            } else {
                g_Ric.padSim = 0x2000;
            }
        }

        if (D_us_801CF3CC == 0) {
            D_us_801CF3D0 = 8;
            D_us_801CF3CC = 1;
            return;
        }

        if (playerDistanceX > 0x58) {
            func_us_801B5A14(0);
        } else {
            if (((globalPosX < 0x10) && (RIC.facingLeft == 0)) ||
                ((globalPosX > 0xF0) && (RIC.facingLeft))) {
                func_us_801B5A14(4);
                if (D_us_801CF3E0 != 0) {
                    func_us_801B5A14(0xD);
                    return;
                }
            } else if (g_Player.status & PLAYER_STATUS_CROUCH) {
                if (rand() & 1) {
                    func_us_801B5A14(6);
                } else {
                    func_us_801B5A14(5);
                }
            } else {
                if (g_Player.timers[ALU_T_9]) {
                    switch (rand() & 7) { /* switch 2 */
                    case 0:               /* switch 2 */
                    case 6:               /* switch 2 */
                        func_us_801B5A14(6);
                        break;
                    case 7: /* switch 2 */
                        func_us_801B5A14(7);
                        break;
                    case 1: /* switch 2 */
                        func_us_801B5A14(5);
                        break;
                    case 2: /* switch 2 */
                    case 3: /* switch 2 */
                    case 4: /* switch 2 */
                    case 5: /* switch 2 */
                    default:
                        func_us_801B5A14(2);
                        break;
                    }
                } else {
                    if (g_Player.timers[ALU_T_10]) {
                        if (rand() & 1) {
                            func_us_801B5A14(7);
                        } else {
                            func_us_801B5A14(5);
                        }
                    } else if (D_us_801CF3D0) {
                        D_us_801CF3D0--;
                    } else if (playerDistanceX < 0x40) {
                        if ((RIC.posY.i.hi - PLAYER.posY.i.hi) < 0x18) {
                            func_us_801B5A14(3);
                        } else {
                            func_us_801B5A14(8);
                        }
                    } else {
                        func_us_801B5A14(8);
                    }
                }
            }
        }
        break;
    case 2:                      /* switch 1 */
        switch (D_us_801CF3CC) { /* switch 3; irregular */
        case 0:                  /* switch 3 */
            if (RIC.step == 5) {
                D_us_801CF3CC = 1;
            } else if (g_Timer & 1) {
                g_Ric.padSim = 0x40;
            }
            break;
        case 1: /* switch 3 */
            if (g_Ric.unk44 & 8) {
                D_us_801CF3CC = 2;
            } else {
                if (g_Timer & 1) {
                    g_Ric.padSim = 0x40;
                }
                if (g_Ric.vram_flag & 1) {
                    func_us_801B5A14(0);
                }
            }
            break;
        case 2:
        default: /* switch 3 */
            if (D_us_801CF3E0 == 0) {
                func_us_801B5A14(9);
            }
            if (g_Ric.vram_flag & 1) {
                if (D_us_801CF3E0 != 0) {
                    func_us_801B5A14(0xC);
                } else {
                    func_us_801B5A14(0);
                }
            }
            break;
        }
        break;
    // whip attack
    case 3: /* switch 1 */
        if (D_us_801CF3CC == 0) {
            if (!g_Ric.unk46) {
                if (g_Timer & 1) {
                    g_Ric.padSim = 0x80;
                }
                D_us_801CF3CC = 1;
            }
        } else {
            if (!g_Ric.unk46) {
                func_us_801B5A14(0);
            }
        }
        break;
    // dash
    case 4: /* switch 1 */
        if (D_us_801CF3CC == 0) {
            if (g_Timer & 1) {
                g_Ric.padSim = PAD_R1;
            }
            if (RIC.step == 0x19) {
                D_us_801CF3C8 = 1;
            }
        } else if (RIC.step != 0x19) {
            func_us_801B5A14(0);
        }
        break;
    case 5: /* switch 1 */
        g_Ric.padSim = 0x4000;
        switch (D_us_801CF3CC) {
        case 0:
            if (RIC.facingLeft != facingLeft) {
                if (facingLeft) {
                    g_Ric.padSim |= 0x8000;
                } else {
                    g_Ric.padSim |= 0x2000;
                }
            }
            if (RIC.step == 3) {
                D_us_801CF3CC = 1;
                D_us_801CF3D0 = 8;
            }
            break;
        case 1:
        default:
            if (!--D_us_801CF3D0) {
                func_us_801B5A14(17);
            } else if (playerDistanceX < 0x40) {
                func_us_801B5A14(10);
            }
            break;
        }
        break;
    case 6: /* switch 1 */
        if (D_us_801CF3CC == 0) {
            if (RIC.step == 5) {
                D_us_801CF3CC = 1;
            } else if (g_Timer & 1) {
                g_Ric.padSim = 0x40;
            }
        } else if (g_Ric.vram_flag & 1) {
            func_us_801B5A14(0);
        } else if (RIC.velocityY > 0x4000) {
            func_us_801B5A14(9);
        }
        break;
    case 7: /* switch 1 */
        if (RIC.facingLeft) {
            g_Ric.padSim = PAD_LEFT;
        } else {
            g_Ric.padSim = PAD_RIGHT;
        }
        if (D_us_801CF3CC == 0) {
            if (RIC.step == 5) {
                D_us_801CF3CC = 1;
            } else if (g_Timer & 1) {
                g_Ric.padSim |= PAD_CROSS;
            }
        } else if (g_Ric.vram_flag & 1) {
            func_us_801B5A14(0);
        } else if (RIC.velocityY > 0x4000) {
            if (rand() & 1) {
                func_us_801B5A14(0xB);
            } else {
                func_us_801B5A14(9);
            }
        }
        break;
    // subweapon attack?
    case 8: /* switch 1 */
        if (D_us_801CF3CC == 0) {
            if (!g_Ric.unk46) {
                if (g_Timer & 1) {
                    g_Ric.padSim = PAD_UP | PAD_SQUARE;
                }
                D_us_801CF3CC = 1;
            }
        } else if (!g_Ric.unk46) {
            func_us_801B5A14(0);
        }
        break;
    case 9: /* switch 1 */
        if (g_Ric.vram_flag & 1) {
            func_us_801B5A14(0);
        } else if (D_us_801CF3CC == 0) {
            if (!g_Ric.unk46) {
                if (g_Timer & 1) {
                    g_Ric.padSim = PAD_UP | PAD_SQUARE;
                }
                D_us_801CF3CC = 1;
            }
        } else if (!g_Ric.unk46) {
            func_us_801B5A14(0);
        }
        break;
    case 10: /* switch 1 */
        g_Ric.padSim = PAD_DOWN;
        if (D_us_801CF3CC == 0) {
            if (!g_Ric.unk46) {
                if (g_Timer & 1) {
                    g_Ric.padSim |= PAD_SQUARE;
                }
                D_us_801CF3CC = 1;
            }
        } else if (!g_Ric.unk46) {
            func_us_801B5A14(0);
        }
        break;
    case 11: /* switch 1 */
        if (g_Ric.vram_flag & 1) {
            func_us_801B5A14(0);
        } else if (D_us_801CF3CC == 0) {
            if (!g_Ric.unk46) {
                if (g_Timer & 1) {
                    g_Ric.padSim = 0x80;
                }
                D_us_801CF3CC = 1;
            }
        } else if (!g_Ric.unk46) {
            func_us_801B5A14(0);
        }
        break;
    case 12: /* switch 1 */
        if (D_us_801CF3CC == 0) {
            if (RIC.step == 0x1C) {
                D_us_801CF3CC = 1;
            } else if (g_Timer & 1) {
                g_Ric.padSim = 0x110;
            }
        } else if (RIC.step != 0x1C) {
            func_us_801B5A14(0x11);
            return;
        }
        break;
    case 13: /* switch 1 */
        // STEP: cutscene
        if (D_us_801CF3CC == 0) {
            if (RIC.step == 0x1C) {
                D_us_801CF3CC = 1;
            } else if (g_Timer & 1) {
                g_Ric.padSim = 0x810;
            }
        } else if (RIC.step != 0x1C) {
            func_us_801B5A14(0);
        }
        break;

    case 14: /* switch 1 */
        if (D_us_801CF3CC == 0) {
            if (RIC.step == 0x13) {
                D_us_801CF3CC = 1;
            } else if (g_Timer & 1) {
                g_Ric.padSim = 0x14;
            }
        } else if (RIC.step != 0x13) {
            func_us_801B5A14(0);
        }
        break;

    case 15: /* switch 1 */
        if (D_us_801CF3CC == 0) {
            if (RIC.step == 0x15) {
                D_us_801CF3CC = 1;
            } else if (g_Timer & 1) {
                g_Ric.padSim = 0x11;
            }
        } else if (RIC.step != 0x15) {
            func_us_801B5A14(0);
        }
        break;
    case 16: /* switch 1 */
        if (D_us_801CF3CC == 0) {
            if (RIC.step == 0x13) {
                D_us_801CF3CC = 1;
            } else if (g_Timer & 1) {
                g_Ric.padSim = 0x10;
            }
        } else if (RIC.step != 0x13) {
            func_us_801B5A14(0);
        }
        break;
    case 17:                     /* switch 1 */
        switch (D_us_801CF3CC) { /* switch 4; irregular */
        case 0:                  /* switch 4 */
            g_Ric.padSim = 0x4000;
            if (RIC.step == 3) {
                D_us_801CF3CC = 1;
            }
            break;
        case 1: /* switch 4 */
            if (RIC.step == 0x18) {
                D_us_801CF3CC = 4;
                if (D_us_801CF3E0 != 0) {
                    if (RIC.facingLeft && RIC.posX.i.hi > 0x80) {
                        D_us_801CF3CC = 2;
                    }
                    if (!RIC.facingLeft && RIC.posX.i.hi < 0x80) {
                        D_us_801CF3CC = 2;
                    }
                }
            } else {
                g_Ric.padSim = 0x4000;
                if (g_Timer & 1) {
                    g_Ric.padSim |= PAD_CROSS;
                }
            }
            break;
        case 2: /* switch 4 */
            if (RIC.step == 0x1B) {
                D_us_801CF3CC = 3;
            } else {
                g_Ric.padSim = 0x4000;
                if (g_Timer & 1) {
                    g_Ric.padSim |= 0x40;
                }
            }
            break;
        case 3: /* switch 4 */
            g_Ric.padSim = 0x80;
            if (RIC.step != 0x1B) {
                func_us_801B5A14(0);
            }
            // fallthrough

        default:
            func_us_801B5A14(0);
            break;
        }
        break;
    case 18: /* switch 1 */
        OVL_EXPORT(RicSetInvincibilityFrames)(1, 4);
        if (RIC.step == 1) {
            func_us_801B5A14(0x13);
        }
        break;

    case 19: /* switch 1 */
        OVL_EXPORT(RicSetInvincibilityFrames)(1, 4);
        if (D_us_801CF3CC == 0) {
            D_us_801CF3D0 = 0x40;
            D_us_801CF3CC = 1;
        } else {
            if ((g_CutsceneFlags & 2) || (g_CastleFlags[SHAFT_ORB_DEFEATED]) ||
                (g_DemoMode != Demo_None)) {
                if (!--D_us_801CF3D0) {
                    OVL_EXPORT(RicCreateEntFactoryFromEntity)
                    (g_CurrentEntity, 0x48, 0);
                    func_us_801B5A14(0x10);
                }
            }
        }
        break;
    case 30: /* switch 1 */
        g_Player.timers[ALU_T_INVINCIBLE_CONSUMABLES] = 3;
        OVL_EXPORT(RicSetInvincibilityFrames)(1, 8);
        g_Ric.padSim = 0x1000;
        if (RIC.step == 1 && RIC.step_s == 1) {
            RIC.step = 0x50;
            RIC.step_s = 0;
            D_us_801CF3C8 = 0x1F;
        }
        break;
    case 31: /* switch 1 */
        g_Player.timers[ALU_T_INVINCIBLE_CONSUMABLES] = 3;
        OVL_EXPORT(RicSetInvincibilityFrames)(1, 8);
        if (RIC.step != 0x50) {
            D_us_801CF3E0 = 1;
            func_us_801B5A14(0x20);
        }
        break;
    case 32: /* switch 1 */
        g_Player.timers[ALU_T_INVINCIBLE_CONSUMABLES] = 3;
        OVL_EXPORT(RicSetInvincibilityFrames)(1, 8);
        if (D_us_801CF3CC == 0) {
            D_us_801CF3D0 = 0x10;
            D_us_801CF3CC = 1;
        } else {
            if (D_us_801CF3D0 != 0) {
                D_us_801CF3D0--;
            }
            func_us_801B5A14(0xF);
        }
        break;

    case 40: /* switch 1 */
        g_Player.timers[ALU_T_INVINCIBLE_CONSUMABLES] = 3;
        D_us_80181278 = 0x32;
        D_us_801CF3C8++;
        break;

    case 41: /* switch 1 */
        g_Player.timers[ALU_T_INVINCIBLE_CONSUMABLES] = 3;
        break;

    case 50: /* switch 1 */
        if (!(g_Player.status & PLAYER_STATUS_DEAD)) {
            func_us_801B5A14(0);
        }
        g_Ric.padSim = 0x1000;
        break;
    }
}

extern s32 D_us_801D11C0;

void func_us_801B6998(void) {
    switch (D_us_80181278) {
    case 0:
        break;
    case 10:
        if ((g_CastleFlags[SHAFT_ORB_DEFEATED] == 0) &&
            (g_DemoMode == Demo_None)) {
            g_unkGraphicsStruct.pauseEnemies = true;
            D_us_801D11C0 = 0;
        }
        D_us_80181278++;
        break;
    case 11:
        if (++D_us_801D11C0 > 1) {
            if ((g_CastleFlags[SHAFT_ORB_DEFEATED] == 0) &&
                (g_DemoMode == Demo_None)) {
                g_unkGraphicsStruct.unk20 = 0xFF;
            }
            D_us_80181278++;
        }
        break;
    case 20:
        if (g_CutsceneFlags & 4) {
            D_us_80181278 = 0x1E;
        }
        break;
    case 40:
        g_CutsceneFlags |= 8;
        break;
    case 50:
    default:
        break;
    }
}

extern EInit D_us_80180400; //
extern s32 D_us_801CF3E0;
extern s32 D_us_801CF3E4;

void EntityRichter(Entity* self) {
    Entity* entity;
    s32 i;

    g_Ric.unk6A = RIC.hitPoints;
    if (self->step == 0) {
        InitializeEntity(D_us_80180400);
        func_us_801B4BD0(); //
        entity = &g_Entities[STAGE_ENTITY_START + 4];
        for (i = STAGE_ENTITY_START + 4; i < 144; i++, entity++) {
            DestroyEntity(entity);
        }
        g_Ric.unk6E = g_Ric.unk6A = g_Ric.unk6C = RIC.hitPoints;
        D_us_801CF3E4 = g_Ric.unk6E / 2;
        D_us_801CF3E0 = 0;
        g_Ric.unk70 = RIC.hitboxState;
        func_us_801B5A14(18);
        OVL_EXPORT(DisableAfterImage)(1, 48);
    } else {
        RichterThinking();
        OVL_EXPORT(RicMain)(); // equivalent to EntityDoppleganger{10,40}
        func_us_801BBBD0();
        func_us_801B6998();
    }
    g_Ric.unk6C = g_Ric.unk6A;
}

// possible file split - pl_setstep

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepStand);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepWalk);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepRun);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepJump);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepFall);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepCrouch);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicResetPose);

void func_us_801B77D8(void) {
    if ((RIC.posX.i.hi - PLAYER.posX.i.hi) <= 0) {
        RIC.entityRoomIndex = 0;
    } else {
        RIC.entityRoomIndex = 1;
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepHit);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepDead);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepStandInAir);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepEnableFlameWhip);

void OVL_EXPORT(RicStepHydrostorm)(void) {
    if (RIC.poseTimer < 0) {
        OVL_EXPORT(RicSetStand)(0);
        g_Ric.unk46 = 0;
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepGenericSubwpnCrash);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepThrowDaggers);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepSlide);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepSlideKick);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepBladeDash);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", func_us_801B8E80);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepHighJump);
