#include "ric.h"

s32 func_8015D250(s32 unused_arg) {
    SubweaponDef subweapon;
    s16 subweaponId;

    if (!(g_Player.padPressed & PAD_UP)) {
        return 1;
    }

    subweaponId = func_8015FB84(&subweapon, 0, 0);
    if (subweaponId <= 0) {
        return 1;
    }
    if (subweapon.blueprintNum == 0) {
        return 4;
    }
    if (func_8015D1D0(subweaponId, subweapon.unk6) < 0) {
        return 2;
    }
    if ((s16)func_8015FB84(&subweapon, 0, 1) <= 0) {
        return 3;
    }
    if (g_Player.unk72 != 0) {
        return 5;
    }

    CreateEntFactoryFromEntity(g_CurrentEntity, subweapon.blueprintNum, 0);
    g_Player.D_80072F00[10] = 4;

    switch (PLAYER.step) {
    case 25:
        PLAYER.step = 0;
        CreateEntFactoryFromEntity(g_CurrentEntity, 0x0, 0);
        func_8015C920(D_801555E8);
        break;

    case 0:
    case 1:
    case 2:
        PLAYER.step = 0;
        func_8015C920(D_801555E8);
        break;

    case 3:
    case 4:
        PLAYER.step = 4;
        func_8015C920(D_80155638);
        break;
    }
    g_Player.unk46 = 3;
    PLAYER.step_s = 0x42;
    g_Player.D_80072F00[10] = 4;
    return 0;
}

bool func_8015D3CC(void) {
    s32 i;
    s16 poisoned;
    s32 temp_rand = rand();
    s16 randOf6 = temp_rand % 6;

    if (func_8015D250(temp_rand / 6) == 0) {
        if (randOf6 == 0) {
            g_api.PlaySfx(0x6F9);
        }
        if (randOf6 == 1) {
            g_api.PlaySfx(0x6FA);
        }
        if (randOf6 == 2) {
            g_api.PlaySfx(0x6FB);
        }
        return 1;
    }
    poisoned = g_Player.D_80072F00[0] != 0;
    for (i = 16; i < 31; i++) {
        DestroyEntity(&g_Entities[i]);
    }
    if (CreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(poisoned * 0x100, 10), 0) != NULL) {
        if (poisoned) {
            g_api.PlaySfx(0x6B5);
        } else {
            g_api.PlaySfx(0x706);
        }
        if (randOf6 == 0) {
            g_api.PlaySfx(0x6F9);
        }
        if (randOf6 == 1) {
            g_api.PlaySfx(0x6FA);
        }
        if (randOf6 == 2) {
            g_api.PlaySfx(0x6FB);
        }
        switch (PLAYER.step) {
        default:
            return 0;
        case Player_Stand:
        case Player_Walk:
            PLAYER.step = 0;
            func_8015C920(D_80155588);
            g_CurrentEntity->velocityX = 0;
            break;
        case Player_Unk25:
            PLAYER.step = 0;
            func_8015C920(D_80155588);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
            break;
        case Player_Crouch:
            func_8015C920(D_801555A8);
            g_CurrentEntity->velocityX = 0;
            break;
        case Player_Fall:
        case Player_Jump:
            PLAYER.step = 4;
            func_8015C920(D_801555C8);
            break;
        }
        g_Player.unk46 = 1;
        PLAYER.step_s = 0x40;
        g_Player.D_80072F00[9] = 4;
        return 1;
    }
    return 0;
}

