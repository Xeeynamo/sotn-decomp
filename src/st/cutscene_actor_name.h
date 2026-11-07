// SPDX-License-Identifier: AGPL-3.0-or-later
#if TARGET == TARGET_PSP
// Based on version JP 1.0 but accounts for multiple languages
#include "cutscene_actor_name_psp.h"

#elif VERSION <= VER_JP10
// Creates primitives for the actor name at the head of the dialogue.
// Function is drastically different than JP 1.1 and above.
void DrawCutsceneActorName(u16 actorIndex, Entity* self) {
    Primitive* prim;
    u16 ch;
    u16 i;
    s16 x;
    u16 actorNameStartIndex;
    u16* actorName;
    s32 primIndex;
    u8* len;

    primIndex = g_api.AllocPrimitives(PRIM_SPRT, actor_prims[actorIndex]);
    if (primIndex == -1) {
        DestroyEntity(self);
        return;
    }

    g_Dialogue.primIndex[1] = primIndex;
    prim = &g_PrimBuf[primIndex];
    x = 0x38;
    len = actor_name_len;
    actorNameStartIndex = 0;
    for (i = 0; i < actorIndex; i++) {
        actorNameStartIndex += *len & 0x7F;
        len++;
    }
    actorName = &actor_names[actorNameStartIndex];
    while (prim) {
        prim->type = PRIM_SPRT;
        prim->tpage = 0x1E;
        prim->clut = PAL_UNK_196;
        ch = *actorName++;
        prim->u0 = (s8)((ch & 0xF) * FONT_W);
        prim->v0 = (s8)((ch & 0xF0) >> 1);
        prim->u1 = prim->v1 = FONT_W;
        prim->priority = 0x1FF;
        prim->drawMode = DRAW_HIDE;
        prim->x0 = x;
        prim->y0 = g_Dialogue.startY + 6;
        if (ch & 0xF000) {
            prim = prim->next;
            prim->type = PRIM_SPRT;
            prim->tpage = 0x1E;
            prim->clut = PAL_UNK_196;
            if (ch & 0x4000) {
                prim->u0 = 0x78;
            } else {
                prim->u0 = 0x70;
            }
            prim->v0 = 0x48;
            prim->u1 = prim->v1 = FONT_W;
            prim->priority = 0x1FF;
            prim->drawMode = DRAW_HIDE;
            prim->x0 = x;
            prim->y0 = g_Dialogue.startY - 2;
        }
        x += FONT_GAP;
        prim = prim->next;
    }
}
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
            prim->clut = PAL_UNK_196;
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
