// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

void func_8012D3E8(void) {
    byte pad[0x28];
    s32 directionsPressed =
        g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);

    if ((g_Player.padTapped & PAD_CROSS) && (D_800B0914 != 4)) {
        func_8012CCE4();
        return;
    }
    if (!(g_Player.pl_vram_flag & 1) && (D_800B0914 != 4)) {
        func_8012CED4();
        return;
    }
    if ((g_Player.padPressed & PAD_DOWN) && (D_800B0914 != 4)) {
        func_8012CFF0();
        return;
    }

    switch (D_800B0914) {
    case 0:
        if (g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) {
            func_8012CC30(0);
            break;
        }
        if (PLAYER.animFrameIdx >= 3) {
            if (PLAYER.animFrameDuration < 0) {
                func_8012CB4C();
                if (!(directionsPressed & (PAD_LEFT | PAD_RIGHT))) {
                    // Evil! This function takes no arguments! This is
                    // why func_8012CA64 had to be commented out of dra.h.
                    func_8012CA64(0);
                    break;
                }
            }
            SetSpeedX(FIX(1));
            break;
        }
        if (PLAYER.animFrameDuration == 1 && PLAYER.animFrameIdx == 2) {
            PLAYER.facingLeft++;
            PLAYER.facingLeft &= 1;
        }
        SetSpeedX(FIX(-1));
        break;

    case 1:
        if (g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) {
            func_8012CC30(0);
            break;
        }
        SetSpeedX(FIX(1));
        if ((PLAYER.facingLeft && (directionsPressed & PAD_RIGHT)) ||
            (!PLAYER.facingLeft && (directionsPressed & PAD_LEFT))) {
            D_800B0914 = 0;
            SetPlayerAnim(0xE1);
        }

        if (!(directionsPressed & (PAD_LEFT | PAD_RIGHT))) {
            func_8012CA64();
        }
        break;
    case 2:
        if ((g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) &&
            (abs(PLAYER.velocityX) < FIX(3))) {
            func_8012CC30(0);
            break;
        }

        if (g_GameTimer % 6 == 0) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(69, 1), 0);
        }
        if (PLAYER.velocityX > 0) {
            PLAYER.velocityX += FIX(3.0 / 128);
            if (PLAYER.velocityX > FIX(9)) {
                PLAYER.velocityX = FIX(9);
            }
            if (!IsRelicActive(RELIC_POWER_OF_WOLF) &&
                PLAYER.velocityX > FIX(3)) {
                PLAYER.velocityX = FIX(3);
            }
        }
        if (PLAYER.velocityX < 0) {
            PLAYER.velocityX -= FIX(3.0 / 128);
            if (PLAYER.velocityX < FIX(-9)) {
                PLAYER.velocityX = FIX(-9);
            }
            // @bug The end of this should be FIX(-3) since we're capping
            // the negative velocity. This is weird and could be useful for
            // someone! Namely, if velocity is less than 0 (which was already
            // checked) then you will instantly accelerate up to -3.
            if (!IsRelicActive(RELIC_POWER_OF_WOLF) &&
                PLAYER.velocityX < FIX(3)) {
                PLAYER.velocityX = FIX(-3);
            }
        }
        if (((g_Player.pl_vram_flag & 4) && PLAYER.velocityX > FIX(5.5)) ||
            ((g_Player.pl_vram_flag & 8) && PLAYER.velocityX < FIX(-5.5))) {
            func_8012D28C(1);
            break;
        }
        if (((g_Player.pl_vram_flag & 4) && PLAYER.velocityX > FIX(4)) ||
            ((g_Player.pl_vram_flag & 8) && PLAYER.velocityX < FIX(-5.5))) {
            func_8012D28C(0);
            break;
        }
        if ((g_Player.pl_vram_flag & 4) && PLAYER.velocityX > 0 ||
            (g_Player.pl_vram_flag & 8) && PLAYER.velocityX < 0 ||
            (directionsPressed & (PAD_LEFT | PAD_RIGHT)) == 0) {
            PLAYER.ext.player.anim = 0xE0;
            // Set the state to 3, and the timer to 24. Note that in case 3,
            // this decrements.
            D_800B0914 = 3;
            D_800B091C = 24;
            break;
        }

        if (PLAYER.facingLeft) {
            if (((g_Player.unk04 & 0xF001) == 1) &&
                ((D_80138438 & 0xF001) == 0xC001)) {
                func_8012CCE4();
                PLAYER.velocityY /= 4;
            }
            if (((g_Player.unk04 & 0xF001) == 0x8001) &&
                ((D_80138438 & 0xF001) == 1)) {
                func_8012CCE4();
                PLAYER.velocityY /= 2;
            }
        } else {
            if (((g_Player.unk04 & 0xF001) == 1) &&
                ((D_80138438 & 0xF001) == 0x8001)) {
                func_8012CCE4();
                PLAYER.velocityY /= 4;
            }
            if (((g_Player.unk04 & 0xF001) == 0xC001) &&
                ((D_80138438 & 0xF001) == 1)) {
                func_8012CCE4();
                PLAYER.velocityY /= 2;
            }
        }
        break;
    case 3:
        if ((g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) &&
            (abs(PLAYER.velocityX) < FIX(3))) {
            func_8012CC30(0);
            break;
        }
        if (abs(PLAYER.velocityX) > FIX(1)) {
            DecelerateX(0x2000);
        }
        if ((PLAYER.facingLeft && (directionsPressed & PAD_RIGHT)) ||
            (!PLAYER.facingLeft && (directionsPressed & PAD_LEFT))) {
            D_800B0914 = 0;
            SetPlayerAnim(0xE1);
        }

        if (--D_800B091C == 0) {
            D_800B0914 = 1;
            D_8013842C = 0xC;
        }
        break;
    case 4:
        DecelerateX(0x400);
        if (!(g_GameTimer % 2)) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(69, 1), 0);
        }
        if (PLAYER.animFrameDuration >= 0) {
            break;
        }
        if (((g_Player.padPressed & PAD_RIGHT) && !PLAYER.facingLeft) ||
            ((g_Player.padPressed & PAD_LEFT) && PLAYER.facingLeft)) {
            SetPlayerAnim(0xE2);
            D_800B0914 = 2;
            if (abs(PLAYER.velocityX) < FIX(2)) {
                SetSpeedX(FIX(2));
                break;
            }
        } else {
            func_8012CA64();
            PLAYER.velocityX = 0;
        }
        break;
    }
}

