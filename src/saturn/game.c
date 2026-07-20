// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "game.h"
#include "lib/scl.h"

void PlaySfx(s32 sfxId);

bool func_800F27F4(s32 arg0) {
    if (arg0 == 0) {
        if (g_unkGraphicsStruct.D_800973FC != 0 || D_8006BB00 != 0) {
            return false;
        }
        if (D_8003C708.flags & (FLAG_UNK_40 | FLAG_UNK_20)) {
            return false;
        }
        D_801375C8 = 1;
        return true;
    }
    D_801375C8 = 8;
}

void func_800F2860(void) {
    switch (D_801375C8) {
    case 0:
        break;
    case 1:
        PlaySfx(SET_UNK_80);
        D_801375C8++;
        break;
    case 2:
        if (func_80131F68() == 0) {
            D_801375C8++;
        }
        break;
    case 3:
        PlaySfx(0xE0000120);
        D_801375C8++;
        break;
    case 4:
        if (func_80131F68() != 0) {
            D_801375C8++;
        }
        break;
    case 5:
        if (func_80131F68() == 0) {
            D_801375C8++;
        }
        break;
    case 6:
        PlaySfx(currentMusicId);
        D_801375C8 = 0;
        break;
    case 7:
        if (func_80131F68() == 0) {
            D_801375C8--;
        }
        break;
    case 8:
        PlaySfx(SET_UNK_80);
        D_801375C8--;
        break;
    }
}

// RunMainEngine
INCLUDE_ASM("asm/saturn/game/f_match", f6070A60, RunMainEngine);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6071C3C, func_06071C3C);

extern s32 DAT_0605c120;
extern s32 g_PlayerY;
extern s32 D_80097C98;
extern s32 DAT_0605c668;
extern s32 DAT_0605cd54;
extern s32 g_PlayerX;
extern Unk0605cd70 DAT_0605cd70;
extern s32 DAT_0605ceb0;
extern s32 DAT_0605d7dc;
extern s32 DAT_060860bc;
extern s32 DAT_060860c0;
extern s32 D_801375A8;
extern s32 D_801375A0;
extern RoomLoadDefHolder D_801375BC;
extern s32 D_8013759C;
extern s32 D_801375A4;

void FUN_060666a4(s32);
void SetDefaultSCLPriority(s32);
void FUN_0606d358(s32);
void func_0600ff08(void);
void func_06009510(s32);

