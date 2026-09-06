// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "maria.h"

typedef enum {
    TELEPORT_CHECK_NONE = 0,
    TELEPORT_CHECK_TO_RTOP = 2,
    TELEPORT_CHECK_TO_TOP = 4
} TeleportCheck;

extern s32 g_PlayerX;
extern s32 g_PlayerY;

// GetTeleportToOtherCastle
static TeleportCheck func_060A5060(void) {
    if (PLAYER.step != MARIA_PL_S_STAND || PLAYER.step_s != 1) {
        return TELEPORT_CHECK_NONE;
    }
    if (g_CurrentRoom.stageID == STAGE_TOP) {
        if (ABS((g_Tilemap.left << 8) + g_PlayerX - 8079) < 4 &&
            ABS((g_Tilemap.top << 8) + g_PlayerY - 2127) < 4) {
            return TELEPORT_CHECK_TO_RTOP;
        }
    }
    if (g_CurrentRoom.stageID == STAGE_RTOP) {
        if (ABS((g_Tilemap.left << 8) + g_PlayerX - 8430) < 4 &&
            ABS((g_Tilemap.top << 8) + g_PlayerY - 14407) < 4) {
            return TELEPORT_CHECK_TO_TOP;
        }
    }
    return TELEPORT_CHECK_NONE;
}
s16 func_060A5154(void) {
    Collider collider;
    s32 yvar;
    s32 collisions;
    s32 i;
    s32 xCenter;
    s32 xRight;
    s32 xLeft;
    s32 filter;

    filter = EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID;
    xCenter = PLAYER.posX.val;
    xRight = PLAYER.posX.val + FIX(4);
    xLeft = PLAYER.posX.val - FIX(4);

    for (i = 0; i < 3; i++) {
        yvar = PLAYER.posY.val + g_MariaCollisionProbeYOffsets[i];
        collisions = 0;
        CheckCollision(xCenter, yvar, &collider, 0);
        if ((collider.effects & filter) == EFFECT_SOLID) {
            collisions++;
        }

        CheckCollision(xRight, yvar, &collider, 0);
        if ((collider.effects & filter) == EFFECT_SOLID) {
            collisions++;
        }

        CheckCollision(xLeft, yvar, &collider, 0);
        if ((collider.effects & filter) == EFFECT_SOLID) {
            collisions++;
        }

        if (collisions != 0) {
            return i + 1;
        }
    }

    return 0;
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A5208, func_060A5208);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A54F0, func_060A54F0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A5884, func_060A5884);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A59A8, func_060A59A8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A5AD4, func_060A5AD4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A5BE8, func_060A5BE8);
void func_060A6624(u16 arg0) {
    s32 xOffset;

    xOffset = 3;
    if (PLAYER.facingLeft) {
        xOffset = -3;
    }
    PLAYER.posY.i.hi = PLAYER.posY.i.hi;
    PLAYER.posX.i.hi += xOffset;
    RicCreateEntFactoryFromEntity(g_CurrentEntity, 0x10004U, 0);
    PLAYER.posY.i.hi = PLAYER.posY.i.hi;
    PLAYER.posX.i.hi -= xOffset;
    if (arg0 & 1) {
        func_0600FB0C(3);
        PlaySfx(0x644);
    }
    if (arg0 & 2) {
        PLAYER.velocityX = 0;
        PLAYER.velocityY = 0;
    }
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A66C8, func_060A66C8);

enum MariaInputChecks {
    CHECK_GROUND = 1,
    CHECK_FALL = 4,
    CHECK_FACING = 8,
    CHECK_JUMP = 0x10,
    CHECK_CRASH = 0x40,
    CHECK_80 = 0x80,
    CHECK_GRAVITY_HIT = 0x200,
    CHECK_ATTACK = 0x1000,
    CHECK_CROUCH = 0x2000,
    CHECK_GRAVITY_FALL = 0x8000,
    CHECK_GRAVITY_JUMP = 0x10000,
    CHECK_GROUND_AFTER_HIT = 0x20000,
    CHECK_SLIDE = 0x40000,
    CHECK_UNK = 0x80000
};

#define MariaSetSpeedX(speed)                                                  \
    do {                                                                       \
        s32 _tmp_speed = (speed);                                              \
        if (g_CurrentEntity->facingLeft == 1)                                  \
            _tmp_speed = -_tmp_speed;                                          \
        g_CurrentEntity->velocityX = _tmp_speed;                               \
    } while (0)

void MariaStepWalk(void) {
    // CHECK_UNK extra
    if (!MariaCheckInput(CHECK_UNK | CHECK_FALL | CHECK_FACING | CHECK_JUMP |
                         CHECK_CRASH | CHECK_ATTACK | CHECK_CROUCH)) {
        MariaDecelerateX(FIX(0.15625)); // altered
        if (MariaCheckFacing() == 0) {
            MariaSetStand(0);
            return;
        }
        if (PLAYER.step_s != 0) {
            if (PLAYER.step_s) {
            }
        } else {
            MariaSetSpeedX(FIX(1.59375)); // altered
        }
    }
}

void func_060A6A94(void) {
    s32 velocityX;

    if (g_Player.unk7A != 0) {
        func_060A926C(0);
        return;
    }

    g_Player.timers[8] = 8;
    g_Player.timers[1] = 8;

    if (MariaCheckInput(0x8305C) == 0) {
        MariaDecelerateX(FIX(0.15625));
        if (MariaCheckFacing() == 0) {
            RicSetStand(PLAYER.velocityX >> 1);
            if (g_Player.timers[0xB] == 0 && !(g_Player.vram_flag & 0xC)) {
                if (g_Player.vram_flag & 0x20) {
                    RicSetAnimation(g_MariaAnimWalkStopFacingBitSet);
                } else {
                    RicSetAnimation(g_MariaAnimWalkStopFacingBitClear);
                }
                RicCreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
            }
        } else if (PLAYER.step_s == 0) {
            velocityX = FIX(2.8125);
            if (g_CurrentEntity->facingLeft == 1) {
                velocityX = -velocityX;
            }
            g_CurrentEntity->velocityX = velocityX;
        }
    }
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A6B90, func_060A6B90);
void func_060A70B4(void) {
    if (MariaCheckInput(CHECK_GROUND | CHECK_FACING | 0x20 | CHECK_ATTACK |
                        CHECK_GRAVITY_FALL) == 0) {
        MariaDecelerateX(FIX(0.078125));
        if (PLAYER.step_s == 0) {
            if ((g_Player.timers[MARIA_PL_T_5] != 0) &&
                ((g_Player.padTapped & PAD_CROSS) != 0)) {
                func_060A9474();
                return;
            }
            if (MariaCheckFacing() != 0) {
                MariaSetSpeedX(FIX(0.9375));
            }
        }
    }
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A714C, func_060A714C);
void func_060A7508(void) {
    Entity* entity;
    s16 attackerOffX;
    s16 playerOffX;
    s16 distance;

    entity = PLAYER.unkB4;
    if (entity->facingLeft) {
        attackerOffX = -entity->hitboxOffX;
    } else {
        attackerOffX = entity->hitboxOffX;
    }

    if (PLAYER.facingLeft) {
        playerOffX = -PLAYER.hitboxOffX;
    } else {
        playerOffX = PLAYER.hitboxOffX;
    }

    distance = playerOffX + PLAYER.posX.i.hi - entity->posX.i.hi - attackerOffX;
    if (ABS(distance) < 16 && entity->velocityX != 0) {
        if (entity->velocityX < 0) {
            PLAYER.entityRoomIndex = 0;
        } else {
            PLAYER.entityRoomIndex = 1;
        }
        return;
    }

    if (distance < 0) {
        PLAYER.entityRoomIndex = 0;
    } else {
        PLAYER.entityRoomIndex = 1;
    }
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A75AC, func_060A75AC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A7DF4, func_060A7DF4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A7F70, func_060A7F70);
// Maria's RicStepStandInAir
void func_060A8248(void) {
    s16 palettes[] = {0, 20, 21, 22};

    if (PLAYER.step_s == 0) {
        PLAYER.velocityY += FIX(0.21875);
        if (PLAYER.velocityY > 0) {
            PLAYER.velocityY = 0;
            PLAYER.step_s = 1;
        }
    } else {
        PLAYER.palette = palettes[PLAYER.poseTimer & 3];
        if (g_Player.unk4E != 0) {
            g_Player.unk46 = 0;
            RicSetStep(MARIA_PL_S_JUMP);
            RicSetAnimation(&g_MariaAnimFall);
            g_Player.unk44 = 0;
            PLAYER.palette = 0;
        }
    }

    if (g_Player.unk72 != 0) {
        PLAYER.velocityY = 0;
    }
}

