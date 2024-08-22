// SPDX-License-Identifier: AGPL-3.0-only
#include "sattypes.h"
#include "inc_asm.h"

#define _SPR2_
#include "spr.h"

extern Uint16 SpEraseLTPoint;
extern Uint16 SpEraseRBPoint;
extern Uint16 EraseData;
extern Uint16 EraseLeftX;
extern Uint16 EraseTopY;
extern Uint16 EraseRightX;
extern Uint16 EraseBotY;
extern Uint16 BitWidth;

extern XyInt scrSize[8];

// SEGA_SPR.A

// func_060218E8
void SPR_SetTvMode(Uint16 mode, Uint16 screenSize, Uint16 doubleInterlace) {

    SpTvMode = 0x0007 & mode;
    SPR_WRITE_REG(SPR_W_TVMR, SpTvMode);
    if (screenSize > SPR_TV_704X240)
        screenSize = SPR_TV_320X224;
    SpScreenX = scrSize[screenSize].x;
    SpScreenY = scrSize[screenSize].y;
    if (doubleInterlace == ON)
        SpScreenY <<= 1;

    if ((mode == SPR_TV_HIRESO) || (mode == SPR_TV_ROT8))
        BitWidth = 1;
    else
        BitWidth = 0;

    if (doubleInterlace)
        SpDie = SPR_FBCR_DIE;
    else
        SpDie = 0;
    SpDil = 0;
}

// func_06021A58
void SPR_GetStatus(SprSpStatus* spStatus) {

    spStatus->frameChgMode = SpFrameChgMode;
    spStatus->frameEraseMode = SpFrameEraseMode;
    spStatus->vbInterval = VBInterval;
    spStatus->eraseData = EraseData;
    spStatus->eraseLeftX = EraseLeftX;
    spStatus->eraseTopY = EraseTopY;
    spStatus->eraseRightX = EraseRightX;
    spStatus->eraseBotY = EraseBotY;
}

// func_06021AE8
void SPR_SetEraseData(
    Uint16 eraseData, Uint16 leftX, Uint16 topY, Uint16 rightX, Uint16 botY) {

    EraseData = eraseData;
    EraseLeftX = leftX;
    EraseTopY = topY;
    EraseRightX = rightX;
    EraseBotY = botY;

    SPR_WRITE_REG(SPR_W_EWDR, eraseData);

    if (BitWidth)
        leftX >>= 4;
    else
        leftX >>= 3;
    if (SpDie)
        topY >>= 1;
    SpEraseLTPoint = (leftX << 9) + topY;
    SPR_WRITE_REG(SPR_W_EWLR, SpEraseLTPoint);

    rightX++;
    if (BitWidth)
        rightX >>= 4;
    else
        rightX >>= 3;
    if (SpDie)
        botY >>= 1;
    SpEraseRBPoint = (rightX << 9) + botY;
    SPR_WRITE_REG(SPR_W_EWRR, SpEraseRBPoint);
}

// func_06022060
void SPR_WaitDrawEnd(void) {
    while ((SPR_READ_REG(SPR_R_EDSR) & 0x0002) == 0)
        ;
}

// func_06022088
void SPR_SetEosMode(Sint32 eosFlag) {
    if (eosFlag)
        SpFbcrMode = SPR_FBCR_EOS;
    else
        SpFbcrMode = 0;
}

#define VRAM_GRAN_MAX 16384
#define SP_SYS_CMD_MAX 4

#define GetSpCmdArea(CMD)                                                      \
    SPR_2SetDrawPrty(drawPrty);                                                \
    CMD = mstCmd++;                                                            \
    SpMstCmdPos++;

#define SetCharPara(CMD)                                                       \
    CMD->charAddr = SpCharTbl[charNo].addr;                                    \
    CMD->charSize = SpCharTbl[charNo].xySize;                                  \
    drawMode = (drawMode & ~DRAW_COLOR) | SpCharTbl[charNo].mode;

#define SetDrawPara(CMD)                                                       \
    CMD->drawMode = drawMode;                                                  \
    if ((drawMode & DRAW_COLOR) == COLOR_1)                                    \
        CMD->color = vramInfo.lookupTblR + color * 4;                          \
    else                                                                       \
        CMD->color = color;

