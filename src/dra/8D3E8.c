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
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x100, 69), 0);
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
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x100, 69), 0);
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
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
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
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
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
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
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
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x100, 4), 0);
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
        if (CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x2300, 44), 0) == NULL) {
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
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x2300, 44), 0);
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
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x1b00, 44), 0);
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

// When Alucard uses the cross subweapon for 100 hearts.
// Entity ID 7, blueprint #7 (this is a coincidence)
void EntityGiantSpinningCross(Entity* self) {
    MATRIX m;
    SVECTOR rot;
    VECTOR trans1;
    SVECTOR pos;
    SVECTOR sp50;
    s32 z;
    s32 nclip;
    Primitive* prim;
    s32 i;
    u8* primUVCoords;
    SVECTOR* temp_a3;
    SVECTOR** vectors_ptr;
    u16 priority;

    pos = D_800E2024;
    sp50 = D_800E202C;

    if (self->step == 0) {
        self->primIndex = g_api.func_800EDB58(PRIM_GT4, 46);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->tpage = 0x1C;
            prim->blendMode = 0x100 | BLEND_VISIBLE;
            prim = prim->next;
        }
        func_8011A290(self);
        self->hitboxHeight = 0x50;
        self->hitboxWidth = 0xC;
        self->posY.i.hi = 0x160;
        self->velocityY = FIX(-6);
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
        self->facingLeft = 0;
        self->ext.giantcross.unk7C = 0;
        self->ext.giantcross.unk7E = 0x400;
        PlaySfx(0x661);
        self->step++;
        primUVCoords = &D_800B0F94[0][0];
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 46; i++, prim = prim->next, primUVCoords += 5) {
            prim->clut = (primUVCoords[4] & 0xF) | 0x1A0;
            switch (primUVCoords[4] & 0xF0) {
            case 0x10:
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                break;
            case 0x20:
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1];
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1];
                break;
            case 0x30:
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1];
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1];
                break;
            case 0x40:
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                break;
            case 0x50:
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                break;
            case 0x60:
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1];
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1];
                break;
            case 0x70:
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1];
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1];
                break;
            default:
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                break;
            }
        }
        return;
    }
    if (self->posY.i.hi < -0x40) {
        DestroyEntity(self);
        return;
    }
    if (self->posY.i.hi < 0) {
        self->velocityY -= FIX(0.5);
    }
    self->posY.val += self->velocityY;
    self->ext.giantcross.unk7C += 0x60;
    self->ext.giantcross.unk7E += 0x60;
    trans1.vx = -(rcos(self->ext.giantcross.unk7C) * 0x60) >> 0xC;
    trans1.vy = self->posY.i.hi - 0x80;
    trans1.vz = ((rsin(self->ext.giantcross.unk7C) * 0x60) >> 0xC) + 0x180;
    rot.vy = self->ext.giantcross.unk7E;
    rot.vz = 0x40;
    rot.vx = 0;

    SetGeomOffset(self->posX.i.hi, 120);
    gte_SetGeomScreen(320);
    RotMatrix(&rot, &m);
    TransMatrix(&m, &trans1);
    gte_SetRotMatrix(&m);
    gte_SetTransMatrix(&m);
    gte_ldv0(&pos);
    gte_rtps();
    prim = &g_PrimBuf[self->primIndex];
    vectors_ptr = &D_800B0CB4;
    gte_stsxy2(&prim->x0);
    gte_stszotz(&z);
    self->hitboxOffX = prim->x0 - self->posX.i.hi;
    self->hitboxOffY = prim->y0 - self->posY.i.hi;
    for (i = 0; i < 46; i++, prim = prim->next, vectors_ptr += 4) {
        gte_ldv3(vectors_ptr[0], vectors_ptr[1], vectors_ptr[3]);
        gte_rtpt();
        temp_a3 = vectors_ptr[2];
        prim->type = 4;
        gte_nclip();
        prim->blendMode = BLEND_VISIBLE;
        gte_stopz(&nclip);
        if (nclip < 0) {
            continue;
        }
        gte_stsxy3(&prim->x0, &prim->x1, &prim->x2);
        gte_ldv0(temp_a3);
        gte_rtps();
        prim->blendMode = 0;
        if (z < 16) {
            priority = 0x1B6;
        } else if (z >= 999) {
            priority = 0x10;
        } else {
            priority = 0x120;
            priority -= z;
        }
        prim->priority = priority;
        gte_stsxy(&prim->x3);
    }
}
