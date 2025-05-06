// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

static u16 maria_pal[] = {
#include "gen_maria_pal.h"
};

#include "gen_wpn_owl_spr.h"
static u16 wpn_owl_pal[] = {
#include "gen_wpn_owl_pal.h"
};
static u8 D_pspeu_092C7328[] = {
#include "gen_wpn_owl_gfx.h"
};

#include "gen_wpn_doll_spr.h"
static u16 wpn_doll_pal[] = {
#include "gen_wpn_doll_pal.h"
};
static u8 D_pspeu_092C8298[] = {
#include "gen_wpn_doll_gfx.h"
};

#include "gen_wpn_turtle_spr.h"
static u16 wpn_turtle_pal[] = {
#include "gen_wpn_turtle_pal.h"
};
static u16 wpn_turtle2_pal[] = {
#include "gen_wpn_turtle2_pal.h"
};
static u8 D_pspeu_092C93D0[] = {
#include "gen_wpn_turtle_gfx.h"
};

#include "gen_wpn_cardinal_spr.h"
static u16 wpn_cardinal_pal[] = {
#include "gen_wpn_cardinal_pal.h"
};
static u8 D_pspeu_092CB6A8[] = {
#include "gen_wpn_cardinal_gfx.h"
};

#include "gen_wpn_cat_spr.h"
static u16 wpn_cat_pal[] = {
#include "gen_wpn_cat_pal.h"
};
static u16 wpn_cat2_pal[] = {
#include "gen_wpn_cat2_pal.h"
};
static u8 D_pspeu_092CCF70[] = {
#include "gen_wpn_cat_gfx.h"
};

#include "gen_wpn_dragon_spr.h"
static u16 wpn_dragon_pal[] = {
#include "gen_wpn_dragon_pal.h"
};
static u16 wpn_dragon2_pal[] = {
#include "gen_wpn_dragon2_pal.h"
};
static u8 D_pspeu_092CE450[] = {
#include "gen_wpn_dragon_gfx.h"
};

#include "gen_maria.h"

static u8 D_pspeu_092DEE98[] = {
#include "gen_D_pspeu_092DEE98.h"
};

static u8 D_pspeu_092DFE38[] = {
#include "gen_D_pspeu_092DFE38.h"
};

static u8 D_pspeu_092E0C28[] = {
#include "gen_D_pspeu_092E0C28.h"
};

static u8 D_pspeu_092E1B80[] = {
#include "gen_D_pspeu_092E1B80.h"
};

static u8 D_pspeu_092E2E08[] = {
#include "gen_D_pspeu_092E2E08.h"
};

static u8 D_pspeu_092E4070[] = {
#include "gen_D_pspeu_092E4070.h"
};

static u16 D_pspeu_092E4F38[] = {
#include "gen_crash_cat_pal.h"
};

static u16 D_pspeu_092E4F58[] = {
#include "gen_crash_turtle_pal.h"
};

static u16 D_pspeu_092E4F78[] = {
#include "gen_crash_dragon_pal.h"
};

static u16 D_pspeu_092E4F98[] = {
#include "gen_crash_cardinal_pal.h"
};

static LangImg D_pspeu_092E5538 = {
    4, 0, {0x000, 0x180, 128, 128}, D_pspeu_092C7328, -1};
static LangImg D_pspeu_092E5550 = {
    4, 0, {0x000, 0x100, 128, 128}, D_pspeu_092C93D0, -1};
static LangImg D_pspeu_092E5568 = {
    4, 0, {0x000, 0x140, 128, 128}, D_pspeu_092CCF70, -1};
static LangImg D_pspeu_092E5580 = {
    4, 0, {0x000, 0x120, 128, 128}, D_pspeu_092CB6A8, -1};
static LangImg D_pspeu_092E5598 = {
    4, 0, {0x000, 0x160, 128, 128}, D_pspeu_092CE450, -1};
