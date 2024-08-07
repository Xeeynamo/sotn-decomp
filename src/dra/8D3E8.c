#include "dra.h"
#include "dra_bss.h"
#include "objects.h"
#include "sfx.h"

static s32 D_800B0924[] = {14, 6, 4, 4, 6, 14};

static u16 D_800B093C[] = {69, 0};
static u16 D_800B0940[] = {49, 0};
static u16 D_800B0944[] = {48, 0};
static u16 D_800B0948[] = {36, 37, 38, 39, 40, 41, 42, 43, 0};
static u16 D_800B095C[] = {44, 45, 46, 47, 48, 49, 50, 51, 0};
static u16 D_800B0970[] = {69, 67, 68, 68, 67, 69, -1};
static u16 D_800B0980[] = {52, 53, -1};
static u16 D_800B0988[] = {53, 52, -1};
static u16 D_800B0990[] = {55, 56, 57, 58, 58, 58, 58, 61, 62, 63, 64, -1};
static u16 D_800B09A8[] = {59, 60, 61, 62, 63, 64, 64, -1};
static u16 D_800B09B8[] = {55, 56, 57, 61, 62, 63, 64, -1};
static u16 D_800B09C8[] = {59, 60, 61, 62, 63, 64, -1};
static u16 D_800B09D8[] = {52, 54, 52, -1};
static u16 D_800B09E0[] = {53, -1};
static u16 D_800B09E4[] = {60, 61, 62, 63, 60, 61, 62, 63, 0};
static u16* D_800B09F8[] = {
    D_800B093C, D_800B0940, D_800B095C, D_800B0970, D_800B0948, D_800B0980,
    D_800B0988, D_800B09D8, D_800B09C8, D_800B0990, D_800B09B8, D_800B09E0,
    D_800B09A8, D_800B0990, D_800B09E4, D_800B0990, D_800B0944,
};

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
            s->prim->drawMode = 0x13F;
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
    s->prim->drawMode = 0x335;
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

s32 func_8012F83C(s32 x0, s32 y0, s32 x1, s32 y1, s32 distance) {
    s32 diffX = x0 - x1;
    s32 diffY = y0 - y1;

    return (SquareRoot12((SQ(diffX) + SQ(diffY)) << 12) >> 12) >= distance;
}

static s16 D_800B0A3C[] = {1, 2, 1, 0, 1, 2, 1, 0};
static s16 D_800B0A4C[] = {0, 1, 2, 3, 4, 3, 2, 1};

