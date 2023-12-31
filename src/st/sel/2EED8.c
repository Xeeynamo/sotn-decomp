#include "sel.h"

typedef enum {
    Tips_Generic,
    Tips_Input,
    Tips_YesNo,
    Tips_Confirm,
    Tips_MenuNavigation,
    Tips_NoYes,
} NavigationTips;

extern const char D_801A7620[];

extern s32 D_801BAF0C;
extern s32 D_801BAFC8;
extern s32 D_801BAFCC;

void Update(void) {
    s32 temp_v0;
    s32 var_a0_2;
    s32 i;
    s32 port;
    s32 slot;
    s32 icon;

    func_801B1F34();
    switch (D_8003C9A4) {
    case 0:
        func_801B18F4();
        func_801B1B88();
        D_8003C9A4--;
        break;
    case -1:
        g_api.PlaySfx(MU_PRAYER);
        g_GameTimer = 0;
        D_801BAF08 = 0;
        func_801B2D6C();
        g_api.func_800EA5E4(0);
        g_api.func_800EA5E4(0x8000);
        g_api.func_800EA5E4(0x8001);
        g_api.func_800EA5E4(0x8002);
        g_api.func_800EA5E4(0x8003);
        g_api.func_800EA5E4(0x8006);
        SetupFileChoose();
        func_801ACC7C();
        InitMainMenuGraphics();
        func_801ACF7C();
        func_801AECA0();
        func_801B1F4C(9);
        func_801AD490();
        D_8003C9A4 += 2;
        break;
    case 1:
        func_801AD590();
        func_801AD490();
        if (func_801ACDFC() != 0) {
            D_8003C9A4++;
        }
        break;
    case 2:
        func_801AD590();
        func_801AD490();
        if (g_pads[0].tapped & PAD_CROSS) {
            switch (D_801D6B0C) {
            case 0:
                g_api.PlaySfx(0x633);
                D_8003C9A4 = 0x10;
                break;
            case 1:
                g_api.PlaySfx(0x633);
                D_8003C9A4 = 0x30;
                break;
            case 2:
                g_api.PlaySfx(0x633);
                D_8003C9A4 = 0x90;
                break;
            case 3:
                g_api.PlaySfx(0x633);
                D_8003C9A4 = 0x50;
                break;
            case 4:
                g_api.PlaySfx(0x633);
                D_8003C9A4 = 0x70;
                break;
            default:
                g_api.PlaySfx(0x686);
                break;
            }
        }
        break;
    case 3:
        func_801AD590();
        func_801AD490();
        if (func_801ACEC0()) {
            SetGameState(Game_Title);
        }
        break;
    case 16:
        STRCPY(g_InputSaveName, "        ");
        func_801AEA8C(0);
        D_8003C9A4++;
        // fallthrough
    case 17:
        for (i = 0; i < 8; i++) {
            if (g_InputSaveName[i] != ' ') {
                break;
            }
        }
        if (!(g_pads[0].tapped & PAD_SELECT) &&
            (!(g_pads[0].tapped & PAD_TRIANGLE) || i != 8 ||
             g_InputCursorPos != 0)) {
            UpdateNameEntry();
            func_801AD78C();
            if (g_pads[0].tapped & PAD_START) {
                g_api.PlaySfx(0x633);
                func_801AD66C();
                if (g_PlayableCharacter == 0) {
                    g_StageId = STAGE_ST0;
                } else {
                    g_StageId = STAGE_NO3;
                }
                D_8003C730 = 0;
                D_8006C378 = -1;
                if (D_801BAF10) {
                    D_80097924 = -1;
                } else {
                    D_80097924 = D_801D6B04 / 15;
                }
                g_api.PlaySfx(0x80);
                D_8003C9A4++;
            }
        } else {
            D_8003C9A4 = 0x30;
        }
        break;
    case 18:
        func_801AD78C();
        if (func_801ACEC0()) {
            func_801B18F4();
            func_801B19F4();
            func_801B1DA8();
            func_801B2D1C();
            g_api.func_800EA538(0);
            if (g_PlayableCharacter == 0) {
                SetGameState(Game_VideoPlayback);
            } else {
                g_GameStep++;
            }
        }
        break;
    case 48:
        SelectMainMenuOption(MAIN_MENU_CURSOR_FILE_SELECT);
        func_801B2608("Checking Memory Card．", 4);
        func_801B2608("Do not remove Memory Card．", 5);
        func_801B3120();
        D_8003C9A4++;
        // fallthrough
    case 49:
        func_801ADF94(0x80, 0);
        D_800978C4 = 0;
        if (func_801B3164()) {
            D_800978C4 = 1;
            D_8003C9A4++;
            CheckIfMemcardsCanBeUsed();
            if (g_SaveSummary[0].padding == -2 ||
                g_SaveSummary[1].padding == -2) {
                D_801BAFC8 = 0x30;
                D_801BAFCC = 0x32;
                D_8003C9A4 = 0x200;
            }
        }
        break;
    case 50:
        if (g_IsTimeAttackUnlocked == 0) {
            D_801BAF0C = 0xFF;
        } else {
            D_801BAF0C = 0x2FF;
        }
        if (g_SaveSummary[0].padding < 0) {
            g_MemCardSelectorX = (g_MemCardSelectorX % 3) + 3;
        }
        if (g_SaveSummary[1].padding < 0) {
            g_MemCardSelectorX %= 3;
        }
        if (D_801BAF10) {
            func_801B2608("You won’t be able to save", 4);
            func_801B2608("your game． Is that OK？", 5);
            func_801ADF94(0x83, 0);
            DrawNavigationTips(Tips_YesNo);
            D_8003C9A4 = 0x40;
        } else {
            DrawNavigationTips(Tips_Generic);
            func_801ADF94(1, 0);
            func_801B25D4(D_801A7620, 4);
            func_801B25D4(D_801A7620, 5);
            D_8003C9A4++;
        }
        break;
    case 64:
        func_801ADF94(0x81, 0);
        DrawNavigationTips(Tips_YesNo);
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            func_801AE9A8();
            func_801AD490();
            D_8003C9A4 = 2;
        } else if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(0x633);
            D_8003C9A4 = 0x10;
        }
        break;
    case 65:
        func_801ADF94(0x83, 0);
        DrawNavigationTips(Tips_YesNo);
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            D_801BAF0C = 0xFF;
            DrawNavigationTips(Tips_Generic);
            func_801B2608("Select file to be loaded．", 4);
            func_801B2608("", 5);
            D_8003C9A4 = 0x33;
        } else if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(0x633);
            D_8003C9A4 = 0x10;
        }
        break;
    case 51:
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            func_801AE9A8();
            func_801AD490();
            D_8003C9A4 = 2;
            break;
        }

        UpdateFileSelect();
        func_801ADF94(1, 0);
        if (++D_801BAF0C == 0x100) {
            func_801B2608("Select file to be loaded．", 4);
            func_801B2608("", 5);
        }
        if (D_801BAF0C == 0x200) {
            if (D_801BAF14 != 0) {
                func_801B2608("Press Start button", 4);
                func_801B2608("to begin new game．", 5);
            } else {
                func_801B2608("Select New Game", 4);
                func_801B2608("to start from beginning．", 5);
            }
            if (g_IsTimeAttackUnlocked == 0) {
                D_801BAF0C = 0;
            }
        }
        if (D_801BAF0C == 0x300) {
            func_801B2608("Input ””RICHTER”” to play", 4);
            func_801B2608("as Richter Belmont．", 5);
            D_801BAF0C = 0;
        }
        if ((g_pads[0].tapped & PAD_START) && D_801BAF14 != 0) {
            g_api.PlaySfx(0x633);
            func_801B2608("You won’t be able to save", 4);
            func_801B2608("your game． Is that OK？", 5);
            func_801ADF94(0x81, 0);
            DrawNavigationTips(Tips_YesNo);
            D_8003C9A4 = 0x41;
        } else if (g_pads[0].tapped & PAD_CROSS) {
            port = D_801D6B04 / 15;
            slot = D_801D6B04 % 15;
            icon = g_SaveSummary[port].icon[slot];
            if (icon >= 0) {
                g_api.PlaySfx(0x633);
                D_8003C9A4 = 0x100;
            } else if (icon == -3) {
                g_api.PlaySfx(0x633);
                D_8003C9A4 = 0x10;
            } else {
                g_api.PlaySfx(0x686);
            }
        }
        break;
    case 144:
        SelectMainMenuOption(MAIN_MENU_CURSOR_FILE_DELETE);
        func_801ACBE4(GFX_UNK_15, 0);
        func_801B2608("Checking Memory Card．", 4);
        func_801B2608("Do not remove Memory Card．", 5);
        func_801B3120();
        D_8003C9A4++;
        // fallthrough
    case 145:
        func_801ADF94(0x80, 0);
        D_800978C4 = 0;
        if (func_801B3164()) {
            D_800978C4 = 1;
            D_8003C9A4++;
            CheckIfMemcardsCanBeUsed();
            if (g_SaveSummary[0].padding == -2 ||
                g_SaveSummary[1].padding == -2) {
                D_801BAFC8 = 0x90;
                D_801BAFCC = 146;
                D_8003C9A4 = 0x200;
            }
        }
        break;
    case 146:
        func_801ACBE4(GFX_UNK_15, 0);
        if (g_SaveSummary[0].padding < 0) {
            g_MemCardSelectorX = (g_MemCardSelectorX % 3) + 3;
        }
        if (g_SaveSummary[1].padding < 0) {
            g_MemCardSelectorX %= 3;
        }
        func_801AEE74();
        if (D_801BAF10) {
            func_801B2608("No data found", 4);
            func_801B2608("on this Memory Card．", 5);
            func_801ADF94(0x82, 0);
            DrawNavigationTips(Tips_Confirm);
            D_8003C9A4 = 0xA0;
        } else {
            DrawNavigationTips(Tips_Generic);
            func_801ADF94(2, 0);
            func_801B2608("Select the file", 4);
            func_801B2608("you wish to rename．", 5);
            D_8003C9A4++;
        }
        break;
    case 160:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x82, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(0x633);
            func_801AE9A8();
            func_801AD490();
            D_8003C9A4 = 2;
        }
        break;
    case 147:
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            func_801AE9A8();
            func_801AD490();
            D_8003C9A4 = 2;
        } else {
            UpdateFileSelect();
            func_801ADF94(2, 0);
            if (g_pads[0].tapped & PAD_CROSS) {
                port = D_801D6B04 / 15;
                slot = D_801D6B04 % 15;
                if (g_SaveSummary[port].icon[slot] >= 0) {
                    g_api.PlaySfx(0x633);
                    D_8003C9A4++;
                } else {
                    g_api.PlaySfx(0x686);
                }
            }
        }
        break;
    case 148:
        STRCPY(g_InputSaveName, "        ");
        func_801AEA8C(1);
        D_8003C9A4++;
        // fallthrough
    case 149:
        for (i = 0; i < 8; i++) {
            if (g_InputSaveName[i] != ' ') {
                break;
            }
        }
        if (g_pads[0].tapped & PAD_SELECT ||
            (g_pads[0].tapped & PAD_TRIANGLE && i == 8 &&
             g_InputCursorPos == 0)) {
            SelectMainMenuOption(MAIN_MENU_CURSOR_FILE_DELETE);
            D_8003C9A4 = 146;
        } else {
            UpdateNameEntry();
            func_801AD78C();
            if (g_pads[0].tapped & PAD_START) {
                SelectMainMenuOption(MAIN_MENU_CURSOR_FILE_DELETE);
                var_a0_2 = 0;
                for (i = 0; i < 8; i++) {
                    if (g_InputSaveName[i] == ' ') {
                        var_a0_2++;
                    }
                }
                if (var_a0_2 == 8) {
                    D_8003C9A4 = 146;
                } else {
                    func_801ACBE4(GFX_UNK_15, 0);
                    func_801B2608("Changing Name．", 4);
                    func_801B2608("Do not remove Memory Card．", 5);
                    g_api.PlaySfx(0x633);
                    D_8003C9A4++;
                }
            }
        }
        break;
    case 150:
        func_801ACBE4(GFX_UNK_6, 8);
        func_801ADF94(0x82, 0);
        func_801B38B4(D_801D6B04, D_801D6B04);
        D_8003C9A4++;
        break;
    case 151:
        func_801ADF94(0x82, 0);
        D_800978C4 = 0;
        temp_v0 = func_801B3A94(g_InputSaveName);
        if (temp_v0 != 0) {
            D_800978C4 = 1;
        }
        if (temp_v0 == 1) {
            func_801B1F4C(5);
            func_801B2608("Name changed．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            D_8003C9A4 += 2;
        }
        if (temp_v0 == -1) {
            func_801B1F4C(5);
            func_801B2608("Loading error．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            D_8003C9A4++;
        }
        if (temp_v0 == -3) {
            func_801B1F4C(5);
            func_801B2608("Save error．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            D_8003C9A4++;
        }
        break;
    case 152:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x82, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(0x633);
            func_801ACBE4(GFX_UNK_15, 8);
            D_8003C9A4 = 0x90;
        }
        break;
    case 153:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x82, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(0x633);
            D_8003C9A4 = 146;
        }
        break;
    case 80:
        SelectMainMenuOption(MAIN_MENU_CURSOR_NAME_CHANGE);
        func_801B2608("Checking Memory Card．", 4);
        func_801B2608("Do not remove Memory Card．", 5);
        func_801B3120();
        D_8003C9A4++;
        // fallthrough
    case 81:
        func_801ADF94(0x80, 0);
        D_800978C4 = 0;
        if (func_801B3164()) {
            D_800978C4 = 1;
            D_8003C9A4++;
            CheckIfMemcardsCanBeUsed();
            if (g_SaveSummary[0].padding == -2 ||
                g_SaveSummary[1].padding == -2) {
                D_801BAFC8 = 0x50;
                D_801BAFCC = 0x52;
                D_8003C9A4 = 0x200;
            }
        }
        break;
    case 82:
        if (g_SaveSummary[0].padding < 0) {
            g_MemCardSelectorX = (g_MemCardSelectorX % 3) + 3;
        }
        if (g_SaveSummary[1].padding < 0) {
            g_MemCardSelectorX %= 3;
        }
        func_801AEE74();
        if (D_801BAF10) {
            func_801B2608("No data found", 4);
            func_801B2608("on this Memory Card．", 5);
            func_801ADF94(0x82, 0);
            DrawNavigationTips(Tips_Confirm);
            D_8003C9A4 = 0x60;
        } else {
            DrawNavigationTips(Tips_Generic);
            func_801ADF94(2, 0);
            func_801B2608("Select file", 4);
            func_801B2608("to be copied．", 5);
            D_8003C9A4++;
        }
        break;
    case 96:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x82, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(0x633);
            func_801AE9A8();
            func_801AD490();
            D_8003C9A4 = 2;
        }
        break;
    case 83:
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            func_801AE9A8();
            func_801AD490();
            D_8003C9A4 = 2;
        } else {
            UpdateFileSelect();
            func_801ADF94(2, 0);
            if (g_pads[0].tapped & PAD_CROSS) {
                port = D_801D6B04 / 15;
                slot = D_801D6B04 % 15;
                if (g_SaveSummary[port].icon[slot] >= 0) {
                    func_801B2608("Where do you want", 4);
                    func_801B2608("to copy to？", 5);
                    D_801BC3EC = D_801D6B04;
                    g_api.PlaySfx(0x633);
                    D_8003C9A4++;
                } else {
                    g_api.PlaySfx(0x686);
                }
            }
        }
        break;
    case 84:
        UpdateFileSelect();
        func_801ADF94(2, 1);
        func_801AE6D0();
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            func_801ACBE4(GFX_UNK_18, 8);
            func_801ACBE4(GFX_UNK_19, 8);
            func_801ACBE4(GFX_UNK_20, 8);
            func_801B2608("Select file", 4);
            func_801B2608("to be copied．", 5);
            D_8003C9A4--;
        } else {
            if (g_pads[0].tapped & PAD_CROSS) {
                port = D_801D6B04 / 15;
                slot = D_801D6B04 % 15;
                if (D_801BC3EC != D_801D6B04) {
                    icon = g_SaveSummary[port].icon[slot];
                    if (icon >= 0) {
                        func_801B1F4C(5);
                        func_801B2608("OK to overwrite data？", 4);
                        g_api.PlaySfx(0x633);
                        D_8003C9A4 = 0x59;
                    } else if (icon != -2) {
                        func_801B2608("Copying data．", 4);
                        func_801B2608("Do not remove Memory Card．", 5);
                        g_api.PlaySfx(0x633);
                        D_8003C9A4++;
                    }
                } else {
                    g_api.PlaySfx(0x686);
                }
            }
        }
        break;
    case 85:
        func_801ACBE4(GFX_UNK_6, 8);
        func_801ADF94(0x82, 1);
        func_801AE6D0();
        func_801B38B4(D_801BC3EC, D_801D6B04);
        D_8003C9A4++;
        break;
    case 86:
        func_801ADF94(0x82, 1);
        func_801AE6D0();
        D_800978C4 = 0;
        temp_v0 = func_801B3A94(0);
        if (temp_v0 != 0) {
            D_800978C4 = 1;
        }
        if (temp_v0 == 1) {
            func_801B1F4C(5);
            func_801B2608("File copied．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            D_8003C9A4 += 2;
        }
        if (temp_v0 == -1) {
            func_801B1F4C(5);
            func_801B2608("Loading error．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            D_8003C9A4++;
        }
        if (temp_v0 == -3) {
            func_801B1F4C(5);
            func_801B2608("Save error．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            D_8003C9A4++;
        }
        break;
    case 87:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x82, 1);
        func_801AE6D0();
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(0x633);
            func_801ACBE4(GFX_UNK_15, 8);
            D_8003C9A4 = 0x50;
        }
        break;
    case 88:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x82, 1);
        func_801AE6D0();
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(0x633);
            func_801ACBE4(GFX_UNK_18, 8);
            func_801ACBE4(GFX_UNK_19, 8);
            func_801ACBE4(GFX_UNK_20, 8);
            D_8003C9A4 = 0x52;
        }
        break;
    case 89:
        DrawNavigationTips(Tips_YesNo);
        func_801ADF94(0x82, 1);
        func_801AE6D0();
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(0x633);
            func_801B2608("Copying data．", 4);
            func_801B2608("Do not remove Memory Card．", 5);
            D_8003C9A4 = 0x55;
        } else {
            if (g_pads[0].tapped & PAD_TRIANGLE) {
                func_801B1F4C(5);
                func_801B25D4("どこにコピーしますか？", 4);
                DrawNavigationTips(Tips_Generic);
                D_8003C9A4 = 0x54;
            }
            func_801AD1D0();
        }
        break;
    case 112:
        SelectMainMenuOption(MAIN_MENU_CURSOR_FILE_COPY);
        func_801B2608("Checking Memory Card．", 4);
        func_801B2608("Do not remove Memory Card．", 5);
        func_801B3120();
        D_8003C9A4++;
        // fallthrough
    case 113:
        func_801ADF94(0x80, 0);
        D_800978C4 = 0;
        if (func_801B3164()) {
            D_800978C4 = 1;
            D_8003C9A4++;
            CheckIfMemcardsCanBeUsed();
            if (g_SaveSummary[0].padding == -2 ||
                g_SaveSummary[1].padding == -2) {
                D_801BAFC8 = 0x70;
                D_801BAFCC = 0x72;
                D_8003C9A4 = 0x200;
            }
        }
        break;
    case 114:
        if (g_SaveSummary[0].padding < 0) {
            g_MemCardSelectorX = (g_MemCardSelectorX % 3) + 3;
        }
        if (g_SaveSummary[1].padding < 0) {
            g_MemCardSelectorX %= 3;
        }
        func_801AEE74();
        if (D_801BAF10) {
            func_801B2608("No data found", 4);
            func_801B2608("on this Memory Card．", 5);
            func_801ADF94(0x82, 0);
            DrawNavigationTips(Tips_Confirm);
            D_8003C9A4 = 0x80;
        } else {
            DrawNavigationTips(Tips_Generic);
            func_801ADF94(2, 0);
            func_801B2608("Select file", 4);
            func_801B2608("to be erased．", 5);
            D_8003C9A4++;
        }
        break;
    case 128:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x82, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(0x633);
            func_801AE9A8();
            func_801AD490();
            D_8003C9A4 = 2;
        }
        break;
    case 115:
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            func_801AE9A8();
            func_801AD490();
            D_8003C9A4 = 2;
        } else {
            UpdateFileSelect();
            func_801ADF94(2, 0);
            DrawNavigationTips(Tips_Generic);
            if (g_pads[0].tapped & PAD_CROSS) {
                port = D_801D6B04 / 15;
                slot = D_801D6B04 % 15;
                if (g_SaveSummary[port].icon[slot] >= 0) {
                    func_801B1F4C(5);
                    func_801B2608("Is it OK to erase file？", 4);
                    g_api.PlaySfx(0x633);
                    D_8003C9A4++;
                } else {
                    g_api.PlaySfx(0x686);
                }
            }
        }
        break;
    case 116:
        DrawNavigationTips(Tips_YesNo);
        func_801ADF94(0x82, 0);
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            func_801B2608("Select file", 4);
            func_801B2608("to be erased．", 5);
            D_8003C9A4--;
        } else if (g_pads[0].tapped & PAD_CROSS) {
            func_801ACBE4(GFX_UNK_15, 8);
            g_api.PlaySfx(0x633);
            D_8003C9A4++;
        }
        break;
    case 117:
        func_801ACBE4(GFX_UNK_6, 8);
        func_801ADF94(0x82, 0);
        func_801B3E14(D_801D6B04);
        D_8003C9A4++;
        break;
    case 118:
        func_801ADF94(0x82, 0);
        D_800978C4 = 0;
        temp_v0 = func_801B3E2C();
        if (temp_v0 != 0) {
            D_800978C4 = 1;
        }
        if (temp_v0 == 1) {
            func_801B1F4C(5);
            func_801B2608("File erased．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            D_8003C9A4 += 2;
        }
        if (temp_v0 == -1) {
            func_801B1F4C(5);
            func_801B2608("Delete error．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            D_8003C9A4++;
        }
        break;
    case 119:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x82, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(0x633);
            func_801ACBE4(GFX_UNK_15, 8);
            D_8003C9A4 = 0x70;
        }
        break;
    case 120:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x82, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(0x633);
            D_8003C9A4 = 0x72;
        }
        break;
    case 256:
        func_801ACBE4(GFX_UNK_6, 8);
        func_801ADF94(0x81, 0);
        func_801B2608("Loading Memory Card．", 4);
        func_801B2608("Do not remove Memory Card．", 5);
        func_801ACBE4(GFX_UNK_15, 0);
        func_801B367C(D_801D6B04);
        D_8003C9A4++;
        break;
    case 257:
        func_801ADF94(0x81, 0);
        D_800978C4 = 0;
        temp_v0 = TryLoadSaveData();
        if (temp_v0 != 0) {
            D_800978C4 = 1;
        }
        if (temp_v0 == 1) {
            D_8003C730 = 1;
            D_80097924 = D_801D6B04 / 15;
            D_8006C378 = g_SaveSummary[D_80097924].slot[D_801D6B04 % 15];
            g_api.PlaySfx(0x80);
            D_8003C9A4 = 0x104;
        }
        if (temp_v0 == -1) {
            func_801B1F4C(5);
            func_801B2608("Loading error．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            D_8003C9A4++;
        }
        if (temp_v0 == -2) {
            func_801B1F4C(5);
            func_801B2608("Version error．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            D_8003C9A4++;
        }
        break;
    case 258:
        func_801ADF94(0x81, 0);
        if (g_pads[0].tapped) {
            func_801ACBE4(GFX_UNK_15, 8);
            D_8003C9A4 = 0x30;
        }
        break;
    case 260:
        func_801ADF94(0x81, 0);
        if (func_801ACEC0()) {
            g_GameStep++;
        }
        break;
    case 512:
        DrawNavigationTips(Tips_NoYes);
        func_801ADF94(0x80, 0);
        if (g_SaveSummary[0].padding != -2) {
            D_8003C9A4 = 0x210;
        } else {
            func_801B2608("Format Memory Card", 4);
            func_801B2608("in slot １？", 5);
            D_8003C9A4++;
        }
        break;
    case 513:
        func_801ADF94(0x80, 0);
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            g_api.PlaySfx(0x633);
            func_801ACBE4(GFX_UNK_6, 8);
            MemCardSetPort(0);
            D_8003C9A4++;
        } else {
            if (g_pads[0].tapped & PAD_CROSS) {
                D_8003C9A4 = 0x210;
            }
            func_801AD218();
        }
        break;
    case 514:
        func_801ADF94(0x80, 0);
        D_800978C4 = 0;
        temp_v0 = MemCardInitAndFormat();
        if (temp_v0 != 0) {
            D_800978C4 = 1;
        }
        if (temp_v0 == 1) {
            func_801B1F4C(5);
            func_801B2608("Formatting completed．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            D_8003C9A4 += 2;
        }
        if (temp_v0 == -1) {
            func_801B1F4C(5);
            func_801B2608("Formatting error．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            D_8003C9A4++;
        }
        break;
    case 515:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x80, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(0x633);
            func_801ACBE4(GFX_UNK_15, 8);
            D_8003C9A4 = D_801BAFC8;
        }
        break;
    case 516:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x80, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(0x633);
            D_8003C9A4 = D_801BAFC8;
        }
        break;
    case 528:
        func_801ADF94(0x80, 0);
        func_801AD218();
        if (g_SaveSummary[1].padding != -2) {
            D_8003C9A4 = 0x220;
        } else {
            func_801B2608("Format Memory Card", 4);
            func_801B2608("in slot １？", 5);
            D_8003C9A4++;
        }
        break;
    case 529:
        func_801ADF94(0x80, 0);
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            g_api.PlaySfx(0x633);
            func_801ACBE4(GFX_UNK_6, 8);
            MemCardSetPort(1);
            D_8003C9A4++;
        } else {
            if (g_pads[0].tapped & 0x40) {
                D_8003C9A4 = 0x220;
            }
            func_801AD218();
        }
        break;
    case 530:
        func_801ADF94(0x80, 0);
        D_800978C4 = 0;
        temp_v0 = MemCardInitAndFormat();
        if (temp_v0 != 0) {
            D_800978C4 = 1;
        }
        if (temp_v0 == 1) {
            func_801B1F4C(5);
            func_801B2608("Formatting completed．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            D_8003C9A4 += 2;
        }
        if (temp_v0 == -1) {
            func_801B1F4C(5);
            func_801B2608("Formatting error．", 4);
            func_801ACBE4(GFX_UNK_15, 0);
            D_8003C9A4++;
        }
        break;
    case 531:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x80, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(0x633);
            func_801ACBE4(GFX_UNK_15, 8);
            D_8003C9A4 = D_801BAFC8;
        }
        break;
    case 532:
        DrawNavigationTips(Tips_Confirm);
        func_801ADF94(0x80, 0);
        if (g_pads[0].tapped & PAD_CROSS) {
            g_api.PlaySfx(0x633);
            D_8003C9A4 = D_801BAFC8;
        }
        break;
    case 544:
        func_801ADF94(0x80, 0);
        if (D_801BAF10) {
            DrawNavigationTips(Tips_YesNo);
        }
        D_8003C9A4 = D_801BAFCC;
        break;
    }
    if (++g_GameTimer == 10) {
        g_GameTimer = 0;
        D_801BAF08 = (D_801BAF08 + 1) % 3;
    }
}

