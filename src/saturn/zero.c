// SPDX-License-Identifier: AGPL-3.0-or-later
#include "zero.h"
#include "inc_asm.h"
#include "sattypes.h"
#include "lib/sys.h"

#define _SPR2_
#include "lib/spr/spr.h"
#include "game.h"

// func_06004080
void entrypoint(void) {
    func_06030DF0();
    Scl_s_reg.tvmode &= ~0x8100;
    SclProcess = 1;
    InitSystem();
    DAT_0605cea0.unk2 = 0;
    DAT_0605C658 = 1;
    while (true) {
        func_060040D8();
    }
}

void func_06010400();
void PlaySfx();
void StartColorOffsetFade(s32, u16);

void func_060040D8(void) {
    g_Timer++;
    func_06007D54();
    switch (DAT_0605cea0.unk2) {
    case 0:
        func_0600456C();
        DAT_0605D7F8 = 0;
        func_06004F50(0x20);
        DAT_0605cea0.unk0++;
        break;
    case 6:
        if (DAT_0605cea0.unk0 == 0) {
            func_06005328();
            DAT_0605cea0.unk0++;
            Scl_s_reg.tvmode |= 0x8000;
            SclProcess = 1;
        }
        func_060645E0();
        break;
    case 2:
        if (DAT_0605cea0.unk0 == 0) {
            func_06005328();
            DAT_0605cea0.unk0++;
        }
        func_06064688();
        UpdateScrollForRoom();
        break;
    case 3:
        func_0606468c();
        break;
    case 7:
        func_06064614();
        UpdateScrollForRoom();
        break;
    case 4:
        if (DAT_0605cea0.unk0 == 0) {
            func_06005328();
            DAT_0605cea0.unk0++;
        }
        func_06064674();
        break;
    case 8:
        if (DAT_0605cea0.unk0 == 0) {
            func_06005328();
            DAT_0605cea0.unk0++;
        }
        func_06064580();
        break;
    case 0x11:
        if (DAT_0605cea0.unk0 == 0 && DAT_0605cea0.unk2 == 0x11) {
            if (func_06005328() == 0) {
                DAT_0605cea0.unk0++;
            }
        } else {
            func_06009838();
            func_0606463C();
            UpdateScrollForRoom();
        }
        break;
    case 5:
        if (DAT_0605cea0.unk0 == 0) {
            StartColorOffsetFade(0, 2);
            func_06005328();
            DAT_0605cea0.unk0++;
        }
        func_06064644();
        UpdateScrollForRoom();
        break;
    case 0x20:
        CloseSpriteList();
        Scl_s_reg.dispenbl &= ~0x003F;
        SclProcess = 1;
        Scl_s_reg.tvmode &= ~0x8100;
        SclProcess = 1;
        InitializePads();
        SPR_WaitDrawEnd();
        ClearFrameBuffer(0x8000);
        SCL_DisplayFrame();
        ClearFrameBuffer(0x8000);
        SetVblank(1);
        DAT_06057F34 = 0;
        MoviePRGClear();
        func_06005328();
        DAT_06057F34 = func_06064690();
        if ((DAT_06057F34 == 2) && (DAT_0605D7F8 == 0)) {
            SYS_EXECDMP();
        }
        Scl_s_reg.tvmode &= ~0x8100;
        SclProcess = 1;
        SCL_DisplayFrame();
        SCL_Vdp2Init();
        func_06011CE4();
        ReturnToGame();
        func_06004F50(0x31);
        func_06007D54();
        break;
    case 0x31:
        DAT_0605D7F0 = true;
        func_0600D8BC();
        break;
    }
    if (func_0600FB4C() != 0) {
        if (DAT_0605cea0.unk2 == 6) {
            SYS_EXECDMP();
        } else {
            PlaySfx(SET_UNK_0B);
            while (func_06013320() == 0) {
                func_06010400();
                SCL_DisplayFrame();
            }
            func_06012FB4();
            func_0600652C();
            func_0601333C();
            if (DAT_0605cea0.unk2 == 2) {
                SYS_EXECDMP();
            }
        }
        StartColorOffsetFade(0, 4);
        func_06004F50(0x30);
    }
    func_06010400();
    CloseSpriteList();
    func_06005310();
    SPR_WaitDrawEnd();
    func_06008264();
    SCL_DisplayFrame();
    TransferAllBgLayers();
    ((void (*)(void))rand)();
}

void InitScuDma();
void InitBackupRam();
void func_06011CE4();

void InitSystem(void) {
    CSH_Init(0);
    CSH_AllClr();
    func_06004A10();
    InitScuDma();
    InitSpriteEngine(0);
    func_0600B234();
    func_0600DAB4();
    InitVdp2Display();
    func_06006470();
    InitBackupRam();
    func_06011CE4();
    SetVblank(1);
    func_060082C8();
    InitDebugPrint();
}

