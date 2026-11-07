// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../zero.h"
#include "../zero/overlay.h"
#include "../game.h"
#include <saturn_player.h>
#include <saturn_weapon.h>
#include <string.h>

extern SaturnGameApi g_ApiInit;
extern SaturnPlayerOvl SATZ_PLAYER_DATA;
extern SaturnStageDataTables SATZ_STAGE_DATA;
extern SaturnPlayerOvl g_PlayerOvl;

static const struct {
    const char* name;
    void* area;
    const void* header;
    u32 size;
} s_Overlays[] = {
    {"GAME.PRG", &g_GameOvl, &g_ApiInit, sizeof(SaturnGameApi)},
    {SATZ_PLAYER_PRG, &g_PlayerOvl, &SATZ_PLAYER_DATA, sizeof(SaturnPlayerOvl)},
    {SATZ_STAGE_PRG, &g_StageOverlayData, &SATZ_STAGE_DATA,
     sizeof(SaturnStageDataTables)},
};

#if SATZ_PLAYER_ID != 2
void (*g_MariaMapMenuFunctions[19])(void);
#endif

static int is_prg(const char* name) {
    size_t n = strlen(name);
    return n > 4 && !strcmp(name + n - 4, ".PRG");
}

void* sotn_satz_load_target(void* dst) {
    unsigned long address = (unsigned long)dst;

    if (address >= 0x30000000ul || (address & ~0x20000000ul) >= 0x08000000ul) {
        return dst;
    }
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

#ifdef SATZ_WEAPON_SLOT
extern SaturnWeaponOvl g_WeaponHeader;
extern void* DAT_060D9018;

static int install_weapon(int hand, void* dst, u32 sector, s32* size) {
    void** words[] = {
        (void**)g_Weapon0OvlArea,
        &DAT_060D6004,
        &DAT_060D6008,
        &DAT_060D600C,
        &DAT_060D6010,
        &DAT_060D6014,
        &DAT_060D6018,
        &DAT_060D601C,
        &DAT_060D6020,
        &DAT_060D6024,
        &DAT_060D6028,
        &DAT_060D602C,
        &DAT_060D6030,
        &DAT_060D6034,
        &DAT_060D6038,
        &DAT_060D603C,
    };
    u32 i;

    if (dst != (hand ? g_Weapon1OvlArea : g_Weapon0OvlArea) ||
        sector != SATZ_WEAPON_SLOT * (WEAPON_SLOT_SIZE / 0x800)) {
        satz_die("WEAPON%d.PRG loaded to %p from sector %u: only slot %d is "
                 "built",
                 hand, dst, sector, SATZ_WEAPON_SLOT);
    }
    if (hand) {
        DAT_060D9018 = (void*)g_WeaponHeader.entries[6];
        DAT_060D9040 = g_WeaponHeader.data;
    } else {
        for (i = 0; i < 16; i++) {
            *words[i] = (void*)g_WeaponHeader.entries[i];
        }
        DAT_060D6040 = g_WeaponHeader.data;
    }
    *size = WEAPON_SLOT_SIZE;
    return 1;
}

#endif

int sotn_satz_install_overlay(
    const char* name, void* dst, u32 sector, s32* size) {
    u32 i;

    if (!is_prg(name)) {
        return 0;
    }
#ifdef SATZ_WEAPON_SLOT
    if (!strcmp(name, "WEAPON0.PRG") || !strcmp(name, "WEAPON1.PRG")) {
        return install_weapon(name[6] == '1', dst, sector, size);
    }
#endif
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
