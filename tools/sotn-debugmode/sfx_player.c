#include "debugmode.h"
#include "../../src/dra/dra.h"
#include "sfx.h"

typedef struct {
    int param;
    int min;
    int max;
    void (*action)(int param);
} Sounds;

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

Sounds g_SoundCtrl[] = {
    /**/ {0, 0x001, 0x0FF, Play},
    /**/ {0, 0x300, 0x5FF, Play},
    /**/ {0, 0x600, 0xFFF, Play},
    /**/ {0, 0, 0, StopAllSounds},
    /**/ {STEREO_SOUND, MONO_SOUND, STEREO_SOUND, ChangeSoundMode},
    /**/ {0, 0, 0x4F, LoadStageSounds},
    /**/ {0, 0, 6, LoadServant},
};
int g_SoundOption;

void InitSfxPlayer(void) {
    int i;

    g_SoundOption = 0;
    for (i = 0; i < LEN(g_SoundCtrl); i++) {
        g_SoundCtrl[i].param = g_SoundCtrl[i].min;
    }
}
void UpdateSfxPlayer(void) {
    const int MenuWidth = 212;
    const int PageScroll = 0x40;
    const char* stageName = DbgGetStageLba(g_SoundCtrl[5].param)->ovlName;

    DbgDrawMenuRect(4, 44, MenuWidth + 10, 8 + LEN(g_SoundCtrl) * 8);
    DbgDrawCursor(9, 48 + g_SoundOption * 8, MenuWidth, 8);
    if (g_IsUsingCd) {
        FntPrint("CD loading...\n");
        return;
    }

    FntPrint("Kind 1 ID: %03X\n", g_SoundCtrl[0].param);
    FntPrint("Kind 2 ID: %03X\n", g_SoundCtrl[1].param);
    FntPrint("Kind 3 ID: %03X\n", g_SoundCtrl[2].param);
    FntPrint("Stop all sounds\n");
    FntPrint("Sound mode: %s\n", g_SoundCtrl[4].param ? "MONO" : "STEREO");
    FntPrint("Load stage: SD_%s.VH (%02X)\n", stageName, g_SoundCtrl[5].param);
    FntPrint("Load servant: SD_00%d.VH\n", g_SoundCtrl[6].param);

    if (g_pads->tapped & PAD_L1) {
        g_SoundCtrl[g_SoundOption].param -= PageScroll;
    }
    if (g_pads->tapped & PAD_R1) {
        g_SoundCtrl[g_SoundOption].param += PageScroll;
    }
    if (g_pads->repeat & PAD_LEFT) {
        g_SoundCtrl[g_SoundOption].param--;
    }
    if (g_pads->repeat & PAD_RIGHT) {
        g_SoundCtrl[g_SoundOption].param++;
    }
    if (g_SoundCtrl[g_SoundOption].param < g_SoundCtrl[g_SoundOption].min) {
        g_SoundCtrl[g_SoundOption].param = g_SoundCtrl[g_SoundOption].max;
    } else if (
        g_SoundCtrl[g_SoundOption].param > g_SoundCtrl[g_SoundOption].max) {
        g_SoundCtrl[g_SoundOption].param = g_SoundCtrl[g_SoundOption].min;
    }

    if (g_pads->tapped & PAD_CROSS && g_SoundCtrl[g_SoundOption].action) {
        g_SoundCtrl[g_SoundOption].action(g_SoundCtrl[g_SoundOption].param);
    }

    if (g_pads->tapped & PAD_UP) {
        g_SoundOption--;
        if (g_SoundOption < 0) {
            g_SoundOption = LEN(g_SoundCtrl) - 1;
        }
        g_api.PlaySfx(NA_SE_SY_MOVE_MENU_CURSOR);
    }
    if (g_pads->tapped & PAD_DOWN) {
        g_SoundOption++;
        if (g_SoundOption >= LEN(g_SoundCtrl)) {
            g_SoundOption = 0;
        }
        g_api.PlaySfx(NA_SE_SY_MOVE_MENU_CURSOR);
    }
}