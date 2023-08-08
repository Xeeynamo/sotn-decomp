#include "debugmode.h"
#include "../../src/dra/dra.h"
#include "sfx.h"

void Play(int param) { g_api.PlaySfx(param); }
void StopAllSounds(int param) { g_api.PlaySfx(SET_STOP_MUSIC); }
void ChangeSoundMode(int param) {
    g_api.PlaySfx(param ? SET_SOUNDMODE_STEREO : SET_SOUNDMODE_MONO);
}
void LoadStageSounds(int param) {
    g_CdStep = CdStep_LoadInit;
    g_LoadFile = CdFile_StageSfx;
    g_mapTilesetId = param;
}
void LoadServant(int param) {
    g_CdStep = CdStep_LoadInit;
    g_LoadFile = CdFile_ServantChr;
    g_mapTilesetId = param;
}

DbgMenuItem g_SoundItems[] = {
    {0, 0x001, 0x0FF, Play, DbgMenu_ActionOnInput},
    {0, 0x300, 0x5FF, Play, DbgMenu_ActionOnInput},
    {0, 0x600, 0xFFF, Play, DbgMenu_ActionOnInput},
    {0, 0, 0, StopAllSounds, DbgMenu_ActionOnInput},
    {STEREO_SOUND, MONO_SOUND, STEREO_SOUND, ChangeSoundMode,
     DbgMenu_ActionOnChange},
    {0, 0, 0x4F, LoadStageSounds, DbgMenu_ActionOnInput},
    {0, 0, 6, LoadServant, DbgMenu_ActionOnInput},
    MENU_END,
};
DbgMenuCtrl g_SoundCtrl = {
    g_SoundItems,
    212,
    0x40,
    false,
};

void InitSfxPlayer(void) {}
void UpdateSfxPlayer(void) {
    const char* stageName = DbgGetStageLba(g_SoundItems[5].param)->ovlName;

    if (g_IsUsingCd) {
        FntPrint("CD loading...\n");
        return;
    }

    FntPrint("Kind 1 ID: %03X\n", g_SoundItems[0].param);
    FntPrint("Kind 2 ID: %03X\n", g_SoundItems[1].param);
    FntPrint("Kind 3 ID: %03X\n", g_SoundItems[2].param);
    FntPrint("Stop all sounds\n");
    FntPrint("Sound mode: %s\n", g_SoundItems[4].param ? "MONO" : "STEREO");
    FntPrint("Load stage: SD_%s.VH (%02X)\n", stageName, g_SoundItems[5].param);
    FntPrint("Load servant: SD_00%d.VH\n", g_SoundItems[6].param);
    DbgMenuNavigate(&g_SoundCtrl);
}