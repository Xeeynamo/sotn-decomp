// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

extern PlayerState g_Dop;

// n.b.! this file is the same as bo4/unk_45354.c

extern s16 D_us_801D433E;

// may be equivalent func_8010DFF0 in DRA
void func_us_801C4954(s32 resetAnims, s32 arg1) {
    Primitive* prim;

    if (resetAnims) {
        g_Entities[E_ID_41].ext.disableAfterImage.unk7D = 1;
        g_Entities[E_ID_41].animCurFrame = g_Entities[E_ID_42].animCurFrame =
            g_Entities[E_ID_43].animCurFrame = 0;
        prim = &g_PrimBuf[g_Entities[1].primIndex];
        while (prim != NULL) {
            prim->x1 = 0;
            prim = prim->next;
        }
    }
    g_Entities[E_ID_41].ext.disableAfterImage.unk7C = 1;
    g_Entities[E_ID_41].ext.disableAfterImage.unk7E = 0xA;
    if (arg1 != 0) {
        if (arg1 < 4) {
            D_us_801D433E = 4;
        } else {
            D_us_801D433E = arg1;
        }
    }
}

void func_8010E0A8(void) {
    g_Entities[STAGE_ENTITY_START + UNK_ENTITY_1].ext.entSlot1.unk2 = 0;
}

void func_8010E0B8(void) {
    g_Entities[STAGE_ENTITY_START + UNK_ENTITY_1].ext.entSlot1.unk1 = 0;
    g_Entities[STAGE_ENTITY_START + UNK_ENTITY_1].ext.entSlot1.unk0 = 0;
}

void func_us_801C4A30(s16 a0, s16 a1) {
    if (g_Dop.timers[ALU_T_INVINCIBLE_CONSUMABLES] <= a1) {
        g_Dop.timers[ALU_T_INVINCIBLE_CONSUMABLES] = a1;
    }
}

#include "../../decelerate.h"

