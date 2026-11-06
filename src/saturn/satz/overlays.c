// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../zero.h"
#include "../zero/overlay.h"
#include "../game.h"
#include <saturn_player.h>
#include <string.h>

extern SaturnGameApi g_ApiInit;
extern SaturnPlayerOvl MARIA_player;
extern SaturnStageDataTables g_Stage15Data;
extern SaturnPlayerOvl g_PlayerOvl;

static const struct {
    const char* name;
    void* area;
    const void* header;
    u32 size;
} s_Overlays[] = {
    {"GAME.PRG", &g_GameOvl, &g_ApiInit, sizeof(SaturnGameApi)},
    {"MARIA.PRG", &g_PlayerOvl, &MARIA_player, sizeof(SaturnPlayerOvl)},
    {"STAGE_15.PRG", &g_StageOverlayData, &g_Stage15Data,
     sizeof(SaturnStageDataTables)},
};

static int is_prg(const char* name) {
    size_t n = strlen(name);
    return n > 4 && !strcmp(name + n - 4, ".PRG");
}

void* sotn_satz_load_target(void* dst) {
    unsigned long address = (unsigned long)dst;

    if ((address & 0x07F00000) >= 0x05A00000 &&
        (address & 0x07F00000) < 0x06000000) {
        return satz_bus_pointer(address);
    }
    if ((address & 0x07F00000) == 0x06000000 ||
        (address & 0x07F00000) == 0x00200000) {
        satz_die(
            "load into work RAM address %08lX: give it a C label", address);
    }
    return dst;
}

s32 (*sotn_satz_movie_entry(void))(void);
extern s32 (*DAT_06066000)();

int sotn_satz_install_overlay(const char* name, void* dst, s32* size) {
    u32 i;

    if (!is_prg(name)) {
        return 0;
    }
    if (!strcmp(name, "MOVIE.PRG")) {
        DAT_06066000 = sotn_satz_movie_entry();
        *size = 0;
        return 1;
    }
    for (i = 0; i < sizeof(s_Overlays) / sizeof(s_Overlays[0]); i++) {
        if (!strcmp(name, s_Overlays[i].name)) {
            if (dst != s_Overlays[i].area) {
                satz_die("%s loaded to %p, not its header area", name, dst);
            }
            memcpy(
                s_Overlays[i].area, s_Overlays[i].header, s_Overlays[i].size);
            if (s_Overlays[i].area == &g_PlayerOvl) {
                DAT_060A5000 = (void (*)())g_PlayerOvl.init;
                DAT_060A5004 = g_PlayerOvl.main;
                DAT_060A5008 = g_PlayerOvl.updatePlayerEntities;
            }
            *size = s_Overlays[i].size;
            return 1;
        }
    }
    satz_die("overlay %s is not in the native build", name);
}
