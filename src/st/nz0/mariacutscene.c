#include "nz0.h"

// This file consists of EntityMariaCutscene, and all the functions it calls.
// No function in NZ0 calls anything in there, nor does anything in here call
// any NZ0 functions, besides the ones in this file.

void func_801B74CC(void) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
}

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
    prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
    prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
    prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
    prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
    prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
REDACTED
    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;
REDACTED
REDACTED
REDACTED
    prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED

REDACTED
    RECT rect;

    rect.y = (arg0 * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

void func_801B7740(void) {
    Primitive* prim;

    func_801B76E4(g_Dialogue.nextCharY);
REDACTED
    prim->tpage = 0x10;
REDACTED
REDACTED
    prim->u0 = 0;
REDACTED
    prim->x0 = prim->x0 + 4;
REDACTED
    prim->u1 = 0xC0;
    prim->v1 = 0xC;
    prim->priority = 0x1FF;
    prim->drawMode = DRAW_DEFAULT;
}
REDACTED
// Creates primitives for the actor name at the head of the dialogue
void func_801B77F8(u16 actorIndex, Entity* self) {
REDACTED
REDACTED
    s32 x;
    u16 chCount;
    const char* actorName;
    char ch;

    actorName = D_8018146C[actorIndex];
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
REDACTED
    actorName = D_8018146C[actorIndex];
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
REDACTED
            prim = prim->next;
            x += FONT_GAP;
        }
    }
}
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
void func_801B79A8(void) {
    Entity* entity;
    u16 startTimer;
    u8 entityIndex;

REDACTED
    // protect from overflows
REDACTED
REDACTED
        return;
    }

    while (true) {
        // Start the dialogue script only if the start timer has passed
REDACTED
REDACTED
            // Re-evaluate the condition at the next frame
REDACTED
            return;
        }

REDACTED
        case 0:
REDACTED
            entity = &g_Entities[STAGE_ENTITY_START + entityIndex];
            DestroyEntity(entity);

REDACTED
            entity->pfnUpdate = PfnEntityUpdates[entity->entityId - 1];
REDACTED
REDACTED
REDACTED
REDACTED
            break;
        case 1:
