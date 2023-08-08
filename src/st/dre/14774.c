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

s32 func_801947C8(s32 arg0) {
    Primitive* prim;
    s16 firstPrimIndex;

    firstPrimIndex = g_api.AllocPrimitives(PRIM_SPRT, 7);
    D_801A3F10[0] = firstPrimIndex;
    if (firstPrimIndex == -1) {
        D_801A3F10[0] = 0;
        return 0;
    }
    D_801A3ED8 = arg0;
    D_801A3F14 = 0;
    D_801A3F0C = -1;
    D_801A3F08 = -1;
    func_80194774();

    if (prim && prim) { // !FAKE
    }

    prim = D_801A3EF0[0] = &g_PrimBuf[D_801A3F10[0]];

    prim->blendMode = BLEND_VISIBLE;
    prim = D_801A3EF0[1] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = D_801A3EF0[2] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = D_801A3EF0[3] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = D_801A3EF0[4] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = D_801A3EF0[5] = prim->next;

    prim->type = 4;
    prim->blendMode = BLEND_VISIBLE;

    prim = prim->next;
    prim->type = PRIM_G4;
    prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0xFF;
    prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->g0 = prim->g1 = prim->g2 =
        prim->g3 = 0;
    prim->x0 = prim->x2 = 4;
    prim->x1 = prim->x3 = 0xF8;
    prim->priority = 0x1FD;
    prim->blendMode = BLEND_VISIBLE;

    prim = prim->next;
    prim->type = PRIM_TILE;
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

INCLUDE_ASM("asm/us/st/dre/nonmatchings/14774", func_80194FF4);

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

// Fades to white
INCLUDE_ASM("asm/us/st/dre/nonmatchings/14774", EntityFadeToWhite1);

// Fades to white ID 24
INCLUDE_ASM("asm/us/st/dre/nonmatchings/14774", EntityFadeToWhite2);