void func_8012F894(Entity* self) {
    u16* chosenAnimArray;
    s32 f178_count;
    bool f178_finish;
    Collider collider1;
    Collider collider2;
    Primitive* prim;

    s32 playerX;
    s32 playerY;
    s32 var_s1;
    s32 angle;
    s32 hitboxY;
    s32 hitboxX;
    s32 animControl;
    s32 chosenAnimIndex;

    s32 vram_flag_F000;

    if (!(g_Player.unk0C & PLAYER_STATUS_WOLF_FORM)) {
        DestroyEntity(self);
        return;
    }
    if (PLAYER.ext.player.anim == 0xE1) {
        D_800B0920 = D_800B0924[PLAYER.animFrameIdx];
    }
    if (self->step == 0) {
        self->primIndex = AllocPrimitives(PRIM_GT4, 6);
        if (self->primIndex == -1) {
            return;
        }
        self->animSet = 0xF;
        self->unk5A = 0x7E;
        self->palette = PLAYER.palette;
#ifdef VERSION_HD
        self->zPriority = PLAYER.zPriority - 2;
#endif
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_40000 |
                      FLAG_UNK_20000;
        self->step++;
    }
    animControl = 0;
#ifndef VERSION_HD
    self->zPriority = PLAYER.zPriority - 2;
#endif
    self->facingLeft = PLAYER.facingLeft;
    if (abs(PLAYER.velocityX) > FIX(3)) {
        PLAYER.drawFlags = self->drawFlags |= DRAW_HIDE;
        PLAYER.drawMode = self->drawMode =
            DRAW_UNK_40 | DRAW_TPAGE | DRAW_TPAGE2;

        var_s1 = (abs(PLAYER.velocityX) - FIX(3)) >> 11;
        if (var_s1 > 0x80) {
            var_s1 = 0x80;
        }
        PLAYER.unk6C = self->unk6C = 0xFF - var_s1;
    } else {
        self->drawFlags &= ~DRAW_HIDE;
        PLAYER.drawFlags = self->drawFlags;
        PLAYER.drawMode = self->drawMode = DRAW_DEFAULT;
    }
    switch (PLAYER.step_s) {
    case 1:
        if (D_800B0914 == 1) {
            D_800B0920 = 8;
        }
        break;
    case 2:
        switch (D_800B0914) {
        case 0:
            break;
        case 1:
        case 3:
            D_800B0920 -= D_800B0A3C[PLAYER.animFrameIdx];
            break;
        case 2:
            D_800B0920 -= D_800B0A4C[PLAYER.animFrameIdx];
            break;
        case 4:
            break;
        }
        break;
    case 4:
        if (PLAYER.velocityY < 0) {
            if (D_80138430 > 0x700) {
                D_80138430 -= 0x20;
            }
            D_800B0920 = 10;
        } else {
            if (D_80138430 < 0x7C0) {
                D_80138430 += 0x20;
            }
            D_800B0920 = 12;
        }
        break;
    case 5:
    case 8:
        D_800B0920 = 0xC;
        break;
    case 7:
        if (D_80138430 < 0x900) {
            D_80138430 += 0x20;
        }
        break;
    case 9:
        D_800B0920 -= D_800B0A3C[PLAYER.animFrameIdx];
        break;
    }

    playerX = PLAYER.posX.i.hi;
    playerY = PLAYER.posY.i.hi + 25;
    if (!(g_Player.pl_vram_flag & 1) || (PLAYER.step_s == 7)) {
        angle = D_80138430;
        if (PLAYER.facingLeft) {
            angle = 0x800 - D_80138430;
        }
        if (g_Player.unk04 & 0x40) {
            angle = 0x800;
            if (PLAYER.facingLeft) {
                angle = 0x800 - angle;
            }
        }
        hitboxX = (((rcos(angle) >> 4) * D_800B0920) >> 8) + playerX;
        hitboxY = playerY + -(((rsin(angle) >> 4) * D_800B0920) >> 8);
    } else {
        var_s1 = 1;
        hitboxY = playerY + 2;
        // This loop is really gross, I will appreciate you forever if you can
        // make it look more reasonable.
        while (1) {
            if (PLAYER.facingLeft) {
                hitboxX = playerX + var_s1;
            } else {
                hitboxX = playerX - var_s1;
            }
            hitboxY += 2;
            CheckCollision(hitboxX, hitboxY, &collider1, 0);
            if (collider1.effects & EFFECT_SOLID) {
                CheckCollision(
                    hitboxX, (hitboxY + collider1.unk18) - 1, &collider2, 0);
                if (!(collider2.effects & EFFECT_SOLID)) {
                    hitboxY += collider1.unk18;
                    if (func_8012F83C(playerX, playerY, hitboxX, hitboxY,
                                      D_800B0920) != 0) {
                        animControl = 1;
                        if (collider1.effects & EFFECT_UNK_8000) {
                            animControl = 3;
                            if (PLAYER.facingLeft &&
                                (collider1.effects & EFFECT_UNK_4000)) {
                                animControl = 2;
                            }
                            if (!PLAYER.facingLeft &&
                                !(collider1.effects & EFFECT_UNK_4000)) {
                                animControl = 2;
                            }
                        }
                        angle = ratan2(-(hitboxY - playerY), hitboxX - playerX);
                        break;
                    }
                    var_s1++;
                    continue;
                }
                if ((collider2.effects &
                     (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) !=
                    (EFFECT_UNK_8000 | EFFECT_SOLID)) {
                    continue;
                }
                hitboxY += collider1.unk18 - 1 + collider2.unk18;
                if (func_8012F83C(
                        playerX, playerY, hitboxX, hitboxY, D_800B0920)) {
                    animControl = 3;
                    if (PLAYER.facingLeft &&
                        (collider1.effects & EFFECT_UNK_4000)) {
                        animControl = 2;
                    }
                    if (!PLAYER.facingLeft &&
                        !(collider1.effects & EFFECT_UNK_4000)) {
                        animControl = 2;
                    }

                    angle = ratan2(-(hitboxY - playerY), hitboxX - playerX);
                    break;
                }
                var_s1++;
                continue;
            }
            if (var_s1 < 5) {
                var_s1++;
                hitboxY -= 2;
                continue;
            }

            vram_flag_F000 = g_Player.pl_vram_flag & 0xF000;
            angle = 0x800;
            if (vram_flag_F000 == 0xE000) {
                angle = 0x760;
            }
            if (vram_flag_F000 == 0xD000) {
                angle = 0x6D2;
            }
            if (vram_flag_F000 == 0xC000) {
                angle = 0x600;
            }
            if (vram_flag_F000 == 0x8000) {
                angle = 0xA00;
            }
            if (vram_flag_F000 == 0x9000) {
                angle = 0x92E;
            }
            if (vram_flag_F000 == 0xA000) {
                angle = 0x8A0;
            }
            if (PLAYER.facingLeft) {
                angle -= 0x800;
            }
            hitboxX = (((rcos(angle) >> 4) * D_800B0920) >> 8) + playerX;
            hitboxY = playerY + -(((rsin(angle) >> 4) * D_800B0920) >> 8);
            animControl = 0;
            if (var_s1 <= 10) {
                if ((PLAYER.facingLeft || (playerX - D_800B0920) >= 0) &&
                    (!PLAYER.facingLeft || (playerX + D_800B0920) < 0x101) &&
                    ((PLAYER.step_s == 1) || (PLAYER.step_s == 3))) {
                    if (!PLAYER.facingLeft) {
                        CheckCollision((PLAYER.posX.i.hi - D_800B0920) - 1,
                                       PLAYER.posY.i.hi + 23, &collider1, 0);
                        if (!(collider1.effects & EFFECT_SOLID)) {
                            PLAYER.velocityX = FIX(-1);
                            func_8012CB0C();
                        }
                    } else {
                        CheckCollision(PLAYER.posX.i.hi + D_800B0920 + 1,
                                       PLAYER.posY.i.hi + 23, &collider1, 0);
                        if (!(collider1.effects & EFFECT_SOLID)) {
                            PLAYER.velocityX = FIX(1);
                            func_8012CB0C();
                        }
                    }
                }
            }
            break; // Breaking here means the loop will never loop.
            // Only way to repeat is through the many Continue statements.
        }
    }

    if (!PLAYER.facingLeft) {
        if (playerX - D_800B0920 < 0) {
            hitboxX = playerX - D_800B0920;
            hitboxY = playerY;
            angle = 0x800;
        }
        D_80138430 = angle;
    } else {
        if (playerX + D_800B0920 > 0x100) {
            hitboxX = playerX + D_800B0920;
            hitboxY = playerY;
            angle = 0;
        }
        D_80138430 = 0x800 - angle;
    }
    D_80138430 &= 0xFFF;
    self->posX.i.hi = hitboxX;
    self->posY.i.hi = hitboxY - 0x17;
    self->posX.i.lo = PLAYER.posX.i.lo;
    self->posY.i.lo = PLAYER.posY.i.lo;
    chosenAnimIndex = PLAYER.ext.player.anim - 0xDE;
    if ((PLAYER.step_s == 1) && (D_800B0914 == 0)) {
        if (animControl == 2) {
            chosenAnimIndex = 1;
        }
        if (animControl == 1) {
            chosenAnimIndex = 0;
        }
        if (animControl == 3) {
            chosenAnimIndex = 0x10;
        }
    }
    chosenAnimArray = D_800B09F8[chosenAnimIndex];
    self->animCurFrame = chosenAnimArray[PLAYER.animFrameIdx];
    if (self->animCurFrame == -1) {
        self->animCurFrame = (&chosenAnimArray[PLAYER.animFrameIdx])[-1];
    }

    f178_count = -1;
    if ((abs(PLAYER.velocityX) > FIX(2.5)) && (g_GameTimer % 6 == 0)) {
        f178_count = D_8013843C % 5;
        D_8013843C++;
    }
    f178_finish = false;
    if (abs(PLAYER.velocityX) > FIX(3)) {
        f178_finish = true;
        self->palette = PLAYER.palette = 0x810D;
    }
    prim = &g_PrimBuf[self->primIndex];
    func_8012F178(prim, f178_count, f178_finish);
    self->palette = PLAYER.palette;
}

static s16 D_800B0A5C[] = {0, 1, 0, -1, 0, 1, 0, -1};
static s16 D_800B0A6C[] = {0, 1, 2, 3, 4, 3, 2, 1};
static s16 D_800B0A7C[] = {0, 0, 1, 1, 2, 2, 3, 3};
void func_80130264(Entity* self) {
    s32 var_v1;

    if (!(g_Player.unk0C & PLAYER_STATUS_WOLF_FORM)) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        self->animSet = ANIMSET_DRA(15);
        self->animCurFrame = 1;
        self->unk5A = 0x7E;
        self->palette = PLAYER.palette;
#if defined(VERSION_HD)
        self->zPriority = PLAYER.zPriority;
#endif
        self->flags = FLAG_UNK_04000000 | FLAG_UNK_20000 | FLAG_UNK_40000;
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->rotPivotX = 0;
        self->rotPivotY = 9;
        LOH(self->hitboxOffX) = -4;
        self->hitboxOffY = 10;
        self->hitboxWidth = 20;
        self->hitboxHeight = 6;
        self->step++;
    }
#if !defined(VERSION_HD)
    self->zPriority = PLAYER.zPriority;
#endif
    self->facingLeft = PLAYER.facingLeft;
    self->posX.val = g_Entities->posX.val;
    self->posY.val = PLAYER.posY.val;
    self->rotZ = 0x800 - D_80138430;

    switch (PLAYER.step_s) {
    case 1:
        if (D_800B0914 == 1) {
            self->rotZ -= 0x180;
        }
        break;
    case 2:
        switch (D_800B0914) {
        case 0:
            if (PLAYER.animCurFrame == 33) {
                self->animCurFrame = 31;
            }
            if (PLAYER.animCurFrame == 34) {
                self->animCurFrame = 32;
            }
            break;
        case 1:
        case 3:
            var_v1 = D_800B0A5C[PLAYER.animFrameIdx];
            self->posY.i.hi += var_v1;
            self->rotZ -= var_v1 << 5;
            break;
        case 2:
            var_v1 = D_800B0A6C[PLAYER.animFrameIdx];
            self->posY.i.hi += var_v1;
            self->rotZ -= var_v1 << 5;
            break;
        case 4:
            var_v1 = D_800B0A7C[PLAYER.animFrameIdx];
            self->posY.i.hi += var_v1;
            break;
        }
        if (g_Player.pl_vram_flag & 0x8000) {
            self->posY.i.hi += 2;
        }
        break;
    case 3:
        if (PLAYER.animCurFrame == 18) {
            self->posY.i.hi += 4;
        }
        if (PLAYER.animCurFrame == 19) {
            self->posY.i.hi += 8;
        }
        if (PLAYER.animCurFrame == 20) {
            self->posY.i.hi += 8;
        }
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        break;
    }
    if (D_80138430 == 0xA00) {
        self->posY.i.hi += 2;
    }
    self->palette = PLAYER.palette;
    self->hitboxState = 0;
    if (abs(PLAYER.velocityX) > FIX(3) &&
        (PLAYER.step_s != 2 || D_800B0914 != 4)) {
        func_8011A328(self, 13);
        self->enemyId = 3;
        if (self->hitFlags && !CastSpell(13)) {
            D_800B0914 = 3;
            PLAYER.ext.player.anim = 0xE0;
            D_800B091C = 0x18;
        }
    }
    self->hitFlags = 0;
}