void func_801B17C8(void) {
    switch (g_MenuStep) {
    case 0:
        if (D_80097924 == -1 || D_8006C378 == -1) {
            g_GameStep++;
        } else {
            D_800978C4 = 0;
            g_MenuStep++;
        }
        break;

    case 1:
        func_801B3A54(D_80097924, D_8006C378);
        g_MenuStep++;
        break;

    case 2:
        D_800978C4 = 0;
        if (func_801B3A94(1) != 0) {
            D_800978C4 = 1;
            g_GameStep++;
        }
        break;
    }
}

void SetGameState(GameState gameState) {
    g_GameState = gameState;
    g_GameStep = 0;
    g_backbufferX = 0;
    g_backbufferY = 0;
}

void func_801B18F4(void) { ClearImage(&D_801825A4, 0, 0, 0); }

void func_801B1924(void) {
    g_GpuBuffers[0].draw.r0 = 0;
    g_GpuBuffers[0].draw.g0 = 0;
    g_GpuBuffers[0].draw.b0 = 0;
    g_GpuBuffers[1].draw.r0 = 0;
    g_GpuBuffers[1].draw.g0 = 0;
    g_GpuBuffers[1].draw.b0 = 0;
}

void func_801B195C(s32 arg0) {
    g_GpuBuffers[0].draw.clip.y = 20;
    g_GpuBuffers[0].draw.clip.h = 207;
    if (arg0 == 0) {
        g_GpuBuffers[1].draw.clip.y = 20;
    } else {
        g_GpuBuffers[1].draw.clip.y = 276;
    }
    g_GpuBuffers[1].draw.clip.h = 207;
    g_GpuBuffers[1].draw.isbg = 1;
    g_GpuBuffers[0].draw.isbg = 1;
    func_801B1924();
    g_GpuBuffers[1].draw.dtd = 0;
    g_GpuBuffers[0].draw.dtd = 0;
    g_GpuBuffers[1].disp.isrgb24 = 0;
    g_GpuBuffers[0].disp.isrgb24 = 0;
}

