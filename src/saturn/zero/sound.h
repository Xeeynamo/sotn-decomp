// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_ZERO_SOUND_H
#define SATURN_ZERO_SOUND_H

#include "sattypes.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s16 unk24;
    s16 unk26;
} SoundRequest;

typedef struct {
    s32 unk0;
    s32 unk4;
} SoundMemoryLayout;

extern SoundRequest DAT_06063C30[];
extern SoundMemoryLayout DAT_06062270;

#define UNCACHED_SOUND_REQUESTS ((volatile SoundRequest*)0x26063C30)

void PcmOpen(s32 code);
void PcmLseek(u32 handle, s32 offset);
void func_06016B9C(s32 handle, s32 address, s32 size);
void PcmClose(s32 handle, s32 type);

extern void (*DAT_06000310)(s32, void (*)(void));

extern s32 DAT_06041280;
extern s32 DAT_06041284;
extern s32 DAT_06057C24;
extern s32 DAT_06057C28;
extern s32 DAT_06057C2C;
extern s32 DAT_06057C30;
extern s32 DAT_06062238;
extern s32 DAT_06062244;
extern s32 DAT_06062248;
extern s32 DAT_06062250;
extern s32 DAT_06062280;
extern s32 DAT_06062378;
extern u32 DAT_06062388;
extern s32 DAT_060623A0;
extern s32 DAT_060623BC;
extern s32 DAT_06063BD0;
extern s32 DAT_06063BFC;
extern s32 DAT_06063C18;
extern s32 DAT_06063E70;
extern s32 DAT_06063E90;
extern u32 DAT_06063EA8;
extern s32 DAT_06063EB0;
extern s32 DAT_060641D0;
extern s32 DAT_060641D4;
extern s32 DAT_060641D8;
extern s32 DAT_060641DC;
extern s32 DAT_060641E0;
extern s32 DAT_060641E4;
extern u32 DAT_060641EC;
extern s32 DAT_06064208;
extern s32 DAT_06064210;
extern s32 DAT_0606422C;
extern s32 DAT_06064234;
extern s16 DAT_06064238;
extern u32 DAT_0606423C;
extern s8 DAT_060642E8;
extern s32 DAT_060642EC;
extern s32 DAT_060642F4;
extern s32 DAT_060642DC;
extern s32 DAT_06064300;
extern s32 DAT_06064324;
extern s8 DAT_06064330;
extern s32 DAT_06064334;
extern s32 DAT_06064338;
extern s32 DAT_0606433C;
extern u32 DAT_06064350;
extern s32 DAT_06064358;
extern s32 DAT_06064360;
extern s8 DAT_06064378;
extern u32 DAT_06064384;
extern s32 DAT_0606438C;
extern s32 DAT_06064390;
extern s32 DAT_06064394;
extern s32 DAT_060643D0;
extern s8 DAT_06064400;
extern s8 DAT_0606442C;
extern s32 DAT_06064430;
extern s8 DAT_06064474;
extern s8 DAT_06064488;
extern u32 DAT_0606448C;
extern u32 DAT_06064498;
extern s8 DAT_060644A0;
extern s8 DAT_060644C2;
extern s8 DAT_060644C5;
extern s8 DAT_060644E4;
extern s8 DAT_0606227C;
extern s32 d_060623B0[];

void PlaySfx(s32 sfxId);
void func_06010400(void);
void func_06012474(void);
void func_06012554(void);
void func_060139C4(void);
void func_060157CC(void);
void func_06015E68(void);
void func_06017508(void);
void func_06017988(void);
s32 IsXaBgmPlaying(void);
s32 func_0601B448(s32*);
s32 func_0601B4AC(u8*);
s32 func_0601B674(s32);
s32 func_0601BC14(s32, s32, s32, s32);
void func_0601BE3C(s32, void*, s32*);
s32 func_0601BEE8(s32);
s32 func_0601C01C(s32, s32);
s32 func_0601C26C(s32);

#endif
