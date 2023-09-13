#define INCLUDE_ASM_NEW
#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

void func_80113AAC(void) {
    s32 var_s1 = 0;
    s32 temp;

    g_Player.unk4A++;
    if (func_8010FDF8(2) != 0) {
        return;
    }

    switch (PLAYER.step_s) {
    case 0:
        if (g_Player.pl_vram_flag & 2) {
            func_801139CC(3);
            if (g_Player.unk4A >= 5) {
                PLAYER.step_s = 2;
                PLAYER.rotAngle = 0x800;
                PLAYER.rotPivotY = 2;
                PLAYER.rotPivotX = 0;
                PLAYER.unk19 |= 4;
                PLAYER.facingLeft = (PLAYER.facingLeft + 1) & 1;
                func_8010DA48(0x2B);
            } else {
                PLAYER.step_s = 3;
            }
        } else if (g_Player.unk4A > 28) {
            PLAYER.step_s = 1;
            PLAYER.velocityY = -0x60000;
            func_8010DA48(0x1B);
        }
        break;

    case 1:
        if (g_Player.pl_vram_flag & 2) {
            PLAYER.step_s = 2;
            func_801139CC(3);
        } else {
            PLAYER.velocityY += 0x6000;
            if (PLAYER.velocityY > 0x8000) {
                var_s1 = 1;
            }
        }
        break;

    case 2:
        PLAYER.unk19 |= 4;
        PLAYER.rotPivotX = 0;
        PLAYER.rotPivotY = 2;
        if (g_Player.unk4A >= 0x39) {
            func_8010DA48(0x2D);
            PLAYER.rotAngle = 0;
            PLAYER.step_s = 4;
            PLAYER.unk19 &= 0xFB;
            PLAYER.facingLeft = (PLAYER.facingLeft + 1) & 1;
        }
        break;

    case 3:
        if (g_Player.unk4A > 20) {
            var_s1 = 1;
        }
        break;

    case 4:
        PLAYER.velocityY += 0x1000;
        if (PLAYER.animFrameDuration < 0) {
            var_s1 = 2;
        }
        break;
    }

    if (var_s1 != 0) {
        temp = 0; // TODO: !FAKE
        if ((var_s1 - 1) != temp) {
            func_8010DA48(0x1C);
        }
        PLAYER.palette = 0x8100;
        PLAYER.step_s = 1;
        PLAYER.step = Player_Jump;
    }
}

s32 func_80113D7C(s16 damageAmount) {
    DamageParam damage;
    s32 sfx;
    s32 temp_s0;
    s16 step;
    u16 temp_s1;

    temp_s0 = HandleDamage(&damage, 2, damageAmount / 2, 1);
    func_80118C84(damage.damageTaken, 0);
    func_800FE8F0();
    if (temp_s0 != 4) {
        g_Player.D_80072F04 = 4;
        g_Player.unk40 = 0x8166;
        sfx = D_800ACF8A[(rand() & 1)];
        PlaySfx(sfx);
        if (step && step) // TODO: !FAKE
            ;
        return 0;
    }
    step = PLAYER.step;
    temp_s1 = PLAYER.step_s;
    damage.unk0 = 0;
    damage.damageKind = 0;
    SetPlayerStep(Player_Unk16);
    func_80115394(&damage, step, temp_s1);
    return -1;
}

s32 func_80113E68(void) {
    s16 rnd = rand();
    PLAYER.ext.player.unkAC = 0x2E + (rnd % 3);
    return rnd % 16;
}

void func_80113EE0(void) {
    PLAYER.animSet = ANIMSET_DRA(1);
    PLAYER.unk19 &= 0xF3;
    PLAYER.animFrameDuration = 0;
    PLAYER.animFrameIdx = 0;
    PLAYER.entityId = 0;
    PLAYER.blendMode = 0;
    g_Player.unk44 = 0;
    g_Player.unk46 = 0;
    PLAYER.rotAngle = 0;
    PLAYER.zPriority = g_zEntityCenter.S16.unk0;
    if (g_Entities[E_WEAPON].entityId == E_UNK_22) {
        func_8010FAF4();
    }
}

