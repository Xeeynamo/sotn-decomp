// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

extern s32 D_us_801D4118[];
extern s32 D_us_801D4198[];
extern s32 D_us_801D4D74;

void func_us_801C1A38(void) {
    Entity* entity;
    Primitive* prim;
    s16 primIndex;
    s32 angle;
    s32 scale;
    s32 i;
    s32 colliderSize;
    s32* colliders;

    g_CurrentEntity = &DOPPLEGANGER;
    DOPPLEGANGER.animSet = ANIMSET_OVL(1);
    DOPPLEGANGER.unk5A = 8;
    g_PlayerDraw[8].enableColorBlend = 0;
    DOPPLEGANGER.zPriority = g_unkGraphicsStruct.g_zEntityCenter + 8;
    if (DOPPLEGANGER.posX.i.hi < PLAYER.posX.i.hi) {
        DOPPLEGANGER.facingLeft = false;
    } else {
        DOPPLEGANGER.facingLeft = true;
    }

    DOPPLEGANGER.palette = PAL_OVL(0x200);
    DOPPLEGANGER.rotX = 0x100;
    DOPPLEGANGER.rotY = 0x100;
    DOPPLEGANGER.drawMode = DRAW_DEFAULT;
    DOPPLEGANGER.flags =
        FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED | FLAG_UNK_400000;

    // BUG: this loop seems to be clearing parts of the floor
    //      ceiling colliders, but not all of them
    colliderSize = (sizeof(Collider) * 6) + 0x1C;
    colliders = (s32*)g_Dop.colFloor;
    for (i = 0; i < colliderSize; i++, colliders++) {
        *colliders = 0;
    }

    D_us_801D4D74 = 0;
    g_Dop.vram_flag = 0;
    func_us_801C59DC(0);
    entity = &g_Entities[E_ID_41];

    for (i = 0; i < 3; i++, entity++) {
        DestroyEntity(entity);
        entity->animSet = ANIMSET_OVL(1);
        entity->unk5A = i + 9;
        entity->palette = PAL_OVL(0x200);
        entity->flags = FLAG_POS_CAMERA_LOCKED;
    }
    primIndex = g_api.AllocPrimitives(PRIM_TILE, 6);
    prim = &g_PrimBuf[primIndex];
    g_Entities[E_ID_41].primIndex = primIndex;
    g_Entities[E_ID_41].flags |= FLAG_HAS_PRIMS;

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        prim = prim->next;
    }

    for (i = 0; i < 32; i++) {
        angle = (rand() & 0x3FF) + 0x100;
        scale = (rand() & 0xFF) + 0x100;
        D_us_801D4118[i] = ((rcos(angle) << 4) * scale) >> 8;
        D_us_801D4198[i] = -(((rsin(angle) << 4) * scale) >> 7);
    }
}

INCLUDE_ASM("boss/bo4/nonmatchings/doppleganger", func_us_801C1CB0);

extern s32 D_us_801805A0;
extern s16 D_us_801811E8[];
extern s32 D_us_8018120C[];
extern u8 D_us_80183C70[][4];
extern AnimationFrame* D_us_80183CB4[];
extern SpriteParts* D_us_801B159C[];
extern s32 D_us_801D4A1C;

