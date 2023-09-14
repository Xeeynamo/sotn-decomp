#ifndef MEMCARD_H
#define MEMCARD_H

#include "common.h"
#include <psxsdk/kernel.h>
#include <psxsdk/libapi.h>

#define BLOCK_PER_CARD (15)
#define CARD_BLOCK_SIZE (8192)

typedef struct {
    /* 0x000 */ struct DIRENTRY entries[BLOCK_PER_CARD];
    /* 0x258 */ u32 unk258;
    /* 0x25C */ u32 unk25C;
    /* 0x260 */ u32 nBlockUsed;
    /* 0x264 */ s32 nFreeBlock;
    /* 0x268 */ u8 blocks[BLOCK_PER_CARD];
} MemcardInfo; /* size=0x278 */

extern MemcardInfo g_MemcardInfo[2];
extern s32 g_MemcardBlockRead;

#endif