void func_0600456C(void) {
    func_06004878();
    func_060046E8();
    func_060047E8();
    SetVDP2Vram();

    Scl_w_reg.win0_start[0] = 0;
    Scl_w_reg.win0_start[1] = 12;
    Scl_w_reg.win0_end[0] = 640;
    Scl_w_reg.win0_end[1] = 240;
    Scl_w_reg.wincontrl[0] = 0x0383;
    Scl_w_reg.wincontrl[1] = 0x8383;
    Scl_w_reg.wincontrl[2] = 0x0083;

    SclProcess = 1;
    func_06009D30();
    DAT_0605D770.unk0 = 0;
    SCL_DisplayFrame();
}

// original name: RESET_SYSTEM
void func_0600460C(void) {
    CSH_Init(0);
    CSH_AllClr();
    func_06004A10();
    InitSpriteEngine(0);
    func_0600B234();
    func_0600DAB4();
    InitVdp2Display();
    SetVDP2Vram();

    Scl_w_reg.win0_start[0] = 0;
    Scl_w_reg.win0_start[1] = 12;
    Scl_w_reg.win0_end[0] = 640;
    Scl_w_reg.win0_end[1] = 240;
    Scl_w_reg.wincontrl[0] = 0x0383;
    Scl_w_reg.wincontrl[1] = 0x8383;
    Scl_w_reg.wincontrl[2] = 0x0083;
    SclProcess = 1;

    func_06009D30();
    GFS_Reset();
    func_06006470();
    func_060082C8();
    InitDebugPrint();
}

void func_060046E8(void) {
    BgTransfer* transfer;
    u32 i;

    DAT_06057F40 = 0;
    D_8003C730 = 0;
    g_Timer = 0;
    DAT_0605C10C = 0;
    g_GameTimer = 0;

    DAT_0605cea0.unk0 = 0;
    DAT_0605cea0.unk2 = 0;
    DAT_0605cea0.unk4 = 0xFFFF;
    DAT_0605cea0.unk8 = 0;

    DAT_0605cd70.unk0 = 0;
    DAT_0605cd70.unk2 = 0;
    DAT_0605cd70.unk4 = 0xFFFF;
    DAT_0605cd70.unk8 = 0;

    DAT_0605c680.unk0 = 0;
    DAT_0605c680.unk8 = 0;
    DAT_0605c680.unk4 = 0;
    DAT_0605c680.unk10 = 0;
    DAT_0605c680.unkC = 0;
    DAT_0605c680.unk18 = 0;
    DAT_0605c680.g_ScrollDeltaX = 0;
    DAT_0605c680.unk20 = 0;
    DAT_0605c680.g_ScrollDeltaY = 0;
    DAT_0605c680.unk2C = 0;
    DAT_0605c680.unk24 = 0;
    DAT_0605c680.unk30 = 0;
    DAT_0605c680.unk28 = 0;
    DAT_0605c680.unk3C = 0;
    DAT_0605c680.unk34 = 0;
    DAT_0605c680.unk40 = 0;
    DAT_0605c680.unk38 = 0;

    func_0600FB34();

    transfer = &DAT_0605D6C0[0];
    for (i = 0; i < 8; i++) {
        transfer[i].tileFlags = 0;
        transfer[i].src = 0;
        transfer[i].dest = 0;
        transfer[i].cnt = 0;
    }

    g_CurrentRoom.stageID = 0;
    g_CurrentRoom.unk2 = 0;
    g_CurrentRoom.unk4 = 0;
    g_CurrentRoom.unk6 = 0;
    DAT_0605D7F0 = false;
    g_Status.timerHours = 0;
    g_Status.timerMinutes = 0;
    g_Status.timerSeconds = 1;
}

void func_060047E8(void) {
    DAT_0605C118 = 0;
    g_Settings.D_8003CB00 = 0;
    g_Settings.D_8003CB04 = 0;
    DAT_0605CE90 = 0;
    DAT_0605C6D4 = 0;
    g_CutsceneHasControl = 0;
    DAT_0605C6E4 = 0;
    DAT_0605c664 = 0;
    D_80097C98 = 0;
    D_8006C374 = 0;
    g_Tilemap.scrollX.val = 0;
    g_Tilemap.scrollY.val = 0;
    g_Tilemap.unk8 = 0;
    g_Tilemap.vSize = 0;
    g_Tilemap.hSize = 0;
    g_Tilemap.unk14 = 0;
    g_Tilemap.bottom = 0;
    g_Tilemap.right = 0;
    g_Tilemap.top = 0;
    g_Tilemap.left = 0;
    g_Tilemap.height = 0;
    g_Tilemap.width = 0;
    g_Tilemap.y = 0;
    g_Tilemap.x = 0;
    DAT_0605C6D8.a = 0;
    currentMusicId = 0;
}

