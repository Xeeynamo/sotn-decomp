// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

// n.b.! this is the same as bo4/unk_46E7C.c

void func_us_801C648C(s32 arg0) {
    s32 move = DOPPLEGANGER.facingLeft != 0 ? -3 : 3;

    DOPPLEGANGER.posY.i.hi -= 22;
    DOPPLEGANGER.posX.i.hi = move + DOPPLEGANGER.posX.i.hi;
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(4, 1), 0);
    DOPPLEGANGER.posY.i.hi = DOPPLEGANGER.posY.i.hi + 22;
    DOPPLEGANGER.posX.i.hi = DOPPLEGANGER.posX.i.hi - move;

    if (arg0 & 1) {
        g_api.func_80102CD8(3);
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
    }
    if (arg0 & 2) {
        DOPPLEGANGER.velocityX = 0;
        DOPPLEGANGER.velocityY = 0;
    }
}

void SetDopplegangerAnim(u8 anim);
bool func_us_801C5650(s32 branchFlags);

extern PlayerState g_Dop;

void DopplegangerStepHighJump(void) {
    s32 temp;
    s32 var_s1;

    var_s1 = 0;
    g_Dop.unk4A++;
    if (func_us_801C5650(2) != 0) {
        return;
    }

    switch (DOPPLEGANGER.step_s) {
    case 0:
        if (g_Dop.vram_flag & 2) {
            func_us_801C648C(3);
            if (g_Dop.unk4A > 4) {
                DOPPLEGANGER.step_s = 2;
                DOPPLEGANGER.rotate = 0x800;
                DOPPLEGANGER.rotPivotX = 0;
                DOPPLEGANGER.rotPivotY = 2;
                DOPPLEGANGER.drawFlags |= FLAG_DRAW_ROTATE;
                DOPPLEGANGER.facingLeft = (DOPPLEGANGER.facingLeft + 1) & 1;
                SetDopplegangerAnim(0x2B);
            } else {
                DOPPLEGANGER.step_s = 3;
            }
        } else if (g_Dop.unk4A > 28) {
            DOPPLEGANGER.step_s = 1;
            DOPPLEGANGER.velocityY = -0x60000;
            SetDopplegangerAnim(0x1B);
        }
        break;

    case 1:
        if (g_Dop.vram_flag & 2) {
            DOPPLEGANGER.step_s = 2;
            func_us_801C648C(3);
        } else {
            DOPPLEGANGER.velocityY = DOPPLEGANGER.velocityY + 0x6000;
            if (DOPPLEGANGER.velocityY > 0x8000) {
                var_s1 = 1;
            }
        }
        break;

    case 2:
        DOPPLEGANGER.drawFlags |= FLAG_DRAW_ROTATE;
        DOPPLEGANGER.rotPivotX = 0;
        DOPPLEGANGER.rotPivotY = 2;
        if (g_Dop.unk4A > 56) {
            SetDopplegangerAnim(0x2D);
            DOPPLEGANGER.rotate = 0;
            DOPPLEGANGER.step_s = 4;
            DOPPLEGANGER.drawFlags &=
                FLAG_BLINK | FLAG_DRAW_UNK40 | FLAG_DRAW_UNK20 |
                FLAG_DRAW_UNK10 | FLAG_DRAW_OPACITY | FLAG_DRAW_SCALEY |
                FLAG_DRAW_SCALEX;
            DOPPLEGANGER.facingLeft = (DOPPLEGANGER.facingLeft + 1) & 1;
        }
        break;
    case 3:
        if (g_Dop.unk4A > 20) {
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
        DOPPLEGANGER.palette = PAL_OVL(0x200);
        DOPPLEGANGER.step_s = 1;
        DOPPLEGANGER.step = Dop_Jump;
    }
}

s32 func_80113E68(void) {
    s16 rnd = rand() & PSP_RANDMASK;
    DOPPLEGANGER.ext.player.anim = 0x2E + (rnd % 3);
    return rnd % 16;
}

void func_us_801C68CC(void) {
    DOPPLEGANGER.animSet = ANIMSET_OVL(1);
    DOPPLEGANGER.drawFlags &=
        FLAG_BLINK | FLAG_DRAW_UNK40 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK10 |
        FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
    DOPPLEGANGER.poseTimer = 0;
    DOPPLEGANGER.pose = 0;
    DOPPLEGANGER.drawMode = DRAW_DEFAULT;
    g_Dop.unk44 = 0;
    g_Dop.unk46 = 0;
    DOPPLEGANGER.rotate = 0;
    if (g_Entities[STAGE_ENTITY_START + 16].entityId == E_MIST) {
        func_8010FAF4();
    }
}

void func_us_801C6950(void) {
    if (DOPPLEGANGER.posX.i.hi <= PLAYER.posX.i.hi) {
        DOPPLEGANGER.entityRoomIndex = 0;
        return;
    }
    DOPPLEGANGER.entityRoomIndex = 1;
}

extern s16 D_us_801813C8[];

void DopplegangerHandleDamage(DamageParam* damage, s16 step, s16 step_s) {
    s32 sfxIndex;

    switch (DOPPLEGANGER.step_s) {
    case 0:
        sfxIndex = 0;
        func_us_801C68CC();
        func_us_801C6950();
        switch (damage->damageKind) {
        case 3:
            sfxIndex = (rand() & 1) + 3;
            DOPPLEGANGER.velocityY = FIX(-4);
            func_8010E3B8(FIX(-5.0 / 6));
            DOPPLEGANGER.step_s = 1;
            if (func_80113E68() == 0) {
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
                func_8010E3B8(FIX(-5.0 / 3));
                DOPPLEGANGER.step_s = 6;

                DOPPLEGANGER.ext.player.anim = 0x31;
                if (DOPPLEGANGER.entityRoomIndex != DOPPLEGANGER.facingLeft) {
                    DOPPLEGANGER.ext.player.anim = 0x33;
                }

                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 6), 0);
                break;
            case 2:
                DOPPLEGANGER.velocityY = 0;
                func_8010E3B8(FIX(-1.25));
                DOPPLEGANGER.step_s = 7;
                DOPPLEGANGER.ext.player.anim = 0x23;
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
                break;
            default:
            case 3:
            case 4:
                DOPPLEGANGER.velocityY = FIX(-2);
                func_8010E3B8(FIX(-1.25));
                DOPPLEGANGER.step_s = 1;
                func_80113E68();
                break;
            }
            break;
        default:
            FntPrint("dam_kind:%04x\n", damage->damageKind);
            break;
        }

        g_Dop.unk40 = 0x8166;
        g_Dop.timers[2] = 6;
        g_api.PlaySfx(D_us_801813C8[sfxIndex]);

        if (damage->effects & EFFECT_UNK_8000) {
            g_api.PlaySfx(SFX_FM_EXPLODE_SWISHES);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x2C, 0x45), 0);
            g_Dop.unk40 = 0x8160;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(17, 1), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(18, 0), 0);
            g_Dop.timers[2] = 0x10;
        } else if (damage->effects & EFFECT_UNK_0100) {
            g_Dop.timers[1] = 0x400;
            g_Dop.unk40 = 0x8165;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x2C, 23), 0);
        } else if (damage->effects & EFFECT_SOLID_FROM_BELOW) {
            g_Dop.timers[0] = 0x400;
            g_Dop.unk40 = 0x8164;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x2C, 22), 0);
        } else if (damage->effects & EFFECT_UNK_4000) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x2D, 0), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x2C, 0x46), 0);
            g_Dop.timers[2] = 0x18;
            g_Dop.unk40 = 0x8202;
        } else if (damage->effects & EFFECT_UNK_2000) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x2E, 0), 0);
            g_Dop.timers[2] = 0xC;
            g_Dop.unk40 = 0x8169;
            DOPPLEGANGER.ext.player.anim = 0x2E;
        } else if (damage->effects & EFFECT_UNK_1000) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x72, 0), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x2C, 0x63), 0);
            g_Dop.timers[2] = 8;
            g_Dop.unk40 = 0x8164;
        } else if (damage->effects & EFFECT_UNK_0800) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x71, 0), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x2C, 0x62), 0);
            g_Dop.timers[2] = 16;
            g_Dop.unk40 = 0x8164;
        } else if (!(damage->effects &
                     (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                      EFFECT_UNK_1000 | EFFECT_UNK_0800 | EFFECT_UNK_0200 |
                      EFFECT_SOLID_FROM_BELOW | EFFECT_SOLID_FROM_ABOVE))) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x2C, 0x58), 0);
        }
        break;
    case 1:
        if ((func_us_801C5650(0x20280) == 0) && (DOPPLEGANGER.poseTimer < 0)) {
            SetDopplegangerAnim(0x1C);
            DOPPLEGANGER.facingLeft = (DOPPLEGANGER.facingLeft + 1) & 1;
            return;
        }
        break;
    case 8:
        DOPPLEGANGER.palette = PAL_OVL(0x200);
        // fallthrough
    case 6:
    case 7:
        DecelerateX(FIX(1.0 / 8));
        if (!(g_Dop.vram_flag & 1)) {
            func_us_801C4FDC();
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

extern s32 D_us_801805B8;
extern s32 D_us_801D3308;
extern s32 D_us_801D330C;
extern s32 D_us_801D3310;
extern s32 D_us_801D3314;
extern u_long D_us_801D37EC[];
extern RECT D_us_80182064;

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
                // Entity 32 appears to be EntityDopplegangerDissolves
                if (ent->entityId == 32) {
                    g_api.PlaySfx(SFX_BO4_UNK_7E6);
                    DOPPLEGANGER.step_s = 16;
                    return;
                }
            }
        }
        g_api.PlaySfx(SFX_BO4_UNK_7E6);
        func_us_801C68CC();
        func_us_801C6950();
        DOPPLEGANGER.velocityY = FIX(-3.25);
        func_8010E3B8(FIX(-1.25));
        DOPPLEGANGER.ext.player.anim = 0xC0;
        DOPPLEGANGER.rotate = 0;
        DOPPLEGANGER.rotPivotY = 0;
        DOPPLEGANGER.rotPivotX = 0;
        if (damage->effects & ELEMENT_FIRE) {
            func_80118C28(3);
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x4F), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_51, 2), 0);
            D_us_801D3310 = 1;
        } else if (damage->effects & ELEMENT_THUNDER) {
            func_80118C28(9);
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x59), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_45, 1), 0);
            D_us_801D3310 = 2;
        } else if (damage->effects & ELEMENT_ICE) {
            func_80118C28(10);
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x5A), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, BP_HIT_BY_ICE, 0);
            D_us_801D3310 = 3;
            DOPPLEGANGER.drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        } else {
            func_80118C28(1);
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x53), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_49, 5), 0);
            D_us_801D3310 = 0;
        }
        plDraw->r0 = plDraw->g0 = plDraw->b0 = plDraw->r1 = plDraw->g1 =
            plDraw->b1 = plDraw->r2 = plDraw->g2 = plDraw->b2 = plDraw->r3 =
                plDraw->g3 = plDraw->b3 = 0x80;
        plDraw->enableColorBlend = 1;
        DOPPLEGANGER.step_s++;
        break;
    case 1:
        if (D_us_801D3310 == 0) {
            if (plDraw->r0 < 248) {
                plDraw->r0++;
            }
            if (plDraw->b0 >= 9) {
                plDraw->b0--;
            }

            plDraw->r3 = plDraw->r2 = plDraw->r1 = plDraw->r0;
            plDraw->g0 = plDraw->g1 = plDraw->b1 = plDraw->g2 = plDraw->b2 =
                plDraw->g3 = plDraw->b3 = plDraw->b0;
        }
        if (D_us_801D3310 == 1 || D_us_801D3310 == 2) {
            if (plDraw->b0 > 8) {
                plDraw->b0--;
            }
            plDraw->r3 = plDraw->r2 = plDraw->r1 = plDraw->r0 = plDraw->g0 =
                plDraw->g1 = plDraw->b1 = plDraw->g2 = plDraw->b2 = plDraw->g3 =
                    plDraw->b3 = plDraw->b0;
        }
        if (D_us_801D3310 == 3) {
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
            StoreImage(&D_us_80182064, (u_long*)&D_us_801D37EC);
            D_us_801D3308 = 0;
            D_us_801D330C = 0x40;
            g_CurrentEntity->step_s++;
        }
        break;
    case 2:
        for (i = 0; i < 4; i++) {
            s2 = data = (u8*)&D_us_801D37EC[0];
            s2 += ((D_us_801D3308 >> 1) & 7);
            s2 += ((D_us_801D3308 & 0xFF) >> 4) << 5;
            for (j = 0; j < 16; j++) {
                if (D_us_801D3308 & 1) {
                    *(s2 + ((j & 3) * 8) + ((j >> 2) * 0x200)) &= 0xF0;
                } else {
                    *(s2 + ((j & 3) * 8) + ((j >> 2) * 0x200)) &= 0x0F;
                }
            }
            D_us_801D3308 += 0x23;
            D_us_801D3308 &= 0xFF;
        }
        LoadImage(&D_us_80182064, (u_long*)data);
        if (--D_us_801D330C == 0) {
            DOPPLEGANGER.velocityY = 0;
            plDraw->enableColorBlend = 0;
            g_CurrentEntity->step_s = 0x80;
        }
        break;
    case 16:
        D_us_801D3314 = 0x50;
        DOPPLEGANGER.step_s++;
        break;
    case 17:
        g_Dop.unk5E = 5;
        if (D_us_801D3314 % 16 == 7) {
            g_Dop.padTapped = PAD_UP;
            g_api.PlaySfx(SFX_STONE_MOVE_B);
        }
        if (--D_us_801D3314 == 0) {
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
        D_us_801805B8 |= 4;
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

extern PlayerState g_Dop;
extern AnimationFrame D_us_80183B98[];

bool BatFormFinished(void) {
    if (DOPPLEGANGER.step_s == 0 || !(g_Dop.padTapped & 8)) {
        return false;
    }

    SetDopplegangerStep(10);
    SetDopplegangerAnim(202);
    D_us_80183B98[0].pose = 6;
    DOPPLEGANGER.palette = PAL_OVL(0x20D);
    g_Dop.unk66 = 0;
    g_Dop.unk68 = 0;
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(44, 0x21), 0);
    DOPPLEGANGER.velocityY >>= 1;
    return true;
}

