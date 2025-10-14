// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

extern PlayerState g_Dop;

// n.b.! this file is the same as rbo5/unk_44954.c

// may be equivalent func_8010DFF0 in DRA
void func_us_801C5354(s32 resetAnims, s32 arg1) {
    Primitive* prim;

    if (resetAnims) {
        g_Entities[E_ID_41].ext.disableAfterImage.unk7D = 1;
        g_Entities[E_ID_41].animCurFrame = g_Entities[E_ID_42].animCurFrame =
            g_Entities[E_ID_43].animCurFrame = 0;
        prim = &g_PrimBuf[g_Entities[E_AFTERIMAGE_1].primIndex];
        while (prim != NULL) {
            prim->x1 = 0;
            prim = prim->next;
        }
    }
    g_Entities[E_ID_41].ext.disableAfterImage.unk7C = 1;
    g_Entities[E_ID_41].ext.disableAfterImage.unk7E = 0xA;
    if (arg1 != 0) {
        if (arg1 < 4) {
            g_Dop.timers[ALU_T_15] = 4;
        } else {
            g_Dop.timers[ALU_T_15] = arg1;
        }
    }
}

#ifndef VERSION_PC
static void ResetAfterImageIndex(void) UNUSED {
    g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].ext.afterImage.index = 0;
}
#endif

void OVL_EXPORT(EnableAfterImage)(void) {
    g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].ext.afterImage.resetFlag =
        0;
    g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].ext.afterImage.disableFlag =
        0;
}

// similar to DRA's func_8010E168. share's the function signature but
// not the entity creation logic, a0 is ignored
void OVL_EXPORT(func_us_801C5430)(s16 a0, s16 minTime) {
    if (g_Dop.timers[ALU_T_INVINCIBLE_CONSUMABLES] <= minTime) {
        g_Dop.timers[ALU_T_INVINCIBLE_CONSUMABLES] = minTime;
    }
}

#ifndef VERSION_PC
#include "../../decelerate.h"
#endif

s32 OVL_EXPORT(CheckMoveDirection)(void) {
    if (g_Dop.unk44 & 2) {
        return 0;
    }
    if (DOPPLEGANGER.facingLeft == true) {
        if (g_Dop.padPressed & PAD_RIGHT) {
            DOPPLEGANGER.facingLeft = 0;
            g_Dop.unk4C = 1;
            return -1;
        }
        if (g_Dop.padPressed & PAD_LEFT) {
            return 1;
        }
    } else {
        if (g_Dop.padPressed & PAD_RIGHT) {
            return 1;
        }
        if (g_Dop.padPressed & PAD_LEFT) {
            DOPPLEGANGER.facingLeft = 1;
            g_Dop.unk4C = 1;
            return -1;
        }
    }
    return 0;
}

s32 func_us_801C55A8(s32 minX, s32 maxX) {
    if (DOPPLEGANGER.step == Dop_Stand &&
        DOPPLEGANGER.step == DOPPLEGANGER.step_s) {
        if (DOPPLEGANGER.posX.i.hi >= minX) {
            if (maxX >= DOPPLEGANGER.posX.i.hi) {
                return true;
            }
        }
    }
    return false;
}

#ifndef VERSION_PC
#include "../../set_speed_x.h"
#endif

void DopSetVelocity(s32 velocityX) {
    if (DOPPLEGANGER.entityRoomIndex == 1) {
        velocityX = -velocityX;
    }
    DOPPLEGANGER.velocityX = velocityX;
}

static u8 D_us_80181318[][2] = {
    {0x00, 0x11},
    {0x04, 0x15},
    {0x01, 0x10},
    {0x03, 0x23},
};

void OVL_EXPORT(func_8010E470)(s32 arg0, s32 velocityX) {
    s32 unused_stack[2];

    DOPPLEGANGER.velocityX = velocityX;
    DOPPLEGANGER.velocityY = 0;
    DOPPLEGANGER.step = Dop_Crouch;
    DOPPLEGANGER.step_s = D_us_80181318[arg0][0];
    SetDopplegangerAnim(D_us_80181318[arg0][1]);
}

static u8 D_us_80181320[] = {
    0x04, 0x05, 0x0A, 0x0B, 0x0E, 0x0F, 0x1D, 0x1E, 0x04, 0x03, 0x00, 0x00,
};

