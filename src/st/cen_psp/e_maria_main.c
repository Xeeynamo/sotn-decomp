// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../cen/cen.h"

extern u16 g_EInitUnk;

// bss
s32 mar_80175958[32];
s32 mar_801759D8[32];
static ButtonComboState g_MarComboButtons[2];
static s32 D_pspeu_092E5F20;
static s32 D_pspeu_09294300;

extern s32 D_pspeu_092E5F28;

typedef enum {
    TELEPORT_CHECK_NONE = 0,
    TELEPORT_CHECK_TO_RTOP = 2,
    TELEPORT_CHECK_TO_TOP = 4
} TeleportCheck;
static TeleportCheck GetTeleportToOtherCastle(void) {
    // Is player in the pose when pressing UP?
    if (MARIA.step != PL_S_STAND || MARIA.step_s != 1) {
        return TELEPORT_CHECK_NONE;
    }

    // Check for X/Y boundaries in TOP
    if (g_StageId == STAGE_TOP) {
        if (abs((g_Tilemap.left << 8) + g_PlayerX - 8000) < 4 &&
            abs((g_Tilemap.top << 8) + g_PlayerY - 2127) < 4) {
            return TELEPORT_CHECK_TO_RTOP;
        }
    }

    // Check for X/Y boundaries in RTOP
    if (g_StageId == STAGE_RTOP) {
        if (abs((g_Tilemap.left << 8) + g_PlayerX - 8384) < 4 &&
#if defined(VERSION_PSP)
            abs((g_Tilemap.top << 8) + g_PlayerY - 14407) < 4) {
#else
            abs((g_Tilemap.top << 8) + g_PlayerY) - 14407 < 4) {
#endif
            return TELEPORT_CHECK_TO_TOP;
        }
    }

    return TELEPORT_CHECK_NONE;
}

// yOffsets
static s16 mar_80154568[] = {0, -8, -16};
static s16 func_80156DE4(void) {
    // Variables that change during execution
    Collider collider;
    s32 yvar;
    s32 collisions;
    s32 i;
    s32 xCenter;
    s32 xRight;
    s32 xLeft;
    s32 filter;

    // Values that are set once and never again (but not const for some reason)
    filter = EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID;
    xCenter = MARIA.posX.i.hi;
    xRight = MARIA.posX.i.hi + 4;
    xLeft = MARIA.posX.i.hi - 4;

    for (i = 0; i < LEN(mar_80154568); i++) {
        yvar = MARIA.posY.i.hi + mar_80154568[i];
        collisions = 0;
        g_api.CheckCollision(xCenter, yvar, &collider, 0);
        if ((collider.effects & filter) == EFFECT_SOLID) {
            collisions += 1;
        }
        g_api.CheckCollision(xRight, yvar, &collider, 0);
        if ((collider.effects & filter) == EFFECT_SOLID) {
            collisions += 1;
        }
        g_api.CheckCollision(xLeft, yvar, &collider, 0);
        if ((collider.effects & filter) == EFFECT_SOLID) {
            collisions += 1;
        }
        if (collisions != 0) {
            return i + 1;
        }
    }

    return 0;
}

static void func_pspeu_09239F50(s16** spriteParts, s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        // BUG? Is this supposed to set something?
        spriteParts[i];
    }
}

