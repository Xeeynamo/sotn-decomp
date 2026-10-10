// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"
#include "../../dra/subwpn_dagger.h"

// Used in dra/7E4BC, dra/bss, rbo5/unk_4648C, bo4/unk_465F0
typedef struct {
    f32 posX;
    f32 posY;
    s16 angle1;
    s16 angle2;
    s16 size;
    s16 xOffset;
    s16 yOffset;
    s16 pad;
} mistStruct; // size = 0x14

Entity* CreateEntFactoryFromEntity(Entity* source, u32 factoryParams, s16 arg2);

extern PlayerState g_Dop;

void func_us_801C5354(s32 resetAnims, s32 arg1);
s32 CheckMoveDirection(void);
void func_8010E470(s32 arg0, s32 velocityX);
void func_8010E570(s32 arg0);
void func_8010E6AC(bool forceAnim13);
void func_8010FAF4(void);
bool func_us_801C6040(s32 arg0);
void DecelerateX(s32 amount);
void SetSpeedX(s32 speed);
void SetDopplegangerAnim(s32 anim);

void func_80111CC0(void) {
    if (g_Dop.timers[ALU_T_CURSE]) {
        CreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x17), 0);
    }
    if (g_Dop.timers[ALU_T_POISON]) {
        CreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x16), 0);
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
            func_8010E570(0);
            var_s0 |= 0x8000;
        }
        if (var_s0 & 2 && g_Dop.padPressed & PAD_UP && !g_Dop.unk48) {
            SetDopplegangerAnim(anim);
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

void DopplegangerStepWalk(void) {
    if (func_us_801C6040(0x4301C) == false) {
        SetSpeedX(FIX(1.5));
        if (CheckMoveDirection() == 0) {
            func_8010E570(0);
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
        if (!(g_Dop.unk44 & 0x40) && !(g_Dop.padPressed & PAD_CROSS)) {
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
        moveDirection = CheckMoveDirection();
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
            func_8010FAF4();
        }
        break;
    }
}

void DopplegangerStepFall(void) {
    if (func_us_801C6040(0x9029) == false) {
        DecelerateX(FIX(1.0 / 16.0));
        if (CheckMoveDirection() != 0) {
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
        case 4:
        case 3:
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
            func_8010E470(0, 0);
            var_s0 |= 0x8000;
        }

        if (var_s0 & 2 && g_Dop.unk4C) {
            SetDopplegangerAnim(0x14);
            DOPPLEGANGER.step_s = 0;
            var_s0 |= 0x8000;
        }

        if (var_s0 & 4 && !(g_Dop.padPressed & PAD_DOWN)) {
            SetDopplegangerAnim(0x13);
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

// n.b.! this is the same as rbo5/unk_4648C.c

void func_us_801C6E7C(u16 arg0) {
    s16 move = 3;

    if (DOPPLEGANGER.facingLeft) {
        move = -move;
    }

    DOPPLEGANGER.posY.i.hi -= 22;
    DOPPLEGANGER.posX.i.hi += move;
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_4, 1), 0);
    DOPPLEGANGER.posY.i.hi += 22;
    DOPPLEGANGER.posX.i.hi -= move;

    if (arg0 & 1) {
        g_api.ShakeCamera(SHAKE_Y_SMALL2);
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
    }
    if (arg0 & 2) {
        DOPPLEGANGER.velocityX = 0;
        DOPPLEGANGER.velocityY = 0;
    }
}

void SetDopplegangerAnim(s32 anim);
bool func_us_801C6040(s32 branchFlags);

extern PlayerState g_Dop;

#ifdef VERSION_PSP
INCLUDE_ASM("boss/bo4/nonmatchings/unk_465F0", DopplegangerStepHighJump);
#else
void DopplegangerStepHighJump(void) {
    s32 temp;
    s32 var_s1;

    var_s1 = 0;
    g_Dop.gravBootTimer++;
    if (func_us_801C6040(2) != 0) {
        return;
    }

    switch (DOPPLEGANGER.step_s) {
    case 0:
        if (g_Dop.vram_flag & TOUCHING_CEILING) {
            func_us_801C6E7C(3);
            if (g_Dop.gravBootTimer > 4) {
                DOPPLEGANGER.step_s = 2;
                DOPPLEGANGER.rotate = 0x800;
                DOPPLEGANGER.rotPivotX = 0;
                DOPPLEGANGER.rotPivotY = 2;
                DOPPLEGANGER.drawFlags |= ENTITY_ROTATE;
                DOPPLEGANGER.facingLeft = (DOPPLEGANGER.facingLeft + 1) & 1;
                SetDopplegangerAnim(0x2B);
            } else {
                DOPPLEGANGER.step_s = 3;
            }
        } else if (g_Dop.gravBootTimer > 28) {
            DOPPLEGANGER.step_s = 1;
            DOPPLEGANGER.velocityY = -0x60000;
            SetDopplegangerAnim(0x1B);
        }
        break;

    case 1:
        if (g_Dop.vram_flag & TOUCHING_CEILING) {
            DOPPLEGANGER.step_s = 2;
            func_us_801C6E7C(3);
        } else {
            DOPPLEGANGER.velocityY = DOPPLEGANGER.velocityY + 0x6000;
            if (DOPPLEGANGER.velocityY > 0x8000) {
                var_s1 = 1;
            }
        }
        break;

    case 2:
        DOPPLEGANGER.drawFlags |= ENTITY_ROTATE;
        DOPPLEGANGER.rotPivotX = 0;
        DOPPLEGANGER.rotPivotY = 2;
        if (g_Dop.gravBootTimer > 56) {
            SetDopplegangerAnim(0x2D);
            DOPPLEGANGER.rotate = 0;
            DOPPLEGANGER.step_s = 4;
            DOPPLEGANGER.drawFlags &=
                ENTITY_BLINK | ENTITY_MASK_B | ENTITY_MASK_G | ENTITY_MASK_R |
                ENTITY_OPACITY | ENTITY_SCALEY | ENTITY_SCALEX;
            DOPPLEGANGER.facingLeft = (DOPPLEGANGER.facingLeft + 1) & 1;
        }
        break;
    case 3:
        if (g_Dop.gravBootTimer > 20) {
            var_s1 = 1;
        }
        break;
    case 4:
        DOPPLEGANGER.velocityY += FIX(1.0 / 16.0);
        if (DOPPLEGANGER.poseTimer < 0) {
            var_s1 = 2;
        }
        break;
    }

    if (var_s1 != 0) {
        temp = 0; // TODO: !FAKE
        if ((var_s1 - 1) != temp) {
            SetDopplegangerAnim(0x1C);
        }
        DOPPLEGANGER.palette = PAL_FLAG(0x200);
        DOPPLEGANGER.step_s = 1;
        DOPPLEGANGER.step = Dop_Jump;
    }
}
#endif

s32 func_801133E68(void) {
    s16 rnd = rand() & PSP_RANDMASK;
    DOPPLEGANGER.ext.player.anim = 0x2E + (rnd % 3);
    return rnd % 16;
}

void func_8010FAF4();

// similar to DRA's func_80113EE0
static void func_us_801C72BC(void) {
    DOPPLEGANGER.pose = DOPPLEGANGER.poseTimer = 0;
    DOPPLEGANGER.animSet = ANIMSET_OVL(1);
    DOPPLEGANGER.blendMode = BLEND_NO;
    g_Dop.unk44 = 0;
    g_Dop.unk46 = 0;
    DOPPLEGANGER.drawFlags &= ENTITY_BLINK | ENTITY_MASK_B | ENTITY_MASK_G |
                              ENTITY_MASK_R | ENTITY_SCALEY | ENTITY_SCALEX;
    DOPPLEGANGER.rotate = 0;
    if (g_Entities[STAGE_ENTITY_START + 16].entityId == E_MIST) {
        func_8010FAF4();
    }
}

static void func_us_801C7340(void) {
    if (DOPPLEGANGER.posX.i.hi <= PLAYER.posX.i.hi) {
        DOPPLEGANGER.entityRoomIndex = 0;
    } else {
        DOPPLEGANGER.entityRoomIndex = 1;
    }
}

s16 D_us_8018133C[] = {
    SFX_VO_DOP_YELL,   SFX_VO_DOP_PAIN_F, SFX_VO_DOP_PAIN_E, SFX_VO_DOP_PAIN_D,
    SFX_VO_DOP_PAIN_C, SFX_VO_DOP_PAIN_B, SFX_VO_DOP_PAIN_A,
};

#ifdef VERSION_PSP
char D_pspeu_0926B178[] = "dam_kind:%04x\n";
INCLUDE_ASM("boss/bo4/nonmatchings/unk_465F0", DopplegangerHandleDamage);
#else
void DopplegangerHandleDamage(DamageParam* damage, s16 step, s16 step_s) {
    s32 sfxIndex;

    switch (DOPPLEGANGER.step_s) {
    case 0:
        sfxIndex = 0;
        func_us_801C72BC();
        func_us_801C7340();
        switch (damage->damageKind) {
        case 3:
            sfxIndex = (rand() & 1) + 3;
            DOPPLEGANGER.velocityY = FIX(-4);
            DopSetVelocity(FIX(-5.0 / 6));
            DOPPLEGANGER.step_s = 1;
            if (func_801133E68() == 0) {
                DOPPLEGANGER.ext.player.anim = 0x40;
            }
            break;
        case 2:
            sfxIndex = (rand() & 1) + 5;
            step--;
            switch (step) {
            case 0:
            case 1:
                DOPPLEGANGER.velocityY = 0;
                DopSetVelocity(FIX(-5.0 / 3));
                DOPPLEGANGER.step_s = 6;

                DOPPLEGANGER.ext.player.anim = 0x31;
                if (DOPPLEGANGER.entityRoomIndex != DOPPLEGANGER.facingLeft) {
                    DOPPLEGANGER.ext.player.anim = 0x33;
                }

                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_0, 6), 0);
                break;
            case 2:
                DOPPLEGANGER.velocityY = 0;
                DopSetVelocity(FIX(-1.25));
                DOPPLEGANGER.step_s = 7;
                DOPPLEGANGER.ext.player.anim = 0x23;
                CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
                break;
            default:
            case 3:
            case 4:
                DOPPLEGANGER.velocityY = FIX(-2);
                DopSetVelocity(FIX(-1.25));
                DOPPLEGANGER.step_s = 1;
                func_801133E68();
                break;
            }
            break;
        default:
            FntPrint("dam_kind:%04x\n", damage->damageKind);
            break;
        }

        g_Dop.damagePalette = PAL_FLAG(PAL_CC_RED_EFFECT_A);
        g_Dop.timers[ALU_T_HITEFFECT] = 6;
        g_api.PlaySfx(D_us_8018133C[sfxIndex]);

        if (damage->effects & EFFECT_UNK_8000) {
            g_api.PlaySfx(SFX_FM_EXPLODE_SWISHES);
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x45), 0);
            g_Dop.damagePalette = PAL_FLAG(PAL_CC_FIRE_EFFECT);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_17, 1), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_18, 0), 0);
            g_Dop.timers[ALU_T_HITEFFECT] = 0x10;
        } else if (damage->effects & EFFECT_UNK_0100) {
            g_Dop.timers[ALU_T_CURSE] = 0x400;
            g_Dop.damagePalette = PAL_FLAG(PAL_CC_CURSE_EFFECT);
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 23), 0);
        } else if (damage->effects & EFFECT_SOLID_FROM_BELOW) {
            g_Dop.timers[ALU_T_POISON] = 0x400;
            g_Dop.damagePalette = PAL_FLAG(PAL_CC_DARK_EFFECT);
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 22), 0);
        } else if (damage->effects & EFFECT_UNK_4000) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_45, 0), 0);
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x46), 0);
            g_Dop.timers[ALU_T_HITEFFECT] = 0x18;
            g_Dop.damagePalette = PAL_FLAG(0x202);
        } else if (damage->effects & EFFECT_UNK_2000) {
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_HIT_BY_ICE, 0), 0);
            g_Dop.timers[ALU_T_HITEFFECT] = 0xC;
            g_Dop.damagePalette = PAL_FLAG(PAL_CC_BLUE_EFFECT_A);
            DOPPLEGANGER.ext.player.anim = 0x2E;
        } else if (damage->effects & EFFECT_UNK_1000) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_114, 0), 0);
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x63), 0);
            g_Dop.timers[ALU_T_HITEFFECT] = 8;
            g_Dop.damagePalette = PAL_FLAG(PAL_CC_DARK_EFFECT);
        } else if (damage->effects & EFFECT_UNK_0800) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_113, 0), 0);
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x62), 0);
            g_Dop.timers[ALU_T_HITEFFECT] = 16;
            g_Dop.damagePalette = PAL_FLAG(PAL_CC_DARK_EFFECT);
        } else if (!(damage->effects &
                     (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                      EFFECT_UNK_1000 | EFFECT_UNK_0800 | EFFECT_UNK_0200 |
                      EFFECT_SOLID_FROM_BELOW | EFFECT_SOLID_FROM_ABOVE))) {
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x58), 0);
        }
        break;
    case 1:
        if ((func_us_801C6040(0x20280) == 0) && (DOPPLEGANGER.poseTimer < 0)) {
            SetDopplegangerAnim(0x1C);
            DOPPLEGANGER.facingLeft = (DOPPLEGANGER.facingLeft + 1) & 1;
            return;
        }
        break;
    case 8:
        DOPPLEGANGER.palette = PAL_FLAG(0x200);
        // fallthrough
    case 6:
    case 7:
        DecelerateX(FIX(1.0 / 8));
        if (!(g_Dop.vram_flag & TOUCHING_GROUND)) {
            func_us_801C59DC();
        }
        if (DOPPLEGANGER.poseTimer < 0) {
            if (DOPPLEGANGER.step_s == 6) {
                func_8010E570(0);
                return;
            }
            func_8010E470(0, DOPPLEGANGER.velocityX);
        }
        break;
    }
}
#endif