// original name: INIT_ROOM
void InitRoom(void) {
    u16 uVar9;
    u32 i;
    Entity* ent;
    Primitive* prim;

    if (DAT_0605d750.unk4 < 0x50) {
        D_8003C708.flags = 0;
    }
    DAT_0605c668 = 1;
    DAT_0605ceb0 = 0;
    Scl_w_reg.win1_start[0] = 0;
    Scl_w_reg.win1_start[1] = 0;
    Scl_w_reg.win1_end[0] = 0;
    Scl_w_reg.win1_end[1] = 0;
    Scl_w_reg.wincontrl[0] = 0x8383;
    SclProcess = 1;
    func_0600ff08();
    if (DAT_0605d750.unk4 < 0x50) {
        D_801375BC.def =
            (RoomLoadDef*)FUN_0606d804(DAT_0605d750.stageID & 0xDF);
        D_801375BC.def =
            (RoomLoadDef*)((u8*)D_801375BC.def + DAT_0605d750.unk4 * 6 + 4);
    }
    D_8013759C = PLAYER.posX.val;
    D_801375A0 = PLAYER.posY.val;
    PLAYER.posX.i.hi = D_801375BC.pos.x + g_Tilemap.scrollX.i.hi;
    PLAYER.posY.i.hi = D_801375BC.pos.y + g_Tilemap.scrollY.i.hi;
    DAT_060860bc = 0;
    DAT_060860c0 = 0;
    FUN_0606d358(1);
    uVar9 = DAT_0605d750.stageID & 0xDF;
    if ((uVar9 == 6 || uVar9 == 11 || uVar9 == 9 || uVar9 == 3) &&
        DAT_0605d750.unkA != DAT_0605d750.unk8) {
        DAT_0605d750.unkA = DAT_0605d750.unk8;
    } else {
        DAT_0605d7dc = DAT_0605c120;
    }
    func_06009510(DAT_0605d750.unk4);
    PLAYER.posX.i.hi = PLAYER.posX.i.hi % 0x140;
    PLAYER.posY.i.hi = PLAYER.posY.i.hi % 0x100;

    g_Tilemap.left = (D_801375BC.def - 1)->tileLayoutId;
    g_Tilemap.top = (D_801375BC.def - 1)->tilesetId;
    g_Tilemap.right = (D_801375BC.def - 1)->objGfxId;
    g_Tilemap.bottom = (D_801375BC.def - 1)->objLayoutId;

    g_Tilemap.hSize = g_Tilemap.right - g_Tilemap.left + 1;
    g_Tilemap.vSize = g_Tilemap.bottom - g_Tilemap.top + 1;
    g_Tilemap.x = ((D_801375BC.def - 1)->tileLayoutId - g_Tilemap.left) * 0x140;
    g_Tilemap.y = ((D_801375BC.def - 1)->tilesetId - g_Tilemap.top) * 0x100;
    g_Tilemap.width =
        ((D_801375BC.def - 1)->objGfxId - g_Tilemap.left + 1) * 0x140;
    g_Tilemap.height =
        ((D_801375BC.def - 1)->objLayoutId - g_Tilemap.top + 1) * 0x100;
    g_Tilemap.scrollX.i.hi = (DAT_0605d750.unkC - g_Tilemap.left) * 0x140;
    g_Tilemap.scrollY.i.hi = (DAT_0605d750.unk10 - g_Tilemap.top) * 0x100;
    g_PlayerX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
    g_PlayerY = PLAYER.posY.i.hi + g_Tilemap.scrollY.i.hi;
    func_800F0CD8(0);
    func_06064608();
    if (PLAYER.posX.val < 0) {
        PLAYER.posX.val = 0;
        PLAYER.posX.i.lo = 0;
        PLAYER.posX.i.hi = 0;
    }
    if (PLAYER.posY.val < 0) {
        PLAYER.posY.val = 0;
        PLAYER.posY.i.lo = 0;
        PLAYER.posY.i.hi = 0;
    }

    g_PlayerX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
    g_PlayerY = PLAYER.posY.i.hi + g_Tilemap.scrollY.i.hi;
    func_800F0CD8(0);
    D_801375A4 = D_8013759C - PLAYER.posX.val;
    D_801375A8 = D_801375A0 - PLAYER.posY.val;
    for (i = 0, ent = g_Entities; i < 0x100; i++, ent++) {
        if (ent->flags & FLAG_UNK_20000) {
            ent->posX.val -= D_801375A4;
            ent->posY.val -= D_801375A8;
        }
    }
    D_801375A4 = D_801375A4 >> 16;
    D_801375A8 = D_801375A8 >> 16;
    for (i = 0, prim = &g_PrimBuf[0]; i < 0x200; i++, prim++) {
        if ((prim->drawMode & DRAW_UNK_100) &&
            (prim->drawMode != DRAW_INVALID)) {
            switch (prim->type & 0xF) {
            case 2:
            case 3:
            case 4:
                prim->x3 -= D_801375A4;
                prim->y3 -= D_801375A8;
                prim->x2 -= D_801375A4;
                prim->y2 -= D_801375A8;
            case 5:
                prim->x1 -= D_801375A4;
                prim->y1 -= D_801375A8;
            case 0:
            case 1:
                prim->x0 -= D_801375A4;
                prim->y0 -= D_801375A8;
            }
        }
    }
    if (DAT_0605d750.stageID != 0x2B) {
        for (i = 0; i < 8; i++) {
            g_unkGraphicsStruct.D_80097428[i] = 0;
        }
        func_800F0CD8(0);
        func_800F0CD8(0);
        for (i = 0; i < 8; i++) {
            g_unkGraphicsStruct.D_80097428[i] = 0;
        }
    }

    if (D_80097C98 == 2) {
        D_80097C98 = 3;
    } else {
        D_80097C98 = 0;
    }
    DAT_0605c680.unk4 = DAT_0605c680.unk8 = g_Tilemap.scrollX.i.hi << 0x10;
    DAT_0605c680.unkC = DAT_0605c680.unk10 = g_Tilemap.scrollY.i.hi << 0x10;
    DAT_0605c680.g_ScrollDeltaX = 0;
    DAT_0605c680.g_ScrollDeltaY = 0;
    DAT_0605c680.unk3C = DAT_0605c680.unk8;
    DAT_0605c680.unk34 = DAT_0605c680.unk4;
    DAT_0605c680.unk40 = DAT_0605c680.unkC;
    DAT_0605c680.unk38 = DAT_0605c680.unk10;
    SetDefaultSCLPriority(0);
    func_800F0CD8(0);
    func_800F0CD8(0);
    FUN_060666a4(DAT_0605d750.unk4);
    FUN_0606c160();
    FUN_0606c160();
    DAT_0605cd70.unk0++;
    if ((DAT_0605d750.unk6 == 0x50) || (DAT_0605d750.unk6 == 0x60)) {
        if (g_unkGraphicsStruct.D_800973FC == 0) {
            PlaySfx(FUN_060727dc(
                g_PlayableCharacter, DAT_0605d750.stageID, DAT_0605d750.unk4));
        } else {
            currentMusicId = FUN_060727dc(
                g_PlayableCharacter, DAT_0605d750.stageID, DAT_0605d750.unk4);
            DAT_0605cd54 = 1;
        }
    }
    if ((DAT_0605d750.unk4 == 0x50) || (DAT_0605d750.unk4 == 0x60)) {
        if (func_06012dfc() != 0) {
            PlaySfx(SET_STOP_MUSIC);
        }
        if ((g_unkGraphicsStruct.D_800973FC != 0) && (D_8006BB00 != 0)) {
            if (DAT_0605d750.unk4 == 0x50) {
                PlaySfx(SET_STOP_MUSIC);
                DAT_0605cd54 = 1;
            }
        } else {
            PlaySfx(SET_UNK_80);
        }
    }
}

