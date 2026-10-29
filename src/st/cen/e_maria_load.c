// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../cen/cen.h"

static u16 maria_pal[] = {
#include "../cen/gen/maria_pal.h"
};

#include "../cen/gen/wpn_owl_spr.h"
static u16 wpn_owl_pal[] = {
#include "../cen/gen/wpn_owl_pal.h"
};
static u8 wpn_owl_gfx[] = {
#include "../cen/gen/wpn_owl_gfx.h"
};

#include "../cen/gen/wpn_doll_spr.h"
static u16 wpn_doll_pal[] = {
#include "../cen/gen/wpn_doll_pal.h"
};
static u8 wpn_doll_gfx[] = {
#include "../cen/gen/wpn_doll_gfx.h"
};

#include "../cen/gen/wpn_turtle_spr.h"
static u16 wpn_turtle_pal[] = {
#include "../cen/gen/wpn_turtle_pal.h"
};
static u16 wpn_turtle2_pal[] = {
#include "../cen/gen/wpn_turtle2_pal.h"
};
static u8 wpn_turtle_gfx[] = {
#include "../cen/gen/wpn_turtle_gfx.h"
};

#include "../cen/gen/wpn_cardinal_spr.h"
static u16 wpn_cardinal_pal[] = {
#include "../cen/gen/wpn_cardinal_pal.h"
};
static u8 wpn_cardinal_gfx[] = {
#include "../cen/gen/wpn_cardinal_gfx.h"
};

#include "../cen/gen/wpn_cat_spr.h"
static u16 wpn_cat_pal[] = {
#include "../cen/gen/wpn_cat_pal.h"
};
static u16 wpn_cat2_pal[] = {
#include "../cen/gen/wpn_cat2_pal.h"
};
static u8 wpn_cat_gfx[] = {
#include "../cen/gen/wpn_cat_gfx.h"
};

#include "../cen/gen/wpn_dragon_spr.h"
static u16 wpn_dragon_pal[] = {
#include "../cen/gen/wpn_dragon_pal.h"
};
static u16 wpn_dragon2_pal[] = {
#include "../cen/gen/wpn_dragon2_pal.h"
};
static u8 wpn_dragon_gfx[] = {
#include "../cen/gen/wpn_dragon_gfx.h"
};

static u8 crash_turtle_gfx[] = {
#include "../cen/gen/crash_turtle_gfx.h"
};
static u8 crash_dragon_gfx[] = {
#include "../cen/gen/crash_dragon_gfx.h"
};
static u8 crash_cardinal_gfx[] = {
#include "../cen/gen/crash_cardinal_gfx.h"
};
static u8 crash_cat_gfx[] = {
#include "../cen/gen/crash_cat_gfx.h"
};

static u16 crash_cat_pal[] = {
#include "../cen/gen/crash_cat_pal.h"
};
static u16 crash_turtle_pal[] = {
#include "../cen/gen/crash_turtle_pal.h"
};
static u16 crash_dragon_pal[] = {
#include "../cen/gen/crash_dragon_pal.h"
};
static u16 crash_cardinal_pal[] = {
#include "../cen/gen/crash_cardinal_pal.h"
};

// clang-format
static u_long* wpn_owl_img[] = {
    (u_long*)GFX_BANK_COMPRESSED,
#ifdef VERSION_PSP
    GFX_ENTRY(0x100, 0x180, 128, 128, wpn_owl_gfx),
#else
    GFX_ENTRY(0x180, 0x240, 128, 128, wpn_owl_gfx),
#endif
    GFX_TERMINATE(),
};
static u_long* wpn_turtle_img[] = {
    (u_long*)GFX_BANK_COMPRESSED,
#ifdef VERSION_PSP
    GFX_ENTRY(0x100, 0x100, 128, 128, wpn_turtle_gfx),
#else
    GFX_ENTRY(0x100, 0x2E0, 128, 128, wpn_turtle_gfx),
#endif
    GFX_TERMINATE(),
};
static u_long* wpn_cat_img[] = {
    (u_long*)GFX_BANK_COMPRESSED,
#ifdef VERSION_PSP
    GFX_ENTRY(0x100, 0x140, 128, 128, wpn_cat_gfx),
#else
    GFX_ENTRY(0x180, 0x2C0, 128, 128, wpn_cat_gfx),
#endif
    GFX_TERMINATE(),
};
static u_long* wpn_cardinal_img[] = {
    (u_long*)GFX_BANK_COMPRESSED,
#ifdef VERSION_PSP
    GFX_ENTRY(0x100, 0x120, 128, 128, wpn_cardinal_gfx),
#else
    GFX_ENTRY(0x100, 0x260, 128, 128, wpn_cardinal_gfx),
#endif
    GFX_TERMINATE(),
};
static u_long* wpn_dragon_img[] = {
    (u_long*)GFX_BANK_COMPRESSED,
#ifdef VERSION_PSP
    GFX_ENTRY(0x100, 0x160, 128, 128, wpn_dragon_gfx),
#else
    GFX_ENTRY(0x100, 0x240, 128, 128, wpn_dragon_gfx),
#endif
    GFX_TERMINATE(),
};
static u_long* wpn_doll_img[] = {
    (u_long*)GFX_BANK_COMPRESSED,
#ifdef VERSION_PSP
    GFX_ENTRY(0x100, 0x1A0, 128, 128, wpn_doll_gfx),
#else
    GFX_ENTRY(0x180, 0x260, 128, 128, wpn_doll_gfx),
#endif
    GFX_TERMINATE(),
};
static u_long* crash_img[] = {
    (u_long*)GFX_BANK_COMPRESSED,
#ifdef VERSION_PSP
    GFX_ENTRY(0x100, 0x1C0, 128, 128, crash_turtle_gfx),
#else
    GFX_ENTRY(0x100, 0x300, 128, 128, crash_turtle_gfx),
#endif
    GFX_TERMINATE(),
};

