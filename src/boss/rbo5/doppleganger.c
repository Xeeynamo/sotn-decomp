// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

extern s32 D_us_801D36E8[];
extern s32 D_us_801D3768[];
extern s32 D_us_801D4344;

static void func_us_801C096C(void) {
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
    DOPPLEGANGER.scaleX = 0x100;
    DOPPLEGANGER.scaleY = 0x100;
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

    D_us_801D4344 = 1;
    g_Dop.vram_flag = 1;
    func_8010E570(0);
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
        D_us_801D36E8[i] = ((rcos(angle) << 4) * scale) >> 8;
        D_us_801D3768[i] = -(((rsin(angle) << 4) * scale) >> 7);
    }

    g_api.TimeAttackController(
        TIMEATTACK_EVENT_DOPPLEGANGER_40_DEFEAT, TIMEATTACK_SET_VISITED);
}

static s16 D_us_80181274[] = {
    -0x30, -0x30, -0x2F, -0x28, -0x29, -0x1E, -0x1F, -0x1E, -0x29,
    -0x29, -0x31, -0x33, -0x33, -0x2A, -0x29, -0x1D, -0x1D, 0,
};
static s32 D_us_80181298[] = {
    FIX(1.0 / 2048.0), FIX(1.0 / 1024.0), FIX(1.0 / 2.0),    FIX(1.0 / 8.0),
    FIX(1.0 / 4.0),    FIX(1.0 / 16.0),   FIX(1.0 / 32.0),   FIX(1.0 / 128.0),
    FIX(1.0 / 256.0),  FIX(1.0 / 2048.0),
    FIX(1.0 / 512.0), // different from bo4
    FIX(1.0 / 2048.0), FIX(1.0 / 2048.0), FIX(1.0 / 2048.0), FIX(1.0 / 2048.0),
    FIX(1.0 / 2048.0),
};

#include "../dop_check_st_collision.h"

extern s32 D_us_801805B8;
extern u8 D_us_80183CFC[][4];
extern AnimationFrame* D_us_80183D40[];
extern SpriteParts* D_us_801B1674[];
extern s32 D_us_801D3FEC;

