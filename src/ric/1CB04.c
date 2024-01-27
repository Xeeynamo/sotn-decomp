#include "ric.h"
#include "player.h"

void func_80158B04(s32 arg0) {
    s32 var_s0;

    if (PLAYER.facingLeft != 0) {
        var_s0 = -3;
    } else {
        var_s0 = 3;
    }

    PLAYER.posY.i.hi -= 16;
    PLAYER.posX.i.hi = var_s0 + PLAYER.posX.i.hi;
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x100, 4), 0);
    PLAYER.posY.i.hi += 16;
    PLAYER.posX.i.hi = PLAYER.posX.i.hi - var_s0;

    if (arg0 & 1) {
        g_api.func_80102CD8(3);
        g_api.PlaySfx(NA_SE_SECRET_STAIRS);
    }

    if (arg0 & 2) {
        PLAYER.velocityX = 0;
        PLAYER.velocityY = 0;
    }
}

void func_80158BFC(void) {
    s32 var_s0;

    if (PLAYER.step < 64) {
        if (D_8015459C != 0) {
            D_8015459C--;
        } else if (D_80097448[0] >= 49) {
            if (PLAYER.facingLeft != 0) {
                var_s0 = -4;
            } else {
                var_s0 = 4;
            }
            PLAYER.posX.i.hi = var_s0 + PLAYER.posX.i.hi;
            PLAYER.posY.i.hi -= 16;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x800, 4), 0);
            D_8015459C = 0x60;
            PLAYER.posY.i.hi += 16;
            PLAYER.posX.i.hi = PLAYER.posX.i.hi - var_s0;
        }
    }

    if (func_8015DBB0(0x40000 | 0x305C) == false) {
        func_8015C93C(0x2000);
        switch (PLAYER.step_s) {
        case 0:
            if (func_8015C9CC() == 0) {
                if (g_Player.padPressed & PAD_UP) {
                    func_8015C920(&D_80155394);
                    PLAYER.step_s = 1;
                    break;
                }
            } else {
                func_8015CDE0(0);
            }
            break;

        case 1:
            if (func_8015C9CC() != 0) {
                func_8015CDE0(0);
                break;
            } else if (g_Player.padPressed & PAD_UP) {
                break;
            } else {
                func_8015CD98(0);
                break;
            }

        case 64:
            func_8015CB58(1, 1);
            if (PLAYER.animFrameIdx < 3) {
                func_8015C9CC();
                if (g_Player.padPressed & PAD_DOWN) {
                    PLAYER.step = 2;
                    PLAYER.unk4C = D_801555A8;
                    break;
                }
            }

            if (PLAYER.animFrameDuration < 0) {
                if (g_Player.padPressed & PAD_SQUARE) {
                    g_Player.unk46 = 2;
                    PLAYER.step_s++;
                    func_8015C920(D_80155730);
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 17), 0);
                    break;
                }
                g_Player.unk46 = 0;
                func_8015CD98(0);
            }
            break;

        case 65:
            func_8015CB58(1, 1);
            if (g_Player.padPressed & PAD_SQUARE) {
                break;
            }
            g_Player.unk46 = 0;
            func_8015CD98(0);
            break;

        case 66:
            func_8015CB58(1, 1);
            if (PLAYER.animFrameIdx < 3) {
                func_8015C9CC();
            }
            if (PLAYER.animFrameDuration < 0) {
                g_Player.unk46 = 0;
                func_8015CD98(0);
            }
        }
    }
}

void func_80158F38(void) {
    if (func_8015DBB0(0x305C) == 0) {
        func_8015C93C(0x2000);
        if (func_8015C9CC() == 0) {
            func_8015CD98(0);
            return;
        }

        if (PLAYER.step_s == 0) {
            SetSpeedX(0x14000);
        }
    }
}

void func_80158FA4(void) {
    if (g_Player.unk7A != 0) {
        func_8015CDE0(0);
        return;
    }
    g_Player.D_80072F00[8] = 8;
    g_Player.D_80072F00[1] = 8;

    if (!func_8015DBB0(0x305C)) {
        func_8015C93C(0x2000);
        if (func_8015C9CC() == 0) {
            func_8015CD98(0);
            if (g_Player.D_80072F00[11] == 0) {
                if (!(g_Player.pl_vram_flag & 0xC)) {
                    func_8015C920(&D_8015539C);
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 0), 0);
                }
            } else {
                PLAYER.velocityX = 0;
            }
        } else if (PLAYER.step_s == 0) {
            SetSpeedX(0x24000);
        }
    }
}