void OVL_EXPORT(func_8010E570)(s32 arg0) {
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
            DOPPLEGANGER.ext.player.anim = D_us_80181320[2 + atLedge];
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
    SetDopplegangerAnim(D_us_80181320[anim]);
}

void OVL_EXPORT(func_8010E6AC)(bool forceAnim13) {
    bool atLedge;

    atLedge = false;
    if (g_Dop.vram_flag & IN_AIR_OR_EDGE) {
        atLedge = true;
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
        OVL_EXPORT(CreateEntFactoryFromEntity)
        (g_CurrentEntity, FACTORY(1, 5), 0);
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

void func_us_801C58E4(void) {
    if (OVL_EXPORT(CheckMoveDirection)() != 0) {
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

void func_us_801C5990(void) {
    DOPPLEGANGER.velocityY = FIX(-4.25);
    g_Dop.unk44 |= 0x21;
    SetDopplegangerAnim(0x20);
    DOPPLEGANGER.step_s = 0;
}

void func_us_801C59DC(void) {
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

void func_us_801C5A4C(void) {
    if (OVL_EXPORT(CheckMoveDirection)() != 0) {
        SetSpeedX(0x30000);
    } else {
        DOPPLEGANGER.velocityX = 0;
    }
    SetDopplegangerStep(9);
    DOPPLEGANGER.velocityY = FIX(-12);
    SetDopplegangerAnim(0x21);
    g_Dop.unk4A = 0;
    g_Dop.unk44 &= 0xFFFE;
    OVL_EXPORT(CreateEntFactoryFromEntity)(g_CurrentEntity, FACTORY(2, 0), 0);
}

static s16 D_us_8018132C[] = {
    SFX_BO4_UNK_7DE,
    SFX_BO4_UNK_7DF,
    SFX_BO4_UNK_7E0,
    SFX_BO4_UNK_7E1,
};

void OVL_EXPORT(func_8010EA54)(s32 arg0) {
    s16 temp_hi;

    if (arg0 != 0) {
        temp_hi = rand() % arg0;
        if (temp_hi < 4) {
            g_api.PlaySfx(D_us_8018132C[temp_hi]);
        }
    }
}

s32 func_us_801C5B68(void) {
    Entity* entity;
    s32 i;
    s32 entityCount;
    s32 targetCount;
    s32 animBase;
    s32 playerAnimOffset;
    s32 var_s4;

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

    OVL_EXPORT(CreateEntFactoryFromEntity)(g_CurrentEntity, FACTORY(3, 0), 0);

    g_Dop.timers[ALU_T_10] = 4;
    if (DOPPLEGANGER.step_s >= 0x40) {
        return 0;
    }

    animBase = 0x5D;
    switch (DOPPLEGANGER.step) {
    case Dop_Stand:
        var_s4 = playerAnimOffset;
        SetDopplegangerAnim(animBase + var_s4);
        break;
    case Dop_Crouch:
        var_s4 = 2;
        if (DOPPLEGANGER.step_s == 2) {
            var_s4 = playerAnimOffset;
            SetDopplegangerStep(1);
        }
        SetDopplegangerAnim(animBase + var_s4);
        break;
    }
    return 0;
}

#ifndef VERSION_PC
static void func_8010ED54(u8 anim) UNUSED {
    DOPPLEGANGER.velocityX = DOPPLEGANGER.velocityY = 0;
    SetDopplegangerStep(16);
    SetDopplegangerAnim(anim);
    OVL_EXPORT(CreateEntFactoryFromEntity)(g_CurrentEntity, FACTORY(61, 20), 0);
    g_Dop.unk48 = 0;
}
#endif

s32 func_us_801C5CF8(void) {
    s32 defaultAnimOffset;
    s32 attackPressed;
    s16 animOffset;
    s16 animBase;

    defaultAnimOffset = 0;
    if (g_Dop.vram_flag & IN_AIR_OR_EDGE) {
        defaultAnimOffset = 1;
    }

    attackPressed = g_Dop.padTapped & (PAD_SQUARE | PAD_CIRCLE);
    animBase = func_us_801C5B68();

    if (!animBase) {
        return 1;
    }

    if (animBase < 0) {
        return 0;
    }

    if (g_Dop.unk46 & 0x8000) {
        return 0;
    }

    if (g_Dop.timers[ALU_T_CURSE]) {
        OVL_EXPORT(CreateEntFactoryFromEntity)
        (g_CurrentEntity, FACTORY(0x39, 1), 0);

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
        g_api.PlaySfx(SFX_BO4_UNK_7D7);
        return 1;
    }

    if (attackPressed == PAD_SQUARE) {
        OVL_EXPORT(CreateEntFactoryFromEntity)
        (g_CurrentEntity, FACTORY(0x30, 0), 0);
        DOPPLEGANGER.step_s = 0x41;
        g_Dop.unk46 = 0x8002;
        g_Dop.unk54 = 0xD;
        animBase = 0x41;
    } else {
        g_Dop.unk46 = 0x8003;
        DOPPLEGANGER.step_s = 0x42;
        OVL_EXPORT(CreateEntFactoryFromEntity)
        (g_CurrentEntity, FACTORY(0x30, 1), 0);
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
    g_Dop.timers[ALU_T_9] = 4;

    return 1;
}

void OVL_EXPORT(func_8010FAF4)(void) {
    Entity* ent = &g_Entities[E_ID_50];
    DestroyEntity(ent);
    g_Dop.unk46 = 0;
}

void func_us_801C5FDC(void) {
    DOPPLEGANGER.step = Dop_Stand;
    DOPPLEGANGER.step_s = 3;
    SetSpeedX(FIX(-3.5));
    g_CurrentEntity->velocityY = FIX(0.0);
    SetDopplegangerAnim(0xDB);
    OVL_EXPORT(CreateEntFactoryFromEntity)(g_CurrentEntity, 0, 0);
}

bool func_us_801C6040(s32 arg0) {
    s32 velocityX;
    s32 velocityY;
    u8 _pad[40]; // n.b.! needs to be 33-40 bytes (inclusive)

    if (arg0 & 8) {
        if (g_Dop.unk46 == 0) {
            OVL_EXPORT(CheckMoveDirection)();
        }
    }

    if (arg0 & 0x8000) {
        DOPPLEGANGER.velocityY += FIX(11.0 / 64.0);
        if (DOPPLEGANGER.velocityY > FIX(7.0)) {
            DOPPLEGANGER.velocityY = FIX(7.0);
        }
    }
    if (arg0 & 0x10000) {
        if (DOPPLEGANGER.velocityY < FIX(3.0 / 8.0) &&
            DOPPLEGANGER.velocityY > -FIX(1.0 / 8.0) && !(g_Dop.unk44 & 0x20) &&
            (g_Dop.padPressed & 0x40)) {
            DOPPLEGANGER.velocityY += FIX(563.0 / 16384.0);
        } else {

            DOPPLEGANGER.velocityY += FIX(11.0 / 64.0);
            if (DOPPLEGANGER.velocityY > FIX(7.0)) {
                DOPPLEGANGER.velocityY = FIX(7.0);
            }
        }
    }

    if (arg0 & 0x80) {
        if (g_Dop.vram_flag & TOUCHING_CEILING) {
            if (DOPPLEGANGER.velocityY < FIX(-1)) {
                DOPPLEGANGER.velocityY = FIX(-1);
            }
        }
    }
    if (arg0 & 0x200) {
        if (DOPPLEGANGER.velocityY < FIX(3.0 / 8.0) &&
            DOPPLEGANGER.velocityY > -FIX(1.0 / 8.0)) {
            DOPPLEGANGER.velocityY += FIX(11.0 / 128.0);
        } else {
            DOPPLEGANGER.velocityY += FIX(11.0 / 64.0);
            if (DOPPLEGANGER.velocityY > FIX(7)) {
                DOPPLEGANGER.velocityY = FIX(7);
            }
        }
    }

    if (DOPPLEGANGER.velocityY >= 0) {
        if ((arg0 & 1) && (g_Dop.vram_flag & TOUCHING_GROUND)) {
            if (g_Dop.unk46) {
                if ((g_Dop.unk46 & 0x7FFF) == 0xFF) {
                    OVL_EXPORT(func_8010E570)(0);
                    OVL_EXPORT(func_8010FAF4)();
                    g_api.PlaySfx(SFX_STOMP_SOFT_B);
                    return true;
                }
                if (DOPPLEGANGER.velocityY > FIX(6.875)) {
                    OVL_EXPORT(func_8010E470)(1, 0U);
                    g_api.PlaySfx(SFX_STOMP_HARD_B);
                    OVL_EXPORT(CreateEntFactoryFromEntity)
                    (g_CurrentEntity, 0, 0);
                } else {
                    if (g_Dop.unk44 & 0x10) {
                        OVL_EXPORT(func_8010E6AC)(1);
                    } else {
                        OVL_EXPORT(func_8010E570)(0);
                    }
                    g_api.PlaySfx(SFX_STOMP_SOFT_B);
                }
                OVL_EXPORT(func_8010FAF4)();
                return true;
            }
            if (DOPPLEGANGER.velocityY > FIX(6.875)) {
                if (DOPPLEGANGER.step_s == 0x70 ||
                    DOPPLEGANGER.step == Dop_Jump) {
                    OVL_EXPORT(func_8010E470)(3, DOPPLEGANGER.velocityX / 2);
                } else {
                    OVL_EXPORT(func_8010E470)(1, 0);
                }
                g_api.PlaySfx(SFX_STOMP_HARD_B);
                OVL_EXPORT(CreateEntFactoryFromEntity)(g_CurrentEntity, 0, 0);
            } else if (g_Dop.unk44 & 0x10) {
                OVL_EXPORT(func_8010E6AC)(1);
                g_api.PlaySfx(SFX_STOMP_SOFT_B);
            } else if (abs(DOPPLEGANGER.velocityX) > FIX(2)) {
                g_api.PlaySfx(SFX_STOMP_HARD_B);
                OVL_EXPORT(CreateEntFactoryFromEntity)(g_CurrentEntity, 0, 0);
                OVL_EXPORT(func_8010E570)(DOPPLEGANGER.velocityX);
            } else {
                g_api.PlaySfx(SFX_STOMP_SOFT_B);
                OVL_EXPORT(func_8010E570)(0);
            }
            return true;
        }

        if ((arg0 & 0x20000) && (g_Dop.vram_flag & TOUCHING_GROUND)) {
            OVL_EXPORT(func_8010E470)(3, DOPPLEGANGER.velocityX);
            g_api.PlaySfx(SFX_STOMP_HARD_B);
            OVL_EXPORT(CreateEntFactoryFromEntity)(g_CurrentEntity, 0, 0);
            return true;
        }
    }

    if ((arg0 & 4) && !(g_Dop.vram_flag & TOUCHING_GROUND)) {
        func_us_801C59DC();
        return true;
    }

    if ((arg0 & 0x1000) && (g_Dop.padTapped & 0xA0) && func_us_801C5CF8()) {
        return true;
    }

    if (!(g_Dop.unk46 & 0x8000)) {
        if ((arg0 & 0x10) && (g_Dop.padTapped & 0x40)) {
            func_us_801C58E4();
            return true;
        }

        if ((arg0 & 0x20) && (g_Dop.padTapped & 0x40) && !(g_Dop.unk44 & 1)) {
            func_us_801C5990();
            return true;
        }

        if ((arg0 & 0x2000) && (g_Dop.padPressed & 0x4000)) {
            OVL_EXPORT(func_8010E470)(2, 0U);
            return true;
        }

        if ((arg0 & 0x40000) && (g_Dop.padTapped & 0x10) &&
            DOPPLEGANGER.ext.player.anim != 0xDB) {
            func_us_801C5FDC();
            return true;
        }
    }

    return false;
}

void OVL_EXPORT(func_80111CC0)(void) {
    if (g_Dop.timers[ALU_T_CURSE] != 0) {
        OVL_EXPORT(CreateEntFactoryFromEntity)
        (g_CurrentEntity, FACTORY(0x2C, 0x17), 0);
    }
    if (g_Dop.timers[ALU_T_POISON] != 0) {
        OVL_EXPORT(CreateEntFactoryFromEntity)
        (g_CurrentEntity, FACTORY(0x2C, 0x16), 0);
    }
}

void DopplegangerStepStand(void) {
    s32 anim;
    u16 var_s0;

    var_s0 = 3;
    anim = 0;
    if (g_Dop.vram_flag & IN_AIR_OR_EDGE) {
        anim = 1;
    }

    if (func_us_801C6040(0x4301C) == false) {
        DecelerateX(FIX(0.125));
        switch (DOPPLEGANGER.step_s) {
        case 0:
        case 2:
            break;
        case 1:
            var_s0 = 1;
            if (!(g_Dop.padPressed & PAD_UP)) {
                var_s0 = 5;
            }
            break;
        case 3:
            var_s0 = 0;
            if (DOPPLEGANGER.pose > 3) {
                var_s0 = 1;
            }
            if (DOPPLEGANGER.pose > 6 || DOPPLEGANGER.poseTimer < 0) {
                var_s0 = 7;
            }
            break;
        case 0x40:
        case 0x41:
        case 0x42:
            func_us_801C5354(1, 1);
            if (DOPPLEGANGER.pose < g_Dop.unk54) {
                var_s0 = 0;
            } else {
                g_Dop.unk46 &= 0x7FFF;
                var_s0 = 0x1B;
                if (DOPPLEGANGER.poseTimer < 0) {
                    var_s0 = 0xF;
                }
            }
            break;
        case 0x51:

            func_us_801C5354(1, 1);
            var_s0 = 0;
            if (DOPPLEGANGER.poseTimer < 0) {
                var_s0 = 0xF;
            }

            break;
        }

        if (var_s0 & 4) {
            OVL_EXPORT(func_8010E570)(0);
            var_s0 |= 0x8000;
        }
        if (var_s0 & 2 && g_Dop.padPressed & PAD_UP && !g_Dop.unk48) {
            SetDopplegangerAnim(anim);
            DOPPLEGANGER.step_s = 1;
            var_s0 |= 0x8000;
        }

        if (var_s0 & 1 && OVL_EXPORT(CheckMoveDirection)() != 0) {
            OVL_EXPORT(func_8010E6AC)(0);
            var_s0 |= 0x8000;
        }
        if (var_s0 & 0x8000 && var_s0 & 8) {
            OVL_EXPORT(func_8010FAF4)();
        }
    }
}

void DopplegangerStepWalk(void) {
    if (func_us_801C6040(0x4301C) == false) {
        SetSpeedX(FIX(1.5));
        if (OVL_EXPORT(CheckMoveDirection)() == 0) {
            OVL_EXPORT(func_8010E570)(0);
        }
    }
}

static s16 D_us_80181334[] = {
    1,
    31,
    0,
    27,
};

void DopplegangerStepJump(void) {
    s32 moveDirection;
    s16 index;

    DecelerateX(FIX(1.0 / 16.0));
    if (DOPPLEGANGER.velocityY < FIX(-1)) {
        if (!(g_Dop.unk44 & 0x40) && !(g_Dop.padPressed & 0x40)) {
            DOPPLEGANGER.velocityY = FIX(-1);
        }
        if (g_Dop.vram_flag & TOUCHING_CEILING) {
            DOPPLEGANGER.velocityY = FIX(-0.25);
            g_Dop.unk44 |= 0x20;
        }
    }

    if (func_us_801C6040(0x11029)) {
        return;
    }

    switch (DOPPLEGANGER.step_s) {
    case 0:
        moveDirection = OVL_EXPORT(CheckMoveDirection)();
        if (moveDirection) {
            if (DOPPLEGANGER.ext.player.anim == 22 ||
                DOPPLEGANGER.ext.player.anim == 25) {
                SetDopplegangerAnim(24);
            }
            SetSpeedX(FIX(1.5));
        } else if (DOPPLEGANGER.ext.player.anim == 26 ||
                   DOPPLEGANGER.ext.player.anim == 24) {
            SetDopplegangerAnim(25);
        }
        if (moveDirection <= 0) {
            g_Dop.unk44 &= 0xFFEF;
        }
        if (DOPPLEGANGER.velocityY > 0) {
            if (DOPPLEGANGER.ext.player.anim != 27) {
                SetDopplegangerAnim(27);
            }
            DOPPLEGANGER.step_s = 1;
        }
        break;
    case 1:
        moveDirection = OVL_EXPORT(CheckMoveDirection)();
        if (moveDirection != 0) {
            SetSpeedX(FIX(1.5));
        }
        if (moveDirection <= 0) {
            g_Dop.unk44 &= 0xFFEF;
        }

        break;

    case 0x40:
    case 0x41:
    case 0x42:
    case 0x51:
        func_us_801C5354(1, 1);
        if (g_Dop.padPressed & PAD_LEFT) {
            DOPPLEGANGER.velocityX = FIX(-1.5);
        }
        if (g_Dop.padPressed & PAD_RIGHT) {
            DOPPLEGANGER.velocityX = FIX(1.5);
        }
        if (DOPPLEGANGER.poseTimer < 0) {
            if (DOPPLEGANGER.velocityY > FIX(1)) {
                index = 0;
            } else {
                index = 2;
            }
            DOPPLEGANGER.step_s = D_us_80181334[index];
            SetDopplegangerAnim((u8)D_us_80181334[index + 1]);
            OVL_EXPORT(func_8010FAF4)();
        }
        break;
    }
}

void DopplegangerStepFall(void) {
    if (func_us_801C6040(0x9029) == false) {
        DecelerateX(FIX(1.0 / 16.0));
        if (OVL_EXPORT(CheckMoveDirection)() != 0) {
            SetSpeedX(FIX(3.0 / 4.0));
        }
    }
}

void DopplegangerStepCrouch(void) {
    s32 anim;
    s16 var_s0;
    u8 _pad[40]; // any size between 33-40 (inclusive);

    var_s0 = 0;
    // n.b.! much of this code is copied from `DopplegangerStepStand`,
    // but this variable is not used in this version of the function
    anim = 0;
    if (g_Dop.vram_flag & IN_AIR_OR_EDGE) {
        anim = 1;
    }

    if (func_us_801C6040(0x100C) == false) {
        DecelerateX(FIX(0.125));
        switch (DOPPLEGANGER.step_s) {
        case 0:
            var_s0 = 6;
            break;

        case 1:
            if (!(g_Dop.padPressed & PAD_DOWN)) {
                // n.b.! var_s0 is set, but never used
                var_s0 = 1;
                SetDopplegangerAnim(0x13);
                DOPPLEGANGER.step_s = 2;
                DOPPLEGANGER.pose = 1;
                return;
            }

            if (DOPPLEGANGER.ext.player.anim == 0x65) {
                DOPPLEGANGER.step_s = 0;
            } else if (DOPPLEGANGER.poseTimer < 0) {
                var_s0 = 0x20;
            }
            break;
        case 3:
        case 4:
            if (DOPPLEGANGER.poseTimer < 0) {
                var_s0 = 0x20;
            }
            break;
        case 2:
            var_s0 = 1;
            if (DOPPLEGANGER.poseTimer < 0) {
                OVL_EXPORT(func_8010E570)(0);
            }
            break;
        case 0x40:
        case 0x41:
        case 0x42:
            func_us_801C5354(1, 1);
            if (DOPPLEGANGER.pose < g_Dop.unk54) {
                var_s0 = 0;
            } else {
                g_Dop.unk46 &= 0x7FFF;
                var_s0 = 0xE;
                if (DOPPLEGANGER.poseTimer < 0) {
                    var_s0 = 0x2E;
                }
            }
            break;
        case 0x51:
            func_us_801C5354(1, 1);
            if (DOPPLEGANGER.poseTimer < 0) {
                var_s0 = 0x2E;
            }
            break;
        }

        if (var_s0 & 0x20) {
            OVL_EXPORT(func_8010E470)(0, 0);
            var_s0 |= 0x8000;
        }

        if (var_s0 & 2 && g_Dop.unk4C) {
            SetDopplegangerAnim(0x14);
            DOPPLEGANGER.step_s = 0;
            var_s0 |= 0x8000;
        }

        if (var_s0 & 4 && !(g_Dop.padPressed & 0x4000)) {
            SetDopplegangerAnim(0x13);
            DOPPLEGANGER.step_s = 2;
            var_s0 |= 0x8000;
        }

        if (var_s0 & 1 && OVL_EXPORT(CheckMoveDirection)()) {
            OVL_EXPORT(func_8010E6AC)(0);
            var_s0 |= 0x8000;
        }

        if (var_s0 & 0x8000 && var_s0 & 8) {
            OVL_EXPORT(func_8010FAF4)();
        }
    }
}