void EntityDoppleganger40(void) {
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
            D_us_801805B8 |= 2;
            step = DOPPLEGANGER.step;
            step_s = DOPPLEGANGER.step_s;
            pos.x.val = D_us_80181298[g_CurrentEntity->nFramesInvincibility];
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
                        func_us_801C4954(0, 0);
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
                        D_us_80181298[g_CurrentEntity->nFramesInvincibility];

                    if ((g_Dop.unk6C - g_Dop.unk6A) >= 10) {
                        pos.y.val = 3;
                    } else {
                        pos.y.val = 2;
                    }

                    i = 3;
                    if (pos.x.val & 0x200) {
                        i = 7;
                    }

                    if (DOPPLEGANGER.step == Dop_StatusStone) {
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
                    D_us_801D3FEC = 12;
                }
                g_api.PlaySfx(SFX_TRANSFORM_LOW);
                if (DOPPLEGANGER.rotate == FIX(1.0 / 32.0)) {
                    DOPPLEGANGER.rotate = 0;
                    DOPPLEGANGER.animCurFrame = 0x9D;
                    DOPPLEGANGER.facingLeft++;
                    DOPPLEGANGER.facingLeft &= 1;
                }
                SetDopplegangerStep(6);
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
                if (DOPPLEGANGER.rotate == FIX(1.0 / 32.0)) {
                    DOPPLEGANGER.rotate = 0;
                    DOPPLEGANGER.animCurFrame = 0x9D;
                    DOPPLEGANGER.facingLeft++;
                    DOPPLEGANGER.facingLeft &= 1;
                }
                SetDopplegangerStep(8);
                g_api.PlaySfx(SFX_TRANSFORM_LOW);
            }

            if ((g_Dop.padTapped & PAD_TRIANGLE) &&
                (g_Dop.padPressed & PAD_DOWN) && DOPPLEGANGER.step == 3) {
                func_us_801C504C();
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
        g_api.TimeAttackController(
            TIMEATTACK_EVENT_DOPPLEGANGER_40_DEFEAT, true);
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
        func_us_801C4954(1, 1);
        if (DOPPLEGANGER.step_s == 3) {
            func_us_801C4A30(1, 4);
        }
        status = PLAYER_STATUS_UNK100000 | PLAYER_STATUS_BAT_FORM;
        if (DOPPLEGANGER.step_s) {
            DOPPLEGANGER.animSet = ANIMSET_OVL(2);
        }
        break;
    case Dop_MorphMist:
        func_us_801C4954(1, 1);
        func_us_801C4A30(1, 4);
        status = PLAYER_STATUS_UNK100000 | PLAYER_STATUS_MIST_FORM;
        DOPPLEGANGER.palette = PAL_OVL(0x20D);
        break;
    case Dop_UnmorphMist:
        func_us_801C4954(1, 1);
        status = PLAYER_STATUS_UNK800000 | PLAYER_STATUS_UNK100000 |
                 PLAYER_STATUS_MIST_FORM;
        DOPPLEGANGER.palette = PAL_OVL(0x20D);
        func_us_801C4A30(1, 4);
        break;
    case Dop_UnmorphBat:
        func_us_801C4954(1, 1);
        status = PLAYER_STATUS_UNK400000 | PLAYER_STATUS_UNK100000 |
                 PLAYER_STATUS_BAT_FORM;
        if (DOPPLEGANGER.step_s == 0) {
            DOPPLEGANGER.animSet = ANIMSET_OVL(2);
        }
        func_us_801C4A30(1, 4);
        break;
    case Dop_HighJump:
        func_us_801C4954(1, 1);
        func_us_801C4A30(1, 4);
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        break;
    case Dop_Hit:
        status = PLAYER_STATUS_UNK100000 | PLAYER_STATUS_UNK10000;
        func_us_801C4954(1, 1);
        func_us_801C4A30(1, 4);
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        break;
    case Dop_Kill:
        status = PLAYER_STATUS_UNK100000 | PLAYER_STATUS_DEAD |
                 PLAYER_STATUS_UNK10000;
        if (DOPPLEGANGER.step_s == 0x80) {
            status |= PLAYER_STATUS_UNK80000;
        }
        func_us_801C4954(1, 1);
        func_us_801C4A30(1, 4);
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        break;
    case Dop_SwordWarp:
        status = PLAYER_STATUS_UNK100000;
        func_us_801C4954(1, 1);
        func_us_801C4A30(4, 0x30);
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        DOPPLEGANGER.palette = PAL_OVL(0x20D);
        break;
    case 12:
        status = PLAYER_STATUS_UNK100000 | PLAYER_STATUS_UNK10000 |
                 PLAYER_STATUS_STONE;
        func_us_801C4954(1, 1);
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        break;
    }

    if (g_Dop.timers[0]) {
        status |= PLAYER_STATUS_UNK100000 | PLAYER_STATUS_POISON;
        func_us_801C4954(1, 1);
    }

    g_Dop.status = status;

    if ((g_Dop.unk08 & PLAYER_STATUS_UNK10000) &&
        !(g_Dop.status & (PLAYER_STATUS_DEAD | PLAYER_STATUS_UNK10000))) {
        g_Dop.timers[15] = 4;
        DOPPLEGANGER.palette = PAL_OVL(0x200);
    }
    OVL_EXPORT(PlayAnimation)(D_us_80183CFC, D_us_80183D40);
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
    OVL_EXPORT(func_8010D59C)();
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
                OVL_EXPORT(CheckStageCollision)(0);
            } else {
                OVL_EXPORT(CheckStageCollision)(1);
            }
        }
        if (DOPPLEGANGER.posY.i.hi >= 0) {
            OVL_EXPORT(CheckStageCollision)(0);
        }
        if (DOPPLEGANGER.posY.i.hi >= 0) {
            OVL_EXPORT(CheckStageCollision)(0);
        }
        if (DOPPLEGANGER.posY.i.hi >= 0) {
            OVL_EXPORT(CheckStageCollision)(0);
        }
        if (DOPPLEGANGER.posY.i.hi < 0) {
            DOPPLEGANGER.posY.val = FIX(-1);
        }

        DOPPLEGANGER.velocityX *= 4;
        DOPPLEGANGER.velocityY *= 4;
    } else if (g_Dop.status & PLAYER_STATUS_UNK800000) {
        OVL_EXPORT(CheckStageCollision)(0);
    } else {
        OVL_EXPORT(CheckStageCollision)(1);
    }

    g_Dop.unk04 = vram_flag;
    OVL_EXPORT(func_8010D800)();

    if (DOPPLEGANGER.animSet == (s16)ANIMSET_OVL(2)) {
        parts = D_us_801B1674[DOPPLEGANGER.animCurFrame & 0x7FFF];

        parts->parts[0].offsetx =
            D_us_801D3FEC + D_us_80181274[DOPPLEGANGER.animCurFrame];
    }

    FntPrint("noroi:%02x\n", g_Dop.timers[1]);
}

