// SPDX-License-Identifier: AGPL-3.0-only
#include "sattypes.h"
#include "inc_asm.h"
#include "xpt.h"
#include "scl.h"
#include "def.h"
#include "spr.h"

// SEGA_SCL.A

extern Uint32 SclCurSclNum;
extern SclRotreg* SclRotregBuff;
extern SclSysreg Scl_s_reg;
extern SclRotscl Scl_r_reg;

extern Uint16 SclDisplayX;
extern Uint16 SclDisplayY;

extern Uint32 SclRbgKtbAddr[];
extern Sint32 SclRbgKtbOffset[];

extern Uint8 SclRa, SclRb;

extern Uint16 SclK_TableBuff[2][820];
extern Uint32 SclK_TableNum[2];
extern Uint16 SclK_TableFlag[2];

extern Uint32 SclRbgKtbAddr[2];
extern Sint32 SclRbgKtbOffset[2];
extern Uint16 SclRotXySw[2];
extern Uint8 SclRa, SclRb;
extern Uint32 SclRotateTableAddress;
extern Fixed32 SclRotateXy[2];
extern Fixed32 SclRotateZ[2];
extern Fixed32 SclRotateDisp[2];
extern Fixed32 SclRotateMoveZ[2];

extern Uint16 SclRPMD;

extern Uint16 SclRotateTableMode;

extern Uint32 SclColRamAlloc256[];
extern Uint32 SclColRamAlloc2048[];

extern Uint16* regaddr;

extern Uint32 SclAddrLsTbl[];
extern Uint32 SclAddrCsTbl[];
extern Uint16 SclLengthLsTbl;
extern Uint16 SclLengthCsTbl;

// func_06024444
void SCL_Open(Uint32 sclnum) {
    if (SclProcess == 1)
        SclProcess = 0;
    SclCurSclNum = sclnum;
}

void SCL_Close(void) {
    if (SclProcess == 0)
        SclProcess = 1;
}

// func_06024494
void SCL_MoveTo(Fixed32 x, Fixed32 y, Fixed32 z) {
    switch (SclCurSclNum) {
    case SCL_NBG0:
        Scl_n_reg.n0_move_x = x;
        Scl_n_reg.n0_move_y = y;
        break;
    case SCL_NBG1:
        Scl_n_reg.n1_move_x = x;
        Scl_n_reg.n1_move_y = y;
        break;
    case SCL_NBG2:
        Scl_n_reg.n2_move_x = x >> 16;
        Scl_n_reg.n2_move_y = y >> 16;
        break;
    case SCL_NBG3:
        Scl_n_reg.n3_move_x = x >> 16;
        Scl_n_reg.n3_move_y = y >> 16;
        break;
    case SCL_RBG_TB_A:
        SclRotregBuff[0].move.x = x;
        SclRotregBuff[0].move.y = y;
        if (SclRbgKtbAddr[0] && !(SclRbgKtbOffset[0] && SclRotateDisp[0]))
            SclRotateMoveZ[0] = z;
        else
            SclRotateMoveZ[0] = 0;
        if (SclRotateMoveZ[0])
            SCL_Rotate(0, 0, 0);
        break;
    case SCL_RBG_TB_B:
        SclRotregBuff[1].move.x = x;
        SclRotregBuff[1].move.y = y;
        if (SclRbgKtbAddr[1] && !(SclRbgKtbOffset[1] && SclRotateDisp[1]))
            SclRotateMoveZ[1] = z;
        else
            SclRotateMoveZ[1] = 0;
        if (SclRotateMoveZ[1])
            SCL_Rotate(0, 0, 0);
        break;
    }
}

// func_0602465C
void SCL_Scale(Fixed32 Sx, Fixed32 Sy) {
    Fixed32 wSx, wSy;

    wSx = Sx;
    wSy = Sy;
    switch (SclCurSclNum) {
    case SCL_NBG0:
    case SCL_NBG1:
        if (wSx > FIXED(255))
            wSx = FIXED(255);
        else if (wSx < FIXED(0.25))
            wSx = FIXED(0.25);
        else if (wSx == FIXED(0))
            wSx = FIXED(1);
        if (wSy > FIXED(255))
            wSy = FIXED(255);
        else if (wSy < FIXED(0.25))
            wSy = FIXED(0.25);
        else if (wSy == FIXED(0))
            wSy = FIXED(1);
        wSx = DIV_FIXED(FIXED(1), wSx);
        wSy = DIV_FIXED(FIXED(1), wSy);
        break;
    case SCL_RBG_TB_A:
    case SCL_RBG_TB_B:
        wSx = DIV_FIXED(FIXED(1), wSx);
        wSy = DIV_FIXED(FIXED(1), wSy);
        break;
    }

    switch (SclCurSclNum) {
    case SCL_NBG0:
        Scl_n_reg.n0_delta_x = wSx;
        Scl_n_reg.n0_delta_y = wSy;
        break;
    case SCL_NBG1:
        Scl_n_reg.n1_delta_x = wSx;
        Scl_n_reg.n1_delta_y = wSy;
        break;
    case SCL_RBG_TB_A:
        SclRotregBuff[0].zoom.x = wSx;
        SclRotregBuff[0].zoom.y = wSy;
        if (Scl_r_reg.k_contrl & 0x00ff)
            SCL_Rotate(0, 0, 0);
        break;
    case SCL_RBG_TB_B:
        SclRotregBuff[1].zoom.x = wSx;
        SclRotregBuff[1].zoom.y = wSy;
        if (Scl_r_reg.k_contrl & 0xff00)
            SCL_Rotate(0, 0, 0);
        break;
    }
}

// dma is off
// func_06024848
void SCL_CopyReg() {
    Uint16 i;
    if (SclK_TableFlag[0] && SclRbgKtbAddr[0]) {
        SCL_Memcpyw(
            (void*)SclRbgKtbAddr[0], SclK_TableBuff[0], SclK_TableNum[0] * 2);
        SclK_TableFlag[0] = 0;
    }
    if (SclK_TableFlag[1] && SclRbgKtbAddr[1]) {
        SCL_Memcpyw(
            (void*)SclRbgKtbAddr[1], SclK_TableBuff[1], SclK_TableNum[1] * 2);
        SclK_TableFlag[1] = 0;
    }
    {
        const Uint32 size = 0x60;
        const Uint32 p = (Uint32)SclRotateTableAddress;
        void* const pA = (void*)p;
        void* const pB = (void*)(p + 0x80);
        if (pA != NULL) {
            SCL_Memcpyw(pA, &SclRotregBuff[0], size);
            SCL_Memcpyw(pB, &SclRotregBuff[1], size);
        }
    }

    i = 0;
    regaddr[0] = Scl_s_reg.tvmode;
    regaddr[1] = Scl_s_reg.extenbl;
    regaddr[3] = Scl_s_reg.vramsize;
    SCL_Memcpyw(&regaddr[7], &Scl_s_reg.ramcontrl, 13 * 2);

    i += sizeof(SclSysreg) / 2;
    SCL_Memcpyw(&regaddr[i], &Scl_d_reg, sizeof(SclDataset));
    i += sizeof(SclDataset) / 2;
    SCL_Memcpyw(&regaddr[i], &Scl_n_reg, sizeof(SclNorscl));
    i += sizeof(SclNorscl) / 2;
    SCL_Memcpyw(&regaddr[i], &Scl_r_reg, sizeof(SclRotscl));
    i += sizeof(SclRotscl) / 2;
    SCL_Memcpyw(&regaddr[i], &Scl_w_reg, sizeof(SclWinscl));
    i += sizeof(SclWinscl) / 2;
}

// func_06024A48
void SCL_ScrollShow(void) {

    switch (SclProcess) {
    case 1:
        SCL_CopyReg();
        SclProcess = 0;
        break;
    case 2:
        SCL_Memcpyw(
            (void*)SclAddrLsTbl[0], (void*)SclAddrLsTbl[1], SclLengthLsTbl * 4);
        SCL_Memcpyw(
            (void*)SclAddrCsTbl[0], (void*)SclAddrCsTbl[1], SclLengthCsTbl * 4);
        SCL_CopyReg();
        SclProcess = 0;
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    }

    SCL_PriIntProc();
}

// func_06024B20
void SCL_Memcpyw(void* dest, void* src, Uint32 tcnt) {

    if ((dest != NULL) && (src != NULL)) {

        Uint32 tcr, tsize;
        tsize = tcnt;
        tsize = tsize / 2;

        for (tcr = 0; tcr < tsize; tcr++) {
            *((Uint16*)dest) = *((Uint16*)src);
            dest = (Uint8*)dest + 2;
            src = (Uint8*)src + 2;
        }
    }
}

// func_06024B84
void SCL_SetColRamMode(Uint32 ComRamMode) {
    switch (ComRamMode) {
    case SCL_CRM15_1024:
        Scl_s_reg.ramcontrl = (Scl_s_reg.ramcontrl & 0x0FFF) | 0x0000;
        break;
    case SCL_CRM15_2048:
        Scl_s_reg.ramcontrl = (Scl_s_reg.ramcontrl & 0x0FFF) | 0x1000;
        break;
    case SCL_CRM24_1024:
        Scl_s_reg.ramcontrl = (Scl_s_reg.ramcontrl & 0x0FFF) | 0x2000;
        break;
    }
    if (SclProcess == 0)
        SclProcess = 1;
}

