// SPDX-License-Identifier: AGPL-3.0-or-later
#include "zero.h"
#include "inc_asm.h"
#include "sattypes.h"
#include "lib/sys.h"

#define _SPR2_
#include "lib/spr/spr.h"
#include "game.h"

extern s32* SpGourTbl;
extern s32* DAT_0605c120[];

// func_06004080
void entrypoint(void) {
    func_06030df0();
    Scl_s_reg.tvmode &= ~0x8100;
    SclProcess = 1;
    InitSystem();
    DAT_0605cea2 = 0;
    DAT_0605C658 = 1;
    do {
        func_060040d8();
    } while (true);
}

void MoviePRGClear();
void func_06010400();
void PlaySfx();
void SCL_Vdp2Init();
void SCL_DisplayFrame();
void StartColorOffsetFade(s32, s32);

void func_060040d8(void) {
    g_Timer++;
    func_06007d54();
    switch (DAT_0605cea2) {
    case 0:
        func_0600456c();
        DAT_0605d7f8 = 0;
        func_06004f50(0x20);
        DAT_0605cea0++;
        break;
    case 6:
        if (DAT_0605cea0 == 0) {
            func_06005328();
            DAT_0605cea0++;
            Scl_s_reg.tvmode |= 0x8000;
            SclProcess = 1;
        }
        func_060645E0();
        break;
    case 2:
        if (DAT_0605cea0 == 0) {
            func_06005328();
            DAT_0605cea0++;
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
        if (DAT_0605cea0 == 0) {
            func_06005328();
            DAT_0605cea0++;
        }
        func_06064674();
        break;
    case 8:
        if (DAT_0605cea0 == 0) {
            func_06005328();
            DAT_0605cea0++;
        }
        func_06064580();
        break;
    case 0x11:
        if (*((u32*)&DAT_0605cea0) == 0x11) {
            if (func_06005328() == 0) {
                DAT_0605cea0++;
            }
        } else {
            func_06009838();
            func_0606463c();
            UpdateScrollForRoom();
        }
        break;
    case 5:
        if (DAT_0605cea0 == 0) {
            StartColorOffsetFade(0, 2);
            func_06005328();
            DAT_0605cea0++;
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
        DAT_06057f34 = 0;
        MoviePRGClear();
        func_06005328();
        DAT_06057f34 = func_06064690();
        if ((DAT_06057f34 == 2) && (DAT_0605d7f8 == 0)) {
            SYS_EXECDMP();
        }
        Scl_s_reg.tvmode &= ~0x8100;
        SclProcess = 1;
        SCL_DisplayFrame();
        SCL_Vdp2Init();
        func_06011ce4();
        ReturnToGame();
        func_06004f50(0x31);
        func_06007d54();
        break;
    case 0x31:
        DAT_0605d7f0 = 1;
        func_0600d8bc();
        break;
    }
    if (func_0600fb4c() != 0) {
        if (DAT_0605cea2 == 6) {
            SYS_EXECDMP();
        } else {
            PlaySfx(SET_UNK_0B);
            while (func_06013320() == 0) {
                func_06010400();
                SCL_DisplayFrame();
            }
            func_06012fb4();
            func_0600652C();
            func_0601333c();
            if (DAT_0605cea2 == 2) {
                SYS_EXECDMP();
            }
        }
        StartColorOffsetFade(0, 4);
        func_06004f50(0x30);
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

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60044D0, InitSystem);
void func_0600456C(void) {
    func_06004878();
    func_060046E8();
    func_060047E8();
    func_06007F6C();

    Scl_w_reg.win0_start[0] = 0;
    Scl_w_reg.win0_start[1] = 0xC;
    Scl_w_reg.win0_end[0] = 0x280;
    Scl_w_reg.win0_end[1] = 0xF0;
    Scl_w_reg.wincontrl[0] = 0x383;
    Scl_w_reg.wincontrl[1] = 0x8383;
    Scl_w_reg.wincontrl[2] = 0x83;

    SclProcess = 1;
    func_06009D30();
    DAT_0605D770.unk0 = 0;
    SCL_DisplayFrame();
}

// _RESET_SYSTEM
void func_0600460C(void) {
    CSH_Init(0);
    CSH_AllClr();
    func_06004A10();
    InitSpriteEngine(0);
    func_0600B234();
    func_0600DAB4();
    InitVdp2Display();
    func_06007F6C();

    Scl_w_reg.win0_start[0] = 0;
    Scl_w_reg.win0_start[1] = 0xC;
    Scl_w_reg.win0_end[0] = 0x280;
    Scl_w_reg.win0_end[1] = 0xF0;
    Scl_w_reg.wincontrl[0] = 0x383;
    Scl_w_reg.wincontrl[1] = 0x8383;
    Scl_w_reg.wincontrl[2] = 0x83;
    SclProcess = 1;

    func_06009D30();
    func_0601B600();
    func_06006470();
    func_060082C8();
    InitDebugPrint();
}
void func_060046E8(void) {
    Unk0605cd70* state;
    struct BgTransfer* transfers;
    u32 i;

    DAT_06057F40 = 0;
    D_8003C730 = 0;
    g_Timer = 0;
    DAT_0605c10c = 0;
    g_GameTimer = 0;

    state = (Unk0605cd70*)&DAT_0605cea0;
    state->unk0 = 0;
    state->unk2 = 0;
    state->unk4 = 0xFFFF;
    state->unk8 = 0;

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

    transfers = DAT_0605d6c0;
    for (i = 0; i < 8; i++) {
        transfers[i].tileFlags = 0;
        transfers[i].src = 0;
        transfers[i].dest = 0;
        transfers[i].cnt = 0;
    }

    g_CurrentRoom.stageID = 0;
    g_CurrentRoom.unk2 = 0;
    g_CurrentRoom.unk4 = 0;
    g_CurrentRoom.unk6 = 0;
    DAT_0605d7f0 = 0;
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
    DAT_0605c6e4 = 0;
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
    DAT_0605C6DC = 0;
    currentMusicId = 0;
}
void func_06004878(void) {
    do {
    } while (func_0602BB98(0, 0, 0, 0, 0) == 1);

    do {
        DAT_060505E0 = (DAT_06065D32 != 0) ? &DAT_06065D40 : NULL;
    } while (DAT_060505E0 == NULL);

    DAT_0605D764 = ((DAT_060505E0->unk4 >> 9) ^ 1) & 1;
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

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004924, func_06004924);
void func_06004A10(void) {
    s32 i;
    s8* ptr;
    s32 limit;
    s8 value;

    i = 0;
    ptr = &DAT_06057F50;
    limit = 9;
    value = 0;
    do {
        *ptr++ = value;
        i++;
    } while (i <= limit);

    g_pads->tapped = g_pads->previous = g_pads->pressed = 0;
    ResetPadsRepeat();
    do {
    } while (func_0602BB98(2, 1, 2, (s32)&DAT_06057F50, 0) != 0);
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004A74, func_06004A74);
void func_06004C14(void) {
    s16 previous;
    s16 pressed;

    previous = g_pads[0].pressed;
    g_pads[0].tapped = previous;
    pressed = ~DAT_060505F8->buttons;
    g_pads[0].pressed = pressed;
    g_pads[0].previous = pressed & (previous ^ pressed);
}

s32 g_PadsRepeatTimer[];

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

// _REPEAT_PAD
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004C70, UpdatePadsRepeat);

// func_06004CDC
void InitializePads(void) {
    g_pads[0].previous = g_pads[0].pressed = g_pads[0].tapped =
        g_pads[0].repeat = PAD_NONE;
}

// SET_VBLANK
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004D00, func_06004D00);
void func_06004D84(void) {
    u32 sr;
    u32 imask;

    SH2_GET_SR(sr);
    imask = (sr & 0xF0) >> 4;
    SH2_GET_SR(sr);
    sr &= ~0xF0;
    SH2_SET_SR(sr);

    SCL_VblankStart();
    DAT_0605c10c += 1;
    func_06008EE8();
    SignalSlaveSh2();

    SH2_GET_SR(sr);
    sr &= ~0xF0;
    sr = (imask << 4) | sr;
    SH2_SET_SR(sr);
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004DE8, func_06004DE8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004E50, func_06004E50);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004E94, func_06004E94);

// RETURN_TO_GAME
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004EF0, func_06004EF0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004F50, func_06004F50);
void func_06005208(s32 arg) {
    u16 mode = arg;
    Unk0605cd70* state = &DAT_0605cd70;

    state->unk4 = state->unk2;
    state->unk2 = mode;
    state->unk0 = 0;
    state->unk8 = 0;
    DAT_0605c110 = 0;

    if (mode == 5) {
        DAT_06065470 &= 0xfffe;
        SclProcess = 1;
        DAT_0605d772 = 5;
    } else {
        DAT_0605C100 = 0;
        DAT_0605CD80 = 0;
        DAT_0605CD5C = 0;
        DAT_0605C65C = 0;
        ResetLayerColorCalc();

        switch (mode) {
        case 1:
            if ((g_CurrentRoom.stageID & 0xdf) == 0x0d) {
                func_06009F10();
            }
            if (state->unk4 == 4) {
                state->unk0 += 3;
            } else {
                DAT_0606465C();
                if (state->unk4 == 1) {
                    state->unk0 += 1;
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
const char* logo = "LOGO.PRG";
const char* kcen = "KCEN.MAP";

void func_06005470(void) {
    s32 end;

    ReadFileToAddr("LOGO.PRG", (s32)&DAT_060a5000);
    if (g_FileLoadEnabled != 0) {
        func_0601B184();
    }
    DAT_0605D7DC = (s32)&DAT_00252000;
    end = DAT_0605D7DC + ReadFileToAddr("KCEN.MAP", (s32)&DAT_00252000);
    DAT_0605D7DC = end;
    if (end & 1) {
        DAT_0605D7DC = end + 1;
    }
}

const char* title_p = "TITLE.PRG";
const u16 title_p_len = 0x0009;
const char* title_c = "TITLE.CHR";
const u16 title_c_len = 0x0009;
const char* ascii_f = "ASCII.FON";
const u16 ascii_f_len = 0x0009;
const char* title_m = "TITLE.MAP";
const u16 title_m_len = 0x0009;
void func_06005508(void) {
    s32 end;

    ReadFileToAddr((char*)&DAT_060054D8, (s32)&DAT_060a5000);
    if (g_FileLoadEnabled != 0) {
        func_0601AEF4();
    }
    ReadFileToAddr((char*)&DAT_060054E4, 0x25C13980);
    ReadFileToAddr((char*)&DAT_060054F0, (s32)&DAT_00252000);
    func_060100DC();

    DAT_0605D7DC = 0x00256000;
    end = DAT_0605D7DC + ReadFileToAddr((char*)&DAT_060054FC, 0x00256000);
    DAT_0605D7DC = end;
    if (end & 1) {
        DAT_0605D7DC = end + 1;
    }
    *DAT_0605c120 = (s32*)DAT_0605D7DC;
}

// _READ_LOAD_MODE
s32 func_060055A4(void) { return 0; }
const char* rload_map = "RLOAD.MAP";
const char* load_map = "LOAD.MAP";

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60055C8, func_060055C8);
void func_0600583C(void) {
    s32 end;

    ReadFileToAddr((char*)&DAT_06005810, (s32)&DAT_060a5000);
    if (g_FileLoadEnabled != 0) {
        func_0601AF2C();
    }
    ReadFileToAddr((char*)&DAT_0600581C, 0x25C13980);
    DAT_0605D7DC = 0x254000;
    end = DAT_0605D7DC + ReadFileToAddr((char*)&DAT_0600582C, 0x254000);
    DAT_0605D7DC = end;
    if (end & 1) {
        DAT_0605D7DC = end + 1;
    }
}

const u16 DAT_060058B4[14] = {
    0x5354, 0x4146, 0x462E, 0x5052, 0x4700, 0x0009, 0x5354,
    0x4146, 0x524F, 0x4C4C, 0x2E4D, 0x4150, 0x0000, 0x0009,
};

void func_060058D0(void) {
    s32 end;

    ReadFileToAddr((char*)&DAT_060058B4, (s32)&DAT_060a5000);
    if (g_FileLoadEnabled != 0) {
        func_0601AF44();
    }
    DAT_0605D7DC = 0x254000;
    end = DAT_0605D7DC + ReadFileToAddr((char*)&DAT_060058C0, 0x254000);
    DAT_0605D7DC = end;
    if (end & 1) {
        DAT_0605D7DC = end + 1;
    }
}

const u16 DAT_06005938[] = {0x4D4F, 0x5649, 0x452E, 0x5052, 0x4700, 0x0009};

extern s32 func_0601B1B4(void);

void func_06005944(void) {
    ReadFileToAddr((char*)&DAT_06005938, (s32)&DAT_06066000);
    if (g_FileLoadEnabled != 0) {
        func_0601B1B4();
    }
}

const u16 DAT_0600597C[60] = {
    0x5334, 0x3330, 0x2E50, 0x544E, 0x0000, 0x0009, 0x5334, 0x3330, 0x2E43,
    0x4852, 0x0000, 0x0009, 0x5334, 0x3430, 0x2E50, 0x544E, 0x0000, 0x0009,
    0x5334, 0x3430, 0x2E43, 0x4852, 0x0000, 0x0009, 0x5334, 0x3130, 0x2E50,
    0x544E, 0x0000, 0x0009, 0x5334, 0x3130, 0x2E43, 0x4852, 0x0000, 0x0009,
    0x5334, 0x3030, 0x2E50, 0x544E, 0x0000, 0x0009, 0x5334, 0x3030, 0x2E43,
    0x4852, 0x0000, 0x0009, 0x454E, 0x4449, 0x4E47, 0x2E50, 0x5247, 0x0000,
    0x454E, 0x4449, 0x4E47, 0x2E43, 0x4852, 0x0000,
};
void func_060059F4(void) {
    ReadFileToAddr((char*)&DAT_060059DC, (s32)&g_StageOverlayData);
    if (g_FileLoadEnabled != 0) {
        func_0601B19C();
    }
    ReadFileToAddr((char*)&DAT_060059E8, 0x25C2A980);
    if (DAT_0605D7FC != 4 && DAT_0605D7FC != 6) {
        ReadFileToAddr(DAT_06038A14[DAT_0605D7FC - 1][0], 0x25E22000);
        ReadFileToAddr(DAT_06038A14[DAT_0605D7FC - 1][1], 0x25E60000);
    }
    DAT_060645C4();
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6005A90, func_06005A90);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6005E3C, func_06005E3C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600607C, func_0600607C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006170, func_06006170);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60062F8, func_060062F8);
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
            DAT_06038a44 = index;
            DAT_06050668 = index;
            index = 1;
        case 1:
            result = func_06006170();
            break;
        case 2:
            result = func_060062F8(0, &DAT_0605AE80);
            break;
        }

        if (result == 1) {
            DAT_06050668 = 0;
            index += 1;
        } else if (result == 0) {
            success = 0;
            break;
        }
    } while (index <= 2);

    if (success == 0) {
        DAT_0600026C();
    }

    DAT_0605AE8C = &DAT_0605064C;
    *(char*)((char*)&DAT_0605064C - 0x40) = 0;
    return success;
}

