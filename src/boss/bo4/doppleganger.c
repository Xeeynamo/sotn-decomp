// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

extern s32 D_us_801D4118[];
extern s32 D_us_801D4198[];
extern s32 D_us_801D4D74;

void func_us_801C1A38(void) {
    Entity* entity;
    Primitive* prim;
    s16 primIndex;
    s32 angle;
    s32 scale;
    s32 i;
    s32 colliderSize;
    s32* colliders;

    g_CurrentEntity = &DOPPLEGANGER;
    DOPPLEGANGER.animSet = ANIMSET_OVL(1);
    DOPPLEGANGER.unk5A = 8;
    g_PlayerDraw[8].enableColorBlend = 0;
    DOPPLEGANGER.zPriority = g_unkGraphicsStruct.g_zEntityCenter + 8;
    if (DOPPLEGANGER.posX.i.hi < PLAYER.posX.i.hi) {
        DOPPLEGANGER.facingLeft = false;
    } else {
        DOPPLEGANGER.facingLeft = true;
    }

    DOPPLEGANGER.palette = PAL_OVL(0x200);
    DOPPLEGANGER.rotX = 0x100;
    DOPPLEGANGER.rotY = 0x100;
    DOPPLEGANGER.drawMode = DRAW_DEFAULT;
    DOPPLEGANGER.flags =
        FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED | FLAG_UNK_400000;

    // BUG: this loop seems to be clearing parts of the floor
    //      ceiling colliders, but not all of them
    colliderSize = (sizeof(Collider) * 6) + 0x1C;
    colliders = (s32*)g_Dop.colFloor;
    for (i = 0; i < colliderSize; i++, colliders++) {
        *colliders = 0;
    }

    D_us_801D4D74 = 0;
    g_Dop.vram_flag = 0;
    func_us_801C59DC(0);
    entity = &g_Entities[E_ID_41];

    for (i = 0; i < 3; i++, entity++) {
        DestroyEntity(entity);
        entity->animSet = ANIMSET_OVL(1);
        entity->unk5A = i + 9;
        entity->palette = PAL_OVL(0x200);
        entity->flags = FLAG_POS_CAMERA_LOCKED;
    }
    primIndex = g_api.AllocPrimitives(PRIM_TILE, 6);
    prim = &g_PrimBuf[primIndex];
    g_Entities[E_ID_41].primIndex = primIndex;
    g_Entities[E_ID_41].flags |= FLAG_HAS_PRIMS;

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        prim = prim->next;
    }

    for (i = 0; i < 32; i++) {
        angle = (rand() & 0x3FF) + 0x100;
        scale = (rand() & 0xFF) + 0x100;
        D_us_801D4118[i] = ((rcos(angle) << 4) * scale) >> 8;
        D_us_801D4198[i] = -(((rsin(angle) << 4) * scale) >> 7);
    }
}

INCLUDE_ASM("boss/bo4/nonmatchings/doppleganger", func_us_801C1CB0);

INCLUDE_ASM("boss/bo4/nonmatchings/doppleganger", func_us_801C2284);

typedef enum {
    THINK_STEP_0 = 0,
    THINK_STEP_1,
    THINK_STEP_2,
    THINK_STEP_3,
    THINK_STEP_4,
    THINK_STEP_5,
    THINK_STEP_6,
    THINK_STEP_7,
    THINK_STEP_14 = 14,
    THINK_STEP_15,
    THINK_STEP_GAME_OVER,
    THINK_STEP_17,
    THINK_STEP_BACKDASH,
    THINK_STEP_WAIT,
} ThinkStep;

extern s32 D_us_801D3D24; // think_step
extern s32 D_us_801D3D28; // timer
extern s32 D_us_801D3D2C; // timer

