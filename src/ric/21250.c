// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"
#include "sfx.h"

s32 func_8015D250(s32 unused_arg) {
    SubweaponDef subweapon;
    s16 subweaponId;

    if (!(g_Player.padPressed & PAD_UP)) {
        return 1;
    }

    subweaponId = func_8015FB84(&subweapon, false, false);
    if (subweaponId <= 0) {
        return 1;
    }
    if (subweapon.blueprintNum == 0) {
        return 4;
    }
    if (func_8015D1D0(subweaponId, subweapon.unk6) < 0) {
        return 2;
    }
    subweaponId = func_8015FB84(&subweapon, false, true);
    if (subweaponId <= 0) {
        return 3;
    }
    if (g_Player.unk72) {
        return 5;
    }

    RicCreateEntFactoryFromEntity(g_CurrentEntity, subweapon.blueprintNum, 0);
    g_Player.timers[PL_T_10] = 4;

    switch (PLAYER.step) {
    case PL_S_RUN:
        PLAYER.step = PL_S_STAND;
        RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
        RicSetAnimation(D_801555E8);
        break;
    case PL_S_STAND:
    case PL_S_WALK:
    case PL_S_CROUCH:
        PLAYER.step = PL_S_STAND;
        RicSetAnimation(D_801555E8);
        break;
    case PL_S_FALL:
    case PL_S_JUMP:
        PLAYER.step = PL_S_JUMP;
        RicSetAnimation(D_80155638);
        break;
    }
    g_Player.unk46 = 3;
    PLAYER.step_s = 0x42;
    g_Player.timers[PL_T_10] = 4;
    return 0;
}

bool RicDoAttack(void) {
    s32 i;
    s16 poisoned;
    s32 temp_rand = rand();
    s16 sfxGrunt = temp_rand % 6;

    if (func_8015D250(temp_rand / 6) == 0) {
        if (sfxGrunt == 0) {
            g_api.PlaySfx(SFX_GRUNT_A);
        }
        if (sfxGrunt == 1) {
            g_api.PlaySfx(SFX_GRUNT_B);
        }
        if (sfxGrunt == 2) {
            g_api.PlaySfx(SFX_GRUNT_C);
        }
        return true;
    }
    poisoned = g_Player.timers[PL_T_POISON] != 0;
    for (i = 16; i < 31; i++) {
        DestroyEntity(&g_Entities[i]);
    }
    if (RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_WHIP, poisoned), 0)) {
        if (poisoned) {
            g_api.PlaySfx(0x6B5);
        } else {
            g_api.PlaySfx(0x706);
        }
        if (sfxGrunt == 0) {
            g_api.PlaySfx(SFX_GRUNT_A);
        }
        if (sfxGrunt == 1) {
            g_api.PlaySfx(SFX_GRUNT_B);
        }
        if (sfxGrunt == 2) {
            g_api.PlaySfx(SFX_GRUNT_C);
        }
        switch (PLAYER.step) {
        default:
            return false;
        case Player_Stand:
        case Player_Walk:
            PLAYER.step = PL_S_STAND;
            RicSetAnimation(D_80155588);
            g_CurrentEntity->velocityX = 0;
            break;
        case PL_S_RUN:
            PLAYER.step = PL_S_STAND;
            RicSetAnimation(D_80155588);
            RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
            break;
        case Player_Crouch:
            RicSetAnimation(D_801555A8);
            g_CurrentEntity->velocityX = 0;
            break;
        case Player_Fall:
        case Player_Jump:
            PLAYER.step = PL_S_JUMP;
            RicSetAnimation(D_801555C8);
            break;
        }
        g_Player.unk46 = 1;
        PLAYER.step_s = 0x40;
        g_Player.timers[PL_T_9] = 4;
        return true;
    }
    return false;
}

bool RicDoCrash(void) {
    SubweaponDef subWpn;
    Entity* subWpnEnt;
    s16 subWpnID;

    subWpnID = func_8015FB84(&subWpn, true, false);
    if (subWpnID < 0) {
        return 0;
    }
    if (subWpnID == PL_W_HOLYWATER && g_Player.timers[PL_T_3]) {
        return 0;
    }
    if (subWpnID == PL_W_STOPWATCH && g_unkGraphicsStruct.D_800973FC) {
        return 0;
    }
    if (subWpn.blueprintNum) {
        if (subWpnID == 1) {
            subWpnEnt = RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(subWpn.blueprintNum, 1), 0);
        } else {
            subWpnEnt = RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(subWpn.blueprintNum, 0), 0);
        }
    }
    if (subWpnEnt == NULL) {
        return 0;
    }
    subWpnID = func_8015FB84(&subWpn, true, true);
    g_Player.unk46 = 4;
    g_Player.unk4E = 0;
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    switch (subWpnID) {
    case SUBWPN_NONE:
        RicSetStep(PL_S_FLAME_WHIP);
        RicSetAnimation(ric_anim_flame_whip);
        RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_36, 1), 0);
        g_api.PlaySfx(SFX_GRUNT_SUBWPN_A);
        break;
    case SUBWPN_DAGGER:
        RicSetStep(PL_S_THROW_DAGGERS);
        RicSetAnimation(ric_anim_throw_daggers);
        g_api.PlaySfx(SFX_GRUNT_SUBWPN_A);
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 2), 0);
        break;
    case SUBWPN_AXE:
        RicSetStep(PL_S_STAND_IN_AIR);
        RicSetAnimation(ric_ric_anim_stand_in_air);
        PLAYER.velocityY = FIX(-4.6875);
        if (g_Player.unk72) {
            PLAYER.velocityY = 0;
        }
        func_8015CC28();
        g_api.PlaySfx(SFX_GRUNT_SUBWPN_A);
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 2), 0);
        break;
    case SUBWPN_HOLYWATER:
        RicSetStep(PL_S_HYDROSTORM);
        RicSetAnimation(ric_anim_point_finger_up);
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x40), 0);
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x47), 0);
        g_api.PlaySfx(SFX_HYDROSTORM);
        break;
    case SUBWPN_REBNDSTONE:
    case SUBWPN_VIBHUTI:
    case SUBWPN_AGUNEA:
        RicSetStep(PL_S_SUBWPN_CRASH);
        RicSetAnimation(ric_anim_point_finger_up);
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x40), 0);
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x47), 0);
        g_api.PlaySfx(SFX_GRUNT_SUBWPN_A);
        break;
    case SUBWPN_BIBLE:
    case SUBWPN_STOPWATCH:
        RicSetStep(PL_S_SUBWPN_CRASH);
        RicSetAnimation(D_801558E4);
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x40), 0);
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x47), 0);
        g_api.PlaySfx(SFX_GRUNT_SUBWPN_A);
        break;
    case SUBWPN_CROSS:
        RicSetStep(PL_S_STAND_IN_AIR);
        RicSetAnimation(ric_ric_anim_stand_in_air);
        PLAYER.velocityY = FIX(-4.6875);
        if (g_Player.unk72) {
            PLAYER.velocityY = 0;
        }
        func_8015CC28();
        g_api.PlaySfx(SFX_CROSS_CRASH);
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 2), 0);
        break;
    }
    g_Player.timers[PL_T_12] = 4;
    return 1;
}

void RicSetDeadPrologue() { RicSetStep(PL_S_DEAD_PROLOGUE); }

void RicSetSlide(void) {
    RicCheckFacing();
    RicSetStep(PL_S_SLIDE);
    RicSetAnimation(D_80155750);
    g_CurrentEntity->velocityY = 0;
    RicSetSpeedX(FIX(5.5));
    func_8015CC28();
    RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_25, 0);
    g_api.PlaySfx(0x707);
    g_Player.timers[PL_T_12] = 4;
}

void RicSetSlideKick(void) {
    g_Player.unk44 = 0;
    RicSetStep(PL_S_SLIDE_KICK);
    RicSetAnimation(D_8015577C);
    g_CurrentEntity->velocityY = FIX(-2);
    RicSetSpeedX(FIX(5.5));
    func_8015CC28();
    RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_25, 0);
    g_api.PlaySfx(SFX_GRUNT_B);
    g_Player.timers[PL_T_12] = 4;
    RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_31, 0);
}

