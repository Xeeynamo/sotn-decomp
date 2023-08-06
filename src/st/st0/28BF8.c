/*
 * Overlay: ST0
 * Description: Cutscene of Richter talking to Dracula
 */

#include "st0.h"

void func_801A8BF8(void) {
    Primitive* prim;

    func_801A8B9C(g_Dialogue.D_801C24DA);
    prim = g_Dialogue.D_801C24E4[g_Dialogue.D_801C24DA];
    prim->tpage = 0x10;
    prim->clut = g_Dialogue.D_801C24E0;
    prim->y0 = g_Dialogue.D_801C24D2;
    prim->u0 = 0;
    prim->x0 = g_Dialogue.D_801C24D0;
    prim->x0 = prim->x0 + 4;
    prim->v0 = g_Dialogue.D_801C24DA * 0xC - 0x80;
    prim->u1 = 0xC0;
    prim->v1 = 0xC;
    prim->priority = 0x1FF;
    prim->blendMode = 0;
}

// Creates primitives for the actor name at the head of the dialogue
void func_801A8CB0(u16 actorIndex, Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 x;
    u16 chCount;
    const char* actorName;
    char ch;

    actorName = D_80180828[actorIndex];
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
    g_Dialogue.D_801C24FC[1] = primIndex;
    actorName = D_80180828[actorIndex];
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
            prim->blendMode = BLEND_VISIBLE;
            prim->x0 = x;
            prim->y0 = g_Dialogue.D_801C24D4 + 6;
            prim = prim->next;
            x += FONT_GAP;
        }
    }
}

void func_801A8E34(s32 arg0) {
    g_Dialogue.D_801C250C = arg0 + 0x100000;
    g_Dialogue.D_801C250A = 0;
    g_Dialogue.D_801C2508 = 1;
}

void func_801A8E60(void) {
    Entity* entity;
    u16 startTimer;
    u8 entityIndex;

    g_Dialogue.D_801C250A++;
    // protect from overflows
    if (g_Dialogue.D_801C250A > 0xFFFE) {
        g_Dialogue.D_801C2508 = 0;
        return;
    }

    while (true) {
        // Start the dialogue script only if the start timer has passed
        startTimer = (*g_Dialogue.D_801C250C++ << 8) | *g_Dialogue.D_801C250C++;
        if (g_Dialogue.D_801C250A < startTimer) {
            // Re-evaluate the condition at the next frame
            g_Dialogue.D_801C250C -= 2;
            return;
        }

        switch (*g_Dialogue.D_801C250C++) {
        case 0:
            entityIndex = *g_Dialogue.D_801C250C++;
            entity = &g_Entities[STAGE_ENTITY_START + entityIndex];
            DestroyEntity(entity);

            entity->entityId = *g_Dialogue.D_801C250C++;
            entity->pfnUpdate = PfnEntityUpdates[entity->entityId - 1];
            entity->posX.i.hi = *g_Dialogue.D_801C250C++ * 0x10;
            entity->posX.i.hi = *g_Dialogue.D_801C250C++ | entity->posX.i.hi;
            entity->posY.i.hi = *g_Dialogue.D_801C250C++ * 0x10;
            entity->posY.i.hi = *g_Dialogue.D_801C250C++ | entity->posY.i.hi;
            break;
        case 1:
            entityIndex = *g_Dialogue.D_801C250C++;
            entity = &g_Entities[STAGE_ENTITY_START + entityIndex];
            DestroyEntity(entity);
            break;
        case 2:
            if (!((D_801C257C >> *g_Dialogue.D_801C250C) & 1)) {
                g_Dialogue.D_801C250C--;
                return;
            }
            D_801C257C &= ~(1 << *g_Dialogue.D_801C250C++);
            break;
        case 3:
            D_801C257C |= 1 << *g_Dialogue.D_801C250C++;
            break;
        }
    }
}