void func_80113F7C(void) {
    Entity* entity = PLAYER.ext.generic.unkB8.entityPtr;
    s16 posX;
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

    posX = var_a0 + PLAYER.posX.i.hi - entity->posX.i.hi - var_a2;

    if (ABS(posX) < 16) {
        if (entity->velocityX != 0) {
            if (entity->velocityX >= 0) {
                PLAYER.entityRoomIndex = 1;
                return;
            }
            goto block_14;
        }
        goto block_13;
    }
    // TODO: labels are !FAKE
block_13:
    if (posX < 0) {
    block_14:
        PLAYER.entityRoomIndex = 0;
        return;
    }

    PLAYER.entityRoomIndex = 1;
}

void AlucardHandleDamage(DamageParam* param, s16 arg1, s16 arg2);
INCLUDE_ASM("dra/nonmatchings/73AAC", AlucardHandleDamage);

void func_80114DF4(s32 arg0) {
    s16 randvar;
    s32 newlyPetrified;
    s32 yShift;

    newlyPetrified = 0;
    switch (PLAYER.step_s) {
    case 0:
        newlyPetrified = 1;
        func_80113EE0();
        func_80113F7C();
        PLAYER.velocityY = FIX(-4);
        if (!(g_Player.pl_vram_flag & 1)) {
            PLAYER.velocityY = FIX(-2);
        }
        func_8010E3B8(FIX(-1.25));
        func_80113E68();
        PLAYER.palette = 0x8161;
        PlaySfx(0x6EC);
        g_Player.D_80072F04 = 0;
        g_Player.D_80072F00 = 0;
        g_Player.D_80072F02 = 0;
        g_Player.unk5E = GetStatusAilmentTimer(STATUS_AILMENT_PETRIFIED, 8);
        func_8011AAFC(g_CurrentEntity, 0x3002F, 0);
        func_8010E168(1, 4);
        PLAYER.step_s = 1;
        break;
    case 1:
        func_8010E168(1, 4);
        PLAYER.palette = 0x8161;
        if (func_8010FDF8(0x20280) != 0) {
            PLAYER.step = Player_StatusStone;
            PLAYER.velocityY = 0;
            PLAYER.velocityX = 0;
            func_80102CD8(1);
            PlaySfx(0x644);
            func_8011AAFC(g_CurrentEntity, 0x27, 0);

            randvar = rand() % 64;

            if (g_Status.hp == 0) {
                D_80137FE0 = 0x20;
                randvar = 2;
            }
            if (randvar << 0x10) {
                PLAYER.palette = (randvar & 1) - 0x7E62;
                func_8010DA48(randvar & 1 | 0x38);
                func_8011AAFC(g_CurrentEntity, 0x30010, 0);
            } else {
                PLAYER.palette = 0x819E;
                func_8010DA48(0x3A);
                func_8011AAFC(g_CurrentEntity, 0x7001D, 0);
            }
            PLAYER.step_s = 2;
        }
        break;
    case 2:
        if (D_80097448[0] >= 0x29) {
            yShift = FIX(11.0 / 256);
        } else {
            yShift = FIX(44.0 / 256);
        }

        // I don't know man
        do {
        } while (0);

        if (!(g_Player.pl_vram_flag & 1)) {
            PLAYER.velocityY += yShift;
            if (PLAYER.velocityY > FIX(7)) {
                PLAYER.velocityY = FIX(7);
            }
            func_8010E168(1, 4);
            break;
        }

        if (!(g_Player.unk04 & 1)) {
            func_80102CD8(1);
            PlaySfx(0x644);
        }

        PLAYER.velocityY = 0;
        if (g_Status.hp == 0) {
            if (--D_80137FE0 == 0) {
                PLAYER.step = Player_Unk16;
                PlaySfx(0x6F6);
                PLAYER.step_s = 16;
            }
            func_8010E168(1, 4);
            break;
        }
        // Handles wiggling out of being petrified.
        if (g_Player.padTapped & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT) ||
            arg0 != 0 || D_800ACE44 != 0) {
            PLAYER.animFrameDuration = 0x10;
            g_Player.padTapped |= (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
            // Counter for how many wiggles left until we're out
            g_Player.unk5E--;
            PlaySfx(0x608);
            if (g_Player.unk5E == 0) {
                func_8010DA48(0x3B);
                if (PLAYER.ext.player.unkAC != 0x3A) {
                    func_8011AAFC(g_CurrentEntity, 0x30010, 0);
                } else {
                    func_8011AAFC(g_CurrentEntity, 0x20, 0);
                }
                PlaySfx(0x6E7);
                PLAYER.step = Player_Hit;
                PLAYER.step_s = 6;
                PLAYER.palette = 0x8100;
                break;
            }
            func_8010E168(1, 0x1C);
            PLAYER.step_s = 3;
            if (PLAYER.ext.player.unkAC != 0x3A) {
                func_8011AAFC(g_CurrentEntity, 0x3000D, 0);
                func_8011AAFC(g_CurrentEntity, 0x3001F, 0);
            } else {
                func_8011AAFC(g_CurrentEntity, 0x8000D, 0);
                func_8011AAFC(g_CurrentEntity, 0x7001E, 0);
            }
        }
        PLAYER.palette = ((PLAYER.ext.player.unkAC + 0xFFC8) & 1) - 0x7E62;
        break;
    case 3:
        if (PLAYER.animFrameDuration < 0) {
            PLAYER.step_s = 2;
            PLAYER.unk19 &= 0xFB;
        } else {
            PLAYER.rotPivotX = 0;
            PLAYER.unk19 |= 4;
            PLAYER.rotAngle = D_800ACF94[PLAYER.animFrameDuration] >> 4;
            if (PLAYER.rotAngle == 0) {
                PLAYER.rotPivotY = 0x18;
            } else {
                PLAYER.rotPivotY = 0x14;
            }
        }
        break;
    }
    if (PLAYER.ext.player.unkAC == 0x3A) {
        func_8010E168(1, 4);
    }
    if (newlyPetrified && (g_Player.unk72 != 0)) {
        PLAYER.velocityY = 0;
    }
}