void func_06004878(void) {
    while (PER_LInit(PER_KD_SYS, 0, 0, NULL, 0) == PER_INT_ERR) {
    }

    do {
        DAT_060505E0 = PER_GET_SYS();
    } while (DAT_060505E0 == NULL);

    DAT_0605D764 = DAT_060505E0->sm & PER_MSK_STEREO ? false : true;
    if (DAT_0605D764 != 0) {
        ((s32(*)(s32))PlaySfx)(0xF0000006);
    } else {
        ((s32(*)(s32))PlaySfx)(0xF0000005);
    }
    SCL_DisplayFrame();
    SCL_DisplayFrame();
    SCL_DisplayFrame();
    func_06004A10();
}

void func_06004924(void) {
    u32 status_sys;

    while (PER_LInit(PER_KD_SYS, 0, 0, NULL, 0) == PER_INT_ERR) {
    }

    do {
        DAT_060505E4 = PER_GET_SYS();
    } while (DAT_060505E4 == NULL);
    status_sys = DAT_060505E4->sm;
    if (DAT_0605D764 != 0) {
        status_sys &= ~PER_MSK_STEREO;
    } else {
        status_sys |= PER_MSK_STEREO;
    }
    PER_SMPC_SET_SM(status_sys);

    SCL_DisplayFrame();
    SCL_DisplayFrame();
    SCL_DisplayFrame();
    func_06004A10();
}

extern s8 DAT_06057F50[PER_WORK_SIZE(1, 2)];

void func_06004A10(void) {
    s32 i;
    s8* ptr;

    i = 0;
    ptr = DAT_06057F50;
    for (; i < PER_WORK_SIZE(1, 2); i++) {
        *ptr++ = 0;
    }

    g_pads[0].previous = g_pads[0].tapped = g_pads[0].pressed = 0;
    ResetPadsRepeat();
    while (PER_LInit(PER_KD_PERTIM, 1, 2, DAT_06057F50, 0) != PER_INT_OK) {
    }
}

void InitializePads(void);

void func_06004A74(void) {
    u32 status;
    s32 i;

    g_pads[0].previous = g_pads[0].pressed;
    status = PER_LGetPer(&DAT_060505F8, &DAT_060505FC);
    if (DAT_060505FC->con != PER_MCON_NCON_UNKNOWN &&
        DAT_060505F8->id == PER_ID_DGT && DAT_060505F8->size == PER_SIZE_DGT) {
        if (!DAT_0605D7F0) {
            UpdatePads();
            UpdatePadsRepeat();
        }
    } else if (DAT_060505F8->id == PER_ID_ANL) {
        InitializePads();
    }
    if (status == PER_INT_ERR) {
        InitializePads();
    }
    if (DAT_060505FC->con != 1) {
        func_06004A10();
    }
    if (status == PER_INT_ERR || DAT_060505FC->con != 1) {
        DAT_06057F60[0] = 0x01;
        DAT_06057F60[1] = 0x00;
        DAT_06057F60[2] = 0x00;
        DAT_06057F60[3] = 0x21;
        DAT_06057F60[4] = 0x45;
        DAT_06057F60[5] = 0x98;
        DAT_06057F60[6] = 0x19;
    } else {
        DAT_06050600 = PER_GET_TIM();
        DAT_06057F60[0] = DAT_06050600[0];
        DAT_06057F60[1] = DAT_06050600[1];
        DAT_06057F60[2] = DAT_06050600[2];
        DAT_06057F60[3] = DAT_06050600[3];
        DAT_06057F60[4] = DAT_06050600[4];
        DAT_06057F60[5] = DAT_06050600[5];
        DAT_06057F60[6] = DAT_06050600[6];
    }
}

void UpdatePads(void) {
    g_pads[0].previous = g_pads[0].pressed;
    g_pads[0].pressed = ~DAT_060505F8->buttons;
    g_pads[0].tapped =
        (g_pads[0].pressed ^ g_pads[0].previous) & g_pads[0].pressed;
}

extern u8 g_PadsRepeatTimer[0x10];

// func_06004C44
void ResetPadsRepeat(void) {
    u8* ptr;
    s32 i;

    g_pads[0].repeat = PAD_NONE;
    ptr = g_PadsRepeatTimer;
    for (i = 0; i < 0x10; i++) {
        *ptr++ = 0x10;
    }
}

// original name: REPEAT_PAD
void UpdatePadsRepeat(void) {
    u16 button = 1;
    u16 tapped = g_pads[0].tapped;
    u16 pressed = g_pads[0].pressed;
    u16 repeat = 0;
    s32 i;

    for (i = 0; i < 0x10; i++, button <<= 1) {
        if (pressed & button) {
            if (tapped & button) {
                repeat |= button;
                g_PadsRepeatTimer[i] = 0x10;
            } else if (!g_PadsRepeatTimer[i]--) {
                repeat |= button;
                g_PadsRepeatTimer[i] = 5;
            }
        }
    }
    g_pads[0].repeat = repeat;
}