#define SetDrawParaTex(CMD)                                                    \
    CMD->drawMode = drawMode;                                                  \
    if (color == 0xffff)                                                       \
        color = SpCharTbl[charNo].color;                                       \
    if ((drawMode & DRAW_COLOR) == COLOR_1)                                    \
        CMD->color = vramInfo.lookupTblR + color * 4;                          \
    else                                                                       \
        CMD->color = color;

#define SetGourPara(CMD)                                                       \
    if (gourTblNo == NO_GOUR)                                                  \
        CMD->grshAddr = 0;                                                     \
    else                                                                       \
        CMD->grshAddr = crGourTblR + gourTblNo;

struct VramInfo {
    Uint16 cmdTblCnt;
    Uint16 cmdTblSize;
    Uint16 gourTblCnt;
    Uint16 gourTblSize;
    Uint16 lookupTblCnt;
    Uint16 lookupTblSize;
    SprLookupTbl* lookupTbl;
    Vaddr lookupTblR;
    Uint8* blockPool;
    Uint16 blockPoolSize;
};

struct VramTbl {
    SprSpCmd* cmdTbl;
    Vaddr cmdTblR;
    SprGourTbl* gourTbl;
    Vaddr gourTblR;
};

struct NullBlock {
    struct NullBlock* next;
    Uint16 size;
};

typedef struct NullBlock NullBlock;

extern Sint32 Sp2OpenFlag;
extern Sint32 SpLCoordX;
extern Sint32 SpLCoordY;
extern Sint32 SpScreenX;
extern Sint32 SpScreenY;
extern SprCharTbl* SpCharTbl;
extern Sint32 SpCharMax;
extern Sint32 SpDrawPrtyBlkMax;
extern Sint32 SpCmdNo;
extern Sint32 SpDrawPrtyProcFlag;
extern SprDrawPrtyBlk* SpDrawPrtyBlk;
extern SprSpCmd* SpCmdTbl;
extern Vaddr SpCmdTblR;
extern SprDrawPrtyBlk* SpMstDrawPrtyBlk;
extern SprSpCmd* SpMstCmd;
extern int SpMstCmdPos;
extern SprDrawPrtyBlk* SpSlvDrawPrtyBlk;
extern SprSpCmd* SpSlvCmd;
extern int SpSlvCmdPos;
extern Vaddr SpLookupTblR;
extern Sint32 SpGourTblMax;
extern SprGourTbl* SpGourTbl;

extern SprSpCmd* mstCmd;
extern SprSpCmd* slvCmd;

extern Uint8* VRAM;
extern Sint32 vramSW;
extern SprSpCmd* topSpCmd;
extern struct VramInfo vramInfo;
extern struct VramTbl vramTbl[2];
extern NullBlock* nullBlockTop;
extern Uint16 eraseData;
extern Uint16 displayInterval;
extern Vaddr crGourTblR;
extern SprGourTbl* crGourTbl;

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60220B4, func_060220B4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60220EC, func_060220EC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022138, func_06022138);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022148, func_06022148);

// func_06022164
void SPR_2Initial(Spr2WorkArea* workArea) {
    SPR_InitSlaveSH();
    SPR_2Initial2(workArea);
}

