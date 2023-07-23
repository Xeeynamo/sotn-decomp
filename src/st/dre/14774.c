#include "dre.h"

void func_80194774(void) {
    D_801A3EE4 = 2;
    D_801A3EE2 = 2;
    D_801A3EE6 = 0;
    D_801A3EEA = 0;
    D_801A3EEE = 0;
    D_801A3EEF = 8;
    D_801A3EDE = D_801A3EE0 + 20;
}

s32 func_801947C8(s32 textDialogue) {
    Primitive* prim;
    s16 firstPrimIndex;

    firstPrimIndex = g_api.AllocPrimitives(PRIM_SPRT, 7);
    g_Dialogue.primIndex[2] = firstPrimIndex;
    if (firstPrimIndex == -1) {
        g_Dialogue.primIndex[2] = 0;
        return 0;
    }
    g_Dialogue.nextCharDialogue = textDialogue;
    g_Dialogue.unk3C = 0;
    g_Dialogue.primIndex[1] = -1;
    g_Dialogue.primIndex[0] = -1;
    func_80194774();

    if (prim && prim) { // !FAKE
    }

    prim = g_Dialogue.prim[0] = &g_PrimBuf[g_Dialogue.primIndex[2]];

    prim->blendMode = BLEND_VISIBLE;
    prim = g_Dialogue.prim[1] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = g_Dialogue.prim[2] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = g_Dialogue.prim[3] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = g_Dialogue.prim[4] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = g_Dialogue.prim[5] = prim->next;

    prim->type = 4;
    prim->blendMode = BLEND_VISIBLE;

    prim = prim->next;
    prim->type = 3;
    prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0xFF;
    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;
    prim->x0 = prim->x2 = 4;
    prim->x1 = prim->x3 = 0xF8;
    prim->priority = 0x1FD;
    prim->blendMode = BLEND_VISIBLE;

    prim = prim->next;
    prim->type = 1;
    prim->x0 = 3;
    prim->y0 = 0x2F;
    prim->v0 = 0x4A;
    prim->r0 = prim->g0 = prim->b0 = 0xFF;
    prim->priority = 0x1FC;
    prim->blendMode = BLEND_VISIBLE;
    return 1;
}

