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
        if (func_06012DD0() == 0) {
            D_801375C8++;
        }
        break;
    case 3:
        PlaySfx(0xE0000120);
        D_801375C8++;
        break;
    case 4:
        if (func_06012DD0() != 0) {
            D_801375C8++;
        }
        break;
    case 5:
        if (func_06012DD0() == 0) {
            D_801375C8++;
        }
        break;
    case 6:
        PlaySfx(currentMusicId);
        D_801375C8 = 0;
        break;
    case 7:
        if (func_06012DD0() == 0) {
            D_801375C8--;
        }
        break;
    case 8:
        PlaySfx(SET_UNK_80);
        D_801375C8--;
        break;
    }
}

extern u16 DAT_0605becc;
extern s32 D_8006C374;
extern s16 DAT_0605c110;
extern u16 D_8003C730;
extern s32 g_PlayerY;
extern s32 D_80097C98;
extern s32 DAT_0605c664;
extern s32 DAT_0605C6D4;
extern s32 stopMusicFlag;
extern s32 g_PlayerX;
extern u16 DAT_0605cea2;
extern s32 DAT_0605ceb0;
extern u16 DAT_0605D744;
extern s16 DAT_0605d772;
extern s32 DAT_0605d7f0;
extern s32 DAT_06085508;
extern s32 DAT_0608550C;
extern s32 DAT_06085520;
extern u16 DAT_06085528;
extern s32 DAT_0608552C;
extern s32 DAT_06085530;
extern u16 DAT_060860AC;
extern s32 D_801375AC;
extern s32 D_801375B0;
extern s32 D_801375B4;
extern s32 D_801375B8;
extern s32 D_801375A8;
extern s32 D_801375A0;
extern RoomLoadDefHolder D_801375BC;
extern s32 D_8013759C;
extern s32 D_801375A4;
extern s32 DAT_06086258;

void func_06078120();
void UpdateStageEntities();
void func_0600E0D0(s16, s16, s16, s16);
void func_80102D70();
s32 func_800F0CD8(u16);
void func_06005208(s32);
void func_0606D554(s32);
void StartColorOffsetFade(s32, s32);
void func_0606C160();
void func_06066854();
void InitRoom();
void func_0600A030();
void ScrollEntitiesWithCamera(s32, s32, s32, s32);
void func_06070988();
void HitDetection();
void func_06009CCC();
void func_0600FC04();
void func_06071C3C();

static void func_800F223C(void) {
    g_CurrentRoom.stageID ^= STAGE_INVERTEDCASTLE_FLAG;
    func_800F2120();
    g_CurrentRoom.stageID ^= STAGE_INVERTEDCASTLE_FLAG;
}

