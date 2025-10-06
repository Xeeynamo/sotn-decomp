// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../sel/sel.h"

extern s32 D_91CE5E8;
extern s32 D_91CE5F0;
extern s32 D_psp_09285EB8;
extern s32 D_psp_09285EC0;
extern s32 D_psp_09285EC8;
extern s32 D_psp_09285ED0;
extern s32 D_psp_09285ED8;
extern s32 D_psp_09285EE0;
extern char D_psp_09285510[];
extern char D_psp_09285520[];
extern char D_psp_09285530[];
extern s32 D_psp_09285EA8;
extern s32 D_psp_09285E80;
extern s32 D_psp_09285E88;
extern s32 D_psp_09285E90;
extern s32 D_psp_09285E98;
extern s32 D_psp_09285EA0;
extern s32 D_psp_09285EB0;
extern s32 D_psp_09286634;
extern s32 D_psp_0928628C;
extern s32 D_91CE5D0;
extern u32 D_psp_09285D68;
extern s32 D_psp_09285E78;
extern s32 g_UserLanguage;
extern s32 D_psp_0924F800;
extern s32 D_psp_0924F808;
extern s32 D_psp_09285E68;
extern s32 D_psp_09285E70;
extern s32 D_psp_09285D60;
extern s32 D_91CE558;
extern u8 D_psp_09285170[];
extern s32 D_psp_09285480[];
extern s32 D_psp_09285508;
extern s32 D_psp_08B42050;

void func_psp_09240A88(void) {
    switch (g_GameEngineStep) {
    case 0:
        if (g_IsUsingCd) {
            break;
        }
        g_IsTimeAttackUnlocked = 1;
        D_91CE5F0 = 1;
        D_91CE5E8 = 0;
        g_GameEngineStep++;
        break;

    case 1:
        func_90FFAB8();
        if (D_91CE5F0) {
            break;
        }
        g_IsTimeAttackUnlocked = 0;
        D_91CE5E8 = 0;
        func_psp_0923F498();
        g_GameState = Game_Title;
        g_GameEngineStep = 0;
        break;
    }
}