void func_0600652C(void) {
    func_0601B600();
    DAT_06038a44 = 0;
}

struct Unk0600654C {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unka;
    s32 unkc;
    s32 unk10;
};
// func_0600654C
s32 ReadFileToAddr(char* path, s32 addr) {
    struct Unk0600654C unk;
    unk.unk0 = (s32)path;
    unk.unk4 = addr;
    unk.unk8 = -1;
    unk.unka = 0;
    return func_06006574(&unk);
}

// _FileReadSetAdrEx
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006574, func_06006574);

// func_060066F0
void ReadFileToAddrAsync(u32 param_1, u32 param_2, u32 param_3, u32 param_4) {
    struct Unk0600654C unk;
    unk.unk0 = param_1;
    unk.unk4 = param_2;
    unk.unk8 = -1;
    unk.unka = 0;
    unk.unkc = param_3;
    unk.unk10 = param_4;
    func_06006720(&unk, 3, 0);
}

// _FileReadNWStartEx
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006720, func_06006720);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006A7C, func_06006A7C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006C00, func_06006C00);
s8* func_06006E14(s8* path) {
    s32 lastSlash;
    s32 i;

    lastSlash = -1;
    i = 0;
    do {
        if (path[i] == '\\') {
            lastSlash = i;
        } else if (path[i] == 0) {
            break;
        }
        i++;
    } while (i <= 0x3E);

    lastSlash++;
    return path + lastSlash;
}

const u16 DAT_06006E4A = 0x0009;
void func_06006E4C(s8* path, s8* dst) {
    s32 lastSlash;
    s32 i;

    lastSlash = -1;
    i = 0;
    do {
        if (path[i] == '\\') {
            lastSlash = i;
        } else if (path[i] == 0) {
            break;
        }
        i++;
    } while (i <= 0x3E);

    lastSlash++;
    for (i = 0; i < lastSlash; i++) {
        dst[i] = path[i];
    }
    dst[lastSlash] = 0;
}

s32 func_06006E9C(s32* arg0, s32 arg1) {
    s32 stride;
    s32 base;

    func_0601B910(arg1, &stride, arg0, &base);
    return (stride * (*arg0 - 1)) + base;
}

// _IsCdOpened
u32 func_06006ED4() { return (func_0602DCFC() >> 5) & 1; }

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
    while (func_0602D754(&stat[1]) == -8 && retries > 0) {
    }
    status[0] = data[0] & 0x0F;
    if ((u32)(stat[0] - 1) <= 1U) {
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

const u16 DAT_06006F7E = 0x0000;
const u16 DAT_06006F80 = 0x0000;
const char weapon0_prg[] = "WEAPON0.PRG";
const char weapon0_chr[] = "WEAPON0.CHR";
const char dummy_dat[] = "DUMMY.DAT";
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006FA8, func_06006FA8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60071C8, func_060071C8);

s32 func_060076D0(s32 arg0) {
    s32 result;

    if (g_Status.equipment[4] == 0x19) {
        result = DAT_060645AC + 0x2D4C;
    } else {
        result = DAT_060645AC + (g_Status.equipment[arg0] * 0x34);
    }
    return result;
}

// _CD_READ_OUT
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007714, func_06007714);

struct Unk0600654C prg_info;
struct Unk0600654C chr_info;

char* WEAPON0_PRG;
char* WEAPON0_CHR;
char* WEAPON1_PRG;
char* WEAPON1_CHR;

void func_06007824(s32 arg0, s32 arg1) {
    if ((g_FileLoadEnabled == 0) || (0x3F < arg1)) {
        func_0601AE5C(arg0, arg1);
    } else {
        prg_info.unka = arg1 * 6;
        chr_info.unka = arg1 * 8;
        if (arg0 == 0) {
            prg_info.unk0 = &WEAPON0_PRG;
            prg_info.unk4 = 0x060D6000;
            chr_info.unk0 = &WEAPON0_CHR;
            chr_info.unk4 = VRAM_ADDR + 0x1D980;
        } else {
            prg_info.unk0 = &WEAPON1_PRG;
            prg_info.unk4 = 0x060D9000;
            chr_info.unk0 = &WEAPON1_CHR;
            chr_info.unk4 = VRAM_ADDR + 0x21980;
        }
        func_06006574(&prg_info);
        func_0601AE2C(arg0);
        func_06006574(&chr_info);
        func_0600C298(arg0);
        func_0600C0C4(arg0);
    }
}

extern struct Unk0600654C DAT_06038B6C;
extern struct Unk0600654C DAT_06038BAC;

extern s32 DAT_06038C24[][2];
void SetServantResourceList(void);
void func_0600C254(void);
void func_0600C0FC(void);

void func_060078EC(s32 arg0) {
    if (g_FileLoadEnabled != 0) {
        DAT_06038B6C.unk0 = DAT_06038C24[arg0][0];
        func_06006574(&DAT_06038B6C);
        SetServantResourceList();
        DAT_06038BAC.unk0 = DAT_06038C24[arg0][1];
        DAT_06038BAC.unk4 = 0x25C25980;
        func_06006574(&DAT_06038BAC);
        func_0600C254();
        func_0600C0FC();
    }
}

// _InitVdp1
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007968, InitSpriteEngine);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007A34, AllocSpriteCharVram);
u16 func_06007B34(SprLookupTbl* tbl) {
    Uint16* entry;
    s32 i;
    u16 tblNo;
    s32 last;
    s32 flags;

    tblNo = d_0605AEA8;
    if (tblNo <= 0x1FFU) {
        if (tbl != NULL) {
            entry = tbl->entry;
            i = 0;
            last = 0xF;
            flags = ~0x7FFF;
            do {
                *entry |= flags;
                i += 1;
                entry++;
            } while (i <= last);
            SPR_2SetLookupTbl(tblNo, tbl);
        }
        d_0605AEA8 += 1;
    }
    return tblNo;
}

s32 func_06007B8C(s16* colors) {
    u32 charNo;
    s16* dest;
    s32 i;

    charNo = (u16)d_0605AEB0;
    if (charNo <= 0x3E) {
        if (colors != NULL) {
            dest = (s16*)(SCL_COLRAM_ADDR + 0x800 + charNo * 0x20);

            for (i = 0; i <= 0xF; i++) {
                *dest++ = *colors++ & 0x7FFF;
            }
        }
        d_0605AEB0++;
    }
    return charNo | 0x4000;
}

u16 LocalLookupTblNoToVram(u16 arg0);

u16 func_06007BE0(s16* colors, s32 arg1) {
    u16 tblNo;
    u16 index;
    u16 limit;
    u16 mask;
    u16 vram;
    s16* dst;
    SprLookupTbl lookupTbl;

    tblNo = d_0605AEA8;
    if (tblNo > 0x1FFU) {
        return tblNo;
    }
    if ((u16)d_0605AEB0 > 0x3EU) {
        return 0x4000 | d_0605AEB0;
    }
    if (colors != NULL) {
        dst = (s16*)(SCL_COLRAM_ADDR + 0x800 + ((u16)d_0605AEB0 << 5));
        index = 0;
        limit = 0xF;
        mask = 0x7FFF;
        do {
            *dst++ = *colors++ & mask;
            index++;
        } while (index <= limit);

        vram = LocalLookupTblNoToVram(d_0605AEB0);
        index = 0;
        do {
            lookupTbl.entry[index] = vram + index;
            index++;
        } while (index <= 0xFU);

        SPR_2SetLookupTbl(d_0605AEA8, &lookupTbl);
    }
    d_0605AEA8 += 1;
    d_0605AEB0 += 1;
    return tblNo;
}

// _SprSetGourTbl
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007CA0, AllocGourTbl);

// func_06007CE0
u16 LocalLookupTblNoToVram(u16 arg0) { return arg0 * 0x10 + 0x400; }

s16 d_0605BECA;
s16 d_0605AEA8;
s16 d_0605AEB0;
s16 d_0605BEC8;
s32 d_06038dbc;
s32 DAT_0605BEC4;
s32 d_060576AC;

// func_06007CF8
void ResetSpriteVram() {
    SPR_2ClrAllChar();
    d_0605BECA = 0;
    d_0605AEA8 = 0;
    d_0605AEB0 = 0;
    d_0605BEC8 = 0x304;
    d_060576AC = 0;
    DAT_0605BEC4 = 0x00011180;
    d_06038dbc = 0;
}

typedef union {
    SprSpCmd cmd;
    SprSpCmdR raw;
} SprCmdBuf;

extern u16 d_0605AEA0[4];
extern SprSpCmd DAT_06050684[];

void func_06007D54(void) {
    SprCmdBuf sp;

    SPR_2OpenCommand(1);

    sp.cmd.control = 0x1009;
    sp.raw.dummy[5] = DAT_0605BEC0;
    if (SpMstCmdPos <= 0x277) {
        SPR_2Cmd(0, &sp.cmd);
        d_0605AEAC += 0x20;
    }

    sp.cmd.control = 0x1008;
    sp.raw.dummy[3] = ((s32*)d_0605AEA0)[0];
    sp.raw.dummy[5] = ((s32*)d_0605AEA0)[1];
    if (SpMstCmdPos <= 0x277) {
        SPR_2Cmd(0, &sp.cmd);
        d_0605AEAC += 0x20;
    }

    sp.cmd.control = 0x100A;
    sp.raw.dummy[3] = DAT_0600E23C;
    if (SpMstCmdPos <= 0x277) {
        SPR_2Cmd(0, &sp.cmd);
        d_0605AEAC += 0x20;
    }

    d_0605AEAC = (s32)&DAT_06050684[SpMstCmdPos];
}

s32 d_06038c5c;
s32 d_06038c5c;
s32 d_0605BEBE;
u16 d_0605AEA0[4];
// func_06007E14
void CloseSpriteList(void) {
    SprSpCmd cmd;

    if (d_06038c5c) {
        d_06038c5c--;
        cmd.control = JUMP_ASSIGN | FUNC_TEXTURE;
        cmd.drawMode = ECDSPD_DISABLE;
        cmd.color = RGB16_COLOR(0, 0, 0);
        cmd.ax = cmd.dx = 0;
        cmd.bx = cmd.cx = d_0605BEBE;
        cmd.ay = cmd.by = 0;
        cmd.cy = cmd.dy = d_0605AEA0[1] - 1;
        SPR_2Cmd(0x1FF, &cmd);
        d_0605AEAC += 0x20;
    }

    SPR_2CloseCommand();
}

// func_06007EB8
void SetSpriteEraseData(s16 param_1) {
    SPR_2FrameEraseData(param_1);
    SPR_SetEraseData(
        param_1, d_0605AEA0[0], d_0605AEA0[1], d_0605AEA0[2], d_0605AEA0[3]);
}

// func_06007F04
void InitVdp2Display(void) {
    SCL_Vdp2Init();
    SCL_SetDisplayMode(0, 1, 0);
    SPR_2FrameChgIntr(-1);
    SclPriBuffDirty.SclColOffset = 1;
    SclColOffset.ColorOffsetEnable = 0x6f;
    SCL_SetColOffset(0, 0x6f, 0xFF01, 0xFF01, 0xFF01);
    SetVdp2BackgroundColor();
}

// _SET_VDP2_VRAM
void func_06007F6C(void) {
    SclVramConfig cfg;
    SCL_InitVramConfigTb(&cfg);
    cfg.vramModeA = 0;
    cfg.vramModeB = 1;
    cfg.vramA0 = cfg.vramB0 = cfg.vramB1 = 0;
    SCL_SetVramConfig(&cfg);
    SCL_SetColRamMode(1);
    SCL_DisplayFrame();
    SCL_SetSpriteMode(5, 1, 0);

    SCL_SetPriority(4, 7);
    SCL_SetPriority(8, 4);
    SCL_SetPriority(0x20, 3);
    SCL_SetPriority(0x10, 2);
    SCL_SetPriority(0x100, 4);
    SCL_SetPriority(0x200, 1);
    SCL_SetPriority(0x400, 2);
    SCL_SetPriority(0x800, 3);
    SCL_SetPriority(0x1000, 4);
    SCL_SetPriority(0x2000, 6);
    SCL_SetPriority(0x4000, 7);
    SCL_SetPriority(0x8000, 0);

    SCL_SetColMixMode(6, 1);
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008048, ResetLayerColorCalc);
extern s16 DAT_0606570C;

void func_060080EC(s32 arg0) {
    if (arg0 == 1) {
        SclPriBuffDirty.SclOtherPri = 1;
        DAT_0606570C &= ~0x100;
    } else {
        SclPriBuffDirty.SclOtherPri = 1;
        DAT_0606570C = (DAT_0606570C & ~0x100) | 0x100;
    }
}

// SetVdp2BackgroundColor
void SetVdp2BackgroundColor(void) {
    s16 local_c[2];
    local_c[0] = 0;
    SCL_SetBack(SCL_VDP2_VRAM + 0x7FE20, 1, local_c);
}

void func_0600815C(u8 r, u8 g, u8 b) {
    Uint16 color;

    color = ((b << 0xA) + (g << 5) + r) - 0x8000;
    SCL_SetBack(SCL_VDP2_VRAM + 0x7FE20, 1, &color);
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600819C, BlankScreen);

