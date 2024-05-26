#include "dra.h"
#include "sfx.h"
#include "player.h"

void func_801092E8(s32 arg0) {
    D_800A37D8[0] = D_800ACE48[arg0 * 2];
    D_800A37D8[1] = D_800ACE48[arg0 * 2 + 1];
    D_8006EBE0 = D_800ACE48[arg0 * 2];
}

void func_80109328(void) {
    s16* player_unk1E = &PLAYER.rotZ;

    g_Player.unk66 = 0;
    if (*player_unk1E == 0x800 && PLAYER.step == 8) {
        PLAYER.rotZ = 0;
        PLAYER.animCurFrame = 0x9D;
        PLAYER.facingLeft = (PLAYER.facingLeft + 1) & 1;
    }

    if (g_Player.D_80072F00[11] != 0) {
        g_Player.D_80072F00[11] = 0;
        func_801092E8(0);
    }
    PLAYER.drawMode = DRAW_DEFAULT;
}

void func_801093C4(void) {
    DRAWENV drawEnv;
    Primitive* prim;
    s32 i;

    prim = &g_PrimBuf[g_Entities[1].primIndex];
    for (i = 0; i < 6; i++) {
        prim = prim->next;
    }
    switch (g_Player.unk6A) {
    case 0:
        if (func_800EDB08(prim) != 0) {
            prim->type = PRIM_ENV;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            func_800EDB08(prim);
            if (prim != NULL) {
                prim->type = PRIM_ENV;
                prim->drawMode = DRAW_HIDE;
                g_Player.unk6A++;
            }
        }
        break;
    case 1:
        if (g_Player.unk6A != 1) {
            return;
        }
        drawEnv = g_CurrentBuffer->draw;
        drawEnv.isbg = false;
        if (g_Player.unk0C & 0x04000000) {
            drawEnv.isbg = true;
        }
        drawEnv.r0 = drawEnv.g0 = drawEnv.b0 = 0;
        drawEnv.ofs[0] = 0x200;
        drawEnv.clip = D_800ACE60;
        drawEnv.ofs[1] = 0x1C0;
        SetDrawEnv(*(DR_ENV**)&prim->r1, &drawEnv);
        prim->priority = 0x190;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        prim->priority = 0x1B0;
        prim->drawMode = 0x800;
    }
}

// Duplicate of RIC func_80156F40
void func_80109594() {
    Entity* e;
    Primitive* prim;
    s32 radius;
    s32 intensity;
    s32 primIndex;
    s32 i;
    s32 val;
    s32 memset_len;
    s32* memset_ptr;
    s32 (*weapon)(void);

    g_Player.unk6A = 0;
    g_CurrentEntity = g_Entities;
    DestroyEntity(g_CurrentEntity);
    PLAYER.posX.val = 0x200000;
    PLAYER.posY.val = 0x200000;
    PLAYER.animSet = ANIMSET_DRA(1);
    PLAYER.palette = 0x8100;
    PLAYER.facingLeft = 0;
    PLAYER.rotX = 0x100;
    PLAYER.rotY = 0x100;
    PLAYER.zPriority = (u16)g_unkGraphicsStruct.g_zEntityCenter.S16.unk0;

    memset_len = sizeof(PlayerState) / sizeof(s32);
    memset_ptr = &g_Player;
    for (i = 0; i < memset_len; i++) {
        *memset_ptr++ = 0;
    }

    for (i = 0; i < 0x10; i++) {
        g_ButtonCombo[i].buttonsCorrect = 0;
        g_ButtonCombo[i].timer = 0;
    }

    g_Player.unk04 = 1;
    g_Player.pl_vram_flag = 1;
    func_8010E570(0);

    for (e = &g_Entities[1], i = 0; i < 3; i++, e++) {
        DestroyEntity(e);
        e->animSet = ANIMSET_DRA(1);
        e->unk5A = i + 1;
        e->palette = 0x8100;
        e->flags = FLAG_UNK_20000 | FLAG_UNK_08000000;
    }

    primIndex = AllocPrimitives(PRIM_TILE, 8);
    prim = &g_PrimBuf[primIndex];
    g_Entities[1].primIndex = primIndex;
    g_Entities[1].flags |= 0x800000;
    for (i = 0; i < 6; i++) {
        prim->drawMode = 0x10A;
        prim = prim->next;
    }
    func_801093C4();

#if defined(VERSION_US)
    g_Player.unk20[0] = 0x10;
    g_Player.D_80072EFC = 0x10;
    g_Player.padSim = 0;
    D_80137FB8 = 0;
    D_80137FBC = 1;
#elif defined(VERSION_HD)
    D_80137FB8 = 0;
#endif

    if (g_Status.mp != g_Status.mpMax) {
        D_80137FB4 = 0;
    } else {
        D_80137FB4 = 1;
    }
    g_PlayerDraw->enableColorBlend = 0;
    func_800EA5E4(0x16);
    func_801092E8(0);
    for (i = 0; i < 0x20; i++) {
        radius = (rand() & 0x3FF) + 0x100;
        intensity = (rand() & 0xFF) + 0x100;
        val = rcos(radius) * 0x10;
        D_801396F8[i] = +((val * intensity) >> 8);
        val = rsin(radius) * 0x10;
        D_80139778[i] = -((val * intensity) >> 7);
    }
    func_80111928();
    if (D_80097C98 == 6) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x100, 121), 0);
        func_8010E42C(1);
    }
    if (D_80097C98 == 4) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x300, 121), 0);
        func_8010E42C(3);
    }
    if (D_80097C98 == 5) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x500, 121), 0);
        func_8010E42C(5);
    }

    g_CurrentEntity = g_Entities;
    weapon = D_8017A000.GetWeaponId;
    if (weapon() != 0x2D) {
        return;
    }
    if (CheckEquipmentItemCount(ITEM_AXE_LORD_ARMOR, EQUIP_ARMOR) == 0) {
        return;
    }
    func_8010FAF4();

    weapon = D_8017A000.EntityWeaponAttack;
    weapon();
    g_Player.unk0C |= 0x01000000;
    func_8010DFF0(1, 10);
    func_80109328();
}