void func_8012DBBC(void) {
    s32 vel_boost;

    if (g_Player.timers[5] && (g_Player.padTapped & PAD_CROSS)) {
        func_8012CCE4();
        return;
    }
    if ((PLAYER.facingLeft && !(g_Player.padPressed & PAD_LEFT)) ||
        (!PLAYER.facingLeft && !(g_Player.padPressed & PAD_RIGHT))) {
        DecelerateX(FIX(4.0 / 128));
    }
    if (g_Player.pl_vram_flag & 1) {
        if (D_800B0914 == 1) {
            PLAYER.step_s = 2;
            D_800B0914 = 2;
            SetPlayerAnim(0xE2);
        } else if (PLAYER.velocityY > FIX(6.875)) {
            PLAYER.step_s = 3;
            D_800B0914 = 3;
            SetPlayerAnim(0xE5);
            CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
        } else {
            func_8012CA64();
        }
        PLAYER.velocityY = 0;
        PlaySfx(SFX_STOMP_SOFT_B);
        return;
    }
    if (g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) {
        func_8012CC30(1);
    }
    switch (D_800B0914) {
    case 0:
        CheckMoveDirection();
        break;
    case 1:
        if (((g_Player.pl_vram_flag & 4) && PLAYER.velocityX > FIX(5.5)) ||
            ((g_Player.pl_vram_flag & 8) && PLAYER.velocityX < FIX(-5.5))) {
            func_8012D28C(1);
            return;
        }
        if (((g_Player.pl_vram_flag & 4) && PLAYER.velocityX > FIX(4)) ||
            ((g_Player.pl_vram_flag & 8) && PLAYER.velocityX < FIX(-5.5))) {
            func_8012D28C(0);
            return;
        }
        if (((g_Player.pl_vram_flag & 4) && (PLAYER.velocityX > FIX(2.5))) ||
            ((g_Player.pl_vram_flag & 8) && (PLAYER.velocityX < FIX(-2.5)))) {
            DecelerateX(FIX(0.125));
        }
        if (PLAYER.animFrameIdx == 3) {
            PLAYER.animFrameDuration = 6;
        }
    }
    vel_boost = FIX(20.0 / 128);
    if (D_80097448[0] > 12) {
        vel_boost /= 4;
    }
    PLAYER.velocityY += vel_boost;
    if (PLAYER.velocityY > FIX(7)) {
        PLAYER.velocityY = FIX(7);
    }
}