void func_psp_09240B58(void) {
    RECT rect;
    Primitive* prim;
    Primitive* prim15;
    s32 i;
    s32 var_s3;

    if (0) {
        s32 var_s4 = 0; // fake
    }

    func_psp_0923FBF0();
    switch (g_GameEngineStep) {
    case 0:
        if (g_UseDisk != 0) {
            g_CdStep = 1;
            g_LoadFile = 0x8003;
            D_91CE5D0 = 0xFF;
        }
        rect.x = 0x220;
        rect.y = 0x1AF;
        rect.w = 2;
        rect.h = 1;
        StoreImage(&rect, (u_long*)&D_psp_09285D68);
        func_psp_09237CB8();
        D_psp_09285E78 = g_api.AllocPrimitives(PRIM_SPRT, 0x15);
        prim = &g_PrimBuf[D_psp_09285E78];
        for (i = 0; i < 3; i++, prim = prim->next) {
            prim->x0 = i * 0x80 + 0x70;
            prim->y0 = 0xA0;
            prim->u0 = 0x80;
            prim->v0 = i * 0x10 + 0xB0;
            prim->u1 = 0x80;
            if (i == 2) {
                prim->u1 = 0x20;
            }
            prim->v1 = 0x10;
            prim->tpage = 0x18;
            prim->clut = 0x20;
            prim->priority = 1;
            prim->drawMode = DRAW_HIDE;
        }
        for (i = 0; i < 4; i++, prim = prim->next) {
            prim->x0 = i * 0x80 + 0xC;
            prim->y0 = 0xD6;
            prim->u0 = 0x80;
            prim->v0 = i * 8 + 0x90;
            prim->u1 = 0x80;
            if (i == 3) {
                prim->u1 = 0x64;
            }
            prim->v1 = 8;
            prim->tpage = 0x18;
            prim->clut = 0x21;
            prim->priority = 1;
            prim->drawMode = DRAW_HIDE;
        }
        for (i = 0; i < 4; i++, prim = prim->next) {
            prim->x0 = i * 0x80;
            prim->u1 = 0x80;
            prim->v1 = 0xF0;
            prim->tpage = i + 0x88;
            prim->clut = 0x10;
            prim->drawMode = DRAW_HIDE;
        }
        for (i = 0; i < 4; i++, prim = prim->next) {
            prim->x0 = i * 0x80;
            prim->u1 = 0x80;
            prim->y0 = 8;
            prim->v1 = 0x80;
            switch (i) {
            case 0:
            case 1:
                prim->tpage = (D_psp_0924F800 | 0x80) + i;
                break;
            case 2:
            case 3:
                prim->tpage = ((D_psp_0924F808 | 0x80) + i) - 2;
                break;
            }
            prim->clut = 0;
            prim->priority = 2;
            prim->drawMode = DRAW_HIDE;
        }
        prim->x0 = 0x101;
        prim->y0 = 0x60;
        prim->u1 = 0xFF;
        prim->v1 = 0x90;
        prim->tpage = 0x18;
        prim->clut = 0x22;
        prim->priority = 1;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;

        prim->v0 = 0x90;
        prim->u1 = 0x78;
        prim->v1 = 0x40;
        prim->tpage = 0x18;
        prim->clut = 0x22;
        prim->priority = 1;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;

        for (i = 0; i < 2; i++, prim = prim->next) {
            prim->x0 = (i * 0x80) + 0xA0;
            prim->y0 = 0x9C;
            if (i == 0) {
                prim->u0 = 0;
                prim->v0 = 0;
                prim->u1 = 0x80;
                prim->v1 = 0x10;
                prim->tpage = 0x1F;
            } else if (g_UserLanguage != 1) {
                prim->u0 = 0;
                prim->v0 = 0x10;
                prim->u1 = 0x80;
                prim->v1 = 0x14;
                prim->tpage = 0x1F;
            } else {
                prim->u0 = 0x85;
                prim->v0 = 0xC0;
                prim->u1 = 0x24;
                prim->v1 = 0x10;
                prim->tpage = 0x18;
            }
            prim->clut = 0x20;
            prim->priority = 0;
            prim->drawMode = DRAW_HIDE;
        }
        for (i = 0; i < 1; i++, prim = prim->next) {
            prim->x0 = 0xA0;
            prim->y0 = 0xBC;
            prim->u0 = 0;
            prim->v0 = 0x60;
            prim->u1 = 0x80;
            prim->v1 = 0x10;
            prim->tpage = 0x1F;
            prim->clut = 0x20;
            prim->priority = 0;
            prim->drawMode = DRAW_HIDE;
        }
        for (i = 0; i < 1; i++, prim = prim->next) {
            prim->x0 = 0x78;
            prim->y0 = 0x9C;
            prim->u0 = 0x30;
            prim->v0 = 0x50;
            prim->u1 = 0x20;
            prim->v1 = 0x10;
            prim->tpage = 0x1F;
            prim->clut = 0x20;
            prim->priority = 0;
            prim->drawMode = DRAW_HIDE;
        }
        D_psp_09285E70 = 0;
        func_psp_0923F498();
        D_psp_09285E68 = 0;
        g_GameEngineStep++;
        func_891CEB8(0x200, 0xF0);
        func_891CEB8(0x200, 0xF1);
        func_8925F7C(0x200, 0xF2, 0x10, 1);
        func_8925F7C(0x210, 0xF2, 0x10, 1);
        func_8925F7C(0x220, 0xF2, 0x10, 1);
        break;

    case 1:
        func_psp_0923F668();
        prim = &g_PrimBuf[D_psp_09285E78];
        i = 0;
        D_psp_09285E68 += 8;
        while (prim != NULL) {
            prim->drawMode = DRAW_COLORS;
            func_psp_0923F948(prim, D_psp_09285E68);
            if (i == 15 || i == 16) {
                prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            }
            prim = prim->next;
            i++;
        }
        if (D_psp_09285E68 == 0x80) {
            D_psp_09285D60 = 0x800;
            g_GameEngineStep++;
        }
        break;

    case 2:
        prim = &g_PrimBuf[D_psp_09285E78];
        for (i = 0; prim != NULL; prim = prim->next, i++) {
            if (i < 3) {
                prim->drawMode = DRAW_HIDE;
                if (g_Timer & 0x30) {
                    prim->drawMode = DRAW_DEFAULT;
                }
            }
            if ((i != 15) && (i != 16)) {
                continue;
            }
            if (i == 15) {
                prim15 = prim;
            }
            switch (prim->p1) {
            case 0:
                if (i == 0xF) {
                    if (!(rand() & 0x7F)) {
                        prim->p2 = 6;
                        prim->tpage = 0x19;
                        prim->p1++;
                    }
                } else if (
                    (prim15->p1 >= 2) || (prim15->p1 && (prim15->p2 < 3))) {
                    prim->p2 = (rand() & 3) + 6;
                    prim->tpage = 0x19;
                    prim->p1++;
                }
                break;

            case 1:
                if (!--prim->p2) {
                    prim->p2 = 6;
                    prim->tpage = 0x1A;
                    prim->p1++;
                }
                break;

            case 2:
                if (!--prim->p2) {
                    prim->p2 = (rand() & 7) + 6;
                    prim->tpage = 0x1B;
                    prim->p1++;
                }
                break;

            case 3:
                if (!--prim->p2) {
                    prim->p2 = 5;
                    prim->tpage = 0x1A;
                    prim->p1++;
                }
                break;

            case 4:
                if (!--prim->p2) {
                    prim->p2 = 5;
                    prim->tpage = 0x19;
                    prim->p1++;
                }
                break;

            case 5:
                if (!--prim->p2) {
                    prim->p2 = 6;
                    prim->tpage = 0x18;
                    prim->p1++;
                }
                break;

            case 6:
                if (!--prim->p2) {
                    if (i == 0x10) {
                        prim->p1 = 0;
                    } else {
                        prim->p1++;
                        prim->p2 = 6;
                        if (rand() & 3) {
                            prim->p1 = 1;
                            prim->tpage = 0x19;
                        }
                    }
                }
                break;

            case 7:
                if (!--prim->p2) {
                    prim->p1 = 0;
                }
                break;
            }
            if (i == 0x10) {
                if (prim->tpage == 0x18) {
                    prim->u1 = 0x78;
                } else {
                    prim->u1 = 0x70;
                }
            }
        }
        var_s3 = 0;
        if (g_pads[0].tapped & 8) {
            var_s3++;
        }
        if (var_s3 != 0) {
            g_api.PlaySfx(SFX_START_SLAM_B);
            g_GameEngineStep++;
        }
        break;

    case 3:
        g_GameEngineStep = 7;
        break;

    case 4:
        if (g_pads[0].tapped & 0x60) {
            g_api.PlaySfx(SFX_DEBUG_SELECT);
            D_91CE558++;
            if (D_91CE558 >= 0x21) {
                D_91CE558 = 0;
            }
        }
        if (g_pads[0].tapped & 0x90) {
            g_api.PlaySfx(SFX_DEBUG_SELECT);
            D_91CE558--;
            if (D_91CE558 < 0) {
                D_91CE558 = 0x20;
            }
        }
        g_StageId = D_psp_09285170[D_91CE558];
        func_psp_0923FC08(1);
        func_90F0DD8(D_psp_09285480[D_91CE558], 1);
        if (g_pads[0].tapped & (D_psp_08B42050 | 8)) {
            g_api.PlaySfx(SFX_START_SLAM_B);
            g_GameEngineStep++;
        }
        break;

    case 5:
        func_psp_0923F498();
        func_psp_0923F5C0();
        func_psp_0923F9E8();
        g_api.FreePrimitives(D_psp_09285E78);
        STRCPY(g_Status.saveName, &D_psp_09285508);
        if (g_StageId == STAGE_ST0) {
            func_psp_0923F460(Game_VideoPlayback);
        } else if (g_StageId == STAGE_MEMORYCARD) {
            func_psp_0923F460(Game_MainMenu);
        } else {
            func_psp_0923F460(Game_NowLoading);
            g_GameStep = 2;
        }
        break;

    case 6:
        prim = &g_PrimBuf[D_psp_09285E78] + 3;
        i = 3;
        D_psp_09285E68 -= 8;
        while (prim != NULL) {
            prim->drawMode = DRAW_COLORS;
            func_psp_0923F948(prim, D_psp_09285E68);
            if (i == 15 || i == 16) {
                prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            }
            prim = prim->next;
            i++;
        }
        if (D_psp_09285E68 == 0) {
            g_StageId = STAGE_MEMORYCARD;
            g_GameEngineStep = 5;
        }
        if (D_psp_09285E70 == 1) {
            func_psp_0923F460(0xA);
        }
        break;

    case 7:
        prim = &g_PrimBuf[D_psp_09285E78];
        for (i = 0; i < 3; i++, prim = prim->next) {
            prim->priority = 0;
            prim->drawMode = DRAW_HIDE;
        }
        prim = &g_PrimBuf[D_psp_09285E78] + 17;
        for (i = 0; i < 3; i++, prim = prim->next) {
            prim->priority = 2;
        }
        prim = &g_PrimBuf[D_psp_09285E78] + 20;
        for (i = 0; i < 1; i++, prim = prim->next) {
            prim->priority = 2;
            prim->x0 = 0x78;
            prim->y0 = (D_psp_09285E70 << 5) + 0x9C;
        }
        if (g_pads[0].tapped & 0x40) {
            D_psp_09285E70++;
            if (D_psp_09285E70 >= 2) {
                D_psp_09285E70 = 1;
            } else {
                g_api.PlaySfx(0x67B);
            }
        }
        if (g_pads[0].tapped & 0x10) {
            D_psp_09285E70--;
            if (D_psp_09285E70 < 0) {
                D_psp_09285E70 = 0;
            } else {
                g_api.PlaySfx(0x67B);
            }
        }
        if (g_pads[0].tapped & (D_psp_08B42050 | 8)) {
            g_api.PlaySfx(0x63D);
            g_GameEngineStep = 6;
        }
        break;
    }
}