// func_06024C20
void SCL_PriIntProc(void) {
    SCL_AutoExec();

    if (SclPriBuffDirty.SclOtherPri) {
        SCL_Memcpyw(SclRealOtherPri, &SclOtherPri, sizeof(SclOtherPri));
        SclPriBuffDirty.SclOtherPri = 0;
    }
    if (SclPriBuffDirty.SclSpPriNum) {
        SCL_Memcpyw(SclRealSpPriNum, &SclSpPriNum, sizeof(SclSpPriNum));
        SclPriBuffDirty.SclSpPriNum = 0;
    }
    if (SclPriBuffDirty.SclBgPriNum) {
        SCL_Memcpyw(SclRealBgPriNum, &SclBgPriNum, sizeof(SclBgPriNum));
        SclPriBuffDirty.SclBgPriNum = 0;
    }
    if (SclPriBuffDirty.SclSpColMix) {
        SCL_Memcpyw(SclRealSpColMix, &SclSpColMix, sizeof(SclSpColMix));
        SclPriBuffDirty.SclSpColMix = 0;
    }
    if (SclPriBuffDirty.SclBgColMix) {
        SCL_Memcpyw(SclRealBgColMix, &SclBgColMix, sizeof(SclBgColMix));
        SclPriBuffDirty.SclBgColMix = 0;
    }
    if (SclPriBuffDirty.SclColOffset) {
        SCL_Memcpyw(SclRealColOffset, &SclColOffset, sizeof(SclColOffset));
        SclPriBuffDirty.SclColOffset = 0;
    }

    return;
}

// func_06024DB4
void SCL_SetFrameInterval(Uint16 count) {
    if (count == 0xffff) {
        SpFrameChgMode = NO_INTER_FRAME_CHG;
        SpFrameEraseMode = 0;
        SPR_WRITE_REG(SPR_W_FBCR, SPR_FBCR_MANUAL | SpFbcrMode);
        VBInterval = count;
    } else if (count == 0xfffe) {
        SpFrameChgMode = NO_INTER_VBE_FRAME_CHG;
        SpFrameEraseMode = 0;
        SPR_WRITE_REG(SPR_W_FBCR, SPR_FBCR_MANUAL | SpFbcrMode);
        VBInterval = count;
    } else {
        if (count & 0x8000)
            SpFrameEraseMode = 0;
        else
            SpFrameEraseMode = 1;
        count &= 0x7fff;
        if (count)
            if (count == 1)
                SpFrameChgMode = AUTO_FRAME_CHG;
            else
                SpFrameChgMode = MANUAL_FRAME_CHG;
        else
            SpFrameChgMode = AUTO_FRAME_CHG;
        VBInterval = count;
        if (SpFrameChgMode == AUTO_FRAME_CHG)
            SPR_WRITE_REG(SPR_W_FBCR, SPR_FBCR_AUTO | SpFbcrMode);
        else
            SPR_WRITE_REG(SPR_W_FBCR, SPR_FBCR_MANUAL | SpFbcrMode);
    }
}
extern Sint32 ReqDisplayFlag2;
extern Sint32 VBIntrDisableDepth;
extern Sint32 frameChgFlag;

// func_06024EC0
void SCL_DisplayFrame(void) {

    if (VBInterval) {
        ReqDisplayFlag = 1;
        while (ReqDisplayFlag)
            ;
        while (ReqDisplayFlag2)
            ;
    }
}

// func_06024F08
void SCL_VblInit(void) {

    SpFrameChgMode = AUTO_FRAME_CHG;
    SpFrameEraseMode = 1;
    VBInterval = 0;
    VBIntervalCounter = 0;
    ReqDisplayFlag = 0;
    ReqDisplayFlag2 = 0;
    VBIntrDisableDepth = 0;
    frameChgFlag = 0;
}

extern Uint16 SpTvMode;

// func_06024F64
void SCL_VblankStart(void) {
    if (SpFrameChgMode == NO_INTER_FRAME_CHG) {
        if (ReqDisplayFlag) {
            SCL_ScrollShow();
            frameChgFlag = 2;
        }
    } else if (SpFrameChgMode == NO_INTER_VBE_FRAME_CHG) {
        if (ReqDisplayFlag) {
            SPR_WRITE_REG(SPR_W_TVMR, SpTvMode | 0x0008);
            SPR_WRITE_REG(SPR_W_FBCR, SPR_FBCR_MANUAL | SpFbcrMode);
            SCL_ScrollShow();
            frameChgFlag = 3;
        }
    } else if (SpFrameChgMode == AUTO_FRAME_CHG) {
        SCL_ScrollShow();
        frameChgFlag = 4;
    } else {
        VBIntervalCounter++;
        if (SpFrameEraseMode == ON) {
            if ((VBInterval - 1) <= VBIntervalCounter) {
                SPR_WRITE_REG(SPR_W_FBCR, SPR_FBCR_ERASE | SpFbcrMode);
            }
        }
        if (VBInterval <= VBIntervalCounter) {
            if (ReqDisplayFlag) {
                SCL_ScrollShow();
                frameChgFlag = 1;
            }
            VBIntervalCounter = 0;
        }
    }
}
extern Sint32 SpInitialFlag;

void SCL_VblankEnd(void) {
    Uint16 tvStat;

    if (SpDie) {
        tvStat = SPR_SCLREAD_REG(SPR_R_TVSTAT);
        if (tvStat & 2)
            SPR_WRITE_REG(SPR_W_FBCR, 0x000c | SpFbcrMode);
        else
            SPR_WRITE_REG(SPR_W_FBCR, 0x0008 | SpFbcrMode);

        frameChgFlag = 0;
        ReqDisplayFlag = 0;
    } else if (frameChgFlag) {

        if ((frameChgFlag == 2) && (SpInitialFlag != 0) &&
            ((SPR_READ_REG(SPR_R_EDSR) & 0x0002) == 0))
            ReqDisplayFlag2 = 1;
        else {
            if (frameChgFlag == 3)
                SPR_WRITE_REG(SPR_W_TVMR, SpTvMode);
            else if ((frameChgFlag == 1) || (frameChgFlag == 2))
                SPR_WRITE_REG(SPR_W_FBCR, SPR_FBCR_MANUAL | SpFbcrMode);
            frameChgFlag = 0;
            ReqDisplayFlag2 = 0;
        }
        ReqDisplayFlag = 0;
    }
}

extern Uint8 SclAutoVeFlag;

// func_06025174
void SCL_PriorityInit(void) {
    Uint8 i;

    SCL_InitSclOtherPri();
    SCL_InitSclSpPriNum();
    SCL_InitSclBgPriNum();
    SCL_InitSclSpColMix();
    SCL_InitSclBgColMix();
    SCL_InitSclColOffset();

    for (i = 0; i < 8; i++) {
        SclColRamAlloc256[i] = 0;
    }
    SclColRamAlloc2048[0] = 0;
    SclAutoVeFlag = 0;
}
// func_06025214
Uint32 SCL_GetColRamMode(void) {
    return (Uint32)((Scl_s_reg.ramcontrl & 0x3000) >> 12);
}

// func_06025244
void SCL_AbortAutoVe(void) { SclAutoVeFlag = 0; }

// func_0602525C
void SCL_SetColMixRate(Uint32 Surfaces, Uint8 Rate) {
    SCL_SET_CCRTMD(0);
    SCL_SET_CCMD(0);
    if (Surfaces & SCL_SP0) {
        if (Rate < 32) {
            SCL_SET_SPCCEN(1);
            SCL_SET_S0CCRT(Rate);
        } else {
            SCL_SET_SPCCEN(0);
        }
    }
    if (Surfaces & SCL_SP1) {
        if (Rate < 32) {
            SCL_SET_SPCCEN(1);
            SCL_SET_S1CCRT(Rate);
        } else {
            SCL_SET_SPCCEN(0);
        }
    }
    if (Surfaces & SCL_SP2) {
        if (Rate < 32) {
            SCL_SET_SPCCEN(1);
            SCL_SET_S2CCRT(Rate);
        } else {
            SCL_SET_SPCCEN(0);
        }
    }
    if (Surfaces & SCL_SP3) {
        if (Rate < 32) {
            SCL_SET_SPCCEN(1);
            SCL_SET_S3CCRT(Rate);
        } else {
            SCL_SET_SPCCEN(0);
        }
    }
    if (Surfaces & SCL_SP4) {
        if (Rate < 32) {
            SCL_SET_SPCCEN(1);
            SCL_SET_S4CCRT(Rate);
        } else {
            SCL_SET_SPCCEN(0);
        }
    }
    if (Surfaces & SCL_SP5) {
        if (Rate < 32) {
            SCL_SET_SPCCEN(1);
            SCL_SET_S5CCRT(Rate);
        } else {
            SCL_SET_SPCCEN(0);
        }
    }
    if (Surfaces & SCL_SP6) {
        if (Rate < 32) {
            SCL_SET_SPCCEN(1);
            SCL_SET_S6CCRT(Rate);
        } else {
            SCL_SET_SPCCEN(0);
        }
    }
    if (Surfaces & SCL_SP7) {
        if (Rate < 32) {
            SCL_SET_SPCCEN(1);
            SCL_SET_S7CCRT(Rate);
        } else {
            SCL_SET_SPCCEN(0);
        }
    }
    if ((Surfaces & SCL_NBG0) || (Surfaces & SCL_RBG1)) {
        if (Rate < 32) {
            SCL_SET_N0CCEN(1);
            SCL_SET_N0CCRT(Rate);
        } else {
            SCL_SET_N0CCEN(0);
        }
    }
    if ((Surfaces & SCL_NBG1) || (Surfaces & SCL_EXBG)) {
        if (Rate < 32) {
            SCL_SET_N1CCEN(1);
            SCL_SET_N1CCRT(Rate);
        } else {
            SCL_SET_N1CCEN(0);
        }
    }
    if (Surfaces & SCL_NBG2) {
        if (Rate < 32) {
            SCL_SET_N2CCEN(1);
            SCL_SET_N2CCRT(Rate);
        } else {
            SCL_SET_N2CCEN(0);
        }
    }
    if (Surfaces & SCL_NBG3) {
        if (Rate < 32) {
            SCL_SET_N3CCEN(1);
            SCL_SET_N3CCRT(Rate);
        } else {
            SCL_SET_N3CCEN(0);
        }
    }
    if (Surfaces & SCL_RBG0) {
        if (Rate < 32) {
            SCL_SET_R0CCEN(1);
            SCL_SET_R0CCRT(Rate);
        } else {
            SCL_SET_R0CCEN(0);
        }
    }
}

