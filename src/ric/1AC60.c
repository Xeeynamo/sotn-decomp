/*
 * File: 1AC60.c
 * Overlay: RIC
 * Description: Overlay for the character Richter.
 */

#include "ric.h"
#include "player.h"

#include "../destroy_entity.h"

TeleportCheck GetTeleportToOtherCastle(void) {
    s32 xCheckTop;
    s32 yCheckTop;
    s32 xCheckRTop;
    s32 yCheckRTop;

    // Is player in the pose when pressing UP?
    if (PLAYER.step != 0 || PLAYER.step_s != 1) {
        return TELEPORT_CHECK_NONE;
    }

    // Check for X/Y boundaries in TOP
    if (g_StageId == STAGE_TOP) {
        xCheckTop = (g_Tilemap.left << 8) + playerX - 8000;
        if (ABS(xCheckTop) < 4) {
            yCheckTop = (g_Tilemap.top << 8) + playerY - 2127;
            if (ABS(yCheckTop) < 4) {
                return TELEPORT_CHECK_TO_RTOP;
            }
        }
    }

    // Check for X/Y boundaries in RTOP
    if (g_StageId == STAGE_RTOP) {
        xCheckRTop = (g_Tilemap.left << 8) + playerX - 8384;
        if (ABS(xCheckRTop) < 4) {
            yCheckRTop = (g_Tilemap.top << 8) + playerY;
            if (ABS(yCheckRTop) - 14407 < 4) {
                return TELEPORT_CHECK_TO_TOP;
            }
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
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter.S16.unk0;
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
        prim->blendMode = 0x102 | BLEND_VISIBLE;
    }
    if (D_80097C98 == 6) {
        CreateEntFactoryFromEntity(playerPtr, FACTORY(0x100, 77), 0);
        func_8015CC70(1);
    }
    if (D_80097C98 == 4) {
        CreateEntFactoryFromEntity(playerPtr, FACTORY(0x300, 77), 0);
        func_8015CC70(3);
    }
    if (D_80097C98 == 5) {
        CreateEntFactoryFromEntity(playerPtr, FACTORY(0x500, 77), 0);
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
                D_801545F4[i].unk2 = D_80154644[i];
                D_801545E4[i].unk2 = D_8015465C[i];
            } else {
                D_801545F4[i].unk2 = D_80154644[i];
                D_801545E4[i].unk2 = D_8015463C[i];
            }
        }
        for (i = 0; i < 7; i++) {
            if (unk0C & 0x20) {
                D_80154604[i].unk2 = D_80154664[i];
                D_80154604[i + 7].unk2 = D_80154664[i];
            } else {
                D_80154604[i].unk2 = D_8015464C[i];
                D_80154604[i + 7].unk2 = D_8015464C[i];
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
        argX = PLAYER.posX.i.hi + D_801545F4[i].unk0;
        argY = PLAYER.posY.i.hi + D_801545F4[i].unk2;
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
        argX = PLAYER.posX.i.hi + D_801545E4[i].unk0;
        argY = PLAYER.posY.i.hi + D_801545E4[i].unk2;
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
        argX = PLAYER.posX.i.hi + D_80154604[i].unk0;
        argY = PLAYER.posY.i.hi + D_80154604[i].unk2;
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

    switch (D_801758E0.buttonsCorrect) {
    case 0:
        if (g_Player.padTapped == up) {
            D_801758E0.timer = 20;
            D_801758E0.buttonsCorrect++;
        }
        break;
    case 1:
        if (directionsPressed == down) {
            D_801758E0.timer = 20;
            D_801758E0.buttonsCorrect++;
            break;
        }
        if (--D_801758E0.timer == 0) {
            D_801758E0.buttonsCorrect = 0;
        }
        break;
    case 2:
        if (directionsPressed == down_forward) {
            D_801758E0.timer = 20;
            D_801758E0.buttonsCorrect++;
            break;
        }
        if (--D_801758E0.timer == 0) {
            D_801758E0.buttonsCorrect = 0;
        }
        break;
    case 3:
        if (--D_801758E0.timer == 0) {
            D_801758E0.buttonsCorrect = 0;
        }
        if ((PLAYER.step == Player_Stand || PLAYER.step == Player_Walk) ||
            PLAYER.step == Player_Crouch ||
            (PLAYER.step == Player_Fall || PLAYER.step == Player_Jump)) {
            if (g_Player.unk72 != 0) {
                D_801758E0.buttonsCorrect = 0;
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

INCLUDE_ASM("ric/nonmatchings/1AC60", UpdateEntityRichter);

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

void func_80158B04(s32 arg0) {
    s32 var_s0;

    if (PLAYER.facingLeft != 0) {
        var_s0 = -3;
    } else {
        var_s0 = 3;
    }

    PLAYER.posY.i.hi -= 16;
    PLAYER.posX.i.hi = var_s0 + PLAYER.posX.i.hi;
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x100, 4), 0);
    PLAYER.posY.i.hi += 16;
    PLAYER.posX.i.hi = PLAYER.posX.i.hi - var_s0;

    if (arg0 & 1) {
        g_api.func_80102CD8(3);
        g_api.PlaySfx(NA_SE_SECRET_STAIRS);
    }

    if (arg0 & 2) {
        PLAYER.velocityX = 0;
        PLAYER.velocityY = 0;
    }
}

void func_80158BFC(void) {
    s32 var_s0;

    if (PLAYER.step < 64) {
        if (D_8015459C != 0) {
            D_8015459C--;
        } else if (D_80097448[0] >= 49) {
            if (PLAYER.facingLeft != 0) {
                var_s0 = -4;
            } else {
                var_s0 = 4;
            }
            PLAYER.posX.i.hi = var_s0 + PLAYER.posX.i.hi;
            PLAYER.posY.i.hi -= 16;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x800, 4), 0);
            D_8015459C = 0x60;
            PLAYER.posY.i.hi += 16;
            PLAYER.posX.i.hi = PLAYER.posX.i.hi - var_s0;
        }
    }

    if (func_8015DBB0(0x40000 | 0x305C) == false) {
        func_8015C93C(0x2000);
        switch (PLAYER.step_s) {
        case 0:
            if (func_8015C9CC() == 0) {
                if (g_Player.padPressed & PAD_UP) {
                    func_8015C920(&D_80155394);
                    PLAYER.step_s = 1;
                    break;
                }
            } else {
                func_8015CDE0(0);
            }
            break;

        case 1:
            if (func_8015C9CC() != 0) {
                func_8015CDE0(0);
                break;
            } else if (g_Player.padPressed & PAD_UP) {
                break;
            } else {
                func_8015CD98(0);
                break;
            }

        case 64:
            func_8015CB58(1, 1);
            if (PLAYER.animFrameIdx < 3) {
                func_8015C9CC();
                if (g_Player.padPressed & PAD_DOWN) {
                    PLAYER.step = 2;
                    PLAYER.unk4C = D_801555A8;
                    break;
                }
            }

            if (PLAYER.animFrameDuration < 0) {
                if (g_Player.padPressed & PAD_SQUARE) {
                    g_Player.unk46 = 2;
                    PLAYER.step_s++;
                    func_8015C920(D_80155730);
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 17), 0);
                    break;
                }
                g_Player.unk46 = 0;
                func_8015CD98(0);
            }
            break;

        case 65:
            func_8015CB58(1, 1);
            if (g_Player.padPressed & PAD_SQUARE) {
                break;
            }
            g_Player.unk46 = 0;
            func_8015CD98(0);
            break;

        case 66:
            func_8015CB58(1, 1);
            if (PLAYER.animFrameIdx < 3) {
                func_8015C9CC();
            }
            if (PLAYER.animFrameDuration < 0) {
                g_Player.unk46 = 0;
                func_8015CD98(0);
            }
        }
    }
}