void func_8012DF04(void) {
    s32 velocityBoost;

    if (g_Player.timers[5] && (g_Player.padTapped & PAD_CROSS)) {
        func_8012CCE4();
        return;
    }
    velocityBoost = FIX(20.0 / 128);
    if (D_80097448[0] > 12) {
        velocityBoost /= 4;
    }
    PLAYER.velocityY += velocityBoost;
    if (PLAYER.velocityY > FIX(7)) {
        PLAYER.velocityY = FIX(7);
    }
    if (g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) {
        func_8012CC30(1);
    }
    if (g_Player.pl_vram_flag & 1) {
        PlaySfx(SFX_STOMP_SOFT_B);
        if (PLAYER.velocityY > FIX(6.875)) {
            PLAYER.step_s = 3;
            D_800B0914 = 3;
            SetPlayerAnim(0xE5);
            CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
        } else {
            func_8012CA64();
        }
        PLAYER.velocityY = 0;
    }
}

void func_8012E040(void) {
    s32 var_s0 = true;
    s32 vel_boost;
    s16 xOffset;

    if ((PLAYER.facingLeft && !(g_Player.padPressed & PAD_LEFT)) ||
        (!PLAYER.facingLeft && !(g_Player.padPressed & PAD_RIGHT))) {
        var_s0 = false;
        DecelerateX(FIX(16.0 / 128));
    }
    if (g_Player.pl_vram_flag & 1) {
        if (D_800B0914 == 2) {
            PLAYER.step_s = 2;
            D_800B0914 = 2;
            SetPlayerAnim(0xE2);
        } else if ((PLAYER.velocityY > FIX(6.875)) || (D_800B0914 == 3)) {
            PLAYER.step_s = 3;
            D_800B0914 = 3;
            SetPlayerAnim(0xE5);
            CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
        } else {
            if (D_800B0914 == 0) {
                func_8012CA64();
            }
            if (D_800B0914 == 1) {
                func_8012CB4C();
            }
        }
        PlaySfx(SFX_STOMP_SOFT_B);
        PLAYER.velocityY = 0;
        return;
    }
    if ((PLAYER.velocityY < FIX(-1)) && (g_Player.pl_vram_flag & 2)) {
        if (PLAYER.velocityY < FIX(-5)) {
            xOffset = 3;
            if (PLAYER.facingLeft) {
                xOffset = -xOffset;
            }
            PLAYER.posX.i.hi += xOffset;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(4, 1), 0);
            PLAYER.posX.i.hi -= xOffset;
            func_80102CD8(3);
            PlaySfx(SFX_WALL_DEBRIS_B);
            PLAYER.velocityX = 0;
            PLAYER.velocityY = 0;
            func_8012CED4();
            return;
        }
        PLAYER.velocityY = 0;
    }
    if (g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) {
        func_8012CC30(1);
    }
    switch (D_800B0914) {
    case 0:
        CheckMoveDirection();
        if (var_s0) {
            if (abs(PLAYER.velocityX) < FIX(1)) {
                SetSpeedX(FIX(1));
            }
        }
        break;
    case 1:
        CheckMoveDirection();
        if (var_s0) {
            if (abs(PLAYER.velocityX) < FIX(1)) {
                SetSpeedX(FIX(1));
            } else {
                DecelerateX(FIX(16.0 / 128));
            }
        }
        break;
    case 2:
        if (((g_Player.pl_vram_flag & 4) && PLAYER.velocityX > FIX(5.5)) ||
            ((g_Player.pl_vram_flag & 8) && PLAYER.velocityX < FIX(-5.5))) {
            func_8012D28C(1);
            return;
        }
        if ((g_Player.pl_vram_flag & 4) && (PLAYER.velocityX > FIX(4)) ||
            ((g_Player.pl_vram_flag & 8) && PLAYER.velocityX < FIX(-5.5))) {
            func_8012D28C(0);
            return;
        }
        // This is a silly way to write this
        if ((g_Player.pl_vram_flag & 8 && PLAYER.velocityX > 0) || 
            (g_Player.pl_vram_flag & 8 && PLAYER.velocityX < 0)) {
            D_800B0914 = 1;
        }
        if (abs(PLAYER.velocityX) < FIX(1)) {
            D_800B0914 = 1;
        }
        if ((PLAYER.facingLeft && (g_Player.padPressed & PAD_RIGHT)) ||
            (!PLAYER.facingLeft && (g_Player.padPressed & PAD_LEFT))) {
            CheckMoveDirection();
            D_800B0914 = 1;
            SetSpeedX(FIX(1));
            break;
        }
        if (PLAYER.animFrameIdx == 3) {
            PLAYER.animFrameDuration = 6;
        }
        break;

    case 3:
        if (PLAYER.animFrameIdx == 3) {
            PLAYER.animFrameDuration = 6;
        }
        break;
    }
    vel_boost = FIX(20.0 / 128);
    if (D_80097448[0] > 12) {
        // Interesting, wrong registers if you do /= here.
        vel_boost = vel_boost / 4;
    } 
    PLAYER.velocityY += vel_boost;
    if (PLAYER.velocityY > FIX(7)) {
        PLAYER.velocityY = FIX(7);
    }
}
void func_8012E550(void) {
    s32 i;
    s16 playerFrame = PLAYER.animFrameIdx;
    bool pressingDown = g_Player.padPressed & PAD_DOWN;

    DecelerateX(FIX(0.125));
    if (g_Player.padTapped & PAD_CROSS) {
        if (g_Player.padPressed & PAD_DOWN) {
            for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
                if (g_Player.colFloor[i].effects & EFFECT_SOLID_FROM_ABOVE) {
                    g_Player.timers[7] = 8;
                    func_8012CED4();
                    PLAYER.velocityX = 0;
                    PLAYER.animFrameIdx = 4;
                    PLAYER.animFrameDuration = 1;
                    PLAYER.velocityY = FIX(2);
                    return;
                }
            }
        }
        func_8012CCE4();
        return;
    }
    if (!(g_Player.pl_vram_flag & 1)) {
        func_8012CED4();
        return;
    }
    if (g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE) && D_800B0914 != 3) {
        func_8012CC30(0);
        return;
    }
    switch (D_800B0914) {
    case 0:
        if (!pressingDown) {
            SetPlayerAnim(0xE4);
            D_800B0914 = 2;
            if (playerFrame == 0) {
                PLAYER.animFrameIdx = 1;
            }
        } else if (PLAYER.animFrameDuration < 0) {
            D_800B0914++;
        }
        break;
    case 1:
        if (pressingDown) {
            break;
        }
        SetPlayerAnim(0xE4);
        D_800B0914 = 2;
        break;
    case 2:
        if (pressingDown) {
            SetPlayerAnim(0xE3);
            D_800B0914 = 0;
            if (playerFrame != 0) {
                break;
            }
            PLAYER.animFrameIdx = 1;
            break;
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8012CA64();
        }
        break;
    case 3:
        if (PLAYER.animFrameDuration < 0) {
            func_8012CA64();
        }
        break;
    }
}

