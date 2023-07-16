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
extern s32 DAT_00252000;
extern s32 DAT_00258000;
extern s32* DAT_0606471C;

struct Unk060645D0_1 {
    struct Unk060645D0_2* unk0;
};
struct Unk060645D0_2 {
    u8 pad[0x8];
    s16 unk8;
};
extern struct Unk060645D0_1* DAT_060645D0;

s32* DAT_060485e0;
struct Unk0605d6c0* DAT_0605d6c0[];
u16 DAT_060086d4;
s32 PTR_FUN_060086cc(s32, s32, s32);
void func_0600871C(s32, s32, s32);
void func_060089F0(s32);
s32 DAT_0605c680;
s32 DAT_060086e4;
s32 func_0600F96C(s32, s32, s32);
// func_060086E8
void DmaScroll(s32* src, s32* dest, u32 cnt);

struct Unk0605d6c0 {
    u32 flags;
    u32 src;
    u32 dest;
    u32 cnt;
};

struct Unk0605CD90 {
    s32 dst0;
    s32 dst4;
    s32 unk8;
    s32 unkc;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1c;
    u8 pad[13];
};

struct Unk0605CD90 DAT_0605CD90[];

#define DMA_SRC_ADDR 0x002E0000

#endif