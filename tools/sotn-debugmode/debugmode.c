#include "debugmode.h"
#include "sfx.h"

typedef struct {
    void (*Init)();
    void (*Update)();
    bool showMenu;
    bool pauseGame;
    const char* name;
} DebugMenu;

void DummyDummyDummy() {}
void InitDebugFlagsPlayer(void);
void InitEntitySpawn(void);
void InitSfxPlayer(void);
void InitDraTest800FD874(void);
void InitCollisionViewer(void);
void InitFlagChecker(void);
void InitStageSelect(void);
void UpdateDebugFlagsPlayer();
void UpdateDraEntitySpawn();
void UpdateStageEntitySpawn();
void UpdateSfxPlayer(void);
void UpdateDraTest800FD874(void);
void UpdateCollisionViewer(void);
void UpdateFlagChecker(void);
void UpdateStageSelect(void);

DebugMenu g_DebugMenus[] = {
    DummyDummyDummy,      DummyDummyDummy,        true,  false, "R2 = debug",
    InitDebugFlagsPlayer, UpdateDebugFlagsPlayer, true,  true,  "Debug mode",
    InitEntitySpawn,      UpdateDraEntitySpawn,   true,  true,  "DRA spawn",
    InitEntitySpawn,      UpdateStageEntitySpawn, true,  true,  "Stage spawn",
    InitSfxPlayer,        UpdateSfxPlayer,        true,  true,  "Snd player",
    InitDraTest800FD874,  UpdateDraTest800FD874,  true,  true,  "Inventory",
    InitCollisionViewer,  UpdateCollisionViewer,  false, false, "Collision map",
    InitFlagChecker,      UpdateFlagChecker,      true,  true,  "Castleflags",
    InitStageSelect,      UpdateStageSelect,      true,  true,  "Stages",
};

int g_DebugMode;
bool g_DebugModePaused;
bool g_EntitiesPaused;
bool (*g_Hook)(void);

void DestroyEntity(Entity* item);
void Init(void) {
    int i;

    g_EntitiesPaused = false;
    g_DebugMode = 0;
    g_DebugModePaused = 0;
    for (i = 0; i < LEN(g_DebugMenus); i++) {
        g_DebugMenus[i].Init();
    }
}

bool UpdateLogic() {
    if (g_pads->tapped & PAD_R2) {
        if (!g_DebugModePaused) {
            g_DebugMode++;
            if (g_DebugMode >= LEN(g_DebugMenus)) {
                g_DebugMode = 0;
            }
        } else {
            g_DebugModePaused = false;
        }
        PLAY_MENU_SOUND();
    }

    if (g_DebugModePaused) {
        return;
    }

    if (g_pads->pressed & PAD_TRIANGLE || g_pads->pressed & PAD_START) {
        g_DebugModePaused = true;
        return;
    }

    if (g_DebugMenus[g_DebugMode].pauseGame != g_EntitiesPaused) {
        g_EntitiesPaused ^= 1;
    }

    if (g_DebugMenus[g_DebugMode].showMenu) {
        DbgDrawMenuRect(159, 22, 90, 14);
        SetFontCoord(160, 26);
        FntPrint("%s\n", g_DebugMenus[g_DebugMode].name);
    }
    SetFontCoord(8, 48);
    g_DebugMenus[g_DebugMode].Update();

    return !g_EntitiesPaused;
}

bool Update(void) {
    bool entityPaused;

    BeginFont();
    DbgBeginDrawMenu();

    entityPaused = g_Hook ? !!g_Hook() : UpdateLogic();
    if (g_Hook) {
        entityPaused = !!g_Hook();
    }

    DbgEndDrawMenu();
    EndFont();

    return entityPaused;
}

void SetHook(int (*hook)(void)) { g_Hook = hook; }