extern u8* DAT_060645b8;

// original name: SET_DEFAULT_SCL_PRIORITY
void SetDefaultSCLPriority(s32 arg0) {
    u8* ptr;

    if (DAT_0605d750.unk4 < 0x20) {
        ptr = &DAT_060645b8[DAT_0605d750.unk4 * 12];
        SCL_SetPriority(0x4, ptr[0]);
        SCL_SetPriority(0x8, ptr[1]);
        SCL_SetPriority(0x10, ptr[2]);
        SCL_SetPriority(0x20, ptr[3]);
        SCL_SetPriority(0x100, ptr[4]);
        SCL_SetPriority(0x200, ptr[5]);
        SCL_SetPriority(0x400, ptr[6]);
        SCL_SetPriority(0x800, ptr[7]);
        SCL_SetPriority(0x1000, ptr[8]);
        SCL_SetPriority(0x2000, ptr[9]);
        SCL_SetPriority(0x4000, ptr[10]);
        SCL_SetPriority(0x8000, ptr[11]);
    } else {
        SCL_SetPriority(0x4, 7);
        SCL_SetPriority(0x8, 4);
        SCL_SetPriority(0x10, 2);
        SCL_SetPriority(0x20, 3);
        SCL_SetPriority(0x100, 3);
        SCL_SetPriority(0x200, 1);
        SCL_SetPriority(0x400, 2);
        SCL_SetPriority(0x800, 3);
        SCL_SetPriority(0x1000, 4);
        SCL_SetPriority(0x2000, 6);
        SCL_SetPriority(0x4000, 7);
        SCL_SetPriority(0x8000, 0);
    }
    SCL_SetColMixMode(6, 1);
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f60727DC, func_060727DC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607284C, func_0607284C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60728B4, func_060728B4);

// _INIT_GAME_OVER
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6072BCC, func_06072BCC);

// _GAMEOVER_FADEIN
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6072C04, func_06072C04);

extern u8 DAT_06057f68;
extern u16 DAT_0605becc;
extern s16 DAT_0605c110;
extern s32 DAT_0605c664;
extern s32 DAT_0605c6e4;
extern s32 DAT_0605d7f0;
extern s32 D_06085534;
extern s32 DAT_06085d5c;
extern s32 DAT_06085d60;
extern s32 DAT_06085d64;
extern s32 prevMusicId;
extern s32 DAT_06086258;
extern s32 DAT_06086270;
extern s32 DAT_06086288;
extern s32 DAT_0608629c;

void func_06073280(void);
void UpdateCapePalette(void);
void func_06005208(s32);
void func_06008D04(s32, s32);
void CheckWeaponCombo(void);
void make_all(void);