static void DopplegangerThinking(void) {
    s32 posX;
    s32 playerDistanceX;
    u32 facingLeft;

    posX = g_Tilemap.scrollX.i.hi + DOPPLEGANGER.posX.i.hi;
    g_Dop.demo_timer = 2;
    g_Dop.padSim = PAD_NONE;

    if (g_Player.status & PLAYER_STATUS_DEAD) {
        D_us_801D3D24 = THINK_STEP_GAME_OVER;
    }
    if (g_Dop.status & PLAYER_STATUS_UNK10000) {
        D_us_801D3D24 = THINK_STEP_0;
    }
    if (g_Dop.status & PLAYER_STATUS_STONE) {
        D_us_801D3D24 = THINK_STEP_15;
    }

    if ((g_Player.timers[ALU_T_12]) &&
        (D_us_801D3D24 != THINK_STEP_GAME_OVER) &&
        !(g_Dop.status & PLAYER_STATUS_MIST_FORM)) {
        g_Dop.padSim = PAD_R2;
        D_us_801D3D28 = 64;
        D_us_801D3D24 = THINK_STEP_14;
    }

    facingLeft = false;
    if ((DOPPLEGANGER.posX.i.hi - PLAYER.posX.i.hi) >= 0) {
        facingLeft = true;
    }

    playerDistanceX = abs(DOPPLEGANGER.posX.i.hi - PLAYER.posX.i.hi);

    FntPrint("hm:%02x\n", playerDistanceX);
    FntPrint("think_step:%02x\n", D_us_801D3D24);

    switch (D_us_801D3D24) {
    case THINK_STEP_0:
        if (!(g_Dop.status & PLAYER_STATUS_UNK10000)) {
            if (g_Player.timers[ALU_T_10]) {
                if (rand() & 1) {
                    if (facingLeft) {
                        g_Dop.padSim = PAD_LEFT;
                    } else {
                        g_Dop.padSim = PAD_RIGHT;
                    }
                    g_Dop.padSim |= PAD_CROSS;
                    D_us_801D3D24 = THINK_STEP_7;
                } else {
                    g_Dop.padSim |= PAD_DOWN;
                    D_us_801D3D24 = THINK_STEP_5;
                    D_us_801D3D28 = 72;
                }
            } else if (abs(DOPPLEGANGER.posY.i.hi - PLAYER.posY.i.hi) > 32) {
                if (facingLeft) {
                    g_Dop.padSim = PAD_LEFT;
                } else {
                    g_Dop.padSim = PAD_RIGHT;
                }
                g_Dop.padSim |= PAD_CROSS;
                D_us_801D3D24 = THINK_STEP_7;
            } else if (playerDistanceX > 80) {
                if (facingLeft) {
                    g_Dop.padSim = PAD_LEFT;
                } else {
                    g_Dop.padSim = PAD_RIGHT;
                }
            } else {
                D_us_801D3D28 = 16;
                D_us_801D3D24 = THINK_STEP_1;
            }
        }
        break;

    case THINK_STEP_1:
        if (DOPPLEGANGER.facingLeft != facingLeft) {
            if (facingLeft) {
                g_Dop.padSim = PAD_LEFT;
            } else {
                g_Dop.padSim = PAD_RIGHT;
            }
        }
        if (playerDistanceX > 80) {
            D_us_801D3D24 = THINK_STEP_0;
        } else {
            if ((posX < 96 && DOPPLEGANGER.facingLeft == false) ||
                (posX > 416 && DOPPLEGANGER.facingLeft)) {
                D_us_801D3D28 = 64;
                g_Dop.padSim |= PAD_R1;
                D_us_801D3D24 = THINK_STEP_3;
                break;
            }

            if ((g_Player.timers[ALU_T_9]) ||
                ((g_Player.status & PLAYER_STATUS_CROUCH) && (rand() & 1))) {
                switch (rand() & 7) {
                case 0:
                case 6:
                case 7:
                    g_Dop.padSim |= PAD_CROSS;
                    D_us_801D3D24 = THINK_STEP_6;
                    D_us_801D3D28 = 72;
                    break;
                case 1:
                    g_Dop.padSim |= PAD_DOWN;
                    D_us_801D3D24 = THINK_STEP_5;
                    D_us_801D3D28 = 72;
                    break;
                case 2:
                    if (g_Player.status & PLAYER_STATUS_CROUCH) {
                        g_Dop.padSim |= PAD_DOWN;
                        D_us_801D3D24 = THINK_STEP_5;
                        D_us_801D3D28 = 72;
                        break;
                    }
                    // fallthrough
                case 3:
                case 4:
                case 5:
                    g_Dop.padSim |= PAD_TRIANGLE;
                    D_us_801D3D24 = THINK_STEP_2;
                    D_us_801D3D28 = 32;
                    break;
                }
            } else if (g_Player.timers[ALU_T_10]) {
                if (rand() & 1) {
                    if (facingLeft) {
                        g_Dop.padSim = PAD_LEFT;
                    } else {
                        g_Dop.padSim = PAD_RIGHT;
                    }
                    g_Dop.padSim |= PAD_CROSS;
                    D_us_801D3D24 = THINK_STEP_7;
                } else {
                    g_Dop.padSim |= PAD_DOWN;
                    D_us_801D3D24 = THINK_STEP_5;
                    D_us_801D3D28 = 72;
                }
            } else {
                if (playerDistanceX < 56) {
                    if (D_us_801D3D2C) {
                        D_us_801D3D2C--;
                    } else {

                        // n.b.! Doppleganger can get locked here
                        //       if none of the preamble conditions override the
                        //       current step. This causes him to remain in the
                        //       crouch position attacking every 32 frames. If
                        //       the player is near a door, elevated above
                        //       Doppleganger, the attack will never hit, the
                        //       distance will never change and Dop will just
                        //       keep swinging.

                        g_Dop.padSim |= PAD_SQUARE;
                        D_us_801D3D2C = 32;
                    }
                } else if (--D_us_801D3D28 == 0) {
                    g_Dop.padSim |= PAD_UP | PAD_SQUARE;
                    D_us_801D3D28 = 112;
                    D_us_801D3D2C = 32;
                }
            }
        }
        break;
    case THINK_STEP_2:
        if (--D_us_801D3D28 == 0) {
            g_Dop.padSim = PAD_UP | PAD_CIRCLE;
            D_us_801D3D24 = THINK_STEP_0;
            D_us_801D3D28 = 112;
        }
        break;

    case THINK_STEP_3:
        if (DOPPLEGANGER.step_s) {
            g_Dop.padSim = PAD_SQUARE;
            D_us_801D3D28 = 24;
            D_us_801D3D24 = THINK_STEP_4;
        }
        break;

    case THINK_STEP_4:
        if (!(g_GameTimer % 2)) {
            g_Dop.padSim = PAD_UP;
        }

        if (--D_us_801D3D28 == 0) {
            g_Dop.padSim = PAD_R1;
            D_us_801D3D24 = THINK_STEP_0;
        }
        break;

    case THINK_STEP_5:
        if ((--D_us_801D3D28 == 0) || !(g_Dop.status & PLAYER_STATUS_CROUCH)) {
            D_us_801D3D24 = THINK_STEP_0;
            D_us_801D3D2C = 32;
        }
        if (DOPPLEGANGER.facingLeft != facingLeft) {
            if (facingLeft) {
                g_Dop.padSim = PAD_LEFT;
            } else {
                g_Dop.padSim = PAD_RIGHT;
            }
        }
        g_Dop.padSim |= PAD_DOWN;
        if (playerDistanceX < 56) {
            if (D_us_801D3D2C) {
                D_us_801D3D2C--;
            } else {
                // crouch attack
                g_Dop.padSim |= PAD_DOWN | PAD_SQUARE;
                D_us_801D3D2C = 32;
            }
        }
        break;
    case THINK_STEP_6:
        if (g_Dop.vram_flag & 1) {
            D_us_801D3D24 = THINK_STEP_0;
        } else {
            g_Dop.padSim |= PAD_CROSS;
            if (!(g_GameTimer % 32)) {
                g_Dop.padSim |= PAD_UP | PAD_CIRCLE;
            }
        }
        break;
    case THINK_STEP_7:
        if (g_Dop.vram_flag & 1) {
            D_us_801D3D24 = THINK_STEP_0;
        } else {
            if (playerDistanceX > 16) {
                if (DOPPLEGANGER.facingLeft) {
                    g_Dop.padSim = PAD_LEFT;
                } else {
                    g_Dop.padSim = PAD_RIGHT;
                }
            }

            g_Dop.padSim |= PAD_CROSS;
            if (DOPPLEGANGER.velocityY > 0) {
                if (DOPPLEGANGER.velocityY > FIX(2)) {
                    g_Dop.padSim |= PAD_DOWN | PAD_SQUARE | PAD_CROSS;
                }

                if (abs(DOPPLEGANGER.posY.i.hi - PLAYER.posY.i.hi) < 16) {
                    g_Dop.padSim |= PAD_DOWN | PAD_SQUARE;
                }
            }
        }
        break;
    case THINK_STEP_14:
        if (!(g_GameTimer % 8)) {
            g_Dop.padSim = PAD_UP;
        }
        if (!(g_Dop.status & PLAYER_STATUS_MIST_FORM) && (g_GameTimer & 1)) {
            g_Dop.padSim = PAD_R2;
        }

        if (--D_us_801D3D28 == 0) {
            if (g_Dop.status & PLAYER_STATUS_MIST_FORM) {
                g_Dop.padSim = PAD_R2;
            }
            D_us_801D3D24 = THINK_STEP_0;
        }
        break;
    case THINK_STEP_15:
        if (!(g_Dop.status & PLAYER_STATUS_STONE)) {
            D_us_801D3D24 = THINK_STEP_0;
        }
        if (!(g_GameTimer & 0xF)) {
            g_Dop.padSim = PAD_UP;
        }
        break;
    case THINK_STEP_GAME_OVER:
        if (!(g_Player.status & PLAYER_STATUS_DEAD)) {
            D_us_801D3D24 = THINK_STEP_0;
        }
        g_Dop.padSim = PAD_UP;
        // transform back to doppleganger form
        if (g_Dop.status & PLAYER_STATUS_BAT_FORM) {
            g_Dop.padSim = PAD_R1;
        }
        if (g_Dop.status & PLAYER_STATUS_MIST_FORM) {
            g_Dop.padSim = PAD_R2;
        }
        break;
    case THINK_STEP_17:
        if (abs(DOPPLEGANGER.posY.i.hi - PLAYER.posY.i.hi) < 8) {
            D_us_801D3D24 = THINK_STEP_0;
        }
        break;
    case THINK_STEP_BACKDASH:
        if (DOPPLEGANGER.step == Dop_Stand) {
            // backdash
            g_Dop.padSim |= PAD_TRIANGLE;
            D_us_801D3D24 = THINK_STEP_WAIT;
            D_us_801D3D2C = 64;
        }
        break;
    case THINK_STEP_WAIT:
        if (--D_us_801D3D2C == 0) {
            D_us_801D3D24 = THINK_STEP_0;
        }
        break;
    }
}

