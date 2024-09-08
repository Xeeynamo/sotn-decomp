// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"
#include "player.h"

#include "../destroy_entity.h"

void RicHandleStand(void);
void RicHandleWalk(void);
void RicHandleCrouch(void);
void RicHandleFall(void);
void RicHandleJump(void);
void RicHandleRun(void);
void RicHandleBossGrab(void);
void RicHandleStandInAir(void);
void RicHandleEnableFlameWhip(void);
void RicHandleHydrostorm(void);
void RicHandleGenericSubwpnCrash(void);
void RicHandleThrowDaggers(void);
void RicHandleDeadPrologue(void);
void RicHandleSlide(void);
void RicHandleSlideKick(void);
void RicHandleHighJump(void);
void RicSetDeadPrologue(void);
void func_8015BCD0(void);
int RicDoCrash(void);
void DisableAfterImage(s32 resetAnims, s32 arg1);
void RicSetInvincibilityFrames(s32 kind, s16 invincibilityFrames);
void RicHandleHit(
    s32 damageEffect, u32 damageKind, s16 prevStep, s32 prevStepS);
void RicHandleDead(
    s32 damageEffects, s32 damageKind, s32 prevStep, s32 prevStepS);

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
            abs((g_Tilemap.top << 8) + g_PlayerY) - 14407 < 4) {
            return TELEPORT_CHECK_TO_TOP;
        }
    }

    return TELEPORT_CHECK_NONE;
}

static s16 func_80156DE4(void) {
    // Variables that change during execution
    Collider collider;
    s32 yvar;
    s32 collisions;
    s32 i;
    // Values that are set once and never again (but not const for some reason)
    s32 xpos = PLAYER.posX.i.hi;
    s32 xp4 = xpos + 4;
    s32 xm4 = xpos - 4;
    s32 coll_flags = EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID;

    for (i = 0; i < 3; i++) {
        yvar = PLAYER.posY.i.hi + D_80154568[i];
        g_api.CheckCollision(xpos, yvar, &collider, 0);
        collisions = 0;
        if ((collider.effects & coll_flags) == EFFECT_SOLID) {
            collisions += 1;
        }
        g_api.CheckCollision(xp4, yvar, &collider, 0);
        if ((collider.effects & coll_flags) == EFFECT_SOLID) {
            collisions += 1;
        }
        g_api.CheckCollision(xm4, yvar, &collider, 0);
        if ((collider.effects & coll_flags) == EFFECT_SOLID) {
            collisions += 1;
        }
        if (collisions != 0) {
            return i + 1;
        }
    }
    return 0;
}

static void RicDebugOff();