extern Uint32 SclAutoSurface;
extern Uint32 SclAutoInterval;
extern Uint32 SclAutoCount;
extern Uint32 SclAutoIndex;
extern Uint32 SclAutoMax;
extern Sint16 SclAutoRed, SclAutoGreen, SclAutoBlue;
extern Sint16 SclAutoEndRed, SclAutoEndGreen, SclAutoEndBlue;
extern Sint16 SclAutoEndRed2, SclAutoEndGreen2, SclAutoEndBlue2;
extern Uint8 SclAutoCurRate;
extern Uint8 SclAutoEndRate;
extern Uint8 SclAutoVeFlag;
extern Uint8 SclAutoPlusFlag;
extern Uint8 SclAutoRGB[6][256];

// func_06025AE4
void SCL_AutoExec(void) {
    Uint32 ColorL[1];
    Uint8* ColorB;
    Uint32 i;

    ColorB = (Uint8*)ColorL;

    switch (SclAutoVeFlag) {
    case 1:
        if (SclAutoInterval > SclAutoCount)
            SclAutoCount++;
        else {
            SclAutoVeFlag = 0;
            for (i = 0; i < SclAutoMax; i++) {
                if (SclAutoRGB[0][i] > SclAutoRGB[3][i]) {
                    SclAutoRGB[3][i]++;
                    SclAutoVeFlag = 1;
                } else if (SclAutoRGB[0][i] < SclAutoRGB[3][i]) {
                    SclAutoRGB[3][i]--;
                    SclAutoVeFlag = 1;
                }
                if (SclAutoRGB[1][i] > SclAutoRGB[4][i]) {
                    SclAutoRGB[4][i]++;
                    SclAutoVeFlag = 1;
                } else if (SclAutoRGB[1][i] < SclAutoRGB[4][i]) {
                    SclAutoRGB[4][i]--;
                    SclAutoVeFlag = 1;
                }
                if (SclAutoRGB[2][i] > SclAutoRGB[5][i]) {
                    SclAutoRGB[5][i]++;
                    SclAutoVeFlag = 1;
                } else if (SclAutoRGB[2][i] < SclAutoRGB[5][i]) {
                    SclAutoRGB[5][i]--;
                    SclAutoVeFlag = 1;
                }
            }
            SclAutoCount = 0;
            if (SCL_GetColRamMode() == SCL_CRM24_1024) {
                for (i = 0; i < SclAutoMax; i++) {
                    ColorB[0] = 0;
                    ColorB[1] = SclAutoRGB[3][i];
                    ColorB[2] = SclAutoRGB[4][i];
                    ColorB[3] = SclAutoRGB[5][i];
                    SCL_SetColRam(
                        SclAutoSurface, SclAutoIndex + i, 1, &ColorL[0]);
                }
            } else {
                for (i = 0; i < SclAutoMax; i++) {
                    ColorL[0] = SclAutoRGB[3][i];
                    ColorL[0] = (ColorL[0] << 5) | SclAutoRGB[4][i];
                    ColorL[0] = (ColorL[0] << 5) | SclAutoRGB[5][i];
                    SCL_SetColRam(
                        SclAutoSurface, SclAutoIndex + i, 1, &ColorL[0]);
                }
            }
        }
        break;
    case 2:
        if (SclAutoInterval > SclAutoCount)
            SclAutoCount++;
        else {
            if (SclAutoPlusFlag) {
                SclAutoCurRate++;
                if (SclAutoCurRate >= SclAutoEndRate) {
                    SclAutoCurRate = SclAutoEndRate;
                    SclAutoVeFlag = 0;
                }
            } else {
                SclAutoCurRate--;
                if (SclAutoCurRate <= SclAutoEndRate) {
                    SclAutoCurRate = SclAutoEndRate;
                    SclAutoVeFlag = 0;
                }
            }
            if (SCL_SP0 & SclAutoSurface)
                SCL_SetColMixRate(SCL_SP0, SclAutoCurRate);
            if (SCL_SP1 & SclAutoSurface)
                SCL_SetColMixRate(SCL_SP1, SclAutoCurRate);
            if (SCL_SP2 & SclAutoSurface)
                SCL_SetColMixRate(SCL_SP2, SclAutoCurRate);
            if (SCL_SP3 & SclAutoSurface)
                SCL_SetColMixRate(SCL_SP3, SclAutoCurRate);
            if (SCL_SP4 & SclAutoSurface)
                SCL_SetColMixRate(SCL_SP4, SclAutoCurRate);
            if (SCL_SP5 & SclAutoSurface)
                SCL_SetColMixRate(SCL_SP5, SclAutoCurRate);
            if (SCL_SP6 & SclAutoSurface)
                SCL_SetColMixRate(SCL_SP6, SclAutoCurRate);
            if (SCL_SP7 & SclAutoSurface)
                SCL_SetColMixRate(SCL_SP7, SclAutoCurRate);
            if (SCL_NBG0 & SclAutoSurface)
                SCL_SetColMixRate(SCL_NBG0, SclAutoCurRate);
            if (SCL_NBG1 & SclAutoSurface)
                SCL_SetColMixRate(SCL_NBG1, SclAutoCurRate);
            if (SCL_NBG2 & SclAutoSurface)
                SCL_SetColMixRate(SCL_NBG2, SclAutoCurRate);
            if (SCL_NBG3 & SclAutoSurface)
                SCL_SetColMixRate(SCL_NBG3, SclAutoCurRate);
            if (SCL_RBG0 & SclAutoSurface)
                SCL_SetColMixRate(SCL_RBG0, SclAutoCurRate);
            if (SCL_RBG1 & SclAutoSurface)
                SCL_SetColMixRate(SCL_RBG1, SclAutoCurRate);
            if (SCL_EXBG & SclAutoSurface)
                SCL_SetColMixRate(SCL_EXBG, SclAutoCurRate);
            SclAutoCount = 0;
        }
        break;
    case 3:
        if (SclAutoInterval > SclAutoCount)
            SclAutoCount++;
        else {
            SclAutoEndRed -= SclAutoRed;
            SclAutoEndGreen -= SclAutoGreen;
            SclAutoEndBlue -= SclAutoBlue;
            if (SclAutoRed > 0) {
                if (SclAutoEndRed <= 0)
                    SclAutoRed = 0;
            } else {
                if (SclAutoEndRed >= 0)
                    SclAutoRed = 0;
            }

            if (SclAutoGreen > 0) {
                if (SclAutoEndGreen <= 0)
                    SclAutoGreen = 0;
            } else {
                if (SclAutoEndGreen >= 0)
                    SclAutoGreen = 0;
            }

            if (SclAutoBlue > 0) {
                if (SclAutoEndBlue <= 0)
                    SclAutoBlue = 0;
            } else {
                if (SclAutoEndBlue >= 0)
                    SclAutoBlue = 0;
            }

            SCL_IncColOffset(
                SclAutoSurface, SclAutoRed, SclAutoGreen, SclAutoBlue);

            if (SclAutoRed == 0 && SclAutoGreen == 0 && SclAutoBlue == 0) {
                SclAutoVeFlag = 0;
                if (SclAutoSurface == SCL_OFFSET_A) {
                    SCL_SET_COARD(SclAutoEndRed2);
                    SCL_SET_COAGR(SclAutoEndGreen2);
                    SCL_SET_COABL(SclAutoEndBlue2);
                } else {
                    SCL_SET_COBRD(SclAutoEndRed2);
                    SCL_SET_COBGR(SclAutoEndGreen2);
                    SCL_SET_COBBL(SclAutoEndBlue2);
                }
            }
            SclAutoCount = 0;
        }
        break;
    }
}

// func_060263E0
void SCL_IncColOffset(Uint32 OffsetReg, Sint16 red, Sint16 green, Sint16 blue) {
    if (OffsetReg == SCL_OFFSET_A) {
        SCL_SET_COARD(SCL_GET_COARD() + red);
        SCL_SET_COAGR(SCL_GET_COAGR() + green);
        SCL_SET_COABL(SCL_GET_COABL() + blue);
    } else {
        SCL_SET_COBRD(SCL_GET_COBRD() + red);
        SCL_SET_COBGR(SCL_GET_COBGR() + green);
        SCL_SET_COBBL(SCL_GET_COBBL() + blue);
    }
}

// func_06026534
static void SCL_InitSclOtherPri(void) {
    SCL_SET_SPCCCS(3);
    SCL_SET_SPCCEN(0);
    SCL_SET_SPCLMD(1);
    SCL_SET_SPWINEN(0);
    SCL_SET_SPTYPE(7);
    SCL_SET_N0CAOS(0);
    SCL_SET_N1CAOS(0);
    SCL_SET_N2CAOS(0);
    SCL_SET_N3CAOS(0);
    SCL_SET_R0CAOS(0);
    SCL_SET_SPCAOS(0);
    SCL_SET_N0CAOS(0);
    SCL_SET_N1CAOS(0);
    SCL_SET_N2CAOS(0);
    SCL_SET_N3CAOS(0);
    SCL_SET_R0CAOS(0);
    SCL_SET_SPCAOS(0);
    SCL_SET_N0LCEN(0);
    SCL_SET_N1LCEN(0);
    SCL_SET_N2LCEN(0);
    SCL_SET_N3LCEN(0);
    SCL_SET_R0LCEN(0);
    SCL_SET_SPLCEN(0);
    SCL_SET_N0SPRM(0);
    SCL_SET_N1SPRM(0);
    SCL_SET_N2SPRM(0);
    SCL_SET_N3SPRM(0);
    SCL_SET_R0SPRM(0);
    SCL_SET_BOKEN(0);
    SCL_SET_BOKN(0);
    SCL_SET_EXCCEN(0);
    SCL_SET_CCRTMD(0);
    SCL_SET_CCMD(1);
    SCL_SET_SPCCEN(0);
    SCL_SET_LCCCEN(0);
    SCL_SET_R0CCEN(0);
    SCL_SET_N3CCEN(0);
    SCL_SET_N2CCEN(0);
    SCL_SET_N1CCEN(0);
    SCL_SET_N0CCEN(0);
    SCL_SET_N0SCCM(0);
    SCL_SET_N1SCCM(0);
    SCL_SET_N2SCCM(0);
    SCL_SET_N3SCCM(0);
    SCL_SET_R0SCCM(0);
    SCL_SET_N0SDEN(0);
    SCL_SET_N1SDEN(0);
    SCL_SET_N2SDEN(0);
    SCL_SET_N3SDEN(0);
    SCL_SET_R0SDEN(0);
    SCL_SET_BKSDEN(0);
    SCL_SET_TPSDSL(0);
    SclPriBuffDirty.SclOtherPri = 1;
}