// Maria's RicStepEnableFlameWhip
void func_060A8308(void) {
    if (PLAYER.animCurFrame == 181 && PLAYER.poseTimer == 1) {
        RicCreateEntFactoryFromEntity(g_CurrentEntity, MARIA_BP_35, 0);
        PlaySfx(0x62F);
    }

    if (PLAYER.poseTimer < 0) {
        RicSetStand(0);
        g_Player.unk46 = 0;
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(MARIA_BP_RIC_BLINK, 0x45), 0);
        g_Player.timers[MARIA_PL_T_POISON] = 0x800;
    }

    if (!(g_Player.vram_flag & TOUCHING_GROUND)) {
        RicSetFall();
        g_Player.unk46 = 0;
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(MARIA_BP_RIC_BLINK, 0x45), 0);
        g_Player.timers[MARIA_PL_T_POISON] = 0x800;
    }
}

// func_060A83C8
void RicStepHydrostorm(void) {
    if (PLAYER.poseTimer < 0) {
        RicSetStand(0);
        g_Player.unk46 = 0;
    }

    if ((g_Player.vram_flag & TOUCHING_GROUND) == 0) {
        RicSetFall();
        g_Player.unk46 = 0;
    }
}

// func_060A841C
void RicStepGenericSubwpnCrash(void) {
    if (g_Player.unk4E) {
        RicSetStand(0);
        g_Player.unk46 = 0;
    }

    if (!(g_Player.vram_flag & TOUCHING_GROUND)) {
        RicSetFall();
        g_Player.unk46 = 0;
    }
}

void func_060A8470(void) {
    s32 timer;

    if (PLAYER.step_s == 0) {
        DAT_060D2918 = 0x200;
        PLAYER.step_s++;
    } else {
        MariaCheckFacing();
        timer = DAT_060D2918 - 1;
        DAT_060D2918 = timer;
        if (timer == 0) {
            g_Player.unk46 = 0;
            RicSetStand(0);
            g_Player.unk4E = 1;
        }
    }

    if (g_Player.padTapped & PAD_CROSS) {
        func_060A9474();
        g_Player.unk46 = 0;
        g_Player.unk4E = 1;
        DAT_060D2918 = 0;
    }

    if (!(g_Player.vram_flag & TOUCHING_GROUND)) {
        RicSetFall();
        g_Player.unk46 = 0;
        g_Player.unk4E = 1;
        DAT_060D2918 = 0;
    }
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8534, func_060A8534);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8860, func_060A8860);
void func_060A8A38(void) {
    s32 distance;

    if (g_CurrentRoom.stageID == STAGE_TOP) {
        distance = (g_Tilemap.left << 8) + g_PlayerX;
        if (distance < 0) {
            distance = -distance;
        }
        if ((distance - 0x1F8F) > 0) {
            PLAYER.posX.i.hi--;
        }

        distance = (g_Tilemap.left << 8) + g_PlayerX;
        if (distance < 0) {
            distance = -distance;
        }
        if ((distance - 0x1F8F) < 0) {
            PLAYER.posX.i.hi++;
        }
    }

    if (g_CurrentRoom.stageID == STAGE_RTOP) {
        distance = (g_Tilemap.left << 8) + g_PlayerX;
        if (distance < 0) {
            distance = -distance;
        }
        if ((distance - 0x20EE) > 0) {
            PLAYER.posX.i.hi--;
        }

        distance = (g_Tilemap.left << 8) + g_PlayerX;
        if (distance < 0) {
            distance = -distance;
        }
        if ((distance - 0x20EE) < 0) {
            PLAYER.posX.i.hi++;
        }
    }
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8AE8, func_060A8AE8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8C14, func_060A8C14);
void func_060A8E34(void) {
    MariaDecelerateX(FIX(0.140625));

    if (g_Entities->poseTimer < 0 ||
        (g_Entities->velocityX >= 0 ? g_Entities->velocityX <= 0x7FFF
                                    : -g_Entities->velocityX <= 0x7FFF)) {
        g_Player.unk46 = 0;
        RicSetStand(0);
        return;
    }

    if (g_Entities->pose > 0x11U && !(g_Player.vram_flag & 1)) {
        g_Player.unk46 = 0;
        RicSetFall();
        return;
    }

    if (!(g_GameTimer & 3) && g_Entities->pose <= 0x11U &&
        (g_Player.vram_flag & 1)) {
        RicCreateEntFactoryFromEntity(g_CurrentEntity, 0x20018U, 0);
    }

    if (g_Entities->pose == 0x12 && g_Entities->poseTimer == 1 &&
        (g_Player.vram_flag & 1)) {
        RicCreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
    }
}

void func_060A8F2C(void) {
    bool loadAnim;

    loadAnim = false;
    g_Player.high_jump_timer++;
    switch (PLAYER.step_s) {
    case 0:
        if (g_Player.padPressed & (PAD_LEFT | PAD_RIGHT)) {
            if (PLAYER.facingLeft) {
                if (!(g_Player.padPressed & PAD_LEFT)) {
                    MariaDecelerateX(FIX(0.078125));
                }
            } else {
                if (!(g_Player.padPressed & PAD_RIGHT)) {
                    MariaDecelerateX(FIX(0.078125));
                }
            }
        } else {
            MariaDecelerateX(FIX(0.078125));
        }

        if (g_Player.vram_flag & TOUCHING_CEILING) {
            func_060A6624(3);
            g_Player.high_jump_timer = 0;
            PLAYER.step_s = 2;
        } else if (g_Player.high_jump_timer > 0x1C) {
            PLAYER.step_s = 1;
            PLAYER.velocityY = FIX(-6);
        }
        break;
    case 1:
        if (g_Player.vram_flag & TOUCHING_CEILING) {
            PLAYER.step_s = 2;
            func_060A6624(3);
            g_Player.high_jump_timer = 0;
        } else {
            PLAYER.velocityY += FIX(0.375);
            if (PLAYER.velocityY > FIX(0.5)) {
                loadAnim = true;
            }
        }
        break;
    case 2:
        if (g_Player.high_jump_timer > 4) {
            loadAnim = true;
        }
        break;
    }

    if (loadAnim) {
        RicSetAnimation(&g_MariaAnimFall);
        RicSetStep(4);
    }
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9064, func_060A9064);

void func_060A9130(void) { RicSetStep(0xf0); }

// func_060A8EB8
void MariaSetInit(s32 step_s) {
    PLAYER.step = MARIA_PL_S_INIT;
    PLAYER.step_s = step_s;
    PLAYER.pose = PLAYER.poseTimer = 0;
    if (step_s & 1) {
        PLAYER.anim = D_80155950;
    } else {
        PLAYER.anim = D_8015591C;
    }
}

void func_060A9194(s32 arg0, s32 arg1) {
    AnimationFrame* anim = ric_anim_crouch;

    RicSetStep(MARIA_PL_S_CROUCH);
    g_Player.unk44 = 0;
    PLAYER.velocityX = arg1;
    PLAYER.velocityY = 0;

    if (arg0 == 1) {
        PLAYER.step_s = 4;
    } else if (arg0 == 2) {
        PLAYER.step_s = 1;
    } else if (arg0 == 3) {
        PLAYER.step_s = 0;
        anim = ric_anim_land_from_air_run;
    }

    RicSetAnimation(anim);
}

