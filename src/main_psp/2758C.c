// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>
#include <psxsdk/libgpu.h>

extern char D_psp_08946688;
extern char D_psp_089466A0[];
extern s32 D_psp_08C63B24;
extern u8 g_BmpCastleMap[0x8000];
extern u16 g_Clut[3][0x1000];

void func_psp_089262C4(void);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", FntPrint);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_08925F7C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_089260AC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_089260D0);

int CdInit(void) { return 0; }

int CdMix(void* vol) { return 0; }

long CdDataCallback(void (*func)()) {
    if (func != NULL) {
        func();
    }
    return 0;
}

long CdReadyCallback(void (*func)()) { return NULL; }

void ChangeClearPAD(long) {}

void InitCARD(long val) { func_psp_08919140(); }

long StartCARD(void) { return 0; }

void _bu_init(void) {}

void SsSetStereo(void) {}

void SsSetMono(void) {}

void SsSetMVol(short voll, short volr) {}

void SsSetSerialAttr(char s_num, char attr, char mode) {}

void SsUtSetReverbDepth(short ldepth, short rdepth) {}

void SsSeqPlay(short seq_access_num, char play_mode, short l_count) {}

s16 SsSeqOpen(u32 addr, s16 vab_id) { return 0; }

void SsSeqClose(short seq_access_num) {}

void SsSeqStop(short seq_access_num) {}

void SsSeqSetVol(short arg0, short arg1, short arg2) {}

void FntLoad(s32 tx, s32 ty) {}

s32 FntOpen(s32 x, s32 y, s32 w, s32 h, s32 isbg, s32 n) { return 0; }

void SetDumpFnt(int id) {}

int SetGraphDebug(int level) { return 0; }

void PadInit(int mode) {}

u_long PadRead(int id) { return 0; }

void GsInitVcount(void) { func_psp_089262C4(); }

void func_psp_089262C4(void) { D_psp_08C63B24 = func_psp_0891B528(); }

long GsGetVcount(void) {
    return ((func_psp_0891B528() - D_psp_08C63B24) + 1) << 8;
}

int CdControl(u_char com, u_char* param, u_char* result) { return 2; }

int CdSync(int mode, u_char* result) { return 2; }

void func_psp_08926348(void) {
    u8* temp_v0;

    temp_v0 = (u8*)func_psp_08919C8C(0);
    if (func_psp_08919E6C(0, temp_v0) > 0) {
        func_psp_08910D28();
        func_psp_0890FC2C();
        func_psp_0890FF84();
        func_psp_08910298(1);
        func_psp_089117F4(
            1, 0, 0, 0x100, 0x110, 0xF0, (u8*)func_psp_08919E1C(temp_v0), 0, 0,
            0x100, (u8*)sceGeEdramGetAddr() + 0x1BC000);
        func_psp_089117F4(
            3, 0, 0, 0x100, 1, 0x100, (u8*)func_psp_08919DF4(temp_v0), 0, 0,
            0x100, (u8*)sceGeEdramGetAddr() + 0x1DE000);
        func_psp_0890FF2C();
        sceKernelDcacheWritebackAll();
        func_psp_0890FE98();
        DrawSync(0);
    }
}

void func_psp_08926498(void) {
    sceKernelPowerTick(0);
    FntPrint(&D_psp_08946688);
}

void func_psp_089264CC(s32 arg0, u_long* arg1, s32 arg2) {
    RECT rect;
    u16* var_s0;

    var_s0 = (u16*)g_Clut;
    arg0 &= 0x3FF;
    if ((arg0 >= 0) && (arg0 < 0x100)) {
        rect.x = 0x200;
    } else if ((arg0 >= 0x100) && (arg0 < 0x200)) {
        rect.x = 0;
        var_s0 += 0x1000;
    } else if ((arg0 >= 0x200) && (arg0 < 0x300)) {
        rect.x = 0x100;
        var_s0 += 0x2000;
    } else {
        return;
    }
    if (arg2 != 0) {
        u8* p = (u8*)arg1;
        p[0] = 0;
        p[1] = 0;
    }
    rect.x += (arg0 & 0xF) * 0x10;
    rect.y = ((arg0 / 0x10) & 0xF) + 0xF0;
    rect.w = 0x100;
    rect.h = 1;
    LoadImage(&rect, arg1);
    var_s0 += (((arg0 / 0x10) & 0xF) << 8) + ((arg0 & 0xF) * 0x10);
    memcpy(var_s0, arg1, 0x200);
}

void func_psp_0892667C(s32 arg0, u_long* arg1) {
    RECT rect;
    u16* var_s0;

    var_s0 = (u16*)g_Clut;
    arg0 &= 0x3FF;
    if ((arg0 >= 0) && (arg0 < 0x100)) {
        rect.x = 0x200;
    } else if ((arg0 >= 0x100) && (arg0 < 0x200)) {
        rect.x = 0;
        var_s0 += 0x1000;
    } else if ((arg0 >= 0x200) && (arg0 < 0x300)) {
        rect.x = 0x100;
        var_s0 += 0x2000;
    } else {
        return;
    }
    rect.x += (arg0 & 0xF) * 0x10;
    rect.y = ((arg0 / 0x10) & 0xF) + 0xF0;
    rect.w = 0x10;
    rect.h = 1;
    LoadImage(&rect, arg1);
    var_s0 += (((arg0 / 0x10) & 0xF) << 8) + ((arg0 & 0xF) * 0x10);
    memcpy(var_s0, arg1, 0x20);
}