// func_06004CDC
void InitializePads(void) {
    g_pads[0].tapped = g_pads[0].pressed = g_pads[0].previous =
        g_pads[0].repeat = PAD_NONE;
}

// original name: SET_VBLANK
void SetVblank(s32 useAlternateHandlers) {

    set_imask(15);

    if (useAlternateHandlers == 0) {
        INT_ChgMsk(
            INT_MSK_NULL, INT_MSK_VBLK_IN | INT_MSK_VBLK_OUT | INT_MSK_HBLK_IN);
        INT_SetScuFunc(INT_SCU_VBLK_IN, func_06004D84);
        INT_SetScuFunc(INT_SCU_VBLK_OUT, func_06004DE8);
        INT_SetScuFunc(INT_SCU_HBLK_IN, NULL);
        INT_ChgMsk(INT_MSK_VBLK_IN | INT_MSK_VBLK_OUT, INT_MSK_NULL);
    } else {
        INT_ChgMsk(INT_MSK_NULL, INT_MSK_VBLK_IN | INT_MSK_VBLK_OUT);
        INT_SetScuFunc(INT_SCU_VBLK_IN, func_06004E50);
        INT_SetScuFunc(INT_SCU_VBLK_OUT, func_06004E94);
        INT_ChgMsk(INT_MSK_VBLK_IN | INT_MSK_VBLK_OUT, INT_MSK_NULL);
    }

    set_imask(0);
}

void func_06004D84(void) {
    u32 msk;

    msk = get_imask();
    set_imask(0);

    SCL_VblankStart();
    DAT_0605C10C++;
    func_06008EE8();
    SignalSlaveSh2();

    set_imask(msk);
}

void func_06004DE8(void) {
    u32 msk;

    msk = get_imask();
    set_imask(0);

    SCL_VblankEnd();
    func_06004A74();
    if (IsCdOpened() == true) {
        SYS_EXECDMP();
    }

    set_imask(msk);
}

void func_06004E50(void) {
    u32 msk;

    msk = get_imask();
    set_imask(0);

    SCL_VblankStart();

    set_imask(msk);
}

void func_06004E94(void) {
    u32 msk;

    msk = get_imask();
    set_imask(0);

    SCL_VblankEnd();
    if (IsCdOpened() == true) {
        SYS_EXECDMP();
    }

    set_imask(msk);
}

// original name: RETURN_TO_GAME
void ReturnToGame(void) { SetVblank(0); }

void func_06004F50(u16 arg0) {
    SCL_SET_N1SPRM(0);
    SCL_SET_N2SPRM(0);
    switch (arg0) {
    case 0x6:
        DAT_0605D770.unk2 = 7;
        break;

    case 0x2:
        DAT_0605D770.unk2 = 2;
        ((s32(*)(void))func_06009D30)();
        break;

    case 0x4:
        DAT_0605D770.unk2 = 13;
        break;

    case 0x8:
        DAT_0605D770.unk2 = 14;
        break;

    case 0x11:
        DAT_0605D770.unk2 = 3;
        func_06064640(0);
        SCL_SET_N1SPRM(1);
        SCL_SET_N2SPRM(1);
        break;

    case 0x20:
        DAT_0605D770.unk2 = 6;
        break;

    case 0x30:
        DAT_0605D7F0 = true;
        Scl_s_reg.tvmode &= 0x7EFF;
        SclProcess = 1;
        SCL_DisplayFrame();
        BlankScreen();
        DestroyEntitiesFrom(0);
        func_0600B254();
        InitPrimBuf();
        ((s32(*)(void))func_060195F0)();
        DAT_0605C6E4 = 0;
        SetSpriteEraseData(RGB16_COLOR(0, 0, 0) & 0x7FFF);
        g_CurrentRoom.stageID = 0;
        g_CurrentRoom.unk4 = 0;
        g_CurrentRoom.unk2 = -1;
        g_CurrentRoom.unk6 = -1;
        g_CurrentRoom.unk8 = 0;
        g_CurrentRoom.unkA = -1;
        ResetLayerColorCalc();
        Scl_w_reg.win1_start[0] = 0;
        Scl_w_reg.win1_start[1] = 0;
        Scl_w_reg.win1_end[0] = 0;
        Scl_w_reg.win1_end[1] = 0;
        Scl_w_reg.wincontrl[0] = 0x8383;
        SclProcess = 1;
        SetVDP2Vram();
        DAT_0605cea0.unk2 = arg0;
        func_06004F50(2);
        DAT_0605D7F0 = false;
        return;

    case 5:
        DAT_0605D770.unk2 = 12;
        break;
    }

    if (arg0 != 0x20) {
        func_06009058(arg0);
    }
    Scl_w_reg.win1_start[0] = 0;
    Scl_w_reg.win1_start[1] = 0;
    Scl_w_reg.win1_end[0] = 0;
    Scl_w_reg.win1_end[1] = 0;
    Scl_w_reg.wincontrl[0] = 0x8383;
    SclProcess = 1;
    DAT_0605cea0.unk4 = DAT_0605cea0.unk2;
    DAT_0605cea0.unk2 = arg0;
    DAT_0605cea0.unk0 = 0;
    DAT_0605cea0.unk8 = 0;
    DAT_0605cd70.unk2 = 0;
    DAT_0605cd70.unk4 = -1;
    if ((arg0 == 0x11) && (D_8003C730 == 0)) {
        g_CurrentRoom.unk2 = -1;
        g_CurrentRoom.unk6 = -1;
        g_CurrentRoom.unk8 = 0;
        g_CurrentRoom.unkA = -1;
    }
}