extern s32 D_us_801805A0;
static s32 D_us_801D3D30;
static s32 D_us_801D3D34;
static s32 D_us_801D3D38;
static s32 D_us_801D3D3C;
extern u_long D_us_801D421C[];
extern RECT D_us_80181FD8;

void func_80118C28(s32 arg0);

void DopplegangerStepKill(DamageParam* damage, s16 dopStep, s16 arg2) {
    s32 i;
    s32 j;
    Entity* ent;
    u8* s2;
    u8* data;
    PlayerDraw* plDraw;

    DOPPLEGANGER.drawFlags = DRAW_COLORS;
    plDraw = &g_PlayerDraw[8];

    switch (DOPPLEGANGER.step_s) {
    case 0:
        DOPPLEGANGER.velocityY = 0;
        DOPPLEGANGER.velocityX = 0;
        if (dopStep == Dop_StatusStone) {
            ent = &DOPPLEGANGER + 16;
            for (j = 16; j < 64; j++, ent++) {
                // Entity 32 appears to be EntityPlayerDissolves
                if (ent->entityId == 32) {
                    g_api.PlaySfx(SFX_VO_DOP_DEATH);
                    DOPPLEGANGER.step_s = 16;
                    return;
                }
            }
        }
        g_api.PlaySfx(SFX_VO_DOP_DEATH);
        func_us_801C72BC();
        func_us_801C7340();
        DOPPLEGANGER.velocityY = FIX(-3.25);
        DopSetVelocity(FIX(-1.25));
        DOPPLEGANGER.ext.player.anim = 0xC0;
        DOPPLEGANGER.rotate = 0;
        DOPPLEGANGER.rotPivotY = 0;
        DOPPLEGANGER.rotPivotX = 0;
        if (damage->effects & ELEMENT_FIRE) {
            func_80118C28(3);
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x4F), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_51, 2), 0);
            D_us_801D3D38 = 1;
        } else if (damage->effects & ELEMENT_THUNDER) {
            func_80118C28(9);
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x59), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_45, 1), 0);
            D_us_801D3D38 = 2;
        } else if (damage->effects & ELEMENT_ICE) {
            func_80118C28(10);
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x5A), 0);
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_HIT_BY_ICE, 0), 0);
            D_us_801D3D38 = 3;
            DOPPLEGANGER.blendMode = BLEND_TRANSP | BLEND_ADD;
        } else {
            func_80118C28(1);
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x53), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_49, 5), 0);
            D_us_801D3D38 = 0;
        }
        plDraw->r0 = plDraw->g0 = plDraw->b0 = plDraw->r1 = plDraw->g1 =
            plDraw->b1 = plDraw->r2 = plDraw->g2 = plDraw->b2 = plDraw->r3 =
                plDraw->g3 = plDraw->b3 = 128;
        plDraw->enableColorBlend = 1;
        DOPPLEGANGER.step_s++;
        break;
    case 1:
        if (D_us_801D3D38 == 0) {
            if (plDraw->r0 < 248) {
                plDraw->r0++;
            }
            if (plDraw->b0 > 8) {
                plDraw->b0--;
            }

            plDraw->r3 = plDraw->r2 = plDraw->r1 = plDraw->r0;
            plDraw->g0 = plDraw->g1 = plDraw->b1 = plDraw->g2 = plDraw->b2 =
                plDraw->g3 = plDraw->b3 = plDraw->b0;
        }
        if (D_us_801D3D38 == 1 || D_us_801D3D38 == 2) {
            if (plDraw->b0 > 8) {
                plDraw->b0--;
            }
            plDraw->r3 = plDraw->r2 = plDraw->r1 = plDraw->r0 = plDraw->g0 =
                plDraw->g1 = plDraw->b1 = plDraw->g2 = plDraw->b2 = plDraw->g3 =
                    plDraw->b3 = plDraw->b0;
        }
        if (D_us_801D3D38 == 3) {
            if (plDraw->r0 < 248) {
                plDraw->r0--;
            }
            plDraw->r3 = plDraw->r2 = plDraw->r1 = plDraw->g3 = plDraw->g2 =
                plDraw->g1 = plDraw->g0 = plDraw->r0;
            if (plDraw->b0 < 248) {
                plDraw->b0++;
            }
            plDraw->b3 = plDraw->b2 = plDraw->b1 = plDraw->b0;
        }
        DOPPLEGANGER.velocityY += FIX(11.0 / 128);
        if (DOPPLEGANGER.velocityY > FIX(1.0 / 4)) {
            DOPPLEGANGER.velocityY = FIX(1.0 / 16);
        }
        if (DOPPLEGANGER.poseTimer < 0) {
            StoreImage(&D_us_80181FD8, (u_long*)&D_us_801D421C);
            D_us_801D3D30 = 0;
            D_us_801D3D34 = 0x40;
            g_CurrentEntity->step_s++;
        }
        break;
    case 2:
        for (i = 0; i < 4; i++) {
            s2 = data = (u8*)D_us_801D421C;
            s2 += ((D_us_801D3D30 >> 1) & 7);
            s2 += ((D_us_801D3D30 & 0xFF) >> 4) << 5;
            for (j = 0; j < 16; j++) {
                if (D_us_801D3D30 & 1) {
                    *(s2 + ((j & 3) * 8) + ((j >> 2) * 0x200)) &= 0xF0;
                } else {
                    *(s2 + ((j & 3) * 8) + ((j >> 2) * 0x200)) &= 0x0F;
                }
            }
            D_us_801D3D30 += 0x23;
            D_us_801D3D30 &= 0xFF;
        }
        LoadImage(&D_us_80181FD8, (u_long*)data);
        if (--D_us_801D3D34 == 0) {
            DOPPLEGANGER.velocityY = 0;
            plDraw->enableColorBlend = 0;
            g_CurrentEntity->step_s = 0x80;
        }
        break;
    case 16:
        D_us_801D3D3C = 0x50;
        DOPPLEGANGER.step_s++;
        break;
    case 17:
        g_Dop.unk5E = 5;
        if (D_us_801D3D3C % 16 == 7) {
            g_Dop.padTapped = PAD_UP;
            g_api.PlaySfx(SFX_STONE_MOVE_B);
        }
        if (--D_us_801D3D3C == 0) {
            SetDopplegangerAnim(0x3E);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_16, 3), 0);
            DOPPLEGANGER.step_s++;
        }
        break;
    case 18:
        if (DOPPLEGANGER.poseTimer < 0) {
            plDraw->enableColorBlend = 0;
            g_CurrentEntity->step_s = 0x80;
        }
        break;
    case 0x80:
        D_us_801805A0 |= 4;
        break;
    }
    DecelerateX(FIX(1.0 / 64));
    if (DOPPLEGANGER.pose >= 15) {
        if ((DOPPLEGANGER.pose == 22) && (DOPPLEGANGER.poseTimer == 1)) {
            DOPPLEGANGER.rotate -= 0x100;
        }
        DOPPLEGANGER.rotate -= 6;
        if (DOPPLEGANGER.rotate < -0x280) {
            DOPPLEGANGER.rotate = -0x280;
        }
    }
}