// Animates the portrait size of the actor by enlarging or shrinking it
void func_801A910C(u8 ySteps) {
    Primitive* prim;
    s32 primIndex;
    s32 i;

    primIndex = g_Dialogue.D_801C24DA + 1;
    while (primIndex >= 5) {
        primIndex -= 5;
    }
    if (g_CurrentEntity->step_s == 0) {
        prim = g_Dialogue.D_801C24E4[primIndex];
        prim->v1 -= ySteps;
        prim->v0 += ySteps;
        if (prim->v1 == 0) {
            g_CurrentEntity->step_s++;
            prim->blendMode = BLEND_VISIBLE;
        }
    }

    for (i = 0; i < 5; i++) {
        if (i != primIndex) {
            prim = g_Dialogue.D_801C24E4[i];
            prim->y0 -= ySteps;
        }
    }
    g_Dialogue.D_801C24DC++;
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/28BF8", EntityDialogue);

void func_801AA218(s16 arg0) {
    s16 temp_a1 = ((0xE0 - arg0) / 2) + 0x80;
    s16 temp_v1 = temp_a1 - *D_8009740C;

    if (temp_v1 >= 3) {
        *D_8009740C = *D_8009740C + 2;
    } else if (temp_v1 < -2) {
        *D_8009740C = *D_8009740C - 2;
    } else {
        *D_8009740C = temp_a1;
    }
}

void EntityCutscene(Entity* self) {
    Unkstruct8* roomLayout = &g_CurrentRoomTileLayout;
    Entity* player = &PLAYER;
    u16 posX;

    self->posX.i.hi = player->posX.i.hi;
    self->posY.i.hi = player->posY.i.hi - 1;

    if ((self->step != 14) && (D_801C24C8 != 0) && (D_801C2580 != 0) &&
        (self->step >= 5)) {
        self->step = 15;
        self->animSet = ANIMSET_DRA(0);
        self->animCurFrame = 0;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180598);
        self->unk5A = 0x46;
        self->palette = 0x120;
        break;

    case 1:
        if (self->step_s != 0) {
            if ((player->step < 3) || (player->step == 25)) {
                posX = player->posX.i.hi + roomLayout->unkA;
                if (posX > 0x8000) {
                    posX = 0;
                }
                if (posX > 0xA0) {
                    g_Player.D_80072EF4 = 0x8000;
                } else {
                    g_Player.D_80072EF4 = 0x2000;
                }
                g_Entities[1].ext.generic.unk7C.S8.unk0 = 1;
                g_Player.D_80072EFC = 0xFF;
                func_801AA218(posX);
                SetStep(2);
            }
        } else {
            if ((player->posX.i.hi + roomLayout->unkA) < 0xE1) {
                D_8003C8B8 = 0;
                self->step_s++;
            }
        }
        break;

    case 2:
        posX = player->posX.i.hi + roomLayout->unkA;
        if (posX > 0x8000) {
            posX = 0;
        }

        if ((g_Player.D_80072EF4 == 0x8000) && (posX <= 0xA0) ||
            (g_Player.D_80072EF4 == 0x2000) && (posX >= 0x9F)) {
            g_Player.D_80072EFC = 1;
            g_Player.D_80072EF4 = 0x8000;
            self->ext.generic.unk7C.s = 0x18;
            D_801C257C |= 1;
            self->step++;
        }
        func_801AA218(posX);
        break;

    case 3:
        posX = player->posX.i.hi + roomLayout->unkA;
        if (posX > 0x8000) {
            posX = 0;
        }
        func_801AA218(posX);
        g_Player.D_80072EFC = 1;
        g_Player.D_80072EF4 = 0;
        if (!--self->ext.generic.unk7C.u) {
            SetStep(4);
        }
        break;

    case 4:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_80180830, self) == 0) {
            self->step++;
            g_CurrentRoom.width = 0x100;
        }
        player->animCurFrame = self->animCurFrame;
        break;

    case 5:
        g_Player.D_80072EFC = 1;
        player->animCurFrame = self->animCurFrame;
        if (D_801C257C & 0x400) {
            player->animCurFrame = 0;
            self->animSet = ANIMSET_OVL(5);
            self->animCurFrame = 1;
            SetStep(6);
        }
        break;

    case 6:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_8018083C, self) == 0) {
            if (D_801C257C & 0x800) {
                SetStep(7);
            }
        }
        player->animCurFrame = 0;
        break;

    case 7:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_8018084C, self) == 0) {
            if (D_801C257C & 0x1000) {
                SetStep(8);
            }
        }
        player->animCurFrame = 0;
        break;

    case 8:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_8018085C, self) == 0) {
            if (D_801C257C & 0x2000) {
                SetStep(9);
            }
        }
        player->animCurFrame = 0;
        break;

    case 9:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_80180864, self) == 0) {
            if (D_801C257C & 0x4000) {
                SetStep(10);
            }
        }
        player->animCurFrame = 0;
        break;

    case 10:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_8018086C, self) == 0) {
            if (D_801C257C & 0x8000) {
                SetStep(11);
            }
        }
        player->animCurFrame = 0;
        break;

    case 11:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_8018087C, self) == 0) {
            if (D_801C257C & 0x10000) {
                SetStep(12);
            }
        }
        player->animCurFrame = 0;
        break;

    case 12:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_80180884, self) == 0) {
            if (D_801C257C & 0x20000) {
                SetStep(13);
            }
        }
        player->animCurFrame = 0;
        break;

    case 13:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_8018088C, self) == 0) {
            if (D_801C257C & 0x40000) {
                SetStep(14);
            }
        }
        player->animCurFrame = 0;
        break;

    case 14:
        g_Player.D_80072EFC = 1;
        player->animCurFrame = 0;
        if (AnimateEntity(D_80180894, self) == 0) {
            self->animCurFrame = 0;
            player->animCurFrame = 7;
            SetStep(15);
        }
        break;

    case 15:
        g_Player.D_80072EFC = 1;
        player->animCurFrame = 7;
        if (D_801C257C & 4) {
            g_Player.D_80072EF4 = 0x8000;
            DestroyEntity(self);
            D_8003C8B8 = 1;
        }
        break;
    }
}