void EntityDoppleganger10(void) {
    s32 i;
    s32 status;
    s16 step;
    s16 step_s;
    s32 var_s5;
    s32 posY;
    s32 posX;
    s32 vram_flag;
    Pos pos;
    Pos unused_pos;
    SpriteParts* parts;

    g_CurrentEntity = &DOPPLEGANGER;
    g_Dop.unk4C = 0;
    var_s5 = 0;
    step = 0;
    step_s = 0;
    var_s5 = 0;
    DOPPLEGANGER.drawFlags = FLAG_DRAW_DEFAULT;

    if (!(g_Dop.status & PLAYER_STATUS_DEAD)) {
        if ((DOPPLEGANGER.step != Dop_Kill) &&
            (DOPPLEGANGER.flags & FLAG_DEAD)) {
            D_us_801805A0 |= 2;
            step = DOPPLEGANGER.step;
            step_s = DOPPLEGANGER.step_s;
            pos.x.val = D_us_8018120C[g_CurrentEntity->nFramesInvincibility];
            SetDopplegangerStep(Dop_Kill);
        } else {
            for (i = 0; i < LEN(g_Dop.timers); i++) {
                if (g_Dop.timers[i]) {
                    switch (i) {
                    case 0:
                    case 1:
                        break;
                    case 2:
                        DOPPLEGANGER.palette = g_Dop.unk40;
                        break;
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                        break;
                    case 15:
                        func_us_801C5354(0, 0);
                        break;
                    }

                    if (--g_Dop.timers[i] == 0) {
                        switch (i) {
                        case 0:
                        case 1:
                            break;
                        case 2:
                            DOPPLEGANGER.palette = PAL_OVL(0x200);
                            break;
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                        case 9:
                        case 10:
                        case 11:
                        case 12:
                        case 13:
                        case 14:
                            break;
                        case 15:
                            func_8010E0B8();
                            break;
                        }
                    }
                }
            }

            g_Dop.padHeld = g_Dop.padPressed;
            if (g_Dop.demo_timer != 0) {
                g_Dop.demo_timer--;
                g_Dop.padPressed = g_Dop.padSim & 0xFFFF;
            } else {
                g_Dop.padPressed = g_pads[1].pressed;
            }

            g_Dop.padTapped =
                (g_Dop.padHeld ^ g_Dop.padPressed) & g_Dop.padPressed;
            if (g_Dop.status & PLAYER_STATUS_UNK8) {
                g_Dop.padTapped &= ~(PAD_SQUARE | PAD_CIRCLE);
                g_Dop.padPressed &= ~(PAD_SQUARE | PAD_CIRCLE);
            }

            if (!g_Dop.timers[14]) {
                if ((g_CurrentEntity->hitFlags > 0) &&
                    (g_CurrentEntity->hitFlags < 4)) {
                    step = DOPPLEGANGER.step;
                    step_s = DOPPLEGANGER.step_s;
                    pos.x.val =
                        D_us_8018120C[g_CurrentEntity->nFramesInvincibility];

                    if ((g_Dop.unk6C - g_Dop.unk6A) >= 10) {
                        pos.y.val = 3;
                    } else {
                        pos.y.val = 2;
                    }

                    i = 3;
                    if (pos.x.val & 0x200) {
                        i = 7;
                    }

                    if (DOPPLEGANGER.step == 0xC) {
                        i = 8;
                    }

                    switch (i) {
                    case 0:
                    case 1:
                    case 2:
                        break;
                    case 3:
                        SetDopplegangerStep(Dop_Hit);
                        break;
                    case 7:
                        SetDopplegangerStep(Dop_StatusStone);
                        break;
                    case 4:
                    case 5:
                    case 6:
                        break;
                    case 8:
                        var_s5 = 1;
                        break;
                    case 9:
                        break;
                    }
                }
            }

            if ((g_Dop.padTapped & PAD_R1) &&
                (DOPPLEGANGER.step == Dop_Stand ||
                 DOPPLEGANGER.step == Dop_Walk ||
                 DOPPLEGANGER.step == Dop_Crouch ||
                 DOPPLEGANGER.step == Dop_Fall ||
                 DOPPLEGANGER.step == Dop_Jump ||
                 DOPPLEGANGER.step == Dop_HighJump ||
                 DOPPLEGANGER.step == Dop_MorphMist)) {
                if (DOPPLEGANGER.step == Dop_Crouch) {
                    D_us_801D4A1C = 12;
                }
                g_api.PlaySfx(SFX_TRANSFORM_LOW);
                if (DOPPLEGANGER.rotZ == FIX(1.0 / 32.0)) {
                    DOPPLEGANGER.rotZ = 0;
                    DOPPLEGANGER.animCurFrame = 0x9D;
                    DOPPLEGANGER.facingLeft++;
                    DOPPLEGANGER.facingLeft &= 1;
                }
                SetDopplegangerStep(Dop_MorphBat);
                g_Dop.unk66 = 0;
            }
            if ((g_Dop.padTapped & PAD_R2) &&
                (DOPPLEGANGER.step == Dop_Stand ||
                 DOPPLEGANGER.step == Dop_Walk ||
                 DOPPLEGANGER.step == Dop_Crouch ||
                 DOPPLEGANGER.step == Dop_Fall ||
                 DOPPLEGANGER.step == Dop_Jump ||
                 DOPPLEGANGER.step == Dop_HighJump ||
                 DOPPLEGANGER.step == Dop_MorphBat)) {
                if (DOPPLEGANGER.rotZ == FIX(1.0 / 32.0)) {
                    DOPPLEGANGER.rotZ = 0;
                    DOPPLEGANGER.animCurFrame = 0x9D;
                    DOPPLEGANGER.facingLeft++;
                    DOPPLEGANGER.facingLeft &= 1;
                }
                SetDopplegangerStep(Dop_MorphMist);
                g_api.PlaySfx(SFX_TRANSFORM_LOW);
            }
        }
    }
    g_Dop.prev_step = DOPPLEGANGER.step;
    g_Dop.prev_step_s = DOPPLEGANGER.step_s;

    switch (DOPPLEGANGER.step) {
    case Dop_Stand:
        DopplegangerStepStand();
        break;
    case Dop_Walk:
        DopplegangerStepWalk();
        break;
    case Dop_Crouch:
        DopplegangerStepCrouch();
        break;
    case Dop_Fall:
        DopplegangerStepFall();
        break;
    case Dop_Jump:
        DopplegangerStepJump();
        break;
    case Dop_MorphBat:
        ControlBatForm();
        break;
    case Dop_UnmorphBat:
        DopplegangerStepUnmorphBat();
        break;
    case Dop_MorphMist:
        ControlMistForm();
        break;
    case Dop_UnmorphMist:
        DopplegangerStepUnmorphMist();
        break;
    case Dop_HighJump:
        DopplegangerStepHighJump();
        break;
    case Dop_SwordWarp:
        DopplegangerStepSwordWarp();
        break;
    case Dop_Hit:
        DopplegangerHandleDamage(&pos, step, step_s);
        break;
    case Dop_Kill:
        DopplegangerStepKill(&pos, step, step_s);
        break;
    case Dop_StatusStone:
        DopplegangerStepStone(var_s5);
        break;
    }

    g_Dop.status &= ~PLAYER_STATUS_UNK8;
    // TODO: is unk08 previous status?
    g_Dop.unk08 = g_Dop.status;

    status = 0;

    switch (DOPPLEGANGER.step) {
    case Dop_Crouch:
        if (DOPPLEGANGER.step_s != 2) {
            status = PLAYER_STATUS_CROUCH;
        }
        // fallthrough
    case Dop_Stand:
    case Dop_Walk:
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        break;
    case Dop_Fall:
    case Dop_Jump:
        status = PLAYER_STATUS_UNK2000;
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        break;
    case Dop_MorphBat:
        func_us_801C5354(1, 1);
        if (DOPPLEGANGER.step_s == 3) {
            func_us_801C5430(1, 4);
        }
        status = PLAYER_STATUS_UNK100000 | PLAYER_STATUS_BAT_FORM;
        ;
        if (DOPPLEGANGER.step_s) {
            DOPPLEGANGER.animSet = ANIMSET_OVL(2);
        }
        break;
    case Dop_MorphMist:
        func_us_801C5354(1, 1);
        func_us_801C5430(1, 4);
        status = PLAYER_STATUS_UNK100000 | PLAYER_STATUS_MIST_FORM;
        DOPPLEGANGER.palette = PAL_OVL(0x20D);
        break;
    case Dop_UnmorphMist:
        func_us_801C5354(1, 1);
        status = PLAYER_STATUS_UNK800000 | PLAYER_STATUS_UNK100000 |
                 PLAYER_STATUS_MIST_FORM;
        DOPPLEGANGER.palette = PAL_OVL(0x20D);
        func_us_801C5430(1, 4);
        break;
    case Dop_UnmorphBat:
        func_us_801C5354(1, 1);
        status = PLAYER_STATUS_UNK400000 | PLAYER_STATUS_UNK100000 |
                 PLAYER_STATUS_BAT_FORM;
        if (DOPPLEGANGER.step_s == 0) {
            DOPPLEGANGER.animSet = ANIMSET_OVL(2);
        }
        func_us_801C5430(1, 4);
        break;
    case Dop_HighJump:
        func_us_801C5354(1, 1);
        func_us_801C5430(1, 4);
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        break;
    case Dop_Hit:
        status = PLAYER_STATUS_UNK100000 | PLAYER_STATUS_UNK10000;
        func_us_801C5354(1, 1);
        func_us_801C5430(1, 4);
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        break;
    case Dop_Kill:
        status = PLAYER_STATUS_UNK100000 | PLAYER_STATUS_DEAD |
                 PLAYER_STATUS_UNK10000;
        if (DOPPLEGANGER.step_s == 0x80) {
            status |= PLAYER_STATUS_UNK80000;
        }
        func_us_801C5354(1, 1);
        func_us_801C5430(1, 4);
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        break;
    case Dop_SwordWarp:
        status = PLAYER_STATUS_UNK100000;
        func_us_801C5354(1, 1);
        func_us_801C5430(4, 0x30);
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        DOPPLEGANGER.palette = PAL_OVL(0x20D);
        break;
    case Dop_StatusStone:
        status = PLAYER_STATUS_UNK100000 | PLAYER_STATUS_UNK10000 |
                 PLAYER_STATUS_STONE;
        func_us_801C5354(1, 1);
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        break;
    }

    if (g_Dop.timers[0]) {
        status |= PLAYER_STATUS_UNK100000 | PLAYER_STATUS_POISON;
        func_us_801C5354(1, 1);
    }

    g_Dop.status = status;

    if ((g_Dop.unk08 & PLAYER_STATUS_UNK10000) &&
        !(g_Dop.status & (PLAYER_STATUS_DEAD | PLAYER_STATUS_UNK10000))) {
        g_Dop.timers[15] = 4;
        DOPPLEGANGER.palette = PAL_OVL(0x200);
    }
    PlayAnimation(D_us_80183C70, D_us_80183CB4);
    if (g_Dop.status & PLAYER_STATUS_DEAD) {
        if (DOPPLEGANGER.poseTimer < 0) {
            DOPPLEGANGER.animCurFrame |= 0x8000;
        }
        DOPPLEGANGER.hitboxState = 0;
    } else {
        DOPPLEGANGER.hitboxState = g_Dop.unk70;
        if (g_Dop.status & PLAYER_STATUS_STONE) {
            DOPPLEGANGER.hitboxState &= 0xFFCF;
        }
        if ((g_Dop.timers[13] | g_Dop.timers[14]) != 0) {
            DOPPLEGANGER.hitboxState = 0;
        }
    }
    func_8010D59C();
    vram_flag = g_Dop.vram_flag;
    posX = DOPPLEGANGER.posX.val;
    posY = DOPPLEGANGER.posY.val;

    if ((g_Dop.status & PLAYER_STATUS_BAT_FORM) ||
        DOPPLEGANGER.step == Dop_HighJump ||
        abs(DOPPLEGANGER.velocityX) > FIX(2)) {

        DOPPLEGANGER.velocityX >>= 2;
        DOPPLEGANGER.velocityY >>= 2;
        if (DOPPLEGANGER.posY.i.hi >= 0) {
            if (g_Dop.status & PLAYER_STATUS_UNK400000) {
                func_us_801C1CB0(0);
            } else {
                func_us_801C1CB0(1);
            }
        }
        if (DOPPLEGANGER.posY.i.hi >= 0) {
            func_us_801C1CB0(0);
        }
        if (DOPPLEGANGER.posY.i.hi >= 0) {
            func_us_801C1CB0(0);
        }
        if (DOPPLEGANGER.posY.i.hi >= 0) {
            func_us_801C1CB0(0);
        }
        if (DOPPLEGANGER.posY.i.hi < 0) {
            DOPPLEGANGER.posY.val = FIX(-1);
        }

        DOPPLEGANGER.velocityX *= 4;
        DOPPLEGANGER.velocityY *= 4;
    } else if (g_Dop.status & PLAYER_STATUS_UNK800000) {
        func_us_801C1CB0(0);
    } else {
        func_us_801C1CB0(1);
    }

    g_Dop.unk04 = vram_flag;
    func_8010D800();

    if (DOPPLEGANGER.animSet == (s16)ANIMSET_OVL(2)) {
        parts = D_us_801B159C[DOPPLEGANGER.animCurFrame & 0x7FFF];

        parts->parts[0].offsetx =
            D_us_801D4A1C + D_us_801811E8[DOPPLEGANGER.animCurFrame];
    }

    FntPrint("noroi:%02x\n", g_Dop.timers[1]);
}