extern AnimationFrame D_us_80183B0C[];

s32 BatFormFinished(void) {
    if (DOPPLEGANGER.step_s == 0) {
        return false;
    }
    if (g_Dop.padTapped & PAD_R1) {
        SetDopplegangerStep(10);
        SetDopplegangerAnim(202);
        D_us_80183B0C[0].pose = 6;
        DOPPLEGANGER.palette = PAL_FLAG(0x20D);
        g_Dop.unk66 = 0;
        g_Dop.unk68 = 0;
        CreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x21), 0);
        DOPPLEGANGER.velocityY >>= 1;
        return true;
    }
    return false;
}

void func_8011690C(s16 arg0) {
    if (DOPPLEGANGER.rotate < arg0) {
        DOPPLEGANGER.rotate += 16;
        if (DOPPLEGANGER.rotate > arg0) {
            DOPPLEGANGER.rotate = arg0;
        }
    }
    if (DOPPLEGANGER.rotate > arg0) {
        DOPPLEGANGER.rotate -= 16;
        if (DOPPLEGANGER.rotate < arg0) {
            DOPPLEGANGER.rotate = arg0;
        }
    }
}

static s32 CheckWingSmashInput(void) {
    // n.b.! Dop40 checks for padPressed
    if (g_Dop.padTapped & PAD_SQUARE) {
        return true;
    }
    return false;
}

