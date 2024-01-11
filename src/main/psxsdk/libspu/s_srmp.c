#include "common.h"
#include "libspu_internal.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libspu/s_srmp", SpuSetReverbModeParam);

void _spu_setReverbAttr(struct rev_param_entry* arg0) {
    s32 temp_a2;
    u32 temp_a1;

    temp_a1 = arg0->flags;
    temp_a2 = temp_a1 == 0;
    if ((temp_a2 != 0) || (temp_a1 & 1)) {
        _spu_RXX->rxx.dAPF1 = arg0->dAPF1;
    }
    if ((temp_a2 != 0) || (temp_a1 & 2)) {
        _spu_RXX->rxx.dAPF2 = arg0->dAPF2;
    }
    if ((temp_a2 != 0) || (temp_a1 & 4)) {
        _spu_RXX->rxx.vIIR = arg0->vIIR;
    }
    if ((temp_a2 != 0) || (temp_a1 & 8)) {
        _spu_RXX->rxx.vCOMB1 = arg0->vCOMB1;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x10)) {
        _spu_RXX->rxx.vCOMB2 = arg0->vCOMB2;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x20)) {
        _spu_RXX->rxx.vCOMB3 = arg0->vCOMB3;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x40)) {
        _spu_RXX->rxx.vCOMB4 = arg0->vCOMB4;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x80)) {
        _spu_RXX->rxx.vWALL = arg0->vWALL;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x100)) {
        _spu_RXX->rxx.vAPF1 = arg0->vAPF1;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x200)) {
        _spu_RXX->rxx.vAPF2 = arg0->vAPF2;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x400)) {
        _spu_RXX->rxx.mLSAME = arg0->mLSAME;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x800)) {
        _spu_RXX->rxx.mRSAME = arg0->mRSAME;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x1000)) {
        _spu_RXX->rxx.mLCOMB1 = arg0->mLCOMB1;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x2000)) {
        _spu_RXX->rxx.mRCOMB1 = arg0->mRCOMB1;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x4000)) {
        _spu_RXX->rxx.mLCOMB2 = arg0->mLCOMB2;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x8000)) {
        _spu_RXX->rxx.mRCOMB2 = arg0->mRCOMB2;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x10000)) {
        _spu_RXX->rxx.dLSAME = arg0->dLSAME;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x20000)) {
        _spu_RXX->rxx.dRSAME = arg0->dRSAME;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x40000)) {
        _spu_RXX->rxx.mLDIFF = arg0->mLDIFF;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x80000)) {
        _spu_RXX->rxx.mRDIFF = arg0->mRDIFF;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x100000)) {
        _spu_RXX->rxx.mLCOMB3 = arg0->mLCOMB3;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x200000)) {
        _spu_RXX->rxx.mRCOMB3 = arg0->mRCOMB3;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x400000)) {
        _spu_RXX->rxx.mLCOMB4 = arg0->mLCOMB4;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x800000)) {
        _spu_RXX->rxx.mRCOMB4 = arg0->mRCOMB4;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x01000000)) {
        _spu_RXX->rxx.dLDIFF = arg0->dLDIFF;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x02000000)) {
        _spu_RXX->rxx.dRDIFF = arg0->dRDIFF;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x04000000)) {
        _spu_RXX->rxx.mLAPF1 = arg0->mLAPF1;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x08000000)) {
        _spu_RXX->rxx.mRAPF1 = arg0->mRAPF1;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x10000000)) {
        _spu_RXX->rxx.mLAPF2 = arg0->mLAPF2;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x20000000)) {
        _spu_RXX->rxx.mRAPF2 = arg0->mRAPF2;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x40000000)) {
        _spu_RXX->rxx.vLIN = arg0->vLIN;
    }
    if ((temp_a2 != 0) || ((s32)temp_a1 < 0)) {
        _spu_RXX->rxx.vRIN = arg0->vRIN;
    }
}
