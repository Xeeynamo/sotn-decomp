// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: en_stage_name.c
 * Overlay: CHI
 * Description: ENTITY - Stage name popup
 */

#include "chi.h"

#ifdef VERSION_PSP
#define STAGE_NAME_LOAD_GFX
#define NUM_PRIMS 181
#define PRIM_X0_VAL 8
#define PRIM_X1_VAL 0xF8

extern u32 D_91CE570; // Defined in global address space

static SVECTOR D_psp_09254DD8 = {-112, 0, -20};
static SVECTOR D_psp_09254DE0 = {112, 0, -20};
static SVECTOR D_psp_09254DE8 = {0, 0, FLT(1)};
static MATRIX D_psp_09254DF0 = {
    {{0, FLT(-0.5), FLT(0.5)}, {0, 0, FLT(1)}, {0, FLT(0.5), FLT(0.5)}},
    {0, 0, 0}};

static u8 stage_name_en[] = {
#include "gen/stage_name_en.h"
};
static u8 stage_name_it[] = {
#include "gen/stage_name_it.h"
};
static u8 stage_name_sp[] = {
#include "gen/stage_name_sp.h"
};
static u8 stage_name_ge[] = {
#include "gen/stage_name_ge.h"
};
static u8 stage_name_fr[] = {
#include "gen/stage_name_fr.h"
};
extern s32 g_UserLanguage; // Defined in global address space

static u_long* gfxBank[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(256, 64, 128, 128, stage_name_en),
    GFX_TERMINATE(),
};

static u8* stage_name_gfx[] = {
    stage_name_en, stage_name_fr, stage_name_sp, stage_name_ge, stage_name_it};

static void LoadStageNameGraphics(void) {
    gfxBank[3] = (u_long*)stage_name_gfx[g_UserLanguage - 1];
    func_91040A0(gfxBank);
}
#include "../e_stage_name_alternate.h"
#else
// func_801AD0EC: StageNamePopupHelper
// func_801AD2BC: [E_STAGE_NAME_POPUP] EntityStageNamePopup
#include "../e_stage_name.h"
#endif