void func_801B19F4(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDrawEnv(
        &g_GpuBuffers[1].draw, DISP_STAGE_W, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDispEnv(
        &g_GpuBuffers[0].disp, DISP_STAGE_W, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    func_801B195C(0);
}

void func_801B1A98(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_W, DISP_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 256, DISP_W, DISP_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 256, DISP_W, DISP_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_W, DISP_H);
    g_GpuBuffers[1].draw.clip.y = DISP_W / 2;
    g_GpuBuffers[1].draw.clip.h = DISP_H;
    g_GpuBuffers[0].draw.clip.h = DISP_H;
    g_GpuBuffers[0].draw.clip.y = 0;
    g_GpuBuffers[1].draw.isbg = 1;
    g_GpuBuffers[0].draw.isbg = 1;
    func_801B1924();
    g_GpuBuffers[1].disp.isrgb24 = 0;
    g_GpuBuffers[0].disp.isrgb24 = 0;
}

void func_801B1B88(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, 384, DISP_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 256, 384, DISP_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 256, 384, DISP_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, 384, DISP_H);
    g_GpuBuffers[1].draw.clip.y = 256;
    g_GpuBuffers[1].draw.clip.h = DISP_H;
    g_GpuBuffers[0].draw.clip.h = DISP_H;
    g_GpuBuffers[0].draw.clip.y = 0;
    g_GpuBuffers[1].draw.isbg = 1;
    g_GpuBuffers[0].draw.isbg = 1;
    func_801B1924();
    g_GpuBuffers[1].disp.isrgb24 = 0;
    g_GpuBuffers[0].disp.isrgb24 = 0;
}