void func_8012E7A4(void) {
    s32 i, j; //Not nested, just two incrementers for two loops
    Entity* entity;
#if defined(VERSION_US)
    if (g_Entities[16].entityId != 0x22) {
        if (CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(44, 0x23), 0) ==
            NULL) {
            return;
        }
        func_8010FAF4();
        g_Player.unk66++;
    }
#endif

    for (i = 0; i < 6; i++) {
        D_800B08CC[i].state = 0;
    }

    D_801396EC = PLAYER.animCurFrame;
    D_801396E0 = PLAYER.animSet;
    func_8010E168(1, 4);
    DestroyEntity(&g_Entities[17]);
    g_Entities[17].entityId = 0x38;
    DestroyEntity(&g_Entities[18]);
    g_Entities[18].entityId = 0x37;
    DestroyEntity(&g_Entities[19]);
    g_Entities[19].entityId = 0x39;
    DestroyEntity(&g_Entities[20]);
    g_Entities[20].entityId = 0x3A;

    for (entity = &g_Entities[21], j = 0; j < 9; j++, entity++) {
        DestroyEntity(entity);
        entity->entityId = 0x3B;
        entity->params = j;
    }
    // We create entity #60, which is func_8013136C
    DestroyEntity(&g_Entities[30]);
    g_Entities[30].entityId = 60;

    func_8012CED4();
    PLAYER.animFrameIdx = 4;
    PLAYER.animFrameDuration = 4;
    PLAYER.step_s = 8;
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter - 2;
    D_80138430 = 0x800;
    PLAYER.rotZ = 0;
    g_Player.unk44 = g_Player.unk46 = g_Player.unk48 = 0;
    D_8013842C = 0;
    PLAYER.velocityX = 0;
    PLAYER.velocityY = 0;
    PLAYER.unk5A = 0x7E;
    PLAYER.animSet = 0xF;
    PLAYER.palette = 0x810D;
    
