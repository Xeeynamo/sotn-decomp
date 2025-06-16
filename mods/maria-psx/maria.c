#include <game.h>

// copied from src/dra/5F60C.c
typedef struct {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    s32 u;
    s32 v;
    s32 tpage;
    s32 clut;
} SubwpnIconParams;
static SubwpnIconParams D_psp_09147418[] = {
    {0x00C, 0x007, 0x00F, 0x017, 0x0D0, 0x0C0, 0x01E, 0x17F},
    {0x005, 0x009, 0x01F, 0x017, 0x0E0, 0x0B0, 0x01E, 0x17F},
    {0x005, 0x009, 0x01F, 0x017, 0x0E0, 0x0C8, 0x01E, 0x17F},
    {0x004, 0x000, 0x01F, 0x01F, 0x0E0, 0x0E0, 0x01E, 0x17F},
    {0x00C, 0x009, 0x010, 0x017, 0x098, 0x0D8, 0x01E, 0x17F}};
static s32 _hud_search_pattern[] = {
    0x009, 0x00F, 0x018, 0x010, 0x0A8, 0x0C0, 0x01E, 0x17F};
static bool DoesRichterHudMatch(s32* ptr) {
    return ptr[0] == _hud_search_pattern[0] &&
           ptr[1] == _hud_search_pattern[1] &&
           ptr[2] == _hud_search_pattern[2] &&
           ptr[3] == _hud_search_pattern[3] &&
           ptr[4] == _hud_search_pattern[4] &&
           ptr[5] == _hud_search_pattern[5] &&
           ptr[6] == _hud_search_pattern[6] && ptr[7] == _hud_search_pattern[7];
}
static SubwpnIconParams* SearchRichterSubwpnIconsDef(s32* ptr) {
    if (DoesRichterHudMatch(ptr)) {
        return (SubwpnIconParams*)ptr;
    }
    for (ptr = (s32*)0x800A0000; (u32)ptr < 0x8013C000U; ptr++) {
        if (DoesRichterHudMatch(ptr)) {
            return (SubwpnIconParams*)ptr;
        }
    }
    return NULL;
}
static void PatchHudSubweaponUV() {
    // offset of g_ricSubwpnIcons, from build/us/dra.map
    s32* DefaultOffset = (s32*)0x800A3014;
    SubwpnIconParams* params = SearchRichterSubwpnIconsDef(DefaultOffset);
    if (!params) {
        // failed to patch, silently fail and continue instead of crashing
        return;
    }
    // Patch Richter subweapon UVs and replace them with those from Maria
    memcpy(params, D_psp_09147418, sizeof(D_psp_09147418));
}

int func_8919BA8() { return 0; }
int func_90E4C58() { return 0; }
void func_90E4C18() {}
void func_90E4C68() {}
void func_9101FC8() {}

void func_91040A0(u_long** _gfxBank) {
    GfxBank* gfxBank;
    GfxLoad* gfxLoad;
    s32 i;

    gfxBank = (GfxBank*)_gfxBank; // avoid problems with the game.h signature
    if (gfxBank->kind == GFX_BANK_NONE) {
        return -1;
    }
    if (gfxBank->kind == -1) {
        return -1;
    }
    for (i = 0; i < LEN(g_GfxLoad); i++) {
        gfxLoad = &g_GfxLoad[i];
        if (gfxLoad->kind == GFX_BANK_NONE) {
            gfxLoad->kind = gfxBank->kind;
            gfxLoad->unk6 = 0;
            gfxLoad->unk8 = 0;
            gfxLoad->next = gfxBank->entries;
            return i;
        }
        gfxLoad++;
    }
}

void func_892667C(s32 paletteID, u16* paletteData) {
    int x = (paletteID & 15) * 16;
    int y = (paletteID >> 4) & 15;
    RECT rect = {x, 240 + y, 16, 1};
    LoadImage(&rect, (u_long*)paletteData);
}

void func_9142FC8(int sfx) {}

void func_89285A0(s32 angle, MATRIX* out) {
    short c = (short)rcos(angle);
    short s = (short)rsin(angle);
    out->m[0][0] = c;
    out->m[0][1] = (s16)-s;
    out->m[0][2] = 0;
    out->m[1][0] = s;
    out->m[1][1] = c;
    out->m[1][2] = 0;
    out->m[2][0] = 0;
    out->m[2][1] = 0;
    out->m[2][2] = 4096;
    out->t[2] = 0;
    out->t[1] = 0;
    out->t[0] = 0;
}

s16 func_90E0E30(PrimitiveType kind, s32 count) {
    return g_api.AllocPrimitives(kind, count);
}

void MARIA_Load();
void MarInit(s16 initParam);
void MarPsxInit(u16 initParam) {
    static int isInitialized = 0;
    if (!isInitialized) {
        MARIA_Load();
        PatchHudSubweaponUV();
        g_api.CalcDealDamageMaria = g_api.func_800FD664;
        g_api.CalcPlayerDamageMaria = g_api.CalcPlayerDamage;
        isInitialized = true;
    }

    // Call the actual init function
    MarInit(initParam);
}

void MarMain(void);
void MarPsxMain() {
    // on PSP, subWeapon==0 falls to the subweapon Doll. But on PSX the HUD will
    // show no icon. We need to tell to PSX DRA to show Doll on the HUD as
    // subWeapon=5, but tell to MARIA overlay that subWeapon=5 is actually Doll
    if (g_Status.subWeapon >= 5) {
        g_Status.subWeapon = 0;
    }
    MarMain();
    if (g_Status.subWeapon == 0) {
        // Force to show Doll on the HUD
        g_Status.subWeapon = 5;
    }
}

#include "gen/maria.h"
void MarUpdatePlayerEntities(void);
void MarGetPlayerSensor(Collider* col);
// needs to stay at the bottom for the struct to fall to 0x8013C000
PlayerOvl MARIA_override = {
    MarPsxMain,    MarPsxInit,    MarUpdatePlayerEntities, MarGetPlayerSensor,
    maria_sprites, maria_sprites, maria_sprites,           maria_sprites,
};