// original name: SUB_DISP
void SubDisp(void) {
    switch (DAT_06057f68) {
    case 1:
        if (DAT_0605cd70.unk0 == 0x14) {
            func_06008D04(1, 0x28);
        } else {
            func_06008D04(1, 0xF);
        }
        DAT_06057f68++;
        break;
    case 2:
        if (DAT_0605becc == 0) {
            DAT_06057f68++;
        }
        break;
    case 4:
        if (DAT_0605cd70.unk0 == 0x17) {
            func_06008D04(0, 0x28);
        } else {
            func_06008D04(0, 0xF);
        }
        DAT_06057f68++;
        break;
    case 5:
        if (DAT_0605becc == 0) {
            DAT_06057f68++;
        }
        break;
    }
    if ((g_PlayableCharacter == 0) && (DAT_0605becc == 0) &&
        (DAT_0605cd70.unk0 > 3) && (DAT_0605d7f0 == 0)) {
        if ((g_pads[0].previous & 0x800) && (DAT_06086270 == 0) &&
            (DAT_0605cd70.unk0 < 0x14)) {
            if (CheckIfAllButtonsAreAssigned()) {
                D_06085534 = 0x70;
                DAT_06057f68 = 4;
                DAT_06086270 = 1;
            } else {
                goto LAB_06072d9e;
            }
        }
        if ((DAT_06086270 == 1) && (DAT_06057f68 == 6)) {
            DAT_06086270 = 2;
            DAT_0605cd70.unk8 = 0;
            DAT_06057f68 = 0;
            func_06073280();
            DAT_0605cd70.unk0 = 0x70;
            DAT_0605d7f0 = 1;
        }
    }
LAB_06072d9e:
    switch (DAT_0605cd70.unk0) {
    case 0:
        DAT_06086270 = 0;
    case 1:
    case 2:
        prevMusicId = currentMusicId;
        currentMusicId = 0;
        DAT_0605cd70.unk0 += 3;
    case 3:
        func_06064628(g_PlayableCharacter);
        if (g_PlayableCharacter == 0) {
            DAT_06085d5c = g_Settings.windowColors[0];
            DAT_06085d60 = g_Settings.windowColors[1];
            DAT_06085d64 = g_Settings.windowColors[2];
        } else {
            DAT_06086258 = 0;
        }
        break;
    case 6:
        func_0606464C();
        break;
    case 7:
        func_06064590();
        break;
    case 8:
        func_06064630();
        break;
    case 9:
        func_060645C0();
        break;
    case 10:
        func_06064618();
        break;
    case 11:
        func_060645A0();
        break;
    case 20:
        if (DAT_06057f68 == 0) {
            func_06064594();
            DAT_06057f68 = 1;
        } else {
            func_060645B4();
            if (DAT_06057f68 == 3) {
                DAT_0605cd70.unk0++;
                DAT_06057f68 = 0;
            }
        }
        break;
    case 21:
        func_060645B4();
        if (DAT_0605cd70.unk0 == 0x16) {
            D_06085534 = 0x70;
            DAT_0605d7f0 = 1;
            DAT_06057f68 = 4;
            if (g_PlayableCharacter != 0) {
                DAT_06086258 = 1;
            }
        } else if (DAT_0605cd70.unk0 == 0x17) {
            if (g_PlayableCharacter == 0) {
                D_06085534 = 6;
                DAT_06057f68 = 4;
                DAT_0605cd70.unk8 = 0;
            } else {
                D_06085534 = 0x70;
                DAT_0605d7f0 = 1;
                DAT_06057f68 = 4;
                DAT_06086258 = 2;
            }
        }
        break;
    case 22:
        if (DAT_06057f68 == 6) {
            DAT_06057f68 = 0;
            DAT_0605cd70.unk0 = D_06085534;
            func_06073280();
        } else {
            func_060645B4();
        }
        break;
    case 23:
        if (DAT_06057f68 == 6) {
            DAT_0605cd70.unk0 = D_06085534;
            DAT_0605cd70.unk8 = 0;
            if (g_PlayableCharacter != 0) {
                func_06073280();
            }
        } else {
            func_060645B4();
        }
        break;
    case 0x70:
        if (g_PlayableCharacter == 0) {
            CheckWeaponCombo();
            make_all();
            DAT_0605c680.unk4 = DAT_06086288;
            DAT_0605c680.unkC = DAT_0608629c;
        }
        func_06005328();
        DAT_0605cd70.unk0++;
        break;
    case 0x71:
        currentMusicId = prevMusicId;
        if ((g_PlayableCharacter == 0) && func_060743B8(0)) {
            break;
        }
        DAT_0605cd70.unk0++;
        DAT_0605d7f0 = 1;
        break;
    case 0x72:
        if ((g_PlayableCharacter == 0) && func_060743B8(1)) {
            break;
        }
        func_06005208(1);
        if (g_PlayableCharacter == 0) {
            UpdateCapePalette();
            PlaySfx(SET_UNPAUSE_SFX_SCRIPTS);
            PlaySfx(SET_KEY_ON_20_21);
            PlaySfx(SET_KEY_ON_22_23);
        }
        DAT_0605c6e4 = 0;
        DAT_0605c110 = 0;
        DAT_06086270 = 0;
        DAT_06057f68 = 0;
        DAT_0605c664 = 0;
        break;
    }
}

