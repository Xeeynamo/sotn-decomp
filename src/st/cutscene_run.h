// SPDX-License-Identifier: AGPL-3.0-or-later
//
// Options:
//
//     #define CUTSCENE_TILEMAP_SCROLL:
//
//         adds additional decrements based on `g_Tilemap`'s scroll position

// st0 uses a union for g_Dialogue
#ifdef STAGE_IS_ST0
#define G_DIALOGUE g_Dialogue.std
#else
#define G_DIALOGUE g_Dialogue
#endif

extern u32 g_CutsceneFlags;
extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[];

static void CutsceneRun(void) {
    Entity* entity;
    u16 startTimer;

    G_DIALOGUE.timer++;
    // protect from overflows
    if (G_DIALOGUE.timer >= 0xFFFF) {
        G_DIALOGUE.unk3C = 0;
        return;
    }
    while (true) {
        // Start the dialogue script only if the start timer has passed
        startTimer = *G_DIALOGUE.scriptEnd++ << 8;
        startTimer |= *G_DIALOGUE.scriptEnd++;
        if (G_DIALOGUE.timer < startTimer) {
            // Re-evaluate the condition at the next frame
            G_DIALOGUE.scriptEnd -= 2;
            return;
        }
        switch (*G_DIALOGUE.scriptEnd++) {
        case 0:
            entity = &g_Entities[*G_DIALOGUE.scriptEnd++ & 0xFF] +
                     STAGE_ENTITY_START;
            DestroyEntity(entity);
            entity->entityId = *G_DIALOGUE.scriptEnd++;
            entity->pfnUpdate = OVL_EXPORT(EntityUpdates)[entity->entityId - 1];
            entity->posX.i.hi = *G_DIALOGUE.scriptEnd++ * 0x10;
            entity->posX.i.hi |= *G_DIALOGUE.scriptEnd++;
            entity->posY.i.hi = *G_DIALOGUE.scriptEnd++ * 0x10;
            entity->posY.i.hi |= *G_DIALOGUE.scriptEnd++;
#ifdef CUTSCENE_TILEMAP_SCROLL
            entity->posX.i.hi -= g_Tilemap.scrollX.i.hi;
            entity->posY.i.hi -= g_Tilemap.scrollY.i.hi;
#endif
            break;
        case 1:
            entity = &g_Entities[*G_DIALOGUE.scriptEnd++ & 0xFF] +
                     STAGE_ENTITY_START;
            DestroyEntity(entity);
            break;
        case 2:
            if (!((g_CutsceneFlags >> *G_DIALOGUE.scriptEnd) & 1)) {
#ifdef STAGE_IS_DRE
                G_DIALOGUE.scriptEnd -= 3;
                G_DIALOGUE.timer--;
#else
                G_DIALOGUE.scriptEnd--;
#endif
                return;
            }
            g_CutsceneFlags &= ~(1 << *G_DIALOGUE.scriptEnd++);
            break;
        case 3:
            g_CutsceneFlags |= 1 << *G_DIALOGUE.scriptEnd++;
            break;
        }
    }
}
