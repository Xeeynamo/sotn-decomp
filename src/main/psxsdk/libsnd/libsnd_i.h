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

void SpuVmSeKeyOn(s16 arg0, s16 arg1, u16 arg2, s32 arg3, u16 arg4, u16 arg5);
void SpuVmSetSeqVol(s16, u16, u16, s32);
s32 SpuVmGetSeqVol(s16, s16*, s16*);
s16 SpuIsTransferCompleted(s16);

void _spu_setInTransfer(s32);
u32 SpuSetTransferStartAddr(u32);
extern s32 _svm_vab_total[];
extern s32 _svm_vab_start[];
extern u8 _svm_vab_used[];

s16 SsVabOpenHeadWithMode(u8* addr, s16 vabid, s32 arg2, u32 sbaddr);

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

u8 SpuVmAlloc(u8);
s32 vmNoiseOn2(u8, u16, u16, u16, u16);

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
};

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

extern ProgAtr* _svm_pg;

struct RegBufStruct {
    short field_0_vol_left;
    short field_2_vol_right;
    short field_4_pitch;
    unsigned short field_6_vagAddr;
    unsigned short field_8_adsr1;
    unsigned short field_A_adsr2;
    short field_0xc;
    short field_0xe;
};
extern struct RegBufStruct _svm_sreg_buf[24];
extern unsigned char _svm_sreg_dirty[24];

extern volatile u16* D_80032F10;
extern u8 spuVmMaxVoice;

struct SpuVoice {
    u8 pad[4];
    s16 unk04;
    u8 pad2[6];
    s16 unkc;
    s16 unke;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    u8 pad4[3];
    u8 unk1b;
    u8 pad3[23];
};

extern struct SpuVoice _svm_voice[24];
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

s16 SsVabTransBodyPartly(u8* addr, u32 bufsize, s16 vabid);
u32 SpuWritePartly(u8*, u32);

struct SndSeqTickEnv {
    s32 unk0;
    s32 unk4;
    u32 unk8;
    u32 unk12;
    u8 unk16;
    u8 unk17;
    u8 unk18;
};

extern struct SndSeqTickEnv _snd_seq_tick_env;

extern s32 VBLANK_MINUS;

extern s16 _svm_damper;

s32 SpuVmPBVoice(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4);

extern VagAtr* _svm_vab_tn[16];
extern ProgAtr* _svm_vab_pg[16];
extern VabHdr* _svm_vab_vh[16];
extern ProgAtr* _svm_pg;
extern VabHdr* _svm_vh;
extern s16 kMaxPrograms;

#endif