void func_pspeu_0923C2F8(void);
void MarInit(s16 initParam) {
    s32 i;
    Entity* entity;
    SpriteParts** spriteptr;
    Primitive* prim;
    s16 radius;
    s16 intensity;
    s32* memset_ptr;
    s32 memset_len;

    MARIA_Load();
    g_CurrentEntity = &MARIA;
    OVL_EXPORT(InitializeEntity)(&g_EInitUnk);
    g_CurrentEntity->unk5A = 0xC;
    MARIA.posX.val = FIX(32);
    MARIA.posY.val = FIX(32);
    MARIA.animSet = ANIMSET_PL_MARIA;
    MARIA.zPriority = g_unkGraphicsStruct.g_zEntityCenter;
    MARIA.facingLeft = 0;
    MARIA.palette = PAL_MARIA;
    MARIA.scaleY = 0x100;
    MARIA.scaleX = 0x100;
    MARIA.hitboxOffX = 0;
    MARIA.hitboxOffY = 0;
    MARIA.rotPivotY = 0x18;

    memset_len = sizeof(PlayerState) / sizeof(s32);
    memset_ptr = (s32*)&g_Maria;
    for (i = 0; i < memset_len; i++) {
        *memset_ptr++ = 0;
    }

    g_Maria.vram_flag = g_Maria.unk04 = 1;
    MarSetStand(0);
    MARIA.anim = mar_anim_stand_relax;
    g_PlayerDraw[5].enableColorBlend = 0;
    MarDebugOff();

    for (i = 0; i < LEN(mar_80175958); i++) {
        radius = (rand() & 0x3FF) + 0x100;
        intensity = (rand() & 0xFF) + 0x100;
        mar_80175958[i] = +(((rcos(radius) << 4) * intensity) >> 8);
        mar_801759D8[i] = -(((rsin(radius) << 4) * intensity) >> 7);
    }

    func_pspeu_09239F50(wpn_owl_spr, 0x16);
    func_pspeu_09239F50(wpn_turtle_spr, 8);
    func_pspeu_09239F50(wpn_cat_spr, 0x12);
    func_pspeu_09239F50(wpn_cardinal_spr, 0x14);
    func_pspeu_09239F50(wpn_dragon_spr, 0xD);
    func_pspeu_09239F50(wpn_doll_spr, 0xB);

    spriteptr = g_api.o.spriteBanks;
    spriteptr += 3;
    *spriteptr = (SpriteParts*)maria_spr; // ANIMSET_PL_MARIA
    spriteptr++;
    *spriteptr = (SpriteParts*)wpn_owl_spr; // ANIMSET_WPN_OWL
    spriteptr++;
    *spriteptr = (SpriteParts*)wpn_turtle_spr; // ANIMSET_WPN_TURTLE
    spriteptr++;
    *spriteptr = (SpriteParts*)wpn_cat_spr; // ANIMSET_WPN_CAT
    spriteptr++;
    *spriteptr = (SpriteParts*)wpn_cardinal_spr; // ANIMSET_WPN_CARDINAL
    spriteptr++;
    *spriteptr = (SpriteParts*)wpn_dragon_spr; // ANIMSET_WPN_DRAGON
    spriteptr++;
    *spriteptr = (SpriteParts*)wpn_doll_spr; // ANIMSET_WPN_DOLL

    for (entity = &MARIA_AFTERIMAGE_1, i = 0; i < 3; i++, entity++) {
        DestroyEntity(entity);
        entity->animSet = ANIMSET_PL_MARIA;
        entity->unk5A = i + 0xD;
        entity->palette = PAL_MARIA;
        entity->flags = FLAG_UNK_20000 | FLAG_POS_CAMERA_LOCKED;
    }

    MARIA_AFTERIMAGE_1.primIndex = g_api.AllocPrimitives(PRIM_TILE, 6);
    MARIA_AFTERIMAGE_1.flags |= FLAG_HAS_PRIMS;
    prim = &g_PrimBuf[MARIA_AFTERIMAGE_1.primIndex];

    // nb. use of i here seems unnecessary
    for (i = 0; prim != NULL; i++, prim = prim->next) {
        prim->drawMode = DRAW_UNK_100 | DRAW_UNK02 | DRAW_HIDE;
    }

    if (D_80097C98 == 6) {
        MarCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_TELEPORT, 1), 0);
        MarSetInit(1);
    }

    if (D_80097C98 == 4) {
        MarCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_TELEPORT, 3), 0);
        MarSetInit(3);
    }

    if (D_80097C98 == 5) {
        MarCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_TELEPORT, 5), 0);
        MarSetInit(5);
    }

    MarLoadPalettes();
    MarLoadGraphics();
    D_pspeu_092E5F20 = 30;
    func_pspeu_0923C2F8();
}

