// SPDX-License-Identifier: AGPL-3.0-or-later
extern ServantEvent g_Events[];
extern ServantEvent* g_EventQueue;
extern u32 g_CurrentServant;
extern s32 g_CurrentRoomX;
extern s32 g_CurrentRoomY;

// Trigger an event under certain specific set of conditions
void ProcessEvent(Entity* self, bool resetEvent) {
    ServantEvent* evt;
    ServantEvent* queue;
    s32 cameraX;
    s32 cameraY;
    s32 i;

    if (resetEvent) {
        g_CurrentRoomY = 0;
        g_CurrentRoomX = 0;
        g_CurrentServant = 0;
        return;
    }

    cameraX = g_Tilemap.scrollX.i.hi;
    cameraY = g_Tilemap.scrollY.i.hi;
    // Ensures the following block is only evaluated once per room
    if (g_CurrentServant != g_Servant || g_CurrentRoomX != g_Tilemap.left ||
        g_CurrentRoomY != g_Tilemap.top) {
        g_CurrentServant = g_Servant;
        g_CurrentRoomX = g_Tilemap.left;
        g_CurrentRoomY = g_Tilemap.top;
        queue = g_EventQueue;
        for (i = 1; g_Events[i].roomX != -1; i++) {
            evt = &g_Events[i];
            // Filter by familiar
            if (evt->servantId != -1 && evt->servantId != g_CurrentServant) {
                continue;
            }

#if defined(VERSION_US)
            if (evt->roomX < 0) {
                if (!(g_StageId & STAGE_INVERTEDCASTLE_FLAG)) {
                    continue;
                }
                goto block_13;
            }
            if (!(g_StageId & STAGE_INVERTEDCASTLE_FLAG)) {
            block_13:
#elif defined(VERSION_HD) || defined(VERSION_PSP)
            if (evt->roomX >= 0 ||
                (g_StageId >= STAGE_RNO0 && g_StageId < STAGE_RNZ1_DEMO)) {
#endif
                if (abs(evt->roomX) != g_CurrentRoomX ||
                    evt->roomY != g_CurrentRoomY) {
                    continue;
                }

                if (evt->cameraX == cameraX && evt->cameraY == cameraY &&
                    (evt->condition == -1 ||
                     (!(evt->condition & 0x80000000) ||
                      !g_CastleFlags[evt->condition & 0xFFFF]) &&
                         (!(evt->condition & CHECK_RELIC_FLAG) ||
                          !(g_Status.relics[evt->condition & 0xFFFF] &
                            RELIC_FLAG_FOUND)))) {
                    evt->timer = 0;
                    if (evt->delay == 0) {
                        CreateEventEntity(self, evt->entityId, evt->params);
                        if (evt->unk2C) {
                            continue;
                        }
                    }
                }
                if (evt->delay > 0) {
                    evt->timer = evt->delay - 1;
                }
                queue->next = evt;
                queue = evt;
            }
        }
        queue->next = NULL;
    } else {
        queue = g_EventQueue;
        while (queue->next != NULL) {
            if (!evt->delay) {
            }
            if (queue->next->cameraX == cameraX &&
                queue->next->cameraY == cameraY &&
                (queue->next->condition == -1 ||
                 (!(queue->next->condition & 0x80000000) ||
                  !g_CastleFlags[queue->next->condition & 0xFFFF]) &&
                     (!(queue->next->condition & CHECK_RELIC_FLAG) ||
                      !(g_Status.relics[queue->next->condition & 0xFFFF] &
                        1)))) {
                if (queue->next->timer > 0) {
                    queue->next->timer--;
                } else {
                    CreateEventEntity(
                        self, queue->next->entityId, queue->next->params);
                    if (queue->next->unk2C) {
                        queue->next = queue->next->next;
                        continue;
                    } else {
                        queue->next->timer = queue->next->delay;
                    }
                }
            }
            queue = queue->next;
        }
    }
}