void func_80109990(void) {
    if (D_80137FB4 == 0) {
        if (g_Status.mp == g_Status.mpMax && !(g_Player.unk0C & 0x100000)) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 40), 0);
            PlaySfx(NA_SE_PL_MP_GAUGE);
            D_80137FB4++;
        }
    } else if (g_Status.mp != g_Status.mpMax) {
        D_80137FB4 = 0;
    }
}

void func_80109A44(s32 arg0);
INCLUDE_ASM("dra/nonmatchings/692E8", func_80109A44);

void func_8010A234(s32 arg0) {
    s32 (*weapon)(void);

    g_CurrentEntity = &PLAYER;
    weapon = D_8017A000.GetWeaponId;
    // Wearing Axe Lord Armor! This is probably when you initially put it on.
    if ((weapon() == 0x2D) &&
        CheckEquipmentItemCount(ITEM_AXE_LORD_ARMOR, EQUIP_ARMOR)) {
        if (!(g_Player.unk0C & 0x01000000)) {
            // Alucard says "WHAT?!" when first putting on Axe Lord Armor
            PlaySfx(NA_SE_VO_AL_WHAT);
            g_Player.padSim = 0;
            g_Player.D_80072EFC = 0x20;
            func_8010FAF4();
            weapon = D_8017A000.EntityWeaponAttack;
            weapon();
            g_Player.unk0C |= 0x01000000;
            func_8010DFF0(1, 0xA);
            func_80109328();
            if (arg0 != 0) {
                func_8010DBFC(D_800B0130, D_800B01B8);
            }
        }
    } else if (g_Player.unk0C & 0x01000000) {
        PLAYER.palette = 0x8100;
        PLAYER.animSet = 1;
        PLAYER.unk5A = 0;
        PLAYER.rotZ = 0;
        PLAYER.drawFlags &= 0xF3;
        func_8010FAF4();
        PLAYER.rotPivotY = 0;
        PLAYER.rotPivotX = 0;
        if (g_Player.pl_vram_flag & 1) {
            func_8010E570(0);
        } else {
            func_8010E7AC();
        }
        g_Player.unk0C &= ~0x01000000;
        func_80111CC0();
        if (arg0 != 0) {
            func_8010DBFC(D_800B0130, D_800B01B8);
        }
    }
}

void func_8010A3F0(void) {
    s32 temp = 0x38;

    if (D_8017A000.GetWeaponId() == temp && D_8017D000.GetWeaponId() == temp) {
        if (g_Player.D_80072F00[11] == 0) {
            func_801092E8(1);
        }
        g_Player.D_80072F00[11] = 0x20;
        temp = g_Player.unk10 != 0;
        if (temp && g_Status.D_80097C40 < -1) {
            g_Status.D_80097C40++;
        }
    }
    g_Player.unk10 = 0;
}

TeleportCheck GetTeleportToOtherCastle(void) {
    // Is player in the pose when pressing UP?
    if (PLAYER.step != 0 || PLAYER.step_s != 1) {
        return TELEPORT_CHECK_NONE;
    }

    // Check for X/Y boundaries in TOP
    if (g_StageId == STAGE_TOP) {
        if (abs(g_Tilemap.left * 256 + playerX - 8000) < 4 &&
            abs(g_Tilemap.top * 256 + playerY - 2127) < 4) {
            return TELEPORT_CHECK_TO_RTOP;
        }
    }

    // Check for X/Y boundaries in RTOP
    if (g_StageId == STAGE_RTOP) {
        if (abs(g_Tilemap.left * 256 + playerX - 8384) < 4 &&
#if defined(VERSION_US)
            abs(g_Tilemap.top * 256 + playerY - 14407) < 4) {
#elif defined(VERSION_HD)
            abs(g_Tilemap.top * 256 + playerY) - 14407 < 4) {
#endif
            return TELEPORT_CHECK_TO_TOP;
        }
    }

    return TELEPORT_CHECK_NONE;
}