static s16 D_800B0A8C[] = {0, 1, 0, -1, 0, 1, 0, -1};
static s16 D_800B0A9C[] = {0, 1, 1, 0, 0, 1, 1, 0};
static s16 D_800B0AAC[] = {0, 0, 0, 1, 1, 1, 2, 2};
void func_80130618(Entity* self) {
    s32 var_v1;

    if (!(g_Player.unk0C & PLAYER_STATUS_WOLF_FORM)) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        self->animSet = 0xF;
        self->animCurFrame = 0x23;
        self->unk5A = 0x7E;
        self->palette = PLAYER.palette;
#if defined(VERSION_HD)
        self->zPriority = PLAYER.zPriority - 2;
#endif
        self->flags = FLAG_UNK_04000000 | FLAG_UNK_20000 | FLAG_UNK_40000;
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->rotPivotX = 1;
        self->rotPivotY = 8;
        self->step++;
    }
#if !defined(VERSION_HD)
    self->zPriority = PLAYER.zPriority - 2;
#endif
    self->facingLeft = PLAYER.facingLeft;
    self->posX.val = g_Entities[UNK_ENTITY_11].posX.val;
    self->posY.val = g_Entities[UNK_ENTITY_11].posY.val;
    self->rotZ = -((D_80138430 - 0x800) / 2);

    switch (PLAYER.step_s) {
    case 1:
        if (D_800B0914 == 1) {
            self->rotZ -= 0x100;
            self->posY.i.hi += 8;
        }
        if (D_80138430 < 0x601) {
            self->posY.i.hi += 2;
        }
        break;
    case 2:
        switch (D_800B0914) {
        case 0:
            if (PLAYER.animCurFrame == 33) {
                self->animCurFrame = 65;
            }
            if (PLAYER.animCurFrame == 34) {
                self->animCurFrame = 66;
            }
            break;
        case 1:
        case 3:
            var_v1 = D_800B0A8C[PLAYER.animFrameIdx];
            self->posY.i.hi += var_v1;
            break;
        case 2:
            var_v1 = D_800B0A9C[PLAYER.animFrameIdx];
            self->posY.i.hi += var_v1;
            break;
        case 4:
            var_v1 = D_800B0AAC[PLAYER.animFrameIdx];
            self->posY.i.hi += var_v1;
            break;
        }
        if (D_80138430 < 0x701) {
            self->posY.i.hi++;
        }
        if (D_80138430 < 0x601) {
            self->posY.i.hi += 2;
        }
        break;
    case 3:
        if (PLAYER.animCurFrame == 0x12) {
            self->posY.i.hi += 4;
        }
        if (PLAYER.animCurFrame == 0x13) {
            self->posY.i.hi += 8;
        }
        if (PLAYER.animCurFrame == 0x14) {
            self->posY.i.hi += 8;
        }
        if (D_80138430 <= 0x600) {
            self->posY.i.hi += 2;
        }
        break;
    case 4:
        if (D_800B0914 == 0) {
            self->posY.i.hi++;
            self->rotZ -= 0x180;
        }
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        break;
    }
    self->palette = PLAYER.palette;
    self->drawMode = DRAW_DEFAULT;
    self->drawFlags &= ~FLAG_DRAW_UNK8;
    if (abs(PLAYER.velocityX) > FIX(3)) {
        self->drawFlags |= FLAG_DRAW_UNK8;
        self->drawMode = FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK40;
        self->unk6C = ~MIN((abs(PLAYER.velocityX) - FIX(3)) >> 12, 160);
    }
}

