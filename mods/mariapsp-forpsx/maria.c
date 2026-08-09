// SPDX-License-Identifier: AGPL-3.0-or-later
#include <maria.h>
#ifdef MARIA_SFX_DEBUG

#define MARIA_SFX_FIRST SFX_VO_MAR_8E6
#define MARIA_SFX_LAST SFX_VO_MAR_DEATH
#define MARIA_PSX_SFX_FIRST SFX_VO_RIC_ATTACK_A
#define SFX_DATA_FIRST 0x600
extern Unkstruct_800BF554 g_SfxData[];
void MarPlaySfx(s32 sfx);

#define MARIA_SFX_COUNT 16
#define MARIA_SFX_MENU_PRIMS 176
#define MARIA_SFX_MENU_X 8
#define MARIA_SFX_MENU_Y 48

static s32 s_MariaSfxIndex;
static s16 s_MariaSfxMenuPrimIndex = -1;

static const char* const s_MariaSfxEnumNames[MARIA_SFX_COUNT] = {
    "SFX_VO_MAR_8E6",    "SFX_VO_MAR_ATTACK_C", "SFX_VO_MAR_8E8",
    "SFX_VO_MAR_8E9",    "SFX_VO_MAR_8EA",      "SFX_VO_MAR_8EB",
    "SFX_VO_MAR_8EC",    "SFX_VO_MAR_8ED",      "SFX_VO_MAR_8EE",
    "SFX_VO_MAR_8EF",    "SFX_VO_MAR_8F0",      "SFX_VO_MAR_8F1",
    "SFX_VO_MAR_PAIN_B", "SFX_VO_MAR_PAIN_C",   "SFX_VO_MAR_PAIN_D",
    "SFX_VO_MAR_DEATH",
};

static const char* const s_MariaSfxSampleNames[MARIA_SFX_COUNT] = {
    "MARY2A", "MARY2B", "MARY2C", "MARY2D", "MARY2E", "MARY2F",
    "MARY2G", "MARY2Q", "MARY2P", "MARY2N", "MARY2O", "MARY2M",
    "MARY2R", "MARY2T", "MARY2V", "MARY2W",
};

static Primitive* DrawMariaSfxChar(Primitive* prim, s32* x, s32 y, char ch) {
    u8 glyph;

    if (ch == ' ') {
        *x += FONT_W;
        return prim;
    }
    if (prim == NULL) {
        return NULL;
    }

    glyph = ch - 0x20;
    prim->type = PRIM_SPRT;
    prim->tpage = 0x1E;
    prim->clut = PAL_UNK_196;
    prim->u0 = (glyph & 0xF) * FONT_W;
    prim->v0 = (glyph & 0xF0) >> 1;
    prim->u1 = FONT_W;
    prim->v1 = FONT_H;
    prim->x0 = *x;
    prim->y0 = y;
    prim->priority = 0x1F1;
    prim->drawMode = DRAW_DEFAULT;
    *x += FONT_W;
    return prim->next;
}

static Primitive* DrawMariaSfxString(
    Primitive* prim, s32* x, s32 y, const char* text) {
    while (*text != '\0') {
        prim = DrawMariaSfxChar(prim, x, y, *text++);
    }
    return prim;
}

static Primitive* DrawMariaSfxHex(Primitive* prim, s32* x, s32 y, u32 value) {
    static const char digits[] = "0123456789ABCDEF";
    s32 shift;

    for (shift = 12; shift >= 0; shift -= 4) {
        prim = DrawMariaSfxChar(prim, x, y, digits[(value >> shift) & 0xF]);
    }
    return prim;
}

static Primitive* DrawMariaSfxDec2(Primitive* prim, s32* x, s32 y, u32 value) {
    prim = DrawMariaSfxChar(prim, x, y, '0' + value / 10);
    return DrawMariaSfxChar(prim, x, y, '0' + value % 10);
}