#if !defined(VERSION_US)
    if (g_Entities[16].entityId != 0x22) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(44, 0x23), 0);
        func_8010FAF4();
        g_Player.unk66++;
    }
#endif
}

void func_8012E9C0(void) {
    s32 i;

    PLAYER.palette = 0x810D;
    for (i = 0; i < 4; i++) {
        if (g_SensorsFloor[i].y < g_SensorsFloorDefault[i]) {
            g_SensorsFloor[i].y++;
        }
    }
    func_8010E168(1, 4);
    PLAYER.velocityY = 0;
    PLAYER.animFrameDuration = 4;
    if (g_Entities[16].entityId == 0x22) {
        if (func_8011203C() == 0) {
            return;
        }
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(44, 0x1b), 0);
    } else if (g_Player.unk66 != 3) {
        return;
    }
    PLAYER.palette = 0x104;
    PLAYER.step_s = 5;
    PLAYER.velocityY = FIX(-1.5);
}

void func_8012EAD0(void) {
    s32 i;
    s32 else_cycles;

    DecelerateX(FIX(0.125));
    if (g_Player.pl_vram_flag & 3) {
        PLAYER.velocityY = 0;
    }
    DecelerateY(FIX(0.125));
    else_cycles = 0;
    switch (PLAYER.step_s) {
    case 0:
        for (i = 0; i < 4; i++) {
            if (g_SensorsCeiling[i].y > g_SensorsCeilingDefault[i]) {
                g_SensorsCeiling[i].y--;
            } else {
                else_cycles++;
            }
        }
        if ((g_Player.pl_vram_flag & 3) == 3) {
            g_Player.unk68 = 1;
            PLAYER.velocityY = 0;
            PLAYER.velocityX = 0;
        }
        if (else_cycles == 4) {
            PLAYER.animSet = 1;
            PLAYER.unk5A = 0;
            PLAYER.drawFlags = PLAYER.rotZ = 0;
            SetPlayerAnim(0xCA);
            g_Player.unk66 = 1;
            if (g_Player.unk68) {
                PLAYER.step_s = 2;
                D_800AFDA4[1] = 0xC7;
            } else {
                PLAYER.step_s = 1;
                D_800AFDA4[1] = 0x5F;
            }
        }
        break;
    case 1:
        if (g_Player.unk66 == 3) {
            func_8010E83C(0);
            if (!(g_Player.pl_vram_flag & 0x8000)) {
                PLAYER.velocityY = FIX(-1);
            }
            g_Player.unk44 |= 0x100;
            PLAYER.palette = 0x8100;
            PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter;
#if defined(VERSION_US)
            g_Player.unk20 = 0x18;
#elif defined(VERSION_HD)
            D_800ACEDC_hd = 0x18;
#elif defined(VERSION_PSP)
            D_psp_09234B68 = 0x18;
#endif
            
            func_80111CC0();
        }
        break;
    case 2:
        if (g_Player.unk66 == 3) {
#if defined(VERSION_US)
            PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter;
#endif

            func_8010E4D0();
        }
    }
}

