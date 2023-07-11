#ifndef ZERO_BIN_H
#define ZERO_BIN_H
#include "sattypes.h"

#define VDP2_VRAM 0x25E00000
#define VDP2_DEBUG_TILEMAP_OFFSET (VDP2_VRAM + 0x58000)

// func_06023394
void DMA_CpuMemCopy(s32*, s32*, u32);

// func_06023484
s32 DMA_CpuResult();

// func_060234F4
void DMA_ScuInit();

void SPR_2SetGourTbl(u16 arg0);

void func_0600DACC();

extern s32 DAT_0601ac28[];
extern s32 DAT_0601ac2c[];
extern s32 DAT_0601ac30[];
extern s32 DAT_0601ac34[];
extern s32 DAT_0601ac38[];
extern s32 DAT_0601ac3c[];
extern s32 DAT_0601ac40[];
extern s32 DAT_0601ac44[];
extern s32 DAT_0605D910[];
extern s16 DAT_0605AEA8;
extern s16 DAT_06057A10[];

struct Unk060645D0_1 {
    struct Unk060645D0_2* unk0;
};
struct Unk060645D0_2 {
    u8 pad[0x8];
    s16 unk8;
};
extern struct Unk060645D0_1* DAT_060645D0;

#endif