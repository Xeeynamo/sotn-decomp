// SPDX-License-Identifier: AGPL-3.0-or-later
//
// Options:
//
//     #define CUTSCENE_TILEMAP_SCROLL:
//
//         adds additional decrements based on `g_Tilemap`'s scroll position

extern Dialogue OVL_EXPORT(Dialogue);
extern u32 OVL_EXPORT(CutsceneFlags);
extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[];

static void CutsceneRun(void) {
    Entity* entity;
    u16 startTimer;

    OVL_EXPORT(Dialogue).timer++;
    // protect from overflows
    if (OVL_EXPORT(Dialogue).timer >= 0xFFFF) {
        OVL_EXPORT(Dialogue).unk3C = 0;
        return;
    }
    while (true) {
        // Start the dialogue script only if the start timer has passed
        startTimer = *OVL_EXPORT(Dialogue).scriptEnd++ << 8;
        startTimer |= *OVL_EXPORT(Dialogue).scriptEnd++;
        if (OVL_EXPORT(Dialogue).timer < startTimer) {
            // Re-evaluate the condition at the next frame
            OVL_EXPORT(Dialogue).scriptEnd -= 2;
            return;
        }
        switch (*OVL_EXPORT(Dialogue).scriptEnd++) {
        case 0:
            entity = &g_Entities[*OVL_EXPORT(Dialogue).scriptEnd++ & 0xFF] +
                     STAGE_ENTITY_START;
            DestroyEntity(entity);
            entity->entityId = *OVL_EXPORT(Dialogue).scriptEnd++;
            entity->pfnUpdate = OVL_EXPORT(EntityUpdates)[entity->entityId - 1];
            entity->posX.i.hi = *OVL_EXPORT(Dialogue).scriptEnd++ * 0x10;
            entity->posX.i.hi |= *OVL_EXPORT(Dialogue).scriptEnd++;
            entity->posY.i.hi = *OVL_EXPORT(Dialogue).scriptEnd++ * 0x10;
            entity->posY.i.hi |= *OVL_EXPORT(Dialogue).scriptEnd++;
#ifdef CUTSCENE_TILEMAP_SCROLL
            entity->posX.i.hi -= g_Tilemap.scrollX.i.hi;
            entity->posY.i.hi -= g_Tilemap.scrollY.i.hi;
#endif
            break;
        case 1:
            entity = &g_Entities[*OVL_EXPORT(Dialogue).scriptEnd++ & 0xFF] +
                     STAGE_ENTITY_START;
            DestroyEntity(entity);
            break;
        case 2:
            if (!((OVL_EXPORT(CutsceneFlags) >>
                   *OVL_EXPORT(Dialogue).scriptEnd) &
                  1)) {
#ifdef STAGE_IS_DRE
                OVL_EXPORT(Dialogue).timer--;
                OVL_EXPORT(Dialogue).scriptEnd -= 3;
#else
                OVL_EXPORT(Dialogue).scriptEnd--;
#endif
                return;
            }
            OVL_EXPORT(CutsceneFlags) &=
                ~(1 << *OVL_EXPORT(Dialogue).scriptEnd++);
            break;
        case 3:
            OVL_EXPORT(CutsceneFlags) |= 1 << *OVL_EXPORT(Dialogue).scriptEnd++;
            break;
        }
    }
}