// func_06026C30
static void SCL_InitSclSpPriNum(void) {
    SCL_SET_S0PRIN(0);
    SCL_SET_S1PRIN(0);
    SCL_SET_S2PRIN(0);
    SCL_SET_S3PRIN(0);
    SCL_SET_S4PRIN(0);
    SCL_SET_S5PRIN(0);
    SCL_SET_S6PRIN(0);
    SCL_SET_S7PRIN(0);
    SclPriBuffDirty.SclSpPriNum = 1;
}

// func_06026D3C
static void SCL_InitSclBgPriNum(void) {
    SCL_SET_N0PRIN(3);
    SCL_SET_N1PRIN(2);
    SCL_SET_N2PRIN(1);
    SCL_SET_N3PRIN(0);
    SCL_SET_R0PRIN(4);
    SclPriBuffDirty.SclBgPriNum = 1;
}

// func_06026DF0
static void SCL_InitSclSpColMix(void) {
    SCL_SET_S0CCRT(0);
    SCL_SET_S1CCRT(0);
    SCL_SET_S2CCRT(0);
    SCL_SET_S3CCRT(0);
    SCL_SET_S4CCRT(0);
    SCL_SET_S5CCRT(0);
    SCL_SET_S6CCRT(0);
    SCL_SET_S5CCRT(0);
    SclPriBuffDirty.SclSpColMix = 1;
}

// func_06026EEC
static void SCL_InitSclBgColMix(void) {
    SCL_SET_N0CCRT(0);
    SCL_SET_N1CCRT(0);
    SCL_SET_N2CCRT(0);
    SCL_SET_N3CCRT(0);
    SCL_SET_R0CCRT(0);
    SCL_SET_LCCCRT(0);
    SCL_SET_BKCCRT(0);
    SclPriBuffDirty.SclBgColMix = 1;
}

// func_06026FC4
static void SCL_InitSclColOffset(void) {

    SCL_SET_N0COEN(0);
    SCL_SET_N1COEN(0);
    SCL_SET_N2COEN(0);
    SCL_SET_N3COEN(0);
    SCL_SET_R0COEN(0);
    SCL_SET_BKCOEN(0);
    SCL_SET_SPCOEN(0);
    SCL_SET_N0COSL(0);
    SCL_SET_N1COSL(0);
    SCL_SET_N2COSL(0);
    SCL_SET_N3COSL(0);
    SCL_SET_R0COSL(0);
    SCL_SET_BKCOSL(0);
    SCL_SET_SPCOSL(0);
    SCL_SET_COARD(0);
    SCL_SET_COAGR(0);
    SCL_SET_COABL(0);
    SCL_SET_COBRD(0);
    SCL_SET_COBGR(0);
    SCL_SET_COBBL(0);
    SclPriBuffDirty.SclColOffset = 1;
}

// func_060271F0
void SCL_SetShadowBit(Uint32 Object) {
    SCL_SET_TPSDSL(0);
    SCL_SET_N0SDEN(0);
    SCL_SET_N1SDEN(0);
    SCL_SET_N2SDEN(0);
    SCL_SET_N3SDEN(0);
    SCL_SET_R0SDEN(0);
    SCL_SET_BKSDEN(0);

    if (Object) {
        SCL_SET_TPSDSL(1);
        if (SCL_NBG0 & Object)
            SCL_SET_N0SDEN(1);
        if (SCL_RBG1 & Object)
            SCL_SET_N0SDEN(1);
        if (SCL_NBG1 & Object)
            SCL_SET_N1SDEN(1);
        if (SCL_EXBG & Object)
            SCL_SET_N1SDEN(1);
        if (SCL_NBG2 & Object)
            SCL_SET_N2SDEN(1);
        if (SCL_NBG3 & Object)
            SCL_SET_N3SDEN(1);
        if (SCL_RBG0 & Object)
            SCL_SET_R0SDEN(1);
        if (SCL_BACK & Object)
            SCL_SET_BKSDEN(1);
    }
}

#include "sys.h"

// func_060274C0
void SCL_SetDisplayMode(Uint8 interlace, Uint8 vertical, Uint8 horizontal) {
    Uint32 SysClock;

    SysClock = SYS_GETSYSCK;

    Scl_s_reg.tvmode &= 0xffcf;
    switch (vertical) {
    case SCL_224LINE:
        SclDisplayY = 224;
        break;
    case SCL_240LINE:
        SclDisplayY = 240;
        Scl_s_reg.tvmode |= 0x0010;
        break;
    case SCL_256LINE:
        SclDisplayY = 256;
        Scl_s_reg.tvmode |= 0x0020;
        break;
    }

    Scl_s_reg.tvmode &= 0xff3f;
    switch (interlace) {
    case SCL_NON_INTER:
        break;
    case SCL_SINGLE_INTER:
        Scl_s_reg.tvmode |= 0x0080;
        break;
    case SCL_DOUBLE_INTER:
        SclDisplayY *= 2;
        Scl_s_reg.tvmode |= 0x00c0;
        break;
    }

    Scl_s_reg.tvmode &= 0xfff0;
    switch (horizontal) {
    case SCL_NORMAL_A:
        SclDisplayX = 320;
        if (SysClock != 0)
            SYS_CHGSYSCK(0);
        break;
    case SCL_NORMAL_B:
        SclDisplayX = 352;
        Scl_s_reg.tvmode |= 0x0001;
        if (SysClock != 1)
            SYS_CHGSYSCK(1);
        break;
    case SCL_HIRESO_A:
        SclDisplayX = 640;
        Scl_s_reg.tvmode |= 0x0002;
        if (SysClock != 0)
            SYS_CHGSYSCK(0);
        break;
    case SCL_HIRESO_B:
        SclDisplayX = 704;
        Scl_s_reg.tvmode |= 0x0003;
        if (SysClock != 1)
            SYS_CHGSYSCK(1);
        break;
    case SCL_NORMAL_AE:
        SclDisplayX = 320;
        SclDisplayY = 480;
        Scl_s_reg.tvmode |= 0x0004;
        if (SysClock != 0)
            SYS_CHGSYSCK(0);
        break;
    case SCL_NORMAL_BE:
        SclDisplayX = 352;
        SclDisplayY = 480;
        Scl_s_reg.tvmode |= 0x0005;
        if (SysClock != 1)
            SYS_CHGSYSCK(1);
        break;
    case SCL_HIRESO_AE:
        SclDisplayX = 640;
        SclDisplayY = 480;
        Scl_s_reg.tvmode |= 0x0006;
        if (SysClock != 0)
            SYS_CHGSYSCK(0);
        break;
    case SCL_HIRESO_BE:
        SclDisplayX = 704;
        SclDisplayY = 480;
        Scl_s_reg.tvmode |= 0x0007;
        if (SysClock != 1)
            SYS_CHGSYSCK(1);
        break;
    }
    if (SclProcess == 0)
        SclProcess = 1;
}

// func_060277D8
void SCL_SetColOffset(
    Uint32 OffsetReg, Uint32 Surfaces, Sint16 red, Sint16 green, Sint16 blue) {
    if (OffsetReg == SCL_OFFSET_A) {
        SCL_SET_COARD(red);
        SCL_SET_COAGR(green);
        SCL_SET_COABL(blue);
    } else {
        SCL_SET_COBRD(red);
        SCL_SET_COBGR(green);
        SCL_SET_COBBL(blue);
    }
    if (Surfaces & SCL_SP0) {
        SCL_SET_SPCOEN(1);
        SCL_SET_SPCOSL(OffsetReg);
    }
    if (Surfaces & SCL_NBG0) {
        SCL_SET_N0COEN(1);
        SCL_SET_N0COSL(OffsetReg);
    }
    if (Surfaces & SCL_NBG1) {
        SCL_SET_N1COEN(1);
        SCL_SET_N1COSL(OffsetReg);
    }
    if (Surfaces & SCL_NBG2) {
        SCL_SET_N2COEN(1);
        SCL_SET_N2COSL(OffsetReg);
    }
    if (Surfaces & SCL_NBG3) {
        SCL_SET_N3COEN(1);
        SCL_SET_N3COSL(OffsetReg);
    }
    if (Surfaces & SCL_RBG0) {
        SCL_SET_R0COEN(1);
        SCL_SET_R0COSL(OffsetReg);
    }
    if (Surfaces & SCL_BACK) {
        SCL_SET_BKCOEN(1);
        SCL_SET_BKCOSL(OffsetReg);
    }
}

// func_06027B74
void SCL_InitVramConfigTb(SclVramConfig* tp) {
    tp->ktboffsetA = 0;
    tp->ktboffsetB = 0;
    tp->vramModeA = OFF;
    tp->vramModeB = OFF;

    tp->vramA0 = SCL_NON;
    tp->vramA1 = SCL_NON;
    tp->vramB0 = SCL_NON;
    tp->vramB1 = SCL_NON;
    tp->colram = SCL_NON;
}

