/*
 * File: d_298.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

#include "chi.h"

// D_80180298
static u_long* GfxBank_Null[] = {
    GFX_BANK_NONE,
    GFX_ENTRY(0, 0, 0, 0, 0),
    GFX_TERMINATE(),
};

// D_801802AC
static u_long* GfxBank_StageName[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(256, 64, 128, 128, (void*)0x80189B38),
    GFX_ENTRY(256, 96, 128, 128, (void*)0x80182508),
    GFX_TERMINATE(),
};

// D_801802CC
static void* GfxBank_Gremlin1[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(256, 128, 128, 128, (void*)0x80182A60),
    GFX_TERMINATE(),
};

// D_801802E0
static void* GfxBank_Gremlin2[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(256, 128, 128, 128, (void*)0x80182A60),
    GFX_TERMINATE(),
};

// D_801802F4
static void* GfxBank_SalemWitch[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(256, 128, 128, 128, (void*)0x80183480),
    GFX_ENTRY(256, 160, 128, 128, (void*)0x801841F8),
    GFX_ENTRY(384, 128, 128, 128, (void*)0x80185BA0),
    GFX_ENTRY(384, 160, 128, 128, (void*)0x80186B1C),
    GFX_ENTRY(256, 448, 128, 128, (void*)0x80184DBC),
    GFX_TERMINATE(),
};

// D_80180338
static void* GfxBank_AllWeeds[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(256, 192, 128, 128, (void*)0x801870F8),
    GFX_ENTRY(256, 256, 128, 128, (void*)0x80187E84),
    GFX_ENTRY(256, 288, 128, 128, (void*)0x80188A10),
    GFX_TERMINATE(),
};

// D_80180364
GfxBank* OVL_EXPORT(g_EntityGfxs)[] = {
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_StageName,
    (GfxBank*)GfxBank_Gremlin1,
    (GfxBank*)GfxBank_SalemWitch,
    (GfxBank*)GfxBank_AllWeeds,
    (GfxBank*)GfxBank_Gremlin2,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
    (GfxBank*)GfxBank_Null,
};