// func_0600824C
void InitScuDma(void) {
    // sega library func
    DMA_ScuInit();
}

// _VDP1_TRANS
void func_06008264(void) {
    FlushVramTransfers();
    func_06008488();
    func_060082E8();
    func_06008464();
}

// func_06008298
void TransferAllBgLayers(void) {
    s32 i;
    for (i = 0; i < 8; i++) {
        TransferBgLayer(i);
    }
}

// _INIT_TRANS
void func_060082C8(void) {
    func_060082E8();
    func_0600841C();
}

void func_060082E8(void) {
    s32* ptr;
    s32 i;

    ptr = DAT_060576B0;
    for (i = 0; i < 0x10; i++, ptr += 3) {
        ptr[2] = 0;
        ptr[0] = 0;
        ptr[1] = 0;
    }
    DAT_06057770 = 0;
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600831C, QueueVramTransfer);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008374, FlushVramTransfers);
void func_0600841C(void) {
    s32 i;
    s32 last;
    s32 zero;
    s32 fill;
    Unk0605DB60* entry;
    s16* p8;
    s16* pA;
    s16* pC;
    s16* pE;

    entry = d_0605DB60;
    i = 0;
    last = 0x1F;
    zero = 0;
    fill = -1;
    pE = &entry->unkE;
    pC = &entry->unkC;
    pA = &entry->unkA;
    p8 = &entry->unk8;

    for (; i <= last; i++, entry++) {
        entry->unk0 = zero;
        entry->unk4 = zero;
        *p8 = fill;
        p8 += 8;
        *pA = fill;
        pA += 8;
        *pC = fill;
        pC += 8;
        *pE = fill;
        pE += 8;
    }
}

void func_06008464(void) {
    Unk0605DB60* entry;
    s32 i;

    entry = d_0605DB60;

    for (i = 0; i < 0x20; i++) {
        entry->unk0 = 0;
        entry->unk4 = 0;
        entry++;
    }
}

void func_06008488(void) {
    s32* chars;
    s32* palettes;
    Unk0605DB60* entry;
    s32* src;
    s32 i;

    chars = (s32*)(((u16)DAT_0605aec0[0][0] * 8) + 0x25C00000);
    palettes = (s32*)((SPR_2LookupTblNoToVram(0x10U) * 8) + 0x25C00000);
    entry = d_0605DB60;
    i = 0;
    do {
        src = (s32*)entry->unk0;
        if (src != NULL) {
            DMA_CpuMemCopy2(chars, src, 0x40U);
            do {
            } while (DMA_CpuResult() == 2);
        }
        src = (s32*)entry->unk4;
        if (src != NULL) {
            DMA_CpuMemCopy2(palettes, src, 0x10U);
            do {
            } while (DMA_CpuResult() == 2);
        }
        i += 1;
        entry++;
        chars += 0x20;
        palettes += 8;
    } while (i <= 0x1F);
}
s32 func_06008524(u32 dest, u32 src, u32 cnt) {
    u32 first;
    u32 i;
    struct BgTransfer* transfer;

    first = 0;
    if (DAT_0605cd70.unk0 == 0) {
        first = 4;
    }
    if (DAT_0605cd70.unk0 == 1) {
        first = 3;
    }
    transfer = &DAT_0605d6c0[first];

    for (i = first; i < 8; i++, transfer++) {
        if (transfer->cnt == 0) {
            transfer->src = src;
            transfer->dest = dest;
            transfer->cnt = cnt;
            transfer->tileFlags |= 8;
            return 1;
        }
    }
    return 0;
}

// Handles transfer of background tile graphics
// func_06008588
void TransferBgLayer(int param_1) {
    s32 cnt;
    struct BgTransfer* puVar5;
    struct Unk0605CD90* puVar6;

    puVar5 = &DAT_0605d6c0[param_1];
    puVar6 = &DAT_0605CD90[param_1];
    if (puVar5->tileFlags == 0) {
        return;
    }
    if (puVar5->tileFlags & 1) {
        cnt =
            DecompressLZSS(puVar6->unkc, (s32)SYS_buf_060485E0, puVar6->unk18);
        DmaScroll((s32*)SYS_buf_060485E0, puVar6->dst0, cnt);
    }
    if (puVar5->tileFlags & 2) {
        cnt =
            DecompressLZSS(puVar6->unk10, (s32)SYS_buf_060485E0, puVar6->unk1c);
        DmaScroll((s32*)SYS_buf_060485E0, puVar6->dst4, cnt);
    }
    if (puVar5->tileFlags & 4) {
        if (DAT_0605cd70.unk2 == 4) {
            BuildSubDispTilemap(puVar6);
        } else {
            func_0600871C(puVar6, &DAT_0605c680, param_1);
        }
    }
    if (puVar5->tileFlags & 8) {
        DmaScroll(puVar5->src, puVar5->dest, puVar5->cnt);
    }
    if (puVar5->tileFlags & 0x10) {
        DmaScroll(puVar5->src, puVar5->dest, puVar5->cnt);
    }
    if (puVar5->tileFlags & 0x20) {
        DmaScroll(puVar5->src, puVar5->dest, puVar5->cnt);
    }
    if (puVar5->tileFlags & 0x40) {
        cnt = DecompressLZSS(puVar6->unkc, DMA_SRC_ADDR, puVar6->unk18);
        DmaScroll(DMA_SRC_ADDR, puVar6->dst0, cnt);
    }
    if (puVar5->tileFlags & 0x80) {
        cnt = DecompressLZSS(puVar6->unk10, DMA_SRC_ADDR, puVar6->unk1c);
        DmaScroll(DMA_SRC_ADDR, puVar6->dst4, cnt);
    }
    puVar5->tileFlags = 0;
    puVar5->cnt = 0;
    puVar5->dest = 0;
    puVar5->src = 0;
    return;
}

// _DMA_SCROLL
// func_060086E8
void DmaScroll(s32* src, s32* dest, u32 cnt) {
    s32 result;

    if (cnt != 0) {
        // sega DMA lib
        DMA_CpuMemCopy2(dest, src, cnt >> 1);
        do {
            result = DMA_CpuResult();
        } while (result == 2);
    }
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600871C, func_0600871C);

// func_060089F0
void BuildSubDispTilemap(struct Unk0605CD90* param_1) {
    u16 sVar2;
    s16* psVar5;
    s16* psVar7;
    u16 i; // r2
    u16 j; // r1

    psVar7 = DAT_0605c120[3] + 1;
    sVar2 = param_1->unk24 * 0x1000;
    j = 0;
    psVar5 = param_1->unk8 + j * 0x20;
    for (j = 0; j < 32; j++) {
        for (i = 0; i < 32; i++) {
            *psVar5++ = *psVar7++ + sVar2;
        }
        psVar5 = 0x400 + param_1->unk8 + j * 0x20;

        for (i = 0; i < 10; i++) {
            *psVar5++ = *psVar7++ + sVar2;
        }
        psVar5 = param_1->unk8 + (j + 1) * 0x20;
    }
}

void func_06008A70(void) {
    func_06008AB4();
    if (g_CurrentRoom.stageID == 0x41 && g_CurrentRoom.unk4 == 0x12) {
        func_06008C2C();
    } else {
        func_06008B20();
    }
}
void func_06008AB4(s32 arg0, s32 arg1, s32 arg2) {
    if (DAT_0605cd70.unk2 != 4 &&
        (DAT_0605cd70.unk0 != 0x91 || DAT_0605cd70.unk2 != 1) &&
        (u16)DAT_0605d772 != 4) {
        if (DAT_0605cd70.unk2 != 5 || DAT_0605cd70.unk0 <= 2) {
            func_0600BD68(arg0, arg1, arg2, &DAT_0605cd70);
        }
        func_0600DE38();
        func_0600E164();
    }
}

// _SCROLL_DSP
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008B20, func_06008B20);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008C2C, func_06008C2C);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f6008D04, func_06008D04);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f6008EE8, func_06008EE8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008FF0, func_800EA5AC);

void func_06009010(u8* rgb) {
    Sint16 enabled;

    enabled = DAT_0605C6DC;
    if (enabled != 0) {
        SCL_SetColOffset(0, 0x6F, rgb[0], rgb[1], rgb[2]);
    } else {
        SCL_SetColOffset(0, 0x6F, 0, 0, enabled);
    }
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009058, func_06009058);

// _GAME_SCROLL_SET
void func_06009510(s32 param_1) {
    s32 scrollId;
    s32 i;
    s32 bound;
    struct Unk0605CD90* ptr;

    scrollId = (u16)param_1;
    i = 0;
    ptr = DAT_0605CD90;

    for (; i < 4; i++, ptr++) {
        ptr->unk18 = 0;
    }

    if (scrollId == 0x50) {
        DAT_06064624(0);
    } else {
        bound = 0x50;
        if (scrollId >= bound) {
            bound = 0x63;
            if (scrollId <= bound) {
                bound = 0x60;
                if (scrollId >= bound) {
                    DAT_06064624(1);
                } else {
                    DAT_0606461C(scrollId);
                }
            } else {
                DAT_0606461C(scrollId);
            }
        } else {
            DAT_0606461C(scrollId);
        }
    }
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009570, func_06009570);

void func_0600971C(void) {
    if (g_PlayableCharacter == 0) {
        SCL_SetDisplayMode(0, 1, 0);
        SCL_SetCycleTable(DAT_06038D70);
    }

    Scl_w_reg.win0_start[0] = 0;
    Scl_w_reg.win0_start[1] = 12;
    Scl_w_reg.win0_end[0] = 0x0280;
    Scl_w_reg.win0_end[1] = 0x00F0;
    Scl_w_reg.wincontrl[0] = 0x0383;
    Scl_w_reg.wincontrl[1] = 0x8383;
    Scl_w_reg.wincontrl[2] = 0x0083;

    SclProcess = 1;
    DAT_06065470 &= 0xFFFE;
    SclProcess = 1;
}

void func_060097B4(Entity* arg0, s32 arg1) {
    u16 step;
    u16 step_s;
    s32 x;
    s32 y;

    SCL_Open(8 << arg1);
    step = arg0->step;
    x = 0;
    y = 0xA0000;
    if (step != 0) {
        x = (s32)DAT_0605c680.unk34 / (s32)step;
    }
    step_s = arg0->step_s;
    if (step_s != 0) {
        y = (s32)DAT_0605c680.unk38 / (s32)step_s;
    }
    SCL_MoveTo(x, y, 0);
    SCL_Close();
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009838, func_06009838);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60098F0, func_060098F0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009AE8, func_06009AE8);

// _UPDATE_BG
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009CCC, func_06009CCC);

void func_06009D30(void) {
    u32 i;

    i = 0;
    do {
        func_06009D60(i);
        i += 1;
    } while (i <= 3U);
}
void func_06009D60(u32 bank) {
    u32* dst;
    u32 count;

    if (bank <= 1) {
        dst = (u32*)(bank * 0x20000 + 0x25E00000);
        for (count = 0; count <= 0x7FFF; count++) {
            *dst++ = 0;
        }
        return;
    }

    dst = (u32*)((bank - 2) * 0x20000 + 0x25E40000);
    for (count = 0; count <= 0x7FFF; count++) {
        *dst++ = 0;
    }
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009DB0, func_06009DB0);
void func_06009F10(void) {
    SclConfig scfg;

    SCL_InitConfigTb(&scfg);
    scfg.charsize = 0;
    scfg.pnamesize = 1;
    scfg.platesize = 0;
    scfg.coltype = 0;
    scfg.datatype = 0;
    scfg.mapover = 0;
    scfg.flip = 0;
    scfg.plate_addr[3] = 0x25E48000;
    scfg.plate_addr[2] = 0x25E48000;
    scfg.plate_addr[1] = 0x25E48000;
    scfg.plate_addr[0] = 0x25E48000;
    scfg.patnamecontrl = 0x21;
    SCL_SetConfig(0x10, &scfg);
}

// _X_SCROLL_TRANS
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009F84, func_06009F84);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A030, func_0600A030);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A088, func_0600A088);
void func_0600A240(s32 param_1) {
    if (param_1 != 0) {
        DAT_0605D910[0x4D] = 1;
    } else {
        DAT_0605D910[4] = 1;
    }
}

// _SetCharTrans
void func_0600A264(u16 arg0, s32 arg1, s32 arg2) {
    QueueVramTransfer(DAT_0605aec0[arg0][0] * 8 + 0x25C00000, arg2, arg1);
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A29C, LookupTblNoToVramAddr);

// func_0600A304
void SetSprGourTable(u16 arg0, SprGourTbl* gourTbl) {
    SPR_2SetGourTbl(arg0, gourTbl);
}

// _SetPlTransNonSeparateAura
void func_0600A31C(void) { DAT_0605D910[3] = 1; }

void func_0600A330(void) {
    if (g_PlayableCharacter == 0) {
        DAT_0605D910[3] = 0;
    }
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A350, func_0600A350);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A490, func_0600A490);
extern u8 d_060578A0[];

// MapBytesThroughLutPair
void func_0600A5FC(u8* src, u8* dst0, u8* dst1, s32 count) {
    u8 value;

    if (count > 0) {
        do {
            value = *src++;
            *dst0++ = DAT_060577A0[value];
            *dst1++ = d_060578A0[value];
            count--;
        } while (count > 0);
    }
}

u8 d_060578A0[];
// func_0600A62C
void MapBytesThroughLut(u8* param_1, u8* param_2, int param_3) {
    for (; param_3 > 0; param_3--) {
        *param_2++ = d_060578A0[*param_1++];
    }
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A650, func_0600A650);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A77C, func_0600A77C);

// _UpdateMirage
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600AA18, func_0600AA18);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600AB60, func_0600AB60);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600AC30, func_0600AC30);

