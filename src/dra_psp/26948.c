// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_psp_091032C8);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", RenderTilemap);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", SetRoomForegroundLayer);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", SetRoomBackgroundLayer);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", LoadRoomLayer);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_psp_09103E68);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_800EAEA4);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", ResetPendingGfxLoad);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", LoadGfxAsync);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_psp_091040A0);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", DecompressWriteNibble);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", DecompressReadNibble);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", DecompressData);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", LoadPendingGfx);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_800EB4F8);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", LoadEquipIcon);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_psp_09104810);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_psp_09104878);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_psp_091048B8);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_801092E8);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_80109328);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_801093C4);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_psp_09104C80);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_80109990);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", CheckStageCollision);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_8010A234);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_8010A3F0);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", GetTeleportToOtherCastle);

extern bool D_8C630C4;

extern s32 D_800ACDF8;
extern s32 D_800ACDFC;
extern s32 D_800ACE00[];
extern s16 D_800ACE20[];

extern s32 D_80137FB8;

extern s32 D_psp_09234B68;
extern s32 D_psp_09234B88;
extern s32 D_psp_09234B90;

void EntityAlucard() {
    s32 sp5c;
    s32 sp58;
    s32 sp54;
    DamageParam damage; //sp44
    s32 sp40 = 0;
    unkstr_800cfe48* sp3c;
    s32 sp38;
    void (*weapon_func)();
    PlayerDraw* draw;

    s32 var_s8;
    s32 var_s7;
    s16 var_s6;
    s16 var_s5;
    s16 var_s3;
    u32 newStatus_s2;
    s32 i;
    s16 playerHitPoints;


    g_CurrentEntity = &PLAYER;
    if (D_800ACE44 != 0) {
        D_800ACE44--;
    }
    if (g_unkGraphicsStruct.D_800973FC != 0 && D_80137FB8 == 0) {
        CreateEntFactoryFromEntity(g_CurrentEntity, 0x78, 0);
    }
    D_80137FB8 = g_unkGraphicsStruct.D_800973FC;
    g_Player.unk4C = 0;

    var_s8 = 0;
    var_s6 = 0;
    var_s5 = 0;
    var_s8 = 0;
    PLAYER.drawFlags = 0;
    g_Player.unk18 = 0;
    g_Player.unk70 = 0;
    
    g_Player.unk72 = func_80110394();
    if (!(g_Player.status & PLAYER_STATUS_DEAD)) {
        i = GetTeleportToOtherCastle();
        if (i != 0) {
            func_8010E42C(i);
        }
        if (PLAYER.step != 0x12) {
            func_8010A234(0);
            func_8010A3F0();
            func_80109990();
            if (g_Player.unk56) {
                g_Status.hp += g_Player.unk58;
                func_800FE8F0();
                CreateHPNumMove(g_Player.unk58, 1);
                if (g_Player.unk56 == 1) {
                    PlaySfx(SFX_HEALTH_PICKUP);
                    if (!(g_Player.status & PLAYER_STATUS_STONE)) {
                        CreateEntFactoryFromEntity(
                            g_CurrentEntity, FACTORY(0x2C, 0x48), 0);
                        CreateEntFactoryFromEntity(
                            g_CurrentEntity, FACTORY(0x2C, 0x44), 0);
                    }
                }
                if ((g_Player.unk56 == 2) &&
                    !(g_Player.status & PLAYER_STATUS_STONE)) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x2C, 0x48), 0);
                }
                if (g_Status.hpMax < g_Status.hp) {
                    g_Status.hp = g_Status.hpMax;
                }
                g_Player.unk56 = 0;
            }
            i = CheckAndDoLevelUp();
            if (i != 0) {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x19, i - 1), 0);
            }
            for (i = 0; i < 16; i++) {
                if (g_Player.timers[i]) {
                    switch (i) {
                    case 0:
                    case 1:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 12:
                    case 13:
                    case 14:
                        break;
                    case 2:
                        PLAYER.palette = g_Player.unk40;
                        break;
                    case 3:
                        PLAYER.palette = g_Player.high_jump_timer;
                        g_Player.timers[15] = 12;
                        break;
                    case 4: {
                        var_s3 = ((g_GameTimer & 0xF) << 8);
                        draw = g_PlayerDraw;
                        draw->r0 = draw->b0 = draw->g0 = (rsin(var_s3) + 0x1000) / 64 + 0x60;
                        var_s3 += 0x200;
                        draw->r1 = draw->b1 = draw->g1 = (rsin(var_s3) + 0x1000) / 64 + 0x60;
                        var_s3 += 0x200;
                        draw->r3 = draw->b3 = draw->g3 = (rsin(var_s3) + 0x1000) / 64 + 0x60;
                        var_s3 += 0x200;
                        draw->r2 = draw->b2 = draw->g2 = (rsin(var_s3) + 0x1000) / 64 + 0x60;
                        draw->enableColorBlend = 1;
                        break;
                    }
                    case 15:
                        func_8010DFF0(0, 0);
                        break;
                    case 11:
                        if (D_800ACDF8 == 0) {
                            func_801092E8(1);
                        }
                        break;

                    }
                    if (--g_Player.timers[i] == 0) {
                        switch (i) {
                        case 5:
                        case 7:
                        case 8:
                        case 9:
                        case 10:
                        case 12:
                        case 14:
                            break;    
                        case 0:
                            if (!(g_Player.status & (PLAYER_STATUS_STONE |
                                                     PLAYER_STATUS_CURSE))) {
                                g_Player.timers[4] = 0xC;
                                g_Player.timers[15] = 0xC;
                                func_8010E168(1, 0xC);
                            }
                            continue;
                        case 1:
                            if (!(g_Player.status & (PLAYER_STATUS_STONE |
                                                     PLAYER_STATUS_CURSE))) {
                                g_Player.timers[4] = 0xC;
                                g_Player.timers[15] = 0xC;
                                func_8010E168(1, 0xC);
                            }
                            continue;
                        case 2:
                            PLAYER.palette = 0x8100;
                            continue;
                        case 3:
                            PLAYER.palette = 0x8100;
                            if (!(g_Player.status &
                                  (PLAYER_STATUS_STONE | PLAYER_STATUS_POISON |
                                   PLAYER_STATUS_CURSE))) {
                                g_Player.timers[4] = 0xC;
                                g_Player.timers[15] = 0xC;
                                func_8010E168(1, 0xC);
                            }
                            continue;
                        case 4:
                            draw->enableColorBlend = 0;
                            continue;
                        case 6:
                            if ((PLAYER.step == 3) &&
                                (PLAYER.ext.player.anim != 0x1C)) {
                                SetPlayerAnim(0x1C);
                                g_Player.unk44 &= 0xFFEF;
                            }
                            continue;
                        case 13:
                            func_8010E168(1, 0x10);
                            continue;
                        case 15:
                            func_8010E0B8();
                            continue;
                        case 11:
                            func_801092E8(0);
                            continue;
                        }
                    }
                }
            }
            if (D_800ACDFC != 0) {
                D_800ACDFC--;
            }
            g_Player.padHeld = g_Player.padPressed;
            if (g_Player.demo_timer != 0) {
                sp38 = 1;
            } else {
                sp38 = 0;
            }
            sp40 = sp38;
            if (g_Player.demo_timer != 0) {
                g_Player.demo_timer--;
                g_Player.padPressed = g_Player.padSim & 0xFFFF;
                switch (g_Player.padSim >> 0x10) { /* switch 6; irregular */
                case 1:                            /* switch 6 */
                    if (PLAYER.step != Player_Unk48) {
                        func_8010E168(1, 4);
                        SetPlayerStep(Player_Unk48);
                        g_unkGraphicsStruct.pauseEnemies = 1;
                    }
                    break;
                case 2: /* switch 6 */
                    func_8010E168(1, 4);
                    if (g_Player.status & PLAYER_STATUS_AXEARMOR) {
                        SetPlayerStep(Player_Unk50);
                    } else {
                        SetPlayerStep(Player_Unk49);
                    }
                    g_unkGraphicsStruct.pauseEnemies = 1;
                    break;
                }
            } else {
                g_Player.padPressed = g_pads[0].pressed & ~(PAD_SQUARE | PAD_CROSS | PAD_TRIANGLE | PAD_CIRCLE | PAD_L1 | PAD_R1);
                for (i = 0; i < 6; i++) {
                    if (g_Settings.buttonMask[i] == (g_pads[0].pressed & g_Settings.buttonMask[i])) {
                        g_Player.padPressed |= D_800ACE00[i];
                    }
                }
            }
            g_Player.padTapped =
                (g_Player.padHeld ^ g_Player.padPressed) & g_Player.padPressed;
            if (g_Player.status & PLAYER_STATUS_UNK8) {
                g_Player.padTapped &= ~(PAD_SQUARE | PAD_CIRCLE);
                g_Player.padPressed &= ~(PAD_SQUARE | PAD_CIRCLE);
            }
            if ((g_DebugPlayer != 0) && (func_801119C4() != 0)) {
                return;
            }
            if ((D_80097448[1] != 0) &&
                (IsRelicActive(RELIC_HOLY_SYMBOL) == 0) &&
                !(PLAYER.hitParams & 0x1F)) {
                PLAYER.hitParams = 6;
            }

            if (g_Player.timers[13] | g_Player.timers[14]) {
                goto specialmove;
            }
            if (g_Player.unk60 < 2) {
                if (g_Player.unk60 == 1) {
                    var_s6 = PLAYER.step;
                    var_s5 = PLAYER.step_s;
                    SetPlayerStep(Player_BossGrab);
                } else {
                    if (1) { // to make curly braces match
                        if (PLAYER.hitParams) {
                            var_s6 = PLAYER.step;
                            var_s5 = PLAYER.step_s;
                            i = HandleDamage(
                                &damage, PLAYER.hitParams, PLAYER.hitPoints, 0);
                            if(D_8C630C4){
                                PLAYER.hitPoints = 0;
                                i = 0;
                            }
                            if ((g_Player.status & PLAYER_STATUS_AXEARMOR) &&
                                ((i == 1) || (i == 8) ||
                                 (i == 7))) {
                                i = 3;
                                damage.damageKind = DAMAGEKIND_1;
                            }
                            switch (i) {
                            case 0:
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, FACTORY(0x2F, 0), 0);
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, FACTORY(0x2C, 0x43), 0);
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, FACTORY(0x2C, 0x51), 0);
                                CreateHPNumMove(0, 0);
                                func_8010E168(1, 0xC);
                                break;
                            case 1:
                                g_Player.unk18 = damage.effects;
                                g_Player.high_jump_timer = 0x8166;
                                func_8010E168(1, 0xC);
                                g_Player.timers[3] = 6;
                                PlaySfx(SFX_VO_ALU_PAIN_A);
                                CreateHPNumMove(1, 0);
                                break;
                            case 2:
                                g_Player.unk18 = damage.effects;
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, FACTORY(0x73, 0), 0);
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, FACTORY(0x2C, 0x58), 0);
                                g_Player.high_jump_timer = 0x8166;
                                func_8010E168(1, 0xC);
                                g_Player.timers[3] = 6;
                                break;
                            case 3:
                                g_Player.unk18 = damage.effects;
                                SetPlayerStep(Player_Hit);
                                CreateHPNumMove(damage.damageTaken, 0);
                                break;
                            case 4:
                                CreateHPNumMove(damage.damageTaken, 0);
                                SetPlayerStep(Player_Kill);
                                break;
                            case 5:
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, FACTORY(0x2C, 0x44), 0);
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, FACTORY(0x2C, 0x48), 0);
                                CreateHPNumMove(damage.unkC, 1);
                                func_8010E168(1, 0xC);
                                break;
                            case 6:
                                SetPlayerStep(Player_KillWater);
                                break;
                            case 7:
                                g_Player.unk18 = damage.effects;
                                SetPlayerStep(Player_StatusStone);
                                CreateHPNumMove(damage.damageTaken, 0);
                                break;
                            case 8:
                                g_Player.unk18 = damage.effects;
                                CreateHPNumMove(damage.damageTaken, 0);
                                var_s8 = 1;
                                break;
                            case 9:
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, FACTORY(0x2C, 0x4E), 0);
                                if (D_800ACDFC == 0) {
                                    PlaySfx(SFX_VO_ALU_PAIN_E);
                                }
                                D_800ACDFC = 0x20;
                                if (damage.damageTaken != 0) {
                                    PlaySfx(SFX_WATER_DAMAGE_SWISHES);
                                }
                                break;
                            }
                        }
                    }
                specialmove:
                    CheckSpecialMoveInputs();
                    if (D_psp_09234B68 != 0){
                        D_psp_09234B68--;
                    }
                    if(D_psp_09234B68 == 0) {
                        var_s7 = g_Player.padPressed;
                        if(sp40 != 0 || PLAYER.step == Player_MorphMist || PLAYER.step == Player_MorphWolf || PLAYER.step == Player_MorphBat){
                                    D_psp_09234B88 = 0;
                                    D_psp_09234B90 = g_Player.padTapped;
                        } else {
                            if(var_s7 & 0x300){
                                D_psp_09234B90 |= (var_s7 & 0x300);
                                D_psp_09234B88++;
                                if(D_psp_09234B88 <= 5){
                                    g_Player.padTapped = var_s7 & ~0x300;
                                }
                                if(D_psp_09234B88 == 6){
                                    g_Player.padTapped |= D_psp_09234B90;
                                }
                            } else {
                                if(D_psp_09234B88 != 0){
                                    D_psp_09234B88 = 0;
                                    g_Player.padTapped = D_psp_09234B90;
                                } else {
                                    D_psp_09234B88 = 0;
                                    D_psp_09234B90 = 0;
                                }
                            }
                        }
                        
                        if (D_80097448[1] == 0) {
                            if (((g_Player.padTapped & BTN_MIST) == BTN_MIST) &&
                                (HandleTransformationMP(
                                     FORM_MIST, CHECK_ONLY) == 0) &&
                                ((PLAYER.step == Player_Stand) || 
                                 (PLAYER.step == Player_Walk) ||
                                 (PLAYER.step == Player_Crouch) || 
                                 (PLAYER.step == Player_Fall) ||
                                 (PLAYER.step == Player_Jump) || 
                                 (PLAYER.step == Player_AlucardStuck) ||
                                 (PLAYER.step == Player_HighJump) ||
                                 ((PLAYER.step == Player_MorphBat) && (PLAYER.step_s)) ||
                                 ((PLAYER.step == Player_MorphWolf) && (PLAYER.step_s) && (PLAYER.step_s != 8)))) {
                                func_80109328();
                                SetPlayerStep(Player_MorphMist);
                                PlaySfx(SFX_TRANSFORM_LOW);
                                goto block_159;
                            }
                            if (((g_Player.padTapped & BTN_MIST) == PAD_R1) &&
                                (HandleTransformationMP(
                                    FORM_BAT, CHECK_ONLY) == 0) &&
                                ((PLAYER.step == Player_Stand) || 
                                 (PLAYER.step == Player_Walk) ||
                                 (PLAYER.step == Player_Crouch) || 
                                 (PLAYER.step == Player_Fall) ||
                                 (PLAYER.step == Player_Jump) || 
                                 (PLAYER.step == Player_AlucardStuck) ||
                                 (PLAYER.step == Player_HighJump) ||
                                 (PLAYER.step == Player_MorphMist) ||
                                 ((PLAYER.step == Player_MorphWolf) && (PLAYER.step_s) && (PLAYER.step_s != 8)))) {
                                    if (PLAYER.step == 6 || PLAYER.step == 2) {
                                        D_8013AECC = 0xC;
                                    }
                                    func_80109328();
                                    SetPlayerStep(Player_MorphBat);
                                    PlaySfx(SFX_TRANSFORM_LOW);
                                    goto block_160;
                                }
                        }
                        if (((g_Player.padTapped & BTN_MIST) == PAD_L1) &&
                            (HandleTransformationMP(
                                FORM_WOLF, CHECK_ONLY) == 0) &&
                            ((D_80097448[1] == 0) ||
                             IsRelicActive(RELIC_HOLY_SYMBOL)) &&
                            ((PLAYER.step == Player_Stand) || 
                             (PLAYER.step == Player_Walk) ||
                             (PLAYER.step == Player_Crouch) || 
                             (PLAYER.step == Player_Fall) ||
                             (PLAYER.step == Player_Jump) || 
                             (PLAYER.step == Player_AlucardStuck) ||
                             (PLAYER.step == Player_HighJump) ||
                            (PLAYER.step == Player_MorphMist) || 
                            ((PLAYER.step == Player_MorphBat) && (PLAYER.step_s)))) {
                            func_80109328();
                            SetPlayerStep(0x18);
                            PlaySfx(SFX_TRANSFORM);
                        }
                    }
                }
            }
        }
    }