void func_801590A0(void) {
    if ((D_80154570 == 0) && (PLAYER.velocityY < FIX(-1)) &&
        !(g_Player.unk44 & 0x40) && !(g_Player.padPressed & PAD_CROSS)) {
        PLAYER.velocityY = FIX(-1);
    }
    if ((g_Player.pl_vram_flag & 2) && (PLAYER.velocityY < FIX(-1))) {
        PLAYER.velocityY = FIX(-0.25);
        g_Player.unk44 |= 0x20;
    }
    if (func_8015DBB0(0x11009)) {
        return;
    }
    switch (PLAYER.step_s) {
    // Need at least one fake case to make the switch match
    case 1:
        return;
    case 0:
        func_8015C93C(0x1000);
        if (func_8015C9CC()) {
            if (g_Player.unk44 & 0x10) {
                SetSpeedX(FIX(2.25));
            } else {
                SetSpeedX(FIX(1.25));
            }
            g_Player.unk44 &= ~4;
        } else {
            g_Player.unk44 &= ~0x10;
            if ((PLAYER.animFrameIdx < 2) &&
                ((LOW(g_Player.unk44) & 0xC) == 4) &&
                (g_Player.padTapped & PAD_CROSS)) {
                func_8015C920(D_8015555C);
                SetSpeedX(FIX(-1.5));
                PLAYER.velocityY = FIX(-2.625);
                if (g_Player.unk72 != 0) {
                    PLAYER.velocityY = 0;
                }
                PLAYER.step_s = 2;
                g_Player.unk44 |= 0xA;
                g_Player.unk44 &= ~4;
            }
        }
        return;
    case 0x40:
        func_8015CB58(1, 1);
        if (PLAYER.animFrameIdx < 3) {
            if (func_8015C9CC() != 0) {
                if (g_Player.unk44 & 0x10) {
                    SetSpeedX(FIX(2.25));
                } else {
                    SetSpeedX(FIX(1.25));
                }
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        } else {
            if (((g_Player.padPressed & PAD_RIGHT) && !PLAYER.facingLeft) ||
                ((g_Player.padPressed & PAD_LEFT) && PLAYER.facingLeft)) {
                if (g_Player.unk44 & 0x10) {
                    SetSpeedX(FIX(2.25));
                } else {
                    SetSpeedX(FIX(1.25));
                }
                SetSpeedX(FIX(1.25));
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        }
        if (PLAYER.animFrameDuration < 0) {
            if (g_Player.padPressed & PAD_SQUARE) {
                g_Player.unk46 = 2;
                PLAYER.step_s += 1;
                func_8015C920(D_80155740);
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 17), 0);
            } else {
                g_Player.unk46 = 0;
                PLAYER.step_s = 0;
                func_8015C920(D_80155528);
            }
        }
        return;
    case 0x41:
        func_8015CB58(1, 1);
        if (!(g_Player.padPressed & PAD_SQUARE)) {
            g_Player.unk46 = 0;
            PLAYER.step_s = 0;
            func_8015C920(D_80155528);
        }
        return;
    case 0x42:
        func_8015CB58(1, 1);
        if (PLAYER.animFrameIdx < 3) {
            if (func_8015C9CC() != 0) {
                if (g_Player.unk44 & 0x10) {
                    SetSpeedX(FIX(2.25));
                } else {
                    SetSpeedX(FIX(1.25));
                }
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        } else {
            if (((g_Player.padPressed & PAD_RIGHT) && !PLAYER.facingLeft) ||
                ((g_Player.padPressed & PAD_LEFT) && PLAYER.facingLeft)) {
                if (g_Player.unk44 & 0x10) {
                    SetSpeedX(FIX(2.25));
                } else {
                    SetSpeedX(FIX(1.25));
                }
                SetSpeedX(FIX(1.25));
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        }
        if (PLAYER.animFrameDuration < 0) {
            g_Player.unk46 = 0;
            PLAYER.step_s = 0;
            func_8015C920(D_80155528);
        }
    }
}

void func_801595D8(void) {
    if (func_8015DBB0(0x9009)) {
        return;
    }
    func_8015C93C(0x1000);
    if (PLAYER.step_s != 0) {
        return;
    }
    if (g_Player.D_80072F00[5] != 0 && g_Player.padTapped & PAD_CROSS) {
        func_8015D020();
    } else if (func_8015C9CC() != 0) {
        SetSpeedX(0xC000);
    }
}

void func_80159670(void) {
    s32 i;
    s16 xShift;

    if ((g_Player.padTapped & PAD_CROSS) && (g_Player.unk46 == 0) &&
        (g_Player.padPressed & PAD_DOWN)) {
        for (i = 0; i < 4; i++) {
            if ((g_Player.colliders[i].effects & EFFECT_SOLID_FROM_ABOVE)) {
                g_Player.D_80072F00[7] = 8;
                return;
            }
        }
    }
    if (func_8015DBB0(0x4100C)) {
        return;
    }
    if ((g_Player.padTapped & PAD_CROSS) && (g_Player.unk46 == 0) &&
        (g_Player.unk72 == 0)) {
        func_8015D020(1);
        return;
    } else if ((g_Player.unk72 == 0) && (g_Player.unk46 == 0) &&
               (g_Player.padTapped & PAD_TRIANGLE) && func_8015D678()) {
        return;
    }
    func_8015C93C(0x2000);
    switch (PLAYER.step_s) {
    case 0x0:
        if (D_8015459C != 0) {
            D_8015459C--;
        } else if ((*D_80097448 >= 0x19) && (g_Player.unk48 == 0)) {
            if (PLAYER.facingLeft) {
                xShift = -9;
            } else {
                xShift = 9;
            }
            PLAYER.posX.i.hi += xShift;
            PLAYER.posY.i.hi += 2;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x800, 4), 0);
            D_8015459C = 0x60;
            PLAYER.posY.i.hi -= 2;
            PLAYER.posX.i.hi -= xShift;
        }
        if (!(g_Player.padPressed & PAD_DOWN) &&
            ((g_Player.unk72 == 0) || !(g_Player.pl_vram_flag & 0x40))) {
            func_8015C920(D_801554E0);
            PLAYER.step_s = 2;
            return;
        }
        break;
    case 0x1:
        if (!(g_Player.padPressed & PAD_DOWN) &&
            ((g_Player.unk72 == 0) || !(g_Player.pl_vram_flag & 0x40))) {
            if (func_8015C9CC() == 0) {
                PLAYER.unk4C = D_801554E0;
                PLAYER.step_s = 2;
                PLAYER.animFrameDuration = 1;
                PLAYER.animFrameIdx = 2 - PLAYER.animFrameIdx;
                return;
            }
            func_8015CDE0(0);
            return;
        }
    case 0x4:
        if (PLAYER.animFrameDuration != -1) {
            return;
        }
        func_8015C920(D_801554C0);
        PLAYER.step_s = 0;
        return;
    case 0x2:
        if ((g_Player.unk72 == 0) || !(g_Player.pl_vram_flag & 0x40)) {
            if (func_8015C9CC() != 0) {
                func_8015CDE0(0);
                return;
            }
            if (PLAYER.animFrameDuration == -1) {
                func_8015CD98(0);
                return;
            }
        }
        break;
    case 0x3:
        if (PLAYER.animFrameDuration < 0) {
            func_8015C920(D_801554C0);
            PLAYER.step_s = 0;
            return;
        }
        break;
    case 0x40:
        func_8015CB58(1, 1);
        if (PLAYER.animFrameIdx < 3) {
            func_8015C9CC();
            if (!(g_Player.padPressed & PAD_DOWN) && (g_Player.unk72 == 0)) {
                PLAYER.step = 0;
                PLAYER.unk4C = D_80155588;
                return;
            }
        }
        if (PLAYER.animFrameDuration < 0) {
            if (g_Player.padPressed & PAD_SQUARE) {
                g_Player.unk46 = 2;
                PLAYER.step_s++;
                func_8015C920(D_80155738);
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 17), 0);
                return;
            }
            g_Player.unk46 = 0;
            PLAYER.step_s = 0;
            func_8015C920(D_801554C0);
        }
        break;
    case 0x41:
        func_8015CB58(1, 1);
        if (!(g_Player.padPressed & PAD_SQUARE)) {
            g_Player.unk46 = 0;
            PLAYER.step_s = 0;
            func_8015C920(D_801554C0);
        }
        break;
    }
}

