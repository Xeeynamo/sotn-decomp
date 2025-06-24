// SPDX-License-Identifier: AGPL-3.0-or-later

void SetCutsceneEnd(u8* ptr) {
#if !defined(VERSION_PSP)
    g_Dialogue.scriptEnd = ptr + 0x100000;
#else
    g_Dialogue.scriptEnd = ptr;
#endif
    g_Dialogue.timer = 0;
    g_Dialogue.unk3C = 1;
}

void CutsceneRun(void) {
    Entity* entity;
    u16 startTimer;

    g_Dialogue.timer++;
    // protect from overflows
    if (g_Dialogue.timer >= 0xFFFF) {
        g_Dialogue.unk3C = 0;
        return;
    }
    while (true) {
        // Start the dialogue script only if the start timer has passed
        startTimer = *g_Dialogue.scriptEnd++ << 8;
        startTimer |= *g_Dialogue.scriptEnd++;
        if (g_Dialogue.timer < startTimer) {
            // Re-evaluate the condition at the next frame
            g_Dialogue.scriptEnd -= 2;
            return;
        }
        switch (*g_Dialogue.scriptEnd++) {
        case 0:
            entity = &g_Entities[*g_Dialogue.scriptEnd++ & 0xFF] +
                     STAGE_ENTITY_START;
            DestroyEntity(entity);
            entity->entityId = *g_Dialogue.scriptEnd++;
            entity->pfnUpdate = OVL_EXPORT(EntityUpdates)[entity->entityId - 1];
            entity->posX.i.hi = *g_Dialogue.scriptEnd++ * 0x10;
            entity->posX.i.hi |= *g_Dialogue.scriptEnd++;
            entity->posY.i.hi = *g_Dialogue.scriptEnd++ * 0x10;
            entity->posY.i.hi |= *g_Dialogue.scriptEnd++;
#ifdef STAGE_IS_DAI
            entity->posX.i.hi -= g_Tilemap.scrollX.i.hi;
            entity->posY.i.hi -= g_Tilemap.scrollY.i.hi;
#endif
            break;
        case 1:
            entity = &g_Entities[*g_Dialogue.scriptEnd++ & 0xFF] +
                     STAGE_ENTITY_START;
            DestroyEntity(entity);
            break;
        case 2:
            if (!((g_CutsceneFlags >> *g_Dialogue.scriptEnd) & 1)) {
                g_Dialogue.scriptEnd--;
                return;
            }
            g_CutsceneFlags &= ~(1 << *g_Dialogue.scriptEnd++);
            break;
        case 3:
            g_CutsceneFlags |= 1 << *g_Dialogue.scriptEnd++;
            break;
        }
    }
}

#ifndef STAGE_IS_DAI
void CutsceneSkip(Entity* self) {
    if (g_pads[0].tapped == PAD_START) {
        g_SkipCutscene = true;
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
#endif

// Animates the portrait size of the actor by enlarging or shrinking it
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