block_159:
block_160:
    g_Player.prev_step = PLAYER.step;
    g_Player.prev_step_s = PLAYER.step_s;
    D_800ACDF8 = g_Player.timers[ALU_T_DARKMETAMORPH];
    switch (PLAYER.step) {
case Player_Stand:
        PlayerStepStand();
        break;
    case Player_Walk:
        PlayerStepWalk();
        break;
    case Player_Crouch:
        PlayerStepCrouch();
        break;
    case Player_Fall:
        PlayerStepFall();
        break;
    case Player_Jump:
        PlayerStepJump();
        break;
    case Player_MorphBat:
        ControlBatForm();
        break;
    case Player_UnmorphBat:
        PlayerStepUnmorphBat();
        break;
    case Player_MorphMist:
        ControlMistForm();
        break;
    case Player_UnmorphMist:
        PlayerStepUnmorphMist();
        break;
    case Player_MorphWolf:
        PlayerStepMorphWolf();
        break;
    case Player_UnmorphWolf:
        PlayerStepUnmorphWolf();
        break;
    case Player_HighJump:
        PlayerStepHighJump();
        break;
    case Player_SwordWarp:
        PlayerStepSwordWarp();
        break;
    case Player_Hit:
        AlucardHandleDamage(&damage, var_s6, var_s5);
        break;
    case Player_StatusStone:
        PlayerStepStoned(var_s8);
        break;
    case Player_BossGrab:
        PlayerStepBossGrab();
        break;
    case Player_Kill:
        PlayerStepKill(&damage, var_s6, var_s5);
        break;
    case Player_Unk17:
        PlayerStepUnk17();
        break;
    case Player_Teleport:
        PlayerStepTeleport();
        break;
    case Player_SpellDarkMetamorphosis:
        PlayerStepDarkMetamorphosis();
        break;
    case Player_SpellSummonSpirit:
        PlayerStepSummonSpells();
        break;
    case Player_SpellHellfire:
        PlayerStepHellfire();
        break;
    case Player_SpellTetraSpirit:
        PlayerStepSummonSpells();
        break;
    case Player_SpellSoulSteal:
        PlayerStepSoulSteal();
        break;
    case Player_SpellSwordBrothers:
        PlayerStepSummonSpells();
        break;
    case Player_Unk48:
        PlayerStepUnk48();
        break;
    case Player_Unk49:
        PlayerStepUnk49();
        break;
    case Player_Unk50:
        PlayerStepUnk50();
        break;
    case Player_KillWater:
        PlayerStepKillWater();
        break;
    case Player_AlucardStuck:
        PlayerStepStuck();
        break;
    case Player_AxearmorStand:
        weapon_func = D_8017A000.func_ptr_80170004;
        weapon_func();
        break;
    case Player_AxearmorWalk:
        weapon_func = D_8017A000.func_ptr_80170008;
        weapon_func();
        break;
    case Player_AxearmorJump:
        weapon_func = D_8017A000.func_ptr_8017000C;
        weapon_func();
        break;
    case Player_AxearmorHit:
        weapon_func = D_8017A000.func_ptr_80170010;
        weapon_func();
    }
    g_unkGraphicsStruct.unk1C &= ~2;
    g_Player.status &= ~PLAYER_STATUS_UNK8;
    g_Player.unk08 = g_Player.status;
    newStatus_s2 = 0;
    g_Status.D_80097BF8 &= ~1;
    switch (PLAYER.step) {
    case Player_Crouch:               
        if (PLAYER.step_s != 2) {
            newStatus_s2 = PLAYER_STATUS_CROUCH;
        }
        newStatus_s2 |= 0x10000000;
        break;
    case Player_Walk:
        newStatus_s2 = 0x04000000;
        /* fallthrough */
    case Player_Stand:
        newStatus_s2 |= 0x10000000;
        if (PLAYER.step_s == 4) {
            newStatus_s2 |= 0x08100000;
        }
        break;
    case Player_Fall:
    case Player_Jump:
        newStatus_s2 = 0x10002000;
        break;
    case Player_MorphBat:
        if (PLAYER.step_s == 3) {
            func_8010E168(1, 4);
            g_unkGraphicsStruct.unk1C |= 2;
        }
        newStatus_s2 = 0x28100001;
        break;
    case Player_MorphMist:
        func_8010E168(1, 4);
        newStatus_s2 = 0x28100002;
        PLAYER.palette = 0x810D;
        break;
    case Player_UnmorphMist:
        newStatus_s2 = 0x28900002;
        PLAYER.palette = 0x810D;
        func_8010E168(1, 4);
        break;
    case Player_AlucardStuck:
        func_8010E168(1, 4);
        newStatus_s2 = 0x18100010 | PLAYER_STATUS_CROUCH;
        break;
    case Player_UnmorphBat:
        newStatus_s2 = 0x28500001;
        if (PLAYER.step_s == 0) {
            PLAYER.animSet = 0xD;
            PLAYER.unk5A = 0;
        }
        func_8010E168(1, 4);
        break;
    case Player_HighJump:
        func_8010E168(1, 4);
        newStatus_s2 = 0x38000000;
        break;
    case Player_Hit:  
    case Player_Unk48:
    case Player_Unk49:
        newStatus_s2 = 0x38110000;
        func_8010E168(1, 12);
        break;
    case Player_StatusStone:
        newStatus_s2 = 0x38110080;
        break;
    case Player_BossGrab:
        newStatus_s2 = 0x38110040;
        func_8010E168(1, 12);
        break;
    case Player_Kill:
    case Player_KillWater:  
        newStatus_s2 = 0x18150000;
        if (PLAYER.step_s == 0x80) {
            newStatus_s2 |= PLAYER_STATUS_UNK80000;
        }
        func_8010E168(1, 12);
        break;
    case Player_Unk17:
        newStatus_s2 = 0x18150000;
        func_8010E168(1, 12);
        break;
    case Player_Teleport:
        newStatus_s2 = 0x18100000;
        func_8010E168(1, 12);
        break;
    case Player_SpellSummonSpirit: 
    case Player_SpellTetraSpirit:  
    case Player_SpellSwordBrothers:
        func_8010E168(1, 0x10);
        newStatus_s2 = 0x38000200 | PLAYER_STATUS_CROUCH;
        break;
    case Player_SpellSoulSteal:  
    case Player_SpellHellfire:         
    case Player_SpellDarkMetamorphosis:
        func_8010E168(1, 0x10);
        newStatus_s2 = 0x38000200;
        break;
    case Player_AxearmorHit:
        func_8010E168(1, 0x14);
        /* fallthrough */
    case Player_AxearmorStand:
    case Player_AxearmorWalk: 
    case Player_AxearmorJump: 
    case Player_Unk50:   
        newStatus_s2 = 0x29100000;
        PLAYER.unk5A = 0x64;
        break;
    case Player_SwordWarp:
        newStatus_s2 = 0x18100000;
        func_8010E168(4, 0xC);
        PLAYER.palette = 0x810D;
        break;
    case Player_MorphWolf:
        g_unkGraphicsStruct.unk1C |= 2;
        if (abs(PLAYER.velocityX) > FIX(3)) {
            func_8010E168(1, 4);
        }
        newStatus_s2 = 0x2C100204;
        if ((PLAYER.step_s == 0) || (PLAYER.step_s == 8)) {
            newStatus_s2 |= PLAYER_STATUS_UNK40000000;
        }
        if (PLAYER.step_s == 3) {
            newStatus_s2 |= PLAYER_STATUS_CROUCH;
        }
        break;
    case Player_UnmorphWolf:
        newStatus_s2 = 0x68100000;
        func_8010E168(1, 4);
        break;
    }
    if (g_Player.timers[9]) {
        newStatus_s2 |= 0x400;
    }
    if (g_Player.timers[10]) {
        newStatus_s2 |= 0x800;
    }
    if (g_Player.timers[12]) {
        newStatus_s2 |= 0x1000;
    }
    if (g_Player.timers[0]) {
        newStatus_s2 |= 0x28104000;
    }
    if (g_Player.timers[1]) {
        newStatus_s2 |= 0x28108000;
    }
    if (*D_80097448 != 0) {
        newStatus_s2 |= 0x08020000;
    }
    if (g_Player.timers[ALU_T_DARKMETAMORPH]) {
        newStatus_s2 |= 0x02000000;
    }
    g_Player.status = newStatus_s2;
    if ((newStatus_s2 & 0x08000000) || (g_unkGraphicsStruct.D_800973FC != 0)) {
        func_8010DFF0(1, 1);
    }
    if (newStatus_s2 & 0x10000000) {
        PLAYER.animSet = 1;
        PLAYER.unk5A = 0;
    }
    if (newStatus_s2 & 0x20000000) {
        g_Status.D_80097BF8 |= 1;
    }
    if (g_Player.timers[13] | g_Player.timers[14]) {
        g_Player.status |= PLAYER_STATUS_UNK100;
    }
    if ((g_Player.unk08 & 0x10000) &&
        !(g_Player.status & (PLAYER_STATUS_UNK10000 | PLAYER_STATUS_DEAD))) {
        func_8010E168(1, 0xC);
        if (!(g_Player.status & (PLAYER_STATUS_POISON | PLAYER_STATUS_CURSE))) {
            g_Player.timers[4] = 0xC;
            g_Player.timers[15] = 4;
            PLAYER.palette = 0x8100;
        }
    }
    PlayAnimation(D_800B0130, D_800B01B8);
    if (g_Player.status & PLAYER_STATUS_DEAD) {
        if (PLAYER.animFrameDuration < 0) {
            PLAYER.animCurFrame |= ANIM_FRAME_LOAD;
        }
        
        PLAYER.hitboxState = PLAYER.hitParams = 0;
    } else {
        PLAYER.hitboxState = 1;
        PLAYER.hitParams = 0;
        PLAYER.hitPoints = 0;
    }
    g_Player.unk14 = 0;
    g_Player.unk7A = 0;
    func_801093C4();
    if (!(g_Player.status & (PLAYER_STATUS_UNK10 | PLAYER_STATUS_UNK40))) {
        if ((CheckEquipmentItemCount(0x58U, 4U) != 0) &&
            !(g_Player.status & (PLAYER_STATUS_TRANSFORM | PLAYER_STATUS_UNK10 |
                                 PLAYER_STATUS_UNK10000 | PLAYER_STATUS_DEAD |
                                 PLAYER_STATUS_AXEARMOR)) &&
            !(PLAYER.drawFlags & (FLAG_DRAW_ROTY | FLAG_DRAW_ROTZ))) {
            PLAYER.drawFlags |= FLAG_DRAW_ROTY;
            PLAYER.rotY = 0x110;
            PLAYER.rotPivotY = 0x18;
        }
        func_8010D59C();
        if ((*D_80097448 >= 0x29 ||
             ((g_Player.status & PLAYER_STATUS_WOLF_FORM) &&
              *D_80097448 > 0xC)) &&
            (!g_CurrentEntity->nFramesInvincibility)) {
            PLAYER.velocityY = PLAYER.velocityY * 3 / 4;
            PLAYER.velocityX = PLAYER.velocityX * 3 / 4;
        }
        sp58 = PLAYER.posX.val;
        sp54 = PLAYER.posY.val;
        sp5c = g_Player.vram_flag;
        if (!(g_Player.status &
              (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_WOLF_FORM |
               PLAYER_STATUS_UNK400000 | PLAYER_STATUS_UNK40000000))) {
            if ((abs(PLAYER.velocityX) >= FIX(2)) || (PLAYER.step == 8)) {
                goto block_293;
            } else {
                goto oddblock;
            }
        } else {
        block_293:
            PLAYER.velocityX = PLAYER.velocityX >> 3;
            PLAYER.velocityY = PLAYER.velocityY >> 3;
            if (PLAYER.posY.i.hi >= 0) {
                if (g_Player.status &
                    (PLAYER_STATUS_UNK400000 | PLAYER_STATUS_UNK40000000)) {
                    CheckStageCollision(0);
                } else {
                    CheckStageCollision(1);
                }
            }
            for (i = 0; i < 7; i++) {
                if (PLAYER.posY.i.hi >= 0) {
                    CheckStageCollision(0);
                }
            }
            if (PLAYER.posY.i.hi < 0) {
                PLAYER.posY.val = FIX(-1);
            }
            PLAYER.velocityX *= 8;
            PLAYER.velocityY *= 8;
            goto post_oddblock;
        oddblock:
            if (g_Player.status & PLAYER_STATUS_UNK800000) {
                CheckStageCollision(0);
            } else {
                CheckStageCollision(1);
            }
        }
    post_oddblock:
        g_Player.unk04 = sp5c;
        if (((*D_80097448 >= 0x29) ||
             ((g_Player.status & PLAYER_STATUS_WOLF_FORM) &&
              (*D_80097448 > 0xC))) &&
            (!g_CurrentEntity->nFramesInvincibility)) {
            PLAYER.velocityY = PLAYER.velocityY * 4 / 3;
            PLAYER.velocityX = PLAYER.velocityX * 4 / 3;
        }
        g_CurrentEntity->nFramesInvincibility = 0;
        func_8010D800();
        if (PLAYER.animSet == 0xD) {
            sp3c = D_800CFE48[PLAYER.animCurFrame & 0x7FFF];
            sp3c->unk4 =
                D_8013AECC + D_800ACE20[PLAYER.animCurFrame];
        }
    }
}