void func_801B1C78(POLY_GT4* poly, u8 colorIntensity, s32 vertexIndex) {
    switch (vertexIndex) {
    case 0:
        poly->r0 = poly->g0 = poly->b0 = colorIntensity;
        break;
    case 1:
        poly->r1 = poly->g1 = poly->b1 = colorIntensity;
        break;
    case 2:
        poly->r2 = poly->g2 = poly->b2 = colorIntensity;
        break;
    case 3:
        poly->r3 = poly->g3 = poly->b3 = colorIntensity;
        break;
    }
}

void func_801B1CFC(POLY_GT4* poly, s32 colorIntensity) {
    func_801B1C78(poly, colorIntensity, 0);
    func_801B1C78(poly, colorIntensity, 1);
    func_801B1C78(poly, colorIntensity, 2);
    func_801B1C78(poly, colorIntensity, 3);
}

void func_801B1D68(POLY_GT4* poly) { func_801B1CFC(poly, 0); }

void func_801B1D88(POLY_GT4* arg0) { func_801B1CFC(arg0, 0x80); }

void func_801B1DA8(void) {
    s32 index = 0;
    s32 i, j;

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x200; j < 0x300; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0; j < 0x100; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x100; j < 0x200; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
        }
    }
}

void func_801B1ED0(void) {
    s32 var_v1 = 0xF;
    s32* var_v0 = D_801BC3D4;

    do {
        *var_v0-- = 0;
    } while (--var_v1 >= 0);
}