void func_psp_09241BF8(void) {
    func_913D618();
    D_psp_09285EE0 = 0;
    D_psp_09285ED8 = 0;
    D_psp_09285ED0 = 0;
    D_psp_09285EC8 = 0;
}

s32 func_psp_09241C38(s32 arg0) { return 0; }

void func_psp_09241C50(s32 port, s32 slot, s32 slotValue) {
    SaveData* save;
    s32 flags;

    g_SaveSummary[port].slot[slot] = slotValue;
    save = (SaveData*)g_Pix;
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
    if (save->info.saveSize != 0x11C8) {
        save->info.endGameFlags = 0;
    }
    g_SaveSummary[port].kind[slot] = save->info.endGameFlags;
    g_SaveSummary[port].character[slot] = save->info.character;
    STRCPY(g_SaveSummary[port].name[slot], save->info.name);
    g_IsTimeAttackUnlocked |= save->info.endGameFlags;
}

void func_psp_09241F70(void) {
    s32 i;

    D_psp_09285EC0 = 0;
    for (i = 0; i < 0xF; i++) {
        g_SaveSummary[0].icon[i] = -1;
        g_SaveSummary[1].icon[i] = -1;
        g_SaveSummary[0].slot[i] = -3;
        g_SaveSummary[1].slot[i] = -3;
    }
}

