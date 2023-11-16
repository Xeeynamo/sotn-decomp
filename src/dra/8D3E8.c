#include "dra.h"
#include "objects.h"
#include "sfx.h"

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
        if (g_Player.padTapped & PAD_SQUARE) {
            func_8012CC30(0);
            return;
        }
        if (PLAYER.animFrameIdx >= 3) {
            if (PLAYER.animFrameDuration < 0) {
                func_8012CB4C();
                if (!(directionsPressed & (PAD_LEFT | PAD_RIGHT))) {
                    // Evil! This function takes no arguments! This is
                    // why func_8012CA64 had to be commented out of dra.h.
                    func_8012CA64(0);
                    return;
                }
            }
            SetSpeedX(FIX(1));
            return;
        }
        if (PLAYER.animFrameIdx == 2 && PLAYER.animFrameDuration == 1) {
            PLAYER.facingLeft = (PLAYER.facingLeft + 1) & 1;
        }
        SetSpeedX(FIX(-1));
        return;

    case 1:
        if (g_Player.padTapped & PAD_SQUARE) {
            func_8012CC30(0);
            return;
        }
        SetSpeedX(FIX(1));
        if ((PLAYER.facingLeft && (directionsPressed & PAD_RIGHT)) ||
            (!PLAYER.facingLeft && (directionsPressed & PAD_LEFT))) {
            D_800B0914 = 0;
            func_8010DA48(0xE1);
        }

        if (!(directionsPressed & (PAD_LEFT | PAD_RIGHT))) {
            func_8012CA64();
        }
        return;
    case 2:
        if ((g_Player.padTapped & PAD_SQUARE) &&
            (ABS(PLAYER.velocityX) < FIX(3))) {
            func_8012CC30(0);
            return;
        }

        if (g_GameTimer % 6 == 0) {
            CreateEntFactoryFromEntity(g_CurrentEntity, 0x10045U, 0);
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
            return;
        }
        if (((g_Player.pl_vram_flag & 4) && PLAYER.velocityX > FIX(4)) ||
            ((g_Player.pl_vram_flag & 8) && PLAYER.velocityX < FIX(-5.5))) {
            func_8012D28C(0);
            return;
        }
        if ((g_Player.pl_vram_flag & 4) && PLAYER.velocityX > 0 ||
            (g_Player.pl_vram_flag & 8) && PLAYER.velocityX < 0 ||
            (directionsPressed & (PAD_LEFT | PAD_RIGHT)) == 0) {
            PLAYER.ext.player.unkAC = 0xE0;
            // Set the state to 3, and the timer to 24. Note that in case 3,
            // this decrements.
            D_800B0914 = 3;
            D_800B091C = 24;
            return;
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

        return;
    case 3:
        if ((g_Player.padTapped & PAD_SQUARE) &&
            (ABS(PLAYER.velocityX) < FIX(3))) {
            func_8012CC30(0);
            return;
        }
        if (ABS(PLAYER.velocityX) > FIX(1)) {
            DecelerateX(0x2000);
        }
        if ((PLAYER.facingLeft && (directionsPressed & PAD_RIGHT)) ||
            (!PLAYER.facingLeft && (directionsPressed & PAD_LEFT))) {
            D_800B0914 = 0;
            func_8010DA48(0xE1);
        }

        if (--D_800B091C == 0) {
            D_800B0914 = 1;
            D_8013842C = 0xC;
        }
        return;
    case 4:
        DecelerateX(0x400);
        if (!(g_GameTimer & 1)) {
            CreateEntFactoryFromEntity(g_CurrentEntity, 0x10045U, 0);
        }
        if (PLAYER.animFrameDuration >= 0) {
            return;
        }
        if (((g_Player.padPressed & PAD_RIGHT) && !PLAYER.facingLeft) ||
            ((g_Player.padPressed & PAD_LEFT) && PLAYER.facingLeft)) {
            func_8010DA48(0xE2);
            D_800B0914 = 2;
            if (ABS(PLAYER.velocityX) < FIX(2)) {
                SetSpeedX(FIX(2));
                return;
            }
        } else {
            func_8012CA64();
            PLAYER.velocityX = 0;
        }
        return;
    }
}

