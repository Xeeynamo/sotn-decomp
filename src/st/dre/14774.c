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

    prim->drawMode = DRAW_HIDE;
    prim = g_Dialogue.prim[1] = prim->next;

    prim->drawMode = DRAW_HIDE;
    prim = g_Dialogue.prim[2] = prim->next;

    prim->drawMode = DRAW_HIDE;
    prim = g_Dialogue.prim[3] = prim->next;

    prim->drawMode = DRAW_HIDE;
    prim = g_Dialogue.prim[4] = prim->next;

    prim->drawMode = DRAW_HIDE;
    prim = g_Dialogue.prim[5] = prim->next;

    prim->type = 4;
    prim->drawMode = DRAW_HIDE;

    prim = prim->next;
    prim->type = 3;
    prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0xFF;
    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;
    prim->x0 = prim->x2 = 4;
    prim->x1 = prim->x3 = 0xF8;
    prim->priority = 0x1FD;
    prim->drawMode = DRAW_HIDE;

    prim = prim->next;
    prim->type = 1;
    prim->x0 = 3;
    prim->y0 = 0x2F;
    prim->v0 = 0x4A;
    prim->r0 = prim->g0 = prim->b0 = 0xFF;
    prim->priority = 0x1FC;
    prim->drawMode = DRAW_HIDE;
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
    prim->drawMode = DRAW_DEFAULT;
}

// Creates primitives for the actor name at the head of the dialogue
void func_80194AA0(u16 actorIndex, Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 x;
    u16 chCount;
    const char* actorName;
    char ch;

    actorName = D_80180938[actorIndex];
    chCount = 0;
    while (true) {
        ch = *actorName++;
        if (ch == DIAG_EOL) {
            ch = *actorName++;
            if (ch == DIAG_EOS) {
                break;
            }
        }
        if (ch == MENUCHAR(' ')) {
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
    actorName = D_80180938[actorIndex];
    x = 0x38;
    while (prim != NULL) {
        ch = *actorName++;
        if (ch == MENUCHAR(' ')) {
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
            prim->y0 = g_Dialogue.startY + 6;
            prim = prim->next;
            x += FONT_GAP;
        }
    }
}

void func_80194C24(s32 arg0) {
    g_Dialogue.unk40 = arg0 + 0x100000;
    g_Dialogue.timer = 0;
    g_Dialogue.unk3C = 1;
}

void func_80194C50(void) {
    Entity* entity;
    u16 startTimer;
    u8 entityIndex;
    Dialogue* ptr;

    g_Dialogue.timer++;
    // protect from overflows
    if (g_Dialogue.timer > 0xFFFE) {
        g_Dialogue.unk3C = 0;
        return;
    }

    while (true) {
        // Start the dialogue script only if the start timer has passed
        startTimer = (*g_Dialogue.unk40++ << 8) | *g_Dialogue.unk40++;
        if (g_Dialogue.timer < startTimer) {
            // Re-evaluate the condition at the next frame
            g_Dialogue.unk40 -= 2;
            return;
        }

        switch (*g_Dialogue.unk40++) {
        case 0:
            entityIndex = *g_Dialogue.unk40++;
            entity = &g_Entities[STAGE_ENTITY_START + entityIndex];
            DestroyEntity(entity);
            entity->entityId = *g_Dialogue.unk40++;
            entity->pfnUpdate = PfnEntityUpdates[entity->entityId - 1];
            entity->posX.i.hi = *g_Dialogue.unk40++ * 0x10;
            entity->posX.i.hi = *g_Dialogue.unk40++ | entity->posX.i.hi;
            entity->posY.i.hi = *g_Dialogue.unk40++ * 0x10;
            entity->posY.i.hi = *g_Dialogue.unk40++ | entity->posY.i.hi;
            break;

        case 1:
            entityIndex = *g_Dialogue.unk40++;
            entity = &g_Entities[STAGE_ENTITY_START + entityIndex];
            DestroyEntity(entity);
            break;

        case 2:
            if (!((D_801A3F84 >> *g_Dialogue.unk40) & 1)) {
                g_Dialogue.unk40 -= 3;
                g_Dialogue.timer--;
                return;
            }
            D_801A3F84 &= ~(1 << *g_Dialogue.unk40++);
            break;

        case 3:
            D_801A3F84 |= 1 << *g_Dialogue.unk40++;
            break;
        }
    }
}

void func_80194F14(Entity* self) {
    if (g_pads[0].tapped == PAD_START) {
        D_801A3ED4 = 1;
        g_api.FreePrimitives(self->primIndex);
        self->flags ^= FLAG_HAS_PRIMS;
        if (g_Dialogue.primIndex[1] != -1) {
            g_api.FreePrimitives(g_Dialogue.primIndex[1]);
        }
        if (g_Dialogue.primIndex[0] != -1) {
            g_api.FreePrimitives(g_Dialogue.primIndex[0]);
        }
        g_api.PlaySfx(SET_STOP_MUSIC);
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
            prim->drawMode = DRAW_HIDE;
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
INCLUDE_ASM("st/dre/nonmatchings/14774", EntitySuccubusCutscene);

void func_801961DC(s16 arg0) {
    s16 temp_v0 = arg0 - *(s16*)g_unkGraphicsStruct.unkC;

    if (temp_v0 > 1) {
        g_unkGraphicsStruct.unkC++;
    } else if (temp_v0 < -1) {
        g_unkGraphicsStruct.unkC--;
    } else {
        g_unkGraphicsStruct.unkC = arg0;
    }
}

INCLUDE_ASM("st/dre/nonmatchings/14774", EntityUnkId21);

// appears to load from the CD and freeze the game
INCLUDE_ASM("st/dre/nonmatchings/14774", EntityUnkId23);
