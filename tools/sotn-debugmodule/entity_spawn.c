#include "debugmode.h"

typedef struct {
    int length;
    void** values;
} EntityDef;

#define ENTITY_DEF(first, last)                                                \
    { ((last) - (first)) / 4 + 1, first }
#define ENTITY_NONE                                                            \
    { 0, NULL }

EntityDef g_DraEntities[] = {
    ENTITY_DEF(0x800AD0C4, 0x800AD1D0),
};
EntityDef g_RicEntities[] = {
    ENTITY_DEF(0x8015495C, 0x80154A68),
};
EntityDef g_StageEntities[] = {
    ENTITY_NONE,                        // STAGE_NO0
    ENTITY_NONE,                        // STAGE_NO1
    ENTITY_NONE,                        // STAGE_LIB
    ENTITY_NONE,                        // STAGE_CAT
    ENTITY_NONE,                        // STAGE_NO2
    ENTITY_NONE,                        // STAGE_CHI
    ENTITY_NONE,                        // STAGE_DAI
    ENTITY_DEF(0x801808D0, 0x80180A38), // STAGE_NP3
    ENTITY_DEF(0x80180394, 0x80180400), // STAGE_CEN
    ENTITY_NONE,                        // STAGE_NO4
    ENTITY_NONE,                        // STAGE_ARE
    ENTITY_NONE,                        // STAGE_TOP
    ENTITY_DEF(0x80180A94, 0x80180BC4), // STAGE_NZ0
    ENTITY_NONE,                        // STAGE_NZ1
    ENTITY_DEF(0x801803E4, 0x80180440), // STAGE_WRP
    ENTITY_NONE,                        // STAGE_NO1_ALT
    ENTITY_NONE,                        // STAGE_NO0_ALT
    ENTITY_NONE,                        //
    ENTITY_DEF(0x801803C8, 0x80180454), // STAGE_DRE
    ENTITY_DEF(0x80180A94, 0x80180BC4), // STAGE_UNK_13
    ENTITY_NONE,                        // STAGE_UNK_14
    ENTITY_NONE,                        // STAGE_UNK_15
    ENTITY_NONE,                        // STAGE_BO7
    ENTITY_NONE,                        // STAGE_MAR
    ENTITY_NONE,                        // STAGE_BO6
    ENTITY_NONE,                        // STAGE_BO5
    ENTITY_NONE,                        // STAGE_BO4
    ENTITY_NONE,                        // STAGE_BO3
    ENTITY_NONE,                        // STAGE_BO2
    ENTITY_NONE,                        // STAGE_BO1
    ENTITY_NONE,                        // STAGE_BO0
    ENTITY_DEF(0x801804C0, 0x80180570), // STAGE_ST0
    ENTITY_NONE,                        // STAGE_RNO0
    ENTITY_NONE,                        // STAGE_RNO1
    ENTITY_NONE,                        // STAGE_RLIB
    ENTITY_NONE,                        // STAGE_RCAT
    ENTITY_NONE,                        // STAGE_RNO2
    ENTITY_NONE,                        // STAGE_RCHI
    ENTITY_NONE,                        // STAGE_RDAI
    ENTITY_NONE,                        // STAGE_RNO3
    ENTITY_NONE,                        // STAGE_RCEN
    ENTITY_NONE,                        // STAGE_RNO4
    ENTITY_NONE,                        // STAGE_RARE
    ENTITY_NONE,                        // STAGE_RTOP
    ENTITY_NONE,                        // STAGE_RNZ0
    ENTITY_NONE,                        // STAGE_RNZ1
    ENTITY_NONE,                        // STAGE_RWRP
    ENTITY_NONE,                        // STAGE_NO1
    ENTITY_NONE,                        // STAGE_NO1
    ENTITY_NONE,                        // STAGE_NO1
    ENTITY_NONE,                        // STAGE_NO1
    ENTITY_NONE,                        // STAGE_NO1
    ENTITY_NONE,                        // STAGE_NO1
    ENTITY_NONE,                        // STAGE_RNZ1
    ENTITY_NONE,                        // STAGE_RBO8
    ENTITY_NONE,                        // STAGE_RBO7
    ENTITY_NONE,                        // STAGE_RBO6
    ENTITY_NONE,                        // STAGE_RBO5
    ENTITY_NONE,                        // STAGE_RBO4
    ENTITY_NONE,                        // STAGE_RBO3
    ENTITY_NONE,                        // STAGE_RBO2
    ENTITY_NONE,                        // STAGE_RBO1
    ENTITY_NONE,                        // STAGE_RBO0
    ENTITY_NONE,                        // STAGE_NO1
    ENTITY_DEF(0x8018049C, 0x801804EC), // STAGE_MAD
    ENTITY_DEF(0x80180924, 0x80180AA8), // STAGE_NO3
    ENTITY_NONE,                        // STAGE_DAI
    ENTITY_NONE,                        // STAGE_LIB
    ENTITY_NONE,                        // STAGE_NO1
    ENTITY_NONE,                        // STAGE_SEL
    ENTITY_NONE,                        // STAGE_TE1
    ENTITY_NONE,                        // STAGE_TE2
    ENTITY_NONE,                        // STAGE_TE3
    ENTITY_NONE,                        // STAGE_TE4
    ENTITY_NONE,                        // STAGE_TE5
    ENTITY_NONE,                        // STAGE_TOP
    ENTITY_NONE,                        // STAGE_TE2
    ENTITY_NONE,                        // STAGE_TE2
    ENTITY_NONE,                        // STAGE_TE2
    ENTITY_NONE,                        // STAGE_TE2
};