// func_0600AD80
int GetEnemyPlayerCharaAddr(void) {
    return -(s32)&DAT_00252000 + (s32)&DAT_00258000;
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600AD98, InitPaletteRemapLuts);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600AE30, func_0600AE30);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600AEE4, func_0600AEE4);
void func_0600AFA8(SpriteObject* sprite, SaturnSpriteFrameHeader* frame) {
    SpritePart* part;
    SaturnSpritePart* src;
    u16* in;
    u16* out;
    s32 i;
    s32 count;

    sprite->flags = frame->header;
    sprite->slotAndStreamId =
        (sprite->slotAndStreamId & ~0x7F) | (frame->commandFlags & 0x7F);

    count = (frame->header & 0x3F00) >> 8;
    part = sprite->parts;
    src = (SaturnSpritePart*)(frame + 1);
    i = 0;

    while (i < count) {
        in = (u16*)src;
        part->attributes = *in++;
        ++i;
        out = (u16*)part;
        ++out;
        *out++ = *in++;
        *out++ = *in++;
        *out = *in;
        src++;
        part = part->next;
    }
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600B004, func_0600B004);

// _SetParts
void func_0600B084(SpritePart* part, SaturnSpritePart* src, s32 count) {
    s32 i;
    u16* in;
    u16* out;
    u16 attributes;

    for (i = 0; i < count; i++, src++) {
        in = (u16*)src;
        out = (u16*)part;
        attributes = *in++;
        *out++ = attributes;
        *out++ = *in++;
        *out++ = *in++;
        *out = *in;
        part = part->next;
    }
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600B0B8, func_0600B0B8);

void func_0600B104(u16* param_1, int param_2, int param_3)

{
    s32 i;
    for (i = 0; i < param_3; i++) {
        *param_1 = *param_1 & 0xE0FF | (param_2 << 8);
        param_1 = *(u16**)(param_1 + 6);
    }
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600B12C, func_0600B12C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600B1A8, AllocSpriteObject);

void func_0600B234(void) {
    InitPaletteRemapLuts();
    func_0600B254();
}

// _ClearOdma
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600B254, func_0600B254);

static inline SpritePart* AllocSpriteParts(s32 maxParts) {
    SpritePart* head;
    SpritePart* node;

    if (g_SpritePartsInUse + maxParts > SPRITE_PART_MAX) {
        return NULL;
    }

    head = node = g_SpritePartFreeList;
    g_SpritePartsInUse += maxParts;
    for (; maxParts > 1; maxParts--) {
        node->attributes = 0;
        *(int*)&node->rotate = 0x00004040;
        node = node->next;
    }
    g_SpritePartFreeList = node->next;
    node->attributes = 0;
    *(int*)&node->rotate = 0x00004040;
    node->next = NULL;
    return head;
}

// func_0600B344
SpriteObject* CreateSpriteObject(
    u16 charBase, u16 clutBase, SaturnSpriteImage* images, s32 maxParts) {
    SpriteObject* obj;
    SpritePart* head;

    obj = AllocSpriteObject();
    if (obj == NULL) {
        return NULL;
    }

    head = AllocSpriteParts(maxParts);
    if (head == NULL) {
        obj->next = g_SpriteObjectFreeList;
        g_SpriteObjectFreeList = obj;
        g_SpriteObjectsInUse--;
        return NULL;
    }

    obj->charBase = charBase;
    obj->clutBase = clutBase;
    obj->images = images;
    obj->parts = head;
    obj->next = NULL;

    if (g_SpriteListTail == NULL) {
        g_SpriteListTail = obj;
        g_SpriteListHead = obj;
    } else {
        g_SpriteListTail->next = obj;
        g_SpriteListTail = obj;
    }
    g_SpriteListCount++;
    return obj;
}

void func_0600B428(SpriteObject* obj) {
    SpriteObject* prev;
    SpritePart* firstPart;
    SpritePart* lastPart;
    SpritePart* next;

    if (g_SpriteListCount > 0) {
        if (g_SpriteListHead == obj) {
            g_SpriteListHead = obj->next;
            prev = NULL;
        } else {
            prev = g_SpriteListHead;
            for (; prev->next != obj; prev = prev->next) {
            }
            prev->next = obj->next;
        }
        if (g_SpriteListTail == obj) {
            g_SpriteListTail = prev;
        }
        firstPart = obj->parts;
        next = firstPart->next;
        lastPart = firstPart;
        while (next != NULL) {
            lastPart = lastPart->next;
            g_SpritePartsInUse--;
            next = lastPart->next;
        }
        g_SpritePartsInUse--;
        lastPart->next = g_SpritePartFreeList;
        g_SpritePartFreeList = firstPart;
        obj->next = g_SpriteObjectFreeList;
        g_SpriteObjectFreeList = obj;
        g_SpriteObjectsInUse--;
        g_SpriteListCount--;
    }
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600B4C4, func_0600B4C4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600B954, func_0600B954);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600BA24, func_0600BA24);

void func_0600BCE0(s32* mtx, s16 angle) {
    s32 sincos[2];
    s32 cosv;
    s32 sinv;
    s32 axis;

    rsincos(angle, &sincos[0], &sincos[1]);
    cosv = sincos[1];
    sinv = sincos[0];
    axis = mtx[0];
    sincos[1] = cosv * 0x10;
    sincos[0] = sinv * 0x10;
    mtx[0] = MTH_Mul(sincos[1], axis);
    mtx[1] = MTH_Mul(sincos[0], axis);
    axis = mtx[3];
    mtx[2] = -MTH_Mul(sincos[0], axis);
    mtx[3] = MTH_Mul(sincos[1], axis);
}

// func_0600BD4C
int GetSpriteObjectGourTbl(u8* param_1) { return SpGourTbl + param_1[2] * 2; }

// _Odma
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600BD68, func_0600BD68);

// _AllocGameSprite
void func_0600BE18(s32 arg0) {
    if ((u32)(arg0 - 1) <= 1U) {
        func_0600BEA8();
        func_0600BF08();
        func_0600BF38();
    } else {
        func_0600BEA8();
        func_0600BF08();
        func_0600BF38();
        func_0600BF8C();
        func_0600BFD8();
    }
    func_0600C18C();
}

void func_0600BE7C(void) {
    func_0600BEA8();
    func_0600BF08();
    func_0600C18C();
}

void func_0600BEA8(void) {
    s16 size[2];
    Unk0605DB60* entry;
    s32 i;
    s32 last;
    s32 fill;
    s16* p8;
    s16* pA;
    s16* pC;
    s16* pE;

    size[0] = 0x80;
    size[1] = 0x40;
    AllocSpriteCharVram(8, 0, size, 0);

    entry = d_0605DB60;
    i = 0;
    last = 0x1F;
    fill = -1;
    pE = &entry->unkE;
    pC = &entry->unkC;
    pA = &entry->unkA;
    p8 = &entry->unk8;

    do {
        *p8 = fill;
        p8 += 8;
        *pA = fill;
        pA += 8;
        *pC = fill;
        pC += 8;
        *pE = fill;
        pE += 8;
        i++;
    } while (i <= last);
}
void func_0600BF08(void) {
    u16 sp[2];

    sp[0] = 0x60;
    sp[1] = 0x80;
    AllocSpriteCharVram(8, 0, sp, 0);
}

void func_0600BF38(void) {
    s16 local[2];
    s32 i;

    local[0] = 0x80;
    local[1] = 0x50;
    i = 0;
    do {
        AllocSpriteCharVram(8, 0, local, 0);
        i++;
    } while (i <= 7);
    func_0600AB60();
}
void func_0600BF8C(void) {
    s16 local[2];
    s32 i;

    local[0] = 0x100;
    local[1] = 0x80;
    i = 0;
    do {
        AllocSpriteCharVram(8, 0, local, 0);
        i++;
    } while (i <= 1);
}
void func_0600BFD8(void) {
    s16 local[2];

    local[0] = 0x100;
    local[1] = 0xA0;
    AllocSpriteCharVram(8, 0, local, 0);
}

void func_0600C00C(void) {
    SaturnSpriteResource** banks;
    s32 i;
    SaturnSpriteImage* images;
    s32 palette;
    SaturnSpriteResource* bank;

    banks = DAT_06064650;
    banks[0]->allocationIndex = 3;
    if (g_PlayableCharacter == 0) {
        banks[3]->allocationIndex = 3;
        banks[2]->allocationIndex = 3;
        banks[4]->allocationIndex = 3;
    }
    if ((u32)(g_PlayableCharacter - 1) <= 1U) {
        d_0605BECA = 0xA;
    } else {
        d_0605BECA = 0xD;
    }
    bank = DAT_06064650[5];
    i = 5;
    if (bank != NULL) {
        do {
            if (bank->palettes != NULL) {
                images = bank->images;
                if (images != NULL) {
                    palette = 8;
                    if (bank->flags & 0x4000) {
                        palette = 0;
                    }
                    bank->allocationIndex =
                        func_0600AE30(NULL, images, palette);
                }
            }
            i += 1;
            bank = DAT_06064650[i];
        } while (bank != NULL);
    }
    DAT_06038FD4 = d_0605BECA;
}

void func_0600C0C4(int param_1) {
    if (param_1 == 0) {
        d_0605BECA = 10;
        DAT_060645D4[0]->allocationIndex = 10;
    } else {
        d_0605BECA = 11;
        DAT_06064670[0]->allocationIndex = 11;
    }
}

void func_0600C0FC(void) { DAT_060645D0[0]->allocationIndex = 0xC; }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C114, func_0600C114);

void func_0600C18C(void) {
    d_0605AEA8 = 0x10;
    return;
}

void func_0600C1A0(void) {
    SaturnSpriteResource* entry;
    s32 i;
    s32 j;

    if ((u32)(g_PlayableCharacter - 1) <= 1U) {
        d_0605AEA8 = 0x30;
    } else {
        d_0605AEA8 = 0xA0;
    }
    d_0605AEB0 = 0;

    for (i = 0; i <= 4; i++) {
        entry = DAT_06064650[i];
        if (entry->palettes != NULL) {
            entry->flags = func_0600AEE4(entry->palettes);
        }
    }

    for (j = 5; (entry = DAT_06064650[j]) != NULL; j++) {
        if (entry->palettes != NULL) {
            entry->flags = func_0600AEE4(entry->palettes);
        }
    }

    DAT_06038FD6 = d_0605AEA8;
    DAT_06038FD8 = d_0605AEB0;
}

void func_0600C254(void) {
    u16 prev;
    SaturnSpriteResource* bank;

    prev = d_0605AEA8;
    d_0605AEA8 = 0x90;
    bank = DAT_060645D0[0];
    bank->flags = func_0600AEE4(bank->palettes);
    d_0605AEA8 = prev;
}

void func_0600C298(s32 param_1) {
    u16 prev;
    SaturnSpriteResource* bank;

    prev = d_0605AEA8;
    if (param_1 == 0) {
        d_0605AEA8 = 0x30;
        bank = DAT_060645D4[0];
    } else {
        d_0605AEA8 = 0x60;
        bank = DAT_06064670[0];
    }
    bank->flags = func_0600AEE4(bank->palettes);
    d_0605AEA8 = prev;
}

// _SetLocalPalData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C2EC, func_0600C2EC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C3A8, func_0600C3A8);

// _RequestItemTrans
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C43C, func_0600C43C);

void func_0600C518(s32* charSrc, s32* palSrc, s32 charRows, s32 palRows) {
    s32* dst;
    s32 chunks;
    s32 i;

    chunks = charRows / 3;
    dst = func_0600CB04(0x140, 0);
    i = 0;

    while (i < chunks) {
        DMA_CpuMemCopy2(dst, charSrc, 0xC0U);
        do {
        } while (DMA_CpuResult() == 2);
        i += 1;
        dst += 0x100;
        charSrc += 0x60;
        charRows -= 3;
    }

    if (charRows > 0) {
        DMA_CpuMemCopy2(dst, charSrc, charRows * 0x40);
        do {
        } while (DMA_CpuResult() == 2);
    }

    chunks = palRows / 12;
    dst = func_0600CB04(0x140, 0x6C);
    i = 0;

    while (i < chunks) {
        DMA_CpuMemCopy2(dst, palSrc, 0xC0U);
        do {
        } while (DMA_CpuResult() == 2);
        dst += 0x100;
        palSrc += 0x60;
        palRows -= 0xC;
        i += 1;
    }

    if (palRows > 0) {
        DMA_CpuMemCopy2(dst, palSrc, palRows * 0x10);
        do {
        } while (DMA_CpuResult() == 2);
    }
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C628, func_0600C628);

void func_0600C6AC(s32 arg0, s32 arg1) {
    func_0600C880(0x13B00, arg1, 0x240);
    func_0600C880(0x13E00, arg0, 0x2980);
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C6E4, func_0600C6E4);

// _SetGameoverToFrameBuffer

void func_0600C7E4(s32 arg0, s32 arg1) {
    s32 offset;

    offset = 0x16800;
    offset = func_0600C880(offset, arg1, 0x20);
    func_0600C880(offset, arg0, 0x1400);
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C818, func_0600C818);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C880, func_0600C880);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C99C, func_0600C99C);

// ClearFrameBuffer

// ClearFrameBuffer
void func_0600CAB8(u16 color) {
    u16* ptr;
    s32 y;
    s32 x;

    for (y = 0; y <= 0xEF; y++) {
        ptr = (u16*)func_0600CB04(0, y);
        for (x = 0; x <= 0x13F; x++) {
            *ptr++ = color;
        }
    }
}
s32* func_0600CB04(s32 x, s32 y) {
    u32 base = 0x25C80000;

    return (s32*)(base + (0x200 * y + x) * 2);
}
s32 func_0600CB20(s32 offset) {
    s32 row;
    s32 col;
    s32 base;

    offset = offset >> 1;
    row = offset / 0xC0;
    col = offset - (row * 0xC0) + 0x140;
    base = 0x25C80000;
    return (row * 0x200 + col) * 2 + base;
}

const unsigned short DAT_0600CB68[6] = {
    0x4452, 0x4143, 0x554C, 0x4158, 0x5F00, 0x0009};
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600CB74, Crc32);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600CBCC, func_0600CBCC);

// _ASYS_RESET_DIS
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600CC14, func_0600CC14);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600CC5C, InitBackupRam);