s32 g_WingSmashTimer;
extern s32 D_us_801D4A1C;

#ifdef VERSION_PSP
INCLUDE_ASM("boss/bo4/nonmatchings/unk_465F0", ControlBatForm);
#else
void ControlBatForm(void) {
    Entity* newEntity;
    s32 pressingCross;
    s16 x_offset;
    u32 directionsPressed;

    if (BatFormFinished()) {
        return;
    }

    directionsPressed =
        g_Dop.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    pressingCross = g_Dop.padPressed & PAD_CROSS;
    DOPPLEGANGER.drawFlags = ENTITY_ROTATE;
    DOPPLEGANGER.rotPivotY = 0;

    if (CheckWingSmashInput() && (DOPPLEGANGER.step_s)) {
        SetDopplegangerAnim(0xC6);
        SetSpeedX(FIX(6));
        DOPPLEGANGER.step_s = 3;
        CreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x5c), 0);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_67, 0), 0);
        g_WingSmashTimer = 0x40;
    }

    switch (DOPPLEGANGER.step_s) {
    case 0:
        DOPPLEGANGER.rotate = 0;
        g_Dop.unk44 = g_Dop.unk46 = g_Dop.unk48 = 0;
        if (g_Entities[STAGE_ENTITY_START + 16].entityId == 0x22) {
            if (g_Entities[STAGE_ENTITY_START + 16].step != 5) {
                if (g_Entities[STAGE_ENTITY_START + 16].step < 3) {
                    g_Dop.unk46 = 0;
                    g_Entities[STAGE_ENTITY_START + 16].step = 3;
                }
                return;
            } else {
                DestroyEntity(&g_Entities[STAGE_ENTITY_START + 16]);
                SetDopplegangerAnim(0xC3);
            }
        } else {
            if (g_Dop.unk66 == 0) {
                newEntity = CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x20), 0);

                func_8010FAF4();
                g_Dop.unk66++;
            }
            DecelerateX(FIX(9.0 / 512.0));
            DecelerateY(FIX(9.0 / 512.0));
            if (abs(DOPPLEGANGER.velocityY) > FIX(1.25)) {
                if (DOPPLEGANGER.velocityY > 0) {
                    DOPPLEGANGER.velocityY = FIX(1.25);
                } else {
                    DOPPLEGANGER.velocityY = FIX(-1.25);
                }
            }
            SetDopplegangerAnim(0xCA);
            D_us_80183B0C[0].pose = DOPPLEGANGER.animCurFrame;
            DOPPLEGANGER.palette = PAL_FLAG(0x20D);
            if (g_Dop.unk66 == 1) {
                return;
            }
            if (g_Dop.unk66 == 2) {
                DOPPLEGANGER.animSet = ANIMSET_OVL(2);
                D_us_80183B0C[0].pose = 6;
                return;
            }
        }
        SetDopplegangerAnim(0xC3);
        DOPPLEGANGER.poseTimer = 1;
        DOPPLEGANGER.pose = 2;
        DOPPLEGANGER.palette = PAL_FLAG(0x200);
        CheckMoveDirection();
        DOPPLEGANGER.step_s++;
        break;
    case 1:
        if (directionsPressed && !pressingCross) {
            if (DOPPLEGANGER.ext.player.anim == 0xC3) {
                DOPPLEGANGER.pose /= 3;
            }
            DOPPLEGANGER.step_s++;
        } else {
            func_8011690C(0);
            DecelerateX(FIX(9.0 / 128.0));
            DecelerateY(FIX(9.0 / 128.0));
            break;
        }
    case 2:
        // If you're pressing cross, you can't move and inputs are ignored.
        if (pressingCross) {
            directionsPressed = 0;
        }
        switch (directionsPressed) {
        case 0:
        default:
            SetDopplegangerAnim(0xC3);
            DOPPLEGANGER.step_s = 1;
            break;
        case PAD_UP:
            DOPPLEGANGER.ext.player.anim = 0xC2;
            if (DOPPLEGANGER.velocityY < FIX(-1.25)) {
                DecelerateY(FIX(9.0 / 128.0));
            } else {
                DOPPLEGANGER.velocityY = FIX(-1.25);
            }
            func_8011690C(-0x80);
            DecelerateX(FIX(9.0 / 128.0));
            break;
        case PAD_DOWN:
            if (g_Dop.vram_flag & TOUCHING_GROUND) {
                DOPPLEGANGER.ext.player.anim = 0xC4;
            } else {
                DOPPLEGANGER.ext.player.anim = 0xC5;
            }
            if (DOPPLEGANGER.velocityY > FIX(1.25)) {
                DecelerateY(FIX(9.0 / 128.0));
            } else {
                DOPPLEGANGER.velocityY = FIX(1.25);
            }
            func_8011690C(0);
            DecelerateX(FIX(9.0 / 128.0));
            break;
        case PAD_RIGHT:
            DOPPLEGANGER.ext.player.anim = 0xC2;
            DOPPLEGANGER.facingLeft = 0;
            func_8011690C(0x180);
            if (DOPPLEGANGER.velocityX > FIX(1.25)) {
                DecelerateX(FIX(9.0 / 128.0));
            } else {
                DOPPLEGANGER.velocityX = FIX(1.25);
            }
            DecelerateY(FIX(9.0 / 128.0));
            break;
        case PAD_LEFT:
            DOPPLEGANGER.ext.player.anim = 0xC2;
            DOPPLEGANGER.facingLeft = 1;
            func_8011690C(0x180);
            if (DOPPLEGANGER.velocityX < FIX(-1.25)) {
                DecelerateX(FIX(9.0 / 128.0));
            } else {
                DOPPLEGANGER.velocityX = FIX(-1.25);
            }
            DecelerateY(FIX(9.0 / 128.0));

            break;
        case PAD_RIGHT | PAD_UP:
            DOPPLEGANGER.ext.player.anim = 0xC2;
            DOPPLEGANGER.facingLeft = 0;
            func_8011690C(0x80);
            if (DOPPLEGANGER.velocityX > FIX(0.875)) {
                DecelerateX(FIX(3.0 / 64.0));
            } else {
                DOPPLEGANGER.velocityX = FIX(0.875);
            }
            if (DOPPLEGANGER.velocityY < FIX(-0.875)) {
                DecelerateY(FIX(3.0 / 64.0));
            } else {
                DOPPLEGANGER.velocityY = FIX(-0.875);
            }
            break;
        case PAD_LEFT | PAD_UP:
            DOPPLEGANGER.ext.player.anim = 0xC2;
            DOPPLEGANGER.facingLeft = 1;
            func_8011690C(0x80);
            if (DOPPLEGANGER.velocityX < FIX(-0.875)) {
                DecelerateX(FIX(3.0 / 64.0));
            } else {
                DOPPLEGANGER.velocityX = FIX(-0.875);
            }
            if (DOPPLEGANGER.velocityY < FIX(-0.875)) {
                DecelerateY(FIX(3.0 / 64.0));
            } else {
                DOPPLEGANGER.velocityY = FIX(-0.875);
            }
            break;
        case PAD_RIGHT | PAD_DOWN:
            if (g_Dop.vram_flag & TOUCHING_GROUND) {
                DOPPLEGANGER.ext.player.anim = 0xC4;
            } else {
                DOPPLEGANGER.ext.player.anim = 0xC5;
            }
            DOPPLEGANGER.facingLeft = 0;
            func_8011690C(0);
            if (DOPPLEGANGER.velocityX > FIX(0.875)) {
                DecelerateX(FIX(3.0 / 64.0));
            } else {
                DOPPLEGANGER.velocityX = FIX(0.875);
            }
            if (DOPPLEGANGER.velocityY > FIX(1.75)) {
                DecelerateY(FIX(3.0 / 64.0));
            } else {
                DOPPLEGANGER.velocityY = FIX(1.75);
            }
            break;
        case PAD_LEFT | PAD_DOWN:
            if (g_Dop.vram_flag & TOUCHING_GROUND) {
                DOPPLEGANGER.ext.player.anim = 0xC4;
            } else {
                DOPPLEGANGER.ext.player.anim = 0xC5;
            }
            DOPPLEGANGER.facingLeft = 1;
            func_8011690C(0);
            if (DOPPLEGANGER.velocityX < FIX(-0.875)) {
                DecelerateX(FIX(3.0 / 64.0));
            } else {
                DOPPLEGANGER.velocityX = FIX(-0.875);
            }
            if (DOPPLEGANGER.velocityY > FIX(1.75)) {
                DecelerateY(FIX(3.0 / 64.0));
            } else {
                DOPPLEGANGER.velocityY = FIX(1.75);
            }
            break;
        }
        break;
    case 3:
        if (!DOPPLEGANGER.facingLeft && (g_Dop.vram_flag & TOUCHING_R_WALL) ||
            DOPPLEGANGER.facingLeft && (g_Dop.vram_flag & TOUCHING_L_WALL)) {
            g_Dop.padTapped = PAD_R1;
            BatFormFinished();
            g_api.ShakeCamera(SHAKE_X_MEDIUM);
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            DOPPLEGANGER.velocityX = 0;
            g_Dop.demo_timer = 32;
            g_Dop.padSim = 0;
            break;
        }
        // When wing smash ends, force an un-transform
        if (--g_WingSmashTimer == 0) {
            g_Dop.padTapped = PAD_R1;
            BatFormFinished();
            g_Dop.demo_timer = 32;
            g_Dop.padSim = 0;
        } else {
            if (directionsPressed & PAD_UP) {
                DOPPLEGANGER.velocityY -= FIX(0.125);
                func_8011690C(0x80);
            }
            if (directionsPressed & PAD_DOWN) {
                DOPPLEGANGER.velocityY += FIX(0.125);
            }
            if (!(directionsPressed & PAD_UP)) {
                func_8011690C(0x180);
            }
            if (!(directionsPressed & (PAD_DOWN | PAD_UP))) {
                DecelerateY(FIX(1.0 / 8.0));
            }
            if (g_Dop.vram_flag & TOUCHING_CEILING_SLOPE) {
                if (DOPPLEGANGER.facingLeft &&
                        (g_Dop.vram_flag & VRAM_FLAG_UNK400) ||
                    !DOPPLEGANGER.facingLeft &&
                        !(g_Dop.vram_flag & VRAM_FLAG_UNK400)) {
                    DOPPLEGANGER.velocityY = FIX(6);
                }
            }
            if (g_Dop.vram_flag & TOUCHING_ANY_SLOPE) {
                if (DOPPLEGANGER.facingLeft &&
                        (g_Dop.vram_flag & TOUCHING_RAISING_SLOPE) ||
                    !DOPPLEGANGER.facingLeft &&
                        !(g_Dop.vram_flag & TOUCHING_RAISING_SLOPE)) {
                    DOPPLEGANGER.velocityY = FIX(-6);
                }
            }
            if (DOPPLEGANGER.velocityY < FIX(-6)) {
                DOPPLEGANGER.velocityY = FIX(-6);
            }
            if (DOPPLEGANGER.velocityY > FIX(6)) {
                DOPPLEGANGER.velocityY = FIX(6);
            }
            if (g_GameTimer % 3 == 0) {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_WING_SMASH_TRAIL, 0), 0);
                if (g_Dop.vram_flag & TOUCHING_GROUND) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(BP_69, 9), 0);
                }
                if (g_Dop.vram_flag & TOUCHING_CEILING) {
                    x_offset = 3;
                    if (DOPPLEGANGER.facingLeft) {
                        x_offset = -x_offset;
                    }
                    DOPPLEGANGER.posY.i.hi -= 8;
                    DOPPLEGANGER.posX.i.hi += x_offset;
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(BP_4, 1), 0);
                    DOPPLEGANGER.posY.i.hi += 8;
                    DOPPLEGANGER.posX.i.hi -= x_offset;
                }
            }
        }
        break;
    }

    if (D_us_801D4A1C != 0) {
        if (DOPPLEGANGER.velocityX > 0) {
            DOPPLEGANGER.velocityX = 0;
        }
    }
    if (D_us_801D4A1C != 0) {
        if (D_us_801D4A1C > 0) {
            D_us_801D4A1C--;
            g_CurrentEntity->posY.i.hi++;
        } else {
            D_us_801D4A1C++;
            g_CurrentEntity->posY.i.hi--;
        }
    }
}
#endif