void func_8011690C(s16 arg0) {
    if (DOPPLEGANGER.rotate < arg0) {
        DOPPLEGANGER.rotate += 16;
        if (arg0 < DOPPLEGANGER.rotate) {
            DOPPLEGANGER.rotate = arg0;
        }
    }
    if (arg0 < DOPPLEGANGER.rotate) {
        DOPPLEGANGER.rotate -= 16;
        if (DOPPLEGANGER.rotate < arg0) {
            DOPPLEGANGER.rotate = arg0;
        }
    }
}

static s32 CheckWingSmashInput(void) {
    // n.b.! Dop10 checks for padTapped
    if (g_Dop.padPressed & PAD_SQUARE) {
        return true;
    }
    return false;
}

extern s32 g_WingSmashTimer;
extern AnimationFrame D_us_80183B98[];
extern s32 D_us_801D3FEC;

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
    DOPPLEGANGER.drawFlags = FLAG_DRAW_ROTATE;
    DOPPLEGANGER.rotPivotY = 0;

    if (CheckWingSmashInput() && (DOPPLEGANGER.step_s)) {
        SetDopplegangerAnim(0xC6);
        SetSpeedX(FIX(6));
        DOPPLEGANGER.step_s = 3;
        CreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x5c), 0);
        CreateEntFactoryFromEntity(g_CurrentEntity, BP_67, 0);
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
            D_us_80183B98[0].pose = DOPPLEGANGER.animCurFrame;
            DOPPLEGANGER.palette = PAL_OVL(0x20D);
            if (g_Dop.unk66 == 1) {
                return;
            }
            if (g_Dop.unk66 == 2) {
                DOPPLEGANGER.animSet = ANIMSET_OVL(2);
                D_us_80183B98[0].pose = 6;
                return;
            }
        }
        SetDopplegangerAnim(0xC3);
        DOPPLEGANGER.poseTimer = 1;
        DOPPLEGANGER.pose = 2;
        DOPPLEGANGER.palette = PAL_OVL(0x200);
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
            if (g_Dop.vram_flag & 1) {
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
            if (g_Dop.vram_flag & 1) {
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
            if (g_Dop.vram_flag & 1) {
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
        if (!DOPPLEGANGER.facingLeft && (g_Dop.vram_flag & 4) ||
            DOPPLEGANGER.facingLeft && (g_Dop.vram_flag & 8)) {
            g_Dop.padTapped = PAD_R1;
            BatFormFinished();
            g_api.func_80102CD8(2);
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
            if (g_Dop.vram_flag & 0x800) {
                if (DOPPLEGANGER.facingLeft && (g_Dop.vram_flag & 0x400) ||
                    !DOPPLEGANGER.facingLeft && !(g_Dop.vram_flag & 0x400)) {
                    DOPPLEGANGER.velocityY = FIX(6);
                }
            }
            if (g_Dop.vram_flag & 0x8000) {
                if (DOPPLEGANGER.facingLeft && (g_Dop.vram_flag & 0x4000) ||
                    !DOPPLEGANGER.facingLeft && !(g_Dop.vram_flag & 0x4000)) {
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
                    g_CurrentEntity, BP_WING_SMASH_TRAIL, 0);
                if (g_Dop.vram_flag & 1) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(BP_69, 9), 0);
                }
                if (g_Dop.vram_flag & 2) {
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

    if (D_us_801D3FEC != 0) {
        if (DOPPLEGANGER.velocityX > 0) {
            DOPPLEGANGER.velocityX = 0;
        }
    }
    if (D_us_801D3FEC != 0) {
        if (D_us_801D3FEC > 0) {
            D_us_801D3FEC--;
            g_CurrentEntity->posY.i.hi++;
        } else {
            D_us_801D3FEC++;
            g_CurrentEntity->posY.i.hi--;
        }
    }
}

extern s16 g_DopSensorsCeilingDefault[];
extern s16 g_DopSensorsFloorDefault[];
extern Point16 g_DopSensorsCeiling[];
extern Point16 g_DopSensorsFloor[];

void DopplegangerStepUnmorphBat(void) {
    s32 i;
    s32 count;
    u8 _pad[40]; // must be between 33 & 40

    DOPPLEGANGER.drawFlags = FLAG_DRAW_ROTATE;
    DecelerateX(FIX(1.0 / 8.0));
    if (g_Dop.vram_flag & 3) {
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

            if (i == 0 && (g_Dop.vram_flag & 0x8000)) {
                DOPPLEGANGER.posY.i.hi--;
            }
        }

        if (count == 8) {
            DOPPLEGANGER.animSet = ANIMSET_OVL(1);
            DOPPLEGANGER.drawFlags = FLAG_DRAW_DEFAULT;
            DOPPLEGANGER.rotate = 0;
            g_Dop.unk66 = 1;
            DOPPLEGANGER.step_s = 1;
            D_us_80183B98[0].pose = 0x5F;
        }
        break;

    case 1:
        if (g_Dop.unk66 == 3) {
            func_us_801C4EE4();
            if (!(g_Dop.vram_flag & 0x8000)) {
                DOPPLEGANGER.velocityY = 0xFFFF0000;
            }
            DOPPLEGANGER.palette = PAL_OVL(0x200);
            func_80111CC0();
        }
        break;
    }
}

s32 func_us_801C84F4(void) {
    if ((DOPPLEGANGER.step_s == 0) || !(g_Dop.padTapped & PAD_R2)) {
        return false;
    }
    CheckMoveDirection();
    SetDopplegangerStep(15);
    return true;
}

extern s32 D_us_801D3FEC;

void ControlMistForm(void) {
    u32 padDirection;

    if (func_us_801C84F4() == 0) {
        padDirection = g_Dop.padPressed & PAD_DIRECTION_MASK;
        switch (DOPPLEGANGER.step_s) {
        case 0:
            CheckMoveDirection();
            g_Dop.unk44 = g_Dop.unk46 = g_Dop.unk48 = 0;
            g_api.func_800EA5E4(0x8003U);
            func_8010FAF4();
            CreateEntFactoryFromEntity(g_CurrentEntity, 0x49U, 0);
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
            D_us_80183B98[0].pose = DOPPLEGANGER.animCurFrame;
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

        if (D_us_801D3FEC != 0) {
            if (D_us_801D3FEC > 0) {
                D_us_801D3FEC--;
                DOPPLEGANGER.posY.i.hi++;
            } else {
                D_us_801D3FEC++;
                DOPPLEGANGER.posY.i.hi--;
            }
        }
    }
}
extern s16 g_DopSensorsCeilingDefault[];
extern s16 g_DopSensorsFloorDefault[];

void DopplegangerStepUnmorphMist(void) {
    s32 i;
    s32 count;
    u8 _pad[40];

    if ((g_Dop.vram_flag & 1) && DOPPLEGANGER.velocityY > 0) {
        DOPPLEGANGER.velocityY = 0;
    }
    if ((g_Dop.vram_flag & 2) && DOPPLEGANGER.velocityY < 0) {
        DOPPLEGANGER.velocityY = 0;
    }

    DecelerateX(FIX(1.0 / 128.0));
    DecelerateY(FIX(1.0 / 128.0));
    count = 0;

    for (i = 0; i < 4; i++) {

        if (g_DopSensorsFloor[i].y < g_DopSensorsFloorDefault[i]) {
            g_DopSensorsFloor[i].y++;
        } else {
            count += 1;
        }
        if (g_DopSensorsCeiling[i].y > g_DopSensorsCeilingDefault[i]) {
            g_DopSensorsCeiling[i].y--;
        } else {
            count += 1;
        }
        if (i == 0 && (g_Dop.vram_flag & 0x8000)) {
            DOPPLEGANGER.posY.i.hi--;
        }
    }

    if (count == 8) {
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        SetDopplegangerAnim(0xCB);
        if (DOPPLEGANGER.step_s != 0) {
            SetDopplegangerAnim(0xCC);
        }

        if (g_Entities[E_ID_50].step < 3) {
            g_Entities[E_ID_50].step = 3;
            return;
        }
        if (g_Entities[E_ID_50].step == 5) {
            DOPPLEGANGER.palette = PAL_OVL(0x200);
            func_8010FAF4();
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x2C, 0x5B), 0);
            func_us_801C4EE4();
            if (!(g_Dop.vram_flag & 0x8000)) {
                DOPPLEGANGER.velocityY = FIX(-1);
            }
            func_80111CC0();
        }
    }
}

extern s32 D_us_801D331C;

void DopplegangerStepSwordWarp(void) {
    if (DOPPLEGANGER.step_s == 0) {
        if (g_Entities[E_BOSS_WEAPON].entityId == E_NONE) {
            D_us_801D331C = 0x10;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(61, 0x15), 0);
            DOPPLEGANGER.step_s++;
        }
    } else if (--D_us_801D331C == 0) {
        DOPPLEGANGER.palette = PAL_OVL(0x200);
        func_8010E570(0);
    }
}