extern u_long* crash_img[];
extern s16 D_pspeu_0927E218[];
extern s16 D_pspeu_0927E2F8[];
extern s16 D_pspeu_0927E3B0[];

static void LoadPatchedPalette(s32 paletteID, u16* palette) {
    s32 i;

    for (i = 0; i < COLORS_PER_PAL; i++) {
        if (palette[i] != 0) {
            palette[i] |= 0x8000;
        }
    }
    func_psp_0892667C(paletteID, palette);
}

// MarLoadPalettes
void MarLoadPalettes(void) {
    LoadPatchedPalette(PAL_MARIA, maria_pal);
    LoadPatchedPalette(PAL_WPN_OWL, wpn_owl_pal);
    LoadPatchedPalette(PAL_WPN_TURTLE, wpn_turtle_pal);
    LoadPatchedPalette(PAL_WPN_TURTLE_CRASH, wpn_turtle2_pal);
    LoadPatchedPalette(PAL_WPN_CAT, wpn_cat_pal);
    LoadPatchedPalette(PAL_WPN_CAT_CRASH, wpn_cat2_pal);
    LoadPatchedPalette(PAL_WPN_CARDINAL, wpn_cardinal_pal);
    LoadPatchedPalette(PAL_WPN_DRAGON, wpn_dragon_pal);
    LoadPatchedPalette(PAL_WPN_DRAGON_CRASH, wpn_dragon2_pal);
    LoadPatchedPalette(PAL_WPN_DOLL, wpn_doll_pal);
    LoadPatchedPalette(PAL_CRASH, crash_cat_pal);
}

void LoadCrashSummonResouces(s32 crashId) {
    switch (crashId) {
    case PL_W_CARDINAL:
        crash_img[3] = (u_long*)crash_cardinal_gfx;
        LoadPatchedPalette(PAL_CRASH, crash_cardinal_pal);
        break;
    case PL_W_CAT:
        crash_img[3] = (u_long*)crash_cat_gfx;
        LoadPatchedPalette(PAL_CRASH, crash_cat_pal);
        break;
    case PL_W_TURTLE:
        crash_img[3] = (u_long*)crash_turtle_gfx;
        LoadPatchedPalette(PAL_CRASH, crash_turtle_pal);
        break;
    case PL_W_DRAGON:
        crash_img[3] = (u_long*)crash_dragon_gfx;
        LoadPatchedPalette(PAL_CRASH, crash_dragon_pal);
        break;
    }
    func_psp_091040A0(crash_img);
}

void MarLoadGraphics(void) {}

void MARIA_Load(void) {
    func_psp_091040A0(wpn_owl_img);
    func_psp_091040A0(wpn_turtle_img);
    func_psp_091040A0(wpn_cat_img);
    func_psp_091040A0(wpn_cardinal_img);
    func_psp_091040A0(wpn_dragon_img);
    func_psp_091040A0(wpn_doll_img);

    if (((SpriteParts*)wpn_cat_spr_6)->parts[6].offsetx == -48) {
        ((SpriteParts*)wpn_cat_spr_6)->parts[6].offsetx--;
    }
    if (((SpriteParts*)wpn_cat_spr_7)->parts[3].offsetx == -48) {
        ((SpriteParts*)wpn_cat_spr_7)->parts[3].offsetx--;
    }
    if (((SpriteParts*)wpn_cat_spr_8)->parts[3].offsetx == -49) {
        ((SpriteParts*)wpn_cat_spr_8)->parts[3].offsetx--;
    }
}

void LoadMariaImage(void) { LoadPatchedPalette(PAL_MARIA, maria_pal); }

void LoadOwlImage(void) {
    LoadPatchedPalette(PAL_WPN_OWL, wpn_owl_pal);
    func_psp_091040A0(wpn_owl_img);
}

void LoadTurtleImage(void) {
    LoadPatchedPalette(PAL_WPN_TURTLE, wpn_turtle_pal);
    func_psp_091040A0(wpn_turtle_img);
}

void LoadCatImage(void) {
    LoadPatchedPalette(PAL_WPN_CAT, wpn_cat_pal);
    LoadPatchedPalette(PAL_WPN_CAT_CRASH, wpn_cat2_pal);
    func_psp_091040A0(wpn_cat_img);
}

void LoadCardinalImage(void) {
    LoadPatchedPalette(PAL_WPN_CARDINAL, wpn_cardinal_pal);
    func_psp_091040A0(wpn_cardinal_img);
}

void LoadDragonImage(void) {
    LoadPatchedPalette(PAL_WPN_DRAGON, wpn_dragon_pal);
    LoadPatchedPalette(PAL_WPN_DRAGON_CRASH, wpn_dragon2_pal);
    func_psp_091040A0(wpn_dragon_img);
}

void LoadDollImage(void) {
    LoadPatchedPalette(PAL_WPN_DOLL, wpn_doll_pal);
    func_psp_091040A0(wpn_doll_img);
}