void func_80159BC8(void) {
    PLAYER.animFrameDuration = 0;
    PLAYER.animFrameIdx = 0;
    g_Player.unk44 = 0;
    g_Player.unk46 = 0;
    PLAYER.drawFlags &= 0xFB;
}

void func_80159C04(void) {
    Entity* entity = PLAYER.ext.generic.unkB8.entityPtr;
    s16 temp_v0;
    s32 var_a0;
    s32 var_a2;

    if (entity->facingLeft != 0) {
        var_a2 = -entity->hitboxOffX;
    } else {
        var_a2 = entity->hitboxOffX;
    }

    if (PLAYER.facingLeft != 0) {
        var_a0 = -PLAYER.hitboxOffX;
    } else {
        var_a0 = PLAYER.hitboxOffX;
    }

    temp_v0 = var_a0 + PLAYER.posX.i.hi - entity->posX.i.hi - var_a2;

    if (ABS(temp_v0) < 16) {
        if (entity->velocityX != 0) {
            if (entity->velocityX < 0) {
                PLAYER.entityRoomIndex = 0;
                return;
            } else {
                PLAYER.entityRoomIndex = 1;
                return;
            }
        }
    }

    if (temp_v0 < 0) {
        PLAYER.entityRoomIndex = 0;
    } else {
        PLAYER.entityRoomIndex = 1;
    }
}

