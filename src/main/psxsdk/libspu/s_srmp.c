#define INCLUDE_ASM_NEW
#include "common.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libspu/s_srmp", SpuSetReverbModeParam);

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

typedef struct {
    short left;  /* Lch */
    short right; /* Rch */
} SpuVolume;
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

extern SPU_RXX* _spu_RXX;

void _spu_setReverbAttr(struct rev_param_entry* arg0) {
    s32 temp_a2;
    u32 temp_a1;

    temp_a1 = arg0->flags;
    temp_a2 = temp_a1 == 0;
    if ((temp_a2 != 0) || (temp_a1 & 1)) {
        _spu_RXX->dAPF1 = arg0->dAPF1;
    }
    if ((temp_a2 != 0) || (temp_a1 & 2)) {
        _spu_RXX->dAPF2 = arg0->dAPF2;
    }
    if ((temp_a2 != 0) || (temp_a1 & 4)) {
        _spu_RXX->vIIR = arg0->vIIR;
    }
    if ((temp_a2 != 0) || (temp_a1 & 8)) {
        _spu_RXX->vCOMB1 = arg0->vCOMB1;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x10)) {
        _spu_RXX->vCOMB2 = arg0->vCOMB2;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x20)) {
        _spu_RXX->vCOMB3 = arg0->vCOMB3;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x40)) {
        _spu_RXX->vCOMB4 = arg0->vCOMB4;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x80)) {
        _spu_RXX->vWALL = arg0->vWALL;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x100)) {
        _spu_RXX->vAPF1 = arg0->vAPF1;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x200)) {
        _spu_RXX->vAPF2 = arg0->vAPF2;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x400)) {
        _spu_RXX->mLSAME = arg0->mLSAME;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x800)) {
        _spu_RXX->mRSAME = arg0->mRSAME;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x1000)) {
        _spu_RXX->mLCOMB1 = arg0->mLCOMB1;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x2000)) {
        _spu_RXX->mRCOMB1 = arg0->mRCOMB1;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x4000)) {
        _spu_RXX->mLCOMB2 = arg0->mLCOMB2;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x8000)) {
        _spu_RXX->mRCOMB2 = arg0->mRCOMB2;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x10000)) {
        _spu_RXX->dLSAME = arg0->dLSAME;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x20000)) {
        _spu_RXX->dRSAME = arg0->dRSAME;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x40000)) {
        _spu_RXX->mLDIFF = arg0->mLDIFF;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x80000)) {
        _spu_RXX->mRDIFF = arg0->mRDIFF;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x100000)) {
        _spu_RXX->mLCOMB3 = arg0->mLCOMB3;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x200000)) {
        _spu_RXX->mRCOMB3 = arg0->mRCOMB3;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x400000)) {
        _spu_RXX->mLCOMB4 = arg0->mLCOMB4;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x800000)) {
        _spu_RXX->mRCOMB4 = arg0->mRCOMB4;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x01000000)) {
        _spu_RXX->dLDIFF = arg0->dLDIFF;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x02000000)) {
        _spu_RXX->dRDIFF = arg0->dRDIFF;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x04000000)) {
        _spu_RXX->mLAPF1 = arg0->mLAPF1;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x08000000)) {
        _spu_RXX->mRAPF1 = arg0->mRAPF1;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x10000000)) {
        _spu_RXX->mLAPF2 = arg0->mLAPF2;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x20000000)) {
        _spu_RXX->mRAPF2 = arg0->mRAPF2;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x40000000)) {
        _spu_RXX->vLIN = arg0->vLIN;
    }
    if ((temp_a2 != 0) || ((s32)temp_a1 < 0)) {
        _spu_RXX->vRIN = arg0->vRIN;
    }
}