static Primitive* DrawMariaSfxDec3(Primitive* prim, s32* x, s32 y, u32 value) {
    prim = DrawMariaSfxChar(prim, x, y, value >= 100 ? '0' + value / 100 : ' ');
    prim =
        DrawMariaSfxChar(prim, x, y, value >= 10 ? '0' + value / 10 % 10 : ' ');
    return DrawMariaSfxChar(prim, x, y, '0' + value % 10);
}

static void DrawMariaSfxMenu(
    s32 mariaSfx, s32 psxSfx, Unkstruct_800BF554* metadata) {
    Primitive* prim = &g_PrimBuf[s_MariaSfxMenuPrimIndex];
    s32 x;
    s32 y = MARIA_SFX_MENU_Y;

    prim->type = PRIM_TILE;
    prim->r0 = prim->g0 = prim->b0 = 0x10;
    prim->x0 = 4;
    prim->y0 = y - 4;
    prim->u0 = 248;
    prim->v0 = 84;
    prim->priority = 0x1F0;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;

    x = MARIA_SFX_MENU_X;
    prim = DrawMariaSfxString(prim, &x, y, "MARIA SFX ");
    prim = DrawMariaSfxDec2(prim, &x, y, s_MariaSfxIndex + 1);
    prim = DrawMariaSfxString(prim, &x, y, "/16");

    x = MARIA_SFX_MENU_X;
    y += 10;
    prim = DrawMariaSfxString(prim, &x, y, "Sfx ");
    prim =
        DrawMariaSfxString(prim, &x, y, s_MariaSfxEnumNames[s_MariaSfxIndex]);

    x = MARIA_SFX_MENU_X;
    y += 10;
    prim = DrawMariaSfxString(prim, &x, y, "ID ");
    prim = DrawMariaSfxHex(prim, &x, y, mariaSfx);
    prim = DrawMariaSfxString(prim, &x, y, " -> PSX ");
    prim = DrawMariaSfxHex(prim, &x, y, psxSfx);

    x = MARIA_SFX_MENU_X;
    y += 10;
    prim = DrawMariaSfxString(prim, &x, y, "WAV ");
    prim =
        DrawMariaSfxString(prim, &x, y, s_MariaSfxSampleNames[s_MariaSfxIndex]);

    x = MARIA_SFX_MENU_X;
    y += 10;
    prim = DrawMariaSfxString(prim, &x, y, "VAB ");
    prim = DrawMariaSfxDec3(prim, &x, y, metadata->vabid);
    prim = DrawMariaSfxString(prim, &x, y, " PROG ");
    prim = DrawMariaSfxDec3(prim, &x, y, metadata->prog);
    prim = DrawMariaSfxString(prim, &x, y, " NOTE ");
    prim = DrawMariaSfxDec3(prim, &x, y, metadata->note);

    x = MARIA_SFX_MENU_X;
    y += 10;
    prim = DrawMariaSfxString(prim, &x, y, "VOL ");
    prim = DrawMariaSfxDec3(prim, &x, y, metadata->volume);
    prim = DrawMariaSfxString(prim, &x, y, " MODE ");
    prim = DrawMariaSfxDec3(prim, &x, y, metadata->mode);
    prim = DrawMariaSfxString(prim, &x, y, " TONE ");
    prim = DrawMariaSfxDec3(prim, &x, y, metadata->tone);

    x = MARIA_SFX_MENU_X;
    y += 10;
    prim = DrawMariaSfxString(prim, &x, y, "UNK6 ");
    prim = DrawMariaSfxDec3(prim, &x, y, metadata->unk6);

    x = MARIA_SFX_MENU_X;
    y += 10;
    prim = DrawMariaSfxString(prim, &x, y, "UP/DOWN SELECT X PLAY");

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

static bool OpenMariaSfxMenu(void) {
    s_MariaSfxMenuPrimIndex =
        g_api.AllocPrimitives(PRIM_SPRT, MARIA_SFX_MENU_PRIMS);
    if (s_MariaSfxMenuPrimIndex < 0) {
        return false;
    }
    return true;
}

static void UpdateMariaSfxMenu(void) {
    s32 mariaSfx;
    s32 psxSfx;
    Unkstruct_800BF554* metadata;
    u16 tapped = g_pads[0].tapped;

    if (tapped & PAD_UP) {
        s_MariaSfxIndex--;
        if (s_MariaSfxIndex < 0) {
            s_MariaSfxIndex = MARIA_SFX_COUNT - 1;
        }
    }
    if (tapped & PAD_DOWN) {
        s_MariaSfxIndex++;
        if (s_MariaSfxIndex >= MARIA_SFX_COUNT) {
            s_MariaSfxIndex = 0;
        }
    }

    mariaSfx = MARIA_SFX_FIRST + s_MariaSfxIndex;
    psxSfx = MARIA_PSX_SFX_FIRST + s_MariaSfxIndex;
    metadata = &g_SfxData[psxSfx - SFX_DATA_FIRST];

    if (tapped & PAD_CROSS) {
        MarPlaySfx(mariaSfx);
    }
    DrawMariaSfxMenu(mariaSfx, psxSfx, metadata);
}

void MarSoundTest(void) {
    if (s_MariaSfxMenuPrimIndex < 0 && !OpenMariaSfxMenu()) {
        return;
    }
    UpdateMariaSfxMenu();
}
#endif

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
    {0x05, 0x09, 0x1F, 0x17, 0xE0, 0xB0, 0x01E, 0x17F}, // CAT
    {0x0C, 0x07, 0x0F, 0x17, 0xD0, 0xC0, 0x01E, 0x17F}, // CARDINAL
    {0x05, 0x09, 0x1F, 0x17, 0xE0, 0xC8, 0x01E, 0x17F}, // TURTLE
    {0x0C, 0x09, 0x10, 0x17, 0x98, 0xD8, 0x01E, 0x17F}, // DOLL (dummy)
    {0x0C, 0x09, 0x10, 0x17, 0x98, 0xD8, 0x01E, 0x17F}, // DOLL
    {0x0C, 0x09, 0x10, 0x17, 0x98, 0xD8, 0x01E, 0x17F}, // DOLL (dummy)
    {0x0C, 0x09, 0x10, 0x17, 0x98, 0xD8, 0x01E, 0x17F}, // DOLL (dummy)
    {0x04, 0x00, 0x1F, 0x1F, 0xE0, 0xE0, 0x01E, 0x17F}, // DRAGON
    {0x0C, 0x09, 0x10, 0x17, 0x98, 0xD8, 0x01E, 0x17F}, // DOLL (dummy)
};
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

