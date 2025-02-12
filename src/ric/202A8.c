// SPDX-License-Identifier: AGPL-3.0-or-later

#include "ric.h"

void RicHandleHighJump(void) {
    bool loadAnim = 0;
    s32 temp;

#if defined(VERSION_US)
    FntPrint("pl_vram_flag:%04x\n", g_Player.pl_vram_flag);
    FntPrint("pl_high_jump_timer:%04x\n", g_Player.pl_high_jump_timer);
    FntPrint("pl_step_s:%02x\n", PLAYER.step_s);
#endif
    g_Player.pl_high_jump_timer++;

    switch (PLAYER.step_s) {
    case 0:
        if (g_Player.padPressed & (PAD_LEFT | PAD_RIGHT)) {
            if (!PLAYER.facingLeft) {
                temp = g_Player.padPressed & PAD_RIGHT;
            } else {
                temp = g_Player.padPressed & PAD_LEFT;
            }
            if (temp == 0) {
                RicDecelerateX(0x1000);
            }
        } else {
            RicDecelerateX(0x1000);
        }

        if (g_Player.pl_vram_flag & 2) {
            func_80158B04(3);
            g_Player.pl_high_jump_timer = 0;
            PLAYER.step_s = 2;
        } else if (g_Player.pl_high_jump_timer >= 0x1D) {
            PLAYER.step_s = 1;
            PLAYER.velocityY = -0x60000;
        }
        break;

    case 1:
        if (g_Player.pl_vram_flag & 2) {
            PLAYER.step_s = 2;
            func_80158B04(3);
            g_Player.pl_high_jump_timer = 0;
        } else {
            PLAYER.velocityY += 0x6000;
            if (PLAYER.velocityY > 0x8000) {
                loadAnim = true;
            }
        }
        break;

    case 2:
        if (g_Player.pl_high_jump_timer >= 5) {
            loadAnim = true;
        }
        break;
    }

    if (loadAnim) {
        RicSetAnimation(D_80155534);
        RicSetStep(PL_S_JUMP);
    }
}

// Same function in DRA is UpdateAfterImage
void RicUpdateAfterImage(void) {
    byte stackpad[40];
    Primitive* prim;
    s32 i;

    if (g_Entities[1].ext.entSlot1.unk0 != 0) {
        return;
    }
    if ((g_Player.padTapped & GAMEBUTTONS) ||
        ((g_Player.padHeld ^ g_Player.padPressed) & g_Player.padHeld &
         GAMEBUTTONS) ||
        (PLAYER.velocityY > FIX(0.5))) {
        g_Entities[1].ext.entSlot1.unk2 = 0;
        g_Entities[1].ext.entSlot1.unk3 = 0;
    } else {
        if (g_Entities[1].ext.entSlot1.unk2 >= 10) {
            return;
        }
        if (g_Entities[1].ext.entSlot1.unk3 == 0) {
            g_Entities[1].ext.entSlot1.unk3 =
                D_801545B0[g_Entities[1].ext.entSlot1.unk2];
        }
        if (!(--g_Entities[1].ext.entSlot1.unk3 & 0xFF)) {
            g_Entities[1].ext.entSlot1.unk2++;
            g_Entities[1].ext.entSlot1.unk3 =
                D_801545B0[g_Entities[1].ext.entSlot1.unk2];
        }
    }
    if (g_Entities[1].animFrameIdx != 0) {
        g_Entities[1].animFrameIdx--;
        return;
    }
    prim = &g_PrimBuf[g_Entities[1].primIndex];
    for (prim = &g_PrimBuf[g_Entities[1].primIndex], i = 0; prim != NULL;
         prim = prim->next, i++) {
        if (i == g_Entities[1].entityId) {
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            prim->x0 = PLAYER.posX.i.hi;
            prim->y0 = PLAYER.posY.i.hi;
            prim->x1 = PLAYER.animCurFrame;
            prim->y1 = 0;
            prim->x2 = PLAYER.facingLeft;
            prim->y2 = PLAYER.palette;
        }
    }
    g_Entities[1].animFrameIdx = 2;
    g_Entities[1].entityId++;
    if (g_Entities[1].entityId >= 6) {
        g_Entities[1].entityId = 0;
    }
}

// Extremely similar to UpdateAfterImageOpacity
void func_8015C6D4(void) {
    byte pad[0x28];
    PlayerDraw* plDraw;
    Primitive* prim;
    s32 entNum;
    s32 i;
    u8 temp_t0;
    u8 temp_t1;
    u8 temp_t2;

    prim = &g_PrimBuf[g_Entities[1].primIndex];
    temp_t2 = g_Entities[1].ext.entSlot1.unk1;
    temp_t1 = D_801545C4[g_Entities[1].ext.entSlot1.unk2];
    temp_t0 = D_801545D4[g_Entities[1].ext.entSlot1.unk2];

    plDraw = &g_PlayerDraw[1];
    for (i = 0; prim != NULL; prim = prim->next, i++) {
        if (temp_t0 < prim->r0) {
            prim->r0 -= temp_t1;
        }
        if (prim->r0 < 112 && prim->b0 < 240) {
            prim->b0 += 6;
        }
        if (prim->r0 < 88) {
            prim->y1 = 16;
        } else {
            prim->y1 = 0;
        }
        if (temp_t0 >= prim->r0) {
            prim->x1 = 0;
        }
        if (!((i ^ g_Timer) & 1)) {
            continue;
        }

        entNum = (i / 2) + 1;
        g_Entities[entNum].posX.i.hi = prim->x0;
        g_Entities[entNum].posY.i.hi = prim->y0;
        g_Entities[entNum].animCurFrame = prim->x1;
        g_Entities[entNum].drawMode = prim->y1;
        g_Entities[entNum].facingLeft = prim->x2;
        g_Entities[entNum].palette = prim->y2;
        g_Entities[entNum].zPriority = PLAYER.zPriority - 2;
        if (temp_t2) {
            g_Entities[entNum].animCurFrame = 0;
            prim->x1 = 0;
        }

        plDraw->r0 = plDraw->r1 = plDraw->r2 = plDraw->r3 = plDraw->b0 =
            plDraw->b1 = plDraw->b2 = plDraw->b3 = prim->r0;
        plDraw->g0 = plDraw->g1 = plDraw->g2 = plDraw->g3 = prim->b0;
        plDraw->enableColorBlend = true;
        plDraw++;
    }
}

void RicSetStep(int step) {
    PLAYER.step = step;
    PLAYER.step_s = 0;
}
