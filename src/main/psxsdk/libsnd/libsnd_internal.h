#ifndef LIBSND_INTERNAL_H
#define LIBSND_INTERNAL_H

#include "common.h"
struct Unk {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    s16 unkA;
    u16 unkC;
    u16 unkE;
    u16 unk10;
};

void _SsUtResolveADSR(s32 arg0, u32 arg1, struct Unk* arg2);
void _SsSeqPlay(s16, s16);
void _SsClose(s16);

extern s32 D_80032EF4;
extern u8 D_80032F00;
extern s8 D_80032F01;
extern u8 D_80032F02;
void EnterCriticalSection(void);
void VSyncCallback(void (*func)());
void ExitCriticalSection(void);
void InterruptCallback(s32, s32);
void ResetCallback();
void SpuInit();
void _SsInit();
void Snd_SetPlayMode(s16, s16, u8, s16);
void SpuQuit();
void _SsStart(s32);
extern void (*D_80032EF8)();
extern void (*D_80032EFC)();
extern s32 D_80032F04;
void SpuVmSeKeyOff(s16 arg0, s16 arg1, u16 arg2);
void SpuVmSeKeyOn(s32, u8, u16, u8, u16, u16);
void SpuVmSetSeqVol(s16, u16, u16, s32);
s32 SpuVmGetSeqVol(s16, s16*, s16*);
s16 func_8002ACB4(s16);

void _spu_setInTransfer(s32);
void func_8002AB58(u8*, s32);
void func_8002ABB8(s32);
void func_8002ABF4(s32);
extern s32 D_800987CC[];
extern s32 D_80098810[];
extern u8 svm_vab_used[];

s16 SsVabOpenHeadWithMode(u8* addr, s16 vabid, s32 arg2, u32 sbaddr);

void _spu_setInTransfer(s32);
extern u8 svm_vab_used[];

extern u8 svm_vab_used[];
void func_80028FF4(s32);
extern s32 D_80098810[];
extern u16 _svm_vab_count;

typedef struct VabHdr {
    s32 form;
    s32 ver;
    s32 id;
    u32 fsize;
    u16 reserved0;
    u16 ps;
    u16 ts;
    u16 vs;
    u8 mvol;
    u8 pan;
    u8 attr1;
    u8 attr2;
    u32 reserved1;
} VabHdr;

s16 SsVabOpenHead(u8*, s16);
s16 SsVabTransBody(u8*, s16);
extern s32 D_80098854[];

extern u8 spuVmMaxVoice;

extern s16 _svm_stereo_mono;

u8 SpuVmAlloc(u8);
s32 vmNoiseOn2(u8, u16, u16, s32, s32);
extern s8 D_800978D7;
extern s16 D_800978E2;
extern u8 spuVmMaxVoice;
void SpuVmKeyOff(s32, s16, s16, u16);
void SeAutoVol(s16, s16, s16, s16);
void SeAutoPan(s16, s16, s16, s16);

#endif