void EntitySpawner(void* ptrs);
Entity* AllocEntity(Entity* start, Entity* end);
void DestroyEntity(Entity* item);

const int EntityPreview = 4;
int g_SpawnOption;
int g_Mode;
u8 g_SpawnEntityId;
u16 g_SpawnEntityParams;
u16 g_EntityStart;
u16 g_EntityEnd;
s16 g_SpawnX;
s16 g_SpawnY;
bool g_IsSpawnPreviewEnabled;
bool g_IsSpawnPlaceMode;
Entity* g_SpawnPlaceEntity;

const char* g_ModeNames[] = {
    "DRA",
    "STAGE",
    "RIC",
};

int GetEntityAllocationCount() {
    s32 allocated = 0;
    s32 i;

    for (i = g_EntityStart; i < g_EntityEnd; i++) {
        if (g_Entities[i].entityId) {
            allocated++;
        }
    }

    return allocated;
}

EntityDef* GetEntityDef(int mode) {
    switch (mode) {
    case 0:
        return g_DraEntities;
    case 1:
        if (g_StageId >= LEN(g_StageEntities)) {
            return NULL;
        }
        return &g_StageEntities[g_StageId];
    case 2:
        return g_RicEntities;
    default:
        return NULL;
    }
}

void* GetEntityUpdateFunc(int mode, u16 id) {
    EntityDef* entityDefs;

    entityDefs = GetEntityDef(mode);
    if (entityDefs == NULL || id >= entityDefs->length) {
        return NULL;
    }

    return entityDefs->values[id];
}

void SetEntityPreview(int mode, u16 id, u16 params) {
    Entity* e = &g_Entities[EntityPreview];
    void* pfnUpdate = GetEntityUpdateFunc(mode, id);
    DestroyEntity(e);

    if (pfnUpdate != NULL) {
        e->entityId = id;
        e->params = params;
        e->pfnUpdate = pfnUpdate;
        e->zPriority = 0x1F0;
        e->posX.i.hi = g_SpawnX;
        e->posY.i.hi = g_SpawnY;
        g_CurrentEntity = e;
        e->pfnUpdate(e); // runs three cycles to ensure we can preview
        e->pfnUpdate(e); // some graphics from the entity
        e->pfnUpdate(e);
    }
}

void DelEntityPreview() { DestroyEntity(&g_Entities[EntityPreview]); }