void RunMainEngine(void) {
    s32 x, y;
    s32 iVar9;

    if (D_80097C98 != 0) {
        DAT_0605d7f0 = 1;
    }
    switch (DAT_0605cd70.unk0) {
    case 0:
        if (func_06005328() == 0) {
            func_06071C3C();
            D_8003C730 = 0;
            DAT_0605cd70.unk0 = 6;
            DAT_0605cd70.unk8 = 0;
            if (g_CurrentRoom.stageID == 0x43) {
                DAT_06085508 = DAT_06085508 + 1 & 1;
            }
        }
        break;
    case 1:
        if (stopMusicFlag != 0) {
            currentMusicId = func_060727DC(
                g_PlayableCharacter, g_CurrentRoom.stageID, g_CurrentRoom.unk4);
            if (g_unkGraphicsStruct.D_800973FC != 1) {
                PlaySfx(SET_STOP_MUSIC);
                if (func_06012DD0()) {
                    return;
                }
                PlaySfx(currentMusicId);
                stopMusicFlag = 0;
            }
        }
        InitRoom();
        DAT_0605cd70.unk0 = 6;
        DAT_0605cd70.unk8 = 0;
        break;
    case 6:
        if (DAT_0605cd70.unk8 == 8) {
            DAT_0605cd70.unk0 = 2;
            DAT_0605cd70.unk8 = 0;
            DAT_0608550C = 0;
        } else {
            DAT_0605cd70.unk8++;
            if (D_80097C98 != 0) {
                DAT_0605c110 = 1;
            } else {
                DAT_0605c110 = 0;
            }
            goto LAB_06070f5a;
        }
    case 2:
        if (func_0607284C() == 0) {
            switch (D_80097C98) {
            case 3:
            case 6:
                StartColorOffsetFade(3, 0x3F);
                g_Player.demo_timer = 4;
                DAT_0605cd70.unk0 += 2;
                break;
            case 4:
            case 5:
                StartColorOffsetFade(3, 0x5A);
                g_Player.demo_timer = 4;
                DAT_0605cd70.unk0 += 2;
                break;
            case 1:
            case 7:
                StartColorOffsetFade(1, 8);
                g_Player.demo_timer = 4;
                DAT_0605cd70.unk0 += 2;
                break;
            case 0:
                StartColorOffsetFade(1, 4);
                DAT_0605cd70.unk0 += 2;
                break;
            case 2:
            default:
                g_Player.demo_timer = 4;
                DAT_0605cd70.unk0 += 2;
                break;
            }
            func_0600A030();
        }
        if (D_80097C98 != 0) {
            goto LAB_06070f5a;
        }
        break;
    case 3:
        if (g_PlayableCharacter == 0) {
            func_06064660(1);
            if (DAT_0605cd70.unk8 == 0) {
                DAT_0608550C = DAT_0605cd70.unk8;
                DAT_0605cd70.unk8 = 1;
            }
            if (func_0607284C() != 0) {
                return;
            }
        } else if (DAT_06086258 == 1) {
            if (func_060743B8(DAT_0605cd70.unk8) != 0) {
                return;
            }
            if (DAT_0605cd70.unk8 == 0) {
                DAT_0605cd70.unk8 = 1;
                return;
            }
        }
        DAT_0605cd70.unk8 = 0;
        StartColorOffsetFade(1, 8);
        func_0600A030();
        if ((g_PlayableCharacter != 0) && (DAT_06086258 == 1)) {
            if (StatusPause(1) != 0) {
                DAT_0605c664 = 0;
                PlaySfx(SET_UNPAUSE_SFX_SCRIPTS);
                PlaySfx(SET_KEY_ON_20_21);
                PlaySfx(SET_KEY_ON_22_23);
            }
            DAT_06086258 = 0;
            DAT_0605ceb0 = 1;
        }
    case 4:
        if (DAT_0605becc == 0) {
            DAT_0605cd70.unk0 = 5;
            DAT_0605d7f0 = 0;
            D_80097C98 = 0;
            DAT_060860AC = 0;
            DAT_0605ceb0 = 1;
            if ((g_PlayableCharacter != 0) && (DAT_06086258 == 2)) {
                DAT_0605cd70.unk0 = 0xA0;
                DAT_06086258 = 0;
            }
        }
        if ((DAT_0605cd70.unk4 == 4) && (DAT_0605cd70.unk0 == 3)) {
            goto LAB_06070fd2;
        }
        if (D_80097C98 != 0) {
            goto LAB_06070f5a;
        }
        break;
    case 5:
        if (DAT_0605cd70.unk0 == 5) {
            DAT_0605c110 = 1;
        }
    LAB_06070f5a:
        g_GameTimer++;
        func_0600FC04();
        func_06009CCC();
        HitDetection();
        g_Player.unk7C = D_8013759C = PLAYER.posX.i.hi;
        g_Player.unk7E = D_801375A0 = PLAYER.posY.i.hi;
        g_unkGraphicsStruct.shoveX.val = 0;
        g_unkGraphicsStruct.shoveY.val = 0;
        if (DAT_06085520 != 0) {
            func_0600E0D0(D_801375B4, D_801375B8, D_801375A4, D_801375A8);
            DAT_06085520 = 0;
        }
        func_06064604();
        func_06064664();
        func_06066854();
    LAB_06070fd2:
        func_0606C160();
        if (DAT_0605cd70.unk0 == 3) {
            DAT_0605cd70.unk0++;
            return;
        }
        func_06078120();
        if (DAT_0605cea2 == 5) {
            if (D_80097C98 == 6) {
                D_80097C98 = 0;
            }
            return;
        }
        func_06070988();
        if (DAT_0605C6D4 == 3) {
            DAT_0605C6D4 = 0;
            D_80097C98 = 0x8000000;
            return;
        }
        if (D_80097C98 & 0x80000000) {
            PlaySfx(0xF0000008);
            return;
        }
        if ((DAT_0605cd70.unk0 != 6) && (DAT_0605cd70.unk0 != 4) &&
            (DAT_0605cd70.unk0 != 2)) {
            if ((D_80097C98 == 4) || (D_80097C98 == 5) || (D_80097C98 == 6)) {
                PlaySfx(0xF0000008);
                func_800EA5AC(0xFFFF, 0xFF, 0xFF, 0xFF);
            }
            if (D_80097C98 == 4) {
                func_800F223C();
                g_CurrentRoom.stageID = 0x2B;
                D_8006C374 = 0x43;
                DAT_0605cd70.unk4 = -1;
                DAT_0605cd70.unk0 = 0x84;
                DAT_0605cd70.unk8 = 0;
                return;
            } else if (D_80097C98 == 5) {
                func_800F223C();
                g_CurrentRoom.stageID = 0xB;
                D_8006C374 = 0x44;
                DAT_0605cd70.unk4 = -1;
                DAT_0605cd70.unk0 = 0x84;
                DAT_0605cd70.unk8 = 0;
                return;
            } else if (D_80097C98 == 6) {
                g_CurrentRoom.stageID = 0x40;
                func_800F223C();
                D_8006C374 = 0xA7;
                DAT_0605cd70.unk4 = -1;
                DAT_0605cd70.unk0 = 0x84;
                DAT_0605cd70.unk8 = 0;
                return;
            } else if (D_80097C98 == 7) {
                g_CurrentRoom.stageID = 9;
                g_CurrentRoom.unk8 = 1;
                func_800F223C();
                D_8006C374 = 0x39;
                DAT_0605cd70.unk4 = -1;
                DAT_0605cd70.unk0 = 0x84;
                DAT_0605cd70.unk8 = 0;
                return;
            } else if (D_80097C98 == 1) {
                PLAYER.posX.i.hi += 0x140;
            }
        }

        D_801375A4 = D_8013759C - PLAYER.posX.i.hi;
        D_801375A8 = D_801375A0 - PLAYER.posY.i.hi;
        g_PlayerX -= D_801375A4;
        g_PlayerY -= D_801375A8;
        D_8013759C = PLAYER.posX.val;
        D_801375A0 = PLAYER.posY.val;
        D_801375AC = g_Tilemap.scrollX.i.hi;
        D_801375B0 = g_Tilemap.scrollY.i.hi;
        func_80102D70();
        if (g_unkGraphicsStruct.unk28 != 0) {
            func_06064658(g_unkGraphicsStruct.unk28);
            DAT_06085528 = DAT_0605cd70.unk0;
            DAT_0605cd70.unk0 = 0x70;
            PlaySfx(SET_PAUSE_SFX_SCRIPTS);
        } else {
            iVar9 = func_800F0CD8(DAT_0605c110);
            if (iVar9 != 0) {
                DAT_0605c110 = 0;
                DAT_0605d7f0 = 1;
                if (iVar9 > 1) {
                    D_8006C374 = iVar9 - 2;
                    DAT_0605cd70.unk4 = -1;
                    DAT_0605cd70.unk0 = 0x88;
                    DAT_0605cd70.unk8 = 0;
                } else if (D_801375BC.def->tilesetId == 0xFF) {
                    D_8006C374 = D_801375BC.def->tileLayoutId;
                    DAT_0605cd70.unk4 = -1;
                    DAT_0605cd70.unk0 = 0x84;
                    DAT_0605cd70.unk8 = 0;
                } else if (D_801375BC.def->tilesetId == 0xEE) {
                    D_8006C374 = D_801375BC.def->tileLayoutId;
                    DAT_0605cd70.unk0 = 0x85;
                    DAT_0605cd70.unk8 = 0;
                } else {
                    DAT_060860AC = 1;
                    DAT_0605cd70.unk0 = 0x81;
                }
                return;
            }
            D_801375B4 = D_801375AC - g_Tilemap.scrollX.i.hi;
            D_801375B8 = D_801375B0 - g_Tilemap.scrollY.i.hi;
            D_801375A4 = D_8013759C - PLAYER.posX.val;
            D_801375A8 = D_801375A0 - PLAYER.posY.val;
            x = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
            y = PLAYER.posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (x != DAT_0608552C || y != DAT_06085530) {
                D_801375A4 -= g_unkGraphicsStruct.shoveX.val;
                D_801375A8 -= g_unkGraphicsStruct.shoveY.val;
                DAT_0608552C = x;
                DAT_06085530 = y;
            }
            ScrollEntitiesWithCamera(
                D_801375B4, D_801375B8, D_801375A4, D_801375A8);
            D_801375A4 = D_801375A4 >> 16;
            D_801375A8 = D_801375A8 >> 16;
            DAT_06085520 = 1;
            if (g_Player.status & PLAYER_STATUS_UNK80000) {
                StartColorOffsetFade(2, 0x78);
                PlaySfx(SET_UNK_80);
                PlaySfx(SET_XA_PLAYBACK);
                func_06005208(5);
                return;
            }
            if (g_unkGraphicsStruct.D_800973FC != 0 && D_8006BB00 == 0) {
                D_8006BB00 = 1;
                MuteCd();
            } else if (g_unkGraphicsStruct.D_800973FC == 0 && D_8006BB00 != 0) {
                if (g_unkGraphicsStruct.pauseEnemies != 0) {
                    stopMusicFlag = 0;
                    D_8006BB00 = 0;
                    UnMuteCd();
                } else if (stopMusicFlag == 0) {
                    D_8006BB00 = 0;
                    if ((D_8003C708.flags & (FLAG_UNK_40 | FLAG_UNK_20)) != 0) {
                        PlaySfx(SET_STOP_MUSIC);
                    } else {
                        UnMuteCd();
                    }
                } else {
                    if ((D_8003C708.flags & (FLAG_UNK_40 | FLAG_UNK_20)) == 0) {
                        UnMuteCd();
                        PlaySfx(currentMusicId);
                        if (currentMusicId != 0) {
                            stopMusicFlag = 0;
                        }
                    }
                    D_8006BB00 = 0;
                }
            }
            if ((DAT_0605cd70.unk0 & 0x80) != 0) {
                return;
            }
            if (DAT_0605becc != 0) {
                return;
            }
            if (D_801375C8 != 0) {
                return;
            }
            if (func_06079AF0() != 0) {
                PlaySfx(SET_RELEASE_RATE_LOW_22_23);
                PlaySfx(SET_RELEASE_RATE_LOW_20_21);
                PlaySfx(SET_PAUSE_SFX_SCRIPTS);
                DAT_0605c664 = 1;
                DAT_060860AC = 4;
                DAT_0605cd70.unk0 = 0xF0;
                DAT_0605ceb0 = 0;
            }
        }
        break;
    case 0xF0:
        if (CdSoundCommandQueueEmpty() != 0) {
            if (func_80133950() != 0) {
                DAT_0605cd70.unk0++;
            }
        }
        break;
    case 0xF1:
        if (CdSoundCommandQueueEmpty() == 0) {
            break;
        }
        DAT_0605cd70.unk0++;
    case 0xF2:
        PlaySfx(SET_UNK_10);
        DAT_0605cd70.unk0++;
        break;
    case 0xF3:
        if (func_80133950() != 0) {
            stopMusicFlag = 1;
            if (g_PlayableCharacter == 0) {
                DAT_0605cd70.unk0++;
                StartColorOffsetFade(0, 8);
                DAT_0605cd70.unk0 = 0x83;
            } else {
                func_06064658(g_unkGraphicsStruct.unk28);
                DAT_0605cd70.unk0 = 0xA0;
            }
        }
        break;
    case 0x81:
        DAT_0605cd70.unk0 += 2;
        if (D_80097C98 == 0) {
            StartColorOffsetFade(0, 4);
        }
        break;
    case 0x82:
        DAT_0605cd70.unk0++;
        StartColorOffsetFade(2, 8);
        break;
    case 0x83:
        if (DAT_0605becc != 0) {
            return;
        }
        if (DAT_060860AC == 2) {
            if (D_801375BC.def->tilesetId != 0xEE) {
                DAT_0605cd70.unk2 = -1;
            }
            DAT_060860AC = 1;
        } else if (DAT_060860AC == 4) {
            DAT_0605cd70.unk0 += 4;
            if (g_PlayableCharacter != 0) {
                goto line464;
            } else {
                goto switchD_06070ab8_caseD_87;
            }
        }
        Scl_s_reg.dispenbl &= ~0x003F;
        SclProcess = 1;
    line464:
        func_06005208(DAT_060860AC);
        break;
    case 0x84:
        if (D_80097C98 != 0) {
            func_0606C160();
        }
        switch (DAT_0605cd70.unk8) {
        case 0:
            DAT_0605cd70.unk8++;
            if (D_80097C98 == 4 || D_80097C98 == 5) {
                StartColorOffsetFade(2, 0x3F);
            } else if (D_80097C98 == 6) {
                StartColorOffsetFade(2, 0x30);
            }
        case 1:
            if (func_0600FBBC() == 0) {
                DAT_0605cd70.unk8++;
            }
            break;
        case 2:
            if (func_80133950() != 0) {
                PlaySfx(SET_UNK_0B);
                while (func_06013320() == 0) {
                    func_06010400();
                    SCL_DisplayFrame();
                }
                DAT_0605cd70.unk8++;
            }
            break;
        case 3:
            DAT_0605d772 = 4;
            DAT_0605cd70.unk0 += 2;
            break;
        }
        break;
    case 0x85:
        switch (DAT_0605cd70.unk8) {
        case 0:
            if (func_0600FBBC() == 0) {
                DAT_0605cd70.unk8++;
            }
            break;
        case 1:
            if (func_80133950() != 0) {
                PlaySfx(SET_UNK_0B);
                while (func_06013320() == 0) {
                    func_06010400();
                    SCL_DisplayFrame();
                }
                DAT_0605d772 = 9;
                stopMusicFlag = 1;
                DAT_0605cd70.unk0++;
            }
            break;
        }
        break;
    case 0x86:
        DAT_0605cd70.unk0 = 0x90;
        if (D_80097C98 == 0 && g_CurrentRoom.stageID != 0x38) {
            StartColorOffsetFade(0, 4);
        }
        break;
    case 0x90:
        if (DAT_0605becc != 0) {
            break;
        }
        DAT_0605cd70.unk0++;
    case 0x91:
        if (func_06005328() == 0) {
            if ((D_801375BC.def->tilesetId != 0xEE) || (D_80097C98 != 0)) {
                DAT_0605cd70.unk2 = -1;
            }
            func_06005208(1);
        }
        break;
    case 0x87:
    switchD_06070ab8_caseD_87:
        if ((g_PlayableCharacter != 0) || func_80133950()) {
            DAT_0605d772 = (y = 11, y);
            func_06005328();
            func_06005208(DAT_060860AC);
        }
        break;
    case 0x88:
        switch (DAT_0605cd70.unk8) {
        case 0:
            if (func_0600FBBC() == 0) {
                DAT_0605cd70.unk8++;
            }
            break;
        case 1:
            if (func_80133950() != 0) {
                PlaySfx(SET_UNK_0B);
                while (func_06013320() == 0) {
                    func_06010400();
                    SCL_DisplayFrame();
                }
                DAT_0605d772 = 4;
                stopMusicFlag = 0;
                DAT_0605cd70.unk0 = 0x86;
                func_0606D554(1);
            }
            break;
        }
        break;
    case 0x70:
        if (g_unkGraphicsStruct.unk28 != 0) {
            if (g_CurrentRoom.stageID != 0x1F) {
                if (g_PlayableCharacter == 0) {
                    if (g_unkGraphicsStruct.unk28 == 0xFFF) {
                        func_06064604();
                        func_060645E8();
                        UpdateStageEntities();
                    } else if (g_unkGraphicsStruct.unk28 != 0xFF) {
                        func_0606458C();
                        func_06064664();
                        UpdateStageEntities();
                        func_80102D70();
                    } else {
                        UpdateStageEntities();
                        func_80102D70();
                    }
                } else if (g_PlayableCharacter == 2) {
                    func_0606458C();
                    func_06064664();
                    UpdateStageEntities();
                    func_80102D70();
                } else {
                    UpdateStageEntities();
                    func_80102D70();
                }
            } else {
                D_8013759C = PLAYER.posX.i.hi;
                D_801375A0 = PLAYER.posY.i.hi;
                func_06064604();
                func_06064664();
                D_801375A4 = D_8013759C - PLAYER.posX.i.hi;
                D_801375A8 = D_801375A0 - PLAYER.posY.i.hi;
                g_PlayerX -= D_801375A4;
                g_PlayerY -= D_801375A8;
            }
        } else {
            func_8010E168(1, 0x30);
            DAT_0605cd70.unk0 = DAT_06085528;
            PlaySfx(SET_UNPAUSE_SFX_SCRIPTS);
        }
        if (DAT_0605cd70.unk0 == 3) {
            if (g_PlayableCharacter == 0) {
                DAT_0605cd70.unk0++;
            } else {
                DAT_0605cd70.unk0 = 0xA0;
            }
        }
        func_06078120();
        break;
    case 0xA0:
        if (g_PlayableCharacter == 0) {
            DAT_0605cd70.unk0 = 5;
        } else {
            func_06078120();
            if (g_pads[0].previous & PAD_START) {
                if (StatusPause(1) != 0) {
                    DAT_0605c664 = 0;
                    PlaySfx(SET_UNPAUSE_SFX_SCRIPTS);
                    PlaySfx(SET_KEY_ON_20_21);
                    PlaySfx(SET_KEY_ON_22_23);
                    DAT_0605cd70.unk0++;
                    DAT_06086258 = 0;
                }
            } else {
                if (((g_pads[0].previous & PAD_L1) && (DAT_0605D744 != 0)) &&
                    (func_06076718() != 0)) {
                    DAT_060860AC = 4;
                    StartColorOffsetFade(0, 8);
                    DAT_0605cd70.unk0 = 0x83;
                    DAT_0605ceb0 = 0;
                    func_0601AF5C();
                }
            }
        }
        break;
    case 0xA1:
        func_06078120();
        if (func_060743B8(0) == 0) {
            DAT_0605cd70.unk0++;
        }
        break;
    case 0xA2:
        func_06078120();
        if (func_060743B8(1) == 0) {
            DAT_0605cd70.unk0 = 5;
            DAT_0605ceb0 = 1;
        }
        break;
    }
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f6071C3C, func_06071C3C);