extern s16 g_ButtonMask[];

bool CheckIfAllButtonsAreAssigned(void) {
    s32 buf[9];
    s32 i;
    s32 bitMask_Assigned;
    s32* buttonConfig;

    for (i = 0; i < 9; i++) {
        buf[i] = 0;
    }

    buttonConfig = g_Settings.buttonConfig;
    for (i = 0; i < 8; i++) {
        buf[*buttonConfig++] = 1;
    }

    for (i = 0; i < 9; i++) {
        if (buf[i] == 0) {
            g_Settings.buttonConfig[8] = i;
            break;
        }
    }

    for (i = 0; i < 9; i++) {
        g_Settings.buttonMask[i] = g_ButtonMask[g_Settings.buttonConfig[i]];
    }

    bitMask_Assigned = 0;
    buttonConfig = g_Settings.buttonConfig;
    for (i = 0; i < 9; i++) {
        bitMask_Assigned |= 1 << *buttonConfig++;
    }
    if (bitMask_Assigned == 0xFF) {
        return true;
    } else {
        return false;
    }
}

void func_0600971C(void);
extern s16 DAT_0605d772;
extern s16 DAT_06065470;
extern s16 DAT_060862a4;

void func_06073280(void) {
    if (g_PlayableCharacter == 0) {
        UpdateCapePalette();
    }
    DAT_0605d772 = 8;
    func_060645B0();
    DAT_06065470 |= DAT_060862a4;
    SclProcess = 1;
    func_0600971C();
}

extern s16 DAT_06086220[];

void func_06074278(s32);

// original name: INIT_SUB_GAMEN
void func_060732E4(s32 arg0) {
    s16 sVar3;
    s32 i;

    switch (arg0) {
    case 7:
        func_06064638();
        for (i = 0; i < 10; i++) {
            DAT_06086220[i] = 0x7E + i * 14;
        }
        func_06074278(0);
        break;
    case 8:
        func_060645FC();
        func_06074278(0);
        break;
    case 9:
        func_060645BC();
        func_06074278(0);
        break;
    case 10:
        func_06064620();
        func_06009570(3);
        func_06074278(1);
        break;
    case 11:
        func_06064600();
        func_06009570(4);
        func_06074278(1);
        break;
    }
    DAT_06057f68 = 1;
}

extern s32 g_MenuPageScrollActive;

// original name: PSX_cursor_up_down
void MenuHandleCursorInput(s32* nav, u8 nOptions, u32 type) {
    u8 prevCursor = *nav;

    switch (type) {
    case 3: // vertical clamp
        if (g_pads[0].repeat & PAD_UP) {
            if (*nav) {
                *nav -= 1;
            }
        }
        if (g_pads[0].repeat & PAD_DOWN) {
            if (*nav != nOptions - 1) {
                *nav += 1;
            }
        }
        break;
    case 0: // vertical loop
        if (g_pads[0].repeat & PAD_UP) {
            *nav -= 1;
            if (*nav == -1) {
                *nav = nOptions - 1;
            }
        }
        if (g_pads[0].repeat & PAD_DOWN) {
            *nav += 1;
            if (*nav == nOptions) {
                *nav = 0;
            }
        }
        break;
    case 4: // horizontal clamp
        if (g_pads[0].repeat & PAD_LEFT) {
            if (*nav) {
                *nav -= 1;
            }
        }
        if (g_pads[0].repeat & PAD_RIGHT) {
            if (*nav != nOptions - 1) {
                *nav += 1;
            }
        }
        break;
    case 5: // horizontal loop
        if (g_pads[0].repeat & PAD_LEFT) {
            *nav -= 1;
            if (*nav == -1) {
                *nav = nOptions - 1;
            }
        }
        if (g_pads[0].repeat & PAD_RIGHT) {
            *nav += 1;
            if (*nav == nOptions) {
                *nav = 0;
            }
        }
        break;
    case 1:
    case 2:
        if (g_pads[0].repeat & PAD_UP) {
            if (*nav >= 2) {
                *nav -= 2;
            }
        } else if (g_pads[0].repeat & PAD_DOWN) {
            if (*nav == nOptions - 2) {
                if (*nav & 1) {
                    *nav += 1;
                }
            }
            if (*nav < nOptions - 2) {
                *nav += 2;
            }
        }
        if (g_pads[0].repeat & (PAD_LEFT | PAD_RIGHT)) {
            *nav ^= 1;
            if (*nav == nOptions) {
                *nav ^= 1;
            }
        }
        if ((type == 2) && (g_MenuPageScrollActive == 0)) {
            if (g_pads[0].repeat & PAD_L1) {
                if (*nav >= 10) {
                    *nav -= 10;
                } else {
                    *nav = 0;
                }
            }
            if (g_pads[0].repeat & PAD_R1) {
                if (*nav < nOptions - 10) {
                    *nav += 10;
                } else {
                    *nav = nOptions - 1;
                }
            }
        }
        break;
    }
    if (prevCursor != *nav) {
        PlaySfx(SFX_UI_MOVE);
    }
}