void func_06005208(s32 arg0) {
    u16 mode = arg0;

    DAT_0605cd70.unk4 = DAT_0605cd70.unk2;
    DAT_0605cd70.unk2 = mode;
    DAT_0605cd70.unk0 = 0;
    DAT_0605cd70.unk8 = 0;
    DAT_0605C110 = 0;

    if (mode == 5) {
        Scl_s_reg.dispenbl &= ~0x0001;
        SclProcess = 1;
        DAT_0605D770.unk2 = 5;
    } else {
        DAT_0605C100 = 0;
        DAT_0605CD80 = 0;
        DAT_0605CD5C = 0;
        DAT_0605C65C = 0;
        ResetLayerColorCalc();

        switch (mode) {
        case 1:
            if ((g_CurrentRoom.stageID & 0xDF) == 0xD) {
                func_06009F10();
            }
            if (DAT_0605cd70.unk4 == 4) {
                DAT_0605cd70.unk0 += 3;
            } else {
                func_0606465C();
                if (DAT_0605cd70.unk4 == 1) {
                    DAT_0605cd70.unk0 += 1;
                }
                SetVdp2BackgroundColor();
            }
            break;

        case 4:
            SetVdp2BackgroundColor();
            DAT_06057f68 = 0;
            break;
        }
    }
}

void func_06005310(void) { func_06006FA8(); }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6005328, func_06005328);

void func_0600544C(void) {}

void func_06005470(void) {
    ReadFileToAddr("LOGO.PRG", 0x060A5000);
    if (g_FileLoadEnabled != 0) {
        func_0601B184();
    }
    DAT_0605D7DC = (s32)&DAT_00252000;
    DAT_0605D7DC += ReadFileToAddr("KCEN.MAP", DAT_0605D7DC);
    if (DAT_0605D7DC & 1) {
        DAT_0605D7DC++;
    }
}

extern s16* DAT_0605C120[];

void func_06005508(void) {
    ReadFileToAddr("TITLE.PRG", 0x060A5000);
    if (g_FileLoadEnabled != 0) {
        func_0601AEF4();
    }
    ReadFileToAddr("TITLE.CHR", VRAM_ADDR + 0x13980);
    ReadFileToAddr("ASCII.FON", (s32)&DAT_00252000);
    func_060100DC();

    DAT_0605D7DC = 0x00256000;
    DAT_0605D7DC += ReadFileToAddr("TITLE.MAP", DAT_0605D7DC);
    if (DAT_0605D7DC & 1) {
        DAT_0605D7DC++;
    }
    DAT_0605C120[0] = (s16*)DAT_0605D7DC;
}

// original name: READ_LOAD_MODE
s32 func_060055A4(void) { return 0; }

void func_06019FA0(s32);
void func_06019FE4(s32);

