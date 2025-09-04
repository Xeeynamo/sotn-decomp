// SPDX-License-Identifier: MIT
#ifndef LIBSND_INTERNAL_H
#define LIBSND_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <psxsdk/libspu.h>

#include "common.h"
struct Unk {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    s16 unkA;
    s16 unkC;
    u16 unkE;
    s16 unk10;
};
void _SsUtResolveADSR(u16 arg0, u16 arg1, struct Unk* arg2);
void _SsSeqPlay(s16, s16);
void _SsClose(s16);

void EnterCriticalSection(void);
void VSyncCallback(void (*func)());
void ExitCriticalSection(void);
void* InterruptCallback(u8, void (*)());
void ResetCallback(void);
void SpuInit(void);
void _SsInit(void);
void SsSeqCalledTbyT(void);
void Snd_SetPlayMode(s16, s16, u8, s16);
void SpuQuit(void);

extern s32 D_8003C74C;
extern SpuReverbAttr _svm_rattr;

void SpuVmSeKeyOn(s16 arg0, s16 arg1, u16 arg2, s32 arg3, u16 arg4, u16 arg5);
s32 SpuVmSetSeqVol(s16 seq_sep_no, u16 voll, u16 volr, s16 arg3);
s32 SpuVmGetSeqVol(s16, s16*, s16*);
s16 SpuIsTransferCompleted(s16);

void _spu_setInTransfer(s32);
u32 SpuSetTransferStartAddr(u32);
extern s32 _svm_vab_total[];
extern s32 _svm_vab_start[];
extern u8 _svm_vab_used[];

void SpuFree(s32);
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
extern s32 _svm_brr_start_addr[];

extern u8 spuVmMaxVoice;

extern s16 _svm_stereo_mono;

void vmNoiseOn2(u8 arg0, u16 arg1, u16 arg2, u16 arg3, u16 arg4);

#ifdef VERSION_PC
struct thing {
    s16 a, b;
};

struct struct_svm {
    char field_0_sep_sep_no_tonecount;
    char field_1_vabId;
    char field_2_note;
    char field_0x3;
    char field_4_voll;
    char field_0x5;
    char field_6_program;
    char field_7_fake_program;
    char field_8_unknown;
    char field_0x9;
    char field_A_mvol;
    char field_B_mpan;
    char field_C_vag_idx;
    char field_D_vol;
    char field_E_pan;
    char field_F_prior;
    char field_10_centre;
    unsigned char field_11_shift;
    char field_12_mode;
    char field_0x13;
    short field_14_seq_sep_no;
    short field_16_vag_idx;
    short field_18_voice_idx;
    short field_0x1a;
    struct thing unk1c;
};
#else
struct struct_svm {
    char field_0_sep_sep_no_tonecount;
    char field_1_vabId;
    char field_2_note;
    char field_0x3;
    char field_4_voll;
    char field_0x5;
    char field_6_program;
    char field_7_fake_program;
    char field_8_unknown;
    char field_0x9;
    char field_A_mvol;
    char field_B_mpan;
    char field_C_vag_idx;
    char field_D_vol;
    char field_E_pan;
    char field_F_prior;
    char field_10_centre;
    unsigned char field_11_shift;
    char field_12_mode;
    char field_0x13;
    u8 field_14_seq_sep_no;
    u8 pad;
    short field_16_vag_idx;
    short field_18_voice_idx;
    short field_0x1a;
};
#endif

extern struct struct_svm _svm_cur;

extern u8 spuVmMaxVoice;
void SeAutoVol(s16, s16, s16, s16);
void SeAutoPan(s16, s16, s16, s16);

// similar to
// https://github.com/AliveTeam/sound_rev/blob/7a9223139c3375bf10e96a4ac17d77b973979e20/psx_seq_player/lib_snd.hpp#L127C1-L184C7

struct SeqStruct {
    u8 unk0;
    u8 pad1[3];
    u8* read_pos;
    u8* next_sep_pos; /* 0x8 */
    u8* loop_pos;     /* 0xC */
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
    s16 unk4a;
    s16 unk4c;
    s16 vol[16];
    s16 unk6E;
    s16 unk70;
    s16 unk72;
    u16 unk74;
    u16 unk76;
    s16 unk78;
    s16 unk7A;
    s32 unk7c;
    u32 unk80;
    s32 unk84;
    s32 delta_value;
    s32 unk8c;
    s32 unk90;
    u32 unk94;
    u32 unk98;
    s32 unk9C;
    u32 unkA0;
    u32 unkA4;
    s16 padA6;
    s16 padaa;
};