s32 func_psp_09242010(void) {
    char saveFile[0x20];
    s32 slot;
    s32 port;
    s32 var_s1;
    s32 i;

    FntPrint(
        D_psp_09285510, D_psp_09285EC0, D_psp_09285EB8); // sotn-lint-ignore
    FntPrint(D_psp_09285520, D_psp_09285EA8);            // sotn-lint-ignore
    port = D_psp_09285EB8 / 15;
    slot = D_psp_09285EB8 % 15;

    switch (D_psp_09285EC0) {
    case 0:
        g_IsTimeAttackUnlocked = 0;
        func_913D618();
        D_psp_09285EA8 = 0;
        D_psp_09285EC0++;
        break;

    case 1:
        D_psp_0928628C = func_913D9B0(0, 0);
        if (D_psp_0928628C != 0) {
            if (D_psp_0928628C == -1 && D_psp_09285EA8-- != 0) {
                D_psp_0928628C = 0;
            } else if (D_psp_0928628C == -3 && D_psp_09285EA8-- != 0) {
                D_psp_0928628C = 0;
            } else {
                func_913D618();
                D_psp_09285EA8 = 0;
                D_psp_09285EC0++;
            }
        }
        break;

    case 2:
        D_psp_09286634 = func_913D9B0(1, 0);
        if (D_psp_09286634 != 0) {
            if (D_psp_09286634 == -1 && D_psp_09285EA8-- != 0) {
                D_psp_09286634 = 0;
            } else if (D_psp_09286634 == -3 && D_psp_09285EA8-- != 0) {
                D_psp_09286634 = 0;
            } else {
                func_913D618();
                D_psp_09285EC0++;
            }
        }
        break;

    case 3:
        var_s1 = func_913D640(0, 0);
        if (var_s1 >= 0) {
            var_s1 = func_psp_09241C38(0);
            for (i = 0; i < 0xF; i++) {
                func_913E468(saveFile, i);
                func_913D700(0, saveFile, i);
                g_SaveSummary[0].icon[i] = -3;
                if (i >= (0xF - var_s1)) {
                    g_SaveSummary[0].icon[i] = -2;
                }
            }
            func_913D618();
            D_psp_09285EC0++;
        }
        break;

    case 4:
        var_s1 = func_913D640(1, 0);
        if (var_s1 >= 0) {
            var_s1 = func_psp_09241C38(1);
            for (i = 0; i < 0xF; i++) {
                func_913E468(saveFile, i);
                func_913D700(1, saveFile, i);
                g_SaveSummary[1].icon[i] = -3;
                if (i >= (0xF - var_s1)) {
                    g_SaveSummary[1].icon[i] = -2;
                }
            }
            func_913D618();
            D_psp_09285EB8 = 0;
            D_psp_09285EB0 = 0;
            D_psp_09285EA8 = 0;
            D_psp_09285EC0++;
        }
        break;

    case 5:
        if (func_913D798(port, slot) == 0) {
            D_psp_09285EB8++;
            if (D_psp_09285EB8 == 0x1E) {
                D_psp_09285EC0 += 2;
            }
            if (D_psp_09285EB8 == 0xF) {
                D_psp_09285EB0 = 0;
            }
        } else {
            func_913E468(saveFile, slot);
            var_s1 = func_913D7D8(port, 0, saveFile, g_Pix, 0);
            if (var_s1 != 0) {
                if (D_psp_09285EA8-- == 0) {
                    D_psp_09285EC0 = 0;
                }
            } else {
                D_psp_09285EC0++;
            }
        }
        break;

    case 6:
        var_s1 = func_913D998(port);
        if (var_s1 != 0) {
            if (var_s1 == -3) {
                if (D_psp_09285EA8-- == 0) {
                    D_psp_09285EC0 = 0;
                } else {
                    D_psp_09285EC0--;
                }
            } else {
                func_psp_09241C50(port, D_psp_09285EB0, slot);
                D_psp_09285EB0++;
                D_psp_09285EA8 = 0;
                D_psp_09285EB8++;
                if (D_psp_09285EB8 == 0x1E) {
                    D_psp_09285EC0++;
                } else {
                    if (D_psp_09285EB8 == 0xF) {
                        D_psp_09285EB0 = 0;
                    }
                    D_psp_09285EC0--;
                }
            }
        }
        break;

    case 7:
        return 1;
    }
    return 0;
}