u8 func_801B1EF4(u8 arg0) {
    if (arg0 & 0x80) {
        return func_801B1EF4((arg0 & 0x7F) + 3);
    } else {
        return (arg0 * 0x10) & 0xF0;
    }
}

void func_801B1F34(void) { D_801BAFD0 = g_Pix[1]; }

void func_801B1F4C(s32 arg0) {
    const s32 count = 0x200;
    u8* pix;
    s32 i;

    D_801BC398[arg0] = 0;
    arg0 = func_801B1EF4(arg0);
    pix = D_801BAFD0;
    for (i = 0; i < count * 4; i++) {
        *D_801BAFD0++ = 0;
    }

    LoadTPage(pix, 0, 0, 0x180, arg0, 0x100, 0x10);
}

void func_801B1FD8(u8* arg0, s32 arg1) {
    const int W = 12;
    const int H = 16;
    const int LEN = W * H / 2;
    s32 y;
    s32 i;
    s32 x;
    u8* srcPix;
    s32 param;

    y = func_801B1EF4(arg1);
    x = 0;
    while (*arg0 != 0 && D_801BAFD0 < g_Pix[4]) {
        param = *arg0++ << 8;
        param += *arg0++;
        srcPix = g_api.func_80106A28(param, 3);
        for (i = 0; i < LEN; i++) {
            D_801BAFD0[i] = *srcPix++;
        }
        LoadTPage(D_801BAFD0, 0, 0, D_801BAFD4 + x, D_801BAFD8 + y, W, H);
        D_801BAFD0 += LEN;
        x += 3;
    }
}

