#include "../sattypes.h"
#include "../inc_asm.h"

#define _SPR2_
#include "spr.h"

extern Uint16 EraseData;
extern Uint16 EraseLeftX;
extern Uint16 EraseTopY;
extern Uint16 EraseRightX;
extern Uint16 EraseBotY;

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
extern SprSpCmd* s_chainLastCmd;
extern Vaddr s_chainTopCmdR;

Vaddr flushDrawPrtyBlock(int entryCnt, SprDrawPrtyBlk* mstZBlk,
                         SprDrawPrtyBlk* slvZBlk, SprSpCmd** rtnChainLastCmd);

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

// func_06022A48
void SPR_2CloseCommand(void) {
    SprSpCmd* spCmd;

    SPR_2FlushDrawPrty();

    spCmd = SpCmdTbl + SpCmdNo;
    spCmd->control = CTRL_END;
    topSpCmd->control = CTRL_SKIP | JUMP_ASSIGN;
    if (displayInterval == 0xffff) {
        SpCmdNo = 0;

        spCmd = SpCmdTbl + SpCmdNo++;
        spCmd->control = JUMP_NEXT | FUNC_LCOORD;
        spCmd->ax = 0;
        spCmd->ay = 0;

        spCmd = SpCmdTbl + SpCmdNo++;
        spCmd->control = JUMP_NEXT | ZOOM_NOPOINT | DIR_NOREV | FUNC_POLYGON;
        spCmd->drawMode = ECDSPD_DISABLE | COLOR_5 | COMPO_REP;
        spCmd->color = eraseData;

        spCmd->ax = EraseLeftX;
        spCmd->ay = EraseTopY;
        spCmd->bx = EraseRightX;
        spCmd->by = EraseTopY;
        spCmd->cx = EraseRightX;
        spCmd->cy = EraseBotY;
        spCmd->dx = EraseLeftX;
        spCmd->dy = EraseBotY;
        spCmd->grshAddr = 0;

        spCmd = SpCmdTbl + SpCmdNo++;
        spCmd->control = JUMP_NEXT | FUNC_LCOORD;
        spCmd->ax = SpLCoordX;
        spCmd->ay = SpLCoordY;

        spCmd = SpCmdTbl + SpCmdNo;
        spCmd->control = CTRL_SKIP | JUMP_ASSIGN;
        spCmd->link = SpCmdTblR + SP_SYS_CMD_MAX * 4;
        topSpCmd->link = SpCmdTblR;
    } else {
        topSpCmd->link = SpCmdTblR + SP_SYS_CMD_MAX * 4;
    }

    if (SpGourTblMax) {
        DMA_ScuMemCopy(crGourTbl, SpGourTbl, sizeof(SprGourTbl) * SpGourTblMax);
        DMA_ScuResult();
    }
}

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

// func_06022E8C
void SPR_2FlushDrawPrtyBlock(void) {
    extern void SlaveFlushDrawPrtyBlock(void);
    SprSpCmd *spCmd, *chainLastCmd;
    Vaddr chainTopCmdR;
    int wCmdNo;

    SPR_RunSlaveSH((PARA_RTN*)SlaveFlushDrawPrtyBlock, 0);

    chainTopCmdR = flushDrawPrtyBlock(
        SpDrawPrtyBlkMax - (SpDrawPrtyBlkMax >> 1),
        SpMstDrawPrtyBlk + (SpDrawPrtyBlkMax >> 1),
        SpSlvDrawPrtyBlk + (SpDrawPrtyBlkMax >> 1), &chainLastCmd);

    SPR_WaitEndSlaveSH();

    if (s_chainLastCmd) {
        s_chainLastCmd->link = chainTopCmdR;
        chainTopCmdR = s_chainTopCmdR;
        if (chainLastCmd == 0)
            chainLastCmd = s_chainLastCmd;
    }

    if (chainLastCmd) {
        wCmdNo = SpCmdNo;

        spCmd = SpCmdTbl + SpCmdNo - 1;
        spCmd->control |= JUMP_ASSIGN;
        spCmd->link = chainTopCmdR;

        SpCmdNo = SpCmdNo + SpMstCmdPos + SpSlvCmdPos;
        chainLastCmd->link = SpCmdTblR + (SpCmdNo << 2);

        spCmd = SpCmdTbl + SpCmdNo++;
        spCmd->control = CTRL_SKIP | JUMP_NEXT;

        if (SpMstCmdPos) {
            spCmd = SpCmdTbl + wCmdNo;
            DMA_ScuMemCopy(spCmd, SpMstCmd, sizeof(SprSpCmd) * SpMstCmdPos);
            DMA_ScuResult();
        }
        if (SpSlvCmdPos) {
            spCmd = spCmd + SpMstCmdPos;
            DMA_ScuMemCopy(spCmd, SpSlvCmd, sizeof(SprSpCmd) * SpSlvCmdPos);
            DMA_ScuResult();
        }
    }
    mstCmd = SpMstCmd;
    slvCmd = SpSlvCmd;
    SpMstCmdPos = 0;
    SpSlvCmdPos = 0;
}

// func_060230B8 
void SlaveFlushDrawPrtyBlock(void) {
    s_chainTopCmdR = flushDrawPrtyBlock(SpDrawPrtyBlkMax >> 1, SpMstDrawPrtyBlk,
                                        SpSlvDrawPrtyBlk, &s_chainLastCmd);
}