void RichterHandleDamage(s32 arg0, u32 arg1, s16 arg2) {
    DamageParam damage;
    s32 xShift;
    s32 i;
    bool step_s_zero = false;

    if (D_80173B64 != 0) {
        D_80173B64--;
    }
    switch (PLAYER.step_s) {
    case 0:
        step_s_zero = true;
        func_80159BC8();
        if (arg1 < 16) {
            func_80159C04();
        } else {
            PLAYER.entityRoomIndex = PLAYER.facingLeft;
        }
        if (arg0 & 0x4000) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 48), 0);
            PLAYER.velocityY = FIX(-4);
            func_8015CAAC(FIX(-1.25));
            PLAYER.step_s = 1;
            PLAYER.unk4C = D_801556C4;
            g_Player.unk40 = 0x8120;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 48), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x4600, 33), 0);
            g_Player.D_80072F00[2] = 6;
            g_api.PlaySfx(0x703);
            break;
        } else {
            if (arg0 & 0x2000) {
                arg1 = 3;
            }
            switch (arg1 - 2) {
            case 0:
                switch (arg2) {
                case 0:
                case 1:
                    PLAYER.velocityY = 0;
                    func_8015CAAC(FIX(-1.25));
                    PLAYER.step_s = 6;
                    PLAYER.unk4C = D_8015569C;
                    g_api.PlaySfx(0x702);
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 0), 0);
                    break;
                case 2:
                    PLAYER.velocityY = 0;
                    func_8015CAAC(FIX(-1.25));
                    PLAYER.step_s = 7;
                    PLAYER.unk4C = D_80155704;
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 0), 0);
                    g_api.PlaySfx(0x703);
                    break;
                case 3:
                case 4:
                    PLAYER.velocityY = FIX(-3);
                    func_8015CAAC(FIX(-1.25));
                    PLAYER.step_s = 1;
                    PLAYER.unk4C = D_80155694;
                    g_api.PlaySfx(0x702);
                    break;
                }
                break;
            case 2:
            case 3:
                PLAYER.velocityY = FIX(-0.5);
                g_Player.damageTaken = PLAYER.hitPoints;
                PLAYER.posY.val -= 1;
                func_8015CAAC(FIX(-8));
                PLAYER.step_s = 2;
                PLAYER.unk4C = D_80155694;
                g_Player.D_80072F00[2] = 0x200;
                PLAYER.facingLeft = PLAYER.entityRoomIndex;
                break;
            default:
            case 1:
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
                switch (arg2) {
                default:
                case 0:
                case 1:
                    PLAYER.velocityY = FIX(-4);
                    func_8015CAAC(FIX(-1.25));
                    PLAYER.step_s = 1;
                    PLAYER.unk4C = D_80155694;
                    g_api.PlaySfx(0x702);
                    break;
                case 2:
                    PLAYER.velocityY = 0;
                    func_8015CAAC(FIX(-1.25));
                    PLAYER.step_s = 7;
                    PLAYER.unk4C = D_80155704;
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 0), 0);
                    g_api.PlaySfx(0x703);
                    break;
                case 3:
                case 4:
                    PLAYER.velocityY = FIX(-3);
                    func_8015CAAC(FIX(-1.25));
                    PLAYER.step_s = 1;
                    PLAYER.unk4C = D_80155694;
                    g_api.PlaySfx(0x702);
                    break;
                }
                break;
            }
            g_Player.unk40 = 0x8166;
            g_Player.D_80072F00[2] = 6;
            if (arg0 & 0x8000) {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x100, 8), 0);
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 9), 0);
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x4300, 33), 0);
                g_Player.unk40 = 0x8160;
                g_Player.D_80072F00[2] = 0x10;
                break;
            } else if (arg0 & 0x40) {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x500, 46), 0);
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x4400, 33), 0);
                g_Player.unk40 = 0x8166;
                g_Player.D_80072F00[2] = 0x10;
                break;
            } else if (arg0 & 0x2000) {
                // Creates EntityHitByIce
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 47), 0);
                g_Player.D_80072F00[2] = 0xC;
                g_Player.unk40 = 0x8169;
                break;
            } else {
                if (arg0 & 0x800) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 70), 0);
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x5600, 33), 0);
                    g_Player.D_80072F00[2] = 0x10;
                    g_Player.unk40 = 0x8164;
                }
                if (arg0 & 0x1000) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 71), 0);
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x5700, 33), 0);
                    g_Player.D_80072F00[2] = 8;
                    g_Player.unk40 = 0x8168;
                }
                if (!(arg0 & 0xF840)) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x5300, 33), 0);
                }
            }
        }
        break;
    case 1:
        if ((g_Player.pl_vram_flag & 2) && (PLAYER.velocityY < FIX(-1))) {
            PLAYER.velocityY = FIX(-1);
        }
        if (func_8015DBB0(0x20280)) {
            return;
        }
        break;
    case 2:
        if ((g_Player.unk04 & 0x8000) && !(g_Player.pl_vram_flag & 0x8000)) {
            goto block_6dc;
        }
        if ((g_Player.pl_vram_flag & 0x8000) && !(g_GameTimer & 1)) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0xA00, 74), 0);
        }
        if (!(g_Player.pl_vram_flag & 0xE)) {
            break;
        }
        if (g_Player.pl_vram_flag & 2) {
            func_80158B04(1);
            D_80173B64 = 0x18;
            PLAYER.velocityX /= 2;
            PLAYER.velocityY = 0;
            PLAYER.step_s = 5;
            damage.effects = 0;
            damage.damageKind = 1;
            damage.damageTaken = g_Player.damageTaken;
            if (g_api.func_800FD5BC(&damage) != 0) {
                SetPlayerStep(Player_Kill);
                func_8015A9B0(0, 2, 10, 2);
                return;
            }
            break;
        } else {
            if ((g_StageId != STAGE_BO6) && (g_StageId != STAGE_RBO6) &&
                (g_StageId != STAGE_DRE)) {
                for (i = 2; i < 7; i++) {
                    if ((g_Player.colliders3[i].effects & 2)) {
                        break;
                    }
                }
                if (i == 7) {
                    for (i = 9; i < 0xE; i++) {
                        if ((g_Player.colliders3[i].effects & 2)) {
                            break;
                        }
                    }
                }
                if (i == 14) {
                block_6dc:
                    PLAYER.velocityY = FIX(-4);
                    func_8015CAAC(FIX(-1.25));
                    xShift = -3;
                    if (PLAYER.velocityX != 0) {
                        xShift = 3;
                    }
                    PLAYER.posY.i.hi += 20;
                    PLAYER.posX.i.hi = xShift + PLAYER.posX.i.hi;
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x900, 4), 0);
                    PLAYER.posY.i.hi -= 20;
                    PLAYER.posX.i.hi -= xShift;
                    g_api.PlaySfx(NA_SE_EN_ROCK_BREAK);
                    g_api.func_80102CD8(2);
                    PLAYER.step_s = 1;
                    damage.effects = 0;
                    damage.damageKind = 1;
                    damage.damageTaken = g_Player.damageTaken;
                    if (g_api.func_800FD5BC(&damage) != 0) {
                        SetPlayerStep(Player_Kill);
                        func_8015A9B0(0, 2, 10, 2);
                        return;
                    }
                    break;
                }
            }
            D_80173B64 = 8;
            g_api.PlaySfx(NA_SE_EN_ROCK_BREAK);
            PLAYER.velocityY = FIX(-2.5);
            g_api.func_80102CD8(2);
            PLAYER.step_s = 3;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x800, 75), 0);
        }
        damage.effects = 0;
        damage.damageKind = 1;
        damage.damageTaken = g_Player.damageTaken;
        if (g_api.func_800FD5BC(&damage) != 0) {
            SetPlayerStep(Player_Kill);
            func_8015A9B0(0, 2, 10, 2);
            return;
        }
        break;
    case 3:
        if (D_80173B64 == 0) {
            SetSpeedX(FIX(0.75));
            if (func_8015DBB0(0x20280)) {
                return;
            }
        }
        break;
    case 5:
        func_8015C93C(0x2000);
        if (D_80173B64 != 0) {
            if ((g_Player.pl_vram_flag & 2) && !(g_GameTimer & 3)) {
                func_80158B04(0);
            }
            break;
        } else if (g_Player.pl_vram_flag & 0xC) {
            if (!(g_Player.pl_vram_flag & 0xFF03)) {
                PLAYER.velocityY += FIX(12.0 / 128);
                if (PLAYER.velocityY > FIX(7)) {
                    PLAYER.velocityY = FIX(7);
                }
                if (!(g_GameTimer & 3)) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x400, 76), 0);
                }
                break;
            }
        }
        PLAYER.step_s = 1;
        PLAYER.animFrameIdx = 0;
        PLAYER.animFrameDuration = 0;
        break;
    case 6:
        func_8015C93C(0x2000);
        if (!(g_Player.pl_vram_flag & 1)) {
            func_8015CF08();
        }
        if (PLAYER.animFrameDuration < 0) {
            if ((g_Player.unk5C == 0) || (g_Status.hp > 0)) {
                func_8015CD98(PLAYER.velocityX);
                break;
            }
            func_8015D9B4();
            return;
        }
        break;
    case 7:
        func_8015C93C(0x2000);
        if (!(g_Player.pl_vram_flag & 1)) {
            func_8015CF08();
        }
        if (PLAYER.animFrameDuration < 0) {
            if ((g_Player.unk5C != 0) && (g_Status.hp <= 0)) {
                func_8015D9B4();
                return;
            }
            func_8015CCC8(0, PLAYER.velocityX);
        }
        break;
    }
    if (step_s_zero && (g_Player.unk72 != 0)) {
        PLAYER.velocityY = 0;
    }
}

