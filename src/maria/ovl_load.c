// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

static u16 maria_pal[] = {
#include "gen_maria_pal.h"
};

#include "gen_wpn_owl_spr.h"
static u16 wpn_owl_pal[] = {
#include "gen_wpn_owl_pal.h"
};
static u8 wpn_owl_gfx[] = {
#include "gen_wpn_owl_gfx.h"
};

#include "gen_wpn_doll_spr.h"
static u16 wpn_doll_pal[] = {
#include "gen_wpn_doll_pal.h"
};
static u8 wpn_doll_gfx[] = {
#include "gen_wpn_doll_gfx.h"
};

#include "gen_wpn_turtle_spr.h"
static u16 wpn_turtle_pal[] = {
#include "gen_wpn_turtle_pal.h"
};
static u16 wpn_turtle2_pal[] = {
#include "gen_wpn_turtle2_pal.h"
};
static u8 wpn_turtle_gfx[] = {
#include "gen_wpn_turtle_gfx.h"
};

#include "gen_wpn_cardinal_spr.h"
static u16 wpn_cardinal_pal[] = {
#include "gen_wpn_cardinal_pal.h"
};
static u8 wpn_cardinal_gfx[] = {
#include "gen_wpn_cardinal_gfx.h"
};

#include "gen_wpn_cat_spr.h"
static u16 wpn_cat_pal[] = {
#include "gen_wpn_cat_pal.h"
};
static u16 wpn_cat2_pal[] = {
#include "gen_wpn_cat2_pal.h"
};
static u8 wpn_cat_gfx[] = {
#include "gen_wpn_cat_gfx.h"
};

#include "gen_wpn_dragon_spr.h"
static u16 wpn_dragon_pal[] = {
#include "gen_wpn_dragon_pal.h"
};
static u16 wpn_dragon2_pal[] = {
#include "gen_wpn_dragon2_pal.h"
};
static u8 wpn_dragon_gfx[] = {
#include "gen_wpn_dragon_gfx.h"
};

#include "gen_maria.h"

static u8 items_gfx[] = {
#include "gen_items_gfx.h"
};

static u8 hud_en[] = {
#include "gen_hud_en.h"
};

static u8 crash_turtle_gfx[] = {
#include "gen_crash_turtle_gfx.h"
};
static u8 crash_dragon_gfx[] = {
#include "gen_crash_dragon_gfx.h"
};
static u8 crash_cardinal_gfx[] = {
#include "gen_crash_cardinal_gfx.h"
};
static u8 crash_cat_gfx[] = {
#include "gen_crash_cat_gfx.h"
};

static u16 crash_cat_pal[] = {
#include "gen_crash_cat_pal.h"
};
static u16 crash_turtle_pal[] = {
#include "gen_crash_turtle_pal.h"
};
static u16 crash_dragon_pal[] = {
#include "gen_crash_dragon_pal.h"
};
static u16 crash_cardinal_pal[] = {
#include "gen_crash_cardinal_pal.h"
};

static LangImg wpn_owl_img = {4, 0, {0x000, 0x180, 128, 128}, wpn_owl_gfx, -1};
static LangImg wpn_turtle_img = {
    4, 0, {0x000, 0x100, 128, 128}, wpn_turtle_gfx, -1};
static LangImg wpn_cat_img = {4, 0, {0x000, 0x140, 128, 128}, wpn_cat_gfx, -1};
static LangImg wpn_cardinal_img = {
    4, 0, {0x000, 0x120, 128, 128}, wpn_cardinal_gfx, -1};
static LangImg wpn_dragon_img = {
    4, 0, {0x000, 0x160, 128, 128}, wpn_dragon_gfx, -1};
static LangImg wpn_doll_img = {
    4, 0, {0x000, 0x1A0, 128, 128}, wpn_doll_gfx, -1};
static LangImg crash_img = {
    4, 0, {0x000, 0x1C0, 128, 128}, crash_turtle_gfx, -1};
static LangImg hud_img = {4, 0, {0x100, 0x2C0, 128, 128}, hud_en, -1};
static LangImg items_img = {4, 0, {0x180, 0x3A0, 128, 128}, items_gfx, -1};

static void LoadPatchedPalette(s32 paletteID, u16* palette) {
    s32 i;

    for (i = 0; i < COLORS_PER_PAL; i++) {
        if (palette[i] != 0) {
            palette[i] |= 0x8000;
        }
    }
    func_892667C(paletteID, palette);
}

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

void func_pspeu_092C0138(s32 arg0) {
    switch (arg0) {
    case 1:
        crash_img.imgData = crash_cardinal_gfx;
        LoadPatchedPalette(PAL_CRASH, crash_cardinal_pal);
        break;
    case 2:
        crash_img.imgData = crash_cat_gfx;
        LoadPatchedPalette(PAL_CRASH, crash_cat_pal);
        break;
    case 3:
        crash_img.imgData = crash_turtle_gfx;
        LoadPatchedPalette(PAL_CRASH, crash_turtle_pal);
        break;
    case 4:
        crash_img.imgData = crash_dragon_gfx;
        LoadPatchedPalette(PAL_CRASH, crash_dragon_pal);
        break;
    }
    func_91040A0(&crash_img);
}

void MarLoadGraphics(void) {
    func_91040A0(&hud_img);
    func_91040A0(&items_img);
}

extern PlayerOvl D_pspeu_092C0400;
void MAR_Load(void) {
    memcpy(&g_PlOvl, &D_pspeu_092C0400, sizeof(PlayerOvl));
    memcpy(&g_PlOvlSpritesheet, maria_sprites, sizeof(maria_sprites));
    func_91040A0(&wpn_owl_img);
    func_91040A0(&wpn_turtle_img);
    func_91040A0(&wpn_cat_img);
    func_91040A0(&wpn_cardinal_img);
    func_91040A0(&wpn_dragon_img);
    func_91040A0(&wpn_doll_img);

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
