#include "../sattypes.h"
#include "../inc_asm.h"

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

static inline void set_sr(register Uint32 sr) {
    __asm__ volatile("ldc	%0, sr" : : "r"(sr));
}

static inline Uint32 get_sr(void) {
    Uint32 sr;
    __asm__ volatile("stc	sr, %0" : "=r"(sr));
    return sr;
}

static inline Uint32 get_imask(void) {
    Uint32 imask = (get_sr() & 0x000000F0) >> 4;
    return imask;
}

static inline void set_imask(register Uint32 imask) {
    Uint32 sr = get_sr();

    sr &= ~0x000000F0;
    sr |= imask << 4;
    set_sr(sr);
}

// func_060217EC
void SPR_Initial(Uint8** VRAM) {
    int iMask;
    iMask = get_imask();
    set_imask(15);
    SPR_SetEosMode(0);
    SPR_SetTvMode(SPR_TV_NORMAL, SPR_TV_320X224, 0);
    SPR_WRITE_REG(SPR_W_FBCR, SPR_FBCR_AUTO | SpFbcrMode);
    SPR_WRITE_REG(SPR_W_PTMR, 0x0002);
    SPR_WRITE_REG(SPR_W_EWDR, RGB16_COLOR(0, 0, 0));
    SPR_WRITE_REG(SPR_W_EWLR, 0x0000);
    SPR_WRITE_REG(SPR_W_EWRR, 0xffff);

    SPR_SetEraseData(RGB16_COLOR(0, 0, 0), 0, 0, SpScreenX - 1, SpScreenY - 1);

    *VRAM = (Uint8*)VRAM_ADDR;

    *(*VRAM) = 0x80;
    *((*VRAM) + 1) = 0x00;

    set_imask(iMask);

    SpInitialFlag = 1;
}

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