extern s32 DAT_0605c120;
extern s32 DAT_0605C668;
extern s32 DAT_0605d7dc;

void InitRoomEntities(s32);
void SetDefaultSCLPriority(s32);
void func_800F2404(s32);
void SetCanRevealMap(void);
void func_06009510(s32);

// original name: INIT_ROOM
void InitRoom(void) {
    u16 uVar9;
    u32 i;
    Entity* ent;
    Primitive* prim;

    if (g_CurrentRoom.unk4 < 0x50) {
        D_8003C708.flags = 0;
    }
    DAT_0605C668 = 1;
    DAT_0605ceb0 = 0;
    Scl_w_reg.win1_start[0] = 0;
    Scl_w_reg.win1_start[1] = 0;
    Scl_w_reg.win1_end[0] = 0;
    Scl_w_reg.win1_end[1] = 0;
    Scl_w_reg.wincontrl[0] = 0x8383;
    SclProcess = 1;
    SetCanRevealMap();
    if (g_CurrentRoom.unk4 < 0x50) {
        D_801375BC.def =
            (RoomLoadDef*)GetRoomLoadDefTable(g_CurrentRoom.stageID & 0xDF);
        D_801375BC.def =
            (RoomLoadDef*)((u8*)D_801375BC.def + g_CurrentRoom.unk4 * 6 + 4);
    }
    D_8013759C = PLAYER.posX.val;
    D_801375A0 = PLAYER.posY.val;
    PLAYER.posX.i.hi = D_801375BC.pos.x + g_Tilemap.scrollX.i.hi;
    PLAYER.posY.i.hi = D_801375BC.pos.y + g_Tilemap.scrollY.i.hi;
    D_801375B4 = 0;
    D_801375B8 = 0;
    func_800F2404(1);
    uVar9 = g_CurrentRoom.stageID & 0xDF;
    if ((uVar9 == 6 || uVar9 == 11 || uVar9 == 9 || uVar9 == 3) &&
        g_CurrentRoom.unkA != g_CurrentRoom.unk8) {
        g_CurrentRoom.unkA = g_CurrentRoom.unk8;
    } else {
        DAT_0605d7dc = DAT_0605c120;
    }
    func_06009510(g_CurrentRoom.unk4);
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
    g_Tilemap.scrollX.i.hi = (g_CurrentRoom.unkC - g_Tilemap.left) * 0x140;
    g_Tilemap.scrollY.i.hi = (g_CurrentRoom.unk10 - g_Tilemap.top) * 0x100;
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
    if (g_CurrentRoom.stageID != 0x2B) {
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
    InitRoomEntities(g_CurrentRoom.unk4);
    func_0606C160();
    func_0606C160();
    DAT_0605cd70.unk0++;
    if ((g_CurrentRoom.unk6 == 0x50) || (g_CurrentRoom.unk6 == 0x60)) {
        if (g_unkGraphicsStruct.D_800973FC == 0) {
            PlaySfx(func_060727DC(g_PlayableCharacter, g_CurrentRoom.stageID,
                                  g_CurrentRoom.unk4));
        } else {
            currentMusicId = func_060727DC(
                g_PlayableCharacter, g_CurrentRoom.stageID, g_CurrentRoom.unk4);
            stopMusicFlag = 1;
        }
    }
    if ((g_CurrentRoom.unk4 == 0x50) || (g_CurrentRoom.unk4 == 0x60)) {
        if (func_06012DFC() != 0) {
            PlaySfx(SET_STOP_MUSIC);
        }
        if ((g_unkGraphicsStruct.D_800973FC != 0) && (D_8006BB00 != 0)) {
            if (g_CurrentRoom.unk4 == 0x50) {
                PlaySfx(SET_STOP_MUSIC);
                stopMusicFlag = 1;
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

    if (g_CurrentRoom.unk4 < 0x20) {
        ptr = &DAT_060645b8[g_CurrentRoom.unk4 * 12];
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
extern s32 DAT_0605c6e4;
extern s32 D_06085534;
extern s32 g_StatusWindowColorRed;
extern s32 g_StatusWindowColorGreen;
extern s32 g_StatusWindowColorBlue;
extern s32 prevMusicId;
extern s32 DAT_06086270;
extern s32 DAT_06086288;
extern s32 DAT_0608629c;

void func_06073280(void);
void UpdateCapePalette(void);
void StartColorOffsetFade(s32, s32);
void CheckWeaponCombo(void);
void make_all(void);

// original name: SUB_DISP
void SubDisp(void) {
    switch (DAT_06057f68) {
    case 1:
        if (DAT_0605cd70.unk0 == 0x14) {
            StartColorOffsetFade(1, 0x28);
        } else {
            StartColorOffsetFade(1, 0xF);
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
            StartColorOffsetFade(0, 0x28);
        } else {
            StartColorOffsetFade(0, 0xF);
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
            g_StatusWindowColorRed = g_Settings.windowColors[0];
            g_StatusWindowColorGreen = g_Settings.windowColors[1];
            g_StatusWindowColorBlue = g_Settings.windowColors[2];
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
extern s16 DAT_060862a4;

void func_06073280(void) {
    if (g_PlayableCharacter == 0) {
        UpdateCapePalette();
    }
    DAT_0605d772 = 8;
    func_060645B0();
    Scl_s_reg.dispenbl |= DAT_060862a4;
    SclProcess = 1;
    func_0600971C();
}

extern s16 DAT_06086220[];

void SetVdp2DisplayMode(s32);

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
        SetVdp2DisplayMode(0);
        break;
    case 8:
        func_060645FC();
        SetVdp2DisplayMode(0);
        break;
    case 9:
        func_060645BC();
        SetVdp2DisplayMode(0);
        break;
    case 10:
        func_06064620();
        func_06009570(3);
        SetVdp2DisplayMode(1);
        break;
    case 11:
        func_06064600();
        func_06009570(4);
        SetVdp2DisplayMode(1);
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

extern s32 g_EquipOrderType;

// original name: PSX_sort_item
void func_800FBAC4(void) {
    s32 i, j;
    s32* ptr;

    for (i = g_EquipOrderType; i > 0; i--) {
        j = g_Settings.equipOrderTypes[i];
        g_Settings.equipOrderTypes[i] = g_Settings.equipOrderTypes[i - 1];
        g_Settings.equipOrderTypes[i - 1] = j;
    }
    g_EquipOrderType = 0;
    ptr = D_801375D8;
    *ptr++ = 0;
    for (i = 0; i < 0xB; i++) {
        s32 importantcategory = g_Settings.equipOrderTypes[i];
        for (j = 0; j < 0xB0; j++) {
            s32 order = g_Status.equipHandOrder[j];
            if (g_Status.equipHandCount[order] != 0 && order != 0 &&
                g_EquipDefs[order].itemCategory == importantcategory) {
                *ptr++ = order;
            }
        }
    }
    for (j = 0; j < 0xB0; j++) {
        s32 order = g_Status.equipHandOrder[j];
        if (g_Status.equipHandCount[order] == 0) {
            *ptr++ = order;
        }
    }
    ptr = D_801375D8;
    for (i = 0; i < 0xB0; i++) {
        g_Status.equipHandOrder[i] = *ptr++;
    }
}

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

extern s32 DAT_06086210;
void func_06074048(u8 param_1) {
    DAT_06086210 = 0;
    if (param_1 != 0) {
        DAT_06086210 = 1;
    }
}
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074068, func_06074068);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60740F8, func_060740F8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074278, SetVdp2DisplayMode);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60743B8, func_060743B8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074470, func_06074470);

// _EVENT_SCL_TRANS
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60744F8, func_060744F8);

// _SS_MOJI_SET
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60745A0, func_060745A0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074698, func_06074698);

// func_06074700
void ClearVdp2CharRamA1(void) {
    u16 i;
    u32* char_ram;

    char_ram = (u32*)SCL_VDP2_VRAM_A1;
    for (i = 0; i < 0x800; i++) {
        *char_ram++ = 0;
    }
}

extern u32 g_FontGlyphDataSizes[];

// func_06074724
u32* GetStageTextGlyphData(s32 arg0, u16 arg1) {
    switch (arg1) {
    case 0x41:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[0];
        } else {
            return &g_FontGlyphDataSizes[5];
        }
    case 0x12:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[10];
        } else {
            return &g_FontGlyphDataSizes[34];
        }
    case 0x1F:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[152];
        } else {
            return &g_FontGlyphDataSizes[158];
        }
    case 0x18:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[58];
        } else {
            return &g_FontGlyphDataSizes[71];
        }
    case 0xB:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[84];
        } else {
            return &g_FontGlyphDataSizes[91];
        }
    case 0x40:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[164];
        } else {
            return &g_FontGlyphDataSizes[170];
        }
    case 0x9:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[176];
        } else {
            return &g_FontGlyphDataSizes[178];
        }
    case 0x28:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[98];
        } else {
            return &g_FontGlyphDataSizes[110];
        }
    case 0x38:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[122];
        } else {
            return &g_FontGlyphDataSizes[137];
        }
    case 0xC:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[180];
        } else {
            return &g_FontGlyphDataSizes[185];
        }
    case 0x6:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[190];
        } else {
            return &g_FontGlyphDataSizes[195];
        }
    case 0x19:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[200];
        } else {
            return &g_FontGlyphDataSizes[207];
        }
    case 0x1C:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[214];
        } else {
            return &g_FontGlyphDataSizes[219];
        }
    case 0x8:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[224];
        } else {
            return &g_FontGlyphDataSizes[238];
        }
    case 0x3C:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[252];
        } else {
            return &g_FontGlyphDataSizes[255];
        }
    case 0x17:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[258];
        } else {
            return &g_FontGlyphDataSizes[263];
        }
    }
    return NULL;
}