void RicSetBladeDash(void) {
    RicSetStep(PL_S_BLADEDASH);
    RicSetAnimation(ric_anim_blade_dash);
    g_CurrentEntity->velocityY = 0;
    RicSetSpeedX(FIX(5.5));
    g_Player.unk46 = 5;
    g_Player.timers[PL_T_12] = 4;
    RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_BLADE_DASH, 0);
    func_8015CC28();
    g_api.PlaySfx(SFX_GRUNT_C);
    g_api.PlaySfx(0x707);
}

bool RicCheckInput(s32 checks) {
    s32 velYChange;
    u32 effects;

    if (checks & CHECK_FACING) {
        if (g_Player.unk46 == 0) {
            RicCheckFacing();
        }
    }
    velYChange = (checks & CHECK_GRAVITY_FALL) ? FIX(28.0 / 128) : 0;
    if (checks & CHECK_GRAVITY_JUMP) {
        if (FIX(-1.0 / 8) < PLAYER.velocityY &&
            PLAYER.velocityY < FIX(3.0 / 8) && !(g_Player.unk44 & 0x20) &&
            (g_Player.padPressed & PAD_CROSS)) {
            // Note that 5.6 is precisely 1/5 of 28.
            velYChange = FIX(5.6 / 128);
        } else {
            velYChange = FIX(28.0 / 128);
        }
    }
    if (checks & CHECK_GRAVITY_HIT) {
        if (FIX(-1.0 / 8) < PLAYER.velocityY &&
            PLAYER.velocityY < FIX(3.0 / 8)) {
            velYChange = FIX(14.0 / 128);
        } else {
            velYChange = FIX(28.0 / 128);
        }
    }
    if (*D_80097448 >= 0x29) {
        velYChange /= 4;
    }
    PLAYER.velocityY += velYChange;
    if (PLAYER.velocityY > FIX(7)) {
        PLAYER.velocityY = FIX(7);
    }
    if ((checks & CHECK_80) && (g_Player.pl_vram_flag & 2) &&
        (PLAYER.velocityY < FIX(-1))) {
        PLAYER.velocityY = FIX(-1);
    }
    if (PLAYER.velocityY >= 0) {
        if ((checks & CHECK_GROUND) && (g_Player.pl_vram_flag & 1)) {
            switch (g_Player.unk46) {
            case 0:
            default:
                if (g_Player.unk44 & 8) {
                    RicSetCrouch(3, PLAYER.velocityX);
                    g_api.PlaySfx(SFX_STOMP_SOFT_A);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                    return true;
                }
                if (PLAYER.velocityY > FIX(6.875)) {
                    RicSetCrouch(1, 0);
                    g_api.PlaySfx(SFX_STOMP_SOFT_A);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                } else if (g_Player.padPressed & (PAD_LEFT | PAD_RIGHT)) {
                    if ((g_Player.unk44 & 0x10) && (g_Player.unk7A == 0)) {
                        RicSetRun();
                    } else {
                        RicSetWalk(0);
                    }
                } else {
                    RicSetStand(0);
                }
                return true;
            case 1:
                if (PLAYER.velocityY > FIX(6.875)) {
                    PLAYER.step = PL_S_CROUCH;
                    PLAYER.anim = D_801555A8;
                    g_api.PlaySfx(SFX_STOMP_HARD_B);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                } else {
                    PLAYER.step = PL_S_STAND;
                    PLAYER.anim = D_80155588;
                    if (g_Player.unk44 & 8) {
                        RicCreateEntFactoryFromEntity(
                            g_CurrentEntity, BP_SKID_SMOKE, 0);
                        g_api.PlaySfx(SFX_STOMP_HARD_B);
                    } else {
                        PLAYER.velocityX = 0;
                    }
                }
                PLAYER.velocityY = 0;
                g_Player.unk44 = 0;
                return true;
            case 2:
                if (PLAYER.velocityY > FIX(6.875)) {
                    PLAYER.step = PL_S_CROUCH;
                    PLAYER.anim = D_80155738;
                    g_api.PlaySfx(SFX_STOMP_SOFT_A);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                } else {
                    PLAYER.step = PL_S_STAND;
                    PLAYER.anim = ric_anim_brandish_whip;
                    if (!(g_Player.unk44 & 8)) {
                        PLAYER.velocityX = 0;
                    } else {
                        RicCreateEntFactoryFromEntity(
                            g_CurrentEntity, BP_SKID_SMOKE, 0);
                        g_api.PlaySfx(SFX_STOMP_SOFT_A);
                    }
                }
                PLAYER.velocityY = 0;
                g_Player.unk44 = 0;
                return true;
            case 3:
                if ((PLAYER.velocityY > FIX(6.875)) || (g_Player.unk44 & 8)) {
                    g_api.PlaySfx(SFX_STOMP_SOFT_A);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                }
                PLAYER.velocityY = 0;
                if (!(g_Player.unk44 & 8)) {
                    PLAYER.velocityX = 0;
                }
                PLAYER.step = PL_S_STAND;
                PLAYER.anim = D_801555E8;
                g_Player.unk44 = 0;
                return true;
            }
        } else if (
            checks & CHECK_GROUND_AFTER_HIT && (g_Player.pl_vram_flag & 1)) {
            RicSetCrouch(1, PLAYER.velocityX);
            g_api.PlaySfx(SFX_STOMP_SOFT_A);
            if (g_Player.unk5C && (g_Status.hp < 2)) {
                RicSetDeadPrologue();
                return true;
            } else {
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, BP_SKID_SMOKE, 0);
            }
            return true;
        }
    }
    if (checks & CHECK_FALL && !(g_Player.pl_vram_flag & 1)) {
        if (g_Player.unk46 != 0) {
            if (g_Player.unk46 == 1) {
                PLAYER.step_s = 0x40;
                PLAYER.step = PL_S_JUMP;
                PLAYER.anim = D_801555C8;
                return true;
            }
            if (g_Player.unk46 == 2) {
                PLAYER.step_s = 0x41;
                PLAYER.step = PL_S_JUMP;
                PLAYER.anim = D_801555C8;
                return true;
            }
            if (g_Player.unk46 == 3) {
                PLAYER.step_s = 0x42;
                PLAYER.step = PL_S_JUMP;
                PLAYER.anim = D_80155638;
                return true;
            }
        } else {
            RicSetFall();
            return true;
        }
    }
    if (g_Player.unk46 != 0) {
        return false;
    }
    if (checks & CHECK_CRASH && (g_Player.padTapped & PAD_TRIANGLE) &&
        RicDoCrash()) {
        return true;
    }
    if (checks & CHECK_SLIDE) {
        if (!PLAYER.facingLeft) {
            effects = g_Player.colliders[2].effects & EFFECT_UNK_8000;
        } else {
            effects = g_Player.colliders[3].effects & EFFECT_UNK_8000;
        }
        if (!effects) {
            if (((PLAYER.posX.i.hi <= (u8)-5) || PLAYER.facingLeft) &&
                ((PLAYER.posX.i.hi >= 5) || !PLAYER.facingLeft) &&
                (g_Player.padPressed & PAD_DOWN) &&
                (g_Player.padTapped & PAD_CROSS)) {
                RicSetSlide();
                return true;
            }
        }
    }
    if (checks & CHECK_JUMP && (g_Player.padTapped & PAD_CROSS)) {
        RicSetJump();
        return true;
    }
    if (checks & CHECK_ATTACK && (g_Player.padTapped & PAD_SQUARE) &&
        RicDoAttack()) {
        return true;
    }
    if (checks & CHECK_CROUCH && (g_Player.padPressed & PAD_DOWN)) {
        RicSetCrouch(2, 0);
        return true;
    }
    return false;
}