static void CheckStageCollision(s32 arg0) {
    Collider collider;
    s32 i;
    s16 posX;
    s16 posY;
    s32 status;
    s32* unk04_ptr;
    s32 velocityX;
    s32* vram_ptr;

    vram_ptr = &g_Maria.vram_flag;
    unk04_ptr = &g_Maria.unk04;
    *unk04_ptr = *vram_ptr;
    *vram_ptr = 0;
    status = g_Maria.status;

    if (arg0) {
        for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
            if (status & PLAYER_STATUS_CROUCH) {
                if (status & PLAYER_STATUS_UNK80000000) {
                    g_MarSensorsFloor[i].y = D_pspeu_092C51A0[i];
                    g_MarSensorsCeiling[i].y = D_pspeu_092C5198[i];
                } else {
                    g_MarSensorsFloor[i].y = g_MarSensorsFloorDefault[i];
                    g_MarSensorsCeiling[i].y = g_MarSensorsCeilingCrouch[i];
                }
            } else {
                g_MarSensorsFloor[i].y = g_MarSensorsFloorDefault[i];
                g_MarSensorsCeiling[i].y = g_MarSensorsCeilingDefault[i];
            }
        }

        for (i = 0; i < NUM_VERTICAL_SENSORS; i++) {
            if (status & PLAYER_STATUS_CROUCH) {
                if (status & PLAYER_STATUS_UNK80000000) {
                    g_MarSensorsWall[i].y = D_pspeu_092C51A8[i];
                    g_MarSensorsWall[i + NUM_VERTICAL_SENSORS].y =
                        D_pspeu_092C51A8[i];
                } else {
                    g_MarSensorsWall[i].y = g_MarSensorsWallCrouch[i];
                    g_MarSensorsWall[i + NUM_VERTICAL_SENSORS].y =
                        g_MarSensorsWallCrouch[i];
                }
            } else {
                g_MarSensorsWall[i].y = g_MarSensorsWallDefault[i];
                g_MarSensorsWall[i + NUM_VERTICAL_SENSORS].y =
                    g_MarSensorsWallDefault[i];
            }
        }
    }

    velocityX = MARIA.velocityX;
    if (MARIA.velocityX < 0 && !(*unk04_ptr & 8)) {
        if ((*unk04_ptr & 0xF000) == 0xC000) {
            velocityX = (velocityX * 10) / 16;
        }

        if ((*unk04_ptr & 0xF000) == 0xD000) {
            velocityX = (velocityX * 13) / 16;
        }
        MARIA.posX.val = (MARIA.posX.val + velocityX);
    }
    if (MARIA.velocityX > 0 && !(*unk04_ptr & 4)) {
        if ((*unk04_ptr & 0xF000) == 0x8000) {
            velocityX = (velocityX * 10) / 16;
        }
        if ((*unk04_ptr & 0xF000) == 0x9000) {
            velocityX = (velocityX * 13) / 16;
        }
        MARIA.posX.val += velocityX;
    }
    if (MARIA.velocityY < 0 && !(*unk04_ptr & 2)) {
        MARIA.posY.val += MARIA.velocityY;
    }

    if (MARIA.velocityY > 0 && !(*unk04_ptr & 1)) {
        MARIA.posY.val += MARIA.velocityY;
    }

    for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
        posX = MARIA.posX.i.hi + g_MarSensorsFloor[i].x;
        posY = MARIA.posY.i.hi + g_MarSensorsFloor[i].y;
        g_api.CheckCollision(posX, posY, &g_Maria.colFloor[i], 0);
        if (g_Maria.timers[PL_T_7] &&
            (g_Maria.colFloor[i].effects & EFFECT_SOLID_FROM_ABOVE)) {
            g_api.CheckCollision(posX, posY + 0xC, &collider, 0);
            if (!(collider.effects & EFFECT_SOLID)) {
                g_Maria.colFloor[i].effects = EFFECT_NONE;
            }
        }
    }

    MarCheckFloor();

    for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
        posX = MARIA.posX.i.hi + g_MarSensorsCeiling[i].x;
        posY = MARIA.posY.i.hi + g_MarSensorsCeiling[i].y;
        g_api.CheckCollision(posX, posY, &g_Maria.colCeiling[i], 0);
    }

    MarCheckCeiling();
    if ((*vram_ptr & 1) && MARIA.velocityY >= 0) {
        MARIA.posY.i.lo = 0;
    }

    if ((*vram_ptr & 2) && MARIA.velocityY <= 0) {
        MARIA.posY.i.lo = 0;
    }

    for (i = 0; i < NUM_VERTICAL_SENSORS * 2; i++) {
        posX = MARIA.posX.i.hi + g_MarSensorsWall[i].x;
        posY = MARIA.posY.i.hi + g_MarSensorsWall[i].y;
        g_api.CheckCollision(posX, posY, &g_Maria.colWall[i], 0);
    }

    MarCheckWallRight();
    MarCheckWallLeft();

    if ((*vram_ptr & 4) && MARIA.velocityX > 0) {
        MARIA.posX.i.lo = 0;
    }

    if ((*vram_ptr & 8) && MARIA.velocityX < 0) {
        MARIA.posX.i.lo = 0;
    }
}