extern s16 g_DopSensorsCeilingDefault[];
extern s16 g_DopSensorsFloorDefault[];
extern Point16 g_DopSensorsCeiling[];
extern Point16 g_DopSensorsFloor[];

void DopplegangerStepUnmorphBat(void) {
    s32 i;
    s32 count;
    u8 _pad[40]; // must be between 33 & 40

    DOPPLEGANGER.drawFlags = ENTITY_ROTATE;
    DecelerateX(FIX(1.0 / 8.0));
    if (g_Dop.vram_flag & (TOUCHING_CEILING | TOUCHING_GROUND)) {
        DOPPLEGANGER.velocityY = 0;
    }
    DecelerateY(FIX(1.0 / 8.0));
    func_8011690C(0);
    count = 0;

    switch (DOPPLEGANGER.step_s) {
    case 0:
        for (i = 0; i < 4; i++) {
            if (g_DopSensorsFloor[i].y < g_DopSensorsFloorDefault[i]) {
                g_DopSensorsFloor[i].y++;
            } else {
                count++;
            }

            if (g_DopSensorsCeiling[i].y > g_DopSensorsCeilingDefault[i]) {
                g_DopSensorsCeiling[i].y--;
            } else {
                count++;
            }

            if (i == 0 && (g_Dop.vram_flag & TOUCHING_ANY_SLOPE)) {
                DOPPLEGANGER.posY.i.hi--;
            }
        }

        if (count == 8) {
            DOPPLEGANGER.animSet = ANIMSET_OVL(1);
            DOPPLEGANGER.drawFlags = ENTITY_DEFAULT;
            DOPPLEGANGER.rotate = 0;
            g_Dop.unk66 = 1;
            DOPPLEGANGER.step_s = 1;
            D_us_80183B0C[0].pose = 0x5F;
        }
        break;

    case 1:
        if (g_Dop.unk66 == 3) {
            func_us_801C58E4();
            if (!(g_Dop.vram_flag & TOUCHING_ANY_SLOPE)) {
                DOPPLEGANGER.velocityY = FIX(-1);
            }
            DOPPLEGANGER.palette = PAL_FLAG(0x200);
            func_80111CC0();
        }
        break;
    }
}