// _ABup_CheckRam
s32 func_0600CD70(void) {
    s32 work[6];
    s32 status;
    s32 result;

    InitBackupRam();
    DAT_0605DD61 = 1;
    SMPC_ISSUE(SMPC_SNDOFF);

    if ((u16)DAT_0605DD90 == 1) {
        status = func_06030690(0, 0, work);
        result = 0;
        if (status == 2) {
            result = status;
        }
    } else {
        result = 1;
    }

    DAT_0605DD61 = 0;
    SMPC_ISSUE(SMPC_SNDON);
    return result;
}

s32 func_0600CE1C(void) {
    s8 work[24];
    s32 status;
    s32 result;

    InitBackupRam();
    DAT_0605DD61 = 1;
    SMPC_ISSUE(SMPC_SNDOFF);

    if (DAT_0605DD94 == 2) {
        status = func_06030690(1, 0, work);
        result = 0;
        if (status == 2) {
            result = status;
        }
    } else {
        result = 1;
    }

    DAT_0605DD61 = 0;
    SMPC_ISSUE(SMPC_SNDON);
    return result;
}

const u16 DAT_0600CEC8[4] = {0x2573, 0x2530, 0x3264, 0x0000};
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600CED0, func_0600CED0);
s32 func_0600D028(s32 arg0, s8 arg1) {
    s32 work[3];
    s32 result;
    s32* value = &DAT_06038FE0;
    const void* format = DAT_0600CEC8;
    s32 (*setup)(void*, const void*, s32, s8) = func_06032F50;

    setup(work, format, *value, arg1);
    DAT_0605DD61 = 1;
    SMPC_ISSUE(SMPC_SNDOFF);
    result = func_06030768(arg0, work, &SYS_state_060485C0);
    DAT_0605DD61 = 0;
    SMPC_ISSUE(SMPC_SNDON);
    return result;
}

void func_0600D0DC(s32 arg0, s32 arg1, s32 arg2) {
    s8 date[5];

    date[0] =
        (((u8)DAT_06057F60.unk6 >> 4) * 1000) +
        ((DAT_06057F60.unk6 & 0x0F) * 100) +
        (((u8)DAT_06057F60.unk5 >> 4) * 10) + (DAT_06057F60.unk5 & 0x0F) + 0x44;
    date[1] = DAT_06057F60.unk4 & 0x0F;
    date[2] = BCD_TO_DEC(DAT_06057F60.unk3);
    date[3] = BCD_TO_DEC(DAT_06057F60.unk2);
    date[4] = BCD_TO_DEC(DAT_06057F60.unk1);

    func_06030968(date, arg1, arg2, date + 4);
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600D1A0, func_0600D1A0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600D264, func_0600D264);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600D370, func_0600D370);
s8 func_0600D47C(s32 arg0, s8 arg1) {
    char work[12];

    func_06032F50(work, DAT_0600CEC8, DAT_06038FE0, arg1);
    return func_06030898(arg0, work, &SYS_state_060485C0);
}

s8 func_0600D4C4(s32 arg0, s8 arg1) {
    s32 work[3];

    func_06032F50(work, DAT_0600CEC8, DAT_06038FE0, arg1);
    return func_060307C4(arg0, work);
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600D508, SaveGameState);

// _ABup_ChechsumSet

void func_0600D6C0(void) {
    ((s32*)&SYS_state_060485C4)[-1] = Crc32(0x1120, &SYS_state_060485C4);
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600D6EC, LoadGameState);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600D8BC, func_0600D8BC);

// original name: MOVIE_PRG_CLEAR
void MoviePRGClear(void) { memset(0x06066000, 0, 0x9A000); }

void func_0600DAB4(void) { InitPrimBuf(); }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600DACC, InitPrimBuf);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600DB38, func_0600DB38);

void func_0600DCA4(s32 arg0) {
    Primitive* prim;

    prim = &g_PrimBuf[arg0];
    if (prim->next != NULL) {
        do {
            prim->drawMode = 0xFFFF;
            prim = prim->next;
            DAT_06061DD4--;
        } while (prim->next != NULL);
    }
    prim->drawMode = 0xFFFF;
    DAT_06061DD4--;
}
s32 func_0600DCF0(Primitive* prim) {
    s32 visible;
    s16* x;
    s32 i;
    u16 maxX;
    u16 maxY;
    s32 lastCorner;
    s16* y;
    s16 py;

    visible = 0;
    x = &prim->x0;
    i = 0;
    maxX = 0x17F;
    maxY = 0x12F;
    lastCorner = 3;
    y = &prim->y0;

    do {
        py = *y;
        y += 2;
        if ((u16)(*x + 0x20) <= maxX) {
            if ((u16)(py + 0x20) <= maxY) {
                visible = 1;
                return visible;
            }
        }
        i++;
        x += 2;
    } while (i <= lastCorner);

    return visible;
}

s32 func_0600DD38(Primitive* prim) {
    s32 visible;
    s16* x;
    s32 i;
    s32 lastCorner;
    u16 maxX;
    u16 maxY;
    s16* y;
    s16 py;

    visible = 0;
    x = &prim->x0;
    i = 0;
    lastCorner = 1;
    maxX = 0x17F;
    maxY = 0x12F;
    y = &prim->y0;

    for (; i <= lastCorner; i++, lastCorner = 1, x += 4) {
        py = *y;
        y += 4;
        if ((u16)(*x + 0x20) <= maxX && (u16)(py + 0x20) <= maxY) {
            visible = lastCorner;
            break;
        }
    }

    return visible;
}

const u16 DAT_0600DD82 = 0x0009;
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600DD84, func_0600DD84);
s32 func_0600DDD4(Primitive* prim) {
    s32 visible;
    s16* x;
    s32 i;
    s32 lastCorner;
    u16 maxX;
    u16 maxY;
    s16* y;
    s16 py;

    visible = 0;
    x = &prim->x0;
    i = 0;
    lastCorner = 1;
    maxX = 0x17F;
    maxY = 0x12F;
    y = &prim->y0;

    for (; i <= lastCorner; i++, lastCorner = 1, x += 2) {
        py = *y;
        y += 2;
        if ((u16)(*x + 0x20) <= maxX && (u16)(py + 0x20) <= maxY) {
            visible = lastCorner;
            break;
        }
    }

    return visible;
}

bool func_0600DE20(void) { return 0; }

bool func_0600DE2C(void) { return 1; }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600DE38, func_0600DE38);
void func_0600DFC0(Primitive* arg0, s16 arg1, s16 arg2) {
    arg0->x0 += arg1;
    arg0->x1 += arg1;
    arg0->x2 += arg1;
    arg0->x3 += arg1;
    arg0->y0 += arg2;
    arg0->y1 += arg2;
    arg0->y2 += arg2;
    arg0->y3 += arg2;
}

void func_0600E01C(Primitive* arg0, s16 arg1, s16 arg2) {
    arg0->x0 += arg1;
    arg0->x2 += arg1;
    arg0->y0 += arg2;
    arg0->y2 += arg2;
}

const s16 DAT_0600E04E = 0x0009;

void func_0600E050(Primitive* arg0, s16 arg1, s16 arg2) {
    arg0->x0 += arg1;
    arg0->y0 += arg2;
}

void func_0600E070(Primitive* arg0, s16 arg1, s16 arg2) {
    arg0->x0 += arg1;
    arg0->x1 += arg1;
    arg0->y0 += arg2;
    arg0->y1 += arg2;
}

void func_0600E0A4(Primitive* arg0, s16 arg1, s16 arg2) {
    arg0->unk4 += arg1;
    arg0->unk8 += arg2;
}

void func_0600E0C4() {}

void func_0600E0D0(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    Primitive* prim;
    s16* drawMode;
    s32 i;
    s16 raw;
    u16 mode;
    void (**dispatch)(Primitive*, s16, s16);

    prim = g_PrimBuf;
    i = 0;
    dispatch = DAT_0603908C;
    drawMode = (s16*)&prim->drawMode;

    do {
        raw = *drawMode;
        drawMode += 0x12;
        mode = raw;
        if (mode != 0xFFFF) {
            if (mode & 2) {
                dispatch[prim->type & 0x0F](prim, arg0, arg1);
            } else if (mode & 0x200) {
                dispatch[prim->type & 0x0F](prim, -arg2, -arg3);
            }
        }
        i++;
        prim++;
    } while (i <= 0x1FF);
}
void func_0600E164(void) {
    SprSpCmd cmd;
    s32 count;

    count = DAT_0605CD5C;
    if (count != 0) {
        if (count > 0) {
            cmd.ax = cmd.dx = *(s16*)&DAT_0605BEC0 - (--count);
            cmd.bx = cmd.cx = *(s16*)&DAT_0605BEC0;
        } else {
            cmd.ax = cmd.dx = 0;
            cmd.bx = cmd.cx = ~count;
        }
        cmd.control = 0x1004;
        cmd.drawMode = 0x00C0;
        cmd.color = 0x67F0;
        cmd.ay = cmd.by = DAT_0605AEA2;
        cmd.cy = cmd.dy = DAT_0605BEC2;
        SPR_2Cmd(0x1FF, &cmd);
        d_0605AEAC += 0x20;
    }
}

const Uint16 DAT_0600E228[12] = {0};

void func_0600E240(Point16* arg0) {
    MTH_InitialMatrix(&DAT_06061DF0, 2, &DAT_060579A8);
    DAT_06061DE8[0] = ((Point16*)&DAT_0600E23C)->x;
    DAT_06061DE8[1] = ((Point16*)&DAT_0600E23C)->y;
    DAT_06057A08.x = -(arg0->x / 2);
    DAT_06057A08.y = -(arg0->y / 2);
    DAT_06057A0C.x = arg0->x + arg0->x / 2;
    DAT_06057A0C.y = arg0->y + arg0->y / 2;
}

// _RotTransCurMatrix_ps
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E2D4, SetCurrentMatrixBinAngle);

void func_0600E390(MthXyz* arg0, MthXyz* arg1) {
    MTH_ClearMatrix(&DAT_06061DF0);
    DAT_06061DF0.current->val[0][3] = arg1->x;
    DAT_06061DF0.current->val[1][3] = arg1->y;
    DAT_06061DF0.current->val[2][3] = arg1->z;
    if (arg0->z != 0) {
        MTH_RotateMatrixZ(&DAT_06061DF0, arg0->z);
    }
    if (arg0->y != 0) {
        MTH_RotateMatrixY(&DAT_06061DF0, arg0->y);
    }
    if (arg0->x != 0) {
        MTH_RotateMatrixX(&DAT_06061DF0, arg0->x);
    }
}

void func_0600E400(MthXyz* src, MthXyz* dst, s32 count) {
    MthXyz unused;

    if (count > 0) {
        do {
            MTH_NormalTrans(DAT_06061DF0.current, src, dst);
            src++;
            count--;
            dst++;
        } while (count > 0);
    }
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E450, TransformAndProjectPoints);

// _CheckClipScreenArea

s32 func_0600E4E0(Point16* arg0) {
    if (arg0->x < DAT_06057A08.x || DAT_06057A0C.x < arg0->x ||
        arg0->y < DAT_06057A08.y || DAT_06057A0C.y < arg0->y) {
        return 0;
    }
    return 1;
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E51C, RotateVec2Degrees);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E5A4, RotateVec2);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E61C, func_0600E61C);

