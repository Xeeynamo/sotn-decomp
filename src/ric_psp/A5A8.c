// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../ric/ric.h"
#include <player.h>

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

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/A5A8", func_8015C6D4);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/A5A8", RicSetStep);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/A5A8", RicSetAnimation);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/A5A8", RicDecelerateX);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/A5A8", RicCheckFacing);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/A5A8", RicSetSpeedX);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/A5A8", func_8015CAAC);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/A5A8", RicSetInvincibilityFrames);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/A5A8", DisableAfterImage);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/A5A8", func_8015CC28);