void func_80158F38(void) {
    if (func_8015DBB0(0x305C) == 0) {
        func_8015C93C(0x2000);
        if (func_8015C9CC() == 0) {
            func_8015CD98(0);
            return;
        }

        if (PLAYER.step_s == 0) {
            SetSpeedX(0x14000);
        }
    }
}

void func_80158FA4(void) {
    if (g_Player.unk7A != 0) {
        func_8015CDE0(0);
        return;
    }
    g_Player.D_80072F00[8] = 8;
    g_Player.D_80072F00[1] = 8;

    if (!func_8015DBB0(0x305C)) {
        func_8015C93C(0x2000);
        if (func_8015C9CC() == 0) {
            func_8015CD98(0);
            if (g_Player.D_80072F00[11] == 0) {
                if (!(g_Player.pl_vram_flag & 0xC)) {
                    func_8015C920(&D_8015539C);
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 0), 0);
                }
            } else {
                PLAYER.velocityX = 0;
            }
        } else if (PLAYER.step_s == 0) {
            SetSpeedX(0x24000);
        }
    }
}

void func_801590A0(void) {
    if ((D_80154570 == 0) && (PLAYER.velocityY < FIX(-1)) &&
        !(g_Player.unk44 & 0x40) && !(g_Player.padPressed & PAD_CROSS)) {
        PLAYER.velocityY = FIX(-1);
    }
    if ((g_Player.pl_vram_flag & 2) && (PLAYER.velocityY < FIX(-1))) {
        PLAYER.velocityY = FIX(-0.25);
        g_Player.unk44 |= 0x20;
    }
    if (func_8015DBB0(0x11009)) {
        return;
    }
    switch (PLAYER.step_s) {
    // Need at least one fake case to make the switch match
    case 1:
        return;
    case 0:
        func_8015C93C(0x1000);
        if (func_8015C9CC()) {
            if (g_Player.unk44 & 0x10) {
                SetSpeedX(FIX(2.25));
            } else {
                SetSpeedX(FIX(1.25));
            }
            g_Player.unk44 &= ~4;
        } else {
            g_Player.unk44 &= ~0x10;
            if ((PLAYER.animFrameIdx < 2) &&
                ((LOW(g_Player.unk44) & 0xC) == 4) &&
                (g_Player.padTapped & PAD_CROSS)) {
                func_8015C920(D_8015555C);
                SetSpeedX(FIX(-1.5));
                PLAYER.velocityY = FIX(-2.625);
                if (g_Player.unk72 != 0) {
                    PLAYER.velocityY = 0;
                }
                PLAYER.step_s = 2;
                g_Player.unk44 |= 0xA;
                g_Player.unk44 &= ~4;
            }
        }
        return;
    case 0x40:
        func_8015CB58(1, 1);
        if (PLAYER.animFrameIdx < 3) {
            if (func_8015C9CC() != 0) {
                if (g_Player.unk44 & 0x10) {
                    SetSpeedX(FIX(2.25));
                } else {
                    SetSpeedX(FIX(1.25));
                }
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        } else {
            if (((g_Player.padPressed & PAD_RIGHT) && !PLAYER.facingLeft) ||
                ((g_Player.padPressed & PAD_LEFT) && PLAYER.facingLeft)) {
                if (g_Player.unk44 & 0x10) {
                    SetSpeedX(FIX(2.25));
                } else {
                    SetSpeedX(FIX(1.25));
                }
                SetSpeedX(FIX(1.25));
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        }
        if (PLAYER.animFrameDuration < 0) {
            if (g_Player.padPressed & PAD_SQUARE) {
                g_Player.unk46 = 2;
                PLAYER.step_s += 1;
                func_8015C920(D_80155740);
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 17), 0);
            } else {
                g_Player.unk46 = 0;
                PLAYER.step_s = 0;
                func_8015C920(D_80155528);
            }
        }
        return;
    case 0x41:
        func_8015CB58(1, 1);
        if (!(g_Player.padPressed & PAD_SQUARE)) {
            g_Player.unk46 = 0;
            PLAYER.step_s = 0;
            func_8015C920(D_80155528);
        }
        return;
    case 0x42:
        func_8015CB58(1, 1);
        if (PLAYER.animFrameIdx < 3) {
            if (func_8015C9CC() != 0) {
                if (g_Player.unk44 & 0x10) {
                    SetSpeedX(FIX(2.25));
                } else {
                    SetSpeedX(FIX(1.25));
                }
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        } else {
            if (((g_Player.padPressed & PAD_RIGHT) && !PLAYER.facingLeft) ||
                ((g_Player.padPressed & PAD_LEFT) && PLAYER.facingLeft)) {
                if (g_Player.unk44 & 0x10) {
                    SetSpeedX(FIX(2.25));
                } else {
                    SetSpeedX(FIX(1.25));
                }
                SetSpeedX(FIX(1.25));
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        }
        if (PLAYER.animFrameDuration < 0) {
            g_Player.unk46 = 0;
            PLAYER.step_s = 0;
            func_8015C920(D_80155528);
        }
    }
}

void func_801595D8(void) {
    if (func_8015DBB0(0x9009)) {
        return;
    }
    func_8015C93C(0x1000);
    if (PLAYER.step_s != 0) {
        return;
    }
    if (g_Player.D_80072F00[5] != 0 && g_Player.padTapped & PAD_CROSS) {
        func_8015D020();
    } else if (func_8015C9CC() != 0) {
        SetSpeedX(0xC000);
    }
}

void func_80159670(void) {
    s32 i;
    s16 xShift;

    if ((g_Player.padTapped & PAD_CROSS) && (g_Player.unk46 == 0) &&
        (g_Player.padPressed & PAD_DOWN)) {
        for (i = 0; i < 4; i++) {
            if ((g_Player.colliders[i].effects & EFFECT_SOLID_FROM_ABOVE)) {
                g_Player.D_80072F00[7] = 8;
                return;
            }
        }
    }
    if (func_8015DBB0(0x4100C)) {
        return;
    }
    if ((g_Player.padTapped & PAD_CROSS) && (g_Player.unk46 == 0) &&
        (g_Player.unk72 == 0)) {
        func_8015D020(1);
        return;
    } else if ((g_Player.unk72 == 0) && (g_Player.unk46 == 0) &&
               (g_Player.padTapped & PAD_TRIANGLE) && func_8015D678()) {
        return;
    }
    func_8015C93C(0x2000);
    switch (PLAYER.step_s) {
    case 0x0:
        if (D_8015459C != 0) {
            D_8015459C--;
        } else if ((*D_80097448 >= 0x19) && (g_Player.unk48 == 0)) {
            if (PLAYER.facingLeft) {
                xShift = -9;
            } else {
                xShift = 9;
            }
            PLAYER.posX.i.hi += xShift;
            PLAYER.posY.i.hi += 2;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x800, 4), 0);
            D_8015459C = 0x60;
            PLAYER.posY.i.hi -= 2;
            PLAYER.posX.i.hi -= xShift;
        }
        if (!(g_Player.padPressed & PAD_DOWN) &&
            ((g_Player.unk72 == 0) || !(g_Player.pl_vram_flag & 0x40))) {
            func_8015C920(D_801554E0);
            PLAYER.step_s = 2;
            return;
        }
        break;
    case 0x1:
        if (!(g_Player.padPressed & PAD_DOWN) &&
            ((g_Player.unk72 == 0) || !(g_Player.pl_vram_flag & 0x40))) {
            if (func_8015C9CC() == 0) {
                PLAYER.unk4C = D_801554E0;
                PLAYER.step_s = 2;
                PLAYER.animFrameDuration = 1;
                PLAYER.animFrameIdx = 2 - PLAYER.animFrameIdx;
                return;
            }
            func_8015CDE0(0);
            return;
        }
    case 0x4:
        if (PLAYER.animFrameDuration != -1) {
            return;
        }
        func_8015C920(D_801554C0);
        PLAYER.step_s = 0;
        return;
    case 0x2:
        if ((g_Player.unk72 == 0) || !(g_Player.pl_vram_flag & 0x40)) {
            if (func_8015C9CC() != 0) {
                func_8015CDE0(0);
                return;
            }
            if (PLAYER.animFrameDuration == -1) {
                func_8015CD98(0);
                return;
            }
        }
        break;
    case 0x3:
        if (PLAYER.animFrameDuration < 0) {
            func_8015C920(D_801554C0);
            PLAYER.step_s = 0;
            return;
        }
        break;
    case 0x40:
        func_8015CB58(1, 1);
        if (PLAYER.animFrameIdx < 3) {
            func_8015C9CC();
            if (!(g_Player.padPressed & PAD_DOWN) && (g_Player.unk72 == 0)) {
                PLAYER.step = 0;
                PLAYER.unk4C = D_80155588;
                return;
            }
        }
        if (PLAYER.animFrameDuration < 0) {
            if (g_Player.padPressed & PAD_SQUARE) {
                g_Player.unk46 = 2;
                PLAYER.step_s++;
                func_8015C920(D_80155738);
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 17), 0);
                return;
            }
            g_Player.unk46 = 0;
            PLAYER.step_s = 0;
            func_8015C920(D_801554C0);
        }
        break;
    case 0x41:
        func_8015CB58(1, 1);
        if (!(g_Player.padPressed & PAD_SQUARE)) {
            g_Player.unk46 = 0;
            PLAYER.step_s = 0;
            func_8015C920(D_801554C0);
        }
        break;
    }
}