typedef enum {
    THINK_STEP_0 = 0,
    THINK_STEP_1,
    THINK_STEP_2,
    THINK_STEP_3,
    THINK_STEP_4,
    THINK_STEP_5,
    THINK_STEP_6,
    THINK_STEP_7,
    THINK_STEP_14 = 14,
    THINK_STEP_15,
    THINK_STEP_GAME_OVER,
    THINK_STEP_17,
    THINK_STEP_BACKDASH,
    THINK_STEP_WAIT,
} ThinkStep;

extern s32 D_us_801D3D24; // think_step
extern s32 D_us_801D3D28; // timer
extern s32 D_us_801D3D2C; // timer

static void DopplegangerThinking(void) {
    s32 posX;
    s32 playerDistanceX;
    u32 facingLeft;

    posX = g_Tilemap.scrollX.i.hi + DOPPLEGANGER.posX.i.hi;
    g_Dop.demo_timer = 2;
    g_Dop.padSim = PAD_NONE;

    if (g_Player.status & PLAYER_STATUS_DEAD) {
        D_us_801D3D24 = THINK_STEP_GAME_OVER;
    }
    if (g_Dop.status & PLAYER_STATUS_UNK10000) {
        D_us_801D3D24 = THINK_STEP_0;
    }
    if (g_Dop.status & PLAYER_STATUS_STONE) {
        D_us_801D3D24 = THINK_STEP_15;
    }

    if ((g_Player.timers[ALU_T_12]) &&
        (D_us_801D3D24 != THINK_STEP_GAME_OVER) &&
        !(g_Dop.status & PLAYER_STATUS_MIST_FORM)) {
        g_Dop.padSim = PAD_R2;
        D_us_801D3D28 = 64;
        D_us_801D3D24 = THINK_STEP_14;
    }

    facingLeft = false;
    if ((DOPPLEGANGER.posX.i.hi - PLAYER.posX.i.hi) >= 0) {
        facingLeft = true;
    }

    playerDistanceX = abs(DOPPLEGANGER.posX.i.hi - PLAYER.posX.i.hi);

    FntPrint("hm:%02x\n", playerDistanceX);
    FntPrint("think_step:%02x\n", D_us_801D3D24);

    switch (D_us_801D3D24) {
    case THINK_STEP_0:
        if (!(g_Dop.status & PLAYER_STATUS_UNK10000)) {
            if (g_Player.timers[ALU_T_10]) {
                if (rand() & 1) {
                    if (facingLeft) {
                        g_Dop.padSim = PAD_LEFT;
                    } else {
                        g_Dop.padSim = PAD_RIGHT;
                    }
                    g_Dop.padSim |= PAD_CROSS;
                    D_us_801D3D24 = THINK_STEP_7;
                } else {
                    g_Dop.padSim |= PAD_DOWN;
                    D_us_801D3D24 = THINK_STEP_5;
                    D_us_801D3D28 = 72;
                }
            } else if (abs(DOPPLEGANGER.posY.i.hi - PLAYER.posY.i.hi) > 32) {
                if (facingLeft) {
                    g_Dop.padSim = PAD_LEFT;
                } else {
                    g_Dop.padSim = PAD_RIGHT;
                }
                g_Dop.padSim |= PAD_CROSS;
                D_us_801D3D24 = THINK_STEP_7;
            } else if (playerDistanceX > 80) {
                if (facingLeft) {
                    g_Dop.padSim = PAD_LEFT;
                } else {
                    g_Dop.padSim = PAD_RIGHT;
                }
            } else {
                D_us_801D3D28 = 16;
                D_us_801D3D24 = THINK_STEP_1;
            }
        }
        break;

    case THINK_STEP_1:
        if (DOPPLEGANGER.facingLeft != facingLeft) {
            if (facingLeft) {
                g_Dop.padSim = PAD_LEFT;
            } else {
                g_Dop.padSim = PAD_RIGHT;
            }
        }
        if (playerDistanceX > 80) {
            D_us_801D3D24 = THINK_STEP_0;
        } else {
            if ((posX < 96 && DOPPLEGANGER.facingLeft == false) ||
                (posX > 416 && DOPPLEGANGER.facingLeft)) {
                D_us_801D3D28 = 64;
                g_Dop.padSim |= PAD_R1;
                D_us_801D3D24 = THINK_STEP_3;
                break;
            }

            if ((g_Player.timers[ALU_T_9]) ||
                ((g_Player.status & PLAYER_STATUS_CROUCH) && (rand() & 1))) {
                switch (rand() & 7) {
                case 0:
                case 6:
                case 7:
                    g_Dop.padSim |= PAD_CROSS;
                    D_us_801D3D24 = THINK_STEP_6;
                    D_us_801D3D28 = 72;
                    break;
                case 1:
                    g_Dop.padSim |= PAD_DOWN;
                    D_us_801D3D24 = THINK_STEP_5;
                    D_us_801D3D28 = 72;
                    break;
                case 2:
                    if (g_Player.status & PLAYER_STATUS_CROUCH) {
                        g_Dop.padSim |= PAD_DOWN;
                        D_us_801D3D24 = THINK_STEP_5;
                        D_us_801D3D28 = 72;
                        break;
                    }
                    // fallthrough
                case 3:
                case 4:
                case 5:
                    g_Dop.padSim |= PAD_TRIANGLE;
                    D_us_801D3D24 = THINK_STEP_2;
                    D_us_801D3D28 = 32;
                    break;
                }
            } else if (g_Player.timers[ALU_T_10]) {
                if (rand() & 1) {
                    if (facingLeft) {
                        g_Dop.padSim = PAD_LEFT;
                    } else {
                        g_Dop.padSim = PAD_RIGHT;
                    }
                    g_Dop.padSim |= PAD_CROSS;
                    D_us_801D3D24 = THINK_STEP_7;
                } else {
                    g_Dop.padSim |= PAD_DOWN;
                    D_us_801D3D24 = THINK_STEP_5;
                    D_us_801D3D28 = 72;
                }
            } else {
                if (playerDistanceX < 56) {
                    if (D_us_801D3D2C) {
                        D_us_801D3D2C--;
                    } else {

                        // n.b.! Doppleganger can get locked here
                        //       if none of the preamble conditions override the
                        //       current step. This causes him to remain in the
                        //       crouch position attacking every 32 frames. If
                        //       the player is near a door, elevated above
                        //       Doppleganger, the attack will never hit, the
                        //       distance will never change and Dop will just
                        //       keep swinging.

                        g_Dop.padSim |= PAD_SQUARE;
                        D_us_801D3D2C = 32;
                    }
                } else if (--D_us_801D3D28 == 0) {
                    g_Dop.padSim |= PAD_UP | PAD_SQUARE;
                    D_us_801D3D28 = 112;
                    D_us_801D3D2C = 32;
                }
            }
        }
        break;
    case THINK_STEP_2:
        if (--D_us_801D3D28 == 0) {
            g_Dop.padSim = PAD_UP | PAD_CIRCLE;
            D_us_801D3D24 = THINK_STEP_0;
            D_us_801D3D28 = 112;
        }
        break;

    case THINK_STEP_3:
        if (DOPPLEGANGER.step_s) {
            g_Dop.padSim = PAD_SQUARE;
            D_us_801D3D28 = 24;
            D_us_801D3D24 = THINK_STEP_4;
        }
        break;

    case THINK_STEP_4:
        if (!(g_GameTimer % 2)) {
            g_Dop.padSim = PAD_UP;
        }

        if (--D_us_801D3D28 == 0) {
            g_Dop.padSim = PAD_R1;
            D_us_801D3D24 = THINK_STEP_0;
        }
        break;

    case THINK_STEP_5:
        if ((--D_us_801D3D28 == 0) || !(g_Dop.status & PLAYER_STATUS_CROUCH)) {
            D_us_801D3D24 = THINK_STEP_0;
            D_us_801D3D2C = 32;
        }
        if (DOPPLEGANGER.facingLeft != facingLeft) {
            if (facingLeft) {
                g_Dop.padSim = PAD_LEFT;
            } else {
                g_Dop.padSim = PAD_RIGHT;
            }
        }
        g_Dop.padSim |= PAD_DOWN;
        if (playerDistanceX < 56) {
            if (D_us_801D3D2C) {
                D_us_801D3D2C--;
            } else {
                // crouch attack
                g_Dop.padSim |= PAD_DOWN | PAD_SQUARE;
                D_us_801D3D2C = 32;
            }
        }
        break;
    case THINK_STEP_6:
        if (g_Dop.vram_flag & 1) {
            D_us_801D3D24 = THINK_STEP_0;
        } else {
            g_Dop.padSim |= PAD_CROSS;
            if (!(g_GameTimer % 32)) {
                g_Dop.padSim |= PAD_UP | PAD_CIRCLE;
            }
        }
        break;
    case THINK_STEP_7:
        if (g_Dop.vram_flag & 1) {
            D_us_801D3D24 = THINK_STEP_0;
        } else {
            if (playerDistanceX > 16) {
                if (DOPPLEGANGER.facingLeft) {
                    g_Dop.padSim = PAD_LEFT;
                } else {
                    g_Dop.padSim = PAD_RIGHT;
                }
            }

            g_Dop.padSim |= PAD_CROSS;
            if (DOPPLEGANGER.velocityY > 0) {
                if (DOPPLEGANGER.velocityY > FIX(2)) {
                    g_Dop.padSim |= PAD_DOWN | PAD_SQUARE | PAD_CROSS;
                }

                if (abs(DOPPLEGANGER.posY.i.hi - PLAYER.posY.i.hi) < 16) {
                    g_Dop.padSim |= PAD_DOWN | PAD_SQUARE;
                }
            }
        }
        break;
    case THINK_STEP_14:
        if (!(g_GameTimer % 8)) {
            g_Dop.padSim = PAD_UP;
        }
        if (!(g_Dop.status & PLAYER_STATUS_MIST_FORM) && (g_GameTimer & 1)) {
            g_Dop.padSim = PAD_R2;
        }

        if (--D_us_801D3D28 == 0) {
            if (g_Dop.status & PLAYER_STATUS_MIST_FORM) {
                g_Dop.padSim = PAD_R2;
            }
            D_us_801D3D24 = THINK_STEP_0;
        }
        break;
    case THINK_STEP_15:
        if (!(g_Dop.status & PLAYER_STATUS_STONE)) {
            D_us_801D3D24 = THINK_STEP_0;
        }
        if (!(g_GameTimer & 0xF)) {
            g_Dop.padSim = PAD_UP;
        }
        break;
    case THINK_STEP_GAME_OVER:
        if (!(g_Player.status & PLAYER_STATUS_DEAD)) {
            D_us_801D3D24 = THINK_STEP_0;
        }
        g_Dop.padSim = PAD_UP;
        // transform back to doppleganger form
        if (g_Dop.status & PLAYER_STATUS_BAT_FORM) {
            g_Dop.padSim = PAD_R1;
        }
        if (g_Dop.status & PLAYER_STATUS_MIST_FORM) {
            g_Dop.padSim = PAD_R2;
        }
        break;
    case THINK_STEP_17:
        if (abs(DOPPLEGANGER.posY.i.hi - PLAYER.posY.i.hi) < 8) {
            D_us_801D3D24 = THINK_STEP_0;
        }
        break;
    case THINK_STEP_BACKDASH:
        if (DOPPLEGANGER.step == Dop_Stand) {
            // backdash
            g_Dop.padSim |= PAD_TRIANGLE;
            D_us_801D3D24 = THINK_STEP_WAIT;
            D_us_801D3D2C = 64;
        }
        break;
    case THINK_STEP_WAIT:
        if (--D_us_801D3D2C == 0) {
            D_us_801D3D24 = THINK_STEP_0;
        }
        break;
    }
}

