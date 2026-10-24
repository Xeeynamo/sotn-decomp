// SPDX-License-Identifier: AGPL-3.0-or-later
#include <psyz/module.h>
#include <game.h>
#include <string.h>
#include "../stages/overlay.h"
#include "../boss/rbo5/rbo5.h"

extern AbbreviatedOverlay2 g_BossOverlay;
extern PfnEntityUpdate EntityUpdates[];
extern LayoutEntity* entityLayoutHorizontal[];
extern LayoutEntity* entityLayoutVertical[];
extern PfnEntityUpdate* PfnEntityUpdates;
extern LayoutEntity** g_pStObjLayoutHorizontal;
extern LayoutEntity** g_pStObjLayoutVertical;

// On Windows, compiling an overlay as a DLL will fail to link global variables
// that belong to the main executable, in this case is g_clut.
// The fix is to create a copy of src/boss/rbo5/palette_def.c, and to init it
// at runtime.
extern s16* D_us_801AC360[0x1F0]; // from stage_data.c
u_long* cluts[4];                 // used by header.c
static void InitPaletteDef(void) {
    static u_long* D_us_80180094[] = {
        MAKE_PAL_OP(PAL_BULK_COPY, 0),
        PAL_BULK(0x2000, D_us_801AC360),
        PAL_TERMINATE(),
    };
    static u_long* D_us_801800A8[] = {
        PAL_COPY_INFO(),
        PAL_COPY_DATA_(0x20F0, NULL, 16),
    };
    static u_long* D_us_801800B8[] = {
        MAKE_PAL_OP(PAL_UNK_OP2, 2),
        PAL_COPY_DATA_(0x20F0, NULL, 16),
        PAL_TERMINATE(),
    };
    static u_long* D_us_801800CC[] = {
        MAKE_PAL_OP(PAL_UNK_OP2, 2),
        PAL_COPY_DATA_(0x20F0, NULL, 16),
        PAL_TERMINATE(),
    };
    D_us_801800A8[3] = (u_long*)&g_Clut[2][0xA0];
    D_us_801800B8[3] = (u_long*)&g_Clut[2][0xC0];
    D_us_801800CC[3] = (u_long*)&g_Clut[2][0];
    cluts[0] = (u_long*)D_us_80180094;
    cluts[1] = (u_long*)D_us_801800B8;
    cluts[2] = (u_long*)D_us_801800CC;
    cluts[3] = (u_long*)D_us_801800A8;
}

void Psyz_ModuleStart(void* param) {
    Overlay* o = param;

    InitPaletteDef();
    memcpy(o, &g_BossOverlay, sizeof(AbbreviatedOverlay2));
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = entityLayoutHorizontal;
    g_pStObjLayoutVertical = entityLayoutVertical;
}

void Psyz_ModuleStop(void) {}
