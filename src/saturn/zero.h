// SPDX-License-Identifier: AGPL-3.0-only
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

struct Unk0605CD90 {
    s32 dst0;
    s32 dst4;
    u16* unk8;
    s32 unkc;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1c;
    s32 unk20;
    s16 unk24;
    u8 pad[10];
};

void func_060089F0(struct Unk0605CD90* param_1);
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
    u8 unk[0x20];
    s32 unk30;
    u32 unk34;
    u32 unk38;
    u32 unk3c;
};

struct Unk0605CD90 DAT_0605CD90[];

#define DMA_SRC_ADDR 0x002E0000

extern s32* DAT_0605c120[];

#define VDP2_25E58000 0x25E58000
#define VDP2_25F00600 0x25F00600

extern s16 DAT_06062224[];
extern s32 DAT_06039214;
void ClearDebugPrintTilemap();

#define SH2_REG_M_FRT_IC 0x21000000

extern s32 DAT_060645d0;
extern s32 DAT_060cf040;

extern s32* DAT_06064674;
extern s32* DAT_060a5000;
extern s32* DAT_06064580;
extern s32* DAT_060645e0;

extern s32* DAT_06064644;
extern s32* DAT_060dc000;

extern s32* DAT_06064690;
extern s32* DAT_06066000;

void func_06006FA8(void);
int func_06018D88(void);
void func_06033024();

extern u8 DAT_060644c1;
extern u8 DAT_060644dc;

extern s32 DAT_060476a4;
extern s32 DAT_060476a0;
extern s32 DAT_06064354;
extern s32 DAT_060644AC;

struct Unk0600E050 {
    u8 pad[0x4];
    s16 unk4;
    s16 pad6;
    s16 unk8;
    u8 pada[2];
    s16 unkc;
    s16 unke;
};

void func_0601B600();
extern s32 DAT_06038a44;

s32 func_06017FA4(s32 param_1, s32 param_2, s32 param_3);

void func_060082E8(void);
void func_0600841C(void);

void func_0600AD98(void);
void func_0600B254(void);

extern s32 DAT_06064214;
extern s8 DAT_060644C0;

extern u16 DAT_0605cea2;
extern u32 DAT_0605c658;
void func_06030df0();
void func_060044D0();
void func_060040D8();

#endif
