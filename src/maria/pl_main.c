// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

#include "../get_lang.h"

#include "../destroy_entity.h"

s32 mar_80175958[32];
s32 mar_801759D8[32];
static ButtonComboState g_MarComboButtons[2];
static s32 D_pspeu_092E5F28;
static s32 D_pspeu_092E5F20;

typedef enum {
    TELEPORT_CHECK_NONE = 0,
    TELEPORT_CHECK_TO_RTOP = 2,
    TELEPORT_CHECK_TO_TOP = 4
} TeleportCheck;
static TeleportCheck GetTeleportToOtherCastle(void) {
    // Is player in the pose when pressing UP?
    if (PLAYER.step != PL_S_STAND || PLAYER.step_s != 1) {
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
    xCenter = PLAYER.posX.i.hi;
    xRight = PLAYER.posX.i.hi + 4;
    xLeft = PLAYER.posX.i.hi - 4;

    for (i = 0; i < LEN(mar_80154568); i++) {
        yvar = PLAYER.posY.i.hi + mar_80154568[i];
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

static u8 font_eu[] = {
#include "gen/font_eu.h"
};
static u_long* g_FontImage[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x380, 128, 128, font_eu),
    GFX_TERMINATE(),
};

static u8 hud_sp[] = {
#include "gen/hud_sp.h"
};
static u8 hud_it[] = {
#include "gen/hud_it.h"
};
static u8 hud_ge[] = {
#include "gen/hud_ge.h"
};
static u8 hud_fr[] = {
#include "gen/hud_fr.h"
};
static u_long* g_HudImage[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x2C0, 128, 128, hud_sp),
    GFX_TERMINATE(),
};

// Similar to of AluInit and RicInit
void MarInit(s16 initParam) {
    Entity* e;
    s16 radius;
    s16 intensity;
    Primitive* prim;
    s32 i;
    SpriteParts** spriteptr;
    s32* memset_ptr;
    s32 memset_len;
#ifndef VERSION_PSP
    Entity* g_CurrentEntity;
#endif

    g_CurrentEntity = &PLAYER;
    DestroyEntity(g_CurrentEntity);
    PLAYER.posX.val = FIX(32);
    PLAYER.posY.val = FIX(32);
    PLAYER.animSet = ANIMSET_OVL(0x10);
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter;
    PLAYER.facingLeft = 0;
    PLAYER.palette = PAL_MARIA;
    PLAYER.scaleY = 0x100;
    PLAYER.scaleX = 0x100;
    PLAYER.hitboxOffX = 0;
    PLAYER.hitboxOffY = 0;
    PLAYER.rotPivotY = 0x18;
    memset_len = sizeof(PlayerState) / sizeof(s32);
    memset_ptr = (s32*)&g_Player;
    for (i = 0; i < memset_len; i++) {
        *memset_ptr++ = 0;
    }
    g_Player.vram_flag = g_Player.unk04 = 1;
    MarSetStand(0);
    PLAYER.anim = mar_anim_stand_relax;
    g_PlayerDraw->enableColorBlend = 0;
    MarDebugOff();
    for (i = 0; i < LEN(mar_80175958); i++) {
        radius = (rand() & 0x3FF) + 0x100;
        intensity = (rand() & 0xFF) + 0x100;
        mar_80175958[i] = +(((rcos(radius) << 4) * intensity) >> 8);
        mar_801759D8[i] = -(((rsin(radius) << 4) * intensity) >> 7);
    }
    spriteptr = g_api.o.spriteBanks;
    spriteptr += 0x10;
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
    for (e = &g_Entities[E_AFTERIMAGE_1], i = 0; i < 3; i++, e++) {
        DestroyEntity(e);
        e->animSet = ANIMSET_OVL(0x10);
        e->unk5A = i + 1;
        e->palette = PAL_MARIA;
        e->flags = FLAG_UNK_20000 | FLAG_POS_CAMERA_LOCKED;
    }
    g_Entities[E_AFTERIMAGE_1].primIndex = g_api.AllocPrimitives(PRIM_TILE, 6);
    g_Entities[E_AFTERIMAGE_1].flags |= FLAG_HAS_PRIMS;
    for (prim = &g_PrimBuf[g_Entities[E_AFTERIMAGE_1].primIndex], i = 0;
         prim != NULL; i++, prim = prim->next) {
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
#ifdef VERSION_PSP
    // ifdef'fed for the same reason in RicInit
    D_pspeu_092E5F20 = 30;

    func_91040A0(g_FontImage);
    g_HudImage[3] = (u_long*)GetLang(NULL, hud_fr, hud_sp, hud_ge, hud_it);
    if (g_HudImage[3]) {
        func_91040A0(g_HudImage);
    }
#endif
    func_90E4C68();
}

static void CheckStageCollision(bool arg0) {
    Collider collider;
    s16 argX;
    s16 argY;
    s32 xVel;
    s32 i;
    s32 j;
    s32* vram_ptr;
    s32* unk04_ptr;
    s32 status;

    vram_ptr = &g_Player.vram_flag;
    unk04_ptr = &g_Player.unk04;
    *unk04_ptr = *vram_ptr;
    *vram_ptr = 0;
    status = g_Player.status;

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
    xVel = PLAYER.velocityX;
    if (PLAYER.velocityX < 0) {
        if (!(*unk04_ptr & 8)) {
            if ((*unk04_ptr & 0xF000) == 0xC000) {
                xVel = xVel * 10 / 16;
            }
            if ((*unk04_ptr & 0xF000) == 0xD000) {
                xVel = xVel * 13 / 16;
            }
            PLAYER.posX.val += xVel;
        }
    }
    if (PLAYER.velocityX > 0) {
        if (!(*unk04_ptr & 4)) {
            if ((*unk04_ptr & 0xF000) == 0x8000) {
                xVel = xVel * 10 / 16;
            }
            if ((*unk04_ptr & 0xF000) == 0x9000) {
                xVel = xVel * 13 / 16;
            }
            PLAYER.posX.val += xVel;
        }
    }
    if ((PLAYER.velocityY < 0) && !(*unk04_ptr & 2)) {
        PLAYER.posY.val += PLAYER.velocityY;
    }
    if ((PLAYER.velocityY > 0) && !(*unk04_ptr & 1)) {
        PLAYER.posY.val += PLAYER.velocityY;
    }
    for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
        argX = PLAYER.posX.i.hi + g_MarSensorsFloor[i].x;
        argY = PLAYER.posY.i.hi + g_MarSensorsFloor[i].y;
        g_api.CheckCollision(argX, argY, &g_Player.colFloor[i], 0);
        if (g_Player.timers[PL_T_7] &&
            (g_Player.colFloor[i].effects & EFFECT_SOLID_FROM_ABOVE)) {
            g_api.CheckCollision(argX, argY + 0xC, &collider, 0);
            if (!(collider.effects & EFFECT_SOLID)) {
                g_Player.colFloor[i].effects = EFFECT_NONE;
            }
        }
    }
    MarCheckFloor();
    for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
        argX = PLAYER.posX.i.hi + g_MarSensorsCeiling[i].x;
        argY = PLAYER.posY.i.hi + g_MarSensorsCeiling[i].y;
        g_api.CheckCollision(argX, argY, &g_Player.colCeiling[i], 0);
    }
    MarCheckCeiling();
    if ((*vram_ptr & 1) && (PLAYER.velocityY >= 0)) {
        PLAYER.posY.i.lo = 0;
    }
    if ((*vram_ptr & 2) && (PLAYER.velocityY <= 0)) {
        PLAYER.posY.i.lo = 0;
    }
    for (i = 0; i < NUM_VERTICAL_SENSORS * 2; i++) {
        argX = PLAYER.posX.i.hi + g_MarSensorsWall[i].x;
        argY = PLAYER.posY.i.hi + g_MarSensorsWall[i].y;
        g_api.CheckCollision(argX, argY, &g_Player.colWall[i], 0);
    }
    MarCheckWallRight();
    MarCheckWallLeft();
    if ((*vram_ptr & 4) && (PLAYER.velocityX > 0)) {
        PLAYER.posX.i.lo = 0;
    }
    if ((*vram_ptr & 8) && (PLAYER.velocityX < 0)) {
        PLAYER.posX.i.lo = 0;
    }
}

