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
            SetPlayerAnim(0xE1);
        }

        if (!(directionsPressed & (PAD_LEFT | PAD_RIGHT))) {
            func_8012CA64();
        }
        return;
    case 2:
        if ((g_Player.padTapped & PAD_SQUARE) &&
            (abs(PLAYER.velocityX) < FIX(3))) {
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
            PLAYER.ext.player.anim = 0xE0;
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
            (abs(PLAYER.velocityX) < FIX(3))) {
            func_8012CC30(0);
            return;
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
            SetPlayerAnim(0xE2);
            D_800B0914 = 2;
            if (abs(PLAYER.velocityX) < FIX(2)) {
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

    if ((g_Player.D_80072F00[5] != 0) && (g_Player.padTapped & PAD_CROSS)) {
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
            SetPlayerAnim(0xE2);
        } else if (PLAYER.velocityY > FIX(6.875)) {
            PLAYER.step_s = 3;
            D_800B0914 = 3;
            SetPlayerAnim(0xE5);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
        } else {
            func_8012CA64();
        }
        PLAYER.velocityY = 0;
        PlaySfx(SFX_UNK_64C);
        return;
    }
    if (g_Player.padTapped & PAD_SQUARE) {
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

    if ((g_Player.D_80072F00[5] != 0) && (g_Player.padTapped & PAD_CROSS)) {
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
        PlaySfx(SFX_UNK_64C);
        if (PLAYER.velocityY > FIX(6.875)) {
            PLAYER.step_s = 3;
            D_800B0914 = 3;
            SetPlayerAnim(0xE5);
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
            SetPlayerAnim(0xE2);
        } else if ((PLAYER.velocityY > FIX(6.875)) || (D_800B0914 == 3)) {
            PLAYER.step_s = 3;
            D_800B0914 = 3;
            SetPlayerAnim(0xE5);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
        } else {
            if (D_800B0914 == 0) {
                func_8012CA64();
            }
            if (D_800B0914 == 1) {
                func_8012CB4C();
            }
        }
        PlaySfx(SFX_UNK_64C);
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
            PlaySfx(NA_SE_EN_ROCK_BREAK);
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
        CheckMoveDirection();
        if (var_s0 != 0) {
            if (abs(PLAYER.velocityX) < FIX(1)) {
                SetSpeedX(FIX(1));
            }
        }
        break;
    case 1:
        CheckMoveDirection();
        if (var_s0 != 0) {
            if (abs(PLAYER.velocityX) >= FIX(1)) {
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
        if (abs(PLAYER.velocityX) < FIX(1)) {
            D_800B0914 = 1;
        }
        if ((PLAYER.facingLeft != 0 && (g_Player.padPressed & PAD_RIGHT)) ||
            (PLAYER.facingLeft == 0 && (g_Player.padPressed & PAD_LEFT))) {
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
        if (g_Player.padPressed & PAD_DOWN) {
            for (i = 0; i < 4; i++) {
                if (g_Player.colliders[i].effects & EFFECT_SOLID_FROM_ABOVE) {
                    g_Player.D_80072F00[7] = 8;
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
            SetPlayerAnim(0xE4);
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
        SetPlayerAnim(0xE4);
        D_800B0914 = 2;
        return;
    case 2:
        if (pressingDown) {
            SetPlayerAnim(0xE3);
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

    for (entity = &g_Entities[21], i = 0; i < 9; i++, entity++) {
        DestroyEntity(entity);
        entity->entityId = 0x3B;
        entity->params = i;
    }
    // We create entity #60, which is func_8013136C
    DestroyEntity(&g_Entities[30]);
    g_Entities[30].entityId = 60;

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
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter.unk - 2;
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
        if (D_800ACED0[i].y < D_800ACE90[i]) {
            D_800ACED0[i].y++;
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
            if (D_800ACE88[i] < D_800ACEC0[i].y) {
                D_800ACEC0[i].y--;
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
            PLAYER.drawFlags = FLAG_DRAW_DEFAULT;
            SetPlayerAnim(0xCA);
            g_Player.unk66 = 1;
            if (g_Player.unk68 != 0) {
                PLAYER.step_s = 2;
                D_800AFDA4[1] = 0xC7;
            } else {
                PLAYER.step_s = 1;
                D_800AFDA4[1] = 0x5F;
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
            g_Player.unk20 = 0x18;
#elif defined(VERSION_HD)
            D_800ACEDC_hd = 0x18;
#endif
            g_Player.unk44 |= 0x100;
            PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter.unk;
            func_80111CC0();
        }
        return;
    case 2:
        if (g_Player.unk66 == 3) {
#if defined(VERSION_US)
            PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter.unk;
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
    PLAYER.drawMode = DRAW_DEFAULT;
// HD version lacks this line!
#if defined(VERSION_US)
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter.unk - 2;
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
        if (abs(PLAYER.velocityX) >= FIX(4)) {
            var_v1 = 3;
        }
        if (abs(PLAYER.velocityX) >= FIX(5)) {
            var_v1--;
        }
        if (abs(PLAYER.velocityX) >= FIX(6)) {
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
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter.unk - 2;
#endif
}

void func_8012F178(Primitive* prim, s32 count, bool finishUp) {
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
    scratchpad_8012F178* scratchpad;

#ifdef VERSION_PSP
#define LEFTVEL -0x13
#define TPAGE 0x4118
#define V_OFFSET 0
#else
#define LEFTVEL -0x14
#define TPAGE 0x118
#define V_OFFSET 0xC0
#endif

    scratchpad = (scratchpad_8012F178*)SPAD(0);
    scratchpad->prim = prim;
    scratchpad->i_limit = count;
    scratchpad->helper = &D_800B08CC[0];
    // D_800B08CC has length 6 but we go i < 5? Odd.
    for (scratchpad->i = 0; scratchpad->i < 5; scratchpad->i++,
        scratchpad->helper++) {
        if (scratchpad->i == scratchpad->i_limit && scratchpad->helper->state) {
            scratchpad->helper->state = 2;
        }
        switch (scratchpad->helper->state) {
        case 0:
            scratchpad->prim->u0 = scratchpad->prim->u2 = 0;
            scratchpad->prim->u1 = scratchpad->prim->u3 = 0x3F;
            scratchpad->prim->v0 = scratchpad->prim->v1 = V_OFFSET;
            scratchpad->prim->v2 = scratchpad->prim->v3 = V_OFFSET + 0x3F;
            scratchpad->prim->tpage = TPAGE;
            scratchpad->prim->priority = PLAYER.zPriority - 6;
            scratchpad->prim->drawMode = 0x13F;
            scratchpad->helper->state++;
        case 1:
#if defined(VERSION_US)
            scratchpad->prim->priority = PLAYER.zPriority - 6;
#endif
            scratchpad->prim->drawMode |= DRAW_HIDE;
            break;
        case 2:
            scratchpad->helper->facingLeft = PLAYER.facingLeft;
            scratchpad->x = PLAYER.posX.i.hi;
            scratchpad->y = PLAYER.posY.i.hi;
            if (!PLAYER.facingLeft) {
                scratchpad->velX = -0x2C;
            } else {
                scratchpad->velX = LEFTVEL;
            }
            scratchpad->velY = -0x18;
            scratchpad->x += scratchpad->velX;
            scratchpad->y += scratchpad->velY;
            scratchpad->prim->x0 = scratchpad->prim->x2 = scratchpad->x;
            scratchpad->prim->x1 = scratchpad->prim->x3 = scratchpad->x + 0x3F;
            scratchpad->prim->y0 = scratchpad->prim->y1 = scratchpad->y;
            scratchpad->prim->y2 = scratchpad->prim->y3 = scratchpad->y + 0x3F;
            scratchpad->prim->drawMode &= ~DRAW_HIDE;
            scratchpad->prim->r0 = scratchpad->prim->b0 = scratchpad->prim->g0 =
                scratchpad->prim->r1 = scratchpad->prim->b1 =
                    scratchpad->prim->g1 = scratchpad->prim->r2 =
                        scratchpad->prim->b2 = scratchpad->prim->g2 =
                            scratchpad->prim->r3 = scratchpad->prim->b3 =
                                scratchpad->prim->g3 = 0x80;
#if defined(VERSION_US)
            scratchpad->prim->priority = PLAYER.zPriority - 6;
#endif
            scratchpad->helper->timer = 0x20;
            scratchpad->helper->state++;
            break;
        case 3:
            if (scratchpad->helper->facingLeft) {
                if (scratchpad->prim->g2 > 12) {
                    scratchpad->prim->g2 -= 6;
                } else {
                    scratchpad->prim->g2 = 0;
                }
                if (scratchpad->prim->g3 > 12) {
                    scratchpad->prim->g3 -= 12;
                } else {
                    scratchpad->prim->g3 = 0;
                }
            } else {
                if (scratchpad->prim->g2 > 12) {
                    scratchpad->prim->g2 -= 12;
                } else {
                    scratchpad->prim->g2 = 0;
                }
                if (scratchpad->prim->g3 > 12) {
                    scratchpad->prim->g3 -= 6;
                } else {
                    scratchpad->prim->g3 = 0;
                }
            }
            scratchpad->prim->r0 = scratchpad->prim->b0 = scratchpad->prim->g0 =
                scratchpad->prim->r2 = scratchpad->prim->b2 =
                    scratchpad->prim->g2;
            scratchpad->prim->r1 = scratchpad->prim->b1 = scratchpad->prim->g1 =
                scratchpad->prim->r3 = scratchpad->prim->b3 =
                    scratchpad->prim->g3;
#if defined(VERSION_US)
            scratchpad->prim->priority = PLAYER.zPriority - 6;
#endif
            if (--scratchpad->helper->timer == 0) {
                scratchpad->helper->state = 1;
            }
            scratchpad->prim->drawMode &= ~DRAW_HIDE;
            break;
        }
        scratchpad->prim = scratchpad->prim->next;
    }
    // Not sure what the rest of this function is for. But to do it,
    // we have to have finishUp set. If not, we hide and exit.
    if (!finishUp) {
        scratchpad->prim->drawMode |= DRAW_HIDE;
        return;
    }
    // Rest of the function is what I'm calling the finishUp routine.
    scratchpad->prim->u0 = scratchpad->prim->u2 = 0;
    scratchpad->prim->u1 = scratchpad->prim->u3 = 0x3F;
    scratchpad->prim->v0 = scratchpad->prim->v1 = V_OFFSET;
    scratchpad->prim->v2 = scratchpad->prim->v3 = V_OFFSET + 0x3F;
    scratchpad->prim->tpage = TPAGE;
    scratchpad->prim->priority = PLAYER.zPriority;
    scratchpad->prim->drawMode = 0x335;
    scratchpad->helper->facingLeft = PLAYER.facingLeft;
    scratchpad->x = PLAYER.posX.i.hi;
    scratchpad->y = PLAYER.posY.i.hi;
    if (!PLAYER.facingLeft) {
        scratchpad->velX = -0x2C;
    } else {
        scratchpad->velX = LEFTVEL;
    }
    scratchpad->velY = -0x18;
    scratchpad->x += scratchpad->velX;
    scratchpad->y += scratchpad->velY;
    scratchpad->prim->x0 = scratchpad->prim->x2 = scratchpad->x;
    scratchpad->prim->x1 = scratchpad->prim->x3 = scratchpad->x + 0x3F;
    scratchpad->prim->y0 = scratchpad->prim->y1 = scratchpad->y;
    scratchpad->prim->y2 = scratchpad->prim->y3 = scratchpad->y + 0x3F;

    scratchpad->i = abs(PLAYER.velocityX) + FIX(-3) >> 8;
    if (scratchpad->i > 0x7F) {
        scratchpad->i = 0x7F;
    }
    scratchpad->colors[1] = (u8)scratchpad->i + 0x80;

    scratchpad->i = abs(PLAYER.velocityX) + FIX(-3) >> 8;
    if (scratchpad->i > 0x7F) {
        scratchpad->i = 0x7F;
    }
    scratchpad->colors[0] = 0x80 - (u8)scratchpad->i;

    if (scratchpad->helper->facingLeft) {
        scratchpad->prim->b0 = scratchpad->prim->g2 = scratchpad->colors[1];
        scratchpad->prim->g3 = scratchpad->colors[0];
        scratchpad->prim->b1 = scratchpad->prim->b2 = scratchpad->prim->b3 =
            0xFF;
    } else {
        scratchpad->prim->b1 = scratchpad->prim->g2 = scratchpad->colors[0];
        scratchpad->prim->g3 = scratchpad->colors[1];
        scratchpad->prim->b0 = scratchpad->prim->b2 = scratchpad->prim->b3 =
            0xFF;
    }
    scratchpad->prim->r0 = scratchpad->prim->g0 = scratchpad->prim->r2 =
        scratchpad->prim->g2;
    scratchpad->prim->r1 = scratchpad->prim->g1 = scratchpad->prim->r3 =
        scratchpad->prim->g3;
}

s32 func_8012F83C(s32 x0, s32 y0, s32 x1, s32 y1, s32 distance) {
    s32 diffX = x0 - x1;
    s32 diffY = y0 - y1;

    return (SquareRoot12((SQ(diffX) + SQ(diffY)) << 12) >> 12) >= distance;
}

INCLUDE_ASM("dra/nonmatchings/8D3E8", func_8012F894);
