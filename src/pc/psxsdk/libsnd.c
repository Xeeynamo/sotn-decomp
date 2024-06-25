#ifndef WANT_LIBSND_LLE
#include <common.h>
#include <psxsdk/libspu.h>
#include <psxsdk/libsnd.h>
#include <log.h>

short SsUtSetVVol(short vc, short voll, short volr) {
    DEBUGF("not implemented\n");
    return 0;
}

void SsSetSerialAttr(char s_num, char attr, char mode) { NOT_IMPLEMENTED; }

void SsSeqPlay(s16 seq_access_num, s8 play_mode, s16 l_count) {
    NOT_IMPLEMENTED;
}

void SsSetMVol(short voll, short volr) { NOT_IMPLEMENTED; }

void SsSeqSetVol(s16 arg0, s32 arg1, s32 arg2) { NOT_IMPLEMENTED; }

short SsSeqOpen(u_long* addr, short vab_id) {
    NOT_IMPLEMENTED;
    return 0;
}

void SsSeqClose(short seq_access_num) { NOT_IMPLEMENTED; }

void SsSeqStop(short seq_access_num) { NOT_IMPLEMENTED; }

short SsUtKeyOnV(short voice, short vabId, short prog, short tone, short note,
                 short fine, short voll, short volr) {
    NOT_IMPLEMENTED;
    return 0;
}

void SsUtReverbOn(void) { NOT_IMPLEMENTED; }

void SsUtSetReverbType(short type) { NOT_IMPLEMENTED; }

void SsSetTableSize(char* table, short s_max, short t_max) { NOT_IMPLEMENTED; }

void SsStart(void) { NOT_IMPLEMENTED; }

char SsSetReservedVoice(char voices) {
    DEBUGF("%d", voices);
    return 0;
}

void SsSetTickMode(long tick_mode) { DEBUGF("%d", tick_mode); }

void MySsInitHot();
void SsInitHot(void) { MySsInitHot(); }

void SsSetStereo(void) { NOT_IMPLEMENTED; }

void SsSetMono(void) { NOT_IMPLEMENTED; }

void SsSetSerialVol(short s_num, short voll, short volr) {
    DEBUGF("s_num %d voll %d volr %d", s_num, voll, volr);
}

void SsUtSetReverbDepth(short ldepth, short rdepth) {
    DEBUGF("ldepth %d rdepth %d", ldepth, rdepth);
}

s32 SsVabTransCompleted(short immediateFlag) {
    NOT_IMPLEMENTED;
    return 1;
}

s32 SsVabOpenHeadSticky(u_char* addr, u_long vabid, u_long sbaddr) {
    NOT_IMPLEMENTED;
    return 0;
}

s32 SsVabTransBodyPartly(u_char* addr, u_long bufsize, u_long vabid) {
    NOT_IMPLEMENTED;
    return 0;
}

void SsVabClose(short vab_id) { NOT_IMPLEMENTED; }

#else
#include <common.h>
#include <psxsdk/libspu.h>
#include <log.h>
#include <assert.h>
#include "../../main/psxsdk/libsnd/libsnd_i.h"
#include <stdarg.h>

u16* D_80032F10;

struct SpuVoice _svm_voice[NUM_SPU_CHANNELS];

void WaitEvent(s32) {}

union RegBuf _svm_sreg_buf;

unsigned char _svm_sreg_dirty[NUM_SPU_CHANNELS];

unsigned short _svm_okon1;
unsigned short _svm_okon2;
unsigned short _svm_okof1;
unsigned short _svm_okof2;