INCLUDE_ASM("dra/nonmatchings/73AAC", func_80115394);

void func_80115BB0(void) {
    PLAYER.unk19 = 4;
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    PLAYER.animFrameDuration = 4;

    if (D_80097420[0] == 0) {
        if (g_Player.pl_vram_flag & 1) {
            func_8010E570(0);
        } else {
            func_8010E7AC();
        }
        func_8011AAFC(g_CurrentEntity, 0x4A0000 | 0x2C, 0);
        D_80097D37 = 0;
    }
}

// same as RIC/func_8015BB80
void func_80115C50(void) {
    s32 dist;

    if (g_StageId == STAGE_TOP) {
        dist = (g_CurrentRoom.left * 256) + playerX;
        dist = ABS(dist);

        if (dist - 8000 > 0) {
            PLAYER.posX.i.hi--;
        }

        dist = (g_CurrentRoom.left * 256) + playerX;
        dist = ABS(dist);

        if (dist - 8000 < 0) {
            PLAYER.posX.i.hi++;
        }
    }

    if (g_StageId == (STAGE_TOP | STAGE_INVERTEDCASTLE_FLAG)) {
        dist = (g_CurrentRoom.left * 256) + playerX;
        dist = ABS(dist);

        if (dist - 8384 > 0) {
            PLAYER.posX.i.hi--;
        }

        dist = (g_CurrentRoom.left * 256) + playerX;
        dist = ABS(dist);

        if (dist - 8384 < 0) {
            PLAYER.posX.i.hi++;
        }
    }
}