// Duplicate of DRA func_80109594
void RicInit(s16 initParam) {
    Entity* e;
    s32 radius;
    s32 intensity;
    s32 primIndex;
    Primitive* prim;
    s32 i;
    s32 val;
    s32 memset_len;
    s32* memset_ptr;
    SpriteParts** spriteptr;
    Entity* playerPtr = &PLAYER;

    DestroyEntity(&PLAYER);
    PLAYER.posX.val = FIX(32);
    PLAYER.posY.val = FIX(32);
    PLAYER.animSet = ANIMSET_OVL(0x10);
    PLAYER.palette = 0x8120;
    PLAYER.rotX = PLAYER.rotY = 0x100;
    PLAYER.facingLeft = 0;
    PLAYER.rotPivotY = 0x18;
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter;
    memset_len = sizeof(PlayerState) / sizeof(s32);
    memset_ptr = &g_Player;
    for (i = 0; i < memset_len; i++) {
        *memset_ptr++ = 0;
    }
    g_Player.unk04 = 1;
    g_Player.pl_vram_flag = 1;
    RicSetStand(0);
    PLAYER.anim = ric_anim_stand_relax;
    g_Player.unk5C = initParam;
    if (g_StageId == STAGE_ST0) {
        g_IsPrologueStage = true;
    } else {
        g_IsPrologueStage = false;
    }
    g_PlayerDraw->enableColorBlend = 0;
    RicDebugOff();
    for (i = 0; i < LEN(D_80175958); i++) {
        radius = (rand() & 0x3FF) + 0x100;
        intensity = (rand() & 0xFF) + 0x100;
        val = rcos(radius) * 0x10;
        D_80175958[i] = +((val * intensity) >> 8);
        val = rsin(radius) * 0x10;
        D_801759D8[i] = -((val * intensity) >> 7);
    }
    spriteptr = g_api.o.spriteBanks;
    spriteptr += 0x10;
    *spriteptr++ = D_801530AC;
    *spriteptr++ = D_80153AA0;
    *spriteptr++ = D_80153D24;
    *spriteptr++ = D_801541A8;
    for (e = &g_Entities[1], i = 0; i < 3; i++, e++) {
        DestroyEntity(e);
        e->animSet = ANIMSET_OVL(0x10);
        e->unk5A = i + 1;
        e->palette = 0x8120;
        e->flags = FLAG_UNK_20000 | FLAG_POS_CAMERA_LOCKED;
    }
    primIndex = g_api.AllocPrimitives(PRIM_TILE, 6);

    g_Entities[1].primIndex = primIndex;
    g_Entities[1].flags |= FLAG_HAS_PRIMS;
    for (prim = &g_PrimBuf[primIndex]; prim != NULL; prim = prim->next) {
        prim->drawMode = 0x102 | DRAW_HIDE;
    }
    if (D_80097C98 == 6) {
        RicCreateEntFactoryFromEntity(playerPtr, FACTORY(BP_TELEPORT, 1), 0);
        func_8015CC70(1);
    }
    if (D_80097C98 == 4) {
        RicCreateEntFactoryFromEntity(playerPtr, FACTORY(BP_TELEPORT, 3), 0);
        func_8015CC70(3);
    }
    if (D_80097C98 == 5) {
        RicCreateEntFactoryFromEntity(playerPtr, FACTORY(BP_TELEPORT, 5), 0);
        func_8015CC70(5);
    }
}