const short ratan_tbl[] = {
    0x000, 0x000, 0x001, 0x001, 0x002, 0x003, 0x003, 0x004, 0x005, 0x005, 0x006,
    0x007, 0x007, 0x008, 0x008, 0x009, 0x00A, 0x00A, 0x00B, 0x00C, 0x00C, 0x00D,
    0x00E, 0x00E, 0x00F, 0x00F, 0x010, 0x011, 0x011, 0x012, 0x013, 0x013, 0x014,
    0x015, 0x015, 0x016, 0x016, 0x017, 0x018, 0x018, 0x019, 0x01A, 0x01A, 0x01B,
    0x01B, 0x01C, 0x01D, 0x01D, 0x01E, 0x01F, 0x01F, 0x020, 0x021, 0x021, 0x022,
    0x022, 0x023, 0x024, 0x024, 0x025, 0x026, 0x026, 0x027, 0x028, 0x028, 0x029,
    0x029, 0x02A, 0x02B, 0x02B, 0x02C, 0x02D, 0x02D, 0x02E, 0x02F, 0x02F, 0x030,
    0x030, 0x031, 0x032, 0x032, 0x033, 0x034, 0x034, 0x035, 0x035, 0x036, 0x037,
    0x037, 0x038, 0x039, 0x039, 0x03A, 0x03B, 0x03B, 0x03C, 0x03C, 0x03D, 0x03E,
    0x03E, 0x03F, 0x040, 0x040, 0x041, 0x041, 0x042, 0x043, 0x043, 0x044, 0x045,
    0x045, 0x046, 0x047, 0x047, 0x048, 0x048, 0x049, 0x04A, 0x04A, 0x04B, 0x04C,
    0x04C, 0x04D, 0x04D, 0x04E, 0x04F, 0x04F, 0x050, 0x051, 0x051, 0x052, 0x052,
    0x053, 0x054, 0x054, 0x055, 0x056, 0x056, 0x057, 0x057, 0x058, 0x059, 0x059,
    0x05A, 0x05B, 0x05B, 0x05C, 0x05C, 0x05D, 0x05E, 0x05E, 0x05F, 0x060, 0x060,
    0x061, 0x061, 0x062, 0x063, 0x063, 0x064, 0x065, 0x065, 0x066, 0x066, 0x067,
    0x068, 0x068, 0x069, 0x06A, 0x06A, 0x06B, 0x06B, 0x06C, 0x06D, 0x06D, 0x06E,
    0x06E, 0x06F, 0x070, 0x070, 0x071, 0x072, 0x072, 0x073, 0x073, 0x074, 0x075,
    0x075, 0x076, 0x076, 0x077, 0x078, 0x078, 0x079, 0x07A, 0x07A, 0x07B, 0x07B,
    0x07C, 0x07D, 0x07D, 0x07E, 0x07E, 0x07F, 0x080, 0x080, 0x081, 0x082, 0x082,
    0x083, 0x083, 0x084, 0x085, 0x085, 0x086, 0x086, 0x087, 0x088, 0x088, 0x089,
    0x089, 0x08A, 0x08B, 0x08B, 0x08C, 0x08C, 0x08D, 0x08E, 0x08E, 0x08F, 0x090,
    0x090, 0x091, 0x091, 0x092, 0x093, 0x093, 0x094, 0x094, 0x095, 0x096, 0x096,
    0x097, 0x097, 0x098, 0x099, 0x099, 0x09A, 0x09A, 0x09B, 0x09C, 0x09C, 0x09D,
    0x09D, 0x09E, 0x09F, 0x09F, 0x0A0, 0x0A0, 0x0A1, 0x0A2, 0x0A2, 0x0A3, 0x0A3,
    0x0A4, 0x0A5, 0x0A5, 0x0A6, 0x0A6, 0x0A7, 0x0A8, 0x0A8, 0x0A9, 0x0A9, 0x0AA,
    0x0AB, 0x0AB, 0x0AC, 0x0AC, 0x0AD, 0x0AE, 0x0AE, 0x0AF, 0x0AF, 0x0B0, 0x0B0,
    0x0B1, 0x0B2, 0x0B2, 0x0B3, 0x0B3, 0x0B4, 0x0B5, 0x0B5, 0x0B6, 0x0B6, 0x0B7,
    0x0B8, 0x0B8, 0x0B9, 0x0B9, 0x0BA, 0x0BA, 0x0BB, 0x0BC, 0x0BC, 0x0BD, 0x0BD,
    0x0BE, 0x0BF, 0x0BF, 0x0C0, 0x0C0, 0x0C1, 0x0C1, 0x0C2, 0x0C3, 0x0C3, 0x0C4,
    0x0C4, 0x0C5, 0x0C6, 0x0C6, 0x0C7, 0x0C7, 0x0C8, 0x0C8, 0x0C9, 0x0CA, 0x0CA,
    0x0CB, 0x0CB, 0x0CC, 0x0CC, 0x0CD, 0x0CE, 0x0CE, 0x0CF, 0x0CF, 0x0D0, 0x0D0,
    0x0D1, 0x0D2, 0x0D2, 0x0D3, 0x0D3, 0x0D4, 0x0D4, 0x0D5, 0x0D6, 0x0D6, 0x0D7,
    0x0D7, 0x0D8, 0x0D8, 0x0D9, 0x0DA, 0x0DA, 0x0DB, 0x0DB, 0x0DC, 0x0DC, 0x0DD,
    0x0DE, 0x0DE, 0x0DF, 0x0DF, 0x0E0, 0x0E0, 0x0E1, 0x0E2, 0x0E2, 0x0E3, 0x0E3,
    0x0E4, 0x0E4, 0x0E5, 0x0E5, 0x0E6, 0x0E7, 0x0E7, 0x0E8, 0x0E8, 0x0E9, 0x0E9,
    0x0EA, 0x0EA, 0x0EB, 0x0EC, 0x0EC, 0x0ED, 0x0ED, 0x0EE, 0x0EE, 0x0EF, 0x0EF,
    0x0F0, 0x0F1, 0x0F1, 0x0F2, 0x0F2, 0x0F3, 0x0F3, 0x0F4, 0x0F4, 0x0F5, 0x0F6,
    0x0F6, 0x0F7, 0x0F7, 0x0F8, 0x0F8, 0x0F9, 0x0F9, 0x0FA, 0x0FB, 0x0FB, 0x0FC,
    0x0FC, 0x0FD, 0x0FD, 0x0FE, 0x0FE, 0x0FF, 0x0FF, 0x100, 0x101, 0x101, 0x102,
    0x102, 0x103, 0x103, 0x104, 0x104, 0x105, 0x105, 0x106, 0x106, 0x107, 0x108,
    0x108, 0x109, 0x109, 0x10A, 0x10A, 0x10B, 0x10B, 0x10C, 0x10C, 0x10D, 0x10D,
    0x10E, 0x10E, 0x10F, 0x110, 0x110, 0x111, 0x111, 0x112, 0x112, 0x113, 0x113,
    0x114, 0x114, 0x115, 0x115, 0x116, 0x116, 0x117, 0x117, 0x118, 0x119, 0x119,
    0x11A, 0x11A, 0x11B, 0x11B, 0x11C, 0x11C, 0x11D, 0x11D, 0x11E, 0x11E, 0x11F,
    0x11F, 0x120, 0x120, 0x121, 0x121, 0x122, 0x122, 0x123, 0x123, 0x124, 0x125,
    0x125, 0x126, 0x126, 0x127, 0x127, 0x128, 0x128, 0x129, 0x129, 0x12A, 0x12A,
    0x12B, 0x12B, 0x12C, 0x12C, 0x12D, 0x12D, 0x12E, 0x12E, 0x12F, 0x12F, 0x130,
    0x130, 0x131, 0x131, 0x132, 0x132, 0x133, 0x133, 0x134, 0x134, 0x135, 0x135,
    0x136, 0x136, 0x137, 0x137, 0x138, 0x138, 0x139, 0x139, 0x13A, 0x13A, 0x13B,
    0x13B, 0x13C, 0x13C, 0x13D, 0x13D, 0x13E, 0x13E, 0x13F, 0x13F, 0x140, 0x140,
    0x141, 0x141, 0x142, 0x142, 0x143, 0x143, 0x144, 0x144, 0x145, 0x145, 0x146,
    0x146, 0x147, 0x147, 0x148, 0x148, 0x149, 0x149, 0x14A, 0x14A, 0x14B, 0x14B,
    0x14C, 0x14C, 0x14D, 0x14D, 0x14E, 0x14E, 0x14E, 0x14F, 0x14F, 0x150, 0x150,
    0x151, 0x151, 0x152, 0x152, 0x153, 0x153, 0x154, 0x154, 0x155, 0x155, 0x156,
    0x156, 0x157, 0x157, 0x158, 0x158, 0x159, 0x159, 0x159, 0x15A, 0x15A, 0x15B,
    0x15B, 0x15C, 0x15C, 0x15D, 0x15D, 0x15E, 0x15E, 0x15F, 0x15F, 0x160, 0x160,
    0x161, 0x161, 0x161, 0x162, 0x162, 0x163, 0x163, 0x164, 0x164, 0x165, 0x165,
    0x166, 0x166, 0x167, 0x167, 0x168, 0x168, 0x168, 0x169, 0x169, 0x16A, 0x16A,
    0x16B, 0x16B, 0x16C, 0x16C, 0x16D, 0x16D, 0x16D, 0x16E, 0x16E, 0x16F, 0x16F,
    0x170, 0x170, 0x171, 0x171, 0x172, 0x172, 0x172, 0x173, 0x173, 0x174, 0x174,
    0x175, 0x175, 0x176, 0x176, 0x177, 0x177, 0x177, 0x178, 0x178, 0x179, 0x179,
    0x17A, 0x17A, 0x17B, 0x17B, 0x17B, 0x17C, 0x17C, 0x17D, 0x17D, 0x17E, 0x17E,
    0x17F, 0x17F, 0x17F, 0x180, 0x180, 0x181, 0x181, 0x182, 0x182, 0x182, 0x183,
    0x183, 0x184, 0x184, 0x185, 0x185, 0x186, 0x186, 0x186, 0x187, 0x187, 0x188,
    0x188, 0x189, 0x189, 0x189, 0x18A, 0x18A, 0x18B, 0x18B, 0x18C, 0x18C, 0x18C,
    0x18D, 0x18D, 0x18E, 0x18E, 0x18F, 0x18F, 0x18F, 0x190, 0x190, 0x191, 0x191,
    0x192, 0x192, 0x192, 0x193, 0x193, 0x194, 0x194, 0x195, 0x195, 0x195, 0x196,
    0x196, 0x197, 0x197, 0x197, 0x198, 0x198, 0x199, 0x199, 0x19A, 0x19A, 0x19A,
    0x19B, 0x19B, 0x19C, 0x19C, 0x19C, 0x19D, 0x19D, 0x19E, 0x19E, 0x19E, 0x19F,
    0x19F, 0x1A0, 0x1A0, 0x1A1, 0x1A1, 0x1A1, 0x1A2, 0x1A2, 0x1A3, 0x1A3, 0x1A3,
    0x1A4, 0x1A4, 0x1A5, 0x1A5, 0x1A5, 0x1A6, 0x1A6, 0x1A7, 0x1A7, 0x1A7, 0x1A8,
    0x1A8, 0x1A9, 0x1A9, 0x1A9, 0x1AA, 0x1AA, 0x1AB, 0x1AB, 0x1AB, 0x1AC, 0x1AC,
    0x1AD, 0x1AD, 0x1AD, 0x1AE, 0x1AE, 0x1AF, 0x1AF, 0x1AF, 0x1B0, 0x1B0, 0x1B1,
    0x1B1, 0x1B1, 0x1B2, 0x1B2, 0x1B3, 0x1B3, 0x1B3, 0x1B4, 0x1B4, 0x1B5, 0x1B5,
    0x1B5, 0x1B6, 0x1B6, 0x1B7, 0x1B7, 0x1B7, 0x1B8, 0x1B8, 0x1B8, 0x1B9, 0x1B9,
    0x1BA, 0x1BA, 0x1BA, 0x1BB, 0x1BB, 0x1BC, 0x1BC, 0x1BC, 0x1BD, 0x1BD, 0x1BD,
    0x1BE, 0x1BE, 0x1BF, 0x1BF, 0x1BF, 0x1C0, 0x1C0, 0x1C0, 0x1C1, 0x1C1, 0x1C2,
    0x1C2, 0x1C2, 0x1C3, 0x1C3, 0x1C4, 0x1C4, 0x1C4, 0x1C5, 0x1C5, 0x1C5, 0x1C6,
    0x1C6, 0x1C7, 0x1C7, 0x1C7, 0x1C8, 0x1C8, 0x1C8, 0x1C9, 0x1C9, 0x1CA, 0x1CA,
    0x1CA, 0x1CB, 0x1CB, 0x1CB, 0x1CC, 0x1CC, 0x1CC, 0x1CD, 0x1CD, 0x1CE, 0x1CE,
    0x1CE, 0x1CF, 0x1CF, 0x1CF, 0x1D0, 0x1D0, 0x1D0, 0x1D1, 0x1D1, 0x1D2, 0x1D2,
    0x1D2, 0x1D3, 0x1D3, 0x1D3, 0x1D4, 0x1D4, 0x1D4, 0x1D5, 0x1D5, 0x1D6, 0x1D6,
    0x1D6, 0x1D7, 0x1D7, 0x1D7, 0x1D8, 0x1D8, 0x1D8, 0x1D9, 0x1D9, 0x1D9, 0x1DA,
    0x1DA, 0x1DB, 0x1DB, 0x1DB, 0x1DC, 0x1DC, 0x1DC, 0x1DD, 0x1DD, 0x1DD, 0x1DE,
    0x1DE, 0x1DE, 0x1DF, 0x1DF, 0x1DF, 0x1E0, 0x1E0, 0x1E1, 0x1E1, 0x1E1, 0x1E2,
    0x1E2, 0x1E2, 0x1E3, 0x1E3, 0x1E3, 0x1E4, 0x1E4, 0x1E4, 0x1E5, 0x1E5, 0x1E5,
    0x1E6, 0x1E6, 0x1E6, 0x1E7, 0x1E7, 0x1E7, 0x1E8, 0x1E8, 0x1E8, 0x1E9, 0x1E9,
    0x1E9, 0x1EA, 0x1EA, 0x1EA, 0x1EB, 0x1EB, 0x1EB, 0x1EC, 0x1EC, 0x1ED, 0x1ED,
    0x1ED, 0x1EE, 0x1EE, 0x1EE, 0x1EF, 0x1EF, 0x1EF, 0x1F0, 0x1F0, 0x1F0, 0x1F1,
    0x1F1, 0x1F1, 0x1F2, 0x1F2, 0x1F2, 0x1F3, 0x1F3, 0x1F3, 0x1F4, 0x1F4, 0x1F4,
    0x1F4, 0x1F5, 0x1F5, 0x1F5, 0x1F6, 0x1F6, 0x1F6, 0x1F7, 0x1F7, 0x1F7, 0x1F8,
    0x1F8, 0x1F8, 0x1F9, 0x1F9, 0x1F9, 0x1FA, 0x1FA, 0x1FA, 0x1FB, 0x1FB, 0x1FB,
    0x1FC, 0x1FC, 0x1FC, 0x1FD, 0x1FD, 0x1FD, 0x1FE, 0x1FE, 0x1FE, 0x1FF, 0x1FF,
    0x1FF, 0x200, 0x200, 0x200, 0x200, 0x201, 0x201, 0x201, 0x202, 0x202, 0x202,
    0x203, 0x203, 0x203, 0x204, 0x204, 0x204,
};

s32 func_0600EE64(s32 arg0) { return MTH_Sqrt(arg0 << 4) >> 4; }

long ratan2(long dx, long dy) {
    long ret;

    while (dx <= -0x200000 || dx >= 0x200000 || dy <= -0x200000 ||
           dy >= 0x200000) {
        dy = dy >> 1;
        dx = dx >> 1;
    }

    if (dy == 0) {
        if (dx == 0) {
            return 0;
        }
        if (dx > 0) {
            return 0x400;
        } else {
            return 0xC00;
        }
    }

    if (dx >= 0) {
        if (dy > 0) {
            if (dy >= dx) {
                ret = 0x000 + ratan_tbl[(dx << 10) / dy];
            } else {
                ret = 0x400 - ratan_tbl[(dy << 10) / dx];
            }
        } else {
            if (-dy >= dx) {
                ret = 0x800 - ratan_tbl[(dx << 10) / -dy];
            } else {
                ret = 0x400 + ratan_tbl[(-dy << 10) / dx];
            }
        }
    } else {
        if (dy < 0) {
            if (-dy >= -dx) {
                ret = 0x800 + ratan_tbl[(-dx << 10) / -dy];
            } else {
                ret = 0xC00 - ratan_tbl[(-dy << 10) / -dx];
            }
        } else {
            if (dy >= -dx) {
                ret = 0x1000 - ratan_tbl[(-dx << 10) / dy];
            } else {
                ret = 0xC00 + ratan_tbl[(dy << 10) / -dx];
            }
        }
    }
    return ret;
}