s32 func_us_801C8EE4(void) {
    if (DOPPLEGANGER.step_s == 0) {
        return false;
    }
    if (g_Dop.padTapped & PAD_R2) {
        CheckMoveDirection();
        SetDopplegangerStep(15);
        return true;
    }
    return false;
}

void ControlMistForm(void) {
    u32 padDirection;

    if (func_us_801C8EE4() == 0) {
        padDirection = g_Dop.padPressed & PAD_DIRECTION_MASK;
        switch (DOPPLEGANGER.step_s) {
        case 0:
            CheckMoveDirection();
            g_Dop.unk44 = g_Dop.unk46 = g_Dop.unk48 = 0;
            g_api.func_800EA5E4(ANIMSET_OVL(3));
            func_8010FAF4();
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_73, 0), 0);
            if (DOPPLEGANGER.velocityX > 0) {
                DOPPLEGANGER.velocityX = FIX(1);
            }
            if (DOPPLEGANGER.velocityX < 0) {
                DOPPLEGANGER.velocityX = FIX(-1);
            }
            if (DOPPLEGANGER.velocityY > 0) {
                DOPPLEGANGER.velocityY = FIX(1);
            }
            if (DOPPLEGANGER.velocityY < 0) {
                DOPPLEGANGER.velocityY = FIX(-1);
            }
            SetDopplegangerAnim(0xCA);
            D_us_80183B0C[0].pose = DOPPLEGANGER.animCurFrame;
            g_api.func_800EA538(5);
            g_api.func_800EA5E4(0x8801U);
            DOPPLEGANGER.step_s++;
            break;

        case 1:
            switch (padDirection) {
            case PAD_NONE:
            default:
                DecelerateX(FIX(3.0 / 256.0));
                DecelerateY(FIX(3.0 / 256.0));
                break;
            case PAD_UP:
                if (DOPPLEGANGER.velocityY < FIX(-1.0)) {
                    DecelerateY(FIX(3.0 / 256.0));
                } else {
                    DOPPLEGANGER.velocityY = FIX(-1.0);
                }
                DecelerateX(FIX(3.0 / 256.0));
                break;
            case PAD_DOWN:
                if (DOPPLEGANGER.velocityY > FIX(1.0)) {
                    DecelerateY(FIX(3.0 / 256.0));
                } else {
                    DOPPLEGANGER.velocityY = FIX(1.0);
                }
                DecelerateX(FIX(3.0 / 256.0));
                break;
            case PAD_RIGHT:
                DOPPLEGANGER.facingLeft = false;
                if (DOPPLEGANGER.velocityX > FIX(1.0)) {
                    DecelerateX(FIX(3.0 / 256.0));
                } else {
                    DOPPLEGANGER.velocityX = FIX(1.0);
                }
                DecelerateY(FIX(3.0 / 256.0));
                break;
            case PAD_LEFT:
                DOPPLEGANGER.facingLeft = true;
                if (DOPPLEGANGER.velocityX < FIX(-1.0)) {
                    DecelerateX(FIX(3.0 / 256.0));
                } else {
                    DOPPLEGANGER.velocityX = FIX(-1.0);
                }
                DecelerateY(FIX(3.0 / 256.0));
                break;

            case (PAD_UP | PAD_RIGHT):
                DOPPLEGANGER.facingLeft = false;
                if (DOPPLEGANGER.velocityX > FIX(0.625)) {
                    DecelerateX(FIX(1.0 / 128.0));
                } else {
                    DOPPLEGANGER.velocityX = FIX(0.625);
                }

                if (DOPPLEGANGER.velocityY < FIX(-0.625)) {
                    DecelerateY(FIX(1.0 / 128.0));
                } else {
                    DOPPLEGANGER.velocityY = FIX(-0.625);
                }
                break;
            case (PAD_UP | PAD_LEFT):
                DOPPLEGANGER.facingLeft = true;
                if (DOPPLEGANGER.velocityX < FIX(-0.625)) {
                    DecelerateX(FIX(1.0 / 128.0));
                } else {
                    DOPPLEGANGER.velocityX = FIX(-0.625);
                }

                if (DOPPLEGANGER.velocityY < FIX(-0.625)) {
                    DecelerateY(FIX(1.0 / 128.0));
                } else {
                    DOPPLEGANGER.velocityY = FIX(-0.625);
                }
                break;

            case (PAD_DOWN | PAD_RIGHT):
                DOPPLEGANGER.facingLeft = false;
                if (DOPPLEGANGER.velocityX > FIX(0.625)) {
                    DecelerateX(FIX(1.0 / 128.0));
                } else {
                    DOPPLEGANGER.velocityX = FIX(0.625);
                }
                if (DOPPLEGANGER.velocityY > FIX(0.625)) {
                    DecelerateY(FIX(1.0 / 128.0));
                } else {
                    DOPPLEGANGER.velocityY = FIX(0.625);
                }
                break;
            case (PAD_DOWN | PAD_LEFT):
                DOPPLEGANGER.facingLeft = 1;
                if (DOPPLEGANGER.velocityX < FIX(-0.625)) {
                    DecelerateX(FIX(1.0 / 128.0));
                } else {
                    DOPPLEGANGER.velocityX = FIX(-0.625);
                }

                if (DOPPLEGANGER.velocityY > FIX(0.625)) {
                    DecelerateY(FIX(1.0 / 128.0));
                } else {
                    DOPPLEGANGER.velocityY = FIX(0.625);
                }
                break;
            }
            break;

        default:
            FntPrint("error step\n");
            break;
        }

        if (D_us_801D4A1C != 0) {
            if (D_us_801D4A1C > 0) {
                D_us_801D4A1C--;
                DOPPLEGANGER.posY.i.hi++;
            } else {
                D_us_801D4A1C++;
                DOPPLEGANGER.posY.i.hi--;
            }
        }
    }
}