s32 CheckMoveDirection(void) {
    if (g_Dop.unk44 & 2) {
        return 0;
    }
    if (DOPPLEGANGER.facingLeft == 1) {
        if (g_Dop.padPressed & PAD_RIGHT) {
            DOPPLEGANGER.facingLeft = 0;
            g_Dop.unk4C = 1;
            return -1;
        } else if (g_Dop.padPressed & PAD_LEFT) {
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

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C4BA8);

#include "../../set_speed_x.h"

void func_8010E3B8(s32 velocityX) {
    if (DOPPLEGANGER.entityRoomIndex == 1) {
        velocityX = -velocityX;
    }
    DOPPLEGANGER.velocityX = velocityX;
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_8010E470);

extern u8 D_us_801813AC[];

void func_8010E570(s32 arg0) {
    s32 anim = 0;
    bool atLedge = false;

    if (g_Dop.vram_flag & 0x20) {
        atLedge = true;
    }

    DOPPLEGANGER.velocityX = arg0;
    DOPPLEGANGER.velocityY = 0;
    SetPlayerStep(Dop_Stand);
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
    SetPlayerAnim(D_us_801813AC[anim]);
}

void func_8010E6AC(bool forceAnim13) {
    bool atLedge;

    atLedge = 0;
    if (g_Dop.vram_flag & 0x20) {
        atLedge = 1;
    }

    SetSpeedX(FIX(1.5));
    DOPPLEGANGER.velocityY = 0;
    SetPlayerStep(Dop_Walk);

    if (forceAnim13) {
        if (DOPPLEGANGER.ext.player.anim != 13) {
            SetPlayerAnim(13);
        }
    } else {
        SetPlayerAnim(7);
        // Factory blueprint 1 has child 2, which is func_8011B5A4
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(1, 5), 0);
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
        SetPlayerAnim(0x1A);
        SetSpeedX(FIX(3.0 / 2.0));
        g_Dop.unk44 = 0;
    } else {
        SetPlayerAnim(0x16);
        DOPPLEGANGER.velocityX = 0;
        g_Dop.unk44 = 4;
    }
    DOPPLEGANGER.velocityY = FIX(-4.875);
    SetPlayerStep(5);
    if (g_Dop.prev_step == 2) {
        g_Dop.unk44 |= 0x10;
    }
}

void func_us_801C4F90(void) {
    DOPPLEGANGER.velocityY = FIX(-4.25);
    g_Dop.unk44 |= 0x21;
    SetPlayerAnim(0x20);
    DOPPLEGANGER.step_s = 0;
}

void func_us_801C4FDC(void) {
    SetPlayerStep(4);
    if (g_Dop.prev_step != 2) {
        SetPlayerAnim(0x1C);
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
    SetPlayerStep(9);
    DOPPLEGANGER.velocityY = FIX(-12);
    SetPlayerAnim(0x21);
    g_Dop.unk4A = 0;
    g_Dop.unk44 &= 0xFFFE;
    CreateEntFactoryFromEntity(g_CurrentEntity, 2, 0);
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_8010EA54);

s32 func_us_801C5168(void) {
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
    if (g_Dop.vram_flag & 0x20) {
        playerAnimOffset = 1;
    }

    targetCount = 3;
    for (entity = &g_Entities[E_ID_60], i = 0, entityCount = 0; i < 16; i++,
        entity++) {
        if (entity->entityId == E_ID_14) {
            entityCount++;
        }
        if (entityCount >= targetCount) {
            return -1;
        }
    }

    CreateEntFactoryFromEntity(g_CurrentEntity, 24, 0);

    g_Dop.timers[10] = 4;
    if (DOPPLEGANGER.step_s >= 0x40) {
        return 0;
    }

    animBase = 0x5D;
    switch (DOPPLEGANGER.step) {
    case 1:
        var_s4 = playerAnimOffset;
        SetPlayerAnim(animBase + var_s4);
        break;
    case 3:
        var_s4 = 2;
        if (DOPPLEGANGER.step_s == 2) {
            var_s4 = playerAnimOffset;
            SetPlayerStep(1);
        }
        SetPlayerAnim(animBase + var_s4);
        break;
    }
    return 0;
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_8010ED54);

s32 func_us_801C52F8(void) {
    s32 defaultAnimOffset;
    s32 deltaX;
    s16 animOffset;
    s16 animBase;

    defaultAnimOffset = 0;
    if (g_Dop.vram_flag & 0x20) {
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
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x39, 1), 0);

        switch (DOPPLEGANGER.step) {
        case 1:
        case 2:
            SetPlayerAnim(0xB5);
            DOPPLEGANGER.step = 1;
            break;
        case 3:
            SetPlayerAnim(0xB6);
            DOPPLEGANGER.step = 3;
            break;
        case 4:
        case 5:
            SetPlayerAnim(0xB7);
            DOPPLEGANGER.step = 5;
            break;
        }
        g_Dop.unk46 = 0x8012;
        g_Dop.unk54 = 0xFF;
        DOPPLEGANGER.step_s = 0x51;
        g_api.PlaySfx(SFX_BO4_UNK_7D7);
        return 1;
    }

    deltaX = abs(DOPPLEGANGER.posX.i.hi - PLAYER.posX.i.hi);

    if (deltaX > 36) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x30, 0), 0);
        DOPPLEGANGER.step_s = 0x41;
        g_Dop.unk46 = 0x8002;
        g_Dop.unk54 = 0xD;
        animBase = 0x41;
    } else {
        g_Dop.unk46 = 0x8003;
        DOPPLEGANGER.step_s = 0x42;
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x30, 1), 0);
        g_Dop.unk54 = 8;
        animBase = 0xA7;
    }

    switch (DOPPLEGANGER.step) {
    case 1:
    case 2:
        g_CurrentEntity->velocityX = g_CurrentEntity->velocityX >> 1;
        DOPPLEGANGER.step = 1;
        animOffset = defaultAnimOffset;
        break;
    case 3:
        animOffset = 2;
        if (g_Dop.padPressed & (PAD_RIGHT | PAD_LEFT)) {
            animOffset++;
        }
        if (DOPPLEGANGER.step_s == 2) {
            animOffset = defaultAnimOffset;
            DOPPLEGANGER.step = 1;
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

    SetPlayerAnim(animBase + animOffset);
    g_Dop.timers[9] = 4;

    return 1;
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_8010FAF4);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C55EC);

