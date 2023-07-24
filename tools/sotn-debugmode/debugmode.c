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
void InitEntitySpawn(void);
void InitSfxPlayer(void);
void InitDraTest800FD874(void);
void InitCollisionViewer(void);
void InitFlagChecker(void);
void InitStageSelect(void);
void UpdateDraEntitySpawn();
void UpdateStageEntitySpawn();
void UpdateSfxPlayer(void);
void UpdateDraTest800FD874(void);
void UpdateCollisionViewer(void);
void UpdateFlagChecker(void);
void UpdateStageSelect(void);

void Foo() {}

DebugMenu g_DebugMenus[] = {
    DummyDummyDummy,     DummyDummyDummy,        true,  false, "Debug mode",
    InitEntitySpawn,     UpdateDraEntitySpawn,   true,  true,  "DRA spawn",
    InitEntitySpawn,     UpdateStageEntitySpawn, true,  true,  "Stage spawn",
    InitSfxPlayer,       UpdateSfxPlayer,        true,  true,  "Snd player",
    InitDraTest800FD874, UpdateDraTest800FD874,  true,  true,  "Inventory",
    InitCollisionViewer, UpdateCollisionViewer,  false, false, "Collision map",
    InitFlagChecker,     UpdateFlagChecker,      true,  true,  "Castleflags",
    InitStageSelect,     UpdateStageSelect,      true,  true,  "Stages",
};

int g_DebugMode;
bool g_EntitiesPaused;
int g_PrimIndex;
Primitive* g_PrimFirst;
Primitive* g_PrimCur;

void DestroyEntity(Entity* item);
void Init(void) {
    int i;

    g_EntitiesPaused = false;
    g_DebugMode = 0;
    for (i = 0; i < LEN(g_DebugMenus); i++) {
        g_DebugMenus[i].Init();
    }
}
bool Update(void) {
    BeginFont();
    DbgBeginDrawMenu();

    if (g_pads->tapped & PAD_R2) {
        g_DebugMode++;
        if (g_DebugMode >= LEN(g_DebugMenus)) {
            g_DebugMode = 0;
        }
        g_api.PlaySfx(NA_SE_SY_MOVE_MENU_CURSOR);
    }

    if (g_DebugMenus[g_DebugMode].pauseGame != g_EntitiesPaused) {
        g_EntitiesPaused ^= 1;
    }

    if (g_DebugMenus[g_DebugMode].showMenu) {
        DbgDrawMenuRect(159, 22, 90, 14);
        SetFontCoord(160, 26);
        FntPrint("%s\n", g_DebugMenus[g_DebugMode].name);
    } else {
    }
    SetFontCoord(8, 48);
    g_DebugMenus[g_DebugMode].Update();

    DbgEndDrawMenu();
    EndFont();

    return !g_EntitiesPaused;
}