void func_8012DBBC(void) {
    s32 vel_boost;

    if ((g_Player.D_80072F0A != 0) && (g_Player.padTapped & PAD_CROSS)) {
        func_8012CCE4();
        return;
    }
    if ((PLAYER.facingLeft != 0 && !(g_Player.padPressed & PAD_LEFT)) ||
        (PLAYER.facingLeft == 0 && !(g_Player.padPressed & PAD_RIGHT))) {
        DecelerateX(FIX(4.0 / 128));
    }
    if (g_Player.pl_vram_flag & 1) {
        if (D_800B0914 == 1) {
            PLAYER.step_s = 2;
            D_800B0914 = 2;
            func_8010DA48(0xE2);
        } else if (PLAYER.velocityY > FIX(6.875)) {
            PLAYER.step_s = 3;
            D_800B0914 = 3;
            func_8010DA48(0xE5);
            CreateEntFactoryFromEntity(g_CurrentEntity, 0U, 0);
        } else {
            func_8012CA64();
        }
        PLAYER.velocityY = 0;
        PlaySfx(0x64C);
        return;
    }
    if (g_Player.padTapped & PAD_SQUARE) {
        func_8012CC30(1);
    }
    switch (D_800B0914) {
    case 0:
        func_8010E27C();
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
    if (D_80097448[0] >= 13) {
        vel_boost = FIX(5.0 / 128);
    } else {
        vel_boost = FIX(20.0 / 128);
    }
    PLAYER.velocityY += vel_boost;
    if (PLAYER.velocityY > FIX(7)) {
        PLAYER.velocityY = FIX(7);
    }
}

void func_8012DF04(void) {
    s32 velocityBoost;

    if ((g_Player.D_80072F0A != 0) && (g_Player.padTapped & PAD_CROSS)) {
        func_8012CCE4();
        return;
    }

    if (D_80097448[0] >= 13) {
        velocityBoost = FIX(5.0 / 128);
    } else {
        velocityBoost = FIX(20.0 / 128);
    }
    PLAYER.velocityY += velocityBoost;
    if (PLAYER.velocityY > FIX(7)) {
        PLAYER.velocityY = FIX(7);
    }
    if (g_Player.padTapped & PAD_SQUARE) {
        func_8012CC30(1);
    }
    if (g_Player.pl_vram_flag & 1) {
        PlaySfx(0x64C);
        if (PLAYER.velocityY > FIX(6.875)) {
            PLAYER.step_s = 3;
            D_800B0914 = 3;
            func_8010DA48(0xE5);
            CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
        } else {
            func_8012CA64();
        }
        PLAYER.velocityY = 0;
    }
}

void func_8012E040(void) {
    s32 vel_boost;
    s32 var_s0;
    s32 xOffset;

    var_s0 = 1;
    if ((PLAYER.facingLeft != 0 && !(g_Player.padPressed & PAD_LEFT)) ||
        (PLAYER.facingLeft == 0 && !(g_Player.padPressed & PAD_RIGHT))) {
        var_s0 = 0;
        DecelerateX(FIX(16.0 / 128));
    }
    if (g_Player.pl_vram_flag & 1) {
        if (D_800B0914 == 2) {
            PLAYER.step_s = 2;
            D_800B0914 = 2;
            func_8010DA48(0xE2);
        } else if ((PLAYER.velocityY > FIX(6.875)) || (D_800B0914 == 3)) {
            PLAYER.step_s = 3;
            D_800B0914 = 3;
            func_8010DA48(0xE5);
            CreateEntFactoryFromEntity(g_CurrentEntity, 0U, 0);
        } else {
            if (D_800B0914 == 0) {
                func_8012CA64();
            }
            if (D_800B0914 == 1) {
                func_8012CB4C();
            }
        }
        PlaySfx(0x64C);
        PLAYER.velocityY = 0;
        return;
    }
    if ((PLAYER.velocityY < FIX(-1)) && (g_Player.pl_vram_flag & 2)) {
        if (PLAYER.velocityY < FIX(-5)) {
            if (PLAYER.facingLeft != 0) {
                xOffset = -3;
            } else {
                xOffset = 3;
            }
            PLAYER.posY.i.hi = PLAYER.posY.i.hi;
            PLAYER.posX.i.hi = xOffset + PLAYER.posX.i.hi;
            CreateEntFactoryFromEntity(g_CurrentEntity, 0x10004U, 0);
            PLAYER.posY.i.hi = PLAYER.posY.i.hi;
            PLAYER.posX.i.hi -= xOffset;
            func_80102CD8(3);
            PlaySfx(0x644);
            PLAYER.velocityX = 0;
            PLAYER.velocityY = 0;
            func_8012CED4();
            return;
        }
        PLAYER.velocityY = 0;
    }
    if (g_Player.padTapped & PAD_SQUARE) {
        func_8012CC30(1);
    }
    switch (D_800B0914) {
    case 0:
        func_8010E27C();
        if (var_s0 != 0) {
            if (ABS(PLAYER.velocityX) < FIX(1)) {
                SetSpeedX(FIX(1));
            }
        }
        break;
    case 1:
        func_8010E27C();
        if (var_s0 != 0) {
            if (ABS(PLAYER.velocityX) >= FIX(1)) {
                DecelerateX(FIX(16.0 / 128));
            } else {
                SetSpeedX(FIX(1));
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
        if (g_Player.pl_vram_flag & 8 && PLAYER.velocityX != 0) {
            D_800B0914 = 1;
        }
        if (ABS(PLAYER.velocityX) < FIX(1)) {
            D_800B0914 = 1;
        }
        if ((PLAYER.facingLeft != 0 && (g_Player.padPressed & PAD_RIGHT)) ||
            (PLAYER.facingLeft == 0 && (g_Player.padPressed & PAD_LEFT))) {
            func_8010E27C();
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

    if (D_80097448[0] >= 13) {
        vel_boost = FIX(5.0 / 128);
    } else {
        vel_boost = FIX(20.0 / 128);
    }
    PLAYER.velocityY += vel_boost;
    if (PLAYER.velocityY > FIX(7)) {
        PLAYER.velocityY = FIX(7);
    }
}

void func_8012E550(void) {
    s32 i;
    u16 playerFrame = PLAYER.animFrameIdx;
    s32 pressingDown = g_Player.padPressed & PAD_DOWN;

    DecelerateX(FIX(0.125));
    if (g_Player.padTapped & PAD_CROSS) {
        if ((g_Player.padPressed & PAD_DOWN)) {
            for (i = 0; i < 4; i++) {
                if ((g_Player.colliders[i].effects & EFFECT_SOLID_FROM_ABOVE)) {
                    g_Player.D_80072F0E = 8;
                    func_8012CED4();
                    PLAYER.animFrameIdx = 4;
                    PLAYER.animFrameDuration = 1;
                    PLAYER.velocityX = 0;
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
    if (g_Player.padTapped & PAD_SQUARE && D_800B0914 != 3) {
        func_8012CC30(0);
        return;
    }
    switch (D_800B0914) {
    case 0:
        if (!pressingDown) {
            func_8010DA48(0xE4);
            D_800B0914 = 2;
            if (playerFrame == 0) {
                PLAYER.animFrameIdx = 1;
            }
        } else if (PLAYER.animFrameDuration < 0) {
            D_800B0914 = 1;
        }
        return;
    case 1:
        if (pressingDown) {
            return;
        }
        func_8010DA48(0xE4);
        D_800B0914 = 2;
        return;
    case 2:
        if (pressingDown) {
            func_8010DA48(0xE3);
            D_800B0914 = 0;
            if (playerFrame != 0) {
                return;
            }
            PLAYER.animFrameIdx = 1;
            return;
        }
    case 3:
        if (PLAYER.animFrameDuration < 0) {
            func_8012CA64();
        }
    }
}

void func_8012E7A4(void) {
    s32 i;
    Entity* entity;
#if defined(VERSION_US)
    if (g_Entities[16].entityId != 0x22) {
        if (CreateEntFactoryFromEntity(g_CurrentEntity, 0x23002CU, 0) == NULL) {
            return;
        }
        func_8010FAF4();
        g_Player.unk66++;
    }
#endif

    for (i = 0; i < 6; i++) {
        D_800B08CC[i].unk0 = 0;
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

    for (entity = &g_Entities[21], i = 0; i < 9; i++, entity++) {
        DestroyEntity(entity);
        entity->entityId = 0x3B;
        entity->params = i;
    }
    DestroyEntity(&g_Entities[30]);
    g_Entities[30].entityId = 0x3C;
    func_8012CED4();
    PLAYER.animFrameIdx = 4;
    PLAYER.animFrameDuration = 4;
    PLAYER.step_s = 8;
    D_80138430 = 0x800;
    PLAYER.unk5A = 0x7E;
    PLAYER.animSet = 0xF;
    PLAYER.rotZ = 0;
    g_Player.unk48 = 0;
    g_Player.unk46 = 0;
    g_Player.unk44 = 0;
    D_8013842C = 0;
    PLAYER.velocityX = 0;
    PLAYER.velocityY = 0;
    PLAYER.palette = 0x810D;
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter.S16.unk0 - 2;
#if defined(VERSION_HD)
    if (g_Entities[16].entityId != 0x22) {
        CreateEntFactoryFromEntity(g_CurrentEntity, 0x23002C, 0);
        func_8010FAF4();
        g_Player.unk66++;
    }
#endif
}

void func_8012E9C0(void) {
    s32 i;

    PLAYER.palette = 0x810D;
    for (i = 0; i < 4; i++) {
        if (D_800ACED0.pairs[i].unk2 < D_800ACE90[i]) {
            D_800ACED0.pairs[i].unk2++;
        }
    }
    func_8010E168(1, 4);
    PLAYER.animFrameDuration = 4;
    PLAYER.velocityY = 0;
    if (g_Entities[16].entityId == 0x22) {
        if (func_8011203C() == 0) {
            return;
        }
        CreateEntFactoryFromEntity(g_CurrentEntity, 0x1B002CU, 0);
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
        i = 0;
        for (i = 0; i < 4; i++) {
            if (D_800ACE88[i] < D_800ACEC0[i].unk2) {
                D_800ACEC0[i].unk2--;
            } else {
                else_cycles += 1;
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
            PLAYER.rotZ = 0;
            PLAYER.drawFlags = 0;
            func_8010DA48(0xCA);
            g_Player.unk66 = 1;
            if (g_Player.unk68 != 0) {
                PLAYER.step_s = 2;
                D_800AFDA6[0] = 0xC7;
            } else {
                PLAYER.step_s = 1;
                D_800AFDA6[0] = 0x5F;
            }
        }
        return;
    case 1:
        if (g_Player.unk66 == 3) {
            func_8010E83C(0);
            if (!(g_Player.pl_vram_flag & 0x8000)) {
                PLAYER.velocityY = FIX(-1);
            }
            PLAYER.palette = 0x8100;
#if defined(VERSION_US)
            g_Player.unk20[0] = 0x18;
#elif defined(VERSION_HD)
            D_800ACEDC_hd = 0x18;
#endif
            g_Player.unk44 |= 0x100;
            PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter.S16.unk0;
            func_80111CC0();
        }
        return;
    case 2:
        if (g_Player.unk66 == 3) {
#if defined(VERSION_US)
            PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter.S16.unk0;
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
    if (D_80097448[1] >= 13) {
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
    s16 var_v1;
    s32 i;

    PLAYER.palette = 0x104;
    PLAYER.blendMode = 0;
// HD version lacks this line!
#if defined(VERSION_US)
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter.S16.unk0 - 2;
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
        var_v1 = 4;
        if (ABS(PLAYER.velocityX) >= FIX(4)) {
            var_v1 = 3;
        }
        if (ABS(PLAYER.velocityX) >= FIX(5)) {
            var_v1--;
        }
        if (ABS(PLAYER.velocityX) >= FIX(6)) {
            var_v1--;
        }
        // Might be misusing D_800AFFB8 here
        D_800AFFB8[i * 2] = var_v1;
    }
    if (D_80138430 < 0x600) {
        D_80138430 = 0x600;
    }
    if (D_80138430 > 0xA00) {
        D_80138430 = 0xA00;
    }
    // HD version lacks this line!

#if defined(VERSION_US)
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter.S16.unk0 - 2;
#endif
}

INCLUDE_ASM("dra/nonmatchings/8D3E8", func_8012F178);

s32 func_8012F83C(s32 x0, s32 y0, s32 x1, s32 y1, s32 distance) {
    s32 diffX = x0 - x1;
    s32 diffY = y0 - y1;

    return (SquareRoot12((SQ(diffX) + SQ(diffY)) << 12) >> 12) >= distance;
}

INCLUDE_ASM("dra/nonmatchings/8D3E8", func_8012F894);

INCLUDE_ASM("dra/nonmatchings/8D3E8", func_80130264);

INCLUDE_ASM("dra/nonmatchings/8D3E8", func_80130618);

INCLUDE_ASM("dra/nonmatchings/8D3E8", func_801309B4);

INCLUDE_ASM("dra/nonmatchings/8D3E8", func_80130E94);

// DECOMP_ME_WIP func_8013136C https://decomp.me/scratch/cu30D
// TODO: branching is wrong jpt_ needs a file split
#ifndef NON_EQUIVALENT
INCLUDE_ASM("dra/nonmatchings/8D3E8", func_8013136C);
#else
void func_8012C600(void);
extern u16 D_8007412E;
extern s32 D_800741CC;
extern s32 D_800741D0;

void func_8013136C(Entity* entity) {
    if (!(g_Player.unk0C & PLAYER_STATUS_WOLF_FORM)) {
        DestroyEntity(entity);
        return;
    }
    if (entity->step == 0) {
        entity->animSet = ANIMSET_DRA(15);
        entity->unk5A = 0x7E;
        entity->palette = PLAYER.palette;
        entity->flags = FLAG_UNK_20000 | FLAG_UNK_40000 | FLAG_UNK_04000000;
        entity->drawFlags = FLAG_DRAW_ROTZ;
        entity->unk20 = -8;
        entity->step++;
    }
    entity->animCurFrame = 80;
    entity->facingLeft = PLAYER.facingLeft;
    entity->posX.val = g_Entities[UNK_ENTITY_13].posX.val; // D_800741CC
    entity->posY.val = g_Entities[UNK_ENTITY_13].posY.val; // D_800741D0
    if (PLAYER.facingLeft == 0) {
        entity->zPriority = PLAYER.zPriority - 5;
        entity->posX.i.hi += 8;
    } else {
        entity->zPriority = PLAYER.zPriority + 5;
        entity->posX.i.hi -= 8;
    }
    entity->posY.i.hi += 3;
    entity->unk1E = g_Entities[UNK_ENTITY_13].unk1E;
    switch (PLAYER.step_s - 1) {
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        break;

    case 0:
        if (D_800B0914 == 1) {
            entity->posY.i.hi -= 2;
            if (PLAYER.facingLeft == 0) {
                entity->posX.i.hi -= 8;
            } else {
                entity->posX.i.hi += 8;
            }
        }
        break;

    case 2:
        switch (D_800B0914) {
        case 1:
            break;

        case 0:
            if (PLAYER.animCurFrame == 33) {
                entity->animCurFrame = 81;
                if (PLAYER.facingLeft == 0) {
                    entity->posX.i.hi += 3;
                } else {
                    entity->posX.i.hi += 6;
                }
            }
            if (PLAYER.animCurFrame == 34) {
                if (PLAYER.facingLeft == 0) {
                    entity->posX.i.hi += 3;
                } else {
                    entity->posX.i.hi += 13;
                }
                entity->animCurFrame = 82;
            }
        case 2:
            break;
        }
        break;
    }
    entity->palette = PLAYER.palette;
    func_8012C600();
}
#endif

// one rotating cross from the cross subweapon crash
INCLUDE_ASM("dra/nonmatchings/8D3E8", func_801315F8);

void func_80131EBC(const char* str, s16 id) { D_80138784[id] = str; }

// gets used later with MakeCdLoc
void SetCdPos(s32 value) { g_CurCdPos = value; }

void MuteCd(void) {
    g_MuteCd = 1;
    D_8013B694 = 0;
}

void UnMuteCd(void) {
    g_MuteCd = 0;
    D_8013B694++;
}

s32 func_80131F28(void) { return D_80138F7C; }

u16 func_80131F38(void) {
    if (g_SeqPlayingId == 0) {
        return 0;
    }
    return g_SeqPlayingId | 0x200;
}

bool func_80131F68(void) {
    if (D_8013B61C == 0) {
        return D_8013901C != 0;
    }
    return true;
}

s16 GetCdVolume(void) { return g_CdVolume; }

void SetReverbDepth(short depth) { SsUtSetReverbDepth(depth, depth); }

void func_80131FCC(void) {
    if (D_8013B680 == 0) {
        D_80138F7C = 0;
    } else {
        s32 temp_v1 = D_8013B680;
        s32 temp_v0 = D_8013B680;
        if (temp_v0 >= 0 && temp_v1 < 3)
            D_80138F7C++;
    }
    D_8013B680 = 0;
}

u8 DoCdCommand(u_char com, u_char* param, u_char* result) {
    g_CdCommandStatus = CdSync(1, g_CdCommandResult);

    if (com == CdlGetlocL) {
        if (g_CdCommandStatus != CdlComplete) {
            CdControl(CdlNop, 0, 0);
            D_8013B680 = 2;
            return D_8013B680;
        }
    } else if (*g_CdCommandResult & CdlStatShellOpen ||
               *g_CdCommandResult & CdlStatSeekError) {
        CdControl(CdlNop, 0, 0);
        D_8013B680 = 2;
        return D_8013B680;
    }

    if (g_CdCommandStatus == CdlComplete) {
        if (CdControl(com, param, result)) {
            D_8013B680 = 0;
            return D_8013B680;
        }
    }

    D_8013B680 = 1;
    return D_8013B680;
}

void SetMaxVolume(void) {
    g_volumeL = 127;
    g_volumeR = 127;
    SsSetMVol(g_volumeL, g_volumeR);
}

void InitSoundVars3(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        g_ChannelGroupVolume[i] = 0;
        g_UnkChannelSetting1[i] = 0;
        g_UnkChannelSetting2[i] = 0;
        D_8013B66C[i] = 0;
        D_8013B5EC[i] = 0;
        D_8013B628[i] = 0;
        D_8013B648[i] = 0;
        D_8013AEA0[i] = 0;
    }
}

void InitSoundVars2(void) {
    s32 i;

    InitSoundVars3();
    D_8013B690 = 0;

    for (i = 0; i < 4; i++) {
        D_8013B650[i] = 0;
        D_8013AED4[i] = 0;
    }
    D_80139804 = 0;
    D_8013B664 = 0;
}

void InitSoundVars1(void) {
    InitSoundVars2();
    g_CdSoundCommand16 = 0;
    D_80138454 = 0;
    do {
        g_SeqPointers[D_80138454] = 0;
    } while (++D_80138454 < 0xA);

    for (D_80138454 = 0; D_80138454 < LEN(g_CdSoundCommandQueue);
         D_80138454++) {
        g_CdSoundCommandQueue[D_80138454] = 0;
    }

    g_CdSoundCommandQueuePos = 0;
    D_8013AEE8 = 0;
    for (D_80138454 = 0; D_80138454 < LEN(g_SoundCommandRingBuffer);
         D_80138454++) {
        g_SoundCommandRingBuffer[D_80138454] = 0;
    }

    g_SoundCommandRingBufferReadPos = 0;
    g_SoundCommandRingBufferWritePos = 0;
    for (D_80138454 = 0; D_80138454 < LEN(g_SfxRingBuffer); D_80138454++) {
        g_SfxRingBuffer[D_80138454].sndId = 0;
        g_SfxRingBuffer[D_80138454].unk02 = 0;
        g_SfxRingBuffer[D_80138454].unk04 = 0;
    }

    D_80139A6C = 0x20;
    D_8013AE7C = 0x7F;
    g_SfxRingBufferReadPos = 0;
    g_sfxRingBufferWritePos = 0;
    D_801390C4 = 0;
    D_8013AEE0 = 0;
    D_8013AE94 = 0;
    D_801390A4 = 0;
    D_80139010 = 0;
    D_80139A74 = 0;
    D_8013B69C = 0;
    g_SeqAccessNum = 0;
    D_80138FBC = 0;
    D_8013901C = 0;
    D_80139800 = 0;
    D_80138F80 = 0;
    D_80139014 = 0;
    D_8013B618 = 0;
    D_8013980C = 0;
    g_CdSoundCommandStep = 0;
    D_801390A0 = 0;
    g_SeqVolume1 = 0x70;
    g_SeqVolume2 = 0x70;
    D_8013B680 = 0;
    D_80138F7C = 0;
    D_801390D8 = 0;
    g_KeyOffChannels = 0;
    g_MuteCd = 0;
    D_8013B694 = 0;
    D_8013B61C = 0;
}

void SetCdVolume(s8 s_num, s16 arg1, s16 arg2) {
    short voll = g_CdVolumeTable[arg1];
    short volr = g_CdVolumeTable[arg2];

    SsSetSerialVol(s_num, voll, volr);
}

void SetMonoStereo(u8 soundMode) {
    CdlATV audioVolume;

    switch (soundMode) {
    case MONO_SOUND:
        if (D_801390A8 != 0) {
            SsSetMono();
            audioVolume.val2 = 128; // CD (R) --> SPU (R)
            audioVolume.val0 = 128; // CD (L) --> SPU (L)
            audioVolume.val3 = 128; // CD Right sound transferred to left
            audioVolume.val1 = 128; // CD Left sound transferred to right
            CdMix(&audioVolume);
            D_8013AE7C = 108;
            D_801390A8 = 0;
        }
        break;
    case STEREO_SOUND:
        if (D_801390A8 != 1) {
            SsSetStereo();
            audioVolume.val2 = 224; // CD (R) --> SPU (R)
            audioVolume.val0 = 224; // CD (L) --> SPU (L)
            audioVolume.val3 = 0;
            audioVolume.val1 = 0;
            CdMix(&audioVolume);
            D_8013AE7C = 127;
            D_801390A8 = 1;
        }
        break;
    }
}

void SoundInit(void) {
    g_SoundInitialized = 1;
    SsInitHot();
    SsSetTickMode(SS_TICK60);
    SetMonoStereo(STEREO_SOUND);
    SsSetReservedVoice(0x10);
    SsStart();
    SsSetTableSize(g_SeqTable, SEQ_TABLE_S_MAX, SEQ_TABLE_T_MAX);
    SsUtSetReverbType(SS_REV_TYPE_STUDIO_B);
    SpuClearReverbWorkArea(SS_REV_TYPE_STUDIO_B);
    SsUtReverbOn();
    SetMaxVolume();
    g_CdVolume = 0x78;
    SsSetSerialAttr(0, 0, 1);
    SetCdVolume(0, g_CdVolume, g_CdVolume);
    g_CdMode[0] = CdlModeSpeed | CdlModeRT | CdlModeSF;
    DoCdCommand(CdlSetmode, g_CdMode, 0);
    InitSoundVars1();
    SetReverbDepth(10);
    SpuSetTransferMode(0);
    SpuSetIRQCallback(NULL);
    CdReadyCallback(NULL);
    SpuMallocWithStartAddr(0x1010, 0x10000);
}

s32 func_801326D8(void) {
    if (D_8013901C != 0)
        return 1;
    if (g_SeqPlayingId != 0)
        return 3;
    return (D_801390D8 != 0) * 2;
}

void SoundWait(void) {
    while (!(func_801326D8() & 0xFF) == 0) {
        VSync(0);
        func_801361F8();
    }
}

void MuteSound(void) {
    SsSetMVol(0, 0);
    SsSetSerialAttr(SS_SERIAL_A, SS_MIX, SS_SOFF);
    SetCdVolume(SS_SERIAL_A, 0, 0);
    SetMaxVolume();
    InitSoundVars1();
}

INCLUDE_ASM("dra/nonmatchings/8D3E8", func_801327B4);

// last entries seem like a different table
s16 g_CdVolumeTable[] = {
    0x0000, 0x0002, 0x0004, 0x0006, 0x0008, 0x000A, 0x000C, 0x000E, 0x0010,
    0x0012, 0x0014, 0x0016, 0x0018, 0x001A, 0x001C, 0x001E, 0x0020, 0x0022,
    0x0024, 0x0026, 0x0028, 0x002A, 0x002C, 0x002E, 0x0030, 0x0032, 0x0034,
    0x0036, 0x0038, 0x003A, 0x003C, 0x003E, 0x0040, 0x0041, 0x0042, 0x0043,
    0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C,
    0x004D, 0x004E, 0x004F, 0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055,
    0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E,
    0x005F, 0x0060, 0x0060, 0x0061, 0x0061, 0x0062, 0x0062, 0x0063, 0x0063,
    0x0064, 0x0064, 0x0065, 0x0065, 0x0066, 0x0066, 0x0067, 0x0067, 0x0068,
    0x0068, 0x0069, 0x0069, 0x006A, 0x006A, 0x006B, 0x006B, 0x006C, 0x006C,
    0x006D, 0x006D, 0x006E, 0x006E, 0x006F, 0x006F, 0x0070, 0x0070, 0x0071,
    0x0071, 0x0072, 0x0072, 0x0073, 0x0073, 0x0074, 0x0074, 0x0075, 0x0075,
    0x0076, 0x0076, 0x0077, 0x0077, 0x0078, 0x0078, 0x0079, 0x0079, 0x007A,
    0x007A, 0x007B, 0x007B, 0x007C, 0x007C, 0x007D, 0x007D, 0x007E, 0x007E,
    0x007F, 0x007F, 0x0000, 0x007F, 0x0010, 0x007F, 0x0020, 0x007F, 0x0030,
    0x007F, 0x0040, 0x007F, 0x0050, 0x007F, 0x0060, 0x007F, 0x0070, 0x007F};

s16 g_VolumeTable[] = {
    0x007F, 0x007F, 0x007F, 0x0070, 0x007F, 0x0060, 0x007F, 0x0050, 0x007F,
    0x0040, 0x007F, 0x0030, 0x007F, 0x0020, 0x007F, 0x0010, 0x007F, 0x0000};

s32 g_DebugEnabled = 0;
s32 D_800BD1C4 = 0;

#ifdef VERSION_US
s32 g_VabAddrs[] = {0x00001010, 0x00042CC0, 0x00050E50,
                    0x00060A40, 0x00060A40, 0x00060A40};
#else // VERSION_HD
s32 g_VabAddrs[] = {0x00001010, 0x00042CC0, 0x00050E90,
                    0x00060D40, 0x00060D40, 0x00060D40};
#endif

void func_80132A04(s16 voice, s16 vabId, s16 prog, s16 tone, s16 note,
                   s16 volume, s16 distance) {
    if (distance == 0) {
        g_VolL = volume;
        g_VolR = volume;
    } else {
        g_VolR = (volume * g_VolumeTable[distance * 2 + 0]) >> 7;
        g_VolL = (volume * g_VolumeTable[distance * 2 + 1]) >> 7;
    }

    if (voice >= 0 && voice < 0x18) {
        SsUtKeyOnV(voice, vabId, prog, tone, note, 0, g_VolL, g_VolR);
        SsUtKeyOnV(voice + 1, vabId, prog, 1 - -tone, note, 0, g_VolL, g_VolR);
        return;
    }

    switch (voice) {
    case 0x1E:
        func_801327B4(0, 4, vabId, prog, tone, note, g_VolL, g_VolR);
        break;
    case 0x1F:
        func_801327B4(4, 8, vabId, prog, tone, note, g_VolL, g_VolR);
        break;
    case 0x20:
        func_801327B4(8, 12, vabId, prog, tone, note, g_VolL, g_VolR);
        break;
    case 0x21:
        func_801327B4(14, 18, vabId, prog, tone, note, g_VolL, g_VolR);
        break;
    }
}

void AddCdSoundCommand(s16 arg0) {
    s32 i;
    s32 isFound;

    if (arg0 == 6) {
        isFound = 0;
        for (i = 0; i < g_CdSoundCommandQueuePos; i++) {
            if (g_CdSoundCommandQueue[i] == 0xC) {
                isFound = 1;
            }
        }

        if (isFound) {
            g_DebugEnabled++;
            g_CdSoundCommandQueue[g_CdSoundCommandQueuePos] = 0xE;
            g_CdSoundCommandQueuePos++;
            if (g_CdSoundCommandQueuePos == 0x100) {
                D_8013AEE8++;
                for (i = 1; i < 0x100; i++) {
                    g_CdSoundCommandQueue[i] = 0;
                }

                g_CdSoundCommandQueuePos = 1;
                g_CdSoundCommandQueue[g_CdSoundCommandQueuePos] = 0xE;
                g_CdSoundCommandQueuePos++;
            }
        }
    }
    g_CdSoundCommandQueue[g_CdSoundCommandQueuePos] = arg0;
    g_CdSoundCommandQueuePos++;
    if (g_CdSoundCommandQueuePos == 0x100) {
        D_8013AEE8++;
        for (i = 1; i < 0x100; i++) {
            g_CdSoundCommandQueue[i] = 0;
        }

        g_CdSoundCommandQueuePos = 1;
    }
}

u16 AdvanceCdSoundCommandQueue(void) {
    s32 i;

    for (i = 0; i < 255; i++) {
        g_CdSoundCommandQueue[i] = g_CdSoundCommandQueue[i + 1];
    }
    return --g_CdSoundCommandQueuePos;
}

#define ENCODE_BCD(x) ((((x) / 10) << 4) + ((x) % 10))

void MakeCdLoc(u32 address, CdlLOC* cd_loc) {
    u32 minutes;
    cd_loc->sector = ENCODE_BCD(address % 75);
    cd_loc->second = ENCODE_BCD(address / 75 % 60);
    minutes = address / 75 / 60;
    cd_loc->minute = ENCODE_BCD(minutes);
}
