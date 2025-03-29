// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/10BF0", func_psp_090ED570);

INCLUDE_ASM("dra_psp/psp/dra_psp/10BF0", func_psp_090ED658);

INCLUDE_ASM("dra_psp/psp/dra_psp/10BF0", func_psp_090ED818);

void MenuReverseCloakDraw(MenuContext* context) {
    const int StrX = 188;
    const int ImgW = 88;
    char** menuStr;
    
    menuStr= g_MenuStr;
    MenuDrawStr(menuStr[30], StrX, 48, context);
    menuStr= g_MenuStr;
    MenuDrawStr(menuStr[31], StrX, 64, context);
    func_800F5E68(context, g_Settings.isCloakLiningReversed, StrX - 2, 46, ImgW,
                  12, 4, 1);
}

void MenuSoundConfigDraw(void) {}

INCLUDE_ASM("dra_psp/psp/dra_psp/10BF0", func_psp_090ED9E0);

INCLUDE_ASM("dra_psp/psp/dra_psp/10BF0", func_psp_090EDA78);