void func_80159BC8(void) {
    PLAYER.animFrameDuration = 0;
    PLAYER.animFrameIdx = 0;
    g_Player.unk44 = 0;
    g_Player.unk46 = 0;
    PLAYER.drawFlags &= 0xFB;
}

void func_80159C04(void) {
    Entity* entity = PLAYER.ext.generic.unkB8.entityPtr;
    s16 temp_v0;
    s32 var_a0;
    s32 var_a2;

    if (entity->facingLeft != 0) {
        var_a2 = -entity->hitboxOffX;
    } else {
        var_a2 = entity->hitboxOffX;
    }

    if (PLAYER.facingLeft != 0) {
        var_a0 = -PLAYER.hitboxOffX;
    } else {
        var_a0 = PLAYER.hitboxOffX;
    }

    temp_v0 = var_a0 + PLAYER.posX.i.hi - entity->posX.i.hi - var_a2;

    if (ABS(temp_v0) < 16) {
        if (entity->velocityX != 0) {
            if (entity->velocityX < 0) {
                PLAYER.entityRoomIndex = 0;
                return;
            } else {
                PLAYER.entityRoomIndex = 1;
                return;
            }
        }
    }

    if (temp_v0 < 0) {
        PLAYER.entityRoomIndex = 0;
    } else {
        PLAYER.entityRoomIndex = 1;
    }
}