s32 func_060055C8(void) {
    s32 iVar4;

    if (DAT_0605D770.unk0 == 0x0) {
        func_06019FA0(0);
    } else {
        func_06019FE4(0);
    }

    if (DAT_06038A44) {
        return 1;
    }

    DAT_06038A44 = 1;
    switch (DAT_0605D770.unk0) {
    case 0:
        ResetSpriteVram();
        AllocGameSprite(g_PlayableCharacter);
        Scl_s_reg.dispenbl &= ~0x003F;
        SclProcess = 1;
        ((s32(*)(s32, s32))StartColorOffsetFade)(1, 2);
        DAT_0605D770.unk0++;

    case 1:
        DAT_0605D770.unk0++;

    case 2:
        DAT_0605D770.unk8 = 1;
        break;

    case 3:
        DAT_0605D770.unk8 = 2;
        break;

    case 4:
        DAT_0605D770.unk8 = 3;
        if (g_PlayableCharacter == 1 || g_PlayableCharacter == 2) {
            DAT_0605D770.unk0 += 6;
        }
        break;

    case 5:
        DAT_0605D770.unk8 = 4;
        break;

    case 6:
        DAT_0605D770.unk8 = 5;
        break;

    case 7:
        DAT_0605D770.unk8 = 6;
        break;

    case 8:
        DAT_0605D770.unk8 = 7;
        if (g_Servant < 1) {
            DAT_0605D770.unk0 += 2;
        }
        break;

    case 9:
        DAT_0605D770.unk8 = 11;
        break;

    case 10:
        DAT_0605D770.unk8 = 12;
        break;

    case 11:
        DAT_0605D770.unk8 = 8;
        break;

    case 12:
        DAT_0605D770.unk8 = 9;
        break;

    case 13:
        if (func_0600607C(g_CurrentRoom.stageID)) {
            ReadFileToAddr(func_06005E3C(0, g_CurrentRoom.stageID),
                           SCL_VDP2_VRAM_A1 + 0x2000);
            ReadFileToAddr(
                func_06005E3C(1, g_CurrentRoom.stageID), SCL_VDP2_VRAM_B1);
            func_060645C4();
        }

        if (g_CurrentRoom.stageID & 0x20) {
            ReadFileToAddr("RLOAD.MAP", &DAT_060937F8);
        } else {
            ReadFileToAddr("LOAD.MAP", &DAT_060937F8);
        }

        iVar4 = 0;
        if (g_CurrentRoom.stageID == 0x1A || g_CurrentRoom.stageID == 0x18 ||
            g_CurrentRoom.stageID == 0x39) {
            iVar4 = GetEnemyPlayerCharaAddr();
        }
        DAT_0605D7DC = iVar4 + (s32)&DAT_00252000;
        DAT_0605D770.unk8 = 10;
        break;

    case 14:
        DAT_06038A44 = 0;
        return 0;
    }
    DAT_0605D770.unk0++;
    return 1;
}

void func_0600583C(void) {
    ReadFileToAddr("OPEN.PRG", 0x060A5000);
    if (g_FileLoadEnabled != 0) {
        func_0601AF2C();
    }
    ReadFileToAddr("OPENNING.CHR", VRAM_ADDR + 0x13980);
    DAT_0605D7DC = 0x254000;
    DAT_0605D7DC += ReadFileToAddr("OPENNING.MAP", DAT_0605D7DC);
    if (DAT_0605D7DC & 1) {
        DAT_0605D7DC++;
    }
}

void func_060058D0(void) {
    ReadFileToAddr("STAFF.PRG", 0x060A5000);
    if (g_FileLoadEnabled != 0) {
        func_0601AF44();
    }
    DAT_0605D7DC = 0x254000;
    DAT_0605D7DC += ReadFileToAddr("STAFROLL.MAP", DAT_0605D7DC);
    if (DAT_0605D7DC & 1) {
        DAT_0605D7DC++;
    }
}

void func_06005944(void) {
    ReadFileToAddr("MOVIE.PRG", 0x06066000);
    if (g_FileLoadEnabled != 0) {
        func_0601B1B4();
    }
}

const char DAT_0600597C[] = "S430.PTN";

const char DAT_06005988[] = "S430.CHR";

const char DAT_06005994[] = "S440.PTN";

const char DAT_060059A0[] = "S440.CHR";

const char DAT_060059AC[] = "S410.PTN";

const char DAT_060059B8[] = "S410.CHR";

const char DAT_060059C4[] = "S400.PTN";

const char DAT_060059D0[] = "S400.CHR";

void func_060059F4(void) {
    ReadFileToAddr("ENDING.PRG", (s32)&g_StageOverlayData);
    if (g_FileLoadEnabled != 0) {
        func_0601B19C();
    }
    ReadFileToAddr("ENDING.CHR", VRAM_ADDR + 0x2A980);
    if (DAT_0605D7FC != 4 && DAT_0605D7FC != 6) {
        ReadFileToAddr(
            DAT_06038A14[DAT_0605D7FC - 1][0], SCL_VDP2_VRAM_A1 + 0x2000);
        ReadFileToAddr(DAT_06038A14[DAT_0605D7FC - 1][1], SCL_VDP2_VRAM_B1);
    }
    func_060645C4();
}