void func_8015A7D0(void) {
    DamageParam damage;
    switch (g_CurrentEntity->step_s) {
    case 0:
        func_80159BC8();
        if (g_Player.unk62 == 0) {
            PLAYER.unk4C = D_80155694;
            g_Player.D_80072F00[2] = 8;
            g_Player.unk40 = 0x8166;
            g_api.PlaySfx(0x702);
        }
        PLAYER.step_s = 1;
        PLAYER.velocityX = PLAYER.velocityY = 0;
        g_Player.unk60 = 2;
        return;
    case 1:
        // Effectively a switch on g_Player.unk60
        if (g_Player.unk60 == 3) {
            damage.effects = 0;
            damage.damageKind = 1;
            damage.damageTaken = g_Player.damageTaken;
            if (g_api.func_800FD5BC(&damage)) {
                SetPlayerStep(Player_Kill);
                func_8015A9B0(0, 2, 12, 1);
                return;
            }
            if (g_Player.unk62 == 0) {
                g_Player.D_80072F00[2] = 4;
                g_Player.unk40 = 0x8166;
                g_api.PlaySfx(0x703);
            }
            g_Player.unk60 = 2;
        } else if (g_Player.unk60 == 4) { /* switch 1 */
            PLAYER.step = Player_Hit;
            PLAYER.step_s = 2;
            g_Player.unk60 = 0;
            g_Player.damageTaken = g_Player.unk64;
            g_api.PlaySfx(0x704);
        } else if (g_Player.unk60 == 0) { /* switch 1 */
            PLAYER.step = Player_Hit;
            PLAYER.step_s = 1;
        }
    }
}