const s16 rsin_tbl[1024] = {
    0x0000, 0x0006, 0x000C, 0x0012, 0x0019, 0x001F, 0x0025, 0x002B, 0x0032,
    0x0038, 0x003E, 0x0045, 0x004B, 0x0051, 0x0057, 0x005E, 0x0064, 0x006A,
    0x0071, 0x0077, 0x007D, 0x0083, 0x008A, 0x0090, 0x0096, 0x009D, 0x00A3,
    0x00A9, 0x00AF, 0x00B6, 0x00BC, 0x00C2, 0x00C8, 0x00CF, 0x00D5, 0x00DB,
    0x00E2, 0x00E8, 0x00EE, 0x00F4, 0x00FB, 0x0101, 0x0107, 0x010D, 0x0114,
    0x011A, 0x0120, 0x0127, 0x012D, 0x0133, 0x0139, 0x0140, 0x0146, 0x014C,
    0x0152, 0x0159, 0x015F, 0x0165, 0x016B, 0x0172, 0x0178, 0x017E, 0x0184,
    0x018B, 0x0191, 0x0197, 0x019D, 0x01A4, 0x01AA, 0x01B0, 0x01B6, 0x01BD,
    0x01C3, 0x01C9, 0x01CF, 0x01D6, 0x01DC, 0x01E2, 0x01E8, 0x01EF, 0x01F5,
    0x01FB, 0x0201, 0x0208, 0x020E, 0x0214, 0x021A, 0x0221, 0x0227, 0x022D,
    0x0233, 0x0239, 0x0240, 0x0246, 0x024C, 0x0252, 0x0259, 0x025F, 0x0265,
    0x026B, 0x0271, 0x0278, 0x027E, 0x0284, 0x028A, 0x0290, 0x0297, 0x029D,
    0x02A3, 0x02A9, 0x02AF, 0x02B6, 0x02BC, 0x02C2, 0x02C8, 0x02CE, 0x02D5,
    0x02DB, 0x02E1, 0x02E7, 0x02ED, 0x02F3, 0x02FA, 0x0300, 0x0306, 0x030C,
    0x0312, 0x0318, 0x031F, 0x0325, 0x032B, 0x0331, 0x0337, 0x033D, 0x0344,
    0x034A, 0x0350, 0x0356, 0x035C, 0x0362, 0x0368, 0x036F, 0x0375, 0x037B,
    0x0381, 0x0387, 0x038D, 0x0393, 0x0399, 0x03A0, 0x03A6, 0x03AC, 0x03B2,
    0x03B8, 0x03BE, 0x03C4, 0x03CA, 0x03D0, 0x03D7, 0x03DD, 0x03E3, 0x03E9,
    0x03EF, 0x03F5, 0x03FB, 0x0401, 0x0407, 0x040D, 0x0413, 0x041A, 0x0420,
    0x0426, 0x042C, 0x0432, 0x0438, 0x043E, 0x0444, 0x044A, 0x0450, 0x0456,
    0x045C, 0x0462, 0x0468, 0x046E, 0x0474, 0x047A, 0x0480, 0x0486, 0x048C,
    0x0492, 0x0498, 0x049E, 0x04A5, 0x04AB, 0x04B1, 0x04B7, 0x04BD, 0x04C3,
    0x04C9, 0x04CF, 0x04D5, 0x04DB, 0x04E0, 0x04E6, 0x04EC, 0x04F2, 0x04F8,
    0x04FE, 0x0504, 0x050A, 0x0510, 0x0516, 0x051C, 0x0522, 0x0528, 0x052E,
    0x0534, 0x053A, 0x0540, 0x0546, 0x054C, 0x0552, 0x0558, 0x055D, 0x0563,
    0x0569, 0x056F, 0x0575, 0x057B, 0x0581, 0x0587, 0x058D, 0x0593, 0x0599,
    0x059E, 0x05A4, 0x05AA, 0x05B0, 0x05B6, 0x05BC, 0x05C2, 0x05C7, 0x05CD,
    0x05D3, 0x05D9, 0x05DF, 0x05E5, 0x05EB, 0x05F0, 0x05F6, 0x05FC, 0x0602,
    0x0608, 0x060E, 0x0613, 0x0619, 0x061F, 0x0625, 0x062B, 0x0630, 0x0636,
    0x063C, 0x0642, 0x0648, 0x064D, 0x0653, 0x0659, 0x065F, 0x0664, 0x066A,
    0x0670, 0x0676, 0x067B, 0x0681, 0x0687, 0x068D, 0x0692, 0x0698, 0x069E,
    0x06A3, 0x06A9, 0x06AF, 0x06B5, 0x06BA, 0x06C0, 0x06C6, 0x06CB, 0x06D1,
    0x06D7, 0x06DC, 0x06E2, 0x06E8, 0x06ED, 0x06F3, 0x06F9, 0x06FE, 0x0704,
    0x070A, 0x070F, 0x0715, 0x071B, 0x0720, 0x0726, 0x072B, 0x0731, 0x0737,
    0x073C, 0x0742, 0x0748, 0x074D, 0x0753, 0x0758, 0x075E, 0x0763, 0x0769,
    0x076F, 0x0774, 0x077A, 0x077F, 0x0785, 0x078A, 0x0790, 0x0795, 0x079B,
    0x07A0, 0x07A6, 0x07AC, 0x07B1, 0x07B7, 0x07BC, 0x07C2, 0x07C7, 0x07CD,
    0x07D2, 0x07D7, 0x07DD, 0x07E2, 0x07E8, 0x07ED, 0x07F3, 0x07F8, 0x07FE,
    0x0803, 0x0809, 0x080E, 0x0813, 0x0819, 0x081E, 0x0824, 0x0829, 0x082E,
    0x0834, 0x0839, 0x083F, 0x0844, 0x0849, 0x084F, 0x0854, 0x085A, 0x085F,
    0x0864, 0x086A, 0x086F, 0x0874, 0x087A, 0x087F, 0x0884, 0x088A, 0x088F,
    0x0894, 0x0899, 0x089F, 0x08A4, 0x08A9, 0x08AF, 0x08B4, 0x08B9, 0x08BE,
    0x08C4, 0x08C9, 0x08CE, 0x08D3, 0x08D9, 0x08DE, 0x08E3, 0x08E8, 0x08EE,
    0x08F3, 0x08F8, 0x08FD, 0x0902, 0x0908, 0x090D, 0x0912, 0x0917, 0x091C,
    0x0921, 0x0927, 0x092C, 0x0931, 0x0936, 0x093B, 0x0940, 0x0945, 0x094B,
    0x0950, 0x0955, 0x095A, 0x095F, 0x0964, 0x0969, 0x096E, 0x0973, 0x0978,
    0x097D, 0x0982, 0x0987, 0x098D, 0x0992, 0x0997, 0x099C, 0x09A1, 0x09A6,
    0x09AB, 0x09B0, 0x09B5, 0x09BA, 0x09BF, 0x09C4, 0x09C9, 0x09CE, 0x09D3,
    0x09D7, 0x09DC, 0x09E1, 0x09E6, 0x09EB, 0x09F0, 0x09F5, 0x09FA, 0x09FF,
    0x0A04, 0x0A09, 0x0A0E, 0x0A12, 0x0A17, 0x0A1C, 0x0A21, 0x0A26, 0x0A2B,
    0x0A30, 0x0A35, 0x0A39, 0x0A3E, 0x0A43, 0x0A48, 0x0A4D, 0x0A51, 0x0A56,
    0x0A5B, 0x0A60, 0x0A65, 0x0A69, 0x0A6E, 0x0A73, 0x0A78, 0x0A7C, 0x0A81,
    0x0A86, 0x0A8B, 0x0A8F, 0x0A94, 0x0A99, 0x0A9D, 0x0AA2, 0x0AA7, 0x0AAC,
    0x0AB0, 0x0AB5, 0x0ABA, 0x0ABE, 0x0AC3, 0x0AC8, 0x0ACC, 0x0AD1, 0x0AD5,
    0x0ADA, 0x0ADF, 0x0AE3, 0x0AE8, 0x0AEC, 0x0AF1, 0x0AF6, 0x0AFA, 0x0AFF,
    0x0B03, 0x0B08, 0x0B0C, 0x0B11, 0x0B15, 0x0B1A, 0x0B1F, 0x0B23, 0x0B28,
    0x0B2C, 0x0B31, 0x0B35, 0x0B3A, 0x0B3E, 0x0B42, 0x0B47, 0x0B4B, 0x0B50,
    0x0B54, 0x0B59, 0x0B5D, 0x0B62, 0x0B66, 0x0B6A, 0x0B6F, 0x0B73, 0x0B78,
    0x0B7C, 0x0B80, 0x0B85, 0x0B89, 0x0B8D, 0x0B92, 0x0B96, 0x0B9A, 0x0B9F,
    0x0BA3, 0x0BA7, 0x0BAC, 0x0BB0, 0x0BB4, 0x0BB8, 0x0BBD, 0x0BC1, 0x0BC5,
    0x0BCA, 0x0BCE, 0x0BD2, 0x0BD6, 0x0BDA, 0x0BDF, 0x0BE3, 0x0BE7, 0x0BEB,
    0x0BEF, 0x0BF4, 0x0BF8, 0x0BFC, 0x0C00, 0x0C04, 0x0C08, 0x0C0D, 0x0C11,
    0x0C15, 0x0C19, 0x0C1D, 0x0C21, 0x0C25, 0x0C29, 0x0C2D, 0x0C31, 0x0C36,
    0x0C3A, 0x0C3E, 0x0C42, 0x0C46, 0x0C4A, 0x0C4E, 0x0C52, 0x0C56, 0x0C5A,
    0x0C5E, 0x0C62, 0x0C66, 0x0C6A, 0x0C6E, 0x0C72, 0x0C76, 0x0C79, 0x0C7D,
    0x0C81, 0x0C85, 0x0C89, 0x0C8D, 0x0C91, 0x0C95, 0x0C99, 0x0C9D, 0x0CA0,
    0x0CA4, 0x0CA8, 0x0CAC, 0x0CB0, 0x0CB4, 0x0CB7, 0x0CBB, 0x0CBF, 0x0CC3,
    0x0CC7, 0x0CCA, 0x0CCE, 0x0CD2, 0x0CD6, 0x0CD9, 0x0CDD, 0x0CE1, 0x0CE5,
    0x0CE8, 0x0CEC, 0x0CF0, 0x0CF3, 0x0CF7, 0x0CFB, 0x0CFE, 0x0D02, 0x0D06,
    0x0D09, 0x0D0D, 0x0D11, 0x0D14, 0x0D18, 0x0D1C, 0x0D1F, 0x0D23, 0x0D26,
    0x0D2A, 0x0D2D, 0x0D31, 0x0D35, 0x0D38, 0x0D3C, 0x0D3F, 0x0D43, 0x0D46,
    0x0D4A, 0x0D4D, 0x0D51, 0x0D54, 0x0D58, 0x0D5B, 0x0D5F, 0x0D62, 0x0D65,
    0x0D69, 0x0D6C, 0x0D70, 0x0D73, 0x0D77, 0x0D7A, 0x0D7D, 0x0D81, 0x0D84,
    0x0D87, 0x0D8B, 0x0D8E, 0x0D91, 0x0D95, 0x0D98, 0x0D9B, 0x0D9F, 0x0DA2,
    0x0DA5, 0x0DA9, 0x0DAC, 0x0DAF, 0x0DB2, 0x0DB6, 0x0DB9, 0x0DBC, 0x0DBF,
    0x0DC2, 0x0DC6, 0x0DC9, 0x0DCC, 0x0DCF, 0x0DD2, 0x0DD5, 0x0DD9, 0x0DDC,
    0x0DDF, 0x0DE2, 0x0DE5, 0x0DE8, 0x0DEB, 0x0DEE, 0x0DF2, 0x0DF5, 0x0DF8,
    0x0DFB, 0x0DFE, 0x0E01, 0x0E04, 0x0E07, 0x0E0A, 0x0E0D, 0x0E10, 0x0E13,
    0x0E16, 0x0E19, 0x0E1C, 0x0E1F, 0x0E22, 0x0E25, 0x0E28, 0x0E2B, 0x0E2D,
    0x0E30, 0x0E33, 0x0E36, 0x0E39, 0x0E3C, 0x0E3F, 0x0E42, 0x0E44, 0x0E47,
    0x0E4A, 0x0E4D, 0x0E50, 0x0E53, 0x0E55, 0x0E58, 0x0E5B, 0x0E5E, 0x0E60,
    0x0E63, 0x0E66, 0x0E69, 0x0E6B, 0x0E6E, 0x0E71, 0x0E74, 0x0E76, 0x0E79,
    0x0E7C, 0x0E7E, 0x0E81, 0x0E84, 0x0E86, 0x0E89, 0x0E8B, 0x0E8E, 0x0E91,
    0x0E93, 0x0E96, 0x0E98, 0x0E9B, 0x0E9E, 0x0EA0, 0x0EA3, 0x0EA5, 0x0EA8,
    0x0EAA, 0x0EAD, 0x0EAF, 0x0EB2, 0x0EB4, 0x0EB7, 0x0EB9, 0x0EBC, 0x0EBE,
    0x0EC0, 0x0EC3, 0x0EC5, 0x0EC8, 0x0ECA, 0x0ECD, 0x0ECF, 0x0ED1, 0x0ED4,
    0x0ED6, 0x0ED8, 0x0EDB, 0x0EDD, 0x0EDF, 0x0EE2, 0x0EE4, 0x0EE6, 0x0EE8,
    0x0EEB, 0x0EED, 0x0EEF, 0x0EF2, 0x0EF4, 0x0EF6, 0x0EF8, 0x0EFA, 0x0EFD,
    0x0EFF, 0x0F01, 0x0F03, 0x0F05, 0x0F08, 0x0F0A, 0x0F0C, 0x0F0E, 0x0F10,
    0x0F12, 0x0F14, 0x0F16, 0x0F18, 0x0F1B, 0x0F1D, 0x0F1F, 0x0F21, 0x0F23,
    0x0F25, 0x0F27, 0x0F29, 0x0F2B, 0x0F2D, 0x0F2F, 0x0F31, 0x0F33, 0x0F35,
    0x0F37, 0x0F39, 0x0F3B, 0x0F3C, 0x0F3E, 0x0F40, 0x0F42, 0x0F44, 0x0F46,
    0x0F48, 0x0F4A, 0x0F4B, 0x0F4D, 0x0F4F, 0x0F51, 0x0F53, 0x0F55, 0x0F56,
    0x0F58, 0x0F5A, 0x0F5C, 0x0F5D, 0x0F5F, 0x0F61, 0x0F63, 0x0F64, 0x0F66,
    0x0F68, 0x0F69, 0x0F6B, 0x0F6D, 0x0F6E, 0x0F70, 0x0F72, 0x0F73, 0x0F75,
    0x0F77, 0x0F78, 0x0F7A, 0x0F7B, 0x0F7D, 0x0F7F, 0x0F80, 0x0F82, 0x0F83,
    0x0F85, 0x0F86, 0x0F88, 0x0F89, 0x0F8B, 0x0F8C, 0x0F8E, 0x0F8F, 0x0F91,
    0x0F92, 0x0F94, 0x0F95, 0x0F96, 0x0F98, 0x0F99, 0x0F9B, 0x0F9C, 0x0F9D,
    0x0F9F, 0x0FA0, 0x0FA1, 0x0FA3, 0x0FA4, 0x0FA5, 0x0FA7, 0x0FA8, 0x0FA9,
    0x0FAB, 0x0FAC, 0x0FAD, 0x0FAE, 0x0FB0, 0x0FB1, 0x0FB2, 0x0FB3, 0x0FB4,
    0x0FB6, 0x0FB7, 0x0FB8, 0x0FB9, 0x0FBA, 0x0FBB, 0x0FBD, 0x0FBE, 0x0FBF,
    0x0FC0, 0x0FC1, 0x0FC2, 0x0FC3, 0x0FC4, 0x0FC5, 0x0FC6, 0x0FC7, 0x0FC8,
    0x0FC9, 0x0FCA, 0x0FCB, 0x0FCC, 0x0FCD, 0x0FCE, 0x0FCF, 0x0FD0, 0x0FD1,
    0x0FD2, 0x0FD3, 0x0FD4, 0x0FD5, 0x0FD6, 0x0FD7, 0x0FD8, 0x0FD9, 0x0FD9,
    0x0FDA, 0x0FDB, 0x0FDC, 0x0FDD, 0x0FDE, 0x0FDE, 0x0FDF, 0x0FE0, 0x0FE1,
    0x0FE1, 0x0FE2, 0x0FE3, 0x0FE4, 0x0FE4, 0x0FE5, 0x0FE6, 0x0FE7, 0x0FE7,
    0x0FE8, 0x0FE9, 0x0FE9, 0x0FEA, 0x0FEB, 0x0FEB, 0x0FEC, 0x0FEC, 0x0FED,
    0x0FEE, 0x0FEE, 0x0FEF, 0x0FEF, 0x0FF0, 0x0FF0, 0x0FF1, 0x0FF1, 0x0FF2,
    0x0FF2, 0x0FF3, 0x0FF3, 0x0FF4, 0x0FF4, 0x0FF5, 0x0FF5, 0x0FF6, 0x0FF6,
    0x0FF7, 0x0FF7, 0x0FF7, 0x0FF8, 0x0FF8, 0x0FF9, 0x0FF9, 0x0FF9, 0x0FFA,
    0x0FFA, 0x0FFA, 0x0FFB, 0x0FFB, 0x0FFB, 0x0FFB, 0x0FFC, 0x0FFC, 0x0FFC,
    0x0FFC, 0x0FFD, 0x0FFD, 0x0FFD, 0x0FFD, 0x0FFE, 0x0FFE, 0x0FFE, 0x0FFE,
    0x0FFE, 0x0FFE, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF,
    0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF,
};

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600F7BC, rsin);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600F81C, rcos);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600F87C, rsincos);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600F914, SquareRoot0);