void func_801B2108(const char* str, s32 id);
INCLUDE_ASM("asm/us/st/sel/nonmatchings/2EED8", func_801B2108);

void func_801B248C(const char* str, s32 id) {
    if (D_801BC398[id] != str) {
        func_801B1F4C(id);
        D_801BC398[id] = str;
        func_801B1FD8(str, id);
    }
}

void func_801B24F8(const char* str, s32 id) {
    if (D_801BC398[id] != str) {
        func_801B1F4C(id);
        D_801BC398[id] = str;
        func_801B2108(str, id);
    }
}

void func_801B2564(const char* str, s32 id) {
    D_801BAFD4 = 0x3C0;
    D_801BAFD8 = 0x100;
    func_801B248C(str, id);
}

void func_801B259C(const char* str, s32 id) {
    D_801BAFD4 = 0x3C0;
    D_801BAFD8 = 0x100;
    func_801B24F8(str, id);
}

void func_801B25D4(const char* str, s32 id) {
    D_801BAFD4 = 0x180;
    D_801BAFD8 = 0;
    func_801B248C(str, id);
}

void func_801B2608(const char* str, s32 id) {
    D_801BAFD4 = 0x180;
    D_801BAFD8 = 0;
    func_801B24F8(str, id);
}

void func_801B263C(const char* str, s32 id) {
    D_801BAFD4 = 0x180;
    D_801BAFD8 = 0;
    func_801B1FD8(str, id);
}