void func_8012ED30(void) {
    if (g_Player.padTapped & PAD_CROSS) {
        func_8012CCE4();
        D_80138440 = 0x10;
        return;
    }
    if (g_Player.pl_vram_flag & 1) {
        func_8012CA64();
        return;
    }
    if (!IsRelicActive(RELIC_SKILL_OF_WOLF) ||
        !(g_Player.padPressed & PAD_TRIANGLE) || (D_80097448[1] == 0)) {
        func_8012CED4();
        return;
    }
    SetSpeedX(FIX(0.5));
    if (D_80097448[1] > 12) {
        PLAYER.velocityY = FIX(-0.5);
    } else {
        PLAYER.velocityY = 0;
    }
    if (g_Player.padPressed & PAD_RIGHT) {
        PLAYER.facingLeft = 0;
        PLAYER.velocityX = FIX(0.5);
    }
    if (g_Player.padPressed & PAD_LEFT) {
        PLAYER.facingLeft = 1;
        PLAYER.velocityX = FIX(-0.5);
    }
    // If you're not pressing any of right, left, or up
    if (!(g_Player.padPressed & (PAD_RIGHT | PAD_LEFT | PAD_UP))) {
        DecelerateX(0x400);
        PLAYER.velocityY = FIX(0.5);
    }
    if (PLAYER.velocityY <= 0) {
        if (D_80138430 > 2112) {
            D_80138430 -= 8;
        }
        if (D_80138430 < 2112) {
            D_80138430 += 8;
        }
    } else {
        if (D_80138430 > 1824) {
            D_80138430 -= 8;
        }
        if (D_80138430 < 1824) {
            D_80138430 += 8;
        }
    }
}
void func_8012EF2C(void) {
    s32 i;
    s32 xSpeed;
    s32 var_s0;

    PLAYER.palette = 0x104;
    PLAYER.drawMode = DRAW_DEFAULT;
#if defined(VERSION_US)
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter - 2;
#endif
    if (WolfFormFinished()) {
        return;
    }
    if (D_8013842C != 0) {
        D_8013842C--;
    }
    if (D_80138440 != 0) {
        D_80138440--;
    }
    D_80138444 = 0;
    func_8012C97C();
    D_800B0920 = 14;
    switch (PLAYER.step_s) {
    case 0:
        func_8012E7A4();
        break;
    case 1:
        func_8012D024();
        break;
    case 2:
        func_8012D3E8();
        break;
    case 3:
        func_8012E550();
        break;
    case 4:
        func_8012E040();
        break;
    case 5:
        func_8012DBBC();
        break;
    case 7:
        func_8012D178();
        break;
    case 6:
        func_8012DF04();
        break;
    case 8:
        func_8012E9C0();
        break;
    case 9:
        func_8012ED30();
    }
    D_80138438 = g_Player.unk04;
    for (i = 0; i < 8; i++) {
        var_s0 = 4;
        xSpeed = abs(PLAYER.velocityX);
        if (xSpeed >= FIX(4)) {
            var_s0--;
        }
        if (xSpeed >= FIX(5)) {
            var_s0--;
        }
        if (xSpeed >= FIX(6)) {
            var_s0--;
        }
        // Might be misusing D_800AFFB8 here
        D_800AFFB8[i * 2] = var_s0;
    }
    if (D_80138430 < 0x600) {
        D_80138430 = 0x600;
    }
    if (D_80138430 > 0xA00) {
        D_80138430 = 0xA00;
    }
#if defined(VERSION_US)
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter - 2;
#endif
}

