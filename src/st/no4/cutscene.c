// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"
#include "../pfn_entity_update.h"
#include <cutscene.h>

extern Dialogue3 g_Dialogue;

static void CutsceneUnk1(void) {
    g_Dialogue.nextCharX = 2;
    g_Dialogue.nextCharY = 0;
    g_Dialogue.nextCharTimer = 0;
    g_Dialogue.unkB = 8;
}

#if defined(VERSION_PC)
#define NUM_CUTSCENE_PRIM 6
#else
#define NUM_CUTSCENE_PRIM 5
#endif

static u8 SetCutsceneScript(u8* script) {
    Primitive* prim;

    g_Dialogue.primIndex[2] =
        g_api.AllocPrimitives(PRIM_SPRT, NUM_CUTSCENE_PRIM);

    if (g_Dialogue.primIndex[2] != -1) {
        g_Dialogue.scriptCur = script;
        g_Dialogue.primIndex[1] = -1;
        g_Dialogue.primIndex[0] = -1;
        CutsceneUnk1();

        prim = g_Dialogue.prim[0] = &g_PrimBuf[g_Dialogue.primIndex[2]];

        prim->drawMode = DRAW_HIDE;
        prim = g_Dialogue.prim[1] = prim->next;

        prim->drawMode = DRAW_HIDE;
        prim = g_Dialogue.prim[2] = prim->next;

        prim->drawMode = DRAW_HIDE;
        prim = g_Dialogue.prim[3] = prim->next;

#ifdef VERSION_PSP
        prim->drawMode = DRAW_HIDE;
        prim = g_Dialogue.prim[4] = prim->next;
#endif

        prim->type = PRIM_GT4;
        prim->drawMode = DRAW_HIDE;

        prim = prim->next;
        prim->type = PRIM_G4;
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
            prim->g2 = prim->g3 = prim->b2 = prim->b3 = 0;
        prim->b0 = prim->b1 = 0x7F;
        prim->x0 = prim->x2 = 4;
        prim->x1 = prim->x3 = 0xF8;
        prim->priority = 0x1FD;
        prim->drawMode = DRAW_HIDE;

        prim = prim->next;
        prim->type = PRIM_TILE;
        prim->r0 = prim->g0 = prim->b0 = 0x10;
        prim->x0 = 3;
        prim->y0 = 0x2F;
        prim->v0 = 0x4A;
        prim->priority = 0x1FC;
        prim->drawMode = DRAW_HIDE;
        return 1;
    }

    g_Dialogue.primIndex[2] = 0;
    return 0;
}

static void CutsceneUnk3(s16 yOffset) {
    RECT rect;

    rect.x = 0;
    rect.y = (yOffset * 12) + 0x180;
    rect.w = 64;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

static void CutsceneUnk4(s32 nextLineY) {
    Primitive* prim;

    CutsceneUnk3(g_Dialogue.nextCharY);
    prim = g_Dialogue.prim[g_Dialogue.nextCharY];
    prim->tpage = 0x10;
    prim->clut = 0x1A1;
    prim->x0 = 0x38;
    prim->y0 = nextLineY + 0x2C;
    prim->u0 = 0;
    prim->v0 = nextLineY + -0x80;
    prim->u1 = 0xC0;
    prim->v1 = 0xC;
    prim->priority = 0x1FF;
    prim->drawMode = DRAW_DEFAULT;
}

static const char* actor_names[] = {_S("Ferryman")};
// Creates primitives for the actor name at the head of the dialogue
static void DrawCutsceneActorName(u16 actorIndex, Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 x;
    u16 chCount;
    const char* actorName;
    char ch;

    actorName = actor_names[0];
    chCount = 0;
    while (true) {
        ch = *actorName++;
        if (ch == DIAG_EOL) {
            ch = *actorName++;
            if (ch == DIAG_EOS) {
                break;
            }
        }
        if (ch == CH(' ')) {
            continue;
        }
        chCount++;
    }

    // Create chCount amount of sprites based on the actor name's letter count
    primIndex = g_api.AllocPrimitives(PRIM_SPRT, chCount);
    if (primIndex == -1) {
        DestroyEntity(self);
        return;
    }

    // Fill prims to render the actor name on screen
    prim = &g_PrimBuf[primIndex];
    g_Dialogue.primIndex[1] = primIndex;
    actorName = actor_names[0];
    x = 0x38;
    while (prim != NULL) {
        ch = *actorName++;
        if (ch == CH(' ')) {
            x += FONT_SPACE;
        } else {
            prim->type = PRIM_SPRT;
            prim->tpage = 0x1E;
            prim->clut = 0x196;
            prim->u0 = (ch & 0x0F) * FONT_W;
            prim->v0 = (ch & 0xF0) / (FONT_H / 4);
            prim->v1 = FONT_H;
            prim->u1 = FONT_W;
            prim->priority = 0x1FF;
            prim->drawMode = DRAW_HIDE;
            prim->x0 = x;
            prim->y0 = 0x1E;
            prim = prim->next;
            x += FONT_GAP;
        }
    }
}

static void ScaleCutsceneAvatar(const u8 ySteps) {
    const int PrimCount = 5;
    Primitive* prim;
    s32 primIndex;
    s32 i;

    primIndex = g_Dialogue.nextCharY + 1;
    while (primIndex >= PrimCount) {
        primIndex -= PrimCount;
    }
    if (g_CurrentEntity->step_s == 0) {
        prim = g_Dialogue.prim[primIndex];
        prim->v0 += ySteps;
        prim->v1 -= ySteps;
        if (prim->v1 == 0) {
            g_CurrentEntity->step_s++;
            prim->drawMode = DRAW_HIDE;
        }
    }

    for (i = 0; i < PrimCount; i++) {
        if (i != primIndex) {
            prim = g_Dialogue.prim[i];
            prim->y0 -= ySteps;
        }
    }
    g_Dialogue.portraitAnimTimer++;
}

extern s32 g_SkipCutscene;
extern u32 g_CutsceneFlags;
extern s32 g_IsCutsceneDone;

extern u8 D_us_80185354[]; // ferryman left
extern u8 D_us_801853B7[]; // ferryman right

INCLUDE_ASM("st/no4/nonmatchings/cutscene", NO4_EntityCutscene);
