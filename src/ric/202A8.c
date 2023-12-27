
#include "ric.h"

void func_8015C2A8(void) {
    bool loadAnim = 0;
    s32 temp;

    FntPrint("pl_vram_flag:%04x\n", g_Player.pl_vram_flag);
    FntPrint("pl_high_jump_timer:%04x\n", g_Player.pl_high_jump_timer);
    FntPrint("pl_step_s:%02x\n", PLAYER.step_s);
    g_Player.pl_high_jump_timer++;

    switch (PLAYER.step_s) {
    case 0:
        if (g_Player.padPressed & (PAD_LEFT | PAD_RIGHT)) {
            if (PLAYER.facingLeft == 0) {
                temp = g_Player.padPressed & PAD_RIGHT;
            } else {
                temp = g_Player.padPressed & PAD_LEFT;
            }
            if (temp == 0) {
                func_8015C93C(0x1000);
            }
        } else {
            func_8015C93C(0x1000);
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
        func_8015C920(&D_80155534);
        SetPlayerStep(4);
    }
}

// Same function in DRA is func_8010D59C
void func_8015C4AC(void) {
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

INCLUDE_ASM("asm/us/ric/nonmatchings/202A8", func_8015C6D4);

void SetPlayerStep(PlayerSteps step) {
    PLAYER.step = step;
    PLAYER.step_s = 0;
}