extern EInit D_us_80180410;

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
} Unk_Dop;

extern Unk_Dop D_us_801D4DDA;

void func_us_801C37B4(Entity* self) {
    s32 i;
    Entity* entity;
    s16 hitPoints;

    D_us_801D4DDA.unk0 = DOPPLEGANGER.hitPoints;
    if (self->step == 0) {
        InitializeEntity(D_us_80180410);
        func_us_801C1A38();

        entity = &g_Entities[STAGE_ENTITY_START + 4];
        for (i = (STAGE_ENTITY_START + 4); i < (STAGE_ENTITY_START + 80); i++,
            entity++) {
            DestroyEntity(entity);
        }

        D_us_801D4DDA.unk4 = D_us_801D4DDA.unk0 = D_us_801D4DDA.unk2 =
            DOPPLEGANGER.hitPoints;

        D_us_801D4DDA.unk6 = DOPPLEGANGER.hitboxState;
        D_us_801D3D24 = THINK_STEP_BACKDASH;
        func_us_801C5354(1, 48);
    } else {
        DopplegangerThinking();
        func_us_801C2284();
        func_us_801CA014();
    }
    D_us_801D4DDA.unk2 = D_us_801D4DDA.unk0;
    FntPrint("life:%02x\n", DOPPLEGANGER.hitPoints);
}

