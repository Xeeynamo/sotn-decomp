#include "no3.h"

// intro owl and leaves
void EntityFlyingOwlAndLeaves(Entity* entity) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* newEntity;
    u16 animFlag = true;
    u16 i;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180B00);
        entity->animSet = ANIMSET_OVL(1);
        entity->animCurFrame = 56;
        if (entity->params != 0) {
            entity->drawFlags =
                FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_UNK8;
            entity->rotX = 0x180;
            entity->rotY = 0x180;
            entity->unk6C = 0x60;
            entity->posY.i.hi = -16;
            entity->zPriority = 0xC1;
        } else {
            entity->drawFlags = FLAG_DRAW_UNK8;
            entity->unk6C = 0x20;
            entity->zPriority = 0xBF;
        }
        entity->unk68 = 0x1C0;
        break;

    case 1:
        if (entity->posX.i.hi < 224) {
            entity->ext.generic.unk7C.s = 0;
            entity->step++;
        }
        break;

    case 2:
        if (!(entity->ext.generic.unk7C.s++ & 7)) {
            g_api.PlaySfx(SE_TREE_BRANCH);
        }
        if (entity->posX.i.hi < 192) {
            SetStep(3);
            if (entity->params != 0) {
                entity->velocityX = FIX(8);
                entity->velocityY = FIX(3);
                break;
            }
            entity->velocityX = FIX(10);
            entity->velocityY = FIX(1.625);
            for (i = 0; i < 8; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(0x60, newEntity);
                    newEntity->params = i;
                }
            }
        }
        break;

    case 3:
        if (entity->params != 0) {
            animFlag = AnimateEntity(D_801819DC, entity);
            entity->velocityY -= 0xA00;
        } else {
            animFlag = AnimateEntity(D_801819D0, entity);
            if (entity->velocityY > (s32)0xFFFE0000) {
                entity->velocityY -= FIX(0.03125);
            }
        }
        MoveEntity();
        if ((entity->params == 0) && (tilemap->cameraX.i.hi > 0xD80)) {
            entity->step++;
        }
        if (entity->posX.i.hi > 288) {
            DestroyEntity(entity);
        } else if (entity->posY.i.hi < -16) {
            DestroyEntity(entity);
        }
        break;

    case 4:
        if (entity->velocityY > (s32)0xFFFE0000) {
            entity->velocityY -= FIX(0.03125);
        }
        animFlag = AnimateEntity(D_801819D0, entity);
        MoveEntity();
        if (entity->unk6C < 0x78) {
            entity->unk6C += 2;
        }
        if (entity->posX.i.hi > 288) {
            DestroyEntity(entity);
        } else if (entity->posY.i.hi < -16) {
            DestroyEntity(entity);
        }
    }

    if (!animFlag) {
        func_801CAD28(SE_OWL_WING_FLAP);
    }
}

// a single leaf from when the owl comes out in the intro
void EntityFallingLeaf(Entity* entity) {
    volatile int pad;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180B00);
        entity->animSet = ANIMSET_OVL(1);
        entity->animCurFrame = (entity->params & 1) + 63;
        entity->zPriority = 0xC1;
        entity->velocityX = D_801819E8[entity->params * 2];
        entity->velocityY = D_801819EC[entity->params * 2];
        entity->unk68 = 0x1C0;
        break;

    case 1:
        if (entity->velocityX > 0) {
            entity->velocityX -= FIX(0.0625);
        }
        if (entity->velocityY < FIX(1.0)) {
            entity->velocityY += 0x400;
        }
        if (entity->velocityY > FIX(1.0)) {
            entity->velocityY -= 0x400;
        }
        MoveEntity();
        break;
    }
}

void func_801BE544(void) {
    D_801D7D30 = 0x182;
    D_801D7D2E = 0x182;
    D_801D7D32 = 0;
    D_801D7D36 = 0;
    D_801D7D3A = 0;
    D_801D7D3B = 8;
    D_801D7D2A = D_801D7D2C + 0x14;
}

s32 func_801BE598(s32 textDialogue) {
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
    func_801BE544();

    //! FAKE:
    if (prim && prim) {
    }

    prim = g_Dialogue.prim[0] = &g_PrimBuf[g_Dialogue.primIndex[2]];

    prim->blendMode = BLEND_VISIBLE;
    prim = g_Dialogue.prim[1] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = g_Dialogue.prim[2] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = g_Dialogue.prim[3] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = g_Dialogue.prim[4] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = g_Dialogue.prim[5] = prim->next;

    prim->type = 4;
    prim->blendMode = BLEND_VISIBLE;

    prim = prim->next;
    prim->type = 3;
    prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0xFF;
    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;
    prim->x0 = prim->x2 = 4;
    prim->x1 = prim->x3 = 0xF8;
    prim->priority = 0x1FD;
    prim->blendMode = BLEND_VISIBLE;

    prim = prim->next;
    prim->type = 1;
    prim->x0 = 3;
    prim->y0 = 0x2F;
    prim->v0 = 0x4A;
    prim->r0 = prim->g0 = prim->b0 = 0xFF;
    prim->priority = 0x1FC;
    prim->blendMode = BLEND_VISIBLE;
    return 1;
}

void func_801BE75C(s16 yOffset) {
    RECT rect;

    rect.x = 384;
    rect.y = (yOffset * 12) + 256;
    rect.w = 64;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

void func_801BE7BC(void) {
    Primitive* prim;

    func_801BE75C(g_Dialogue.nextCharY);
    prim = g_Dialogue.prim[g_Dialogue.nextCharY];
    prim->tpage = 0x16;
    prim->clut = g_Dialogue.clutIndex;
    prim->y0 = g_Dialogue.nextLineY;
    prim->u0 = 0;
    prim->x0 = g_Dialogue.startX;
    prim->x0 = prim->x0 + 4;
    prim->v0 = g_Dialogue.nextCharY * 0xC;
    prim->u1 = 0xC0;
    prim->v1 = 0xC;
    prim->priority = 0x1FF;
    prim->blendMode = 0;
}

// Creates primitives for the actor name at the head of the dialogue
void func_801BE870(u16 actorIndex, Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 x;
    u16 chCount;
    const char* actorName;
    char ch;

    actorName = D_80181ACC[actorIndex];
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
    actorName = D_80181ACC[actorIndex];
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
            prim->y0 = g_Dialogue.startY + 6;
            prim = prim->next;
            x += FONT_GAP;
        }
    }
}

void func_801BE9F4(s32 arg0) {
    g_Dialogue.unk40 = arg0 + 0x100000;
    g_Dialogue.timer = 0;
    g_Dialogue.unk3C = 1;
}

void func_801BEA20(void) {
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
            if (!((D_801D7DD0 >> *g_Dialogue.unk40) & 1)) {
                g_Dialogue.unk40--;
                return;
            }
            D_801D7DD0 &= ~(1 << *g_Dialogue.unk40++);
            break;
        case 3:
            D_801D7DD0 |= 1 << *g_Dialogue.unk40++;
            break;
        }
    }
}

void func_801BECCC(Entity* self) {
    if (g_pads[0].tapped == PAD_START) {
        D_801D7D20 = 1;
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

INCLUDE_ASM("st/no3/nonmatchings/3E134", func_801BEDAC);
// seems to cause a room transition
INCLUDE_ASM("st/no3/nonmatchings/3E134", EntityRoomTransition1);