// func_060A9210
// new alt animation
void RicSetStand(s32 velocityX) {
    PLAYER.velocityX = velocityX;
    PLAYER.velocityY = 0;
    g_Player.unk44 = 0;

    RicSetStep(MARIA_PL_S_STAND);

    if (g_Player.vram_flag & IN_AIR_OR_EDGE)
        RicSetAnimation(ric_anim_stand_alt);
    else
        RicSetAnimation(ric_anim_stand);
}

void MariaSetWalk(s32 arg0) {
    if (g_Player.timers[MARIA_PL_T_8] && !g_Player.unk7A) {
        func_060A9304();
        return;
    }
    g_Player.timers[MARIA_PL_T_CURSE] = 8;
    if (g_Player.timers[MARIA_PL_T_CURSE]) {
        g_Player.timers[MARIA_PL_T_8] = 12;
    }
    g_Player.timers[MARIA_PL_T_CURSE] = 12;
    g_Player.unk44 = 0;
    RicSetStep(MARIA_PL_S_WALK);
    RicSetAnimation(ric_anim_walk);
    MariaSetSpeedX(FIX(1.59375));
    PLAYER.velocityY = 0;
}
void func_060A9304(void) {
    if (g_Player.unk7A) {
        MariaSetWalk(0);
        return;
    }

    g_Player.unk44 = 0;
    RicSetStep(MARIA_PL_S_RUN);
    RicSetAnimation(ric_anim_run);
    MariaSetSpeedX(FIX(2.8125));
    g_Player.timers[MARIA_PL_T_RUN] = 40;
    PLAYER.velocityY = 0;
    RicCreateEntFactoryFromEntity(
        g_CurrentEntity, FACTORY(MARIA_BP_SMOKE_PUFF, 5), 0);
}

// _RicSetFall

void func_060A939C(void) {
    if (g_Player.prev_step != 0x19 && g_Player.prev_step != 0x17) {
        g_Entities->velocityX = 0;
    }
    if (g_Player.prev_step != 1 && g_Player.prev_step != 0x19) {
        RicSetAnimation(&g_MariaAnimFall);
    }
    if (g_Player.prev_step == 0x19) {
        g_Player.unk44 = 0x10;
    }
    RicSetStep(3);
    g_Entities->velocityY = FIX(2);
    g_Player.timers[5] = 8;
    g_Player.timers[6] = 8;
    g_Player.timers[1] = 0;
    g_Player.timers[8] = 0;
    if (g_Player.prev_step == 0x17) {
        g_Player.timers[6] = 0;
        g_Player.timers[5] = 0;
        g_Entities->pose = 2;
        g_Entities->poseTimer = 0x10;
        g_Entities->velocityX /= 2;
    }
}
void RicSetFall(void);

s32 func_060A9474(void) {
    PlayerState* player = &g_Player;
    s32 facing;
    s32 velocityX;

    if (player->unk72 != 0) {
        RicSetFall();
        return;
    }

    facing = MariaCheckFacing();
    if (facing != 0 || g_Entities->step == 0x17) {
        RicSetAnimation(&g_MariaAnim_060C2ADC);
        if (g_Entities->step == 0x19) {
            velocityX = FIX(2.8125);
            if (g_CurrentEntity->facingLeft == 1) {
                velocityX = -velocityX;
            }
            g_CurrentEntity->velocityX = velocityX;
            player->unk44 = 0x10;
        } else {
            velocityX = FIX(1.59375);
            if (g_CurrentEntity->facingLeft == 1) {
                velocityX = -velocityX;
            }
            g_CurrentEntity->velocityX = velocityX;
            player->unk44 = 0;
        }
    } else {
        RicSetAnimation(&g_MariaAnim_060C2B18);
        g_Entities->velocityX = facing;
        player->unk44 = 4;
    }

    RicSetStep(4);
    g_Entities->velocityY = FIX(-4);
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A955C, func_060A955C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9608, func_060A9608);

// func_060A96D4
s32 MariaCheckSubwpnChainLimit(s16 subwpnId, s16 limit) {
    Entity* entity;
    s32 i;
    s32 nFound;
    s32 nEmpty;

    // Iterate through entities 32-48 (which hold subweapons)
    // Any that match the proposed ID increments the count.
    // If at any point the count reaches the limit, return -1.
    entity = &g_Entities[32];
    for (i = 0, nFound = 0, nEmpty = 0; i < 16; i++, entity++) {
        if (!entity->entityId) {
            nEmpty++;
        }
        if (entity->ext.subweapon.subweaponId &&
            entity->ext.subweapon.subweaponId == subwpnId) {
            nFound++;
        }
        if (nFound >= limit) {
            return -1;
        }
    }
    // This will indicate that there is an available entity slot
    // to hold the subweapon we're trying to spawn.
    // At the end, if this is zero, there are none available so return
    // -1 to indicate there is no room for the proposed subweapon.
    if (nEmpty) {
        return 0;
    }
    return -1;
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A973C, func_060A973C);

int func_060A9958(int param_1) {
    int iVar2;

    iVar2 = (int)(char)g_MariaInitialAfterimageTimers[param_1];
    if (!(iVar2 <= g_Status.mp)) {
        iVar2 = 0;
    } else {
        g_Status.mp -= iVar2;
    }
    return iVar2;
}

const u32 pad_060a998c = 0xAAAAAAAB;

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9990, func_060A9990);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9BC4, func_060A9BC4);

s32 func_060A9CE8(void) {
    s32 pad[5];
    return 1;
}

void func_060A9CF8(void) { RicSetStep(0x16); }

void func_060A9D10(void) {
    MariaCheckFacing();
    RicSetStep(MARIA_PL_S_SLIDE);
    RicSetAnimation(&g_MariaAnim_060C2E4C);
    g_CurrentEntity->velocityY = 0;
    MariaSetSpeedX(FIX(6.625));
    func_060AA948();
    RicCreateEntFactoryFromEntity(g_CurrentEntity, MARIA_BP_25, 0);
    RicCreateEntFactoryFromEntity(g_CurrentEntity, MARIA_BP_SKID_SMOKE, 0);
    PlaySfx(0x617);
    g_Player.timers[MARIA_PL_T_12] = 4;
}
void func_060A9DA4(void) {
    g_Player.unk44 = 0;
    RicSetStep(MARIA_PL_S_SLIDE_KICK);
    RicSetAnimation(&g_MariaAnim_060C2F8C);
    g_CurrentEntity->velocityY = FIX(-2);
    MariaSetSpeedX(FIX(6.625));
    func_060AA948();
    RicCreateEntFactoryFromEntity(g_CurrentEntity, MARIA_BP_25, 0);
    PlaySfx(0x71D);
    g_Player.timers[MARIA_PL_T_12] = 4;
    RicCreateEntFactoryFromEntity(g_CurrentEntity, MARIA_BP_31, 0);
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9E40, func_060A9E40);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9EC4, func_060A9EC4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9F84, func_060A9F84);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA0A0, func_060AA0A0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA260, func_060AA260);

// RicSetStep
void RicSetStep(s16 step) {
    PLAYER.step = step;
    PLAYER.step_s = 0;
}

void RicSetAnimation(AnimationFrame* anim) {
    g_CurrentEntity->anim = anim;
    g_CurrentEntity->poseTimer = 0;
    g_CurrentEntity->pose = 0;
}

#include "update_entity_sprite.h"

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA608, func_060AA608);

// func_060AA754
void MariaDecelerateX(s32 speed) {
    if (g_CurrentEntity->velocityX < 0) {
        g_CurrentEntity->velocityX += speed;
        if (g_CurrentEntity->velocityX > 0) {
            g_CurrentEntity->velocityX = 0;
        }
    } else {
        g_CurrentEntity->velocityX -= speed;
        if (g_CurrentEntity->velocityX < 0)
            g_CurrentEntity->velocityX = 0;
    }
}

// func_060AA784
void RicDecelerateY(s32 speed) {
    if (g_CurrentEntity->velocityY < 0) {
        g_CurrentEntity->velocityY += speed;
        if (g_CurrentEntity->velocityY > 0) {
            g_CurrentEntity->velocityY = 0;
        }
    } else {
        g_CurrentEntity->velocityY -= speed;
        if (g_CurrentEntity->velocityY < 0) {
            g_CurrentEntity->velocityY = 0;
        }
    }
}