void func_psp_092426B0(s32 arg0) {
    D_psp_09285EC0 = 0;
    D_psp_09285EB8 = arg0;
}

s32 func_psp_092426D8(void) {
    char saveFile[0x20];
    s32 port;
    s32 slot;
    s32 blockId;
    s32 temp_s0;

    FntPrint(
        D_psp_09285510, D_psp_09285EC0, D_psp_09285EB8); // sotn-lint-ignore
    FntPrint(D_psp_09285520, D_psp_09285EA8);            // sotn-lint-ignore
    port = D_psp_09285EB8 / 15;
    slot = D_psp_09285EB8 % 15;
    blockId = g_SaveSummary[port].slot[slot];
    switch (D_psp_09285EC0) {
    case 0:
        func_913D618();
        D_psp_09285EA8 = 0;
        D_psp_09285EC0 = 3;
        break;

    case 3:
        func_913E468(saveFile, blockId);
        temp_s0 = func_913D7D8(port, 0, saveFile, g_Pix[0], 1);
        if (temp_s0 != 0) {
            if (D_psp_09285EA8-- == 0) {
                return -1;
            }
        } else {
            D_psp_09285EC0++;
        }
        break;

    case 4:
        temp_s0 = func_913D998(port);
        if (temp_s0 != 0) {
            if (temp_s0 == -3) {
                if (D_psp_09285EA8-- == 0) {
                    return -1;
                }
                D_psp_09285EC0--;
            } else {
                temp_s0 = func_913E220(g_Pix[0]);
                if (temp_s0 < 0) {
                    return -2;
                } else {
                    return 1;
                }
            }
        }
        break;
    }
    return 0;
}