// On MARIA overlay, PL_W_NONE is used for the Doll Crash. We need to convert it
// back and forth to make it work in the overlay and in the HUD managed by DRA.
// * Bible -> Doll
// * Knife -> Cat
// * Vithubi -> Dragon
// * Axe -> Bird
// * Water -> Turtle
static int equipped_subweapon;
static inline void ConvertSubweaponRicToMaria() {
    switch (g_Status.subWeapon) {
    case SUBWPN_NONE:
        g_Status.subWeapon = PL_W_NONE;
        break;
    case SUBWPN_DAGGER:
        g_Status.subWeapon = PL_W_CAT;
        break;
    case SUBWPN_AXE:
        g_Status.subWeapon = PL_W_CARDINAL;
        break;
    case SUBWPN_HOLYWATER:
        g_Status.subWeapon = PL_W_TURTLE;
        break;
    case SUBWPN_BIBLE:
        g_Status.subWeapon = PL_W_NONE;
        break;
    case SUBWPN_VIBHUTI:
        g_Status.subWeapon = PL_W_DRAGON;
        break;
    default:
        // Re-use previous subweapon, and increase heart count by 1
        g_Status.subWeapon = equipped_subweapon;
        if (g_Status.hearts < g_Status.heartsMax) {
            g_Status.hearts++;
        }
        break;
    }
    equipped_subweapon = g_Status.subWeapon;
}
static inline void ConvertSubweaponMariaToRic() {
    switch (g_Status.subWeapon) {
    case PL_W_NONE:
        g_Status.subWeapon = SUBWPN_BIBLE;
        break;
    case PL_W_CAT:
        g_Status.subWeapon = SUBWPN_DAGGER;
        break;
    case PL_W_CARDINAL:
        g_Status.subWeapon = SUBWPN_AXE;
        break;
    case PL_W_TURTLE:
        g_Status.subWeapon = SUBWPN_HOLYWATER;
        break;
    case PL_W_DRAGON:
        g_Status.subWeapon = SUBWPN_VIBHUTI;
        break;
    }
}