// func_060AA7B4
s32 RicCheckFacing(void) {
    if (g_Player.unk44 & 2) {
        return 0;
    }

    if (PLAYER.facingLeft == 1) {
        if (g_Player.padPressed & PAD_RIGHT) {
            PLAYER.facingLeft = 0;
            g_Player.unk4C = 1;
            return -1;
        } else if (g_Player.padPressed & PAD_LEFT) {
            return 1;
        }
    } else {
        if (g_Player.padPressed & PAD_RIGHT) {
            return 1;
        }
        if (g_Player.padPressed & PAD_LEFT) {
            PLAYER.facingLeft = 1;
            g_Player.unk4C = 1;
            return -1;
        }
    }
    return 0;
}

// func_060AA830
int func_8015CAAC(s32 speed) {
    if (PLAYER.entityRoomIndex == 1)
        speed = -speed;
    PLAYER.velocityX = speed;
    return speed;
}

// func_060AA854
void RicSetInvincibilityFrames(s32 kind, s16 invincibilityFrames) {
    if (!kind) {
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(MARIA_BP_RIC_BLINK, 0x15), 0);
        if (g_Player.timers[MARIA_PL_T_INVINCIBLE_SCENE] <=
            invincibilityFrames) {
            g_Player.timers[MARIA_PL_T_INVINCIBLE_SCENE] = invincibilityFrames;
        }
    } else if (g_Player.timers[MARIA_PL_T_INVINCIBLE] <= invincibilityFrames) {
        g_Player.timers[MARIA_PL_T_INVINCIBLE] = invincibilityFrames;
    }
}

// DisableAfterImage

void func_060AA8AC(s32 resetAnims, s32 arg1) {
    Entity* entity;
    Primitive* prim;
    s32 i;

    if (resetAnims != 0) {
        g_Entities[1].ext.afterImage.resetFlag = 1;
        entity = &g_Entities[1];
        i = 0;
        for (; i <= 2; i++) {
            entity->animCurFrame = 0;
            entity->unk0->flags = 0;
            entity++;
        }

        prim = &g_PrimBuf[g_Entities[1].primIndex];
        while (prim != NULL) {
            prim->x1 = 0;
            prim = prim->next;
        }
    }

    g_Entities[1].ext.afterImage.disableFlag = 1;
    g_Entities[1].ext.afterImage.index = 10;

    if (arg1 != 0) {
        if (arg1 <= 3) {
            g_Player.timers[MARIA_PL_T_AFTERIMAGE_DISABLE] = 4;
        } else {
            g_Player.timers[MARIA_PL_T_AFTERIMAGE_DISABLE] = arg1;
        }
    }
}

// func_060AA948
void func_8015CC28(void) {
    g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag =
        g_Entities[E_AFTERIMAGE_1].ext.afterImage.resetFlag =
            g_Entities[E_AFTERIMAGE_1].ext.afterImage.index =
                g_Entities[E_AFTERIMAGE_1].ext.afterImage.timer = 0;
}

void func_060AA974(void) { func_060AA8AC(1, 1); }

void func_060AA9EC(void) {
    g_CurrentEntity = &PLAYER;
    if (g_unkGraphicsStruct.unk28 == 4) {
        func_060aa608(g_MariaFrameProperties, g_MariaAnimationGroups);
    }
}

s32 func_060AAA2C(void) {
    s32 ret = 0;

    if (g_Player.unk3FC > 300) {
        ret = 3;
    } else if (g_Player.unk3FC > 200) {
        ret = 2;
    } else if (g_Player.unk3FC > 100) {
        ret = 1;
    }

    return ret;
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AAA68, func_060AAA68);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AB088, func_060AB088);

// func_060AB258
void RicGetPlayerSensor(Collider* col) {
    col->unk14 = g_RicSensorsWall[0].x;
    col->unk1C = g_RicSensorsWall[0].y;
    col->unk18 = g_RicSensorsFloor[1].y - FIX(1);
    col->unk20 = g_RicSensorsCeiling[1].y + FIX(1);
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AB294, func_060AB294);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AB6C4, func_060AB6C4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ABAA4, func_060ABAA4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ABC54, func_060ABC54);

#define E_NONE 0
// func_060AB980
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

// func_060AB9C0
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

#define LEN(x) ((s32)(sizeof(x) / sizeof(*(x))))
s32 D_80174F80[11];
// func_060ABA08
// extra loop vs. ric version
void func_8015F9F0(Entity* entity) {
    s32 i;
    s32 enemyId;
    if (entity < &g_Entities[32]) {
        for (i = 0;; i++) {
            for (enemyId = 3; enemyId < LEN(D_80174F80) - 4; enemyId++) {
                if (D_80174F80[enemyId] == i) {
                    D_80174F80[enemyId] = i + 1;
                    entity->enemyId = enemyId;
                    return;
                }
            }
        }
    } else {
        for (i = 0;; i++) {
            for (enemyId = 7; enemyId < LEN(D_80174F80); enemyId++) {
                if (D_80174F80[enemyId] == i) {
                    D_80174F80[enemyId] = i + 1;
                    entity->enemyId = enemyId;
                    return;
                }
            }
        }
    }
}

// func_060ABEF8
void func_8015FA5C(s32 arg0) {
    g_MariaEmptyAnimMarker = g_MariaBlueprintColors[arg0][0];
    D_80174FB0 = g_MariaBlueprintColors[arg0][1];
    D_80174FB4 = g_MariaBlueprintColors[arg0][2];
    D_80174FB8 = g_MariaBlueprintColors[arg0][3];
}

void func_060ABF40(Entity* self) {
    SubweaponDef* subweaponDef;

    subweaponDef = &DAT_060C1B02[self->ext.subweapon.subweaponId];
    if (g_Player.timers[13] != 0) {
        self->attack = subweaponDef->attack * 2;
    } else {
        self->attack = subweaponDef->attack;
    }
    self->attackElement = subweaponDef->attackElement;
    self->hitboxState = subweaponDef->hitboxState;
    self->nFramesInvincibility = subweaponDef->nFramesInvincibility;
    self->stunFrames = subweaponDef->stunFrames;
    self->hitEffect = subweaponDef->hitEffect;
    self->entityRoomIndex = subweaponDef->entityRoomIndex;
    self->attack = func_0606F328(self->attack);
    func_060ABE94(self);
}

void func_060ABFF0(Entity* entity, MariaAttackDef* def) {
    entity->attack = def->attack;
    entity->hitboxWidth = def->hitboxWidth;
    entity->hitboxHeight = def->hitboxHeight;
    entity->hitboxOffX = def->hitboxOffX;
    entity->hitboxOffY = def->hitboxOffY;
    entity->attackElement = def->attackElement;
    entity->hitboxState = def->hitboxState;
    entity->nFramesInvincibility = def->nFramesInvincibility;
    entity->stunFrames = def->stunFrames;
    entity->hitEffect = def->hitEffect;
    entity->entityRoomIndex = def->entityRoomIndex;
    entity->attack = func_0606F328(entity->attack);
    func_060ABE94(entity);
}
s32 func_060AC09C(
    SubweaponDef* actualSubweapon, s32 isItemCrash, s32 useHearts) {
    SubweaponDef* subweapon;

    if (isItemCrash == 0) {
        *actualSubweapon = g_MariaSubweaponDefs[g_Status.subWeapon];
        if (g_Status.hearts >= actualSubweapon->heartCost) {
            if (useHearts != 0) {
                g_Status.hearts -= actualSubweapon->heartCost;
            }
            return g_Status.subWeapon;
        }
    } else {
        subweapon = &g_MariaSubweaponDefs[g_Status.subWeapon];
        *actualSubweapon = g_MariaSubweaponDefs[subweapon->crashId];
        if (g_Status.hearts >= actualSubweapon->heartCost) {
            if (useHearts != 0) {
                g_Status.hearts -= actualSubweapon->heartCost;
            }
            return g_Status.subWeapon;
        }
    }
    return -1;
}
s32 func_060AC148(Primitive* prim, s16 posX, s16 posY) {
    s16 offset;
    s16 xOffset;
    u16* texture;
    u16* frameWord = (u16*)&prim->x1;
    u8 frame = ((u8*)frameWord)[1];

    if (frame >= 3) {
        offset = 4;
    } else {
        offset = 6;
    }

    if (frame == 6) {
        return -1;
    }

    xOffset = offset | 1;
    prim->x0 = posX - xOffset;
    prim->y0 = posY - offset;
    prim->x2 = posX + xOffset;
    prim->y2 = posY + offset;

    texture =
        DAT_0605aec0[(u16)DAT_060C6D7C + g_MariaPrimitiveSizeIndices[frame]];
    prim->unk8 = texture[0];
    prim->unkA = texture[1];

    prim->y1++;
    if (!(prim->y1 & 1)) {
        (*frameWord)++;
    }
    return 0;
}

