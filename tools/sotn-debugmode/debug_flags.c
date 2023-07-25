#include "debugmode.h"
#include "../../src/dra/dra.h"
#include "sfx.h"

u32* const g_DraDebugHitboxViewMode = 0x801362B0;
u32* const g_DraDebugHitboxViewEnabled = 0x800BD1C0;

int g_DbgLoadState;
int HookLoadStage();
int HookLoadAlucard();
int HookLoadRichter();

void EnableNoClip(int param) {
    D_80098850 = param; // TODO merge: rename g_DebugPlayer
}
void EnableShowHitboxes(int param) {
    *g_DraDebugHitboxViewMode = param;
    *g_DraDebugHitboxViewEnabled = param;
}
void ChangeStage(int param) {
    g_DbgLoadState = 0;
    g_mapTilesetId = param;
    g_StageId = param;
    SetHook(HookLoadStage);
}
void ChangePlayer(int param) {
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

DbgMenuItem g_DebugFlagsItems[] = {
    /**/ {0, 0, 1, EnableNoClip, DbgMenu_ActionOnChange},
    /**/ {0, 0, 1, EnableShowHitboxes, DbgMenu_ActionOnChange},
    /**/ {0, 0, 0x4F, ChangeStage, DbgMenu_ActionOnInput},
    /**/ {0, 0, 1, ChangePlayer, DbgMenu_ActionOnInput},
    /**/ MENU_END,
};
DbgMenuCtrl g_DebugFlagsCtrl = {
    g_DebugFlagsItems,
    200,
    0x40,
    false,
};

void InitDebugFlagsPlayer(void) {
    g_DebugFlagsItems[2].param = g_StageId;
    g_DebugFlagsItems[3].param = g_CurrentPlayableCharacter;
}
void UpdateDebugFlagsPlayer(void) {
    int stageCursor = g_DebugFlagsItems[2].param;
    Lba* lba = DbgGetStageLba(stageCursor);

    FntPrint("No clip mode: %s\n", D_80098850 ? "on" : "off");
    FntPrint("Show hitboxes: %s\n", *g_DraDebugHitboxViewMode ? "on" : "off");
    FntPrint("Stage: %02X %s (%s, %s)\n", stageCursor, lba->name, lba->ovlName,
             lba->gfxName);
    FntPrint(
        "Player: %s\n", g_DebugFlagsItems[3].param ? "Richter" : "Alucard");

    DbgMenuNavigate(&g_DebugFlagsCtrl);
}

int HookLoadStage() {
    if (g_GameState != Game_Play) {
        return false;
    }

    switch (g_DbgLoadState++) {
    case 0:
        g_CurrentPlayableCharacter = PLAYER_RICHTER;
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

int HookLoadRichter() {
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
        g_CurrentPlayableCharacter = PLAYER_RICHTER;
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

int HookLoadAlucard() {
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
        g_CurrentPlayableCharacter = PLAYER_ALUCARD;
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