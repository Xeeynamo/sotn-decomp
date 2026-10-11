// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

extern PlayerState g_Dop;

static u8 D_us_801813A4[][2] = {
    {0, 17},
    {4, 21},
    {1, 16},
    {3, 35},
};

void func_8010E470(s32 arg0, s32 velocityX) {
    s32 unused_stack[2];

    DOPPLEGANGER.velocityX = velocityX;
    DOPPLEGANGER.velocityY = 0;
    DOPPLEGANGER.step = Dop_Crouch;
    DOPPLEGANGER.step_s = D_us_801813A4[arg0][0];
    SetDopplegangerAnim(D_us_801813A4[arg0][1]);
}

static u8 D_us_801813AC[] = {
    0x04, 0x05, 0x0A, 0x0B, 0x0E, 0x0F, 0x1D, 0x1E, 0x04, 0x03, 0x00, 0x00,
};

void func_8010E570(s32 arg0) {
    s32 anim = 0;
    bool atLedge = false;

    if (g_Dop.vram_flag & IN_AIR_OR_EDGE) {
        atLedge = true;
    }

    DOPPLEGANGER.velocityX = arg0;
    DOPPLEGANGER.velocityY = 0;
    SetDopplegangerStep(Dop_Stand);
    if (g_Dop.unk48) {
        DOPPLEGANGER.step_s = 2;
        atLedge = false;
    }

    switch (g_Dop.prev_step) {
    case Dop_UnmorphBat:
        anim = 4;
        break;
    case Dop_Walk:
        anim = 4;
        if (DOPPLEGANGER.ext.player.anim == 9) {
            DOPPLEGANGER.ext.player.anim = D_us_801813AC[2 + atLedge];
            return;
        }
        if (DOPPLEGANGER.ext.player.anim == 7) {
            anim = 0;
        }
        break;
    case Dop_Jump:
    case Dop_Fall:
        anim = 6;
        if (abs(DOPPLEGANGER.velocityX) > FIX(2.5)) {
            anim = 4;
        }
        break;
    default:
        anim = 8;
        break;
    }
    anim += atLedge;
    SetDopplegangerAnim(D_us_801813AC[anim]);
}

void func_8010E6AC(bool forceAnim13) {
    bool atLedge;

    atLedge = 0;
    if (g_Dop.vram_flag & IN_AIR_OR_EDGE) {
        atLedge = 1;
    }

    SetSpeedX(FIX(1.5));
    DOPPLEGANGER.velocityY = 0;
    SetDopplegangerStep(Dop_Walk);

    if (forceAnim13) {
        if (DOPPLEGANGER.ext.player.anim != 13) {
            SetDopplegangerAnim(13);
        }
    } else {
        SetDopplegangerAnim(7);
        // Factory blueprint 1 has child 2, which is EntitySmokePuff
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_1, 5), 0);
    }

    if (g_Dop.unk4C) {
        DOPPLEGANGER.ext.player.anim = 9;
    }

    if (DOPPLEGANGER.ext.player.anim == 7 && atLedge) {
        DOPPLEGANGER.pose = 1;
    }

    if (g_Dop.prev_step == Dop_Crouch) {
        DOPPLEGANGER.pose = 4;
    }
}

void func_us_801C4EE4(void) {
    if (CheckMoveDirection() != 0) {
        SetDopplegangerAnim(0x1A);
        SetSpeedX(FIX(3.0 / 2.0));
        g_Dop.unk44 = 0;
    } else {
        SetDopplegangerAnim(0x16);
        DOPPLEGANGER.velocityX = 0;
        g_Dop.unk44 = 4;
    }
    DOPPLEGANGER.velocityY = FIX(-4.875);
    SetDopplegangerStep(5);
    if (g_Dop.prev_step == 2) {
        g_Dop.unk44 |= 0x10;
    }
}

void func_us_801C4F90(void) {
    DOPPLEGANGER.velocityY = FIX(-4.25);
    g_Dop.unk44 |= 0x21;
    SetDopplegangerAnim(0x20);
    DOPPLEGANGER.step_s = 0;
}

void func_us_801C4FDC(void) {
    SetDopplegangerStep(4);
    if (g_Dop.prev_step != 2) {
        SetDopplegangerAnim(0x1C);
    }
    DOPPLEGANGER.velocityY = FIX(2.0);
    g_Dop.timers[ALU_T_5] = 8;
    g_Dop.timers[ALU_T_6] = 8;
    DOPPLEGANGER.velocityX = 0;
    g_Dop.unk44 = 0x10;
}

void func_us_801C504C(void) {
    if (CheckMoveDirection() != 0) {
        SetSpeedX(FIX(3));
    } else {
        DOPPLEGANGER.velocityX = 0;
    }
    SetDopplegangerStep(9);
    DOPPLEGANGER.velocityY = FIX(-12);
    SetDopplegangerAnim(0x21);
    g_Dop.gravBootTimer = 0;
    g_Dop.unk44 &= ~1;
    CreateEntFactoryFromEntity(
        g_CurrentEntity, FACTORY(BP_GRAVITY_BOOT_BEAM, 0), 0);
}

static s16 D_us_801813B8[] = {
    SFX_VO_DOP_ATTACK_A,
    SFX_VO_DOP_ATTACK_B,
    SFX_VO_DOP_ATTACK_C,
    SFX_VO_DOP_ATTACK_D,
};

