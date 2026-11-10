// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../zero.h"
#include "../zero/overlay.h"
#include "../game.h"
#include <saturn_player.h>
#include <saturn_weapon.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "module.h"

extern SaturnGameApi g_ApiInit;
extern SaturnPlayerOvl g_PlayerOvl;

void (*g_MariaMapMenuFunctions[19])(void);

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
    u32 slot = sector / (WEAPON_SLOT_SIZE / 0x800);
    SaturnWeaponOvl* header = dst;
    char name[8];
    u32 i;

    if (dst != (hand ? g_Weapon1OvlArea : g_Weapon0OvlArea) ||
        sector % (WEAPON_SLOT_SIZE / 0x800) || slot >= WEAPON_SLOTS) {
        satz_die("WEAPON%d.PRG loaded to %p from sector %u", hand, dst, sector);
    }
    snprintf(name, sizeof(name), "w%d_%02u", hand, slot);
    satz_module_open(hand ? SATZ_AREA_WEAPON1 : SATZ_AREA_WEAPON0, name, dst);
    if (hand) {
        DAT_060D9018 = (void*)header->entries[6];
        DAT_060D9040 = header->data;
    } else {
        for (i = 0; i < 16; i++) {
            *words[i] = (void*)header->entries[i];
        }
        DAT_060D6040 = header->data;
    }
    *size = WEAPON_SLOT_SIZE;
    return 1;
}

static void module_name(const char* prg, char* out, size_t size) {
    size_t i;

    for (i = 0; prg[i] && prg[i] != '.' && i + 1 < size; i++) {
        out[i] = (char)tolower((unsigned char)prg[i]);
    }
    out[i] = '\0';
}

int sotn_satz_install_overlay(
    const char* name, void* dst, u32 sector, s32* size) {
    char module[32];

    if (!is_prg(name)) {
        return 0;
    }
    if (!strcmp(name, "WEAPON0.PRG") || !strcmp(name, "WEAPON1.PRG")) {
        return install_weapon(name[6] == '1', dst, sector, size);
    }
    if (!strcmp(name, "MOVIE.PRG")) {
        DAT_06066000 = sotn_satz_movie_entry();
        *size = 0;
        return 1;
    }
    if (!strcmp(name, "GAME.PRG")) {
        if (dst != &g_GameOvl) {
            satz_die("%s loaded to %p, not its header area", name, dst);
        }
        memcpy(&g_GameOvl, &g_ApiInit, sizeof(SaturnGameApi));
        *size = sizeof(SaturnGameApi);
        return 1;
    }
    module_name(name, module, sizeof(module));
    if (dst == &g_PlayerOvl) {
        satz_module_open(SATZ_AREA_PLAYER, module, dst);
        DAT_060A5000 = (void (*)())g_PlayerOvl.init;
        DAT_060A5004 = g_PlayerOvl.main;
        DAT_060A5008 = g_PlayerOvl.updatePlayerEntities;
        *size = sizeof(SaturnPlayerOvl);
        return 1;
    }
    if (dst == &g_StageOverlayData) {
        satz_module_open(SATZ_AREA_STAGE, module, dst);
        *size = sizeof(SaturnStageDataTables);
        return 1;
    }
    satz_die("overlay %s loaded to %p, not an overlay area", name, dst);
}