void RichterHandleDamage(s32 arg0, u32 arg1, s16 arg2) {
    DamageParam damage;
    s32 xShift;
    s32 i;
    bool step_s_zero = false;

    if (D_80173B64 != 0) {
        D_80173B64--;
    }
    switch (PLAYER.step_s) {
    case 0:
        step_s_zero = true;
        func_80159BC8();
        if (arg1 < 16) {
            func_80159C04();
        } else {
            PLAYER.entityRoomIndex = PLAYER.facingLeft;
        }
        if (arg0 & 0x4000) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 48), 0);
            PLAYER.velocityY = FIX(-4);
            func_8015CAAC(FIX(-1.25));
            PLAYER.step_s = 1;
            PLAYER.unk4C = D_801556C4;
            g_Player.unk40 = 0x8120;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 48), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x4600, 33), 0);
            g_Player.D_80072F00[2] = 6;
            g_api.PlaySfx(0x703);
            break;
        } else {
            if (arg0 & 0x2000) {
                arg1 = 3;
            }
            switch (arg1 - 2) {
            case 0:
                switch (arg2) {
                case 0:
                case 1:
                    PLAYER.velocityY = 0;
                    func_8015CAAC(FIX(-1.25));
                    PLAYER.step_s = 6;
                    PLAYER.unk4C = D_8015569C;
                    g_api.PlaySfx(0x702);
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 0), 0);
                    break;
                case 2:
                    PLAYER.velocityY = 0;
                    func_8015CAAC(FIX(-1.25));
                    PLAYER.step_s = 7;
                    PLAYER.unk4C = D_80155704;
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 0), 0);
                    g_api.PlaySfx(0x703);
                    break;
                case 3:
                case 4:
                    PLAYER.velocityY = FIX(-3);
                    func_8015CAAC(FIX(-1.25));
                    PLAYER.step_s = 1;
                    PLAYER.unk4C = D_80155694;
                    g_api.PlaySfx(0x702);
                    break;
                }
                break;
            case 2:
            case 3:
                PLAYER.velocityY = FIX(-0.5);
                g_Player.damageTaken = PLAYER.hitPoints;
                PLAYER.posY.val -= 1;
                func_8015CAAC(FIX(-8));
                PLAYER.step_s = 2;
                PLAYER.unk4C = D_80155694;
                g_Player.D_80072F00[2] = 0x200;
                PLAYER.facingLeft = PLAYER.entityRoomIndex;
                break;
            default:
            case 1:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
                switch (arg2) {
                default:
                case 0:
                case 1:
                    PLAYER.velocityY = FIX(-4);
                    func_8015CAAC(FIX(-1.25));
                    PLAYER.step_s = 1;
                    PLAYER.unk4C = D_80155694;
                    g_api.PlaySfx(0x702);
                    break;
                case 2:
                    PLAYER.velocityY = 0;
                    func_8015CAAC(FIX(-1.25));
                    PLAYER.step_s = 7;
                    PLAYER.unk4C = D_80155704;
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 0), 0);
                    g_api.PlaySfx(0x703);
                    break;
                case 3:
                case 4:
                    PLAYER.velocityY = FIX(-3);
                    func_8015CAAC(FIX(-1.25));
                    PLAYER.step_s = 1;
                    PLAYER.unk4C = D_80155694;
                    g_api.PlaySfx(0x702);
                    break;
                }
                break;
            }
            g_Player.unk40 = 0x8166;
            g_Player.D_80072F00[2] = 6;
            if (arg0 & 0x8000) {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x100, 8), 0);
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 9), 0);
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x4300, 33), 0);
                g_Player.unk40 = 0x8160;
                g_Player.D_80072F00[2] = 0x10;
                break;
            } else if (arg0 & 0x40) {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x500, 46), 0);
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x4400, 33), 0);
                g_Player.unk40 = 0x8166;
                g_Player.D_80072F00[2] = 0x10;
                break;
            } else if (arg0 & 0x2000) {
                // Creates EntityHitByIce
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 47), 0);
                g_Player.D_80072F00[2] = 0xC;
                g_Player.unk40 = 0x8169;
                break;
            } else {
                if (arg0 & 0x800) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 70), 0);
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x5600, 33), 0);
                    g_Player.D_80072F00[2] = 0x10;
                    g_Player.unk40 = 0x8164;
                }
                if (arg0 & 0x1000) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 71), 0);
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x5700, 33), 0);
                    g_Player.D_80072F00[2] = 8;
                    g_Player.unk40 = 0x8168;
                }
                if (!(arg0 & 0xF840)) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x5300, 33), 0);
                }
            }
        }
        break;
    case 1:
        if ((g_Player.pl_vram_flag & 2) && (PLAYER.velocityY < FIX(-1))) {
            PLAYER.velocityY = FIX(-1);
        }
        if (func_8015DBB0(0x20280)) {
            return;
        }
        break;
    case 2:
        if ((g_Player.unk04 & 0x8000) && !(g_Player.pl_vram_flag & 0x8000)) {
            goto block_6dc;
        }
        if ((g_Player.pl_vram_flag & 0x8000) && !(g_GameTimer & 1)) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0xA00, 74), 0);
        }
        if (!(g_Player.pl_vram_flag & 0xE)) {
            break;
        }
        if (g_Player.pl_vram_flag & 2) {
            func_80158B04(1);
            D_80173B64 = 0x18;
            PLAYER.velocityX /= 2;
            PLAYER.velocityY = 0;
            PLAYER.step_s = 5;
            damage.effects = 0;
            damage.damageKind = 1;
            damage.damageTaken = g_Player.damageTaken;
            if (g_api.func_800FD5BC(&damage) != 0) {
                SetPlayerStep(Player_Kill);
                func_8015A9B0(0, 2, 10, 2);
                return;
            }
            break;
        } else {
            if ((g_StageId != STAGE_BO6) && (g_StageId != STAGE_RBO6) &&
                (g_StageId != STAGE_DRE)) {
                for (i = 2; i < 7; i++) {
                    if ((g_Player.colliders3[i].effects & 2)) {
                        break;
                    }
                }
                if (i == 7) {
                    for (i = 9; i < 0xE; i++) {
                        if ((g_Player.colliders3[i].effects & 2)) {
                            break;
                        }
                    }
                }
                if (i == 14) {
                block_6dc:
                    PLAYER.velocityY = FIX(-4);
                    func_8015CAAC(FIX(-1.25));
                    xShift = -3;
                    if (PLAYER.velocityX != 0) {
                        xShift = 3;
                    }
                    PLAYER.posY.i.hi += 20;
                    PLAYER.posX.i.hi = xShift + PLAYER.posX.i.hi;
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x900, 4), 0);
                    PLAYER.posY.i.hi -= 20;
                    PLAYER.posX.i.hi -= xShift;
                    g_api.PlaySfx(NA_SE_EN_ROCK_BREAK);
                    g_api.func_80102CD8(2);
                    PLAYER.step_s = 1;
                    damage.effects = 0;
                    damage.damageKind = 1;
                    damage.damageTaken = g_Player.damageTaken;
                    if (g_api.func_800FD5BC(&damage) != 0) {
                        SetPlayerStep(Player_Kill);
                        func_8015A9B0(0, 2, 10, 2);
                        return;
                    }
                    break;
                }
            }
            D_80173B64 = 8;
            g_api.PlaySfx(NA_SE_EN_ROCK_BREAK);
            PLAYER.velocityY = FIX(-2.5);
            g_api.func_80102CD8(2);
            PLAYER.step_s = 3;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x800, 75), 0);
        }
        damage.effects = 0;
        damage.damageKind = 1;
        damage.damageTaken = g_Player.damageTaken;
        if (g_api.func_800FD5BC(&damage) != 0) {
            SetPlayerStep(Player_Kill);
            func_8015A9B0(0, 2, 10, 2);
            return;
        }
        break;
    case 3:
        if (D_80173B64 == 0) {
            SetSpeedX(FIX(0.75));
            if (func_8015DBB0(0x20280)) {
                return;
            }
        }
        break;
    case 5:
        func_8015C93C(0x2000);
        if (D_80173B64 != 0) {
            if ((g_Player.pl_vram_flag & 2) && !(g_GameTimer & 3)) {
                func_80158B04(0);
            }
            break;
        } else if (g_Player.pl_vram_flag & 0xC) {
            if (!(g_Player.pl_vram_flag & 0xFF03)) {
                PLAYER.velocityY += FIX(12.0 / 128);
                if (PLAYER.velocityY > FIX(7)) {
                    PLAYER.velocityY = FIX(7);
                }
                if (!(g_GameTimer & 3)) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x400, 76), 0);
                }
                break;
            }
        }
        PLAYER.step_s = 1;
        PLAYER.animFrameIdx = 0;
        PLAYER.animFrameDuration = 0;
        break;
    case 6:
        func_8015C93C(0x2000);
        if (!(g_Player.pl_vram_flag & 1)) {
            func_8015CF08();
        }
        if (PLAYER.animFrameDuration < 0) {
            if ((g_Player.unk5C == 0) || (g_Status.hp > 0)) {
                func_8015CD98(PLAYER.velocityX);
                break;
            }
            func_8015D9B4();
            return;
        }
        break;
    case 7:
        func_8015C93C(0x2000);
        if (!(g_Player.pl_vram_flag & 1)) {
            func_8015CF08();
        }
        if (PLAYER.animFrameDuration < 0) {
            if ((g_Player.unk5C != 0) && (g_Status.hp <= 0)) {
                func_8015D9B4();
                return;
            }
            func_8015CCC8(0, PLAYER.velocityX);
        }
        break;
    }
    if (step_s_zero && (g_Player.unk72 != 0)) {
        PLAYER.velocityY = 0;
    }
}