static AnimationFrame D_800B0ABC[] = {
    {0x02, 0x48}, {0x04, 0x4B}, {0x10, 0x4C},
    {0x04, 0x4B}, {0x08, 0x48}, {-1, 0x00},
};
static s32 D_800B0AD4[] = {0, 1, 2, 1, 0, 0};
static s32 D_800B0AEC[] = {0, 1, 1, 2, 2, 1, 1, 0};
extern s32 D_80138448;

void func_801309B4(Entity* self) {
    s32 var_s2;
    s32 var_a1;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_v0;
    s32 var_v0_2;

    if (!(g_Player.unk0C & PLAYER_STATUS_WOLF_FORM)) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        self->animSet = ANIMSET_DRA(15);
        self->unk5A = 0x7E;
#if defined(VERSION_HD)
        self->zPriority = PLAYER.zPriority + 2;
#endif
        self->flags = FLAG_UNK_04000000 | FLAG_UNK_100000 | FLAG_UNK_20000 |
                      FLAG_UNK_40000;
        self->animFrameDuration = 1;
        self->animFrameIdx = 4;
        self->unk4C = D_800B0ABC;
        self->hitboxWidth = 10;
        self->hitboxHeight = 8;
        self->animCurFrame = 72;
        self->step++;
    }
#if !defined(VERSION_HD)
    self->zPriority = PLAYER.zPriority + 2;
