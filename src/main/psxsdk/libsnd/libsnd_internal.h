#ifndef LIBSND_INTERNAL_H
#define LIBSND_INTERNAL_H

#include <psxsdk/libspu.h>

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

extern s32 D_8003C74C;
extern SpuReverbAttr _svm_rattr;

void SpuVmSeKeyOn(s32, u8, u16, u8, u16, u16);
void SpuVmSetSeqVol(s16, u16, u16, s32);
s32 SpuVmGetSeqVol(s16, s16*, s16*);
s16 SpuIsTransferCompleted(s16);

void _spu_setInTransfer(s32);
void SpuSetTransferStartAddr(s32);
extern s32 D_800987CC[];
extern s32 D_80098810[];
extern u8 svm_vab_used[];

s16 SsVabOpenHeadWithMode(u8* addr, s16 vabid, s32 arg2, u32 sbaddr);

void _spu_setInTransfer(s32);

void SpuFree(s32);
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
s32 vmNoiseOn2(u8, u16, u16, u16, u16);
extern s8 D_800978D7;
extern s16 D_800978E2;
extern u8 spuVmMaxVoice;
void SeAutoVol(s16, s16, s16, s16);
void SeAutoPan(s16, s16, s16, s16);

// similar to
// https://github.com/AliveTeam/sound_rev/blob/7a9223139c3375bf10e96a4ac17d77b973979e20/psx_seq_player/lib_snd.hpp#L127C1-L184C7

struct SeqStruct {
    u8 unk0;
    u8 pad1[3];
    u8* read_pos;
    s32 unk8;
    s32 unkc;
    u8 unk10;
    u8 unk11;
    u8 channel;
    u8 unk13;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 panpot[16];
    u8 unk27;
    u8 unk28;
    u8 unk29;
    u8 unk2a;
    u8 unk2b;
    u8 programs[16];
    u8 unk3C;
    u8 pad3D;
    s16 unk3E;
    s16 unk40;
    s16 unk42;
    s16 unk44;
    s16 unk46;
    s16 unk48;
    u8 pad8[2];
    s16 unk4c;
    s16 vol[16];
    u8 pad10[1];
    s16 unk70;
    s16 unk72;
    u16 unk74;
    s16 unk76;
    s16 unk78;
    s16 unk7A;
    s32 unk7c;
    u32 unk80;
    s32 unk84;
    s32 delta_value;
    s32 unk8c;
    s32 unk90;
    s32 unk94;
    s32 unk98;
    s32 unk9C;
    s32 unkA0;
    s32 unkA4;
    s16 padA6;
    s16 padaa;
};

extern struct SeqStruct* _ss_score[32];

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

typedef struct ProgAtr { /* Program Headdings */

    unsigned char tones;      /* # of tones */
    unsigned char mvol;       /* program volume */
    unsigned char prior;      /* program priority */
    unsigned char mode;       /* program mode */
    unsigned char mpan;       /* program pan */
    char reserved0;           /* system reserved */
    short attr;               /* program attribute */
    unsigned long reserved1;  // "fake" program index (skips empties)
    unsigned short reserved2; // even vag spu ptr
    unsigned short reserved3; // odd vag spu ptr
} ProgAtr;                    /* 16 byte */

extern ProgAtr* D_8006C3B4;
extern u8 svm_vab_used[];

#endif