Entity* SpawnEntity(int mode, u16 id, u16 params) {
    Entity* e;
    void* pfnUpdate;

    e = AllocEntity(g_Entities + g_EntityStart, g_Entities + g_EntityEnd);
    if (e == NULL) {
        return;
    }

    pfnUpdate = GetEntityUpdateFunc(mode, id);
    DestroyEntity(e);

    if (pfnUpdate != NULL) {
        e->entityId = id;
        e->params = params;
        e->pfnUpdate = pfnUpdate;
        e->zPriority = PLAYER.zPriority + 0x20;
        e->posX.i.hi = g_SpawnX;
        e->posY.i.hi = g_SpawnY;
        e->pfnUpdate(e);
    }

    return e;
}

void UpdateEntityPlacement(int mode) {
    if (g_SpawnPlaceEntity == NULL) {
        // it should never be NULL. Exit before this crashes.
        g_IsSpawnPlaceMode = false;
        return;
    }

    DbgDrawMenuRect(4, 44, 96 + 10, 16);
    FntPrint("(%d, %d)\n", g_SpawnX, g_SpawnY);
    if (g_pads[0].pressed & PAD_LEFT) {
        g_SpawnX = g_SpawnPlaceEntity->posX.i.hi--;
    }
    if (g_pads[0].pressed & PAD_RIGHT) {
        g_SpawnX = g_SpawnPlaceEntity->posX.i.hi++;
    }
    if (g_pads[0].pressed & PAD_UP) {
        g_SpawnY = g_SpawnPlaceEntity->posY.i.hi--;
    }
    if (g_pads[0].pressed & PAD_DOWN) {
        g_SpawnY = g_SpawnPlaceEntity->posY.i.hi++;
    }
    if (g_pads[0].tapped & PAD_CIRCLE) {
        DestroyEntity(g_SpawnPlaceEntity);
        g_IsSpawnPlaceMode = false;
        g_SpawnPlaceEntity = NULL;
    }
    if (g_pads[0].tapped & PAD_SQUARE) {
        SpawnEntity(mode, g_SpawnEntityId, g_SpawnEntityParams);
    }
    if (g_pads[0].tapped & PAD_CROSS) {
        PauseDebugMode();
        g_IsSpawnPlaceMode = false;
        g_SpawnPlaceEntity = NULL;
    }
}

void InitEntitySpawn(void) {
    g_Mode = 1;
    g_SpawnOption = 0;
    g_SpawnEntityId = 1;
    g_SpawnEntityParams = 0;
    g_EntityStart = 0x40;
    g_EntityEnd = 0x80;
    g_SpawnX = 176;
    g_SpawnY = 122;
    g_IsSpawnPreviewEnabled = false;
    g_IsSpawnPlaceMode = false;
}

