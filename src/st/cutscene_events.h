// SPDX-License-Identifier: AGPL-3.0-or-later
//
// Options:
//
//     #define CUTSCENE_TILEMAP_SCROLL:
//
//         adds additional decrements based on `g_Tilemap`'s scroll position

extern Dialogue g_Dialogue;
extern u32 g_CutsceneFlags;
extern PfnEntityUpdate EntityUpdates[];

static void RunCutsceneEvents(void) {
    Entity* entity;
    u16 startTimer;

    g_Dialogue.timer++;
    // protect from overflows
    if (g_Dialogue.timer >= 0xFFFF) {
        g_Dialogue.hasEvents = 0;
        return;
    }
    while (true) {
        // Run the next event only once its start timer has elapsed
        startTimer = *g_Dialogue.eventCur++ << 8;
        startTimer |= *g_Dialogue.eventCur++;
        if (g_Dialogue.timer < startTimer) {
            // Re-evaluate the condition at the next frame
            g_Dialogue.eventCur -= 2;
            return;
        }
        switch (*g_Dialogue.eventCur++) {
        case CSEV_SPAWN:
            entity =
                &g_Entities[*g_Dialogue.eventCur++ & 0xFF] + STAGE_ENTITY_START;
            DestroyEntity(entity);
            entity->entityId = *g_Dialogue.eventCur++;
            entity->pfnUpdate = EntityUpdates[entity->entityId - 1];
            entity->posX.i.hi = *g_Dialogue.eventCur++ * 0x10;
            entity->posX.i.hi |= *g_Dialogue.eventCur++;
            entity->posY.i.hi = *g_Dialogue.eventCur++ * 0x10;
            entity->posY.i.hi |= *g_Dialogue.eventCur++;
#ifdef CUTSCENE_TILEMAP_SCROLL
            entity->posX.i.hi -= g_Tilemap.scrollX.i.hi;
            entity->posY.i.hi -= g_Tilemap.scrollY.i.hi;
#endif
            break;
        case CSEV_DESTROY:
            entity =
                &g_Entities[*g_Dialogue.eventCur++ & 0xFF] + STAGE_ENTITY_START;
            DestroyEntity(entity);
            break;
        case CSEV_WAIT_FOR_FLAG:
            if (!((g_CutsceneFlags >> *g_Dialogue.eventCur) & 1)) {
#ifdef STAGE_IS_DRE
                g_Dialogue.timer--;
                g_Dialogue.eventCur -= 3;
#else
                g_Dialogue.eventCur--;
#endif
                return;
            }
            g_CutsceneFlags &= ~(1 << *g_Dialogue.eventCur++);
            break;
        case CSEV_SET_FLAG:
            g_CutsceneFlags |= 1 << *g_Dialogue.eventCur++;
            break;
        }
    }
}
