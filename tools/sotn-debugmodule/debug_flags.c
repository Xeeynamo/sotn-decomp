#include "debugmode.h"
#include "../../src/dra/dra.h"
#include "sfx.h"

static u32* const g_DraDebugHitboxViewMode = (u32*)0x801362B0;
static u32* const g_DraDebugHitboxViewEnabled = (u32*)0x800BD1C0;

static int g_DbgLoadState;
static int HookLoadStage();
static int HookLoadAlucard();
static int HookLoadRichter();

static void ChangeStage(int param) {
    g_DbgLoadState = 0;
    g_LoadOvlIdx = param;
    g_StageId = param;
    SetHook(HookLoadStage);
}
static void ChangePlayer(int param) {
    g_DbgLoadState = 0;
    switch (param) {
    case 0:
        SetHook(HookLoadAlucard);
        break;
    case 1:
        SetHook(HookLoadRichter);
        break;
    }
}
static void SetNoClip(int param) { g_DebugPlayer = param; }
static void SetFrameByFrame(bool isEnabled) { g_FrameByFrame = isEnabled; }
static void SetShowHitboxes(int param) {
    *g_DraDebugHitboxViewMode = param;
    *g_DraDebugHitboxViewEnabled = param;
}
static void SetShowDebugMessages(bool isVisible) {
    g_ShowDebugMessages = isVisible;
    if (isVisible) {
        g_ShowCollisionLayer = false;
        g_ShowDrawCalls = 0;
        g_ShowHBlankInfo = false;
    }
}
static void SetShowCollisionLayer(bool isVisible) {
    g_ShowCollisionLayer = isVisible;
    if (isVisible) {
        g_ShowDebugMessages = false;
        g_ShowDrawCalls = 0;
        g_ShowHBlankInfo = false;
    }
}
static void SetShowDrawCalls(int param) {
    g_ShowDrawCalls = param;
    if (param != 0) {
        g_ShowCollisionLayer = false;
        g_ShowDebugMessages = false;
        g_ShowHBlankInfo = false;
    }
}
static void SetShowHBlankInfo(bool isVisible) {
    g_ShowHBlankInfo = isVisible;
    if (isVisible) {
        g_ShowCollisionLayer = false;
        g_ShowDebugMessages = false;
        g_ShowDrawCalls = 0;
    }
}

static DbgMenuItem g_DebugFlagsItems[] = {
    /**/ {0, 0, 0x4F, ChangeStage, DbgMenu_ActionOnInput},
    /**/ {0, 0, 1, ChangePlayer, DbgMenu_ActionOnInput},
    /**/ {0, false, true, SetNoClip, DbgMenu_ActionOnChange},
    /**/ {0, false, true, SetFrameByFrame, DbgMenu_ActionOnChange},
    /**/ {0, false, true, SetShowHitboxes, DbgMenu_ActionOnChange},
    /**/ {0, false, true, SetShowDebugMessages, DbgMenu_ActionOnChange},
    /**/ {0, false, true, SetShowCollisionLayer, DbgMenu_ActionOnChange},
    /**/ {0, 0, 2, SetShowDrawCalls, DbgMenu_ActionOnChange},
    /**/ {0, 0, 2, SetShowHBlankInfo, DbgMenu_ActionOnChange},
    /**/ MENU_END,
};
static DbgMenuCtrl g_DebugFlagsCtrl = {
    g_DebugFlagsItems,
    236,
    0x40,
    false,
};

static const char* const c_DrawCalls[] = {
    "off",
    "current",
    "max",
};

void InitDebugFlagsPlayer(void) {
    g_DebugFlagsItems[0].param = g_StageId;
    g_DebugFlagsItems[1].param = g_PlayableCharacter;
}
void UpdateDebugFlagsPlayer(void) {
    int stageCursor = g_DebugFlagsItems[0].param;
    Lba* lba = DbgGetStageLba(stageCursor);

    FntPrint("Stage: %02X %s (%s, %s)\n", stageCursor, lba->name, lba->ovlName,
             lba->gfxName);
    FntPrint(
        "Player: %s\n", g_DebugFlagsItems[1].param ? "Richter" : "Alucard");
    FntPrint("No clip: %s\n", g_DebugPlayer ? "on" : "off");
    FntPrint("Frame by frame: %s  (L1+L2)\n", g_FrameByFrame ? "on" : "off");
    FntPrint("Show hitboxes: %s\n", *g_DraDebugHitboxViewMode ? "on" : "off");
    FntPrint("Show debug messages: %s\n", g_ShowDebugMessages ? "on" : "off");
    FntPrint("Show collision layer: %s\n", g_ShowCollisionLayer ? "on" : "off");
    FntPrint("Show draw calls: %s\n", c_DrawCalls[g_DebugFlagsItems[7].param]);
    FntPrint("Show HBlank info: %s\n", g_ShowHBlankInfo ? "on" : "off");

    DbgMenuNavigate(&g_DebugFlagsCtrl);
}

static int HookLoadStage() {
    if (g_GameState != Game_Play) {
        return false;
    }

    switch (g_DbgLoadState++) {
    case 0:
        g_PlayableCharacter = PLAYER_RICHTER;
        g_GameState = Game_NowLoading;
        g_GameStep = 2;
        break;
    default:
        if (g_GameState == Game_Play) {
            SetHook(NULL);
        }
        break;
    }

    return true;
}

static int HookLoadRichter() {
    if (g_IsUsingCd) {
        return false;
    }

    switch (g_DbgLoadState++) {
    case 0:
        g_CdStep = CdStep_LoadInit;
        g_LoadFile = CdFile_RichterPrg;
        break;
    case 1:
        g_CdStep = CdStep_LoadInit;
        g_LoadFile = CdFile_GameChr;
        break;
    case 2:
        g_PlayableCharacter = PLAYER_RICHTER;
        g_GameState = Game_NowLoading;
        g_GameStep = 2;
        break;
    default:
        if (g_GameState == Game_Play) {
            SetHook(NULL);
        }
        break;
    }

    return true;
}

static int HookLoadAlucard() {
    if (g_IsUsingCd) {
        return false;
    }

    switch (g_DbgLoadState++) {
    case 0:
        g_CdStep = CdStep_LoadInit;
        g_LoadFile = CdFile_AlucardPrg;
        break;
    case 1:
        g_CdStep = CdStep_LoadInit;
        g_LoadFile = CdFile_GameChr;
        break;
    case 2:
        g_PlayableCharacter = PLAYER_ALUCARD;
        g_GameState = Game_NowLoading;
        g_GameStep = 2;
        break;
    default:
        if (g_GameState == Game_Play) {
            SetHook(NULL);
        }
        break;
    }

    return true;
}