#ifndef MEMCARD_H
#define MEMCARD_H

// save manager
// port: 0 or 1, it is the physical port where you plug the memory card.
// port_s: 0-3, valid only in the context of multi tap, unused in this game.
// channel: the numerical combination of port and port_s
// block: 0-14, a memory card can store up to 15 blocks

#include "common.h"
#include <psxsdk/kernel.h>
#include <psxsdk/libapi.h>

#define PORT_COUNT (2)
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
extern s32 g_MemcardPortMask[];
extern u16 g_saveIconPal0[0x10][0x10];
extern u8* g_saveIconTexture[0x10];

#endif