static s32 debug_wait_info_timer;
static void DebugShowWaitInfo(const char* msg) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    if (debug_wait_info_timer++ & 4) {
        FntPrint("\no\n");
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
    FntFlush(-1);
}

static void DebugInputWait(const char* msg) {
    while (PadRead(0))
        DebugShowWaitInfo(msg);
    while (PadRead(0) == 0)
        DebugShowWaitInfo(msg);
}

void func_8015E484(void) {
    s32 i;
    s32 collision = 0;
    s16 startingPosY = PLAYER.posY.i.hi;

    if (g_Player.pl_vram_flag & 1 || g_IsRicDebugEnter || g_Player.unk78 == 1) {
        return;
    }
    if (PLAYER.posY.i.hi < 0x30) {
        PLAYER.posY.i.hi -= 0x10;
        while (true) {
            for (i = 0; i < 4; ++i) {
                g_api.CheckCollision((s16)(PLAYER.posX.i.hi + D_801545F4[i].x),
                                     (s16)(PLAYER.posY.i.hi + D_801545F4[i].y),
                                     &g_Player.colliders[i], 0);
            }

            if ((g_Player.colliders[1].effects & 0x81) == 1 ||
                (g_Player.colliders[2].effects & 0x81) == 1 ||
                (g_Player.colliders[3].effects & 0x81) == 1) {
                PLAYER.velocityY = 0;
                PLAYER.posY.i.hi -= 1;
                collision = 1;
            } else if (collision == 0) {
                PLAYER.posY.i.hi += 8;
                if (PLAYER.posY.i.hi >= 0x30) {
                    PLAYER.posY.i.hi = startingPosY;
                    return;
                }
            } else {
                return;
            }
        }

    } else if (PLAYER.posY.i.hi >= 0xB1) {
        PLAYER.posY.i.hi += 0x20;
        while (true) {
            for (i = 0; i < 4; ++i) {
                g_api.CheckCollision((s16)(PLAYER.posX.i.hi + D_801545E4[i].x),
                                     (s16)(PLAYER.posY.i.hi + D_801545E4[i].y),
                                     &g_Player.colliders2[i], 0);
            }

            if ((g_Player.colliders2[1].effects & 0x41) == 1 ||
                (g_Player.colliders2[2].effects & 0x41) == 1 ||
                (g_Player.colliders2[3].effects & 0x41) == 1) {
                PLAYER.velocityY = 0;
                PLAYER.posY.i.hi += 1;
                collision = 1;
            } else if (collision != 0) {
                PLAYER.posY.i.hi -= 1;
                return;
            } else {
                PLAYER.posY.i.hi -= 8;
                if (PLAYER.posY.i.hi < 0xB1) {
                    PLAYER.posY.i.hi = startingPosY;
                    return;
                }
            }
        }
    }
}

void func_8015E7B4(Unkstruct_8010BF64* arg0) { // !FAKE:
    s32 temp = D_80154604[0].x;

    arg0->unk14 = temp;
    arg0->unk1C = temp = D_80154604[0].y;
    arg0->unk18 = D_801545F4[1].y - 1;
    arg0->unk20 = D_801545E4[1].y + 1;
}

void func_8015E800(void) {
    Collider sp10;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_s0;
    s32 temp_s7;
    s32 i;
    s32 var_s5;
    s32 var_v1;
    u16 var_a1;
    s16 argX;
    s16 argY;
    s32 sp10effects;
    s16 temp_s16;

    u16* yPosPtr = &PLAYER.posY.i.hi;
    u16* xPosPtr = &PLAYER.posX.i.hi;
    s32* vram_ptr = &g_Player.pl_vram_flag;

    var_s5 = 0;
    i = 0;
    if (g_unkGraphicsStruct.unk18) {
        *vram_ptr = 1;
        return;
    }
    if ((PLAYER.velocityY == 0) && (g_Player.unk04 & 1)) {
        var_s5 = 4;
    } else {
        i = 1;
    }
    for (; i < 4; i++, var_s5 = 0) {
        temp_a0 = g_Player.colliders[i].effects;
        if (temp_a0 & EFFECT_SOLID_FROM_BELOW) {
            continue;
        }
        if ((temp_a0 & EFFECT_UNK_0002) || (PLAYER.velocityY >= 0) ||
            (PLAYER.step == PL_S_SLIDE_KICK && (temp_a0 & EFFECT_UNK_8000))) {
            temp_s0 = g_Player.colliders[i].effects &
                      (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SOLID);
            if ((temp_s0 == EFFECT_SOLID) ||
                (g_Player.colliders[i].effects & EFFECT_UNK_0800)) {
                argX = *xPosPtr + D_801545F4[i].x;
                argY = *yPosPtr + D_801545F4[i].y +
                       (g_Player.colliders[i].unk18 - 1);
                g_api.CheckCollision(argX, argY, &sp10, 0);
                sp10effects = sp10.effects;
                if (!(sp10effects & EFFECT_SOLID)) {
                    if (g_Player.colliders[i].effects != EFFECT_SOLID ||
                        PLAYER.velocityY >= 0 ||
                        PLAYER.step == PL_S_SLIDE_KICK) {
                        if (temp_s0 & EFFECT_UNK_0800) {
                            *yPosPtr += var_s5 + g_Player.colliders[i].unk8;
                        } else {
                            *yPosPtr += var_s5 + g_Player.colliders[i].unk18;
                        }
                        *vram_ptr |= 1;
                        return;
                    }
                    continue;
                } else {
                    temp_a1 = sp10effects & (EFFECT_UNK_8000 | EFFECT_UNK_0002 |
                                             EFFECT_SOLID);
                    if ((temp_a1) == (EFFECT_UNK_8000 | EFFECT_SOLID)) {
                        if (i < 2) {
                            *vram_ptr |= ((sp10effects &
                                           (EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                                            EFFECT_UNK_1000)) +
                                          temp_a1);
                            *yPosPtr += g_Player.colliders[i].unk8 +
                                        sp10.unk18 + (var_s5 - 1);
                            return;
                        }
                        if ((i == 2) &&
                            ((sp10effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                                             EFFECT_SOLID)) ==
                             (EFFECT_UNK_8000 | EFFECT_SOLID))) {
                            g_Player.colliders[2].effects = sp10effects;
                            g_Player.colliders[2].unk10 =
                                g_Player.colliders[2].unk8;
                        }
                        if ((i == 3) &&
                            ((sp10effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                                             EFFECT_SOLID)) ==
                             (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                              EFFECT_SOLID))) {
                            g_Player.colliders[3].effects = sp10effects;
                            g_Player.colliders[3].unk10 =
                                g_Player.colliders[3].unk8;
                        }
                    }
                }
            }
            if ((temp_s0 != (EFFECT_UNK_8000 | EFFECT_SOLID)) || (i >= 2)) {
                continue;
            }
            *vram_ptr |= g_Player.colliders[i].effects &
                         (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                          EFFECT_UNK_1000 | EFFECT_SOLID);
            *yPosPtr += var_s5 + g_Player.colliders[i].unk18;
            return;
        }
    }
    if (g_Player.colliders[1].effects & 4) {
        *vram_ptr |= 0x11;
        if ((g_Timer & 3) == 0) {
            (*yPosPtr)++;
        }
        return;
    }
    if (g_Player.colliders[1].effects & 8) {
        *vram_ptr |= 0x80;
    }
    if (PLAYER.velocityY < 0) {
        return;
    }
    argX = *xPosPtr + D_801545F4[0].x;
    argY = *yPosPtr + D_801545F4[0].y + 10;
    g_api.CheckCollision(argX, argY, &sp10, 0);
    if ((sp10.effects & (EFFECT_UNK_8000 | EFFECT_SOLID)) != 0) {
        return;
    }

    for (i = 2; i < 4; i++) {
        if ((g_Player.colliders[3].effects & EFFECT_UNK_8000) &&
            (g_Player.colliders[2].effects & EFFECT_UNK_8000)) {
            return;
        }
        temp_s0 = g_Player.colliders[i].effects;
        temp_s7 = ((g_Player.colliders[i].effects &
                    (EFFECT_UNK_4000 | EFFECT_UNK_2000 | EFFECT_UNK_1000)) |
                   (EFFECT_UNK_8000 | EFFECT_SOLID));
        if (!(temp_s0 & EFFECT_UNK_8000)) {
            continue;
        }
        if (i == 2) {
            temp_a0 = EFFECT_UNK_4000;
            var_a1 = g_Player.colliders[2].unk4;
            temp_s16 = g_Player.colliders[2].unk4;
            var_v1 = temp_s16 + 8;
        } else {
            temp_a0 = 0;
            var_a1 = g_Player.colliders[3].unkC;
            temp_s16 = g_Player.colliders[3].unkC;
            var_v1 = 8 - temp_s16;
        }
        if ((temp_s0 & EFFECT_UNK_4000) == temp_a0) {
            argX = var_a1 + (*xPosPtr + D_801545F4[i].x);
            argY = *yPosPtr + D_801545F4[i].y;
            g_api.CheckCollision(argX, argY, &sp10, 0);
            if (sp10.effects & 1) {
                *yPosPtr += sp10.unk18;
                *vram_ptr |= temp_s7;
                return;
            }
            continue;
        }
        if (var_v1 <= 0) {
            continue;
        }
        if (!(temp_s0 & 1)) {
            continue;
        }
        argX = var_a1 + (*xPosPtr + D_801545F4[i].x);
        argY = *yPosPtr + D_801545F4[i].y + g_Player.colliders[i].unk10;
        g_api.CheckCollision(argX, argY, &sp10, 0);
        if (sp10.effects & 1) {
            *yPosPtr += (sp10.unk18 + g_Player.colliders[i].unk10);
            *vram_ptr |= temp_s7;
            return;
        }
    }
}