REDACTED
            entity = &g_Entities[STAGE_ENTITY_START + entityIndex];
            DestroyEntity(entity);
            break;
        case 2:
            if (!((g_mariaCutsceneFlags >> *g_Dialogue.unk40) & 1)) {
                g_Dialogue.unk40--;
                return;
            }
            g_mariaCutsceneFlags &= ~(1 << *g_Dialogue.unk40++);
            break;
        case 3:
            g_mariaCutsceneFlags |= 1 << *g_Dialogue.unk40++;
            break;
        }
    }
}
REDACTED
// Animates the portrait size of the actor by enlarging or shrinking it
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    while (primIndex >= 5) {
        primIndex -= 5;
    }
    if (g_CurrentEntity->step_s == 0) {
REDACTED
        prim->v1 -= ySteps;
        prim->v0 += ySteps;
        if (prim->v1 == 0) {
            g_CurrentEntity->step_s++;
            prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

// cutscene where alucard and maria discuss castle changing
void EntityMariaCutscene(Entity* self) {
    RECT rect;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s16 j;
    s16 uCoord;
    s16 vCoord;
    u16 nextChar;
    s32 nextChar2;
    s32 bit_shifty;

    if (self->step != 0) {
        if ((D_801CB73C != 0) && (D_801CB684 == 0) &&
            ((g_Settings.D_8003CB04 & 0x100) ||
             (g_IsTimeAttackUnlocked != 0)) &&
            (g_pads[0].tapped == PAD_START)) {
            D_801CB684 = 1;
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
        if ((self->step) && (g_Dialogue.unk3C != 0)) {
            func_801B79A8();
        }
    }
    switch (self->step) {
    case 0:
        if ((g_CastleFlags[133] != 0) ||
            (g_PlayableCharacter != PLAYER_ALUCARD)) {
            DestroyEntity(self);
            return;
        }
        if (func_801B7520(D_80183B0C) & 0xFF) {
            self->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            g_mariaCutsceneFlags = 0;
            D_801CB73C = 0;
            D_801CB684 = 0;
            D_8003C704 = 1;
            self->primIndex = g_Dialogue.primIndex[2];
            self->step++;
        }
        break;
    case 1:
        // this is a huge While-loop! Don't miss it!
        while (1) {
            if ((g_Dialogue.nextCharTimer != 0) && (D_801CB684 == 0)) {
                g_Dialogue.nextCharTimer--;
                return;
            }
            nextChar = *g_Dialogue.nextCharDialogue++;
            switch (nextChar) {
            case 0:
                self->step = 7;
                return;
            case 1:
                if (D_801CB684 != 0) {
                    continue;
                }
                g_Dialogue.nextCharX = g_Dialogue.nextLineX;
                if (!(g_Dialogue.unk12 & 1)) {
                    g_Dialogue.nextLineY += 12;
                }
                g_Dialogue.nextCharY++;
                if (g_Dialogue.nextCharY >= 5) {
                    g_Dialogue.nextCharY = 0;
                }
                func_801B7740();
                if (!(g_Dialogue.unk12 & 1)) {
                    if (g_Dialogue.nextCharY >= 4) {
                        g_Dialogue.unk12 |= 1;
                        g_Dialogue.portraitAnimTimer = 0;
                        self->step_s = 0;
                        self->step++;
                        return;
                    }
                    continue;
                }
                g_Dialogue.portraitAnimTimer = 0;
                self->step_s = 0;
                self->step++;
                return;
            case 2:
                g_Dialogue.unk17 = *g_Dialogue.nextCharDialogue++;
                continue;
            case 3:
                g_Dialogue.nextCharTimer = *g_Dialogue.nextCharDialogue++;
                if (D_801CB684 != 0) {
                    continue;
                }
                return;
            case 4:
                if (D_801CB684 != 0) {
                    continue;
                }
                prim = g_Dialogue.prim[0];
                for (i = 0; i < 5; i++) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
                return;
            case 5:
                if (D_801CB684 != 0) {
                    g_Dialogue.nextCharDialogue += 2;
                    continue;
                }
                // fake reuse of i?
                i = *g_Dialogue.nextCharDialogue++;
                nextChar2 = *g_Dialogue.nextCharDialogue++;
                prim = g_Dialogue.prim[5];
                uCoord = D_801813C8[nextChar2 & 1];
                vCoord = D_801813CC[nextChar2 & 1];
                prim->clut = D_801813D0[i];
                prim->tpage = 0x90;
                if (nextChar2 & 0x80) {
                    prim->u0 = prim->u2 = uCoord + 0x2F;
                    prim->u1 = prim->u3 = uCoord;
                } else {
                    prim->u0 = prim->u2 = uCoord;
                    prim->u1 = prim->u3 = uCoord + 0x2F;
                }
                prim->v0 = prim->v1 = vCoord;
                prim->v2 = prim->v3 = vCoord + 0x48;
                prim->x0 = prim->x1 = prim->x2 = prim->x3 =
                    g_Dialogue.startX - 0x1E;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                    g_Dialogue.startY + 0x24;
                g_Dialogue.clutIndex = D_801813D8[i];
                func_801B74CC();
                func_801B7740();
                prim->priority = 0x1FE;
                prim->drawMode = 0;
                func_801B77F8(i, self);
                g_Dialogue.portraitAnimTimer = 6;
                self->step = 3;
                return;
            case 6:
                if (D_801CB684 != 0) {
                    continue;
                }
                for (prim = g_Dialogue.prim[0], i = 0; i < 5; i++) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
                g_api.FreePrimitives(g_Dialogue.primIndex[1]);
                g_Dialogue.primIndex[1] = -1;
                g_Dialogue.portraitAnimTimer = 6;
                self->step = 4;
                return;
            case 7:
                if (D_801CB684 != 0) {
                    g_Dialogue.nextCharDialogue++;
                    g_Dialogue.nextCharDialogue++;
                    continue;
                }
                g_Dialogue.startX = *g_Dialogue.nextCharDialogue++;
                g_Dialogue.startY = *g_Dialogue.nextCharDialogue++;
                prim = g_Dialogue.prim[5];
                prim = prim->next;
                prim->y0 = prim->y1 = g_Dialogue.startY;
                prim->y2 = prim->y3 = g_Dialogue.startY + 0x48;
                prim = prim->next;
                prim->y0 = g_Dialogue.startY - 1;
                prim->u0 = 0xF6;
                g_Dialogue.portraitAnimTimer = 0x18;
                self->step = 5;
                self->step_s = 0;
                return;

            case 8:
                if (D_801CB684 != 0) {
                    continue;
                }
                g_Dialogue.portraitAnimTimer = 0x18;
                self->step = 6;
                return;
            case 9:
                if (D_801CB684 != 0) {
                    g_Dialogue.nextCharDialogue++;
                    g_Dialogue.nextCharDialogue++;
                    continue;
                }
                nextChar = *g_Dialogue.nextCharDialogue++;
                nextChar <<= 4;
                nextChar |= *g_Dialogue.nextCharDialogue++;
                g_api.PlaySfx(nextChar);
                continue;
            case 10:
                if (D_801CB684 != 0) {
                    continue;
                }
                if (g_api.func_80131F68() != false) {
                    continue;
                }
                *g_Dialogue.nextCharDialogue--;
                return;
            case 11:
                if (D_801CB684 != 0) {
                    continue;
                }
                if (g_api.func_80131F68() != true) {
                    continue;
                }
                *g_Dialogue.nextCharDialogue--;
                return;
            case 12:
                bit_shifty = (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                func_801B797C((u8*)bit_shifty);
                continue;
            case 13:
                continue;
            case 14:
                bit_shifty = (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty += (u16)0x100000;
                g_Dialogue.nextCharDialogue += *(u16*)bit_shifty << 2;

                bit_shifty = (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue;
                g_Dialogue.nextCharDialogue = (u8*)bit_shifty + 0x100000;
                continue;

            case 15:
                bit_shifty = (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue;
                g_Dialogue.nextCharDialogue = (u8*)bit_shifty + 0x100000;
                continue;

            case 16:
                if (!((g_mariaCutsceneFlags >> *g_Dialogue.nextCharDialogue) &
                      1)) {
                    g_Dialogue.nextCharDialogue--;
                    return;
                }
                g_mariaCutsceneFlags &= ~(1 << *g_Dialogue.nextCharDialogue);
                *g_Dialogue.nextCharDialogue++;
                continue;
            case 17:
                g_mariaCutsceneFlags |= 1 << *g_Dialogue.nextCharDialogue++;
                continue;
            case 18:
                g_Dialogue.unk3C = 0;
                continue;
            case 19:
                if (D_801CB684 != 0) {
                    g_Dialogue.nextCharDialogue += 5;
                } else {
                    bit_shifty = (s32)*g_Dialogue.nextCharDialogue++;
                    bit_shifty <<= 4;
                    bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                    bit_shifty <<= 4;
                    bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                    bit_shifty <<= 4;
                    bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                    bit_shifty += 0x100000;
                    nextChar2 = g_Dialogue.nextCharDialogue++[0];
                    LoadTPage((u32*)bit_shifty, 1, 0, D_801813D4[nextChar2],
                              0x100, 0x30, 0x48);
                }
                continue;
            case 20:
                nextChar = *g_Dialogue.nextCharDialogue++;
                nextChar <<= 4;
                nextChar |= *g_Dialogue.nextCharDialogue++;
                g_api.PlaySfx(nextChar);
                continue;
            case 21:
                g_mariaCutsceneFlags = 0;
                D_801CB684 = 0;
                D_801CB73C = 0;
                continue;
            case 22:
                g_mariaCutsceneFlags &= ~(1 << *g_Dialogue.nextCharDialogue++);
                continue;
            case 23:
                return;
            case 24:
                if (!((g_mariaCutsceneFlags >> *g_Dialogue.nextCharDialogue) &
                      1)) {
                    *g_Dialogue.nextCharDialogue--;
                    return;
                }
                *g_Dialogue.nextCharDialogue++;
                continue;
            default:
                if (D_801CB684 != 0) {
                    continue;
                }
                g_Dialogue.nextCharTimer = g_Dialogue.unk17;
            }
            break; // This breaks the big while-loop!
        }
        if (nextChar == 0x20) {
            g_Dialogue.nextCharX += 2;
            return;
        }
        rect.x = ((nextChar & 0xF) * 2) + 0x380;
        rect.y = ((u32)(nextChar & 0xF0) >> 1) + 0xF0;
        rect.w = 2;
        rect.h = 8;
        vCoord = (g_Dialogue.nextCharY * 0xC) + 0x180;
        MoveImage(&rect, g_Dialogue.nextCharX, vCoord);
        g_Dialogue.nextCharX += 2;
        break;
    case 2:
        func_801B7C54(2U);
        if (g_Dialogue.portraitAnimTimer >= 6) {
            self->step -= 1;
            return;
        }
        break;
    case 3:
        prim = g_Dialogue.prim[5];
        prim->x0 = prim->x2 -= 4;
        prim->x1 = prim->x3 += 4;
        prim->y0 = prim->y1 -= 6;
        prim->y2 = prim->y3 += 6;
        g_Dialogue.portraitAnimTimer--;
        if (!g_Dialogue.portraitAnimTimer) {
            self->step = 1;
            for (prim = &g_PrimBuf[g_Dialogue.primIndex[1]]; prim != NULL;
                 prim = prim->next) {
                prim->drawMode = 0;
            }
        }
        break;
    case 4:
        prim = g_Dialogue.prim[5];
        prim->x0 = prim->x2 += 4;
        prim->x1 = prim->x3 -= 4;
        prim->y0 = prim->y1 += 6;
        prim->y2 = prim->y3 -= 6;
        if (prim->x1 >= (g_Dialogue.startX - 2)) {
            prim->x1 = prim->x3 = g_Dialogue.startX - 3;
        }
        g_Dialogue.portraitAnimTimer--;
        if (!g_Dialogue.portraitAnimTimer) {
            self->step = 1;
            return;
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            D_801CB73C = 1;
            primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 0x48);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            g_Dialogue.primIndex[0] = primIndex;
            for (prim = &g_PrimBuf[primIndex], j = 0; prim != NULL;
                 prim = prim->next) {
                prim->r0 = prim->r1 = 0x7F;
                prim->b0 = prim->b1 = prim->g0 = prim->g1 = 0;
                prim->x0 = prim->x1 = 0xF7;
                prim->y0 = prim->y1 = g_Dialogue.startY + j;
                prim->priority = 0x1FE;
                prim->drawMode = 0;
                prim->x2 = D_801813DC[j];
                prim->x3 = 0xF70;

                j++;
            }
            self->step_s++;
            return;
        case 1:
            for (j = 0, prim = &g_PrimBuf[g_Dialogue.primIndex[0]];
                 prim != NULL; prim = prim->next) {
                prim->x3 -= prim->x2;
                prim->x2 += 2;
                prim->x0 = prim->x3 / 16;
                if (prim->x0 < 5) {
                    prim->x0 = 4;
                } else {
                    j = 1;
                }
            }
            if (j == 0) {
                g_api.FreePrimitives(g_Dialogue.primIndex[0]);
                g_Dialogue.primIndex[0] = -1;
                prim = g_Dialogue.prim[5];
                prim = prim->next;
                prim->blendMode = 0x11;
                prim = prim->next;
                prim->blendMode = 0x51;
                self->step_s++;
                return;
            }
            break;
        case 2:
            j = 0;
            prim = g_Dialogue.prim[5];
            prim = prim->next;
            if (prim->r0 < 0x10) {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
            } else {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 -= 0x10;
                j = 1;
            }
            if (prim->b0 >= 0x7F) {
                prim->b0 = prim->b1 = 0x7F;
            } else {
                prim->b0 = prim->b1 += 8;
                j = 1;
            }

            prim = prim->next;
            if (prim->r0 < 0x10) {
                prim->r0 = prim->g0 = prim->b0 = 0x10;
            } else {
                prim->r0 = prim->g0 = prim->b0 -= 0xF;
                j = 1;
            }
            if (j == 0) {
                self->step = 1;
            }
        }
        break;
    case 6:
        prim = g_Dialogue.prim[5];
        prim = prim->next;
        g_Dialogue.portraitAnimTimer--;
        if (g_Dialogue.portraitAnimTimer >= 0xC) {
            prim = prim->next;
            prim->u0 -= 20;
            if (g_Dialogue.portraitAnimTimer & 1) {
                prim->u0--;
                return;
            }
        } else {
            if (!g_Dialogue.portraitAnimTimer) {
                self->step = 1;
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->y2 = (prim->y3 -= 6);
            }
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            return;
        }
        break;

    case 7:
        DestroyEntity(self);
        g_CastleFlags[133] = 1;
        D_8003C704 = 0;
        g_Settings.D_8003CB04 |= 0x100;
        break;
    }
}