#define N 1024 // Size of ring buffer - must be power of 2.
#define N_MIN_1 1023
#define F 34 // Upper limit for match_length.
#define R N - F
// Encode string into position and length, if match_length is greater than this.
#define THRESHOLD 2

extern u8 text_buf[N_MIN_1 + F];

s32 DecompressLZSS(u8* src, u8* dst, u32 srclen) {
    s32 r;
    s32 dstCount;
    s32 srcCount;
    u32 i, j, k, c;
    u32 flags;

    if (srclen == 0) {
        return 0;
    }
    for (i = 0; i < R; i++) {
        text_buf[i] = 0;
    }

    r = R;
    dstCount = 0;
    srcCount = 0;
    flags = 0;

    while (true) {
        if (((flags >>= 1) & 0x100) == 0) {
            c = *src++;
            srcCount++;
            flags = c | 0xFF00;
        }
        if (flags & 1) {
            c = *src++;
            *dst++ = c;

            dstCount++;
            srcCount++;

            if (srcCount == srclen) {
                break;
            }
            text_buf[r++] = c;
            r &= N_MIN_1;
        } else {
            i = *src++;
            j = *src++;
            srcCount += 2;

            i |= ((j & 0xE0) << 3);
            j = (j & 0x1F) + THRESHOLD;

            for (k = 0; k <= j; k++) {
                c = text_buf[(i + k) & N_MIN_1];
                *dst++ = c;
                dstCount++;
                text_buf[r++] = c;
                r &= N_MIN_1;
            }
            if (srcCount == srclen || srcCount == (srclen + 1)) {
                break;
            }
        }
    }

    return dstCount;
}

// _PSX_SHAKE_MAIN
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600FA4C, func_0600FA4C);

void func_0600FACC(void) {
    struct ShakeState* shake = &DAT_06057A10;

    shake->offset = shake->offsets[shake->index];
    shake->index++;
    if (shake->offsets[shake->index] == 0x7FFF) {
        shake->id = 0;
        shake->offset = 0;
    }
}

void func_0600FB0C(s32 arg0) {
    DAT_06057A10.id = arg0;
    DAT_06057A10.index = 0;
    DAT_06057A10.offsets = (s16*)DAT_06039128[arg0];
}

void func_0600FB34(void) {
    DAT_06057A10.id = 0;
    DAT_06057A10.offset = 0;
}

s32 func_0600FB4C(void) {
    if (((DAT_0605d772 & 0xffff) == 0) &&
        ((g_pads[0].pressed & 0x0700) == 0x0700)) {
        if ((g_pads[0].previous & PAD_START) && (DAT_0605C658 != 0)) {
            return 1;
        }
    }
    return 0;
}

// original name: TEST_TEST
void func_0600FB9C(void) { func_0602A778(0x100, 32, 0); }

s32 func_0600FBBC(void) {
    return CdSoundCommandQueueEmpty() != 0
               ? (PlaySfx(0xF0000010), ((s32(*)(void))func_06010400)(),
                  PlaySfx(0xF0000008), 0)
               : 1;
}

// _all_map_check
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600FC04, RevealMapCellAtPlayer);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600FCF8, func_0600FCF8);

void func_0600FE98(s32 arg0) {
    s32 x = g_Tilemap.left + g_PlayerX / 320;

    MarkRoomVisited(x, g_Tilemap.top + g_PlayerY / 240, arg0, &g_Tilemap);
}

void func_800F2120(void) {}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600FF08, SetCanRevealMap);

void func_0600FF64(s16 arg0) {
    s32 i;
    Entity* entity;

    entity = &DAT_060997F8[arg0];
    for (i = arg0; i <= 0xFF; i++, entity++) {
        DestroyEntity(entity);
    }
}
void func_0600FFB8(Entity* self) {
    if (self->unk0 != NULL) {
        DestroySpriteObject(self->unk0);
    }
    if (self->flags & 0x800000) {
        FreePrimitives(self->primIndex);
    }
    memset(self, 0, sizeof(Entity));
}

// func_06010008
void InitDebugPrint(void) {
    SclConfig temp;

    DAT_06062224[1] = 0;
    DAT_06062224[0] = 0;
    ClearDebugPrintTilemap();
    SCL_InitConfigTb(&temp);
    temp.dispenbl = 1;
    temp.charsize = 0;
    temp.pnamesize = 1;
    temp.platesize = 0;
    temp.coltype = 0;
    temp.datatype = 0;
    temp.mapover = 0;
    temp.flip = 0;
    temp.patnamecontrl = 0x66;
    temp.plate_addr[0] = VDP2_DEBUG_TILEMAP_OFFSET;
    temp.plate_addr[1] = VDP2_DEBUG_TILEMAP_OFFSET;
    temp.plate_addr[2] = VDP2_DEBUG_TILEMAP_OFFSET;
    temp.plate_addr[3] = VDP2_DEBUG_TILEMAP_OFFSET;
    SCL_SetConfig(SCL_NBG0, &temp);
    DAT_0605d6c0[3].tileFlags = 0x10;
    DAT_0605d6c0[3].src = &DAT_06039214;
    DAT_0605d6c0[3].dest = VDP2_25F00600;
    DAT_0605d6c0[3].cnt = 0x80;
}

// 0x060100b8
// clears the debug print tilemap area, debug prints are at least used by
// the stage select screen on the title screen
void ClearDebugPrintTilemap(void) {
    u16 i;
    u16* ptr;

    ptr = VDP2_DEBUG_TILEMAP_OFFSET;
    for (i = 0; i < 0x1000; i++) {
        *ptr++ = 0;
    }
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60100DC, func_060100DC);

// debug print function used by title screen stage select
// _DEBUG_FONT_SET2
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6010274, func_06010274);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6010328, func_06010328);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6010400, func_06010400);

// _pause_seq
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60110C0, func_060110C0);

// func_06011264
void SignalSlaveSh2(void) {
    // set input capture flag on sub-sh2
    *((u16*)SH2_REG_M_FRT_IC) = 0xffff;
    return;
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011278, func_06011278);
void func_06011A6C(s32 arg0) {
    s32 i;

    i = 0;
    for (;;) {
        if (DAT_06064250[i] != 0) {
            if (i != 0x1E) {
                i++;
                continue;
            }
        }
        break;
    }
    DAT_06064250[i] = arg0;
    DAT_06064250[i + 1] = 0;
}

s32 PlaySfxVolPan(s32 sfxId, s32 sfxVol, s16 sfxPan) {
    s32 ret = 0;

    if (sfxId < 0x600 || sfxId > 0x916) {
        return -3;
    }
    if (sfxPan < -8 || sfxPan > 8) {
        sfxPan = 0x40;
        ret = -1;
    } else {
        if (sfxPan == 0) {
            sfxPan = sfxPan * 8 + 0x40;
        } else if (sfxPan > 0) {
            sfxPan = sfxPan * 8 + 0x3F;
        } else {
            sfxPan = sfxPan * 8 + 0x40;
        }
    }
    DAT_06064230 = sfxVol;
    DAT_060643c4 = sfxPan;
    DAT_060644c4 = 1;
    PlaySfx(sfxId);
    DAT_060644c4 = 0;
    return ret;
}

s32 func_06011B28(s32 arg0) {
    if (arg0 < 0) {
        arg0 = 0;
    } else if (arg0 <= 0x0F) {
        arg0 *= 2;
    } else if (arg0 <= 0x1F) {
        arg0 = ((arg0 - 0x10) * 0x26) / 0x10 + 0x20;
    } else if (arg0 <= 0x2F) {
        arg0 = ((arg0 - 0x20) * 0x1A) / 0x10 + 0x46;
    } else if (arg0 <= 0x3F) {
        arg0 = ((arg0 - 0x30) * 0x0D) / 0x10 + 0x60;
    } else if (arg0 <= 0x4F) {
        arg0 = (arg0 - 0x40) / 2 + 0x6D;
    } else if (arg0 <= 0x5F) {
        arg0 = ((arg0 - 0x50) * 5) / 0x10 + 0x75;
    } else if (arg0 <= 0x6F) {
        arg0 = (arg0 - 0x60) / 4 + 0x7A;
    } else if (arg0 <= 0x81) {
        arg0 = ((arg0 - 0x70) * 4) / 18 + 0x7E;
    }
    if (arg0 == 0) {
        arg0 = 1;
    }
    return arg0;
}

s32 func_06011C28(s32 volume, s16 pan) {
    s32 result;

    result = 0;
    if (DAT_060643E0.unk1C == 0) {
        return -2;
    }
    if ((u16)(pan + 8) > 0x10U) {
        pan = 0x40;
        result = -1;
    } else if (pan == 0) {
        pan = 0x40;
    } else {
        if (pan > 0) {
            pan = pan * 8 + 0x3F;
        } else {
            pan = pan * 8 + 0x40;
        }
    }
    volume = func_06011B28((DAT_060644B0 * volume) / 127);
    if (volume == 0) {
        volume = 1;
    }
    func_06018B8C(7, volume, 0);
    func_06018C00(7, 0, pan);
    DAT_0606436E = pan;
    return result;
}

const u16 DAT_06011CE0 = 0x5344;
const u16 DAT_06011CE2 = 0x0000;
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011CE4, func_06011CE4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011EE0, func_06011EE0);

// func_06011F40
void StopPcm(s32 param) { SND_StopPcm2(); }

void func_06011F58(void) {
    s32 bgm;

    func_06011F40(7);
    DAT_060641F4 = 0;
    DAT_06063EB4 = 0;
    DAT_06062258 = 0;
    bgm = DAT_06062290[DAT_06062268];
    if (bgm != 0) {
        func_0601BDD0(bgm);
        DAT_06063C1C = 0;
    }
    D_8013B61C = 0;
    DAT_06063BD4 = 0;
}

// _KeyOffBGM2
void func_06011FC8(void) {
    s32 bgm;

    func_06011F40(7);
    DAT_060641F4 = 0;
    DAT_06063EB4 = 0;
    bgm = DAT_06062290[DAT_06062268];
    if (bgm != 0) {
        func_0601BDD0(bgm);
        DAT_06063C1C = 0;
    }
    D_8013B61C = 0;
    DAT_06063BD4 = 0;
}