void EntityAlucard(void) {
    DamageParam damage;
    s32 (*weapon_func)(void);
    s32 var_fp;
    PlayerDraw* draw;

    s32 temp_v0;
    u16 temp_v0_2;
    s32 temp_s1;
    s32 temp_a0;
    s32 temp_v1;
    s32 var_s0;
    u16 var_s6;
    u16 var_s7;

    g_CurrentEntity = &PLAYER;
    if (D_800ACE44 != 0) {
        D_800ACE44--;
    }
    if (D_800973FC != 0 && D_80137FB8 == 0) {
        CreateEntFactoryFromEntity(g_Entities, 0x78U, 0);
    }
    var_fp = 0;
    var_s6 = 0;
    g_Player.unk70 = g_Player.unk18 = PLAYER.drawFlags = g_Player.unk4C = 0;
    D_80137FB8 = D_800973FC;
    var_s7 = 0;
    g_Player.unk72 = func_80110394();
    if (!(g_Player.unk0C & 0x40000)) {
        var_s0 = GetTeleportToOtherCastle();
        if (var_s0 != 0) {
            func_8010E42C(var_s0);
        }
        if (PLAYER.step != 0x12) {
            func_8010A234(0);
            func_8010A3F0();
            func_80109990();
            if (g_Player.unk56 != 0) {
                g_Status.hp += g_Player.unk58;
                func_800FE8F0();
                func_80118C84(g_Player.unk58, 1);
                if (g_Player.unk56 == 1) {
                    PlaySfx(0x68E);
                    if (!(g_Player.unk0C & 0x80)) {
                        CreateEntFactoryFromEntity(
                            g_CurrentEntity, 0x48002CU, 0);
                        CreateEntFactoryFromEntity(
                            g_CurrentEntity, 0x44002CU, 0);
                    }
                }
                if ((g_Player.unk56 == 2) && !(g_Player.unk0C & 0x80)) {
                    CreateEntFactoryFromEntity(g_CurrentEntity, 0x48002CU, 0);
                }
                if (g_Status.hpMax < g_Status.hp) {
                    g_Status.hp = g_Status.hpMax;
                }
                g_Player.unk56 = 0;
            }
            var_s0 = CheckAndDoLevelUp();
            if (var_s0 != 0) {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, ((var_s0 - 1) << 0x10) | 0x19, 0);
            }
            for (var_s0 = 0; var_s0 < 16; var_s0++) {
                if (g_Player.D_80072F00[var_s0] != 0) {
                    switch (var_s0) {
                    case 2:
                        PLAYER.palette = g_Player.unk40;
                        break;
                    case 3:
                        PLAYER.palette = g_Player.pl_high_jump_timer;
                        g_Player.D_80072F00[15] = 12;
                        break;
                    case 4: {
                        s32 temp_s1 = ((g_GameTimer & 0xF) << 8);
                        draw = g_PlayerDraw;
                        draw->r0 = draw->b0 = draw->g0 =
                            (rsin((s16)temp_s1) + 0x1000) / 64 + 0x60;
                        draw->r1 = draw->b1 = draw->g1 =
                            (rsin(temp_s1 + 0x200) + 0x1000) / 64 + 0x60;
                        draw->r3 = draw->b3 = draw->g3 =
                            (rsin(temp_s1 + 0x400) + 0x1000) / 64 + 0x60;
                        draw->r2 = draw->b2 = draw->g2 =
                            (rsin(temp_s1 + 0x600) + 0x1000) / 64 + 0x60;
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
                    case 0:
                        break;
                    }
                    if (--g_Player.D_80072F00[var_s0] == 0) {
                        switch (var_s0) {
                        case 0:
                            if (!(g_Player.unk0C & 0x8080)) {
                                g_Player.D_80072F00[4] = 0xC;
                                g_Player.D_80072F00[15] = 0xC;
                                func_8010E168(1, 0xC);
                            }
                            continue;
                        case 1:
                            if (!(g_Player.unk0C & 0x8080)) {
                                g_Player.D_80072F00[4] = 0xC;
                                g_Player.D_80072F00[15] = 0xC;
                                func_8010E168(1, 0xC);
                            }
                            continue;
                        case 2:
                            PLAYER.palette = 0x8100;
                            continue;
                        case 3:
                            PLAYER.palette = 0x8100;
                            if (!(g_Player.unk0C & 0xC080)) {
                                g_Player.D_80072F00[4] = 0xC;
                                g_Player.D_80072F00[15] = 0xC;
                                func_8010E168(1, 0xC);
                            }
                            continue;
                        case 4:
                            draw->enableColorBlend = 0;
                            continue;
                        case 6:
                            if ((PLAYER.step == 3) &&
                                (PLAYER.ext.player.unkAC != 0x1C)) {
                                func_8010DA48(0x1C);
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
            if (g_Player.D_80072EFC != 0) {
                g_Player.D_80072EFC--;
#ifdef VERSION_US
                if (g_Player.D_80072EFC == 0) {
                    D_80137FBC = 1;
                }
#endif
                g_Player.padPressed = g_Player.padSim & 0xFFFF;
                switch (g_Player.padSim >> 0x10) { /* switch 6; irregular */
                case 1:                            /* switch 6 */
                    if (PLAYER.step != 0x30) {
                        func_8010E168(1, 4);
                        SetPlayerStep(0x30);
                        g_unkGraphicsStruct.unk0 = 1;
                    }
                    break;
                case 2: /* switch 6 */
                    func_8010E168(1, 4);
                    if (g_Player.unk0C & 0x01000000) {
                        SetPlayerStep(0x32);
                    } else {
                        SetPlayerStep(0x31);
                    }
                    g_unkGraphicsStruct.unk0 = 1;
                    break;
                }
            } else {
                g_Player.padPressed = g_pads->pressed;
                g_Player.padPressed = g_Player.padPressed & 0xFF00;
                for (var_s0 = 0; var_s0 < 8; var_s0++) {
                    if (g_pads->pressed & g_Settings.buttonMask[var_s0]) {
                        g_Player.padPressed |= D_800ACE00[var_s0];
                    }
                }
#ifdef VERSION_US
                if (D_80137FBC != 0) {
                    D_80137FBC = 0;
                    g_Player.padHeld = g_Player.padPressed;
                }
#endif
            }
            g_Player.padTapped =
                (g_Player.padHeld ^ g_Player.padPressed) & g_Player.padPressed;
            if (g_Player.unk0C & 8) {
                g_Player.padTapped &= ~(PAD_SQUARE | PAD_CIRCLE);
                g_Player.padPressed &= ~(PAD_SQUARE | PAD_CIRCLE);
            }
            if ((g_DebugPlayer != 0) && (func_801119C4() != 0)) {
#ifdef VERSION_US
                FntPrint("step:%04x\n", PLAYER.step);
                FntPrint("bat_i_step:%04x\n", g_Player.unk66);
#endif
                return;
            }
            if ((D_80097448[1] != 0) &&
                (IsRelicActive(RELIC_HOLY_SYMBOL) == 0) &&
                !(PLAYER.unk44 & 0x1F)) {
                PLAYER.unk44 = 6;
            }

// HD and US test this in slightly different places leading to this and the
// following ifdef.
#if defined(VERSION_HD)
            if ((g_Player.D_80072F00[13] | g_Player.D_80072F00[14]) != 0) {
                goto specialmove;
            }
#endif
            if (g_Player.unk60 < 2) {
                if (g_Player.unk60 == 1) {
                    var_s6 = PLAYER.step;
                    var_s7 = PLAYER.step_s;
                    SetPlayerStep(Player_BossGrab);
                } else {
#if defined(VERSION_US)
                    if ((g_Player.D_80072F00[13] | g_Player.D_80072F00[14]) ==
                        0) {
#elif defined(VERSION_HD)
                    if (1) { // to make curly braces match
#endif
                        if (PLAYER.unk44) {
                            var_s6 = PLAYER.step;
                            var_s7 = PLAYER.step_s;
                            var_s0 = HandleDamage(
                                &damage, PLAYER.unk44, PLAYER.hitPoints, 0);
                            if ((g_Player.unk0C & 0x01000000) &&
                                ((var_s0 == 1) || (var_s0 == 7) ||
                                 (var_s0 == 8))) {
                                var_s0 = 3;
                                damage.damageKind = 1;
                            }
                            switch (var_s0) {
                            case 0:
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, 0x2FU, 0);
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, 0x43002CU, 0);
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, 0x51002CU, 0);
                                func_80118C84(0, 0);
                                func_8010E168(1, 0xC);
                                break;
                            case 1:
                                g_Player.pl_high_jump_timer = 0x8166;
                                g_Player.unk18 = damage.effects;
                                func_8010E168(1, 0xC);
                                g_Player.D_80072F00[3] = 6;
                                PlaySfx(0x6E7);
                                func_80118C84(1, 0);
                                break;
                            case 2:
                                g_Player.unk18 = damage.effects;
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, 0x73U, 0);
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, 0x58002CU, 0);
                                g_Player.pl_high_jump_timer = 0x8166;
                                func_8010E168(1, 0xC);
                                g_Player.D_80072F00[3] = 6;
                                break;
                            case 3:
                                g_Player.unk18 = damage.effects;
                                SetPlayerStep(Player_Hit);
                                func_80118C84(damage.damageTaken, 0);
                                break;
                            case 4:
                                func_80118C84(damage.damageTaken, 0);
                                SetPlayerStep(Player_Kill);
                                break;
                            case 5:
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, 0x44002CU, 0);
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, 0x48002CU, 0);
                                func_80118C84(damage.unkC, 1);
                                func_8010E168(1, 0xC);
                                break;
                            case 6:
                                SetPlayerStep(Player_KillWater);
                                break;
                            case 7:
                                g_Player.unk18 = damage.effects;
                                SetPlayerStep(Player_StatusStone);
                                func_80118C84(damage.damageTaken, 0);
                                break;
                            case 8:
                                g_Player.unk18 = damage.effects;
                                func_80118C84(damage.damageTaken, 0);
                                var_fp = 1;
                                break;
                            case 9:
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, 0x4E002CU, 0);
                                if (D_800ACDFC == 0) {
                                    PlaySfx(0x6EB);
                                }
                                D_800ACDFC = 0x20;
                                if (damage.damageTaken != 0) {
                                    PlaySfx(0x6A3);
                                }
                                break;
                            }
                        }
                    }
                specialmove:
                    CheckSpecialMoveInputs();
#if defined(VERSION_US)
                    if (g_Player.unk20[0] == 0 || --g_Player.unk20[0] == 0) {
#elif defined(VERSION_HD)
                    if (D_800ACEDC_hd == 0 || --D_800ACEDC_hd == 0) {
#endif
                        if (D_80097448[1] == 0) {
                            if ((g_Player.padTapped & PAD_L1) &&
                                (HandleTransformationMP(
                                     FORM_MIST, CHECK_ONLY) == 0) &&
                                ((PLAYER.step == 0) || (PLAYER.step == 1) ||
                                 (PLAYER.step == 2) || (PLAYER.step == 3) ||
                                 (PLAYER.step == 4) || (PLAYER.step == 6) ||
                                 (PLAYER.step == 8) ||
                                 ((PLAYER.step == 5) && (PLAYER.step_s != 0)) ||
                                 ((PLAYER.step == 0x18) &&
                                  (PLAYER.step_s != 0) &&
                                  (PLAYER.step_s != 8)))) {
                                func_80109328();
                                SetPlayerStep(Player_MorphMist);
                                PlaySfx(0x6A0);
                                goto block_159;
                            }
                            if ((g_Player.padTapped & PAD_R1) &&
                                (HandleTransformationMP(FORM_BAT, CHECK_ONLY) ==
                                 0)) {
                                if (PLAYER.step == 0 || (PLAYER.step == 1) ||
                                    (PLAYER.step == 2) || (PLAYER.step == 3) ||
                                    (PLAYER.step == 4) || (PLAYER.step == 6)) {
                                    goto block_62check;
                                }
                                if ((PLAYER.step == 7) || (PLAYER.step == 8) ||
                                    (PLAYER.step == 24 &&
                                     (PLAYER.step_s != 0 &&
                                      PLAYER.step_s != 8))) {
                                block_62check:
                                    if (PLAYER.step == 6 || PLAYER.step == 2) {
                                        D_8013AECC = 0xC;
                                    }
                                    func_80109328();
                                    SetPlayerStep(Player_MorphBat);
                                    PlaySfx(0x6A0);
                                    goto block_160;
                                }
                            }
                        }
                        if ((g_Player.padTapped & PAD_R2) &&
                            (HandleTransformationMP(FORM_WOLF, CHECK_ONLY) ==
                             0) &&
                            ((D_80097448[1] == 0) ||
                             IsRelicActive(RELIC_HOLY_SYMBOL)) &&
                            (PLAYER.step == 0 || (PLAYER.step == 1) ||
                             (PLAYER.step == 2) || (PLAYER.step == 3) ||
                             (PLAYER.step == 4) || (PLAYER.step == 6) ||
                             ((PLAYER.step == 7) || (PLAYER.step == 8)) ||
                             ((PLAYER.step == 5) && (PLAYER.step_s != 0)))) {
                            func_80109328();
                            SetPlayerStep(0x18);
                            PlaySfx(0x668);
                        }
                    }
                }
            }
        }
    }