void func_psp_09242920(s32 arg0, s32 arg1) {
    s32 j;
    s32 i;
    s32 n;

    D_psp_09285EC0 = 0;
    D_psp_09285EA0 = arg0 / 15;
    n = arg0 % 15;
    D_psp_09285E98 = g_SaveSummary[D_psp_09285EA0].slot[n];
    D_psp_09285E90 = arg1 / 15;
    n = arg1 % 15;
    D_psp_09285E80 = n;
    D_psp_09285E88 = g_SaveSummary[D_psp_09285E90].slot[n];
    if (g_SaveSummary[D_psp_09285E90].icon[n] == -3) {
        for (i = 0; i < 0xF; i++) {
            for (j = 0; j < 0xF; j++) {
                if ((g_SaveSummary[D_psp_09285E90].icon[j] >= 0) &&
                    (g_SaveSummary[D_psp_09285E90].slot[j] == i)) {
                    break;
                }
            }
            if (j == 0xF) {
                D_psp_09285E88 = i;
                return;
            }
        }
    }
}

void func_psp_09242B40(s32 arg0, s32 arg1) {
    D_psp_09285EC0 = 0;
    D_psp_09285EA0 = arg0;
    D_psp_09285E98 = arg1;
    D_psp_09285E90 = arg0;
    D_psp_09285E80 = arg1;
    D_psp_09285E88 = arg1;
}