const u16 pad_060AC1F8[] = {0xAAAA, 0xAAAB};
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC1FC, func_060AC1FC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC458, func_060AC458);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC604, func_060AC604);
void func_060AC850(void) {
    Entity* entity;
    s32 i;

    if (PLAYER.unk0 != NULL) {
        g_CurrentEntity = entity = &g_Entities[UNK_ENTITY_4];
        i = UNK_ENTITY_4;
        do {
            if (!(entity->flags & FLAG_UNK_20000)) {
                DestroyEntity(entity);
            }
            if ((entity->flags & FLAG_UNK_02000000) && (entity->step != 0)) {
                entity->flags |= FLAG_UNK_00200000;
                entity->pfnUpdate(entity);
                entity->flags &= ~FLAG_UNK_00200000;
            }
            i++;
            g_CurrentEntity++;
            entity++;
        } while (i <= 0x3F);
        ((s32(*)(s32, s32))func_060AA8AC)(1, 3);
    }
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC90C, func_060AC90C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC9E0, func_060AC9E0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ACD98, func_060ACD98);
void func_060ACE84(Entity* entity) {
    extern void MariaSetSubweaponParams(Entity*);

    if (g_Entities[PLAYER_CHARACTER].step != 26) {
        DestroyEntity(entity);
        return;
    }
    entity->posX.i.hi = g_Entities[PLAYER_CHARACTER].posX.i.hi;
    entity->posY.i.hi = g_Entities[PLAYER_CHARACTER].posY.i.hi;
    entity->facingLeft = g_Entities[PLAYER_CHARACTER].facingLeft;
    if (entity->step == 0) {
        entity->flags = (FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED) |
                        FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->hitboxOffX = 25;
        entity->hitboxWidth = 11;
        entity->hitboxHeight = 9;
        entity->ext.subweapon.subweaponId = 23;
        MariaSetSubweaponParams(entity);
        entity->step++;
    }
    if (g_Entities[PLAYER_CHARACTER].animCurFrame == 140) {
        entity->hitboxOffY = 0;
    }
    if (g_Entities[PLAYER_CHARACTER].animCurFrame == 141) {
        entity->hitboxOffY = 12;
    }
    if (entity->hitFlags) {
        g_Player.unk44 |= 0x80;
    } else {
        g_Player.unk44 &= ~0x80;
    }
    entity->hitFlags = 0;
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ACF8C, func_060ACF8C);
void func_060AD048(Entity* arg0) {
    extern void MariaSetSubweaponParams(Entity*);

    if (PLAYER.step != 8) {
        DestroyEntity(arg0);
        return;
    }

    arg0->posX.i.hi = PLAYER.posX.i.hi;
    arg0->posY.i.hi = PLAYER.posY.i.hi;
    arg0->facingLeft = PLAYER.facingLeft;

    if (arg0->step == 0) {
        arg0->flags = 0x04060000;
        arg0->hitboxOffX = 7;
        arg0->hitboxOffY = -0x1A;
        arg0->hitboxWidth = 0xA;
        arg0->hitboxHeight = 0xC;
        arg0->ext.subweapon.subweaponId = 0x16;
        MariaSetSubweaponParams(arg0);
        arg0->step++;
    }
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AD0E8, func_060AD0E8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AD248, func_060AD248);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AD3A8, func_060AD3A8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AD7D8, func_060AD7D8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AE014, func_060AE014);
void func_060AE2C8(Entity* self) {
    switch (self->step) {
    case 0:
        self->unk0 = CreateSpriteObject(
            g_EntitySpriteBank01.allocationIndex, g_EntitySpriteBank01.flags,
            g_EntitySpriteBank01.images, 5);
        if (self->unk0 != NULL) {
            self->ext.spriteEntity.frames = DAT_06045E14;
            self->unk0->zPriority = g_Entities->zPriority + 4;
            self->animSet = 2;
            self->anim = &DAT_060C2408;
            self->flags = 0x00170000;
            self->velocityY = (MTH_GetRand() & 0x3FFF) - FIX(1);
            self->step++;
        } else {
            DestroyEntity(self);
        }
        break;

    case 1:
        if (self->pose == 6) {
            if (self->poseTimer == 1 && (MTH_GetRand() & 1)) {
                RicCreateEntFactoryFromEntity(self, 4, 0);
            }
        }
        self->posY.val += self->velocityY;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AE3C0, func_060AE3C0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AE730, func_060AE730);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AE8D8, func_060AE8D8);

void func_060AEAB8() {}

#define E_WEAPON 0x10
#define STAGE_ENTITY_START 64

// func_060AEAC4
bool func_80162E9C(Entity* entity) {
    Entity* e;
    s32 i;
    s16 objId;
    s16 params;

    objId = entity->entityId;
    params = entity->params;
    for (e = &g_Entities[E_WEAPON], i = E_WEAPON; i < STAGE_ENTITY_START; e++,
        i++) {
        if (objId == e->entityId && params == e->params && e != entity) {
            return true;
        }
    }
    return false;
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AEB18, func_060AEB18);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AEFB4, func_060AEFB4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AF17C, func_060AF17C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AF444, func_060AF444);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AFAB4, func_060AFAB4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AFBA4, func_060AFBA4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B0220, func_060B0220);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B0474, func_060B0474);

void func_060B099C(Entity* self) { DestroyEntity(self); }

void func_060B09B4() {}

const u16 pad_60B09BC = 0;

s32 func_060B09C0() { return 0; }

const u16 pad_60B09C8 = 0;

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B09CC, func_060B09CC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B1474, func_060B1474);
void func_060B18C8(Entity* entity) {
    SpriteObject* sprite;

    if (entity->step == 0) {
        sprite = CreateSpriteObject(
            g_EntitySpriteBank09.allocationIndex, (u16)(DAT_06046C02 + 0x1C),
            g_EntitySpriteBank09.images, 1);
        entity->unk0 = sprite;
        if (sprite != NULL) {
            entity->ext.spriteEntity.frames = &g_Stage02OpaquePuffFrameData1;
            entity->unk0->zPriority = PLAYER.zPriority + 2;
            entity->anim = &g_MariaEntity87Anim0;
            entity->flags = 0x08100000;
            entity->posY.i.hi -= 6;
            entity->velocityY = FIX(-0.5);
            func_060ABFF0NoInline(entity, &g_MariaEntity87CombatConfig);
            PlaySfx(0x65C);
            entity->step++;
        } else {
            DestroyEntity(entity);
            return;
        }
    } else {
        if (entity->poseTimer < 0) {
            DestroyEntity(entity);
            return;
        }
        entity->posY.val += entity->velocityY;
    }
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B199C, func_060B199C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B1A58, func_060B1A58);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B1E78, func_060B1E78);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B2474, func_060B2474);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B2604, func_060B2604);