bool func_8015D678(void) {
    SubweaponDef subWpn;
    Entity* subWpnEnt;
    s16 subWpnID;

    subWpnID = func_8015FB84(&subWpn, true, false);
    if (subWpnID < 0) {
        return 0;
    }
    if ((subWpnID == 3) && (g_Player.D_80072F00[3] != 0)) {
        return 0;
    }
    if ((subWpnID == 6) && (D_800973FC != 0)) {
        return 0;
    }
    if (subWpn.blueprintNum != 0) {
        if (subWpnID == 1) {
            subWpnEnt = CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x100, subWpn.blueprintNum), 0);
        } else {
            subWpnEnt = CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0, subWpn.blueprintNum), 0);
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
        SetPlayerStep(Player_FlameWhip);
        func_8015C920(D_80155840);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x100, 36), 0);
        g_api.PlaySfx(0x6FC);
        break;
    case SUBWPN_DAGGER:
        SetPlayerStep(Player_ThousandBlades);
        func_8015C920(D_80155608);
        g_api.PlaySfx(0x6FC);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x200, 33), 0);
        break;
    case SUBWPN_AXE:
        SetPlayerStep(Player_Teleport);
        func_8015C920(D_80155658);
        PLAYER.velocityY = FIX(-4.6875);
        if (g_Player.unk72 != 0) {
            PLAYER.velocityY = 0;
        }
        func_8015CC28();
        g_api.PlaySfx(0x6FC);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x200, 33), 0);
        break;
    case SUBWPN_HOLYWATER:
        SetPlayerStep(Player_Hydrostorm);
        func_8015C920(D_801557AC);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x4000, 33), 0);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x4700, 33), 0);
        g_api.PlaySfx(0x700);
        break;
    case SUBWPN_REBNDSTONE:
    case SUBWPN_VIBHUTI:
    case SUBWPN_AGUNEA:
        SetPlayerStep(Player_Unk27);
        func_8015C920(D_801557AC);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x4000, 33), 0);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x4700, 33), 0);
        g_api.PlaySfx(0x6FC);
        break;
    case SUBWPN_BIBLE:
    case SUBWPN_STOPWATCH:
        SetPlayerStep(Player_Unk27);
        func_8015C920(D_801558E4);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x4000, 33), 0);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x4700, 33), 0);
        g_api.PlaySfx(0x6FC);
        break;
    case SUBWPN_CROSS:
        SetPlayerStep(Player_Teleport);
        func_8015C920(D_80155658);
        PLAYER.velocityY = FIX(-4.6875);
        if (g_Player.unk72 != 0) {
            PLAYER.velocityY = 0;
        }
        func_8015CC28();
        g_api.PlaySfx(0x701);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x200, 33), 0);
        break;
    }
    g_Player.D_80072F00[12] = 4;
    return 1;
}

void func_8015D9B4() { SetPlayerStep(22); }

void func_8015D9D4(void) {
    func_8015C9CC();
    SetPlayerStep(0x17);
    func_8015C920(&D_80155750);
    g_CurrentEntity->velocityY = 0;
    SetSpeedX(0x58000);
    func_8015CC28();
    CreateEntFactoryFromEntity(g_CurrentEntity, 0x19, 0);
    g_api.PlaySfx(0x707);
    g_Player.D_80072F00[12] = 4;
}

void func_8015DA60(void) {
    g_Player.unk44 = 0;
    SetPlayerStep(0x1A);
    func_8015C920(&D_8015577C);
    g_CurrentEntity->velocityY = FIX(-2);
    SetSpeedX(0x58000);
    func_8015CC28();
    CreateEntFactoryFromEntity(g_CurrentEntity, 0x19, 0);
    g_api.PlaySfx(0x6FA);
    g_Player.D_80072F00[12] = 4;
    CreateEntFactoryFromEntity(g_CurrentEntity, 0x1F, 0);
}

void DoBladeDash(void) {
    SetPlayerStep(0x18);
    func_8015C920(&D_801557D8);
    g_CurrentEntity->velocityY = 0;
    SetSpeedX(FIX(5.5));
    g_Player.unk46 = 5;
    g_Player.D_80072F00[12] = 4;
    CreateEntFactoryFromEntity(g_CurrentEntity, 0x1A, 0);
    func_8015CC28();
    g_api.PlaySfx(0x6FB);
    g_api.PlaySfx(0x707);
}