static s32 D_us_801D32F4;
static s32 D_us_801D32F8;

void func_us_801C1DB0(s32 arg0) {
    D_us_801D32F4 = arg0;
    D_us_801D32F8 = 0;
}

extern s32 D_us_801805B0;
static s32 D_us_801D32FC;
static s32 D_us_801D3300;
static s32 D_us_801D3304;

void func_us_801C1DC8(void) {
    s32 dopOffsetX;
    s32 flags;
    s32 playerDistance;
    u32 playerLeft;

    flags = 0;
    dopOffsetX = g_Tilemap.scrollX.i.hi + DOPPLEGANGER.posX.i.hi;
    g_Dop.demo_timer = 2;
    g_Dop.padSim = PAD_NONE;
    playerLeft = false;
    if ((DOPPLEGANGER.posX.i.hi - PLAYER.posX.i.hi) >= 0) {
        playerLeft = true;
    }
    playerDistance = abs(DOPPLEGANGER.posX.i.hi - PLAYER.posX.i.hi);

    if (g_Player.status & PLAYER_STATUS_DEAD) {
        func_us_801C1DB0(0x10);
    } else if (g_Dop.status & PLAYER_STATUS_STONE) {
        func_us_801C1DB0(0xF);
    } else if (g_Dop.status & PLAYER_STATUS_UNK10000) {
        func_us_801C1DB0(0);
    } else if (g_Player.timers[12] && D_us_801D32F4 != 0xE) {
        func_us_801C1DB0(0xE);
    }

    switch (D_us_801D32F4) {
    case 0:
        if (!(g_Dop.status & PLAYER_STATUS_UNK10000)) {
            if (DOPPLEGANGER.facingLeft != playerLeft) {
                if (playerLeft) {
                    g_Dop.padSim = PAD_LEFT;
                } else {
                    g_Dop.padSim = PAD_RIGHT;
                }
            }
            if (g_Player.timers[10]) {
                if (rand() & 1) {
                    func_us_801C1DB0(7);
                } else {
                    func_us_801C1DB0(5);
                }
                break;
            }

            if (abs(DOPPLEGANGER.posY.i.hi - PLAYER.posY.i.hi) >= 0x21) {
                func_us_801C1DB0(7);
                break;
            }

            if (playerDistance >= 0x51) {
                if (playerLeft) {
                    g_Dop.padSim = PAD_LEFT;
                } else {
                    g_Dop.padSim = PAD_RIGHT;
                }
            } else {
                func_us_801C1DB0(1);
            }
        }
        break;
    case 1:
        if (D_us_801D32F8 == 0) {
            D_us_801D32FC = 0x20;
            D_us_801D3300 = 8;
            D_us_801D32F8++;
        }
        if (DOPPLEGANGER.facingLeft != playerLeft) {
            if (playerLeft) {
                g_Dop.padSim = PAD_LEFT;
            } else {
                g_Dop.padSim = PAD_RIGHT;
            }
        }
        if (playerDistance > 0x50) {
            func_us_801C1DB0(0);
            break;
        }

        if (dopOffsetX < 0x30) {
            if (!DOPPLEGANGER.facingLeft) {
                g_Dop.padSim = PAD_RIGHT;
                func_us_801C1DB0(3);
                break;
            }
        }
        if (dopOffsetX > 0xD0 && (DOPPLEGANGER.facingLeft)) {
            g_Dop.padSim = PAD_LEFT;
            func_us_801C1DB0(3);
            break;
        }
        if (g_Player.timers[9]) {
            switch (rand() & 7) {
            case 0:
            case 6:
            case 7:
                func_us_801C1DB0(6);
                break;
            case 1:
            case 2:
                func_us_801C1DB0(5);
                break;
            case 3:
            case 4:
            case 5:
                func_us_801C1DB0(2);
                break;
            }
        } else {
            if (g_Player.timers[10]) {
                if (rand() & 1) {
                    func_us_801C1DB0(7);
                } else {
                    func_us_801C1DB0(5);
                }
                break;
            }
            if (g_Player.status & PLAYER_STATUS_CROUCH) {
                func_us_801C1DB0(7);
                break;
            } else {
                if (playerDistance < 0x10) {
                    if (DOPPLEGANGER.posX.i.hi >= 0x80) {
                        g_Dop.padSim = PAD_LEFT;
                        func_us_801C1DB0(2);
                    } else {
                        g_Dop.padSim = PAD_RIGHT;
                        func_us_801C1DB0(2);
                    }
                }
                if (playerDistance < 0x40) {
                    if (D_us_801D3300 != 0) {
                        D_us_801D3300--;
                        return;
                    }
                    func_us_801C1DB0(8);
                    break;
                }
                if (D_us_801D32FC != 0) {
                    D_us_801D32FC--;
                    break;
                }
                func_us_801C1DB0(9);
            }
        }
        break;
    case 2:
        if (D_us_801D32F8 == 0) {
            if (DOPPLEGANGER.step == 1 && DOPPLEGANGER.step_s == 3) {
                D_us_801D32F8++;
            } else if (g_Timer & 1) {
                g_Dop.padSim = PAD_TRIANGLE;
            }

        } else if (DOPPLEGANGER.step != 1 || DOPPLEGANGER.step_s != 3) {
            func_us_801C1DB0(9);
        }
        break;
    case 3:
        switch (D_us_801D32F8) {
        case 0:
            if (g_Dop.status & PLAYER_STATUS_BAT_FORM) {
                D_us_801D32F8++;
            } else if (g_Timer & 1) {
                g_Dop.padSim = PAD_R1;
            }
            DOPPLEGANGER.velocityX = 0;
            break;
        case 1:
            if (DOPPLEGANGER.step == 6 && DOPPLEGANGER.step_s == 3) {
                D_us_801D32FC = 0xA;
                D_us_801D32F8++;
            } else {
                g_Dop.padSim = PAD_SQUARE;
            }

            if (DOPPLEGANGER.step != 6) {
                func_us_801C1DB0(0);
            }
            break;
        case 2:
            if (!(g_GameTimer & 1)) {
                g_Dop.padSim = PAD_UP;
            }
            if (D_us_801D32FC != 0) {
                D_us_801D32FC--;
            } else if (g_Timer & 1) {
                g_Dop.padSim |= PAD_R1;
            }

            if (DOPPLEGANGER.step != 6) {
                func_us_801C1DB0(0);
            }
            break;
        }
        break;
    case 4:
        g_Dop.padSim = PAD_DOWN;
        if (D_us_801D32F8 == 0) {
            if (g_Dop.unk46) {
                D_us_801D32F8++;
            } else if (g_Timer & 1) {
                g_Dop.padSim |= PAD_DOWN | PAD_SQUARE;
            }
        } else if (!g_Dop.unk46) {
            func_us_801C1DB0(0);
        }
        break;
    case 5:
        if (DOPPLEGANGER.facingLeft != playerLeft) {
            if (playerLeft) {
                g_Dop.padSim = PAD_LEFT;
            } else {
                g_Dop.padSim = PAD_RIGHT;
            }
        }
        g_Dop.padSim |= PAD_DOWN;
        if (D_us_801D32F8 == 0) {
            if (DOPPLEGANGER.step == 3) {
                D_us_801D32F8++;
                D_us_801D32FC = 6;
            }
        } else {
            if (--D_us_801D32FC == 0) {
                func_us_801C1DB0(10);
            } else if (playerDistance < 0x40) {
                func_us_801C1DB0(4);
            }
        }
        break;
    case 6:
        if (D_us_801D32F8 == 0) {
            if ((u16)DOPPLEGANGER.step == 5) {
                D_us_801D32FC = 0;
                D_us_801D32F8++;
            } else {
                if (g_Timer & 1) {
                    g_Dop.padSim = PAD_CROSS;
                }
            }
        } else {
            if (g_Dop.vram_flag & 1) {
                func_us_801C1DB0(0);
            } else {
                g_Dop.padSim = PAD_CROSS;
                D_us_801D32FC++;
                if (!(D_us_801D32FC % 16)) {
                    g_Dop.padSim |= PAD_UP | PAD_SQUARE | PAD_CROSS;
                }
            }
        }
        break;
    case 7:
        if (D_us_801D32F8 == 0) {
            if ((u16)DOPPLEGANGER.step == 5) {
                D_us_801D32FC = 0;
                D_us_801D32F8++;
                return;
            }

            if (playerLeft) {
                g_Dop.padSim = PAD_LEFT;
            } else {
                g_Dop.padSim = PAD_RIGHT;
            }
            if (g_Timer & 1) {
                g_Dop.padSim |= PAD_CROSS;
            }
            D_us_801D3304 = g_Dop.padSim & (PAD_LEFT | PAD_RIGHT);
        } else if (g_Dop.vram_flag & 1) {
            func_us_801C1DB0(0);
        } else {
            g_Dop.padSim = D_us_801D3304 + PAD_CROSS;
            if (DOPPLEGANGER.velocityY > 0) {
                if (DOPPLEGANGER.velocityY > FIX(2)) {
                    g_Dop.padSim |= PAD_DOWN | PAD_SQUARE;
                }

                if (abs(DOPPLEGANGER.posY.i.hi - PLAYER.posY.i.hi) < 0x10) {
                    g_Dop.padSim |= PAD_DOWN | PAD_SQUARE;
                }
            }
        }
        break;
    case 8:
        if (D_us_801D32F8 == 0) {
            if (g_Dop.unk46) {
                D_us_801D32F8++;
            } else {
                if (g_Timer & 1) {
                    g_Dop.padSim |= PAD_SQUARE;
                }
            }
        } else if (!g_Dop.unk46) {
            if (playerLeft) {
                g_Dop.padSim |= PAD_LEFT;
            } else {
                g_Dop.padSim |= PAD_RIGHT;
            }
            func_us_801C1DB0(0);
            if (DOPPLEGANGER.facingLeft) {
                if (DOPPLEGANGER.posX.i.hi < 0xA0) {
                    func_us_801C1DB0(2);
                }
                if (DOPPLEGANGER.facingLeft) {
                    break;
                }
            }
            if (DOPPLEGANGER.posX.i.hi > 0x60) {
                func_us_801C1DB0(2);
            }
        }
        break;
    case 9:
        switch (D_us_801D32F8) {
        case 0:
            D_us_801D32F8++;
            D_us_801D32FC = 0x18;
            g_Dop.padSim = PAD_UP | PAD_SQUARE;
            break;
        case 1:
            if (--D_us_801D32FC == 0) {
                D_us_801D32F8++;
                g_Dop.padSim = PAD_UP | PAD_SQUARE;
                D_us_801D32FC = 0x10;
                if (playerLeft) {
                    g_Dop.padSim |= PAD_LEFT;
                } else {
                    g_Dop.padSim |= PAD_RIGHT;
                }
            }
            break;
        case 2:
            if (--D_us_801D32FC == 0) {
                if (playerLeft) {
                    g_Dop.padSim |= PAD_LEFT;
                } else {
                    g_Dop.padSim |= PAD_RIGHT;
                }
                D_us_801D32F8++;
            }
            // fallthrough
        case 4:
        default:
            if (DOPPLEGANGER.facingLeft && DOPPLEGANGER.posX.i.hi < 0xA0) {
                func_us_801C1DB0(2);
            } else if (
                !DOPPLEGANGER.facingLeft && DOPPLEGANGER.posX.i.hi > 0x60) {
                func_us_801C1DB0(2);
            } else {
                func_us_801C1DB0(0);
            }
            break;
        }
        break;
    case 10:
        if (D_us_801D32F8 == 0) {
            g_Dop.padSim = PAD_DOWN;
            if (DOPPLEGANGER.step == 9) {
                D_us_801D32F8++;
            }
            if (g_Timer & 1) {
                g_Dop.padSim |= PAD_DOWN | PAD_TRIANGLE;
            }
        } else if (DOPPLEGANGER.step != 9) {
            D_us_801D32F4 = 6;
            D_us_801D32F8 = 1; // PLAYER_STATUS_BAT_FORM?
        }
        break;
    case 14:
        if (D_us_801D32F8 == 0) {
            if (g_Timer & 1) {
                g_Dop.padSim = PAD_R2;
            }
            if (g_Dop.status & PLAYER_STATUS_MIST_FORM) {
                g_Dop.padSim = PAD_NONE;
                D_us_801D32F8++;
                D_us_801D32FC = 0xA0;
            }
        } else if (D_us_801D32FC != 0) {
            D_us_801D32FC--;
            if (!(g_GameTimer & 0x1F)) {
                g_Dop.padSim = PAD_UP;
            }
        } else {
            if (g_Timer & 1) {
                g_Dop.padSim = PAD_R2;
            }
            if (!(g_Dop.status & PLAYER_STATUS_MIST_FORM)) {
                g_Dop.padSim = PAD_NONE;
                func_us_801C1DB0(0);
            }
        }
        break;
    case 15:
        if (!(g_Dop.status & PLAYER_STATUS_STONE)) {
            func_us_801C1DB0(0);
        }
        if (!(g_GameTimer & 0x3F)) {
            g_Dop.padSim = PAD_UP;
        }
        break;
    case 16:
        if (!(g_Player.status & PLAYER_STATUS_DEAD)) {
            func_us_801C1DB0(0);
        }
        g_Dop.padSim = PAD_UP;
        if ((g_Dop.status & PLAYER_STATUS_BAT_FORM) && (g_Timer & 1)) {
            g_Dop.padSim = PAD_R1;
        }
        if ((g_Dop.status & PLAYER_STATUS_MIST_FORM) && (g_Timer & 1)) {
            g_Dop.padSim = PAD_R1;
        }
        break;
    case 17:
        if (abs(DOPPLEGANGER.posY.i.hi - PLAYER.posY.i.hi) < 8) {
            D_us_801D32F4 = 0;
            return;
        }
        break;
    case 18:
        func_us_801C4A30(1, 4);
        g_Player.padSim = PAD_LEFT;
        g_Player.demo_timer = 4;
        g_Dop.padSim = PAD_RIGHT;
        g_Dop.demo_timer = 4;
        if (PLAYER.posX.i.hi < 0xB8) {
            g_Player.padSim = PAD_NONE;
            flags |= 1;
        }
        if (DOPPLEGANGER.posX.i.hi >= 0x49) {
            g_Dop.padSim = PAD_NONE;
            flags |= 2;
        }
        if (flags == 3) {
            D_us_801805B0 = 0xE;
            func_us_801C1DB0(0x13);
            break;
        }
        break;
    case 19:
    case 21:
        func_us_801C4A30(1, 4);
        if (D_us_801D32F8 == 0) {
            D_us_801D32FC = 0x40;
            D_us_801D32F8++;
        } else {
            if (--D_us_801D32FC == 0) {
                func_us_801C1DB0(0);
            }
        }
        break;
    case 20:
        func_us_801C4A30(1, 4);
        g_Player.padSim = PAD_RIGHT;
        g_Player.demo_timer = 4;
        g_Dop.padSim = PAD_LEFT;
        g_Dop.demo_timer = 4;
        if (PLAYER.posX.i.hi >= 0x49) {
            g_Player.padSim = PAD_NONE;
            flags |= 1;
        }
        if (DOPPLEGANGER.posX.i.hi < 0xB8) {
            g_Dop.padSim = PAD_NONE;
            flags |= 2;
        }
        if (flags == 3) {
            D_us_801805B0 = 7;
            func_us_801C1DB0(0x15);
        }
        break;
    }
}

