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

void _SsUtResolveADSR(u16 arg0, u16 arg1, struct Unk* arg2);
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

// similar to
// https://github.com/AliveTeam/sound_rev/blob/7a9223139c3375bf10e96a4ac17d77b973979e20/psx_seq_player/lib_snd.hpp#L127C1-L184C7
struct SeqStruct {
    u8 unk0;
    u8* read_pos;
    u8 pad[0x3c-8];
    u8 unk3C;
    s16 unk3E;
    s16 unk40;
    s16 unk42;
    s16 unk44;
    u8 pad46[46];
    s16 unk74;
    s16 unk76;
    s16 unk78;
    s16 unk7A;
    u8 pad7C[2];
    u32 unk80;
    u8 pad84[0xc];
    s32 unk90;
    s32 unk94;
    s32 unk98;
    s32 unk9C;
    s32 unkA0;
    s32 unkA4;
    u8 padA6[2];
};

extern struct SeqStruct* _ss_score[32];

typedef struct {
    short left;  /* Lch */
    short right; /* Rch */
} SpuVolume;

typedef struct {
    SpuVolume volume; /* volume       */
    long reverb;      /* reverb on/off */
    long mix;         /* mixing on/off */
} SpuExtAttr;

typedef struct {
    unsigned long mask; /* settings mask */

    SpuVolume mvol;     /* master volume */
    SpuVolume mvolmode; /* master volume mode */
    SpuVolume mvolx;    /* current master volume */
    SpuExtAttr cd;      /* CD input attributes */
    SpuExtAttr ext;     /* external digital input attributes */
} SpuCommonAttr;

#define SPU_COMMON_MVOLL (0x01 << 0) /* master volume (left) */
#define SPU_COMMON_MVOLR (0x01 << 1) /* master volume (right) */
extern void SpuSetCommonAttr(SpuCommonAttr* attr);

extern s16 _snd_seq_s_max;
extern s16 _snd_seq_t_max;

#endif