static void func_801572A8(bool arg0) {
    Collider collider;
    s16 argX;
    s16 argY;
    s32 xVel;
    s32 i;
    s32 j;
    s32 unk0C;

    s32* vram_ptr = &g_Player.pl_vram_flag;
    s32* unk04_ptr = &g_Player.unk04;

    g_Player.unk04 = *vram_ptr;
    *vram_ptr = 0;
    unk0C = g_Player.unk0C;

    if (arg0) {
        for (i = 0; i < LEN(D_801545E4); i++) {
            if (unk0C & 0x20) {
                D_801545F4[i].y = D_80154644[i];
                D_801545E4[i].y = D_8015465C[i];
            } else {
                D_801545F4[i].y = D_80154644[i];
                D_801545E4[i].y = D_8015463C[i];
            }
        }
        for (i = 0; i < 7; i++) {
            if (unk0C & 0x20) {
                D_80154604[i].y = D_80154664[i];
                D_80154604[i + 7].y = D_80154664[i];
            } else {
                D_80154604[i].y = D_8015464C[i];
                D_80154604[i + 7].y = D_8015464C[i];
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
    for (i = 0; i < 4; i++) {
        argX = PLAYER.posX.i.hi + D_801545F4[i].x;
        argY = PLAYER.posY.i.hi + D_801545F4[i].y;
        g_api.CheckCollision(argX, argY, &g_Player.colliders[i], 0);
        if (g_Player.timers[PL_T_7] && (g_Player.colliders[i].effects & 0x40)) {
            g_api.CheckCollision(argX, argY + 0xC, &collider, 0);
            if (!(collider.effects & EFFECT_SOLID)) {
                g_Player.colliders[i].effects = 0;
            }
        }
    }
    func_8015E800();
    for (i = 0; i < 4; i++) {
        argX = PLAYER.posX.i.hi + D_801545E4[i].x;
        argY = PLAYER.posY.i.hi + D_801545E4[i].y;
        g_api.CheckCollision(argX, argY, &g_Player.colliders2[i], 0);
    }
    func_8015EE28();
    if ((*vram_ptr & 1) && (PLAYER.velocityY >= 0)) {
        PLAYER.posY.i.lo = 0;
    }
    if ((*vram_ptr & 2) && (PLAYER.velocityY <= 0)) {
        PLAYER.posY.i.lo = 0;
    }
    for (i = 0; i < 14; i++) {
        argX = PLAYER.posX.i.hi + D_80154604[i].x;
        argY = PLAYER.posY.i.hi + D_80154604[i].y;
        g_api.CheckCollision(argX, argY, &g_Player.colliders3[i], 0);
    }
    func_8015F414();
    func_8015F680();
    if ((*vram_ptr & 4) && (PLAYER.velocityX > 0)) {
        PLAYER.posX.i.lo = 0;
    }
    if ((*vram_ptr & 8) && (PLAYER.velocityX < 0)) {
        PLAYER.posX.i.lo = 0;
    }
}

static void CheckBladeDashInput(void) {
    s32 up;
    s32 down;
    s32 temp_down = PAD_DOWN;
    s32 directionsPressed =
        g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);

    s32 down_forward = temp_down + (!PLAYER.facingLeft ? PAD_RIGHT : PAD_LEFT);
    up = PAD_UP;
    down = PAD_DOWN;

    switch (g_bladeDashButtons.buttonsCorrect) {
    case 0:
        if (g_Player.padTapped == up) {
            g_bladeDashButtons.timer = 20;
            g_bladeDashButtons.buttonsCorrect++;
        }
        break;
    case 1:
        if (directionsPressed == down) {
            g_bladeDashButtons.timer = 20;
            g_bladeDashButtons.buttonsCorrect++;
            break;
        }
        if (--g_bladeDashButtons.timer == 0) {
            g_bladeDashButtons.buttonsCorrect = 0;
        }
        break;
    case 2:
        if (directionsPressed == down_forward) {
            g_bladeDashButtons.timer = 20;
            g_bladeDashButtons.buttonsCorrect++;
            break;
        }
        if (--g_bladeDashButtons.timer == 0) {
            g_bladeDashButtons.buttonsCorrect = 0;
        }
        break;
    case 3:
        if (--g_bladeDashButtons.timer == 0) {
            g_bladeDashButtons.buttonsCorrect = 0;
        }
        if (PLAYER.step == PL_S_STAND || PLAYER.step == PL_S_WALK ||
            PLAYER.step == PL_S_CROUCH ||
            (PLAYER.step == PL_S_FALL || PLAYER.step == PL_S_JUMP)) {
            if (g_Player.unk72) {
                g_bladeDashButtons.buttonsCorrect = 0;
            } else if (
                (g_Player.unk46 == 0) && (g_Player.padTapped & PAD_SQUARE)) {
                RicSetBladeDash();
            }
        }
        break;
    }
}

static void CheckHighJumpInput(void) {
    switch (D_801758E4.buttonsCorrect) {
    case 0:
        if (g_Player.padTapped & PAD_DOWN) {
            if (g_Player.padHeld == 0) {
                D_801758E4.timer = 16;
                D_801758E4.buttonsCorrect++;
                return;
            }
        }
        return;
    case 1:
        if (g_Player.padTapped & PAD_UP) {
            D_801758E4.timer = 16;
            D_801758E4.buttonsCorrect++;
            return;
        }
        if (--D_801758E4.timer == 0) {
            D_801758E4.buttonsCorrect = 0;
        }
        break;
    case 2:
        if ((D_801758E4.timer != 0) && (--D_801758E4.timer == 0)) {
            D_801758E4.buttonsCorrect = 0;
            return;
        }
        if ((g_Player.padTapped & PAD_CROSS) && (g_Player.unk46 == 0) &&
            ((PLAYER.step == PL_S_CROUCH) || (PLAYER.step == PL_S_STAND) ||
             ((PLAYER.step == PL_S_JUMP) && (PLAYER.velocityY > FIX(1))) ||
             (PLAYER.step == PL_S_FALL))) {
            if (!g_Player.unk72) {
                RicSetHighJump();
            }
            D_801758E4.buttonsCorrect = 0;
        }
        break;
    }
}

static bool RicDebug(void);
void RicHandleDead(s32 damageEffects, s32 arg1, s32 arg2, s32 arg3);

void RicMain(void) {
    DamageParam damage;
    s32 temp_s0;
    s32 var_s4;
    s32 damageKind;
    s32 damageEffects;
    s16 playerStep;
    s16 playerStepS;
    s32 i;
    bool isDamageTakenDeadly;
    f32* playerY;

    PlayerDraw* playerDraw = g_PlayerDraw;

    g_CurrentEntity = &PLAYER;
    g_Player.unk4C = 0;
    g_Player.unk72 = func_80156DE4();
    FntPrint("pl_head_f:%02x\n", g_Player.unk72);
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
            PLAYER.palette = g_Player.unk40;
            break;
        case PL_T_4: {
            s32 temp_s0 = (g_GameTimer & 0xF) << 8;
            playerDraw->r0 = playerDraw->b0 = playerDraw->g0 =
                (rsin((s16)temp_s0) + 0x1000) / 64 + 0x60;
            playerDraw->r1 = playerDraw->b1 = playerDraw->g1 =
                (rsin(temp_s0 + 0x200) + 0x1000) / 64 + 0x60;
            playerDraw->r3 = playerDraw->b3 = playerDraw->g3 =
                (rsin(temp_s0 + 0x400) + 0x1000) / 64 + 0x60;
            playerDraw->r2 = playerDraw->b2 = playerDraw->g2 =
                (rsin(temp_s0 + 0x600) + 0x1000) / 64 + 0x60;
            playerDraw->enableColorBlend = 1;
            break;
        }
        case PL_T_INVINCIBLE_SCENE:
            g_Player.timers[PL_T_INVINCIBLE_SCENE] = 4;
            break;
        case PL_T_AFTERIMAGE_DISABLE:
            DisableAfterImage(0, 0);
            break;
        }
        if (--g_Player.timers[i]) {
            continue;
        }
        switch (i) {
        case PL_T_POISON:
            break;
        case PL_T_2:
            PLAYER.palette = 0x8120;
            break;
        case PL_T_4:
            playerDraw->enableColorBlend = 0;
            break;
        case PL_T_INVINCIBLE_SCENE:
            RicSetInvincibilityFrames(1, 16);
            break;
        case PL_T_6:
            if ((PLAYER.step == PL_S_FALL) && (PLAYER.anim != D_80155534)) {
                RicSetAnimation(D_80155534);
                g_Player.unk44 &= ~0x10;
            }
            break;
        case PL_T_AFTERIMAGE_DISABLE:
            func_8015CC28();
            break;
        }
    }
    g_Player.padHeld = g_Player.padPressed;
    if (g_Player.D_80072EFC) {
        g_Player.D_80072EFC--;
        g_Player.padPressed = g_Player.padSim;
    } else {
        g_Player.padPressed = g_pads[0].pressed;
    }
    g_Player.padTapped =
        (g_Player.padHeld ^ g_Player.padPressed) & g_Player.padPressed;
    if (PLAYER.step == PL_S_DEAD) {
        goto block_47;
    }
    // Reuse the i variable here even though we aren't iterating
    i = GetTeleportToOtherCastle();
    if (i != TELEPORT_CHECK_NONE) {
        func_8015CC70(i);
    }
    // Richter must use step #32 for something else, look into it!
    if (PLAYER.step == PL_S_INIT) {
        goto block_48;
    }
    if (g_DebugPlayer && RicDebug()) {
        return;
    }
    if (g_Player.unk60 >= 2) {
        goto block_47;
    }
    if (g_Player.unk60 == 1) {
        playerStep = PLAYER.step;
        playerStepS = PLAYER.step_s;
        RicSetStep(PL_S_BOSS_GRAB);
        goto block_48;
    }
    if ((g_Player.timers[PL_T_INVINCIBLE_SCENE] |
         g_Player.timers[PL_T_INVINCIBLE]) ||
        !PLAYER.hitParams) {
        goto block_47;
    }
    playerStep = PLAYER.step;
    playerStepS = PLAYER.step_s;
    damage.effects = PLAYER.hitParams & ~0x1F;
    damage.damageKind = PLAYER.hitParams & 0x1F;
    damage.damageTaken = PLAYER.hitPoints;
    isDamageTakenDeadly = g_api.CalcPlayerDamage(&damage);
    damageKind = damage.damageKind;
    damageEffects = damage.effects;
    if (isDamageTakenDeadly) {
        if (!g_Player.unk5C) {
            RicSetStep(PL_S_DEAD);
        } else {
            g_Status.hp = 1;
            RicSetStep(PL_S_HIT);
        }
    } else {
        RicSetStep(PL_S_HIT);
    }
    goto block_48;
block_47:
    CheckBladeDashInput();
    CheckHighJumpInput();
block_48:
    g_Player.prev_step = PLAYER.step;
    g_Player.prev_step_s = PLAYER.step_s;
    switch (PLAYER.step) {
    case PL_S_STAND:
        RicHandleStand();
        break;
    case PL_S_WALK:
        RicHandleWalk();
        break;
    case PL_S_CROUCH:
        RicHandleCrouch();
        break;
    case PL_S_FALL:
        RicHandleFall();
        break;
    case PL_S_JUMP:
        RicHandleJump();
        break;
    case PL_S_HIGHJUMP:
        RicHandleHighJump();
        break;
    case PL_S_HIT:
        RicHandleHit(damageEffects, damageKind, playerStep, playerStepS);
        break;
    case PL_S_BOSS_GRAB:
        RicHandleBossGrab();
        break;
    case PL_S_DEAD:
        RicHandleDead(damageEffects, damageKind, playerStep, playerStepS);
        break;
    case PL_S_STAND_IN_AIR:
        RicHandleStandInAir();
        break;
    case PL_S_FLAME_WHIP:
        RicHandleEnableFlameWhip();
        break;
    case PL_S_HYDROSTORM:
        RicHandleHydrostorm();
        break;
    case PL_S_THROW_DAGGERS:
        RicHandleThrowDaggers();
        break;
    case PL_S_SUBWPN_CRASH:
        RicHandleGenericSubwpnCrash();
        break;
    case PL_S_DEAD_PROLOGUE:
        RicHandleDeadPrologue();
        break;
    case PL_S_SLIDE:
        RicHandleSlide();
        break;
    case PL_S_RUN:
        RicHandleRun();
        break;
    case PL_S_SLIDE_KICK:
        RicHandleSlideKick();
        break;
    case PL_S_BLADEDASH:
        RicHandleBladeDash();
        break;
    case PL_S_INIT:
        func_8015BCD0();
        break;
    }
    g_Player.unk08 = g_Player.unk0C;
#ifdef VERSION_PC
    var_s4 = 0;
#endif
    switch (PLAYER.step) {
    case PL_S_STAND:
    case PL_S_WALK:
        var_s4 = NO_AFTERIMAGE;
        break;
    case PL_S_CROUCH:
        var_s4 = NO_AFTERIMAGE;
        if (PLAYER.step_s != 2) {
            var_s4 = NO_AFTERIMAGE | PLAYER_STATUS_UNK_20;
        }
        break;
    case PL_S_FALL:
    case PL_S_JUMP:
        var_s4 = NO_AFTERIMAGE | PLAYER_STATUS_UNK2000;
        break;
    case PL_S_HIGHJUMP:
        RicSetInvincibilityFrames(1, 4);
        break;
    case PL_S_HIT:
        var_s4 = NO_AFTERIMAGE | PLAYER_STATUS_UNK10000;
    case PL_S_STAND_IN_AIR:
        RicSetInvincibilityFrames(1, 16);
        break;
    case PL_S_BOSS_GRAB:
        var_s4 = NO_AFTERIMAGE | PLAYER_STATUS_UNK100000 |
                 PLAYER_STATUS_UNK10000 | PLAYER_STATUS_UNK40;
        RicSetInvincibilityFrames(1, 16);
        break;
    case PL_S_DEAD:
        var_s4 =
            NO_AFTERIMAGE | PLAYER_STATUS_UNK40000 | PLAYER_STATUS_UNK10000;
        if (PLAYER.step_s == 0x80) {
            var_s4 = NO_AFTERIMAGE | PLAYER_STATUS_UNK80000 |
                     PLAYER_STATUS_UNK40000 | PLAYER_STATUS_UNK10000;
        }
        RicSetInvincibilityFrames(1, 16);
        break;
    case PL_S_SLIDE:
    case PL_S_SLIDE_KICK:
        var_s4 = 0x20;
        break;
    case PL_S_RUN:
    case PL_S_BLADEDASH:
        break;
    case PL_S_FLAME_WHIP:
    case PL_S_HYDROSTORM:
    case PL_S_THROW_DAGGERS:
    case PL_S_DEAD_PROLOGUE:
    case PL_S_SUBWPN_CRASH:
    case PL_S_INIT:
        var_s4 = NO_AFTERIMAGE;
        RicSetInvincibilityFrames(1, 16);
        break;
    }
    if (g_Player.timers[PL_T_ATTACK]) {
        var_s4 |= PLAYER_STATUS_UNK400;
    }
    if (g_Player.timers[PL_T_10]) {
        var_s4 |= PLAYER_STATUS_UNK800;
    }
    if (g_Player.timers[PL_T_12]) {
        var_s4 |= PLAYER_STATUS_UNK1000;
    }
    if (*D_80097448 != 0) {
        var_s4 |= PLAYER_STATUS_UNK20000;
    }
    var_s4 |= PLAYER_STATUS_UNK10000000;
    g_Player.unk0C = var_s4;
    if (g_Player.unk08 & PLAYER_STATUS_UNK10000) {
        if (!(var_s4 & PLAYER_STATUS_UNK10000)) {
            if (g_Player.unk5C != 0) {
                if (g_Status.hp < 2) {
                    RicSetDeadPrologue();
                    RicSetInvincibilityFrames(1, 16);
                }
            } else {
                RicSetInvincibilityFrames(1, 16);
                g_Player.timers[PL_T_4] = 0x10;
                PLAYER.palette = 0x8120;
            }
        }
    }
    if (var_s4 & NO_AFTERIMAGE) {
        DisableAfterImage(1, 4);
    }
    if (g_Player.timers[PL_T_INVINCIBLE_SCENE] |
        g_Player.timers[PL_T_INVINCIBLE]) {
        g_Player.unk0C |= 0x100;
    }
    g_api.UpdateAnim(D_80155964, D_8015538C);
    PLAYER.hitboxState = 1;
    PLAYER.hitParams = 0;
    PLAYER.hitPoints = 0;
    g_Player.unk7A = 0;
    if (PLAYER.anim == D_801556C4) {
        PLAYER.palette = D_80154574[PLAYER.animFrameIdx];
    }
    if ((PLAYER.anim == ric_anim_stand_in_air) && (PLAYER.animFrameIdx == 4)) {
        PLAYER.palette = D_80154594[PLAYER.animFrameDuration & 3];
    }
    if ((PLAYER.step == PL_S_DEAD) && (PLAYER.animFrameDuration < 0)) {
        PLAYER.animCurFrame |= ANIM_FRAME_LOAD;
    }
    if (g_Player.unk0C & 0x50) {
        return;
    }
    func_8015C4AC();
    if ((*D_80097448 >= 0x29) && (g_CurrentEntity->nFramesInvincibility == 0)) {
        PLAYER.velocityY = PLAYER.velocityY * 3 / 4;
        PLAYER.velocityX = PLAYER.velocityX * 3 / 4;
    }
    playerY = &PLAYER.posY.i;
    temp_s0 = g_Player.pl_vram_flag;
    if ((abs(PLAYER.velocityY) > FIX(2)) || (abs(PLAYER.velocityX) > FIX(2))) {
        PLAYER.velocityY = PLAYER.velocityY >> 2;
        PLAYER.velocityX = PLAYER.velocityX >> 2;
        if ((playerY->i.hi < 0) || (func_801572A8(1), (playerY->i.hi < 0)) ||
            (func_801572A8(0), (playerY->i.hi < 0)) ||
            (func_801572A8(0), (playerY->i.hi < 0)) ||
            (func_801572A8(0), (playerY->i.hi < 0))) {
            PLAYER.posY.val = FIX(-1);
        }
        PLAYER.velocityX *= 4;
        PLAYER.velocityY *= 4;
    } else {
        func_801572A8(1);
    }
    g_Player.unk04 = temp_s0;
    if ((*D_80097448 >= 0x29) && (g_CurrentEntity->nFramesInvincibility == 0)) {
        PLAYER.velocityY = (PLAYER.velocityY * 4) / 3;
        PLAYER.velocityX = (PLAYER.velocityX * 4) / 3;
    }
    g_CurrentEntity->nFramesInvincibility = 0;
    func_8015C6D4();
}

