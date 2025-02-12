// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../st0/st0.h"
#include <cutscene.h>

extern Dialogue g_Dialogue;
// clang-format off
static u16 actor_names_en[] = {
    CH('R'), CH('i'), CH('c'), CH('h'), CH('t'), CH('e'), CH('r'),
    CH('D'), CH('r'), CH('a'), CH('c'), CH('u'), CH('l'), CH('a'),
    CH('D'), CH('e'), CH('a'), CH('t'), CH('h'),
    CH('A'), CH('l'), CH('u'), CH('c'), CH('a'), CH('r'), CH('d'),
    CH('M'), CH('a'), CH('r'), CH('i'), CH('a'),
    CH('L'), CH('i'), CH('b'), CH('r'), CH('a'), CH('r'), CH('i'), CH('a'), CH('n'),
    CH('L'), CH('i'), CH('s'), CH('a'),
    CH('S'), CH('u'), CH('c'), CH('c'), CH('u'), CH('b'), CH('u'), CH('s'),
    CH('F'), CH('e'), CH('r'), CH('r'), CH('y'), CH('m'), CH('a'), CH('n'),
    CH('S'), CH('h'), CH('a'), CH('f'), CH('t')};
static u8 actor_name_len_en[] = {7, 7, 5, 7, 5, 9, 4, 8, 8, 5};

static u16 actor_names_sp[] = {
    CH('R'), CH('i'), CH('c'), CH('h'), CH('t'), CH('e'), CH('r'),
    CH('D'), CH('r'), CH('a'), CH('c'), CH('u'), CH('l'), CH('a'),
    CH('D'), CH('e'), CH('a'), CH('t'), CH('h'), 
    CH('A'), CH('l'), CH('u'), CH('c'), CH('a'), CH('r'), CH('d'),
    CH('M'), CH('a'), CH('r'), CH('i'), CH('a'),
    CH('B'), CH('i'), CH('b'), CH('l'), CH('i'), CH('o'), CH('t'), CH('e'), CH('c'), CH('a'), CH('r'), CH('i'), CH('o'),
    CH('L'), CH('i'), CH('s'), CH('a'),
    CH('S'), 0xAC, CH('c'), CH('u'), CH('b'), CH('o'),
    CH('B'), CH('a'), CH('r'), CH('q'), CH('u'), CH('e'), CH('r'), CH('o'),
    CH('S'), CH('h'), CH('a'), CH('f'), CH('t')};
static u8 actor_name_len_sp[] = {7, 7, 5, 7, 5, 13, 4, 6, 8, 5};

static u16 actor_names_it[] = {
    CH('R'), CH('i'), CH('c'), CH('h'), CH('t'), CH('e'), CH('r'),
    CH('D'), CH('r'), CH('a'), CH('c'), CH('u'), CH('l'), CH('a'),
    CH('D'), CH('e'), CH('a'), CH('t'), CH('h'),
    CH('A'), CH('l'), CH('u'), CH('c'), CH('a'), CH('r'), CH('d'),
    CH('M'), CH('a'), CH('r'), CH('i'), CH('a'),
    CH('B'), CH('i'), CH('b'), CH('l'), CH('i'), CH('o'), CH('t'), CH('e'), CH('c'), CH('a'), CH('r'), CH('i'), CH('o'),
    CH('L'), CH('i'), CH('s'), CH('a'),
    CH('S'), CH('u'), CH('c'), CH('c'), CH('u'), CH('b'), CH('u'), CH('s'),
    CH('T'), CH('r'), CH('a'), CH('g'), CH('h'), CH('e'), CH('t'), CH('t'), CH('a'), CH('t'), CH('o'), CH('r'), CH('e'),
    CH('S'), CH('h'), CH('a'), CH('f'), CH('t')};
static u8 actor_name_len_it[] = {7, 7, 5, 7, 5, 13, 4, 8, 13, 5};

static u16 actor_names_fr[] = {
    CH('R'), CH('i'), CH('c'), CH('h'), CH('t'), CH('e'), CH('r'),
    CH('D'), CH('r'), CH('a'), CH('c'), CH('u'), CH('l'), CH('a'),
    CH('D'), CH('e'), CH('a'), CH('t'), CH('h'),
    CH('A'), CH('l'), CH('u'), CH('c'), CH('a'), CH('r'), CH('d'),
    CH('M'), CH('a'), CH('r'), CH('i'), CH('a'),
    CH('B'), CH('i'), CH('b'), CH('l'), CH('i'), CH('o'), CH('t'), CH('h'), 0xA0, CH('c'), CH('a'), CH('i'), CH('r'), CH('e'),
    CH('L'), CH('i'), CH('s'), CH('a'),
    CH('S'), CH('u'), CH('c'), CH('c'), CH('u'), CH('b'), CH('e'),
    CH('P'), CH('a'), CH('s'), CH('s'), CH('e'), CH('u'), CH('r'),
    CH('S'), CH('h'), CH('a'), CH('f'), CH('t')};
static u8 actor_name_len_fr[] = {7, 7, 5, 7, 5, 14, 4, 7, 7, 5};

