#ifndef LIBSPU_INTERNAL_H
#define LIBSPU_INTERNAL_H

#include "psxsdk/libspu.h"

#define NUM_SPU_CHANNELS 24

void* InterruptCallback(int, void (*)());
void _SpuInit(s32);
s32 _spu_read(s32 arg0, s32 arg1);
void _spu_FiDMA();

extern s32 D_80033098;
extern s32 _spu_EVdma;
extern s32 _spu_isCalled;
extern s32 _spu_inTransfer;

extern s32 D_8003355C;
extern s32 D_80033560;
extern s8* D_80033564;
extern s32 _spu_mem_mode_plus;

typedef struct tagSpuMalloc {
    u32 addr;
    u32 size;
} SPU_MALLOC;

extern s32 D_80033550;
extern void (* volatile _spu_transferCallback)();
extern s32 _spu_inTransfer;

void _SpuCallback(s32 arg0);
extern void (* volatile _spu_IRQCallback)();

s32 SpuSetAnyVoice(s32 on_off, u32 bits, s32 addr1, s32 addr2);

s32 _spu_t(s32, ...);
s32 _spu_writeByIO(u8*, s32);
extern s32 _spu_transMode;
extern u16 _spu_tsa;

u32 _spu_FsetRXXa(s32 arg0, u32 arg1);
s32 _spu_write(u8*, u32);
extern s32 _spu_inTransfer;

void _SpuSetVoiceAttr(SpuVoiceAttr* arg, s32, s32, s32);

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

typedef struct tagSpuVoiceRegister {
    SpuVolume volume; // 0-2
    u16 pitch;        // 4
    u16 addr;         // 6
    u16 adsr[2];      // 8-A
    u16 volumex;      // C
    u16 loop_addr;    // E
} SPU_VOICE_REG;      // 16 bytes

typedef struct tagSpuControl {
    SPU_VOICE_REG voice[24];
    SpuVolume main_vol; // 180
    SpuVolume rev_vol;  // 184
    // bit flags
    u16 key_on[2];       // 188
    u16 key_off[2];      // 18C
    u16 chan_fm[2];      // 190
    u16 noise_mode[2];   // 194
    u16 rev_mode[2];     // 198
    u32 chan_on;         // 19C
    u16 unk;             // 1A0
    u16 rev_work_addr;   // 1A2
    u16 irq_addr;        // 1A4
    u16 trans_addr;      // 1A6
    u16 trans_fifo;      // 1A8
    u16 spucnt;          // 1AA SPUCNT
    u16 data_trans;      // 1AC
    u16 spustat;         // 1AE SPUSTAT
    SpuVolume cd_vol;    // 1B0
    SpuVolume ex_vol;    // 1B4
    SpuVolume main_volx; // 1B8
    SpuVolume unk_vol;   // 1BC

    u16 dAPF1; // Starting at 0x1F801DC0
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
} SPU_RXX;

union SpuUnion {
    SPU_RXX rxxnv;
    volatile SPU_RXX rxx;
    volatile u16 raw[0x100];
};

extern union SpuUnion* _spu_RXX;

s32 _SpuIsInAllocateArea_(u32);
extern s32 _spu_rev_flag;
extern s32 _spu_rev_reserve_wa;
extern s32 _spu_rev_offsetaddr;

extern s32 _spu_trans_mode;
extern s32 _spu_transMode;

#define SPU_TRANSFER_BY_DMA 0
#define SPU_TRANSFER_BY_IO 1

extern u8* _spu_memList;

#endif