#endif
    self->facingLeft = PLAYER.facingLeft;
    self->posX.val = g_Entities[UNK_ENTITY_12].posX.val;
    self->posY.val = g_Entities[UNK_ENTITY_12].posY.val + FIX(4);
    self->flags =
        FLAG_UNK_04000000 | FLAG_UNK_100000 | FLAG_UNK_20000 | FLAG_UNK_40000;

    var_a1 = D_80138430 - 0x800;
    if (D_80138430 > 0x980) {
        var_a1 = 0x180;
    }
    if (D_80138430 < 0x680) {
        var_a1 = -0x180;
    }
    self->palette = PLAYER.palette;
    var_s2 = 11;
    var_s0 = var_a1;
    switch (PLAYER.step_s) {
    case 1:
        var_s0 = var_a1;
        if (D_800B0914 == 1) {
            var_s0 += 0x100;
        }
        break;
    case 2:
        switch (D_800B0914) {
        case 0:
            if (PLAYER.animCurFrame == 33) {
                var_s0 = !PLAYER.facingLeft;
                self->posX.i.hi =
                    var_s0 ? self->posX.i.hi + 4 : self->posX.i.hi - 4;
                self->animCurFrame = 73;
                self->flags &= ~FLAG_UNK_100000;
                return;
            }
            if (PLAYER.animCurFrame == 34) {
                self->animCurFrame = 74;
                self->flags &= ~FLAG_UNK_100000;
                return;
            }
            break;
        case 1:
            break;
        case 2:
            var_s2 += D_800B0AEC[PLAYER.animFrameIdx];
            var_s0 -= 0x80;
            if (D_80138430 == 0xA00) {
                var_s0 += 0x80;
            }
            if (D_80138430 == 0x600) {
                var_s0 += 0x80;
            }
            break;
        }
        break;
    case 3:
        var_s0 -= 0x100;
        if (var_s0 < -0x180) {
            var_s0 = -0x180;
            break;
        }
        break;
    case 4:
        if (D_800B0914 == 2) {
            var_s0 -= 0x40;
        }
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        break;
    }

    var_s2 = var_s2 - (var_s0 >> 7);
    if (PLAYER.facingLeft) {
        var_s0 = 0x800 - var_s0;
    }
    self->posX.i.hi += ((rcos(var_s0) >> 4) * var_s2) >> 8;
    self->posY.i.hi -= ((rsin(var_s0) >> 4) * var_s2) >> 8;
    if (PLAYER.step_s != 8 && PLAYER.step_s != 0 && D_80138444 != 0 &&
        self->animFrameDuration == -1) {
        PlaySfx(SFX_UNK_6F7);
        self->animFrameDuration = 0;
        self->animFrameIdx = 0;
    }
    var_s2 = D_800B0AD4[self->animFrameIdx];
    if (PLAYER.facingLeft) {
        var_s2 = -var_s2;
    }
    self->posX.i.hi += var_s2;
    if (PLAYER.step_s == 2 && D_800B0914 == 4) {
        func_8011A328(self, 4);
        self->enemyId = 3;
    } else if (self->animCurFrame != 72 && self->animCurFrame != 73 &&
               self->animCurFrame != 74) {
        func_8011A328(self, 14);
        self->enemyId = 3;
    } else {
        self->hitboxState = 0;
    }
    if (self->animFrameDuration < 0) {
        if (D_80138448 != 0) {
            D_80138448 -= 1;
        } else if (*D_80097448 >= 0x19) {
            var_s0_2 = PLAYER.facingLeft ? -4 : 4;
            self->posX.i.hi = var_s0_2 + self->posX.i.hi;
            self->posY.i.hi += 2;
            CreateEntFactoryFromEntity(self, FACTORY(0xD00, 4), 0);
            D_80138448 = 0x40;
            self->posY.i.hi -= 2;
            self->posX.i.hi -= var_s0_2;
        }
    }
}

static s16 D_800B0B0C[] = {87, 88, 89, 89, 90, 90, 89, 88, 87};
static s16 D_800B0B20[] = {
    0x0, 0x040, 0x080, 0x0C0, 0x100, 0x140, 0x180, 0x1C0, 0x200};
extern s32 D_8013844C;
extern s32 D_80138450;