INCLUDE_ASM("ric/nonmatchings/1CB04", func_8015A9B0);

void func_8015AFE0(void) {
    if (PLAYER.step_s == 0) {
        PLAYER.velocityY += 0x3800;
        if (PLAYER.velocityY > 0) {
            PLAYER.velocityY = 0;
            PLAYER.step_s = 1;
        }
    } else if (g_Player.unk4E != 0) {
        g_Player.unk46 = 0;
        SetPlayerStep(4);
        func_8015C920(&D_80155528);
        g_Player.unk44 = 0;
    }
    if (g_Player.unk72 != 0) {
        PLAYER.velocityY = 0;
    }
}

void func_8015B098(void) {
    if ((PLAYER.animCurFrame == 0xB5) && (PLAYER.animFrameDuration == 1)) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 35), 0);
        g_api.PlaySfx(NA_SE_UNK_62F);
    }

    if (PLAYER.animFrameDuration < 0) {
        func_8015CD98(0);
        g_Player.unk46 = 0;
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x4500, 33), 0);
        g_Player.D_80072F00[0] = 0x800;
    }

    if (!(g_Player.pl_vram_flag & 1)) {
        func_8015CF08();
        g_Player.unk46 = 0;
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x4500, 33), 0);
        g_Player.D_80072F00[0] = 0x800;
    }
}