s32 func_psp_09242BA0(s32 arg0) {
    char saveFile[0x20];
    s32 var_s0;
    SaveData* save;
    u32 var_s3;
    u32 var_s2;

    FntPrint(D_psp_09285530, D_psp_09285EC0,
             D_psp_09285E98 + (D_psp_09285EA0 * 0xF),
             D_psp_09285E88 + (D_psp_09285E90 * 0xF)); // sotn-lint-ignore
    FntPrint(D_psp_09285520, D_psp_09285EA8);          // sotn-lint-ignore
    switch (D_psp_09285EC0) {
    case 0:
        func_913D618();
        D_psp_09285EA8 = 0;
        D_psp_09285EC0++;
        break;

    case 1:
        func_913E468(saveFile, D_psp_09285E98);
        var_s0 = func_913D7D8(D_psp_09285EA0, 0, saveFile, g_Pix, 1);
        if (var_s0 != 0) {
            if (D_psp_09285EA8-- == 0) {
                return -1;
            }
        } else {
            D_psp_09285EC0++;
        }
        break;

    case 2:
        var_s0 = func_913D998(D_psp_09285EA0);
        if (var_s0 != 0) {
            if (var_s0 == -3) {
                if (D_psp_09285EA8-- == 0) {
                    return -1;
                }
                D_psp_09285EC0--;
            } else {
                save = (SaveData*)g_Pix;
                if (arg0 != 0) {
                    if (arg0 == 1) {
                        save->info.endGameFlags |= 1;
                    } else {
                        STRCPY(save->info.name, arg0);
                        STRCPY(save->status.saveName, arg0);
                    }
                }
                func_913E220(g_Pix);
                func_913DB20(g_Pix, D_psp_09285E80, save->info.cardIcon);
                D_psp_09285EA8 = 0;
                D_psp_09285EC0++;
            }
        }
        break;

    case 3:
        if (g_SaveSummary[D_psp_09285E90].icon[D_psp_09285E80] >= 0) {
            var_s3 = 0;
        } else {
            var_s3 = 1;
        }
        func_913E468(saveFile, D_psp_09285E88);
        if (D_psp_09285E88 == func_8919560()) {
            var_s2 = 1;
        } else {
            var_s2 = 0;
        }
        var_s0 =
            func_913D890(D_psp_09285E90, 0, saveFile, g_Pix, 1, var_s3, var_s2);
        if (var_s0 != 0) {
            if (D_psp_09285EA8-- == 0) {
                return -3;
            }
        } else {
            D_psp_09285EC0++;
        }
        break;

    case 4:
        var_s0 = func_913D998(D_psp_09285E90);
        if (var_s0 != 0) {
            if (var_s0 == -3) {
                if (D_psp_09285EA8-- == 0) {
                    return -3;
                }
                D_psp_09285EC0--;
            } else {
                func_psp_09241C50(
                    D_psp_09285E90, D_psp_09285E80, D_psp_09285E88);
                return 1;
            }
        }
        break;
    }
    return 0;
}

void func_psp_09243000(s32 arg0) {
    D_psp_09285EC0 = 0;
    D_psp_09285EB8 = arg0;
}

s32 func_psp_09243028(void) {
    char saveFile[0x20];
    s32 var_s2;
    s32 port;
    s32 slot;
    s32 blockId;
    s32 var_s3;

    port = D_psp_09285EB8 / 15;
    slot = D_psp_09285EB8 % 15;
    blockId = g_SaveSummary[port].slot[slot];
    switch (D_psp_09285EC0) {
    case 0:
        func_913D618();
        D_psp_09285EA8 = 0;
        D_psp_09285EC0++;
        break;

    case 1:
        func_913E468(saveFile, blockId);
        if (slot == func_8919560()) {
            var_s2 = 1;
        } else {
            var_s2 = 0;
        }
        var_s3 = func_913D930(port, 0, saveFile, var_s2);
        if (var_s3 != 0) {
            if (D_psp_09285EA8-- == 0) {
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