const s32 rodata_padding_1A784 = 0;

void func_8015A7D0(void) {
    DamageParam damage;
    switch (g_CurrentEntity->step_s) {
    case 0:
        func_80159BC8();
        if (g_Player.unk62 == 0) {
            PLAYER.unk4C = D_80155694;
            g_Player.D_80072F00[2] = 8;
            g_Player.unk40 = 0x8166;
            g_api.PlaySfx(0x702);
        }
        PLAYER.step_s = 1;
        PLAYER.velocityX = PLAYER.velocityY = 0;
        g_Player.unk60 = 2;
        return;
    case 1:
        // Effectively a switch on g_Player.unk60
        if (g_Player.unk60 == 3) {
            damage.effects = 0;
            damage.damageKind = 1;
            damage.damageTaken = g_Player.damageTaken;
            if (g_api.func_800FD5BC(&damage)) {
                SetPlayerStep(Player_Kill);
                func_8015A9B0(0, 2, 12, 1);
                return;
            }
            if (g_Player.unk62 == 0) {
                g_Player.D_80072F00[2] = 4;
                g_Player.unk40 = 0x8166;
                g_api.PlaySfx(0x703);
            }
            g_Player.unk60 = 2;
        } else if (g_Player.unk60 == 4) { /* switch 1 */
            PLAYER.step = Player_Hit;
            PLAYER.step_s = 2;
            g_Player.unk60 = 0;
            g_Player.damageTaken = g_Player.unk64;
            g_api.PlaySfx(0x704);
        } else if (g_Player.unk60 == 0) { /* switch 1 */
            PLAYER.step = Player_Hit;
            PLAYER.step_s = 1;
        }
    }
}

