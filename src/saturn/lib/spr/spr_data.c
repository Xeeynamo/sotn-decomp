#include "../def.h"

/* Writable SPR library state in its original SDK order. */
Sint32 SpInitialFlag = 0;
Uint16 SpEraseLTPoint = 0;
Uint16 SpEraseRBPoint = 0;
Uint16 EraseData = 0;
Uint16 EraseLeftX = 0;
Uint16 EraseTopY = 0;
Uint16 EraseRightX = 0;
Uint16 EraseBotY = 0;
Uint16 BitWidth = 0;

XyInt scrSize[8] = {
    {320, 224}, {320, 240}, {352, 224}, {352, 240},
    {640, 224}, {640, 240}, {704, 224}, {704, 240},
};

Uint16 SpTvMode = 0;
Uint16 SpFbcrMode = 0;
Uint16 SpDie = 0;
Uint16 SpDil = 0;
Uint32 SPR_SlaveParam = 0;
