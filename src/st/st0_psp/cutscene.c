// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../st0/st0.h"
#include <cutscene.h>

extern Dialogue g_Dialogue;
extern u8 D_pspeu_09253C08[];
extern u8 D_pspeu_09253DE0[];
extern u8 D_pspeu_09253CA0[];
extern u8 D_pspeu_09253E78[];
extern u8 D_pspeu_09253D48[];
extern u8 D_pspeu_09253B80[];
extern u8 D_pspeu_09253D58[];
extern u8 D_pspeu_09253C18[];
extern u8 D_pspeu_09253DF0[];
extern u8 D_pspeu_09253CB0[];

void DrawCutsceneActorName(u16 actorIndex, Entity* self, u16* actorNames,
                           u8* arg3, s32* arg4, s32 nActors) {
    Primitive* prim;
    u16 ch;
    u16 i;
    s16 x;
    u8* actorNameLength;
    u16 actorNameStartIndex;
    u16* actorName;
    s32 primIndex;
    u8* len;

    // Create a certain amount of sprites based on the actor name's letter count
    actorNameLength =
        (u8*)GetLang(D_pspeu_09253C08, D_pspeu_09253DE0, D_pspeu_09253CA0,
                     D_pspeu_09253E78, D_pspeu_09253D48);
    ch = actorNameLength[arg3[actorIndex]];
    primIndex = g_api.AllocPrimitives(PRIM_SPRT, ch);
    if (primIndex == -1) {
        DestroyEntity(self);
        return;
    }

    // Pre-calculate primitives that renders the actor's name
    x = 0x38;
#if defined(VERSION_PSP)
    g_Dialogue.primIndex[0] = primIndex;
#else
    g_Dialogue.primIndex[1] = primIndex;
#endif
    prim = &g_PrimBuf[primIndex];
    len = actorNameLength;
    actorNameStartIndex = 0;
    for (i = 0; i < arg3[actorIndex]; i++) {
        actorNameStartIndex += actorNameLength[i];
    }
    actorNames =
        (u16*)GetLang(D_pspeu_09253B80, D_pspeu_09253D58, D_pspeu_09253C18,
                      D_pspeu_09253DF0, D_pspeu_09253CB0);
    actorName = (u16*)(actorNames + actorNameStartIndex);
    while (prim) {
        prim->type = PRIM_SPRT;
        prim->tpage = 0x1E;
        prim->clut = 0x196;
        ch = *actorName++;
        prim->u0 = (s8)((ch & 0x0F) * FONT_W);
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
            prim->clut = 0x196;
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

INCLUDE_ASM("st/st0_psp/psp/st0_psp/cutscene", func_pspeu_09238F10);

INCLUDE_ASM("st/st0_psp/psp/st0_psp/cutscene", func_pspeu_09238F90);

INCLUDE_ASM("st/st0_psp/psp/st0_psp/cutscene", func_pspeu_09239060);

INCLUDE_ASM("st/st0_psp/psp/st0_psp/cutscene", func_pspeu_092390C0);

INCLUDE_ASM("st/st0_psp/psp/st0_psp/cutscene", func_pspeu_092392D0);

INCLUDE_ASM("st/st0_psp/psp/st0_psp/cutscene", func_pspeu_09239308);

INCLUDE_ASM("st/st0_psp/psp/st0_psp/cutscene", ST0_EntityCutscene);
