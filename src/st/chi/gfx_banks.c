/*
 * File: gfx_banks.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

#include "chi.h"

// D_80180298
static u_long* GfxBank_Null[] = {
    GFX_BANK_NONE,
    GFX_ENTRY(0, 0, 0, 0, NULL),
    GFX_TERMINATE(),
};

extern u8 D_80189B38[];
extern u8 D_80182508[];

// D_801802AC
static u_long* GfxBank_StageName[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x40, 0x80, 0x80, D_80189B38), // EN Stage Name
    GFX_ENTRY(0x100, 0x60, 0x80, 0x80, D_80182508), // JP Stage Name (Large)
    GFX_TERMINATE(),
};

extern u8 D_80182A60[];

// D_801802CC
static u_long* GfxBank_Gremlin1[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x80, 0x80, 0x80, D_80182A60), // Gremlin
    GFX_TERMINATE(),
};

// D_801802E0
static u_long* GfxBank_Gremlin2[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x80, 0x80, 0x80, D_80182A60), // Gremlin
    GFX_TERMINATE(),
};

extern u8 D_80183480[];
extern u8 D_801841F8[];
extern u8 D_80185BA0[];
extern u8 D_80186B1C[];
extern u8 D_80184DBC[];

// D_801802F4
static u_long* GfxBank_SalemWitch[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x80, 0x80, 0x80, D_80183480),     // Body/Arm
    GFX_ENTRY(0x100, 0xA0, 0x80, 0x80, D_801841F8),     // Shine/Curse/Body
    GFX_ENTRY(0x180, 0x80, 0x80, 0x80, D_80185BA0),     // Explosion
    GFX_ENTRY(0x180, 0xA0, 0x80, 0x80, D_80186B1C),     // Shine
    GFX_ENTRY(0x100, 0x1C0, 0x80, 0x80, D_80184DBC),    // Fire
    GFX_TERMINATE(),
};

extern u8 D_801870F8[];
extern u8 D_80187E84[];
extern u8 D_80188A10[];

// D_80180338
static u_long* GfxBank_AllWeeds[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0xC0, 0x80, 0x80, D_801870F8),     // Thornweed/Corpseweed
    GFX_ENTRY(0x100, 0x100, 0x80, 0x80, D_80187E84),    // Venus Weed Flower/Stem/Woman/Projectiles
    GFX_ENTRY(0x100, 0x120, 0x80, 0x80, D_80188A10),    // Venus Weed Woman
    GFX_TERMINATE(),
};

// D_80180364
u_long* OVL_EXPORT(g_EntityGfxs)[] = {
    GfxBank_Null,
    GfxBank_StageName,
    GfxBank_Gremlin1,
    GfxBank_SalemWitch,
    GfxBank_AllWeeds,
    GfxBank_Gremlin2,
    GfxBank_Null,
    GfxBank_Null,
    GfxBank_Null,
    GfxBank_Null,
    GfxBank_Null,
    GfxBank_Null,
    GfxBank_Null,
    GfxBank_Null,
    GfxBank_Null,
    GfxBank_Null,
    GfxBank_Null,
    GfxBank_Null,
    GfxBank_Null,
    GfxBank_Null,
};