// func_06027BD8
void SCL_SetVramConfig(SclVramConfig* tp) {
    Uint8 sw, offsw;

    SclRbgKtbAddr[0] = 0;
    SclRbgKtbAddr[1] = 0;
    SclRbgKtbOffset[0] = tp->ktboffsetA;
    SclRbgKtbOffset[1] = tp->ktboffsetB;

    Scl_s_reg.ramcontrl &= 0x7fff;

    if (tp->vramModeA == ON)
        Scl_s_reg.ramcontrl |= 0x0100;
    else
        Scl_s_reg.ramcontrl &= 0xfeff;

    if (tp->vramModeB == ON)
        Scl_s_reg.ramcontrl |= 0x0200;
    else
        Scl_s_reg.ramcontrl &= 0xfdff;

    sw = 0;
    offsw = 0;

    if (tp->vramA0 < 4) {
        Scl_s_reg.ramcontrl =
            (Scl_s_reg.ramcontrl & 0xfffc) | (Uint16)tp->vramA0;
        if (tp->vramA0 == SCL_RBG0_K) {
            if (SclRbgKtbOffset[0])
                Scl_s_reg.ramcontrl &= 0xfffc;
            else
                offsw = 1;
            sw = 1;
            Scl_r_reg.k_offset &= 0xff00;
            SclRbgKtbAddr[0] = SCL_VDP2_VRAM_A0 + SclRbgKtbOffset[0];
        }
    } else {
        if (tp->vramA0 == SCL_RBG1_K) {
            Scl_r_reg.k_offset &= 0x00ff;
            SclRbgKtbAddr[1] = SCL_VDP2_VRAM_A0 + SclRbgKtbOffset[1];
        }
    }

    if (tp->vramA1 < 4) {
        Scl_s_reg.ramcontrl =
            (Scl_s_reg.ramcontrl & 0xfff3) | (Uint16)(tp->vramA1 << 2);
        if (tp->vramA1 == SCL_RBG0_K) {
            if (sw == 0) {
                if (SclRbgKtbOffset[0])
                    Scl_s_reg.ramcontrl &= 0xfff3;
                else
                    offsw = 2;
                Scl_r_reg.k_offset &= 0xff00;
                Scl_r_reg.k_offset |= 0x0001;
                SclRbgKtbAddr[0] = SCL_VDP2_VRAM_A1 + SclRbgKtbOffset[0];
                sw = 1;
            } else {
                if (SclRbgKtbOffset[1])
                    Scl_s_reg.ramcontrl &= 0xfff3;
                Scl_r_reg.k_offset &= 0x00ff;
                Scl_r_reg.k_offset |= 0x0100;
                SclRbgKtbAddr[1] = SCL_VDP2_VRAM_A1 + SclRbgKtbOffset[1];
                sw++;
            }
        }
    } else {
        if (tp->vramA1 == SCL_RBG1_K) {
            Scl_r_reg.k_offset &= 0x00ff;
            Scl_r_reg.k_offset |= 0x0100;
            SclRbgKtbAddr[1] = SCL_VDP2_VRAM_A1 + SclRbgKtbOffset[1];
        }
    }

    if (tp->vramB0 < 4) {
        Scl_s_reg.ramcontrl =
            (Scl_s_reg.ramcontrl & 0xffcf) | (Uint16)(tp->vramB0 << 4);
        if (tp->vramB0 == SCL_RBG0_K) {
            if (sw == 0) {
                if (SclRbgKtbOffset[0])
                    Scl_s_reg.ramcontrl &= 0xffcf;
                else
                    offsw = 3;
                Scl_r_reg.k_offset &= 0xff00;
                Scl_r_reg.k_offset |= 0x0002;
                sw = 1;
                SclRbgKtbAddr[0] = SCL_VDP2_VRAM_B0 + SclRbgKtbOffset[0];
            } else {
                if (SclRbgKtbOffset[1])
                    Scl_s_reg.ramcontrl &= 0xffcf;
                Scl_r_reg.k_offset &= 0x00ff;
                Scl_r_reg.k_offset |= 0x0200;
                sw++;
                SclRbgKtbAddr[1] = SCL_VDP2_VRAM_B0 + SclRbgKtbOffset[1];
            }
        }
    } else {
        if (tp->vramB0 == SCL_RBG1_K && SclRbgKtbOffset[1]) {
            Scl_r_reg.k_offset &= 0x00ff;
            Scl_r_reg.k_offset |= 0x0200;
            SclRbgKtbAddr[1] = SCL_VDP2_VRAM_B0 + SclRbgKtbOffset[1];
        }
    }

    if (tp->vramB1 < 4) {
        Scl_s_reg.ramcontrl =
            (Scl_s_reg.ramcontrl & 0xff3f) | (Uint16)(tp->vramB1 << 6);
        if (tp->vramB1 == SCL_RBG0_K) {
            if (sw == 0) {
                if (SclRbgKtbOffset[0])
                    Scl_s_reg.ramcontrl &= 0xff3f;
                else
                    offsw = 4;
                Scl_r_reg.k_offset &= 0xff00;
                Scl_r_reg.k_offset |= 0x0003;
                sw = 1;
                SclRbgKtbAddr[0] = SCL_VDP2_VRAM_B1 + SclRbgKtbOffset[0];
            } else {
                if (SclRbgKtbOffset[1])
                    Scl_s_reg.ramcontrl &= 0xff3f;
                Scl_r_reg.k_offset &= 0x00ff;
                Scl_r_reg.k_offset |= 0x0300;
                sw++;
                SclRbgKtbAddr[1] = SCL_VDP2_VRAM_B1 + SclRbgKtbOffset[1];
            }
        }
    } else {
        if (tp->vramB1 == SCL_RBG1_K && SclRbgKtbOffset[1]) {
            Scl_r_reg.k_offset &= 0x00ff;
            Scl_r_reg.k_offset |= 0x0300;
            SclRbgKtbAddr[1] = SCL_VDP2_VRAM_B1 + SclRbgKtbOffset[1];
        }
    }

    if (!SclRbgKtbAddr[1]) {
        if (tp->colram == SCL_RBG0_K && !SclRbgKtbAddr[0] &&
            SCL_GetColRamMode() == SCL_CRM15_2048) {
            Scl_s_reg.ramcontrl |= 0x8000;
            SclRbgKtbAddr[0] = SCL_COLRAM_ADDR + 0x800;
        } else if (SclRbgKtbAddr[0] && SclRb != SCL_NON) {
            if (!SclRbgKtbOffset[1])
                SclRbgKtbOffset[1] = 0x400 + SclRbgKtbOffset[0];
            if (!SclRbgKtbOffset[0])
                SclRbgKtbOffset[0] = -1;
            SclRbgKtbAddr[1] = SclRbgKtbAddr[0] + SclRbgKtbOffset[1];
            Scl_r_reg.k_offset =
                (Scl_r_reg.k_offset & 0x00ff) | Scl_r_reg.k_offset << 8;
            switch (offsw) {
            case 1:
                Scl_s_reg.ramcontrl &= 0xfffc;
                break;
            case 2:
                Scl_s_reg.ramcontrl &= 0xfff3;
                break;
            case 3:
                Scl_s_reg.ramcontrl &= 0xffcf;
                break;
            case 4:
                Scl_s_reg.ramcontrl &= 0xff3f;
                break;
            }
        } else if (!SclRbgKtbAddr[0]) {
            if (SclRbgKtbOffset[0] && SclRa != SCL_NON) {
                Scl_r_reg.k_offset &= 0xff00;
                Scl_r_reg.k_offset |= (Uint16)(SclRbgKtbOffset[0] / 0x20000);
                SclRbgKtbAddr[0] = SCL_VDP2_VRAM + SclRbgKtbOffset[0];
            }
            if (SclRbgKtbOffset[1] && SclRb != SCL_NON) {
                Scl_r_reg.k_offset &= 0x00ff;
                Scl_r_reg.k_offset |=
                    ((Uint16)(SclRbgKtbOffset[1] / 0x20000)) << 8;
                SclRbgKtbAddr[1] = SCL_VDP2_VRAM + SclRbgKtbOffset[1];
            }
        }
    }
}

// func_06028548
void SCL_SetSpriteMode(Uint8 Type, Uint8 ColMode, Uint8 WinMode) {
    SCL_SET_SPTYPE(Type);
    SCL_SET_SPCLMD(ColMode);
    SCL_SET_SPWINEN(WinMode);
}

// func_06028614
void SCL_SetPriority(Uint32 Object, Uint8 Priority) {
    Uint16 PriNum;

    PriNum = Priority;
    if (SCL_SP0 & Object)
        SCL_SET_S0PRIN(PriNum);
    if (SCL_SP1 & Object)
        SCL_SET_S1PRIN(PriNum);
    if (SCL_SP2 & Object)
        SCL_SET_S2PRIN(PriNum);
    if (SCL_SP3 & Object)
        SCL_SET_S3PRIN(PriNum);
    if (SCL_SP4 & Object)
        SCL_SET_S4PRIN(PriNum);
    if (SCL_SP5 & Object)
        SCL_SET_S5PRIN(PriNum);
    if (SCL_SP6 & Object)
        SCL_SET_S6PRIN(PriNum);
    if (SCL_SP7 & Object)
        SCL_SET_S7PRIN(PriNum);
    if (SCL_NBG0 & Object)
        SCL_SET_N0PRIN(PriNum);
    if (SCL_RBG1 & Object)
        SCL_SET_N0PRIN(PriNum);
    if (SCL_NBG1 & Object)
        SCL_SET_N1PRIN(PriNum);
    if (SCL_EXBG & Object)
        SCL_SET_N1PRIN(PriNum);
    if (SCL_NBG2 & Object)
        SCL_SET_N2PRIN(PriNum);
    if (SCL_NBG3 & Object)
        SCL_SET_N3PRIN(PriNum);
    if (SCL_RBG0 & Object)
        SCL_SET_R0PRIN(PriNum);
}

