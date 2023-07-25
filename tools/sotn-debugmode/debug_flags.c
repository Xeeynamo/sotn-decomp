#include "debugmode.h"
#include "../../src/dra/dra.h"
#include "sfx.h"

u32* const g_DraDebugHitboxViewMode = 0x801362B0;
u32* const g_DraDebugHitboxViewEnabled = 0x800BD1C0;

int g_LoadPlayerState;
bool HookLoadAlucard();
bool HookLoadRichter();

void EnableNoClip(int param) {
    D_80098850 = param; // TODO merge: rename g_DebugPlayer
}
void EnableShowHitboxes(int param) {
    *g_DraDebugHitboxViewMode = param;
    *g_DraDebugHitboxViewEnabled = param;
}
void ChangePlayer(int param) {
    g_LoadPlayerState = 0;
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
    /**/ {0, 0, 1, ChangePlayer, DbgMenu_ActionOnChange},
    /**/ MENU_END,
};
DbgMenuCtrl g_DebugFlagsCtrl = {
    g_DebugFlagsItems,
    200,
    0x40,
    false,
};

void InitDebugFlagsPlayer(void) {}
void UpdateDebugFlagsPlayer(void) {
    FntPrint("No clip mode: %s\n", D_80098850 ? "on" : "off");
    FntPrint("Show hitboxes: %s\n", *g_DraDebugHitboxViewMode ? "on" : "off");
    FntPrint(
        "Player: %s\n", g_CurrentPlayableCharacter ? "Richter" : "Alucard");

    DbgMenuNavigate(&g_DebugFlagsCtrl);
}

bool HookLoadRichter() {
    if (g_IsUsingCd) {
        return;
    }

    FntPrint("Loading Richter: %d\n", g_LoadPlayerState);
    switch (g_LoadPlayerState++) {
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

bool HookLoadAlucard() {
    if (g_IsUsingCd) {
        return;
    }

    FntPrint("Loading Alucard: %d\n", g_LoadPlayerState);
    switch (g_LoadPlayerState++) {
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