block_159:
block_160:
    g_Player.unk50 = PLAYER.step;
    g_Player.unk52 = PLAYER.step_s;
    D_800ACDF8 = (s32)g_Player.D_80072F00[11];
    switch (PLAYER.step) {
    case Player_Stand:
        func_801120B4();
        break;
    case Player_Walk:
        func_80112B64();
        break;
    case Player_Crouch:
        func_801131C4();
        break;
    case Player_Fall:
        func_80113148();
        break;
    case Player_Jump:
        func_80112BB0();
        break;
    case Player_MorphBat:
        ControlBatForm();
        break;
    case Player_UnmorphBat:
        func_801177A0();
        break;
    case Player_MorphMist:
        ControlMistForm();
        break;
    case Player_UnmorphMist:
        func_801182F8();
        break;
    case Player_MorphWolf:
        func_8012EF2C();
        break;
    case Player_UnmorphWolf:
        func_8012EAD0();
        break;
    case Player_HighJump:
        func_80113AAC();
        break;
    case Player_SwordWarp:
        func_801186EC();
        break;
    case Player_Hit:
        AlucardHandleDamage(&damage, (s16)var_s6, (s16)var_s7);
        break;
    case Player_StatusStone:
        func_80114DF4(var_fp);
        break;
    case Player_BossGrab:
        func_80116208();
        break;
    case Player_Kill:
        func_80115394(&damage, (s16)var_s6, (s16)var_s7);
        break;
    case Player_Unk17:
        func_80115BB0();
        break;
    case Player_Teleport:
        func_80115DA0();
        break;
    case Player_SpellDarkMetamorphosis:
        func_80118614();
        break;
    case Player_SpellHellfire:
        PlayerStepHellfire();
        break;
    case Player_SpellSoulSteal:
        func_80118670();
        break;
    case Player_SpellSummonSpirit:
    case Player_SpellTetraSpirit:
    case Player_SpellSwordBrothers:
        func_80118640();
        break;
    case Player_Unk48:
        func_801166A4();
        break;
    case Player_Unk49:
        func_8011678C();
        break;
    case Player_Unk50:
        func_801167D0();
        break;
    case Player_KillWater:
        func_80115F54();
        break;
    case Player_AlucardStuck:
        func_80117AC0();
        break;
    case Player_AxearmorStand:
        weapon_func = D_8017A000.func_ptr_80170004;
        goto runweapon;
    case Player_AxearmorWalk:
        weapon_func = D_8017A000.func_ptr_80170008;
        goto runweapon;
    case Player_AxearmorJump:
        weapon_func = D_8017A000.func_ptr_8017000C;
        goto runweapon;
    case Player_AxearmorHit:
        weapon_func = D_8017A000.func_ptr_80170010;
    runweapon:
        weapon_func();
    }
    var_s0 = 0;
    g_unkGraphicsStruct.unk1C &= ~2;
    g_Player.unk0C &= ~8;
    g_Player.unk08 = g_Player.unk0C;
    g_Status.D_80097BF8 &= ~1;
    switch (PLAYER.step) { /* switch 5 */
    case 2:                /* switch 5 */
        if (PLAYER.step_s != 2) {
            var_s0 = 0x20;
        }
        var_s0 |= 0x10000000;
        break;
    case 1: /* switch 5 */
        var_s0 = 0x04000000;
        /* fallthrough */
    case 0: /* switch 5 */
        var_s0 |= 0x10000000;
        if (PLAYER.step_s == 4) {
            var_s0 |= 0x08100000;
        }
        break;
    case 3: /* switch 5 */
    case 4: /* switch 5 */
        var_s0 = 0x10002000;
        break;
    case 5: /* switch 5 */
        if (PLAYER.step_s == 3) {
            func_8010E168(1, 4);
            g_unkGraphicsStruct.unk1C |= 2;
        }
        var_s0 = 0x28100001;
        break;
    case 7: /* switch 5 */
        func_8010E168(1, 4);
        var_s0 = 0x28100002;
        PLAYER.palette = 0x810D;
        break;
    case 14:
        var_s0 = 0x28900002;
        PLAYER.palette = 0x810D;
        func_8010E168(1, 4);
        break;
    case 6: /* switch 5 */
        func_8010E168(1, 4);
        var_s0 = 0x18100030;
        break;
    case 9: /* switch 5 */
        var_s0 = 0x28500001;
        if (PLAYER.step_s == 0) {
            PLAYER.animSet = 0xD;
            PLAYER.unk5A = 0;
        }
        func_8010E168(1, 4);
        break;
    case 8: /* switch 5 */
        func_8010E168(1, 4);
        var_s0 = 0x38000000;
        break;
    case 10: /* switch 5 */
    case 48: /* switch 5 */
    case 49: /* switch 5 */
        var_s0 = 0x38110000;
        func_8010E168(1, 12);
        break;
    case 11: /* switch 5 */
        var_s0 = 0x38110080;
        break;
    case 12: /* switch 5 */
        var_s0 = 0x38110040;
        func_8010E168(1, 12);
        break;
    case 13: /* switch 5 */
    case 16: /* switch 5 */
        var_s0 = 0x18150000;
        if (PLAYER.step_s == 0x80) {
            var_s0 = 0x181D0000;
        }
        func_8010E168(1, 12);
        break;
    case 17: /* switch 5 */
        var_s0 = 0x18150000;
        func_8010E168(1, 12);
        break;
    case 18: /* switch 5 */
        var_s0 = 0x18100000;
        func_8010E168(1, 12);
        break;
    case 33: /* switch 5 */
    case 35: /* switch 5 */
    case 39: /* switch 5 */
        func_8010E168(1, 0x10);
        var_s0 = 0x38000220;
        break;
    case 32: /* switch 5 */
    case 34: /* switch 5 */
    case 37: /* switch 5 */
        func_8010E168(1, 0x10);
        var_s0 = 0x38000200;
        break;
    case 43: /* switch 5 */
        func_8010E168(1, 0x14);
        /* fallthrough */
    case 40: /* switch 5 */
    case 41: /* switch 5 */
    case 42: /* switch 5 */
    case 50: /* switch 5 */
        PLAYER.unk5A = 0x64;
        var_s0 = 0x29100000;
        break;
    case 15: /* switch 5 */
        var_s0 = 0x18100000;
        func_8010E168(4, 0xC);
        PLAYER.palette = 0x810D;
        break;
    case 24: /* switch 5 */
        g_unkGraphicsStruct.unk1C |= 2;
        if (abs(PLAYER.velocityX) > FIX(3)) {
            func_8010E168(1, 4);
        }
        var_s0 = 0x2C100204;
        if ((PLAYER.step_s == 0) || (PLAYER.step_s == 8)) {
            var_s0 = 0x6C100204;
        }
        if (PLAYER.step_s == 3) {
            var_s0 |= 0x20;
        }
        break;
    case 25: /* switch 5 */
        var_s0 = 0x68100000;
        func_8010E168(1, 4);
        break;
    }
    if (g_Player.D_80072F00[9] != 0) {
        var_s0 |= 0x400;
    }
    if (g_Player.D_80072F00[10] != 0) {
        var_s0 |= 0x800;
    }
    if (g_Player.D_80072F00[12] != 0) {
        var_s0 |= 0x1000;
    }
    if (g_Player.D_80072F00[0] != 0) {
        var_s0 |= 0x28104000;
    }
    if (g_Player.D_80072F00[1] != 0) {
        var_s0 |= 0x28108000;
    }
    if (*D_80097448 != 0) {
        var_s0 |= 0x08020000;
    }
    if (g_Player.D_80072F00[11] != 0) {
        var_s0 |= 0x02000000;
    }
    g_Player.unk0C = var_s0;
    if ((var_s0 & 0x08000000) || (D_800973FC != 0)) {
        func_8010DFF0(1, 1);
    }
    if (var_s0 & 0x10000000) {
        PLAYER.animSet = 1;
        PLAYER.unk5A = 0;
    }
    if (var_s0 & 0x20000000) {
        g_Status.D_80097BF8 |= 1;
    }
    if ((g_Player.D_80072F00[13] | g_Player.D_80072F00[14]) != 0) {
        g_Player.unk0C |= 0x100;
    }
    if ((g_Player.unk08 & 0x10000) && !(g_Player.unk0C & 0x50000)) {
        func_8010E168(1, 0xC);
        if (!(g_Player.unk0C & 0xC000)) {
            g_Player.D_80072F00[4] = 0xC;
            g_Player.D_80072F00[15] = 4;
            PLAYER.palette = 0x8100;
        }
    }
    func_8010DBFC(D_800B0130, D_800B01B8);
    if (g_Player.unk0C & 0x40000) {
        if (PLAYER.animFrameDuration < 0) {
            PLAYER.animCurFrame |= 0x8000;
        }
        PLAYER.unk44 = 0;
        PLAYER.hitboxState = 0;
    } else {
        PLAYER.hitboxState = 1;
        PLAYER.unk44 = 0;
        PLAYER.hitPoints = 0;
    }
    g_Player.unk14 = 0;
    g_Player.unk7A = 0;
    func_801093C4();
    if (!(g_Player.unk0C & 0x50)) {
        if ((CheckEquipmentItemCount(0x58U, 4U) != 0) &&
            !(g_Player.unk0C & 0x01050017) && !(PLAYER.drawFlags & 6)) {
            PLAYER.drawFlags |= 2;
            PLAYER.rotY = 0x110;
            PLAYER.rotPivotY = 0x18;
        }
        func_8010D59C();
        if ((*D_80097448 >= 0x29 ||
             ((g_Player.unk0C & 4) && *D_80097448 >= 0xD)) &&
            (g_CurrentEntity->nFramesInvincibility == 0)) {
            PLAYER.velocityY = PLAYER.velocityY * 3 / 4;
            PLAYER.velocityX = PLAYER.velocityX * 3 / 4;
        }
        temp_s1 = g_Player.pl_vram_flag;
        if (!(g_Player.unk0C & (0x40400000 | 5))) {
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
                if (g_Player.unk0C & 0x40400000) {
                    func_80109A44(0);
                } else {
                    func_80109A44(1);
                }
            }
            for (var_s0 = 0; var_s0 < 7; var_s0++) {
                if (PLAYER.posY.i.hi >= 0) {
                    func_80109A44(0);
                }
            }
            if (PLAYER.posY.i.hi < 0) {
                PLAYER.posY.val = FIX(-1);
            }
            PLAYER.velocityX *= 8;
            PLAYER.velocityY *= 8;
            goto post_oddblock;
        oddblock:
            if (g_Player.unk0C & 0x800000) {
                func_80109A44(0);
            } else {
                func_80109A44(1);
            }
        }
    post_oddblock:
        g_Player.unk04 = temp_s1;
        if (((*D_80097448 >= 0x29) ||
             ((g_Player.unk0C & 4) && (*D_80097448 >= 0xD))) &&
            (g_CurrentEntity->nFramesInvincibility == 0)) {
            PLAYER.velocityY = PLAYER.velocityY * 4 / 3;
            PLAYER.velocityX = PLAYER.velocityX * 4 / 3;
        }
        g_CurrentEntity->nFramesInvincibility = 0;
        func_8010D800();
        if (PLAYER.animSet == 0xD) {
            D_800CFE48[PLAYER.animCurFrame & 0x7FFF]->unk4 =
                D_8013AECC + D_800ACE20[PLAYER.animCurFrame];
        }
