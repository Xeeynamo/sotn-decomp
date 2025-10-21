// SPDX-License-Identifier: AGPL-3.0-or-later
#if defined(VERSION_PSP) || defined(VERSION_HD)
#include "cutscene_actor_name_psp.h"
#else
extern const char* actor_names[];

#ifndef DRAW_NAME_ACTOR_INDEX
#define DRAW_NAME_ACTOR_INDEX actorIndex
#endif

// Creates primitives for the actor name at the head of the dialogue
static void DrawCutsceneActorName(u16 actorIndex, Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 x;
    u16 chCount;
    const char* actorName;
    char ch;

    actorName = actor_names[DRAW_NAME_ACTOR_INDEX];
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
    actorName = actor_names[DRAW_NAME_ACTOR_INDEX];
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
#ifdef DRAW_NAME_PRIM_Y0
            prim->y0 = DRAW_NAME_PRIM_Y0;
#else
            prim->y0 = g_Dialogue.startY + 6;
#endif
            prim = prim->next;
            x += FONT_GAP;
        }
    }
}
#endif