void DopplegangerStepUnmorphMist(void) {
    s32 i;
    u8 _pad[40];
    s32 count;

    if ((g_Dop.vram_flag & TOUCHING_GROUND) && DOPPLEGANGER.velocityY > 0) {
        DOPPLEGANGER.velocityY = 0;
    }
    if ((g_Dop.vram_flag & TOUCHING_CEILING) && DOPPLEGANGER.velocityY < 0) {
        DOPPLEGANGER.velocityY = 0;
    }

    DecelerateX(FIX(1.0 / 128.0));
    DecelerateY(FIX(1.0 / 128.0));
    count = 0;

    for (i = 0; i < 4; i++) {

        if (g_DopSensorsFloor[i].y < g_DopSensorsFloorDefault[i]) {
            g_DopSensorsFloor[i].y++;
        } else {
            count++;
        }
        if (g_DopSensorsCeiling[i].y > g_DopSensorsCeilingDefault[i]) {
            g_DopSensorsCeiling[i].y--;
        } else {
            count++;
        }
        if (i == 0 && (g_Dop.vram_flag & TOUCHING_ANY_SLOPE)) {
            DOPPLEGANGER.posY.i.hi--;
        }
    }

    if (count == 8) {
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        SetDopplegangerAnim(0xCB);
        if (DOPPLEGANGER.step_s) {
            SetDopplegangerAnim(0xCC);
        }

        if (g_Entities[E_ID_50].step < 3) {
            g_Entities[E_ID_50].step = 3;
            return;
        }
        if (g_Entities[E_ID_50].step == 5) {
            DOPPLEGANGER.palette = PAL_FLAG(0x200);
            func_8010FAF4();
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x5B), 0);
            func_us_801C58E4();
            if (!(g_Dop.vram_flag & TOUCHING_ANY_SLOPE)) {
                DOPPLEGANGER.velocityY = FIX(-1);
            }
            func_80111CC0();
        }
    }
}