#ifdef VERSION_PC
extern struct SeqStruct* _ss_score[34];
#else
extern struct SeqStruct* _ss_score[32];
#endif

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
    u32 reserved1;            // "fake" program index (skips empties)
    unsigned short reserved2; // even vag spu ptr
    unsigned short reserved3; // odd vag spu ptr
} ProgAtr;                    /* 16 byte */

extern ProgAtr* _svm_pg;

#define NUM_SPU_CHANNELS 24

extern s16 _svm_sreg_buf[NUM_SPU_CHANNELS * 8];

extern unsigned char _svm_sreg_dirty[NUM_SPU_CHANNELS];

extern u8 spuVmMaxVoice;

struct SpuVoice {
    s16 unk0;
    s16 unk2;
    s16 unk04;
    u16 unk6;
    s16 unk8;
    char unka;
    char unkb;
    s16 note; /* 0xC */
    s16 unke;
    s16 unk10;
    s16 prog;  /* 0x12 */
    s16 tone;  /* 0x14*/
    s16 vabId; /* 0x16 */
    s16 unk18;
    u8 pad4[1];
    u8 unk1b;
    s16 auto_vol; /* 0x1c */
    s16 unk1e;
    s16 unk20;
    s16 unk22;
    s16 start_vol; /* 0x24 */
    s16 end_vol;   /* 0x26 */
    s16 auto_pan;  /* 0x28 */
    s16 unk2a;
    s16 unk2c;
    s16 unk2e;
    s16 start_pan; /* 0x30 */
    s16 end_pan;   /* 0x32 */
};

extern struct SpuVoice _svm_voice[NUM_SPU_CHANNELS];
u32 SpuVmVSetUp(s16, s16);

typedef struct VagAtr { /* VAG Tone Headdings */

    unsigned char prior;     /* tone priority */
    unsigned char mode;      /* play mode */
    unsigned char vol;       /* tone volume*/
    unsigned char pan;       /* tone panning */
    unsigned char center;    /* center note */
    unsigned char shift;     /* center note fine tune */
    unsigned char min;       /* minimam note limit */
    unsigned char max;       /* maximam note limit */
    unsigned char vibW;      /* vibrate depth */
    unsigned char vibT;      /* vibrate duration */
    unsigned char porW;      /* portamento depth */
    unsigned char porT;      /* portamento duration */
    unsigned char pbmin;     /* under pitch bend max */
    unsigned char pbmax;     /* upper pitch bend max */
    unsigned char reserved1; /* system reserved */
    unsigned char reserved2; /* system reserved */
    unsigned short adsr1;    /* adsr1 */
    unsigned short adsr2;    /* adsr2 */
    short prog;              /* parent program*/
    short vag;               /* vag reference */
    short reserved[4];       /* system reserved */

} VagAtr; /* 32 byte */

extern VagAtr* _svm_tn;

void SpuVmFlush();
void _SsSndCrescendo(s16, s16);
void _SsSndDecrescendo(s16, s16);
void _SsSndPause(s16, s16);
void _SsSndPlay(s16, s16);
void _SsSndReplay(s16, s16);
void _SsSndTempo(s16, s16);
extern s32 _snd_ev_flag;
extern s32 _snd_openflag;

short SsUtGetProgAtr(short vabId, short progNum, ProgAtr* progatrptr);
short SsUtGetVagAtr(
    short vabId, short progNum, short toneNum, VagAtr* vagatrptr);
short SsUtSetVagAtr(
    short vabId, short progNum, short toneNum, VagAtr* vagatrptr);

short SsVabTransBodyPartly(
    unsigned char* addr, unsigned long bufsize, short vabid);

u32 SpuWritePartly(u8*, u32);

struct SndSeqTickEnv {
    s32 unk0;
    s32 unk4;
    void (*unk8)();
    void (*unk12)();
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
    u32 unk20;
};

extern struct SndSeqTickEnv _snd_seq_tick_env;

extern u32 VBLANK_MINUS;

extern s16 _svm_damper;

extern VagAtr* _svm_vab_tn[16];
extern ProgAtr* _svm_vab_pg[16];
extern VabHdr* _svm_vab_vh[16];
extern ProgAtr* _svm_pg;
extern VabHdr* _svm_vh;
extern s16 kMaxPrograms;

extern unsigned short _svm_okon1;
extern unsigned short _svm_okon2;
extern unsigned short _svm_okof1;
extern unsigned short _svm_okof2;

void SsUtSetReverbDepth(short, short);

#ifdef __cplusplus
}
#endif

#endif