s32 _svm_brr_start_addr[16]; /* number: 10 */
s16 _svm_stereo_mono;        /* number: 11 */
SpuReverbAttr _svm_rattr;    /* number: 12 */
u8 _svm_vab_used[16] = {0};  /* number: 13 */
u8 spuVmMaxVoice;            /* number: 14 */
u16 _svm_vab_count;          /* number: 15 */
s16 kMaxPrograms;            /* number: 16 */
struct struct_svm _svm_cur;  /* number: 17 */
s16 _svm_damper;             /* number: 18 */
s16 _svm_vcf;                /* number: 19 */
u8 _svm_auto_kof_mode;       /* number: 20 */
VabHdr* _svm_vab_vh[16];     /* number: 21 */
ProgAtr* _svm_vab_pg[16];    /* number: 22 */
VagAtr* _svm_vab_tn[16];     /* number: 23 */
s32 _svm_vab_start[16];      /* number: 24 */
s32 _svm_vab_total[16];      /* number: 25 */
VabHdr* _svm_vh;             /* number: 26 */
ProgAtr* _svm_pg;            /* number: 27 */
VagAtr* _svm_tn;             /* number: 28 */
void* _svm_vg;               /* number: 29 */

void ResetCallback() {}

typedef void (*SndSsMarkCallbackProc)(short seq_no, short sep_no, short data);

SndSsMarkCallbackProc _SsMarkCallback[32][16]; /* #11 */
struct SeqStruct* _ss_score[32];               /* #12 */
s32 VBLANK_MINUS;                              /* #13 */
s32 _snd_openflag;                             /* #14 */
s16 _snd_seq_s_max;                            /* #15 */
s16 _snd_seq_t_max;                            /* #16 */
s32 _snd_ev_flag;                              /* #17 */

long _spu_transMode;

void* DMACallback(int dma, void (*func)()) { return NULL; }

s32 _spu_rev_startaddr[16] = {
    0x0000FFFE, 0x0000FB28, 0x0000FC18, 0x0000F6F8, 0x0000F204, 0x0000EA44,
    0x0000E128, 0x0000CFF8, 0x0000CFF8, 0x0000F880, 0x00000002, 0x000004D8,
    0x000003D8, 0x00000908, 0x00000DFC, 0x000015BC};
s32 D_80033098;

// s_ini.c
s32 _spu_fd = 0;
long _spu_trans_mode = 0;
s32 _spu_rev_flag = 0;
s32 _spu_rev_reserve_wa = 0;
s32 _spu_rev_offsetaddr = 0;

SpuReverbAttr _spu_rev_attr = {0, 0, 0, 0, 0, 0};

u16 _spu_voice_centerNote[24] = {
    0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000,
    0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000,
    0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000};

s32 _spu_EVdma = 0;

s32 _spu_keystat = 0;

s8 _spu_zerobuf[1024] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
s32 _spu_isCalled = 0;

u16 D_80032F14[1];
s32 _spu_AllocBlockNum;
s32 D_80033560;
s8* D_80033564;
s32 _spu_mem_mode_plus = 3;

typedef struct tagSpuMalloc {
    u32 addr;
    u32 size;
} SPU_MALLOC;

SPU_MALLOC* _spu_memList = NULL;

s32 _spu_inTransfer;
struct _ss_spu_vm_rec_struct {
    u32 pad[2];
    SPU_MALLOC D_8003BD50[364];
};

short D_80032EC0[] = {0x0000, 0x0000, 0x1000, 0x3000,
                      0x00BF, 0x0000, 0x0000, 0x0000};
union SpuUnion* _spu_RXX;

u16 D_80032ED0[] = {0x3FFF, 0x3FFF, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000};

struct _ss_spu_vm_rec_struct _ss_spu_vm_rec;

s16 _svm_orev1;
s16 _svm_orev2;

void SpuVmKeyOn(s16, s16, u8, s32, s32, s32) { assert(0); }

s32 _svm_envx_hist[32];
s32 D_8003BD08 = 0;

void SpuVmFlush(void) {}

void SpuVmKeyOnNow(short vagCount, short pitch) { assert(0); }

void vmNoiseOn(s32 arg0) { assert(0); }

void SpuVmDoAllocate(void) { assert(0); }