// func_060B295C
void MariaEntityCrashReboundStoneParticles(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->ext.subweapon.subweaponId = PL_W_CRASH_REBOUND_STONE;
        MariaSetSubweaponParams(entity);
        entity->hitboxWidth = 5;
        entity->hitboxHeight = 4;
        entity->step++;
        break;
    case 1:
        entity->ext.subweapon.timer++;
        if (entity->ext.subweapon.timer > 3) {
            DestroyEntity(entity);
        }
        break;
    }
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B29D4, func_060B29D4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B2E7C, func_060B2E7C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B2FC8, func_060B2FC8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B30BC, func_060B30BC);

void func_060B3678() {}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B3684, func_060B3684);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B382C, func_060B382C);

// func_060B4470
void MariaEntityStopwatchCrashLightning(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->ext.subweapon.subweaponId = PL_W_30;
        MariaSetSubweaponParams(entity);
        entity->hitboxWidth = 10;
        entity->hitboxHeight = 8;
        entity->step++;
        break;
    case 1:
        entity->ext.subweapon.timer++;
        if (entity->ext.subweapon.timer > 4) {
            DestroyEntity(entity);
        }
        break;
    }
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B44E8, func_060B44E8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B4598, func_060B4598);

void func_060B46A0(Entity* self) { DestroyEntity(self); }

// should be able to remove when next function is decompiled
const u16 pad_060B46B8 = 0xAAAA;
const u16 pad_060B46BA = 0xAAAB;

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B46BC, func_060B46BC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B4B80, func_060B4B80);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B4CF4, func_060B4CF4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B5C3C, func_060B5C3C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B5E28, func_060B5E28);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B626C, func_060B626C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B668C, func_060B668C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B6C94, func_060B6C94);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B72B4, func_060B72B4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B776C, func_060B776C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B7A48, func_060B7A48);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B7E08, func_060B7E08);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B7F50, func_060B7F50);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B805C, func_060B805C);

void func_060B82AC() {}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B82B8, func_060B82B8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B85C8, func_060B85C8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B868C, func_060B868C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B89F0, func_060B89F0);

#define EFFECT_SIDE 1 << 1

// func_060B8AC4
s32 func_8016840C(s32 y, s32 x) {
    Collider collider;
    s32 xShift;
    if (g_CurrentEntity->velocityX == 0) {
        return 0;
    }
    CheckCollision(g_CurrentEntity->posX.val + x, g_CurrentEntity->posY.val + y,
                   &collider, 0);
    if (g_CurrentEntity->velocityX > 0) {
        xShift = collider.unk14;
    } else {
        xShift = collider.unk1C;
    }
    if (collider.effects & EFFECT_SIDE) {
        g_CurrentEntity->posX.val += xShift;
        return 2;
    }
    return 0;
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B8B24, func_060B8B24);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B9048, func_060B9048);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B9404, func_060B9404);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B96C0, func_060B96C0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B99A8, func_060B99A8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B9B88, func_060B9B88);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B9D88, func_060B9D88);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B9FE0, func_060B9FE0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BA148, func_060BA148);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BA32C, func_060BA32C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BA4BC, func_060BA4BC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BA6E8, func_060BA6E8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BA914, func_060BA914);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BABE0, func_060BABE0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BAC78, func_060BAC78);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BADA8, func_060BADA8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BAFF0, func_060BAFF0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BB334, func_060BB334);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BB4AC, func_060BB4AC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BB724, func_060BB724);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BB868, func_060BB868);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BBEF8, func_060BBEF8);
Entity* func_060BC024(Entity* self) {
    Entity* entity;
    Entity* last;
    s32 direction;
    s32 count;

    last = NULL;
    direction = -1;
    if (self->facingLeft != 0) {
        direction = 1;
    }

    entity = &g_Entities[0x40];
    count = 0;
    for (; entity != &g_Entities[0xC0]; entity++) {
        if (entity->entityId == 0 || entity->hitboxState == 0) {
            continue;
        }
        if (entity->posX.i.hi < -0x10) {
            continue;
        }
        if (entity->posX.i.hi > 0x150) {
            continue;
        }
        if (entity->posY.i.hi > 0xF0) {
            continue;
        }
        if (entity->posY.i.hi < 0) {
            continue;
        }
        if (entity->hitPoints > 0x6FFF) {
            continue;
        }
        if (entity->flags & 0x80000) {
            count++;
            last = entity;
        } else if ((entity->posX.i.hi - self->posX.i.hi) * direction > 0) {
            entity->flags |= 0x80000;
            return entity;
        }
    }

    if (count != 0) {
        return last;
    }
    return NULL;
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BC0F4, func_060BC0F4);
u16 func_060BC23C(Entity* self) {
    if (self->step > 4) {
        if (self->velocityX != 0) {
            if (self->velocityX < 0) {
                self->facingLeft = 0;
            } else {
                self->facingLeft = 1;
            }
        }
    } else {
        self->ext.bat.batIndex++;
        if ((u16)self->ext.bat.batIndex > 50U) {
            self->ext.bat.batIndex = 0;
            if (ABS(self->ext.bat.randomMovementScaler + PLAYER.posX.i.hi -
                    self->posX.i.hi) <= 29 &&
                ABS(self->ext.bat.angleStep + PLAYER.posY.i.hi -
                    self->posY.i.hi) <= 29) {
                if (self->facingLeft == PLAYER.facingLeft) {
                    self->facingLeft = !self->facingLeft;
                    self->ext.bat.batIndex = 0;
                }
            } else if (self->velocityX != 0) {
                if (self->velocityX < 0) {
                    self->facingLeft = 0;
                } else {
                    self->facingLeft = 1;
                }
            }
        }
    }
    return self->facingLeft;
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BC320, func_060BC320);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BCBD8, func_060BCBD8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BCCE8, func_060BCCE8);
void func_060BCFF4(Entity* arg0) {
    switch (arg0->step) {
    case 0:
        func_060ABFF0NoInline(arg0, &g_MariaEntity060BCFF4CombatConfig);
        arg0->flags = 0x04020000;
        arg0->step++;
        break;
    case 1:
        if (g_Entities->poseTimer < 0) {
            g_Player.timers[0xD] = 0x7D0;
            arg0->step++;
        }
        break;
    default:
        if (g_Player.timers[0xD] == 0) {
            DestroyEntity(arg0);
            return;
        }
        break;
    }

    arg0->posX.i.hi = g_Entities->posX.i.hi;
    arg0->posY.i.hi = g_Entities->posY.i.hi;
    arg0->facingLeft = g_Entities->facingLeft;
    arg0->hitboxOffX = g_Entities->hitboxOffX;
    arg0->hitboxOffY = g_Entities->hitboxOffY;
    arg0->hitboxWidth = g_Entities->hitboxWidth;
    arg0->hitboxHeight = g_Entities->hitboxHeight;
}
typedef struct {
    /* 0x00 */ AnimationFrame* anims[4];
    /* 0x10 */ u16 spriteIds[8];
} MariaEntity060BD0D0Work;

void func_060BD0D0(Entity* self) {
    volatile MariaEntity060BD0D0Work work;

    work.anims[0] = g_MariaEntity060BD0D0Anim0;
    work.anims[1] = g_MariaEntity060BD0D0Anim0;
    work.anims[2] = g_MariaEntity060BD0D0Anim1;
    work.anims[3] = g_MariaEntity060BD0D0Anim2;
    work.spriteIds[0] = 0x100;
    work.spriteIds[1] = 0x104;
    work.spriteIds[2] = 0x108;
    work.spriteIds[3] = 0x10C;
    work.spriteIds[4] = 0x110;
    work.spriteIds[5] = 0x10C;
    work.spriteIds[6] = 0x108;
    work.spriteIds[7] = 0x104;

    DestroyEntity(g_CurrentEntity);
}
void func_060BD150(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = 0x60000;
        func_060ABFF0NoInline(self, &g_MariaEntity060BD150CombatConfig);
        self->ext.et_060BD150.timer = 300;
        RicCreateEntFactoryFromEntity(self, 100, 0);
        self->step++;
        break;

    case 1:
        if (func_060AAA2CNoInline() != 3) {
            self->step++;
        }
        break;

    case 2:
        if (--self->ext.et_060BD150.timer < 0) {
            RicCreateEntFactoryFromEntity(self, 0x10064, 0);
            self->step++;
        }
        break;

    default:
        DestroyEntity(self);
        return;
    }

    if (self->hitFlags) {
        RicCreateEntFactoryFromEntity(self, 100, 0);
        self->hitFlags = 0;
    }

    self->posX.i.hi = g_Entities->posX.i.hi;
    self->posY.i.hi = g_Entities->posY.i.hi;
    self->facingLeft = g_Entities->facingLeft;
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BD244, func_060BD244);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BD474, func_060BD474);