// func_06022194
void SPR_2Initial2(Spr2WorkArea* workArea) {
    Uint16 w;
    Uint8* wp;
    Uint16 gourTblCnt, cmdTblCnt;

    SpCharMax = workArea->charMax;
    SpCharTbl = workArea->charTbl;

    gourTblCnt = (workArea->gourTblMax + 3) & 0xfffc;

    SPR_Initial(&VRAM);

    cmdTblCnt = workArea->commandMax + SP_SYS_CMD_MAX;
    vramInfo.cmdTblCnt = cmdTblCnt;
    vramInfo.cmdTblSize = cmdTblCnt;
    vramInfo.gourTblCnt = gourTblCnt;
    vramInfo.gourTblSize = gourTblCnt / 4;
    vramInfo.lookupTblCnt = workArea->lookupTblMax;
    vramInfo.lookupTblSize = workArea->lookupTblMax;
    w = (vramInfo.cmdTblSize + vramInfo.gourTblSize) * 2 +
        vramInfo.lookupTblSize + 1;
    vramInfo.blockPoolSize = VRAM_GRAN_MAX - w;

    vramTbl[0].cmdTbl = (SprSpCmd*)VRAM + 1;
    vramTbl[0].gourTbl = (SprGourTbl*)(vramTbl[0].cmdTbl + vramInfo.cmdTblSize);
    vramTbl[1].cmdTbl =
        (SprSpCmd*)(vramTbl[0].gourTbl + vramInfo.gourTblSize * 4);
    vramTbl[1].gourTbl = (SprGourTbl*)(vramTbl[1].cmdTbl + vramInfo.cmdTblSize);
    vramInfo.lookupTbl =
        (SprLookupTbl*)(vramTbl[1].gourTbl + vramInfo.gourTblSize * 4);
    wp = (Uint8*)(vramInfo.lookupTbl + vramInfo.lookupTblSize);
    vramInfo.blockPool = wp;

    vramTbl[0].cmdTblR = 4;
    vramTbl[0].gourTblR = vramTbl[0].cmdTblR + vramInfo.cmdTblSize * 4;
    vramTbl[1].cmdTblR = vramTbl[0].gourTblR + vramInfo.gourTblSize * 4;
    vramTbl[1].gourTblR = vramTbl[1].cmdTblR + vramInfo.cmdTblSize * 4;
    vramInfo.lookupTblR = vramTbl[1].gourTblR + vramInfo.gourTblSize * 4;

    SPR_2ClrAllChar();

    topSpCmd = (SprSpCmd*)VRAM;
    topSpCmd->control = CTRL_END;

    SpMstCmd = workArea->mstCmd;
    SpSlvCmd = workArea->slvCmd;
    SpMstDrawPrtyBlk = workArea->mstDrawPrtyBlk;
    SpSlvDrawPrtyBlk = workArea->slvDrawPrtyBlk;
    SpDrawPrtyBlkMax = workArea->drawPrtyBlkMax;
    SpGourTblMax = workArea->gourTblMax;
    SpGourTbl = workArea->gourTbl;
    SpDrawPrtyProcFlag = 0;
    memset(SpMstDrawPrtyBlk, 0xff, sizeof(SprDrawPrtyBlk) * SpDrawPrtyBlkMax);
    if (SpSlvDrawPrtyBlk)
        memset(
            SpSlvDrawPrtyBlk, 0xff, sizeof(SprDrawPrtyBlk) * SpDrawPrtyBlkMax);
    SpLookupTblR = vramInfo.lookupTblR;

    vramSW = 0;
    SpCmdNo = SP_SYS_CMD_MAX;
    SPR_2FrameEraseData(RGB16_COLOR(0, 0, 0));
    SpLCoordX = SpLCoordY = 0;
}

// func_06022514
void SPR_2SetTvMode(Uint16 mode, Uint16 screenSize, Uint16 doubleInterlace) {
    SPR_SetTvMode(mode, screenSize, doubleInterlace);
}

// func_06022588
void SPR_2FrameChgIntr(Uint16 interval) {
    extern void SCL_SetFrameInterval(Uint16 count);
    displayInterval = interval;
    SCL_SetFrameInterval(interval);
}

// func_060225C4
void SPR_2FrameEraseData(Uint16 rgbColor) {
    SPR_SetEraseData(rgbColor, 0, 0, SpScreenX - 1, SpScreenY - 1);
    eraseData = rgbColor;
}

// func_0602262C
void SPR_2SetGourTbl(Uint16 gourTblNo, SprGourTbl* gourTbl) {
    memcpy(&SpGourTbl[gourTblNo], gourTbl, sizeof(SprGourTbl));
}

// func_06022678
void SPR_2SetLookupTbl(Uint16 lookupTblNo, SprLookupTbl* lookupTbl) {
    SprLookupTbl* dLookupTbl;
    dLookupTbl = vramInfo.lookupTbl + lookupTblNo;
    DMA_ScuMemCopy(dLookupTbl, lookupTbl, sizeof(SprLookupTbl));
    DMA_ScuResult();
}

// func_060226D0
void SPR_2ClrAllChar(void) {
    Sint32 i;
    for (i = 0; i < SpCharMax; i++)
        SpCharTbl[i].addr = 0;

    if (vramInfo.blockPoolSize) {
        nullBlockTop = (struct NullBlock*)vramInfo.blockPool;
        nullBlockTop->next = 0;
        nullBlockTop->size = vramInfo.blockPoolSize;
    } else
        nullBlockTop = 0;
}

// func_06022768
Uint16 SPR_2GourTblNoToVram(Uint16 gourTblNo) {
    return vramTbl[vramSW].gourTblR + gourTblNo;
}

// func_060227AC
Uint16 SPR_2LookupTblNoToVram(Uint16 lookupTblNo) {
    return vramInfo.lookupTblR + lookupTblNo * 4;
}