s32 func_us_801C5650(s32 arg0) {
    s32 velocityX;
    s32 velocityY;
    u8 _pad[40]; // n.b.! needs to be 33-40 bytes (inclusive)

    if (arg0 & 8) {
        if (g_Dop.unk46 == 0) {
            CheckMoveDirection();
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
        if (g_Dop.vram_flag & 2) {
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
        if ((arg0 & 1) && (g_Dop.vram_flag & 1)) {
            if (g_Dop.unk46) {
                if ((g_Dop.unk46 & 0x7FFF) == 0xFF) {
                    func_8010E570(0);
                    func_8010FAF4();
                    g_api.PlaySfx(SFX_STOMP_SOFT_B);
                    return 1;
                }
                if (DOPPLEGANGER.velocityY > FIX(6.875)) {
                    func_8010E470(1, 0U);
                    g_api.PlaySfx(SFX_STOMP_HARD_B);
                    CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
                } else {
                    if (g_Dop.unk44 & 0x10) {
                        func_8010E6AC(1);
                    } else {
                        func_8010E570(0);
                    }
                    g_api.PlaySfx(SFX_STOMP_SOFT_B);
                }
                func_8010FAF4();
                return 1;
            }
            if (DOPPLEGANGER.velocityY > FIX(6.875)) {
                if (DOPPLEGANGER.step_s == 0x70 || DOPPLEGANGER.step == 5) {
                    func_8010E470(3, DOPPLEGANGER.velocityX / 2);
                } else {
                    func_8010E470(1, 0);
                }
                g_api.PlaySfx(SFX_STOMP_HARD_B);
                CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
            } else if (g_Dop.unk44 & 0x10) {
                func_8010E6AC(1);
                g_api.PlaySfx(SFX_STOMP_SOFT_B);
            } else if (abs(DOPPLEGANGER.velocityX) > FIX(2)) {
                g_api.PlaySfx(SFX_STOMP_HARD_B);
                CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
                func_8010E570(DOPPLEGANGER.velocityX);
            } else {
                g_api.PlaySfx(SFX_STOMP_SOFT_B);
                func_8010E570(0);
            }
            return 1;
        }

        if ((arg0 & 0x20000) && (g_Dop.vram_flag & 1)) {
            func_8010E470(3, DOPPLEGANGER.velocityX);
            g_api.PlaySfx(SFX_STOMP_HARD_B);
            CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
            return 1;
        }
    }

    if ((arg0 & 4) && !(g_Dop.vram_flag & 0x1)) {
        func_us_801C4FDC();
        return 1;
    }

    if ((arg0 & 0x1000) && (g_Dop.padTapped & 0xA0) && func_us_801C52F8()) {
        return 1;
    }

    if (!(g_Dop.unk46 & 0x8000)) {
        if ((arg0 & 0x10) && (g_Dop.padTapped & 0x40)) {
            func_us_801C4EE4();
            return 1;
        }

        if ((arg0 & 0x20) && (g_Dop.padTapped & 0x40) && !(g_Dop.unk44 & 1)) {
            func_us_801C4F90();
            return 1;
        }

        if ((arg0 & 0x2000) && (g_Dop.padPressed & 0x4000)) {
            func_8010E470(2, 0U);
            return 1;
        }

        if ((arg0 & 0x40000) && (g_Dop.padTapped & 0x10) &&
            DOPPLEGANGER.ext.player.anim != 0xDB) {
            func_us_801C55EC();
            return 1;
        }
    }

    return 0;
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_80111CC0);

void func_us_801C5C64(void) {
    s32 anim;
    u16 var_s0;

    var_s0 = 3;
    anim = 0;
    if (g_Dop.vram_flag & 0x20) {
        anim = 1;
    }

    if (func_us_801C5650(0x4301C) == 0) {
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
            func_us_801C4954(1, 1);
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

            func_us_801C4954(1, 1);
            var_s0 = 0;
            if (DOPPLEGANGER.poseTimer < 0) {
                var_s0 = 0xF;
            }

            break;
        }

        if (var_s0 & 4) {
            func_8010E570(0);
            var_s0 |= 0x8000;
        }
        if (var_s0 & 2 && g_Dop.padPressed & PAD_UP && !g_Dop.unk48) {
            SetPlayerAnim(anim);
            DOPPLEGANGER.step_s = 1;
            var_s0 |= 0x8000;
        }

        if (var_s0 & 1 && CheckMoveDirection() != 0) {
            func_8010E6AC(0);
            var_s0 |= 0x8000;
        }
        if (var_s0 & 0x8000 && var_s0 & 8) {
            func_8010FAF4();
        }
    }
}

void PlayerStepWalk(void) {
    if (func_us_801C5650(0x4301C) == 0) {
        SetSpeedX(FIX(1.5));
        if (CheckMoveDirection() == 0) {
            func_8010E570(0);
        }
    }
}

extern s16 D_us_801813C0[];

void func_us_801C5EE0(void) {
    s32 moveDirection;
    s16 index;

    DecelerateX(FIX(1.0 / 16.0));
    if (DOPPLEGANGER.velocityY < FIX(-1)) {
        if (!(g_Dop.unk44 & 0x40) && !(g_Dop.padPressed & 0x40)) {
            DOPPLEGANGER.velocityY = FIX(-1);
        }
        if (g_Dop.vram_flag & 2) {
            DOPPLEGANGER.velocityY = FIX(-0.25);
            g_Dop.unk44 |= 0x20;
        }
    }

    if (func_us_801C5650(0x11029)) {
        return;
    }

    switch (DOPPLEGANGER.step_s) {
    case 0:
        moveDirection = CheckMoveDirection();
        if (moveDirection) {
            if (DOPPLEGANGER.ext.player.anim == 22 ||
                DOPPLEGANGER.ext.player.anim == 25) {
                SetPlayerAnim(24);
            }
            SetSpeedX(FIX(1.5));
        } else if (DOPPLEGANGER.ext.player.anim == 26 ||
                   DOPPLEGANGER.ext.player.anim == 24) {
            SetPlayerAnim(25);
        }
        if (moveDirection <= 0) {
            g_Dop.unk44 &= 0xFFEF;
        }
        if (DOPPLEGANGER.velocityY > 0) {
            if (DOPPLEGANGER.ext.player.anim != 27) {
                SetPlayerAnim(27);
            }
            DOPPLEGANGER.step_s = 1;
        }
        break;
    case 1:
        moveDirection = CheckMoveDirection();
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
        func_us_801C4954(1, 1);
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
            DOPPLEGANGER.step_s = D_us_801813C0[index];
            SetPlayerAnim((u8)D_us_801813C0[index + 1]);
            func_8010FAF4();
        }
        break;
    }
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C61B0);