s32 func_06005A90(void) {
    func_06019FE4(0);
    switch (DAT_0605D770.unk8) {
    case 0:
        ((s32(*)(s32))PlaySfx)(DAT_060389E0[g_PlayableCharacter][0]);
        DAT_0605D770.unk8++;
        return 1;

    case 1:
        if (func_06012D88() != 0) {
            return 1;
        }
        DAT_0605D770.unk8++;
        return 1;

    case 2:
        ((s32(*)(s32))PlaySfx)(DAT_060389E0[g_PlayableCharacter][1]);
        DAT_0605D770.unk8++;
        return 1;

    case 3:
        if (func_06012D88() != 0) {
            return 1;
        }
        DAT_0605D770.unk8++;

    case 4:
        ((s32(*)(s32))PlaySfx)(g_StageFileRecords[g_CurrentRoom.stageID].unkC);
        DAT_0605D770.unk8++;
        return 1;

    case 5:
        if (func_06012D88() != 0) {
            return 1;
        }
        if ((g_Servant != 0) && (g_PlayableCharacter == 0)) {
            DAT_0605D770.unk8++;
            return 1;
        }
        goto block_43;

    case 6:
        ((s32(*)(s32))PlaySfx)(DAT_060389F8[g_Servant - 1]);
        DAT_0605D770.unk8++;
        return 1;

    case 7:
        if (func_06012D88() != 0) {
            return 1;
        }
    block_43:
        if (g_CurrentRoom.stageID == 0x1F) {
            DAT_0605D770.unk8 = 8;
            goto case8;
        }
        if (g_CurrentRoom.stageID == 0x40) {
            DAT_0605D770.unk8 = 9;
            goto case9;
        }
        if (g_PlayableCharacter != 0 && g_CurrentRoom.stageID == 0x41) {
            DAT_0605D770.unk8 = 10;
            goto case10;
        }
        ((s32(*)(s32, s32))StartColorOffsetFade)(0, 2);
        return 0;

    case 8:
    case8:
        ((s32(*)(s32))PlaySfx)(0xF0000807);
        DAT_0605D770.unk8 = 0x80;
        return 1;

    case 9:
    case9:
        ((s32(*)(s32))PlaySfx)(0xF0000810);
        DAT_0605D770.unk8 = 0x80;
        return 1;

    case 10:
    case10:
        if (g_PlayableCharacter == 1) {
            ((s32(*)(s32))PlaySfx)(0xF0000812);
        }
        if (g_PlayableCharacter == 2) {
            ((s32(*)(s32))PlaySfx)(0xF000080F);
        }
        DAT_0605D770.unk8 = 0x80;
        return 1;

    case 0x80:
        if (func_06012D88() != 0) {
            return 1;
        }
    default:
        ((s32(*)(s32, s32))StartColorOffsetFade)(0, 2);
        return 0;
    }
}

char* func_06005E3C(s32 arg0, u16 arg1) {
    switch (arg1) {
    case 0x1F:
        if (arg0 == 0) {
            return "S011.CHR";
        } else {
            return "S011.PTN";
        }
    case 0x40:
        if (arg0 == 0) {
            return "S160.CHR";
        } else {
            return "S160.PTN";
        }
    case 0x9:
        if (arg0 == 0) {
            return "SWATA.CHR";
        } else {
            return "SWATA.PTN";
        }
    case 0x12:
        if (arg0 == 0) {
            return "EVENT070.001";
        } else {
            return "EVENT070.002";
        }
    case 0x18:
        if (arg0 == 0) {
            return "SBO7.CHR";
        } else {
            return "SBO7.PTN";
        }
    case 0xB:
        if (arg0 == 0) {
            return "S302.CHR";
        } else {
            return "S302.PTN";
        }
    case 0x41:
        if (arg0 == 0) {
            return "EVENT020.001";
        } else {
            return "EVENT020.002";
        }
    case 0xC:
        if (arg0 == 0) {
            return "S040.CHR";
        } else {
            return "S040.PTN";
        }
    case 0x6:
        if (arg0 == 0) {
            return "S060.CHR";
        } else {
            return "S060.PTN";
        }
    case 0x19:
        if (arg0 == 0) {
            return "S050.CHR";
        } else {
            return "S050.PTN";
        }
    case 0x1C:
        if (arg0 == 0) {
            return "S110.CHR";
        } else {
            return "S110.PTN";
        }
    case 0x28:
        if (arg0 == 0) {
            return "SR14.CHR";
        } else {
            return "SR14.PTN";
        }
    case 0x38:
        if (arg0 == 0) {
            return "SDRACULA.CHR";
        } else {
            return "SDRACULA.PTN";
        }
    case 0x3C:
        if (arg0 == 0) {
            return "S140.CHR";
        } else {
            return "S140.PTN";
        }
    case 0x8:
        if (arg0 == 0) {
            return "S190.CHR";
        } else {
            return "S190.PTN";
        }
    case 0x17:
        if (arg0 == 0) {
            return "S030.CHR";
        } else {
            return "S030.PTN";
        }
    }
    return NULL;
}