extern EInit D_us_80180410;

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
} Unk_Dop;

extern Unk_Dop D_us_801D4DDA;

void func_us_801C37B4(Entity* self) {
    s32 i;
    Entity* entity;
    s16 hitPoints;

    D_us_801D4DDA.unk0 = DOPPLEGANGER.hitPoints;
    if (self->step == 0) {
        InitializeEntity(D_us_80180410);
        func_us_801C1A38();

        entity = &g_Entities[STAGE_ENTITY_START + 4];
        for (i = (STAGE_ENTITY_START + 4); i < (STAGE_ENTITY_START + 80); i++,
            entity++) {
            DestroyEntity(entity);
        }

        D_us_801D4DDA.unk4 = D_us_801D4DDA.unk0 = D_us_801D4DDA.unk2 =
            DOPPLEGANGER.hitPoints;

        D_us_801D4DDA.unk6 = DOPPLEGANGER.hitboxState;
        D_us_801D3D24 = THINK_STEP_BACKDASH;
        func_us_801C5354(1, 48);
    } else {
        DopplegangerThinking();
        EntityDoppleganger10();
        func_us_801CA014();
    }
    D_us_801D4DDA.unk2 = D_us_801D4DDA.unk0;
    FntPrint("life:%02x\n", DOPPLEGANGER.hitPoints);
}

