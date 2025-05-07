// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

// n.b.! this is the same as rbo5/unk_4648C.c

void func_us_801C6E7C(s32 arg0) {
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
bool func_us_801C6040(s32 branchFlags);

extern PlayerState g_Dop;

void DopplegangerStepHighJump(void) {
    s32 temp;
    s32 var_s1;

    var_s1 = 0;
    g_Dop.unk4A++;
    if (func_us_801C6040(2) != 0) {
        return;
    }

    switch (DOPPLEGANGER.step_s) {
    case 0:
        if (g_Dop.vram_flag & 2) {
            func_us_801C6E7C(3);
            if (g_Dop.unk4A > 4) {
                DOPPLEGANGER.step_s = 2;
                DOPPLEGANGER.rotZ = 0x800;
                DOPPLEGANGER.rotPivotX = 0;
                DOPPLEGANGER.rotPivotY = 2;
                DOPPLEGANGER.drawFlags |= FLAG_DRAW_ROTZ;
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
            func_us_801C6E7C(3);
        } else {
            DOPPLEGANGER.velocityY = DOPPLEGANGER.velocityY + 0x6000;
            if (DOPPLEGANGER.velocityY > 0x8000) {
                var_s1 = 1;
            }
        }
        break;

    case 2:
        DOPPLEGANGER.drawFlags |= FLAG_DRAW_ROTZ;
        DOPPLEGANGER.rotPivotX = 0;
        DOPPLEGANGER.rotPivotY = 2;
        if (g_Dop.unk4A > 56) {
            SetDopplegangerAnim(0x2D);
            DOPPLEGANGER.rotZ = 0;
            DOPPLEGANGER.step_s = 4;
            DOPPLEGANGER.drawFlags &=
                FLAG_BLINK | FLAG_DRAW_UNK40 | FLAG_DRAW_UNK20 |
                FLAG_DRAW_UNK10 | FLAG_DRAW_UNK8 | FLAG_DRAW_ROTY |
                FLAG_DRAW_ROTX;
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

void func_8010FAF4();

void func_us_801C72BC(void) {
    DOPPLEGANGER.animSet = ANIMSET_OVL(1);
    DOPPLEGANGER.drawFlags &= FLAG_BLINK | FLAG_DRAW_UNK40 | FLAG_DRAW_UNK20 |
                              FLAG_DRAW_UNK10 | FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
    DOPPLEGANGER.poseTimer = 0;
    DOPPLEGANGER.pose = 0;
    DOPPLEGANGER.drawMode = DRAW_DEFAULT;
    g_Dop.unk44 = 0;
    g_Dop.unk46 = 0;
    DOPPLEGANGER.rotZ = 0;
    if (g_Entities[STAGE_ENTITY_START + 16].entityId == E_ID_22) {
        func_8010FAF4();
    }
}

void func_us_801C7340(void) {
    if (DOPPLEGANGER.posX.i.hi <= PLAYER.posX.i.hi) {
        DOPPLEGANGER.entityRoomIndex = 0;
        return;
    }
    DOPPLEGANGER.entityRoomIndex = 1;
}

INCLUDE_ASM("boss/bo4/nonmatchings/unk_46E7C", DopplegangerHandleDamage);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_46E7C", DopplegangerStepKill);

extern s16 D_us_80183B0E[];

s32 BatFormFinished(void) {
    if ((DOPPLEGANGER.step_s == 0) || !(g_Dop.padTapped & 8)) {
        return false;
    }

    SetDopplegangerStep(10);
    SetDopplegangerAnim(202);
    D_us_80183B0E[0] = 6;
    DOPPLEGANGER.palette = PAL_OVL(0x20D);
    g_Dop.unk66 = 0;
    g_Dop.unk68 = 0;
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(44, 0x21), 0);
    DOPPLEGANGER.velocityY >>= 1;
    return true;
}

void func_8011690C(s16 arg0) {
    if (DOPPLEGANGER.rotZ < arg0) {
        DOPPLEGANGER.rotZ += 16;
        if (arg0 < DOPPLEGANGER.rotZ) {
            DOPPLEGANGER.rotZ = arg0;
        }
    }
    if (arg0 < DOPPLEGANGER.rotZ) {
        DOPPLEGANGER.rotZ -= 16;
        if (DOPPLEGANGER.rotZ < arg0) {
            DOPPLEGANGER.rotZ = arg0;
        }
    }
}

static s32 func_us_801C820C(void) {
    // n.b.! Dop40 checks for padPressed
    if (g_Dop.padTapped & PAD_SQUARE) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("boss/bo4/nonmatchings/unk_46E7C", ControlBatForm);

extern s16 D_us_8018126C[];
extern s16 D_us_80181274[];
extern s16 D_us_8018128C[][2];
extern s16 D_us_8018129C[][2];
extern s16 D_us_80183B0C[][2];

void DopplegangerStepUnmorphBat(void) {
    s32 i;
    s32 count;
    u8 _pad[40]; // must be between 33 & 40

    DOPPLEGANGER.drawFlags = FLAG_DRAW_ROTZ;
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
            if (D_us_8018129C[i][1] < D_us_80181274[i]) {
                D_us_8018129C[i][1]++;
            } else {
                count++;
            }

            if (D_us_8018128C[i][1] > D_us_8018126C[i]) {
                D_us_8018128C[i][1]--;
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
            DOPPLEGANGER.rotZ = 0;
            g_Dop.unk66 = 1;
            DOPPLEGANGER.step_s = 1;
            D_us_80183B0C[0][1] = 0x5F;
        }
        break;

    case 1:
        if (g_Dop.unk66 == 3) {
            func_us_801C58E4();
            if (!(g_Dop.vram_flag & 0x8000)) {
                DOPPLEGANGER.velocityY = 0xFFFF0000;
            }
            DOPPLEGANGER.palette = 0x8200;
            func_80111CC0();
        }
        break;
    }
}

s32 func_us_801C8EE4(void) {
    if (DOPPLEGANGER.step_s == 0 || !(g_Dop.padTapped & PAD_R2)) {
        return false;
    }
    CheckMoveDirection();
    SetDopplegangerStep(15);
    return true;
}

extern s32 D_us_801D4A1C;

void ControlMistForm(void) {
    u32 padDirection;

    if (func_us_801C8EE4() == 0) {
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
            D_us_80183B0E[0] = DOPPLEGANGER.animCurFrame;
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

        if (D_us_8018129C[i][1] < D_us_80181274[i]) {
            D_us_8018129C[i][1]++;
        } else {
            count += 1;
        }
        if (D_us_8018128C[i][1] > D_us_8018126C[i]) {
            D_us_8018128C[i][1]--;
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
            func_us_801C58E4();
            if (!(g_Dop.vram_flag & 0x8000)) {
                DOPPLEGANGER.velocityY = FIX(-1);
            }
            func_80111CC0();
        }
    }
}

extern s32 D_us_801D3D44;

void DopplegangerStepSwordWarp(void) {
    if (DOPPLEGANGER.step_s == 0) {
        if (g_Entities[E_BOSS_WEAPON].entityId == E_NONE) {
            D_us_801D3D44 = 0x10;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(61, 0x15), 0);
            DOPPLEGANGER.step_s++;
        }
    } else if (--D_us_801D3D44 == 0) {
        DOPPLEGANGER.palette = PAL_OVL(0x200);
        func_8010E570(0);
    }
}

extern s16 D_us_8018134C[]; // rotation angles
extern s32 D_us_801D3D48;

void DopplegangerStepStone(s32 arg0) {
    switch (DOPPLEGANGER.step_s) {
    case 0:
        func_us_801C72BC();
        func_us_801C7340();
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
        func_us_801C5430(1, 4);
        DOPPLEGANGER.palette = PAL_OVL(0x161);
        if (func_us_801C6040(0x20280) != 0) {
            DOPPLEGANGER.step = Dop_StatusStone;
            DOPPLEGANGER.velocityX = DOPPLEGANGER.velocityY = 0;
            g_api.func_80102CD8(1);
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(39, 0), 0);
            if (g_Dop.unk6A == 0) {
                D_us_801D3D48 = 0x20;
            }
            DOPPLEGANGER.palette = PAL_OVL(0x19E);
            SetDopplegangerAnim(0x38);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(16, 3), 0);
            DOPPLEGANGER.step_s = 2;
        }
        break;

    case 2:
        if (g_Dop.unk6A == 0) {
            if (--D_us_801D3D48 == 0) {
                DOPPLEGANGER.step = Dop_Kill;
                g_api.PlaySfx(SFX_BO4_UNK_7E6);
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(16, 3), 0);
                DOPPLEGANGER.step_s = 16;
            }
            func_us_801C5430(1, 4);
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
                func_us_801C5430(1, 4);
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
                FLAG_DRAW_UNK10 | FLAG_DRAW_UNK8 | FLAG_DRAW_ROTY |
                FLAG_DRAW_ROTX;
        } else {
            DOPPLEGANGER.rotPivotX = 0;
            DOPPLEGANGER.drawFlags |= FLAG_DRAW_ROTZ;
            DOPPLEGANGER.rotZ = D_us_8018134C[DOPPLEGANGER.poseTimer] >> 0x4;
            if (DOPPLEGANGER.rotZ == 0) {
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
} unionD_us_8018136C;
extern unionD_us_8018136C D_us_8018136C[];

extern u8 D_us_801D3D4C;
extern u8 D_us_801D3D50;
extern u8 D_us_801D3D54;
extern u8 D_us_801D3D58;

void func_80118C28(s32 arg0) {
    // Break up the 4-byte struct D_us_8018136C[arg0] into individual bytes.
    D_us_801D3D4C = D_us_8018136C[arg0].rawBytes[0];
    D_us_801D3D50 = D_us_8018136C[arg0].rawBytes[1];
    D_us_801D3D54 = D_us_8018136C[arg0].rawBytes[2];
    D_us_801D3D58 = D_us_8018136C[arg0].rawBytes[3];
}

extern u8 D_us_801813A0[];

static s32 func_80119E78(Primitive* prim, s16 xCenter, s16 yCenter) {
    s16 right;
    s16 size;
    u8* idx;

    // D_us_801813A0 is a read-only array of bytes in 8-byte groups.
    // These are sets of 4 pairs of u,v values.
    // the ->b0 value is very likely fake.
    idx = D_us_801813A0;
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

extern Point16 D_us_801D3D5C[16];

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
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, LEN(D_us_801D3D5C));
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_POS_CAMERA_LOCKED;
        hitboxX = DOPPLEGANGER.posX.i.hi + DOPPLEGANGER.hitboxOffX;
        hitboxY = DOPPLEGANGER.posY.i.hi + DOPPLEGANGER.hitboxOffY;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < LEN(D_us_801D3D5C); i++) {
            xRand = hitboxX + rand() % 24 - 12;
            yRand = hitboxY + rand() % 48 - 24;
            D_us_801D3D5C[i].x = xRand;
            D_us_801D3D5C[i].y = yRand;
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
    for (i = 0; i < LEN(D_us_801D3D5C); i++) {
        switch (prim->g0) {
        case 0:
            if (--prim->g1 == 0) {
                prim->g0++;
            }
            break;
        case 1:
            hitboxX = D_us_801D3D5C[i].x;
            hitboxY = D_us_801D3D5C[i].y;
            shouldHide = func_80119E78(prim, hitboxX, hitboxY);
            D_us_801D3D5C[i].y--;
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

extern PfnEntityUpdate D_us_801813D0[];
// some kind of timer
extern u8 D_us_801D3D4C;
extern u8 D_us_801D3D50;
extern u8 D_us_801D3D54;
extern u8 D_us_801D3D58;

void func_us_801CA014(void) {
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

        entityUpdate = D_us_801813D0[entity->entityId];
        entityUpdate(entity);

        entity = g_CurrentEntity;
        if (entity->entityId != 0) {
            if (!(entity->flags & FLAG_UNK_10000000) &&
                (entity->posX.i.hi > 288 || entity->posX.i.hi < -32 ||
                 entity->posY.i.hi > 256 || entity->posY.i.hi < -16)) {
                DestroyEntity(g_CurrentEntity);
            } else {
                if (entity->flags & FLAG_UNK_20000000) {
                    UpdateAnim(0, &D_us_8018136C[0].af);
                }
                entity->flags |= FLAG_NOT_AN_ENEMY;
            }
        }
    }

    if (D_us_801D3D4C) {
        D_us_801D3D4C--;
        if (D_us_801D3D4C & 1) {
            g_api.g_pfn_800EA5AC(
                1, D_us_801D3D50, D_us_801D3D54, D_us_801D3D58);
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

INCLUDE_ASM("boss/bo4/nonmatchings/unk_46E7C", func_us_801CA2AC);

extern EInit D_us_80180434;

void func_us_801CA748(Entity* self) {
    if (DOPPLEGANGER.step != Dop_MorphBat ||
        DOPPLEGANGER.step_s != Dop_Crouch) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        InitializeEntity(D_us_80180434);
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

extern u8 D_us_8018181C[10];
extern s16 D_us_80181778[];
extern AnimationFrame D_us_801817A8[];
extern u8 D_us_8018180C[NUM_VERTICAL_SENSORS * 2];
extern s16 D_us_8018179C[];
extern s32 D_us_80181784[];
extern Point16 D_us_801812AC[NUM_VERTICAL_SENSORS * 2]; // g_SensorsWall

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
        self->anim = D_us_801817A8;
        self->zPriority = DOPPLEGANGER.zPriority + 2;
        self->flags = FLAG_UNK_20000000 | FLAG_POS_CAMERA_LOCKED;
        self->palette = PAL_OVL(0x195);
        self->drawMode = DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;

        posX = D_us_80181778[paramsLo];
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
            for (i = paramsLo * 2; i < LEN(D_us_8018180C); i++) {
                if (g_Dop.colWall[D_us_8018180C[i]].effects &
                    (EFFECT_UNK_0002 | EFFECT_SOLID)) {
                    break;
                }
            }
            if (i == LEN(D_us_8018180C)) {
                DestroyEntity(self);
                return;
            }
            self->posX.i.hi =
                DOPPLEGANGER.posX.i.hi + D_us_801812AC[D_us_8018180C[i]].x;
            self->posY.i.hi =
                DOPPLEGANGER.posY.i.hi + D_us_801812AC[D_us_8018180C[i]].y;
            self->velocityY = FIX(-0.25);
            self->rotX = D_us_8018179C[1] + 0x40;
            self->rotY = self->rotX;
            self->step++;
            return;
        }
        if (paramsHi == 8) {
            for (i = paramsLo * 2; i < LEN(D_us_8018181C); i++) {
                if (g_Dop.colWall[D_us_8018181C[i]].effects &
                    (EFFECT_UNK_0002 | EFFECT_SOLID)) {
                    break;
                }
            }
            if (i == LEN(D_us_8018181C)) {
                DestroyEntity(self);
                return;
            }
            self->posX.i.hi =
                DOPPLEGANGER.posX.i.hi + D_us_801812AC[D_us_8018181C[i]].x;
            self->posY.i.hi =
                DOPPLEGANGER.posY.i.hi + D_us_801812AC[D_us_8018181C[i]].y;
            self->velocityY = D_us_80181784[paramsLo];
            self->rotX = D_us_8018179C[paramsLo] + 0x20;
            self->rotY = self->rotX;
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
        self->rotX = D_us_8018179C[paramsLo] + 0x40;
        self->velocityY = D_us_80181784[paramsLo];
        if (paramsHi == 1) {
            self->velocityY = FIX(-0.25);
            SetSpeedX(-0x3000);
            self->rotX = D_us_8018179C[1] + 0x40;
        }
        if (paramsHi == 5) {
            self->velocityY = D_us_80181784[4 - paramsLo * 2];
        }
        self->rotY = self->rotX;
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

extern s32 D_us_801D3D9C;
extern AnimationFrame D_us_80181828[];

void DopEntityHitByDark(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_20000000 | FLAG_POS_CAMERA_LOCKED;
        self->unk5A = 0x79;
        self->animSet = ANIMSET_DRA(14);
        self->zPriority = DOPPLEGANGER.zPriority + 2;
        self->palette = PAL_OVL(0x19F);

        if (D_us_801D3D9C & 1) {
            self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
        } else {
            self->drawMode = DRAW_TPAGE;
        }
        D_us_801D3D9C++;
        self->unk6C = 0xFF;
        self->drawFlags =
            FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20;
        self->rotX = self->rotY = 0x40;
        self->anim = D_us_80181828;

        self->posY.i.hi += ((rand() % 35) - 15);
        self->posX.i.hi += ((rand() % 20) - 10);
        self->velocityY = FIX(-0.375) - (rand() & 0x3FFF);
        self->step++;
        break;
    case 1:
        if (self->unk6C > 16) {
            self->unk6C -= 8;
        }
        self->posY.val += self->velocityY;
        self->rotX += 8;
        self->rotY += 8;
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

INCLUDE_ASM("boss/bo4/nonmatchings/unk_46E7C", EntityDopplegangerBlinkWhite);

extern s16* D_us_801B0A78[];
extern s16 D_us_80181B74[24][5];
extern u8* g_SpriteSheet[];

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
    animFramePtr = D_us_801B0A78[DOPPLEGANGER.animCurFrame & INT16_MAX];
    spriteIdx = *animFramePtr++;
    spriteIdx &= INT16_MAX;
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
    self->rotZ = DOPPLEGANGER.rotZ;
    self->drawFlags =
        DOPPLEGANGER.drawFlags | (FLAG_DRAW_ROTX | FLAG_DRAW_ROTY);
    primData = D_us_80181B74[upperparams];
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
            self->rotX = DOPPLEGANGER.rotX; // Player rotX is (always?) 0x100
            self->rotY = DOPPLEGANGER.rotY; // Player rotY is (always?) 0x100
            self->rotPivotY = DOPPLEGANGER.rotPivotY;
            self->rotPivotX = DOPPLEGANGER.rotPivotX;
            self->ext.playerOutline.timer = 8;
            break;
        case 2: // Agunea
            self->ext.playerOutline.brightness = 0xC0;
            self->rotX = DOPPLEGANGER.rotX; // Player rotX is (always?) 0x100
            self->rotY = DOPPLEGANGER.rotY; // Player rotY is (always?) 0x100
            self->rotPivotY = DOPPLEGANGER.rotPivotY;
            self->rotPivotX = DOPPLEGANGER.rotPivotX;
            self->ext.playerOutline.timer = 8;
            break;
        case 1: // Curse attack
            self->ext.playerOutline.brightness = 0x100;
            self->rotX = DOPPLEGANGER.rotX; // Player rotX is (always?) 0x100
            self->rotY = DOPPLEGANGER.rotY; // Player rotY is (always?) 0x100
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
            self->rotX = DOPPLEGANGER.rotX + 0x60;
            self->rotY = DOPPLEGANGER.rotY + 0x60;
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
            self->rotX += 8;
            self->rotY += 8;
            self->ext.playerOutline.brightness -= 5;
            if (self->ext.playerOutline.brightness < 0) {
                DestroyEntity(self);
                return;
            }
            break;
        case 1: // Curse attack, grows slower and dims faster
            self->rotX += 2;
            self->rotY += 2;
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
            self->rotX -= 8;
            self->rotY -= 8;
            if (self->rotX <= 0x100) {
                self->rotY = self->rotX = 0x100;
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
        PRED(prim) = primData[0] * self->ext.playerOutline.brightness / 256;
        PGRN(prim) = primData[1] * self->ext.playerOutline.brightness / 256;
        PBLU(prim) = primData[2] * self->ext.playerOutline.brightness / 256;
        prim->priority = DOPPLEGANGER.zPriority + 2;
        prim = prim->next;
    }
    func_us_801C5354(1, 1);
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
        self->drawFlags = DOPPLEGANGER.drawFlags |
                          (FLAG_DRAW_UNK8 | FLAG_DRAW_ROTY | FLAG_DRAW_ROTX);
        self->unk6C = 0x80; // a lifetime counter
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->rotZ = DOPPLEGANGER.rotZ;
        self->facingLeft = DOPPLEGANGER.facingLeft;
        self->palette = PAL_OVL(0x202);
        self->rotX = self->rotY = 0x100;
        self->step++;
        return;
    }
    // This actually makes the wing smashes shrink over time, not rotate.
    self->rotX -= 8;
    self->rotY -= 8;
    self->animCurFrame = DOPPLEGANGER.animCurFrame | ANIM_FRAME_LOAD;
    // Unclear why we count down by 5's instead of just making unk6C start
    // smaller
    if (self->unk6C >= 5) {
        self->unk6C -= 5;
    } else {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("boss/bo4/nonmatchings/unk_46E7C", func_us_801CD178);

extern AnimationFrame D_us_801817A8[];
extern AnimationFrame D_us_80181D3C[];
extern AnimationFrame D_us_80181D78[];

void func_us_801CD89C(Entity* self) {
    s16 paramsLo = self->params & 0xFF;
    s16 paramsHi = (self->params >> 8) & 0xFF;

    switch (self->step) {
    case 0:
        if (paramsHi == 1) {
            self->rotX = 0xC0;
            self->rotY = 0xC0;
            self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
            self->animSet = ANIMSET_DRA(2);
            self->anim = D_us_80181D78;
        }

        if ((paramsHi == 0) || (paramsHi == 2)) {
            if (paramsLo & 3) {
                self->anim = D_us_80181D3C;
                self->rotX = 0x120;
                self->rotY = 0x120;
                self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
                self->animSet = ANIMSET_DRA(2);
            } else {
                self->animSet = ANIMSET_DRA(5);
                self->anim = D_us_801817A8;
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
        self->rotX -= 4;
        self->rotY -= 4;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if ((self->pose == 8) && (self->anim != D_us_801817A8)) {
            self->drawMode = DRAW_TPAGE;
            if (!(paramsLo & 1) && (self->poseTimer == 1)) {
                CreateEntFactoryFromEntity(self, FACTORY(4, 4), 0);
            }
        }

        if ((self->pose == 16) && (self->anim == D_us_801817A8)) {
            self->drawMode = DRAW_TPAGE;
        }

        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

extern u16 D_us_80181DAC[2];

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
            prim->clut = D_us_80181DAC[rand() & 1];
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
extern Point16* D_us_80181DF8[];

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
                self->rotZ = 0x100;
            } else {
                self->rotZ = -0x100;
            }
        } else {
            if (DOPPLEGANGER.velocityX > 0) {
                self->rotZ = 0x80;
            } else {
                self->rotZ = 0xF80;
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
        offset = D_us_80181DF8[i * 3];
        if (prim->u0 < 2) {
            size = SquareRoot12(
                ((offset->x * offset->x) + (offset->y * offset->y)) << 0xC);
            angle = self->rotZ + ratan2(offset->y, offset->x);
            xShift = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x0 = selfX + xShift;
            prim->y0 = selfY + yShift;

            offset = D_us_80181DF8[i * 3 + 1];
            size = SquareRoot12(
                ((offset->x * offset->x) + (offset->y * offset->y)) << 0xC);
            angle = self->rotZ + ratan2(offset->y, offset->x);
            xShift = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x1 = selfX + xShift;
            prim->y1 = selfY + yShift;

            offset = D_us_80181DF8[i * 3 + 2];
            size = SquareRoot12(
                ((offset->x * offset->x) + (offset->y * offset->y)) << 0xC);
            angle = self->rotZ + ratan2(offset->y, offset->x);
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

extern mistStruct D_us_801D3DA0[16];

void func_80121F14(s32 velocityX, s32 velocityY) {
    mistStruct* ptr = D_us_801D3DA0;
    s32 i;

    for (i = 0; i < LEN(D_us_801D3DA0); i++, ptr++) {
        ptr->posX.val += velocityX;
        ptr->posY.val += velocityY;
    }
}

extern Primitive D_us_801D3F00[8];
extern u32 D_us_80181F98[8];
extern u32 D_us_80181FB8[8];
extern mistStruct D_us_801D3DA0[16];

Primitive* func_us_801CEA30(
    bool arg0, s32 arg1, Primitive* arg2, s16 facingLeft) {
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
            prim = &D_us_801D3F00[D_us_80181F98[arg1 >> 1]];
            primU0 = prim->u0;
            tempU = prim->u1;
            primV0 = prim->v0;
            tempV = prim->v1;
        } else {
            prim = &D_us_801D3F00[D_us_80181FB8[arg1 >> 1]];
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
        angle1 = D_us_801D3DA0[arg1].angle1;
        angle2 = D_us_801D3DA0[(arg1 + 1) % 16].angle1;

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

INCLUDE_ASM("boss/bo4/nonmatchings/unk_46E7C", EntityMist);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_46E7C", func_us_801D0318);

#include "../../rebound_stone.h"

INCLUDE_ASM("boss/bo4/nonmatchings/unk_46E7C", func_us_801D0DE0);

s32 UpdateUnarmedAnim(s8*, AnimationFrame*);
extern EInit D_us_80180440;
extern EInit D_us_8018044C;
extern DopWeaponAnimation D_us_80184278[];

// Similar to DRA's EntityUnarmedAttack
void func_us_801D162C(Entity* self) {
    EInit* var_a0;
    s16 animIndex;
    DopWeaponAnimation* anim;

    animIndex = (self->params & 0x7FFF) >> 8;
    self->posX.val = DOPPLEGANGER.posX.val;
    self->posY.val = DOPPLEGANGER.posY.val;
    self->facingLeft = DOPPLEGANGER.facingLeft;
    anim = &D_us_80184278[animIndex];

    if (DOPPLEGANGER.ext.player.anim < anim->frameStart ||
        DOPPLEGANGER.ext.player.anim >= (anim->frameStart + 7) ||
        !g_Dop.unk46) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        var_a0 = &D_us_80180440;
        if (animIndex != 0) {
            var_a0 = &D_us_8018044C;
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

INCLUDE_ASM("boss/bo4/nonmatchings/unk_46E7C", func_us_801D17EC);