// func_06074964
u32* GetEventTextGlyphData(s32 arg0, s32 arg1) {
    switch (arg1) {
    case 0:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[268];
        } else {
            return &g_FontGlyphDataSizes[269];
        }
    case 1:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[270];
        } else {
            return &g_FontGlyphDataSizes[278];
        }
    case 2:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[286];
        } else {
            return &g_FontGlyphDataSizes[303];
        }
    case 3:
        return NULL;
    case 4:
        if (arg0 == 0) {
            return &g_FontGlyphDataSizes[320];
        } else {
            return &g_FontGlyphDataSizes[337];
        }
    case 5:
        return NULL;
    }
    return NULL;
}

extern u16 g_EquippedCapePalette[4];
extern u16 D_800A37F4[][4];
extern s32 g_CapePaletteDefs[];

void UpdateCapePalette(void) {
    s32 clut;
    s32 i;

    if (g_PlayableCharacter == 0) {
        i = 0;
        while (1) {
            if (g_Status.equipment[5] == g_CapePaletteDefs[i]) {
                break;
            }

            if (g_CapePaletteDefs[i] == -1) {
                break;
            }

            i += 2;
        }
        clut = g_CapePaletteDefs[i + 1];
        if ((g_Status.equipment[5] == 0x32) &&
            g_Settings.isCloakLiningReversed) {
            clut++;
        }
        for (i = 0; i < 4; i++) {
            g_EquippedCapePalette[i] = D_800A37F4[clut][i];
        }
        func_060645A4();
    }
}