#include "../../set_prim_rect.h"

void func_801B2700(s32 tpage, s32 otIdx) {
    DR_MODE* drawMode = &g_CurrentBuffer->drawModes[g_GpuUsage.drawModes];
    u_long* ot = g_CurrentBuffer->ot;

    SetDrawMode(drawMode, 0, 0, tpage, &D_80182584);
    AddPrim(&ot[otIdx], drawMode);
    g_GpuUsage.drawModes++;
}

void func_801B27A8(s32 x, s32 y, s32 w, s32 h, s32 u, s32 v, s32 clut, s32 arg7,
                   s32 tge, s32 c) {
    SPRT* sprite = &g_CurrentBuffer->sprite[g_GpuUsage.sp];
    GpuBuffer* temp_s4 = g_CurrentBuffer;

    SetSemiTrans(sprite, 0);
    SetShadeTex(sprite, tge);
    sprite->x0 = x;
    sprite->y0 = y;
    sprite->w = w;
    sprite->h = h;
    sprite->u0 = u;
    sprite->v0 = v;
    sprite->r0 = c;
    sprite->g0 = c;
    sprite->b0 = c;
    sprite->clut = D_8003C104[clut];
    AddPrim(&temp_s4->ot[0x20], sprite);
    g_GpuUsage.sp++;
    func_801B2700(arg7, 0x20);
}

void func_801B28D4(u8* str, s32 x, s32 y, s32 tge) {
    const int w = 12;
    const int h = 16;
    u8 ch;

loop_1:
    ch = *str++;
    if (ch != 0xFF) {
        s32 u = (ch & 0xF) * w;
        s32 v = ch & 0xF0;
        func_801B27A8(x, y, w, h, u, v, 0x1A1, 6, tge, 0x40);
        x += w;
        goto loop_1;
    }
}

s32 func_801B2984(u8 ch) {
    s32 i;
    for (i = 0; i < 0x20; i++) {
        if (D_8018046C[i * 3] == ch)
            return i;
    }
    return 0x20;
}

void DrawString16x16(const char* str, s32 x, s32 y, s32 tga) {
    const int W = 16;
    const int H = 16;
    char ch;
    s32 uvIndex;

    while (true) {
        ch = *str++;
        if (ch == 0) {
            break;
        }

        uvIndex = func_801B2984(ch);
        func_801B27A8(x, y, W, H, D_8018046C[uvIndex * 3 + 1],
                      D_8018046C[uvIndex * 3 + 2], 0x200, 12, tga, 0x40);
        x += W;
    }
}

void func_801B2A9C(s32 img, s32 x, s32 y, s32 tge) {
    func_801B27A8(
        x, y, 8, 8, (img & 0xF) * 8, (img & 0xF0) / 2, 0x196, 0x1E, tge, 0x80);
}

void DrawImages8x8(u8* imgs, s32 x, s32 y, s32 tge) {
    while (true) {
        if (*imgs == 0xFF)
            break;
        func_801B2A9C(*imgs, x, y, tge);
        x += 8;
        imgs++;
    }
}

void func_801B2B78(s32 icon, s32 x, s32 y, s32 tge) {
    func_801B27A8(x, y, 8, 8, icon * 8 + 176, 120, 0x200, 0xC, tge, 0x40);
}

void func_801B2BD4(s32 digit, s32 x, s32 y, s32 tge) {
    do {
        func_801B2B78(digit % 10, x, y, tge);
        digit /= 10;
        x -= 8;
    } while (digit != 0);
}

void func_801B2C70(s32 digit, s32 x, s32 y, s32 tge) {
    func_801B2B78(digit % 10, x, y, tge);
    func_801B2B78(digit / 10, x - 8, y, tge);
}

void func_801B2CF8(POLY_GT4* poly) {
    u32* data = poly;
    s32 n = sizeof(POLY_GT4) / sizeof(*data);
    s32 i;

    for (i = 0; i < n; i++) {
        *data++ = 0;
    }
}

void func_801B2D1C(void) {
    s32 i;
    Primitive* prim;

    for (i = 0, prim = g_PrimBuf; i < MAX_PRIM_COUNT; i++) {
        func_801B2CF8((s32*)prim);
        prim->type = PRIM_NONE;
        prim++;
    }
}

void func_801B2D6C(void) {
    MemcardInit();
    D_801BAFDC = 0;
    D_801BAFE0 = 0;
    D_801BAFE4 = 0;
    D_801BAFE8 = 0;
}

s32 func_801B2DAC(void) { return D_801BAFE4 < 2 || D_801BAFE4 == 2; }

void func_801B2DDC(void) {}

void func_801B2DE4(void) {}

void func_801B2DEC(void) {}

void func_801B2DF4(void) {
    if (func_801B2DAC() != 0) {
        D_801BAFDC = func_800E9880(D_801BAFE8, 0);
        if (D_801BAFDC != 0) {
            D_801BAFE0 = D_801BAFDC;
        }
    }

    func_801B2DDC();
    func_801B2DE4();
    func_801B2DEC();
}

extern const char D_801A7AE4[19] ALIGNED4; // "BASLUS-00067DRAX00"
s32 func_801B2E5C(s32 port) {
    char cardName[32];
    struct DIRENTRY* dirent;
    s32 i;
    s32 j;
    s32 totalSize;
    s32 nBlockUsed;

    STRCPY(cardName, D_801A7AE4);
    totalSize = 0;
    nBlockUsed = g_MemcardInfo[port].nBlockUsed;
    dirent = &g_MemcardInfo[port].entries;
    for (i = 0; i < nBlockUsed; i++) {
        for (j = 0; j < 16; j++) {
            if (cardName[j] != dirent[i].name[j]) {
                break;
            }
        }
        if (j != 16) {
            totalSize += dirent[i].size;
        }
    }

    totalSize /= CARD_BLOCK_SIZE;
    return totalSize;
}