void func_060BD5F0(void) {
    memset(&g_MariaCastleMapState, 0, 4);
    memcpy(CASTLE_MAP_BITMAP, g_MariaCastleMapBitmap, CASTLE_MAP_BITMAP_SIZE);

    func_060BB330();
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BD638, func_060BD638);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BD81C, func_060BD81C);
void func_060BD9E8(u8 walls, u8* dst) {
    u8* p;
    s32 i;

    if (walls & 0x40) {
        p = dst;
        for (i = 0; i < 5; i++) {
            *p++ |= 0x88;
            *p++ |= 0x88;
            *p |= 0x88;
            p += 0x9E;
        }
    }
    if (walls & 0x10) {
        p = dst + 2;
        for (i = 0; i < 5; i++) {
            *p++ |= 0x08;
            *p++ |= 0x88;
            *p++ |= 0x88;
            *p |= 0x80;
            p += 0x9D;
        }
    }
    if (walls & 4) {
        p = dst + 5;
        for (i = 0; i < 5; i++) {
            *p++ |= 0x88;
            *p++ |= 0x88;
            *p |= 0x88;
            p += 0x9E;
        }
    }
    if (walls & 1) {
        p = dst + 7;
        for (i = 0; i < 5; i++) {
            *p++ |= 0x08;
            *p++ |= 0x88;
            *p++ |= 0x88;
            *p |= 0x80;
            p += 0x9D;
        }
    }
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BDAD0, func_060BDAD0);
void func_060BDC7C(void) {
    u8* dst;
    u8* revealDst;
    s32 mapOffset;
    s32 mapIndex;
    s32 row;
    s32 col;
    s32 revealRow;
    u32 revealCol;

    dst = CASTLE_MAP_BITMAP;
    mapOffset = 0;
    if (g_CurrentRoom.stageID & 0x20) {
        mapOffset = 0x0400;
        revealDst = dst + 0x6970;
        for (revealRow = 0; revealRow <= 3; revealRow++) {
            for (revealCol = 0; revealCol <= 10; revealCol++) {
                revealDst[revealCol] = g_MariaMapRevealPattern[revealCol];
            }
            revealDst += CASTLE_MAP_BITMAP_PITCH;
        }
    }

    row = 0;
    mapIndex = mapOffset;
    for (; row <= 0x3F; row++) {
        for (col = 0; col <= 0x0F; col++) {
            func_060BD638(g_CastleMap[mapIndex++], dst);
            dst += CASTLE_MAP_CELL_WIDTH;
        }
        dst += CASTLE_MAP_BITMAP_PITCH * 3;
    }

    func_060BDAD0();
    dst = CASTLE_MAP_BITMAP;
    row = 0;
    mapIndex = mapOffset;
    for (; row <= 0x3F; row++) {
        for (col = 0; col <= 0x0F; col++) {
            func_060BD9E8(g_CastleMap[mapIndex++], dst);
            dst += CASTLE_MAP_CELL_WIDTH;
        }
        dst += CASTLE_MAP_BITMAP_PITCH * 3;
    }

    dst = CASTLE_MAP_BITMAP;
    row = 0;
    mapIndex = mapOffset;
    for (; row <= 0x3F; row++) {
        for (col = 0; col <= 0x0F; col++) {
            func_060BD81C(g_CastleMap[mapIndex++], dst);
            dst += CASTLE_MAP_CELL_WIDTH;
        }
        dst += CASTLE_MAP_BITMAP_PITCH * 3;
    }
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BDDA0, func_060BDDA0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BDED8, func_060BDED8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE064, func_060BE064);

typedef struct {
    u16 unk_0000[0xC00];
    u16 colors0[4];
    u16 colors1[4];
} SpGourTblData;

extern SpGourTblData* SpGourTbl;

void func_060BE258(void) {
    s32* ptr;
    u16* colors0;
    u16* colors1;

    ptr = func_060784A8();
    func_060BE72C(ptr);
    d_060cd748 = DAT_060476a0;
    d_060cd74c = DAT_060476a4;
    if (g_PlayableCharacter == 0) {
        DAT_060476a0 = 0x252000;
        DAT_060476a4 = 1;
    }
    colors0 = SpGourTbl->colors0;
    colors0[0] = colors0[1] = 0xB18C;
    colors0[2] = colors0[3] = 0xD294;
    colors1 = SpGourTbl->colors1;
    colors1[0] = colors1[1] = colors1[2] = colors1[3] = 0x9084;
    DAT_0605c6e4 = 1;
}
void func_060BE308(s32* src) {
    s32* dst;
    Unk0605DB60* entry;
    s32 i;

    dst = (s32*)((DAT_0605aec0[0][0] * 8) + 0x25C00000);
    DMA_CpuMemCopy2(dst, src, 0x8400);
    while (DMA_CpuResult() == 2) {
    }

    entry = d_0605DB60;
    for (i = 0; i <= 0x1F; i++) {
        entry->unkC = entry->unk8;
        entry->unkE = entry->unkA;
        entry++;
    }

    dst = (s32*)((SPR_2LookupTblNoToVram(0x10) * 8) + 0x25C00000);
    DMA_CpuMemCopy2(dst, src + 0x4200, 0x400);
    while (DMA_CpuResult() == 2) {
    }

    dst = (s32*)0x25F00800;
    DMA_CpuMemCopy2(dst, src + 0x4400, 0x200);
    while (DMA_CpuResult() == 2) {
    }
}

s32 DAT_06086390;
s32 DAT_060476a0;
s32 DAT_060476a4;
s32* func_060784A8();

void func_060BE3D4(void) {
    s32* iVar2;
    iVar2 = func_060784A8();
    func_060BB9BC(iVar2);
    DAT_060476a0 = g_MariaSavedMapVramBase;
    DAT_060476a4 = g_MariaSavedMapPlaneConfig;
}

// same sequence of funcs as in richter

void func_060BE414(void) {
    s32* iVar2;
    DAT_06086390 = 0;
    iVar2 = func_060784A8();
    iVar2[0x4500] = 0xffffffff;
}

void func_060BE440(void) {
    s32* work;
    u8* area;
    u8* dst;
    s32 i;
    u32 clear_size;
    u8* table_base;
    s32 table_offset;
    u32 dma_offset;

    DAT_06086390 = 1;
    work = func_060784A8();
    work[0x4500] = -1;

    clear_size = 0xA000U;
    area = (u8*)(work + 0x4501);
    memset(area, 0, clear_size);
    dst = area;

    i = 0;
    do {
        func_06078700(dst, DAT_06085DE8[i], 4);
        dst += 0x180;
        i++;
    } while (i <= 10);

    i = 0;
    do {
        func_06078700(dst, DAT_06085E14[i], 4);
        dst += 0x180;
        i++;
    } while (i <= 7);

    i = 0;
    do {
        func_06078700(dst, DAT_06085DCC[i], 4);
        dst += 0x180;
        i++;
    } while (i <= 1);

    table_base = (u8*)DAT_0605aec0;
    table_offset = 8;
    dma_offset = *(u16*)(table_base + table_offset);
    dma_offset *= 8U;
    dma_offset += 0x25C00000U;
    DMA_CpuMemCopy2((s32*)dma_offset, work + 0x4501, 0xFC0U);

    while (DMA_CpuResult() == 2) {
    }
}