INCLUDE_ASM("boss/bo4/nonmatchings/doppleganger", func_us_801C38C0);

INCLUDE_ASM("boss/bo4/nonmatchings/doppleganger", func_us_801C3EEC);

extern Point16 D_us_801812AC[];

void func_us_801C44C8(void) {
    Collider collider;

    s16* dopY;
    s16* dopX;
    s32 effects;
    s32 i;
    u32* pVramFlag;

    s16 offsetX, offsetY;

    dopY = &DOPPLEGANGER.posY.i.hi;
    dopX = &DOPPLEGANGER.posX.i.hi;

    pVramFlag = &g_Dop.vram_flag;
    effects =
        g_Dop.unk04 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                       EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if (effects == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID) ||
        effects == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID) ||
        effects == (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                    EFFECT_SOLID)) {
        *pVramFlag |= 4;
        return;
    }

    for (i = 0; i < 7; i++) {
        effects = g_Dop.colWall[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_UNK_0002 | EFFECT_SOLID);
        if ((effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_0002 | EFFECT_SOLID))) {

            offsetX = *dopX + D_us_801812AC[i].x + g_Dop.colWall[i].unk4 - 1;
            offsetY = *dopY + D_us_801812AC[i].y;
            g_api.CheckCollision(offsetX, offsetY, &collider, 0);

            if (!(collider.effects & EFFECT_SOLID)) {
                *pVramFlag |= 4;
                *dopX += g_Dop.colWall[i].unk4;
                return;
            }
        }

        if ((effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                EFFECT_UNK_8000 &&
            i != 0 &&
            ((g_Dop.colWall[0].effects & EFFECT_UNK_0800) ||
             !(g_Dop.colWall[0].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *pVramFlag |= 4;
            *dopX += g_Dop.colWall[i].unk4;
            return;
        }

        if ((effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                EFFECT_UNK_0800 &&
            i != 6 &&
            ((g_Dop.colWall[6].effects & EFFECT_UNK_8000) ||
             !(g_Dop.colWall[6].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *pVramFlag |= 4;
            *dopX += g_Dop.colWall[i].unk4;
            return;
        }
    }
}

extern Point16 D_us_801812AC[];

void func_us_801C4710(void) {
    Collider collider;

    s16* dopY;
    s16* dopX;
    s32 effects;
    s32 i;
    u32* pVramFlag;

    s16 offsetX, offsetY;
    dopY = &DOPPLEGANGER.posY.i.hi;
    dopX = &DOPPLEGANGER.posX.i.hi;

    pVramFlag = &g_Dop.vram_flag;
    effects =
        g_Dop.unk04 &
        (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0800 |
         EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if (effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                    EFFECT_SOLID) ||
        effects == (EFFECT_UNK_0800 | EFFECT_UNK_0400 | EFFECT_UNK_0002 |
                    EFFECT_SOLID) ||
        effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                    EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID)) {
        *pVramFlag |= 8;
        return;
    }

    for (i = 7; i < 14; i++) {
        effects = g_Dop.colWall[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_UNK_0002 | EFFECT_SOLID);
        if (effects == (EFFECT_UNK_8000 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_0800 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                        EFFECT_SOLID) ||
            effects == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                        EFFECT_SOLID) ||
            effects == (EFFECT_UNK_0002 | EFFECT_SOLID)) {

            offsetX = *dopX + D_us_801812AC[i].x + g_Dop.colWall[i].unkC + 1;
            offsetY = *dopY + D_us_801812AC[i].y;
            g_api.CheckCollision(offsetX, offsetY, &collider, 0);

            if (!(collider.effects & EFFECT_SOLID)) {
                *pVramFlag |= 8;
                *dopX += g_Dop.colWall[i].unkC;
                return;
            }
        }

        if ((effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                (EFFECT_UNK_8000 | EFFECT_UNK_4000) &&
            i != 7 &&
            ((g_Dop.colWall[7].effects & EFFECT_UNK_0800) ||
             !(g_Dop.colWall[7].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *pVramFlag |= 8;
            *dopX += g_Dop.colWall[i].unkC;
            return;
        }

        if (((effects &
              (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
             (EFFECT_UNK_4000 | EFFECT_UNK_0800)) &&
            i != 13 &&
            ((g_Dop.colWall[13].effects & EFFECT_UNK_8000) ||
             !(g_Dop.colWall[13].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *pVramFlag |= 8;
            *dopX += g_Dop.colWall[i].unkC;
            return;
        }
    }
}
