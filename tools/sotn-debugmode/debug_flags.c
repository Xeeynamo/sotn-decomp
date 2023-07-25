#include "debugmode.h"
#include "../../src/dra/dra.h"
#include "sfx.h"

u32* const g_DraDebugHitboxViewMode = 0x801362B0;
u32* const g_DraDebugHitboxViewEnabled = 0x800BD1C0;

void EnableNoClip(int param) {
    D_80098850 = param; // TODO merge: rename g_DebugPlayer
}
void EnableShowHitboxes(int param) {
    *g_DraDebugHitboxViewMode = param;
    *g_DraDebugHitboxViewEnabled = param;
}
void ChangePlayer(int param) { ; }

DbgMenuItem g_DebugFlagsItems[] = {
    /**/ {0, 0, 1, EnableNoClip, DbgMenu_ActionOnChange},
    /**/ {0, 0, 1, EnableShowHitboxes, DbgMenu_ActionOnChange},
    /**/ {0, 0, 1, ChangePlayer, DbgMenu_ActionOnInput},
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