static void RicDebugOff() { g_IsRicDebugEnter = false; }

static void RicDebugEnter(void) {
    g_IsRicDebugEnter = true;
    g_RicDebugCurFrame = PLAYER.animCurFrame;
    g_RicDebugDrawFlags = PLAYER.drawFlags;
    g_RicDebugPalette = PLAYER.palette;
}

static void RicDebugExit(void) {
    g_IsRicDebugEnter = false;
    PLAYER.hitParams = 0;
    PLAYER.animCurFrame = g_RicDebugCurFrame;
    PLAYER.drawFlags = g_RicDebugDrawFlags;
    PLAYER.palette = g_RicDebugPalette;
}

static bool RicDebug(void) {
    if (!g_IsRicDebugEnter) {
        if (g_Player.padTapped & PAD_L2) {
            if (g_Player.D_80072EFC == 0) {
                RicDebugEnter();
                return true;
            }
        }
        return false;
    }

    if (g_Player.D_80072EFC || g_Player.padTapped & PAD_L2) {
        RicDebugExit();
        return false;
    }

    if (g_Player.padPressed & PAD_CROSS) {
        if (g_Player.padPressed & PAD_RIGHT) {
            g_Entities->posX.val += FIX(16.0);
        }
        if (g_Player.padPressed & PAD_LEFT) {
            g_Entities->posX.val -= FIX(16.0);
        }
        if (g_Player.padPressed & PAD_UP) {
            PLAYER.posY.val -= FIX(16.0);
        }
        if (g_Player.padPressed & PAD_DOWN) {
            PLAYER.posY.val += FIX(16.0);
        }

    } else {
        if (g_Player.padTapped & PAD_RIGHT) {
            g_Entities->posX.val += FIX(16.0);
        }
        if (g_Player.padTapped & PAD_LEFT) {
            g_Entities->posX.val -= FIX(16.0);
        }
        if (g_Player.padTapped & PAD_UP) {
            PLAYER.posY.val -= FIX(16.0);
        }
        if (g_Player.padTapped & PAD_DOWN) {
            PLAYER.posY.val += FIX(16.0);
        }
    }

    if (g_Player.padTapped & PAD_CIRCLE) {
        PLAYER.animCurFrame--;
    }
    if (g_Player.padTapped & PAD_SQUARE) {
        PLAYER.animCurFrame++;
    }

    if (PLAYER.animCurFrame <= 0) {
        PLAYER.animCurFrame = 1;
    }
    if (PLAYER.animCurFrame < 212 == 0) {
        PLAYER.animCurFrame = 211;
    }
    FntPrint("charal:%02x\n", PLAYER.animCurFrame);
    return true;
}