bool func_8015DBB0(s32 arg_flags) {
    s32 velYChange;
    u32 effects;

    if (arg_flags & 8) {
        if (g_Player.unk46 == 0) {
            func_8015C9CC();
        }
    }
    velYChange = (arg_flags & 0x8000) ? FIX(28.0 / 128) : 0;
    if (arg_flags & 0x10000) {
        if (FIX(-1.0 / 8) < PLAYER.velocityY &&
            PLAYER.velocityY < FIX(3.0 / 8) && !(g_Player.unk44 & 0x20) &&
            (g_Player.padPressed & PAD_CROSS)) {
            // Note that 5.6 is precisely 1/5 of 28.
            velYChange = FIX(5.6 / 128);
        } else {
            velYChange = FIX(28.0 / 128);
        }
    }
    if (arg_flags & 0x200) {
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
    if ((arg_flags & 0x80) && (g_Player.pl_vram_flag & 2) &&
        (PLAYER.velocityY < FIX(-1))) {
        PLAYER.velocityY = FIX(-1);
    }
    if (PLAYER.velocityY >= 0) {
        if ((arg_flags & 1) && (g_Player.pl_vram_flag & 1)) {
            switch (g_Player.unk46) {
            case 0:
            default:
                if (g_Player.unk44 & 8) {
                    func_8015CCC8(3, PLAYER.velocityX);
                    g_api.PlaySfx(0x64B);
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 0), 0);
                    return true;
                }
                if (PLAYER.velocityY > 0x6E000) {
                    func_8015CCC8(1, 0);
                    g_api.PlaySfx(0x64B);
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 0), 0);
                } else if (g_Player.padPressed & (PAD_LEFT | PAD_RIGHT)) {
                    if ((g_Player.unk44 & 0x10) && (g_Player.unk7A == 0)) {
                        func_8015CE7C();
                    } else {
                        func_8015CDE0(0);
                    }
                } else {
                    func_8015CD98(0);
                }
                return true;
            case 1: /* switch 1 */
                if (PLAYER.velocityY > 0x6E000) {
                    PLAYER.step = 2;
                    PLAYER.unk4C = D_801555A8;
                    g_api.PlaySfx(0x647);
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 0), 0);
                } else {
                    PLAYER.step = 0;
                    PLAYER.unk4C = D_80155588;
                    if (g_Player.unk44 & 8) {
                        CreateEntFactoryFromEntity(
                            g_CurrentEntity, FACTORY(0, 0), 0);
                        g_api.PlaySfx(0x647);
                    } else {
                        PLAYER.velocityX = 0;
                    }
                }
                PLAYER.velocityY = 0;
                g_Player.unk44 = 0;
                return true;
            case 2: /* switch 1 */
                if (PLAYER.velocityY > 0x6E000) {
                    PLAYER.step = 2;
                    PLAYER.unk4C = D_80155738;
                    g_api.PlaySfx(0x64B);
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 0), 0);
                } else {
                    PLAYER.step = 0;
                    PLAYER.unk4C = D_80155730;
                    if (!(g_Player.unk44 & 8)) {
                        PLAYER.velocityX = 0;
                    } else {
                        CreateEntFactoryFromEntity(
                            g_CurrentEntity, FACTORY(0, 0), 0);
                        g_api.PlaySfx(0x64B);
                    }
                }
                PLAYER.velocityY = 0;
                g_Player.unk44 = 0;
                return true;
            case 3: /* switch 1 */
                if ((PLAYER.velocityY > 0x6E000) || (g_Player.unk44 & 8)) {
                    g_api.PlaySfx(0x64B);
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 0), 0);
                }
                PLAYER.velocityY = 0;
                if (!(g_Player.unk44 & 8)) {
                    PLAYER.velocityX = 0;
                }
                PLAYER.step = 0;
                PLAYER.unk4C = D_801555E8;
                g_Player.unk44 = 0;
                return true;
            }
        } else if ((arg_flags & 0x20000) && (g_Player.pl_vram_flag & 1)) {
            func_8015CCC8(1, PLAYER.velocityX);
            g_api.PlaySfx(0x64B);
            if ((g_Player.unk5C != 0) && (g_Status.hp < 2)) {
                func_8015D9B4();
                return true;
            } else {
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
            }
            return true;
        }
    }
    if ((arg_flags & 4) && !(g_Player.pl_vram_flag & 1)) {
        if (g_Player.unk46 != 0) {
            if (g_Player.unk46 == 1) {
                PLAYER.step_s = 0x40;
                PLAYER.step = 4;
                PLAYER.unk4C = D_801555C8;
                return true;
            }
            if (g_Player.unk46 == 2) {
                PLAYER.step_s = 0x41;
                PLAYER.step = 4;
                PLAYER.unk4C = D_801555C8;
                return true;
            }
            if (g_Player.unk46 == 3) {
                PLAYER.step_s = 0x42;
                PLAYER.step = 4;
                PLAYER.unk4C = D_80155638;
                return true;
            }
        } else {
            func_8015CF08();
            return true;
        }
    }
    if (g_Player.unk46 != 0) {
        return false;
    }
    if ((arg_flags & 0x40) && (g_Player.padTapped & PAD_TRIANGLE) &&
        (func_8015D678() != 0)) {
        return true;
    }
    if (arg_flags & 0x40000) {
        if (!PLAYER.facingLeft) {
            effects = g_Player.colliders[2].effects & EFFECT_UNK_8000;
        } else {
            effects = g_Player.colliders[3].effects & EFFECT_UNK_8000;
        }
        if (!effects) {
            if (((PLAYER.posX.i.hi <= (u8)-5) || (PLAYER.facingLeft)) &&
                ((PLAYER.posX.i.hi >= 5) || (!PLAYER.facingLeft)) &&
                (g_Player.padPressed & PAD_DOWN) &&
                (g_Player.padTapped & PAD_CROSS)) {
                func_8015D9D4();
                return true;
            }
        }
    }
    if (arg_flags & 0x10 && (g_Player.padTapped & PAD_CROSS)) {
        func_8015D020();
        return true;
    }
    if ((arg_flags & 0x1000) && (g_Player.padTapped & PAD_SQUARE) &&
        (func_8015D3CC() != 0)) {
        return true;
    }
    if ((arg_flags & 0x2000) && (g_Player.padPressed & PAD_DOWN)) {
        func_8015CCC8(2, 0);
        return true;
    }
    return false;
}
