#include "nz0.h"

void func_801B6DE4(Entity* self) {
    s32 temp_s1 = self->hitFlags;
    s16 primIndex;
    POLY_GT4* poly;
    s32 y;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGeneric);
        self->ext.generic.unk80.modeS32 =
            self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        self->hitboxHeight = 8;
        self->hitboxOffY = -22;
        self->hitboxWidth = 6;
        self->hitboxState = 1;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        poly = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = poly;

        self->flags |= FLAG_HAS_PRIMS;
        poly->tpage = 0xF;
        poly->clut = 9;
        poly->u0 = 72;
        poly->v0 = 200;
        poly->u1 = 16;
        poly->v1 = 16;
        poly->pad2 = 0x5F;
        poly->code = 6;
        poly->pad3 = 2;

    case 1:
        if (temp_s1 != 0) {
            self->posY.val += FIX(1.0);
            y = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if ((self->ext.generic.unk80.modeS32 + 4) < y) {
                self->posY.i.hi = (u16)(self->ext.generic.unk80.modeS16.unk0 -
                                        (g_Tilemap.scrollY.i.hi - 4));
                self->step++;
                func_801C29B0(NA_SE_EV_SWITCH_CLICK);
                g_ElevatorTarget = self->params;
            }
        }
        break;

    case 2:
        if (temp_s1 == 0) {
            self->posY.val += 0xFFFF0000;
            y = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (y < self->ext.generic.unk80.modeS32) {
                self->posY.i.hi = (u16)(self->ext.generic.unk80.modeS16.unk0) -
                                  g_Tilemap.scrollY.i.hi;
                self->step = 1;
            }
        }
        break;
    }

    poly = (POLY_GT4*)(*((s32*)(&self->ext.generic.unk7C)));
    poly->x0 = self->posX.i.hi - 8;
    poly->y0 = self->posY.i.hi;
    poly->y0 = poly->y0 - 8;
}

typedef enum ElevatorSubSteps {
    /* 0 */ ELEVATOR_INIT,
    /* 1 */ ELEVATOR_IDLE,
    /* 2 */ ELEVATOR_ASCEND,
    /* 3 */ ELEVATOR_DESCEND,
} ElevatorSubSteps;

void EntityElevator(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 player;
    s32 x, y;
    s32 temp;

    FntPrint("elevator:%x\n", g_ElevatorTarget);

    if (g_Player.unk0C & 3) {
        temp = 0;
    } else {
        temp = func_801BD9A0(self, 16, 5, 4);
    }

    //! FAKE:
    player = PLAYER_CHARACTER;

    switch (self->step) {
    case ELEVATOR_INIT:
        InitializeEntity(g_EInitGeneric);
        self->hitboxOffX = 0;
        self->hitboxOffY = 68;
        self->hitboxWidth = 16;
        self->hitboxHeight = 5;
        self->hitboxState = 1;

        if (g_ElevatorTarget != 0) {
            y = g_ElevatorTargetPos[g_ElevatorTarget];
            self->posY.i.hi = y - g_Tilemap.scrollY.i.hi;
        } else {
            g_ElevatorTarget = self->params;
        }

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 32);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.elevator.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->type = PRIM_SPRT;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 8;
        prim->v0 = 0x80;
        prim->u1 = 0x20;
        prim->v1 = 0x48;
        prim->priority = 0x72;
        prim->drawMode = 2;
        prim = prim->next;
        while (prim != NULL) {
            prim->type = PRIM_SPRT;
            prim->tpage = 0xF;
            prim->clut = 9;
            prim->u0 = 0;
            prim->v0 = 0x80;
            prim->u1 = 8;
            prim->v1 = 0x40;
            prim->priority = 0x5F;
            prim->drawMode = 2;
            prim = prim->next;
        }
        self->ext.elevator.elevatorTarget = g_ElevatorTarget;

    case ELEVATOR_IDLE:
        if (temp != 0) {
            if (g_pads[0].pressed & PAD_UP) {
                if (--g_ElevatorTarget < 1) {
                    g_ElevatorTarget = 1;
                }
            }
            if (g_pads[0].pressed & PAD_DOWN) {
                if (++g_ElevatorTarget > 3) {
                    g_ElevatorTarget = 3;
                }
            }
        }

        if (g_ElevatorTarget != self->ext.elevator.elevatorTarget) {
            y = g_ElevatorTargetPos[g_ElevatorTarget];
            y -= g_Tilemap.scrollY.i.hi;
            if (y >= self->posY.i.hi) {
                self->step = ELEVATOR_DESCEND;
            } else {
                self->step = ELEVATOR_ASCEND;
            }
            func_801C29B0(0x6E6);
        }
        self->ext.elevator.elevatorTarget = g_ElevatorTarget;
        break;

    case ELEVATOR_ASCEND:
        self->posY.i.hi--;
        y = g_ElevatorTargetPos[self->ext.elevator.elevatorTarget] -
            g_Tilemap.scrollY.i.hi;
        if (self->posY.i.hi >= y) {
            if (temp != 0) {
                g_api.func_8010DFF0(0, 1);
                g_Entities[player].posY.i.hi--;
                D_80097488.y.i.hi--;
            }
        } else {
            self->posY.i.hi = y;
            self->step = ELEVATOR_IDLE;
        }
        break;

    case ELEVATOR_DESCEND:
        self->posY.i.hi++;
        y = g_ElevatorTargetPos[self->ext.elevator.elevatorTarget] -
            g_Tilemap.scrollY.i.hi;
        if (y < self->posY.i.hi) {
            self->posY.i.hi = y;
            self->step = ELEVATOR_IDLE;
            break;
        }
        if (temp != 0) {
            g_api.func_8010DFF0(0, 1);
            g_Entities[player].posY.i.hi++;
            D_80097488.y.i.hi++;
        }
        break;
    }
    prim = self->ext.prim;
    prim->x0 = self->posX.i.hi - 16;
    prim->y0 = self->posY.i.hi;

    prim = prim->next;
    x = self->posX.i.hi;
    y = self->posY.i.hi - 56;
    x -= 3;
    while (prim != NULL) {
        prim->x0 = x;
        prim->y0 = y;
        prim = prim->next;
        y -= 0x40;
    }
}

