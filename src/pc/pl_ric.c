#include <game.h>
#include "../../ric/ric.h"

extern PlayerOvl RIC_player;

static void (*real_player_init)(u16 params);
static void InjectPlayerInit(u16 params) {
    // fixes a bug where g_CurrentEntity is not correctly initialized at init
    g_CurrentEntity = &PLAYER;
    real_player_init(params);
}

void InitPlayerRic(void) {
    g_PlOvl.D_8013C000 = RIC_player.D_8013C000;
    g_PlOvl.D_8013C004 = InjectPlayerInit;
    g_PlOvl.D_8013C008 = RIC_player.D_8013C008;
    g_PlOvl.D_8013C00C = RIC_player.D_8013C00C;
    real_player_init = RIC_player.D_8013C004;
}

FactoryBlueprint g_RicFactoryBlueprints[78];

// clang-format off
// from assets/ric/subweapondefs.json
SubweaponDef D_80154688[NUM_WEAPONS] = {
    {0, 30000, 0, 0, 0, 0, 0, 0, 2, 1, 15, 0, 0},
    {20, 1, ELEMENT_CUT | ELEMENT_HOLY, 3, 4, 4, 0, BP_SUBWPN_DAGGER, 2, 129, 21, 0, 32},
    {50, 1, ELEMENT_CUT | ELEMENT_HOLY, 3, 32, 4, 0, BP_AXE, 2, 129, 20, 0, 32},
    {5, 1, ELEMENT_HIT, 1, 32, 4, 0, BP_SUBWPN_HOLYWATER, 2, 1, 16, 0, 0},
    {40, 1, ELEMENT_HIT | ELEMENT_HOLY, 4, 32, 4, 0, BP_SUBWPN_CROSS, 2, 129, 12, 0, 0},
    {5, 5, ELEMENT_HOLY, 2, 24, 4, 0, BP_BIBLE, 2, 1, 26, 0, 0},
    {0, 10, 0, 1, 50, 0, 0, BP_SUBWPN_STOPWATCH, 0, 0, 27, 0, 0},
    {40, 1, ELEMENT_HIT | ELEMENT_HOLY, 3, 32, 4, 0, BP_REBOUND_STONE, 2, 1, 25, 0, 0},
    {20, 1, ELEMENT_HOLY, 3, 10, 4, 0, BP_VIBHUTI, 2, 1, 24, 0, 0},
    {20, 10, ELEMENT_HOLY | ELEMENT_THUNDER, 1, 10, 10, 0, BP_AGUNEA, 2, 129, 28, 0, 0},
    {15, 30000, ELEMENT_HOLY, 1, 10, 4, 0, 0, 2, 1, 10, 0, 0},
    {8, 1, ELEMENT_HOLY | ELEMENT_FIRE, 2, 16, 4, 0, BP_HOLYWATER_FLAMES, 2, 1, 0, 0, 0},
    {40, 20, ELEMENT_HIT | ELEMENT_HOLY, 1, 32, 4, 0, BP_CRASH_CROSS, 2, 1, 0, 0, 0},
    {60, 0, ELEMENT_HIT | ELEMENT_HOLY, 1, 24, 4, 0, 0, 2, 1, 0, 0, 0},
    {32, 5, ELEMENT_HIT | ELEMENT_HOLY, 1, 32, 4, 0, 0, 2, 1, 0, 0, 0},
    {64, 15, ELEMENT_HIT | ELEMENT_HOLY | ELEMENT_FIRE, 1, 32, 4, 0, 0, 2, 1, 0, 32},
    {80, 15, ELEMENT_HIT | ELEMENT_HOLY, 1, 32, 24, 0, BP_HYDROSTORM, 130, 1, 0, 0, 0},
    {80, 0, ELEMENT_HIT, 1, 32, 4, 0, 0, 2, 1, 0, 0, 32},
    {20, 0, ELEMENT_HIT, 1, 32, 4, 0, 0, 2, 1, 0, 0, 0},
    {5, 0, ELEMENT_HIT | ELEMENT_HOLY, 1, 32, 4, 0, 0, 2, 1, 0, 0, 0},
    {40, 10, ELEMENT_CUT | ELEMENT_HOLY, 1, 32, 4, 0, BP_CRASH_AXE, 2, 129, 0, 0, 32},
    {20, 10, ELEMENT_CUT | ELEMENT_HOLY, 1, 4, 4, 0, BP_CRASH_DAGGER, 2, 129, 0, 0, 32},
    {80, 0, ELEMENT_HIT, 1, 32, 4, 0, 0, 2, 1, 0, 0, 32},
    {60, 0, ELEMENT_HIT, 1, 32, 4, 0, 0, 2, 1, 0, 0, 128},
    {20, 10, ELEMENT_HIT | ELEMENT_HOLY, 1, 32, 4, 0, BP_CRASH_VITHUBI, 2, 1, 0, 0, 0},
    {20, 10, ELEMENT_HIT, 1, 32, 4, 0, BP_CRASH_REBOUND_STONE, 2, 1, 0, 0, 0},
    {80, 15, ELEMENT_HIT | ELEMENT_HOLY, 1, 32, 4, 0, BP_CRASH_BIBLE, 2, 1, 0, 0, 0},
    {0, 20, ELEMENT_HIT, 1, 32, 32, 0, BP_CRASH_STOPWATCH, 2, 1, 0, 0, 0},
    {80, 20, ELEMENT_HIT | ELEMENT_THUNDER, 1, 32, 4, 0, BP_CRASH_AGUNEA, 2, 1, 0, 0, 0},
    {10, 30000, ELEMENT_HIT, 1, 32, 4, 0, 0, 2, 1, 0, 0, 0},
    {15, 30000, ELEMENT_HIT | ELEMENT_THUNDER, 1, 32, 64, 0, 0, 2, 1, 0, 0, 0},
};