static void CheckBladeDashInput(void) {
    s32 pressed;
    s32 up;
    s32 down;
    s32 forward;
    s32 down_forward;

    pressed = g_Maria.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    if (MARIA.facingLeft == 0) {
        down_forward = PAD_DOWN | PAD_RIGHT;
        forward = PAD_RIGHT;
    } else {
        down_forward = PAD_DOWN | PAD_LEFT;
        forward = PAD_LEFT;
    }
    up = PAD_UP;
    down = PAD_DOWN;

    switch (g_MarComboButtons[0].buttonsCorrect) {
    case 0:
        if (g_Maria.padTapped == up) {
            g_MarComboButtons[0].timer = 20;
            g_MarComboButtons[0].buttonsCorrect++;
        }
        break;
    case 1:
        if (pressed == down) {
            g_MarComboButtons[0].timer = 20;
            g_MarComboButtons[0].buttonsCorrect++;
            break;
        }
        if (--g_MarComboButtons[0].timer == 0) {
            g_MarComboButtons[0].buttonsCorrect = 0;
        }
        break;
    case 2:
        if (pressed == down_forward) {
            g_MarComboButtons[0].timer = 20;
            g_MarComboButtons[0].buttonsCorrect++;
            break;
        }
        if (--g_MarComboButtons[0].timer == 0) {
            g_MarComboButtons[0].buttonsCorrect = 0;
        }
        break;
    case 3:
        if (--g_MarComboButtons[0].timer == 0) {
            g_MarComboButtons[0].buttonsCorrect = 0;
        }
        if (MARIA.step == PL_S_STAND || MARIA.step == PL_S_WALK ||
            MARIA.step == PL_S_CROUCH || MARIA.step == PL_S_JUMP ||
            MARIA.step == PL_S_FALL) {
            if (g_Maria.unk72) {
                g_MarComboButtons[0].buttonsCorrect = 0;
            } else if (!g_Maria.unk46 && (g_Maria.padTapped & PAD_SQUARE)) {
                MarSetBladeDash();
            }
        }
        break;
    }
}

static void CheckHighJumpInput(void) {
    switch (g_MarComboButtons[1].buttonsCorrect) {
    case 0:
        if (g_Maria.padTapped & PAD_DOWN) {
            if (g_Maria.padHeld == 0) {
                g_MarComboButtons[1].timer = 16;
                g_MarComboButtons[1].buttonsCorrect++;
                return;
            }
        }
        break;
    case 1:
        if (g_Maria.padTapped & PAD_UP) {
            g_MarComboButtons[1].timer = 16;
            g_MarComboButtons[1].buttonsCorrect++;
            return;
        }
        if (--g_MarComboButtons[1].timer == 0) {
            g_MarComboButtons[1].buttonsCorrect = 0;
        }
        break;
    case 2:
        if (g_MarComboButtons[1].timer && --g_MarComboButtons[1].timer == 0) {
            g_MarComboButtons[1].buttonsCorrect = 0;
            return;
        }
        if ((g_Maria.padTapped & PAD_CROSS) && !g_Maria.unk46) {
            if (MARIA.step == PL_S_CROUCH || MARIA.step == PL_S_STAND ||
                (MARIA.step == PL_S_JUMP && MARIA.velocityY > FIX(1)) ||
                MARIA.step == PL_S_FALL) {
                if (g_Maria.unk72) {
                    g_MarComboButtons[1].buttonsCorrect = 0;
                } else {
                    MarSetHighJump();
                    g_MarComboButtons[1].buttonsCorrect = 0;
                }
            }
        }
        break;
    }
}