void func_801B74CC(void) {
    D_801CB694 = 2;
    D_801CB692 = 2;
    D_801CB696 = 0;
    D_801CB69A = 0;
    D_801CB69E = 0;
    D_801CB69F = 8;
    D_801CB68E = D_801CB690 + 0x14;
}

// called from EntityMariaCutscene
s32 func_801B7520(s32 textDialogue) {
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
    func_801B74CC();

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

void func_801B76E4(s16 arg0) {
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
void func_801B77F8(u16 actorIndex, Entity* self) {
    Primitive* prim;
    s16 primIndex;
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
    g_Dialogue.primIndex[1] = primIndex;
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
            prim->y0 = g_Dialogue.startY + 6;
            prim = prim->next;
            x += FONT_GAP;
        }
    }
}

void func_801B797C(s32 arg0) {
    g_Dialogue.unk40 = arg0 + 0x100000;
    g_Dialogue.timer = 0;
    g_Dialogue.unk3C = 1;
}

void func_801B79A8(void) {
    Entity* entity;
    u16 startTimer;
    u8 entityIndex;

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
            if (!((D_801CB734 >> *g_Dialogue.unk40) & 1)) {
                g_Dialogue.unk40--;
                return;
            }
            D_801CB734 &= ~(1 << *g_Dialogue.unk40++);
            break;
        case 3:
            D_801CB734 |= 1 << *g_Dialogue.unk40++;
            break;
        }
    }
}

// Animates the portrait size of the actor by enlarging or shrinking it
void func_801B7C54(u8 ySteps) {
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

// cutscene where alucard and maria discuss castle changing
INCLUDE_ASM("st/nz0/nonmatchings/36DE4", EntityMariaCutscene);

void func_801B8E0C(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BEC);
        D_8003C8B8 = 0;
        g_unkGraphicsStruct.unk0 = 1;
        g_Player.padSim = PAD_LEFT;
        if (g_Player.unk0C & PLAYER_STATUS_WOLF_FORM) {
            g_Player.padSim = PAD_R2;
        }
        g_Player.D_80072EFC = 1;
        break;

    case 1:
        if (PLAYER.posX.i.hi < 176) {
            g_Player.padSim = 0;
            self->step++;
        } else {
            g_Player.padSim = 0;
            if (g_Player.unk0C & PLAYER_STATUS_WOLF_FORM) {
                if (g_Timer & 1) {
                    g_Player.padSim = PAD_R2;
                }
            } else {
                g_Player.padSim = PAD_LEFT;
            }
        }
        g_Player.D_80072EFC = 1;
        break;

    case 2:
        if (D_801CB734 & 0x2000) {
            D_8003C8B8 = 1;
            if (g_unkGraphicsStruct.unk0 != 0) {
                g_unkGraphicsStruct.unk0 = 0;
            }
            DestroyEntity(self);
        }
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        break;
    }
}

INCLUDE_ASM("st/nz0/nonmatchings/36DE4", func_801B8F94);