// func_06028978
void SCL_SetColMixMode(Uint32 ColMixPriority, Uint8 Mode) {
    SCL_SET_SPCCCS(Mode);
    SCL_SET_SPCCN(ColMixPriority);
}

// func_06028A00
static void SCL_SetLineColReg(Uint32 Surface, Uint16 sw) {
    switch (Surface) {
    case SCL_SPR:
        SCL_SET_SPLCEN(sw);
        break;
    case SCL_RBG0:
        SCL_SET_R0LCEN(sw);
        break;
    case SCL_NBG0:
    case SCL_RBG1:
        SCL_SET_N0LCEN(sw);
        break;
    case SCL_NBG1:
    case SCL_EXBG:
        SCL_SET_N1LCEN(sw);
        break;
    case SCL_NBG2:
        SCL_SET_N2LCEN(sw);
        break;
    case SCL_NBG3:
        SCL_SET_N3LCEN(sw);
        break;
    default:
        break;
    }
}

// func_06028BE4
void SCL_EnableLineCol(Uint32 Surface) { SCL_SetLineColReg(Surface, 1); }

// func_06028C0C
void SCL_DisableLineCol(Uint32 Surface) { SCL_SetLineColReg(Surface, 0); }

// func_06028C34
void SCL_SetBack(Uint32 addr, Uint16 dataSize, Uint16* dataTb) {
    if (dataSize == 1 || dataSize == SclDisplayY) {
        Scl_n_reg.backcolmode = addr & 0x0007ffff;

        SCL_Memcpyw(
            (void*)(Scl_n_reg.backcolmode | 0x25e00000), dataTb, dataSize * 2);

        Scl_n_reg.backcolmode /= 2;

        if (dataSize != 1)
            Scl_n_reg.backcolmode |= 0x80000000;
        if (SclProcess == 0)
            SclProcess = 1;
    }
}

// func_06028D10
void SCL_InitConfigTb(SclConfig* scfg) {
    Uint8 i;

    scfg->dispenbl = OFF;
    scfg->charsize = SCL_CHAR_SIZE_1X1;
    scfg->pnamesize = SCL_PN2WORD;
    scfg->platesize = SCL_PL_SIZE_1X1;
    scfg->bmpsize = SCL_BMP_SIZE_512X256;
    scfg->coltype = SCL_COL_TYPE_16;
    scfg->datatype = SCL_CELL;
    scfg->flip = SCL_PN_10BIT;
    scfg->mapover = SCL_OVER_0;
    scfg->patnamecontrl = 0;

    for (i = 0; i < 16; i++)
        scfg->plate_addr[i] = 0;
}