INCLUDE_ASM("ric/nonmatchings/1AC60", func_8015A9B0);

void func_8015AFE0(void) {
    if (PLAYER.step_s == 0) {
        PLAYER.velocityY += 0x3800;
        if (PLAYER.velocityY > 0) {
            PLAYER.velocityY = 0;
            PLAYER.step_s = 1;
        }
    } else if (g_Player.unk4E != 0) {
        g_Player.unk46 = 0;
        SetPlayerStep(4);
        func_8015C920(&D_80155528);
        g_Player.unk44 = 0;
    }
    if (g_Player.unk72 != 0) {
        PLAYER.velocityY = 0;
    }
}

void func_8015B098(void) {
    if ((PLAYER.animCurFrame == 0xB5) && (PLAYER.animFrameDuration == 1)) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 35), 0);
        g_api.PlaySfx(NA_SE_UNK_62F);
    }

    if (PLAYER.animFrameDuration < 0) {
        func_8015CD98(0);
        g_Player.unk46 = 0;
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x4500, 33), 0);
        g_Player.D_80072F00[0] = 0x800;
    }

    if (!(g_Player.pl_vram_flag & 1)) {
        func_8015CF08();
        g_Player.unk46 = 0;
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x4500, 33), 0);
        g_Player.D_80072F00[0] = 0x800;
    }
}

