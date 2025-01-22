// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

void SetPlayerStep(s16 step) {
    PLAYER.step = step;
    PLAYER.step_s = 0;
}

u8 g_D_800ACF18[] = {10, 8, 8, 6, 6, 4, 4,   4,   4, 4,
                     4,  4, 4, 4, 4, 4, 255, 255, 0, 0};

void func_8010D59C(void) {
    byte stackpad[40];
    Primitive* prim;
    s32 i;

    if (g_Entities[1].ext.entSlot1.unk0) {
        return;
    }
    switch (PLAYER.ext.player.anim) {
    case 0x5E:
    case 0x5D:
    case 0x60:
    case 0x61:
    case 0x62:
        g_Entities[1].ext.entSlot1.unk2 = 10;
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
                g_D_800ACF18[g_Entities[1].ext.entSlot1.unk2];
        }
        if (--g_Entities[1].ext.entSlot1.unk3 == 0) {
            g_Entities[1].ext.entSlot1.unk2++;
            g_Entities[1].ext.entSlot1.unk3 =
                g_D_800ACF18[g_Entities[1].ext.entSlot1.unk2];
        }
    }
    if (g_Entities[1].animFrameIdx) {
        g_Entities[1].animFrameIdx--;
        return;
    }
    prim = &g_PrimBuf[g_Entities[1].primIndex];
    for (i = 0; i < 6; i++) {
        if (i == g_Entities[1].entityId) {
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            prim->x0 = PLAYER.posX.i.hi;
            prim->y0 = PLAYER.posY.i.hi;
            prim->x1 = PLAYER.animCurFrame;
            prim->y1 = 0;
            prim->x2 = PLAYER.facingLeft;
            prim->y2 = PLAYER.palette;
        }
        prim = prim->next;
    }
    g_Entities[1].animFrameIdx = 2;
    g_Entities[1].entityId++;
    if (g_Entities[1].entityId >= 6) {
        g_Entities[1].entityId = 0;
    }
}

u8 g_shadowOpacityReductionTable[] = {
    4, 4, 4, 4, 6, 6, 6, 6, 8, 8, 16, 16, 16, 16, 16, 16};
u8 g_D_800ACF3C[] = {8,  12, 16, 20, 24, 28, 32, 32,
                     32, 32, 32, 32, 32, 32, 32, 32};