INCLUDE_ASM("boss/bo4/nonmatchings/doppleganger", func_us_801C38C0);

INCLUDE_ASM("boss/bo4/nonmatchings/doppleganger", func_us_801C3EEC);

extern Point16 D_us_801812AC[];

void func_us_801C44C8(void) {
    Collider collider;

    s16* dopY;
    s16* dopX;
    s32 effects;
    s32 i;
    u32* pVramFlag;

    s16 offsetX, offsetY;

    dopY = &DOPPLEGANGER.posY.i.hi;
    dopX = &DOPPLEGANGER.posX.i.hi;

    pVramFlag = &g_Dop.vram_flag;
    effects =
        g_Dop.unk04 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                       EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if (effects == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID) ||
        effects == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID) ||
        effects == (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                    EFFECT_SOLID)) {
        *pVramFlag |= 4;
        return;
    }

    for (i = 0; i < 7; i++) {
        effects = g_Dop.colWall[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_UNK_0002 | EFFECT_SOLID);
        if ((effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_0002 | EFFECT_SOLID))) {

            offsetX = *dopX + D_us_801812AC[i].x + g_Dop.colWall[i].unk4 - 1;
            offsetY = *dopY + D_us_801812AC[i].y;
            g_api.CheckCollision(offsetX, offsetY, &collider, 0);

            if (!(collider.effects & EFFECT_SOLID)) {
                *pVramFlag |= 4;
                *dopX += g_Dop.colWall[i].unk4;
                return;
            }
        }

        if ((effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                EFFECT_UNK_8000 &&
            i != 0 &&
            ((g_Dop.colWall[0].effects & EFFECT_UNK_0800) ||
             !(g_Dop.colWall[0].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *pVramFlag |= 4;
            *dopX += g_Dop.colWall[i].unk4;
            return;
        }

        if ((effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                EFFECT_UNK_0800 &&
            i != 6 &&
            ((g_Dop.colWall[6].effects & EFFECT_UNK_8000) ||
             !(g_Dop.colWall[6].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *pVramFlag |= 4;
            *dopX += g_Dop.colWall[i].unk4;
            return;
        }
    }
}

extern Point16 D_us_801812AC[];

void func_us_801C4710(void) {
    Collider collider;

    s16* dopY;
    s16* dopX;
    s32 effects;
    s32 i;
    u32* pVramFlag;

    s16 offsetX, offsetY;
    dopY = &DOPPLEGANGER.posY.i.hi;
    dopX = &DOPPLEGANGER.posX.i.hi;

    pVramFlag = &g_Dop.vram_flag;
    effects =
        g_Dop.unk04 &
        (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0800 |
         EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if (effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                    EFFECT_SOLID) ||
        effects == (EFFECT_UNK_0800 | EFFECT_UNK_0400 | EFFECT_UNK_0002 |
                    EFFECT_SOLID) ||
        effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                    EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID)) {
        *pVramFlag |= 8;
        return;
    }

    for (i = 7; i < 14; i++) {
        effects = g_Dop.colWall[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_UNK_0002 | EFFECT_SOLID);
        if (effects == (EFFECT_UNK_8000 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_0800 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                        EFFECT_SOLID) ||
            effects == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                        EFFECT_SOLID) ||
            effects == (EFFECT_UNK_0002 | EFFECT_SOLID)) {

            offsetX = *dopX + D_us_801812AC[i].x + g_Dop.colWall[i].unkC + 1;
            offsetY = *dopY + D_us_801812AC[i].y;
            g_api.CheckCollision(offsetX, offsetY, &collider, 0);

            if (!(collider.effects & EFFECT_SOLID)) {
                *pVramFlag |= 8;
                *dopX += g_Dop.colWall[i].unkC;
                return;
            }
        }

        if ((effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                (EFFECT_UNK_8000 | EFFECT_UNK_4000) &&
            i != 7 &&
            ((g_Dop.colWall[7].effects & EFFECT_UNK_0800) ||
             !(g_Dop.colWall[7].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *pVramFlag |= 8;
            *dopX += g_Dop.colWall[i].unkC;
            return;
        }

        if (((effects &
              (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
             (EFFECT_UNK_4000 | EFFECT_UNK_0800)) &&
            i != 13 &&
            ((g_Dop.colWall[13].effects & EFFECT_UNK_8000) ||
             !(g_Dop.colWall[13].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *pVramFlag |= 8;
            *dopX += g_Dop.colWall[i].unkC;
            return;
        }
    }
}