int PadReadPSP() { return 0; }
int func_psp_090E4C58() { return 0; }
void func_psp_090E4C18() {}
void func_psp_090E4C68() {}
void func_800FE8F0() {}

void func_psp_091040A0(u_long** _gfxBank) {
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
    return -1;
}

void func_psp_0892667C(s32 paletteID, u16* paletteData) {
    int x = (paletteID & 15) * 16;
    int y = (paletteID >> 4) & 15;
    RECT rect = {x, 240 + y, 16, 1};
    memcpy(
        &g_Clut[(paletteID & 0x300) >> 8][(paletteID & 0xFF) * COLORS_PER_PAL],
        paletteData, PALETTE_LEN);
    LoadImage(&rect, (u_long*)paletteData);
}

// replace ric sound effects with maria's
#define MARIA_SFX_FIRST SFX_VO_MAR_8E6
#define MARIA_SFX_LAST SFX_VO_MAR_DEATH
#define MARIA_PSX_SFX_FIRST SFX_VO_RIC_ATTACK_A
#define SFX_DATA_FIRST 0x600
extern Unkstruct_800BF554 g_SfxData[];

static void PatchMariaSfxData(void) {
    Unkstruct_800BF554* dst = &g_SfxData[MARIA_PSX_SFX_FIRST - 0x600];
    s32 i;

    for (i = 0; i < 16; i++) {
        dst[i].vabid = 1;
        dst[i].prog = 1 + i / 8;
        dst[i].note = 60;
        dst[i].volume = i == 15 ? 124 : 127;
        dst[i].mode = 0;
        dst[i].tone = (i % 8) * 2;
        dst[i].unk6 = i == 15 ? 90 : 80;
    }
}

void PlaySfx(s32 sfx) { g_api.PlaySfx(sfx); }

void MarPlaySfx(s32 sfx) {
    if (sfx >= MARIA_SFX_FIRST && sfx <= MARIA_SFX_LAST) {
        sfx += MARIA_PSX_SFX_FIRST - MARIA_SFX_FIRST;
    }
    PlaySfx(sfx);
}

void func_psp_089285A0(s32 angle, MATRIX* out) {
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

s16 AllocPrimitives(PrimitiveType kind, s32 count) {
    return g_api.AllocPrimitives(kind, count);
}

void MARIA_Load();
void MarInit(s16 initParam);

static void MarPsxInit(u16 initParam) {
    static int isInitialized = 0;
    if (!isInitialized) {
        MARIA_Load();
        PatchHudSubweaponUV();
        PatchMariaSfxData();
        g_api.CalcDealDamageMaria = g_api.func_800FD664;
        g_api.CalcPlayerDamageMaria = g_api.CalcPlayerDamage;
        isInitialized = true;
    }

    // Call the actual init function
    MarInit(initParam);
}

void MarMain(void);
static void MarPsxMain() {
#ifdef MARIA_SFX_DEBUG
    MarSoundTest();
#else
    ConvertSubweaponRicToMaria();
    MarMain();
    ConvertSubweaponMariaToRic();
#endif
}

#include "gen/maria.h"
void MarUpdatePlayerEntities(void);
void MarGetPlayerSensor(Collider* col);
// needs to stay at the bottom for the struct to fall to 0x8013C000
PlayerOvl MARIA_override = {
    MarPsxMain,    MarPsxInit,    MarUpdatePlayerEntities, MarGetPlayerSensor,
    maria_sprites, maria_sprites, maria_sprites,           maria_sprites,
};