struct rev_param_entry {
    u32 flags;
    u16 dAPF1;
    u16 dAPF2;
    u16 vIIR;
    u16 vCOMB1;
    u16 vCOMB2;
    u16 vCOMB3;
    u16 vCOMB4;
    u16 vWALL;
    u16 vAPF1;
    u16 vAPF2;
    u16 mLSAME;
    u16 mRSAME;
    u16 mLCOMB1;
    u16 mRCOMB1;
    u16 mLCOMB2;
    u16 mRCOMB2;
    u16 dLSAME;
    u16 dRSAME;
    u16 mLDIFF;
    u16 mRDIFF;
    u16 mLCOMB3;
    u16 mRCOMB3;
    u16 mLCOMB4;
    u16 mRCOMB4;
    u16 dLDIFF;
    u16 dRDIFF;
    u16 mLAPF1;
    u16 mRAPF1;
    u16 mLAPF2;
    u16 mRAPF2;
    u16 vLIN;
    u16 vRIN;
};

struct rev_param_entry _spu_rev_param[1];

long SpuSetReverbModeParam(SpuReverbAttr* attr) {
    // skipping this for now
    return 0;
}

long ResetRCnt(long spec) { return 1; }

void* InterruptCallback(u8, void (*)()) { return 0; }

long GetVideoMode(void) { return 0; }

struct SndSeqTickEnv _snd_seq_tick_env;

s32 D_8003355C;

void SpuSetCommonAttr(SpuCommonAttr* attr) { assert(false); }

s32 _spu_AllocBlockNum;
s32 _spu_AllocLastNum;
s32 _spu_mem_mode_unitM;
s32 _spu_rev_offsetaddr;
s32 _spu_rev_reserve_wa;

long SpuMalloc(long size) {
    assert(false);
    return 0;
}

int SsVabOpenHeadWithMode(unsigned char* pAddr, int vabId, s32 pFn, long mode) {
    assert(false);
    return 0;
}

void func_800286E0(void) {}

u16 _spu_tsa;
void (* volatile _spu_transferCallback)();

s32 _spu_mem_mode;
s32 _spu_mem_mode_unit;
s32 _spu_mem_mode_unitM;

s32* D_80033508;
s32* D_8003350C;
s32* D_80033510;
s32* D_80033518;
s32 D_80033550;
s32 D_800334FC;
s32* D_80033514;
u16 D_80033540[] = {
    0x0707, 0x0707, 0x0707, 0x0707, 0x0707, 0x0707, 0x0707, 0x0707,
};
s32 _spu_addrMode;

void (* volatile _spu_IRQCallback)();

void DeliverEvent(unsigned long, unsigned long) {}

s32 D_800330F8[256] = {0};
s32 D_80033558;
volatile u32* D_80033554;

void write_dma(u32 data, char* file, int line);

// dma function, reimplement to avoid pulling in dma controller
int _spu_t(int mode, ...) {
    va_list args;
    va_start(args, mode);
    s32 spu_ram_dest_addr;
    u32* source_address;
    s32 count;
    s32 i;

    switch (mode) {
    case 0:
    case 1:
        write_16(0x1F801DAA, (read_16(0x1F801DAA) & ~0x30) | 0x20, __FILE__,
                 __LINE__);
        return 0;

    case 2:
        // set destination address
        spu_ram_dest_addr = va_arg(args, u32) >> _spu_mem_mode_plus;
        _spu_tsa = spu_ram_dest_addr;

        // dma destination address in spu ram
        write_16(0x1f801da6, spu_ram_dest_addr, __FILE__, __LINE__);
        return 0;

    case 3:
        // transfer
        source_address = (u32*)va_arg(args, u32*);
        count = (s32)va_arg(args, s32);
        for (i = 0; i < count / 4; i++) {
            write_dma(source_address[i], __FILE__, __LINE__);
        }
        return 0;
        break;
    }

    assert(false);
    return 0;
}

void _SsSndCrescendo(s16, s16) { assert(false); }
void _SsSndDecrescendo(s16, s16) { assert(false); }

void SpuVmSetVol(
    short seq_sep_no, short vabId, short program, short voll, short volr) {
    assert(false);
}

void _SsContDataEntry(s16, s16, u8) { assert(false); }

#endif