// func_06074A98
u16* GetCustomCloakPalette(void) { return D_800A37F4[8]; }

void ApplyJosephsCloakPalette(void) {
    u16 g_JosephsCloakColors[4];
    u16* ptr;
    s32 i;

    g_JosephsCloakColors[0] = RGB16_COLOR(
        g_Settings.cloakColors[3] * 3 / 4, g_Settings.cloakColors[4] * 3 / 4,
        g_Settings.cloakColors[5] * 3 / 4);
    g_JosephsCloakColors[1] =
        RGB16_COLOR(g_Settings.cloakColors[3], g_Settings.cloakColors[4],
                    g_Settings.cloakColors[5]);
    g_JosephsCloakColors[2] = RGB16_COLOR(
        g_Settings.cloakColors[0] * 3 / 4, g_Settings.cloakColors[1] * 3 / 4,
        g_Settings.cloakColors[2] * 3 / 4);
    g_JosephsCloakColors[3] =
        RGB16_COLOR(g_Settings.cloakColors[0], g_Settings.cloakColors[1],
                    g_Settings.cloakColors[2]);

    ptr = GetCustomCloakPalette();
    for (i = 0; i < 4; i++) {
        *ptr++ = g_JosephsCloakColors[i];
    }
}

void func_06074BF4(void) {
    if (g_CurrentRoom.stageID != STAGE_ST0 && g_PlayableCharacter == 0) {
        UpdateCapePalette();
    }
}

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