bool func_0600607C(u16 arg0) {
    if (g_PlayableCharacter != 0 && g_CurrentRoom.stageID == 0x9) {
        return true;
    }
    if (g_PlayableCharacter == 1 && g_CurrentRoom.stageID == 0x1F) {
        return true;
    }
    if (g_PlayableCharacter == 0) {
        switch (arg0) {
        case 0x6:
        case 0x8:
        case 0x9:
        case 0xB:
        case 0xC:
        case 0x12:
        case 0x17:
        case 0x18:
        case 0x19:
        case 0x1C:
        case 0x1F:
        case 0x28:
        case 0x38:
        case 0x3C:
        case 0x40:
        case 0x41:
            return true;
        }
    }
    return false;
}

const char DAT_06006158[] = "in GfsInit";

const char DAT_06006164[] = "in CdInit";

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006170, func_06006170);

const char DAT_060062E8[] = "in GfsLoadDir";

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60062F8, func_060062F8);

const char DAT_06006448[] = "In NameToID";

const char DAT_06006454[] = "In Load";

const char DAT_0600645C[] = "In Seek";

const char DAT_06006464[] = "In SetDir";

s32 func_06006470(void) {
    s32 result;
    s32 index;
    s32 success;

    result = 1;
    index = 0;
    success = 1;

    do {
        switch (index) {
        case 0:
            DAT_06038A44 = 0;
            DAT_06050668 = 0;
            index++;
        case 1:
            result = func_06006170();
            break;
        case 2:
            result = func_060062F8(0, &DAT_0605AE80);
            break;
        }

        if (result == 1) {
            DAT_06050668 = 0;
            index++;
        } else if (result == 0) {
            success = 0;
            break;
        }
    } while (index < 3);

    if (success == 0) {
        SYS_EXECDMP();
    }

    DAT_0605AE8C = &DAT_0605060C[0x40];
    DAT_0605060C[0] = 0;
    return success;
}

void func_0600652C(void) {
    GFS_Reset();
    DAT_06038A44 = 0;
}

// func_0600654C
s32 ReadFileToAddr(char* path, s32 addr) {
    Unk0600654C unk;
    unk.unk0 = path;
    unk.unk4 = (void*)addr;
    unk.unk8 = -1;
    unk.unkA = 0;
    return func_06006574(&unk);
}

// _FileReadSetAdrEx
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006574, func_06006574);

// func_060066F0
void ReadFileToAddrAsync(char* arg0, u32 arg1, u32 arg2, u32 arg3) {
    Unk0600654C unk;
    unk.unk0 = arg0;
    unk.unk4 = (void*)arg1;
    unk.unk8 = -1;
    unk.unkA = 0;
    unk.unkC = arg2;
    unk.unk10 = arg3;
    func_06006720(&unk, 3, 0);
}

// _FileReadNWStartEx
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006720, func_06006720);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006A7C, func_06006A7C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006C00, func_06006C00);

char* func_06006E14(char* path) {
    s32 lastSlash;
    s32 i;

    lastSlash = -1;
    for (i = 0; i < 0x3F; i++) {
        if (path[i] == '\\') {
            lastSlash = i;
        } else if (path[i] == 0) {
            break;
        }
    }

    lastSlash++;
    return path + lastSlash;
}

void func_06006E4C(char* path, char* dst) {
    s32 lastSlash;
    s32 i;

    lastSlash = -1;
    for (i = 0; i < 0x3F; i++) {
        if (path[i] == '\\') {
            lastSlash = i;
        } else if (path[i] == 0) {
            break;
        }
    }

    lastSlash++;
    for (i = 0; i < lastSlash; i++) {
        dst[i] = path[i];
    }
    dst[lastSlash] = 0;
}

s32 func_06006E9C(s32* nsct, GfsHn gfs) {
    s32 sctsz;
    s32 lstsz;

    GFS_GetFileSize(gfs, &sctsz, nsct, &lstsz);
    return (sctsz * (*nsct - 1)) + lstsz;
}

// original name: IsCdOpened
bool IsCdOpened() { return (CDC_GetHirqReq() & CDC_HIRQ_DCHG) ? true : false; }

s32 func_06006EF8(void) {
    s32 stat[4];
    s32* status;
    s32 retries;
    s32 result;
    char* data;

    result = 1;
    data = (char*)&stat[1];
    status = stat;
    retries = 0x10;
    while (CDC_GetPeriStat(&stat[1]) == CDC_ERR_PERI && retries > 0) {
    }
    status[0] = data[0] & 0x0F;
    if (stat[0] == 1 || stat[0] == 2) {
        result = 0;
    }
    return result;
}

bool func_06006F50(void) { return 1; }

// func_06006F5C
bool CdSeek(void) { return 1; }

// func_06006F68
bool GetFileReadStat(void) { return 0; }

s32 func_06006F74(void) { return 1; }