void func_8015EE28(void) {
    Collider collider;
    s32 temp_fp;
    u32 temp_s0;
    s32 temp_v1;
    s32 var_a0;
    s32 i;
    u16 var_a1;
    s16 temp_s16;

    s16 newY;

    s16 argX;
    s16 argY;

    u32 collidereffects;

    u16* yPosPtr = &PLAYER.posY.i.hi;
    u16* xPosPtr = &PLAYER.posX.i.hi;
    s32* vram_ptr = &g_Player.pl_vram_flag;
    // weird thing where i has to get initialized first
    i = 1;

    if (g_unkGraphicsStruct.unk18) {
        return;
    }
    for (i = 1; i < 4; i++) {
        var_a0 = g_Player.colliders2[i].effects;
        temp_s0 = var_a0 & (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SOLID);
        if (var_a0 & EFFECT_SOLID_FROM_ABOVE) {
            continue;
        }
        if ((temp_s0 == EFFECT_SOLID) || (var_a0 & EFFECT_UNK_8000)) {
            if ((PLAYER.step == PL_S_SLIDE_KICK || PLAYER.step == PL_S_SLIDE) &&
                !(var_a0 & EFFECT_SOLID)) {
                continue;
            }
            argX = *xPosPtr + D_801545E4[i].x;
            argY =
                *yPosPtr + D_801545E4[i].y + g_Player.colliders2[i].unk10 + 1;
            g_api.CheckCollision(argX, argY, &collider, 0);
            collidereffects = collider.effects;
            if (!(collidereffects & 1)) {
                if ((g_Player.colliders2[i].effects != EFFECT_SOLID) ||
                    (PLAYER.velocityY <= 0)) {
                    *vram_ptr |= 2;
                    if (!(*vram_ptr & 1) &&
                        ((g_Player.unk04 &
                          (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID)) !=
                         (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID))) {
                        if (g_Player.colliders2[i].effects & EFFECT_UNK_8000) {
                            *yPosPtr += g_Player.colliders2[i].unk10;
                        } else {
                            *yPosPtr += g_Player.colliders2[i].unk20;
                        }
                    }
                    return;
                }
                continue;
            }
            if ((collider.effects &
                 (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ==
                (EFFECT_UNK_0800 | EFFECT_SOLID)) {
                if (i < 2) {
                    *vram_ptr |= (EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                                  ((collidereffects >> 4) &
                                   (EFFECT_UNK_0400 | EFFECT_UNK_0200 |
                                    EFFECT_UNK_0100)));
                    if (!(*vram_ptr & 1)) {
                        newY = *yPosPtr + 1 +
                               (g_Player.colliders2[i].unk10 + collider.unk20);
                        *yPosPtr = newY;
                    }
                    return;
                }
                if ((i == 2) &&
                    ((collidereffects &
                      (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ==
                     (EFFECT_UNK_0800 | EFFECT_SOLID))) {
                    g_Player.colliders[2].effects = collidereffects;
                    g_Player.colliders[2].unk8 = g_Player.colliders[2].unk10;
                }
                if ((i == 3) &&
                    ((collidereffects &
                      (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ==
                     (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID))) {
                    g_Player.colliders[3].effects = collidereffects;
                    g_Player.colliders[3].unk8 = g_Player.colliders[3].unk10;
                }
            }
            if ((collidereffects & EFFECT_UNK_0800) == 0) {
                *vram_ptr |=
                    (EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                     ((collidereffects >> 4) &
                      (EFFECT_UNK_0400 | EFFECT_UNK_0200 | EFFECT_UNK_0100)));
                if (!(*vram_ptr & 1)) {
                    newY = *yPosPtr + 1 +
                           (g_Player.colliders2[i].unk10 + collider.unk20);
                    *yPosPtr = newY;
                }
                return;
            }
        }
        if ((temp_s0 == (EFFECT_UNK_0800 | EFFECT_SOLID)) && (i < 2)) {
            *vram_ptr |=
                (EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                 ((g_Player.colliders2[i].effects >> 4) &
                  (EFFECT_UNK_0400 | EFFECT_UNK_0200 | EFFECT_UNK_0100)));
            if (!(*vram_ptr & 1)) {
                *yPosPtr += g_Player.colliders2[i].unk20;
            }
            return;
        }
    }

    if (PLAYER.velocityY > 0) {
        return;
    }
    argX = *xPosPtr + D_801545E4[0].x;
    argY = (*yPosPtr + D_801545E4[0].y) - 10;
    g_api.CheckCollision(argX, argY, &collider, 0);
    if ((collider.effects & 1) != 0) {
        return;
    }
    for (i = 2; i < 4; i++) {
        if ((g_Player.colliders[7].effects & EFFECT_UNK_0800) &&
            (g_Player.colliders[6].effects & EFFECT_UNK_0800)) {
            return;
        }
        temp_s0 = g_Player.colliders2[i].effects;
        temp_fp = ((temp_s0 >> 4) &
                   (EFFECT_UNK_0400 | EFFECT_UNK_0200 | EFFECT_UNK_0100)) +
                  (EFFECT_UNK_0800 | EFFECT_UNK_0002);
        if (temp_s0 & EFFECT_UNK_0800) {
            if (i == 2) {
                var_a0 = EFFECT_UNK_4000;
                var_a1 = g_Player.colliders[6].unk4;
                temp_s16 = g_Player.colliders[6].unk4;
                temp_v1 = temp_s16 + 8;
            } else {
                var_a0 = 0;
                var_a1 = g_Player.colliders[7].unkC;
                temp_s16 = g_Player.colliders[7].unkC;
                temp_v1 = 8 - temp_s16;
            }
            if ((temp_s0 & EFFECT_UNK_4000) == var_a0) {
                argX = var_a1 + (*xPosPtr + D_801545E4[i].x);
                argY = *yPosPtr + D_801545E4[i].y;
                g_api.CheckCollision(argX, argY, &collider, 0);
                if (collider.effects & 1) {
                    *vram_ptr |= temp_fp;
                    if (!(*vram_ptr & 1)) {
                        *yPosPtr += collider.unk20;
                    }
                    return;
                }
            } else if ((temp_v1 > 0) && (temp_s0 & 1)) {
                argX = var_a1 + (*xPosPtr + D_801545E4[i].x);
                argY = *yPosPtr + D_801545E4[i].y + g_Player.colliders2[i].unk8;
                g_api.CheckCollision(argX, argY, &collider, 0);
                if (collider.effects & 1) {
                    if (!(*vram_ptr & 1)) {
                        *yPosPtr +=
                            collider.unk20 + g_Player.colliders2[i].unk8;
                    }
                    *vram_ptr |= temp_fp;
                    return;
                }
            }
        }
    }
}

void func_8015F414(void) {
    Collider collider;
    s32 temp_s0;
    s32 i;

    s16 argX;
    s16 argY;

    u16* yPosPtr = &PLAYER.posY.i.hi;
    u16* xPosPtr = &PLAYER.posX.i.hi;
    s32* vram_ptr = &g_Player.pl_vram_flag;

    if (g_unkGraphicsStruct.unk18) {
        return;
    }
    temp_s0 =
        g_Player.unk04 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                          EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if ((temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
        (temp_s0 == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
        (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                     EFFECT_SOLID))) {
        *vram_ptr |= 4;
        return;
    }

    for (i = 0; i < 7; i++) {
        temp_s0 = g_Player.colliders3[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_UNK_0002 | EFFECT_SOLID);
        if ((temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_0002 | EFFECT_SOLID))) {
            argX = *xPosPtr + D_80154604[i].x + g_Player.colliders3[i].unk4 - 1;
            argY = *yPosPtr + D_80154604[i].y;
            g_api.CheckCollision(argX, argY, &collider, 0);
            if ((collider.effects & 1) == 0) {
                *vram_ptr |= 4;
                *xPosPtr += g_Player.colliders3[i].unk4;
                return;
            }
        }

        if (!(*vram_ptr & 1)) {
            if ((temp_s0 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                            EFFECT_UNK_0800)) == EFFECT_UNK_8000 &&
                (i != 0) &&
                ((g_Player.colliders3[0].effects & EFFECT_UNK_0800) ||
                 !(g_Player.colliders3[0].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vram_ptr |= 4;
                *xPosPtr += g_Player.colliders3[i].unk4;
                return;
            }
            if (((temp_s0 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                             EFFECT_UNK_0800)) == EFFECT_UNK_0800) &&
                (i != 6) &&
                ((g_Player.colliders3[6].effects & EFFECT_UNK_8000) ||
                 !(g_Player.colliders3[6].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vram_ptr |= 4;
                *xPosPtr += g_Player.colliders3[i].unk4;
                return;
            }
        }
    }
}

void func_8015F680(void) {
    Collider collider;
    s32 temp_s0;
    s32 i;
    s16 argX;
    s16 argY;

    u16* yPosPtr = &PLAYER.posY.i.hi;
    u16* xPosPtr = &PLAYER.posX.i.hi;
    s32* vram_ptr = &g_Player.pl_vram_flag;

    if (g_unkGraphicsStruct.unk18) {
        return;
    }
    temp_s0 =
        g_Player.unk04 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                          EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if ((temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                     EFFECT_SOLID)) ||
        (temp_s0 == (EFFECT_UNK_0800 | EFFECT_UNK_0400 | EFFECT_UNK_0002 |
                     EFFECT_SOLID)) ||
        (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                     EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID))) {
        *vram_ptr |= 8;
        return;
    }
    for (i = 7; i < 14; i++) {
        temp_s0 = g_Player.colliders3[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_UNK_0002 | EFFECT_SOLID);
        if ((temp_s0 == (EFFECT_UNK_8000 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_0800 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_0002 | EFFECT_SOLID))) {
            argX = *xPosPtr + D_80154604[i].x + g_Player.colliders3[i].unkC + 1;
            argY = *yPosPtr + D_80154604[i].y;
            g_api.CheckCollision(argX, argY, &collider, 0);
            if ((collider.effects & 1) == 0) {
                *vram_ptr |= 8;
                *xPosPtr += g_Player.colliders3[i].unkC;
                return;
            }
        }
        if (!(*vram_ptr & 1)) {
            if (((temp_s0 &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                 (EFFECT_UNK_8000 | EFFECT_UNK_4000)) &&
                (i != 7) &&
                ((g_Player.colliders3[7].effects & EFFECT_UNK_0800) ||
                 !(g_Player.colliders3[7].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vram_ptr |= 8;
                *xPosPtr += g_Player.colliders3[i].unkC;
                return;
            }
            if (((temp_s0 &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                 (EFFECT_UNK_4000 | EFFECT_UNK_0800)) &&
                (i != 13) &&
                ((g_Player.colliders3[13].effects & EFFECT_UNK_8000) ||
                 !(g_Player.colliders3[13].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vram_ptr |= 8;
                *xPosPtr += g_Player.colliders3[i].unkC;
                return;
            }
        }
    }
}

Entity* RicGetFreeEntity(s16 start, s16 end) {
    Entity* entity = &g_Entities[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

Entity* RicGetFreeEntityReverse(s16 start, s16 end) {
    Entity* entity = &g_Entities[end - 1];
    s16 i;
    for (i = end - 1; i >= start; i--, entity--) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

static s32 D_80174F80[11];
static void func_8015F9F0(Entity* entity) {
    s32 i;
    s32 enemyId;

    if (entity < &g_Entities[32]) {
        entity->enemyId = 1;
        return;
    }

    for (i = 0;; i++) {
        for (enemyId = 2; enemyId < LEN(D_80174F80); ++enemyId) {
            if (D_80174F80[enemyId] == i) {
                ++D_80174F80[enemyId];
                entity->enemyId = enemyId;
                return;
            }
        }
    }
}

static u8 D_80174FAC;
STATIC_PAD_BSS(3);
static u8 D_80174FB0;
STATIC_PAD_BSS(3);
static u8 D_80174FB4;
STATIC_PAD_BSS(3);
static u8 D_80174FB8;
STATIC_PAD_BSS(3);
void func_8015FA5C(s32 arg0) {
    D_80174FAC = D_80154674[arg0][0];
    D_80174FB0 = D_80154674[arg0][1];
    D_80174FB4 = D_80154674[arg0][2];
    D_80174FB8 = D_80154674[arg0][3];
}

void RicSetSubweaponParams(Entity* entity) {
    u16 attack;
    SubweaponDef* subwpn = &D_80154688[entity->ext.subweapon.subweaponId];

    if (g_Player.timers[PL_T_INVINCIBLE_SCENE]) {
        attack = subwpn->attack * 2;
    } else {
        attack = subwpn->attack;
    }

    entity->attack = attack;
    entity->attackElement = subwpn->attackElement;
    entity->hitboxState = subwpn->hitboxState;
    entity->nFramesInvincibility = subwpn->nFramesInvincibility;
    entity->stunFrames = subwpn->stunFrames;
    entity->hitEffect = subwpn->hitEffect;
    entity->entityRoomIndex = subwpn->entityRoomIndex;
    entity->attack = g_api.func_800FD664(entity->attack);
    func_8015F9F0(entity);
}

// We're playing as Richter and we used a subweapon (normal or crash)
s32 func_8015FB84(SubweaponDef* subwpn, s32 isItemCrash, s32 useHearts) {
    s32 pad[2]; // Needed so stack pointer moves properly
    u8 crashId;
    // Not an item crash. Just read the item in.
    if (isItemCrash == 0) {
        *subwpn = D_80154688[g_Status.subWeapon];
        if (g_Status.hearts >= subwpn->heartCost) {
            if (useHearts) {
                g_Status.hearts -= subwpn->heartCost;
            }
            return g_Status.subWeapon;
        }
    } else {
        // If it's a crash, load the subweapon by referencing our
        // subweapon's crash ID and loading that.
        crashId = D_80154688[g_Status.subWeapon].crashId;
        *subwpn = D_80154688[crashId];
        if (g_Status.hearts >= subwpn->heartCost) {
            if (useHearts) {
                g_Status.hearts -= subwpn->heartCost;
            }
            return g_Status.subWeapon;
        }
    }
    return -1;
}

// Corresponding DRA function is func_80119E78
u8 uv_anim_801548F4[6][8] = {
    {0x00, 0x50, 0x10, 0x50, 0x00, 0x60, 0x10, 0x60},
    {0x10, 0x50, 0x20, 0x50, 0x10, 0x60, 0x20, 0x60},
    {0x70, 0x40, 0x80, 0x40, 0x70, 0x50, 0x80, 0x50},
    {0x70, 0x30, 0x78, 0x30, 0x70, 0x38, 0x78, 0x38},
    {0x78, 0x30, 0x80, 0x30, 0x78, 0x38, 0x80, 0x38},
    {0x70, 0x38, 0x78, 0x38, 0x77, 0x40, 0x78, 0x40}};
s32 func_8015FDB0(Primitive* prim, s16 posX, s16 posY) {
    s16 offset;
    s32 ret;
    u8* uvAnim;

    ret = 0;
    uvAnim = uv_anim_801548F4;
    if (prim->b0 >= 6) {
        prim->b0 = 0;
        ret = -1;
    }

    uvAnim = &uvAnim[prim->b0 * 8];

    if (prim->b0 > 2) {
        offset = 4;
    } else {
        offset = 6;
    }

    prim->x0 = posX - offset;
    prim->y0 = posY - offset;
    prim->x1 = posX + offset;
    prim->y1 = posY - offset;
    prim->x2 = posX - offset;
    prim->y2 = posY + offset;
    prim->x3 = posX + offset;
    prim->y3 = posY + offset;
    prim->u0 = *uvAnim++;
    prim->v0 = *uvAnim++;
    prim->u1 = *uvAnim++;
    prim->v1 = *uvAnim++;
    prim->u2 = *uvAnim++;
    prim->v2 = *uvAnim++;
    prim->u3 = *uvAnim++;
    prim->v3 = *uvAnim;

    if (!(++prim->b1 & 1)) {
        prim->b0++;
    }
    return ret;
}

// Corresponding DRA function is func_80119F70
static Point16 D_80174FBC[16];
void RicEntityHitByHoly(Entity* entity) {
    Primitive* prim;
    s16 temp_xRand;
    s32 temp_yRand;
    s32 i;
    s16 hitboxY;
    s16 hitboxX;
    s32 temp;

    switch (entity->step) {
    case 0:
        entity->primIndex =
            (s16)g_api.AllocPrimitives(PRIM_GT4, LEN(D_80174FBC));
        if (entity->primIndex == -1) {
            DestroyEntity(entity);
            return;
        }
        entity->flags = FLAG_HAS_PRIMS | FLAG_UNK_40000 | FLAG_UNK_20000;
        hitboxX = PLAYER.posX.i.hi + PLAYER.hitboxOffX;
        hitboxY = PLAYER.posY.i.hi + PLAYER.hitboxOffY;
        prim = &g_PrimBuf[entity->primIndex];
        for (i = 0; i < LEN(D_80174FBC); i++) {
            temp_xRand = hitboxX + rand() % 24 - 12;
            temp_yRand = rand();
            D_80174FBC[i].x = temp_xRand;
            D_80174FBC[i].y = hitboxY + temp_yRand % 48 - 24;
            prim->clut = 0x1B2;
            prim->tpage = 0x1A;
            prim->b0 = 0;
            prim->b1 = 0;
            prim->g0 = 0;
            prim->g1 = (rand() & 7) + 1;
            prim->g2 = 0;
            prim->priority = PLAYER.zPriority + 4;
            prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE | DRAW_HIDE |
                             DRAW_UNK02 | DRAW_TRANSP;
            if (rand() & 1) {
                prim->drawMode =
                    DRAW_UNK_100 | DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                    DRAW_HIDE | DRAW_UNK02 | DRAW_TRANSP;
            }
            prim = prim->next;
        }
        entity->step++;
        break;
    case 1:
        if (!(g_Player.unk0C & 0x10000)) {
            DestroyEntity(entity);
            return;
        }
        break;
    }

    prim = &g_PrimBuf[entity->primIndex];
    for (i = 0; i < 16; i += 1) {
        switch (prim->g0) {
        case 0:
            if (!(--prim->g1 & 0xFF)) {
                prim->g0++;
            }
            break;
        case 1:
            hitboxY = D_80174FBC[i].x;
            hitboxX = D_80174FBC[i].y;
            temp = func_8015FDB0((POLY_GT4*)prim, hitboxY, hitboxX);
            D_80174FBC[i].y--;
            if (temp < 0) {
                prim->drawMode |= DRAW_HIDE;
                prim->g0++;
            } else {
                prim->drawMode &= ~DRAW_HIDE;
            }
            break;
        }
        prim = prim->next;
    }
}

// same as DRA/func_8011F074
static AnimationFrame anim_smoke_dark[] = {
    {2, FRAME(1, 0)},  {2, FRAME(2, 0)},
    {2, FRAME(3, 0)},  {2, FRAME(4, 0)},
    {2, FRAME(5, 0)},  {2, FRAME(6, 0)},
    {2, FRAME(7, 0)},  {2, FRAME(8, 0)},
    {2, FRAME(9, 0)},  {2, FRAME(10, 0)},
    {2, FRAME(11, 0)}, {2, FRAME(12, 0)},
    {2, FRAME(13, 0)}, A_END};
static s32 D_80174FFC;
void RicEntityHitByDark(Entity* entity) {
    s16 posX;
    s16 posY;

    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_20000 | FLAG_UNK_100000 | FLAG_UNK_08000000;
        entity->unk5A = 0x79;
        entity->animSet = ANIMSET_DRA(14);
        entity->zPriority = PLAYER.zPriority + 2;
        entity->palette = 0x819F;

        if (D_80174FFC & 1) {
            entity->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
        } else {
            entity->drawMode = DRAW_TPAGE;
        }
        entity->rotY = 0x40;
        entity->rotX = 0x40;
        entity->anim = anim_smoke_dark;
        D_80174FFC++;
        entity->unk6C = 0xFF;
        entity->drawFlags =
            FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20;
        posX = 10;
        posY = 15;
        entity->posY.i.hi = entity->posY.i.hi - posY + (rand() % 35);
        entity->posX.i.hi = entity->posX.i.hi - posX + (rand() % 20);
        entity->velocityY = -0x6000 - (rand() & 0x3FFF);
        entity->step++;
        break;

    case 1:
        if (entity->unk6C >= 17) {
            entity->unk6C += 248;
        }
        entity->posY.val += entity->velocityY;
        entity->rotX += 8;
        entity->rotY += 8;
        if (entity->animFrameDuration < 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

static void RicEntityDummy(Entity* self) {}

static void func_801603BC(void) {}

void RicEntityFactory(Entity* self);
void RicEntitySmokePuff(Entity* self);
void RicEntitySubwpnCross(Entity* self);
void func_80169C10(Entity* self);
void RicEntityHitByCutBlood(Entity* self);
void RicEntitySubwpnCrossTrail(Entity* self);
void RicEntitySubwpnHolyWater(Entity* self);
void RicEntitySubwpnHolyWaterFlame(Entity* self);
void func_80161C2C(Entity* self);
void RicEntityWhip(Entity* self);
void RicEntityCrashHydroStorm(Entity* self);
void RicEntityCrashCrossBeam(Entity* self);
void RicEntitySubwpnCrashCross(Entity* self);
void RicEntityNotImplemented1(Entity* self);
void RicEntityNotImplemented2(Entity* self);
void RicEntityArmBrandishWhip(Entity* self);
void func_80167964(Entity* self);
void RicEntityDummy(Entity* self);
void func_80161EF8(Entity* self);
void RicEntityNotImplemented3(Entity* self);
void RicEntityRevivalColumn(Entity* self);
void RicEntityApplyMariaPowerAnim(Entity* self);
void func_80160C38(Entity* self);
void RicEntityBladeDash(Entity* self);
void func_801623E0(Entity* self);
void func_80162604(Entity* self);
void RicEntityMaria(Entity* self);
void RicEntityMariaPowers(Entity* self);
void func_80160F0C(Entity* self);
void RicEntityNotImplemented4(Entity* self);
void RicEntityPlayerBlinkWhite(Entity* self);
void RicEntitySubwpnCrashCrossParticles(Entity* self);
void func_801641A0(Entity* self);
void RicEntityShrinkingPowerUpRing(Entity* self);
void func_80167A70(Entity* self);
void RicEntitySubwpnAxe(Entity* self);
void RicEntityCrashAxe(Entity* self);
void RicEntitySubwpnDagger(Entity* self);
void func_80160D2C(Entity* self);
void RicEntityHitByIce(Entity* self);
void RicEntityHitByLightning(Entity* self);
void RicEntitySubwpnReboundStone(Entity* self);
void RicEntitySubwpnThrownVibhuti(Entity* self);
void RicEntitySubwpnAgunea(Entity* self);
void RicEntityAguneaHitEnemy(Entity* self);
void RicEntityCrashVibhuti(Entity* self);
void RicEntityVibhutiCrashCloud(Entity* self);
void RicEntityCrashReboundStone(Entity* self);
void func_8016D9C4(Entity* self);
void RicEntityCrashReboundStoneExplosion(Entity* self);
void RicEntityCrashBible(Entity* self);
void RicEntityCrashBibleBeam(Entity* self);
void RicEntitySubpwnBible(Entity* self);
void RicEntitySubpwnBibleTrail(Entity* self);
void RicEntitySubwpnStopwatch(Entity* self);
void RicEntitySubwpnStopwatchCircle(Entity* self);
void func_801705EC(Entity* self);
void func_8016F198(Entity* self);
void RicEntityAguneaCircle(Entity* self);
void RicEntityAguneaLightning(Entity* self);
void RicEntityCrashReboundStoneParticles(Entity* self);
void RicEntityHitByDark(Entity* self);
void RicEntityHitByHoly(Entity* self);
void RicEntityCrashStopwatchDoneSparkle(Entity* self);
void func_80170548(Entity* self);
void RicEntityTeleport(Entity* self);
void RicEntityDummy(Entity* self);
static PfnEntityUpdate entity_functions[] = {
    RicEntityDummy,
    RicEntityFactory,
    RicEntitySmokePuff,
    RicEntitySubwpnCross,
    func_80169C10,
    RicEntityHitByCutBlood,
    RicEntitySubwpnCrossTrail,
    RicEntitySubwpnHolyWater,
    RicEntitySubwpnHolyWaterFlame,
    func_80161C2C,
    RicEntityWhip,
    RicEntityCrashHydroStorm,
    RicEntityCrashCrossBeam,
    RicEntitySubwpnCrashCross,
    RicEntityNotImplemented1,
    RicEntityNotImplemented2,
    RicEntityArmBrandishWhip,
    func_80167964,
    RicEntityDummy,
    func_80161EF8,
    RicEntityNotImplemented3,
    RicEntityRevivalColumn,
    RicEntityApplyMariaPowerAnim,
    func_80160C38,
    RicEntityBladeDash,
    func_801623E0,
    func_80162604,
    RicEntityMaria,
    RicEntityMariaPowers,
    func_80160F0C,
    RicEntityNotImplemented4,
    RicEntityPlayerBlinkWhite,
    RicEntitySubwpnCrashCrossParticles,
    func_801641A0,
    RicEntityShrinkingPowerUpRing,
    func_80167A70,
    RicEntitySubwpnAxe,
    RicEntityCrashAxe,
    RicEntitySubwpnDagger,
    func_80160D2C,
    RicEntityHitByIce,
    RicEntityHitByLightning,
    RicEntitySubwpnReboundStone,
    RicEntitySubwpnThrownVibhuti,
    RicEntitySubwpnAgunea,
    RicEntityAguneaHitEnemy,
    RicEntityCrashVibhuti,
    RicEntityVibhutiCrashCloud,
    RicEntityCrashReboundStone,
    func_8016D9C4,
    RicEntityCrashReboundStoneExplosion,
    RicEntityCrashBible,
    RicEntityCrashBibleBeam,
    RicEntitySubpwnBible,
    RicEntitySubpwnBibleTrail,
    RicEntitySubwpnStopwatch,
    RicEntitySubwpnStopwatchCircle,
    func_801705EC,
    func_8016F198,
    RicEntityAguneaCircle,
    RicEntityAguneaLightning,
    RicEntityCrashReboundStoneParticles,
    RicEntityHitByDark,
    RicEntityHitByHoly,
    RicEntityCrashStopwatchDoneSparkle,
    func_80170548,
    RicEntityTeleport,
    RicEntityDummy};
STATIC_ASSERT(LEN(entity_functions) == NUM_ENTITIES, "entity array wrong size");

// Corresponding DRA function is UpdatePlayerEntities
void RicUpdatePlayerEntities(void) {
    SubweaponDef subwpn;
    Entity* entity;
    s32 i;
    s32 i2;
    s32 i3;
    s32 isPrologueTimeStopped;
    s32 enemy;
    s32 enemy2;

    isPrologueTimeStopped = g_unkGraphicsStruct.unk20;
    entity = g_CurrentEntity = &g_Entities[4];
    for (i = 4; i < 0x40; i++, g_CurrentEntity++, entity++) {
        if (entity->entityId) {
            if (entity->step == 0) {
                entity->pfnUpdate = entity_functions[entity->entityId];
            }
            if (!isPrologueTimeStopped || (entity->flags & FLAG_UNK_10000)) {
                entity->pfnUpdate(entity);
                entity = g_CurrentEntity;
                if (entity->entityId) {
                    if (!(entity->flags & FLAG_UNK_04000000) &&
                        (entity->posX.i.hi < -32 || entity->posX.i.hi > 288 ||
                         entity->posY.i.hi < -16 || entity->posY.i.hi > 256)) {
                        DestroyEntity(entity);
                    } else if (entity->flags & FLAG_UNK_100000) {
                        g_api.UpdateAnim(0, D_80154674);
                    }
                }
            }
        }
    }

    if (D_80174FAC != 0) {
        if (--D_80174FAC & 1) {
            g_api.g_pfn_800EA5AC(1, D_80174FB0, D_80174FB4, D_80174FB8);
        }
    }

    D_80174F80[1] = D_80174F80[2] = 0;
    enemy = g_Entities[16].enemyId;
    if (enemy == 1) {
        D_80174F80[1] = 1;
    } else if (enemy == 2) {
        D_80174F80[2] = 1;
    }

    for (i2 = 3; i2 < 11; i2++) {
        D_80174F80[i2] = 0;
    }

    entity = &g_Entities[17];
    for (i3 = 17; i3 < 48; entity++, i3++) {
        enemy2 = entity->enemyId;
        if (enemy2 >= 3) {
            D_80174F80[entity->enemyId]++;
        }
    }
    // This IF will fire if we have enough hearts to use a subweapon crash.
    // No idea what it's doing here.
    if (func_8015FB84(&subwpn, true, false) >= 0) {
        g_Player.unk0C |= PLAYER_STATUS_UNK200000;
    }
    if (g_Player.unk0C & (PLAYER_STATUS_UNK40000 | PLAYER_STATUS_UNK80000)) {
        FntPrint("dead player\n");
        entity = &g_Entities[17]; // Weird code here. Set entity to #17 but...
        entity -= 13; // then change to #4 before the for-loop starting with 4?
        for (i = 4; i < 64; i++, entity++) {
            entity->hitboxState = 0;
        }
    }
}

FactoryBlueprint g_RicFactoryBlueprints[] = {
    B_MAKE(E_SMOKE_PUFF, 5, 1, true, true, 2, B_DECOR, 0, 0),
    B_MAKE(E_SMOKE_PUFF, 3, 1, true, true, 4, B_DECOR, 2, 0),
    B_MAKE(E_SUBWPN_CROSS, 1, 1, true, true, 0, B_KIND_9, 1, 8),
    B_MAKE(E_80169C10, 3, 1, true, true, 2, B_DECOR, 0, 0),
    B_MAKE(E_HIT_BY_CUT_BLOOD, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_SUBWPN_CROSS_TRAIL, 4, 1, true, true, 4, B_DECOR, 0, 4),
    B_MAKE(E_SUBWPN_HOLY_WATER, 1, 1, true, true, 0, B_KIND_9, 1, 8),
    B_MAKE(E_SUBWPN_HOLY_WATER_FLAME, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_80161C2C, 6, 1, true, true, 12, B_KIND_8, 3, 0),
    B_MAKE(E_80161C2C, 128, 1, true, true, 3, B_KIND_8, 3, 8),
    B_MAKE(E_WHIP, 15, 15, false, true, 0, B_KIND_10, 1, 0),
    B_MAKE(E_HIT_BY_CUT_BLOOD, 72, 1, true, true, 2, B_KIND_3, 1, 0),
    B_MAKE(E_CRASH_HYDROSTORM, 48, 1, false, true, 6, B_WPN, 1, 48),
    B_MAKE(E_CRASH_CROSS_ROTATING, 1, 1, false, true, 0, B_KIND_9, 0, 0),
    B_MAKE(E_CRASH_CROSS_BEAM, 6, 1, true, true, 24, B_KIND_9, 0, 0),
    B_MAKE(E_NOT_IMPLEMENTED_1, 16, 16, false, true, 0, B_KIND_8, 1, 0),
    B_MAKE(E_NOT_IMPLEMENTED_2, 15, 15, true, true, 0, B_KIND_8, 1, 0),
    B_MAKE(E_ARM_BRANDISH_WHIP, 1, 1, false, true, 0, B_KIND_12, 1, 0),
    B_MAKE(E_80167964, 1, 1, true, true, 0, B_KIND_8, 0, 0),
    B_MAKE(E_SUBWPN_AXE, 1, 1, true, true, 0, B_KIND_9, 1, 8),
    B_MAKE(E_80161EF8, 1, 1, true, true, 0, B_DECOR, 4, 0),
    B_MAKE(E_NOT_IMPLEMENTED_3, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_REVIVAL_COLUMN, 1, 1, false, true, 0, B_KIND_3, 0, 0),
    B_MAKE(E_APPLY_MARIA_POWER_ANIM, 4, 1, false, true, 24, B_KIND_3, 0, 0),
    B_MAKE(E_SMOKE_PUFF, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_80160C38, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_BLADE_DASH, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_801623E0, 1, 1, true, true, 0, B_KIND_3, 0, 0),
    B_MAKE(E_80162604, 1, 1, true, true, 0, B_KIND_3, 0, 0),
    B_MAKE(E_MARIA, 1, 1, false, true, 0, B_KIND_5, 0, 0),
    B_MAKE(E_MARIA_POWERS, 4, 1, true, true, 4, B_KIND_3, 0, 0),
    B_MAKE(E_80160D2C, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_NOT_IMPLEMENTED_4, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_BLINK_WHITE, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_SUBWPN_CRASH_CROSS_PARTICLES, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_801641A0, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_SHRINKING_POWERUP_RING, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_SHRINKING_POWERUP_RING, 1, 1, true, true, 0, B_DECOR, 0, 4),
    B_MAKE(E_SHRINKING_POWERUP_RING, 1, 1, true, true, 0, B_DECOR, 0, 8),
    B_MAKE(E_SHRINKING_POWERUP_RING, 1, 1, true, true, 0, B_DECOR, 0, 12),
    B_MAKE(E_80167A70, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_CRASH_AXE, 8, 8, false, true, 0, B_WPN, 1, 32),
    B_MAKE(E_HIT_BY_CUT_BLOOD, 3, 1, true, true, 3, B_DECOR, 0, 0),
    B_MAKE(E_SUBWPN_DAGGER, 1, 1, true, true, 0, B_KIND_9, 1, 8),
    B_MAKE(E_SUBWPN_DAGGER, 128, 1, false, true, 4, B_KIND_14, 4, 8),
    B_MAKE(E_80160F0C, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_HIT_BY_CUT_BLOOD, 12, 1, true, true, 2, B_KIND_8, 3, 0),
    B_MAKE(E_HIT_BY_ICE, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_HIT_BY_LIGHTNING, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_SUBWPN_VIBHUTI, 1, 1, true, true, 0, B_WPN, 1, 8),
    B_MAKE(E_SUBWPN_REBOUND_STONE, 1, 1, true, true, 0, B_WPN, 1, 4),
    B_MAKE(E_SUBWPN_AGUNEA, 1, 1, true, true, 0, B_WPN, 1, 4),
    B_MAKE(E_SUBWPN_AGUNEA_HIT_ENEMY, 1, 1, true, true, 0, B_DECOR, 1, 0),
    B_MAKE(E_80161C2C, 72, 1, true, true, 2, B_KIND_3, 1, 16),
    B_MAKE(E_CRASH_VIBHUTI, 1, 1, false, true, 0, B_DECOR, 0, 18),
    B_MAKE(E_CRASH_VIBHUTI_CLOUD, 1, 1, true, true, 0, B_KIND_6, 0, 0),
    B_MAKE(E_CRASH_REBOUND_STONE, 1, 1, false, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_8016D9C4, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_CRASH_REBOUND_STONE_EXPLOSION, 1, 1, false, true, 0, B_WPN, 0, 0),
    B_MAKE(E_CRASH_BIBLE, 1, 1, false, true, 0, B_WPN, 0, 0),
    B_MAKE(E_CRASH_BIBLE_BEAM, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_SUBWPN_BIBLE, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_SUBWPN_BIBLE_TRAIL, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_SUBWPN_STOPWATCH, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_SUBWPN_STOPWATCH_CIRCLE, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_801705EC, 1, 1, false, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_8016F198, 2, 1, true, true, 2, B_DECOR, 0, 0),
    B_MAKE(E_AGUNEA_CIRCLE, 1, 1, false, true, 0, B_WPN, 0, 20),
    B_MAKE(E_AGUNEA_LIGHTNING, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(
        E_CRASH_REBOUND_STONE_PARTICLES, 1, 1, true, true, 0, B_KIND_3, 0, 0),
    B_MAKE(E_HIT_BY_DARK, 96, 1, true, true, 4, B_KIND_8, 1, 0),
    B_MAKE(E_HIT_BY_HOLY, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_CRASH_STOPWATCH_DONE_PARTICLE, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_80170548, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_SMOKE_PUFF, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_SMOKE_PUFF, 4, 1, true, true, 2, B_DECOR, 3, 0),
    B_MAKE(E_SMOKE_PUFF, 6, 6, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_TELEPORT, 1, 1, false, true, 0, B_KIND_3, 0, 0),
};
STATIC_ASSERT(
    LEN(g_RicFactoryBlueprints) == NUM_BLUEPRINTS, "bp array wrong size");

// Similar to the version in DRA but with some logic removed
Entity* RicCreateEntFactoryFromEntity(
    Entity* source, u32 factoryParams, s32 arg2) {
    /**
     * arg2 is unused, but needed to match other functions that call
     * this function, probably part of the code for a debug build
     */
    Entity* entity = RicGetFreeEntity(8, 16);

    if (entity != NULL) {
        DestroyEntity(entity);
        entity->entityId = E_FACTORY;
        // the parent pointer must align for anything the factory creates
        entity->ext.factory.parent = source;
        entity->posX.val = source->posX.val;
        entity->posY.val = source->posY.val;
        entity->facingLeft = source->facingLeft;
        entity->zPriority = source->zPriority;
        entity->params = factoryParams & 0xFFF;
        entity->ext.factory.unkA0 = (factoryParams >> 8) & 0xFF00;
        if (source->flags & FLAG_UNK_10000) {
            entity->flags |= FLAG_UNK_10000;
        }
    } else {
        return NULL;
    }
    return entity;
}