// func_06028ddc
void SCL_SetConfig(Uint16 sclnum, SclConfig* scfg) {
    Uint16 temp;
    Uint16* mapoffset = 0;
    Uint16* map = 0;
    Uint16* map2;
    Uint16 boundary = 0;
    Uint16 shift = 0;
    Uint16 shift2 = 0;
    Uint16 max = 0;
    Uint16 i;
    Uint16 flip;
    Uint16 mapoffsetW;

    map2 = 0;

    flip = scfg->flip;
    flip = (flip << 14) & 0x4000;
    switch (sclnum) {
    case SCL_NBG0:
        temp = scfg->dispenbl;
        temp &= 0x0001;
        Scl_s_reg.dispenbl &= 0xfffe;
        Scl_s_reg.dispenbl |= temp;

        temp = scfg->charsize;
        temp &= 0x0001;
        Scl_d_reg.charcontrl0 &= 0xfffe;
        Scl_d_reg.charcontrl0 |= temp;

        Scl_d_reg.patnamecontrl[0] = scfg->patnamecontrl;

        temp = scfg->pnamesize;
        temp = (temp << 15) & 0x8000;
        Scl_d_reg.patnamecontrl[0] &= 0x7fff;
        Scl_d_reg.patnamecontrl[0] |= temp;

        Scl_d_reg.patnamecontrl[0] &= 0xbfff;
        Scl_d_reg.patnamecontrl[0] |= flip;

        temp = scfg->platesize;
        temp &= 0x0003;
        Scl_d_reg.platesize &= 0xfffc;
        Scl_d_reg.platesize |= temp;

        temp = scfg->bmpsize;
        temp = (temp << 2) & 0x000c;
        Scl_d_reg.charcontrl0 &= 0xfff3;
        Scl_d_reg.charcontrl0 |= temp;

        temp = scfg->coltype;
        temp = (temp << 4) & 0x0070;
        Scl_d_reg.charcontrl0 &= 0xff8f;
        Scl_d_reg.charcontrl0 |= temp;

        temp = scfg->datatype;
        temp = (temp << 1) & 0x0002;
        Scl_d_reg.charcontrl0 &= 0xfffd;
        Scl_d_reg.charcontrl0 |= temp;

        Scl_d_reg.mapoffset0 &= 0xfff0;
        mapoffset = &Scl_d_reg.mapoffset0;
        shift = 0;
        map = &Scl_d_reg.normap[0];
        max = 2;
        break;
    case SCL_NBG1:
        temp = scfg->dispenbl;
        temp = (temp << 1) & 0x0002;
        Scl_s_reg.dispenbl &= 0xfffD;
        Scl_s_reg.dispenbl |= temp;

        temp = scfg->charsize;
        temp = (temp << 8) & 0x0100;
        Scl_d_reg.charcontrl0 &= 0xfeff;
        Scl_d_reg.charcontrl0 |= temp;

        Scl_d_reg.patnamecontrl[1] = scfg->patnamecontrl;

        temp = scfg->pnamesize;
        temp = (temp << 15) & 0x8000;
        Scl_d_reg.patnamecontrl[1] &= 0x7fff;
        Scl_d_reg.patnamecontrl[1] |= temp;

        Scl_d_reg.patnamecontrl[1] &= 0xbfff;
        Scl_d_reg.patnamecontrl[1] |= flip;

        temp = scfg->platesize;
        temp = (temp << 2) & 0x000c;
        Scl_d_reg.platesize &= 0xfff3;
        Scl_d_reg.platesize |= temp;

        temp = scfg->bmpsize;
        temp = (temp << 10) & 0x0c00;
        Scl_d_reg.charcontrl0 &= 0xf3ff;
        Scl_d_reg.charcontrl0 |= temp;

        temp = scfg->coltype;
        temp = (temp << 12) & 0x3000;
        Scl_d_reg.charcontrl0 &= 0xcfff;
        Scl_d_reg.charcontrl0 |= temp;

        temp = scfg->datatype;
        temp = (temp << 9) & 0x0200;
        Scl_d_reg.charcontrl0 &= 0xfdff;
        Scl_d_reg.charcontrl0 |= temp;

        Scl_d_reg.mapoffset0 &= 0xff0f;
        mapoffset = &Scl_d_reg.mapoffset0;
        shift = 4;
        map = &Scl_d_reg.normap[2];
        max = 2;
        break;
    case SCL_NBG2:
        temp = scfg->dispenbl;
        temp = (temp << 2) & 0x0004;
        Scl_s_reg.dispenbl &= 0xfffb;
        Scl_s_reg.dispenbl |= temp;

        temp = scfg->charsize;
        temp = temp & 0x0001;
        Scl_d_reg.charcontrl1 &= 0xfffe;
        Scl_d_reg.charcontrl1 |= temp;

        Scl_d_reg.patnamecontrl[2] = scfg->patnamecontrl;

        temp = scfg->pnamesize;
        temp = (temp << 15) & 0x8000;
        Scl_d_reg.patnamecontrl[2] &= 0x7fff;
        Scl_d_reg.patnamecontrl[2] |= temp;

        Scl_d_reg.patnamecontrl[2] &= 0xbfff;
        Scl_d_reg.patnamecontrl[2] |= flip;

        temp = scfg->platesize;
        temp = (temp << 4) & 0x0030;
        Scl_d_reg.platesize &= 0xffcf;
        Scl_d_reg.platesize |= temp;

        temp = scfg->coltype;
        temp = (temp << 1) & 0x0002;
        Scl_d_reg.charcontrl1 &= 0xfffd;
        Scl_d_reg.charcontrl1 |= temp;

        Scl_d_reg.mapoffset0 &= 0xf0ff;
        mapoffset = &Scl_d_reg.mapoffset0;
        shift = 8;
        map = &Scl_d_reg.normap[4];
        max = 2;
        break;
    case SCL_NBG3:
        temp = scfg->dispenbl;
        temp = (temp << 3) & 0x0008;
        Scl_s_reg.dispenbl &= 0xfff7;
        Scl_s_reg.dispenbl |= temp;

        temp = scfg->charsize;
        temp = (temp << 4) & 0x0010;
        Scl_d_reg.charcontrl1 &= 0xffef;
        Scl_d_reg.charcontrl1 |= temp;

        Scl_d_reg.patnamecontrl[3] = scfg->patnamecontrl;

        temp = scfg->pnamesize;
        temp = (temp << 15) & 0x8000;
        Scl_d_reg.patnamecontrl[3] &= 0x7fff;
        Scl_d_reg.patnamecontrl[3] |= temp;

        Scl_d_reg.patnamecontrl[3] &= 0xbfff;
        Scl_d_reg.patnamecontrl[3] |= flip;

        temp = scfg->platesize;
        temp = (temp << 6) & 0x00c0;
        Scl_d_reg.platesize &= 0xff3f;
        Scl_d_reg.platesize |= temp;

        temp = scfg->coltype;
        temp = (temp << 5) & 0x0020;
        Scl_d_reg.charcontrl1 &= 0xffdf;
        Scl_d_reg.charcontrl1 |= temp;

        Scl_d_reg.mapoffset0 &= 0x0fff;
        mapoffset = &Scl_d_reg.mapoffset0;
        shift = 12;
        map = &Scl_d_reg.normap[6];
        max = 2;
        break;
    case SCL_RBG0:
        temp = scfg->dispenbl;
        temp = (temp << 4) & 0x0010;
        Scl_s_reg.dispenbl &= 0xffef;
        Scl_s_reg.dispenbl |= temp;

        temp = scfg->charsize;
        temp = (temp << 8) & 0x0100;
        Scl_d_reg.charcontrl1 &= 0xfeff;
        Scl_d_reg.charcontrl1 |= temp;

        Scl_d_reg.patnamecontrl[4] = scfg->patnamecontrl;

        temp = scfg->pnamesize;
        temp = (temp << 15) & 0x8000;
        Scl_d_reg.patnamecontrl[4] &= 0x7fff;
        Scl_d_reg.patnamecontrl[4] |= temp;

        Scl_d_reg.patnamecontrl[4] &= 0xbfff;
        Scl_d_reg.patnamecontrl[4] |= flip;

        temp = scfg->bmpsize;
        temp = (temp << 10) & 0x0400;
        Scl_d_reg.charcontrl1 &= 0xfbff;
        Scl_d_reg.charcontrl1 |= temp;

        temp = scfg->coltype;
        temp = (temp << 12) & 0x7000;
        Scl_d_reg.charcontrl1 &= 0x8fff;
        Scl_d_reg.charcontrl1 |= temp;

        temp = scfg->datatype;
        temp = (temp << 9) & 0x0200;
        Scl_d_reg.charcontrl1 &= 0xfdff;
        Scl_d_reg.charcontrl1 |= temp;

        max = 8;

        if ((SclRa == SCL_RBG0) && (SclRb == SCL_RBG0)) {
            Scl_d_reg.mapoffset1 &= 0xfff0;
            mapoffset = &Scl_d_reg.mapoffset1;
            shift = 0;
            map = &Scl_d_reg.rotmap[0];
            shift2 = 4;
            map2 = &Scl_d_reg.rotmap[8];

            temp = scfg->platesize;
            temp = ((temp << 8) & 0x0300) | ((temp << 12) & 0x3000);
            Scl_d_reg.platesize &= 0xfcff;
            Scl_d_reg.platesize |= temp;

            temp = scfg->mapover;
            temp = ((temp << 10) & 0x0c00) | ((temp << 14) & 0xc000);
            Scl_d_reg.platesize &= 0x33ff;
            Scl_d_reg.platesize |= temp;
        } else {
            if (SclRa == SCL_RBG0) {
                Scl_d_reg.mapoffset1 &= 0xfff0;
                mapoffset = &Scl_d_reg.mapoffset1;
                shift = 0;
                map = &Scl_d_reg.rotmap[0];

                temp = scfg->platesize;
                temp = (temp << 8) & 0x0300;
                Scl_d_reg.platesize &= 0xfcff;
                Scl_d_reg.platesize |= temp;

                temp = scfg->mapover;
                temp = (temp << 10) & 0x0c00;
                Scl_d_reg.platesize &= 0xf3ff;
                Scl_d_reg.platesize |= temp;
            } else if (SclRb == SCL_RBG0) {
                Scl_d_reg.mapoffset1 &= 0xff0f;
                mapoffset = &Scl_d_reg.mapoffset1;
                shift = 4;
                map = &Scl_d_reg.rotmap[8];

                temp = scfg->platesize;
                temp = (temp << 12) & 0x3000;
                Scl_d_reg.platesize &= 0xcfff;
                Scl_d_reg.platesize |= temp;

                temp = scfg->mapover;
                temp = (temp << 14) & 0xc000;
                Scl_d_reg.platesize &= 0x3fff;
                Scl_d_reg.platesize |= temp;
            }
        }
        break;
    case SCL_RBG1:
        if ((SclRa == SCL_RBG0) && (SclRb == SCL_RBG1)) {
            Scl_s_reg.dispenbl &= 0xffdf;
            if (scfg->dispenbl)
                Scl_s_reg.dispenbl |= 0x0020;

            temp = scfg->charsize;
            temp &= 0x0001;
            Scl_d_reg.charcontrl0 &= 0xfffe;
            Scl_d_reg.charcontrl0 |= temp;

            Scl_d_reg.patnamecontrl[0] = scfg->patnamecontrl;

            temp = scfg->pnamesize;
            temp = (temp << 15) & 0x8000;
            Scl_d_reg.patnamecontrl[0] &= 0x7fff;
            Scl_d_reg.patnamecontrl[0] |= temp;

            Scl_d_reg.patnamecontrl[0] &= 0xbfff;
            Scl_d_reg.patnamecontrl[0] |= flip;

            temp = scfg->platesize;
            temp = (temp << 12) & 0x3000;
            Scl_d_reg.platesize &= 0xcfff;
            Scl_d_reg.platesize |= temp;

            temp = scfg->mapover;
            temp = (temp << 14) & 0xc000;
            Scl_d_reg.platesize &= 0x3fff;
            Scl_d_reg.platesize |= temp;

            temp = scfg->coltype;
            temp = (temp << 4) & 0x0070;
            Scl_d_reg.charcontrl0 &= 0xff8f;
            Scl_d_reg.charcontrl0 |= temp;

            temp = SCL_CELL;
            temp = (temp << 1) & 0x0002;
            Scl_d_reg.charcontrl0 &= 0xfffd;
            Scl_d_reg.charcontrl0 |= temp;

            max = 8;
            Scl_d_reg.mapoffset1 &= 0xff0f;
            mapoffset = &Scl_d_reg.mapoffset1;
            shift = 4;
            map = &Scl_d_reg.rotmap[8];
        }
        break;
    }

    if (scfg->datatype == SCL_BITMAP) {
        mapoffsetW = ((scfg->plate_addr[0] - SCL_VDP2_VRAM) / 0x20000) & 0x0007;
        *mapoffset |= mapoffsetW << shift;
    } else {
        if (scfg->pnamesize == 1) {
            if (scfg->charsize == 0) {
                boundary = 0x2000;
            } else {
                boundary = 0x800;
            }
        } else {
            if (scfg->charsize == 0) {
                boundary = 0x4000;
            } else {
                boundary = 0x1000;
            }
        }
        mapoffsetW =
            (0x01c0 & ((scfg->plate_addr[0] - SCL_VDP2_VRAM) / boundary)) >> 6;
        *mapoffset |= mapoffsetW << shift;
    }

    for (i = 0; i < max; i++) {
        map[i] =
            (0x003f & ((scfg->plate_addr[i * 2] - SCL_VDP2_VRAM) / boundary));
        temp = (0x003f &
                ((scfg->plate_addr[i * 2 + 1] - SCL_VDP2_VRAM) / boundary))
               << 8;

        map[i] |= (temp & 0x3f00);
    }
    if (map2) {
        *mapoffset &= 0x000f;
        *mapoffset |= *mapoffset << shift2;

        for (i = 0; i < max; i++) {
            map2[i] =
                (0x003f &
                 ((scfg->plate_addr[16 + (i * 2)] - SCL_VDP2_VRAM) / boundary));
            temp = (0x003f &
                    ((scfg->plate_addr[16 + (i * 2 + 1)] - SCL_VDP2_VRAM) /
                     boundary))
                   << 8;
            map2[i] |= (temp & 0x3f00);
        }
    }
    if (SclProcess == 0)
        SclProcess = 1;
}

// func_0602A654
void SCL_SetCycleTable(Uint16* tp) {
    Uint16 i;
    for (i = 0; i < 8; i++) {
        Scl_s_reg.vramcyc[i] = tp[i];
    }
}

// func_0602A6DC
void SCL_FreeColRam(Uint32 Surface) {
    Uint32 work;
    Uint8 i;

    work = Surface ^ 0xffffffff;

    for (i = 0; i < 8; i++) {
        SclColRamAlloc256[i] &= work;
    }
    SclColRamAlloc2048[0] &= work;
}

// func_0602A778
Uint32 SCL_AllocColRam(Uint32 Surface, Uint32 NumOfColors, Uint8 transparent) {
    Uint8 Max256 = 0;
    Uint32 i;
    Uint32 Size256 = 0;

    SCL_FreeColRam(Surface);

    if (SclColRamAlloc2048[0] != 0)
        return (Uint32)NULL;

    switch (SCL_GetColRamMode()) {
    case SCL_CRM15_1024:
        if (1024 < NumOfColors)
            return (Uint32)NULL;
        Max256 = 4;
        Size256 = 512;
        break;
    case SCL_CRM15_2048:
        if (2048 < NumOfColors)
            return (Uint32)NULL;
        Max256 = 8;
        Size256 = 512;
        break;
    case SCL_CRM24_1024:
        if (1024 < NumOfColors)
            return (Uint32)NULL;
        Max256 = 4;
        Size256 = 1024;
        break;
    }

    if (256 >= NumOfColors) {
        for (i = 0; i < Max256; i++) {
            if (SclColRamAlloc256[i] == 0) {
                SclColRamAlloc256[i] = Surface;
                SCL_SetColRamOffset(Surface, i, transparent);
                return SCL_COLRAM_ADDR + (Size256 * i);
            }
        }
    } else {
        for (i = 0; i < Max256; i++)
            if (SclColRamAlloc256[i] != 0)
                return (Uint32)NULL;
        SclColRamAlloc2048[0] = Surface;
        SCL_SetColRamOffset(Surface, 0, transparent);
        return SCL_COLRAM_ADDR;
    }
}