static u16 actor_names_ge[] = {
    CH('R'), CH('i'), CH('c'), CH('h'), CH('t'), CH('e'), CH('r'),
    CH('D'), CH('r'), CH('a'), CH('c'), CH('u'), CH('l'), CH('a'),
    CH('D'), CH('e'), CH('a'), CH('t'), CH('h'),
    CH('A'), CH('l'), CH('u'), CH('c'), CH('a'), CH('r'), CH('d'),
    CH('M'), CH('a'), CH('r'), CH('i'), CH('a'),
    CH('B'), CH('i'), CH('b'), CH('l'), CH('i'), CH('o'), CH('t'), CH('h'), CH('e'), CH('k'), CH('a'), CH('r'),
    CH('L'), CH('i'), CH('s'), CH('a'),
    CH('S'), CH('u'), CH('k'), CH('k'), CH('u'), CH('b'), CH('u'), CH('s'),
    CH('F'), 0x9D, CH('h'), CH('r'), CH('m'), CH('a'), CH('n'), CH('n'),
    CH('S'), CH('h'), CH('a'), CH('f'), CH('t')};
static u8 actor_name_len_ge[] = {7, 7, 5, 7, 5, 12, 4, 8, 8, 5};
// clang-format on

static u8 D_80180784[] = {0, 64, 0, 0};
static u8 D_80180788[] = {0, 0, 0, 0};
static u16 D_8018078C[] = {0x230, 0x248};
static u16 D_80180790[] = {0, 32};
static u16 D_80180794[] = {0x1A1, 0x1A1};
static s16 D_80180798[] = {
    0x8,  0x13, 0x11, 0x31, 0x4F, 0x26, 0x36, 0x1D, 0x1B, 0x33, 0x2C, 0x21,
    0x19, 0xA,  0x33, 0x1F, 0x48, 0x2F, 0x13, 0x19, 0x4D, 0x4B, 0x17, 0x1D,
    0x12, 0x2,  0x1B, 0x2A, 0x50, 0x45, 0x32, 0xD,  0x2A, 0x4D, 0x6,  0x27,
    0x7,  0x48, 0x2F, 0x1B, 0x36, 0x22, 0x39, 0x14, 0x39, 0x1D, 0xA,  0x35,
    0x10, 0x1B, 0x3D, 0x17, 0x2E, 0xB,  0x49, 0x42, 0x3D, 0x2A, 0x1,  0xC,
    0x1B, 0x34, 0x41, 0x35, 0x8,  0xE,  0x4D, 0x11, 0x34, 0x41, 0x29, 0x48};
s32 D_pspeu_09253F38[] = {0x100, 0};
s32 D_pspeu_09253F40[] = {0x100, 0};

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
        (u8*)GetLang(actor_name_len_en, actor_name_len_fr, actor_name_len_sp,
                     actor_name_len_ge, actor_name_len_it);
    ch = actorNameLength[arg3[actorIndex]];
    primIndex = g_api.AllocPrimBuffers(PRIM_SPRT, ch);
    if (primIndex == -1) {
        DestroyEntity(self);
        return;
    }

    // Pre-calculate primitives that renders the actor's name
    x = 0x38;
    g_Dialogue.primIndex[1] = primIndex;
    prim = &g_PrimBuf[primIndex];
    len = actorNameLength;
    actorNameStartIndex = 0;
    for (i = 0; i < arg3[actorIndex]; i++) {
        actorNameStartIndex += actorNameLength[i];
    }
    actorNames = (u16*)GetLang(
        (u8*)actor_names_en, (u8*)actor_names_fr, (u8*)actor_names_sp,
        (u8*)actor_names_ge, (u8*)actor_names_it);
    actorName = (u16*)(actorNames + actorNameStartIndex);
    while (prim) {
        prim->type = PRIM_SPRT;
        prim->tpage = 0x1E;
        prim->clut = 0x196;
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

#include "../cutscene_unk3.h"
#include "../cutscene_unk4.h"

static void CutsceneUnk1(void) {
    g_Dialogue.nextLineY = g_Dialogue.startY + 0x14;
    g_Dialogue.nextCharX = g_Dialogue.nextLineX = 0;
    g_Dialogue.nextCharY = 0;
    g_Dialogue.unk12 = 0;
    g_Dialogue.nextCharTimer = 0;
    g_Dialogue.unk17 = 2;
}

static u8 SetCutsceneScript(u8* script) {
    Primitive* prim;
    g_Dialogue.primIndex[2] = g_api.AllocPrimBuffers(PRIM_SPRT, 7);
    if (g_Dialogue.primIndex[2] != -1) {
        g_Dialogue.scriptCur = script;
        g_Dialogue.unk3C = 0;
        g_Dialogue.primIndex[1] = -1;
        g_Dialogue.primIndex[0] = -1;
        CutsceneUnk1();

        prim = &g_PrimBuf[g_Dialogue.primIndex[2]];
        g_Dialogue.prim[0] = prim;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;

        g_Dialogue.prim[1] = prim;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;

        g_Dialogue.prim[2] = prim;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;

        g_Dialogue.prim[3] = prim;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;

        g_Dialogue.prim[4] = prim;
        prim->type = PRIM_GT4;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;

        prim->type = PRIM_G4;
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0xFF;
        prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;
        prim->x0 = prim->x2 = 4;
        prim->x1 = prim->x3 = 0xF8;
        prim->priority = 0x1FD;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;

        prim->type = PRIM_TILE;
        prim->r0 = prim->g0 = prim->b0 = 0xFF;
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

#include "../set_cutscene_end.h"

extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[];
#define PfnEntityUpdates OVL_EXPORT(EntityUpdates)
#include "../cutscene_run.h"

INCLUDE_ASM("st/st0_psp/psp/st0_psp/cutscene", ST0_EntityCutscene);