extern EInit EInitUnk16;

void EntityUnkId16(Entity* self) {
    Entity* entity;
    s32 i;

    g_Dop.unk6A = DOPPLEGANGER.hitPoints;
    if (self->step == 0) {
        InitializeEntity(EInitUnk16);
        if (PLAYER.posX.i.hi > 0x80) {
            DOPPLEGANGER.posX.i.hi = 0x10;
        } else {
            DOPPLEGANGER.posX.i.hi = 0xF0;
        }
        func_us_801C096C();
        entity = &g_Entities[68];
        for (i = 68; i < 144; i++, entity++) {
            DestroyEntity(entity);
        }
        g_Dop.unk6C = DOPPLEGANGER.hitPoints;
        g_Dop.unk6A = DOPPLEGANGER.hitPoints;
        g_Dop.unk6E = DOPPLEGANGER.hitPoints;
        g_Dop.unk70 = DOPPLEGANGER.hitboxState;
        if (PLAYER.posX.i.hi > 0x80) {
            func_us_801C1DB0(0x12);
        } else {
            func_us_801C1DB0(0x14);
        }
        func_us_801C4954(1, 0x30);
    } else {
        func_us_801C1DC8();
        EntityDoppleganger40();
        func_us_801C9624();
    }
    g_Dop.unk6C = g_Dop.unk6A;
}

#include "../dop_collision.h"