static u16 mar_80154574[] = {
    PAL_UNK_812F, PAL_UNK_812F, PAL_MARIA,    PAL_UNK_812F, PAL_UNK_812F,
    PAL_MARIA,    PAL_UNK_812F, PAL_UNK_812F, PAL_MARIA,    PAL_UNK_812F,
    PAL_UNK_812E, PAL_UNK_812F, PAL_UNK_812E, PAL_UNK_812F, PAL_MARIA};

#include "../cen/gen/maria.h"
void MarMain(void) {
    s32 sp40[4];
    s32 posX;
    s32 posY;
    s32 vramFlag;

    PlayerDraw* playerDraw;
    s16 angle;
    s32 i;
    s32 newStatus;
    s16 step;
    s16 step_s;
    s32 var_s8;
    s32 damageEffects;
    s32 damageKind;

    var_s8 = 0;
    g_CurrentEntity = &MARIA;
    playerDraw = &g_PlayerDraw[5];
    damageEffects = 0;
    damageKind = 0;

    if (g_Maria.unk78) {
        // this is new to the maria overlay
        g_Maria.unk7A = 0;
        g_Maria.unk5C = 0;
        g_Maria.unk78 = 0;
    }

    g_Maria.unk4C = 0;
    g_Maria.unk72 = func_80156DE4();
    if (!(g_Maria.status & PLAYER_STATUS_DEAD)) {
        if (MARIA.step != PL_S_DEAD && (MARIA.flags & FLAG_DEAD)) {
            D_pspeu_09294300 |= 1;
            step = MARIA.step;
            step_s = MARIA.step_s;
            sp40[0] = mar_80154574[g_CurrentEntity->nFramesInvincibility];
            MarSetStep(PL_S_DEAD);
        } else {
            for (i = 0; i < LEN(g_Maria.timers); i++) {
                if (!g_Maria.timers[i]) {
                    continue;
                }

                switch (i) {
                case PL_T_POISON:
                case PL_T_CURSE:
                    break;
                case PL_T_2:
                    MARIA.palette = g_Maria.damagePalette;
                    break;
                case PL_T_3:
                    break;
                case PL_T_4:
                    angle = (g_GameTimer & 0xF) * 256;
                    playerDraw->r0 = playerDraw->g0 = playerDraw->b0 =
                        ((rsin(angle) + 0x1000) / 64) + 0x60;
                    angle += 0x200;
                    playerDraw->r1 = playerDraw->g1 = playerDraw->b1 =
                        ((rsin(angle) + 0x1000) / 64) + 0x60;
                    angle += 0x200;
                    playerDraw->r3 = playerDraw->g3 = playerDraw->b3 =
                        ((rsin(angle) + 0x1000) / 64) + 0x60;
                    angle += 0x200;
                    playerDraw->r2 = playerDraw->g2 = playerDraw->b2 =
                        ((rsin(angle) + 0x1000) / 64) + 0x60;
                    playerDraw->enableColorBlend = 1;
                    break;
                case PL_T_5:
                case PL_T_6:
                case PL_T_7:
                case PL_T_8:
                case PL_T_ATTACK:
                case PL_T_10:
                case PL_T_RUN:
                case PL_T_12:
                case PL_T_INVINCIBLE_SCENE:
                case PL_T_INVINCIBLE:
                    // removed compared to RIC, as Maria does not have a
                    // prologue
                    break;
                case PL_T_AFTERIMAGE_DISABLE:
                    MarDisableAfterImage(0, 0);
                    break;
                }

                if (--g_Maria.timers[i] != 0) {
                    continue;
                }

                switch (i) {
                case PL_T_POISON:
                case PL_T_CURSE:
                    break;
                case PL_T_2:
                    MARIA.palette = PAL_FLAG(0x130);
                    break;
                case PL_T_3:
                    break;
                case PL_T_4:
                    playerDraw->enableColorBlend = 0;
                    break;
                case PL_T_5:
                    break;
                case PL_T_6:
                    if (MARIA.step == PL_S_FALL && MARIA.anim != mar_80155534) {
                        MarSetAnimation(mar_80155534);
                        g_Maria.unk44 &= ~0x10;
                    }
                    break;
                case PL_T_7:
                case PL_T_8:
                case PL_T_ATTACK:
                case PL_T_10:
                case PL_T_RUN:
                case PL_T_12:
                case PL_T_INVINCIBLE_SCENE:
                case PL_T_INVINCIBLE:
                    break;
                case PL_T_AFTERIMAGE_DISABLE:
                    func_maria_8015CC28();
                    break;
                }
            }

            g_Maria.padHeld = g_Maria.padPressed;
            if (g_Maria.demo_timer) {
                g_Maria.demo_timer--;
                g_Maria.padPressed = g_Maria.padSim;
            } else {
                g_Maria.padPressed = g_pads[0].pressed;
#ifdef VERSION_PSP
                if (D_pspeu_092E5F20 > 0) {
                    D_pspeu_092E5F20--;
                    g_Maria.padPressed = 0;
                }
#endif
            }

            g_Maria.padTapped =
                g_Maria.padPressed & (g_Maria.padHeld ^ g_Maria.padPressed);
            if (MARIA.step != PL_S_DEAD) {
                // Reuse the i variable here even though we aren't iterating
                i = GetTeleportToOtherCastle();
                if (i != TELEPORT_CHECK_NONE) {
                    MarSetInit(i);
                }

                if (MARIA.step != PL_S_INIT) {
                    if (g_DebugPlayer && MarDebug()) {
                        return;
                    }

                    if (g_Maria.unk56) {
                        // this block is exclusive to Maria
                        g_Status.hp += g_Maria.unk58;
                        func_800FE8F0();
                        func_pspeu_092BEAB0(g_Maria.unk58);
                        if (g_Status.hpMax < g_Status.hp) {
                            g_Status.hp = g_Status.hpMax;
                        }
                        g_Maria.unk56 = 0;
                    }

                    if (!(g_Maria.timers[PL_T_INVINCIBLE_SCENE] |
                          g_Maria.timers[PL_T_INVINCIBLE]) &&
                        g_Maria.unk60 < 2) {
                        if (g_Maria.unk60 == 1) {
                            step = MARIA.step;
                            step_s = MARIA.step_s;
                            MarSetStep(PL_S_BOSS_GRAB);
                        } else if (g_CurrentEntity->hitFlags > 0 &&
                                   g_CurrentEntity->hitFlags < 4) {
                            step = MARIA.step;
                            step_s = MARIA.step_s;
                            sp40[0] = mar_80154574[g_CurrentEntity
                                                       ->nFramesInvincibility];
                            if (g_Maria.unk6C - g_Maria.unk6A >= 0xA) {
                                sp40[1] = 3;
                            } else {
                                sp40[1] = 2;
                            }

                            i = 3;
                            if (sp40[0] & 0x200) {
                                i = 7;
                            }

                            if (MARIA.step == PL_S_11) {
                                i = 8;
                            }

                            switch (i) {
                            case 0:
                            case 1:
                            case 2:
                                break;
                            case 3:
                                MarSetStep(PL_S_HIT);
                                break;
                            case 4:
                            case 5:
                            case 6:
                                break;
                            case 7:
                                MarSetStep(PL_S_11);
                                break;
                            case 8:
                                // Looks unused / copied from Doppleganger's
                                // stone state?
                                var_s8 = 1;
                                break;
                            case 9:
                                break;
                            }
                        }
                    }
                    goto check_input_combo;
                }
            } else {
            check_input_combo:
                CheckBladeDashInput();
                CheckHighJumpInput();
            }
        }
    }

    g_Maria.prev_step = MARIA.step;
    g_Maria.prev_step_s = MARIA.step_s;
    switch (MARIA.step) {
    case PL_S_STAND:
        MarStepStand();
        break;
    case PL_S_WALK:
        MarStepWalk();
        break;
    case PL_S_CROUCH:
        MarStepCrouch();
        break;
    case PL_S_FALL:
        MarStepFall();
        break;
    case PL_S_JUMP:
        MarStepJump();
        break;
    case PL_S_HIGHJUMP:
        MarStepHighJump();
        break;
    case PL_S_HIT:
        MarStepHit(damageEffects, damageKind, step, step_s);
        break;
    case PL_S_BOSS_GRAB:
        MarStepBossGrab();
        break;
    case PL_S_DEAD:
        MarStepDead(damageEffects, damageKind, step, step_s);
        break;
    case PL_S_18:
        func_pspeu_092B0C70();
        break;
    case PL_S_CARDINAL_CRASH:
        MarStepCardinalCrash();
        break;
    case PL_S_CAT_CRASH:
        MarStepCatCrash();
        break;
    case PL_S_TURTLE_CRASH:
        MarStepTurtleCrash();
        break;
    case PL_S_DRAGON_CRASH:
        MarStepDragonCrash();
        break;
    case PL_S_CARDINAL_ATTACK:
        MarStepCardinalAttack();
        break;
    case PL_S_SLIDE:
        MarStepSlide();
        break;
    case PL_S_RUN:
        MarStepRun();
        break;
    case PL_S_BLADEDASH:
        MarStepBladeDash();
        break;
    case PL_S_INIT:
        MarStepTeleport();
        break;
    }

    g_Maria.unk08 = g_Maria.status;
    newStatus = 0;
    switch (MARIA.step) {
    case PL_S_STAND:
        newStatus = NO_AFTERIMAGE;
        break;
    case PL_S_WALK:
        newStatus = NO_AFTERIMAGE;
        break;
    case PL_S_CROUCH:
        newStatus = NO_AFTERIMAGE;
        if (MARIA.step_s != 2) {
            newStatus = NO_AFTERIMAGE | PLAYER_STATUS_CROUCH;
        }
        break;
    case PL_S_FALL:
        newStatus = NO_AFTERIMAGE | PLAYER_STATUS_UNK2000;
        break;
    case PL_S_JUMP:
        newStatus = NO_AFTERIMAGE | PLAYER_STATUS_UNK2000;
        break;
    case PL_S_HIGHJUMP:
        break;
    case PL_S_HIT:
        newStatus = NO_AFTERIMAGE | PLAYER_STATUS_UNK10000;
        MarSetInvincibilityFrames(1, 16);
        break;
    case PL_S_BOSS_GRAB:
        newStatus = PLAYER_STATUS_UNK100000 | PLAYER_STATUS_UNK10000 |
                    PLAYER_STATUS_UNK40;
        MarSetInvincibilityFrames(1, 16);
        break;
    case PL_S_DEAD:
        newStatus = NO_AFTERIMAGE | PLAYER_STATUS_DEAD | PLAYER_STATUS_UNK10000;
        if (MARIA.step_s == 0x80) {
            newStatus |= PLAYER_STATUS_UNK80000;
        }
        MarSetInvincibilityFrames(1, 16);
        break;
    case PL_S_CARDINAL_CRASH:
    case PL_S_CAT_CRASH:
    case PL_S_TURTLE_CRASH:
    case PL_S_DRAGON_CRASH:
    case PL_S_18:
        newStatus = 0x08000000;
        MarSetInvincibilityFrames(1, 16);
        break;
    case PL_S_CARDINAL_ATTACK:
        break;
    case PL_S_SLIDE:
        newStatus = 0x20;
        break;
    case PL_S_RUN:
        newStatus = 0x80000020;
        break;
    case PL_S_BLADEDASH:
        break;
    case PL_S_INIT:
        newStatus = NO_AFTERIMAGE;
        MarSetInvincibilityFrames(1, 16);
        break;
    }

    if (g_Maria.timers[PL_T_ATTACK]) {
        newStatus |= PLAYER_STATUS_UNK400;
    }

    if (g_Maria.timers[PL_T_10]) {
        newStatus |= PLAYER_STATUS_SUBWPN;
    }

    if (g_Maria.timers[PL_T_12]) {
        newStatus |= PLAYER_STATUS_SPELLCAST;
    }

    if (g_unkGraphicsStruct.D_80097448 != 0) {
        newStatus |= PLAYER_STATUS_UNK20000;
    }

    newStatus |= PLAYER_STATUS_UNK10000000;
    g_Maria.status = newStatus;

    if ((g_Maria.unk08 & PLAYER_STATUS_UNK10000) &&
        !(g_Maria.status & PLAYER_STATUS_UNK10000)) {
        MarSetInvincibilityFrames(1, 16);
        g_Maria.timers[PL_T_4] = 0x10;
        MARIA.palette = PAL_MARIA;
    }

    if (newStatus & NO_AFTERIMAGE) {
        MarDisableAfterImage(1, 4);
    }

    if ((g_Maria.timers[PL_T_INVINCIBLE_SCENE] |
         g_Maria.timers[PL_T_INVINCIBLE]) != 0) {
        g_Maria.status |= PLAYER_STATUS_INVINCIBLE;
    }

    g_api.UpdateAnim(mar_80155964, mar_8015538C);
    if (g_Maria.status & PLAYER_STATUS_DEAD) {
        MARIA.hitboxState = 0;
    } else {
        MARIA.hitboxState = 0x33;
        if (g_Maria.status & PLAYER_STATUS_STONE) {
            MARIA.hitboxState &= 0xFFCF;
        }

        if ((g_Maria.timers[PL_T_INVINCIBLE_SCENE] |
             g_Maria.timers[PL_T_INVINCIBLE]) != 0) {
            MARIA.hitboxState = 0;
        }
    }

    MARIA.hitParams = 0;
    if (MARIA.anim == mar_801556C4) {
        MARIA.palette = mar_80154574[MARIA.pose];
    }

    if (g_Maria.status & (PLAYER_STATUS_UNK40 | PLAYER_STATUS_UNK10)) {
        return;
    }
    InitMariaAfterImage();
    if (g_unkGraphicsStruct.D_80097448 > 0x28 &&
        !g_CurrentEntity->nFramesInvincibility) {
        MARIA.velocityY = (MARIA.velocityY * 3) / 4;
        MARIA.velocityX = (MARIA.velocityX * 3) / 4;
    }

    posX = MARIA.posX.val;
    posY = MARIA.posY.val;
    vramFlag = g_Maria.vram_flag;
    if (abs(MARIA.velocityY) > FIX(2) || abs(MARIA.velocityX) > FIX(2)) {
        MARIA.velocityX >>= 2;
        MARIA.velocityY >>= 2;

        if (MARIA.posY.i.hi >= 0) {
            CheckStageCollision(1);
        }

        if (MARIA.posY.i.hi >= 0) {
            CheckStageCollision(0);
        }

        if (MARIA.posY.i.hi >= 0) {
            CheckStageCollision(0);
        }

        if (MARIA.posY.i.hi >= 0) {
            CheckStageCollision(0);
        }

        if (MARIA.posY.i.hi < 0) {
            MARIA.posY.val = FIX(-1);
        }

        MARIA.velocityX *= 4;
        MARIA.velocityY *= 4;
    } else {
        CheckStageCollision(1);
    }

    g_Maria.unk04 = vramFlag;
    if (g_unkGraphicsStruct.D_80097448 > 0x28 &&
        !g_CurrentEntity->nFramesInvincibility) {
        MARIA.velocityY = (MARIA.velocityY * 4) / 3;
        MARIA.velocityX = (MARIA.velocityX * 4) / 3;
    }
    g_CurrentEntity->nFramesInvincibility = 0;
    DrawMariaAfterImage();
}

void func_pspeu_0923C2F8(void) {
    g_CurrentEntity->flags = FLAG_POS_CAMERA_LOCKED;
    g_CurrentEntity->animSet = ANIMSET_PL_MARIA;
    g_CurrentEntity->animCurFrame = 1;
    MARIA.posX.i.hi = 0x138 - g_Tilemap.scrollX.i.hi;
    MARIA.posY.i.hi = 0x1C7 - g_Tilemap.scrollY.i.hi;
    g_CurrentEntity->palette = 0x210;
    g_CurrentEntity->zPriority = 0x80;
    g_Maria.unk6E = g_Maria.unk6A = g_Maria.unk6C = MARIA.hitPoints;
}