static s32 D_us_801D3D44;

void DopplegangerStepSwordWarp(void) {
    if (DOPPLEGANGER.step_s == 0) {
        if (g_Entities[E_BOSS_WEAPON].entityId == E_NONE) {
            D_us_801D3D44 = 0x10;
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_61, 0x15), 0);
            DOPPLEGANGER.step_s++;
        }
    } else if (--D_us_801D3D44 == 0) {
        DOPPLEGANGER.palette = PAL_FLAG(0x200);
        func_8010E570(0);
    }
}

// rotation angles
static s16 D_us_8018134C[] = {
    0x0000, 0x0000, 0x0100, 0x0000, 0xFF00, 0x0000, 0x0100, 0x0000,
    0xFF00, 0xFE00, 0xFF00, 0x0000, 0x0100, 0x0200, 0x0100, 0x0000,
};
static s32 D_us_801D3D48;

void DopplegangerStepStone(s32 arg0) {
    switch (DOPPLEGANGER.step_s) {
    case 0:
        func_us_801C72BC();
        func_us_801C7340();
        DOPPLEGANGER.velocityY = FIX(-4);
        DopSetVelocity(FIX(-0.625));
        func_801133E68();
        DOPPLEGANGER.palette = PAL_FLAG(PAL_CC_STONE_EFFECT);
        // This unique pain grunt doesn't have an Alucard equivalent
        g_api.PlaySfx(SFX_VO_DOP_PAIN_F);
        g_Dop.timers[ALU_T_HITEFFECT] = 0;
        g_Dop.unk5E = 8;
        DOPPLEGANGER.step_s = 1;
        break;

    case 1:
        func_us_801C5430(1, 4);
        DOPPLEGANGER.palette = PAL_FLAG(PAL_CC_STONE_EFFECT);
        if (func_us_801C6040(0x20280) != 0) {
            DOPPLEGANGER.step = Dop_StatusStone;
            DOPPLEGANGER.velocityX = DOPPLEGANGER.velocityY = 0;
            g_api.ShakeCamera(SHAKE_Y_SMALL);
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_39, 0), 0);
            if (g_Dop.unk6A <= 0) {
                D_us_801D3D48 = 0x20;
            }
            DOPPLEGANGER.palette = PAL_FLAG(PAL_UNK_19E);
            SetDopplegangerAnim(0x38);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_16, 3), 0);
            DOPPLEGANGER.step_s = 2;
        }
        break;

    case 2:
        if (g_Dop.unk6A <= 0) {
            if (--D_us_801D3D48 == 0) {
                DOPPLEGANGER.step = Dop_Kill;
                g_api.PlaySfx(SFX_VO_DOP_DEATH);
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_16, 3), 0);
                DOPPLEGANGER.step_s = 16;
            }
            func_us_801C5430(1, 4);
            break;
        }

        if ((g_Dop.padTapped & PAD_DIRECTION_MASK) || arg0 != 0) {
            g_Dop.padTapped |= PAD_DIRECTION_MASK;
            g_Dop.unk5E--;
            DOPPLEGANGER.poseTimer = 16;
            g_api.PlaySfx(SFX_STONE_MOVE_B);

            if (g_Dop.unk5E == 0) {
                SetDopplegangerAnim(0x3B);
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_16, 3), 0);
                g_api.PlaySfx(SFX_VO_DOP_YELL);
                DOPPLEGANGER.step = Dop_Hit;
                DOPPLEGANGER.step_s = 8;
                DOPPLEGANGER.palette = PAL_FLAG(0x200);
                break;
            }
            func_us_801C5430(1, 4);
            DOPPLEGANGER.step_s = 3;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_13, 3), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_31, 3), 0);
        }
        DOPPLEGANGER.palette = PAL_FLAG(PAL_UNK_19E);
        break;

    case 3:
        if (DOPPLEGANGER.poseTimer < 0) {
            DOPPLEGANGER.step_s = 2;
            DOPPLEGANGER.drawFlags &=
                ENTITY_BLINK | ENTITY_MASK_B | ENTITY_MASK_G | ENTITY_MASK_R |
                ENTITY_OPACITY | ENTITY_SCALEY | ENTITY_SCALEX;
        } else {
            DOPPLEGANGER.rotPivotX = 0;
            DOPPLEGANGER.drawFlags |= ENTITY_ROTATE;
            DOPPLEGANGER.rotate = D_us_8018134C[DOPPLEGANGER.poseTimer] >> 0x4;
            if (DOPPLEGANGER.rotate) {
                DOPPLEGANGER.rotPivotY = 20;
            } else {
                DOPPLEGANGER.rotPivotY = 24;
            }
        }
        DOPPLEGANGER.palette = PAL_FLAG(PAL_UNK_19E);
        break;
    }
}