void func_80130E94(Entity* self) {
    s32 temp_v1;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    u16 params;
    s32 var_s6;
    s32 var_s7;

    if (!(g_Player.unk0C & PLAYER_STATUS_WOLF_FORM)) {
        DestroyEntity(self);
        return;
    }
    params = self->params;
    var_s1 = 0;
    var_s2 = 0;
    if (self->step == 0) {
        self->animSet = 15;
        self->animCurFrame = D_800B0B0C[params];
        self->unk5A = 0x7E;
        D_8013844C = 0;
        self->palette = PLAYER.palette;
#if defined(VERSION_HD)
        self->zPriority = PLAYER.zPriority - 3;
#endif
        self->flags = FLAG_UNK_04000000 | FLAG_UNK_20000 | FLAG_UNK_40000;
        self->ext.timer.t = 0x20;
        self->rotZ = D_80138430;
        self->step++;
    }
    self->facingLeft = PLAYER.facingLeft;
#if !defined(VERSION_HD)
    self->zPriority = PLAYER.zPriority - 3;
#endif
    var_s6 = 2;
    if (params == 0) {
        var_s4 = g_Entities[19].posX.val;
        var_s4 += PLAYER.facingLeft ? FIX(3) : -FIX(3);
        var_s7 = g_Entities[19].posY.val + FIX(7);
    } else {
        var_s4 = self[-1].posX.val;
        var_s7 = self[-1].posY.val;
    }
    if (PLAYER.animCurFrame == 33) {
        var_s6 = 1;
    }
    if (PLAYER.animCurFrame == 34) {
        var_s6 = 0;
    }
    if (params == 0) {
        var_s3 = D_8013844C;
        switch (PLAYER.step_s) {
        case 1:
            var_s2 = 0x100;
            var_s1 = 0x80;
            D_8013844C += 0x18;
            if (D_800B0914 == 1) {
                var_s1 = -0x80;
            }
            break;
        case 2:
            switch (D_800B0914) {
            case 0:
                var_s1 = -0x300;
                break;
            case 1:
            case 3:
                var_s2 = 0x40;
                var_s1 = -0x200;
                D_8013844C += 0x100;
                break;
            case 2:
                var_s2 = 0x40;
                D_8013844C += 0x100;
                var_s1 =
                    MIN((abs(PLAYER.velocityX) + -FIX(3)) >> 10, 0x100) - 0x100;
                break;
            }
            break;
        case 3:
            var_s2 = 0x40;
            var_s1 = 0x80;
            D_8013844C += 0x10;
            break;
        case 4:
            if (D_800B0914 == 0) {
                var_s1 = -0x200;
                if (PLAYER.velocityY < 0) {
                    var_s1 = 0x600;
                }
            } else {
                var_s2 = 0x20;
                var_s1 = -0x100;
                if (PLAYER.velocityY < 0) {
                    var_s1 = 0x100;
                }
            }
            break;
        case 7:
            var_s1 = -0x80;
            break;
        case 5:
        case 6:
        case 8:
            var_s1 = -0x200;
            break;
        case 9:
            var_s2 = 0x100;
            var_s1 = 0x80;
            D_8013844C += 0x18;
            break;
        }
        D_80138450 =
            var_s1 + D_80138430 + (((rsin(var_s3) >> 8) * var_s2) >> 4);
    }
    temp_v1 = (D_80138450 - D_80138430) * D_800B0B20[params] / 256 + D_80138430;
    if (temp_v1 < self->rotZ) {
        self->rotZ -= self->ext.timer.t;
    }
    if (self->rotZ < temp_v1) {
        self->rotZ += self->ext.timer.t;
    }
    if (PLAYER.facingLeft == 0) {
        var_s3 = self->rotZ;
    } else {
        var_s3 = 0x800 - self->rotZ;
    }
    self->posX.val = var_s4 + rcos(var_s3) * var_s6 * 0x10;
    self->posY.val = var_s7 - rsin(var_s3) * var_s6 * 0x10;
    self->palette = PLAYER.palette;
    self->drawMode = 0;
    self->drawFlags &= ~FLAG_DRAW_UNK8;
    if (abs(PLAYER.velocityX) > FIX(3)) {
        self->drawFlags |= FLAG_DRAW_UNK8;
        self->drawMode = FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK40;
        self->unk6C = ~MIN((abs(PLAYER.velocityX) - FIX(3)) >> 12, 128);
    }
}
// Entity #60. This is created manually at g_Entities[30].
// Creation is in func_8012E7A4.
void func_8013136C(Entity* self) {
    if (!(g_Player.unk0C & PLAYER_STATUS_WOLF_FORM)) {
        DestroyEntity(self);
        return;
    }
    if (!self->step) {
        self->animSet = 0xF;
        self->unk5A = 0x7E;
        self->palette = PLAYER.palette;
        self->flags = FLAG_UNK_04000000 | FLAG_UNK_20000 | FLAG_UNK_40000;
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->rotPivotX = -8;
        self->step++;
    }
    self->animCurFrame = 80;
    self->facingLeft = PLAYER.facingLeft;
    self->posX.val = g_Entities[UNK_ENTITY_13].posX.val;
    self->posY.val = g_Entities[UNK_ENTITY_13].posY.val;
    if (!PLAYER.facingLeft) {
        self->zPriority = PLAYER.zPriority - 5;
        self->posX.i.hi += 8;
    } else {
        self->zPriority = PLAYER.zPriority + 5;
        self->posX.i.hi -= 8;
    }
    self->posY.i.hi += 3;
    self->rotZ = g_Entities[UNK_ENTITY_12].rotZ;
    switch (PLAYER.step_s) {
    case 1:
        if (D_800B0914 == 1) {
            self->posY.i.hi -= 2;
            if (!PLAYER.facingLeft) {
                self->posX.i.hi -= 8;
            } else {
                self->posX.i.hi += 8;
            }
        }
        break;
    case 2:
        switch (D_800B0914) {
        case 0:
            if (PLAYER.animCurFrame == 33) {
                self->animCurFrame = 81;
                if (!PLAYER.facingLeft) {
                    self->posX.i.hi += 3;
                } else {
                    self->posX.i.hi += 6;
                }
            }
            if (PLAYER.animCurFrame == 34) {
                if (!PLAYER.facingLeft) {
                    self->posX.i.hi += 3;
                } else {
                    self->posX.i.hi += 13;
                }
                self->animCurFrame = 82;
            }
            break;
        case 1:
            break;
        case 3:
        case 2:
        default:
            break;
        }
        break;
    case 3:
        break;
    case 4:
        D_800B0914 == 0;
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        break;
    }
    self->palette = PLAYER.palette;
    func_8012C600();
}