// SAT: func_0607356C
bool func_800FB1EC(s32 arg0) {
    if (D_801375CC == EQUIP_HAND) {
        if (arg0 == 0) {
            return true;
        }
    } else if ((arg0 == 0x1A) || (arg0 == 0) || (arg0 == 0x30) ||
               (arg0 == 0x3A)) { // 3A instead of 39
        return true;
    }

    return false;
}

extern s32 g_NewPlayerStatsTotal[];
extern s32 g_NewAttackRightHand;
extern s32 g_NewAttackLeftHand;
extern s32 g_NewDefenseEquip;

// SAT: func_060735A4
void func_800F7244(void) {
    s32 i;

    g_NewAttackRightHand = g_Status.attackHands[0];
    g_NewAttackLeftHand = g_Status.attackHands[1];
    g_NewDefenseEquip = g_Status.defenseEquip;
    for (i = 0; i < 4; i++) {
        g_NewPlayerStatsTotal[i] =
            g_Status.statsBase[i] + g_Status.statsEquip[i];
    }
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607360C, func_0607360C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607369C, func_0607369C);

typedef struct EquipMenuHelper {
    s32 equipTypeFilter;
    s32 index;
    s32 isAccessory;
} EquipMenuHelper;

extern EquipMenuHelper g_EquipMenuHelper[];

// original name : PSX_id_init
void func_800FB0FC(void) {
    EquipMenuHelper* helper = &g_EquipMenuHelper[g_MenuNavigation.cursorEquip];

    D_801375CC = helper->equipTypeFilter;
    D_801375D4 = helper->index;
    func_800FAF44(helper->isAccessory);
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607371C, func_0607371C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6073740, func_06073740);

// _goto_equip
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6073770, func_06073770);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60737A0, func_060737A0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6073E58, func_06073E58);

// _PSX_sort_item
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6073EEC, func_06073EEC);

// original name: PSX_equip_id_init
void func_800FAF44(bool isAccessory) {
    s32 i;
    s32* ptr;

    D_801375D8 = (s32*)0x002F2000;
    ptr = (s32*)0x002F2000;

    if (!isAccessory) {
        for (i = 0; i < 0xB0; i++) {
            *ptr++ = i;
        }
    } else {
        for (i = 0; i < 0x5C; i++) {
            if (g_AccessoryDefs[i].equipType == D_801375D4) {
                *ptr++ = i;
            }
        }
    }
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074048, func_06074048);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074068, func_06074068);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60740F8, func_060740F8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074278, func_06074278);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60743B8, func_060743B8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074470, func_06074470);

// _EVENT_SCL_TRANS
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60744F8, func_060744F8);

// _SS_MOJI_SET
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60745A0, func_060745A0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074698, func_06074698);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074700, func_06074700);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074724, func_06074724);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074964, func_06074964);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60749F8, func_060749F8);

extern u16 g_JosephsCloakColors[4];
u16* func_06074A98(void) { return g_JosephsCloakColors; }

INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074AA8, func_06074AA8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074BF4, func_06074BF4);

void func_06074C28(void) {
    g_Status.equipment[0] = 0xA6;
    g_Status.equipment[1] = 0x10;
    g_Status.subWeapon = 0;
    g_Status.hpMax = g_Status.hp = 300;
    g_Status.mpMax = g_Status.mp = 1000;
    g_Status.equipment[3] = 0x2F;
    g_Status.equipment[4] = 0xF;
    g_Status.equipment[5] = 0x39;
    g_Status.equipment[6] = 0x50;
    g_Status.equipment[7] = 0x48;
}