extern s16 D_us_801813D8[]; // rotation angles
extern s32 D_us_801D3320;

void DopplegangerStepStone(s32 arg0) {
    switch (DOPPLEGANGER.step_s) {
    case 0:
        func_us_801C68CC();
        func_us_801C6950();
        DOPPLEGANGER.velocityY = FIX(-4);
        func_8010E3B8(FIX(-0.625));
        func_80113E68();
        DOPPLEGANGER.palette = PAL_OVL(0x161);
        g_api.PlaySfx(SFX_BO4_UNK_7DC);
        g_Dop.unk5E = 8;
        g_Dop.timers[2] = 0;
        DOPPLEGANGER.step_s = 1;
        break;

    case 1:
        func_us_801C4A30(1, 4);
        DOPPLEGANGER.palette = PAL_OVL(0x161);
        if (func_us_801C5650(0x20280) != 0) {
            DOPPLEGANGER.step = Dop_StatusStone;
            DOPPLEGANGER.velocityX = DOPPLEGANGER.velocityY = 0;
            g_api.func_80102CD8(1);
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(39, 0), 0);
            if (g_Dop.unk6A == 0) {
                D_us_801D3320 = 0x20;
            }
            DOPPLEGANGER.palette = PAL_OVL(0x19E);
            SetDopplegangerAnim(0x38);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(16, 3), 0);
            DOPPLEGANGER.step_s = 2;
        }
        break;

    case 2:
        if (g_Dop.unk6A == 0) {
            if (--D_us_801D3320 == 0) {
                DOPPLEGANGER.step = Dop_Kill;
                g_api.PlaySfx(SFX_BO4_UNK_7E6);
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(16, 3), 0);
                DOPPLEGANGER.step_s = 16;
            }
            func_us_801C4A30(1, 4);
            break;
        }

        if ((g_Dop.padTapped & PAD_DIRECTION_MASK) || arg0 != 0) {
            g_Dop.padTapped |= PAD_DIRECTION_MASK;
            DOPPLEGANGER.poseTimer = 16;
            g_Dop.unk5E--;
            g_api.PlaySfx(SFX_STONE_MOVE_B);

            if (g_Dop.unk5E == 0) {
                SetDopplegangerAnim(0x3B);
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(16, 3), 0);
                g_api.PlaySfx(SFX_BO4_UNK_7DD);
                DOPPLEGANGER.step = Dop_Hit;
                DOPPLEGANGER.step_s = 8;
                DOPPLEGANGER.palette = PAL_OVL(0x200);
            } else {
                func_us_801C4A30(1, 4);
                DOPPLEGANGER.step_s = 3;
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(13, 3), 0);
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(31, 3), 0);
                DOPPLEGANGER.palette = PAL_OVL(0x19E);
            }
        } else {
            DOPPLEGANGER.palette = PAL_OVL(0x19E);
        }

        break;

    case 3:
        if (DOPPLEGANGER.poseTimer < 0) {
            DOPPLEGANGER.step_s = 2;
            DOPPLEGANGER.drawFlags &=
                FLAG_BLINK | FLAG_DRAW_UNK40 | FLAG_DRAW_UNK20 |
                FLAG_DRAW_UNK10 | FLAG_DRAW_OPACITY | FLAG_DRAW_SCALEY |
                FLAG_DRAW_SCALEX;
        } else {
            DOPPLEGANGER.rotPivotX = 0;
            DOPPLEGANGER.drawFlags |= FLAG_DRAW_ROTATE;
            DOPPLEGANGER.rotate = D_us_801813D8[DOPPLEGANGER.poseTimer] >> 0x4;
            if (DOPPLEGANGER.rotate == 0) {
                DOPPLEGANGER.rotPivotY = 24;
            } else {
                DOPPLEGANGER.rotPivotY = 20;
            }
        }
        DOPPLEGANGER.palette = PAL_OVL(0x19E);
        break;
    }
}

#include "../../get_free_entity.h"

// this is the same as unionD_800ACFB4 in DRA
typedef union {
    u8 rawBytes[4];
    AnimationFrame af;
} unionD_us_801813F8;
extern unionD_us_801813F8 D_us_801813F8[];

extern u8 D_us_801D3324;
extern u8 D_us_801D3328;
extern u8 D_us_801D332C;
extern u8 D_us_801D3330;

void func_80118C28(s32 arg0) {
    // Break up the 4-byte struct D_us_801813F8[arg0] into individual bytes.
    D_us_801D3324 = D_us_801813F8[arg0].rawBytes[0];
    D_us_801D3328 = D_us_801813F8[arg0].rawBytes[1];
    D_us_801D332C = D_us_801813F8[arg0].rawBytes[2];
    D_us_801D3330 = D_us_801813F8[arg0].rawBytes[3];
}

extern u8 D_us_8018142C[];

static s32 func_80119E78(Primitive* prim, s16 xCenter, s16 yCenter) {
    s16 right;
    s16 size;
    u8* idx;

    // D_us_8018142C is a read-only array of bytes in 8-byte groups.
    // These are sets of 4 pairs of u,v values.
    // the ->b0 value is very likely fake.
    idx = D_us_8018142C;
    idx += prim->b0 * 8;
    if (prim->b0 >= 3) {
        size = 4;
    } else {
        size = 6;
    }
    if (prim->b0 == 6) {
        return -1;
    }
    prim->x0 = xCenter - size;
    prim->y0 = yCenter - size;
    prim->x1 = xCenter + size;
    prim->y1 = yCenter - size;
    prim->x2 = xCenter - size;
    prim->y2 = yCenter + size;
    prim->x3 = xCenter + size;
    prim->y3 = yCenter + size;

    prim->u0 = *idx++;
    prim->v0 = *idx++;
    prim->u1 = *idx++;
    prim->v1 = *idx++;
    prim->u2 = *idx++;
    prim->v2 = *idx++;
    prim->u3 = *idx++;
    prim->v3 = *idx;
    prim->b1++;
    if (!(prim->b1 & 1)) {
        prim->b0++;
    }
    return 0;
}
extern Point16 D_us_801D3334[16];

void DopEntityHitByHoly(Entity* self) {
    s32 shouldHide;
    s16 xRand;
    s16 yRand;
    s32 i;
    s16 hitboxX;
    s16 hitboxY;
    Primitive* prim;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, LEN(D_us_801D3334));
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_POS_CAMERA_LOCKED;
        hitboxX = DOPPLEGANGER.posX.i.hi + DOPPLEGANGER.hitboxOffX;
        hitboxY = DOPPLEGANGER.posY.i.hi + DOPPLEGANGER.hitboxOffY;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < LEN(D_us_801D3334); i++) {
            xRand = hitboxX + rand() % 24 - 12;
            yRand = hitboxY + rand() % 48 - 24;
            D_us_801D3334[i].x = xRand;
            D_us_801D3334[i].y = yRand;
            prim->clut = 0x1B2;
            prim->tpage = 0x1A;
            prim->b0 = 0;
            prim->b1 = 0;
            prim->g0 = 0;
            prim->g1 = (rand() & 7) + 1;
            prim->g2 = 0;
            prim->priority = DOPPLEGANGER.zPriority + 4;
            prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE | DRAW_HIDE |
                             DRAW_UNK02 | DRAW_TRANSP;
            if (rand() & 1) {
                prim->drawMode =
                    DRAW_UNK_100 | DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                    DRAW_HIDE | DRAW_UNK02 | DRAW_TRANSP;
            }
            prim = prim->next;
        }
        self->step++;
        break;

    case 1:
        if (!(g_Dop.status & PLAYER_STATUS_UNK10000)) {
            DestroyEntity(self);
            return;
        }
    }

    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < LEN(D_us_801D3334); i++) {
        switch (prim->g0) {
        case 0:
            if (--prim->g1 == 0) {
                prim->g0++;
            }
            break;
        case 1:
            hitboxX = D_us_801D3334[i].x;
            hitboxY = D_us_801D3334[i].y;
            shouldHide = func_80119E78(prim, hitboxX, hitboxY);
            D_us_801D3334[i].y--;
            if (shouldHide < 0) {
                prim->drawMode |= DRAW_HIDE;
                prim->g0++;
            } else {
                prim->drawMode &= ~DRAW_HIDE;
            }
            break;
        }
        prim = prim->next;
    }
}

void PrintDummySet(void) { FntPrint("dummy set\n"); }

extern PfnEntityUpdate D_us_8018145C[];
// some kind of timer
extern u8 D_us_801D3324;
extern u8 D_us_801D3328;
extern u8 D_us_801D332C;
extern u8 D_us_801D3330;

void func_us_801C9624(void) {
    Entity* entity;
    PfnEntityUpdate entityUpdate;
    s32 i;

    entity = g_CurrentEntity = &g_Entities[E_ID_44];

    for (i = E_ID_44; i < E_ID_90; i++, g_CurrentEntity++, entity++) {
        if (i == 16 && entity->entityId == 0) {
            g_Dop.unk48 = 0;
        }

        if (entity->entityId == 0) {
            continue;
        }

        entityUpdate = D_us_8018145C[entity->entityId];
        entityUpdate(entity);

        entity = g_CurrentEntity;
        if (entity->entityId != 0) {
            if (!(entity->flags & FLAG_UNK_10000000) &&
                (entity->posX.i.hi > 288 || entity->posX.i.hi < -32 ||
                 entity->posY.i.hi > 256 || entity->posY.i.hi < -16)) {
                DestroyEntity(g_CurrentEntity);
            } else {
                if (entity->flags & FLAG_UNK_20000000) {
                    UpdateAnim(0, &D_us_801813F8[0].af);
                }
                entity->flags |= FLAG_NOT_AN_ENEMY;
            }
        }
    }

    if (D_us_801D3324) {
        D_us_801D3324--;
        if (D_us_801D3324 & 1) {
            g_api.func_800EA5AC(1, D_us_801D3328, D_us_801D332C, D_us_801D3330);
        }
    }

    if (g_Dop.status & (PLAYER_STATUS_DEAD | PLAYER_STATUS_UNK80000)) {
        FntPrint("dead boss\n");
        entity = &g_Entities[E_ID_44];
        for (i = E_ID_44; i < E_ID_90; i++, entity++) {
            entity->hitboxState = 0;
        }
    }
}

Entity* CreateEntFactoryFromEntity(
    Entity* source, u32 factoryParams, s16 arg2) {
    Entity* newFactory = GetFreeEntity(E_ID_44, E_ID_50);

    if (newFactory == NULL) {
        return NULL;
    }

    DestroyEntity(newFactory);
    newFactory->entityId = E_FACTORY;
    newFactory->ext.factory.parent = source;
    newFactory->posX.val = source->posX.val;
    newFactory->posY.val = source->posY.val;
    newFactory->facingLeft = source->facingLeft;
    newFactory->zPriority = source->zPriority;
    newFactory->params = factoryParams & 0xFFF;
    newFactory->ext.factory.paramsBase = (factoryParams & 0xFF0000) >> 8;
    return newFactory;
}

Entity* GetFreeEntityReverse(s16 start, s16 end);

extern FactoryBlueprint D_us_8018153C[];
extern u8 D_us_801817F0[NUM_BLUEPRINT_KIND][2];