// func_060227E4
Uint16 SPR_2CharNoToVram(Uint16 charNo) { return SpCharTbl[charNo].addr; }

// func_0602281C
void SPR_2GetAreaSizeInfo(SprAreaSize* areaSizeInfo) {
    NullBlock* nullBlock;
    Uint16 nullBlkMaxSize, totalNullBlkCount;
    nullBlock = nullBlockTop;
    nullBlkMaxSize = 0;
    totalNullBlkCount = 0;
    while (nullBlock) {
        if (nullBlkMaxSize < nullBlock->size)
            nullBlkMaxSize = nullBlock->size;
        totalNullBlkCount += nullBlock->size;
        nullBlock = nullBlock->next;
    }
    areaSizeInfo->charRemainBlkCount = totalNullBlkCount;
    areaSizeInfo->charNullBlkMaxSize = nullBlkMaxSize;
    areaSizeInfo->commandMax = vramInfo.cmdTblCnt;
    areaSizeInfo->gourTblMax = vramInfo.gourTblCnt;
    areaSizeInfo->lookupTblMax = vramInfo.lookupTblCnt;
    areaSizeInfo->charMax = SpCharMax;
    areaSizeInfo->drawPrtyBlkMax = SpDrawPrtyBlkMax;
    areaSizeInfo->useCommandCount = SpCmdNo;
}

// func_0602292C
void SPR_2OpenCommand(Uint16 drawPrtyFlag) {
    SprSpCmd* spCmd;
    Sp2OpenFlag = 1;
    vramSW ^= 1;
    SpCmdNo = SP_SYS_CMD_MAX;
    SpDrawPrtyProcFlag = drawPrtyFlag;
    SpCmdTbl = vramTbl[vramSW].cmdTbl;
    SpCmdTblR = vramTbl[vramSW].cmdTblR;
    crGourTblR = vramTbl[vramSW].gourTblR;
    crGourTbl = vramTbl[vramSW].gourTbl;
    spCmd = SpCmdTbl + SpCmdNo;
    spCmd->control = CTRL_SKIP;
    SpCmdNo++;
    mstCmd = SpMstCmd;
    slvCmd = SpSlvCmd;
    SpMstCmdPos = 0;
    SpSlvCmdPos = 0;
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022A48, func_06022A48);

// func_06022C7C
void SPR_2FlushDrawPrty(void) { SPR_2FlushDrawPrtyBlock(); }

// func_06022C9C
void SPR_2LocalCoord(Sint32 drawPrty, XyInt* xy) {
    SprSpCmd* spCmd;
    GetSpCmdArea(spCmd);
    spCmd->control = JUMP_ASSIGN | FUNC_LCOORD;
    spCmd->ax = xy->x;
    spCmd->ay = xy->y;

    SpLCoordX = xy->x;
    SpLCoordY = xy->y;
}

// func_06022D28
void SPR_2SysClip(Sint32 drawPrty, XyInt* xy) {
    SprSpCmd* spCmd;
    GetSpCmdArea(spCmd);
    spCmd->control = JUMP_ASSIGN | FUNC_SCLIP;
    spCmd->cx = xy->x;
    spCmd->cy = xy->y;
}

// func_06022D98
void SPR_2UserClip(Sint32 drawPrty, XyInt xy[2]) {
    SprSpCmd* spCmd;
    GetSpCmdArea(spCmd);
    spCmd->control = JUMP_ASSIGN | FUNC_UCLIP;
    spCmd->ax = xy[0].x;
    spCmd->ay = xy[0].y;
    spCmd->cx = xy[1].x;
    spCmd->cy = xy[1].y;
}

// func_06022E2C
void SPR_2Cmd(Sint32 drawPrty, SprSpCmd* pSpCmd) {
    SprSpCmd* spCmd;
    GetSpCmdArea(spCmd);
    sprMemCpyW(spCmd, pSpCmd, 16);
}

// _SPR_2FlushDrawPrtyBlock
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022E8C, func_06022E8C);

// SlaveFlushDrawPrtyBlock
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60230B8, func_060230B8);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023108, func_06023108);

// SPR_RunSlaveSH
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023114, func_06023114);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023144, func_06023144);

// flushDrawPrtyBlock
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60231C0, func_060231C0);

INCLUDE_ASM("asm/saturn/zero/data", d6023394, d_06023394);
