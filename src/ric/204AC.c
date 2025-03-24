// SPDX-License-Identifier: AGPL-3.0-or-later

#include "ric.h"

// Same function in DRA is func_8010D59C
void func_8015C4AC(void) {
    byte stackpad[40];
    Primitive* prim;
    s32 i;

    if (g_Entities[1].ext.entSlot1.unk0) {
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
        if (--g_Entities[1].ext.entSlot1.unk3 == 0) {
            g_Entities[1].ext.entSlot1.unk2++;
            g_Entities[1].ext.entSlot1.unk3 =
                D_801545B0[g_Entities[1].ext.entSlot1.unk2];
        }
    }
    if (g_Entities[1].animFrameIdx) {
        g_Entities[1].animFrameIdx--;
        return;
    }
#if !defined(VERSION_PSP)
    prim = &g_PrimBuf[g_Entities[1].primIndex];
#endif
    for (prim = &g_PrimBuf[g_Entities[1].primIndex], i = 0; prim != NULL; i++,
        prim = prim->next) {
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

// Extremely similar to func_8010D800
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
