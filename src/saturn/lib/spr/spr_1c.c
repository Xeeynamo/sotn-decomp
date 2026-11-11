#define _SPR2_
#include "spr.h"
#include "../machine.h"

Sint32 SpInitialFlag = 0;
// TODO import these symbols here
extern Sint32 SpScreenX;
extern Sint32 SpScreenY;
extern Uint16 SpTvMode;
extern Uint16 SpFbcrMode;
extern Uint16 SpDie;
extern Uint16 SpDil;

static Uint16 SpEraseLTPoint = 0;
static Uint16 SpEraseRBPoint = 0;
static Uint16 EraseData = 0;
static Uint16 EraseLeftX = 0;
static Uint16 EraseTopY = 0;
static Uint16 EraseRightX = 0;
static Uint16 EraseBotY = 0;
static Uint16 BitWidth = 0;

static XyInt scrSize[8] = {
    {320, 224}, /* SPR_TV_320X224  */
    {320, 240}, /* SPR_TV_320X240  */
    {352, 224}, /* SPR_TV_352X224  */
    {352, 240}, /* SPR_TV_352X240  */
    {640, 224}, /* SPR_TV_640X224  */
    {640, 240}, /* SPR_TV_640X240  */
    {704, 224}, /* SPR_TV_704X224  */
    {704, 240}, /* SPR_TV_704X240  */
};

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