void func_psp_08926808(s32 arg0, u_long* arg1) {
    RECT rect;
    u16* var_s0;

    var_s0 = (u16*)g_Clut;
    arg0 &= 0x3FF;
    if ((arg0 >= 0) && (arg0 < 0x100)) {
        rect.x = 0x200;
    } else if ((arg0 >= 0x100) && (arg0 < 0x200)) {
        rect.x = 0;
        var_s0 += 0x1000;
    } else if ((arg0 >= 0x200) && (arg0 < 0x300)) {
        rect.x = 0x100;
        var_s0 += 0x2000;
    } else {
        return;
    }
    rect.x += (arg0 & 0xF) * 0x10;
    rect.y = ((arg0 / 0x10) & 0xF) + 0xF0;
    rect.w = 0x10;
    rect.h = 1;
    func_psp_0891C1C0(&rect, arg1);
    var_s0 += (((arg0 / 0x10) & 0xF) << 8) + ((arg0 & 0xF) * 0x10);
    memcpy(var_s0, arg1, 0x20);
}

void GameEntrypoint(void) {
    func_psp_08926348();
    func_psp_0892A1EC(0);
    while (func_psp_0890FB70(D_psp_089466A0, g_BmpCastleMap, 0, 0x8000) == 0) {
        sceKernelDelayThreadCB(1000000);
    }
    MainGame();
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_08926A08);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", Krom2RawAdd);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", ApplyRotMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", ScaleMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", CompMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", DpqColor);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", NormalColorDpq);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", NormalClip);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", RotTrans);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", RotTransPers);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", RotTransPers3);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", RotTransPers4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", RotAverage3);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", RotAverage4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", RotAverageNclip3);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", RotAverageNclip4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_08927C5C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", SquareRoot0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", SquareRoot12);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", ratan2);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", VectorNormalS);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", rcos);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", rsin);

void gte_stub(void) {}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", InitGeom);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", SetGeomScreen);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", SetGeomOffset);

void SetFarColor(void) {}

void SetFogNear(void) {}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_089280CC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892827C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_08928428);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_08928498);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892851C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_089285A0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", RotMatrixX);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", RotMatrixY);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", RotMatrixZ);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", RotMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", RotMatrixYXZ);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", SetRotMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", TransMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", SetTransMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_SetTransVector);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_ldv0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_ldv1);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_ldv2);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_ldv3c);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_ldtx);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_ldty);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_ldtz);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_ldtr);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_08928980);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_rtps);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_rtpt);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_stsxy);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_stsxy3_gt3);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_stsxy3);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_stszotz);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_stotz);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_stopz);

void gte_dpcs(void) {}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_strgb);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_ldrgb);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_nclip);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_avsz3);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_089295E4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_avsz4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_ldv01c);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", gte_stsxy01c);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", SetColorMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", SetLightMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", SetBackColor);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_08929838);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_08929860);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", NormalColorCol);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_08929FA8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892A018);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892A0C4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892A0F0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892A1EC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892A21C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892A28C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892A2D8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892A3D4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892A414);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892A620);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892A70C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892A76C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892A7E0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892A8C0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892A8FC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892A97C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892A998);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", SsSetSerialVol);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892A9E0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", strFileOpen);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", strFileClose);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", strFileRead);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", strFileLseek);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", play_bgm);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", init_atrac3plus);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", play_atrac3plus);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", createPlayModeFlag);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", setPlayMode);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", checkPlayMode);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", waitPlayMode);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", clearPlayMode);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", release_arg);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", at3plus_addData);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", reset_position);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", fadeoutOperation);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", DvdUmdIoInit);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", DvdUmdIoTerm);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", DvdUmdRetryOpenCB);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", DvdUmdRetryRead);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892BF14);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892BF48);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892BFD0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892BFD8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892C168);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892C174);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892C188);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892C214);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892C3D4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892C4F8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892C524);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892C540);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892C62C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892C660);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892C860);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892CA28);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892CA90);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892CAD8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892CB10);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892CB1C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892CB30);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892CB40);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892CC48);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892CD48);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892CDE0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892CEB0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892CF0C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892CF34);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892CF7C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892CF88);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892CF90);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892D030);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892D130);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892D154);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892D1B0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892D1D8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892D220);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892D2E8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892D3B8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892D4A8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892D518);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892D520);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892D598);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892D5F0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892D674);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892D818);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892D844);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892D96C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892DADC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892DB90);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892DBE4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892DC40);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892DCD8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892DD54);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892DDB0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892DF08);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892DF70);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892DFCC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892E498);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892E6A4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892E718);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892E798);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892E818);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892E8B8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892E914);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892E978);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892E994);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892E9B0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892E9E4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", GsClearVcount);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892EA24);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892EAFC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892EB04);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892EBE8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892EC7C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", SpuGetAllKeysStatus);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", SsUtKeyOnV);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", SsUtSetVVol);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", SpuSetKey);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", SpuSetVoiceAttr);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_0892F83C);