void func_8010EA54(s32 arg0) {
    s16 temp_hi;

    if (arg0 != 0) {
        temp_hi = rand() % arg0;
        if (temp_hi < 4) {
            g_api.PlaySfx(D_us_801813B8[temp_hi]);
        }
    }
}

s32 func_us_801C5168(void) {
    Entity* entity;
    s32 i;
    s32 entityCount;
    s32 targetCount;
    s32 animBase;
    s32 playerAnimOffset;
    s32 animOffset;

    playerAnimOffset = 0;
    if (!(g_Dop.padPressed & PAD_UP)) {
        return 1;
    }
    if (g_Dop.vram_flag & IN_AIR_OR_EDGE) {
        playerAnimOffset = 1;
    }

    targetCount = 3;
    for (entity = &g_Entities[E_ID_60], i = 0, entityCount = 0; i < 16; i++,
        entity++) {
        if (entity->entityId == E_EXPLOSION_VARIANTS) {
            entityCount++;
        }
        if (entityCount >= targetCount) {
            return -1;
        }
    }

    CreateEntFactoryFromEntity(
        g_CurrentEntity, FACTORY(BP_REBOUND_STONE, 0), 0);

    g_Dop.timers[10] = 4;
    if (DOPPLEGANGER.step_s >= 0x40) {
        return 0;
    }

    animBase = 0x5D;
    switch (DOPPLEGANGER.step) {
    case Dop_Stand:
        animOffset = playerAnimOffset;
        SetDopplegangerAnim(animBase + animOffset);
        break;
    case Dop_Crouch:
        animOffset = 2;
        if (DOPPLEGANGER.step_s == 2) {
            animOffset = playerAnimOffset;
            SetDopplegangerStep(1);
        }
        SetDopplegangerAnim(animBase + animOffset);
        break;
    }
    return 0;
}

void func_8010ED54(u8 anim) {
    DOPPLEGANGER.velocityX = DOPPLEGANGER.velocityY = 0;
    SetDopplegangerStep(16);
    SetDopplegangerAnim(anim);
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_61, 20), 0);
    g_Dop.unk48 = 0;
}

s32 func_us_801C52F8(void) {
    s32 defaultAnimOffset;
    s32 deltaX;
    s16 animOffset;
    s16 animBase;

    defaultAnimOffset = 0;
    if (g_Dop.vram_flag & IN_AIR_OR_EDGE) {
        defaultAnimOffset = 1;
    }

    animBase = func_us_801C5168();

    if (!animBase) {
        return 1;
    }

    if (animBase < 0) {
        return 0;
    }

    if (g_Dop.unk46 & 0x8000) {
        return 0;
    }

    if (g_Dop.timers[1]) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_57, 1), 0);

        switch (DOPPLEGANGER.step) {
        case Dop_Stand:
        case Dop_Walk:
            SetDopplegangerAnim(0xB5);
            DOPPLEGANGER.step = Dop_Stand;
            break;
        case Dop_Crouch:
            SetDopplegangerAnim(0xB6);
            DOPPLEGANGER.step = Dop_Crouch;
            break;
        case Dop_Fall:
        case Dop_Jump:
            SetDopplegangerAnim(0xB7);
            DOPPLEGANGER.step = Dop_Jump;
            break;
        }
        g_Dop.unk46 = 0x8012;
        g_Dop.unk54 = 0xFF;
        DOPPLEGANGER.step_s = 0x51;
        g_api.PlaySfx(SFX_VO_DOP_PAIN_A);
        return 1;
    }

    deltaX = abs(DOPPLEGANGER.posX.i.hi - PLAYER.posX.i.hi);

    if (deltaX > 36) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_48, 0), 0);
        DOPPLEGANGER.step_s = 0x41;
        g_Dop.unk46 = 0x8002;
        g_Dop.unk54 = 0xD;
        animBase = 0x41;
    } else {
        g_Dop.unk46 = 0x8003;
        DOPPLEGANGER.step_s = 0x42;
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_48, 1), 0);
        g_Dop.unk54 = 8;
        animBase = 0xA7;
    }

    switch (DOPPLEGANGER.step) {
    case Dop_Stand:
    case Dop_Walk:
        g_CurrentEntity->velocityX = g_CurrentEntity->velocityX >> 1;
        DOPPLEGANGER.step = Dop_Stand;
        animOffset = defaultAnimOffset;
        break;
    case 3:
        animOffset = 2;
        if (g_Dop.padPressed & (PAD_RIGHT | PAD_LEFT)) {
            animOffset++;
        }
        if (DOPPLEGANGER.step_s == 2) {
            animOffset = defaultAnimOffset;
            DOPPLEGANGER.step = Dop_Stand;
        }
        break;
    case 4:
    case 5:
        animOffset = 4;
        if (DOPPLEGANGER.velocityY > 0) {
            animOffset++;
            if (g_Dop.padPressed & PAD_DOWN) {
                animOffset++;
            }
        }
        break;
    }

    SetDopplegangerAnim(animBase + animOffset);
    g_Dop.timers[9] = 4;

    return 1;
}

void func_8010FAF4(void) {
    Entity* ent = &g_Entities[E_ID_50];
    DestroyEntity(ent);
    g_Dop.unk46 = 0;
}

void func_us_801C55EC(void) {
    DOPPLEGANGER.step = Dop_Stand;
    DOPPLEGANGER.step_s = 3;
    SetSpeedX(FIX(-3.5));
    g_CurrentEntity->velocityY = FIX(0.0);
    SetDopplegangerAnim(0xDB);
    CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
}