static SVECTOR D_800B0B34 = {-8, -72, -4};
static SVECTOR D_800B0B3C = {8, -72, -4};
static SVECTOR D_800B0B44 = {-48, -32, -4};
static SVECTOR D_800B0B4C = {-8, -32, -4};
static SVECTOR D_800B0B54 = {8, -32, -4};
static SVECTOR D_800B0B5C = {48, -32, -4};
static SVECTOR D_800B0B64 = {-48, -16, -4};
static SVECTOR D_800B0B6C = {-8, -16, -4};
static SVECTOR D_800B0B74 = {8, -16, -4};
static SVECTOR D_800B0B7C = {48, -16, -4};
static SVECTOR D_800B0B84 = {-8, 72, -4};
static SVECTOR D_800B0B8C = {8, 72, -4};
static SVECTOR D_800B0B94 = {-24, -48, -4}; // unused
static SVECTOR D_800B0B9C = {-8, -48, -4};
static SVECTOR D_800B0BA4 = {8, -48, -4};
static SVECTOR D_800B0BAC = {24, -48, -4}; // unused
static SVECTOR D_800B0BB4 = {-24, -32, -4};
static SVECTOR D_800B0BBC = {24, -32, -4};
static SVECTOR D_800B0BC4 = {-24, -16, -4};
static SVECTOR D_800B0BCC = {24, -16, -4};
static SVECTOR D_800B0BD4 = {-24, 0, -4}; // unused
static SVECTOR D_800B0BDC = {-8, 0, -4};
static SVECTOR D_800B0BE4 = {8, 0, -4};
static SVECTOR D_800B0BEC = {24, 0, -4}; // unused
static SVECTOR D_800B0BF4 = {-8, -72, 4};
static SVECTOR D_800B0BFC = {8, -72, 4};
static SVECTOR D_800B0C04 = {-48, -32, 4};
static SVECTOR D_800B0C0C = {-8, -32, 4};
static SVECTOR D_800B0C14 = {8, -32, 4};
static SVECTOR D_800B0C1C = {48, -32, 4};
static SVECTOR D_800B0C24 = {-48, -16, 4};
static SVECTOR D_800B0C2C = {-8, -16, 4};
static SVECTOR D_800B0C34 = {8, -16, 4};
static SVECTOR D_800B0C3C = {48, -16, 4};
static SVECTOR D_800B0C44 = {-8, 72, 4};
static SVECTOR D_800B0C4C = {8, 72, 4};
static SVECTOR D_800B0C54 = {-24, -48, 4};
static SVECTOR D_800B0C5C = {-8, -48, 4};
static SVECTOR D_800B0C64 = {8, -48, 4};
static SVECTOR D_800B0C6C = {24, -48, 4};
static SVECTOR D_800B0C74 = {-24, -32, 4};
static SVECTOR D_800B0C7C = {24, -32, 4};
static SVECTOR D_800B0C84 = {-24, -16, 4};
static SVECTOR D_800B0C8C = {24, -16, 4};
static SVECTOR D_800B0C94 = {-24, 0, 4};
static SVECTOR D_800B0C9C = {-8, 0, 4};
static SVECTOR D_800B0CA4 = {8, 0, 4};
static SVECTOR D_800B0CAC = {24, 0, 4};
static SVECTOR* D_800B0CB4[][4] = {
    {&D_800B0B4C, &D_800B0B54, &D_800B0B74, &D_800B0B6C},
    {&D_800B0C54, &D_800B0C5C, &D_800B0C0C, &D_800B0C74},
    {&D_800B0C64, &D_800B0C6C, &D_800B0C7C, &D_800B0C14},
    {&D_800B0C84, &D_800B0C2C, &D_800B0C9C, &D_800B0C94},
    {&D_800B0C34, &D_800B0C8C, &D_800B0CAC, &D_800B0CA4},
    {&D_800B0C0C, &D_800B0C5C, &D_800B0C54, &D_800B0C74},
    {&D_800B0C7C, &D_800B0C6C, &D_800B0C64, &D_800B0C14},
    {&D_800B0C9C, &D_800B0C2C, &D_800B0C84, &D_800B0C94},
    {&D_800B0CAC, &D_800B0C8C, &D_800B0C34, &D_800B0CA4},
    {&D_800B0C14, &D_800B0C64, &D_800B0C5C, &D_800B0C0C},
    {&D_800B0C2C, &D_800B0C0C, &D_800B0C74, &D_800B0C84},
    {&D_800B0C8C, &D_800B0C7C, &D_800B0C14, &D_800B0C34},
    {&D_800B0CA4, &D_800B0C34, &D_800B0C2C, &D_800B0C9C},
    {&D_800B0C34, &D_800B0C14, &D_800B0C0C, &D_800B0C2C},
    {&D_800B0B3C, &D_800B0BFC, &D_800B0C64, &D_800B0BA4},
    {&D_800B0BA4, &D_800B0C64, &D_800B0C14, &D_800B0B54},
    {&D_800B0B74, &D_800B0C34, &D_800B0CA4, &D_800B0BE4},
    {&D_800B0BE4, &D_800B0CA4, &D_800B0C4C, &D_800B0B8C},
    {&D_800B0C74, &D_800B0C0C, &D_800B0B4C, &D_800B0BB4},
    {&D_800B0C14, &D_800B0C7C, &D_800B0BBC, &D_800B0B54},
    {&D_800B0C64, &D_800B0BFC, &D_800B0BF4, &D_800B0C5C},
    {&D_800B0C84, &D_800B0C74, &D_800B0C04, &D_800B0C24},
    {&D_800B0C3C, &D_800B0C1C, &D_800B0C7C, &D_800B0C8C},
    {&D_800B0C4C, &D_800B0CA4, &D_800B0C9C, &D_800B0C44},
    {&D_800B0C5C, &D_800B0BF4, &D_800B0B34, &D_800B0B9C},
    {&D_800B0C0C, &D_800B0C5C, &D_800B0B9C, &D_800B0B4C},
    {&D_800B0C9C, &D_800B0C2C, &D_800B0B6C, &D_800B0BDC},
    {&D_800B0C44, &D_800B0C9C, &D_800B0BDC, &D_800B0B84},
    {&D_800B0B6C, &D_800B0C2C, &D_800B0C84, &D_800B0BC4},
    {&D_800B0BCC, &D_800B0C8C, &D_800B0C34, &D_800B0B74},
    {&D_800B0B6C, &D_800B0B74, &D_800B0BE4, &D_800B0BDC},
    {&D_800B0BDC, &D_800B0BE4, &D_800B0B8C, &D_800B0B84},
    {&D_800B0B34, &D_800B0B3C, &D_800B0BA4, &D_800B0B9C},
    {&D_800B0B9C, &D_800B0BA4, &D_800B0B54, &D_800B0B4C},
    {&D_800B0B5C, &D_800B0C1C, &D_800B0C3C, &D_800B0B7C},
    {&D_800B0BF4, &D_800B0BFC, &D_800B0B3C, &D_800B0B34},
    {&D_800B0C24, &D_800B0C04, &D_800B0B44, &D_800B0B64},
    {&D_800B0B8C, &D_800B0C4C, &D_800B0C44, &D_800B0B84},
    {&D_800B0C04, &D_800B0C74, &D_800B0BB4, &D_800B0B44},
    {&D_800B0BC4, &D_800B0C84, &D_800B0C24, &D_800B0B64},
    {&D_800B0C7C, &D_800B0C1C, &D_800B0B5C, &D_800B0BBC},
    {&D_800B0B7C, &D_800B0C3C, &D_800B0C8C, &D_800B0BCC},
    {&D_800B0BB4, &D_800B0B4C, &D_800B0B6C, &D_800B0BC4},
    {&D_800B0B54, &D_800B0BBC, &D_800B0BCC, &D_800B0B74},
    {&D_800B0B44, &D_800B0BB4, &D_800B0BC4, &D_800B0B64},
    {&D_800B0BBC, &D_800B0B5C, &D_800B0B7C, &D_800B0BCC},
};
static u8 D_800B0F94[][5] = {
    {0x38, 0x08, 0x10, 0x10, 0x0D}, {0x58, 0x08, 0x10, 0x10, 0x0E},
    {0x58, 0x08, 0x10, 0x10, 0x1E}, {0x58, 0x08, 0x10, 0x10, 0x2E},
    {0x58, 0x08, 0x10, 0x10, 0x3E}, {0x58, 0x08, 0x10, 0x10, 0x4E},
    {0x58, 0x08, 0x10, 0x10, 0x5E}, {0x58, 0x08, 0x10, 0x10, 0x6E},
    {0x58, 0x08, 0x10, 0x10, 0x7E}, {0x68, 0x08, 0x10, 0x10, 0x4E},
    {0x68, 0x08, 0x10, 0x10, 0x2E}, {0x68, 0x08, 0x10, 0x10, 0x0E},
    {0x68, 0x08, 0x10, 0x10, 0x6E}, {0x68, 0x18, 0x10, 0x10, 0x4E},
    {0x68, 0x30, 0x10, 0x10, 0x0E}, {0x68, 0x30, 0x10, 0x10, 0x0E},
    {0x68, 0x30, 0x10, 0x10, 0x0E}, {0x68, 0x30, 0x10, 0x10, 0x0E},
    {0x68, 0x30, 0x10, 0x10, 0x0E}, {0x68, 0x30, 0x10, 0x10, 0x0E},
    {0x68, 0x30, 0x10, 0x10, 0x4E}, {0x68, 0x30, 0x10, 0x10, 0x4E},
    {0x68, 0x30, 0x10, 0x10, 0x4E}, {0x68, 0x30, 0x10, 0x10, 0x4E},
    {0x68, 0x30, 0x10, 0x10, 0x4E}, {0x68, 0x30, 0x10, 0x10, 0x4E},
    {0x68, 0x30, 0x10, 0x10, 0x4E}, {0x68, 0x30, 0x10, 0x10, 0x4E},
    {0x68, 0x30, 0x10, 0x10, 0x4E}, {0x68, 0x30, 0x10, 0x10, 0x4E},
    {0x38, 0x18, 0x10, 0x10, 0x0F}, {0x38, 0x28, 0x10, 0x48, 0x0F},
    {0x50, 0x20, 0x10, 0x18, 0x0F}, {0x50, 0x38, 0x10, 0x10, 0x0F},
    {0x70, 0x48, 0x08, 0x08, 0x0F}, {0x70, 0x48, 0x08, 0x08, 0x0F},
    {0x70, 0x48, 0x08, 0x08, 0x4F}, {0x70, 0x48, 0x08, 0x08, 0x4F},
    {0x50, 0x50, 0x18, 0x08, 0x0F}, {0x50, 0x50, 0x18, 0x08, 0x4F},
    {0x50, 0x50, 0x18, 0x08, 0x1F}, {0x50, 0x50, 0x18, 0x08, 0x5F},
    {0x68, 0x58, 0x10, 0x10, 0x0F}, {0x68, 0x58, 0x10, 0x10, 0x1F},
    {0x50, 0x58, 0x18, 0x10, 0x0F}, {0x50, 0x58, 0x18, 0x10, 0x1F},
};