#ifdef VERSION_US
        FntPrint("step:%04x\n", PLAYER.step);
        FntPrint("bat_i_step:%04x\n", g_Player.unk66);
#endif
    }
}

void func_8010BF64(Unkstruct_8010BF64* arg0) {
    if (g_PlayableCharacter == PLAYER_ALUCARD) {
        u32 unk0C_var = (g_Player.unk0C / 2) & 2;
        arg0->unk14 = D_800ACED0.pairs[4].unk0 - unk0C_var;
        arg0->unk1C = D_800ACED0.pairs[4].unk2 + unk0C_var;
        arg0->unk18 = D_800ACED0.pairs[1].unk2 - 1;
        arg0->unk20 = D_800ACEC0[1].unk2 + 1;
    } else {
        g_PlOvl.D_8013C00C();
    }
}

void func_8010BFFC(void) {
    s16 x;
    s16 y;
    s32 i;
    bool collided = false;
    u16 original_Y = PLAYER.posY.i.hi;

    if ((g_Player.pl_vram_flag & 1) || (D_801396EA != 0) ||
#if defined(VERSION_US)
        (g_Player.unk0C & 0x40000007) ||
        ((g_PlayableCharacter != 0) && (PLAYER.step == 0x18)) ||
#elif defined(VERSION_HD)
        (g_Player.unk0C & PLAYER_STATUS_TRANSFORM) ||
#endif
        (g_Player.unk78 == 1)) {
        return;
    }
    if (PLAYER.posY.i.hi < 48) {
        PLAYER.posY.i.hi -= 16;
        while (true) {
            for (i = 0; i < 4; i++) {
                x = PLAYER.posX.i.hi + D_800ACED0.pairs[i].unk0;
                y = PLAYER.posY.i.hi + D_800ACED0.pairs[i].unk2;
                CheckCollision(x, y, &g_Player.colliders[i], 0);
            }
            if ((g_Player.colliders[1].effects &
                 (EFFECT_SOLID_FROM_BELOW + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colliders[2].effects &
                 (EFFECT_SOLID_FROM_BELOW + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colliders[3].effects &
                 (EFFECT_SOLID_FROM_BELOW + EFFECT_SOLID)) == EFFECT_SOLID) {
                // I don't know man
                (*(&PLAYER)).posY.i.hi--;
                PLAYER.velocityY = 0;
                collided = true;
                continue;
            }
            if (collided) {
                return;
            }
            PLAYER.posY.i.hi += 8;
            if (PLAYER.posY.i.hi >= 48) {
                PLAYER.posY.i.hi = original_Y;
                return;
            }
        }
    } else if (PLAYER.posY.i.hi > 176) {
        PLAYER.posY.i.hi += 32;
        while (true) {
            for (i = 0; i < 4; i++) {
                x = PLAYER.posX.i.hi + D_800ACEC0[i].unk0;
                y = PLAYER.posY.i.hi + D_800ACEC0[i].unk2;
#if defined(VERSION_US)
                if (g_PlayableCharacter != PLAYER_ALUCARD) {
                    y += 6;
                }
#endif
                CheckCollision(x, y, &g_Player.colliders[4 + i], 0);
            }
            if ((g_Player.colliders[5].effects &
                 (EFFECT_SOLID_FROM_ABOVE + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colliders[6].effects &
                 (EFFECT_SOLID_FROM_ABOVE + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colliders[7].effects &
                 (EFFECT_SOLID_FROM_ABOVE + EFFECT_SOLID)) == EFFECT_SOLID) {
                // I don't know man
                (*(&PLAYER)).posY.i.hi++;
                PLAYER.velocityY = 0;
                collided = true;
                continue;
            }
            if (collided) {
                PLAYER.posY.i.hi--;
                return;
            }
            PLAYER.posY.i.hi -= 8;
            if (PLAYER.posY.i.hi <= 176) {
                PLAYER.posY.i.hi = original_Y;
                return;
            }
        }
    }
}

INCLUDE_ASM("dra/nonmatchings/692E8", func_8010C36C);

INCLUDE_ASM("dra/nonmatchings/692E8", func_8010C9F4);

INCLUDE_ASM("dra/nonmatchings/692E8", func_8010D010);

INCLUDE_ASM("dra/nonmatchings/692E8", func_8010D2C8);

void SetPlayerStep(PlayerSteps step) {
    PLAYER.step = step;
    PLAYER.step_s = 0;
}