static void CheckBladeDashInput(void) {
    s32 pressed;
    s32 up;
    s32 down;
    s32 forward;
    s32 down_forward;

    pressed = g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    if (PLAYER.facingLeft == 0) {
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
        if (g_Player.padTapped == up) {
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
        if (PLAYER.step == PL_S_STAND || PLAYER.step == PL_S_WALK ||
            PLAYER.step == PL_S_CROUCH || PLAYER.step == PL_S_JUMP ||
            PLAYER.step == PL_S_FALL) {
            if (g_Player.unk72) {
                g_MarComboButtons[0].buttonsCorrect = 0;
            } else if (!g_Player.unk46 && (g_Player.padTapped & PAD_SQUARE)) {
                MarSetBladeDash();
            }
        }
        break;
    }
}

static void CheckHighJumpInput(void) {
    switch (g_MarComboButtons[1].buttonsCorrect) {
    case 0:
        if (g_Player.padTapped & PAD_DOWN) {
            if (g_Player.padHeld == 0) {
                g_MarComboButtons[1].timer = 16;
                g_MarComboButtons[1].buttonsCorrect++;
                return;
            }
        }
        break;
    case 1:
        if (g_Player.padTapped & PAD_UP) {
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
        if (g_Player.padTapped & PAD_CROSS) {
            if (PLAYER.step == PL_S_CROUCH || PLAYER.step == PL_S_STAND ||
                (PLAYER.step == PL_S_JUMP && PLAYER.velocityY > FIX(1)) ||
                PLAYER.step == PL_S_FALL) {
                if (g_Player.unk72) {
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
// the main difference with Richter is that every code related to how Richter
// survives at 0hp during the prologue, it's removed.
void MarMain(void) {
    s16 angle;
    s32 i;
    s32 newStatus;
    s32 damageEffects;
    s16 playerStep;
    s16 playerStepS;
    s32 damageKind;
    bool isDamageTakenDeadly;
    PlayerDraw* draw;
    DamageParam damage;
    int posX;
    int posY;
    s32 vramFlag;
    s32 temp;

    g_CurrentEntity = &PLAYER;
    draw = &g_PlayerDraw[0];
    if (g_Player.unk78) {
        // this is new to the maria overlay
        g_Player.unk7A = 0;
        g_Player.unk5C = 0;
        g_Player.unk78 = 0;
    }
    damageEffects = 0;
    g_Player.unk4C = 0;
    g_Player.unk72 = func_80156DE4();
    for (i = 0; i < LEN(g_Player.timers); i++) {
        if (!g_Player.timers[i]) {
            continue;
        }
        switch (i) {
        case PL_T_POISON:
        case PL_T_CURSE:
        case PL_T_3:
        case PL_T_5:
        case PL_T_6:
        case PL_T_7:
        case PL_T_8:
        case PL_T_ATTACK:
        case PL_T_10:
        case PL_T_RUN:
        case PL_T_12:
        case PL_T_INVINCIBLE:
            break;
        case PL_T_2:
            PLAYER.palette = g_Player.damagePalette;
            break;
        case PL_T_4: {
            angle = (g_GameTimer & 0xF) * 256;
            draw->r0 = draw->g0 = draw->b0 = (rsin(angle) + 0x1000) / 64 + 0x60;
            angle += 0x200;
            draw->r1 = draw->g1 = draw->b1 = (rsin(angle) + 0x1000) / 64 + 0x60;
            angle += 0x200;
            draw->r3 = draw->g3 = draw->b3 = (rsin(angle) + 0x1000) / 64 + 0x60;
            angle += 0x200;
            draw->r2 = draw->g2 = draw->b2 = (rsin(angle) + 0x1000) / 64 + 0x60;
            draw->enableColorBlend = 1;
            break;
        }
        case PL_T_INVINCIBLE_SCENE:
            // removed compared to RIC, as Maria does not have a prologue
            break;
        case PL_T_AFTERIMAGE_DISABLE:
            MarDisableAfterImage(0, 0);
            break;
        }
        if (--g_Player.timers[i] != 0) {
            continue;
        }
        switch (i) {
        case PL_T_POISON:
        case PL_T_5:
        case PL_T_7:
        case PL_T_8:
        case PL_T_ATTACK:
        case PL_T_10:
        case PL_T_12:
        case PL_T_INVINCIBLE:
            break;
        case PL_T_2:
            PLAYER.palette = PAL_MARIA;
            break;
        case PL_T_4:
            draw->enableColorBlend = 0;
            break;
        case PL_T_INVINCIBLE_SCENE:
            // removed compared to RIC, as Maria does not have a prologue
            break;
        case PL_T_6:
            if (PLAYER.step == PL_S_FALL && PLAYER.anim != mar_80155534) {
                MarSetAnimation(mar_80155534);
                g_Player.unk44 &= ~0x10;
            }
            break;
        case PL_T_AFTERIMAGE_DISABLE:
            func_maria_8015CC28();
            break;
        }
    }
    g_Player.padHeld = g_Player.padPressed;
    if (g_Player.demo_timer) {
        g_Player.demo_timer--;
        g_Player.padPressed = g_Player.padSim;
    } else {
        g_Player.padPressed = g_pads[0].pressed;
#ifdef VERSION_PSP
        if (D_pspeu_092E5F20 > 0) {
            D_pspeu_092E5F20--;
            g_Player.padPressed = 0;
        }
#endif
    }
    g_Player.padTapped =
        g_Player.padPressed & (g_Player.padHeld ^ g_Player.padPressed);
    if (PLAYER.step != PL_S_DEAD) {
        // Reuse the i variable here even though we aren't iterating
        i = GetTeleportToOtherCastle();
        if (i != TELEPORT_CHECK_NONE) {
            MarSetInit(i);
        }
        // Marhter must use step #32 for something else, look into it!
        if (PLAYER.step != PL_S_INIT) {
            if (g_DebugPlayer && MarDebug()) {
                return;
            }
            if (g_Player.unk56) {
                // this block is exclusive to Maria
                g_Status.hp += g_Player.unk58;
                func_9101FC8();
                func_pspeu_092BEAB0(g_Player.unk58);
                if (g_Status.hpMax < g_Status.hp) {
                    g_Status.hp = g_Status.hpMax;
                }
                g_Player.unk56 = 0;
            }
            if (!(g_Player.timers[PL_T_INVINCIBLE_SCENE] |
                  g_Player.timers[PL_T_INVINCIBLE]) &&
                g_Player.unk60 < 2) {
                if (g_Player.unk60 == 1) {
                    playerStep = PLAYER.step;
                    playerStepS = PLAYER.step_s;
                    MarSetStep(PL_S_BOSS_GRAB);
                    goto check_input_combo;
                } else if (PLAYER.hitParams) {
                    playerStep = PLAYER.step;
                    playerStepS = PLAYER.step_s;
                    damage.effects = PLAYER.hitParams & ~0x1F;
                    damage.damageKind = PLAYER.hitParams & 0x1F;
#ifdef VERSION_PSP
                    if (D_8C630C4) {
                        PLAYER.hitPoints = 0;
                    }
#endif
                    damage.damageTaken = PLAYER.hitPoints;
                    isDamageTakenDeadly = g_api.CalcPlayerDamageMaria(&damage);
                    damageKind = damage.damageKind;
                    damageEffects = damage.effects;
                    if (isDamageTakenDeadly) {
                        MarSetStep(PL_S_DEAD);
                    } else {
                        MarSetStep(PL_S_HIT);
                    }
                } else {
                    goto check_input_combo;
                }
            } else {
                goto check_input_combo;
            }
        }
    } else {
    check_input_combo:
        CheckBladeDashInput();
        CheckHighJumpInput();
    }
    g_Player.prev_step = PLAYER.step;
    g_Player.prev_step_s = PLAYER.step_s;
    switch (PLAYER.step) {
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
        MarStepHit(damageEffects, damageKind, playerStep, playerStepS);
        break;
    case PL_S_BOSS_GRAB:
        MarStepBossGrab();
        break;
    case PL_S_DEAD:
        MarStepDead(damageEffects, damageKind, playerStep, playerStepS);
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
    g_Player.unk08 = g_Player.status;
    newStatus = 0;
    switch (PLAYER.step) {
    case PL_S_STAND:
        newStatus = NO_AFTERIMAGE;
        break;
    case PL_S_WALK:
        newStatus = NO_AFTERIMAGE;
        break;
    case PL_S_CROUCH:
        newStatus = NO_AFTERIMAGE;
        if (PLAYER.step_s != 2) {
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
        if (PLAYER.step_s == 0x80) {
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
    if (g_Player.timers[PL_T_ATTACK]) {
        newStatus |= PLAYER_STATUS_UNK400;
    }
    if (g_Player.timers[PL_T_10]) {
        newStatus |= PLAYER_STATUS_UNK800;
    }
    if (g_Player.timers[PL_T_12]) {
        newStatus |= PLAYER_STATUS_UNK1000;
    }
    if (*D_80097448 != 0) {
        newStatus |= PLAYER_STATUS_UNK20000;
    }
    newStatus |= PLAYER_STATUS_UNK10000000;
    g_Player.status = newStatus;
    if (g_Player.unk08 & PLAYER_STATUS_UNK10000 &&
        !(g_Player.status & PLAYER_STATUS_UNK10000)) {
        MarSetInvincibilityFrames(1, 16);
        g_Player.timers[PL_T_4] = 0x10;
        PLAYER.palette = PAL_MARIA;
    }
    if (newStatus & NO_AFTERIMAGE) {
        MarDisableAfterImage(1, 4);
    }
    if (g_Player.timers[PL_T_INVINCIBLE_SCENE] |
        g_Player.timers[PL_T_INVINCIBLE]) {
        g_Player.status |= PLAYER_STATUS_UNK100;
    }
    g_api.UpdateAnim(mar_80155964, (AnimationFrame**)mar_8015538C);
    PLAYER.hitboxState = 1;
    PLAYER.hitParams = 0;
    PLAYER.hitPoints = 0;
    if (PLAYER.anim == mar_801556C4) {
        PLAYER.palette = mar_80154574[PLAYER.pose];
    }
    if (PLAYER.step == PL_S_DEAD) {
        if (PLAYER.poseTimer < 0) {
            PLAYER.animCurFrame |= ANIM_FRAME_LOAD;
        }
#if defined(VERSION_HD) || defined(VERSION_PSP)
        PLAYER.posX.val += PLAYER.velocityX;
        PLAYER.posY.val += PLAYER.velocityY;
        return;
#endif
    }
    if (g_Player.status & (PLAYER_STATUS_UNK10 | PLAYER_STATUS_UNK40)) {
        return;
    }
    InitMariaAfterImage();
    if ((*D_80097448 > 0x28) && !g_CurrentEntity->nFramesInvincibility) {
        PLAYER.velocityY = PLAYER.velocityY * 3 / 4;
        PLAYER.velocityX = PLAYER.velocityX * 3 / 4;
    }
    posX = PLAYER.posX.val;
    posY = PLAYER.posY.val;
    vramFlag = g_Player.vram_flag;
    if (abs(PLAYER.velocityY) > FIX(2) || abs(PLAYER.velocityX) > FIX(2)) {
        PLAYER.velocityX >>= 2;
        PLAYER.velocityY >>= 2;
        if (PLAYER.posY.i.hi >= 0) {
            CheckStageCollision(1);
        }
        if (PLAYER.posY.i.hi >= 0) {
            CheckStageCollision(0);
        }
        if (PLAYER.posY.i.hi >= 0) {
            CheckStageCollision(0);
        }
        if (PLAYER.posY.i.hi >= 0) {
            CheckStageCollision(0);
        }
        if (PLAYER.posY.i.hi < 0) {
            PLAYER.posY.val = FIX(-1);
        }
        PLAYER.velocityX *= 4;
        PLAYER.velocityY *= 4;
    } else {
        CheckStageCollision(1);
    }
    g_Player.unk04 = vramFlag;
    if (*D_80097448 > 0x28 && !g_CurrentEntity->nFramesInvincibility) {
        PLAYER.velocityY = (PLAYER.velocityY * 4) / 3;
        PLAYER.velocityX = (PLAYER.velocityX * 4) / 3;
    }
    g_CurrentEntity->nFramesInvincibility = 0;
    DrawMariaAfterImage();

    // this block is new to maria and it is related to the support for
    // the two subweapons
    if (!(D_pspeu_092E5F28 & PAD_CIRCLE) && (PadReadPSP() & PAD_CIRCLE) &&
        func_90E4C58() < 0) {
        func_90E4C18();
        temp = g_Status.subWeapon;
        g_Status.subWeapon = g_Status.D_80097C40;
        g_Status.D_80097C40 = temp;
    }
    D_pspeu_092E5F28 = PadReadPSP();
}
