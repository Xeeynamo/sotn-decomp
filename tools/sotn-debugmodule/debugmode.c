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
void InitFlagChecker(void);
void UpdateDebugFlagsPlayer();
void UpdateEntitySpawn();
void UpdateSfxPlayer(void);
void UpdateFlagChecker(void);

DebugMenu g_DebugMenus[] = {
    DummyDummyDummy,      DummyDummyDummy,        true, false, "L2 = debug",
    InitDebugFlagsPlayer, UpdateDebugFlagsPlayer, true, true,  "Debug mode",
    InitEntitySpawn,      UpdateEntitySpawn,      true, true,  "Entity spwn",
    InitSfxPlayer,        UpdateSfxPlayer,        true, true,  "Snd player",
    InitFlagChecker,      UpdateFlagChecker,      true, true,  "Castleflags",
};

int g_DebugMode;
bool g_DebugModePaused;
bool g_EntitiesPaused;
bool g_ShowDebugMessages;
bool g_ShowCollisionLayer;
bool g_FrameByFrame;
int g_ShowDrawCalls;
bool g_ShowHBlankInfo;
int (*g_Hook)(void);

void DrawCollisionLayer();
void ShowDrawCalls(int mode);
void ShowHBlankInfo();
void DestroyEntity(Entity* item);

void Init(void) {
    int i;

    g_EntitiesPaused = false;
    g_DebugMode = 0;
    g_DebugModePaused = false;
    g_ShowDebugMessages = false;
    g_ShowCollisionLayer = false;
    g_FrameByFrame = false;
    g_ShowDrawCalls = 0;
    g_ShowHBlankInfo = false;
    g_Hook = NULL;
    for (i = 0; i < LEN(g_DebugMenus); i++) {
        g_DebugMenus[i].Init();
    }
}

bool UpdateLogic() {
    if (g_pads[0].tapped & PAD_L2) {
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

    if (g_pads[0].pressed & PAD_TRIANGLE || g_pads[0].pressed & PAD_START) {
        PauseDebugMode();
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
    bool entityPaused = false;
    bool isDebugMenuVisible = g_DebugModePaused == false && g_DebugMode != 0;
    bool skipFntOverride = g_ShowDebugMessages && !isDebugMenuVisible;

    if (!skipFntOverride) {
        BeginFont();
        DbgBeginDrawMenu();
    }
    if (g_ShowDebugMessages) {
        PrintDefaultFont();
    }

    if (!skipFntOverride && !isDebugMenuVisible) {
        if (g_ShowCollisionLayer) {
            if (g_GameState == Game_Play) {
                DrawCollisionLayer();
            }
        } else if (g_ShowDrawCalls) {
            ShowDrawCalls(g_ShowDrawCalls);
        } else if (g_ShowHBlankInfo) {
            ShowHBlankInfo();
        }
    }

    entityPaused = g_Hook ? !!g_Hook() : UpdateLogic();
    if (g_Hook) {
        entityPaused = !!g_Hook();
    }

    if (!skipFntOverride) {
        DbgEndDrawMenu();
        EndFont();
    }

    if (g_FrameByFrame) {
        return g_pads[0].repeat & PAD_L2 || g_pads[0].tapped & PAD_L1;
    }

    return entityPaused;
}

void PauseDebugMode() { g_DebugModePaused = true; }

void SetHook(int (*hook)(void)) { g_Hook = hook; }

u8 GetColType(s32 x, s32 y) {
    // borrowing first part of CheckCollision
    s32 absX;
    s32 absY;
    u8 colType;
    int new_var;
    // g_Camera.posX.i.lo doesn't seem to work like I expect
    u16* cameraX = (u16*)0x80073074;
    u16* cameraY = (u16*)0x8007307C;
    absX = x + *cameraX;
    absY = y + *cameraY;
    new_var = 0x10;
    if (absX < 0 || (u32)absX >= g_Tilemap.hSize << 8 || absY < 0 ||
        (u32)absY >= g_Tilemap.vSize << 8) {
        colType = 0;
    } else {

        // 16x16 blocks
        u16 colTile =
            g_Tilemap
                .fg[(absX >> 4) + (((absY >> 4) * g_Tilemap.hSize) * new_var)];
        TileDefinition* temp = (TileDefinition*)0x80073088;
        colType = temp->collision[colTile];
    }
    return colType;
}

void DrawCollisionLayer() {
    int x;
    int y;
    u8 colType;
    u16 cameraX = *(u16*)0x80073074;
    u16 cameraY = *(u16*)0x8007307C;

    // skip first 4 rows since we are stuck with their FntOpen settings
    SetFontCoord(-(cameraX & 0xF) + 8, -(cameraY & 0xF) + 16);
    for (y = 16; y < 224; y += 16) {
        // skip first column since we are stuck with their FntOpen settings
        FntPrint(" ", colType);
        for (x = 16; x < 256; x += 16) {
            colType = GetColType(x, y);

            // skip empty tiles
            if (colType == 0) {
                FntPrint("  ", colType);
            } else {
                FntPrint("%02x", colType);
            }
        }
        FntPrint("\n\n");
    }
}

void ShowDrawCalls(int mode) {
    const GpuUsage* const gpuMaxUsage = (GpuUsage*)0x801362DCU;
    GpuUsage* gpuUsage;

    switch (mode) {
    case 1:
        gpuUsage = &g_GpuUsage;
        FntPrint("cur call count\n");
        FntPrint("NOT IMPLEMENTED YET\n");
        break;
    case 2:
        gpuUsage = gpuMaxUsage;
        FntPrint("max call count\n");
        break;
    default:
        return;
    }

    FntPrint("dr  :%03x\n", gpuUsage->drawModes);
    FntPrint("gt4 :%03x\n", gpuUsage->gt4);
    FntPrint("g4  :%03x\n", gpuUsage->g4);
    FntPrint("gt3 :%03x\n", gpuUsage->gt3);
    FntPrint("line:%03x\n", gpuUsage->line);
    FntPrint("sp16:%03x\n", gpuUsage->sp16);
    FntPrint("sp  :%03x\n", gpuUsage->sp);
    FntPrint("tile:%03x\n", gpuUsage->tile);
    FntPrint("env :%03x\n", gpuUsage->env);
}

void ShowHBlankInfo() {
    GpuUsage* const gpuMaxUsage = (GpuUsage*)0x801362D0U;
    if (g_Timer & 1) {
        FntPrint("l=%03x/100\n", gpuMaxUsage[1]);
        FntPrint("l=%03x/100\n", gpuMaxUsage[0]);
    } else {
        FntPrint("l=%03x/100\n", gpuMaxUsage[0]);
        FntPrint("l=%03x/100\n", gpuMaxUsage[1]);
    }
    gpuMaxUsage[0] = gpuMaxUsage[1];
}