void func_8019498C(s16 yOffset) {
    RECT rect;

    rect.y = (yOffset * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14774", func_801949E8);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14774", func_80194AA0);

void func_80194C24(s32 arg0) {
    D_801A3F18 = arg0 + 0x100000;
    D_801A3F16 = 0;
    D_801A3F14 = 1;
}

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14774", func_80194C50);

void func_80194F14(Entity* self) {
    /** TODO: !FAKE
     * do while (0) fixed instruction reordering at
     * entity->flags ^= FLAG_HAS_PRIMS;
     * but intruduces a problem in PlaySfx, which is fixed
     * by using gameApi pointer.
     */
    GameApi* gameApi;

    if (g_pads[0].tapped == PAD_START) {
        D_801A3ED4 = 1;
        g_api.FreePrimitives(self->primIndex);
        do {
            self->flags ^= FLAG_HAS_PRIMS;
        } while (0);
        if (D_801A3F0C != -1) {
            g_api.FreePrimitives(D_801A3F0C);
        }
        if (D_801A3F08 != -1) {
            g_api.FreePrimitives(D_801A3F08);
        }
        gameApi = &g_api;
        (*gameApi).PlaySfx(SET_STOP_MUSIC);
        self->step = 1;
        self->step_s = 0;
    }
}

void func_80194FF4(u8 ySteps) {
    Primitive* prim;
    s32 primIndex;
    s32 i;

    primIndex = g_Dialogue.nextCharY + 1;
    while (primIndex >= 5) {
        primIndex -= 5;
    }
    if (g_CurrentEntity->step_s == 0) {
        prim = g_Dialogue.prim[primIndex];
        prim->v1 -= ySteps;
        prim->v0 += ySteps;
        if (prim->v1 == 0) {
            g_CurrentEntity->step_s++;
            prim->blendMode = BLEND_VISIBLE;
        }
    }

    for (i = 0; i < 5; i++) {
        if (i != primIndex) {
            prim = g_Dialogue.prim[i];
            prim->y0 -= ySteps;
        }
    }
    g_Dialogue.portraitAnimTimer++;
}

// dialogue with mother opens as alucard walks right ID 20
INCLUDE_ASM("asm/us/st/dre/nonmatchings/14774", EntitySuccubusCutscene);

void func_801961DC(s16 arg0) {
    s16 temp_v0 = arg0 - *(s16*)D_8009740C;

    if (temp_v0 > 1) {
        D_8009740C[0]++;
    } else if (temp_v0 < -1) {
        D_8009740C[0]--;
    } else {
        D_8009740C[0] = arg0;
    }
}

extern s32 D_80097400;

void EntityCSMoveAlucard(Entity* self) {
    Unkstruct8* currentRoomTileLayout = &g_CurrentRoomTileLayout;
    Entity* player = &PLAYER;
    s16 posX;

    FntPrint("step %x\n", self->step);
    if ((D_801A3ED4 != 0) && (self->step < 8)) {
        SetStep(8);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_8018047C);
        D_8003C8B8 = 0;
        D_80097400 = 1;
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 1;
        if (g_DemoMode != Demo_None) {
            self->ext.generic.unk7C.s = 64;
            break;
        }
        self->ext.generic.unk7C.s = 128;
        break;

    case 1:
        g_Player.D_80072EF4 = 0;
        if (self->ext.generic.unk7C.u != 0) {
            self->ext.generic.unk7C.u--;
        }
        if (g_Player.unk0C & 7) {
            if (g_blinkTimer & 1) {
                if (!(g_Player.unk0C & 1)) {
                    if (!(g_Player.unk0C & 2)) {
                        if (g_Player.unk0C & 4) {
                            g_Player.D_80072EF4 = 2;
                        }
                    } else {
                        g_Player.D_80072EF4 = 4;
                    }
                } else {
                    g_Player.D_80072EF4 = 8;
                }
            }
        } else if (self->ext.generic.unk7C.u == 0) {
            self->step++;
            g_Player.D_80072EF4 = 0x2000;
        }
        g_Player.D_80072EFC = 1;
        break;

    case 2: // Alucard walks forward
        g_Player.D_80072EF4 = 0x2000;
        posX = player->posX.i.hi + currentRoomTileLayout->unkA;
        if (posX > 256) {
            if (!(D_801A3F84 & 1)) {
                D_801A3F84 |= 1;
            }
        }
        if (posX > 288) {
            g_Player.D_80072EF4 = 0;
            player->posX.i.hi = 288 - currentRoomTileLayout->unkA;
            self->step++;
        }
        g_Player.D_80072EFC = 1;
        return;

    case 3: // Alucard stops walking
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 1;
        func_801961DC(0x20);
        if (D_801A3F84 & 2) {
            self->step++;
        }
        break;

    case 4:
        g_Player.D_80072EF4 = 0x2000;
        posX = player->posX.i.hi + currentRoomTileLayout->unkA;
        if (posX > 256) {
            if (!(D_801A3F84 & 1)) {
                D_801A3F84 |= 1;
            }
        }
        if (posX > 352) {
            g_Player.D_80072EF4 = 0;
            player->posX.i.hi = 352 - currentRoomTileLayout->unkA;
            posX = 352;
            self->step++;
        }
        *D_8009740C = posX - 256;
        g_Player.D_80072EFC = 1;
        break;

    case 5: // Conversation with fake lisa
        g_Player.D_80072EFC = 1;
        if (D_801A3F84 & 8) {
            SetStep(6);
        }
        break;

    case 6: // Alucard's reaction to realizing she's not his mother
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_80180944, self) == 0) {
            SetStep(7);
            break;
        }
        player->animCurFrame = self->animCurFrame;
        break;

    case 7:
        g_Player.D_80072EFC = 1;
        if (D_801A3F84 & 0x200) {
            SetStep(8);
        }
        break;

    case 8:
        func_801961DC(0x80);
        if (*D_8009740C == 0x80) {
            D_8003C8B8 = 1;
            if (D_80097400 != 0) {
                D_80097400 = 0;
            }
            DestroyEntity(self);
        }
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 1;
        break;
    }
}

const u32 rodata_footer = 0;

// appears to load from the CD and freeze the game
INCLUDE_ASM("asm/us/st/dre/nonmatchings/14774", EntityUnkId23);