static void func_8012F178(Primitive* prim, s32 count, bool finishUp) {
    // Someone got the brilliant idea to use the scratchpad for every
    // single local variable in this function. So this isn't really a
    // struct, but it describes the layout of that scratchpad. It's not
    // used anywhere else, so we just define it inside the function.
    typedef struct {
        s32 unused;
        s32 i;
        s32 x;
        s32 y;
        s32 velX;
        s32 velY;
        s32 i_limit;
        Primitive* prim;
        helper_8012F178* helper;
        byte pad[15];
        u8 colors[2];
    } scratchpad_8012F178;
    scratchpad_8012F178* s;

#ifdef VERSION_PSP
#define LEFTVEL -0x13
#define TPAGE 0x4118
#define V_OFFSET 0
#else
#define LEFTVEL -0x14
#define TPAGE 0x118
#define V_OFFSET 0xC0
#endif
#ifdef VERSION_PC
    scratchpad_8012F178 _s;
    s = &_s;
#else
    s = (scratchpad_8012F178*)SPAD(0);
#endif
    s->prim = prim;
    s->i_limit = count;
    s->helper = &D_800B08CC[0];
    // D_800B08CC has length 6 but we go i < 5? Odd.
    for (s->i = 0; s->i < 5; s->i++, s->helper++) {
        if (s->i == s->i_limit && s->helper->state) {
            s->helper->state = 2;
        }
        switch (s->helper->state) {
        case 0:
            s->prim->u0 = s->prim->u2 = 0;
            s->prim->u1 = s->prim->u3 = 0x3F;
            s->prim->v0 = s->prim->v1 = V_OFFSET;
            s->prim->v2 = s->prim->v3 = V_OFFSET + 0x3F;
            s->prim->tpage = TPAGE;
            s->prim->priority = PLAYER.zPriority - 6;
            s->prim->drawMode =
                DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE |
                DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            s->helper->state++;
        case 1:
#if defined(VERSION_US)
            s->prim->priority = PLAYER.zPriority - 6;
#endif
            s->prim->drawMode |= DRAW_HIDE;
            break;
        case 2:
            s->helper->facingLeft = PLAYER.facingLeft;
            s->x = PLAYER.posX.i.hi;
            s->y = PLAYER.posY.i.hi;
            if (!PLAYER.facingLeft) {
                s->velX = -0x2C;
            } else {
                s->velX = LEFTVEL;
            }
            s->velY = -0x18;
            s->x += s->velX;
            s->y += s->velY;
            s->prim->x0 = s->prim->x2 = s->x;
            s->prim->x1 = s->prim->x3 = s->x + 0x3F;
            s->prim->y0 = s->prim->y1 = s->y;
            s->prim->y2 = s->prim->y3 = s->y + 0x3F;
            s->prim->drawMode &= ~DRAW_HIDE;
            s->prim->r0 = s->prim->b0 = s->prim->g0 = s->prim->r1 =
                s->prim->b1 = s->prim->g1 = s->prim->r2 = s->prim->b2 =
                    s->prim->g2 = s->prim->r3 = s->prim->b3 = s->prim->g3 =
                        0x80;
#if defined(VERSION_US)
            s->prim->priority = PLAYER.zPriority - 6;
#endif
            s->helper->timer = 0x20;
            s->helper->state++;
            break;
        case 3:
            if (s->helper->facingLeft) {
                if (s->prim->g2 > 12) {
                    s->prim->g2 -= 6;
                } else {
                    s->prim->g2 = 0;
                }
                if (s->prim->g3 > 12) {
                    s->prim->g3 -= 12;
                } else {
                    s->prim->g3 = 0;
                }
            } else {
                if (s->prim->g2 > 12) {
                    s->prim->g2 -= 12;
                } else {
                    s->prim->g2 = 0;
                }
                if (s->prim->g3 > 12) {
                    s->prim->g3 -= 6;
                } else {
                    s->prim->g3 = 0;
                }
            }
            s->prim->r0 = s->prim->b0 = s->prim->g0 = s->prim->r2 =
                s->prim->b2 = s->prim->g2;
            s->prim->r1 = s->prim->b1 = s->prim->g1 = s->prim->r3 =
                s->prim->b3 = s->prim->g3;
#if defined(VERSION_US)
            s->prim->priority = PLAYER.zPriority - 6;
#endif
            if (--s->helper->timer == 0) {
                s->helper->state = 1;
            }
            s->prim->drawMode &= ~DRAW_HIDE;
            break;
        }
        s->prim = s->prim->next;
    }
    // Not sure what the rest of this function is for. But to do it,
    // we have to have finishUp set. If not, we hide and exit.
    if (!finishUp) {
        s->prim->drawMode |= DRAW_HIDE;
        return;
    }
    // Rest of the function is what I'm calling the finishUp routine.
    s->prim->u0 = s->prim->u2 = 0;
    s->prim->u1 = s->prim->u3 = 0x3F;
    s->prim->v0 = s->prim->v1 = V_OFFSET;
    s->prim->v2 = s->prim->v3 = V_OFFSET + 0x3F;
    s->prim->tpage = TPAGE;
    s->prim->priority = PLAYER.zPriority;
    s->prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE |
                        DRAW_COLORS | DRAW_TRANSP;
    s->helper->facingLeft = PLAYER.facingLeft;
    s->x = PLAYER.posX.i.hi;
    s->y = PLAYER.posY.i.hi;
    if (!PLAYER.facingLeft) {
        s->velX = -0x2C;
    } else {
        s->velX = LEFTVEL;
    }
    s->velY = -0x18;
    s->x += s->velX;
    s->y += s->velY;
    s->prim->x0 = s->prim->x2 = s->x;
    s->prim->x1 = s->prim->x3 = s->x + 0x3F;
    s->prim->y0 = s->prim->y1 = s->y;
    s->prim->y2 = s->prim->y3 = s->y + 0x3F;

    s->i = abs(PLAYER.velocityX) + FIX(-3) >> 8;
    if (s->i > 0x7F) {
        s->i = 0x7F;
    }
    s->colors[1] = (u8)s->i + 0x80;

    s->i = abs(PLAYER.velocityX) + FIX(-3) >> 8;
    if (s->i > 0x7F) {
        s->i = 0x7F;
    }
    s->colors[0] = 0x80 - (u8)s->i;

    if (s->helper->facingLeft) {
        s->prim->b0 = s->prim->g2 = s->colors[1];
        s->prim->g3 = s->colors[0];
        s->prim->b1 = s->prim->b2 = s->prim->b3 = 0xFF;
    } else {
        s->prim->b1 = s->prim->g2 = s->colors[0];
        s->prim->g3 = s->colors[1];
        s->prim->b0 = s->prim->b2 = s->prim->b3 = 0xFF;
    }
    s->prim->r0 = s->prim->g0 = s->prim->r2 = s->prim->g2;
    s->prim->r1 = s->prim->g1 = s->prim->r3 = s->prim->g3;
}

bool func_8012F83C(s32 x0, s32 y0, s32 x1, s32 y1, s32 distance) {
    s32 diffX = x0 - x1;
    s32 diffY = y0 - y1;
    s32 sqrt = SquareRoot12((SQ(diffX) + SQ(diffY)) << 12);

    if((sqrt >> 12) >= distance){
        return true;
    } else{
        return false;
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8012F894);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_80130264);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_80130618);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_801309B4);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_80130E94);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8013136C);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", EntityGiantSpinningCross);