void func_us_801C98BC(Entity* self) {
    Entity* newEntity;
    s16 i;
    s16 n;
    s16 endIndex;
    s16 startIndex;
    u8* data;

    if (self->step == 0) {
        data = (u8*)&D_us_8018153C[self->params];
        self->ext.factory.newEntityId = *data++;
        self->ext.factory.amount = *data++;
        self->ext.factory.nPerCycle = *data & 0x3F;
        self->ext.factory.isNonCritical = (s16)(*data >> 7) & 1;
        self->ext.factory.incParamsKind = (s16)(*data++ >> 6) & 1;
        self->ext.factory.tCycle = *data++;
        self->ext.factory.kind = *data & 0xF;
        self->ext.factory.origin = (s16)(*data++ >> 4) & 0xF;
        self->ext.factory.delay = *data;
        self->flags |= FLAG_UNK_10000000;

        self->step++;

        switch (self->ext.factory.origin) {
        case B_ORIGIN_DEFAULT:
        case B_ORIGIN_6:
            self->flags |= FLAG_POS_CAMERA_LOCKED;
            break;
        case B_ORIGIN_2:
        case B_ORIGIN_4:
        case B_ORIGIN_5:
        case B_ORIGIN_7:
            self->posX.val = DOPPLEGANGER.posX.val;
            self->posY.val = DOPPLEGANGER.posY.val;
            break;
        }
    } else {
        switch (self->ext.factory.origin) {
        case B_ORIGIN_DEFAULT:
        case B_ORIGIN_1:
        case B_ORIGIN_3:
        case B_ORIGIN_5:
        case B_ORIGIN_6:
            break;
        case B_ORIGIN_2:
            self->posX.val = DOPPLEGANGER.posX.val;
            self->posY.val = DOPPLEGANGER.posY.val;
            break;
        case B_ORIGIN_4:
            self->posX.val = DOPPLEGANGER.posX.val;
            self->posY.val = DOPPLEGANGER.posY.val;
            if (DOPPLEGANGER.step != 2) {
                self->entityId = 0;
                return;
            }
            break;
        case B_ORIGIN_7:
            self->posX.val = DOPPLEGANGER.posX.val;
            self->posY.val = DOPPLEGANGER.posY.val;
            if (DOPPLEGANGER.step != 11) {
                self->entityId = 0;
                return;
            }
            break;
        }
    }

    if (self->ext.factory.delay) {
        if (--self->ext.factory.delay) {
            return;
        }
        self->ext.factory.delay = self->ext.factory.tCycle;
    }

    // Save this value so we don't have to re-fetch on every for-loop cycle
    n = self->ext.factory.nPerCycle;
    for (i = 0; i < n; i++) {

        // !FAKE, this should probably be &entity_ranges[unk9C] or similar,
        // instead of doing &entity_ranges followed by +=
        data = (u8*)&D_us_801817F0[0];
        data += self->ext.factory.kind * 2;

        startIndex = *data++;
        endIndex = *data;

        if (self->ext.factory.kind == 3) {
            DestroyEntity(&g_Entities[startIndex]);
            newEntity = &g_Entities[startIndex];
            g_Dop.unk48 = 0;
        } else if (self->ext.factory.kind == 0) {
            newEntity = GetFreeEntityReverse(startIndex, endIndex + 1);
        } else if (self->ext.factory.kind == 8) {
            if ((self->ext.factory.spawnIndex % 3) == 0) {
                newEntity = GetFreeEntity(81, 96);
            }
            if ((self->ext.factory.spawnIndex % 3) == 1) {
                newEntity = GetFreeEntity(96, 112);
            }
            if ((self->ext.factory.spawnIndex % 3) == 2) {
                newEntity = GetFreeEntity(112, 128);
            }
        } else {
            newEntity = GetFreeEntity(startIndex, endIndex + 1);
        }

        if (newEntity == NULL) {
            if (self->ext.factory.isNonCritical == 1) {
                self->entityId = 0;
            } else {
                self->ext.factory.delay = self->ext.factory.tCycle;
            }
            return;
        }

        DestroyEntity(newEntity);
        newEntity->entityId = self->ext.factory.newEntityId;
        newEntity->params = self->ext.factory.paramsBase;
        // The child  (newEntity) is not an ent factory, but because the factory
        // creates many entities, we can't pick a particular extension. But
        // we're not allowed to use generic, so i'll just reuse entFactory.
        newEntity->ext.factory.parent = self->ext.factory.parent;
        newEntity->posX.val = self->posX.val;
        newEntity->posY.val = self->posY.val;
        newEntity->facingLeft = self->facingLeft;
        newEntity->zPriority = self->zPriority;

        if (self->ext.factory.incParamsKind) {
            newEntity->params += self->ext.factory.spawnIndex;
        } else {
            newEntity->params += i;
        }

        self->ext.factory.spawnIndex++;

        if (self->ext.factory.spawnIndex == self->ext.factory.amount) {
            self->entityId = 0;
            return;
        }
    }
    self->ext.factory.delay = self->ext.factory.tCycle;
}

extern EInit D_us_80180448;

void func_us_801C9D58(Entity* self) {
    if (DOPPLEGANGER.step != Dop_MorphBat || DOPPLEGANGER.step_s != 3) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        InitializeEntity(D_us_80180448);
        if (g_Dop.status & PLAYER_STATUS_POISON) {
            self->attack /= 2;
        }
        self->hitboxOffX = 4;
        self->step++;
    }

    self->flags =
        FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED | FLAG_NOT_AN_ENEMY;
    self->facingLeft = DOPPLEGANGER.facingLeft;
    self->posY.i.hi = DOPPLEGANGER.posY.i.hi;
    self->posX.i.hi = DOPPLEGANGER.posX.i.hi;
}

extern u8 D_us_801818A8[10];
extern s16 D_us_80181804[];
extern AnimationFrame D_800AD57C[];
extern u8 D_us_80181898[NUM_VERTICAL_SENSORS * 2];
extern s16 D_us_80181828[];
extern s32 D_us_80181810[];
extern Point16 g_DopSensorsWall[NUM_VERTICAL_SENSORS * 2]; // g_SensorsWall

