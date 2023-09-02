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

void func_801949E8(void) {
    Primitive* prim;

    func_8019498C(g_Dialogue.nextCharY);
    prim = g_Dialogue.prim[g_Dialogue.nextCharY];
    prim->tpage = 0x10;
    prim->clut = g_Dialogue.clutIndex;
    prim->y0 = g_Dialogue.nextLineY;
    prim->u0 = 0;
    prim->x0 = g_Dialogue.startX;
    prim->x0 = prim->x0 + 4;
    prim->v0 = g_Dialogue.nextCharY * 0xC - 0x80;
    prim->u1 = 0xC0;
    prim->v1 = 0xC;
    prim->priority = 0x1FF;
    prim->blendMode = 0;
}

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

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14774", EntityUnkId21);

// appears to load from the CD and freeze the game
INCLUDE_ASM("asm/us/st/dre/nonmatchings/14774", EntityUnkId23);