#ifdef VERSION_US
static u8 dirty_data1 = 0x20;
static u8 dirty_data2 = 0x0D;
#endif

// When Alucard uses the cross subweapon for 100 hearts.
// Entity ID 7, blueprint #7 (this is a coincidence)
void EntityGiantSpinningCross(Entity* self) {
    static const SVECTOR D_800E2024 = {0, 0, 0};
    static const SVECTOR D_800E202C = {0xFFA0, 0, 0};
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
        self->primIndex = g_api.func_800EDB58(PRIM_GT4, LEN(D_800B0CB4));
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->tpage = 0x1C;
            prim->drawMode = 0x100 | DRAW_HIDE;
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
        PlaySfx(SFX_UNK_661);
        self->step++;
        primUVCoords = &D_800B0F94[0][0];
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < LEN(D_800B0CB4); i++, prim = prim->next,
            primUVCoords += 5) {
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
    for (i = 0; i < LEN(D_800B0CB4); i++, prim = prim->next, vectors_ptr += 4) {
        gte_ldv3(vectors_ptr[0], vectors_ptr[1], vectors_ptr[3]);
        gte_rtpt();
        temp_a3 = vectors_ptr[2];
        prim->type = 4;
        gte_nclip();
        prim->drawMode = DRAW_HIDE;
        gte_stopz(&nclip);
        if (nclip < 0) {
            continue;
        }
        gte_stsxy3(&prim->x0, &prim->x1, &prim->x2);
        gte_ldv0(temp_a3);
        gte_rtps();
        prim->drawMode = DRAW_DEFAULT;
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