void EntitySmokePuff(Entity* self) {
    byte stackpad[40];
    s16 posX;
    s32 i;
    s16 paramsLo;
    s16 paramsHi;

    switch (self->step) {
    case 0:
        paramsHi = self->params >> 8;
        paramsLo = self->params & 0xFF;
        self->animSet = 5;
        self->anim = D_800AD57C;
        self->zPriority = DOPPLEGANGER.zPriority + 2;
        self->flags = FLAG_UNK_20000000 | FLAG_POS_CAMERA_LOCKED;
        self->palette = PAL_OVL(0x195);
        self->drawMode = DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;

        posX = D_us_80181804[paramsLo];
        if (paramsHi == 0) {
            posX += 6;
        }
        if (paramsHi == 1) {
            posX -= 8;
        }
        if ((paramsHi == 2) || (paramsHi == 0xA)) {
            posX -= 2;
        }
        if (paramsHi == 5) {
            posX = -6;
        }
        if (paramsHi == 6) {
            posX = -24;
        }
        if (paramsHi == 3) {
            posX = (rand() % 30) - 0xE;
            paramsLo = (rand() & 3) + 2;
            self->posY.i.hi -= rand() % 4;
        }
        if (paramsHi == 7) {
            posX = (rand() % 60) - 0x1E;
            paramsLo = (rand() & 3) + 2;
            self->posY.i.hi -= rand() % 4;
        }
        if (paramsHi == 9) {
            posX = rand() % 16 - 8;
            paramsLo = (rand() & 3) + 2;
            self->posY.i.hi -= (20 + (rand() % 4));
        }
        if (paramsHi == 4) {
            for (i = paramsLo * 2; i < LEN(D_us_80181898); i++) {
                if (g_Dop.colWall[D_us_80181898[i]].effects &
                    (EFFECT_UNK_0002 | EFFECT_SOLID)) {
                    break;
                }
            }
            if (i == LEN(D_us_80181898)) {
                DestroyEntity(self);
                return;
            }
            self->posX.i.hi =
                DOPPLEGANGER.posX.i.hi + g_DopSensorsWall[D_us_80181898[i]].x;
            self->posY.i.hi =
                DOPPLEGANGER.posY.i.hi + g_DopSensorsWall[D_us_80181898[i]].y;
            self->velocityY = FIX(-0.25);
            self->scaleX = D_us_80181828[1] + 0x40;
            self->scaleY = self->scaleX;
            self->step++;
            return;
        }
        if (paramsHi == 8) {
            for (i = paramsLo * 2; i < LEN(D_us_801818A8); i++) {
                if (g_Dop.colWall[D_us_801818A8[i]].effects &
                    (EFFECT_UNK_0002 | EFFECT_SOLID)) {
                    break;
                }
            }
            if (i == LEN(D_us_801818A8)) {
                DestroyEntity(self);
                return;
            }
            self->posX.i.hi =
                DOPPLEGANGER.posX.i.hi + g_DopSensorsWall[D_us_801818A8[i]].x;
            self->posY.i.hi =
                DOPPLEGANGER.posY.i.hi + g_DopSensorsWall[D_us_801818A8[i]].y;
            self->velocityY = D_us_80181810[paramsLo];
            self->scaleX = D_us_80181828[paramsLo] + 0x20;
            self->scaleY = self->scaleX;
            self->step++;
            return;
        }
        if (paramsHi == 1) {
            if (g_Dop.vram_flag & 0x8000) {
                posX /= 2;
            }
        }
        if (paramsHi == 6) {
            if (DOPPLEGANGER.velocityX > 0) {
                posX = -posX;
            }
        } else {
            if (self->facingLeft) {
                posX = -posX;
            }
        }
        self->posX.i.hi += posX;
        self->posY.i.hi += 0x18;
        self->scaleX = D_us_80181828[paramsLo] + 0x40;
        self->velocityY = D_us_80181810[paramsLo];
        if (paramsHi == 1) {
            self->velocityY = FIX(-0.25);
            SetSpeedX(-0x3000);
            self->scaleX = D_us_80181828[1] + 0x40;
        }
        if (paramsHi == 5) {
            self->velocityY = D_us_80181810[4 - paramsLo * 2];
        }
        self->scaleY = self->scaleX;
        if (paramsHi == 10) {
            self->posY.i.hi -= 6;
        }
        self->step++;
        break;
    case 1:
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

extern s32 D_us_801D3374;
extern AnimationFrame D_us_801818B4[];

void DopEntityHitByDark(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_20000000 | FLAG_POS_CAMERA_LOCKED;
        self->unk5A = 0x79;
        self->animSet = ANIMSET_DRA(14);
        self->zPriority = DOPPLEGANGER.zPriority + 2;
        self->palette = PAL_OVL(0x19F);

        if (D_us_801D3374 & 1) {
            self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
        } else {
            self->drawMode = DRAW_TPAGE;
        }
        D_us_801D3374++;
        self->opacity = 0xFF;
        self->drawFlags = FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY |
                          FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20;
        self->scaleX = self->scaleY = 0x40;
        self->anim = D_us_801818B4;

        self->posY.i.hi += ((rand() % 35) - 15);
        self->posX.i.hi += ((rand() % 20) - 10);
        self->velocityY = FIX(-0.375) - (rand() & 0x3FFF);
        self->step++;
        break;
    case 1:
        if (self->opacity > 16) {
            self->opacity -= 8;
        }
        self->posY.val += self->velocityY;
        self->scaleX += 8;
        self->scaleY += 8;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

// Does any entity with the same ID and params already
// exist in the index range [0x50, 0x90)
static bool func_8011BD48(Entity* entity) {
    s16 objId = entity->entityId;
    s16 params = entity->params;
    Entity* e;
    s32 i;

    for (e = &g_Entities[E_ID_50], i = E_ID_50; i < E_ID_90; e++, i++) {
        if (objId == e->entityId && params == e->params && e != entity) {
            return true;
        }
    }

    return false;
}

extern s16* D_us_801B0B50[];
extern s16* D_us_801B1674[];
extern s16 D_us_8018192C[42][10];
extern s32 D_us_801818EC[];
extern u8* g_SpriteSheet[];
extern s32 D_us_80181BFC;
extern u8** g_PlOvlDopBatSpritesheet[1];

// player turns white for some sort of status effect
void EntityDopplegangerBlinkWhite(Entity* self) {
    Primitive* prim;
    u8 var_s7;
    u8 var_s6;
    u8 sp7f;
    u8 sp7e;
    s16 sp7c;
    s16 sp7a;
    s16 xOffset;
    s16 yOffset;
    s16 sp78;
    s16 sp76;
    s16 sp74;
    s16 sp72;
    s16 posX;
    s16 posY;
    s16* sp5c;
    u8* sp58;
    s32 i;
    s32 sp54;
    s32 sp50;

    s16 maskedParams;
    s16 angle;
    s16 sp6e;
    s16* sp4c;
    s16 sp6c;
    s16 sp6a;
    s16 sp68;
    s16 sp66;
    s16 sp64;
    s16 sp62;
    s16 sp60;

    s32 sp40;
    Entity* sp3C;
    s32 sp38;

    maskedParams = (self->params & 0x7F00) >> 8;

    if (((maskedParams & 0x3F) != 0x1D) &&
        (g_Dop.status & PLAYER_STATUS_MIST_FORM)) {
        D_us_80181BFC = 0;
        DestroyEntity(self);
        return;
    }

    if ((D_us_80181BFC) && maskedParams != 0x20 && maskedParams != 0x21 &&
        ((maskedParams & 0x3F) != 0x1D)) {
        DestroyEntity(self);
        return;
    }

    self->posY.i.hi = DOPPLEGANGER.posY.i.hi;
    self->posX.i.hi = DOPPLEGANGER.posX.i.hi;
    self->facingLeft = DOPPLEGANGER.facingLeft;
    if (DOPPLEGANGER.animSet == (s16)ANIMSET_OVL(1)) {
        sp5c = D_us_801B0B50[DOPPLEGANGER.animCurFrame & 0x7FFF];
    }
    if (DOPPLEGANGER.animSet == (s16)ANIMSET_OVL(2)) {
        sp5c = D_us_801B1674[DOPPLEGANGER.animCurFrame & 0x7FFF];
    }
    if (!DOPPLEGANGER.animSet || (DOPPLEGANGER.animCurFrame & 0x7FFF) == 0) {
        DestroyEntity(self);
        return;
    }

    sp72 = *sp5c++;
    sp72 &= 0x7FFF;

    posX = self->posX.i.hi;
    posY = self->posY.i.hi;

    if (DOPPLEGANGER.animSet == (s16)ANIMSET_OVL(1)) {
        sp58 = g_SpriteSheet[sp72];
    }
    if (DOPPLEGANGER.animSet == (s16)ANIMSET_OVL(2)) {
        sp58 = (g_PlOvlDopBatSpritesheet)[sp72];
    }

    var_s7 = 4;
    var_s6 = 1;
    sp7f = var_s7 + sp58[0];
    sp7e = var_s6 + sp58[1];
    xOffset = sp7f - var_s7;
    yOffset = sp7e - var_s6;
    sp7c = sp5c[0] + sp58[2];
    sp7a = sp5c[1] + sp58[3];

    self->rotate = DOPPLEGANGER.rotate;
    self->drawFlags = DOPPLEGANGER.drawFlags;
    self->scaleX = DOPPLEGANGER.scaleX;
    self->scaleY = DOPPLEGANGER.scaleY;
    self->rotPivotY = DOPPLEGANGER.rotPivotY;
    self->rotPivotX = DOPPLEGANGER.rotPivotX;

    sp4c = D_us_8018192C[maskedParams & 0x3F];
    switch (self->step) {
    case 0:
        if (func_8011BD48(self)) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 8; i++) {
            D_us_801818EC[i] = i << 9;
            prim->tpage = 0x10;
            prim->clut = sp4c[3];
            prim->r0 = prim->b0 = prim->g0 = prim->r1 = prim->b1 = prim->g1 =
                prim->r2 = prim->b2 = prim->g2 = prim->r3 = prim->b3 =
                    prim->g3 = 0x80;
            prim->priority = DOPPLEGANGER.zPriority + 2;

            prim->drawMode = sp4c[8] + DRAW_COLORS + DRAW_UNK02;
            prim = prim->next;
        }
        self->ext.playerBlink.unk8A = sp4c[9];
        self->ext.playerBlink.unk90 = 0;
        self->ext.playerBlink.unk98 = 0;
        self->ext.playerBlink.unk9A = 0x100;
        self->step++;
        if (maskedParams == 0x20) {
            self->step = 8;
        }
        if (maskedParams == 0x21) {
            self->step = 0xA;
        }
        break;
    case 1:
        if (sp4c[7] == 0x7008) {
            self->ext.playerBlink.unk90 += 0x50;
        } else {
            self->ext.playerBlink.unk90 += 0xA;
        }
        if (self->ext.playerBlink.unk90 > 0x100) {
            self->ext.playerBlink.unk90 = 0x100;
            self->ext.playerBlink.unk80 = sp4c[7];
            self->step++;
        }
        break;
    case 2:
        if (sp4c[7] >= 0x7000) {
            self->ext.playerBlink.unk80 = 8;
            switch ((u32)sp4c[7]) {
            case 0x7000:
                if (g_Dop.timers[1] == 0) {
                    self->step++;
                }
                break;
            case 0x7001:
            case 0x7007:
                if (DOPPLEGANGER.step != Dop_Hit) {
                    self->step++;
                }
                break;
            case 0x7005:
            case 0x7006:
                if (DOPPLEGANGER.ext.player.anim != 0xC0) {
                    self->step++;
                }
                break;
            case 0x7008:
                if ((g_Dop.status & PLAYER_STATUS_UNK400000) == 0) {
                    self->step++;
                }
                break;
            case 0x7009: // Hold this step until player is out of state (5,3)
                // This state corresponds to wing smashing.
                if (DOPPLEGANGER.step_s != 3 ||
                    DOPPLEGANGER.step != Dop_MorphBat) {
                    self->step++;
                }
            }
        }
        if (--self->ext.playerBlink.unk80 == 0) {
            self->step++;
        }
        break;
    case 3:
        self->ext.playerBlink.unk90 -= 10;
        if (self->ext.playerBlink.unk90 < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    case 8:
        D_us_80181BFC = 1;
        self->ext.playerBlink.unk98 += 8;
        self->ext.playerBlink.unk9C += 256;
        if (self->ext.playerBlink.unk98 > 128) {
            self->ext.playerBlink.unk98 = 128;
            g_Dop.unk66 = 2;
            self->step++;
        }
        break;
    case 9:
    case 11:
        self->ext.playerBlink.unk98 -= 8;
        self->ext.playerBlink.unk9C += 0x100;
        if (self->ext.playerBlink.unk98 < 0) {
            g_Dop.unk66 = 3;
            self->params = 0x1B00;
            self->step = 1;
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 8; i++) {
                prim->clut = 0x15F;
                prim = prim->next;
            }
            D_us_80181BFC = 0;
            return;
        }
        break;
    case 10:
        D_us_80181BFC = 1;
        self->ext.playerBlink.unk98 += 8;
        self->ext.playerBlink.unk9C += 0x100;
        if (self->ext.playerBlink.unk98 > 0x80) {
            self->ext.playerBlink.unk98 = 0x80;
        }
        if (g_Dop.unk66 == 1) {
            self->step++;
        }
        break;
    }

    sp78 = self->ext.playerBlink.unk9C;
    sp76 = self->ext.playerBlink.unk98;
    sp54 = 3;
    sp50 = 6;
    if (sp4c[7] == 0x700A) {
        sp50 = 0;
        sp54 = 0;
    }
    self->ext.playerBlink.unk82 += self->ext.playerBlink.unk8A;
    if (self->facingLeft) {
        posX = posX - sp7c;
    } else {
        posX = posX + sp7c;
    }
    posY = posY + sp7a;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 8; i++) {
        if (maskedParams & 0x40) {
            switch (i) {
            case 0:
                if (self->facingLeft) {
                    prim->x1 = posX - xOffset / 2;
                } else {
                    prim->x1 = posX + xOffset / 2;
                }
                prim->x0 = posX;
                prim->u0 = var_s7;
                prim->u1 = var_s7 + xOffset / 2;
                prim->y1 = posY;
                prim->y0 = posY;
                prim->v1 = var_s6;
                prim->v0 = var_s6;
                break;
            case 1:
                if (self->facingLeft) {
                    prim->x0 = posX - xOffset / 2;
                    prim->x1 = posX - xOffset;
                } else {
                    prim->x0 = posX + xOffset / 2;
                    prim->x1 = posX + xOffset;
                }
                prim->u0 = var_s7 + xOffset / 2;
                prim->u1 = var_s7 + xOffset;
                prim->y0 = prim->y1 = posY;
                prim->v0 = prim->v1 = var_s6;
                break;
            case 2:
                if (self->facingLeft) {
                    prim->x0 = prim->x1 = posX - xOffset;
                } else {
                    prim->x0 = prim->x1 = posX + xOffset;
                }
                prim->u0 = prim->u1 = var_s7 + xOffset;
                prim->y0 = posY;
                prim->y1 = posY + yOffset / 2;
                prim->v0 = var_s6;
                prim->v1 = var_s6 + yOffset / 2;
                break;
            case 3:
                if (self->facingLeft) {
                    prim->x0 = prim->x1 = posX - xOffset;
                } else {
                    prim->x0 = prim->x1 = posX + xOffset;
                }

                prim->u0 = prim->u1 = var_s7 + xOffset;
                prim->y0 = posY + yOffset / 2;
                prim->y1 = posY + yOffset;
                prim->v0 = var_s6 + yOffset / 2;
                prim->v1 = var_s6 + yOffset;
                break;
            case 4:
                if (self->facingLeft) {
                    prim->x0 = posX - xOffset;
                    prim->x1 = posX - xOffset / 2;
                } else {
                    prim->x0 = posX + xOffset;
                    prim->x1 = posX + xOffset / 2;
                }
                prim->u0 = var_s7 + xOffset;
                prim->u1 = var_s7 + xOffset / 2;
                prim->y0 = prim->y1 = posY + yOffset;
                prim->v0 = prim->v1 = var_s6 + yOffset;
                break;
            case 5:
                if (self->facingLeft) {
                    prim->x0 = posX - xOffset / 2;
                } else {
                    prim->x0 = posX + xOffset / 2;
                }
                prim->x1 = posX;
                prim->u0 = var_s7 + xOffset / 2;
                prim->u1 = var_s7;
                prim->y0 = prim->y1 = posY + yOffset;
                prim->v0 = prim->v1 = var_s6 + yOffset;

                break;
            case 6:
                prim->x1 = posX;
                prim->x0 = posX;
                prim->u1 = var_s7;
                prim->u0 = var_s7;
                prim->y0 = posY + yOffset;
                prim->y1 = posY + yOffset / 2;
                prim->v0 = var_s6 + yOffset;
                prim->v1 = var_s6 + yOffset / 2;
                break;
            case 7:
                prim->x1 = posX;
                prim->x0 = posX;
                prim->u1 = var_s7;
                prim->u0 = var_s7;
                prim->y0 = posY + yOffset / 2;
                prim->y1 = posY;
                prim->v0 = var_s6 + yOffset / 2;
                prim->v1 = var_s6;
                break;
            }
            if (self->facingLeft) {
                prim->x2 = prim->x3 =
                    posX - xOffset / 2 +
                    ((rcos(self->ext.playerBlink.unk82) >> 4) * sp54 >> 0xC);
            } else {
                prim->x2 = prim->x3 =
                    posX + xOffset / 2 +
                    ((rcos(self->ext.playerBlink.unk82) >> 4) * sp54 >> 0xC);
            }
            prim->y2 = prim->y3 =
                (posY + yOffset / 2) -
                ((rsin(self->ext.playerBlink.unk82) >> 4) * sp50 >> 8);
            prim->u2 = prim->u3 = var_s7 + xOffset / 2;
            prim->v2 = prim->v3 = var_s6 + yOffset / 2;
        } else {
            if (self->facingLeft) {
                prim->x0 = prim->x2 = (posX - xOffset) + 1;
                prim->x1 = prim->x3 = posX + 1;
            } else {
                prim->x0 = prim->x2 = posX;
                prim->x1 = prim->x3 = posX + xOffset;
            }
            if (maskedParams == 0x20 || maskedParams == 0x21) {
                sp74 = (rsin(sp78) >> 7) * sp76 / 256;
                prim->x0 += sp74;
                prim->x1 += sp74;
                sp78 += 0x600;
                sp74 = (rsin(sp78) >> 7) * sp76 / 256;
                prim->x2 += sp74;
                prim->x3 += sp74;
            }
            prim->y0 = prim->y1 = posY + yOffset * i / 8;
            prim->y2 = prim->y3 = posY + yOffset * (i + 1) / 8;
            if (self->facingLeft) {
                prim->u0 = prim->u2 = sp7f - 1;
                prim->u1 = prim->u3 = var_s7 - 1;
            } else {
                prim->u0 = prim->u2 = var_s7;
                prim->u1 = prim->u3 = sp7f;
            }
            prim->v0 = prim->v1 = var_s6 + yOffset * i / 8;
            prim->v2 = prim->v3 = var_s6 + yOffset * (i + 1) / 8;
        }

        g_api.func_800EB758(self->posX.i.hi, self->posY.i.hi, self,
                            self->drawFlags, (POLY_GT4*)prim, self->facingLeft);

        if (maskedParams != 0x20 && maskedParams != 0x21) {
            sp6e = sp4c[0];
            sp6c = sp4c[2];
            sp6a = sp4c[1];
            sp68 = sp4c[4];
            sp64 = sp4c[6];
            sp66 = sp4c[5];
            // clang-format off
            if (maskedParams & 0x40) {
                angle = D_us_801818EC[(i + sp6e) % 8];
                prim->r0 = (((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp68);
                angle = D_us_801818EC[(i + sp6c) % 8];
                prim->g0 = (((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp64);
                angle = D_us_801818EC[(i + sp6a) % 8];
                prim->b0 = (((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp66);
                angle = D_us_801818EC[(i + sp6e + 1) % 8];
                prim->r1 = (((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp68);
                angle = D_us_801818EC[(i + sp6c + 1) % 8];
                prim->g1 = (((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp64);
                angle = D_us_801818EC[(i + sp6a + 1) % 8];
                prim->b1 = (((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp66);
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 = 0;
                D_us_801818EC[i] += self->ext.playerBlink.unk8A;
            } else {
                angle = D_us_801818EC[(i + sp6e) % 8];
                prim->r0 = prim->r1 =(((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp68);
                angle = D_us_801818EC[(i + sp6c) % 8];
                prim->g0 = prim->g1 =(((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp64);
                angle = D_us_801818EC[(i + sp6a) % 8];
                prim->b0 = prim->b1 =(((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp66);
                angle = D_us_801818EC[(i + sp6e + 1) % 8];
                prim->r2 = prim->r3 =(((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp68);
                angle = D_us_801818EC[(i + sp6c + 1) % 8];
                prim->g2 = prim->g3 =(((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp64);
                angle = D_us_801818EC[(i + sp6a + 1) % 8];
                prim->b2 = prim->b3 =(((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp66);
                D_us_801818EC[i] += self->ext.playerBlink.unk8A;
            }
        }
        // clang-format on
        prim = prim->next;
    }
    func_us_801C4954(1, 1);
    if (((maskedParams & 0x3F) == 0) || ((maskedParams & 0x3F) == 7)) {
        func_us_801C4A30(1, 0xA);
    }
}

extern s16* D_us_801B0B50[];
extern s16 D_us_80181C00[24][5];

void EntityDopplegangerOutline(Entity* self) {
    s16* animFramePtr;
    u8* spritesheetPtr;
    s16 xOffset;
    s16 yOffset;
    s16 width;
    Primitive* prim;
    s16 spriteIdx;
    s32 i;
    s16 upperparams;
    u8 spriteX;
    s16* primData;
    s16 xVar;
    s16 yVar;
    u8 four;
    u8 one;
    s16 height;
    u8 spriteY;
    s16 selfX;
    s16 selfY;

    if ((g_Dop.status & (PLAYER_STATUS_AXEARMOR | PLAYER_STATUS_TRANSFORM)) ||
        !DOPPLEGANGER.animSet || !(DOPPLEGANGER.animCurFrame & INT16_MAX)) {
        DestroyEntity(self);
        return;
    }

    upperparams = (self->params & 0x7F00) >> 8;
    self->posX.i.hi = DOPPLEGANGER.posX.i.hi;
    self->posY.i.hi = DOPPLEGANGER.posY.i.hi;
    self->facingLeft = DOPPLEGANGER.facingLeft;
    animFramePtr = D_us_801B0B50[DOPPLEGANGER.animCurFrame & INT16_MAX];
    spriteIdx = *animFramePtr++;
    spriteIdx &= 0x7FFF;
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    spritesheetPtr = ((u8**)g_SpriteSheet)[spriteIdx];
    four = 4;
    one = 1;
    spriteX = four + spritesheetPtr[0];
    spriteY = one + spritesheetPtr[1];
    width = spriteX - four;
    height = spriteY - one;
    xOffset = animFramePtr[0] + spritesheetPtr[2];
    yOffset = animFramePtr[1] + spritesheetPtr[3];
    self->rotate = DOPPLEGANGER.rotate;
    self->drawFlags =
        DOPPLEGANGER.drawFlags | (FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY);
    primData = D_us_80181C00[upperparams];
    switch (self->step) {
    case 0: // Initialization
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        // This is just not a for-loop, that's weird
        for (i = 0; i < 1; i++) {
            prim->tpage = 0x10;
            prim->clut = primData[3]; // Always 259
            prim->priority = DOPPLEGANGER.zPriority + 2;
            // primData[4] is always 49; DRAW_UNK_40 | DRAW_HIDE | DRAW_TRANSP
            prim->drawMode = primData[4] + (DRAW_COLORS | DRAW_UNK02);
            prim = prim->next;
        }
        switch (upperparams) {
        case 0: // MP refill
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 17: // Dark Metamorphosis
        case 18:
        case 20: // Sword Warp Spell (#1)
        case 22: // Soul Steal
            self->ext.playerOutline.brightness = 0x80;
            self->scaleX =
                DOPPLEGANGER.scaleX; // Player scaleX is (always?) 0x100
            self->scaleY =
                DOPPLEGANGER.scaleY; // Player scaleY is (always?) 0x100
            self->rotPivotY = DOPPLEGANGER.rotPivotY;
            self->rotPivotX = DOPPLEGANGER.rotPivotX;
            self->ext.playerOutline.timer = 8;
            break;
        case 2: // Agunea
            self->ext.playerOutline.brightness = 0xC0;
            self->scaleX =
                DOPPLEGANGER.scaleX; // Player scaleX is (always?) 0x100
            self->scaleY =
                DOPPLEGANGER.scaleY; // Player scaleY is (always?) 0x100
            self->rotPivotY = DOPPLEGANGER.rotPivotY;
            self->rotPivotX = DOPPLEGANGER.rotPivotX;
            self->ext.playerOutline.timer = 8;
            break;
        case 1: // Curse attack
            self->ext.playerOutline.brightness = 0x100;
            self->scaleX =
                DOPPLEGANGER.scaleX; // Player scaleX is (always?) 0x100
            self->scaleY =
                DOPPLEGANGER.scaleY; // Player scaleY is (always?) 0x100
            self->rotPivotY = DOPPLEGANGER.rotPivotY;
            self->rotPivotX = DOPPLEGANGER.rotPivotX;
            self->ext.playerOutline.timer = 8;
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 14:
        case 15:
        case 16:
        case 19:
        case 21: // Sword Warp Spell (#2)
            self->ext.playerOutline.brightness = 0x80;
            self->scaleX = DOPPLEGANGER.scaleX + 0x60;
            self->scaleY = DOPPLEGANGER.scaleY + 0x60;
            self->rotPivotY = DOPPLEGANGER.rotPivotY;
            self->rotPivotX = DOPPLEGANGER.rotPivotX;
            self->ext.playerOutline.timer = 8;
            break;
        }
        self->step++;
        break;

    case 1: // 8 frames at constant size
        switch (upperparams) {
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 14:
        case 15:
        case 16:
        case 18:
        case 21: // Sword Warp Spell (#2)
            self->ext.playerOutline.brightness += 16;
        case 0: // MP refill
        case 1: // Curse attack
        case 2: // Agunea
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 17: // Dark Metamorphosis
        case 19:
        case 20: // Sword Warp Spell (#1)
        case 22: // Soul Steal
            if (--self->ext.playerOutline.timer == 0) {
                self->step++;
            }
        }
        break;
    case 2: // Outline grows/shrinks, and dims
        switch (upperparams) {
        case 0: // MP refill
        case 2: // Agunea
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 15:
        case 16:
        case 17: // Dark Metamorphosis
        case 18:
        case 20: // Sword Warp Spell (#1)
        case 22: // Soul Steal
            self->scaleX += 8;
            self->scaleY += 8;
            self->ext.playerOutline.brightness -= 5;
            if (self->ext.playerOutline.brightness < 0) {
                DestroyEntity(self);
                return;
            }
            break;
        case 1: // Curse attack, grows slower and dims faster
            self->scaleX += 2;
            self->scaleY += 2;
            self->ext.playerOutline.brightness -= 16;
            if (self->ext.playerOutline.brightness < 0) {
                DestroyEntity(self);
                return;
            }
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 14:
        case 19:
        case 21: // Sword Warp Spell (#2)
            // Shrinks inward, and when at size 0x100, holds there for 8 frames
            // in step 3
            self->scaleX -= 8;
            self->scaleY -= 8;
            if (self->scaleX <= 0x100) {
                self->scaleY = self->scaleX = 0x100;
                self->ext.playerOutline.timer = 8;
                self->step++;
            }
        }
        break;
    case 3: // Outline continues static until done
        if (--self->ext.playerOutline.timer == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    if (self->facingLeft) {
        selfX = selfX - xOffset;
    } else {
        selfX = selfX + xOffset;
    }
    selfY = selfY + yOffset;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i <= 0; i++) {
        if (self->facingLeft) {
            prim->x0 = prim->x2 = (selfX - width) + 1;
            prim->x1 = prim->x3 = selfX + 1;
        } else {
            prim->x0 = prim->x2 = selfX;
            prim->x1 = prim->x3 = selfX + width;
        }

        prim->y0 = prim->y1 = selfY;
        prim->y2 = prim->y3 = selfY + height;
        if (self->facingLeft) {
            prim->u0 = prim->u2 = spriteX - 1;
            prim->u1 = prim->u3 = four - 1;
        } else {
            prim->u0 = prim->u2 = four;
            prim->u1 = prim->u3 = spriteX;
        }
        prim->v0 = prim->v1 = one;
        prim->v2 = prim->v3 = one + height;
        g_api.func_800EB758(self->posX.i.hi, self->posY.i.hi, self,
                            self->drawFlags, prim, (u16)self->facingLeft);
        prim->r0 = prim->r1 = prim->r2 = prim->r3 =
            primData[0] * self->ext.playerOutline.brightness / 256;
        prim->g0 = prim->g1 = prim->g2 = prim->g3 =
            primData[1] * self->ext.playerOutline.brightness / 256;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 =
            primData[2] * self->ext.playerOutline.brightness / 256;
        prim->priority = DOPPLEGANGER.zPriority + 2;
        prim = prim->next;
    }
    func_us_801C4954(1, 1);
}

void EntityGravityBootBeam(Entity* self) {
    Primitive* prim;
    s16 halfWidth;
    s32 i;
    s16 yOffset = -12;

    switch (self->step) {
    case 0:
        self->posY.i.hi = DOPPLEGANGER.posY.i.hi + 37;
        self->ext.timer.t = 1536;
        self->primIndex = g_api.AllocPrimitives(PRIM_G4, 4);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;

        for (prim = &g_PrimBuf[self->primIndex], i = 0; prim != NULL; i++,
            prim = prim->next) {
            halfWidth = (self->ext.timer.t >> 8) - i; // unused in this loop
            prim->r0 = 0;
            prim->g0 = 0;
            prim->b0 = 0xC0;
            prim->r1 = 0;
            prim->g1 = 0;
            prim->b1 = 0xC0;
            prim->r2 = 0x40;
            prim->g2 = 0x40;
            prim->b2 = 0x40;
            prim->r3 = 0x40;
            prim->g3 = 0x40;
            prim->b3 = 0x40;

            prim->priority = DOPPLEGANGER.zPriority - 2;
            prim->drawMode = DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        }
        self->step++;
        break;

    case 1:
        if (DOPPLEGANGER.velocityY > FIX(-1.5)) {
            self->step = Dop_Walk;
        }
        // If transformed, timer drains faster
        if (g_Dop.status & (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM)) {
            self->step = Dop_Crouch;
        }
        break;

    case 3:
        // note that with the fallthrough these decrements stack
        self->ext.timer.t -= 160;
    case 2:
        self->ext.timer.t -= 96;
        if (self->ext.timer.t < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    for (prim = &g_PrimBuf[self->primIndex], i = 0; prim != NULL; i++,
        prim = prim->next) {
        // As timer counts down, beam gets narrower.
        halfWidth = (self->ext.timer.t >> 8) - i;
        if (halfWidth < 0) {
            halfWidth = 0;
        }
        prim->x0 = self->posX.i.hi - halfWidth;
        prim->x1 = self->posX.i.hi + halfWidth;
        prim->x2 = DOPPLEGANGER.posX.i.hi - halfWidth;
        prim->x3 = DOPPLEGANGER.posX.i.hi + halfWidth;
        prim->y2 = prim->y3 = DOPPLEGANGER.posY.i.hi - yOffset;
        prim->y0 = prim->y1 = self->posY.i.hi;
    }
}

// The blue outlines of the bat that show up when wing smashing
void EntityWingSmashTrail(Entity* self) {
    if (!(DOPPLEGANGER.step_s == 3 && DOPPLEGANGER.step == Dop_MorphBat)) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->animSet = DOPPLEGANGER.animSet;
        self->animCurFrame = DOPPLEGANGER.animCurFrame | ANIM_FRAME_LOAD;
        self->unk5A = 8;
        self->zPriority = DOPPLEGANGER.zPriority - 2;
        self->drawFlags =
            DOPPLEGANGER.drawFlags |
            (FLAG_DRAW_OPACITY | FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX);
        self->opacity = 0x80;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->rotate = DOPPLEGANGER.rotate;
        self->facingLeft = DOPPLEGANGER.facingLeft;
        self->palette = PAL_OVL(0x202);
        self->scaleX = self->scaleY = 0x100;
        self->step++;
        return;
    }
    // This actually makes the wing smashes shrink over time, not rotate.
    self->scaleX -= 8;
    self->scaleY -= 8;
    self->animCurFrame = DOPPLEGANGER.animCurFrame | ANIM_FRAME_LOAD;
    if (self->opacity >= 5) {
        self->opacity -= 5;
    } else {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801CC788);

extern AnimationFrame D_800AD57C[];
extern AnimationFrame D_us_80181DC8[];
extern AnimationFrame D_us_80181E04[];

void func_8011EDA8(Entity* self) {
    s16 paramsLo = self->params & 0xFF;
    s16 paramsHi = (self->params >> 8) & 0xFF;

    switch (self->step) {
    case 0:
        if (paramsHi == 1) {
            self->scaleX = 0xC0;
            self->scaleY = 0xC0;
            self->drawFlags = FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY;
            self->animSet = ANIMSET_DRA(2);
            self->anim = D_us_80181E04;
        }

        if ((paramsHi == 0) || (paramsHi == 2)) {
            if (paramsLo & 3) {
                self->anim = D_us_80181DC8;
                self->scaleX = 0x120;
                self->scaleY = 0x120;
                self->drawFlags = FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY;
                self->animSet = ANIMSET_DRA(2);
            } else {
                self->animSet = ANIMSET_DRA(5);
                self->anim = D_800AD57C;
                self->palette = PAL_OVL(0x170);
            }
        }
        self->flags = FLAG_UNK_20000000 | FLAG_POS_CAMERA_LOCKED;

        if (rand() & 3) {
            self->zPriority = DOPPLEGANGER.zPriority + 2;
        } else {
            self->zPriority = DOPPLEGANGER.zPriority - 2;
        }

        if (paramsHi == 2) {
            self->posX.i.hi = DOPPLEGANGER.posX.i.hi + (rand() % 44) - 22;
        } else {
            self->posX.i.hi = DOPPLEGANGER.posX.i.hi + (rand() & 15) - 8;
        }

        self->posY.i.hi = DOPPLEGANGER.posY.i.hi + DOPPLEGANGER.hitboxOffY +
                          (rand() & 31) - 16;
        self->velocityY = FIX(-0.5);
        self->velocityX = DOPPLEGANGER.velocityX >> 2;
        self->step++;
        break;

    case 1:
        self->scaleX -= 4;
        self->scaleY -= 4;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if ((self->pose == 8) && (self->anim != D_800AD57C)) {
            self->drawMode = DRAW_TPAGE;
            if (!(paramsLo & 1) && (self->poseTimer == 1)) {
                CreateEntFactoryFromEntity(self, FACTORY(4, 4), 0);
            }
        }

        if ((self->pose == 16) && (self->anim == D_800AD57C)) {
            self->drawMode = DRAW_TPAGE;
        }

        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

extern u16 D_us_80181E38[2];

void DopEntityHitByLightning(Entity* self) {
    s16 xBase;
    s16 yBase;
    s32 xOffset;
    s32 yOffset;
    bool var_s0 = false;
    s32 temp_s2;
    s16 temp_s1_2;
    s16 temp_s0;
    s32 i;
    Primitive* prevPrim;
    Primitive* prim;

    if ((self->params & 0xFF00) != 0) {
        if ((++self->ext.hitbylightning.unk9C) > 0xA8) {
            var_s0 = true;
        }
    } else if (DOPPLEGANGER.step != Dop_Hit) {
        var_s0 = true;
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 6);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0x3F);
        self->ext.hitbylightning.unk80 = rand() & PSP_RANDMASK;
        self->ext.hitbylightning.unk82 = (rand() & 0x1FF) + 0x100;
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->x0 = prim->x1 = prim->x2 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = prim->y2 = prim->y3 = self->posY.i.hi;
            prim->tpage = 0x1A;
            prim->clut = D_us_80181E38[rand() & 1];
            prim->priority = DOPPLEGANGER.zPriority - 2;
            PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) = PGREY(prim, 3) =
                0x80;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }
        if ((DOPPLEGANGER.velocityY != 0) && (DOPPLEGANGER.step != Dop_Kill)) {
            self->ext.hitbylightning.unk92 = 1;
        }
        self->ext.hitbylightning.unk94 = 16;
        g_api.PlaySfx(SFX_MAGIC_SWITCH);
        g_api.PlaySfx(SFX_THUNDER_B);
        self->step++;
        break;
    case 1:
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0x1FF);
        temp_s2 = rsin(self->ext.hitbylightning.unk80);
        self->ext.hitbylightning.unk80 += self->ext.hitbylightning.unk82;
        xOffset = ((rcos(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) * 12;
        // This should probably be * -14 but that doesn't work.
        yOffset =
            -((rsin(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) * 7 << 1;
        self->posX.val = xOffset + DOPPLEGANGER.posX.val;
        self->posY.val = yOffset + DOPPLEGANGER.posY.val;
        if ((self->ext.hitbylightning.unk92) && (g_Dop.vram_flag & 0xE)) {
            var_s0 = true;
        }
        if (var_s0) {
            self->ext.hitbylightning.unk90 = (rand() & 0xF) + 0x10;
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.hitbylightning.unk90 == 0) {
            DestroyEntity(self);
            return;
        }
        if (self->ext.hitbylightning.unk94 > 0) {
            self->ext.hitbylightning.unk94--;
        }
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0xFF);
        temp_s2 = rsin(self->ext.hitbylightning.unk80);
        self->ext.hitbylightning.unk80 += self->ext.hitbylightning.unk82;
        xOffset = (((rcos(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) *
                   ((rand() % 8) + 8));
        yOffset = (-((rsin(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) *
                   ((rand() % 8) + 10)) +
                  self->ext.hitbylightning.unk98;
        self->posX.val = DOPPLEGANGER.posX.val + xOffset;
        self->posY.val = DOPPLEGANGER.posY.val + yOffset;
        self->ext.hitbylightning.unk98 -= 0x8000;
        prim = &g_PrimBuf[self->primIndex];
        break;
    }
    xBase = (self->posX.i.hi + (rand() & 7)) - 4;
    yBase = (self->posY.i.hi + (rand() & 0x1F)) - 0x18;
    temp_s1_2 = self->ext.hitbylightning.unk94;
    temp_s1_2 = (temp_s1_2 * rsin(self->ext.hitbylightning.unk80)) >> 0xC;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 5; i++) {
        prevPrim = prim;
        prim = prim->next;
        *prevPrim = *prim;
        prevPrim->next = prim;
        prevPrim->u0 = prevPrim->u2 = (i * 0x10) + 0x90;
        prevPrim->u1 = prevPrim->u3 = ((i + 1) * 0x10) + 0x90;
        prevPrim->v0 = prevPrim->v1 = 0xC0;
        prevPrim->v2 = prevPrim->v3 = 0xCF;
    }
    prim->x0 = prim->x1;
    prim->y0 = prim->y1;
    prim->x2 = prim->x3;
    prim->y2 = prim->y3;
    temp_s0 = self->ext.hitbylightning.unk7C + 0x400;
    prim->x1 = xBase + (((rcos(temp_s0) >> 4) * temp_s1_2) >> 8);
    prim->y1 = yBase - (((rsin(temp_s0) >> 4) * temp_s1_2) >> 8);
    temp_s0 = self->ext.hitbylightning.unk7C - 0x400;
    prim->x3 = xBase + (((rcos(temp_s0) >> 4) * temp_s1_2) >> 8);
    prim->y3 = yBase - (((rsin(temp_s0) >> 4) * temp_s1_2) >> 8);

    temp_s0 = (self->ext.hitbylightning.unk80 & 0xFFF);
    if (temp_s0 < 0x400) {
        prim->priority = DOPPLEGANGER.zPriority + 2;
    } else if (temp_s0 < 0xC00) {
        prim->priority = DOPPLEGANGER.zPriority - 2;
    } else {
        prim->priority = DOPPLEGANGER.zPriority + 2;
    }
    prim->u0 = prim->u2 = (i << 4) + 0x90;
    prim->u1 = prim->u3 = (i + 1 << 4) + 0x90;
    prim->v0 = prim->v1 = 0xC0;
    prim->v2 = prim->v3 = 0xCF;
}

// player gets frozen
extern Point16* D_us_80181E84[];

void EntityHitByIce(Entity* self) {
    s32 i;
    s16 xShift;
    s16 yShift;
    s32 size;
    s16 primYshift;
    s16 selfX;
    s16 selfY;
    Point16* offset;
    bool sp18;

    s16 angle;

    Primitive* prim;

    self->posX.i.hi = DOPPLEGANGER.posX.i.hi;
    self->posY.i.hi = DOPPLEGANGER.posY.i.hi;

    sp18 = false;
    if (!(g_Dop.status & PLAYER_STATUS_UNK10000)) {
        sp18 = true;
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT3, 24);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS;
        for (prim = &g_PrimBuf[self->primIndex]; prim != NULL;
             prim = prim->next) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = (rand() & 0xF) + 0x30;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = (rand() & 0x7F) + 0x80;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = (rand() & 0x1F) + 0x30;
            if (rand() & 1) {
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            } else {
                prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            }
            prim->type = PRIM_G4;
            prim->priority = DOPPLEGANGER.zPriority + 2;
        }
        if (DOPPLEGANGER.velocityY != 0) {
            self->ext.hitbyice.unk7E = 1;
        }
        if (DOPPLEGANGER.step == Dop_Kill) {
            self->ext.hitbyice.unk80 = 1;
            self->ext.hitbyice.unk82 = 0x14;
            self->ext.hitbyice.unk7E = 0;
        }
        if (DOPPLEGANGER.velocityY != 0) {
            if (DOPPLEGANGER.facingLeft) {
                self->rotate = 0x100;
            } else {
                self->rotate = -0x100;
            }
        } else {
            if (DOPPLEGANGER.velocityX > 0) {
                self->rotate = 0x80;
            } else {
                self->rotate = 0xF80;
            }
        }
        self->step++;
        break;
    case 1:
        if (self->ext.hitbyice.unk80 && --self->ext.hitbyice.unk82 == 0) {
            sp18 = true;
        }
        // Could rewrite as a series of && and || but that would probably reduce
        // readability
        if (self->ext.hitbyice.unk7E) {
            if (g_Dop.vram_flag & 0xC) {
                sp18 = true;
            }
            if (DOPPLEGANGER.step == Dop_Hit && DOPPLEGANGER.step_s == 5) {
                sp18 = true;
            }
        }
        if (sp18) {
            self->ext.hitbyice.unk7C = 0x40;
            g_api.PlaySfx(SFX_MAGIC_SWITCH);
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.hitbyice.unk7C == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    for (prim = &g_PrimBuf[self->primIndex], i = 0; i < 24; prim = prim->next,
        i++) {
        offset = D_us_80181E84[i * 3];
        if (prim->u0 < 2) {
            size = SquareRoot12(
                ((offset->x * offset->x) + (offset->y * offset->y)) << 0xC);
            angle = self->rotate + ratan2(offset->y, offset->x);
            xShift = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x0 = selfX + xShift;
            prim->y0 = selfY + yShift;

            offset = D_us_80181E84[i * 3 + 1];
            size = SquareRoot12(
                ((offset->x * offset->x) + (offset->y * offset->y)) << 0xC);
            angle = self->rotate + ratan2(offset->y, offset->x);
            xShift = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x1 = selfX + xShift;
            prim->y1 = selfY + yShift;

            offset = D_us_80181E84[i * 3 + 2];
            size = SquareRoot12(
                ((offset->x * offset->x) + (offset->y * offset->y)) << 0xC);
            angle = self->rotate + ratan2(offset->y, offset->x);
            xShift = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x2 = prim->x3 = selfX + xShift;
            prim->y2 = prim->y3 = selfY + yShift;
        }
        if ((prim->u0 == 0) && (sp18 != 0)) {
            prim->u0++;
            prim->v0 = (rand() & 15) + 1;
        }
        if (prim->u0 == 1) {
            if (--prim->v0 == 0) {
                prim->u0++;
                prim->v0 = 0x20;
                prim->u2 = 0xF0;
            }
        }
        if (prim->u0 == 2) {
            if ((prim->u2 < 0x70) || (prim->u2 > 0xD0)) {
                prim->u2 += 4;
            }
            primYshift = (s8)prim->u2 >> 4;
            prim->y0 += primYshift;
            prim->y1 += primYshift;
            prim->y2 += primYshift;
            prim->y3 += primYshift;
            if (prim->r3 < 4) {
                prim->r3 -= 4;
            }
            if (prim->g3 < 4) {
                prim->g3 -= 4;
            }
            if (prim->b3 < 4) {
                prim->b3 -= 4;
            }
            prim->r0 = prim->r1 = prim->r2 = prim->r3;
            prim->b0 = prim->b1 = prim->b2 = prim->b3;
            prim->g0 = prim->g1 = prim->g2 = prim->g3;

            prim->drawMode &= ~DRAW_UNK02;
            if (--prim->v0 == 0) {
                prim->drawMode |= DRAW_HIDE;
            }
        }
    }
}

#include "../../dra/mist.h"

extern mistStruct D_us_801D3378[16];

void func_80121F14(s32 velocityX, s32 velocityY) {
    mistStruct* ptr = D_us_801D3378;
    s32 i;

    for (i = 0; i < LEN(D_us_801D3378); i++, ptr++) {
        ptr->posX.val += velocityX;
        ptr->posY.val += velocityY;
    }
}

extern Primitive D_us_801D34D8[8];
extern u32 D_us_80182024[8];
extern u32 D_us_80182044[8];
extern mistStruct D_us_801D3378[16];

Primitive* func_80121F58(bool arg0, s32 arg1, Primitive* arg2, s16 facingLeft) {
    s32 primU0;
    s32 tempU;
    s32 tempV;
    s32 primU1;
    s32 primV0;
    s32 primV1;
    s16 angle1;
    s16 angle2;
    Primitive* prim;
    s32 i;

    if (arg0 == false) {
        if (facingLeft) {
            prim = &D_us_801D34D8[D_us_80182024[arg1 >> 1]];
            primU0 = prim->u0;
            tempU = prim->u1;
            primV0 = prim->v0;
            tempV = prim->v1;
        } else {
            prim = &D_us_801D34D8[D_us_80182044[arg1 >> 1]];
            primU0 = prim->u1;
            tempU = prim->u0;
            primV0 = prim->v1;
            tempV = prim->v0;
        }

        primU1 = (prim->u0 + prim->u1) / 2;
        primV1 = (prim->v0 + prim->v1) / 2;

        if (arg1 & 1) {
            primU0 = primU1;
            primU1 = tempU;
            primV0 = primV1;
            primV1 = tempV;
        }
        arg2->u0 = primU0;
        arg2->v0 = primV0;
        arg2->u1 = primU1;
        arg2->v1 = primV1;
        arg2->u3 = arg2->u2 = prim->u2;
        arg2->v3 = arg2->v2 = prim->v2;
        if (DOPPLEGANGER.animSet == 0xF) {
            arg2->tpage = 0x118;
        } else {
#ifdef VERSION_PSP
            arg2->tpage = 0x18;
#else
            arg2->tpage = 0x10;
#endif
        }
        arg2->clut = 0x20F;
        arg2->priority = DOPPLEGANGER.zPriority + 2;
        arg2->drawMode = DRAW_UNK_400 | DRAW_UNK_100 | DRAW_TPAGE2 |
                         DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        arg2 = arg2->next;
    } else {
        angle1 = D_us_801D3378[arg1].angle1;
        angle2 = D_us_801D3378[(arg1 + 1) % 16].angle1;

        for (i = 0; i < 4; i++) {
            // nb: the cos/sin arguments seem to be invariant, could've been
            // extracted outside the loop
            arg2->u0 = 0x60 + ((((rcos(angle1) >> 4) * 8) * (i + 1)) >> 8);
            arg2->v0 = 0xA0 - ((((rsin(angle1) >> 4) * 8) * (i + 1)) >> 8);
            arg2->u1 = 0x60 + ((((rcos(angle2) >> 4) * 8) * (i + 1)) >> 8);
            arg2->v1 = 0xA0 - ((((rsin(angle2) >> 4) * 8) * (i + 1)) >> 8);

            if (i == 3) {
                if (arg2->u0 < 4) {
                    arg2->u0 = -1;
                }
                if (arg2->u1 < 4) {
                    arg2->u1 = -1;
                }
                if (arg2->v0 < 4) {
                    arg2->v0 = -1;
                }
                if (arg2->v1 < 4) {
                    arg2->v1 = -1;
                }
            }

            arg2->u2 = 0x60 + ((((rcos(angle1) >> 4) * 8) * i) >> 8);
            arg2->v2 = 0xA0 - ((((rsin(angle1) >> 4) * 8) * i) >> 8);
            arg2->u3 = 0x60 + ((((rcos(angle2) >> 4) * 8) * i) >> 8);
            arg2->v3 = 0xA0 - ((((rsin(angle2) >> 4) * 8) * i) >> 8);

            arg2->tpage = 0x18;
            arg2->clut = 0x20F;
            arg2->priority = DOPPLEGANGER.zPriority + 4;
            arg2->drawMode =
                DRAW_UNK_400 | DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE |
                DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            arg2 = arg2->next;
        }
    }
    return arg2;
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", EntityMist);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801CF8C4);

#include "../../rebound_stone.h"

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801D038C);

s32 UpdateUnarmedAnim(s8*, AnimationFrame*);
extern EInit D_us_80180454;
extern EInit D_us_80180460;
extern DopWeaponAnimation D_us_80184304[];

// Similar to DRA's EntityUnarmedAttack
void func_us_801D0BD8(Entity* self) {
    EInit* var_a0;
    s16 animIndex;
    DopWeaponAnimation* anim;

    animIndex = (self->params & 0x7FFF) >> 8;
    self->posX.val = DOPPLEGANGER.posX.val;
    self->posY.val = DOPPLEGANGER.posY.val;
    self->facingLeft = DOPPLEGANGER.facingLeft;
    anim = &D_us_80184304[animIndex];

    if (DOPPLEGANGER.ext.player.anim < anim->frameStart ||
        DOPPLEGANGER.ext.player.anim >= (anim->frameStart + 7) ||
        !g_Dop.unk46) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        var_a0 = &D_us_80180454;
        if (animIndex != 0) {
            var_a0 = &D_us_80180460;
        }
        InitializeEntity(*var_a0);
        if (g_Dop.status & PLAYER_STATUS_POISON) {
            self->attack /= 2;
        }
        self->zPriority = DOPPLEGANGER.zPriority - 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->flags = FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED;
        self->step = Dop_Stand;
    }
    self->ext.weapon.anim = DOPPLEGANGER.ext.player.anim - anim->frameStart;
    if (DOPPLEGANGER.poseTimer == 1 && DOPPLEGANGER.pose == anim->soundFrame) {
        g_api.PlaySfx(anim->soundId);
    }
    if (UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801D0D98);
