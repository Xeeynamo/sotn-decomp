// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/F4D0", func_psp_090EBE50);

u8 func_800F548C(u8 arg0) {
    if (arg0 & 0x100) {
        return func_800F548C(arg0 & 0xFF);
    }
    if (arg0 & 0x80) {
        return func_800F548C((arg0 & 0x7F) + 3);
    }
    return arg0 << 4;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/F4D0", func_psp_090EBF50);

INCLUDE_ASM("dra_psp/psp/dra_psp/F4D0", func_psp_090EBFA8);

INCLUDE_ASM("dra_psp/psp/dra_psp/F4D0", func_psp_090EC0C0);

INCLUDE_ASM("dra_psp/psp/dra_psp/F4D0", func_psp_090EC248);

INCLUDE_ASM("dra_psp/psp/dra_psp/F4D0", func_psp_090EC380);

INCLUDE_ASM("dra_psp/psp/dra_psp/F4D0", func_psp_090EC518);

INCLUDE_ASM("dra_psp/psp/dra_psp/F4D0", func_psp_090EC568);

INCLUDE_ASM("dra_psp/psp/dra_psp/F4D0", MenuDrawSprite);

INCLUDE_ASM("dra_psp/psp/dra_psp/F4D0", MenuDrawRect);

INCLUDE_ASM("dra_psp/psp/dra_psp/F4D0", func_psp_090EC968);


extern s16 g_RelicMenuFadeTimer;
void DrawRelicsMenu(MenuContext* ctx) {
    s32 ctx_h;
    s32 switchFadeLevel;
    s32 i;
    s32 spriteX;
    s32 spriteY;
    s32 baseY;
    s32 var_s3;
    s32 u_OnOff;
    u8* relic;

    ctx_h = ctx->h;
    relic = &g_Status.relics[RELIC_SOUL_OF_BAT];

    for (i = 0; i < 30; i++, relic++) {
#define INDEXER i
        spriteX = (i & 1) * 0xB0;
        spriteY = ctx_h + ((INDEXER / 2) * 0x13 + 0x22);
        if (*relic & RELIC_FLAG_FOUND) {
            if (spriteY < 0) {
                continue;
            }
            if (spriteY >= 193) {
                continue;
            }
            if ((i & 2) == 0) {
                MenuDrawSprite(
                    ctx, spriteX + 0x38, spriteY, 0x78, 0x10, (i & 1) * 0x78,
                    func_800F548C(i/4 + 0x80), 0x1A1, 6, 1, 0, 0);
            } else {
                MenuDrawSprite(
                    ctx, spriteX + 0x38, spriteY, 0x78, 0x10, (i & 1) * 0x78,
                    func_800F548C(i/4 + 0x103), 0x1A1, 7, 1, 0, 0);
            }
        }
        // Determine the U value for the texture to use for the switch
        if(*relic & RELIC_FLAG_ACTIVE){
            u_OnOff = 0;
        } else {
            u_OnOff = 0x30;
        }
        switchFadeLevel = 0;
        if (INDEXER == g_MenuNavigation.cursorRelic) {
            // This routine handles the fade in/fade out of the ON/OFF switch
            // when hovering
            if (++g_RelicMenuFadeTimer >= 0x48) {
                g_RelicMenuFadeTimer = 0;
            }
            if (g_RelicMenuFadeTimer < 0x24) {
                // Fade up
                switchFadeLevel = g_RelicMenuFadeTimer / 6;
            } else {
                // Fade down
                switchFadeLevel = 6 - ((g_RelicMenuFadeTimer - 0x24) / 6);
            }
        }
        MenuDrawSprite(ctx, spriteX + 8, spriteY, 0x2F, 0xF, u_OnOff, 0x70,
                       switchFadeLevel + 0x1C8, 0x1F,
                       INDEXER == g_MenuNavigation.cursorRelic, 0x40, 0);
    }
    spriteY = ctx_h + ((g_MenuNavigation.cursorRelic / 2) * 0x13 + 0x22) ;
    MenuDrawRect(ctx, ((g_MenuNavigation.cursorRelic & 1) * 0xB0) + 8,
                 spriteY -1, 0xA8, 0x12, 0x60, 0, 0);
#undef INDEXER
}
