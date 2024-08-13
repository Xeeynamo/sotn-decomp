/*
 * File: 1AC60.c
 * Overlay: RIC
 * Description: Overlay for the character Richter.
 */

#include "ric.h"
#include "player.h"

#include "../destroy_entity.h"

static TeleportCheck GetTeleportToOtherCastle(void) {
    // Is player in the pose when pressing UP?
    if (PLAYER.step != 0 || PLAYER.step_s != 1) {
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

s16 func_80156DE4(void) {
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

void func_801587C0();

// Duplicate of DRA func_80109594
void func_80156F40(s16 arg0) {
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
    func_8015CD98(0);
    PLAYER.unk4C = D_80155480;
    g_Player.unk5C = arg0;
    if (g_StageId == STAGE_ST0) {
        D_80154570 = 1;
    } else {
        D_80154570 = 0;
    }
    g_PlayerDraw->enableColorBlend = 0;
    func_801587C0();
    for (i = 0; i < 0x20; i++) {
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
        e->flags = FLAG_UNK_20000 | FLAG_UNK_08000000;
    }
    primIndex = g_api.AllocPrimitives(PRIM_TILE, 6);

    g_Entities[1].primIndex = primIndex;
    g_Entities[1].flags |= FLAG_HAS_PRIMS;
    for (prim = &g_PrimBuf[primIndex]; prim != NULL; prim = prim->next) {
        prim->drawMode = 0x102 | DRAW_HIDE;
    }
    if (D_80097C98 == 6) {
        RicCreateEntFactoryFromEntity(playerPtr, FACTORY(0x100, 77), 0);
        func_8015CC70(1);
    }
    if (D_80097C98 == 4) {
        RicCreateEntFactoryFromEntity(playerPtr, FACTORY(0x300, 77), 0);
        func_8015CC70(3);
    }
    if (D_80097C98 == 5) {
        RicCreateEntFactoryFromEntity(playerPtr, FACTORY(0x500, 77), 0);
        func_8015CC70(5);
    }
}

void func_801572A8(bool arg0) {
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
        if ((g_Player.D_80072F00[7] != 0) &&
            (g_Player.colliders[i].effects & 0x40)) {
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

void CheckBladeDashInput(void) {
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
        if ((PLAYER.step == Player_Stand || PLAYER.step == Player_Walk) ||
            PLAYER.step == Player_Crouch ||
            (PLAYER.step == Player_Fall || PLAYER.step == Player_Jump)) {
            if (g_Player.unk72 != 0) {
                g_bladeDashButtons.buttonsCorrect = 0;
            } else if (
                (g_Player.unk46 == 0) && (g_Player.padTapped & PAD_SQUARE)) {
                DoBladeDash();
            }
        }
        break;
    }
}

void CheckHighJumpInput(void) {
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
            ((PLAYER.step == Player_Crouch) || (PLAYER.step == Player_Stand) ||
             ((PLAYER.step == Player_Jump) && (PLAYER.velocityY > FIX(1))) ||
             (PLAYER.step == Player_Fall))) {
            if (g_Player.unk72 == 0) {
                DoHighJump();
            }
            D_801758E4.buttonsCorrect = 0;
        }
        break;
    }
}

bool func_8015885C(void);
void func_8015A9B0(s32 damageEffects, s32 arg1, s32 arg2, s32 arg3);

void UpdateEntityRichter(void) {
    DamageParam damage;
    s32 temp_s0;
    s32 var_s4;
    s32 damageKind;
    s32 damageEffects;
    s16 playerStep;
    s16 playerStepS;
    s32 i;
    bool condition;
    f32* playerY;

    PlayerDraw* playerDraw = g_PlayerDraw;

    g_CurrentEntity = &PLAYER;
    g_Player.unk4C = 0;
    g_Player.unk72 = func_80156DE4();
    FntPrint("pl_head_f:%02x\n", g_Player.unk72);
    for (i = 0; i < 16; i++) {
        if (g_Player.D_80072F00[i] == 0) {
            continue;
        }
        switch (i) {
        case 0:
        case 1:
        case 3:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 14:
            break;
        case 2:
            PLAYER.palette = g_Player.unk40;
            break;
        case 4: {
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
        case 13:
            g_Player.D_80072F00[13] = 4;
            break;
        case 15:
            func_8015CB58(0, 0);
            break;
        }
        if (--(g_Player.D_80072F00[i]) != 0) {
            continue;
        }
        switch (i) {
        case 0:
            break;
        case 2:
            PLAYER.palette = 0x8120;
            break;
        case 4:
            playerDraw->enableColorBlend = 0;
            break;
        case 13:
            func_8015CAD4(1, 0x10);
            break;
        case 6:
            if ((PLAYER.step == Player_Fall) && (PLAYER.unk4C != D_80155534)) {
                func_8015C920(D_80155534);
                g_Player.unk44 &= ~0x10;
            }
            break;
        case 15:
            func_8015CC28();
            break;
        }
    }
    g_Player.padHeld = g_Player.padPressed;
    if (g_Player.D_80072EFC != 0) {
        g_Player.D_80072EFC--;
        g_Player.padPressed = g_Player.padSim;
    } else {
        g_Player.padPressed = g_pads[0].pressed;
    }
    g_Player.padTapped =
        (g_Player.padHeld ^ g_Player.padPressed) & g_Player.padPressed;
    if (PLAYER.step == Player_Kill) {
        goto block_47;
    }
    // Reuse the i variable here even though we aren't iterating
    i = GetTeleportToOtherCastle();
    if (i != TELEPORT_CHECK_NONE) {
        func_8015CC70(i);
    }
    // Richter must use step #32 for something else, look into it!
    if (PLAYER.step == Player_SpellDarkMetamorphosis) {
        goto block_48;
    }
    if ((g_DebugPlayer != 0) && (func_8015885C())) {
        return;
    }
    if (g_Player.unk60 >= 2) {
        goto block_47;
    }
    if (g_Player.unk60 == 1) {
        playerStep = PLAYER.step;
        playerStepS = PLAYER.step_s;
        RicSetPlayerStep(Player_BossGrab);
        goto block_48;
    }
    if (((g_Player.D_80072F00[13] | g_Player.D_80072F00[14]) != 0) ||
        (PLAYER.unk44 == 0)) {
        goto block_47;
    }
    playerStep = PLAYER.step;
    playerStepS = PLAYER.step_s;
    damage.effects = PLAYER.unk44 & ~0x1F;
    damage.damageKind = PLAYER.unk44 & 0x1F;
    damage.damageTaken = PLAYER.hitPoints;
    condition = g_api.func_800FD5BC(&damage);
    damageKind = damage.damageKind;
    damageEffects = damage.effects;
    if (condition) {
        if (g_Player.unk5C == 0) {
            RicSetPlayerStep(Player_Kill);
        } else {
            g_Status.hp = 1;
            RicSetPlayerStep(Player_Hit);
        }
    } else {
        RicSetPlayerStep(Player_Hit);
    }
    goto block_48;
block_47:
    CheckBladeDashInput();
    CheckHighJumpInput();
block_48:
    g_Player.unk50 = PLAYER.step;
    g_Player.unk52 = PLAYER.step_s;
    switch (PLAYER.step) {
    case 0:
        func_80158BFC();
        break;
    case 1:
        func_80158F38();
        break;
    case 2:
        func_80159670();
        break;
    case 3:
        func_801595D8();
        break;
    case 4:
        func_801590A0();
        break;
    case 8:
        func_8015C2A8();
        break;
    case 10:
        RichterHandleDamage(damageEffects, damageKind, playerStep, playerStepS);
        break;
    case 12:
        func_8015A7D0();
        break;
    case 16:
        func_8015A9B0(damageEffects, damageKind, playerStep, playerStepS);
        break;
    case 18:
        func_8015AFE0();
        break;
    case 19:
        func_8015B098();
        break;
    case 20:
        func_8015B18C();
        break;
    case 21:
        func_8015B244();
        break;
    case 27:
        func_8015B1E8();
        break;
    case 22:
        func_8015B348();
        break;
    case 23:
        func_8015B898();
        break;
    case 25:
        func_80158FA4();
        break;
    case Player_SlideKick:
        PlayerStepSlideKick();
        break;
    case Player_RichterBladeDash:
        HandleBladeDash();
        break;
    case 32:
        func_8015BCD0();
        break;
    }
    g_Player.unk08 = g_Player.unk0C;
    switch (PLAYER.step) {
    case 0:
    case 1:
        var_s4 = 0x08000000;
        break;
    case 2:
        var_s4 = 0x08000000;
        if (PLAYER.step_s != 2) {
            var_s4 = 0x08000020;
        }
        break;
    case 3:
    case 4:
        var_s4 = 0x08002000;
        break;
    case 8:
        func_8015CAD4(1, 4);
        break;
    case 10:
        var_s4 = 0x08010000;
    case 18:
        func_8015CAD4(1, 16);
        break;
    case 12:
        var_s4 = 0x08110040;
        func_8015CAD4(1, 16);
        break;
    case 16:
        var_s4 = 0x08050000;
        if (PLAYER.step_s == 0x80) {
            var_s4 = 0x080D0000;
        }
        func_8015CAD4(1, 16);
        break;
    case 23:
    case 26:
        var_s4 = 0x20;
        break;
    case 19:
    case 20:
    case 21:
    case 22:
    case 27:
    case 32:
        var_s4 = 0x08000000;
        func_8015CAD4(1, 16);
        break;
    }
    if (g_Player.D_80072F00[9] != 0) {
        var_s4 |= 0x400;
    }
    if (g_Player.D_80072F00[10] != 0) {
        var_s4 |= 0x800;
    }
    if (g_Player.D_80072F00[12] != 0) {
        var_s4 |= 0x1000;
    }
    if (*D_80097448 != 0) {
        var_s4 |= 0x20000;
    }
    var_s4 |= 0x10000000;
    g_Player.unk0C = var_s4;
    if (g_Player.unk08 & 0x10000) {
        if (!(var_s4 & 0x10000)) {
            if (g_Player.unk5C != 0) {
                if (g_Status.hp < 2) {
                    func_8015D9B4();
                    func_8015CAD4(1, 0x10);
                }
            } else {
                func_8015CAD4(1, 0x10);
                g_Player.D_80072F00[4] = 0x10;
                PLAYER.palette = 0x8120;
            }
        }
    }
    if (var_s4 & 0x08000000) {
        func_8015CB58(1, 4);
    }
    if ((g_Player.D_80072F00[13] | g_Player.D_80072F00[14]) != 0) {
        g_Player.unk0C |= 0x100;
    }
    g_api.UpdateAnim(D_80155964, D_8015538C);
    PLAYER.hitboxState = 1;
    PLAYER.unk44 = 0;
    PLAYER.hitPoints = 0;
    g_Player.unk7A = 0;
    if (PLAYER.unk4C == D_801556C4) {
        PLAYER.palette = D_80154574[PLAYER.animFrameIdx];
    }
    if ((PLAYER.unk4C == D_80155658) && (PLAYER.animFrameIdx == 4)) {
        PLAYER.palette = D_80154594[PLAYER.animFrameDuration & 3];
    }
    if ((PLAYER.step == 0x10) && (PLAYER.animFrameDuration < 0)) {
        PLAYER.animCurFrame |= 0x8000;
    }
    if (g_Player.unk0C & 0x50) {
        return;
    }
    func_8015C4AC();
    if ((*D_80097448 >= 0x29) && (g_CurrentEntity->nFramesInvincibility == 0)) {
        PLAYER.velocityY = PLAYER.velocityY * 3 / 4;
        PLAYER.velocityX = PLAYER.velocityX * 3 / 4;
    }
    playerY = &g_Entities[PLAYER_CHARACTER].posY.i;
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

void func_801587C0() { D_80175956 = 0; }

void func_801587D0(void) {
    D_80175956 = 1;
    D_80175950 = PLAYER.animCurFrame;
    D_80175952 = PLAYER.drawFlags;
    D_80175954 = PLAYER.palette;
}

void func_80158814(void) {
    D_80175956 = 0;
    PLAYER.unk44 = 0;
    PLAYER.animCurFrame = D_80175950;
    PLAYER.drawFlags = *(u8*)&D_80175952;
    PLAYER.palette = D_80175954;
}

bool func_8015885C(void) {
    if (D_80175956 == 0) {
        if (g_Player.padTapped & PAD_L2) {
            if (g_Player.D_80072EFC == 0) {
                func_801587D0();
                return true;
            }
        }
        return false;
    }

    if ((g_Player.D_80072EFC != 0) || (g_Player.padTapped & PAD_L2)) {
        func_80158814();
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
