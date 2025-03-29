// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/10990", func_psp_090ED310);

extern s32 D_psp_0914A3B8;
extern s32 D_psp_0914A3D0;
extern s32 D_psp_0914A3C8;
extern s32 D_psp_0914A3D8;
extern s32 D_psp_0914A3C0;

extern u8* g_ChRgb[];

extern u8* func_psp_090EAF08(void*, void*, void*, void*, void*);

void MenuWindowColorsDraw(MenuContext* context) {
    s32 x = 188;
    s32 y;
    s32 i;

    *g_ChRgb = func_psp_090EAF08(&D_psp_0914A3B8, &D_psp_0914A3D0, &D_psp_0914A3C8, &D_psp_0914A3D8, &D_psp_0914A3C0);

    for (i = 0; i < 3; i++) {
        MenuDrawChar((*g_ChRgb)[i], x + 32, (i * 12) + 80, context);
        MenuDrawInt(g_Settings.windowColors[i], x + 72, 80 + i * 12, context);
    }
    func_800F5E68(
        context, g_MenuNavigation.cursorWindowColors, x - 2, 78, 120, 12, 0, 1);
}