// func_0602A964
static Fixed32 Fsin(Fixed32 a) {
    Uint16 sign;
    Fixed32 val;

    sign = 0;
    if (a & 0x80000000) {
        sign = 1;
        a = -a;
    }
    a = a % FIXED(360);

    if (FIXED(270) <= a) {
        val = -fsin(FIXED(360) - a);
    } else if (FIXED(180) <= a) {
        val = -fsin(a - FIXED(180));
    } else if (FIXED(90) <= a) {
        val = fsin(FIXED(180) - a);
    } else {
        val = fsin(a);
    }

    if (val == 0x0000ffff)
        val = FIXED(1);

    if (sign)
        val = -val;
    return val;
}

// func_0602AA84
static Fixed32 Fcos(Fixed32 a) {
    Uint16 sign;
    Fixed32 val;

    sign = 0;
    if (a & 0x80000000) {
        sign = 0;
        a = -a;
    }
    a = a % FIXED(360);

    if (a == 0)
        return FIXED(1);

    if (FIXED(270) <= a) {
        val = fcos(FIXED(360) - a);
    } else if (FIXED(180) < a) {
        val = -fcos(a - FIXED(180));
    } else if (FIXED(180) == a) {
        val = -FIXED(1);
    } else if (FIXED(90) <= a) {
        val = -fcos(FIXED(180) - a);
    } else {
        val = fcos(a);
    }
    return val;
}

extern Fixed32 currentMatrix[2][9];

// SCL_Rotate, but apparently edited by the devs to remove unused
// dimensions for space saving reasons?
// func_0602AB9C
void SCL_Rotate(Fixed32 xy, Fixed32 z, Fixed32 disp) {
    Uint16 TbNum;

    switch (SclCurSclNum) {
    case SCL_RBG_TB_A:
        TbNum = 0;
        break;
    case SCL_RBG_TB_B:
        TbNum = 1;
        break;
    default:
        return;
        break;
    }

    currentMatrix[TbNum][0] = FIXED(1);
    currentMatrix[TbNum][1] = FIXED(0);
    currentMatrix[TbNum][2] = FIXED(0);
    currentMatrix[TbNum][3] = FIXED(0);
    currentMatrix[TbNum][4] = FIXED(1);
    currentMatrix[TbNum][5] = FIXED(0);
    currentMatrix[TbNum][6] = FIXED(0);
    currentMatrix[TbNum][7] = FIXED(0);
    currentMatrix[TbNum][8] = FIXED(1);

    if (SclRbgKtbAddr[TbNum]) {
        SclRotateXy[TbNum] += xy;
    } else {
        SclRotateXy[TbNum] = 0;
    }

    SclRotateZ[TbNum] += z;

    if (!SclRotateXy[TbNum] && xy) {
        switch (SclCurSclNum) {
        case SCL_RBG_TB_A:
            Scl_r_reg.k_contrl &= 0xff00;
            break;
        case SCL_RBG_TB_B:
            Scl_r_reg.k_contrl &= 0x00ff;
            break;
        }
    }

    if (disp)
        SCL_RotateZD(disp);

    if (SclRbgKtbOffset[TbNum] && SclRotateDisp[TbNum]) {
        SclRotateXy[TbNum] = 0;
    }

    if (SclRotateXy[TbNum] || SclRotateMoveZ[TbNum]) {
        currentMatrix[TbNum][0] = SclRotregBuff[TbNum].zoom.x;
        currentMatrix[TbNum][4] = SclRotregBuff[TbNum].zoom.y;
    } else if ((TbNum == 0 && (Scl_r_reg.k_contrl & 0x00ff)) ||
               (TbNum == 1 && (Scl_r_reg.k_contrl & 0xff00))) {
        currentMatrix[TbNum][0] = SclRotregBuff[TbNum].zoom.x;
        currentMatrix[TbNum][4] = SclRotregBuff[TbNum].zoom.y;
        SclRotregBuff[TbNum].matrix_a = SclRotregBuff[TbNum].zoom.x;
        SclRotregBuff[TbNum].matrix_e = SclRotregBuff[TbNum].zoom.y;
    }

#if 0
	if(SclRotateZ[TbNum])	SCL_RotateZ(SclRotateZ[TbNum]);

	if( SclRotateXy[TbNum] || SclRotateMoveZ[TbNum] ) {
		if(SclRotXySw[TbNum]==0 || SclRbgKtbOffset[TbNum])
			SCL_RotateX(SclRotateXy[TbNum]);
		else	SCL_RotateY(SclRotateXy[TbNum]);
	}
#endif
}

extern Fixed32 SclCsx[2], SclCsy[2];

// func_0602B024
void SCL_RotateZD(Fixed32 r) {
    Uint16 TbNum;

    switch (SclCurSclNum) {
    case SCL_RBG_TB_A:
        TbNum = 0;
        break;
    case SCL_RBG_TB_B:
        TbNum = 1;
        break;
    default:
        return;
        break;
    }

    if (SclRbgKtbOffset[TbNum] &&
        (SclRotateXy[TbNum] || SclRotateMoveZ[TbNum])) {
        SclRotateDisp[TbNum] = 0;
        return;
    }

    SclRotateDisp[TbNum] += r;

    if (SclRotateDisp[TbNum] >= FIXED(360))
        SclRotateDisp[TbNum] -= FIXED(360);
    if (SclRotateDisp[TbNum] < FIXED(0))
        SclRotateDisp[TbNum] += FIXED(360);

    SclRotregBuff[TbNum].screenst.x =
        SclCsx[TbNum] - MUL_FIXED(Fcos(SclRotateDisp[TbNum]), SclCsx[TbNum]) -
        MUL_FIXED((-Fsin(SclRotateDisp[TbNum])), SclCsy[TbNum]);
    SclRotregBuff[TbNum].screenst.y =
        SclCsy[TbNum] - MUL_FIXED(Fsin(SclRotateDisp[TbNum]), SclCsx[TbNum]) -
        MUL_FIXED((Fcos(SclRotateDisp[TbNum])), SclCsy[TbNum]);
    SclRotregBuff[TbNum].screenst.z = FIXED(0);
    SclRotregBuff[TbNum].screendlt.x = -Fsin(SclRotateDisp[TbNum]);
    SclRotregBuff[TbNum].screendlt.y = Fcos(SclRotateDisp[TbNum]);
    SclRotregBuff[TbNum].delta.x = Fcos(SclRotateDisp[TbNum]);
    SclRotregBuff[TbNum].delta.y = Fsin(SclRotateDisp[TbNum]);
}

void SCL_SetColRam(Uint32 Object, Uint32 Index, Uint32 num, void* Color) {
    Uint32 *color32, *ram32;
    Uint16 *color16, *ram16;

    if (SCL_GetColRamMode() == 2) {
        color32 = (Uint32*)Color;
        ram32 = (Uint32*)((Uint32)SCL_COLRAM_ADDR +
                          (SCL_GetColRamOffset(Object) * 0x400)) +
                Index;

        if (num == 1) {
            ram32[0] = color32[0];
        } else {
            SCL_Memcpyw(ram32, color32, num * 4);
        }
    } else {
        color16 = (Uint16*)Color;
        ram16 = (Uint16*)((Uint32)SCL_COLRAM_ADDR +
                          (SCL_GetColRamOffset(Object) * 0x200)) +
                Index;

        if (num == 1) {
            ram16[0] = color16[0];
        } else {
            SCL_Memcpyw(ram16, color16, num * 2);
        }
    }
}

extern Uint32 SclLineColRamOffset;

// func_0602B52C
void SCL_SetColRamOffset(Uint32 Object, Uint32 Offset, Uint8 transparent) {
    if (Object & SCL_SPR)
        SCL_SET_SPCAOS(Offset);

    if ((Object & SCL_NBG0) || (Object & SCL_RBG1)) {
        SCL_SET_N0CAOS(Offset);
        if (transparent)
            Scl_s_reg.dispenbl |= 0x0100;
        else
            Scl_s_reg.dispenbl &= 0xfeff;
    }

    if ((Object & SCL_NBG1) || (Object & SCL_EXBG)) {
        SCL_SET_N1CAOS(Offset);
        if (transparent)
            Scl_s_reg.dispenbl |= 0x0200;
        else
            Scl_s_reg.dispenbl &= 0xfdff;
    }

    if (Object & SCL_NBG2) {
        SCL_SET_N2CAOS(Offset);
        if (transparent)
            Scl_s_reg.dispenbl |= 0x0400;
        else
            Scl_s_reg.dispenbl &= 0xfbff;
    }

    if (Object & SCL_NBG3) {
        SCL_SET_N3CAOS(Offset);
        if (transparent)
            Scl_s_reg.dispenbl |= 0x0800;
        else
            Scl_s_reg.dispenbl &= 0xf7ff;
    }

    if (Object & SCL_RBG0) {
        SCL_SET_R0CAOS(Offset);
        if (transparent)
            Scl_s_reg.dispenbl |= 0x1000;
        else
            Scl_s_reg.dispenbl &= 0xefff;
    }

    if (Object & SCL_LNCL) {
        SclLineColRamOffset = Offset;
    }
}

extern Uint32 SclLineColRamOffset;
// func_0602B85C
Uint32 SCL_GetColRamOffset(Uint32 Object) {
    switch (Object) {
    case SCL_SPR:
        return SCL_GET_SPCAOS();
        break;
    case SCL_NBG0:
    case SCL_RBG1:
        return SCL_GET_N0CAOS();
        break;
    case SCL_NBG1:
    case SCL_EXBG:
        return SCL_GET_N1CAOS();
        break;
    case SCL_NBG2:
        return SCL_GET_N2CAOS();
        break;
    case SCL_NBG3:
        return SCL_GET_N3CAOS();
        break;
    case SCL_RBG0:
        return SCL_GET_R0CAOS();
        break;
    case SCL_LNCL:
        return SclLineColRamOffset;
        break;
    default:
        break;
    }
}

const u16 pad_602B9B2 = 0;