void func_us_801C61F8(void) {
    s32 anim;
    s16 var_s0;
    u8 _pad[40]; // any size between 33-40 (inclusive);

    var_s0 = 0;
    // n.b.! much of this code is copied from `func_us_801C6654`,
    // but this variable is not used in this version of the function
    anim = 0;
    if (g_Dop.vram_flag & 0x20) {
        anim = 1;
    }

    if (func_us_801C5650(0x100C) == 0) {
        DecelerateX(FIX(0.125));
        switch (DOPPLEGANGER.step_s) {
        case 0:
            var_s0 = 6;
            break;

        case 1:
            if (!(g_Dop.padPressed & PAD_DOWN)) {
                // n.b.! var_s0 is set, but never used
                var_s0 = 1;
                SetPlayerAnim(0x13);
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
                func_8010E570(0);
            }
            break;
        case 0x40:
        case 0x41:
        case 0x42:
            func_us_801C4954(1, 1);
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
            func_us_801C4954(1, 1);
            if (DOPPLEGANGER.poseTimer < 0) {
                var_s0 = 0x2E;
            }
            break;
        }

        if (var_s0 & 0x20) {
            func_8010E470(0, 0);
            var_s0 |= 0x8000;
        }

        if (var_s0 & 2 && g_Dop.unk4C) {
            SetPlayerAnim(0x14);
            DOPPLEGANGER.step_s = 0;
            var_s0 |= 0x8000;
        }

        if (var_s0 & 4 && !(g_Dop.padPressed & PAD_DOWN)) {
            SetPlayerAnim(0x13);
            DOPPLEGANGER.step_s = 2;
            var_s0 |= 0x8000;
        }

        if (var_s0 & 1 && CheckMoveDirection()) {
            func_8010E6AC(0);
            var_s0 |= 0x8000;
        }

        if (var_s0 & 0x8000 && var_s0 & 8) {
            func_8010FAF4();
        }
    }
}