void func_8015B18C(void) {
    if (PLAYER.animFrameDuration < 0) {
        func_8015CD98(0);
        g_Player.unk46 = 0;
    }

    if ((g_Player.pl_vram_flag & 1) == 0) {
        func_8015CF08();
        g_Player.unk46 = 0;
    }
}

void func_8015B1E8(void) {
    if (g_Player.unk4E) {
        func_8015CD98(0);
        g_Player.unk46 = 0;
    }

    if ((g_Player.pl_vram_flag & 1) == 0) {
        func_8015CF08();
        g_Player.unk46 = 0;
    }
}

void func_8015B244(void) {
    if (PLAYER.step_s == 0) {
        D_80174F74 = 0x200;
        PLAYER.step_s++;
    } else {
        func_8015C9CC();
        D_80174F74--;
        if (D_80174F74 == 0) {
            g_Player.unk46 = 0;
            func_8015CD98(0);
            g_Player.unk4E = 1;
        }
    }
    if (g_Player.padTapped & PAD_CROSS) {
        func_8015D020();
        g_Player.unk46 = 0;
        g_Player.unk4E = 1;
        D_80174F74 = 0;
    }
    if (!(g_Player.pl_vram_flag & 1)) {
        func_8015CF08();
        g_Player.unk46 = 0;
        g_Player.unk4E = 1;
        D_80174F74 = 0;
    }
}
// Runs when Richter's step is 22. This happens when he dies in prologue
// and gets saved by Maria.
void func_8015B348(void) {
    switch (PLAYER.step_s) {
    case 0:
        g_CurrentEntity->flags |= FLAG_UNK_10000;
        D_80097420[0] = 4;
        func_8015C93C(0x2000);

        if (PLAYER.velocityX == 0) {
            func_8015C920(&D_80155748);
            g_Player.D_80072F00[13] = 4;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 29), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x900, 33), 0);
            D_801545AC = 0;
            PLAYER.step_s++;
        }
        break;

    case 1:
        PLAYER.drawFlags = FLAG_DRAW_ROTY;
        D_801545AA += 64;
        PLAYER.rotY = (rsin(D_801545AA) >> 0xA) + 256;

        if (D_801545AC != 0) {
            D_801545AC--;
            if ((D_801545AC) == 0) {
                PLAYER.drawFlags = 0;
                PLAYER.rotY = 0x100;
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 23), 0);
                D_801545A8 = 0x90;
                PLAYER.step_s++;
            }
        }
        break;

    case 2:
        // In this step, Richter rises into the air, similar to when he uses the
        // Cross subweapon crash.
        D_801545A8--;
        if ((D_801545A8) == 0) {
            func_8015C920(&D_801558B4);
            PLAYER.palette = 0x814E;
            g_CurrentEntity->velocityY = FIX(-1);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 22), 0);
            D_801545A8 = 0x30;
            g_api.PlaySfx(0x6E2);
            D_80174F78 = 0xA0;
            PLAYER.step_s++;
        }
        break;

    case 3:
        D_801545A8--;
        if ((D_801545A8) == 0) {
            PLAYER.velocityY = 0;
            D_801545A8 = 0xC0;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 36), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x200, 37), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x300, 38), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x400, 39), 0);
            PLAYER.palette = 0x813D;
            g_Player.D_80072F00[13] = 0;
            PLAYER.step_s++;
        }

        if (g_Status.hp < g_Status.hpMax) {
            g_Status.hp++;
        }

        D_80174F78--;
        if ((D_80174F78 >= 0) && (D_80174F78 % 20 == 0)) {
            g_api.PlaySfx(NA_SE_PL_RIC_UNK_6E2);
        }
        break;

    case 4:
        D_801545A8--;
        if ((D_801545A8 << 0x10) == 0) {
            D_801545A8 = 0x10;
            PLAYER.step_s++;
        }

        if (g_Status.hp < g_Status.hpMax) {
            g_Status.hp++;
        }

        D_80174F78--;
        if ((D_80174F78 >= 0) && (D_80174F78 % 20 == 0)) {
            g_api.PlaySfx(NA_SE_PL_RIC_UNK_6E2);
        }
        break;

    case 5:
        if (D_801545A8 == 5) {
            PLAYER.animFrameIdx = 6;
            PLAYER.palette = 0x8120;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 28), 0);
        }
        D_801545A8--;
        if (D_801545A8 == 0) {
            func_8015C920(&D_801558D4);
            g_api.PlaySfx(NA_SE_UNK_62F);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 27), 0);
            PLAYER.step_s++;
            break;
        }

        if (g_Status.hp < g_Status.hpMax) {
            g_Status.hp++;
        }
        break;

    case 6:
        if (PLAYER.animFrameDuration < 0) {
            func_8015C920(&D_801558DC);
            PLAYER.step_s++;
        }
        break;

    case 7:
        if (PLAYER.animFrameDuration < 0) {
            g_CurrentEntity->flags &= ~FLAG_UNK_10000;
            D_80097420[0] = 0;
            func_8015CF08();
            func_8015C920(&D_801558DC);
            g_Player.D_80072F00[13] = 4;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x900, 33), 0);
        }
        break;
    }
}