void UpdateEntitySpawn(void) {
    const int MenuWidth = 220;
    const int NOptions = 5;
    const int NItems = NOptions;

    int i;
    EntityDef* entityDefs;
    u16 prevId, prevParams;

    if (g_IsSpawnPlaceMode) {
        UpdateEntityPlacement(g_Mode);
        return;
    }

    entityDefs = GetEntityDef(g_Mode);
    if (entityDefs == NULL || entityDefs->length == 0) {
        DbgDrawMenuRect(4, 44, MenuWidth + 10, 8 + 1 * 8);
        FntPrint("no entities");
        return;
    }

    DbgDrawMenuRect(4, 44, MenuWidth + 10, 8 + NItems * 8);
    DbgDrawCursor(9, 48 + g_SpawnOption * 8, MenuWidth, 8);

    FntPrint("Mode: %s (Alloc %d/%d)\n", g_ModeNames[g_Mode],
             GetEntityAllocationCount(), g_EntityEnd - g_EntityStart);
    FntPrint("ID %02X/%02X (func %08X)\n", g_SpawnEntityId, entityDefs->length,
             GetEntityUpdateFunc(g_Mode, g_SpawnEntityId));
    FntPrint("Params %04X (Square=flag)\n", g_SpawnEntityParams);
    FntPrint("Entity preview: %s\n", g_IsSpawnPreviewEnabled ? "ON" : "OFF");
    FntPrint("Place entity (Square=spam)\n", g_SpawnEntityParams);

    if (g_pads[0].repeat & PAD_UP) {
        g_SpawnOption--;
        if (g_SpawnOption < 0) {
            g_SpawnOption = NOptions - 1;
        }
        PLAY_MENU_SOUND();
    }
    if (g_pads[0].repeat & PAD_DOWN) {
        g_SpawnOption++;
        if (g_SpawnOption >= NOptions) {
            g_SpawnOption = 0;
        }
        PLAY_MENU_SOUND();
    }

    prevId = g_SpawnEntityId;
    prevParams = g_SpawnEntityParams;
    switch (g_SpawnOption) {
    case 0:
        if (g_pads[0].repeat & PAD_LEFT || g_pads[0].repeat & PAD_RIGHT ||
            g_pads[0].repeat & PAD_CROSS) {
            g_Mode++;
            if (g_PlayableCharacter == PLAYER_ALUCARD) {
                if (g_Mode > 1) {
                    g_Mode = 0;
                }
            } else if (g_PlayableCharacter == PLAYER_RICHTER) {
                if (g_Mode > 2) {
                    g_Mode = 0;
                }
            }

            g_SpawnEntityId = 1;
            g_SpawnEntityParams = 0;
        }
        break;
    case 1: // ID option
        if (g_pads[0].repeat & PAD_LEFT) {
            g_SpawnEntityId--;
            if (g_SpawnEntityId < 1) {
                g_SpawnEntityId = 1;
            } else {
                g_SpawnEntityParams = 0;
            }
        }
        if (g_pads[0].repeat & PAD_RIGHT) {
            g_SpawnEntityId++;
            if (g_SpawnEntityId >= entityDefs->length) {
                g_SpawnEntityId = entityDefs->length - 1;
            } else {
                g_SpawnEntityParams = 0;
            }
        }
        if (g_pads[0].tapped & PAD_CROSS) {
            SpawnEntity(g_Mode, g_SpawnEntityId, g_SpawnEntityParams);
        }
        break;
    case 2: // Params option
        if (g_pads[0].repeat & PAD_LEFT) {
            g_SpawnEntityParams--;
        }
        if (g_pads[0].repeat & PAD_RIGHT) {
            g_SpawnEntityParams++;
        }
        if (g_pads[0].repeat & PAD_SQUARE) {
            g_SpawnEntityParams ^= 0x8000;
        }
        if (g_pads[0].tapped & PAD_CROSS) {
            SpawnEntity(g_Mode, g_SpawnEntityId, g_SpawnEntityParams);
        }
        break;
    case 3:
        if (g_pads[0].repeat & PAD_LEFT || g_pads[0].repeat & PAD_RIGHT ||
            g_pads[0].repeat & PAD_CROSS) {
            g_IsSpawnPreviewEnabled ^= 1;
            if (g_IsSpawnPreviewEnabled) {
                prevId = -1;
            } else {
                DelEntityPreview();
            }
            PLAY_MENU_SOUND();
        }
        break;
    case 4: // Place option
        if (g_pads[0].tapped & PAD_CROSS) {
            g_IsSpawnPlaceMode = true;
            g_SpawnPlaceEntity =
                SpawnEntity(g_Mode, g_SpawnEntityId, g_SpawnEntityParams);
            DelEntityPreview();
        }
        if (g_pads[0].tapped & PAD_SQUARE) {
            SpawnEntity(g_Mode, g_SpawnEntityId, g_SpawnEntityParams);
        }
        break;
    }

    if (prevId != g_SpawnEntityId || prevParams != g_SpawnEntityParams) {
        if (g_IsSpawnPreviewEnabled) {
            SetEntityPreview(g_Mode, g_SpawnEntityId, g_SpawnEntityParams);
        }
        PLAY_MENU_SOUND();
    }
}

Entity* AllocEntity(Entity* start, Entity* end) {
    Entity* current = start;
    while (current < end) {
        if (current->entityId == 0) {
            return current;
        }

        current++;
    }
    return NULL;
}

#include "../../src/destroy_entity.h"