void func_060BE54C(void) {
    s32* base;
    s32* dst;
    u8* text;
    s32 slot;
    s32 i;

    DAT_06086390 = 2;
    base = func_060784A8();
    base[0x4500] = -1;
    memset(base + 0x4501, 0, 0xA000);

    text = (u8*)(base + 0x4501);
    for (i = 0; i <= 7; i++) {
        func_06078700(text, func_06078748(i), 12);
        text += 0x480;
    }
    func_06078700(text, DAT_06085DCC[2], 6);

    slot = 2;
    dst = (s32*)((DAT_0605aec0[slot][0] * 8) + 0x25C00000);
    DMA_CpuMemCopy2(dst, base + 0x4501, 0x1320);
    while (DMA_CpuResult() == 2) {
    }
}
void func_060BE618(void) {
    s32* base;
    s32* dst;
    u8* text;
    s32 slot;
    s32 i;

    DAT_06086390 = 3;
    base = func_060784A8();
    base[0x4500] = -1;
    memset(base + 0x4501, 0, 0xA000);

    text = (u8*)(base + 0x4501);
    for (i = 0; i <= 0x1F; i++) {
        func_06078700(text, func_06078748(i), 12);
        text += 0x480;
    }

    slot = 2;
    dst = (s32*)((DAT_0605aec0[slot][0] * 8) + 0x25C00000);
    DMA_CpuMemCopy2(dst, base + 0x4501, 0x4800);
    while (DMA_CpuResult() == 2) {
    }
}

void func_060BE6D4(void) {
    int* iVar2;
    DAT_06086390 = 4;
    iVar2 = func_060784A8();
    iVar2[0x4500] = 0xffffffff;
}

void func_060BE700(void) {
    int* iVar2;
    DAT_06086390 = 5;
    iVar2 = func_060784A8();
    iVar2[0x4500] = 0xffffffff;
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE72C, func_060BE72C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE854, func_060BE854);
extern s16 g_ButtonMask[];

bool func_060BE994(void) {
    s32 buf[9];
    s32 i;
    s32 bitMask_Assigned;
    s32* buttonConfig;

    for (i = 0; i < 9; i++) {
        buf[i] = 0;
    }

    buttonConfig = g_Settings.buttonConfig;
    for (i = 0; i < 8; i++) {
        buf[*buttonConfig++] = 1;
    }

    for (i = 0; i < 9; i++) {
        if (buf[i] == 0) {
            g_Settings.buttonConfig[8] = i;
            break;
        }
    }

    for (i = 0; i < 9; i++) {
        g_Settings.buttonMask[i] = g_ButtonMask[g_Settings.buttonConfig[i]];
    }

    bitMask_Assigned = 0;
    buttonConfig = g_Settings.buttonConfig;
    for (i = 0; i < 9; i++) {
        bitMask_Assigned |= 1 << *buttonConfig++;
    }
    if (bitMask_Assigned == 0xFF) {
        return true;
    } else {
        return false;
    }
}
void func_060BEA54(void) {
    Point16* pos;
    s32 i;
    s32 value;
    s32 buttonConfig;

    pos = g_MariaMapUiPositionsA;
    for (i = 0; i < 4; i++) {
        func_06078684(0x1C0, g_Status.statsBase[i], pos++);
        if (g_Status.statsEquip[i] != 0) {
            if (g_Status.statsEquip[i] > 0) {
                func_06078550(0x1C0, 0x0B, pos++);
                value = g_Status.statsEquip[i];
            } else {
                func_06078550(0x1C0, 0x0D, pos++);
                value = -g_Status.statsEquip[i];
            }
            func_06078684(0x1C0, value, pos++);
        } else {
            pos += 2;
        }
    }

    pos = g_MariaMapUiPositionsB;
    buttonConfig = g_Settings.buttonConfig[0];
    func_06078550(0x1C0, g_MariaMapIconIndices[buttonConfig], pos++);
    func_06078684(0x1C0, g_Status.attackHands[0], pos++);
    buttonConfig = g_Settings.buttonConfig[2];
    func_06078550(0x1C0, g_MariaMapIconIndices[buttonConfig], pos++);
    func_06078684(0x1C0, g_Status.attackHands[1], pos++);
    func_06078684(0x1C0, g_Status.defenseEquip, pos);
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BEB74, func_060BEB74);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BEE30, func_060BEE30);

void func_060BF0F4(u32 param_1) {
    int first;
    int cur;
    int offset;
    int i;
    u8* ptr;

    if (param_1 == 6)
        offset = 0x28;
    else if (param_1 & 1)
        offset = 0x28;
    else
        offset = 0;

    first = g_MariaMapRevealRowIndices[param_1];

    for (cur = first; cur < first + 4; cur++) {
        int tile = cur << 6;

        ptr = (u8*)tile;
        ptr += (u32)0x25E58000 + offset;

        for (i = 0; i < 0x20; i++)
            *ptr++ = 0;

        if (offset == 0x28) {
            ptr = (u8*)(0x25E58800 + tile);

            for (i = 0; i < 0x10; i++)
                *ptr++ = 0;
        }
    }
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BF180, func_060BF180);

u32 D_06085534;
u8 DAT_06057f68;

s32 func_060732E4(u16);

void func_060BF35C(void) {
    if (DAT_0605cd70.unk8 != 0) {
        if (DAT_0605cd70.unk8 == 1) {
            goto after;
        }
        return;
    } else {
        func_060732E4(DAT_0605cd70.unk0);
        DAT_0605cd70.unk8 += 1;
    }
after:
    if ((DAT_06057f68 == 0) && (g_pads[0].previous & 0x100)) {
        D_06085534 = 6;
        DAT_06057f68 = 4;
    }
    func_060BF180();
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BF3D0, func_060BF3D0);
void func_060BF704(void) {
    switch (DAT_0605cd70.unk8) {
    case 0:
        func_060732E4(DAT_0605cd70.unk0);
        DAT_0605cd70.unk8++;
        /* fall through */
    case 1:
        if (DAT_06057f68 == 0 && (g_pads[0].previous & PAD_CROSS)) {
            D_06085534 = 6;
            DAT_06057f68 = 4;
        }
        if (DAT_06057f68 == 3) {
            DAT_06057f68 = 0;
        }
        if (DAT_06057f68 == 6) {
            DAT_0605cd70.unk0 = 6;
            DAT_0605cd70.unk8 = 0;
            DAT_06065470 &= ~0x003F;
            SclProcess = 1;
        }
        func_060BF3D0();
    }
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BF7B0, func_060BF7B0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BFA68, func_060BFA68);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BFBF8, func_060BFBF8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BFD24, func_060BFD24);
void func_060BFE38(void) {
    s32 i;
    s32 swapped;
    s32 time;
    s32 stageId;

    for (i = 0; i < 28; i++) {
        DAT_060D2A94[i] = func_0606F21C(i, 0);
        if (DAT_060D2A94[i] == 0) {
            DAT_060D2A94[i] = 1000000;
        }
        DAT_060D2B04[i] = i;
    }

    do {
        swapped = false;
        for (i = 0; i < 27; i++) {
            if (DAT_060D2A94[i] > DAT_060D2A94[i + 1]) {
                time = DAT_060D2A94[i];
                DAT_060D2A94[i] = DAT_060D2A94[i + 1];
                DAT_060D2A94[i + 1] = time;
                stageId = DAT_060D2B04[i];
                DAT_060D2B04[i] = DAT_060D2B04[i + 1];
                DAT_060D2B04[i + 1] = stageId;
                swapped++;
            }
        }
    } while (swapped);
}
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BFECC, func_060BFECC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60C00B4, func_060C00B4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60C0428, func_060C0428);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60C0920, func_060C0920);

u32* d_06086234;
u32* d_06086250;

void func_060C0A5C(void) {
    if (d_06086234 == 0) {
        memset((void*)0x25E58288, 0, 0xC);
        memset((void*)0x25E582C8, 0, 0xC);
    }

    if (d_06086250 == 0) {
        memset((void*)0x25E58348, 0, 0xC);
        memset((void*)0x25E58388, 0, 0xC);
    }

    if (g_GameClearFlag == 0) {
        memset((void*)0x25E584C8, 0, 0x10);
        memset((void*)0x25E58508, 0, 0x10);
    }
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60C0AE4, func_060C0AE4);