void HydrateSaveSummaryEntry(s32 port, s32 slot, s32 slotValue) {
    SaveData* save = (SaveData*)g_Pix;
    g_SaveSummary[port].slot[slot] = slotValue;
    g_SaveSummary[port].icon[slot] = save->info.cardIcon;
    g_SaveSummary[port].stage[slot] = save->info.stage;
    g_SaveSummary[port].roomX[slot] = save->info.roomX;
    g_SaveSummary[port].roomY[slot] = save->info.roomY;
    g_SaveSummary[port].nRoomsExplored[slot] = save->info.nRoomsExplored;
    g_SaveSummary[port].level[slot] = save->info.level;
    g_SaveSummary[port].gold[slot] = save->info.gold;
    g_SaveSummary[port].playHours[slot] = save->info.playHours;
    g_SaveSummary[port].playSeconds[slot] = save->info.playSeconds;
    g_SaveSummary[port].playMinutes[slot] = save->info.playMinutes;
    if (save->info.saveSize != sizeof(SaveData)) {
        save->info.endGameFlags = 0;
    }
    g_SaveSummary[port].kind[slot] = save->info.endGameFlags;
    g_SaveSummary[port].character[slot] = save->info.character;
    strcpy(g_SaveSummary[port].name[slot], save->info.name);
    g_IsTimeAttackUnlocked |= save->info.endGameFlags;
}

void func_801B3120(void) {
    s32* var_a0;
    s32* var_v0;
    s32* var_v1;
    s32 i;
    s32 n;

    g_MemCardRStep = 0;
    i = 0;
    n = -1;
    var_v0 = g_SaveSummary;
    var_a0 = var_v0 + 0xEA;
    var_v1 = var_v0;
    for (; i < 0xF; i++) {
        *var_v1 = n;
        *var_a0 = n;
        var_a0++;
        var_v1++;
    }
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2EED8", func_801B3164);

void func_801B367C(s32 arg0) {
    g_MemCardRStep = 0;
    g_MemCardRStepSub = arg0;
}

s32 TryLoadSaveData(void) {
    char saveFile[32];
    s32 nPort;
    s32 nSlot;
    s32 temp_v0;
    s32 blockId;

    FntPrint(D_801A7AF8, g_MemCardRStep, g_MemCardRStepSub);
    FntPrint(D_801A7B08, g_MemCardRetryCount);

    nPort = g_MemCardRStepSub / 15;
    nSlot = g_MemCardRStepSub % 15;
    blockId = g_SaveSummary[nPort].slot[nSlot];
    switch (g_MemCardRStep) {
    case 0:
        MemcardInit();
        g_MemCardRetryCount = 10;
        g_MemCardRStep = 3;
        break;
    case 3:
        MakeMemcardPath(saveFile, blockId);
        if (MemcardReadFile(nPort, 0, saveFile, g_Pix[0], 1) != 0) {
            g_MemCardRetryCount--;
            if (g_MemCardRetryCount != -1) {
                return 0;
            }
            temp_v0 = -1;
            return temp_v0;
        }
        g_MemCardRStep++;
        break;
    case 4:
        temp_v0 = MemcardClose(nPort);
        if (temp_v0 != 0) {
            if (temp_v0 == -3) {
                g_MemCardRetryCount--;
                if (g_MemCardRetryCount == -1) {
                    return -1;
                } else {
                    g_MemCardRStep--;
                    do {
                        return 0;
                    } while (0); // FAKE!
                }
            }
            if (LoadSaveData(g_Pix[0]) < 0) {
                return -2;
            } else {
                return 1;
            }
        }
        break;
    }

    return 0;
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2EED8", func_801B38B4);

void func_801B3A54(s32 arg0, s32 arg1) {
    char pad[0x20];

    g_MemCardRStep = 0;
    D_801BAFFC = arg0;
    D_801BB000 = arg1;
    D_801BB004 = arg0;
    D_801BB00C = arg1;
    D_801BB008 = arg1;
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2EED8", func_801B3A94);

void func_801B3E14(s32 arg0) {
    g_MemCardRStep = 0;
    g_MemCardRStepSub = arg0;
}

s32 func_801B3E2C(void) {
    char path[32];
    s32 slot;
    s32 blockId;
    s32 port;

    port = g_MemCardRStepSub / 15;
    slot = g_MemCardRStepSub % 15;
    blockId = g_SaveSummary[port].slot[slot];
    switch (g_MemCardRStep) {
    case 0:
        MemcardInit(slot, blockId);
        g_MemCardRetryCount = 10;
        g_MemCardRStep++;
        break;
    case 1:
        MakeMemcardPath(path, blockId);
        if (MemcardEraseFile(port, 0, path)) {
            if (--g_MemCardRetryCount == -1) {
                return -1;
            }
        } else {
            g_SaveSummary[port].icon[slot] = -3;
            return 1;
        }
        break;
    }
    return 0;
}

void MemCardSetPort(s32 port) {
    g_MemCardRStep = 0;
    g_MemCardRStepSub = port;
}

s32 MemCardInitAndFormat(void) {
    int dummy[8];
    u32 nPort = g_MemCardRStepSub;
    s32 state = g_MemCardRStep;

    switch (state) {
    case 0:
        MemcardInit();
        g_MemCardRetryCount = 5;
        g_MemCardRStep++;
        break;

    case 1:
        if (MemcardFormat(nPort, 0) != 1) {
            if (--g_MemCardRetryCount == -1) {
                return -1;
            }
        } else {
            return 1;
        }
        break;
    }

    return 0;
}

void InitRoomEntities(s32 objLayoutId) {
    switch (D_8003C9A4) {
    case 0:
        if (g_IsUsingCd) {
            break;
        }
        g_IsTimeAttackUnlocked = true;
        D_8003C728 = 1;
        D_8003C100 = 0;
        D_8003C9A4 = 1;
        break;

    case 1:
        func_801B9C80();
        if (D_8003C728) {
            break;
        }
        g_IsTimeAttackUnlocked = false;
        D_8003C100 = 0;
        func_801B18F4();
        g_GameState = Game_Title;
        D_8003C9A4 = 0;
        break;
    }
}