// Equivalent in RIC is func_8015C6D4
void func_8010D800(void) {
    byte pad[0x28];
    PlayerDraw* plDraw;
    Primitive* prim;
    s32 i;
    u8 temp_t0;
    u8 temp_t1;
    u8 temp_t2;

    temp_t2 = g_Entities[1].ext.entSlot1.unk1;
    prim = &g_PrimBuf[g_Entities[1].primIndex];
    plDraw = &g_PlayerDraw[1];
    temp_t1 = g_shadowOpacityReductionTable[g_Entities[1].ext.entSlot1.unk2];
    temp_t0 = g_D_800ACF3C[g_Entities[1].ext.entSlot1.unk2];

    for (i = 0; i < 6; prim = prim->next, i++) {
        if (prim->r0 > temp_t0) {
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
        if (prim->r0 <= temp_t0) {
            prim->x1 = 0;
        }
        if (!((i ^ g_Timer) & 1)) {
            continue;
        }

        g_Entities[(i / 2) + 1].posX.i.hi = prim->x0;
        g_Entities[(i / 2) + 1].posY.i.hi = prim->y0;
        g_Entities[(i / 2) + 1].animCurFrame = prim->x1;
        g_Entities[(i / 2) + 1].drawMode = prim->y1;
        g_Entities[(i / 2) + 1].facingLeft = prim->x2;
        g_Entities[(i / 2) + 1].palette = prim->y2;
        g_Entities[(i / 2) + 1].zPriority = PLAYER.zPriority - 2;
        if (temp_t2) {
            g_Entities[(i / 2) + 1].animCurFrame = 0;
            prim->x1 = 0;
        }

        PRED(plDraw) = PBLU(plDraw) = prim->r0;
        PGRN(plDraw) = prim->b0;
        plDraw->enableColorBlend = true;
        plDraw++;
    }
}

// Unused; deadstripped on PSP
void func_8010DA2C(AnimationFrame* frames) {
    g_CurrentEntity->anim = frames;
    g_CurrentEntity->animFrameDuration = 0;
    g_CurrentEntity->animFrameIdx = 0;
}

void SetPlayerAnim(u8 anim) {
    g_CurrentEntity->ext.player.anim = anim;
    g_CurrentEntity->animFrameDuration = 0;
    g_CurrentEntity->animFrameIdx = 0;
}

AnimationFrame* func_8010DA70(AnimationFrame** frames) {
    u16* anim;
    s32 idx;
    u16* subanim;
    s32 var_s1;
    s32 idxSub;

    anim = (u16*)frames[g_CurrentEntity->ext.player.anim];
    idx = 0;
    var_s1 = 0;
    while (true) {
        if ((&anim[idx * 2])[0] == 0xFFFD) {
            for(idxSub = 0; true; idxSub++, var_s1++){
                subanim = (u16*)D_800B0594[(&anim[idx * 2])[1] & 0xFF];
                if ((&subanim[idxSub * 2])[0] == 0xFFFF) {
                    idx++;
                    // Probably fake. Makes PSP registers match.
                    idxSub = idxSub;
                    break;
                }
                if (var_s1 == g_CurrentEntity->animFrameIdx) {
                    return (AnimationFrame*)&subanim[idxSub * 2];
                }
            }
        } else if (var_s1 == g_CurrentEntity->animFrameIdx) {
            return (AnimationFrame*)(anim + idx * 2);
        } else {
            var_s1++;
            idx++;
        }
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", UpdateUnarmedAnim);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_8010DBFC);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", UpdateAnim);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_psp_09117538);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_8010DFF0);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_8010E0A8);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_psp_091176D8);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_psp_091176F0);

void func_8010E168(s32 arg0, s16 arg1) {
    if (arg0 == 0) {
        // Create factory with unkA0 = 0x1500, blueprint #44.
        // Blueprint 44 is to make child entity #11, or EntityPlayerBlinkWhite
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(44, 0x15), 0);
        if (g_Player.timers[13] <= arg1) {
            g_Player.timers[13] = arg1;
        }
    } else if (g_Player.timers[14] <= arg1) {
        g_Player.timers[14] = arg1;
    }
}

void DecelerateX(s32 amount) {
    if (g_CurrentEntity->velocityX < 0) {
        g_CurrentEntity->velocityX += amount;
        if (g_CurrentEntity->velocityX > 0) {
            g_CurrentEntity->velocityX = 0;
        }
    } else {
        g_CurrentEntity->velocityX -= amount;
        if (g_CurrentEntity->velocityX < 0) {
            g_CurrentEntity->velocityX = 0;
        }
    }
}

void DecelerateY(s32 amount) {
    if (g_CurrentEntity->velocityY < 0) {
        g_CurrentEntity->velocityY += amount;
        if (g_CurrentEntity->velocityY > 0) {
            g_CurrentEntity->velocityY = 0;
        }
    } else {
        g_CurrentEntity->velocityY -= amount;
        if (g_CurrentEntity->velocityY < 0) {
            g_CurrentEntity->velocityY = 0;
        }
    }
}

s32 CheckMoveDirection(void) {
    if (g_Player.unk44 & 2) {
        return 0;
    }
    if (PLAYER.facingLeft == 1) {
        if (g_Player.padPressed & PAD_RIGHT) {
            PLAYER.facingLeft = 0;
            g_Player.unk4C = 1;
            return -1;
        } else if (g_Player.padPressed & PAD_LEFT) {
            return 1;
        }
    } else {
        if (g_Player.padPressed & PAD_RIGHT) {
            return 1;
        }
        if (g_Player.padPressed & PAD_LEFT) {
            PLAYER.facingLeft = 1;
            g_Player.unk4C = 1;
            return -1;
        }
    }
    return 0;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_psp_09117A90);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", SetSpeedX);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_psp_09117B78);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_8010E3E0);