void func_8015B898(void) {
    s32 condition = 0;

    if (!PLAYER.facingLeft) {
        condition = (g_Player.pl_vram_flag & 4) != condition;
    } else if (g_Player.pl_vram_flag & 8) {
        condition = 1;
    }
    if ((PLAYER.posX.i.hi > (u8)-5) && (!PLAYER.facingLeft)) {
        condition = 1;
    }
    if (PLAYER.posX.i.hi < 5 && (PLAYER.facingLeft)) {
        condition = 1;
    }
    if ((!PLAYER.facingLeft &&
         (g_Player.colliders[2].effects & EFFECT_UNK_8000)) ||
        (PLAYER.facingLeft &&
         (g_Player.colliders[3].effects & EFFECT_UNK_8000))) {
        condition = 1;
    }
    if (condition && (PLAYER.animFrameIdx < 6)) {
        PLAYER.animFrameIdx = 6;
        if (PLAYER.velocityX > FIX(1)) {
            PLAYER.velocityX = FIX(2);
        }
        if (PLAYER.velocityX < FIX(-1)) {
            PLAYER.velocityX = FIX(-2);
        }
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
    }
    if (PLAYER.animFrameIdx < 5) {
        if (func_8015DBB0(0x44)) {
            return;
        }
        if ((g_Player.unk72 == 0) && (g_Player.padTapped & PAD_CROSS)) {
            PLAYER.posY.i.hi -= 4;
            func_8015DA60();
            return;
        }
    } else if (PLAYER.animFrameIdx < 7) {
        if (func_8015DBB0(0x40044)) {
            return;
        }
    } else if (func_8015DBB0(0x4004C)) {
        return;
    }

    func_8015C93C(0x2000);
    if (PLAYER.step_s == 0) {
        if (!(g_GameTimer & 3) && (2 < PLAYER.animFrameIdx) &&
            (PLAYER.animFrameIdx < 6)) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x200, 24), 0);
        }
        if (PLAYER.animFrameIdx == 6 && PLAYER.animFrameDuration == 1) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8015CCC8(0, PLAYER.velocityX);
        }
    }
}

// same as DRA/func_80115C50
void func_8015BB80(void) {
    s32 dist;

    if (g_StageId == STAGE_TOP) {
        dist = g_Tilemap.left * 256 + playerX;
        dist = ABS(dist);

        if (dist - 8000 > 0) {
            PLAYER.posX.i.hi--;
        }

        dist = g_Tilemap.left * 256 + playerX;
        dist = ABS(dist);

        if (dist - 8000 < 0) {
            PLAYER.posX.i.hi++;
        }
    }

    if (g_StageId == (STAGE_TOP | STAGE_INVERTEDCASTLE_FLAG)) {
        dist = g_Tilemap.left * 256 + playerX;
        dist = ABS(dist);

        if (dist - 8384 > 0) {
            PLAYER.posX.i.hi--;
        }

        dist = g_Tilemap.left * 256 + playerX;
        dist = ABS(dist);

        if (dist - 8384 < 0) {
            PLAYER.posX.i.hi++;
        }
    }
}