static LangImg D_pspeu_092E55B0 = {
    4, 0, {0x000, 0x1A0, 128, 128}, D_pspeu_092C8298, -1};
static LangImg D_pspeu_092E55C8 = {
    4, 0, {0x000, 0x1C0, 128, 128}, D_pspeu_092E0C28, -1};
static LangImg D_pspeu_092E55E0 = {
    4, 0, {0x100, 0x2C0, 128, 128}, D_pspeu_092DFE38, -1};
static LangImg D_pspeu_092E55F8 = {
    4, 0, {0x180, 0x3A0, 128, 128}, D_pspeu_092DEE98, -1};

static void func_pspeu_092BFFB8(s32 paletteID, u16* palette) {
    s32 i;

    for (i = 0; i < COLORS_PER_PAL; i++) {
        if (palette[i] != 0) {
            palette[i] |= 0x8000;
        }
    }
    func_892667C(paletteID, palette);
}

void func_pspeu_092C0040(void) {
    func_pspeu_092BFFB8(PAL_MARIA, maria_pal);
    func_pspeu_092BFFB8(PAL_WPN_OWL, wpn_owl_pal);
    func_pspeu_092BFFB8(PAL_WPN_TURTLE, wpn_turtle_pal);
    func_pspeu_092BFFB8(PAL_WPN_TURTLE_CRASH, wpn_turtle2_pal);
    func_pspeu_092BFFB8(PAL_WPN_CAT, wpn_cat_pal);
    func_pspeu_092BFFB8(PAL_WPN_CAT_CRASH, wpn_cat2_pal);
    func_pspeu_092BFFB8(PAL_WPN_CARDINAL, wpn_cardinal_pal);
    func_pspeu_092BFFB8(PAL_WPN_DRAGON, wpn_dragon_pal);
    func_pspeu_092BFFB8(PAL_WPN_DRAGON_CRASH, wpn_dragon2_pal);
    func_pspeu_092BFFB8(PAL_WPN_DOLL, wpn_doll_pal);
    func_pspeu_092BFFB8(PAL_UNK_811E, D_pspeu_092E4F38);
}

void func_pspeu_092C0138(s32 arg0) {
    switch (arg0) {
    case 1:
        D_pspeu_092E55C8.imgData = D_pspeu_092E2E08;
        func_pspeu_092BFFB8(PAL_UNK_811E, D_pspeu_092E4F98);
        break;
    case 2:
        D_pspeu_092E55C8.imgData = D_pspeu_092E4070;
        func_pspeu_092BFFB8(PAL_UNK_811E, D_pspeu_092E4F38);
        break;
    case 3:
        D_pspeu_092E55C8.imgData = D_pspeu_092E0C28;
        func_pspeu_092BFFB8(PAL_UNK_811E, D_pspeu_092E4F58);
        break;
    case 4:
        D_pspeu_092E55C8.imgData = D_pspeu_092E1B80;
        func_pspeu_092BFFB8(PAL_UNK_811E, D_pspeu_092E4F78);
        break;
    }
    func_91040A0(&D_pspeu_092E55C8);
}

void func_pspeu_092C0248(void) {
    func_91040A0(&D_pspeu_092E55E0);
    func_91040A0(&D_pspeu_092E55F8);
}

extern PlayerOvl D_pspeu_092C0400;
void MAR_Load(void) {
    memcpy(&g_PlOvl, &D_pspeu_092C0400, sizeof(PlayerOvl));
    memcpy(&g_PlOvlSpritesheet, maria_sprites, sizeof(maria_sprites));
    func_91040A0(&D_pspeu_092E5538);
    func_91040A0(&D_pspeu_092E5550);
    func_91040A0(&D_pspeu_092E5568);
    func_91040A0(&D_pspeu_092E5580);
    func_91040A0(&D_pspeu_092E5598);
    func_91040A0(&D_pspeu_092E55B0);

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