void func_8015B18C(void) {
    if (PLAYER.animFrameDuration < 0) {
        func_8015CD98(0);
        g_Player.unk46 = 0;
    }

    if ((g_Player.pl_vram_flag & 1) == 0) {
        func_8015CF08();
        g_Player.unk46 = 0;
    }
}

void func_8015B1E8(void) {
    if (g_Player.unk4E) {
        func_8015CD98(0);
        g_Player.unk46 = 0;
    }

    if ((g_Player.pl_vram_flag & 1) == 0) {
        func_8015CF08();
        g_Player.unk46 = 0;
    }
}

void func_8015B244(void) {
    if (PLAYER.step_s == 0) {
        D_80174F74 = 0x200;
        PLAYER.step_s++;
    } else {
        func_8015C9CC();
        D_80174F74--;
        if (D_80174F74 == 0) {
            g_Player.unk46 = 0;
            func_8015CD98(0);
            g_Player.unk4E = 1;
        }
    }
    if (g_Player.padTapped & PAD_CROSS) {
        func_8015D020();
        g_Player.unk46 = 0;
        g_Player.unk4E = 1;
        D_80174F74 = 0;
    }
    if (!(g_Player.pl_vram_flag & 1)) {
        func_8015CF08();
        g_Player.unk46 = 0;
        g_Player.unk4E = 1;
        D_80174F74 = 0;
    }
}
